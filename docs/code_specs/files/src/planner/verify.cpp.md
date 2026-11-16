# `src/planner/verify.cpp` — block usage map

[Source](../../../../../src/planner/verify.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Independently validate CROWN tree coverage, guard, connected-variable paths, connex output structure and height claims.

Snapshot SHA-256: `33b647bdba71bda5fb9612e8883bb416c9e25dc9c043f84cc30ee2247898bf08`. 462 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../src/planner/verify.cpp#L1) | Imports dependencies; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Each case commits one cursor transition. Set/map lookup, allocation and · [reviewed contract](#b0001) |
| [B0002 · 19–33](../../../../../src/planner/verify.cpp#L19) | Type/record definition: enum class Phase |  · [reviewed contract](#b0002) |
| [B0003 · 34–42](../../../../../src/planner/verify.cpp#L34) | Type/record definition: struct NodeState |  · [reviewed contract](#b0003) |
| [B0004 · 43–43](../../../../../src/planner/verify.cpp#L43) | Type/record definition: struct Frame |  · [reviewed contract](#b0004) |
| [B0005 · 44–66](../../../../../src/planner/verify.cpp#L44) | declares callable signatures; declares values/defaults or compile-time conditions. | growth make_shared · [reviewed contract](#b0005) |
| [B0006 · 67–68](../../../../../src/planner/verify.cpp#L67) | Callable definition: Impl(std::shared_ptr&lt;const BindingData&gt; b, std::shared_ptr&lt;const FreeConnexTree&gt; t) : binding(std::move(b)), tree(std::move(t)) | calls binding, std::move, tree · [reviewed contract](#b0006) |
| [B0007 · 69–73](../../../../../src/planner/verify.cpp#L69) | Callable definition: void violation(std::string rule, std::string message, std::optional&lt;NodeId&gt; node = {}, std::optional&lt;VariableId&gt; var = {}, std::o… | calls push_back, std::move; growth push_back · [reviewed contract](#b0007) |
| [B0008 · 74–427](../../../../../src/planner/verify.cpp#L74) | Callable definition: UnitResult step(const UnitContext& context) | calls empty, permits, violation, size; returns {UnitEvent::depth_blocked, 1}; {UnitEvent::depth_blocked, 1}; growth emplace_back, insert, make_shared, push_back, reserve; source comment (unverified): // Numeric topology must be safe before separator/connectivity traversals. · [reviewed contract](#b0008) |
| [B0009 · 428–429](../../../../../src/planner/verify.cpp#L428) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 430–432](../../../../../src/planner/verify.cpp#L430) | Callable definition: ValidationMachine::ValidationMachine(std::shared_ptr&lt;const BindingData&gt; binding, std::shared_ptr&lt;const FreeConnexTree&gt; tree) : da… | calls data_, std::move; growth make_unique · [reviewed contract](#b0010) |
| [B0011 · 433–435](../../../../../src/planner/verify.cpp#L433) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 436–436](../../../../../src/planner/verify.cpp#L436) | Callable definition: UnitResult ValidationMachine::step(const UnitContext& context) | calls step; returns data_-&gt;step(context) · [reviewed contract](#b0012) |
| [B0013 · 437–437](../../../../../src/planner/verify.cpp#L437) | Callable definition: const ValidationReport& ValidationMachine::report() const noexcept | calls ; returns *data_-&gt;result · [reviewed contract](#b0013) |
| [B0014 · 438–438](../../../../../src/planner/verify.cpp#L438) | Callable definition: std::shared_ptr&lt;const CheckedUpper&gt; ValidationMachine::checked() const noexcept | calls ; returns data_-&gt;authority · [reviewed contract](#b0014) |
| [B0015 · 439–444](../../../../../src/planner/verify.cpp#L439) | Callable definition: std::size_t ValidationMachine::current_depth() const noexcept | calls std::max, size; returns data_-&gt;active ? std::max(std::size_t{1}, data_-&gt;frames.size()) : 0; source comment (unverified): // One saved rule frame is active for nonempty input. Reachability reuses it · [reviewed contract](#b0015) |
| [B0016 · 445–447](../../../../../src/planner/verify.cpp#L445) | declares namespace scope. | source comment (unverified): // namespace crown::planner::continuation_detail · [reviewed contract](#b0016) |
| [B0017 · 448–461](../../../../../src/planner/verify.cpp#L448) | Callable definition: ValidationReport validate_tree(const Catalog& catalog, const Query& query, const FreeConnexTree& tree) | calls validate, machine, std::move, step; returns machine.report(); growth make_shared; 1 loop sites; source comment (unverified): // Input validation and ownership copies are explicit blocking-adapter admission · [reviewed contract](#b0017) |
| [B0018 · 462–462](../../../../../src/planner/verify.cpp#L462) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner · [reviewed contract](#b0018) |

## B0001

[Lines 1–18](../../../../../src/planner/verify.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ValidationMachine::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own independent validation scratch, program counter and eventual upper evidence. |
| inputs / outputs | Shared immutable binding/tree, initially invalid report and no authority. |
| invariants | Numeric topology is checked before graph traversals; name/scope/rule violations prevent valid publication even when further numeric traversals are safe. |
| ownership | Owns deques, ordered sets, iterators into stable owned sets, report and authority. string_views in names borrow the retained immutable tree. |
| failure | No caller may mutate input through another alias or step a moved-from facade; RAII releases partial preparation and complete scratch. |
| cost | Metadata scales with nodes/edges/scopes/variables/violations. Deques preserve elements on append but internal allocation/map work is not a fixed-time promise. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0002

[Lines 19–33](../../../../../src/planner/verify.cpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Phase {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode every resumable validation stage explicitly. |
| inputs / outputs | Private phase enumerator saved between step calls. |
| invariants | Progress follows numeric safety, structural properties, connectivity, connex, height, then publication; terminal done is stable. |
| ownership | Stored inside Impl, not a global registry or public serialization protocol. |
| failure | A throwing stage retains its last uncommitted phase/cursors. |
| cost | Fixed enum state; phase count does not bound total loop visits. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0003

[Lines 34–42](../../../../../src/planner/verify.cpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NodeState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain per-node topology and path metrics for independent verification. |
| inputs / outputs | Parent count/ID, reach mark, variable-connectivity stamp, nearest native ancestor, height/depth. |
| invariants | Parent links are used for traversals only after numeric topology/reachability checks; native height and ordinary depth are distinct. |
| ownership | Deque-owned state, indexed by NodeId. |
| failure | Inert fields default without traversing input; deque growth may allocate during nodes phase. |
| cost | Fixed metadata per node; not a proof of bounded total scratch. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0004

[Lines 43–43](../../../../../src/planner/verify.cpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Frame {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Save one reachability descent and next child index. |
| inputs / outputs | NodeId and child offset. |
| invariants | Parent offset advances only after child frame insertion succeeds; desired depth is tested first. |
| ownership | Value held in the machine-owned deque; does not own a tree node. |
| failure | Failed child append leaves the prior logical descent pending. |
| cost | Fixed frame fields; append may invoke real deque/allocator work. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0005

[Lines 44–66](../../../../../src/planner/verify.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L66:sha256:7a80b2107a6c32cc84207cd12b016cf878209172260f01d986f2aaaae24ad2d4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain binding, tree, result, authority, phase, active, topology_valid, occurrences, states, names, frames, order, queue, violations, complete_scope, head, covered, claimed_coverage, supplied, it, other, supplied_it, i, j, k, position, variable, height, edge_depth, first, output_only in ValidationMachine::Impl across its lifetime. |
| inputs / outputs | These are stored fields for ValidationMachine::Impl, not callable parameters or results; constructors and later methods set or consume them. |
| invariants | The fields preserve the named machine or owner state between calls; counters, cursors, and stored claims remain data until adjacent methods update or validate them. |
| ownership | shared_ptr members retain their pointees through shared ownership; this span does not deep-copy them; containers and strings own their elements or bytes; string_view members borrow backing text. |
| failure | The inline make_shared&lt;ValidationReport&gt;() and container construction/growth can fail allocation. The surrounding factory/caller defines translation and cleanup; this span does not implement a recovery wrapper. |
| cost | Impl construction evaluates result = make_shared&lt;ValidationReport&gt;(), allocating its object/control storage. Member container construction, including deque setup, can also allocate before advance prepares additional state; later payload growth adds its own costs. Copying existing shared handles does not deep-copy their pointees. |
| Design | [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 67–68](../../../../../src/planner/verify.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Impl(std::shared_ptr<const BindingData> b,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt immutable input owners into inert validation state. |
| inputs / outputs | Moves two shared handles; default member initialization creates an empty report. |
| invariants | No graph walk, catalog validation or tree copy occurs inside this constructor. |
| ownership | Impl retains both inputs and its newly allocated report. |
| failure | Report/Impl allocation may fail before a usable machine exists; RAII releases successful members. |
| cost | Fixed handles and empty-container setup plus report allocation; later validation is incremental. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0007

[Lines 69–73](../../../../../src/planner/verify.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void violation(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append an owning diagnostic before advancing the failing rule cursor. |
| inputs / outputs | Rule/message and optional node/variable/occurrence/related witnesses to pending violations deque. |
| invariants | Recording a violation never marks the tree valid; malformed numeric IDs can be reported without dereferencing them. |
| ownership | Owns diagnostic strings and scalar witness IDs. |
| failure | Argument/deque allocation can throw; caller cursor advances only after append success. |
| cost | Diagnostic byte construction and possible deque allocation, not a constant-time failure guarantee. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0008

[Lines 74–427](../../../../../src/planner/verify.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  UnitResult step(const UnitContext& context)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one saved independent validation transition. |
| inputs / outputs | Per-call frame ceiling; returns progress, depth request, or final upper-valid/invalid event. |
| invariants | All rules are checked independently of constructors/search. Complete valid report and preallocated authority are the sole success publication. |
| ownership | Mutates owned scratch while retaining input owners; no borrowed caller data or runtime relation. |
| failure | Allocation exceptions propagate for retry. Depth rejection precedes child insertion; failed tree rules accumulate owning violations. |
| cost | One phase transition is not a CPU bound: ordered lookups, allocation, string comparison and vector reserve retain their costs. Traversal/clearing cursors save incremental progress. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::start:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the first nonempty rule frame. |
| inputs / outputs | Query body emptiness and frame ceiling choose empty_cover or counts. |
| invariants | No active frame is installed before permits(1). |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Depth denial returns requested1 without phase progress. |
| cost | Fixed tests/state writes; no container growth. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::empty_cover:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a constant-body query uses an empty tree. |
| inputs / outputs | Root/node presence may append cover violation, then empty_connex. |
| invariants | Empty-body shape has no phantom native/generalized node. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Violation preparation may allocate before phase advance. |
| cost | Fixed emptiness reads plus any owning diagnostic. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::empty_connex:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a nonempty supplied connex list for an empty tree. |
| inputs / outputs | Optional list emptiness may append connex_certificate violation. |
| invariants | An absent or empty list is allowed. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic allocation leaves this phase pending. |
| cost | Fixed optional/size reads; no list scan. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::empty_height:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the optional zero-height claim for an empty body. |
| inputs / outputs | Nonzero claim adds height violation; next export_prepare. |
| invariants | Constant empty-tree native height is0. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Violation allocation precedes phase commit. |
| cost | Fixed height comparison plus possible diagnostic. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::counts:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Incrementally allocate one native-occurrence coverage counter. |
| inputs / outputs | Append zero until counter count equals query.atoms size, then nodes. |
| invariants | No atom occurrence is omitted because scopes coincide. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Deque allocation can fail before size/phase progress. |
| cost | One append or completion test; deque metadata/allocator cost applies. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::nodes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Incrementally create inert per-node verification state. |
| inputs / outputs | Append NodeState until tree node count reached, then node_name. |
| invariants | No node traversal or implicit bulk value initialization is hidden in this stage. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Deque growth can throw before phase transition. |
| cost | One fixed state append, with real container allocation cost. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::node_name:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check each node label and start its scope cursor. |
| inputs / outputs | At node end move to cover; otherwise reject empty/duplicate label or insert string_view. |
| invariants | Views borrow immutable retained tree strings; label failures need not make numeric traversals unsafe. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Set/diagnostic allocation precedes scope/phase installation. |
| cost | Ordered label lookup/insert compares actual string bytes; possible set node allocation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::node_scope:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one variable ID in the current scope. |
| inputs / outputs | Current iterator against query variable count; increment or advance node_kind. |
| invariants | Out-of-domain variable gets a witness without indexing by it. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Violation allocation precedes iterator increment. |
| cost | One ID test; end check is fixed, diagnostic bytes/allocator separate. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::node_kind:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify native/generalized nodes and admit native occurrence counting. |
| inputs / outputs | Valid native occurrence increments its counter and starts terms; generalized goes to its checks. |
| invariants | Unknown/missing occurrence is diagnosed before any atom indexing. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Invalid-kind/occurrence diagnostic can allocate before phase advance. |
| cost | Fixed tag/index checks and counter update; no scope copy. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::native_terms:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the complete native scope from one original atom term at a time. |
| inputs / outputs | Insert variable term into complete_scope; constants contribute no variable. |
| invariants | Native scope uses full atom occurrence, never its output projection. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Set allocation failure leaves the term index pending. |
| cost | One term plus logarithmic variable-set insertion; duplicate terms reuse set membership. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::native_compare_begin:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose native-scope mismatch or synchronized comparison. |
| inputs / outputs | Compare sizes; initialize two iterators only when equal. |
| invariants | Equal cardinality makes paired iterator advancement safe. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocating operation in this stage. |
| cost | Fixed size reads/iterator setup. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::native_compare:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one pair of native-scope variable IDs. |
| inputs / outputs | Equal pair advances both; first difference goes to native_scope_bad. |
| invariants | Every expected variable must match complete declared scope. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocating operation before a later diagnostic phase. |
| cost | One ordered-ID comparison and iterator increments. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::native_scope_bad:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one complete-native-scope violation. |
| inputs / outputs | Append scope diagnostic with native occurrence witness; next native_clear. |
| invariants | No successful upper can ignore this mismatch. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic/deque allocation leaves the same report step pending. |
| cost | Owning diagnostic construction; no full scope formatting. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::native_clear:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release temporary native-scope members incrementally. |
| inputs / outputs | Erase one first element, or finish at node_next. |
| invariants | No stale complete_scope elements enter the next native node. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Stored ID destruction/erase does not allocate. |
| cost | One node erase/deallocation; total clearing follows scope size. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::generalized_occurrence:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject external occurrence identity on a generalized node. |
| inputs / outputs | Optional occurrence adds cover violation, then generalized_leaf. |
| invariants | Generalized scope is local plan metadata, not a physical input alias. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic append can throw before phase publication. |
| cost | Fixed optional check plus any diagnostic construction. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::generalized_leaf:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ensure every leaf is an original native input. |
| inputs / outputs | Generalized node with no children adds cover violation. |
| invariants | Unary generalized nodes remain valid for P02; P03 normal form is separate. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic append can allocate before node_next. |
| cost | Fixed child emptiness test, no descendant scan. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::node_next:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance to the next node identity/scope checks. |
| inputs / outputs | Increment i and select node_name. |
| invariants | Prior native scratch has been cleared before reuse. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocation or failure conversion. |
| cost | Fixed state updates. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::cover:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one original occurrence appears exactly once. |
| inputs / outputs | Read coverage counter, append missing/duplicate occurrence diagnostic, advance. |
| invariants | Aliases and equal/contained scopes retain separate occurrence identities. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic append precedes index advance. |
| cost | One counter check plus optional owning diagnostic. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::root:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Establish a usable numeric root before graph rules. |
| inputs / outputs | Missing/out-of-range root records topology failure; initialize edge cursors. |
| invariants | Numeric graph traversals are skipped after topology_valid becomes false. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic append happens before the failure flag/cursors commit. |
| cost | Fixed root/index tests; no reachability walk. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::edges:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count one in-range child link or record its invalid numeric ID. |
| inputs / outputs | Per-node child cursor updates incoming count/parent or topology violation. |
| invariants | No out-of-range child indexes states; all links are examined before parent rules. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Violation allocation leaves the child cursor pending. |
| cost | One link test/update; row/Scope data are not copied. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::parent_counts:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check rooted-tree indegrees before traversals. |
| inputs / outputs | Each node needs0 parents for root,1 otherwise; stop to export on unsafe topology. |
| invariants | Duplicate parents/cycles cannot silently pass as a rooted tree; disconnected cycles are checked by reachability next. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Violation allocation precedes index/unsafe-flag update. |
| cost | One count comparison per node plus diagnostic preparation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::reach_start:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the first reachability frame only with admitted depth. |
| inputs / outputs | Push root, mark seen, select reach. |
| invariants | Root/edges/parent IDs are numerically safe at this point. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Depth denial or failed frame append leaves the transition pending. |
| cost | One deque push and marker; allocation cost stays real. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::reach:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one child descent or completed reachability frame. |
| inputs / outputs | Read parent child offset, check seen/depth, append child before advancing parent. |
| invariants | Successful child append is the only point after which parent progress and seen mark commit. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Denied depth or allocation failure does not consume the pending descent. |
| cost | One saved child transition or pop; container growth is not a strict-time bound. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::reach_check:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject nodes unreachable from the checked root. |
| inputs / outputs | One seen flag at a time; then order_start or export_prepare. |
| invariants | Rooted indegrees plus complete reachability establish safe tree topology. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic append precedes marking topology invalid/index advance. |
| cost | One seen read plus possible diagnostic; no fresh graph traversal. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::order_start:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed parent-before-child property traversal. |
| inputs / outputs | Push root in order, reset position/child offset. |
| invariants | Only numerically valid reachable trees enter this stage. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Deque append can fail before cursor publication. |
| cost | One saved root insertion. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::order:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one child to the breadth-first property order. |
| inputs / outputs | Read current parent child, append to order, then advance offset. |
| invariants | Parents precede children, allowing inherited height/depth/native-ancestor metadata. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Failed append retains current child offset. |
| cost | One append/offset transition; total order storage is O(nodes). |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::separator_reserve:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund complete separator-vector capacity before incremental initialization. |
| inputs / outputs | reserve(tree.nodes.size), then separator_init. |
| invariants | Later separator vector growth cannot relocate its stored scope objects. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Reserve failure leaves the same capacity admission pending. |
| cost | One potentially large allocation; this phase is not a constant wall-time promise. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::separator_init:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one empty separator slot at reserved capacity. |
| inputs / outputs | Append empty set until every node has one, then properties. |
| invariants | Slots are keyed by numeric NodeId with no claimed input trusted. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Reserved default set construction does not copy node scopes. |
| cost | One empty slot per call; previously admitted vector capacity covers storage. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::properties:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inherit path metadata and begin actual separator computation. |
| inputs / outputs | Parent supplies nearest native ancestor, native height and edge depth; start current scope. |
| invariants | Parent order is complete; root retains zero inherited metrics. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocation in field/iterator preparation. |
| cost | Fixed indexed reads/state writes. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::separator:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intersect one child-scope member with its parent scope. |
| inputs / outputs | Insert matching variable in result separator, or finish above. |
| invariants | Actual parent intersection is computed independently of claimed_separator. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Set insertion allocation precedes iterator advance. |
| cost | One ordered parent-set lookup and possible separator-node allocation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::above:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count native path weight and forbid generalized descendants below a native. |
| inputs / outputs | Native increments height; generalized with native ancestor appends above violation. |
| invariants | Generalized nodes add zero native height; ordinary edge depth stays separate. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Generalized violation allocation precedes guard cursor publication. |
| cost | Fixed tag/ancestor work plus possible diagnostic; no ancestor rescan. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::guard_begin:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start the next generalized-child inclusion check. |
| inputs / outputs | Skip native nodes/completed children; otherwise reset generalized scope iterator. |
| invariants | Each generalized scope must be guarded by every child, not merely one anchor. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocation in iterator/cursor setup. |
| cost | Fixed phase/child checks. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::guard:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one generalized-scope variable against the current child. |
| inputs / outputs | Missing child membership records a variable/related-node witness. |
| invariants | Complete per-child checks preserve independent guard validation. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Violation append precedes variable iterator advance. |
| cost | One ordered set membership query and possible diagnostic allocation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::claimed_separator_begin:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select comparison of optional claimed and actual separator. |
| inputs / outputs | Absent claim skips; unequal size routes to diagnostic; equal sizes install paired iterators. |
| invariants | Claimed metadata is never used as the computed separator. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocating operation in this transition. |
| cost | Fixed optional/size/iterator setup. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::claimed_separator:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one claimed/actual separator member. |
| inputs / outputs | Advance equal pairs; mismatch selects claimed_separator_bad. |
| invariants | Equal prechecked sizes make paired dereference safe. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocation; diagnostic is a separate stage. |
| cost | One ID comparison and iterator updates. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::claimed_separator_bad:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record a supplied separator mismatch. |
| inputs / outputs | Append separator diagnostic for current node, then property_finish. |
| invariants | Underclaims and overclaims both invalidate the supplied tree. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic preparation may throw before phase commit. |
| cost | Owning fixed-message diagnostic; no full set formatting. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::property_finish:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Update leaf maxima and move to the next ordered node. |
| inputs / outputs | Leaf contributes native-height and edge-depth maxima independently. |
| invariants | The two maxima can arise on different root-to-leaf paths. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocation in max/index updates. |
| cost | Fixed metadata work. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::connect_start:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the next query variable for running-intersection verification. |
| inputs / outputs | After all variables proceed to head; otherwise seed scan starts at node0. |
| invariants | Even hidden variables are independently checked. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocation in counters/phase. |
| cost | Fixed cursor setup per variable. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::connect_seed:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Locate a containing node and start its induced-subgraph walk. |
| inputs / outputs | Scan scope membership; first match seeds queue and variable stamp. |
| invariants | Variables with no containing node have no disconnected occurrences; valid query/native cover separately constrain usage. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Queue append can fail before stamps/cursors commit. |
| cost | One ordered scope lookup or one deque seed; scan may visit all nodes. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::connect_walk:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Traverse one parent/child adjacency containing the current variable. |
| inputs / outputs | Only unvisited containing neighbors enter queue; then advance saved adjacency offset. |
| invariants | Parent edges are included, so connected variable occurrences can meet through ancestors. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Queue insertion precedes stamp/offset change; lookup/allocator costs remain actual. |
| cost | One saved adjacency, ordered scope membership and possible deque append. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::connect_check:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a containing node missed by the induced walk. |
| inputs / outputs | One membership/stamp test at a time; first miss records connect violation. |
| invariants | A single witness per disconnected variable is enough to reject the candidate. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic append precedes clearing-phase selection. |
| cost | Up to all node scopes per variable plus ordered membership/diagnostic cost. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::connect_clear:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release the per-variable BFS frontier incrementally. |
| inputs / outputs | Pop one queued node, then advance variable after queue empties. |
| invariants | Old stamps are distinguished by variable number, avoiding a whole marker reset. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Pop/ID destruction does not allocate. |
| cost | One queue pop; total clearing follows reached nodes. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::head:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the unique head-variable set incrementally. |
| inputs / outputs | One ordered output variable inserted per step, then maximal_reserve. |
| invariants | Repeated output positions are deduplicated only for structural connex membership. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Set allocation can fail before output index advance. |
| cost | One ordered-set insertion with possible node allocation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::maximal_reserve:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund maximal-connex node-vector capacity. |
| inputs / outputs | reserve(node count), then maximal_start. |
| invariants | Safe tree topology bounds included nodes by this capacity. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Reserve failure leaves phase pending. |
| cost | Potentially large allocation; no claim that selected-step work bounds allocator time. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::maximal_start:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed the maximal allowed root-connected output subtree C*. |
| inputs / outputs | Insert checked root, start scope coverage. |
| invariants | Root scope may include hidden variables; no root-scope-subset-head restriction is invented. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Prior reserve makes this NodeId append nonallocating. |
| cost | Fixed reserved append and cursor setup. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::maximal_node:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the next C* node and begin its scope coverage. |
| inputs / outputs | When closure is complete, start head coverage verification. |
| invariants | Closure list contains only edges admitted by output-only separators. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocation in iterator setup. |
| cost | Fixed list/index/iterator reads. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::maximal_scope:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate one included node-scope variable. |
| inputs / outputs | Insert in covered, or start child scan at scope end. |
| invariants | Coverage union can contain hidden variables; only head coverage is required. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Set allocation precedes iterator advance. |
| cost | One ordered-set insertion; total follows included scope incidences. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::maximal_child:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one child separator eligibility scan. |
| inputs / outputs | Save child ID and reset output_only=true before maximal_separator. |
| invariants | Separators were computed independently during properties. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocation during cursor setup. |
| cost | Fixed child/separator iterator reads. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::maximal_separator:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a C* child exactly when its full separator lies in head. |
| inputs / outputs | One separator member tests head; completed eligible child appends to closure. |
| invariants | No hidden-variable crossing enters C*; empty separators pass. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Prior reserve makes successful child append nonallocating. |
| cost | One ordered head lookup or one fixed append/child advance. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::head_check:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test the local maximal-connex coverage lemma. |
| inputs / outputs | One head variable must be in covered; then optional supplied subtree checks. |
| invariants | Missing head coverage rejects connex without guessing a smaller subtree. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Violation allocation precedes iterator advance. |
| cost | One ordered coverage lookup and optional diagnostic. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::supplied_start:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decide whether a user-supplied connex list needs independent validation. |
| inputs / outputs | Absent list goes to height; present list starts IDs at0. |
| invariants | Computed C* and supplied list are separate evidence paths. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocation in this phase. |
| cost | Fixed optional check and cursor writes. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::supplied_ids:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate/deduplicate one supplied connex node ID. |
| inputs / outputs | Out-of-range/duplicate ID reports violation; valid unique ID enters supplied set. |
| invariants | Invalid IDs are never used to index node state. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Set/diagnostic allocation precedes list index advance. |
| cost | One range check and ordered lookup/insert, with allocation as needed. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::supplied_root:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require root inclusion in the supplied connected witness. |
| inputs / outputs | Append violation when missing; begin ordered supplied-node traversal. |
| invariants | A disconnected component cannot masquerade as a root-containing connex subtree. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic append precedes traversal iterator publication. |
| cost | One ordered membership query plus optional diagnostic. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::supplied_node:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the next valid supplied node or begin supplied head coverage. |
| inputs / outputs | Reads supplied iterator only after IDs are range-checked. |
| invariants | No invalid numeric ID reaches later parent/scope accesses. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocation in cursor/iterator setup. |
| cost | Fixed next-node selection. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::supplied_parent:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check root-connected parent closure of a supplied node. |
| inputs / outputs | A nonroot supplied node requires its computed parent in supplied. |
| invariants | Parent links come from verified topology, not a claimed list. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Violation allocation precedes separator cursor setup. |
| cost | One optional parent and ordered set lookup plus diagnostic. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::supplied_separator:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check each supplied node crosses only output-variable separators. |
| inputs / outputs | Missing head membership records connex_certificate and starts scope accumulation. |
| invariants | The root separator is empty; arbitrary supplied subsets still need every crossing checked. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic allocation precedes the early-finish phase switch. |
| cost | One ordered membership check per visited separator member. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::supplied_scope:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate supplied-witness scope coverage. |
| inputs / outputs | Insert one variable, or advance to the next supplied node. |
| invariants | No missing-parent correction is silently performed; earlier violations remain. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Set allocation precedes scope iterator advance. |
| cost | One ordered-set insertion with actual node allocation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::supplied_head:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the supplied witness independently covers every output variable. |
| inputs / outputs | One head membership in claimed_coverage, then height. |
| invariants | A valid maximal closure does not excuse a malformed supplied witness. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Violation allocation precedes head iterator advance. |
| cost | One ordered lookup and possible diagnostic per head variable. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::height:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the optional claimed native height with the computed exact value. |
| inputs / outputs | Nonmatching claim adds height violation, then export_prepare. |
| invariants | Both overclaims and underclaims reject; generalized nodes have weight0. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Diagnostic allocation precedes phase advance. |
| cost | Fixed optional/value comparison plus diagnostic construction. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::export_prepare:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve final report violation capacity before moving entries. |
| inputs / outputs | reserve pending violation count, then export_violation. |
| invariants | Prepared capacity prevents export-time vector relocation of diagnostic entries. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Allocation failure retains all pending deque entries. |
| cost | One potentially large reserve; bulk allocator work is outside fixed-time guarantees. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::export_violation:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move one prepared violation into the report. |
| inputs / outputs | Move deque front into reserved vector, then pop; empty queue selects publish. |
| invariants | Diagnostic strings move with their owner; no reference to a popped item escapes. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | Reserved default-allocator string/optional moves are nonallocating. |
| cost | One diagnostic move/pop; no whole-report copy in this stage. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::publish:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish valid-upper authority only after every rule succeeds. |
| inputs / outputs | If violations empty, allocate CheckedUpper first, then set report metrics/valid and authority; mark done. |
| invariants | No lower/optimum evidence is created; no throwing operation follows valid/authority publication. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | make_shared failure leaves report.valid and authority unpublished for retry. |
| cost | One authority allocation/refcount assembly on success; invalid result returns without it. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

```text
case Phase::done:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the stable completed upper-valid/invalid event. |
| inputs / outputs | Read result.valid without restarting any work. |
| invariants | No further report/tree/scratch mutation occurs after publication. |
| ownership | Uses immutable retained binding/tree and Impl-owned cursors/scratch/report; no caller-data borrow escapes. |
| failure | No allocating operation in the terminal read. |
| cost | Fixed event return; facade terminal-call policy remains separate. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0009

[Lines 428–429](../../../../../src/planner/verify.cpp#L428); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L428-L429:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0010

[Lines 430–432](../../../../../src/planner/verify.cpp#L430); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ValidationMachine::ValidationMachine(std::shared_ptr<const BindingData> binding,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the opaque validation owner without executing validation. |
| inputs / outputs | Moves immutable input handles into make_unique&lt;Impl&gt;. |
| invariants | Requires validated non-null binding and stable tree owners from the private caller. |
| ownership | Unique Impl plus shared inputs; no additional deep input copy. |
| failure | Allocation failure aborts construction; no checked report is published. |
| cost | Impl/empty report allocation and scalar setup, independent of graph traversal. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0011

[Lines 433–435](../../../../../src/planner/verify.cpp#L433); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ValidationMachine::~ValidationMachine() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release or transfer the private validation owner through default lifetime operations. |
| inputs / outputs | Destructor and adjacent default noexcept move operations. |
| invariants | A move transfers Impl; source methods require a live owner and are not moved-from probes. |
| ownership | Unique ownership prevents duplicate scratch deletion; shared input/evidence can outlive this machine. |
| failure | Destruction is nonthrowing; it can synchronously release last-owned query/tree/report containers. |
| cost | Move construction transfers one implementation pointer. Move assignment can synchronously destroy the destination's previous Impl before taking the source; that release, and destruction itself, can scale with retained scratch and any last-owned input/tree/report payload. These lifetime costs lie outside continuation steps. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0012

[Lines 436–436](../../../../../src/planner/verify.cpp#L436); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UnitResult ValidationMachine::step(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward one admitted context to the retained validation cursor. |
| inputs / outputs | Const UnitContext borrow to UnitResult. |
| invariants | Facade budgets are charged externally; this wrapper does not double-charge or revalidate admission. |
| ownership | Requires live data_; context is not retained. |
| failure | Propagates engine preparation exceptions and depth events unchanged. |
| cost | Fixed dispatch plus the selected phase actual cost; no extra owner/allocation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0013

[Lines 437–437](../../../../../src/planner/verify.cpp#L437); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ValidationReport& ValidationMachine::report()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the current report without copying diagnostic/separator collections. |
| inputs / outputs | Const reference to result, including not-yet-valid intermediate state. |
| invariants | Only a completed successful pass sets valid and checked height; incomplete scratch is not upper authority. |
| ownership | Reference requires report/machine owner lifetime; later steps may mutate it until publication. |
| failure | Declared noexcept, requiring a live unmoved machine. |
| cost | Fixed reference return; an explicit caller copy can allocate and copy all report data. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0014

[Lines 438–438](../../../../../src/planner/verify.cpp#L438); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const CheckedUpper> ValidationMachine::checked()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain completed valid-upper evidence independently of the machine. |
| inputs / outputs | Copies nullable shared authority handle. |
| invariants | Null until valid publication; invalid or incomplete verification never yields authority. |
| ownership | Successful handle retains input/tree/report after machine destruction. |
| failure | Declared noexcept; does not re-run any rule. |
| cost | Shared refcount copy without deep traversal or new control block; final owner teardown may be large. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0015

[Lines 439–444](../../../../../src/planner/verify.cpp#L439); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ValidationMachine::current_depth()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report active saved-frame nesting without counting breadth as depth. |
| inputs / outputs | Returns0 when inactive; otherwise max(1, reach frames). |
| invariants | One rule frame covers nonempty validation; BFS queues and stored nodes are width/storage, not additional simultaneous call frames. |
| ownership | Reads owned counters, returns independent scalar. |
| failure | Declared noexcept; initial depth denial leaves no active frame. |
| cost | Fixed size/max reads, no graph scan or allocation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0016

[Lines 445–447](../../../../../src/planner/verify.cpp#L445); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L445-L447:sha256:a9817cb666c3b5e9f1d31ea7ca16ade96612a4b664342c693deabb74bea1519a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | close crown::planner::continuation_detail and open crown::planner in src/planner/verify.cpp. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0017

[Lines 448–461](../../../../../src/planner/verify.cpp#L448); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ValidationReport validate_tree(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Offer blocking independent validation with explicit admission and result-export costs. |
| inputs / outputs | Catalog/query/tree borrows to an owning complete report. |
| invariants | Input validation is separate from tree-rule reports. Unlimited context drives the real machine, not a second validator; success is upper feasibility/height only. |
| ownership | Copies catalog/query/tree into retained owners, then copies the final legacy report out. |
| failure | Invalid input, admission/export allocation or engine allocation errors propagate; invalid tree structure returns violations. |
| cost | Input validation/deep copies, full machine traversal and allocating report export are blocking adapter work outside continuation quanta. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §3.2 Definitions 3.1–3.2 and native height](https://arxiv.org/pdf/2301.04003v2) |

## B0018

[Lines 462–462](../../../../../src/planner/verify.cpp#L462); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L462-L462:sha256:acb95521e5c8cc117a4f60f87ae076d39f48ab1ff02f31d3b8a4ada933fd3da0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |
