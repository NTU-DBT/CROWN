# `src/recovery/local_sink_codec.hpp` — block usage map

[Source](../../../../../src/recovery/local_sink_codec.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `a264939ae31781d37ed64f5f391f242261d0e25c9aeb287141d44d672b605f58`. 13 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–3](../../../../../src/recovery/local_sink_codec.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 4–4](../../../../../src/recovery/local_sink_codec.hpp#L4) | Type/record definition: struct Encoded |  · [reviewed contract](#b0002) |
| [B0003 · 5–5](../../../../../src/recovery/local_sink_codec.hpp#L5) | Type/record definition: struct Inspected |  · [reviewed contract](#b0003) |
| [B0004 · 6–13](../../../../../src/recovery/local_sink_codec.hpp#L6) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Validates protected length without requiring the body. File::open decides · [reviewed contract](#b0004) |

## B0001

[Lines 1–3](../../../../../src/recovery/local_sink_codec.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/recovery/local_sink.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare private canonical local-sink wire operations beside the actual File owner. |
| inputs / outputs | Public fixed Header/Row/Epoch types and explicit account/limit parameters. |
| invariants | These codec functions do not acquire File locks, establish sequence continuity across frames, append/fsync or issue private receipts. |
| ownership | No global state or implicit receiving account. |
| failure | Only invoked codecs may fail; include has no runtime effects. |
| cost | Compile-time boundary; costs follow individual operations. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0002

[Lines 4–4](../../../../../src/recovery/local_sink_codec.hpp#L4); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Encoded {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry funded canonical bytes and measured codec work to File publication. |
| inputs / outputs | ImageVector&lt;char&gt; bytes and used work. |
| invariants | work describes the performed codec call; File consumes it into its cumulative grant and compares actual bytes for duplicate epochs. Mutable fields alone are not delivery evidence. |
| ownership | Vector owns its actual receiving-account allocation; copying can allocate, moving transfers the owner. |
| failure | Copy/allocation failures obey vector/account behavior; destruction releases owned buffer. |
| cost | O(bytes) deep copy if copied, constant transfer if moved; byte storage overlaps other encoder scratch until return. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0003

[Lines 5–5](../../../../../src/recovery/local_sink_codec.hpp#L5); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Inspected {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed structural facts from one validated frame. |
| inputs / outputs | Header discriminator/binding, ordinal,generation,sequence,rows and work. |
| invariants | Header frames fill binding and ordinal0; epoch frames fill positive lineage/row metadata. Unused fields remain defaults. Cross-frame continuity and schema SHA derivation belong to File. |
| ownership | Fixed metadata owns no input frame, lock or row payload. |
| failure | Construction/editing does not validate values; only inspect supplies checked facts. |
| cost | Fixed-size value copying; no retained dynamic graph. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

## B0004

[Lines 6–13](../../../../../src/recovery/local_sink_codec.hpp#L6); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Encoded encode_header(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a schema-bound immutable sink origin frame. |
| inputs / outputs | Account, Header, schema and ImageLimits in; canonical funded Encoded out. |
| invariants | Validates header/type/policy fields and exact schema count; File derives schema_sha256 before calling. Performs sizing first but remaining encode/checksum work can still exhaust after allocation. |
| ownership | Output vector owns supplied-account bytes; schema/header are borrowed synchronously. |
| failure | ImageFailure/allocation failure leaves no File published; private vector unwinds. |
| cost | Fixed metadata+O(fields) encode/hash; finite1024/schema validation debits plus serialized and checksum work. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

```text
[[nodiscard]] Encoded encode_epoch(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode sorted unique complete signed-row bytes for canonical sink delivery. |
| inputs / outputs | Account, ordinal/generation/sequence, row/schema views and limits in. |
| invariants | Requires positive coordinates, row/schema/type/scalar limits and UTF-8 text; sorts serialized complete signed rows and rejects byte duplicates. Cross-frame ordinal/sequence/generation continuity is separate File validation. |
| ownership | Segment array, serialized values and final bytes overlap under one account; all caller rows remain borrowed through the call. |
| failure | Validation/work/allocation failure discards scratch/results before append. No File poison is created by this codec alone. |
| cost | O(total row bytes) plus O(r log r) charged lexicographic comparisons; copying/hashing adds passes and finite work can fail after scratch allocation. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

```text
[[nodiscard]] Inspected inspect(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a complete canonical sink frame without decoding an owned Epoch. |
| inputs / outputs | Immutable full frame and schema/limits in; fixed Inspected out. |
| invariants | Checks protected prefix/body checksum, type/schema data, UTF-8, exact exhaustion and strictly increasing complete row bytes. It does not authenticate origin, derive schema hash or prove log-prefix continuity. |
| ownership | Borrows frame/schema only during call. |
| failure | ImageFailure on framing/work/canonical mismatch; no file repair or row allocation. |
| cost | O(frame bytes+comparison text), explicit prefix/hash/validation/comparison work. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

```text
[[nodiscard]] Epoch decode(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize a fully inspected epoch into receiver-owned native rows. |
| inputs / outputs | Account, immutable complete frame and schema/limits in; Epoch out. |
| invariants | Rejects header frames, performs inspect then parse under one combined record work limit; not all second-pass work is precharged before growth. |
| ownership | ImageVector&lt;Row&gt; and deep AccountedRows own receiver bytes; input string views are copied before escape. |
| failure | Work/allocation failure during second pass releases private result. File caller decides its own I/O/poison state. |
| cost | Two complete parse/checksum passes plus compact-row copying and scratch descriptors, all simultaneous allocations charged to the account. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |

```text
[[nodiscard]] std::uint64_t frame_size(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate protected length before a File caller classifies a short frame body. |
| inputs / outputs | At least the148-byte protected header plus limits in; total frame length and used work out. |
| invariants | Checks magic/version/flags/body bound/hash text/protected-header SHA; it does not require/inspect the body or itself know file offset. File::open rejects any incomplete initial frame before accepting a later torn tail. |
| ownership | Only borrowed header bytes; work reference updated on successful return. |
| failure | ImageFailure leaves caller work argument unchanged because assignment follows prefix validation; no truncation occurs here. |
| cost | Fixed header/prefix hashing and bounded arithmetic, independent of declared body size. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp) |
