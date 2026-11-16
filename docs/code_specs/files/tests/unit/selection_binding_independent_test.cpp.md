# `tests/unit/selection_binding_independent_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_binding_independent_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `174c6d040c21921039d5f80b849243b06e7b70563cc20866a6517b9232dd9c8c`. 281 lines partitioned into 24 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/selection_binding_independent_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // An independent byte-vector writer, not the production string visitor. Word · [reviewed contract](#b0001) |
| [B0002 · 16–34](../../../../../tests/unit/selection_binding_independent_test.cpp#L16) | Type/record definition: struct Bytes | growth insert, push_back; 2 loop sites; source comment (unverified): // An independent byte-vector writer, not the production string visitor. Word · [reviewed contract](#b0002) |
| [B0003 · 35–40](../../../../../tests/unit/selection_binding_independent_test.cpp#L35) | Callable definition: bool equals(const std::string& actual,const Bytes& expected) | calls size; returns false; false; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 41–45](../../../../../tests/unit/selection_binding_independent_test.cpp#L41) | Callable definition: std::string string_of(const Bytes& value) | calls reserve, size, push_back; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 46–46](../../../../../tests/unit/selection_binding_independent_test.cpp#L46) | Callable definition: std::string scalar(const Value& value) | calls b, wire::scalar_binding_record; returns wire::scalar_binding_record(value,b) · [reviewed contract](#b0005) |
| [B0006 · 47–47](../../../../../tests/unit/selection_binding_independent_test.cpp#L47) | Callable definition: std::string tree(const FreeConnexTree& value) | calls b, wire::tree_binding_record; returns wire::tree_binding_record(value,b) · [reviewed contract](#b0006) |
| [B0007 · 48–48](../../../../../tests/unit/selection_binding_independent_test.cpp#L48) | Callable definition: std::string core(const Catalog& catalog,const Query& query) | calls b, wire::core_binding_record; returns wire::core_binding_record(catalog,query,b) · [reviewed contract](#b0007) |
| [B0008 · 49–49](../../../../../tests/unit/selection_binding_independent_test.cpp#L49) | Callable definition: std::string program(const frontend::NormalizedSql& value) | calls b, wire::program_binding_record; returns wire::program_binding_record(value,b) · [reviewed contract](#b0008) |
| [B0009 · 50–50](../../../../../tests/unit/selection_binding_independent_test.cpp#L50) | Explanatory comments or spacing. |  |
| [B0010 · 51–77](../../../../../tests/unit/selection_binding_independent_test.cpp#L51) | Callable definition: void scalar_literals() | calls expected, r, u, i; guard check(equals(scalar(Value{value}),integer(value)),"signed scalar differs from independent modulo-2^…; returns expected; 5 loop sites · [reviewed contract](#b0010) |
| [B0011 · 78–78](../../../../../tests/unit/selection_binding_independent_test.cpp#L78) | Explanatory comments or spacing. |  |
| [B0012 · 79–86](../../../../../tests/unit/selection_binding_independent_test.cpp#L79) | Callable definition: FreeConnexTree raw_fixture() | calls ; returns value · [reviewed contract](#b0012) |
| [B0013 · 87–110](../../../../../tests/unit/selection_binding_independent_test.cpp#L87) | Callable definition: void tree_literals_and_mutations() | calls raw_fixture, expected, r, p; guard check(equals(baseline,expected),"literal raw-tree bytes differ from independent framed vector");; growth insert, push_back; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 111–111](../../../../../tests/unit/selection_binding_independent_test.cpp#L111) | Explanatory comments or spacing. |  |
| [B0015 · 112–121](../../../../../tests/unit/selection_binding_independent_test.cpp#L112) | Callable definition: std::pair&lt;Catalog,Query&gt; core_fixture() | calls Decimal::parse; returns {catalog,query} · [reviewed contract](#b0015) |
| [B0016 · 122–137](../../../../../tests/unit/selection_binding_independent_test.cpp#L122) | Callable definition: Bytes literal_core_inner() | calls b, r, u, a; returns b; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 138–174](../../../../../tests/unit/selection_binding_independent_test.cpp#L138) | Callable definition: void core_literals_and_mutations() | calls core_fixture, expected, r, text; guard check(equals(baseline,expected),"nested literal core bytes differ from independent P07-v2 framing");; growth emplace, push_back; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 175–175](../../../../../tests/unit/selection_binding_independent_test.cpp#L175) | Explanatory comments or spacing. |  |
| [B0019 · 176–197](../../../../../tests/unit/selection_binding_independent_test.cpp#L176) | Callable definition: frontend::NormalizedSql program_fixture() | calls core_fixture, Decimal::parse; returns x · [reviewed contract](#b0019) |
| [B0020 · 198–252](../../../../../tests/unit/selection_binding_independent_test.cpp#L198) | Callable definition: void normalized_field_mutations() | calls program_fixture, program, void, push_back; guard for(const auto& change:mutations){auto copy=original;change(copy);check(program(copy)!=baseline,"no…; growth push_back; 1 loop sites; source comment (unverified): // This is a deliberately rich byte-record fixture, not an admitted SQL · [reviewed contract](#b0020) |
| [B0021 · 253–253](../../../../../tests/unit/selection_binding_independent_test.cpp#L253) | Explanatory comments or spacing. |  |
| [B0022 · 254–273](../../../../../tests/unit/selection_binding_independent_test.cpp#L254) | Callable definition: void exact_byte_budget() | calls full, wire::scalar_binding_record, check, size; guard check(full.usage.work==expected.size() && full.usage.binding_key_bytes==expected.size() && full.usa…; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 274–275](../../../../../tests/unit/selection_binding_independent_test.cpp#L274) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0023) |
| [B0024 · 276–281](../../../../../tests/unit/selection_binding_independent_test.cpp#L276) | Callable definition: int main() | calls scalar_literals, tree_literals_and_mutations, core_literals_and_mutations, normalized_field_mutations; returns 1 · [reviewed contract](#b0024) |

## B0001

[Lines 1–15](../../../../../tests/unit/selection_binding_independent_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:890deef01bdceaae3963852010e14b442cc5d937d3eecd5bb83bb9a5422406f8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_binding_independent_test.cpp: include "selection_independent_fixture.hpp", "selection_detail.hpp", &lt;functional&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;string_view&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–34](../../../../../tests/unit/selection_binding_independent_test.cpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Bytes {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the independent expected byte stream used by selection-record tests. |
| inputs / outputs | Bytes owns an unsigned-byte vector; construction appends a literal domain prefix, and methods append raw bytes, tags, 64-bit words, typed values, text and record names. |
| invariants | word emits exactly eight most-significant-first base-256 bytes; text stores tag S, length, then raw bytes; signed i casts to uint64 modulo 2^64. |
| ownership | Vector storage is owned by Bytes; input string_views are borrowed only during each append. |
| failure | Vector growth may throw; no encoding budget or validation is attached to the expected writer. |
| cost | Each emitted byte pushes or inserts into the vector; word uses a local eight-byte array and insertion can grow the vector. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0003

[Lines 35–40](../../../../../tests/unit/selection_binding_independent_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool equals(const std::string& actual,const Bytes& expected){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a production record byte-for-byte with the independent expected writer. |
| inputs / outputs | Inputs are an actual std::string and borrowed Bytes; returns false on length mismatch or first differing unsigned byte. |
| invariants | Comparison is length-sensitive and binary-safe, including NUL and high bytes. |
| ownership | Both inputs are borrowed for the call; no copy is retained. |
| failure | No explicit failure exception path; comparison itself is Boolean. |
| cost | Length check plus at most one byte traversal through the common length. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0004

[Lines 41–45](../../../../../tests/unit/selection_binding_independent_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string string_of(const Bytes& value){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert expected unsigned record bytes to a length-preserving std::string for nesting. |
| inputs / outputs | Input is borrowed Bytes; returns a string with one char appended for each expected byte. |
| invariants | Requests capacity for the input byte count and preserves embedded NUL/high-byte positions; this is test framing support, not a production encoder. |
| ownership | Returned string owns its bytes; Bytes remains caller-owned. |
| failure | String allocation may throw. |
| cost | One reserve request and one append per byte; growth follows the standard string allocator. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0005

[Lines 46–46](../../../../../tests/unit/selection_binding_independent_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string scalar(const Value& value){wire::Budget b(rank::Limits{});return wire::scalar_binding_record(value,b);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce the production scalar binding record for a Value. |
| inputs / outputs | Input is a borrowed Value; creates a fresh detail::Budget with default ranking Limits and returns scalar_binding_record bytes. |
| invariants | The diagnostic prefix and payload follow CROWN-SELECTION-SCALAR;1; framing; no proof, selection or cache is created. |
| ownership | Value is borrowed during encoding; returned std::string owns the bytes. |
| failure | Encoder budget, decimal formatting and string allocation failures propagate. |
| cost | Encodes one variant and its payload under a fresh logical budget; output can allocate. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0006

[Lines 47–47](../../../../../tests/unit/selection_binding_independent_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string tree(const FreeConnexTree& value){wire::Budget b(rank::Limits{});return wire::tree_binding_record(value,b);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce the production tree binding record for a supplied tree value. |
| inputs / outputs | Input is a borrowed FreeConnexTree; returns tree_binding_record bytes under a fresh default ranking budget. |
| invariants | The record includes raw tree fields and optional claims as supplied; this function does not validate or certify the tree. |
| ownership | Tree is borrowed; returned string owns encoded bytes. |
| failure | Encoder and allocation failures propagate. |
| cost | Traverses nodes, scopes, children and claims, charging the encoder budget and materializing output bytes. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0007

[Lines 48–48](../../../../../tests/unit/selection_binding_independent_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string core(const Catalog& catalog,const Query& query){wire::Budget b(rank::Limits{});return wire::core_binding_record(catalog,query,b);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce the production core catalog/query binding record. |
| inputs / outputs | Inputs are borrowed Catalog and Query; returns core_binding_record bytes under a fresh default ranking budget. |
| invariants | This diagnostic path frames the supplied core values and nested candidate-binding-v2 bytes; it does not run query validation or admit a candidate. |
| ownership | Catalog and Query are borrowed for synchronous encoding; output string owns bytes. |
| failure | Nested binding encoding, budget exhaustion or allocation failure propagates. |
| cost | Walks complete catalog/query data and constructs a nested v2 record plus outer framing. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0008

[Lines 49–49](../../../../../tests/unit/selection_binding_independent_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string program(const frontend::NormalizedSql& value){wire::Budget b(rank::Limits{});return wire::program_binding_record(value,b);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce the production normalized-program binding record. |
| inputs / outputs | Input is a borrowed NormalizedSql value; returns program_binding_record bytes under a fresh default ranking budget. |
| invariants | All fields selected by the private program record are encoded as provided; the helper does not normalize, validate or admit this object. |
| ownership | NormalizedSql is borrowed; returned string owns its bytes. |
| failure | Nested record encoding, budget exhaustion and allocation failures propagate. |
| cost | Traverses the normalized binding, parameters, constants, core, adapters, routes and outputs and builds complete framed bytes. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0010

[Lines 51–77](../../../../../tests/unit/selection_binding_independent_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar_literals(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare scalar records with literal independent frames for the supported Value alternatives. |
| inputs / outputs | Exercises int64 boundaries, empty/NUL/binary strings, both Booleans, two Dates and four canonical Decimal spellings; each expected result is built with Bytes. |
| invariants | Checks variant tags, exact bytes, Date distinct from equal integer days, Decimal canonicalization and Decimal distinct from same-text string. These finite literals are not a general proof of every value. |
| ownership | Values and expected byte streams are local; production encoder returns owning strings. |
| failure | Any byte/type/canonical-form mismatch throws through test check; parsing or encoding errors propagate. |
| cost | The successful source path makes 28 production scalar-record encodes across the five Value alternatives: 5 integer, 3 string, 2 Boolean, 6 Date/integer comparison and 12 Decimal/canonical/string comparison calls. This finite schedule is not a proof of every value. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0012

[Lines 79–86](../../../../../tests/unit/selection_binding_independent_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree raw_fixture(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the raw tree value used by the literal tree-record test. |
| inputs / outputs | No inputs; returns a FreeConnexTree with embedded NUL/high-byte IDs, duplicate child IDs, claims and native/generalized nodes. |
| invariants | The structure is intentionally supplied raw to the diagnostic encoder; no P02 or planner admission is asserted. |
| ownership | Returned tree owns node strings, sets and vectors. |
| failure | Value allocation may throw; malformed claims are intentionally not rejected by this fixture builder. |
| cost | Constructs a small tree DTO with several owned containers and strings. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0013

[Lines 87–110](../../../../../tests/unit/selection_binding_independent_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void tree_literals_and_mutations(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify the tree record’s literal bytes and sensitivity to selected tree-field mutations. |
| inputs / outputs | No inputs; encodes raw_fixture(), compares with an independent Bytes literal, then applies 17 individual copies/mutations and checks each record differs; also checks the empty-tree frame. |
| invariants | The tested mutations cover root, node ID/kind/scope/children/occurrence/separator claims, tree claims, node order and count; it establishes only these cases. |
| ownership | Baseline tree, mutated copies, expected Bytes and encoded strings are local owners. |
| failure | A collapsed record, mismatch or allocation/encoding exception fails the group. |
| cost | Performs a baseline plus repeated full tree encodes and comparisons; mutation copies and output strings grow with the tiny fixture. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0015

[Lines 112–121](../../../../../tests/unit/selection_binding_independent_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::pair<Catalog,Query> core_fixture(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the rich raw Catalog/Query DTO for the independent core-record test. |
| inputs / outputs | No inputs; returns a pair containing catalog version, typed columns, constraints, statistics, key hint and query terms/outputs with binary bytes and optional-like variants. |
| invariants | The builder does not call validate; the consumer checks raw record framing/mutation sensitivity rather than admission or query semantics. |
| ownership | Returned pair owns catalog/query strings and containers. |
| failure | DTO construction/allocation failures propagate. |
| cost | Builds the literal fixture and value-owned vectors/maps; no production ranking or proof call occurs here. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0016

[Lines 122–137](../../../../../tests/unit/selection_binding_independent_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Bytes literal_core_inner(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write the nested expected candidate-binding-v2 bytes used inside the literal core record. |
| inputs / outputs | No inputs; creates a Bytes writer and appends explicit record tags and field payloads for the fixed raw core fixture. |
| invariants | This is an independent hard-coded expected byte program, not a call into either production binding encoder; it describes only the fixture values. |
| ownership | Returned Bytes owns its vector. |
| failure | Vector growth may throw; no validation or budget admission occurs. |
| cost | Appends the fixed sequence of framed fields and raw strings to the expected vector. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0017

[Lines 138–174](../../../../../tests/unit/selection_binding_independent_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void core_literals_and_mutations(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check literal core-record bytes and selected field-mutation coverage. |
| inputs / outputs | No inputs; compares core(catalog,query) with a Bytes literal embedding literal_core_inner(), then applies 38 catalog/query field mutations and requires each encoded record to differ. |
| invariants | Mutation outcomes establish sensitivity for the enumerated fields only; raw DTO variants are encoded directly without P07 admission. |
| ownership | Fixture, mutated copies, expected writer and output strings are local owners. |
| failure | Mismatched bytes, collapsed mutation or allocation/encoding errors fail the group. |
| cost | Encodes one full core baseline and re-encodes after each selected mutation; each run traverses catalog/query and allocates output and copies. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0019

[Lines 176–197](../../../../../tests/unit/selection_binding_independent_test.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::NormalizedSql program_fixture(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the deliberately rich NormalizedSql DTO for program-record mutation checks. |
| inputs / outputs | No inputs; fills raw bound SQL, types, expressions, params/constants, core, adapters, routes, normalized outputs and limits, then returns it. |
| invariants | The source comment explicitly marks this as a byte-record fixture, not an admitted SQL program; no bind, normalize, lowering, proof or cache call occurs here. |
| ownership | Returned NormalizedSql owns nested binding/core vectors and strings. |
| failure | Fixture allocation failures propagate; malformed combinations are retained for encoding tests. |
| cost | Builds one fixed nested NormalizedSql DTO from the core fixture using ordinary vectors and strings. It performs no production encoding or mutation loop; its caller normalized_field_mutations copies and encodes the returned value. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0020

[Lines 198–252](../../../../../tests/unit/selection_binding_independent_test.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void normalized_field_mutations(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the program record against a baseline and selected normalized-field mutations. |
| inputs / outputs | No inputs; encodes the raw fixture once, copies it for each listed mutation, and requires the resulting program record differ. |
| invariants | Changes span bound source/types/wrapper/expressions/limits and normalized values/core/adapters/routes/outputs/schema; this is selected field sensitivity, not validation of a normalized program. |
| ownership | Original and mutation copies are owning DTOs; temporary encoded strings are local. |
| failure | A collapsed record or copy/encoding exception fails the group. |
| cost | Builds one rich raw DTO, encodes one baseline, then makes 79 DTO copies and one production program-record encode per listed mutation: 80 program-record encodes on the successful source path. Each program() call has a fresh finite Budget. Work and ordinary allocation follow the nested fixture size; this is not exhaustive schema coverage or measured CPU. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0022

[Lines 254–273](../../../../../tests/unit/selection_binding_independent_test.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_byte_budget(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify exact and one-under logical byte/work budgets for one scalar record. |
| inputs / outputs | Creates a three-byte string Value containing a, NUL and 0xff, encodes it with default Limits, then independently sets work, binding_key_bytes or payload_bytes to measured usage and one lower. |
| invariants | Each exact cap succeeds with identical bytes; each one-under cap must throw detail::Failure with resource_limit. The assertion covers one tiny scalar record and three logical counters only. |
| ownership | Value, expected string and budgets are local; each encoding produces its own result. |
| failure | Unexpected truncation, acceptance at one-under or wrong stop fails; allocation errors propagate. |
| cost | Runs seven encoder calls on this one record: one calibration, then one exact-cap and one one-under attempt for each of three logical counters. This measures neither allocator bytes nor CPU time. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0023

[Lines 274–275](../../../../../tests/unit/selection_binding_independent_test.cpp#L274); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L274-L275:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_binding_independent_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 276–281](../../../../../tests/unit/selection_binding_independent_test.cpp#L276); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the five independent selection-binding record test groups. |
| inputs / outputs | No inputs; invokes scalar literals, raw tree literals/mutations, core literals/mutations, normalized field mutations and exact byte budget, then returns process status. |
| invariants | Success text follows all five groups; diagnostics report mutation/type counts; only std::exception is caught. |
| ownership | Main owns no shared DTO state; every group creates local values. |
| failure | Caught standard exception prints to stderr and returns 1; other exception types are not caught. |
| cost | Finite scalar/tree/core/program serialization groups with many deliberate mutations; source calls describe intended tests, not an executed test run. |
| Design | [tests/unit/selection_binding_independent_test.cpp](../../../../../tests/unit/selection_binding_independent_test.cpp), [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |
