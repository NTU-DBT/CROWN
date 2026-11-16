# O08 CLI and embeddable API acceptance

O08 is verified on 10 November 2026. The complete Refactor.md goal remains
active: 46 cards are verified, A02 remains in progress, and 31 have not started.
Work is uncommitted on baseline `e369a623517723b3be3ea3e9806779f3c591e7f9`.
This is local development packaging; no R1 release or publication is claimed.

## Acceptance scope

The [O08 card and Section 8.5](../../Refactor.md) require a user to compile an
unseen supported SQL query, load input, inspect its plan, consume results,
checkpoint and restore using public interfaces. The implementation provides
those commands, bounded trace verification and a scoped durable-file benchmark,
versioned headers and transport schemas, structured diagnostics, installation
instructions and a generic public API example. See the [CLI guide](../cli.md).

The selected matrix covers all 17 previous CLI/schema regressions and the two
new workflow/package tests. It does **not** claim a full 266-test release run.
All existing native runtime implementations and prior tests are byte-identical
to the [O05/O06 predecessor](o05-o06-native-acceptance-2026-11-10.md), whose full
264-test, five-configuration acceptance remains separately recorded. Generated
commands and properties for all 264 predecessor tests remain unchanged after
source/build path normalization. There are now 266 registered tests.

| Configuration | Selected tests passed | Test wall time |
| --- | --- | --- |
| GCC 13 Debug | 19/19 | 70.29 s across two archived invocations |
| GCC 13 Release | 19/19 | 13.77 s |
| Clang 18 Debug | 19/19 | 42.42 s |
| GCC 13 ASan + UBSan, leak detection | 19/19 | 221.35 s |
| Fresh source-only GCC 13 Release | 19/19 | 13.66 s |

All CROWN compilation uses C++23 and the existing strict warning/error policy.
Sanitizer tests inherit `detect_leaks=1:halt_on_error=1` and UBSan halt/stacktrace
settings, including their installed consumer subprocesses. The parser archive
is instrumented too; configuration and ASan/UBSan symbol checks are recorded.

## Functional evidence

Five independently prepared fixtures contain 34 physical input events. The
workflow test performs 259 public CLI checks covering full and proper
projection, self-join loop/new-new cases, scalar EXISTS, disconnected products,
all five native scalar types, int64 boundaries, UTF-8/NUL strings, dates and
exact decimal spellings. Every event's raw signed delta, complete current rows,
duplicate absence and source position are checked against the independent
oracle. Initial Boolean state and empty epochs are included.

The tests exercise new-process recovery, checkpoint rotation and verified
retirement, explicit query/sink IDs and incorrect-ID rejection. Four compiled
EXPLAIN formats leave files unchanged. Typed minimum-height proof replay,
constant-false handling, malformed versions/proofs/options, output caps and
reference work/event/byte guards are checked. Compiled artifacts and successful
and failed command reports are validated against closed versioned schemas.
Both benchmark modes match oracle state and actual delivery receipts; timing
partitions and actual observation/run context are checked.

The package test installs and moves the prefix, then configures a copied public
example outside the source and build trees. Its 18 subprocess commands exercise
all five SQL cases: consume two events, rotate, and restore one more in another
process. Exact rows, source positions and verified output epochs match the
oracle. The consumer inherits C++23 and uses installed headers/libraries only;
it links no testing or reference archive. The installed CLI's optional reference
diagnostics are separate from that production library closure.

The guide's preparation helper and compile/validate/explain/run/results/
checkpoint/restore sequence also passed nine commands against the development
CLI. Exclusive helper output creation preserves an existing output file.

## Source, build and review records

All evidence paths below are relative to `build/verification/`:

- `o08-workflow-native-inputs-v1.json` freezes 1,140 source/input/document paths.
  The exact source-only copy contains only those files and no earlier objects
  or CMake cache. All 1,102 predecessor paths have preserved preimages.
- `o08-workflow-native-matrix-audit-v1.json` binds the selected results, original
  test definitions and 895 actual build artifacts: five CLI ELFs, 605 C++
  objects, 80 CROWN archives, five parser archives, 170 flags/link records and
  30 build metadata files. Each configuration builds 15 production archives
  and one reference archive used by CLI diagnostics.
- Per-mode configure/build/CTest/driver receipts retain commands, timestamps,
  exit codes, source manifests and log hashes. CTest stdout was archived before
  later enumeration. Every launched driver was observed terminal with exit 0;
  no build overlapped CTest in the same directory.
- `o08-workflow-native-requirement-audit-v2.json` records eight O08 requirements
  and their source/test evidence. Root implemented and reviewed production
  code; Luna Max supplied bounded independent fixtures and a guide draft.
  No Astra agent was used for this O08 work.
- `o08-workflow-native-upstream-warning-review-v1.json` records only pinned
  upstream C/Make diagnostics. A newly observed sanitizer warning concerns
  PostgreSQL `namestrcpy`: its bounded zero-padding copy is immediately followed
  by a final NUL write. The source matches the pinned archive. No project C++
  warning, source patch or warning-policy change was accepted.
- `o08-workflow-native-guide-example-v1.json`, registration review, Git
  provenance, final source successor and checkpoint seal retain the remaining
  example, compatibility and handoff evidence.

The development compiler fix exports an owning Row only at the independent
reference boundary; maintained execution gains no Row mirror. The initial
constant-false test used an absent column and was corrected to quote the actual
catalog column. Auxiliary audit checks were corrected for the legitimate
build-versus-test schema snapshot and Make recursion level. No native test,
assertion, timeout, resource cap or runtime implementation was weakened.

## Limits and remaining work

Height proof establishes structural minimum only. Benchmark output describes a
single durable-file run; repeated controlled comparisons and performance
claims remain B-stage work. Native query-account limits have the documented
compiler/caller/export/reference boundaries and do not bound total process RSS.
Stdout is a report view; actual local sink receipts govern durable delivery.

Recovery retains the predecessor's trusted Linux namespace and successful
local-fsync assumptions. Process-crash tests do not prove power-loss behavior
or arbitrary external callback effects. A02's project license decision, richer
optimization, experiments and full V-stage release gates remain open.
