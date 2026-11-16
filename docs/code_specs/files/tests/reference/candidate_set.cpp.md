# `tests/reference/candidate_set.cpp` — block usage map

[Source](../../../../../tests/reference/candidate_set.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3ed5cca7e6c292e27427162296bf463340170e1eb47f3c2ffaa98cef414a2bb6`. 423 lines partitioned into 49 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/reference/candidate_set.cpp#L1) | Imports dependencies; declares namespace scope. | growth new · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../tests/reference/candidate_set.cpp#L15) | Type/record definition: struct StopRequest |  · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../tests/reference/candidate_set.cpp#L18) | Explanatory comments or spacing. |  |
| [B0004 · 19–22](../../../../../tests/reference/candidate_set.cpp#L19) | Type/record definition: struct Edge |  · [reviewed contract](#b0004) |
| [B0005 · 23–23](../../../../../tests/reference/candidate_set.cpp#L23) | Explanatory comments or spacing. |  |
| [B0006 · 24–27](../../../../../tests/reference/candidate_set.cpp#L24) | Type/record definition: struct RootedShape |  · [reviewed contract](#b0006) |
| [B0007 · 28–28](../../../../../tests/reference/candidate_set.cpp#L28) | Explanatory comments or spacing. |  |
| [B0008 · 29–72](../../../../../tests/reference/candidate_set.cpp#L29) | Callable definition: template &lt;class Charge&gt; \[\[nodiscard\]\] std::string signature_node(const FreeConnexTree& tree, NodeId id, Charge& charge) | calls charge, reserve, size, push_back; returns left &lt; right; encoded; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 73–73](../../../../../tests/reference/candidate_set.cpp#L73) | Explanatory comments or spacing. |  |
| [B0010 · 74–84](../../../../../tests/reference/candidate_set.cpp#L74) | Callable definition: template &lt;class Charge&gt; \[\[nodiscard\]\] std::string make_reference_signature(const FreeConnexTree& tree, Charge& charge) | calls signature_node, std::to_string, size; returns @; result_signature · [reviewed contract](#b0010) |
| [B0011 · 85–94](../../../../../tests/reference/candidate_set.cpp#L85) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 95–98](../../../../../tests/reference/candidate_set.cpp#L95) | Callable definition: Collector(const Catalog& source_catalog, const Query& source_query, std::size_t source_height, NormalFormCollectionLimits source_… | calls catalog, query, requested_height, limits · [reviewed contract](#b0012) |
| [B0013 · 99–99](../../../../../tests/reference/candidate_set.cpp#L99) | Explanatory comments or spacing. |  |
| [B0014 · 100–108](../../../../../tests/reference/candidate_set.cpp#L100) | Callable definition: void charge() | calls max · [reviewed contract](#b0014) |
| [B0015 · 109–109](../../../../../tests/reference/candidate_set.cpp#L109) | Explanatory comments or spacing. |  |
| [B0016 · 110–132](../../../../../tests/reference/candidate_set.cpp#L110) | Callable definition: void initialize_native_scopes() | calls size, reserve, charge, insert; growth insert, push_back, reserve; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 133–133](../../../../../tests/reference/candidate_set.cpp#L133) | Explanatory comments or spacing. |  |
| [B0018 · 134–145](../../../../../tests/reference/candidate_set.cpp#L134) | Callable definition: void collect_subsets(const std::vector&lt;VariableId&gt;& variables, std::size_t position, VariableSet& current, std::set&lt;VariableSet&gt;&… | calls charge, size, insert, erase; growth insert · [reviewed contract](#b0018) |
| [B0019 · 146–146](../../../../../tests/reference/candidate_set.cpp#L146) | Explanatory comments or spacing. |  |
| [B0020 · 147–155](../../../../../tests/reference/candidate_set.cpp#L147) | Callable definition: void build_scope_universe() | calls variables, begin, end, collect_subsets; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 156–156](../../../../../tests/reference/candidate_set.cpp#L156) | Explanatory comments or spacing. |  |
| [B0022 · 157–200](../../../../../tests/reference/candidate_set.cpp#L157) | Callable definition: \[\[nodiscard\]\] std::vector&lt;Edge&gt; decode_prufer(std::size_t node_count, const std::vector&lt;std::size_t&gt;& code) | calls charge, push_back, degree, reserve; returns edges; edges; growth push_back, reserve; 4 loop sites · [reviewed contract](#b0022) |
| [B0023 · 201–201](../../../../../tests/reference/candidate_set.cpp#L201) | Explanatory comments or spacing. |  |
| [B0024 · 202–213](../../../../../tests/reference/candidate_set.cpp#L202) | Callable definition: \[\[nodiscard\]\] bool advance_prufer(std::vector&lt;std::size_t&gt;& code, std::size_t base) | calls size, charge; returns true; false; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 214–214](../../../../../tests/reference/candidate_set.cpp#L214) | Explanatory comments or spacing. |  |
| [B0026 · 215–257](../../../../../tests/reference/candidate_set.cpp#L215) | Callable definition: \[\[nodiscard\]\] RootedShape orient(const std::vector&lt;Edge&gt;& edges, std::size_t node_count, std::size_t root) | calls adjacency, charge, push_back, std::sort; returns shape; growth push_back, reserve, resize; 6 loop sites · [reviewed contract](#b0026) |
| [B0027 · 258–258](../../../../../tests/reference/candidate_set.cpp#L258) | Explanatory comments or spacing. |  |
| [B0028 · 259–273](../../../../../tests/reference/candidate_set.cpp#L259) | Callable definition: \[\[nodiscard\]\] bool is_normal_form(const RootedShape& shape, std::size_t native_count) | calls size, charge, empty; returns false; false; 2 loop sites · [reviewed contract](#b0028) |
| [B0029 · 274–274](../../../../../tests/reference/candidate_set.cpp#L274) | Explanatory comments or spacing. |  |
| [B0030 · 275–296](../../../../../tests/reference/candidate_set.cpp#L275) | Callable definition: \[\[nodiscard\]\] FreeConnexTree make_tree(const RootedShape& shape, std::size_t root, const std::vector&lt;VariableSet&gt;& generalized_sc… | calls size, reserve, charge, std::to_string; returns tree; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0030) |
| [B0031 · 297–297](../../../../../tests/reference/candidate_set.cpp#L297) | Explanatory comments or spacing. |  |
| [B0032 · 298–301](../../../../../tests/reference/candidate_set.cpp#L298) | Callable definition: \[\[nodiscard\]\] std::string structural_signature(const FreeConnexTree& tree) | calls charge, crown::reference::make_reference_signature; returns ::crown::reference::make_reference_signature(tree, meter) · [reviewed contract](#b0032) |
| [B0033 · 302–302](../../../../../tests/reference/candidate_set.cpp#L302) | Explanatory comments or spacing. |  |
| [B0034 · 303–319](../../../../../tests/reference/candidate_set.cpp#L303) | Callable definition: void consider(FreeConnexTree tree) | calls charge, planner::validate_tree, structural_signature, push_back; growth push_back; 1 loop sites; source comment (unverified): // Claims are copied only from this successful P02 report. They are not · [reviewed contract](#b0034) |
| [B0035 · 320–320](../../../../../tests/reference/candidate_set.cpp#L320) | Explanatory comments or spacing. |  |
| [B0036 · 321–335](../../../../../tests/reference/candidate_set.cpp#L321) | Callable definition: void assign_generalized_scopes(const RootedShape& shape, std::size_t root, std::size_t generalized_count, std::vector&lt;VariableSet… | calls charge, consider, make_tree; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 336–336](../../../../../tests/reference/candidate_set.cpp#L336) | Explanatory comments or spacing. |  |
| [B0038 · 337–349](../../../../../tests/reference/candidate_set.cpp#L337) | Callable definition: void consider_rooted_topology(const std::vector&lt;Edge&gt;& edges, std::size_t node_count, std::size_t root, std::size_t generalized_c… | calls charge, orient, is_normal_form, size · [reviewed contract](#b0038) |
| [B0039 · 350–350](../../../../../tests/reference/candidate_set.cpp#L350) | Explanatory comments or spacing. |  |
| [B0040 · 351–370](../../../../../tests/reference/candidate_set.cpp#L351) | Callable definition: void enumerate_generalized_count(std::size_t generalized_count) | calls size, max, std::logic_error, code; 2 loop sites · [reviewed contract](#b0040) |
| [B0041 · 371–371](../../../../../tests/reference/candidate_set.cpp#L371) | Explanatory comments or spacing. |  |
| [B0042 · 372–376](../../../../../tests/reference/candidate_set.cpp#L372) | Callable definition: void collect_empty_body() | calls consider, std::move · [reviewed contract](#b0042) |
| [B0043 · 377–377](../../../../../tests/reference/candidate_set.cpp#L377) | Explanatory comments or spacing. |  |
| [B0044 · 378–391](../../../../../tests/reference/candidate_set.cpp#L378) | Callable definition: void run() | calls initialize_native_scopes, empty, collect_empty_body, size; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 392–395](../../../../../tests/reference/candidate_set.cpp#L392) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0045) |
| [B0046 · 396–399](../../../../../tests/reference/candidate_set.cpp#L396) | Callable definition: std::string normal_form_reference_signature(const FreeConnexTree& checked_tree) | calls make_reference_signature; returns make_reference_signature(checked_tree, no_charge) · [reviewed contract](#b0046) |
| [B0047 · 400–400](../../../../../tests/reference/candidate_set.cpp#L400) | Explanatory comments or spacing. |  |
| [B0048 · 401–421](../../../../../tests/reference/candidate_set.cpp#L401) | Callable definition: NormalFormCollectionResult collect_normal_form_plan_set( const Catalog& catalog, const Query& query, std::size_t supplied_native_… | calls run, std::move; returns std::move(collector.result) · [reviewed contract](#b0048) |
| [B0049 · 422–423](../../../../../tests/reference/candidate_set.cpp#L422) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::reference · [reviewed contract](#b0049) |

## B0001

[Lines 1–14](../../../../../tests/reference/candidate_set.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:020486350ebac55be618250c39a1103b7e5c01ab0ea30949ae8d2de0f12b3ad1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidate_set.cpp: include "candidate_set.hpp", "crown/planner/verify.hpp", &lt;algorithm&gt;, &lt;limits&gt;, &lt;new&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;utility&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–17](../../../../../tests/reference/candidate_set.cpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StopRequest {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carries the reason for an internal collector stop through private recursion. |
| inputs / outputs | One NormalFormCollectionStop value in; private StopRequest thrown by a helper. |
| invariants | Only the public collection wrapper catches this sentinel and marks the prefix resource-limited, incomplete. |
| ownership | Stores one enum; owns no query, tree or result. |
| failure | Only matching StopRequest is translated; unrelated exception types are not handled here. |
| cost | Fixed-size enum and unwinding; no container work. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 19–22](../../../../../tests/reference/candidate_set.cpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Edge {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represents one unlabeled-by-query undirected topology edge before rooting. |
| inputs / outputs | Two size_t node labels in; one private edge value out. |
| invariants | Labels must be in the current internal node range; external IDs are not represented. |
| ownership | Copied in local edge vectors for one topology. |
| failure | Does not validate endpoints; downstream orient assumes decoder output. |
| cost | Two indices per edge plus vector storage. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 24–27](../../../../../tests/reference/candidate_set.cpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RootedShape {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carries one root-oriented child list and its maximum native depth. |
| inputs / outputs | Nested child labels and native_height in/out of orient. |
| invariants | Native depth counts labels below native_scopes.size(); root and children describe one rooted tree. |
| ownership | Owns per-topology nested vectors; never published directly. |
| failure | Bad internal topology is rejected by orient; this record adds no checks. |
| cost | O(nodes+edges) shape storage and repeated construction per root. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0008

[Lines 29–72](../../../../../tests/reference/candidate_set.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Charge>
[[nodiscard]] std::string signature_node(const FreeConnexTree& tree, NodeId id, Charge& charge) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds the recursive node portion of the independent canonical structure signature. |
| inputs / outputs | Tree, node ID and charge callback in; framed kind/occurrence/scope/sorted-child string out. |
| invariants | Display IDs and claimed fields are ignored; scope order is retained and child signatures are sorted. The caller must supply a P02-validated tree for the intended Catalog/Query binding; recursion follows child NodeIds directly. |
| ownership | Borrows tree and callback; temporary and returned strings own normal string allocations. |
| failure | The helper does not validate node IDs or detect cycles. Callback and allocation failures propagate; invalid IDs can access out of bounds and cyclic child graphs can recurse without termination. |
| cost | Visits nodes/scope/children and sorts child tokens; recursion, string bytes and allocation are not independently capped. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0010

[Lines 74–84](../../../../../tests/reference/candidate_set.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Charge>
[[nodiscard]] std::string make_reference_signature(const FreeConnexTree& tree, Charge& charge) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adds the NFREF1 outer frame and distinct empty-tree marker to a structural signature. |
| inputs / outputs | Tree and charge callback in; deterministic string out. |
| invariants | Empty root yields NFREF1&lt;EMPTY:0&gt; without charge; nonempty form length-frames the root token. Caller must have checked the tree. |
| ownership | Borrows tree/callback and owns returned string plus temporary root string. |
| failure | No validation or binding identity; unchecked recursive indexing and callback/allocation failures remain possible. |
| cost | Empty case is fixed work; nonempty serializes/sorts/allocates through signature_node. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0011

[Lines 85–94](../../../../../tests/reference/candidate_set.cpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L94:sha256:5712d240cf6c5a8ab5e4562e72f7c22020871eb6aa4f718d3bf65f9824e81683
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidate_set.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 95–98](../../../../../tests/reference/candidate_set.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Collector(const Catalog& source_catalog, const Query& source_query,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initializes one collector for a specific borrowed binding, requested height and limits. |
| inputs / outputs | Catalog and Query references, height and NormalFormCollectionLimits in. |
| invariants | P02 receives the same Catalog/Query; height is an exact enumeration filter. |
| ownership | Catalog/Query are borrowed for the collection call; Collector owns result and scratch containers. |
| failure | Does not validate inputs at construction; reference lifetime is caller responsibility. |
| cost | Scalar initialization and empty standard containers; no deep binding copy. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0014

[Lines 100–108](../../../../../tests/reference/candidate_set.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void charge() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charges a reference transition and requests stop at overflow or configured work cap. |
| inputs / outputs | Reads result.work_units/limits; increments only when allowed. |
| invariants | Checks uint64 overflow first; reaching max_work_units stops before increment; validate_tree is counted as one transition, not internally metered. |
| ownership | Mutates collector-owned counter only. |
| failure | Throws private work_counter_overflow or work_limit sentinel; wrapper returns incomplete resource-limited prefix. |
| cost | Constant checks per charge; no bound on CPU, allocations, sorts or internal P02 effort. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0016

[Lines 110–132](../../../../../tests/reference/candidate_set.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void initialize_native_scopes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds each native atom scope and enforces the reference-only small arity caps. |
| inputs / outputs | Borrowed Query atoms/terms in; VariableSet entries in native_scopes. |
| invariants | At most 3 native occurrences and 3 distinct active variables; charges atoms and terms; constants and ignored terms are not variables. |
| ownership | Copies variable IDs into collector-owned sets. |
| failure | Exceeding caps is a resource stop, not semantic unsupported; work stop may leave only private partial scratch. |
| cost | Scans terms and ordered-set inserts; caps constrain this routine but do not promise allocation-free work. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0018

[Lines 134–145](../../../../../tests/reference/candidate_set.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void collect_subsets(const std::vector<VariableId>& variables, std::size_t position,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerates each native scope powerset into a deduplicating ordered set. |
| inputs / outputs | Variable vector, recursion position, mutable current set, destination set in. |
| invariants | Each recursive entry is charged; terminal state inserts one subset; include/exclude branches cover all subsets. |
| ownership | Borrows the variable vector and mutable working/destination sets. On normal completion each include branch erases its working variable; a thrown stop/allocation error can leave this private scratch partially modified. The destination owns copied subset keys. |
| failure | Work/allocation/container stops can leave the collector scratch prefix partial; public wrapper catches only configured types. |
| cost | 2^(k+1)-1 recursion entries for width k plus set costs; active-variable cap limits k to 3. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0020

[Lines 147–155](../../../../../tests/reference/candidate_set.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void build_scope_universe() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds the sorted union of all native-scope subsets for generalized scope assignment. |
| inputs / outputs | Reads native_scopes; writes scope_universe from a temporary ordered set. |
| invariants | Includes empty scope and deduplicates equal subsets across occurrences; called only for multiple native scopes. |
| ownership | Temporary set/variable vectors are local; scope_universe owns copied scopes. |
| failure | Resource stop interrupts construction; allocation and length errors reach the public wrapper. |
| cost | Repeats powerset traversal per scope, then stores the unique union; set and vector allocations are outside work_units. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0022

[Lines 157–200](../../../../../tests/reference/candidate_set.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] std::vector<Edge> decode_prufer(std::size_t node_count,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decodes one internal Prüfer sequence into an owning edge list. |
| inputs / outputs | node_count and code vector in; edge vector out. |
| invariants | 1 node gives no edge, 2 nodes gives their single edge; larger trees use ascending leaves and generated digits. |
| ownership | Owns degree scratch and returned edge vector. |
| failure | Unexpected incomplete sequence state throws logic_error; work/allocation failures propagate to the wrapper. |
| cost | Repeated leaf scans can be O(n²) per code; charged transitions do not include all allocation/sort costs. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0024

[Lines 202–213](../../../../../tests/reference/candidate_set.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] bool advance_prufer(std::vector<std::size_t>& code, std::size_t base) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advances the internal Prüfer digit vector in base node_count. |
| inputs / outputs | Mutable code and base in; bool says whether another code exists. |
| invariants | Rightmost digit advances first; carry resets digits to zero; each examined digit is charged. |
| ownership | Mutates caller-owned code only. |
| failure | Work stop may interrupt a carry; digits are trusted because Collector created them. |
| cost | At most code.size() charged inspections per call; total number of codes is combinatorial. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0026

[Lines 215–257](../../../../../tests/reference/candidate_set.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] RootedShape orient(const std::vector<Edge>& edges, std::size_t node_count,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Orients one decoded edge list from a chosen root and computes native height. |
| inputs / outputs | Edges, node_count, root in; RootedShape out. |
| invariants | Sorts neighbors; traversal assigns each node once; throws if graph is repeated/disconnected; native label means index below native scope count. |
| ownership | Owns adjacency, parent, order, depth and returned shape vectors for this call. |
| failure | Endpoint/root indexing is unchecked; logic_error detects visited duplicate or disconnected decoder output; resource stops propagate. |
| cost | Builds/sorts adjacency and traverses edges/nodes; sorting and vector allocations are not charged. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0028

[Lines 259–273](../../../../../tests/reference/candidate_set.cpp#L259); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] bool is_normal_form(const RootedShape& shape, std::size_t native_count) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rejects rooted shapes outside the enumerator’s literal normal-form and requested-height family. |
| inputs / outputs | RootedShape and native_count in; bool out. |
| invariants | Generalized nodes cannot be leaves and need at least two children; native children must be native; native_height must equal requested height. |
| ownership | Borrows shape; returns no state. |
| failure | Assumes internal child labels are valid; does not perform P02 or tree validation. |
| cost | Scans nodes and native child edges with charges, repeated for every topology/root. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0030

[Lines 275–296](../../../../../tests/reference/candidate_set.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] FreeConnexTree make_tree(const RootedShape& shape, std::size_t root,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materializes a rooted shape and chosen generalized scopes as a FreeConnexTree draft. |
| inputs / outputs | Shape, root and generalized-scope assignment in; native-first tree out. |
| invariants | Native labels map to occurrence indices and native scopes; remaining labels use assigned generalized scopes; display IDs are reference-node-N. |
| ownership | Returned tree/nested containers own copies; source vectors are borrowed during build. |
| failure | Assumes internal assignment lengths and labels match; charge/allocation failure can abort draft construction. |
| cost | Copies O(nodes+edges+scope entries); charges visits, not allocated bytes. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0032

[Lines 298–301](../../../../../tests/reference/candidate_set.cpp#L298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] std::string structural_signature(const FreeConnexTree& tree) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs the shared reference serializer with Collector::charge as its meter. |
| inputs / outputs | Tree in; string signature out. |
| invariants | Uses same framing as public helper; adds no catalog/query identity. |
| ownership | Borrows tree/Collector; result string owns bytes. |
| failure | No validation; callback, string and unchecked-index failures propagate. |
| cost | Charges recursive node visits, scope entries, child appends and each child-signature sort comparator through Collector::charge. Full string-comparison bytes, formatting/copying, allocations and CPU are not individually metered; orient adjacency sorts are a separate uncharged operation. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0034

[Lines 303–319](../../../../../tests/reference/candidate_set.cpp#L303); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void consider(FreeConnexTree tree) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validates a draft against original binding, checks exact height, signs, deduplicates and publishes it. |
| inputs / outputs | Owns draft by value; may append NormalFormReferencePlan to result. |
| invariants | Only valid P02 trees at requested height retained; trusted claims copied only after P02; claims excluded from signature; first duplicate remains. |
| ownership | Collector owns retained signature/tree; binding is borrowed. |
| failure | Invalid or wrong-height candidate is filtered; work, bad_alloc and length_error become resource stops outside; other exceptions escape. |
| cost | One charge wraps full validate_tree; signature work charged; duplicate check is linear in current result count; containers allocate. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0036

[Lines 321–335](../../../../../tests/reference/candidate_set.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void assign_generalized_scopes(const RootedShape& shape, std::size_t root,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerates the Cartesian product of scope_universe for generalized nodes. |
| inputs / outputs | Shape/root/g count plus mutable assignment and position in. |
| invariants | Charges recursive entry and each scope choice; calls make_tree/consider only after all g slots assigned. |
| ownership | Borrows shape; mutates caller assignment; published plan owns its copies. |
| failure | Stop/allocation interruption publishes only completed assignments. |
| cost | U^g assignments plus recursive frames and per-assignment P02/signature/dedup; no allocation-free guarantee. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0038

[Lines 337–349](../../../../../tests/reference/candidate_set.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void consider_rooted_topology(const std::vector<Edge>& edges, std::size_t node_count,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Orients one topology/root, applies structural filters and delegates scope combinations. |
| inputs / outputs | Edge list, node count, root and generalized count in. |
| invariants | For each topology code that completes, the loop considers every root unless a configured stop interrupts it; exact height/normal-form filtering precedes tree validation; generalized_count=0 directly considers a tree. |
| ownership | Borrows edges; local shape/assignment scratch. |
| failure | Invalid internal graph throws; work/allocation stops propagate; filtered shape returns normally. |
| cost | Creates and sorts adjacency for each root; generalized scope products and P02 add further work. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0040

[Lines 351–370](../../../../../tests/reference/candidate_set.cpp#L351); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void enumerate_generalized_count(std::size_t generalized_count) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerates all generated topology codes and roots for one generalized-node count. |
| inputs / outputs | Generalized count in; iterates node_count = native_count + g. |
| invariants | Checks size_t addition overflow; zero nodes is an internal logic error; code length n-2 for n&gt;2; requested height only filters later. |
| ownership | Owns code and per-code edge vector; result accumulates in Collector. |
| failure | Overflow is resource stop; logic_error and unsupported exception types escape public wrapper; configured stops return prefix. |
| cost | For n&gt;2 visits n^(n-2) Prüfer codes times n roots, multiplied by scope products and validation; combinatorial, not a proof search budget. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0042

[Lines 372–376](../../../../../tests/reference/candidate_set.cpp#L372); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void collect_empty_body() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Handles the empty-body family as one empty-tree candidate. |
| inputs / outputs | No inputs; constructs empty FreeConnexTree and calls consider. |
| invariants | Marks exhausted only if candidate consideration returns normally; P02/requested-height still applies. |
| ownership | Moves empty draft into consider; retained member belongs to result. |
| failure | Any stop prevents completion and is handled by public wrapper. |
| cost | No topology generation; one validation/signature path for the empty member. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0044

[Lines 378–391](../../../../../tests/reference/candidate_set.cpp#L378); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Coordinates native scope setup, empty-body handling and every generalized-count pass. |
| inputs / outputs | Uses borrowed binding, requested height and limits; mutates Collector result/scratch. |
| invariants | Empty atom list takes dedicated branch; otherwise g is 0 through native_count-1; scope universe built only for more than one native; exhausted is set after full traversal. |
| ownership | Scratch/results owned by Collector; Catalog/Query borrowed. |
| failure | Thrown stop prevents final exhausted assignment; wrapper marks partial result incomplete. |
| cost | Combines powersets, Prüfer sequences, roots, scope products, P02, signatures and dedup; height does not cap enumeration. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0045

[Lines 392–395](../../../../../tests/reference/candidate_set.cpp#L392); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L392-L395:sha256:cd0be991c0e1227a9d4bda3b7413c8ccc8481f5f91e813f497c05045b8c8c8d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in candidate_set.cpp: struct Collector, namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0046

[Lines 396–399](../../../../../tests/reference/candidate_set.cpp#L396); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string normal_form_reference_signature(const FreeConnexTree& checked_tree) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exposes the unmetered structural signature helper for caller-checked trees. |
| inputs / outputs | A FreeConnexTree caller has already accepted with P02; returns signature string. |
| invariants | The helper itself does not validate or bind the tree; signature is not a global key/proof and excludes query identity. |
| ownership | Borrows input tree; owns returned string. |
| failure | Unchecked indexing/recursive allocation failures are not translated here. |
| cost | No work cap; recursion, sort and string allocations still occur. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0048

[Lines 401–421](../../../../../tests/reference/candidate_set.cpp#L401); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NormalFormCollectionResult collect_normal_form_plan_set(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Returns a bounded prefix or completed literal normal-form family for one requested height. |
| inputs / outputs | Borrowed Catalog/Query, height and work limits in; result owns plans/signatures/counters/status. |
| invariants | This is a synchronous blocking collector with no saved cursor. Native-occurrence and distinct active-variable caps are each 3, and the default reference-transition cap is 5,000,000. Hitting a work/cap/allocation/container stop returns a partial prefix with exhausted=false and resource_limited=true. Requested height filters the literal family; it proves neither feasibility nor minimum height nor global cost optimality. Exhausted means this finite requested-height generator finished. |
| ownership | Catalog/Query must outlive call; Collector scratch dies; returned plans own trees and strings. |
| failure | Catches internal StopRequest, bad_alloc, length_error into incomplete resource-limited result; other exceptions propagate. |
| cost | Combinatorial generation; validate_tree counts as one transition; CPU, allocations, sorted adjacency, bytes and wall time are not measured. |
| Design | [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/unit/candidates_test.cpp](../../../../../tests/unit/candidates_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0049

[Lines 422–423](../../../../../tests/reference/candidate_set.cpp#L422); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L422-L423:sha256:eb4a6d7eca0fbb1ee325a62b521f86ac21994585cdfc1ad5076d9f90286d82dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in candidate_set.cpp: namespace crown::reference. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |
