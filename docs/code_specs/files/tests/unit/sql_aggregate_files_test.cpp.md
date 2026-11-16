# `tests/unit/sql_aggregate_files_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_files_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a1379c0fa2654c0f89362e9c1df5f4790ac518fe99fab2219a02d704e32a5d1e`. 202 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/sql_aggregate_files_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;ar::SinkReceipt&gt; && !std::is_aggregate_v&lt;ar::SinkRec…; source comment (unverified): // Actual files preserve independent W/I/C and the sink's separate D. File · [reviewed contract](#b0001) |
| [B0002 · 16–46](../../../../../tests/unit/sql_aggregate_files_test.cpp#L16) | Callable definition: void round_trip(Schema& s,const Packets& p) | calls file, resource::MemoryAccount::create, ar::WalFile::create, ar::SinkFile::create; guard const auto initial_receipt=sink.receipt();assert(initial_receipt.prefix().physical_sequence==0);; source comment (unverified): // Actual files preserve independent W/I/C and the sink's separate D. File · [reviewed contract](#b0002) |
| [B0003 · 47–49](../../../../../tests/unit/sql_aggregate_files_test.cpp#L47) | Explanatory comments or spacing. | source comment (unverified): // Every prefix cut after a complete header is either a complete prior prefix or · [reviewed contract](#b0003) |
| [B0004 · 50–89](../../../../../tests/unit/sql_aggregate_files_test.cpp#L50) | Callable definition: void tails_and_corruption(Schema& s,const Packets& p) | calls file, Packets::prefix, bytes, size; guard assert(file.state().wal.pending && file.state().wal.command_sequence==0 && file.state().torn_tail==…; 6 loop sites; source comment (unverified): // Every prefix cut after a complete header is either a complete prior prefix or · [reviewed contract](#b0004) |
| [B0005 · 90–91](../../../../../tests/unit/sql_aggregate_files_test.cpp#L90) | Explanatory comments or spacing. | source comment (unverified): // Rebased sinks use global C ordinals and accept an increasing input-sequence · [reviewed contract](#b0005) |
| [B0006 · 92–126](../../../../../tests/unit/sql_aggregate_files_test.cpp#L92) | Callable definition: void identity_and_extremes(Schema& s,const Packets& p) | calls file, program, ar::encode, info; guard const auto baseline=sink.receipt();assert(baseline.prefix().generation==0 && baseline.prefix().phys…; 1 loop sites; source comment (unverified): // Rebased sinks use global C ordinals and accept an increasing input-sequence · [reviewed contract](#b0006) |
| [B0007 · 127–129](../../../../../tests/unit/sql_aggregate_files_test.cpp#L127) | Explanatory comments or spacing. | source comment (unverified): // An immutable Frame may have a different genuine schema or be moved from. · [reviewed contract](#b0007) |
| [B0008 · 130–150](../../../../../tests/unit/sql_aggregate_files_test.cpp#L130) | Callable definition: void frame_boundaries(Schema& s,const Packets& p) | calls file, ar::WalFile::create, ar::SinkFile::create, contents; guard assert(std::holds_alternative&lt;frontend::SqlAggregateProgram&gt;(bound));const auto& alien=std::get&lt;fro…; growth copy_of; source comment (unverified): // An immutable Frame may have a different genuine schema or be moved from. · [reviewed contract](#b0008) |
| [B0009 · 151–153](../../../../../tests/unit/sql_aggregate_files_test.cpp#L151) | Explanatory comments or spacing. | source comment (unverified): // Successful open's measured grants are replayed exactly and one below. Scope · [reviewed contract](#b0009) |
| [B0010 · 154–172](../../../../../tests/unit/sql_aggregate_files_test.cpp#L154) | Callable definition: template&lt;class Factory&gt; void receiving_limits(Factory factory,const std::string& path) | calls contents, resource::MemoryAccount::create, factory, statistics; guard assert(failed && receiver.statistics().current.allocations==1 && descriptors()==fds && contents(pat…; 2 loop sites; source comment (unverified): // Successful open's measured grants are replayed exactly and one below. Scope · [reviewed contract](#b0010) |
| [B0011 · 173–196](../../../../../tests/unit/sql_aggregate_files_test.cpp#L173) | Callable definition: void limits_namespace_and_lifetime(Schema& s,const Packets& p) | calls file, put, Packets::prefix, receiving_limits; guard put(wp,"preserved");refused(\[&\]{auto file=ar::WalFile::create(s.account,wp,s.admitted.descriptor,s.…; returns ar::WalFile::open(account,wp,s.admitted.descriptor,s.wal,limits); ar::SinkFile::open(account,sp,s.a…; growth emplace; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 197–197](../../../../../tests/unit/sql_aggregate_files_test.cpp#L197) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 198–202](../../../../../tests/unit/sql_aggregate_files_test.cpp#L198) | Callable definition: int main() | calls packets, round_trip, tails_and_corruption, identity_and_extremes · [reviewed contract](#b0013) |

## B0001

[Lines 1–15](../../../../../tests/unit/sql_aggregate_files_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:6929bc4d9b33ce4ea5672119c25a99f077602cdd210522cd163db0c2066f16a4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_files_test.cpp: include "sql_aggregate_file_fixture.hpp", "index_allocation.hpp", &lt;iostream&gt;, &lt;optional&gt;; bind local aliases/name imports; require 4 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_aggregate_files_test.cpp](../../../../../tests/unit/sql_aggregate_files_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–46](../../../../../tests/unit/sql_aggregate_files_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void round_trip(Schema& s,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise actual create, append, duplicate verification, move, close and reopen for a linked WAL/sink pair. |
| inputs / outputs | The function borrows fixture frames and schema, creates files in a stack Directory, appends two WAL commits plus two sink epochs, then checks prefixes and reopened byte streams. |
| invariants | The WAL retains transport W/I/C frontiers, including the synthetic Reject; sink duplicates return false only after byte comparison. Moving an owner invalidates the source; owner-level unlock/FD lifetime ends at close/destruction. |
| ownership | The two File owners keep their locks and receiving-account metadata for the function scope; frames remain owned by Packets and Directory outlives both owners. |
| failure | S04 denial is expected only for initial sink append scratch funding; the empty-receiver owners are not mistaken for native semantic replay or coordinator publication. |
| cost | It performs a fixed seven-record WAL and three-record sink round trip with one ordinary-new denial and two reopen scans. Frame bytes, metadata/index and scratch are actual receiver-account allocations; the test does not time them. |
| Design | tests/unit/sql_aggregate_files_test.cpp:16-46, docs/sql_aggregate_files.md:43-60, docs/sql_aggregate_files.md:62-83, src/recovery/sql_aggregate_wal_file.cpp:67-83, src/recovery/sql_aggregate_sink_file.cpp:94-128, tests/support/index_allocation.hpp:11-70 |

## B0003

[Lines 47–49](../../../../../tests/unit/sql_aggregate_files_test.cpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L49:sha256:25fc722890a8febb78c4079d7ff8cd4a77f188cb6dd57a3d4289c75866b4e78a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Every prefix cut after a complete header is either a complete prior prefix or one validated incomplete suffix. Repair preserves complete pending Inputs; a complete corrupt record, wrong kind or wrong ordinal is never repaired. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_files_test.cpp](../../../../../tests/unit/sql_aggregate_files_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 50–89](../../../../../tests/unit/sql_aggregate_files_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void tails_and_corruption(Schema& s,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check strict prefixes of representative next records and reject complete or authenticated-invalid records without rewriting them. |
| inputs / outputs | For a prior WAL prefix and sink header it varies the cut through one Commit/GroupEpoch, tests bytewise mutations and three resealed envelope mutations, then verifies a duplicate through a torn suffix. |
| invariants | Repair is called explicitly by the test after open; it does not perform the session-level native/source/sink validation that docs require before production repair. |
| ownership | Each WalFile/SinkFile owns its lock only until scope exit; path contents are reloaded through fixture streams, and the test reuses one directory leaf sequentially. |
| failure | Open rejects complete corrupt bytes and inconsistent kind/ordinal/length evidence. The finite mutation set is not an exhaustive proof over all hostile byte strings. |
| cost | Loops are bounded by one frame's encoded byte length plus three hand-built modes; each cut writes/copies a prefix, and open scans use actual receiving-account scratch and file metadata. |
| Design | tests/unit/sql_aggregate_files_test.cpp:50-89, docs/sql_aggregate_files.md:94-111, src/recovery/sql_aggregate_file_detail.cpp:258-280, src/recovery/sql_aggregate_wal_file.cpp:44-65, src/recovery/sql_aggregate_sink_file.cpp:72-90 |

## B0005

[Lines 90–91](../../../../../tests/unit/sql_aggregate_files_test.cpp#L90); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L91:sha256:b3c46f091d33d56d7672e888c4a4ce1fefc2fbad584feb4345be4669e0de1059
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Rebased sinks use global C ordinals and accept an increasing input-sequence gap; falling generation/I, relative ordinals and differing duplicate bytes fail. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_files_test.cpp](../../../../../tests/unit/sql_aggregate_files_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 92–126](../../../../../tests/unit/sql_aggregate_files_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void identity_and_extremes(Schema& s,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise rebased transport ordinals, permitted increasing sink-I gaps, identity rejection and integer terminal frontiers. |
| inputs / outputs | The test makes a WAL header at C=10/I=17 and a sink at base C=10, appends I=18 and global epoch ordinal C=11, then tries falling metadata, relative ordinals, changed duplicate bytes and UINT64_MAX cases. |
| invariants | The increasing I gap is accepted at the sink prefix boundary but this rebased history does not itself write a Reject record. Terminal C/I maxima reject any impossible next record, and a wrong descriptor binding cannot create a destination. |
| ownership | The test owns two actual file owners at a time and closes the sink before the temp directory leaves scope; source Packets are only borrowed for one max-frontier refusal. |
| failure | Wrong generation/I, wrong relative C, different duplicate body, mismatched descriptor, or terminal suffix is rejected before an accepted append; these are selected cases, not every integer boundary combination. |
| cost | The scenario writes a fixed number of headers/epochs and one synthetic empty Input; its only stress is constant-width uint64 boundary handling, with receiver-account storage allocated by file owners. |
| Design | tests/unit/sql_aggregate_files_test.cpp:92-126, docs/sql_aggregate_files.md:64-83, src/recovery/sql_aggregate_wal_file.cpp:67-79, src/recovery/sql_aggregate_sink_file.cpp:27-42, src/recovery/sql_aggregate_sink_file.cpp:94-122 |

## B0007

[Lines 127–129](../../../../../tests/unit/sql_aggregate_files_test.cpp#L127); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L127-L129:sha256:8f095cbe371aa82d61dd6e4871973ecb6ae24d6e906d531ec6713ddf7d7196d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: An immutable Frame may have a different genuine schema or be moved from. The file must inspect actual bytes under its own program, with no mutation or poisoning for these pre-I/O refusals; cached Frame metadata is insufficient. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_files_test.cpp](../../../../../tests/unit/sql_aggregate_files_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 130–150](../../../../../tests/unit/sql_aggregate_files_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void frame_boundaries(Schema& s,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove an owner's frozen schema and actual bytes gate append before file mutation. |
| inputs / outputs | The test supplies a genuine alien aggregate Frame, cross-kind WAL/sink Frames, and a moved-from Frame, then checks file bytes, owner health, records and operation counters. |
| invariants | Cached Frame info is not authority: owners inspect under their own program. A WAL transition thrown inside next.feed occurs before its work charge; this test asserts bytes and operations, not a work delta. SinkFile charges a successful generic inspect before later kind/order checks, so a parseable wrong-kind frame may still spend work. No native replay is tested. |
| ownership | The two owner locks are held for the checks; the original and moved Frame handles are stack values backed by account-funded encoded storage. |
| failure | Mismatched inputs are refused before append I/O and leave both owners reusable. The alien SQL is valid but structurally distinct; no claim is made about arbitrary codec corruption here. |
| cost | It creates two owners and a small set of frames/one row tuple; actual schema binding and output-frame allocations use the supplied account, while counter assertions cover only this test path. |
| Design | tests/unit/sql_aggregate_files_test.cpp:130-150, docs/sql_aggregate_files.md:43-54, src/recovery/sql_aggregate_wal_file.cpp:67-77, src/recovery/sql_aggregate_sink_file.cpp:94-122, include/crown/recovery/sql_aggregate_files.hpp:49-51 |

## B0009

[Lines 151–153](../../../../../tests/unit/sql_aggregate_files_test.cpp#L151); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L151-L153:sha256:8d9cfac5a7442f1f2ce05c54e2f914214c6f2e387b6e9be8146180640f6dabae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Successful open's measured grants are replayed exactly and one below. Scope allocation cuts cover every receiving metadata/index/scratch allocation, with file bytes/FD counts and the receiving account restored after each rejection. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_files_test.cpp](../../../../../tests/unit/sql_aggregate_files_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 154–172](../../../../../tests/unit/sql_aggregate_files_test.cpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Factory> void receiving_limits(Factory factory,const std::string& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure a valid open's receiving-account high-water and exact replacement-new count, then test allocation and file-limit cuts. |
| inputs / outputs | A factory opens the supplied path; the helper records S04 covered new calls and account peak bytes, injects bad_alloc at each measured allocation position, tests exact/one-byte-short account caps, and lowers work/operations/bytes/records one at a time. |
| invariants | File bytes and descriptor counts must recover after each allocation cut. S04 counts only its replaced C++ new forms; MemoryAccount requested bytes and POSIX activity are separate measures. |
| ownership | The caller supplies the factory/path and keeps the fixture file stable; each returned file owner is destroyed before post-failure account and FD assertions. |
| failure | Expected failures are bad_alloc for each injected cut and a standard exception for one-below limits; this test does not inject malloc, OS page pressure, or native runtime work. |
| cost | For N measured covered allocation sites, the helper invokes the factory N+9 times: one measurement, N injected cuts, exact/one-under account opens, stats and exact file-grant opens, and four single-limit reductions. Each attempt performs bounded real scan/metadata/index work; test sweeps are separate from ordinary append cost. |
| Design | tests/unit/sql_aggregate_files_test.cpp:154-172, docs/sql_aggregate_files.md:113-137, src/recovery/sql_aggregate_wal_file.cpp:6-14, src/recovery/sql_aggregate_sink_file.cpp:7-17, tests/support/index_allocation.hpp:11-70 |

## B0011

[Lines 173–196](../../../../../tests/unit/sql_aggregate_files_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void limits_namespace_and_lifetime(Schema& s,const Packets& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact record/work/I/O limits, path/no-follow/create preservation and ownership across producer-account teardown. |
| inputs / outputs | It prepares full WAL/sink byte streams, calls receiving_limits, probes one-over record counts, unsafe names and symlink/open/create collisions, then appends through owners whose source Schema has left scope. |
| invariants | An owner freezes the admitted program into the receiving account and retains its file lock/FD independently of the producer runtime. Symlinks, existing destination bytes, and invalid path shapes are refused without replacement. |
| ownership | The stack Directory, receiver and producer account outlive the file owners that use them; optional owners are reset before FD/temp/account cleanup assertions. |
| failure | The selected invalid names, symlink and occupied target are refused; assertions cover only these path forms and one retained-owner lifetime, not all hostile namespace races. |
| cost | The test opens each three-record/two-epoch stream several times for exact cap checks and performs fixed descriptor and temporary scans; frame/index/schema copies are real receiver-account allocations. |
| Design | tests/unit/sql_aggregate_files_test.cpp:173-196, docs/sql_aggregate_files.md:27-41, docs/sql_aggregate_files.md:113-137, src/recovery/sql_aggregate_file_detail.cpp:41-53, src/recovery/sql_aggregate_wal_file.cpp:26-65, src/recovery/sql_aggregate_sink_file.cpp:64-90 |

## B0012

[Lines 197–197](../../../../../tests/unit/sql_aggregate_files_test.cpp#L197); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L197-L197:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_files_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_aggregate_files_test.cpp](../../../../../tests/unit/sql_aggregate_files_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 198–202](../../../../../tests/unit/sql_aggregate_files_test.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the five deterministic behavioral groups over one schema and one shared immutable packet set. |
| inputs / outputs | It constructs one Schema and Packets, calls each helper once in fixed order, and writes a pass line only if all assertions survive. |
| invariants | The executable checks lower file primitives and fixture relationships; it does not exercise the native replay coordinator or certify power-loss durability. |
| ownership | Schema and Packets stay alive through every helper; each helper owns its own stack directory and scoped file owners. |
| failure | An uncaught exception or failed assertion terminates the test before the printed pass line; the print itself is not independent test evidence. |
| cost | The main sequence has five calls and no data-dependent loop of its own; costs come from the bounded helper cases and actual file-owner allocations. |
| Design | tests/unit/sql_aggregate_files_test.cpp:198-202, tests/unit/sql_aggregate_files_test.cpp:16-46, tests/unit/sql_aggregate_files_test.cpp:50-196, docs/sql_aggregate_files.md:11-14 |
