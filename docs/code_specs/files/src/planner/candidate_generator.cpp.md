# `src/planner/candidate_generator.cpp` — block usage map

[Source](../../../../../src/planner/candidate_generator.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Enumerate candidate tree structures with an explicit generator frontier.

Snapshot SHA-256: `53497ef7083f9b9c84b87a0a1bbd88c9e4b31fabd7fd55372ef3be25e95843f9`. 350 lines partitioned into 39 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../src/planner/candidate_generator.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 16–18](../../../../../src/planner/candidate_generator.cpp#L16) | Callable definition: void prepare_increment(std::uint64_t value) | calls ContentStop · [reviewed contract](#b0002) |
| [B0003 · 19–22](../../../../../src/planner/candidate_generator.cpp#L19) | Callable definition: bool monotone(std::optional&lt;std::uint64_t&gt; old_limit, std::optional&lt;std::uint64_t&gt; new_limit) noexcept | calls ; returns old_limit ? (!new_limit \|\| *new_limit &gt;= *old_limit) : !new_limit · [reviewed contract](#b0003) |
| [B0004 · 23–24](../../../../../src/planner/candidate_generator.cpp#L23) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../src/planner/candidate_generator.cpp#L25) | Callable definition: ContentBudget::ContentBudget(ContentLimits limits) noexcept : limits_(limits) | calls limits_ · [reviewed contract](#b0005) |
| [B0006 · 26–28](../../../../../src/planner/candidate_generator.cpp#L26) | Explanatory comments or spacing. | source comment (unverified): // Preflight only. After allocation succeeds, commit the same charge without · [reviewed contract](#b0006) |
| [B0007 · 29–36](../../../../../src/planner/candidate_generator.cpp#L29) | Callable definition: void ContentBudget::prepare(std::uint64_t records, std::uint64_t cells) const | calls ContentStop; source comment (unverified): // Preflight only. After allocation succeeds, commit the same charge without · [reviewed contract](#b0007) |
| [B0008 · 37–40](../../../../../src/planner/candidate_generator.cpp#L37) | Callable definition: void ContentBudget::commit(std::uint64_t records, std::uint64_t cells) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 41–47](../../../../../src/planner/candidate_generator.cpp#L41) | Callable definition: bool ContentBudget::raise_limits(ContentLimits limits) noexcept | calls monotone; returns false; true · [reviewed contract](#b0009) |
| [B0010 · 48–48](../../../../../src/planner/candidate_generator.cpp#L48) | Callable definition: ContentLimits ContentBudget::limits() const noexcept | calls ; returns limits_ · [reviewed contract](#b0010) |
| [B0011 · 49–49](../../../../../src/planner/candidate_generator.cpp#L49) | Callable definition: std::uint64_t ContentBudget::records() const noexcept | calls ; returns records_ · [reviewed contract](#b0011) |
| [B0012 · 50–50](../../../../../src/planner/candidate_generator.cpp#L50) | Callable definition: std::uint64_t ContentBudget::cells() const noexcept | calls ; returns cells_ · [reviewed contract](#b0012) |
| [B0013 · 51–52](../../../../../src/planner/candidate_generator.cpp#L51) | declares types or opens a type body. |  · [reviewed contract](#b0013) |
| [B0014 · 53–53](../../../../../src/planner/candidate_generator.cpp#L53) | Type/record definition: struct NodeState |  · [reviewed contract](#b0014) |
| [B0015 · 54–55](../../../../../src/planner/candidate_generator.cpp#L54) | Explanatory comments or spacing. | source comment (unverified): // One generalized scope: native anchor plus ascending-variable inclusion · [reviewed contract](#b0015) |
| [B0016 · 56–56](../../../../../src/planner/candidate_generator.cpp#L56) | Type/record definition: struct ScopeDigit | source comment (unverified): // One generalized scope: native anchor plus ascending-variable inclusion · [reviewed contract](#b0016) |
| [B0017 · 57–57](../../../../../src/planner/candidate_generator.cpp#L57) | Type/record definition: struct Frame |  · [reviewed contract](#b0017) |
| [B0018 · 58–74](../../../../../src/planner/candidate_generator.cpp#L58) | declares values/defaults or compile-time conditions. | source comment (unverified): // Retained original IDs and dynamic cursors; no fixed-width subset masks. · [reviewed contract](#b0018) |
| [B0019 · 75–79](../../../../../src/planner/candidate_generator.cpp#L75) | Callable definition: Impl(std::shared_ptr&lt;const cd::BindingData&gt; input, std::size_t height, std::shared_ptr&lt;ContentBudget&gt; content) : binding(std::mov… | calls binding, std::move, target, budget · [reviewed contract](#b0019) |
| [B0020 · 80–80](../../../../../src/planner/candidate_generator.cpp#L80) | Callable definition: ~Impl() | calls cancel · [reviewed contract](#b0020) |
| [B0021 · 81–83](../../../../../src/planner/candidate_generator.cpp#L81) | Callable definition: std::size_t depth() const noexcept | calls size; returns !started \|\| finished \|\| was_cancelled ? 0 : 1 + stack.size() · [reviewed contract](#b0021) |
| [B0022 · 84–89](../../../../../src/planner/candidate_generator.cpp#L84) | Callable definition: template&lt;class T&gt; void append(std::vector&lt;T&gt;& out, T value, std::uint64_t records = 0) | calls size, max_size, ContentStop, prepare; growth push_back · [reviewed contract](#b0022) |
| [B0023 · 90–96](../../../../../src/planner/candidate_generator.cpp#L90) | Callable definition: void put_variable(VariableSet& out, VariableId variable) | calls contains, size, max_size, ContentStop; growth insert · [reviewed contract](#b0023) |
| [B0024 · 97–98](../../../../../src/planner/candidate_generator.cpp#L97) | Explanatory comments or spacing. | source comment (unverified): // Counter room first; shared ownership publication then cannot allocate. · [reviewed contract](#b0024) |
| [B0025 · 99–104](../../../../../src/planner/candidate_generator.cpp#L99) | Callable definition: void publish() | calls prepare_increment, reset; source comment (unverified): // Counter room first; shared ownership publication then cannot allocate. · [reviewed contract](#b0025) |
| [B0026 · 105–108](../../../../../src/planner/candidate_generator.cpp#L105) | Explanatory comments or spacing. | source comment (unverified): // Every root and non-self parent tuple is visited for g=0..m-1. The local · [reviewed contract](#b0026) |
| [B0027 · 109–285](../../../../../src/planner/candidate_generator.cpp#L109) | Callable definition: control::Task run() | calls GEN_AT, control::operation, GEN_OP, depth; growth make_shared, push_back; 27 loop sites; source comment (unverified): // Every root and non-self parent tuple is visited for g=0..m-1. The local · [reviewed contract](#b0027) |
| [B0028 · 286–287](../../../../../src/planner/candidate_generator.cpp#L286) | Closes surrounding scope/type. |  · [reviewed contract](#b0028) |
| [B0029 · 288–290](../../../../../src/planner/candidate_generator.cpp#L288) | Callable definition: NormalFormGenerator::NormalFormGenerator(std::shared_ptr&lt;const cd::BindingData&gt; binding, std::size_t height, std::shared_ptr&lt;Cont… | calls data_, std::move; growth make_unique · [reviewed contract](#b0029) |
| [B0030 · 291–297](../../../../../src/planner/candidate_generator.cpp#L291) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Ready drafts cannot be skipped by more grants. Control-frame admission and · [reviewed contract](#b0030) |
| [B0031 · 298–327](../../../../../src/planner/candidate_generator.cpp#L298) | Callable definition: Step NormalFormGenerator::step(const cd::UnitContext& context) | calls depth, permits, prepare_increment, prepare; returns {GeneratorEvent::draft_ready}; {GeneratorEvent::stopped}; source comment (unverified): // Ready drafts cannot be skipped by more grants. Control-frame admission and · [reviewed contract](#b0031) |
| [B0032 · 328–328](../../../../../src/planner/candidate_generator.cpp#L328) | Callable definition: std::shared_ptr&lt;const FreeConnexTree&gt; NormalFormGenerator::draft() const noexcept | calls ; returns data_-&gt;ready · [reviewed contract](#b0032) |
| [B0033 · 329–330](../../../../../src/planner/candidate_generator.cpp#L329) | Explanatory comments or spacing. | source comment (unverified): // Acknowledge only after provider validation/rejection/publication. Reset · [reviewed contract](#b0033) |
| [B0034 · 331–335](../../../../../src/planner/candidate_generator.cpp#L331) | Callable definition: void NormalFormGenerator::consume_draft() noexcept | calls reset; source comment (unverified): // Acknowledge only after provider validation/rejection/publication. Reset · [reviewed contract](#b0034) |
| [B0035 · 336–336](../../../../../src/planner/candidate_generator.cpp#L336) | Callable definition: const GeneratorStatistics& NormalFormGenerator::statistics() const noexcept | calls ; returns data_-&gt;stats · [reviewed contract](#b0035) |
| [B0036 · 337–337](../../../../../src/planner/candidate_generator.cpp#L337) | Callable definition: std::size_t NormalFormGenerator::current_depth() const noexcept | calls depth; returns data_-&gt;depth() · [reviewed contract](#b0036) |
| [B0037 · 338–338](../../../../../src/planner/candidate_generator.cpp#L338) | Callable definition: bool NormalFormGenerator::cancelled() const noexcept | calls ; returns data_-&gt;was_cancelled · [reviewed contract](#b0037) |
| [B0038 · 339–349](../../../../../src/planner/candidate_generator.cpp#L339) | Callable definition: void NormalFormGenerator::cancel() noexcept | calls cancel, reset, clear · [reviewed contract](#b0038) |
| [B0039 · 350–350](../../../../../src/planner/candidate_generator.cpp#L350) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::candidate_detail · [reviewed contract](#b0039) |

## B0001

[Lines 1–15](../../../../../src/planner/candidate_generator.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:f1db1bc10049831525800b56b08f8ed34b159932374fdb601c6a2fdaf1d8311a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "candidate_machine.hpp", #include "producer_cursor.hpp", #include &lt;algorithm&gt;, #include &lt;limits&gt;, #include &lt;stdexcept&gt;, #include &lt;utility&gt;, #include &lt;vector&gt; available to src/planner/candidate_generator.cpp; open crown::planner::candidate_detail and anonymous helper namespace. In this span, bind cd = continuation_detail, control = cd::producer_private. Define constexpr bounds counter_max, index_max. |
| inputs / outputs | Includes supply declarations; the listed namespace aliases bind names, and any listed constexpr bounds are constant-initialized metadata. These declarations do not run a planner search or validate a query. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | Namespace aliases own no runtime object. Any constexpr bounds in this span are fixed scalar metadata; no query owner, mutable counter or allocation grant is created by them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Preprocessing, name lookup and compile-time constant evaluation; constexpr bounds require no dynamic initialization and can occupy fixed constant storage when used. Included definitions retain their own call/construction costs. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0002

[Lines 16–18](../../../../../src/planner/candidate_generator.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_increment(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent a generator diagnostic increment from wrapping. |
| inputs / outputs | uint64 value checked against maximum. |
| invariants | Guard runs before related state publication. |
| ownership | Reads scalar only. |
| failure | Throws ContentStop(counter_overflow). |
| cost | Constant comparison. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp) |

## B0003

[Lines 19–22](../../../../../src/planner/candidate_generator.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool monotone(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check optional content-ceiling extension semantics. |
| inputs / outputs | Old/new optional uint64; Boolean. |
| invariants | Finite to larger/unbounded allowed; unbounded to finite rejected. |
| ownership | Borrows value copies; no mutation. |
| failure | Noexcept and allocation-free. |
| cost | Constant comparisons. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0004

[Lines 23–24](../../../../../src/planner/candidate_generator.cpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L24:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the lexical scope identified by the source span. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0005

[Lines 25–25](../../../../../src/planner/candidate_generator.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ContentBudget::ContentBudget(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize unconsumed content counters and copied limits. |
| inputs / outputs | ContentLimits into private fields. |
| invariants | Counters default zero; constructor does not charge work/storage. |
| ownership | Owns value limits only. |
| failure | Noexcept. |
| cost | Constant initialization. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp) |

## B0006

[Lines 26–28](../../../../../src/planner/candidate_generator.cpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L28:sha256:aacbcca5943009f8dbf31ada3c9f7af85648a2702e9c70824242f72566127020
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ContentBudget: Preflight only. After allocation succeeds, commit the same charge without intervening budget mutation. Counts are cumulative logical cells/records; failed allocations commit nothing and consumed/discarded content is not refunded. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ContentBudget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ContentBudget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0007

[Lines 29–36](../../../../../src/planner/candidate_generator.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ContentBudget::prepare(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight overflow and finite record/cell room before allocation. |
| inputs / outputs | Requested uint64 increments; no mutation. |
| invariants | Subtraction checks avoid unsigned overflow and underflow even when consumed totals already exceed a proposed bound. |
| ownership | Reads exclusive shared budget. |
| failure | Throws specific ContentStop for overflow, records or cells; leaves counters unchanged. |
| cost | Constant arithmetic. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp) |

## B0008

[Lines 37–40](../../../../../src/planner/candidate_generator.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ContentBudget::commit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit a successful matching logical charge. |
| inputs / outputs | Adds records/cells to consumed totals. |
| invariants | Caller must previously prepare same values without intervening budget mutation. No implicit allocation, recheck or refund. |
| ownership | Mutates two counters only. |
| failure | Noexcept unchecked addition is safe under precondition. |
| cost | Constant-time. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp) |

## B0009

[Lines 41–47](../../../../../src/planner/candidate_generator.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ContentBudget::raise_limits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extend content limits without resetting consumed construction. |
| inputs / outputs | New ContentLimits; Boolean success. |
| invariants | Rejects tightened or below-consumed limits before mutation. |
| ownership | Replaces scalar limit value; no worker restart. |
| failure | Noexcept false on invalid change. |
| cost | Constant checks. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0010

[Lines 48–48](../../../../../src/planner/candidate_generator.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ContentLimits ContentBudget::limits()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current content ceilings. |
| inputs / outputs | ContentLimits by value. |
| invariants | Limits reflect accepted raises, not actual allocator capacity. |
| ownership | Fixed optional copy. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp) |

## B0011

[Lines 49–49](../../../../../src/planner/candidate_generator.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t ContentBudget::records()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read cumulative logical record charges. |
| inputs / outputs | uint64 total by value. |
| invariants | Discarded/consumed content remains charged. |
| ownership | Scalar copy. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0012

[Lines 50–50](../../../../../src/planner/candidate_generator.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t ContentBudget::cells()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read cumulative logical cell charges. |
| inputs / outputs | uint64 total by value. |
| invariants | This is construction content, not allocator bytes or live cells. |
| ownership | Scalar copy. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0013

[Lines 51–52](../../../../../src/planner/candidate_generator.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L52:sha256:dab3bc72101807d528590e6d2b8341a6c2cca9b0da2d80a7e6881a1c5abc2bbc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin the definition of NormalFormGenerator::Impl in src/planner/candidate_generator.cpp; retained fields and operations are declared in the following spans. |
| inputs / outputs | This type opener has no callable inputs or outputs; it establishes the C++ type whose later members define state and operations. |
| invariants | The declaration establishes type identity and scope only; proof authority or runtime behavior comes from initialized state and methods. |
| ownership | The opener itself owns no runtime storage. Object layout and member lifetimes come from the following field declarations. |
| failure | Ill-formed or incomplete type definitions fail compilation; construction failures arise only when the completed type is instantiated. |
| cost | Compile-time parsing only at this span; runtime object size and construction cost are determined by its completed members. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0014

[Lines 53–53](../../../../../src/planner/candidate_generator.cpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct NodeState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one labeled topology parent digit and traversal scratch. |
| inputs / outputs | Parent/children numeric values and seen flag. |
| invariants | Root self-parent is never an edge; other parent digits exclude self. Counters/flags reset each topology. |
| ownership | Value in owned node vector. |
| failure | No checks in aggregate; enumeration guarantees in-range indexes. |
| cost | Constant per label. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0015

[Lines 54–55](../../../../../src/planner/candidate_generator.cpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L55:sha256:1853e48bd95a8151ec80acb4c4eeb0fc90fb95d1f0ccca561b71a2fb75e1c464
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ScopeDigit: One generalized scope: native anchor plus ascending-variable inclusion bytes. Different anchors can represent the same set; dedup handles that. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ScopeDigit; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ScopeDigit come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0016

[Lines 56–56](../../../../../src/planner/candidate_generator.cpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct ScopeDigit {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one generalized scope through a native anchor and dynamic inclusion bits. |
| inputs / outputs | Anchor occurrence index plus byte-vector bits. |
| invariants | Bit order follows ascending variables of the anchor scope; duplicate subsets across anchors are intentional. |
| ownership | Owns bit vector, retains no iterator into external data. |
| failure | Allocation/limit stops in append preserve pending resize/advance. |
| cost | O(anchor scope width) storage; dynamic carry scans bits and anchors. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0017

[Lines 57–57](../../../../../src/planner/candidate_generator.cpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct Frame {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain DFS position and native path count for one reached label. |
| inputs / outputs | Node label,next child label,native depth. |
| invariants | next_child scans all labels, not a prebuilt adjacency list; pushed native depth counts native nodes only. |
| ownership | Value in owned explicit stack. |
| failure | Push prepared before seen/reached/parent cursor updates. |
| cost | Constant frame storage; n candidate-child checks per frame. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0018

[Lines 58–74](../../../../../src/planner/candidate_generator.cpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::shared_ptr<const cd::BindingData> binding;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own source scopes, topology/scope digits, DFS and draft publication state across grants. |
| inputs / outputs | Binding/target/budget; vectors, building/ready tree owners, engine/task/statistics and flags. |
| invariants | Source IDs are original occurrences/variables. Ready tree remains stable until consume; unfinished building never escapes. |
| ownership | Unique pimpl shares immutable binding/budget and owns all scratch/coroutine/tree content. |
| failure | Saved operations isolate allocations; cancellation detaches frames before clearing referenced scratch. |
| cost | O(m+g+DFS depth+scope bits+draft content) live storage, plus cumulatively charged discarded constructions. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0019

[Lines 75–79](../../../../../src/planner/candidate_generator.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Impl(std::shared_ptr<const cd::BindingData> input,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit inert generator inputs and reject absent owners. |
| inputs / outputs | Binding,target height,budget moved to fields. |
| invariants | Does not validate arbitrary query contents or prove target minimum; facade supplies admitted inputs. |
| ownership | Retains shared source/budget; scratch lazy. |
| failure | Throws invalid_argument for null binding/budget; shell allocation can throw. |
| cost | Constant shell initialization, no enumeration. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp) |

## B0020

[Lines 80–80](../../../../../src/planner/candidate_generator.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~Impl() { engine.cancel(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach active generator frames before member scratch destruction. |
| inputs / outputs | Destructor invokes leaf-first Engine::cancel. |
| invariants | Task ownership is cleared to avoid double destroy/recursive active-frame chains. |
| ownership | Releases control frames before vectors/trees. |
| failure | Nonthrowing cancellation and standard destructors. |
| cost | O(active frames) plus local cleanup outside grant accounting. |
| Design | [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0021

[Lines 81–83](../../../../../src/planner/candidate_generator.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::size_t depth() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report owned generator control frame plus DFS frames. |
| inputs / outputs | Zero before start/finished/cancelled, else 1+stack.size(). |
| invariants | Blocked requested pushes do not own frames; even empty-body generation uses one control frame while active. |
| ownership | Scalar snapshot from owned stack. |
| failure | Noexcept. |
| cost | Constant-time. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0022

[Lines 84–89](../../../../../src/planner/candidate_generator.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class T> void append(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one budgeted vector cell with explicit capacity representability check. |
| inputs / outputs | Value by value and optional record charge; destination owns moved value. |
| invariants | max_size/preparation precede push; commit follows successful allocation. Current call values have safe move behavior. |
| ownership | Owns appended cell in scratch/tree vector. |
| failure | ContentStop or bad_alloc before commit; saved closure retains retry point. |
| cost | Amortized append plus relocation/value costs; budget check constant. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0023

[Lines 90–96](../../../../../src/planner/candidate_generator.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void put_variable(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deduplicate and charge each constructed scope member once. |
| inputs / outputs | VariableSet and original VariableId. |
| invariants | Repeats do not increase occurrence incidence or duplicate charges. |
| ownership | Set owns scalar ID. |
| failure | Size overflow/content limit/allocation stop before commit. |
| cost | Logarithmic contains+insert and one set-node allocation if absent. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0024

[Lines 97–98](../../../../../src/planner/candidate_generator.cpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L98:sha256:30afa031ebbb53d80b58c57721979668be849ef62423dd479819ea81982166ee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for publish: Counter room first; shared ownership publication then cannot allocate. The provider must still perform original P02, height and full-key checks. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies publish; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for publish come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0025

[Lines 99–104](../../../../../src/planner/candidate_generator.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void publish() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one complete unchecked tree draft. |
| inputs / outputs | Moves shared building ownership to ready and increments drafts_ready. |
| invariants | Counter room checked first; ready gates future steps until acknowledgement. No P02/minimum authority is created. |
| ownership | Ready shared owner retains immutable-use tree; building reference released. |
| failure | ContentStop overflow before any ownership publication. |
| cost | Constant shared-pointer operations. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp) |

## B0026

[Lines 105–108](../../../../../src/planner/candidate_generator.cpp#L105); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L108:sha256:7a5d93748126388ff7c74dbc880d23bc5067f1339c09304887c7078f7e4f08e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for run: Every root and non-self parent tuple is visited for g=0..m-1. The local contraction/guard proof justifies this minimum-height representative family; no global maintenance-cost completeness or new lower proof follows. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies run; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for run come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0027

[Lines 109–285](../../../../../src/planner/candidate_generator.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  control::Task run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate all labeled normal-form topologies and dynamic generalized-scope tuples at target native height. |
| inputs / outputs | Original scopes and target; emits ready drafts, waits for consume, finally sets finished. |
| invariants | g=0..m-1; every root/parent assignment excluding self edges is visited. Connectivity, Above, branching&gt;=2 and exact native height filter topologies; P02 checks remaining semantics. Empty body emits one empty tree. |
| ownership | Owns saved control locals/dynamic bit vectors/explicit DFS; allocates each draft by node/scope/edge operations. |
| failure | All allocations occur in saved operations outside resume; limits preserve digits/DFS/pending action. Size/counter preflights prevent arithmetic wrap. |
| cost | For n=m+g, root/parent family is exponential and DFS scans O(n²) labels per connected topology. Scope tuples multiply native power-set choices, with duplicates; tree builds cost nodes+scopes+edges and container operations. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [Refactor.md](../../../../../Refactor.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp) |

## B0028

[Lines 286–287](../../../../../src/planner/candidate_generator.cpp#L286); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L286-L287:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0029

[Lines 288–290](../../../../../src/planner/candidate_generator.cpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NormalFormGenerator::NormalFormGenerator(std::shared_ptr<const cd::BindingData> binding,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate inert unique generator implementation. |
| inputs / outputs | Binding,target,budget retained by pimpl. |
| invariants | Actual scope derivation and enumeration start in step. |
| ownership | Unique Impl owns shared inputs and future task. |
| failure | make_unique/null-input error propagates before caller publication. |
| cost | One shell allocation, constant initialization. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp) |

## B0030

[Lines 291–297](../../../../../src/planner/candidate_generator.cpp#L291); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NormalFormGenerator::~NormalFormGenerator() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement unique generator teardown and ownership moves. |
| inputs / outputs | Default destructor/move constructor/move assignment. |
| invariants | Moved-from machine is not stepped; target replacement destroys prior owned work. |
| ownership | Moves unique pimpl; Impl cancels frames before scratch release. |
| failure | Noexcept moves/destruction with current members. |
| cost | Move construction constant; target/final cleanup size-dependent, outside grants. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0031

[Lines 298–327](../../../../../src/planner/candidate_generator.cpp#L298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Step NormalFormGenerator::step(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resume one saved generator operation or admit its control frame. |
| inputs / outputs | UnitContext input; ready/exhausted/stopped/advanced Step. |
| invariants | Ready gate precedes all work; cancelled/overflow/finished flags are stable. Logical depth checks count owned frames; completed_steps increments only after success. |
| ownership | Task/Engine stay owned across retry; draft retained until consume. |
| failure | ContentStop translates to reason; overflow flag latches. bad_alloc escapes with started/pending operation unchanged. |
| cost | One frame allocation or pending operation per successful call; allocations/comparisons/relocations have variable costs. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0032

[Lines 328–328](../../../../../src/planner/candidate_generator.cpp#L328); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const FreeConnexTree> NormalFormGenerator::draft()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the currently ready unchecked tree. |
| inputs / outputs | Null until publish or after consume; shared const tree otherwise. |
| invariants | Caller must run P02/height/key gates before accepting; this getter grants no proof. |
| ownership | Shared copy retains tree beyond generator consumption/cancel. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant-time handle copy. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp) |

## B0033

[Lines 329–330](../../../../../src/planner/candidate_generator.cpp#L329); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L329-L330:sha256:065efe00bd7b380ba35b3c68dc0f316bf0f47cd95617a4a2497fdcc03d9c7620
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for NormalFormGenerator: Acknowledge only after provider validation/rejection/publication. Reset before increment prevents duplicate acknowledgements from inflating history. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies NormalFormGenerator; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for NormalFormGenerator come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0034

[Lines 331–335](../../../../../src/planner/candidate_generator.cpp#L331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void NormalFormGenerator::consume_draft()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acknowledge one ready proposal after its provider gate finishes. |
| inputs / outputs | Resets ready and increments drafts_consumed, or no-op if absent. |
| invariants | Count remains &lt;=guarded drafts_ready; duplicate acknowledgements cannot increment twice. |
| ownership | Releases generator ready owner; external checked handles can retain tree. |
| failure | Noexcept; current payload cleanup is standard nonthrowing destruction. |
| cost | Constant owner reset plus possible size-dependent final tree destruction. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0035

[Lines 336–336](../../../../../src/planner/candidate_generator.cpp#L336); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const GeneratorStatistics& NormalFormGenerator::statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose generator activity counters without copying storage. |
| inputs / outputs | Const GeneratorStatistics&. |
| invariants | Counters concern enumeration, not proof or candidate publication. |
| ownership | Borrowed from pimpl; expires on destruction/replacement. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant access. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp) |

## B0036

[Lines 337–337](../../../../../src/planner/candidate_generator.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t NormalFormGenerator::current_depth()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return current owned control+DFS depth. |
| inputs / outputs | size_t from Impl::depth(). |
| invariants | Does not include unrelated suspended validator/key workers or blocked pushes. |
| ownership | Scalar copy. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant-time. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0037

[Lines 338–338](../../../../../src/planner/candidate_generator.cpp#L338); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool NormalFormGenerator::cancelled()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe terminal explicit generator cancellation. |
| inputs / outputs | Boolean was_cancelled flag. |
| invariants | Cancellation is independent of natural exhaustion and overflow. |
| ownership | Scalar read. |
| failure | Noexcept; valid pimpl required. |
| cost | Constant-time. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp) |

## B0038

[Lines 339–349](../../../../../src/planner/candidate_generator.cpp#L339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void NormalFormGenerator::cancel()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release unpublished generator work while retaining diagnostic history. |
| inputs / outputs | No-op for moved-from/already-cancelled; cancels engine, clears drafts/scopes/nodes/digits/stack and marks cancelled. |
| invariants | Control frames detach before scratch expires. Shared draft copies survive; vector clear may retain allocated capacity until destruction. |
| ownership | Releases logical contents and owners; pimpl/binding/budget/statistics remain. |
| failure | Noexcept; no dynamic diagnostic or new allocation. |
| cost | Cleanup proportional to active frames and owned cells; outside grant work. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0039

[Lines 350–350](../../../../../src/planner/candidate_generator.cpp#L350); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L350-L350:sha256:3ea00d71de03416591bb9844776a36ebb57b0e6adb064ec801803bb4199e2fb5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::candidate_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |
