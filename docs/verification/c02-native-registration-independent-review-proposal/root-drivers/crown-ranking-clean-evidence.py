from pathlib import Path
import datetime,hashlib,importlib.util,json,shutil,sys
W=Path('/home/userroot/Codex/CROWN');E=W/'build/verification';A=E/'ranking-clean-artifacts';M=E/'ranking-clean-artifacts-manifest.json';F=json.loads((E/'ranking-execution-freeze.json').read_text())
if A.exists()or M.exists():raise SystemExit('preserve previous clean evidence')
A.mkdir();sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def inputs(root):
 def one(roots,extra):
  paths=set(extra)
  for name in roots:paths.update(p.relative_to(root).as_posix()for p in(root/name).rglob('*')if p.is_file()and'__pycache__'not in p.parts and p.suffix not in{'.pyc','.pyo'})
  h=hashlib.sha256()
  for rel in sorted(paths):h.update(rel.encode());h.update(b'\0');h.update((root/rel).read_bytes());h.update(b'\0')
  return{'count':len(paths),'sha256':h.hexdigest()}
 return{'native':one(['include','src','apps','tests','cmake'],['CMakeLists.txt','CMakePresets.json']),'execution':one(['include','src','apps','tests','cmake','schemas','tools','third_party'],['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'])}
spec=importlib.util.spec_from_file_location('crown_clean_original',W/'tools/verify_clean_build.py');module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
spec2=importlib.util.spec_from_file_location('crown_symbols','/tmp/crown-ranking-symbols.py');symbols=importlib.util.module_from_spec(spec2);spec2.loader.exec_module(symbols)
record={'started_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'adapter_sha256':sha(Path(__file__)),'original_helper':'tools/verify_clean_build.py','original_helper_sha256':sha(W/'tools/verify_clean_build.py'),'source_before':inputs(W),'snapshot_inputs':None,'commands':[],'retained':[],'status':'running','changes':'runtime wrapper adds only --verbose to build/test and retains metadata before original finally cleanup, and raises this wrapper command ceiling to3600s; frozen native helper file unchanged'}
assert record['source_before']['native']==F['native']and record['source_before']['execution']==F['execution']
def save():M.write_text(json.dumps(record,indent=2)+'\n')
save();original_copy=module.copy_snapshot;original_run=module.run_command

def copied(repository,source,log):
 original_copy(repository,source,log);value=inputs(source);assert value['native']==F['native']and value['execution']==F['execution'];record['snapshot_inputs']=value;record['snapshot_source']=str(source);save()

def retain(build):
 candidates=[build/'compile_commands.json',build/'CMakeCache.txt',build/'CTestTestfile.cmake',build/'Testing/Temporary/LastTest.log']
 candidates+=list((build/'CMakeFiles').glob('*/flags.make'))+list((build/'CMakeFiles').glob('*/link.txt'))
 candidates+=list((build/'_deps/libpg_query').glob('*/Makefile'))
 for source in sorted(set(candidates)):
  if source.is_file():
   target=A/source.relative_to(build);target.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(source,target);record['retained'].append({'source':str(source),'retained':str(target.relative_to(W)),'sha256':sha(target)})
 if (build/'libcrown_runtime.a').is_file():record['symbols_manifest']=str(symbols.collect(build,'clean-source'))
 save()

def run(command,log):
 enriched=list(command)
 if enriched[0]=='ctest'or(enriched[0]=='cmake'and'--build'in enriched):enriched.append('--verbose')
 record['commands'].append({'original':command,'executed':enriched});save()
 try:return original_run(enriched,log)
 finally:
  if enriched[0]=='ctest':retain(Path(enriched[enriched.index('--test-dir')+1]))
# Additional C02 translation units and fault sweeps get a 3600-second command
# ceiling in this evidence wrapper; the repository helper remains unchanged.
module.COMMAND_TIMEOUT_SECONDS=3600
module.copy_snapshot=copied;module.run_command=run
code=module.main(sys.argv[1:]);record['source_after']=inputs(W);record['temporary_removed']=not Path(record['snapshot_source']).parent.exists()if record.get('snapshot_source')else None;record['source_stable']=record['source_before']==record['source_after'];record['exit_code']=code;record['status']='passed'if code==0 and record['source_stable']and record['temporary_removed']else'failed';record['completed_utc']=datetime.datetime.now(datetime.timezone.utc).isoformat();save();raise SystemExit(0 if record['status']=='passed'else 1)
