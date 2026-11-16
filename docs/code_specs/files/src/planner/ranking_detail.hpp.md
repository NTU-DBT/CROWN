# `src/planner/ranking_detail.hpp` — block usage map

[Source](../../../../../src/planner/ranking_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `5fb7ee1131e8dab43d0316e1770dfe71882e497d8b3173a198a282fb537334a4`. 123 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/planner/ranking_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 10–12](../../../../../src/planner/ranking_detail.hpp#L10) | Callable definition: template&lt;class T&gt; resource::OwnerAllocator&lt;T&gt; score_allocator(const resource::MemoryAccount& account) | calls ; returns resource::OwnerAllocator&lt;T&gt;(account,resource::MemoryPurpose::capture,score_memory_owner) · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../src/planner/ranking_detail.hpp#L13) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 14–16](../../../../../src/planner/ranking_detail.hpp#L14) | Callable definition: template&lt;class T&gt; resource::MemoryAllocator&lt;T&gt; scratch_allocator(const resource::MemoryAccount& account) | calls ; returns resource::MemoryAllocator&lt;T&gt;(account,resource::MemoryPurpose::scratch,score_memory_owner) · [reviewed contract](#b0004) |
| [B0005 · 17–19](../../../../../src/planner/ranking_detail.hpp#L17) | Callable definition: template&lt;class T&gt; resource::OwnerAllocator&lt;T&gt; evidence_allocator(const resource::MemoryAccount& account) | calls ; returns resource::OwnerAllocator&lt;T&gt;(account,resource::MemoryPurpose::capture,evidence_memory_owner) · [reviewed contract](#b0005) |
| [B0006 · 20–20](../../../../../src/planner/ranking_detail.hpp#L20) | Type/record definition: struct Failure |  · [reviewed contract](#b0006) |
| [B0007 · 21–27](../../../../../src/planner/ranking_detail.hpp#L21) | declares types or opens a type body. | source comment (unverified): // Logical debits are cumulative, not transactional: later byte rejection can · [reviewed contract](#b0007) |
| [B0008 · 28–34](../../../../../src/planner/ranking_detail.hpp#L28) | Callable definition: explicit Budget(const Limits& value,Usage initial={},const resource::MemoryAccount& account={}) :limits(value),usage(initial),mem… | calls limits, usage, memory, carried_active · [reviewed contract](#b0008) |
| [B0009 · 35–42](../../../../../src/planner/ranking_detail.hpp#L35) | Callable definition: void time() | calls std::chrono::steady_clock::now, count · [reviewed contract](#b0009) |
| [B0010 · 43–46](../../../../../src/planner/ranking_detail.hpp#L43) | Callable definition: static void add(std::uint64_t& value,std::uint64_t n,std::uint64_t cap,Stop stop) | calls  · [reviewed contract](#b0010) |
| [B0011 · 47–47](../../../../../src/planner/ranking_detail.hpp#L47) | Callable definition: void work(std::uint64_t n=1) | calls time, add · [reviewed contract](#b0011) |
| [B0012 · 48–48](../../../../../src/planner/ranking_detail.hpp#L48) | Callable definition: void cells(std::uint64_t n=1) | calls add · [reviewed contract](#b0012) |
| [B0013 · 49–49](../../../../../src/planner/ranking_detail.hpp#L49) | Callable definition: void bytes(std::uint64_t n) | calls add · [reviewed contract](#b0013) |
| [B0014 · 50–50](../../../../../src/planner/ranking_detail.hpp#L50) | Callable definition: void keys(std::uint64_t n) | calls work, add · [reviewed contract](#b0014) |
| [B0015 · 51–58](../../../../../src/planner/ranking_detail.hpp#L51) | Callable definition: void check_all() const | calls count · [reviewed contract](#b0015) |
| [B0016 · 59–62](../../../../../src/planner/ranking_detail.hpp#L59) | Callable definition: template&lt;class T&gt; void vector_items(std::size_t n) | calls max, cells, bytes · [reviewed contract](#b0016) |
| [B0017 · 63–64](../../../../../src/planner/ranking_detail.hpp#L63) | Closes surrounding scope/type. | source comment (unverified): // Little-endian base-2^32; all published values have at most 512 bits. · [reviewed contract](#b0017) |
| [B0018 · 65–81](../../../../../src/planner/ranking_detail.hpp#L65) | Type/record definition: class UInt | guard void check(const Budget&) const;; source comment (unverified): // Little-endian base-2^32; all published values have at most 512 bits. · [reviewed contract](#b0018) |
| [B0019 · 82–97](../../../../../src/planner/ranking_detail.hpp#L82) | Type/record definition: struct EvidenceData |  · [reviewed contract](#b0019) |
| [B0020 · 98–110](../../../../../src/planner/ranking_detail.hpp#L98) | Type/record definition: struct ResultData |  · [reviewed contract](#b0020) |
| [B0021 · 111–115](../../../../../src/planner/ranking_detail.hpp#L111) | Type/record definition: struct Factory | returns Evidence(std::move(p)); *x.data_ · [reviewed contract](#b0021) |
| [B0022 · 116–123](../../../../../src/planner/ranking_detail.hpp#L116) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::planner::ranking::detail · [reviewed contract](#b0022) |

## B0001

[Lines 1–9](../../../../../src/planner/ranking_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr resource::MemoryAttribution evidence_memory_owner
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign capture-owner9 to evidence component storage. |
| inputs / outputs | Constant attribution passed to account allocators. |
| invariants | Tag is diagnostic attribution, not new budget/freshness/proof authority. |
| ownership | Inline immutable tag. |
| failure | No validation/allocation. |
| cost | Fixed literal value. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
inline constexpr resource::MemoryAttribution score_memory_owner
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign capture-owner11 to score/score-scratch storage. |
| inputs / outputs | Constant attribution passed to account allocators. |
| invariants | Tag is diagnostic attribution, not new budget/freshness/proof authority. |
| ownership | Inline immutable tag. |
| failure | No validation/allocation. |
| cost | Fixed literal value. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 10–12](../../../../../src/planner/ranking_detail.hpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> resource::OwnerAllocator<T> score_allocator(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select retained score ownership attribution. |
| inputs / outputs | OwnerAllocator capture purpose/capture-owner11 for supplied account. |
| invariants | Copies of allocator retain original account identity. |
| ownership | Returns allocator handle; no payload allocation yet. |
| failure | Follows account/allocator construction contract. |
| cost | Fixed allocator handle work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 13–13](../../../../../src/planner/ranking_detail.hpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using Scratch=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own temporary score arrays under scratch attribution. |
| inputs / outputs | std::vector&lt;T,MemoryAllocator&lt;T&gt;&gt; used for traversal, UInt arrays and lowering scratch. |
| invariants | Scratch capacity is real account allocation, not cumulative logical cell usage. |
| ownership | Allocator retains receiving account for the vector lifetime; element pointers are not public retained outputs. |
| failure | Vector allocation/element failures propagate to rank boundary. |
| cost | Count/capacity-dependent allocation and element cleanup; no pooled/restarted resource state. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 14–16](../../../../../src/planner/ranking_detail.hpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> resource::MemoryAllocator<T> scratch_allocator(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select temporary score scratch attribution. |
| inputs / outputs | MemoryAllocator scratch purpose/capture-owner11. |
| invariants | Scratch is attributed separately from retained capture storage. |
| ownership | Returns account-retaining allocator. |
| failure | Follows allocator/account contract. |
| cost | Fixed allocator handle work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 17–19](../../../../../src/planner/ranking_detail.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> resource::OwnerAllocator<T> evidence_allocator(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select retained evidence attribution. |
| inputs / outputs | OwnerAllocator capture purpose/capture-owner9. |
| invariants | Evidence stays in the captured plan account. |
| ownership | Returns account-retaining allocator. |
| failure | Follows allocator/account contract. |
| cost | Fixed handle work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 20–20](../../../../../src/planner/ranking_detail.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Failure {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a precise local stop without allocating a message. |
| inputs / outputs | Single Stop enum thrown to rank boundary. |
| invariants | Internal carrier has no proof/result authority. |
| ownership | Inline exception payload. |
| failure | Thrown only by explicit budget/invariant checks. |
| cost | Fixed payload, ordinary exception runtime costs when thrown. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 21–27](../../../../../src/planner/ranking_detail.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Budget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track logical ranking/delegation usage with carried preparation time. |
| inputs / outputs | Owns limits/usage/account/start time and carried active nanoseconds. |
| invariants | Charging is not transactional: earlier debits survive later rejection; actual account capacity remains separate. |
| ownership | Owns scalar state/account handle for synchronous processing. |
| failure | Failure stops, no resumable worker state or generic rollback layer. |
| cost | Fixed bookkeeping; clocks and callees add their explicit costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 28–34](../../../../../src/planner/ranking_detail.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Budget(const Limits&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit score bit/time limits and carried usage before work. |
| inputs / outputs | Copies limits/initial usage/account, records start only when active time requested, then checks every existing debit. |
| invariants | Score bits must be1..512; time cannot be negative; carried usage cannot exceed new ceilings. |
| ownership | Local Budget owns copied account handle and scalars. |
| failure | Constructor throws Failure before optional emplacement completes on invalid/exhausted options. |
| cost | Fixed checks and optional clock sample; no payload allocation. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 35–42](../../../../../src/planner/ranking_detail.hpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void time() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sample cumulative cooperative active processing time. |
| inputs / outputs | Elapsed since construction plus carried time saturates at UINT64_MAX; rejects reaching finite ceiling. |
| invariants | No active-time limit means no clock sample/update here; excludes later destruction and caller idle time. |
| ownership | Mutates numeric usage only. |
| failure | Negative elapsed maps internal_error; finite ceiling maps time_limit. |
| cost | Fixed clock sample/arithmetic; not hard preemption. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 43–46](../../../../../src/planner/ranking_detail.hpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static void add(std::uint64_t&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit one bounded nonwrapping logical counter. |
| inputs / outputs | Rejects value&gt;cap or n&gt;cap-value before addition. |
| invariants | The single counter is unchanged on rejection; earlier different counter debits are not rolled back. |
| ownership | Borrows caller counter. |
| failure | Throws the supplied precise stop. |
| cost | Fixed arithmetic/branch. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 47–47](../../../../../src/planner/ranking_detail.hpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void work(std::uint64_t
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge logical work after a clock sample. |
| inputs / outputs | time then checked work increment. |
| invariants | Time can stop before new work; completed prior debits remain. |
| ownership | Mutates Budget. |
| failure | time_limit/work_limit Failure. |
| cost | Fixed clock/counter work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 48–48](../../../../../src/planner/ranking_detail.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cells(std::uint64_t
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge logical cells. |
| inputs / outputs | Checked cells increment without its own clock sample. |
| invariants | Not actual allocator capacity or current live cell count. |
| ownership | Mutates Budget. |
| failure | cell_limit Failure before this addition. |
| cost | Fixed counter work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 49–49](../../../../../src/planner/ranking_detail.hpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bytes(std::uint64_t
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge logical component payload bytes. |
| inputs / outputs | Checked payload_bytes increment. |
| invariants | Component model may conservatively recount shared metadata; not peak memory. |
| ownership | Mutates Budget. |
| failure | byte_limit Failure before this addition. |
| cost | Fixed counter work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 50–50](../../../../../src/planner/ranking_detail.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void keys(std::uint64_t
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge examined/encoded exact binding-key bytes. |
| inputs / outputs | Charges work first, then binding_key_bytes. |
| invariants | Byte rejection can leave work advanced; no false prepare/commit transaction claim. |
| ownership | Mutates Budget. |
| failure | Clock/work/key-byte Failure with prior debits retained. |
| cost | Fixed per-call bookkeeping plus delegated clocks. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 51–58](../../../../../src/planner/ranking_detail.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_all() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate all carried logical/delegated ceilings. |
| inputs / outputs | Checks work,cells,key/payload,delegated units and finite carried active time. |
| invariants | Equal usage is allowed for work/bytes but active time uses &gt;=; score_bits separately admitted by constructor. |
| ownership | Borrows options/usage. |
| failure | Throws precise work/cell/byte/lowering/time stop. |
| cost | Fixed set of numeric checks. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 59–62](../../../../../src/planner/ranking_detail.hpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void vector_items(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit a logical vector component conservatively. |
| inputs / outputs | Checks n*sizeof(T) representability, then cells(n), bytes(n*sizeof(T)). |
| invariants | A bytes failure can follow accepted cell debit; capacity/control/allocator overhead is separate. |
| ownership | No vector is allocated by this helper. |
| failure | byte_limit or cell_limit Failure. |
| cost | Fixed arithmetic/counter work. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 63–64](../../../../../src/planner/ranking_detail.hpp#L63); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L64:sha256:6abd03a770a22824424496706e24595ef3f8f607f57c055f2d11aef0fe6c83a5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. Its attached note introduces nearby behavior: Little-endian base-2^32; all published values have at most 512 bits. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0018

[Lines 65–81](../../../../../src/planner/ranking_detail.hpp#L65); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class UInt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent nonnegative exact scores in sixteen base-2^32 limbs. |
| inputs / outputs | Fixed512-bit value; arithmetic enforces request score_bits; decimal outputs at most155digits. |
| invariants | No floating-point approximation, dynamic bigint or unsigned wrap is accepted as score. |
| ownership | All arithmetic scratch inline; decimal output separately owns/allocates text. |
| failure | Bit/work/payload/clock failures report no complete rank. |
| cost | Fixed limb capacity; arithmetic has bounded loops, decimal rendering at most155iterations. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
struct Digits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store bounded reverse decimal rendering scratch. |
| inputs / outputs | 155inline char slots plus count. |
| invariants | 512-bit maximum needs at most155digits, including zero rendered once. |
| ownership | Stack/member value; no dynamic payload. |
| failure | No independent check; UInt kernel establishes bounds. |
| cost | Fixed155-byte buffer. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
UInt()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an exact zero score in fixed inline limbs. |
| inputs / outputs | Default member initialization clears all16uint32 limbs. |
| invariants | Zero is valid under every constructor-admitted positive score width. |
| ownership | Owns only inline limbs. |
| failure | No allocation or budget check in zero construction. |
| cost | Fixed16-limb initialization, no dynamic bigint allocation. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 82–97](../../../../../src/planner/ranking_detail.hpp#L82); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EvidenceData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain captured compiled source and accounted score facts. |
| inputs / outputs | CompiledProgram, exact binding text, input/source vectors, identity/accounting/reasons/denominator and preparation usage. |
| invariants | Defaults mark evidence unavailable until the capture factory populates facts; no public caller import. |
| ownership | Evidence vectors/text use captured program account; program retains its metadata. PhysicalPlan constructor explicitly creates a standalone compiled program. |
| failure | Native conversion/allocation may throw before factory publication. |
| cost | Program handle retention plus account-aware empty container setup; DTO conversion can validate/copy/allocate complete source. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
explicit EvidenceData(CompiledProgram p)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain captured native metadata and create its accounted evidence containers. |
| inputs / outputs | Moves a by-value compiled handle and selects its account for binding/weights/sources/observations. |
| invariants | Default unavailable reason masks remain until capture fills facts; construction alone does not establish healthy/current score evidence. |
| ownership | Shares native plan owner; containers retain the same account and start empty. |
| failure | Invalid compiled-handle access or allocator-contract/member construction failure can throw before publication; this overload performs no source conversion or producer replay. |
| cost | Fixed handle/container/allocator setup; later population is separate. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
explicit EvidenceData(const PhysicalPlan& p)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a legacy physical DTO into a standalone compiled evidence basis. |
| inputs / outputs | Calls CompiledProgram::standalone then delegates native constructor. |
| invariants | Default unavailable reason masks remain until capture fills facts; construction alone does not establish healthy/current score evidence. |
| ownership | Owns resulting compiled owner/account and empty evidence containers; original DTO remains caller owned. |
| failure | Program conversion/allocation may throw before private data is published. |
| cost | Creates a standalone account, validates/freezes storage binding/layout/projection metadata and copies the complete program/source into native ownership. This is not a constant handle conversion, P02 rerun, SQL normalization replay or identity recomputation. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp) |

## B0020

[Lines 98–110](../../../../../src/planner/ranking_detail.hpp#L98); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResultData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a privately prepared complete ranking payload. |
| inputs / outputs | Receiving account, snapshot/request/effective policy, fallback/evidence, accounted scores, selection and usage. |
| invariants | Selected/result publication occurs only after all admissions/scoring/tie-break complete. |
| ownership | Retains old snapshot/evidence owners and new accounted score vector. |
| failure | Constructor/member failures release private owners; no partial public Result. |
| cost | Fixed owner/options setup plus existing immutable-owner retention; final destruction scales with owned scores/plans. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
ResultData(const resource::MemoryAccount& a,CandidateSnapshot s,Request r,std::optional<Evidence> e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the receiving-account owner for a whole ranking. |
| inputs / outputs | Retains supplied account, transfers local snapshot/request/evidence copies, initializes effective=request.policy and empty score vector. |
| invariants | This private draft has no selected result authority before all score/admission checks and final publication. |
| ownership | Owns account-aware score container plus immutable borrowed-source owners by retained value. |
| failure | Any member construction failure unwinds the draft before public Result creation. |
| cost | Fixed account/handle/options setup plus reference retention and possible replaced local-owner cleanup; no score payload built yet. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 111–115](../../../../../src/planner/ranking_detail.hpp#L111); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Factory {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict public Evidence/Result creation to prepared internal payloads. |
| inputs / outputs | Wrap shared const data or borrow private evidence data. |
| invariants | Supplied data must be nonnull/complete; this bridge does no proof or freshness validation. |
| ownership | Transfers/borrows shared immutable payloads. |
| failure | No internal empty check; closed factory callers establish preconditions. |
| cost | Fixed handle/field access plus possible destination temporary release. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
static Evidence evidence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a prepared evidence owner. |
| inputs / outputs | Factory-only shared payload bridge. |
| invariants | Nonnull and completed-data preconditions are supplied by closed internal callers. |
| ownership | Moves the supplied shared const EvidenceData owner into the returned Evidence; the by-value local parameter may become empty. |
| failure | No additional validation/exception conversion. |
| cost | Fixed handle/field access. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
static const EvidenceData& data(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow private immutable evidence data. |
| inputs / outputs | Factory-only shared payload bridge. |
| invariants | Nonnull and completed-data preconditions are supplied by closed internal callers. |
| ownership | Borrows EvidenceData through the supplied retained Evidence; caller must keep that payload owned for the reference lifetime. |
| failure | No additional validation/exception conversion. |
| cost | Fixed handle/field access. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
static Result result(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a prepared complete result owner. |
| inputs / outputs | Factory-only shared payload bridge. |
| invariants | Nonnull and completed-data preconditions are supplied by closed internal callers. |
| ownership | Moves the supplied shared const ResultData owner into returned Result; it does not borrow a separate Evidence object here. |
| failure | No additional validation/exception conversion. |
| cost | Fixed handle/field access. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 116–123](../../../../../src/planner/ranking_detail.hpp#L116); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L123:sha256:5b5aaf869472e9eeb8ffd1a243685090a529f39e5a2322c306b4e316fc78d1e2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare binding, binding, binding, binding, score_binding, score_binding, equal_bytes in src/planner/ranking_detail.hpp with the exact signatures shown in this span. |
| inputs / outputs | Signatures: std::string binding(const Catalog&,const Query&,Budget&); std::string binding(const program::Catalog&,const program::Query&,Budget&); EvidenceText binding(const Catalog&,const Query&,Budget&,const resource::MemoryAccount&); EvidenceText binding(const program::Catalog&,const program::Query&,Budget&,const resource::MemoryAccount&); ScoreText score_binding(const Catalog&,const Query&,Budget&,const resource::MemoryAccount&); ScoreText score_binding(const program::Catalog&,const program::Query&,Budget&,const resource::MemoryAccount&); bool equal_bytes(std::string_view,std::string_view,Budget&);. These declarations specify parameter and result types; definitions supply runtime work. |
| invariants | The declarations fix C++ call types only; they do not execute, validate arguments, or create proof authority. |
| ownership | Catalog/Query/Budget/MemoryAccount reference parameters borrow caller objects for the call. The two string_view values in equal_bytes borrow their character backing. By-value std::string results own characters; EvidenceText and ScoreText are owning text using OwnerAllocator&lt;char&gt;, retaining their allocator/account affiliation without creating a new allowance. |
| failure | Ill-formed or mismatched declarations fail compilation/linkage. Runtime exception and resource-stop behavior belongs to each definition. |
| cost | The compiler parses the signatures; there is no runtime work or allocation until a definition is called. |
| Design | [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/resource/owner_text.hpp](../../../../../include/crown/resource/owner_text.hpp) |
