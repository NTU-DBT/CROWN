# `src/planner/ranking_payload.cpp` — block usage map

[Source](../../../../../src/planner/ranking_payload.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `1312b1669dd0bc1ed1b927e3aa6784d220111feec702488cb60cca9fffac08f3`. 146 lines partitioned into 28 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/planner/ranking_payload.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../src/planner/ranking_payload.cpp#L8) | Callable definition: template&lt;class T&gt; void fixed(Budget& b) | calls work, bytes · [reviewed contract](#b0002) |
| [B0003 · 9–10](../../../../../src/planner/ranking_payload.cpp#L9) | Explanatory comments or spacing. | source comment (unverified): // Owned-type component sizes are a conservative logical payload model. · [reviewed contract](#b0003) |
| [B0004 · 11–11](../../../../../src/planner/ranking_payload.cpp#L11) | Callable definition: template&lt;class Range&gt; void sequence(const Range& v,Budget& b) | calls work, size; source comment (unverified): // Owned-type component sizes are a conservative logical payload model. · [reviewed contract](#b0004) |
| [B0005 · 12–12](../../../../../src/planner/ranking_payload.cpp#L12) | Callable definition: void string(std::string_view s,Budget& b) | calls work, size, bytes · [reviewed contract](#b0005) |
| [B0006 · 13–17](../../../../../src/planner/ranking_payload.cpp#L13) | Callable definition: template&lt;class Scalar&gt; void scalar(const Scalar& value,Budget& b) | calls work, index, string, bytes; source comment (unverified): // Both scalar representations own an exact coefficient of at most38 digits. · [reviewed contract](#b0006) |
| [B0007 · 18–18](../../../../../src/planner/ranking_payload.cpp#L18) | Callable definition: template&lt;class Range&gt; void variables(const Range& v,Budget& b) | calls work, size · [reviewed contract](#b0007) |
| [B0008 · 19–26](../../../../../src/planner/ranking_payload.cpp#L19) | Callable definition: template&lt;class CatalogView&gt; void catalog(const CatalogView& c,Budget& b) | calls sequence, string, std::visit, constexpr; 5 loop sites · [reviewed contract](#b0008) |
| [B0009 · 27–31](../../../../../src/planner/ranking_payload.cpp#L27) | Callable definition: template&lt;class QueryView&gt; void query(const QueryView& q,Budget& b) | calls sequence, string, scalar; 4 loop sites · [reviewed contract](#b0009) |
| [B0010 · 32–35](../../../../../src/planner/ranking_payload.cpp#L32) | Callable definition: template&lt;class TreeView&gt; void tree(const TreeView& t,Budget& b) | calls sequence, string, variables; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 36–37](../../../../../src/planner/ranking_payload.cpp#L36) | Explanatory comments or spacing. | source comment (unverified): // Walk the full bound/core/adapter program, including literal/string bytes; · [reviewed contract](#b0011) |
| [B0012 · 38–50](../../../../../src/planner/ranking_payload.cpp#L38) | Callable definition: template&lt;class NormalizedView&gt; void normalized(const NormalizedView& n,Budget& b) | calls catalog, string, sequence, scalar; 10 loop sites; source comment (unverified): // Walk the full bound/core/adapter program, including literal/string bytes; · [reviewed contract](#b0012) |
| [B0013 · 51–52](../../../../../src/planner/ranking_payload.cpp#L51) | Explanatory comments or spacing. | source comment (unverified): // A bounded iterative visitor; even the scratch pointer inventory is charged. · [reviewed contract](#b0013) |
| [B0014 · 53–56](../../../../../src/planner/ranking_payload.cpp#L53) | Callable definition: template&lt;class T,class Function&gt; void pending_stack(T root,Budget& b,Function visit) | calls pending, push_back, visit; growth push_back; source comment (unverified): // A bounded iterative visitor; even the scratch pointer inventory is charged. · [reviewed contract](#b0014) |
| [B0015 · 57–71](../../../../../src/planner/ranking_payload.cpp#L57) | Callable definition: void canonical(const io::Json& root,Budget& b) | calls pending_stack, empty, back, pop_back; growth push_back; 3 loop sites · [reviewed contract](#b0015) |
| [B0016 · 72–84](../../../../../src/planner/ranking_payload.cpp#L72) | Callable definition: void canonical(program::JsonView root,Budget& b) | calls static_assert, pending_stack, empty, back; guard static_assert(sizeof(program::JsonView)==sizeof(const io::Json*));; growth push_back; 3 loop sites · [reviewed contract](#b0016) |
| [B0017 · 85–88](../../../../../src/planner/ranking_payload.cpp#L85) | Callable definition: template&lt;class IdentityView&gt; void identity(const IdentityView& id,Budget& b) | calls canonical, string, sequence · [reviewed contract](#b0017) |
| [B0018 · 89–89](../../../../../src/planner/ranking_payload.cpp#L89) | Callable definition: template&lt;class P&gt; void projection(const P& p,Budget& b) | calls sequence, fields · [reviewed contract](#b0018) |
| [B0019 · 90–90](../../../../../src/planner/ranking_payload.cpp#L90) | Callable definition: template&lt;class Range&gt; void strings(const Range& values,Budget& b) | calls sequence, string; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 91–92](../../../../../src/planner/ranking_payload.cpp#L91) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0020) |
| [B0021 · 93–93](../../../../../src/planner/ranking_payload.cpp#L93) | Callable definition: void plan_identity_payload(const program::QueryIdentity& value,Budget& budget) | calls identity · [reviewed contract](#b0021) |
| [B0022 · 94–102](../../../../../src/planner/ranking_payload.cpp#L94) | Callable definition: template&lt;class Plan&gt; void plan_source_payload_impl(const MinimumHeightCandidate& c,const Plan& basis,Budget& b) | calls catalog, query, tree, normalized; source comment (unverified): // Exact binding, identical owned program and options give the same semantic · [reviewed contract](#b0022) |
| [B0023 · 103–103](../../../../../src/planner/ranking_payload.cpp#L103) | Callable definition: void plan_source_payload(const MinimumHeightCandidate& c,const CompiledProgram& p,Budget& b) | calls plan_source_payload_impl · [reviewed contract](#b0023) |
| [B0024 · 104–104](../../../../../src/planner/ranking_payload.cpp#L104) | Callable definition: void plan_source_payload(const MinimumHeightCandidate& c,const PhysicalPlan& p,Budget& b) | calls plan_source_payload_impl · [reviewed contract](#b0024) |
| [B0025 · 105–133](../../../../../src/planner/ranking_payload.cpp#L105) | Callable definition: template&lt;class Plan&gt; void plan_compiled_payload_impl(const Plan& p,Budget& b) | calls options, string, guarantee, strings; 10 loop sites; source comment (unverified): // Compiler-owned descriptors also retain stable read-only ranges/context · [reviewed contract](#b0025) |
| [B0026 · 134–134](../../../../../src/planner/ranking_payload.cpp#L134) | Callable definition: void plan_compiled_payload(const PhysicalPlan& p,Budget& b) | calls plan_compiled_payload_impl · [reviewed contract](#b0026) |
| [B0027 · 135–145](../../../../../src/planner/ranking_payload.cpp#L135) | Callable definition: void plan_compiled_payload(const CompiledProgram& p,Budget& b) | calls plan_compiled_payload_impl, input_preparation_limits, input_preparation, work · [reviewed contract](#b0027) |
| [B0028 · 146–146](../../../../../src/planner/ranking_payload.cpp#L146) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::ranking::detail · [reviewed contract](#b0028) |

## B0001

[Lines 1–7](../../../../../src/planner/ranking_payload.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:38bec30a8b57bb9a06b9e9883611faa29ad9a61a8f5b94a74c8525dff147d009
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "ranking_payload.hpp", #include "compiled_source.hpp", #include &lt;type_traits&gt;, #include &lt;variant&gt; available to src/planner/ranking_payload.cpp; open crown::planner::ranking::detail and anonymous helper namespace. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/ranking_payload.cpp](../../../../../src/planner/ranking_payload.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0002

[Lines 8–8](../../../../../src/planner/ranking_payload.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void fixed(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge a fixed logical object component. |
| inputs / outputs | One work and sizeof(T) payload debit. |
| invariants | Models object component size, not a new allocation or retained capacity. |
| ownership | Uses T only in sizeof and mutates the borrowed Budget; no T object/source payload or worklist is constructed. |
| failure | Budget work/clock/payload Failure propagates; there is no source traversal or scratch allocation in fixed. |
| cost | Fixed debit bookkeeping. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 9–10](../../../../../src/planner/ranking_payload.cpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L10:sha256:702458a0a1c06580c6ace1e3a3bcdf8f5008eeab9c259c3e0d3eb28d54c493fd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for size: Owned-type component sizes are a conservative logical payload model. Capacity, allocator nodes/control blocks and peak coexistence are separate. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies size; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for size come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/ranking_payload.cpp](../../../../../src/planner/ranking_payload.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0004

[Lines 11–11](../../../../../src/planner/ranking_payload.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> void sequence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge logical sequence elements using their mapped owning DTO type. |
| inputs / outputs | Work(size), then vector_items&lt;OwnedType&lt;value_type&gt;&gt;(size). |
| invariants | No capacity/node/controlblock estimate; borrowed native views use explicit owned-type mapping. |
| ownership | Borrows the range to read size and mutates Budget; mapped element type is compile-time metadata, not an allocated vector. |
| failure | Budget work/clock/cell/payload Failure propagates with earlier debits retained; sequence does not copy elements or allocate scratch. |
| cost | Fixed operations with size-proportional logical charge; elements visited separately by caller. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 12–12](../../../../../src/planner/ranking_payload.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void string(std::string_view
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge a logical string payload. |
| inputs / outputs | Work(length) then bytes(length). |
| invariants | Does not copy/allocate the string or measure its spare capacity. |
| ownership | Borrows string_view length metadata and mutates Budget; no character copy, byte traversal or scratch owner is created. |
| failure | Budget work/clock/payload Failure propagates; this helper does not allocate text or a worklist. |
| cost | Constant metadata access plus logical length debit. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 13–17](../../../../../src/planner/ranking_payload.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Scalar> void scalar(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge variable payload of the admitted scalar variant. |
| inputs / outputs | One base work; strings charge actual bytes, Decimal charges conservative38coefficientbytes. |
| invariants | Both DTO/native scalar variant layouts have string tag1, Decimal tag4 and at most38coefficientdigits. |
| ownership | Borrows the admitted scalar variant, reads its tag/string length and mutates Budget; no scalar export or scratch worklist is created. |
| failure | Budget work/clock/payload Failure propagates; admitted variant ordering is a precondition, and this helper performs no allocation. |
| cost | Fixed tag dispatch plus string-length metadata; Decimal conservative constant allowance. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 18–18](../../../../../src/planner/ranking_payload.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> void variables(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge one variable-ID sequence. |
| inputs / outputs | Work(size) and vector_items&lt;VariableId&gt;(size). |
| invariants | Variable scope logical content differs from ordered-container/tree node overhead. |
| ownership | Borrows container size and mutates Budget; no variable vector/set is constructed or retained. |
| failure | Budget work/clock/cell/payload Failure propagates; no variable-element copy or scratch allocation occurs. |
| cost | Fixed bookkeeping; logical charge linear in length. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 19–26](../../../../../src/planner/ranking_payload.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> void catalog(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit owned catalog payload components. |
| inputs / outputs | Tables/names/columns, constraint names/column arrays/foreign targets, distinct-count columns and key-hint reasons. |
| invariants | Already admitted typed catalog; this charges data and does not validate or canonicalize identities. |
| ownership | Borrows admitted catalog records/length metadata and mutates Budget; does not copy names/arrays or create a JSON worklist. |
| failure | Budget failures propagate with prior debits retained; valid typed catalog traversal performs no scratch allocation. |
| cost | Visits table/column/constraint/distinct-estimate/hint records. String and column-ID array lengths give bulk logical debits from metadata; this visitor does not scan/copy their characters or every selector element. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 27–31](../../../../../src/planner/ranking_payload.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class QueryView> void query(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit query model payload components. |
| inputs / outputs | Variables/names, atoms/occurrences/terms/scalar constants and head aliases. |
| invariants | Does not treat display names or this byte model as a new query binding token. |
| ownership | Borrows admitted query/term/scalar records and their length metadata, mutating only Budget; creates no owned model or JSON worklist. |
| failure | Budget failures propagate with prior debits retained; valid typed query traversal performs no scratch allocation. |
| cost | Visits variable/atom/term/head records. String widths and bounded Decimal payloads are logical debits; no character copy/scan or model allocation occurs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 32–35](../../../../../src/planner/ranking_payload.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class TreeView> void tree(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit proposed tree payload components. |
| inputs / outputs | Nodes/IDs/scopes/children and optional separator/connex claims. |
| invariants | Charges claims as stored; validation/proof authority remains elsewhere. |
| ownership | Borrows admitted tree records and size metadata, mutating only Budget; does not copy scopes/children or construct a traversal worklist. |
| failure | Budget failures propagate with prior debits retained; this sizing visitor does not allocate tree/JSON scratch or validate topology. |
| cost | Visits nodes and optional claim presence. Scope/child/connex counts are read from container metadata and debited in bulk; this visitor does not traverse tree edges or copy node text. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 36–37](../../../../../src/planner/ranking_payload.cpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L37:sha256:3871b15420a07d0d3f85537c64ea609c41dfeeab5b26268778688f12c94e117b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for string: Walk the full bound/core/adapter program, including literal/string bytes; this does not execute SQL or derive a new normalization proof. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies string; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for string come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/ranking_payload.cpp](../../../../../src/planner/ranking_payload.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0012

[Lines 38–50](../../../../../src/planner/ranking_payload.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class NormalizedView> void normalized(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit bound and normalized SQL owned program payload. |
| inputs / outputs | Binding/catalog/source/parameters/occurrences/expressions/predicates/outputs, core model, adapters/routes and literal payloads. |
| invariants | Charges the admitted form without evaluating expressions, proving SQL equivalence or enabling a new syntax. |
| ownership | Borrows admitted bound/core/adapter records and length metadata, mutating only Budget; no SQL execution, DTO copy or JSON worklist. |
| failure | Budget failures propagate with prior debits retained; valid normalized metadata traversal performs no scratch allocation. |
| cost | Nested visits to occurrence/expression/adapter/output records and scalar slots. Selector/text lengths yield bulk logical charges rather than rescanning characters or following expression dependencies; no SQL graph recursion/evaluation. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 51–52](../../../../../src/planner/ranking_payload.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L52:sha256:37b35d69f759a5a19e08768c2e9349c8e8afd55c5f6c89745dbecce2a120ab58
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for visit: A bounded iterative visitor; even the scratch pointer inventory is charged. Keys and nodes are a logical DOM model, not std::map node overhead. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies visit; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for visit come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/ranking_payload.cpp](../../../../../src/planner/ranking_payload.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0014

[Lines 53–56](../../../../../src/planner/ranking_payload.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T,class Function> void pending_stack(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an iterative immutable-DOM visitor with a local pointer/view inventory. |
| inputs / outputs | Pushes root into account Scratch when Budget.memory is present, ordinary vector otherwise, then invokes visitor. |
| invariants | Caller debits logical items; actual vector growth/capacity belongs to allocator/account, not the payload model. |
| ownership | Worklist owns only non-owning pointers/views for this synchronous call; source must survive visitor. |
| failure | Allocation/visitor failure releases worklist by RAII and propagates without changing source. |
| cost | O(max pending frontier) slots, allocator/growth cost and visitor traversal; fixed metadata setup. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 57–71](../../../../../src/planner/ranking_payload.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void canonical(const io::Json&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit an ordinary canonical JSON DOM without recursive descent. |
| inputs / outputs | Charges logical Json nodes, string/key payloads and pending child pointers; rejects binary nodes. |
| invariants | Logical DOM model excludes std::map node overhead/capacity; charges are not actual allocation bytes. |
| ownership | Borrows already admitted immutable source/model and mutates only Budget; JSON visitors use local scratch worklists. |
| failure | Budget Failure or scratch allocation propagates; previous debits remain spent and original input remains unchanged. |
| cost | O(nodes+keys/string bytes) logical charges and iterative pointer-inventory processing. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 72–84](../../../../../src/planner/ranking_payload.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void canonical(program::JsonView
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit an account-backed immutable JSON view. |
| inputs / outputs | Uses fixed-size JsonView work items and native key/member/array access; charges the same logical DOM shapes. |
| invariants | View size equals a Json pointer; accepted native view kinds are already constrained by program construction. |
| ownership | Borrows already admitted immutable source/model and mutates only Budget; JSON visitors use local scratch worklists. |
| failure | Budget Failure or scratch allocation propagates; previous debits remain spent and original input remains unchanged. |
| cost | O(nodes+object members+array elements) indexed visits; JsonView key/member/at are O(1) checked span access. Text widths are metadata-derived logical debits, not character scans. Scratch frontier growth/capacity, clocks and deallocation remain real costs. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_span.hpp](../../../../../include/crown/ir/program_span.hpp), [include/crown/ir/program_json.hpp](../../../../../include/crown/ir/program_json.hpp) |

## B0017

[Lines 85–88](../../../../../src/planner/ranking_payload.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class IdentityView> void identity(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge the complete retained query identity payload. |
| inputs / outputs | Fixed QueryIdentity model, canonical DOM, four hash strings and occurrence/variable orders. |
| invariants | Charges existing identity data rather than computing hash/proof authority. |
| ownership | Borrows already admitted immutable source/model and mutates only Budget; JSON visitors use local scratch worklists. |
| failure | Budget Failure or scratch allocation propagates; previous debits remain spent and original input remains unchanged. |
| cost | Complete canonical DOM node/member traversal and its worklist, plus hash/order length metadata and bulk logical payload charges; no identity recomputation or hash-text byte scan. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 89–89](../../../../../src/planner/ranking_payload.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class P> void projection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge a conservative projection component. |
| inputs / outputs | Two layout handles, field span/vector objects and owned field sequence. |
| invariants | Shared layouts/projections may be counted repeatedly across references deliberately; no dedup allocator graph claim. |
| ownership | Borrows projection field-count metadata and mutates Budget; sizeof allowances do not construct layout/projection/vector objects. |
| failure | Budget failures or invalid descriptor getter contracts propagate; valid sizing allocates no projection or worklist. |
| cost | Fixed component charges plus field-count debit. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 90–90](../../../../../src/planner/ranking_payload.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> void strings(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge a sequence of string components. |
| inputs / outputs | Sequence debit followed by each string length debit. |
| invariants | No native string copying or allocator capacity measurement occurs here. |
| ownership | Borrows strings and their length metadata, mutating Budget; no character storage or worklist is created. |
| failure | Budget failures propagate; valid string metadata traversal performs no scratch/text allocation. |
| cost | O(number of strings) visits plus total logical byte charges. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 91–92](../../../../../src/planner/ranking_payload.cpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L92:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the lexical scope identified by the source span. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/ranking_payload.cpp](../../../../../src/planner/ranking_payload.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0021

[Lines 93–93](../../../../../src/planner/ranking_payload.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void plan_identity_payload(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate native identity payload admission. |
| inputs / outputs | Calls identity(value,budget). |
| invariants | No identity recomputation or proof/freshness validation. |
| ownership | Borrows already admitted immutable source/model and mutates only Budget; JSON visitors use local scratch worklists. |
| failure | Budget Failure or scratch allocation propagates; previous debits remain spent and original input remains unchanged. |
| cost | Fixed call plus complete identity visitor. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 94–102](../../../../../src/planner/ranking_payload.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Plan> void plan_source_payload_impl(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit modeled candidate source payload before new lowering. |
| inputs / outputs | Charges DTO-shaped source fields, candidate model/tree, optional basis normalized program and complete existing semantic identity. |
| invariants | Exact binding/source/options identify semantic inputs; output identity is checked again after lowering. Logical model is not peak allocated storage. |
| ownership | Borrows already admitted immutable source/model and mutates only Budget; JSON visitors use local scratch worklists. |
| failure | Budget Failure or scratch allocation propagates; previous debits remain spent and original input remains unchanged. |
| cost | Visits candidate/source/SQL records and complete existing canonical identity DOM before blocking compilation. Many scalar-ID arrays/text fields are admitted by bulk length debits; canonical traversal alone creates the local pointer/view worklist. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 103–103](../../../../../src/planner/ranking_payload.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void plan_source_payload(const MinimumHeightCandidate& c,const CompiledProgram&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate source admission for a native basis. |
| inputs / outputs | Runs the shared visitor on candidate plus CompiledProgram view. |
| invariants | Does not export/copy full DTO or bypass exact binding checks. |
| ownership | Borrows already admitted immutable source/model and mutates only Budget; JSON visitors use local scratch worklists. |
| failure | Budget Failure or scratch allocation propagates; previous debits remain spent and original input remains unchanged. |
| cost | Fixed delegation plus full shared source visitor. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 104–104](../../../../../src/planner/ranking_payload.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void plan_source_payload(const MinimumHeightCandidate& c,const PhysicalPlan&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate source admission for a legacy DTO basis. |
| inputs / outputs | Runs shared visitor on candidate plus PhysicalPlan. |
| invariants | No new compiler or authority is constructed by this visitor. |
| ownership | Borrows already admitted immutable source/model and mutates only Budget; JSON visitors use local scratch worklists. |
| failure | Budget Failure or scratch allocation propagates; previous debits remain spent and original input remains unchanged. |
| cost | Fixed delegation plus full shared source visitor. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 105–133](../../../../../src/planner/ranking_payload.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Plan> void plan_compiled_payload_impl(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge complete candidate-local lowered program components. |
| inputs / outputs | Options/profile/validation/hash/layouts/projections/relations/indexes/input guards/routes/nodes/edges/enumeration/result-layout fields. |
| invariants | Duplicate-variable layout pair allowance is linear in fields; shared projection components can be conservatively charged more than once. Excludes allocator capacity/control/node/peak overhead. |
| ownership | Borrows immutable compiled component views and their size/text metadata, mutating Budget; does not clone descriptors/DTOs or create a JSON worklist. |
| failure | Budget or invalid plan/descriptor accessor failures propagate; valid component sizing performs no scratch allocation. Earlier debits are not rolled back. |
| cost | Visits compiled records, container headers, scalar constant payloads and length metadata. Field/selector/scope/text widths produce bulk logical debits, not full character/selector scans; no descriptor/DTO copy or JSON worklist allocation here. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 134–134](../../../../../src/planner/ranking_payload.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void plan_compiled_payload(const PhysicalPlan&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate compiled DTO component admission. |
| inputs / outputs | Shared compiled visitor on PhysicalPlan. |
| invariants | No running storage/cursor work or memory-byte guarantee. |
| ownership | Borrows PhysicalPlan and mutable Budget only for the synchronous compiled-component visitor; retains no model pointer or scratch owner. |
| failure | Propagates Budget and invalid plan/descriptor accessor failures; the valid compiled visitor allocates no worklist or DTO. |
| cost | Fixed delegation plus full component visitor. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 135–145](../../../../../src/planner/ranking_payload.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L145:sha256:378550a9fe019b88bfab7a21d4bf8bd6d2d3444700520ad8c7c87a5200be6ace
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include retained prepared SQL input tables in the logical payload charge for CompiledProgram cache entries. |
| inputs / outputs | After the existing compiled public-component walk, prepared plans add fixed limits/usage records, two logical vector headers, instruction and executable-port work/cells, and usage.metadata_bytes. |
| invariants | The branch requires prepared-input limits; PhysicalPlan and interpreted plans retain the prior charge. Normalized-source accounting already includes instruction argument bodies. This is a logical retained-payload model, not allocator peak or actual account bytes. |
| ownership | Reads immutable CompiledProgram metadata and preparation counters without creating an owner, table, or cache entry. |
| failure | Budget exhaustion rejects the payload assessment before retention; the visitor does not mutate the plan or cache. |
| cost | After the existing public-component walk, the prepared branch performs O(1) actual size/counter reads. Its logical model debits work/cells proportional to instruction and executable-input counts and includes the reported table-capacity bytes; it does not traverse private tables. |
| Design | [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md), [tests/unit/input_specialization_cache_test.cpp](../../../../../tests/unit/input_specialization_cache_test.cpp) |

## B0028

[Lines 146–146](../../../../../src/planner/ranking_payload.cpp#L146); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L146:sha256:8bf65c99ea9806935a6f88212f8f7cd998531829b15fe2d7e82f4bf3d015cd76
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::ranking::detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/ranking_payload.cpp](../../../../../src/planner/ranking_payload.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |
