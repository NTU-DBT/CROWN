from pathlib import Path
import datetime,hashlib,json,subprocess,sys
W=Path('/home/userroot/Codex/CROWN');E=W/'build/verification'
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def collect(build,label,parser_undefined=False):
 build=Path(build).resolve();summary=E/f'ranking-{label}-symbols.json'
 if summary.exists():raise RuntimeError('preserve existing symbol evidence '+str(summary))
 specs=[('plan',build/'libcrown_plan.a',False),('ranking',build/'libcrown_ranking.a',False),('ranking_runtime',build/'libcrown_ranking_runtime.a',False),('ranking_runtime_testing',build/'libcrown_ranking_runtime_testing.a',False),('planner_testing',build/'libcrown_planner_testing.a',False),('runtime',build/'libcrown_runtime.a',False),('runtime_testing',build/'libcrown_runtime_testing.a',False),('explain',build/'libcrown_explain.a',False),('explain_testing',build/'libcrown_explain_testing.a',False)]
 if parser_undefined:specs.append(('parser_undefined',build/'_deps/libpg_query/libpg_query-18.1.0/libpg_query.a',True))
 rows=[]
 for name,archive,undefined in specs:
  before=sha(archive);dump=E/f'ranking-{label}-{name}.nm';err=E/f'ranking-{label}-{name}.nm.stderr';cmd=['nm','-C','--undefined-only'if undefined else'--defined-only',str(archive)]
  with dump.open('x')as out,err.open('x')as stderr:p=subprocess.run(cmd,stdout=out,stderr=stderr,check=False)
  after=sha(archive);row={'role':name,'archive':str(archive),'archive_sha256':before,'archive_stable':before==after,'command':cmd,'exit_code':p.returncode,'dump':str(dump.relative_to(W)),'dump_sha256':sha(dump),'stderr':str(err.relative_to(W)),'stderr_sha256':sha(err)};rows.append(row)
  if p.returncode or before!=after:raise RuntimeError('symbol capture failure '+str(row))
 runtime_dump=(E/f'ranking-{label}-runtime.nm').read_text()
 testing_dump=(E/f'ranking-{label}-runtime_testing.nm').read_text()
 if 'RuntimeTestProbe::' in runtime_dump or 'seed_c01_report_saturation' in runtime_dump:
  raise RuntimeError('testing seam exported by production runtime')
 if 'RuntimeTestProbe::seed_c01_report_saturation' not in testing_dump:
  raise RuntimeError('testing C01 saturation seam absent')
 record={'configuration':label,'recorded_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'collector_sha256':sha(Path(__file__)),'records':rows,'status':'captured; independent semantic audit pending'};summary.write_text(json.dumps(record,indent=2)+'\n');return summary
if __name__=='__main__':print(collect(sys.argv[1],sys.argv[2],len(sys.argv)>3 and sys.argv[3]=='--parser-undefined'))
