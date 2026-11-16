from pathlib import Path
import json,hashlib,difflib
H=Path(__file__).resolve().parent;R=H.parents[2]
for f,d in json.loads((H/'baseline-sha256.json').read_text()).items():
 if hashlib.sha256((R/f).read_bytes()).hexdigest()!=d:raise SystemExit('baseline changed: '+f)
chunks=[];hashes={}
for p in sorted((H/'overlay').rglob('*')):
 if p.is_file():
  rel=p.relative_to(H/'overlay').as_posix();assert not (R/rel).exists(),rel
  chunks.extend(difflib.unified_diff([],p.read_text().splitlines(keepends=True),fromfile='/dev/null',tofile='b/'+rel));hashes[p.relative_to(H).as_posix()]=hashlib.sha256(p.read_bytes()).hexdigest()
for p in sorted((H/'schemas').glob('*.json')):
 rel='schemas/'+p.name;assert not (R/rel).exists(),rel
 chunks.extend(difflib.unified_diff([],p.read_text().splitlines(keepends=True),fromfile='/dev/null',tofile='b/'+rel));hashes[rel]=hashlib.sha256(p.read_bytes()).hexdigest()
(H/'query-explain.patch').write_text(''.join(chunks));(H/'proposal-sha256.json').write_text(json.dumps(hashes,indent=2)+'\n')
print(json.dumps({'new_native_paths_proposed':len(hashes),'patch_applied':False}))
