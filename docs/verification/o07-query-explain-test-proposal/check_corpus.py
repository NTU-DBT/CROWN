#!/usr/bin/env python3
"""Offline schema + independent semantic checks. Root runs this; author does not.
Requires installed jsonschema. No network, subprocess, report authority import,
or producer advancement. A schema pass never manufactures a typed proof.
"""
import argparse
import copy
import json
from pathlib import Path
import re
from jsonschema import Draft202012Validator

HERE = Path(__file__).resolve().parent
PACKAGE = HERE.parent / 'o07-query-explain-proposal'
STATES = ['unknown', 'owner_checked_upper_unpublished', 'checked_upper', 'verified_optimum', 'verified_infeasible']
SOURCES = ['exact_search', 'certificate_replay', 'checked_upper', 'verified_optimum', 'verified_infeasible', 'checked_certificate']
def require(ok, message):
    if not ok:
        raise AssertionError(message)
def pairs(items):
    out = {}
    for key, value in items:
        require(key not in out, 'duplicate JSON object key')
        out[key] = value
    return out
def load(path):
    return json.loads(path.read_text(encoding='utf-8'), object_pairs_hook=pairs,
                      parse_constant=lambda x: (_ for _ in ()).throw(AssertionError('nonfinite JSON ' + x)))
def maybe(x):
    return None if x == 'null' else int(x)
def texthex(x):
    return '' if x == '-' else bytes.fromhex(x).decode('utf-8')
def native_expected(path, report):
    lines = iter(path.read_text().splitlines())
    first = next(lines).split()
    require(report['height']['status'] == STATES[int(first[1])], 'status differs from typed native accessor')
    require(report['source'] == SOURCES[int(first[3])], 'source differs from native accessor')
    require(report['height']['lower'] == maybe(first[5]) and report['height']['upper'] == maybe(first[7]), 'bounds differ from native accessors')
    nodes = []; claims = []; expected_count = None; claim_count = None
    for line in lines:
        fields = iter(line.split()); kind = next(fields)
        if kind == 'tree':
            tree = report['witness']['tree']
            require(tree['root'] == maybe(next(fields)), 'native root altered')
            require(tree['claimed_native_height'] == maybe(next(fields)), 'native height claim altered')
            expected_count = int(next(fields))
        elif kind == 'connex':
            first = next(fields)
            ids = None if first == 'null' else [int(next(fields)) for _ in range(int(first))]
            require(report['witness']['tree']['claimed_connex'] == ids, 'native connex claim altered')
        elif kind == 'node':
            label = texthex(next(fields)); nodekind = ['native', 'generalized'][int(next(fields))]; occurrence = maybe(next(fields))
            scope = [int(next(fields)) for _ in range(int(next(fields)))]; children = [int(next(fields)) for _ in range(int(next(fields)))]
            first = next(fields); separator = None if first == 'null' else [int(next(fields)) for _ in range(int(first))]
            nodes.append(dict(id=label, kind=nodekind, occurrence=occurrence, scope=scope, children=children, claimed_separator=separator))
        elif kind == 'certificate':
            c = report['certificate']; require(c['algorithm'] == texthex(next(fields)), 'native proof algorithm altered')
            require(c['minimum_height'] == maybe(next(fields)), 'native proof height altered'); claim_count = int(next(fields))
        elif kind == 'claim':
            generalized = bool(int(next(fields))); reachable = bool(int(next(fields))); bound = maybe(next(fields)); occurrences = [int(next(fields)) for _ in range(int(next(fields)))]
            claims.append(dict(generalized_allowed=generalized, connex_reachable=reachable, bound=bound, occurrences=occurrences))
        elif kind in ('producer', 'search_replay', 'replay'):
            c = report['replay']['work'] if kind == 'replay' else report['search']['producer' if kind == 'producer' else 'replay']
            keys = ['attempted', 'committed_transitions', 'allocation_failures', 'active_nanoseconds', 'current_depth', 'peak_depth']
            require([c[k] for k in keys] == [int(v) for v in fields], 'native work counters altered')
        else:
            raise AssertionError('unknown native sidecar record')
    if expected_count is not None:
        require(len(nodes) == expected_count and nodes == report['witness']['tree']['nodes'], 'native tree claims changed')
    if claim_count is not None:
        require(len(claims) == claim_count and claims == report['certificate']['lower_bounds'], 'native lower-bound claims changed')
def tree_semantics(t, binding, expected_height):
    nodes=t['nodes']; root=t['root']; atoms=binding['query']['atoms']; variables=binding['query']['variables']
    if not nodes:
        require(root is None and not atoms and expected_height == 0, 'fabricated empty witness')
        return
    require(type(root) is int and 0 <= root < len(nodes), 'root out of range')
    seen=set(); occurrences=[]; parent={root: None}; maximum=0
    stack=[(root, 0)]
    while stack:
        index, height=stack.pop(); require(index not in seen, 'cycle/duplicate child'); seen.add(index)
        n=nodes[index]; scope=set(n['scope']); require(len(scope)==len(n['scope']) and all(0<=x<len(variables) for x in scope), 'scope IDs')
        if n['kind']=='native':
            occurrence=n['occurrence']; require(type(occurrence) is int and 0<=occurrence<len(atoms), 'occurrence reference')
            occurrences.append(occurrence); native={x['variable'] for x in atoms[occurrence]['terms'] if x['kind']=='variable'}
            require(scope==native, 'native scope differs from atom'); height+=1
        else:
            require(n['occurrence'] is None, 'generalized occurrence'); require(len(n['children'])>=2, 'unreduced generalized node')
        maximum=max(maximum,height)
        for child in n['children']:
            require(type(child) is int and 0<=child<len(nodes) and child not in parent, 'bad child reference/multiple parent')
            parent[child]=index; stack.append((child,height))
    require(len(seen)==len(nodes), 'unreachable node')
    require(sorted(occurrences)==list(range(len(atoms))), 'missing/duplicate native occurrence')
    require(maximum==expected_height, 'computed native height differs from typed height')
    # Running intersection is checked independently over the exported graph.
    for variable in range(len(variables)):
        owning={i for i,n in enumerate(nodes) if variable in n['scope']}
        if not owning: continue
        work=[next(iter(owning))]; connected=set()
        while work:
            i=work.pop()
            if i in connected: continue
            connected.add(i)
            adjacent=nodes[i]['children']+[parent[i]]
            work.extend(x for x in adjacent if x in owning and x not in connected)
        require(connected==owning, 'running-intersection violation')
    if t['claimed_connex'] is not None:
        require(all(0<=i<len(nodes) for i in t['claimed_connex']), 'connex reference')
def semantics(r, base, tree_validator):
    h=r['height']; status=h['status']; w=r['witness']; c=r['certificate']; s=r['search']; replay=r['replay']
    require(r['recognized_class']['status']=='not_collected' and r['recognized_class']['diagnostic_work']==0, 'hidden recognition')
    require(r['cost']['status']=='not_run' and r['cost']['estimates'] is None and r['cost']['candidate_family_exhaustion'] is None, 'invented cost authority')
    require(h['minimum_proven']==(status=='verified_optimum') and h['infeasible_proven']==(status=='verified_infeasible'), 'authority flags')
    require(h['witness_exportable']==(w is not None), 'exportability mismatch')
    require((s is not None)==(r['source']=='exact_search') and (replay is not None)==(r['source']=='certificate_replay'), 'source/progress mismatch')
    if status=='verified_optimum':
        require(w is not None and c is not None and h['lower']==h['upper']==w['height']==c['minimum_height'], 'optimum binding heights')
        require(c['tree']==w['tree'], 'proof/witness tree mismatch')
    elif status=='verified_infeasible':
        require(w is None and c is not None and c['tree'] is None and c['minimum_height'] is None and h['lower'] is None and h['upper'] is None, 'negative authority')
    else:
        require(c is None, 'unproven certificate exposed')
        require(h['lower']==(1 if r['binding']['query']['atoms'] else 0), 'universal lower changed')
    if status=='unknown': require(w is None and h['upper'] is None, 'unknown upper')
    if status=='owner_checked_upper_unpublished': require(w is None and s['policy']=='strict' and h['upper'] is not None, 'hidden upper tree exposure')
    if s:
        require(s['structural_counters']['work']==s['producer']['attempted'] and s['structural_counters']['certificate_work']==s['replay']['attempted'], 'counter alias mismatch')
        if not s['proof_complete']: require(status not in ('verified_optimum','verified_infeasible'), 'premature publication')
    if replay and not replay['valid']: require(c is None and w is None, 'invalid/partial replay minted evidence')
    for counters in ([s['producer'],s['replay']] if s else [])+([replay['work']] if replay else []):
        require(counters['committed_transitions']<=counters['attempted'] and counters['current_depth']<=counters['peak_depth'], 'counter inequalities')
        require(counters['active_nanoseconds_at_cap']==(counters['active_nanoseconds']==2**64-1), 'cap diagnostic')
    txt=base.with_suffix('.txt').read_text(encoding='utf-8')
    require('Structural height: '+status+';' in txt, 'human status mismatch')
    if w:
        tree=load(base.with_suffix('.tree.json'));tree_validator.validate(tree)
        require(tree['binding']==r['binding'] and tree['tree']==w['tree'] and tree['height']==w['height'], 'tree export lost exact binding')
        tree_semantics(w['tree'],r['binding'],w['height'])
        dot=base.with_suffix('.dot').read_text(encoding='utf-8')
        ids=[int(x) for x in re.findall(r'^  n(\d+) \[label=',dot,re.M)]
        edges=[tuple(map(int,x)) for x in re.findall(r'^  n(\d+) -> n(\d+);$',dot,re.M)]
        require(ids==list(range(len(w['tree']['nodes']))), 'DOT node IDs')
        require(edges==[(i,c) for i,n in enumerate(w['tree']['nodes']) for c in n['children']], 'DOT edges')
    else:
        require(not base.with_suffix('.tree.json').exists() and not base.with_suffix('.dot').exists(), 'fabricated tree files')
    if 'metadata-' in base.name:
        catalog=r['binding']['catalog'];q=r['binding']['query'];t=catalog['tables'][1]
        require(catalog['version']==19 and t['source_schema_version']==23 and t['name']=='child\0"\\\n', 'metadata text/version roundtrip')
        require(t['statistics']['row_count']==2**64-1 and t['statistics']['distinct_counts']==[{'columns':[1,0],'estimate':123456}], 'exact unsigned metadata')
        require(t['constraints'][0]==dict(kind='foreign_key',name='fk',status='enforced',columns=[0],referenced_table=0,referenced_columns=[0]), 'FK roundtrip')
        require(t['constraints'][1]['status']=='untrusted' and t['key_hints'][0]['reason']=='hint\0reason', 'status/hint roundtrip')
        require(t['columns'][4]['decimal']==dict(precision=38,scale=6) and all(not x['nullable'] and x['collation']=='binary' for x in t['columns']), 'column metadata')
        require(q['variables']==[dict(name='v\0name',type='int64')] and q['atoms'][0]['occurrence']=='a\0"\\\n\0' and q['atoms'][0]['table']==1, 'exact variable/occurrence binding')
        constants=[x.get('constant') for x in q['atoms'][0]['terms']]
        require(constants[1:5]==[dict(type='string',value='str\0"\\\n'),dict(type='bool',value=True),dict(type='date',value='0001-01-01'),dict(type='decimal',value='-123456789012345678901234567890.123456')], 'scalar tagging/exact values')
        require(constants[6]==dict(type='int64',value=-(2**63)), 'signed scalar minimum')
        require(q['head']==[dict(variable=0,alias='duplicate')]*2 and q['atoms'][0]['terms'][5]['kind']=='ignored_column', 'ordered duplicate output/ignored term')

def main():
    parser=argparse.ArgumentParser();parser.add_argument('corpus',type=Path);parser.add_argument('--require-all',action='store_true');a=parser.parse_args()
    schema=load(PACKAGE/'schemas/query-explain-v1.schema.json');tree_schema=load(PACKAGE/'schemas/query-witness-v1.schema.json')
    Draft202012Validator.check_schema(schema);Draft202012Validator.check_schema(tree_schema)
    validator=Draft202012Validator(schema);tree_validator=Draft202012Validator(tree_schema)
    paths=sorted(a.corpus.rglob('*.report.json'));require(bool(paths),'empty corpus')
    statuses=set();sources=set();stops=set();groups=set();family_search=family_replay=0
    for path in paths:
        r=load(path);validator.validate(r);base=path.with_name(path.name.removesuffix('.report.json'))
        native_expected(base.with_suffix('.expected'),r);semantics(r,base,tree_validator)
        statuses.add(r['height']['status']);sources.add(r['source'])
        for key in ('search','replay'):
            if r[key]: stops.add(r[key]['recorded_last_stop'])
        if 'family-search' in path.name:family_search+=1
        if 'family-replay' in path.name:family_replay+=1
        for name in ('metadata','allocation','internal-failed','cancel','invalid-replay','post-upper-time'):
            if name in path.name:groups.add(name)
        bad=copy.deepcopy(r);bad['caller_editable_authority']=True
        require(not validator.is_valid(bad),'schema accepted undeclared authority field')
        if r['height']['status']=='unknown':
            bad=copy.deepcopy(r);bad['height']['minimum_proven']=True
            require(not validator.is_valid(bad),'schema accepted forged minimum flag')
    if a.require_all:
        require(statuses==set(STATES),'missing height status family')
        require(sources==set(SOURCES),'missing typed source family')
        require({'total_work','total_time','depth_limit','quantum_time','cancelled','allocation_failure','internal_failure'}<=stops,'missing actual stop family')
        require({'metadata','allocation','internal-failed','cancel','invalid-replay','post-upper-time'}<=groups,'missing mandatory groups')
        # All 437 run twice. The single raw byte anchor cannot be JSON exported.
        require(family_search==872 and family_replay==872,'426+11 finite family corpus is incomplete')
    print(json.dumps(dict(status='PASS',reports=len(paths),statuses=sorted(statuses),sources=sorted(sources),stops=sorted(stops),family_search=family_search,family_replay=family_replay),indent=2))
if __name__=='__main__':main()
