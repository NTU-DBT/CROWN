#!/usr/bin/env python3
"""Correctness-gated whole-implementation legacy/native/SQLite B04 study.

All implementations receive the same physical events and required observations.
Each fresh process retains identical fresh-owner warmups before one measured
pass. JVM/parser/formatting/layout differences remain explicit confounders.
"""
from copy import deepcopy
from fractions import Fraction
import argparse
import datetime
import json
import os
from pathlib import Path
import random
import re
import sys

sys.dont_write_bytecode = True
from component_workloads import L3_SQL, L5_DISTINCT, L5_GROUP, catalog, evaluate_request
from ranking_analysis import ratio
from run_measurements import Experiment, build_provenance, digest, distribution, environment, require
from run_operational_evaluation import check_report, count_signature, observation_key, save, stage_samples, wanted


def legacy_actual(actual, family):
    """Decode actual published scalar/group text or named Scala signed rows."""
    if family == 'l5_distinct_count':
        text = actual['raw_output']
        require(re.fullmatch(r'(0|[1-9][0-9]*)\.0000\n',text) is not None, 'invalid legacy cardinality text')
        return int(text.split('.')[0])
    if family == 'l5_group_count':
        groups = []
        keys = set()
        for line in actual['raw_output'].splitlines():
            match = re.fullmatch(r'\(([1-9][0-9]*),([1-9][0-9]*)\) -> ([1-9][0-9]*)\.0000',line)
            require(match is not None, 'invalid full legacy group text')
            key = [int(match[1]),int(match[2])]
            require(tuple(key) not in keys, 'duplicate full legacy group')
            keys.add(tuple(key)); groups.append({'key':key,'values':[*key,int(match[3])]})
        return groups
    changes = []
    for line in actual['delta_text'].splitlines():
        match = re.fullmatch(r'([+-])\s+(.+)',line)
        require(match is not None, 'invalid Scala signed record')
        require(re.fullmatch(r'\([A-D],-?[0-9]+\)(?:\s*,\s*\([A-D],-?[0-9]+\)){3}',match[2]) is not None,
                'invalid Scala signed payload')
        pairs = re.findall(r'\(([A-D]),(-?[0-9]+)\)',match[2])
        require(len(pairs) == 4 and {name for name,_ in pairs} == set('ABCD'), 'invalid Scala named tuple')
        values = {name:int(value) for name,value in pairs}
        changes.append({'operation':match[1],'values':[values[name] for name in 'ABCD']})
    return {'rows':actual['rows'],'delta':changes}


def check_observations(report, arm, request, oracle, verify, reference=None):
    """Check external verify observations or any measured pass's frozen duties.

    Native verification uses the stronger native checker before this function
    admits measured counts. No large oracle graph is needed during timing.
    """
    implementation = {'set':'native_unweighted_set','aggregate':'native_sql_aggregate',
                      'legacy_cpp':'legacy_cpp_local_api','legacy_scala':'legacy_scala_local_api','sqlite':'sqlite_recomputation_v1'}[arm['adapter']]
    require(report['implementation'] == implementation and all(report[key] == request[key]
            for key in ('command','case_id','query_family','output')), 'external adapter identity differs')
    require(len(report['passes']) == request['warmup_passes']+1, 'external pass count differs')
    checked = 0
    for index,value in enumerate(report['passes']):
        require(value['warmup'] is (index < request['warmup_passes']), 'external warmup differs')
        for key in ('initialize_ns','loop_wall_ns','teardown_ns'):
            require(value[key] is None if verify else type(value[key]) is int and value[key] >= 0, 'external clock differs')
        require(len(value['epochs']) == len(request['events']), 'external physical horizon differs')
        for offset,epoch in enumerate(value['epochs'],1):
            require(epoch['sequence'] == offset and epoch['phase'] == request['events'][offset-1]['phase'], 'external source order differs')
            for key,sample in epoch.items():
                if key.endswith('_ns') and sample is not None:
                    require(not verify and type(sample) is int and sample >= 0, 'component epoch clock differs')
            if verify:
                actual = epoch['actual'] if arm['adapter'] == 'sqlite' else legacy_actual(epoch['actual'],request['query_family'])
                require(observation_key(actual,request['output']) == observation_key(wanted(oracle['epochs'][offset-1],request['output']),request['output']),
                        arm['id']+': external output differs at physical input '+str(offset))
                checked += 1
            else:
                require(epoch['actual'] is None, 'external measure captured output graph')
        if reference:
            require(count_signature(value) == reference['counts'], 'external measured output obligations differ')
    fields = reference['identity'] if reference else ('implementation','query_family','output','source_sql_sha256','sqlite_version')
    identity = {key:report[key] for key in fields if key in report}
    require(reference is None or identity == reference['identity'], 'external implementation identity changed')
    return {'identity':identity,'counts':count_signature(report['passes'][-1]),'checked_prefixes':checked}


def run(args):
    for name,value in vars(args).items():
        if isinstance(value,Path): setattr(args,name,value.resolve())
    source, build, output = args.source.resolve(), args.build_dir.resolve(), args.output.resolve()
    require(sys.platform.startswith('linux') and hasattr(os,'wait4'), 'study requires Linux wait4')
    require(0 <= args.warmups <= 5 and 1 <= args.repetitions <= 30 and 1 <= args.command_timeout <= 3600, 'invalid finite trial grant')
    require(1 <= args.max_events <= 1000000 and 1 <= args.max_total_bytes <= 4*1024**3, 'invalid matched input/output grant')
    require(args.preflight_only or args.cpu is not None, 'timing requires explicit CPU affinity')
    require(args.cpu is None or args.cpu in os.sched_getaffinity(0), 'CPU outside allowed affinity')
    require(not output.exists() and args.cohorts.stat().st_size <= 64*1024**2, 'output exists or manifest exceeds grant')
    document = json.loads(args.cohorts.read_text())
    require(document['kind'] == 'b04_matched_baseline_cohorts' and document['schema_version'] == 1, 'unknown matched cohort schema')
    require(1 <= len(document['arms']) <= 128, 'invalid matched arm grant')
    arms = {arm['id']:arm for arm in document['arms']}
    require(len(arms) == len(document['arms']), 'duplicate matched arm')
    queries = {'l3_full_rows':(L3_SQL,'delta_and_snapshot'),'l5_distinct_count':(L5_DISTINCT,'cardinality'),'l5_group_count':(L5_GROUP,'groups_full')}
    catalogs = {'l3_full_rows':catalog({'g1':('a','b'),'g2':('b','c'),'g3':('c','d')}),
                'l5_distinct_count':catalog({'graph':('src','dst')}),'l5_group_count':catalog({'graph':('src','dst')})}
    for identifier,arm in arms.items():
        require(identifier and identifier.replace('-','').replace('_','').isalnum(), 'invalid matched arm id')
        require(arm['adapter'] in ('set','aggregate','legacy_cpp','legacy_scala','sqlite'), 'unknown matched adapter')
        request = arm['request']; family = request['query_family']
        require(family in queries and (request['program']['sql'],request['output']) == queries[family], 'fixed original query/observation differs')
        require(request['program'] == {'sql':queries[family][0],'catalog':catalogs[family]}, 'fixed original physical column mapping differs')
        require(request['command'] == 'verify' and 0 < len(request['events']) <= args.max_events, 'invalid matched event grant')
        require((arm['adapter'] != 'legacy_scala' or family == 'l3_full_rows') and
                (arm['adapter'] != 'legacy_cpp' or family != 'l3_full_rows'), 'wrong fixed original program')
        if arm['adapter'] in ('set','aggregate'):
            require(arm['adapter'] == ('aggregate' if family == 'l5_group_count' else 'set'), 'wrong native fixed-query adapter')
            require(request['native'].get('observation_interval',1) == 1 and request['native'].get('transaction_batch_size',1) == 1,
                    'matched baselines require a transaction and observation after every physical input')
            require(request['native'].get('mode') == 'delta' if arm['adapter'] == 'set' else not request['native'].get('aggregate_source_only',False),
                    'matched native arm requires scalar delta fold or ordinary SQL aggregate runtime')
        request['warmup_passes'],request['measured_passes'] = args.warmups,1
    require(document['comparisons'] and len({item['id'] for item in document['comparisons']}) == len(document['comparisons']), 'empty or duplicate matched comparisons')
    for comparison in document['comparisons']:
        left, right = arms[comparison['baseline']], arms[comparison['variant']]
        require(comparison['axis'] in ('whole_implementation','incremental_vs_recomputation') and right['adapter'] in ('set','aggregate') and
                left['adapter'] in (('sqlite',) if comparison['axis'] == 'incremental_vs_recomputation' else ('legacy_cpp','legacy_scala')),
                'matched comparison mislabels implementation scope')
        require(left['request']['program'] == right['request']['program'] and left['request']['events'] == right['request']['events'] and
                left['request']['output'] == right['request']['output'], 'matched source/query/output differs')
    native = {'set':args.set_adapter.resolve(),'aggregate':args.aggregate_adapter.resolve()}
    provenance = build_provenance(source,build,args.crown.resolve(),args.collector.resolve(),list(native.values()))
    for name in ('tools/run_baseline_evaluation.py','tools/sqlite_component.py','tools/component_workloads.py',
                 'tools/run_operational_evaluation.py','tools/ranking_analysis.py','tools/support/ComponentReplay.scala',
                 'examples/component-runtime/legacy_cpp.cpp','examples/component-runtime/component_request.hpp'):
        provenance['harness_sources'][name] = digest(source/name)
    # Bind actual immutable executable/JAR/class bytes. Existing qualification
    # manifests supply build lineage; this study does not rebuild old prefixes.
    adapters = {arm['adapter'] for arm in arms.values()}
    pins,classpath = {},[]
    if 'legacy_cpp' in adapters:
        require(args.legacy_cpp is not None and args.legacy_provenance is not None, 'original C++ arms need executable and qualification pins')
        legacy_pins = json.loads(args.legacy_provenance.read_text())['relative_sha256']
        pins.update({str(source/path):value for path,value in legacy_pins.items()})
        require(str(args.legacy_cpp) in pins, 'legacy executable absent from supplied qualification')
        pins[str(args.legacy_provenance)] = digest(args.legacy_provenance)
    if 'legacy_scala' in adapters:
        require(args.java is not None and args.scala_classes is not None and args.scala_classpath and args.scala_provenance is not None,
                'original Scala arms need Java, helper classes, published classpath and qualification pins')
        classpath = [args.scala_classes,*[Path(part).resolve() for part in args.scala_classpath.split(os.pathsep)]]
    listings = {}
    launchers = ([args.java] if 'legacy_scala' in adapters else [])+[Path(sys.executable).resolve()]
    for path in [*launchers,*classpath]:
        require(path.exists(), 'missing external runtime input')
        files = sorted(child for child in path.rglob('*') if child.is_file()) if path.is_dir() else [path]
        require(files, 'empty external classpath entry')
        if path.is_dir(): listings[str(path)] = [str(child.relative_to(path)) for child in files]
        for child in files: pins[str(child)] = digest(child)
    if 'legacy_scala' in adapters:
        expected = json.loads(args.scala_provenance.read_text())['relative_sha256']
        for path in [args.java,*classpath]:
            files = [child for child in path.rglob('*') if child.is_file()] if path.is_dir() else [path]
            for child in files:
                require(expected.get(str(child.relative_to(source))) == pins[str(child)], 'Scala runtime/classpath differs from qualification inventory')
        pins[str(args.scala_provenance)] = digest(args.scala_provenance)
    for path,expected in pins.items(): require(digest(Path(path)) == expected, 'external input qualification differs')
    output.mkdir(parents=True,exist_ok=False); args._created_output = True
    (output/'java-home').mkdir(); (output/'java-tmp').mkdir()
    # Third-party process side effects belong to the new study directory.
    os.chdir(output)
    experiment = Experiment(output,args.cpu,args.command_timeout,args.max_total_bytes)
    packet = {'schema_version':1,'kind':'b04_matched_baseline_study','status':'running','B04_accepted':False,
              'started_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'environment':environment(),'build':provenance,
              'working_directory':str(output),
              'manifest_sha256':digest(args.cohorts),'cohorts':document,'external_pins':pins,'classpath_listings':listings,
              'verification':[],'runs':[],'summaries':[],'comparisons':[],'correctness_gate':'pending',
              'scope':'finite whole-implementation observations; original C++ local APIs and Scala keyed harness; parser/scalar/formatting/layout/JVM/JIT/allocator costs remain; SQLite is exact full recomputation with Python; no pure-dispatch or isolated incremental-operator cause; native account and whole-child RSS differ; no steady-state JVM or power-loss claim'}
    checkpoint = lambda: save(output/'experiment.json',packet)
    save(output/'frozen-cohorts.json',document,True); packet['frozen_cohorts_sha256'] = digest(output/'frozen-cohorts.json'); checkpoint()
    def command(arm,path):
        adapter = arm['adapter']
        if adapter in native: return [native[adapter],path]
        if adapter == 'legacy_cpp': return [args.legacy_cpp.resolve(),path]
        if adapter == 'sqlite': return [Path(sys.executable).resolve(),source/'tools/sqlite_component.py',path]
        return [args.java.resolve(),'-Duser.home='+str(output/'java-home'),'-Djava.io.tmpdir='+str(output/'java-tmp'),
                '-XX:-UsePerfData','-cp',os.pathsep.join(map(str,classpath)),'ComponentReplay',path]
    gates,requests = {},{}
    for identifier,arm in arms.items():
        request = deepcopy(arm['request']); path = output/(identifier+'.verify.request.json'); save(path,request,True)
        oracle = evaluate_request(request,arm['oracle'])
        report,record = experiment.invoke('preflight:'+identifier,command(arm,path))
        check = check_report if arm['adapter'] in native else check_observations
        gate = check(report,arm,request,oracle,True); gates[identifier] = gate
        # The verified raw report retains every actual observation. Measurement
        # needs only the horizon plus frozen output counts, so release this
        # arm's large independent row graph before evaluating the next arm.
        del oracle
        requests[identifier] = {'path':str(path),'sha256':digest(path)}
        packet['verification'].append({'arm':identifier,'gate':gate,'request':requests[identifier],**record}); checkpoint()
    packet['correctness_gate'] = 'all_preflights_pass'; checkpoint()
    samples = {identifier:[] for identifier in arms}
    order = list(arms); random.Random(args.schedule_seed).shuffle(order)
    if not args.preflight_only:
        for repetition in range(args.repetitions):
            for identifier in order[repetition % len(order):]+order[:repetition % len(order)]:
                require(digest(args.cohorts) == packet['manifest_sha256'] and digest(Path(requests[identifier]['path'])) == requests[identifier]['sha256'], 'frozen matched input changed')
                arm = arms[identifier]; request = deepcopy(arm['request']); request['command'] = 'measure'
                path = output/(identifier+'.measure-'+str(repetition)+'.request.json'); save(path,request,True)
                report,record = experiment.invoke('measure:'+identifier+':'+str(repetition),command(arm,path))
                check_observations(report,arm,request,None,False,gates[identifier])
                samples[identifier].append((report,record)); packet['runs'].append({'arm':identifier,'repetition':repetition,'request':str(path),'request_sha256':digest(path),**record}); checkpoint()
        for identifier,values in samples.items():
            stages = {}
            for report,_ in values:
                for name,counts in stage_samples(report).items(): stages.setdefault(name,[]).extend(counts)
            loops = stages['pass.loop_wall_ns']; inputs = len(arms[identifier]['request']['events'])
            packet['summaries'].append({'arm':identifier,'physical_inputs_per_pass':inputs,
                'loop_ns_per_physical_input':ratio(Fraction(sum(loops),len(loops)*inputs)),
                'stage_latency_ns':{name:distribution(counts) for name,counts in stages.items()},
                'process_maxrss_KiB':distribution([record['process_maxrss_KiB'] for _,record in values]),
                'output_counts':[count_signature(report['passes'][-1]) for report,_ in values],
                'native_memory_final_owner':[report['passes'][-1]['native_memory_before_teardown'] for report,_ in values]})
        summaries = {value['arm']:value for value in packet['summaries']}
        for comparison in document['comparisons']:
            values = [summaries[comparison[side]]['loop_ns_per_physical_input'] for side in ('baseline','variant')]
            a,b = [Fraction(int(value['numerator']),int(value['denominator'])) for value in values]
            packet['comparisons'].append({**comparison,'variant_over_baseline':ratio(b/a) if a else None,
                                          'baseline_identity':gates[comparison['baseline']]['identity'],'variant_identity':gates[comparison['variant']]['identity']})
    # Recheck bytes/listings only after all measured children have exited.
    for path,expected in {**provenance['files'],**provenance['compiled_dependencies'],**pins}.items():
        require(digest(Path(path)) == expected, 'compiled/external input changed during matched study')
    for path,expected in provenance['harness_sources'].items(): require(digest(source/path) == expected, 'matched harness changed')
    for path,listing in listings.items(): require(sorted(str(child.relative_to(path)) for child in Path(path).rglob('*') if child.is_file()) == listing, 'classpath directory changed')
    for tool in experiment.tools.values(): require(digest(Path(tool['path'])) == tool['sha256'], 'measurement launcher changed')
    require(digest(args.cohorts) == packet['manifest_sha256'] and digest(output/'frozen-cohorts.json') == packet['frozen_cohorts_sha256'], 'matched manifest changed')
    packet.update(status='preflight_complete' if args.preflight_only else 'complete_conditional_matched',
                  finished_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),frozen_inputs_unchanged=True,commands_sha256=digest(output/'commands.json')); checkpoint()
    print('Matched B04 packet: '+str(len(arms))+' arms, '+str(len(packet['runs']))+' measured invocations: '+str(output))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('source','build-dir','crown','collector','set-adapter','aggregate-adapter','cohorts','output'):
        parser.add_argument('--'+name,type=Path,required=True)
    for name in ('legacy-cpp','legacy-provenance','java','scala-classes','scala-provenance'):
        parser.add_argument('--'+name,type=Path)
    parser.add_argument('--scala-classpath')
    parser.add_argument('--warmups',type=int,default=1); parser.add_argument('--repetitions',type=int,default=3)
    parser.add_argument('--cpu',type=int); parser.add_argument('--schedule-seed',type=int,default=20261115)
    parser.add_argument('--command-timeout',type=int,default=300); parser.add_argument('--max-events',type=int,default=65536)
    parser.add_argument('--max-total-bytes',type=int,default=1024**3); parser.add_argument('--preflight-only',action='store_true')
    args = parser.parse_args(); args._created_output = False
    try:
        run(args)
    except Exception as error:
        path = args.output.resolve()/'experiment.json'
        if args._created_output and path.is_file():
            packet = json.loads(path.read_text()); packet.update(status='failed',failure=str(error)); save(path,packet)
        print('Matched B04 study failed: '+str(error),file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
