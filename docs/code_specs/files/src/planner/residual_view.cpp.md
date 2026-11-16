# `src/planner/residual_view.cpp` — block usage map

[Source](../../../../../src/planner/residual_view.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate and replay residual-reduction/reconstruction candidates as a structural aid to the exact planner.

Snapshot SHA-256: `438936dc08524cdcfa532c492370467657045fd60c4d430d7fdd39794ddaac43`. 101 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [residual](../../../subsystem_contracts.md#residual). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../src/planner/residual_view.cpp#L1) | Imports dependencies; declares namespace scope; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Private callers provide valid, sorted, unique original occurrence IDs and · [reviewed contract](#b0001) |
| [B0002 · 19–21](../../../../../src/planner/residual_view.cpp#L19) | Callable definition: Impl(std::shared_ptr&lt;const cd::BindingData&gt; b, std::shared_ptr&lt;const std::vector&lt;std::size_t&gt;&gt; m, std::shared_ptr&lt;ConstructionBud… | calls binding, std::move, members, budget · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../src/planner/residual_view.cpp#L22) | Callable definition: ~Impl() | calls cancel · [reviewed contract](#b0003) |
| [B0004 · 23–27](../../../../../src/planner/residual_view.cpp#L23) | Callable definition: template&lt;class T, class U&gt; void append(std::vector&lt;T&gt;& out, U&& value, std::uint64_t records = 0) | calls prepare, push_back, commit; growth push_back · [reviewed contract](#b0004) |
| [B0005 · 28–82](../../../../../src/planner/residual_view.cpp#L28) | Callable definition: pp::Task run() | calls VIEW_OP, pp::operation, empty, prepare; growth emplace_back, make_shared, push_back, reserve; 8 loop sites · [reviewed contract](#b0005) |
| [B0006 · 83–83](../../../../../src/planner/residual_view.cpp#L83) | Closes surrounding scope/type. |  · [reviewed contract](#b0006) |
| [B0007 · 84–86](../../../../../src/planner/residual_view.cpp#L84) | Callable definition: InducedViewMachine::InducedViewMachine(std::shared_ptr&lt;const cd::BindingData&gt; b, std::shared_ptr&lt;const std::vector&lt;std::size_t&gt;&gt; … | calls data_, std::move; growth make_unique · [reviewed contract](#b0007) |
| [B0008 · 87–89](../../../../../src/planner/residual_view.cpp#L87) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 90–98](../../../../../src/planner/residual_view.cpp#L90) | Callable definition: Step InducedViewMachine::step(const cd::UnitContext& ctx) | calls permits, current_depth, prepare, run; returns {Event::complete}; {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, current_dept… · [reviewed contract](#b0009) |
| [B0010 · 99–99](../../../../../src/planner/residual_view.cpp#L99) | Callable definition: std::shared_ptr&lt;const ResidualView&gt; InducedViewMachine::view() const noexcept | calls ; returns data_-&gt;result · [reviewed contract](#b0010) |
| [B0011 · 100–100](../../../../../src/planner/residual_view.cpp#L100) | Callable definition: std::size_t InducedViewMachine::current_depth() const noexcept | calls empty; returns data_-&gt;result \|\| data_-&gt;members-&gt;empty() ? 0 : 1 · [reviewed contract](#b0011) |
| [B0012 · 101–101](../../../../../src/planner/residual_view.cpp#L101) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::residual_detail · [reviewed contract](#b0012) |

## B0001

[Lines 1–18](../../../../../src/planner/residual_view.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InducedViewMachine::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own active-variable flags, dense maps/query draft and its saved construction cursor. |
| inputs / outputs | Original binding, ordered original member owner, budget, draft/result, active byte vector, engine/task and started flag. |
| invariants | Members are trusted ascending unique valid occurrence IDs; result remains null until every mapping/query/head cell is complete. |
| ownership | Shared source/member/budget owners plus private draft and coroutine; result shares the frozen draft. |
| failure | Impl destructor cancels active frames before fields expire; invalid caller member indexes are outside this private API contract. |
| cost | O(original variables+atoms) map/flag scratch plus induced query content and shared input storage. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0002

[Lines 19–21](../../../../../src/planner/residual_view.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Impl(std::shared_ptr<const cd::BindingData> b,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain induced-view inputs in an inert shell. |
| inputs / outputs | Binding, ordered members and construction budget moved into fields. |
| invariants | Does not scan or validate the member vector here. |
| ownership | Shared owners ensure input/member lifetimes through all yields. |
| failure | Only pointer moves in body; outer make_unique allocation can throw. |
| cost | Constant initial shell cost. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp) |

## B0003

[Lines 22–22](../../../../../src/planner/residual_view.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~Impl() { engine.cancel(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach and destroy active view frames before their referenced state. |
| inputs / outputs | Engine cancellation during pimpl destruction. |
| invariants | Task owners are cleared leaf-first; subsequent Task destruction cannot destroy the same active frame twice. |
| ownership | Releases live coroutine ownership before input/draft fields. |
| failure | Nonthrowing cancellation and standard destruction. |
| cost | O(active frames) plus destroyed local payloads, outside grants. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0004

[Lines 23–27](../../../../../src/planner/residual_view.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class T, class U> void append(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one induced-query/map vector element after successful allocation. |
| inputs / outputs | Forwarded element and optional record charge; one cell committed. |
| invariants | prepare precedes push_back; failed allocation does not commit counters or skip the pending operation. |
| ownership | Destination vector owns moved/copied value. |
| failure | Limited/bad_alloc propagate for facade retry. |
| cost | Amortized vector append plus value copy width; capacity relocation and allocations are outside scalar transition claims. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0005

[Lines 28–82](../../../../../src/planner/residual_view.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  pp::Task run()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a dense induced binding preserving all selected original query content. |
| inputs / outputs | Reads selected occurrences, marks active variables, assigns maps, remaps terms and copies surviving head positions; publishes result last. |
| invariants | Dense variable order is ascending original ID; occurrence order follows trusted ascending members. Repeated output aliases/order, constants, ignored columns, tables/names/types and contradiction are preserved. |
| ownership | Private draft/maps own copies; source/member owners survive suspension. No catalog copy is stored in ResidualView. |
| failure | Saved allocating operations retain exact retry position. Dereference of inverse variable mapping relies on prior active-variable scan. |
| cost | Scans original V/N map dimensions, selected terms and original head, with allocations for query cells/strings. reserve can allocate full capacities; logical cell ceilings do not cap allocator bytes. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0006

[Lines 83–83](../../../../../src/planner/residual_view.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L83:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0007

[Lines 84–86](../../../../../src/planner/residual_view.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InducedViewMachine::InducedViewMachine(std::shared_ptr<const cd::BindingData>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the unique inert induced-view implementation. |
| inputs / outputs | Binding/member/budget shared owners in, pimpl owned by machine. |
| invariants | Actual query/map work starts lazily in step. |
| ownership | Unique Impl retains all shared input lifetimes. |
| failure | Shell allocation may throw before caller publication. |
| cost | One shell allocation, no input traversal. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0008

[Lines 87–89](../../../../../src/planner/residual_view.cpp#L87); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InducedViewMachine::~InducedViewMachine() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement unique view-machine teardown and moves. |
| inputs / outputs | Default destructor/move constructor/move assignment. |
| invariants | Move leaves source data_ null; callers use only destination. |
| ownership | Moves Impl; releasing a prior Impl cancels its frames and destroys scratch. |
| failure | Noexcept moves/destruction under standard member contracts. |
| cost | Move construction constant; cleanup is size-dependent and excluded from grant work. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0009

[Lines 90–98](../../../../../src/planner/residual_view.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Step InducedViewMachine::step(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start or advance the retained view constructor one saved operation. |
| inputs / outputs | UnitContext input; advanced/complete/depth-stopped Step. |
| invariants | Completed view remains stable. Nonempty input checks depth 1 before lazy frame admission; empty selected members use administrative depth zero. |
| ownership | Root Task/Engine stay owned for retry across calls. |
| failure | Reported depth stop or propagated Limited/bad_alloc retains pending operation. |
| cost | One root-frame allocation or saved operation; reserve and scalar/string copies can have variable-width cost. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0010

[Lines 99–99](../../../../../src/planner/residual_view.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const ResidualView> InducedViewMachine::view()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share only the completed dense query and maps. |
| inputs / outputs | Null before completion; shared const ResidualView afterwards. |
| invariants | Draft is never exposed while being mutated. |
| ownership | Returned owner keeps the view alive independently of the machine. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant-time shared-pointer copy; no content copy. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0011

[Lines 100–100](../../../../../src/planner/residual_view.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t InducedViewMachine::current_depth()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the single logical view frame when work is nonempty. |
| inputs / outputs | Zero if result exists or members empty, otherwise one. |
| invariants | This is administrative logical depth, never a CROWN native height. |
| ownership | Scalar read. |
| failure | Noexcept; valid pimpl/member owner required. |
| cost | Constant-time. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0012

[Lines 101–101](../../../../../src/planner/residual_view.cpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L101:sha256:10243363061d9249809d0b3342036a00aa4668303f7fcba1d86fd8f5d445a835
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::residual_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |
