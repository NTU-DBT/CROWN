# `src/planner/residual_reconstruct.cpp` — block usage map

[Source](../../../../../src/planner/residual_reconstruct.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Reconstruct and check candidate trees, retaining the exact-repair boundary for counterexamples.

Snapshot SHA-256: `b4e7ffda266db425d0bbe66ba5f335e5c76bfcdf47b96b03fa4aa947a5bb09b9`. 591 lines partitioned into 37 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [residual](../../../subsystem_contracts.md#residual). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/planner/residual_reconstruct.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 11–14](../../../../../src/planner/residual_reconstruct.cpp#L11) | Callable definition: void incrementable(std::uint64_t value) | calls max, Limited · [reviewed contract](#b0002) |
| [B0003 · 15–44](../../../../../src/planner/residual_reconstruct.cpp#L15) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // These coroutines share only the P06 suspension mechanism. Candidate construction · [reviewed contract](#b0003) |
| [B0004 · 45–50](../../../../../src/planner/residual_reconstruct.cpp#L45) | Callable definition: Impl(std::shared_ptr&lt;const cd::BindingData&gt; b, std::shared_ptr&lt;const ResidualTraceRecord&gt; t, std::shared_ptr&lt;ConstructionBudget&gt; … | calls binding, std::move, trace, budget · [reviewed contract](#b0004) |
| [B0005 · 51–51](../../../../../src/planner/residual_reconstruct.cpp#L51) | Callable definition: ~Impl() | calls cancel · [reviewed contract](#b0005) |
| [B0006 · 52–52](../../../../../src/planner/residual_reconstruct.cpp#L52) | Explanatory comments or spacing. |  |
| [B0007 · 53–55](../../../../../src/planner/residual_reconstruct.cpp#L53) | Callable definition: template&lt;class F&gt; auto op(F f, std::size_t extra = 0) noexcept | calls cp::operation, std::move; returns cp::operation(std::move(f), engine.depth + extra) · [reviewed contract](#b0007) |
| [B0008 · 56–61](../../../../../src/planner/residual_reconstruct.cpp#L56) | Callable definition: template&lt;class F&gt; cp::Task make_task(F create) | calls prepare, create, commit; returns value · [reviewed contract](#b0008) |
| [B0009 · 62–69](../../../../../src/planner/residual_reconstruct.cpp#L62) | Callable definition: cd::UnitContext child_context() const noexcept | calls ; returns value · [reviewed contract](#b0009) |
| [B0010 · 70–73](../../../../../src/planner/residual_reconstruct.cpp#L70) | Callable definition: void child_depth(std::size_t requested) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 74–80](../../../../../src/planner/residual_reconstruct.cpp#L74) | Callable definition: std::size_t depth() const noexcept | calls empty, current_depth, std::max; returns 0; engine.depth + child · [reviewed contract](#b0011) |
| [B0012 · 81–87](../../../../../src/planner/residual_reconstruct.cpp#L81) | Explanatory comments or spacing. | source comment (unverified): // One node shell, scope member or edge per transition. Claims are deliberately · [reviewed contract](#b0012) |
| [B0013 · 88–126](../../../../../src/planner/residual_reconstruct.cpp#L88) | Callable definition: cp::Task copy_tree(const FreeConnexTree* source, unsigned mode) | calls op, prepare, std::move, commit; growth insert, make_shared, push_back; 3 loop sites; source comment (unverified): // One node shell, scope member or edge per transition. Claims are deliberately · [reviewed contract](#b0013) |
| [B0014 · 127–130](../../../../../src/planner/residual_reconstruct.cpp#L127) | Explanatory comments or spacing. | source comment (unverified): // This exact proof belongs to view-&gt;query only. Prefix infeasibility requests · [reviewed contract](#b0014) |
| [B0015 · 131–193](../../../../../src/planner/residual_reconstruct.cpp#L131) | Callable definition: cp::Task solve(bool seed) | calls op, prepare, incrementable, ExactSearch::create; returns copy_tree(&exact_upper-&gt;tree(), 1); growth emplace; 1 loop sites; source comment (unverified): // This exact proof belongs to view-&gt;query only. Prefix infeasibility requests · [reviewed contract](#b0015) |
| [B0016 · 194–198](../../../../../src/planner/residual_reconstruct.cpp#L194) | Explanatory comments or spacing. | source comment (unverified): // A partial proposal needs an original-to-local tree copy and full owned · [reviewed contract](#b0016) |
| [B0017 · 199–252](../../../../../src/planner/residual_reconstruct.cpp#L199) | Callable definition: cp::Task validate(bool full) | calls op, make_task, copy_tree, get; returns copy_tree(draft.get(), 2); growth make_shared, make_unique; 1 loop sites; source comment (unverified): // A partial proposal needs an original-to-local tree copy and full owned · [reviewed contract](#b0017) |
| [B0018 · 253–253](../../../../../src/planner/residual_reconstruct.cpp#L253) | Explanatory comments or spacing. |  |
| [B0019 · 254–294](../../../../../src/planner/residual_reconstruct.cpp#L254) | Callable definition: cp::Task make_view(std::size_t ear) | calls op, prepare, std::move, commit; growth make_shared, make_unique, push_back; 2 loop sites · [reviewed contract](#b0019) |
| [B0020 · 295–299](../../../../../src/planner/residual_reconstruct.cpp#L295) | Explanatory comments or spacing. | source comment (unverified): // Local proposal family from Refactor.md Section 5.3: alternate placements · [reviewed contract](#b0020) |
| [B0021 · 300–406](../../../../../src/planner/residual_reconstruct.cpp#L300) | Callable definition: cp::Task attempt(std::size_t ear, std::size_t target, unsigned rule) | calls op, contains, make_task, copy_tree; returns copy_tree(current.get(), 0); validate(false); growth insert, push_back; 6 loop sites; source comment (unverified): // Local proposal family from Refactor.md Section 5.3: alternate placements · [reviewed contract](#b0021) |
| [B0022 · 407–411](../../../../../src/planner/residual_reconstruct.cpp#L407) | Explanatory comments or spacing. | source comment (unverified): // Greedy first-valid restoration is incomplete. Scan the original atom list · [reviewed contract](#b0022) |
| [B0023 · 412–491](../../../../../src/planner/residual_reconstruct.cpp#L412) | Callable definition: cp::Task restore(std::size_t ear, std::size_t anchor) | calls op, clear, contains, prepare; returns make_view(ear); attempt(ear, *preferred, 0); growth insert, push_back; 7 loop sites; source comment (unverified): // Greedy first-valid restoration is incomplete. Scan the original atom list · [reviewed contract](#b0023) |
| [B0024 · 492–492](../../../../../src/planner/residual_reconstruct.cpp#L492) | Explanatory comments or spacing. |  |
| [B0025 · 493–552](../../../../../src/planner/residual_reconstruct.cpp#L493) | Callable definition: cp::Task run() | calls op, prepare, insert, commit; returns solve(true); restore(deletions\[d - 1\].occurrence, deletions\[d - 1\].anchor); growth insert; 4 loop sites; source comment (unverified): // No induced checked handle escapes. Re-check the fully restored tree using · [reviewed contract](#b0025) |
| [B0026 · 553–554](../../../../../src/planner/residual_reconstruct.cpp#L553) | Closes surrounding scope/type. |  · [reviewed contract](#b0026) |
| [B0027 · 555–557](../../../../../src/planner/residual_reconstruct.cpp#L555) | Callable definition: ReconstructionMachine::ReconstructionMachine(std::shared_ptr&lt;const cd::BindingData&gt; binding, std::shared_ptr&lt;const ResidualTraceR… | calls data_, std::move; growth make_unique · [reviewed contract](#b0027) |
| [B0028 · 558–560](../../../../../src/planner/residual_reconstruct.cpp#L558) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0028) |
| [B0029 · 561–577](../../../../../src/planner/residual_reconstruct.cpp#L561) | Callable definition: Step ReconstructionMachine::step(const cd::UnitContext& context) | calls empty, permits, make_task, run; returns {Event::complete}; {Event::stopped, ResidualStopReason::depth_limit, StopReason::none, 1} · [reviewed contract](#b0029) |
| [B0030 · 578–578](../../../../../src/planner/residual_reconstruct.cpp#L578) | Callable definition: ResidualPhase ReconstructionMachine::phase() const noexcept | calls ; returns data_-&gt;phase_value · [reviewed contract](#b0030) |
| [B0031 · 579–579](../../../../../src/planner/residual_reconstruct.cpp#L579) | Callable definition: const ResidualStatistics& ReconstructionMachine::statistics() const noexcept | calls ; returns data_-&gt;stats · [reviewed contract](#b0031) |
| [B0032 · 580–580](../../../../../src/planner/residual_reconstruct.cpp#L580) | Callable definition: std::size_t ReconstructionMachine::current_depth() const noexcept | calls depth; returns data_-&gt;depth() · [reviewed contract](#b0032) |
| [B0033 · 581–581](../../../../../src/planner/residual_reconstruct.cpp#L581) | Callable definition: std::shared_ptr&lt;const cd::CheckedUpper&gt; ReconstructionMachine::checked_upper() const noexcept | calls ; returns data_-&gt;upper · [reviewed contract](#b0033) |
| [B0034 · 582–582](../../../../../src/planner/residual_reconstruct.cpp#L582) | Callable definition: ResidualOrigin ReconstructionMachine::origin() const noexcept | calls ; returns data_-&gt;origin_value · [reviewed contract](#b0034) |
| [B0035 · 583–585](../../../../../src/planner/residual_reconstruct.cpp#L583) | Callable definition: SearchProgress ReconstructionMachine::exact_progress() const noexcept | calls progress; returns data_-&gt;exact ? data_-&gt;exact-&gt;progress() : SearchProgress{} · [reviewed contract](#b0035) |
| [B0036 · 586–590](../../../../../src/planner/residual_reconstruct.cpp#L586) | Callable definition: LimitChange ReconstructionMachine::raise_exact_limits(ContinuationLimits limits) noexcept | calls progress, raise_limits; returns data_-&gt;exact-&gt;raise_limits(limits); LimitChange::applied · [reviewed contract](#b0036) |
| [B0037 · 591–591](../../../../../src/planner/residual_reconstruct.cpp#L591) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::residual_detail · [reviewed contract](#b0037) |

## B0001

[Lines 1–10](../../../../../src/planner/residual_reconstruct.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:ca941e868ffe23648758b277ce270c295f2f1965a72d0cb58b2d554626155195
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "residual_machine.hpp", #include "producer_cursor.hpp", #include &lt;algorithm&gt;, #include &lt;stdexcept&gt;, #include &lt;utility&gt; available to src/planner/residual_reconstruct.cpp; open crown::planner::residual_detail and anonymous helper namespace. In this span, bind cp = cd::producer_private. |
| inputs / outputs | Includes supply declarations; the listed namespace aliases bind names, and any listed constexpr bounds are constant-initialized metadata. These declarations do not run a planner search or validate a query. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | Namespace aliases own no runtime object. Any constexpr bounds in this span are fixed scalar metadata; no query owner, mutable counter or allocation grant is created by them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Preprocessing, name lookup and compile-time constant evaluation; constexpr bounds require no dynamic initialization and can occupy fixed constant storage when used. Included definitions retain their own call/construction costs. |
| Design | [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0002

[Lines 11–14](../../../../../src/planner/residual_reconstruct.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void incrementable(std::uint64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight a reconstruction statistic before associated publication changes. |
| inputs / outputs | uint64 value; returns unless already maximum. |
| invariants | Callers increment only after preparation/allocation succeeds; no counter wraps. |
| ownership | No ownership or mutation in the helper. |
| failure | Throws Limited(counter_overflow), terminalized by facade. |
| cost | Constant-time comparison. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0003

[Lines 15–44](../../../../../src/planner/residual_reconstruct.cpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReconstructionMachine::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain reverse-restoration execution, original-ID private trees and all owned child workers. |
| inputs / outputs | Binding/replayed trace/budget, engine/main/context/result, restored IDs/variables, maps/parents, exact/view/validator owners and final CheckedUpper. |
| invariants | Private current/draft trees are not authority; exact proofs remain induced-query scoped. upper is published only after final P02 with the original binding owner. |
| ownership | Shares immutable sources/budget; uniquely owns workers and tasks; aliasing terminal view retains the trace; tree pointer lifetimes span every copy task. |
| failure | Saved operations isolate allocations; expected stops preserve state, malformed internal mappings trigger terminal facade failure. Destructor cancels frames before fields expire. |
| cost | Retains multiple whole-tree variants, view maps, validator scratch and latest prefix exact owner; repeated attempts/admissions can dominate reduction cost. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0004

[Lines 45–50](../../../../../src/planner/residual_reconstruct.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Impl(std::shared_ptr<const cd::BindingData> b,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize inert reconstruction ownership and empty-body scheduling mode. |
| inputs / outputs | Moves binding, replayed trace and construction budget; sets engine administrative_only for empty body. |
| invariants | No seed, restoration or validation runs during construction. |
| ownership | Retains source/trace/budget shared owners for all child operations. |
| failure | Pointer moves and empty-body test do not throw; enclosing shell allocation may. |
| cost | Constant shell work. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0005

[Lines 51–51](../../../../../src/planner/residual_reconstruct.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~Impl() { engine.cancel(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy active restoration task chains before their referenced workers/state. |
| inputs / outputs | Engine cancellation from Impl destructor. |
| invariants | Leaf-first detach avoids recursive active coroutine teardown. |
| ownership | Cancels live Task frames; child exact/view/validator owners are released by subsequent member destruction. |
| failure | Noexcept under current captures and member destructors; no diagnostics allocated. |
| cost | O(active frame chain) plus local cleanup outside advance accounting. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0007

[Lines 53–55](../../../../../src/planner/residual_reconstruct.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class F> auto op(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a saved reconstruction operation tagged with its intended logical nesting. |
| inputs / outputs | Callable and optional extra depth; returns generic producer Operation. |
| invariants | Current callers capture only nonallocating pointer/scalar/reference state. Requested depth is engine.depth+extra and empty-body administrative mode may ignore it. |
| ownership | Awaitable lives in the caller coroutine frame until engine executes it outside resume. |
| failure | Declared noexcept; requires the actual closure move to be nonthrowing. Callable execution may throw for facade handling. |
| cost | Constant closure/depth setup for current captures. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0008

[Lines 56–61](../../../../../src/planner/residual_reconstruct.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class F> cp::Task make_task(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Account child coroutine-frame construction before publishing its Task. |
| inputs / outputs | Factory callable creates Task; one logical record committed after success. |
| invariants | Potentially allocating create executes outside resume through op, or directly in initial step; a failed frame allocation does not advance the parent. |
| ownership | Returned Task owns the new frame and is moved into the saved parent owner. |
| failure | Limited/bad_alloc propagate before commit; current factories perform only coroutine creation. |
| cost | One frame allocation and constant bookkeeping; frame size follows that coroutine locals. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0009

[Lines 62–69](../../../../../src/planner/residual_reconstruct.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cd::UnitContext child_context()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate the outer residual depth ceiling into remaining child-worker depth. |
| inputs / outputs | Copies context then subtracts active reconstruction engine depth, clamped at zero. |
| invariants | Delegated exact uses its own ContinuationLimits; this context applies to induced-view/P02 children. |
| ownership | Fixed optional value copy; does not borrow after return. |
| failure | Noexcept; no allocation. |
| cost | Constant arithmetic. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0010

[Lines 70–73](../../../../../src/planner/residual_reconstruct.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void child_depth(std::size_t requested) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lift a blocked child depth into the residual owner coordinate. |
| inputs / outputs | Requested child depth becomes stopped/depth_limit result with engine.depth added. |
| invariants | No semantic action is committed by reporting the stop; parent task remains at the child stepping loop. |
| ownership | Stores fixed Step data in pimpl. |
| failure | Noexcept; represents a resumable depth ceiling stop. |
| cost | Constant arithmetic/assignment. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0011

[Lines 74–80](../../../../../src/planner/residual_reconstruct.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::size_t depth() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report reconstruction coroutine nesting plus active view/P02 depth. |
| inputs / outputs | Zero for empty original body; otherwise engine.depth plus max active validator/view depth. |
| invariants | Only one logical child contributes at a time. Delegated exact frames are excluded here and available through exact_progress. |
| ownership | Scalar read from owned workers. |
| failure | Noexcept; child getters allocate nothing. |
| cost | Constant number of worker queries. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0012

[Lines 81–87](../../../../../src/planner/residual_reconstruct.cpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L87:sha256:6f02bf5d2c3d4b8cfbae5855885bd44c31c6f07344489bfa6e9c7538f936b662
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for copy_tree: One node shell, scope member or edge per transition. Claims are deliberately omitted: P02 derives fresh claims for the new binding. mode 0 copies original IDs, mode 1 maps exact/local IDs to originals, mode 2 maps originals to local. source stays owned by current/draft/exact_upper until this child returns. Vector growth, set insertion and string widths remain container costs; the saved cursor counts logical node/scope/edge copies, not allocator bytes. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies copy_tree; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for copy_tree come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0013

[Lines 88–126](../../../../../src/planner/residual_reconstruct.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cp::Task copy_tree(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Incrementally copy a tree and optionally translate occurrence/variable IDs between original and current induced bindings. |
| inputs / outputs | Source pointer and mode 0/original, 1/local-to-original, 2/original-to-local; writes copied shared tree. |
| invariants | Preserves root, node kinds/topology and complete scopes while regenerating unique rN names. Drops claims so P02 derives fresh metrics/separators. Source owner remains alive through the whole child task. |
| ownership | Allocates a private owned tree, nodes, set members and child edges; borrows source and retained view maps during copying. |
| failure | Saved allocations retain source/cursor on failure. at()/optional.value() reject impossible internal mappings and become terminal internal_failure through facade. |
| cost | O(nodes+scope members+edges) saved logical operations with logarithmic set insertion. No node-vector reserve is present, so capacity reallocations/moves are extra container cost. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0014

[Lines 127–130](../../../../../src/planner/residual_reconstruct.cpp#L127); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L127-L130:sha256:444821c7eb6667205608e2e4d50dae94424293aa00e5e970aafecc0075ffc90a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for solve: This exact proof belongs to view-&gt;query only. Prefix infeasibility requests full original search; prefix lower/optimum never becomes original authority. Each scheduled advance grants the retained exact owner one work unit. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies solve; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for solve come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0015

[Lines 131–193](../../../../../src/planner/residual_reconstruct.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cp::Task solve(bool seed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own and finish exact search for the current induced seed or restored-prefix repair. |
| inputs / outputs | Current ResidualView and exact ceilings; successful checked upper is copied to original IDs in current; exact_ok records feasibility. |
| invariants | Nonstalled seed must have native height 0/1 as appropriate. Prefix infeasibility sets exact_ok=false for original fallback; prefix lower proof never leaves reconstruction as original authority. |
| ownership | ExactSearch owns copied catalog/query and independent proof; exact_upper retains checked tree while copy_tree reads it. Replacing prior exact owner releases its state. |
| failure | Delegated resumable stops retain owner/cursor and exact reason; counter overflow is terminal. Unexpected inner outcomes throw logic_error for facade containment. |
| cost | One exact work unit per scheduled solve step; admission copies/validates whole catalog and induced query outside per-cell content charges. Exact search/replay may be exponential; prefix tree copy is linear in tree content. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0016

[Lines 194–198](../../../../../src/planner/residual_reconstruct.cpp#L194); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L194-L198:sha256:d7d96bc60d026a2a2a0e3ae96f3110e447748e2df0fad939a70a3257682dc4bc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for validate: A partial proposal needs an original-to-local tree copy and full owned induced catalog/query admission on each attempt. Those copies and P02 scratch are real variable-width costs outside residual record/cell caps. Only full validation shares the original binding and can populate upper. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies validate; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for validate come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0017

[Lines 199–252](../../../../../src/planner/residual_reconstruct.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cp::Task validate(bool full)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently P02-check one proposal against its restored query or the complete original binding. |
| inputs / outputs | Private draft plus full flag; validation_ok set on success, final full checked authority stored in upper. |
| invariants | Partial proposals are mapped to local IDs and admitted with an owned induced binding. Full check shares the exact original BindingData; only that CheckedUpper can be exported. |
| ownership | Owns temporary mapped tree, validation binding and ValidationMachine across suspension; resets child scratch after result while final upper retains checked tree/report/binding. |
| failure | Allocation/depth failures preserve pending worker. Invalid draft increments rejection count and remains private; budget exhaustion before rejection cleanup is resumable. |
| cost | Each partial attempt copies the whole tree and entire catalog/query for admission, then scans P02 obligations. Validator scratch and admission copies are outside residual record/cell caps; active call time includes them. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0019

[Lines 254–294](../../../../../src/planner/residual_reconstruct.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cp::Task make_view(std::size_t ear)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the next restored query from all already restored occurrences plus this ear. |
| inputs / outputs | Original ear index; publishes view after InducedViewMachine completes. |
| invariants | Members are ascending original IDs because the method scans the full original atom vector; no old query is edited or admitted by a stale head. |
| ownership | Owns a shared member vector and child machine, then shares completed view and releases the child shell. |
| failure | Saved member/view allocations and child depth stops retain exact retry position; unexpected events throw logic_error. |
| cost | Scans every original occurrence per restoration, then builds original-sized maps and selected query content. Lookup in restored set is logarithmic. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0020

[Lines 295–299](../../../../../src/planner/residual_reconstruct.cpp#L295); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L295-L299:sha256:ab5aeb05c8ae5d80a3ec978619ffb340f7b3a9e0b1f8dc86dece69e3f5f4c4b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for attempt: Local proposal family from Refactor.md Section 5.3: alternate placements and generalized forks repair specific failures of naive reattachment. They are not P2 Appendix B completeness/height claims. P02 independently checks restored-head reachability and every structural rule before commit. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies attempt; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for attempt come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0021

[Lines 300–406](../../../../../src/planner/residual_reconstruct.cpp#L300); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cp::Task attempt(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Propose one native attachment, guarded generalized leaf, or generalized fork and accept it only after P02. |
| inputs / outputs | Original ear, current target node and rule 0/1/2; on successful validation replaces current and records last-step origin. |
| invariants | Shared ear scope must fit target. Generalized leaf requires parent scope inside ear. Fork scope is shared, with old generalized parent contained in it. Full restored-head/connect/guard/above checks remain independent P02 obligations; proposal family is incomplete. |
| ownership | Copies current into private draft; rejected drafts never alter current. New native/fork nodes own complete scope/edges; validator owns mapped copies during checking. |
| failure | Incompatible proposals return without a draft. Saved allocation/limit failures are retryable; only a valid independent report commits current/provenance/graft count. |
| cost | Scans shared/parent scopes; compatible attempt copies the whole current tree, appends scope/edges, maps/copies again and admits a validator. Fork parent-edge replacement scans that parent children. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md](../../../../../Refactor.md), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0022

[Lines 407–411](../../../../../src/planner/residual_reconstruct.cpp#L407); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L407-L411:sha256:2d250a49c62247694fa5dc8fdee16c694c4d3f533553be3fb64f291e67f2f16a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for restore: Greedy first-valid restoration is incomplete. Scan the original atom list to build the enlarged head/query, try recorded/other placements, then use an owned complete prefix repair. Each compatible draft can copy/check the entire tree; exhaustion alone never means original infeasibility. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies restore; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for restore come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0023

[Lines 412–491](../../../../../src/planner/residual_reconstruct.cpp#L412); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cp::Task restore(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore one deleted occurrence using greedy checked placements, then exact prefix repair if all fail. |
| inputs / outputs | Ear and recorded anchor from reverse deletion traversal; updates restored occurrence/variable sets after a valid enlarged tree exists. |
| invariants | Preferred recorded anchor is tried first, then remaining native placements, generalized leaves and forks. First valid choice ends this step and can exclude future solutions; exhausted family uses complete repair. Infeasible prefix never directly certifies original infeasibility. |
| ownership | Retains old current until a proposal/repair succeeds; owns new induced view, shared-scope and parents scratch across attempts. |
| failure | Depth/allocation/content stops preserve the pending operation. Failed exact prefix returns without restoration commit so run requests full original search. |
| cost | Per restoration scans original atom membership, all current nodes/edges and up to O(tree nodes) placements per rule. Each compatible placement can incur whole-tree copies and full P02/admission costs. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md](../../../../../Refactor.md), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0025

[Lines 493–552](../../../../../src/planner/residual_reconstruct.cpp#L493); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cp::Task run()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed the terminal induced query, restore every deletion in reverse order and P02-check the final original tree. |
| inputs / outputs | Replayed trace and original binding; finishes with checked_upper or need_original_exact. |
| invariants | Reverse layer/deletion order restores supporting anchors first. Terminal/prefix exact authority stays induced-scoped. Final tree uses original IDs and the same original binding owner; failure requests full original exact fallback. |
| ownership | Aliasing shared_ptr to terminal_view retains the entire trace; restored sets, current trees and child tasks remain owned until finished/destruction. |
| failure | Unsuccessful seed/repair and invalid final P02 produce need_original_exact. Missing/mismatched final upper owner throws logic_error for terminal containment. |
| cost | Visits every deleted occurrence once but restoration may generate many whole-tree drafts. Final copy/check duplicates tree data; all allocations execute in saved operations. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0026

[Lines 553–554](../../../../../src/planner/residual_reconstruct.cpp#L553); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L553-L554:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0027

[Lines 555–557](../../../../../src/planner/residual_reconstruct.cpp#L555); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReconstructionMachine::ReconstructionMachine(std::shared_ptr<const cd::BindingData>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate a retained inert reconstruction pimpl. |
| inputs / outputs | Binding, verified-shape trace and shared budget ownership in. |
| invariants | Facade independently replays the trace before this constructor is called. No exact search runs here. |
| ownership | Unique Impl retains shared input/trace/budget lifetimes. |
| failure | Shell allocation may throw before facade stage publication. |
| cost | One initial shell allocation; no input scans. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0028

[Lines 558–560](../../../../../src/planner/residual_reconstruct.cpp#L558); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReconstructionMachine::~ReconstructionMachine() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement unique reconstruction ownership teardown and moves. |
| inputs / outputs | Default destructor, move construction and move assignment. |
| invariants | Moved-from machine has null pimpl and is not reused by the facade. Published final shared uppers retain their data. |
| ownership | Moves unique Impl; replaced/destroyed state cancels active frames before child workers/trees die. |
| failure | Noexcept moves and standard nonthrowing destructors. |
| cost | Move construction constant; replacement/destruction cleanup can traverse large exact/tree state outside grants. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0029

[Lines 561–577](../../../../../src/planner/residual_reconstruct.cpp#L561); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Step ReconstructionMachine::step(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one retained restoration operation or lazily create its main frame. |
| inputs / outputs | UnitContext in; current Step, depth-stopped or generic complete after finished. |
| invariants | Resets ephemeral result each active call; child exact/view/P02 loops retain position. The first finish returns checked_upper/need_original_exact; subsequent calls return complete, so facade must handle the first event. |
| ownership | Owns main Task/Engine and retained context in pimpl; no replacement binding is accepted. |
| failure | Root admission/depth block is explicit; saved-operation allocation/Limited propagate for facade retry. |
| cost | Constant scheduling plus one saved operation, which can admit variable-width child bindings. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0030

[Lines 578–578](../../../../../src/planner/residual_reconstruct.cpp#L578); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualPhase ReconstructionMachine::phase()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current reconstruction phase for progress. |
| inputs / outputs | ResidualPhase scalar. |
| invariants | Seed/repair/restore/validation phases describe activity, not exact original authority. |
| ownership | Borrowed pimpl read only. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant-time. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0031

[Lines 579–579](../../../../../src/planner/residual_reconstruct.cpp#L579); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ResidualStatistics& ReconstructionMachine::statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose local restoration/proposal/repair/admission diagnostics. |
| inputs / outputs | Const reference to stats. |
| invariants | Last origin and cumulative counters differ; a later native restoration does not erase earlier graft count. |
| ownership | Reference borrows pimpl and expires with it. |
| failure | Noexcept; no aggregation/allocation here. |
| cost | Constant access. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0032

[Lines 580–580](../../../../../src/planner/residual_reconstruct.cpp#L580); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ReconstructionMachine::current_depth()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return combined reconstruction/view/P02 logical frame depth. |
| inputs / outputs | Delegates to Impl::depth(). |
| invariants | Excludes delegated exact owner depth, which has its own ceiling and progress. |
| ownership | Scalar snapshot from owned state. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant-time. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0033

[Lines 581–581](../../../../../src/planner/residual_reconstruct.cpp#L581); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const cd::CheckedUpper> ReconstructionMachine::checked_upper()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share only final original-binding P02 authority. |
| inputs / outputs | Null until validate(true) succeeds; otherwise immutable CheckedUpper. |
| invariants | No induced proposal CheckedUpper is published through this accessor. Facade rechecks binding pointer/report/tree before CandidateData creation. |
| ownership | Returned shared owner retains original binding, complete tree and report independently of machine. |
| failure | Noexcept; null is unavailable status. |
| cost | Constant shared-pointer copy; no tree copy. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0034

[Lines 582–582](../../../../../src/planner/residual_reconstruct.cpp#L582); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualOrigin ReconstructionMachine::origin()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return last successful reconstruction operation provenance. |
| inputs / outputs | ResidualOrigin by value. |
| invariants | Failed proposals do not change it; seed/repair/native/generalized/graft provenance is separate from proof scope. |
| ownership | Scalar copy. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant-time. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0035

[Lines 583–585](../../../../../src/planner/residual_reconstruct.cpp#L583); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchProgress ReconstructionMachine::exact_progress()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose latest seed/prefix exact-search diagnostics without exporting its authority. |
| inputs / outputs | ExactSearch.progress() or default SearchProgress before admission. |
| invariants | This progress remains induced-query scoped until facade separately sets exact_scope_original on original-search admission. |
| ownership | Fixed-size value copy; exact owner stays private. |
| failure | Noexcept; no exact owner yields default diagnostics. |
| cost | Constant-time. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0036

[Lines 586–590](../../../../../src/planner/residual_reconstruct.cpp#L586); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LimitChange ReconstructionMachine::raise_exact_limits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward a monotone extension to the currently unfinished prefix exact owner. |
| inputs / outputs | ContinuationLimits in; delegated result or applied when no unfinished exact exists. |
| invariants | Outer facade validates and updates shared budget limits after this succeeds; later prefix admissions read the updated budget. |
| ownership | Mutates one owned exact continuation under exclusive access. |
| failure | Noexcept; completed/absent inner owner needs no update; inner rejection propagates. |
| cost | Constant checks plus one ExactSearch.raise_limits call. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0037

[Lines 591–591](../../../../../src/planner/residual_reconstruct.cpp#L591); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L591-L591:sha256:10243363061d9249809d0b3342036a00aa4668303f7fcba1d86fd8f5d445a835
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::residual_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |
