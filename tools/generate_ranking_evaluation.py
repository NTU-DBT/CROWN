#!/usr/bin/env python3
"""Disjoint finite C07 traces with independent relational/SQLite result oracles."""
from __future__ import annotations
import argparse
import collections
import copy
import hashlib
import json
from pathlib import Path
import sys
sys.dont_write_bytecode=True
from generate_workloads import canonical,oracle,specifications

ROOT=Path(__file__).resolve().parents[1]
DEFAULT_QUERIES=['boolean_path','full_star_3','composite_separator']
SCENARIOS=[('train','train',3,0),('calibration','calibration',4,0),
           ('evaluation_in_distribution','evaluation',4,0),
           ('evaluation_rate_shift','evaluation',4,-1),
           ('evaluation_fanout_shift','evaluation',8,-1)]
def require(value,message):
    if not value:raise ValueError(message)
def sha(value):return hashlib.sha256(value).hexdigest()
def rows_for(spec,seed,split_index,fanout):
    # Distinct value domains, including separator keys, make physical tuples
    # disjoint across every split, not merely differently named source feeds.
    offset=(seed%1000000)*1000000+split_index*10000
    hot=set(spec['hot'])
    if spec['id']=='boolean_path':hot.update(['x1','x2'])
    result={}
    for table_index,atom in enumerate(spec['atoms']):
        require(atom['table'] not in result,'C07 generator currently requires distinct physical tables')
        values=[]
        for row in range(fanout+table_index):
            values.append(tuple(offset+(0 if variable in hot else row+100*spec['variables'].index(variable)) for variable in atom['variables']))
        # A table with only separator fields can collapse by set semantics.
        result[atom['table']]=list(dict.fromkeys(values))
    return result
def make_trace(spec,seed,split_index,fanout,hot_index):
    pools=rows_for(spec,seed,split_index,fanout);tables=list(pools);hot=tables[hot_index]
    entries=[(table,row) for table,rows in pools.items() for row in rows]
    entries.sort(key=lambda item:sha(f'{seed}:{split_index}:{canonical(item)}'.encode()))
    events=[('insert',table,list(row),'charged_load') for table,row in entries]
    for phase,table in [('hot_relation',hot),('within_trace_shift',tables[(tables.index(hot)+1)%len(tables)])]:
        repeats=16 if phase=='hot_relation' else 4
        choices=sorted(pools[table],key=lambda row:sha(f'{seed}:{phase}:{canonical(row)}'.encode()))
        for index in range(repeats):
            row=choices[index%len(choices)]
            events.extend([('delete',table,list(row),phase),('insert',table,list(row),phase)])
    # Exact input attempts include no-ops; they are not silently discarded from
    # C02 weights or the measured workload horizon.
    for _ in range(8):events.append(('insert',hot,list(pools[hot][0]),'duplicate_insert'))
    require(len(events)<=4096,'C07 event grant exceeded')
    return pools,events
def build(seed=20261111,selected=None):
    require(isinstance(seed,int) and not isinstance(seed,bool) and 0<=seed<2**32,'invalid split seed')
    selected=DEFAULT_QUERIES if selected is None else selected
    require(selected and len(selected)==len(set(selected)) and set(selected)<=set(DEFAULT_QUERIES),'unknown/duplicate C07 query selection')
    specs={s['id']:s for s in specifications()};files={};queries=[];traces=[]
    def put(path,value,raw=False):
        data=(value if raw else json.dumps(value,ensure_ascii=False,sort_keys=True,indent=2)+'\n').encode();files[path]=data
        return {'path':path,'sha256':sha(data),'bytes':len(data)}
    for name in selected:
        spec=copy.deepcopy(specs[name]);prefix='queries/'+name+'/'
        queries.append({'id':name,'sql':put(prefix+'query.sql',spec['sql'],True),'catalog':put(prefix+'catalog.json',spec['catalog']),
                        'semantics':'exact_physical_set_and_SQL_DISTINCT_or_EXISTS','head':spec['head'],'atoms':spec['atoms'],
                        'origin':'B02_SQL_and_catalog_with_new_disjoint_C07_data','structure_tags':spec['tags']})
        domains=[];semantic_hashes=[]
        for index,(scenario,role,fanout,hot_index) in enumerate(SCENARIOS):
            pools,events=make_trace(spec,seed,index,fanout,hot_index);expected=oracle(spec,events)
            physical={(table,tuple(row)) for table,rows in pools.items() for row in rows}
            require(all(not(physical&other) for other in domains),'split physical tuples overlap');domains.append(physical)
            semantic=sha(canonical([(op,table,values) for op,table,values,_ in events]).encode());require(semantic not in semantic_hashes,'split event content is duplicated');semantic_hashes.append(semantic)
            identifier=name+'/'+scenario;source='c07-'+sha(identifier.encode())[:24]
            records=[{'schema_version':1,'catalog_version':1,'source_schema_version':1,'sequence':n,'table':table,'operation':operation,'values':values,'source_position':{'source':source,'offset':n}}
                     for n,(operation,table,values,_) in enumerate(events,1)]
            prefix='traces/'+identifier+'/'
            traces.append({'id':identifier,'query':name,'role':role,'scenario':scenario,
                           'events':put(prefix+'events.template.jsonl',''.join(canonical(r)+'\n' for r in records),True),
                           'oracle':put(prefix+'expected.json',expected),'events_count':len(records),
                           'semantic_events_sha256':semantic,'source_id':source,'initial_state':'empty_all_tables',
                           'phase_labels':list(dict.fromkeys(e[3] for e in events)),'charged_load_events':len(physical),
                           'configured_fanout':fanout,'physical_rows_by_table':{t:len(rows) for t,rows in pools.items()},
                           'hot_table':list(pools)[hot_index],'input_attempts_by_table':dict(collections.Counter(e[1] for e in events)),
                           'max_result_rows':max([len(expected['initial_rows']),*(len(e['current_rows']) for e in expected['epochs'])]),
                           'update_contract':'ordered_atomic_physical_set_insert_delete_with_committed_noops',
                           'shift_scope':'relation_update_mix_and_data_degree_not_wall_clock_arrival_Hz'})
    manifest={'schema_version':1,'kind':'c07_ranking_trace_split','generator':{'path':'tools/generate_ranking_evaluation.py','sha256':sha(Path(__file__).read_bytes()),'seed':seed,'query_ids':selected},
              'oracle_implementation':{'path':'tools/generate_workloads.py','sha256':sha((ROOT/'tools/generate_workloads.py').read_bytes()),'algorithm':'independent_assignment_and_SQLite_after_every_physical_event'},
              'queries':queries,'traces':traces,'split_contract':{'unit':'physical_trace','training':'only_train_trace_is_visible_to_C05_choices_and_proxy_features',
                'calibration':'separate_rows_and_trace_for_explicit_evaluation_layer_proxy_to_cost_mapping_only',
                'evaluation':'three_disjoint_traces_never_used_for_choice_or_coefficient_fitting',
                'physical_tuple_overlap_allowed':False,'semantic_trace_duplicates_allowed':False,
                'query_family_holdout':False,'shared_SQL':'same_query_family_to_test_statistical_transfer_across_fresh_data_and_update_mix'},
              'license':{'origin':'new_local_synthetic_data','project_license':'A02_undecided_local_development_only','redistribution':'not_authorized_by_this_manifest'},
              'limits':['finite_synthetic_traces_not_all_query_or_scale_coverage','one_deterministic_trace_per_scenario_not_independent_statistical_replicates','high_fanout_is_an_explicit_bounded_stress_not_B05_scalability_evidence','candidate_counts_and_family_completion_must_be_observed_from_native_exporter','all_loading_is_charged_from_empty']}
    put('manifest.json',manifest);return files
def verify(source,pack):
    manifest=json.loads((pack/'manifest.json').read_text());require(manifest['schema_version']==1 and manifest['kind']=='c07_ranking_trace_split','unknown split manifest')
    expected=build(manifest['generator']['seed'],manifest['generator']['query_ids'])
    actual={str(p.relative_to(pack)):p.read_bytes() for p in pack.rglob('*') if p.is_file()}
    require(actual==expected,'C07 split bytes differ from deterministic independent generation')
    require(source.resolve()==ROOT,'split verification must use the actual generator source root')
    return manifest,{'queries':len(manifest['queries']),'traces':len(manifest['traces']),'physical_events':sum(t['events_count'] for t in manifest['traces']),'split_disjoint':True,'independent_oracles':'relational_and_SQLite','sha256':sha((pack/'manifest.json').read_bytes())}
def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--seed',type=int,default=20261111);parser.add_argument('--query',action='append');group=parser.add_mutually_exclusive_group(required=True);group.add_argument('--output',type=Path);group.add_argument('--check',type=Path);args=parser.parse_args()
    if args.check:
        _,result=verify(ROOT,args.check.resolve());print(json.dumps(result,sort_keys=True));return
    files=build(args.seed,args.query);args.output.mkdir(parents=True,exist_ok=False)
    for relative,data in files.items():
        path=args.output/relative;path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
    print(f'C07 split generated: {len(files)} files; disjoint training/calibration/three evaluation traces per query.')
if __name__=='__main__':
    try:main()
    except Exception as error:print(str(error),file=sys.stderr);raise SystemExit(1)
