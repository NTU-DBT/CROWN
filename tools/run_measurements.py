#!/usr/bin/env python3
"""Controlled repeated measurements of admitted, checksummed B02 workloads."""
from __future__ import annotations
import argparse
import collections
import datetime
import hashlib
import json
import math
import os
from pathlib import Path
import platform
import re
import shlex
import shutil
import signal
import statistics
import subprocess
import sys
import time

sys.dont_write_bytecode = True
from verify_workloads import canonical, file_entry, static_verify


def require(value, message):
    if not value: raise ValueError(message)


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def measurement_tools():
    """Pin lightweight target-resource and affinity launchers outside Python."""
    result = {}
    for name in ('time', 'taskset'):
        found = shutil.which(name)
        require(found is not None, 'missing measurement launcher: ' + name)
        path = Path(found).resolve()
        result[name] = {'path': str(path), 'sha256': digest(path)}
    return result


def distribution(values):
    require(all(isinstance(x, int) and not isinstance(x, bool) and x >= 0 for x in values), 'invalid nonnegative raw sample')
    ordered = sorted(values); bins = collections.Counter(x.bit_length() for x in values)
    percentile = lambda p: ordered[(len(ordered) * p + 99) // 100 - 1] if ordered else None
    return {'samples': len(values), 'minimum': min(values) if values else None, 'maximum': max(values) if values else None,
            'sum': sum(values), 'mean': statistics.fmean(values) if values else None,
            'standard_deviation': statistics.stdev(values) if len(values) > 1 else None,
            'p50': percentile(50), 'p95': percentile(95), 'p99': percentile(99),
            'percentile_method': 'nearest_rank_ceil_pN',
            'histogram': [{'bin': b, 'lower_inclusive': 0 if b == 0 else 1 << (b - 1),
                           'upper_inclusive': 0 if b == 0 else (1 << b) - 1, 'count': count} for b, count in sorted(bins.items())]}


def environment():
    cpu = {}
    if Path('/proc/cpuinfo').exists():
        for line in Path('/proc/cpuinfo').read_text().splitlines():
            if ':' in line:
                key, value = (x.strip() for x in line.split(':', 1))
                if key in ['vendor_id', 'model name', 'cpu family', 'model', 'stepping', 'microcode'] and key not in cpu: cpu[key] = value
    memory = {}
    if Path('/proc/meminfo').exists():
        for line in Path('/proc/meminfo').read_text().splitlines():
            key, value = line.split(':', 1)
            if key in ['MemTotal', 'SwapTotal']: memory[key] = value.strip()
    cpu_policy = {}
    for path in sorted(Path('/sys/devices/system/cpu/cpufreq').glob('policy*/scaling_governor')):
        try: cpu_policy[str(path)] = path.read_text().strip()
        except OSError: cpu_policy[str(path)] = None
    return {'platform': platform.platform(), 'uname': list(platform.uname()), 'python': sys.version,
            'measurement_tools': measurement_tools(),
            'process_maxrss_source': 'GNU time target child; outer wait4 launcher RSS retained separately',
            'cpu': cpu, 'memory': memory, 'logical_cpus': os.cpu_count(),
            'parent_affinity': sorted(os.sched_getaffinity(0)) if hasattr(os, 'sched_getaffinity') else None,
            'clock': 'time.monotonic_ns', 'cache_state': 'uncontrolled_OS_and_hardware_caches',
            'allocator': 'native_CXX_operator_new_and_recorded_query_account; no custom_process_allocator_selected',
            'frequency_governors_observed': cpu_policy, 'frequency_control': 'observed_only_not_changed_or_guaranteed_constant',
            'environment_variables': {k: os.environ.get(k) for k in ['LANG', 'LC_ALL', 'TZ', 'ASAN_OPTIONS', 'UBSAN_OPTIONS', 'MALLOC_ARENA_MAX', 'OMP_NUM_THREADS', 'LD_PRELOAD', 'LD_LIBRARY_PATH', 'GLIBC_TUNABLES']}}


# Hashes bind current bytes; filesystem freshness checks are not cryptographic build lineage.
def build_provenance(source_root, build, crown, collector, extra_binaries=()):
    require(crown.parent == build and collector.parent == build, 'controlled measurements require binaries from the supplied CMake build')
    cache = build / 'CMakeCache.txt'; commands_path = build / 'compile_commands.json'
    require(cache.is_file() and commands_path.is_file(), 'missing actual build provenance')
    commands = json.loads(commands_path.read_text()); files = {str(cache): digest(cache), str(commands_path): digest(commands_path)}
    links, targets, artifacts = {}, set(), {}
    binaries = [crown, collector, *extra_binaries]
    require(all(binary.parent == build and binary.is_file() for binary in binaries), 'extra controlled binary is outside the supplied CMake build')
    require(len({binary.name for binary in binaries}) == len(binaries), 'duplicate controlled binary target')
    for binary in binaries:
        name = binary.name
        link_path = build / 'CMakeFiles' / (name + '.dir') / 'link.txt'
        require(link_path.is_file(), 'missing actual binary link command')
        require(link_path.stat().st_mtime_ns <= binary.stat().st_mtime_ns, 'link command changed after measured executable; relink before measurement')
        links[name] = link_path.read_text(); files[str(link_path)] = digest(link_path); targets.add(name + '.dir')
        artifacts[name + '.dir'] = binary
        for argument in shlex.split(links[name]):
            if argument.endswith(('.a', '.o')):
                path = Path(argument); path = path if path.is_absolute() else build / path
                require(path.is_file(), 'missing linked object/archive'); files[str(path)] = digest(path)
                require(path.stat().st_mtime_ns <= binary.stat().st_mtime_ns, 'linked object/archive is newer than measured executable; relink before measurement')
                if path.name.startswith('libcrown_') and path.suffix == '.a':
                    target = path.name.removeprefix('lib').removesuffix('.a') + '.dir'
                    targets.add(target); artifacts[target] = path
    compiled = []; dependency_hashes = {}
    target_units = {target: 0 for target in targets}
    for entry in commands:
        args = shlex.split(entry['command']); relative = Path(args[args.index('-o') + 1])
        if not any(part in targets for part in relative.parts): continue
        obj = Path(entry['directory']) / relative
        require(obj.is_file(), 'linked target has an unbuilt C++ unit')
        target = next(part for part in relative.parts if part in targets)
        target_units[target] += 1
        require(obj.stat().st_mtime_ns <= artifacts[target].stat().st_mtime_ns, 'compiled object is newer than its archive/executable; rebuild the containing target before measurement')
        flags = build / 'CMakeFiles' / target / 'flags.make'
        require(flags.is_file() and flags.stat().st_mtime_ns <= obj.stat().st_mtime_ns, 'compiler flags changed after object; rebuild before measurement')
        files[str(flags)] = digest(flags)
        source = Path(entry['file']); require(source.is_file(), 'source bytes unavailable for controlled build provenance')
        require(source.stat().st_mtime_ns <= obj.stat().st_mtime_ns, 'source changed after its compiled object; rebuild before measurement')
        dependencies = Path(str(obj) + '.d')
        require(dependencies.is_file(), 'missing compiler dependency record; rebuild with Makefile dependency output')
        dependency_text = dependencies.read_text().replace('\\\n', ' ')
        require(':' in dependency_text, 'invalid compiler dependency record')
        paths = []
        for name in shlex.split(dependency_text.split(':', 1)[1]):
            path = Path(name); path = path if path.is_absolute() else Path(entry['directory']) / path
            path = path.resolve(); require(path.is_file(), 'compiled dependency bytes unavailable')
            require(path.stat().st_mtime_ns <= obj.stat().st_mtime_ns, 'header/dependency changed after its compiled object; rebuild before measurement')
            key = str(path)
            if key not in dependency_hashes: dependency_hashes[key] = digest(path)
            paths.append(key)
        compiled.append({'source': str(source), 'source_sha256': digest(source), 'object': str(obj), 'object_sha256': digest(obj),
                         'command': entry['command'], 'dependency_record': str(dependencies),
                         'dependency_record_sha256': digest(dependencies), 'dependencies': paths})
    require(any(x['source'].endswith('/examples/workload-measurement/main.cpp') for x in compiled), 'collector object is absent from actual build inventory')
    require(all(target_units.values()), 'linked project target has no recorded compiled units')
    for binary in binaries: files[str(binary)] = digest(binary)
    for extra in [build / '_deps/libpg_query-build-config.txt', build / 'CrownConfig.cmake']:
        if extra.is_file(): files[str(extra)] = digest(extra)
    compiler = re.search(r'(?m)^CMAKE_CXX_COMPILER:(?:FILEPATH|STRING)=(.+)$', cache.read_text())
    require(compiler is not None, 'compiler path is absent from actual CMake cache')
    version = subprocess.run([compiler[1], '--version'], capture_output=True, text=True, check=True, timeout=30).stdout
    repository = {'source_root': str(source_root), 'head': None, 'worktree_changes': None,
                  'qualification': 'Source/object/dependency hashes identify the measured bytes; HEAD alone does not identify an uncommitted build.'}
    git_env = dict(os.environ, GIT_OPTIONAL_LOCKS='0')
    top = subprocess.run(['git', '-C', str(source_root), 'rev-parse', '--show-toplevel'], capture_output=True, text=True, env=git_env, timeout=30)
    if top.returncode == 0 and Path(top.stdout.strip()).resolve() == source_root:
        head = subprocess.run(['git', '-C', str(source_root), 'rev-parse', '--verify', 'HEAD'], capture_output=True, text=True, env=git_env, timeout=30)
        require(head.returncode == 0, 'cannot inspect source repository HEAD')
        repository['head'] = head.stdout.strip()
        status = subprocess.run(['git', '-C', str(source_root), 'status', '--porcelain', '--untracked-files=no'], capture_output=True, text=True, env=git_env, timeout=30)
        require(status.returncode == 0, 'cannot inspect source revision changes')
        repository['worktree_changes'] = bool(status.stdout)
    harness_sources = {}
    for relative in ['tools/run_measurements.py', 'tools/verify_workloads.py', 'tools/generate_workloads.py',
                     'tools/verify_imported_workloads.py', 'schemas/workload-measurement-v2.schema.json',
                     'schemas/measurement-experiment-v1.schema.json']:
        path = source_root / relative; require(path.is_file(), 'missing harness source'); harness_sources[relative] = digest(path)
    return {'build_directory': str(build), 'files': files, 'link_commands': links, 'compiled_units': compiled,
            'compiler': compiler[1], 'compiler_version_output': version,
            'compiler_binary_sha256': digest(Path(compiler[1]).resolve()), 'compiled_dependencies': dependency_hashes,
            'repository': repository, 'harness_sources': harness_sources,
            'qualification': 'Actual binaries/objects/archives/commands and recorded C++ dependency bytes are bound. Source/header/flags-to-object, object-to-archive and link-input/command-to-executable freshness is checked by filesystem timestamps; this is not cryptographic build lineage against altered timestamps. Dynamically loaded system libraries are not archived.'}


class Experiment:
    def __init__(self, output, cpu, timeout, byte_limit):
        self.output = output; self.cpu = cpu; self.timeout = timeout; self.byte_limit = byte_limit
        self.bytes = 0; self.commands = []
        self.tools = measurement_tools()

    # Raw-output bytes are checked after the child exits; sink files are outside this grant.
    def invoke(self, label, arguments):
        require(len(self.commands) < 10000, 'experiment command count grant exceeded')
        number = len(self.commands); out = self.output / f'command-{number:05d}.stdout'; err = self.output / f'command-{number:05d}.stderr'
        resources = self.output / f'command-{number:05d}.resources'
        target = list(map(str, arguments))
        if self.cpu is not None:
            target = [self.tools['taskset']['path'], '--cpu-list', str(self.cpu), *target]
        launch = [self.tools['time']['path'], '--quiet', '--format=%M', '--output=' + str(resources), '--', *target]
        start = time.monotonic_ns()
        timed_out = False
        with out.open('xb') as stdout, err.open('xb') as stderr:
            process = subprocess.Popen(launch, stdout=stdout, stderr=stderr, start_new_session=True)
            while True:
                pid, status, usage = os.wait4(process.pid, os.WNOHANG)
                if pid: break
                if time.monotonic_ns() - start > self.timeout * 1_000_000_000:
                    try: os.killpg(process.pid, signal.SIGKILL)
                    except ProcessLookupError: pass
                    _, status, usage = os.wait4(process.pid, 0)
                    process.returncode = os.waitstatus_to_exitcode(status)
                    timed_out = True
                    break
                time.sleep(0.002)
            process.returncode = os.waitstatus_to_exitcode(status)
        elapsed = time.monotonic_ns() - start
        self.bytes += out.stat().st_size + err.stat().st_size
        # The lightweight time process forks the target after exec. Its target
        # RSS does not inherit the large Python parent's pre-exec high-water.
        resource_text = resources.read_text().strip() if resources.exists() else ''
        target_rss = int(resource_text) if resource_text else None
        record = {'index': number, 'label': label, 'arguments': list(map(str, arguments)), 'exit_code': process.returncode,
                  'launch_arguments': launch,
                  'wall_ns': elapsed, 'user_cpu_seconds': usage.ru_utime, 'system_cpu_seconds': usage.ru_stime,
                  'cpu_scope': 'owned_launcher_and_waited_target',
                  'exit_detection_poll_period_ns': 2000000,
                  'process_maxrss_KiB': target_rss, 'launcher_maxrss_KiB': usage.ru_maxrss,
                  'resource_usage': resources.name, 'resource_usage_sha256': digest(resources) if resources.exists() else None,
                  'requested_affinity': [self.cpu] if self.cpu is not None else None,
                  'stdout': out.name, 'stdout_sha256': digest(out), 'stderr': err.name, 'stderr_sha256': digest(err), 'timed_out': timed_out}
        self.commands.append(record); self.save_commands()
        if timed_out: raise TimeoutError('measurement command timed out: ' + label)
        require(self.bytes <= self.byte_limit, 'experiment raw-output byte limit exceeded')
        require(process.returncode == 0 and not err.read_bytes(), f'{label} failed; inspect {err}')
        require(target_rss is not None and target_rss >= 0, 'missing target RSS resource record')
        return json.loads(out.read_text()), record

    def save_commands(self):
        (self.output / 'commands.json').write_text(json.dumps(self.commands, indent=2) + '\n')


def indexed_options():
    # Explicit measured configuration, equal to the verified finite native
    # corpus backend grant; no implicit change of the engine defaults.
    return {'schema_version': 2,
            'policy': {'arithmetic': 'exact-nonnull-v1', 'planner': 'crown-tree-v1', 'optimization': 'structural-height-v1', 'cost_model': 'no-cost-v1'},
            'limits': {'work': 1000000, 'identity_work': 1000000},
            'indexed_storage': {'algorithm': 'indexed_chained_v1', 'traversal': 'insertion_first_live_key_v1',
                                'component_scope': 'per_table_including_undo', 'work_scope': 'operation_aggregate',
                                'limits': dict(zip(['rows', 'indices', 'keys', 'memberships', 'nodes', 'directory_slots', 'arena_slots', 'arena_pins', 'journal_entries'],
                                                   [4096, 64, 32768, 65536, 131072, 524288, 8192, 32768, 8192])),
                                'work': {key: 1000000000 for key in ['structural_steps', 'scalar_fields', 'scalar_bytes', 'pointer_slots', 'link_actions']}}}


def summarize(reports):
    events = [event for report in reports for event in report['epochs']]
    phases = {}
    names = ['decode_ns', 'native_prepare_commit_ns', 'output_setup_ns', 'output_next_ns', 'encoding_ns', 'sink_write_wait_ns', 'output_release_ns', 'epoch_release_ns', 'input_ack_ns', 'event_active_ns', 'diagnostics_ns']
    for event in events:
        phase = phases.setdefault(event['phase'], {name: 0 for name in names})
        for name in names: phase[name] += event[name]
    return {'runs': len(reports), 'update_latency_ns': distribution([event['event_active_ns'] for event in events]),
            'native_prepare_commit_ns': distribution([event['native_prepare_commit_ns'] for event in events]),
            'output_call_latency_ns': distribution([call['nanoseconds'] for event in events for call in event['output_calls']]),
            'first_result_delay_ns': distribution([event['output_setup_ns'] + event['output_calls'][0]['nanoseconds'] for event in events
                                                   if event['output_calls'] and event['output_calls'][0]['returned_row']]),
            'successful_next_ns': distribution([call['nanoseconds'] for event in events for call in event['output_calls'] if call['returned_row']]),
            'termination_next_ns': distribution([call['nanoseconds'] for event in events for call in event['output_calls'] if not call['returned_row']]),
            'query_current_requested_bytes': distribution([event['memory']['current_requested_bytes'] for event in events]),
            'query_cumulative_peak_requested_bytes': distribution([event['memory']['peak_requested_bytes'] for event in events]),
            'loop_wall_ns': distribution([report['timings']['loop_wall_ns'] for report in reports]), 'phases': phases,
            'output_rows': sum(report['output_rows'] for report in reports),
            'accounting': 'Phase partitions include every load event; native_prepare_commit includes internal delta preparation; optional operator metrics overlap per their registry and must not be summed across layers.'}


def run(args):
    source = args.source.resolve(); pack = (args.pack or source / 'benchmarks/workloads').resolve()
    crown = args.crown.resolve(); collector = args.collector.resolve(); build = args.build_dir.resolve()
    require(sys.platform.startswith('linux') and hasattr(os, 'wait4'), 'controlled runner requires Linux wait4 accounting')
    require(1 <= args.repetitions <= 30 and 0 <= args.warmups <= 5, 'repetition/warmup limit exceeded')
    require(1 <= args.command_timeout <= 3600 and 1 <= args.max_total_bytes <= 4 * 1024**3, 'invalid runner resource limit')
    if args.cpu is not None: require(args.cpu in os.sched_getaffinity(0), 'requested CPU is outside the allowed affinity mask')
    require(0 <= args.sink_delay_us <= 100000, 'sink delay exceeds collector grant')
    manifest, validation = static_verify(source, pack)
    queries = {query['id']: query for query in manifest['queries']}
    eligible = {w['id']: w for w in manifest['workloads'] if queries[w['query']]['expected_admission'] == 'admitted'}
    ids = args.case or list(eligible)
    require(len(ids) == len(set(ids)) and set(ids) <= set(eligible), 'unknown, duplicate or native-ineligible workload case')
    modes = args.mode or ['maintenance', 'snapshot', 'delta']; backends = args.backend or ['reference_ordered_v1', 'indexed_chained_v1']
    require(len(set(modes)) == len(modes) and len(set(backends)) == len(backends), 'duplicate output mode/backend')
    require(len(ids) * len(modes) * len(backends) * (args.repetitions + args.warmups + 1) <= 10000, 'experiment command count grant exceeded')
    provenance = build_provenance(source, build, crown, collector)
    lock = source / 'dependencies.lock.json'
    provenance['dependency_lock'] = {'path': str(lock), 'sha256': digest(lock), 'contents': json.loads(lock.read_text())}
    output = args.output.resolve(); output.mkdir(parents=True, exist_ok=False)
    experiment = Experiment(output, args.cpu, args.command_timeout, args.max_total_bytes)
    packet = {'schema_version': 1, 'kind': 'controlled_workload_measurements', 'status': 'running',
              'started_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
              'manifest_sha256': digest(pack / 'manifest.json'), 'environment': environment(), 'build': provenance,
              'configuration': {'case_ids': ids, 'modes': modes, 'backends': backends, 'repetitions': args.repetitions, 'warmups': args.warmups,
                                'codec': args.codec, 'sink': args.sink, 'sink_delay_us': args.sink_delay_us,
                                'observation': args.observe, 'workload_counters': not args.no_workload_counters,
                                'cpu': args.cpu, 'single_writer': True, 'schedule_seed': args.schedule_seed,
                                'command_timeout_seconds': args.command_timeout, 'max_total_raw_bytes': args.max_total_bytes},
              'manifest_validation': validation, 'correctness_gate': 'pending', 'compilation': [], 'verification': [], 'runs': [],
              'summaries': [], 'limits': ['No fixed speedup or statistical confidence claim.', 'Volatile native-core runs have no WAL/checkpoint/fsync.',
                                        'Compiler process wall includes startup/read/SQL/proof/lowering/export; artifact load/validation is separately reported by collector.',
                                        'Target RSS includes collector/compiler buffers; outer launcher RSS is separate; query-account bytes have their own scope.',
                                        'Raw warmups are retained and excluded from measured aggregates; OS/hardware caches are uncontrolled.']}
    def save(): (output / 'experiment.json').write_text(json.dumps(packet, indent=2) + '\n')
    save(); plans = {}; canonical_catalogs = {}; combinations = []
    options_path = output / 'indexed-options.json'; options_path.write_text(json.dumps(indexed_options(), indent=2) + '\n')
    try:
        for identifier in ids:
            workload = eligible[identifier]; query = queries[workload['query']]
            sql = file_entry(pack, query['sql']); catalog = file_entry(pack, query['catalog'])
            if query['id'] not in canonical_catalogs:
                data, _ = experiment.invoke('catalog', [crown, 'canonicalize-catalog', catalog])
                canonical_catalogs[query['id']] = hashlib.sha256(canonical(data).encode()).hexdigest()
            expected_path = file_entry(pack, workload['oracle']); expected = json.loads(expected_path.read_text())
            bound = output / (identifier.replace('/', '__') + '.input.jsonl')
            if not bound.exists():
                records = [json.loads(line) for line in file_entry(pack, workload['events']).read_text().splitlines()]
                for event in records: event['catalog_sha256'] = canonical_catalogs[query['id']]
                bound.write_text(''.join(canonical(event) + '\n' for event in records))
            for backend in backends:
                require(backend in query['expected_backends'], 'backend not admitted by workload manifest')
                key = (query['id'], backend)
                arguments = [crown, 'compile', sql, catalog]
                if backend == 'indexed_chained_v1': arguments += ['--physical-options', options_path]
                if key not in plans:
                    plan, command = experiment.invoke('preflight_compile', arguments)
                    plan_path = output / (query['id'] + '-' + backend + '.compiled.json'); plan_path.write_text(canonical(plan))
                    checked_plan, _ = experiment.invoke('validate_plan', [crown, 'validate-plan', 'compiled', plan_path])
                    require(checked_plan['physical_valid'] and checked_plan['height_status'] in ['proven_minimum', 'checked_constant_operator'], 'compiled artifact lacks checked admission')
                    plans[key] = (plan_path, plan, arguments)
                plan_path, _, _ = plans[key]
                for mode in modes:
                    label = identifier + '/' + backend + '/' + mode
                    request = {'schema_version': 1, 'command': 'verify', 'output_mode': mode, 'codec': args.codec, 'sink': args.sink,
                               'sink_delay_us': args.sink_delay_us, 'observation': args.observe, 'workload_counters': not args.no_workload_counters,
                               'memory_limit_bytes': 256 * 1024 * 1024, 'max_events': 4096, 'max_output_calls': 1000000, 'max_encoded_bytes': 64 * 1024 * 1024,
                               'phases': [event['phase'] for event in expected['epochs']], 'label': label, 'preflight_receipt_sha256': None}
                    request_path = output / (label.replace('/', '__') + '.request.json'); request_path.write_text(canonical(request))
                    report, command = experiment.invoke('verify', [collector, plan_path, bound, request_path, expected_path, output / 'verification-unused-sink'])
                    require(report.get('verified') is True and report['records'] == workload['events_count'] and report['backend'] == backend and report['output_mode'] == mode, 'native preflight failed or changed configuration')
                    require(report['input_sha256'] == digest(bound) and report['artifact_sha256'] == digest(plan_path) and
                            report['runtime_mode'] == ('delta' if mode == 'delta' else 'maintenance'), 'preflight input/plan/runtime binding mismatch')
                    packet['verification'].append({'label': label, 'command': command['index'], 'receipt_sha256': command['stdout_sha256'],
                                                   'binding_sha256': report['binding_sha256'], 'input_sha256': digest(bound), 'oracle_sha256': digest(expected_path), 'passed': True})
                    combinations.append({'label': label, 'request': request, 'request_path': request_path, 'plan': plan_path, 'input': bound,
                                         'expected': expected, 'receipt': command['stdout_sha256'], 'binding': report['binding_sha256']})
        packet['correctness_gate'] = 'passed_all_configurations_before_warmup_or_measurement'; save()
        for (query_id, backend), (plan_path, plan, arguments) in plans.items():
            for repetition in range(args.warmups + args.repetitions):
                compiled, command = experiment.invoke('compile_warmup' if repetition < args.warmups else 'compile_measured', arguments)
                require(compiled == plan, 'repeated compilation changed the admitted artifact')
                packet['compilation'].append({'query': query_id, 'backend': backend, 'warmup': repetition < args.warmups,
                                              'repetition': repetition - args.warmups, 'command': command['index'], 'process_wall_ns': command['wall_ns'],
                                              'process_maxrss_KiB': command['process_maxrss_KiB']})
        reports = collections.defaultdict(list)
        for repetition in range(args.warmups + args.repetitions):
            schedule = sorted(combinations, key=lambda combo: hashlib.sha256(f'{args.schedule_seed}:{repetition}:{combo["label"]}'.encode()).hexdigest())
            for combo in schedule:
                request = dict(combo['request'], command='measure', preflight_receipt_sha256=combo['receipt'])
                request_path = combo['request_path'].with_name(combo['request_path'].stem + f'.round-{repetition}.json')
                with request_path.open('x') as stream: stream.write(canonical(request))
                sink_path = output / (combo['label'].replace('/', '__') + f'-round-{repetition}.sink')
                report, command = experiment.invoke('warmup' if repetition < args.warmups else 'measure',
                                                     [collector, combo['plan'], combo['input'], request_path, '-', sink_path])
                expected = combo['expected']; mode = request['output_mode']
                counts = [len(event['signed_delta']) if mode == 'delta' else len(event['current_rows']) if mode == 'snapshot' else 0 for event in expected['epochs']]
                require(report['kind'] == 'native_workload_measurement' and report['binding_sha256'] == combo['binding'] and
                        report['request']['preflight_receipt_sha256'] == combo['receipt'], 'measurement/preflight context mismatch')
                require([event['output_rows'] for event in report['epochs']] == counts and report['output_rows'] == sum(counts), 'measurement output demand mismatch')
                require(report['records'] == len(counts) and report['runtime_mode'] == ('delta' if mode == 'delta' else 'maintenance'), 'measured runtime mode/horizon mismatch')
                if args.cpu is not None: require(report['environment']['actual_affinity'] == [args.cpu], 'requested CPU affinity was not applied')
                require(report['sink']['calls'] == sum(counts), 'sink consumption count mismatch')
                if args.sink == 'file':
                    require(sink_path.stat().st_size == report['sink']['bytes'], 'sink byte count mismatch')
                    if args.codec == 'jsonl':
                        actual = [json.loads(line) for line in sink_path.read_text().splitlines()]
                        expected_output = []
                        for event in expected['epochs']:
                            if mode == 'snapshot': expected_output.extend({'sequence': event['sequence'], 'values': row} for row in event['current_rows'])
                            elif mode == 'delta': expected_output.extend({'sequence': event['sequence'], **row} for row in event['signed_delta'])
                        require(sorted(map(canonical, actual)) == sorted(map(canonical, expected_output)), 'measured encoded file differs from independent oracle')
                entry = {'label': combo['label'], 'warmup': repetition < args.warmups, 'repetition': repetition - args.warmups,
                         'command': command['index'], 'raw_report': command['stdout'], 'raw_report_sha256': command['stdout_sha256'],
                         'process_maxrss_KiB': command['process_maxrss_KiB'], 'collector_binding_sha256': report['binding_sha256']}
                packet['runs'].append(entry)
                if repetition >= args.warmups: reports[combo['label']].append(command['stdout'])
                save()
        # Raw reports are immutable files; materialize one repetition group for
        # summary instead of retaining every configuration's full Python DTOs.
        packet['summaries'] = [{'label': label, **summarize([json.loads((output / name).read_text()) for name in names])}
                               for label, names in sorted(reports.items())]
        packet['compilation_summaries'] = [{'query': query, 'backend': backend,
            'process_wall_ns': distribution([row['process_wall_ns'] for row in packet['compilation'] if row['query'] == query and row['backend'] == backend and not row['warmup']]),
            'process_maxrss_KiB': distribution([row['process_maxrss_KiB'] for row in packet['compilation'] if row['query'] == query and row['backend'] == backend and not row['warmup']])}
            for query, backend in plans]
        packet['completed_utc'] = datetime.datetime.now(datetime.timezone.utc).isoformat()
        packet['status'] = 'complete'; packet['commands_sha256'] = digest(output / 'commands.json'); save()
        print(f'B03 controlled packet complete: {len(combinations)} configurations, {args.repetitions} measured repetitions, {args.warmups} retained warmups; {output / "experiment.json"}')
    except Exception as error:
        packet['status'] = 'failed'; packet['error'] = str(error)
        packet['completed_utc'] = datetime.datetime.now(datetime.timezone.utc).isoformat(); save(); raise


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, required=True); parser.add_argument('--pack', type=Path)
    parser.add_argument('--crown', type=Path, required=True); parser.add_argument('--collector', type=Path, required=True)
    parser.add_argument('--build-dir', type=Path, required=True); parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--case', action='append'); parser.add_argument('--mode', action='append', choices=['maintenance', 'snapshot', 'delta'])
    parser.add_argument('--backend', action='append', choices=['reference_ordered_v1', 'indexed_chained_v1'])
    parser.add_argument('--repetitions', type=int, default=3); parser.add_argument('--warmups', type=int, default=1)
    parser.add_argument('--codec', choices=['none', 'jsonl'], default='jsonl'); parser.add_argument('--sink', choices=['discard', 'file'], default='discard')
    parser.add_argument('--sink-delay-us', type=int, default=0); parser.add_argument('--observe', choices=['off', 'counters', 'timed'], default='counters')
    parser.add_argument('--no-workload-counters', action='store_true'); parser.add_argument('--cpu', type=int)
    parser.add_argument('--schedule-seed', type=int, default=20261111); parser.add_argument('--command-timeout', type=int, default=300)
    parser.add_argument('--max-total-bytes', type=int, default=512 * 1024 * 1024)
    run(parser.parse_args())


if __name__ == '__main__':
    try: main()
    except Exception as error:
        print('B03 measurement failed: ' + str(error), file=sys.stderr); raise SystemExit(1)
