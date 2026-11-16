# `src/runtime/weighted_cursor.cpp` — block usage map

[Source](../../../../../src/runtime/weighted_cursor.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact full-subtree messages and local visible factors, then enumerate projected core tuples with multiplicities.

Snapshot SHA-256: `935f47db594f7ad68f584fa9e227ed987822717dba61d2565a497284fa749a52`. 193 lines partitioned into 32 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [weighted](../../../subsystem_contracts.md#weighted). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/annotations.md](../../../../annotations.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/runtime/weighted_cursor.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body. | source comment (unverified): // Usage, factor proof and cost boundaries: docs/weighted_enumeration.md. · [reviewed contract](#b0001) |
| [B0002 · 14–19](../../../../../src/runtime/weighted_cursor.cpp#L14) | Type/record definition: struct Frame |  · [reviewed contract](#b0002) |
| [B0003 · 20–36](../../../../../src/runtime/weighted_cursor.cpp#L20) | declares values/defaults or compile-time conditions. | source comment (unverified): // Program/layout/binding remain inspectable after close. Only an active · [reviewed contract](#b0003) |
| [B0004 · 37–56](../../../../../src/runtime/weighted_cursor.cpp#L37) | Callable definition: Data(std::shared_ptr&lt;Impl&gt; runtime, CursorOptions opts) :owner(std::move(runtime)),lease(detail::storage_lease(owner-&gt;context)), … | calls owner, std::move, lease, detail::storage_lease; growth emplace_back, reserve; 1 loop sites; source comment (unverified): // Reserve traversal/output scratch before publishing a reader. Startup · [reviewed contract](#b0004) |
| [B0005 · 57–57](../../../../../src/runtime/weighted_cursor.cpp#L57) | Callable definition: ~Data() | calls close · [reviewed contract](#b0005) |
| [B0006 · 58–58](../../../../../src/runtime/weighted_cursor.cpp#L58) | Explanatory comments or spacing. |  |
| [B0007 · 59–64](../../../../../src/runtime/weighted_cursor.cpp#L59) | Callable definition: void charge(std::uint64_t amount=1) | calls require; guard require(amount&lt;=UINT64_MAX-metrics.work && (!options.work_limit \|\| · [reviewed contract](#b0007) |
| [B0008 · 65–70](../../../../../src/runtime/weighted_cursor.cpp#L65) | Callable definition: void metric(std::uint64_t& counter, std::uint64_t amount=1) | calls charge; source comment (unverified): // Metric-managed counters start at zero and are subsets of total work. · [reviewed contract](#b0008) |
| [B0009 · 71–77](../../../../../src/runtime/weighted_cursor.cpp#L71) | Callable definition: void sample_grant() noexcept | calls limit, get, remaining · [reviewed contract](#b0009) |
| [B0010 · 78–88](../../../../../src/runtime/weighted_cursor.cpp#L78) | Callable definition: void close(CursorState state) noexcept | calls sample_grant, clear, std::terminate, reset; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 89–91](../../../../../src/runtime/weighted_cursor.cpp#L89) | Callable definition: storage::ScalarView value(AssignmentSlot slot) const | calls at, values; returns frames.at(slot.step).selected-&gt;values()\[slot.field.value\] · [reviewed contract](#b0011) |
| [B0012 · 92–94](../../../../../src/runtime/weighted_cursor.cpp#L92) | Explanatory comments or spacing. | source comment (unverified): // Visible tuples are borrowed under the runtime reader lease. Native table · [reviewed contract](#b0012) |
| [B0013 · 95–117](../../../../../src/runtime/weighted_cursor.cpp#L95) | Callable definition: bool select(Frame& frame, const program::EnumerationStep& step) | calls table, metric, require, fields; guard require(step.parent_key && step.bucket_index,"weighted_contract","visible child lacks its compiled …; returns false; true; source comment (unverified): // Visible tuples are borrowed under the runtime reader lease. Native table · [reviewed contract](#b0013) |
| [B0014 · 118–121](../../../../../src/runtime/weighted_cursor.cpp#L118) | Callable definition: void close_frame(Frame& frame) | calls metric, reset · [reviewed contract](#b0014) |
| [B0015 · 122–136](../../../../../src/runtime/weighted_cursor.cpp#L122) | Callable definition: Result emit(Multiplicity count) | calls enumeration, metric, require, value; guard require(value(equality.left)==value(equality.right),"weighted_contract","visible assignments disagr…; returns {std::move(tuple),count}; growth push_back; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 137–148](../../../../../src/runtime/weighted_cursor.cpp#L137) | Callable definition: std::optional&lt;Result&gt; advance() | calls metric, route, emit, require; guard require(!frames.empty(),"weighted_contract","weighted visible program has no root");; returns {}; {} · [reviewed contract](#b0016) |
| [B0017 · 149–166](../../../../../src/runtime/weighted_cursor.cpp#L149) | Callable definition: std::optional&lt;Result&gt; next() | calls require, operation, advance, sample_grant; guard require(status!=CursorState::failed,"invalid_cursor","weighted result cursor failed and is closed");; returns {}; result; source comment (unverified): // One real cursor failure boundary: release all borrowed state/readers, · [reviewed contract](#b0017) |
| [B0018 · 167–168](../../../../../src/runtime/weighted_cursor.cpp#L167) | Closes surrounding scope/type. |  · [reviewed contract](#b0018) |
| [B0019 · 169–176](../../../../../src/runtime/weighted_cursor.cpp#L169) | Callable definition: WeightedRuntime::ResultCursor WeightedRuntime::results(CursorOptions options) const | calls impl, readable, require, operation; guard require(owner.readers!=UINT64_MAX,"resource_limit","weighted reader count exhausted");; returns ResultCursor(std::move(data)); growth make_accounted_unique · [reviewed contract](#b0019) |
| [B0020 · 177–177](../../../../../src/runtime/weighted_cursor.cpp#L177) | Callable definition: WeightedRuntime::ResultCursor::ResultCursor(resource::AccountedUnique&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0020) |
| [B0021 · 178–180](../../../../../src/runtime/weighted_cursor.cpp#L178) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |
| [B0022 · 181–183](../../../../../src/runtime/weighted_cursor.cpp#L181) | Callable definition: WeightedRuntime::ResultCursor::Data& WeightedRuntime::ResultCursor::data() const | calls require, bool; guard require(bool(data_),"invalid_cursor","weighted result cursor was moved from");return *data_;; returns *data_ · [reviewed contract](#b0022) |
| [B0023 · 184–184](../../../../../src/runtime/weighted_cursor.cpp#L184) | Callable definition: bool WeightedRuntime::ResultCursor::active() const noexcept | calls ; returns data_ && data_-&gt;status==CursorState::active · [reviewed contract](#b0023) |
| [B0024 · 185–185](../../../../../src/runtime/weighted_cursor.cpp#L185) | Callable definition: CursorState WeightedRuntime::ResultCursor::state() const | calls data; returns data().status · [reviewed contract](#b0024) |
| [B0025 · 186–186](../../../../../src/runtime/weighted_cursor.cpp#L186) | Callable definition: std::uint64_t WeightedRuntime::ResultCursor::sequence() const | calls data; returns data().sequence · [reviewed contract](#b0025) |
| [B0026 · 187–187](../../../../../src/runtime/weighted_cursor.cpp#L187) | Callable definition: std::uint64_t WeightedRuntime::ResultCursor::owner() const | calls data; returns data().owner_id · [reviewed contract](#b0026) |
| [B0027 · 188–188](../../../../../src/runtime/weighted_cursor.cpp#L188) | Callable definition: const Binding& WeightedRuntime::ResultCursor::binding() const & | calls data; returns data().binding · [reviewed contract](#b0027) |
| [B0028 · 189–189](../../../../../src/runtime/weighted_cursor.cpp#L189) | Callable definition: const storage::TupleLayout& WeightedRuntime::ResultCursor::layout() const & | calls data; returns data().output_layout · [reviewed contract](#b0028) |
| [B0029 · 190–190](../../../../../src/runtime/weighted_cursor.cpp#L190) | Callable definition: const CursorMetrics& WeightedRuntime::ResultCursor::metrics() const & | calls data; returns data().metrics · [reviewed contract](#b0029) |
| [B0030 · 191–191](../../../../../src/runtime/weighted_cursor.cpp#L191) | Callable definition: std::optional&lt;Result&gt; WeightedRuntime::ResultCursor::next() | calls data, next; returns data().next() · [reviewed contract](#b0030) |
| [B0031 · 192–192](../../../../../src/runtime/weighted_cursor.cpp#L192) | Callable definition: void WeightedRuntime::ResultCursor::cancel() noexcept | calls close · [reviewed contract](#b0031) |
| [B0032 · 193–193](../../../../../src/runtime/weighted_cursor.cpp#L193) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0032) |

## B0001

[Lines 1–13](../../../../../src/runtime/weighted_cursor.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:be6bfa8350640a4006c40d6610dc2ee2d559ef7a7fc1a5946b30d39c8eb5a406
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/weighted_cursor.cpp: imports \`"weighted_detail.hpp"\`, \`&lt;algorithm&gt;\` for compilation; opens namespace \`crown::runtime\`; opens anonymous namespace with translation-unit-local linkage; imports or aliases \`weighted_detail::Vector\`, \`weighted_detail::require\`; defines/starts \`struct WeightedRuntime::ResultCursor::Data\` in this range; closes \`anonymous namespace\`. Source comment: Usage, factor proof and cost boundaries: docs/weighted_enumeration.md. Enumerate positive visible keys; each child weight enters one prefix product Member/state declarations in this range include \`} struct WeightedRuntime::ResultCursor::Data {\`. |
| inputs / outputs | This span declares/carries these members or local values: \`} struct WeightedRuntime::ResultCursor::Data {\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: Usage, factor proof and cost boundaries: docs/weighted_enumeration.md. Enumerate positive visible keys; each child weight enters one prefix product. Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 14–19](../../../../../src/runtime/weighted_cursor.cpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Frame {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one visible enumeration step and scalar prefix for iterative backtracking. |
| inputs / outputs | Optional native cursor/key, borrowed selected tuple and product of selected factors through this linear step. |
| invariants | Parent separator lookup uses parent_step; prefix multiplication uses the immediately preceding compiled step, including earlier siblings. |
| ownership | No per-frame row copy or arena pin; the global cursor reader keeps selected rows stable. Key storage uses the original account. |
| failure | Frame acquisition/advance may fail at the outer next boundary; clearing it requires no new allocation. |
| cost | Fixed metadata per C* step, plus one live/bucket cursor and projected key while opened. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0003

[Lines 20–36](../../../../../src/runtime/weighted_cursor.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L36:sha256:7a9f8c1e406a82d2d824a6028eea5c708e2503f75e918aac40611186cbb40914
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/weighted_cursor.cpp: this range contains member/state declarations Source comment: Program/layout/binding remain inspectable after close. Only an active cursor retains mutable runtime state and its one original native grant Member/state declarations in this range include \`std::shared_ptr&lt;Impl&gt; owner\`; \`storage::TupleLayout output_layout\`; \`std::uint64_t owner_id, sequence\`; \`Vector&lt;Frame&gt; frames\`; \`Vector&lt;storage::ScalarView&gt; row\`; \`std::size_t position=0\`; \`bool answer=false, resume=false, leased=false\`. |
| inputs / outputs | This span declares/carries these members or local values: \`std::shared_ptr&lt;Impl&gt; owner\`; \`storage::TupleLayout output_layout\`; \`std::uint64_t owner_id, sequence\`; \`Vector&lt;Frame&gt; frames\`; \`Vector&lt;storage::ScalarView&gt; row\`; \`std::size_t position=0\`; \`bool answer=false, resume=false, leased=false\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | The source note says: Program/layout/binding remain inspectable after close. Only an active cursor retains mutable runtime state and its one original native grant. Prose alone does not enforce the rule. |
| ownership | Vector is the runtime account-backed vector alias; the enclosing constructor selects the account and purpose. shared_ptr members retain shared state for the handle lifetime. Span/view members borrow their source; retain the source owner for the full use window. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 37–56](../../../../../src/runtime/weighted_cursor.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<Impl>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a complete cursor owner and funded scratch before publishing its reader. |
| inputs / outputs | Runtime/options produce retained program/layout/binding, empty frames and reserved output-cell scratch. |
| invariants | Snapshot root existence once; the upcoming reader lease makes it immutable. Startup visits no data rows. |
| ownership | Program/layout alias accounted immutable metadata; frame/row storage and one retained native grant use the same account. |
| failure | Constructor failure destroys partial owners with reader count unchanged. Factory increments readers only after success. |
| cost | O(number of compiled visible steps plus output width) scratch reservation; no answer materialization. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0005

[Lines 57–57](../../../../../src/runtime/weighted_cursor.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close a reader abandoned by token destruction. |
| inputs / outputs | Destruction requests cancelled state if still active. |
| invariants | Terminal Data is left terminal; close is idempotent. |
| ownership | RAII releases borrowed frames before the retained owner/grant. |
| failure | Noexcept cleanup contract. |
| cost | O(all preallocated C* frames) plus native release; final owner destruction may also release the runtime. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0007

[Lines 59–64](../../../../../src/runtime/weighted_cursor.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one cumulative cursor-work increment. |
| inputs / outputs | Amount to updated work count, bounded by uint64 and optional cap. |
| invariants | Validate before debit; never reset across next calls. |
| ownership | Scalar state in the cursor; no owning diagnostic on the success path. |
| failure | Exhaustion throws resource_limit; startup/next owns the appropriate cleanup boundary. |
| cost | Fixed-width arithmetic/comparisons; this counter is not CPU instructions or a wall-time bound. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0008

[Lines 65–70](../../../../../src/runtime/weighted_cursor.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void metric(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count one performed category of work under the same cumulative budget. |
| inputs / outputs | A reference to a metric-managed category counter and a nonnegative increment; updates total and category once. |
| invariants | Managed counters begin at zero and increment only here, so each is at most cumulative work. Successful charge proves both additions fit; phase summaries, queue peaks and cleanup counts are not passed here. |
| ownership | Borrows inline cursor/epoch counters; no memory allocation on success. |
| failure | Budget or total-overflow rejection happens in charge before the category increment; the existing outer boundary handles rollback or cursor closure. |
| cost | Fixed-width budget/overflow checks once in charge, then two scalar additions; no second category overflow guard. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0009

[Lines 71–77](../../../../../src/runtime/weighted_cursor.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sample_grant() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record original native work spent without creating another allowance. |
| inputs / outputs | Retained lease remaining dimensions subtracted from immutable per-operation maxima. |
| invariants | Reference mode has no lease/debit; closed metadata preserves the last sample. |
| ownership | Borrows context/allowance while active, stores only scalar diagnostics. |
| failure | No allocation or arithmetic admission during sampling. |
| cost | Five fixed subtractions; no storage traversal. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0010

[Lines 78–88](../../../../../src/runtime/weighted_cursor.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void close(CursorState state)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release all borrowed traversal state and exactly one published reader. |
| inputs / outputs | Active cursor to exhausted/cancelled/failed state; metadata and spent diagnostics remain. |
| invariants | Destroy frame cursors/keys before releasing runtime. Repeated close is harmless and cannot change an already closed state. |
| ownership | Clears scratch elements, drops grant/runtime, retains program/layout/binding and caller-owned buffer capacities until data destruction. |
| failure | No allocation; only violated internal reader ownership can terminate a noexcept close. |
| cost | O(all C* frames), including unopened frames, plus underlying key/cursor destruction. Final runtime destruction can be O(state size) after the facade is gone; it is separate from abstract forward work. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0011

[Lines 89–91](../../../../../src/runtime/weighted_cursor.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::ScalarView value(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one selected visible scalar by compiled assignment slot. |
| inputs / outputs | A compiled step/field pair returns a ScalarView into that frame selected tuple. |
| invariants | Called only for a complete selected assignment; immutable compilation validated field positions. |
| ownership | View borrows the frame tuple under the reader lease; emit copies it into owning output before advancing. |
| failure | Invalid internal step/selection is a contract defect, not user-input recovery. |
| cost | O(1), no export or allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0012

[Lines 92–94](../../../../../src/runtime/weighted_cursor.cpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L94:sha256:d454f0416a3fa695d530766d2a94d12098df74f39af42a7804f84a1880efe4ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`bool select(Frame& frame, const program::EnumerationStep& step)\`: Visible tuples are borrowed under the runtime reader lease. Native table cursors follow live links/buckets; no snapshot, pin per row or result set. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/weighted_cursor.cpp:L95; use that declaration for the actual input/output shape. |
| invariants | The source note states: Visible tuples are borrowed under the runtime reader lease. Native table cursors follow live links/buckets; no snapshot, pin per row or result set. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Visible tuples are borrowed under the runtime reader lease. Native table cursors follow live links/buckets; no snapshot, pin per row or result set. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0013

[Lines 95–117](../../../../../src/runtime/weighted_cursor.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool select(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one compiled E step and cache its positive factor prefix. |
| inputs / outputs | Frame plus EnumerationStep to selected row or exhausted bucket. |
| invariants | Root scans live entries; child projects its selected parent to the compiled separator index. Prefix multiplies each selected factor once. |
| ownership | Selected rows borrow native tables under the reader; only the lookup key is an owning temporary. |
| failure | Native grant/heap/work and checked multiplication failures propagate through next. |
| cost | One cursor advance, ID-map factor lookup and checked product per selection; hash/order/payload costs remain explicit. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0014

[Lines 118–121](../../../../../src/runtime/weighted_cursor.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void close_frame(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End one exhausted step before backtracking. |
| inputs / outputs | Open frame to cleared cursor/key/selected reference. |
| invariants | A later parent selection reopens the step with a fresh matching key; no stale selected pointer is used. |
| ownership | Release read cursor/key while the overall runtime reader remains held. |
| failure | Forward-work admission may fail first; outer close then cleans it without another budget check. |
| cost | Fixed resets plus underlying cursor/key release; counted separately from mandatory close cleanup. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0015

[Lines 122–136](../../../../../src/runtime/weighted_cursor.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Result emit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble declared ordered/repeated head slots and transfer one owning compressed row. |
| inputs / outputs | Selected visible assignment and final prefix weight to original-account Tuple plus multiplicity. |
| invariants | Check compiled shared-slot equalities; never multiply full subtree messages or hidden witness factors here. |
| ownership | Reserved ScalarView scratch borrows rows; native output copies actual values then transfers a funded immutable tuple owner. |
| failure | Output allocation/work failure closes cursor; prior outputs remain owning and valid. |
| cost | O(shared equalities + output fields/deep bytes); one output record regardless of its multiplicity. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0016

[Lines 137–148](../../../../../src/runtime/weighted_cursor.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<Result> advance()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run iterative visible nested-loop traversal until one complete assignment or termination. |
| inputs / outputs | Current frames/position/resume and cached answer flag to Result or null. |
| invariants | No recursion. Resume starts at last step; exhausted steps close before moving backward. Constant true/false use unit/zero empty tuples. |
| ownership | Only active Data owner/grant/reader and frame state are used. |
| failure | All throwing discovery/output work is handled by the one next boundary. |
| cost | Work follows actual visible bucket advances; hidden witnesses and a result relation are never materialized. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0017

[Lines 149–166](../../../../../src/runtime/weighted_cursor.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<Result> next()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a compressed result stream under its original grant, retaining phase diagnostics. |
| inputs / outputs | Active next rebinds retained lease; row updates max-result work, null records termination, failure records failed/last work. |
| invariants | Cancelled/exhausted next returns null without spending work; failed next rejects. Committed query state is never mutated. |
| ownership | Success keeps reader until terminal null/cancel; failure releases it before propagating the original typed error. |
| failure | One catch closes the read operation and rethrows; there is no translation/fallback layer. |
| cost | Cumulative operation accounting and actual traversal/output work; no per-call grant refill or output history. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0018

[Lines 167–168](../../../../../src/runtime/weighted_cursor.cpp#L167); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L167-L168:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct WeightedRuntime::ResultCursor::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct WeightedRuntime::ResultCursor::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct WeightedRuntime::ResultCursor::Data\` at its lexical source position in src/runtime/weighted_cursor.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct WeightedRuntime::ResultCursor::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0019

[Lines 169–176](../../../../../src/runtime/weighted_cursor.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WeightedRuntime::results(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a committed reader only after complete cursor preparation succeeds. |
| inputs / outputs | Cursor options to move-only ResultCursor for current sequence/binding/output layout. |
| invariants | Reject a private writer and reader-count overflow before admission; multiple committed readers are allowed. |
| ownership | Allocate Data/scratch/grant in original account, then increment reader count and mark the token leased. |
| failure | Failed construction publishes no reader; returning the prepared token is a nonthrowing owner move. |
| cost | One funded cursor owner and original grant, O(C*) frames plus O(ordered head width, including repetitions) row-view scratch; no query-state mirror or result scan. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0020

[Lines 177–177](../../../../../src/runtime/weighted_cursor.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WeightedRuntime::ResultCursor::ResultCursor(resource::
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a fully prepared published reader. |
| inputs / outputs | Accounted unique Data moves into the public cursor token. |
| invariants | The factory already incremented its one reader count. |
| ownership | Sole Data owner moves; it retains the original query owner/lease. |
| failure | Noexcept token construction. |
| cost | O(1), no allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0021

[Lines 178–180](../../../../../src/runtime/weighted_cursor.cpp#L178); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L178-L180:sha256:382c5942ff93d38d760e876e7ade93c2a107d7fd863f6012cb72b4502e45baf2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/weighted_cursor.cpp; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0022

[Lines 181–183](../../../../../src/runtime/weighted_cursor.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WeightedRuntime::ResultCursor::Data& WeightedRuntime::ResultCursor::data()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow this cursor private state after validating token presence. |
| inputs / outputs | A non-moved token returns Data, including closed metadata. |
| invariants | Terminal state is handled by Data::next; mere inspection remains valid after close. |
| ownership | Borrowed reference with cursor-token lifetime. |
| failure | Moved-from token raises invalid_cursor. |
| cost | O(1), allocation-free success. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0023

[Lines 184–184](../../../../../src/runtime/weighted_cursor.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool WeightedRuntime::ResultCursor::active()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether a cursor still holds a published reader. |
| inputs / outputs | Returns true only with Data in active state. |
| invariants | Moved-from, exhausted, cancelled and failed tokens are inactive. |
| ownership | Inline state checks; no owner retention. |
| failure | Noexcept, including moved-from access. |
| cost | O(1). |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0024

[Lines 185–185](../../../../../src/runtime/weighted_cursor.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CursorState WeightedRuntime::ResultCursor::state()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect active/exhausted/cancelled/failed state. |
| inputs / outputs | Copies Data status. |
| invariants | Metadata remains inspectable after close; no mutable runtime lease is required then. |
| ownership | Scalars are copied; references borrow this cursor Data and must not outlive the token. |
| failure | Moved-from access raises invalid_cursor. |
| cost | O(1), no storage traversal or success-path allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0025

[Lines 186–186](../../../../../src/runtime/weighted_cursor.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t WeightedRuntime::ResultCursor::sequence()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the cursor committed snapshot sequence. |
| inputs / outputs | Copies sequence captured before reader publication. |
| invariants | Metadata remains inspectable after close; no mutable runtime lease is required then. |
| ownership | Scalars are copied; references borrow this cursor Data and must not outlive the token. |
| failure | Moved-from access raises invalid_cursor. |
| cost | O(1), no storage traversal or success-path allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0026

[Lines 187–187](../../../../../src/runtime/weighted_cursor.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t WeightedRuntime::ResultCursor::owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the original query owner identity. |
| inputs / outputs | Copies owner ID captured at startup. |
| invariants | Metadata remains inspectable after close; no mutable runtime lease is required then. |
| ownership | Scalars are copied; references borrow this cursor Data and must not outlive the token. |
| failure | Moved-from access raises invalid_cursor. |
| cost | O(1), no storage traversal or success-path allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0027

[Lines 188–188](../../../../../src/runtime/weighted_cursor.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Binding& WeightedRuntime::ResultCursor::binding()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the cursor weighted semantic identity. |
| inputs / outputs | Returns its retained Binding by const lvalue reference. |
| invariants | Metadata remains inspectable after close; no mutable runtime lease is required then. |
| ownership | Scalars are copied; references borrow this cursor Data and must not outlive the token. |
| failure | Moved-from access raises invalid_cursor. |
| cost | O(1), no storage traversal or success-path allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0028

[Lines 189–189](../../../../../src/runtime/weighted_cursor.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::TupleLayout& WeightedRuntime::ResultCursor::layout()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the declared ordered output layout. |
| inputs / outputs | Returns its retained layout by const lvalue reference, including repeated head slots. |
| invariants | Metadata remains inspectable after close; no mutable runtime lease is required then. |
| ownership | Scalars are copied; references borrow this cursor Data and must not outlive the token. |
| failure | Moved-from access raises invalid_cursor. |
| cost | O(1), no storage traversal or success-path allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0029

[Lines 190–190](../../../../../src/runtime/weighted_cursor.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CursorMetrics& WeightedRuntime::ResultCursor::metrics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow cumulative and phase cursor diagnostics. |
| inputs / outputs | Returns inline Data metrics by const lvalue reference; values can change on next/close. |
| invariants | Metadata remains inspectable after close; no mutable runtime lease is required then. |
| ownership | Scalars are copied; references borrow this cursor Data and must not outlive the token. |
| failure | Moved-from access raises invalid_cursor. |
| cost | O(1), no storage traversal or success-path allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0030

[Lines 191–191](../../../../../src/runtime/weighted_cursor.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<Result> WeightedRuntime::ResultCursor::next()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fetch the next compressed owning result through the single failure boundary. |
| inputs / outputs | Returns one positive tuple/multiplicity or terminal nullopt; output order is unspecified. |
| invariants | The last successful result still retains the reader. Exhausted/cancelled calls return nullopt; failed calls raise invalid_cursor. |
| ownership | Returned Tuple owns its original-account payload independently of frames/runtime lifetime. |
| failure | Moved-from token rejects access; active read/output failure closes borrowed state and preserves the original exception. |
| cost | Only underlying traversal/output work under the cumulative budget and original grant; no wrapper history or grant refill. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0031

[Lines 192–192](../../../../../src/runtime/weighted_cursor.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void WeightedRuntime::ResultCursor::cancel()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End an active reader early without allocating or throwing. |
| inputs / outputs | Active token closes as cancelled; moved-from or terminal tokens are no-ops. |
| invariants | Previously returned owning rows remain valid and other cursors keep their own reader leases. |
| ownership | Releases mutable owner/grant after destroying borrowed frames; retains inspectable immutable metadata. |
| failure | Noexcept, nonallocating close. |
| cost | O(all C* frames), including unopened frames, plus underlying key/cursor/runtime release. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0032

[Lines 193–193](../../../../../src/runtime/weighted_cursor.cpp#L193); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L193-L193:sha256:024a31d07f0690bcfeef2cd00cf111a56223bd48741eae7b548b6bc9143d9111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in src/runtime/weighted_cursor.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
