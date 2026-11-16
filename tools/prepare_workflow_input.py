#!/usr/bin/env python3
"""Bind a small JSONL example template to a CROWN canonical catalog."""
from pathlib import Path
import hashlib,json,subprocess,sys

# Input/output byte grants are checked after complete read/encode, before exclusive output.
def main():
    if len(sys.argv)!=5:raise ValueError('usage: prepare_workflow_input.py CROWN CATALOG.json TEMPLATE.jsonl OUTPUT.jsonl')
    executable,catalog,template,output=sys.argv[1:]
    data=Path(template).read_bytes()
    if len(data)>8*1024*1024:raise ValueError('example template exceeds8MiB')
    result=subprocess.run([executable,'canonicalize-catalog',catalog],check=True,capture_output=True,text=True)
    canonical=json.dumps(json.loads(result.stdout),sort_keys=True,ensure_ascii=False,separators=(',',':')).encode('utf-8')
    digest=hashlib.sha256(canonical).hexdigest();lines=[]
    for number,line in enumerate(data.decode('utf-8').splitlines(),1):
        event=json.loads(line)
        if not isinstance(event,dict):raise ValueError(f'line{number}: expected an update object')
        if 'catalog_sha256' in event and event['catalog_sha256']!=digest:raise ValueError(f'line{number}: existing catalog binding differs')
        event['catalog_sha256']=digest;lines.append(json.dumps(event,ensure_ascii=False,separators=(',',':'))+'\n')
    encoded=''.join(lines)
    if len(encoded.encode('utf-8'))>16*1024*1024:raise ValueError('bound example stream exceeds16MiB')
    with Path(output).open('x',encoding='utf-8') as stream:stream.write(encoded)
    print(f'Bound{len(lines)} physical records to canonical catalog {digest}')
    return 0
if __name__=='__main__':
    try:raise SystemExit(main())
    except Exception as error:print(str(error),file=sys.stderr);raise SystemExit(1)
