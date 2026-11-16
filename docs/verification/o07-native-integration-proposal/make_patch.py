#!/usr/bin/env python3
from pathlib import Path
import difflib,hashlib,json
H=Path(__file__).resolve().parent;R=H.parents[2];C=H.parent/'o07-composed-explain-proposal'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
for rel,digest in json.loads((H/'baseline-sha256.json').read_text()).items():
 if sha(R/rel)!=digest:raise SystemExit('baseline changed: '+rel)
old={rel:R/v['resolved_source'] for rel,v in json.loads((C/'source-map.json').read_text()).items()}
current={p.relative_to(H/'overlay').as_posix():p for p in (H/'overlay').rglob('*') if p.is_file()}
current.update({'schemas/'+p.name:p for p in (H/'schemas').glob('*.json')})
standalone='apps/crown-explain/main.cpp'
def patch(files,base):
 chunks=[]
 for rel,p in sorted(files.items()):
  previous=base.get(rel,R/rel);before=previous.read_text().splitlines(keepends=True) if previous.is_file() else []
  after=p.read_text().splitlines(keepends=True) if p else []
  chunks.extend(difflib.unified_diff(before,after,fromfile='a/'+rel if before else '/dev/null',tofile='b/'+rel if p else '/dev/null'))
 return ''.join(chunks)
(H/'native-integration-incremental.patch').write_text(patch({**current,standalone:None},old))
full={**old,**current};full.pop(standalone,None)
(H/'native-integration-complete.patch').write_text(patch(full,{}))
(H/'source-map.json').write_text(json.dumps({r:{'resolved_source':str(p.relative_to(R)),'sha256':sha(p),'native_baseline_sha256':sha(R/r) if (R/r).is_file() else None} for r,p in sorted(full.items())},indent=2)+'\n')
(H/'proposal-sha256.json').write_text(json.dumps({str(p.relative_to(H)):sha(p) for p in sorted(current.values())},indent=2)+'\n')
print(json.dumps({'native_paths':len(full),'schemas':[x for x in full if x.startswith('schemas/')],'applied':False}))
