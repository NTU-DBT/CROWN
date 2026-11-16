#!/usr/bin/env python3
"""Compile/link report closure against matching complete runtime. Never execute."""
from pathlib import Path
import argparse,hashlib,json,subprocess
H=Path(__file__).resolve().parent;R=H.parents[2];B=H.parent/'o07-runtime-proposal';M=H.parent/'o07-mode-binding-proposal';E=H.parent/'o07-explain-proposal';C=H.parent/'o07-run-context-proposal'
p=argparse.ArgumentParser();p.add_argument('output',type=Path);p.add_argument('--runtime-evidence',type=Path,required=True);args=p.parse_args();out=args.output.resolve()
if not out.is_relative_to(Path('/tmp')):p.error('output must be under /tmp')
for path,digest in json.loads((H/'baseline-sha256.json').read_text()).items():
 if hashlib.sha256((R/path).read_bytes()).hexdigest()!=digest:raise SystemExit('baseline mismatch: '+path)
e=json.loads(args.runtime_evidence.read_text());a=Path(e['archive'])
if hashlib.sha256(a.read_bytes()).hexdigest()!=e['archive_sha256']:raise SystemExit('runtime archive mismatch')
out.mkdir(parents=True,exist_ok=True)
flags=['-std=c++23','-O'+e['optimization'],'-Wall','-Wextra','-Wpedantic','-Wconversion','-Wsign-conversion','-Werror']
if e['testing']:flags+=['-DCROWN_RUNTIME_TESTING']
for d in [H/'overlay/include',C/'overlay/include',M/'overlay/include',B/'overlay/include',E/'overlay/include',R/'include']:flags+=['-I',str(d)]
flags+=['-isystem',str(R/'third_party')]
paths=[H/'overlay/src/io/cursor_observation.cpp',C/'overlay/src/io/run_context.cpp',E/'overlay/src/observability/explain.cpp',E/'overlay/src/io/explain.cpp',E/'overlay/apps/crown-explain-proposal/main.cpp']
rows=[];objects=[];deps=set()
for i,src in enumerate(paths):
 obj=out/(str(i)+'.o');dep=out/(str(i)+'.d');cmd=['/usr/bin/c++',*flags,'-MMD','-MF',str(dep),'-c',str(src),'-o',str(obj)]
 result=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(out/(str(i)+'.log')).write_text(result.stdout)
 rows.append({'source':str(src),'command':cmd,'exit_code':result.returncode});(out/'compile-results.json').write_text(json.dumps(rows,indent=2)+'\n')
 if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
 deps.update(Path(x) for x in dep.read_text().replace('\\\n',' ').split(':',1)[1].split());objects.append(obj)
archives=[a,R/'build/release/libcrown_plan.a',R/'build/release/libcrown_sql.a',R/'build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a',R/'build/release/libcrown_core.a']
bin=out/'crown-explain-cursor-observation-proposal';cmd=['/usr/bin/c++',*(str(x) for x in objects),'-o',str(bin),*(str(x) for x in archives)]
result=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(out/'link.log').write_text(result.stdout)
rows.append({'command':cmd,'exit_code':result.returncode})
if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
report={'kind':'compiler/linker only; no binary execution','testing':e['testing'],'optimization':e['optimization'],'binary':str(bin),'binary_sha256':hashlib.sha256(bin.read_bytes()).hexdigest(),'commands':rows,'archives':{str(x):hashlib.sha256(x.read_bytes()).hexdigest() for x in archives},'compiler_dependencies':{str(x):hashlib.sha256(x.read_bytes()).hexdigest() for x in sorted(deps)}}
(out/'compile-evidence.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps({k:v for k,v in report.items() if k not in ['commands','archives','compiler_dependencies']}))
