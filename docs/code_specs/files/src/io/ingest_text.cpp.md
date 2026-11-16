# `src/io/ingest_text.cpp` — block usage map

[Source](../../../../../src/io/ingest_text.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `a8f879022a9f3565749c0fcea4e80953ba3ef46d0fa0d7228c701ce483e396f1`. 55 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/io/ingest_text.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–11](../../../../../src/io/ingest_text.cpp#L9) | Callable definition: \[\[noreturn\]\] void invalid_document(const char* message) | calls Error · [reviewed contract](#b0002) |
| [B0003 · 12–12](../../../../../src/io/ingest_text.cpp#L12) | Explanatory comments or spacing. |  |
| [B0004 · 13–13](../../../../../src/io/ingest_text.cpp#L13) | Callable definition: bool continuation(unsigned char byte) | calls ; returns byte &gt;= 0x80U && byte &lt;= 0xbfU · [reviewed contract](#b0004) |
| [B0005 · 14–16](../../../../../src/io/ingest_text.cpp#L14) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 17–53](../../../../../src/io/ingest_text.cpp#L17) | Callable definition: void require_utf8(std::string_view text) | calls size, invalid_document, continuation; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 54–55](../../../../../src/io/ingest_text.cpp#L54) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io::ingest_detail · [reviewed contract](#b0007) |

## B0001

[Lines 1–8](../../../../../src/io/ingest_text.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:d7b6709e98ea65839a5242fccedef8c8e32bdf33cad19204309d22ef8e6c0a83
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (ingest_text.hpp, crown/api/error.hpp, cstddef) and opens crown::io::ingest_detail scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_specs/files/src/io/ingest_text.cpp.md](ingest_text.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0002

[Lines 9–11](../../../../../src/io/ingest_text.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void invalid_document(const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise the text helper's exact invalid_document rejection category. |
| inputs / outputs | Always throws Error(invalid_document,message) with the supplied static diagnostic text. |
| invariants | It neither rolls back a read callback nor marks an EventReader failed; caller/active reader owns poison/retry/acknowledgement semantics. |
| ownership | Error owns copied diagnostic text; no input pointer is retained. |
| failure | Always throws; diagnostic or exception allocation can itself fail. No handler or retry is hidden. |
| cost | Only failure/diagnostic construction; this unchanged helper remains live through require_utf8. |
| Design | [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [src/io/ingest_text.hpp](../../../../../src/io/ingest_text.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 13–13](../../../../../src/io/ingest_text.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool continuation(unsigned char byte) { return byte >= 0x80U && byte <= 0xbfU; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize one UTF-8 continuation-byte range. |
| inputs / outputs | Returns true exactly for unsigned byte 0x80..0xbf. |
| invariants | Caller supplies unsigned bytes; this predicate does not validate sequence width, scalar range or text lifetime by itself. |
| ownership | Only inline byte/result values are used. |
| failure | No throwing operation or exception translation. |
| cost | Two bounded integer comparisons; no allocation or text scan. |
| Design | [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [src/io/ingest_text.hpp](../../../../../src/io/ingest_text.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 14–16](../../../../../src/io/ingest_text.cpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L16:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_specs/files/src/io/ingest_text.cpp.md](ingest_text.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0006

[Lines 17–53](../../../../../src/io/ingest_text.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require_utf8(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate complete UTF-8 scalar encoding without normalizing accepted bytes. |
| inputs / outputs | Scans ASCII or valid 2/3/4-byte sequences, rejecting invalid starts/continuations, truncation, overlong forms, surrogates and code points above U+10FFFF. |
| invariants | ASCII control/NUL bytes remain valid string data; caller separately restricts source identifiers/field/domain/byte limits. This shared helper remains live in native decoding, readers, progress checks and diagnostic/input writers. |
| ownership | Borrows stable string_view; stores or transforms no bytes. |
| failure | Malformed encoding raises invalid_document through the narrow helper. It does not catch, poison a reader or choose a retry policy. |
| cost | Linear byte scan with bounded per-codepoint work and no successful heap allocation. It is preserved token-for-token in the separate unused-parser deletion proposal. |
| Design | [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [src/io/ingest_text.hpp](../../../../../src/io/ingest_text.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 54–55](../../../../../src/io/ingest_text.cpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L55:sha256:e0786388b01f95a95bc2851f51f6b67a09c6e412701190bb1d8cc526c8da34d8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io::ingest_detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_specs/files/src/io/ingest_text.cpp.md](ingest_text.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
