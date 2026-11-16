# `tests/unit/sql_aggregate_descriptor_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `f4c482a17c19d6050e361662608a74b4c4a0f107c64b15f88aee053788019ee7`. 146 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 17–22](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L17) | Callable definition: Catalog catalog(bool opaque=false) | calls push_back, std::string; returns schema; growth push_back · [reviewed contract](#b0002) |
| [B0003 · 23–29](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L23) | Callable definition: frontend::SqlAggregateProgram bind(bool opaque=false,std::string_view sql= "SELECT a.g,COUNT(*),SUM(a.x),AVG(a.x) FROM r a WHERE … | calls catalog, frontend::bind_sql_aggregate, assert, std::move; guard assert(std::holds_alternative&lt;frontend::SqlAggregateProgram&gt;(result));return std::get&lt;frontend::Sql…; returns std::get&lt;frontend::SqlAggregateProgram&gt;(std::move(result)) · [reviewed contract](#b0003) |
| [B0004 · 30–34](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L30) | Callable definition: FreeConnexTree tree(const frontend::SqlAggregateProgram& program) | calls source_program, contradiction, export_core, planner::minimum_tree; guard assert(selected.tree);return *selected.tree;; returns {}; *selected.tree · [reviewed contract](#b0004) |
| [B0005 · 35–39](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L35) | Callable definition: runtime::sql_aggregate::Options normal() | calls ; returns options · [reviewed contract](#b0005) |
| [B0006 · 40–40](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L40) | Callable definition: Cell number(std::int64_t value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0006) |
| [B0007 · 41–42](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L41) | Explanatory comments or spacing. | source comment (unverified): // Independent test framing permits checksum-valid hostile CBOR without codec · [reviewed contract](#b0007) |
| [B0008 · 43–43](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L43) | Callable definition: void word(std::string& out,std::uint64_t value) | calls ; 1 loop sites; source comment (unverified): // Independent test framing permits checksum-valid hostile CBOR without codec · [reviewed contract](#b0008) |
| [B0009 · 44–49](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L44) | Callable definition: std::string envelope(std::string_view binding,std::string_view recipe) | calls word, size, result, sha256_fixed; returns result+body · [reviewed contract](#b0009) |
| [B0010 · 50–50](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L50) | Callable definition: std::string bytes(const std::vector&lt;std::uint8_t&gt;& value) | calls data, size; returns {reinterpret_cast&lt;const char*&gt;(value.data()),value.size()} · [reviewed contract](#b0010) |
| [B0011 · 51–53](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L51) | Callable definition: template&lt;class Action&gt; void wire_rejected(Action action) | calls deny, action, assert; guard bool failed=false;{s04_alloc::Scope deny(0);try{action();}catch(const recovery::ImageFailure&){fail… · [reviewed contract](#b0011) |
| [B0012 · 54–56](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L54) | Callable definition: template&lt;class Action&gt; void refused(Action action) | calls action, assert; guard bool failed=false;try{action();}catch(const std::exception&){failed=true;}assert(failed); · [reviewed contract](#b0012) |
| [B0013 · 57–80](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L57) | Callable definition: void cbor_and_frame(const char* fixture) | calls envelope, std::string_view, file, assert; guard std::ifstream file(fixture);std::string hex;file&gt;&gt;hex;assert(hex.size()==valid.size()*2);; 5 loop sites · [reviewed contract](#b0013) |
| [B0014 · 81–130](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L81) | Callable definition: void genuine_round_trip(bool indexed,bool opaque) | calls bind, s04_runtime::options, reset, resource::MemoryAccount::create; guard assert(restored.descriptor.bytes()==admitted.descriptor.bytes());assert(restored.descriptor.program…; 2 loop sites; source comment (unverified): // Finite host replay admits original unlimited producer compile policies. · [reviewed contract](#b0014) |
| [B0015 · 131–140](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L131) | Callable definition: void receiving_caps() | calls bind, resource::MemoryAccount::create, ar::admit_into, tree; guard assert(trial.statistics().current.allocations==1);} · [reviewed contract](#b0015) |
| [B0016 · 141–141](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L141) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 142–146](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L142) | Callable definition: int main(int argc,char** argv) | calls assert, cbor_and_frame, genuine_round_trip, receiving_caps; guard assert(argc==2);cbor_and_frame(argv\[1\]);; 2 loop sites · [reviewed contract](#b0017) |

## B0001

[Lines 1–16](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:2f915e01f86b935bb9453a4a74c8b8fa3b69b6719835e92c6e26eb71e1f8d0e3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_descriptor_test.cpp: include "crown/recovery/sql_aggregate_descriptor.hpp", "crown/ir/digest.hpp", "crown/io/document.hpp", "crown/planner/oracle.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;cassert&gt;, &lt;fstream&gt;, &lt;iostream&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–22](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog catalog(bool opaque=false) {
  Catalog schema{1,{{"r",{{"id",ScalarType::int64},{"g",ScalarType::string,true},
      {"x",ScalarType::int64,true},{"flag",ScalarType::boolean}}},{"unused",{{"z",ScalarType::int64}}}}};
  if(opaque)schema.tables[0].key_hints.push_back({{ColumnId{0}},std::string(1,static_cast<char>(0xff))});
  return schema;
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the descriptor fixture catalog with one used and one unused physical table, optionally carrying an opaque hint byte. |
| inputs / outputs | Returns table \`r\` with id/group/value/flag columns plus unused table \`unused\`; opaque mode adds an invalid UTF8 byte to a catalog hint. |
| invariants | The descriptor must preserve real catalog bytes even when a hint is not UTF8; the unused table is part of original catalog identity. |
| ownership | Returns a test-owned Catalog value passed to the genuine SQL binder. |
| failure | No expected production failure; invalid fixture binding is caught by the caller assertion. |
| cost | Small ordinary test fixture construction. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0003

[Lines 23–29](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::SqlAggregateProgram bind(bool opaque=false,std::string_view sql=
    "SELECT a.g,COUNT(*),SUM(a.x),AVG(a.x) FROM r a WHERE a.id>$1 AND a.flag GROUP BY a.id,a.g") {
  frontend::SqlAggregateBindOptions options;options.source.binding.parameters={{"threshold",ScalarType::int64}};
  options.source.parameters={Value{std::int64_t{2}}};options.kernel.average_scale=2;
  const auto schema=catalog(opaque);auto result=frontend::bind_sql_aggregate(sql,schema,options);
  assert(std::holds_alternative<frontend::SqlAggregateProgram>(result));return std::get<frontend::SqlAggregateProgram>(std::move(result));
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a genuine SQL aggregate program from original SQL, typed threshold parameter, catalog and AVG scale. |
| inputs / outputs | Binds \`SELECT a.g, COUNT(*), SUM(a.x), AVG(a.x)\` with id threshold and flag predicate, grouping by id and nullable g. |
| invariants | Uses the actual frontend binder and asserts the result is the genuine program alternative; it does not manufacture binding metadata. |
| ownership | Returned program owns compiler metadata through the binder’s normal standalone account. |
| failure | A binding diagnostic makes the test assertion fail. |
| cost | Actual cold parser/binder fixture cost; not an update-path measurement. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0004

[Lines 30–34](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree tree(const frontend::SqlAggregateProgram& program) {
  if(program.source_program().contradiction())return {};
  const auto core=program.source_program().export_core();const auto selected=planner::minimum_tree(core.catalog,core.query);
  assert(selected.tree);return *selected.tree;
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose a genuine valid FreeConnexTree for the fixture’s bound query. |
| inputs / outputs | For contradiction returns the authentic empty tree; otherwise asks the planner for a minimum tree and requires a selected result. |
| invariants | This test helper supplies one accepted tree to exercise descriptor storage; it does not establish that admit_into itself proves minimality. |
| ownership | Returns an owned tree value copied into subsequent factory calls. |
| failure | Missing planner result fails the test assertion. |
| cost | Cold planner test-fixture work only. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0005

[Lines 35–39](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::sql_aggregate::Options normal() {
  runtime::sql_aggregate::Options options;options.capture_changes=true;options.count_limit=10;
  options.source.native.multiplicity_limit=30;options.group_work_limit=200000;
  options.source.source_work_limit={200000,200000,8ULL*1024*1024,0,0};return options;
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a concrete original operational policy for descriptor round-trip tests. |
| inputs / outputs | Enables change capture, caps count at 10, native multiplicity at 30, group work at 200000 and source work with the five-dimensional tuple. |
| invariants | These values are serialized/rebound as producer policy; they do not mint receiving account capacity. |
| ownership | Returns a small test policy value copied into actual runtime factories. |
| failure | No failure by construction; unsupported policy is rejected by the factory under test. |
| cost | Constant option setup. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |

## B0006

[Lines 40–40](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell number(std::int64_t value) {return storage::ScalarView{value};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a signed integer into the SQL row test cell alternative. |
| inputs / outputs | Returns a ScalarView-backed Cell for an int64 value. |
| invariants | Cell remains an explicit nullable SQL cell shape used in the genuine source replacement. |
| ownership | The Cell view borrows only the immediate scalar value representation, which is copied into the batch input during the call. |
| failure | No explicit error path. |
| cost | Constant stack construction. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp) |

## B0007

[Lines 41–42](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L42:sha256:59c59f7dbd56ed13ba121c04ce582fa495111504309c66586661bfb50e484d15
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Independent test framing permits checksum-valid hostile CBOR without codec encoder authority. This follows the documented 148-byte protected envelope. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 43–43](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void word(std::string& out,std::uint64_t value) {for(unsigned i=0;i<8;++i)out+=static_cast<char>(value>>(8*i));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write an unsigned 64-bit little-endian word for an independent hostile-frame test encoder. |
| inputs / outputs | Appends exactly eight low-to-high bytes to the test string. |
| invariants | Does not call the production encoder, so checksum-valid malformed payloads are independent inputs. |
| ownership | Mutates only the caller’s test-owned string. |
| failure | String allocation failures propagate from test setup. |
| cost | Eight append operations per field. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0009

[Lines 44–49](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string envelope(std::string_view binding,std::string_view recipe) {
  std::string body;word(body,binding.size());body+=binding;word(body,recipe.size());body+=recipe;
  std::string result("CROWNAD2\x01\x00\x00\x00",12);word(result,body.size());
  const auto hash=sha256_fixed(body);result.append(hash.data(),hash.size());
  const auto prefix=sha256_fixed(result);result.append(prefix.data(),prefix.size());return result+body;
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a CROWNAD2 length/hash envelope around arbitrary binding and recipe CBOR bytes for independent tests. |
| inputs / outputs | Writes both length-prefixed sections, fixed version/reserved header, body checksum and protected-prefix checksum. |
| invariants | Envelope construction intentionally allows malformed CBOR components while keeping framing/checksums self-consistent. |
| ownership | Returns an owning test string; input views must survive through the copies. |
| failure | Ordinary test-string allocation failures propagate. |
| cost | O(frame byte length) copies and hashing; test construction only. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0010

[Lines 50–50](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string bytes(const std::vector<std::uint8_t>& value) {return {reinterpret_cast<const char*>(value.data()),value.size()};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt a CBOR encoder byte vector into a binary std::string for hostile fixture construction. |
| inputs / outputs | Copies the exact byte count with no text decoding or UTF8 normalization. |
| invariants | Must preserve arbitrary binary bytes including embedded NUL. |
| ownership | Returns owned test bytes independent of the input vector after the copy. |
| failure | String allocation failure propagates from setup. |
| cost | One O(n) copy in test code. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0011

[Lines 51–53](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void wire_rejected(Action action) {
  bool failed=false;{s04_alloc::Scope deny(0);try{action();}catch(const recovery::ImageFailure&){failed=true;}assert(s04_alloc::calls==0);}assert(failed);
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that malformed descriptor wire rejects with ImageFailure before covered C++ allocation. |
| inputs / outputs | Runs one action while the test-only \`s04_alloc::Scope\` denies zero C++ new requests, then requires the expected fixed failure and zero seam calls. |
| invariants | This is a narrow C++ new seam for the inspector, not a global malloc/syscall denial or a proof about dependencies outside the seam. |
| ownership | Action borrows captured fixture values for the call; RAII restores the test hook afterward. |
| failure | If no ImageFailure occurs or any covered new call is observed, the test assertion fails. |
| cost | One action invocation plus fixed test-hook accounting. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0012

[Lines 54–56](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void refused(Action action) {
  bool failed=false;try{action();}catch(const std::exception&){failed=true;}assert(failed);
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert only that an adversarial rebind/admit action throws a standard exception. |
| inputs / outputs | Invokes a callable and records whether any \`std::exception\` subtype was thrown. |
| invariants | Does not assert a particular fault class; exact rejection layer must be inferred from the action and surrounding assertions. |
| ownership | The callable owns temporary admission values and unwinds them before return. |
| failure | No exception is a failed expectation; non-std exceptions are not caught. |
| cost | Constant test bookkeeping around the action. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0013

[Lines 57–80](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cbor_and_frame(const char* fixture) {
  const auto valid=envelope(std::string_view("\xa0",1),std::string_view("\xa0",1));
  std::ifstream file(fixture);std::string hex;file>>hex;assert(hex.size()==valid.size()*2);
  constexpr std::string_view digits="0123456789abcdef";
  for(std::size_t i=0;i<valid.size();++i){const auto byte=static_cast<unsigned char>(valid[i]);assert(hex[2*i]==digits[byte>>4] && hex[2*i+1]==digits[byte&15]);}
  ar::InspectedDescriptor inspected{};{s04_alloc::Scope deny(0);inspected=ar::inspect_descriptor(valid);assert(s04_alloc::calls==0);}
  assert(inspected.sha256==sha256_fixed(valid) && inspected.binding_image==std::string_view("\xa0",1));
  for(std::size_t cut=0;cut<valid.size();++cut)wire_rejected([&]{static_cast<void>(ar::inspect_descriptor(std::string_view(valid).substr(0,cut)));});
  for(std::size_t i=0;i<valid.size();++i){auto bad=valid;bad[i]^=1;wire_rejected([&]{static_cast<void>(ar::inspect_descriptor(bad));});}
  const std::array bad{
      std::string("\xbf\xff",2),std::string("\x18\x01",2),std::string("\x59\x01\x00",3),
      std::string("\xc0\x00",2),std::string("\xf9\x3c\x00",3),std::string("\xf7",1),
      std::string("\xa2\x61\x61\x01\x61\x61\x02",7),std::string("\xa2\x61\x62\x01\x61\x61\x02",7),
      std::string("\xa1\x61\xff\x00",4),std::string("\x3b\x80\x00\x00\x00\x00\x00\x00\x00",9),
      std::string("\x9b\xff\xff\xff\xff\xff\xff\xff\xff",9)};
  for(const auto& cbor:bad){const auto hostile=envelope(cbor,std::string_view("\xa0",1));wire_rejected([&]{static_cast<void>(ar::inspect_descriptor(hostile));});}
  std::string deep(130,static_cast<char>(0x81));deep+=static_cast<char>(0xf6);const auto nested=envelope(deep,std::string_view("\xa0",1));
  wire_rejected([&]{static_cast<void>(ar::inspect_descriptor(nested));});
  const auto opaque=envelope(std::string("\x61\xff",2),std::string_view("\xa0",1));static_cast<void>(ar::inspect_descriptor(opaque));
  ar::DescriptorLimits exact;exact.image.bytes=valid.size();exact.image.work=inspected.statistics.work;exact.cbor_items=2;exact.cbor_depth=0;
  static_cast<void>(ar::inspect_descriptor(valid,exact));
  for(unsigned i=0;i<4;++i){auto low=exact;if(i==0)--low.image.bytes;if(i==1)--low.image.work;if(i==2)--low.cbor_items;if(i==3)low.cbor_depth=257;
    wire_rejected([&]{static_cast<void>(ar::inspect_descriptor(valid,low));});}
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test descriptor framing, allocation-free inspection, CBOR restrictions and exact descriptor limits. |
| inputs / outputs | Checks the fixture hex against a minimal two-map frame, successful inspection under zero C++ new calls, every truncation and bit flip, invalid CBOR heads/maps/keys/depth, opaque text values, exact limits and one-below limits. |
| invariants | The test’s own envelope helper creates the frame; \`inspect_descriptor\` must reject structural/checksum/limit failures before DOM creation and preserve opaque text values without a blanket UTF8 rule. |
| ownership | Fixture and constructed strings live through each borrowed inspection result; \`InspectedDescriptor\` views are not retained beyond those bytes. |
| failure | Expected malformed-input outcomes are ImageFailure; assertions check the allocation seam remains at zero. |
| cost | Quadratic-looking repeated mutation loop is bounded by the small golden frame; covers C++ new requests only, not global malloc or native syscalls. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [tests/fixtures/sql_aggregate_descriptor/envelope.hex](../../../../../tests/fixtures/sql_aggregate_descriptor/envelope.hex), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0014

[Lines 81–130](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void genuine_round_trip(bool indexed,bool opaque) {
  const auto original=bind(opaque);auto physical=indexed?s04_runtime::options():PhysicalOptions{};
  // Finite host replay admits original unlimited producer compile policies.
  physical.limits.work_limit.reset();physical.limits.identity.work_limit.reset();
  const auto account=resource::MemoryAccount::create(memory);auto admitted=ar::admit_into(account,original,tree(original),physical,normal());
  const auto receiver=resource::MemoryAccount::create(memory);auto restored=ar::rebind_into(receiver,admitted.descriptor.bytes());
  assert(restored.descriptor.bytes()==admitted.descriptor.bytes());assert(restored.descriptor.program().binding_image()==original.binding_image());
  assert(restored.descriptor.native_binding()==admitted.descriptor.native_binding());assert(restored.descriptor.native_program().account().statistics().owner==receiver.statistics().owner);
  assert(restored.descriptor.options().count_limit==10 && restored.descriptor.options().source.native.multiplicity_limit==30 &&
      restored.descriptor.options().source.source_work_limit==normal().source.source_work_limit && restored.descriptor.options().group_work_limit==200000);
  assert(!restored.descriptor.native_program().options().limits.work_limit && !restored.descriptor.native_program().options().limits.identity.work_limit);
  const std::array<Cell,4> row{number(3),{},number(5),storage::ScalarView{true}};
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,2}};
  const auto a=admitted.runtime.prepare_batch({1,edits}).commit(),b=restored.runtime.prepare_batch({1,edits}).commit();
  assert(a.output.size()==1 && b.output.size()==1 && a.output[0].key==b.output[0].key && a.output[0].after==b.output[0].after);
  const auto frame=ar::encode(receiver,original,1,ar::GroupEpochView{7,1,1,restored.descriptor.sha256(),b.changed,b.group_changed,b.output});
  static_cast<void>(ar::inspect(original,frame.bytes()));
  auto metadata=restored.descriptor;restored=ar::rebind_into(receiver,metadata.bytes());assert(restored.runtime.sequence()==0);
  ar::AdmissionLimits exact;exact.descriptor.image.work=restored.statistics.work;
  {auto pass=ar::rebind_into(receiver,metadata.bytes(),exact);assert(pass.statistics.work==restored.statistics.work);}
  const auto baseline=receiver.statistics().current;--exact.descriptor.image.work;
  refused([&]{auto denied=ar::rebind_into(receiver,metadata.bytes(),exact);});assert(receiver.statistics().current==baseline);
  exact={};exact.lowering.work_limit=0;refused([&]{auto denied=ar::rebind_into(receiver,metadata.bytes(),exact);});
  exact={};exact.binding.work_limit.reset();refused([&]{auto denied=ar::rebind_into(receiver,metadata.bytes(),exact);});
  // Each finite receiving binder grant can refuse valid bytes without corruption.
  for(unsigned phase=0;phase<4;++phase) {
    exact={};
    if(phase==0)exact.binding.work_limit=0;
    else if(phase==1)exact.binding.source.work_limit=0;
    else if(phase==2)exact.binding.source.binding.limits.work_limit=0;
    else exact.binding.kernel.limits.work_limit=0;
    bool work_refused=false;
    try{auto denied=ar::rebind_into(receiver,metadata.bytes(),exact);}
    catch(const recovery::ImageFailure& error){work_refused=error.fault()==recovery::ImageFault::work;}
    assert(work_refused && receiver.statistics().current==baseline);
  }
  auto stored=ar::inspect_descriptor(metadata.bytes());const auto binding=stored.binding_image;
  auto recipe=Json::from_cbor(stored.recipe.begin(),stored.recipe.end());
  for(const auto* key:{"schema_version","records","arithmetic","output","physical_sha256","source_sha256","weighted_shape_sha256","weighted_sha256","multiplicity_limit"}) {
    auto changed=recipe;changed[key]=changed[key].is_string()?Json("forged"):Json(999);
    const auto hostile=envelope(binding,bytes(Json::to_cbor(changed)));const auto before=receiver.statistics().current;
    refused([&]{auto value=ar::rebind_into(receiver,hostile);});assert(receiver.statistics().current==before);
  }
  auto changed_binding=Json::from_cbor(binding.begin(),binding.end());changed_binding["decode"]["encoding"]="forged";
  const auto hostile=envelope(bytes(Json::to_cbor(changed_binding)),stored.recipe);
  refused([&]{auto value=ar::rebind_into(receiver,hostile);});
  auto no_capture=normal();no_capture.capture_changes=false;
  refused([&]{auto value=ar::admit_into(receiver,original,tree(original),physical,no_capture);});
  account.check_invariants();receiver.check_invariants();
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare genuine descriptor admission/rebind for ordered/indexed backends and opaque catalog metadata. |
| inputs / outputs | Builds original compiler program, admits it, rebinds bytes to a second account, compares exact bytes/program/native binding/policies and receiving owner, applies one nullable physical replacement to both C0 runtimes, compares group output, and validates a resulting group epoch. |
| invariants | Normal options and original physical producer limits survive exactly; disabled physical work counters exercise the host-check-plus-original-policy construction path, while default finite producer caps exercise the common one-pass path. Rebind returns C0 and does not replay the test epoch. |
| ownership | Each factory receives its own MemoryAccount; frame views borrow a surviving descriptor copy. Failed tamper/admission temporaries unwind before account-current checks. |
| failure | Exercises rejected edited recipe/binding, one-below codec work, missing lower/binder caps and disabled change capture. Four zero receiving binder grants must throw ImageFailure(work) and preserve the receiving account baseline; remaining generic refused checks do not prescribe each exception subtype. |
| cost | Cold bind/lower/runtime/CBOR work plus one true next-epoch batch for equivalence; not a CPU benchmark or recovery replay test. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0015

[Lines 131–140](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void receiving_caps() {
  const auto original=bind();const auto producer=resource::MemoryAccount::create(memory);
  const auto admitted=ar::admit_into(producer,original,tree(original),{},normal());std::uint64_t peak=0;
  {auto trial=resource::MemoryAccount::create(memory);{auto value=ar::rebind_into(trial,admitted.descriptor.bytes());peak=trial.statistics().peak_requested_bytes;}
    assert(trial.statistics().current.allocations==1);}
  {auto exact=resource::MemoryAccount::create(peak);auto value=ar::rebind_into(exact,admitted.descriptor.bytes());assert(exact.statistics().peak_requested_bytes==peak);}
  {auto low=resource::MemoryAccount::create(peak-1);bool failed=false;
    try{auto value=ar::rebind_into(low,admitted.descriptor.bytes());}catch(const resource::MemoryFailure& error){failed=error.fault()==resource::MemoryFault::limit;}
    assert(failed && low.statistics().current.allocations==1);low.check_invariants();}
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure and enforce the receiving account’s peak requested bytes for a live rebind result. |
| inputs / outputs | Measures peak while the re-bound descriptor/runtime are alive, verifies a same-size account succeeds, and a cap one byte lower yields MemoryFailure::limit. |
| invariants | The measured scope is MemoryAccount requested bytes and allocation count only; it does not equal payload size or global malloc/DOM/compiler workspace. |
| ownership | The local Admitted owner is destroyed before asserting only the controller allocation remains in each account. |
| failure | An insufficient receiving grant fails at the actual account allocator and leaves no retained admission allocation. |
| cost | Three cold rebind trials; exact/one-under grants validate account accounting, not CPU or all process allocations. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0016

[Lines 141–141](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L141); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L141:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_descriptor_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 142–146](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
  assert(argc==2);cbor_and_frame(argv[1]);
  for(const bool indexed:{false,true})for(const bool opaque:{false,true})genuine_round_trip(indexed,opaque);
  receiving_caps();std::cout<<"R2 genuine descriptor/binding/native/options; opaque metadata; finite host/unlimited producer; nullable next epoch; hostile CBOR/checksums/caps passed\n";
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the fixture envelope and all four ordered/indexed × ordinary/opaque descriptor round-trip combinations. |
| inputs / outputs | Requires the CTest-supplied envelope fixture path; then executes frame/CBOR tests, four genuine factory cases, receiving-account caps and invariant checks. |
| invariants | The test’s assertions are the oracle; source presence alone does not prove execution, full backend behavior, durable replay or global allocator coverage. |
| ownership | Test process owns fixture streams, strings, accounts and admitted runtimes for their lexical scopes. |
| failure | Assertion failure or uncaught test exception returns a failing test process. |
| cost | Test-only cold compile/runtime operations and one concrete batch per round trip. |
| Design | [tests/unit/sql_aggregate_descriptor_test.cpp](../../../../../tests/unit/sql_aggregate_descriptor_test.cpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../sql_aggregate_descriptor.md) |
