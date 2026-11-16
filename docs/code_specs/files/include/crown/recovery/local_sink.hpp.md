# `include/crown/recovery/local_sink.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/local_sink.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Persist canonical complete epoch output and return authority-bearing delivery receipts.

Snapshot SHA-256: `6c6aec2206c303b61c260cc40a5636f47ee774be703d698c6f8eb4cec5a46b4d`. 108 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/recovery/local_sink.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–13](../../../../../../include/crown/recovery/local_sink.hpp#L7) | Type/record definition: struct Header |  · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../../include/crown/recovery/local_sink.hpp#L14) | Type/record definition: struct RowView | growth insert · [reviewed contract](#b0003) |
| [B0004 · 15–15](../../../../../../include/crown/recovery/local_sink.hpp#L15) | Type/record definition: struct Row | growth insert · [reviewed contract](#b0004) |
| [B0005 · 16–16](../../../../../../include/crown/recovery/local_sink.hpp#L16) | Type/record definition: struct Epoch |  · [reviewed contract](#b0005) |
| [B0006 · 17–21](../../../../../../include/crown/recovery/local_sink.hpp#L17) | Type/record definition: struct Limits |  · [reviewed contract](#b0006) |
| [B0007 · 22–22](../../../../../../include/crown/recovery/local_sink.hpp#L22) | Type/record definition: enum class Stage :std::uint8_t |  · [reviewed contract](#b0007) |
| [B0008 · 23–23](../../../../../../include/crown/recovery/local_sink.hpp#L23) | Type/record definition: enum class Fault :std::uint8_t |  · [reviewed contract](#b0008) |
| [B0009 · 24–24](../../../../../../include/crown/recovery/local_sink.hpp#L24) | Type/record definition: enum class Outcome :std::uint8_t |  · [reviewed contract](#b0009) |
| [B0010 · 25–25](../../../../../../include/crown/recovery/local_sink.hpp#L25) | Type/record definition: enum class HeaderMatch :std::uint8_t |  · [reviewed contract](#b0010) |
| [B0011 · 26–36](../../../../../../include/crown/recovery/local_sink.hpp#L26) | Type/record definition: class Failure final:public std::exception | returns fault_; stage_ · [reviewed contract](#b0011) |
| [B0012 · 37–41](../../../../../../include/crown/recovery/local_sink.hpp#L37) | Type/record definition: struct State |  · [reviewed contract](#b0012) |
| [B0013 · 42–46](../../../../../../include/crown/recovery/local_sink.hpp#L42) | Type/record definition: struct Prefix |  · [reviewed contract](#b0013) |
| [B0014 · 47–49](../../../../../../include/crown/recovery/local_sink.hpp#L47) | declares types or opens a type body. | source comment (unverified): // Authority for this bound local sink's complete durable prefix. Descriptive · [reviewed contract](#b0014) |
| [B0015 · 50–65](../../../../../../include/crown/recovery/local_sink.hpp#L50) | Type/record definition: class Receipt | returns header_; prefix_.generation; source comment (unverified): // Authority for this bound local sink's complete durable prefix. Descriptive · [reviewed contract](#b0015) |
| [B0016 · 66–88](../../../../../../include/crown/recovery/local_sink.hpp#L66) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Each complete epoch is canonicalized by sign and exact typed wire bytes; · [reviewed contract](#b0016) |
| [B0017 · 89–90](../../../../../../include/crown/recovery/local_sink.hpp#L89) | Type/record definition: private: struct Index |  · [reviewed contract](#b0017) |
| [B0018 · 91–99](../../../../../../include/crown/recovery/local_sink.hpp#L91) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 100–100](../../../../../../include/crown/recovery/local_sink.hpp#L100) | Type/record definition: struct stat stamp_ |  · [reviewed contract](#b0019) |
| [B0020 · 101–108](../../../../../../include/crown/recovery/local_sink.hpp#L101) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::recovery::sink · [reviewed contract](#b0020) |

## B0001

[Lines 1–6](../../../../../../include/crown/recovery/local_sink.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose native local durable epoch sink protocol. |
| inputs / outputs | Includes funded image/scalar views and Linux stat. |
| invariants | Sink signs/typed wire values define canonical epoch; filesystem namespace trusted/cooperating writer required. |
| ownership | No File/Receipt created at inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 7–13](../../../../../../include/crown/recovery/local_sink.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool operator==(const Header&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare sink headers. |
| inputs / outputs | Default equality compares IDs/runtime binding/origin frontier/schema fields. |
| invariants | Value equality does not prove actual source/native admission, live file/lock ownership or durable acceptance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Bounded fixed-member comparison, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
struct Header {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe expected sink identity/schema/origin. |
| inputs / outputs | Query/sink IDs, runtime binding, first generation/base sequence/field count and schema SHA. |
| invariants | Actual File derives schema hash and validates header. Caller-created header equality does not authenticate file, prefix or output delivery. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 14–14](../../../../../../include/crown/recovery/local_sink.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RowView {SetOperation operation=SetOperation::insert;storage::TupleValuesView values;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one signed native row for whole-epoch canonicalization. |
| inputs / outputs | SetOperation plus TupleValuesView. |
| invariants | Caller keeps complete row/scalar/string backing unchanged through encode/sort/compare; no partial epoch acknowledgment. |
| ownership | View owns no row/source/pin/account. |
| failure | Codec validates sign/types/schema/UTF8 wire strings at use, construction validates nothing. |
| cost | O(1) view copy; later encoded byte work separate. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 15–15](../../../../../../include/crown/recovery/local_sink.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Row {SetOperation operation=SetOperation::insert;storage::AccountedRow values;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one native decoded signed sink row. |
| inputs / outputs | Operation plus move-only AccountedRow. |
| invariants | Actual decode copies complete canonical row on receiver account; public fields themselves no durable proof. |
| ownership | One native row block, no supported implicit copy; moves transfer. |
| failure | Decode clone/account failure propagates before output publication. |
| cost | O(row bytes) explicit materialization, fixed block transfer/free. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 16–16](../../../../../../include/crown/recovery/local_sink.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Epoch {std::uint64_t generation=0,sequence=0;ImageVector<Row> rows;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a complete decoded sink epoch. |
| inputs / outputs | Generation/sequence plus ImageVector&lt;Row&gt; with move-only row entries. |
| invariants | Complete File/codec checks precede return; generation/sequence flags alone not durable authority. |
| ownership | Owns receiver vector/row blocks independent of File lifetime; input scratch not retained. Copying move-only row graph not a supported implicit deep clone. |
| failure | Allocation/decode/resource failure unwinds partial epoch. |
| cost | O(epoch bytes/rows) decode, teardown visits row owners plus vector free; moving transfers storage. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 17–21](../../../../../../include/crown/recovery/local_sink.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound sink record/whole-file/IO workloads. |
| inputs / outputs | Record64MiB/512Mi work/65536rows, whole1GiB/work4Gi/epochs+operations1M,path4095,chunk1MiB. |
| invariants | File owns cumulative work/operations. Record limits dynamically shrink to remaining work; native delivery-work budget separate. Byte/scalar compare/hash/IO/account costs distinct. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 22–22](../../../../../../include/crown/recovery/local_sink.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Stage :std::uint8_t {path,open_directory,entropy,create_temporary,open_file,stat_file,lock_file,read_data,write_data,sync_file,link_file,unlink_temporary,sync_directory,truncate_tail,close_file,close_directory,state};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify sink IO/state phase. |
| inputs / outputs | path/open/stat/lock/read/write/sync/link/unlink/truncate/close/state. |
| invariants | Stage separate from operation outcome. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 23–23](../../../../../../include/crown/recovery/local_sink.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Fault :std::uint8_t {io,limit,path,not_regular,busy,changed,truncated,state};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify sink file failure. |
| inputs / outputs | io/limit/path/not_regular/busy/changed/truncated/state. |
| invariants | Codec ImageFailure distinct from sink File Failure. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 24–24](../../../../../../include/crown/recovery/local_sink.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Outcome :std::uint8_t {unchanged,unknown,durable};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe sink attempted operation durability. |
| inputs / outputs | unchanged/unknown/durable. |
| invariants | Unknown requires new actual File/open validation, not same-owner retry; later stat may fail after durable fsync. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 25–25](../../../../../../include/crown/recovery/local_sink.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class HeaderMatch :std::uint8_t {exact,identity};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose sink header admission strictness. |
| inputs / outputs | exact versus identity. |
| invariants | Identity ignores only first_generation/base_sequence; every other Header field, including complete runtime binding and schema, must match. It does not trust caller origin fields. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 26–36](../../../../../../include/crown/recovery/local_sink.hpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Failure final:public std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed sink Failure diagnostics. |
| inputs / outputs | Fault/stage/outcome/errno/temp-cleanup flag. |
| invariants | Actual staged File protocol sets diagnostics; fields are not durable mutation authority. |
| ownership | Only fixed enums/native errno/booleans; what() returns static literal, no dynamic message or authority owner. |
| failure | Constructor/getters noexcept; constructing this public diagnostic itself does not prove a file effect or grant recovery authority. |
| cost | Fixed object construction/copy/getters, no dynamic message formatting or IO. Throw/unwind still has normal C++ ABI/stack cost and can require exception storage outside the query payload model. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Failure(Fault fault,Stage stage,Outcome outcome,int error=0,bool cleanup=false) noexcept:fault_(fault),stage_(stage),outcome_(outcome),error_(error),cleanup_(cleanup) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct sink Failure. |
| inputs / outputs | Stores supplied fixed diagnostic fields. |
| invariants | Actual implementation chooses phase/outcome; caller-created fields are descriptive only. |
| ownership | Inline values only; no file/runtime retained. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Fault fault() const noexcept{return fault_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read sink Failure fault. |
| inputs / outputs | Returns stored fault by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Stage stage() const noexcept{return stage_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read sink Failure stage. |
| inputs / outputs | Returns stored stage by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Outcome outcome() const noexcept{return outcome_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read sink Failure outcome. |
| inputs / outputs | Returns stored outcome by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] int native_error() const noexcept{return error_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read sink Failure native error. |
| inputs / outputs | Returns stored native error by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool temporary_cleanup_failed() const noexcept{return cleanup_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read sink Failure temporary cleanup failure. |
| inputs / outputs | Returns stored temporary cleanup failure by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const char* what() const noexcept override{return "local sink file operation failed";}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read sink Failure static message. |
| inputs / outputs | Returns constant what() literal. |
| invariants | Message is diagnostic label, not serialized recovery proof. |
| ownership | Static storage; pointer does not depend on exception lifetime. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 37–41](../../../../../../include/crown/recovery/local_sink.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct State {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report persisted admitted sink prefix and buffer/health counters. |
| inputs / outputs | Header, epochs/generation/sequence/bytes/work/operations/buffer bytes,torn_tail/recovery_required. |
| invariants | State is descriptive, available on poisoned open File with recovery_required=true. It cannot construct Receipt or authorize retirement. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 42–46](../../../../../../include/crown/recovery/local_sink.hpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Prefix {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one complete sink prefix fingerprint. |
| inputs / outputs | Generation/sequence/end byte offset and chained content SHA. |
| invariants | Actual admitted File supplies it, but returned Prefix remains descriptive; receipt and native generation retirement checks separate. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const Prefix&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare sink prefixes. |
| inputs / outputs | Default equality compares generation/sequence/bytes/chained hash. |
| invariants | Value equality does not prove actual source/native admission, live file/lock ownership or durable acceptance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Bounded fixed-member comparison, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 47–49](../../../../../../include/crown/recovery/local_sink.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class File;
// Authority for this bound local sink's complete durable prefix. Descriptive
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward File as the only receipt constructor authority. |
| inputs / outputs | Private Receipt friendship follows File forward declaration. |
| invariants | Descriptive State/Prefix/frontiers cannot public-construct the capability. |
| ownership | No File/lock instantiated here. |
| failure | Compile-time access boundary. |
| cost | No runtime action. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 50–65](../../../../../../include/crown/recovery/local_sink.hpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Receipt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry immutable actual File-minted durable-prefix receipt. |
| inputs / outputs | Private const Header/Prefix, public copy-only value/accessors; only File constructs from healthy complete admitted prefix. |
| invariants | Capability relies on trusted namespace/files. It does not retain open fd/flock or promise external namespace cannot change; generation retirement independently checks actual checkpoint/prefix/lineage. |
| ownership | Owns fixed arrays/scalars only, not File/account/lock; copying receipt copies actual authorized values, no shared graph. |
| failure | Fixed noexcept copy/getters; no public metadata-to-receipt constructor or assignment. |
| cost | Bounded fixed copy/release, no IO/heap/hash during receipt copy. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Receipt(const Receipt& other) noexcept:header_(other.header_),prefix_(other.prefix_) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a File-minted receipt. |
| inputs / outputs | Copies const Header and Prefix. |
| invariants | Copy does not perform new IO or extend File lock. |
| ownership | Independent fixed capability value only. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Receipt& operator=(const Receipt&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject receipt assignment. |
| inputs / outputs | Copy assignment deleted; const members remain immutable. |
| invariants | Prevents mutable relabeling through assignment; copy construction allowed. |
| ownership | No new owner. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Header header() const noexcept{return header_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read receipt header. |
| inputs / outputs | Returns Header by value. |
| invariants | No new file validation, mutation, hash or durability acquired. |
| ownership | Fixed copied return; no backing borrow. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::uint64_t generation() const noexcept{return prefix_.generation;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read receipt generation. |
| inputs / outputs | Returns U64 by value. |
| invariants | No new file validation, mutation, hash or durability acquired. |
| ownership | Fixed copied return; no backing borrow. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::uint64_t sequence() const noexcept{return prefix_.sequence;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read receipt sequence. |
| inputs / outputs | Returns U64 by value. |
| invariants | No new file validation, mutation, hash or durability acquired. |
| ownership | Fixed copied return; no backing borrow. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::uint64_t bytes() const noexcept{return prefix_.bytes;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read receipt bytes. |
| inputs / outputs | Returns U64 by value. |
| invariants | No new file validation, mutation, hash or durability acquired. |
| ownership | Fixed copied return; no backing borrow. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::array<char,64> content_sha256() const noexcept{return prefix_.content_sha256;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read receipt chained content digest. |
| inputs / outputs | Returns array&lt;char,64&gt; by value. |
| invariants | No new file validation, mutation, hash or durability acquired. |
| ownership | Fixed copied return; no backing borrow. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
Receipt(const Header& header,const Prefix& prefix) noexcept:header_(header),prefix_(prefix) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mint receipt from actual healthy File prefix. |
| inputs / outputs | Private friend copies Header/Prefix supplied by File::receipt. |
| invariants | File separately requires ready/no torn tail; caller DTOs cannot invoke constructor. |
| ownership | Fixed values only, no fd/account retained. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
const Header header_;const Prefix prefix_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store immutable receipt identity and prefix. |
| inputs / outputs | const Header header_; const Prefix prefix_. |
| invariants | No public mutation or authority minting from plain Prefix. |
| ownership | Fixed inline fields, independent from original File object lifetime. |
| failure | No runtime validation here; provenance comes from private constructor. |
| cost | Bounded storage and trivial teardown. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0016

[Lines 66–88](../../../../../../include/crown/recovery/local_sink.hpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class File {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own actual canonical durable sink file and advisory lock. |
| inputs / outputs | Account, validated Header/schema/index/scratch/other buffers, fd/stat, cumulative work/operations/bytes and health/outcome. |
| invariants | Whole epoch canonical sign+typed wire bytes exclude producer ordinal/layout/order. File alone mints receipt, state is descriptive. Own File single-writer under trusted namespace. |
| ownership | Actual fd/flock and original account; schema/index/bytes funded on same account, copied only by explicit codec; File noncopyable. |
| failure | IO failures/poison/outcomes remain staged; pure pre/post-read validation failures are distinct. No generic rollback of uncertain mutation. |
| cost | Open scans full prefix; append encodes/sorts whole epoch, exact duplicate read/byte compare; indexed read decodes one frame; prefix/receipt fixed lookup. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static File create(const resource::MemoryAccount&,std::string_view,const Header&,std::span<const ScalarType>,Limits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a new bound durable sink without overwrite. |
| inputs / outputs | Actual account/path/Header/schema/limits. Derive schema hash, canonical encode header before publishing. |
| invariants | Exclusive temp+flock/write/file fsync/linkat no-overwrite/unlinktemp/dirfsync then stamp/close. Existing file/symlink never replaced. |
| ownership | Unique fd/schema/index/buffers on actual account; path/schema only borrowed through setup. |
| failure | Header/codec/OOM failures before link leave no name authority; File Failure cleanup annotates temp failure; link uncertain not retried. |
| cost | Schema O(F) buffer/hash, header codec, bounded entropy/temp attempts, write/fsync/link/dirsync/stat; real syscall/account caps. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static File open(const resource::MemoryAccount&,std::string_view,const Header&,std::span<const ScalarType>,Limits={},HeaderMatch=HeaderMatch::exact);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open/admit a complete sink prefix and optional valid torn suffix. |
| inputs / outputs | Account/path/Header/schema/Limits/HeaderMatch. |
| invariants | No-follow regular file/exclusive flock; validate header/mode/schema, every complete canonical epoch/ordinal/generation/hash chain; EOF/stat/file+name sync before success. Torn suffix not repaired here. |
| ownership | Owns fd/lock and native schema/index/scratch on receiver account. HeaderMatch identity discovers origin only under actual checks. |
| failure | Malformed complete frame, binding/IO/limit/OOM rejects; no native output marked delivered by open alone. |
| cost | O(file bytes+epoch row codec comparisons) scan/hash, grow index/scratch, sync file/directory; not fixed header-only operation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
~File();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy sink File by best-effort close. |
| inputs / outputs | raw_close(fd_) preserves errno; member buffers/accounts destruct. |
| invariants | Use close for checked close; destructor does not repair/unlink/history retire. |
| ownership | Releases actual fd/flock and schema/index/scratch buffers/account. |
| failure | Nonthrowing, no allocation. |
| cost | One raw close, fixed number trivial buffer frees/account release. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
File(const File&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject sink File copy construction. |
| inputs / outputs | Deleted operation. |
| invariants | Cannot duplicate actual fd/lock/cumulative prefix authority by value. |
| ownership | Unique live File. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
File& operator=(const File&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject sink File copy assignment. |
| inputs / outputs | Deleted operation. |
| invariants | Cannot duplicate actual fd/lock/cumulative prefix authority by value. |
| ownership | Unique live File. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
File(File&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume sink File by move construction. |
| inputs / outputs | Transfers native vectors/fd and fixed header/stat/counters; source fd=-1/poisoned, account shared-retained. |
| invariants | Moved source has no live File authority, vector storage not copied. |
| ownership | Destination owns actual fd/flock/buffers/account. |
| failure | noexcept. |
| cost | Fixed ownership/handle transfer, no IO/allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
File& operator=(File&&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject sink File move assignment. |
| inputs / outputs | Deleted operation. |
| invariants | No overwrite of live fd/lock/prefix lifecycle. |
| ownership | Move construction only. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] State state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read persisted sink state including poison. |
| inputs / outputs | Requires fd open but does not call ready; returns header/frontiers/work/operations and actual vector requested bytes/torn/poison. |
| invariants | Poisoned state is explicitly recovery_required. State/frontiers are not Receipt or same-owner mutation permission. |
| ownership | Fixed returned record; array allocations remain File-owned. |
| failure | Closed→sink Failure(state); exact allocation_usage reads may expose contract failure if corrupted. |
| cost | O(1) index back/counter/four allocation-header reads; no file IO/hash/ledger scan. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Receipt receipt() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mint receipt for healthy complete admitted sink prefix. |
| inputs / outputs | ready and !torn, then private Receipt(header,prefix(latest)). |
| invariants | No receipt for poisoned/torn File. Still requires trusted namespace and independent retirement source/checkpoint checks. |
| ownership | Returned fixed capability retains no fd/flock/account. |
| failure | Typed state Failure when unavailable. |
| cost | O(1) stored metadata/index lookup, no IO/allocation/hash. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Prefix prefix(std::uint64_t sequence) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read descriptive admitted prefix by contiguous sequence. |
| inputs / outputs | Healthy ready File; sequence in \[base,base+index.size\], return header prefix for base else indexed entry end/hash. |
| invariants | Lookup does not read file or grant receipt/retirement authority. Valid existing prefix readable with healthy torn tail for verification before repair. |
| ownership | Fixed copy only; no row/file borrow returned. |
| failure | State failure if closed/poison; ImageFailure(binding) for out-of-range sequence. |
| cost | O(1) ordinal index lookup/fixed hash copy, no allocation/IO. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool append(std::uint64_t generation,std::uint64_t sequence,std::span<const RowView>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append whole canonical epoch or verify exact durable duplicate. |
| inputs / outputs | Healthy nontorn File,generation/next-or-existing sequence, stable span&lt;RowView&gt;. |
| invariants | Encode/freeze/sort complete typed signed bytes and fund index growth before write. Duplicate compares entire persisted encoded bytes, not digest/ordinal alone; false only identical already-durable epoch. |
| ownership | Account-funded encoded/scratch/index buffers, row views borrowed synchronously; schema/epoch canonical codec rejects duplicate signed rows. |
| failure | Pre-write limits/OOM/codec failure no mutation. During actual read/write/stat owner poisoned; pure duplicate compare/work error after completed read occurs after poison cleared. Append write/sync/stat failure may require reopen even if durable. |
| cost | O(epoch bytes+R log R signed-byte comparisons) encode/sort/hash; duplicate reads/compares one frame, append chunk write/fsync/stat+index fixed push, all actual costs cumulative. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void verify_epoch(std::uint64_t generation,std::uint64_t sequence,std::span<const RowView>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one already accepted complete epoch without writing. |
| inputs / outputs | ready File plus generation/sequence/rows; delegates verify_only accept_epoch. |
| invariants | Requires existing ordinal; valid torn tail allowed so native recovery validates sink coverage before deciding repair. Full canonical bytes compared. |
| ownership | Funded encode/compare buffers; no native output backlog retained by File. |
| failure | IO/poison/limit/codec/binding mismatches propagate; complete read clears poison before pure compare failure. |
| cost | Same canonical encode/sort and requested-frame read/byte compare as duplicate append; no write/fsync mutation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Epoch read_epoch(std::uint64_t sequence);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one admitted sink epoch into independent native rows. |
| inputs / outputs | Healthy File and sequence strictly afterbase through indexed end. |
| invariants | O(1) validated index chooses exact frame; stat/read/stat then clear poison before inspect/decode. Requires generation/sequence/ordinal match and reserves remaining parse work. |
| ownership | Returned native Epoch owns receiver arrays/row blocks beyond File lifetime; scratch remains File-owned. |
| failure | IO/stat failure poisons; later inspect/limit/decode failures propagate after successful read without claiming every failure poisons. |
| cost | O(frame bytes/rows) read/hash/inspect and two-pass decode with cell scratch/output allocations, plus fixed index lookup/two fstats. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void repair_tail();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Repair only valid incomplete sink suffix. |
| inputs / outputs | ready; nontorn no-op, else poison/stat/ftruncate(bytes_)/fsync/refresh then clear torn/poison. |
| invariants | Every complete accepted epoch and index/prefix stays intact. Native recovery validates source/sink first. |
| ownership | Same actual fd/flock, no new graph. |
| failure | IO failure retains poison and staged unchanged/unknown/durable outcome. |
| cost | Fixed syscall sequence, no complete-prefix rescan or allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void close();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close sink fd with checked outcome. |
| inputs / outputs | Detach fd then checked close, including poisoned File. |
| invariants | No retry close on EINTR/EIO; repeated close rejects. |
| ownership | Releases fd/flock, buffers/account remain until destruction. |
| failure | Typed state/IO/limit failure after actual descriptor detachment. |
| cost | One charged close attempt, no allocation/scan. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 89–90](../../../../../../include/crown/recovery/local_sink.hpp#L89); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Index {std::uint64_t generation=0,offset=0,size=0;std::array<char,64> content_sha256{};};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain fixed actual admitted epoch-index entry. |
| inputs / outputs | Generation/offset/size/chained content SHA. |
| invariants | Only File successful open/append populates entry; copied numeric fields alone do not recreate live File authority. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 91–99](../../../../../../include/crown/recovery/local_sink.hpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
File(const resource::MemoryAccount&,const Header&,std::span<const ScalarType>,Limits);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize private sink schema and original account. |
| inputs / outputs | Account/Header/schema/Limits bind native arrays, consume1024+4F work, derive/compare schema hash and copy schema. |
| invariants | Header.field count/digest must match supplied schema; full header/policy validation follows header codec. |
| ownership | Retains original account; schema/hash scratch allocate on it, fd remains-1 before create/open. |
| failure | ImageFailure(work/limit/binding/scalar)/OOM unwinds private object before File publication. |
| cost | O(F) schema buffer/hash/copy plus fixed metadata; actual allocations separate from work cap. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void ready() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check healthy sink owner. |
| inputs / outputs | Reject fd&lt;0 or poisoned. |
| invariants | Torn flag checked separately by append/receipt; verify_epoch may still use valid complete prefix. |
| ownership | No new owner; actual File retains account/fd/flock. |
| failure | Fixed sink Failure(state,unchanged). |
| cost | O(1), no allocation/IO. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void consume(std::uint64_t);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge cumulative sink codec work. |
| inputs / outputs | Require amount&lt;=limits.work-work_, then increment. |
| invariants | Owner private invariant work&lt;=cap, no saturation/refund or new allowance. |
| ownership | No new owner; actual File retains account/fd/flock. |
| failure | ImageFailure(work) before rejected increment. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void refresh();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Refresh sink stat after successful mutation. |
| inputs / outputs | Checked fstat into owned stamp. |
| invariants | A successful fsync can precede failed refresh while outcome remains durable and poison active. |
| ownership | No new owner; actual File retains account/fd/flock. |
| failure | Staged IO/limit Failure. |
| cost | One charged fstat, fixed metadata. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void unchanged_file();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check admitted sink inode/stamp unchanged. |
| inputs / outputs | Checked fstat then compare dev/inode/size/mtime/ctime. |
| invariants | Does not update baseline or replace lock; external mismatch rejects actual owner use. |
| ownership | No new owner; actual File retains account/fd/flock. |
| failure | Changed/IO/limit Failure with current outcome. |
| cost | One charged fstat/fixed comparisons, no allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ImageLimits record_limits() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Limit next sink record to remaining owner work. |
| inputs / outputs | Copies Limits.record and sets work=min(record.work,limits.work-work_). |
| invariants | Per-record and cumulative File caps compose; copied public ImageLimits cannot alter File allowance. |
| ownership | Returns fixed value, no payload. |
| failure | Current private work invariant; no throwing operation, signature not noexcept. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool accept_epoch(std::uint64_t,std::uint64_t,std::span<const RowView>,bool verify_only);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Centralize new/duplicate/verify-only whole-epoch processing. |
| inputs / outputs | Private generation/sequence/borrowed rows/verify flag. |
| invariants | ready, allowed torn onlyverify, contiguous new ordinals, positive/nondecreasing lineage; preencode/indexreserve before write, full persisted byte equality for duplicates. |
| ownership | Actual account owns encoded/other/index storage; caller rows not retained after return. |
| failure | Pure errors before IO leave owner healthy; IO/stat phase poison; duplicate pure compare errors after read clear poison; new write fsync/refresh must complete before index publication. |
| cost | Whole epoch encoding/sorting/hash, duplicate frame IO+2B compare charge or new frame write/fsync and chain hash/index capacity; no lazy row acknowledgment. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
std::int64_t call(Stage,std::size_t=0,int=-1,const char* =nullptr,int=-1,const char* =nullptr,void* =nullptr,std::uint64_t=0,struct stat* =nullptr,bool emergency_cleanup=false);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch one bounded sink syscall. |
| inputs / outputs | Stage/arguments/buffer/offset/stat; increments actual operations, invokes test hook only testing build, returns result with errno. |
| invariants | Mutation syscall admission (write/truncate/link) marks unknown conservatively even if interrupted. Mandatory cleanup unlinks bypass ordinary op cap but UINT64 overflow still rejects. Closing detaches/releases fd even at cap. Only the explicit emergency_cleanup flag from the eight-attempt failure helper bypasses the ordinary operation cap; normal post-link unlink/EINTR does not. |
| ownership | Borrow arguments only for syscall; actual File keeps descriptor/lock; no heap message. |
| failure | Typed File failure on limits/state; IO errno left for checked; test hook behavior not a production service. |
| cost | One syscall attempt/fixed accounting; no allocation. Actual blocking IO/fsync cost not modeled as constant CPU. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md), [tests/unit/file_cleanup_quota_test.cpp](../../../../../../tests/unit/file_cleanup_quota_test.cpp) |

```text
std::int64_t checked(Stage,std::size_t=0,int=-1,const char* =nullptr,int=-1,const char* =nullptr,void* =nullptr,std::uint64_t=0,struct stat* =nullptr);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check sink syscall with exact retry policy. |
| inputs / outputs | Calls dispatch until nonnegative or nonretryable error. |
| invariants | Retries EINTR except close and link publication; lock EWOULDBLOCK/EAGAIN becomes busy. Never retries uncertain publication. |
| ownership | No new owner/buffer retained. |
| failure | Throws fixed staged File failure including errno/outcome; ordinary operation cap bounds retries. |
| cost | One charge per attempt, no allocation/formatting; actual syscall latency explicit. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void transfer(bool,char*,std::size_t,std::uint64_t);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer exact sink bytes in bounded chunks. |
| inputs / outputs | Read/write, borrowed char buffer,size,offset; loop until full transfer. |
| invariants | Chunk limit, short transfer and EINTR handling real; zero read→truncated, zero write→IO/EIO. |
| ownership | Buffer must stay writable/readable for call; actual fd retained by File. |
| failure | Checked stage/limit/IO failure propagates current outcome; mutating caller has already arranged poison. |
| cost | O(bytes) transfer and ceil(bytes/chunk) minimum successful syscalls, short/EINTR may add; no new payload allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool cleanup_temporary(int,const char*) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clean sink temporary under bounded emergency retry. |
| inputs / outputs | unlink_temporary up to8 attempts; success or ENOENT true, otherwise false. |
| invariants | Outside ordinary IO cap to permit cleanup, still overflow guarded. Cleanup does not roll back an installed destination or durable prefix. This fixed helper alone requests emergency_cleanup; normal publication cannot inherit the exemption by syscall stage. |
| ownership | Borrows directory fd/name, retains no extra owner. |
| failure | noexcept catch converts cleanup error to false for outer diagnostic; this catch is necessary error-report boundary. |
| cost | At most8 unlink attempts, no allocation/scan. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md), [tests/unit/file_cleanup_quota_test.cpp](../../../../../../tests/unit/file_cleanup_quota_test.cpp) |

```text
resource::MemoryAccount account_;Header header_;Limits limits_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual sink account/header/limits. |
| inputs / outputs | MemoryAccount account_, copied Header and fixed Limits. |
| invariants | Original account is retained authority for allocations, header is descriptive expected lineage. No fresh grant on moves/copies. |
| ownership | File owns account handle and fd elsewhere; fixed header not row/native authority. |
| failure | No runtime action in declarations. |
| cost | Fixed storage/copy; last account released after buffers. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
ImageVector<ScalarType> schema_;ImageVector<Index> index_;ImageVector<char> scratch_,other_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own native schema/index and IO/compare buffers. |
| inputs / outputs | Four ImageVectors for schema types, fixed Index entries, scratch and duplicate comparison bytes. |
| invariants | Capacity/account requests remain real while File lives; record buffers are not native result row mirrors. |
| ownership | Same account via image_allocator; no source views retained in vectors. |
| failure | Growth may throw in private encode/open/append phases before mutation where designed. |
| cost | Schema O(F), index O(epochs), scratch/comparison O(frame bytes); release four trivial-element buffers, no byte scan. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0019

[Lines 100–100](../../../../../../include/crown/recovery/local_sink.hpp#L100); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int fd_=-1;struct stat stamp_{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own actual sink descriptor/lock and fixed stat baseline. |
| inputs / outputs | fd_ default-1, struct stat stamp_. |
| invariants | Move transfers fd then invalidates source; numeric stamp copy does not duplicate authority. |
| ownership | Unique actual fd/flock with best-effort destructor close. |
| failure | Checked protocol operations can throw; destructor release no allocation. |
| cost | Fixed metadata; one close at final descriptor release. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 101–108](../../../../../../include/crown/recovery/local_sink.hpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t operations_=0,work_=0,bytes_=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store cumulative sink counters and health/prefix diagnostics. |
| inputs / outputs | operations/work/bytes/header bytes/header chain checksum/outcome/poison/torn. |
| invariants | Counters/private index govern actual prefix; State copies never authorize receipt, continuation budget or retirement. |
| ownership | Fixed fields only; actual buffers/fd retained elsewhere in File. |
| failure | No validation at declaration; methods enforce phases. |
| cost | Bounded storage/reads, no heap/IO. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::array<char,64> schema_sha256(const resource::MemoryAccount&,std::span<const ScalarType>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash exact sink scalar schema using original-account scratch. |
| inputs / outputs | Account and borrowed ScalarType span return fixed64 hex SHA. |
| invariants | Require each scalar enum supported0..4; field order matters. Hash is descriptive until actual File checks it. |
| ownership | Temporary funded char vector copies one byte per type, released before return; span not retained. |
| failure | ImageFailure(scalar)/account/OOM propagates; no File mutation. |
| cost | O(F) allocate/copy/hash type bytes; not an allocation-free scalar helper. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

```text
inline constexpr std::size_t frame_prefix_size=84,frame_header_size=148;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set sink dual-checksum frame sizes. |
| inputs / outputs | Prefix84, full header148 bytes. |
| invariants | Body/prefix hash framing matches sink codec; physical output order/ordinals excluded from semantic canonical row identity. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/local_sink.hpp](../../../../../../include/crown/recovery/local_sink.hpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [src/recovery/local_sink_codec.cpp](../../../../../../src/recovery/local_sink_codec.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |
