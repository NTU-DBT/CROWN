# `tests/unit/indexed_owner_statistics_fixture.hpp` — block usage map

[Source](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ae80fcc902adc3a46edc49222db22b321e42876234f2b1c17f2faf3ead4f3836`. 108 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L13) | Callable definition: inline Value n(std::int64_t x) | calls ; returns x · [reviewed contract](#b0002) |
| [B0003 · 14–16](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L14) | Callable definition: inline void check(bool b,std::source_location at=std::source_location::current()) | calls std::source_location::current, std::runtime_error, std::string, file_name; guard inline void check(bool b,std::source_location at=std::source_location::current()){ · [reviewed contract](#b0003) |
| [B0004 · 17–28](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L17) | Callable definition: inline PhysicalPlan plan(bool generalized=false) | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog,q,FreeConnexTree{NodeId{0},{{@ ,NodeKind::generalized,{VariableId{1… · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L29) | Callable definition: inline Database database() | calls n; returns {{{{n(1),n(7),n(10)},{n(1),n(7),n(11)},{n(2),n(7),n(20)},{n(3),n(8),n(30)}},{{n(7)}},{{n(99)}}}} · [reviewed contract](#b0005) |
| [B0006 · 30–31](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L30) | Explanatory comments or spacing. | source comment (unverified): // Separate geometry: G(y) -&gt; R(x,y), S(y), with T(x) below R. · [reviewed contract](#b0006) |
| [B0007 · 32–41](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L32) | Callable definition: inline PhysicalPlan hidden_separator_plan() | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog,q,FreeConnexTree{NodeId{0},{{@ ,NodeKind::generalized,{VariableId{1…; source comment (unverified): // Separate geometry: G(y) -&gt; R(x,y), S(y), with T(x) below R. · [reviewed contract](#b0007) |
| [B0008 · 42–44](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L42) | Callable definition: inline Database hidden_separator_database() | calls database, push_back, n; returns result; growth push_back · [reviewed contract](#b0008) |
| [B0009 · 45–56](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L45) | Callable definition: inline stats::OwnerRequest request(const auto& p) | calls edges, push_back; returns r; growth push_back; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 57–57](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L57) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 58–71](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L58) | Callable definition: inline void distribution(const stats::Component& component,const Counts& expected,std::uint64_t visited,std::size_t top_k=16) | calls check, has_value, size, emplace_back; guard check(component.availability==stats::Availability::available && component.distribution.has_value());; returns a.second!=b.second?a.second&gt;b.second:a.first&lt;b.first; growth emplace_back, resize; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 72–73](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L72) | Explanatory comments or spacing. | source comment (unverified): // Independent set/map oracle for this literal R(x,y,ignored), S(y) fixture. · [reviewed contract](#b0012) |
| [B0013 · 74–95](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L74) | Callable definition: inline void fixture_facts(const stats::OwnerCapture& actual,const Database& input) | calls check, availability, components, size; guard check(actual.availability()==stats::Availability::available && actual.components().size()==8);; returns static_cast&lt;std::uint64_t&gt;(values.size()); 4 loop sites; source comment (unverified): // Independent set/map oracle for this literal R(x,y,ignored), S(y) fixture. · [reviewed contract](#b0013) |
| [B0014 · 96–107](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L96) | Callable definition: inline void same_facts(const stats::OwnerCapture& a,const stats::OwnerCapture& b) | calls check, availability, physical_source_scope, components; guard check(a.availability()==b.availability() && a.physical_source_scope()==b.physical_source_scope() &&…; 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 108–108](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L108) | Closes surrounding scope/type. |  · [reviewed contract](#b0015) |

## B0001

[Lines 1–12](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:36b448a8a352d8606d7c972c91740c40662b4df6e4cbea99be73348d7ff48f27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_owner_statistics_fixture.hpp: include "indexed_runtime_fixture.hpp", "crown/runtime/owner_statistics.hpp", "crown/runtime/physical.hpp", "crown/planner/lower.hpp", &lt;algorithm&gt;, &lt;map&gt;, &lt;stdexcept&gt;, &lt;source_location&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_owner_statistics_fixture.hpp](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–13](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Value n(std::int64_t x){return x;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert an integer fixture value into the native Value alternative. |
| inputs / outputs | int64_t enters; Value holding that integer exits. |
| invariants | The conversion preserves the signed value and introduces no statistics or plan identity. |
| ownership | Returns a scalar Value by value and retains no input or runtime reference. |
| failure | No expected failure beyond native scalar value construction. |
| cost | Scalar value construction; no allocation or engine ownership. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 14–16](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void check(bool b,std::source_location at=std::source_location::current()){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an owner-statistics fixture assertion with its source file and line. |
| inputs / outputs | Boolean assertion plus the default or explicit source_location enter; no result exits. |
| invariants | A true condition returns normally; false reports the call-site location, not the helper definition. |
| ownership | Reads the bool and source_location by value; retains no owner, request, or report. |
| failure | False throws std::runtime_error containing source file and line; it is not a runtime::statistics error contract. |
| cost | One branch and, only on failure, runtime_error string construction. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 17–28](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan plan(bool generalized=false){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the two-node R(x,y), S(y) plan, optionally rooted at generalized G(y), using s04_runtime::lower_tree. |
| inputs / outputs | A generalized flag enters; catalog/query/tree lower to a PhysicalPlan with optional ignored source column and unused catalog table. |
| invariants | The ordinary plan preserves x,y head and R-to-S separator y; generalized mode changes the head to y and adds G with children R,S. Indexed variant routes through S04 lowering for the index configuration. |
| ownership | Returned plan owns its catalog/tree data; all local catalog/query/tree objects die after lowering. |
| failure | Planner validation/resource errors propagate before the test begins; helper does not convert them to expected test failures. |
| cost | Constructs a fixed three-table query and lowers a two- or three-node tree once; no data rows are scanned. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 29–29](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Database database(){return {{{{n(1),n(7),n(10)},{n(1),n(7),n(11)},{n(2),n(7),n(20)},{n(3),n(8),n(30)}},{{n(7)}},{{n(99)}}}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the literal owner fixture database. |
| inputs / outputs | No arguments; Database exits with four R source rows, S={7}, and one unused-table row. |
| invariants | R contains two distinct full witnesses for (1,7), one (2,7), and one (3,8); only y=7 survives the S join. |
| ownership | Database owns copied Rows; no relation view into a runtime is created. |
| failure | Value/container allocation failure propagates to the caller. |
| cost | Constructs fixed-size relation sets; no evaluator or runtime snapshot is consulted. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 30–31](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L31:sha256:5c55e4e1e827fca381d8f060c20a7239057710fa5c0bb62b014e6ff89cd92910
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Separate geometry: G(y) -&gt; R(x,y), S(y), with T(x) below R. G-&gt;R and G-&gt;S separators contain output y; R-&gt;T contains hidden x. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/indexed_owner_statistics_fixture.hpp](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 32–41](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan hidden_separator_plan(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the separate G(y)-&gt;R(x,y),S(y) plan with a hidden x separator from R to T(x). |
| inputs / outputs | No arguments; a plan with four catalog tables and four tree nodes exits. |
| invariants | G-to-R and G-to-S separators are output y; R-to-T separator is hidden x, so the fixture distinguishes output-only reachability from an arbitrary child relation. |
| ownership | Returned plan owns the catalog and lowered tree; no source database or runtime is borrowed. |
| failure | Lowering/validation errors propagate; the helper does not assert a runtime behavior by itself. |
| cost | Builds and lowers one fixed four-node plan; only planner construction work occurs. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 42–44](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Database hidden_separator_database(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extend the owner fixture database with T(x) rows 1, 2, and 3. |
| inputs / outputs | Database copy enters; an owning Database with appended T relation exits. |
| invariants | The three T keys cross the hidden x separator and are nonempty, allowing not_applicable E to be distinguished from exact empty data. |
| ownership | Copies the source Database and owns the appended relation; input remains unchanged. |
| failure | Container allocation failure propagates to the caller. |
| cost | Copies the small base relations and appends three rows. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 45–56](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline stats::OwnerRequest request(const auto& p){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a deterministic eight-component OwnerRequest from the actual lowered plan. |
| inputs / outputs | Borrowed plan enters; request exits with source R/y, unused-source cardinality, occurrence 0, root records/S/P/E, and the first admitted reverse index when present. |
| invariants | IDs come from the compiled plan; the helper does not infer an index ID from a display label or assume all plans have an index. |
| ownership | Request owns its selection and field vectors; plan is borrowed only while locating an admitted reverse index. |
| failure | Invalid plan contents are surfaced by later capture; vector allocation errors propagate. |
| cost | Constructs a fixed set of seven initial selections and scans plan edges until the first reverse index. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 57–57](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L57); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L57:sha256:414fa0bc72dd72e0a01b3f8907397f5aa30f766af807351639452889cad9c5c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_owner_statistics_fixture.hpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_owner_statistics_fixture.hpp](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 58–71](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void distribution(const stats::Component& component,const Counts& expected,std::uint64_t visited,std::size_t top_k=16){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact availability, NDV, multiplicity histogram, and deterministic heavy-key order against a literal map. |
| inputs / outputs | Borrowed Component, expected ordered Row-to-count map, visited population, and top-K cap enter; assertion-only result exits. |
| invariants | Requires exact completion; histogram groups equal multiplicities; heavy keys rank by count descending then native Row ascending and are truncated to top_k. |
| ownership | Expected map and component are borrowed; sorted ranking vector is local and destroyed on return. |
| failure | A failed assertion throws the source-located fixture runtime_error; incomplete distributions are rejected rather than interpreted as zero. |
| cost | Builds a multiplicity histogram and sorts at most the supplied fixture key count, O(K log K); it does not include runtime scan cost. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 72–73](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L72); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L73:sha256:5de5e2c88af4e06dd1d2355911227bf112e29b5c51d835b636980cff2f3b0647
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Independent set/map oracle for this literal R(x,y,ignored), S(y) fixture. It does not inspect engine snapshots, support counters or collector output. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/indexed_owner_statistics_fixture.hpp](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 74–95](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void fixture_facts(const stats::OwnerCapture& actual,const Database& input){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the eight requested component facts from the literal input database without reading runtime internals. |
| inputs / outputs | Borrowed OwnerCapture and Database enter; assertion-only result exits. |
| invariants | Groups source y, full native R keys, reverse degrees, survivor y, root P(empty key), visible full keys, and unused-source cardinality; source/occurrence components without requested projections have no distribution. P/E weighted histogram totals equal visible rows. |
| ownership | Capture remains an owning value; input Database is borrowed; local ordered maps own expected keys only through the check. |
| failure | Assertion mismatch throws; map/container allocation or capture was previously completed and is not converted into an availability value. |
| cost | One pass over literal rows and grouped keys plus exact histogram/top-K checks; the oracle does not reuse engine snapshots, support counters, or output. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0014

[Lines 96–107](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void same_facts(const stats::OwnerCapture& a,const stats::OwnerCapture& b){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two owning captures structurally while ignoring the owner identity that can legitimately differ after replay/rebuild. |
| inputs / outputs | Two borrowed OwnerCaptures enter; assertion-only result exits. |
| invariants | Compares availability, scope availability, ordered components, layouts, selections, distribution completion/visited/NDV/histogram and every heavy key/count. |
| ownership | Captures own all compared report data; helper borrows both for the call and stores no reference. |
| failure | A mismatch throws; no mutation or recovery is attempted. |
| cost | Linear in component count plus histogram/heavy-key lengths; does not scan a runtime. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0015

[Lines 108–108](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp#L108); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L108:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_owner_statistics_fixture.hpp: namespace owner_fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_owner_statistics_fixture.hpp](../../../../../tests/unit/indexed_owner_statistics_fixture.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |
