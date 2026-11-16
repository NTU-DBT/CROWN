#!/usr/bin/env python3
"""Install, move the prefix, compile a public consumer, and resume its native state."""
from pathlib import Path
import argparse,hashlib,json,shutil,subprocess,tempfile

def require(value,message):
    if not value:raise RuntimeError(message)
def key(value):return json.dumps(value,ensure_ascii=False,sort_keys=True,separators=(',',':'))
def main():
    parser=argparse.ArgumentParser();parser.add_argument('source');parser.add_argument('build');parser.add_argument('compiler');parser.add_argument('sanitize');args=parser.parse_args()
    root=Path(args.source).resolve();build=Path(args.build).resolve();records=[]
    def run(command):
        result=subprocess.run([str(x) for x in command],capture_output=True,text=True,timeout=240)
        records.append({'command':[str(x) for x in command],'exit_code':result.returncode})
        require(result.returncode==0,f'{command}: {result.stderr[-2500:]} {result.stdout[-2500:]}')
        return result
    with tempfile.TemporaryDirectory(prefix='crown-installed-workflow-') as temporary:
        base=Path(temporary);stage=base/'stage';prefix=base/'relocated prefix'
        run(['cmake','--install',build,'--prefix',stage]);stage.rename(prefix)
        require(not stage.exists(),'original prefix still exists')
        require(not list(prefix.rglob('*testing*.a')) and not list(prefix.rglob('libcrown_reference.a')),'testing/reference archive installed')
        require((prefix/'include/crown/version.hpp').is_file() and (prefix/'include/nlohmann/json.hpp').is_file(),'installed public headers missing')
        configs=list(prefix.rglob('CrownConfig.cmake'));require(len(configs)==1,'installed package config ambiguous')
        source=base/'outside-source';shutil.copytree(prefix/'share/crown/examples/native-workflow',source)
        consumer=base/'outside-build';command=['cmake','-S',source,'-B',consumer,'-DCMAKE_BUILD_TYPE=Release','-DCMAKE_CXX_COMPILER='+args.compiler,'-DCrown_DIR='+str(configs[0].parent),'-DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF']
        if args.sanitize.upper() in ['ON','TRUE','1','YES']:command+=['-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer']
        run(command);run(['cmake','--build',consumer,'-j2'])
        compile_commands=json.loads((consumer/'compile_commands.json').read_text());require(len(compile_commands)==1,'unexpected consumer units')
        command=compile_commands[0]['command'];require('-std=c++23' in command,'C++23 not inherited')
        for forbidden in [str(root/'include'),str(root/'third_party'),str(build)]:require(forbidden not in command,'consumer used source/build headers')
        link=(consumer/'CMakeFiles/crown_native_workflow.dir/link.txt').read_text();require('testing' not in link and 'libcrown_reference' not in link,'consumer linked test/reference ABI')
        manifest=json.loads((root/'tests/workflow/manifest.json').read_text())
        for name,case in manifest['cases'].items():
            directory=base/name;directory.mkdir();fixture=root/'tests/workflow';catalog=fixture/case['catalog'];sql=fixture/case['query']
            canonical=json.loads(run([prefix/'bin/crown','canonicalize-catalog',catalog]).stdout)
            digest=hashlib.sha256(key(canonical).encode()).hexdigest();events=[json.loads(line) for line in (fixture/case['events_template_jsonl']).read_text().splitlines()]
            for event in events:event['catalog_sha256']=digest
            updates=directory/'input.jsonl';updates.write_text(''.join(key(event)+'\n' for event in events))
            expected=json.loads((fixture/case['expected_oracle']).read_text())['events'];exe=consumer/'crown_native_workflow';state=directory/'state.root';sink=directory/'results.sink'
            first=json.loads(run([exe,'run',sql,catalog,updates,state,sink,2]).stdout)
            require(first['public_api_version']==1 and first['sequence']==first['verified_output_sequence']==2,'installed API initial epoch differs')
            require(len(first['rows'])==len(expected[1]['current_rows']) and {key(x) for x in first['rows']}=={key(x) for x in expected[1]['current_rows']},'installed API initial state differs from oracle')
            continued=json.loads(run([exe,'restore',sql,catalog,updates,state,sink,1]).stdout)
            require(continued['sequence']==continued['verified_output_sequence']==3,'installed API restart lost/duplicated input')
            require(len(continued['rows'])==len(expected[2]['current_rows']) and {key(x) for x in continued['rows']}=={key(x) for x in expected[2]['current_rows']},'installed API next state differs from oracle')
            require(continued['source_positions']=={case['source_id']:case['source_offsets'][2]},'installed API source differs')
            print('installed workflow',name,'SQL/public API/checkpoint/new-process restore/oracle passed')
        require((prefix/'share/crown/schemas/compiled-workflow-v1.schema.json').is_file(),'workflow schema not installed')
        require(list((prefix/'share/crown/licenses').rglob('LICENSE*')),'vendor notices missing')
    print('O08 moved install and public consumer passed;',len(records),'commands; no source/test/reference dependency')
    return 0
if __name__=='__main__':
    try:raise SystemExit(main())
    except Exception as error:print(str(error));raise SystemExit(1)
