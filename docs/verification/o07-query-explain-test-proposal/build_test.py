#!/usr/bin/env python3
"""Compile/link only. Never execute the produced test or schema checker."""
from pathlib import Path
import argparse, hashlib, json, subprocess
H=Path(__file__).resolve().parent;R=H.parents[2];P=H.parent/'o07-query-explain-proposal'
p=argparse.ArgumentParser();p.add_argument('output',type=Path);p.add_argument('--opt',choices=['0','3'],default='0');a=p.parse_args();out=a.output.resolve()
if not out.is_relative_to(Path('/tmp')):p.error('output must be under /tmp')
def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()
ready=json.loads((P/'readiness.json').read_text())
if ready['package_sha256']!='1ee51f89955602fc2ff2a0aecce1c1728a4ba10d0981f0a4fb4b66ea58049802':raise SystemExit('wrong frozen report package')
pins={P/f:d for f,d in ready['files'].items()}
libs=[Path('/tmp/crown-o07-query-explain-o0/libcrown_query_explain_proposal.a'),R/'build/release/libcrown_reference.a',R/'build/release/libcrown_core.a']
pins.update(dict(zip(libs,['889e42c051bfb75413f1a8cb1bc7cde3c09a96d84341558dfbeef747250624fb','035a204d7e00355b7f14e94255f8d77688f43a5688aabba898f6cedfd43f39f5','784b820ff9284ad75033552056fd2a81113f7eb54be5db56959f31ce778bcf9d'])))
pins.update({R/f:digest(R/f) for f in ['tests/reference/tree_oracle.cpp','tests/reference/tree_oracle.hpp','src/planner/search_budget.hpp','CMakeLists.txt']})
def verify():
 for path,d in pins.items():
  if digest(path)!=d:raise SystemExit('frozen dependency changed: '+str(path))
verify();out.mkdir(parents=True,exist_ok=True);src=H/'query_explain_test.cpp';source_hash=digest(src);obj=out/'query_explain_test.o';dep=out/'query_explain_test.d';binary=out/'query-explain-test'
flags=['-std=c++23','-O'+a.opt,'-g','-Wall','-Wextra','-Wpedantic','-Wconversion','-Wsign-conversion','-Werror','-I',str(P/'overlay/include'),'-I',str(P/'fixtures'),'-I',str(R/'include'),'-I',str(R/'tests/reference'),'-isystem',str(R/'third_party')]
commands=[['/usr/bin/c++',*flags,'-MMD','-MF',str(dep),'-c',str(src),'-o',str(obj)],['/usr/bin/c++',str(obj),*(str(x) for x in libs),'-o',str(binary)]]
for i,cmd in enumerate(commands):
 result=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT);(out/f'{i}.log').write_text(result.stdout)
 if result.returncode:print(result.stdout);raise SystemExit(result.returncode)
verify()
if digest(src)!=source_hash:raise SystemExit('test changed during compilation')
deps={Path(x) for x in dep.read_text().replace('\\\n',' ').split(':',1)[1].split()}
evidence=dict(status='strict compile/link only; NO test or Python checker execution',optimization=a.opt,commands=commands,source_sha256=source_hash,binary=str(binary),binary_sha256=digest(binary),dependency_hashes={str(x):digest(x) for x in sorted(deps)},frozen_inputs={str(x):d for x,d in pins.items()},linked_archives={str(x):digest(x) for x in libs},runtime_archives_linked=False)
(out/'compile-evidence.json').write_text(json.dumps(evidence,indent=2)+'\n');print(json.dumps({k:v for k,v in evidence.items() if k not in ('commands','dependency_hashes','frozen_inputs')},indent=2))
