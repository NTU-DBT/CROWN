#!/usr/bin/env python3
"""Pin compiler-only artifacts and check frozen inputs; no target execution."""
from pathlib import Path
import hashlib,json,shutil
H=Path(__file__).resolve().parent;R=H.parents[2]
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
base=json.loads((H/'baseline-sha256.json').read_text())
for name in ['o07-runtime-proposal','o07-mode-binding-proposal','o07-explain-proposal','o07-run-context-proposal','o07-cursor-observation-proposal','o07-query-explain-proposal']:
 p=H.parent/name
 ready=p/'readiness.json'
 if ready.is_file():
  base[str(ready.relative_to(R))]=sha(ready)
  manifest=json.loads(ready.read_text())
  for rel,digest in manifest.get('files',{}).items():
   full=p/rel
   if sha(full)!=digest:raise SystemExit('prior package drift: '+str(full))
   base[str(full.relative_to(R))]=digest
 for schema in (p/'schemas').glob('*.json'):base[str(schema.relative_to(R))]=sha(schema)
for rel in ['Refactor.md','CMakeLists.txt']:
 base.setdefault(rel,sha(R/rel))
for rel,digest in base.items():
 if sha(R/rel)!=digest:raise SystemExit('baseline mismatch: '+rel)
(H/'baseline-sha256.json').write_text(json.dumps(dict(sorted(base.items())),indent=2)+'\n')
evidences={}
for kind in ['runtime','report']:
 for config in ['testing','production']:
  src=Path('/tmp')/('crown-o07-composed-'+kind+'-'+config)/'compile-evidence.json'
  e=json.loads(src.read_text())
  for path,digest in e['compiler_dependencies'].items():
   if sha(Path(path))!=digest:raise SystemExit('compiled source drift: '+path)
  if kind=='runtime':
   if sha(Path(e['archive']))!=e['archive_sha256']:raise SystemExit('archive drift')
   for row in e['compile_results']:
    if row['exit_code']!=0:raise SystemExit('failed compile')
  else:
   if sha(Path(e['binary']))!=e['binary_sha256']:raise SystemExit('binary drift')
   for path,digest in e['archives'].items():
    if sha(Path(path))!=digest:raise SystemExit('linked archive drift')
   for row in e['commands']:
    if row['exit_code']!=0:raise SystemExit('failed compile/link')
  dst=H/('compile-evidence-'+kind+'-'+config+'.json');shutil.copyfile(src,dst);evidences[kind+'_'+config]=e
preserved={'native_and_prior_baseline_pins':len(base),'all_unchanged':True,'compiler_dependency_hashes_unchanged':True,'native_source_or_build_edits':False,'patches_applied':False,'target_binaries_or_tests_executed':False,'status':'O07 NS; independent and native acceptance outstanding'}
(H/'preservation-checks.json').write_text(json.dumps(preserved,indent=2)+'\n')
# Readiness does not hash itself; canonical hash is sorted compact files map.
files={str(p.relative_to(H)):sha(p) for p in sorted(H.rglob('*')) if p.is_file() and p.name!='readiness.json'}
manifest={'status':'excluded compiler/linker-only proposal; O07 not_started; no binary/test execution','package_sha256':hashlib.sha256(json.dumps(files,sort_keys=True,separators=(',',':')).encode()).hexdigest(),'files':files,'baseline_pins':len(base),'runtime_translation_units_each':9,'report_cli_translation_units_each':7,'artifacts':{k:{f:e[f] for f in (['archive','archive_sha256'] if k.startswith('runtime') else ['binary','binary_sha256'])} for k,e in evidences.items()},'layer_order':['composed','cursor','run_context','mode_binding','runtime','physical_explain','query_explain','native']}
(H/'readiness.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps({'package_sha256':manifest['package_sha256'],'baseline_pins':len(base),'artifacts':manifest['artifacts']}))
