# `src/planner/residual_trace.cpp` — block usage map

[Source](../../../../../src/planner/residual_trace.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Replay and validate each claimed reduction step against the source query.

Snapshot SHA-256: `524b000ebdf31a2f7d653a9a4a1ecc8c267e9297c1339c69f51bbe4e35031115`. 295 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [residual](../../../subsystem_contracts.md#residual). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../src/planner/residual_trace.cpp#L1) | Imports dependencies; declares namespace scope; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Independent replay uses original terms and its own scopes/incidences/pairs, · [reviewed contract](#b0001) |
| [B0002 · 24–24](../../../../../src/planner/residual_trace.cpp#L24) | Type/record definition: struct Pair |  · [reviewed contract](#b0002) |
| [B0003 · 25–26](../../../../../src/planner/residual_trace.cpp#L25) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 27–28](../../../../../src/planner/residual_trace.cpp#L27) | Callable definition: Impl(std::shared_ptr&lt;const cd::BindingData&gt; b, std::shared_ptr&lt;const ResidualTraceRecord&gt; c, std::shared_ptr&lt;ConstructionBudget&gt; … | calls binding, std::move, claim, budget · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../src/planner/residual_trace.cpp#L29) | Callable definition: ~Impl() | calls cancel · [reviewed contract](#b0005) |
| [B0006 · 30–30](../../../../../src/planner/residual_trace.cpp#L30) | Callable definition: auto tick() | calls cursor::operation; returns cursor::operation(\[\] {}) · [reviewed contract](#b0006) |
| [B0007 · 31–31](../../../../../src/planner/residual_trace.cpp#L31) | Callable definition: void fail(ResidualTraceRule rule) noexcept | calls  · [reviewed contract](#b0007) |
| [B0008 · 32–34](../../../../../src/planner/residual_trace.cpp#L32) | Callable definition: template&lt;class T&gt; void append(std::vector&lt;T&gt;& out, const T& value, std::uint64_t cells = 1) | calls prepare, push_back, commit; growth push_back · [reviewed contract](#b0008) |
| [B0009 · 35–38](../../../../../src/planner/residual_trace.cpp#L35) | Callable definition: void insert(VariableSet& out, VariableId value) | calls contains, prepare, commit; growth insert · [reviewed contract](#b0009) |
| [B0010 · 39–47](../../../../../src/planner/residual_trace.cpp#L39) | Callable definition: template&lt;class A, class B&gt; cursor::Task equal(const A& a, const B& b, ResidualTraceRule rule) | calls tick, size, fail, begin; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 48–50](../../../../../src/planner/residual_trace.cpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Rebuild incidence independently, scanning all ordered variable pairs and · [reviewed contract](#b0011) |
| [B0012 · 51–75](../../../../../src/planner/residual_trace.cpp#L51) | Callable definition: cursor::Task derive() | calls clear, size, cursor::operation, append; growth insert; 7 loop sites; source comment (unverified): // Rebuild incidence independently, scanning all ordered variable pairs and · [reviewed contract](#b0012) |
| [B0013 · 76–129](../../../../../src/planner/residual_trace.cpp#L76) | Callable definition: cursor::Task view() | calls cursor::operation, prepare, equal, commit; 6 loop sites · [reviewed contract](#b0013) |
| [B0014 · 130–231](../../../../../src/planner/residual_trace.cpp#L130) | Callable definition: cursor::Task run() | calls tick, fail, size, cursor::operation; growth insert; 13 loop sites · [reviewed contract](#b0014) |
| [B0015 · 232–232](../../../../../src/planner/residual_trace.cpp#L232) | Closes surrounding scope/type. |  · [reviewed contract](#b0015) |
| [B0016 · 233–234](../../../../../src/planner/residual_trace.cpp#L233) | Callable definition: TraceReplayMachine::TraceReplayMachine(std::shared_ptr&lt;const cd::BindingData&gt; b, std::shared_ptr&lt;const ResidualTraceRecord&gt; c, st… | calls data_, std::move; growth make_unique · [reviewed contract](#b0016) |
| [B0017 · 235–235](../../../../../src/planner/residual_trace.cpp#L235) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |
| [B0018 · 236–252](../../../../../src/planner/residual_trace.cpp#L236) | Callable definition: Step TraceReplayMachine::step(const cd::UnitContext& context) | calls max, Limited, empty, permits; returns {d.result.valid ? Event::complete : Event::invalid_trace}; {Event::stopped, ResidualStopReason::dep… · [reviewed contract](#b0018) |
| [B0019 · 253–253](../../../../../src/planner/residual_trace.cpp#L253) | Callable definition: std::size_t TraceReplayMachine::current_depth() const noexcept | calls empty; returns data_-&gt;binding-&gt;query.atoms.empty() \|\| data_-&gt;finished ? 0 : data_-&gt;engine.depth · [reviewed contract](#b0019) |
| [B0020 · 254–254](../../../../../src/planner/residual_trace.cpp#L254) | Callable definition: ResidualTraceReport TraceReplayMachine::report() const noexcept | calls ; returns data_-&gt;result · [reviewed contract](#b0020) |
| [B0021 · 255–261](../../../../../src/planner/residual_trace.cpp#L255) | declares namespace scope. | source comment (unverified): // namespace crown::planner::residual_detail · [reviewed contract](#b0021) |
| [B0022 · 262–294](../../../../../src/planner/residual_trace.cpp#L262) | Callable definition: ResidualTraceReport verify_residual_trace(const Catalog& catalog, const Query& query, const ResidualTraceRecord& trace, const Sea… | calls count, std::invalid_argument, validate, reset; returns report; machine-&gt;report(); growth make_shared, make_unique; 1 loop sites; source comment (unverified): // Blocking diagnostic adapter: source validation and full binding/claim copies · [reviewed contract](#b0022) |
| [B0023 · 295–295](../../../../../src/planner/residual_trace.cpp#L295) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner · [reviewed contract](#b0023) |

## B0001

[Lines 1–23](../../../../../src/planner/residual_trace.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TraceReplayMachine::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an independent trace-consistency computation with source/claim ownership. |
| inputs / outputs | Shared original binding, claimed record and budget; root/engine, report, derived scopes/head/incidence/members/liveness/pairs. |
| invariants | Claim is never edited. Every semantic fact is derived from original terms and compared before use; producer algorithms and view helpers are not called. |
| ownership | Owns independent scratch and saved coroutine frames; shared binding/claim remain alive. |
| failure | Allocation/limit failures preserve the pending closure; destructor cancels frames before scratch destruction. |
| cost | Independent reconstruction duplicates source scope/member data and can materialize O(m²) eligible pairs per round. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp) |

## B0002

[Lines 24–24](../../../../../src/planner/residual_trace.cpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct Pair {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one independently derived eligible frozen ear-anchor relation. |
| inputs / outputs | Original ear/anchor IDs and exact condition bit mask. |
| invariants | Pairs are appended in ascending ear then anchor order, determining the first-live-pair deletion order. |
| ownership | Owns three scalars; pair vector remains stable during the deletion scan. |
| failure | No validation/exception in aggregate; run() derives values from validated source indexes. |
| cost | Constant storage per pair; vector can contain quadratically many pairs. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp) |

## B0003

[Lines 25–26](../../../../../src/planner/residual_trace.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L26:sha256:4cbe12b9a8ef3fba09766cfa6210f03f25d6cf05f4790d21e2f026103aa97331
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain pairs, hierarchical in TraceReplayMachine::Impl across its lifetime. |
| inputs / outputs | These are stored fields for TraceReplayMachine::Impl, not callable parameters or results; constructors and later methods set or consume them. |
| invariants | The fields preserve the named machine or owner state between calls; counters, cursors, and stored claims remain data until adjacent methods update or validate them. |
| ownership | containers and strings own their elements or bytes. |
| failure | The declarations add no exception path by themselves. Constructing owner/container members or growing them later can fail through the surrounding object-creation or update path. |
| cost | Adds fixed per-instance storage for the listed values and owner/container handles; container payloads allocate or grow only as the machine prepares state. |
| Design | [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0004

[Lines 27–28](../../../../../src/planner/residual_trace.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Impl(std::shared_ptr<const cd::BindingData> b,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an inert independent replay owner. |
| inputs / outputs | Moves immutable binding/claim and shared construction budget. |
| invariants | No trace checks run during shell construction. |
| ownership | Retains shared inputs, allowing caller/local shells to release their copies. |
| failure | Pointer moves do not throw; enclosing allocation may. |
| cost | Constant shell initialization. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0005

[Lines 29–29](../../../../../src/planner/residual_trace.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~Impl() { engine.cancel(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cancel live replay frames before derived state and claim owners expire. |
| inputs / outputs | Destructor invokes generic engine cancellation. |
| invariants | Active frames are detached leaf-first, avoiding recursive owner-chain unwind. |
| ownership | Releases coroutine frames; remaining members destroy afterwards. |
| failure | Noexcept standard destruction; no error conversion. |
| cost | O(active frames) plus local cleanup outside grants. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0006

[Lines 30–30](../../../../../src/planner/residual_trace.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  auto tick() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Suspend before an allocation-free replay comparison or cursor action. |
| inputs / outputs | Returns an empty saved Operation closure. |
| invariants | No semantic producer helper is called; this is scheduling only. Default operation depth is zero, while nested task admissions enforce depth. |
| ownership | Awaitable is stored in its owning coroutine frame. |
| failure | Construction/empty closure execution allocates nothing. |
| cost | Constant scheduler operation. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0007

[Lines 31–31](../../../../../src/planner/residual_trace.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void fail(ResidualTraceRule rule) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the first detected trace obligation failure for immediate coroutine return. |
| inputs / outputs | Stores the supplied rule in report. |
| invariants | Callers co_return after a failing comparison, so subsequent checks do not overwrite a completed invalid claim. valid remains false. |
| ownership | Mutates one scalar in the private report. |
| failure | Noexcept; no diagnostic string allocation. |
| cost | Constant-time. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0008

[Lines 32–34](../../../../../src/planner/residual_trace.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class T> void append(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append independent replay scratch with explicit record/cell accounting. |
| inputs / outputs | Vector and const value, optional cells default one; charges one record plus chosen cells. |
| invariants | prepare precedes push_back; commit follows success. Unlike producer append, every scratch append here has record charge one. |
| ownership | Copies value into owned scratch; does not retain a borrowed value reference after success. |
| failure | Limited/bad_alloc escape before accounting commit and retain retry position. |
| cost | Amortized vector append plus element-copy/capacity cost; budget checks constant. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0009

[Lines 35–38](../../../../../src/planner/residual_trace.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void insert(VariableSet& out, VariableId value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deduplicate independently derived variables and charge only new set members. |
| inputs / outputs | VariableSet and VariableId; inserts when absent. |
| invariants | Replay charges one logical record and one cell per inserted member; repeated term/head positions do not add incidence. |
| ownership | Set owns numeric value. |
| failure | Limited/bad_alloc propagate before commit. |
| cost | Logarithmic contains/insert plus set-node allocation. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0010

[Lines 39–47](../../../../../src/planner/residual_trace.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class A, class B> cursor::Task equal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two ordered scalar-ID collections incrementally. |
| inputs / outputs | Collections and failure rule; sets report.rule on length/element mismatch. |
| invariants | All current instantiations compare primitive occurrence/variable IDs, one element per tick; equality alone never establishes tree/proof authority. |
| ownership | Coroutine borrows collections whose owning source/claim/scratch lives through the child task. |
| failure | Child-frame allocation is prepared by caller; ticks do not allocate. Mismatch returns normally with invalid diagnostic. |
| cost | One size comparison plus O(collection length) saved comparisons; frame storage is constant. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp) |

## B0011

[Lines 48–50](../../../../../src/planner/residual_trace.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L50:sha256:91c61ec7ccb41ffb84fbd93906627c679bd4e18a37daceef96cc16729ad791bb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for derive: Rebuild incidence independently, scanning all ordered variable pairs and all current members even after a hierarchy violation is known. Container clear/destruction is cleanup cost outside the scalar transition account. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies derive; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for derive come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0012

[Lines 51–75](../../../../../src/planner/residual_trace.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cursor::Task derive()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute current variable/head/unique sets and q-hierarchy from original scopes/current members. |
| inputs / outputs | Updates independent scratch counts/sets and hierarchical flag. |
| invariants | Counts are by occurrence scopes, not term multiplicity. Ordered variable pairs detect both laminar crossing and proper free-incidence containment. |
| ownership | Owns rebuilt vectors/sets; references use immutable scopes/member IDs. |
| failure | Allocating insert/append work is saved for retry. clear/destruction between yields is separate cleanup cost. |
| cost | Scans current scope incidences, original variable slots and all ordered variable pairs times members; no short-circuit after hierarchy failure. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [Refactor.md](../../../../../Refactor.md), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0013

[Lines 76–129](../../../../../src/planner/residual_trace.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cursor::Task view()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently check the claimed terminal dense mapping and query contents. |
| inputs / outputs | Compares both map directions, variables, atoms/term alternatives/constants and ordered surviving head aliases. |
| invariants | Sizes and exact maps validate before dereference; local IDs use ascending originals. Source table IDs/names/types/contradiction must match exactly. |
| ownership | Borrows immutable binding/claim and independent derived members/variables; child equal tasks retain parent-frame lifetime. |
| failure | First mismatch sets mapping/query rule; no checked view is constructed by this function. Allocations are only scheduled child-frame admission. |
| cost | Linear scans of original map sizes and terminal query contents; string/value comparisons are variable-width. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0014

[Lines 130–231](../../../../../src/planner/residual_trace.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  cursor::Task run()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay version, original scopes, every frozen layer, deletion maximality, terminal state and dense query independently. |
| inputs / outputs | Consumes owned source and claim; sets valid=true only after all checks succeed. |
| invariants | Derives all supports/bits; first live derived pair must match each deletion. Recomputes members/head/hierarchy between layers; no producer or reconstruction semantic helpers. |
| ownership | Maintains own liveness/pairs/scopes and child frames; claim remains immutable. |
| failure | Mismatch retains rule and diagnostic layer/occurrence/anchor then returns. Saved allocations preserve pending work on bad_alloc/Limited; invalid traces confer no authority. |
| cost | Rebuilds all-pairs eligibility and repeatedly scans pairs per deletion; hierarchy derivation scans ordered variable pairs. Cumulative scratch records/cells include rebuilding; clears/deallocation remain explicit excluded cleanup. |
| Design | [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0015

[Lines 232–232](../../../../../src/planner/residual_trace.cpp#L232); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L232-L232:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0016

[Lines 233–234](../../../../../src/planner/residual_trace.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TraceReplayMachine::TraceReplayMachine(std::shared_ptr<const cd::BindingData>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate an inert replay implementation retaining immutable source/claim. |
| inputs / outputs | Three shared owners become the unique pimpl inputs. |
| invariants | No validity flag is set at construction. |
| ownership | Machine owns Impl; shared owners retain original source, raw claim and shared cumulative budget. |
| failure | Shell allocation may throw before facade stage change. |
| cost | One shell allocation; no trace scan. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0017

[Lines 235–235](../../../../../src/planner/residual_trace.cpp#L235); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TraceReplayMachine::~TraceReplayMachine() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release replay implementation with explicit frame cancellation first. |
| inputs / outputs | Default unique-pimpl destructor. |
| invariants | Impl destructor detaches all active Task owners before nested members die. |
| ownership | Destroys private scratch while shared record/binding may survive elsewhere. |
| failure | Nonthrowing engine/container destruction. |
| cost | Size-dependent cleanup outside advance/search-limit accounting. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0018

[Lines 236–252](../../../../../src/planner/residual_trace.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Step TraceReplayMachine::step(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge one replay attempt and start or resume its saved verification operation. |
| inputs / outputs | UnitContext input; advanced, complete, invalid_trace or depth stop. |
| invariants | Finished report is stable. Work count checks overflow first and includes blocked nonempty-depth attempts. Empty body uses administrative depth zero. |
| ownership | Retains root Task/Engine and report in pimpl. |
| failure | Limited overflow propagates; root-frame/saved-operation allocations remain retryable. A depth block returns exact requested depth. |
| cost | Constant scheduling plus one saved operation; child comparisons/derivations distribute scans across steps. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0019

[Lines 253–253](../../../../../src/planner/residual_trace.cpp#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t TraceReplayMachine::current_depth()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report active replay coroutine nesting for the outer residual ledger. |
| inputs / outputs | Zero for empty body/finished, otherwise engine.depth. |
| invariants | Depth is the saved replay frame count, not reduction rounds or tree native height. |
| ownership | Scalar snapshot from owned engine. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant-time. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0020

[Lines 254–254](../../../../../src/planner/residual_trace.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualTraceReport TraceReplayMachine::report()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the current replay diagnostic without allocating. |
| inputs / outputs | ResidualTraceReport value, including current work/context/failure rule. |
| invariants | Only run completion can set valid; interim reports are incomplete data. |
| ownership | Self-contained scalar/optional copy. |
| failure | Noexcept; no content serialization or claim copy. |
| cost | Constant-time fixed-size copy. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0021

[Lines 255–261](../../../../../src/planner/residual_trace.cpp#L255); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L255-L261:sha256:298d5f3f7ffb291fff4b851d324c610c2fd5aea7de6dfafdf87deb7a0dadc6c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | close crown::planner::residual_detail and open crown::planner in src/planner/residual_trace.cpp. Attached note: Blocking diagnostic adapter: source validation and full binding/claim copies precede replay work/time limits. Resource return discards this private owner; callers needing retained search state use ResidualSearch. Invalid source validation errors propagate; allocation/limit failures return explicit reports. The note is documentation only. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0022

[Lines 262–294](../../../../../src/planner/residual_trace.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualTraceReport verify_residual_trace(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a blocking diagnostic replay adapter for caller-supplied untrusted trace data. |
| inputs / outputs | Catalog/Query/trace plus SearchLimits; returns valid, invalid or resource-limited report. |
| invariants | Validates source before owned copies; copied claim is replayed independently. Time/work checks apply after admission; success verifies reduction only and never constructs authoritative upper/minimum handles. |
| ownership | Owns copied full binding/claim, uncapped logical ConstructionBudget and private replay machine for this call. Returned report has no borrowed references. |
| failure | Negative time throws invalid_argument; invalid Catalog/Query validation may throw. bad_alloc/Limited become explicit resource reports; incomplete replay never returns valid=true. |
| cost | Whole Catalog/Query/trace admission copies and validation are outside replay grants; then loop performs saved steps until limit/completion. This blocking adapter does not retain a resumable owner after return. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp) |

## B0023

[Lines 295–295](../../../../../src/planner/residual_trace.cpp#L295); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L295-L295:sha256:4694e0f1e6f869fb33efbef9837cf0d20c8f194dc3c9f2b5be909714a0f5c690
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |
