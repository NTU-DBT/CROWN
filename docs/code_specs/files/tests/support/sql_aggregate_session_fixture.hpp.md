# `tests/support/sql_aggregate_session_fixture.hpp` — block usage map

[Source](../../../../../tests/support/sql_aggregate_session_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ae10643a7f364121edb30d91f696067c0fd277f40fc320c14281917fae86bb29`. 68 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–18](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L18) | Callable definition: inline Cell text(std::string_view value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0002) |
| [B0003 · 19–19](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L19) | Callable definition: inline Catalog schema() | calls ; returns {1,{{@ ,{{@ ,ScalarType::string,true},{@ ,ScalarType::int64,true}}}}} · [reviewed contract](#b0003) |
| [B0004 · 20–21](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L20) | Explanatory comments or spacing. | source comment (unverified): // Genuine SQL/compiler metadata is test setup. Mutable native state is created · [reviewed contract](#b0004) |
| [B0005 · 22–43](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L22) | Type/record definition: struct Fixture | guard auto result=frontend::bind_sql_aggregate_into(account,sql,catalog);assert(std::holds_alternative&lt;fr…; returns ar::Session::create_into(account,{root,sink},identity,program,tree,physical,normal,limits); ar::Ses…; source comment (unverified): // Genuine SQL/compiler metadata is test setup. Mutable native state is created · [reviewed contract](#b0005) |
| [B0006 · 44–46](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L44) | Callable definition: inline std::string generation_file(const Fixture& f,std::uint64_t generation,std::string_view suffix=".wal") | calls std::setw, std::setfill, str; returns out.str() · [reviewed contract](#b0006) |
| [B0007 · 47–48](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L47) | Explanatory comments or spacing. | source comment (unverified): // Split only known complete fixture frames. This helper neither validates nor · [reviewed contract](#b0007) |
| [B0008 · 49–58](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L49) | Callable definition: inline std::vector&lt;std::string&gt; frames(std::string_view bytes) | calls size, assert, std::uint64_t, emplace_back; guard assert(bytes.size()-at&gt;=ar::frame_header_size);std::uint64_t body=0;; returns result; growth emplace_back; 2 loop sites; source comment (unverified): // Split only known complete fixture frames. This helper neither validates nor · [reviewed contract](#b0008) |
| [B0009 · 59–61](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L59) | Callable definition: inline std::string join(const std::vector&lt;std::string&gt;& frames,std::size_t count) | calls ; returns out; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 62–64](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L62) | Callable definition: inline ar::Decision step(ar::Session& session,std::span&lt;const runtime::sql_rows::SourceReplacement&gt; edits,bool deliver=true) | calls state, log, decide, assert; guard const auto next=session.state().disposed+1;session.log({next,edits,{},{}});auto result=session.deci…; returns result · [reviewed contract](#b0010) |
| [B0011 · 65–67](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L65) | Callable definition: inline void state(const ar::Session& s,std::uint64_t w,std::uint64_t i,std::uint64_t c,std::uint64_t d) | calls assert; guard const auto value=s.state();assert(value.logged==w && value.disposed==i && value.committed==c && val… · [reviewed contract](#b0011) |
| [B0012 · 68–68](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L68) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::sql_aggregate_session_test · [reviewed contract](#b0012) |

## B0001

[Lines 1–17](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:909c23ff781ea4159f66a1125e24f35bd81d407a809ec445ef3fefbecd3524f8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_session_fixture.hpp: include "crown/recovery/sql_aggregate_session.hpp", "sql_aggregate_file_fixture.hpp", "indexed_runtime_fixture.hpp", &lt;iomanip&gt;, &lt;sstream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–18](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Cell text(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make a borrowed string scalar usable as one nullable SQL physical cell in session fixtures. |
| inputs / outputs | string_view in; ScalarView-backed Cell out. |
| invariants | The cell borrows the source bytes; callers keep the source alive through the operation that copies or encodes it. |
| ownership | No payload copy or account allocation occurs in this adapter. |
| failure | No explicit validation; lifetime/type errors surface at the consumer. |
| cost | Fixed variant construction; string size is not traversed. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0003

[Lines 19–19](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Catalog schema()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the default nullable one-table SQL schema for the session tests. |
| inputs / outputs | No input; version-1 catalog with r(g nullable string, x nullable int64) out. |
| invariants | This schema has no implicit key or constraint; tests that need UNIQUE or FK declare those constraints explicitly. |
| ownership | Returns a fixture-owned Catalog value. |
| failure | Ordinary Catalog construction failure propagates. |
| cost | Fixed small catalog construction. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0004

[Lines 20–21](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L21:sha256:4cb9b97f201cf8f564b185bbe3a14a7642983267c2f82f99a276e3ad05ce334b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Genuine SQL/compiler metadata is test setup. Mutable native state is created only inside Session factories, so a receiving session has no shadow database. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 22–43](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one bounded test environment around a genuinely bound SQL aggregate program and the public R2 Session factories. |
| inputs / outputs | Optional indexed mode, catalog and original SQL in; account, bound program, checked minimum tree, physical options, session limits and deterministic test identities available to create/recover helpers. |
| invariants | Binding uses the real frontend; the source tree comes from the actual planner; change capture is enabled. \`create()\` uses \`Session::create_into\`; \`recover()\` supplies only the query identity to \`Session::recover_into\`, so mutable runtime state is not imported as recovery authority. Indexed work is an explicit test grant. |
| ownership | The fixture owns the temporary directory, 128 MiB receiving account and immutable compiler metadata; each returned Session owns its actual runtime and file/root locks. |
| failure | Binding or planner diagnostics fail the fixture assertion; account, factory, file and recovery failures propagate. |
| cost | One bind and minimum-tree selection per fixture plus the requested genuine session operations; indexed mode adds only its explicit physical setup and work caps. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [src/recovery/sql_aggregate_session.cpp](../../../../../src/recovery/sql_aggregate_session.cpp), Refactor.md:1325, [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0006

[Lines 44–46](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string generation_file(const Fixture& f,std::uint64_t generation,std::string_view suffix=".wal")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name one fixture generation file for controlled WAL edits. |
| inputs / outputs | Fixture root, generation and optional suffix in; path ending in a zero-padded 16-digit hexadecimal generation and suffix out. |
| invariants | Formats a path only; it neither creates a file nor validates or authorizes its contents. |
| ownership | Returns an ordinary test-owned string. |
| failure | Stream/string allocation failure propagates. |
| cost | O(path bytes) formatting and result storage. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [tests/support/sql_aggregate_file_fixture.hpp](../../../../../tests/support/sql_aggregate_file_fixture.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0007

[Lines 47–48](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L48:sha256:8cccf33ba508f9f8c03b089f9e1d9a9da33946db02d2280679ea500606b44bf6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Split only known complete fixture frames. This helper neither validates nor authorizes imported state; hostile mutations use production recovery afterward. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 49–58](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::vector<std::string> frames(std::string_view bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Split known complete fixture bytes at their declared frame lengths before a targeted mutation. |
| inputs / outputs | Fixture file bytes in; byte-preserving complete-frame strings out. |
| invariants | Checks enough header bytes and that each declared body fits the remaining input; it does not validate hashes, versions, types or semantic authority. Hostile edits are passed back through production recovery. |
| ownership | Returns owning test strings independent of the source view. |
| failure | Assertions stop on a short header or impossible frame length. |
| cost | O(frame count + input bytes), with storage proportional to copied bytes. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0009

[Lines 59–61](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string join(const std::vector<std::string>& frames,std::size_t count)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reassemble a chosen prefix of already split fixture frames. |
| inputs / outputs | Frame vector and prefix count in; concatenated bytes out. |
| invariants | Copies exactly the requested prefix and performs no frame validation. |
| ownership | Returns a fresh test-owned string. |
| failure | An out-of-range count violates the test precondition; allocation failure propagates. |
| cost | O(bytes in selected frames) copy and storage. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0010

[Lines 62–64](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline ar::Decision step(ar::Session& session,std::span<const runtime::sql_rows::SourceReplacement> edits,bool deliver=true)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one test command through the real Session log/decision path and optionally acknowledge its actual output. |
| inputs / outputs | Ready Session, replacement span and delivery flag in; actual Decision out. |
| invariants | Transport command ordinal is \`disposed + 1\`; a rejected command is not delivered. Successful delivery must be confirmed by the real sink owner. |
| ownership | The helper passes borrowed edits only through \`log\`; Session owns its pending input and output spool. |
| failure | Session/file errors and the delivery assertion propagate; this helper does not retry or translate failures. |
| cost | One genuine log and decision, plus one sink append when delivery is requested and output is not rejected. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0011

[Lines 65–67](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void state(const ar::Session& s,std::uint64_t w,std::uint64_t i,std::uint64_t c,std::uint64_t d)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the four independent durable/session frontiers at a test boundary. |
| inputs / outputs | Session and expected W/I/C/D values in; assertion success or failure out. |
| invariants | Compares W to logged, I to disposed, C to committed and D to delivered; it does not collapse WAL ordinal, source progress or native sequence into one counter. |
| ownership | Borrows the ready Session and reads its public state. |
| failure | Any frontier mismatch fails the test assertion; an invalidated Session rejects state access. |
| cost | Fixed number of state reads and scalar comparisons. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0012

[Lines 68–68](../../../../../tests/support/sql_aggregate_session_fixture.hpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L68:sha256:0f51d2659db00bf65eab7675fffa3044b854e9a8a6b1c716ab512242848ee9cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_session_fixture.hpp: namespace crown::sql_aggregate_session_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |
