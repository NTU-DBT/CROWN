# `tests/unit/sql_aggregate_session_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `b1daa92f1323363bb287b061545a06b4e4b07a9c0f34f6acf58051c1e4be9ebb`. 170 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L8) | Type/record definition: enum class Mode |  · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L9) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 10–13](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L10) | Callable definition: void log(ar::Session& s,bool reject=false) | calls  · [reviewed contract](#b0004) |
| [B0005 · 14–14](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L14) | Explanatory comments or spacing. | source comment (unverified): // Reset only this fixture's disposable namespace after all owners release locks. · [reviewed contract](#b0005) |
| [B0006 · 15–23](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L15) | Callable definition: void prepare(Fixture& f,Mode mode,std::optional&lt;ar::Session&gt;& owner) | calls reset, std::filesystem::directory_iterator, std::filesystem::remove_all, path; guard assert(!owner-&gt;decide().rejected);if(mode==Mode::deliver)return;; growth emplace; 1 loop sites; source comment (unverified): // Reset only this fixture's disposable namespace after all owners release locks. · [reviewed contract](#b0006) |
| [B0007 · 24–27](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L24) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Capture bytes only after a genuine baseline owner closes. Restoring a · [reviewed contract](#b0007) |
| [B0008 · 28–30](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L28) | Callable definition: Namespace capture(const Fixture& f) | calls std::filesystem::directory_iterator, emplace_back, path, string; returns result; growth emplace_back; 1 loop sites; source comment (unverified): // Capture bytes only after a genuine baseline owner closes. Restoring a · [reviewed contract](#b0008) |
| [B0009 · 31–35](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L31) | Callable definition: void restore(Fixture& f,const Namespace& image,Mode mode,std::optional&lt;ar::Session&gt;& owner) | calls reset, std::filesystem::directory_iterator, std::filesystem::remove_all, path; growth emplace; 2 loop sites · [reviewed contract](#b0009) |
| [B0010 · 36–46](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L36) | Callable definition: void perform(Fixture& f,Mode mode,std::optional&lt;ar::Session&gt;& owner) | calls emplace, create, recover, log; guard case Mode::commit:assert(!owner-&gt;decide().rejected);break;; growth emplace · [reviewed contract](#b0010) |
| [B0011 · 47–48](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L47) | Explanatory comments or spacing. | source comment (unverified): // Reopen the authoritative files after releasing the failed owner. Complete · [reviewed contract](#b0011) |
| [B0012 · 49–59](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L49) | Callable definition: void surviving(Fixture& f,Mode mode) | calls std::filesystem::exists, assert, recover, state; guard if(!std::filesystem::exists(f.root)) {assert(mode==Mode::create);return;}; source comment (unverified): // Reopen the authoritative files after releasing the failed owner. Complete · [reviewed contract](#b0012) |
| [B0013 · 60–62](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L60) | Explanatory comments or spacing. | source comment (unverified): // Inject before every observed call and after supported successful effects; · [reviewed contract](#b0013) |
| [B0014 · 63–97](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L63) | Callable definition: void io_matrix() | calls statistics, sql_aggregate_file_test::descriptors, prepare, reset; guard assert(failed);; growth emplace; 3 loop sites; source comment (unverified): // Inject before every observed call and after supported successful effects; · [reviewed contract](#b0014) |
| [B0015 · 98–99](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L98) | Explanatory comments or spacing. | source comment (unverified): // From the first append stamp through confirmed native/progress publication, · [reviewed contract](#b0015) |
| [B0016 · 100–120](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L100) | Callable definition: void prepaid_publication() | calls prepare, installed, perform, assert; guard {Installed installed(hook);s04_alloc::Scope allocations;perform(f,mode,owner);assert(hook.armed && …; 2 loop sites; source comment (unverified): // From the first append stamp through confirmed native/progress publication, · [reviewed contract](#b0016) |
| [B0017 · 121–124](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L121) | Explanatory comments or spacing. | source comment (unverified): // Each covered allocation in live preparation/log funding and cold recovery can · [reviewed contract](#b0017) |
| [B0018 · 125–149](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L125) | Callable definition: void allocation_cuts() | calls prepare, reset, capture, restore; guard assert(failed && contents(wal)==prior && contents(f.sink)==sink);; 2 loop sites; source comment (unverified): // Each covered allocation in live preparation/log funding and cold recovery can · [reviewed contract](#b0018) |
| [B0019 · 150–151](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L150) | Explanatory comments or spacing. | source comment (unverified): // Root-validation failures invalidate the owner; failure deleting/syncing only · [reviewed contract](#b0019) |
| [B0020 · 152–168](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L152) | Callable definition: void root_retry_boundaries() | calls prepare, installed, perform, reset; guard if(root_read) {validation=true;assert(owner-&gt;requires_reopen());}; 1 loop sites; source comment (unverified): // Root-validation failures invalidate the owner; failure deleting/syncing only · [reviewed contract](#b0020) |
| [B0021 · 169–169](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L169) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0021) |
| [B0022 · 170–170](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L170) | Callable definition: int main() | calls io_matrix, prepaid_publication, allocation_cuts, root_retry_boundaries · [reviewed contract](#b0022) |

## B0001

[Lines 1–7](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:ef6427bdda25e129ab2b1ad7582848d58e0b9e7666580d9ebf14f0b8e356ae8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_session_fault_test.cpp: include "sql_aggregate_session_probe.hpp", &lt;iostream&gt;, &lt;sys/wait.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–8](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Mode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select one of seven real Session lifecycle operations in the fault harness. |
| inputs / outputs | A fixed test-only create/log/commit/reject/deliver/checkpoint/recover tag selects matching prepare, perform and surviving assertions. |
| invariants | Mode is not a persisted wire tag or a product error category. Each matrix baseline and injected repeat uses the same operation; source/native/file authority still comes from genuine factories. |
| ownership | Fixed enum value; no account, FD, namespace image or mutable database ownership. |
| failure | Adding an enumerator requires updating the exhaustive perform switch and fixture/recovery expectations; compiler warnings and runtime assertions expose an incomplete dispatch. |
| cost | Fixed test dispatch only; no product field or per-row runtime operation. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0003

[Lines 9–9](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::array<Cell,2> row{Cell{},number(5)};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the SQL aggregate Session fault test’s fixed row at translation-unit initialization. |
| inputs / outputs | Initializes a const two-Cell array before main; its second Cell calls the test helper number(5), and log() later uses this row in SourceReplacement. |
| invariants | This is a test fixture global, not a production aggregate startup action; one fixed row is reused by the fault-mode helpers. |
| ownership | The anonymous-namespace array has static lifetime and owns its Cell values. |
| failure | No local catch surrounds the initializer; an exceptional static initialization failure prevents normal test startup. The called number(5) helper constructs the fixed numeric ScalarView value. |
| cost | Two fixed Cell/ScalarView values constructed once per process; no input-sized data is created. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), tests/unit/sql_aggregate_session_fault_test.cpp:9-9 |

## B0004

[Lines 10–13](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void log(ar::Session& s,bool reject=false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append the fixed first test command, optionally arranged to fail the native before-weight check. |
| inputs / outputs | Session and Reject selector in; one logged physical replacement with source/reader progress out. |
| invariants | The non-Reject case changes an absent row from weight 0 to 1; the Reject case records an intentionally false before weight. It does not call decide. |
| ownership | Row/edit buffers are local borrowed input; Session owns the encoded pending command after log returns. |
| failure | Actual Session/File errors propagate. |
| cost | One small Input encode and real WAL append. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0005

[Lines 14–14](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L14:sha256:e0f9b8e11d74368a1bf1d479f7d784698e8dc6efbfe98a80d8aa4c1aa6af0980
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Reset only this fixture's disposable namespace after all owners release locks. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 15–23](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare(Fixture& f,Mode mode,std::optional<ar::Session>& owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset the fixture namespace after releasing locks and create the exact starting files/state for one fault-test mode. |
| inputs / outputs | Fixture, mode and optional owner in; fresh empty/create, logged, committed, rejected, delivered, checkpoint-ready or deliberately torn recovery state out. |
| invariants | All deletion/mutation is confined to the fixture directory. The owner is released before files are removed. Recovery mode starts from a real committed/delivered history with incomplete WAL and sink suffixes. |
| ownership | Fixture owns the disposable directory; the optional Session owns live locks only for modes that retain an owner. |
| failure | Filesystem, assertion and real Session failures propagate. |
| cost | Recreates a small local history of at most one command and one group epoch, plus any selected torn suffix. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0007

[Lines 24–27](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L27:sha256:9928baf6ba7ec55adab5b9df0c10b8fba662ff09cceaaf01e765a720fecad70a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_session_fault_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 28–30](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Namespace capture(const Fixture& f)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture the exact byte contents and paths in a disposable fixture namespace after its genuine baseline owner has closed. |
| inputs / outputs | Fixture directory in; test-owned vector of path/byte-string pairs out. |
| invariants | Captures actual files only; the image contains no native state, receipt or authority. It is used to reproduce the same filesystem starting point before fault attempts. |
| ownership | Returns owning ordinary test strings independent of the directory reads. |
| failure | Directory iteration, file read or string allocation failure propagates. |
| cost | O(number of fixture files + total captured bytes), with storage equal to the copied namespace. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/sql_aggregate_file_fixture.hpp](../../../../../tests/support/sql_aggregate_file_fixture.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0009

[Lines 31–35](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void restore(Fixture& f,const Namespace& image,Mode mode,std::optional<ar::Session>& owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore one captured fixture namespace byte-for-byte and reconstruct the genuine live Session needed by the selected operation. |
| inputs / outputs | Fixture, captured path/bytes, mode and optional owner in; exact filesystem baseline and, except for create/recover modes, an owner returned by real recovery out. |
| invariants | The namespace copy resets only disposable fixture files after releasing owner locks. Modes that need a live Session call f.recover() after restoring bytes; copied files are never treated as native state or a receipt shortcut. |
| ownership | Fixture directory owns restored files; optional Session owns actual locks/runtime after the genuine reopen. |
| failure | Filesystem writes or genuine recovery failures propagate. |
| cost | O(captured file count + total bytes) to remove/rewrite, plus one actual recovery for modes requiring a live owner. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0010

[Lines 36–46](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void perform(Fixture& f,Mode mode,std::optional<ar::Session>& owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the single operation selected by the fault-matrix mode. |
| inputs / outputs | Prepared fixture state and mode in; one create/recover/log/decide/deliver/checkpoint attempt out. |
| invariants | Mode-specific expected decisions are asserted; the matrix does not silently retry a failed operation on the same owner. |
| ownership | Mutates the optional live Session and actual fixture files according to the selected operation. |
| failure | File/Generation failures and explicit assertions propagate to the matrix caller. |
| cost | One bounded public Session operation, with its real file/native work. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0011

[Lines 47–48](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L48:sha256:b9865449d9e50a0286f298fd9c802fe59f013df864a86b39333c6ede77e03ef9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Reopen the authoritative files after releasing the failed owner. Complete surviving decisions are replayed; an undecided Input remains the same head. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 49–59](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void surviving(Fixture& f,Mode mode)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reopen the authoritative files after a failed/cut operation, finish any valid pending decision/output and inspect the resulting source/progress state. |
| inputs / outputs | Fixture files and original mode in; genuine recovered Session state and assertions out. |
| invariants | Only a surviving complete valid prefix may be replayed. At completion W=I and D=C; source weight and source/reader positions reflect only disposed commands. Recovery is through the real factory. |
| ownership | A local recovered Session owns the actual root/WAL/sink locks until the helper returns. |
| failure | Invalid surviving state, wrong Reject/commit result or mismatched source/progress fails an assertion or recovery. |
| cost | One cold recovery and at most one pending decision plus one output delivery for a tiny history. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0013

[Lines 60–62](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L62:sha256:0e430a3e2227fb2d19bd4f9ba533e385881a6fb9a92c55c5bbbec20d5f609834
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Inject before every observed call and after supported successful effects; acquisition-after EIO is normalized before acquisition. Every durability boundary gets a real child exit in the same filesystem, not a power-loss test. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 63–97](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void io_matrix()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise before/after syscall EIO reports and selected child exits across create, log, commit, Reject, delivery, checkpoint and recovery operations. |
| inputs / outputs | Fixture histories and baseline seam traces in; failure/latch assertions, descriptor/account cleanup checks and same-filesystem recovery of surviving bytes out. |
| invariants | Each mode starts from identical captured bytes; restore rebuilds a genuine owner before live operations. Before EIO can prevent the real syscall; after EIO follows a successful effect for supported stages, while descriptor-acquisition after-errors normalize before the call to avoid hiding an FD. For process cuts a child exits at selected before/after observations and the parent reopens shared files. These are same-filesystem process cuts, not power-loss experiments. |
| ownership | Parent and forked child have process-local Session/account copies; files are the shared evidence. Owner scopes are released before parent recovery. |
| failure | Every injected fault must be reported; uncertain live owners must require reopen; descriptors and receiving-account allocations return to fixture baselines; surviving state must replay validly. |
| cost | For each observed operation, restore and repeat a bounded history for the selected before/after error; also fork at selected write/sync/link/rename/truncate observations. Captured files eliminate repeated baseline publication but each reopen is real. This is fault coverage, not timing or power-loss evidence. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/sql_aggregate_file_probe.hpp](../../../../../tests/support/sql_aggregate_file_probe.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/sql_aggregate_file_fixture.hpp](../../../../../tests/support/sql_aggregate_file_fixture.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0015

[Lines 98–99](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L98); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L98-L99:sha256:9ea053fbcc882b4ad81a2dea61f861190eb48cb8edfdf1ce80d4101d4ef8efeb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: From the first append stamp through confirmed native/progress publication, no covered C++ allocation is permitted. The same holds for sink acknowledgement. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 100–120](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepaid_publication()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deny covered C++ new calls after selected file boundaries and require append/publication, sink acknowledgement and final root selection to finish. |
| inputs / outputs | Log, Commit, Reject, delivery and checkpoint-rotation modes in; counter assertions plus final Session state/generation out. |
| invariants | The replacement-new Scope counts/denies C++ new attempts only; it excludes libc malloc, bytes, MemoryAccount charges and syscalls. It first denies after an observed append/sink call, then separately denies after the selected root directory-sync effect and requires generation 2 to be selected. |
| ownership | The test executable's single-TU replacement operators own the counter; Session owns its receiver-account state and files. |
| failure | Any counted/triggered \`new\` attempt or incorrect pending/commit/reject/delivery state fails an assertion. |
| cost | Four live append/publication/delivery actions, then two actual checkpoint rotations: one discovery trace and one denied-allocation handoff. Each action has real initial fixture publication outside its denial scope. This counts the verification setup separately from product update cost. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0017

[Lines 121–124](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L124:sha256:973b2e5f4b5394cb6d10e8aaa7ce66ba355d91d073ea91bb666b54826304fc53
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Each covered allocation in live preparation/log funding and cold recovery can fail independently. Live cuts retry the same healthy owner, exercising actual undo. Cold cuts preserve the same files/account and need only one final healthy reopen. Covered new attempts remain separate from receiving-account bytes. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 125–149](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_cuts()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail each covered C++ new attempt in live log/commit/Reject and cold recovery, then verify either same-owner retry with genuine rollback or unchanged cold files/account followed by one healthy reopen. |
| inputs / outputs | Normal-run new-attempt counts and prepared fixture states in; per-attempt \`bad_alloc\`, exact WAL/sink bytes, unchanged undisposed frontiers, account cleanup and recovery assertions out. |
| invariants | For live modes, each bad_alloc leaves a healthy owner with C/I unchanged, no source/progress mutation and unchanged WAL/sink bytes; the same owner retries the same command successfully. For recovery mode, each denial preserves the exact torn files and receiver-account baseline; a single healthy final recovery settles the fixture. Replacement-new attempts remain separate from MemoryAccount bytes and syscall hooks. |
| ownership | Counter lifetime is local to each Scope; captured fixture files and account remain test-owned; live optional Session is retained for same-owner retry and released before final accounting. |
| failure | Each selected new attempt must fail as bad_alloc; partial state, file changes, an unhealthy live owner, failed same-owner retry, account leak or failed final recovery fails an assertion. |
| cost | One count pass per mode plus one bounded repeat for each observed new attempt; live attempts include same-owner retry, while cold attempts share one final healthy recovery after all cut points. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0019

[Lines 150–151](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L150); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L150-L151:sha256:4364b26741e3a01e75ccd86ea5c5018f3c09f8b8e07586d65d565cf00d3780e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Root-validation failures invalidate the owner; failure deleting/syncing only the unselected next candidates leaves the selected generation usable/retryable. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 152–168](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void root_retry_boundaries()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish failures while checking the selected root from retryable failures while cleaning/syncing unselected checkpoint candidates. |
| inputs / outputs | One real checkpoint-rotation event trace in; injected candidate-unlink, directory-sync and selected-root-read failures plus owner/retry assertions out. |
| invariants | Selected-root validation failure requires reopen; candidate unlink or directory-sync failure leaves generation 1 selected and permits checkpoint retry on the same owner. |
| ownership | Fixture owns test files; a live Session retains root locks during the retry assertions. |
| failure | Each targeted failure must be refused with the appropriate owner readiness and selected generation. |
| cost | One baseline rotation trace and three bounded fault/retry scenarios. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0021

[Lines 169–169](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L169); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L169-L169:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_session_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 170–170](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the syscall/fork matrix, publication allocation denial, per-new allocation cuts and root retry-boundary assertions. |
| inputs / outputs | No input; invokes four bounded fault groups and returns only after all assertions complete. |
| invariants | The test's fork exits are selected process exits around observed syscalls, not simulated machine power loss. |
| ownership | Each group owns its fixture and releases local owner scopes before returning. |
| failure | Any assertion, expected-failure mismatch or uncaught real file error prevents successful completion. |
| cost | Sum of the mode matrix and repeated small local recoveries; no performance measurement. |
| Design | [tests/unit/sql_aggregate_session_fault_test.cpp](../../../../../tests/unit/sql_aggregate_session_fault_test.cpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |
