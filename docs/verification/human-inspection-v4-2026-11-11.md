# Human inspection continuation: frontend and catalog

This pass follows the [scalar/native-table checkpoint](human-inspection-v3-2026-11-11.md).
A current-model reviewer inspected binding; a bounded Luna Max reviewer inspected
parser, admission and catalog boundaries. Root inspected normalization and the
reference SQL adapter, checked both reviewer packets, implemented the direct
changes and ran validation. No Astra run was added. The full implementation and
repository-wide human review remain active.

## Direct changes and preserved boundaries

Two local lookup maps in [`bind.cpp`](../../src/frontend/bind.cpp) become explicit
branches for seven scalar-comparison spellings and six Boolean truth tests.
Those maps existed only to look up fixed names; no iteration order was observed.
The same spellings select the same enums. Unsupported scalar operators still
reject before either child is bound. Boolean tests still bind/type-check their
argument before extracting the test name. Work charges, expression insertion,
locations and diagnostics retain their order.

The internal normalization `contract` helper now takes a literal pointer rather
than an implicitly constructed string. The source audit checks all 27 call sites
and confirms their second arguments are literals. Successful checks borrow those
static bytes; a failed check constructs the same owned Error code/message. The
checks themselves stay intact. Avoided map/string allocations intentionally
remove their possible allocation failures. No runtime owner, cache, registry,
instrumentation or dependency is added, and no speedup is claimed.

The audit proves exactly those three executable substitutions in two source
files, plus comments. Three headers change comments only. Maintained tests,
fixtures, CMake, public interfaces and all catches are unchanged. Existing
handlers preserve syntax/catalog/parameter/binding phases, source coordinates,
allocation rejection and internal-parser errors. Reference adapter rollback is
already supplied by local candidate owners before publication; it needs no
additional catch/rethrow layer.

## Human contracts and cost disclosures

The pass adds 149 individually authored seven-field contracts: 54 binding,
49 parser/admission/catalog, and 46 normalization/adapter cards. All 139 selected
production callable/type/inline-cluster blocks in the twelve assigned source
and header files have cards. Additional cards cover public declaration groups,
the Normalizer owner and individual adapter getters. There are now **872 scoped
contracts across 853 mapped blocks**. The [inspection index](../code_specs/README.md)
maps 664 maintained files, 152,321 lines and 16,819 blocks with current hashes.

Another 4,439 selected production blocks remain without individual semantic
cards: 877 in include, 3,505 in src and 57 in apps. This is an inventory rather
than a semantic coverage percentage. Structural partitions and retained comments
are not a certification of every repository branch. Full per-block review stays
open.

Seven reviewer comment edits and root's local comments clarify owned binding
results, SQL output positions, cast/decimal comparison rules, selected work
checkpoints, diagnostic exception scope and non-null source-column requirements.
Five documentation corrections across four guides remove stale statements about
binding, admission, lowering and EXISTS output wrapping. The SQL support table
is explicitly mixed-stage historical context, with the current task ledger
linked separately. No unsupported single checkpoint date is assigned to it.

The [normalization cost section](../sql_normalization.md#implementation-and-cost)
and [primitive cards](../code_specs/primitives.md) expose material costs:

- Parsing copies source and the full AST while holding the process-wide parser
  mutex. Limits are selected byte/depth boundaries, not total time or memory caps.
- Binding revalidates the entire catalog for each table occurrence through the
  public lookup helper, after initial catalog validation. Unqualified lookup
  eagerly builds candidate descriptions even on success. NATURAL matching,
  USING membership and scope copies retain their actual scan/copy costs.
- Normalization copies binding/catalog/source/parameters before its first work
  charge. Each `adapt_row` copies the query-wide constant slots, not just local
  projection cells. Exact decimal domain checks can format owning text.
- The independent `AdapterState` copies full physical, logical and support
  collections even for valid no-ops. Candidate validation and swaps make its
  transaction direct; it carries no native runtime update bound.
- Reference catalog constraints validate full data and build ordered projected
  key sets. Metadata validation and untrusted hints do not prove data constraints.

Those remaining costs are documented candidates, not redesigned in this pass.
Any later change must preserve diagnostic order, work-limit behavior, input
identity and borrowed lifetimes. Frontend, catalog, parser ownership and SQL
three-valued behavior use their actual local design guides; they are not
attributed to the dynamic-CQ paper's allocator or runtime theorem.

## Executed validation

| Configuration | Selected linked CTests | Elapsed |
| --- | ---: | ---: |
| Fresh GCC Debug | 6 passed | 0.43 s |
| Fresh ASan + UBSan with leak detection | 6 passed | 1.52 s |

The tests are `parser`, `binding`, `normalization`, `catalog`, `admission` and
`schemas`. They check owned results, Unicode/error locations, scope/typing,
specialization, projection supports and alias atomicity, catalog constraints,
grounded constants, bounded recognition, replay, migration and identities.
Final build/test receipts bind the same 1,101 inputs with no concurrent change.
The builds produce 18 linked native artifacts and 136 actual C++ objects.

A verification-only native bridge executes 41 SQL cases per profile: all seven
comparison spellings both ordinary and pg_catalog-qualified, all six truth tests
over TRUE/FALSE/NULL, local truth expressions, and three rejection-order cases.
Independent SQLite evaluation, with UNKNOWN expressed through its NULL truth
definition, checks 198 result rows per profile. The same bridge is separately
linked to the sealed predecessor libraries; its complete serialized binding,
normalization, work, diagnostic and result transcript matches the current one
byte for byte in both profiles. Four bridge executables and two bridge C++
objects are additional controls, not new registered tests or maintained files.

Four additional actual binding/normalization objects compile under strict
optimized GCC and Clang flags. Across linked builds and controls there are
22 linked artifacts and 142 actual C++ objects. These are actual measured
artifact counts; optimized compilation is not a linked Release test matrix.
Timings describe this run and establish no comparative performance result.

The specification checker validates current hashes, contiguous partitions and
28,912 local links. All 872 authored anchors resolve uniquely. The generator and
checker are unchanged from the sealed predecessor; its eight anchor fixtures
and ten negative checker controls remain applicable and preserved. All 314
same-profile test definitions/properties and CMake/install declarations remain
unchanged. No full 314-test run or complete repository review is claimed.

All 2,445 predecessor source paths have preserved before-images; previous frozen
source/build/evidence remains intact. The staged packets are under
`build/verification/inspection-v4-{binding,edges,root}-v1`. Acceptance is
`inspection-v4-acceptance-v1.json`, and the progress/source closure is
`inspection-v4-progress-v1.json`. Final raw test logs are
`inspection-v4-ctest-final-{debug,sanitizer}-v1.LastTest.log`.
The [handoff](../handoff.md) records remaining review and implementation scope.
