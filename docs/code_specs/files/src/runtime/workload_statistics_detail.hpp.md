# `src/runtime/workload_statistics_detail.hpp` — block usage map

[Source](../../../../../src/runtime/workload_statistics_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `e48b6aa717a0ce0ff88c21feb19f80fc26bc333bcf813a88b7ecef5963736975`. 51 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/runtime/workload_statistics_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Original-account routes and numeric slabs; snapshots explicitly clone committed · [reviewed contract](#b0001) |
| [B0002 · 11–12](../../../../../src/runtime/workload_statistics_detail.hpp#L11) | Callable definition: public: State():State(resource::MemoryAccount::create(std::numeric_limits&lt;U64&gt;::max())) | calls resource::MemoryAccount::create, max · [reviewed contract](#b0002) |
| [B0003 · 13–14](../../../../../src/runtime/workload_statistics_detail.hpp#L13) | Callable definition: explicit State(const resource::MemoryAccount& account):collector_(account), routes_(resource::MemoryAllocator&lt;std::size_t&gt;(accoun… | calls collector_, routes_ · [reviewed contract](#b0003) |
| [B0004 · 15–16](../../../../../src/runtime/workload_statistics_detail.hpp#L15) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 17–17](../../../../../src/runtime/workload_statistics_detail.hpp#L17) | Callable definition: \[\[nodiscard\]\] Options options() const noexcept | calls ; returns collector_.options() · [reviewed contract](#b0005) |
| [B0006 · 18–18](../../../../../src/runtime/workload_statistics_detail.hpp#L18) | controls preprocessing. |  · [reviewed contract](#b0006) |
| [B0007 · 19–22](../../../../../src/runtime/workload_statistics_detail.hpp#L19) | Callable definition: void seed_report_saturation() noexcept | calls  · [reviewed contract](#b0007) |
| [B0008 · 23–51](../../../../../src/runtime/workload_statistics_detail.hpp#L23) | controls preprocessing; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Initial binding does not rotate a stream; constructor replay stays off. · [reviewed contract](#b0008) |

## B0001

[Lines 1–10](../../../../../src/runtime/workload_statistics_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class State {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind plan-derived workload routes to one transactional numeric collector and interval identity. |
| inputs / outputs | collector_ owns funded observation slabs; routes_ maps group/local dense IDs to descriptors. Fixed stride/offset fields encode root, occurrence, derivation, survivor, parent, visible and signed edge positions. ModeFacts and generations label current/one previous segment. |
| invariants | Native runtime constructors pass their original account. Configuration/reset/mode switching are explicit boundaries; ordinary hooks capture actual attempted operations without query rows/hash recomputation. Single-writer synchronous use; no thread synchronization. |
| ownership | State owns only funded numeric routes/collector arrays and inline modes/tags, retaining no row/text/cursor or owner pointer. Detached Snapshot explicitly copies committed arrays on the same account. |
| failure | Configure validates/funds before publication with strong guarantee; hot hooks are noexcept and preserve collector invalid/protocol/saturation metadata. No fallback account or generic recovery. |
| cost | State storage is O(descriptor+route count) with fixed numeric histograms. Configuration includes repeated plan-route validation and O(D^2) Collector validation. Detail hooks bounded; root admit/finish/reset/mode rotation perform dense O(D) Cell scans. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–12](../../../../../src/runtime/workload_statistics_detail.hpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  State():State(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an explicit standalone workload component account for isolated use. |
| inputs / outputs | Delegates to account-taking State with MemoryAccount::create(UINT64_MAX). |
| invariants | Native runtimes use the explicit existing-account overload; this is not a fallback for account exhaustion or a native cap override. |
| ownership | New standalone account is retained by collector/routes allocators; no engine row or source owner exists here. |
| failure | Account allocation failure propagates, with no substitute/retry. |
| cost | Actual standalone account/control creation plus empty component setup, no plan/row scan. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 13–14](../../../../../src/runtime/workload_statistics_detail.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  explicit State(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind workload observations and dense route storage to an existing allocation account. |
| inputs / outputs | Constructs Collector(account) and empty routes_ with observation purpose/observation:1 attribution. |
| invariants | This constructor neither validates/configures a plan nor admits descriptors or engine transactions. |
| ownership | Retains original account through funded allocators; no deep account copy or row storage. |
| failure | No local catch; later configuration allocations use this exact account and its real cap. |
| cost | Fixed empty allocator/collector setup, with actual route/slab allocation deferred to configure. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 15–16](../../../../../src/runtime/workload_statistics_detail.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Plan> void configure(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive and atomically install complete observation strata/routes from the actual immutable plan. |
| inputs / outputs | Validates mode/sampling, dense node/input/edge identities and base routes, computes checked stride/groups/descriptor payload, builds candidate descriptors/routes, calls Collector.configure then swaps routes and fixed offsets/generation metadata. |
| invariants | Quiescent-only allocating barrier; all possible throws precede publication. Physical groups are every source table insert/erase; logical owner groups are logical insert/erase. Off keeps descriptors/routes empty while retaining correct fixed metadata. No query row or source-binding hash scan. |
| ownership | Candidate arrays and old/new overlap are funded on the same existing account; old configuration survives all prepublication failures. Input plan is borrowed only while deriving numeric IDs. |
| failure | Invalid metadata/options/size/cell/account/allocation failures propagate; Collector rejects pending and preserves previous state. No catch, partial strata or unlimited fallback. |
| cost | Scans node/input/edge/base-route metadata; std::count over each input route and per-group plan loops can repeat, followed by O(D^2) Collector checks and actual route/four-array allocations. No claim of constant or fully linear setup. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void reset(U64 sequence)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset workload interval only if the collector is quiescent. |
| inputs / outputs | If collector.reset succeeds, sets interval_start to supplied committed sequence, clears previous bounds/modes and segment/saturation; otherwise returns without metadata change. |
| invariants | Engine source/row state and mode binding remain unchanged. Sampling history and report generation are explicit observation controls, not source progress. |
| ownership | Reuses owned arrays/account; no detached snapshots are rewritten. |
| failure | Noexcept and pending denial is silent by this private caller contract; public owner controls when reset is legal. |
| cost | Dense three-slab Collector reset plus fixed interval metadata stores, no heap/clocks. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 17–17](../../../../../src/runtime/workload_statistics_detail.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] Options options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy current validated fixed workload collection options. |
| inputs / outputs | Returns collector_.options() by value. |
| invariants | Options describe mode/max_cells/sample/detail ceilings, not current engine mode or a new allocation/work allowance. |
| ownership | Inline option result owns no row/span/account; State remains owner of arrays. |
| failure | Declared noexcept; no validation/recovery. |
| cost | Fixed Options copy, no allocation or scan. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 18–18](../../../../../src/runtime/workload_statistics_detail.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L18:sha256:c4b9c3fab52d74ef772a80090ef4a35760b5a3b41ee88be876eed0db22a2fcbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/workload_statistics_detail.hpp: opens/branches compile-time guard \`#ifdef CROWN_RUNTIME_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0007

[Lines 19–22](../../../../../src/runtime/workload_statistics_detail.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void seed_report_saturation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject numeric workload/collector saturation only in test builds. |
| inputs / outputs | Seeds collector report saturation and sets configuration_generation_/segment_ and flags to UINT64_MAX/saturated. |
| invariants | CROWN_RUNTIME_TESTING only; test injection cannot create engine commit, source, checked plan or actual-owner Evidence authority. |
| ownership | Mutates only numeric collector/state fields in preallocated storage. |
| failure | Noexcept with no account replacement or error handler. |
| cost | O(committed Cell count) test-only seeding plus fixed state fields; no heap/clocks. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 23–51](../../../../../src/runtime/workload_statistics_detail.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] Snapshot snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach an owning numeric current/previous workload snapshot on the actual program account. |
| inputs / outputs | Funds Snapshot::Data, copies current stamp/options/modes/descriptors/committed/previous arrays and metadata, computes component object/routes capacity accounting, and combines explicit pending with collector.pending(). |
| invariants | Snapshot excludes attempt-private cells and native row payloads/pins. Facts describe the supplied stable committed owner/sequence plus interval/saturation metadata; caller supplies the actual program/owner boundary. Older snapshots are not modified by later updates/rotations. |
| ownership | Result retains CompiledProgram/original account and deep copied funded numeric arrays; native runtime rows are not referenced. Snapshot handles subsequently share Data, while with_pending explicitly clones arrays. |
| failure | Actual account/allocation/copy failure propagates before any snapshot escapes; source collector is read-only and prior snapshots remain intact. |
| cost | O(descriptor/current/previous Cell counts) numeric copying and actual shared/array allocations, plus fixed capacity arithmetic; no table/row scan or free shared-wrapper-only capture claim. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  [[nodiscard]] Ticket physical(TableId,SetOperation)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose actual source-table/sign root for one physical input observation. |
| inputs / outputs | Computes table*2+operation index with host overflow guard and enters that group. |
| invariants | Valid plan routes identify each table/sign; overflow/out-of-range becomes absent/invalid descriptor metadata, not a wrapped valid route. No source membership is read here. |
| ownership | Returns inline collector Ticket; uses preallocated routes/slabs and retains no input row. |
| failure | Noexcept flags/protocol behavior is delegated to enter/Collector. |
| cost | Fixed checked route arithmetic plus root dense attempt clear or fixed nested admission; no heap/clock. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  [[nodiscard]] Ticket logical(SetOperation)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the sign-only root for a lower logical-owner observation. |
| inputs / outputs | Converts operation to logical group and calls enter(). |
| invariants | Logical root has no physical-table denominator or source membership authority. Nested calls share the active outer root. |
| ownership | Only inline ticket/numeric routes; no logical tuple is retained. |
| failure | Noexcept collector protocol flags handle invalid/misordered use. |
| cost | Fixed group choice plus root dense clear or fixed nested entry; no heap/clocks. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void physical_fact(bool changed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage the independently known physical changed/noop input fact after membership lookup. |
| inputs / outputs | Forwards to Collector.physical_fact only when a collector scope is pending. |
| invariants | Exactly one root fact is expected; duplicate/wrong-kind staging invalidates protocol. Sampling/truncated detail does not erase known root fact. |
| ownership | Only preallocated numeric Cell and flags mutate; no source row copy. |
| failure | Noexcept delegation; no catch/retry or actual source acknowledgement. |
| cost | Fixed pending check and scalar stores, no allocation or row scan. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void logical_fact(Ticket,bool changed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage one changed/noop fact only for an outer logical-owner root. |
| inputs / outputs | Forwards when ticket.serial!=0, depth==1 and physical_owner_ is false. |
| invariants | Nested logical support updates beneath a physical transaction must not create extra root input denominators. |
| ownership | Only inline Ticket/fact values; no row or source owner retained. |
| failure | Noexcept; Collector applies precise pending/root-kind/protocol checks. |
| cost | Fixed conditions and scalar stores, no heap/clock. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void finish(Ticket,bool commit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close exact native observation scope with actual engine success/failure. |
| inputs / outputs | Nonzero ticket forwards to Collector.finish, preserving nested/root all-or-nothing publication rules. |
| invariants | No detail prefix from aborted/truncated selected attempt becomes complete. This hook observes commit outcome and does not itself commit engine state. |
| ownership | Only owned numeric arrays/counters mutate; ticket has no row/account owner. |
| failure | Noexcept invalid protocol sets collector flags; no exception recovery layer. |
| cost | Nested fixed work; root dense merge/clear O(D) even with unsampled inputs, without new allocation or clock. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void occurrence(OccurrenceId,bool accepted)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe one actual adapter visit result at its compiled occurrence route. |
| inputs / outputs | Routes occurrence_offset+ID and calls Collector.occurrence unless off. |
| invariants | Actual accepted/rejected calls, including repetitions, are counted; no row-key deduplication. IDs/role/offset arithmetic are from admitted immutable plan/caller routing; Collector additionally validates resolved descriptor scope/kind. |
| ownership | Only numeric values are staged; no query key/string/row or live cursor retained. |
| failure | Noexcept; off is inert, invalid detail route flags/truncates sample without allocating exception diagnostics. |
| cost | Fixed route arithmetic and bounded collector detail/histogram work; no population scan, heap or clocks. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void derivation(OccurrenceId,U64 before,U64 after)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe a native derivation-count transition at the actual occurrence route. |
| inputs / outputs | Routes derivation_offset+ID and calls Collector.support unless off. |
| invariants | Counts physical derivations, distinct from survivor/parent/visible support population. IDs/role/offset arithmetic are from admitted immutable plan/caller routing; Collector additionally validates resolved descriptor scope/kind. |
| ownership | Only numeric values are staged; no query key/string/row or live cursor retained. |
| failure | Noexcept; off is inert, invalid detail route flags/truncates sample without allocating exception diagnostics. |
| cost | Fixed route arithmetic and bounded collector detail/histogram work; no population scan, heap or clocks. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void support(NodeId,SupportRole,U64 before,U64 after)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe a named S/P/E support-count transition. |
| inputs / outputs | Selects survivor/parent/visible offset from actual role then routes node and calls Collector.support unless off. |
| invariants | Internal callers pass survivors, parent_support or visible; other roles are not validated by this offset selector. These are after-value events rather than current-state key histograms. IDs/role/offset arithmetic are from admitted immutable plan/caller routing; Collector additionally validates resolved descriptor scope/kind. |
| ownership | Only numeric values are staged; no query key/string/row or live cursor retained. |
| failure | Noexcept; off is inert, invalid detail route flags/truncates sample without allocating exception diagnostics. |
| cost | Fixed route arithmetic and bounded collector detail/histogram work; no population scan, heap or clocks. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void touched(std::size_t edge,bool appeared,U64 degree)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe one actual signed child-edge degree/presence probe. |
| inputs / outputs | Routes edge_offset+2*edge+sign and calls Collector.degree unless off. |
| invariants | Compiled descriptor distinguishes native reverse-bucket degree from generalized pre-probe 0/1 presence; zeros/repeated events are retained. IDs/role/offset arithmetic are from admitted immutable plan/caller routing; Collector additionally validates resolved descriptor scope/kind. |
| ownership | Only numeric values are staged; no query key/string/row or live cursor retained. |
| failure | Noexcept; off is inert, invalid detail route flags/truncates sample without allocating exception diagnostics. |
| cost | Fixed route arithmetic and bounded collector detail/histogram work; no population scan, heap or clocks. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  void modes(ModeFacts,U64 sequence,bool initial=false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record a successful semantic mode boundary without mixing observation intervals. |
| inputs / outputs | Initial/unbound call binds ModeFacts without rotation; unchanged returns; change stores previous modes/bounds, advances segment with saturation and force-rotates collector. |
| invariants | Caller invokes only after successful semantic mode switch at quiescent boundary. force ensures actual boundary survives saturated segment tag; constructor replay remains observation-off. |
| ownership | Only inline metadata and reused numeric slab owners; older Snapshot graphs stay unchanged. |
| failure | Noexcept; the private caller guarantees no pending collector (rotate refusal is not used as semantic rollback). No added handler or allocation. |
| cost | Fixed comparisons plus O(D) current/attempt clears on real mode rotation; no clocks/heap. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  static constexpr std::size_t absent=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use an impossible descriptor position as explicit invalid/off route sentinel. |
| inputs / outputs | absent is SIZE_MAX; route/enter propagate it to Collector descriptor checks instead of indexing it. |
| invariants | Admitted route/descriptor payload arithmetic prevents valid arrays from occupying this sentinel position. |
| ownership | Compile-time inline scalar, no owned storage. |
| failure | No runtime throw; collector marks invalid descriptor when admitted as an erroneous route. |
| cost | Compile-time constant, no executable overhead beyond existing comparisons. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  [[nodiscard]] std::size_t route(std::size_t local)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve one compiled local position in the currently active input group. |
| inputs / outputs | Checks local&lt;stride, nonzero stride and active_group&lt;routes.size/stride before reading group*stride+local, otherwise returns absent. |
| invariants | Bounds check precedes multiplication/indexing; route entries themselves are validated/configured descriptor positions or absent. |
| ownership | Returns inline index into State-owned immutable-until-configure route array; no external pointer. |
| failure | Noexcept invalid group/local is sentinel rather than throw; Collector later marks wrong detail/root use. |
| cost | Fixed bound arithmetic/one route lookup without allocation or descriptor scan. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  [[nodiscard]] Ticket enter(std::size_t group)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose root/nested workload observation using one existing collector attempt. |
| inputs / outputs | Off returns inert; pending collector calls nest(current_ticket); otherwise records active_group and admits its root route. |
| invariants | Nested scope does not replace active group, clear staged cells or start another input/sample; root clears dense attempt slab even if unsampled. |
| ownership | Inline Ticket and preallocated state only; no input row retained. |
| failure | Noexcept with Collector protocol/ordinal flags, no new handler. |
| cost | Fixed nested path; O(D) root clear; no heap/clocks. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  statistics_collection::Collector collector_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own compact native observation storage and plan-derived route/interval metadata. |
| inputs / outputs | collector_/routes_ own accounted arrays; stride_/active_group_/offsets encode dense positions; physical_owner_/modes_bound_ distinguish owner and binding; current/previous ModeFacts, generations, sequence bounds and saturation flags label intervals. |
| invariants | No per-input dynamic container, runtime row, catalog hash or owner pointer is stored. Prior history is one numeric segment; actual mode rotation is forced even at saturated segment label. |
| ownership | Arrays retain original account; scalar fields are inline. State does not share its mutable arrays with detached snapshots. |
| failure | Configure owns all throwing allocation and strong publication; hook methods maintain bounded numeric flags and do not add recovery scaffolding. |
| cost | O(routes+Cells+descriptors) retained payload plus real account framing. Root lifecycle scans remain dense; hot detail routing has fixed arithmetic. |
| Design | [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.hpp](../../../../../src/runtime/statistics_collection.hpp), [src/runtime/statistics_collection.cpp](../../../../../src/runtime/statistics_collection.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/workload_statistics_test.cpp](../../../../../tests/unit/workload_statistics_test.cpp), [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |
