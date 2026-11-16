# `src/runtime/statistics_collection.hpp` — block usage map

[Source](../../../../../src/runtime/statistics_collection.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `50889a1a360a507f2e596c8ac003885132e02d7ea6a3b21f4f0c6d5bea65a57f`. 88 lines partitioned into 25 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../src/runtime/statistics_collection.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Transactional numeric slabs: detail hooks are fixed work; root lifecycle scans · [reviewed contract](#b0001) |
| [B0002 · 24–24](../../../../../src/runtime/statistics_collection.hpp#L24) | Type/record definition: struct Ticket |  · [reviewed contract](#b0002) |
| [B0003 · 25–28](../../../../../src/runtime/statistics_collection.hpp#L25) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Explicit standalone component account; runtimes pass their existing grant. · [reviewed contract](#b0003) |
| [B0004 · 29–29](../../../../../src/runtime/statistics_collection.hpp#L29) | Callable definition: \[\[nodiscard\]\] resource::MemoryAccount memory_account() const noexcept | calls get_allocator, account; returns descriptors_.get_allocator().account() · [reviewed contract](#b0004) |
| [B0005 · 30–41](../../../../../src/runtime/statistics_collection.hpp#L30) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Explicit quiescent allocating barrier. Throws on invalid config/OOM; · [reviewed contract](#b0005) |
| [B0006 · 42–42](../../../../../src/runtime/statistics_collection.hpp#L42) | Callable definition: Ticket current_ticket() const noexcept | calls ; returns {active_serial_,depth_,0} · [reviewed contract](#b0006) |
| [B0007 · 43–51](../../../../../src/runtime/statistics_collection.hpp#L43) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Caller must invoke only after a SUCCESSFUL semantic mode switch. · [reviewed contract](#b0007) |
| [B0008 · 52–52](../../../../../src/runtime/statistics_collection.hpp#L52) | Callable definition: std::span&lt;const Cell&gt; committed() const noexcept | calls ; returns committed_ · [reviewed contract](#b0008) |
| [B0009 · 53–53](../../../../../src/runtime/statistics_collection.hpp#L53) | Callable definition: std::span&lt;const Cell&gt; previous() const noexcept | calls ; returns previous_ · [reviewed contract](#b0009) |
| [B0010 · 54–54](../../../../../src/runtime/statistics_collection.hpp#L54) | Callable definition: std::span&lt;const Descriptor&gt; descriptors() const noexcept | calls ; returns descriptors_ · [reviewed contract](#b0010) |
| [B0011 · 55–55](../../../../../src/runtime/statistics_collection.hpp#L55) | Callable definition: const Metadata& metadata() const noexcept | calls ; returns meta_ · [reviewed contract](#b0011) |
| [B0012 · 56–56](../../../../../src/runtime/statistics_collection.hpp#L56) | Callable definition: const Metadata& previous_metadata() const noexcept | calls ; returns previous_meta_ · [reviewed contract](#b0012) |
| [B0013 · 57–57](../../../../../src/runtime/statistics_collection.hpp#L57) | Callable definition: const Options& options() const noexcept | calls ; returns options_ · [reviewed contract](#b0013) |
| [B0014 · 58–58](../../../../../src/runtime/statistics_collection.hpp#L58) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0014) |
| [B0015 · 59–59](../../../../../src/runtime/statistics_collection.hpp#L59) | Callable definition: bool pending() const noexcept | calls ; returns depth_ != 0 · [reviewed contract](#b0015) |
| [B0016 · 60–60](../../../../../src/runtime/statistics_collection.hpp#L60) | Callable definition: bool has_previous() const noexcept | calls ; returns has_previous_ · [reviewed contract](#b0016) |
| [B0017 · 61–61](../../../../../src/runtime/statistics_collection.hpp#L61) | Callable definition: bool replaced_history() const noexcept | calls ; returns replaced_history_ · [reviewed contract](#b0017) |
| [B0018 · 62–62](../../../../../src/runtime/statistics_collection.hpp#L62) | controls preprocessing. |  · [reviewed contract](#b0018) |
| [B0019 · 63–67](../../../../../src/runtime/statistics_collection.hpp#L63) | Callable definition: void seed_report_saturation() noexcept | calls ; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 68–68](../../../../../src/runtime/statistics_collection.hpp#L68) | controls preprocessing. |  · [reviewed contract](#b0020) |
| [B0021 · 69–69](../../../../../src/runtime/statistics_collection.hpp#L69) | Callable definition: U64 generation() const noexcept | calls ; returns generation_ · [reviewed contract](#b0021) |
| [B0022 · 70–70](../../../../../src/runtime/statistics_collection.hpp#L70) | Callable definition: bool generation_saturated() const noexcept | calls ; returns generation_saturated_ · [reviewed contract](#b0022) |
| [B0023 · 71–71](../../../../../src/runtime/statistics_collection.hpp#L71) | Callable definition: U64 configuration() const noexcept | calls ; returns configuration_ · [reviewed contract](#b0023) |
| [B0024 · 72–72](../../../../../src/runtime/statistics_collection.hpp#L72) | Callable definition: U64 previous_configuration() const noexcept | calls ; returns previous_configuration_ · [reviewed contract](#b0024) |
| [B0025 · 73–88](../../../../../src/runtime/statistics_collection.hpp#L73) | declares types or opens a type body; declares callable signatures. | source comment (unverified): // standalone boundary injection only; no public setter · [reviewed contract](#b0025) |

## B0001

[Lines 1–23](../../../../../src/runtime/statistics_collection.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr resource::MemoryAttribution memory_owner
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify native workload collector and route-array allocation ownership. |
| inputs / outputs | All observation arrays use observation:1 under the existing query account. |
| invariants | Attribution is a partition tag, not a new account/grant or an independent whole-query memory limit. |
| ownership | Inline tag owns no storage; allocators retain actual account separately. |
| failure | No runtime failure path. |
| cost | Compile-time scalar metadata, no runtime instrumentation. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 24–24](../../../../../src/runtime/statistics_collection.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Ticket {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the private collector's exact nesting protocol identity. |
| inputs / outputs | serial identifies the active scope, depth gives nesting level, parent restores prior active serial when that scope finishes. Zero serial is inert/off/refused. |
| invariants | Numeric Ticket is neither an engine commit token nor source-order/proof authority. Internal callers preserve LIFO serial/depth and the parent returned by nest(). |
| ownership | Inline values only; no query rows/owners or allocations. |
| failure | Protocol misuse is detected by Collector metadata/poisoning where checked; arbitrary forged parent values are outside internal caller discipline. |
| cost | Three uint64 values, fixed copy/comparison. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 25–28](../../../../../src/runtime/statistics_collection.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Collector {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep transactional numeric observations in fixed native slabs with private attempt staging. |
| inputs / outputs | configure allocates descriptors and committed/attempt/previous Cell vectors; admit/nest/facts/detail/finish route one actual transaction, reset/rotate establish explicit observation intervals. |
| invariants | Only successful outer root publishes known root facts; only selected complete nontruncated detail merges. Abort/protocol misuse poisons the whole attempt. Observation counters saturate explicitly and are not correctness/proof authority. |
| ownership | All arrays retain original account allocators. Copy/move are deleted to preserve borrowed spans/protocol state. No query row/key/string copy or native cursor is stored. |
| failure | configure validates and allocates before swapping, preserving old collector on failure. Hot noexcept hooks use flags/null/false instead of exceptions; they are not generic recovery of engine mutations. |
| cost | configure validates duplicates/parents with O(descriptor_count^2) scans and funds four vectors. Detail/nested hooks are bounded scalar/65-bin operations without heap/clocks; root admit/finish/reset/rotate scan dense Cell slabs, including unsampled attempts. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  Collector();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize collector ownership without collecting an event. |
| inputs / outputs | Creates an explicit standalone component account with UINT64_MAX then delegates to the account-taking constructor. Native runtime construction uses the other overload. |
| invariants | Construction leaves off/default options and empty slabs; it does not invent descriptors or mark any engine transaction committed. |
| ownership | Collector retains account through allocators; no caller arrays are borrowed. |
| failure | Account creation can fail; no unlimited fallback is substituted into a native runtime. |
| cost | One standalone account/control creation plus empty vector allocators; no row/descriptor scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  explicit Collector(const resource::MemoryAccount&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize collector ownership without collecting an event. |
| inputs / outputs | Binds descriptor and all three Cell-vector allocators to supplied account, observation purpose and observation:1. |
| invariants | Construction leaves off/default options and empty slabs; it does not invent descriptors or mark any engine transaction committed. |
| ownership | Collector retains account through allocators; no caller arrays are borrowed. |
| failure | Empty setup has no custom catch; later configure allocations retain account failure semantics. |
| cost | Fixed four empty allocator/vector setups; capacity admission occurs in configure. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 29–29](../../../../../src/runtime/statistics_collection.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] resource::MemoryAccount memory_account()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose an owning handle to the collector's actual existing allocation account. |
| inputs / outputs | Returns descriptors_.get_allocator().account() by value. |
| invariants | This is the same account owner and limit, not a grant refill or maximum-account replacement. |
| ownership | Returned handle retains the account; vector storage remains collector-owned. |
| failure | Noexcept shared handle copy, no explicit error path. |
| cost | Fixed owner-handle copy; no ledger/row scan or vector clone. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 30–41](../../../../../src/runtime/statistics_collection.hpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Collector(const Collector&) = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent copying/moving an active collector with borrowed slabs and nesting state. |
| inputs / outputs | All copy/move constructors and assignments in this declaration cluster are deleted. |
| invariants | One stable Collector address/protocol owns its arrays; detached Snapshot is the explicit owning-copy boundary. |
| ownership | No implicit slab rehome, array-sharing or ticket transfer operation is offered. |
| failure | Attempted use fails at compile time, not via runtime recovery. |
| cost | No runtime code or instrumentation. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void configure(Options,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a complete descriptor configuration at a quiescent allocating barrier. |
| inputs / outputs | Validates mode/sampling/max_cells/size arithmetic, root shape and nonroot parent existence, exact descriptor uniqueness, then builds descriptor plus three Cell arrays and checks actual capacities/external route payload before swap/reset. |
| invariants | Requires no pending scope. Strong guarantee: all throwing operations precede publication. max_cells admits all required strata together; no partial descriptor set or silently clipped configuration. |
| ownership | Copies descriptors into funded immutable observation array; old/new slabs and producer routes may coexist transiently on the same original account. |
| failure | logic_error for pending, invalid_argument for semantics, length_error for bounds, native account/allocation failures propagate. No broad catch or fallback. |
| cost | O(D^2) duplicate/parent validation plus O(D) copies/three slab initialization and actual vector allocations; external_bytes is a logical retained-component accounting addend, not an allocation by itself. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  Ticket admit(std::size_t root_descriptor)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start one outer observation attempt before source membership lookup. |
| inputs / outputs | Off returns inert; otherwise validates no pending scope/serial exhaustion, selects deterministic ordinal sampling, records attempt metadata, clears the entire attempt slab, marks invalid root if necessary and returns exact root Ticket. |
| invariants | Root facts arrive once later. Unselected attempts still clear dense scratch; sampling omits detail collection, not all lifecycle work. |
| ownership | Mutates preallocated numeric slabs and fixed flags only; no query rows/cursors or new account. |
| failure | Noexcept: misuse/exhaustion flags protocol/ordinal metadata and may return inert. Invalid root poisons attempt; no throwing rollback layer. |
| cost | O(Cell count) dense clear, even unsampled, plus fixed sampling/counter arithmetic; no heap allocation or clock read. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void physical_fact(bool changed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage one exact physical root membership fact independently of sampled detail. |
| inputs / outputs | Requires pending matching physical root and no prior staged input; writes inputs=1, changed/noop complement and input_staged=true. |
| invariants | Fact is private until successful outer finish; it is separate from occurrence/support event detail and remains known even if detail truncates. |
| ownership | Only fixed attempt Cell fields/metadata mutate; no row values or external references are stored. |
| failure | Noexcept; invalid duplicate/missing/wrong-kind protocol sets protocol_error and poisons any pending scope. |
| cost | Fixed validation/field stores with no allocation, clock or slab scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void logical_fact(bool changed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage one exact logical root membership fact independently of sampled detail. |
| inputs / outputs | Requires pending matching logical root and no prior staged input; writes inputs=1, changed/noop complement and input_staged=true. |
| invariants | Fact is private until successful outer finish; it is separate from occurrence/support event detail and remains known even if detail truncates. |
| ownership | Only fixed attempt Cell fields/metadata mutate; no row values or external references are stored. |
| failure | Noexcept; invalid duplicate/missing/wrong-kind protocol sets protocol_error and poisons any pending scope. |
| cost | Fixed validation/field stores with no allocation, clock or slab scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 42–42](../../../../../src/runtime/statistics_collection.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Ticket current_ticket()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply current serial/depth for internal nested admission. |
| inputs / outputs | Returns {active_serial_,depth_,0}. |
| invariants | Parent is intentionally zero here; nest() constructs the new child ticket with the real active parent. Do not finish arbitrary nested scopes with this synthetic parent field. |
| ownership | Inline values only, no retained owner. |
| failure | Noexcept scalar return, no validation/recovery. |
| cost | Fixed three-word construction. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 43–51](../../../../../src/runtime/statistics_collection.hpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Ticket begin(std::size_t physical_descriptor, bool changed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine root admission and immediate physical fact staging for standalone callers. |
| inputs / outputs | Calls admit then physical_fact(changed) only if returned Ticket is active. |
| invariants | Only physical roots fit this convenience path; logical-owner callers stage logical facts through the distinct method. |
| ownership | Uses existing funded slabs and returns inline ticket; no row ownership. |
| failure | Noexcept with admit/fact metadata/poison semantics, no new handler. |
| cost | Dense attempt clear from admit plus fixed fact stores, with no allocation/clock. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  Ticket nest(Ticket parent)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a nested collector scope in exact LIFO protocol without clearing the root attempt. |
| inputs / outputs | Checks pending/active serial/depth and counter maxima; increments serial/depth and returns ticket with previous active serial as parent. |
| invariants | Nested scope shares root sample/private cells and detail budget. It does not start another physical input or reset staged observations. |
| ownership | Only inline counters/flags; parent ticket is copied by value. |
| failure | Noexcept invalid protocol marks protocol_error and poisons current root, returning inert; no exceptions or allocation. |
| cost | Fixed checks/increments independent of descriptor count; no dense clear. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  bool finish(Ticket, bool commit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close a matching scope and publish only a valid successful outer observation transaction. |
| inputs / outputs | Requires exact active serial/depth; false commit poisons root, nested close restores parent; root requires one fact, publishes root Cells and only complete selected detail, updates metadata, then clears attempt slab. |
| invariants | Any nested abort/protocol fault prevents all root publication. Truncation discards staged detail but can preserve independently known successful root facts. No prefix of a selected sample is merged. |
| ownership | Moves no query rows/owners; merges preallocated numeric Cells and restores inline protocol state. |
| failure | Noexcept; off succeeds, invalid protocol returns false/flags poison. This reports observation validity, not engine commit success authority. |
| cost | Nested close fixed; root scans all attempt cells and merges eligible Cells (fixed 65-bin merge) then clears dense slab: O(D), no heap/clocks. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void occurrence(std::size_t descriptor, bool accepted)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage one numeric detail hook within the root sample budget. |
| inputs / outputs | For a valid selected occurrence detail cell, increments visited and accepted or rejected. |
| invariants | Repeated actual adapter calls are all observed; no key/value deduplication. detail() checks kind/table/operation/input_scope and marks invalid/truncated samples explicitly; unsampled/poisoned/truncated detail is skipped. |
| ownership | Only inline attempt Cell/65-bin counters and saturation flags mutate; no query payload is retained. |
| failure | Noexcept, fixed metadata flags represent invalid descriptor/protocol/detail-budget truncation; no exception/retry layer. |
| cost | Bounded scalar/histogram updates independent of rows/descriptors; no heap, clock or population scan after configuration. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void support(std::size_t descriptor, U64 before, U64 after)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage one numeric detail hook within the root sample budget. |
| inputs / outputs | After detail admission, unchanged before/after returns; changed values increment transitions/zero crossings and observe after in the fixed histogram. |
| invariants | Budget action is admitted before before==after check; after-value support events differ from current positive-key population and can include zero. detail() checks kind/table/operation/input_scope and marks invalid/truncated samples explicitly; unsampled/poisoned/truncated detail is skipped. |
| ownership | Only inline attempt Cell/65-bin counters and saturation flags mutate; no query payload is retained. |
| failure | Noexcept, fixed metadata flags represent invalid descriptor/protocol/detail-budget truncation; no exception/retry layer. |
| cost | Bounded scalar/histogram updates independent of rows/descriptors; no heap, clock or population scan after configuration. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void degree(std::size_t descriptor, U64 value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage one numeric detail hook within the root sample budget. |
| inputs / outputs | After detail admission, observes the actual touched degree or generalized pre-probe presence in the fixed numeric Cell. |
| invariants | Zero/repeated observations count as actual events; native degree and generalized 0/1 semantics are chosen by source descriptor/caller, not inferred by the collector. detail() checks kind/table/operation/input_scope and marks invalid/truncated samples explicitly; unsampled/poisoned/truncated detail is skipped. |
| ownership | Only inline attempt Cell/65-bin counters and saturation flags mutate; no query payload is retained. |
| failure | Noexcept, fixed metadata flags represent invalid descriptor/protocol/detail-budget truncation; no exception/retry layer. |
| cost | Bounded scalar/histogram updates independent of rows/descriptors; no heap, clock or population scan after configuration. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  bool reset()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clear observation history only at a quiescent caller boundary. |
| inputs / outputs | Returns false while pending; otherwise zeroes current/attempt/previous slabs and metadata, resets sampling/history/config tags and increments saturating reset generation. |
| invariants | Does not reset serial_ to permit stale-ticket reuse; engine state/source sequence are untouched. Explicit reset discards previous interval intentionally. |
| ownership | Retains vector capacities/account owners for reuse; no deallocation/replacement is needed. |
| failure | Noexcept boolean denial for pending, explicit saturation rather than wrapped generation. |
| cost | O(three dense Cell slabs), no heap or clocks; reset is not universally O(1). |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  bool rotate(U64 resolved_configuration,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a new observed semantic segment only after the actual mode change succeeds. |
| inputs / outputs | Returns false if pending, inert if off or same config without force; otherwise swaps current into previous, clears new current/attempt, rotates metadata/config tags and resets sample ordinal. |
| invariants | Only one previous segment is retained; another rotation marks replaced_history. force preserves a real boundary even when a saturated numeric segment tag is unchanged. |
| ownership | Reuses existing vector owners/capacities; no row copy, source reset or extra history container. |
| failure | Noexcept; caller supplies successful semantic change and current configuration, rather than using rotation as engine mode authority. |
| cost | O(current+attempt Cell count) dense clears and fixed swaps, no heap/clocks; prior retained values are bounded to one segment. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 52–52](../../../../../src/runtime/statistics_collection.hpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::span<const Cell> committed()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow collector-owned numeric observation arrays without capturing them. |
| inputs / outputs | Returns a const span over committed_. Current committed exact root and eligible complete-sample detail counters. |
| invariants | These are live component views, not owning Snapshot values; configure/reset/rotate/update can replace or change their interpretation/content. Read only at the caller's stable synchronous boundary. |
| ownership | Collector retains vector/account owners; returned span owns neither. Keep the collector alive and respect mutation invalidation. |
| failure | Noexcept span construction; no bounds validation, copy or recovery. |
| cost | Fixed pointer/length return, no allocation or scan. Explicit State::snapshot pays O(D) copy costs. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 53–53](../../../../../src/runtime/statistics_collection.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::span<const Cell> previous()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow collector-owned numeric observation arrays without capturing them. |
| inputs / outputs | Returns a const span over previous_. One prior segment slab; has_previous() determines whether it is available history. |
| invariants | These are live component views, not owning Snapshot values; configure/reset/rotate/update can replace or change their interpretation/content. Read only at the caller's stable synchronous boundary. |
| ownership | Collector retains vector/account owners; returned span owns neither. Keep the collector alive and respect mutation invalidation. |
| failure | Noexcept span construction; no bounds validation, copy or recovery. |
| cost | Fixed pointer/length return, no allocation or scan. Explicit State::snapshot pays O(D) copy costs. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 54–54](../../../../../src/runtime/statistics_collection.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::span<const Descriptor> descriptors()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow collector-owned numeric observation arrays without capturing them. |
| inputs / outputs | Returns a const span over descriptors_. Configured descriptor positions define all route IDs and Cell interpretation. |
| invariants | These are live component views, not owning Snapshot values; configure/reset/rotate/update can replace or change their interpretation/content. Read only at the caller's stable synchronous boundary. |
| ownership | Collector retains vector/account owners; returned span owns neither. Keep the collector alive and respect mutation invalidation. |
| failure | Noexcept span construction; no bounds validation, copy or recovery. |
| cost | Fixed pointer/length return, no allocation or scan. Explicit State::snapshot pays O(D) copy costs. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 55–55](../../../../../src/runtime/statistics_collection.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  const Metadata& metadata()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the collector's current observation lifecycle/protocol/saturation census. |
| inputs / outputs | Returns meta_ by const reference. |
| invariants | Reference is live collector state, not detached captured history. Caller holds stable exclusive component access and reads availability/saturation flags with values. |
| ownership | Borrowed reference requires collector lifetime and no incompatible mutation; it owns no account or rows. |
| failure | Noexcept reference return, no validation/catch. |
| cost | Fixed access, no graph clone, row scan, clock or allocation. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 56–56](../../../../../src/runtime/statistics_collection.hpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  const Metadata& previous_metadata()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the collector's prior segment metadata, meaningful together with has_previous. |
| inputs / outputs | Returns previous_meta_ by const reference. |
| invariants | Reference is live collector state, not detached captured history. Caller holds stable exclusive component access and reads availability/saturation flags with values. |
| ownership | Borrowed reference requires collector lifetime and no incompatible mutation; it owns no account or rows. |
| failure | Noexcept reference return, no validation/catch. |
| cost | Fixed access, no graph clone, row scan, clock or allocation. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 57–57](../../../../../src/runtime/statistics_collection.hpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  const Options& options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the collector's validated current collection mode/sampling/cell/detail ceilings. |
| inputs / outputs | Returns options_ by const reference. |
| invariants | Reference is live collector state, not detached captured history. Caller holds stable exclusive component access and reads availability/saturation flags with values. |
| ownership | Borrowed reference requires collector lifetime and no incompatible mutation; it owns no account or rows. |
| failure | Noexcept reference return, no validation/catch. |
| cost | Fixed access, no graph clone, row scan, clock or allocation. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 58–58](../../../../../src/runtime/statistics_collection.hpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Memory memory() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report actual collector vector-capacity payload accounting without claiming whole-query requested bytes. |
| inputs / outputs | Returns sizeof(Collector), capacities*sizeof elements for four vectors and their retained_payload_bytes sum. |
| invariants | Excludes allocator framing, separately owned producer routes, detached snapshots and old/new configuration overlap; State adjusts its own object/routes accounting. Payload arithmetic was admitted by configure. |
| ownership | Inline numeric result retains no native pointer or owner. |
| failure | Noexcept fixed arithmetic under configured capacity invariants, no account snapshot or error mapping. |
| cost | Four capacity reads/products and fixed sums, no row/ledger scan or allocation. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 59–59](../../../../../src/runtime/statistics_collection.hpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool pending()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whether any private collector attempt scope remains active. |
| inputs / outputs | Returns depth_ != 0 by value. |
| invariants | This numeric/flag fact is observation metadata, not live engine/source authority or proof. Interpret generation saturation/history availability with its companion metadata. |
| ownership | Inline result owns no component span, account or row. |
| failure | Declared noexcept, no failure/catch. |
| cost | Fixed scalar load/check without allocation, clock or scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 60–60](../../../../../src/runtime/statistics_collection.hpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool has_previous()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whether a prior semantic segment was retained. |
| inputs / outputs | Returns has_previous_ by value. |
| invariants | This numeric/flag fact is observation metadata, not live engine/source authority or proof. Interpret generation saturation/history availability with its companion metadata. |
| ownership | Inline result owns no component span, account or row. |
| failure | Declared noexcept, no failure/catch. |
| cost | Fixed scalar load/check without allocation, clock or scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 61–61](../../../../../src/runtime/statistics_collection.hpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool replaced_history()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whether a second rotation replaced older interval history. |
| inputs / outputs | Returns replaced_history_ by value. |
| invariants | This numeric/flag fact is observation metadata, not live engine/source authority or proof. Interpret generation saturation/history availability with its companion metadata. |
| ownership | Inline result owns no component span, account or row. |
| failure | Declared noexcept, no failure/catch. |
| cost | Fixed scalar load/check without allocation, clock or scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 62–62](../../../../../src/runtime/statistics_collection.hpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L62:sha256:c4b9c3fab52d74ef772a80090ef4a35760b5a3b41ee88be876eed0db22a2fcbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/statistics_collection.hpp: opens/branches compile-time guard \`#ifdef CROWN_RUNTIME_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0019

[Lines 63–67](../../../../../src/runtime/statistics_collection.hpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void seed_report_saturation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject numeric saturation boundaries only in testing builds. |
| inputs / outputs | Sets selected committed counters/saturation/bin\[64\] and current committed metadata to UINT64_MAX. |
| invariants | Compiled only under CROWN_RUNTIME_TESTING. It changes diagnostic observations for boundary tests, not engine row/source ownership or public commit authority. |
| ownership | Mutates preallocated numeric cells; no payload or new owner is created. |
| failure | Noexcept, with no additional allocation/recovery mechanism. |
| cost | O(committed Cell count) explicit test injection, no heap or clock. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 68–68](../../../../../src/runtime/statistics_collection.hpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L68:sha256:9a349bbd1a21104f051e34b2c8a9e70cc7fbb50bc19a67781f2a140c386d9438
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/statistics_collection.hpp: closes the matching compile-time guard. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0021

[Lines 69–69](../../../../../src/runtime/statistics_collection.hpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  U64 generation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose saturating explicit reset/configure generation. |
| inputs / outputs | Returns generation_ by value. |
| invariants | This numeric/flag fact is observation metadata, not live engine/source authority or proof. Interpret generation saturation/history availability with its companion metadata. |
| ownership | Inline result owns no component span, account or row. |
| failure | Declared noexcept, no failure/catch. |
| cost | Fixed scalar load/check without allocation, clock or scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 70–70](../../../../../src/runtime/statistics_collection.hpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool generation_saturated()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whether reset generation can no longer represent all boundaries numerically. |
| inputs / outputs | Returns generation_saturated_ by value. |
| invariants | This numeric/flag fact is observation metadata, not live engine/source authority or proof. Interpret generation saturation/history availability with its companion metadata. |
| ownership | Inline result owns no component span, account or row. |
| failure | Declared noexcept, no failure/catch. |
| cost | Fixed scalar load/check without allocation, clock or scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 71–71](../../../../../src/runtime/statistics_collection.hpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  U64 configuration()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose current resolved configuration tag supplied by rotation. |
| inputs / outputs | Returns configuration_ by value. |
| invariants | This numeric/flag fact is observation metadata, not live engine/source authority or proof. Interpret generation saturation/history availability with its companion metadata. |
| ownership | Inline result owns no component span, account or row. |
| failure | Declared noexcept, no failure/catch. |
| cost | Fixed scalar load/check without allocation, clock or scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 72–72](../../../../../src/runtime/statistics_collection.hpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  U64 previous_configuration()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose previous rotated configuration tag. |
| inputs / outputs | Returns previous_configuration_ by value. |
| invariants | This numeric/flag fact is observation metadata, not live engine/source authority or proof. Interpret generation saturation/history availability with its companion metadata. |
| ownership | Inline result owns no component span, account or row. |
| failure | Declared noexcept, no failure/catch. |
| cost | Fixed scalar load/check without allocation, clock or scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 73–88](../../../../../src/runtime/statistics_collection.hpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  friend struct CollectorTestAccess;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep standalone boundary injection in a private friend seam. |
| inputs / outputs | Friend access can inspect/set numeric protocol test state; normal public methods expose no setter for these members. |
| invariants | This declaration is an encapsulation/testing boundary, not a security guarantee or actual-owner Evidence constructor. |
| ownership | No runtime owner or allocation is introduced. |
| failure | Compile-time access declaration only. |
| cost | No executable work. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  Cell* detail(std::size_t, Kind) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one sampled detail event against the active root descriptor and detail budget. |
| inputs / outputs | Checks mode/pending, descriptor kind/table/operation/input_scope, poison/selection/truncation, physical no-op protocol, then increments action count and returns mutable attempt Cell or null. |
| invariants | Invalid routes/no-op hooks/detail exhaustion invalidate the detailed sample while independently staged root facts can remain publishable. Unsampled paths do not consume detail actions. |
| ownership | Returned Cell pointer borrows preallocated attempt slab only until collector mutation/finish; no query row or native key is retained. |
| failure | Noexcept flags/null dispatch; no thrown diagnostic strings, new handlers or engine recovery. |
| cost | Bounded checks/counter changes with no allocation, clocks or descriptor scan. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void clear(MemoryVector<Cell>&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clear one dense numeric slab while recording explicit lifecycle cost counters. |
| inputs / outputs | Assigns Cell{} to every element and saturating-increments meta_.cleared_cells. |
| invariants | Array capacity/allocator remain unchanged; clearing is real lifecycle work even when detail sampling is off for the attempt. |
| ownership | Mutates only owned numeric array and metadata; no external row view is touched. |
| failure | Noexcept fixed Cell assignment/counters. |
| cost | O(slab size) with fixed 65-bin Cells; no replacement allocation or clock. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  Options options_{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the collector's owned slabs and exact private root/nesting lifecycle state. |
| inputs / outputs | options_/descriptors_ bind configuration; committed_/attempt_/previous_ hold numeric histories; meta_/previous_meta_ track lifecycle. serial_/active_serial_/depth_ enforce LIFO; ordinal_ samples attempts; actions_ bounds detail; generation_/configuration tags identify boundaries. |
| invariants | physical_ selects the active root; selected_/truncated_/poisoned_/ordinal_done_/input_staged_ govern all-or-nothing detail and known root facts. Saturation/history flags remain explicit. No per-attempt dynamic containers or query row values exist. |
| ownership | Vectors own accounted observation arrays; flags/counters are inline. Borrowed spans are invalidated or changed by lifecycle methods as documented. |
| failure | configure is the allocating/throwing barrier; event hooks preserve preallocated no-throw operation and mark unavailable facts, not fabricated validity. |
| cost | Storage O(D) numeric Cells/descriptors with fixed histogram size; root lifecycle scans are O(D), even with no selected detail. This layout adds no per-row logging/index or hidden clock. |
| Design | [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [docs/code_review.md](../../../../code_review.md) |
