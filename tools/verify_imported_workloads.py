#!/usr/bin/env python3
"""Check pinned imported SQL definitions without changing their result semantics."""
from __future__ import annotations
import argparse
import copy
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import subprocess
import sys
sys.dont_write_bytecode = True
from generate_workloads import acyclic


def require(value, message):
    if not value: raise ValueError(message)


def checked(source, entry):
    relative = PurePosixPath(entry['path'])
    require(not relative.is_absolute() and '..' not in relative.parts and '\\' not in str(relative), 'unsafe imported path')
    path = source / relative
    require(path.resolve().is_relative_to(source.resolve()) and path.is_file(), 'outside/missing imported source')
    require(hashlib.sha256(path.read_bytes()).hexdigest() == entry['sha256'], 'imported source checksum mismatch')
    return path


def walk(value):
    if isinstance(value, dict):
        yield value
        for child in value.values(): yield from walk(child)
    elif isinstance(value, list):
        for child in value: yield from walk(child)


# This resolver covers the pinned equality-join ASTs, without general SQL scope semantics.
def equality_body(ast):
    aliases, order = {}, []
    for node in walk(ast):
        if 'RangeVar' in node:
            atom = node['RangeVar']; table = atom['relname']; alias = atom.get('alias', {}).get('aliasname', table)
            require(alias not in aliases, 'shadowed alias requires a scoped import review')
            aliases[alias] = table; order.append((alias, table))
    prefixes = {'customer': 'c_', 'orders': 'o_', 'lineitem': 'l_', 'supplier': 's_', 'nation': 'n_',
                'region': 'r_', 'part': 'p_', 'partsupp': 'ps_', 'catalog_sales': 'cs_', 'customer_address': 'ca_',
                'date_dim': 'd_', 'store_sales': 'ss_', 'store': 's_', 'item': 'i_'}
    def column(node):
        if not isinstance(node, dict) or 'ColumnRef' not in node: return None
        fields = node['ColumnRef']['fields']
        require(all('String' in field for field in fields), 'unsupported equality reference')
        return [field['String']['sval'] for field in fields]
    def resolve(names):
        if len(names) == 2:
            alias, name = names; require(alias in aliases, 'unknown join alias')
        else:
            require(len(names) == 1, 'unsupported qualified join column'); name = names[0]
            choices = [a for a, table in aliases.items() if table in prefixes and name.startswith(prefixes[table])]
            require(len(choices) == 1, 'ambiguous unqualified imported join column'); alias = choices[0]
        return alias + '.' + name
    parent = {}
    def find(name):
        parent.setdefault(name, name)
        while name != parent[name]: parent[name] = parent[parent[name]]; name = parent[name]
        return name
    for node in walk(ast):
        if 'A_Expr' not in node: continue
        expression = node['A_Expr']
        if expression.get('name') != [{'String': {'sval': '='}}]: continue
        left, right = column(expression.get('lexpr')), column(expression.get('rexpr'))
        if left is not None and right is not None: parent[find(resolve(left))] = find(resolve(right))
    scopes = {alias: set() for alias in aliases}
    for name in parent: scopes[name.split('.')[0]].add(find(name))
    return order, acyclic(list(scopes.values()))


def verify(source, packet, crown=None):
    require(packet['schema_version'] == 1 and packet['kind'] == 'crown_imported_query_inventory', 'unknown imported inventory')
    require(packet['source_integrity']['repository'] == 'hkustDB/DynaGox' and
            packet['source_integrity']['commit'] == 'c6811db68a34ab3b32722968c4e1e821f730c5ac', 'source version requires a new reviewed packet')
    pinned_blobs = {'Queries.md': 'c520700d12741ef0e5578087812b7e7256043e4a',
                    'Readme.md': 'a4548066af0e711ee6700073eef8d9605eb06b9d'}
    documents = {}
    for entry in packet['source_documents']:
        path = checked(source, entry); data = path.read_bytes()
        require(entry['git_blob_sha1'] == pinned_blobs.get(path.name) and
                '/blob/c6811db68a34ab3b32722968c4e1e821f730c5ac/' in entry['url'], 'document does not match the reviewed source pin')
        require(hashlib.sha1(b'blob ' + str(len(data)).encode() + b'\0' + data).hexdigest() == entry['git_blob_sha1'], 'pinned Git blob mismatch')
        documents[path.name] = data.decode('utf-8')
    require(set(documents) == set(pinned_blobs), 'incomplete source document packet')
    canonical = documents['Queries.md']
    matches = list(re.finditer(r'(?m)^-- ([A-Z0-9-]+)\s*$', canonical))
    originals = {}
    for i, match in enumerate(matches):
        originals[match[1]] = canonical[match.end():matches[i + 1].start() if i + 1 < len(matches) else len(canonical)].strip().removesuffix('```').strip() + '\n'
    queries = packet['queries']; require(len(queries) == len(originals) == 24, 'incomplete canonical query inventory')
    require([query['label'] for query in queries] == list(originals), 'canonical labels/order changed')
    cyclic = []; parsed_count = 0
    for query in queries:
        path = checked(source, query['sql']); sql = path.read_text()
        require(sql == originals[query['label']], 'original SQL definition replaced by an adapted query')
        require(query['select_clause_verbatim'] in sql, 'SELECT clause mismatch')
        if query['group_by_clause_verbatim']: require(query['group_by_clause_verbatim'] in sql, 'GROUP BY mismatch')
        for equality in query['join_equalities_verbatim']: require(equality in sql, 'join description changed')
        require(not query['native_run_eligible'] and query['catalog'] is None and
                query['expected_native_R1_compatibility']['compatible_as_written'] is False, 'aggregate source enabled for R1 timing')
        require(query['data_record'] == 'external_input_not_imported' and query['source_license'] == 'unresolved_A02_local_inspection_only', 'unknown data/license accepted')
        declared = query['structural_classification']['equality_join_body'] == 'alpha_acyclic'
        if not declared: cyclic.append(query['label'])
        if crown:
            result = subprocess.run([str(crown), 'parse-sql', str(path)], capture_output=True, text=True, timeout=60)
            require(result.returncode == 0 and not result.stderr, 'imported SQL parse failed: ' + query['label'])
            parsed = json.loads(result.stdout)
            require(parsed['syntax_valid'] and parsed['admission_status'] == 'not_checked' and parsed['source'] == sql, 'parser result changed scope/source')
            aggregates = [node['FuncCall']['funcname'][-1]['String']['sval'] for node in walk(parsed['ast'])
                          if 'FuncCall' in node and node['FuncCall'].get('funcname') and
                          node['FuncCall']['funcname'][-1]['String']['sval'] in ['count', 'sum', 'max']]
            require(aggregates, 'aggregate query was silently replaced with set enumeration')
            atoms, actual = equality_body(parsed['ast'])
            expected = [((atom.get('alias') or atom['table']).lower(), atom['table'].lower()) for atom in query['occurrences']]
            require(atoms == expected and actual == declared, 'imported occurrence/body classification mismatch')
            parsed_count += 1
    require(cyclic == ['DUMBBELL', 'TPCH-Q5'], 'cyclic imported cases changed')
    require(all(not record['available'] and not record['native_timing_eligible'] and record['bytes_sha256'] is None and record['license'] is None
                for record in packet['data_records']), 'unverified external dataset made runnable')
    return {'source_queries': len(queries), 'original_aggregate_queries': 24, 'acyclic_equality_bodies': 22,
            'cyclic_equality_bodies': cyclic, 'parsed_and_shape_checked': parsed_count, 'native_R1_timing_eligible': 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, required=True)
    parser.add_argument('--crown', type=Path)
    args = parser.parse_args(); source = args.source.resolve()
    packet = json.loads((source / 'benchmarks/legacy/dynagox/manifest.json').read_text())
    result = verify(source, packet, args.crown.resolve() if args.crown else None)
    mutations = []
    bad = copy.deepcopy(packet); bad['queries'][0]['native_run_eligible'] = True; mutations.append(bad)
    bad = copy.deepcopy(packet); bad['data_records'][0]['available'] = True; mutations.append(bad)
    bad = copy.deepcopy(packet); bad['source_documents'][0]['git_blob_sha1'] = '0' * 40; mutations.append(bad)
    bad = copy.deepcopy(packet); bad['queries'][0]['sql'] = copy.deepcopy(packet['queries'][1]['sql']); mutations.append(bad)
    for bad in mutations:
        try: verify(source, bad)
        except ValueError: pass
        else: raise ValueError('invalid source pin/SQL/data/native eligibility metadata accepted')
    result['invalid_metadata_rejected'] = len(mutations)
    print('B02 imported sources PASS ' + json.dumps(result, sort_keys=True))


if __name__ == '__main__':
    try: main()
    except Exception as error:
        print('B02 imported-source verification failed: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
