# AntiGravity / coding-agent handoff

Updated 11 November 2026. Full [Refactor.md](../Refactor.md) implementation remains
active. Work is uncommitted at baseline `e369a623517723b3be3ea3e9806779f3c591e7f9`.
The [ledger](task_ledger.md) is **54 verified, 1 in progress (A02),
23 not started; 78 total**. No release is claimed.

## Verified human inspection continuation, version 4

The frontend/catalog review adds 149 individually authored contracts: 54 from a
current-model binding reviewer, 49 from a bounded Luna Max parser/admission/
catalog reviewer and 46 from root's normalization/adapter review. No Astra run
was added. All 139 selected production blocks across the twelve assigned files
have cards. The current map has 872 scoped contracts in 853 blocks, across
664 files, 152,321 lines and 16,819 structural blocks. Another 4,439 selected
production blocks lack individual cards; full human review remains open.

Start with the [verification record](verification/human-inspection-v4-2026-11-11.md),
[inspection index](code_specs/README.md) and
[normalization cost contract](sql_normalization.md#implementation-and-cost).
Staged packets are `build/verification/inspection-v4-{binding,edges,root}-v1`.
Root preserved all 2,445 predecessor source paths before editing. All previous
frozen source/build/evidence stays sealed, including v3 libraries read by the
separate baseline corpus executables.

Two fixed comparison/Boolean-test maps become direct enum branch chains. The
normalization contract helper accepts literal diagnostic pointers, constructing
owned strings only on failure; all 27 call sites are statically checked. The
source audit proves these three substitutions in two cpp files plus comments,
with three comment-only headers. No check, catch, maintained test, fixture,
public interface or CMake declaration changes. Seven staged source comments,
local owner/work/copy comments and five corrections across four guides clarify
actual behavior. SQL support notes are labeled mixed-stage historical context;
current task status and admission/lowering/runtime boundaries stay distinct.

The cards disclose repeated whole-catalog validation per FROM, eager lookup
candidate descriptions, NATURAL/USING scans and scope copies, parser mutex/AST
costs, query-wide constant scratch per adapt_row, decimal text formatting and
full-state copy-commit even for no-ops. Those larger candidates remain unchanged
pending their own diagnostic/work/lifetime analysis; frontend/reference costs
are not attributed to native CROWN update or paper bounds.

Fresh Debug and ASan/UBSan/leak profiles each pass six selected CTests in 0.43 s
and 1.52 s. Each profile's additional 41-query corpus checks 198 result rows
against independent SQLite/truth definitions and matches the predecessor's full
serialized binding, normalization, work, diagnostic and result transcript byte
for byte. There are 22 linked artifacts and 142 actual C++ objects, including
four bridge executables, two bridge objects and four strict optimized GCC/Clang
compile controls. No linked Release matrix, full 314-test run or speedup claim.
Final native receipts are `inspection-v4-build-final-*-v1` and
`inspection-v4-ctest-final-*-v1`, with 1,101 stable inputs. The current checker
passes 28,912 local links, complete partitions and all 872 unique anchors.
The unchanged generator/checker retain the predecessor's eight anchor fixtures
and ten negative controls. All 314 same-profile registrations remain unchanged.

Acceptance is `build/verification/inspection-v4-acceptance-v1.json`; progress and
source closure are `build/verification/inspection-v4-progress-v1.json` and
`build/inspection-v4-source-v1`. Earlier failed exploratory controls remain
separate from final gates. Ledger remains 54 verified, 1 in progress (A02),
23 not started; 78 total. Full Refactor.md implementation remains active.

Next: continue individual block/comment review in planner, session/delta,
remaining native/header and IO boundaries. Use exact source hashes and actual
paper/design references; preserve diagnostic/work ordering before optimizing.
W04 remains the next implementation card, followed separately by W05/W06.
Licensing, experiments and release gates remain open.

## Verified human inspection continuation, version 3

The broader user-requested human review remains active. Root revalidated all
2,444 predecessor source paths and preserved before-images under
`build/verification/inspection-v3-preimages-v1` before editing. Two read-only
reviewers supplied 126 scalar/row/layout/projection and 118 indexed-table/journal
cards. Root authored 101 ordered-reference cards and integrated 61 Luna Max
dispatch/protocol cards. No additional Astra run was used. The current index has
723 scoped authored contracts across 709 mapped blocks, covering 664 files,
152,293 lines and 16,816 structural blocks. Another 4,578 selected production
callable/type/inline-cluster blocks still lack individual cards. Structural
coverage is not universal semantic certification.

Start with the [verification record](verification/human-inspection-v3-2026-11-11.md),
[inspection index](code_specs/README.md), [primitive cards](code_specs/primitives.md)
and [native journal protocol](storage_journal.md#accounted-native-interfaces).
Staged reviews and controls are under
`build/verification/inspection-v3-{inventory,scalars,indexed,status-proposals,dispatch,root}-v1`.
Root applied nine reviewer comment/docs corrections and local ownership, grant,
pin preparation and cost clarifications. Seventeen status paragraphs across
12 guides now distinguish implemented native accounting, dated checkpoints and
compiler/input/export/RSS boundaries.

TupleValuesView equality caches both arities and rejects different widths before
cell access; equal-width values retain the same scalar three-way comparisons.
Row/RowView equality delegates to that central operation. Ordering is unchanged.
The source-edit audit proves one intended native executable change, eight native
comment-only files and one test diagnostic-string edit. No assertion, fixture,
registration, new allocation/state/framework or instrumentation is introduced.
Required native cleanup and preparation/undo catches remain. Repeated projection
checks and public/native validation remain candidates requiring preserved error
ordering and diagnostics before removal.

Final fresh GCC Debug and ASan/UBSan with leak detection each pass five selected
linked tests: scalars, layouts, memory_account_contract, public_tuple_memory and
s04_storage_table. Elapsed times are 0.44 s and 1.63 s. Each configuration reports
508 storage/dispatch/plan allocation positions plus four public-tuple faults,
44 indexed work and nine component boundaries, five plan work boundaries and
500 independent StorageTable operations. There are 30 actual linked artifacts
and 222 actual C++ objects: 220 from the two testing-runtime builds plus two
strict optimized GCC/Clang tuple_values.cpp compilation controls. No linked
Release matrix, full 314-test run or measured speedup is claimed.

Final native build receipts are `inspection-v3-build-final-{debug,sanitizer}-v3`;
final CTest receipts/raw logs are `inspection-v3-ctest-final-{debug,sanitizer}-v2`.
All bind the same 1,101 current code inputs without concurrent changes. The
checker passes 28,083 local links and complete/current structural maps; all
723 anchors resolve uniquely, with eight anchor fixtures and ten negative
checker controls. All 314 same-profile test commands/properties and CMake/install
declarations are unchanged. Earlier preparatory receipts remain exploratory.

Acceptance is `build/verification/inspection-v3-acceptance-v1.json`; progress and
source closure are `build/verification/inspection-v3-progress-v1.json` and
`build/inspection-v3-source-v1`. Prior source/build/evidence trees remain sealed,
including all 56 inspection-v2 linked artifacts. Ledger remains 54 verified,
1 in progress (A02), 23 not started; 78 total. The full Refactor.md goal is active.

Next priority: continue the remaining individually authored block/comment review,
including frontend/planner, session/delta boundaries and unlisted native/header
forwarders. Use actual current hashes and distinct paper versus local-engineering
references; keep main code direct and record real costs before optimizing. W04
is the next implementation card, followed separately by W05/W06. Licensing,
experiments and release work remain open.

## Verified human inspection continuation, version 2


The broader user-requested review continues after this scoped checkpoint.
All2,443 W03 source paths were revalidated/preserved under
`build/verification/inspection-v2-preimages-v1` before edits. Two reviewers using
the current model, without another Astra run, supplied102 Boolean and68 native
cards; root added15 physical/grant cards. There are317 authored seven-field
contracts across305 mapped blocks. The current source map covers664 files,
152,263 lines and16,815 blocks. Full repository per-block semantic/comment review
remains open. Start with the [verification record](verification/human-inspection-v2-2026-11-11.md),
[inspection index](code_specs/README.md), [cards](code_specs/primitives.md) and
[error dispositions](code_specs/error_handling.md).

Root integrated14 staged comment/docs edits after exact source/hash checks and
added direct physical ownership/account/history comments. Four redundant
mechanisms are removed: Boolean/physical category overflow guards after
cumulative charge, an always-nonnull address-of-entry tuple guard, and a physical
preparation rollback/rethrow catch already covered by its unique Data owner
before public error presentation. Required resumed route/stage cleanup, native
allocation cleanup and typed public diagnostic boundaries remain. There is no
new runtime owner/allocation/registry/framework/instrumentation or speedup claim.

New cards disclose O(matches) reverse-bucket scratch, full Boolean flag copies,
separately funded inverses, account-ledger/arena-high-water and diagnostic costs.
Public/native double tuple validation remains an optimization candidate because
public field-index diagnostics and invalid-layout ordering differ. Corrected
P1v2 support/enumeration references are distinct from local native engineering
contracts. The authored source-anchor locator resolves unique actual source
positions;317 real anchors and eight class-forward/inline/format/negative fixtures
pass. The first documentation map was correctly rejected for unmatched/duplicate
anchors; final maps pass, with two old anchors qualified to their definitions.

Final native gates: fresh GCC Debug18 checks pass13.99s; ASan/UBSan with leak
detection18 checks pass46.29s. Both cover1,011 reported update allocation failure
points and41 basic result-cursor failure points, plus overlay/witness sweeps.
Indexed/ordered models, physical projection collisions, prefix/prepared epochs,
reader/owner lifetimes and one storage grant are included. Four additional actual
support.cpp/physical.cpp objects compile under strict optimized GCC/Clang; these
are compilation controls, not linked Release tests. Final native build/test
inputs are stable. The source-edit audit proves exactly four intended removals
plus comments in nine native files; seven are comment-only. The offline generator
is the tenth changed maintained code input. No new maintained source/test file.

All314 test definitions/properties match the corresponding W03 Debug/sanitizer
profiles; CMake/install declarations are unchanged. The checker validates25,408
local links/current hashes/full partitions and ten negative checker controls.
No full314test run or universal semantic certification is claimed.

Acceptance: `build/verification/inspection-v2-acceptance-v1.json` binds13
requirements,1,101 code inputs,56 linked native artifacts and250 actual C++ objects
(246 from the linked builds plus four optimized controls). Raw test logs are
`inspection-v2-ctest-final-{debug,sanitizer}-v1.LastTest.log`; final build receipts
are `inspection-v2-build-final-{debug,sanitizer}-v2`.
Staged reviews and root controls are in
`build/verification/inspection-v2-{boolean,native,root}-v1`. Root source-edit and
anchor controls are separately executable. Preparatory dependency receipts that
captured later support edits and the sanitizer v1 build that saw an offline-tool
edit are exploratory, not final gates. Existing W03/W02/W01/C06 artifacts stay
sealed; all80 W03 native artifacts are revalidated unchanged.

Progress/source closure: `build/verification/inspection-v2-progress-v1.json`,
frozen source `build/inspection-v2-source-v1`. All recorded jobs are terminal at
that seal. Ledger remains54 verified/1A02 in progress/23not started,78 total;
full Refactor.md goal stays active. Do not mark it complete at a review checkpoint.

Next priority: continue the user's human per-block/comment review in remaining
native wrappers/table journals, scalar parsing/hashing, frontend/planner and
session/delta boundaries, using exact current source hashes and distinct paper
versus local-engineering claims. Existing review packets list their unreviewed
forwarders/statistics/initialization/probe gaps. Keep main code direct and avoid
new runtime checks/frameworks for documentation. W04 is the next implementation
card; W05/W06 stay separate. License/EXPLAIN/experiment/release work remains open.

## Verified W03 checkpoint



W03 is verified at the direct-CQ logical replacement boundary. Start with the
[projected factor/cursor specification](weighted_enumeration.md),
[verification record](verification/w03-projected-bags-2026-11-11.md),
[inspection index](code_specs/README.md) and [usage cards](code_specs/primitives.md).
The entire Refactor.md goal remains active; do not mark it complete at this card.

Root owns factor math, implementation and final validation. One bounded Luna Max
agent supplied only the independent Python projected oracle. One user-authorized
Astra Max read-only verifier found no W03 correctness blocker; root resolved its
three small findings: redundant metric overflow guards, all-frame/head-width cost
wording and a central ordering/reader/terminal cursor usage contract. That agent
ran no builds/tests and did not certify the complete repository.

Local visible factors exclude children explicitly enumerated inside C*, sum
hidden native/generalized assignments, and share existing native E tables and
compact counter inverses with full messages. Each row caches a scalar local
contribution; positive inside changes reuse it. One flat immutable outside-slot
list avoids enumerated-sibling scans without per-row arrays. Maintenance and
committed traversal live in separate weighted.cpp/weighted_cursor.cpp units,
sharing only a small private declaration header. No new policy/exception framework,
result history, hidden witness materialization or arbitrary-semiring registry.

The compressed cursor emits owning core Tuple/multiplicity records; output
order is unspecified. One caller may interleave readers. All writers, including
no-ops, are excluded until terminal next/cancel/destruction/failure closes every
reader. One original grant and cumulative budget span all next calls. Closed
metadata stays inspectable; owning rows survive the cursor/runtime. FactorChange
records are local inspection changes, not joined-answer deltas.

Final stable-source gates: eight selected tests each pass GCC Debug 9.86s,
GCC Release 4.25s, Clang18 Release 4.36s and ASan/UBSan with leaks 40.67s. Every
configuration checks2,910 projected and1,516 subtree oracle states,1,108 update
allocation cuts and26 cursor cuts on both backends. Failed updates and retries
also compare factors/bag outputs. Typed/repeated/empty outputs,96-node hidden/
visible chains, generalized sums, precision/overflow, reader/owner lifetimes,
exact/one-under work/heap/native thresholds and4,096 compressed outputs are
covered. Existing set-cursor and annotation admission checks pass. Test elapsed
times are validation context, not comparative performance measurements.

Moved installed strict Clang consumer links only CROWN::runtime, includes the
weighted header independently, and checks the hand60 count, repeated head,
precision, query ownership, exclusions/lifetimes/terminal metadata and both SQL
constructor rejections. All15 installed CROWN archives match final Clang.
The testing runtime compiles. All311 predecessor registrations/properties and
install declarations are retained;314 tests registered. This is not a full-suite run.

The structural source map covers664 files/152,240 lines/16,810 blocks, with132
scoped seven-field authored contracts. Every callable block in weighted.cpp and
weighted_cursor.cpp has a usage card. The checker validates24,245 local links,
current hashes and contiguous/full inventory; ten negative controls pass. The
user-requested semantic specification/comment review of every repository block
remains open; structural coverage is not that certification. Documentation adds
no runtime checks or instrumentation. Existing Boolean present-array copies and
account lifetime-ledger scans remain explicit measured-cost candidates.

Acceptance: `build/verification/w03-acceptance-v1.json` and its checked driver
bind23 requirements,1,101 code inputs,80 actual native artifacts and504 actual
C++ objects. Final receipt families: `w03-build-final-*-v1`,
`w03-ctest-final-*-v1` and separately archived `.LastTest.log` files. Other evidence:
`w03-registration-v1.json`, `w03-astra-inspection-v1.json`,
`w03-specs-generate-v4`, `w03-specs-check-v2`,
`w03-specs-negative-controls-v1`, and `w03-public-surface-v1`.
Progress/source closure is `build/verification/w03-progress-v1.json`; the frozen
source is `build/w03-source-v1`. All2,425 W02 predecessor paths have preserved
before-images under `build/verification/w03-preimages-v1`; all83 sealed W02
native artifacts were revalidated unchanged. Preserve W03/W02/W01/C06 evidence.

No job remains live after the progress seal. Receipt driver:
`build/verification/w03-record-driver-v1.py`; it refuses overwrites and records
input hashes/changes. One early Release fixture build failed on GCC's nested
variant move warning; direct VariableId construction fixes it without disabling
warnings. Exploratory receipts with mid-build source changes are not final gates.
Never build while CTest is live in that directory; archive LastTest.log before
another CTest/enumeration and never test after a failed build. Default sandbox
bwrap fails; use require_escalated for local commands. Ninja is unavailable;
use Unix Makefiles. Clang18 remains under build/toolchains/clang18/root/usr/lib/llvm-18/bin.

Next: W04 COUNT/SUM/AVG needs explicit binder/group sufficient-state semantics and
mature SQL-oracle agreement, followed separately by W05 bag/NULL admission and
W06 aggregate transaction/recovery. Continue human-readable primitive contracts
and keep main code direct. A02 distribution license remains unresolved; do not
repeat the question while independent authorized work is available. Larger review
cleanups/EXPLAIN versioning, experiments and V01/V02/release reviews remain open.
Below is frozen checkpoint history; older next-step/status prose is historical.

## Historical W02 and human inspection checkpoint

W02 is verified. The full Refactor.md implementation goal remains active; never
mark it complete at this card checkpoint. Work stays uncommitted at baseline
`e369a623517723b3be3ea3e9806779f3c591e7f9`. Revalidated/preserved all 1,750 W01
predecessor paths under `build/verification/w02-preimages-v1`.

Start with [the inspection index](code_specs/README.md),
[reviewed primitives](code_specs/primitives.md),
[error dispositions](code_specs/error_handling.md),
[weighted contract](weighted_messages.md) and
[verification record](verification/w02-human-specs-2026-11-11.md).
The source map covers 656 maintained code/build/test files, 150,698 lines and 16,646
blocks, with 51 scoped seven-field semantic contracts. Structural coverage is
explicitly distinguished from individually authored semantic specifications;
every retained comment/branch is not blanket-certified. Offline generator/checker
validates hashes, complete inventory/line partitions and 23,437 local links, with
ten negative controls including empty semantic fields/duplicate anchors.

The user's explicit request started one Astra Max documentation/structure agent,
`human_specs_structure`. Its frozen staged overlay/evidence is under
`build/verification/human-spec-revision-v1`; root integrated only docs/tools and
applied 23 exact comment edits across 18 files. All17 changed C++ units produce
byte-identical actual g++ preprocessed output; CMake noncomment code is identical.
The two root tool adjustments clarify that the enum mapper is applied and check
required contract fields/unique anchors. `Operation::note` now calls the shared
noexcept `component_diagnostic` value mapper instead of throwing just to catch
and copy a diagnostic. Required rollback/durable boundaries remain.

Root owns W02 design/code/validation. One bounded Luna Max inventory covered
native storage/journals/grants; another implemented the Python assignment oracle,
with root review and zero-row correction. `runtime/weighted.hpp`/weighted.cpp
maintain direct-CQ native logical tuple replacements, full subtree sums/products,
nested generalized products then separator sums, causal numeric FIFO events,
compact scalar/one-slot undo and original-account state/captures. Default numeric
changes copy no full diagnostic record arrays; change/event histories are opt-in.
Weighted identity/profile is separate; normalized SQL is rejected. Projected
bags, SUM/AVG and weighted recovery remain W03–W06. No Boolean numeric bound or
measured speedup is claimed.

Final gates, all terminal exit0:

| Configuration | Passed selected tests | Seconds |
| --- | ---: | ---: |
| GCC Debug | 8 | 6.34 |
| GCC Release | 6 | 1.50 |
| Clang Release | 6 | 1.55 |
| ASan/UBSan/leaks | 6 | 26.52 |

Each checks 1,516 independent unbounded-integer update states and 894 actual
allocation failure cuts across creation/deletion, both backends and capture
modes. C++ complete-assignment state is compared after each logical update.
Controls include hidden/generalized sums, numeric-only changes, candidate birth/
reclamation, typed disconnected three-child empty keys, depth 256, stale/type/
sequence/overflow rejection, exact/one-under work/heap, 64-stage same native grant
plus private capture at its exact/one-under structural threshold, nonallocating
commit/rollback, moves, owning retention and bounded churn. Set admission and
selection regressions pass; Debug also runs support journals and epoch indices.
The testing runtime variant compiles separately.

A strict moved-installed Clang consumer passes without source/test headers or
reference linkage: new-owner compiler import, bindings, >2^53 precision, snapshots,
moves and SQL rejection through both constructors. All15 installed native
archives match final Clang archives byte for byte. All308 prior registrations
and installation declarations are preserved;311 tests registered. Full311 suite
and R1 release are not claimed.

`w02-acceptance-v1.json`/`.py` audit 18 requirements, 1,093 matching code inputs,
83 actual archives/ELFs, 511 actual C++ objects, scoped receipts/raw logs,
registration and predecessor preimages. Final source continuation is
`w02-progress-v1.json`; source-only snapshot is `build/w02-source-v1`.
Receipt driver: `w02-record-driver-v1.py`. Initial syntax/fixture/command failures
are separately classified in `w02-developer-negatives-v1.json`; no failed build
was followed by stale-binary testing.

All jobs are closed; preserve `w02-development-make`, `w02-human-release`,
`w02-human-clang-release`, `w02-human-sanitizer`, raw LastTest archives, installed
consumer and frozen review evidence. Use new build/source/evidence directories
for later work; do not mutate historical W01/C06 seals.

Next: W03 projected bag enumeration (W02/D02 dependencies verified). Establish
local visible factors/hidden summation and tuple/multiplicity cursor semantics
before code: explicitly enumerated children must not also enter the parent
factor. Keep numeric support/payload and output-size representation distinct.
A02 licensing remains unresolved; do not infer it or ask again while independent
work is available. V01/V02 full semantic/documentation/release reviews remain
open; the block map is not their completion. Optional Boolean fan-out-copy,
physical ledger-scan and frozen EXPLAIN-v2 cleanup candidates remain documented.

## Completed W01 acceptance and requested review

W01 is verified. The full goal stays active; W02 exact weighted subtree message
maintenance is next. Its W01/R04 dependencies are verified. C04/B01 still need
A02 disposition; do not infer a license or ask again while independent work is
available. Do not mark the whole goal complete at this checkpoint.

The user requested direct code and multiple powerful reviewers with paper/design
references a human can follow. Three Astra Max scoped reviews are complete;
302 maintained implementation/header paths are inventoried with explicit depth:
65 algorithm files, 147 native files, 89 boundary files and one version header
reviewed by root. Root owns implementation/fixes and validation. Reviewers ran
no builds/tests and changed no project sources. One earlier bounded Luna Max
inventory covered the W01 scalar/admission extension points. Start with
[code_review.md](code_review.md), then [annotations.md](annotations.md).

W01 adds exact support/payload types, distinct membership/numeric changes,
checked uint64/int64 and fixed decimal policies, final-value replacement and
closed backend admission. No catch scaffolding was added to arithmetic. SUM
zero does not erase a live group. The current set runtime still rejects weighted
policy names; weighted SQL/runtime remains W02–W06.

Root fixed unused rejected-verifier retention, legacy recovery ownership after
tail repair, missing no-op C01/O07 tickets, typed native-work partial capture,
strict external JSON, incomplete clean-source copies and stale-link provenance.
Legacy torn-tail/allocation and indexed-capture rejection were reproduced before
fixes. The guide records remaining optional cleanup and frozen EXPLAIN v2 status
labels; those labels need a separate capability-report version.

Final gates:

| Configuration/scope | Passed checks | Seconds |
| --- | ---: | ---: |
| GCC Debug affected/regression | 27 | 271.23 |
| Fresh source-only GCC Release affected/regression | 33 | 327.44 |
| Clang Release review controls | 14 | 329.82 |
| ASan/UBSan with leak checking | 9 | 665.61 |
| Fresh Release moved installed workflows | 4 | 58.42 |

A separate strict Clang consumer passes using only moved installed annotation
headers/library. Each arithmetic oracle checks 15,588 Python integer/fraction
cases. Legacy admission sweeps 1,879 actual allocation cuts on both backends,
with both torn tails, exact/one-under receiving heap, lock release/retry and the
next input/output. Existing selected recovery still passes 1,105 cuts. Residual
semantic/persistent-OOM checks pass Debug and both Release compilers; sanitizer
scope includes semantics and excludes the persistent residual sweep/process crashes.
No full 308-test execution, isolated speedup or release is claimed.

`build/verification/w01-review-acceptance-v1.json` binds 15 requirements,
1,082 current code inputs, 143 actual top-level native archives/executables,
696 C++ compilation records and ten final receipts/raw logs. All 302 predecessor
commands/properties and installation declarations are preserved; 308 registered.
All 1,739 C06 predecessor preimages are intact under `w01-preimages-v1`.
`build/w01-review-source-v1` is an immutable 1,750-path source-only copy; its docs
describe the pre-acceptance state. Final current docs/source continuation is
`build/verification/w01-review-progress-v3.json`.

All build/test/audit jobs are terminal and closed. Preserve the four build trees
`build/w01-development`, `build/w01-review-clang-release`,
`build/w01-review-sanitizer` and `build/w01-review-gcc-release`, their receipts,
raw LastTest logs and public-control artifacts. Do not rebuild sealed trees.
Never build while CTest is live in that same directory. Failed developer packets
remain separate: initial Value-name collision, fixture-only local-delivery
discard and workflow command mistakes, actual legacy-tail/indexed-work reproducers,
and legitimate CMake compiler-cache type handling. Do not count them as success.

Receipt driver: `build/verification/w01-record-driver-v1.py`; reproducible audit:
`build/verification/w01-review-acceptance-v1.py`. Review detail/inventories and
exact corrected P1/P2 PDFs are under the three `review-*-v1` directories. The
root bundled PDF is older than P1 v2; use the exact primary links/hashes in the
guide. Preserve historical seals and .git; use new source/build/evidence paths
for W02. Sections below are chronological prior checkpoints: their old “current”
and “next” statements apply to their recorded phase.

## Completed C06 checkpoint before W01

C06 is now verified as a component. The full Refactor.md goal remains active;
do not mark the whole goal complete at this checkpoint. The ledger is51 verified,
one in progress (A02),26 not started,78 total. W01 annotation capabilities is the
next independent path: its A03/R03/D03 dependencies are verified. C04/B01 still
require A02 disposition; do not infer a license or ask again while other work
remains available.

Final C06 gates:28 selected GCC Debug tests pass190.37s; all20 C06 tests pass on
fresh source-only GCC13 Release78.70s and linked Clang18 Release84.45s. Eleven
ASan/UBSan/leak controls pass115.22s. Both Release packets include the moved SDK
with external compilation, different physical trees, retirement and fresh-process
recovery on both backends. All302 registered tests were not executed together.

`build/verification/c06-transition-acceptance-v1.json` checks13 concrete C06
requirements, all1732 predecessor preimages, exact1739-path source copies,1073
matching current code/CMake/test/example/tool/schema inputs,142 actual archives/
ELFs/public-example objects,11 final receipts and raw test logs. Actual runtime
symbol audits preserve the optional C05 dependency boundary. All295 predecessor
CMake definitions/install targets and test properties remain unchanged after
excluding only the new blocks/example install. No R0/R1 release, measured speedup
or whole-process compiler DTO memory guarantee is claimed.

Final source/continuation map is `c06-transition-progress-v4.json`. All build/test/
audit jobs have terminal exit0 and no jobs remain active. Preserve these build
trees and receipts. Exact negative source overlays in
`c06-transition-failure-inputs-v1` reproduce the SQL EXISTS test assertion,
recovery post-repair allocation, declared sink-index comparison and wrong SDK
scalar-enum failures; their raw receipts/logs are retained. Do not count failed
packets as final success. Root implemented/reviewed everything; one Luna Max
read-only C05 inventory completed. No Astra use in this continuation.

## C06 transition implementation details

The previous goal turn was progress: native installation/recovery reached the
verified development checkpoint below. Root continued implementation/review with
one bounded, read-only Luna Max inventory of C05 public timing/options APIs.
No Astra review was requested in this continuation. Keep implementation direct:
the optional bridge and compiler boundary add no catch scaffolding.

Implemented after preserving all1732 predecessor paths in
`build/verification/c06-transition-preimages-v1`:

- Optional measured `selection::select_for_reoptimization` and
  `selection::begin_reoptimization`. Ordinary C05 selection still reads no extra
  clocks by default. Complete wall preparation plus freshness validation enters
  native payback; stale owner/epoch/reset/configuration/private and unmeasured
  selections are rejected before native preparation.
- Explicit `CompilerPlanArtifact::prepare(account, CompiledProgram)` exports and
  canonically reconstructs a selected program outside mutation. Export/lowering/
  serialization/teardown time is included. CQ/SQL/backend cases match independent
  canonical bytes and complete compiler replay.
- Switch persistence cuts now snapshot at1, catch up two records and select at
  delivered B=3:176 I/O positions,176 process crashes and60 allocation cuts across
  both backends. Promotion at delivered B=3 passes140 I/O/140 crash/56 allocation
  cuts and retains the root lock after ambiguous selection.
- Receiving recovery passes all1105 actual allocation cuts and exact/one-under
  heap limits with both WAL and sink tails incomplete. This found a real final
  generation-holder allocation after repair. The holder is now allocated first,
  and exact runtime binding is checked before replay. Every failed admission
  leaves both tails unchanged, releases locks and permits retry.
- Churn passes64 switches/128 inputs across both backends/modes, varied data,
  forecasts/configuration/pause,32MiB original heap, two-generation history and
  32-epoch sink budgets, exact reference delivery and final recovery after old
  plan deletion. Native resident requests stay steady. The earlier observed
  1408-byte increase was the declared sink index doubling16→32 entries; subtract
  only actual reported sink vector requests for the native-state comparison,
  while retaining them in total current/peak and heap limits.
- `examples/reoptimization` is installed and compiles under production/testing
  definitions. The moved SDK test compiles an external consumer without source,
  test or reference dependencies, changes a physical tree and resumes SQL in a
  fresh process after rotation/retirement on both backends.

`c06-transition-ctest-v6.json`: all28 selected Debug tests pass190.37s. This includes
all20 C06 checks and eight C05/legacy regressions. The earlier SDK-only packet
passed11.90s.302 tests register; all295 predecessor properties are preserved.
The final compiler/sanitizer gates are recorded in the acceptance section above.
Intermediate progress-v2/v3 live-job lists are historical; their jobs are closed.

Fresh builds use exact1739-path `c06-transition-source-v2.json`; generated Python
cache files were excluded. Source v1 preserves the SDK example's wrong scalar
enum; source v2 changes that one file to the public `ScalarType::string`. The v1
configure trees never built and must not be mistaken for execution evidence.
The production recovery fix and all other engine/test sources match both copies.
Other failed test inputs and logs remain preserved. C06 component acceptance is
verified; the entire78-card goal remains unproven and active.

## Previous C06 native installation checkpoint

The root model implemented actual `publish_reoptimization`, managed rotation,
journal promotion and same-lock descriptor-aware recovery. The old runtime stays
owned until descriptor/checkpoint/fresh target WAL are synced and the root selects
the new generation. Installation then uses nonthrowing moves/cleanup. The small
selection guard handles ambiguous selection and root-lock retention; new main
paths have no catch scaffolding, following the user's clean-code preference.

`LockedGenerationRecovery` holds the actual root lock and original receiving
account across explicit external `CompilerPlanArtifact::replay`, then is consumed
by native admission. Exact target checkpoint/WAL binding and immutable sink-origin
header/schema/source/policy plus prefix validation precede repair. Ordinary v3
caller-plan recovery remains rejected. Legacy roots also work through the new
handoff. `promote_journal` preserves unmanaged files and sink identity while
selecting a new managed floor. Descriptor v2 retains the actual switch epoch
through rotations and late sink attachment; v1 golden bytes remain unchanged.

Compiler-artifact and publication-preparation time enter payback. Current workload
configuration is applied at installation and counters reset at B. Final cleanup
timing/current memory include old runtime and checkpoint/image scratch release.
Both old/new native states and publication allocations use the original account;
the external compiler account/DTO scope remains explicit.

Final development checks in `build/c06-install-development`:

- `c06-install-ctest-v4.json`: all15 selected tests pass100.35s, including24 actual
  CQ/SQL/EXISTS/repeated-constant/backend/mode/sink install combinations, paused
  queues and both window FIFO policies, rotation/retirement/repeated switch,
  immutable sink origins and late attachment, promotion and exact next updates.
- Native publication fault tests pass176 I/O cuts,176 process-crash cuts and56
  allocation cuts across both backends. They deny allocations from root selection
  onward and compare actual allocation calls with original-account admissions.
  These crash fixtures switch at B=0; extend to a nonzero caught-up/delivered
  prefix for full acceptance. Existing66 descriptor I/O/66 descriptor crash and
  1180 preparation allocation controls also pass in this packet.
- New recovery regressions prove retirement/sink preflight before WAL repair,
  actual lock retention across compiler decode, wrong-artifact rejection without
  repair, cached-reader failure/barrier/first unread continuation, healthy EOF
  rejection and post-cleanup memory reporting. The monitor found the EOF gate,
  retirement preflight and cleanup scope issues; all three are fixed and tested.
- `c06-install-compatibility-ctest-v1.json`: nine additional legacy checkpoint,
  window envelope, image, journal, sink replay, generation/retirement, rebuild and
  compiler-artifact checks pass34.14s. Together the two packets exercise24 distinct
  tests. Raw LastTest logs are archived before later CTest calls.
- `c06-install-clang-v3.json`:18 strict Clang18 syntax units pass, including
  production/testing variants. This is not linked Clang/runtime evidence.
- `c06-install-registration-v1.json`:295 tests register and all290 predecessor
  definitions/properties are preserved. CTest omits commands for unbuilt binaries;
  exact predecessor CMake text, excluding only the new blocks, is checked too.

Four fresh ASan/UBSan/leak checks pass20.48s in
`c06-install-sanitizer-ctest-v1.json`: actual installation, every publication
allocation cut, locked recovery/cached continuation and descriptor inspection.
The successful build uses the immutable
`build/c06-install-sanitizer-source-v1` snapshot and its manifest. The snapshot has1736
paths:1732 source/fixture/document inputs plus four explicitly incidental generated
Python cache files. Native inputs are compared separately; do not count those
caches as source growth. All981 native/CMake/test input hashes match the current
development source. Sanitizer I/O/crash, full295 and linked Clang execution are
not claimed. Final development source/receipts/artifacts are bound by
`c06-install-progress-v2.json` and `c06-install-development-audit-v1.json`.

Full goal and C06 remain active/in progress:50 verified/2 in progress/26 not
started. Remaining work includes the optional C05 selection bridge/freshness/cost
boundary, nonzero-prefix switch and promotion failure/crash cuts, receiving-account
recovery allocation/exact-cap cases, repeated memory/retirement churn, final
Release/linked Clang/source-only/installed SDK checks and source/evidence seal.
The existing preparation and foundation packets below are historical.

## Earlier durable foundation checkpoint

Current durable continuation (root implements all code): user explicitly requested
one Astra Max monitor, `c06_work_monitor`, after asking for lower routine Astra
frequency. Reuse that single reviewer for concrete checkpoints; do not spawn
routine extra Astra agents. One bounded Luna Max native/JSON codec inventory also
completed. Both are read-only; no code/build/tests were delegated. User also asked
for direct implementation and short exception handling. New codec/artifact main
paths use small guards/helpers and no added catch scaffolding.

All1719 preparation-checkpoint inputs are preserved in
`build/verification/c06-generation-preimages-v1`. The root-v3 descriptor/file
foundation is implemented: exact legacy root v1/v2 retained; v3 binds per-generation
`.plan` with bounded receiving-account reads, candidate/history cleanup, retirement
intent v2 preserving the hash, and native uncertainty latch. Before history deletion
the selected descriptor is reread/hash-verified. Ordinary caller-plan session
recovery rejects v3 pending authoritative locked descriptor admission. No native
plan installation/rotation/recovery/sink-lineage/promotion is supplied yet.

The original six strict Debug generation/retirement tests passed102.82s, including
new66 syscall I/O failures and66 process crashes over plan publication, root
selection and locked reads, exact surviving descriptor/root and unchanged old
files. Legacy intent/root goldens, all retirement fault/crash regressions passed.
Receipts `c06-generation-build-v1.json` / `c06-generation-ctest-v1.json`; exact seven
inputs preserved in `c06-generation-v1-inputs` because later CMake additions differ.

New `CROWNPL1` descriptor codec passes an independent Python1529-byte packet,
six optional-field combinations, every truncation/bit flip, checksummed metadata
corruption, exact byte/work/artifact limits, native funding/OOM/retry. Explicit
`io::CompilerPlanArtifact` factories prepare/replay complete immutable compiler
inputs under a supplied compiler account; native admission requires its receiving
account and finite indexed grant. Six CQ/EXISTS/repeated-constant SQL/backend
combinations pass; forged compiled work rejects. Compiler DTO temporaries remain
explicitly outside native byte accounting; retained compiler-account current/peak
is not a total/phase-local peak. Factory timing now includes internal DTO teardown.
No factory is called inside native mutation; publication must consume this typed
input and incorporate its cost, not hide JSON export in core.

Final strict Debug build-v14 and all eight new/legacy checks passed103.98s in
`c06-generation-ctest-v3.json`, with raw LastTest preserved. This includes the
selected-descriptor retirement freshness check and ordinary caller-plan v3
recovery rejection. Final12 strict Clang18 syntax units passed in
`c06-generation-clang-syntax-v3.json`; new generation source has not received a
linked Clang or sanitizer gate.290 tests register, preserving all286 predecessor
definitions/properties after normalizing the separate build directory. No full290
gate is claimed. All final jobs (build/test7284 and syntax45698) closed exit0;
no jobs remain live. The
previous preparation sanitizer packet below is historical, not new-source proof.

The Astra monitor independently verified all1719 predecessor preimages, seven
receipts/logs and53 existing artifacts. It reviewed root/codec/prepare source,
flagged the ambiguity-reuse latch, work-before-validation order, fixture command
frontier and compiler-factory cleanup timing; all are addressed. Keep cached-stream
retry coverage and current workload configuration at installation on the next
checklist. New test fixture corrections and strict-build failures are preserved;
CTest descriptor-v2 accidentally used the stale v6 binary after build-v7 failed and
is explicitly excluded as updated-source evidence. No flags or semantics weakened.

Current source/continuation manifest is `c06-generation-progress-v3.json`, binding
1728 source paths and final receipts. Earlier v1/v2 job lists are historical.
Independent descriptor packet reproduction lives in
`tests/recovery/reoptimization/generate.py` (default verifies; --write regenerates
from the pinned legacy intent). C06/full goal remain
in progress:50 verified/2 A02+C06 in progress/26 not started. Required next is the
complete typed native publication/locked descriptor recovery/sink lineage/rotation/
retirement/promotion protocol, then actual repeated switches, failure/crash and
full compiler/source-only/SDK acceptance. Do not substitute these file/codec
components for a working plan switch.

### Earlier preparation checkpoint

Previous goal turn completed/sealed C07 below. Current C06 remains in progress;
full goal stays active (50 verified/2 A02+C06 in progress/26 not started). See
[development contract](reoptimization.md). Root implements/reviews the work.
Luna Max `c06_recovery_inventory` supplied one bounded read-only existing-binding
inventory; one Astra Max `c06_transition_review` supplied a bounded read-only
review of complex durable publication/sink lineage. Both completed; no coding
was delegated. Routine design/code/math/tests remain root-owned, following the
user's request to use Astra sparingly.

Latest continuation implements the whole candidate preparation path in the root
model: no agents spawned and no additional Astra use. The user explicitly asked
to reduce Astra Max frequency and rely on the root model for more tasks. Preserve
that preference; reserve Astra Max for occasional unusually difficult reviews.

`QuerySession` now owns original-account snapshot/catch-up state. New explicit APIs
begin a typed candidate, request its admission barrier, advance a bounded native
call quantum, inspect status and cancel. Funded row/record staging precedes old
native begin, commits link without allocating, failed attempts release staging,
and committed no-ops remain ordered. Overflow/OOM/work failures cancel only the
candidate while preserving the ordinary writer's transactional retry contract.
Target replay never emits public output. The final barrier drains admitted queue,
paused and full watermark work, blocks new typed/stream admission, waits for normal
output/sink delivery including empty epochs, and compares exact source rows plus
actual SQL results with bounded funded sets/cursors. Eligibility retains both
owners at B and freezes admission; no plan installation is implied by `verified`.

Status reports exact ledger allocation requests, separate native/coordination work,
phase clocks and original-account current/cumulative-peak memory. Snapshot timing
includes control allocation; old drain time is separate from incremental staging/
replay cost. Drop releases migration control. Original WAL/root uncertainty also
terminates candidate state as recovery-required, preserving original gates/locks;
cancel cannot bypass them. Core runtime still has no selection-runtime dependency.

All16 selected strict GCC Debug CTests pass33.30s in
`c06-session-ctest-v4.json`, with exact inputs in `c06-session-build-v7.json` and
archived raw LastTest. Four C06 checks include16 original SQL/CQ/backend/mode/build
cases, four multirow repeated/constant SQL projection cases, both watermark FIFO
policies/backends, exact ledger byte boundaries, OOM/work/policy/stale fences,
unread stream barrier and original generation/sink recovery. The fault check
passes all1180 actual allocation cuts across snapshot/old-begin/catch-up/equivalence,
nonallocating publication after old-WAL sync, and input/decision uncertainty with
exact original journal recovery on both backends. Existing12 regressions cover
session/exception/window/sequence/checkpoint/window-envelope/journal/generation/
local-sink replay/memory/initialization/scale. This is not a full registered gate.

All four fresh ASan/UBSan/leak C06 tests pass18.28s in
`c06-session-sanitizer-ctest-v1.json`, from exact1719-source copy
`c06-session-sanitizer-source-v1.json` and native build-v2. All14 final GCC code/
CMake/test inputs exactly match that copy. Strict Clang18 syntax controls pass13
actual production/testing runtime and C06-test translation units; this is not a
Clang-linked runtime gate.286 tests register, preserving all284 predecessor
properties and exact CMake definitions plus two new test blocks; see registration
audit-v1. No full286 or four-configuration acceptance is claimed. GCC build49174/
test76782, fresh sanitizer build54160/test90017 and Clang52841 all closed exit0;
no jobs remain live. Sanitizer v1 failed configure because bare clang names were
absent from PATH; v2 uses the installed GCC sanitizer runtime. All failed receipts
remain. Earlier session
CTest-v1 driver read private output; CTest-v3 fixture wrongly expected delta output
in maintenance mode. Both are corrected; exact14 v6 failed-test inputs are retained
in `c06-session-ctest-v3-inputs`. No flags or production semantics were weakened.

All1716 foundation inputs are preserved in `c06-session-preimages-v1`. Current
continuation/source receipt is `c06-session-progress-v4.json`; earlier v1–v3 job
lists are historical. Native additions are
`src/runtime/reoptimization_detail.hpp`, `tests/unit/reoptimization_session_test.cpp`
and `tests/unit/reoptimization_fault_test.cpp`; session/storage row preflight and
physical/delta equivalence integrations are changed. Full durable selected-plan
publication, root-v3 descriptor/recovery/sink lineage/retirement, actual repeated
switches and full compiler/crash/acceptance/seal remain required before C06 verified.

Native `DeltaRuntime::rebuilt_for` now bootstraps an actual typed minimum-height
alternative from the current complete admitted source. It preserves exact
physical epoch, actual mode, source/backend grant and old state, under the same
original query account; target has a new owner. PhysicalRuntime's same-plan
rebuild shares the new internal common path. Compiler and physical build grants
stay distinct and both require accounting in eventual C06 reports. This primitive
does not install a session plan or pretend to supply ordered catch-up/durability.

The allocation-free policy module uses explicit caller-predicted nanoseconds per
input/horizon, minimum epoch gap, relative/absolute savings and exact payback of
measured preparation plus a publication/cleanup reserve. C02 unitless scores are
not time predictions. Missing/invalid forecasts, insufficient gain/horizon and
u64 overflow reject honestly. Eligibility grants no native switch authority.

At the earlier foundation checkpoint, strict GCC Debug build-v3/v4 and all four
selected CTests passed0.66s: new bootstrap,
new policy and both existing initialization/scale regressions. The bootstrap
covers48 SQL/CQ/reference/indexed/mode/build combinations and32 actual alternative
plans, exact subsequent source/results/deltas, busy/private/cursor/unread-output
barriers, foreign candidates, work/memory exhaustion and retry. Standalone exact
policy arithmetic tests also passed.284 tests registered then, not a full284 gate.
Receipts: `build/verification/c06-native-bootstrap-build-v3.json`, `build-v4.json`,
`c06-native-bootstrap-ctest-v2.json` with archived raw stdout, and registration-v1.
Build handles50198/73889 closed exit2 (strict test-indentation then make's initial
old graph missing newly generated policy target); explicit configure/build15846
and final42666 closed exit0. First/v2 four-test receipts are preserved. No jobs
remain live; never restart from quiet logs/stale progress.

All1711 predecessor inputs have exact preimages in
`build/verification/c06-reoptimization-preimages-v1`. The earlier foundation
manifest is `c06-reoptimization-progress-v6.json`; current continuation/source is
the session-progress-v4 receipt above (development scope, not a seal).
The public policy header/source, tests and development guide were new files;
CMake and native delta/physical headers/sources changed. All earlier artifact trees
and sealed C07 evidence remain untouched. Broad work is uncommitted; .git is
read-only; local commands need escalation because the default launcher is broken.

Next implement complete C06 selected-plan publication on top of the preparation
path above. Prepare every allocation/metadata object before publication and retain
the old runtime through completion. The selected generation must be self-contained:
root-v3-bound plan descriptor,
target checkpoint and WAL, exact immutable sink-origin header/validated lineage,
versioned retirement intent and recovery under the same root lock. Keep current
HeaderMatch checks strict. Candidate-only unchanged failures can abort target;
post-selection uncertainty must block admission/output and recover authoritative
root, never overwrite it to roll back. Journal-only sessions require explicit
managed-root promotion. Rebind or account retained old program/catalog aliases.

Keep selection integration opt-in to avoid core runtime -> selection_runtime
cycles. Native core can consume typed candidates; an optional C05 bridge must
revalidate actual owner/epoch/source at prepare. Descriptor encoding/admission
must preserve S05's original-account/explicit compiler-DTO boundary; do not hide
unaccounted PhysicalPlan/JSON exports inside a native switch. Add repeated-switch,
queue/window/watermark, sink-backpressure/empty-epoch, allocation/crash/fault cuts,
recovery of either surviving root and post-retirement restart against exact
non-switching references. Full compiler/source-only/work/dual-state accounting
and final evidence review/seal remain before C06 verification.
Never build during CTest in one directory; archive LastTest.log before later
CTest/enumeration. No project license or full release is inferred.

## Current C07 verified checkpoint

C07 is verified. Root implemented/reviewed the public C05 training-only exporter,
proof-preserving candidate-v2 collector import, disjoint trace corpus and actual
held-out B03-based runner. See [methodology](ranking_evaluation.md),
[finite observations](verification/c07-heldout-observations-2026-11-11.md) and
[acceptance](verification/c07-ranking-acceptance-2026-11-11.md).
Luna Max provided one bounded read-only corpus inventory. No Astra used. Root
handles most work; reserve Astra Max for occasional difficult problems. The full
Refactor goal remains active:50 verified/1 A02 in progress/27 not started.

All15 selected fresh-source Release CTests pass315.59s: three C07 and12 B03/B02/
CLI/package/schema/admission/reference/C03/C02 regressions. The source-only copy
has1710 exact inputs, no old cache/objects. All279 predecessor test commands and
properties remain;282 registered. Every sanitizer registration retains leak/halt/
stacktrace settings. This is selected acceptance, not a full282 release gate.

Full independent acceptance passes in304.64s:16 checked candidate artifacts across
six query/backend groups,240 preflights,576 retained runs (one warm-up/two measured),
162 held-out analyses and486 exact raw cost/regret/error checks. The15 traces/916
physical events have disjoint row domains, independent assignment/SQLite oracles,
relation-mix/fanout shifts and charged loading/noops. Query families cross roles;
this is not unseen-query-family generalization. Native C05 choices use training
only; calibration mappings freeze before held-out warmups/samples. Measured
feasible candidates define regret, not the policy's own proxy score.

Native P06/P07 observes3 Boolean-path/4 star/1 composite candidates per backend
and heights2/1/1. Their declared finite families exhaust without establishing
minimum global cost. Original height-proof witnesses stay intact; the collector
independently checks actual candidate validity/equal optimum height. Workflow-v1
still requires witness identity. Actual C05 constraints/stops and exact C02
unitless proxies are retained; C03/C04/C06 are disabled/separate. The finite
report preserves weighted-depth active-time regret4.82–7.15% and about19% sampled
native memory regret on one shifted reference Boolean context. No fixed speedup,
confidence or global CBO claim follows. Memory peak is boundary-sampled before
final workload export, not RSS or a phase-local peak.

Debug/Clang18/ASan+UBSan/leaks controls each pass144 independent train/rate/fanout
candidate/mode checks plus18 raw measurements/168 commands. Actual C05 choices
and decompositions equal Release. Moved installed public exporter/collector
examples pass48 independent cases/62 commands and strict C++23 without source/
build/test/reference dependencies. Core libraries/headers/old tests/B02 data
remain unchanged. Only reviewed pinned upstream C/Make warnings appear.

Evidence prefix `build/verification/c07-`: `ranking-inputs-v1.json` freezes1710
tested paths, preserving all1660 predecessors; `ranking-fresh-source-v1.json`
is the exact copy. `matrix-audit-v1.json` binds5778 actual artifacts,128 fresh C++
units/seven ELFs/16 build CROWN archives, four compiler configurations and all
matching raw outputs. `requirement-audit-v2.json` accepts twelve requirements.
`ranking-inputs-v2.json` is the1711-path documentation-only successor. Verify
`checkpoint-seal-v1.json` and `post-seal-v1.json`; final continuation is
`ranking-progress-final-v1.json`. All1660 predecessor preimages remain in
`c07-ranking-preimages-v1`.

Preserve v1's honest512MiB raw-output failure after540 runs and exact source
preimages. Full C07 uses an explicit1GiB default grant; no calls/checks are
truncated. Development exporter v1's options-version probe error also remains.
All final jobs were observed closed exit0: fresh46823, full checker7956,
installed19378, Debug52455/Clang44208/sanitizer47036 and final audit84189.
No verification jobs remain active. Do not restart from quiet logs/stale progress.
Never build during CTest in one directory; raw LastTest.log is archived before
later tests/enumeration. Broad work is uncommitted; .git is read-only and local
commands need escalation because the default launcher is broken.

Next: C06 depends on verified C05/R06/O05. Existing APIs rebuild the same plan and
restore exact physical bindings; they do not expose a safe hot-plan replacement.
Implement actual snapshot rebuild/ordered catch-up/equivalence/atomic switch with
old-plan rollback, hysteresis/payback and shared dual-state accounting. Preserve
session input/output progress and O05 journal/checkpoint/generation binding;
do not substitute restoring an old checkpoint under another plan. C04/B01/A02
license disposition, other extensions, B04/B05 and full release gates remain.
Do not infer a project license or mark the full goal complete.

## Current B03 verified checkpoint

B03 is verified. Root implemented and reviewed the public native collector,
controlled repeated runner, closed raw/experiment schemas and moved-install
example; see [measurement.md](measurement.md) and the
[acceptance record](verification/b03-measurement-acceptance-2026-11-11.md).
Luna Max provided one bounded read-only API inventory. No Astra used. Root
handles most work; reserve Astra Max for occasional difficult problems, following
the user's latest preference. The full78-card goal remains active.

All12 selected fresh-source Release CTests pass in22.05s: both B03 tests and ten
predecessor regression tests, including560 B02 native replays/9944 epochs,
CLI/package and selected schema/admission/reference/C03/C02 checks. The exact
copy has1659 inputs with no old cache/objects. All277 predecessor commands and
properties are retained;279 registered. Every sanitizer registration retains
leak/halt/stacktrace settings. This is selected acceptance, not a full279 release.

Debug/Release/Clang18/ASan+UBSan controls each pass30 configurations/60 native
commands over five independent B02 mechanisms, both storage backends and three
output modes. Persistent controlled packets pass12 configurations ×three retained
runs (one warm-up/two measured), plus disabled observations/workload, actual
single-CPU affinity,100us sink wait, six collector rejections and an owned-child
timeout. The moved installed example passes12 independent SQL/backend/mode cases
and33 commands under strict public-only C++23. No speedup comparison follows.

Actual storage labels come from the validated compiled plan. Native preparation
includes pending-owner cleanup; committed epoch cleanup has a separate disjoint
clock. Every loading prefix starts from empty and contributes to totals. Raw
warm-ups remain available and are excluded from summaries. O07/C01 availability,
saturation and overlap rules remain explicit. Native current/cumulative-peak
account bytes are distinct from process RSS; caller/compiler/report/input-stream
DTOs remain outside that account. No phase peak is derived by subtraction.

The harness binds sources/objects/archives, compiler-recorded headers, compiler
binary/version, repository HEAD/change status, harness sources, dependency lock,
environment and actual thread/affinity. Uncommitted hashes identify measured
bytes. This is volatile native core work with a funded EventReader and external
encoding/sink; no WAL/checkpoint/fsync. Durable O08 CLI has a separate scope.
Unchanged production runtime/library algorithms retain their sealed provenance.

Evidence prefix `build/verification/b03-`: `measurement-inputs-v1.json` freezes
1659 tested paths, preserving all1651 predecessors; `measurement-fresh-source-v1.json`
is the exact copy. `matrix-audit-v1.json` binds2082 actual artifacts,127 fresh C++
units/six ELFs/16 CROWN archives and four compiler controls.
`requirement-audit-v2.json` accepts ten requirements. The documentation-only
successor is `measurement-inputs-v2.json` (1660 paths). Verify
`checkpoint-seal-v1.json` and `post-seal-v1.json`; continuation is
`measurement-progress-final-v1.json`. All predecessor preimages remain in
`b03-measurement-preimages-v1`. Preserve failed prototype/runner/install/audit
receipts; they are superseded evidence, not acceptance on current sources.

All live jobs were observed terminal: fresh driver62827, controlled runner7996,
Release controls48719, Debug20241/Clang78006/sanitizer50242 and installed13036
closed exit0. Final audit80439 closed exit0; first audit46011 caught its own
missing-log-field assumption and is superseded. Earlier strict compiler errors,
backend-label rejection and GNU-extension example failure remain preserved.
No verification jobs remain active. Never restart from quiet logs/stale progress.
Never build during CTest in one directory; raw LastTest.log is archived before
later enumeration. Commands require escalation because the default launcher is
broken; broad work is uncommitted and .git remains read-only.

Next choose C07's actual train/calibration/evaluation split and feasible-candidate
measurement against verified C05/B03, preserving independent results and separating
search/model/runtime quality. C06 is another open path. B01/A02 license/source
qualification, B04/B05 experiments, extensions and full release gates remain;
do not infer a project license or mark the full goal complete.

## Current B02 verified checkpoint

B02 is verified. Full78-card goal remains active; A02 licensing and29 other
cards/release gates remain open. Root implemented and reviewed the generator,
manifest/schema, independent oracles, native exporter, registry and acceptance.
Luna Max supplied two bounded CROWN/DynaGox classification proposals, independently
checked and corrected by root. No Astra was used. Root handles routine work;
reserve Astra Max for complex problems, following the user's preference.

See the [workload guide](workloads.md) and
[acceptance record](verification/b02-workload-manifest-acceptance-2026-11-11.md).
The generated corpus has24 SQL definitions/144 traces:20 admitted families with
seven regimes each, plus four rejected controls. Independent assignment/SQLite
oracles agree on2507 events (2486 admitted). Cases include non-graph higher-arity,
Boolean/disconnected/proper-head, nested/equal/contained, composite/string and
self-join mechanisms. Every runnable case binds complete semantics/head/structure/
update/backend/output/provenance contracts. No all-free-connex coverage follows.

GCC Debug/Release, Clang18 Debug and ASan+UBSan/leaks controls each pass560 native
replays/9944 epochs/644 commands, with actual rows/deltas/source/sequence checked
on reference/indexed storage and delta/maintenance modes. The exporter has no
oracle/query-class dispatch and uses production libraries. Exact sealed archive
hashes and unchanged336 case files connect those controls to final sources.

All10 integrated source-only Release CTests pass in13.39s, including the three
B02 tests, CLI/install and selected schema/admission/reference/C03/C02 checks.
The copied tree has exactly1650 inputs and no old cache/objects. Existing runtime
and test code is unchanged. All274 C03 predecessor and both local B02 test
commands/properties remain;277 registered. Current277 sanitizer registrations
retain ASan leak/halt and UBSan halt/stacktrace settings. This is selected
acceptance, not a full277 release run or controlled performance experiment.

The source inventory covers all116 scenarios/13 distinct local CROWN labels,
122 local fingerprints/120 original Git blobs, and24 original pinned DynaGox
aggregate SQL definitions. Root checks the original SELECT/GROUP BY/occurrences,
source pins and equality bodies:22 acyclic, DUMBBELL/TPCH-Q5 cyclic. All24 parse
and shape-check in four compiler modes; no aggregate is silently rewritten or
enabled for native R1 timing. Seven registry entries bind source packets while
real datasets/catalogs/licenses/runtime contracts remain unavailable. DynaGox
experiment variants are distinct from complete official suites. Source-only
SQL imports grant no baseline build, timing or distribution authority.

Evidence prefix `build/verification/b02-workload-`: `import-inputs-v1.json` is
1650 tested paths; `import-fresh-source-v1.json` the exact copy;
`import-matrix-audit-v1.json` pins3519 actual native/raw artifacts,126 final fresh
C++ units/five ELFs/16 CROWN archives and all preserved controls.
`requirement-audit-v2.json` accepts eight requirements. `import-inputs-v2.json`
is the1651-path documentation-only successor. Verify `import-checkpoint-seal-v1.json`
and `import-post-seal-v1.json` before edits; final continuation is
`progress-final-v1.json`. Keep all preimages and original failed receipts.

The earlier local driver96435 retains exit8 from root's omitted selection-library
build target. Repair19707/56246 succeeded without source changes; the final
integrated driver10188 includes the package closure and closed exit0. Import
sanitizer9736 and registration8142 also closed exit0. No verification jobs remain
active. Never restart historical jobs from quiet logs or superseded progress.
Never build during CTest in one directory; archive LastTest.log before later
CTest/enumeration. The broad tree is uncommitted, `.git` read-only, and commands
require escalation because the default launcher is broken.

Next implement B03 against verified O07/O08/B02: a controlled repeated runner,
recorded environment/raw timing/memory/latency/counters, explicit compile/load/
maintenance/full-or-delta/encoding/sink boundaries, actual output-mode labels and
correctness before timing. Use runnable manifested inputs; unavailable imported
sources cannot become native comparison runs. C07 held-out quality follows B03.
C06, R2/R3 and full release gates remain. Do not infer a project license or claim
fixed speedups, full official-suite results or complete Refactor implementation.

## Previous C03 verified checkpoint

C03 is verified; full78-card goal active. Root implemented and reviewed the
model and owns acceptance. Luna Max supplied bounded independent fixtures and
calibration/profile/result failure-test proposals, reviewed and integrated by
root. No Astra was used. The user asks root to handle routine work and reserve
Astra Max for complex problems. See the [model contract](maintenance_cost.md)
and [acceptance record](verification/c03-maintenance-cost-acceptance-2026-11-10.md).

Candidate-bound native profiles produce conditional event/touched-bucket
forecasts and exact rational decompositions. Observations remain distinct from
measured or inferred calibration assumptions; raw observations/rank/uncertainty
are retained. Full/delta/annotation/encoding/checkpoint demand and memory budgets
stay separate. Closed reports and the moved-install SQL-only example pass. No
C03 policy is automatically enabled in C05. Existing pre-C03 runtime sources
and tests remain unchanged.

All31 selected tests pass in GCC Debug61.55s, Release18.60s, Clang18 Debug42.78s,
ASan+UBSan/leaks Debug226.14s and fresh source-only Release18.45s. Scope: eight
C03, four ranking/memory and19 CLI/package regressions. This is separate from
the full274-test release gate. All266 earlier generated commands/properties are
preserved. Strict C++23 warnings/errors, test assertions and sanitizer settings
are audited; only reviewed unmodified pinned vendor C/Make diagnostics appear.

Reference/indexed coverage includes sampled60/12 versus complete36, exact census
4inputs/2changes, selected no-ops, unseen strata, truncation, backend mismatch,
zero-demand, private-state rejection and actual test-ABI saturation. Saturated
details cannot become complete forecasts or timing features. Per mode, persistent
failure tests cover212/216 capture and16/16 estimate allocation positions, plus
four fitting/three isolated-calibration allocations. Earlier records, account
usage and runtime/workload/rows remain intact; retry succeeds.

Evidence prefix `build/verification/c03-final-native-`: `inputs-v1.json` freezes
1155 tested inputs; the fresh copy contains exactly those files with no previous
objects/cache. `matrix-audit-v1.json` binds1285 actual artifacts, five modes and
13 closed phase jobs. `requirement-audit-v2.json`, `root-review-v1.json`, warning
review and Git provenance record final review. `inputs-v2.json` is the1156-path
documentation-only successor; `checkpoint-seal-v1.json` and
`post-seal-audit-v1.json` are authoritative for restart. Preserve the historical
raw development failures and source preimages. Earlier calibration data remains
in `c03-measured-calibration-reports-v3` and the two compiler control directories.

All driver handles were observed terminal with exit0: Debug74495, Release21007,
Clang74620, sanitizer51774 and fresh Release72421. No C03 jobs remain active.
Never restart from a quiet log or old progress file. Never build during CTest in
the same directory, and archive LastTest.log before later CTest/enumeration.
Local commands require escalation because the default launcher is broken;
the broad worktree is uncommitted and `.git` is read-only.

Next choose an unblocked Refactor card from its actual dependencies: B02's
workload manifest can prepare B03/C07 experiments; C06 reoptimization is another
open implementation path. C04 depends on unresolved A02 license disposition.
Do not infer a project license. Preserve unavailable/rank-deficient model facts,
future-memory uncertainty and native resource/delivery boundaries. C05 richer
policy integration, held-out quality, remaining cards and V release gates stay
open. Do not mark the full goal or an R1 release complete.

## Previous O08 verified checkpoint

O08 is verified. Root implemented and reviewed production additions and ran the
matrix/audit; Luna Max supplied bounded independent fixtures and a guide draft.
No Astra was used. The user prefers root to handle most work and reserve Astra
Max for difficult cases where another deep review helps.

[Acceptance evidence](verification/o08-workflow-acceptance-2026-11-10.md) and the
[CLI/install guide](cli.md) describe SQL/catalog compilation with independently
checked minimum-height artifacts (or a checked constant-false operator), direct
compiled EXPLAIN/validation, native run/restore/snapshot/checkpoint/results,
bounded trace verification and a scoped durable-file benchmark. Reports grant
no acknowledgment or retirement authority. IDs, limits, errors and observation
context are explicit. A relocatable CMake package exports versioned public APIs
and a generic SQL-driven example, with no query-class registration.

All19 affected CLI/package tests passed in GCC Debug (70.29s across two archived
invocations), Release (13.77s), Clang18 Debug (42.42s), ASan+UBSan/leaks Debug
(221.35s), and clean source-only Release (13.66s). Each mode covers259 CLI checks
over34 independent physical events/five fixtures and18 moved-install/public
consumer commands. The installed consumer processes2 events, rotates, then
restores1 in a new process, matching exact oracle state/source/output progress.
The documented helper and full file workflow also passed nine commands.

All264 prior generated test commands/properties and all existing native runtime
implementations/tests are unchanged;266 tests are registered. This selected19
matrix is separate from the predecessor's full264x5 acceptance and from a future
full266 release gate. Eight O08 requirements and895 actual build artifacts were
audited: five CLI ELFs,605 C++ objects,80 CROWN archives, five parser archives,
170 flags/link records and30 metadata files. No project C++ warning or weakened
assertion/cap/timeout was accepted. Reviewed pinned upstream C warnings remain
explicit, including a sanitizer-only namestrcpy warning followed by a final NUL.

Evidence prefix `build/verification/o08-workflow-native-` contains1102 preserved
preimages, frozen1140-input `inputs-v1`, exact fresh-source manifest, immutable
phase receipts/logs/archived stdout, `matrix-audit-v1`, eight-requirement review,
Git provenance, final documentation successor and checkpoint seal. All four
matrix driver handles were observed terminal with exit0: Release18289,
Clang56767, sanitizer73745, fresh Release28165. No O08 jobs remain active. Never
restart a completed verification from a quiet log or superseded progress file.
The older isolated O08 candidate is superseded; do not copy it over current code.

Next: review C03 maintenance cost-model requirements against verified C01/C02
interfaces. A02 license choice, remaining optimizer/extensions, experiments and
full release reviews remain open. Keep source frozen during builds/tests,
never build in a directory with live CTest, and archive LastTest.log before a
later test/enumeration. Full78-card goal remains active.

## Predecessor integrated O04–O06 acceptance

O05 and O06 are verified after full 264/264 PASS in Debug, Release, Clang18,
ASan+UBSan/leaks and fresh source-only Release. O04 is revalidated in that cohort.
See [integrated evidence](verification/o05-o06-native-acceptance-2026-11-10.md).
Root implemented/reviewed the native work and owns acceptance. Luna Max supplied
bounded earlier coverage inventory; no Astra used. Root handles routine work;
Astra Max remains occasional for unusually difficult problems.

The 1101 tested source paths preserve all 1100 predecessors. This round adds two
native pipeline tests and fixes three comment descriptions; production behavior
is unchanged. All 262 earlier test commands/properties, fixtures, assertions,
caps and timeouts remain. Both backends now compose loop-edge multi-alias
private-work prefixes,460 persistent OOM points,32 writer errors,16 poisoned
same-owner sink errors and68 process exits with exact oracle state/deltas,
feed20/30/40 positions, queued-next-event preservation, work retention, next
update, verified retirement and restart. Predecessor round trips/corruption/
stream/window/resource/crash coverage also runs fully in all five modes.

The 20-requirement implementation audit and both unchanged production-only controls
pass. Native audit pins1090 registered executables,65 relevant actual objects,
130 Crown archives/five parser archives,1240 strict flag records/1220 links,
15 metadata files and ten control executables/objects. All 40 final jobs are
closed; terminal stdout archived. Source-only fresh build uses no previous
objects/cache and all compiled units use the copied tree. Strict warnings,
assertions, leak/undefined checks remain; only three unchanged pinned upstream
C diagnostics appear in the fresh build.

Evidence prefix: build/verification/o05-o06-final-native-acceptance-.
Authoritative final inputs-v2 has1102 paths (one new evidence document);
inputs-v1 remains the 1101 tested source snapshot. Verify checkpoint-seal-v1 and
post-seal-audit-v1 before edits. The packet includes preimages, fresh manifest,
all raw full-matrix receipts/stdout, binary inventories, public controls,
requirement-audit-v2, root-review-v1, matrix-audit-v1 and progress-final-v1.
Never build during CTest in the same directory. Archive LastTest.log before
another test/enumeration. Local command execution requires escalation because
the default launcher is broken in this environment. The working tree is broad
and uncommitted; do not discard pre-existing work or write the read-only .git.

O08 has a concrete isolated candidate at build/o08-workflow-source-v1 (1106
paths; seven changed/new paths). The original tested source stays unchanged.
Its strict Release production build and real CMake installation passed; the
149-file install was moved before an outside C++23 consumer configured/built.
Installed CLI and consumer both passed unseen SQL/self-join, durable output,
feed20/30/40, checkpoint/restore, exact next-deletion and malformed-proof/version/
argument tests. See build/verification/o08-workflow-progress-v1.json and
its source/install/consumer receipts. This is unmerged candidate evidence, not
full O08 acceptance. Copy only its seven changed/new paths after preserving this
final source; retain all authoritative final docs. Compile artifact EXPLAIN,
options/help/schema/error/export contracts, examples/registration and complete
required validation remain. Luna Max's install inventory is read-only; root
owns this implementation.

Next complete O08 library/CLI/install examples for a complete unseen supported
SQL workflow. Read actual Refactor.md O08/Section8.5 and existing public APIs/
CLI before changing code; preserve existing native semantics and exactness and
resource status reporting. A02 needs the user's project license choice; complete
unblocked work first. C03/C04/C06/C07, W/X/B/V cards and release gate reviews stay
open. The full 78-card goal remains active:45 verified, A02 in progress,32 not
started. Do not mark the full goal complete for O05/O06 card acceptance.

Limits remain trusted stable Linux namespace/cooperating locks/local fsync;
process exits are not power-loss tests. Arbitrary external callback effects
require their own durable idempotency protocol. Old unproved v1 sink prefixes
cannot retire/rotate. Sink file compaction/spill is not added and configured
file/index caps remain. Full release gate disposition stays open.

## Predecessor O05/O06 native history retirement

This historical snapshot's next-work statements are superseded by the integrated
acceptance above.

This goal turn is progress. Root implemented/reviewed production code. Luna Max
supplied bounded read-only inventory/review and independent724-byte intent/
324-byte root fixtures; no Astra was used. All1088 predecessor paths preserved.
Full goal remains active; ledger43 verified/3 in progress(A02/O05/O06)/32 not
started,78 total. See [retirement API](history-retirement.md) and
[evidence](verification/o06-history-retirement-native-2026-11-10.md).

`retire_generation_history()` requires quiescent native state and actual private
local prefix verification through committed output, plus selected checkpoint/root
validation. Rootv2/324 bytes pins checkpoint sink identity/physical sequence/
byte length/ordered frame-checksum chain. File frames stay unchanged; account-
funded per-prefix hashes and private native verified-prefix state prevent
pre-checkpoint forged output from being promoted on restart. V1/212-byte roots
remain recoverable, but an older unproven sink prefix cannot retire/rotate.

Under the same generation lock, no-replace+sync724-byte CROWNRT1 intent records
the old range/native root projection and sink header/ack coverage; same-generation
floor update+sync preserves its delivery anchor; each recorded older unlink
directory-syncs; intent unlink+directory-sync happens last. Current pair stays
recoverable. Unknown failures block session publication until reopen. Sink-aware
factory validates actual root/checkpoint/sink/native/source/intent before either
tail repair, then resumes cleanup before exposure. Bare recovery rejects pending
intent. No allocation occurs after intent publication. Limits remain copied,
cumulative and charged to the original account; no automatic quota refill.

Initial6/6 focused tests missed a real checkpoint-boundary sink-prefix gap found
by Luna review. Root production control proves deletion before fix (negative1);
unchanged final control rejects/preserves history (positive0). Full1099 interim
paths (1095 sources+4 generated caches),5 relevant objects/negative ELF preserved.
The v2 content anchor/private prefix fix is covered through both restart paths;
follow-up review found no concrete bypass/order issue. Root owns acceptance.

Frozen source1:1098 paths;10 existing production/build/header edits plus10 new
paths. Final75/75 PASS four modes: Debug 202.14s, Release 288.92s, Clang18 290.96s, ASan+UBSan/leaks 221.05s.
262 registered names preserve all259 predecessors; scoped75, not whole/fresh
acceptance.12 typed/32 stream/16 window cases,724 intent and324 root cuts/flips,
861 allocation faults,312 actual file errors/312 process exits verify real native
state/source/output/dedup/next update. Predecessor generation coverage remains
dynamic (226 errors/228 process exits). Crashes are not power loss.

Audit pins228 executables,48 objects,16 archives/four caches and488 flags/links.
All19 final matrix/control receipt jobs CLOSED; stdout archived. Prefix
build/verification/o06-history-retirement-native- contains preimages/interim/
negative-objects/independent-v1,controls,inputs-v1,final jobs,matrix-audit-v1,
root-review-v1,progress-v1,jobs-v1,checkpoint-seal-v1,post-seal-audit-v1. Final
docs-only source2 adds API/evidence guides (1100 paths). Verify seal/readback
before new edits; never build during CTest in the same directory, and archive
LastTest.log before another test/enumeration.

Next: whole262+ and fresh-source integrated O04–O06 acceptance. Review actual
Refactor.md O05/O06 requirements and native invariants against complete evidence
before changing either ledger status. Update stale v1-only source comments when
preparing that fresh build. A02 licensing, O08 CLI, other cards and release gates
remain open. Sink-file compaction is not added: existing file/index caps still
bound output retention. Local file delivery proves no arbitrary external effects.

## Predecessor O06 sink-aware native reconstruction

This is the historical restart snapshot; next-work statements are superseded
by the retirement component above.


This goal turn is progress. Root implemented/reviewed production changes; Luna
Max supplied bounded read-only inventory/review. No Astra was used. All1084
predecessor paths preserved. See [API](local-sink.md) and
[evidence](verification/o06-sink-restore-native-2026-11-10.md). Full goal active;
ledger43 verified/3 in progress(A02/O05/O06)/32 not started,78 total.

New `restore_journal_with_local_sink` and `restore_generation_with_local_sink`
validate the actual persisted sink in the same receiving account before native
replay. `File::verify_epoch` compares existing complete canonical epochs without
writing missing output, including through a valid incomplete suffix. Actual
accepted physical epochs incl empty closures are verified and released without
entering replay backlog; metadata commits emit no new physical closure. Only
missing output consumes replay row/byte caps. Fully accepted replay accepts zero
for both, while native spool/sort/views/index/transient buffers retain the shared
heap and copied cumulative decode/source/file/delivery-work limits. No caller
frontier can substitute for durable coverage. Both tails repair only after full
WAL/native/source/pending/EOF/stamp/sync/seek checks. No owner/output escapes on
failure. Existing two-step/bare factories retain their documented behavior.

Frozen source1:1087 paths;5 existing build/production edits and3 new tests/support.
Selected72/72 PASS all four modes: Debug 115.85s, Release 131.98s, Clang18 147.79s, ASan+UBSan/leaks 166.98s.
259 registered names retain all256 predecessors; this is scoped72 acceptance,
not whole259/fresh acceptance.48 typed/32 stream/16 window cases verify exact
native state/source/outputs/next updates and no tentative append. All1161
receiving allocation faults,204 actual file errors and204 process exits pass,
including both-tail repair ordering, exact/under caps and finite interruptions.
Crashes are not power loss. Public production-only control proves zero backlog
restore/exact7 vs6 work and read-only missing-epoch rejection. Luna found no
concrete production defect in its bounded review; root owns acceptance judgment.

Audit pins220 executables,32 objects,16 archives/four caches and472 flags/links.
All18 final matrix/control receipt jobs CLOSED; terminal stdout archived. Prefix
build/verification/o06-sink-restore-native- contains preimages-v1,controls,
inputs-v1,all final-v1 jobs,matrix-audit-v1,root-review-v1,progress-v1,jobs-v1,
checkpoint-seal-v1,post-seal-audit-v1. Final docs-only source2 adds this record
(1088 paths). Verify seal/readback before edits. Never build during CTest in
the same directory; archive LastTest.log before later tests/enumeration.

Next implement durable generation history-retirement intent/continuation bound
to the live verified sink, selected checkpoint/root and original lifetime lock.
Keep old selected pairs until the protocol is durable. Root's current212-byte
CROWNGR1 first/current floor and gen+1-only publication need a reviewed same-gen
floor operation plus durable pending cleanup intent; advancing first before
recording cleanup loses which pairs remain to delete. Every unlink/directory
sync/root update/intent cleanup failure or crash must leave a recoverable selected
pair and resumable intent. Do not authorize deletion from reports, caller-frontier
options or output consumption. Cover those boundaries, then whole259+new/fresh
O04–O06 acceptance. A02 licensing, O08 workflow and other Refactor cards/release
gates remain open.

## Predecessor O06 durable local epoch sink

This is the historical sink snapshot; next-work statements are superseded by
the sink-aware component above.


This goal turn is progress. Root implemented/reviewed production code. Luna Max
supplied bounded inventory/read-only review and independent265-byte fixture; no
Astra was used. Root handles most work; Astra Max stays occasional. All1070
predecessor paths verified/preserved. See [local sink API](local-sink.md) and
[evidence](verification/o06-local-sink-native-2026-11-10.md). Full goal active;
ledger43 verified/3 in progress(A02/O05/O06)/32 not started,78 total.

CROWNSK1 framed local files atomically accept complete committed physical epochs,
including empty output. Canonical native typed bytes/signs bind query/sink/
program/source/catalog/policy/schema/generation/physical sequence and exclude
ordinal/order/layout address. Retries compare full bytes. File create/open/append/
read/receipt/explicit torn repair retain trusted Linux nofollow/flock/fsync
semantics, original-account storage and copied cumulative limits. Private immutable
receipts cannot be constructed from mutable reports or detached bytes.

QuerySession create/open/deliver/read/state/receipt APIs own the sink. Output stays
until sync; further begin returns would_block before another source peek, typed
queues stay bounded and direct transfer/discard cannot bypass delivery. Post-sync
acknowledgment is allocation-free. Recovery verifies already persisted epochs,
then emits missing output in order; metadata window steps have no extra physical
output epoch. Stop/drop preserves WAL-based native/output reconstruction.

Final frozen source1 selected69/69 PASS four modes: Debug 73.51s, Release 51.92s, Clang18 89.3s, ASan+UBSan/leaks 143.23s.
256 registered names retain all253 predecessors; this is scoped69, not whole256
or fresh-source acceptance.24 typed/32 stream/16 partial-window cases compare
independent results/state/source/next updates, with canonical retry across restart
and generation rotation.381 epoch cuts/656 header cuts/1036 flips+63 checksum
prefix negatives, exact-under caps, native scalar lifetime, slow queue/cancel and
private fan-out barriers pass. All5 delivery OOM points retain output for retry;
108 actual file errors and108 process exits verify native old/new state/source/
output/dedup/next update. These crashes are not power loss.

Luna found a partial-header-checksum flaw after focused tests passed. Root public
production-only control reproduces accepted/truncated corrupt hex byte (exit1);
same final control rejects before repair and preserves bytes (exit0). Full1082
interim paths and4 relevant objects/negative ELF preserved. Available checksum
prefix bytes now validate against SHA256 with work reserved. All predecessor
tests/fixtures/caps/timeouts/flag records unchanged; accepted strict builds have
zero diagnostics and assertions/sanitizer/leak checks enabled.

Audit pins212 executables,40 changed-unit objects,16 archives/four caches and456
flags/links plus4 public-control builds. All18 final matrix/control receipt jobs
CLOSED; terminal stdout archived. Prefix build/verification/o06-local-sink-native-
contains preimages-v1,interim-v1,negative-objects-v1,independent-v1,controls,
inputs-v1,all final-v1 jobs,matrix-audit-v1,root-review-v1,progress-v1,jobs-v1,
checkpoint-seal-v1,post-seal-audit-v1. Final docs-only source2 adds2 guides
(1084 paths); verify seal/readback before edits. Never build during CTest in the
same directory; archive LastTest.log before another test/enumeration.

Next: sink-aware reconstruction. Current two-step restore retains all native
replay output before opening the sink, within configured row/byte/work/heap caps.
It rejects caller-frontier suppression/partial consumption as delivery authority.
Add a native factory which opens/validates the real sink in the same receiving
account before replay, compares acknowledged epoch bytes without writing new
tentative output, retains only missing output and exposes no owner/output until
whole WAL/native/source/EOF/stamp checks complete. Do not mint extra source/index/
heap allowances or skip corruption/binding checks.

Then integrate crash-safe retirement intent/continuation with the generation
lock and actual verified sink/checkpoint/root coverage. Keep old selected pairs
until that protocol is durable; never treat output consumption or options as a
receipt. Cover every unlink/sync/root/intent crash/error boundary, then whole256+
new/fresh-source O04–O06 acceptance. O08 CLI, A02 licensing and other Refactor
cards/release gates remain open. Local committed-file delivery does not prove
arbitrary external callback side effects.

## Predecessor O05 durable generation selection/rotation

This is the historical generation snapshot; next-work statements are superseded
by the local sink component above.


This goal turn is progress. Root implemented/reviewed the new selector and native
session hooks. Luna Max supplied a bounded helper inventory/read-only review and
independent212-byte golden; no Astra was used. Root handles routine/most work;
Astra Max stays occasional. All1057 predecessor source paths were verified and
preserved. See [generation API](generations.md) and
[evidence](verification/o05-generation-native-2026-11-10.md). O05 and full goal
remain active/in progress; ledger43 verified/3 in progress(A02/O05/O06)/32 not
started,78 total.

QuerySession::enable_generation/rotate_generation/restore_generation integrate a
fixed checksummed CROWNGR1 root, lifetime sentinel lock and account-funded owner.
Complete exclusive native checkpoint and fresh bound journal are synced before
root link/rename/directory fsync; no new-log input starts before root durability.
Completion after the root syscall is allocation-free. Recovery validates root
identity/checksum/stable metadata and selected checkpoint hash/bases before
native replay/tail repair. It returns paused, preserving native pending input,
partial windows, decoder/source/CSV state and bounded generation-tagged output.

Old selected pairs remain intact. Only next unselected candidates can be cleaned
under a validated current root/lock. No directory scan or temporary chooses an
active pair. Retained generations default32; copied cumulative root I/O/work and
existing native/file/account caps remain finite. Unknown selection blocks session
publication until drop/reopen. Relative paths require stable CWD and the same
trusted Linux namespace/fsync assumptions. No durable O06 acknowledgment or
committed-history retirement is claimed by rotation/output consumption.

Final native source1 selected66/66 PASS four modes: Debug 60.69s, Release 37.03s, Clang18 64.7s, ASan+UBSan/leaks 145.63s.
CTest registers253, retaining all250 predecessors. This is scoped66 acceptance,
not whole253/fresh acceptance.24 typed,32 stream and16 window/backend/pending
cases verify state/source/output identities and the next update; root every-cut/
bit-flip, checksum-valid malformed bindings and validation-before-repair pass.
All910 receiving allocation faults,222 applicable actual syscall errors and224
process exits pass. Two after-success injections on already-ENOENT unlink calls
are recorded separately; both crash sides of all112 actual boundaries pass.
Crashes verify actual native old/new recovery/next updates, not power loss.

Unchanged production-only controls exposed initial checkpoint load-policy shape
checks missing from enable (path/chunk/operations, all3 negative exit1). Preflight
now rejects before pair publication; same source positives exit0. Full1068-path
interim source and2 relevant objects/negative ELF are preserved. Initial compile
corrections and one invalid fault-test assumption are retained; no predecessor
test/fixture/cap/timeout changed. Accepted builds have zero diagnostics and strict
flags/assertions/leak checks remain enabled. Luna's bounded review found no
further actionable issue; root owns the implementation/acceptance judgment.

Audit pins204 executables,24 changed-unit objects,16 archives/four caches and440
flags/links plus public controls. All22 final matrix/control receipt jobs are
CLOSED; terminal stdout is archived. Prefix build/verification/
o05-generation-native- contains preimages-v1,interim-v1,negative-objects-v1,
independent-v1,controls,inputs-v1,all final-v1 jobs,matrix-audit-v1,root-review-v1,
progress-v1,jobs-v1,checkpoint-seal-v1,post-seal-audit-v1. Final docs-only source2
adds2 guides (1070 paths); verify its seal/readback before new edits. Never build
during CTest in the same directory; archive LastTest.log before later tests or
enumeration.

Next implement O06 durable local sink/outbox/acknowledgment/deduplication and
bounded backpressure/cancellation. Establish a durable delivery frontier/receipt
whose query/generation/physical coverage can authorize old-pair retirement only
after the new pair/root are durable. Do not treat in-process consumption/discard
or replay options as that receipt. Cover every retirement/persistence crash/error
boundary, then run full253+new/fresh-source integrated O04–O06 acceptance. O08 CLI,
A02 licensing and other Refactor cards/release gates remain open.

## Predecessor O05 native restore/replay

This is the historical replay snapshot; next-work statements are superseded by
the generation component above.


This goal turn is progress. Root implemented and reviewed the native factory;
Luna Max supplied bounded read-only inventory/review. No Astra was used. Root
handles most work; Astra Max remains occasional. All1053 predecessor paths are
preserved. See [native API](native-replay.md) and
[evidence](verification/o05-native-replay-2026-11-10.md). O05 stays in progress;
full goal remains active with43 verified/3 in progress(A02/O05/O06)/32 not started.

QuerySession::restore_journal binds the exact durable checkpoint/log pair,
reconstructs into one receiving account, stages native reader/queue input and
matches each actual prepared transition against its decision. Effects/output
stay private until full prefix/EOF/stamp/sync checks. It returns paused with the
writer attached. Complete pending input and active partial watermark commands
survive. Decoder bytes/records/header/CSV mapping/source positions precede unread
external continuation; optional original-source seek is explicit. Torn repair
follows native validation/seek; complete semantic corruption never truncates.

Committed replay output uses a bounded account-funded buffer and exact
query/generation/physical epoch/operation/typed-values identity excluding ordinal
and iteration order. Consume next_recovered_output or explicitly discard before
new admission. Output frontier is caller policy, not a persisted acknowledgment.
Status/statistics include the backlog. Work quotas are copied and cumulative;
native memory/failure/file categories and strict compiler settings are retained.

Final tested source1 selected63/63 PASS in all four modes: Debug 30.66s, Release 20.78s, Clang18 41.02s, ASan+UBSan/leaks 123.3s.
Normal CTest registers250, retaining all247 predecessors. This is scoped
component acceptance, not whole250/fresh acceptance. Native state/source/output
identity and subsequent update pass24 typed,80 stream,2 nullary quoted CSV and16
partial-window cases. Every470 input/decision byte cut,916 allocation faults,
98 actual syscall errors and98 process exits pass. Crashes reopen the actual
factory and verify state/source/output/pending input, not power loss.

Unchanged production public controls reproduce two initial gaps (negative ELF
exit1): known CSV start109 accepted instead of108, and1024-byte new source name
escaped work128. Final ELF exits0 for both. Precharged value/source/CSV work,
exact known text starts and schema/quoting first-header byte bounds close them.
All old tests/fixtures/caps/timeouts remain unchanged. Root corrected strict
compiler diagnostics; all accepted builds have zero diagnostics.

Audit pins196 ELFs,32 changed objects,16 archives/four caches and424 compiler/link
records plus public controls. Final four-mode/control receipt jobs are CLOSED;
terminal CTest stdout is archived. Receipt prefix is build/verification/
o05-native-replay- (preimages-v1,interim-v1,negative-objects-v1,public controls,
inputs-v1,final jobs,matrix-audit-v1,root-review-v1,progress-v1,jobs-v1,
checkpoint-seal-v1,post-seal-audit-v1). Debug final jobs use final-v1; other modes
v1. Earlier focused/failing build logs and the harmless Debug name collision are
preserved. Final docs-only source2 adds2 guides (1057 paths); verify its seal and
readback before new edits. Never build during CTest in the same directory;
archive LastTest.log before later tests/enumeration.

Next implement durable compatible checkpoint/generation selection/publication
before any committed-log retirement. Define authoritative durable root recovery
for old/new pairs and every publication/retirement boundary. Then implement O06
durable local output/outbox acknowledgment/deduplication/backpressure using the
semantic identity contract, integrated crash/failure boundaries and full/fresh
acceptance. First CSV raw header/source bytes are not authenticated by seeking;
the bound journal and documented native semantic checks remain authoritative.
O08 CLI, A02 licensing and other Refactor cards/release gates remain open.

## Predecessor O05 prepared session journal writer

This is the historical writer snapshot; its next-work statements are superseded
by the native recovery component above.


This goal turn is progress. Root implemented/reviewed production changes. Luna
Max supplied bounded inventory/stream fixtures/review/independent prefix bytes;
no Astra was used. All 1043 predecessor paths were verified and preserved. See
[writer contract](session-journal.md) and [evidence](verification/o05-session-journal-2026-11-10.md).
Full goal remains active: 43 verified / 3 in progress(A02/O05/O06) / 32 not started,
78 total. O05 has no production native reconstruction/replay factory yet.

QuerySession::enable_journal binds an exclusive new log to the complete exact
current durable checkpoint. Reader/queue input stays owned while the logical
input frame syncs before physical engine begin. A prepared physical or metadata
decision syncs before native publication/window/source acknowledgment/output.
Drain uses that barrier too. Decoder bytes/records/header/CSV permutation are
captured for a cached row. New fixed journal_state metadata reports the last
confirmed prefix; FileFailure forces recovery_required and blocks further
publication. Predecision allocation failure rolls back private work and can
retry the same input without duplicating the record. Checkpoint-file replacement
is blocked while attached; explicit drop releases the File lock/funded buffers.

Final tested source2 selected60/60 PASS all four modes: Debug 26.83s, Release 10.14s, Clang18 22.05s, ASan+UBSan/leaks 95.75s.
Normal CTest now247 names, retaining all244 predecessors. These are scoped
component regressions, not whole/fresh O05 acceptance. Native cases cover12
query/backend combinations,32 eight-format/backend/prior-record cases, both
window FIFO policies, paused drain, metadata/physical decisions, source counters,
allocation denial after decision fsync,48 actual before/after syscall errors and
16 actual process exits. Crashes prove writer prefixes/lock release, not native
restart or power loss. Accepted builds have zero compiler diagnostics and strict
flags/assertions/leak checks remain enabled.

Interim source1 passed60 in four modes, but unchanged production-only public
controls reproduced two uncovered bugs (both exit1): drop retained the lock and
nonfinal duplicate-label expiration metadata was rejected by the codec. Source2
passes both same controls (exit0). Partial metadata is now watermark-only, leaves
physical/command counters fixed and advances substep; insertion/withdrawal and
nonwindow invalid contexts still reject. Four duplicate-expiration backend/FIFO
cases and an independent1311-byte four-frame prefix/all1312 cuts pass. All seven
old golden frames are byte-identical. The old partial-metadata encoder negative
is now a strict stream-prefix negative, with unknown-kind rejection retained;
other old tests/caps/timeouts are unchanged. Independent fixture v1's16-byte
query-id error was caught by root; corrected v2 verifies32 ASCII bytes/header624.

Audit pins188 native executables,32 changed-unit objects,16 archives/four caches
and408 compiler/link records plus production public controls. All46 native jobs
are CLOSED; terminal stdout is archived. Receipt prefix:
build/verification/o05-session-journal- (preimages-v1,interim-v1,negative-objects-v1,
inputs-v1/v2,all v8/v10 jobs,public-control commands/negative/positive ELF/logs,
independent fixture v1/v2,matrix-audit-v1,root-review-v1,progress-v1,checkpoint-seal-v1,
post-seal-audit-v1). Final docs-only source3 adds two guides. Verify its final seal
before new edits. Never build during CTest in the same directory; archive
LastTest.log before later tests/enumeration.

Next implement a native restore/replay factory from the exact checkpoint and
validated prefix. Stage decoded native input into the owned reader/queue without
ordinary Row conversion/new allowance; prepare source nodes before commit. Restore
bytes/records/header/CSV mapping, checking any checkpoint-known permutation and
source limits, before reading the external post-replay continuation. Match each
actual prepared transition to decision kind/physical/command/substep/completion,
including metadata-only partial watermark steps. Keep uncommitted input/active
commands for later admission and expose no tentative recovery output. Define
recovered control/EOF behavior explicitly. Root-review-v1 records interface and
protocol constraints. Then durable checkpoint/generation selection/retirement,
audited stable output identity/O06, all integrated persistence boundaries and
whole/fresh acceptance. Root handles routine work; Astra Max stays occasional.

## Predecessor O05 durable journal file component

This is the historical file snapshot; its next-work statements are superseded
by the current writer component above.

This goal turn is progress. Root implemented/reviewed this cohort without any
sub-agent or Astra. All1035 predecessor source paths were verified/preserved.
See the [file contract](journal-files.md) and
[component record](verification/o05-journal-file-2026-11-10.md). O05 remains in
progress; ledger43 verified/3 in progress(A02/O05/O06)/32 not started,78 total.

File::create/open add exclusive advisory writer ownership, durable creation
without replacement, no-follow regular-file admission, streamed receiving-account
buffers and exact expected binding. Append validates the private cursor before
writing, loops short/EINTR writes and fsyncs before success. Post-validation
failures poison the owner; unknown may already contain a complete commit, so
close/reopen rather than retry. Open validates/syncs the surviving visible prefix.
Explicit repair removes only an incomplete later tail, preserving complete
pending input and every physical window substep. Checked Linux close never
retries. Local-filesystem/trusted-namespace/stable-name assumptions are explicit;
process exits do not simulate power loss.

Final tested source2 selected57/57 PASS in four modes: Debug 25.01s, Release 13.22s, Clang18 20.41s, ASan+UBSan/leaks 95.16s.
Normal CTest now244 names, retaining all241 predecessor names. This is component
regression acceptance, not whole/fresh O05 acceptance. All136 injected actual
syscall errors and136 process exits cover12 create/17 open/19 append/20 repair
boundaries. Byte cuts/flips, partial window repair, actual short-write failure,
uncertain complete commit, poison/reopen, exact/under memory/validation limits,
allocation faults, ownership/descriptor cleanup, interruption/zero-progress bounds
and temporary basename collision pass. Accepted builds have zero diagnostics;
strict flags/assertions/sanitizer/leak settings remain enabled.

Audit pins180 actual executables,16 changed-unit objects,16 archives/four caches
and392 compiler/link records. Native workflow jobs are CLOSED and terminal CTest
stdout is archived. Initial counter/helper compile corrections, interim source1
and the Release nonnull build failure are preserved; explicit syscall argument
checks pass in final source2 with unchanged flags. Receipt prefix is
build/verification/o05-journal-file-: preimages-v1,initial-v1,source-v1,
release-negative-v1,inputs-v1/v2,all v5/v6 job receipts,matrix-audit-v1,
root-review-v1,progress-v1,checkpoint-seal-v1 and post-seal-audit-v1.
Final docs-only source3 adds two guides; verify its seal before further edits.
Never build during CTest in the same directory; archive LastTest.log first.

Next integrate prepared native query commit and durable input/decision ordering,
then checkpoint reconstruction and deterministic physical/window replay. Restore
post-replay source/CSV counters and pending command continuation. Define durable
checkpoint/generation selection before retiring committed history, stable output
identity and O06 delivery, every integrated persistence boundary and whole/fresh
acceptance. File storage alone does not complete WAL recovery. Full Refactor.md
goal remains active. Root handles routine work; Astra Max stays occasional.

## Predecessor O05 maintained journal codec component

This is the historical codec snapshot; its next-work statements describe that
boundary and are superseded by the current file component above.

Previous and current goal turns are progress. Root verified/preserved all1020
O04 source paths before implementing `o05-journal-native-*`. Luna Max generated
independent fixtures and provided bounded read-only quota/lifetime review. No
Astra was used. See the [journal contract](journal.md) and
[component record](verification/o05-journal-native-2026-11-10.md). O05 remains
in_progress; O04 is verified on its predecessor full snapshot.

Maintained CROWNWAL/version1 lives in include/crown/recovery/journal.hpp and
src/recovery/journal.cpp, with a normal production-runtime test and seven
independent fixtures. Protected header/body checksums distinguish complete
corruption from torn tails. Physical events, all window commands, reader/source
metadata, input-bound commit markers and checkpoint markers preserve separate
physical/command/substep progress. Decoded rows/source/CSV fields own account
bytes; input_view borrows them without ordinary Row conversion and rejects
rvalue owners. Inspection/scanning allocate zero.

Opaque Cursor owns its copied limits/expected header and continuation; detached
Scanned reports cannot mint quota, and no constructor imports them. Copy is
deleted; moves invalidate source. Feed/tail failures preserve private state.
Both the source-name work-before-UTF8 flaw and public mutable-snapshot work-reset
flaw have preserved native negative ELF/source/logs and passing public controls.
Native memory errors retain their real categories; journal diagnostics are fixed.

Final tested source6 selected54/54 PASS all four modes:
Debug 23.33s, Release 3.87s, Clang18 18.85s,
ASan+UBSan/leaks 93.24s. Normal CTest registers241 names; these54 are the
component regression scope, including all53 predecessor names. Seven golden
frames total1955 bytes; every truncation/one-bit flip per byte,1804 window-prefix
cuts, whole/incremental parity, all seven encoder/five decoder allocation faults,
exact/one-under caps and decoded lifetime pass. No old test, assertion, fixture,
cap or timeout changed. Accepted native builds have zero compiler diagnostics.
Strict flags/assertions/leak settings and production-only linkage were checked.

Audit pins172 actual executables/four caches,12 changed-unit objects,16 archives
and376 compiler/link records. All 37 jobs and all current build/test/control/audit
handles are CLOSED; every terminal CTest stdout is archived. Receipt prefix:
`build/verification/o05-journal-native-` (jobs-v1, inputs-v1–v7, matrix-audit-v1,
root-review-v1, two negative-input/control families, positive-controls, progress-v1,
checkpoint-seal-v1, post-seal-audit-v1). Source6 pins1033 tested paths; final7 adds
the API guide and component record, with docs-only changes (1035 paths).
Verify final seal/readback before new edits; old negative/interim matrices are
preserved. Never build during CTest in the same directory; archive LastTest.log
before another run/enumeration and inspect actual live state on resume.

Next implement durable single-writer journal file I/O using the opaque cursor:
atomic durable initialization, append/commit ordering, checked sync/close,
bounded short/EINTR/error handling, torn-tail repair and explicit indeterminate
outcomes. Integrate the already nonallocating prepared query commit, reader
post-replay counters/CSV/source continuation and partial window commands. Do not
truncate/retire until a durable compatible checkpoint and generation root make
recovery unambiguous. Use audited stable output identity rather than unproved
row ordinals; cover self-join fan-out/drain and every persistence boundary, then
full/fresh acceptance. O06 delivery remains separate. The codec alone is not WAL.
Ledger43 verified/3 in progress(A02/O05/O06)/32 not started,78 total. Full Refactor.md
goal stays active. Routine work stays in root; Astra Max is used sparingly.

## Predecessor O04 full acceptance — verified

Previous and current goal turns are progress. Root completed
`o04-final-native-acceptance-*`; Luna Max supplied a bounded read-only requirement
inventory. No Astra was used. All 1019 predecessor source paths and the durable-file
seal were verified and preserved before the full matrix. Native implementation
and registered tests are unchanged from that predecessor; this cohort adds
supplemental public binding controls and full acceptance evidence. See the
[full record](verification/o04-native-acceptance-2026-11-10.md) and [API/format contract](checkpoints.md).

All **240/240 current registered tests PASS in all five configurations**:
GCC Debug 924.94s, GCC Release 168.54s,
Clang18 Debug 758.85s, ASan+UBSan/leaks 3649.70s,
fresh source-only Release 167.70s. All 227 predecessor names remain;
13 O04 names extend them. No predecessor test, assertion, cap or timeout was weakened.
The clean tree contains the accepted 1019 source paths, no copied cache/object/
library/executable, and built/tested independently in a new Release directory.

Eight explicit O04 artifact/acceptance requirements map to reviewed native code
and actual test names. Source/catalog/plan/arithmetic binding, pointer-free state,
checksums/compatibility, quiescent barriers, exact state/results/next updates,
safe corruption/truncation/version failures, repeated resource budgets and
durable publication/failure outcomes all pass. The 531-byte runtime and1067-byte
session fixtures are independently pinned. Detailed native/source/window/binary/
file case and allocation counts remain in the predecessor records below.

Five supplementary production-only controls independently alter embedded source
SHA or catalog version, preserve the physical hash, recompute both valid checksums
and require ImageFault::binding on four restore attempts per field. Each valid
baseline restores. All five modes pass, including sanitizer/leaks and the clean
source-only libraries. Their source, exact compiler/link commands, objects,
executables and raw logs are retained; no private runtime hook is used.

Audit binds **1010 full-build native executables plus five supplemental controls**,
130 project archives,1160 strict C++ flag records,1140 links and15 build metadata
files. CROWN C++ code has zero compiler diagnostics; actual strict C++23 warnings
as errors, enabled test checks and sanitizer/leak settings were verified. The
fresh upstream build reproduces exactly the accepted S05 clean build's two upb
C warnings and one recursive Make notice; no flag or suppression was changed.
The unchanged archive and complete warning lines have their own review receipt.

All 25 jobs and all current build/test/control/pin/audit handles are CLOSED.
Every terminal CTest stdout is archived. Receipt prefix is
`build/verification/o04-final-native-acceptance-`: inputs-v1, fresh-source-manifest-v1,
five binary-inventory-v1 files, requirement-audit-v1/v2, matrix-audit-v1,
upstream-warning-review-v1, progress-final-v1, checkpoint-seal-v1 and
post-seal-audit-v1. Final inputs-v2 add this verification guide and change only
documentation (1020 paths). Verify the final seal/readback before new edits;
historical progress-v1/v2/v3 and their live handles are superseded by final receipts.
Never build during CTest in the same directory; archive LastTest.log before later
tests/enumeration and check actual live state on resume.

The ledger is now **43 verified,2 in progress(A02/O06),33 not started;78 total**.
O04 is verified. Full Refactor.md and release gates remain open. Next implement
O05 ordered input WAL, explicit commit/barrier records and deterministic recovery,
including interruption of self-join fan-out/drain, truncation only after durable
checkpoints and explicit replay output/deduplication boundaries. O06 durable sinks
and delivery remain separate. The read-only preliminary interface inventory is
`build/verification/o05-recovery-interface-inventory-v1.json`; its nine facts include
the existing nonallocating prepared commit, private-until-commit public output,
stream decoder/source progress and window command/physical barriers. Recheck the
source hashes before implementation. Continue routine work in root; Astra Max is reserved
for unusually difficult problems. The complete thread goal remains active.

During the long sanitizer wait, root also built an isolated experimental
CRWNWL00/version0 codec/prefix validator under
`build/verification/o05-journal-prototype-v1`. Seven independent Python fixtures,
1955 truncations/byte flips and1804 prefix cuts per mode pass Debug/Release/Clang/
sanitizers. Rows/source/CSV fields own funded bytes; inspection/scanning allocate
zero. Both the unfunded inspector-allocator setup and complete-length-versus-torn-
tail flaws have preserved negative executables and passing after-controls. Header
and body checksums are separate. That prototype has its own seal/readback and
read-only review. It is excluded from the maintained source and240-test matrix;
it does not implement durable journal I/O or recovery, and O05 remains not_started.
Port only after rechecking the prototype/source hashes and implementing the full
O05 persistence, replay, window/source and output-identity protocol.

## Predecessor O04 atomic durable checkpoint files

Previous and current goal turns are progress. Root implemented
`o04-session-files-native-*`; Luna Max supplied a bounded local-manpage inventory
and read-only descriptor/lifetime review. No Astra was used. All 1011 predecessor
source paths were verified and preserved. See the [file record](verification/o04-session-files-native-2026-11-10.md)
and [API/outcome contract](checkpoints.md). O04 remains in_progress.

`QuerySession::checkpoint_file` holds its guard through native capture, encoding
and publication. The existing parent directory is anchored once. An exclusive
0600 random sibling is fully written, fsynced and checked on close, then renamed
over the final entry before parent fsync and checked close. A temporary basename
equal to the destination is skipped before creation. The final leaf is replaced
without following it. The parent must be trusted against external edits to the
writer's temporary names; this is the supported Linux local-filesystem contract.

`FileFailure` reports fixed fault/stage/errno, not_published/unknown/
published_unsynced/durable state and temporary_cleanup_failed. Rename errors are
conservatively unknown; errors after replacement never claim rollback. Mandatory
temporary cleanup has at most eight attempts outside ordinary I/O quota. Short
transfers, zero progress, interruptions, checked-close failures and operation
ceilings are handled explicitly. Process exits can leave private temporary files;
the named loader never chooses them automatically.

`restore_file` requires a regular no-follow file. It validates a fixed 316-byte
stack preamble before allocating one complete buffer in the receiving account;
decode and native reconstruction reuse that account and one indexed runtime
grant. Expected length/EOF and inode/size/mtime/ctime are checked. Full envelope
and nested runtime validation follows. File bytes never escape the synchronous
restore, and failed allocation/parse/I/O paths close their descriptors. Active
streams still require the next-unread-byte continuation and the caller supplies
the matching immutable CompiledProgram.

Final source7 selected **53/53 PASS in all four configurations**:
Debug 23.43s, Release 6.11s, Clang18 19.23s,
ASan+UBSan/leaks 92.81s. Production file tests cover 48 typed cases;
self-join allocation sweeps cover all 18/608 reference and 20/617 indexed
capture/restore requests. Exact/one-under receiving account caps, repeated saves,
source-closed CSV continuation, both window FIFOs/backends, corruption, truncation,
symlinks, special files and changing-file rejection pass. All previous 50 selected
regressions remain; predecessor fixtures/assertions/caps/timeouts were not weakened.

Each backend exercises before/after failures for all 26 publication and 25 read
syscalls, plus 52 process-exit publication boundaries. The parent compares exact
old/new epochs, state and subsequent deltas. Power-loss/hardware simulation is
not claimed; durability depends on successful local filesystem fsync guarantees.
An unchanged deterministic temporary-name-equals-destination control failed
before the guard and passes after it. Its ten pre-fix source paths, actual ELF
and raw negative/positive logs are preserved. Cleanup EACCES/persistent EINTR
controls verify bounded failure reporting and old-artifact retention.

The first Release build caught ignored mutation-test syscall results under
fortified warnings. Source7 checks those results and requires actual file
mutation; production code is unchanged from source6. Every accepted build has
zero compiler diagnostics, strict warnings/assertions and checked sanitizer/leak
settings. Audit pins 168 actual executables/four caches, 24 changed-unit objects,
16 archives and 368 compiler/link records. All 31 jobs and all current
build/test handles are CLOSED; every terminal CTest stdout is archived.

Receipt prefix is `build/verification/o04-session-files-native-`: jobs-v1,
matrix-audit-v1, namespace-negative-inputs-v1, namespace-negative-v1/positive-v1,
session-composition-review-v1, progress-v1, checkpoint-seal-v1 and
post-seal-audit-v1. Source7 pins 1018 tested paths; final8 adds the verification
guide and changes documentation only (1019 paths). Verify the final seal/readback
before starting new work. Never build during CTest in the same directory; archive
LastTest.log before later tests/enumeration. Check actual live state on resume.

Next run complete O04 full registered-suite and fresh-source acceptance before
changing its ledger status. Use the existing Refactor.md gates and strict flags;
the scoped 53-case matrix does not replace them. O05 WAL follows O04; O06 durable
delivery/replay identity remains separate. Ledger 42/3/33 and the full 78-card
goal remain active. Root should handle routine work; use Astra Max sparingly.

## Predecessor O04 complete binary session envelope

Previous and current goal turns are progress. Root completed
`o04-session-image-native-*`; Luna Max supplied the field inventory, independent
Python fixture and read-only review. No Astra was used. All1000 predecessor
source paths were verified and preserved. See the [binary session record](verification/o04-session-image-native-2026-11-10.md)
and [format/API contract](checkpoints.md). O04 remains in_progress.

`QuerySession::checkpoint_image` now writes complete CROWNSI1/version1 state,
including its CROWNRI1 runtime component, controls/source kind/EOF/failure,
input/snapshot/queue/workload policies, accepted positions, reader origin/CSV
mapping and window labels/count IDs/deadlines/progress. Full structural and both
checksum checks precede decoded allocation. Enum/optional/size/text/sequence and
metadata limits are preflighted. Native runtime admission still validates actual
program/catalog/arithmetic/policies, rows, window references and managed base
membership. A matching immutable CompiledProgram is required from the caller.

Capture holds the session guard throughout native capture and encoding. Restore
uses one receiving account; temporary native source/window data owns its bytes.
The runtime blob borrows caller bytes only during synchronous restore, avoiding
an extra64MiB copy. Runtime admission uses one indexed grant. Active streams need
a continuation at the next unread byte (including EOF); typed/stopped states
reject unused continuations. Source memory limits can be overridden explicitly.
Native in-memory checkpoint APIs remain available.

Source8 selected50/50 PASS: Debug22.95s, Release3.10s,
Clang1818.78s, ASan+UBSan/leaks97.51s. The two new
production/grant targets each cover48 typed,16 stream and16 window cases.
Self-join capture/restore sweeps all18/613 reference and20/622 indexed positions;
exact/one-under codec/restore limits, source-closed lifetime, CSV permutation,
all native window scalars, failed/busy/writer/window barriers and next updates
pass. All48 predecessor regressions are retained. No predecessor assertion,
fixture, cap or timeout was weakened.

The independent1067-byte struct/hashlib fixture has SHA256
03b891a90f0b0a96406d77361d19f431546656365e9cce69f601c476e58492b4.
Every truncation/bit flip and checksum-valid malformed fields reject before
allocation. An unchanged public-only production-library control detects the
encoder/inspector mismatch for caller-mutated progress before source8, then
rejects it after the fix. All22 pre-fix source paths and the negative ELF/log are
retained. Raw-scalar fixtures use native admission, preserving the text adapters'
UTF-8 contract. GDB pins the41-byte existing running session-busy diagnostic;
its corrected new test keeps stopped active-window zero-allocation rejection.
Capture-work words are descriptive metadata, never authority for a new grant.

Audit pins160 actual executables/four caches,56 changed-unit objects,16 archives
and352 compiler/link records. Accepted builds have zero compiler diagnostics;
strict warnings/assertions and sanitizer/leak settings were checked against actual
flags. All32 jobs and every build/test/audit handle are CLOSED. Every terminal
CTest stdout is archived. Never build during CTest in the same directory;
archive LastTest.log before later tests/enumeration. Verify live state on resume.

Receipt prefix is `build/verification/o04-session-image-native-`: jobs-v1,
matrix-audit-v1, encoder-negative-inputs-v1, encoder-negative-v1/positive-v1,
session-composition-review-v1, progress-v1, checkpoint-seal-v1 and
post-seal-audit-v1. Source8 pins1010 tested paths; final9 adds the verification
guide and changes documentation only (1011 paths).

Then-next work (now implemented above) was atomic durable file publication and bounded file loading using
this complete envelope. Retain the same receiving account when reading/decoding;
handle write/sync/rename/directory-sync failures with a documented publication
state. Exercise failure boundaries and retain the previous complete artifact.
Then run complete O04 full/fresh-source acceptance before changing its ledger
status. O05 WAL follows O04; O06 replay/delivery identity remains separate.
Ledger42/3/33 and the full78-card goal remain active and unchanged.

## Predecessor O04 native complete-session checkpoint composition

Root completed `o04-session-checkpoint-native-*` directly; no Astra or other
agent was used. The previous and current goal turns are progress. All996
predecessor source paths were verified and preserved before changes. See the
[native session record](verification/o04-session-checkpoint-native-2026-11-10.md)
and [checkpoint contract](checkpoints.md). O04 remains in_progress.

`QuerySession::checkpoint_state` and `restore_state` now compose the native
runtime/source/options/window owners under the session guard, one receiving
account and one indexed admission grant. They preserve control, input kind,
EOF/failure flags, snapshot/input/queue policies, workload configuration,
accepted positions, reader counter origin/CSV mapping and independent
source/window/physical sequences. Managed base rows must equal distinct window
counts; internally valid mismatched window state rejects, while unmanaged
initialized tables survive. No internal ordinary DTO graph is introduced.

Capture rejects queued/cached/failed active input, private work, unread output
and active window commands, including between physical commits. Stopping retains
an unfinished watermark tombstone: that terminal state still rejects capture
before allocation, preserving its committed physical/accepted prefixes. An
active stream restore needs a supplied continuation at the next unread byte;
a stopped stream needs none. Images survive original-session destruction.

An unchanged public-only production-library control exposed a saved reader
counter reset: it accepted sequence2 past configured records1. The preserved
pre-fix ELF/source/log demonstrate this. Restore now binds session reader records
to accepted sequence and rejects excessive distinct accepted positions before
receiving allocation. The unchanged control now rejects the same malformed state.

Tested source8 passes48/48 selected tests: GCC Debug22.90s,
Release3.09s, Clang18 Debug19.93s and
ASan+UBSan/leaks94.06s. Production and grant variants cover48
typed cases,16 stream profile/backend cases and16 window cases per variant.
All17/609 reference and19/618 indexed self-join capture/restore fault positions,
and26/306 reference or28/315 indexed window positions, pass. Exact/one-under
restore caps, source-closed lifetime, malformed metadata, wrong-thread/busy
barriers, initialized state and next-update behavior pass. Existing44 regressions
are retained. No old assertion, fixture, limit or timeout was weakened.

Audit pins152 actual executables/four caches,52 changed-unit objects,16 archives
and336 compiler/link records. Accepted builds have zero compiler diagnostics.
All43 jobs and all build/test/audit handles are CLOSED; every terminal
CTest stdout is archived. Never build while CTest runs in the same directory;
save LastTest.log before later tests/enumeration. Verify actual state on resume.

Receipt prefix is `build/verification/o04-session-checkpoint-native-`: jobs-v1,
matrix-audit-v1, session-composition-review-v1, progress-v1, checkpoint-seal-v1 and
post-seal-audit-v1. Source8 pins999 tested paths. Final9 adds this stage's
verification guide and changes documentation only (1000 paths).

Next encode a pointer-free complete session envelope around the native state,
with bounded validation, checksum and explicit format compatibility rules.
Then implement atomic durable file publication and persistence-failure handling,
and run complete O04 full/fresh-source acceptance. `SessionCheckpoint` is an
in-memory C++ object; only its runtime_image is already binary. O05 WAL follows
O04; O06 durable delivery/replay identity remains separate. Ledger42/3/33 and the
full78-card goal remain active and unchanged.

## Predecessor O04 source/window native state checkpoint

Root completed o04-session-state-native-* directly; no Astra was used. Previous
and current goal turns are progress. All991 predecessor sources were checked
without drift and copied to preimages-v1. See
[verification](verification/o04-session-state-native-2026-11-10.md) and
[component contract](checkpoints.md). O04 remains in_progress.

Native queue/reader/window checkpoint_state and receiving-account restore now
preserve accepted positions, all eight reader profiles/counters/CSV mapping/EOF,
queue closed/limit state, window labels/orphaned count IDs, FIFO/expiration
indices, watermark and independent sequences. Snapshots/imports use one original
or receiving account and native options/rows, with no internal ordinary DTO graph.
Queues must be empty; readers must have no unacknowledged cache; prepared or
active multi-step watermarks reject capture even between physical commits.

The predecessor runtime image restore ended one indexed admission grant before
live bootstrap. Preserved source3 fails the new direct fresh_operations==1
assertion. Source4's one outer grant passes the same assertion; source5 adds the
public zero-indexed-work failure and immediate restore-peak calibration. Indexed
restore now has389 persistent allocation positions (previous391); reference377
is unchanged. No old fixture/assertion/limit/timeout was weakened.

Source6 selected44/44 PASS GCC Debug22.44s, Release3.17s, Clang18 Debug18.31s,
ASan+UBSan/leaks93.20s. Source/window tests link the production runtime. All3–4/
12–15 reader and10/12 queue capture/restore faults pass;1025-source custom limits
preserve continuity. All6/30 window faults pass both backends/FIFO policies,
exact/one-under bytes, metadata limits, malformed state, retained lifetime,
repeated capture and next insert/expiration behavior. Existing ingest/CLI,
transport, session/window and storage/memory regressions remain intact.

Audit pins136 actual executables/four caches,64 changed-unit objects,16 core/
plan/runtime archives and304 compiler/link records. Accepted builds have zero
compiler diagnostics; strict flags/assertions and sanitizer/leak settings remain.
All20 jobs and every build/test/audit handle are CLOSED. Every terminal CTest
stdout is archived. Verify actual state on continuation. Never build during
CTest in one directory; save LastTest.log before later tests/enumeration.

Receipt prefix is build/verification/o04-session-state-native-: jobs-v1,
matrix-audit-v1, session-composition-review-v1, progress-v1, checkpoint-seal-v1,
post-seal-audit-v1. Source6 is tested995 paths; final7 adds the verification guide
and changes documentation only. Preserve all predecessors and raw failures.

Then-next work (now implemented above) was complete QuerySession native checkpoint/restore under Guard and
one receiving account/admission grant. Preserve control/EOF/failure/snapshot/input
policies and source kind. Cross-check accepted/runtime/window sequences and
managed base rows against window counts during native runtime admission.
Reader restore uses a supplied continuation at the next unread byte; retain its
original counter origin. Then encode the complete versioned session manifest
and publish atomically/durably. Full query/input/window/compatibility/corruption/
resource/fresh-source acceptance remains required. This is native component
progress, not a complete session checkpoint or durable file implementation.
Ledger42 verified/3 in progress(A02/O04/O06)/33 not started is unchanged; full78-card
goal remains active. O05 WAL follows O04; O06 replay/delivery identity is separate.

## Predecessor O04 native runtime checkpoint progress

Root completed the scoped native runtime component directly; no Astra was used.
A small Luna Max review hit the existing thread limit. The previous goal turn
was progress (verified/sealed S05); this turn implements new production code and
its native evidence. All984 predecessor sources were checked and preserved.
See [component contract](checkpoints.md) and
[verification](verification/o04-native-checkpoint-2026-11-10.md).

src/recovery/image.cpp and recovery/image.hpp implement CROWNRI1/version1,
separate from the experimental CRWNCP00 prototype. DeltaRuntime checkpoint_image
and restore_image capture under the original account and rebuild validated
source/support/derivation/index/live state under one receiving account at the
original sequence. Program/catalog/arithmetic/policy bindings and exact scalar
bytes are checked. Diagnostic history resets; receiving memory cap can differ.
This runtime component does not yet supply a session or durable file checkpoint.

Source6 selected37/37 PASS in GCC Debug121.89s, Release16.72s, Clang18 Debug98.17s,
ASan+UBSan/leaks529.80s. All20 backend/policy/build cases match exact state and
next-update delta sets; direct on-output cases sweep11/13 capture and377/391
restore faults, with exact/one-under receiving caps. The codec matches an
independent531-byte struct/hashlib fixture, every truncation/bit flip, resealed
malformed fields, extremal/wide binary values and all1/5 allocation positions.
Held images survive source closure and reconcile in actual memory reports.

The audited37-case scope uses27 actual targets per mode. Readback pins108
executables/four caches,28 changed-unit objects,12 core/runtime libraries and240
compiler/link records. A separate public-only control links actual production
runtime archives without the testing ABI: all four modes PASS both backends,
source-closed lifetime, state/sequence and next erase. Its first candidate's
ordinal0 expectation was corrected to the existing public ordinal1 contract;
raw failures/candidates remain. Initial Debug policy/calibration failures remain
with exact and persistent-failure assertions retained. No old limit/timeout or
assertion changed; sanitizer initialization_exceptions finished under its900s limit.

All20 jobs and all matrix/control/audit handles are CLOSED. Detailed terminal
CTest stdout is archived. Verify actual state on continuation. Never build while
CTest runs in the same directory; archive LastTest.log before later tests/enumeration.
Receipt prefix is build/verification/o04-native-checkpoint-: jobs-v1,
matrix-audit-v1, progress-v1, checkpoint-seal-v1 and post-seal-audit-v1.
Source6 is the tested990-path map; final7 adds the verification guide and changes
documentation only. Preserve all predecessor/experimental evidence.

## Predecessor O04 integration review

session-integration-review-v1.json pins10 actual source files. Restore must
construct QuerySession::Impl around the restored DeltaRuntime account. A barrier
needs no pending/output/readers and no active multi-step watermark: active window
commands can persist between physical commits. TypedQueue lacks accepted-progress
seeding; EventReader also owns cached input, bytes/records, CSV header/permutation
and framing. Serialize native accepted positions/options and window labels/counts/
expiration/FIFO indices, independent command/physical/watermark/last-label counters,
then validate agreement with managed base rows. Avoid internal ordinary DTO exports.

Add the complete versioned session manifest, bounded metadata and atomic durable
publication, then full corruption/compatibility/repeated-checkpoint acceptance and
fresh source matrix. Current tests compare exact delta sets; stable replay
ordering/identity is O05/O06 work. O04 remains in_progress. O05 WAL follows it;
O06 delivery is separate. Ledger42 verified/3 in progress(A02/O04/O06)/33 not
started is unchanged by this scoped milestone. The full78-card goal remains active.

## Predecessor S05 acceptance checkpoint — verified

Root completed `s05-final-native-acceptance-*` directly. No Astra was used;
reserve Astra Max for occasional difficult problems per the user's preference.
The native query memory contract and six S05 requirements are verified. See
[acceptance evidence](verification/s05-native-acceptance-2026-11-09.md) and the
[current contract](query_memory.md). Caller/compiler/export boundaries are explicit;
this does not claim a process-RSS cap or durable recovery/delivery.

Full227/227 PASS: GCC Debug911.41s, GCC Release155.78s, Clang18 Debug749.69s,
ASan+UBSan/leaks3703.93s and fresh source-only Release155.29s. Reused Debug/fresh
runs cover identical executable code: predecessor final7 differs from tested5
only in documentation. The long sanitizer planner sweep finished successfully;
handle3838 is CLOSED. It retained its original7200s sanitizer timeout and every
assertion/fixture. The earlier3600s status came from Debug's configuration; no
timeout was changed. Every terminal CTest stdout is archived.

Independent readback passed984 source paths,982 preserved preimages,950 actual
native executables/five caches,20 primary compiler/link records,334 fresh C++
objects,96 parser objects,27 libraries,436 fresh compiler/link records and2470
predecessor artifacts. Exact pre-existing dependency warnings/pins remain visible
in the predecessor evidence. No new internal unfunded path was found in the
account/caller dataflow review of32 source files; syntax searches are navigation
aids. Requirement-audit-v2 and readback-v1 record the actual acceptance checks.

All three current test jobs are CLOSED; no build/test/probe/readback handle is
live. Verify actual state on continuation. Never build while CTest runs in the
same directory; archive terminal LastTest.log before later CTest/enumeration.
Current receipt prefix is build/verification/s05-final-native-acceptance-;
jobs-v1.json, progress-v1.json, checkpoint-seal-v1.json and post-seal-audit-v1.json
bind final source/evidence. Source1 is the tested982-path baseline, draft2 adds
two guides, final3 changes documentation only. All predecessor evidence remains.

## Predecessor next dependency: O04 versioned checkpoints

R06/O02/S05 are verified. O04 is not_started: its isolated experimental codec is
groundwork under build/verification/o04-checkpoint-codec-prototype-v1, outside
production source and the tested source map. Candidate1's borrowed-view compiler
warning remains; candidate2 uses an explicit local view. Strict Release and
ASan+UBSan/leaks candidate2 probes PASS, with handles49705/18050 CLOSED.

The codec uses original-account binary rows, fixed plan/catalog/epoch binding,
version/arithmetic/endian identifiers, SHA256 and byte/work/count limits. Exact
scalar/NUL/raw-byte roundtrip, all9 encode/all7 decode allocation faults,
no-allocation early rejection and independent result lifetime pass. The format
is experimental CRWNCP00/version0; do not present it as a checkpoint API.

Next implement complete plan/options/source-position/window metadata, a genuine
session quiescent barrier, restore admission/rebuild and atomic file publication.
Verify same state/results and next-update behavior, malformed/version rejection,
failure rollback and repeated checkpoint resource budgets. O05 WAL depends on
O04; O06 durable sinks/delivery remains separate. No checkpoint card is verified
by the row codec alone. The full78-card implementation goal remains active.

## Predecessor S05 native invariant diagnostic checkpoint

Root completed scoped `s05-invariant-diagnostics-native-*` work directly. A small Luna Max
caller census was requested but spawn was rejected at the agent thread limit;
root completed the census. No Astra was used. Keep Astra Max use sparse.

Issue keys/arrays and actual independent Support/Physical/Delta expected-state
collections now use the original account (capture:15). Physical checks use a
native database and private native record rows; no ordinary full support snapshot
is created internally. Delta retains its independent top-down factor check and
observed-bucket regrouping. Work/issue semantics and wire version1 are preserved.

Production source1 builds cleanly. Source3 focused Debug PASS3/3 in13.20s, including
the original runtime localization test and operator report regression. All42 new
owner/backend/tree/scalar cases reconcile upstream requests to the original
account, sweep22–171 inspection allocation positions plus copy positions, and
check exact/one-under work/issue/query-byte caps, same-cap retry, retained lifetime
and nonallocating release. Rich keys include wide NUL strings, Boolean, date and
38-digit decimal values. Current memory and older reports survive failures.

A separately compiled predecessor probe uses frozen old headers and untouched
old Release archives. All210 current healthy/corrupt/zero-work/zero-issue/partial
reports match it byte for byte and validate against the unchanged schema. The
new invariant_wire case carries those independent reference digests in source.

Source5 (982 paths) full Debug PASS227/227 in911.41s; selected117/117 PASS Release
21.00s, Clang18 101.28s and ASan+UBSan/leaks567.85s across105 actual targets per
mode. Fresh source-only Release full227/227 PASS155.29s. The fresh build uses
exact982 pinned files without prior cache/objects:334 strict C++ objects,96
parser C objects,27 local libraries and436 native flag/link records are pinned.
The primary inventory pins505 executables/four caches; fresh inventory adds190
fresh binaries. Eight successful builds have zero project compiler diagnostics.
The fresh log's one Make scheduling and two upstream upb maybe-uninitialized
warnings match the exact pre-existing policy, including counts and archive pin.
They are preserved and are not asserted safe/fixed/false positives. Additional
dependency or any project warning remains an audit failure.

All976 predecessor paths were verified and preserved. Maps1–7, raw failures and
executed helper versions remain. Final7 changes documentation only from tested5.
Draft6/closer1's broad compiler-warning claim failed; closer2 uses the exact
already documented dependency diagnostic policy with a separate pinned receipt.
All27 jobs are CLOSED. Every terminal CTest stdout is saved. No build/test or
binary-inventory handle remains. Before continuing inspect actual jobs/handles; never
build during CTest in the same directory. See
[verification](verification/s05-invariant-diagnostics-native-2026-11-09.md) and
[native contract](invariant_memory.md). Job state is
build/verification/s05-invariant-diagnostics-native-{jobs-v1,progress-v1,
checkpoint-seal-v1,post-seal-audit-v1}.json. Independent readback binds sources,
preimages, old/current packets, executables, objects/libraries, flags and links.

The bounded runtime-disposition-review-v1.json classifies62 syntax matches and
confirms owner statistics routes through native capture. Existing caller state
exports, standalone legacy statistics and exception presentation are boundaries;
this is not an exhaustive compiler/I/O ownership proof. Existing tests, schemas
and tools are unchanged. Next: finish compiler/I/O ownership/work-path review,
then full Clang/sanitizer registration. Fresh Release full227 is verified for
source5; preserve that scope rather than presenting it as proof of later code.
S05 and the full78-card goal remain active; ledger41/3/34 is unchanged.

## Predecessor S05 operator memory reconciliation checkpoint

Root completed the scoped `s05-operator-memory-native-*` work directly.
One small Luna Max task supplied a read-only census/review; no Astra was used.
Use Astra Max sparingly, per the user's latest preference.

Native reports now reconcile actual Support/Physical/Delta/Session operator
records with actual allocation owners, table/index storage and arena lifetimes.
The report and scratch use the original query account under capture:14; scratch
closes before the captured account instant. Owner/purpose/lifetime totals and
table/arena joins are checked. Pending/released states omit committed counts.
The Delta coordinator's actual tag is UINT64_MAX, separate from factor0. A single
old delta-memory summation adapter includes that tag without changing assertions.
The new version1 schema and runtime/session `--format memory-json` CLI are explicit
caller exports; max-bytes caps final output before publication, not JSON scratch.

Source7 (973 paths) Debug focused PASS4/4 in1.52s: actual report/schema/CLI plus
delta_memory. Both backends, four owner kinds, three shapes, every persistent
allocation fault, exact/one-under logical/query caps, no-allocation release,
held snapshots, pending/stopped/dropped states, retained/free slots, 20 churn
cycles, wide NUL strings, composite buckets, SQL plans and corrupted live degrees
pass. Source8 adds documentation only (976 paths). Full Debug PASS225/225 in
917.93s; selected115/115 PASS Release18.66s and Clang18 99.41s. The selected set
uses104 actual native targets per mode; full Debug names189 native executables.
ASan+UBSan/leaks PASS115/115 in544.62s. All nine successful builds have zero
diagnostics. Actual strict flags/assertions/instrumentation and native links are
pinned in20 generated compiler/link records.

All964 predecessor sources were verified;965 preimages include the old handoff.
Maps1–9 and all raw failures remain. Detailed stdout for Debug CTest1–5 and each
Release/Clang/sanitizer run has been saved before further enumeration. All24 jobs
are CLOSED; no build/test or executable-inventory job remains. Final source9
changes documentation only from tested8 (976 paths). The executable inventory
pins501 native binaries and four caches. See
[verification scope](verification/s05-operator-memory-native-2026-11-09.md) and
[public contract](memory_reports.md). Job state is in
build/verification/s05-operator-memory-native-{jobs-v1,progress-v1,
checkpoint-seal-v1,post-seal-audit-v1}.json. The seal/readback bind inputs,
preimages, receipts, actual executable bytes, generated flags and document links.

The exact old-test adapter audit passes. Next: fund the remaining invariant
diagnostic graphs without weakening invariants or changing limit/error behavior.
Root's remaining-diagnostics-review-v1.json identifies ordinary expected-state
maps/sets/rows in Support/Physical/Delta inspect/check_invariants and owning
InspectionContext issue storage. Funding those paths and full native/fresh-source
acceptance still keep S05 open. Ledger41/3/34 and the full78-card goal remain active.

## Predecessor S05 native ranking/selection ownership checkpoint

Root completed the scoped `s05-ranking-selection-native-*` ownership work. No
Astra was used. Small Luna Max subtasks supplied compiler/caller census, explicit
caller exports and exact old-test adapters; root handled production, new tests,
review and verification. Use Astra Max sparingly, per the user's preference.
Full Refactor.md remains ACTIVE; ledger41 verified/3 in progress/34 not started.

C02 score/result controls, all text/arrays and modeled native programs now use
the original query account (capture:11). C05 captured Source/Request text,
assessments/decisions, key/cache nodes and Selection use capture:12; CurrentSelection
uses capture:13. Binding/census/order/canonical/compiler scratch is funded too.
Native lowering reuses checked validation and admitted source/identity fields;
it retains the canonical source owner, avoiding chains of old physical graphs.
Deep native admission copies complete source/token graphs into a receiving query,
allowing the original source to close independently. Cache FIFO nodes retain
allocation accounts; publication, iterative clear and final release allocate
nothing. Caller immutable compiler/proof/family/cache aliases remain boundaries.
Public native runtime/session factories retain one query account and one indexed
operation grant across program admission, initialization and live bootstrap.
Compiler metadata counters and logical lowering limits are distinct from execution
update caps. Pure initial DirectCQ compilation precedes execution admission.

Source22 full Debug PASS221/221 in876.17s; selected111/111 across103 native targets
PASS Release22.06s, Clang18 104.41s, ASan+UBSan/leaks570.61s. Final review added an
empty-native-input reproducer in source23, preserving its failure. Source24 adds
two preconditions before standalone account creation/current or as-of capture.
Valid paths add no allocation or logical charge. Final17-case selection regressions
PASS each: Debug56.58s, Release6.44s, Clang42.44s, sanitizer193.39s. These supplement
the broad source22 runs; do not call the broad runs reruns on24. The new admission
alias gives222 registered cases and112 selected names using the same103 targets.
Final source25 changes documentation only from24 and freezes964 paths.

Actual tests reconcile all new requests to the original account on both backends.
Ranking persistent positions30–699 and selection322/396/805/853 reference versus
328/401/813/861 indexed, all source/owner kinds and cache modes, exact/one-under
caps, same-cap release/retry, old-result lifetime/controller-only release and
pending/stopped/dropped boundaries pass. A calibrated admission-only work grant
proves initialization cannot refill it. Full old/new physical JSON, SQL DISTINCT/
EXISTS, rich scalars, work/hash/token aliases and30 no-history replacements pass.
Fourteen old test files have exact native type/allocator/caller-export or identical
in-place integer-construction adapters. Frozen encoders, schemas/tools, limits,
timeouts and assertions are intact. All accepted builds have zero diagnostics.

All60 recorded jobs are CLOSED. No test/build or binary-inventory handle remains.
Detailed terminal CTest stdout was saved before later runs/enumeration. Historical
binary inventoryv1 pins412 source22 executables; finalv2 pins412 current executables
and four caches. Inventoryv2 describes broad runs;v3 records final registration.
Input maps1–25,957 preimages, all raw failures, executed failed helpers, new failed
fixtures/reproducers and audit receipts remain preserved. foundation-progress-v1/v2
are historical focused milestones; final progress/seal/readback supersede them.

See [verification scope](verification/s05-ranking-selection-native-2026-11-09.md)
and build/verification/s05-ranking-selection-native-{jobs-v1,progress-v1,
checkpoint-seal-v1,post-seal-audit-v1}.json. Before starting new work, inspect actual
jobs/handles/logs. Do not build during CTest in the same directory, and preserve
terminal LastTest.log before another run/enumeration. Keep all predecessor artifacts.

Next: authentic operator record/byte reconciliation, remaining diagnostic/work
path disposition and full native/fresh-source acceptance. A02/S05/O06 remain in
progress; S05 whole-query memory acceptance and full native acceptance are FALSE.
Do not mark the full78-card goal complete or paused at this checkpoint.

## Predecessor S05 native runtime ranking evidence checkpoint

Root implements `s05-ranking-evidence-native-*`; no Astra is used. The existing
Luna Max agent supplied a read-only ownership/caller census. Root handles most
work; the user's latest preference is to use Astra Max only sparingly for
especially difficult problems. Runtime ranking
evidence now charges both binding encodings, decimal formatting, retained
binding/weight/source/observation arrays, census/selection scratch and evidence
shared controls to the original query account (capture:9/10). Internally generated
source selections use a fixed array and a synchronous borrowed request view.
Existing caller request APIs delegate to the same capture implementation.

Production source1 compiles without diagnostics and all8 original focused
ranking/selection/capture tests pass. Source3 adds the actual memory test and
registration: PASS1/1 in0.47s, both backends, physical/delta/session owners and all
live/pending/stopped/dropped session phases, collection/source options, frozen v2
binding bytes, exact/one-under query caps, retained lifetime/controller-only release
and every persistent allocation position. A new fixture initially passed invalid
UTF-8 into the compiler's JSON plan identity; source3 preserves that raw-byte
encoder case and uses compiler-admissible UTF-8/NUL metadata in the native-plan
fixture. Production source1 is unchanged. Raw failure, candidate and source maps
are preserved. A target-registration build attempt is also retained.

Tested source3 freezes955 paths. Final source4 changes documentation only (956).
Full Debug PASS218/218 in914.60s. Selected105/105 cases across97 native
targets PASS each: Release100.57s, Clang18 583.38s and
ASan+UBSan/leaks3408.06s. All seven accepted builds have zero compiler
diagnostics. Detailed terminal test stdout is preserved before any further CTest
run/enumeration. All19 recorded jobs/handles are CLOSED. Progress-v2 binds source,
raw receipts, actual executables and handoff; progress-v1 is historical. Inspect
`build/verification/s05-ranking-evidence-native-jobs-v1.json` before new work.
These are scoped incremental results; full native/fresh-source acceptance remains
open. See [ranking evidence checks](verification/s05-ranking-evidence-native-2026-11-09.md).

Ranking score/result/selection graphs, authentic operator record/byte
reconciliation and full native/fresh-source acceptance remain open. This is
incremental work toward S05, not whole-query acceptance. Ledger41/3/34 and the
full78-card goal remain ACTIVE. Preserve all predecessor evidence and sealed maps.

## Predecessor S05 native retained report graph checkpoint

Root implements `s05-report-capture-native-*`; one Luna Max agent performed
read-only caller/remaining-owner census. No Astra used. Previous goal turn was
verified progress. CapturedObservationTrace/trace arrays, CapturedStateGauges
node/base arrays and CombinedCapture/ModeDescriptor/PlanExplanation/
StatisticsExplanation real object/shared controls now use the original query
account (capture:3/4/5/6/7/8). SessionStatisticsContext already uses capture:0 and
now retains native trace/combined children. Runtime wrappers propagate native
captures directly; no ordinary trace/gauge export mirror sits in the retained
query/report path. Existing public ObservationTrace/CommittedStateGauges exports
remain caller DTOs. Compile-only PhysicalPlan reports use an explicit standalone
component account; admitted CompiledProgram reports keep their existing grant.

Production source1 is unchanged through source3. Source2 adds/registers the new
actual memory test; source3 fixes only its loop formatting under unchanged strict
warnings-as-errors. Tested source3 freezes953 paths; final source4 changes documentation only (954). All11 original focused observation/
trace/gauge/combined/report/session/owner checks PASS source1 in7.66s. New actual
report memory test PASS source3 in0.72s, both backends:7 runtime capture families
and all12 live/pending/stopped/dropped session report/context families, exact real
request reconciliation, original-account retained controls/arrays, no-allocation
shared handle copies, native value copies, retained lifetime/controller-only final
release, exact/one-under query caps after hoarding genuine snapshots, same-cap
retry after release and every persistent allocation position. Native trace/gauge
cross-query assignments adopt source allocation and preserve old metadata/arrays
on failure. Gauge JSON matches the independent caller DTO export.

Runtime persistent fault counts: mode1, trace1, gauges2, compile-only native plan2,
combined59/61, plan5, statistics63/65 (reference/indexed). Runtime fixture peaks
440414..750049 reference /448151..757276 indexed and session statistics peaks
579842..828943 /586251..836655 bytes are Debug fixture values, not universal
bounds. Dropped-session cap tests retain83/84 genuine reports before the next
frontier. One old helper has2 exact type/export-range boundary substitutions;
all other bytes/reference assertions/models are preserved. Raw new-test formatting
failure/candidate/source2 are retained. No warning, flag, timeout, schema, frozen
verifier, test assertion or existing export interface is weakened.

Source3 full Debug build4 and CTest3 PASS217/217 in907.06s. Selected81
cases across73 native executables PASS each: Release16.10s,
Clang18 97.42s and ASan+UBSan/leaks530.04s. Accepted builds
have zero compiler diagnostics. Complete detailed stdout is preserved without
registration overlap. All recorded jobs/handles are CLOSED; inspect jobs-v1
before new work. Historical progress-v1 is not live authority. Selection-v2
includes query_explain/explain_cli; selection-v1 was never used for the broad
build/run scope. Progress-v2 binds source/raw receipts/binaries/scope/handoff.
These are incremental scoped results; full native/fresh-source acceptance stays
open. See [retained report evidence](verification/s05-report-capture-native-2026-11-09.md).

Next: runtime ranking evidence controls/binding/weight/source storage and runtime
selection/result graphs; audit remaining diagnostic/work paths and complete
authentic operator record/byte reconciliation
and complete overflow/no-op/churn/compiler/sanitizer/fresh-source native matrices.
Caller request/trace/gauge/table/text exports and supplied immutable evidence/
benchmark aliases are explicit boundaries. Fixed cursor/configuration/summary
values remain fixed or funded aliases. Ledger41/3/34 and full78-card goal stay
ACTIVE; S05/whole-query/full native acceptance remain FALSE. Preserve predecessor
maps/preimages/raw receipts/frozen verifiers/executed helpers.

## Predecessor S05 native owner capture checkpoint

Root implemented `s05-owner-capture-native-*`; one Luna Max agent performed a
read-only caller/remaining-owner census. No Astra was used. Root handles most
work; reserve Astra Max for difficult problems where another review adds value.
Production source2 corrects only the explicit allocator construction from source1.
Source3–7 change the new test/registration and one indexed helper adapter only.
Tested source7 freezes951 paths; final source8 changes documentation only (952).
Progress-v2 binds sources, raw attempts, native executables, scope and handoff.

Actual OwnerCapture component/field/histogram/top-K arrays and compact heavy-key
rows now consume the original CompiledProgram account under capture:2. Group
nodes and weighted builder object/control use the same grant. Native projection
gathers directly into one AccountedRow block, including binary strings and inline
38-digit decimals. Deep copies keep the source account; transactional cross-query
assignment preserves old destination stamp/facts/account on any denial. Native
CapturedSelection/Distribution/Key read interfaces retain no ordinary Row/string
mirror. Plan/layout values share funded metadata. Caller requests and standalone
table Capture/Distribution values remain explicit DTO boundaries. JSON/scalar
encoding and scope/freshness/distribution semantics stay intact.

Source7 full Debug build8 and CTest5 PASS216/216 in908.13s. Selected78
cases across70 native executables PASS each: Release16.26s,
Clang18 98.65s and ASan+UBSan/leaks540.16s. Accepted builds
have zero compiler diagnostics; complete detailed stdout is preserved without
registration overlap. All recorded jobs/handles are CLOSED. Inspect jobs-v1
before starting new work; historical progress-v1 is not live authority. These
incremental scopes do not establish full native/fresh-source acceptance.

All11 original focused checks PASS source2 in7.69s. Actual new owner memory and
registered indexed owner/session tests PASS source7 3/3 in1.31s. Actual upstream/
account request equality, nested retained block totals, caller field independence,
all5 scalars/binary bytes/38-digit decimals, exact/one-under query caps, same-cap
retry after releasing a held capture, deep/cross-query copy, retained lifetime/
controller-only release and persistent failures pass both backends. Debug fixture
capture peaks6757073/6776116 and copy peaks6750074/6768687 bytes (reference/indexed)
are measurements, not universal bounds. Persistent capture90/92 and cross-query
copy49/49 positions preserve both queries. Component logical limits remain
separate from actual native requests and held/transient overlap under the cap.

Pending capture retains no component graph. Reference metadata reads allocate
nothing; indexed reads acquire the existing work grant's2 native lease/allowance
object/control requests. Both denial points preserve pending/accepted state.
Rollback and final cleanup allocate nothing. Preserve raw allocator-constructor
compile failure, new-harness private-accessor/wrong-options failures and pending-
allocation assumption failures/GDB trace. Corrections stayed in the new harness;
production did not change after source2. Three old helper files have9 exact type/
range boundary substitutions; whole-file reconstruction preserves every other
byte/model/assertion. No compiler flag/limit/timeout/schema/frozen verifier changed.
Root corrected Luna's registration claim against CMake's foreach loop and explicitly
selected the registered indexed owner/session cases. See
[owner-capture evidence](verification/s05-owner-capture-native-2026-11-09.md).

Next: CombinedCapture control, retained ObservationTrace/session/report/evidence
graphs. Cursor/configuration/summary values are fixed data or funded aliases;
standalone capture/serialized values remain explicit caller exports. Authentic
operator record/byte reconciliation, async/diagnostic/invariant scratch and full
overflow/no-op/churn/compiler/sanitizer/fresh-source native matrices remain.
Ledger41/3/34 and full78-card goal remain ACTIVE; S05/whole-query/full native
acceptance remain FALSE. Preserve predecessor maps/preimages/raw receipts/frozen
verifiers/executed helpers.

## Predecessor S05 native instrumentation ownership checkpoint

Root implemented `s05-instrumentation-native-*`; one Luna Max agent performed a
read-only caller and remaining-owner census. No Astra was used. Root handles most
work; reserve Astra Max for difficult problems where another review adds value.
Production source1 remains unchanged through tested source4 (948 paths).
Final source5 changes documentation only (949 paths). Progress-v2 binds source,
raw receipts, actual native executables, scope audit and this handoff.

Actual ObservationState shared control/object/trace capacity, workload State/
Collector retained/configure descriptor/route/cell arrays and immutable workload
Snapshot controls/numeric arrays now consume the original query grant. Runtime
construction passes StorageWorkContext's existing account. Physical/delta/session
wrappers share the one Support-owned observer. observation:0/1 and capture:1
attribution preserves existing session:0 identities. Private standalone Collector/
State adapters alone create an explicit component account.

Source4 full Debug build5 and CTest4 PASS215/215 in896.08s.
Selected75 cases across67 native executables PASS each: Release16.20s,
Clang18 92.94s and ASan+UBSan/leaks528.50s. Accepted builds
have zero compiler diagnostics. Complete detailed stdout is preserved without
overlapping registration enumeration. All recorded jobs/handles are CLOSED;
inspect jobs-v1 before starting new work. Progress-v1 is historical. These are
scoped results; full native compiler/sanitizer/fresh-source acceptance stays open.

All8 unchanged collector/workload/observation/session/report checks passed source1
in3.83s. New actual instrumentation_memory passes both backends, reconciling
upstream requests with original-account successes: observer0/1/2 blocks by mode,
5 retained working arrays,4 blocks per immutable capture and8 allocations for
public pending-session capture/copy (4 remain retained). Exact/one-under query
caps, persistent2/6/4/8 observer/configure/capture/pending failure positions,
same-grant retry, nonallocating hooks/commit/reset/drop, old settings/history/
accepted progress and retained lifetime/controller-only final release pass.
Debug trace requests658710/peak659326 bytes; reconfigure peaks8418950/8437811,
capture7302576/7321437 and pending7316729/7335517 (reference/indexed) are fixture
measurements, not universal limits. Public numeric spans/stamps/availability and
component payload-memory semantics remain intact. Allocator framing and capture/
configuration overlap are additional real query-account requests.

Preserve the raw new-test private-helper compile failure and symmetric12-alias
canonicalization work-limit failure. Only the new harness was corrected: it uses
public pending capture and12 distinct source tables. No compiler limit, flag,
timeout, old test/assertion, frozen verifier or schema changed. MemoryAccount
still calls global operator new, so existing injectors cover native requests.
See [instrumentation evidence](verification/s05-instrumentation-native-2026-11-09.md).

Next: OwnerCapture components/selections/distributions/heavy rows and scan scratch,
then retained ObservationTrace, CombinedCapture/session/report/evidence graphs.
Cursor/configuration/summary values are fixed data or funded aliases. Async/
diagnostic/invariant scratch, authentic operator record/byte reconciliation and
complete overflow/no-op/churn/compiler/sanitizer/fresh-source native matrices
remain. Ledger41/3/34 and full78-card goal remain ACTIVE; S05/whole-query/full
native acceptance remain FALSE. Preserve predecessor maps/preimages/raw receipts/
frozen verifiers/executed helpers.

## Predecessor S05 native streaming input ownership checkpoint

Root implemented `s05-stream-input-*`; one Luna Max agent did read-only census.
No Astra was used. Continue with root for most work and reserve Astra Max
sparingly. Previous goal turn was progress. Native source8 freezes946 paths; library production is unchanged from source7.
Source9 changes only the CLI accepted-progress DTO export. Final source10 changes documentation only,
for947 paths. Progress-v2 binds source, raw receipts, binaries, scope and handoff.

Actual EventReader control/options/fingerprint/framing/native JSON/binary/
delimited decoding/cached compact rows/source text/progress use the original
CompiledProgram account. AccountedInputOptions shares native immutable control/
map/key/source/null storage with SessionRunContext. No ordinary operational
Row/JSON DOM/string/progress mirror or replacement grant is retained. Native
fixed digest/decimal parsing and admitted-catalog lookup avoid ordinary scratch.
Standalone CatalogSource construction remains an explicit external/compiler
adapter account; actual query sessions derive both catalog and original grant
from the admitted program. Public DTO codecs remain independent references.

Both reader and replay expose stable InputEventView values; native physical/delta
apply_view imports pending ownership before returning. Source nodes prepare before
engine work. Ack/commit/close/stop allocate nothing, and stream/typed stopped
progress stays native. Progress value copies fund original-account controls/nodes/
keys; immutable option copies share storage without allocation. Retained progress/
options survive reader/runtime destruction. Parser/order/OOM remains sticky with
explicit source recreation; engine rejection retains the same cached input.
Malformed native JSON syntax has stable invalid_document text; other schema/
domain/binding/option/limit/source codes and order keep their contracts.

Source8 Debug build6 PASSES every target. Its CTest4 had213/214 with one CLI
object/array mismatch; source9 fixes only that explicit DTO export. Source9 final
Debug CTest5 PASSES214/214 in892.96s. All40 native source8 checks PASS
Release16.31s, Clang1899.21s and sanitizers550.31s.
All16 source9 CLI checks PASS each mode: Debug49.73s,
Release8.26s, Clang36.41s, sanitizers199.29s. Accepted strict
builds have zero compiler diagnostics; complete detailed stdout is preserved
without registration overlap. All39 recorded jobs/handles are
CLOSED; inspect jobs-v1 before new work. Earlier snapshots are historical.
Full compiler/sanitizer/fresh-source/native acceptance remains separately open.

Actual memory tests cover both backends/all8 formats, five scalars/38-digit/
binary/UTF-8/source/null/relation text, original-account request reconciliation,
exact/one-under query caps, smaller same-sequence recreation, persistent ctor/
peek failures, nonallocating publication/close/stop, retained options/progress and
controller-only final release. Debug JSONL peak817523/817887 and binary
423971/424335 bytes are fixture values, not universal bounds. Full8-format peaks
and10–14 constructor/13–38 peek faults per backend are in progress/evidence.
Nineteen directed JSON cases/backend and an independent12007-case native/public
JSON differential pass:308 accepted/11699 rejected, zero code/value differences
and no native storage drift. This is not a proof of every possible document.

Five old tests have8 exact boundary adapters; all other bytes/assertions/reference
algorithms are preserved. Keep raw compile/type failures, actual unaccounted
catalog-revalidation failure, all preimages and the preserved old reader. The
source move followed complete replacement syntax acceptance, resolving automatic
review's intermediate-removal concern. No flags/timeouts/frozen verifiers/schema/
old source map/raw receipt/executed helper changes. See
[stream-input evidence](verification/s05-stream-input-2026-11-09.md).

Next: fund operational ObservationState control/trace capacity and workload State/
Collector route/descriptor/cell/configure arrays. Retained cursor/configuration/
summary values are fixed data or funded aliases; do not count them as remaining
owning strings. Capture shell is funded; nested retained trace/combined/owner/
workload/report/evidence payloads and diagnostic/async graphs remain open. The
focused next-owner census is not exhaustive. Continue authentic record/byte
reconciliation, complete overflow/no-op/churn/native matrices and all other cards.
Ledger41/3/34 and full78-card goal remain ACTIVE; S05/whole-query acceptance FALSE.
Preserve all predecessor maps/preimages/raw receipts/frozen checkers/helpers.

## Predecessor S05 native typed input ownership checkpoint

Root implemented `s05-typed-input-*`; one existing Luna Max agent completed a
read-only caller/test census. No Astra was used. Continue with root for most
work and reserve Astra Max sparingly. Previous goal turn was verified progress.
Tested source5 freezes 938 paths; final source6 changes documentation only, for
939 paths. Progress-v2 binds sources, raw receipts, binaries, scope audit and handoff.

Actual typed query queue/batch/item/compact row/source text and prepared/accepted/
stopped progress now use the original CompiledProgram account. A crown_plan
bridge supplies both account and catalog authority; core has no back-link.
Known real-request preflight precedes copying, complete private import reconciles
actual bytes, and caller DTOs empty only after publication. Full/OOM preserves
the offered batch and previous queue state. Native item views stay stable through
pending work/whole watermark expansion. Permanent row errors are deferred until
head validation without retaining unusable ordinary Rows or changing diagnostics.
Queue bytes now mean actual retained batch/item/row/source requests, with fixed
queue/progress/catalog and source preparation additional under the same grant.

InputPositions/AccountedInputProgress funds real controls/nodes/key bytes under
session:2. Copies are value snapshots with strong exception-safe assignment;
moves/ack/close/stop allocate nothing. Typed stopped progress remains native and
survives facade closure. Session hot checks avoid DTO export; public progress/
snapshots explicitly export caller values. Destruction detaches chains iteratively.

Full Debug build5 PASSES every target; full Debug CTest3 PASSES 213/213 in
906.32s. All 37 selected checks PASS GCC Release 16.40s,
Clang18 99.88s and ASan+UBSan/leaks 528.05s. Accepted strict
builds have zero compiler diagnostics. Complete detailed stdout is preserved,
with no CTest/registration enumeration overlap. Full native/fresh-source/compiler/
sanitizer acceptance remains separately open. All 20 recorded jobs/
handles are CLOSED; inspect jobs-v1 before new work. Earlier progress/active-check
records are immutable historical snapshots.

Actual memory test proves constructor/admission/peek/progress-copy allocation
equality, five scalars/38-digit decimals/binary/source text, exact actual batch
bytes, full denial with zero allocation, exact/one-under component/query caps,
caller preservation and retry, retained progress, nonallocating barriers and
10/2/3 persistent admission/peek/copy faults per backend. Reference late errors
cover malformed scalar, type/decimal, envelope and column precedence. Debug
fixture bytes118803 and peaks146695 reference/147059 indexed are fixture values.
Three existing tests have only six view type-name substitutions; exact whole-file
audit preserves all other bytes/assertions/independent DTO models. Retain the raw
initial formatting failure and its preimage. No warning or semantic rule weakened.

Streaming reader/control/options/fingerprint/wire/lexer/parser/delimited/cached
rows/progress still require native funding. The session footer distinguishes that
stream dependency from native typed progress; do not claim reader completion.
Run-context input options, retained observation/cursor/workload, capture/report/
diagnostic/async graphs and authentic operator record/byte reconciliation remain.
The 9-file 248-candidate inventory is not exhaustive;
it distinguishes funded aliases/caller/compiler DTOs from internal ownership.
Preserve original grants, atomic accepted prefixes and nonallocating publication/
rollback/cleanup, finish complete overflow/churn/native matrices and all other cards.
See [typed-input evidence](verification/s05-typed-input-2026-11-09.md). Ledger
41/3/34 and full78-card goal remain ACTIVE; S05/whole-query acceptance FALSE.
Preserve old maps/preimages/raw receipts/frozen verifiers/executed helpers unchanged.

## Predecessor S05 native window ownership checkpoint

Root implemented `s05-window-native-*`; one existing Luna Max agent performed a
read-only caller/test census. No Astra was used. Keep root for most work and
reserve Astra Max sparingly, per user preference. Previous goal turn was progress.
Production remains source1. Source4 freezes 929 paths; source5 changes only the
new test's owner-transfer idiom. Final source6 changes documentation only, for
930 paths. Progress-v2 binds source, raw receipts, binaries, scope audit and handoff.

Actual window options/control/capacity, label/count compact rows, expiration/
FIFO/relation nodes, active watermark/preflight storage and Prepared control/
update payload use the original account. Outer session controls keep session:0;
nested window ownership is session:1. Immutable WindowTables/AccountedWindowOptions
copies retain funded ownership after facades close. PhysicalUpdateView admits
borrowed native input without an ordinary Row mirror; pending state imports its
own rows/pins before returning. Canonical state remains an external DTO export.
The window payload sublimit now measures native descriptors/capacity; actual
framing/tree/control/preparation requests also consume the original query limit.

Full Debug build5 PASSES all targets; source4 full Debug CTest4 PASSES 212/212 in
880.95s. Selected 25 source4 checks PASS Clang18 99.58s and
ASan+UBSan/leaks 523.04s. Final source5 new test PASSES separately in
Debug 1.59s, Clang 1.41s and sanitizers 5.97s.
GCC Release source5 selected 25/25 PASS in 15.09s. All strict final
builds have zero compiler diagnostics. Existing tests are unchanged; final-test
assertion calls are preserved. This is scoped evidence; full compiler/sanitizer/
fresh-source/native acceptance remains open. Detailed stdout is preserved before
subsequent runs, with no CTest/registration enumeration overlap.

Real allocation equality, exact/one-under insertion and 512-label expansion caps,
all five scalars/38-digit decimals/binary keys, both backends/FIFO policies,
retained option/update lifetime, prior-prefix preservation, persistent failures,
same-input retry, controller-only release and nonallocating publish/stop/teardown
pass. Source4 insertion peaks are 129086/130446, global watermark 550946/551821,
per-relation 551232/552107; these are fixture values rather than universal bounds.
Preserve raw private-accessor compile failure, GDB-confirmed nested test-guard
abort and GCC Release optional reset/emplace warning. Source3/4/5 correct only
that new harness; no production rule, assertion or warning was weakened.

All 28 recorded jobs/handles are CLOSED; inspect jobs-v1 before new
work. Earlier progress/active-check records remain immutable historical state.
Old maps/preimages/raw receipts/frozen verifiers/executed helpers stay unchanged.
See [window evidence](verification/s05-window-native-2026-11-09.md) and
[memory contract](memory_accounts.md). Ledger 41/3/34 and the full 78-card goal
remain ACTIVE. S05/whole-query memory-budget acceptance remains FALSE.

Next: fund transport/queue/reader controls and nested input/window-command/source-
position values, session input/options/progress/observation/cursor/workload graphs,
capture/report/diagnostic/asynchronous storage and authentic operator record/byte
reconciliation. The 7-file 211-candidate inventory is not
exhaustive and distinguishes funded aliases/borrowed values/external DTOs from
remaining internal ownership. Preserve original allowances, atomic committed
prefixes and nonallocating publication/rollback/cleanup. Complete full native
compiler/sanitizer/fresh-source, overflow/churn matrices and every remaining card.

## Predecessor S05 constraint validation and rebuild scratch checkpoint

Root implemented `s05-validation-scratch-*`; one existing Luna Max agent completed
a read-only semantic/test census. No Astra was used. Continue using root for most
work and reserve Astra Max for occasional exceptional tasks, per user preference.
Source5 freezes926 paths and is the tested C++ implementation; final source6 adds
only current documentation, for927 paths. Immutable progress-v2 binds the final
source, raw receipts, binary hashes, scope audit and this handoff.

Actual physical input shape/type/decimal validation, whole-after-state native
constraint snapshots/projected keys and sorted operational rebuild snapshots now
use the original finite query account. The immutable admitted catalog is borrowed;
no ordinary operational whole-Database/Row/string mirror is built. Constraint
order, exact diagnostics, unused/self/cyclic tables, untrusted/empty keys and
both deterministic construction methods retain their behavior. Original work
precharges precede copies. Old owner, native snapshot and new owner share the
same allowance; failed admission preserves the old epoch and allows retry.

Full Debug build6 PASSES every target. Full Debug CTest5 PASSES211/211 in
882.29s. All20 selected checks PASS each GCC Release16.20s,
Clang18 100.24s and ASan+UBSan/leaks528.38s. All four current
strict builds have zero compiler warnings/errors. Complete detailed stdout is
preserved for each scope. Full compiler/sanitizer/fresh-source/native acceptance
remains open. All25 recorded commands/handles are CLOSED; inspect
jobs-v1 before starting new work. Progress-v1 is immutable historical running state.

New actual-runtime tests cover all five scalars/38-digit decimals/binary keys,
reference diagnostic parity, upstream-allocation reconciliation, exact/one-under
caps, constrained updates and shared-account direct/replay rebuild overlap,
persistent allocation failures and same-input recovery. Fixture validator peaks
are160549 /161329, update peaks657133 /659715 and replay rebuild peaks
752779 /757501; update faults44 /48 and rebuild faults64 /68.
These are fixture measurements rather than universal memory bounds.

Preserve raw source4 Release/ASan dangling Decimal-view failures and the obsolete
sanitizer cancellation record. Source5 fixes ScalarView lifetime; no warning or
assertion was weakened. Source3 fixes only the new test's caller-construction
measurement scope. Existing tests, public reference validator, frozen schemas/
CLI checkers, old source maps, preimages and executed helpers remain unchanged.
See [constraint evidence](verification/s05-validation-scratch-2026-11-09.md) and
[memory contract](memory_accounts.md). Ledger41/3/34 stays unchanged and the full
78-card goal remains ACTIVE. Whole-query/S05 acceptance remains FALSE.

Next: fund nested input/options/progress, transport/reader/queue, window maps/
rows/active-command/prepared controls and capture/report/diagnostic/async owners.
The7-file221-candidate inventory distinguishes internal operational scratch from
funded aliases and explicit external DTO exports; it is not exhaustive proof.
Authentic operator record/byte reconciliation, complete overflow/churn/native
matrices and all other cards remain. Preserve original allowances, atomic prior
epochs and nonallocating publication/rollback/cleanup throughout.

## Predecessor S05 epoch and journal array checkpoint

Root implemented `s05-epoch-arrays-*`; one Luna Max agent completed a read-only
caller/test census and no Astra agent was used. Continue using the root model
for complex work, with Astra Max reserved for exceptional problems. Previous
goal turn was progress. Source2 freezes923 paths and is the tested C++ code;
source3 changes current documentation only. Immutable progress-v2 binds final
source, raw receipts, binary hashes and this handoff.

Actual SupportJournal events, SupportEpoch transitions, PhysicalPreview derivation
capacity and retained SupportValueState child bit flags use real original-query
allocations. OwnerAllocator propagates that same account/purpose/attribution for
result copy/move/swap; maintained tables/record state still use fixed MemoryAllocator.
Copies fund new capacity under the source grant; moves/publication/cleanup allocate
nothing. Empty/no-op/trace-disabled buffers allocate no capacity. Old events,
transitions, child flags and derivations retain charged native data after facade
destruction. No uncharged mirror, accounting-only ticket or new allowance exists.

Full Debug build2 PASSES every target. Full Debug CTest2 PASSES210/210 in897.26s.
All18 selected ownership/model/lifetime/failure tests PASS each incremental mode:
GCC Release16.70s, Clang18 98.49s, ASan+UBSan/leaks538.55s. All four strict builds
have zero compiler warnings/errors. Full Debug detailed stdout contains all210
entries and is preserved; no registration enumeration overlapped that run.
Full compiler/sanitizer/fresh-source/native acceptance remains separately open.

Actual new epoch_memory test proves precise array request lookup, bit-buffer
rebind, origin-preserving copies/moves/swaps, trace on/off, no-allocation publication
and release, retained events/derivations after facade destruction, exact/one-under
history caps and109/123 persistent allocation failures. Debug fixture peaks are
146774 reference/152217 indexed; they are not universal production peaks. Denial
preserves the old epoch and releasing history permits same-sequence retry. Eight
existing test files explicitly export external DTO/range values and compare exact
bits; all assertion call counts and the staged-output failure probe remain. Full
model/semantic checks pass; the syntactic adaptation audit alone is not proof.

All14 recorded commands/handles are CLOSED; inspect jobs-v1 before new commands.
Progress-v1 is immutable historical running state. Old maps/preimages/raw receipts,
frozen schemas/CLI checkers and executed proof helpers remain unchanged. See
[epoch evidence](verification/s05-epoch-arrays-2026-11-09.md) and
[memory contract](memory_accounts.md). Ledger41/3/34 remains unchanged, and the
entire78-card goal stays active. Whole-query/S05 acceptance remains FALSE.

Next: fund operational constraint validation and bulk/initialization/rebuild
staging, including internal ordinary Database/Row/string materialization, under
the same finite account. It is still query-owned scratch even when not retained
rollback state. Then finish nested input/options/progress/window/transport/reader/
capture/diagnostic/async graphs and authentic operator record/byte reconciliation.
The next-owner inventory distinguishes remaining internal materialization from
already-funded aliases and explicit external exports; it is not exhaustive proof.
Preserve original allowances, atomic prior epochs and allocation-free publication/
rollback/cleanup, and complete the remaining full native matrices and cards.

## Predecessor S05 session and snapshot ownership checkpoint

Root implemented `s05-session-owners-*`; one Luna Max agent performed a read-only
caller/test audit, and no Astra agent was used. Continue doing complex work in
the root model and reserve Astra Max for exceptional problems. Source3 freezes
920 paths and is the tested C++ implementation. Final source4 changes only
current documentation; progress-v2 binds final hashes and scopes.

SessionSnapshot rows now use immutable SessionRows ownership. Its actual shared
object/control and vector capacity requests, including account framing, consume
the ORIGINAL query account alongside native tuple payloads. Empty rows allocate
no collection/control/capacity block. Row-collection copies and assignments share
that owner without allocation or a fresh allowance, including assignment across
queries. Iterators/references borrow from a live collection handle; copying a
whole snapshot can still allocate its ordinary progress map.

Factories return QuerySession::Owner, with actual funded facade/Impl and its
original-account deleter. Run-context and session capture OUTER controls are
funded too. Native WindowController construction borrows the already compiled
catalog and funds stable facade/Impl controls without moving the controller.
Nested options/progress, window nodes/rows/prepared controls and capture graphs
remain open. Published SupportJournal event, SupportEpoch transition and
PhysicalPreview derivation arrays also still use ordinary outer capacity.
Whole-query/S05 acceptance remains FALSE; ledger41/3/34 stays unchanged.

Current full Debug build4 PASSES every target with zero compiler warnings/errors.
Debug CTest3 PASSES57/57 related integration checks in130.09s. All14 selected
ownership/lifecycle/window/initialization-failure tests PASS in each incremental
mode: Release15.27s, Clang18 97.18s, ASan+UBSan/leaks519.43s. Their strict builds
have no compiler warnings/errors. These are scoped checks; there is no new full
current209-test, full compiler/sanitizer or fresh-source acceptance claim.

Actual new test stdout reconciles every retained collection/control/capacity and
tuple request; tests exact/one-under snapshot/query limits, held results after
facade destruction, immutable cross-account assignment, empty/nullary results,
nonallocating cleanup and23/25 persistent snapshot faults. Debug fixture peaks
are968527 reference/972668 indexed for13 rows with8192-byte string bodies. These
are fixture-specific, not universal production peaks. Seven existing tests have
only15 owner type substitutions; exact whole-file audit preserves all other
assertions and independent algorithms. Detailed stdout and raw receipts remain.

All commands/handles are CLOSED; inspect jobs-v1 before new work. Preserve raw
initial nonmovable-window compile failure, missing-target build attempts and the
new test's growth-schedule fixture failure. Source3 changes only that new fixture
from2: a smaller row cap legitimately selects smaller vector capacity, so the
exact/one-under comparison now keeps its measured growth schedule. No previous
CLI/schema/frozen verifier, old source map or executed proof helper was changed.
See [session evidence](verification/s05-session-owners-2026-11-09.md),
[memory contract](memory_accounts.md) and [session guide](session_lifecycle.md).

Next: fund published epoch/journal outer arrays and nested input/progress/window/
transport/reader/run-context/capture/diagnostic/async owners under the same finite
account. Preserve atomic admission/rejection, input head ownership through pending
work, original budgets, previous epochs and nonallocating publication/cleanup.
The next-owner inventory names131 candidates across9 files; it is not exhaustive
and distinguishes already-funded aliases and borrowed update parameters. Actual
Physical/Delta pending preparation retains native source/journal owners, rather
than an extra whole input Row copy. Authentic operator record/byte reconciliation,
complete byte/overflow/churn acceptance and full native matrices remain open.
The entire78-card goal stays active.

## Predecessor S05 public result checkpoint

Root completed the `s05-public-tuples-*` implementation and scoped checks without
agents. Follow the user's preference: do most work in the root model; reserve
Astra Max for exceptional difficult problems. Historical pending agent threads
still occupy the non-root slots; do not repeatedly attempt new agents.

Public Tuple retains an immutable native AccountedTuple and actual shared
object/control allocation under the ORIGINAL query account. `values()` returns
read-only TupleValuesView; native copies, views and iterators retain the same
payload without allocation and may outlive tuples/facades. Scalar string views
borrow from that retained owner. Explicit `export_row/export_scalar` provide
ordinary caller values; standalone compiler/tool tuples retain legacy Row input.
Native layout/projection factories preserve the original metadata token/account,
and projection avoids an unaccounted owning scratch row. Public cursor, Delta
mapped/scalar outputs and physical derivation payloads stay native. Spool bytes
now include actual scalar/shared-owner/node requests and account framing. Snapshot
payload limits use the same tuple usage; the outer snapshot vector is still open.

Source7 freezes **918 paths**. Full Debug build8 and CTest4 PASS every target and
**208/208 tests in901.14s**. The earlier broad CTest3 passes56/56 in123.73s.
Release and Clang18 each pass11/11 selected checks plus a separately run1/1
`layouts` check; the initial singular-name regex omitted that registered test.
These are selected incremental compiler checks, not full compiler/fresh-source
acceptance.

ASan+UBSan/leak CTest1 passes17/18; unchanged `storage_journal` hit its120s timeout.
Its direct run then PASSES in150.13s, including12,960 model operations and32/8
insert/erase fault positions. Source8 changes ONLY that test's sanitizer timeout
to300s. The same binary's registered retry PASSES1/1 in143.71s. The original raw
timeout remains intact; do not describe this as one18/18 CTest run. Source9 adds
only current documentation and the snapshot-limit comment; C++ behavior is
unchanged from7. Detailed new-test stdout is preserved from the source7 sanitizer
run: exact native public tuple peak10222/four faults, caller-retained output peaks
337506 reference/344847 indexed. These are scoped fixture measurements.

Test adaptation preserves assertion call counts in57 existing test/helper files;
the syntactic audit is not semantic proof. Exactly one precise work assertion
changes from `output_fields==1` to the declared output width, because the native
producer reads all scalar views before admitting its compact row. Its source6
failure and all lease/failure/state assertions are preserved. Raw compile
attempts, preimages and frozen CLI packages remain unchanged.

All commands/handles are CLOSED; inspect jobs-v1 before new work. Immutable
progress-v2 and [public-result evidence](verification/s05-public-tuples-2026-11-09.md)
bind final scope and hashes. Debug's mutable LastTest.log was overwritten by
registration enumeration; use the complete outer CTest4 raw receipt for208/208.
Its stale LastTestsFailed.log is source6 history, not a current failure; the
ctest-history-v2 annotation records this distinction.

Next: fund SessionSnapshot outer capacity/growth blocks, session controls/context,
typed queue/reader Row/string/control ownership and capture/diagnostic/async
owners under the same finite query account. The next-boundary inventory names
61 candidate sites in7 selected files; it is not a complete audit. Preserve batch
ownership on admission rejection, head ownership through pending work, original
allowances, atomic previous epochs and allocation-free publication/cleanup.
Authentic operator record/byte reconciliation and full native/compiler/sanitizer/
fresh-source matrices remain open. Full query-cap/S05 acceptance stays FALSE;
the ledger remains **41/3/34**, and the whole78-card objective stays active.

Following sections retain historical checkpoint scopes and remaining-work lists;
this current section supersedes their public-output status. Never edit old maps,
preimages, raw logs, executed proof helpers or frozen CLI packages.

## Predecessor native Delta live-state implementation

Current continuation uses `s05-delta-live-*` artifacts. Root implemented and
reviewed this cohort without agents. Reserve Astra Max for exceptional difficult
problems; use the root model for most work. The ledger remains **41 verified,
3 in progress, 34 not started** and the full goal stays active.

Actual ordered Delta rows use an internal AVL map/set. Both nodes and compact
scalar payloads are allocated by the ORIGINAL query account. Extracted nodes own
the exact allocation, so undo reclassification/reinsertion does not scan the
account ledger. Rotations and deletion preserve row/mapped addresses; destruction
is iterative and nonallocating. Independent tests cover all 720 six-key insertion
permutations, 6000 seeded mutations, exact/one-under caps, stable handles, binary
strings/decimals, nested owners, persistent faults and controller-only release.

Delta factor/separator/head/child/rank metadata, live L/P/B images and nested
rows, changed/removed keys, productive queues, events and linked undo now use the
existing account. So do anchored frames/scratch, stage owners, pending token,
epoch owner/stage summaries and actual spool NODE storage. Support cursor
`next_native()` emits AccountedTuple with the existing native output layout.
Native/public cursors share one producer/lifecycle and mandatory work accounting.
Native bucket/fixed-binding inputs avoid owning Row/string reimports. All actual
Delta internal production uses that native path. Explicit owning export remains
at public mapped spool output and caller diagnostics. Public Tuple/Row/string
payloads, captures/session/queue/async ownership and authentic whole-query
record/byte reconciliation still need completion. Whole-query memory-budget
completion and full S05 acceptance remain FALSE. No shadow tickets or new grants.

Source8 (914 paths) full Debug build9 PASSES every target; full Debug CTest5
PASSES **207/207 in 884.52s**. ASan+UBSan/leak build1 and CTest1 PASS **18/18 in
32.06s**. GCC Release build1/CTest1 PASS **6/6 in 0.33s**. Source8's initial Clang
build failed strict warnings on the physical source owner's implicit member
initializer. An isolated explicit constructor initializer compiled cleanly with
the same Clang flags before adoption. Source9 changes ONLY physical.cpp production
code to that initializer; it preserves initialization order and all assertions.

Current source9 targeted builds/tests PASS **8/8 in all four configurations**:
GCC Debug 1.92s, GCC Release 0.27s, Clang18 1.66s, ASan+UBSan/leaks 6.70s.
The two GCC Debug and two Release physical objects are byte-identical after debug
information removal to the tested source8 objects; see physical-objects-source9
comparison.json. Instrumented objects differ and have their own current checks.
There is no claim of a new source9 full-207/fresh-source matrix.

Actual native bootstrap exact/one-under peaks are 2060572 reference and 2071356
indexed. Complete Delta update persistent-failure sweeps cover 262/280 positions,
preserving prior state and same-sequence retry. Five strategies and both backends
pass crossing caps, actual attribution, undo and allocation-free prepared commit/
transfer/cleanup. Native/public cursor values, layout/account tokens and work
match, and inputs/results survive source/facade destruction. Existing empty-delta
work remains 8 for 1 versus 64 dead rows; anchored result work remains 13.
Current quantitative stdout is preserved in debug-ctest6-internal-stdout-v1.log.

All cohort commands/handles are CLOSED; jobs-v1 active is empty. Immutable
progress-v1 records the earlier running state and must not be overwritten.
Final progress-v2, source10 and this handoff record the completed scoped checks.
Source10 changes documentation only from9. Next-boundary inventory-v1 identifies
61 candidate values() calls across 15 production files; it is an inventory, not
acceptance evidence. Start with public Tuple's owned Row/strings while preserving
nonallocating publication/transfer/release. Then finish captures, session/queue/
async ownership, owner reconciliation and the remaining Refactor.md cards.

Preserve every raw failure: build1 test signedness, CTest1 caller probe allocated
under fault0, CTest3 small bootstrap fixture high-water assumption, build7 producer
name collided with an existing cursor-list pointer, and Clang build1 implicit
owner initializer warning. No assertion or warning gate was disabled. The isolated
larger source5 fixture fault258/276 counts and full Debug build6 are historical;
never bind them to current source. Never edit executed helpers, frozen packages,
old maps/preimages/raw logs, or restart a job recorded as active.

## Predecessor native plan interface implementation

Current continuation uses `s05-plan-interface-*` artifacts. Root is implementing
and checking this work; no additional agent is needed. The existing user
preference is to use Astra Max only sparingly for exceptional problems.

Immutable `CompiledProgram` metadata now lives in the core plan archive under
`crown::program`; runtime headers retain source aliases. The move passed native
program, runtime-memory and pure-ranking-link tests (3/3). Private compiler input
conversion reconstructs normalized SQL/options only when explicitly lowering a
new candidate. It is not a retained runtime compiler graph or a new query grant.

Native C02 evidence now holds the actual program owner and reads native
catalog/query/JSON views. SessionReportMetadata now holds only this native owner:
its transitional PhysicalPlan field and duplicate getter have been removed.
Selection's exact source encoder reads both compiler and native metadata with
the same versioned bytes; explicit compiler-output payload admission keeps its
legacy read-only overload. No runtime evidence materializes an old compiler graph.

Full isolated Debug build8 passes every target. Source map4 binds904 paths;
build8-binaries-v1 binds32 Debug binaries and both pure link inventories (no
runtime/report archives). Focused Debug CTest3 passes27/27 in42.06s. Sanitizer
build1 and ASan+UBSan/leak CTest1 pass9/9 in14.97s. Exact native binding is
compared to the frozen predecessor format after source destruction, with exact
and one-under payload caps. Full normalized SQL serialization and relowered
semantic/physical identities match the original compiler input. All unchanged
selection binding/cache/resource/source tests pass. Builds3/4/6/7 remain raw
failed attempts (unused visitor, misplaced friend, two downstream typed readers).
Do not replace those records or apply predecessor source pins to this source.

Persistent allocation-fault CTest1 on build8/map4 passed5/5 in768.52s:
ranking30.87s, normalized ranking768.51s, selection505.73s, normalized
selection223.21s, independent publication0.58s. Its raw stdout is authoritative;
quick and fault CTest invocations briefly overlapped, so shared temporary/history
files are not evidence. All these processes/handles are CLOSED. Do not repeat
these long sweeps merely to recover logs; later changes need their own checks.

Source5 native catalog/row/database validation uses the existing algorithms.
Build9 and direct1 pass4/4: legacy catalog/core, exact native shape/decimal/unique/
FK errors and actual ranking account/token identity. Source6 adds CatalogSource
as legacy-owned catalog or aliasing shared_ptr to the actual program's source
catalog. CompiledProgram::source_catalog_owner() allocates no control/mirror.
Actual QuerySession reader/queue constructors use this native alternative.
Fingerprint, JSON and binary bytes match legacy typed fixtures (including all
scalars, constraints, statistics and NUL metadata). Build10 and direct2 pass4/4;
core/SQL reader+queue lifetime releases to controller-only after source/program
destruction. Session failure checks pass (create199, begin48, step75, snapshot7,
drain14). EventReader.catalog() now returns const CatalogSource&.

Public Support/Physical/Delta plan() now returns const CompiledProgram&. Support
Impl::plan holds only this native owner after State construction; no persistent
PhysicalPlan remains in actual runtime owners. State's native constructor shares
the existing program/binding. Physical's private PlanSource variant is a transient
compiler/native construction argument, never a retained member. Native rebuild
reuses the original account, rejects a foreign account, preserves limit/backend
checks and the outer operation's existing work lease. Delta factor scopes now
borrow native spans and anchored DTO layouts share native descriptors.

Build11/12 failed on explicit diagnostic export and factor view types; build13
compiled the actual runtime, factor and native program but its initialization
oracle still required PhysicalPlan. Direct3 passes2/2, including the ORIGINAL
delta_factor regression with unchanged assertions. Source10 adapts initialization
oracle input types only: tests/reference/native_input.hpp makes explicit owned
reference inputs using private compiler conversion; independent assignment,
reference evaluation, SQL mapping and every assertion remain. Runtime updates/
rebuilds never use that helper. Build14 passes initialization, runtime_memory
and initialization-exception targets. Direct4 PASSES3/3, including persistent
physical/delta rebuild faults:974/1888 physical direct/replay and1048/1962 delta
direct/replay. Zero-work rebuild's largest allocation is215 bytes for a32768-byte
payload. Original account, work caps, retry, source/state and diagnostic checks
remain; no assertion was removed. Handles68134/68168 are CLOSED.

Current source map19 binds910 paths; source7–17 track public-plan corrections.
Sources18/19 change only schema test registration and add a native report fixture
plus versioned current-schema verifiers; production sources are unchanged from17.
The latest current public cutover has NOT had a complete compatibility/compiler/
sanitizer matrix. Full original-plan release is therefore still unaccepted;
S05 acceptance remains false. PhysicalBasis now stores an explicitly visited
variant of PhysicalPlan/CompiledProgram; actual-owner examples compile without
new accounts, source re-import or cached compiler graphs. Source and raw-tree
encoders preserve the same outer source tag and complete bytes; native explicit
lowering alone materializes owned compiler inputs after payload admission. A
new native/compiler cache-key/output/account differential test is being built.
Its initial test used a nonexistent cache constructor; source16 correctly uses
PlanCache::create(). Direct5 now passes2/2: native/compiler cache keys, output
plan and original account are identical; unchanged delta_factor passes again.

Source12–15 port independent reference/indexed support, physical, delta prefix,
initialization, cursor and prepared metadata input types only, with original
algorithms/assertions intact. Native support trace/snapshot diagnostic overloads
now read the program directly. Full collecting build20 reached all targets and
found only remaining typed helpers plus the new cache-test constructor. Source16
adds metadata-only native explanation factories (sharing the existing program),
ports those grouped helpers, and corrects the cache test. Build21 found the
journal adapter before its using-directives and one epoch-view predicate still
typed as the compiler step. Source17 uses a generic readable-layout adapter and
a read-only predicate; no warning suppression or assertion change. Full Debug
build22 PASSES ALL targets with zero warning diagnostics. Both current pure
planner link inventories contain no execution/report archive. Full build
inventory-v1 records204 tests and eight key binary identities.

Full Debug CTest4 is CLOSED, handle56781, with203/204 passing in1083.94s.
The sole failure was the old frozen CLI gate given current schemas. All current
native runtime, reference/indexed model, memory, initialization/rebuild fault,
ranking/selection and collision cases pass. Sanitizer build2 PASSES
all12 native/IO/rebuild/report/ranking/selection targets; ASan+UBSan/leak CTest2
PASSES12/12 in20.39s. Sanitizer handles49363/42567 are CLOSED. Current immutable
progress-v1 records the earlier live state; immutable progress-v2 records the
terminal203/204 result and the successful unchanged frozen CLI replay. Neither
record is overwritten or relabeled as a fully green/current205-test run.
Build22 handle71194 and inventory-read handle90237 are CLOSED. All earlier
full build handles and map4 fault sweeps are CLOSED. Inspect jobs-v1/logs first;
never restart live jobs. The schema registration issue is now RESOLVED with
original evidence preserved: the original frozen checker passes2749 checks /
175 CLI invocations against its own original pinned schemas. CMake now supplies
that schema directory (not the evolving current-schema directory). Registered
explain_cli passes44.80s. No checker/package/fixture checksum was changed.

New native report fixture tests/unit/report_memory_schema_test.cpp verifies
actual account limits before generating default,1048699 andUINT64_MAX session
reports. New tools/verify_report_memory_schema_v2.py checks that the ENTIRE schema
diff is exactly the two optional uint64 memory properties; default omission and
frozen compatibility, both exact nondefault field paths, max precision, negative/
overflow/Boolean/string/fraction/null/array/object rejection, zero syntax and all66
original package hashes. It PASSES115 checks / registered report_memory_schema
passes1.25s. Artifacts are retained in /tmp/crown-report-memory-schema-v2-qqv_5dh7
and immutable memory-schema-native-output-v2.log. The first checker v1 failed at
import because referencing is not installed. It and raw failure remain intact;
v2 uses the installed offline RefResolver with identical semantic assertions.
No network dependency was installed and no validator finding was suppressed.

Current inventory has205 registered tests. This is combined current coverage:
the203 source17 passes plus repaired frozen gate and new memory-schema gate;
there has NOT been a single205/205 run. Full incremental Debug build23 PASSES
every target; handle87356 is CLOSED, with no production implementation changes.
All cohort build/test handles are now CLOSED and jobs-v1 active is empty.
No complete S05/query-cap/Release/Clang/fresh-source acceptance is claimed.
Then finish remaining public outputs/child flags/captures/diagnostics/delta/
session/queue/async funding and authentic record/byte reconciliation. The
predecessor record below is historical, not proof of this source. Ledger remains
41/3/34; all78-card work is active.

Remaining concrete inventory at predecessor source19: Support RecordState child flags already use funded
MemoryVector<uint8_t>; do not redo that work. Delta Factor scopes borrow native
program spans, but separator/head/child/rank vectors, LiveImage/ProductiveQueue
relations/maps, prepared output and associated scratch still need actual funding.
storage::Tuple currently retains Row and exposes const Row&; std::string payload
cannot become funded merely by funding its outer container. Complete native
payload/readonly output boundaries while preserving no-allocation transfer,
commit, rollback and cleanup. Do not add shadow tickets, std mirrors, per-update
compiler re-import, or fresh execution allowances. Caller diagnostics/exports
and session/queue/async/capture attribution remain open. Root owns architecture.

Artifacts: `s05-plan-interface-*` source maps1–19, immutable preimages1–21,
versioned raw build/CTest logs and build8 binary inventory. The executed
run-job-v1 and direct-checks-v1 helpers are immutable; jobs-v1 holds child PIDs and terminal
results. Root implemented/reviewed/executed this cohort. No Astra or other agent
ran; the earlier Luna followup was rejected by the thread limit.

## Previous full retained-program implementation

Full goal remains active at 41/3/34. This successor is UNDER CONSTRUCTION;
there is no accepted retained-program checkpoint. Never rebind predecessor
input hashes to current sources. Runtime original plan release is incomplete.

CompiledProgram owns complete accounted model/SQL/validation/identity metadata,
native scalars, flat JSON and canonical layout/projection tokens. Actual Support
State, EpochView groups and result cursors retain it. Native input adapters are
used by physical mutation, bulk initialization, inspection and invariant checks.
Bulk seeds are funded native tuples; no internal standard Row re-import remains
in those paths. Public result/change/diagnostic DTO ownership is still open.

Readable TupleLayout/Projection handles share actual accounted native backing,
control and token; no field/string mirror or new control block is allocated.
Direct AccountedLayout::make covers native SQL/source/fragment layouts, binary
context, invalid partial construction, repeated variables and empty layouts.
Physical sources and cursor outputs use native backing. Statistics population,
index and occurrence descriptors now do too. Source4 capture token assertions and
journal replay preserve real runtime token plus full compiler descriptor checks.
The saved context oracle owns its expected string before destroying its input;
returned result tests release the result before the final controller-only check.

Verified construction cohort: full incremental Debug build19 passed every target.
Focused Debug3 passed 4/4 in3.66s (memory/native-program/physical/initialization).
Before metadata-only extraction, native program faults were359 reference/360
indexed. Native descriptor no-allocation/token/lifetime tests passed. Reference/
indexed peaks: support75278/80644, cursor65403/69358, binary binding65923/68612,
overlay160691/157575. Support fault positions110/124, physical124/140. Later
metadata-only work changes construction peaks/counts; remeasure rather than reuse.

Successor source4: fresh isolated build/retained-program-debug six focused tests
passed6/6 in1.96s; native capture/journal ASan+UBSan/leaks passed3/3 in3.20s.
Earlier sanitizer runtime set passed10/10; its core oracle failed as expected and
then passed separately after correction (Debug0.38s, sanitizer1.20s). No runtime
sanitizer findings were suppressed. Fresh isolated pinned C dependency emitted a
jobserver warning and two upstream upb maybe-uninitialized warnings; C++ targets
passed Werror. Do not call the fresh build warning-free overall.

Original source1 full Debug CTest4 completed197/204 in3133.35s. Failures:
- memory_account_contract and both accounted-indexed collision variants: saved
  expected_context borrowed a freed original string. GDB/ASan confirmed it;
  explicit owning-oracle fix passes primary Debug/San. Collision reruns pending.
- support_journal: compiler-token replay oracle after native snapshot cutover.
  Corrected runtime-token plus descriptor checks pass isolated Debug/San.
- s04_indexed_runtime_budget:40-row crossing had4056 pointer words vs setup4103;
  every other domain dominated. Original assertions remain; see optimization below.
- delta_factor: factor uses native token while public runtime plan() still exposes
  the original compiler token. Complete native public-plan API; do not weaken test.
- explain_cli: immutable acceptance package pins old report schema c4aa8c7c...;
  current bac63f22... equals the previous cursor-cohort schema. This mismatch
  predates this cohort. Existing executed checker/package/fixtures are untouched.
  Handle a reviewed versioned successor or legitimate schema repair, not blind
  hash updates or weakened checks.
Original focused56 closed54/56 in1087.10s (journal and budget failures). Preserve
both raw failures; these are original binary/input-map1 runs, not current green
acceptance. All original long test handles68633/84779 are CLOSED.

Current successor implementation: workload Snapshot, OwnerCapture and
observability ModeDescriptor own CompiledProgram. SessionReportMetadata has its
actual compiled_program() owner for reports plus an explicitly transitional
PhysicalPlan plan() handle for the existing C02 pure-ranking boundary.
Physical/delta private getters share the actual State program; no fresh query
account/grant is made for runtime reports. Native report/model readers compare
full catalogs, constraints, statistics/hints, query terms/scalars and tree claims
against typed original evidence. Compiler-only explanations use a standalone
metadata account and work inventory; they create no query execution state.
AccountedPlanStorage::freeze_binding now freezes immutable metadata without
constructing temporary mutable tables. CompiledProgram uses it; actual State
constructs tables once with the original account/grant. Public storage constructors
retain their original materialization and checks. The unchanged40-row budget
fixture should now be rechecked against reduced setup work.

Native report builds are now passing the targeted compilation. Isolated build7
built all11 targets with zero C++ diagnostics. Debug isolated CTest2 passed10/11
in15.18s: core, native program/memory, owner/workload, both collision modes,
journal and strict production/composed reports pass. The remaining40-row budget
fixture still had pointer words4056 vs setup4067 after metadata-only extraction.
Only the real population changed40->48 (preimage25); all original dominance,
exact/five independent one-under rollback, stable handles, no-refill, allocation-
free recovery and retry assertions remain. Build8/CTest3 pass; exact work is
{1977,702,28750,4448,5082};163 allocation positions pass,0.82s. No boundary was
relaxed. Current native program constructor faults are348 reference/349 indexed.

Source8 current ASan+UBSan/leaks CTest4 passed13/13 in35.14s (core, both
collision modes, program/memory, owner/workload success/failures, strict reports,
journal and exact work-budget tests). Full isolated build9 then found C02's
runtime bridge requires a PhysicalPlan from SessionReportMetadata.plan(). Do not
clone/re-import a compiler graph or move runtime dependency into the pure ranking
library just to make it compile. Source9 explicitly stages this boundary:
SessionReportMetadata.plan() stays PhysicalPlan for C02 while compiled_program()
shares the actual State program. ModeDescriptor/from-session and independent
report readers use compiled_program(). No new query account/grant or graph clone
is made. This compatibility handle MUST be removed during final public-plan/C02
source-interface migration; full original-plan release remains false.

Current reviewable progress record: s05-retained-program-progress-v1.json.
Full isolated Debug build11 passed ALL targets with zero C++ warnings. Build10's
last mismatch was a numeric census fixture passing PhysicalPlan to native State
snapshot; it now uses metadata from an actual owner (preimage27), with every
saturation/protocol assertion preserved. Final Debug CTest4 passes19/19 in16.05s:
core/native program/memory, owner/workload success/failures, both collisions,
journal, strict production/composed reports, exact budget, ranking census,
ranking/selection pure-link and contract/empty cases. Current compatibility
ASan+UBSan/leaks CTest5 passes6/6 in17.25s (workload, reports, composed, ranking
contract/empty, selection contract), in addition to source8 sanitizer13/13.

ALL retained-program build/test handles are now CLOSED; jobs-v1 active is empty.
Do not poll any old handles, including10600/69450/5741/81206/45469. Current source
input maps v10/v11 contain the same897 implementation paths; this handoff is
bound separately in the progress receipt. Source
implementation remained unchanged during final build/checks. This is reviewable
PROGRESS, not full S05 acceptance or whole-goal completion. No current Release/
Clang/frozen-source/full native/compiler gate is claimed from predecessor proofs.
The original204-test run remains197/204; do not replace its raw result with these
selected successor passes. Five original failures have corrected current focused
coverage; delta_factor/public-plan token and pinned explain_cli remain open.

Luna's read-only catalog inventory for the next cutover: EventReader::Data and
TypedQueue::Data retain Catalog; their validators/readers are concretely typed.
EventReader exposes const Catalog& catalog(). WindowController retains no Catalog
but takes one during construction. Native catalog aliases should retain the
existing program, with read-only validators/helpers; no old graph materialization
per update. validate_database is in src/ir/model.cpp; catalog validation/constraints/
find_table are src/catalog/catalog.cpp. Rebuild currently passes the old plan to
initialize_at; it needs native program constructors preserving account/grant.
No registered CTest was found reading production C++ source at runtime;
verify_clean_build.py does copy/build sources but is not a registered CTest.

Actual retained compiler plans remain in Support Impl::plan and the explicit
SessionReportMetadata::plan_ compatibility handle (constructor arguments and
construction-only Builder::source_ do not count). Public runtime
plan APIs plus catalog/reader/validator/rebuild consumers still need cutover.
After that, finish all public output/child-flag/capture/diagnostic/delta/session/
queue/rebuild/async ownership and authentic operator byte/record reconciliation.
Full S05 acceptance/compiler/source/native matrices and all78 cards remain open.
A02/O06 remain in progress; no goal blockage or completion is claimed.

Artifacts use s05-retained-program prefix: immutable preimages-v1–v27, input maps
v1–v11 (897 paths), raw build/CTest/debugger logs, Debug inventory v1, selected-test
names v1, mutable jobs-v1. Input1 binds original build19/tests; input2 changes only
owned context oracle; input3 native capture descriptors; input4 journal token
oracle; input5 retained reports; input6 metadata-only/explanation ownership.
Input7 includes the completed native getter/test reader; input8 the48-row fixture;
input9 explicit C02 compatibility; input10 numeric census fixture; input11 final
implementation validation (same source hashes as10). Handoff digest is separate.
All handles are CLOSED at this update. Root implemented/reviewed/executed all
architecture and fixes. Luna Max only performed bounded read-only inventories.
No Astra ran. A single exceptional Astra Max design review was attempted but
thread limits rejected creation; root made the compatibility decision. Reserve
Astra Max for exceptional problems and keep root doing most work as requested.

## Previous S05 cursor/view ownership checkpoint

Sealed record: `build/verification/s05-cursor-overlays-checkpoint-v1.json`
(SHA-256 `fa696859de39510f5d4b4391ea794699e087bead608f16fb7a181d4ee5fbbaf1`). Source audit and matrix are bound in that record.

Actual view overlays now fund full/projected AccountedRow keys and every nested
map/set node under the existing query account. Transparent RowView probes avoid
internal standard Row exports. Cursor fixed scalars own compact copies, including
binary bytes. Fragment/position/first-field/outer/selected/variable/stack and direct
initialization postorder/stack scratch are also funded. Empty outer maps and nested
buckets receive explicit allocators. Patch::memory() returns the account by value
so no reference escapes a temporary allocator. Patch array words consume the
original canonical native work grant; no new account or allowance is created.

All **48 selected tests** pass GCC Debug/Release, Clang18 Debug and GCC
ASan+UBSan/leaks: **122.41 /14.90 /93.83 /511.54 seconds**. Final builds have zero
compiler warnings and original sanitizer timeouts remain. The cohort includes
memory40, independent models, journal/epoch/prepared/result/fragment failure and
lifetime suites, indexed budgets, physical/delta/session/initialization/scale,
statistics/observation, original strict reports and physical/support CLI fixtures.
These are incremental live-source checks, not fresh frozen-source/full compiler/
native acceptance gates. Implementation stayed unchanged during the final matrix.

Direct Debug peaks (reference/indexed): four cursors **35,573/39,372**, binary fixed
binding **36,429/38,962**, before-side overlay **131,062/127,790** requested bytes.
An 8,194-byte NUL/0xff binding is charged. Full and nested index overlay keys
charge at least three owned binary copies. Exact/one-under limits, smaller retry,
prepared-state preservation, allocation-free rollback and retained ghost/direct
lookups after binding input/facade destruction pass. Final owners release to the
account controller. Existing support110/124 and physical126/142 upstream faults,
canonical/payload/pin checks and stable warmed native-capacity reuse remain.

Current build/verification records use the s05-cursor-overlays prefix: checkpoint/
matrix/inputs/current-source-audit/root-review v1, immutable close helper,
selected-tests-v1, raw build/CTest/full native outputs, preimages-v1 and mutable
jobs-v1. Continuation is s05-native-query-integration-next-v10.json. Original
executed helpers, pinned baselines and raw receipts were not edited. Never apply
historical INPUT binders to successor code. All processes are CLOSED: focused
build4425, final builds85889/44731/43726/79033, CTests48383/76141/65259/60439.
Do not poll them. Root implemented/reviewed/executed. Luna Max only supplied
bounded read-only fixture/accessor inventories. No Astra was used; continue using
root for most work and reserve Astra Max for exceptional difficulty.

Next substantive work is the **complete retained compiled runtime program** under
the same account, releasing original PhysicalPlan and legacy descriptor handles.
Include catalog/query/tree, validation/guarantee/options/identity, canonical identity
JSON, normalized SQL/bound expressions/constants/parameters/outputs, input adapters
and all compiled metadata. Reuse canonical funded layout/projection aliases.
Current plan()/source_layout()/output APIs and rebuild/report consumers need an
explicit native ownership/view migration. PhysicalPlan::Data also owns a JSON
cleanup-pointer vector: preserve nonallocating destruction on partial failure.
Luna's factual accessor inventory and required scope are recorded in v10.

Then finish transient physical Row adaptation, public journal child flags and
get/result/snapshot/trace/capture/diagnostic buffers, delta/session/imported queues/
output/rebuild/async ownership, actual compiled-operator byte/record reconciliation
and complete native/source/compiler acceptance. Unused legacy work alias cleanup
remains; all operational support/physical storage already uses native canonical
work. Do not substitute an unmeasured retained old graph or budget tickets for
native ownership. Full S05 and all 78 cards remain active at **41/3/34**.

See [overlay evidence](verification/cursor-overlays-2026-11-08.md),
[contract](memory_accounts.md) and [ledger](task_ledger.md). The prior compact
support checkpoint below is historical; its prepared overlay draft was verified
against its base hash, applied, and extended for scratch ownership in this cohort.

## Previous S05 compact logical support checkpoint

Sealed checkpoint: `build/verification/s05-compact-support-checkpoint-v1.json`
(SHA-256 `dc745a7d3bdb546254b527db5a0cce4e972098bde45d0677da31bf25c3bc2ad7`). Source audit and matrix are bound in that record.

Actual SupportRuntime now uses AccountedPlanStorage and native compact tables
for both backends. Frozen node/edge/enumeration programs, propagation tuples,
metadata/undo and retained native journal pins use the existing query account.
The bounded construction-only projection memo preserves canonical index/source
aliases; no source pointer memo is retained. Array words and memo reservation
consume the same finite native work grant before publication.

Journal record/writer arrays, pending/transaction controls, cursor/frame/condition/
lookup/probe-child buffers and view controls/patch arrays are funded. Public
relation_layout() exposes the authoritative borrowed native token. Native direct
lookup uses funded scalar-view scratch. Public get/result/snapshot/trace outputs
remain explicit legacy exports.

All **48 selected tests** pass GCC Debug/Release, Clang18 Debug and GCC
ASan+UBSan/leaks: **117.50 /14.96 /91.26 /503.52 seconds**. Final builds have zero
compiler warnings; the original sanitizer timeout is unchanged. The selection
includes memory40, independent support models, journals/prepared epochs, result/
fragment/epoch cursors and failures, indexed budgets, physical/delta schedules,
sessions, initialization/scale/failures, captures, original strict reports and
physical/support CLI fixtures. These are incremental live-source checks, not
fresh frozen-source/full compiler/native acceptance gates.

Final fixture peaks (reference/indexed): support **45,896/51,106**, four concurrent
cursors **35,445/39,244**, physical sources **37,565/41,065** requested bytes.
Exact/one-under admission and smaller retry pass. Denied cursor startup preserves
existing leases and releases partial controls. Actual support110/124 and integrated
physical126/142 persistent allocation failures preserve prior canonical state and
valid retry. Retained journals/cursors/pins release the account to its controller.
These are testing fixtures, not full query or production peaks.

The original exact-byte rollback failure and diagnostics remain preserved. Native
arenas/directories keep admitted reusable capacity; tests now demand exact prior
canonical state, unchanged compact payload ownership, no leaked retained records/
pins and stable warmed churn. Undo under fail-every-allocation makes zero calls.
Native journal test images use explicit exported rows and retained layout handles;
token identity uses each runtime's native relation authority, and separate runtimes
compare descriptors/values. Independent oracles and pinned report checks remain.

Current build/verification receipts: s05-compact-support checkpoint/matrix/inputs/
current-source-audit/root-review v1, immutable close helper, selected-tests-v1,
raw outputs/full per-test logs, preimages v1–v7, mutable jobs-v1 and continuation
s05-native-query-integration-next-v9.json. Original executed checkers, baselines
and raw receipts were not edited. Never bind predecessor INPUT hashes to successor
source; use predecessor file names only when preparing a new source record.

All processes are CLOSED, including final build80597/67041/74006/82338 and
CTest79400/25674/9913/62320. All failed earlier attempts remain in jobs-v1;
do not poll closed handles. Root implemented/reviewed/executed this cohort. Luna
Max only supplied a bounded read-only API inventory; **no Astra was used**.
Continue relying on root and reserving Astra Max for exceptional difficulty.

Next, fund actual view overlay map nodes/compact keys and cursor fixed scalars.
A separate unapplied draft is preserved as
build/verification/s05-compact-support-next-overlay-candidate-v1.cpp, with its
manifest/base hash and strict C++23 syntax-only receipt. It is not part of the
48-test matrix and still needs runtime resource/lifetime tests and review. Check
the manifest base hash before applying it. Continuation v9 records the exact plan.

Full S05 remains open: original PhysicalPlan/catalog/query/SQL metadata and legacy
output descriptors; public outputs/child flags; overlay/binding maps and remaining
startup/initialization scratch; delta/session/queues/captures/output/rebuild
ownership; actual compiled-operator reconciliation and full native acceptance.
The unused legacy work alias remains; actual support/physical use native work.
The [support evidence](verification/compact-support-2026-11-08.md),
[contract](memory_accounts.md) and [ledger](task_ledger.md) describe the boundary.
The full 78-card goal remains active at **41/3/34**.

## Previous S05 compact physical source checkpoint

PhysicalRuntime now uses native AccountedStorageTable for both selected backends.
Source rows/pins/owning exports and derivation keys are compact and funded by the
existing query account. Actual arrays/map nodes, pending controls and count undo
are funded. There is no earlier source table or retained standard source Row
mirror. Native source limits/work remain enforced; rebuild shares the account.

One canonical finite work balance supports native fixed diagnostics and a private
nonowning legacy support diagnostic view. The view stores a root pointer in a
union, not another remaining allowance; it cannot mint/refill work. Its owning
lease retains the canonical control. Public fixed failures format only after
prepared state unwinds. Private source metadata IDs preserve public owner IDs.

`SourceRowChange::retained` is AccountedTupleArena::Pin and `tuple()` borrows an
AccountedTuple. `get_source()` returns an owning AccountedTuple with output
attribution under the same account. Borrowed RowView/Row comparison allocates
nothing; explicit scalar/row exports preserve all scalar kinds and binary bytes.
`source_layout()` still returns the legacy metadata descriptor for current capture
consumers; the tuple's own layout is its funded frozen token.

All **32 selected tests** pass GCC Debug/Release, Clang18 C/C++ Debug and GCC
ASan+UBSan/leaks. Times: 168.28 /26.63 /128.62 /694.36 seconds. Debug then added
integrated physical-fault assertions to runtime_memory and reran that test only
(0.39s); native implementation did not change. Other modes ran the final version.
The cohort includes native40 memory, physical/indexed routes, initialization/fault/
retention, delta schedules/faults, sessions, captures and original strict reports.
Debug CLI also builds and passes physical/support fixtures (2/2, 2.90 seconds).

New actual physical sweeps fail all **132 reference /145 indexed** allocation
positions and verify previous canonical state/stable handles and valid retry.
An 8,194-byte ignored binary column has routed fixture peaks **26,608/27,604**;
exact/one-under/smaller-retry, retained pin after facade release and final routed
release pass. Existing support116/127 faults remain; indexed support peak becomes
10,805 because its lease now owns the real diagnostic view (reference10,383).
These are fixture/testing runtime bytes, not full query/production peaks.

Legacy PhysicalPlan/source descriptor data, transient source Row adapter, logical
support rows/tables, delta/session/queues/outputs/captures and full operator
reconciliation remain open. Ledger map classification costs O(outstanding account
allocations). No uniform runtime speed/delay or whole-query cap is claimed.

Current build/verification receipts: **s05-compact-source-checkpoint-v1.json**,
matrix/root-review/current-source-audit v1, inputs v1 (888 files), preimages v1–v4,
raw mode and CLI outputs, mutable jobs v1, continuation next-plan v8. These are
incremental live-source checks, not fresh frozen-source/compiler audit gates.
Predecessor owner/accounted-plan binders are historical; never apply their INPUT
hashes to current code. Original executed checkers and pinned baselines were not
edited. Initial preview serializer compile failure remains preserved.

All processes are CLOSED. Most recent build handles **53167/29064/21234/31467/
38596/99304** and CTests **96841/55165/76512/9902/71853** are closed; do not poll.
All earlier handles in jobs v1 are also closed. Root implemented/reviewed/executed.
Only a bounded read-only Luna Max API inventory/follow-up was delegated. No Astra
was used; continue reserving it for exceptional decisions.

See [source evidence](verification/compact-sources-2026-11-08.md) and the
[contract](memory_accounts.md). Full 78-card counts remain **41/3/34**.

## Previous runtime owner/metadata checkpoint

Actual Support/Physical/Delta runtimes now share one finite memory account for
both storage backends. Session options forward it. Rebuild retains that account
across old/new state while preserving separate target work grants. Implementation
controls, indexed leases/grants, and support record/counter/flag/routing/queue/undo
allocations are funded. Saved flags and extracted nodes retain compatible
allocators; undo allocates nothing. Private metadata IDs use their own authority,
so public runtime-owner sequences and pinned default v2 report bytes stay stable.
Custom limits survive trace/configuration/report exports. The default is 256 MiB.

All **16 focused tests** pass GCC Debug/Release, Clang18 C/C++ Debug and GCC
ASan+UBSan/leaks (30.50/11.94/26.35/102.42 seconds). This includes the 40-check
compact-memory fixture, new real-runtime memory tests, existing support/physical/
delta faults, session, shared indexed work and six strict report/observation
checks. The new fixture passes 116/127 persistent epoch faults, exact/one-under
routed peaks 10,383/10,757 bytes, previous-state rollback/retry, allocation-free
undo, retained controls, shared rebuild overlap and 40 no-op/churn cycles.

This is incremental maintained-source verification, **not** a fresh full native
suite/compiler audit or complete S05. Legacy PhysicalPlan, Row/Tuple/table
payloads, output, remaining delta/session collections and full operator reports
still need migration. `accounted_memory_statistics()` reports only routed bytes.
Map-node lifetime classification currently costs O(outstanding account
allocations); do not claim a uniform runtime speed/delay bound.

Current receipts under `build/verification/` have prefix `s05-runtime-owner-`:
checkpoint v1, root review v1, matrix v1, tested-inputs v1 (886 files), current-
source audit v1, final mode logs/native output attempt2, mutable jobs v1 and
successive preimages v1–v5. Root implemented/reviewed/executed. One focused
read-only Astra Max architecture review completed. The user explicitly reiterated
using Astra Max less; handle most work and reviews with root.

No compiler/test/helper is active. Final build handles **4554/37187/46314/21201**
and CTest handles **70178/38326/12196/71180** are CLOSED. All earlier handles in
the jobs record are also closed. Do not poll them. Failures and /tmp artifacts
remain preserved: allocator-type compile errors, a corrected retained-token test
expectation, default report byte compatibility, and the fixed public-owner ID
regression. Original checkers and legacy baselines were never changed.

See [runtime evidence](verification/runtime-memory-2026-11-08.md) and the
[contract](memory_accounts.md). Full ledger counts remain 41/3/34 of 78.

## Previous accounted compiled-plan checkpoint

S05 is in progress. Native account/allocator, compact rows, frozen layouts/
projections, arenas, accounted reference/optimized tables and dispatch exist.
New `crown_accounted_plan_storage` builds AccountedPlanStorage from an actual
borrowed opaque PhysicalPlan. It retains funded storage metadata, numeric
relation/index mappings and native tables; no original plan, source span or
standard Row mirror is retained. Frozen aliases and distinct projection tokens
are preserved. Copies share metadata and create fresh table/instance owners
under the same existing query account. Moves between allocator owners allocate
nothing. Metadata, instance, table/arena, input and controller bytes reconcile
with independently observed real requests.

All 14 selected tests pass and are audited in GCC Debug/Release, Clang C/C++
Debug and GCC ASan+UBSan/leaks. Each fresh build has 77 actual C++ commands from
68 distinct sources, 13 native libraries and 14 executables. The parser adds
96 C objects from the pinned archive; all 1,156 extracted original files match.
Each memory profile runs 40 checks retaining all earlier 38/36/31/26 checks.
The actual compiled-plan/SQL test invokes the public opaque-plan constructor,
compares exact rows/IDs, index/key/bucket order and sparse copies for both
backends. The test-only construction shim uses the same native implementation
for allocation tracing and is absent from production libraries.

New fixtures fail all 179 constructor/copy positions: reference 26/56, indexed
29/68. Five positive initialization work domains pass exact/one-under admission.
Source descriptors are destroyed before use; pins keep frozen layout bytes
charged until final release. Fixture peaks are 47,912 requested bytes for
reference and 51,066 for production indexed; three testing State fields add
24 bytes (51,090). Exact byte limits, one-under denial and smaller retry pass.
Prior 91 reference/104 indexed/134 dispatch fault positions, 44 work boundaries,
nine component limits, retained undo and differential/sparse checks remain.
Metadata compilation costs are separate from ordinary indexed-path guarantees.
No universal startup/delay or runtime speedup is asserted.

See the [contract](memory_accounts.md) and [scoped evidence](verification/memory-plan-2026-11-08.md).
The maintained runtime still uses earlier PlanStorage/StorageTable/Tuple/Row.
Complete IR/catalog/query ownership, actual runtime adoption, operator reports
and full native query acceptance remain open.

Current evidence under `build/verification/`:

- `s05-accounted-plan-checkpoint-v1.json` and current-source audit v1.
- `s05-accounted-plan-matrix-accepted-v1.json`.
- Frozen `s05-accounted-plan-source-attempt-1/` (883 files) and execution freeze
  attempt1. Reviewed documentation adds one evidence file (884 current inputs).
- `s05-accounted-plan-LABEL-attempt-1-records/`, audit-v5 summaries and actual
  terminal closures for debug/release/clang/sanitize.
- Executed runner `s05-native-storage-run-v2.py`, auditor v5 with plan root
  auditor review v1, plan collector/binder v1 and documentation receipt.
- Mutable `s05-accounted-plan-jobs.json`; continuation
  `s05-native-query-integration-next-v6.json`; exact source findings in
  `s05-native-runtime-adoption-notes-v1.json`.

No compiler, test, benchmark or helper is active. Run handles **76862** (Debug),
**38054** (Release), **71927** (Clang), **36693** (sanitizers), auditors
**9401/46675/29257/58443** and collector **46100** are CLOSED. Do not poll them,
prior dispatch/optimized/native/source8 handles or old S04 sanitizer **99561**.
Repeat passing modes only for changed source, failures or a justified concern.

## Next implementation: frozen program and logical support values

1. Freeze the complete retained runtime/query program under the existing owner.
   Reuse AccountedPlanStorage tokens and current physical source frozen layouts;
   preserve projection aliases across inputs/nodes/edges/enumeration/output. Own
   constants, adapters, IR/catalog/query/normalization/identity/guarantee metadata
   and release original PhysicalPlan/legacy descriptors in the actual runtime.
2. Port the existing logical support state to accounted storage and compact owned/
   borrowed values. Physical sources and derivation keys already use it. Add
   funded scalar-view assembly at the actual adapter/assembly boundaries; remove
   the transient source Row export and earlier DerivationChange/Support values.
   Change downstream metadata/value views in the same coherent adoption, not an
   unused helper beside existing facades.
3. Preserve one canonical work balance across old diagnostic views and compact
   tables until migration removes the legacy view. Do not change diagnostic mode
   by mutating the root, mint replacement grants, or create another account for
   reference sources, nested calls or old/new rebuild state.
4. Finish cursor/capture/output/delta/session/rebuild/input-transfer ownership.
   Moving caller-built queue payloads into engine ownership does not charge them;
   import/clone or checked transfer must retain the original account contract.
5. Reconcile actual compiled operator records with live/retained/reserved/current/
   peak/historical bytes; deduplicate shared metadata. Keep allocator/purpose/
   attribution unchanged through undo. Document/remove ledger scan costs without
   hiding them under ordinary O(1) claims.
6. Expand complete query byte/overflow/failure/no-op/churn checks and perform full
   native/source/compiler gates before verifying S05. Keep the entire 78-card goal
   active; A02 licensing and all other open cards/release gates remain required.

The previous one-off focused architecture review favored explicit ownership and
read-only compact runtime program views. Root owns implementation and most
reviews; use Astra Max much less, as explicitly requested by the user.

## Preserve contracts and historical evidence

Read [indexed storage](indexed_storage.md), [arenas](tuple_arenas.md),
[storage undo](storage_journal.md), [prepared epochs](prepared_epochs.md),
[physical plans](physical_plans.md), [sessions](session_lifecycle.md) and
[statistics](statistics.md) when changing ownership. Preserve native IDs,
tokens, handles, pins, finite shared work and allocation-free undo/final teardown.
Shared metadata and weak controls stay charged until actual final deallocation.
Requested ordinary-new bytes exclude allocator usable size, RSS and exception-
runtime storage. The nested-string coverage-gap witness remains explicit.

Never edit executed helpers, frozen sources, raw records or failures. Source1
passed all four modes on its first run. Runner v2 additionally pins the parser's
C driver. Upstream hides individual C command lines; audited make/source/object/
archive evidence is stated separately from exact native C++ commands.

Prior checkpoints are `s05-accounted-dispatch-checkpoint-v1.json`,
`s05-accounted-indexed-checkpoint-v1.json` and `s05-native-storage-checkpoint-v1.json`.
S04 remains verified on its historical source: 199 tests/five modes, 281 commands/
231 sources, canonical `s04-completion-checkpoint.json` and
`docs/verification/indexed-sources.sha256`. Qualified timings showed faster
secondary walks and slower primary/eight-live walks. Never compare historical
source/INPUT maps with successor code. Preimages/full prior handoffs are under
`build/verification/s05-accounted-plan-preimages-v1/` and predecessor preimage
directories. The old editable component draft is historical; live include/src
code is authoritative. The accounted-plan frozen snapshot predates this runtime
migration. Its source binder is historical; use the runtime-owner source audit
for current code and do not re-evaluate predecessor INPUT hashes against it.

## Environment and working preference

GCC 13, CMake 3.28, Python 3.12. Clang drivers are
`build/toolchains/clang18/root/usr/bin/clang++-18` and `clang-18`; preserve their
spellings and pin the resolved binary separately. Build offline. Default launch
fails with bwrap loopback setup; scoped local commands work with
`require_escalated`. No automatic review rejection occurred. Git metadata is
read-only; no commit was made.

Root handles implementation, most reviews and execution. Use Astra Max only
occasionally for unusually difficult decisions; one focused architecture review
completed in this runtime phase. The user explicitly asked to reduce its use.
Luna Max may handle bounded simple work; do not delegate project execution.

A02 distribution licensing remains pending. Do not infer an answer or ask again;
independent original implementation proceeds under Refactor.md section 1.4.
O04–O06 recovery/delivery, optimizer/extensions/experiments and release cards
remain open. Keep the full 78-card goal active; do not pause without the user's
request or mark it complete at this storage checkpoint.
