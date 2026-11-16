# `tests/support/session_journal_stream_cases.hpp` — block usage map

[Source](../../../../../tests/support/session_journal_stream_cases.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `38f1a06209651b6f36344807b9340b705c6c5632bd9914ddbdeb1a4f858bc0a2`. 118 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/support/session_journal_stream_cases.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // data/options own bytes; name borrows a literal; progress expectations are ordinary data. · [reviewed contract](#b0001) |
| [B0002 · 15–21](../../../../../tests/support/session_journal_stream_cases.hpp#L15) | Type/record definition: struct Case | source comment (unverified): // data/options own bytes; name borrows a literal; progress expectations are ordinary data. · [reviewed contract](#b0002) |
| [B0003 · 22–23](../../../../../tests/support/session_journal_stream_cases.hpp#L22) | declares namespace scope. |  · [reviewed contract](#b0003) |
| [B0004 · 24–30](../../../../../tests/support/session_journal_stream_cases.hpp#L24) | Callable definition: inline io::InputEvent event(std::uint64_t sequence,std::int64_t x,std::int64_t y, std::string source,std::uint64_t offset) | calls std::move; returns result; growth insert · [reviewed contract](#b0004) |
| [B0005 · 31–31](../../../../../tests/support/session_journal_stream_cases.hpp#L31) | Explanatory comments or spacing. |  |
| [B0006 · 32–35](../../../../../tests/support/session_journal_stream_cases.hpp#L32) | Callable definition: inline void finish(Case& value) | calls size · [reviewed contract](#b0006) |
| [B0007 · 36–42](../../../../../tests/support/session_journal_stream_cases.hpp#L36) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0007) |
| [B0008 · 43–116](../../../../../tests/support/session_journal_stream_cases.hpp#L43) | Callable definition: inline std::vector&lt;Case&gt; cases(const Catalog& catalog) | calls size, std::invalid_argument, reserve, io::write_input_json; returns result; growth emplace, push_back, reserve; source comment (unverified): // These fixtures assume exactly one physical table e(x,y), with two int64 · [reviewed contract](#b0008) |
| [B0009 · 117–118](../../../../../tests/support/session_journal_stream_cases.hpp#L117) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::session_journal_stream_test · [reviewed contract](#b0009) |

## B0001

[Lines 1–14](../../../../../tests/support/session_journal_stream_cases.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:0c67f2cb09e1a25e61fd0c22cfb1b3df0a7ded7925e0058dad1664769b4f697e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_journal_stream_cases.hpp: include "crown/io/ingest.hpp", &lt;array&gt;, &lt;cstdint&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;utility&gt;, &lt;vector&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–21](../../../../../tests/support/session_journal_stream_cases.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Case
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one two-record input profile with literal progress expectations. |
| inputs / outputs | name is a static literal pointer; options/data are owning; bytes are cumulative consumed-byte checkpoints; source_offsets are explicit expected source positions. |
| invariants | Profiles require one e(x,y) table with int64 columns; byte checkpoints differ from configured/source offset origin. |
| ownership | Copies options maps/string/data deeply; name borrows immortal literal. Default moves follow actual standard members. |
| failure | Copy/construction can allocate; Case itself establishes no typed admission or progress authority. |
| cost | Storage proportional to profile bytes/options; fixed two-element expected arrays. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 22–23](../../../../../tests/support/session_journal_stream_cases.hpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L23:sha256:2fb1ccd015c87682509518c26fbecd92ee36bceb2639519b495621d9e1628745
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_journal_stream_cases.hpp: declare the recorded helper API/type boundary. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 24–30](../../../../../tests/support/session_journal_stream_cases.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline io::InputEvent event(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one owned physical input for wire-profile serialization. |
| inputs / outputs | Returns insertion into table0 with sequence,x,y and moved source string/offset. |
| invariants | Assumes trusted int64 e(x,y); no catalog/type/source validation happens here. |
| ownership | Owns Row and source string; no reference to caller string is retained after by-value transfer. |
| failure | Row/string construction can allocate; no native state is mutated. |
| cost | One two-scalar row and source DTO construction/copy/move. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 32–35](../../../../../tests/support/session_journal_stream_cases.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void finish(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind parser record/total-byte caps to the finite two-record profile. |
| inputs / outputs | Sets records2 and total_bytes=data.size after complete profile encoding. |
| invariants | Total byte cap is full encoded stream size, distinct from per-event progress/source offsets and peak parse memory. |
| ownership | Mutates owned Case options; no data copy or native allowance. |
| failure | No explicit failure for scalar assignments; downstream parser performs real checks. |
| cost | Fixed field updates; data.size is constant-time. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 36–42](../../../../../tests/support/session_journal_stream_cases.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L42:sha256:38692a380e91a1bc00a130caf9ec2349f5d2a2624ac385eeade3ed0bf5c498d1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_journal_stream_cases.hpp: namespace detail. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 43–116](../../../../../tests/support/session_journal_stream_cases.hpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::vector<Case> cases(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create eight owned stream profiles with exact byte/source checkpoints. |
| inputs / outputs | Requires catalog e(x,y) two int64 columns; reserves8 and builds JSONL, binary, CSV and five legacy forms. |
| invariants | JSON/binary use production serializers, so wire bytes are not an independent encoder oracle. Delimited literal strings/offset arrays provide separate expected progress facts. |
| ownership | Returns vector owning all data/options; transient serialized strings are copied into combined wire payloads. |
| failure | Wrong catalog throws invalid_argument; serializer/copy/reserve allocations/errors propagate before result. |
| cost | Two actual serializations for each wire profile, literal copies and eight Case allocations/moves; no native session execution. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
Case jsonl{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the JSONL recovery/progress fixture. |
| inputs / outputs | Two wire events with source offsets10/20 and newline delimiters. |
| invariants | Consumed bytes include each newline; offsets come from explicit encoded source positions. |
| ownership | Local Case owns options/data and is moved into result; literal names/source strings retain their normal owned/static lifetimes. |
| failure | Ordinary construction/serialization can throw before the Case is returned; no session mutation. |
| cost | Bounded two-event encoding/copy plus vector insertion; actual parsing and checkpoint restore happen in callers. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
Case binary{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the binary recovery/progress fixture. |
| inputs / outputs | Two concatenated binary frames with source offsets30/40. |
| invariants | Consumed checkpoints are cumulative frame sizes; wire source offsets remain distinct. |
| ownership | Local Case owns options/data and is moved into result; literal names/source strings retain their normal owned/static lifetimes. |
| failure | Ordinary construction/serialization can throw before the Case is returned; no session mutation. |
| cost | Bounded two-event encoding/copy plus vector insertion; actual parsing and checkpoint restore happen in callers. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
Case csv{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the CSV recovery/progress fixture. |
| inputs / outputs | Literal y;x header followed by 2;1 and 3;2 with semicolon delimiter; byte origin100. |
| invariants | Header name remapping is intentional; bytes8/12 and source104/108 are literal expectations. |
| ownership | Local Case owns options/data and is moved into result; literal names/source strings retain their normal owned/static lifetimes. |
| failure | Ordinary construction/serialization can throw before the Case is returned; no session mutation. |
| cost | Bounded two-event encoding/copy plus vector insertion; actual parsing and checkpoint restore happen in callers. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
Case signed_rows{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the legacy_signed recovery/progress fixture. |
| inputs / outputs | +,1,2 and +,2,3 lines, table0, source byte origin200. |
| invariants | Consumed6/12 and offsets200/206 count line starts relative to origin. |
| ownership | Local Case owns options/data and is moved into result; literal names/source strings retain their normal owned/static lifetimes. |
| failure | Ordinary construction/serialization can throw before the Case is returned; no session mutation. |
| cost | Bounded two-event encoding/copy plus vector insertion; actual parsing and checkpoint restore happen in callers. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
Case relations{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the legacy_relations recovery/progress fixture. |
| inputs / outputs | +,E,1,2 and +,E,2,3 with explicit E→table0 map and origin300. |
| invariants | Consumed8/16 and offsets300/308 preserve relation-token interpretation. |
| ownership | Local Case owns options/data and is moved into result; literal names/source strings retain their normal owned/static lifetimes. |
| failure | Ordinary construction/serialization can throw before the Case is returned; no session mutation. |
| cost | Bounded two-event encoding/copy plus vector insertion; actual parsing and checkpoint restore happen in callers. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
Case insert_only{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the legacy_insert_only recovery/progress fixture. |
| inputs / outputs | 1,2 and 2,3 lines, table0, origin400. |
| invariants | Consumed4/8 and offsets400/404 preserve line-start byte positions. |
| ownership | Local Case owns options/data and is moved into result; literal names/source strings retain their normal owned/static lifetimes. |
| failure | Ordinary construction/serialization can throw before the Case is returned; no session mutation. |
| cost | Bounded two-event encoding/copy plus vector insertion; actual parsing and checkpoint restore happen in callers. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
Case flags{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the legacy_flags recovery/progress fixture. |
| inputs / outputs | 1,1,2 and 1,2,3 lines, table0, origin500. |
| invariants | Consumed6/12 and offsets500/506 distinguish operation flag from row values. |
| ownership | Local Case owns options/data and is moved into result; literal names/source strings retain their normal owned/static lifetimes. |
| failure | Ordinary construction/serialization can throw before the Case is returned; no session mutation. |
| cost | Bounded two-event encoding/copy plus vector insertion; actual parsing and checkpoint restore happen in callers. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

```text
Case timestamp_flags{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the legacy_timestamp_flags recovery/progress fixture. |
| inputs / outputs | 10,1,1,2 and 20,1,2,3 lines, table0. |
| invariants | Consumed9/18; source offsets10/20 retain timestamps verbatim, not byte positions. |
| ownership | Local Case owns options/data and is moved into result; literal names/source strings retain their normal owned/static lifetimes. |
| failure | Ordinary construction/serialization can throw before the Case is returned; no session mutation. |
| cost | Bounded two-event encoding/copy plus vector insertion; actual parsing and checkpoint restore happen in callers. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [tests/unit/session_journal_test.cpp](../../../../../tests/unit/session_journal_test.cpp), [tests/unit/generation_test.cpp](../../../../../tests/unit/generation_test.cpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 117–118](../../../../../tests/support/session_journal_stream_cases.hpp#L117); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L118:sha256:72bfd04bb7baba9b0ff010461e5f058668c191fa019e5ada4e351868fcb22239
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_journal_stream_cases.hpp: namespace crown::session_journal_stream_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/session_journal_stream_cases.hpp](../../../../../tests/support/session_journal_stream_cases.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |
