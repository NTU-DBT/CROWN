# V61 full-scope code review and receiving

The current maintained code review passes its source, usage-contract and targeted
correctness gates. The complete six-study report also passes portable replay and
independent raw/table receiving. B04, B06, X09 and X10 are received within the
finite scopes below. The full Refactor implementation goal remains active;
this document does not declare an R1/R2 release.

## Reviewed scope

The [inspection index](../code_specs/README.md) covers **830 code files, 188,584
lines and 20,846 regions**. All 17,707 nonblank regions have source-bound semantic
contracts; 3,139 blank regions retain structural descriptions. The 20,158 adopted
contracts provide purpose, inputs/outputs, invariants, ownership, failure, cost
and references. The canonical checker passes 146,843 local links, zero errors.
[Adoption](../../build/verification/independent-queries-v61-v1/final-contract-adoption-v1/receiving.json)
records the exact current registry and the 21 previously proposed unit cards
explicitly promoted after root's full source/card reads and actual execution.

Production scope is 373 include/src/apps paths: 365 byte-identical successors of
the completed [V60 review](component-evaluation-v60-2026-11-15.md), five changed
files and three new files. V61 entry verified all 4,782 inherited source pairs
and 32.4 GB of preserved evidence with no byte mismatch. Inherited arguments/tests
apply only to unchanged bytes; new code receives separate reads and checks.
Dependencies and immutable published baselines retain their separate pinned
source/qualification scope.

| Change | Human inspection and correctness argument |
| --- | --- |
| [Independent query directory](../independent_queries.md) | Root and independent Luna review. A separate finite account funds map/controller storage. Node allocation precedes nonthrowing owner transfer; directory identity plus monotonic ordinals prevents foreign/stale aliasing. Every Session retains its own runtime/account/progress/publication/recovery. Keeping a live borrow avoids lookup per update. |
| [Prepared SQL input program](../input_specialization.md) | Full root/author/independent reads of the public API, private instruction/range owner, freeze/replan and tests. Instructions derive only from admitted normalized metadata; argument views retain owning Data/basis. Every operation calls the unchanged scalar evaluator; tuple/scalar/IndexWork order remains matched. Physical/source identities remain unchanged; a distinct execution key names dispatch. |
| [C05 cache binding](../selection_binding.md) and [payload model](../selection_accounting.md) | Root implementation and independent review. Prepared execution key and both receiving limits enter a versioned optional suffix; interpreter bytes remain unchanged. Logical cache payload includes policy/usage/table headers and capacity bytes, with O(1) extra size reads; actual MemoryAccount retains allocator/peak scope. |
| [Experimental report tools](../experimental_report.md) | Root full source/diff reads, separate worker replay/arithmetic/corruption checks and actual figure inspection. Per-row resources/wall clocks reference the correct original records; historical source identities and units stay separate. Content-addressed relative gzip replay has no old-path fallback. |
| Scalar test driver | DATE/DECIMAL alternatives construct directly inside Cell, avoiding a GCC13 Release temporary-variant warning. Strict build and independent scalar-oracle controls pass; no native scalar behavior changed. |

The new directory adds no scheduler, shared query operator or update callback.
Preparation adds an optional immutable owner and dispatch branch for normalized
input; the main change-propagation/journal/output algorithms are unchanged. No
new retry, recovery or exception-handling framework was introduced.

## Findings repaired

The review found and repaired three integration issues in prepared execution:
indexed grant validation occurred after analysis could consume an over-cap
grant; non-SQL programs could acquire an unused prepared label/owner; and C05
could return an artifact with another execution policy or preparation limits.
The cache regression was first compiled against pinned pre-fix archives and
failed with the exact cache-alias message, then passed against the fixed build.
[Reproducer and source freeze](../../build/verification/v61-input-execution-cache-v1/DESIGN.md)
retain that distinction.

Test/client receiving corrections cover the empty-head Boolean Row{} witness,
complete recovery header, public error accessor, canonical constant-empty tree,
TupleValuesView serialization, catalog envelope/bool wire spelling and measured
clock/capture validation. Report receiving corrected RSS/stdout and process-wall
links and rejects self-consistent metadata that contradicts actual raw timing or
candidate counts. Failed attempts remain evidence; none is counted as a pass.

## Actual validation

| Cohort | Result and exact scope |
| --- | --- |
| Current Release and ASan/UBSan | Each passes 9/9: three new directory/input/cache tests plus six ordinary/independent C05 source, binding, cache and resource controls. |
| Current independent SQLite receiving | Each profile passes 28 mode/backend gates and 244 prefixes, signed deltas/snapshots/native-work identity, constant false, request/catalog/capture/clock negatives and no-overwrite/CPU guards. |
| Earlier V61 broader receiving | Each profile passes8/8 program/replan/constant/scalar/admission/normalization/physical controls. Relocated public CROWN::queries consumers pass four unseen SQL streams, distinct accounts/progress and strict installed-header/link isolation. These receipts precede only the later getter/C05 changes; they are not relabeled as a whole-current suite. |
| Historical source-package replay | V48/V59/V60 clean source archives rebuild GNU C++23 Release with BUILD_TESTING=OFF; 434 actual compiled-source joins. V48 checks 216 prefixes plus a wrong-oracle denial; V59 checks 90 all-envelope preflights; V60 checks 6 search, 32 operational and 16 delivery gates. No old timings are replaced by these new correctness runs. |
| Current clean source archive | Exact 2,766-member archive joins all 139 measured C++ sources and project compiler dependencies. A fresh Release/OFF rebuild of all public libraries passes 28 mode/backend gates, 244 independent SQLite prefixes and four unseen queries through a relocated installed SDK. These are correctness runs, with zero new methodology measurements. |
| Report receiving | All six complete studies produce 96,705 per-repetition metric rows, 2,179 decisions, 10,355 gzip members and 188 PNG/PDF files. Independent receiving recomputes every metric and 32,235 summary groups from 4,898 raw metric members, checking source/resource pointers. Standalone replay prohibits old repository-prefix reads and regenerates byte-identical tables/context. Earlier genuine subset/corruption/missing/grant/reuse controls remain separate evidence. |

Current native receipts are in
[Release](../../build/verification/v61-input-execution-cache-v1/native-release-v1/commands.json)
and [sanitizer](../../build/verification/v61-input-execution-cache-v1/native-sanitizer-v1/commands.json).
No full-suite pass is inferred from selected tests. Unchanged engine algorithms
retain the explicitly inherited complete V58 Debug/sanitizer evidence.

One independent [Astra Max review](../../build/verification/v61-astra-final-correctness-v1/README.md)
read every changed/new production body and the
three new unit tests, then followed receiving, restore, replan and cache callers.
It found no confirmed correctness defect after the repairs above. Two useful
coverage extensions remain: vary each preparation limit independently and assert
returned limits on cache hits; destroy original/intermediate program owners in
the replan lifetime test. These are test gaps, with the ownership and key-frame
arguments reviewed directly; they are not failed checks or a general proof.

## Controlled component result

The [actual study](../../build/verification/v61-input-specialization-study-v1/experiment.json)
contains 21 case/scale combinations, two backends and two input modes: 84 gates,
4,620 independent SQLite prefixes, 252 measured process invocations and 42 paired
contrasts. Each measured process contains one excluded fresh-owner warmup and
one measured owner. All children use CPU 0; other owned work was held. The same
SQL/tree/storage/trace/output/native-work obligations pass before timing; end
build/harness/input/launcher closure is unchanged and external failures are empty.

The protocol drains signed deltas plus a full snapshot after every input, with
initial snapshot work in initialization. Setup, receiving base copy/preparation,
owner initialization, loop/apply/output/release and whole-process RSS retain
different scopes. There is no per-query JIT or global prepared-program cache.
Each normalized row still copies the existing all-expression value vector.

Finite paired loop ratios range roughly 0.937–1.034 (threaded/interpreted). These
are descriptive ratios across distinct cases, not a pooled speedup or confidence
interval; even constant-false controls vary. The data does not establish broad
benefit. The interpreter stays the default. The compiled byte image is frozen
[separately](../../build/verification/v61-controlled-build-archive-v1/receiving-v1.json):
704 workspace inputs/145,488,579 bytes, three binaries, 18 archives and 139 C++
units. System pins and unarchived dynamic-library limits remain explicit.

## Continuation

The [complete report](../../build/verification/v61-full-experimental-report-v1/report/report.md)
joins all six datasets to qualified source archives, exact raw records and fresh
methodology receipts. The current-source qualification includes its complete
relocated SDK and outside consumer; original build/staging prefixes remain
reusable. Historical measurements remain unchanged. The clean source replays
ran on this machine; no second physical-machine execution is claimed.

The ledger has 67 verified, one in-progress and ten not-started cards. Broader
Refactor and release qualification remain open. Approximation and
parallel/distributed execution remain deferred; the multi-query interface
maintains independent serial sessions. Licensing checks remain deferred while
rights and notices are preserved.
