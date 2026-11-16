# `tests/unit/scalar_statistics_test.cpp` — block usage map

[Source](../../../../../tests/unit/scalar_statistics_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e1ba2249159f3d7776bf9b8a3a9f5c3ea50a6417308d5f1ce6d01cd256ab744e`. 271 lines partitioned into 46 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/scalar_statistics_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 19–21](../../../../../tests/unit/scalar_statistics_test.cpp#L19) | Callable definition: void check(bool value,std::string_view message,std::source_location at=std::source_location::current()) | calls std::source_location::current, std::runtime_error, std::string, file_name; guard void check(bool value,std::string_view message,std::source_location at=std::source_location::curren… · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../tests/unit/scalar_statistics_test.cpp#L22) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 23–23](../../../../../tests/unit/scalar_statistics_test.cpp#L23) | Callable definition: Value decimal(std::string_view value) | calls Decimal::parse; returns Decimal::parse(value) · [reviewed contract](#b0004) |
| [B0005 · 24–24](../../../../../tests/unit/scalar_statistics_test.cpp#L24) | Callable definition: Value date(std::string_view value) | calls Date::parse; returns Date::parse(value) · [reviewed contract](#b0005) |
| [B0006 · 25–26](../../../../../tests/unit/scalar_statistics_test.cpp#L25) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 27–27](../../../../../tests/unit/scalar_statistics_test.cpp#L27) | Callable definition: st::Limits limits() | calls ; returns result · [reviewed contract](#b0007) |
| [B0008 · 28–28](../../../../../tests/unit/scalar_statistics_test.cpp#L28) | Callable definition: ws::Options enabled() | calls ; returns result · [reviewed contract](#b0008) |
| [B0009 · 29–29](../../../../../tests/unit/scalar_statistics_test.cpp#L29) | Callable definition: DeltaOptions options() | calls ; returns result · [reviewed contract](#b0009) |
| [B0010 · 30–30](../../../../../tests/unit/scalar_statistics_test.cpp#L30) | Callable definition: std::uint64_t count_of(const auto& values) | calls size; returns static_cast&lt;std::uint64_t&gt;(values.size()) · [reviewed contract](#b0010) |
| [B0011 · 31–31](../../../../../tests/unit/scalar_statistics_test.cpp#L31) | Callable definition: Row fields(const Row& row,const Fields& selection) | calls push_back, at; returns out; growth push_back; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 32–32](../../../../../tests/unit/scalar_statistics_test.cpp#L32) | Callable definition: Counts project(const Relation& rows,const Fields& selection) | calls fields; returns out; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 33–33](../../../../../tests/unit/scalar_statistics_test.cpp#L33) | Callable definition: Counts ones(const Counts& values) | calls emplace; returns out; growth emplace; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 34–34](../../../../../tests/unit/scalar_statistics_test.cpp#L34) | Callable definition: Counts root_counts(const Counts& survivors) | calls empty, count_of; returns survivors.empty()?Counts{}:Counts{{Row{},count_of(survivors)}} · [reviewed contract](#b0014) |
| [B0015 · 35–35](../../../../../tests/unit/scalar_statistics_test.cpp#L35) | Callable definition: void unknown(const auto& value) | calls check, empty; guard void unknown(const auto& value){check(value.completion==st::Completion::budget_exhausted&&!value.nd… · [reviewed contract](#b0015) |
| [B0016 · 36–44](../../../../../tests/unit/scalar_statistics_test.cpp#L36) | Callable definition: void distribution(const auto& actual,const Counts& expected,std::uint64_t visited,std::size_t top=64) | calls check, count_of, push_back, std::ranges::equal; guard check(actual.completion==st::Completion::exact&&actual.ndv==count_of(expected)&&actual.visited==vis…; returns a.second!=b.second?a.second&gt;b.second:a.first&lt;b.first; growth push_back, resize; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 45–48](../../../../../tests/unit/scalar_statistics_test.cpp#L45) | Callable definition: void component(const st::Component& actual,const Counts& expected,std::uint64_t cardinality,std::uint64_t visited,std::size_t top… | calls check, distribution; guard check(actual.availability==st::Availability::available&&actual.cardinality==cardinality&&actual.dis… · [reviewed contract](#b0017) |
| [B0018 · 49–55](../../../../../tests/unit/scalar_statistics_test.cpp#L49) | Callable definition: void selection(const st::CapturedSelection& actual,const st::Selection& expected) | calls check, index, has_value, std::ranges::equal; guard check(actual.scope.index()==expected.scope.index()&&actual.fields.has_value()==expected.fields.has_… · [reviewed contract](#b0018) |
| [B0019 · 56–63](../../../../../tests/unit/scalar_statistics_test.cpp#L56) | Callable definition: void boundary(const st::CombinedCapture& report,const PhysicalPlan& plan,SupportOwnerId owner,std::uint64_t sequence,bool pending… | calls check, state, stamp, workload; guard check(report.state().stamp().owner==owner&&report.workload().stamp().owner==owner,"actual owner bin… · [reviewed contract](#b0019) |
| [B0020 · 64–65](../../../../../tests/unit/scalar_statistics_test.cpp#L64) | Explanatory comments or spacing. | source comment (unverified): // Rank is supplied by the literal list, never by Value/Decimal/string ordering. · [reviewed contract](#b0020) |
| [B0021 · 66–76](../../../../../tests/unit/scalar_statistics_test.cpp#L66) | Callable definition: void ranked_distribution(const auto& actual,const std::vector&lt;Value&gt;& ordered,const std::vector&lt;std::uint64_t&gt;& multiplicities, s… | calls check, count_of, size, push_back; guard check(actual.completion==st::Completion::exact&&actual.ndv==count_of(ordered)&&actual.visited==visi…; returns multiplicities\[a\]!=multiplicities\[b\]?multiplicities\[a\]&gt;multiplicities\[b\]:a&lt;b; growth push_back, resize; 2 loop sites; source comment (unverified): // Rank is supplied by the literal list, never by Value/Decimal/string ordering. · [reviewed contract](#b0021) |
| [B0022 · 77–106](../../../../../tests/unit/scalar_statistics_test.cpp#L77) | Callable definition: void scalar_order(ScalarType type,const std::vector&lt;Value&gt;& ordered) | calls add_index, multiplicities, size, decimal; guard check(table.insert(source.tuple({input,n(++ordinal)})).inserted,"distinct source witness");}; growth insert; 2 loop sites · [reviewed contract](#b0022) |
| [B0023 · 107–117](../../../../../tests/unit/scalar_statistics_test.cpp#L107) | Callable definition: void scalar_orders() | calls min, max, scalar_order, n · [reviewed contract](#b0023) |
| [B0024 · 118–119](../../../../../tests/unit/scalar_statistics_test.cpp#L118) | Explanatory comments or spacing. | source comment (unverified): // Independent arithmetic: do not call Cell::observe/merge or collector hooks. · [reviewed contract](#b0024) |
| [B0025 · 120–120](../../../../../tests/unit/scalar_statistics_test.cpp#L120) | Callable definition: void observation(ws::Cell& cell,std::uint64_t value) | calls std::min, std::max; 1 loop sites; source comment (unverified): // Independent arithmetic: do not call Cell::observe/merge or collector hooks. · [reviewed contract](#b0025) |
| [B0026 · 121–121](../../../../../tests/unit/scalar_statistics_test.cpp#L121) | Callable definition: void transition(ws::Cell& cell,std::uint64_t before,std::uint64_t after) | calls observation · [reviewed contract](#b0026) |
| [B0027 · 122–139](../../../../../tests/unit/scalar_statistics_test.cpp#L122) | Type/record definition: struct Events | guard check(actual.options()==enabled()&&actual.descriptors().size()==descriptors.size()&&std::equal(desc…; returns cells\[i\]; growth insert; 2 loop sites · [reviewed contract](#b0027) |
| [B0028 · 140–149](../../../../../tests/unit/scalar_statistics_test.cpp#L140) | Callable definition: PhysicalPlan alias_plan() | calls emplace_back, n, planner::lower_tree; returns planner::lower_tree(catalog,query,FreeConnexTree{NodeId{0},{{@ ,NodeKind::generalized,scope,{{1},{2…; growth emplace_back; 2 loop sites · [reviewed contract](#b0028) |
| [B0029 · 150–150](../../../../../tests/unit/scalar_statistics_test.cpp#L150) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0029) |
| [B0030 · 151–158](../../../../../tests/unit/scalar_statistics_test.cpp#L151) | Callable definition: st::OwnerRequest alias_request(const PhysicalPlan& plan) | calls push_back, indexes; returns out; growth push_back; 5 loop sites · [reviewed contract](#b0030) |
| [B0031 · 159–160](../../../../../tests/unit/scalar_statistics_test.cpp#L159) | declares types or opens a type body. |  · [reviewed contract](#b0031) |
| [B0032 · 161–161](../../../../../tests/unit/scalar_statistics_test.cpp#L161) | Callable definition: explicit AliasModel(const ws::Snapshot& initial):events(initial) | calls events · [reviewed contract](#b0032) |
| [B0033 · 162–162](../../../../../tests/unit/scalar_statistics_test.cpp#L162) | Callable definition: Counts joined() const | calls contains, emplace; returns out; growth emplace; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 163–163](../../../../../tests/unit/scalar_statistics_test.cpp#L163) | Callable definition: Counts candidates() const | calls ones; returns out; 1 loop sites · [reviewed contract](#b0034) |
| [B0035 · 164–177](../../../../../tests/unit/scalar_statistics_test.cpp#L164) | Callable definition: void apply(const PhysicalPlan& plan,SetOperation op,const Row& row) | calls insert, erase, input, fields; guard const auto found=native\[route\].find(key);const auto before=found==native\[route\].end()?0:found-&gt;seco…; growth insert; 3 loop sites · [reviewed contract](#b0035) |
| [B0036 · 178–189](../../../../../tests/unit/scalar_statistics_test.cpp#L178) | Callable definition: void check_state(const st::OwnerCapture& report,const PhysicalPlan& plan,const st::OwnerRequest& request) const | calls fields, n, check, components; guard check(native==literal,"alias derivations agree with independent source regrouping");; 3 loop sites · [reviewed contract](#b0036) |
| [B0037 · 190–190](../../../../../tests/unit/scalar_statistics_test.cpp#L190) | Closes surrounding scope/type. |  · [reviewed contract](#b0037) |
| [B0038 · 191–191](../../../../../tests/unit/scalar_statistics_test.cpp#L191) | Callable definition: Row tagged(Row key,std::int64_t tag) | calls push_back, n; returns key; growth push_back · [reviewed contract](#b0038) |
| [B0039 · 192–215](../../../../../tests/unit/scalar_statistics_test.cpp#L192) | Callable definition: void typed_alias_trace() | calls alias_plan, alias_request, runtime, options; guard check(incomplete.state().availability()==st::Availability::budget_exhausted&&incomplete.state().com…; growth insert; 2 loop sites · [reviewed contract](#b0039) |
| [B0040 · 216–216](../../../../../tests/unit/scalar_statistics_test.cpp#L216) | Explanatory comments or spacing. |  |
| [B0041 · 217–225](../../../../../tests/unit/scalar_statistics_test.cpp#L217) | Callable definition: PhysicalPlan constraint_plan() | calls emplace_back, planner::lower_tree; returns planner::lower_tree(catalog,query,FreeConnexTree{NodeId{0},{{@ ,NodeKind::native,{{0},{1}},{},0,{}}…; growth emplace_back · [reviewed contract](#b0041) |
| [B0042 · 226–229](../../../../../tests/unit/scalar_statistics_test.cpp#L226) | Callable definition: st::OwnerRequest constraint_request() | calls ; returns {{{st::SourceScope{{0}},Fields{{0},{1},{2}}},{st::SourceScope{{0}},Fields{{2},{1},{2}}},{st::Source… · [reviewed contract](#b0042) |
| [B0043 · 230–249](../../../../../tests/unit/scalar_statistics_test.cpp#L230) | Type/record definition: struct ConstraintModel | guard events.adapter(0,op,{0},true);const Row key{row\[1\],row\[2\]};const auto old=native.find(key);const au…; returns out; growth insert; 2 loop sites · [reviewed contract](#b0043) |
| [B0044 · 250–269](../../../../../tests/unit/scalar_statistics_test.cpp#L250) | Callable definition: void constrained_trace() | calls constraint_plan, constraint_request, runtime, options; guard try{auto output=runtime.apply({sequence+1,{table},op,row});output.discard();}catch(const Error& err…; growth insert · [reviewed contract](#b0044) |
| [B0045 · 270–270](../../../../../tests/unit/scalar_statistics_test.cpp#L270) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0045) |
| [B0046 · 271–271](../../../../../tests/unit/scalar_statistics_test.cpp#L271) | Callable definition: int main() | calls scalar_orders, typed_alias_trace, constrained_trace, what; returns 1 · [reviewed contract](#b0046) |

## B0001

[Lines 1–18](../../../../../tests/unit/scalar_statistics_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:12aeab126ece86f5c0a34745c7732380d5954c37363a084be19f2c169683f1c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare scalar_statistics_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/combined_statistics.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;map&gt;, &lt;source_location&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–21](../../../../../tests/unit/scalar_statistics_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message,std::source_location at=std::source_location::current()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report a scalar-oracle assertion with its source location. |
| inputs / outputs | Boolean, message view, and default/call-site source_location enter; normal return or source-located std::runtime_error exits. |
| invariants | The successful path does not construct the diagnostic string; the failing message is copied into the exception. |
| ownership | The message view is borrowed; the exception owns its diagnostic. |
| failure | A failed fixture assertion throws std::runtime_error; planner, allocation, and native API failures otherwise propagate to the calling test. This is test-oracle behavior, not a production failure guarantee. |
| cost | Only failed assertions allocate diagnostic storage; no runtime state is changed. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0003

[Lines 22–22](../../../../../tests/unit/scalar_statistics_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value){return value;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an integer Value for typed scalar fixtures. |
| inputs / outputs | int64_t enters; owning Value exits. |
| invariants | Signed minimum and maximum are retained exactly. |
| ownership | Value owns its scalar payload and does not borrow caller storage. |
| failure | No expected failure beyond ordinary value construction. |
| cost | Constant-size scalar construction. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0004

[Lines 23–23](../../../../../tests/unit/scalar_statistics_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value decimal(std::string_view value){return Decimal::parse(value);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a Decimal fixture literal into the canonical numeric Value alternative. |
| inputs / outputs | Decimal text view enters; owning Decimal Value exits. |
| invariants | Equivalent scale/sign spellings are compared by Decimal value equality in the oracle; input text is not kept as a display ranking key. |
| ownership | Input string_view is borrowed only during parse; output Decimal owns normalized numeric state. |
| failure | Invalid decimal parsing propagates before the runtime test runs. |
| cost | Work is proportional to literal length; no relation scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0005

[Lines 24–24](../../../../../tests/unit/scalar_statistics_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value date(std::string_view value){return Date::parse(value);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a date literal into the native date Value alternative. |
| inputs / outputs | Date string_view enters; owning Date Value exits. |
| invariants | Date fixtures cover endpoints, epoch boundaries, leap days, and date ordering. |
| ownership | Input text is borrowed during parse; resulting Date is a value. |
| failure | Invalid date parse propagates. |
| cost | Work is proportional to literal length; no runtime traversal. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0006

[Lines 25–26](../../../../../tests/unit/scalar_statistics_test.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L26:sha256:fb378b358b657ddfcecd70d4af7d9694079e9d04b79eeb5fdcb200d4181a8e45
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare scalar_statistics_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 27–27](../../../../../tests/unit/scalar_statistics_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
st::Limits limits(){st::Limits result;result.work=2000000;result.rows=8192;result.distinct_keys=8192;result.accounted_bytes=8*1024*1024;result.projection_width=8;result.heavy_keys=64;return result;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set finite owner-statistics limits for scalar tests. |
| inputs / outputs | No input; Limits exits with work=2,000,000, rows=8192, keys=8192, accounted_bytes=8 MiB, projection_width=8, heavy_keys=64. |
| invariants | Statistics modeled bytes and work are bounded independently of workload collection and native MemoryAccount caps. |
| ownership | Returns a value object with no owner or heap report attached. |
| failure | No expected error path. |
| cost | Fixed-size configuration construction. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0008

[Lines 28–28](../../../../../tests/unit/scalar_statistics_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ws::Options enabled(){ws::Options result;result.mode=ws::Mode::counters;result.max_cells=512;result.detail_budget=256;return result;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable numeric workload counters with bounded descriptor and detail capacities. |
| inputs / outputs | No input; Options exits with counters mode, max_cells=512, detail_budget=256. |
| invariants | The C01 workload collector is configured while the O07 physical observation clock is separately disabled by options(). |
| ownership | Returns option values only; runtime copies/configures them later. |
| failure | No expected error path. |
| cost | Fixed-size option construction. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0009

[Lines 29–29](../../../../../tests/unit/scalar_statistics_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(){DeltaOptions result;result.mode=DeltaMode::delta;result.physical.support.observation.mode=ObservationMode::off;return result;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select DeltaRuntime mode with O07 observation disabled for event-oracle tests. |
| inputs / outputs | No input; DeltaOptions exits in delta mode with physical support observation off. |
| invariants | C01 workload counter assertions are not mixed with O07 timing/clock activity. |
| ownership | Returns options by value; no runtime retained. |
| failure | No expected error path. |
| cost | Fixed-size option construction. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0010

[Lines 30–30](../../../../../tests/unit/scalar_statistics_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t count_of(const auto& values){return static_cast<std::uint64_t>(values.size());}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count the number of scalar/map entries as uint64_t. |
| inputs / outputs | Container-like value enters by reference; size converted to uint64_t exits. |
| invariants | Test sizes are below conversion overflow; result is an oracle count. |
| ownership | Input container is borrowed; output is scalar. |
| failure | No expected failure path. |
| cost | One size read and integer conversion. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0011

[Lines 31–31](../../../../../tests/unit/scalar_statistics_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row fields(const Row& row,const Fields& selection){Row out;for(auto field:selection)out.push_back(row.at(field.value));return out;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project a Row by ordered FieldId positions. |
| inputs / outputs | Borrowed source Row and ordered field vector enter; owning Row with values in requested order exits. |
| invariants | Repeated field IDs produce repeated values; .at rejects an invalid field index rather than silently substituting. |
| ownership | Source row and selection are borrowed; result row owns copied Value objects. |
| failure | Invalid field access propagates std::out_of_range to the test. |
| cost | One indexed lookup and Value copy per requested field. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0012

[Lines 32–32](../../../../../tests/unit/scalar_statistics_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Counts project(const Relation& rows,const Fields& selection){Counts out;for(const auto& row:rows)++out[fields(row,selection)];return out;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently group a Relation by an ordered projected key. |
| inputs / outputs | Borrowed relation and FieldIds enter; ordered Row-to-count map exits. |
| invariants | Each source row contributes one count; repeated and empty projections follow the literal requested key layout. |
| ownership | Relation is borrowed; output map owns projected keys and counts. |
| failure | Map/key allocation errors propagate; no runtime capture error is translated. |
| cost | Scans each source row, projects fields, and updates ordered map; cost grows with row count and key width. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0013

[Lines 33–33](../../../../../tests/unit/scalar_statistics_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Counts ones(const Counts& values){Counts out;for(const auto& [key,count]:values){static_cast<void>(count);out.emplace(key,1);}return out;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert positive occurrence multiplicities into a set-membership map. |
| inputs / outputs | Borrowed Row-to-count map enters; owning Row-to-one map exits. |
| invariants | Keys are preserved; positive source counts become exactly one and source counts do not influence membership. |
| ownership | Input map is borrowed; output map owns copied keys. |
| failure | Map allocation failures propagate. |
| cost | One ordered-map insertion per input key. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0014

[Lines 34–34](../../../../../tests/unit/scalar_statistics_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Counts root_counts(const Counts& survivors){return survivors.empty()?Counts{}:Counts{{Row{},count_of(survivors)}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent root parent-support as one empty key weighted by survivor-key count. |
| inputs / outputs | Borrowed survivor multiplicity map enters; owning root Row-to-count map exits. |
| invariants | Empty survivors produce no P key; nonempty survivors produce the nullary Row{} key with count equal to distinct survivor keys. |
| ownership | Input is borrowed; returned key/count map owns its value. |
| failure | Allocation failure propagates for the nonempty case. |
| cost | One size read and at most one map insertion. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0015

[Lines 35–35](../../../../../tests/unit/scalar_statistics_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unknown(const auto& value){check(value.completion==st::Completion::budget_exhausted&&!value.ndv&&!value.heavy_keys&&value.histogram.empty(),"incomplete distribution invented facts");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require exhausted distributions to expose progress only, without inferred NDV or top-K. |
| inputs / outputs | Borrowed Distribution-like value enters; assertion-only result exits. |
| invariants | Completion must be budget_exhausted, NDV and heavy keys absent, histogram empty; visited progress is allowed. |
| ownership | Distribution is borrowed and remains owned by its Component/capture. |
| failure | Failed expectation throws source-located runtime_error; no production exception is generated. |
| cost | Constant metadata checks. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0016

[Lines 36–44](../../../../../tests/unit/scalar_statistics_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void distribution(const auto& actual,const Counts& expected,std::uint64_t visited,std::size_t top=64) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare an exact distribution with an independently grouped map, including native Row tie ordering. |
| inputs / outputs | Borrowed actual distribution, expected key-count map, visited count, and top cap enter; assertion-only result exits. |
| invariants | Checks exact completion, NDV, visited rows, multiplicity histogram and top-K ordered by count descending then Row ascending. |
| ownership | Expected and actual values are borrowed; ranked key vector/map are local and destroyed after the check. |
| failure | Mismatch throws runtime_error; allocation failures in the oracle propagate. |
| cost | Builds histogram in one pass and sorts expected keys; O(K log K) oracle work, separate from the runtime scan budget. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0017

[Lines 45–48](../../../../../tests/unit/scalar_statistics_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void component(const st::Component& actual,const Counts& expected,std::uint64_t cardinality,std::uint64_t visited,std::size_t top=64) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a component to be available with exact cardinality and exact projected distribution. |
| inputs / outputs | Borrowed Component, expected map, cardinality, visited count, and top cap enter; assertion-only result exits. |
| invariants | Availability must be available; report cardinality is checked independently of distribution NDV/visits. |
| ownership | Component and expected map are borrowed; no capture is retained. |
| failure | Mismatch throws runtime_error; budget exhaustion is not accepted as an exact component. |
| cost | Fixed metadata checks plus the distribution oracle's histogram/ranking work. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0018

[Lines 49–55](../../../../../tests/unit/scalar_statistics_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void selection(const st::CapturedSelection& actual,const st::Selection& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify that a captured scope and optional ordered FieldIds exactly preserve the request. |
| inputs / outputs | Borrowed CapturedSelection and request Selection enter; assertion-only result exits. |
| invariants | Checks variant alternative, optional-fields presence, order/repetitions, and concrete source/occurrence/node-role/index ID. |
| ownership | Both selections are borrowed; captured selection remains owned by the report. |
| failure | Invalid variant assumptions fail through checked access/assertion; no mutation occurs. |
| cost | Constant number of variant checks plus O(field count) equality. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0019

[Lines 56–63](../../../../../tests/unit/scalar_statistics_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boundary(const st::CombinedCapture& report,const PhysicalPlan& plan,SupportOwnerId owner,std::uint64_t sequence,bool pending=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one CombinedCapture's real owner, plan, committed sequence, and pending-state boundary. |
| inputs / outputs | Borrowed report and PhysicalPlan, expected SupportOwnerId/sequence, and pending flag enter. |
| invariants | Both state and workload bind to the actual owner and same plan hash/epoch; pending means empty pending-private state, otherwise exact available state. |
| ownership | Report owns both snapshots and plan binding; plan is borrowed only for digest comparison. |
| failure | Mismatch throws source-located runtime_error; no data is copied into a new capture. |
| cost | Fixed stamp/hash checks and optional component-empty check. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0020

[Lines 64–65](../../../../../tests/unit/scalar_statistics_test.cpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L65:sha256:9d201006df4edefb46e0dad617dd1637700a69b52ba38bc7e4c75a543057f4db
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Rank is supplied by the literal list, never by Value/Decimal/string ordering. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 66–76](../../../../../tests/unit/scalar_statistics_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ranked_distribution(const auto& actual,const std::vector<Value>& ordered,const std::vector<std::uint64_t>& multiplicities,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank typed scalar keys using a separately supplied literal order, never Value's native comparator. |
| inputs / outputs | Actual Distribution, explicit Value order, multiplicities, visits, top cap, and repeated-field flag enter. |
| invariants | Computes histogram from multiplicities; ranks indices by multiplicity then literal list position; optionally constructs duplicate scalar field in output key. |
| ownership | Actual distribution/order are borrowed; local rank/histogram vectors own only expected oracle data. |
| failure | Exactness or key mismatch throws runtime_error; container allocation propagates. |
| cost | Linear histogram construction plus sorting O(K log K); intentionally avoids a second scalar ordering implementation. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0022

[Lines 77–106](../../../../../tests/unit/scalar_statistics_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar_order(ScalarType type,const std::vector<Value>& ordered) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise one native scalar type through scans, index buckets, repeated/empty projections, caps, hot keys, and retained captures. |
| inputs / outputs | ScalarType and explicit ordered Values enter; creates a ReferenceTable with two witnesses per value, one-value index, repeated-value projection, and nullary projection. |
| invariants | Scan sees all rows while index sees distinct values; equal Decimal spellings collapse; exact work boundary succeeds and one-under/zero-row limits make distribution unknown but retain known source cardinality; hot-key updates alter counts; captured distribution survives table.clear(). |
| ownership | ReferenceTable owns source rows/index; returned captures own keys after table clear; expected ordered list/multiplicities are borrowed then updated locally. |
| failure | Invalid projection/table errors propagate; budget failure is represented as unknown. No allocation-failure injector is used. |
| cost | Constructs 2K rows, runs scan/index/grouping in four request shapes and two cap checks; work is bounded by Limits and is not benchmark timing. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0023

[Lines 107–117](../../../../../tests/unit/scalar_statistics_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar_orders() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply ordered boundary values for integer, bool, date, decimal, and byte-string comparison tests. |
| inputs / outputs | No input; runs scalar_order for min/max int64, both booleans, date boundaries/leap days, decimal scales/extremes, and binary strings containing NUL and high bytes. |
| invariants | The literal list is the oracle order; string values are byte sequences and equal decimal spellings remain one key. |
| ownership | Each temporary Value vector owns its scalar/string contents until its scalar_order call completes. |
| failure | Date/decimal parse and allocation failures propagate. |
| cost | Builds finite fixtures (including 1024-byte strings) and delegates scans to scalar_order. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0024

[Lines 118–119](../../../../../tests/unit/scalar_statistics_test.cpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L119:sha256:ae0449014faf6f2b73a2929eef7f130957ea60640e488ff612d1c80e0003b646
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Independent arithmetic: do not call Cell::observe/merge or collector hooks. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 120–120](../../../../../tests/unit/scalar_statistics_test.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observation(ws::Cell& cell,std::uint64_t value){if(!cell.count)cell.min=cell.max=value;else{cell.min=std::min(cell.min,value);cell.max=std::max(cell.max,value);}++cell.count;cell.sum+=value;std::size_t bin=0;for(auto x=value;x;x/=2)++bin;++cell.bins[bin];}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Update workload Cell expectations with local min/max/count/sum and logarithmic value bins. |
| inputs / outputs | Mutable local Cell and observed unsigned value enter; the cell is updated in place. |
| invariants | Bin index is derived by repeated integer division by two; value zero enters bin zero; this oracle does not call Cell::observe or collector hooks. |
| ownership | Mutates only the caller-owned expected Cell; no snapshot memory is borrowed or modified. |
| failure | Arithmetic follows fixture values; container/state errors do not apply. |
| cost | Constant fixed-width counter updates plus at most 64 divisions. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0026

[Lines 121–121](../../../../../tests/unit/scalar_statistics_test.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void transition(ws::Cell& cell,std::uint64_t before,std::uint64_t after){if(before==after)return;++cell.changes;if(!before)++cell.zero_to_positive;if(!after)++cell.positive_to_zero;observation(cell,after);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record a support-count transition in the independent workload oracle. |
| inputs / outputs | Mutable expected Cell and before/after support counts enter; equal counts are ignored; changed counts increment crossing fields and observe after-value. |
| invariants | Zero-to-positive and positive-to-zero are counted only at their boundaries; every changed support value, including zero, contributes to the after-value histogram. |
| ownership | Expected Cell is mutated in place; inputs are scalar. |
| failure | No expected exception for fixture-domain counts. |
| cost | Constant metadata work plus logarithmic-bin division for after-value. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0027

[Lines 122–139](../../../../../tests/unit/scalar_statistics_test.cpp#L122); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Events {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the independent typed-alias event model's descriptors and expected workload cells. |
| inputs / outputs | Initial Snapshot enters; copies descriptor values and creates one default Cell per descriptor. |
| invariants | Model never uses runtime journal or collector outputs to derive event values; check_snapshot later compares full descriptors/cells/metadata and unavailable arrival rate. |
| ownership | Events owns copied descriptor and Cell vectors; it does not keep a Snapshot reference. |
| failure | Vector allocation failure propagates; missing descriptor lookup throws runtime_error. |
| cost | Copies D descriptors and initializes D cells; subsequent lookup is linear in D. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0028

[Lines 140–149](../../../../../tests/unit/scalar_statistics_test.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan alias_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a generalized two-alias self-join over typed values with a right-alias literal predicate. |
| inputs / outputs | No input; returns lowered PhysicalPlan over one six-column typed source and two occurrences. |
| invariants | Head order includes decimal/string/int/bool/date plus repeated decimal alias; first atom ignores tag and second requires tag=0; root is generalized. |
| ownership | Plan owns catalog/query/tree; temporary construction values do not escape except through the plan. |
| failure | Planner validation/resource failure propagates. |
| cost | Builds/lower one two-occurrence plan; no rows are scanned. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0029

[Lines 150–150](../../../../../tests/unit/scalar_statistics_test.cpp#L150); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L150-L150:sha256:9f486479ee3fad2f49b8f9be109f34d6e77742fca21eea415d1d28b11722578d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare scalar_statistics_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0030

[Lines 151–158](../../../../../tests/unit/scalar_statistics_test.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
st::OwnerRequest alias_request(const PhysicalPlan& plan){st::OwnerRequest out;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select every scalar source field, repeated/reordered/empty projection, both occurrence maps, all node roles, and admitted indexes. |
| inputs / outputs | Borrowed PhysicalPlan enters; owning OwnerRequest exits. |
| invariants | Selection order is explicit; records/survivors carry full fields while P/E have no projection; index IDs are actual plan requirements. |
| ownership | Request owns vectors; plan is borrowed while enumerating indexes. |
| failure | Request allocation or later capture validation failure propagates. |
| cost | Creates fixed source/occurrence/node selections plus one selection per actual index. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0031

[Lines 159–160](../../../../../tests/unit/scalar_statistics_test.cpp#L159); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L159-L160:sha256:16e83749d39ae008855446fcb6e79ff16ce21b4dff25689173cfc4285c312854
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare scalar_statistics_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0032

[Lines 161–161](../../../../../tests/unit/scalar_statistics_test.cpp#L161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit AliasModel(const ws::Snapshot& initial):events(initial){}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize AliasModel from the current workload descriptor schema. |
| inputs / outputs | Borrowed workload Snapshot enters; model's Event oracle copies descriptors and initializes two empty occurrence maps and source relation. |
| invariants | Starting event counters are zero; model data starts empty and does not inspect owner rows to infer a source state. |
| ownership | AliasModel owns source/maps/Event vectors; snapshot is borrowed only during descriptor copy. |
| failure | Copy/allocation failure propagates. |
| cost | Copies descriptor array and allocates an equally sized zero Cell vector. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0033

[Lines 162–162](../../../../../tests/unit/scalar_statistics_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Counts joined() const {Counts out;for(const auto& [key,count]:native[0]){static_cast<void>(count);if(native[1].contains(key))out.emplace(key,1);}return out;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the set of full keys present in both alias derivation maps. |
| inputs / outputs | No input; returns owning key-to-one map for the intersection. |
| invariants | Occurrence multiplicity is ignored for membership; a key appears once iff each alias map contains it. |
| ownership | Both occurrence maps are borrowed; result map owns copied keys. |
| failure | Map allocation failure propagates. |
| cost | Scans the first map and probes the second once per key. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0034

[Lines 163–163](../../../../../tests/unit/scalar_statistics_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Counts candidates() const {auto out=ones(native[0]);for(const auto& [key,count]:native[1]){static_cast<void>(count);out[key]=1;}return out;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute generalized candidate union across both alias maps. |
| inputs / outputs | No input; returns owning key-to-one map of keys in either occurrence. |
| invariants | Duplicate keys across aliases collapse to one candidate; per-alias derivation counts do not become candidate multiplicity. |
| ownership | Both occurrence maps are borrowed; output owns its keys. |
| failure | Map allocation failure propagates. |
| cost | Copies first map keys, scans second map, and inserts/updates union keys. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0035

[Lines 164–177](../../../../../tests/unit/scalar_statistics_test.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply(const PhysicalPlan& plan,SetOperation op,const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical set event to the independent alias, derivation, support, and probe model. |
| inputs / outputs | Borrowed plan, insert/erase operation, and tagged physical Row enter; mutates source set, occurrence counts, and expected Events. |
| invariants | Duplicate/absent input only updates input/no-op counters; accepted aliases update derivation count, S/P/E transitions only on zero-boundary changes, and generalized probes use the actual edge/role identities. Root membership is intersection, candidate membership is union. |
| ownership | Mutates only local AliasModel; input row and plan are borrowed; expected descriptors/cells remain model-owned. |
| failure | Erase without prior derivation or missing compiled edge fails an explicit oracle check; allocation errors propagate. |
| cost | Per event looks up descriptors linearly, mutates ordered maps, and may recalculate root joins; test oracle can be costlier than engine and is not timing evidence. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0036

[Lines 178–189](../../../../../tests/unit/scalar_statistics_test.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_state(const st::OwnerCapture& report,const PhysicalPlan& plan,const st::OwnerRequest& request) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute all owner components from the model source relation and compare selection/layout/population facts. |
| inputs / outputs | Borrowed OwnerCapture, plan, and request enter; assertion-only result exits. |
| invariants | Regroups source rows for each occurrence; derives generalized candidates/root intersection, native support, P/E and index-visible populations; requires matching node kind, projection, cardinality, distribution and admitted index full separator. |
| ownership | Capture/request/plan are borrowed; local literal maps own grouped keys only for this call. |
| failure | Assertion mismatch or invalid expected index/missing visible relation throws runtime_error; no production capture result is altered. |
| cost | Scans source relation, rebuilds two occurrence maps, then checks each requested component; cost scales with rows, requested components and key grouping. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0037

[Lines 190–190](../../../../../tests/unit/scalar_statistics_test.cpp#L190); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L190-L190:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in scalar_statistics_test.cpp: struct AliasModel. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0038

[Lines 191–191](../../../../../tests/unit/scalar_statistics_test.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row tagged(Row key,std::int64_t tag){key.push_back(n(tag));return key;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append a scalar tag to a typed key for alias predicate input rows. |
| inputs / outputs | Owning Row and int64 tag enter by value; new owning Row exits. |
| invariants | Original field order is preserved and tag is last. |
| ownership | Value argument is copied/moved locally; returned row owns its values. |
| failure | Row allocation failure propagates. |
| cost | One vector append. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0039

[Lines 192–215](../../../../../tests/unit/scalar_statistics_test.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_alias_trace() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a typed self-join trace over extreme scalar values while independently checking state and workload event cells after each event. |
| inputs / outputs | Constructs two aliases over int64/bool/date/Decimal/string fields and tag predicate; inserts eleven tagged values, checks a shared-limit partial capture, erases to empty, then resets workload counters. |
| invariants | Oracle source rows and alias maps determine every component and event; decimal alternate spellings compare equal; binary strings survive; incomplete later projection has no invented facts while earlier component remains exact; retained capture is unchanged after later updates/reset. |
| ownership | Runtime and model are local; retained CombinedCapture owns keys/plan/workload cells independent of runtime and model mutation. |
| failure | Budget exhaustion yields explicit unknown; invalid update/native errors propagate; all failed checks fail main. |
| cost | Repeated capture scans all selected typed populations per event and rebuilds literal maps; fixture tests correctness at finite sizes, not a complexity/performance theorem. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0041

[Lines 217–225](../../../../../tests/unit/scalar_statistics_test.cpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan constraint_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a one-node child relation with enforced unique/FK constraints and decimal(4,2) amount. |
| inputs / outputs | No input; plan exits with child(id,parent,amount) referencing parent(id,tag), unique child/parent IDs, FK child.parent-&gt;parent.id, and head parent. |
| invariants | Declared constraints and decimal precision are actual catalog properties; ignored child id is not part of the output head. |
| ownership | Returned plan owns catalog constraints and lowered query. |
| failure | Planner/catalog validation errors propagate. |
| cost | Builds and lowers a fixed two-table one-node plan. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0042

[Lines 226–229](../../../../../tests/unit/scalar_statistics_test.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
st::OwnerRequest constraint_request(){return {{{st::SourceScope{{0}},Fields{{0},{1},{2}}},{st::SourceScope{{0}},Fields{{2},{1},{2}}},{st::SourceScope{{0}},Fields{}},
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request typed source, occurrence, records, survivors, parent-support, and visible statistics for the constrained plan. |
| inputs / outputs | No input; owning OwnerRequest exits with 11 ordered components. |
| invariants | Source projections include reordered and repeated decimal field positions; node records/S use key fields; P/E remain full stored supports. |
| ownership | Request owns all selection and field vectors. |
| failure | Vector allocation failure propagates; actual ID validation occurs during capture. |
| cost | Builds fixed request metadata only. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0043

[Lines 230–249](../../../../../tests/unit/scalar_statistics_test.cpp#L230); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ConstraintModel {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a literal constrained relation/derivation/event model independent of runtime indexes and counters. |
| inputs / outputs | Initial workload Snapshot enters; model stores two source relations, native child projected derivation counts, and an Events oracle. |
| invariants | Source sets reflect accepted catalog rows; derivations are regrouped by child parent/amount; visible, root P, and S/E transitions are derived from local maps. |
| ownership | All maps/sets/Event vectors are model-owned; initial Snapshot is borrowed only during copying. |
| failure | Allocation failure propagates; inconsistent erase is rejected by model checks. |
| cost | Stores O(source rows + projected keys + descriptor count) oracle state and rebuilds expected populations on check. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0044

[Lines 250–269](../../../../../tests/unit/scalar_statistics_test.cpp#L250); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constrained_trace() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check enforced unique/FK/scalar-limit failures against same-owner rollback and constrained literal statistics. |
| inputs / outputs | Creates constrained DeltaRuntime, request, and independent model; attempts invalid child/parent updates, accepts legal updates, tests pending rollback, erases to empty. |
| invariants | Every rejected update preserves owner, sequence, ready phase, canonical state and data freshness while increasing abort accounting; successful events compare exact owner components and workload cells; pending private work is hidden and rollback publishes no cells; final source/derivation maps are empty. |
| ownership | Runtime owns query state; model owns its separate relation/map oracle; saved report is an owning capture and stays usable after errors. |
| failure | Catches expected Error codes constraint_violation and scalar_overflow only; unexpected errors or leaked state fail the test. |
| cost | Executes fixed accepted/rejected trace and recaptures full selections after each transition; oracle cost is bounded by fixture rows and not an update-time measurement. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |

## B0045

[Lines 270–270](../../../../../tests/unit/scalar_statistics_test.cpp#L270); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L270-L270:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in scalar_statistics_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0046

[Lines 271–271](../../../../../tests/unit/scalar_statistics_test.cpp#L271); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{scalar_orders();typed_alias_trace();constrained_trace();std::cout<<"C01 typed scalar/constraint statistics: 7 groups passed\n";}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run scalar ordering, typed alias, and constrained update traces as one test executable. |
| inputs / outputs | No input; invokes scalar_orders, typed_alias_trace, and constrained_trace; prints success or catches std::exception and returns failure. |
| invariants | All test semantics are delegated to three literal oracle groups; output does not assert general scalar-order or update-class guarantees beyond fixtures. |
| ownership | All runtime, model, and capture values are local; saved reports own copied data. |
| failure | Catches std::exception to print failure and return 1; no failure is swallowed. |
| cost | Runs finite scalar boundary fixtures, typed event traces, and constrained updates; no performance measurement. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |
