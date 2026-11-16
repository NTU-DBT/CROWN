# `tests/unit/sql_aggregate_files_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ebf8b9818f481627ed91a6c1c95ffa3cdd8a906d66010b861b2e56d75e909c42`. 238 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. | source comment (unverified): // Bounded syscall observations only. Faults run real I/O unless denied; crash · [reviewed contract](#b0001) |
| [B0002 · 14–35](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L14) | Type/record definition: struct Hook | returns result; source comment (unverified): // Bounded syscall observations only. Faults run real I/O unless denied; crash · [reviewed contract](#b0002) |
| [B0003 · 36–39](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L36) | Type/record definition: struct Installed |  · [reviewed contract](#b0003) |
| [B0004 · 40–40](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L40) | Type/record definition: enum class Mode |  · [reviewed contract](#b0004) |
| [B0005 · 41–48](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L41) | Callable definition: std::string prior(bool sink,Mode mode,const Packets& p) | calls Packets::prefix, bytes, substr; returns {}; result · [reviewed contract](#b0005) |
| [B0006 · 49–51](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L49) | Callable definition: void setup(bool sink,Mode mode,const std::string& path,const Packets& p) | calls std::filesystem::remove, put, prior · [reviewed contract](#b0006) |
| [B0007 · 52–53](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L52) | Explanatory comments or spacing. | source comment (unverified): // No coordinator/native publication is exercised here: this is the actual · [reviewed contract](#b0007) |
| [B0008 · 54–69](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L54) | Callable definition: void exercise(bool sink,Mode mode,const std::string& path,Schema& s,const Packets& p, const resource::MemoryAccount& account,ar::… | calls append, repair_tail, constexpr, verify; source comment (unverified): // No coordinator/native publication is exercised here: this is the actual · [reviewed contract](#b0008) |
| [B0009 · 70–71](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L70) | Explanatory comments or spacing. | source comment (unverified): // Recovery adopts only complete surviving prefix bytes. A failed repair may · [reviewed contract](#b0009) |
| [B0010 · 72–83](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L72) | Callable definition: void surviving(bool sink,Mode mode,const std::string& path,Schema& s,const Packets& p, const resource::MemoryAccount& account) | calls std::filesystem::exists, assert, contents, prior; guard if(!std::filesystem::exists(path)) { assert(mode==Mode::create);return; }; source comment (unverified): // Recovery adopts only complete surviving prefix bytes. A failed repair may · [reviewed contract](#b0010) |
| [B0011 · 84–86](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L84) | Explanatory comments or spacing. | source comment (unverified): // Inject before each call and after supported actual effects; acquisition-after · [reviewed contract](#b0011) |
| [B0012 · 87–132](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L87) | Callable definition: void syscall_matrix(Schema& s,const Packets& p) | calls file, resource::MemoryAccount::create, setup, install; guard assert(trace.size&gt;0 && trace.size&lt;trace.events.size());const auto operations=trace.events\[trace.siz…; returns !e.after && e.stage==stage; 8 loop sites; source comment (unverified): // Inject before each call and after supported actual effects; acquisition-after · [reviewed contract](#b0012) |
| [B0013 · 133–135](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L133) | Explanatory comments or spacing. | source comment (unverified): // An uncertain append poisons all authority getters at prewrite-stat, write, · [reviewed contract](#b0013) |
| [B0014 · 136–163](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L136) | Callable definition: void poison_and_short_tail(Schema& s,const Packets& p) | calls file, setup, state, install; guard failed=true;assert(error.outcome()==(boundary==1?ar::FileOutcome::unchanged:boundary&lt;4?ar::FileOutc…; 3 loop sites; source comment (unverified): // An uncertain append poisons all authority getters at prewrite-stat, write, · [reviewed contract](#b0014) |
| [B0015 · 164–165](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L164) | Explanatory comments or spacing. | source comment (unverified): // Keep failed repair/duplicate owners alive to prove that their getters and · [reviewed contract](#b0015) |
| [B0016 · 166–189](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L166) | Callable definition: void retained_repair_and_verify(Schema& s,const Packets& p) | calls file, setup, state, install; guard assert(failed && file.requires_reopen());refused(\[&\]{static_cast&lt;void&gt;(file.state());});refused(\[&\]…; 4 loop sites; source comment (unverified): // Keep failed repair/duplicate owners alive to prove that their getters and · [reviewed contract](#b0016) |
| [B0017 · 190–193](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L190) | Explanatory comments or spacing. | source comment (unverified): // Explicit exhaustion/collision/cleanup cases remain finite and do not hide · [reviewed contract](#b0017) |
| [B0018 · 194–233](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L194) | Callable definition: void exceptional_paths(Schema& s,const Packets& p) | calls file, setup, state, install; guard {Installed install(hook);s04_alloc::Scope count;file.append((sink?p.sink:p.wal)\[sink?1:2\]);assert(h…; 4 loop sites; source comment (unverified): // Explicit exhaustion/collision/cleanup cases remain finite and do not hide · [reviewed contract](#b0018) |
| [B0019 · 234–234](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L234) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 235–238](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L235) | Callable definition: int main() | calls packets, syscall_matrix, poison_and_short_tail, retained_repair_and_verify · [reviewed contract](#b0020) |

## B0001

[Lines 1–13](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:349f5d3daeb58dc7e3b07e3dbbc87053f1c14ac68b39aac750ddbdf74d9b27d9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_files_fault_test.cpp: include "sql_aggregate_file_fixture.hpp", "sql_aggregate_file_probe.hpp", "index_allocation.hpp", &lt;cerrno&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;sys/wait.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_aggregate_files_fault_test.cpp](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–35](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Hook {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Control and record one R2 file syscall fault scenario without replacing POSIX storage. |
| inputs / outputs | The stack hook stores at most 4096 fixed FileEvents and configures ordinal failure/crash, before/after phase, short transfers, zero entropy, repeated EINTR, cleanup errno, or post-stat allocation denial. |
| invariants | Only the before callback decision changes a syscall; the after callback can arm the S04 allocation counter or exit a child. A full trace silently stops recording without changing operation ordinals. |
| ownership | Installed borrows this Hook through the thread-local API; the hook must outlive the installation and is cleared at scope exit. |
| failure | Its noexcept callback must not throw; _exit(77) intentionally bypasses destructors only in forked crash children. Incorrect mode settings can cause assertions to fail rather than produce a file-level failure. |
| cost | The observation array is 4096 fixed stack events per Hook. It allocates no trace vector and does not replace or simulate filesystem state. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:14-35, tests/support/sql_aggregate_file_probe.hpp:5-19, src/recovery/sql_aggregate_file_detail.cpp:16-20, src/recovery/sql_aggregate_file_detail.cpp:112-165, tests/support/index_allocation.hpp:11-70 |

## B0003

[Lines 36–39](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L36); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install one borrowed syscall callback and clear it when the lexical guard exits. |
| inputs / outputs | Construction passes Hook::call and the Hook address to set_file_hook; destruction replaces both with null. |
| invariants | The underlying probe is thread-local and installations do not stack; nested guards would clear an outer installation prematurely. |
| ownership | The guard borrows the caller's Hook, so declaration order keeps it alive until after the guard destructor runs. |
| failure | No status is returned by set/clear; an incorrectly scoped hook could leave a dangling context, which callers avoid by lexical pairing. |
| cost | Two pointer assignments occur across guard construction/destruction; the guard itself owns no allocation or descriptor. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:36-39, src/recovery/sql_aggregate_file_detail.cpp:16-20, tests/unit/sql_aggregate_files_fault_test.cpp:14-38, tests/support/sql_aggregate_file_probe.hpp:17-19 |

## B0004

[Lines 40–40](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Mode { create,open,append,repair,duplicate };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the lower-level file operation selected by the fault harness. |
| inputs / outputs | The five values route create/open, one append, explicit tail repair, or sink duplicate verification in prior and exercise. |
| invariants | Duplicate is deliberately absent for WAL in the matrix; repair input contains one partial next record, and the enum says nothing about coordinator semantics. |
| ownership | Values are copied into stack loops and helper arguments; no dynamic state is associated with a mode. |
| failure | Invalid enum values have no explicit default branch in the helpers and are outside the test's enumerated call sites. |
| cost | The enum is a fixed underlying test discriminator; scenario work is bounded by the small five-mode loop. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:40-40, tests/unit/sql_aggregate_files_fault_test.cpp:40-69, docs/sql_aggregate_files.md:94-111, src/recovery/sql_aggregate_file_detail.cpp:289-306 |

## B0005

[Lines 41–48](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string prior(bool sink,Mode mode,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the exact initial file prefix for one fault-mode setup. |
| inputs / outputs | A sink selector, operation mode and packet bundle choose zero bytes for create, complete prior header/input/epoch records for other modes, or an additional 23-byte partial next frame for repair. |
| invariants | The returned prefix is fixture data only; it does not mutate the target path or infer what an interrupted syscall actually published. |
| ownership | Packets is borrowed while its frame views are appended into a new owned std::string returned to the caller. |
| failure | Mode-specific indexing assumes packet vectors contain the fixed frames made by Packets; there is no unknown-mode recovery branch. |
| cost | The function copies only the fixed selected prefix and optional 23-byte suffix; string storage is ordinary test memory, not receiver-account state. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:41-48, tests/support/sql_aggregate_file_fixture.hpp:70-96, docs/sql_aggregate_files.md:64-77, docs/sql_aggregate_files.md:94-102 |

## B0006

[Lines 49–51](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void setup(bool sink,Mode mode,const std::string& path,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset one shared path to the chosen pre-operation byte image. |
| inputs / outputs | It removes any prior path and writes prior(...) unless the requested mode is create. |
| invariants | The test starts each injected attempt from known path bytes; temp names are separate entries and cleanup is inspected by callers. |
| ownership | Path and packet bundle are borrowed, while the fixture Directory remains owned by the enclosing scenario. |
| failure | Filesystem remove errors are not checked here; later creation/open assertions expose most setup failures but the helper does not return a status. |
| cost | One file unlink plus at most the selected prefix bytes written are done for each scenario reset; temporary directory entries are not recursively scanned here. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:49-51, tests/unit/sql_aggregate_files_fault_test.cpp:41-51, docs/sql_aggregate_files.md:27-41, src/recovery/sql_aggregate_file_detail.cpp:197-247 |

## B0007

[Lines 52–53](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L53:sha256:f32cd7de825636db93510120f8f97a2f93e2903e86267756428072aeb2080501
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: No coordinator/native publication is exercised here: this is the actual lower file create/open/append/repair/duplicate protocol and checked close. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_files_fault_test.cpp](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 54–69](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exercise(bool sink,Mode mode,const std::string& path,Schema& s,const Packets& p,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one selected actual WalFile or SinkFile operation under the current hook and limits. |
| inputs / outputs | The function creates or opens with the supplied receiving account and headers; append uses the fixed next frame, repair calls repair_tail, duplicate calls sink verify, and only a successful path reaches checked close. |
| invariants | This is the actual lower file protocol only. No native preparation, publication, selected-root decision, source continuation, or coordinator repair authority is exercised. |
| ownership | The selected file owner is moved into the generic lambda by value and closed before path/account/schema/packets leave the caller's scope. |
| failure | The call propagates FileFailure and allocation errors unchanged to the test's caller; a failed operation may leave a durable destination or torn suffix that surviving reopens. |
| cost | One owner and its receiving-account metadata/scratch/index are created per call; append bytes are borrowed from Packets, not copied into a test-side queue. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:54-69, docs/sql_aggregate_files.md:25-60, docs/sql_aggregate_files.md:94-111, src/recovery/sql_aggregate_wal_file.cpp:26-83, src/recovery/sql_aggregate_sink_file.cpp:64-128 |

## B0009

[Lines 70–71](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L71:sha256:62683343e589ffd579f7c9355a9c7b11574f861f9aa5ea6c0e053acf0d6cfbac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Recovery adopts only complete surviving prefix bytes. A failed repair may retain its torn suffix; neither repair outcome discards a complete Input. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_files_fault_test.cpp](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 72–83](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void surviving(bool sink,Mode mode,const std::string& path,Schema& s,const Packets& p,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify actual bytes left after a failed call or child exit by reopening the lower file owner. |
| inputs / outputs | It accepts absent output only for create, otherwise checks exact known prefixes/full append bytes/fully repaired bytes and reopens WAL or sink to inspect bounded state. |
| invariants | A failed repair may leave the torn suffix or have removed it; a complete pending WAL Input must remain pending. This proves physical file state, not native semantic commit authority. |
| ownership | The function owns only its short-lived reopened file owner; caller retains path, account, schema and packet frames. |
| failure | Unexpected surviving bytes, bad checksum or invalid cursor fail an assertion or the open call; this helper does not attempt repair or cleanup. |
| cost | Each invocation reads the observed file into a test string and then scans it with a fresh receiving-account file owner; all prefixes are finite fixture frames. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:72-83, docs/sql_aggregate_files.md:35-41, docs/sql_aggregate_files.md:94-111, src/recovery/sql_aggregate_file_detail.cpp:249-280, src/recovery/sql_aggregate_wal_file.cpp:44-65 |

## B0011

[Lines 84–86](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L84); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L86:sha256:39e422a0025bef0f3594cf65a397ab29fbe47dd0cce1188b530908f55a8108de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Inject before each call and after supported actual effects; acquisition-after errors normalize before open. Check smaller quotas, retryable EINTR and short I/O. Track receiving account allocations and actual FD/temp namespace cleanup separately. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_files_fault_test.cpp](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 87–132](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void syscall_matrix(Schema& s,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep syscall boundaries, operation quotas, selected EINTR/short-transfer behavior, and real process-exit cuts for both file owners. |
| inputs / outputs | It traces create/open/append/repair/duplicate modes, injects before each observed call and after supported actual effects, lowers the operation cap through each observed count, tests each listed retryable stage, clamps transfers, and forks at selected durability stages. |
| invariants | The child performs real POSIX calls and exits at hook boundaries; the parent checks bytes by reopen. Acquisition-after errors are normalized before open, and file-level crash cuts do not simulate power loss or establish future coordinator authority. |
| ownership | The stack Hook owns its fixed trace; each attempt owns fresh path state and a file owner. Forked child descriptors vanish at process exit, while parent Directory/account survive the sweep. |
| failure | Each injected operation failure must surface as FileFailure, release FD/account/temp state, and leave a prefix a new owner can validate. Only enumerated stages and durability events are covered. |
| cost | Iteration is finite by traced operation count and the 4096-event capacity: up to two failures per observed call, one pass per cap, selected EINTR/short-I/O passes, and one child per listed crash event. Real file metadata/index allocations occur on each fresh owner. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:87-132, docs/sql_aggregate_files.md:27-60, docs/sql_aggregate_files.md:123-136, src/recovery/sql_aggregate_file_detail.cpp:112-195, tests/support/sql_aggregate_file_probe.hpp:8-19, tests/support/index_allocation.hpp:11-70 |

## B0013

[Lines 133–135](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L133); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L135:sha256:82fc4c03d4acd69c744ff8c23ce682fdb645bfffa0c126ae44d0821b31539f49
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: An uncertain append poisons all authority getters at prewrite-stat, write, fsync and post-sync-stat. Reopening can adopt an actual complete surviving record even if the previous owner reported unknown or a final-stat failure. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_files_fault_test.cpp](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 136–163](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void poison_and_short_tail(Schema& s,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Establish that uncertain append failures poison a live owner and that a partial WAL suffix is repaired only by a reopened owner. |
| inputs / outputs | For WAL and sink it fails at four traced append boundaries on both phases, checks outcome and disabled getters/retries, then injects a short three-byte write followed by failure and reopens/repairs the WAL. |
| invariants | FileOutcome describes the lower file attempt; it does not grant native commit/retry authority. A new owner explicitly repairs the incomplete suffix while preserving the complete pending input. |
| ownership | The first owner is closed while poisoned; a second independently opened owner performs repair and append while the same path/account/schema stay live. |
| failure | Four selected boundaries are not a proof over every filesystem failure timing. The new owner must successfully scan before repair; no in-place retry is accepted on the poisoned one. |
| cost | The matrix has 16 bounded boundary/phase cases plus one short-write sequence; actual writes and scans use the fixed small frames. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:136-163, docs/sql_aggregate_files.md:49-60, docs/sql_aggregate_files.md:94-111, src/recovery/sql_aggregate_file_detail.cpp:289-306, src/recovery/sql_aggregate_wal_file.cpp:67-79 |

## B0015

[Lines 164–165](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L164); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L164-L165:sha256:fc333225659215c4abd5186f13e2b513700499a460a51e4a2642ec9057ae78aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Keep failed repair/duplicate owners alive to prove that their getters and retry paths stay poisoned, beyond survivor-byte checks after destruction. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_files_fault_test.cpp](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 166–189](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retained_repair_and_verify(Schema& s,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep owners alive across injected repair/duplicate-verification failures to assert the poison latch directly. |
| inputs / outputs | The test covers WAL repair, sink repair and sink duplicate verification at each selected operation boundary before/after, then checks rejected getters and retries before close. |
| invariants | Reopen/survivor checks confirm lower-file bytes separately; a public caller must establish native/root/checkpoint/sink semantic preconditions before production repair. |
| ownership | Each owner remains in the lambda after failure until checked close, rather than relying only on destruction behavior or post-destruction file inspection. |
| failure | A failed repair/verify leaves the old owner unusable even when a syscall effect may have occurred; recovery authority comes only from a later validated open and caller decision. |
| cost | There are three mode families, each bounded by four or three observed operation points and two phases; extra assertions use fixed state/receipt values. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:166-189, docs/sql_aggregate_files.md:56-60, docs/sql_aggregate_files.md:79-83, docs/sql_aggregate_files.md:104-111, src/recovery/sql_aggregate_file_detail.cpp:289-306, src/recovery/sql_aggregate_sink_file.cpp:94-124 |

## B0017

[Lines 190–193](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L190); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L190-L193:sha256:dd30da8b45a7007d0936a50aee114c5fc5266c4f60834c021f035e57341cb64f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Explicit exhaustion/collision/cleanup cases remain finite and do not hide resource denial in broad exception fallbacks. Allocation from the first successful prewrite stamp check through mutation/publication is denied, after all required pre-funding has completed. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_files_fault_test.cpp](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 194–233](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exceptional_paths(Schema& s,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cover post-prewrite-stat allocation denial, empty/short syscall outcomes, finite EINTR exhaustion, name collisions and explicit external mutation detection. |
| inputs / outputs | The function arms S04 denial after the first successful prewrite stat, checks no covered new call occurs through append, then exercises zero transfers, operation-capped repeated EINTR, 16 deterministic entropy collisions, cleanup-error reporting and changed-stamp refusal. |
| invariants | All append funding occurs before the allocation-denial point; this checks the existing path only. Filesystem errors are injected around real syscalls, and external writers violate the cooperative namespace contract. |
| ownership | A poisoned owner is closed and reopened before any explicit repair; persistent temporary names are checked or manually removed by the test. No test repair operation supplies native semantic validation. |
| failure | The EINTR loops stop at finite limits, including at most eight emergency cleanup attempts; entropy collision is fixed at 16 attempts. This does not claim unbounded retry, future coordinator authority, or crash/power-loss equivalence. |
| cost | Two ordinary appends have allocation denial after prewrite stat; remaining cases use fixed stage lists, a 30-operation cap, 16 entropy candidates, one short changed-file case and actual receiver-account metadata. S04 counts covered new calls, not all malloc/account activity. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:194-233, docs/sql_aggregate_files.md:27-33, docs/sql_aggregate_files.md:49-60, docs/sql_aggregate_files.md:123-136, src/recovery/sql_aggregate_file_detail.cpp:186-235, src/recovery/sql_aggregate_file_detail.cpp:289-306, tests/support/index_allocation.hpp:11-70 |

## B0019

[Lines 234–234](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L234); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L234-L234:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_files_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_aggregate_files_fault_test.cpp](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 235–238](../../../../../tests/unit/sql_aggregate_files_fault_test.cpp#L235); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one native SQL fixture and run all four lower-file fault groups. |
| inputs / outputs | It creates Schema and Packets, then invokes syscall, append-poison, retained-repair/verify and exceptional-path helpers once each. |
| invariants | The pass text from syscall_matrix is only one diagnostic; later helper failure still terminates the process. This executable contains no native recovery coordinator. |
| ownership | Schema and packet frames outlive every helper call; each helper owns its own temporary directory and scopes installed hooks around the tested call. |
| failure | Any escaping file/account exception or assertion failure stops execution; no catch in main converts an unexpected error into success. |
| cost | Four fixed helper calls run test-bounded loops; work comes from actual file operations, reopen scans and forked children rather than an unbounded fixture generator. |
| Design | tests/unit/sql_aggregate_files_fault_test.cpp:235-238, tests/unit/sql_aggregate_files_fault_test.cpp:87-238, docs/sql_aggregate_files.md:11-14, tests/support/sql_aggregate_file_fixture.hpp:47-96 |
