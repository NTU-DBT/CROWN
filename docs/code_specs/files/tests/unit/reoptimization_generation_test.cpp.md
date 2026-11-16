# `tests/unit/reoptimization_generation_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_generation_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ce2b59217792bef0db2c00a0a9042fb6c1bfe3b3ce23d4e7277f9614918dc753`. 173 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/reoptimization_generation_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 19–19](../../../../../tests/unit/reoptimization_generation_test.cpp#L19) | Type/record definition: enum class Action |  · [reviewed contract](#b0002) |
| [B0003 · 20–23](../../../../../tests/unit/reoptimization_generation_test.cpp#L20) | Callable definition: template&lt;class Function&gt; GenerationFailure rejected(Function&& function) | calls function, std::runtime_error; returns failure · [reviewed contract](#b0003) |
| [B0004 · 24–30](../../../../../tests/unit/reoptimization_generation_test.cpp#L24) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 31–36](../../../../../tests/unit/reoptimization_generation_test.cpp#L31) | Callable definition: explicit Files(bool delivery=false) | calls emplace, publish_checkpoint, publish_plan, selection; growth emplace · [reviewed contract](#b0005) |
| [B0006 · 37–40](../../../../../tests/unit/reoptimization_generation_test.cpp#L37) | Callable definition: GenerationRoot selection(std::uint64_t generation) const | calls sha256_fixed; returns result · [reviewed contract](#b0006) |
| [B0007 · 41–41](../../../../../tests/unit/reoptimization_generation_test.cpp#L41) | Callable definition: std::string path(std::uint64_t generation,std::string_view suffix) const | calls generation_test::path; returns generation_test::path(root,generation,suffix) · [reviewed contract](#b0007) |
| [B0008 · 42–46](../../../../../tests/unit/reoptimization_generation_test.cpp#L42) | Callable definition: void prepare(Action action) | calls prepare_next, publish_checkpoint, publish_plan · [reviewed contract](#b0008) |
| [B0009 · 47–51](../../../../../tests/unit/reoptimization_generation_test.cpp#L47) | Callable definition: void perform(Action action) | calls publish_plan, publish_root, selection, read_plan · [reviewed contract](#b0009) |
| [B0010 · 52–57](../../../../../tests/unit/reoptimization_generation_test.cpp#L52) | Callable definition: void recover() | calls reset, emplace, selected, check; guard check(generation==1 \|\| generation==2,"uncertain root selected an unknown generation");; growth emplace · [reviewed contract](#b0010) |
| [B0011 · 58–58](../../../../../tests/unit/reoptimization_generation_test.cpp#L58) | Closes surrounding scope/type. |  · [reviewed contract](#b0011) |
| [B0012 · 59–76](../../../../../tests/unit/reoptimization_generation_test.cpp#L59) | Callable definition: void codec_and_binding() | calls f, contents, selected, check; guard check(bytes.size()==(delivery?generation_root_plan_delivery_size:generation_root_plan_size) &&; 3 loop sites · [reviewed contract](#b0012) |
| [B0013 · 77–97](../../../../../tests/unit/reoptimization_generation_test.cpp#L77) | Callable definition: void resource_and_corruption() | calls statistics, reset, CompiledProgram::standalone, window_checkpoint_test::plan; guard check(denied.fault()==GenerationFault::binding && denied.stage()==GenerationStage::state,"caller-se…; growth emplace · [reviewed contract](#b0013) |
| [B0014 · 98–108](../../../../../tests/unit/reoptimization_generation_test.cpp#L98) | Type/record definition: struct Hook | returns result · [reviewed contract](#b0014) |
| [B0015 · 109–112](../../../../../tests/unit/reoptimization_generation_test.cpp#L109) | Type/record definition: struct Installed |  · [reviewed contract](#b0015) |
| [B0016 · 113–113](../../../../../tests/unit/reoptimization_generation_test.cpp#L113) | Callable definition: std::uint64_t call_count(Action action) | calls prepare, scope, perform; returns hook.calls · [reviewed contract](#b0016) |
| [B0017 · 114–139](../../../../../tests/unit/reoptimization_generation_test.cpp#L114) | Callable definition: void faults_and_crashes(bool crash) | calls call_count, prepare, contents, descriptors; guard const auto pid=::fork();check(pid&gt;=0,"descriptor crash fork failed");; 3 loop sites · [reviewed contract](#b0017) |
| [B0018 · 140–164](../../../../../tests/unit/reoptimization_generation_test.cpp#L140) | Callable definition: void retirement() | calls prepare, publish_root, selection, window_checkpoint_test::plan; guard check(encoded.size()==detail::retirement_plan_intent_size && static_cast&lt;unsigned char&gt;(encoded.dat…; growth emplace · [reviewed contract](#b0018) |
| [B0019 · 165–165](../../../../../tests/unit/reoptimization_generation_test.cpp#L165) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 166–173](../../../../../tests/unit/reoptimization_generation_test.cpp#L166) | Callable definition: int main(int argc,char** argv) | calls check, std::string_view, faults_and_crashes, codec_and_binding; guard check(argc==2,"usage: reoptimization_generation faults\|crash");; returns 0; 1 · [reviewed contract](#b0020) |

## B0001

[Lines 1–18](../../../../../tests/unit/reoptimization_generation_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:e414fbaca64b640bb96f1cbf544a7d818d6f388a584be61105bc367e586380b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_generation_test.cpp: include "history_retirement_fixture.hpp", "generation_file_probe.hpp", &lt;cerrno&gt;, &lt;sys/wait.h&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–19](../../../../../tests/unit/reoptimization_generation_test.cpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Action {plan,select,read};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the three operations exercised by the low-level generation owner fixture. |
| inputs / outputs | Defines Action values plan, select, and read for the test dispatch. |
| invariants | The enum is a local test selector; plan bytes and checkpoint bytes in this file are opaque literals, not a valid compiler artifact or runtime checkpoint. |
| ownership | No runtime or file handle is owned by the enum. |
| failure | No failure behavior. |
| cost | Fixed enum value only. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0003

[Lines 20–23](../../../../../tests/unit/reoptimization_generation_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> GenerationFailure rejected(Function&& function) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a low-level generation operation to reject with GenerationFailure and return its typed details. |
| inputs / outputs | Invokes the supplied callable and returns the caught GenerationFailure; success throws runtime_error. |
| invariants | Only GenerationFailure is treated as the expected rejection; other exceptions propagate. |
| ownership | The returned exception object carries fault/stage/outcome values; the callable is borrowed for the call. |
| failure | Unexpected success fails; unrelated exception types propagate. |
| cost | One callable invocation and exception branch; underlying file work depends on the operation. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0004

[Lines 24–30](../../../../../tests/unit/reoptimization_generation_test.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L30:sha256:4718b62ff83247898e5882f5ee87a3a2c8478aece9eae035018c2d879555931d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_generation_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. This filesystem Directory member owns the fixture namespace; its constructor/cleanup follows the documented filesystem effects of its helper type. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. This span declares a filesystem Directory member; its fixture construction/cleanup can perform filesystem I/O outside the native query account. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 31–36](../../../../../tests/unit/reoptimization_generation_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  explicit Files(bool delivery=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a temporary root owner with generation-1 literal descriptor/checkpoint files. |
| inputs / outputs | Constructs temp directory, 8 MiB account, root name, query ID, limits and optional GenerationOwner; publishes generation 1 checkpoint and literal plan, then root; optional delivery anchor has fixed sink ID/sequence 0/148 bytes/hash. |
| invariants | The plan/checkpoint strings are intentionally opaque fixture bytes. The owner retains lock/root state; they do not represent a loadable QuerySession image/compiler artifact. |
| ownership | Directory and optional GenerationOwner own filesystem/lock resources; account is used for explicit plan reads. |
| failure | File creation/publication errors propagate as GenerationFailure or filesystem/test exceptions. |
| cost | Creates and durably publishes a root, checkpoint and plan; filesystem writes, hashes, syncs, lock setup and allocations are fixture setup costs. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0006

[Lines 37–40](../../../../../tests/unit/reoptimization_generation_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  GenerationRoot selection(std::uint64_t generation) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct expected GenerationRoot metadata for generation 1 or 2. |
| inputs / outputs | Returns query ID, requested generation, first generation 1, matching literal checkpoint/plan hashes, zero physical/command sequence, and no delivery anchor in this helper result. |
| invariants | The selected generation determines which literal hashes are expected; this is fixture metadata, not a decoded runtime image. |
| ownership | Returns a fixed value; no owner is retained. |
| failure | No helper-specific failure branch. |
| cost | Fixed metadata/hash selection and value construction; hash inputs are small literals. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0007

[Lines 41–41](../../../../../tests/unit/reoptimization_generation_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::string path(std::uint64_t generation,std::string_view suffix) const {return generation_test::path(root,generation,suffix);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a generation sibling path for a requested suffix. |
| inputs / outputs | Delegates root, generation and suffix to generation_test::path and returns a string. |
| invariants | Only path naming is covered; this helper does not open or validate the result. |
| ownership | Returned std::string owns its bytes. |
| failure | Underlying path helper/allocation failures propagate. |
| cost | Formats one generation path; string allocation depends on path length. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0008

[Lines 42–46](../../../../../tests/unit/reoptimization_generation_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void prepare(Action action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare operation-specific generation-2 candidate files before a faulted action. |
| inputs / outputs | For plan/select, prepares next generation and publishes literal checkpoint; for select also publishes literal plan; read performs no preparation. |
| invariants | Preparation never selects generation 2. Action::plan leaves publication of its plan to perform(); select has all candidate files before root selection. |
| ownership | GenerationOwner retains the lock/candidate bookkeeping; fixture owns literal strings/path names. |
| failure | Generation file, limit, or state failures propagate. |
| cost | May remove the immediate unselected candidate names and sync the directory, then writes/syncs checkpoint and optionally plan. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0009

[Lines 47–51](../../../../../tests/unit/reoptimization_generation_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void perform(Action action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform the selected literal plan, root-selection, or plan-read operation. |
| inputs / outputs | Plan publishes generation-2 literal plan; select publishes expected generation-2 root; read loads the selected plan into the fixture account. |
| invariants | Only select attempts authority-bearing root replacement; plan/read do not select a new root. These are direct GenerationOwner operations, not QuerySession migration. |
| ownership | GenerationOwner retains root lock; read result is a temporary account-backed buffer discarded by the cast-to-void. |
| failure | GenerationFailure and allocation errors propagate to caller/fault harness. |
| cost | Plan/root writes use durable file operations; read checks metadata, reads bytes, hashes and account-allocates a buffer. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0010

[Lines 52–57](../../../../../tests/unit/reoptimization_generation_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void recover() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reopen the root after an injected operation and verify the selected opaque descriptor is recoverable. |
| inputs / outputs | Drops/recreates owner, requires selected generation 1 or 2, reads the corresponding plan and checks literal equality; also checks generation-1 plan and checkpoint bytes unchanged. |
| invariants | Permitted selection is either old or new only for ambiguous root-selection outcomes; no third root is accepted. This is not native session recovery. |
| ownership | Resets the old owner before reopening; the new owner holds the root lock until fixture destruction. Read buffer is temporary. |
| failure | Unknown generation, wrong plan, changed original plan/checkpoint or file errors fail. |
| cost | Drops/reopens lock owner, reads/hashes the selected plan and compares source bytes plus two original files. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0011

[Lines 58–58](../../../../../tests/unit/reoptimization_generation_test.cpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L58:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_generation_test.cpp: struct Files. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 59–76](../../../../../tests/unit/reoptimization_generation_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void codec_and_binding() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check generation-root v3 shape, every truncation/byte mutation, descriptor binding, and root publication with the allocator probe denied. |
| inputs / outputs | Runs with and without a delivery anchor; checks exact encoded size/version/flags and roundtrip selection; tests all shorter prefixes and flips every encoded byte; then exercises unpublished plan, wrong hash, missing lineage, and publishes correct root under s04_alloc denial. |
| invariants | Every tested truncated or single-byte-mutated root is expected to throw GenerationFailure in these two fixture variants. Root selection requires matching candidate plan generation/hash and retains lineage; selection is validated after publication. |
| ownership | Root owner and fixture directory remain alive through checks; changed strings are local copies. |
| failure | Malformed/binding cases must reject; any accepted mutation or changed selected metadata fails. |
| cost | Loops over each byte of the fixed root encoding (with an inner clone/flip/check); then performs several candidate publication and file-inspection operations. This finite byte sweep does not prove parser behavior for all inputs. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0013

[Lines 77–97](../../../../../tests/unit/reoptimization_generation_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void resource_and_corruption() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify account-owned plan reads, corruption/limit rejection, and cleanup of only an immediate unselected candidate. |
| inputs / outputs | Checks legacy caller-selected restore rejects a v3 descriptor root; reads plan into the supplied account and checks owner/requested-byte growth then release; rejects tamper and one-byte-under plan cap, accepts exact cap, and cleans generation-2 orphan plan/checkpoint/WAL on prepare_next. |
| invariants | The byte/account assertions concern this selected literal plan buffer only. Corrupt descriptor bytes remain untouched after failed read; cleanup keeps selected generation-1 plan. Exact plan grant is accepted. |
| ownership | Read result uses the supplied MemoryAccount allocator and releases its requested bytes when the local buffer dies; GenerationOwner owns lock and file handles. |
| failure | Restore/read failures are checked as binding, limit, or read rejection; failed reads do not repair tampered bytes. |
| cost | Reads/hash-compares the selected file, checks account statistics, reads/writes literal files, and unlinks up to three immediate candidate names with directory sync; no CPU/RSS bound. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0014

[Lines 98–108](../../../../../tests/unit/reoptimization_generation_test.cpp#L98); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Hook {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture before/after generation syscall events and inject selected I/O errors or child-process exits. |
| inputs / outputs | Counts before events, optionally calls _exit(77) at a selected ordinal/side, and returns an error_before/error_after decision when configured ordinal matches. |
| invariants | Ordinal increments only for before events; error injection can target before or after callback; events carry stage/target/result/native error. |
| ownership | The hook context pointer is borrowed while installed. |
| failure | Hook is noexcept and expresses injected error/crash through decision or process exit, not an exception. |
| cost | One event callback and fixed-field tests; actual syscall count/work is driven by GenerationOwner operations. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0015

[Lines 109–112](../../../../../tests/unit/reoptimization_generation_test.cpp#L109); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install and clear the generation callback for one scoped test interval. |
| inputs / outputs | Constructor registers Hook::visit; destructor unregisters callback/context. |
| invariants | Hook must outlive the installed scope. The registration is thread-local; destruction sets it to null instead of restoring a prior callback, so nested installations through this helper are unsupported. |
| ownership | Borrows Hook as callback context. Installed owns neither Hook nor any previous thread-local callback registration. |
| failure | No helper failure channel beyond registration API behavior. |
| cost | Two callback registration operations and scope lifetime bookkeeping. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0016

[Lines 113–113](../../../../../tests/unit/reoptimization_generation_test.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t call_count(Action action) {Files f;f.prepare(action);Hook hook;{Installed scope(hook);f.perform(action);}return hook.calls;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure the actual hook boundary count for one plan/select/read action. |
| inputs / outputs | Creates and prepares Files, installs a nonfailing Hook around perform, and returns its before-event count. |
| invariants | The count is measured from actual callback visits for this source/build/runtime path; it is not a hard-coded syscall or cross-platform guarantee. |
| ownership | Files owns its root lock and temporary tree through the call; Hook is local and unregistered before return. |
| failure | Preparation or operation failure propagates. |
| cost | Performs the requested operation once and increments a scalar per before event. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0017

[Lines 114–139](../../../../../tests/unit/reoptimization_generation_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void faults_and_crashes(bool crash) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep every observed before/after fault or crash boundary for the three GenerationOwner operations. |
| inputs / outputs | For plan, select, and read, obtains call_count then creates a fresh Files fixture for each ordinal and before/after side. I/O mode injects GenerationFailure and checks uncertainty or old-root retry; crash mode forks and requires child exit 77. Each parent reopens/recover-checks and verifies descriptor count. |
| invariants | Cut count is runtime-derived as 2×sum(call_count(action)) for the three operations in the current profile. There is no positive-count assertion, so an action reporting zero before-events runs no cut trials. For non-select actions root bytes stay unchanged; selection uncertainty is latched and requires reopen. Recovery accepts only old/new descriptor, and the generation-1 plan/checkpoint remain. |
| ownership | Each trial owns a fresh directory/root owner; crash child shares the filesystem after fork but exits without normal cleanup; parent reopens after wait. |
| failure | Missed hook, wrong uncertainty state, root change outside select, leaked descriptor, failed recovery, or changed original file fails. |
| cost | Per action it computes one baseline count, then runs both sides at each observed boundary with fresh file setup; crash mode adds fork/wait. This is a finite injected cut sweep, not power-loss hardware or a universal syscall proof. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0018

[Lines 140–164](../../../../../tests/unit/reoptimization_generation_test.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retirement() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test root retirement binding and preservation of the current self-contained descriptor. |
| inputs / outputs | Selects generation 2; builds a runtime image solely to form a sink header/receipt fixture; validates v2 intent hash/shape, rejects bad checksum, foreign selected plan hash, and tampered current plan, then retires and reopens. |
| invariants | This low-level fixture uses opaque plan/checkpoint literals; it does not construct a real CompilerPlanArtifact or restore a QuerySession. Successful retirement advances first_generation to 2, deletes only generation-1 plan/checkpoint/WAL, keeps generation-2 plan and lineage, and allows its plan bytes to be read. |
| ownership | GenerationOwner owns root lock; sink File and runtime are fixture-scoped; plan-read buffer is account-owned and temporary. |
| failure | Checksum/binding/corrupt descriptor cases reject without deleting recovery history; successful retirement must preserve current selection. |
| cost | Encodes/inspects intent, opens sink fixture, rereads and hashes selected descriptor, writes retirement intent, unlinks old files and syncs; these are file/hash costs, not a time guarantee. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0019

[Lines 165–165](../../../../../tests/unit/reoptimization_generation_test.cpp#L165); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L165-L165:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_generation_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 166–173](../../../../../tests/unit/reoptimization_generation_test.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch low-level generation descriptor fault tests by argument. |
| inputs / outputs | Requires argc 2. Exact argument crash invokes only crash cuts; every other value runs codec/binding, resource/corruption, retirement and I/O fault cuts. |
| invariants | Unknown non-crash text is not rejected; it selects the ordinary/fault path. Crash mode skips codec/resource/retirement and uses only process-exit sweep. |
| ownership | All fixture resources are scoped to called functions. |
| failure | std::exception prints to stderr and returns 1; success returns 0. |
| cost | Dispatches finite fixture routines; emitted cut counts are generated at runtime from hook counts. No native test execution claim is made here. |
| Design | [tests/unit/reoptimization_generation_test.cpp](../../../../../tests/unit/reoptimization_generation_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/history_retirement_fixture.hpp](../../../../../tests/support/history_retirement_fixture.hpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |
