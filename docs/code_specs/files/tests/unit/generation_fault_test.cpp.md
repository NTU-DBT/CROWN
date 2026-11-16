# `tests/unit/generation_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/generation_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `75b7075a2d155098989e462550b3ecd3a07f223a26cc0c79b9295a0591111b0e`. 140 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/generation_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../tests/unit/generation_fault_test.cpp#L12) | Type/record definition: enum class Action |  · [reviewed contract](#b0002) |
| [B0003 · 13–18](../../../../../tests/unit/generation_fault_test.cpp#L13) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../tests/unit/generation_fault_test.cpp#L19) | Callable definition: void visit(bool done) noexcept | calls _exit · [reviewed contract](#b0004) |
| [B0005 · 20–22](../../../../../tests/unit/generation_fault_test.cpp#L20) | Callable definition: template&lt;class Decision&gt; Decision decision(bool done) const noexcept | calls ; returns result · [reviewed contract](#b0005) |
| [B0006 · 23–35](../../../../../tests/unit/generation_fault_test.cpp#L23) | Callable definition: static recovery::testing::GenerationDecision generation(const recovery::testing::GenerationEvent& event,void* context) noexcept | calls visit; returns result; source comment (unverified): // An after-success error cannot replace an unlink that already failed with · [reviewed contract](#b0006) |
| [B0007 · 36–40](../../../../../tests/unit/generation_fault_test.cpp#L36) | Callable definition: static jp::testing::FileDecision journal(const jp::testing::FileEvent& event,void* context) noexcept | calls visit; returns h.decision&lt;jp::testing::FileDecision&gt;(event.after) · [reviewed contract](#b0007) |
| [B0008 · 41–43](../../../../../tests/unit/generation_fault_test.cpp#L41) | Callable definition: static recovery::testing::FileDecision checkpoint(const recovery::testing::FileEvent& event,void* context) noexcept | calls visit; returns h.decision&lt;recovery::testing::FileDecision&gt;(event.after) · [reviewed contract](#b0008) |
| [B0009 · 44–44](../../../../../tests/unit/generation_fault_test.cpp#L44) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 45–48](../../../../../tests/unit/generation_fault_test.cpp#L45) | Type/record definition: struct Installed |  · [reviewed contract](#b0010) |
| [B0011 · 49–52](../../../../../tests/unit/generation_fault_test.cpp#L49) | declares types or opens a type body. |  · [reviewed contract](#b0011) |
| [B0012 · 53–56](../../../../../tests/unit/generation_fault_test.cpp#L53) | Callable definition: explicit Saved(Action action):f(false,1,action!=Action::enable),program(CompiledProgram::standalone(f.test.plan)) | calls f, program, CompiledProgram::standalone, update · [reviewed contract](#b0012) |
| [B0013 · 57–61](../../../../../tests/unit/generation_fault_test.cpp#L57) | Callable definition: QuerySession::Owner owner(Action action) | calls QuerySession::create_typed, start, QuerySession::restore_generation, recovery_options; returns value; value · [reviewed contract](#b0013) |
| [B0014 · 62–66](../../../../../tests/unit/generation_fault_test.cpp#L62) | Callable definition: void perform(Action action,QuerySession::Owner& value) | calls enable_generation, options, rotate_generation, QuerySession::restore_generation · [reviewed contract](#b0014) |
| [B0015 · 67–82](../../../../../tests/unit/generation_fault_test.cpp#L67) | Callable definition: void verify(Action action) | calls std::filesystem::exists, QuerySession::restore_generation, recovery_options, check; guard if(action==Action::enable){check(value-&gt;status().committed_sequence==0 && value-&gt;progress().sequenc…; growth insert, resize; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 83–83](../../../../../tests/unit/generation_fault_test.cpp#L83) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 84–87](../../../../../tests/unit/generation_fault_test.cpp#L84) | Callable definition: Hook trace(Action action) | calls saved, owner, installed, perform; guard check(!hook.order_violation,"root selected a pair before both files/names were synced");return hook;; returns hook · [reviewed contract](#b0017) |
| [B0018 · 88–106](../../../../../tests/unit/generation_fault_test.cpp#L88) | Callable definition: void io_faults() | calls trace, saved, descriptors, owner; guard check(failed \|\| (action==Action::rotate && hook.already_absent),"generation syscall error was ignor…; 3 loop sites · [reviewed contract](#b0018) |
| [B0019 · 107–119](../../../../../tests/unit/generation_fault_test.cpp#L107) | Callable definition: void crashes() | calls trace, saved, fork, check; guard Saved saved(action);const auto child=::fork();check(child&gt;=0,"generation fork failed");; 3 loop sites · [reviewed contract](#b0019) |
| [B0020 · 120–138](../../../../../tests/unit/generation_fault_test.cpp#L120) | Callable definition: void allocations() | calls saved, emplace, QuerySession::restore_generation, recovery_options; guard const auto account=value-&gt;get_deleter().account();check(allocations==account.statistics().successfu…; growth emplace; 2 loop sites · [reviewed contract](#b0020) |
| [B0021 · 139–139](../../../../../tests/unit/generation_fault_test.cpp#L139) | Closes surrounding scope/type. |  · [reviewed contract](#b0021) |
| [B0022 · 140–140](../../../../../tests/unit/generation_fault_test.cpp#L140) | Callable definition: int main(int argc,char** argv) | calls check, std::string_view, crashes, allocations; guard int main(int argc,char** argv){try{check(argc==2,"expected generation test mode");if(std::string_vi…; returns 1 · [reviewed contract](#b0022) |

## B0001

[Lines 1–11](../../../../../tests/unit/generation_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:f865672c7a169e91903125328a0c41a398ce6cbc756e71d3c0da59e3a9aa354a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare generation_fault_test.cpp: include "generation_fixture.hpp", "generation_file_probe.hpp", "journal_file_probe.hpp", "checkpoint_file_probe.hpp", "crown/api/error.hpp", &lt;cerrno&gt;, &lt;sys/wait.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–12](../../../../../tests/unit/generation_fault_test.cpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Action {enable,rotate,reopen}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select initial publication, rotation or selected-root recovery in the unified generation fault harness. |
| inputs / outputs | Three values feed Saved setup, session ownership and actual operation dispatch. |
| invariants | Each action starts from a different authority state; a failed enable may have no root, whereas rotate/reopen must preserve a valid old/new selected generation. |
| ownership | Plain by-value selector with no file ownership. |
| failure | Fixture callers use only declared values; invalid values are outside the harness contract. |
| cost | Fixed selector. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md) |

## B0003

[Lines 13–18](../../../../../tests/unit/generation_fault_test.cpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L18:sha256:5bb137d337302c055344cca020fbf3d75779478d4f7df44283fbc853440450b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare generation_fault_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 19–19](../../../../../tests/unit/generation_fault_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void visit(bool done) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance the unified syscall ordinal and optionally terminate at the selected before/after side. |
| inputs / outputs | Increments count on before events; matching count/crash/side invokes _exit77. |
| invariants | Generation, journal and checkpoint callbacks share the same Hook count, so a before/after pair uses one ordinal. |
| ownership | Mutates only the stack Hook; child process exit intentionally skips all C++ owner destructors. |
| failure | No exception path; this is process-termination injection, not a power-loss simulator. |
| cost | Fixed counter/condition work per event. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp) |

## B0005

[Lines 20–22](../../../../../tests/unit/generation_fault_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Decision> Decision decision(bool done) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a common short-transfer/error decision for each concrete file-test callback type. |
| inputs / outputs | Returns a default Decision, setting maximum_transfer and a selected EIO before/after result only on before events. |
| invariants | It neither advances count nor mutates native outcomes; the owning test wrapper applies the decision at the actual syscall seam. |
| ownership | Returns fixed test data by value and borrows this Hook. |
| failure | Noexcept fixed-value construction; injected production failures are observed by the surrounding operation. |
| cost | Constant work without heap allocation. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp) |

## B0006

[Lines 23–35](../../../../../tests/unit/generation_fault_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static recovery::testing::GenerationDecision generation(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe generation persistence ordering and configure root-operation failure/allocation barriers. |
| inputs / outputs | Calls visit, records already-absent candidate unlink and successful checkpoint-name sync, checks prerequisites before root link/rename, optionally denies later intercepted new and returns the configured decision. |
| invariants | An after-success injection cannot replace a native unlink that already returned ENOENT. Root publication must follow checkpoint and journal directory sync. Repeated read EINTR remains subject to the real owner quota. |
| ownership | Context borrows the Installed Hook. The allocation barrier changes this test thread’s global-new seam; it owns no root/sink authority itself. |
| failure | Callback is noexcept; crash uses _exit, ordinary I/O failure is returned as a decision. An ordering violation is recorded for a later test assertion. |
| cost | Fixed work at each event; allocation count is sampled before the root publication syscall, not a general allocator/RSS measurement. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0007

[Lines 36–40](../../../../../tests/unit/generation_fault_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static jp::testing::FileDecision journal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fold journal syscall events into the unified generation trace and record durable journal-name publication. |
| inputs / outputs | Calls visit; successful after sync_directory sets journal_synced, then returns the common FileDecision. |
| invariants | The ordering flag requires actual successful sync, not merely seeing a before event. Ordinals are shared with generation/checkpoint operations. |
| ownership | Borrows Hook through callback context; actual journal descriptor/lock remains in production File. |
| failure | Noexcept callback; configured errors/crash are delivered through the testing seam. |
| cost | Constant work per event. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp) |

## B0008

[Lines 41–43](../../../../../tests/unit/generation_fault_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static recovery::testing::FileDecision checkpoint(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fold checkpoint-file syscall events into the same failure/crash ordinal stream. |
| inputs / outputs | Calls visit and returns the common concrete checkpoint-file Decision. |
| invariants | This callback counts/checks actual checkpoint operations; checkpoint name-sync ordering is tracked by the generation callback’s target metadata. |
| ownership | Borrowed Hook context outlives registration; no payload is retained. |
| failure | Noexcept and no local catch; configured production errors propagate through the exercised owner. |
| cost | Constant work per event. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp) |

## B0009

[Lines 44–44](../../../../../tests/unit/generation_fault_test.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in generation_fault_test.cpp: struct Hook. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 45–48](../../../../../tests/unit/generation_fault_test.cpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register one unified Hook across the generation, journal and checkpoint-file testing seams. |
| inputs / outputs | Constructor installs three typed callbacks with the same context; destructor clears all three. |
| invariants | Only one lexical registration is used; cleanup restores null rather than an arbitrary previous registration. |
| ownership | Borrows Hook for the whole actual operation; normal exception unwinding clears all callbacks before Hook destruction. |
| failure | No production exception translation. _exit in a crash child intentionally bypasses this destructor. |
| cost | Six fixed registration/clearing calls across construction/destruction, with no file or heap work. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp) |

## B0011

[Lines 49–52](../../../../../tests/unit/generation_fault_test.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L52:sha256:0ce4289bd373907ef9c755f3d41602a43c4b85dd8f214782f1eef91360b60eb5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare generation_fault_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 53–56](../../../../../tests/unit/generation_fault_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Saved(Action action):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an ordered-backend self-join fixture and retain exact old selected bytes for one trial. |
| inputs / outputs | Builds Fixture(false,1,enable-as-needed) and a genuine standalone compiler; non-enable cases commit two updates and save generation1 checkpoint/WAL/root. |
| invariants | Every error/crash trial receives a fresh independent fixture; the original session is reset before another owner is acquired. |
| ownership | Saved owns the directory/fixture/compiler and copied historical strings. Destroying its original session releases actual locks before owner/verify calls. |
| failure | Any fixture setup/publication failure escapes; a baseline cannot be fabricated from a failed setup. |
| cost | For rotate/reopen, initial generation publication plus two native events and complete byte copies; enable case avoids that history. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp) |

## B0013

[Lines 57–61](../../../../../tests/unit/generation_fault_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner owner(Action action)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire the pre-operation session needed for enable or rotate, leaving reopen with an empty destination owner. |
| inputs / outputs | Enable creates/starts a typed owner; rotate restores generation1, discards replay output and starts; reopen returns empty. |
| invariants | Ownership setup occurs before Installed, so the traced perform operation has a reproducible boundary set. |
| ownership | Returns a real QuerySession::Owner retaining native/file/account state. The standalone compiler remains Saved-owned. |
| failure | Acquisition/replay/start errors propagate; no retry/catch is hidden in the fixture helper. |
| cost | Creation or complete selected recovery for the appropriate action; reopen selector itself is constant. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md) |

## B0014

[Lines 62–66](../../../../../tests/unit/generation_fault_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void perform(Action action,QuerySession::Owner& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Call exactly the concrete generation operation selected by the fault trial. |
| inputs / outputs | Enable attaches initial generation, rotate selects a new pair, reopen assigns a freshly restored owner. |
| invariants | Uses actual session APIs under the installed hooks; value is present for enable/rotate and initially empty for reopen. |
| ownership | Caller owns the reference to the session handle; successful reopen transfers the fresh owner into it. |
| failure | Production GenerationFailure/checkpoint/journal/account failures propagate to the trial without a fixture recovery layer. |
| cost | Actual bounded generation publication/replay I/O and native work; fixed dispatch adds no system design abstraction. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/generations.md](../../../../generations.md) |

## B0015

[Lines 67–82](../../../../../tests/unit/generation_fault_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(Action action)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reopen actual selected state after one generation fault/crash and check output plus the next update. |
| inputs / outputs | Enable allows an absent root; a present enable root is restored and checked for C=I=0 with empty rows, then returns. Only rotate/reopen validate selected generation1/2, epoch/progress2, history bytes, generation-dependent replay output and event3 against the independent oracle. |
| invariants | For rotate/reopen, old selection returns its missing epoch2 output and new selection returns none predating its checkpoint; both recover the same state/source and permit the exact next update. Enable verifies only its separate zero-epoch branch. |
| ownership | Acquires a new healthy owner only after the exercised owner is released. Saved strings/compiler remain independent; returned output rows are consumed before next input. |
| failure | Any invalid root/pair/output/history/progress/next-state check fails; this helper does not accept a DTO as a substitute for restore. |
| cost | Enable does no restore if no root survived, otherwise one zero-state restore. Rotate/reopen add full historical-file comparisons, output drain and one native/reference event. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0016

[Lines 83–83](../../../../../tests/unit/generation_fault_test.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L83:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in generation_fault_test.cpp: struct Saved. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 84–87](../../../../../tests/unit/generation_fault_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Hook trace(Action action)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count the actual successful unified syscall boundaries for one concrete generation action. |
| inputs / outputs | Constructs Saved and an appropriate owner, installs a default Hook, performs the action and returns the fixed counter/flags. |
| invariants | Rejects any ordering flag showing root selection before both candidate names are synced. It covers the chosen ordered-backend fixture, not all program configurations. |
| ownership | Hook registration ends before return; Saved/session lexical owners close normally. |
| failure | Baseline errors or order violation abort instead of authorizing a partial trace. |
| cost | One setup/publication/replay baseline plus constant Hook return. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md) |

## B0018

[Lines 88–106](../../../../../tests/unit/generation_fault_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void io_faults()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep every observed generation I/O error side, allowed absent cleanup, short transfer and bounded repeated interruption. |
| inputs / outputs | For enable/rotate/reopen, rebuilds each trial, injects EIO at each unified ordinal on both sides, checks recovery-required admission blocking, drops owners and verifies actual old/new recovery. |
| invariants | A rotate after-event on already-absent ENOENT cleanup may succeed; all other selected errors must reject. Repeated root-read EINTR hits the finite operation limit without changing the authoritative root. |
| ownership | Hook and owning sessions remain trial-local. Reset releases actual root/log descriptors before Saved.verify obtains fresh locks. |
| failure | Accepts only the named generation/checkpoint/journal failures, or the specific already-absent case. No resource failure is silently converted into semantic success. |
| cost | Two complete trials per observed ordinal per action plus short-I/O and EINTR controls; each includes full fixture and native reopen costs. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp) |

## B0019

[Lines 107–119](../../../../../tests/unit/generation_fault_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void crashes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Terminate a child before/after every successful-baseline generation operation and verify surviving authority in the parent. |
| inputs / outputs | For each action and unified ordinal/side, forks, installs the crash hook around perform, checks exit77 and calls Saved.verify. |
| invariants | Unexpected child exception exits3; an unreached boundary exits4. This proves process-exit behavior under the local filesystem assumptions, not power-loss persistence. |
| ownership | Parent owns fixture history and verification; child owns its acquired session until _exit bypasses cleanup. Parent uses a fresh restored owner afterward. |
| failure | Fork/wait/status or survivor mismatch fails the test; no file repair occurs before actual restore validation. |
| cost | Two child processes per observed ordinal for three actions, with full setup/replay and independent next-state checks. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md) |

## B0020

[Lines 120–138](../../../../../tests/unit/generation_fault_test.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocations()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep receiving reconstruction allocation cuts and check no intercepted C++ new after root selection begins. |
| inputs / outputs | Measures restore new/account counts and peak, injects each observed bad_alloc, tries exact/one-under receiving caps, then arms the allocation barrier before enable/rotate root link/rename. |
| invariants | Failed receive releases descriptors and leaves selected root/WAL bytes intact. Barrier success preserves the count sampled before root publication; this includes the hook’s ordinary/aligned/nothrow overloads, not direct libc/exception ABI. |
| ownership | Each receiving owner closes before the next trial; the barrier is scoped with Installed and s04_alloc::Scope so thread-local interception resets on ordinary exit. |
| failure | Expected injected bad_alloc and MemoryFault::limit are checked separately; root-order or later new-attempt evidence fails the fixture. |
| cost | One full restore per measured allocation cut plus exact/under and two publication controls. Requested-account peak and attempt counts remain separate metrics. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0021

[Lines 139–139](../../../../../tests/unit/generation_fault_test.cpp#L139); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L139-L139:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in generation_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 140–140](../../../../../tests/unit/generation_fault_test.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch generation process-exit coverage or receiving/I/O fault coverage. |
| inputs / outputs | Requires one mode argument; literal crash runs crashes, every other value runs allocations then io_faults. |
| invariants | The fixture uses the ordered physical backend in this executable; the separate generation_test matrix covers both backends. |
| ownership | All hook/session/path owners are group-local and release on normal/exceptional exit. |
| failure | Final std::exception catch prints a diagnostic and returns one; successful completion uses implicit zero. |
| cost | Fixed dispatch plus the selected finite sweeps; this inspection pass does not execute them. |
| Design | [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp), [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp) |
