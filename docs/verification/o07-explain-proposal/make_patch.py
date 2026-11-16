#!/usr/bin/env python3
"""Generate, never apply, the standalone new-source/schema proposal patch."""
from pathlib import Path
import difflib,hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
for path,digest in json.loads((HERE/'baseline-dependencies.json').read_text())['inputs'].items():
 assert hashlib.sha256((ROOT/path).read_bytes()).hexdigest()==digest,path
files={p.relative_to(HERE/'overlay').as_posix():p for p in (HERE/'overlay').rglob('*') if p.is_file()}
files['schemas/explain-report-v1.schema.json']=HERE/'schemas/explain-report-v1.schema.json'
parts=[]
for destination,path in sorted(files.items()):
 assert not (ROOT/destination).exists(),'new source path already exists: '+destination
 parts.extend(difflib.unified_diff([],path.read_text().splitlines(keepends=True),fromfile='/dev/null',tofile='b/'+destination))
(HERE/'o07-explain.patch').write_text(''.join(parts))
(HERE/'proposal-sha256.json').write_text(json.dumps({p.relative_to(HERE).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in files.values()},indent=2)+'\n')
print(json.dumps({'new_paths':len(files),'patch_lines':len(parts)}))
