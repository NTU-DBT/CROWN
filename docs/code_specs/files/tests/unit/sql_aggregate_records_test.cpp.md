# `tests/unit/sql_aggregate_records_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_records_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a1f1d824cf8fa2793f16d9214ac09294af0e9027c69f6b127418ffd8d9a81958`. 198 lines partitioned into 24 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/sql_aggregate_records_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../tests/unit/sql_aggregate_records_test.cpp#L16) | Callable definition: template&lt;class T&gt; concept RvalueView = requires(const T&& value) | calls view · [reviewed contract](#b0002) |
| [B0003 · 17–19](../../../../../tests/unit/sql_aggregate_records_test.cpp#L17) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!RvalueView&lt;ar::DecodedInput&gt; && !std::is_copy_constructible_v&lt;ar::Frame&gt;); · [reviewed contract](#b0003) |
| [B0004 · 20–20](../../../../../tests/unit/sql_aggregate_records_test.cpp#L20) | Callable definition: Cell number(std::int64_t value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0004) |
| [B0005 · 21–21](../../../../../tests/unit/sql_aggregate_records_test.cpp#L21) | Callable definition: Cell text(std::string_view value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../tests/unit/sql_aggregate_records_test.cpp#L22) | Callable definition: ar::Hash hash(char value) | calls fill; returns result · [reviewed contract](#b0006) |
| [B0007 · 23–25](../../../../../tests/unit/sql_aggregate_records_test.cpp#L23) | Callable definition: ar::Binding binding() | calls fill, hash; returns result · [reviewed contract](#b0007) |
| [B0008 · 26–33](../../../../../tests/unit/sql_aggregate_records_test.cpp#L26) | Callable definition: frontend::SqlAggregateProgram bind_program(std::string_view sql="SELECT g,COUNT(*) FROM r GROUP BY g") | calls frontend::bind_sql_aggregate, assert, std::move; guard assert(std::holds_alternative&lt;frontend::SqlAggregateProgram&gt;(result));; returns std::get&lt;frontend::SqlAggregateProgram&gt;(std::move(result)) · [reviewed contract](#b0008) |
| [B0009 · 34–36](../../../../../tests/unit/sql_aggregate_records_test.cpp#L34) | Callable definition: runtime::aggregate::Tuple tuple(const resource::MemoryAccount& account,std::initializer_list&lt;Cell&gt; values) | calls runtime::aggregate::Tuple::copy_of; returns runtime::aggregate::Tuple::copy_of(account,values); growth copy_of · [reviewed contract](#b0009) |
| [B0010 · 37–37](../../../../../tests/unit/sql_aggregate_records_test.cpp#L37) | Explanatory comments or spacing. | source comment (unverified): // All malformed transport paths must reject without covered C++ allocations. · [reviewed contract](#b0010) |
| [B0011 · 38–43](../../../../../tests/unit/sql_aggregate_records_test.cpp#L38) | Callable definition: template&lt;class Action&gt; void rejected(Action action) | calls deny, action, assert; guard assert(s04_alloc::calls==0);; source comment (unverified): // All malformed transport paths must reject without covered C++ allocations. · [reviewed contract](#b0011) |
| [B0012 · 44–46](../../../../../tests/unit/sql_aggregate_records_test.cpp#L44) | Callable definition: template&lt;class Action&gt; void limited(Action action) | calls action, assert; guard bool failed=false;try { action(); } catch(const recovery::ImageFailure&) { failed=true; }assert(fai… · [reviewed contract](#b0012) |
| [B0013 · 47–47](../../../../../tests/unit/sql_aggregate_records_test.cpp#L47) | Explanatory comments or spacing. | source comment (unverified): // Independent Python fixtures compare full bytes, not implementation round trips. · [reviewed contract](#b0013) |
| [B0014 · 48–55](../../../../../tests/unit/sql_aggregate_records_test.cpp#L48) | Callable definition: void golden(std::string_view directory,std::string_view name,const ar::Frame& frame) | calls file, std::string, assert, size; guard assert(encoded.size()==frame.bytes().size()*2);constexpr std::string_view hex="0123456789abcdef";; 1 loop sites; source comment (unverified): // Independent Python fixtures compare full bytes, not implementation round trips. · [reviewed contract](#b0014) |
| [B0015 · 56–56](../../../../../tests/unit/sql_aggregate_records_test.cpp#L56) | Explanatory comments or spacing. | source comment (unverified): // Recompute both checksums so negative cases exercise structure/type validation. · [reviewed contract](#b0015) |
| [B0016 · 57–62](../../../../../tests/unit/sql_aggregate_records_test.cpp#L57) | Callable definition: void reseal(std::string& bytes) | calls sha256_fixed, std::string_view, substr, std::copy; source comment (unverified): // Recompute both checksums so negative cases exercise structure/type validation. · [reviewed contract](#b0016) |
| [B0017 · 63–76](../../../../../tests/unit/sql_aggregate_records_test.cpp#L63) | Callable definition: void frame_checks(const frontend::SqlAggregateProgram& schema,const ar::Frame& frame) | calls bytes, deny, ar::inspect, assert; guard {s04_alloc::Scope deny(0);info=ar::inspect(schema,bytes);assert(s04_alloc::calls==0);}; 2 loop sites · [reviewed contract](#b0017) |
| [B0018 · 77–77](../../../../../tests/unit/sql_aggregate_records_test.cpp#L77) | Explanatory comments or spacing. | source comment (unverified): // Count real allocation sites, fail each one, and require exact account release. · [reviewed contract](#b0018) |
| [B0019 · 78–88](../../../../../tests/unit/sql_aggregate_records_test.cpp#L78) | Callable definition: template&lt;class Factory&gt; void allocation_cuts(const resource::MemoryAccount& account,Factory factory) | calls statistics, factory, assert, fault; guard assert(account.statistics().current==before.current);; 1 loop sites; source comment (unverified): // Count real allocation sites, fail each one, and require exact account release. · [reviewed contract](#b0019) |
| [B0020 · 89–90](../../../../../tests/unit/sql_aggregate_records_test.cpp#L89) | Explanatory comments or spacing. | source comment (unverified): // Independent receiving grants must pass at their measured peak and fail one · [reviewed contract](#b0020) |
| [B0021 · 91–98](../../../../../tests/unit/sql_aggregate_records_test.cpp#L91) | Callable definition: template&lt;class Factory&gt; void receiving_caps(Factory factory) | calls resource::MemoryAccount::create, factory, statistics, assert; guard auto exact=resource::MemoryAccount::create(peak);{auto owned=factory(exact);assert(exact.statistics…; source comment (unverified): // Independent receiving grants must pass at their measured peak and fail one · [reviewed contract](#b0021) |
| [B0022 · 99–129](../../../../../tests/unit/sql_aggregate_records_test.cpp#L99) | Callable definition: void cursor_checks(const frontend::SqlAggregateProgram& schema,const resource::MemoryAccount& account, const ar::Frame& header,co… | calls deny, feed, bytes, assert; guard s04_alloc::Scope deny(0);static_cast&lt;void&gt;(cursor.feed(schema,frame-&gt;bytes()));assert(s04_alloc::ca…; 3 loop sites; source comment (unverified): // C=UINT64_MAX and I=UINT64_MAX are terminal; no overflowing successor. · [reviewed contract](#b0022) |
| [B0023 · 130–131](../../../../../tests/unit/sql_aggregate_records_test.cpp#L130) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0023) |
| [B0024 · 132–198](../../../../../tests/unit/sql_aggregate_records_test.cpp#L132) | Callable definition: int main(int argc,char** argv) | calls assert, bind_program, resource::MemoryAccount::create, ar::encode; guard assert(argc==2);const auto schema=bind_program();const auto account=resource::MemoryAccount::create…; returns id; ar::encode_input(account,schema,1,moved.view()); 2 loop sites; source comment (unverified): // One owned buffer survives external byte/text destruction and facade moves. · [reviewed contract](#b0024) |

## B0001

[Lines 1–15](../../../../../tests/unit/sql_aggregate_records_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:6280bc5727b32e14bf5bc56888a2be5f20e5fbe924c1cf0bf7de53fa25d351d8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_records_test.cpp: include "crown/recovery/sql_aggregate_records.hpp", "crown/ir/digest.hpp", "crown/planner/oracle.hpp", "index_allocation.hpp", &lt;algorithm&gt;, &lt;cassert&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;string&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–16](../../../../../tests/unit/sql_aggregate_records_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> concept RvalueView = requires(const T&& value) { std::move(value).view(); };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect at compile time whether a type exposes a view callable on an rvalue. |
| inputs / outputs | Declaration: \`template&lt;class T&gt; concept RvalueView = requires(const T&& value)\`. Inputs/outputs: Detect at compile time whether a type exposes a view callable on an rvalue. |
| invariants | \`DecodedInput\` and \`Frame\` intentionally do not expose rvalue \`.view()\`/frame copy; this is a compile-time property, not an executed runtime case. |
| ownership | Concept inspects an expression at compile time and owns nothing. |
| failure | Compile-time concept evaluation has no runtime failure path. |
| cost | Compile-time only; no runtime work. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0003

[Lines 17–19](../../../../../tests/unit/sql_aggregate_records_test.cpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L19:sha256:91a43651bf56594abecac6b46d7adaf313f737367b312f2f59447abf9401b3d9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_records_test.cpp: require 3 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 20–20](../../../../../tests/unit/sql_aggregate_records_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell number(std::int64_t value) { return storage::ScalarView{value}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one signed integer cell for test rows. |
| inputs / outputs | Declaration: \`Cell number(std::int64_t value)\`. Inputs/outputs: Construct one signed integer cell for test rows. |
| invariants | Returns an owning Cell value containing signed int64. |
| ownership | Returns Cell by value. |
| failure | No explicit failure translation; Cell construction is by value. |
| cost | Constructs one scalar Cell. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0005

[Lines 21–21](../../../../../tests/unit/sql_aggregate_records_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell text(std::string_view value) { return storage::ScalarView{value}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one borrowed TEXT cell from caller bytes. |
| inputs / outputs | Declaration: \`Cell text(std::string_view value)\`. Inputs/outputs: Construct one borrowed TEXT cell from caller bytes. |
| invariants | Cell stores a borrowed string_view; caller must keep source bytes valid for every encode that reads it. |
| ownership | Returned Cell contains a borrowed view of the argument. |
| failure | No explicit failure translation; Cell construction is by value. |
| cost | Constructs one scalar Cell; does not copy text bytes. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0006

[Lines 22–22](../../../../../tests/unit/sql_aggregate_records_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ar::Hash hash(char value) { ar::Hash result{};result.fill(value);return result; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one fixed-width test hash by repeating a chosen byte. |
| inputs / outputs | Declaration: \`ar::Hash hash(char value)\`. Inputs/outputs: Construct one fixed-width test hash by repeating a chosen byte. |
| invariants | Returns a fixed-size owned lowercase-hex candidate only when caller's fill character is valid for later encoding. |
| ownership | Returns fixed hash array by value. |
| failure | No explicit failure path. |
| cost | Fills 64 fixed bytes. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0007

[Lines 23–25](../../../../../tests/unit/sql_aggregate_records_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ar::Binding binding() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a syntactically valid fixed-width test Binding. |
| inputs / outputs | Declaration: \`ar::Binding binding()\`. Inputs/outputs: Construct a syntactically valid fixed-width test Binding. |
| invariants | Arrays are fixed-size owned values; chosen hex bytes satisfy the codec's binding syntax checks. |
| ownership | Returns fixed Binding arrays by value. |
| failure | No explicit failure path. |
| cost | Fills 96 fixed bytes. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0008

[Lines 26–33](../../../../../tests/unit/sql_aggregate_records_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::SqlAggregateProgram bind_program(std::string_view sql="SELECT g,COUNT(*) FROM r GROUP BY g") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a genuine SQL aggregate program for one source schema and caller-selected query. |
| inputs / outputs | Declaration: \`frontend::SqlAggregateProgram bind_program(std::string_view sql="SELECT g,COUNT(*) FROM r GROUP BY g")\`. Inputs/outputs: Bind a genuine SQL aggregate program for one source schema and caller-selected query. |
| invariants | Uses the genuine binder and immutable SqlAggregateProgram, with one nullable string key and typed source columns; it is not a caller DTO. |
| ownership | Returns immutable program value by value; catalog/query data are owned by that program handle. |
| failure | Binding failure is asserted as test setup; API/compiler exceptions otherwise propagate. |
| cost | Builds/binds one small fixture program. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0009

[Lines 34–36](../../../../../tests/unit/sql_aggregate_records_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::aggregate::Tuple tuple(const resource::MemoryAccount& account,std::initializer_list<Cell> values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy test cells into an account-owned aggregate tuple. |
| inputs / outputs | Declaration: \`runtime::aggregate::Tuple tuple(const resource::MemoryAccount& account,std::initializer_list&lt;Cell&gt; values)\`. Inputs/outputs: Copy test cells into an account-owned aggregate tuple. |
| invariants | Tuple copy uses the receiving MemoryAccount; any string views within cells remain borrowed from their caller storage. |
| ownership | Returned Tuple owns account-backed cells; string_view scalar payloads remain borrowed. |
| failure | Accounted tuple allocation can raise account/allocation failure. |
| cost | Copies a fixed initializer list into one Tuple under the account. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0010

[Lines 37–37](../../../../../tests/unit/sql_aggregate_records_test.cpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L37:sha256:ec7990f2720be9711064d9c6dc2ef6b72d62cf68a8e4922b5450faf5c57906d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: All malformed transport paths must reject without covered C++ allocations. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 38–43](../../../../../tests/unit/sql_aggregate_records_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void rejected(Action action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an ImageFailure while the test replacement-new probe rejects covered C++ allocation calls. |
| inputs / outputs | Declaration: \`template&lt;class Action&gt; void rejected(Action action)\`. Inputs/outputs: Require an ImageFailure while the test replacement-new probe rejects covered C++ allocation calls. |
| invariants | The probe directly defines ordinary, array, aligned, and nothrow global-new replacements; the assertion checks zero calls through those replacements, not direct malloc/account/systemcall activity. |
| ownership | Invokes a borrowed/forwarded action during the call; retains no action or fixture. |
| failure | If no ImageFailure occurs, the assertion fails; any covered replacement-new call makes its injected bad_alloc escape. The helper consumes only ImageFailure. |
| cost | Runs one supplied action under the replacement-new deny probe. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0012

[Lines 44–46](../../../../../tests/unit/sql_aggregate_records_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void limited(Action action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an ImageFailure without asserting an allocation-probe state. |
| inputs / outputs | Declaration: \`template&lt;class Action&gt; void limited(Action action)\`. Inputs/outputs: Require an ImageFailure without asserting an allocation-probe state. |
| invariants | Only an ImageFailure is required; this helper makes no assertion that a C++ new probe ran or that no other allocation channel was touched. |
| ownership | Invokes a borrowed/forwarded action during the call; retains no action or fixture. |
| failure | Throws std::runtime_error when action does not raise ImageFailure; other exceptions propagate. |
| cost | Runs one supplied action and catches only ImageFailure. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0013

[Lines 47–47](../../../../../tests/unit/sql_aggregate_records_test.cpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L47:sha256:0d54787810fce4b03ee28459778b3bde9069c1c9c0395f63c0fe9de2fba2933d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Independent Python fixtures compare full bytes, not implementation round trips. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 48–55](../../../../../tests/unit/sql_aggregate_records_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void golden(std::string_view directory,std::string_view name,const ar::Frame& frame) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every byte of one C++ frame with its separately generated Python hex golden. |
| inputs / outputs | Declaration: \`void golden(std::string_view directory,std::string_view name,const ar::Frame& frame)\`. Inputs/outputs: Compare every byte of one C++ frame with its separately generated Python hex golden. |
| invariants | The golden contains full encoded bytes from the independent Python fixture; comparison checks exact length and each lowercase hex nibble. |
| ownership | Frame and golden text are borrowed for comparison; no bytes are retained. |
| failure | Missing/mismatched fixture file or byte differs causes assertion/process failure; stream failures are not translated into recovery errors. |
| cost | Reads one fixture file and compares every frame byte as two hex characters. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0015

[Lines 56–56](../../../../../tests/unit/sql_aggregate_records_test.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L56:sha256:273d1abdd7a75e18a8eaa7962931971a29588d869eb9b0ca82773f676924eb1e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Recompute both checksums so negative cases exercise structure/type validation. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 57–62](../../../../../tests/unit/sql_aggregate_records_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reseal(std::string& bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute body and prefix checksums after a test mutates an encoded byte. |
| inputs / outputs | Declaration: \`void reseal(std::string& bytes)\`. Inputs/outputs: Recompute body and prefix checksums after a test mutates an encoded byte. |
| invariants | Checksums are recomputed over mutated raw bytes only so malformed parser cases can pass integrity checks; this is test setup, not production repair. |
| ownership | Mutates caller-owned string in place; creates only local checksum arrays. |
| failure | Digest operation may report underlying allocation errors; mutates supplied buffer only. |
| cost | Hashes one frame body and fixed prefix. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0017

[Lines 63–76](../../../../../tests/unit/sql_aggregate_records_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void frame_checks(const frontend::SqlAggregateProgram& schema,const ar::Frame& frame) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one frame's allocation-free inspection, all strict truncations and single-byte flips, exact/one-under byte/work caps, and trailing-byte rejection. |
| inputs / outputs | Declaration: \`void frame_checks(const frontend::SqlAggregateProgram& schema,const ar::Frame& frame)\`. Inputs/outputs: Check one frame's allocation-free inspection, all strict truncations and single-byte flips, exact/one-under byte/work caps, and trailing-byte rejection. |
| invariants | For each supplied frame all shorter prefixes and all one-byte XOR mutations must reject; exact bytes/work limits pass and one-under/trailing bytes fail. |
| ownership | Schema and Frame are borrowed for the call; local malformed strings are owned by each loop iteration. |
| failure | A failed expected-rejection or boundary assertion aborts the test; helper catches only ImageFailure via rejected(). |
| cost | For one frame, checks every shorter prefix and every byte position once, plus exact-boundary cases; finite test work, not production complexity. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0018

[Lines 77–77](../../../../../tests/unit/sql_aggregate_records_test.cpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L77:sha256:96c9790b32ed74b0914396f5e0d08c4887a403ee6286c7d3aeb0c4b0239ac5bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Count real allocation sites, fail each one, and require exact account release. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 78–88](../../../../../tests/unit/sql_aggregate_records_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Factory> void allocation_cuts(const resource::MemoryAccount& account,Factory factory) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep replacement-new fail-after indices for a factory and require caught bad_alloc plus restoration of account current usage. |
| inputs / outputs | Declaration: \`template&lt;class Factory&gt; void allocation_cuts(const resource::MemoryAccount& account,Factory factory)\`. Inputs/outputs: Sweep replacement-new fail-after indices for a factory and require caught bad_alloc plus restoration of account current usage. |
| invariants | Probe call count is successful factory replacement-new calls; each configured fail-after index must yield bad_alloc and restore account current usage, but \`triggered\` is not asserted. |
| ownership | Account reference and Factory object are borrowed; owned factory result is destroyed within each measured/failing scope. |
| failure | The assertion catches std::bad_alloc but does not verify \`s04_alloc::triggered\`; it does not attribute failure to one exact replacement site or inject malloc/account/systemcall failures directly. |
| cost | One success calibration and one factory construction per observed replacement-new fail index; includes account balance checks, not bytes/CPU time. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0020

[Lines 89–90](../../../../../tests/unit/sql_aggregate_records_test.cpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L90:sha256:06744c7e15aa5cc71bafc49f97864847a7312ff9365312560feb79a4fe369322
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Independent receiving grants must pass at their measured peak and fail one byte below it; failures return to the receiving controller's sole allocation. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 91–98](../../../../../tests/unit/sql_aggregate_records_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Factory> void receiving_caps(Factory factory) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one factory's receiving-account peak, require exact-peak success and one-byte-under limit failure, then check the controller-only residual allocation. |
| inputs / outputs | Declaration: \`template&lt;class Factory&gt; void receiving_caps(Factory factory)\`. Inputs/outputs: Measure one factory's receiving-account peak, require exact-peak success and one-byte-under limit failure, then check the controller-only residual allocation. |
| invariants | The 64 MiB trial measures account peak request; exact peak succeeds, peak-1 yields MemoryFault::limit and leaves only the account controller allocation. |
| ownership | Factory and each MemoryAccount are local/borrowed as shown; each result is destroyed before account invariant checks. |
| failure | Requires MemoryFault::limit one byte below measured peak; other errors escape or make the assertion fail. |
| cost | Three account creations per factory path (trial/exact/one-under); each measures account peak request, not elapsed time. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0022

[Lines 99–129](../../../../../tests/unit/sql_aggregate_records_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cursor_checks(const frontend::SqlAggregateProgram& schema,const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise WAL record order, pending identity, W/I/C frontiers, duplicate-feed atomicity, cumulative caps, allocation-free cursor feed, and UINT64_MAX successor rejection. |
| inputs / outputs | Declaration: \`void cursor_checks(const frontend::SqlAggregateProgram& schema,const resource::MemoryAccount& account, const ar::Frame& header,const ar::Frame& input,const ar::Frame& commit,const…\`. Inputs/outputs: Exercise WAL record order, pending identity, W/I/C frontiers, duplicate-feed atomicity, cumulative caps, allocation-free cursor feed, and UINT64_MAX successor rejection. |
| invariants | Cursor transitions use complete in-memory frames only; global-new denial observes replacement calls, while byte/work/record caps and UINT64_MAX behavior are separately asserted. |
| ownership | Schema, account, and Frames are borrowed; cursor owns only fixed validation state. |
| failure | Expected transport rejects are caught through rejected(); cumulative-cap loop catches ImageFailure, while setup/API/account exceptions otherwise propagate. |
| cost | Six cursor records per cap case plus finite transitions/boundary checks; no persistent file scan benchmark. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |

## B0023

[Lines 130–131](../../../../../tests/unit/sql_aggregate_records_test.cpp#L130); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L130-L131:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_records_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 132–198](../../../../../tests/unit/sql_aggregate_records_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build seven record examples and exercise transport goldens, input ownership/use, distinct hidden keys with equal projected COUNT values, malformed inputs, budgets, allocation/account caps, and WAL transitions. |
| inputs / outputs | Declaration: \`int main(int argc,char** argv)\`. Inputs/outputs: Build seven record examples and exercise transport goldens, input ownership/use, distinct hidden keys with equal projected COUNT values, malformed inputs, budgets, allocation/account caps, and WAL transitions. |
| invariants | Seven goldens plus finite malformed/budget/fault fixtures; the hidden-key query keeps NULL and 'z' groups distinct though each projects COUNT=1, reversed input encodes identically, unchanged/empty-engaged sides reject, and deletion encodes. One decoded input is applied once to a genuine runtime, but no WAL file, descriptor admission, durable sync, or semantic recovery replay is run. |
| ownership | All fixture objects and runtime owners are local to main; externally borrowed test strings are deliberately overwritten while decoded frame ownership remains live. |
| failure | Assertions report test failures; test does not run durable file/session admission or semantic recovery replay. |
| cost | Seven fixed goldens, finite loops over each frame's truncations/bytes, three account/factory cap sets and one runtime application; no durable replay benchmark. |
| Design | [tests/unit/sql_aggregate_records_test.cpp](../../../../../tests/unit/sql_aggregate_records_test.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp](../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tools/generate_sql_aggregate_record_fixtures.py](../../../../../tools/generate_sql_aggregate_record_fixtures.py), [tests/fixtures/sql_aggregate_records/wal-header.hex](../../../../../tests/fixtures/sql_aggregate_records/wal-header.hex), [tests/fixtures/sql_aggregate_records/input.hex](../../../../../tests/fixtures/sql_aggregate_records/input.hex), [tests/fixtures/sql_aggregate_records/commit.hex](../../../../../tests/fixtures/sql_aggregate_records/commit.hex), [tests/fixtures/sql_aggregate_records/reject.hex](../../../../../tests/fixtures/sql_aggregate_records/reject.hex), [tests/fixtures/sql_aggregate_records/sink-header.hex](../../../../../tests/fixtures/sql_aggregate_records/sink-header.hex), [tests/fixtures/sql_aggregate_records/group-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/group-epoch.hex), [tests/fixtures/sql_aggregate_records/empty-epoch.hex](../../../../../tests/fixtures/sql_aggregate_records/empty-epoch.hex), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../../sql_aggregate_records.md) |
