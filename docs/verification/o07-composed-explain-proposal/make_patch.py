#!/usr/bin/env python3
"""Emit incremental and complete composed native-source patches; never apply."""
from pathlib import Path
import difflib,hashlib,json
H=Path(__file__).resolve().parent;R=H.parents[2];V=H.parent
layers=[V/(n+'/overlay') for n in ['o07-runtime-proposal','o07-mode-binding-proposal','o07-explain-proposal','o07-run-context-proposal','o07-cursor-observation-proposal','o07-query-explain-proposal']]
for rel,digest in json.loads((H/'baseline-sha256.json').read_text()).items():
 if hashlib.sha256((R/rel).read_bytes()).hexdigest()!=digest:raise SystemExit('baseline changed: '+rel)
prior={}
for layer in layers:
 for p in layer.rglob('*'):
  if p.is_file():prior[p.relative_to(layer).as_posix()]=p
current={p.relative_to(H/'overlay').as_posix():p for p in (H/'overlay').rglob('*') if p.is_file()}
current.update({'schemas/'+p.name:p for p in (H/'schemas').glob('*.json')})
def patch(files,base):
 chunks=[]
 for rel,p in sorted(files.items()):
  previous=base.get(rel,R/rel);before=previous.read_text().splitlines(keepends=True) if previous.is_file() else []
  chunks.extend(difflib.unified_diff(before,p.read_text().splitlines(keepends=True),fromfile='a/'+rel if before else '/dev/null',tofile='b/'+rel))
 return ''.join(chunks)
(H/'composed-incremental.patch').write_text(patch(current,prior))
full={**prior,**current};full={r:p for r,p in full.items() if not r.startswith('apps/crown-explain-proposal/')}
(H/'composed-native.patch').write_text(patch(full,{}))
(H/'source-map.json').write_text(json.dumps({r:{'resolved_source':str(p.relative_to(R)),'sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'native_baseline_sha256':hashlib.sha256((R/r).read_bytes()).hexdigest() if (R/r).is_file() else None} for r,p in sorted(full.items())},indent=2)+'\n')
(H/'proposal-sha256.json').write_text(json.dumps({str(p.relative_to(H)):hashlib.sha256(p.read_bytes()).hexdigest() for p in sorted(current.values())},indent=2)+'\n')
print(json.dumps({'incremental_paths':len(current),'composed_native_paths':len(full),'patches_applied':False}))
