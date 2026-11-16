#!/usr/bin/env python3
"""Offline closed-schema and native-sidecar acceptance. Root executes, never fetches schemas."""
from pathlib import Path
import argparse,json
from contextlib import contextmanager
from jsonschema import Draft202012Validator
ROOT=Path(__file__).resolve().parents[2]
MODE=['maintenance','delta'];COMP=['automatic','ordered_replay','anchored','root_first'];LIVE=['on_output','incremental','eager'];VIEW=['core','sql'];OBS=['off','counters','timed','trace'];AVAIL=['unavailable','disabled','available'];KIND=['native','generalized'];TRACE=['disabled','not_sampled','pending','committed','aborted','released'];TK=['begin','source_change','alias','native_event','child_enqueued','child_applied','journal','reverse_visit','core_result','mapped_record','prepared','drain','commit','abort','transferred','discarded','serialization_attempt','serialization_success','serialization_failure','sink_attempt','sink_success','sink_failure','acknowledged']
OUTPUT=['discard_drain_requested','completion_drain_invoked','retention_disabled','prepared','published','released','transferred','serialization_invoked','sink_invoked','unread_discarded']
@contextmanager
def artifact_context(path):
 try:yield
 except Exception as error:raise AssertionError(f'{path}: {error}') from error
def unique(pairs):
 d={}
 for k,v in pairs:
  assert k not in d,('duplicate key',k)
  d[k]=v
 return d
def load(p):return json.loads(p.read_text(encoding='utf-8'),object_pairs_hook=unique,parse_constant=lambda x:(_ for _ in ()).throw(AssertionError(x)))
def eq(a,b):assert a==b,(a,b)
def val(x):return None if x=='null' else int(x)
def enum(names,x):return names[int(x)]
def unhex(x):return None if x=='null' else '' if x=='-' else bytes.fromhex(x).decode('utf-8')
def metric(m,raw):
 a,v,s=map(int,raw);eq(m['availability'],AVAIL[a]);eq(m['value'],v if a==2 else None);eq(m['saturated'],bool(s) if a==2 else None)
def options(x):
 assert len(x)==20,x
 return dict(mode=enum(MODE,x[0]),completion=enum(COMP,x[1]),live_maintenance=enum(LIVE,x[2]),view=enum(VIEW,x[3]),work_limit=val(x[4]),cursor_work_limit=val(x[5]),view_work_limit=val(x[6]),spool_row_limit=int(x[7]),spool_byte_limit=int(x[8]),physical=dict(work_limit=val(x[9]),derivation_limit=int(x[10]),support=dict(work_limit=val(x[11]),support_limit=int(x[12]),order=enum(['fifo','lifo'],x[13]),capture_transitions=bool(int(x[14])),observation=dict(mode=enum(OBS,x[15]),trace_capacity=int(x[16]),sample_period=int(x[17]),sample_offset=int(x[18]),trace_timings=bool(int(x[19]))))))
def flat_options(x):
 v=options(x);p=v['physical'];s=p['support'];return dict(requested_mode=v['mode'],requested_completion=v['completion'],live_maintenance=v['live_maintenance'],view=v['view'],work_limit=v['work_limit'],cursor_work_limit=v['cursor_work_limit'],epoch_view_work_limit=v['view_work_limit'],spool_rows=v['spool_row_limit'],spool_accounted_bytes=v['spool_byte_limit'],physical_work_limit=p['work_limit'],derivation_limit=p['derivation_limit'],support_work_limit=s['work_limit'],support_limit=s['support_limit'],propagation_order=s['order'],capture_transitions=s['capture_transitions'],observation=s['observation'])
def configuration(c,x,cursor=False):
 if x==['null']:eq(c,None);return
 assert len(x)==28,x
 eq(c['owner' if cursor else 'support_owner'],int(x[0]));eq(c['generation'],int(x[1]));eq(c['generation_saturated'],bool(int(x[2])));eq(c['mode'],enum(MODE,x[3]));eq(c['completion'],enum(COMP,x[4]));eq(c['query_factors'],int(x[7]))
 if not cursor:
  eq(c['format_version'],1);eq(c['live_maintenance'],enum(LIVE,x[5]));eq(c['view'],enum(VIEW,x[6]));eq(c['requested_options'],options(x[8:]));eq(c['guarantee_prose'],'not_copied_from_current_profile')
 else:eq(c['requested_options'],flat_options(x[8:]))
def initialization(c,x):
 if x==['null']:eq(c,None);return
 eq(c['route'],enum(['empty_constructor','initialized_database','rebuilt_snapshot'],x[0]));b=c['applied_build']
 if x[1]=='null':eq(b,None)
 else:eq(b,dict(method=enum(['direct','insertion_replay'],x[1]),work_limit=val(x[2])))
def labels(c,x):
 if x==['null']:eq(c,None);return
 eq(c['authority'],'none');eq(c['provenance'],'caller_declared_unmeasured')
 for k,v in zip(['run','input_adapter','output_codec','sink'],x,strict=True):eq(c[k],unhex(v))
def tree_node(x):
 ident,label,kind,occ=x[:4];rest=list(map(int,x[4:]));arrays=[]
 for _ in range(3):
  n=rest.pop(0);arrays.append(rest[:n]);del rest[:n]
 assert len(rest)==1
 return dict(id=int(ident),label=unhex(label),kind=enum(KIND,kind),occurrence=val(occ),scope=arrays[0],children=arrays[1],separator=arrays[2],connex=bool(rest[0]))
# Sidecars test native export fidelity; this does not independently replay a height proof.
def check_native(d,tree,lines):
 obs=d['observations'];ctx=d['run_context'];g=d['committed_gauges']['value'];c=d['cursor']['value'];summary=lambda s:obs['current' if s=='attempt' else 'last'];attempt=lambda s:ctx['current_attempt' if s=='attempt' else 'last_attempt'];records=[];bases=[];nodes=[];tnodes=[];metric_ids={'attempt':[],'last':[]};cm=[]
 for line in lines:
  tag,*x=line.split()
  if tag=='runtimestate':
   r=d['mode']['runtime'];eq([r['owner'],r['committed_sequence'],r['state'],r['mode'],r['resolved_completion'],r['live_maintenance'],r['result_view']],[int(x[0]),int(x[1]),None if x[2]=='null' else enum(['ready','pending_delta','paused','draining','epoch_prepared','committed_output','committed','aborted'],x[2]),enum(MODE,x[3]),enum(COMP,x[4]),enum(LIVE,x[5]),enum(VIEW,x[6])])
  elif tag=='plan':
   eq(d['route'],enum(['tree','constant_true','constant_false'],x[0]));eq(d['structure']['native_height'],val(x[1]));eq(tree['native_height'],val(x[1]));eq(tree['tree']['root'],val(x[2]))
  elif tag=='tnode':tnodes.append(tree_node(x))
  elif tag=='config':
   scope=x.pop(0);target=c['configuration'] if scope=='cursor' else obs['current_configuration'] if scope=='current' else summary(scope)['configuration'];configuration(target,x,scope=='cursor')
   if scope in ['attempt','last']:
    eq(summary(scope)['mode_binding'],'not_recorded' if target is None else 'exact_begin_configuration');a=attempt(scope)
    for k,field in [('configuration_owner','support_owner'),('configuration_generation','generation'),('configuration_generation_saturated','generation_saturated')]:eq(a[k],None if target is None else target[field])
  elif tag=='init':
   scope=x.pop(0);initialization(ctx['current_initialization'] if scope=='current' else ctx['session']['initialization'] if scope=='session' else attempt(scope)['initialization'],x)
  elif tag=='labels':
   scope=x.pop(0);labels(ctx['current_declared_benchmark'] if scope=='current' else attempt(scope)['declared_benchmark'],x)
  elif tag=='lifetime':
   if obs['availability']=='disabled':eq(obs['lifetime'],None)
   else:eq(obs['lifetime'],dict(attempts=int(x[0]),commits=int(x[1]),aborts=int(x[2]),saturated=bool(int(x[3]))))
  elif tag=='summary':
   scope=x.pop(0);s=summary(scope)
   if x==['null']:eq(s,None);eq(attempt(scope),None)
   else:
    eq([s['attempt'],s['sequence'],s['owner_layer'],s['outcome']],[int(x[0]),int(x[1]),enum(['support','physical','delta'],x[2]),enum(['pending','committed','aborted'],x[3])]);eq(attempt(scope)['attempt'],s['attempt']);eq(attempt(scope)['sequence'],s['sequence'])
  elif tag=='metric':
   scope=x.pop(0);i=int(x.pop(0));metric_ids[scope].append(i);m=summary(scope)['values'][i];eq(m['id'],i);metric(m,x)
  elif tag=='output':
   scope=x.pop(0);v=attempt(scope)['output']
   if x==['null']:eq(v,None)
   else:
    for k,b in zip(OUTPUT,x,strict=True):eq(v[k],bool(int(b)))
  elif tag=='traceheader':
   t=obs['trace'];keys=['support_owner','attempt','sequence','retained_records','dropped_records'];eq(t['disposition'],enum(TRACE,x[0]));eq([t[k] for k in keys],list(map(int,x[1:6])));eq(t['dropped_saturated'],bool(int(x[6])));eq(t['truncated'],bool(int(x[7])))
  elif tag=='trace':
   a=list(map(int,x));noid=lambda v:None if v==2**64-1 else v
   records.append(dict(kind=TK[a[0]],event=a[1],cause=a[2],node=noid(a[3]),occurrence=noid(a[4]),prefix=a[5],before=a[6],after=a[7],role=noid(a[8]),tuple=noid(a[9])))
  elif tag=='gauge':
   if x==['null']:eq(g,None)
   else:eq([g['owner'],g['sequence']],list(map(int,x[:2])));metric(g['base_tuples'],[x[3],x[2],x[4]])
  elif tag=='base':bases.append(dict(table=int(x[0]),tuples=int(x[1])))
  elif tag=='nodegauge':
   n=g['nodes'][len(nodes)];eq([n['node'],n['kind'],n['records'],n['survivors'],n['projected_parent_keys']],[int(x[0]),enum(KIND,x[1]),int(x[2]),int(x[3]),int(x[4])]);metric(n['visible_factor_assignments'],[x[5],x[6],'0']);nodes.append(n)
  elif tag=='session':
   s=d['session'];eq([s[k] for k in ['state','phase','committed_sequence','input_failed','end_of_input','pending_sequence','pending_work','output_remaining','pending_command_sequence']],[enum(['created','running','paused','stopped','dropped'],x[0]),enum(['ready','pending','paused_pending','draining','prepared','output'],x[1]),int(x[2]),bool(int(x[3])),bool(int(x[4])),val(x[5]),int(x[6]),int(x[7]),val(x[8])])
  elif tag=='queue':eq(d['session']['queue'],dict(batches=int(x[0]),events=int(x[1]),accounted_bytes=int(x[2]),closed=bool(int(x[3])),failed=bool(int(x[4]))))
  elif tag=='window':eq(d['session']['window'],dict(zip(['completed_command_sequence','physical_sequence','completed_watermark','last_label','active_command_sequence','completed_steps','total_steps'],map(val,x),strict=True)))
  elif tag=='cursor':
   if x==['null']:eq(c,None)
   else:
    eq([c['owner'],c['sequence']],list(map(int,x[:2])));eq(c['cursor_id'],int(x[2]) if c['observation_options']['mode']!='off' else None);eq(c['cursor_id_saturated'],bool(int(x[3])) if c['observation_options']['mode']!='off' else None);eq(c['constructed'],bool(int(x[4])));eq(c['source'],enum(['committed_results','epoch_visible','epoch_witnesses','epoch_keys','epoch_bucket'],x[5]));eq(c['state'],enum(['active','exhausted','cancelled','failed'],x[6]));eq(c['terminal_reason'],enum(['not_recorded','none','exhausted','explicit_cancel','destruction','move_replacement','invalidated','startup_failure','next_failure'],x[7]));eq([c['mandatory'][k] for k in ['total_work','max_result_work','cleanup_frames']],list(map(int,x[8:])))
  elif tag=='cursoroptions':
   eq(c['view'],enum(VIEW,x[0]));eq(c['observation_options'],dict(mode=enum(OBS,x[1]),trace_capacity=int(x[2]),sample_period=int(x[3]),sample_offset=int(x[4]),trace_timings=bool(int(x[5]))));eq(c['tentative_at_creation'],bool(int(x[6])));eq(c['side'],None if x[7]=='null' else enum(['before','after'],x[7]));eq(c['cursor_work_limit'],val(x[8]))
  elif tag=='cmetric':
   i=int(x.pop(0));cm.append(i);eq(c['metrics'][i]['id'],i);metric(c['metrics'][i]['measurement'],x)
  elif tag=='cwork':eq(c['mandatory'][x[0]],dict(zip(['work', 'calls', 'route_checks', 'descriptor_steps', 'frame_initializations', 'cursor_opens', 'cursor_advances', 'frame_closes', 'tuple_lookups', 'selected_rows', 'bucket_lookups', 'key_fields', 'equality_checks', 'output_fields', 'rows_emitted', 'binding_checks', 'binding_rejections', 'direct_lookups', 'overlay_rows', 'fragment_steps', 'binding_values', 'witness_probes', 'witness_rows', 'join_rejections'],map(int,x[1:]),strict=True)))
  elif tag=='runoptions':eq(ctx['session']['requested_delta'],flat_options(x))
  elif tag=='runfield':
   path,kind,raw=x
   if path=='self':eq(ctx['session'],None)
   else:
    target=ctx['session']
    for part in path.split('.'):target=target[part]
    names={'input_kind':['owned_stream','typed_physical','typed_window'],'input_options.format':['jsonl','binary','csv','legacy_signed','legacy_relations','legacy_insert_only','legacy_flags','legacy_timestamp_flags'],'input_options.csv_operation':['insert','erase'],'window.fifo':['global','per_relation'],'resolved_mode':MODE,'resolved_completion':COMP}
    expected=enum(names[path],raw) if path in names else unhex(raw) if kind=='s' else bool(int(raw)) if kind=='b' else val(raw)
    eq(target,expected)
  elif tag=='runtoken':assert dict(token=unhex(x[0]),table=int(x[1])) in ctx['session']['input_options']['relation_tokens']
  elif tag=='runmanaged':assert int(x[0]) in ctx['session']['window']['managed_tables']
  elif tag=='literal_height':eq(d['height_evidence']['selected_height'],int(x[0]));eq(tree['native_height'],int(x[0]))
  elif tag=='operator_zero_structural_negative':eq(d['height_evidence']['status'],'checked_constant_operator');eq(d['height_evidence']['original_upper'],None);eq(d['structure']['height_domain'],'executable_operator');eq(tree['native_height'],0)
  else:raise AssertionError(('unknown sidecar field',tag))
 if any(line.startswith('plan ') for line in lines):eq(tree['tree']['nodes'],tnodes);eq(d['structure']['selected_tree'],tree['tree'])
 if obs['trace'] is not None:eq(obs['trace']['records'],records);eq(obs['trace']['retained_records'],len(records))
 for scope,ids in metric_ids.items():
  if summary(scope) is not None:eq(ids,list(range(len(summary(scope)['values']))))
 if g is not None:
  eq(g['bases'],bases);eq(len(g['nodes']),len(nodes))
  for k in ['full_result_count','allocated_bytes','live_bytes','checkpoint_bytes','checkpoint_ns','recovery_replay_length']:metric(g[k],['0','0','0'])
 if c is not None:eq(cm,list(range(len(c['metrics']))))
 # Native/public shape consistency, without converting unsupported facts to zero.
 if d['kind']=='session' and d['session']['state']=='dropped':eq(d['mode']['runtime_presence'],'released');eq(d['mode']['runtime']['state'],None);eq(g,None);eq(obs['trace']['disposition'],'released')
 if d['committed_gauges']['availability']!='available':eq(g,None)
 eq(d['cost']['global_optimality'],False)

def schemas(schema_dir):
 result=[]
 for name in ['explain-report-v2.schema.json','explain-tree-v2.schema.json']:
  s=load(schema_dir/name);Draft202012Validator.check_schema(s)
  def closed(v):
   if isinstance(v,dict):
    if (v.get('type')=='object' or isinstance(v.get('type'),list) and 'object' in v['type']) and 'properties' in v:assert v.get('additionalProperties') is False,('open object',name,v.keys())
    if '$ref' in v:assert v['$ref'].startswith('#/'),('external ref',v['$ref'])
    for child in v.values():closed(child)
   elif isinstance(v,list):
    for child in v:closed(child)
  closed(s);result.append(Draft202012Validator(s))
 return result

def main():
 p=argparse.ArgumentParser();p.add_argument('directory',type=Path);p.add_argument('--require-all',action='store_true');p.add_argument('--schema-dir',type=Path,default=ROOT/'schemas');p.add_argument('--repo-root',type=Path,default=ROOT);args=p.parse_args();schema_dir=args.schema_dir if args.schema_dir.is_absolute() else args.repo_root/args.schema_dir;report_schema,tree_schema=schemas(schema_dir);count=0;names=set();modes={};counts={}
 for side in sorted(args.directory.glob('*.expected')):
  with artifact_context(side):
   base=side.with_suffix('');d=load(Path(str(base)+'.json'));tree=load(Path(str(base)+'.tree.json'));report_schema.validate(d);tree_schema.validate(tree);check_native(d,tree,side.read_text().splitlines());name=base.name.split('-',1)[1];names.add(name);counts[name]=counts.get(name,0)+1;modes.setdefault(name,set()).add(d['mode']['runtime']['observation'] if d['mode']['runtime'] else 'compile_only');count+=1
   assert not report_schema.is_valid(dict(d,unexpected_acceptance_field=True))
   assert not tree_schema.is_valid(dict(tree,unexpected_acceptance_field=True))
   text=Path(str(base)+'.txt').read_text(encoding='utf-8');dot=Path(str(base)+'.dot').read_text(encoding='utf-8');assert text and dot.startswith('digraph ');assert '\x00' not in text+dot
   human_trace=[json.loads(line.strip(),object_pairs_hook=unique) for line in text.splitlines() if line.strip().startswith('{"kind":')]
   eq(human_trace,[] if d['observations']['trace'] is None else d['observations']['trace']['records'])
   # Each native node/edge appears once in the bounded DOT tree rendering.
   import re
   ids=re.findall(r'^\s*n(\d+) \[',dot,re.M);edges=re.findall(r'^\s*n(\d+) -> n(\d+)',dot,re.M)
   eq(sorted(map(int,ids)),list(range(len(tree['tree']['nodes']))));eq(sorted((int(a),int(b)) for a,b in edges),sorted((n['id'],c) for n in tree['tree']['nodes'] for c in n['children']))
 for q in args.directory.glob('*.query.json'):
  with artifact_context(q):
   d=load(q);report_schema.validate(d);count+=1;eq(d['kind'],'query');e=d['query_explanation'];eq(e['source'],'verified_infeasible');eq(e['height']['status'],'verified_infeasible');eq(e['height']['minimum_proven'],False);eq(e['height']['infeasible_proven'],True);eq(e['height']['witness_exportable'],False);eq(e['witness'],None);eq(e['height']['upper'],None);eq(e['binding']['query']['contradiction'],True);eq(len(e['binding']['query']['atoms']),3);eq(e['recognized_class']['status'],'not_collected');eq(e['recognized_class']['diagnostic_work'],0)
 assert count>0,'empty corpus'
 if args.require_all:
  required={'initialized-direct','initialized-replay','rebuilt','empty-constructor','runtime-initial','runtime-pending','runtime-paused','runtime-draining','runtime-prepared','runtime-committed','runtime-cursor','runtime-switched','runtime-moved','generation-max-exact','generation-saturated','sink-failed','sink-retried','output-transferred','output-unread-discarded','trace-truncated','trace-aborted','trace-unsampled','session-created','session-pending','session-paused','session-draining','session-prepared','session-committed','session-cursor','session-stopped','session-dropped','window-private','window-prepared','window-committed','window-dropped','cap-heavy107','cap-small4','typed-upper','typed-optimum','typed-candidate','constant-false-triangle','constant-empty-proved','nul-label','detached','fault-recovered-drop'}
  assert required<=names,('missing mandatory scenarios',sorted(required-names));
  for name in ['runtime-initial','runtime-pending','runtime-paused','runtime-draining','runtime-prepared','runtime-committed','runtime-cursor','runtime-switched','runtime-moved']:eq(counts[name],4);eq(modes[name],set(OBS))
  assert (args.directory/'structural-negative.query.json').exists()
 print('PASS closed V2 schemas and native semantic sidecars:',count)
if __name__=='__main__':main()
