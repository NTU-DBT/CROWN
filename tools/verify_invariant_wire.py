#!/usr/bin/env python3
"""Check native diagnostic bytes against an independently compiled predecessor."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import tempfile
from jsonschema import Draft202012Validator, RefResolver

parser=argparse.ArgumentParser()
parser.add_argument('--executable',required=True)
args=parser.parse_args()
root=Path(__file__).resolve().parents[1]
manifest=json.loads((root/'tests/runtime/inspection/wire-v1.json').read_text())
assert manifest['format']=='crown-invariant-wire-fixture-digests' and manifest['version']==1
schema=root/'schemas/runtime-diagnostic-v1.schema.json'
data=json.loads(schema.read_text())
store={path.as_uri():json.loads(path.read_text()) for path in (root/'schemas').glob('*.json')}
validator=Draft202012Validator(data,resolver=RefResolver(base_uri=schema.as_uri(),referrer=data,store=store))
with tempfile.TemporaryDirectory(prefix='crown-invariant-wire-') as temporary:
    directory=Path(temporary)
    subprocess.run([args.executable,'--export-directory',str(directory)],check=True)
    names=sorted(path.name for path in directory.glob('*.json'))
    assert len(names)==210 and names==sorted(manifest['reports'])
    for name in names:
        encoded=(directory/name).read_bytes()
        actual=hashlib.sha256(encoded).hexdigest()
        assert actual==manifest['reports'][name],(name,'diagnostic bytes changed',actual,manifest['reports'][name])
        value=json.loads(encoded);validator.validate(value)
    print('All210 native invariant reports match independently compiled reference bytes and the unchanged schema')
