#!/usr/bin/env python3
"""Current C02 source/metadata audit; historical source-entry checks are forbidden."""
import argparse
import collections
import hashlib
import importlib.util
import json
from pathlib import Path
import re

ROOT=Path('/home/userroot/Codex/CROWN');V=ROOT/'build/verification'
UTILITY=Path('/tmp/crown-observability-source-audit.py')
UTILITY_SHA='83d131c8f92bab8eb3da72dcd644c566c90915aab42bce78de66146e324a09b5'
FREEZE_SHA='1f97f84d7d2a09fb992668fcfa071d0065241b0a5de5395244a966216657d036'
NATIVE={'count':648,'sha256':'726b6ac99057cab64b3b2ee37e437641554bc9165bd832c0cb86ff16d27e705a'}
EXECUTION={'count':705,'sha256':'87455c8e07579b7d3689e90c4a5989a63ec438ea21bedc72b63bb959a4c9a2e5'}
REFACTOR='bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce'
OFFICIAL=ROOT/'docs/verification/ranking-sources.sha256'
CONFIGS=['debug','release','sanitize','clang','clean-source']
ROLES={'plan','planner_testing','ranking','ranking_runtime','ranking_runtime_testing','runtime','runtime_testing','explain','explain_testing'}
ERRORS=[];PENDING=[]

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def pin(path):return {'path':str(path),'sha256':sha(path)}
def need(test,message):
    if not test:ERRORS.append(message)
def waiting(message,final):
    (ERRORS if final else PENDING).append(message)
def read_json(path):return json.loads(path.read_text())
def resolve(path):
    p=Path(path);return p if p.is_absolute() else ROOT/p


def accepted_matrix(path,freeze,authority_id):
    authority_path=V/'ranking-matrix-audit-authority.json'
    need(bool(authority_id) and re.fullmatch(r'[0-9a-f]{64}',authority_id or '') is not None,'root matrix authority SHA must be explicit')
    need(authority_path.is_file(),'matrix authority absent')
    if not authority_path.is_file() or not authority_id:return {'status':'audit_error'}
    need(sha(authority_path)==authority_id,'root matrix authority FILE changed')
    authority=read_json(authority_path);m=read_json(path)
    need(authority.get('reviewer')=='root' and authority.get('decision')=='accepted_evidence_only_auditor','matrix authority decision invalid')
    need(authority.get('native')==NATIVE and authority.get('execution')==EXECUTION,'matrix authority source boundary wrong')
    for field in ['auditor','package_manifest']:
        item=authority.get(field,{});p=resolve(item.get('path',''))
        need(p.is_file() and p.resolve().is_relative_to(ROOT/'docs/verification'),'matrix authority path invalid: '+field)
        if p.is_file():need(sha(p)==item.get('sha256'),'matrix authority FILE drift: '+field)
        if field=='package_manifest' and p.is_file():
            seen=set()
            for line in p.read_text().splitlines():
                match=re.fullmatch(r'([0-9a-f]{64})  (.+)',line);need(match is not None,'auditor package manifest row malformed')
                if not match:continue
                q=resolve(match[2]).resolve();need(q.is_relative_to(p.parent) and q!=p and q not in seen,'auditor package entry escaped or duplicated');seen.add(q)
                need(q.is_file() and sha(q)==match[1],'auditor package entry drift: '+match[2])
            actual={q.resolve() for q in p.parent.rglob('*') if q.is_file() and q!=p and '__pycache__' not in q.parts and q.suffix not in {'.pyc','.pyo'}}
            need(seen==actual,'auditor package inventory is not exact')
    need(m.get('auditor')==authority.get('auditor'),'matrix auditor differs from reviewed authority')
    need(m.get('card')=='C02' and m.get('accepted') is True and m.get('accepted_matrix_evidence') is True and m.get('audit_state')=='accepted_final_matrix','matrix not final accepted C02')
    need(m.get('changes_project_status') is False and m.get('errors')==[] and m.get('pending')==[],'matrix status/remaining gates invalid')
    need(not m.get('unapplied_allocation_approval_ids') and all(x.get('root_approved') is True for x in m.get('allocation_differences',[])),'matrix has unresolved allocation reviews')
    f=m.get('freeze',{});need(f.get('status')=='audited_pass' and f.get('native')==NATIVE and f.get('execution')==EXECUTION,'matrix source boundary differs')
    need(f.get('metadata')=={'path':'build/verification/ranking-execution-freeze.json','sha256':FREEZE_SHA},'matrix freeze FILE identity differs')
    need(f.get('test_names')==freeze['expected_test_names'] and f.get('ordered_names')==freeze['expected_test_names_in_order'] and f.get('legacy_names')==freeze['old_legacy_test_names_in_order'],'matrix test inventory differs')
    need(f.get('historical_manifest_files')==freeze['historical_manifest_file_hashes'],'matrix historical FILE identities differ')
    allowed={Path(p).resolve():h for p,h in freeze['root_execution_helpers'].items()}
    for cache in freeze['predecessor_toolchain_caches'].values():
        for p,h in cache['compiler_files'].items():allowed[Path(p).resolve()]=h
    sidecar=read_json(V/'ranking-clean-dependencies.json');need(sidecar.get('status')=='captured_pass' and sidecar.get('dependency_file_count')==214,'clean direct dependency capture absent/failed')
    item=sidecar['root_helper'];allowed[Path(item['path']).resolve()]=item['sha256']
    for p,h in authority.get('allowed_external_file_pins',{}).items():allowed[Path(p).resolve()]=h
    raw=m.get('read_evidence_sha256',{});need(isinstance(raw,dict) and bool(raw),'matrix raw evidence pins absent')
    external={};bad=[]
    for rel,h in raw.items():
        p=resolve(rel).resolve()
        if not p.is_relative_to(ROOT):
            external[str(p)]=h
            if allowed.get(p)!=h:bad.append(rel)
        if not p.is_file() or sha(p)!=h:bad.append(rel)
    need(not bad,'matrix raw evidence changed/unscoped: '+str(bad))
    for p,h in freeze['root_execution_helpers'].items():need(raw.get(p)==h,'matrix omitted held execution helper: '+p)
    need(set(m.get('matrix',{}))==set(m.get('symbols',{}))==set(CONFIGS),'matrix must contain exact five configuration gates')
    summaries={}
    for name in CONFIGS:
        value=m.get('matrix',{}).get(name,{});symbols=m.get('symbols',{}).get(name,{})
        need(value.get('status')=='audited_pass' and value.get('cross_configuration',{}).get('status')=='audited_pass',name+' matrix gate incomplete')
        need(symbols.get('status')=='audited_pass' and set(symbols.get('roles',{}))==ROLES,name+' nine symbol roles differ')
        need(symbols.get('parser_both_sanitizers') is (name=='sanitize'),name+' parser sanitizer gate differs')
        names=value.get('registered_test_names',[]);outcomes=value.get('test_outcomes',[]);tests=value.get('tests',{})
        need(names==freeze['expected_test_names_in_order'] and names==value.get('actual_order'),name+' actual143 order differs')
        need(len(outcomes)==143 and [x.get('ordinal') for x in outcomes]==list(range(1,144)) and [x.get('name') for x in outcomes]==names and all(x.get('status')=='passed' for x in outcomes),name+' exact143 outcomes differ')
        need(set(tests)==set(names) and all(x.get('passed') is True for x in tests.values()),name+' per-test evidence missing')
        for outcome in outcomes:need(outcome.get('command')==tests.get(outcome.get('name'),{}).get('raw_command') and bool(outcome.get('command')),name+' per-test raw command differs')
        for field in ['summary','registration','raw_lasttest','raw_verbose']:
            item=value.get(field,{});need(bool(item.get('sha256')) and raw.get(item.get('path'))==item.get('sha256'),name+' raw evidence pin omitted: '+field)
        summary_path=V/('ranking-'+name+'-summary.json');s=read_json(summary_path)
        need(value.get('summary')=={'path':str(summary_path.relative_to(ROOT)),'sha256':sha(summary_path)},name+' designated summary differs')
        need(s.get('exit_code')==0 and s.get('test_count')==143 and s.get('source_stable') is True,name+' summary failed')
        need(s.get('fingerprint_before')==s.get('fingerprint_after')==NATIVE['sha256'] and s.get('execution_inputs_before')==s.get('execution_inputs_after')==EXECUTION,name+' terminal source stability differs')
        if name=='clean-source':need(s.get('temporary_removed') is True,'clean temporary tree not removed')
        c=value.get('compilation',{});need(c.get('raw_cmake_entries')==214 and c.get('runtime_units_per_variant')==14 and c.get('report_units_per_variant')==6,name+' compile/variant inventory differs')
        summaries[name]={'test_count':143,'ctest_seconds':s.get('ctest_seconds'),'numeric_rows_observed':value.get('numeric_rows_observed')}
    return {'status':'audited_pass' if not ERRORS else 'audit_error','identity':pin(path),'authority':pin(authority_path),'raw_pin_count':len(raw),'external_file_pins':external,'configurations':summaries}


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--final',action='store_true');parser.add_argument('--seal',type=Path);parser.add_argument('--output',type=Path,required=True);parser.add_argument('--matrix-authority-sha256');args=parser.parse_args()
    if args.output.exists() or args.output.with_suffix('.log').exists():raise RuntimeError('preserve existing source-audit evidence')
    need(sha(UTILITY)==UTILITY_SHA,'historical pure utility FILE changed')
    spec=importlib.util.spec_from_file_location('historical_pure_source_utilities',UTILITY);u=importlib.util.module_from_spec(spec);spec.loader.exec_module(u);u.ERRORS=ERRORS;u.SCHEMAS=['explain-report-v2.schema.json','explain-tree-v2.schema.json','query-explain-v1.schema.json','query-witness-v1.schema.json','statistics-explain-v3.schema.json']
    freeze_path=V/'ranking-execution-freeze.json';need(sha(freeze_path)==FREEZE_SHA,'current freeze FILE changed');freeze=read_json(freeze_path)
    for name,want,roots,extra in [('native',NATIVE,['include','src','apps','tests','cmake'],['CMakeLists.txt','CMakePresets.json']),('execution',EXECUTION,['include','src','apps','tests','cmake','schemas','tools','third_party'],['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'])]:
        paths=u.inventory_under(ROOT,roots,extra);need({'count':len(paths),'sha256':u.pathset_digest(ROOT,paths)}==want==freeze[name],name+' aggregate changed');need({p:sha(ROOT/p) for p in paths}==freeze[name+'_file_sha256'],name+' per-file map changed')
    need(len(freeze['historical_manifest_file_hashes'])==11,'eleven historical manifest FILE identities required')
    for card,item in freeze['historical_manifest_file_hashes'].items():need(sha(ROOT/item['path'])==item['sha256'],card+' historical manifest FILE changed')
    need(sha(ROOT/'Refactor.md')==REFACTOR,'original Refactor.md changed')
    ordinary=u.ordinary_inventory(ROOT);previous,malformed=u.parse_manifest_paths(ROOT/'docs/verification/statistics-sources.sha256');old_paths={p for p,_ in previous};added=sorted(set(ordinary)-old_paths);removed=sorted(old_paths-set(ordinary));integration=read_json(V/'c02-native-integration-start.json')
    need(not malformed and len(previous)==len(old_paths)==733,'previous733 path inventory malformed');need(len(ordinary)==764 and not removed and set(added)=={x['destination'] for x in integration['mappings'] if x['before'] is None} and len(added)==31,'ordinary inventory differs from733+31')
    seal=args.seal or OFFICIAL;seal_status={'path':str(seal),'status':'pending'}
    if seal.is_file():
        entries,malformed=u.parse_manifest_paths(seal);names=[p for p,_ in entries];bad=[p for p,h in entries if p.startswith('/') or '..' in Path(p).parts or not (ROOT/p).is_file() or sha(ROOT/p)!=h];need(not malformed and names==ordinary and len(names)==len(set(names)),'current764 seal inventory differs');need(not bad,'current seal checksum differences: '+str(bad));seal_status={'identity':pin(seal),'status':'audited_pass' if not malformed and names==ordinary and not bad else 'audit_error'}
    else:waiting('current C02 source seal absent',args.final)
    if args.final:need(seal.resolve()==OFFICIAL.resolve(),'final source audit requires official ranking-sources.sha256')
    completion_path=V/'ranking-completion-checkpoint.json';completion=read_json(completion_path) if completion_path.is_file() else {};doc_changes=completion.get('status_document_changes',{});mapped={x['destination']:x for x in integration['mappings']}
    allowed_docs={'README.md','docs/native_build.md','docs/ranking.md'}
    need(set(doc_changes)<=allowed_docs,'unexpected completion documentation change')
    for rel in ordinary:
        actual=sha(ROOT/rel)
        if rel in mapped:
            before=mapped[rel]['after']
            if actual!=before:
                approval=doc_changes.get(rel,{})
                need(rel in allowed_docs and approval.get('before')==before and approval.get('after')==actual and approval.get('change_kind')=='verification_status_only','unreviewed mapped ordinary source drift: '+rel)
        else:need(integration['baseline_entry_pins'].get(str(ROOT/rel))==actual,'unmapped ordinary bytes differ from fresh integration capture: '+rel)
    projection={}
    for name in ['c01-native-integration-start.json','c02-native-integration-start.json']:
        for item in read_json(V/name)['mappings']:
            if Path(item['source']).suffix.lower() in {'.md','.markdown'}:need(sha(ROOT/item['source'])==item['after'],'frozen publication document changed');projection[item['source']]=item['destination']
    base=u.local_destination
    def published(root,source,raw):
        item=base(root,projection.get(source,source),raw)
        if source in projection:item['publication_source_base']=projection[source]
        return item
    u.local_destination=published;links=u.audit_markdown(ROOT,ordinary);need(not links['documents_missing'] and not links['broken_local_destinations'],'Markdown source/link checks failed');schemas=u.schema_references();need(schemas['documents']==29,'native schema inventory differs from29')
    cm=(ROOT/'CMakeLists.txt').read_text();need('docs/verification/' not in cm and '/tmp/crown' not in cm,'native CMake uses excluded paths')
    for var,count in [('CROWN_RUNTIME_SOURCES',14),('CROWN_EXPLAIN_SOURCES',6)]:
        match=re.search(r'set\('+var+r'\s+([^)]*)\)',cm,re.S);values=match[1].split() if match else [];need(len(values)==count and all((ROOT/p).is_file() for p in values),'native source set changed: '+var)
    for p in list((ROOT/'src/runtime').glob('*.cpp'))+list((ROOT/'include/crown/runtime').glob('*.hpp')):need(not re.search(r'#\s*include\s+"crown/(?:observability/|io/(?:explain|query_explain|statistics_explain))',p.read_text()),'runtime/report include: '+str(p))
    for p in (ROOT/'include/crown').rglob('*.hpp'):
        for header in re.findall(r'#\s*include\s+"(crown/[^\"]+)"',p.read_text()):need((ROOT/'include'/header).is_file(),'public include missing: '+header)
    properties=read_json(ROOT/'schemas/statistics-explain-v3.schema.json')['properties']['capabilities'];need('c01_project_gate' not in properties['properties'] and 'c01_project_gate' not in properties['required'],'project acceptance leaked into native schema')
    matrix_path=V/'ranking-matrix-evidence-audit.json';matrix={'status':'pending'}
    if matrix_path.is_file() and read_json(matrix_path).get('accepted') is True:matrix=accepted_matrix(matrix_path,freeze,args.matrix_authority_sha256)
    else:waiting('complete independent C02 matrix audit not accepted',args.final)
    rows=u.task_rows(ROOT/'docs/task_ledger.md',True);cards=u.task_rows(ROOT/'Refactor.md');statuses={x['id']:x['status'] for x in rows};counts=dict(collections.Counter(statuses.values()));need(len(rows)==len(statuses)==78 and set(statuses)=={x['id'] for x in cards},'ledger differs from78 original cards');phase=statuses.get('C02');need(phase in {'in_progress','verified'},'C02 phase invalid')
    want={'verified':39,'in_progress':2,'not_started':37} if phase=='verified' else {'verified':38,'in_progress':3,'not_started':37};need(counts==want,'ledger phase counts differ');need(statuses.get('C01')=='verified' and statuses.get('O07')=='verified' and statuses.get('C05')=='not_started','unrelated card phase differs')
    if phase=='verified':need(matrix['status']=='audited_pass' and seal_status['status']=='audited_pass','C02 marked verified before final gates')
    else:waiting('final C02 verified metadata transition pending',args.final)
    if args.final:
        packet=ROOT/'docs/verification/ranking-2026-11-07.md';need(packet.is_file(),'final C02 evidence packet absent');text=packet.read_text() if packet.is_file() else '';need('143' in text and 'ranking-sources.sha256' in text and OFFICIAL.is_file() and sha(OFFICIAL) in text,'final C02 source/test citations missing');need(set(doc_changes)==allowed_docs,'all three native status guides must be finalized explicitly');head=(ROOT/'docs/handoff.md').read_text().split('## Historical',1)[0];need('goal active' in head.lower() or 'goal remains active' in head.lower(),'current handoff lost full-goal boundary')
    accepted=not ERRORS and not PENDING and matrix['status']=='audited_pass' and phase=='verified' and seal.resolve()==OFFICIAL.resolve();state='accepted_final_source_seal' if accepted else 'source_needs_review' if ERRORS else 'preliminary_pending_final_gates'
    result={'card':'C02','accepted':accepted,'audit_state':state,'requested_final':args.final,'auditor':pin(Path(__file__)),'historical_pure_utility':pin(UTILITY),'freeze':{'identity':pin(freeze_path),'native':NATIVE,'execution':EXECUTION,'historical_manifest_files':freeze['historical_manifest_file_hashes']},'ordinary_count':len(ordinary),'added':added,'removed':removed,'seal':seal_status,'status_document_changes':doc_changes,'markdown':links,'publication_namespace_map':projection,'schema_refs':schemas,'matrix_prerequisite':matrix,'ledger':{'C02':phase,'counts':counts},'errors':ERRORS,'pending':PENDING,'limits':'Current source/metadata and accepted raw matrix binding only. Historical source checksum entries are never evaluated; old path names and manifest FILE identities are separate.'}
    args.output.write_text(json.dumps(result,indent=2,sort_keys=True)+'\n');args.output.with_suffix('.log').write_text(state+'\naccepted='+str(accepted)+'\nerrors='+json.dumps(ERRORS)+'\npending='+json.dumps(PENDING)+'\n');print(state,'accepted='+str(accepted),'ordinary='+str(len(ordinary)),'errors='+str(len(ERRORS)),'pending='+str(len(PENDING)));return 1 if ERRORS else 0

if __name__=='__main__':raise SystemExit(main())
