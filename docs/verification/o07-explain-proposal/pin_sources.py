#!/usr/bin/env python3
"""Record the excluded source dependency baseline. Does not build/run/apply."""
from pathlib import Path
import argparse,hashlib,json,re
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
RUNTIME=HERE.parent/'o07-runtime-proposal'
parser=argparse.ArgumentParser();parser.add_argument('--mode-binding',action='store_true');args=parser.parse_args()
MODE=HERE.parent/'o07-mode-binding-proposal'
SOURCES=['src/observability/explain.cpp','src/io/explain.cpp','apps/crown-explain-proposal/main.cpp']
roots=[HERE/'overlay/include']+([MODE/'overlay/include'] if args.mode_binding else [])+[RUNTIME/'overlay/include',ROOT/'include']
pattern=re.compile(r'^\s*#\s*include\s*"([^"]+)"',re.M)
def closure(start):
 seen=set();todo=[start]
 while todo:
  path=todo.pop().resolve()
  if path in seen:continue
  seen.add(path)
  for name in pattern.findall(path.read_text()):
   for candidate in [path.parent/name]+[root/name for root in roots]:
    if candidate.is_file():todo.append(candidate);break
 return seen
closures={s:closure(HERE/'overlay'/s) for s in SOURCES}
all_paths=set().union(*closures.values())|{ROOT/'CMakeLists.txt',ROOT/'src/planner/candidates.cpp',ROOT/'src/io/physical.cpp',ROOT/'src/io/search.cpp',ROOT/'src/ir/model.cpp',ROOT/'src/frontend/bind.cpp',ROOT/'third_party/nlohmann/json.hpp'}
files={str(path.relative_to(ROOT)):hashlib.sha256(path.read_bytes()).hexdigest() for path in sorted(all_paths)}
report={'source_closure':{s:sorted(str(p.relative_to(ROOT)) for p in c) for s,c in closures.items()},'inputs':files,'notes':'Quoted project includes, explicit native behavior dependencies; no baseline refresh authorizes source edits.'}
(HERE/('baseline-dependencies-mode-binding.json' if args.mode_binding else 'baseline-dependencies.json')).write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({'pinned_inputs':len(files),'sources':len(SOURCES)}))
