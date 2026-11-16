#!/usr/bin/env python3
"""Independent oracle/protocol and controlled-runner acceptance for B03."""
from pathlib import Path
import copy,hashlib,json,os,subprocess,sys,tempfile
import jsonschema

sys.dont_write_bytecode=True
def require(value,message):
    if not value:raise RuntimeError(message)
def main():
    require(len(sys.argv) in [5,6],'usage: measurement_harness.py CROWN COLLECTOR SOURCE BUILD [ARTIFACT_DIRECTORY]')
    crown,collector,source,build=map(lambda x:Path(x).resolve(),sys.argv[1:5]);sys.path.insert(0,str(source/'tools'))
    from run_measurements import Experiment,distribution
    schema=json.loads((source/'schemas/workload-measurement-v2.schema.json').read_text());validator=jsonschema.Draft202012Validator(schema)
    jsonschema.Draft202012Validator.check_schema(schema)
    packet_schema=json.loads((source/'schemas/measurement-experiment-v1.schema.json').read_text());packet_validator=jsonschema.Draft202012Validator(packet_schema)
    jsonschema.Draft202012Validator.check_schema(packet_schema)
    literal=distribution([0,1,2,8,16]);require((literal['p50'],literal['p95'],literal['p99'],literal['sum'])==(2,16,16,27),'literal quantiles differ')
    require([b['count'] for b in literal['histogram']]==[1,1,1,1,1] and distribution([])['p50'] is None,'empty/binned distribution differs')
    temporary=None
    if len(sys.argv)==6:
        base=Path(sys.argv[5]).resolve();base.mkdir(parents=True,exist_ok=False)
    else:
        temporary=tempfile.TemporaryDirectory(prefix='crown-measurement-');base=Path(temporary.name)
    checks=0
    def invoke(args,success=True):
        nonlocal checks
        result=subprocess.run([str(x) for x in args],capture_output=True,text=True,timeout=600)
        require((result.returncode==0)==success,f'{args}: {result.stderr[-2000:]}');checks+=1;return result
    runner=[sys.executable,source/'tools/run_measurements.py','--source',source,'--crown',crown,'--collector',collector,'--build-dir',build]
    output=base/'controlled-file'
    invoke([*runner,'--output',output,'--case','self_join_2/adversarial_churn','--case','hidden_witnesses/delete_after_charged_load',
            '--repetitions',2,'--warmups',1,'--codec','jsonl','--sink','file'])
    packet=json.loads((output/'experiment.json').read_text());commands=json.loads((output/'commands.json').read_text())
    packet_validator.validate(packet)
    require(packet['build']['compiled_dependencies'] and packet['build']['harness_sources'], 'compiled headers or harness sources were not bound')
    require(any(name.endswith('/crown/runtime/delta.hpp') for name in packet['build']['compiled_dependencies']), 'runtime header absent from build provenance')
    require(packet['build']['harness_sources']['tools/run_measurements.py']==hashlib.sha256((source/'tools/run_measurements.py').read_bytes()).hexdigest(), 'runner source binding differs')
    require(packet['status']=='complete' and packet['correctness_gate']=='passed_all_configurations_before_warmup_or_measurement','wrong packet/gate status')
    require(len(packet['verification'])==12 and len(packet['runs'])==36 and len(packet['summaries'])==12,'runner skipped a mode/backend/repetition')
    require({row['label'].rsplit('/',1)[-1] for row in packet['verification']}=={'maintenance','snapshot','delta'},'output mode labels collapsed')
    last_verify=max(row['command'] for row in packet['verification']);first_timing=min(row['index'] for row in commands if row['label'] in ['compile_warmup','compile_measured','warmup','measure'])
    require(last_verify<first_timing,'timing preceded complete correctness gate')
    require(hashlib.sha256((output/'commands.json').read_bytes()).hexdigest()==packet['commands_sha256'],'command provenance mismatch')
    label_to_reports={}
    for entry in packet['runs']:
        path=output/entry['raw_report'];report=json.loads(path.read_text());validator.validate(report)
        require(hashlib.sha256(path.read_bytes()).hexdigest()==entry['raw_report_sha256'],'raw measurement hash differs')
        require(report['runtime_mode']==('delta' if report['output_mode']=='delta' else 'maintenance'),'actual runtime mislabelled')
        for event in report['epochs']:
            parts=['decode_ns','native_prepare_commit_ns','output_setup_ns','output_next_ns','encoding_ns','sink_write_wait_ns','output_release_ns','epoch_release_ns','input_ack_ns']
            require(sum(event[k] for k in parts)<=event['event_active_ns'],'timing phases overlap')
            require(event['memory']['peak_requested_bytes']>=event['memory']['current_requested_bytes'],'invalid cumulative memory peak')
            require(sum(call['returned_row'] for call in event['output_calls'])==event['output_rows'],'output/call census differs')
        if not entry['warmup']:label_to_reports.setdefault(entry['label'],[]).append(report)
    for summary in packet['summaries']:
        reports=label_to_reports[summary['label']];values=[e['event_active_ns'] for r in reports for e in r['epochs']]
        stat=summary['update_latency_ns'];require(stat['samples']==len(values) and stat['sum']==sum(values),'warmups included or raw latency totals differ')
        require(sum(bin['count'] for bin in stat['histogram'])==len(values),'histogram loses samples')
        require(all(bin['count']==sum(bin['lower_inclusive']<=v<=bin['upper_inclusive'] for v in values) for bin in stat['histogram']),'histogram memberships differ')
        require('charged_load' in summary['phases'],'loading was silently omitted')
    require(all(v['process_wall_ns']['samples']==2 for v in packet['compilation_summaries']),'compile warmups were not excluded')
    verify_command=commands[packet['verification'][0]['command']];argv=verify_command['arguments'];oracle=json.loads(Path(argv[4]).read_text());oracle['initial_rows']=[['deliberately_wrong']]
    wrong=base/'wrong-oracle.json';wrong.write_text(json.dumps(oracle));bad_sink=base/'bad-verify-sink'
    failed=invoke([collector,argv[1],argv[2],argv[3],wrong,bad_sink],False)
    require(not failed.stdout and not bad_sink.exists(),'failed correctness verification emitted a measurement or sink')
    request=json.loads(Path(argv[3]).read_text());request['schema_version']=True;bad_request=base/'bad-request.json';bad_request.write_text(json.dumps(request))
    require(not invoke([collector,argv[1],argv[2],bad_request,argv[4],bad_sink],False).stdout,'invalid request emitted partial output')
    for field,limit in [('max_encoded_bytes',0),('max_output_calls',1),('memory_limit_bytes',1),('max_events',0)]:
        request=json.loads(Path(argv[3]).read_text());request.update(command='measure',output_mode='snapshot');request[field]=limit
        limited=base/(field+'.request.json');limited.write_text(json.dumps(request));limited_sink=base/(field+'.sink')
        failed=invoke([collector,argv[1],argv[2],limited,'-',limited_sink],False)
        require(not failed.stdout,'resource failure emitted a successful/partial measurement')
        if field=='max_encoded_bytes':require(limited_sink.stat().st_size==0,'encoded-byte limit was enforced after writing')
    cpu=min(os.sched_getaffinity(0));off=base/'off-discard'
    invoke([*runner,'--output',off,'--case','boolean_path/mixed','--backend','reference_ordered_v1','--mode','snapshot','--mode','delta',
            '--repetitions',1,'--warmups',0,'--codec','none','--sink','discard','--sink-delay-us',100,'--observe','off','--no-workload-counters','--cpu',cpu])
    second=json.loads((off/'experiment.json').read_text())
    packet_validator.validate(second)
    for entry in second['runs']:
        report=json.loads((off/entry['raw_report']).read_text());validator.validate(report)
        require(report['environment']['actual_affinity']==[cpu] and report['environment']['actual_threads']==1,'requested execution placement not actual')
        require(report['workload']['mode']=='off' and report['sink']['bytes']==0,'disabled workload/codec misreported')
        require(all(e['encoding_ns']==0 for e in report['epochs']),'none codec performed hidden encoding')
        require(all(m['availability']=='disabled' for e in report['epochs'] for m in e['operator_metrics'].values()),'disabled optional observations became measured zeros')
        require(sum(e['sink_write_wait_ns'] for e in report['epochs'])>=report['output_rows']*100000,'requested sink wait was not included')
    timeout_dir=base/'timeout';timeout_dir.mkdir();experiment=Experiment(timeout_dir,None,1,1024*1024)
    try:experiment.invoke('owned_timeout',[sys.executable,'-c','import time; time.sleep(5)'])
    except TimeoutError:pass
    else:raise RuntimeError('owned child timeout not enforced')
    require(len(experiment.commands)==1 and experiment.commands[0]['timed_out'],'timeout lost its raw command/failure record')
    rss_dir=base/'rss-isolation';rss_dir.mkdir();rss=Experiment(rss_dir,cpu,30,1024*1024)
    _,before_rss=rss.invoke('rss_before',[sys.executable,'-c','print("{}")'])
    parent_buffer=bytearray(64*1024*1024)
    _,after_rss=rss.invoke('rss_after',[sys.executable,'-c','print("{}")'])
    require(after_rss['process_maxrss_KiB']-before_rss['process_maxrss_KiB']<32*1024,'target RSS inherited the parent report buffer')
    require(after_rss['launcher_maxrss_KiB']>after_rss['process_maxrss_KiB'],'launcher and target RSS scopes collapsed')
    del parent_buffer
    mutated=copy.deepcopy(json.loads((output/packet['runs'][0]['raw_report']).read_text()));mutated['unknown_extension']=True
    require(not validator.is_valid(mutated),'measurement schema accepted unknown fields')
    print(f'B03 measurement harness PASS: {checks} top-level wrapper checks plus an owned timeout and two RSS probes;12 mode/backend cases x3 retained runs;independent rows, correctness gate,raw distributions,load accounting,placement,disabled metrics,wait/failure records and target RSS isolation.')
    if temporary is not None:temporary.cleanup()
if __name__=='__main__':
    try:main()
    except Exception as error:print(str(error),file=sys.stderr);raise SystemExit(1)
