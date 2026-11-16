#!/usr/bin/env python3
"""Compile/link native dispatcher adaptation only. Never run CMake or binaries."""
from pathlib import Path
import argparse,hashlib,json,subprocess
H=Path(__file__).resolve().parent;R=H.parents[2];V=H.parent;C=V/'o07-composed-explain-proposal'
p=argparse.ArgumentParser();p.add_argument('output',type=Path);p.add_argument('--configuration',choices=['testing','production'],required=True);a=p.parse_args();out=a.output.resolve()
if not out.is_relative_to(Path('/tmp')):p.error('output must be under /tmp')
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
base=json.loads((H/'baseline-sha256.json').read_text())
def verify():
 for rel,digest in base.items():
  if sha(R/rel)!=digest:raise SystemExit('baseline changed: '+rel)
verify();report=json.loads((C/('compile-evidence-report-'+a.configuration+'.json')).read_text());runtime=json.loads((C/('compile-evidence-runtime-'+a.configuration+'.json')).read_text())
for evidence in [report,runtime]:
 for path,digest in evidence['compiler_dependencies'].items():
  if sha(Path(path))!=digest:raise SystemExit('matched source drift: '+path)
for path,digest in report['archives'].items():
 if sha(Path(path))!=digest:raise SystemExit('matched library drift: '+path)
if sha(Path(report['binary']))!=report['binary_sha256']:raise SystemExit('matched prior linked evidence drift')
flags=['-std=c++23','-O'+runtime['optimization'],'-Wall','-Wextra','-Wpedantic','-Wconversion','-Wsign-conversion','-Werror']
if runtime['testing']:flags+=['-DCROWN_RUNTIME_TESTING']
for root in [H/'overlay',C/'overlay',V/'o07-cursor-observation-proposal/overlay',V/'o07-run-context-proposal/overlay',V/'o07-mode-binding-proposal/overlay',V/'o07-runtime-proposal/overlay',V/'o07-explain-proposal/overlay',V/'o07-query-explain-proposal/overlay',R]:flags+=['-I',str(root/'include')]
flags+=['-I',str(R/'tests/reference'),'-isystem',str(R/'third_party')]
out.mkdir(parents=True,exist_ok=True);rows=[];objects=[];dependencies=set()
for i,rel in enumerate(['apps/crown/main.cpp','apps/crown/explain.cpp','src/io/explain.cpp']):
 src=H/'overlay'/rel;obj=out/(str(i)+'.o');dep=out/(str(i)+'.d');cmd=['/usr/bin/c++',*flags,'-MMD','-MF',str(dep),'-c',str(src),'-o',str(obj)]
 result=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(out/(str(i)+'.log')).write_text(result.stdout)
 rows.append({'source':str(src),'command':cmd,'exit_code':result.returncode});(out/'compile-results.json').write_text(json.dumps(rows,indent=2)+'\n')
 if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
 dependencies.update(Path(x) for x in dep.read_text().replace('\\\n',' ').split(':',1)[1].split());objects.append(obj)
prior=Path(report['binary']).parent
# The old standalone main (6.o) is deliberately absent; final IO (1.o) is replaced.
reused=[prior/(str(i)+'.o') for i in [0,2,3,4,5]]
archives=[R/'build/release/libcrown_reference.a',Path(runtime['archive']),R/'build/release/libcrown_plan.a',R/'build/release/libcrown_sql.a',R/'build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a',R/'build/release/libcrown_core.a']
binary=out/'crown';cmd=['/usr/bin/c++',*(str(x) for x in objects+reused),'-o',str(binary),*(str(x) for x in archives),'-pthread']
result=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(out/'link.log').write_text(result.stdout);rows.append({'command':cmd,'exit_code':result.returncode})
if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
verify()
e={'kind':'strict direct compiler/linker only; no CMake, binary or test execution','configuration':a.configuration,'commands':rows,'binary':str(binary),'binary_sha256':sha(binary),'new_objects':{str(x):sha(x) for x in objects},'reused_matched_report_objects':{str(x):sha(x) for x in reused},'archives':{str(x):sha(x) for x in archives},'compiler_dependencies':{str(x):sha(x) for x in sorted(dependencies)},'matched_report_evidence':str(C/('compile-evidence-report-'+a.configuration+'.json')),'matched_runtime_evidence':str(C/('compile-evidence-runtime-'+a.configuration+'.json'))}
(out/'compile-evidence.json').write_text(json.dumps(e,indent=2)+'\n');print(json.dumps({k:e[k] for k in ['configuration','binary','binary_sha256']}))
