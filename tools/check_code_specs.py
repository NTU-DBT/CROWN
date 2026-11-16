#!/usr/bin/env python3
"""Check saved source coverage, hashes, local links and Markdown fragments.

Run after tools/generate_code_specs.py. This is an offline documentation check;
it does not build, instrument or certify runtime behavior.
"""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import re
import sys
from urllib.parse import unquote, urlsplit

ROOT=Path(__file__).resolve().parents[1]
DOCS=ROOT/'docs/code_specs'

def headings(path):
    # This accepts a limited ATX/backtick grammar rather than parsing all Markdown.
    seen={};result=set();fenced=False
    for line in path.read_text().splitlines():
        if line.startswith('```'):fenced=not fenced;continue
        if fenced:continue
        match=re.match(r'^#{1,6}\s+(.+?)\s*#*$',line)
        if not match:continue
        value=re.sub(r'[^\w\- ]','',match.group(1).lower()).replace(' ','-')
        count=seen.get(value,0);seen[value]=count+1
        result.add(value+('-'+str(count) if count else ''))
    result.update(re.findall(r'<(?:a|span)\s+id=["\']([^"\']+)',path.read_text()))
    return result

def check(root=ROOT, docs=DOCS):
    # Canonical card edits require regeneration; this checker reads saved flags/contracts.
    manifest=json.loads((docs/'coverage.json').read_text());errors=[];source_names=set();contracts=set();counts={'files':0,'lines':0,'blocks':0}
    for item in manifest['files']:
        source=root/item['source_path'];source_names.add(item['source_path'])
        if not source.is_file():errors.append('missing source: '+item['source_path']);continue
        if hashlib.sha256(source.read_bytes()).hexdigest()!=item['staged_sha256']:
            errors.append('stale source hash: '+item['source_path'])
        total=len(source.read_text().splitlines());cursor=1
        for block in item['blocks']:
            if block['start_line']!=cursor or block['end_line']<cursor:errors.append('gap/overlap: '+item['source_path']+':'+block['id'])
            cursor=block['end_line']+1
            if block.get('manual_review_stale'):errors.append('manual review requires recheck: '+item['source_path']+':'+block['id'])
            for contract in block.get('contracts',[]):
                for field in ('anchor','purpose','inputs_outputs','invariants','ownership','failure','cost','references'):
                    if not contract.get(field):errors.append('empty reviewed field: '+item['source_path']+':'+field)
                key=(item['source_path'],contract.get('anchor',''))
                if key in contracts:errors.append('duplicate reviewed anchor: '+item['source_path']+':'+key[1])
                contracts.add(key)
        if cursor!=item['line_count']+1 or total!=item['line_count']:errors.append('line count: '+item['source_path'])
        counts['files']+=1;counts['lines']+=total;counts['blocks']+=len(item['blocks'])
    suffixes={'.cpp','.cc','.c','.hpp','.h','.inc','.py','.sh','.cmake'}
    expected={'CMakeLists.txt'}
    for scope in ('include','src','apps','tools','examples','cmake','tests'):
        expected.update(str(p.relative_to(root)) for p in (root/scope).rglob('*') if p.is_file() and (p.suffix in suffixes or p.name=='CMakeLists.txt' or p.name.endswith('.cmake.in')))
    replay='tools/support/CrownReplay.scala'
    if (root/replay).is_file():expected.add(replay)
    component_replay='tools/support/ComponentReplay.scala'
    if (root/component_replay).is_file():expected.add(component_replay)
    for missing in sorted(expected-source_names):errors.append('unmapped maintained code: '+missing)
    for surplus in sorted(source_names-expected):errors.append('out-of-scope or removed source: '+surplus)
    if manifest.get('unused_manual_overrides'):errors.append('unmatched manual contract anchors')
    heading_cache={};links=0
    for page in docs.rglob('*.md'):
        for raw in re.findall(r'(?<![!\\])\[[^\]\n]*(?<!\\)\]\(([^\s)]+)\)',page.read_text()):
            url=urlsplit(raw)
            if url.scheme or url.netloc:continue
            path=(page.parent/unquote(url.path)).resolve() if url.path else page
            links+=1
            try:path.relative_to(root.resolve())
            except ValueError:errors.append('link escapes repository: '+str(page)+': '+raw);continue
            if not path.is_file():errors.append('missing local link: '+str(page)+': '+raw);continue
            if not url.fragment:continue
            fragment=unquote(url.fragment)
            if path.suffix=='.md':
                if path not in heading_cache:heading_cache[path]=headings(path)
                if fragment not in heading_cache[path]:errors.append('missing Markdown fragment: '+str(page)+': '+raw)
            elif re.fullmatch(r'L\d+(?:-L\d+)?',fragment):
                maximum=len(path.read_text().splitlines())
                if any(not 1<=int(n)<=maximum for n in re.findall(r'\d+',fragment)):
                    errors.append('source-line link outside file: '+str(page)+': '+raw)
            else:errors.append('unverified local fragment: '+str(page)+': '+raw)
    return {'status':'pass' if not errors else 'fail','coverage':counts,'local_links_checked':links,'errors':errors}

def main():
    result=check();print(json.dumps(result,indent=2))
    return 0 if result['status']=='pass' else 1
if __name__=='__main__':sys.exit(main())
