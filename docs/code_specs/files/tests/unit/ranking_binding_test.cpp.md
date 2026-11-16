# `tests/unit/ranking_binding_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_binding_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `39290ab9c1f6c23aa3b31e7829edb682a2d11fcc1b486925d21335aca45f5b56`. 113 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/ranking_binding_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../tests/unit/ranking_binding_test.cpp#L12) | Callable definition: void check(bool x,const char* message) | calls std::runtime_error; guard void check(bool x,const char* message){if(!x){throw std::runtime_error(message);}} · [reviewed contract](#b0002) |
| [B0003 · 13–28](../../../../../tests/unit/ranking_binding_test.cpp#L13) | Callable definition: void compare(const Catalog& c,const Query& q) | calls planner::frozen_binding_v2::binding_bytes, check, planner::binding_detail::encode, size; guard check(old==planner::binding_detail::encode(c,q),"P07 binding bytes changed"); · [reviewed contract](#b0003) |
| [B0004 · 29–91](../../../../../tests/unit/ranking_binding_test.cpp#L29) | Callable definition: void native_binding() | calls std::string, Date::parse, Decimal::parse, planner::frozen_binding_v2::binding_bytes; guard check(io::input_catalog_sha256(catalog)==io::input_catalog_sha256(native.catalog()) &&; returns std::pair&lt;std::string,std::string&gt;{error.code(),error.what()}; growth insert; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 92–92](../../../../../tests/unit/ranking_binding_test.cpp#L92) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 93–113](../../../../../tests/unit/ranking_binding_test.cpp#L93) | Callable definition: int main() | calls compare, raw, push_back, Date::parse; guard check(planner::binding_detail::encode(changed,q)!=planner::binding_detail::encode(c,q),"catalog sta…; returns 1; growth push_back · [reviewed contract](#b0006) |

## B0001

[Lines 1–11](../../../../../tests/unit/ranking_binding_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:530c9ac6616ec0f240d3688cf9094f6ff58cb53258960d51c64fa06f8fc9f599
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_binding_test.cpp: include "candidate_binding.hpp", "ranking_detail.hpp", "frozen_binding_v2.hpp", "crown/planner/lower.hpp", "crown/catalog/catalog.hpp", "crown/io/ingest.hpp", &lt;iostream&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–12](../../../../../tests/unit/ranking_binding_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool x,const char* message){if(!x){throw std::runtime_error(message);}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a test exception when one binding invariant is false. |
| inputs / outputs | Receives a condition and message; returns no value. |
| invariants | No test state is modified. |
| ownership | Message is borrowed unless failure constructs exception text. |
| failure | False throws runtime_error. |
| cost | One Boolean branch; error construction only on failure. |
| Design | [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp) |

## B0003

[Lines 13–28](../../../../../tests/unit/ranking_binding_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare(const Catalog& c,const Query& q){
  const auto old=planner::frozen_binding_v2::binding_bytes(c,q);
  check(old==planner::binding_detail::encode(c,q),"P07 binding bytes changed");
  planner::ranking::Limits limits;limits.binding_key_bytes=static_cast<std::uint64_t>(old.size());limits.payload_bytes=static_cast<std::uint64_t>(old.size());
  planner::ranking::detail::Budget budget(limits);const auto actual=planner::ranking::detail::binding(c,q,budget);
  check(actual==old && budget.usage.payload_bytes==old.size(),"exact binding cap");
  auto low=limits;low.payload_bytes-=1;planner::ranking::detail::Budget stopped(low);bool hit=false;
  try{static_cast<void>(planner::ranking::detail::binding(c,q,stopped));}
  catch(const planner::ranking::detail::Failure& e){hit=e.stop==planner::ranking::Stop::byte_limit;}
  check(hit && stopped.usage.binding_key_bytes<=low.payload_bytes,"binding allocated beyond residual payload admission");
  limits.payload_bytes+=19;planner::ranking::Usage prior;prior.payload_bytes=20;
  planner::ranking::detail::Budget residual(limits,prior);hit=false;
  try{static_cast<void>(planner::ranking::detail::binding(c,q,residual));}
  catch(const planner::ranking::detail::Failure& e){hit=e.stop==planner::ranking::Stop::byte_limit;}
  check(hit && residual.usage.payload_bytes==20,"prior payload was not protected");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the historical P07 binding bytes with bounded C02 encoding. |
| inputs / outputs | Receives Catalog and Query, builds expected bytes, checks exact key/payload caps, a one-byte-short cap, and a nonzero prior payload allowance. |
| invariants | Successful bytes match exactly; the cap applies to cumulative logical payload admission and preserves prior usage. |
| ownership | Catalog/Query are borrowed; expected/actual strings and Budget are local. |
| failure | The bounded encoder signals byte_limit through its Failure; checks expose any over-admission. |
| cost | Encodes the catalog/query multiple times; work follows their names, constraints, terms, and bytes. |
| Design | [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp) |

## B0004

[Lines 29–91](../../../../../tests/unit/ranking_binding_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_binding(){
  CompiledProgram native;std::string expected;
  {
    Table table{"values",{{"key",ScalarType::int64},{"i",ScalarType::int64},
      {"s",ScalarType::string},{"b",ScalarType::boolean},{"d",ScalarType::date},
      {"n",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,12}},
      {"unused",ScalarType::boolean}}};
    table.source_schema_version=13;
    table.constraints={UniqueConstraint{"key",{ColumnId{0}},ConstraintStatus::enforced},
      ForeignKeyConstraint{"self",{ColumnId{0}},TableId{0},{ColumnId{0}},ConstraintStatus::untrusted},
      ForeignKeyConstraint{"parent",{ColumnId{0}},TableId{1},{ColumnId{0}},ConstraintStatus::enforced}};
    table.statistics.row_count=997;table.statistics.distinct_counts={{{ColumnId{0}},991}};
    table.key_hints={{{ColumnId{1}},std::string("binary\0hint",11)}};
    Table parent{"parent",{{"key",ScalarType::int64}}};
    parent.constraints={UniqueConstraint{"key",{ColumnId{0}},ConstraintStatus::enforced}};
    Catalog catalog{7,{table,parent}};
    Query query{{{"x",ScalarType::int64}},{{"v",TableId{0},{VariableId{0},Value{INT64_MIN},
      Value{std::string("a\0b",3)},Value{true},Value{Date::parse("0001-01-01")},
      Value{Decimal::parse("-99999999999999999999999999.123456789012")},IgnoredColumn{}}}},
      {{VariableId{0},"first"},{VariableId{0},"again"}},false};
    const FreeConnexTree tree{NodeId{0},{{"v",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
    expected=planner::frozen_binding_v2::binding_bytes(catalog,query);
    native=CompiledProgram::standalone(planner::lower_tree(catalog,query,tree));
    const Row row{std::int64_t{1},INT64_MIN,std::string("a\0b",3),true,Date::parse("0001-01-01"),
      Decimal::parse("-99999999999999999999999999.123456789012"),false};
    const Database valid{{Relation{row},Relation{Row{std::int64_t{1}}}}};
    const io::InputEvent event{{1,TableId{0},SetOperation::insert,row},{}};
    check(io::input_catalog_sha256(catalog)==io::input_catalog_sha256(native.catalog()) &&
      io::write_input_json(event,catalog)==io::write_input_json(event,native.catalog()) &&
      io::write_input_binary(event,catalog)==io::write_input_binary(event,native.catalog()),
      "native wire encoding changed typed scalars, constraints, statistics or binary metadata");
    validate_database(catalog,valid);validate_database(native.catalog(),valid);
    check(catalog::find_table(native.catalog(),"values")==TableId{0} && catalog::requires_format3(native.catalog()),
      "native catalog lookup or format metadata changed");
    const auto failure=[](const auto& schema,const Database& database){
      try{validate_database(schema,database);}
      catch(const Error& error){return std::pair<std::string,std::string>{error.code(),error.what()};}
      throw std::runtime_error("invalid database accepted by catalog validator");
    };
    for(unsigned change=0;change<5;++change){
      auto database=valid;auto bad=row;
      if(change==0)bad.pop_back();
      if(change==1)bad[0]=std::string("wrong type");
      if(change==2)bad[5]=Decimal::parse("1.1234567890123");
      if(change==3)bad[6]=true;
      if(change<4){if(change<3)database.tables[0].clear();database.tables[0].insert(bad);}
      else database.tables[1].clear();
      const auto old=failure(catalog,database);const auto actual=failure(native.catalog(),database);
      const auto code=change<2?"invalid_update":change==2?"scalar_overflow":"constraint_violation";
      check(old.first==code && actual==old,"native database validation changed a shape, scalar or constraint failure");
    }
  }
  check(planner::binding_detail::encode(native.catalog(),native.query())==expected,
    "native binding differs from frozen compiler format after source destruction");
  planner::ranking::Limits limits;limits.binding_key_bytes=expected.size();limits.payload_bytes=expected.size();
  planner::ranking::detail::Budget exact(limits);
  check(planner::ranking::detail::binding(native.catalog(),native.query(),exact)==expected &&
    exact.usage.payload_bytes==expected.size(),"native exact binding admission changed");
  --limits.payload_bytes;planner::ranking::detail::Budget low(limits);bool stopped=false;
  try{static_cast<void>(planner::ranking::detail::binding(native.catalog(),native.query(),low));}
  catch(const planner::ranking::detail::Failure& error){stopped=error.stop==planner::ranking::Stop::byte_limit;}
  check(stopped,"native binding escaped one-under admission");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a standalone native artifact owns the complete binding after its source scope ends. |
| inputs / outputs | Builds and lowers a typed catalog/query/tree inside a local source scope. While those values are alive it validates the original and compiled catalogs against valid and five malformed databases; after the source scope ends it compares retained native binding bytes and exact/one-under payload admission. |
| invariants | The artifact binding matches the frozen v2 encoding; exact caps pass and one-under payload cap stops before excess admitted bytes. |
| ownership | CompiledProgram outlives local Catalog/Query/Database construction; it must retain its compiled identity, not borrow their strings. |
| failure | Bad database mutations fail validation; bounded binding failures must report byte_limit. |
| cost | One lower and validation batch with several source mutations; byte counters describe logical admission, not heap or CPU. |
| Design | [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp) |

## B0005

[Lines 92–92](../../../../../tests/unit/ranking_binding_test.cpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L92:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_binding_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 93–113](../../../../../tests/unit/ranking_binding_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{
  Catalog c;Query q;compare(c,q);
  c.version=UINT64_MAX;
  const std::string raw("a\0\xff",3);
  Table t{raw,{{raw,ScalarType::string},{"i",ScalarType::int64},{"b",ScalarType::boolean},{"d",ScalarType::date},{"n",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,12}}}};
  t.source_schema_version=UINT64_MAX;t.constraints.push_back(UniqueConstraint{raw,{ColumnId{1}},ConstraintStatus::enforced});
  t.constraints.push_back(ForeignKeyConstraint{"fk",{ColumnId{1}},TableId{0},{ColumnId{1}},ConstraintStatus::untrusted});
  t.statistics.row_count=UINT64_MAX;t.statistics.distinct_counts.push_back({{ColumnId{0},ColumnId{0}},UINT64_MAX});t.key_hints.push_back({{ColumnId{1}},raw});c.tables.push_back(t);
  q.variables={{raw,ScalarType::string}};
  q.atoms.push_back({raw,TableId{0},{VariableId{0},Value{INT64_MIN},Value{true},Value{Date::parse("0001-01-01")},Value{Decimal::parse("-99999999999999999999999999.123456789012")}}});
  q.atoms.push_back({"alias",TableId{0},{Value{raw},IgnoredColumn{},Value{false},Value{Date::parse("9999-12-31")},Value{Decimal::parse("0.00000000000000000000000000000000000001")}}});
  q.head={{VariableId{0},raw},{VariableId{0},"again"}};compare(c,q);
  auto changed=c;changed.tables[0].statistics.row_count=17;
  check(planner::binding_detail::encode(changed,q)!=planner::binding_detail::encode(c,q),"catalog statistics erased from proof namespace");
  q.contradiction=true;compare(c,q);
  planner::ranking::Limits zero;zero.payload_bytes=0;planner::ranking::detail::Budget b(zero);bool blocked=false;
  try{static_cast<void>(planner::ranking::detail::binding(c,q,b));}catch(const planner::ranking::detail::Failure& e){blocked=e.stop==planner::ranking::Stop::byte_limit;}
  check(blocked && b.usage.binding_key_bytes==0,"prefix not admitted before allocation");
  native_binding();
  std::cout<<"C02 binding: exact predecessor bytes and pre-allocation caps passed\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run core and native binding comparisons over representative catalog/query values. |
| inputs / outputs | Calls compare for multiple fixtures and native_binding for one standalone artifact. |
| invariants | The harness checks binding identity and validation, not ranking or runtime installation. |
| ownership | All cases are local; native_binding retains its result only across the inner source scope. |
| failure | Assertion exceptions fail the executable. |
| cost | A finite set of catalog/query encodes plus one native lowering/validation campaign. |
| Design | [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp) |
