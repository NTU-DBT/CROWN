# `tests/support/sql_rows_session_fixture.hpp` — block usage map

[Source](../../../../../tests/support/sql_rows_session_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `8f3668689afbfaf004d29a71ee4ce207505a7bf2482d11e7403109ccdd3dae21`. 304 lines partitioned into 46 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/support/sql_rows_session_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion. |  · [reviewed contract](#b0001) |
| [B0002 · 24–38](../../../../../tests/support/sql_rows_session_fixture.hpp#L24) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // negative, exact unsigned magnitude · [reviewed contract](#b0002) |
| [B0003 · 39–39](../../../../../tests/support/sql_rows_session_fixture.hpp#L39) | Callable definition: inline Cell text(std::string_view value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0003) |
| [B0004 · 40–40](../../../../../tests/support/sql_rows_session_fixture.hpp#L40) | Explanatory comments or spacing. |  |
| [B0005 · 41–45](../../../../../tests/support/sql_rows_session_fixture.hpp#L41) | Callable definition: inline Catalog bag_schema() | calls ; returns {1, {{@ , {{@ , ScalarType::int64, false}, · [reviewed contract](#b0005) |
| [B0006 · 46–46](../../../../../tests/support/sql_rows_session_fixture.hpp#L46) | Explanatory comments or spacing. |  |
| [B0007 · 47–55](../../../../../tests/support/sql_rows_session_fixture.hpp#L47) | Callable definition: inline frontend::SqlRowsProgram compile_rows(const resource::MemoryAccount& account, std::string_view sql, const Catalog& catalog) | calls frontend::bind_sql_rows_into, Error, std::move; returns std::get&lt;frontend::SqlRowsProgram&gt;(std::move(result)) · [reviewed contract](#b0007) |
| [B0008 · 56–56](../../../../../tests/support/sql_rows_session_fixture.hpp#L56) | Explanatory comments or spacing. |  |
| [B0009 · 57–63](../../../../../tests/support/sql_rows_session_fixture.hpp#L57) | Callable definition: inline FreeConnexTree tree_for(const frontend::SqlRowsProgram& program) | calls contradiction, export_core, planner::minimum_tree, assert; guard assert(selected.status == planner::OracleStatus::proven_minimum && selected.tree);; returns {}; *selected.tree · [reviewed contract](#b0009) |
| [B0010 · 64–78](../../../../../tests/support/sql_rows_session_fixture.hpp#L64) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Genuine public session factories own every mutable native/source state used · [reviewed contract](#b0010) |
| [B0011 · 79–90](../../../../../tests/support/sql_rows_session_fixture.hpp#L79) | Callable definition: explicit Fixture(bool indexed = false, Catalog catalog = bag_schema(), std::string_view sql = "SELECT x FROM r", runtime::sql_row… | calls bag_schema, program, compile_rows, tree · [reviewed contract](#b0011) |
| [B0012 · 91–91](../../../../../tests/support/sql_rows_session_fixture.hpp#L91) | Explanatory comments or spacing. |  |
| [B0013 · 92–95](../../../../../tests/support/sql_rows_session_fixture.hpp#L92) | Callable definition: \[\[nodiscard\]\] sr::Session create() | calls sr::Session::create_into; returns sr::Session::create_into(account, {root, sink}, identity, program, · [reviewed contract](#b0013) |
| [B0014 · 96–98](../../../../../tests/support/sql_rows_session_fixture.hpp#L96) | Callable definition: \[\[nodiscard\]\] sr::Session recover() | calls sr::Session::recover_into; returns sr::Session::recover_into(account, {root, sink}, identity.query_id, limits) · [reviewed contract](#b0014) |
| [B0015 · 99–100](../../../../../tests/support/sql_rows_session_fixture.hpp#L99) | Closes surrounding scope/type. |  · [reviewed contract](#b0015) |
| [B0016 · 101–106](../../../../../tests/support/sql_rows_session_fixture.hpp#L101) | Callable definition: inline void state(const sr::Session& session, std::uint64_t w, std::uint64_t i, std::uint64_t c, std::uint64_t d) | calls assert; guard assert(value.logged == w && value.disposed == i && · [reviewed contract](#b0016) |
| [B0017 · 107–107](../../../../../tests/support/sql_rows_session_fixture.hpp#L107) | Explanatory comments or spacing. |  |
| [B0018 · 108–116](../../../../../tests/support/sql_rows_session_fixture.hpp#L108) | Callable definition: inline Row own_row(std::span&lt;const Cell&gt; cells) | calls reserve, size, emplace_back, storage::export_scalar; returns result; growth emplace_back, reserve; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 117–117](../../../../../tests/support/sql_rows_session_fixture.hpp#L117) | Explanatory comments or spacing. |  |
| [B0020 · 118–124](../../../../../tests/support/sql_rows_session_fixture.hpp#L118) | Callable definition: inline Bag current_bag(sr::Session& session) | calls results, next, assert, emplace; guard assert(result.emplace(item-&gt;tuple.export_values(), item-&gt;multiplicity).second);; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 125–125](../../../../../tests/support/sql_rows_session_fixture.hpp#L125) | Explanatory comments or spacing. |  |
| [B0022 · 126–129](../../../../../tests/support/sql_rows_session_fixture.hpp#L126) | Callable definition: inline std::uint64_t add(std::uint64_t a, std::uint64_t b) | calls assert; guard assert(b &lt;= UINT64_MAX - a);; returns a + b · [reviewed contract](#b0022) |
| [B0023 · 130–133](../../../../../tests/support/sql_rows_session_fixture.hpp#L130) | Callable definition: inline std::uint64_t multiply(std::uint64_t a, std::uint64_t b) | calls assert; guard assert(!a \|\| b &lt;= UINT64_MAX / a);; returns a * b · [reviewed contract](#b0023) |
| [B0024 · 134–134](../../../../../tests/support/sql_rows_session_fixture.hpp#L134) | Explanatory comments or spacing. |  |
| [B0025 · 135–147](../../../../../tests/support/sql_rows_session_fixture.hpp#L135) | Callable definition: inline Changes difference(const Bag& before, const Bag& after) | calls find, end, emplace, contains; returns result; growth emplace; 2 loop sites · [reviewed contract](#b0025) |
| [B0026 · 148–148](../../../../../tests/support/sql_rows_session_fixture.hpp#L148) | Explanatory comments or spacing. |  |
| [B0027 · 149–153](../../../../../tests/support/sql_rows_session_fixture.hpp#L149) | Type/record definition: struct DecodedRowEpoch |  · [reviewed contract](#b0027) |
| [B0028 · 154–154](../../../../../tests/support/sql_rows_session_fixture.hpp#L154) | Explanatory comments or spacing. |  |
| [B0029 · 155–162](../../../../../tests/support/sql_rows_session_fixture.hpp#L155) | Callable definition: inline std::uint64_t read_le(std::string_view bytes, std::size_t& at, unsigned width) | calls assert, size, std::uint64_t; guard assert(width == 1 \|\| width == 4 \|\| width == 8);; returns result; 1 loop sites · [reviewed contract](#b0029) |
| [B0030 · 163–163](../../../../../tests/support/sql_rows_session_fixture.hpp#L163) | Explanatory comments or spacing. |  |
| [B0031 · 164–169](../../../../../tests/support/sql_rows_session_fixture.hpp#L164) | Callable definition: inline std::string_view take(std::string_view bytes, std::size_t& at, std::size_t count) | calls assert, size, substr; guard assert(at &lt;= bytes.size() && count &lt;= bytes.size() - at);; returns value · [reviewed contract](#b0031) |
| [B0032 · 170–170](../../../../../tests/support/sql_rows_session_fixture.hpp#L170) | Explanatory comments or spacing. |  |
| [B0033 · 171–180](../../../../../tests/support/sql_rows_session_fixture.hpp#L171) | Callable definition: inline Date date_from_days(std::int32_t count) | calls assert, ok, std::setfill, std::setw; guard assert(ymd.ok());; returns Date::parse(text.str()) · [reviewed contract](#b0033) |
| [B0034 · 181–181](../../../../../tests/support/sql_rows_session_fixture.hpp#L181) | Explanatory comments or spacing. |  |
| [B0035 · 182–212](../../../../../tests/support/sql_rows_session_fixture.hpp#L182) | Callable definition: inline runtime::aggregate::SqlValue read_cell(std::string_view bytes, std::size_t& at) | calls read_le, assert, take, std::string; guard assert(present &lt;= 1);; returns std::nullopt; Value{std::bit_cast&lt;std::int64_t&gt;(read_le(bytes, at, 8))} · [reviewed contract](#b0035) |
| [B0036 · 213–216](../../../../../tests/support/sql_rows_session_fixture.hpp#L213) | Explanatory comments or spacing. | source comment (unverified): // This deliberately decodes the row payload without calling the row codec's · [reviewed contract](#b0036) |
| [B0037 · 217–265](../../../../../tests/support/sql_rows_session_fixture.hpp#L217) | Callable definition: inline DecodedRowEpoch decode_row_epoch(const frontend::SqlRowsProgram& program, std::string_view frame) | calls assert, size, substr, sr::inspect; guard assert(frame.size() &gt;= header + 107 && frame.substr(0, 8) == "CROWNRW2");; returns result; growth emplace_back, push_back, reserve; 2 loop sites; source comment (unverified): // This deliberately decodes the row payload without calling the row codec's · [reviewed contract](#b0037) |
| [B0038 · 266–266](../../../../../tests/support/sql_rows_session_fixture.hpp#L266) | Explanatory comments or spacing. |  |
| [B0039 · 267–272](../../../../../tests/support/sql_rows_session_fixture.hpp#L267) | Callable definition: inline Changes changes(const DecodedRowEpoch& epoch) | calls assert, emplace; guard assert(result.emplace(tuple, change).second);; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0039) |
| [B0040 · 273–273](../../../../../tests/support/sql_rows_session_fixture.hpp#L273) | Explanatory comments or spacing. |  |
| [B0041 · 274–280](../../../../../tests/support/sql_rows_session_fixture.hpp#L274) | Callable definition: inline std::string generation_file(const Fixture& fixture, std::uint64_t generation, std::string_view suffix = ".wal") | calls std::setw, std::setfill, str; returns out.str() · [reviewed contract](#b0041) |
| [B0042 · 281–281](../../../../../tests/support/sql_rows_session_fixture.hpp#L281) | Explanatory comments or spacing. |  |
| [B0043 · 282–296](../../../../../tests/support/sql_rows_session_fixture.hpp#L282) | Callable definition: inline std::vector&lt;std::string&gt; frames(std::string_view bytes) | calls size, assert, std::uint64_t, emplace_back; guard assert(bytes.size() - at &gt;= sr::frame_header_size);; returns result; growth emplace_back; 2 loop sites · [reviewed contract](#b0043) |
| [B0044 · 297–297](../../../../../tests/support/sql_rows_session_fixture.hpp#L297) | Explanatory comments or spacing. |  |
| [B0045 · 298–302](../../../../../tests/support/sql_rows_session_fixture.hpp#L298) | Callable definition: inline std::string join(const std::vector&lt;std::string&gt;& parts, std::size_t count) | calls ; returns result; 1 loop sites · [reviewed contract](#b0045) |
| [B0046 · 303–304](../../../../../tests/support/sql_rows_session_fixture.hpp#L303) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::sql_rows_session_test · [reviewed contract](#b0046) |

## B0001

[Lines 1–23](../../../../../tests/support/sql_rows_session_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:943c8cac1e8a8133be68cd6960881c28a04b8bbb4b46381075d500c69eeea9ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare dependencies for the durable row-session test fixture. |
| inputs / outputs | Imports compiler, planner, runtime, recovery, account, and file-test interfaces. |
| invariants | These includes expose test and production declarations; no runtime behavior originates here. |
| ownership | This declaration/comment region owns no runtime state; object lifetimes are defined by the adjacent callable or type. |
| failure | No executable failure path is introduced by this declaration/comment region. |
| cost | Compile-time inclusion only. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0002

[Lines 24–38](../../../../../tests/support/sql_rows_session_fixture.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L38:sha256:1df0ad5c9db613afa10e6d152c6353c09024fa6304b41a7679d7ad1f5b4b15c0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open the test namespace and name shared row-session and bag types. |
| inputs / outputs | Aliases Session, Cell, Row, unsigned-weight Bag, signed-magnitude Changes, and file-fixture helpers. |
| invariants | Signed output is represented as a sign bit plus uint64 magnitude; a Bag maps typed rows to uint64 weights. |
| ownership | This declaration/comment region owns no runtime state; object lifetimes are defined by the adjacent callable or type. |
| failure | No executable failure path is introduced by this declaration/comment region. |
| cost | Compile-time aliases only. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0003

[Lines 39–39](../../../../../tests/support/sql_rows_session_fixture.hpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L39:sha256:e007d00e14911e72a5b7782ccf7ee5253b81a5740d70fcbfe4822fa7c2fdd429
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a borrowed text cell. |
| inputs / outputs | Takes string_view and returns Cell containing a ScalarView. |
| invariants | The source text must outlive use of the returned view. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | One scalar-view construction. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0005

[Lines 41–45](../../../../../tests/support/sql_rows_session_fixture.hpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L45:sha256:ae4b32da2379abafe4b3027246adbd28d1d64507ed817d5e7819a00b7df3baaf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the fixed nullable bag-test schema. |
| inputs / outputs | Returns Catalog with one r relation and ordered k, id, nullable x, nullable tag columns. |
| invariants | Physical test rows follow this catalog order and nullability. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Small fixed catalog construction. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0007

[Lines 47–55](../../../../../tests/support/sql_rows_session_fixture.hpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L55:sha256:21e5506fbaf46bfca6ff93c6cf73ede5fc54a0525e8aec7d168d221097c6a1bc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind SQL text and retain its canonical binding image for durable SqlRows Session fixtures. |
| inputs / outputs | Takes account, SQL and Catalog; sets SqlRowsBindOptions::retain_binding_image=true; returns a bound program or converts BindingDiagnostic to Error. |
| invariants | Only successful binding yields a program; the immutable program retains exact source/catalog/typed-parameter CBOR for durable records while the canonical source hash and binder-work policy stay unchanged. |
| ownership | SQL and Catalog are borrowed for the bind call; the supplied account owns the returned immutable program metadata and retained canonical CBOR binding image. |
| failure | BindingDiagnostic is converted to Error; parser, binder and account allocation errors propagate, including inability to retain the canonical image. |
| cost | Normal SQL binding plus one additional linear, account-charged copy of the canonical binding image. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0009

[Lines 57–63](../../../../../tests/support/sql_rows_session_fixture.hpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L63:sha256:822a0d18a54b4baef2b43d242f27253889fd73d0377f8d428f211e738554ea6d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose a proven minimum FreeConnex tree. |
| inputs / outputs | Takes program; returns empty tree for contradiction or selected minimum tree otherwise. |
| invariants | Non-contradiction selection must have proven_minimum status and a tree. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Fixture-time planner oracle work. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0010

[Lines 64–78](../../../../../tests/support/sql_rows_session_fixture.hpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L78:sha256:dda0075f29882a4925deb586cf64a0ce022387cafad9fe7de47e0f4acc5edc4c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Introduce the Fixture and its public-owner boundary. |
| inputs / outputs | Comment and struct opening establish that Session factories own mutable runtime/source state. |
| invariants | Fixture holds compiler metadata and fixed options; Session owns the live state. |
| ownership | Fixture owns its directory, account handle, program and options; create/recover return Session owners that hold mutable runtime and file state. |
| failure | No executable failure path is introduced by this declaration/comment region. |
| cost | Declaration/comment only. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0011

[Lines 79–90](../../../../../tests/support/sql_rows_session_fixture.hpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L90:sha256:6e6f5a7b2682cf126d3d2911d90608c4c3ff546c9f979a956492d4b51dc7ad9d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store durable-session fixture state. |
| inputs / outputs | Members include temp paths, finite account, bound program/tree, physical and SQL-row options, output/session limits, and identity. |
| invariants | Root and sink use the fixture directory; indexed limits are set by the constructor. |
| ownership | Fixture owns its directory, account handle, program and options; create/recover return Session owners that hold mutable runtime and file state. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Fixed declarations; memory cap is explicit. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0013

[Lines 92–95](../../../../../tests/support/sql_rows_session_fixture.hpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L95:sha256:2c58d1163509ac09c0d33dfe80150558f9c8167649ba87623ded32daa709dd06
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize reference or indexed fixture configuration. |
| inputs / outputs | Accepts backend choice, schema, SQL, runtime options and output limits; binds/plans and fixes query/sink identities. |
| invariants | Indexed mode receives explicit finite rebuild-work limits; identifiers are deterministic test inputs. |
| ownership | Fixture owns its directory, account handle, program and options; create/recover return Session owners that hold mutable runtime and file state. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Fixture-time bind, plan and small option setup. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0014

[Lines 96–98](../../../../../tests/support/sql_rows_session_fixture.hpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L98:sha256:3c7ac736b5702d5d4fe908be45ec4b5fdefb116bf67a0a52b39eb75b162ef29d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a public durable Session. |
| inputs / outputs | Calls Session::create_into using all fixture-owned admission and file inputs; returns the Session owner. |
| invariants | Mutable native/source state and file ownership reside in the returned Session. |
| ownership | Fixture owns its directory, account handle, program and options; create/recover return Session owners that hold mutable runtime and file state. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Initial admission and durable namespace creation under configured caps. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0015

[Lines 99–100](../../../../../tests/support/sql_rows_session_fixture.hpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L100:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover a public durable Session. |
| inputs / outputs | Calls Session::recover_into for the fixture paths, query id and limits; returns the recovered owner. |
| invariants | Recovery uses only the persisted fixture namespace and public receiving API. |
| ownership | Fixture owns its directory, account handle, program and options; create/recover return Session owners that hold mutable runtime and file state. |
| failure | No executable failure path is introduced by this declaration/comment region. |
| cost | Bounded recovery/replay according to configured limits. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0016

[Lines 101–106](../../../../../tests/support/sql_rows_session_fixture.hpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L106:sha256:b4a5fa31e3ebd3c5a9fd2e0d77c48c89d70ca35fcdc3016200ead25bdcc742c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the Fixture type. |
| inputs / outputs | Ends the type after its factories. |
| invariants | No additional behavior is declared. |
| ownership | Fixture owns its directory, account handle, program and options; create/recover return Session owners that hold mutable runtime and file state. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Compile-time delimiter. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0018

[Lines 108–116](../../../../../tests/support/sql_rows_session_fixture.hpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L116:sha256:8b45d03ae325478f8560be90982c5be3821f60cf7e35ad99205549fe9cfa28c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert Session durable frontiers. |
| inputs / outputs | Reads state and compares logged, disposed, committed, and delivered sequence values to expected scalars. |
| invariants | Checks the exact selected tuple of frontiers; it does not infer SQL result correctness. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | One state read and scalar comparisons. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0020

[Lines 118–124](../../../../../tests/support/sql_rows_session_fixture.hpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L124:sha256:c706a51b3ac357e6ad101323cf9a0019112a1b192183b0d70a965dae78311d0e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a typed row into the independent expected representation. |
| inputs / outputs | Takes span of Cells and exports present cells while preserving nulls into Row. |
| invariants | Returned width and null positions match the input span. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Linear in row width and copies present scalar values. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0022

[Lines 126–129](../../../../../tests/support/sql_rows_session_fixture.hpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L126-L129:sha256:8d6e73ba9846a27489fc5dce3edaebd6e8fffda21adc85c169e7f19495ed4bee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain public results into an unsigned bag map. |
| inputs / outputs | Takes mutable Session; consumes results cursor and returns tuple-to-multiplicity map. |
| invariants | The test expects each distinct output tuple to appear once in the cursor with its uint64 weight. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | One cursor drain and ordered-map insertions. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0023

[Lines 130–133](../../../../../tests/support/sql_rows_session_fixture.hpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L130-L133:sha256:fe669ece00988ba95ccce8eb3bb70bf9269ad900a7ca12aeb926085242935fbf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add unsigned bag weights with an overflow assertion. |
| inputs / outputs | Takes two uint64 values and returns their sum. |
| invariants | The expected sum must fit uint64. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Constant-time checked arithmetic. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0025

[Lines 135–147](../../../../../tests/support/sql_rows_session_fixture.hpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L147:sha256:5968239bb065377a8dd75f80fec8fd82c28858043e770350b0d6923620690491
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Multiply unsigned bag weights with an overflow assertion. |
| inputs / outputs | Takes two uint64 values and returns their product. |
| invariants | Zero is accepted; otherwise product must fit uint64. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Constant-time checked arithmetic. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0027

[Lines 149–153](../../../../../tests/support/sql_rows_session_fixture.hpp#L149); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L153:sha256:e2edf41497b03659d179fab93f7282d7a29d07a58b2126629338a42a28ee4651
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute signed output difference between two bags. |
| inputs / outputs | Takes before/after maps and returns changed rows as negative flag plus exact unsigned magnitude. |
| invariants | No signed narrowing; unchanged weights are omitted. |
| ownership | The declared value owns its stored members; views/spans inside it remain borrowed only where their types say so. |
| failure | No executable failure path is introduced by this type declaration. |
| cost | Linear ordered-map traversal and lookups. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0029

[Lines 155–162](../../../../../tests/support/sql_rows_session_fixture.hpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L155-L162:sha256:c2546d3a4b5de3de38f52536049389a39aa314e29b40bd3afe5a91570f440440
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent an independently decoded row epoch. |
| inputs / outputs | Stores three sequence identifiers, changed flags, and decoded rows with sign/magnitude. |
| invariants | Weights remain uint64 and signs stay separate. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Value record; storage scales with decoded output. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0031

[Lines 164–169](../../../../../tests/support/sql_rows_session_fixture.hpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L164-L169:sha256:b9e55805ec4584fa3519a266a158dd0ed756df3850f5cfb4fa121a5dc27a5504
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a bounded little-endian integer. |
| inputs / outputs | Takes bytes, mutable offset and width; supports widths 1, 4 or 8 and returns uint64. |
| invariants | Checks remaining bytes before advancing offset. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Linear in the small fixed width. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0033

[Lines 171–180](../../../../../tests/support/sql_rows_session_fixture.hpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L171-L180:sha256:f5a9e8cc2abd7d452ef3f15aab5bf56007ffc22e5fd938001c552ad4b7cd0f04
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Take a bounded frame slice. |
| inputs / outputs | Takes string_view, mutable offset and byte count; returns borrowed substring and advances offset. |
| invariants | Range is checked before cursor advance. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Constant-time slice bookkeeping. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0035

[Lines 182–212](../../../../../tests/support/sql_rows_session_fixture.hpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L182-L212:sha256:82e9b1d295e2a2dcf70d33decb8771fa594a7c4ac9dfa291b3dd4840ce28c5cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert an epoch-day value to Date. |
| inputs / outputs | Takes int32 days, formats zero-padded civil date, parses Date result. |
| invariants | Chrono date must be valid. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Small fixed date formatting/parsing. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0036

[Lines 213–216](../../../../../tests/support/sql_rows_session_fixture.hpp#L213); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L213-L216:sha256:f20e642d20a5968842057083ce4e9970b7fb0e8af41a934a4c4d472310c76e00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document independent typed-payload oracle boundary. |
| inputs / outputs | Clarifies that inspect validates envelope/schema while this parser derives values and signed magnitudes. |
| invariants | Does not claim independent checksum or envelope validation. |
| ownership | This declaration/comment region owns no runtime state; object lifetimes are defined by the adjacent callable or type. |
| failure | No executable failure path is introduced by this declaration/comment region. |
| cost | Comment only. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0037

[Lines 217–265](../../../../../tests/support/sql_rows_session_fixture.hpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L217-L265:sha256:619d18e8a725dc5a51ebeaa2dfeb30244f5e14cf329b389b1fd7595e5a1c1b57
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the row epoch payload independently. |
| inputs / outputs | Takes bound program and frame, checks header/kind, parses metadata/typed rows/signs, then compares structural metadata with inspect. |
| invariants | Checks row width, strict canonical key order, nonzero magnitudes, exact consumption, metadata agreement, and output_changed iff rows exist. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | One inspect plus full frame parse; storage scales with decoded rows. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0039

[Lines 267–272](../../../../../tests/support/sql_rows_session_fixture.hpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L267-L272:sha256:4334c79a49dd1ca00c1a6dcab3fc938b60795d55b9c3c60a8525626d1ee60738
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build signed changes map from decoded epoch rows. |
| inputs / outputs | Takes decoded epoch and inserts typed tuples with their exact sign/magnitude. |
| invariants | Duplicate tuple keys assert; signed magnitude is preserved. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Linear in rows plus map operations. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0041

[Lines 274–280](../../../../../tests/support/sql_rows_session_fixture.hpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L274-L280:sha256:55d50a198f5fab228bd6480e16b7caa31e651a4a7e915e6911f67ff2a1fd84d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Format a generation WAL pathname. |
| inputs / outputs | Takes Fixture, generation and optional suffix; returns root plus zero-padded hexadecimal generation and suffix. |
| invariants | Formatting matches generation files created by these session tests. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Small formatted string construction. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0043

[Lines 282–296](../../../../../tests/support/sql_rows_session_fixture.hpp#L282); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L282-L296:sha256:4e4173d0fc0bee9374c6e60b9fd5b6083e6978527f282821c6b41aa8aa6cba8f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Split a file into bounded length-prefixed frames. |
| inputs / outputs | Takes file bytes and returns owned frame strings after reading each body length. |
| invariants | Requires complete header/body and advances exactly over all input bytes. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Linear scan with a copy for each frame. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0045

[Lines 298–302](../../../../../tests/support/sql_rows_session_fixture.hpp#L298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L298-L302:sha256:4b48c8dcd23f52fb5899261e532a14fcb9e89046bd617adf11c80825713de8f3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Concatenate a prefix of frame strings. |
| inputs / outputs | Takes frame vector and count; returns concatenated owned bytes for the requested prefix. |
| invariants | Caller supplies a count no larger than vector size. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Linear in selected bytes copied. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0046

[Lines 303–304](../../../../../tests/support/sql_rows_session_fixture.hpp#L303); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L303-L304:sha256:f190186429c7063b9af089c98cee9db79cdd7bcfe75a7e7aa2eda06153d0a64f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the fixture namespace. |
| inputs / outputs | Ends the test namespace after all helper declarations. |
| invariants | No additional declarations or runtime behavior. |
| ownership | This declaration/comment region owns no runtime state; object lifetimes are defined by the adjacent callable or type. |
| failure | No executable failure path is introduced by this declaration/comment region. |
| cost | Compile-time delimiter. |
| Design | [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |
