#!/usr/bin/env python3
"""Validate actual native memory-report fixtures and independent byte identities."""
import argparse
import json
from pathlib import Path
import subprocess
import tempfile
from jsonschema import Draft202012Validator

# Importing executes argument parsing and the native exporter; assertions must be enabled.
parser=argparse.ArgumentParser()
parser.add_argument('--executable',required=True)
args=parser.parse_args()
root=Path(__file__).resolve().parents[1]
schema=json.loads((root/'schemas/memory-report-v1.schema.json').read_text())
Draft202012Validator.check_schema(schema)
validator=Draft202012Validator(schema)

def usage_sum(values):
    return {k:sum(v[k] for v in values) for k in ['allocations','requested_bytes','payload_bytes']}

with tempfile.TemporaryDirectory(prefix='crown-operator-memory-') as temporary:
    subprocess.run([args.executable,'--export-directory',temporary],check=True)
    files=sorted(Path(temporary).glob('*.json'))
    assert len(files)==8
    for path in files:
        report=json.loads(path.read_text());validator.validate(report)
        account=report['snapshot']['account'];owners=report['owners']
        keys=[(x['attribution']['kind'],x['attribution']['id']) for x in owners]
        assert len(keys)==len(set(keys))
        assert usage_sum([x['current'] for x in owners])==account['current']
        assert usage_sum(account['by_purpose'].values())==account['current']
        assert usage_sum(account['by_lifetime'].values())==account['current']
        assert account['current']['requested_bytes']<=account['peak_requested_bytes']<=account['limit_bytes']
        assert account['successful_allocations']-account['freed_allocations']==account['current']['allocations']
        by_key=dict(zip(keys,owners))
        if report['snapshot']['layer'] in ['delta','session']:
            coordinator=next(x for x in report['operators'] if x['kind']=='coordinator' and x['layer']=='delta')
            assert coordinator['attribution']=={'kind':'delta_node','id':18446744073709551615}
            assert all(x['attribution']!=coordinator['attribution'] for x in report['operators'] if x['kind']=='delta_factor')
        for table in report['tables']:
            for owner in [table['table_owner'],table['arena']['owner']]:
                attr=owner['attribution'];assert owner==by_key[(attr['kind'],attr['id'])]
            arena=table['arena'];records=arena['records']
            assert records['slots']==records['live_records']+records['retained_records']+records['free_slots']+records['exhausted_slots']
            for kind in ['live','retained','free','exhausted']:
                count=records[{'live':'live_records','retained':'retained_records','free':'free_slots','exhausted':'exhausted_slots'}[kind]]
                assert arena[kind+'_slots']['allocations']==count
            assert arena['live_values']['allocations']==table['live_records']==records['live_records']
            assert usage_sum([table['table_owner']['current'],arena['owner']['current']])==table['owned']
        if report['snapshot']['availability']!='committed':
            assert not report['tables'] and not report['operators']
    print('Eight real memory exports satisfy schema and independent account/arena/owner identities')
