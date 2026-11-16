#!/usr/bin/env python3
from pathlib import Path
import difflib,hashlib,json
H=Path(__file__).resolve().parent;R=H.parents[2];B=H.parent/'o07-runtime-proposal/overlay';M=H.parent/'o07-mode-binding-proposal/overlay'
for path,digest in json.loads((H/'baseline-sha256.json').read_text()).items():
 if hashlib.sha256((R/path).read_bytes()).hexdigest()!=digest:raise SystemExit('baseline mismatch: '+path)
chunks=[];hashes={};baseline={}
for p in sorted((H/'overlay').rglob('*')):
 if not p.is_file():continue
 rel=p.relative_to(H/'overlay').as_posix();old=next((x for x in [M/rel,B/rel,R/rel] if x.exists()),None)
 before=old.read_text().splitlines(keepends=True) if old else []
 chunks.extend(difflib.unified_diff(before,p.read_text().splitlines(keepends=True),fromfile='a/'+rel if old else '/dev/null',tofile='b/'+rel))
 hashes[p.relative_to(H).as_posix()]=hashlib.sha256(p.read_bytes()).hexdigest()
 baseline[rel]=None if old is None else {'path':str(old.relative_to(R)),'sha256':hashlib.sha256(old.read_bytes()).hexdigest()}
(H/'run-context.patch').write_text(''.join(chunks));(H/'overlay-sha256.json').write_text(json.dumps(hashes,indent=2)+'\n');(H/'patch-baselines.json').write_text(json.dumps(baseline,indent=2)+'\n')
print(json.dumps({'changed_paths':len(hashes),'patch_applied':False}))
