#!/usr/bin/env python3
"""Current C02 source/metadata audit; historical source-entry checks are forbidden."""
import argparse
import collections
import difflib
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import sys

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
ERRORS=[];PENDING=[];READ_PINS={}
C01_INTEGRATION_SHA='b6202957a10b545093ca03cba785650c224753a4940fe362ab65aaae52befba8'
WATCHER=Path('/tmp/crown-c02-clean-dependencies-capture.py')
WATCHER_SHA='30647d38d9b03804125012eefe96956dd8c4c218b6522b9d5c6d2700eb78f362'
ALLOWED_DOCS={'README.md','docs/native_build.md','docs/ranking.md'}

class AuditError(Exception):pass
def require(test,message):
    if not test:raise AuditError(message)
def track(path,value):
    key=str(path.resolve());require(key not in READ_PINS or READ_PINS[key]==value,'input changed during audit: '+key);READ_PINS[key]=value;return value
def sha(path):
    h=hashlib.sha256()
    with path.open('rb') as stream:
        for chunk in iter(lambda:stream.read(1024*1024),b''):h.update(chunk)
    return track(path,h.hexdigest())
def read_text(path):
    raw=path.read_bytes();track(path,hashlib.sha256(raw).hexdigest());return raw.decode('utf-8')
def pin(path):return {'path':str(path),'sha256':sha(path)}
def need(test,message):
    if not test:ERRORS.append(message)
def waiting(message,final):
    (ERRORS if final else PENDING).append(message)
def unique_pairs(pairs):
    result={}
    for key,value in pairs:
        require(key not in result,'duplicate JSON key: '+key);result[key]=value
    return result
def read_json(path):return json.loads(read_text(path),object_pairs_hook=unique_pairs)
def resolve(path):
    p=Path(path);return p if p.is_absolute() else ROOT/p


def documented_schemas(u,ordinary,projection):
    """Scan mentions outside fences, including inline code, in publication scope."""
    docs,_=u.markdown_paths(ROOT,ordinary);refs=[];missing=[]
    pattern=re.compile(r'(?:[A-Za-z0-9_.-]+/)*[A-Za-z0-9_.-]+\.schema\.json')
    for rel in docs:
        text=read_text(ROOT/rel)
        declaration=re.search(r'(?:reviewed package is|Package-relative paths below refer to)\s*`(docs/verification/[^`]+/)`',text,re.I)
        package_base=(ROOT/declaration[1]).resolve() if declaration else None
        require(package_base is None or package_base.is_relative_to(ROOT/'docs/verification'),'declared schema package escapes verification root')
        visible,_=u.strip_fences(text.splitlines())
        published=ROOT/projection.get(rel,rel)
        for line_no,line in visible:
            for match in pattern.finditer(line):
                raw=match[0]
                candidates=[published.parent/raw,ROOT/raw] if '/' in raw else [published.parent/raw,published.parent/'schemas'/raw,ROOT/raw,ROOT/'schemas'/raw]
                if package_base is not None:candidates.append(package_base/raw)
                found=None
                for candidate in candidates:
                    candidate=candidate.resolve()
                    if candidate.is_relative_to(ROOT) and candidate.is_file():found=candidate.relative_to(ROOT).as_posix();break
                item={'source':rel,'publication_source_base':projection.get(rel,rel),'line':line_no,'raw':raw,'resolved':found};refs.append(item)
                if found is None:missing.append(item)
    need(not missing,'documented schema path mentions are unresolved: '+str(missing))
    return {'documents':len(docs),'occurrences':len(refs),'missing':missing,'all_exist':not missing,'references':refs,'scope':'Outside fenced blocks; inline-code mentions included; published C01/C02 source namespace.'}


def metadata_approval(integration,final):
    path=V/'ranking-completion-metadata-approval.json'
    if not path.is_file():
        if final:need(False,'immutable completion metadata approval absent')
        return {},{'status':'pending','path':str(path)}
    value=read_json(path)
    need(value.get('card')=='C02' and value.get('reviewer')=='root' and value.get('decision')=='accepted_verification_status_only','completion metadata authority decision invalid')
    need(value.get('native')==NATIVE and value.get('execution')==EXECUTION,'completion metadata authority source boundary differs')
    need(value.get('integration_record_sha256')==sha(V/'c02-native-integration-start.json'),'completion metadata authority integration differs')
    changes=value.get('status_document_changes',{});require(isinstance(changes,dict),'status_document_changes is not an object')
    need(set(changes)==ALLOWED_DOCS,'completion authority must approve exactly all three native status guides')
    mapped={item['destination']:item for item in integration['mappings']}
    for rel,item in changes.items():
        require(rel in ALLOWED_DOCS and rel in mapped and isinstance(item,dict),'invalid completion guide entry')
        before=mapped[rel]['after'];after=sha(ROOT/rel)
        need(item.get('reviewer')=='root' and item.get('decision')=='accepted_verification_status_only','guide lacks explicit root review: '+rel)
        need(item.get('before')==before and item.get('after')==after and before!=after and item.get('change_kind')=='verification_status_only','guide approval is empty, stale, or wrongly scoped: '+rel)
        if 'diff_evidence' in item:
            record=item['diff_evidence'];path=resolve(record['path']);require(path.resolve().is_relative_to(V),'guide diff evidence outside verification records')
            original=read_text(ROOT/mapped[rel]['source']);current=read_text(ROOT/rel)
            wanted=''.join(difflib.unified_diff(original.splitlines(keepends=True),current.splitlines(keepends=True),fromfile=rel+':published',tofile=rel+':verified'))
            need(sha(path)==record.get('sha256') and read_text(path)==wanted,'guide diff evidence does not match exact approved bytes: '+rel)
    return changes,{'status':'audited_pass' if not ERRORS else 'audit_error','identity':pin(V/'ranking-completion-metadata-approval.json'),'scope':'Explicit root classification; the auditor binds bytes/diffs but does not infer prose semantics.'}


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
        require(p.is_file() and p.resolve().is_relative_to(ROOT/'docs/verification'),'matrix authority path invalid: '+field)
        if p.is_file():need(sha(p)==item.get('sha256'),'matrix authority FILE drift: '+field)
        if field=='package_manifest' and p.is_file():
            seen=set()
            for line in read_text(p).splitlines():
                match=re.fullmatch(r'([0-9a-f]{64})  (.+)',line);need(match is not None,'auditor package manifest row malformed')
                if not match:continue
                q=resolve(match[2]).resolve();require(q.is_relative_to(p.parent) and q!=p and q not in seen,'auditor package entry escaped or duplicated');seen.add(q)
                need(q.is_file() and sha(q)==match[1],'auditor package entry drift: '+match[2])
            actual={q.resolve() for q in p.parent.rglob('*') if q.is_file() and q!=p and '__pycache__' not in q.parts and q.suffix not in {'.pyc','.pyo'}}
            need(seen==actual,'auditor package inventory is not exact')
            need(resolve(authority['auditor']['path']).resolve() in seen,'reviewed auditor is not a member of its bound package')
    need(m.get('auditor')==authority.get('auditor'),'matrix auditor differs from reviewed authority')
    need(m.get('card')=='C02' and m.get('accepted') is True and m.get('accepted_matrix_evidence') is True and m.get('audit_state')=='accepted_final_matrix','matrix not final accepted C02')
    need(m.get('changes_project_status') is False and m.get('errors')==[] and m.get('pending')==[],'matrix status/remaining gates invalid')
    need(not m.get('unapplied_allocation_approval_ids') and all(x.get('root_approved') is True for x in m.get('allocation_differences',[])),'matrix has unresolved allocation reviews')
    f=m.get('freeze',{});need(f.get('status')=='audited_pass' and f.get('native')==NATIVE and f.get('execution')==EXECUTION,'matrix source boundary differs')
    need(f.get('metadata')=={'path':'build/verification/ranking-execution-freeze.json','sha256':FREEZE_SHA},'matrix freeze FILE identity differs')
    need(f.get('test_names')==freeze['expected_test_names'] and f.get('ordered_names')==freeze['expected_test_names_in_order'] and f.get('legacy_names')==freeze['old_legacy_test_names_in_order'],'matrix test inventory differs')
    need(f.get('historical_manifest_files')==freeze['historical_manifest_file_hashes'],'matrix historical FILE identities differ')
    closing=m.get('closing_source_guard',{});need(closing.get('status')=='audited_pass' and closing.get('native')==NATIVE and closing.get('execution')==EXECUTION and closing.get('metadata')==f.get('metadata'),'matrix final source guard absent or wrong')
    expected_units={(x['target'],x['source']) for x in freeze['expected_compile_units']};need(len(expected_units)==214,'freeze compile unit identities are not unique214')
    need(f.get('expected_compile_units')==freeze['expected_compile_units'],'matrix freeze compile identities differ')
    mandatory={}
    def mandatory_pin(path,digest):
        key=Path(path).resolve();need(key not in mandatory or mandatory[key]==digest,'mandatory external pin collision');mandatory[key]=digest
    for p,h in freeze['root_execution_helpers'].items():mandatory_pin(p,h)
    for cache in freeze['predecessor_toolchain_caches'].values():
        for p,h in cache['compiler_files'].items():mandatory_pin(p,h)
    sidecar=read_json(V/'ranking-clean-dependencies.json');need(sidecar.get('status')=='captured_pass' and sidecar.get('dependency_file_count')==214,'clean direct dependency capture absent/failed')
    need(sidecar.get('root_helper')=={'path':str(WATCHER),'sha256':WATCHER_SHA},'clean dependency watcher differs from reviewed FILE');mandatory_pin(WATCHER,WATCHER_SHA)
    allowed={}
    declared=authority.get('allowed_external_file_pins');require(isinstance(declared,dict),'closed external whitelist absent')
    for p,h in declared.items():
        key=Path(p);require(key.is_absolute() and key.resolve()==key and not key.is_relative_to(ROOT),'external whitelist path is not canonical/external')
        require(re.fullmatch(r'[0-9a-f]{64}',h) is not None,'external whitelist hash malformed');allowed[key]=h
    for p,h in mandatory.items():need(allowed.get(p)==h,'mandatory external pin missing or overridden: '+str(p))
    raw=m.get('read_evidence_sha256',{});need(isinstance(raw,dict) and bool(raw),'matrix raw evidence pins absent')
    external={};bad=[]
    for rel,h in raw.items():
        p=resolve(rel).resolve()
        if not p.is_relative_to(ROOT):
            need(str(p) not in external or external[str(p)]==h,'external raw pin alias collision')
            external[str(p)]=h
            if allowed.get(p)!=h:bad.append(rel);continue
        if not p.is_file() or sha(p)!=h:bad.append(rel)
    need(not bad,'matrix raw evidence changed/unscoped: '+str(bad))
    need(external=={str(p):h for p,h in allowed.items()},'external whitelist is not the exact observed canonical pin inventory')
    def bound_raw(evidence_path,expected=None):
        p=resolve(evidence_path);key=p.relative_to(ROOT).as_posix() if p.is_relative_to(ROOT) else str(p)
        require(key in raw,'matrix required raw pin omitted: '+key)
        require(p.resolve().is_relative_to(ROOT) or allowed.get(p.resolve())==raw[key],'matrix required external pin is not approved: '+key)
        value=sha(p);need(raw.get(key)==value and (expected is None or expected==value),'matrix required raw pin omitted or differs: '+key)
    bound_raw(V/'ranking-clean-dependencies.json')
    bound_raw(V/'c02-native-integration-start.json',freeze['integration_record_sha256'])
    pin_check=m.get('input_pin_check',{});manifest=resolve(pin_check.get('manifest',''))
    require(manifest.is_file(),'matrix immutable-input manifest absent');bound_raw(manifest)
    immutable_inputs=read_json(manifest);need(pin_check.get('count')==len(immutable_inputs)>0,'matrix immutable-input manifest count differs')
    for item,want in immutable_inputs.items():bound_raw(item,want)
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
        observed_rows=0
        for ordinal,test in enumerate(names,1):
            item=tests.get(test,{});rows=item.get('rows',{})
            need(item.get('ordinal')==ordinal and isinstance(item.get('command'),list) and bool(item.get('command')),name+' per-test ordinal/normalized command differs')
            need(isinstance(rows.get('raw'),list) and isinstance(rows.get('comparison'),list) and len(rows['raw'])==len(rows['comparison']),name+' numeric-row raw/comparison population differs')
            observed_rows+=len(rows.get('raw',[]))
            need(re.fullmatch(r'[0-9a-f]{64}',item.get('output_sha256','')) is not None,name+' per-test output digest malformed')
        need(value.get('numeric_rows_observed')==observed_rows,name+' numeric-row count is not derived from all143 outputs')
        for field in ['summary','registration','raw_lasttest','raw_verbose']:
            item=value.get(field,{});need(bool(item.get('sha256')) and raw.get(item.get('path'))==item.get('sha256'),name+' raw evidence pin omitted: '+field)
        summary_path=V/('ranking-'+name+'-summary.json');s=read_json(summary_path)
        need(value.get('summary')=={'path':str(summary_path.relative_to(ROOT)),'sha256':sha(summary_path)},name+' designated summary differs')
        need(s.get('configuration')==name and s.get('exit_code')==0 and s.get('test_count')==143 and s.get('source_stable') is True,name+' summary failed or belongs to another configuration')
        need(s.get('fingerprint_before')==s.get('fingerprint_after')==NATIVE['sha256'] and s.get('execution_inputs_before')==s.get('execution_inputs_after')==EXECUTION,name+' terminal source stability differs')
        if name=='clean-source':need(s.get('temporary_removed') is True,'clean temporary tree not removed')
        c=value.get('compilation',{});need(c.get('raw_cmake_entries')==214 and c.get('runtime_units_per_variant')==14 and c.get('report_units_per_variant')==6,name+' compile/variant inventory differs')
        inventory=c.get('source_inventory',[]);need(len(inventory)==214 and {(x['target'],x['source']) for x in inventory}==expected_units,name+' actual214 source identities differ')
        need(c.get('ranking_units')==3 and c.get('bridge_units_per_variant')==1,name+' pure/bridge unit inventory differs')
        links=c.get('links',{});need(set(links)=={target for target,_ in expected_units},name+' target/link inventory differs')
        for target,link in links.items():
            if target in {'crown_ranking_usage_production','crown_ranking_usage_testing'}:need(link.get('kind')=='object_library',name+' guide object gained a link')
            else:bound_raw(link['recipe'])
        dependencies=c.get('dependencies',{});need(dependencies.get('status')=='audited_pass' and dependencies.get('direct_dependency_rows') is True and dependencies.get('actual_compile_argv_matches_database') is True,name+' direct dependency/actual compiler evidence incomplete')
        dep_rows=dependencies.get('files',[]);need(len(dep_rows)==214 and {(x['target'],x['source']) for x in dep_rows}==expected_units,name+' direct214 dependency identities differ')
        for row in dep_rows:bound_raw(row['dependency_file'])
        fresh=dependencies.get('actual_recompiled_units',[]);cached=dependencies.get('unchanged_non_JSON_units_not_recompiled',[])
        fresh_set={tuple(x) for x in fresh};cached_set={(x['target'],x['source']) for x in cached}
        need(len(fresh)==len(fresh_set) and len(cached)==len(cached_set) and not fresh_set&cached_set and fresh_set|cached_set==expected_units,name+' fresh/cached population does not partition214 units')
        commands=dependencies.get('actual_compile_commands',[]);need(len(commands)==len(fresh_set) and {(x['target'],x['source']) for x in commands}==fresh_set and all(isinstance(x.get('command'),str) and x['command'] for x in commands),name+' observed compiler command population differs')
        if name=='clean-source':need(fresh_set==expected_units and not cached,name+' clean source did not freshly compile214 units')
        symbol_path=V/('ranking-'+name+'-symbols.json');need(symbols.get('metadata')==str(symbol_path.relative_to(ROOT)),name+' symbol metadata path differs');bound_raw(symbol_path)
        captured=read_json(symbol_path);wanted_roles=ROLES|({'parser_undefined'} if name=='sanitize' else set())
        capture_rows=captured.get('records',[]);need(len(capture_rows)==len(wanted_roles) and {x.get('role') for x in capture_rows}==wanted_roles,name+' captured symbol population differs')
        for item in capture_rows:
            need(item.get('exit_code')==0 and item.get('archive_stable') is True,name+' symbol capture failed or archive drifted')
            bound_raw(item['dump'],item['dump_sha256']);bound_raw(item['stderr'],item['stderr_sha256'])
        summaries[name]={'test_count':143,'ctest_seconds':s.get('ctest_seconds'),'numeric_rows_observed':value.get('numeric_rows_observed')}
    return {'status':'audited_pass' if not ERRORS else 'audit_error','identity':pin(path),'authority':pin(authority_path),'raw_pin_count':len(raw),'external_file_pins':external,'configurations':summaries}


def audit(args):
    sha(Path(__file__))
    require(sha(UTILITY)==UTILITY_SHA,'historical pure utility FILE changed; refusing import')
    sys.dont_write_bytecode=True
    spec=importlib.util.spec_from_file_location('historical_pure_source_utilities',UTILITY);u=importlib.util.module_from_spec(spec);spec.loader.exec_module(u);u.ERRORS=ERRORS;u.read=read_text;u.SCHEMAS=['explain-report-v2.schema.json','explain-tree-v2.schema.json','query-explain-v1.schema.json','query-witness-v1.schema.json','statistics-explain-v3.schema.json']
    freeze_path=V/'ranking-execution-freeze.json';require(sha(freeze_path)==FREEZE_SHA,'current freeze FILE changed');freeze=read_json(freeze_path)
    integration_path=V/'c02-native-integration-start.json';require(sha(integration_path)==freeze['integration_record_sha256'],'fresh C02 integration ownership FILE changed');integration=read_json(integration_path)
    require(integration.get('applied') is True and integration.get('card')=='C02','C02 integration was not applied')
    mappings=integration.get('mappings',[]);require(len(mappings)==len({x['destination'] for x in mappings})==38,'integration must have38 distinct destinations')
    require(sum(x['before'] is None for x in mappings)==31,'integration new/overwritten ownership counts differ')
    for name,want,roots,extra in [('native',NATIVE,['include','src','apps','tests','cmake'],['CMakeLists.txt','CMakePresets.json']),('execution',EXECUTION,['include','src','apps','tests','cmake','schemas','tools','third_party'],['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'])]:
        paths=u.inventory_under(ROOT,roots,extra);need({'count':len(paths),'sha256':u.pathset_digest(ROOT,paths)}==want==freeze[name],name+' aggregate changed');need({p:sha(ROOT/p) for p in paths}==freeze[name+'_file_sha256'],name+' per-file map changed')
    need(len(freeze['historical_manifest_file_hashes'])==11,'eleven historical manifest FILE identities required')
    for card,item in freeze['historical_manifest_file_hashes'].items():need(sha(ROOT/item['path'])==item['sha256'],card+' historical manifest FILE changed')
    need(sha(ROOT/'Refactor.md')==REFACTOR,'original Refactor.md changed')
    ordinary=u.ordinary_inventory(ROOT);previous,malformed=u.parse_manifest_paths(ROOT/'docs/verification/statistics-sources.sha256');old_paths={p for p,_ in previous};added=sorted(set(ordinary)-old_paths);removed=sorted(old_paths-set(ordinary))
    need(not malformed and len(previous)==len(old_paths)==733,'previous733 path inventory malformed');need(len(ordinary)==764 and not removed and set(added)=={x['destination'] for x in integration['mappings'] if x['before'] is None} and len(added)==31,'ordinary inventory differs from733+31')
    seal=args.seal or OFFICIAL;seal_status={'path':str(seal),'status':'pending'}
    if seal.is_file():
        entries,malformed=u.parse_manifest_paths(seal);names=[p for p,_ in entries];bad=[p for p,h in entries if p.startswith('/') or '..' in Path(p).parts or not (ROOT/p).is_file() or sha(ROOT/p)!=h];need(not malformed and names==ordinary and len(names)==len(set(names)),'current764 seal inventory differs');need(not bad,'current seal checksum differences: '+str(bad));seal_status={'identity':pin(seal),'status':'audited_pass' if not malformed and names==ordinary and not bad else 'audit_error'}
    else:waiting('current C02 source seal absent',args.final)
    if args.final:need(seal.resolve()==OFFICIAL.resolve(),'final source audit requires official ranking-sources.sha256')
    doc_changes,approval=metadata_approval(integration,args.final);mapped={x['destination']:x for x in integration['mappings']}
    need(set(doc_changes)<=ALLOWED_DOCS,'unexpected completion documentation change')
    for rel in ordinary:
        actual=sha(ROOT/rel)
        if rel in mapped:
            before=mapped[rel]['after']
            if actual!=before:
                change=doc_changes.get(rel,{})
                need(rel in ALLOWED_DOCS and change.get('before')==before and change.get('after')==actual and change.get('change_kind')=='verification_status_only','unreviewed mapped ordinary source drift: '+rel)
        else:need(integration['baseline_entry_pins'].get(str(ROOT/rel))==actual,'unmapped ordinary bytes differ from fresh integration capture: '+rel)
    projection={}
    require(sha(V/'c01-native-integration-start.json')==C01_INTEGRATION_SHA,'C01 publication namespace ownership FILE changed')
    for name in ['c01-native-integration-start.json','c02-native-integration-start.json']:
        for item in read_json(V/name)['mappings']:
            if Path(item['source']).suffix.lower() in {'.md','.markdown'}:need(sha(ROOT/item['source'])==item['after'],'frozen publication document changed');projection[item['source']]=item['destination']
    base=u.local_destination
    def published(root,source,raw):
        item=base(root,projection.get(source,source),raw)
        if source in projection:item['publication_source_base']=projection[source]
        return item
    u.local_destination=published;markdown_inventory=u.markdown_paths(ROOT,ordinary)[0];links=u.audit_markdown(ROOT,ordinary);need(not links['documents_missing'] and not links['broken_local_destinations'],'Markdown source/link checks failed');schemas=u.schema_references();need(schemas['documents']==29,'native schema inventory differs from29');schema_mentions=documented_schemas(u,ordinary,projection)
    cm=read_text(ROOT/'CMakeLists.txt');need('docs/verification/' not in cm and '/tmp/crown' not in cm,'native CMake uses excluded paths')
    for var,count in [('CROWN_RUNTIME_SOURCES',14),('CROWN_EXPLAIN_SOURCES',6)]:
        match=re.search(r'set\('+var+r'\s+([^)]*)\)',cm,re.S);values=match[1].split() if match else [];need(len(values)==count and all((ROOT/p).is_file() for p in values),'native source set changed: '+var)
    for p in list((ROOT/'src/runtime').glob('*.cpp'))+list((ROOT/'include/crown/runtime').glob('*.hpp')):need(not re.search(r'#\s*include\s+"crown/(?:observability/|io/(?:explain|query_explain|statistics_explain))',read_text(p)),'runtime/report include: '+str(p))
    for p in (ROOT/'include/crown').rglob('*.hpp'):
        for header in re.findall(r'#\s*include\s+"(crown/[^\"]+)"',read_text(p)):need((ROOT/'include'/header).is_file(),'public include missing: '+header)
    properties=read_json(ROOT/'schemas/statistics-explain-v3.schema.json')['properties']['capabilities'];need('c01_project_gate' not in properties['properties'] and 'c01_project_gate' not in properties['required'],'project acceptance leaked into native schema')
    matrix_path=V/'ranking-matrix-evidence-audit.json';matrix={'status':'pending'}
    if matrix_path.is_file() and read_json(matrix_path).get('accepted') is True:matrix=accepted_matrix(matrix_path,freeze,args.matrix_authority_sha256)
    else:waiting('complete independent C02 matrix audit not accepted',args.final)
    rows=u.task_rows(ROOT/'docs/task_ledger.md',True);cards=u.task_rows(ROOT/'Refactor.md');statuses={x['id']:x['status'] for x in rows};counts=dict(collections.Counter(statuses.values()));need(len(rows)==len(statuses)==78 and set(statuses)=={x['id'] for x in cards},'ledger differs from78 original cards');phase=statuses.get('C02');need(phase in {'in_progress','verified'},'C02 phase invalid')
    want={'verified':39,'in_progress':2,'not_started':37} if phase=='verified' else {'verified':38,'in_progress':3,'not_started':37};need(counts==want,'ledger phase counts differ');need(statuses.get('C01')=='verified' and statuses.get('O07')=='verified' and statuses.get('C05')=='not_started','unrelated card phase differs')
    if phase=='verified':need(matrix['status']=='audited_pass' and seal_status['status']=='audited_pass','C02 marked verified before final gates')
    else:waiting('final C02 verified metadata transition pending',args.final)
    if args.final:
        packet=ROOT/'docs/verification/ranking-2026-11-07.md';need(packet.is_file(),'final C02 evidence packet absent');text=read_text(packet) if packet.is_file() else '';need('143' in text and 'ranking-sources.sha256' in text and OFFICIAL.is_file() and sha(OFFICIAL) in text,'final C02 source/test citations missing');need(set(doc_changes)==ALLOWED_DOCS and approval.get('status')=='audited_pass','all three native status guides must be finalized explicitly');head=read_text(ROOT/'docs/handoff.md').split('## Historical',1)[0];need('goal active' in head.lower() or 'goal remains active' in head.lower(),'current handoff lost full-goal boundary')
    if not args.final and not PENDING:PENDING.append('explicit --final invocation is required for final acceptance')
    for p,h in list(READ_PINS.items()):need(sha(Path(p))==h,'read input changed before publication: '+p)
    need(u.ordinary_inventory(ROOT)==ordinary,'ordinary source path inventory changed during audit')
    need(u.markdown_paths(ROOT,ordinary)[0]==markdown_inventory,'Markdown path inventory changed during audit')
    accepted=args.final and not ERRORS and not PENDING and matrix['status']=='audited_pass' and phase=='verified' and seal.resolve()==OFFICIAL.resolve();state='accepted_final_source_seal' if accepted else 'source_needs_review' if ERRORS else 'preliminary_pending_final_gates'
    return {'card':'C02','accepted':accepted,'audit_state':state,'requested_final':args.final,'auditor':pin(Path(__file__)),'historical_pure_utility':pin(UTILITY),'freeze':{'identity':pin(freeze_path),'native':NATIVE,'execution':EXECUTION,'historical_manifest_files':freeze['historical_manifest_file_hashes']},'integration':pin(integration_path),'C01_publication_ownership':pin(V/'c01-native-integration-start.json'),'ordinary_count':len(ordinary),'added':added,'removed':removed,'seal':seal_status,'status_document_changes':doc_changes,'metadata_approval':approval,'markdown':links,'publication_namespace_map':projection,'schema_refs':schemas,'documented_schema_paths':schema_mentions,'matrix_prerequisite':matrix,'ledger':{'C02':phase,'counts':counts},'read_evidence_sha256':READ_PINS,'errors':ERRORS,'pending':PENDING,'limits':'Current source/metadata and accepted raw matrix binding only. Historical source checksum entries are never evaluated; old path names and manifest FILE identities are separate. Status-only semantics are explicitly reviewed by root, not inferred from prose. Completion checkpoint is not an input and may be written afterward.'}


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--final',action='store_true');parser.add_argument('--seal',type=Path);parser.add_argument('--output',type=Path,required=True);parser.add_argument('--matrix-authority-sha256');args=parser.parse_args()
    output=args.output.resolve()
    allowed=(output.parent==V and re.fullmatch(r'ranking-source-[A-Za-z0-9_.-]+\.json',output.name)) or str(output).startswith('/tmp/crown-c02-source-audit-review-')
    require(allowed and output.suffix=='.json','output must be a designated new source-audit JSON')
    require(not output.exists() and not output.with_suffix('.log').exists(),'preserve existing source-audit evidence')
    try:result=audit(args)
    except (AuditError,OSError,ValueError,KeyError,TypeError,IndexError,AttributeError,UnicodeError) as error:
        ERRORS.append(type(error).__name__+': '+str(error))
        result={'card':'C02','accepted':False,'audit_state':'source_needs_review','requested_final':args.final,'audit_completed':False,'auditor':{'path':str(Path(__file__)),'sha256':READ_PINS.get(str(Path(__file__).resolve()))},'read_evidence_sha256':READ_PINS,'errors':ERRORS,'pending':PENDING}
    output.parent.mkdir(parents=True,exist_ok=True)
    with output.open('x',encoding='utf-8') as stream:stream.write(json.dumps(result,indent=2,sort_keys=True)+'\n')
    with output.with_suffix('.log').open('x',encoding='utf-8') as stream:stream.write(result['audit_state']+'\naccepted='+str(result['accepted'])+'\nerrors='+json.dumps(ERRORS)+'\npending='+json.dumps(PENDING)+'\n')
    print(result['audit_state'],'accepted='+str(result['accepted']),'ordinary='+str(result.get('ordinary_count','unavailable')),'errors='+str(len(ERRORS)),'pending='+str(len(PENDING)))
    return 1 if ERRORS else 0

if __name__=='__main__':raise SystemExit(main())
