#!/usr/bin/env python3
"""DRAFT: root-only C05 execution freeze; never replays historical seal entries."""
from pathlib import Path
import csv, datetime, hashlib, json, re, shlex

ROOT = Path('/home/userroot/Codex/CROWN')
V = ROOT/'build/verification'
P = ROOT/'docs/verification/c05-native-registration-proposal'
I = ROOT/'docs/verification/c05-native-registration-independent-review-proposal'
IMPLEMENTATION = ROOT/'docs/verification/c05-selection-implementation-proposal'
OUT = V/'selection-execution-freeze.json'
INTEGRATION_SHA = '9f8824f17f90bf6c1cc8caf89d3abc66adedd0083e38b88fcc8a11b944be66e0'
STAGE_SHA = '38ce409eca1d52cffcf5d3478f7fdc8820135822ed6c611146e5d5bffdf60479'
PUBLICATION_SHA = 'c4c7078a5c3159588eb4c609084053363369619391095a6c27f9dc3b0e13f4af'
REVIEW_SHA = '2e26cde2722464aca87f88c5450e3d00554fe6bb4395002d6f8147394880108e'
PREDECESSOR_SHA = 'b21d69747ea69f0a7d7d86ffd9c372dc47eee5020ee4f0e386a5b45cc1616561'
PREPARATION_REGISTRY_SHA = '286a1350f919811805f73c1c039c6183eb2a59dceffdf2722b50655f454fd3d7'
REFACTOR_SHA = 'bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce'
NEW_TESTS = ['selection_pure_link','selection_contract','selection_cache','selection_source','selection_current',
             'selection_binding','selection_resources','selection_census','selection_exception',
             'selection_normalized_exception','selection_public_independent','selection_cache_independent',
             'selection_resources_independent','selection_binding_independent','selection_publication_fault_independent']
NATIVE_ROOTS = ['include','src','apps','tests','cmake']
EXECUTION_ROOTS = NATIVE_ROOTS + ['schemas','tools','third_party']
HELPERS = ['crown-selection-matrix.py','crown-selection-symbols.py','crown-selection-clean-evidence.py',
           'crown-selection-clean-matrix.py','crown-selection-execution-freeze.py']
ROLES = ['plan','planner_testing','runtime','runtime_testing','explain','explain_testing','ranking',
         'ranking_runtime','ranking_runtime_testing','selection','selection_runtime','selection_runtime_testing']

def need(value, message):
    if not value: raise RuntimeError(message)
def sha(path): return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def absolute(name):
    p = Path(name)
    return p if p.is_absolute() else ROOT/p
def relative(path): return Path(path).relative_to(ROOT).as_posix()
def canonical_pins(pins):
    result = {}
    for name, digest in pins.items():
        p = absolute(name).resolve()
        need(re.fullmatch(r'[0-9a-f]{64}', digest) is not None, 'invalid FILE digest')
        need(p not in result or result[p] == digest, 'conflicting canonical aliases: '+str(p))
        result[p] = digest
    return result

def scope(roots, extra):
    names = set(extra)
    for name in roots:
        names.update(relative(p) for p in (ROOT/name).rglob('*') if p.is_file()
                     and '__pycache__' not in p.parts and p.suffix not in {'.pyc','.pyo'})
    digest = hashlib.sha256(); files = {}
    for name in sorted(names):
        data = (ROOT/name).read_bytes(); files[name] = hashlib.sha256(data).hexdigest()
        digest.update(name.encode()); digest.update(b'\0'); digest.update(data); digest.update(b'\0')
    return {'count':len(names),'sha256':digest.hexdigest()}, files

def main():
    need(not OUT.exists(), 'preserve existing C05 execution freeze')
    integration_path = V/'c05-native-integration-start.json'
    need(sha(integration_path) == INTEGRATION_SHA, 'integration receipt changed')
    integration = json.loads(integration_path.read_text())
    need(integration['card'] == 'C05' and integration['applied'] is True
         and integration['phase'] == 'guarded_native_application_applied', 'application incomplete')
    need(sha(P/'PACKAGE_SHA256SUMS') == PUBLICATION_SHA and sha(I/'PACKAGE_SHA256SUMS') == REVIEW_SHA,
         'accepted publication/review FILE changed')
    manifest_files = {}
    for name, item in integration['manifest_verifications'].items():
        need(sha(absolute(name)) == item['sha256'], 'manifest FILE drift: '+name)
        manifest_files[name] = item['sha256']
    captured = {}
    for group in integration['manifest_input_pins'].values():
        for name, digest in group.items():
            need(name not in captured or captured[name] == digest, 'conflicting captured FILE pin')
            captured[name] = digest
    immutable = {}
    for path, digest in canonical_pins(captured).items():
        if any(path.is_relative_to(root.resolve()) for root in (P,I,IMPLEMENTATION)):
            need(sha(path) == digest, 'immutable publication/preparation drift: '+str(path))
            immutable[str(path)] = digest
    for name in ['source-map.tsv','target-inventory.tsv','expected-ctests-ordered.txt','prior-ctests-ordered.txt','new-ctests-ordered.txt']:
        need(str((P/name).resolve()) in immutable, 'unbound inventory: '+name)
    for name, digest in integration['accepted_precursor_summaries'].items():
        need(sha(V/name) == digest, 'accepted precursor FILE drift: '+name)
    stage_path = V/'c05-publication-stage-build-attempt-1.json'
    need(sha(stage_path) == STAGE_SHA, 'stage receipt changed')
    stage = json.loads(stage_path.read_text())
    need(stage['status'] == 'passed_staged_registration_and_new_consumers' and stage['source_stable'] is True,
         'stage not passed/source-stable')
    need(stage['registered_tests'] == 158 and stage['old_test_prefix_preserved'] == 143 and stage['executed_new_tests'] == 15
         and len(stage['fresh_compiles']) == 24 and stage['new_archives'] == 3 and len(stage['new_links']) == 15,
         'stage population differs')
    previous = json.loads((V/'ranking-execution-freeze.json').read_text())
    accepted_matrix_path = V/'ranking-matrix-evidence-audit.json'
    accepted_matrix = json.loads(accepted_matrix_path.read_text())
    need(accepted_matrix.get('accepted') is True and accepted_matrix.get('audit_state') == 'accepted_final_matrix',
         'predecessor matrix is not accepted')
    accepted_raw = accepted_matrix['read_evidence_sha256']
    rows = list(csv.DictReader((P/'source-map.tsv').read_text().splitlines(), delimiter='\t'))
    need(len(rows) == 34 and len({r['native_destination'] for r in rows}) == 34, 'expected exact34map')
    mapped = {item['destination']:item for item in integration['mappings']}
    need(len(integration['mappings']) == 34 and set(mapped) == {r['native_destination'] for r in rows}, 'map population differs')
    for row in rows:
        name = row['native_destination']; item = mapped[name]
        need(item['source'] == relative(P/row['overlay_file']), 'mapped source differs: '+name)
        need(sha(P/row['overlay_file']) == item['after'] == sha(ROOT/name), 'mapped after-byte drift: '+name)
    native, native_files = scope(NATIVE_ROOTS, ['CMakeLists.txt','CMakePresets.json'])
    execution, execution_files = scope(EXECUTION_ROOTS, ['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'])
    for name, roots, extra, files in [('native',NATIVE_ROOTS,['CMakeLists.txt','CMakePresets.json'],native_files),
                                    ('execution',EXECUTION_ROOTS,['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'],execution_files)]:
        # Predecessor freeze contributes pathnames only, never old entry hashes.
        expected = set(previous[name+'_file_sha256'])
        expected.update(r['native_destination'] for r in rows
                        if r['native_destination'] in extra or r['native_destination'].split('/')[0] in roots)
        need(set(files) == expected, name+' path set differs from old plus reviewed additions')
    baseline = canonical_pins(integration['baseline_entry_pins'])
    for name, digest in execution_files.items():
        if name not in mapped:
            need(baseline.get((ROOT/name).resolve()) == digest, 'fresh unmapped baseline drift: '+name)
    need(native['count'] == 676 and execution['count'] == 733, 'derived 648+28 / 705+28 scopes differ')
    ordered = (P/'expected-ctests-ordered.txt').read_text().splitlines()
    prior = (P/'prior-ctests-ordered.txt').read_text().splitlines()
    need(len(ordered) == len(set(ordered)) == 158 and len(prior) == 143, 'test population differs')
    need(ordered == prior+NEW_TESTS and prior == previous['expected_test_names_in_order'], 'old143/new15 order differs')
    predecessor_path = V/'c05-c02-predecessor-build-evidence.json'
    need(sha(predecessor_path) == PREDECESSOR_SHA, 'predecessor receipt changed')
    predecessor = json.loads(predecessor_path.read_text())
    need(predecessor['status'] == 'captured_pass' and predecessor['predecessor'] == 'C02verified', 'predecessor not captured')
    def retained(name):
        matches = [r for r in predecessor['records'] if r['original'] == name]
        need(len(matches) == 1 and matches[0]['accepted_raw_pin'] is True, 'missing accepted predecessor record: '+name)
        need(accepted_raw.get(name) == matches[0]['sha256'], 'retained FILE is not the accepted predecessor raw pin: '+name)
        p = ROOT/matches[0]['retained']
        need(sha(p) == matches[0]['sha256'], 'retained predecessor FILE drift: '+name)
        return p
    registration = retained('build/release/CTestTestfile.cmake')
    need(re.findall(r'^add_test\(\[=\[(.*?)\]=\]', registration.read_text(), re.M) == prior, 'actual old ordered tests differ')
    old_db = retained('build/release/compile_commands.json'); old_units = []
    for entry in json.loads(old_db.read_text()):
        argv = entry.get('arguments') or shlex.split(entry['command'])
        output = argv[argv.index('-o')+1]
        match = re.fullmatch(r'CMakeFiles/(.+)\.dir/(.+)\.o', output)
        need(match is not None and match[2] == relative(Path(entry['file'])), 'old target/source mismatch')
        old_units.append((match[1],match[2]))
    new_units = [(r['target'],r['source']) for r in csv.DictReader((P/'target-inventory.tsv').read_text().splitlines(), delimiter='\t')]
    units = old_units+new_units
    need(len(old_units) == len(set(old_units)) == 214 and len(new_units) == 24 and len(units) == len(set(units)) == 238,
         'compile-unit population differs')
    caches = {}; canonical_compilers = {}
    for label, folder in [('debug','debug'),('release','release'),('sanitize','sanitize'),('clang','clang-debug')]:
        p = retained('build/'+folder+'/CMakeCache.txt')
        values = {m[1]:m[2] for line in p.read_text().splitlines() if (m := re.fullmatch(r'([^/#][^:]*):[^=]+=(.*)',line))}
        keys = ['CMAKE_C_COMPILER','CMAKE_CXX_COMPILER','CMAKE_BUILD_TYPE','CROWN_SANITIZERS','BUILD_TESTING']
        authority = previous['predecessor_toolchain_caches'][label]
        need({k:values[k] for k in keys} == authority['values'], 'accepted compiler/configuration choices changed: '+label)
        audited = accepted_matrix['closing_source_guard']['toolchains'][label]
        need(audited['values'] == authority['values'] and audited['compiler_files'] == authority['compiler_files'],
             'predecessor freeze/matrix compiler authorities disagree: '+label)
        compilers = dict(authority['compiler_files'])
        need(set(compilers) == {values[k] for k in ['CMAKE_C_COMPILER','CMAKE_CXX_COMPILER']}, 'compiler alias population differs')
        for path, digest in compilers.items():
            key = str(Path(path).resolve())
            aliases = {name:value for name,value in accepted_raw.items() if absolute(name).resolve() == Path(key)}
            need(aliases and set(aliases.values()) == {digest}, 'accepted canonical compiler aliases conflict or are absent')
            need(sha(path) == digest == sha(key), 'compiler bytes changed since accepted predecessor: '+path)
            need(key not in canonical_compilers or canonical_compilers[key] == digest, 'compiler alias conflict')
            canonical_compilers[key] = digest
        caches[label] = {'path':relative(p),'sha256':sha(p),'values':{k:values[k] for k in keys},'compiler_files':compilers}
    need(caches['clang']['values']['CMAKE_BUILD_TYPE'] == 'Debug', 'Clang build type changed')
    need(caches['clang']['values']['CMAKE_C_COMPILER'].endswith('clang-18') and
         caches['clang']['values']['CMAKE_CXX_COMPILER'].endswith('clang++-18'), 'Clang toolchain changed')
    helpers = {str(Path(__file__).resolve().with_name(name)):sha(Path(__file__).resolve().with_name(name)) for name in HELPERS}
    runner = Path(integration['runner'])
    need(sha(runner) == integration['runner_sha256'], 'integration runner FILE drift')
    helpers[str(runner)] = integration['runner_sha256']
    history = integration['historical_manifest_file_hashes']
    need(len(history) == 12, 'expected twelve historical seal FILEs')
    for item in history.values(): need(sha(ROOT/item['path']) == item['sha256'], 'historical seal FILE drift')
    need(sha(ROOT/'Refactor.md') == REFACTOR_SHA, 'original Refactor FILE drift')
    registry = V/'c05-selection-root-jobs.json'
    need(sha(registry) == PREPARATION_REGISTRY_SHA, 'immutable preparation registry drift')
    record = {
        'card':'C05','recorded_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'native':native,'execution':execution,'native_file_sha256':native_files,'execution_file_sha256':execution_files,
        'expected_ctest_count':158,'expected_test_names':sorted(ordered),'expected_test_names_in_order':ordered,
        'old_legacy_test_names_in_order':prior,'expected_compile_command_entries':238,
        'expected_compile_units':[{'target':t,'source':s} for t,s in sorted(units)],
        'added_compile_units':[{'target':t,'source':s} for t,s in new_units],
        'incremental_partition_expectation':{'fresh':24,'cached':214,'actual_partition':'must_be_observed_and_audited'},
        'clean_partition_expectation':{'fresh':238,'cached':0},
        'configs':['debug','release','sanitize','clang','clean-source'],'symbol_roles':ROLES,
        'historical_manifest_file_hashes':history,'manifest_file_pins':manifest_files,'immutable_publication_file_pins':immutable,
        'registration_manifest_sha256':PUBLICATION_SHA,'independent_review_manifest_sha256':REVIEW_SHA,
        'integration_record_sha256':INTEGRATION_SHA,'stage_receipt_sha256':STAGE_SHA,
        'predecessor_generated_evidence':{'path':relative(predecessor_path),'sha256':PREDECESSOR_SHA},
        'predecessor_release_compile_database':{'path':relative(old_db),'sha256':sha(old_db)},
        'predecessor_toolchain_caches':caches,'canonical_compiler_files':canonical_compilers,'root_execution_helpers':helpers,
        'predecessor_compiler_authority':{'freeze':'build/verification/ranking-execution-freeze.json',
                                         'freeze_sha256':sha(V/'ranking-execution-freeze.json'),
                                         'matrix':relative(accepted_matrix_path),'matrix_sha256':sha(accepted_matrix_path),
                                         'scope':'Exact accepted compiler aliases/bytes and cache choices; no new compiler identity is admitted.'},
        'clean_original_helper_sha256':execution_files['tools/verify_clean_build.py'],
        'sanitizer_schedule':{'other_terminal_legs':['debug','release','clang','clean-source'],
                              'quiescence_receipt':'build/verification/selection-sanitize-quiescence.json',
                              'decision':'accepted_quiescent_sanitizer_window'},
        'wrapper_timeout_seconds':{'configure':7200,'build':7200,'test':86400,'clean_total':108000},
        'native_live_registry':'build/verification/c05-native-root-jobs.json',
        'immutable_preparation_registry':{'path':relative(registry),'sha256':PREPARATION_REGISTRY_SHA},
        'scope':'Execution freeze only; no matrix acceptance. Mapped after bytes and fresh integration baseline bind execution. Historical manifest FILEs only; ordinary status documents audited separately.'}
    with OUT.open('x') as handle: handle.write(json.dumps(record,indent=2)+'\n')
    print(json.dumps({'native':native,'execution':execution,'expected_tests':158,'compile_entries':238,'freeze_sha256':sha(OUT)}),flush=True)
    return 0

if __name__ == '__main__': raise SystemExit(main())
