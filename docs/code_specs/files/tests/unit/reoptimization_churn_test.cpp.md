# `tests/unit/reoptimization_churn_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_churn_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `bb9bc6489b5989c30aa01c5609b0eacd6ab4f0cc1a34f13b6c5298d9f47f7ba0`. 95 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/reoptimization_churn_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 14–14](../../../../../tests/unit/reoptimization_churn_test.cpp#L14) | Type/record definition: struct SteadyMemory |  · [reviewed contract](#b0002) |
| [B0003 · 15–17](../../../../../tests/unit/reoptimization_churn_test.cpp#L15) | Callable definition: reoptimization::Options options(std::uint64_t round) | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 18–21](../../../../../tests/unit/reoptimization_churn_test.cpp#L18) | Callable definition: void enqueue(QuerySession& session,const PhysicalSetUpdate& update) | calls batch, check; guard check(session.enqueue(batch)==io::Admission::accepted,"churn input was not admitted"); · [reviewed contract](#b0004) |
| [B0005 · 22–25](../../../../../tests/unit/reoptimization_churn_test.cpp#L22) | Callable definition: void reference_update(QuerySession& session,const PhysicalSetUpdate& update,Outputs& output) | calls enqueue, check, begin_next, local_sink_test::finish; guard enqueue(session,update);check(session.begin_next(),"churn reference event missing");local_sink_test…; growth emplace; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 26–84](../../../../../tests/unit/reoptimization_churn_test.cpp#L26) | Callable definition: void run(const PhysicalPlan& original,const planner::CandidateSnapshot& family,const Database& initial,const PhysicalOptions& phy… | calls file, QuerySession::create_typed, start, generation_test::options; guard check(actual.emplace(delivered.sequence,local_sink_test::output(epoch)).second,"churn repeated a pu…; growth emplace, insert; 3 loop sites; source comment (unverified): // Refactor.md permits a declared retained recovery log. Subtract only the · [reviewed contract](#b0006) |
| [B0007 · 85–85](../../../../../tests/unit/reoptimization_churn_test.cpp#L85) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 86–95](../../../../../tests/unit/reoptimization_churn_test.cpp#L86) | Callable definition: int main(int argc,char** argv) | calls check, c05_independent::boolean_fixture, s04_runtime::options, c05_independent::lower; guard check(argc==2,"usage: reoptimization_churn SOURCE");const auto fixture=c05_independent::boolean_fix…; returns 0; 1; 2 loop sites · [reviewed contract](#b0008) |

## B0001

[Lines 1–13](../../../../../tests/unit/reoptimization_churn_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:264765d1eca68b6a87273804826ce9b3600b867d32603e0af4925de29ac85a49
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_churn_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "local_sink_fixture.hpp", "crown/io/compiler_plan_artifact.hpp", "crown/runtime/session_reoptimization.hpp", &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_churn_test.cpp](../../../../../tests/unit/reoptimization_churn_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–14](../../../../../tests/unit/reoptimization_churn_test.cpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SteadyMemory {std::uint64_t bytes,allocations;bool operator==(const SteadyMemory&) const=default;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the two fields compared for steady original-account memory across repeated candidate selection. |
| inputs / outputs | Fields are requested bytes after subtracting reported sink buffer bytes and the account allocation count. |
| invariants | Only sink buffer bytes are subtracted from requested-byte current; the allocation count remains whole-account and is not adjusted. |
| ownership | Plain value pair. |
| failure | No failure path. |
| cost | Constant-size comparison. |
| Design | [tests/unit/reoptimization_churn_test.cpp § struct SteadyMemory (lines 14-14)](../../../../../tests/unit/reoptimization_churn_test.cpp) |

## B0003

[Lines 15–17](../../../../../tests/unit/reoptimization_churn_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Options options(std::uint64_t round) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Vary caller forecast by round while disabling the minimum-epoch gap for the finite churn campaign. |
| inputs / outputs | Input round; sets gap zero and forecast current time 1,000,000+round×100 ns, target 1 ns, horizon UINT64_MAX. |
| invariants | Values are deterministic caller predictions; there are 16 rounds per run and four backend/mode runs. |
| ownership | Returns Options value. |
| failure | No failure path. |
| cost | Constant-time arithmetic for bounded round values. |
| Design | [tests/unit/reoptimization_churn_test.cpp § reoptimization::Options options(std::uint64_t round) (lines 15-17)](../../../../../tests/unit/reoptimization_churn_test.cpp), [include/crown/runtime/reoptimization.hpp § Forecast, Policy and Options (lines 11-61)](../../../../../include/crown/runtime/reoptimization.hpp), [docs/reoptimization.md § Policy units and boundaries (lines 42-57)](../../../../reoptimization.md) |

## B0004

[Lines 18–21](../../../../../tests/unit/reoptimization_churn_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void enqueue(QuerySession& session,const PhysicalSetUpdate& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Queue one exact wire-positioned physical update without beginning it. |
| inputs / outputs | Inputs session and PhysicalSetUpdate; builds one TransportBatch and requires accepted admission. |
| invariants | Sequence/source position come from the update; the caller controls barrier and execution. |
| ownership | The local TransportBatch copies the supplied update into an InputEvent. Accepted queue admission consumes its records into session-owned storage; this helper checks Admission::accepted but does not separately assert batch.empty(). |
| failure | Check fails unless admission is accepted. |
| cost | One-event batch and copy/admission cost for one row. |
| Design | [tests/unit/reoptimization_churn_test.cpp § void enqueue(QuerySession& session,const PhysicalSetUpdate& update) (lines 18-21)](../../../../../tests/unit/reoptimization_churn_test.cpp), [include/crown/runtime/session.hpp § enqueue API](../../../../../include/crown/runtime/session.hpp) |

## B0005

[Lines 22–25](../../../../../tests/unit/reoptimization_churn_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reference_update(QuerySession& session,const PhysicalSetUpdate& update,Outputs& output) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance the non-switching reference by one update and record its fully drained signed output. |
| inputs / outputs | Reference session, update and output map in; queues and begins the event, steps/commits via local_sink_test::finish, then separately drains next_output into the sequence-keyed signed set. |
| invariants | Checks output rows are unique within one sequence; fixture records exact output only, not timing. |
| ownership | Reference session owns native state; output map owns deep exported rows. |
| failure | Missing event or duplicate output fails; native exceptions propagate. |
| cost | One reference epoch plus a full ordinary output drain/copy. |
| Design | [tests/unit/reoptimization_churn_test.cpp § void reference_update(QuerySession& session,const PhysicalSetUpdate& update,Outputs& output) (lines 22-25)](../../../../../tests/unit/reoptimization_churn_test.cpp), [tests/support/local_sink_fixture.hpp § finish and output (lines 15-20)](../../../../../tests/support/local_sink_fixture.hpp) |

## B0006

[Lines 26–84](../../../../../tests/unit/reoptimization_churn_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run(const PhysicalPlan& original,const planner::CandidateSnapshot& family,const Database& initial,const PhysicalOptions& physical,DeltaMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run 16 alternating candidate switches with exact non-switching outputs, bounded generation/sink settings and a repeated-owner memory comparison. |
| inputs / outputs | Per round, prepares alternating candidate 1/0 before queueing two inputs: one table-1 erase/insert and one table-0 duplicate insert. Mirrors both on the reference, optionally pauses, freezes admission, advances with quantum 1 while delivering old-owner sink epochs, then configures counters, prepares artifact, publishes and retires history. Sixteen rounds produce 32 primary sequence numbers. |
| invariants | Each invocation has 16 rounds and 32 primary inputs under 32 MiB, two retained generations and 32 sink epochs. Starting at round 5, each selected candidate gets a baseline of current bytes minus reported sink buffer bytes and whole-account current allocations; later matching selections compare both. Buffer bytes still count toward peak/cap. Final release asserts current==control-purpose usage, not one controller allocation. |
| ownership | Session/reference owners share no runtime state; only switched session owns managed files and sink. Original query account funds native state; compiler account is separate; output maps own copied rows. |
| failure | Every round must verify two replays and exact accumulated signed-output maps, preserve pause/configuration/account/sink origin, and remove the preceding plan/checkpoint/WAL. Both the reference collector and local_sink_test::output assert signed-row insertion uniqueness. Final checks compare progress and snapshot sizes; selected recovery requires committed 32, matching progress, one row and origin header. |
| cost | One invocation performs 16 switches, 32 primary physical inputs and 32 mirrored reference inputs, with at most 10000 advance(1) calls per round before a verified break. Each advance/finish/delivery has its own native work; the loop is no CPU-time guarantee. Memory reads use cumulative peak and current usage, not per-switch attribution. |
| Design | [tests/unit/reoptimization_churn_test.cpp § void run(const PhysicalPlan& original,const planner::CandidateSnapshot& family,const Database& initial,const PhysicalOptions& physical,DeltaMode mode) (lines 26-84)](../../../../../tests/unit/reoptimization_churn_test.cpp), [src/runtime/session.cpp § publish_reoptimization (lines 1361-1413)](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § lock_generation_recovery and restore_locked_generation (lines 1093-1150)](../../../../../src/runtime/session.cpp), [src/io/compiler_plan_artifact.cpp § prepare and replay overloads (lines 23-54)](../../../../../src/io/compiler_plan_artifact.cpp), [tests/support/local_sink_fixture.hpp § finish and output (lines 15-20)](../../../../../tests/support/local_sink_fixture.hpp), [docs/reoptimization.md § Resource and failure verification (lines 296-304)](../../../../reoptimization.md) |

## B0007

[Lines 85–85](../../../../../tests/unit/reoptimization_churn_test.cpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L85:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_churn_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_churn_test.cpp](../../../../../tests/unit/reoptimization_churn_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 86–95](../../../../../tests/unit/reoptimization_churn_test.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the finite churn scenario across both physical backends and both delta modes. |
| inputs / outputs | Requires source root; loads Boolean fixture, constructs original plan per backend, then runs maintenance and delta modes. |
| invariants | Exactly four run calls yield 64 switches and 128 primary physical inputs, plus 128 corresponding reference inputs. The success-message input count excludes those reference operations. |
| ownership | Main owns source fixture and plans; each run owns independent sessions and temp files. |
| failure | Requires one path; std::exception prints and returns 1. |
| cost | Four 16-round campaigns, including selected recovery after historical-file deletion. |
| Design | [tests/unit/reoptimization_churn_test.cpp § int main(int argc,char** argv) (lines 86-95)](../../../../../tests/unit/reoptimization_churn_test.cpp), [tests/support/selection_independent_fixture.hpp § BooleanFixture and boolean_fixture (lines 111-157)](../../../../../tests/support/selection_independent_fixture.hpp), [CMakeLists.txt § reoptimization_churn registration (lines 704-709)](../../../../../CMakeLists.txt) |
