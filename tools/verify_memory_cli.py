#!/usr/bin/env python3
"""Exercise the actual memory CLI at committed/private/released boundaries."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import tempfile
from jsonschema import Draft202012Validator

# Argument parsing and native CLI cases run at import time; this is a script entry point.
parser=argparse.ArgumentParser()
parser.add_argument('--crown',required=True)
args=parser.parse_args()
root=Path(__file__).resolve().parents[1]
fixtures=root/'tests/observability/cli/fixtures/p08'
validator=Draft202012Validator(json.loads((root/'schemas/memory-report-v1.schema.json').read_text()))
def run(command,code=0):
    value=subprocess.run([args.crown,*map(str,command)],capture_output=True,check=False)
    assert value.returncode==code,(command,value.returncode,value.stderr.decode())
    if code:assert not value.stdout
    return value.stdout

with tempfile.TemporaryDirectory(prefix='crown-memory-cli-') as temporary:
    directory=Path(temporary)
    query=fixtures/'tests/structural/plans/queries/singleton.cq.json'
    tree=fixtures/'tests/structural/plans/trees/singleton.tree.json'
    plan=directory/'plan.json';plan.write_bytes(run(['lower-plan',query,tree]))
    source=json.loads(query.read_text())['catalog'];assert source['tables'][0]['name']=='T_r'
    binding={'catalog':{'version':1,'tables':[{'name':'T_r','source_schema_version':1,'columns':[{'name':'c0','type':'string','nullable':False,'collation':'binary'}],
        'constraints':[],'key_hints':[],'statistics':{'distinct_counts':[]}}]},'schema_version':1}
    digest=hashlib.sha256(json.dumps(binding,sort_keys=True,separators=(',',':')).encode()).hexdigest()
    event={'schema_version':1,'sequence':1,'catalog_version':1,'catalog_sha256':digest,'source_schema_version':1,'table':'T_r','operation':'insert','values':['alpha']}
    events=directory/'events.jsonl';events.write_text(json.dumps(event)+'\n')
    cases=[('runtime',[], 'committed',0),('session',[],'committed',0),
        ('session',['--input',events,'--events',1],'committed',1),
        ('session',['--input',events,'--events',1,'--lifecycle','stop'],'committed',1),
        ('session',['--input',events,'--events',1,'--lifecycle','drop'],'released',1),
        ('session',['--input',events,'--events',1,'--steps',0],'pending',0)]
    for command,options,availability,sequence in cases:
        result=json.loads(run(['explain',command,plan,'--format','memory-json',*options]));validator.validate(result)
        assert result['snapshot']['availability']==availability and result['snapshot']['sequence']==sequence
        assert result['snapshot']['layer']==('delta' if command=='runtime' else 'session')
        total=sum(x['current']['requested_bytes'] for x in result['owners'])
        assert total==result['snapshot']['account']['current']['requested_bytes']
        if availability!='committed':assert not result['tables'] and not result['operators']
        elif sequence==1:
            assert sum(x['live_records'] for x in result['tables'] if x['scope']=='physical_source')==1
    run(['explain','runtime',plan,'--format','memory-json','--max-bytes',0],4)
    run(['explain','runtime',plan,'--format','memory-json','--memory-limit-bytes',1],4)
    run(['explain','physical',plan,'--format','memory-json'],2)
    run(['explain','runtime',plan,'--format','memory-json','--certificate','absent.json'],2)
    print('Native memory CLI: committed/pending/stopped/dropped epochs, source rows, schema and no partial output on limits passed')
