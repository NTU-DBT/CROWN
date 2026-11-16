# `src/planner/candidate_key.cpp` — block usage map

[Source](../../../../../src/planner/candidate_key.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Compute canonical candidate identity through a bounded resumable key machine.

Snapshot SHA-256: `03a0a23698abbe6b95530b291ebcc273ce86ccdd5ca0d44f28c868d2a63a050b`. 341 lines partitioned into 32 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../src/planner/candidate_key.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 20–22](../../../../../src/planner/candidate_key.cpp#L20) | Callable definition: void prepare_increment(std::uint64_t value) | calls ContentStop · [reviewed contract](#b0002) |
| [B0003 · 23–23](../../../../../src/planner/candidate_key.cpp#L23) | Explanatory comments or spacing. |  |
| [B0004 · 24–33](../../../../../src/planner/candidate_key.cpp#L24) | Callable definition: KeyStop key_stop(GeneratorStop reason) noexcept | calls ; returns KeyStop::none; KeyStop::depth_limit · [reviewed contract](#b0004) |
| [B0005 · 34–36](../../../../../src/planner/candidate_key.cpp#L34) | declares types or opens a type body. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 37–41](../../../../../src/planner/candidate_key.cpp#L37) | Type/record definition: struct Frame |  · [reviewed contract](#b0006) |
| [B0007 · 42–59](../../../../../src/planner/candidate_key.cpp#L42) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 60–69](../../../../../src/planner/candidate_key.cpp#L60) | Callable definition: Impl(std::shared_ptr&lt;const FreeConnexTree&gt; input, std::shared_ptr&lt;ContentBudget&gt; content) : tree(std::move(input)), budget(std::m… | calls tree, std::move, budget, std::invalid_argument · [reviewed contract](#b0008) |
| [B0009 · 70–70](../../../../../src/planner/candidate_key.cpp#L70) | Explanatory comments or spacing. |  |
| [B0010 · 71–71](../../../../../src/planner/candidate_key.cpp#L71) | Callable definition: ~Impl() | calls cancel · [reviewed contract](#b0010) |
| [B0011 · 72–72](../../../../../src/planner/candidate_key.cpp#L72) | Explanatory comments or spacing. |  |
| [B0012 · 73–76](../../../../../src/planner/candidate_key.cpp#L73) | Callable definition: std::size_t depth() const noexcept | calls size; returns 0; stack.size() · [reviewed contract](#b0012) |
| [B0013 · 77–77](../../../../../src/planner/candidate_key.cpp#L77) | Explanatory comments or spacing. |  |
| [B0014 · 78–86](../../../../../src/planner/candidate_key.cpp#L78) | Callable definition: template&lt;class Container, class Value&gt; void append(Container& output, Value&& value, std::uint64_t records, std::uint64_t cells) | calls size, max_size, ContentStop, prepare; growth push_back · [reviewed contract](#b0014) |
| [B0015 · 87–87](../../../../../src/planner/candidate_key.cpp#L87) | Explanatory comments or spacing. |  |
| [B0016 · 88–94](../../../../../src/planner/candidate_key.cpp#L88) | Callable definition: void append_char(std::string& output, char value) | calls size, max_size, ContentStop, prepare; growth push_back · [reviewed contract](#b0016) |
| [B0017 · 95–95](../../../../../src/planner/candidate_key.cpp#L95) | Explanatory comments or spacing. |  |
| [B0018 · 96–104](../../../../../src/planner/candidate_key.cpp#L96) | Callable definition: void publish() | calls prepare, std::move, commit; growth make_shared; source comment (unverified): // Call after the resumable cursor has drained its temporary token/frame · [reviewed contract](#b0018) |
| [B0019 · 105–105](../../../../../src/planner/candidate_key.cpp#L105) | Explanatory comments or spacing. |  |
| [B0020 · 106–266](../../../../../src/planner/candidate_key.cpp#L106) | Callable definition: control::Task run() | calls KEY_AT, control::operation, KEY_OP, depth; 17 loop sites; source comment (unverified): // Every potentially allocating operation below is a saved closure and is · [reviewed contract](#b0020) |
| [B0021 · 267–268](../../../../../src/planner/candidate_key.cpp#L267) | Closes surrounding scope/type. |  · [reviewed contract](#b0021) |
| [B0022 · 269–271](../../../../../src/planner/candidate_key.cpp#L269) | Callable definition: StructuralKeyMachine::StructuralKeyMachine(std::shared_ptr&lt;const FreeConnexTree&gt; tree, std::shared_ptr&lt;ContentBudget&gt; budget) : d… | calls data_, std::move; growth make_unique · [reviewed contract](#b0022) |
| [B0023 · 272–277](../../../../../src/planner/candidate_key.cpp#L272) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Move assignment can synchronously release the destination's prior scratch · [reviewed contract](#b0023) |
| [B0024 · 278–313](../../../../../src/planner/candidate_key.cpp#L278) | Callable definition: KeyStep StructuralKeyMachine::step(const cd::UnitContext& context) | calls empty, depth, permits, prepare_increment; returns {KeyEvent::stopped, KeyStop::cancelled}; {KeyEvent::key_ready}; source comment (unverified): // Coroutine frame allocation is outside resume(). · [reviewed contract](#b0024) |
| [B0025 · 314–314](../../../../../src/planner/candidate_key.cpp#L314) | Explanatory comments or spacing. |  |
| [B0026 · 315–317](../../../../../src/planner/candidate_key.cpp#L315) | Callable definition: std::shared_ptr&lt;const std::string&gt; StructuralKeyMachine::key() const noexcept | calls ; returns data_ ? data_-&gt;published : nullptr · [reviewed contract](#b0026) |
| [B0027 · 318–321](../../../../../src/planner/candidate_key.cpp#L318) | Callable definition: const KeyStatistics& StructuralKeyMachine::statistics() const noexcept | calls ; returns data_ ? data_-&gt;stats : empty · [reviewed contract](#b0027) |
| [B0028 · 322–324](../../../../../src/planner/candidate_key.cpp#L322) | Callable definition: std::size_t StructuralKeyMachine::current_depth() const noexcept | calls depth; returns data_ ? data_-&gt;depth() : 0 · [reviewed contract](#b0028) |
| [B0029 · 325–327](../../../../../src/planner/candidate_key.cpp#L325) | Callable definition: bool StructuralKeyMachine::cancelled() const noexcept | calls ; returns !data_ \|\| data_-&gt;was_cancelled · [reviewed contract](#b0029) |
| [B0030 · 328–329](../../../../../src/planner/candidate_key.cpp#L328) | Explanatory comments or spacing. | source comment (unverified): // clear drops live elements but may retain outer-vector/string capacity until · [reviewed contract](#b0030) |
| [B0031 · 330–339](../../../../../src/planner/candidate_key.cpp#L330) | Callable definition: void StructuralKeyMachine::cancel() noexcept | calls cancel, clear, reset; source comment (unverified): // clear drops live elements but may retain outer-vector/string capacity until · [reviewed contract](#b0031) |
| [B0032 · 340–341](../../../../../src/planner/candidate_key.cpp#L340) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::candidate_detail · [reviewed contract](#b0032) |

## B0001

[Lines 1–19](../../../../../src/planner/candidate_key.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:c3e67a308505f71d8f70e79bd30b7526a59378acc589a9540fb6a912c6f0d17f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "candidate_key.hpp", #include "producer_cursor.hpp", #include &lt;algorithm&gt;, #include &lt;array&gt;, #include &lt;charconv&gt;, #include &lt;limits&gt;, #include &lt;stdexcept&gt;, #include &lt;string_view&gt;, #include &lt;system_error&gt;, #include &lt;utility&gt;, #include &lt;vector&gt; available to src/planner/candidate_key.cpp; open crown::planner::candidate_detail and anonymous helper namespace. In this span, bind cd = continuation_detail, control = cd::producer_private. Define constexpr bounds counter_max. |
| inputs / outputs | Includes supply declarations; the listed namespace aliases bind names, and any listed constexpr bounds are constant-initialized metadata. These declarations do not run a planner search or validate a query. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | Namespace aliases own no runtime object. Any constexpr bounds in this span are fixed scalar metadata; no query owner, mutable counter or allocation grant is created by them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Preprocessing, name lookup and compile-time constant evaluation; constexpr bounds require no dynamic initialization and can occupy fixed constant storage when used. Included definitions retain their own call/construction costs. |
| Design | [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0002

[Lines 20–22](../../../../../src/planner/candidate_key.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_increment(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject uint64 metric overflow before a controlled update. |
| inputs / outputs | Current counter to normal return or ContentStop(counter_overflow). |
| invariants | Never changes the counter itself. |
| ownership | Scalar borrow by value. |
| failure | Throws only at maximum; worker catches the typed content stop. |
| cost | Fixed check, no owned payload. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 24–33](../../../../../src/planner/candidate_key.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
KeyStop key_stop(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate shared generator content-stop reasons to token-worker labels. |
| inputs / outputs | GeneratorStop to KeyStop. |
| invariants | Unknown enum conservatively maps counter_overflow; no success is invented. |
| ownership | Enum by value. |
| failure | noexcept conversion. |
| cost | Fixed switch without allocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 34–36](../../../../../src/planner/candidate_key.cpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StructuralKeyMachine::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own postorder token construction and publication state. |
| inputs / outputs | Retained tree/budget, per-node token strings, traversal stack, building/final token, metrics and Engine/Task. |
| invariants | Tree topology is a P02 precondition; minimal root/child range checks are not full cycle/cover verification. |
| ownership | Owns scratch and frame-backed callbacks. Tokens are populated before traversal and retained until final-root copying completes. |
| failure | Cancellation destroys active frames before clearing borrowed scratch/input; no partial token is exposed. |
| cost | All node tokens and repeated descendant bytes can accumulate quadratically; clear may retain outer-vector/string capacity until owner destruction. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 37–41](../../../../../src/planner/candidate_key.cpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Frame {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Save one token traversal node and canonical child-order scratch. |
| inputs / outputs | Node index, next child index and vector of positions in the supplied child array. |
| invariants | Order values are child positions; comparison uses complete child bytes, never NodeId ordering. |
| ownership | Frame/order storage owned by stack; suspended control uses numeric positions rather than saved vector element references. |
| failure | Appending a child frame commits before advancing its parent. |
| cost | One frame plus O(degree) order storage, with real vector relocation/allocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 42–59](../../../../../src/planner/candidate_key.cpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L59:sha256:493c41052152123af11c3705525e731eea97f01c7e0860c43f7c534fd281a22d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the original tree and content budget, traversal tokens/frames/building key, published key, statistics, Engine/Task, and lifecycle flags in StructuralKeyMachine::Impl. |
| inputs / outputs | The fields hold the input owners and resumable structural-key traversal state; the constructor receives shared tree and budget owners in adjacent lines. |
| invariants | Tree validation and invalid-input state remain separate from traversal completion, cancellation, counter overflow, and publication; a key is published only after the traversal completes. |
| ownership | tree and budget share their payload owners; vectors and strings own traversal/output storage; published shares the immutable completed key; Task owns its coroutine frame, while Engine::active is non-owning. |
| failure | The neighboring constructor rejects null owners and can throw invalid_argument. Container/key growth can allocate; later machine methods translate content stops and allocation outcomes. |
| cost | Fixed state plus token, frame, and key storage that grows with tree traversal; the completed key is retained by shared ownership. These declarations add no per-step work. |
| Design | [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0008

[Lines 60–69](../../../../../src/planner/candidate_key.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Impl(std::shared_ptr<const FreeConnexTree> input,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt owners and perform minimal root-envelope checks without traversing. |
| inputs / outputs | Non-null shared tree/budget; invalid root/empty combination sets invalid_input. |
| invariants | Requires a P02-valid topology from the private caller for canonical traversal. |
| ownership | Moves shared owners; no deep tree clone. |
| failure | Null inputs throw invalid_argument; shell allocation can fail; other malformed topology is outside precondition. |
| cost | Fixed shared-handle/root/size work plus inert allocation, independent of descendant count. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 71–71](../../../../../src/planner/candidate_key.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Impl() { engine.cancel(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach live coroutine frames before their borrowed state members are destroyed. |
| inputs / outputs | Destructor cancels Engine, then normal member destruction follows. |
| invariants | Task handle ownership is detached leaf-first by Engine cancellation. |
| ownership | Drops scratch, published/tree/budget references; independently retained token survives. |
| failure | Destruction is nonthrowing and may release last-owned payloads. |
| cost | Can traverse frames, free all token/order buffers and last-owned tree data; not a constant-time operation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 73–76](../../../../../src/planner/candidate_key.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t depth() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the active traversal stack depth. |
| inputs / outputs | 0 after completion/cancel, otherwise stack.size. |
| invariants | This is tree traversal depth, not byte usage or the private administrative coroutine count. |
| ownership | Scalar return from Impl. |
| failure | noexcept; empty-tree encoding has depth0. |
| cost | Fixed flag/size reads. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 78–86](../../../../../src/planner/candidate_key.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void append(Container& output,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit logical content then append one token/frame/order item transactionally. |
| inputs / outputs | Container, forwarded element, record/cell debits. |
| invariants | max_size and content prepare precede push; commit follows successful push. |
| ownership | Moves/copies into machine-owned destination; source preparation remains owned across a failed append. |
| failure | ContentStop or allocation failure leaves logical debit uncommitted and callback pending. |
| cost | Actual vector relocation/element construction is distinct from logical record/cell counts. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 88–94](../../../../../src/planner/candidate_key.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append_char(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund and append one encoded byte. |
| inputs / outputs | Target string and char; prepare(0,1), push, commit. |
| invariants | Byte admission commits only after successful string append. |
| ownership | Target owns appended bytes. |
| failure | Size overflow/content/allocator failure precede logical commit. |
| cost | One logical byte can trigger size-dependent string growth/relocation; no fixed allocator-time claim. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 96–104](../../../../../src/planner/candidate_key.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void publish() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create immutable owning key only after temporary traversal/token storage drains. |
| inputs / outputs | Admit final record, allocate shared string by moving building_key, assign published, commit, finish. |
| invariants | No partial published owner exists if make_shared fails; no throwing update follows successful string construction. |
| ownership | Published string independently owns bytes; scratch capacities and shared budget/tree may remain in Impl. |
| failure | Content admission or allocation can stop/retry before publication. |
| cost | One control-block/string-object allocation and string move; not a deep second key copy for ordinary allocator moves. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 106–266](../../../../../src/planner/candidate_key.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  control::Task run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct collision-free framed rooted-tree tokens through saved operations. |
| inputs / outputs | Allocate token slots, postorder children, insertion-sort complete child tokens, frame scopes/occurrences and copy root bytes. |
| invariants | Node display IDs/vector order and child order do not enter identity. Derived claims are omitted only because P02 already checks them. |
| ownership | Suspended frame retains local indexes/references into immutable tree or stable token slots; only pending operations may throw. |
| failure | Child range error marks invalid; content and allocation failures happen in Engine callback. Invalid cycles are outside caller precondition. |
| cost | Repeated subtree copying and insertion sort can cost quadratic work/storage; numeric formatting is bounded machine-width control flow, and capacity/allocator work remains real. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
#define KEY_AT(desired, ...)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Schedule throwing preparation outside coroutine resume. |
| inputs / outputs | Capture stable frame variables by reference and save requested logical depth. |
| invariants | Callback lifetime is bounded by its suspended owning frame. |
| ownership | Macro locals/callbacks live in the retained owning coroutine frame. |
| failure | Engine retains callback if it throws; unhandled resume exceptions are fatal. |
| cost | One pending operation slot; creating/copying caller captures must be nonthrowing. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
#define KEY_OP(...)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Schedule a token operation at current traversal depth. |
| inputs / outputs | Forwards to KEY_AT(depth()). |
| invariants | Does not add another public work facade or double-charge. |
| ownership | Macro locals/callbacks live in the retained owning coroutine frame. |
| failure | Delegates callback preparation/retry. |
| cost | Fixed wrapper over the actual callback cost. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
#define KEY_CHAR(output, value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Schedule one admitted output byte. |
| inputs / outputs | Forwards append_char through KEY_OP. |
| invariants | Cell count records logical appended bytes, not allocator capacity. |
| ownership | Macro locals/callbacks live in the retained owning coroutine frame. |
| failure | Byte admission/append failures remain pending. |
| cost | One saved byte plus any string growth. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
#define KEY_LITERAL(output, literal)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit fixed grammar text one saved character at a time. |
| inputs / outputs | Iterate literal string_view and schedule KEY_CHAR. |
| invariants | Literal bytes remain static and stable while suspended. |
| ownership | Macro locals/callbacks live in the retained owning coroutine frame. |
| failure | Only the saved append callback may allocate/throw. |
| cost | One transition per literal byte; literal lengths are fixed for this profile. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
#define KEY_SIZE(output, expression)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a machine-size number as decimal digits without formatted heap scratch. |
| inputs / outputs | Evaluate size expression, use bounded stack to_chars, then append digits individually. |
| invariants | Digit array has capacity for supported size_t; profile separators frame the number. |
| ownership | Macro locals/callbacks live in the retained owning coroutine frame. |
| failure | Conversion status is checked inside a saved operation; append/content failures retry. |
| cost | Bounded machine-width formatting plus one charged append per digit. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 267–268](../../../../../src/planner/candidate_key.cpp#L267); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L267-L268:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0022

[Lines 269–271](../../../../../src/planner/candidate_key.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StructuralKeyMachine::StructuralKeyMachine(std::shared_ptr<const FreeConnexTree> tree,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct inert key worker around retained owners. |
| inputs / outputs | Shared tree/budget to unique Impl. |
| invariants | Does not run P02, tokenization or a hidden cache lookup. |
| ownership | Moves owner handles into newly allocated Impl. |
| failure | Null/envelope checks and allocation follow Impl contract. |
| cost | Inert object allocation plus fixed checks; no graph copy. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 272–277](../../../../../src/planner/candidate_key.cpp#L272); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StructuralKeyMachine::~StructuralKeyMachine() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define owner destruction and adjacent default move lifetime behavior. |
| inputs / outputs | Destructor, noexcept move construction and move assignment. |
| invariants | Moved-from public methods are guarded; source owner transfers once. |
| ownership | Unique Impl; published key may be held independently. |
| failure | Nonthrowing lifetime operations can synchronously release previous destination state. |
| cost | Move construction transfers a pointer; move assignment/destruction can release large old scratch/tree/key populations outside steps. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 278–313](../../../../../src/planner/candidate_key.cpp#L278); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
KeyStep StructuralKeyMachine::step(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one retained token transition and report completion/typed stops. |
| inputs / outputs | Context to KeyStep; starts coroutine on first admitted call and thereafter drives saved callback/resume. |
| invariants | Ready/cancel/invalid/overflow states take precedence. Nonempty input requires depth1 before initial work; only successful transitions increment completed_steps. |
| ownership | Retains frame/owners across calls; context is borrowed only for the call. |
| failure | ContentStop becomes reason; bad_alloc propagates with pending logical operation. Counter overflow is terminal, other content limits may be raised. |
| cost | Administrative first frame and one later operation per successful call, plus actual underlying container/control costs; not total CPU accounting. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 315–317](../../../../../src/planner/candidate_key.cpp#L315); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const std::string> StructuralKeyMachine::key()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a complete immutable token without copying its bytes. |
| inputs / outputs | Nullable shared string handle; moved-from returns null. |
| invariants | A key is not query/context identity or proof authority by itself. |
| ownership | Refcounted token owner can outlive worker. |
| failure | noexcept; never publishes incomplete building_key. |
| cost | Fixed handle copy; last-owner byte release is separate. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 318–321](../../../../../src/planner/candidate_key.cpp#L318); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const KeyStatistics& StructuralKeyMachine::statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow current key metrics or stable empty moved-from metrics. |
| inputs / outputs | Const reference to live stats or static zero aggregate. |
| invariants | No step or counter update occurs. |
| ownership | Live reference requires machine lifetime; static fallback has program lifetime. |
| failure | noexcept guarded read. |
| cost | Fixed reference selection without allocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0028

[Lines 322–324](../../../../../src/planner/candidate_key.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t StructuralKeyMachine::current_depth()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read logical traversal depth safely after move. |
| inputs / outputs | Returns Impl.depth or0. |
| invariants | Independent of source native height and breadth/storage. |
| ownership | Scalar copy. |
| failure | noexcept. |
| cost | Fixed pointer/size reads. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0029

[Lines 325–327](../../../../../src/planner/candidate_key.cpp#L325); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool StructuralKeyMachine::cancelled()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish explicit/moved-from cancellation from ordinary completion. |
| inputs / outputs | True for missing owner or was_cancelled; false for a normally published token. |
| invariants | A resource stop is not automatically cancellation. |
| ownership | Scalar copy. |
| failure | noexcept. |
| cost | Fixed guarded flag read. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0030

[Lines 328–329](../../../../../src/planner/candidate_key.cpp#L328); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L328-L329:sha256:df94bf4c0a32c8286a422f451e073a80dfe8852571c7d58c7f697c93cd93d4a9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for StructuralKeyMachine: clear drops live elements but may retain outer-vector/string capacity until this worker is destroyed. A published key makes cancellation a no-op. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies StructuralKeyMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for StructuralKeyMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0031

[Lines 330–339](../../../../../src/planner/candidate_key.cpp#L330); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void StructuralKeyMachine::cancel()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop unfinished token work without revoking published ownership. |
| inputs / outputs | No-op for absent/already-cancelled/published; otherwise cancel frames, clear scratch, drop tree and mark cancelled. |
| invariants | Published immutable key wins over cancellation. Cumulative content charges are not refunded. |
| ownership | Releases live elements/owners; outer vector and cleared string capacities can remain until Impl destruction. |
| failure | Declared noexcept; caller cannot turn cancellation into an allocation/validation continuation. |
| cost | Frame/container/last-owner teardown can scale with retained state and is outside provider advance grants. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0032

[Lines 340–341](../../../../../src/planner/candidate_key.cpp#L340); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L340-L341:sha256:09a159a40d365cb56ac3e4e9761854949aa1ef05f5a3c858139593db61861def
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::candidate_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |
