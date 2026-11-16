from pathlib import Path
import json,re
H=Path(__file__).resolve().parent;R=H.parents[2];D={}
def obj(props):return {'type':'object','properties':props,'required':list(props),'additionalProperties':False}
def arr(item):return {'type':'array','items':item}
def ref(name):return {'$ref':'#/$defs/'+name}
def nullable(value):return {'anyOf':[value,{'type':'null'}]}
def enum(*values):return {'enum':list(values)}
def const(value):return {'const':value}
u={'type':'integer','minimum':0,'maximum':18446744073709551615};b={'type':'boolean'};s={'type':'string'};n={'type':'null'}
scalar_types=enum('int64','string','bool','date','decimal')
D['scalar']={'oneOf':[obj({'type':const(t),'value':v}) for t,v in [('int64',{'type':'integer','minimum':-9223372036854775808,'maximum':9223372036854775807}),('string',s),('bool',b),('date',s),('decimal',s)]]}
D['term']={'oneOf':[obj({'kind':const('variable'),'variable':u}),obj({'kind':const('constant'),'constant':ref('scalar')}),obj({'kind':const('ignored_column')})]}
D['decimal']=obj({'precision':u,'scale':u})
D['column']=obj({'name':s,'type':scalar_types,'nullable':b,'collation':const('binary'),'decimal':nullable(ref('decimal'))})
base={'name':s,'status':enum('enforced','untrusted'),'columns':arr(u)}
D['constraint']={'oneOf':[obj({'kind':const('unique'),**base}),obj({'kind':const('foreign_key'),**base,'referenced_table':u,'referenced_columns':arr(u)})]}
D['table']=obj({'name':s,'source_schema_version':u,'columns':arr(ref('column')),'constraints':arr(ref('constraint')),'statistics':obj({'row_count':nullable(u),'distinct_counts':arr(obj({'columns':arr(u),'estimate':u}))}),'key_hints':arr(obj({'columns':arr(u),'reason':s}))})
D['catalog']=obj({'version':u,'tables':arr(ref('table'))})
D['query']=obj({'contradiction':b,'variables':arr(obj({'name':s,'type':scalar_types})),'atoms':arr(obj({'occurrence':s,'table':u,'terms':arr(ref('term'))})),'head':arr(obj({'variable':u,'alias':s}))})
D['binding']=obj({'catalog':ref('catalog'),'query':ref('query')})
D['tree']=obj({'root':nullable(u),'claimed_connex':nullable(arr(u)),'claimed_native_height':nullable(u),'nodes':arr(obj({'id':s,'kind':enum('native','generalized'),'scope':arr(u),'children':arr(u),'occurrence':nullable(u),'claimed_separator':nullable(arr(u))}))})
D['counters']=obj({**{k:u for k in ['attempted','committed_transitions','allocation_failures','active_nanoseconds','current_depth','peak_depth']},'active_nanoseconds_at_cap':b})
D['phase_limit']=obj({'work':nullable(u),'active_nanoseconds':nullable(u)})
D['search_limits']=obj({'producer':ref('phase_limit'),'replay':ref('phase_limit'),'logical_depth':nullable(u)})
D['replay_limits']=obj({'phase':ref('phase_limit'),'logical_depth':nullable(u)})
header=(R/'include/crown/planner/search.hpp').read_text()
def native_enum(typ):return enum(*re.findall(r'\b[a-z][a-z_]+\b',header.split('enum class '+typ+' {',1)[1].split('}',1)[0]))
stats=re.findall(r'(\w+)\s*=\s*0',(R/'include/crown/planner/oracle.hpp').read_text().split('struct SearchStatistics {')[1].split('};',1)[0]);D['statistics']=obj({k:u for k in stats})
stop_scope=const('owner_last_stop; nonmutating_zero_quantum_return_is_not_retained')
D['search']=obj({'policy':enum('strict','best_found'),'phase':native_enum('SearchPhase'),'recorded_last_stop':native_enum('StopReason'),'result_kind':native_enum('ResultKind'),'stop_scope':stop_scope,'observed_height_interval':obj({'lower':nullable(u),'upper':nullable(u),'lower_evidence':enum('universal','independently_checked'),'infeasible':b}),'producer_complete':b,'proof_complete':b,'limit_revision':u,'producer':ref('counters'),'replay':ref('counters'),'structural_counters':ref('statistics'),'limits':ref('search_limits')})
D['replay']=obj({'phase':native_enum('ReplayPhase'),'recorded_last_stop':native_enum('StopReason'),'complete':b,'valid':b,'checked_claims':u,'limit_revision':u,'work':ref('counters'),'claim_scope':const('unchecked_input_claim_details_not_exposed_until_checked_handle'),'stop_scope':stop_scope,'limits':ref('replay_limits')})
D['height']=obj({'status':enum('unknown','owner_checked_upper_unpublished','checked_upper','verified_optimum','verified_infeasible'),'lower':nullable(u),'upper':nullable(u),'lower_evidence':enum('typed_independent_proof','p06_universal_nonempty_or_empty_body_bound'),'upper_evidence':enum('typed_checked_original_witness','owner_observed_checked_upper_witness_unpublished','none'),'minimum_proven':b,'infeasible_proven':b,'witness_exportable':b})
D['witness']=obj({'authority':const('typed_validated_incumbent_exact_original_binding'),'height':u,'tree':ref('tree')})
D['certificate']=obj({'authority':const('typed_independently_checked_original_binding'),'algorithm':s,'minimum_height':nullable(u),'tree':nullable(ref('tree')),'lower_bounds':arr(obj({'occurrences':arr(u),'generalized_allowed':b,'connex_reachable':b,'bound':nullable(u)}))})
root=obj({'format':const('crown_query_explain'),'version':const(1),'source':enum('exact_search','certificate_replay','checked_upper','verified_optimum','verified_infeasible','checked_certificate'),'accounting':const('continuation_v1'),'binding':ref('binding'),'height':ref('height'),'search':nullable(ref('search')),'replay':nullable(ref('replay')),'witness':nullable(ref('witness')),'certificate':nullable(ref('certificate')),'recognized_class':obj({'status':const('not_collected'),'diagnostic_work':const(0),'reason':const('capture_does_not_run_recognizer_or_reclassify_producer_statistics')}),'cost':obj({'status':const('not_run'),'estimates':n,'statistics':const('not_collected'),'catalog_estimates':const('original_input_metadata_only'),'candidate_family_exhaustion':n}),'active_time_semantics':const('producer_recorded_active_time_excludes_pause; UINT64_MAX_may_be_capped_not_exact'),'proof_scope':const('original_structural_height_only; no_cost_optimum_runtime_or_durable_guarantee'),'structural_domain':const('original_CQ_atom_head_tree_family; contradiction_metadata_preserved; excludes_P08_constant_false_operator_shortcut'),'counter_scopes':const('producer_and_replay_attempted_are_separate_phases; structural.work_aliases_producer.attempted; structural.certificate_work_aliases_replay.attempted; transitions_not_additive_work')})
root['allOf']=[]
for status,wit,cert,lo,up,minp,infp in [('unknown',n,n,u,n,False,False),('owner_checked_upper_unpublished',n,n,u,u,False,False),('checked_upper',ref('witness'),n,u,u,False,False),('verified_optimum',ref('witness'),ref('certificate'),u,u,True,False),('verified_infeasible',n,ref('certificate'),n,n,False,True)]:
 root['allOf'].append({'if':{'properties':{'height':{'properties':{'status':const(status)}}}},'then':{'properties':{'witness':wit,'certificate':cert,'height':{'properties':{'lower':lo,'upper':up,'minimum_proven':const(minp),'infeasible_proven':const(infp),'witness_exportable':const(status in ['checked_upper','verified_optimum'])}}}}})
for source in ['exact_search','certificate_replay','checked_upper','verified_optimum','verified_infeasible','checked_certificate']:
 root['allOf'].append({'if':{'properties':{'source':const(source)}},'then':{'properties':{'search':ref('search') if source=='exact_search' else n,'replay':ref('replay') if source=='certificate_replay' else n}}})
for source,statuses in [('checked_upper',['checked_upper']),('verified_optimum',['verified_optimum']),('verified_infeasible',['verified_infeasible']),('checked_certificate',['verified_optimum','verified_infeasible'])]:
 root['allOf'].append({'if':{'properties':{'source':const(source)}},'then':{'properties':{'height':{'properties':{'status':enum(*statuses)}}}}})
common={'$schema':'https://json-schema.org/draft/2020-12/schema','$comment':'Shape contract only. JSON/flags never mint typed planner authority; source accessors and independent semantic checks remain necessary.','additionalProperties':False}
folder=H/'schemas';folder.mkdir(exist_ok=True)
(folder/'query-explain-v1.schema.json').write_text(json.dumps({**common,'title':'Owned query/search EXPLAIN v1',**root,'$defs':D},indent=2)+'\n')
witness=obj({'format':const('crown_query_witness'),'version':const(1),'authority':const('typed_checked_original_witness'),'height':u,'binding':ref('binding'),'tree':ref('tree')})
(folder/'query-witness-v1.schema.json').write_text(json.dumps({**common,'title':'Original typed checked witness export v1',**witness,'$defs':D},indent=2)+'\n')
