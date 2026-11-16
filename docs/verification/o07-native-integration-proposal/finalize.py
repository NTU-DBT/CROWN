from pathlib import Path
import hashlib,json,shutil
H=Path(__file__).resolve().parent;R=H.parents[2]
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
pins=json.loads((H/'baseline-sha256.json').read_text())
for p,d in pins.items():
 if sha(R/p)!=d:raise SystemExit('baseline drift: '+p)
artifacts={}
for config in ['testing','production']:
 p=Path('/tmp')/('crown-o07-native-integration-'+config)/'compile-evidence.json';e=json.loads(p.read_text())
 for key in ['compiler_dependencies','new_objects','reused_matched_report_objects','archives']:
  for f,d in e[key].items():
   if sha(Path(f))!=d:raise SystemExit('compiled input/artifact drift: '+f)
 if sha(Path(e['binary']))!=e['binary_sha256']:raise SystemExit('binary drift')
 if any(x['exit_code'] for x in e['commands']):raise SystemExit('failed compiler/link command')
 shutil.copyfile(p,H/('compile-evidence-'+config+'.json'));artifacts[config]={k:e[k] for k in ['binary','binary_sha256']}
(H/'preservation-checks.json').write_text(json.dumps({'baseline_pins':len(pins),'all_pins_unchanged':True,'cmake_invoked':False,'binaries_or_tests_executed':False,'native_edits':False,'frozen_package_edits':False,'patches_applied':False},indent=2)+'\n')
files={str(p.relative_to(H)):sha(p) for p in sorted(H.rglob('*')) if p.is_file() and p.name!='readiness.json'}
v={'status':'unapplied native-integration proposal; compiler/linker only; O07 NS','package_sha256':hashlib.sha256(json.dumps(files,sort_keys=True,separators=(',',':')).encode()).hexdigest(),'files':files,'artifacts':artifacts,'baseline_pins':len(pins)}
(H/'readiness.json').write_text(json.dumps(v,indent=2)+'\n');print(json.dumps({k:v[k] for k in ['package_sha256','baseline_pins','artifacts']}))
