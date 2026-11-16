#!/usr/bin/env python3
"""Independent file-only SQL/native CLI/restart/delta workflow acceptance."""
from pathlib import Path
import copy,hashlib,json,subprocess,sys,tempfile
import jsonschema

def require(value,message):
    if not value:raise RuntimeError(message)
def key(value):return json.dumps(value,ensure_ascii=False,sort_keys=True,separators=(',',':'))
def rowset(rows):return {key(row) for row in rows}
def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def native_files(directory):return {p.name:digest(p) for p in directory.iterdir() if p.is_file() and (p.name.startswith('state.root') or p.name=='results.sink')}

def main():
    require(len(sys.argv)==3,'usage: workflow.py EXECUTABLE SOURCE')
    executable=Path(sys.argv[1]).resolve();root=Path(sys.argv[2]).resolve();checks=0
    report_path=root/'schemas/workflow-report-v1.schema.json';report_schema=json.loads(report_path.read_text());report_resolver=jsonschema.RefResolver(base_uri=report_path.as_uri(),referrer=report_schema)
    report_validator=jsonschema.Draft202012Validator(report_schema,resolver=report_resolver)
    def run(args,expected=0,code=None):
        nonlocal checks
        result=subprocess.run([str(executable),*[str(a) for a in args]],capture_output=True,text=True,timeout=120)
        require((result.returncode==0)==(expected==0),f'{args}: exit {result.returncode}: {result.stderr[:500]}')
        if expected==0:require(not result.stderr,f'unexpected stderr: {result.stderr}')
        else:
            require(not result.stdout,f'rejection emitted partial stdout: {args}')
            value=json.loads(result.stderr)
            if code:require(value['error']==code,f'{args}: expected {code}, got {value}')
        if expected!=0:report_validator.validate(json.loads(result.stderr))
        elif args[0] in ['run','restore','snapshot','checkpoint','results','verify-trace','benchmark','validate-plan']:report_validator.validate(json.loads(result.stdout))
        checks+=1;return result
    manifest=json.loads((root/'tests/workflow/manifest.json').read_text())
    for name,h in manifest['source_sha256'].items():require(digest(root/'tests/workflow'/name)==h,f'independent fixture drift: {name}')
    schema_path=root/'schemas/compiled-workflow-v1.schema.json';schema=json.loads(schema_path.read_text())
    resolver=jsonschema.RefResolver(base_uri=schema_path.as_uri(),referrer=schema)
    with tempfile.TemporaryDirectory(prefix='crown-workflow-') as temporary:
        work=Path(temporary)
        for name,case in manifest['cases'].items():
            fixture=root/'tests/workflow';directory=work/name;directory.mkdir();catalog=fixture/case['catalog'];sql=fixture/case['query']
            canonical=json.loads(run(['canonicalize-catalog',catalog]).stdout)
            catalog_hash=hashlib.sha256(key(canonical).encode()).hexdigest()
            events=[json.loads(line) for line in (fixture/case['events_template_jsonl']).read_text().splitlines()]
            for event in events:event['catalog_sha256']=catalog_hash
            updates=directory/'input.jsonl';updates.write_text(''.join(key(event)+'\n' for event in events))
            built=json.loads(run(['compile',sql,catalog]).stdout)
            jsonschema.Draft202012Validator(schema,resolver=resolver).validate(built)
            artifact=directory/'compiled.json';artifact.write_text(key(built))
            validated=json.loads(run(['validate-plan','compiled',artifact]).stdout)
            require(validated['physical_valid'] and validated['height_status']=='proven_minimum','compiled plan validation failed')
            expected=json.loads((fixture/case['expected_oracle']).read_text())
            verified=json.loads(run(['verify-trace',artifact,updates]).stdout)
            require(verified['trace_verified'] and verified['records']==len(events),'bounded relational verification failed')
            for option in ['--verify-work','--reference-bytes','--verify-events']:
                run(['verify-trace',artifact,updates,option,0],1,'resource_limit')
            for mode,observe in [('delta','trace'),('maintenance','off')]:
                bench=directory/('benchmark-'+mode);bench.mkdir()
                report=json.loads(run(['benchmark',artifact,updates,bench/'state.root',bench/'results.sink','--mode',mode,'--observe',observe,'--run-label','independent-workflow']).stdout)
                require(report['records']==len(events) and report['runtime']['mode']==mode and report['runtime']['observation']==observe,'benchmark reported a different executed mode')
                require(rowset(report['final']['rows'])==rowset(expected['events'][-1]['current_rows']),'benchmark state differs from oracle')
                signed=sum(len(e['signed_delta']) for e in expected['events']) if mode=='delta' else 0
                require(report['delivered_rows']==signed and report['delivery']['verified_sequence']==len(events),'benchmark delivery count/receipt differs')
                require(report['initialization_ns']>=0 and report['processing_ns']>=report['input_begin_ns']+report['native_prepare_commit_ns']+report['delivery_ns'],'benchmark timing partitions overlap')

            state_path=directory/'state.root';sink=directory/'results.sink';args=[artifact,updates,state_path,sink]
            for fmt in ['json','text','dot','tree-json']:
                before={p.name:digest(p) for p in directory.iterdir() if p.is_file()}
                explained=run(['explain','compiled',artifact,'--format',fmt]).stdout
                require(bool(explained.strip()),'empty EXPLAIN')
                require(before=={p.name:digest(p) for p in directory.iterdir() if p.is_file()},'EXPLAIN changed a file')
            initial=json.loads(run(['run',*args,'--events',0]).stdout)
            require(rowset(initial['rows'])==rowset(expected['initial_current_rows']),'wrong initial SQL/Boolean result')
            require(initial['committed_sequence']==initial['verified_output_sequence']==0,'initial epoch advanced')
            for epoch in expected['events']:
                result=json.loads(run(['restore',*args,'--events',1]).stdout);sequence=epoch['sequence']
                require(result['committed_sequence']==result['verified_output_sequence']==sequence,f'{name}/{sequence}: wrong state/output frontier')
                require(len(result['rows'])==len(epoch['current_rows']) and rowset(result['rows'])==rowset(epoch['current_rows']),f'{name}/{sequence}: current differs from independent oracle')
                source=epoch['source_position'];require(result['source_positions']=={source['source']:source['offset']},f'{name}/{sequence}: source offset differs')
                actual=json.loads(run(['results',*args,'--epoch',sequence]).stdout)
                rows=[{'operation':row['op'],'values':row['values']} for row in actual['rows']]
                require(len(rows)==len(epoch['signed_delta']) and rowset(rows)==rowset(epoch['signed_delta']),f'{name}/{sequence}: missing/duplicate/signed delta mismatch')
                recovered=json.loads(run(['snapshot',*args]).stdout)
                require(rowset(recovered['rows'])==rowset(epoch['current_rows']) and recovered['source_positions']==result['source_positions'],'native snapshot restart changed state/source')
                if sequence==2:
                    point=json.loads(run(['checkpoint',*args]).stdout)
                    require(point['selected_generation']==2 and point['committed_sequence']==sequence,'rotation changed native epoch')
            ended=json.loads(run(['restore',*args]).stdout)
            require(ended['committed_sequence']==len(events),'EOF changed epoch')
            retired=json.loads(run(['checkpoint',*args,'--retire']).stdout)
            require(retired['first_generation']==retired['selected_generation'],'verified retirement did not complete')
            stable=native_files(directory)
            canonical=key(built)
            duplicates=['{"schema_version":0,'+canonical[1:],
                        canonical.replace('"physical":{','"physical":{"schema_version":0,',1)]
            for index,text in enumerate(duplicates):
                path=directory/f'duplicate-{index}.json';path.write_text(text)
                run(['validate-plan','compiled',path],1,'invalid_document')
                require(native_files(directory)==stable,'duplicate-key admission changed durable files')
            deep=directory/'too-deep.json';deep.write_text('['*258+'0'+']'*258)
            run(['validate-plan','compiled',deep],1,'resource_limit')
            run(['snapshot',*args,'--events',1],1,'usage');require(native_files(directory)==stable,'inapplicable option changed files')
            run(['snapshot',*args,'--max-bytes',2],1,'output_limit');require(native_files(directory)==stable,'bounded snapshot changed durable bytes')
            for index,version in enumerate([True,1.0,2]):
                bad=copy.deepcopy(built);bad['schema_version']=version;path=directory/f'version-{index}.json';path.write_text(key(bad))
                run(['snapshot',path,updates,state_path,sink],1,'invalid_artifact');require(native_files(directory)==stable,'bad version changed files')
            bad=copy.deepcopy(built);bad['height_certificate']['minimum_height']+=1;path=directory/'bad-proof.json';path.write_text(key(bad))
            run(['snapshot',path,updates,state_path,sink],1,'invalid_height_certificate');require(native_files(directory)==stable,'bad proof changed files')
            private=directory/'explicit-ids';private.mkdir();ids=['--query-id','0123456789abcdef0123456789abcdef','--sink-id','fedcba9876543210fedcba9876543210']
            private_args=[artifact,updates,private/'state.root',private/'results.sink']
            run(['run',*private_args,'--events',1,*ids]);run(['restore',*private_args,'--events',1,*ids])
            identified=json.loads(run(['results',*private_args,'--epoch',2,*ids]).stdout)
            require(identified['query_id']==ids[1] and identified['sink_id']==ids[3],'result view lost explicit file identities')
            saved=native_files(private);run(['snapshot',*private_args],1,'generation_failed');require(native_files(private)==saved,'wrong expected identity changed files')
            invalid=directory/'invalid-id';invalid.mkdir();run(['run',artifact,updates,invalid/'state.root',invalid/'results.sink','--query-id','bad'],1,'usage');require(not list(invalid.iterdir()),'bad ID created files')
            for index,value in enumerate(['-1','bad','18446744073709551616']):
                fresh=directory/f'invalid-{index}';fresh.mkdir()
                run(['run',artifact,updates,fresh/'state.root',fresh/'results.sink','--events',value],1,'usage')
                require(not list(fresh.iterdir()),'bad numeric argument created files or locks')
            print(f'workflow {name}: {len(events)} exact epochs/source/deltas/empty frames/restart/rotation/retirement passed')
        # Constant false is an admitted empty operator, with no forged height proof.
        case=next(iter(manifest['cases'].values()));catalog=root/'tests/workflow'/case['catalog'];sql=work/'false.sql'
        source_catalog=json.loads(catalog.read_text())['catalog'];table=source_catalog['tables'][0]
        quote=lambda value:'\"'+value.replace('\"','\"\"')+'\"'
        sql.write_text('SELECT DISTINCT e.'+quote(table['columns'][0]['name'])+' FROM '+quote(table['name'])+' AS e WHERE 1 = 0;\n')
        false=run(['compile',sql,catalog]);empty=json.loads(false.stdout)
        require(empty['physical']['route']=='constant_false' and empty['height_certificate'] is None,'constant-false compile claimed an unrelated structural minimum')
        jsonschema.Draft202012Validator(schema,resolver=resolver).validate(empty)
        path=work/'false.json';path.write_text(key(empty));run(['explain','compiled',path,'--format','json'])
    print(f'O08 workflow {checks} public CLI checks passed; five independent SQL/data fixtures,34 physical epochs')
    return 0
if __name__=='__main__':
    try:raise SystemExit(main())
    except Exception as error:print(str(error),file=sys.stderr);raise SystemExit(1)
