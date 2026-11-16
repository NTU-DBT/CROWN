#!/usr/bin/env python3
"""Prepare a patch against the pinned excluded runtime overlay; never apply it."""
from pathlib import Path
import difflib,hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
BASE=HERE.parent/'o07-runtime-proposal/overlay'
for name,expected in json.loads((HERE/'baseline-sha256.json').read_text()).items():
 if hashlib.sha256((ROOT/name).read_bytes()).hexdigest()!=expected:raise SystemExit('baseline mismatch: '+name)
chunks=[];hashes={}
for path in sorted((HERE/'overlay').rglob('*')):
 if not path.is_file():continue
 relative=path.relative_to(HERE/'overlay').as_posix();original=BASE/relative
 assert original.is_file(),relative
 chunks.extend(difflib.unified_diff(original.read_text().splitlines(keepends=True),path.read_text().splitlines(keepends=True),
  fromfile='a/'+relative,tofile='b/'+relative))
 hashes[path.relative_to(HERE).as_posix()]=hashlib.sha256(path.read_bytes()).hexdigest()
(HERE/'mode-binding.patch').write_text(''.join(chunks))
(HERE/'overlay-sha256.json').write_text(json.dumps(hashes,indent=2)+'\n')
print(json.dumps({'changed_files':len(hashes),'patch_target':'pinned excluded o07-runtime-proposal overlay; not native sources','patch_applied':False}))
