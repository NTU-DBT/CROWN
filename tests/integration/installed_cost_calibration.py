#!/usr/bin/env python3
"""Build the moved installed calibration example and verify its SQL replay."""
from pathlib import Path
import argparse,json,shutil,subprocess,tempfile

def require(value,message):
    if not value:raise RuntimeError(message)
def run(command):
    result=subprocess.run([str(x) for x in command],capture_output=True,text=True,timeout=240)
    require(result.returncode==0,f'{command}: {result.stderr[-2500:]} {result.stdout[-2500:]}')
    return result
def main():
    parser=argparse.ArgumentParser();parser.add_argument('source');parser.add_argument('build');parser.add_argument('compiler');parser.add_argument('sanitize');args=parser.parse_args()
    root=Path(args.source).resolve();build=Path(args.build).resolve()
    with tempfile.TemporaryDirectory(prefix='crown-installed-calibration-') as temporary:
        base=Path(temporary);stage=base/'stage';prefix=base/'moved calibration prefix'
        run(['cmake','--install',build,'--prefix',stage]);stage.rename(prefix)
        require((prefix/'share/crown/schemas/cost-calibration-v1.schema.json').is_file(),'calibration schema not installed')
        source=base/'consumer';shutil.copytree(prefix/'share/crown/examples/cost-calibration',source)
        config=list(prefix.rglob('CrownConfig.cmake'));require(len(config)==1,'installed package config ambiguous')
        target=base/'outside-build';command=['cmake','-S',source,'-B',target,'-DCMAKE_BUILD_TYPE=Release','-DCMAKE_CXX_COMPILER='+args.compiler,'-DCrown_DIR='+str(config[0].parent),'-DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF']
        if args.sanitize.upper() in ['ON','TRUE','1','YES']:command+=['-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer']
        run(command);run(['cmake','--build',target,'-j2'])
        entries=json.loads((target/'compile_commands.json').read_text());require(len(entries)==1,'calibration example has unexpected native units')
        command=entries[0]['command'];require('-std=c++23' in command,'installed calibration example did not inherit C++23')
        for forbidden in [str(root/'include'),str(root/'third_party'),str(build)]:require(forbidden not in command,'installed example used original source/build headers')
        link=(target/'CMakeFiles/crown_cost_calibrate.dir/link.txt').read_text();require('testing' not in link and 'libcrown_reference' not in link,'calibration consumer used testing/reference archive')
        result=run(['python3',root/'tests/integration/cost_calibration.py',target/'crown_cost_calibrate',prefix/'bin/crown',root]);print(result.stdout,end='')
    print('C03 moved installed calibration API/example compiled and all five SQL/oracle/timing-report cases passed')
    return 0
if __name__=='__main__':
    try:raise SystemExit(main())
    except Exception as error:print(str(error));raise SystemExit(1)
