#!/usr/bin/env python3
"""Compile and link only in /tmp. Never execute the result or use CMake."""
from pathlib import Path
import argparse,hashlib,json,subprocess
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
RUNTIME=HERE.parent/'o07-runtime-proposal'
p=argparse.ArgumentParser();p.add_argument('output',type=Path)
p.add_argument('--runtime-archive',type=Path)
p.add_argument('--mode-binding',action='store_true')
args=p.parse_args();out=args.output.resolve()
if not out.is_relative_to(Path('/tmp')):p.error('output must be under /tmp')
dependency_file='baseline-dependencies-mode-binding.json' if args.mode_binding else 'baseline-dependencies.json'
for path,digest in json.loads((HERE/dependency_file).read_text())['inputs'].items():
 if hashlib.sha256((ROOT/path).read_bytes()).hexdigest()!=digest:raise SystemExit('dependency changed: '+path)
MODE=HERE.parent/'o07-mode-binding-proposal'
runtime_evidence=json.loads(((MODE/'compile-evidence-testing.json') if args.mode_binding else (RUNTIME/'compile-evidence.json')).read_text())
if args.runtime_archive is None:args.runtime_archive=Path(runtime_evidence['archive'])
if hashlib.sha256(args.runtime_archive.read_bytes()).hexdigest()!=runtime_evidence['archive_sha256']:
 raise SystemExit('runtime archive does not match frozen compile evidence')
out.mkdir(parents=True,exist_ok=True)
flags=['-std=c++23','-O0','-Wall','-Wextra','-Wpedantic','-Wconversion','-Wsign-conversion','-Werror','-DCROWN_RUNTIME_TESTING','-I',str(HERE/'overlay/include')]
if args.mode_binding:flags+=['-I',str(MODE/'overlay/include')]
flags+=['-I',str(RUNTIME/'overlay/include'),'-I',str(ROOT/'include'),'-isystem',str(ROOT/'third_party')]
commands=[];objects=[]
for source in ['src/observability/explain.cpp','src/io/explain.cpp','apps/crown-explain-proposal/main.cpp']:
 path=HERE/'overlay'/source;stem=source.replace('/','_').removesuffix('.cpp');obj=out/(stem+'.o')
 command=['/usr/bin/c++',*flags,'-MMD','-MF',str(out/(stem+'.d')),'-c',str(path),'-o',str(obj)]
 result=subprocess.run(command,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 (out/(stem+'.log')).write_text(result.stdout);commands.append({'source':source,'sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'command':command,'exit_code':result.returncode})
 if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
 objects.append(obj)
archives=[args.runtime_archive,ROOT/'build/release/libcrown_plan.a',ROOT/'build/release/libcrown_sql.a',ROOT/'build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a',ROOT/'build/release/libcrown_core.a']
output=out/'crown-explain-proposal'
command=['/usr/bin/c++',*(str(o) for o in objects),'-o',str(output),*(str(a) for a in archives)]
result=subprocess.run(command,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(out/'link.log').write_text(result.stdout)
commands.append({'command':command,'exit_code':result.returncode})
evidence={'kind':'compile/link only','mode_binding_api':args.mode_binding,'executed':False,'commands':commands,'archives':{str(a):hashlib.sha256(a.read_bytes()).hexdigest() for a in archives},'binary':str(output)}
(out/'build-evidence.json').write_text(json.dumps(evidence,indent=2)+'\n')
if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
evidence['binary_sha256']=hashlib.sha256(output.read_bytes()).hexdigest()
(out/'build-evidence.json').write_text(json.dumps(evidence,indent=2)+'\n')
(HERE/('compile-evidence-mode-binding.json' if args.mode_binding else 'compile-evidence.json')).write_text(json.dumps(evidence,indent=2)+'\n')
print(json.dumps({'compiled':3,'linked':str(output),'executed':False,'binary_sha256':evidence['binary_sha256']}))
