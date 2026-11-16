#!/usr/bin/env python3
"""Read-only source/ABI audit for this excluded proposal; no build or execution."""
from pathlib import Path
import hashlib,json,re

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
RUNTIME=[
 'src/runtime/support.cpp','src/runtime/physical.cpp','src/runtime/delta.cpp',
 'src/io/support.cpp','src/io/inspection.cpp','src/runtime/replay.cpp',
 'src/runtime/session.cpp','src/runtime/window.cpp',
]
CHANGED=[f'{prefix}/runtime/{name}.{suffix}' for prefix,suffix in [('include/crown','hpp'),('src','cpp')] for name in ['support','physical','delta','session']]
EXTRA=['src/io/batch.cpp','include/crown/io/batch.hpp','include/crown/runtime/window.hpp',
 'include/crown/runtime/replay.hpp','include/crown/io/support.hpp','include/crown/io/inspection.hpp','CMakeLists.txt']
pattern=re.compile(r'^\s*#\s*include\s*"([^"]+)"',re.M)
def closure(source):
 seen=set();todo=[source]
 while todo:
  item=todo.pop()
  if item in seen:continue
  seen.add(item);path=ROOT/item
  for name in pattern.findall(path.read_text()):
   for candidate in [path.parent/name,ROOT/'include'/name]:
    if candidate.is_file():
     child=candidate.resolve().relative_to(ROOT).as_posix()
     if child not in seen:todo.append(child)
     break
 return sorted(seen)
nonruntime=sorted({p.relative_to(ROOT).as_posix() for p in (ROOT/'src').rglob('*.cpp')} - set(RUNTIME))
nonruntime+=sorted(p.relative_to(ROOT).as_posix() for p in (ROOT/'tests/reference').glob('*.cpp'))
changed_headers=set(p for p in CHANGED if p.endswith('.hpp'))
reach={source:sorted(changed_headers.intersection(closure(source))) for source in nonruntime}
reach={k:v for k,v in reach.items() if v}
assert not reach, 'Non-runtime changed-ABI consumers require recompilation: '+repr(reach)
closures={p:closure(p) for p in RUNTIME+['src/io/batch.cpp']}
pinned=sorted(set(CHANGED+EXTRA).union(*(set(v) for v in closures.values())))
report={'runtime_recompile':RUNTIME,'new_runtime':'src/runtime/observation.cpp',
 'changed_public_headers':sorted(changed_headers),'nonruntime_translation_units_checked':len(nonruntime),
 'nonruntime_changed_header_consumers':reach,'quoted_project_include_closures':closures,
 'limits':'Static quoted-project-include closure; compiler dependency checks accompany object compilation. No native runtime object may be linked.'}
(HERE/'abi-source-audit.json').write_text(json.dumps(report,indent=2)+'\n')
(HERE/'baseline-sha256.json').write_text(json.dumps({p:hashlib.sha256((ROOT/p).read_bytes()).hexdigest() for p in pinned},indent=2)+'\n')
print(json.dumps({'pinned_originals':len(pinned),'nonruntime_translation_units_checked':len(nonruntime),'changed_header_consumers':reach}))
