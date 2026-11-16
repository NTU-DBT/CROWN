# `include/crown/io/ingest.hpp` — block usage map

[Source](../../../../../../include/crown/io/ingest.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `d6838201c02d61cf736915cdd0104d9499ac200b590312ad6ab28e3b0833ca81`. 150 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../../include/crown/io/ingest.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 19–23](../../../../../../include/crown/io/ingest.hpp#L19) | Type/record definition: struct SourcePosition |  · [reviewed contract](#b0002) |
| [B0003 · 24–27](../../../../../../include/crown/io/ingest.hpp#L24) | Type/record definition: struct InputEvent |  · [reviewed contract](#b0003) |
| [B0004 · 28–32](../../../../../../include/crown/io/ingest.hpp#L28) | Type/record definition: struct InputProgress |  · [reviewed contract](#b0004) |
| [B0005 · 33–46](../../../../../../include/crown/io/ingest.hpp#L33) | Type/record definition: struct InputLimits | source comment (unverified): // JSON object bytes (LF/CRLF framing excluded), complete binary frame, or · [reviewed contract](#b0005) |
| [B0006 · 47–47](../../../../../../include/crown/io/ingest.hpp#L47) | Type/record definition: enum class InputFormat |  · [reviewed contract](#b0006) |
| [B0007 · 48–68](../../../../../../include/crown/io/ingest.hpp#L48) | Type/record definition: struct InputOptions | growth insert; source comment (unverified): // CSV and single-relation legacy profiles need an explicit physical table. · [reviewed contract](#b0007) |
| [B0008 · 69–89](../../../../../../include/crown/io/ingest.hpp#L69) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Full canonical catalog binding, including source schema versions/policies. · [reviewed contract](#b0008) |
| [B0009 · 90–94](../../../../../../include/crown/io/ingest.hpp#L90) | Type/record definition: struct ReaderPositionView | source comment (unverified): // Decoder continuation after the most recently decoded record, including a · [reviewed contract](#b0009) |
| [B0010 · 95–130](../../../../../../include/crown/io/ingest.hpp#L95) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Borrows the input stream; retains the supplied catalog owner, one bounded decoded record and · [reviewed contract](#b0010) |
| [B0011 · 131–150](../../../../../../include/crown/io/ingest.hpp#L131) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Fully decoded records, including a peeked record not yet acknowledged. · [reviewed contract](#b0011) |

## B0001

[Lines 1–18](../../../../../../include/crown/io/ingest.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io ingest public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0002

[Lines 19–23](../../../../../../include/crown/io/ingest.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourcePosition {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one upstream source name and offset. |
| inputs / outputs | Ordinary text identifier and uint64 offset, compared by value. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::string source;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The owning upstream identifier; source validation separately requires bounded nonempty UTF8 without NUL. |
| inputs / outputs | Stores/exposes the owning upstream identifier; source validation separately requires bounded nonempty UTF8 without NUL. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::uint64_t offset;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The upstream offset whose strict increase is enforced by the source owner. |
| inputs / outputs | Stores/exposes the upstream offset whose strict increase is enforced by the source owner. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
bool operator==(const SourcePosition&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exact source-name/offset value equality. |
| inputs / outputs | Stores/exposes exact source-name/offset value equality. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0003

[Lines 24–27](../../../../../../include/crown/io/ingest.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputEvent {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one external physical full-row set event. |
| inputs / outputs | PhysicalSetUpdate plus optional owning upstream position. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
PhysicalSetUpdate update;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The owning sequence/table/operation/full physical row. |
| inputs / outputs | Stores/exposes the owning sequence/table/operation/full physical row. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::optional<SourcePosition> source_position;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional ordinary owned upstream position. |
| inputs / outputs | Stores/exposes the optional ordinary owned upstream position. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0004

[Lines 28–32](../../../../../../include/crown/io/ingest.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputProgress {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an ordinary exported accepted prefix. |
| inputs / outputs | Accepted sequence and source-name/offset ordered map. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::uint64_t sequence=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The accepted source sequence, excluding pending decoded input. |
| inputs / outputs | Stores/exposes the accepted source sequence, excluding pending decoded input. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::map<std::string,std::uint64_t> source_positions;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The ordinary owning exported source-position map. |
| inputs / outputs | Stores/exposes the ordinary owning exported source-position map. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
bool operator==(const InputProgress&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exact accepted-prefix value equality, not stream/durable authority. |
| inputs / outputs | Stores/exposes exact accepted-prefix value equality, not stream/durable authority. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0005

[Lines 33–46](../../../../../../include/crown/io/ingest.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure independent wire-field and retained-source caps. |
| inputs / outputs | Record/field/column/source bounds and optional cumulative byte/decoded-record limits. |
| invariants | Per-record stateless codecs do not enforce cross-record continuity, retained source count or cumulative byte/record consumption; account limits remain separate. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::size_t record_bytes=1024*1024;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The JSON-object bytes, complete binary frame or raw delimited record limit; framing units differ by format. |
| inputs / outputs | Stores/exposes the JSON-object bytes, complete binary frame or raw delimited record limit; framing units differ by format. |
| invariants | Per-record stateless codecs do not enforce cross-record continuity, retained source count or cumulative byte/record consumption; account limits remain separate. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::size_t field_bytes=1024*1024;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The accepted text/date/decimal field length; JSON lexer token materialization may precede this narrower check. |
| inputs / outputs | Stores/exposes the accepted text/date/decimal field length; JSON lexer token materialization may precede this narrower check. |
| invariants | Per-record stateless codecs do not enforce cross-record continuity, retained source count or cumulative byte/record consumption; account limits remain separate. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::size_t columns=4096;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The per-row physical column-count limit. |
| inputs / outputs | Stores/exposes the per-row physical column-count limit. |
| invariants | Per-record stateless codecs do not enforce cross-record continuity, retained source count or cumulative byte/record consumption; account limits remain separate. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::size_t source_bytes=1024;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The source-name byte limit. |
| inputs / outputs | Stores/exposes the source-name byte limit. |
| invariants | Per-record stateless codecs do not enforce cross-record continuity, retained source count or cumulative byte/record consumption; account limits remain separate. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::size_t sources=1024;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The retained source-position count limit enforced by the stateful source owner. |
| inputs / outputs | Stores/exposes the retained source-position count limit enforced by the stateful source owner. |
| invariants | Per-record stateless codecs do not enforce cross-record continuity, retained source count or cumulative byte/record consumption; account limits remain separate. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::optional<std::uint64_t> total_bytes=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional cumulative reader byte-consumption limit; typed queues reject this wire limit. |
| inputs / outputs | Stores/exposes the optional cumulative reader byte-consumption limit; typed queues reject this wire limit. |
| invariants | Per-record stateless codecs do not enforce cross-record continuity, retained source count or cumulative byte/record consumption; account limits remain separate. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::optional<std::uint64_t> records=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional reader decoded-record cap, or typed queue accepted sequence cap. |
| inputs / outputs | Stores/exposes the optional reader decoded-record cap, or typed queue accepted sequence cap. |
| invariants | Per-record stateless codecs do not enforce cross-record continuity, retained source count or cumulative byte/record consumption; account limits remain separate. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
bool operator==(const InputLimits&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exact limit configuration value equality. |
| inputs / outputs | Stores/exposes exact limit configuration value equality. |
| invariants | Per-record stateless codecs do not enforce cross-record continuity, retained source count or cumulative byte/record consumption; account limits remain separate. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0006

[Lines 47–47](../../../../../../include/crown/io/ingest.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class InputFormat {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select one explicit physical transport profile. |
| inputs / outputs | JSONL, binary, CSV or named legacy signed/relation/insert/flag/timestamp profiles. |
| invariants | No profile inference or NULL guessing; EventReader validates compatible option combinations. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0007

[Lines 48–68](../../../../../../include/crown/io/ingest.hpp#L48); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own caller-supplied transport configuration. |
| inputs / outputs | Format/limits, physical table, delimiter/header/operation, legacy token map, null spelling, source ID and origin offset. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
InputFormat format=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The explicit transport profile. |
| inputs / outputs | Stores/exposes the explicit transport profile. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
InputLimits limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The separate source/record validation limits. |
| inputs / outputs | Stores/exposes the separate source/record validation limits. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::optional<TableId> table;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The required single physical table for CSV/single-relation profiles. |
| inputs / outputs | Stores/exposes the required single physical table for CSV/single-relation profiles. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
char delimiter=',';
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The one-byte ASCII delimiter, excluding quote/CR/LF/NUL. |
| inputs / outputs | Stores/exposes the one-byte ASCII delimiter, excluding quote/CR/LF/NUL. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
bool header=true;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | CSV header parsing/permutation; other profile combinations are validated separately. |
| inputs / outputs | Stores/exposes cSV header parsing/permutation; other profile combinations are validated separately. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
SetOperation csv_operation=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The fixed CSV insert/delete operation. |
| inputs / outputs | Stores/exposes the fixed CSV insert/delete operation. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::map<std::string,TableId> relation_tokens;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The exact external relation-token to physical table mapping. |
| inputs / outputs | Stores/exposes the exact external relation-token to physical table mapping. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::optional<std::string> null_token;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The explicit upstream null spelling to reject in the nonnull engine. |
| inputs / outputs | Stores/exposes the explicit upstream null spelling to reject in the nonnull engine. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::optional<std::string> source;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional source ID used for record origins or retained timestamp offsets. |
| inputs / outputs | Stores/exposes the optional source ID used for record origins or retained timestamp offsets. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::uint64_t byte_offset=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The explicit source byte-origin offset; timestamp profile rejects a nonzero byte origin. |
| inputs / outputs | Stores/exposes the explicit source byte-origin offset; timestamp profile rejects a nonzero byte origin. |
| invariants | The DTO does not validate itself. Format-specific tables/maps/header/source/null rules are checked by EventReader; no option declares query semantics or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0008

[Lines 69–89](../../../../../../include/crown/io/ingest.hpp#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
input_catalog_sha256(const Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the complete catalog/source schema binding digest. |
| inputs / outputs | Returns ordinary owning lowercase SHA256 of canonical catalog JSON bytes, including source versions/policies. |
| invariants | Byte spelling of an arbitrary source file and diagnostic flags are not catalog binding. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Catalog/encoding/allocation failures propagate; no source progress is changed. |
| cost | Full catalog canonical serialization plus hashing and ordinary string storage, even for a native-metadata Catalog view. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
validate_input_event(const InputEvent& event,const Catalog& catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one external physical event without serializing it. |
| inputs / outputs | Checks envelope/table/op/positive sequence, full row types/decimal domains, encoded field/payload bounds and UTF8/source-name rules. |
| invariants | Does not accept input or enforce cross-record contiguous sequence, source-offset monotonicity, source population, total bytes or record consumption. |
| ownership | Borrows event/catalog; Date/Decimal textual validation may allocate ordinary strings. |
| failure | Typed input/catalog/scalar/resource/encoding/allocation errors propagate. |
| cost | Full fields/deep text validation, decimal/date formatting and table checks; no native account/import work is hidden. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
read_input_json(std::string_view text,const Catalog& catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one independently framed physical json event. |
| inputs / outputs | Borrows the complete record, recomputes catalog fingerprint, checks strict version/envelope/binding and returns an ordinary owning InputEvent. |
| invariants | One-record API does not consume a stream or own acceptance state; limits and frame units are format-specific. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Malformed/version/binding/type/UTF8/resource/allocation errors return no completed event. |
| cost | Full catalog serialization/hash plus SAX JSON or binary record parse and ordinary row/string allocation; this is separate from the funded EventReader decoder. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
write_input_json(const InputEvent& event,const Catalog& catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one complete physical json record. |
| inputs / outputs | Validates external event and catalog binding, then returns a complete owning string under record_bytes. |
| invariants | No source acknowledgment, stream position or native publication; binary returns one version1 complete frame. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Validation/encoded-byte/UTF8/allocation failure returns no artifact. |
| cost | Catalog canonicalization/hash, event field/format validation and complete ordinary encoded output; capacity and temporary strings are separate from encoded length. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
read_input_binary(std::string_view bytes,const Catalog& catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one independently framed physical binary event. |
| inputs / outputs | Borrows the complete record, recomputes catalog fingerprint, checks strict version/envelope/binding and returns an ordinary owning InputEvent. |
| invariants | One-record API does not consume a stream or own acceptance state; limits and frame units are format-specific. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Malformed/version/binding/type/UTF8/resource/allocation errors return no completed event. |
| cost | Full catalog serialization/hash plus SAX JSON or binary record parse and ordinary row/string allocation; this is separate from the funded EventReader decoder. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
write_input_binary(const InputEvent& event,const Catalog& catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one complete physical binary record. |
| inputs / outputs | Validates external event and catalog binding, then returns a complete owning string under record_bytes. |
| invariants | No source acknowledgment, stream position or native publication; binary returns one version1 complete frame. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Validation/encoded-byte/UTF8/allocation failure returns no artifact. |
| cost | Catalog canonicalization/hash, event field/format validation and complete ordinary encoded output; capacity and temporary strings are separate from encoded length. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
input_catalog_sha256(const program::Catalog& catalog)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the complete catalog/source schema binding digest. |
| inputs / outputs | Returns ordinary owning lowercase SHA256 of canonical catalog JSON bytes, including source versions/policies. |
| invariants | Byte spelling of an arbitrary source file and diagnostic flags are not catalog binding. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Catalog/encoding/allocation failures propagate; no source progress is changed. |
| cost | Full catalog canonical serialization plus hashing and ordinary string storage, even for a native-metadata Catalog view. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
validate_input_event(const InputEvent& event,const program::Catalog& catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one external physical event without serializing it. |
| inputs / outputs | Checks envelope/table/op/positive sequence, full row types/decimal domains, encoded field/payload bounds and UTF8/source-name rules. |
| invariants | Does not accept input or enforce cross-record contiguous sequence, source-offset monotonicity, source population, total bytes or record consumption. |
| ownership | Borrows event/catalog; Date/Decimal textual validation may allocate ordinary strings. |
| failure | Typed input/catalog/scalar/resource/encoding/allocation errors propagate. |
| cost | Full fields/deep text validation, decimal/date formatting and table checks; no native account/import work is hidden. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
read_input_json(std::string_view text,const program::Catalog& catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one independently framed physical json event. |
| inputs / outputs | Borrows the complete record, recomputes catalog fingerprint, checks strict version/envelope/binding and returns an ordinary owning InputEvent. |
| invariants | One-record API does not consume a stream or own acceptance state; limits and frame units are format-specific. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Malformed/version/binding/type/UTF8/resource/allocation errors return no completed event. |
| cost | Full catalog serialization/hash plus SAX JSON or binary record parse and ordinary row/string allocation; this is separate from the funded EventReader decoder. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
write_input_json(const InputEvent& event,const program::Catalog& catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one complete physical json record. |
| inputs / outputs | Validates external event and catalog binding, then returns a complete owning string under record_bytes. |
| invariants | No source acknowledgment, stream position or native publication; binary returns one version1 complete frame. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Validation/encoded-byte/UTF8/allocation failure returns no artifact. |
| cost | Catalog canonicalization/hash, event field/format validation and complete ordinary encoded output; capacity and temporary strings are separate from encoded length. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
read_input_binary(std::string_view bytes,const program::Catalog& catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one independently framed physical binary event. |
| inputs / outputs | Borrows the complete record, recomputes catalog fingerprint, checks strict version/envelope/binding and returns an ordinary owning InputEvent. |
| invariants | One-record API does not consume a stream or own acceptance state; limits and frame units are format-specific. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Malformed/version/binding/type/UTF8/resource/allocation errors return no completed event. |
| cost | Full catalog serialization/hash plus SAX JSON or binary record parse and ordinary row/string allocation; this is separate from the funded EventReader decoder. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
write_input_binary(const InputEvent& event,const program::Catalog& catalog
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one complete physical binary record. |
| inputs / outputs | Validates external event and catalog binding, then returns a complete owning string under record_bytes. |
| invariants | No source acknowledgment, stream position or native publication; binary returns one version1 complete frame. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Validation/encoded-byte/UTF8/allocation failure returns no artifact. |
| cost | Catalog canonicalization/hash, event field/format validation and complete ordinary encoded output; capacity and temporary strings are separate from encoded length. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0009

[Lines 90–94](../../../../../../include/crown/io/ingest.hpp#L90); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReaderPositionView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the decoder continuation after its latest decoded record. |
| inputs / outputs | Decoded byte/record counters, CSV header flag and borrowed physical field permutation, including an unacknowledged cache. |
| invariants | Capturing this view allocates/accepts nothing and proves no durable source prefix. Mutation/release of decoder state can invalidate its borrow. |
| ownership | Fixed counters plus borrowed span; it retains no reader, stream, option or CSV vector owner. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::uint64_t bytes=0,records=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The decoded continuation byte/record counters, independent of accepted input progress. |
| inputs / outputs | Stores/exposes the decoded continuation byte/record counters, independent of accepted input progress. |
| invariants | Capturing this view allocates/accepts nothing and proves no durable source prefix. Mutation/release of decoder state can invalidate its borrow. |
| ownership | Fixed counters plus borrowed span; it retains no reader, stream, option or CSV vector owner. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
bool header_read=false;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The current CSV header-read continuation flag. |
| inputs / outputs | Stores/exposes the current CSV header-read continuation flag. |
| invariants | Capturing this view allocates/accepts nothing and proves no durable source prefix. Mutation/release of decoder state can invalidate its borrow. |
| ownership | Fixed counters plus borrowed span; it retains no reader, stream, option or CSV vector owner. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::span<const std::size_t> csv_fields;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The borrowed CSV field permutation, guaranteed only within the reader continuation lifetime contract. |
| inputs / outputs | Stores/exposes the borrowed CSV field permutation, guaranteed only within the reader continuation lifetime contract. |
| invariants | Capturing this view allocates/accepts nothing and proves no durable source prefix. Mutation/release of decoder state can invalidate its borrow. |
| ownership | Fixed counters plus borrowed span; it retains no reader, stream, option or CSV vector owner. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0010

[Lines 95–130](../../../../../../include/crown/io/ingest.hpp#L95); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class EventReader
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one bounded ordered physical source with explicit acceptance. |
| inputs / outputs | Caches a complete native event and preallocated source-position update; acknowledge alone advances accepted progress. |
| invariants | Decoder position/counts include unacknowledged input. Engine rejection retries the existing complete cache; decoder failure may have consumed bytes and poisons this reader. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Exceptions during read/decode/order/cache preparation set broken and rethrow; close discards unaccepted cache. Public construction/checkpoint failures publish no usable reader. |
| cost | Reads/scans actual bytes, validates shape/source/domain, funds compact row/text/cache and positions; no hidden external DTO mirror. Native receiving-account cap is separate from wire caps. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
EventReader(std::istream& input,CatalogSource catalog,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, validate or checkpoint an EventReader. |
| inputs / outputs | Construct a standalone reader from owned schema, ordinary options and initial accepted progress. |
| invariants | Uses its own UINT64_MAX account, validates catalog/options and borrows the caller stream; execution should use the admitted-program constructor. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Option/catalog/checkpoint/binding/limit/allocation errors propagate before a usable result; no implicit input acceptance. |
| cost | Account/Data creation, native option/text/map import, accepted-position cloning and complete canonical catalog fingerprint. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
EventReader(std::istream& input,const CompiledProgram&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, validate or checkpoint an EventReader. |
| inputs / outputs | Construct an execution reader from actual admitted program account/catalog plus ordinary option/progress DTOs. |
| invariants | Derives the existing original receiving account; no replacement query grant or compiler DTO retention. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Option/catalog/checkpoint/binding/limit/allocation errors propagate before a usable result; no implicit input acceptance. |
| cost | Funded reader/options/progress construction and fingerprint generation; by-value ordinary input copies may occur before the call. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
static EventReader with_options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, validate or checkpoint an EventReader. |
| inputs / outputs | Construct from native immutable options on the actual program account. |
| invariants | Rejects absent/foreign option account; shares those native values rather than exporting/reconstructing an ordinary options shadow. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Option/catalog/checkpoint/binding/limit/allocation errors propagate before a usable result; no implicit input acceptance. |
| cost | Fixed account-owner check, funded Data/progress import and catalog fingerprint; option handle sharing avoids text/map clone. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
static EventReader restore_state(std::istream&,const CompiledProgram&,const ReaderCheckpoint&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, validate or checkpoint an EventReader. |
| inputs / outputs | Restore a decoder continuation with default source-state limits. |
| invariants | Supplied stream begins at the next unread byte; counters/CSV permutation retain original decoder origin. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Option/catalog/checkpoint/binding/limit/allocation errors propagate before a usable result; no implicit input acceptance. |
| cost | Delegates to explicit bounded restore, including account imports and state checks. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
static EventReader restore_state(std::istream&,const CompiledProgram&,const ReaderCheckpoint&,const SourceStateLimits&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, validate or checkpoint an EventReader. |
| inputs / outputs | Restore source state under explicit bounded preparation. |
| invariants | Revalidates format/options, positions, catalog hash, byte/record bounds and CSV permutation; does not seek/verify the stream prefix itself or accept pending input. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Option/catalog/checkpoint/binding/limit/allocation errors propagate before a usable result; no implicit input acceptance. |
| cost | Native options/text/map cloning, fingerprint work, CSV vector allocation and O(fields²) uniqueness comparisons within selected source work. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
static void validate_checkpoint_options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, validate or checkpoint an EventReader. |
| inputs / outputs | Check native source options/progress against the program source schema. |
| invariants | This checks format/source/table/limit compatibility, not a complete checkpoint, stream prefix or durable root. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Option/catalog/checkpoint/binding/limit/allocation errors propagate before a usable result; no implicit input acceptance. |
| cost | Catalog/profile/position/token-map scans and source text validation; no decoder construction or stream read. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
ReaderCheckpoint checkpoint_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, validate or checkpoint an EventReader. |
| inputs / outputs | Capture the reader source component using default source-state limits. |
| invariants | Requires live Data with no cached unacknowledged record and no broken decoder. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Option/catalog/checkpoint/binding/limit/allocation errors propagate before a usable result; no implicit input acceptance. |
| cost | Delegates to bounded source component capture. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
ReaderCheckpoint checkpoint_state(const SourceStateLimits&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, validate or checkpoint an EventReader. |
| inputs / outputs | Capture owned source component state under explicit work/count caps. |
| invariants | Returned editable native snapshot retains options and clones accepted positions/CSV fields; session quiescence and durable authority are established elsewhere. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Option/catalog/checkpoint/binding/limit/allocation errors propagate before a usable result; no implicit input acceptance. |
| cost | Position/options/CSV scans, funded progress/vector copies and fixed fingerprint copy; no stream I/O or source acknowledgment. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
~EventReader();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release native decoder ownership without destroying its borrowed stream. |
| inputs / outputs | Drops cache/options/positions/CSV state and retained catalog. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Actual row/text/map/options/schema graph release; no recursive stream ownership. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
EventReader(const EventReader&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject implicit reader copying. |
| inputs / outputs | One mutable decoder/acceptance owner per reader. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Compile-time restriction. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
EventReader& operator=(const EventReader&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject reader copy assignment. |
| inputs / outputs | No duplicate mutable cursor/progress owner. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Compile-time restriction. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
EventReader(EventReader&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the funded decoder owner. |
| inputs / outputs | Moves Data handle and preserves the borrowed stream association. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Fixed descriptor transfer, no source row/position clone. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
EventReader& operator=(EventReader&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace and transfer reader ownership. |
| inputs / outputs | Destroys prior decoder Data before taking the replacement. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Transfer plus actual old cache/map/options/catalog release, no new allocation. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
bool failed() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read sticky decoder failure. |
| inputs / outputs | Absent Data returns false. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Fixed flag read. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
AccountedInputProgress close() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move accepted progress out and discard pending decoder ownership. |
| inputs / outputs | Does not acknowledge cache, read/destroy stream or accept more input; repeated close returns empty progress. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | No new allocation; release cache/options/CSV/catalog state with actual owned graph costs. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
const AccountedInputProgress& progress() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow accepted source progress. |
| inputs / outputs | Pending cached event is excluded; explicit progress copies clone Data, map nodes and nonempty key character blocks/bytes. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Fixed live-owner check/reference. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
const CatalogSource& catalog() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained source catalog owner. |
| inputs / outputs | No catalog export or revalidation at this getter. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Fixed live-owner check/reference. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::string_view catalog_sha256() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained complete catalog fingerprint. |
| inputs / outputs | Returns the already stored digest view, not a new digest or proof. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Fixed live-owner check/view. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
const InputEventView* peek();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read/decode and cache one complete physical input event. |
| inputs / outputs | Cached peek returns the same owned native view; ended returns nullptr. New decode prepares contiguous sequence/source acceptance before caching. |
| invariants | No source acceptance before acknowledge. A failed decoder may already have consumed stream bytes, so every exception inside decode/preparation marks broken. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | I/O, syntax, UTF8, source/domain, record/byte cap, native allocation or ordering errors poison and rethrow; engine rejection happens outside this method and can reuse a complete cache. |
| cost | Actual wire read/parse/validation plus compact row/source allocation and possible position-node preparation; cached/ended paths are fixed metadata access. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
void acknowledge() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish an already prepared physical source acceptance. |
| inputs / outputs | Links/updates prepared source position, advances accepted sequence and releases the cache; absent cache is an idempotent no-op. |
| invariants | No input read, callbacks or allocating bookkeeping after engine publication. Decoder counters already advanced at decode. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | No throwing operation under valid owner protocol; no recovery/retry is attempted here. |
| cost | Prepared map link or scalar update plus actual cached row/source release; no new allocation. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0011

[Lines 131–150](../../../../../../include/crown/io/ingest.hpp#L131); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t bytes_read() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read consumed decoder bytes. |
| inputs / outputs | Includes framing/header/consumed bytes, independently of accepted sequence. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Fixed live-owner check/counter read. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::uint64_t records_read() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read fully decoded record count. |
| inputs / outputs | Includes the current complete cached but unacknowledged record. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Fixed live-owner check/counter read. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
ReaderPositionView decoder_position() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the latest decoder continuation. |
| inputs / outputs | Returns counters/header flag and nonretaining CSV permutation span. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Fixed descriptor view; no stream read, allocation or acceptance. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
ReaderPositionView decoder_position() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject immediate continuation borrowing from a temporary reader. |
| inputs / outputs | Compile-time rvalue-borrow restriction. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | No runtime action. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
const AccountedInputOptions& native_options() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow retained native options. |
| inputs / outputs | Returns immutable options owner by reference; no ordinary export. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Fixed live-owner check/reference. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
const AccountedInputOptions& native_options() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject immediate options borrowing from a temporary reader. |
| inputs / outputs | Compile-time rvalue-borrow restriction. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | No runtime action. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
const resource::MemoryAccount& account() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the reader original allocation account. |
| inputs / outputs | Returns its actual account, not a new allowance. |
| invariants | Accepted source state changes only through valid acknowledge; borrowed outputs require live backing. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Deleted functions fail compilation; noexcept operations do not throw. Other accessors reject closed/moved-from readers with invalid_input_reader. |
| cost | Fixed live-owner check/reference. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
bool matches_catalog(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare this reader full schema binding to the actual program. |
| inputs / outputs | Rebuilds native canonical catalog fingerprint from the program and compares it with the stored reader fingerprint. |
| invariants | Equality checks complete catalog binding, not owner identity, source position, stream prefix or minimum proof. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Program/catalog/native allocation/encoding failures propagate; no source input is consumed. |
| cost | Full catalog canonical encoding/hash and native temporary/fingerprint allocation, then fixed-length comparison; not an O(1) cached-ID check. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
friend class runtime::QuerySession;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow the session coordinator to stage verified recovery input. |
| inputs / outputs | Friend accesses private source recovery preparation. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Compile-time access only. |
| failure | No runtime failure. |
| cost | No runtime overhead. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::uint64_t stage_replay(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild a verified pending reader cache without rereading the stream. |
| inputs / outputs | Validates sequence/decoder positions/options/CSV and source bindings, prepares owned row/text/CSV state, then publishes by nonthrowing moves. |
| invariants | Does not acknowledge accepted progress. Supplied continuation is already positioned by the external recovery protocol; copied views alone provide no recovery authority. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Image/native/limit/binding/allocation errors propagate during private preparation; order preparation completes before cache/counter publication. |
| cost | Bounded source/text checks, O(fields²) CSV uniqueness checks, compact row/source copies and a new funded CSV vector; selected returned work excludes total CPU/I/O. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
EventReader(const resource::MemoryAccount&,std::istream&,CatalogSource,InputOptions,InputProgress,bool admitted);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the closed account/catalog reader-construction bridge. |
| inputs / outputs | Takes actual memory/schema authority plus ordinary options, retained native options or explicit source checkpoint. |
| invariants | Only admitted-program/session factories bypass redundant catalog validation; borrowed stream is never owned by this reader. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Validation/limits/binding/allocation failures unwind private construction. |
| cost | The selected constructor native Data/options/progress/fingerprint and restore-validation costs; no replacement query account. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
EventReader(const resource::MemoryAccount&,std::istream&,CatalogSource,const AccountedInputOptions&,InputProgress,bool admitted);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the closed account/catalog reader-construction bridge. |
| inputs / outputs | Takes actual memory/schema authority plus ordinary options, retained native options or explicit source checkpoint. |
| invariants | Only admitted-program/session factories bypass redundant catalog validation; borrowed stream is never owned by this reader. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Validation/limits/binding/allocation failures unwind private construction. |
| cost | The selected constructor native Data/options/progress/fingerprint and restore-validation costs; no replacement query account. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
EventReader(const resource::MemoryAccount&,std::istream&,CatalogSource,const ReaderCheckpoint&,const SourceStateLimits&,bool admitted);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the closed account/catalog reader-construction bridge. |
| inputs / outputs | Takes actual memory/schema authority plus ordinary options, retained native options or explicit source checkpoint. |
| invariants | Only admitted-program/session factories bypass redundant catalog validation; borrowed stream is never owned by this reader. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Validation/limits/binding/allocation failures unwind private construction. |
| cost | The selected constructor native Data/options/progress/fingerprint and restore-validation costs; no replacement query account. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
static void validate_options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply format-specific source option/progress validation. |
| inputs / outputs | Reads CatalogSource and native options/progress using the same Data initializer rules as construction. |
| invariants | Checks explicit profile compatibility and source limits; no reader, byte-prefix or durable authority is minted. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Typed invalid options/source/UTF8/resource errors propagate. |
| cost | Scans relevant schema, token map and source names; no stream read. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
struct Data;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide funded mutable decoder state. |
| inputs / outputs | Opaque Data holds borrowed stream, retained schema/options/progress, native cache/CSV and counters. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Declaration creates no failure handler. |
| cost | No runtime action. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
resource::AccountedUnique<Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the native reader control graph. |
| inputs / outputs | One funded Data descriptor; null represents closed/moved-from. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | EventReader uniquely owns funded decoder/options/progress/cache state and retains CatalogSource. It only borrows the stream, which must survive every read. Returned pointers/references/spans retain no reader or stream. |
| failure | Descriptor transfer is nonthrowing; actual Data preparation has the documented failures. |
| cost | Fixed descriptor storage; final cache/map/options/catalog release has actual graph cost. |
| Design | [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/ingest.cpp](../../../../../../src/io/ingest.cpp), [src/io/ingest_program.cpp](../../../../../../src/io/ingest_program.cpp), [docs/ingestion.md](../../../../../ingestion.md) |
