#!/usr/bin/env python3
"""Inspect actual layered include closure; no compilation or execution."""
from pathlib import Path
import hashlib,json,re
H=Path(__file__).resolve().parent;R=H.parents[2]
roots=[H/'overlay',H.parent/'o07-mode-binding-proposal/overlay',H.parent/'o07-runtime-proposal/overlay',R]
pattern=re.compile(r'^\s*#\s*include\s*"([^"]+)"',re.M)
def resolve(logical):
 return next((root/logical for root in roots if (root/logical).is_file()),None)
def closure(logical):
 seen={};todo=[logical]
 while todo:
  rel=todo.pop()
  if rel in seen:continue
  path=resolve(rel)
  if path is None:continue
  seen[rel]=str(path.relative_to(R))
  for name in pattern.findall(path.read_text()):
   for child in [str(Path(rel).parent/name),'include/'+name,'src/runtime/'+name]:
    if resolve(child) is not None:todo.append(child);break
 return seen
old=json.loads((H.parent/'o07-runtime-proposal/abi-source-audit.json').read_text())
runtime=old['runtime_recompile']+[old['new_runtime']]
nonruntime=sorted({p.relative_to(R).as_posix() for p in (R/'src').rglob('*.cpp')}-set(runtime))
nonruntime+=sorted(p.relative_to(R).as_posix() for p in (R/'tests/reference').glob('*.cpp'))
changed={'include/crown/runtime/'+n+'.hpp' for n in ['observation','support','physical','delta','session']}
closures={s:closure(s) for s in nonruntime+runtime}
affected={s:sorted(changed.intersection(closures[s])) for s in nonruntime if changed.intersection(closures[s])}
if affected:raise SystemExit('nonruntime archive invalid: '+repr(affected))
inputs=set(p for v in closures.values() for p in v.values())
report={'runtime_recompile':runtime,'nonruntime_translation_units_checked':len(nonruntime),'nonruntime_changed_header_consumers':affected,'layered_quoted_include_closures':closures,'source_hashes':{p:hashlib.sha256((R/p).read_bytes()).hexdigest() for p in sorted(inputs)},'limits':'Quoted include analysis; compiler-generated dependencies retained separately. All runtime and all report/test/application consumers must rebuild.'}
(H/'abi-source-audit.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({'checked':len(nonruntime),'affected':affected,'runtime':len(runtime)}))
