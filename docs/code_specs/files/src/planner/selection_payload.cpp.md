# `src/planner/selection_payload.cpp` — block usage map

[Source](../../../../../src/planner/selection_payload.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `e3f60a2b7ae99666895190463fc1e33385fc9ce18df98da3a7391a9ea4140039`. 120 lines partitioned into 25 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/planner/selection_payload.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // Known first-DirectCQ copies and the post-lower identity use the same public · [reviewed contract](#b0001) |
| [B0002 · 9–9](../../../../../src/planner/selection_payload.cpp#L9) | Callable definition: template&lt;class T&gt; void fixed(Budget& b) | calls work, bytes; source comment (unverified): // Known first-DirectCQ copies and the post-lower identity use the same public · [reviewed contract](#b0002) |
| [B0003 · 10–11](../../../../../src/planner/selection_payload.cpp#L10) | Explanatory comments or spacing. | source comment (unverified): // Charge visited sequence elements and modeled element storage. See · [reviewed contract](#b0003) |
| [B0004 · 12–14](../../../../../src/planner/selection_payload.cpp#L12) | Callable definition: template&lt;class T&gt; void sequence(const std::vector&lt;T&gt;& values, Budget& b) | calls work, size; source comment (unverified): // Charge visited sequence elements and modeled element storage. See · [reviewed contract](#b0004) |
| [B0005 · 15–17](../../../../../src/planner/selection_payload.cpp#L15) | Callable definition: void string(const std::string& value, Budget& b) | calls work, size, bytes · [reviewed contract](#b0005) |
| [B0006 · 18–18](../../../../../src/planner/selection_payload.cpp#L18) | Explanatory comments or spacing. | source comment (unverified): // Admit dynamic scalar component allowance. See docs/selection_accounting.md. · [reviewed contract](#b0006) |
| [B0007 · 19–23](../../../../../src/planner/selection_payload.cpp#L19) | Callable definition: void scalar(const Value& value, Budget& b) | calls work, string, bytes; source comment (unverified): // Admit dynamic scalar component allowance. See docs/selection_accounting.md. · [reviewed contract](#b0007) |
| [B0008 · 24–26](../../../../../src/planner/selection_payload.cpp#L24) | Callable definition: void variables(const VariableSet& values, Budget& b) | calls work, size · [reviewed contract](#b0008) |
| [B0009 · 27–44](../../../../../src/planner/selection_payload.cpp#L27) | Callable definition: void catalog(const Catalog& value, Budget& b) | calls sequence, string, std::visit, constexpr; 5 loop sites · [reviewed contract](#b0009) |
| [B0010 · 45–53](../../../../../src/planner/selection_payload.cpp#L45) | Callable definition: void query(const Query& value, Budget& b) | calls sequence, string, scalar; 4 loop sites · [reviewed contract](#b0010) |
| [B0011 · 54–61](../../../../../src/planner/selection_payload.cpp#L54) | Callable definition: void tree(const FreeConnexTree& value, Budget& b) | calls sequence, string, variables; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 62–63](../../../../../src/planner/selection_payload.cpp#L62) | Explanatory comments or spacing. | source comment (unverified): // Iteratively charge an ordinary identity DOM and traversal scratch. See · [reviewed contract](#b0012) |
| [B0013 · 64–81](../../../../../src/planner/selection_payload.cpp#L64) | Callable definition: void canonical(const io::Json& root, Budget& b) | calls empty, back, pop_back, work; guard } else require(!item-&gt;is_binary());; growth push_back; 3 loop sites; source comment (unverified): // Iteratively charge an ordinary identity DOM and traversal scratch. See · [reviewed contract](#b0013) |
| [B0014 · 82–84](../../../../../src/planner/selection_payload.cpp#L82) | Closes surrounding scope/type. | source comment (unverified): // Pre-admit known first DirectCQ compiler source components. See · [reviewed contract](#b0014) |
| [B0015 · 85–89](../../../../../src/planner/selection_payload.cpp#L85) | Callable definition: void direct_source_payload(const MinimumHeightCandidate& candidate, Budget& budget) | calls catalog, query, tree; source comment (unverified): // Pre-admit known first DirectCQ compiler source components. See · [reviewed contract](#b0015) |
| [B0016 · 90–95](../../../../../src/planner/selection_payload.cpp#L90) | Callable definition: void identity_payload(const io::QueryIdentity& identity, Budget& budget) | calls canonical, string, sequence · [reviewed contract](#b0016) |
| [B0017 · 96–97](../../../../../src/planner/selection_payload.cpp#L96) | Explanatory comments or spacing. | source comment (unverified): // Use the C02 native identity component visitor under existing grant/account. See · [reviewed contract](#b0017) |
| [B0018 · 98–100](../../../../../src/planner/selection_payload.cpp#L98) | Callable definition: void identity_payload(const program::QueryIdentity& identity, Budget& budget) | calls borrowed, rd::plan_identity_payload; source comment (unverified): // Use the C02 native identity component visitor under existing grant/account. See · [reviewed contract](#b0018) |
| [B0019 · 101–103](../../../../../src/planner/selection_payload.cpp#L101) | Callable definition: void source_payload(const MinimumHeightCandidate& candidate, const PhysicalPlan& basis, Budget& budget) | calls borrowed, rd::plan_source_payload · [reviewed contract](#b0019) |
| [B0020 · 104–106](../../../../../src/planner/selection_payload.cpp#L104) | Callable definition: void source_payload(const MinimumHeightCandidate& candidate, const CompiledProgram& basis, Budget& budget) | calls borrowed, rd::plan_source_payload · [reviewed contract](#b0020) |
| [B0021 · 107–109](../../../../../src/planner/selection_payload.cpp#L107) | Callable definition: void compiled_payload(const PhysicalPlan& plan, Budget& budget) | calls borrowed, rd::plan_compiled_payload · [reviewed contract](#b0021) |
| [B0022 · 110–112](../../../../../src/planner/selection_payload.cpp#L110) | Callable definition: void compiled_payload(const CompiledProgram& plan, Budget& budget) | calls borrowed, rd::plan_compiled_payload · [reviewed contract](#b0022) |
| [B0023 · 113–114](../../../../../src/planner/selection_payload.cpp#L113) | Explanatory comments or spacing. | source comment (unverified): // Compute logical source-plus-compiled retention charge for one cache entry. See · [reviewed contract](#b0023) |
| [B0024 · 115–119](../../../../../src/planner/selection_payload.cpp#L115) | Callable definition: std::uint64_t cache_plan_payload(const MinimumHeightCandidate& candidate, const CompiledProgram& plan, Budget& budget) | calls source_payload, compiled_payload; returns budget.usage.payload_bytes - before; source comment (unverified): // Compute logical source-plus-compiled retention charge for one cache entry. See · [reviewed contract](#b0024) |
| [B0025 · 120–120](../../../../../src/planner/selection_payload.cpp#L120) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::selection::detail · [reviewed contract](#b0025) |

## B0001

[Lines 1–8](../../../../../src/planner/selection_payload.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:5e9cd177bf9819e169deb916a7e14ccb6c67dd22537c2c123947b8e19b156629
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "selection_detail.hpp", #include "ranking_payload.hpp", #include &lt;type_traits&gt; available to src/planner/selection_payload.cpp; open crown::planner::selection::detail and anonymous helper namespace. Attached note: Known first-DirectCQ copies and the post-lower identity use the same public component model as C02. Native private temporaries/allocator peak are excluded. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/selection_payload.cpp](../../../../../src/planner/selection_payload.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0002

[Lines 9–9](../../../../../src/planner/selection_payload.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void fixed(Budget& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge one known fixed component header. |
| inputs / outputs | One work and sizeof(T) modeled payload. |
| invariants | Does not construct or allocate T. |
| ownership | Mutates counters only. |
| failure | Cap failure retains earlier diagnostics. |
| cost | Fixed debit; real allocation separate. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0003

[Lines 10–11](../../../../../src/planner/selection_payload.cpp#L10); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L11:sha256:19d78f51f3905c9fbe31244a76bd9d8dc58930901c427bae34cfce3ac46e08c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for size: Charge visited sequence elements and modeled element storage. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies size; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for size come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_payload.cpp](../../../../../src/planner/selection_payload.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0004

[Lines 12–14](../../../../../src/planner/selection_payload.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void sequence(const std::vector<T>& values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge visited sequence elements and modeled element storage. |
| inputs / outputs | n work, n cells, n*sizeof(T) payload. |
| invariants | Nested dynamic members are walked separately; capacity/control overhead excluded. |
| ownership | Borrows ordinary vector. |
| failure | Checked debit can throw before caller copies. |
| cost | Fixed size accounting plus later caller traversal. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0005

[Lines 15–17](../../../../../src/planner/selection_payload.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void string(const std::string& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge logical text bytes without formatting/copying them. |
| inputs / outputs | Length work and modeled payload. |
| invariants | No capacity or allocator-framing claim. |
| ownership | Borrows stable string. |
| failure | Budget stop propagates. |
| cost | Reads length; charge represents later payload work. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0006

[Lines 18–18](../../../../../src/planner/selection_payload.cpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L18:sha256:d10bd40426f8e0167dccc2eaf7f83e4098e613713a2cbc3a3e34ec309ad17695
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for scalar: Admit dynamic scalar component allowance. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies scalar; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for scalar come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_payload.cpp](../../../../../src/planner/selection_payload.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0007

[Lines 19–23](../../../../../src/planner/selection_payload.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar(const Value& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit dynamic scalar component allowance. |
| inputs / outputs | Base work; string bytes or conservative 38 work/bytes for bounded Decimal. |
| invariants | It does not render/export a Decimal or validate the value. |
| ownership | Borrows Value. |
| failure | Budget stop propagates. |
| cost | Fixed variant checks plus logical dynamic allowance. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0008

[Lines 24–26](../../../../../src/planner/selection_payload.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void variables(const VariableSet& values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Model variable-set members as logical ID cells/bytes. |
| inputs / outputs | Cardinality work/cells and sizeof(VariableId) payload per member. |
| invariants | Ordered set node overhead is excluded from this model. |
| ownership | Borrows the set. |
| failure | Cap failure propagates. |
| cost | Size accounting, not a set copy. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0009

[Lines 27–44](../../../../../src/planner/selection_payload.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void catalog(const Catalog& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Walk known ordinary catalog dynamic payload components. |
| inputs / outputs | Visits tables/columns, constraint vectors, statistics and key hints/names. |
| invariants | Counts full metadata rather than only query-used tables; fixed fields reside in containing headers. |
| ownership | Borrows model and nested strings/vectors. |
| failure | Budget/variant failure aborts private admission. |
| cost | Linear visited containers/text lengths; does not duplicate the catalog. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0010

[Lines 45–53](../../../../../src/planner/selection_payload.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void query(const Query& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Walk variable/atom/term/head dynamic payload. |
| inputs / outputs | Charges vector elements, names, constants and ordered output aliases. |
| invariants | Constants/ignored term positions remain in modeled vector storage. |
| ownership | Borrows query. |
| failure | Budget failures propagate. |
| cost | Visits all terms and text/Decimal allowances. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0011

[Lines 54–61](../../../../../src/planner/selection_payload.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void tree(const FreeConnexTree& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Model complete supplied-tree dynamic payload including claims. |
| inputs / outputs | Visits node IDs/scopes/children/separators and claimed connex list. |
| invariants | Claims are payload only, never trusted proof. |
| ownership | Borrows tree. |
| failure | Budget stops before retention. |
| cost | Linear node/edge/scope/claim cells and text bytes. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0012

[Lines 62–63](../../../../../src/planner/selection_payload.cpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L63:sha256:175ca90a1099f9dbbe61027aeeba34c73928ac990745cb5007c6cd408f822b0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for canonical: Iteratively charge an ordinary identity DOM and traversal scratch. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies canonical; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for canonical come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_payload.cpp](../../../../../src/planner/selection_payload.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0013

[Lines 64–81](../../../../../src/planner/selection_payload.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void canonical(const io::Json& root,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Iteratively charge an ordinary identity DOM and traversal scratch. |
| inputs / outputs | Explicit pending pointer vector visits nodes, structured overhead, strings and object keys. |
| invariants | Binary JSON is rejected; no recursive traversal stack is assumed. Ordinary DOM path is an explicit compiler/DTO boundary. |
| ownership | Borrows immutable DOM; owns temporary ordinary pointer vector. |
| failure | Budget/allocation failure drops scratch; no cache publication. |
| cost | O(nodes, keys and string bytes), plus vector growth; modeled payload differs from allocated map/capacity overhead. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0014

[Lines 82–84](../../../../../src/planner/selection_payload.cpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L84:sha256:a4c265781d0f40557f1bc1c003f4d245d29354b1d3f9c2edc62372e3b8be3161
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the anonymous helper namespace before the direct_source_payload note. Its attached note introduces nearby behavior: Pre-admit known first DirectCQ compiler source components. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/selection_payload.cpp](../../../../../src/planner/selection_payload.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0015

[Lines 85–89](../../../../../src/planner/selection_payload.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void direct_source_payload(const MinimumHeightCandidate& candidate,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pre-admit known first DirectCQ compiler source components. |
| inputs / outputs | Fixed PhysicalPlan/Catalog/Query/tree/normalized-option controls plus full dynamic model/tree walk. |
| invariants | This is conservative logical admission, not an actual program allocation measure. |
| ownership | Borrows typed checked candidate. |
| failure | Budget stop precedes first lower. |
| cost | Complete supplied model/tree component scan. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0016

[Lines 90–95](../../../../../src/planner/selection_payload.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void identity_payload(const io::QueryIdentity& identity,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit ordinary identity DOM, hashes and order-map payload. |
| inputs / outputs | Fixed header, canonical visitor, four digest strings and ID-order vectors. |
| invariants | Identity bytes do not confer proof authority. |
| ownership | Borrows DTO and owns temporary walk scratch. |
| failure | Logical/allocation failure propagates. |
| cost | Full DOM/text/map component scan. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0017

[Lines 96–97](../../../../../src/planner/selection_payload.cpp#L96); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L97:sha256:e004fb291d5abcb5fb5c835a801f185e11540421fd60a9e3fdc5b5c50002970b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for identity_payload: Use the C02 native identity component visitor under existing grant/account. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies identity_payload; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for identity_payload come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_payload.cpp](../../../../../src/planner/selection_payload.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0018

[Lines 98–100](../../../../../src/planner/selection_payload.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void identity_payload(const program::QueryIdentity& identity,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the C02 native identity component visitor under existing grant/account. |
| inputs / outputs | Delegates rd::plan_identity_payload through Budget.borrowed. |
| invariants | No ordinary identity export or fresh grant is introduced. |
| ownership | Borrows immutable native identity; shares account. |
| failure | Counters are carried even if delegate throws. |
| cost | Native component traversal plus outer timing; actual allocator work separate. |
| Design | [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0019

[Lines 101–103](../../../../../src/planner/selection_payload.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_payload(const MinimumHeightCandidate& candidate, const PhysicalPlan& basis,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge a supplied compiler DTO source with the shared C02 visitor. |
| inputs / outputs | Runs rd::plan_source_payload(candidate,basis) through Budget.borrowed. |
| invariants | Uses unchanged C02 component model; shared metadata may be conservatively counted repeatedly. |
| ownership | Borrows plan/candidate; inner budget shares receiving account. |
| failure | Delegate counters replace outer Usage even on exception. |
| cost | Complete relevant component traversal; logical payload is not allocator peak. |
| Design | [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0020

[Lines 104–106](../../../../../src/planner/selection_payload.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_payload(const MinimumHeightCandidate& candidate, const CompiledProgram& basis,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge native source components without exporting an ordinary graph. |
| inputs / outputs | Runs rd::plan_source_payload(candidate,basis) through Budget.borrowed. |
| invariants | Uses unchanged C02 component model; shared metadata may be conservatively counted repeatedly. |
| ownership | Borrows plan/candidate; inner budget shares receiving account. |
| failure | Delegate counters replace outer Usage even on exception. |
| cost | Complete relevant component traversal; logical payload is not allocator peak. |
| Design | [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0021

[Lines 107–109](../../../../../src/planner/selection_payload.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compiled_payload(const PhysicalPlan& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge complete compiler DTO compiled components. |
| inputs / outputs | Runs rd::plan_compiled_payload(plan) through Budget.borrowed. |
| invariants | Uses unchanged C02 component model; shared metadata may be conservatively counted repeatedly. |
| ownership | Borrows plan/candidate; inner budget shares receiving account. |
| failure | Delegate counters replace outer Usage even on exception. |
| cost | Complete relevant component traversal; logical payload is not allocator peak. |
| Design | [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0022

[Lines 110–112](../../../../../src/planner/selection_payload.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compiled_payload(const CompiledProgram& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge complete native compiled components without an ordinary mirror. |
| inputs / outputs | Runs rd::plan_compiled_payload(plan) through Budget.borrowed. |
| invariants | Uses unchanged C02 component model; shared metadata may be conservatively counted repeatedly. |
| ownership | Borrows plan/candidate; inner budget shares receiving account. |
| failure | Delegate counters replace outer Usage even on exception. |
| cost | Complete relevant component traversal; logical payload is not allocator peak. |
| Design | [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0023

[Lines 113–114](../../../../../src/planner/selection_payload.cpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L114:sha256:a5e6f69dffda8867d9cecf12a09cd350a604d4b27ccbc3f12d07fd16d818e1a9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for cache_plan_payload: Compute logical source-plus-compiled retention charge for one cache entry. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies cache_plan_payload; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for cache_plan_payload come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_payload.cpp](../../../../../src/planner/selection_payload.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0024

[Lines 115–119](../../../../../src/planner/selection_payload.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t cache_plan_payload(const MinimumHeightCandidate& candidate,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute logical source-plus-compiled retention charge for one cache entry. |
| inputs / outputs | Returns payload counter delta after source and compiled visitors. |
| invariants | Recharges independent cache-retention domain even when plan ownership is already shared. |
| ownership | Borrows plan/candidate; no new plan copy. |
| failure | Failure returns no delta and leaves only private cumulative diagnostics. |
| cost | Full component scan; not an address-deduplicated allocator byte count. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0025

[Lines 120–120](../../../../../src/planner/selection_payload.cpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L120:sha256:41848aefb30bbb259c959e13f974e1f553bad9051ef8e1ee6f1df63b5ac2ac7c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::selection::detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/selection_payload.cpp](../../../../../src/planner/selection_payload.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |
