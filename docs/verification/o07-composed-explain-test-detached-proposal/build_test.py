#!/usr/bin/env python3
"""Strict isolated compiler/linker only. Never executes an acceptance binary."""
from pathlib import Path
import argparse,hashlib,json,subprocess
H=Path(__file__).resolve().parent
p=argparse.ArgumentParser();p.add_argument('output',type=Path);p.add_argument('--optimization',choices=['0','3'],required=True);p.add_argument('--repo-root',type=Path,default=H.parents[2]);a=p.parse_args();R=a.repo_root.resolve();P=R/'docs/verification/o07-composed-explain-proposal'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
ready=json.loads((P/'readiness.json').read_text())
assert ready['package_sha256']=='a4e759965fea2efcb3578080f0445d80579bb6f0daf1a5c36ea4149c6310f30a'
pins={str(P/k):v for k,v in ready['files'].items()}
pins.update({str(R/k):v for k,v in json.loads((P/'baseline-sha256.json').read_text()).items()})
for x in ready['artifacts'].values():
 name=x.get('archive',x.get('binary'));pins[name]=x.get('archive_sha256',x.get('binary_sha256'))
old=R/'docs/verification/o07-composed-explain-test-proposal'
prior=json.loads((old/'readiness.json').read_text());assert prior['package_sha256']=='43d0cfd99fc93769d996b3e284e66bfaeb02d40d5aa12cd9223850b54a8d26e7'
pins.update({str(old/k):v for k,v in prior['files'].items()});pins[str(old/'readiness.json')]='27a27db7c49a2e983ecb1eca5a2e13067dc4ece6cb4cb26f287592c018024adc'
def verify():
 for k,v in pins.items():
  if sha(Path(k))!=v:raise SystemExit('pin changed: '+k)
verify()
out=a.output.resolve();assert out.is_relative_to(Path('/tmp'));out.mkdir(parents=True,exist_ok=True)
flags=['-std=c++23','-O'+a.optimization,'-g','-Wall','-Wextra','-Wpedantic','-Wconversion','-Wsign-conversion','-Werror','-DCROWN_RUNTIME_TESTING']
for name in ['o07-composed-explain-proposal','o07-cursor-observation-proposal','o07-run-context-proposal','o07-mode-binding-proposal','o07-runtime-proposal','o07-explain-proposal','o07-query-explain-proposal']:flags+=['-I',str(R/'docs/verification'/name/'overlay/include')]
flags+=['-I',str(R/'include'),'-I',str(R/'tests/reference'),'-isystem',str(R/'third_party')]
obj=out/'test.o';dep=out/'test.d';source=H/'composed_test.cpp'
cmd=['/usr/bin/c++',*flags,'-MMD','-MF',str(dep),'-c',str(source),'-o',str(obj)]
result=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(out/'compile.log').write_text(result.stdout)
if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
objects=[Path('/tmp/crown-o07-composed-report-testing')/(str(i)+'.o') for i in range(6)]
archives=[Path(ready['artifacts']['runtime_testing']['archive']),R/'build/release/libcrown_plan.a',R/'build/release/libcrown_sql.a',R/'build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a',R/'build/release/libcrown_reference.a',R/'build/release/libcrown_core.a']
binary=out/'composed-test';link=['/usr/bin/c++',str(obj),*(str(x) for x in objects),'-o',str(binary),*(str(x) for x in archives)]
result=subprocess.run(link,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(out/'link.log').write_text(result.stdout)
if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
verify();deps={Path(x) for x in dep.read_text().replace('\\\n',' ').split(':',1)[1].split()}
e={'status':'compiler/linker only; no binary or checker execution','optimization':a.optimization,'testing':True,'binary':str(binary),'binary_sha256':sha(binary),'source_sha256':sha(source),'commands':[cmd,link],'frozen_pins':pins,'link_inputs':{str(x):sha(x) for x in objects+archives},'compiler_dependencies':{str(x):sha(x) for x in sorted(deps)}}
(out/'compile-evidence.json').write_text(json.dumps(e,indent=2)+'\n');print(json.dumps({k:v for k,v in e.items() if k not in ['commands','frozen_pins','link_inputs','compiler_dependencies']}))
