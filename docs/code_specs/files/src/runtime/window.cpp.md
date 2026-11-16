# `src/runtime/window.cpp` — block usage map

[Source](../../../../../src/runtime/window.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain operational event-time/FIFO membership and prepared expiration transitions.

Snapshot SHA-256: `3c51bb8a799367173879957df00b3b6ada5495b31367fc0e70b4ae1b5153d7b4`. 554 lines partitioned into 52 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [window](../../../subsystem_contracts.md#window). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/batches_windows.md](../../../../batches_windows.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../src/runtime/window.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 20–22](../../../../../src/runtime/window.cpp#L20) | Callable definition: void require(bool yes,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool yes,std::string_view code,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 23–26](../../../../../src/runtime/window.cpp#L23) | Callable definition: std::size_t add(std::size_t a,std::size_t b) | calls require, max; guard require(b&lt;=std::numeric_limits&lt;std::size_t&gt;::max()-a,"resource_limit","window byte accounting overf…; returns a+b · [reviewed contract](#b0003) |
| [B0004 · 27–30](../../../../../src/runtime/window.cpp#L27) | Callable definition: std::size_t multiply(std::size_t a,std::size_t b) | calls require, max; guard require(!b \|\| a&lt;=std::numeric_limits&lt;std::size_t&gt;::max()/b,"resource_limit","window byte accounting…; returns a*b · [reviewed contract](#b0004) |
| [B0005 · 31–36](../../../../../src/runtime/window.cpp#L31) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Session controls remain session:0; nested window ownership is session:1. · [reviewed contract](#b0005) |
| [B0006 · 37–45](../../../../../src/runtime/window.cpp#L37) | Type/record definition: struct NativeActiveCommand |  · [reviewed contract](#b0006) |
| [B0007 · 46–48](../../../../../src/runtime/window.cpp#L46) | Callable definition: std::size_t label_bytes(const NativeLabel& label) | calls add, stored_payload_bytes; returns add(sizeof(NativeLabel)+sizeof(std::pair&lt;std::uint64_t,std::uint64_t&gt;)+2*sizeof(std::uint64_t),labe… · [reviewed contract](#b0007) |
| [B0008 · 49–49](../../../../../src/runtime/window.cpp#L49) | Callable definition: std::size_t count_bytes(const NativeCount& count) | calls add, stored_payload_bytes; returns add(sizeof(NativeCount),count.values.stored_payload_bytes()) · [reviewed contract](#b0008) |
| [B0009 · 50–50](../../../../../src/runtime/window.cpp#L50) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 51–58](../../../../../src/runtime/window.cpp#L51) | Type/record definition: struct WindowTables::Data | growth insert, reserve · [reviewed contract](#b0010) |
| [B0011 · 59–61](../../../../../src/runtime/window.cpp#L59) | Callable definition: WindowTables WindowTables::copy_of(const resource::MemoryAccount& account,const std::vector&lt;TableId&gt;& source) | calls copy_of, capacity; returns copy_of(account,std::span&lt;const TableId&gt;(source),source.capacity()); growth copy_of · [reviewed contract](#b0011) |
| [B0012 · 62–66](../../../../../src/runtime/window.cpp#L62) | Callable definition: WindowTables WindowTables::copy_of(const resource::MemoryAccount& account,std::span&lt;const TableId&gt; source,std::size_t capacity) | calls empty, WindowTables; returns {}; WindowTables(resource::make_accounted_shared&lt;Data&gt;(window_memory,account,; growth copy_of, make_accounted_shared · [reviewed contract](#b0012) |
| [B0013 · 67–67](../../../../../src/runtime/window.cpp#L67) | Callable definition: std::size_t WindowTables::size() const noexcept | calls size; returns data_?data_-&gt;values.size():0 · [reviewed contract](#b0013) |
| [B0014 · 68–68](../../../../../src/runtime/window.cpp#L68) | Callable definition: std::size_t WindowTables::capacity() const noexcept | calls capacity; returns data_?data_-&gt;values.capacity():0 · [reviewed contract](#b0014) |
| [B0015 · 69–69](../../../../../src/runtime/window.cpp#L69) | Callable definition: const TableId* WindowTables::data() const noexcept | calls data; returns data_?data_-&gt;values.data():nullptr · [reviewed contract](#b0015) |
| [B0016 · 70–72](../../../../../src/runtime/window.cpp#L70) | Callable definition: AccountedWindowOptions::AccountedWindowOptions(const resource::MemoryAccount& account,const WindowOptions& source) :managed_table… | calls managed_tables, WindowTables::copy_of, width, fifo; growth copy_of · [reviewed contract](#b0016) |
| [B0017 · 73–76](../../../../../src/runtime/window.cpp#L73) | Callable definition: AccountedWindowOptions::AccountedWindowOptions(const resource::MemoryAccount& account,const AccountedWindowOptions& source) :mana… | calls managed_tables, WindowTables::copy_of, data, size; growth copy_of · [reviewed contract](#b0017) |
| [B0018 · 77–90](../../../../../src/runtime/window.cpp#L77) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 91–112](../../../../../src/runtime/window.cpp#L91) | Callable definition: template&lt;class CatalogView,class Options&gt; Impl(const resource::MemoryAccount& memory,const CatalogView& catalog,const Options& va… | calls account, options, catalog_sha256, io::input_detail::catalog_digest; guard require(options.width&gt;0 && options.max_labels&gt;0 && options.max_accounted_bytes&gt;0 && options.command…; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 113–117](../../../../../src/runtime/window.cpp#L113) | Explanatory comments or spacing. | source comment (unverified): // Opt-in combined preflight: one integer vector, no retained row/index copy. · [reviewed contract](#b0020) |
| [B0021 · 118–172](../../../../../src/runtime/window.cpp#L118) | Callable definition: template&lt;class Charge&gt; std::size_t preflight_patterns(std::uint64_t mark, const patterns::Declaration& declaration, std::uint64_t… | calls empty, begin, remaining, charge; guard pattern_detail::require(!rule \|\| !rule-&gt;insertion_only, PatternViolationKind::physical_erase,; returns 0; {0, TableId{0}}; growth push_back, reserve; 2 loop sites; source comment (unverified): // Opt-in combined preflight: one integer vector, no retained row/index copy. · [reviewed contract](#b0021) |
| [B0022 · 173–208](../../../../../src/runtime/window.cpp#L173) | Callable definition: template&lt;class Charge&gt; std::size_t preflight_lifetimes(std::uint64_t mark,Charge& charge) const | calls empty, begin, remaining, charge; guard require(previous-&gt;key.first!=key.first \|\| previous-&gt;remaining==0,; returns 0; a.key&lt;b.key; growth push_back, reserve; 2 loop sites; source comment (unverified): // One transient counter vector on the original account; native rows and · [reviewed contract](#b0022) |
| [B0023 · 209–209](../../../../../src/runtime/window.cpp#L209) | Closes surrounding scope/type. |  · [reviewed contract](#b0023) |
| [B0024 · 210–224](../../../../../src/runtime/window.cpp#L210) | Type/record definition: struct WindowController::Prepared::Data |  · [reviewed contract](#b0024) |
| [B0025 · 225–225](../../../../../src/runtime/window.cpp#L225) | Callable definition: WindowController::Prepared::Prepared(resource::AccountedUnique&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0025) |
| [B0026 · 226–228](../../../../../src/runtime/window.cpp#L226) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0026) |
| [B0027 · 229–229](../../../../../src/runtime/window.cpp#L229) | Callable definition: const std::optional&lt;PhysicalUpdateView&gt;& WindowController::Prepared::update() const noexcept | calls ; returns data_-&gt;update · [reviewed contract](#b0027) |
| [B0028 · 230–230](../../../../../src/runtime/window.cpp#L230) | Callable definition: bool WindowController::Prepared::completes_command() const noexcept | calls ; returns data_-&gt;complete · [reviewed contract](#b0028) |
| [B0029 · 231–261](../../../../../src/runtime/window.cpp#L231) | Callable definition: void WindowController::Prepared::publish() noexcept | calls mapped, insert, std::move, find; growth insert; source comment (unverified): // Caller has committed the native step or metadata barrier. Funded integer · [reviewed contract](#b0029) |
| [B0030 · 262–269](../../../../../src/runtime/window.cpp#L262) | Callable definition: WindowController::WindowController(Catalog catalog,WindowOptions options) :data_(\[&\] { // Standalone adapter admission has its ow… | calls data_, resource::MemoryAccount::create, max; returns resource::make_accounted_shared&lt;Impl&gt;({resource::MemoryOwnerKind::session,0},account,; growth make_accounted_shared; source comment (unverified): // Standalone adapter admission has its own finite account. Query sessions · [reviewed contract](#b0030) |
| [B0031 · 270–272](../../../../../src/runtime/window.cpp#L270) | Callable definition: WindowController::WindowController(const resource::MemoryAccount& account,const program::Catalog& catalog,const WindowOptions& op… | calls data_; growth make_accounted_shared · [reviewed contract](#b0031) |
| [B0032 · 273–273](../../../../../src/runtime/window.cpp#L273) | declares namespace scope. |  · [reviewed contract](#b0032) |
| [B0033 · 274–276](../../../../../src/runtime/window.cpp#L274) | Callable definition: void state_require(bool condition,recovery::ImageFault fault=recovery::ImageFault::corrupt) | calls recovery::ImageFailure · [reviewed contract](#b0033) |
| [B0034 · 277–284](../../../../../src/runtime/window.cpp#L277) | Type/record definition: struct StateBudget |  · [reviewed contract](#b0034) |
| [B0035 · 285–285](../../../../../src/runtime/window.cpp#L285) | Type/record definition: struct StateKey |  · [reviewed contract](#b0035) |
| [B0036 · 286–292](../../../../../src/runtime/window.cpp#L286) | Type/record definition: struct StateKeyLess | returns a.table&lt;b.table; a.values&lt;b.values · [reviewed contract](#b0036) |
| [B0037 · 293–293](../../../../../src/runtime/window.cpp#L293) | Closes surrounding scope/type. |  · [reviewed contract](#b0037) |
| [B0038 · 294–308](../../../../../src/runtime/window.cpp#L294) | Callable definition: WindowCheckpoint WindowController::checkpoint_state(WindowStateLimits limits) const | calls state_require, size, charge, row; returns result; growth clone, push_back, reserve; 4 loop sites; source comment (unverified): // Own cloned native rows on this account. A partial watermark, including a · [reviewed contract](#b0038) |
| [B0039 · 309–356](../../../../../src/runtime/window.cpp#L309) | Callable definition: WindowController::WindowController(const resource::MemoryAccount& account,const program::Catalog& catalog, const WindowCheckpoint… | calls data_, state_require, size, capacity; returns result; growth clone, emplace, insert, make_accounted_shared; 3 loop sites; source comment (unverified): // Rebuild private indexes and exact count references before publishing a · [reviewed contract](#b0039) |
| [B0040 · 357–358](../../../../../src/runtime/window.cpp#L357) | controls preprocessing; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0040) |
| [B0041 · 359–362](../../../../../src/runtime/window.cpp#L359) | Callable definition: void RuntimeTestProbe::seed_window_sequence(WindowController& runtime,std::uint64_t sequence) | calls require; guard require(!runtime.data_-&gt;prepared && !runtime.data_-&gt;stopped,"invalid_probe","window sequence probe … · [reviewed contract](#b0041) |
| [B0042 · 363–363](../../../../../src/runtime/window.cpp#L363) | controls preprocessing. |  · [reviewed contract](#b0042) |
| [B0043 · 364–364](../../../../../src/runtime/window.cpp#L364) | Callable definition: const AccountedWindowOptions& WindowController::options() const noexcept | calls ; returns data_-&gt;options · [reviewed contract](#b0043) |
| [B0044 · 365–367](../../../../../src/runtime/window.cpp#L365) | Callable definition: WindowMetrics WindowController::metrics() const noexcept | calls size; returns {data_-&gt;labels.size(),data_-&gt;counts.size(),data_-&gt;bytes,data_-&gt;work} · [reviewed contract](#b0044) |
| [B0045 · 368–373](../../../../../src/runtime/window.cpp#L368) | Callable definition: WindowProgress WindowController::progress() const noexcept | calls ; returns p · [reviewed contract](#b0045) |
| [B0046 · 374–380](../../../../../src/runtime/window.cpp#L374) | Callable definition: void WindowController::stop() noexcept | calls capacity, get_allocator, swap · [reviewed contract](#b0046) |
| [B0047 · 381–396](../../../../../src/runtime/window.cpp#L381) | Callable definition: WindowCanonicalState WindowController::canonical_state() const | calls push_back, storage::export_row, view, assign; returns s; growth push_back; 3 loop sites; source comment (unverified): // Explicit external diagnostic: full ordinary Row/vector copies are outside · [reviewed contract](#b0047) |
| [B0048 · 397–399](../../../../../src/runtime/window.cpp#L397) | Callable definition: WindowController::Prepared WindowController::prepare(const io::WindowCommand& command,std::uint64_t next_physical_sequence) | calls prepare_view, io::WindowCommandView::borrow; returns prepare_view(io::WindowCommandView::borrow(command),next_physical_sequence) · [reviewed contract](#b0048) |
| [B0049 · 400–400](../../../../../src/runtime/window.cpp#L400) | Callable definition: bool WindowController::manages(TableId table) const noexcept | calls contains; returns data_-&gt;relations.contains(table) · [reviewed contract](#b0049) |
| [B0050 · 401–403](../../../../../src/runtime/window.cpp#L401) | Callable definition: WindowController::Prepared WindowController::prepare_view(const io::WindowCommandView& command,std::uint64_t next_physical_sequen… | calls prepare_pattern_view; returns prepare_pattern_view(command,next_physical_sequence,nullptr,nullptr) · [reviewed contract](#b0050) |
| [B0051 · 404–553](../../../../../src/runtime/window.cpp#L404) | Callable definition: WindowController::Prepared WindowController::prepare_pattern_view(const io::WindowCommandView& command, std::uint64_t next_physic… | calls require, max, storage::AccountedRow::copy_of, emplace; guard require(!d.stopped,"invalid_window_command","window controller is stopped");; returns Prepared(std::move(p)); growth copy_of, emplace, insert, make_accounted_unique, push_back, reserve; 6 loop sites; source comment (unverified): // Only distinct-row presence changes produce physical set epochs. Every · [reviewed contract](#b0051) |
| [B0052 · 554–554](../../../../../src/runtime/window.cpp#L554) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0052) |

## B0001

[Lines 1–19](../../../../../src/runtime/window.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/window.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble operational set-window control with native rows and account-funded indexes. |
| inputs / outputs | Window API, fixed Error boundary, compiled metadata, ownership/allocators, native validation and optional test probe are included. |
| invariants | This controller maps operational labels to physical set-presence changes; duplicate labels do not create SQL bag multiplicities or a physical-lifetime FIFO theorem. |
| ownership | Declarations create no runtime account/state. Operational containers below use the supplied original account. |
| failure | No runtime admission or handler introduced by includes/namespaces. |
| cost | No dynamic work for declarations. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 20–22](../../../../../src/runtime/window.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool yes,std::string_view code,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an invalid operational window precondition with its existing public Error. |
| inputs / outputs | Boolean, code and message return normally or construct Error from copied strings. |
| invariants | No retry, mutation repair or hidden status mapper here; owning preparation scopes provide rollback. |
| ownership | Borrows diagnostic views on success; Error owns diagnostic copies on failure. |
| failure | False condition throws Error; diagnostic allocation can itself fail. |
| cost | One branch on success; failure-only diagnostic copies/exception work. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0003

[Lines 23–26](../../../../../src/runtime/window.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t add(std::size_t a,std::size_t b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add window descriptor/payload accounting without host-size wrap. |
| inputs / outputs | Two size_t values return exact sum iff representable. |
| invariants | Declared retained-byte ledger is distinct from actual account requested allocations/framing. |
| ownership | Inline operands/result only. |
| failure | resource_limit Error before overflown sum; no state publication. |
| cost | Constant check/add. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0004

[Lines 27–30](../../../../../src/runtime/window.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t multiply(std::size_t a,std::size_t b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Multiply window capacity/element widths safely. |
| inputs / outputs | size_t dimensions return checked product, including zero. |
| invariants | Used before active-vector/options descriptor accounting; no saturation or approximate bytes. |
| ownership | Inline operands/result only. |
| failure | resource_limit on host-size product overflow. |
| cost | Constant zero/division check and multiply. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0005

[Lines 31–36](../../../../../src/runtime/window.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Session controls remain session:0; nested window ownership is session:1.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind local window ownership and integer-keyed native container types. |
| inputs / outputs | session/1 attribution, account-allocator WindowMap/WindowSet aliases and native checkpoint label/count aliases. |
| invariants | Facade/session controls use session/0 where their factories request it; nested rows/index/active storage use session/1. A constructor may attribute the nested Impl holder to session/1 on restore. |
| ownership | Aliases retain no account until instantiated; no ordinary Row/string graph is hidden here. |
| failure | No dynamic failure or handler in these declarations. |
| cost | Compile-time aliases/constant only. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0006

[Lines 37–45](../../../../../src/runtime/window.cpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NativeActiveCommand {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a preflighted multi-step watermark expiration continuation. |
| inputs / outputs | Account, command sequence and watermark initialize scalar progress and an account-funded expiration-label vector. |
| invariants | Labels follow validated (deadline,label) order; total/completed steps distinguish partial physical prefix from completed command/watermark. accounted_work carries the whole admitted command reservation. |
| ownership | Owns only numeric label IDs/capacity using original account support_metadata/session1; rows remain in live maps. |
| failure | Private vector reserve/growth occurs before first effect; construction failure leaves no live active command. |
| cost | Fixed object plus O(expiring labels) vector capacity; no clone of live row/count/index state. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0007

[Lines 46–48](../../../../../src/runtime/window.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t label_bytes(const NativeLabel& label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one label contribution to the declared retained-window payload ledger. |
| inputs / outputs | Native label returns fixed label/index-descriptor allowance plus its stored row payload bytes. |
| invariants | This max_accounted_bytes policy omits real tree links/control/framing and transient prepared rows; the actual account independently admits those. |
| ownership | Borrows label row metadata only, returns size_t. |
| failure | Checked add can resource-limit before publication. |
| cost | Fixed arithmetic/row payload-size lookup, no row-byte scan or allocation. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0008

[Lines 49–49](../../../../../src/runtime/window.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t count_bytes(const NativeCount& count) {return add(sizeof(NativeCount),count.values.stored_payload_bytes());}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one distinct-count contribution to the declared window ledger. |
| inputs / outputs | NativeCount returns sizeof count descriptor plus stored native row payload bytes. |
| invariants | Not a full node/upstream allocator/RSS measurement. |
| ownership | Borrows owned row metadata; no retained view. |
| failure | Checked add rejects host-size overflow. |
| cost | Constant size arithmetic. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0009

[Lines 50–50](../../../../../src/runtime/window.cpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L50:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/window.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/window.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/window.cpp\` at its lexical source position in src/runtime/window.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/window.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0010

[Lines 51–58](../../../../../src/runtime/window.cpp#L51); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowTables::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an immutable managed-table list with explicit admitted capacity. |
| inputs / outputs | Account, TableId span and requested capacity initialize an immutable-metadata vector; capacity must cover source size. |
| invariants | Only ID copies/capacity are retained. Valid table range/duplicates are checked later by Impl, not by this carrier. |
| ownership | Vector/control use supplied account session1; copies of public WindowTables share this Data. |
| failure | Bad capacity raises ImageFailure(corrupt); reserve/copy allocation failure unwinds private Data. |
| cost | O(source count) copy and capacity*sizeof(TableId) storage plus account framing; no catalog/row scan. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0011

[Lines 59–61](../../../../../src/runtime/window.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowTables WindowTables::copy_of(const resource::MemoryAccount& account,const std::vector<TableId>& source) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze an ordinary caller table vector into accounted options. |
| inputs / outputs | Receiver account and vector forward its data/size and actual capacity to span overload. |
| invariants | Reserved capacity is intentionally preserved for admitted memory policy rather than silently shrinking. |
| ownership | Caller retains input vector; returned nonempty WindowTables owns a separate original-account copy. |
| failure | Delegates capacity/account/allocation errors; caller vector unchanged. |
| cost | Constant forwarding plus O(size) copy/capacity allocation below. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0012

[Lines 62–66](../../../../../src/runtime/window.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowTables WindowTables::copy_of(const resource::MemoryAccount& account,std::span<const TableId> source,std::size_t capacity) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a shared immutable managed-table owner, or a free empty handle. |
| inputs / outputs | Empty source returns default WindowTables without retaining requested capacity; nonempty source allocates accounted Data and vector copy. |
| invariants | Nonempty capacity&gt;=size required by Data. This helper does not create a fresh MemoryAccount or authorize a table. |
| ownership | Shares const Data; resulting options can outlive controller/session while retaining their original account. |
| failure | Private holder/vector failure publishes no handle and preserves caller data. |
| cost | Empty constant/no allocation; nonempty one accounted control plus vector capacity and ID copies. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0013

[Lines 67–67](../../../../../src/runtime/window.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t WindowTables::size() const noexcept {return data_?data_->values.size():0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read managed-table size from an optional owning WindowTables handle. |
| inputs / outputs | Readable handle returns size_t count or0; default empty handle is supported. |
| invariants | No table-range/duplicate validation or account admission occurs here. |
| ownership | Returns inline scalar copy; underlying Data remains owned by sharing handles. |
| failure | noexcept with no allocation or external runtime access. |
| cost | Constant shared-pointer/member check. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0014

[Lines 68–68](../../../../../src/runtime/window.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t WindowTables::capacity() const noexcept {return data_?data_->values.capacity():0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read managed-table capacity from an optional owning WindowTables handle. |
| inputs / outputs | Readable handle returns size_t reserved capacity or0; default empty handle is supported. |
| invariants | No table-range/duplicate validation or account admission occurs here. |
| ownership | Returns inline scalar copy; underlying Data remains owned by sharing handles. |
| failure | noexcept with no allocation or external runtime access. |
| cost | Constant shared-pointer/member check. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0015

[Lines 69–69](../../../../../src/runtime/window.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const TableId* WindowTables::data() const noexcept {return data_?data_->values.data():nullptr;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read managed-table data from an optional owning WindowTables handle. |
| inputs / outputs | Readable handle returns const TableId pointer or nullptr; default empty handle is supported. |
| invariants | No table-range/duplicate validation or account admission occurs here. |
| ownership | Pointer, if returned, borrows immutable Data; retain any sharing WindowTables handle for its lifetime. |
| failure | noexcept with no allocation or external runtime access. |
| cost | Constant shared-pointer/member check. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0016

[Lines 70–72](../../../../../src/runtime/window.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedWindowOptions::AccountedWindowOptions(const resource::MemoryAccount& account,const WindowOptions& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy ordinary WindowOptions into receiving-account immutable window policy. |
| inputs / outputs | Copies scalar width/FIFO/caps/work limit and deep-copies managed-table IDs preserving source capacity. |
| invariants | Accounted-source overload does not just share a foreign capacity owner; actual receiver funds the copied list. Semantic option validation is deferred to Impl. |
| ownership | New WindowTables storage belongs to supplied account; caller policy remains unchanged. |
| failure | Private allocation failure leaves no controller/policy publication. |
| cost | O(managed-table count) copy plus capacity storage; fixed scalar fields. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0017

[Lines 73–76](../../../../../src/runtime/window.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedWindowOptions::AccountedWindowOptions(const resource::MemoryAccount& account,const AccountedWindowOptions& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy AccountedWindowOptions into receiving-account immutable window policy. |
| inputs / outputs | Copies scalar width/FIFO/caps/work limit and deep-copies managed-table IDs preserving source capacity. |
| invariants | Accounted-source overload does not just share a foreign capacity owner; actual receiver funds the copied list. Semantic option validation is deferred to Impl. |
| ownership | New WindowTables storage belongs to supplied account; caller policy remains unchanged. |
| failure | Private allocation failure leaves no controller/policy publication. |
| cost | O(managed-table count) copy plus capacity storage; fixed scalar fields. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0018

[Lines 77–90](../../../../../src/runtime/window.cpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowController::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the sole mutable window label/count/index state. |
| inputs / outputs | Impl fields retain original account/options/catalog digest, label and distinct-count maps, expiration/global/per-table FIFO indexes, optional active watermark, sequences/work/byte ledger and prepared/stopped flags. |
| invariants | Every label references exactly one live distinct full-row count; indexes describe the same live labels. Only count0-&gt;1/1-&gt;0 yields physical set updates. Caller/session serializes access and enforces managed bases initially empty. |
| ownership | Account allocators fund all native rows/nodes/options/active vector. No external DTO row mirror is kept internally. |
| failure | Private constructors/preparation precede publication; no local catch/undo framework in state definition. |
| cost | O(labels+distinct rows+managed tables+expiring IDs) retained payload/index state; actual account includes node links/control/framing. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0019

[Lines 91–112](../../../../../src/runtime/window.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView,class Options> Impl(const resource::MemoryAccount& memory,const CatalogView& catalog,const Options& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate window policy and create original-account empty routing/count state. |
| inputs / outputs | MemoryAccount, immutable CatalogView and options copy funded policy, compute catalog digest, validate positive width/caps/work/FIFO and unique in-range managed tables, precreate per-table FIFO sets. All four explicit FIFO modes are admitted; other enum values reject. |
| invariants | Controller alone does not validate an initial Database; QuerySession checks managed bases empty. Initial declared bytes include managed capacity and relation descriptors, not full allocator overhead. Accept precisely policies 0..4, including explicit unrestricted; no requested declaration is inferred by a standalone controller. |
| ownership | Same account funds copied options/control, per-table map nodes and catalog-digest workspace; rows/indexes start empty. |
| failure | Invalid options/duplicate/range/byte cap or allocation/digest failure destroys private Impl and its nodes. |
| cost | Catalog digest scan plus O(M log M) managed-table setup, options copy/capacity and M map nodes; no query rows processed. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0020

[Lines 113–117](../../../../../src/runtime/window.cpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L117:sha256:9555de19618d518244019bd7180266fee35f58bd8952c20c4111779003530f50
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent preflight_patterns usage, ownership and cost boundary. |
| inputs / outputs | Source comment documents the neighboring implementation; it accepts no runtime input or output. |
| invariants | The note is guidance, not executable enforcement or independent proof. Detailed callable contracts describe the actual checks. Counter fill records one scoped_order flag during its existing pass. Without physical-per-relation or live positive scopes, zero groups share one ignored key and existing birth order is already sufficient; no sort or extra scan is performed. |
| ownership | No runtime owner is created by prose. |
| failure | The comment itself cannot throw or change admission. |
| cost | No runtime work or allocation; the adjacent operation retains its actual costs. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 118–172](../../../../../src/runtime/window.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L172:sha256:c6ccc5b98a05f64810ba8c1661e3895049ddedee2a02a06d4a1213f3c89fe7cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Simulate the entire declared watermark expiration sequence before its first effect. |
| inputs / outputs | Borrow current counts/labels/expirations and declaration; return E expiring labels after decrementing one local vector of group/birth/remaining counters. |
| invariants | Actual birth IDs survive initial-label removal. Positive scopes use raw IDs; zero is table-distinguished only for physical-per-relation; physical-global dominates all scopes. Final decrements require insertion permission and the oldest still-live group member. Successful ordered removals preserve a zero prefix, so the immediate predecessor suffices. Legacy physical failures retain window_fifo_violation; explicit scope failures record update_pattern_violation. Counter fill records one scoped_order flag during its existing pass. Without physical-per-relation or live positive scopes, zero groups share one ignored key and existing birth order is already sufficient; no sort or extra scan is performed. |
| ownership | One transient integer vector is funded by the original query account. Native rows/counts/indexes are synchronous borrows and remain unchanged. No second row store or retained scope index. |
| failure | Existing work grant or account failure rejects before publication. Completed semantic Error fills scalar scratch; failed Error allocation is retryable. Local ownership releases scratch with no new catch layer. |
| cost | O(D) scratch; O(D log R) setup, O(D log D) sorting only for per-table baseline or live positive scopes outside physical-global, O(E(log R+log D)) counter/rule comparisons plus existing label-tree costs. Every explicit visitor/sort/search charge precedes effects; this is not a CPU or engine maintenance bound. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0022

[Lines 173–208](../../../../../src/runtime/window.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L173-L208:sha256:936764fef3e2a5346397849f73a7846d1aa80d0bffcc2210d2d41f8b34455aa8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight a complete physical-lifetime watermark using the existing birth IDs. |
| inputs / outputs | An unopened watermark cutoff and command charge callback in; number of expiring labels out. Empty/no-expiration input returns zero without counter scratch. Caller invokes this only for physical modes before an active command exists. |
| invariants | Each validated live label references a positive count. Global count-ID order is birth order; per-table sorting groups that order. Zero counters start empty and stay a prefix within each group: a final decrement requires a zero predecessor or group start. Thus every hypothetical physical erase is oldest in its scope, while metadata-only decrements are unrestricted. The entire deadline/label sequence passes before any live effect. |
| ownership | Borrows Impl count/label/expiration indexes and the stack charge lambda. One OwnerAllocator vector of integer keys/refcounts is funded by the original account as scratch and destroyed on return/unwind. No row, permanent directory, callback or second allowance is retained. |
| failure | FIFO/work/allocation failure propagates through ordinary local cleanup before publication. Throwing comparator charges can leave scratch partially sorted; live state is unchanged. Lookup presence and positive counters follow the admitted graph invariants rather than extra hot-path error handlers. |
| cost | O(D) counter setup/storage, O(E log D) binary-search comparisons plus existing label lookups and expiration visits; per-table mode adds O(D log D) charged sorting. Actual vector capacity/framing consumes the query cap. The caller separately funds active E-ID storage and reserves future removals; abstract work is not CPU time. |
| Design | [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0023

[Lines 209–209](../../../../../src/runtime/window.cpp#L209); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L209-L209:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct WindowController::Impl\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct WindowController::Impl\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct WindowController::Impl\` at its lexical source position in src/runtime/window.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct WindowController::Impl\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0024

[Lines 210–224](../../../../../src/runtime/window.cpp#L210); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowController::Prepared::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own every resource for one unpublished window step and clear its busy flag on abandonment. |
| inputs / outputs | Prepared::Data holds a borrowed Impl pointer, owning native update row/view, extracted nodes for label/count/expiration/FIFOs, optional new active continuation and prospective counters/flags. |
| invariants | Impl must outlive Prepared; at most one live prepared token and destroy it before stop. No live map membership changes during preparation. Data destructor only clears owner.prepared; member owners release private rows/nodes. |
| ownership | AccountedUnique owns Data on original account journal_undo; node handles own funded nodes until publish moves them. update borrows update_values within this Data. |
| failure | Any preparation/native-step failure destroys token, clears busy and frees private resources without undoing already committed earlier watermark steps. |
| cost | Fixed carrier plus prepared nodes/native row copies/new expiration vector; abandonment deallocation costs, no whole-state rollback scan. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0025

[Lines 225–225](../../../../../src/runtime/window.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowController::Prepared::Prepared(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a move-only owner for one completely prepared window step. |
| inputs / outputs | AccountedUnique&lt;Data&gt; moves into Prepared. |
| invariants | No second token or independent native commit authority is created; publish must follow successful native engine or explicit metadata barrier. |
| ownership | Transfers sole private Data owner; Impl pointer remains borrowed under controller-outlives-token rule. |
| failure | noexcept handle move, no allocating work. |
| cost | Constant owner transfer. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0026

[Lines 226–228](../../../../../src/runtime/window.cpp#L226); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowController::Prepared::~Prepared()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define Prepared destruction and move ownership without copying unpublished work. |
| inputs / outputs | Default destructor/move construction/move assignment transfer/drop AccountedUnique&lt;Data&gt;; copying is forbidden by header. |
| invariants | Destroying an unpublished Data clears prepared flag and releases private nodes/row/vector. A moved-from token must not use update/completes accessors; publish tolerates empty. |
| ownership | Single Data owner. Move assignment first abandons any old token under the same controller-lifetime precondition. |
| failure | noexcept moves/cleanup; no rollback catch or native engine mutation here. |
| cost | Constant handle move plus destruction/release cost of any abandoned prepared resources. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0027

[Lines 229–229](../../../../../src/runtime/window.cpp#L229); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<PhysicalUpdateView>& WindowController::Prepared::update() const noexcept { return data_->update; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the optional physical set transition from a live prepared step. |
| inputs / outputs | Non-moved Prepared returns const optional&lt;PhysicalUpdateView&gt;&; disengaged means metadata-only step. |
| invariants | Physical view values are frozen in Prepared::Data and remain readable while token lives unchanged. It is not an owning detached result. |
| ownership | Borrows token metadata/update_values; controller/token lifetimes and serialization remain required. |
| failure | noexcept and allocation-free; invalid moved-from use is outside precondition. |
| cost | Constant pointer/member read. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0028

[Lines 230–230](../../../../../src/runtime/window.cpp#L230); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool WindowController::Prepared::completes_command() const noexcept { return data_->complete; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Determine whether publishing this step completes the external window command. |
| inputs / outputs | Live Prepared returns its complete flag. |
| invariants | An intermediate watermark step leaves completed command/watermark unchanged and input unacknowledged. |
| ownership | Returns inline Boolean; token retains all resources. |
| failure | noexcept; moved-from accessor use outside contract. |
| cost | Constant read. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0029

[Lines 231–261](../../../../../src/runtime/window.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void WindowController::Prepared::publish() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish already-funded window metadata after a successful native or metadata-only barrier. |
| inputs / outputs | Live Prepared transfers extracted insertion nodes or erases label/index/count references, installs active continuation, advances applicable command/physical/watermark/work/byte counters and releases owner link; empty/already-published token no-ops. |
| invariants | Integer-key comparators, matching allocators, validated existing IDs/counts and exclusive token make transfers nonallocating/nonthrowing. Physical engine commit must precede this method; it does not commit the engine itself. Only last watermark step resets active and advances completed watermark/command. |
| ownership | Moves node/vector ownership into Impl; removes/deallocates old rows/nodes as needed. p.owner=nullptr prevents destructor changing published busy state. |
| failure | noexcept under private invariant. No catch or reverse journal is needed after this barrier; misuse/concurrent mutation violates token contract. |
| cost | Ordered map/set insert/find/erase costs O(log live labels +log distinct counts+log managed tables) per affected index, plus row/node release and final vector teardown. Allocation-free does not mean constant time. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0030

[Lines 262–269](../../../../../src/runtime/window.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowController::WindowController(Catalog catalog,WindowOptions options)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a standalone operational window with its own explicit finite account. |
| inputs / outputs | By-value Catalog/WindowOptions create a new U64-max MemoryAccount then accounted Impl; standalone diagnostics/testing boundary. |
| invariants | This is a constructor admission account, not a per-command refill. QuerySession uses explicit original-account constructor instead. |
| ownership | Data/control/options/nodes retain new account; by-value caller objects may have ordinary allocations outside native operational state. |
| failure | Option/digest/account/allocation failure destroys private construction without a published controller. |
| cost | One account controller plus Impl setup/catalog scan and copied managed options. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0031

[Lines 270–272](../../../../../src/runtime/window.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowController::WindowController(const resource::MemoryAccount& account,const program::Catalog& catalog,const WindowOptions& options)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the operational window on the existing admitted query account. |
| inputs / outputs | Original MemoryAccount, program::Catalog and WindowOptions create accounted Impl with session/0 holder; nested options/index state uses session/1. |
| invariants | No new MemoryAccount/cap or ordinary Catalog copy; session checks initially empty managed bases separately. |
| ownership | Impl and every nested operational allocation use supplied account; frozen catalog is read during construction/digest. |
| failure | Private setup failure leaves no window owner and preserves native runtime. |
| cost | Impl/copy/digest/managed-table setup costs; no physical row maintenance in constructor. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0032

[Lines 273–273](../../../../../src/runtime/window.cpp#L273); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L273-L273:sha256:cf04d99c0f5d3521f67f7c587d20dd3592a5024b903529e1e468844f7fae8135
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/window.cpp: opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0033

[Lines 274–276](../../../../../src/runtime/window.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void state_require(bool condition,recovery::ImageFault fault=recovery::ImageFault::corrupt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject invalid native window checkpoint structure with fixed ImageFailure. |
| inputs / outputs | Boolean and optional ImageFault return or throw fixed native image error. |
| invariants | No allocating public diagnostic conversion, state repair or runtime admission occurs here. |
| ownership | Scalar exception payload only. |
| failure | False condition throws ImageFailure before next private restore action. |
| cost | One branch on success. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0034

[Lines 277–284](../../../../../src/runtime/window.cpp#L277); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StateBudget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound abstract checkpoint capture/restore visits separately from bytes and account allocation. |
| inputs / outputs | WindowStateLimits with used=0 charges checked work; row charges1+field count. |
| invariants | Fresh per-call state-validation budget. Does not meter every tree comparison/scalar byte/clone or mint a native runtime grant. |
| ownership | Stack scalar budget only, borrowed by scratch comparator during restore. |
| failure | Fixed ImageFailure(work) before limit/overflow; earlier local used remains spent until call ends. |
| cost | Constant charge and row-width count; actual downstream row copies/comparisons cost additional bytes. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0035

[Lines 285–285](../../../../../src/runtime/window.cpp#L285); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StateKey {TableId table;storage::RowView values;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a borrowed (table,full native row) key used only during restore uniqueness validation. |
| inputs / outputs | TableId and RowView identify one count row. |
| invariants | Row data belongs to immutable source WindowCheckpoint for entire scratch map lifetime; keys never escape restore. |
| ownership | Nonowning RowView; scratch node allocation is separately accounted. |
| failure | No runtime validation/allocation in this carrier. |
| cost | Fixed key fields, without row-byte copy. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0036

[Lines 286–292](../../../../../src/runtime/window.cpp#L286); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StateKeyLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order restore uniqueness keys with bounded table/row-field visits. |
| inputs / outputs | StateBudget pointer plus StateKeys compare table first then native full-row lexicographic values, charging declared comparison/field visits. |
| invariants | Comparator budget lives through private Unique map construction/destruction. String/decimal byte comparisons and ordered-tree shape costs exceed the abstract field debits. |
| ownership | Borrows checkpoint row bytes and local budget; no allocation by comparator. |
| failure | Work exhaustion throws during private scratch insertion, before controller publication; partial maps unwind. |
| cost | One table comparison plus O(row arity and compared scalar bytes), invoked O(log count rows) per tree insertion. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0037

[Lines 293–293](../../../../../src/runtime/window.cpp#L293); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L293-L293:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/window.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/window.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/window.cpp\` at its lexical source position in src/runtime/window.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/window.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0038

[Lines 294–308](../../../../../src/runtime/window.cpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowCheckpoint WindowController::checkpoint_state(WindowStateLimits limits) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture quiescent native window state with owning rows and original-account metadata. |
| inputs / outputs | No prepared/active command, label/count caps and WindowStateLimits preflight visits before cloning ordered labels/counts into WindowCheckpoint. |
| invariants | Active watermark, including stopped tombstone, rejects; capture does not invent a whole-command snapshot. Preserves count identity even when its original label has expired. |
| ownership | Options share immutable WindowTables account owner; returned label/count arrays and native row clones use original account/image owner and survive controller destruction. |
| failure | Budget/cap/allocation/clone failure drops private result and leaves controller/progress unchanged. |
| cost | O(labels+counts+all cloned scalar bytes) scans/copies plus reserved arrays; capture budget counts structural/field visits, not every byte/allocator overhead. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0039

[Lines 309–356](../../../../../src/runtime/window.cpp#L309); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowController::WindowController(const resource::MemoryAccount& account,const program::Catalog& catalog,
    const WindowCheckpoint& source,WindowStateLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate/rebuild an unpublished window from quiescent native checkpoint state. |
| inputs / outputs | Receiver account/catalog/WindowCheckpoint/limits validate progress/options/catalog digest, count ID/order/full-row uniqueness/types/decimal shapes, label deadlines/references/table/value equality and exact reference totals, then derive all indexes. |
| invariants | No active/prepared state; labels/count IDs and original count identities preserved. Controller rebuild remains separate from native base-row/window matching performed by DeltaRuntime session restore. |
| ownership | Deep-clones source rows/options on receiver. Borrowed source keys and reference counters live only in receiver-account scratch maps; final holder and nested state are accounted. |
| failure | Any malformed count/label/catalog/option/budget/allocation error unwinds private result. Caller source/checkpoint/runtime are untouched; no catch/partial owner published. |
| cost | Catalog hash, O(C log C) uniqueness/reference trees and O(L(log L+log C+log M)) index rebuild plus native row comparisons/clones; scalar bytes/account overlap are additional. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp) |

## B0040

[Lines 357–358](../../../../../src/runtime/window.cpp#L357); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowController::~WindowController()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release WindowController state through its existing shared Impl owner. |
| inputs / outputs | Default destructor drops data_; any retained immutable WindowTables or captured rows remain independent owners. |
| invariants | All Prepared tokens must be destroyed first; their raw Impl pointer is not a lifetime extension. No filesystem/replay/history authority here. |
| ownership | Last Impl release destroys accounted maps/rows/active vector/options and original account handles. |
| failure | Noexcept ordinary member cleanup; no new catch or query rollback. |
| cost | Potential O(resident labels/counts/index nodes/active capacity) teardown, not constant solely because the public handle is small. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0041

[Lines 359–362](../../../../../src/runtime/window.cpp#L359); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void RuntimeTestProbe::seed_window_sequence(WindowController& runtime,std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed physical sequence boundary in the testing build. |
| inputs / outputs | RuntimeTestProbe and U64 sequence update Impl.physical only when not prepared/stopped. |
| invariants | CROWN_RUNTIME_TESTING only; explicit saturation/boundary fixture, not an imported production checkpoint or grant refill. |
| ownership | Mutates one test-only scalar; no row/ID owner changes. |
| failure | Probe precondition Error may throw; no account allocation on valid path. |
| cost | Constant branch/write; absent in normal production API. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0042

[Lines 363–363](../../../../../src/runtime/window.cpp#L363); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L363-L363:sha256:9a349bbd1a21104f051e34b2c8a9e70cc7fbb50bc19a67781f2a140c386d9438
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/window.cpp: closes the matching compile-time guard. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0043

[Lines 364–364](../../../../../src/runtime/window.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedWindowOptions& WindowController::options() const noexcept { return data_->options; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow admitted immutable window policy. |
| inputs / outputs | Readable controller returns const AccountedWindowOptions&. |
| invariants | Changing detached reports cannot alter policy; no validation/copy/recalculation here. |
| ownership | Reference lifetime requires controller/Impl; caller can copy AccountedWindowOptions/WindowTables for owning metadata as appropriate. |
| failure | noexcept no allocation or mutation. |
| cost | Constant pointer/member access. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0044

[Lines 365–367](../../../../../src/runtime/window.cpp#L365); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowMetrics WindowController::metrics() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read label/distinct-row counts and declared retention/work metrics. |
| inputs / outputs | Readable controller returns WindowMetrics by value from map sizes and stored ledger/counter. |
| invariants | accounted_bytes is the policy descriptor/payload ledger; actual account bytes/framing/transient prep differ. last_command_work is committed command/prepaid active work, not total CPU across retries. |
| ownership | Fixed scalar report, no row view. |
| failure | noexcept and allocation-free. |
| cost | Constant sizes/counter reads. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0045

[Lines 368–373](../../../../../src/runtime/window.cpp#L368); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowProgress WindowController::progress() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report independently committed command, physical and active-watermark progress. |
| inputs / outputs | Returns completed command/physical/watermark/last_label; active continuation adds sequence/completed_steps/total_steps. |
| invariants | Partial watermark retains preceding completed watermark/command while physical set steps may advance. Report is descriptive, not an acknowledgment/restore token. |
| ownership | Fixed scalar copy with optional sequence. |
| failure | noexcept no allocation/read of source/runtime. |
| cost | Constant field copies. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0046

[Lines 374–380](../../../../../src/runtime/window.cpp#L374); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void WindowController::stop() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make window stepping terminal while retaining its committed active-prefix tombstone. |
| inputs / outputs | Sets stopped=true; if active, subtracts actual vector capacity from ledger and swaps its expiration labels with empty same-allocator vector. |
| invariants | Destroy Prepared before stop. Does not undo earlier physical steps or acknowledge unfinished command; active scalar sequence/step/work metadata remains inspectable and still blocks checkpoint_state. |
| ownership | Releases active-vector payload on original account; label/count/index state remains resident until controller destruction. |
| failure | noexcept, no new allocation; repeated stop sees empty capacity and does not subtract twice. |
| cost | Fixed swaps/updates plus vector deallocation; no label/count scan. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0047

[Lines 381–396](../../../../../src/runtime/window.cpp#L381); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowCanonicalState WindowController::canonical_state() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a full external diagnostic DTO of committed window bookkeeping. |
| inputs / outputs | Copies labels/count rows, expiration/global/per-table FIFO lists, scalar progress/metrics and optional active IDs into WindowCanonicalState. |
| invariants | Diagnostic whole-state export is separate from operational account-owned state/checkpoint. Session guards reject private work before invoking its public diagnostic wrapper. |
| ownership | Returned ordinary Row/string/vector graph owns its copies outside native account; no live map views escape. |
| failure | Ordinary allocation/scalar export failure propagates and drops private DTO, leaving controller unchanged. |
| cost | O(all resident rows/scalar bytes+index memberships+active IDs) scans/copies and ordinary heap allocations; not a hot update primitive. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0048

[Lines 397–399](../../../../../src/runtime/window.cpp#L397); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowController::Prepared WindowController::prepare(const io::WindowCommand& command,std::uint64_t next_physical_sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an owning input command for the native-view preparation path. |
| inputs / outputs | WindowCommand and next physical sequence convert via WindowCommandView::borrow then call prepare_view. |
| invariants | Same admission/publication semantics; no duplicate whole-command implementation. |
| ownership | Command bytes borrow synchronously; needed retained values are frozen by prepare_view. |
| failure | Delegates validation/resource/allocation errors; no mutation committed here. |
| cost | Constant view conversion plus preparation cost below. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0049

[Lines 400–400](../../../../../src/runtime/window.cpp#L400); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L400-L400:sha256:e9b0f7bae786ddebf89729a523ecf5376c44653212803ae40983f268205d66a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether a source table belongs to the real window owner. |
| inputs / outputs | Borrow TableId and return Impl::relations.contains(table). |
| invariants | Only membership in admitted managed tables is tested; this does not infer a FIFO scope or validate historical ordering. |
| ownership | Borrow controller map synchronously; no returned reference or owner. |
| failure | noexcept native ordered-map lookup with fixed table-key comparison. |
| cost | O(log M) comparisons for M managed tables; no allocation, row scan or new directory. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0050

[Lines 401–403](../../../../../src/runtime/window.cpp#L401); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowController::Prepared WindowController::prepare_view(const io::WindowCommandView& command,std::uint64_t next_physical_sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate the public window view adapter to existing preparation with no Session declaration. |
| inputs / outputs | Borrow WindowCommandView/next physical sequence and call private prepare_pattern_view with null declaration/violation pointers. |
| invariants | The private implementation preserves all baseline ordering, limits and publication behavior. Only QuerySession supplies a declaration; this adapter never synthesizes enforced history. |
| ownership | The original account funds Prepared Data, owned update rows/nodes and active expiration IDs. Legacy per-table watermark validation owns a temporary cursor map; physical modes instead own one transient integer-counter vector. Controller outlives token; abandoned private resources unwind directly without a new handler or row mirror. |
| failure | Invalid option/state/FIFO/time/sequence/work/byte/label/counter or allocation failure leaves current step unpublished; earlier watermark steps remain committed. Prospective prep work is discarded on abort; after first committed watermark step its prepaid command work persists in active state. |
| cost | Fixed delegation plus the original policy-dependent preparation costs; undeclared delegation adds no counter/rule scan or retained storage. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0051

[Lines 404–553](../../../../../src/runtime/window.cpp#L404); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto p=resource::make_accounted_unique<Prepared::Data>(window_memory,d.account,resource::MemoryPurpose::journal_undo,d);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin a private step without marking the live window busy prematurely. |
| inputs / outputs | After stopped/prepared/contiguous-command checks, allocate Data and copy prospective command/ledger; final success sets d.prepared. |
| invariants | No callback/native commit occurs during this preparation; controller lifetime/serialization required. A thrown preparation cannot strand prepared=true. |
| ownership | The local AccountedUnique owns Prepared Data, extracted nodes, the update row and any new active ID vector until transfer or unwind. Physical lifetime counters instead belong to the preflight local scratch vector and die before return; all use the original query account. |
| failure | Allocation/validation failure destroys Data and private owners; live maps/progress unchanged. |
| cost | One fixed original-account holder allocation plus subsequent branch-specific prep resources. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

```text
auto charge=[&](std::uint64_t n=1) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit prospective per-command abstract window work. |
| inputs / outputs | New commands start at zero; active watermarks reuse prepaid work. Each selected visit, row-column unit and physical counter build/sort/search/step charge checks the remaining command_work_limit before publication. |
| invariants | This counter publishes only with the step; aborted preparation discards prospective work. After first watermark step the full reservation stays in active state. It is not a cumulative CPU grant across retries. |
| ownership | Local lambda borrows Data/Impl and stores no callback. |
| failure | resource_limit rejects current prep before effect; no error handler/refill cache. |
| cost | Constant checked addition per explicit charge site. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

```text
auto physical=[&](TableId table,SetOperation operation,storage::RowView row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze a physical set transition owned by the prepared token. |
| inputs / outputs | When distinct row crosses0/1, require representable contiguous next physical sequence and deep-copy native row into update_values, then borrow it in PhysicalUpdateView. |
| invariants | Metadata-only label changes do not consume a physical epoch. Engine/schema/constraint validation and commit precede window publish. |
| ownership | Original account owns prepared native row independently of live label/count rows and caller command. |
| failure | Sequence/account/clone failure aborts prep before live row/count changes. |
| cost | O(row scalar bytes) native copy and one owning row allocation; no ordinary Row/string mirror. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

```text
auto remove=[&](std::uint64_t id,bool check_fifo) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Plan one label removal and physical erase only for its final reference. |
| inputs / outputs | Find a live label/count and prospective byte change. Label policies check the oldest live label; physical policies allow metadata-only removals and check the oldest count birth globally/per table only on the final reference. Count one freezes a physical erase. |
| invariants | Whole-watermark removals consume their complete validated order and prepaid removal work. Explicit physical checks use retained birth count IDs, including orphaned original labels; per-table checks never establish joint FIFO across tables. Explicit final-reference removal first checks insertion-only and positive joint scopes. Active watermark removals skip repeated pattern checks because the whole command was preflighted. Scope zero is unrestricted by the declaration; baseline policies still apply. |
| ownership | Reads live nodes without mutation; prepared row owns any physical payload. |
| failure | Unknown label/FIFO/sequence/allocation error leaves current committed prefix unchanged. |
| cost | Ordered label/count/table lookups and optional native row copy. Explicit final-reference physical-per-table mode additionally scans live counts with charged visits; global physical front lookup uses counts.begin(). No new retained directory or row copy is used for monitoring. Opt-in table lookup is O(log R); explicit scoped withdrawal can scan D existing birth-ordered counts with charged O(log R) member lookup each. No new persistent directory or scratch vector. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

```text
for (const auto& [id,count]:d.counts) {
      charge(); charge(static_cast<std::uint64_t>(insert->values.size()));
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve duplicate labels against the same complete physical row. |
| inputs / outputs | Linear distinct-count scan checks table plus exact native row equality; first match reuses count ID and increments only on publish. |
| invariants | Unused/nonprojected columns still distinguish rows. This is explicit linear lookup, not an indexed-update complexity claim. |
| ownership | Borrows caller values/live count rows; new distinct count and label later get separate accounted native copies. |
| failure | Per-command work/row copy/count overflow failure rejects current prep; no map mutation during scan. |
| cost | O(distinct rows * row arity/compared scalar bytes), with declared visit/column debits and additional tree/byte costs. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

```text
auto global=d.global.begin();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight each required declared/physical/legacy expiration condition before the first watermark effect. |
| inputs / outputs | For values 0/1 only, compare deadline-order expiring label IDs with global or per-table live-label iterators. Reject label-order violations without skipping or reordering an expiration. |
| invariants | This branch enforces label FIFO. Duplicate labels do not establish physical-lifetime FIFO. Values 2/3 use the separate integer-counter preflight; legacy cursor scratch borrows immutable insertion indexes. A constrained declaration uses one combined lifetime preflight, including baseline physical ordering. Legacy label ordering still runs when selected; unrestricted skips that label ordering. Expiring count is not double charged. |
| ownership | Original-account per-table cursor map and fixed iterators; no cloned live state. |
| failure | FIFO/work/allocation failure before any expiration is committed. Later commands cannot pass the active watermark. |
| cost | O(managed tables) scratch nodes for per-table mode and O(expiring labels+boundary) visits plus ordered label/table lookups. Declared path additionally uses one O(D) integer vector, O(D log D) sort only when baseline per-table or live positive scopes require grouping outside global, and O((D+E) log R + E log D) comparisons. Existing per-table label cursors and active-ID storage retain their own costs. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

```text
charge(static_cast<std::uint64_t>(expiring)); // Reserve all future removal work now.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve all future watermark-removal work and actual expansion capacity before stepping. |
| inputs / outputs | After validated expiration count, allocate ID vector, copy full order, charge actual capacity in ledger, debit every future removal and store total/accounted_work in new_active. |
| invariants | First effect cannot leave later steps needing unadmitted abstract removal work. Actual native maintenance/output/row-copy allocations retain their independent limits. Use the count from the selected whole-command preflight exactly once, then prepay future active removals; no per-substep pattern resimulation. |
| ownership | Prepared owns new vector until publish; active state retains it across steps and releases after last/stop. |
| failure | Byte/work/reserve failure aborts before first live effect; actual prior watermark steps are unaffected on later retry. |
| cost | O(expiring labels) vector copy/capacity and second scan; no whole-window row clone. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0052

[Lines 554–554](../../../../../src/runtime/window.cpp#L554); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L554-L554:sha256:97734ee3ed73fbf0bd112ff8fee5fae528737ea20327081d48b1efcf3f9b9a5a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in src/runtime/window.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/batches_windows.md](../../../../batches_windows.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
