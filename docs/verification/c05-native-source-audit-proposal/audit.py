#!/usr/bin/env python3
"""Draft C05 source/metadata auditor bound to the actual applied execution freeze.

No build, test, symbol tool, network or historical INPUT/seal-entry replay is
performed. Only a new designated audit receipt and sibling log may be written.
"""
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
UTILITY=Path(__file__).resolve().parent/'upstream/observability_source_utility.py'
UTILITY_SHA='83d131c8f92bab8eb3da72dcd644c566c90915aab42bce78de66146e324a09b5'
# Root captured this actual freeze after the reviewed 34-path native batch.
# Final matrix/metadata authorities remain separate explicit invocation pins.
FREEZE_SHA='affcb8fa29b193e57f9501c5a88054eaba9467b7040273f36f28c507f3146711'
NATIVE={'count':676,'sha256':'d963498ffa4d0ebcfa650f2a958258c2bf18a352022c264549dc3cbbab79b733'}
EXECUTION={'count':733,'sha256':'fc12d2bd82756946a3a5bcdec910df400481b7af1bc4199254040e59730c2445'}
INTEGRATION_SHA='9f8824f17f90bf6c1cc8caf89d3abc66adedd0083e38b88fcc8a11b944be66e0'
STAGE_SHA='38ce409eca1d52cffcf5d3478f7fdc8820135822ed6c611146e5d5bffdf60479'
JSON_HEADER_SHA='f763c58b102e65242d09275aec4b2f343268280ab4587b15587ad143b2e2a406'
FROZEN_PREPARATION_JOBS_SHA='286a1350f919811805f73c1c039c6183eb2a59dceffdf2722b50655f454fd3d7'
REFACTOR='bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce'
OFFICIAL=ROOT/'docs/verification/selection-sources.sha256'
PRELIMINARY=ROOT/'docs/verification/selection-sources-preliminary.sha256'
PRELIMINARY_SHA='26d1e256906fa7fb803d70c0fac94f5834066a9bd323b2b857dc72be9e4874cc'
PRELIMINARY_RECORD_SHA='60498eab21754264787d11b76ab198bca6edbfb3de060239f399e980bce816f4'
CONFIGS=['debug','release','sanitize','clang','clean-source']
ROLES={'plan','planner_testing','ranking','ranking_runtime','ranking_runtime_testing','runtime','runtime_testing','explain','explain_testing','selection','selection_runtime','selection_runtime_testing'}
ERRORS=[];PENDING=[];READ_PINS={}
C01_INTEGRATION_SHA='b6202957a10b545093ca03cba785650c224753a4940fe362ab65aaae52befba8'
C02_INTEGRATION_SHA='652f6be933a30611ef99a90825d8472039c038400491904d45eb46bb0e10db52'
ALLOWED_DOCS={'README.md','docs/native_build.md','docs/selection.md'}
BASELINE_VERIFIED=set('A01 A03 A04 A05 F01 F02 F03 F04 F05 F06 P01 P02 P03 P04 P05 P06 P07 P08 S01 S02 S03 R01 R02 R03 R04 R05 R06 D01 D02 D03 D04 D05 D06 O01 O02 O03 O07 C01 C02'.split())

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

def valid_digest(value):return isinstance(value,str) and re.fullmatch(r'[0-9a-f]{64}',value) is not None

def current_seal_path(value):
    """Reject historical manifests before parsing even their path inventory."""
    path=resolve(value or OFFICIAL)
    allowed=path in {OFFICIAL,PRELIMINARY} or (path.parent==V and re.fullmatch(r'selection-preliminary-sources(?:-[A-Za-z0-9_.-]+)?\.sha256',path.name))
    require(allowed and not path.is_symlink() and path.resolve()==path,'only the new C05 current/preliminary seal may be evaluated')
    return path

def captured_baseline(integration):
    """Use the already performed pre-application capture; read no old entries."""
    pins=integration.get('baseline_entry_pins',{});require(isinstance(pins,dict),'captured baseline pins absent')
    previous='docs/verification/ranking-sources.sha256'
    require(pins.get(previous)=='3ab4ca48b70203e5cf4e85f4883a6c2279bc01d164ad7ad054adace94dc62a41','captured prior manifest FILE identity differs')
    result={}
    for name,digest in pins.items():
        if name==previous:continue
        path=Path(name)
        require(path.is_absolute() and path.is_relative_to(ROOT) and path.resolve()==path and valid_digest(digest),'noncanonical captured ordinary path/hash')
        rel=path.relative_to(ROOT).as_posix()
        require(rel not in result and not rel.startswith('docs/verification/'),'duplicate/excluded captured ordinary path')
        result[rel]=digest
    require(len(result)==764 and integration.get('baseline_source_entry_count')==764,'captured predecessor ordinary count differs')
    return result


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
    return {'documents':len(docs),'occurrences':len(refs),'missing':missing,'all_exist':not missing,'references':refs,'scope':'Outside fenced blocks; inline-code mentions included; actual published C01/C02/C05 source namespaces.'}


def metadata_approval(integration,final,authority_id):
    path=V/'selection-completion-metadata-approval.json'
    if not path.is_file():
        require(authority_id is None,'supplied metadata-approval identity has no corresponding FILE')
        if final:need(False,'immutable completion metadata approval absent')
        return {},{'status':'pending','path':str(path)}
    require(valid_digest(authority_id) and sha(path)==authority_id,'explicit root metadata-approval FILE identity absent or changed')
    value=read_json(path)
    need(value.get('card')=='C05' and value.get('reviewer')=='root' and value.get('decision')=='accepted_verification_status_only','completion metadata authority decision invalid')
    need(value.get('native')==NATIVE and value.get('execution')==EXECUTION,'completion metadata authority source boundary differs')
    need(value.get('integration_record_sha256')==INTEGRATION_SHA==sha(V/'c05-native-integration-start.json'),'completion metadata authority integration differs')
    changes=value.get('status_document_changes',{});require(isinstance(changes,dict),'status_document_changes is not an object')
    need(set(changes)==ALLOWED_DOCS,'completion authority must approve exactly all three native status guides')
    mapped={item['destination']:item for item in integration['mappings']}
    for rel,item in changes.items():
        require(rel in ALLOWED_DOCS and rel in mapped and isinstance(item,dict),'invalid completion guide entry')
        before=mapped[rel]['after'];after=sha(ROOT/rel)
        need(item.get('reviewer')=='root' and item.get('decision')=='accepted_verification_status_only','guide lacks explicit root review: '+rel)
        need(item.get('before')==before and item.get('after')==after and before!=after and item.get('change_kind')=='verification_status_only','guide approval is empty, stale, or wrongly scoped: '+rel)
        require('diff_evidence' in item,'every approved guide requires exact retained diff evidence: '+rel)
        if 'diff_evidence' in item:
            record=item['diff_evidence'];path=resolve(record['path']);require(path.resolve().is_relative_to(V),'guide diff evidence outside verification records')
            original=read_text(ROOT/mapped[rel]['source']);current=read_text(ROOT/rel)
            wanted=''.join(difflib.unified_diff(original.splitlines(keepends=True),current.splitlines(keepends=True),fromfile=rel+':published',tofile=rel+':verified'))
            need(sha(path)==record.get('sha256') and read_text(path)==wanted,'guide diff evidence does not match exact approved bytes: '+rel)
    return changes,{'status':'audited_pass' if not ERRORS else 'audit_error','identity':pin(V/'selection-completion-metadata-approval.json'),'scope':'Explicit root classification; the auditor binds bytes/diffs but does not infer prose semantics.'}


def accepted_matrix(path,freeze,authority_id):
    authority_path=V/'selection-matrix-audit-authority.json'
    need(bool(authority_id) and re.fullmatch(r'[0-9a-f]{64}',authority_id or '') is not None,'root matrix authority SHA must be explicit')
    need(authority_path.is_file(),'matrix authority absent')
    if not authority_path.is_file() or not authority_id:return {'status':'audit_error'}
    need(sha(authority_path)==authority_id,'root matrix authority FILE changed')
    authority=read_json(authority_path);m=read_json(path)
    need(authority.get('card')=='C05' and authority.get('reviewer')=='root' and authority.get('decision')=='accepted_evidence_only_auditor','matrix authority decision invalid')
    need(authority.get('native')==NATIVE and authority.get('execution')==EXECUTION,'matrix authority source boundary wrong')
    need(authority.get('canonical_matrix')=={'path':path.relative_to(ROOT).as_posix(),'sha256':sha(path)},'root authority does not bind this exact canonical matrix receipt')
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
    need(m.get('card')=='C05' and m.get('accepted') is True and m.get('accepted_matrix_evidence') is True and m.get('audit_state')=='accepted_final_matrix','matrix not final accepted C05')
    need(m.get('changes_project_status') is False and m.get('errors')==[] and m.get('pending')==[],'matrix status/remaining gates invalid')
    need(not m.get('unapplied_allocation_approval_ids') and all(x.get('root_approved') is True for x in m.get('allocation_differences',[])),'matrix has unresolved allocation reviews')
    f=m.get('freeze',{});need(f.get('status')=='audited_pass' and f.get('native')==NATIVE and f.get('execution')==EXECUTION,'matrix source boundary differs')
    need(f.get('metadata')=={'path':'build/verification/selection-execution-freeze.json','sha256':FREEZE_SHA},'matrix freeze FILE identity differs')
    need(f.get('test_names')==freeze['expected_test_names'] and f.get('ordered_names')==freeze['expected_test_names_in_order'] and f.get('legacy_names')==freeze['old_legacy_test_names_in_order'],'matrix test inventory differs')
    need(f.get('historical_manifest_files')==freeze['historical_manifest_file_hashes'],'matrix historical FILE identities differ')
    closing=m.get('closing_source_guard',{});need(closing.get('status')=='audited_pass' and closing.get('native')==NATIVE and closing.get('execution')==EXECUTION and closing.get('metadata')==f.get('metadata'),'matrix final source guard absent or wrong')
    expected_units={(x['target'],x['source']) for x in freeze['expected_compile_units']};need(len(expected_units)==238,'freeze compile unit identities are not unique238')
    added_units={(x['target'],x['source']) for x in freeze['added_compile_units']}
    need(len(added_units)==24 and added_units<=expected_units,'freeze added24 unit identities differ')
    need(set(freeze.get('symbol_roles',[]))==ROLES,'freeze twelve symbol roles differ')
    need(f.get('expected_compile_units')==freeze['expected_compile_units'],'matrix freeze compile identities differ')
    mandatory={};mandatory_aliases={}
    def mandatory_pin(path,digest):
        key=resolve(path).resolve()
        require(key not in mandatory or mandatory[key]==digest,'mandatory tool pin alias collision: '+str(key))
        mandatory[key]=digest;mandatory_aliases.setdefault(key,set()).add(str(path))
    for p,h in freeze['root_execution_helpers'].items():mandatory_pin(p,h)
    for cache in freeze['predecessor_toolchain_caches'].values():
        for p,h in cache['compiler_files'].items():mandatory_pin(p,h)
    # The C05 clean evidence adapter retains all .o.d rows before tree cleanup.
    # Its exact helper FILE is mandatory through root_execution_helpers; there
    # is no separate C02 watcher or inherited 214-row sidecar authority.
    allowed={}
    declared=authority.get('allowed_external_file_pins');require(isinstance(declared,dict),'closed external whitelist absent')
    for p,h in declared.items():
        key=Path(p);require(key.is_absolute() and key.resolve()==key and not key.is_relative_to(ROOT),'external whitelist path is not canonical/external')
        require(re.fullmatch(r'[0-9a-f]{64}',h) is not None,'external whitelist hash malformed');allowed[key]=h
    for p,h in mandatory.items():
        if not p.is_relative_to(ROOT):need(allowed.get(p)==h,'mandatory external pin missing or overridden: '+str(p))
    raw=m.get('read_evidence_sha256',{});require(isinstance(raw,dict) and bool(raw),'matrix raw evidence pins absent')
    canonical_raw={};raw_aliases={};external={};bad=[]
    for rel,h in raw.items():
        p=resolve(rel).resolve()
        require(p not in canonical_raw or canonical_raw[p]==h,'canonical raw pin alias collision: '+str(p))
        canonical_raw[p]=h;raw_aliases.setdefault(p,set()).add(rel)
        if not p.is_relative_to(ROOT):
            external[str(p)]=h
            if allowed.get(p)!=h:bad.append(rel);continue
        if not p.is_file() or sha(p)!=h:bad.append(rel)
    need(not bad,'matrix raw evidence changed/unscoped: '+str(bad))
    need(external=={str(p):h for p,h in allowed.items()},'external whitelist is not the exact observed canonical pin inventory')
    mandatory_tools=[]
    for p,h in sorted(mandatory.items(),key=lambda item:str(item[0])):
        scope='repository_internal' if p.is_relative_to(ROOT) else 'external'
        need(canonical_raw.get(p)==h,'mandatory '+scope+' tool absent or overridden in canonical raw pins: '+str(p))
        need(p.is_file() and sha(p)==h,'mandatory '+scope+' tool FILE changed: '+str(p))
        mandatory_tools.append({'path':str(p),'sha256':h,'scope':scope,
          'mandatory_spellings':sorted(mandatory_aliases[p]),
          'observed_raw_spellings':sorted(raw_aliases.get(p,set()))})
    def bound_raw(evidence_path,expected=None):
        p=resolve(evidence_path);key=p.relative_to(ROOT).as_posix() if p.is_relative_to(ROOT) else str(p)
        require(key in raw,'matrix required raw pin omitted: '+key)
        require(p.resolve().is_relative_to(ROOT) or allowed.get(p.resolve())==raw[key],'matrix required external pin is not approved: '+key)
        value=sha(p);need(raw.get(key)==value and (expected is None or expected==value),'matrix required raw pin omitted or differs: '+key)
    bound_raw(V/'c05-native-integration-start.json',freeze['integration_record_sha256'])
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
        need(symbols.get('status')=='audited_pass' and set(symbols.get('roles',{}))==ROLES,name+' twelve symbol roles differ')
        need(symbols.get('parser_both_sanitizers') is (name=='sanitize'),name+' parser sanitizer gate differs')
        names=value.get('registered_test_names',[]);outcomes=value.get('test_outcomes',[]);tests=value.get('tests',{})
        need(names==freeze['expected_test_names_in_order'] and names==value.get('actual_order'),name+' actual158 order differs')
        need(len(outcomes)==158 and [x.get('ordinal') for x in outcomes]==list(range(1,159)) and [x.get('name') for x in outcomes]==names and all(x.get('status')=='passed' for x in outcomes),name+' exact158 outcomes differ')
        need(set(tests)==set(names) and all(x.get('passed') is True for x in tests.values()),name+' per-test evidence missing')
        for outcome in outcomes:need(outcome.get('command')==tests.get(outcome.get('name'),{}).get('raw_command') and bool(outcome.get('command')),name+' per-test raw command differs')
        observed_rows=0
        for ordinal,test in enumerate(names,1):
            item=tests.get(test,{});rows=item.get('rows',{})
            need(item.get('ordinal')==ordinal and isinstance(item.get('command'),list) and bool(item.get('command')),name+' per-test ordinal/normalized command differs')
            need(isinstance(rows.get('raw'),list) and isinstance(rows.get('comparison'),list) and len(rows['raw'])==len(rows['comparison']),name+' numeric-row raw/comparison population differs')
            observed_rows+=len(rows.get('raw',[]))
            need(re.fullmatch(r'[0-9a-f]{64}',item.get('output_sha256','')) is not None,name+' per-test output digest malformed')
        need(value.get('numeric_rows_observed')==observed_rows,name+' numeric-row count is not derived from all158 outputs')
        for field in ['summary','registration','raw_lasttest','raw_verbose']:
            item=value.get(field,{});need(bool(item.get('sha256')) and raw.get(item.get('path'))==item.get('sha256'),name+' raw evidence pin omitted: '+field)
        summary_path=V/('selection-'+name+'-summary.json');s=read_json(summary_path)
        need(value.get('summary')=={'path':str(summary_path.relative_to(ROOT)),'sha256':sha(summary_path)},name+' designated summary differs')
        need(s.get('terminal') is True and s.get('status')=='passed' and s.get('identity_guards_stable') is True and s.get('freeze_sha256')==FREEZE_SHA,name+' summary is not terminal/passed for the exact held freeze')
        need(s.get('configuration')==name and s.get('exit_code')==0 and s.get('test_count')==158 and s.get('source_stable') is True,name+' summary failed or belongs to another configuration')
        need(s.get('fingerprint_before')==s.get('fingerprint_after')==NATIVE['sha256'] and s.get('execution_inputs_before')==s.get('execution_inputs_after')==EXECUTION,name+' terminal source stability differs')
        if name=='clean-source':need(s.get('temporary_removed') is True,'clean temporary tree not removed')
        c=value.get('compilation',{});need(c.get('raw_cmake_entries')==238 and c.get('runtime_units_per_variant')==14 and c.get('report_units_per_variant')==6,name+' compile/variant inventory differs')
        inventory=c.get('source_inventory',[]);need(len(inventory)==238 and {(x['target'],x['source']) for x in inventory}==expected_units,name+' actual238 source identities differ')
        need(c.get('ranking_units')==3 and c.get('bridge_units_per_variant')==1,name+' pure/bridge unit inventory differs')
        need(c.get('selection_units')==5 and c.get('selection_bridge_units_per_variant')==1,name+' selection pure/bridge unit inventory differs')
        links=c.get('links',{});need(set(links)=={target for target,_ in expected_units},name+' target/link inventory differs')
        for target,link in links.items():
            if target in {'crown_ranking_usage_production','crown_ranking_usage_testing','crown_selection_usage_production','crown_selection_usage_testing'}:need(link.get('kind')=='object_library',name+' guide object gained a link')
            else:bound_raw(link['recipe'])
        dependencies=c.get('dependencies',{});need(dependencies.get('status')=='audited_pass' and dependencies.get('direct_dependency_rows') is True and dependencies.get('actual_compile_argv_matches_database') is True,name+' direct dependency/actual compiler evidence incomplete')
        dep_rows=dependencies.get('files',[]);need(len(dep_rows)==238 and {(x['target'],x['source']) for x in dep_rows}==expected_units,name+' direct238 dependency identities differ')
        for row in dep_rows:bound_raw(row['dependency_file'])
        fresh=dependencies.get('actual_recompiled_units',[]);cached=dependencies.get('unchanged_units_not_recompiled',[])
        fresh_set={tuple(x) for x in fresh};cached_set={(x['target'],x['source']) for x in cached}
        need(len(fresh)==len(fresh_set) and len(cached)==len(cached_set) and not fresh_set&cached_set and fresh_set|cached_set==expected_units,name+' fresh/cached population does not partition238 units')
        commands=dependencies.get('actual_compile_commands',[]);need(len(commands)==len(fresh_set) and {(x['target'],x['source']) for x in commands}==fresh_set and all(isinstance(x.get('command'),str) and x['command'] for x in commands),name+' observed compiler command population differs')
        if name=='clean-source':
            need(fresh_set==expected_units and not cached,name+' clean source did not freshly compile238 units')
            clean_path=V/'selection-clean-artifacts-manifest.json';bound_raw(clean_path);clean=read_json(clean_path)
            need(s.get('clean_artifacts_manifest')==clean_path.relative_to(ROOT).as_posix() and s.get('clean_artifacts_manifest_sha256')==sha(clean_path),'clean summary does not bind final artifact receipt')
            need(clean.get('terminal') is True and clean.get('status')=='passed' and clean.get('exit_code')==0 and clean.get('freeze_sha256')==FREEZE_SHA,'clean artifact receipt not terminal for this freeze')
            for field in ['source_before','snapshot_inputs','snapshot_inputs_after_tests','source_after']:
                need(clean.get(field)=={'native':NATIVE,'execution':EXECUTION},'clean snapshot/repository scope differs: '+field)
            need(clean.get('source_stable') is True and clean.get('temporary_removed') is True and clean.get('identity_guards_stable') is True and clean.get('dependency_inputs_stable_before_cleanup') is True,'clean closure or temporary cleanup guard absent')
            clean_rows=clean.get('dependency_records',[]);included=clean.get('dependency_inputs',{})
            need(clean.get('dependency_capture_complete') is True and clean.get('dependency_capture_phase')=='after_successful_build_before_ctest','clean dependency capture phase/completeness differs')
            need(len(clean_rows)==238 and {(x['target'],x['source']) for x in clean_rows}==expected_units,'clean direct238 identities differ')
            require(isinstance(included,dict) and bool(included),'clean actual included-input identities absent')
            source_root=Path(clean['snapshot_source']);build_root=source_root/'build';used=set()
            for row in clean_rows:
                bound_raw(row['retained'],row['sha256'])
                refs=row.get('included_inputs',[])
                need(bool(refs) and str(source_root/row['source']) in {x['canonical_input'] for x in refs},'clean unit source missing from actual included inputs')
                used.update(x['canonical_input'] for x in refs)
            need(used==set(included),'clean actual included-input inventory is not exact')
            for original,item in included.items():
                canonical=Path(original);require(canonical.is_absolute(),'clean canonical input is relative')
                scope=item.get('scope');digest=item.get('sha256');require(valid_digest(digest),'clean actual input hash malformed')
                if scope=='snapshot_source':
                    rel=item['source_relative'];need(canonical==source_root/rel and rel in freeze['execution_file_sha256'],'clean snapshot input outside frozen inventory')
                    need(item.get('frozen_sha256')==digest==freeze['execution_file_sha256'].get(rel),'clean snapshot include differs from freeze')
                    bound_raw(ROOT/rel,digest)
                elif scope=='generated_build':
                    rel=item['build_relative'];need(canonical==build_root/rel and '..' not in Path(rel).parts,'clean generated input path differs')
                    retained=resolve(item['retained']);need(retained==V/'selection-clean-artifacts'/rel,'clean generated include retained outside exact artifact path')
                    bound_raw(retained,digest)
                elif scope=='external_system':
                    need(not canonical.is_relative_to(ROOT) and not canonical.is_relative_to(source_root.parent),'clean external input has internal/temp scope')
                    bound_raw(canonical,digest)
                else:need(False,'unknown clean actual-input scope: '+str(scope))
        else:
            need(fresh_set==added_units and cached_set==expected_units-added_units,name+' observed incremental partition is not reviewed24fresh/214cached')
            provenance=dependencies.get('cached_predecessor_provenance',{})
            need(provenance.get('status')=='audited_pass' and provenance.get('unit_count')==214,name+' cached predecessor provenance is incomplete')
            item=provenance.get('capture',{});need(item.get('sha256')=='b21d69747ea69f0a7d7d86ffd9c372dc47eee5020ee4f0e386a5b45cc1616561',name+' wrong accepted C02 predecessor capture')
            bound_raw(item.get('path',''),item.get('sha256'))
            need(provenance.get('object_bytes_equal_to_capture') is True and provenance.get('normalized_compile_argv_equal') is True and provenance.get('frozen_project_dependency_bytes_equal') is True,name+' cached object/argv/project-input equality absent')
            need(provenance.get('historical_system_header_bytes_compared') is False and provenance.get('historical_generated_header_bytes_compared') is False,name+' cached historical system/generated scope is overstated or absent')
        symbol_path=V/('selection-'+name+'-symbols.json');need(symbols.get('metadata')==str(symbol_path.relative_to(ROOT)),name+' symbol metadata path differs');bound_raw(symbol_path)
        captured=read_json(symbol_path);wanted_roles=ROLES|({'parser_undefined'} if name=='sanitize' else set())
        need(captured.get('configuration')==name and captured.get('terminal') is True and captured.get('status')=='captured' and captured.get('exit_code')==0 and captured.get('freeze_sha256')==FREEZE_SHA,name+' symbol receipt is not terminal/captured for this configuration/freeze')
        capture_rows=captured.get('records',[]);need(len(capture_rows)==len(wanted_roles) and {x.get('role') for x in capture_rows}==wanted_roles,name+' captured symbol population differs')
        for item in capture_rows:
            need(item.get('exit_code')==0 and item.get('archive_stable') is True,name+' symbol capture failed or archive drifted')
            bound_raw(item['dump'],item['dump_sha256']);bound_raw(item['stderr'],item['stderr_sha256'])
        summaries[name]={'test_count':158,'ctest_seconds':s.get('ctest_seconds'),'numeric_rows_observed':value.get('numeric_rows_observed'),'fresh_units':len(fresh_set),'cached_units':len(cached_set)}
    return {'status':'audited_pass' if not ERRORS else 'audit_error','identity':pin(path),'authority':pin(authority_path),'raw_pin_count':len(raw),'external_file_pins':external,'mandatory_tool_file_pins':mandatory_tools,'configurations':summaries}


def ledger_state(u,final,matrix,seal_status):
    ledger_path=ROOT/'docs/task_ledger.md';handoff_path=ROOT/'docs/handoff.md'
    rows=u.task_rows(ledger_path,True);cards=u.task_rows(ROOT/'Refactor.md')
    statuses={x['id']:x['status'] for x in rows};counts=dict(collections.Counter(statuses.values()))
    need(len(rows)==len(statuses)==78 and set(statuses)=={x['id'] for x in cards},'ledger differs from original78 cards')
    phase=statuses.get('C05');need(phase in {'in_progress','verified'},'C05 phase invalid')
    verified=BASELINE_VERIFIED|({'C05'} if phase=='verified' else set())
    active={'A02','O06'}|({'C05'} if phase=='in_progress' else set())
    need({k for k,v in statuses.items() if v=='verified'}==verified,'verified card set changed outside C05')
    need({k for k,v in statuses.items() if v=='in_progress'}==active,'in-progress card set differs')
    need(all(v=='not_started' for k,v in statuses.items() if k not in verified|active),'unrelated card phase differs')
    want={'verified':40,'in_progress':2,'not_started':36} if phase=='verified' else {'verified':39,'in_progress':3,'not_started':36}
    need(counts==want,'ledger phase counts differ')
    ledger=read_text(ledger_path);head=read_text(handoff_path).split('## Historical',1)[0]
    summary=re.compile(r'(\d+)\s+verified,\s+(two|three|\d+)\s+in progress\s*\(([^)]*)\),\s+(\d+)\s+not started,\s+78\s+total',re.I)
    for source,text in [('ledger',ledger),('current handoff',head)]:
        matches=list(summary.finditer(text));need(bool(matches),source+' explicit current totals absent')
        for match in matches:
            active_count={'two':2,'three':3}.get(match[2].lower())
            if active_count is None:active_count=int(match[2])
            need((int(match[1]),active_count,int(match[4]))==(want['verified'],want['in_progress'],want['not_started']),source+' explicit totals contradict parsed rows')
            need(set(re.findall(r'[A-Z]\d{2}',match[3]))==active,source+' explicit in-progress card names differ')
    need('full 78-card scope remains active' in ledger.lower() and 'release gate disposition remains open' in ledger.lower(),'ledger lost full-goal/release boundary')
    need('goal active' in head.lower() or 'goal remains active' in head.lower(),'current handoff lost full-goal boundary')
    if phase=='verified':need(matrix['status']=='audited_pass' and seal_status['status']=='audited_pass','C05 marked verified before final gates')
    else:waiting('final C05 verified metadata transition pending',final)
    registry_path=V/'c05-native-root-jobs.json';registry=read_json(registry_path)
    need(registry.get('card')=='C05' and registry.get('root_owns_execution') is True and registry.get('full_goal')=='active','wrong current root registry')
    need(registry.get('native_status')==phase,'current native registry status differs from ledger')
    need(sha(V/'c05-selection-root-jobs.json')==FROZEN_PREPARATION_JOBS_SHA,'immutable preparation registry FILE changed')
    return {'C05':phase,'counts':counts,'verified_cards':sorted(verified),'in_progress_cards':sorted(active),'current_registry':pin(registry_path),'registry_scope':'Current progress snapshot, not matrix acceptance authority; old preparation registry is FILE-only.'}


def audit(args):
    sha(Path(__file__))
    require(valid_digest(FREEZE_SHA) and valid_digest(NATIVE['sha256']) and valid_digest(EXECUTION['sha256']),'unconfigured draft: actual root freeze/native/execution FILE identities are required before use')
    for label,value in [('matrix authority',args.matrix_authority_sha256),('metadata approval',args.metadata_approval_sha256)]:
        require(value is None or valid_digest(value),'invalid explicit '+label+' SHA-256')
        if args.final:require(valid_digest(value),'final invocation requires an explicit '+label+' SHA-256')
    seal=current_seal_path(args.seal)
    require(sha(UTILITY)==UTILITY_SHA,'copied historical pure utility FILE changed; refusing import')
    sys.dont_write_bytecode=True
    spec=importlib.util.spec_from_file_location('historical_pure_source_utilities',UTILITY);u=importlib.util.module_from_spec(spec);spec.loader.exec_module(u)
    u.ERRORS=ERRORS;u.read=read_text;u.SCHEMAS=['explain-report-v2.schema.json','explain-tree-v2.schema.json','query-explain-v1.schema.json','query-witness-v1.schema.json','statistics-explain-v3.schema.json']
    freeze_path=V/'selection-execution-freeze.json';require(sha(freeze_path)==FREEZE_SHA,'current C05 freeze FILE changed');freeze=read_json(freeze_path)
    ordered=freeze.get('expected_test_names_in_order',[]);legacy=freeze.get('old_legacy_test_names_in_order',[])
    need(freeze.get('card')=='C05' and freeze.get('configs')==CONFIGS,'freeze card/configuration scope differs')
    need(freeze.get('expected_ctest_count')==158 and len(ordered)==len(set(ordered))==158 and freeze.get('expected_test_names')==sorted(ordered),'freeze exact158 ordered/sorted test inventory differs')
    need(len(legacy)==len(set(legacy))==143 and ordered[:143]==legacy,'freeze does not preserve the exact143 legacy prefix')
    need(freeze.get('expected_compile_command_entries')==238,'freeze expected238 compile-entry count differs')
    need(freeze.get('incremental_partition_expectation')=={'fresh':24,'cached':214,'actual_partition':'must_be_observed_and_audited'} and freeze.get('clean_partition_expectation')=={'fresh':238,'cached':0},'freeze compilation expectations differ')
    integration_path=V/'c05-native-integration-start.json'
    require(sha(integration_path)==INTEGRATION_SHA==freeze['integration_record_sha256'],'applied C05 integration ownership FILE changed');integration=read_json(integration_path)
    require(integration.get('applied') is True and integration.get('card')=='C05' and integration.get('phase')=='guarded_native_application_applied','C05 integration was not applied')
    stage_path=V/'c05-publication-stage-build-attempt-1.json';require(sha(stage_path)==STAGE_SHA,'accepted staged registration FILE changed')
    need(freeze.get('stage_receipt_sha256')==STAGE_SHA,'freeze does not bind accepted stage')
    mappings=integration.get('mappings',[]);require(len(mappings)==len({x['destination'] for x in mappings})==34,'integration must have34 distinct destinations')
    require(sum(x['before'] is None for x in mappings)==31,'integration new/overwritten ownership counts differ')
    baseline=captured_baseline(integration);mapped={x['destination']:x for x in mappings}
    require({x['destination'] for x in mappings if x['before'] is not None}=={'CMakeLists.txt','README.md','docs/native_build.md'},'unexpected overwritten native destinations')
    for item in mappings:
        source=ROOT/item['source'];rel=item['destination']
        require(source.resolve().is_relative_to(ROOT/'docs/verification/c05-native-registration-proposal/overlay'),'mapped source outside actual publication namespace')
        require(not Path(rel).is_absolute() and '..' not in Path(rel).parts and Path(rel).as_posix()==rel,'noncanonical mapped destination')
        need(sha(source)==item['after'],'frozen mapped publication source changed: '+rel)
        need(item['before']==baseline.get(rel),'mapping pre-edit ownership differs from captured baseline: '+rel)
    for name,want,roots,extra in [('native',NATIVE,['include','src','apps','tests','cmake'],['CMakeLists.txt','CMakePresets.json']),('execution',EXECUTION,['include','src','apps','tests','cmake','schemas','tools','third_party'],['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'])]:
        paths=u.inventory_under(ROOT,roots,extra);need({'count':len(paths),'sha256':u.pathset_digest(ROOT,paths)}==want==freeze[name],name+' aggregate changed')
        need({p:sha(ROOT/p) for p in paths}==freeze[name+'_file_sha256'],name+' per-file map changed')
    historical=freeze['historical_manifest_file_hashes']
    need(len(historical)==12 and historical==integration['historical_manifest_file_hashes'],'twelve historical manifest FILE identities differ')
    for card,item in historical.items():need(sha(ROOT/item['path'])==item['sha256'],card+' historical manifest FILE changed')
    need(sha(ROOT/'Refactor.md')==REFACTOR,'original Refactor.md changed')
    need(sha(ROOT/'third_party/nlohmann/json.hpp')==JSON_HEADER_SHA,'unchanged patched native JSON header differs')
    # These mappings contain FILE identities only. Never recurse an INPUT or
    # the integration's historical manifest_input_pins after native application.
    for field in ['immutable_publication_file_pins','manifest_file_pins']:
        files=freeze.get(field);require(isinstance(files,dict) and bool(files),'freeze FILE-only inputs absent: '+field)
        for name,digest in files.items():need(sha(resolve(name))==digest,'immutable FILE changed: '+name)
    ordinary=u.ordinary_inventory(ROOT);added=sorted(set(ordinary)-set(baseline));removed=sorted(set(baseline)-set(ordinary))
    need(len(ordinary)==795 and not removed and set(added)=={x['destination'] for x in mappings if x['before'] is None} and len(added)==31,'ordinary inventory differs from captured764+31')
    if seal==PRELIMINARY:
        require(sha(seal)==PRELIMINARY_SHA,'root-captured preliminary seal FILE changed')
        record_path=V/'selection-preliminary-source-inventory.json';require(sha(record_path)==PRELIMINARY_RECORD_SHA,'preliminary inventory capture FILE changed')
        record=read_json(record_path)
        need(record.get('card')=='C05' and record.get('status')=='current_preliminary_source_inventory_only' and record.get('execution_freeze_sha256')==FREEZE_SHA,'preliminary capture belongs to another phase or freeze')
        need(record.get('manifest')=={'path':PRELIMINARY.relative_to(ROOT).as_posix(),'sha256':PRELIMINARY_SHA} and record.get('ordinary_count')==795 and record.get('predecessor_path_count')==764 and record.get('new_paths')==added and record.get('removed_paths')==[],'preliminary capture current795 path inventory differs')
        need(record.get('path_set_authority')=={'integration':'build/verification/c05-native-integration-start.json','sha256':INTEGRATION_SHA},'preliminary capture ownership authority differs')
    seal_status={'path':str(seal),'status':'pending'}
    if seal.is_file():
        entries,malformed=u.parse_manifest_paths(seal);names=[p for p,_ in entries]
        require(not malformed and names==ordinary and len(names)==len(set(names)),'new795 seal inventory is not exact canonical ordinary paths')
        bad=[p for p,h in entries if sha(ROOT/p)!=h];need(not bad,'new current seal checksum differences: '+str(bad))
        seal_status={'identity':pin(seal),'status':'audited_pass' if not bad else 'audit_error'}
    else:waiting('current C05 source seal absent',args.final)
    if args.final:need(seal==OFFICIAL,'final audit requires official selection-sources.sha256')
    doc_changes,approval=metadata_approval(integration,args.final,args.metadata_approval_sha256)
    for rel in ordinary:
        actual=sha(ROOT/rel)
        if rel in mapped:
            published=mapped[rel]['after']
            if actual!=published:
                change=doc_changes.get(rel,{})
                need(rel in ALLOWED_DOCS and change.get('before')==published and change.get('after')==actual and change.get('change_kind')=='verification_status_only','unreviewed mapped ordinary source drift: '+rel)
        else:need(baseline.get(rel)==actual,'unmapped ordinary bytes differ from captured integration baseline: '+rel)
    projection={};publication_ownership={}
    for name,digest in [('c01-native-integration-start.json',C01_INTEGRATION_SHA),('c02-native-integration-start.json',C02_INTEGRATION_SHA),('c05-native-integration-start.json',INTEGRATION_SHA)]:
        path=V/name;require(sha(path)==digest,'publication namespace ownership FILE changed: '+name);publication_ownership[name]=pin(path)
        for item in read_json(path)['mappings']:
            if Path(item['source']).suffix.lower() in {'.md','.markdown'}:
                need(sha(ROOT/item['source'])==item['after'],'frozen publication document changed')
                require(item['source'] not in projection or projection[item['source']]==item['destination'],'publication namespace alias conflict')
                projection[item['source']]=item['destination']
    base=u.local_destination
    def published(root,source,raw):
        item=base(root,projection.get(source,source),raw)
        if source in projection:item['publication_source_base']=projection[source]
        return item
    u.local_destination=published;markdown_inventory=u.markdown_paths(ROOT,ordinary)[0]
    links=u.audit_markdown(ROOT,ordinary);need(not links['documents_missing'] and not links['broken_local_destinations'],'Markdown source/link checks failed')
    schemas=u.schema_references();need(schemas['documents']==29,'native schema inventory differs from29');schema_mentions=documented_schemas(u,ordinary,projection)
    cm=read_text(ROOT/'CMakeLists.txt');need('docs/verification/' not in cm and '/tmp/crown' not in cm,'native CMake uses excluded paths')
    for var,count in [('CROWN_RUNTIME_SOURCES',14),('CROWN_EXPLAIN_SOURCES',6)]:
        match=re.search(r'set\('+var+r'\s+([^)]*)\)',cm,re.S);values=match[1].split() if match else []
        need(len(values)==count and all((ROOT/p).is_file() for p in values),'native source set changed: '+var)
    for anchor in ['target_link_libraries(crown_selection PUBLIC crown_ranking PRIVATE crown_options)','target_link_libraries(crown_selection_runtime PUBLIC crown_selection crown_ranking_runtime PRIVATE crown_options)','target_link_libraries(crown_selection_runtime_testing PUBLIC crown_selection crown_ranking_runtime_testing PRIVATE crown_options)']:
        need(anchor in cm,'native selection dependency direction changed: '+anchor)
    for p in list((ROOT/'src/runtime').glob('*.cpp'))+list((ROOT/'include/crown/runtime').glob('*.hpp')):
        need(not re.search(r'#\s*include\s+"crown/(?:observability/|io/(?:explain|query_explain|statistics_explain))',read_text(p)),'runtime/report include: '+str(p))
    for p in list((ROOT/'src/planner').glob('selection*'))+[ROOT/'include/crown/planner/selection.hpp']:
        if p.is_file():need(not re.search(r'#\s*include\s+"crown/(?:runtime/|observability/)',read_text(p)),'pure selection pulls runtime/report header: '+str(p))
    for p in (ROOT/'include/crown').rglob('*.hpp'):
        for header in re.findall(r'#\s*include\s+"(crown/[^\"]+)"',read_text(p)):need((ROOT/'include'/header).is_file(),'public include missing: '+header)
    properties=read_json(ROOT/'schemas/statistics-explain-v3.schema.json')['properties']['capabilities']
    need('c01_project_gate' not in properties['properties'] and 'c01_project_gate' not in properties['required'],'project acceptance leaked into native schema')
    matrix_path=V/'selection-matrix-evidence-audit.json';matrix={'status':'pending'}
    authority_path=V/'selection-matrix-audit-authority.json'
    if authority_path.exists() or authority_path.is_symlink() or args.matrix_authority_sha256 is not None:
        require(valid_digest(args.matrix_authority_sha256),'existing or supplied matrix authority requires an explicit SHA-256')
        require(authority_path.is_file(),'supplied matrix-authority identity has no corresponding FILE')
        require(sha(authority_path)==args.matrix_authority_sha256,'supplied matrix-authority FILE changed')
        require(matrix_path.is_file(),'supplied matrix authority has no canonical matrix receipt')
        matrix=accepted_matrix(matrix_path,freeze,args.matrix_authority_sha256)
    elif matrix_path.is_file() and read_json(matrix_path).get('accepted') is True:matrix=accepted_matrix(matrix_path,freeze,args.matrix_authority_sha256)
    else:waiting('complete independent C05 matrix audit not accepted',args.final)
    ledger=ledger_state(u,args.final,matrix,seal_status);phase=ledger['C05']
    if args.final:
        packet=ROOT/'docs/verification/selection-2026-11-07.md';need(packet.is_file(),'final C05 evidence packet absent');text=read_text(packet) if packet.is_file() else ''
        need('158' in text and '238' in text and 'selection-sources.sha256' in text and OFFICIAL.is_file() and sha(OFFICIAL) in text,'final C05 source/test/unit citations missing')
        need(set(doc_changes)==ALLOWED_DOCS and approval.get('status')=='audited_pass','all three native status guides must be finalized explicitly')
    if not args.final and not PENDING:PENDING.append('explicit --final invocation is required for final acceptance')
    for p,h in list(READ_PINS.items()):need(sha(Path(p))==h,'read input changed before publication: '+p)
    need(u.ordinary_inventory(ROOT)==ordinary,'ordinary source path inventory changed during audit')
    need(u.markdown_paths(ROOT,ordinary)[0]==markdown_inventory,'Markdown path inventory changed during audit')
    accepted=args.final and not ERRORS and not PENDING and matrix['status']=='audited_pass' and phase=='verified' and seal==OFFICIAL
    state='accepted_final_source_seal' if accepted else 'source_needs_review' if ERRORS else 'preliminary_pending_final_gates'
    return {'card':'C05','accepted':accepted,'audit_state':state,'requested_final':args.final,'auditor':pin(Path(__file__)),'historical_pure_utility':pin(UTILITY),'freeze':{'identity':pin(freeze_path),'native':NATIVE,'execution':EXECUTION,'historical_manifest_files':historical},'integration':pin(integration_path),'stage':pin(stage_path),'publication_ownership':publication_ownership,'ordinary_count':len(ordinary),'captured_predecessor_count':len(baseline),'added':added,'removed':removed,'seal':seal_status,'status_document_changes':doc_changes,'metadata_approval':approval,'markdown':links,'publication_namespace_map':projection,'schema_refs':schemas,'documented_schema_paths':schema_mentions,'matrix_prerequisite':matrix,'ledger':ledger,'read_evidence_sha256':READ_PINS,'errors':ERRORS,'pending':PENDING,'limits':'Current source/metadata and accepted raw matrix binding only. Historical source/INPUT entries are never re-evaluated; only their FILE identities are read. The ordinary baseline comes from the already accepted integration capture. Status-only semantics require explicit root review. Completion checkpoint is deliberately not an input and may be written afterward.'}


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--final',action='store_true');parser.add_argument('--seal',type=Path);parser.add_argument('--output',type=Path,required=True);parser.add_argument('--matrix-authority-sha256');parser.add_argument('--metadata-approval-sha256');args=parser.parse_args()
    output=args.output.resolve()
    allowed=(output.parent==V and re.fullmatch(r'selection-source-[A-Za-z0-9_.-]+\.json',output.name)) or str(output).startswith('/tmp/crown-c05-source-audit-review-')
    require(allowed and output.suffix=='.json','output must be a designated new source-audit JSON')
    require(not output.exists() and not output.is_symlink() and not output.with_suffix('.log').exists() and not output.with_suffix('.log').is_symlink(),'preserve existing source-audit evidence')
    try:result=audit(args)
    except (AuditError,OSError,ValueError,KeyError,TypeError,IndexError,AttributeError,UnicodeError) as error:
        ERRORS.append(type(error).__name__+': '+str(error))
        result={'card':'C05','accepted':False,'audit_state':'source_needs_review','requested_final':args.final,'audit_completed':False,'auditor':{'path':str(Path(__file__)),'sha256':READ_PINS.get(str(Path(__file__).resolve()))},'read_evidence_sha256':READ_PINS,'errors':ERRORS,'pending':PENDING}
    output.parent.mkdir(parents=True,exist_ok=True)
    with output.open('x',encoding='utf-8') as stream:stream.write(json.dumps(result,indent=2,sort_keys=True)+'\n')
    with output.with_suffix('.log').open('x',encoding='utf-8') as stream:stream.write(result['audit_state']+'\naccepted='+str(result['accepted'])+'\nerrors='+json.dumps(ERRORS)+'\npending='+json.dumps(PENDING)+'\n')
    print(result['audit_state'],'accepted='+str(result['accepted']),'ordinary='+str(result.get('ordinary_count','unavailable')),'errors='+str(len(ERRORS)),'pending='+str(len(PENDING)))
    return 1 if ERRORS else 0

if __name__=='__main__':raise SystemExit(main())
