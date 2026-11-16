#!/usr/bin/env python3
"""Generate a baseline-checked source patch; does not apply it."""
from pathlib import Path
import difflib,hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
baseline=json.loads((HERE/'baseline-sha256.json').read_text())
chunks=[]
for modified in sorted((HERE/'overlay').rglob('*')):
 if not modified.is_file():continue
 path=modified.relative_to(HERE/'overlay').as_posix()
 original=ROOT/path
 if original.exists():
  assert path in baseline and hashlib.sha256(original.read_bytes()).hexdigest()==baseline[path],path
  before=original.read_text().splitlines(keepends=True);label='a/'+path
 else:before=[];label='/dev/null'
 chunks.extend(difflib.unified_diff(before,modified.read_text().splitlines(keepends=True),fromfile=label,tofile='b/'+path))
(HERE/'o07-runtime-observation.patch').write_text(''.join(chunks))
(HERE/'overlay-sha256.json').write_text(json.dumps({p.relative_to(HERE).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in sorted((HERE/'overlay').rglob('*')) if p.is_file()},indent=2)+'\n')
print(json.dumps({'overlay_files':len(json.loads((HERE/'overlay-sha256.json').read_text())),'patch_lines':len(chunks)}))
