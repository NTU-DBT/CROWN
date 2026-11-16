#!/usr/bin/env python3
"""Compile complete isolated cursor-observation runtime; no native build or execution."""
from pathlib import Path
import argparse,hashlib,json,subprocess,sys
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
BASE=HERE.parent/'o07-runtime-proposal'
MODE=HERE.parent/'o07-mode-binding-proposal'
CONTEXT=HERE.parent/'o07-run-context-proposal'
parser=argparse.ArgumentParser()
parser.add_argument('output',type=Path)
parser.add_argument('--testing',action='store_true')
parser.add_argument('--compiler',default='/usr/bin/c++')
parser.add_argument('--opt',choices=['0','2','3'],default='0')
args=parser.parse_args();out=args.output.resolve()
if not out.is_relative_to(Path('/tmp')):parser.error('output must be under /tmp')
pins=json.loads((HERE/'baseline-sha256.json').read_text())
def verify():
 for path,expected in pins.items():
  if hashlib.sha256((ROOT/path).read_bytes()).hexdigest()!=expected:raise SystemExit('baseline mismatch: '+path)
verify();out.mkdir(parents=True,exist_ok=True)
audit=json.loads((HERE/'abi-source-audit.json').read_text())
for path,digest in audit['source_hashes'].items():
 if hashlib.sha256((ROOT/path).read_bytes()).hexdigest()!=digest:raise SystemExit('ABI audit input changed: '+path)
paths=audit['runtime_recompile']
flags=['-std=c++23','-Wall','-Wextra','-Wpedantic','-Wconversion','-Wsign-conversion','-Werror','-O'+args.opt,
 '-I',str(HERE/'overlay/include'),'-I',str(CONTEXT/'overlay/include'),'-I',str(MODE/'overlay/include'),'-I',str(BASE/'overlay/include'),'-I',str(ROOT/'include'),
 '-I',str(ROOT/'src/runtime'),'-I',str(ROOT/'tests/support'),'-isystem',str(ROOT/'third_party')]
if args.testing:flags+=['-DCROWN_RUNTIME_TESTING']
rows=[];objects=[];dependencies=set()
for path in paths:
 source=next(p for p in [HERE/'overlay'/path,CONTEXT/'overlay'/path,MODE/'overlay'/path,BASE/'overlay'/path,ROOT/path] if p.is_file())
 stem=path.replace('/','_').removesuffix('.cpp');obj=out/(stem+'.o');dep=out/(stem+'.d')
 command=[args.compiler,*flags,'-MMD','-MF',str(dep),'-c',str(source),'-o',str(obj)]
 result=subprocess.run(command,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 (out/(stem+'.log')).write_text(result.stdout)
 rows.append({'source':path,'resolved_source':str(source),'sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'command':command,'exit_code':result.returncode})
 (out/'compile-results.json').write_text(json.dumps(rows,indent=2)+'\n')
 if result.returncode:print(result.stdout,file=sys.stderr);raise SystemExit(result.returncode)
 dependency_text=dep.read_text().replace('\\\n',' ')
 dependencies.update(Path(p) for p in dependency_text.split(':',1)[1].split())
 objects.append(str(obj))
verify()
for path,digest in audit['source_hashes'].items():
 if hashlib.sha256((ROOT/path).read_bytes()).hexdigest()!=digest:raise SystemExit('ABI audit input changed during compilation: '+path)
archive=out/'libcrown_runtime_o07_cursor_observation.a';archive.unlink(missing_ok=True)
subprocess.run(['/usr/bin/ar','rcs',str(archive),*objects],check=True)
report={'runtime_translation_units':len(objects),'testing':args.testing,'optimization':args.opt,'archive':str(archive),
 'archive_sha256':hashlib.sha256(archive.read_bytes()).hexdigest(),'executed_tests':False,
 'compile_results':rows,'compiler_dependencies':{str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in sorted(dependencies)},
 'abi_rule':'All runtime units and every consumer must rebuild against new observation header; no older runtime archive may be linked.',
 'baseline_nonruntime_audit':audit['nonruntime_translation_units_checked']}
(out/'compile-evidence.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({k:v for k,v in report.items() if k not in ['compile_results','compiler_dependencies']}))
