# `include/crown/recovery/generation.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/generation.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Read/publish durable generation roots with exact identity and selection outcome.

Snapshot SHA-256: `0111e886c98bd5734079f5c849ba839c8422932b34ca6b5cd34f3558d140ed09`. 65 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/recovery/generation.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–15](../../../../../../include/crown/recovery/generation.hpp#L10) | Type/record definition: enum class GenerationStage : std::uint8_t |  · [reviewed contract](#b0002) |
| [B0003 · 16–16](../../../../../../include/crown/recovery/generation.hpp#L16) | Type/record definition: enum class GenerationTarget : std::uint8_t |  · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../../include/crown/recovery/generation.hpp#L17) | Type/record definition: enum class GenerationFault : std::uint8_t |  · [reviewed contract](#b0004) |
| [B0005 · 18–19](../../../../../../include/crown/recovery/generation.hpp#L18) | Explanatory comments or spacing. | source comment (unverified): // Concerns root selection, not unselected candidate/temporary creation. Unknown · [reviewed contract](#b0005) |
| [B0006 · 20–20](../../../../../../include/crown/recovery/generation.hpp#L20) | Type/record definition: enum class GenerationOutcome : std::uint8_t | source comment (unverified): // Concerns root selection, not unselected candidate/temporary creation. Unknown · [reviewed contract](#b0006) |
| [B0007 · 21–33](../../../../../../include/crown/recovery/generation.hpp#L21) | Type/record definition: class GenerationFailure final:public std::exception | returns fault_; stage_ · [reviewed contract](#b0007) |
| [B0008 · 34–38](../../../../../../include/crown/recovery/generation.hpp#L34) | Type/record definition: struct GenerationLimits |  · [reviewed contract](#b0008) |
| [B0009 · 39–44](../../../../../../include/crown/recovery/generation.hpp#L39) | Type/record definition: struct GenerationDeliveryAnchor |  · [reviewed contract](#b0009) |
| [B0010 · 45–55](../../../../../../include/crown/recovery/generation.hpp#L45) | Type/record definition: struct GenerationRoot | source comment (unverified): // v3 binds a self-contained descriptor at this generation's own .plan path. · [reviewed contract](#b0010) |
| [B0011 · 56–65](../../../../../../include/crown/recovery/generation.hpp#L56) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Checksummed CROWNGR1: v1 is the 212-byte native selection; v2 adds the durable · [reviewed contract](#b0011) |

## B0001

[Lines 1–9](../../../../../../include/crown/recovery/generation.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose bounded generation metadata and fixed errors. |
| inputs / outputs | Includes fixed arrays/options and exception/string_view types. |
| invariants | Local durable root protocols are engineering contracts, not paper theorems. Inspection does not open/lock/mutate root. |
| ownership | No owner or storage allocated by inclusion. |
| failure | Compile-time declarations only. |
| cost | No runtime action at inclusion. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 10–15](../../../../../../include/crown/recovery/generation.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class GenerationStage : std::uint8_t {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify actual generation IO phase. |
| inputs / outputs | Path/open/lock/stat/read/temp/write/sync/close/link/rename/unlink/state/retirement phases. |
| invariants | Stage identifies where native code failed, independently of root selection outcome. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 16–16](../../../../../../include/crown/recovery/generation.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class GenerationTarget : std::uint8_t {lock,root,checkpoint,journal,retirement,plan};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify generation file role. |
| inputs / outputs | lock/root/checkpoint/journal/retirement/plan. |
| invariants | A path-role tag is not authority to mutate that file. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 17–17](../../../../../../include/crown/recovery/generation.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class GenerationFault : std::uint8_t {io,limit,path,not_regular,busy,changed,truncated,corrupt,binding,state};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify generation failure. |
| inputs / outputs | IO/limit/path/nonregular/busy/changed/truncated/corrupt/binding/state. |
| invariants | Actual root owner determines failure stage/outcome, not this tag alone. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 18–19](../../../../../../include/crown/recovery/generation.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L19:sha256:8684a29cac96898058229f096e1d893f8605fc1344bd9a73736553b5a044a1ce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Concerns root selection, not unselected candidate/temporary creation. Unknown requires releasing the old owner and reopening the authoritative root. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/generation.hpp lines 16-21; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [docs/code_specs/files/include/crown/recovery/generation.hpp.md](generation.hpp.md), [docs/generations.md](../../../../../generations.md), [docs/history-retirement.md](../../../../../history-retirement.md) |

## B0006

[Lines 20–20](../../../../../../include/crown/recovery/generation.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class GenerationOutcome : std::uint8_t {unchanged,unknown,durable};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe attempted durable root selection outcome. |
| inputs / outputs | unchanged/unknown/durable. |
| invariants | Concerns root selection, not unselected candidate/temp creation. Unknown requires releasing old owner and reopening authoritative root; it never means rollback all candidate files. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 21–33](../../../../../../include/crown/recovery/generation.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class GenerationFailure final:public std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed GenerationFailure diagnostics. |
| inputs / outputs | Fault/stage/outcome/native error/temp-cleanup flag. |
| invariants | Outcome remains about actual root selection; an already durable root can coexist with later checked-close failure. |
| ownership | Only fixed enums/native errno/booleans; what() returns static literal, no dynamic message or authority owner. |
| failure | Constructor/getters noexcept; constructing this public diagnostic itself does not prove a file effect or grant recovery authority. |
| cost | Fixed object construction/copy/getters, no dynamic message formatting or IO. Throw/unwind still has normal C++ ABI/stack cost and can require exception storage outside the query payload model. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
GenerationFailure(GenerationFault fault,GenerationStage stage,GenerationOutcome outcome,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct GenerationFailure. |
| inputs / outputs | Stores supplied fixed diagnostic fields. |
| invariants | Actual implementation chooses phase/outcome; caller-created fields are descriptive only. |
| ownership | Inline values only; no file/runtime retained. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] GenerationFault fault() const noexcept {return fault_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read GenerationFailure fault. |
| inputs / outputs | Returns stored fault by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] GenerationStage stage() const noexcept {return stage_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read GenerationFailure stage. |
| inputs / outputs | Returns stored stage by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] GenerationOutcome outcome() const noexcept {return outcome_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read GenerationFailure outcome. |
| inputs / outputs | Returns stored outcome by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] int native_error() const noexcept {return error_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read GenerationFailure native error. |
| inputs / outputs | Returns stored native error by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool temporary_cleanup_failed() const noexcept {return cleanup_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read GenerationFailure temporary cleanup failure. |
| inputs / outputs | Returns stored temporary cleanup failure by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const char* what() const noexcept override {return "generation operation failed";}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read GenerationFailure static message. |
| inputs / outputs | Returns constant what() literal. |
| invariants | Message is diagnostic label, not serialized recovery proof. |
| ownership | Static storage; pointer does not depend on exception lifetime. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 34–38](../../../../../../include/crown/recovery/generation.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GenerationLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound actual generation root/file operations. |
| inputs / outputs | Path4095/chunk1MiB, syscall operations1M, checkpoint128MiB, validation1Gi-action and plan64MiB caps. |
| invariants | GenerationOwner validates host/off_t/path bounds. Counters are cumulative per actual owner; public copied limits/state cannot mint more work. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 39–44](../../../../../../include/crown/recovery/generation.hpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GenerationDeliveryAnchor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe an authenticated checkpoint sink-prefix basis. |
| inputs / outputs | Fixed sink ID, sequence, byte end and prefix content hash. |
| invariants | Anchor must be verified against actual sink File/receipt and selected checkpoint. Descriptive anchor cannot authorize history retirement alone. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const GenerationDeliveryAnchor&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare delivery anchors. |
| inputs / outputs | Default equality compares all ID/sequence/bytes/hash fields. |
| invariants | Value equality does not prove actual source/native admission, live file/lock ownership or durable acceptance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Bounded fixed-member comparison, no allocation/IO/clock. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 45–55](../../../../../../include/crown/recovery/generation.hpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GenerationRoot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe selected generation checkpoint/WAL and optional delivery/plan lineage. |
| inputs / outputs | Query ID/current+first generations, checkpoint hash, physical/command sequences, optional delivery anchor and own-generation descriptor hash. |
| invariants | Fields are public metadata, not held root lock or receipt. v3 descriptor self-contained at selected generation .plan; rotation/retirement need no older plan artifact. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const GenerationRoot&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare generation roots. |
| inputs / outputs | Default equality includes both optional anchor and descriptor hash. |
| invariants | Value equality does not prove actual source/native admission, live file/lock ownership or durable acceptance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Bounded fixed-member comparison, no allocation/IO/clock. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 56–65](../../../../../../include/crown/recovery/generation.hpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] GenerationRoot inspect_generation_root(std::string_view);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect one complete checksummed root without acquiring authority. |
| inputs / outputs | Borrow immutable bytes of exact supported root size; return fixed GenerationRoot. |
| invariants | Validate magic/version/flags/body size/SHA, hex IDs/hashes, retained interval and delivery relation. v1/v2/v3 metadata still grants no mutation/retirement or native program authority. |
| ownership | No input bytes retained, fixed return arrays only; no file/lock/account. |
| failure | Malformed/truncated/binding input throws fixed GenerationFailure at read_data with unchanged root outcome; no IO effect. |
| cost | Hash/parse 212/324/276/388 bytes, fixed bounded stack only, no heap allocation. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
inline constexpr std::size_t generation_root_size=212;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set v1 root wire size. |
| inputs / outputs | Constant 212 bytes. |
| invariants | Includes fixed header/body/final checksum; real root work charges depend on actual variant, not universal212-byte assumption. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
inline constexpr std::size_t generation_root_delivery_size=324;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set v2 delivery root wire size. |
| inputs / outputs | Constant 324 bytes. |
| invariants | Includes fixed header/body/final checksum; real root work charges depend on actual variant, not universal212-byte assumption. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
inline constexpr std::size_t generation_root_plan_size=276;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set v3 descriptor root wire size. |
| inputs / outputs | Constant 276 bytes. |
| invariants | Includes fixed header/body/final checksum; real root work charges depend on actual variant, not universal212-byte assumption. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

```text
inline constexpr std::size_t generation_root_plan_delivery_size=388;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set v3 descriptor+delivery root wire size. |
| inputs / outputs | Constant 388 bytes. |
| invariants | Includes fixed header/body/final checksum; real root work charges depend on actual variant, not universal212-byte assumption. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/generation.hpp](../../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |
