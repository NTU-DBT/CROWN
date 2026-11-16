# `tests/unit/native_replanning_test.cpp` — block usage map

[Source](../../../../../tests/unit/native_replanning_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `71e7d44d55b6543c54318e76b33260349999c2c0e9da1734696450809015a2d8`. 297 lines partitioned into 27 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/native_replanning_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../tests/unit/native_replanning_test.cpp#L15) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) {if(!value)throw std::runtime_error(std::string(mes… · [reviewed contract](#b0002) |
| [B0003 · 16–18](../../../../../tests/unit/native_replanning_test.cpp#L16) | Callable definition: template&lt;class Range,class Function&gt; io::Json array(const Range& values,Function emit) | calls io::Json::array, push_back, emit; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../tests/unit/native_replanning_test.cpp#L19) | Callable definition: template&lt;class Range&gt; io::Json ids(const Range& values) | calls array; returns array(values,\[\](auto id){return id.value · [reviewed contract](#b0004) |
| [B0005 · 20–20](../../../../../tests/unit/native_replanning_test.cpp#L20) | Callable definition: template&lt;class Id&gt; io::Json optional_id(const std::optional&lt;Id&gt;& value) | calls io::Json; returns value?io::Json(value-&gt;value):io::Json(nullptr) · [reviewed contract](#b0005) |
| [B0006 · 21–21](../../../../../tests/unit/native_replanning_test.cpp#L21) | Callable definition: io::Json slot(AssignmentSlot value) | calls ; returns {value.step,value.field.value} · [reviewed contract](#b0006) |
| [B0007 · 22–30](../../../../../tests/unit/native_replanning_test.cpp#L22) | Callable definition: template&lt;class L&gt; io::Json layout(const L& value) | calls array, fields, io::Json, optional_id; returns io::Json{{@ ,static_cast&lt;int&gt;(field.type)},{@ ,field.decimal?io::Json{field.decimal-&gt;precision,fiel… · [reviewed contract](#b0007) |
| [B0008 · 31–33](../../../../../tests/unit/native_replanning_test.cpp#L31) | Callable definition: template&lt;class P&gt; io::Json projection(const P& value) | calls source, id, target, ids; returns {{@ ,value.source().id().value},{@ ,value.target().id().value},{@ ,ids(value.fields())}} · [reviewed contract](#b0008) |
| [B0009 · 34–34](../../../../../tests/unit/native_replanning_test.cpp#L34) | Callable definition: io::Json scalar(const Value& value) | calls io::write_scalar; returns io::write_scalar(value) · [reviewed contract](#b0009) |
| [B0010 · 35–35](../../../../../tests/unit/native_replanning_test.cpp#L35) | Callable definition: io::Json scalar(const storage::ScalarView& value) | calls io::write_scalar_view; returns io::write_scalar_view(value) · [reviewed contract](#b0010) |
| [B0011 · 36–69](../../../../../tests/unit/native_replanning_test.cpp#L36) | Callable definition: template&lt;class P&gt; io::Json image(const P& plan) | calls route, std::string, physical_sha256, physical_source_sha256; returns layout(value); io::Json{value.id.value,static_cast&lt;int&gt;(value.role),value.layout.id().value,optiona… · [reviewed contract](#b0011) |
| [B0012 · 70–78](../../../../../tests/unit/native_replanning_test.cpp#L70) | Callable definition: template&lt;class P&gt; auto projections(const P& plan) | calls indexes, push_back, inputs, nodes; returns result; growth push_back; 5 loop sites · [reviewed contract](#b0012) |
| [B0013 · 79–82](../../../../../tests/unit/native_replanning_test.cpp#L79) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(current.allocations==1 && current.requested_bytes==resource::MemoryAccount::control_bytes(),"… · [reviewed contract](#b0013) |
| [B0014 · 83–91](../../../../../tests/unit/native_replanning_test.cpp#L83) | Type/record definition: struct Case | returns sql?planner::lower_normalized(*sql,tree,options):planner::lower_tree(catalog,query,tree,options) · [reviewed contract](#b0014) |
| [B0015 · 92–92](../../../../../tests/unit/native_replanning_test.cpp#L92) | Callable definition: Case core() | calls c02_test::fixture, std::move; returns {std::move(f.catalog),std::move(f.query),{},2} · [reviewed contract](#b0015) |
| [B0016 · 93–100](../../../../../tests/unit/native_replanning_test.cpp#L93) | Callable definition: Case sql(bool exists) | calls c02_test::fixture, frontend::bind_sql, check, frontend::normalize_sql; guard auto bound=frontend::bind_sql(text,f.catalog);check(std::holds_alternative&lt;frontend::BoundSql&gt;(boun…; returns {std::move(catalog),std::move(query),std::move(program),2} · [reviewed contract](#b0016) |
| [B0017 · 101–112](../../../../../tests/unit/native_replanning_test.cpp#L101) | Callable definition: Case rich() | calls std::string, Date::parse, Decimal::parse, std::move; returns {std::move(catalog),std::move(query),{},1} · [reviewed contract](#b0017) |
| [B0018 · 113–123](../../../../../tests/unit/native_replanning_test.cpp#L113) | Type/record definition: struct Fixture | returns CompiledProgram::replan(basis,*input.candidates.candidate(i)) · [reviewed contract](#b0018) |
| [B0019 · 124–151](../../../../../tests/unit/native_replanning_test.cpp#L124) | Callable definition: void equivalence(const Case& input,bool indexed) | calls fixture, candidate_count, lower, replan; guard check(expected.physical_source_sha256()==sha256(io::write_physical_source(expected.catalog(),expect…; growth emplace_back, push_back; 7 loop sites · [reviewed contract](#b0019) |
| [B0020 · 152–161](../../../../../tests/unit/native_replanning_test.cpp#L152) | Callable definition: void requests_and_lifetime(const Case& input,bool indexed) | calls fixture, statistics, replan, check; guard const auto after=account.statistics();check(calls&gt;0 && calls==after.successful_allocations-before.s… · [reviewed contract](#b0020) |
| [B0021 · 162–176](../../../../../tests/unit/native_replanning_test.cpp#L162) | Callable definition: std::size_t persistent(const Case& input,bool indexed) | calls fixture, replan, image, check; guard check(expected&gt;0 && expected&lt;4096,"native replanning fault count is outside test bound");; returns expected; 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 177–197](../../../../../tests/unit/native_replanning_test.cpp#L177) | Callable definition: std::pair&lt;std::uint64_t,std::size_t&gt; caps(const Case& input,bool indexed) | calls fixture, reserve, statistics, replan; guard check(peak&gt;0 && pins&gt;0,"native replan never exceeded source-admission peak");; returns {peak,pins}; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0022) |
| [B0023 · 198–224](../../../../../tests/unit/native_replanning_test.cpp#L198) | Callable definition: void churn_and_work(const Case& input,bool indexed) | calls fixture, statistics, reserve, candidate_count; guard check(fixture.account.statistics().current==expected\[index\],"replanning retained a chain of histori…; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0023) |
| [B0024 · 225–235](../../../../../tests/unit/native_replanning_test.cpp#L225) | Callable definition: void receiving_account(const Case& input,bool indexed) | calls target, source, statistics, CompiledProgram::replan_into; guard check(calls&gt;0 && calls==account.statistics().successful_allocations-before.successful_allocations && · [reviewed contract](#b0024) |
| [B0025 · 236–283](../../../../../tests/unit/native_replanning_test.cpp#L236) | Callable definition: std::pair&lt;std::size_t,std::uint64_t&gt; native_admission_copy(const Case& input,bool indexed) | calls source, replan, image, resource::MemoryAccount::create; guard check(calls&gt;0 && calls&lt;4096 && calls==account.statistics().successful_allocations-before.successful…; returns CompiledProgram::freeze(target,original,&grant); {calls,peak}; growth push_back, reserve; 6 loop sites · [reviewed contract](#b0025) |
| [B0026 · 284–284](../../../../../tests/unit/native_replanning_test.cpp#L284) | Closes surrounding scope/type. |  · [reviewed contract](#b0026) |
| [B0027 · 285–297](../../../../../tests/unit/native_replanning_test.cpp#L285) | Callable definition: int main() | calls core, sql, rich, size; returns 1; 2 loop sites · [reviewed contract](#b0027) |

## B0001

[Lines 1–14](../../../../../tests/unit/native_replanning_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:ba3ec4ac6d69681ddb3f77007bda9e5501f106ba90ac46f6b2a967a5bf42a440
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare native_replanning_test.cpp: include "ranking_fixture.hpp", "indexed_runtime_fixture.hpp", "compiled_source.hpp", "crown/io/physical.hpp", "crown/io/normalization.hpp", "crown/ir/digest.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;iostream&gt;, &lt;optional&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–15](../../../../../tests/unit/native_replanning_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message) {if(!value)throw std::runtime_error(std::string(message));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the test assertion used throughout native replanning checks. |
| inputs / outputs | Inputs are a predicate and a borrowed std::string_view message; normal return has no value. |
| invariants | A true predicate returns; false constructs and throws std::runtime_error from the message bytes. |
| ownership | The message view is borrowed only for the call and no state is retained. |
| failure | The false path can fail while constructing the diagnostic or exception; caller exceptions are not caught here. |
| cost | One branch on success; string and exception work occurs only on the false path. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp) |

## B0003

[Lines 16–18](../../../../../tests/unit/native_replanning_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range,class Function> io::Json array(const Range& values,Function emit) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a JSON array by applying a caller emitter to each range element. |
| inputs / outputs | Input is a borrowed range and an emitter parameter passed by value; output is an owning io::Json array in input iteration order. |
| invariants | Element order and multiplicity are preserved; no sorting or filtering is performed. |
| ownership | The range is borrowed; the emitter is a by-value local parameter. Emitted values are stored in the returned JSON object. |
| failure | Emitter and JSON allocation exceptions propagate. |
| cost | Visits each element once, calls the emitter, and appends one JSON value; result storage may grow. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp) |

## B0004

[Lines 19–19](../../../../../tests/unit/native_replanning_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> io::Json ids(const Range& values) {return array(values,[](auto id){return id.value;});}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an ID range as a JSON array of each ID value. |
| inputs / outputs | Input is a borrowed range whose elements expose value; output is an io::Json array of those values. |
| invariants | Uses range order and multiplicity without checking IDs against a plan. |
| ownership | Input IDs are borrowed; returned JSON owns its numeric entries. |
| failure | JSON construction or allocation exceptions propagate. |
| cost | One array traversal and one JSON append per ID. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp) |

## B0005

[Lines 20–20](../../../../../tests/unit/native_replanning_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Id> io::Json optional_id(const std::optional<Id>& value) {return value?io::Json(value->value):io::Json(nullptr);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an optional typed ID as its numeric value or JSON null. |
| inputs / outputs | Input is an optional ID; output is the contained value field or null. |
| invariants | Presence is retained, including the distinction between absent and a present zero ID. |
| ownership | The optional is borrowed; returned JSON owns its value. |
| failure | JSON value construction exceptions propagate. |
| cost | One presence branch and a small JSON value construction. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp) |

## B0006

[Lines 21–21](../../../../../tests/unit/native_replanning_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json slot(AssignmentSlot value) {return {value.step,value.field.value};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an assignment slot as its step and field indices. |
| inputs / outputs | Input is an AssignmentSlot value; output is a two-element JSON array. |
| invariants | The two numeric members are emitted in step-then-field order without further validation. |
| ownership | Input is copied by value; JSON output owns its numbers. |
| failure | JSON allocation exceptions propagate. |
| cost | Fixed-size JSON construction. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp) |

## B0007

[Lines 22–30](../../../../../tests/unit/native_replanning_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class L> io::Json layout(const L& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the test JSON image of a layout-like plan object. |
| inputs / outputs | Reads the layout ID, fields, catalog version, binding bytes and optional origin; returns JSON containing those values. |
| invariants | Field type is represented by its integer enum value; decimal and variable are optional; origin is absent or table plus source schema version. |
| ownership | The source layout is borrowed; output JSON owns copied binding text and nested arrays. |
| failure | Field traversal, string copying, JSON construction and allocation failures propagate. |
| cost | Traverses all fields once and builds nested JSON arrays/objects; output growth depends on field count and binding length. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp) |

## B0008

[Lines 31–33](../../../../../tests/unit/native_replanning_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class P> io::Json projection(const P& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a projection’s source, target and ordered field IDs. |
| inputs / outputs | Input is a borrowed projection-like object; output has source and target layout IDs plus fields encoded through ids(). |
| invariants | Projection field order and multiplicity are retained; no token-identity check is performed here. |
| ownership | Input projection is borrowed; JSON output owns the encoded IDs. |
| failure | JSON construction or allocation exceptions propagate. |
| cost | Visits each projection field once through ids() and builds one small object. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp) |

## B0009

[Lines 34–34](../../../../../tests/unit/native_replanning_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json scalar(const Value& value) {return io::write_scalar(value);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the public scalar writer for an owning Value. |
| inputs / outputs | Input is a Value; output is the JSON representation returned by io::write_scalar. |
| invariants | Scalar type and formatting are delegated to the IO writer; this helper adds no normalization. |
| ownership | Value is borrowed; returned JSON owns its representation. |
| failure | Writer and allocation exceptions propagate. |
| cost | Cost follows the scalar variant, including any text formatting and JSON storage. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp) |

## B0010

[Lines 35–35](../../../../../tests/unit/native_replanning_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json scalar(const storage::ScalarView& value) {return io::write_scalar_view(value);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the scalar writer for a storage-backed ScalarView. |
| inputs / outputs | Input is a ScalarView; output is the JSON representation returned by io::write_scalar_view. |
| invariants | The storage view is read synchronously and is not exported or retained by this helper. |
| ownership | The view is borrowed; returned JSON owns its representation. |
| failure | Writer and allocation exceptions propagate. |
| cost | Cost follows the viewed scalar and produced JSON; no copy-free guarantee is asserted. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp) |

## B0011

[Lines 36–69](../../../../../tests/unit/native_replanning_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class P> io::Json image(const P& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the comparison image for physical and compiled plan values. |
| inputs / outputs | Input is a plan-like P; output is JSON for route, hashes, work, layouts, relations, indexes, inputs, routes, nodes, edges, enumeration, validation, identity order fields and optional normalized SQL. |
| invariants | It compares the explicitly serialized fields only; identity arrays are included and normalized SQL uses the corresponding plan representation. |
| ownership | Plan is borrowed; nested JSON owns copied strings and values for the duration of comparison. |
| failure | Scalar writing, normalized SQL output, JSON traversal and allocations can fail and propagate. |
| cost | Traverses plan collections and nested members, serializes scalars, and materializes a JSON tree; work and storage grow with plan size and text. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp) |

## B0012

[Lines 70–78](../../../../../tests/unit/native_replanning_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class P> auto projections(const P& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect pointers to every projection location used by the test alias comparison. |
| inputs / outputs | Input is a borrowed plan; output is a vector of pointers into its indexes, inputs, nodes, edges and enumeration steps. |
| invariants | The unevaluated type expression naming indexes()\[0\] does not access element zero at runtime; optional projections are included only when present. |
| ownership | The vector owns pointer values only; every pointed projection remains owned by the plan and pointers are valid only while those objects remain stable. |
| failure | Vector allocation may throw; no empty-index precondition is imposed by the type expression. |
| cost | Scans the listed plan collections and appends one pointer per encountered projection; output size tracks those collections. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp) |

## B0013

[Lines 79–82](../../../../../tests/unit/native_replanning_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that replanning cleanup leaves only the MemoryAccount controller allocation. |
| inputs / outputs | Input is a borrowed MemoryAccount; returns no value after invariant and current-usage checks. |
| invariants | Calls check_invariants(), then requires current allocation count one and requested bytes equal control_bytes(). |
| ownership | Account handle is borrowed; no allocation or account ownership is retained. |
| failure | Invariant violation or failed assertion throws; this helper does not translate the exception. |
| cost | check_invariants walks the live allocation list; statistics() then copies current counters. This is test validation, not allocator or RSS measurement. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0014

[Lines 83–91](../../../../../tests/unit/native_replanning_test.cpp#L83); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Case {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle one core or normalized SQL test case with its checked candidate family. |
| inputs / outputs | Fields hold Catalog, Query, optional NormalizedSql and CandidateSnapshot; constructor receives values and a target proof height. |
| invariants | Constructor moves DTO values into fields and obtains candidates through c02_test::candidates; lower() selects indexed options when requested and uses normalized or core lowering according to sql presence. |
| ownership | Case owns its DTOs and typed snapshot; candidate/proof data follows public owning handle semantics. |
| failure | Candidate setup, lowerer and allocation failures propagate. |
| cost | Construction performs real finite proof/family setup; lower() repeats physical lowering for the selected candidate. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

## B0015

[Lines 92–92](../../../../../tests/unit/native_replanning_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Case core() {auto f=c02_test::fixture();f.query.head={{VariableId{0},"first"},{VariableId{1},"second"},{VariableId{0},"again"}};return {std::move(f.catalog),std::move(f.query),{},2};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the core test case and alter its projected head ordering. |
| inputs / outputs | No inputs; starts with c02_test::fixture, replaces the head with x, y, x aliases and returns a height-two Case without normalized SQL. |
| invariants | Duplicate output of variable zero and head order are intentional parts of the core fixture. |
| ownership | Returned Case owns moved catalog/query and candidate snapshot. |
| failure | Fixture or candidate admission failures propagate. |
| cost | Copies/assigns a small head vector and builds the candidate snapshot through the Case constructor. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

## B0016

[Lines 93–100](../../../../../tests/unit/native_replanning_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Case sql(bool exists) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build either an EXISTS or projected normalized SQL case for replanning. |
| inputs / outputs | Input bool selects one of two literal SQL statements; output is a Case containing bound/normalized core data and height-two candidate snapshot. |
| invariants | Both bind and normalize results are checked for the expected variant before values are moved into Case. |
| ownership | Local bind results and SQL text die after construction; returned Case owns the NormalizedSql and candidate snapshot. |
| failure | A failed bind/normalize assertion throws through check; parser, binder, normalizer or allocation errors propagate. |
| cost | Per call binds and normalizes one statement, then builds the candidate snapshot; this is setup repeated only for the two SQL variants. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

## B0017

[Lines 101–112](../../../../../tests/unit/native_replanning_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Case rich() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a rich core fixture with long, embedded-NUL and typed catalog/query fields. |
| inputs / outputs | No inputs; returns a height-one Case containing multiple scalar types, statistics, constraints, key hints, unused table and repeated output alias. |
| invariants | The string literal contains 8192 z bytes followed by a three-byte embedded-NUL sequence; the Case is non-normalized and uses the constructed core DTOs. |
| ownership | Catalog/query values are moved into Case; its candidate snapshot owns checked proof-prefix handles. |
| failure | Candidate creation or value allocation errors propagate. |
| cost | Builds the fixed rich DTO and its candidate snapshot; large string size is fixture data, not a bound on general plans. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

## B0018

[Lines 113–123](../../../../../tests/unit/native_replanning_test.cpp#L113); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an accounted native basis from a Case for one replanning experiment. |
| inputs / outputs | Inputs are a borrowed Case, indexed toggle and requested account cap; creates a MemoryAccount, lowers the Case, constructs a fixed IndexWorkAllowance and freezes the source plan. |
| invariants | Indexed mode passes one five-dimensional per_operation IndexWorkAllowance through freeze(); its component balances form one aggregate grant, not separate per-domain grants or refills. Reference mode passes UINT64_MAX in each component for that freeze. replan(i) uses NativeLowering’s separate UINT64_MAX five-dimensional metadata allowance; these work allowances are separate from MemoryAccount byte capacity and ReplanLimits. |
| ownership | Fixture owns the account and basis; Case is borrowed and must outlive operations that read input. |
| failure | Account capacity, lowering, freeze and replan failures propagate. |
| cost | Per instance performs source lowering and freeze into the supplied account; its IndexWorkAllowance is passed only to freeze(). NativeLowering constructs its own UINT64_MAX metadata allowance, separate from ReplanLimits and the account byte cap. |
| Design | [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp) |

## B0019

[Lines 124–151](../../../../../tests/unit/native_replanning_test.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void equivalence(const Case& input,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native candidate replanning with independently repeated original lowering. |
| inputs / outputs | Inputs are Case and indexed toggle; for each candidate builds expected lower_tree/lower_normalized output and CompiledProgram::replan output, then checks image, physical export, projection alias relations, applicable input adaptation and storage layouts. |
| invariants | The test also checks source fingerprint, exact serialized physical format and all pairwise same_token results; input adaptation is skipped for normalized SQL. The same IndexWorkAllowance object is passed to make_storage and check_invariants, preserving one remaining balance for the work each operation charges. check_invariants also scans tables/layouts that are not wholly IndexWork-metered. |
| ownership | Case and its candidate handles are borrowed; expected/actual plans, rows and storage are local owners. A replanned CompiledProgram shares the immutable canonical basis while owning new graph metadata. |
| failure | Any semantic image/export/token/adaptation mismatch or API failure aborts by exception. |
| cost | Loops over every retained candidate, serializes plan images/exports, compares projection pairs quadratically in projection count, adapts core rows, and materializes/checks native storage. |
| Design | [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp) |

## B0020

[Lines 152–161](../../../../../tests/unit/native_replanning_test.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void requests_and_lifetime(const Case& input,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check allocation attribution and handle lifetime for an ordinary basis replan. |
| inputs / outputs | Input Case and indexed toggle; creates an optional Fixture, captures account statistics, replans candidate0 under s04_alloc::Scope, then copies/destroys program handles with the scope set to fail on the next intercepted C++ new. |
| invariants | The test requires some intercepted calls and equality with the account successful-allocation delta; it compares current statistics values, not account owner identity. A retained copy remains readable after Fixture reset, then all plan handles are cleared before controller_only. |
| ownership | Fixture owns its account/basis; copied handles share the immutable program data and canonical source basis; Case is borrowed. |
| failure | Unexpected allocation count, lost source lifetime or remaining account allocation throws; operator-new failure can throw bad_alloc inside the measured scope. |
| cost | One replan allocation count plus shared-handle copy/reset and a full account invariant sweep; s04_alloc covers its replacement C++ new forms, not every heap source or RSS. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 162–176](../../../../../tests/unit/native_replanning_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t persistent(const Case& input,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-inject each counted C++ new position during persistent native replan and verify retry. |
| inputs / outputs | Input is Case/indexed; calibrates candidate 0’s complete replan allocation-call count N, then sets fail_after to 0..N on the same Fixture. Values 0..N-1 inject failures; N is the successful boundary control. Each injected failure is retried. |
| invariants | At each injected position below N the attempt throws bad_alloc after point+1 counted calls, publishes no CompiledProgram and leaves account.current unchanged; each of the N failed calls is retried. Position N is a successful boundary call with N counted calls and a matching account successful-allocation delta. The retained image remains unchanged and account invariants are checked after output cleanup. |
| ownership | Fixture, old plan and account are owners; each tentative output is local and is cleared before the next position. |
| failure | Injected or underlying allocation failure is expected below N; assertion and account failures propagate. |
| cost | Runs one retained replan, one calibration and a 0..N sweep with retries for N failures: 2N+3 replan calls in this phase. Faults intercept selected C++ operator new paths, not a universal heap/CPU boundary. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 177–197](../../../../../tests/unit/native_replanning_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::pair<std::uint64_t,std::size_t> caps(const Case& input,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure the tested native plan retention frontier and check exact and one-under account caps. |
| inputs / outputs | Input Case/indexed toggle; repeatedly replans candidate0, retaining each plan until peak_requested_bytes rises after an earlier plan, then repeats at that measured cap and one byte less. Returns measured peak and pin count. |
| invariants | Discovery is limited to at most 1024 iterations; exact cap succeeds, one-under fails with MemoryFault::limit without changing current usage, and releasing one retained plan permits retry under the unchanged one-under limit. |
| ownership | Each Fixture owns a separate account; held CompiledPrograms retain account-backed plans until vector/scope teardown. |
| failure | Failure to find a frontier, wrong cap error, leak, ignored cap or changed retry limit throws. |
| cost | Discovery uses at most 1024 replan attempts; cap checks make 2*pins+3 replans after discovery, excluding fixture/account setup. Account requested-byte peak is not process heap/RSS. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 198–224](../../../../../tests/unit/native_replanning_test.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void churn_and_work(const Case& input,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check plan replacement does not retain a historical graph chain and enforce replan work limits. |
| inputs / outputs | Input Case/indexed toggle; records current account usage per candidate plan, performs 30 replacements, then probes exact and one-under lowering/identity limits and normalized binding/normalization limits when SQL exists. |
| invariants | Replacement current usage must match the corresponding retained-plan baseline and return to basis baseline after clearing. Exact structural work succeeds; one-under lowering and zero identity caps produce their specific ReplanFaults. For normalized SQL cases, zero binding-replay and zero normalization caps are separately tested; those probes are skipped for core cases. |
| ownership | Fixture owns basis/account; replacement handle owns the current native graph, candidate handles are borrowed. |
| failure | Wrong memory/current delta or wrong/missing ReplanFailure is an assertion failure; ordinary errors propagate. |
| cost | For C retained candidates the source schedule performs C baseline replans, 30 replacements, one calibration, one exact-work attempt, one one-under lowering attempt and one zero identity attempt: C+34 replan calls. Normalized SQL adds two zero-limit attempts (C+36). This callable does not construct storage or pass an IndexWorkAllowance; its replan calls use NativeLowering’s separate UINT64_MAX five-dimensional metadata allowance. ReplanLimits work ceilings and MemoryAccount byte capacity are distinct controls. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 225–235](../../../../../tests/unit/native_replanning_test.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void receiving_account(const Case& input,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify replan_into charges a supplied receiving account rather than the basis owner. |
| inputs / outputs | Inputs are Case/indexed toggle; creates separate target and source Fixtures and replans candidate0 from source basis into target account, then resets Fixture handles while output remains held. |
| invariants | Counted C++ new calls equal target successful-allocation delta and source successful count stays fixed. The held result remains valid after Fixture handles reset because it retains the canonical immutable source basis; the source account is checked controller-only only after the held result is released, followed by the target account. |
| ownership | Target account owns the new replan graph, while the result shares and retains the canonical immutable basis in the source account. Resetting the source Fixture does not release that basis until the result is cleared; Case is borrowed. |
| failure | Allocation mismatch, invalid retained output or leaked account block throws. |
| cost | One receiving-account replan, source/target reset, then two invariant-list sweeps; only the test’s C++ new wrapper count is separate from MemoryAccount accounting. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 236–283](../../../../../tests/unit/native_replanning_test.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::pair<std::size_t,std::uint64_t> native_admission_copy(const Case& input,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check freezing a compiled program into another account preserves its serialized fields and allocation behavior. |
| inputs / outputs | Inputs Case/indexed toggle; obtains original candidate0 compiled plan, copies it with CompiledProgram::freeze(target,original,&grant), compares plan image and projection alias pairs, sweeps allocation faults, then discovers and tests target-account peak/one-under caps. |
| invariants | Successful copy preserves image and alias graph; target account receives successful allocations while source account allocation count is unchanged. For allocation sweep count N, only positions 0..N-1 inject failures and must publish no partial copy or change current usage; position N is the successful boundary control. Exact target cap succeeds and one-under rejects until a retained copy is released. After original and source Fixture are reset, the source account is checked controller-only while the receiving copy is still held and image-valid. The receiving account is checked controller-only after that held copy is released. |
| ownership | Original plan owns source metadata; copied plan owns new account-backed metadata in target; local copies/held outputs retain handles independently. |
| failure | Injected bad_alloc and MemoryFailure(limit) are expected at specified positions; any changed image, leak or incorrect account charge throws. |
| cost | Copy calibration plus fault stage makes 2N+2 copy calls; cap discovery is at most 1024 attempts plus 2*pins+3 cap calls, separate from an earlier source replan. Counts cover C++ new calls and MemoryAccount requested bytes, not all heap or CPU. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 284–284](../../../../../tests/unit/native_replanning_test.cpp#L284); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L284-L284:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in native_replanning_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 285–297](../../../../../tests/unit/native_replanning_test.cpp#L285); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all native replanning fixture and account experiments. |
| inputs / outputs | No inputs; builds core, two SQL and rich cases, then runs each under reference and indexed lowering; returns process status. |
| invariants | All four Cases are run for both indexed values; success output occurs after every experiment; only standard exceptions are caught and reported as failure. |
| ownership | Main owns the case array and all fixtures/results created by each group; no shared product state escapes. |
| failure | A caught std::exception prints its message and returns 1; other thrown types are not caught by this main. |
| cost | Runs eight case/backend combinations. Equivalence and churn/work traverse the retained candidate family; lifetime, fault, cap, receiving-account and admission-copy experiments use candidate0. This is the source workload, not evidence of test execution or a runtime bound. |
| Design | [tests/unit/native_replanning_test.cpp](../../../../../tests/unit/native_replanning_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc) |
