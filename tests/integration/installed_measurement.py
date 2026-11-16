#!/usr/bin/env python3
"""Build the moved installed collector example and check independent SQL traces."""
from pathlib import Path
import argparse,hashlib,json,shutil,subprocess,sys,tempfile
import jsonschema

def require(value,message):
    if not value:raise RuntimeError(message)
def key(value):return json.dumps(value,sort_keys=True,separators=(',',':'),ensure_ascii=False)
def main():
    parser=argparse.ArgumentParser();parser.add_argument('source');parser.add_argument('build');parser.add_argument('compiler');parser.add_argument('sanitize');parser.add_argument('artifacts',nargs='?');args=parser.parse_args()
    root=Path(args.source).resolve();build=Path(args.build).resolve();sys.path.insert(0,str(root/'tools'))
    from run_measurements import indexed_options
    temporary=None
    if args.artifacts:base=Path(args.artifacts).resolve();base.mkdir(parents=True,exist_ok=False)
    else:temporary=tempfile.TemporaryDirectory(prefix='crown-installed-measurement-');base=Path(temporary.name)
    records=[]
    def run(command):
        index=len(records);result=subprocess.run(list(map(str,command)),capture_output=True,text=True,timeout=240)
        stdout=base/f'{index}.stdout';stderr=base/f'{index}.stderr';stdout.write_text(result.stdout);stderr.write_text(result.stderr)
        records.append({'arguments':list(map(str,command)),'exit_code':result.returncode,'stdout':stdout.name,'stdout_sha256':hashlib.sha256(stdout.read_bytes()).hexdigest(),'stderr':stderr.name,'stderr_sha256':hashlib.sha256(stderr.read_bytes()).hexdigest()})
        (base/'commands.json').write_text(json.dumps(records,indent=2)+'\n')
        require(result.returncode==0,f'{command}: {result.stderr[-2500:]} {result.stdout[-1500:]}');return result
    stage=base/'stage';prefix=base/'relocated prefix';run(['cmake','--install',build,'--prefix',stage]);stage.rename(prefix)
    require(not stage.exists(),'original install prefix still exists')
    require(not list(prefix.rglob('*testing*.a')) and not list(prefix.rglob('libcrown_reference.a')),'test archive installed')
    configs=list(prefix.rglob('CrownConfig.cmake'));require(len(configs)==1,'ambiguous installed package')
    source=base/'outside-source';shutil.copytree(prefix/'share/crown/examples/workload-measurement',source);consumer=base/'outside-build'
    command=['cmake','-S',source,'-B',consumer,'-DCMAKE_BUILD_TYPE=Release','-DCMAKE_CXX_COMPILER='+args.compiler,'-DCrown_DIR='+str(configs[0].parent),'-DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF','-DCMAKE_EXPORT_COMPILE_COMMANDS=ON']
    if args.sanitize.upper() in ['ON','TRUE','1','YES']:command+=['-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer']
    run(command);run(['cmake','--build',consumer,'--parallel','2'])
    commands=json.loads((consumer/'compile_commands.json').read_text());require(len(commands)==1,'unexpected consumer translation units');command=commands[0]['command']
    for flag in ['-std=c++23','-Wall','-Wextra','-Wpedantic','-Wconversion','-Wsign-conversion','-Werror']:require(flag in command,'public example lost strict C++ flag '+flag)
    for forbidden in [str(root/'include'),str(root/'third_party'),str(build)]:require(forbidden not in command,'consumer used source/build headers')
    link=(consumer/'CMakeFiles/crown_measure_workload.dir/link.txt').read_text();require('testing' not in link and 'libcrown_reference' not in link,'consumer linked test/reference ABI')
    schema_path=prefix/'share/crown/schemas/workload-measurement-v2.schema.json';validator=jsonschema.Draft202012Validator(json.loads(schema_path.read_text()))
    options=base/'indexed-options.json';options.write_text(key(indexed_options()));collector=consumer/'crown_measure_workload';cli=prefix/'bin/crown';configurations=0
    fixture=root/'benchmarks/workloads';manifest=json.loads((fixture/'manifest.json').read_text());queries={q['id']:q for q in manifest['queries']};workloads={w['id']:w for w in manifest['workloads']}
    for name in ['composite_separator','boolean_path']:
        query=queries[name];case=workloads[name+'/mixed'];catalog=fixture/query['catalog']['path'];sql=fixture/query['sql']['path']
        canonical=json.loads(run([cli,'canonicalize-catalog',catalog]).stdout);digest=hashlib.sha256(key(canonical).encode()).hexdigest()
        events=[json.loads(line) for line in (fixture/case['events']['path']).read_text().splitlines()]
        for event in events:event['catalog_sha256']=digest
        updates=base/(name+'.input.jsonl');updates.write_text(''.join(key(event)+'\n' for event in events));expected_path=fixture/case['oracle']['path'];expected=json.loads(expected_path.read_text())
        for backend in ['reference_ordered_v1','indexed_chained_v1']:
            compile_command=[cli,'compile',sql,catalog]
            if backend=='indexed_chained_v1':compile_command+=['--physical-options',options]
            plan=base/(name+'-'+backend+'.compiled.json');plan.write_text(run(compile_command).stdout)
            for mode in ['maintenance','snapshot','delta']:
                label=name+'-'+backend+'-'+mode
                request={'schema_version':1,'command':'verify','output_mode':mode,'codec':'jsonl','sink':'file','sink_delay_us':0,'observation':'counters','workload_counters':True,'memory_limit_bytes':256*1024*1024,'max_events':4096,'max_output_calls':1000000,'max_encoded_bytes':64*1024*1024,'phases':[e['phase'] for e in expected['epochs']],'label':label,'preflight_receipt_sha256':None}
                req=base/(label+'.verify.json');req.write_text(key(request));verified=run([collector,plan,updates,req,expected_path,base/'unused-verification-sink']);validator.validate(json.loads(verified.stdout));require(json.loads(verified.stdout)['verified'],'installed collector did not verify oracle')
                request.update(command='measure',preflight_receipt_sha256=hashlib.sha256(verified.stdout.encode()).hexdigest());req=base/(label+'.measure.json');req.write_text(key(request));sink=base/(label+'.sink')
                report=json.loads(run([collector,plan,updates,req,'-',sink]).stdout);validator.validate(report)
                require(report['backend']==backend and report['output_mode']==mode and report['runtime_mode']==('delta' if mode=='delta' else 'maintenance'),'installed collector mislabeled execution')
                actual=[json.loads(line) for line in sink.read_text().splitlines()];wanted=[]
                for event in expected['epochs']:
                    if mode=='snapshot':wanted.extend({'sequence':event['sequence'],'values':row} for row in event['current_rows'])
                    elif mode=='delta':wanted.extend({'sequence':event['sequence'],**row} for row in event['signed_delta'])
                require(sorted(map(key,actual))==sorted(map(key,wanted)),'installed encoded rows differ from independent oracle');configurations+=1
    print(f'B03 moved installed collector PASS: {configurations} SQL/backend/mode cases, {len(records)} commands; strict public-only build and independent encoded rows.')
    if temporary is not None:temporary.cleanup()
if __name__=='__main__':
    try:main()
    except Exception as error:print(str(error),file=sys.stderr);raise SystemExit(1)
