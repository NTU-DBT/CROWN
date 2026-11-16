# `src/planner/residual_reduce.cpp` — block usage map

[Source](../../../../../src/planner/residual_reduce.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Build residual reduction traces from query scopes and output structure.

Snapshot SHA-256: `10f30e933157000878cba1611c674b4b0069dbe07c369da173ffdf316d783733`. 253 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [residual](../../../subsystem_contracts.md#residual). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../src/planner/residual_reduce.cpp#L1) | Imports dependencies; declares namespace scope; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 24–25](../../../../../src/planner/residual_reduce.cpp#L24) | Callable definition: Impl(std::shared_ptr&lt;const cd::BindingData&gt; b, std::shared_ptr&lt;ConstructionBudget&gt; c) : binding(std::move(b)), budget(std::move(c… | calls binding, std::move, budget · [reviewed contract](#b0002) |
| [B0003 · 26–26](../../../../../src/planner/residual_reduce.cpp#L26) | Callable definition: ~Impl() | calls cancel · [reviewed contract](#b0003) |
| [B0004 · 27–29](../../../../../src/planner/residual_reduce.cpp#L27) | Callable definition: template&lt;class T, class U&gt; void append(std::vector&lt;T&gt;& out, U&& value, std::uint64_t records = 0) | calls prepare, push_back, commit; growth push_back · [reviewed contract](#b0004) |
| [B0005 · 30–33](../../../../../src/planner/residual_reduce.cpp#L30) | Callable definition: void insert(VariableSet& out, VariableId v) | calls contains, prepare, commit; growth insert · [reviewed contract](#b0005) |
| [B0006 · 34–37](../../../../../src/planner/residual_reduce.cpp#L34) | Callable definition: static void increment(std::uint64_t& n) | calls max, Limited · [reviewed contract](#b0006) |
| [B0007 · 38–42](../../../../../src/planner/residual_reduce.cpp#L38) | Explanatory comments or spacing. | source comment (unverified): // P2 arXiv:2603.14754v1, Section 2.1.4, Definition 2.9 and Algorithm 1 · [reviewed contract](#b0007) |
| [B0008 · 43–229](../../../../../src/planner/residual_reduce.cpp#L43) | Callable definition: pp::Task run() | calls RED_OP, pp::operation, empty, prepare; growth insert, make_shared, make_unique, push_back, reserve; 36 loop sites; source comment (unverified): // P2 arXiv:2603.14754v1, Section 2.1.4, Definition 2.9 and Algorithm 1 · [reviewed contract](#b0008) |
| [B0009 · 230–230](../../../../../src/planner/residual_reduce.cpp#L230) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 231–232](../../../../../src/planner/residual_reduce.cpp#L231) | Callable definition: ReductionMachine::ReductionMachine(std::shared_ptr&lt;const cd::BindingData&gt; b, std::shared_ptr&lt;ConstructionBudget&gt; c) : data_(std::… | calls data_, std::move; growth make_unique · [reviewed contract](#b0010) |
| [B0011 · 233–235](../../../../../src/planner/residual_reduce.cpp#L233) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 236–245](../../../../../src/planner/residual_reduce.cpp#L236) | Callable definition: Step ReductionMachine::step(const cd::UnitContext& ctx) | calls permits, current_depth, prepare, run; returns {Event::complete}; {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, current_dept… · [reviewed contract](#b0012) |
| [B0013 · 246–246](../../../../../src/planner/residual_reduce.cpp#L246) | Callable definition: ResidualPhase ReductionMachine::phase() const noexcept | calls ; returns data_-&gt;phase · [reviewed contract](#b0013) |
| [B0014 · 247–247](../../../../../src/planner/residual_reduce.cpp#L247) | Callable definition: const ResidualStatistics& ReductionMachine::statistics() const noexcept | calls ; returns data_-&gt;stats · [reviewed contract](#b0014) |
| [B0015 · 248–251](../../../../../src/planner/residual_reduce.cpp#L248) | Callable definition: std::size_t ReductionMachine::current_depth() const noexcept | calls empty, view, current_depth; returns 0; 1 + (data_-&gt;induced && !data_-&gt;induced-&gt;view() ? data_-&gt;induced-&gt;current_depth() : 0) · [reviewed contract](#b0015) |
| [B0016 · 252–252](../../../../../src/planner/residual_reduce.cpp#L252) | Callable definition: std::shared_ptr&lt;const ResidualTraceRecord&gt; ReductionMachine::trace_record() const noexcept | calls ; returns data_-&gt;result · [reviewed contract](#b0016) |
| [B0017 · 253–253](../../../../../src/planner/residual_reduce.cpp#L253) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::residual_detail · [reviewed contract](#b0017) |

## B0001

[Lines 1–23](../../../../../src/planner/residual_reduce.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReductionMachine::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain reduction cursors, liveness, current layer/ear drafts and immutable-result owners. |
| inputs / outputs | Shared original binding/budget, live/count vectors, original head, draft trace, child induced view, engine/task/context and diagnostics. |
| invariants | Original occurrence IDs stay fixed; pending deletion pair belongs to frozen ear/anchor vectors whose iteration order is ascending. |
| ownership | Owns all scratch/drafts and shared result; child has shared terminal member ownership. Impl destructor cancels engine before member teardown. |
| failure | All allocating semantic changes occur in saved operations; private field storage alone establishes no checked trace authority. |
| cost | Storage accumulates original scopes and frozen layers plus O(original variables+atoms) scratch and child-view duplication. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp) |

## B0002

[Lines 24–25](../../../../../src/planner/residual_reduce.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Impl(std::shared_ptr<const cd::BindingData> b, std::shared_ptr<ConstructionBudget> c)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an inert reduction shell with retained source/budget. |
| inputs / outputs | Moves two shared owners into fields. |
| invariants | No scopes, hierarchy tests or reduction work run at construction. |
| ownership | Retains immutable binding and mutable exclusive shared budget. |
| failure | Constructor only performs nonthrowing shared-pointer moves; enclosing make_unique allocation may throw. |
| cost | Constant shell work; scratch is lazy. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0003

[Lines 26–26](../../../../../src/planner/residual_reduce.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~Impl() { engine.cancel(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cancel active reduction frames before dependent scratch is destroyed. |
| inputs / outputs | Destructor calls Engine::cancel. |
| invariants | Leaf-first cancellation detaches Task owners, preventing recursive active-frame unwind or double destroy. |
| ownership | Releases coroutine frames; later member destructors release scratch/result owners. |
| failure | Noexcept under nonthrowing Task/container destructors; no diagnostic allocation. |
| cost | O(active frames) plus their owned-local teardown; outside grants. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0004

[Lines 27–29](../../../../../src/planner/residual_reduce.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class T, class U> void append(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one logical vector cell after charging its selected record cost. |
| inputs / outputs | Vector, forwarded value and optional records; updates vector and budget. |
| invariants | prepare precedes push_back; commit follows success. Call-site value moves must preserve retry semantics. |
| ownership | Vector owns the appended value; budget charges construction cumulatively. |
| failure | Limited/bad_alloc propagate; failed push leaves no logical commit. Standard-container capacity may change privately. |
| cost | One vector append, amortized constant absent relocation/value width; records/cells checks are constant. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0005

[Lines 30–33](../../../../../src/planner/residual_reduce.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void insert(VariableSet& out, VariableId v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert each variable-set member once and charge one logical cell. |
| inputs / outputs | Set and VariableId; mutates only if absent. |
| invariants | Membership check avoids duplicate charge for repeated atom terms/head positions. |
| ownership | Set owns value; no reference retained. |
| failure | prepare or set allocation may throw before commit. |
| cost | Logarithmic contains+insert in set size, one node allocation on insertion. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0006

[Lines 34–37](../../../../../src/planner/residual_reduce.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static void increment(std::uint64_t& n)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Increment local reduction diagnostics without wrap. |
| inputs / outputs | Counter by reference. |
| invariants | Exhaustion is checked before increment and produces no changed counter. |
| ownership | Mutates scalar only. |
| failure | Throws Limited(counter_overflow). |
| cost | Constant-time. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0007

[Lines 38–42](../../../../../src/planner/residual_reduce.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L42:sha256:ca6ecce4a1d24a849a8bea29ac4e8ad039f902c4a800b9d6d8763eb641877a65
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for run: P2 arXiv:2603.14754v1, Section 2.1.4, Definition 2.9 and Algorithm 1 supply the frozen-ear recipe; ascending-ID tie-breaking and resumable record publication are local choices. Round counts do not prove height. Actual work includes variable-pair/member tests, all anchor pairs and repeated frozen-support scans, plus an independent terminal-view copy. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies run; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for run come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md), [P2 arXiv:2603.14754v1 §2.1.4, Definition 2.9 and Algorithm 1 (frozen-ear reduction recipe only)](https://arxiv.org/pdf/2603.14754v1) |

## B0008

[Lines 43–229](../../../../../src/planner/residual_reduce.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  pp::Task run()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a deterministic frozen-ear trace and terminal dense query through saved operations. |
| inputs / outputs | Uses original binding and budget; publishes result only after scopes, rounds, terminal maps and query copy are complete. |
| invariants | Scopes deduplicate term variables; q-hierarchy precedes every round. All eligible supports freeze before smallest-live-pair deletion, whose append precedes liveness mutation. Stalled reduction is diagnostic. |
| ownership | Owns partial layer/ear/live/count state across yields; delegates view construction then copies its logical cells into the trace. Result remains private until facade replay. |
| failure | Allocations and limits occur in saved closures. Failure before deletion append preserves pair/liveness; no round or terminal fact becomes an original lower certificate. |
| cost | For a round with k variables/m members, hierarchy scans O(k²m) membership checks; eligibility scans all ear-anchor/shared variables; repeated pair rescans can reach cubic in m. Trace/view copies allocate incrementally; reserve/capacity/string costs remain variable-width. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [Refactor.md](../../../../../Refactor.md), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [P2 arXiv:2603.14754v1 §2.1.4, Definition 2.9, Definition 2.10 and Algorithm 1](https://arxiv.org/pdf/2603.14754v1) |

## B0009

[Lines 230–230](../../../../../src/planner/residual_reduce.cpp#L230); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L230-L230:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0010

[Lines 231–232](../../../../../src/planner/residual_reduce.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReductionMachine::ReductionMachine(std::shared_ptr<const cd::BindingData>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate an inert reduction pimpl. |
| inputs / outputs | Owned binding/budget into unique Impl. |
| invariants | No reduction is executed until step starts the coroutine. |
| ownership | Unique implementation retains shared immutable binding and shared budget. |
| failure | make_unique bad_alloc propagates before caller stage publication. |
| cost | One shell allocation with constant initial state. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0011

[Lines 233–235](../../../../../src/planner/residual_reduce.cpp#L233); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReductionMachine::~ReductionMachine() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide teardown and move ownership for the reduction pimpl. |
| inputs / outputs | Default destructor, move construction and move assignment. |
| invariants | Methods on a moved-from machine require valid data_; the facade never uses the old object. |
| ownership | Moves unique Impl; target replacement releases its prior saved state. |
| failure | Noexcept moves; destructor invokes cancelling Impl teardown. |
| cost | Move construction constant; final/replaced cleanup traverses owned data outside grants. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0012

[Lines 236–245](../../../../../src/planner/residual_reduce.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Step ReductionMachine::step(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one saved reduction operation or lazily admit its root frame. |
| inputs / outputs | UnitContext in; complete/advanced/depth-stopped Step. |
| invariants | Completed result is stable. Checks current depth before start/step; induced child receives reduced depth ceiling. Root allocation commits before started becomes durable. |
| ownership | Retains task and engine in pimpl for all resumptions. |
| failure | Depth stops return without semantic progress; allocations/Limited propagate with pending closure intact. |
| cost | Constant scheduling plus at most one saved operation, which may reserve/copy variable-width data. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0013

[Lines 246–246](../../../../../src/planner/residual_reduce.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualPhase ReductionMachine::phase()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the current producer subphase. |
| inputs / outputs | ResidualPhase by value. |
| invariants | phase is diagnostic and does not mark independent trace verification. |
| ownership | Reads pimpl scalar. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant-time. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0014

[Lines 247–247](../../../../../src/planner/residual_reduce.cpp#L247); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ResidualStatistics& ReductionMachine::statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose reduction activity counters for facade aggregation. |
| inputs / outputs | Const reference to local statistics. |
| invariants | These are producer counts only; caller merges them with reconstruction/own counts. |
| ownership | Borrowed from pimpl, invalid after its destruction/move replacement. |
| failure | Noexcept; non-moved-from machine required. |
| cost | Constant-time no-copy access. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0015

[Lines 248–251](../../../../../src/planner/residual_reduce.cpp#L248); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ReductionMachine::current_depth()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report residual reduction frame plus any active induced-view depth. |
| inputs / outputs | Returns zero for complete/empty body, otherwise one plus child depth when unfinished. |
| invariants | Logical depth is separate from native tree height and delegated exact depth. |
| ownership | Scalar snapshot; borrows child during call. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant-time. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0016

[Lines 252–252](../../../../../src/planner/residual_reduce.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const ResidualTraceRecord> ReductionMachine::trace_record()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the fully produced trace only after run publication. |
| inputs / outputs | Null until result is set; shared const record afterwards. |
| invariants | A produced record still needs independent TraceReplayMachine before public verified trace publication. |
| ownership | Returned shared owner can outlive the reduction machine. |
| failure | Noexcept; copying shared_ptr allocates nothing. |
| cost | Constant-time owner copy. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0017

[Lines 253–253](../../../../../src/planner/residual_reduce.cpp#L253); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L253:sha256:10243363061d9249809d0b3342036a00aa4668303f7fcba1d86fd8f5d445a835
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::residual_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |
