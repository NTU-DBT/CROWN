# `include/crown/recovery/image.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/image.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `c3d3f55c550d72616d95f2fed5fdea40c37c80e9b958ab78797a62386b41a7b3`. 81 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../../include/crown/recovery/image.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–14](../../../../../../include/crown/recovery/image.hpp#L12) | Callable definition: template&lt;class T&gt; \[\[nodiscard\]\] auto image_allocator(const resource::MemoryAccount& account) | calls ; returns resource::OwnerAllocator&lt;T&gt;(account,resource::MemoryPurpose::recovery_log,image_owner) · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../../include/crown/recovery/image.hpp#L15) | Type/record definition: enum class ImageFault |  · [reviewed contract](#b0003) |
| [B0004 · 16–23](../../../../../../include/crown/recovery/image.hpp#L16) | Type/record definition: class ImageFailure final:public std::exception | returns fault_; @ · [reviewed contract](#b0004) |
| [B0005 · 24–27](../../../../../../include/crown/recovery/image.hpp#L24) | Type/record definition: struct ImageLimits |  · [reviewed contract](#b0005) |
| [B0006 · 28–29](../../../../../../include/crown/recovery/image.hpp#L28) | Explanatory comments or spacing. | source comment (unverified): // Runtime image component v1. A complete session envelope additionally needs · [reviewed contract](#b0006) |
| [B0007 · 30–35](../../../../../../include/crown/recovery/image.hpp#L30) | Type/record definition: struct ImageBinding | source comment (unverified): // Runtime image component v1. A complete session envelope additionally needs · [reviewed contract](#b0007) |
| [B0008 · 36–40](../../../../../../include/crown/recovery/image.hpp#L36) | Type/record definition: struct ImageManifest |  · [reviewed contract](#b0008) |
| [B0009 · 41–43](../../../../../../include/crown/recovery/image.hpp#L41) | Type/record definition: struct ImageStatistics |  · [reviewed contract](#b0009) |
| [B0010 · 44–47](../../../../../../include/crown/recovery/image.hpp#L44) | Type/record definition: struct InspectedImage |  · [reviewed contract](#b0010) |
| [B0011 · 48–54](../../../../../../include/crown/recovery/image.hpp#L48) | Type/record definition: struct EncodedImage | source comment (unverified): // Copying the byte vector can allocate; moves transfer its actual account. · [reviewed contract](#b0011) |
| [B0012 · 55–55](../../../../../../include/crown/recovery/image.hpp#L55) | Type/record definition: struct ImageTableView |  · [reviewed contract](#b0012) |
| [B0013 · 56–59](../../../../../../include/crown/recovery/image.hpp#L56) | Type/record definition: struct ImageRow | returns row.view() · [reviewed contract](#b0013) |
| [B0014 · 60–67](../../../../../../include/crown/recovery/image.hpp#L60) | Type/record definition: struct DecodedImage | source comment (unverified): // Native row entries are move-only; decoding explicitly funds their copies. · [reviewed contract](#b0014) |
| [B0015 · 68–81](../../../../../../include/crown/recovery/image.hpp#L68) | declares values/defaults or compile-time conditions. | source comment (unverified): // Little endian, exact scalar tags, fixed arithmetic identity, complete-body · [reviewed contract](#b0015) |

## B0001

[Lines 1–11](../../../../../../include/crown/recovery/image.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose bounded native runtime image values. |
| inputs / outputs | Image allocator/row/storage helpers and fixed native image types. |
| invariants | This is runtime component format, not complete session state or durable file API. |
| ownership | No live image allocated by inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action at inclusion. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
inline constexpr resource::MemoryAttribution image_owner{resource::MemoryOwnerKind::recovery,0};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attribute native recovery image storage. |
| inputs / outputs | image_owner={MemoryOwnerKind::recovery,0}. |
| invariants | Label classifies actual account allocations, not a new allowance or recovery authority. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
template<class T> using ImageVector=std::vector<T,resource::OwnerAllocator<T>>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define transferable funded image vectors. |
| inputs / outputs | ImageVector&lt;T&gt;=vector&lt;T,OwnerAllocator&lt;T&gt;&gt;. |
| invariants | Owning copies depend on T; char vectors deep-copy bytes, native move-only row entries do not promise implicit copy. Move/assignment/swap propagate actual account/storage. |
| ownership | Vector owns actual original/receiving-account capacity, allocator retains same grant. |
| failure | Nonempty vector allocation/copy may throw. No automatic account injection into arbitrary nested members. |
| cost | Copy O(elements+their actual payload), move transfer fixed; destruction element-specific plus buffer free. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

## B0002

[Lines 12–14](../../../../../../include/crown/recovery/image.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> [[nodiscard]] auto image_allocator(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind recovery-log image allocator. |
| inputs / outputs | Returns OwnerAllocator&lt;T&gt;(account,recovery_log,image_owner). |
| invariants | No fresh grant; all nested native ownership must use actual supplied account. |
| ownership | Allocator retains MemoryAccount, no T payload allocated. |
| failure | Signature not noexcept; current binding only copies fixed handles. |
| cost | Fixed account/allocator retain. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 15–15](../../../../../../include/crown/recovery/image.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ImageFault { limit, work, corrupt, version, binding, scalar };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify native image rejection. |
| inputs / outputs | limit/work/corrupt/version/binding/scalar. |
| invariants | Codec failure is not a durable file publication outcome. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 16–23](../../../../../../include/crown/recovery/image.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ImageFailure final:public std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed ImageFailure diagnostics. |
| inputs / outputs | One ImageFault; static rejection message. |
| invariants | No dynamic error string or owner retained. |
| ownership | Only fixed enums/native errno/booleans; what() returns static literal, no dynamic message or authority owner. |
| failure | Constructor/getters noexcept; constructing this public diagnostic itself does not prove a file effect or grant recovery authority. |
| cost | Fixed object construction/copy/getters, no dynamic message formatting or IO. Throw/unwind still has normal C++ ABI/stack cost and can require exception storage outside the query payload model. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit ImageFailure(ImageFault fault) noexcept:fault_(fault) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct ImageFailure. |
| inputs / outputs | Stores supplied fixed diagnostic fields. |
| invariants | Actual implementation chooses phase/outcome; caller-created fields are descriptive only. |
| ownership | Inline values only; no file/runtime retained. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ImageFault fault() const noexcept {return fault_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ImageFailure fault. |
| inputs / outputs | Returns stored fault by value. |
| invariants | Do not replace actual file/native recovery checks with the descriptive field. |
| ownership | Independent scalar; error object owns no authority. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const char* what() const noexcept override {return "runtime checkpoint image rejected";}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ImageFailure static message. |
| inputs / outputs | Returns constant what() literal. |
| invariants | Message is diagnostic label, not serialized recovery proof. |
| ownership | Static storage; pointer does not depend on exception lifetime. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 24–27](../../../../../../include/crown/recovery/image.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ImageLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound native image bytes/visits and structural populations. |
| inputs / outputs | Bytes64MiB/work256Mi byte visits, tables4096/rows1M/fields1024/scalar bytes1MiB. |
| invariants | Logical serialization/checksum visits differ from native storage rebuild/scalar compare grants and actual MemoryAccount bytes; no active-time clock. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 28–29](../../../../../../include/crown/recovery/image.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L29:sha256:f2eb8a57ec157894285aee79d3c192b4ff55ae7e33cd5b5127a1cb248ed899a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Runtime image component v1. A complete session envelope additionally needs input positions, options and window state. This is not a durable file API. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/image.hpp lines 26-31; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [docs/code_specs/files/include/crown/recovery/image.hpp.md](image.hpp.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/session_lifecycle.md](../../../../../session_lifecycle.md) |

## B0007

[Lines 30–35](../../../../../../include/crown/recovery/image.hpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ImageBinding {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe expected runtime physical/source/policy binding. |
| inputs / outputs | Fixed physical/source SHA arrays, catalog version and26 policy words. |
| invariants | Factory-derived expected binding checked exactly by decode. Public equal fields cannot supply a checked Program/native schema/source database by themselves. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const ImageBinding&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare image bindings. |
| inputs / outputs | Default equality compares both hashes/catalog version/all26 policy words. |
| invariants | Value equality does not prove actual source/native admission, live file/lock ownership or durable acceptance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Bounded fixed-member comparison, no allocation/IO/clock. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 36–40](../../../../../../include/crown/recovery/image.hpp#L36); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ImageManifest {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one runtime component manifest. |
| inputs / outputs | ImageBinding plus epoch. |
| invariants | Epoch/hash labels are copied metadata, not session source progress, complete window state or durable authority. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const ImageManifest&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare image manifests. |
| inputs / outputs | Default equality compares binding and epoch. |
| invariants | Value equality does not prove actual source/native admission, live file/lock ownership or durable acceptance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Bounded fixed-member comparison, no allocation/IO/clock. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 41–43](../../../../../../include/crown/recovery/image.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ImageStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report codec bytes/logical work/row count. |
| inputs / outputs | Fixed bytes/work/rows. |
| invariants | Work counts named serialized byte/parse/hash visits; not CPU instructions, elapsed time, account heap bytes or native rebuild work. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 44–47](../../../../../../include/crown/recovery/image.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InspectedImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return allocation-free runtime-image inspection metadata. |
| inputs / outputs | ImageManifest and ImageStatistics. |
| invariants | Complete structural/checksum inspection does not validate actual compiled Program/schema/source/window/native relation semantics. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 48–54](../../../../../../include/crown/recovery/image.hpp#L48); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EncodedImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own encoded native runtime component bytes. |
| inputs / outputs | ImageVector&lt;char&gt;, statistics and manifest. |
| invariants | Manifest describes encoded wire structure, not complete session/durable file or actual native admission. |
| ownership | Bytes own funded capacity on supplied account. Copies allocate/deep-copy bytes; moves transfer allocator/storage. Other fields fixed. |
| failure | Byte copies can throw; this public aggregate has no special whole-record copy-assignment publication guarantee. Codec factory prepares privately. |
| cost | O(B) deep-copy allocation, fixed metadata copy; release deallocates trivial-byte vector, no need to hash/scan B bytes again. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 55–55](../../../../../../include/crown/recovery/image.hpp#L55); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ImageTableView {std::span<const storage::RowView> rows;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a table of borrowed native rows for encode. |
| inputs / outputs | span&lt;const RowView&gt; rows. |
| invariants | Both span array and every row/scalar/string backing remain alive/unchanged through both encode passes. No implicit pin or layout ownership. |
| ownership | Owns only pointer/count, retains no data/account. |
| failure | View construction cannot validate lifetime; codec validates counts/scalars during synchronous use. |
| cost | O(1) view copy, no allocation. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 56–59](../../../../../../include/crown/recovery/image.hpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ImageRow {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one native decoded runtime row. |
| inputs / outputs | Move-only AccountedRow; values() returns borrowed RowView. |
| invariants | Native row holds compact exact typed values; zero fields valid. Public ImageRow does not authenticate Program table/schema. |
| ownership | Owns one receiving-account block; native copy disabled, explicit clone needed; move transfers block. |
| failure | Row materialization may throw before publication; move/release do not allocate. |
| cost | O(columns+string bytes) explicit decode copy; fixed transfer/block free. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] storage::RowView values() const noexcept {return row.view();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow decoded runtime row values. |
| inputs / outputs | Returns row.view(). |
| invariants | Returned view valid only while ImageRow/block alive; this getter has no rvalue prohibition, so caller must retain owner. |
| ownership | No owner/pin retained by view. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | O(1) fixed member/value lookup, no allocation/IO/clock. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 60–67](../../../../../../include/crown/recovery/image.hpp#L60); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DecodedImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own every table/row of decoded native runtime component. |
| inputs / outputs | Fixed manifest/stats and nested funded ImageVector&lt;Rows&gt;, where ImageRow contains move-only native row. |
| invariants | Wire validation precedes materialization; actual Program/schema/base/window admission follows separately. Do not promise unsupported implicit deep-copy of move-only row entries. |
| ownership | Owns receiver-account outer/inner arrays and row blocks; input image bytes not retained after completed decode. |
| failure | Allocation failure unwinds unpublished nested arrays/rows; codec/native admission errors remain separate. |
| cost | O(decoded rows/bytes) materialization; teardown visits row owners and table vectors, frees compact blocks without per-string heap graph. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 68–81](../../../../../../include/crown/recovery/image.hpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] EncodedImage encode_image(const resource::MemoryAccount&,const ImageManifest&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode borrowed native tables after complete preflight. |
| inputs / outputs | Actual account, valid manifest, stable ImageTableView span and ImageLimits. |
| invariants | Validate hash/catalog/row/scalar limits; count both write passes and body checksum before first final-buffer allocation. No file IO or complete session capture. |
| ownership | One final funded byte vector; table views borrowed only through two unchanged passes. |
| failure | ImageFailure/work/limit/account/OOM frees private result; no live table mutation. |
| cost | O(serialized bytes+rows/fields) sizing/write/body SHA with precharged byte visits; reserve final size once, fixed-stack scalar formatting. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] DecodedImage decode_image(const resource::MemoryAccount&,std::string_view,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate then materialize native runtime image rows. |
| inputs / outputs | Account/stable immutable string_view, expected actual ImageBinding and finite limits. |
| invariants | Inspect full checksum/structure/binding before output growth; reserve second parse visits. Codec does not verify Program tables/semantic source membership. |
| ownership | Returns receiver-funded row/table arrays owning all scalar/string bytes, no image borrow retained. |
| failure | Version/corrupt/binding/scalar/work/limit/OOM propagate; partial graph freed before return. |
| cost | Full image hash+structural parse then materialization parse/row clones; O(B+rows/fields) byte visits, row-cell scratch capacity plus output graph coexist. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] InspectedImage inspect_image(std::string_view,ImageLimits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect complete runtime image without heap graph. |
| inputs / outputs | Stable bytes+limits yield fixed InspectedImage. |
| invariants | Validates magic/version/complete length/body SHA/scalar structure/counts; no expected binding comparison when caller only inspects, no native/schema admission. |
| ownership | Input borrowed only for call; output fixed copies retain no image/account. |
| failure | Fixed ImageFailure on malformed/resource limits; no native state mutation. |
| cost | O(B+row/field structure) checks/hash, no output allocation or clock. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |

```text
inline constexpr std::size_t image_header_size=84;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set runtime image frame header width. |
| inputs / outputs | image_header_size=84. |
| invariants | 8magic+version/reserved/body length+64 body SHA; not WAL/sink148-byte dual-checksum header. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/image.hpp](../../../../../../include/crown/recovery/image.hpp), [src/recovery/image.cpp](../../../../../../src/recovery/image.cpp), [src/recovery/binary_detail.hpp](../../../../../../src/recovery/binary_detail.hpp), [docs/native-replay.md](../../../../../native-replay.md), [docs/code_review.md](../../../../../code_review.md) |
