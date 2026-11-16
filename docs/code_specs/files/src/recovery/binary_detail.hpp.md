# `src/recovery/binary_detail.hpp` — block usage map

[Source](../../../../../src/recovery/binary_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode/decode bounded fixed-width/versioned recovery fields and exact scalar payloads.

Snapshot SHA-256: `d7f7af4a06d4764d53cffb72314f4519dd1db63c4d06354f0e2cfe4accb0391f`. 115 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/recovery/binary_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–12](../../../../../src/recovery/binary_detail.hpp#L10) | Callable definition: inline void require(bool condition,ImageFault fault=ImageFault::corrupt) | calls ImageFailure; guard inline void require(bool condition,ImageFault fault=ImageFault::corrupt) { · [reviewed contract](#b0002) |
| [B0003 · 13–15](../../../../../src/recovery/binary_detail.hpp#L13) | Callable definition: inline bool hex(std::span&lt;const char&gt; text) | calls std::all_of, begin, end; returns std::all_of(text.begin(),text.end(),\[\](char c){return (c&gt;=@ && c&lt;=@ ) \|\| (c&gt;=@ && c&lt;=@ ) · [reviewed contract](#b0003) |
| [B0004 · 16–23](../../../../../src/recovery/binary_detail.hpp#L16) | Type/record definition: struct Budget | guard require(used&lt;=limits.work && count&lt;=limits.work-used,ImageFault::work);used+=count; · [reviewed contract](#b0004) |
| [B0005 · 24–27](../../../../../src/recovery/binary_detail.hpp#L24) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |
| [B0006 · 28–33](../../../../../src/recovery/binary_detail.hpp#L28) | Callable definition: void put(std::string_view text) | calls require, size, charge, insert; guard require(size&lt;=budget.limits.bytes && text.size()&lt;=budget.limits.bytes-size,ImageFault::limit);; growth insert; source comment (unverified): // Failed insertion leaves charged progress; discard this private writer. · [reviewed contract](#b0006) |
| [B0007 · 34–39](../../../../../src/recovery/binary_detail.hpp#L34) | Callable definition: void integer(std::uint64_t value,unsigned width) | calls put, data; 1 loop sites; source comment (unverified): // Internal callers supply only widths 1, 2, 4 or 8. · [reviewed contract](#b0007) |
| [B0008 · 40–54](../../../../../src/recovery/binary_detail.hpp#L40) | Callable definition: void scalar(const storage::ScalarView& value) | calls integer, index, std::visit, constexpr; guard require(cell.size()&lt;=budget.limits.scalar_bytes,ImageFault::limit);integer(cell.size(),8);put(cell); · [reviewed contract](#b0008) |
| [B0009 · 55–55](../../../../../src/recovery/binary_detail.hpp#L55) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 56–75](../../../../../src/recovery/binary_detail.hpp#L56) | Type/record definition: class Reader | guard require(position&lt;=input.size() && count&lt;=input.size()-position);budget.charge(count);; returns value; value; 1 loop sites; source comment (unverified): // String results borrow these bytes; keep input unchanged through both passes. · [reviewed contract](#b0010) |
| [B0011 · 76–89](../../../../../src/recovery/binary_detail.hpp#L76) | Callable definition: inline bool canonical_decimal(std::string_view text) | calls empty, size, front, find; returns false; false; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 90–100](../../../../../src/recovery/binary_detail.hpp#L90) | Callable definition: inline Date date(std::uint32_t bits) | calls year, require, ok, month; guard require(value.ok() && year&gt;=1 && year&lt;=9999 && std::chrono::sys_days{value}==point,ImageFault::scal…; returns Date::parse({text.data(),text.size()}); 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 101–114](../../../../../src/recovery/binary_detail.hpp#L101) | Callable definition: inline storage::ScalarView scalar(Reader& reader) | calls integer, take, size, require; guard case 2:{const auto value=reader.integer(1);require(value&lt;=1,ImageFault::scalar);return value!=0;}; returns std::bit_cast&lt;std::int64_t&gt;(reader.integer(8)); reader.take(reader.size(reader.budget.limits.scalar… · [reviewed contract](#b0013) |
| [B0014 · 115–115](../../../../../src/recovery/binary_detail.hpp#L115) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::binary_detail · [reviewed contract](#b0014) |

## B0001

[Lines 1–9](../../../../../src/recovery/binary_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/recovery/image.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the internal byte codec and fixed scalar representation across recovery formats. |
| inputs / outputs | Image limits/failures, accounted vector aliases and native scalar views are available to inline helpers. |
| invariants | The internal helpers implement wire mechanics; schema, UTF-8 where required, query binding and publication are caller layers. |
| ownership | Includes add no owning instance; all helper state below is explicit. |
| failure | No initialization or syscall is introduced by this header. |
| cost | Compile-time dependencies; per-byte and allocation costs belong to the invoked helpers. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/local_sink_codec.cpp](../../../../../src/recovery/local_sink_codec.cpp) |

## B0002

[Lines 10–12](../../../../../src/recovery/binary_detail.hpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void require(bool condition
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject one failed codec predicate with its fixed image fault. |
| inputs / outputs | Boolean and optional fault in; returns only when true. |
| invariants | Default fault is corrupt; each caller chooses limit/work/version/binding/scalar where its boundary requires it. |
| ownership | No error text owner or resource acquisition. |
| failure | Throws ImageFailure on false; never catches or repairs prior reader/writer progress. |
| cost | One branch; fixed exception payload, with language exception machinery on failure. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

## B0003

[Lines 13–15](../../../../../src/recovery/binary_detail.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool hex(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize lowercase hexadecimal bytes in a supplied span. |
| inputs / outputs | Borrowed characters in; true iff every byte is 0-9 or a-f. |
| invariants | This alphabet check accepts an empty span and proves neither a required width nor digest authenticity; fixed-array callers establish width. |
| ownership | Only reads the caller span for this call. |
| failure | No explicit failure or allocation. |
| cost | O(n) comparisons with early exit. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

## B0004

[Lines 16–23](../../../../../src/recovery/binary_detail.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Budget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track one codec invocation's byte-work and aggregate row admission. |
| inputs / outputs | Copied ImageLimits with initially zero used and rows counters. |
| invariants | Limits are finite caller-supplied bounds, not a memory account or native build grant. Fresh materialization budgets recheck a pass only after the outer operation has reserved total work. |
| ownership | Owns fixed counters/limits; Writer and Reader borrow this object. |
| failure | Mutable internal state must remain consistent; helper rejection does not reset earlier charges. |
| cost | Fixed storage; byte visits and rows are distinct units. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

```text
void charge(std::uint64_t count)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve additional abstract byte work without unsigned overflow. |
| inputs / outputs | Count in; used increases only on success. |
| invariants | Requires used&lt;=limits.work and count&lt;=limits.work-used before addition. |
| ownership | Mutates only the borrowed invocation budget. |
| failure | ImageFault::work leaves used unchanged for this debit; preceding debits remain. |
| cost | O(1); does not measure instructions, comparisons, syscalls or wall time. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

```text
void row() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one more total row across the image. |
| inputs / outputs | No payload input; rows increments after the bound check. |
| invariants | rows&lt;limits.rows prevents both exceeding the declared limit and increment overflow. |
| ownership | Updates the invocation budget, not a returned table. |
| failure | ImageFault::limit before increment; previous rows remain counted. |
| cost | O(1), separate from row decoding/copy cost. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

## B0005

[Lines 24–27](../../../../../src/recovery/binary_detail.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a byte-writing cursor in either sizing or materializing mode. |
| inputs / outputs | Borrowed Budget, nullable output vector pointer and zero size. |
| invariants | Null output performs validation/sizing only; nonnull output must be the intended fresh output buffer and inputs must remain stable across passes. |
| ownership | Does not own budget or vector; vector allocator determines account ownership. |
| failure | There is no rollback/reset mechanism after a write failure. |
| cost | Fixed state; null output avoids retained byte allocation. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

## B0006

[Lines 28–33](../../../../../src/recovery/binary_detail.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void put(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and optionally append one wire byte span. |
| inputs / outputs | Borrowed bytes in; size/work advance and optional output grows. |
| invariants | Check remaining byte cap with subtraction before charging work. size advances before vector insertion, so failed insertion does not leave a resumable writer. |
| ownership | Copies bytes only when output exists; input must not be invalidated by output insertion. |
| failure | Limit/work rejects before this size advance; vector allocation failure may follow charged progress. Enclosing private-result RAII is the cleanup boundary. |
| cost | O(1) for sizing plus charge; materialization copies O(n) bytes and may grow its account-funded vector. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

## B0007

[Lines 34–39](../../../../../src/recovery/binary_detail.hpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void integer(std::uint64_t value,unsigned width)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write low-order bytes in little-endian wire order. |
| inputs / outputs | u64 and internal width in; delegates width bytes to put. |
| invariants | All inspected callers use widths 1,2,4,8; width&lt;=8 is an internal precondition for the fixed array and shifts, not an external validation API. |
| ownership | Uses an eight-byte stack array; output ownership stays with Writer. |
| failure | put failures propagate; this helper does not roll back earlier bytes. |
| cost | O(width) extraction plus put; no separate heap allocation. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

## B0008

[Lines 40–54](../../../../../src/recovery/binary_detail.hpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar(const storage::ScalarView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one exact native scalar tag and payload. |
| inputs / outputs | ScalarView in; emits variant tag and int64, raw string, Boolean, epoch-day or canonical inline-decimal bytes. |
| invariants | String/decimal payloads obey scalar_bytes. Raw runtime strings are not UTF-8 checked here; enclosing session/sink/journal codecs impose their own text rules. Native Date/InlineDecimal values carry their existing validity. |
| ownership | Borrows view/string payload; decimal rendering uses fixed stack storage. |
| failure | Payload limit/render/put failures can follow the emitted tag and length; callers discard the private output, not resume this Writer. |
| cost | Fixed primitive work or O(string/decimal bytes); byte-work charges emitted bytes, not every render/visit instruction. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [src/storage/accounted_row.cpp § InlineDecimal::render](../../../../../src/storage/accounted_row.cpp), [src/recovery/local_sink_codec.cpp § row](../../../../../src/recovery/local_sink_codec.cpp) |

## B0009

[Lines 55–55](../../../../../src/recovery/binary_detail.hpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L55:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [docs/code_specs/files/src/recovery/binary_detail.hpp.md](binary_detail.hpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md) |

## B0010

[Lines 56–75](../../../../../src/recovery/binary_detail.hpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Reader {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a bounded borrowed byte cursor and its invocation budget. |
| inputs / outputs | Input view, borrowed Budget and initially zero position. |
| invariants | The input remains alive and immutable while any returned slice is used. Reader does not own input or authenticate it; outer codecs verify checksums. |
| ownership | No owned buffer; returned string_views alias input. |
| failure | Methods may advance the cursor before a later structural check rejects; no transactional rewind. |
| cost | Fixed state; byte-work and native copying remain separate. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

```text
std::string_view take(std::size_t count)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exactly the next bounded slice and debit its byte visit. |
| inputs / outputs | Count in; borrowed substring out and position advances. |
| invariants | Bounds use position&lt;=input.size and count&lt;=remaining before substr, then charge work before advancing. |
| ownership | Returned view remains tied to input lifetime/immutability. |
| failure | Corrupt/work rejection before cursor advancement for this take; previous successful reads remain consumed. |
| cost | O(1) view construction and bookkeeping; charge(count) is logical byte work, not a memcpy. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

```text
std::uint64_t integer(unsigned width)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct an unsigned little-endian word. |
| inputs / outputs | Internal width in; u64 out. |
| invariants | Inspected callers pass at most eight bytes, preventing shifts by 64 or more; take enforces input length. |
| ownership | Reads a borrowed local slice; no retained owner. |
| failure | take failure propagates; no rewind after a successful take. |
| cost | O(width) byte/shift operations, with width charged by take. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

```text
std::size_t size(std::uint64_t maximum)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and narrow one counted length under wire and host limits. |
| inputs / outputs | Eight wire bytes and maximum in; size_t out. |
| invariants | Requires value&lt;=maximum and &lt;=SIZE_MAX before cast. This does not prove the subsequent payload exists; take/count-specific guards do that. |
| ownership | Owns only the decoded integer. |
| failure | ImageFault::limit after the eight-byte length has been consumed; no rollback. |
| cost | Eight-byte read plus constant comparisons. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp) |

## B0011

[Lines 76–89](../../../../../src/recovery/binary_detail.hpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool canonical_decimal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize the canonical exact decimal grammar before native parsing. |
| inputs / outputs | Borrowed text in; Boolean out. |
| invariants | Nonempty bounded text, optional minus only, no leading integer zeros, nonempty fraction without trailing zero, scale&lt;=38, significant digits&lt;=38; zero is exactly "0". A second dot fails the digit scan. |
| ownership | No copy or retained view. |
| failure | Returns false for invalid encodings; caller chooses ImageFault::scalar before InlineDecimal::parse. |
| cost | O(n) bounded scans; this lexical/canonical check is distinct from serialized-byte work charges. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [src/storage/accounted_row.cpp § InlineDecimal::parse](../../../../../src/storage/accounted_row.cpp) |

## B0012

[Lines 90–100](../../../../../src/recovery/binary_detail.hpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Date date(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert signed epoch-day bits to the supported Gregorian Date domain. |
| inputs / outputs | u32 bit pattern in; Date out. |
| invariants | The year must be 0001..9999 and round-trip sys_days must equal the original point, excluding chrono narrowing/wrap aliases. |
| ownership | Fixed chrono/scalar values and ten-byte stack formatting; Date owns no text. |
| failure | Invalid domain raises ImageFault::scalar before Date::parse; valid formatted text follows Date's own parser contract. |
| cost | Fixed-size conversion/render/parser work, no successful-path native allocation. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [src/ir/scalar.cpp § Date::parse](../../../../../src/ir/scalar.cpp) |

## B0013

[Lines 101–114](../../../../../src/recovery/binary_detail.hpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline storage::ScalarView scalar(Reader& reader)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one exact scalar while preserving borrowed string lifetime. |
| inputs / outputs | Reader in; tagged ScalarView out. |
| invariants | Tags 0..4 only; Boolean&lt;=1; Date domain and canonical decimal validated. String length obeys scalar_bytes; strings remain raw bytes here. |
| ownership | String alternative aliases Reader input; int/bool/Date/InlineDecimal are inline owned values. Deep ownership is created later by AccountedRow::copy_of. |
| failure | Unknown/noncanonical scalar, count, truncation or work rejects with ImageFailure; cursor may already have advanced. |
| cost | O(serialized scalar bytes) visiting plus bounded date/decimal validation; no decoded row allocation. |
| Design | [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [src/storage/accounted_row.cpp § copy_cells](../../../../../src/storage/accounted_row.cpp) |

## B0014

[Lines 115–115](../../../../../src/recovery/binary_detail.hpp#L115); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L115:sha256:e77c26d59208d11c0a301edf75ae20f08d69623de03e0157914fc6f8835166ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::binary_detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [docs/code_specs/files/src/recovery/binary_detail.hpp.md](binary_detail.hpp.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md) |
