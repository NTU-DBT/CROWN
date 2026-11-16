# `include/crown/recovery/journal.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/journal.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `fda23d930ef04c452e56a004356d63d9e607054842c734a4d0e740fcc2a96247`. 143 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/recovery/journal.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Version-1 journal records and prefix validation. Filesystem durability and · [reviewed contract](#b0001) |
| [B0002 · 9–16](../../../../../../include/crown/recovery/journal.hpp#L9) | Type/record definition: class Failure final:public std::exception | returns fault_; @ · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../../include/crown/recovery/journal.hpp#L17) | Type/record definition: enum class Kind:std::uint8_t |  · [reviewed contract](#b0003) |
| [B0004 · 18–18](../../../../../../include/crown/recovery/journal.hpp#L18) | Type/record definition: enum class InputKind:std::uint8_t |  · [reviewed contract](#b0004) |
| [B0005 · 19–19](../../../../../../include/crown/recovery/journal.hpp#L19) | Type/record definition: enum class CommitKind:std::uint8_t |  · [reviewed contract](#b0005) |
| [B0006 · 20–23](../../../../../../include/crown/recovery/journal.hpp#L20) | Type/record definition: struct Limits |  · [reviewed contract](#b0006) |
| [B0007 · 24–32](../../../../../../include/crown/recovery/journal.hpp#L24) | Type/record definition: struct Header |  · [reviewed contract](#b0007) |
| [B0008 · 33–37](../../../../../../include/crown/recovery/journal.hpp#L33) | Type/record definition: struct ReaderAdvanceView |  · [reviewed contract](#b0008) |
| [B0009 · 38–41](../../../../../../include/crown/recovery/journal.hpp#L38) | Type/record definition: struct InputView |  · [reviewed contract](#b0009) |
| [B0010 · 42–49](../../../../../../include/crown/recovery/journal.hpp#L42) | Type/record definition: struct Commit |  · [reviewed contract](#b0010) |
| [B0011 · 50–54](../../../../../../include/crown/recovery/journal.hpp#L50) | Type/record definition: struct Checkpoint |  · [reviewed contract](#b0011) |
| [B0012 · 55–55](../../../../../../include/crown/recovery/journal.hpp#L55) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 56–65](../../../../../../include/crown/recovery/journal.hpp#L56) | Type/record definition: struct InputMetadata | growth insert · [reviewed contract](#b0013) |
| [B0014 · 66–75](../../../../../../include/crown/recovery/journal.hpp#L66) | Type/record definition: struct Inspected |  · [reviewed contract](#b0014) |
| [B0015 · 76–76](../../../../../../include/crown/recovery/journal.hpp#L76) | Type/record definition: struct Encoded |  · [reviewed contract](#b0015) |
| [B0016 · 77–91](../../../../../../include/crown/recovery/journal.hpp#L77) | Type/record definition: struct Decoded | returns {source.data(),source.size()}; source comment (unverified): // Owns native row/source/CSV payload; returned input views borrow this owner. · [reviewed contract](#b0016) |
| [B0017 · 92–97](../../../../../../include/crown/recovery/journal.hpp#L92) | declares values/defaults or compile-time conditions. | source comment (unverified): // Encode allocates one final buffer after full preflight. Decode retains only · [reviewed contract](#b0017) |
| [B0018 · 98–101](../../../../../../include/crown/recovery/journal.hpp#L98) | Type/record definition: struct ScanLimits |  · [reviewed contract](#b0018) |
| [B0019 · 102–107](../../../../../../include/crown/recovery/journal.hpp#L102) | Type/record definition: struct PendingView |  · [reviewed contract](#b0019) |
| [B0020 · 108–115](../../../../../../include/crown/recovery/journal.hpp#L108) | Type/record definition: struct Scanned |  · [reviewed contract](#b0020) |
| [B0021 · 116–123](../../../../../../include/crown/recovery/journal.hpp#L116) | declares values/defaults or compile-time conditions. | source comment (unverified): // Validates a framed prefix without allocation. Pending frame bytes borrow the · [reviewed contract](#b0021) |
| [B0022 · 124–141](../../../../../../include/crown/recovery/journal.hpp#L124) | Type/record definition: class Cursor | returns state_; source comment (unverified): // One validation owns its cumulative limits and continuation state. Scanned · [reviewed contract](#b0022) |
| [B0023 · 142–143](../../../../../../include/crown/recovery/journal.hpp#L142) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::recovery::journal · [reviewed contract](#b0023) |

## B0001

[Lines 1–8](../../../../../../include/crown/recovery/journal.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose WAL framing separate from files/native replay. |
| inputs / outputs | Includes native image and borrowed input views; Fault aliases ImageFault. |
| invariants | Version1 codec validates structural continuity, never durability or actual native query transition semantics. |
| ownership | No file/account owner at inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action at inclusion. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 9–16](../../../../../../include/crown/recovery/journal.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Failure final:public std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed journal Failure diagnostics. |
| inputs / outputs | Fixed image-fault alias and static message. |
| invariants | guarded translates ImageFailure only; allocation/native errors are not generically swallowed. |
| ownership | Only fixed enums/native errno/booleans; what() returns static literal, no dynamic message or authority owner. |
| failure | Constructor/getters noexcept; constructing this public diagnostic itself does not prove a file effect or grant recovery authority. |
| cost | Fixed object construction/copy/getters, no dynamic message formatting or IO. Throw/unwind still has normal C++ ABI/stack cost and can require exception storage outside the query payload model. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit Failure(Fault fault) noexcept:fault_(fault) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct journal Failure. |
| inputs / outputs | Stores supplied fixed diagnostic fields. |
| invariants | Actual implementation chooses phase/outcome; caller-created fields are descriptive only. |
| ownership | Inline values only; no file/runtime retained. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Fault fault() const noexcept {return fault_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read journal Failure fault. |
| inputs / outputs | Returns stored fault by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const char* what() const noexcept override {return "journal record rejected";}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read journal Failure static message. |
| inputs / outputs | Returns constant what() literal. |
| invariants | Message is diagnostic label, not serialized recovery proof. |
| ownership | Static storage; pointer does not depend on exception lifetime. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 17–17](../../../../../../include/crown/recovery/journal.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Kind:std::uint8_t {header,input,commit,checkpoint};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify journal record kind. |
| inputs / outputs | header/input/commit/checkpoint. |
| invariants | Header ordinal0 only; later ordinal contiguous through validator. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 18–18](../../../../../../include/crown/recovery/journal.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class InputKind:std::uint8_t {stream,physical,window};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify source input kind. |
| inputs / outputs | stream/physical/window. |
| invariants | Only window may separate physical and command sequences; stream inputs require matching reader metadata. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 19–19](../../../../../../include/crown/recovery/journal.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CommitKind:std::uint8_t {physical,metadata};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify committed step kind. |
| inputs / outputs | physical versus metadata. |
| invariants | Physical increments native epoch; metadata window step can preserve physical sequence. Tag alone does not prove engine committed. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 20–23](../../../../../../include/crown/recovery/journal.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound one WAL codec record. |
| inputs / outputs | Nested16MiB record/64Mi byte-work/defaultone row/fields/scalar limits plus source name1024 bytes. |
| invariants | Byte work includes both structural/checksum passes and CSV permutation comparisons; record limits separate from total scan/IO/native grants. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 24–32](../../../../../../include/crown/recovery/journal.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Header {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe expected WAL lineage and checkpoint boundary. |
| inputs / outputs | Query ID/generation, runtime binding, checkpoint SHA, physical/command sequences and InputKind. |
| invariants | Header validates fixed hashes/policy/positive generation and nonwindow equal sequences; supplied expected Header must come from actual checked checkpoint, not caller labels alone. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const Header&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare WAL headers. |
| inputs / outputs | Default equality compares all lineage, binding, frontier and input-kind fields. |
| invariants | Value equality does not prove actual source/native admission, live file/lock ownership or durable acceptance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Bounded fixed-member comparison, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 33–37](../../../../../../include/crown/recovery/journal.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReaderAdvanceView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow decoder continuation for one logged stream input. |
| inputs / outputs | bytes/records/header-read and span&lt;const U64&gt; CSV field permutation. |
| invariants | records must match input sequence; no CSV fields without header; range/permutation uniqueness validated during codec. |
| ownership | Owns fixed counters but borrows CSV array; encode does not retain it. |
| failure | Public record construction validates nothing; later codec rejects malformed values. |
| cost | O(1) copy, codec CSV uniqueness explicitly O(F²). |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 38–41](../../../../../../include/crown/recovery/journal.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one physical/window input plus optional reader advance. |
| inputs / outputs | InputItemView and optional ReaderAdvanceView. |
| invariants | All row/source/CSV backing stable through encode; reader advance allowed only stream physical input. Program/schema/source policy remains native admission. |
| ownership | Owns fixed variants/views only, no row/source/CSV storage, pin or account. |
| failure | Lifetime caller precondition; codec may throw on invalid shape/scalar/source. |
| cost | Fixed view copy; no allocation itself. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 42–49](../../../../../../include/crown/recovery/journal.hpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Commit {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe durable decision for one logged input substep. |
| inputs / outputs | Input ordinal/hash, CommitKind, physical/command sequence, substep and completes_input. |
| invariants | Cursor matches exact pending input ordinal/hash/next substep and progression. Metadata describes a decision, not by itself proof native engine applied it. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const Commit&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare WAL commit decisions. |
| inputs / outputs | Default equality compares all input binding, step/frontier and completion fields. |
| invariants | Value equality does not prove actual source/native admission, live file/lock ownership or durable acceptance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Bounded fixed-member comparison, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 50–54](../../../../../../include/crown/recovery/journal.hpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Checkpoint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe checkpoint marker at complete input boundary. |
| inputs / outputs | Physical/command sequences and checkpoint SHA. |
| invariants | Cursor requires no pending input and current exact frontiers; marker is descriptive and does not publish file/root. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const Checkpoint&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare WAL checkpoint markers. |
| inputs / outputs | Default equality compares frontiers and checksum. |
| invariants | Value equality does not prove actual source/native admission, live file/lock ownership or durable acceptance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Bounded fixed-member comparison, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 55–55](../../../../../../include/crown/recovery/journal.hpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using PayloadView=std::variant<Header,InputView,Commit,Checkpoint>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select one borrowed WAL payload for encode. |
| inputs / outputs | variant&lt;Header,InputView,Commit,Checkpoint&gt;. |
| invariants | Variant index maps record kind; InputView alternative still borrows nested rows/text/CSV. Header0 iff ordinal0. |
| ownership | Fixed values or borrowed views only, no owning input graph retained. |
| failure | Construction/copy fixed; codec validates tag/data, not this alias. |
| cost | O(1) bounded variant copy, no payload allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 56–65](../../../../../../include/crown/recovery/journal.hpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputMetadata {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect fixed input metadata without row materialization. |
| inputs / outputs | Window kind/IDs/sequence/times/field count, source presence/length/offset and reader presence/counters/CSV count. |
| invariants | Metadata omits actual row/source/CSV bytes. Equal metadata cannot prove source equality, input validity or native admission. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 66–75](../../../../../../include/crown/recovery/journal.hpp#L66); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Inspected {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return fixed validated WAL record description. |
| inputs / outputs | Kind/ordinal plus fixed Header/InputMetadata/Commit/Checkpoint, body SHA and ImageStatistics. |
| invariants | Only active kind is meaningful. Both checksums/shape validated by inspect; fixed result is not durable/native authority or owned payload. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 76–76](../../../../../../include/crown/recovery/journal.hpp#L76); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Encoded {ImageVector<char> bytes;ImageStatistics statistics;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own canonical encoded WAL frame. |
| inputs / outputs | Funded char vector plus statistics. |
| invariants | Frame is checksummed structural record, not file-synced durability or engine decision proof. |
| ownership | Copies deep-copy bytes on original account; moves transfer actual vector/account. |
| failure | Copy allocation may throw; no whole-aggregate assignment guarantee. Encoder publishes complete result privately. |
| cost | O(frame bytes) copy/allocation; trivial byte buffer release, no frame rescan. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0016

[Lines 77–91](../../../../../../include/crown/recovery/journal.hpp#L77); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Decoded {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own decoded WAL input payload on receiver account. |
| inputs / outputs | Fixed Inspected info, move-only AccountedRow, funded source char and CSV U64 arrays; lvalue-only borrowed accessors. |
| invariants | Full codec validation precedes row/source growth. Public mutation/shape accessor is not native Program/schema/source-policy admission. |
| ownership | Owns receiver compact row/source/CSV capacity; input frame not retained. Row makes implicit aggregate deep copying unsupported; moves transfer storage. |
| failure | Decode/OOM/scalar/binding failure frees unpublished output; input_view checks descriptive shape/kind before borrowing. |
| cost | O(frame/row/source/CSV bytes) decode/materialize; release one row block/two trivial arrays, no source-byte scan. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::string_view source_name() const & noexcept {return {source.data(),source.size()};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow decoded source-name bytes. |
| inputs / outputs | Returns string_view(source.data(),source.size()) from lvalue Decoded. |
| invariants | Name validity originally checked by codec; public edits are not reauthenticated here. |
| ownership | Keep Decoded/native source vector alive and unchanged; view retains nothing. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
std::string_view source_name() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject source view from a temporary decoded WAL owner. |
| inputs / outputs | Rvalue source_name deleted. |
| invariants | Prevents immediate dangling view; lvalue lifetime still caller responsibility. |
| ownership | No ownership returned. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] InputView input_view() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct a borrowed native input view from decoded payload. |
| inputs / outputs | Lvalue Decoded validates input kind, sequence, row/source/CSV sizes, operation/window variant and optional reader shape; returns InputView. |
| invariants | Checks shape only; actual Program/schema/source/window semantics checked by native admission. Does not rerun original checksum or validate arbitrary caller edits as a new signed input. |
| ownership | Borrows this owner row/source/CSV arrays; no new payload/pin/account retained in view. |
| failure | Fixed journal Failure on inconsistent mutable record; no allocation before successful borrowed return. |
| cost | O(1) shape/tag/count construction; scalar/row/source bytes not scanned here. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
InputView input_view() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject native input view from temporary decoded owner. |
| inputs / outputs | Rvalue input_view deleted. |
| invariants | Owner must survive native consumer. |
| ownership | No storage returned. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 92–97](../../../../../../include/crown/recovery/journal.hpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Encoded encode(const resource::MemoryAccount&,std::uint64_t ordinal,const PayloadView&,Limits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one WAL frame after both structural passes are admitted. |
| inputs / outputs | Account/ordinal/stable PayloadView and per-record Limits. |
| invariants | Validate record/ordinal relation, hash/policy, row/source/CSV; source names nonempty non-NUL UTF8, row strings remain exact native byte values. No durability/native admission. |
| ownership | One final funded frame vector; input row/text/CSV borrowed during both unchanged passes. |
| failure | Only ImageFailure translated to journal Failure; OOM/account failure propagates; private result released. |
| cost | O(frame bytes+F² CSV comparisons) preflight/materialization, body and84-byte prefix SHA; charges both structural passes before final reserve. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Inspected inspect(std::string_view,Limits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect complete WAL record without heap payload. |
| inputs / outputs | Stable bytes and finite Limits return fixed Inspected. |
| invariants | Validate magic/version/length/prefix SHA/body SHA/kind/ordinals/scalars/source/CSV shape, reserving second structural parse work. |
| ownership | No byte ownership retained; fixed result arrays only. |
| failure | ImageFailure becomes journal Failure; no file/native effects. |
| cost | O(frame bytes+F² permutation checks), allocation-free inspection. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Decoded decode(const resource::MemoryAccount&,std::string_view,Limits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate then decode one WAL record into native storage. |
| inputs / outputs | Account/stable bytes and limits. |
| invariants | inspect reserves both structural passes before output growth; metadata validation separate from actual native source policy. |
| ownership | Owned receiver row/source/CSV; no input frame borrow retained after call. |
| failure | journal Failure or account/OOM propagates; partial decoded arrays/row freed. |
| cost | Inspect hash/shape plus materialization parse O(frame bytes+F²); funded cell scratch+row/source/CSV arrays. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 98–101](../../../../../../include/crown/recovery/journal.hpp#L98); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ScanLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound one cumulative WAL prefix validation. |
| inputs / outputs | Per-record Limits plus total256MiB/512Mi work/1M records. |
| invariants | One Cursor owns its continuation/limits; copied Scanned cannot reset or mint another allowance. Work units are codec visits, not native engine replay. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0019

[Lines 102–107](../../../../../../include/crown/recovery/journal.hpp#L102); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PendingView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow pending WAL input frame while carrying fixed continuity metadata. |
| inputs / outputs | Ordinal/next_substep/InputMetadata/input SHA plus string_view frame. |
| invariants | Complete pending input can survive partial window commit; not a disposable torn suffix. |
| ownership | Owns fixed copies only; frame borrows immutable caller/File pending buffer until changed/moved/destroyed. |
| failure | Record construction no validation/lifetime retention. |
| cost | O(1) fixed/view copy, no allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 108–115](../../../../../../include/crown/recovery/journal.hpp#L108); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Scanned {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe current validated prefix and optional pending borrow. |
| inputs / outputs | Header, record/work/physical/command counters, reader bytes, consumed/last boundaries, torn flag, optional PendingView. |
| invariants | No allocation allowance or durable/native decision granted by snapshot. A complete bad-checksum record rejects; only validated incomplete final suffix is torn. |
| ownership | Fixed metadata plus borrowed pending frame; caller must retain original bytes or File owner until use ends. |
| failure | Public copy can be made freely but cannot seed Cursor; actual validator rejects malformed transitions. |
| cost | O(1) fixed copy, no allocation; prior scan/hash CPU already spent. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0021

[Lines 116–123](../../../../../../include/crown/recovery/journal.hpp#L116); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Scanned scan(std::string_view,ScanLimits={},const Header* expected=nullptr);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a complete framed WAL prefix without materializing inputs. |
| inputs / outputs | Immutable borrowed bytes, ScanLimits and optional expected Header; return Scanned. |
| invariants | Require valid header/contiguous ordinals/input hashes/physical-vs-metadata/substep/completion/reader progression and checkpoint boundaries. Only incomplete suffix after valid header accepted as torn; complete corrupt frame rejects. |
| ownership | No heap graph/file owner; pending frame borrows caller prefix. expected Header used synchronously. |
| failure | Typed journal Failure on corruption/binding/work/limits, no repair/native replay/IO. |
| cost | O(total byte/hash/structural visits+CSV permutation comparisons), fixed continuation, no allocation/clock. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0022

[Lines 124–141](../../../../../../include/crown/recovery/journal.hpp#L124); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Cursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own bounded WAL continuation authority without owning frame bytes. |
| inputs / outputs | Fixed limits/optional copied expected header/state and active flag; noncopyable with explicit consuming moves. |
| invariants | Only successful feed/tail publication advances continuation/work. Failed validation leaves old State/budget unchanged; actual CPU from failed retries is not accumulated in stored work. Scanned labels cannot resume it. |
| ownership | No dynamic graph/account/file; state.pending.frame borrows last input bytes, which caller keeps immutable/live across continuation use. |
| failure | Invalid/moved-from feed rejects; fixed Failure, not an allocating recovery path. |
| cost | Construction/state copy O(1), feed/tail actual frame visits; moves fixed and deactivate source. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit Cursor(ScanLimits={},const Header* expected=nullptr);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize one WAL validator and copy expected header. |
| inputs / outputs | Copies ScanLimits and optional expected Header, State default, active true. |
| invariants | No header/frame validation yet; expected pointer not retained. |
| ownership | Only fixed values owned. |
| failure | Constructor current implementation no throwing operation, signature not noexcept. |
| cost | O(1) fixed copy, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Cursor(const Cursor&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject Cursor copy construction. |
| inputs / outputs | Deleted operation. |
| invariants | Prevents duplicating live continuation/allowance from validator value. |
| ownership | Only one active logical validator owner; Scanned remains descriptive copy. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Cursor& operator=(const Cursor&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject Cursor copy assignment. |
| inputs / outputs | Deleted operation. |
| invariants | Prevents duplicating live continuation/allowance from validator value. |
| ownership | Only one active logical validator owner; Scanned remains descriptive copy. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Cursor(Cursor&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume Cursor by move construction. |
| inputs / outputs | Copies fixed limits/expected/state/active, then source inactive and state empty; assignment self-checks. |
| invariants | Both validator states are not independently usable after move. Pending frame view still borrows same backing; no byte copy. |
| ownership | Destination gets continuation authority, not backing ownership. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | Fixed field/view transfer, no allocation/IO. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Cursor& operator=(Cursor&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume Cursor by move assignment. |
| inputs / outputs | Copies fixed limits/expected/state/active, then source inactive and state empty; assignment self-checks. |
| invariants | Both validator states are not independently usable after move. Pending frame view still borrows same backing; no byte copy. |
| ownership | Destination gets continuation authority, not backing ownership. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | Fixed field/view transfer, no allocation/IO. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Scanned feed(std::string_view full_frame) &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one complete frame then publish continuation. |
| inputs / outputs | Lvalue active Cursor, immutable full frame; derive next from State copy then assign State only on success. |
| invariants | Frame must consume exactly supplied bytes and satisfy ordinal/expected/header/pending progression within same cumulative limits. Failed feed does not mutate old state or stored work. |
| ownership | Pending views borrow caller bytes; old pending backing must remain through validations that reference it. |
| failure | journal Failure on moved inactive/malformed/resource input; no partial continuation publication. |
| cost | O(frame bytes+checksums+CSV F²), no allocation; failed retries still consume real CPU not reflected in unchanged State. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Scanned finish_tail(std::string_view incomplete_tail) &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate only a final incomplete suffix and publish torn-tail metadata. |
| inputs / outputs | Active lvalue Cursor and borrowed tail; empty returns State unchanged. |
| invariants | Complete supplied frame is rejected by this method; incomplete accepted only after valid prior header. No truncation/flush/retirement done. |
| ownership | Returned state retains only earlier pending frame borrow, not incomplete tail payload. |
| failure | Validate on copy, reject before State publication; failed call leaves old continuation/work. |
| cost | O(tail-prefix validation/hash visits), fixed temporary, no allocation/IO. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Scanned state() const noexcept {return state_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy current validator metadata. |
| inputs / outputs | Returns Scanned state_ by value, even inactive moved-from default. |
| invariants | Copy does not mint continuation/record/work allowance or durability. |
| ownership | Pending view still borrows caller bytes, no backing retained. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

```text
ScanLimits limits_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one validator allowance and borrowed continuation. |
| inputs / outputs | Private Limits, copied optional expected Header, Scanned and active flag. |
| invariants | No constructor accepts arbitrary Scanned; only internal validation publishes State. |
| ownership | Fixed fields and pending borrow only; no caller input/account/file ownership. |
| failure | Destruction releases no payload; view lifetime external. |
| cost | Bounded object storage/copy/move, no heap cleanup. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0023

[Lines 142–143](../../../../../../include/crown/recovery/journal.hpp#L142); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr std::size_t frame_prefix_size=84,frame_header_size=148;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set WAL dual-checksum frame sizes. |
| inputs / outputs | frame_prefix_size84, frame_header_size148. |
| invariants | Protected length/prefix checksum precede body; header overhead excludes payload and differs from84-byte runtime/session envelope. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/journal.hpp](../../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../../src/recovery/journal.cpp), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |
