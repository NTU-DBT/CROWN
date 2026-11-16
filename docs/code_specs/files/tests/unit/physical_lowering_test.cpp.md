# `tests/unit/physical_lowering_test.cpp` — block usage map

[Source](../../../../../tests/unit/physical_lowering_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4c224efa8ce28869a342ecfa5cf2ee4a01416fe1b12145e47e50590c940b55b2`. 230 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/physical_lowering_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 21–21](../../../../../tests/unit/physical_lowering_test.cpp#L21) | Callable definition: void check(bool value,const std::string& message) | calls std::runtime_error; guard void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0002) |
| [B0003 · 22–25](../../../../../tests/unit/physical_lowering_test.cpp#L22) | Callable definition: std::string read(const std::filesystem::path& path) | calls stream, check, bool, string; guard std::ifstream stream(path); check(bool(stream),"cannot open fixture: "+path.string());; returns {std::istreambuf_iterator&lt;char&gt;{stream},std::istreambuf_iterator&lt;char&gt;{}} · [reviewed contract](#b0003) |
| [B0004 · 26–30](../../../../../tests/unit/physical_lowering_test.cpp#L26) | Callable definition: std::vector&lt;std::string&gt; names(const Query& query,const std::vector&lt;VariableId&gt;& variables) | calls push_back, std::sort, begin, end; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 31–35](../../../../../tests/unit/physical_lowering_test.cpp#L31) | Callable definition: std::vector&lt;VariableId&gt; fields(const storage::TupleLayout& layout) | calls check, has_value, push_back; guard for (const auto& field : layout.fields()) { check(field.variable.has_value(),"logical field lacks a…; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 36–38](../../../../../tests/unit/physical_lowering_test.cpp#L36) | Callable definition: Relation rows(const storage::ReferenceTable& table) | calls snapshot, insert, crown::storage::export_row, values; returns result; growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 39–52](../../../../../tests/unit/physical_lowering_test.cpp#L39) | Callable definition: Assignments atom_assignments(const Catalog& catalog,const Atom& atom,const Database& database) | calls at, validate_row, size, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 53–64](../../../../../tests/unit/physical_lowering_test.cpp#L53) | Callable definition: Assignments join(const Assignments& left,const Assignments& right) | calls emplace, insert, std::move; returns result; growth emplace, insert; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 65–71](../../../../../tests/unit/physical_lowering_test.cpp#L65) | Callable definition: Relation project(const Assignments& assignments,const std::vector&lt;VariableId&gt;& variables) | calls push_back, at, insert, std::move; returns result; growth insert, push_back; 2 loop sites · [reviewed contract](#b0009) |
| [B0010 · 72–81](../../../../../tests/unit/physical_lowering_test.cpp#L72) | Callable definition: Value sample(ScalarType type,std::size_t number) | calls std::string, Date::parse, Decimal::parse, std::runtime_error; returns static_cast&lt;std::int64_t&gt;(number+1); std::string(number==0 ? @ : @ ); source comment (unverified): // Exact in every fixed P/S domain. · [reviewed contract](#b0010) |
| [B0011 · 82–98](../../../../../tests/unit/physical_lowering_test.cpp#L82) | Callable definition: Database data_for(const Catalog& catalog,const Query& query,std::size_t variation) | calls resize, size, push_back, sample; returns database; database; growth insert, push_back, resize; 6 loop sites; source comment (unverified): // Constants and ignored physical fields use the direct CQ's raw row · [reviewed contract](#b0011) |
| [B0012 · 99–101](../../../../../tests/unit/physical_lowering_test.cpp#L99) | Explanatory comments or spacing. | source comment (unverified): // Test-only static interpreter of the emitted numeric program. Expected · [reviewed contract](#b0012) |
| [B0013 · 102–167](../../../../../tests/unit/physical_lowering_test.cpp#L102) | Callable definition: Relation execute(const PhysicalPlan& plan,const Database& database) | calls state, route, crown::storage::export_row, assemble_result; guard check(rows(state.table(plan.nodes()\[input.node.value\].records))==project(expected,plan.nodes()\[inpu…; returns {}; {crown::storage::export_row(plan.assemble_result({}).values())}; growth insert, push_back; 16 loop sites; source comment (unverified): // Test-only static interpreter of the emitted numeric program. Expected · [reviewed contract](#b0013) |
| [B0014 · 168–168](../../../../../tests/unit/physical_lowering_test.cpp#L168) | Explanatory comments or spacing. |  |
| [B0015 · 169–209](../../../../../tests/unit/physical_lowering_test.cpp#L169) | Callable definition: void fixtures(const std::filesystem::path& root) | calls io::Json::parse, read, at, io::read_document; guard catch (const Error& error) { check(error.code()=="invalid_plan",name+": wrong rejection: "+error.co…; growth push_back; 4 loop sites · [reviewed contract](#b0015) |
| [B0016 · 210–223](../../../../../tests/unit/physical_lowering_test.cpp#L210) | Callable definition: void deep_program() | calls std::to_string, push_back, planner::lower_tree, check; guard check(plan.validation().native_height==count && plan.validation().edge_depth==count-1 && plan.enume…; growth push_back; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 224–224](../../../../../tests/unit/physical_lowering_test.cpp#L224) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0017) |
| [B0018 · 225–230](../../../../../tests/unit/physical_lowering_test.cpp#L225) | Callable definition: int main(int argc,char** argv) | calls check, fixtures, deep_program, what; guard check(argc==2,"usage: crown_physical_lowering_test REPOSITORY");; returns 1 · [reviewed contract](#b0018) |

## B0001

[Lines 1–20](../../../../../tests/unit/physical_lowering_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:cb3ca9c99e1b89b66ccde2a643062666430d3de8ad041af3b33981c01a5f0720
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare physical_lowering_test.cpp: include "crown/planner/lower.hpp", "crown/io/physical.hpp", "crown/io/tree.hpp", "crown/storage/physical.hpp", "crown/api/error.hpp", "evaluator.hpp", &lt;algorithm&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;set&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–21](../../../../../tests/unit/physical_lowering_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raises runtime_error for false physical-lowering test predicates. |
| inputs / outputs | bool and const string reference in. |
| invariants | Used only by local fixture/assertion code; caller message is evaluated before call. |
| ownership | Borrows message during check. |
| failure | False condition throws runtime_error. |
| cost | Branch and possible error string construction; no measurement. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0003

[Lines 22–25](../../../../../tests/unit/physical_lowering_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const std::filesystem::path& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reads a whole fixture file into an owning string. |
| inputs / outputs | Filesystem path in; complete file bytes as std::string out. |
| invariants | Checks stream opened before consuming iterators; used with manifest/query/tree fixtures. |
| ownership | Stream is local; return string owns bytes. |
| failure | Open failure throws via check; stream read errors after open are not separately checked. |
| cost | Reads and allocates proportional to file size. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0004

[Lines 26–30](../../../../../tests/unit/physical_lowering_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::string> names(const Query& query,const std::vector<VariableId>& variables) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Maps query variable IDs to names and sorts names for order-insensitive fixture comparison. |
| inputs / outputs | Query and VariableId vector in; sorted string vector out. |
| invariants | Indexes query.variables by id without explicit bounds check; only test-generated valid IDs are passed. |
| ownership | Owns output strings/vector; borrows query. |
| failure | Bad ID can fail through unchecked indexing; allocation errors propagate. |
| cost | O(k log k) sorting plus copied names. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0005

[Lines 31–35](../../../../../tests/unit/physical_lowering_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<VariableId> fields(const storage::TupleLayout& layout) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extracts VariableIds from a compiled tuple layout for logical projection comparison. |
| inputs / outputs | TupleLayout const reference in; vector of variable IDs out. |
| invariants | Every field must have a variable; check throws otherwise. |
| ownership | Returns owning vector; layout is borrowed. |
| failure | Missing variable triggers runtime_error. |
| cost | Linear field scan and vector allocation. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0006

[Lines 36–38](../../../../../tests/unit/physical_lowering_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation rows(const storage::ReferenceTable& table) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materializes a ReferenceTable snapshot as exported logical rows. |
| inputs / outputs | ReferenceTable const reference in; Relation set out. |
| invariants | ReferenceTable::snapshot returns a vector of Tuple values, not numeric TupleHandle IDs. The helper exports each tuple values() view and inserts the logical row into a deduplicating Relation. |
| ownership | Returned Relation owns row/scalar copies; table is borrowed. |
| failure | Table/export errors propagate. |
| cost | Full table snapshot plus row export and ordered-set insertion; allocations are separate from kernel storage. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp) |

## B0007

[Lines 39–52](../../../../../tests/unit/physical_lowering_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Assignments atom_assignments(const Catalog& catalog,const Atom& atom,const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Computes raw atom assignments directly from full physical rows for the independent expected semantics. |
| inputs / outputs | Catalog, Atom, Database in; set of VariableId-to-Value assignments out. |
| invariants | For the validated fixture Catalog/Query, atom arity matches its table. Each physical row is validated, repeated variables must agree and literal terms must match; ignored columns impose no condition. row\[i\] is unchecked and relies on both row width and valid atom shape. |
| ownership | Borrows catalog/atom/database; owns assignment maps/set. |
| failure | Database table lookup uses at and row validation can throw. Valid Atom/table arity is a fixture precondition; malformed overlong atom terms could still index beyond a catalog-valid row. Allocation failures propagate. |
| cost | Scans every row/term and materializes ordered maps/set; cost depends on input rows and terms. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0008

[Lines 53–64](../../../../../tests/unit/physical_lowering_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Assignments join(const Assignments& left,const Assignments& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Joins two materialized assignment sets by compatible shared variable values. |
| inputs / outputs | Two assignment sets in; all merged compatible bindings out. |
| invariants | Cross-product pairs are considered; conflicting shared variable values are discarded; equality is assignment-map equality. |
| ownership | Borrows inputs; owns copied/merged maps in result set. |
| failure | No query-level validation; standard allocation errors propagate. |
| cost | O(\|left\|×\|right\|) pair traversal with map copying and ordered set insertion. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0009

[Lines 65–71](../../../../../tests/unit/physical_lowering_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation project(const Assignments& assignments,const std::vector<VariableId>& variables) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Projects each complete assignment to an ordered CQ variable list and deduplicates rows. |
| inputs / outputs | Assignment set and variable vector in; Relation set out. |
| invariants | Uses \`at\` for each requested variable; relation set removes duplicate projected rows. |
| ownership | Borrows inputs; owns rows/results. |
| failure | Missing variable throws out_of_range; allocation errors propagate. |
| cost | Materializes one row per assignment before set dedup; O(assignments×head-width) values. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0010

[Lines 72–81](../../../../../tests/unit/physical_lowering_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value sample(ScalarType type,std::size_t number) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provides only a finite typed scalar domain for fixture databases. |
| inputs / outputs | ScalarType and small index in; exact Value alternative out. |
| invariants | Cases cover int64, string, bool, date and decimal zero; date has two valid leap-day examples; unknown type throws. |
| ownership | Returns Value by value. |
| failure | Unknown enum throws runtime_error; fixture index is assumed small enough for int64 cast. |
| cost | Fixed scalar creation and parsing; not a data generator benchmark. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0011

[Lines 82–98](../../../../../tests/unit/physical_lowering_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database data_for(const Catalog& catalog,const Query& query,std::size_t variation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds one of three finite database variations for a fixture query. |
| inputs / outputs | Catalog, Query and variation 0/1/2 in; Database of per-table row sets out. |
| invariants | 0 is empty; nonzero seeds two typed rows per table; variation 2 omits first row of table 0; variation 1 additionally inserts rows satisfying each atom’s constants. |
| ownership | Owns database relation sets and generated rows; inputs borrowed. |
| failure | Unexpected variation values follow nonzero seeded path; catalog/table IDs are assumed valid. |
| cost | Scans schema and atom terms; materializes at most two generated rows per table plus atom-specific rows. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0012

[Lines 99–101](../../../../../tests/unit/physical_lowering_test.cpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L101:sha256:c4696cf42f419ff912454113e0dd0b6668ca386aa10dc38b3ee6761bfd348481
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Test-only static interpreter of the emitted numeric program. Expected survivors below come from full subtree assignment joins, not this algorithm. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 102–167](../../../../../tests/unit/physical_lowering_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation execute(const PhysicalPlan& plan,const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Interprets a validated numeric PhysicalPlan into a reference-storage state and compares its operators to full subtree assignments. |
| inputs / outputs | PhysicalPlan and Database in; projected Relation out. |
| invariants | Handles constant routes; adapts native input and compares to raw CQ; independently joins subtree assignments; seeds generalized records from child parent keys; checks survivor/support/visible projections, indexes/invariants and C* enumeration result uniqueness. It is test-only, not the maintained runtime. |
| ownership | ReferencePlanStorage owns empty/filled tables; expected assignment sets and choices are local; plan/database borrowed. |
| failure | Assertions throw on mismatch; physical API/storage errors propagate; unchecked numeric indexing assumes validated compiler output. |
| cost | Materializes snapshots, nested assignment joins, result choices and sets; full independent joins are potentially quadratic/exponential, outside kernel cost accounting. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0015

[Lines 169–209](../../../../../tests/unit/physical_lowering_test.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fixtures(const std::filesystem::path& root) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Loads each manifest lowering fixture, checks expected compiled descriptors/replay, and runs three reference database variations. |
| inputs / outputs | Repository root path in; manifest-listed docs/trees and expected JSON read; valid/invalid counts local. |
| invariants | Invalid trees must throw Error invalid_plan; valid cases compare route, node counts/scopes/visibility/separators/C*/parent/children, exactly C* enumeration, IO replay, then execute against reference::Session for variations 0/1/2. Scope is manifest fixture coverage. |
| ownership | File contents/JSON/documents/plans/database/oracles are local owned values; root only used for path resolution. |
| failure | Missing files/JSON/type mismatches/failed assertion throw; invalid case catches only Error and checks code. |
| cost | Reads manifest and each listed fixture, performs lowering/replay plus three materialized oracle executions per valid case; not a speed test. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0016

[Lines 210–223](../../../../../tests/unit/physical_lowering_test.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void deep_program() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks depth measurements on one manually built 128-native-node chain. |
| inputs / outputs | No external input; creates catalog/query/tree with 128 unary relations and lowers it. |
| invariants | Asserts native height 128, ordinary edge depth 127, enumeration depth 128; then only instantiates empty ReferencePlanStorage and checks invariants. |
| ownership | Locally built structures and resulting plan/storage own data. |
| failure | Lowering/invariant/assertion exceptions propagate to main. |
| cost | One 128-node compile and empty storage initialization; does not execute rows or establish general depth limit/performance. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0017

[Lines 224–224](../../../../../tests/unit/physical_lowering_test.cpp#L224); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L224-L224:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in physical_lowering_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/physical_lowering_test.cpp](../../../../../tests/unit/physical_lowering_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 225–230](../../../../../tests/unit/physical_lowering_test.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs manifest fixture and deep-chain checks using a repository-root argument. |
| inputs / outputs | Requires one root argument; returns zero only after both helpers complete. |
| invariants | Checks argc==2, prints diagnostics on standard exception and returns 1. |
| ownership | Helpers own all inputs/results. |
| failure | Catches std::exception; other exceptions escape; wrong args fail through check. |
| cost | Combines all finite manifest cases and 128-node chain; output line counts are not produced here except helper’s own valid/invalid summary. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [include/crown/io/physical.hpp](../../../../../include/crown/io/physical.hpp), [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [docs/physical_plans.md](../../../../physical_plans.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |
