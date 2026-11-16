#!/usr/bin/env python3
"""Independent split, freeze, raw-cost and held-out regret acceptance for C07."""
from pathlib import Path
from fractions import Fraction
import collections,copy,hashlib,json,math,subprocess,sys,tempfile,warnings
import jsonschema
sys.dont_write_bytecode=True
def require(value,message):
    if not value:raise RuntimeError(message)
def fraction(value):return Fraction(int(value['numerator']),int(value['denominator']))
def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def main():
    require(len(sys.argv) in [6,7],'usage: ranking_evaluation.py CROWN EXPORTER COLLECTOR SOURCE BUILD [ARTIFACT_DIRECTORY]')
    crown,exporter,collector,source,build=map(lambda x:Path(x).resolve(),sys.argv[1:6]);sys.path.insert(0,str(source/'tools'))
    from ranking_analysis import fit_proxy,predict,regret,error_summary,ordering_quality
    model=fit_proxy([(0,3),(1,5),(2,7)]);require((model['intercept'],model['slope'],predict(model,3))==(3,2,9),'literal affine fit differs')
    require(fit_proxy([(2,5),(2,7)])['slope'] is None,'constant proxy invented an identified slope')
    require(fit_proxy([(0,8),(1,4)])['slope']==0,'nonnegative fit admitted negative slope')
    require(fraction(regret({'0':5,'1':3},'0')['absolute_regret'])==2,'literal regret differs')
    require(regret({'0':1,'1':0},'0')['relative_regret'] is None,'zero optimum got a fake relative regret')
    require(fraction(error_summary([2,4],[1,5])['mean_absolute_error'])==1,'literal proxy error differs')
    require(ordering_quality({'0':1,'1':2},{'0':2,'1':1})['discordant']==1,'literal ordering differs')
    temporary=None
    if len(sys.argv)==7:base=Path(sys.argv[6]).resolve();base.mkdir(parents=True,exist_ok=False)
    else:temporary=tempfile.TemporaryDirectory(prefix='crown-heldout-');base=Path(temporary.name)
    calls=0
    def invoke(args,success=True):
        nonlocal calls
        result=subprocess.run(list(map(str,args)),capture_output=True,text=True,timeout=1800);calls+=1
        require((result.returncode==0)==success,f'{args}: {result.stderr[-2500:]} {result.stdout[-500:]}');return result
    directory=source/'schemas';store={p.as_uri():json.loads(p.read_text()) for p in directory.glob('*.json')}
    def validator(name):
        p=directory/name;schema=json.loads(p.read_text());jsonschema.Draft202012Validator.check_schema(schema)
        with warnings.catch_warnings():
            warnings.simplefilter('ignore',DeprecationWarning);resolver=jsonschema.RefResolver(base_uri=p.as_uri(),referrer=schema,store=store)
        return jsonschema.Draft202012Validator(schema,resolver=resolver)
    packet_validator=validator('ranking-evaluation-v1.schema.json');export_validator=validator('ranking-export-v1.schema.json');raw_validator=validator('workload-measurement-v2.schema.json')
    manifest=json.loads((source/'benchmarks/ranking/manifest.json').read_text());validator('ranking-trace-split-v1.schema.json').validate(manifest)
    for query in manifest['queries']:
        seen=set()
        for case in [t for t in manifest['traces'] if t['query']==query['id']]:
            records=[json.loads(line) for line in (source/'benchmarks/ranking'/case['events']['path']).read_text().splitlines()]
            rows={(e['table'],tuple(e['values'])) for e in records};require(not(rows&seen),'held-out split shares physical tuples');seen.update(rows)
    output=base/'controlled';invoke([sys.executable,source/'tools/run_ranking_evaluation.py','--source',source,'--build-dir',build,'--crown',crown,'--collector',collector,'--exporter',exporter,
        '--repetitions',2,'--warmups',1,'--codec','jsonl','--sink','file','--output',output])
    packet=json.loads((output/'experiment.json').read_text());packet_validator.validate(packet);commands=json.loads((output/'commands.json').read_text())
    require(packet['status']=='complete' and len(packet['exports'])==6,'full query/backend groups missing')
    require(sha(output/'commands.json')==packet['commands_sha256'] and sha(output/'choices-frozen.json')==packet['choices_frozen_sha256'] and sha(output/'calibration-frozen.json')==packet['calibration_frozen_sha256'],'command/choice/calibration provenance differs')
    first_timed=min(c['index'] for c in commands if c['label'].startswith(('calibration_','evaluation_')))
    require(max(v['command'] for v in packet['verification'])<first_timed,'a candidate was timed before complete correctness preflight')
    first_eval=min(c['index'] for c in commands if c['label'].startswith('evaluation_'));last_cal=max(c['index'] for c in commands if c['label'].startswith('calibration_'))
    require(last_cal<first_eval,'evaluation started before calibration measurements finished')
    native={};candidate_total=0
    for entry in packet['exports']:
        report=json.loads((output/entry['raw_report']).read_text());export_validator.validate(report);require(sha(output/entry['raw_report'])==entry['raw_report_sha256'],'export hash differs');candidate_total+=len(report['candidates'])
        require(report['search']['family_exhausted'],'default finite candidate family did not finish')
        if entry['query'] in ['boolean_path','full_star_3']:require(len(report['candidates'])>=2,'ranking family became a single-plan timing check')
        require(report['training']['denominator']==report['training_events'],'training census horizon differs')
        native[(entry['query'],entry['backend'])]=report
    require(len(packet['verification'])==candidate_total*5*3,'candidate/trace/mode preflight matrix incomplete')
    require(len(packet['runs'])==candidate_total*4*3*3 and len(packet['analysis'])==3*2*3*3*3,'measured/held-out matrix incomplete')
    measured=collections.defaultdict(list);by_label=collections.defaultdict(list)
    for run in packet['runs']:
        report=json.loads((output/run['raw_report']).read_text());raw_validator.validate(report);require(sha(output/run['raw_report'])==run['raw_report_sha256'],'raw measurement hash differs')
        epochs=report['epochs'];count=len(epochs);active=Fraction(sum(e['event_active_ns'] for e in epochs),count)
        maintenance=Fraction(sum(e['native_prepare_commit_ns']+e['epoch_release_ns'] for e in epochs),count)
        peak=Fraction(max(report['memory_initial']['peak_requested_bytes'],report['memory_final']['peak_requested_bytes'],*(e['memory']['peak_requested_bytes'] for e in epochs)))
        costs={'event_active_ns_per_input':active,'native_prepare_and_epoch_release_ns_per_input':maintenance,'native_peak_requested_bytes':peak}
        require(all(fraction(run['costs'][k])==v for k,v in costs.items()),'reported costs differ from actual raw frames')
        if not run['warmup']:
            q,scenario,backend,candidate,mode=run['label'].split('/');measured[(q,backend,q+'/'+scenario,mode,candidate)].append(costs);by_label[run['label']].append(costs)
    for summary in packet['summaries']:
        require(summary['measured_runs']==2 and len(by_label[summary['label']])==2,'warmups were counted or measured repeats omitted')
        for objective,value in summary['mean_costs'].items():require(fraction(value)==sum((r[objective] for r in by_label[summary['label']]),Fraction())/2,'summary mean does not trace to raw frames')
    objectives_checked=0
    for analysis in packet['analysis']:
        require(analysis['availability']=='measured','default native policy unavailable')
        key=(analysis['query'],analysis['backend']);report=native[key];policy=next(p for p in report['policies'] if p['policy']==analysis['policy'])
        chosen=str(policy['selected_index']);require(chosen==analysis['selected_candidate'],'held-out timing changed native C05 choice')
        for objective,result in analysis['objectives'].items():
            costs={str(c['index']):sum((v[objective] for v in measured[(*key,analysis['trace'],analysis['mode'],str(c['index']))]),Fraction())/2 for c in report['candidates']}
            minimum=min(costs.values());reg=result['runtime_regret'];require(fraction(reg['best_measured_feasible_cost'])==minimum and fraction(reg['absolute_regret'])==costs[chosen]-minimum,'regret was not computed against independently measured candidates')
            require(set(reg['best_measured_feasible'])=={c for c,v in costs.items() if v==minimum},'actual best-candidate set differs')
            predictions=result['held_out_predictions'];intercept=fraction(result['calibration_fit']['intercept']);slope=fraction(result['calibration_fit']['slope']) if result['calibration_fit']['slope'] is not None else 0
            errors=[]
            for p in predictions:
                require(fraction(p['actual_measured_cost'])==costs[p['candidate']],'proxy error used model score as ground truth')
                predicted=intercept+slope*fraction(p['training_proxy']);require(fraction(p['calibrated_prediction'])==predicted,'held-out prediction differs from frozen calibration');errors.append(predicted-costs[p['candidate']])
            require(fraction(result['proxy_estimate_errors']['mean_absolute_error'])==sum(map(abs,errors))/len(errors),'held-out mean absolute error differs')
            require(fraction(result['proxy_estimate_errors']['mean_squared_error'])==sum(e*e for e in errors)/len(errors),'held-out squared error differs')
            if analysis['policy']=='height_only':require(result['calibration_fit']['slope'] is None and result['calibration_fit']['design_rank']==1,'equal heights acquired an identified time coefficient')
            objectives_checked+=1
    export_command=next(c for c in commands if c['label']=='training_and_native_C05_export');argv=export_command['arguments'];request=json.loads(Path(argv[4]).read_text())
    request['slot_limit']='0';req=base/'zero-slot.request.json';req.write_text(json.dumps(request));none=json.loads(invoke([exporter,*argv[1:4],req]).stdout);export_validator.validate(none)
    require(all('selected_index' not in p and p['stop']!=0 for p in none['policies']),'mandatory slot cap was ignored')
    request['schema_version']=True;req=base/'bool-version.request.json';req.write_text(json.dumps(request));require(not invoke([exporter,*argv[1:4],req],False).stdout,'malformed exporter request emitted a report')
    verify_command=next(c for c in commands if c['label']=='preflight_candidate_verification');argv=verify_command['arguments'];artifact=json.loads(Path(argv[1]).read_text());artifact['height_binding']='unverified';bad=base/'bad-binding.json';bad.write_text(json.dumps(artifact))
    require(not invoke([collector,bad,*argv[2:]],False).stdout,'unknown candidate proof binding emitted a report')
    artifact=json.loads(Path(argv[1]).read_text());artifact['height_certificate']['minimum_height']+=1;bad=base/'bad-proof.json';bad.write_text(json.dumps(artifact))
    require(not invoke([collector,bad,*argv[2:]],False).stdout,'corrupted lower-bound proof was trusted')
    mutated=copy.deepcopy(packet);mutated['unknown_extension']=True;require(not packet_validator.is_valid(mutated),'packet schema accepts unknown fields')
    print(f'C07 held-out acceptance PASS: {candidate_total} checked candidates across six query/backend groups; {len(packet["verification"])} preflights/{len(packet["runs"])} retained runs; {len(packet["analysis"])} analyses/{objectives_checked} independent regret/error checks; {calls} protocol commands; all splits, choices and calibration frozen.')
    if temporary is not None:temporary.cleanup()
if __name__=='__main__':
    try:main()
    except Exception as error:print(str(error),file=sys.stderr);raise SystemExit(1)
