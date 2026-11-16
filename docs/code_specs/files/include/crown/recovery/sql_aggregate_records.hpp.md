# `include/crown/recovery/sql_aggregate_records.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/sql_aggregate_records.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `4baa72f51d754c6687112691552ec2cca11b59b53e4f7a9db6759f328cfaff42`. 183 lines partitioned into 30 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // R2 record data only. Binding hashes identify a separately admitted descriptor; · [reviewed contract](#b0001) |
| [B0002 · 14–18](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L14) | Type/record definition: struct Binding | source comment (unverified): // R2 record data only. Binding hashes identify a separately admitted descriptor; · [reviewed contract](#b0002) |
| [B0003 · 19–25](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L19) | Type/record definition: struct WalHeader |  · [reviewed contract](#b0003) |
| [B0004 · 26–31](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L26) | Type/record definition: struct SinkHeader |  · [reviewed contract](#b0004) |
| [B0005 · 32–32](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L32) | Type/record definition: struct SourcePosition |  · [reviewed contract](#b0005) |
| [B0006 · 33–33](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L33) | Explanatory comments or spacing. | source comment (unverified): // JSONL progress is independent of I/C after rejection. No R1 CSV permutation. · [reviewed contract](#b0006) |
| [B0007 · 34–37](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L34) | Type/record definition: struct ReaderPosition | source comment (unverified): // JSONL progress is independent of I/C after rejection. No R1 CSV permutation. · [reviewed contract](#b0007) |
| [B0008 · 38–43](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L38) | Type/record definition: struct InputView |  · [reviewed contract](#b0008) |
| [B0009 · 44–51](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L44) | Type/record definition: struct Commit |  · [reviewed contract](#b0009) |
| [B0010 · 52–52](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L52) | Explanatory comments or spacing. | source comment (unverified): // Stable explicit semantic allowlist. Resource/contract failures have no tag. · [reviewed contract](#b0010) |
| [B0011 · 53–56](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L53) | Type/record definition: enum class RejectReason : std::uint8_t | source comment (unverified): // Stable explicit semantic allowlist. Resource/contract failures have no tag. · [reviewed contract](#b0011) |
| [B0012 · 57–63](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L57) | Type/record definition: struct Reject |  · [reviewed contract](#b0012) |
| [B0013 · 64–69](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L64) | Type/record definition: struct GroupEpochView |  · [reviewed contract](#b0013) |
| [B0014 · 70–70](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L70) | Type/record definition: enum class Kind : std::uint8_t |  · [reviewed contract](#b0014) |
| [B0015 · 71–71](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L71) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |
| [B0016 · 72–75](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L72) | Type/record definition: struct Limits |  · [reviewed contract](#b0016) |
| [B0017 · 76–82](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L76) | Type/record definition: struct InputInfo |  · [reviewed contract](#b0017) |
| [B0018 · 83–87](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L83) | Type/record definition: struct GroupInfo |  · [reviewed contract](#b0018) |
| [B0019 · 88–94](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L88) | Type/record definition: struct Inspected |  · [reviewed contract](#b0019) |
| [B0020 · 95–97](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L95) | Explanatory comments or spacing. | source comment (unverified): // A move transfers account-owned bytes. Views require a live, unmoved frame; · [reviewed contract](#b0020) |
| [B0021 · 98–113](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L98) | Type/record definition: class Frame | returns {bytes_.data(),bytes_.size()}; info_; source comment (unverified): // A move transfers account-owned bytes. Views require a live, unmoved frame; · [reviewed contract](#b0021) |
| [B0022 · 114–116](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L114) | Explanatory comments or spacing. | source comment (unverified): // Decoder owns one frame plus two flat arrays; TEXT cells/source names borrow · [reviewed contract](#b0022) |
| [B0023 · 117–133](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L117) | Type/record definition: class DecodedInput | returns frame_; source comment (unverified): // Decoder owns one frame plus two flat arrays; TEXT cells/source names borrow · [reviewed contract](#b0023) |
| [B0024 · 134–148](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L134) | declares values/defaults or compile-time conditions. | source comment (unverified): // These are bounded transport factories, not durable file/session factories. · [reviewed contract](#b0024) |
| [B0025 · 149–152](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L149) | Type/record definition: struct ScanLimits |  · [reviewed contract](#b0025) |
| [B0026 · 153–156](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L153) | Type/record definition: struct PendingInput |  · [reviewed contract](#b0026) |
| [B0027 · 157–163](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L157) | Type/record definition: struct WalState |  · [reviewed contract](#b0027) |
| [B0028 · 164–166](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L164) | Explanatory comments or spacing. | source comment (unverified): // Allocation-free transport validation, not a file lock or native replay owner. · [reviewed contract](#b0028) |
| [B0029 · 167–181](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L167) | Type/record definition: class WalCursor | returns state_; source comment (unverified): // Allocation-free transport validation, not a file lock or native replay owner. · [reviewed contract](#b0029) |
| [B0030 · 182–183](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L182) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::recovery::sql_aggregate · [reviewed contract](#b0030) |

## B0001

[Lines 1–13](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Hash = std::array<char,64>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Introduce fixed-width \`Hash\`/\`Id\` aliases and forward-declare the internal frame-access helper. |
| inputs / outputs | \`Hash\` is \`array&lt;char,64&gt;\` and \`Id\` is \`array&lt;char,32&gt;\`. \`detail::FrameAccess\` is only named here for later private-constructor friendship; this block defines no helper interface. |
| invariants | Array widths do not validate lowercase hex, bindings, or frames; callers can construct arbitrary bytes. The forward declaration alone grants no access; later friend declarations and private constructors form the codec boundary. |
| ownership | Both aliases store bytes inline. This preamble retains no frame or decoded command arrays; \`Frame\` and \`DecodedInput\` are separate value types declared later. |
| failure | The aliases and forward declaration have no runtime failure path. Later codec routines reject malformed characters/framing; supplied-account allocation failures occur in encode/decode operations. |
| cost | The two arrays require no dynamic storage and the forward declaration has no runtime cost. Later codecs traverse/hash frame bytes and may allocate account-owned buffers. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp §Hash/Id and helper](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp §FrameAccess and hex validation](../../../../../../src/recovery/sql_aggregate_records.cpp), [docs/sql_aggregate_records.md §record binding](../../../../../sql_aggregate_records.md) |

## B0002

[Lines 14–18](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Binding {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify a query and separately admitted descriptor with fixed-width IDs/hashes. |
| inputs / outputs | Declaration: \`struct Binding\`. Inputs/outputs: Identify a query and separately admitted descriptor with fixed-width IDs/hashes. |
| invariants | Fixed arrays own only ID/hash characters; successful decoding does not authorize or reconstruct a descriptor. |
| ownership | Owns only two fixed character arrays; no Program/descriptor object is retained. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0003

[Lines 19–25](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WalHeader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the WAL checkpoint binding, generation, and initial physical/command frontiers. |
| inputs / outputs | Declaration: \`struct WalHeader\`. Inputs/outputs: Carry the WAL checkpoint binding, generation, and initial physical/command frontiers. |
| invariants | The compact header records C as physical_sequence and I as command_sequence; runtime/file binding checks remain external. |
| ownership | Owns fixed arrays and scalar metadata by value. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0004

[Lines 26–31](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SinkHeader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry sink identity and its base physical sequence under a descriptor binding. |
| inputs / outputs | Declaration: \`struct SinkHeader\`. Inputs/outputs: Carry sink identity and its base physical sequence under a descriptor binding. |
| invariants | Sink identity is separate from query/descriptor identity; base_sequence is the sink's advertised baseline. |
| ownership | Owns its nested fixed binding and sink ID by value. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0005

[Lines 32–32](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourcePosition { std::string_view source; std::uint64_t offset; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a source name and identify its byte offset for one encoded input. |
| inputs / outputs | Declaration: \`struct SourcePosition\`. Inputs/outputs: Borrow a source name and identify its byte offset for one encoded input. |
| invariants | source is a string_view borrowed by the enclosing InputView/encode call; it is copied into frame bytes by encoding. |
| ownership | Borrowed \`source\` view; it is not extended by this DTO. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0006

[Lines 33–33](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L33:sha256:f4ca55b4d11f33bd11c80d5526cdde4f9c125bbbd6a3b3c90738bf9568e312d4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: JSONL progress is independent of I/C after rejection. No R1 CSV permutation. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_records.hpp lines 31-35; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_records.hpp.md](sql_aggregate_records.hpp.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0007

[Lines 34–37](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReaderPosition {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry JSONL source-reader byte and record progress independently of I/C frontiers. |
| inputs / outputs | Declaration: \`struct ReaderPosition\`. Inputs/outputs: Carry JSONL source-reader byte and record progress independently of I/C frontiers. |
| invariants | Counters are unsigned value fields; when present on Input, both bytes and records must be positive; they do not replace input/commit/output frontiers. |
| ownership | Owns only two counters. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0008

[Lines 38–43](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present one physical command sequence, ordered source replacements, and optional source/reader metadata for encoding. |
| inputs / outputs | Declaration: \`struct InputView\`. Inputs/outputs: Present one physical command sequence, ordered source replacements, and optional source/reader metadata for encoding. |
| invariants | Replacements preserve supplied order; source and reader metadata are optional and borrowed only during encode. |
| ownership | Borrows replacement span and optional source name; encoding copies them into returned Frame. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0009

[Lines 44–51](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Commit {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record a committed input identity, command/physical sequences, and complete output frame digest/length. |
| inputs / outputs | Declaration: \`struct Commit\`. Inputs/outputs: Record a committed input identity, command/physical sequences, and complete output frame digest/length. |
| invariants | output_sha256/bytes identify a complete encoded group-output frame; neither field proves durable publication. |
| ownership | Owns only fixed hashes and scalar fields. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0010

[Lines 52–52](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L52:sha256:cb6cf0dcee259296b8b75e3ad4538a6cb10332e2aa50394e61f3d09ca68ef867
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Stable explicit semantic allowlist. Resource/contract failures have no tag. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_records.hpp lines 50-54; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_records.hpp.md](sql_aggregate_records.hpp.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0011

[Lines 53–56](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class RejectReason : std::uint8_t {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the explicit semantic rejection tag allowlist used by R2 Reject records. |
| inputs / outputs | Declaration: \`enum class RejectReason : std::uint8_t\`. Inputs/outputs: Define the explicit semantic rejection tag allowlist used by R2 Reject records. |
| invariants | Only six named semantic reasons are representable; resource/contract failures intentionally have no tag. |
| ownership | Enum value is embedded by value; it owns no storage. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0012

[Lines 57–63](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Reject {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one semantic rejection against its pending input identity and unchanged physical frontier. |
| inputs / outputs | Declaration: \`struct Reject\`. Inputs/outputs: Record one semantic rejection against its pending input identity and unchanged physical frontier. |
| invariants | Reject binds to prior input ordinal/hash, advances I when WAL feed accepts it, and leaves C unchanged. |
| ownership | Owns fixed hash/scalars/enum by value. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0013

[Lines 64–69](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L64); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GroupEpochView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present one aggregate group epoch as borrowed complete-key before/after changes plus its sequence/binding facts. |
| inputs / outputs | Declaration: \`struct GroupEpochView\`. Inputs/outputs: Present one aggregate group epoch as borrowed complete-key before/after changes plus its sequence/binding facts. |
| invariants | Group changes use complete keys and borrowed spans; empty epochs are representable and group order is canonicalized by codec. |
| ownership | Borrows the groups span; no group Tuple is retained by this view. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0014

[Lines 70–70](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L70); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Kind : std::uint8_t { wal_header, input, commit, reject, sink_header, group_epoch };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign stable wire tags to the six R2 record payload alternatives. |
| inputs / outputs | Declaration: \`enum class Kind : std::uint8_t\`. Inputs/outputs: Assign stable wire tags to the six R2 record payload alternatives. |
| invariants | Variant index is the wire tag 0..5 in declared order; tag alone conveys no descriptor authority. |
| ownership | Enum value is embedded in PayloadView by value. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0015

[Lines 71–71](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using PayloadView = std::variant<WalHeader,InputView,Commit,Reject,SinkHeader,GroupEpochView>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Unify the six record payload alternatives accepted by the SQL aggregate codec. |
| inputs / outputs | \`PayloadView\` selects WAL header, borrowed input view, commit, reject, sink header, or group-epoch view for encoding. |
| invariants | The view is transport input only; nested spans/text borrow the caller for the encode call. It is not a durable file, native state, or replay authority. |
| ownership | Value alternatives own their fixed DTO members; \`InputView\`/\`GroupEpochView\` retain only borrowed spans/views and must stay valid through encoding. |
| failure | The variant permits construction of malformed metadata; codec validation checks binding, sequence, scalar and payload constraints before publishing a frame. |
| cost | Variant dispatch is fixed; input/group traversal, row ordering, checksum, and account-backed frame allocation depend on payload size. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp §record variants](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp §payload validation and encoding](../../../../../../src/recovery/sql_aggregate_records.cpp), [docs/sql_aggregate_records.md §record forms](../../../../../sql_aggregate_records.md) |

## B0016

[Lines 72–75](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L72); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair per-frame image limits with a bound for optional source-name bytes. |
| inputs / outputs | Declaration: \`struct Limits\`. Inputs/outputs: Pair per-frame image limits with a bound for optional source-name bytes. |
| invariants | \`record\` carries ImageLimits; \`source_bytes\` is a separate transport name ceiling. |
| ownership | Value limits are copied; no shared budget/controller is kept. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0017

[Lines 76–82](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L76); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputInfo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Summarize decoded Input metadata and source offsets into its owning frame. |
| inputs / outputs | Declaration: \`struct InputInfo\`. Inputs/outputs: Summarize decoded Input metadata and source offsets into its owning frame. |
| invariants | source_begin/source_size index frame bytes, not owned text; reader is a fixed metadata copy. |
| ownership | Contains scalar offsets/counts and optional copied ReaderPosition; source bytes remain elsewhere. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0018

[Lines 83–87](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L83); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GroupInfo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Summarize a group epoch without retaining its group-change collection. |
| inputs / outputs | Declaration: \`struct GroupInfo\`. Inputs/outputs: Summarize a group epoch without retaining its group-change collection. |
| invariants | groups is a count only; the summary contains no group rows or replay state. |
| ownership | Owns scalar/hash summary only; no group collection. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0019

[Lines 88–94](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L88); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Inspected {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return validated frame metadata, hashes, statistics, and a compact payload summary. |
| inputs / outputs | Declaration: \`struct Inspected\`. Inputs/outputs: Return validated frame metadata, hashes, statistics, and a compact payload summary. |
| invariants | payload contains fixed DTO/summary variants, not source bytes, full group vectors, or native runtime state. |
| ownership | Owns its fixed variant and statistics; no source frame bytes. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0020

[Lines 95–97](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L95); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L97:sha256:c708d3eac072f4e065c3a56d28d3c923a42e9cf1a845c2205187f11be4dc7db1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: A move transfers account-owned bytes. Views require a live, unmoved frame; immutable bytes avoid a second owned command copy at the coordinator boundary. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_records.hpp lines 93-99; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_records.hpp.md](sql_aggregate_records.hpp.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0021

[Lines 98–113](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L98); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Frame {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own immutable encoded frame bytes and their inspected metadata through move-only access. |
| inputs / outputs | Declaration: \`class Frame\`. Inputs/outputs: Own immutable encoded frame bytes and their inspected metadata through move-only access. |
| invariants | Copies are deleted, moves transfer the account-owned byte vector, and rvalue byte/info access is deleted. |
| ownership | Move-only owner of account-backed bytes; lvalue bytes/info views borrow this object. |
| failure | The constructor is private; encode factories perform validation/allocation before a Frame is returned, while moves and lvalue accessors are noexcept. |
| cost | One move-only frame facade; no byte copy on move. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0022

[Lines 114–116](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L114); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L116:sha256:e082a8146ded6dbe6219a9595c80a69dd9a49b7e6d9ce2e8a67ac8cfadf34191
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Decoder owns one frame plus two flat arrays; TEXT cells/source names borrow that frame. Moves preserve heap addresses; copying/rvalue views are forbidden. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_records.hpp lines 112-118; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_records.hpp.md](sql_aggregate_records.hpp.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0023

[Lines 117–133](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L117); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class DecodedInput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one decoded Input frame plus flat decoded cells/replacements whose string views borrow that frame. |
| inputs / outputs | Declaration: \`class DecodedInput\`. Inputs/outputs: Own one decoded Input frame plus flat decoded cells/replacements whose string views borrow that frame. |
| invariants | Copy/rvalue views are forbidden; frame_ precedes borrowed cells/replacements so its byte owner remains available. |
| ownership | Move-only owner of Frame and account-backed arrays; any \`view()\` result borrows those members. |
| failure | The constructor is private and noexcept; decode/encode_input perform validation/allocation before a DecodedInput is returned, while moves are noexcept. |
| cost | One facade with fixed arrays plus the already allocated frame/cell/replacement vectors; no copy path. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0024

[Lines 134–148](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L134); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Frame encode(const resource::MemoryAccount&,const frontend::SqlAggregateProgram&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare bounded full-frame transport encode, inspect, decode, and input encode/decode operations. |
| inputs / outputs | \`encode\` consumes a genuine SQL aggregate program and payload; \`inspect\` borrows bytes; \`decode_input\` copies a validated input frame and materializes arrays; \`encode_input\` creates one owned frame plus decoded flat views. |
| invariants | These APIs validate one exact frame; they do not own a file/WAL or construct/replay native runtime state. Limits bound codec bytes/rows/work and source metadata as configured. |
| ownership | \`Frame\` owns account-allocated bytes plus fixed \`Inspected\` metadata. \`DecodedInput\` separately owns account-allocated flat cells and replacements alongside a \`Frame\`; its \`view()\` string/replacement references borrow those live owners. \`inspect\` returns ordinary value metadata. |
| failure | Malformed frame, binding, scalar, or configured-limit conditions use \`ImageFailure\`. Failures from supplied-account allocations propagate as resource/allocation failures rather than being translated into an image fault. |
| cost | \`encode\` measures/writes and hashes bytes, staging packed keys/order and sorting group epochs. Successful \`inspect\` scans borrowed bytes and hashes without allocating an account buffer. \`decode_input\` validates then copies frame bytes and allocates flat arrays; \`encode_input\` materializes arrays over its already owned frame, without an encode-then-copy frame buffer. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp §codec declarations](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp §encode/inspect/decode](../../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/binary_detail.hpp §borrowed reader and frame validation](../../../../../../src/recovery/binary_detail.hpp), [docs/sql_aggregate_records.md §bounded transport](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_checkpoint.md §checkpoint is a separate component](../../../../../sql_aggregate_checkpoint.md) |

## B0025

[Lines 149–152](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L149); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ScanLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set cumulative WAL scan byte/work/record ceilings and embedded per-frame limits. |
| inputs / outputs | Declaration: \`struct ScanLimits\`. Inputs/outputs: Set cumulative WAL scan byte/work/record ceilings and embedded per-frame limits. |
| invariants | bytes/work/records are cumulative scan caps; per-frame limits remain in frame and are not refilled per record. |
| ownership | Copies configured numeric limits by value; owns no per-scan allocations. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0026

[Lines 153–156](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L153); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PendingInput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remember the single pending input ordinal, command sequence, and body identity. |
| inputs / outputs | Declaration: \`struct PendingInput\`. Inputs/outputs: Remember the single pending input ordinal, command sequence, and body identity. |
| invariants | At most one pending input is kept; its digest is the validated frame body hash. |
| ownership | Owns the input body digest and numeric identity by value. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0027

[Lines 157–163](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L157); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WalState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold fixed-size WAL transport validation frontiers, cumulative counters, sink floor, and at most one pending input. |
| inputs / outputs | Declaration: \`struct WalState\`. Inputs/outputs: Hold fixed-size WAL transport validation frontiers, cumulative counters, sink floor, and at most one pending input. |
| invariants | State owns fixed-size values and optional one-record identity only; it is neither a file lock nor a genuine replay owner. |
| ownership | Owns fixed counters/headers plus one optional pending identity. |
| failure | DTO declarations do not validate on construction; encode/inspect raises ImageFailure for invalid values, and owning factories may propagate allocation/account exceptions. |
| cost | Fixed-size DTO declaration; no runtime work. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md) |

## B0028

[Lines 164–166](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L164); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L164-L166:sha256:4491460258addc029f63836e8acba491ecc93287cc299d514d5e7b287eee52a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Allocation-free transport validation, not a file lock or native replay owner. Feed complete frames in order. Failure preserves the previous validated state; files still need independent identity/EOF/tail checks and genuine replay. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_records.hpp lines 162-168; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_records.hpp.md](sql_aggregate_records.hpp.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0029

[Lines 167–181](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L167); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class WalCursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Feed complete frames into an allocation-free transport state cursor; this declaration grants no file/replay ownership. |
| inputs / outputs | Declaration: \`class WalCursor\`. Inputs/outputs: Feed complete frames into an allocation-free transport state cursor; this declaration grants no file/replay ownership. |
| invariants | Failed feed must preserve the last validated WalState; caller still performs file identity, EOF/tail, sink and native replay checks. The concrete WalFile friend can stage fixed state with its spent grants; public copying remains forbidden and publication waits for confirmed IO. |
| ownership | Owns fixed ScanLimits and WalState; no file descriptor, account allocation, or replay owner. |
| failure | Construction is noexcept; feed raises ImageFailure for invalid frames/transitions and does not translate it. |
| cost | Fixed-size cursor state; feed work is charged to cumulative scan limits. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_records.md § Wire contract](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Ownership, failure and cost](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § WAL state machine](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

## B0030

[Lines 182–183](../../../../../../include/crown/recovery/sql_aggregate_records.hpp#L182); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr std::size_t frame_prefix_size = 84, frame_header_size = 148;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the protected prefix and full fixed header lengths used by the R2 frame codec. |
| inputs / outputs | The constants are 84 prefix bytes and 148 total header bytes, before the body begins. |
| invariants | Lengths alone do not identify or validate a frame; magic/version, body and prefix hashes, exact length, and typed payload must also match. |
| ownership | Compile-time size constants own no data; frame buffers are separately allocated by codec/file owners. |
| failure | No runtime failure occurs from reading the constants. Parsers reject malformed/truncated lengths and incompatible version/content. |
| cost | No runtime cost for constants; frame hashing/byte visits scale with protected header and body lengths. |
| Design | [include/crown/recovery/sql_aggregate_records.hpp §frame constants](../../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/sql_aggregate_records.cpp §frame framing](../../../../../../src/recovery/sql_aggregate_records.cpp), [src/recovery/sql_aggregate_file_detail.cpp §file frame scan](../../../../../../src/recovery/sql_aggregate_file_detail.cpp), [docs/sql_aggregate_records.md §wire contract](../../../../../sql_aggregate_records.md) |
