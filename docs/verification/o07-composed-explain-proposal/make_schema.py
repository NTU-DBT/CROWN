#!/usr/bin/env python3
"""Closed final transport schemas. Flags are diagnostics, never proof admission."""
from pathlib import Path
import copy,json
H=Path(__file__).resolve().parent
U={'type':'integer','minimum':0,'maximum':18446744073709551615};S={'type':'string'};B={'type':'boolean'};N={'type':'null'}
def c(v):return {'const':v}
def e(*v):return {'enum':list(v)}
def nullable(v):return {'anyOf':[v,N]}
def arr(v):return {'type':'array','items':v}
def obj(**p):return {'type':'object','properties':p,'required':list(p),'additionalProperties':False}
def ref(n):return {'$ref':'#/$defs/'+n}
def imported(path,prefix):
 s=json.loads(path.read_text());defs=s.pop('$defs',{});s.pop('$schema',None);s.pop('$id',None)
 def walk(v):
  if isinstance(v,dict):return {k:('#/$defs/'+prefix+x[len('#/$defs/'):] if k=='$ref' and x.startswith('#/$defs/') else walk(x)) for k,x in v.items()}
  if isinstance(v,list):return [walk(x) for x in v]
  return v
 return walk(s),{prefix+k:walk(v) for k,v in defs.items()}
physical,D=imported(H.parent/'o07-explain-proposal/schemas/explain-report-v1.schema.json','p_')
query,qd=imported(H.parent/'o07-query-explain-proposal/schemas/query-explain-v1.schema.json','q_');D.update(qd)
# Local component shape definitions; every object is closed.
D['measurement']={'oneOf':[obj(availability=c('available'),value=U,saturated=B),obj(availability=e('unavailable','disabled'),value=N,saturated=N)]}
D['observation_options']=obj(mode=e('off','counters','timed','trace'),trace_capacity=U,sample_period=U,sample_offset=U,trace_timings=B)
mode=e('maintenance','delta');completion=e('automatic','ordered_replay','anchored','root_first');view=e('core','sql')
D['flat_delta']=obj(requested_mode=mode,requested_completion=completion,live_maintenance=e('on_output','incremental','eager'),view=view,work_limit=nullable(U),cursor_work_limit=nullable(U),epoch_view_work_limit=nullable(U),spool_rows=U,spool_accounted_bytes=U,physical_work_limit=nullable(U),derivation_limit=U,support_work_limit=nullable(U),support_limit=U,propagation_order=e('fifo','lifo'),capture_transitions=B,observation=ref('observation_options'))
D['initialization']=obj(provenance=c('recorded_successful_construction'),route=e('empty_constructor','initialized_database','rebuilt_snapshot'),applied_build=nullable(obj(method=e('direct','insertion_replay'),work_limit=nullable(U))))
D['declared']=obj(provenance=c('caller_declared_unmeasured'),authority=c('none'),**{k:nullable(S) for k in ['run','input_adapter','output_codec','sink']})
D['output_disposition']=obj(provenance=c('observed_attempt_actions'),initial_retention=c('retain'),**{k:B for k in ['discard_drain_requested','completion_drain_invoked','retention_disabled','prepared','published','released','transferred','serialization_invoked','sink_invoked','unread_discarded']})
D['attempt_context']=obj(attempt=U,sequence=U,scope=c('attempt_begin_context_and_actual_output_lifecycle'),initialization=nullable(ref('initialization')),declared_benchmark=nullable(ref('declared')),configuration_owner=nullable(U),configuration_generation=nullable(U),configuration_generation_saturated=nullable(B),output=nullable(ref('output_disposition')))
D['input_options']=obj(format=e('jsonl','binary','csv','legacy_signed','legacy_relations','legacy_insert_only','legacy_flags','legacy_timestamp_flags'),table=nullable(U),delimiter_byte={'type':'integer','minimum':0,'maximum':255},header=B,csv_operation=e('insert','erase'),relation_tokens=arr(obj(token=S,table=U)),null_token=nullable(S),source=nullable(S),byte_offset=U,limits=obj(record_bytes=U,field_bytes=U,columns=U,source_bytes=U,sources=U,total_bytes=nullable(U),records=nullable(U)))
D['session_context']=obj(provenance=c('recorded_session_admission'),input_kind=e('owned_stream','typed_physical','typed_window'),wire_format_scope=e('applied_to_owned_stream','not_applicable_typed_input'),input_options=ref('input_options'),queue=nullable(obj(batches=U,events=U,accounted_bytes=U)),window=nullable(obj(managed_tables=arr(U),width=U,fifo=e('global','per_relation'),max_labels=U,max_accounted_bytes=U,command_work_limit=U)),snapshot=obj(rows=U,accounted_bytes=U,cursor_work_limit=nullable(U)),initialization=ref('initialization'),requested_delta=ref('flat_delta'),resolved_mode=mode,resolved_completion=completion)
D['run_context']=obj(format=c('crown_run_context'),version=c(1),scope=c('diagnostic_metadata_companion_to_explain'),missing_identity=c('null_not_inferred'),external_callback_identity=c('caller_declarations_do_not_identify_or_validate_std_function_targets'),external_guarantees=c('unmeasured_no_durability_or_recovery_claim'),accounted_byte_scope=c('component_payload_accounting_excludes_allocator_overhead_transients_and_metadata_not_total_memory'),current_initialization=nullable(ref('initialization')),current_declared_benchmark=nullable(ref('declared')),session=nullable(ref('session_context')),current_attempt=nullable(ref('attempt_context')),last_attempt=nullable(ref('attempt_context')))
D['cursor_work']=obj(**{k:U for k in 'work calls route_checks descriptor_steps frame_initializations cursor_opens cursor_advances frame_closes tuple_lookups selected_rows bucket_lookups key_fields equality_checks output_fields rows_emitted binding_checks binding_rejections direct_lookups overlay_rows fragment_steps binding_values witness_probes witness_rows join_rejections'.split()})
D['cursor_configuration']=obj(provenance=c('cursor_begin_runtime_configuration'),owner=U,generation=U,generation_saturated=B,mode=mode,completion=completion,query_factors=U,requested_options=ref('flat_delta'))
D['cursor']=obj(format=c('crown_cursor_observation'),version=c(1),scope=c('one_cursor_lifetime_not_delta_output_spooling'),owner=U,sequence=U,cursor_id=nullable(U),cursor_id_saturated=nullable(B),constructed=B,source=e('committed_results','epoch_visible','epoch_witnesses','epoch_keys','epoch_bucket'),view=view,side=nullable(e('before','after')),tentative_at_creation=B,state=e('active','exhausted','cancelled','failed'),terminal_reason=e('not_recorded','none','exhausted','explicit_cancel','destruction','move_replacement','invalidated','startup_failure','next_failure'),cursor_work_limit=nullable(U),configuration=nullable(ref('cursor_configuration')),timing_partition=c('startup_then_disjoint_successful_exhausted_failed_calls_and_cleanup; excludes_caller_pause; failed_startup_includes_unwinding'),observation_options=ref('observation_options'),sampling_scope=c('per_cursor_counters_and_timings_are_not_per_update_trace_sampling'),metrics=arr(obj(id=U,name=S,unit=S,scope=S,kind=e('counter','high_water','timing'),measurement=ref('measurement'))),mandatory=obj(total_work=U,max_result_work=U,cleanup_frames=U,work_unit=c('existing_abstract_cursor_actions'),last_scope=c('last_active_call_already_in_results_termination_or_failed_not_additive'),**{k:ref('cursor_work') for k in ['startup','results','termination','failed','last']}))
D['gauges']=obj(format=c('crown_committed_state_gauges'),version=c(1),owner=U,sequence=U,scope=c('explicit_committed_state_read_available_with_telemetry_off'),cardinality_unit=c('tuples_or_distinct_keys_as_named'),visible_scope=c('per_node_E_factor_assignments_not_full_join_output_count'),base_tuples=ref('measurement'),bases=arr(obj(table=U,tuples=U)),nodes=arr(obj(node=U,kind=e('native','generalized'),records=U,survivors=U,projected_parent_keys=U,visible_factor_assignments=ref('measurement'))),**{k:ref('measurement') for k in ['full_result_count','allocated_bytes','live_bytes','checkpoint_bytes','checkpoint_ns','recovery_replay_length']},limitations=c('no_total_memory_or_durable_recovery_claim; allocating_snapshot_metadata_not_an_update_charge'))
D['session_status']=obj(state=e('created','running','paused','stopped','dropped'),phase=e('ready','pending','paused_pending','draining','prepared','output'),committed_sequence=U,input_failed=B,end_of_input=B,pending_sequence=nullable(U),pending_work=U,output_remaining=U,pending_command_sequence=nullable(U),queue_availability=e('available','released','not_applicable'),queue=nullable(obj(batches=U,events=U,accounted_bytes=U,closed=B,failed=B)),window_availability=e('available','released','not_applicable'),window=nullable(obj(completed_command_sequence=U,physical_sequence=U,completed_watermark=U,last_label=U,active_command_sequence=nullable(U),completed_steps=U,total_steps=U)),binding=c('actual_owning_session_metadata; no_supplied_plan_or_hash_join'))
for field in ['queue','window']:
 D['session_status'].setdefault('allOf',[]).append({'if':{'properties':{field+'_availability':c('available')}},'then':{'properties':{field:{'not':N}}},'else':{'properties':{field:N}}})
P=physical['properties'];P['schema_version']=c(2);P['kind']=e('physical','runtime','session');P['structure']['properties']['height_domain']=e('executable_operator','validated_query_tree');P['structure']['required'].append('height_domain')
height=D['p_height'];hp=height['properties'];hp['status']=e('checked_upper','verified_original_minimum','checked_constant_operator');hp['scope']=e('original_core_query','p08_constant_false_operator_not_original_CQ_structural_minimum');hp['original_upper']=nullable(U);hp['search_progress']=c('separate_query_explanation_form');hp['source']['enum']+=['p08_checked_constant_operator','p06_validated_original_upper'];height['required'].append('original_upper')
height['allOf'][0]['then']['properties']['source']=e('p08_checked_upper_only','p06_validated_original_upper')
height['allOf'][0]['then']['properties'].update(original_upper=U,scope=c('original_core_query'))
height['allOf'][1]['then']['properties'].update(original_upper=U,scope=c('original_core_query'))
height['allOf'].append({'if':{'properties':{'status':c('checked_constant_operator')}},'then':{'properties':{'source':c('p08_checked_constant_operator'),'selected_height':c(0),'scope':c('p08_constant_false_operator_not_original_CQ_structural_minimum'),'original_upper':N,'original_minimum':N,'algorithm':N,'certificate_role':c('none'),'original_witness':N,'lower_bound_claims':N}}})
md=D['p_mode'];mp=md['properties'];mp['scope']=e('compile_only','current_owner_configuration','retained_session_configuration');mp['runtime_presence']=e('compile_only','live','stopped_retained','released')
for k in ['codec','sink','retention_policy','input_adapter','initialization_method']:del mp[k]
mp['construction_input_and_external_identity']=c('integrated_run_context; external_labels_are_caller_declared_unmeasured');mp['output_disposition']=c('integrated_current_and_last_attempt_output_actions');md['required']=list(mp)
md['allOf']=[{'if':{'properties':{'scope':c('compile_only')}},'then':{'properties':{'runtime':N,'runtime_presence':c('compile_only')}},'else':{'properties':{'runtime':ref('p_runtime_mode')}}}]
D['p_runtime_mode']['properties']['state']=nullable(D['p_runtime_mode']['properties']['state'])
P['run_context']=nullable(ref('run_context'));P['session']=nullable(ref('session_status'))
P['cursor']=obj(scope=c('latest_enabled_cursor_lifecycle_publication; not_lifetime_or_update_total'),availability=e('recorded','disabled','not_recorded'),value=nullable(ref('cursor')))
P['cursor']['allOf']=[{'if':{'properties':{'availability':c('recorded')}},'then':{'properties':{'value':ref('cursor')}},'else':{'properties':{'value':N}}}]
P['committed_gauges']=obj(availability=e('available','compile_only','pending_private_state','runtime_released'),value=nullable(ref('gauges')))
P['committed_gauges']['allOf']=[{'if':{'properties':{'availability':c('available')}},'then':{'properties':{'value':ref('gauges')}},'else':{'properties':{'value':N}}}]
trace=D['p_observations']['properties']['trace']['anyOf'][0]
trace['properties']['record_scope']=c('sampled_numeric_causal_records; omitted_prefix_and_abort_are_not_complete_committed_history; ids_do_not_pin_rows')
trace['required'].append('record_scope')
trace['properties']['records']=arr(obj(kind=e(*'begin source_change alias native_event child_enqueued child_applied journal reverse_visit core_result mapped_record prepared drain commit abort transferred discarded serialization_attempt serialization_success serialization_failure sink_attempt sink_success sink_failure acknowledged'.split()),event=U,cause=U,prefix=U,before=U,after=U,node=nullable(U),occurrence=nullable(U),role=nullable(U),tuple=nullable(U)))
P['open_gates']=arr(e('S05_total_allocator_bytes','O04_checkpoint','O05_recovery','O06_durable_delivery','C01_statistics','C02_ranking','B03_benchmark_validation','O08_release_workflow','native_integration_and_acceptance'))
physical['required']=list(P)
physical.setdefault('allOf',[]).extend([
 {'if':{'properties':{'kind':c('physical')}},'then':{'properties':{'run_context':N,'session':N,'mode':{'properties':{'runtime_presence':c('compile_only')}},'committed_gauges':{'properties':{'availability':c('compile_only')}}}}},
 {'if':{'properties':{'kind':c('runtime')}},'then':{'properties':{'run_context':ref('run_context'),'session':N}}},
 {'if':{'properties':{'kind':c('session')}},'then':{'properties':{'run_context':ref('run_context'),'session':ref('session_status')}}},
 {'if':{'properties':{'route':c('constant_false')}},'then':{'properties':{'structure':{'properties':{'height_domain':c('executable_operator'),'native_height':c(0)}}}},'else':{'properties':{'structure':{'properties':{'height_domain':c('validated_query_tree')}}}}}
])
D['physical_report']=physical;D['query_report']=query
root={'$schema':'https://json-schema.org/draft/2020-12/schema','title':'Composed CROWN EXPLAIN v2','$comment':'Closed transport shape, not authority. Native owner capture is required; schema validation cannot create proof, guarantees, observations, or durability. No arbitrary benchmark identity is measured.','oneOf':[ref('physical_report'),obj(schema_version=c(2),artifact=c('crown_explain'),kind=c('query'),query_explanation=ref('query_report'))],'$defs':D}
H.joinpath('schemas').mkdir(exist_ok=True);H.joinpath('schemas/explain-report-v2.schema.json').write_text(json.dumps(root,indent=2)+'\n')
witness,wd=imported(H.parent/'o07-query-explain-proposal/schemas/query-witness-v1.schema.json','w_')
wd['query_witness']=witness;wd.update({k:v for k,v in D.items() if k.startswith('p_')})
root={'$schema':'https://json-schema.org/draft/2020-12/schema','title':'Composed CROWN tree export v2','$comment':'A diagnostic tree export does not recreate checked authority. Operator and structural witness domains are distinct.','oneOf':[obj(schema_version=c(2),artifact=c('crown_explain_tree'),kind=e('physical','runtime','session'),scope=e('p08_constant_false_operator','p08_validated_selected_tree'),native_height=U,tree=ref('p_tree')),obj(schema_version=c(2),artifact=c('crown_explain_tree'),kind=c('query'),witness=ref('query_witness'))],'$defs':wd}
H.joinpath('schemas/explain-tree-v2.schema.json').write_text(json.dumps(root,indent=2)+'\n')
print('Wrote closed EXPLAIN and tree transport schemas; no target execution.')
