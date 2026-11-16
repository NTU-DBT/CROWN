#!/usr/bin/env python3
"""Strict new-unit compile/link against pinned native core only; no execution."""
from pathlib import Path
import argparse,hashlib,json,subprocess
H=Path(__file__).resolve().parent;R=H.parents[2]
p=argparse.ArgumentParser();p.add_argument('output',type=Path);p.add_argument('--opt',choices=['0','3'],default='0');args=p.parse_args();out=args.output.resolve()
if not out.is_relative_to(Path('/tmp')):p.error('output must be under /tmp')
pins=json.loads((H/'baseline-sha256.json').read_text())
def verify():
 for f,d in pins.items():
  if hashlib.sha256((R/f).read_bytes()).hexdigest()!=d:raise SystemExit('baseline changed: '+f)
verify();out.mkdir(parents=True,exist_ok=True)
paths=[H/'overlay/src/observability/query_explain.cpp',H/'overlay/src/io/query_explain.cpp',H/'compile/link_probe.cpp']
source_hashes={str(x):hashlib.sha256(x.read_bytes()).hexdigest() for x in paths}
flags=['-std=c++23','-O'+args.opt,'-Wall','-Wextra','-Wpedantic','-Wconversion','-Wsign-conversion','-Werror','-I',str(H/'overlay/include'),'-I',str(R/'include'),'-isystem',str(R/'third_party')]
commands=[];objects=[];deps=set()
for i,src in enumerate(paths):
 obj=out/(str(i)+'.o');dep=out/(str(i)+'.d');cmd=['/usr/bin/c++',*flags,'-MMD','-MF',str(dep),'-c',str(src),'-o',str(obj)]
 result=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(out/(str(i)+'.log')).write_text(result.stdout)
 commands.append({'source':str(src),'command':cmd,'exit_code':result.returncode});(out/'compile-results.json').write_text(json.dumps(commands,indent=2)+'\n')
 if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
 deps.update(Path(x) for x in dep.read_text().replace('\\\n',' ').split(':',1)[1].split());objects.append(obj)
core=R/'build/release/libcrown_core.a';binary=out/'query-explain-link-probe';cmd=['/usr/bin/c++',*(str(x) for x in objects),str(core),'-o',str(binary)]
result=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(out/'link.log').write_text(result.stdout);commands.append({'command':cmd,'exit_code':result.returncode})
if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
archive=out/'libcrown_query_explain_proposal.a';archive.unlink(missing_ok=True);subprocess.run(['/usr/bin/ar','rcs',str(archive),*(str(x) for x in objects[:2])],check=True)
verify()
for x,d in source_hashes.items():
 if hashlib.sha256(Path(x).read_bytes()).hexdigest()!=d:raise SystemExit('source changed during compile: '+x)
e={'kind':'compile/link only; no binary execution','optimization':args.opt,'new_translation_units':2,'consumer_translation_units':1,'commands':commands,'source_hashes':source_hashes,'compiler_dependencies':{str(x):hashlib.sha256(x.read_bytes()).hexdigest() for x in sorted(deps)},'reused_native_archive':str(core),'reused_native_archive_sha256':hashlib.sha256(core.read_bytes()).hexdigest(),'proposal_archive':str(archive),'proposal_archive_sha256':hashlib.sha256(archive.read_bytes()).hexdigest(),'binary':str(binary),'binary_sha256':hashlib.sha256(binary.read_bytes()).hexdigest(),'abi':'No native or runtime layout changes; depends only on unchanged planner/core interfaces. No physical-plan/runtime/SQL archive linked.'}
(out/'compile-evidence.json').write_text(json.dumps(e,indent=2)+'\n');print(json.dumps({k:v for k,v in e.items() if k not in ['commands','source_hashes','compiler_dependencies']}))
