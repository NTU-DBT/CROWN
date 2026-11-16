#!/usr/bin/env python3
"""Moved installed public C05 exporter and candidate-proof consumer acceptance."""
from pathlib import Path
import argparse,hashlib,json,shutil,subprocess,sys,tempfile,warnings
import jsonschema
sys.dont_write_bytecode=True
def require(value,message):
    if not value:raise RuntimeError(message)
def key(value):return json.dumps(value,sort_keys=True,separators=(',',':'),ensure_ascii=False)
def main():
    parser=argparse.ArgumentParser();parser.add_argument('source');parser.add_argument('build');parser.add_argument('compiler');parser.add_argument('sanitize');parser.add_argument('artifacts',nargs='?');args=parser.parse_args()
    root=Path(args.source).resolve();build=Path(args.build).resolve();sys.path.insert(0,str(root/'tools'))
    from run_measurements import indexed_options
    temporary=None
    if args.artifacts:base=Path(args.artifacts).resolve();base.mkdir(parents=True,exist_ok=False)
    else:temporary=tempfile.TemporaryDirectory(prefix='crown-installed-ranking-');base=Path(temporary.name)
    commands=[]
    def run(command):
        index=len(commands);p=subprocess.run(list(map(str,command)),capture_output=True,text=True,timeout=300)
        stdout=base/f'{index}.stdout';stderr=base/f'{index}.stderr';stdout.write_text(p.stdout);stderr.write_text(p.stderr)
        commands.append({'arguments':list(map(str,command)),'exit_code':p.returncode,'stdout':stdout.name,'stdout_sha256':hashlib.sha256(stdout.read_bytes()).hexdigest(),'stderr':stderr.name,'stderr_sha256':hashlib.sha256(stderr.read_bytes()).hexdigest()})
        (base/'commands.json').write_text(json.dumps(commands,indent=2)+'\n');require(p.returncode==0,f'{command}: {p.stderr[-2500:]} {p.stdout[-1000:]}');return p
    stage=base/'stage';prefix=base/'relocated prefix';run(['cmake','--install',build,'--prefix',stage]);stage.rename(prefix)
    require(not stage.exists() and not list(prefix.rglob('*testing*.a')) and not list(prefix.rglob('libcrown_reference.a')),'moved public installation invalid')
    configs=list(prefix.rglob('CrownConfig.cmake'));require(len(configs)==1,'ambiguous package config');executables={}
    for example,target in [('ranking-evaluation','crown_export_ranking'),('workload-measurement','crown_measure_workload')]:
        source=base/(example+'-source');shutil.copytree(prefix/'share/crown/examples'/example,source);consumer=base/(example+'-build')
        command=['cmake','-S',source,'-B',consumer,'-DCMAKE_BUILD_TYPE=Release','-DCMAKE_CXX_COMPILER='+args.compiler,'-DCrown_DIR='+str(configs[0].parent),'-DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF','-DCMAKE_EXPORT_COMPILE_COMMANDS=ON']
        if args.sanitize.upper() in ['ON','TRUE','1','YES']:command+=['-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer']
        run(command);run(['cmake','--build',consumer,'--parallel','2']);entries=json.loads((consumer/'compile_commands.json').read_text());require(len(entries)==1,'unexpected installed example translation units')
        command=entries[0]['command']
        for flag in ['-std=c++23','-Wall','-Wextra','-Wpedantic','-Wconversion','-Wsign-conversion','-Werror']:require(flag in command,'example lost strict flag '+flag)
        for forbidden in [str(root/'include'),str(root/'third_party'),str(build)]:require(forbidden not in command,'public example used source/build headers')
        link=(consumer/'CMakeFiles'/(target+'.dir')/'link.txt').read_text();require('testing' not in link and 'libcrown_reference' not in link,'example linked test/reference ABI');executables[target]=consumer/target
    schemas=prefix/'share/crown/schemas';store={p.as_uri():json.loads(p.read_text()) for p in schemas.glob('*.json')}
    def validator(name):
        path=schemas/name;schema=json.loads(path.read_text())
        with warnings.catch_warnings():warnings.simplefilter('ignore',DeprecationWarning);resolver=jsonschema.RefResolver(base_uri=path.as_uri(),referrer=schema,store=store)
        return jsonschema.Draft202012Validator(schema,resolver=resolver)
    export_validator=validator('ranking-export-v1.schema.json');raw_validator=validator('workload-measurement-v2.schema.json')
    pack=root/'benchmarks/ranking';manifest=json.loads((pack/'manifest.json').read_text());cli=prefix/'bin/crown';cases=0
    for query in manifest['queries']:
        sql=pack/query['sql']['path'];catalog=pack/query['catalog']['path'];canonical=json.loads(run([cli,'canonicalize-catalog',catalog]).stdout);digest=hashlib.sha256(key(canonical).encode()).hexdigest()
        trace=next(t for t in manifest['traces'] if t['query']==query['id'] and t['role']=='train');events=[json.loads(line) for line in (pack/trace['events']['path']).read_text().splitlines()]
        for e in events:e['catalog_sha256']=digest
        bound=base/(query['id']+'.input.jsonl');bound.write_text(''.join(key(e)+'\n' for e in events));oracle=pack/trace['oracle']['path'];expected=json.loads(oracle.read_text())
        for backend in ['reference_ordered_v1','indexed_chained_v1']:
            options=indexed_options()
            if backend=='reference_ordered_v1':del options['indexed_storage'];options['schema_version']=1
            request={'schema_version':1,'physical_options':options,'candidate_limit':8,'search_work':10000000,'enumeration_work':10000000,'memory_limit_bytes':256*1024*1024,'max_events':4096,'require_exhausted_family':False,'fallback':'require_evidence','slot_limit':None}
            req=base/(query['id']+'-'+backend+'.export.request.json');req.write_text(key(request));export=json.loads(run([executables['crown_export_ranking'],sql,catalog,bound,req]).stdout);export_validator.validate(export)
            require(all('selected_index' in p for p in export['policies']),'installed public C05 policy unavailable')
            for candidate in export['candidates']:
                artifact=base/(query['id']+'-'+backend+f'-candidate-{candidate["index"]}.compiled.json');artifact.write_text(key(candidate['artifact']))
                for mode in ['maintenance','snapshot','delta']:
                    label=query['id']+'-'+backend+'-'+str(candidate['index'])+'-'+mode
                    request={'schema_version':1,'command':'verify','output_mode':mode,'codec':'none','sink':'discard','sink_delay_us':0,'observation':'counters','workload_counters':True,'memory_limit_bytes':256*1024*1024,'max_events':4096,'max_output_calls':1000000,'max_encoded_bytes':64*1024*1024,'phases':[e['phase'] for e in expected['epochs']],'label':label,'preflight_receipt_sha256':None}
                    req=base/(label+'.request.json');req.write_text(key(request));report=json.loads(run([executables['crown_measure_workload'],artifact,bound,req,oracle,base/'unused-sink']).stdout);raw_validator.validate(report)
                    require(report['verified'] and report['backend']==backend and report['output_mode']==mode,'installed candidate/current/delta verification differs');cases+=1
    print(f'C07 moved installed ranking PASS: {cases} independent candidate/mode checks, {len(commands)} commands; public C05 exporter/collector and strict C++23 moved-prefix builds.')
    if temporary is not None:temporary.cleanup()
if __name__=='__main__':
    try:main()
    except Exception as error:print(str(error),file=sys.stderr);raise SystemExit(1)
