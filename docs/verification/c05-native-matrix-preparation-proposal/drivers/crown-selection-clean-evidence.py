#!/usr/bin/env python3
"""Root-only wrapper around the unchanged clean helper, retaining direct dependencies."""
from pathlib import Path
import argparse, datetime, hashlib, importlib.util, json, os, re, shlex, signal, subprocess, sys, time

ROOT = Path('/home/userroot/Codex/CROWN')
V = ROOT/'build/verification'
ARTIFACTS = V/'selection-clean-artifacts'
MANIFEST = V/'selection-clean-artifacts-manifest.json'
FREEZE = V/'selection-execution-freeze.json'

def need(value, message):
    if not value: raise RuntimeError(message)
def sha(path): return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def stop_group(child):
    try: os.killpg(child.pid,signal.SIGTERM)
    except ProcessLookupError: pass
    try: child.wait(timeout=3)
    except subprocess.TimeoutExpired: pass
    try: os.killpg(child.pid,signal.SIGKILL)
    except ProcessLookupError: pass
    return child.wait()
def interrupted(_signum,_frame): raise InterruptedError('clean adapter received termination signal')
def inputs(root):
    def one(roots, extra):
        names = set(extra)
        for name in roots:
            names.update(p.relative_to(root).as_posix() for p in (root/name).rglob('*') if p.is_file()
                         and '__pycache__' not in p.parts and p.suffix not in {'.pyc','.pyo'})
        digest = hashlib.sha256()
        for name in sorted(names):
            digest.update(name.encode()); digest.update(b'\0'); digest.update((root/name).read_bytes()); digest.update(b'\0')
        return {'count':len(names),'sha256':digest.hexdigest()}
    roots = ['include','src','apps','tests','cmake']
    return {'native':one(roots,['CMakeLists.txt','CMakePresets.json']),
            'execution':one(roots+['schemas','tools','third_party'],['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'])}

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--freeze-sha256',required=True)
    parser.add_argument('--configuration',choices=['Release'],default='Release')
    parser.add_argument('--parallel',type=int,choices=[2],default=2)
    parser.add_argument('--log',default='build/verification/selection-clean-source.log')
    args = parser.parse_args()
    signal.signal(signal.SIGTERM,interrupted)
    need(args.log == 'build/verification/selection-clean-source.log', 'unexpected clean log destination')
    need(sha(FREEZE) == args.freeze_sha256, 'unexpected freeze FILE')
    freeze = json.loads(FREEZE.read_text())
    def guard():
        need(sha(FREEZE) == args.freeze_sha256, 'freeze FILE drift')
        need(freeze['root_execution_helpers'].get(str(Path(__file__).resolve())) == sha(__file__), 'unbound clean adapter')
        for name,digest in freeze['root_execution_helpers'].items(): need(sha(name) == digest, 'helper FILE drift: '+name)
        for name,digest in freeze['canonical_compiler_files'].items(): need(sha(name) == digest, 'compiler FILE drift: '+name)
        for cache in freeze['predecessor_toolchain_caches'].values():
            for name,digest in cache['compiler_files'].items():
                need(sha(name) == digest and freeze['canonical_compiler_files'].get(str(Path(name).resolve())) == digest,
                     'compiler alias drift: '+name)
        need(sha(ROOT/'tools/verify_clean_build.py') == freeze['clean_original_helper_sha256'], 'native clean helper drift')
    guard()
    need(not ARTIFACTS.exists() and not MANIFEST.exists() and not (ROOT/args.log).exists(), 'preserve existing clean evidence')
    before = inputs(ROOT); need(before['native'] == freeze['native'] and before['execution'] == freeze['execution'], 'source drift before clean leg')
    ARTIFACTS.mkdir()
    record = {'configuration':'clean-source','started_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
              'freeze_sha256':args.freeze_sha256,'adapter_sha256':sha(__file__),
              'original_helper':'tools/verify_clean_build.py','original_helper_sha256':sha(ROOT/'tools/verify_clean_build.py'),
              'source_before':before,'snapshot_inputs':None,'commands':[],'retained':[],'dependency_records':[],
              'dependency_inputs':{},
              'dependency_capture_complete':False,'status':'running','terminal':False,
              'scope':'Runtime wrapper adds verbose output, phase ceilings and evidence retention. Native helper and per-test properties are unchanged.'}
    with MANIFEST.open('x') as handle: handle.write(json.dumps(record,indent=2)+'\n')
    def save():
        temporary = MANIFEST.with_suffix('.json.writing')
        with temporary.open('w') as handle: handle.write(json.dumps(record,indent=2)+'\n')
        temporary.replace(MANIFEST)
    retained = {}
    def retain_file(path,build):
        path = Path(path); build = Path(build).resolve()
        need(path.resolve().is_relative_to(build), 'artifact escapes temporary build: '+str(path))
        name = path.relative_to(build).as_posix(); before_hash = sha(path)
        if name in retained:
            need(retained[name]['sha256'] == before_hash, 'retained artifact changed: '+name)
            return retained[name]
        target = ARTIFACTS/name; target.parent.mkdir(parents=True,exist_ok=True)
        with target.open('xb') as handle: handle.write(path.read_bytes())
        need(sha(target) == before_hash == sha(path), 'artifact changed during retention: '+name)
        row = {'source':str(path),'retained':str(target.relative_to(ROOT)),'sha256':before_hash}
        retained[name] = row; record['retained'].append(row)
        return row
    def retain_metadata(build):
        candidates = [build/'compile_commands.json',build/'CMakeCache.txt',build/'CTestTestfile.cmake',
                      build/'Testing/Temporary/LastTest.log',build/'Testing/Temporary/LastTestsFailed.log']
        for pattern in ['*/flags.make','*/link.txt','*/build.make','*/CMakeCCompiler.cmake','*/CMakeCXXCompiler.cmake']:
            candidates.extend((build/'CMakeFiles').glob(pattern))
        candidates.extend((build/'_deps/libpg_query').glob('*/Makefile'))
        for path in sorted(set(candidates)):
            if path.is_file(): retain_file(path,build)
    def retain_dependencies(build):
        source_root = Path(record['snapshot_source']).resolve()
        database = build/'compile_commands.json'; db_pin = retain_file(database,build)
        expected = {(r['target'],r['source']) for r in freeze['expected_compile_units']}
        seen = set(); dep_paths = set(); rows = []; aliases = {}
        def included_file(word, directory):
            observed = Path(word)
            if not observed.is_absolute(): observed = directory/observed
            canonical = observed.resolve(); key = str(canonical)
            need(observed.is_relative_to(source_root) == canonical.is_relative_to(source_root), 'dependency crosses snapshot boundary')
            need(observed.is_relative_to(build.resolve()) == canonical.is_relative_to(build.resolve()), 'dependency crosses build boundary')
            need(not observed.is_relative_to(ROOT) and not canonical.is_relative_to(ROOT), 'working-tree dependency leaked into clean build')
            need('docs/verification' not in str(observed) and 'docs/verification' not in key, 'proposal dependency in clean build')
            need(str(observed) not in aliases or aliases[str(observed)] == key, 'contradictory dependency alias')
            aliases[str(observed)] = key
            if key not in record['dependency_inputs']:
                digest = sha(canonical)
                if canonical.is_relative_to(build.resolve()):
                    pin = retain_file(canonical,build)
                    need(pin['sha256'] == digest, 'generated include changed during retention')
                    item = {'scope':'generated_build','sha256':digest,'build_relative':canonical.relative_to(build.resolve()).as_posix(),
                            'retained':pin['retained']}
                elif canonical.is_relative_to(source_root):
                    name = canonical.relative_to(source_root).as_posix()
                    need(freeze['execution_file_sha256'].get(name) == digest, 'included snapshot source is not frozen: '+name)
                    item = {'scope':'snapshot_source','sha256':digest,'source_relative':name,'frozen_sha256':digest}
                else:
                    need(not canonical.is_relative_to(source_root.parent), 'unclassified temporary dependency')
                    item = {'scope':'external_system','sha256':digest}
                record['dependency_inputs'][key] = item
            return {'compiler_spelling':word,'observed_path':str(observed),'canonical_input':key}
        for entry in json.loads(database.read_text()):
            argv = entry.get('arguments') or shlex.split(entry['command'])
            need('-c' in argv and '-o' in argv, 'non-compilation entry in database')
            directory = Path(entry['directory']).resolve()
            need(directory == build.resolve(), 'unexpected compilation working directory')
            output_raw = argv[argv.index('-o')+1]
            output = Path(output_raw)
            if not output.is_absolute(): output = directory/output
            output = output.resolve(); need(output.is_relative_to(build.resolve()), 'object escapes clean build')
            object_relative = output.relative_to(build.resolve()).as_posix()
            match = re.fullmatch(r'CMakeFiles/([^/]+)\.dir/(.+)\.o',object_relative)
            need(match is not None, 'unrecognized project object path')
            source = Path(entry['file'])
            if not source.is_absolute(): source = directory/source
            source = source.resolve(); need(source.is_relative_to(source_root), 'source escapes clean snapshot')
            unit = (match[1],source.relative_to(source_root).as_posix())
            need(match[2] == unit[1] and unit in expected and unit not in seen, 'duplicate/unexpected target-source entry')
            seen.add(unit)
            dependency_raw = argv[argv.index('-MF')+1] if '-MF' in argv else output_raw+'.d'
            dependency = Path(dependency_raw)
            if not dependency.is_absolute(): dependency = directory/dependency
            dependency = dependency.resolve()
            need(dependency.is_relative_to(build.resolve()) and dependency not in dep_paths, 'dependency alias/escape')
            dep_paths.add(dependency); pin = retain_file(dependency,build)
            text = (ROOT/pin['retained']).read_text().replace('\\\n',' ')
            need(text.count(':') == 1, 'unsupported/ambiguous Make dependency rule')
            left,right = text.split(':',1); left_words = shlex.split(left)
            need(len(left_words) == 1, 'dependency rule has multiple targets')
            lhs = Path(left_words[0]); lhs = lhs if lhs.is_absolute() else directory/lhs
            need(lhs.resolve() == output, 'dependency target differs from object')
            spellings = [included_file(word,directory) for word in shlex.split(right)]
            need(str(source) in {item['canonical_input'] for item in spellings}, 'dependency rule omits its source')
            rows.append({'target':unit[0],'source':unit[1],'command':entry.get('command'),'arguments':argv,
                         'directory':entry['directory'],'object':str(output),'object_sha256':sha(output),
                         'dependency_raw':dependency_raw,'dependency':str(dependency),
                         'retained':pin['retained'],'sha256':pin['sha256'],'included_inputs':spellings})
        need(seen == expected and len(rows) == freeze['expected_compile_command_entries'] == 238,
             'direct clean dependency population differs')
        record['dependency_records'] = rows; record['dependency_capture_complete'] = True
        record['dependency_capture_phase'] = 'after_successful_build_before_ctest'
        record['compile_database_pin'] = db_pin
        record['dependency_scope'] = 'All 238 .o.d rules and actual canonical included-file hashes captured. Snapshot files bind to frozen paths; generated headers are retained; external system inputs are hashed. Semantic include isolation still requires independent audit.'
        save()
    def snapshot_after_tests():
        record['snapshot_inputs_after_tests'] = inputs(Path(record['snapshot_source']))
        need(record['snapshot_inputs_after_tests'] == record['snapshot_inputs'], 'temporary snapshot changed during tests')
        for name,item in record['dependency_inputs'].items():
            need(sha(name) == item['sha256'], 'actual included input changed before cleanup: '+name)
        record['dependency_inputs_stable_before_cleanup'] = True
    sys.dont_write_bytecode = True
    spec = importlib.util.spec_from_file_location('crown_selection_clean_original',ROOT/'tools/verify_clean_build.py')
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
    symbol_path = Path(__file__).resolve().with_name('crown-selection-symbols.py')
    spec2 = importlib.util.spec_from_file_location('crown_selection_symbols',symbol_path)
    symbols = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(symbols)
    original_copy = module.copy_snapshot
    def copied(repository,source,log):
        original_copy(repository,source,log)
        record['snapshot_source'] = str(source); record['snapshot_inputs'] = inputs(source)
        need(record['snapshot_inputs']['native'] == freeze['native'] and record['snapshot_inputs']['execution'] == freeze['execution'],
             'clean snapshot differs from freeze')
        save()
    def run(command,log):
        enriched = list(command)
        phase = 'test' if command[0] == 'ctest' else ('build' if '--build' in command else 'configure')
        if phase in {'build','test'}: enriched.append('--verbose')
        module.COMMAND_TIMEOUT_SECONDS = freeze['wrapper_timeout_seconds'][phase]
        row = {'phase':phase,'original':list(command),'executed':enriched,
               'timeout_seconds':module.COMMAND_TIMEOUT_SECONDS,'status':'running'}
        record['commands'].append(row); save(); started = time.monotonic()
        build = Path(record['snapshot_source'])/'build'
        try:
            guard()
            log.write('\n$ '+shlex.join(enriched)+'\n'); log.flush()
            child = subprocess.Popen(enriched,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,start_new_session=True)
            try:
                raw,_ = child.communicate(timeout=module.COMMAND_TIMEOUT_SECONDS)
                row['exit_code'] = child.returncode
            except (subprocess.TimeoutExpired,InterruptedError,KeyboardInterrupt) as error:
                row['child_exit_code_after_stop'] = stop_group(child)
                row['process_group_signalled_and_direct_child_reaped'] = True
                raw,_ = child.communicate()
                row['exit_code'] = 124 if isinstance(error,subprocess.TimeoutExpired) else 130
                row['timed_out'] = isinstance(error,subprocess.TimeoutExpired); row['termination_error'] = str(error)
            output = raw.decode('utf-8',errors='replace')
            log.write(output)
            if output and not output.endswith('\n'): log.write('\n')
            if row['exit_code'] != 0:
                log.write('command exited with status '+str(row['exit_code'])+'\n'); log.flush()
                raise module.VerificationError('command failed or timed out: '+shlex.join(enriched))
            log.write('command completed in '+format(time.monotonic()-started,'.2f')+'s\n'); log.flush()
            row['status'] = 'passed'
            if phase == 'build':
                retain_metadata(build); retain_dependencies(build)
            if phase == 'test':
                retain_metadata(build)
                manifest = symbols.collect(build,'clean-source',args.freeze_sha256)
                record['symbols_manifest'] = str(manifest.relative_to(ROOT)); record['symbols_manifest_sha256'] = sha(manifest)
                snapshot_after_tests()
            return output
        except Exception as error:
            row['status'] = 'failed'; row['error'] = repr(error)
            # Best-effort failure evidence does not manufacture completeness or pass.
            try: retain_metadata(build)
            except Exception as retention_error: row['retention_error'] = repr(retention_error)
            if phase == 'test':
                try: snapshot_after_tests()
                except Exception as snapshot_error: row['snapshot_guard_error'] = repr(snapshot_error)
            raise
        finally:
            row['seconds'] = round(time.monotonic()-started,3); save()
    module.copy_snapshot = copied; module.run_command = run
    module.COMMAND_TIMEOUT_SECONDS = freeze['wrapper_timeout_seconds']['configure']
    code = 1
    try:
        code = module.main(['--configuration',args.configuration,'--parallel',str(args.parallel),'--log',args.log])
        need(code == 0 and record['dependency_capture_complete'] and record.get('dependency_inputs_stable_before_cleanup') is True and len(record['commands']) == 3
             and all(r['status'] == 'passed' for r in record['commands']) and record.get('symbols_manifest'), 'clean execution incomplete')
    except Exception as error:
        record['error'] = repr(error); code = 1
    try:
        record['source_after'] = inputs(ROOT); record['source_stable'] = record['source_before'] == record['source_after']
        record['temporary_removed'] = not Path(record['snapshot_source']).parent.exists() if record.get('snapshot_source') else False
        need(record['source_stable'] and record['temporary_removed'], 'source drift or temporary tree not removed')
        guard(); record['identity_guards_stable'] = True
    except Exception as error:
        record['final_guard_error'] = repr(error); record['identity_guards_stable'] = False; code = 1
    record.update({'exit_code':code,'status':'passed' if code == 0 else 'failed','terminal':True,
                   'completed_utc':datetime.datetime.now(datetime.timezone.utc).isoformat()})
    save()
    return code

if __name__ == '__main__': raise SystemExit(main())
