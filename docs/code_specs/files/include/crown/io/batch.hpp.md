# `include/crown/io/batch.hpp` — block usage map

[Source](../../../../../../include/crown/io/batch.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `51b38f56d3c97ce04121b0750f554ffa68a18d202a8ba80c14a40196fe71226b`. 105 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../../include/crown/io/batch.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Event time is an adapter uint64 domain, independent of SQL scalar types and · [reviewed contract](#b0001) |
| [B0002 · 15–20](../../../../../../include/crown/io/batch.hpp#L15) | Type/record definition: struct WindowInsert | source comment (unverified): // Event time is an adapter uint64 domain, independent of SQL scalar types and · [reviewed contract](#b0002) |
| [B0003 · 21–25](../../../../../../include/crown/io/batch.hpp#L21) | Type/record definition: struct WindowCommand |  · [reviewed contract](#b0003) |
| [B0004 · 26–26](../../../../../../include/crown/io/batch.hpp#L26) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 27–30](../../../../../../include/crown/io/batch.hpp#L27) | Type/record definition: struct BatchLimits |  · [reviewed contract](#b0005) |
| [B0006 · 31–36](../../../../../../include/crown/io/batch.hpp#L31) | Type/record definition: struct QueueLimits |  · [reviewed contract](#b0006) |
| [B0007 · 37–37](../../../../../../include/crown/io/batch.hpp#L37) | Type/record definition: enum class Admission |  · [reviewed contract](#b0007) |
| [B0008 · 38–38](../../../../../../include/crown/io/batch.hpp#L38) | Type/record definition: enum class QueueMode |  · [reviewed contract](#b0008) |
| [B0009 · 39–40](../../../../../../include/crown/io/batch.hpp#L39) | Explanatory comments or spacing. | source comment (unverified): // Counts cover the retained queued graph; schema/options, accepted positions · [reviewed contract](#b0009) |
| [B0010 · 41–45](../../../../../../include/crown/io/batch.hpp#L41) | Type/record definition: struct QueueStats | source comment (unverified): // Counts cover the retained queued graph; schema/options, accepted positions · [reviewed contract](#b0010) |
| [B0011 · 46–49](../../../../../../include/crown/io/batch.hpp#L46) | Explanatory comments or spacing. | source comment (unverified): // A transport batch preserves every event barrier. No cancellation/coalescing. · [reviewed contract](#b0011) |
| [B0012 · 50–65](../../../../../../include/crown/io/batch.hpp#L50) | Type/record definition: class TransportBatch | source comment (unverified): // A transport batch preserves every event barrier. No cancellation/coalescing. · [reviewed contract](#b0012) |
| [B0013 · 66–101](../../../../../../include/crown/io/batch.hpp#L66) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Closed implementation-owned source for QuerySession. The head remains owned · [reviewed contract](#b0013) |
| [B0014 · 102–105](../../../../../../include/crown/io/batch.hpp#L102) | declares types or opens a type body. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0014) |

## B0001

[Lines 1–14](../../../../../../include/crown/io/batch.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io batch public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0002

[Lines 15–20](../../../../../../include/crown/io/batch.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowInsert {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one external operational-window insertion. |
| inputs / outputs | Label, physical table, ordinary Row and event-time uint64 timestamp; no SQL timestamp scalar conversion. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::uint64_t label;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The session-lifetime insertion label. |
| inputs / outputs | Stores/exposes the session-lifetime insertion label. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TableId table;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The physical source table ID. |
| inputs / outputs | Stores/exposes the physical source table ID. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
Row values;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The owning full physical input row. |
| inputs / outputs | Stores/exposes the owning full physical input row. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::uint64_t timestamp;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The adapter event-time value, independent of source offset and SQL types. |
| inputs / outputs | Stores/exposes the adapter event-time value, independent of source offset and SQL types. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0003

[Lines 21–25](../../../../../../include/crown/io/batch.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowCommand {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one ordered window command and optional upstream position. |
| inputs / outputs | Command sequence, insert/withdraw/watermark variant and optional owning SourcePosition. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::uint64_t sequence;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The command sequence checked by the source owner. |
| inputs / outputs | Stores/exposes the command sequence checked by the source owner. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::variant<WindowInsert,WindowWithdraw,AdvanceWatermark> command;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The exact window command payload; no cancellation or coalescing. |
| inputs / outputs | Stores/exposes the exact window command payload; no cancellation or coalescing. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::optional<SourcePosition> source_position;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional owning upstream name/offset, distinct from event time. |
| inputs / outputs | Stores/exposes the optional owning upstream name/offset, distinct from event time. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Explicit ordinary container/text ownership and deep-copy costs; field declarations add no execution or validation pass. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0004

[Lines 26–26](../../../../../../include/crown/io/batch.hpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using InputItem=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the ordered external physical/window input union. |
| inputs / outputs | InputEvent or WindowCommand, with ordinary owning row/text data. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Malformed or mode-incompatible alternatives are diagnosed at batch/head validation. |
| cost | Variant dispatch plus the actual active ordinary payload copy/destruction cost. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0005

[Lines 27–30](../../../../../../include/crown/io/batch.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BatchLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound one ordinary transport batch capacity model. |
| inputs / outputs | Maximum item count and modeled retained DTO bytes; default 65,536 items / 64 MiB. |
| invariants | This model excludes constructor input overlap, allocation framing and temporary allocations; it is not a process or query account cap. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::size_t events=65536;
  std::size_t bytes=64*1024*1024;
};

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The maximum external batch item count. |
| inputs / outputs | Stores/exposes the maximum external batch item count. |
| invariants | This model excludes constructor input overlap, allocation framing and temporary allocations; it is not a process or query account cap. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::size_t bytes=64*1024*1024;
};

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The DTO list/Value/string-capacity/Decimal byte-model limit. |
| inputs / outputs | Stores/exposes the DTO list/Value/string-capacity/Decimal byte-model limit. |
| invariants | This model excludes constructor input overlap, allocation framing and temporary allocations; it is not a process or query account cap. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0006

[Lines 31–36](../../../../../../include/crown/io/batch.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QueueLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound retained native queued batches and items. |
| inputs / outputs | Batches, events and retained queued allocation requests; enforced independently of the original account limit. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::size_t batches=64;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The maximum retained native batch count. |
| inputs / outputs | Stores/exposes the maximum retained native batch count. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::size_t events=65536;
  std::size_t bytes=64*1024*1024;
  bool operator==(const QueueLimits&) const=default;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The maximum retained unacknowledged item count. |
| inputs / outputs | Stores/exposes the maximum retained unacknowledged item count. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::size_t bytes=64*1024*1024;
  bool operator==(const QueueLimits&) const=default;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The queued batch/item/row/source allocation-request cap. |
| inputs / outputs | Stores/exposes the queued batch/item/row/source allocation-request cap. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
bool operator==(const QueueLimits&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Value equality of queue-cap configuration, not source identity. |
| inputs / outputs | Stores/exposes value equality of queue-cap configuration, not source identity. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0007

[Lines 37–37](../../../../../../include/crown/io/batch.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Admission {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether the offered batch was admitted. |
| inputs / outputs | accepted imports native ownership and empties the caller; full preserves it for retry. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0008

[Lines 38–38](../../../../../../include/crown/io/batch.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class QueueMode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select physical-set versus operational-window source input. |
| inputs / outputs | Mode is validated at construction and matched to each owned head. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0009

[Lines 39–40](../../../../../../include/crown/io/batch.hpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L40:sha256:c1c8d50652e1f42772c3348e5210b7ac1db4372ba422f5c39067e6e5d7e9f5ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Counts cover the retained queued graph; schema/options, accepted positions and account control have separate original-account ownership. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/io/batch.hpp lines 37-42; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [docs/code_specs/files/include/crown/io/batch.hpp.md](batch.hpp.md), [docs/ingestion.md](../../../../../ingestion.md), [docs/session_lifecycle.md](../../../../../session_lifecycle.md) |

## B0010

[Lines 41–45](../../../../../../include/crown/io/batch.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QueueStats {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read retained queue counts and lifecycle flags. |
| inputs / outputs | Batch/item/queued-request counts plus finished/semantic-failed flags. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::size_t batches=0,events=0,accounted_bytes=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The currently retained queued graph counts/requests, excluding separate schema/options/progress/control ownership. |
| inputs / outputs | Stores/exposes the currently retained queued graph counts/requests, excluding separate schema/options/progress/control ownership. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
bool closed=false,failed=false;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finished-admission and sticky semantic-head failure flags; closed may still have drainable items. |
| inputs / outputs | Stores/exposes finished-admission and sticky semantic-head failure flags; closed may still have drainable items. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
bool operator==(const QueueStats&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exact descriptive queue-statistics value equality. |
| inputs / outputs | Stores/exposes exact descriptive queue-statistics value equality. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0011

[Lines 46–49](../../../../../../include/crown/io/batch.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L49:sha256:27715d8635f8622435896adaefe76114811536009f79802416a26557366e11a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: A transport batch preserves every event barrier. No cancellation/coalescing. Bounds owned list nodes, Value slots, string capacities and Decimal allowance; allocator metadata, constructor input, and temporary allocations are separate. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/io/batch.hpp lines 44-51; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [docs/code_specs/files/include/crown/io/batch.hpp.md](batch.hpp.md), [docs/ingestion.md](../../../../../ingestion.md), [docs/session_lifecycle.md](../../../../../session_lifecycle.md) |

## B0012

[Lines 50–65](../../../../../../include/crown/io/batch.hpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class TransportBatch
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an external ordered transport batch before native import. |
| inputs / outputs | By-value vector input becomes a private ordinary list; every event barrier is preserved. |
| invariants | It is ordered transport, not an atomic net transaction; no cancellation/coalescing or source acceptance. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Limit/invalid-variant/allocation failure publishes no constructed batch; by-value input preparation is caller/tool ownership. |
| cost | Two payload/capacity-model passes and ordinary list nodes; constructor input, allocated Data and preparation can overlap. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
explicit TransportBatch(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a bounded external batch. |
| inputs / outputs | Checks item limit, then Data/model bytes before moving items into list nodes; empty input creates no Data. |
| invariants | Only its declared capacity model is capped; no native account or input semantics are admitted. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | resource_limit, invalid_input_kind or ordinary allocation failure unwinds private construction. |
| cost | Linear items/fields/string-capacity inspection, then one list node per item; existing by-value input storage is separate. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
~TransportBatch();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release all external batch data. |
| inputs / outputs | Operate on the batch owner or its stored metadata. |
| invariants | A moved-from/empty batch has no Data and observes empty/zero; copies remain forbidden. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Deleted functions fail compilation; declared noexcept operations do not throw. |
| cost | Destroys the list, ordinary Rows/Values/strings and Data; proportional to owned elements, not just a handle reset. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TransportBatch(const TransportBatch&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject implicit deep copying of external batches. |
| inputs / outputs | Operate on the batch owner or its stored metadata. |
| invariants | A moved-from/empty batch has no Data and observes empty/zero; copies remain forbidden. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Deleted functions fail compilation; declared noexcept operations do not throw. |
| cost | Compile-time restriction only. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TransportBatch& operator=(const TransportBatch&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject external batch copy assignment. |
| inputs / outputs | Operate on the batch owner or its stored metadata. |
| invariants | A moved-from/empty batch has no Data and observes empty/zero; copies remain forbidden. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Deleted functions fail compilation; declared noexcept operations do not throw. |
| cost | Compile-time restriction only. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TransportBatch(TransportBatch&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the external batch owner. |
| inputs / outputs | Operate on the batch owner or its stored metadata. |
| invariants | A moved-from/empty batch has no Data and observes empty/zero; copies remain forbidden. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Deleted functions fail compilation; declared noexcept operations do not throw. |
| cost | Fixed unique-owner transfer, no payload clone. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TransportBatch& operator=(TransportBatch&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace/transfer the external batch owner. |
| inputs / outputs | Operate on the batch owner or its stored metadata. |
| invariants | A moved-from/empty batch has no Data and observes empty/zero; copies remain forbidden. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Deleted functions fail compilation; declared noexcept operations do not throw. |
| cost | Handle transfer plus destruction of any previous owned list/payload; no new allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
bool empty() const noexcept;
  [[nodiscard]] std::size_t size() const noexcept;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether any external items remain. |
| inputs / outputs | Operate on the batch owner or its stored metadata. |
| invariants | A moved-from/empty batch has no Data and observes empty/zero; copies remain forbidden. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Deleted functions fail compilation; declared noexcept operations do not throw. |
| cost | Fixed pointer/list-empty check. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::size_t size() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read remaining external item count. |
| inputs / outputs | Operate on the batch owner or its stored metadata. |
| invariants | A moved-from/empty batch has no Data and observes empty/zero; copies remain forbidden. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Deleted functions fail compilation; declared noexcept operations do not throw. |
| cost | Fixed pointer/list-size read. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::size_t accounted_bytes() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the stored external DTO byte model. |
| inputs / outputs | Operate on the batch owner or its stored metadata. |
| invariants | A moved-from/empty batch has no Data and observes empty/zero; copies remain forbidden. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Deleted functions fail compilation; declared noexcept operations do not throw. |
| cost | Fixed count read; not native account statistics. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
struct Data;
  std::unique_ptr<Data> data_;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide ordinary batch list/storage implementation. |
| inputs / outputs | Opaque Data is uniquely owned by data_; TypedQueue is the sole friend importer. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Declaration adds no handler or resource. |
| cost | No runtime action at declaration. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::unique_ptr<Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the sole ordinary batch graph owner. |
| inputs / outputs | Null represents empty/moved-from; importing consumes this owner after successful native publication. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Ordinary caller-owned value; Rows/strings/vectors/maps own their storage and can allocate when constructed or copied. No native account authority is created. |
| failure | Private graph construction can fail before publication. |
| cost | One unique descriptor; graph destruction retains its actual list/payload costs. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
friend class TypedQueue;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow only TypedQueue to consume external batch internals. |
| inputs / outputs | Friend importer reads source items and clears Data only after complete native preparation. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Compile-time access relationship, not a new runtime owner. |
| failure | No runtime failure. |
| cost | No runtime overhead. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
class TypedQueue;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a closed-world, ordered native input source. |
| inputs / outputs | Imports an offered DTO into funded batch/item/row/source ownership, then validates/acknowledges one head at a time. |
| invariants | Membership/accepted progress are unchanged on failed/full enqueue; account history can record private failed allocations. Finish blocks enqueue while allowing existing heads to drain. |
| ownership | Data, batches/items, compact rows/source text and accepted positions use its original MemoryAccount; schema is retained CatalogSource. |
| failure | Semantic head Error is sticky. Native MemoryFailure/bad_alloc and engine rejection preserve retry of the already-owned head. Explicit close discards pending input without acceptance. |
| cost | Enqueue scans/preflights then allocates/imports all offered items before publication; peek validates one head and may prepare a position node; acknowledgment performs no new allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0013

[Lines 66–101](../../../../../../include/crown/io/batch.hpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TypedQueue(CatalogSource catalog,QueueMode mode,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or checkpoint the native queue source. |
| inputs / outputs | Standalone source construction retains catalog and explicit queue/input limits. |
| invariants | Creates its own UINT64_MAX standalone account and validates catalog; execution should use the CompiledProgram factory. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Invalid options/state/binding/limits or original-account allocation failures propagate before a usable result. |
| cost | Account/Data/progress construction and full catalog validation; no queued items yet. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TypedQueue(const CompiledProgram&,QueueMode,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or checkpoint the native queue source. |
| inputs / outputs | Execution construction derives catalog and finite account from the admitted program. |
| invariants | No replacement query account or nested queue grant; mode is physical/window and typed queues reject wire total_bytes limits. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Invalid options/state/binding/limits or original-account allocation failures propagate before a usable result. |
| cost | Funded source-control/position ownership, catalog-owner retention and option checks. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TypedQueue(const CompiledProgram&,const QueueCheckpoint&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or checkpoint the native queue source. |
| inputs / outputs | Restore an empty queue component with default SourceStateLimits. |
| invariants | Delegates to the explicit bounded checkpoint constructor; no whole session/durable authority from copied fields. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Invalid options/state/binding/limits or original-account allocation failures propagate before a usable result. |
| cost | Explicit restore validation/fingerprint/progress cloning work. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TypedQueue(const CompiledProgram&,const QueueCheckpoint&,const SourceStateLimits&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or checkpoint the native queue source. |
| inputs / outputs | Restore queue metadata under explicit source-state limits. |
| invariants | Validates source positions/record caps/catalog hash/mode; recreates accepted progress into receiving original account, with no pending head. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Invalid options/state/binding/limits or original-account allocation failures propagate before a usable result. |
| cost | Positions/name-byte validation and cloning, canonical catalog fingerprint allocation/hash, and fresh receiving-account Data/map/key character blocks. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
QueueCheckpoint checkpoint_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or checkpoint the native queue source. |
| inputs / outputs | Capture the empty source component with default limits. |
| invariants | Requires live queue, no head/cache and no sticky error; no durable publication occurs. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Invalid options/state/binding/limits or original-account allocation failures propagate before a usable result. |
| cost | Delegates to bounded capture; positions/fingerprint/progress costs remain. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
QueueCheckpoint checkpoint_state(const SourceStateLimits&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or checkpoint the native queue source. |
| inputs / outputs | Capture empty queue metadata under explicit work/position limits. |
| invariants | The returned editable component is revalidated by restore; empty queue is separate from session quiescence/root locking. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Invalid options/state/binding/limits or original-account allocation failures propagate before a usable result. |
| cost | Position/name validation, funded progress Data/map/key-character clones and canonical catalog fingerprint generation. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
~TypedQueue();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release the queue source graph. |
| inputs / outputs | Destroys Data, each batch/item, compact payload, accepted positions and retained schema. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | Iterative batch/item teardown avoids recursive link depth; retained graph/map destruction is proportional to actual owned objects. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TypedQueue(const TypedQueue&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject queue owner copying. |
| inputs / outputs | A live source has one mutable acceptance/control owner. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | Compile-time restriction. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TypedQueue& operator=(const TypedQueue&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject queue copy assignment. |
| inputs / outputs | No duplicate mutable source cursor. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | Compile-time restriction. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TypedQueue(TypedQueue&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer queue source ownership. |
| inputs / outputs | Moves the native Data descriptor. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | Fixed transfer; no row/progress clone. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TypedQueue& operator=(TypedQueue&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace/transfer queue source ownership. |
| inputs / outputs | Releases old Data then transfers the source descriptor. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | Transfer plus actual prior graph/map/schema release costs; no new allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
void finish() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop future batch admission while retaining drainable heads. |
| inputs / outputs | Sets closed when Data exists; does not accept/discard queued events. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | Fixed flag update. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
bool failed() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read sticky semantic-head failure. |
| inputs / outputs | Absent Data reports false. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | Fixed flag read. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
bool closed() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whether further admission is finished. |
| inputs / outputs | Absent Data reports true; existing queued heads may remain. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | Fixed flag read. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
bool empty() const noexcept;
  [[nodiscard]] QueueStats stats() const noexcept;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether queued heads remain. |
| inputs / outputs | Absent Data or no native head reports true. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | Fixed head-pointer test. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
QueueStats stats() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current queue counts and flags. |
| inputs / outputs | Absent Data returns zero counts/closed true/failed false. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | Fixed metadata copy. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
AccountedInputProgress close() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move accepted progress out and discard pending input. |
| inputs / outputs | No implicit acknowledgment; repeated close returns empty progress. |
| invariants | Preserves ordered-source semantics; no hidden input acceptance or engine retry. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Deleted functions fail compilation; declared noexcept owner/control operations do not throw. |
| cost | No new allocation; actual queued graph, schema/options and map ownership release costs remain. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
Admission enqueue(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Atomically import an offered external batch into native queue membership. |
| inputs / outputs | accepted clears offered TransportBatch; full preserves it; a failed private import unwinds before native queue linking. |
| invariants | Preflight and retained native request reconciliation precede publication. No input coalescing, source acknowledgment or engine application. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Closed/failed/malformed/overflow/resource errors propagate; full is a value result. Private account allocation history may advance even though membership/accepted progress and offered batch are preserved. |
| cost | Count/cap checks, repeated row-shape/payload size preflight, funded node/row/text import and original-account request reconciliation; successful publication links prepared graph without another allocation. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
const InputItemView* peek();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and expose the current owned head. |
| inputs / outputs | Returns cached validated head, nullptr when empty, or prepares its monotone source position before caching. |
| invariants | Checks source mode, envelope/row/payload/domain limits, contiguous sequence, record cap and per-source increasing offset before acknowledgment. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Error marks semantic failure sticky; MemoryFailure/bad_alloc bypass that catch so accepted prefix/owned head remain retryable. |
| cost | Head row/text/domain validation plus ordered source-map lookup and possible funded key/node preparation; cached peek reuses the same owned head. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
void acknowledge() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish prepared source acceptance and retire exactly one head. |
| inputs / outputs | Publishes prepared position, updates accepted sequence/counters and releases the owned item/batch when empty; no cached head is a no-op. |
| invariants | Requires source-owned valid cached preparation; no stream read, engine operation or allocation follows acceptance. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | No throwing operation under the owner protocol; internal prepared-map invariant failures terminate rather than recover a foreign token. |
| cost | Prepared map link or scalar update, fixed count/head work and actual retired item/payload/batch release. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
const AccountedInputProgress& progress() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the queue accepted prefix. |
| inputs / outputs | Returns native accepted sequence/source-position map; pending head is excluded. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Closed/moved-from queue rejects with invalid_input_reader. |
| cost | Fixed owner check/reference access; an explicit progress copy allocates Data, map nodes and nonempty key character blocks and copies key bytes. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
friend class runtime::QuerySession;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict recovery head staging to the session coordinator. |
| inputs / outputs | Friend may call private stage_replay and account-aware constructors. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Compile-time access only. |
| failure | No runtime operation. |
| cost | No runtime overhead. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::uint64_t stage_replay(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage a previously verified pending recovery head without external DTO transport. |
| inputs / outputs | Checks source/checkpoint limits and mode, imports one native head then invokes normal peek preparation. |
| invariants | Private restoration publishes its imported head before peek; a subsequent peek error can retain it, and failed session restore discards this private source. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Image/native/semantic/allocation failures propagate; do not promise whole-method unchanged state after head publication. |
| cost | Bounded source/row validation and native one-head allocation/copy; returned value is selected source-state work, not total CPU. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TypedQueue(const resource::MemoryAccount&,CatalogSource,QueueMode,QueueLimits,InputLimits,bool admitted);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the private account/catalog authority bridge. |
| inputs / outputs | Receives an actual retained account/catalog and admitted flag from closed factories. |
| invariants | Only the program bridge supplies admitted=true; standalone sources validate catalog. Flag is private, not caller DTO authority. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Option/checkpoint/allocation errors unwind private construction. |
| cost | Source Data/progress/canonical fingerprint costs of the selected constructor. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TypedQueue(const resource::MemoryAccount&,CatalogSource,const QueueCheckpoint&,const SourceStateLimits&,bool admitted);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the private account/catalog authority bridge. |
| inputs / outputs | Receives an actual retained account/catalog and admitted flag from closed factories. |
| invariants | Only the program bridge supplies admitted=true; standalone sources validate catalog. Flag is private, not caller DTO authority. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Option/checkpoint/allocation errors unwind private construction. |
| cost | Source Data/progress/canonical fingerprint costs of the selected constructor. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0014

[Lines 102–105](../../../../../../include/crown/io/batch.hpp#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Data;
  resource::AccountedUnique<Data> data_;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide native queue storage and acceptance state. |
| inputs / outputs | Opaque implementation contains account/catalog, linked batches, accepted progress and prepared head metadata. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Declaration itself creates no resource or handler. |
| cost | No runtime action. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
resource::AccountedUnique<Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the source-control graph in its original account. |
| inputs / outputs | Single movable funded Data owner; absent means closed/moved-from. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Native Data and queued graph use the retained original account. Returned head/progress pointers borrow this live Data and are invalidated by acknowledgment, close or destruction as applicable. |
| failure | Only prepared construction allocates; descriptor release follows native teardown. |
| cost | Fixed descriptor; final graph release is not a constant-cost population claim. |
| Design | [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/batch_program.cpp](../../../../../../src/io/batch_program.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |
