#!/usr/bin/env python3
"""Capture twelve C05 archive roles; root executes, independent auditor interprets."""
from pathlib import Path
import argparse, datetime, hashlib, json, subprocess

ROOT = Path('/home/userroot/Codex/CROWN')
V = ROOT/'build/verification'
FREEZE = V/'selection-execution-freeze.json'
ROLES = ['plan','planner_testing','runtime','runtime_testing','explain','explain_testing','ranking',
         'ranking_runtime','ranking_runtime_testing','selection','selection_runtime','selection_runtime_testing']

def need(value, message):
    if not value: raise RuntimeError(message)
def sha(path): return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def collect(build, label, freeze_sha256, parser_undefined=False):
    need(label in {'debug','release','sanitize','clang','clean-source'}, 'unsupported symbol label')
    need(parser_undefined == (label == 'sanitize'), 'parser undefined capture required exactly for sanitizer')
    need(sha(FREEZE) == freeze_sha256, 'unexpected freeze FILE')
    freeze = json.loads(FREEZE.read_text())
    need(freeze['symbol_roles'] == ROLES, 'archive role inventory differs')
    own = str(Path(__file__).resolve())
    need(freeze['root_execution_helpers'].get(own) == sha(own), 'unbound symbol collector')
    build = Path(build).resolve(); summary = V/('selection-'+label+'-symbols.json')
    specs = [(name,build/('libcrown_'+name+'.a'),False) for name in ROLES]
    if parser_undefined: specs.append(('parser_undefined',build/'_deps/libpg_query/libpg_query-18.1.0/libpg_query.a',True))
    paths = [summary]
    for name,_,_ in specs:
        paths.extend([V/('selection-'+label+'-'+name+'.nm'),V/('selection-'+label+'-'+name+'.nm.stderr')])
    need(all(not p.exists() for p in paths), 'preserve existing symbol evidence')
    record = {'configuration':label,'started_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
              'freeze_sha256':freeze_sha256,'collector_sha256':sha(own),'records':[],
              'acceptance':'Raw capture only; exact symbol methods, archive members and graph await independent audit.'}
    status = 0
    try:
        for name, archive, undefined in specs:
            before = sha(archive); dump = V/('selection-'+label+'-'+name+'.nm'); err = V/('selection-'+label+'-'+name+'.nm.stderr')
            command = ['nm','-C','--undefined-only' if undefined else '--defined-only',str(archive)]
            row = {'role':name,'archive':str(archive),'archive_sha256':before,'command':command,
                   'dump':str(dump.relative_to(ROOT)),'stderr':str(err.relative_to(ROOT))}
            record['records'].append(row)
            try:
                with dump.open('x') as out, err.open('x') as stderr:
                    result = subprocess.run(command,stdout=out,stderr=stderr,check=False,timeout=600)
                row['exit_code'] = result.returncode
            except Exception as error:
                row['exit_code'] = 124 if isinstance(error,subprocess.TimeoutExpired) else 1
                row['error'] = repr(error)
            finally:
                if archive.is_file(): row['archive_sha256_after'] = sha(archive)
                if dump.is_file(): row['dump_sha256'] = sha(dump)
                if err.is_file(): row['stderr_sha256'] = sha(err)
                row['archive_stable'] = before == row.get('archive_sha256_after')
            need(row['exit_code'] == 0 and row['archive_stable'], 'symbol capture failed: '+name)
        runtime = (V/('selection-'+label+'-runtime.nm')).read_text()
        testing = (V/('selection-'+label+'-runtime_testing.nm')).read_text()
        need('RuntimeTestProbe::' not in runtime and 'seed_c01_report_saturation' not in runtime,
             'testing seam exported by production runtime')
        need('RuntimeTestProbe::seed_c01_report_saturation' in testing, 'testing saturation seam missing')
        need(sha(FREEZE) == freeze_sha256 and sha(own) == record['collector_sha256'], 'collector/freeze drift')
    except Exception as error:
        record['error'] = repr(error); status = 1
    record.update({'exit_code':status,'status':'captured' if status == 0 else 'failed','terminal':True,
                   'completed_utc':datetime.datetime.now(datetime.timezone.utc).isoformat()})
    with summary.open('x') as handle: handle.write(json.dumps(record,indent=2)+'\n')
    if status: raise RuntimeError('symbol evidence failed; retained '+str(summary))
    return summary

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('build'); parser.add_argument('label')
    parser.add_argument('--freeze-sha256',required=True); parser.add_argument('--parser-undefined',action='store_true')
    args = parser.parse_args()
    print(collect(args.build,args.label,args.freeze_sha256,args.parser_undefined),flush=True)
    return 0

if __name__ == '__main__': raise SystemExit(main())
