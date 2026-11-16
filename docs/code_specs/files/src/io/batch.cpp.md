# `src/io/batch.cpp` — block usage map

[Source](../../../../../src/io/batch.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `1f4c834dadd68f4a20cc23d577c34b5bd01e535b636c15cfcac86f0b40f86e1a`. 327 lines partitioned into 53 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../src/io/batch.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 16–18](../../../../../src/io/batch.cpp#L16) | Callable definition: void require(bool condition,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool condition,std::string_view code,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 19–22](../../../../../src/io/batch.cpp#L19) | Callable definition: std::size_t add(std::size_t a,std::size_t b) | calls require, max; guard require(b&lt;=std::numeric_limits&lt;std::size_t&gt;::max()-a,"resource_limit","typed input size accounting …; returns a+b · [reviewed contract](#b0003) |
| [B0004 · 23–26](../../../../../src/io/batch.cpp#L23) | Callable definition: std::size_t slots(std::size_t n,std::size_t width) | calls require, max; guard require(n&lt;=std::numeric_limits&lt;std::size_t&gt;::max()/width,"resource_limit","typed input capacity acc…; returns n*width · [reviewed contract](#b0004) |
| [B0005 · 27–34](../../../../../src/io/batch.cpp#L27) | Callable definition: std::size_t row_bytes(const Row& row) | calls slots, capacity, add; returns bytes; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 35–44](../../../../../src/io/batch.cpp#L35) | Callable definition: std::size_t item_payload(const InputItem& item) | calls std::visit, constexpr, row_bytes, add; returns std::visit(\[\](const auto& event) {; bytes; growth insert · [reviewed contract](#b0006) |
| [B0007 · 45–48](../../../../../src/io/batch.cpp#L45) | Callable definition: std::uint64_t sequence_of(const InputItemView& item) noexcept | calls ; returns event-&gt;update.sequence; std::get&lt;WindowCommandView&gt;(item).sequence · [reviewed contract](#b0007) |
| [B0008 · 49–52](../../../../../src/io/batch.cpp#L49) | Callable definition: const std::optional&lt;SourcePositionView&gt;& position_of(const InputItemView& item) noexcept | calls ; returns event-&gt;source_position; std::get&lt;WindowCommandView&gt;(item).source_position · [reviewed contract](#b0008) |
| [B0009 · 53–54](../../../../../src/io/batch.cpp#L53) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 55–59](../../../../../src/io/batch.cpp#L55) | Type/record definition: struct TransportBatch::Data |  · [reviewed contract](#b0010) |
| [B0011 · 60–60](../../../../../src/io/batch.cpp#L60) | Explanatory comments or spacing. | source comment (unverified): // Ordered transport preserves each event barrier; it is not a net transaction. · [reviewed contract](#b0011) |
| [B0012 · 61–79](../../../../../src/io/batch.cpp#L61) | Callable definition: TransportBatch::TransportBatch(std::vector&lt;InputItem&gt; items,BatchLimits limits) | calls require, size, empty, valueless_by_exception; guard require(items.size()&lt;=limits.events,"resource_limit","transport batch event limit exceeded");; growth make_unique, push_back; 2 loop sites; source comment (unverified): // Ordered transport preserves each event barrier; it is not a net transaction. · [reviewed contract](#b0012) |
| [B0013 · 80–82](../../../../../src/io/batch.cpp#L80) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 83–83](../../../../../src/io/batch.cpp#L83) | Callable definition: bool TransportBatch::empty() const noexcept | calls empty; returns !data_ \|\| data_-&gt;items.empty() · [reviewed contract](#b0014) |
| [B0015 · 84–84](../../../../../src/io/batch.cpp#L84) | Callable definition: std::size_t TransportBatch::size() const noexcept | calls size; returns data_?data_-&gt;items.size():0 · [reviewed contract](#b0015) |
| [B0016 · 85–85](../../../../../src/io/batch.cpp#L85) | Callable definition: std::size_t TransportBatch::accounted_bytes() const noexcept | calls ; returns data_?data_-&gt;bytes:0 · [reviewed contract](#b0016) |
| [B0017 · 86–94](../../../../../src/io/batch.cpp#L86) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |
| [B0018 · 95–99](../../../../../src/io/batch.cpp#L95) | Callable definition: static const Row* row_of(const InputItem& input) noexcept | calls ; returns &event-&gt;update.values; &insert-&gt;values; growth insert · [reviewed contract](#b0018) |
| [B0019 · 100–104](../../../../../src/io/batch.cpp#L100) | Callable definition: static TableId table_of(const InputItem& input) noexcept | calls ; returns event-&gt;update.table; insert-&gt;table; growth insert · [reviewed contract](#b0019) |
| [B0020 · 105–108](../../../../../src/io/batch.cpp#L105) | Callable definition: static InputItemView borrow(const InputItem& input) noexcept | calls InputEventView::borrow, WindowCommandView::borrow; returns InputEventView::borrow(*event); WindowCommandView::borrow(std::get&lt;WindowCommand&gt;(input)) · [reviewed contract](#b0020) |
| [B0021 · 109–112](../../../../../src/io/batch.cpp#L109) | Callable definition: static std::size_t request(std::uint64_t bytes) | calls require, max; guard require(bytes&lt;=std::numeric_limits&lt;std::size_t&gt;::max(),"resource_limit","typed input capacity accou…; returns static_cast&lt;std::size_t&gt;(bytes) · [reviewed contract](#b0021) |
| [B0022 · 113–121](../../../../../src/io/batch.cpp#L113) | Callable definition: static std::size_t owned_bytes(const InputItem& input,input_detail::RowIssue issue) | calls request, resource::MemoryAccount::allocation_bytes, row_of, add; returns bytes · [reviewed contract](#b0022) |
| [B0023 · 122–133](../../../../../src/io/batch.cpp#L122) | Callable definition: Item(const resource::MemoryAccount& account,const InputItemView& input):value(input) | calls value, size, storage::AccountedRow::copy_view, position_of; growth copy_of, insert · [reviewed contract](#b0023) |
| [B0024 · 134–135](../../../../../src/io/batch.cpp#L134) | Explanatory comments or spacing. | source comment (unverified): // Keep a permanent malformed-row issue instead of freezing unusable values. · [reviewed contract](#b0024) |
| [B0025 · 136–150](../../../../../src/io/batch.cpp#L136) | Callable definition: Item(const resource::MemoryAccount& account,const InputItem& input,input_detail::RowIssue problem) :value(borrow(input)),issue(pr… | calls value, borrow, issue, bytes; growth copy_of, insert; source comment (unverified): // Keep a permanent malformed-row issue instead of freezing unusable values. · [reviewed contract](#b0025) |
| [B0026 · 151–151](../../../../../src/io/batch.cpp#L151) | Closes surrounding scope/type. |  · [reviewed contract](#b0026) |
| [B0027 · 152–162](../../../../../src/io/batch.cpp#L152) | Type/record definition: struct Batch | 1 loop sites; source comment (unverified): // Detach each link before destruction: a large offered batch must not · [reviewed contract](#b0027) |
| [B0028 · 163–173](../../../../../src/io/batch.cpp#L163) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0028) |
| [B0029 · 174–179](../../../../../src/io/batch.cpp#L174) | Callable definition: Data(const resource::MemoryAccount& memory,CatalogSource schema,QueueMode kind,QueueLimits cap,InputLimits input_cap,bool admitte… | calls account, catalog, std::move, mode; guard require(mode==QueueMode::physical \|\| mode==QueueMode::window,"invalid_input_options","unknown typed… · [reviewed contract](#b0029) |
| [B0030 · 180–180](../../../../../src/io/batch.cpp#L180) | Callable definition: ~Data() noexcept | calls std::move; 1 loop sites · [reviewed contract](#b0030) |
| [B0031 · 181–185](../../../../../src/io/batch.cpp#L181) | Callable definition: input_detail::RowIssue row_issue(const InputItem& input) const | calls Item::row_of, catalog_source_detail::read, input_detail::row_issue, Item::table_of; returns {}; catalog_source_detail::read(catalog,\[&\](const auto& schema){return input_detail::row_issue( · [reviewed contract](#b0031) |
| [B0032 · 186–186](../../../../../src/io/batch.cpp#L186) | Closes surrounding scope/type. |  · [reviewed contract](#b0032) |
| [B0033 · 187–189](../../../../../src/io/batch.cpp#L187) | Callable definition: TypedQueue::TypedQueue(CatalogSource catalog,QueueMode mode,QueueLimits limits,InputLimits input_limits) :TypedQueue(resource::Me… | calls TypedQueue, resource::MemoryAccount::create, max, std::move · [reviewed contract](#b0033) |
| [B0034 · 190–193](../../../../../src/io/batch.cpp#L190) | Callable definition: TypedQueue::TypedQueue(const resource::MemoryAccount& account,CatalogSource catalog,QueueMode mode, QueueLimits limits,InputLimit… | calls data_, std::move; growth make_accounted_unique · [reviewed contract](#b0034) |
| [B0035 · 194–194](../../../../../src/io/batch.cpp#L194) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0035) |
| [B0036 · 195–205](../../../../../src/io/batch.cpp#L195) | Callable definition: TypedQueue::TypedQueue(const resource::MemoryAccount& account,CatalogSource catalog,const QueueCheckpoint& state,const SourceStat… | calls data_, positions, checkpoint_detail::require, size; guard checkpoint_detail::require(!state.input_limits.records \|\| state.progress.sequence&lt;=*state.input_lim…; returns result; growth make_accounted_unique · [reviewed contract](#b0036) |
| [B0037 · 206–206](../../../../../src/io/batch.cpp#L206) | Callable definition: QueueCheckpoint TypedQueue::checkpoint_state() const | calls checkpoint_state; returns checkpoint_state(SourceStateLimits{}) · [reviewed contract](#b0037) |
| [B0038 · 207–213](../../../../../src/io/batch.cpp#L207) | Callable definition: QueueCheckpoint TypedQueue::checkpoint_state(const SourceStateLimits& limits) const | calls checkpoint_detail::require, bool, positions, checkpoint_detail::hash; guard checkpoint_detail::require(bool(data_));const auto& d=*data_;; returns {AccountedInputProgress(d.account,d.accepted),d.mode,d.limits,d.input_limits,d.stats.closed,hash,bu… · [reviewed contract](#b0038) |
| [B0039 · 214–215](../../../../../src/io/batch.cpp#L214) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0039) |
| [B0040 · 216–249](../../../../../src/io/batch.cpp#L216) | Callable definition: Admission TypedQueue::enqueue(TransportBatch& batch) | calls require, bool, empty, reset; guard require(bool(data_),"invalid_input_reader","closed typed input queue");auto& d=*data_;; returns Admission::accepted; Admission::full; growth make_accounted_unique; 2 loop sites; source comment (unverified): // Reconcile the preflight against actual retained requests before publication. · [reviewed contract](#b0040) |
| [B0041 · 250–251](../../../../../src/io/batch.cpp#L250) | Explanatory comments or spacing. | source comment (unverified): // Private restoration publishes its imported head before peek preparation. · [reviewed contract](#b0041) |
| [B0042 · 252–268](../../../../../src/io/batch.cpp#L252) | Callable definition: std::uint64_t TypedQueue::stage_replay(const InputItemView& input,const SourceStateLimits& limits) | calls checkpoint_detail::require, bool, checkpoint_detail::replay_input, catalog_source_detail::read; guard checkpoint_detail::require(bool(data_));auto& d=*data_;checkpoint_detail::require(!d.head && !d.cac…; returns budget.used; growth make_accounted_unique; source comment (unverified): // Private restoration publishes its imported head before peek preparation. · [reviewed contract](#b0042) |
| [B0043 · 269–269](../../../../../src/io/batch.cpp#L269) | Callable definition: void TypedQueue::finish() noexcept | calls  · [reviewed contract](#b0043) |
| [B0044 · 270–299](../../../../../src/io/batch.cpp#L270) | Callable definition: const InputItemView* TypedQueue::peek() | calls require, bool, catalog_source_detail::read, input_detail::validate; guard require(bool(data_),"invalid_input_reader","closed typed input queue");auto& d=*data_;; returns nullptr; &item; source comment (unverified): // Semantic errors are sticky; native MemoryFailure/bad_alloc bypasses this · [reviewed contract](#b0044) |
| [B0045 · 300–300](../../../../../src/io/batch.cpp#L300) | Explanatory comments or spacing. | source comment (unverified): // Publish prepared source acceptance, then retire exactly one counted head. · [reviewed contract](#b0045) |
| [B0046 · 301–314](../../../../../src/io/batch.cpp#L301) | Callable definition: void TypedQueue::acknowledge() noexcept | calls position_of, publish, sequence_of, std::move; source comment (unverified): // Publish prepared source acceptance, then retire exactly one counted head. · [reviewed contract](#b0046) |
| [B0047 · 315–317](../../../../../src/io/batch.cpp#L315) | Callable definition: const AccountedInputProgress& TypedQueue::progress() const | calls require, bool; guard require(bool(data_),"invalid_input_reader","closed typed input queue");return data_-&gt;accepted;; returns data_-&gt;accepted · [reviewed contract](#b0047) |
| [B0048 · 318–318](../../../../../src/io/batch.cpp#L318) | Callable definition: bool TypedQueue::failed() const noexcept | calls ; returns data_ && data_-&gt;stats.failed · [reviewed contract](#b0048) |
| [B0049 · 319–319](../../../../../src/io/batch.cpp#L319) | Callable definition: bool TypedQueue::closed() const noexcept | calls ; returns !data_ \|\| data_-&gt;stats.closed · [reviewed contract](#b0049) |
| [B0050 · 320–320](../../../../../src/io/batch.cpp#L320) | Callable definition: bool TypedQueue::empty() const noexcept | calls ; returns !data_ \|\| !data_-&gt;head · [reviewed contract](#b0050) |
| [B0051 · 321–321](../../../../../src/io/batch.cpp#L321) | Callable definition: QueueStats TypedQueue::stats() const noexcept | calls ; returns data_?data_-&gt;stats:QueueStats{0,0,0,true,false} · [reviewed contract](#b0051) |
| [B0052 · 322–326](../../../../../src/io/batch.cpp#L322) | Callable definition: AccountedInputProgress TypedQueue::close() noexcept | calls static_assert, std::move, reset; guard static_assert(std::is_nothrow_move_constructible_v&lt;AccountedInputProgress&gt;);; returns {}; result · [reviewed contract](#b0052) |
| [B0053 · 327–327](../../../../../src/io/batch.cpp#L327) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0053) |

## B0001

[Lines 1–15](../../../../../src/io/batch.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:a75f2ff6b09571a4a249f00cf807131e13eb2d28e69a8ae0a6e3cf0844b8d5c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/batch.hpp, crown/api/error.hpp, crown/catalog/catalog.hpp, catalog_source.hpp, input_native.hpp, checkpoint_detail.hpp) and opens crown::io scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_specs/files/src/io/batch.cpp.md](batch.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0002

[Lines 16–18](../../../../../src/io/batch.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition,std::string_view code,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject one explicit batch/queue predicate with its public category. |
| inputs / outputs | True returns; false constructs Error from code/message. |
| invariants | No successful exception-driven control flow or hidden rollback; diagnostic strings can allocate only on failure. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Throws supplied Error; bad_alloc during diagnostic construction remains an allocation failure. |
| cost | Fixed successful branch; failure-only string/error construction. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0003

[Lines 19–22](../../../../../src/io/batch.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t add(std::size_t a,std::size_t b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add typed input footprint sizes without size_t overflow. |
| inputs / outputs | Two nonnegative sizes yield exact sum after subtraction-based admission. |
| invariants | resource_limit precedes wrapped arithmetic; queue/transport caps remain separate callers. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed arithmetic/branch, no successful allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0004

[Lines 23–26](../../../../../src/io/batch.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t slots(std::size_t n,std::size_t width)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a nonzero-width capacity product safely. |
| inputs / outputs | n slots and positive byte width yield n*width after overflow admission. |
| invariants | Private callers pass sizeof(Value)&gt;0; this is a DTO capacity model, not actual upstream requested bytes. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed division/comparison/multiply, no successful allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0005

[Lines 27–34](../../../../../src/io/batch.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t row_bytes(const Row& row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Estimate the offered ordinary Row capacity footprint. |
| inputs / outputs | Counts row.capacity()*sizeof(Value), string capacity+terminator and fixed 64-byte allowance per owning Decimal. |
| invariants | Includes spare Value/text capacity and can count small-string inline capacity conservatively; not exact native MemoryAccount allocation/peak memory or allocator metadata. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | O(live row width) plus constant-time capacity reads, no successful row copy or scalar formatting. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0006

[Lines 35–44](../../../../../src/io/batch.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t item_payload(const InputItem& item)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add the transport DTO payload model for one event/window command. |
| inputs / outputs | Physical row or WindowInsert row contributes row_bytes; optional source string adds capacity+terminator; metadata-only commands have no row. |
| invariants | Preserves every event barrier and source payload; command kind/domain validity remains head validation. Outer InputItem must not be valueless. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | O(row width) footprint scan, no successful allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0007

[Lines 45–48](../../../../../src/io/batch.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t sequence_of(const InputItemView& item) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an input-view external command sequence. |
| inputs / outputs | InputEventView returns update.sequence; WindowCommandView returns command sequence. |
| invariants | Variant is admitted/nonvalueless. Sequence is external command order, which can differ from derived physical window epochs. |
| ownership | Returns copied uint64, no borrowed payload escape. |
| failure | noexcept under valid InputItemView variant invariant. |
| cost | Fixed variant/field access. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0008

[Lines 49–52](../../../../../src/io/batch.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<SourcePositionView>& position_of(const InputItemView& item) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an input-view optional source position. |
| inputs / outputs | Returns const optional&lt;SourcePositionView&gt;& from event or command. |
| invariants | Position bytes remain backed by the owning queue/import input; no copy, validation or acknowledgement. |
| ownership | Reference borrows input view object and its retained source text. |
| failure | noexcept under valid InputItemView variant invariant. |
| cost | Fixed variant/field access. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0009

[Lines 53–54](../../../../../src/io/batch.cpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L54:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_specs/files/src/io/batch.cpp.md](batch.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0010

[Lines 55–59](../../../../../src/io/batch.cpp#L55); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TransportBatch::Data
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the external ordered transport batch DTO graph. |
| inputs / outputs | Data contains list of owning InputItem+modeled byte charge and descriptor baseline. |
| invariants | This ordinary transport graph is distinct from funded native queue ownership. Order and every event barrier are preserved; no cancellation, consolidation or atomic W06 semantics. |
| ownership | TransportBatch uniquely owns Data/list/payloads until accepted native import destroys the offered graph. |
| failure | List/payload preparation can fail before batch construction returns; RAII releases private DTO storage. |
| cost | Ordinary unique control/list nodes plus caller DTO values; bytes is a component estimate, not allocator totals. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0011

[Lines 60–60](../../../../../src/io/batch.cpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L60:sha256:3f527ff2fab711b18763e24cc579b3870af14a8f2e3ba83b87c48435b46a72c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Ordered transport preserves each event barrier; it is not a net transaction. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/batch.cpp lines 58-62; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_specs/files/src/io/batch.cpp.md](batch.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0012

[Lines 61–79](../../../../../src/io/batch.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TransportBatch::TransportBatch(std::vector<InputItem> items,BatchLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a bounded external ordered DTO batch before native admission. |
| inputs / outputs | By-value vector is checked for event count; nonempty Data descriptor and full footprint model are admitted before moving items into list nodes. |
| invariants | Empty input needs no Data. Preflight rejects valueless outer items/cap overflow before payload transfer. Constructor input/descriptor allocation and allocator framing are separate from modeled bytes. |
| ownership | Constructed batch owns each moved DTO item; caller by-value argument is already local and not a strong guarantee on the original caller expression. |
| failure | Count/descriptor/footprint/variant/allocation error returns no batch; private Data/input values unwind. |
| cost | Two O(events+row widths) footprint passes, ordinary Data/list nodes and owning value moves; constructor argument copies are caller-side. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0013

[Lines 80–82](../../../../../src/io/batch.cpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TransportBatch::~TransportBatch()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move or release the external transport graph without accepting events. |
| inputs / outputs | Default destructor releases Data/list; default moves transfer unique Data and assignment retires old destination graph. |
| invariants | Moved-from batch is empty by accessor convention. No source acknowledgement/runtime publication occurs; ordinary caller DTO cleanup stays outside native account. |
| ownership | Exactly one batch owns each Data graph after move; destruction releases ordinary values/list nodes. |
| failure | Default owned teardown/moves are nonthrowing; no catch or retry framework. |
| cost | Fixed unique-handle move plus destination/terminal graph cleanup proportional to items/payloads; no deep copy. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0014

[Lines 83–83](../../../../../src/io/batch.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TransportBatch::empty() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read TransportBatch emptiness. |
| inputs / outputs | Returns true when no Data or empty item list. |
| invariants | No source validation/consumption; modeled bytes are separate from native actual queue requests. |
| ownership | Returns copied scalar; batch ownership stays unchanged. |
| failure | noexcept, empty/moved-from is a valid query. |
| cost | Fixed handle/list metadata access, no allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0015

[Lines 84–84](../../../../../src/io/batch.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t TransportBatch::size() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read TransportBatch event count. |
| inputs / outputs | Returns list size or zero without Data. |
| invariants | No source validation/consumption; modeled bytes are separate from native actual queue requests. |
| ownership | Returns copied scalar; batch ownership stays unchanged. |
| failure | noexcept, empty/moved-from is a valid query. |
| cost | Fixed handle/list metadata access, no allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0016

[Lines 85–85](../../../../../src/io/batch.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t TransportBatch::accounted_bytes() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read TransportBatch modeled byte count. |
| inputs / outputs | Returns retained Data model total or zero without Data. |
| invariants | No source validation/consumption; modeled bytes are separate from native actual queue requests. |
| ownership | Returns copied scalar; batch ownership stays unchanged. |
| failure | noexcept, empty/moved-from is a valid query. |
| cost | Fixed handle/list metadata access, no allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0017

[Lines 86–94](../../../../../src/io/batch.cpp#L86); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TypedQueue::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own intrusive native queued item state rather than ordinary DTO rows. |
| inputs / outputs | Item retains next owner, compact AccountedRow/source text, rebased InputItemView, deferred RowIssue and exact retained request charge. |
| invariants | Views must point to owned native row/source before external batch is released. Permanently malformed rows retain only issue metadata and original arity/field, preserving head diagnostic precedence without unusable values. |
| ownership | Queue Data/Batch uniquely own Item chain under original account; no ordinary retained InputItem mirror. |
| failure | Private construction failures release funded partial row/text/item before graph publication. |
| cost | One funded Item/control and optional compact row/source requests per item; next is an owning link, views/tail pointers are borrowed. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp) |

## B0018

[Lines 95–99](../../../../../src/io/batch.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static const Row* row_of(const InputItem& input) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Locate a source DTO row only for row-bearing items. |
| inputs / outputs | Physical event returns update.values; WindowInsert returns values; withdrawal/watermark returns nullptr. |
| invariants | Outer InputItem is valid. Malformed inner command remains no-row and later becomes the preserved monostate view, not a guessed insertion. |
| ownership | Returned Row pointer borrows offered InputItem. |
| failure | noexcept under valid outer variant; no semantic validation here. |
| cost | Fixed variant checks, no successful allocation. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp) |

## B0019

[Lines 100–104](../../../../../src/io/batch.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static TableId table_of(const InputItem& input) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the physical table only for row-bearing DTO inputs. |
| inputs / outputs | Returns event or WindowInsert table; metadata-only command gives TableId0 sentinel. |
| invariants | Data.row_issue calls this only when row_of exists; metadata-only sentinel is not validated as an actual target. |
| ownership | Returns copied ID. |
| failure | noexcept under outer variant invariant. |
| cost | Fixed variant/field access. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp) |

## B0020

[Lines 105–108](../../../../../src/io/batch.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static InputItemView borrow(const InputItem& input) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an external item without copying its row/source. |
| inputs / outputs | Dispatches InputEventView::borrow or WindowCommandView::borrow. |
| invariants | Malformed inner command becomes monostate for later validation; borrowed DTO fields are frozen/rebased during Item construction before caller batch destruction. |
| ownership | Temporary view borrows original DTO row/source until native copy completes. |
| failure | noexcept; relies on valid outer InputItem variant enforced by TransportBatch. |
| cost | Fixed variant/descriptor construction, no payload allocation. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp) |

## B0021

[Lines 109–112](../../../../../src/io/batch.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static std::size_t request(std::uint64_t bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert native requested-byte totals to size_t safely. |
| inputs / outputs | uint64 byte charge must fit size_t before returning exact value. |
| invariants | No truncating native graph preflight or quota arithmetic; this is not a memory-account allocation. |
| ownership | Returns scalar only. |
| failure | resource_limit on unrepresentable platform size. |
| cost | Fixed bound/conversion. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0022

[Lines 113–121](../../../../../src/io/batch.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static std::size_t owned_bytes(const InputItem& input,input_detail::RowIssue issue)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight exact native retained Item/row/source requests. |
| inputs / outputs | Adds account-framed Item allocation, compact row request if RowIssue none, and source text request if present. |
| invariants | Uses same AccountedRow/Text sizing as import. Invalid row payload is deliberately not copied/charged; deferred issue still retains original diagnostic metadata. |
| ownership | Reads offered DTO/issue only; allocates no queue node or shadow capacity ticket. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | O(row width/text length sizing) with checked requested-byte sums, no successful allocation. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp) |

## B0023

[Lines 122–133](../../../../../src/io/batch.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Item(const resource::MemoryAccount& account,const InputItemView& input):value(input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import a previously validated replay view into one owning native item. |
| inputs / outputs | Copies physical/window-insert row and optional source under account, computes actual framed requests, then rebases every view. |
| invariants | Replay caller already validated domains; issue records original arity and none. No view may remain tied to borrowed journal/body scratch. |
| ownership | Item owns compact payload/source; copied view descriptor points to that native backing. |
| failure | Allocation/contract failures unwind this private imported item before its queue publication. |
| cost | O(row width+string/source bytes), funded compact row/source allocations plus enclosing Item control. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0024

[Lines 134–135](../../../../../src/io/batch.cpp#L134); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L134-L135:sha256:dc0f539cf05ac0301a10b222c4f9a46c3c64b8a231fb3af2774b56347f90ba6f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Keep a permanent malformed-row issue instead of freezing unusable values. The original envelope/column-limit/head diagnostic order is checked at peek. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/batch.cpp lines 132-137; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_specs/files/src/io/batch.cpp.md](batch.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0025

[Lines 136–150](../../../../../src/io/batch.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Item(const resource::MemoryAccount& account,const InputItem& input,input_detail::RowIssue problem) :value(borrow(input)),issue(problem),bytes(owned_bytes(input,problem))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import an offered DTO while deferring permanent malformed-row rejection. |
| inputs / outputs | Retains borrowed descriptor+RowIssue, copies only valid row and optional source, then rebases views even when malformed row becomes empty backing. |
| invariants | Original issue.arity/field/type category preserve envelope/column-limit/head validation order. Semantic rejection happens only at head after earlier inputs commit; no later caller Row mutation can alter queued state. |
| ownership | Owns final native backing and issue metadata; external DTO can be destroyed after complete import. |
| failure | Resource/allocation errors release private preparation; no partial queued item exposed. |
| cost | O(valid row/source bytes and sizing), funded Item/row/source requests; invalid row skips impossible freeze. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp) |

## B0026

[Lines 151–151](../../../../../src/io/batch.cpp#L151); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L151-L151:sha256:42a2cb25a122b44221a6234ec660a7b5fb7f9bde7b3b9e2b3c559a0d96fac739
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_specs/files/src/io/batch.cpp.md](batch.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0027

[Lines 152–162](../../../../../src/io/batch.cpp#L152); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Batch
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one native batch and tear its item chain down iteratively. |
| inputs / outputs | Batch holds next batch owner, head/tail and retained byte total; destructor detaches each Item.next before release. |
| invariants | Tail is borrowed from head chain. Iterative detachment bounds teardown stack depth during success/failure rather than recursively destroying a long offered batch. |
| ownership | Batch uniquely owns its Item chain and next batch link until Data detaches that link. |
| failure | noexcept teardown relies on native owner nonthrowing destruction; no new handler. |
| cost | One funded batch/control plus O(items/payload release) teardown, constant traversal stack. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0028

[Lines 163–173](../../../../../src/io/batch.cpp#L163); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  resource::MemoryAccount account;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain native queue authority, limits, accepted progress and admission state. |
| inputs / outputs | Data stores original account/catalog, mode/queue/input limits, intrusive batch owners/tail, native progress/prepared source node, counts and cached-head flag. |
| invariants | QueueStats tracks retained native graph including current head; fixed queue/catalog/progress and prepared source publication are additional original-account requests. Mutating calls require existing caller serialization. |
| ownership | Data owns batch/progress/prepared graph; tail borrows the owned final batch and catalog retains actual authority. |
| failure | Construction/import/peek own failure phases separately; no implicit source acceptance from retaining this state. |
| cost | Fixed funded queue/control plus bounded batches/items/progress; source directory uses ordered map, not an ordinary DTO mirror. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0029

[Lines 174–179](../../../../../src/io/batch.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Data(const resource::MemoryAccount& memory,CatalogSource schema,QueueMode kind,QueueLimits cap,InputLimits input_cap,bool admitted)
      :account(memory),catalog(std::move(schema)),mode(kind),limits(cap),input_limits(input_cap),accepted(account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit native queue mode/limits and establish accepted progress ownership. |
| inputs / outputs | Retains account/catalog/configuration, constructs native accepted directory, optionally validates standalone catalog. |
| invariants | Only physical/window modes; wire total_bytes rejected for typed queue. Executable constructor elsewhere derives original program grant and skips redundant admitted-catalog validation. |
| ownership | Account/catalog retained by Data; standalone Catalog value may remain ordinary compiler metadata. |
| failure | Invalid mode/wire limit/catalog/account/allocation errors abort construction before queue publication. |
| cost | Funded progress/control setup plus optional full catalog validation; no item import or source acknowledgement. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0030

[Lines 180–180](../../../../../src/io/batch.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy the batch directory with bounded stack use. |
| inputs / outputs | Repeatedly moves Data.head to a local and detaches batch.next before that batch dies. |
| invariants | Batch destructor separately detaches Item links; no recursive full-queue chain destruction or accepted-source advancement. |
| ownership | Releases all unique batch/item owners while Data still retains its account/progress authority. |
| failure | noexcept; no allocation or handler introduced. |
| cost | O(batches+items/payload release), constant link traversal stack; deallocation/account cleanup retains real cost. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0031

[Lines 181–185](../../../../../src/io/batch.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
input_detail::RowIssue row_issue(const InputItem& input) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect and retain the first permanent row issue without freezing bad payload. |
| inputs / outputs | Row-bearing offered item is checked via actual catalog/input_detail::row_issue; metadata command returns default issue. |
| invariants | Issue is descriptive deferred validation, not acceptance. Envelope/sequence/column-limit/source errors still follow head validation order. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | O(row width and decimal-domain checks), no successful row/string formatting allocation. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp) |

## B0032

[Lines 186–186](../../../../../src/io/batch.cpp#L186); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L186-L186:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_specs/files/src/io/batch.cpp.md](batch.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0033

[Lines 187–189](../../../../../src/io/batch.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TypedQueue::TypedQueue(CatalogSource catalog,QueueMode mode,QueueLimits limits,InputLimits input_limits)
    :TypedQueue(resource::MemoryAccount::create(std::numeric_limits<std::uint64_t>::max()),
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an explicit standalone typed adapter queue. |
| inputs / outputs | Delegates CatalogSource/mode/limits through a newly explicit maximum-limit component account. |
| invariants | External/compiler boundary; execution CompiledProgram overload shares its original finite account and catalog owner instead. No nested execution refill. |
| ownership | Queue owns native graph; supplied ordinary Catalog value/alias transfer is its own metadata boundary. |
| failure | Constructor errors unwind private state before public queue return. |
| cost | Account/controller and native queue/progress construction plus standalone catalog validation. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0034

[Lines 190–193](../../../../../src/io/batch.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TypedQueue::TypedQueue(const resource::MemoryAccount& account,CatalogSource catalog,QueueMode mode,
    QueueLimits limits,InputLimits input_limits,bool admitted)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund the stable queue control in a supplied receiving account. |
| inputs / outputs | make_accounted_unique&lt;Data&gt; uses session:2/support_metadata and retained catalog/configuration. |
| invariants | Private caller establishes admitted catalog/account authority; this wrapper does not create a replacement grant. |
| ownership | TypedQueue uniquely owns Data and its native graph. |
| failure | Factory cleanup releases partial raw/control state if Data construction fails. |
| cost | One funded control plus Data/progress construction. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0035

[Lines 194–194](../../../../../src/io/batch.cpp#L194); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TypedQueue::~TypedQueue()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release native queue state without accepting unread items. |
| inputs / outputs | Default unique Data destruction invokes iterative batch/item cleanup and releases native progress/prepared/source owners. |
| invariants | No engine update/source acknowledgement; retained progress snapshots or catalog/program aliases may outlive this facade. |
| ownership | Drops this unique queue owner; independent retained account/program values remain their own owners. |
| failure | Nonthrowing RAII teardown; no extra catch. |
| cost | Cleanup proportional to queue/progress graph and account releases, no deep copy. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0036

[Lines 195–205](../../../../../src/io/batch.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TypedQueue::TypedQueue(const resource::MemoryAccount& account,CatalogSource catalog,const QueueCheckpoint& state,const SourceStateLimits& limits,bool admitted)
    :data_([&] {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore an empty native queue continuation from admitted checkpoint metadata. |
| inputs / outputs | Budgets source positions, validates progress/record/source counts, constructs actual mode/limits/catalog, verifies fingerprint and copies accepted progress/closed state. |
| invariants | No queued tail/cache is imported; checkpoint is accepted source boundary, not a durable authority by itself. Catalog binding must match supplied admitted program. |
| ownership | New Data owns copied native progress under receiver; checkpoint is borrowed during construction. |
| failure | Image/option/catalog/binding/work/account/allocation failures destroy private result before public queue. |
| cost | O(source names + full canonical catalog fingerprint) and funded native control/progress copies; selected SourceStateLimits differs from query memory cap. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0037

[Lines 206–206](../../../../../src/io/batch.cpp#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueueCheckpoint TypedQueue::checkpoint_state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture queue continuation under default SourceStateLimits. |
| inputs / outputs | Delegates checkpoint_state(SourceStateLimits{}). |
| invariants | Explicit bounded metadata capture; no pending item is silently accepted. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed forwarding plus native checkpoint cost. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0038

[Lines 207–213](../../../../../src/io/batch.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueueCheckpoint TypedQueue::checkpoint_state(const SourceStateLimits& limits) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture an owning accepted empty-queue continuation. |
| inputs / outputs | Requires Data with no head/cache/failure; charges positions, recomputes fingerprint and copies accepted progress plus mode/limits/closed metadata. |
| invariants | Queued/unaccepted tail cannot be checkpointed through this method. Hash is binding, not source/durable proof; output is native owning continuation. |
| ownership | Returned QueueCheckpoint owns progress under original account and copied fixed options; queue unchanged. |
| failure | Boundary/image/work/account/allocation failure returns no partial checkpoint. |
| cost | O(source names + catalog canonical bytes), funded progress/fingerprint scratch and selected source work. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0039

[Lines 214–215](../../../../../src/io/batch.cpp#L214); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TypedQueue::TypedQueue(TypedQueue&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer queue graph ownership without moving backing payload addresses. |
| inputs / outputs | Default move constructor/assignment transfers unique Data; assignment first destroys old destination state. |
| invariants | Borrowed internal row/source/tail references remain backed by heap graph. Source facade becomes closed/empty by accessor convention. |
| ownership | Exactly one facade owns transferred Data after move; payload pointers remain heap-stable. |
| failure | noexcept, using nonthrowing owned teardown. |
| cost | Fixed handle move plus old destination teardown, no allocation/deep graph copy. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0040

[Lines 216–249](../../../../../src/io/batch.cpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Admission TypedQueue::enqueue(TransportBatch& batch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import a complete offered DTO batch atomically into native queue ownership. |
| inputs / outputs | Checks open/healthy/count caps, preflights exact batch/item/valid-row/source requests, prepares graph privately and reconciles actual requested-byte delta before linking/stats update and emptying caller batch. |
| invariants | Full rejection and any prepublication failure retain original offered batch/queue. Per-item RowIssue is deferred; ordered set-event/window barriers are not netted or committed together. Account is exclusive during actual-delta reconciliation. |
| ownership | Prepared unique graph becomes queue-owned through nonthrowing link moves; only then external batch Data/payloads are destroyed. |
| failure | Count/byte full returns Admission::full before import. Errors/OOM/actual-charge contract mismatch before link unwind prepared graph and leave caller/queue unchanged. Empty batch is accepted/released without EOF. |
| cost | Two row issue/sizing/import passes, O(events+valid row/source bytes), real funded graph allocation; no retained ordinary DTO copy or extra global ticket. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md), [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0041

[Lines 250–251](../../../../../src/io/batch.cpp#L250); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L250-L251:sha256:7e9b5fadc2170d09b4d80c763ad25a17f68b1b2446dfadeceb5b7a88f5466954
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Private restoration publishes its imported head before peek preparation. A later peek failure can retain that head; failed session restore discards it. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/batch.cpp lines 248-253; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_specs/files/src/io/batch.cpp.md](batch.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0042

[Lines 252–268](../../../../../src/io/batch.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t TypedQueue::stage_replay(const InputItemView& input,const SourceStateLimits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage one replay command into a private restoration queue. |
| inputs / outputs | Requires healthy open empty queue, mode match and budgeted full validation; funds one Batch/Item, checks byte cap, publishes head/stats, then invokes ordinary peek order/source preparation. |
| invariants | Does not acknowledge source. Unlike live enqueue strong guarantee, this private function publishes its imported head before peek: subsequent source allocation/semantic failure can leave that unexposed queue populated. Session restore owns discard on failure. |
| ownership | Private queue owns copied/rebased journal views before peek; public restore returns it only after complete session reconstruction. |
| failure | Before head publication validation/import/quota failure leaves empty queue. Later peek Error latches failed; bad_alloc remains retryable through peek with retained head. Accepted progress remains old; no claim of unchanged private queue on every failure. |
| cost | Conservative source-work validation plus funded Batch/Item/row/source and possible prepared source node; one head only, no wire decode or engine maintenance. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0043

[Lines 269–269](../../../../../src/io/batch.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void TypedQueue::finish() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close typed admission while retaining consumable queued prefix. |
| inputs / outputs | Sets stats.closed if Data exists. |
| invariants | No EOF fabrication while head remains; later enqueues reject, existing peek/ack still work. Closed/empty source meaning is decided by session. |
| ownership | Retains all queue owners and accepted progress. |
| failure | noexcept, empty/moved-from is a no-op. |
| cost | Fixed Boolean assignment, no allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0044

[Lines 270–299](../../../../../src/io/batch.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const InputItemView* TypedQueue::peek()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and cache only the current owned typed input head. |
| inputs / outputs | Checks mode, deferred row/envelope/domain caps, contiguous command sequence/record cap and strictly increasing per-source offset; prepares source-map publication and returns stable view. |
| invariants | Tail errors stay deferred. Only Error semantic/resource-limit diagnostics become sticky; MemoryFailure/std::bad_alloc are not caught and preserve retryable same head. Engine rejection occurs after returned view and also preserves it. |
| ownership | View borrows queue-owned compact row/source until acknowledge/close/destruction; prepared source node remains private. |
| failure | Keep the narrow catch(Error&): latch semantic bad head then rethrow original category. Allocation faults bypass it, release temporary preparation and do not mark queue failed or accept source. |
| cost | Full head scalar/source validation plus ordered source directory comparisons/prepared-node allocation; cached repeat is fixed. No wire record encoding or native engine work charge. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp) |

## B0045

[Lines 300–300](../../../../../src/io/batch.cpp#L300); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L300-L300:sha256:dcb2aaf99d434c55e59814138f8b9584385caf94c2cac7c2197b2c64988e76d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Publish prepared source acceptance, then retire exactly one counted head. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/batch.cpp lines 298-302; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_specs/files/src/io/batch.cpp.md](batch.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0046

[Lines 301–314](../../../../../src/io/batch.cpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void TypedQueue::acknowledge() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acknowledge exactly the already cached typed command after engine/window publication. |
| inputs / outputs | Publishes prepared source offset and accepted sequence, removes charged Item, retires empty Batch and updates counts/tail. |
| invariants | Head remains counted through pending/window expansion until this call. No read, validation, consolidation or engine application; empty/uncached queue is no-op. |
| ownership | Accepted directory adopts prepared node; retiring item invalidates its borrowed view and releases owned row/source. |
| failure | noexcept under cached head/count/node invariants; no catch or rollback layer. |
| cost | Prepared ordered-map link/scalar publication plus Item/possibly Batch/account cleanup; nonallocating/noexcept but not a constant-time all-cleanup claim. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md), [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp) |

## B0047

[Lines 315–317](../../../../../src/io/batch.cpp#L315); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedInputProgress& TypedQueue::progress() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow accepted native queue progress. |
| inputs / outputs | Returns const AccountedInputProgress& from valid Data. |
| invariants | Queued/cached commands are not included until acknowledgement. A snapshot copy is a separate funded value operation. |
| ownership | Borrowed reference requires live queue Data and observes later acknowledgement updates. |
| failure | Closed/moved-from queue throws invalid_input_reader. |
| cost | Fixed owner/field access. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0048

[Lines 318–318](../../../../../src/io/batch.cpp#L318); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TypedQueue::failed() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect typed queue failure flag. |
| inputs / outputs | Returns true only for existing Data with sticky head error. |
| invariants | Does not peek, validate or consume head; closure, emptiness and failure remain distinct. |
| ownership | Copied Boolean/stats only. |
| failure | noexcept with documented empty/moved-from defaults. |
| cost | Fixed pointer/scalar reads, no allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0049

[Lines 319–319](../../../../../src/io/batch.cpp#L319); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TypedQueue::closed() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect typed queue admission closure. |
| inputs / outputs | Returns true without Data or after finish. |
| invariants | Does not peek, validate or consume head; closure, emptiness and failure remain distinct. |
| ownership | Copied Boolean/stats only. |
| failure | noexcept with documented empty/moved-from defaults. |
| cost | Fixed pointer/scalar reads, no allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0050

[Lines 320–320](../../../../../src/io/batch.cpp#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool TypedQueue::empty() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect typed queue queued emptiness. |
| inputs / outputs | Returns true without Data or without head. |
| invariants | Does not peek, validate or consume head; closure, emptiness and failure remain distinct. |
| ownership | Copied Boolean/stats only. |
| failure | noexcept with documented empty/moved-from defaults. |
| cost | Fixed pointer/scalar reads, no allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0051

[Lines 321–321](../../../../../src/io/batch.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueueStats TypedQueue::stats() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect typed queue occupancy. |
| inputs / outputs | Returns copied QueueStats, or closed/empty/nonfailed default when Data absent. |
| invariants | Does not peek, validate or consume head; closure, emptiness and failure remain distinct. |
| ownership | Copied Boolean/stats only. |
| failure | noexcept with documented empty/moved-from defaults. |
| cost | Fixed pointer/scalar reads, no allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0052

[Lines 322–326](../../../../../src/io/batch.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputProgress TypedQueue::close() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close typed source without accepting unread commands and retain accepted progress. |
| inputs / outputs | Moves native accepted progress out, then releases unique Data/queued graph; empty queue returns default progress. |
| invariants | Cached/prepared and tail input is discarded without acknowledgement; external runtime/engine state is untouched. No ordinary map/string DTO export or replacement account. |
| ownership | Returned AccountedInputProgress owns original-account directory independently of queue/runtime lifetime. |
| failure | noexcept, statically requires nonthrowing progress move; repeated close is empty. |
| cost | Noexcept progress move plus iterative queue/progress cleanup; no allocation, with real deallocation/account costs. |
| Design | [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/memory_accounts.md §Native typed input and accepted progress](../../../../memory_accounts.md) |

## B0053

[Lines 327–327](../../../../../src/io/batch.cpp#L327); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L327-L327:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_specs/files/src/io/batch.cpp.md](batch.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
