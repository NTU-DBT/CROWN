#!/usr/bin/env python3
"""Guarded O07 documentation/seal transition; never runs or changes native tests."""
import datetime
import hashlib
import importlib.util
import json
from collections import Counter
from pathlib import Path

ROOT=Path('/home/userroot/Codex/CROWN')
VERIFY=ROOT/'build/verification'
def digest(path): return hashlib.sha256(path.read_bytes()).hexdigest()
def need(value,message):
    if not value: raise RuntimeError(message)

def main():
    source_helper=Path('/tmp/crown-observability-source-audit.py')
    need(digest(source_helper)=='83d131c8f92bab8eb3da72dcd644c566c90915aab42bce78de66146e324a09b5','source helper changed')
    spec=importlib.util.spec_from_file_location('source_audit',source_helper)
    audit=importlib.util.module_from_spec(spec);spec.loader.exec_module(audit)
    frozen_info,freeze=audit.frozen()
    matrix=audit.matrix_prerequisite(True,freeze)
    need(not audit.ERRORS and not audit.PENDING and matrix['status']=='audited_pass',
         'final matrix/freeze prerequisites not accepted: '+repr(audit.ERRORS+audit.PENDING))
    configs=['debug','release','sanitize','clang','clean-source']
    summaries={name:json.loads((VERIFY/f'observability-{name}-summary.json').read_text()) for name in configs}
    for name,data in summaries.items():
        need(data.get('test_count')==99 and data.get('source_stable') is True and data.get('exit_code')==0,
             name+' terminal successful99 summary required')
    need(not (ROOT/'docs/verification/observability-sources.sha256').exists(),'seal already exists; review instead of overwriting')
    ordinary=audit.ordinary_inventory(ROOT)
    need(len(ordinary)==691,'ordinary inventory changed')
    names=['README.md','docs/native_build.md','docs/task_ledger.md','docs/handoff.md',
           'docs/verification/observability-2026-11-07.md']
    original_bytes={rel:(ROOT/rel).read_bytes() for rel in names}
    originals={rel:value.decode('utf-8') for rel,value in original_bytes.items()}
    marker='P07 and the following preparation history describe their recorded source'
    need(originals['docs/handoff.md'].count(marker)==1,'handoff historical boundary missing or ambiguous')
    history=originals['docs/handoff.md'][originals['docs/handoff.md'].index(marker):]
    expected_text={
      'README.md':[
        'Native O07 EXPLAIN/metrics/trace integration is applied and verification is in progress.',
        'The Release build and seven new native tests pass; all99 tests across five\nconfigurations and the new source seal remain pending. See the\n[observability guide](docs/observability.md) and [working record](docs/verification/observability-2026-11-07.md).'],
      'docs/native_build.md':[
        'O07 native observability integration is applied and verification is in progress.',
        'The Release build and seven new tests pass; the complete99-test five-configuration\nmatrix and new source seal remain pending. See [observability.md](observability.md)\nand the [working record](verification/observability-2026-11-07.md).'],
      'docs/task_ledger.md':[
        'and O01–O03 are verified: 36 verified, three in progress (A02/O06/O07), 39 not started, 78 total.',
        'Next: verify integrated O07 across all native targets and five configurations, then seal its exact sources.']}
    for rel,anchors in expected_text.items():
        need(all(anchor in originals[rel] for anchor in anchors),'expected phase text changed: '+rel)
    rows=audit.task_rows(ROOT/'docs/task_ledger.md',True)
    need(len(rows)==len({r['id'] for r in rows})==78,'ledger must retain78 unique cards')
    need({r['id'] for r in rows}=={r['id'] for r in audit.task_rows(ROOT/'Refactor.md')},'ledger card scope changed')
    need(Counter(r['status'] for r in rows)==Counter({'verified':36,'in_progress':3,'not_started':39}),'ledger starting counts changed')
    need(sorted(r['id'] for r in rows if r['status']=='in_progress')==['A02','O06','O07'],'ledger starting phase changed')
    need(sum(line.startswith('| O07 Implement ') and '| in_progress |' in line
             for line in originals['docs/task_ledger.md'].splitlines())==1,'O07 row missing or changed')
    backup=VERIFY/'observability-final-document-backup'
    need(not backup.exists(),'final transition backup already exists')
    need(all((ROOT/rel).read_bytes()==value for rel,value in original_bytes.items()),'documents changed during preflight')
    backup.mkdir()
    for rel in names:
        target=backup/rel;target.parent.mkdir(parents=True,exist_ok=True)
        target.write_bytes(original_bytes[rel])
    readme=ROOT/'README.md';text=originals['README.md']
    old='Native O07 EXPLAIN/metrics/trace integration is applied and verification is in progress.'
    need(old in text,'README phase sentence changed')
    text=text.replace(old,'Native O07 EXPLAIN/metrics/trace integration passes all 99 tests in each of five build configurations.')
    old='The Release build and seven new native tests pass; all99 tests across five\nconfigurations and the new source seal remain pending. See the\n[observability guide](docs/observability.md) and [working record](docs/verification/observability-2026-11-07.md).'
    need(old in text,'README secondary phase text changed')
    text=text.replace(old,'The independent matrix audit records exact results; a current source seal is produced for final validation.\nSee the [observability guide](docs/observability.md) and\n[verified record](docs/verification/observability-2026-11-07.md).')
    readme.write_text(text)
    builddoc=ROOT/'docs/native_build.md';text=originals['docs/native_build.md']
    old='O07 native observability integration is applied and verification is in progress.'
    need(old in text,'build guide phase sentence changed')
    text=text.replace(old,'O07 native observability integration passes all 99 tests across GCC Debug/Release, ASan+UBSan, Clang Debug and a fresh source-only Release build.')
    old='The Release build and seven new tests pass; the complete99-test five-configuration\nmatrix and new source seal remain pending. See [observability.md](observability.md)\nand the [working record](verification/observability-2026-11-07.md).'
    need(old in text,'build guide secondary phase text changed')
    text=text.replace(old,'The independent matrix audit records exact results; the current source seal awaits final source validation.\nSee [observability.md](observability.md) and the\n[verified record](verification/observability-2026-11-07.md).')
    builddoc.write_text(text)
    ledger=ROOT/'docs/task_ledger.md';lines=originals['docs/task_ledger.md'].splitlines()
    found=0
    for i,line in enumerate(lines):
        if line.startswith('| O07 Implement '):
            need('| in_progress |' in line,'O07 ledger not in expected phase')
            lines[i]='| O07 Implement EXPLAIN, metrics and diagnostic traces | verified | Immutable physical/runtime/session/query reports, four closed V2/V1 schemas, bounded exports, explicit mode/context/cursor/gauge/trace ownership and native CLI dispatch. Independent literal/oracle, clock, lifecycle, allocation-failure, schema and disable-parity preparation pass. All 99 tests pass five configurations on unchanged native585/execution635 inputs; independent matrix audit accepts numeric/compiler/parser/export evidence. The 691-source seal is produced; final source audit acceptance is required before completion is recorded in [evidence](verification/observability-2026-11-07.md). |'
            found+=1
        elif line.startswith('G0 remains open '):
            lines[i]=line.replace('and O01–O03 are verified: 36 verified, three in progress (A02/O06/O07), 39 not started, 78 total.', 'and O01–O03/O07 are verified: 37 verified, two in progress (A02/O06), 39 not started, 78 total.')
        elif line.startswith('Next: verify integrated O07 '):
            lines[i]=line.replace('Next: verify integrated O07 across all native targets and five configurations, then seal its exact sources.', 'Next: preserve the verified O07 source seal, then develop and integrate C01 bounded statistics from the excluded reviewed proposals.')
    need(found==1,'O07 ledger row not unique')
    ledger.write_text('\n'.join(lines)+'\n\nO07 verified status is staged conditionally until the final source audit is accepted.\n')
    seal=ROOT/'docs/verification/observability-sources.sha256'
    ordinary=audit.ordinary_inventory(ROOT)
    need(len(ordinary)==691,'final ordinary inventory changed')
    seal.write_text(''.join(digest(ROOT/rel)+'  '+rel+'\n' for rel in ordinary))
    seal_sha=digest(seal)
    labels={'debug':'GCC Debug','release':'GCC Release','sanitize':'ASan + UBSan + leak checking (sanitizer)',
            'clang':'Clang Debug','clean-source':'Fresh source-only Release'}
    table='\n'.join('| '+labels[name]+' | 99/99 | '+str(summaries[name]['ctest_seconds'])+' |' for name in configs)
    packet=f'''# O07 EXPLAIN, metrics and traces — verified candidate

**O07 verified candidate; final source audit required.** All five native configurations pass all 99 tests on one
frozen revision. The staged ledger has 37 verified, two in
progress (A02/O06), 39 not started; O07 acceptance is conditional on the final
source audit. The full 78-card goal remains active. No public release gate is claimed.

| Configuration | Tests | CTest seconds |
| --- | --- | ---: |
{table}

Native integration includes immutable physical/runtime/session/query reports,
the metrics registry and sampled causal trace, human/JSON/DOT/tree JSON exports,
four closed versioned schemas, and the native `crown explain` dispatcher.
Height evidence remains distinct from cost-search status. Current modes,
requested/resolved options, initialization/context, trace sampling, cursor
work/timing, gauges and unavailable components are explicitly represented.

Six new test executables and seven CTest cases preserve all original 92 names
and commands. Standalone preparation includes all 437 query inputs under both
policies against the independent literal oracle and genuine replay, 2,192 report
artifacts, 1,133 cursor checks, 74 composed artifacts, owner/clock/fault/lifetime
coverage, and the final CLI fixture corpus. These are supplemental to the full
native matrix, whose exact per-test results and raw logs are independently audited.

The final native 585 fingerprint is
`9ca9005001bda9e56faa0951077e53fc106450d7350bf185cd62556a7af25d0a`.
The complete execution 635 fingerprint is
`8ae45108daed5530d67372c93b46bb198bf694a5c8bf429cb6905d4b367bbf12`.
All five before/after maps match. The fresh source-only snapshot matches both
inventories, passes all tests and is removed after retained evidence collection.
Freeze: `build/verification/observability-execution-freeze.json`.

The independent [matrix review](observability-matrix-review-2026-11-07.md)
accepts exact 99-name results, all five terminal summaries, 178 structured
numeric rows in each in-place configuration, 157 raw CMake compile commands,
96 vendored parser C units, strict project warnings and separate production/
testing runtime closures. Thirteen historical allocation-only rows have explicit
metadata-layout deltas; the other 152 retain exact values. These inventories
have different meanings. Hidden Make recipes are not expanded executed argv.
The clean build retains the same GNUmake jobserver note and two upstream upb
maybe-uninitialized diagnostics as P07, matched by exact identities/counts and
pinned vendor inputs. They are not claimed fixed or harmless; unexpected or
project warnings still fail. Production archives exclude testing probes;
testing variants expose the expected hooks. Parser sanitizer references include
both ASan and UBSan. Raw evidence: `build/verification/observability-*`.

The [691-source current seal](observability-sources.sha256) has SHA-256
`{seal_sha}`. It contains the previous 592 path inventory plus 99 new paths,
with no removals. All nine historical manifest FILE identities and original
Refactor.md are preserved. Older entry checksums describe older source snapshots
and are not revalidated against current files. The independent final source
audit checks this seal, current links/schema references, integration boundaries,
all 78 ledger cards and accepted matrix artifact identities.

See [observability guide](../observability.md), [native build guide](../native_build.md)
and [AntiGravity handoff](../handoff.md). S05 total allocator bytes, O04/O05
recovery, O06 durable delivery, C01/C02 statistics/cost work, benchmarks and O08
public workflow/release remain open. DOT acceptance is lexical; Graphviz was
not installed or run. Source-position acknowledgement does not imply durability.
'''
    (ROOT/'docs/verification/observability-2026-11-07.md').write_text(packet)
    handoff=ROOT/'docs/handoff.md'
    top=f'''# AntiGravity / coding-agent handoff

Updated: 2026-11-07 (Asia/Shanghai); O07 verified candidate awaiting final source audit; complete 78-card goal active.
Work is uncommitted on `master`, baseline
`e369a623517723b3be3ea3e9806779f3c591e7f9`. `.git` is read-only.
Preserve original Refactor.md and every legacy directory. Use Luna with Max
thinking for focused work and Astra with Max thinking for complex tasks.

## Current checkpoint

**O07 verified candidate; final source audit required.** Native EXPLAIN/metrics/traces, immutable reports, four
schemas, CLI dispatch and separate production/testing closures are integrated.
All 99 tests pass GCC Debug, GCC Release, ASan+UBSan/leak checking (sanitizer),
Clang Debug and fresh source-only Release. All five matrix sessions are terminal
and closed; the clean temporary tree is removed. Staged ledger totals, conditional
on the final source audit: **37 verified,
two in progress (A02/O06), 39 not started, 78 total**. The full goal remains active.

| Configuration | Tests | CTest seconds |
| --- | --- | ---: |
{table}

The independent matrix audit accepts exact per-test results, source stability,
178 numeric rows, 157 CMake compile commands, 96 parser C units, warning policy,
variant closure and production/testing exports. These are distinct inventories.
Current [O07 evidence](verification/observability-2026-11-07.md) and
[691-source seal](verification/observability-sources.sha256), SHA-256
`{seal_sha}`, are authoritative. Preserve all nine older manifest FILE hashes;
their entry checksums describe historical snapshots. Native585 fingerprint
`9ca9005001bda9e56faa0951077e53fc106450d7350bf185cd62556a7af25d0a` and
execution635 fingerprint
`8ae45108daed5530d67372c93b46bb198bf694a5c8bf429cb6905d4b367bbf12` match before
and after every configuration. Records and raw logs use `build/verification/observability-*`.

The matrix helper is `/tmp/crown-observability-matrix-audit.py`, SHA
`6cde7a41b911e24403406bee3ada8bd940816251783133b22319323cb8299241`.
The source helper is `/tmp/crown-observability-source-audit.py`, SHA
`83d131c8f92bab8eb3da72dcd644c566c90915aab42bce78de66146e324a09b5`.
Run the source helper with `--final` and retain its zero-error accepted result
before starting native C01 edits. The exact helper hash is pinned by its review
and audit JSON; the summary line here must match that record.

C01 remains not_started. Its [preflight](verification/c01-statistics-preflight-2026-11-07.md)
and excluded state/online/reference/benchmark packages are preparatory. Both
actual-owner state capture and online hooks now pass strict and complete
ASan+UBSan+leak closures independently:32owner/storage ordinary groups and
five sweeps (100owner/copy plus34storage positions), and10online groups plus
collector regressions with6/278/16configuration/update/mode fault positions.
See [owner results](verification/c01-statistics-owner-root-results-2026-11-07.md)
and [online results](verification/c01-statistics-online-root-results-2026-11-07.md).
The independent [literal reference](verification/c01-statistics-literal-reference-root-results-2026-11-07.md)
passes25scopes/18inputs. The [component benchmark](verification/c01-statistics-benchmark-root-results-2026-11-07.md)
is measured but does not establish native engine overhead. Preserve all frozen
packages and failed attempts. Next create a combined excluded proposal, check
joint owner/epoch/plan/reset/mode lifecycles and separate runtime variants,
then finish compatible EXPLAIN/schema exports and measured native overhead
before native C01 integration/matrix. The combined overlay is now active with
Astra Max, and Luna Max is drafting the API guide. Earlier transient thread
limits were resolved by reusing existing agents. These activities remain excluded.

S04/S05 storage/accounting, O04/O05/O06 recovery/delivery, cost/extension/
experimental work and release gates remain open. A02 still needs distribution
license disposition. No R0/R1 release is claimed. The original 78 cards remain
the scope; completing O07 does not complete this goal.

'''
    handoff.write_text(top+history)
    checkpoint=VERIFY/'observability-preparation-checkpoint.json'
    data=json.loads(checkpoint.read_text());now=datetime.datetime.now(datetime.timezone.utc).isoformat()
    data.update(updated_utc=now,O07='verified candidate phase staged for final source audit; no completion recorded',completion_audit_accepted=False,
                ledger_counts={'verified':37,'in_progress':2,'not_started':39},native_build_or_test_jobs_active=False,
                native_jobs_active=[],remaining_O07_gates=['execute final source audit and record accepted result'])
    data['final_matrix_results']={name:{'passed':True,'tests':99,'ctest_seconds':summaries[name]['ctest_seconds'],
              'source_stable':True,'summary':f'build/verification/observability-{name}-summary.json'} for name in configs}
    data['current_source_seal']={'path':str(seal.relative_to(ROOT)),'count':691,'sha256':seal_sha}
    checkpoint.write_text(json.dumps(data,indent=2)+'\n')
    jobs=VERIFY/'observability-matrix-jobs.json';data=json.loads(jobs.read_text())
    for job in data['jobs']:
        name=job['configuration'];job.update(status='passed_terminal_closed',ctest_count=99,
                    ctest_seconds=summaries[name]['ctest_seconds'],summary=f'build/verification/observability-{name}-summary.json')
    data['updated_utc']=now;data['native_jobs_active']=[];data['clean_source']='passed; temporary tree removed'
    jobs.write_text(json.dumps(data,indent=2)+'\n')
    print('O07 matrix accepted; final691-source seal produced: '+seal_sha)
    print('Run /tmp/crown-observability-source-audit.py --final, add the actual accepted result to excluded documentation, rerun --final, then record completion.')

if __name__=='__main__': main()
