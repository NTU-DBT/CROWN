#!/usr/bin/env python3
"""Direct compiler-only build in /tmp. Never configures CMake or runs tests."""
from pathlib import Path
import argparse,hashlib,json,subprocess,sys
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
parser=argparse.ArgumentParser()
parser.add_argument('output',type=Path)
parser.add_argument('--testing',action='store_true')
parser.add_argument('--compiler',default='/usr/bin/c++')
parser.add_argument('--opt',choices=['0','2','3'],default='0')
args=parser.parse_args()
out=args.output.resolve()
if not out.is_relative_to(Path('/tmp')):
 parser.error('output must be under /tmp; native build directories are forbidden')
for path,expected in json.loads((HERE/'baseline-sha256.json').read_text()).items():
 actual=hashlib.sha256((ROOT/path).read_bytes()).hexdigest()
 if actual!=expected:raise SystemExit('baseline mismatch: '+path)
out.mkdir(parents=True,exist_ok=True)
audit=json.loads((HERE/'abi-source-audit.json').read_text())
paths=audit['runtime_recompile']+[audit['new_runtime']]
flags=['-std=c++23','-Wall','-Wextra','-Wpedantic','-Wconversion','-Wsign-conversion','-Werror','-O'+args.opt,
 '-I',str(HERE/'overlay/include'),'-I',str(ROOT/'include'),'-I',str(ROOT/'src/runtime'),'-I',str(ROOT/'tests/support'),'-isystem',str(ROOT/'third_party')]
if args.testing:flags+=['-DCROWN_RUNTIME_TESTING']
rows=[];objects=[]
for path in paths:
 source=HERE/'overlay'/path
 if not source.exists():source=ROOT/path
 stem=path.replace('/','_').removesuffix('.cpp')
 obj=out/(stem+'.o');dep=out/(stem+'.d')
 command=[args.compiler,*flags,'-MMD','-MF',str(dep),'-c',str(source),'-o',str(obj)]
 result=subprocess.run(command,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
 (out/(stem+'.log')).write_text(result.stdout)
 rows.append({'source':path,'overlay':source.is_relative_to(HERE),'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'command':command,'exit_code':result.returncode})
 (out/'compile-results.json').write_text(json.dumps(rows,indent=2)+'\n')
 if result.returncode:
  print(result.stdout,file=sys.stderr);raise SystemExit(result.returncode)
 objects.append(str(obj))
archive=out/'libcrown_runtime_o07_overlay.a'
# Recreate the archive so stale objects cannot survive a source-list change.
archive.unlink(missing_ok=True)
subprocess.run(['/usr/bin/ar','rcs',str(archive),*objects],check=True)
print(json.dumps({'compiled':len(objects),'testing':args.testing,'archive':str(archive),'executed_tests':False}))
