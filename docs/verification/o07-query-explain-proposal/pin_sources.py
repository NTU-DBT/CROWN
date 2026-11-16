from pathlib import Path
import hashlib,json,re
H=Path(__file__).resolve().parent;R=H.parents[2]
items=['include/crown/planner/search.hpp','include/crown/planner/oracle.hpp','include/crown/ir/model.hpp','include/crown/ir/tree.hpp','include/crown/ir/scalar.hpp','src/planner/search_session.cpp','src/planner/continuation_internal.hpp','src/io/search.cpp','src/io/query_binding.hpp','CMakeLists.txt','build/release/libcrown_core.a']
items=[x for x in items if (R/x).is_file()]
for source in ['docs/verification/o07-explain-proposal/overlay/src/io/explain.cpp','docs/verification/o07-explain-proposal/readiness.json','docs/verification/o07-run-context-proposal/readiness.json','docs/verification/o07-cursor-observation-proposal/readiness.json']:
 items.append(source)
# Native quoted include closure; new units expose no changed native ABI.
pattern=re.compile(r'^\s*#\s*include\s*"([^"]+)"',re.M);todo=[p for p in items if p.endswith(('.cpp','.hpp'))];seen=set(items)
while todo:
 rel=todo.pop();path=R/rel
 for name in pattern.findall(path.read_text()):
  for candidate in [path.parent/name,R/'include'/name]:
   if candidate.is_file():
    child=candidate.resolve().relative_to(R).as_posix()
    if child not in seen:seen.add(child);todo.append(child)
    break
(H/'baseline-sha256.json').write_text(json.dumps({p:hashlib.sha256((R/p).read_bytes()).hexdigest() for p in sorted(seen)},indent=2)+'\n')
