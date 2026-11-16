#!/usr/bin/env python3
"""C07 held-out C05 ranking evaluation against actually measured candidates."""
from __future__ import annotations
import argparse
import collections
import datetime
from fractions import Fraction
import hashlib
import json
import os
from pathlib import Path
import sys
sys.dont_write_bytecode=True
from generate_ranking_evaluation import verify as verify_split
from ranking_analysis import error_summary,export_fit,fit_proxy,ordering_quality,predict,ratio,regret
from run_measurements import Experiment,build_provenance,digest,distribution,environment,indexed_options,require
from verify_workloads import canonical

OBJECTIVES={'event_active_ns_per_input':'nanoseconds_per_physical_input',
            'native_prepare_and_epoch_release_ns_per_input':'nanoseconds_per_physical_input',
            'native_peak_requested_bytes':'native_query_account_requested_bytes'}
def save_json(path,value):path.write_text(json.dumps(value,ensure_ascii=False,sort_keys=True,indent=2)+'\n')
def request_file(path,value):
    with path.open('x') as stream:stream.write(canonical(value))
# Query-account peak is cumulative requested bytes, distinct from process RSS.
def run_costs(report):
    epochs=report['epochs'];require(epochs,'empty measured trace')
    active=sum(e['event_active_ns'] for e in epochs)
    native=sum(e['native_prepare_commit_ns']+e['epoch_release_ns'] for e in epochs)
    peak=max(report['memory_initial']['peak_requested_bytes'],report['memory_final']['peak_requested_bytes'],*(e['memory']['peak_requested_bytes'] for e in epochs))
    return {'event_active_ns_per_input':Fraction(active,len(epochs)),
            'native_prepare_and_epoch_release_ns_per_input':Fraction(native,len(epochs)),
            'native_peak_requested_bytes':Fraction(peak)}, {'event_active_ns_total':active,'native_prepare_and_epoch_release_ns_total':native,'native_peak_requested_bytes':peak}
def primary_scores(policy,candidates):
    assessments=[a for a in policy.get('assessments',[]) if a['purpose'] in [0,2]]
    require(len(assessments)==1,'native policy has no unique primary assessment')
    by_key={c['structural_key']:str(c['index']) for c in candidates};result={}
    for row in assessments[0]['scores']:
        require(row['structural_key'] in by_key,'score names a foreign candidate')
        denominator=int(row['proxy_denominator']);require(denominator>0,'proxy denominator unavailable')
        result[by_key[row['structural_key']]]=Fraction(int(row['proxy_numerator']),denominator)
    require(set(result)==set(by_key.values()),'native assessment skipped candidates');return result
def main_run(args):
    source=args.source.resolve();pack=(args.pack or source/'benchmarks/ranking').resolve();build=args.build_dir.resolve()
    crown=args.crown.resolve();collector=args.collector.resolve();exporter=args.exporter.resolve()
    require(sys.platform.startswith('linux') and hasattr(os,'wait4'),'held-out runner requires Linux wait4')
    require(1<=args.repetitions<=30 and 0<=args.warmups<=5,'invalid repetition/warmup count')
    require(1<=args.candidates<=32 and 1<=args.command_timeout<=3600,'invalid candidate/timeout grant')
    require(1<=args.max_total_bytes<=4*1024**3,'invalid raw stdout/stderr byte grant')
    if args.cpu is not None:require(args.cpu in os.sched_getaffinity(0),'requested CPU is outside allowed affinity')
    manifest,validation=verify_split(source,pack);queries={q['id']:q for q in manifest['queries']};ids=args.query or list(queries)
    require(ids and len(set(ids))==len(ids) and set(ids)<=set(queries),'unknown/duplicate held-out query')
    modes=args.mode or ['maintenance','snapshot','delta'];backends=args.backend or ['reference_ordered_v1','indexed_chained_v1']
    require(len(set(modes))==len(modes) and len(set(backends))==len(backends),'duplicate mode/backend')
    provenance=build_provenance(source,build,crown,collector,[exporter])
    for name in ['tools/run_ranking_evaluation.py','tools/generate_ranking_evaluation.py','tools/ranking_analysis.py',
                 'schemas/compiled-candidate-v2.schema.json','schemas/ranking-export-v1.schema.json',
                 'schemas/ranking-trace-split-v1.schema.json','schemas/ranking-evaluation-v1.schema.json']:
        provenance['harness_sources'][name]=digest(source/name)
    lock=source/'dependencies.lock.json';provenance['dependency_lock']={'path':str(lock),'sha256':digest(lock),'contents':json.loads(lock.read_text())}
    output=args.output.resolve();output.mkdir(parents=True,exist_ok=False);experiment=Experiment(output,args.cpu,args.command_timeout,args.max_total_bytes)
    packet={'schema_version':1,'kind':'c07_held_out_ranking_evaluation','status':'running','started_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
            'manifest_sha256':digest(pack/'manifest.json'),'split_validation':validation,'split_contract':manifest['split_contract'],
            'environment':environment(),'build':provenance,'configuration':{'queries':ids,'modes':modes,'backends':backends,'candidate_limit':args.candidates,
              'repetitions':args.repetitions,'warmups':args.warmups,'schedule_seed':args.schedule_seed,'cpu':args.cpu,'codec':args.codec,'sink':args.sink,
              'native_memory_limit_bytes':256*1024*1024,'observation':'counters','workload':'counters','slot_limit':args.slot_limit,
              'require_exhausted_family':args.require_exhausted_family,'command_timeout_seconds':args.command_timeout,'max_total_raw_bytes':args.max_total_bytes},
            'correctness_gate':'pending','exports':[],'verification':[],'runs':[],'summaries':[],'analysis':[],
            'extensions':{'C03':'not_enabled_in_C05_baseline_evaluation','C04':'not_enabled','C06':'not_enabled'},
            'limits':['No fixed speedup, global minimum-cost or statistical confidence claim.',
              'Native C05 selection uses training only; affine calibration is an evaluation-layer assumption and never changes selection.',
              'Shared SQL families are evaluated on disjoint data/traces; this is not unseen-query-family generalization.',
              'Volatile native core with external codec/sink, no WAL/checkpoint/fsync; loading from empty remains charged.',
              'All retained candidates must pass independent preflight; correctness/resource failure stops the packet rather than silently shrinking the feasible set.',
              'Source query account peak is cumulative, not RSS or predicted future bytes; tuple/index slots are unitless.',
              'Warmups are retained/excluded, caches and CPU frequency are observed but uncontrolled.']}
    def save():save_json(output/'experiment.json',packet)
    save();groups=[];combinations=[];samples=collections.defaultdict(list);raw_totals=collections.defaultdict(list)
    try:
        for identifier in ids:
            query=queries[identifier];catalog=pack/query['catalog']['path'];sql=pack/query['sql']['path']
            canonical_catalog,_=experiment.invoke('canonicalize_catalog',[crown,'canonicalize-catalog',catalog]);catalog_sha=hashlib.sha256(canonical(canonical_catalog).encode()).hexdigest()
            cases=[t for t in manifest['traces'] if t['query']==identifier];training=[t for t in cases if t['role']=='train'];calibration=[t for t in cases if t['role']=='calibration']
            require(len(training)==len(calibration)==1 and any(t['role']=='evaluation' for t in cases),'split must have one training/calibration and held-out evaluation traces')
            bound={};expected={}
            for case in cases:
                records=[json.loads(line) for line in (pack/case['events']['path']).read_text().splitlines()]
                for record in records:record['catalog_sha256']=catalog_sha
                path=output/(case['id'].replace('/','__')+'.input.jsonl')
                with path.open('x') as stream:stream.write(''.join(canonical(record)+'\n' for record in records))
                bound[case['id']]=path;expected[case['id']]=json.loads((pack/case['oracle']['path']).read_text())
            for backend in backends:
                physical=indexed_options()
                if backend=='reference_ordered_v1':del physical['indexed_storage'];physical['schema_version']=1
                native_request={'schema_version':1,'physical_options':physical,'candidate_limit':args.candidates,'search_work':10000000,'enumeration_work':10000000,
                    'memory_limit_bytes':256*1024*1024,'max_events':4096,'require_exhausted_family':args.require_exhausted_family,'fallback':'require_evidence','slot_limit':args.slot_limit}
                req=output/(identifier+'-'+backend+'.export.request.json');request_file(req,native_request)
                exported,command=experiment.invoke('training_and_native_C05_export',[exporter,sql,catalog,bound[training[0]['id']],req])
                require(exported['kind']=='c07_native_ranking_export' and exported['training_sha256']==digest(bound[training[0]['id']]),'native export used different training data')
                require(exported['training_events']==training[0]['events_count'],'native training horizon differs')
                candidates=exported['candidates'];require(candidates and len({c['structural_key'] for c in candidates})==len(candidates),'candidate export is empty or duplicated')
                for policy in exported['policies']:
                    if 'selected_index' in policy:
                        selected=candidates[policy['selected_index']];require(selected['structural_key']==policy['selected_key'] and selected['physical_sha256']==policy['selected_physical_sha256'],'C05 choice differs from exported artifact')
                group={'query':identifier,'backend':backend,'native':exported,'calibration':calibration[0]['id'],'cases':cases};groups.append(group)
                packet['exports'].append({'query':identifier,'backend':backend,'command':command['index'],'raw_report':command['stdout'],'raw_report_sha256':command['stdout_sha256'],
                    'search_quality':exported['search'],'training':exported['training'],'policies':exported['policies'],'setup_timings':exported['setup_timings']})
                proof=candidates[0]['artifact']['height_certificate']
                for candidate in candidates:
                    require(candidate['backend']==backend and candidate['height']==exported['search']['proved_height'],'candidate changes backend/proved height')
                    require(candidate['artifact']['height_certificate']==proof,'export replaced the original proof witness for an alternative')
                    artifact=output/(identifier+'-'+backend+f'-candidate-{candidate["index"]}.compiled.json');request_file(artifact,candidate['artifact'])
                    for case in cases:
                        for mode in modes:
                            label=case['id']+'/'+backend+'/'+str(candidate['index'])+'/'+mode
                            request={'schema_version':1,'command':'verify','output_mode':mode,'codec':args.codec,'sink':args.sink,'sink_delay_us':0,
                                'observation':'counters','workload_counters':True,'memory_limit_bytes':256*1024*1024,'max_events':4096,'max_output_calls':1000000,
                                'max_encoded_bytes':64*1024*1024,'phases':[e['phase'] for e in expected[case['id']]['epochs']],'label':label,'preflight_receipt_sha256':None}
                            req=output/(label.replace('/','__')+'.verify.request.json');request_file(req,request)
                            report,command=experiment.invoke('preflight_candidate_verification',[collector,artifact,bound[case['id']],req,pack/case['oracle']['path'],output/'unused-verification-sink'])
                            require(report.get('verified') is True and report['backend']==backend and report['output_mode']==mode and report['records']==case['events_count'],'candidate preflight failed or mislabeled scope')
                            require(report['physical_sha256']==candidate['physical_sha256'] and report['artifact_sha256']==digest(artifact) and report['input_sha256']==digest(bound[case['id']]),'preflight source/plan binding differs')
                            packet['verification'].append({'label':label,'command':command['index'],'receipt_sha256':command['stdout_sha256'],'binding_sha256':report['binding_sha256'],'passed':True})
                            if case['role']!='train':combinations.append({'query':identifier,'backend':backend,'candidate':str(candidate['index']),'case':case,'mode':mode,'label':label,
                                'request':request,'artifact':artifact,'input':bound[case['id']],'oracle':expected[case['id']],'receipt':command['stdout_sha256'],'binding':report['binding_sha256']})
                save()
        packet['correctness_gate']='all_retained_candidates_and_all_splits_verified_before_warmup_or_measurement'
        choices=output/'choices-frozen.json';save_json(choices,packet['exports']);packet['choices_frozen_sha256']=digest(choices);save()
        # Choices stay frozen for both roles; evaluation also rechecks frozen calibration.
        def measure_role(role):
            selected=[c for c in combinations if c['case']['role']==role]
            for repetition in range(args.warmups+args.repetitions):
                schedule=sorted(selected,key=lambda c:hashlib.sha256(f'{args.schedule_seed}:{role}:{repetition}:{c["label"]}'.encode()).hexdigest())
                for combo in schedule:
                    require(digest(choices)==packet['choices_frozen_sha256'],'native choices changed during evaluation')
                    if role=='evaluation':require(digest(output/'calibration-frozen.json')==packet['calibration_frozen_sha256'],'calibration changed after freeze')
                    request=dict(combo['request'],command='measure',preflight_receipt_sha256=combo['receipt']);base=combo['label'].replace('/','__')+f'.round-{repetition}'
                    req=output/(base+'.request.json');request_file(req,request);sink=output/(base+'.sink')
                    report,command=experiment.invoke(role+('_warmup' if repetition<args.warmups else '_measure'),[collector,combo['artifact'],combo['input'],req,'-',sink])
                    require(report['kind']=='native_workload_measurement' and report['binding_sha256']==combo['binding'] and report['request']==request,'measured candidate context differs from verified context')
                    require(report['backend']==combo['backend'] and report['output_mode']==combo['mode'] and report['runtime_mode']==('delta' if combo['mode']=='delta' else 'maintenance'),'measured mode/backend labels differ')
                    if args.cpu is not None:require(report['environment']['actual_affinity']==[args.cpu],'actual affinity differs')
                    expected=combo['oracle'];mode=combo['mode'];counts=[len(e['signed_delta']) if mode=='delta' else len(e['current_rows']) if mode=='snapshot' else 0 for e in expected['epochs']]
                    require([e['output_rows'] for e in report['epochs']]==counts and report['output_rows']==report['sink']['calls']==sum(counts),'measured output demand differs from oracle')
                    if args.sink=='file':
                        require(sink.stat().st_size==report['sink']['bytes'],'sink bytes differ')
                        if args.codec=='jsonl':
                            wanted=[]
                            for e in expected['epochs']:
                                if mode=='snapshot':wanted.extend({'sequence':e['sequence'],'values':v} for v in e['current_rows'])
                                elif mode=='delta':wanted.extend({'sequence':e['sequence'],**v} for v in e['signed_delta'])
                            require(sorted(map(canonical,[json.loads(x) for x in sink.read_text().splitlines()]))==sorted(map(canonical,wanted)),'measured encoded rows differ from oracle')
                    cost,totals=run_costs(report);warmup=repetition<args.warmups
                    packet['runs'].append({'label':combo['label'],'role':role,'warmup':warmup,'repetition':repetition-args.warmups,'command':command['index'],
                        'raw_report':command['stdout'],'raw_report_sha256':command['stdout_sha256'],'costs':{k:ratio(v) for k,v in cost.items()},'totals':totals})
                    if not warmup:samples[combo['label']].append(cost);raw_totals[combo['label']].append(totals)
                    save()
        def mean_cost(case,backend,mode,candidate,objective):
            label=case+'/'+backend+'/'+candidate+'/'+mode;values=samples[label];require(len(values)==args.repetitions,'missing actual measured candidate repetitions')
            return sum((row[objective] for row in values),Fraction())/len(values)
        measure_role('calibration');models={};frozen=[]
        for group in groups:
            for mode in modes:
                for policy in group['native']['policies']:
                    if 'selected_index' not in policy:continue
                    proxies=primary_scores(policy,group['native']['candidates'])
                    for objective in OBJECTIVES:
                        pairs=[(proxies[c],mean_cost(group['calibration'],group['backend'],mode,c,objective)) for c in proxies]
                        model=fit_proxy(pairs);key=(group['query'],group['backend'],mode,policy['policy'],objective);models[key]=model
                        frozen.append({'query':group['query'],'backend':group['backend'],'mode':mode,'policy':policy['policy'],'objective':objective,
                            'calibration_trace':group['calibration'],'fit':export_fit(model),'raw_pairs':[{'candidate':c,'training_proxy':ratio(proxies[c]),'calibration_cost':ratio(mean_cost(group['calibration'],group['backend'],mode,c,objective))} for c in proxies]})
        save_json(output/'calibration-frozen.json',frozen);packet['calibration_frozen_sha256']=digest(output/'calibration-frozen.json');packet['calibration']=frozen;save()
        measure_role('evaluation')
        for group in groups:
            candidates=group['native']['candidates']
            for case in group['cases']:
                if case['role']!='evaluation':continue
                for mode in modes:
                    for policy in group['native']['policies']:
                        result={'query':group['query'],'backend':group['backend'],'trace':case['id'],'scenario':case['scenario'],'mode':mode,'policy':policy['policy'],
                            'native_choice_stop':policy['stop'],'search_quality':group['native']['search'],'objectives':{}}
                        if 'selected_index' not in policy:result['availability']='native_selection_unavailable';packet['analysis'].append(result);continue
                        proxies=primary_scores(policy,candidates);eligible={str(d['candidate']) for d in policy['decisions'] if d['eligibility'] in [0,1]};chosen=str(policy['selected_index'])
                        result['availability']='measured';result['selected_candidate']=chosen;result['effective_policy']=policy['effective_policy'];result['fallback_reasons']=policy['fallback_reasons']
                        for objective,unit in OBJECTIVES.items():
                            actual={str(c['index']):mean_cost(case['id'],group['backend'],mode,str(c['index']),objective) for c in candidates}
                            model=models[(group['query'],group['backend'],mode,policy['policy'],objective)];predictions={c:predict(model,proxies[c]) for c in eligible};order=sorted(eligible)
                            result['objectives'][objective]={'unit':unit,'runtime_regret':regret(actual,chosen,eligible),
                                'proxy_estimate_errors':error_summary([predictions[c] for c in order],[actual[c] for c in order]),
                                'proxy_ordering':ordering_quality({c:proxies[c] for c in eligible},{c:actual[c] for c in eligible}),
                                'held_out_predictions':[{'candidate':c,'training_proxy':ratio(proxies[c]),'calibrated_prediction':ratio(predictions[c]),'actual_measured_cost':ratio(actual[c])} for c in order],
                                'calibration_fit':export_fit(model),'qualification':'frozen_C05_choice_and_calibration_only_affine_mapping_evaluated_on_held_out_actual_costs'}
                        packet['analysis'].append(result)
        for label,values in sorted(samples.items()):
            totals=raw_totals[label];packet['summaries'].append({'label':label,'measured_runs':len(values),'mean_costs':{k:ratio(sum((v[k] for v in values),Fraction())/len(values)) for k in OBJECTIVES},
                'run_distributions':{k:distribution([v[k] for v in totals]) for k in totals[0]}})
        packet.update(status='complete',completed_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),commands_sha256=digest(output/'commands.json'));save()
        print(f'C07 held-out packet complete: {len(groups)} query/backend groups, {len(packet["verification"])} candidate preflights, {len(packet["runs"])} retained runs, {len(packet["analysis"])} held-out policy analyses; {output/"experiment.json"}')
    except Exception as error:
        packet.update(status='failed',error=str(error),completed_utc=datetime.datetime.now(datetime.timezone.utc).isoformat());save();raise
def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for name in ['source','build-dir','crown','collector','exporter','output']:parser.add_argument('--'+name,type=Path,required=True)
    parser.add_argument('--pack',type=Path);parser.add_argument('--query',action='append');parser.add_argument('--backend',action='append',choices=['reference_ordered_v1','indexed_chained_v1']);parser.add_argument('--mode',action='append',choices=['maintenance','snapshot','delta'])
    parser.add_argument('--repetitions',type=int,default=3);parser.add_argument('--warmups',type=int,default=1);parser.add_argument('--candidates',type=int,default=8);parser.add_argument('--require-exhausted-family',action='store_true');parser.add_argument('--slot-limit')
    parser.add_argument('--codec',choices=['none','jsonl'],default='none');parser.add_argument('--sink',choices=['discard','file'],default='discard');parser.add_argument('--cpu',type=int);parser.add_argument('--schedule-seed',type=int,default=20261111);parser.add_argument('--command-timeout',type=int,default=300);parser.add_argument('--max-total-bytes',type=int,default=1024*1024*1024)
    main_run(parser.parse_args())
if __name__=='__main__':
    try:main()
    except Exception as error:print('C07 held-out evaluation failed: '+str(error),file=sys.stderr);raise SystemExit(1)
