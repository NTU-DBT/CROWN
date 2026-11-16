#!/usr/bin/env python3
"""Root-only C02 native/execution freeze after reviewed integration, before builds."""
from pathlib import Path
import csv
import datetime
import hashlib
import json
import re
import shlex

ROOT=Path('/home/userroot/Codex/CROWN')
V=ROOT/'build/verification'
P=ROOT/'docs/verification/c02-native-registration-proposal'
OUT=V/'ranking-execution-freeze.json'
NEW_TESTS=['ranking_binding','ranking_pure_link','ranking_contract','ranking_empty',
           'ranking_payload_time','ranking_census','ranking_exceptions',
           'ranking_normalized_exceptions','ranking_public_independent',
           'ranking_integer_independent','json_cleanup','json_patch_compatibility']
NATIVE_ROOTS=['include','src','apps','tests','cmake']
EXECUTION_ROOTS=NATIVE_ROOTS+['schemas','tools','third_party']


def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def relative(p):return p.relative_to(ROOT).as_posix()
def scope(roots,extra):
    paths=set(extra)
    for name in roots:
        paths.update(relative(p) for p in (ROOT/name).rglob('*') if p.is_file() and '__pycache__' not in p.parts and p.suffix not in {'.pyc','.pyo'})
    h=hashlib.sha256();files={}
    for rel in sorted(paths):
        b=(ROOT/rel).read_bytes();files[rel]=hashlib.sha256(b).hexdigest()
        h.update(rel.encode());h.update(b'\0');h.update(b);h.update(b'\0')
    return {'count':len(paths),'sha256':h.hexdigest()},files

def participates(rel,roots,extra):
    return rel in extra or rel.split('/')[0] in roots

def main():
    if OUT.exists():raise RuntimeError('preserve existing C02 freeze')
    integration_path=V/'c02-native-integration-start.json'
    integration=json.loads(integration_path.read_text())
    assert integration['applied'] is True
    # Bind every author-package FILE to the exact accepted integration record.
    # No historical source manifest is reopened for its entries here.
    for path,h in integration['publication_pins'].items():
        p=Path(path);p=p if p.is_absolute() else ROOT/p
        assert sha(p)==h,('publication FILE drift',str(p))
    previous=json.loads((V/'statistics-execution-freeze.json').read_text())
    source_map=list(csv.DictReader((P/'source-map.tsv').read_text().splitlines(),delimiter='\t'))
    assert len(source_map)==38
    for item in integration['mappings']:
        assert sha(ROOT/item['destination'])==item['after']
    native,native_files=scope(NATIVE_ROOTS,['CMakeLists.txt','CMakePresets.json'])
    execution,execution_files=scope(EXECUTION_ROOTS,['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'])
    for name,roots,extra,files in [('native',NATIVE_ROOTS,['CMakeLists.txt','CMakePresets.json'],native_files),('execution',EXECUTION_ROOTS,['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'],execution_files)]:
        expected=set(previous[name+'_file_sha256'])
        expected.update(item['native_destination'] for item in source_map if participates(item['native_destination'],roots,extra))
        assert set(files)==expected,(name,sorted(set(files)^expected))
    mapped={item['destination'] for item in integration['mappings']}
    captured_baseline=integration['baseline_entry_pins']
    for rel,h in execution_files.items():
        if rel not in mapped:
            expected=captured_baseline.get(str(ROOT/rel),captured_baseline.get(rel))
            assert expected is not None and expected==h,('unmapped execution byte drift',rel)
    assert native['count']==648 and execution['count']==705
    ordered=(P/'expected-ctests-ordered.txt').read_text().splitlines()
    prior=(P/'prior-ctests-ordered.txt').read_text().splitlines()
    assert len(ordered)==143 and len(set(ordered))==143 and len(prior)==131
    assert ordered[:131]==prior and ordered[131:]==NEW_TESTS
    assert sorted(prior)==previous['expected_test_names']
    archive_manifest=V/'c02-c01-predecessor-build-evidence.json'
    archive=json.loads(archive_manifest.read_text());assert archive['status']=='retained_and_hash_verified'
    def archived(rel):
        entry=next(x for x in archive['files'] if x['previous_path']==rel)
        p=ROOT/entry['retained_path'];assert sha(p)==entry['sha256'];return p
    registration=archived('build/release/CTestTestfile.cmake')
    assert re.findall(r'^add_test\(\[=\[(.*?)\]=\]',registration.read_text(),re.M)==prior
    old_db=archived('build/release/compile_commands.json')
    base_units=[]
    for entry in json.loads(old_db.read_text()):
        argv=entry.get('arguments') or shlex.split(entry['command'])
        output=argv[argv.index('-o')+1]
        m=re.fullmatch(r'CMakeFiles/(.+)\.dir/(.+)\.o',output);assert m,output
        source=relative(Path(entry['file']))
        assert m[2]==source
        base_units.append((m[1],source))
    assert len(base_units)==195 and len(set(base_units))==195
    new_units=[]
    for entry in csv.DictReader((P/'target-inventory.tsv').read_text().splitlines(),delimiter='\t'):
        new_units.extend((entry['target'],source) for source in entry['sources'].split(';'))
    units=base_units+new_units
    assert len(new_units)==19 and len(units)==214 and len(set(units))==214
    cache_values={}
    for name,folder in [('debug','debug'),('release','release'),('sanitize','sanitize'),('clang','clang-debug')]:
        cache=archived('build/'+folder+'/CMakeCache.txt')
        values={m[1]:m[2] for line in cache.read_text().splitlines() if (m:=re.fullmatch(r'([^/#][^:]*):[^=]+=(.*)',line))}
        keys=['CMAKE_C_COMPILER','CMAKE_CXX_COMPILER','CMAKE_BUILD_TYPE','CROWN_SANITIZERS','BUILD_TESTING']
        cache_values[name]={'path':relative(cache),'sha256':sha(cache),'values':{k:values[k] for k in keys}}
        cache_values[name]['compiler_files']={values[k]:sha(Path(values[k])) for k in ['CMAKE_C_COMPILER','CMAKE_CXX_COMPILER']}
    assert cache_values['clang']['values']['CMAKE_BUILD_TYPE']=='Debug'
    assert cache_values['clang']['values']['CMAKE_C_COMPILER'].endswith('clang-18')
    assert cache_values['clang']['values']['CMAKE_CXX_COMPILER'].endswith('clang++-18')
    helpers={}
    for name in ['crown-ranking-matrix.py','crown-ranking-symbols.py','crown-ranking-clean-evidence.py','crown-ranking-clean-matrix.py','crown-c02-native-integrate.py',Path(__file__).name]:
        p=Path('/tmp')/name;helpers[str(p)]=sha(p)
    for item in integration['historical_manifest_file_hashes'].values():
        assert sha(ROOT/item['path'])==item['sha256']
    assert sha(ROOT/'Refactor.md')==integration['refactor_sha256']
    record={'card':'C02','recorded_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
            'native':native,'execution':execution,'native_file_sha256':native_files,'execution_file_sha256':execution_files,
            'expected_ctest_count':143,'expected_test_names':sorted(ordered),'expected_test_names_in_order':ordered,
            'old_legacy_test_names_in_order':prior,'expected_compile_command_entries':214,
            'expected_compile_units':[{'target':t,'source':s} for t,s in sorted(units)],
            'configs':['debug','release','sanitize','clang','clean-source'],
            'historical_manifest_file_hashes':integration['historical_manifest_file_hashes'],
            'registration_manifest_sha256':integration['registration_manifest_sha256'],
            'independent_review_manifest_sha256':integration['independent_review_manifest_sha256'],
            'integration_record_sha256':sha(integration_path),
            'predecessor_generated_evidence':{'path':relative(archive_manifest),'sha256':sha(archive_manifest)},
            'predecessor_release_compile_database':{'path':relative(old_db),'sha256':sha(old_db)},
            'predecessor_toolchain_caches':cache_values,'root_execution_helpers':helpers,
            'scope':'Complete C02 native and execution inputs before five configurations; ordinary docs and final acceptance metadata are audited separately. Eleven historical manifest FILE identities remain fixed; their historical source entries are not rechecked.'}
    OUT.write_text(json.dumps(record,indent=2)+'\n')
    print(json.dumps({'native':native,'execution':execution,'expected_tests':143,'compile_entries':214,'freeze_sha256':sha(OUT)}),flush=True)
    return 0

if __name__=='__main__':raise SystemExit(main())
