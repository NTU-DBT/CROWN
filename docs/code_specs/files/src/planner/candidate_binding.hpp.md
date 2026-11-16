# `src/planner/candidate_binding.hpp` — block usage map

[Source](../../../../../src/planner/candidate_binding.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `769fcff9d2f9c2d757a8fdc300245d186c12037d12760ec5da5efa5eb76cfd52`. 255 lines partitioned into 31 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/planner/candidate_binding.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../src/planner/candidate_binding.hpp#L13) | Type/record definition: enum class LimitKind |  · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../src/planner/candidate_binding.hpp#L14) | Type/record definition: struct Limit |  · [reviewed contract](#b0003) |
| [B0004 · 15–16](../../../../../src/planner/candidate_binding.hpp#L15) | Explanatory comments or spacing. | source comment (unverified): // Work is debited before bytes. A later byte rejection or sink allocation · [reviewed contract](#b0004) |
| [B0005 · 17–26](../../../../../src/planner/candidate_binding.hpp#L17) | Type/record definition: struct Budget | source comment (unverified): // Work is debited before bytes. A later byte rejection or sink allocation · [reviewed contract](#b0005) |
| [B0006 · 27–37](../../../../../src/planner/candidate_binding.hpp#L27) | Type/record definition: struct Bytes | returns std::string(@ ); growth push_back · [reviewed contract](#b0006) |
| [B0007 · 38–47](../../../../../src/planner/candidate_binding.hpp#L38) | Type/record definition: struct AllocatedBytes | growth push_back · [reviewed contract](#b0007) |
| [B0008 · 48–66](../../../../../src/planner/candidate_binding.hpp#L48) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(CHAR_BIT == 8);; source comment (unverified): // Private binding format v2 directly records every Catalog/Query field. It · [reviewed contract](#b0008) |
| [B0009 · 67–67](../../../../../src/planner/candidate_binding.hpp#L67) | Callable definition: template&lt;class... Args&gt; explicit BasicBindingEncoder(Budget* budget,Args&&... args):bytes(budget,std::forward&lt;Args&gt;(args)...) | calls bytes · [reviewed contract](#b0009) |
| [B0010 · 68–68](../../../../../src/planner/candidate_binding.hpp#L68) | Explanatory comments or spacing. |  |
| [B0011 · 69–74](../../../../../src/planner/candidate_binding.hpp#L69) | Callable definition: void word(std::uint64_t value) | calls push_back; growth push_back; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 75–78](../../../../../src/planner/candidate_binding.hpp#L75) | Callable definition: void unsigned_integer(std::uint64_t value) | calls push_back, word; growth push_back · [reviewed contract](#b0012) |
| [B0013 · 79–82](../../../../../src/planner/candidate_binding.hpp#L79) | Callable definition: void signed_integer(std::int64_t value) | calls push_back, word; growth push_back · [reviewed contract](#b0013) |
| [B0014 · 83–86](../../../../../src/planner/candidate_binding.hpp#L83) | Callable definition: template&lt;class Enum&gt; void enumeration(Enum value) | calls push_back, word; growth push_back · [reviewed contract](#b0014) |
| [B0015 · 87–90](../../../../../src/planner/candidate_binding.hpp#L87) | Callable definition: void boolean(bool value) | calls push_back; growth push_back · [reviewed contract](#b0015) |
| [B0016 · 91–95](../../../../../src/planner/candidate_binding.hpp#L91) | Callable definition: void string(std::string_view value) | calls push_back, word, size, append; growth push_back · [reviewed contract](#b0016) |
| [B0017 · 96–99](../../../../../src/planner/candidate_binding.hpp#L96) | Callable definition: void record(std::string_view kind) | calls push_back, string; growth push_back · [reviewed contract](#b0017) |
| [B0018 · 100–103](../../../../../src/planner/candidate_binding.hpp#L100) | Callable definition: void sequence(std::size_t count) | calls push_back, word; growth push_back · [reviewed contract](#b0018) |
| [B0019 · 104–107](../../../../../src/planner/candidate_binding.hpp#L104) | Callable definition: void presence(bool present) | calls push_back; growth push_back · [reviewed contract](#b0019) |
| [B0020 · 108–111](../../../../../src/planner/candidate_binding.hpp#L108) | Callable definition: template&lt;class Range&gt; void column_ids(const Range& ids) | calls sequence, size, unsigned_integer; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 112–124](../../../../../src/planner/candidate_binding.hpp#L112) | Callable definition: template&lt;class ColumnView&gt; void column(const ColumnView& value) | calls record, string, enumeration, boolean · [reviewed contract](#b0021) |
| [B0022 · 125–140](../../../../../src/planner/candidate_binding.hpp#L125) | Callable definition: template&lt;class ConstraintView&gt; void constraint(const ConstraintView& value) | calls record, string, column_ids, enumeration · [reviewed contract](#b0022) |
| [B0023 · 141–164](../../../../../src/planner/candidate_binding.hpp#L141) | Callable definition: template&lt;class TableView&gt; void table(const TableView& value) | calls record, string, sequence, size; 4 loop sites · [reviewed contract](#b0023) |
| [B0024 · 165–196](../../../../../src/planner/candidate_binding.hpp#L165) | Callable definition: template&lt;class Scalar&gt; void scalar(const Scalar& value) | calls record, unsigned_integer, index, signed_integer; returns storage::InlineDecimal::copy_of(std::get&lt;4&gt;(value)); std::get&lt;4&gt;(value); growth copy_of; source comment (unverified): // Explicit native variant index distinguishes every scalar type, including · [reviewed contract](#b0024) |
| [B0025 · 197–209](../../../../../src/planner/candidate_binding.hpp#L197) | Callable definition: template&lt;class TermView&gt; void term(const TermView& value) | calls record, unsigned_integer, index, scalar; source comment (unverified): // IgnoredColumn has no payload. · [reviewed contract](#b0025) |
| [B0026 · 210–215](../../../../../src/planner/candidate_binding.hpp#L210) | Callable definition: template&lt;class CatalogView&gt; void catalog(const CatalogView& value) | calls record, unsigned_integer, sequence, size; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 216–239](../../../../../src/planner/candidate_binding.hpp#L216) | Callable definition: template&lt;class QueryView&gt; void query(const QueryView& value) | calls record, sequence, size, string; 4 loop sites · [reviewed contract](#b0027) |
| [B0028 · 240–241](../../../../../src/planner/candidate_binding.hpp#L240) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0028) |
| [B0029 · 242–248](../../../../../src/planner/candidate_binding.hpp#L242) | Callable definition: template&lt;class CatalogView,class QueryView&gt; inline std::string encode(const CatalogView& catalog, const QueryView& query, Budget*… | calls encoder, catalog, query, std::move; returns std::move(encoder.bytes.value) · [reviewed contract](#b0029) |
| [B0030 · 249–254](../../../../../src/planner/candidate_binding.hpp#L249) | Callable definition: template&lt;class CatalogView,class QueryView&gt; inline AllocatedBytes::String encode(const CatalogView& catalog,const QueryView& quer… | calls encoder, catalog, query, std::move; returns std::move(encoder.bytes.value) · [reviewed contract](#b0030) |
| [B0031 · 255–255](../../../../../src/planner/candidate_binding.hpp#L255) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::binding_detail · [reviewed contract](#b0031) |

## B0001

[Lines 1–12](../../../../../src/planner/candidate_binding.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:658b5346498026b28394ff18b9c1b12c40ea5baaa9f6dc64a1e3e17e55fd2807
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/ir/model.hpp", #include "crown/storage/accounted_row.hpp", #include "crown/resource/owner_allocator.hpp", #include &lt;array&gt;, #include &lt;type_traits&gt;, #include "crown/api/error.hpp", #include &lt;climits&gt;, #include &lt;limits&gt;, #include &lt;string_view&gt;, #include &lt;utility&gt; available to src/planner/candidate_binding.hpp; open crown::planner::binding_detail. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0002

[Lines 13–13](../../../../../src/planner/candidate_binding.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class LimitKind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name admission work versus byte-limit exhaustion. |
| inputs / outputs | Small enum carried by Limit. |
| invariants | Neither label is a peak-memory measurement. |
| ownership | Value-only tag. |
| failure | No allocation in the tag. |
| cost | Fixed metadata. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 14–14](../../../../../src/planner/candidate_binding.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limit {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a private encoding-admission stop without formatting. |
| inputs / outputs | LimitKind payload. |
| invariants | Caller handles this blocking admission outcome; it is not a resumable token-worker result. |
| ownership | Value-only exception payload. |
| failure | Thrown before the disallowed component update. |
| cost | Exception runtime overhead only on limit failure. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 15–16](../../../../../src/planner/candidate_binding.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L16:sha256:c3d9439f7b3b2e7788794dd43026b4759011058461c5e567dba05f27d7db3112
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Budget: Work is debited before bytes. A later byte rejection or sink allocation failure does not roll back accepted debits; this is blocking admission. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Budget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Budget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0005

[Lines 17–26](../../../../../src/planner/candidate_binding.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Budget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge private binding admission units against two distinct external counters. |
| inputs / outputs | References to work/bytes plus maxima; charge(n) checks work, increments it, checks bytes, then increments bytes. |
| invariants | Counters must be distinct. Byte rejection can leave work advanced; accepted charges also remain if a later sink allocation fails. This is not prepare/commit rollback. |
| ownership | Borrows synchronous caller counters; no counter reference enters returned string. |
| failure | Work/bytes Limit identifies the failed check; subtraction guards avoid arithmetic overflow. |
| cost | Constant arithmetic per debit; units track encoded content/admission, not actual allocator bytes or every CPU instruction. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 27–37](../../../../../src/planner/candidate_binding.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Bytes {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write ordinary owning binding bytes with optional content admission. |
| inputs / outputs | std::string and borrowed Budget pointer; prefix/push_back/append charge before storage. |
| invariants | Null budget disables counters, not allocation/length failure. |
| ownership | Owns output bytes; caller budget must outlive the sink during synchronous encoding. |
| failure | Charges are not rolled back on subsequent allocation failure. |
| cost | Character writes and bulk append can grow/copy string capacity. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
static std::string prefix(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge and construct the private binding-format version prefix. |
| inputs / outputs | Optional Budget to CROWN-CANDIDATE-BINDING;2; owning string. |
| invariants | Version marks this exact field/tag grammar; not a public wire migration API. |
| ownership | Returned string owns literal bytes. |
| failure | Budget may stop before construction; string allocation propagates afterward. |
| cost | Fixed prefix width plus possible ordinary allocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
explicit Bytes(Budget* b):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create ordinary sink with a charged version prefix. |
| inputs / outputs | Stores borrowed budget and owning prefix value. |
| invariants | Prefix charge precedes string storage construction. |
| ownership | Sink is local to encoder; returning its value drops the budget pointer. |
| failure | Limit/allocation aborts construction. |
| cost | Fixed prefix initialization and any string storage allocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
  void push_back(char c){if(budget)budget->charge(1);value.push_back(c);}
  void append(std::string_view s){if(budget)budget->charge(static_cast<std::uint64_t>(s.size()));value.append(s);}
};
struct AllocatedBytes
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge and append one ordinary binding byte. |
| inputs / outputs | char to ordinary value after optional charge. |
| invariants | Accepted content debit is not rolled back by later storage failure. |
| ownership | Owns byte; borrows synchronous budget. |
| failure | Limit or string allocation propagates. |
| cost | One logical byte plus real capacity growth/relocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
  void append(std::string_view s){if(budget)budget->charge(static_cast<std::uint64_t>(s.size()));value.append(s);}
};
struct AllocatedBytes
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge and append an ordinary raw byte span without UTF conversion. |
| inputs / outputs | string_view copied to std::string after one width debit. |
| invariants | Embedded NUL/non-UTF bytes retain their lengths and contents. |
| ownership | Borrows span for call, output owns copied bytes. |
| failure | Limit/allocation/length errors propagate; charge may already be recorded. |
| cost | O(span bytes) copy plus possible existing-buffer relocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 38–47](../../../../../src/planner/candidate_binding.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AllocatedBytes {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the same binding grammar in an account-backed output string. |
| inputs / outputs | OwnerAllocator&lt;char&gt; string, borrowed budget and explicit account/purpose/attribution. |
| invariants | Content counters differ from actual account allocation/framing/capacity charges. |
| ownership | Returned string retains allocator/account ownership needed to free its bytes. |
| failure | Memory/account/content/length failures propagate from preparation. |
| cost | Output growth uses account-backed allocations, still with real capacity/relocation costs. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
  AllocatedBytes(Budget* b,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize native output allocator and emit the same version prefix. |
| inputs / outputs | Account, purpose, owner and optional Budget. |
| invariants | No intermediate ordinary binding string is built. |
| ownership | Allocator value retains required account state; budget remains a synchronous borrow. |
| failure | Prefix/account allocation failure destroys unexposed sink. |
| cost | Fixed allocator metadata and prefix writes, possibly several implementation-dependent growth allocations. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
  void push_back(char c){if(budget)budget->charge(1);value.push_back(c);}
  void append(std::string_view s){if(budget)budget->charge(static_cast<std::uint64_t>(s.size()));value.append(s);}
};
// Private binding format
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge and append one account-backed binding byte. |
| inputs / outputs | char to OwnerAllocator string after optional charge. |
| invariants | Same emitted byte and debit order as ordinary sink; allocation framing is separately accounted. |
| ownership | Owns byte under explicit account attribution. |
| failure | Limit or native allocation failure propagates after any accepted debit. |
| cost | One logical byte plus actual string growth/account-ledger work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
  void append(std::string_view s){if(budget)budget->charge(static_cast<std::uint64_t>(s.size()));value.append(s);}
};
// Private binding format
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a raw byte span directly into account-backed binding storage. |
| inputs / outputs | One width charge followed by value.append. |
| invariants | No ordinary temporary string/exported scalar is needed for raw string views. |
| ownership | Input span borrows caller; output/account own final storage. |
| failure | Limit/length/memory failures propagate without a partially returned token. |
| cost | O(bytes) copy plus actual capacity/ledger costs; not constant work from one debit. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 48–66](../../../../../src/planner/candidate_binding.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(CHAR_BIT == 8);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fix the supported binary representation assumptions at compile time. |
| inputs / outputs | Eight-bit bytes and size_t width no greater than uint64, checked by adjacent assertions. |
| invariants | Length/ID words fit the private eight-byte framing domain without narrowing. |
| ownership | Compile-time predicates only. |
| failure | Unsupported platforms fail compilation. |
| cost | No runtime cost or fixed-width query-arity restriction. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
template<class Sink> struct BasicBindingEncoder {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode every current Catalog/Query field into typed framed bytes. |
| inputs / outputs | Ordinary/accounted sink with complete deterministic field traversal. |
| invariants | Record/array/optional/type/length framing is exact; all supplied vector orders, aliases, constants and contradiction are preserved. Model changes require format review/versioning. |
| ownership | Owns sink while borrowing stable model values synchronously; returns owning bytes. |
| failure | This encoder does not validate catalog/query semantics. Unsupported variants, content and allocation errors propagate. |
| cost | Full input/metadata/payload traversal, without a JSON DOM or hash-only identity; admission is outside enumeration quanta. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 67–67](../../../../../src/planner/candidate_binding.hpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class... Args> explicit BasicBindingEncoder(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward sink/account options into a local blocking encoder. |
| inputs / outputs | Budget pointer and optional allocator arguments. |
| invariants | Both sinks use the same field/tag ordering below. |
| ownership | Owns sink, borrows budget only while encoding. |
| failure | Sink construction/preparation failure propagates. |
| cost | Constructor and prefix costs only; no hidden query traversal. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 69–74](../../../../../src/planner/candidate_binding.hpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void word(std::uint64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit exactly eight big-endian bytes. |
| inputs / outputs | uint64 bit pattern to sink. |
| invariants | No variable-width delimiter is needed inside fixed word. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Eight sink writes; each may charge/grow/throw. |
| cost | Eight logical byte writes with underlying sink costs. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 75–78](../../../../../src/planner/candidate_binding.hpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void unsigned_integer(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame an unsigned field with U tag. |
| inputs / outputs | uint64 to U plus fixed word. |
| invariants | Unsigned type differs from I/E/B encodings. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Sink/limit errors propagate. |
| cost | One tag plus eight bytes. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 79–82](../../../../../src/planner/candidate_binding.hpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void signed_integer(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve signed int64 through I tag and modulo-2^64 word. |
| inputs / outputs | int64 converted to uint64 then word. |
| invariants | Negative values remain distinct and lossless in the signed field domain. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Sink/limit errors propagate. |
| cost | One tag plus eight bytes, no numeric text formatting. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 83–86](../../../../../src/planner/candidate_binding.hpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Enum> void enumeration(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame a validated enum value with E tag. |
| inputs / outputs | Private enum to uint64 word. |
| invariants | Known enum domain is a caller validation precondition; record position supplies enum meaning. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Does not reject unknown enum values itself; sink/limit errors propagate. |
| cost | One tag/eight bytes, fixed conversion. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 87–90](../../../../../src/planner/candidate_binding.hpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void boolean(bool value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame Boolean with B and one exact 0/1 byte. |
| inputs / outputs | bool to two sink bytes. |
| invariants | Boolean never aliases an integer/string payload. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Sink/limit errors propagate. |
| cost | Two logical byte writes. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 91–95](../../../../../src/planner/candidate_binding.hpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void string(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame byte-string length and exact payload. |
| inputs / outputs | S, uint64 length, raw bytes. |
| invariants | No delimiter escaping, NUL truncation or UTF normalization occurs. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Sink/limit/length errors propagate. |
| cost | O(payload bytes) copy plus fixed framing and possible capacity relocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 96–99](../../../../../src/planner/candidate_binding.hpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void record(std::string_view kind)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a named record with R plus framed kind. |
| inputs / outputs | Constant grammar name to typed record prefix. |
| invariants | Record names and field order are versioned together. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Sink/limit errors propagate. |
| cost | Kind bytes plus fixed string framing. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 100–103](../../../../../src/planner/candidate_binding.hpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void sequence(std::size_t count)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame an ordered array with A and count. |
| inputs / outputs | size_t count to uint64 word. |
| invariants | Compile-time size-domain assertion protects conversion; ordering remains caller order. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Sink/limit errors propagate. |
| cost | Nine bytes; elements are encoded separately. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 104–107](../../../../../src/planner/candidate_binding.hpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void presence(bool present)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame optional presence separately from any contained value. |
| inputs / outputs | P plus 0/1 byte. |
| invariants | Absence is distinct from a present zero/false/empty payload. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Sink/limit errors propagate. |
| cost | Two logical bytes. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 108–111](../../../../../src/planner/candidate_binding.hpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> void column_ids(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve an ordered column-ID list. |
| inputs / outputs | Array count then each unsigned index. |
| invariants | No sorting/deduplication silently changes declared key/estimate order. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Sink/limit errors propagate. |
| cost | O(number of IDs) framing writes; no copied intermediate ID vector. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 112–124](../../../../../src/planner/candidate_binding.hpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class ColumnView> void column(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode full column declaration including exact domain. |
| inputs / outputs | Name/type/nullability/collation and optional precision/scale. |
| invariants | Nullable and decimal-domain metadata are not dropped from binding identity. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Caller supplies validated fields; sink/limit errors propagate. |
| cost | Full name bytes plus fixed metadata framing. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 125–140](../../../../../src/planner/candidate_binding.hpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class ConstraintView> void constraint(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish complete unique/FK declarations. |
| inputs / outputs | Variant kind/name/source columns/status and FK target/columns. |
| invariants | Enforced/untrusted status and referenced IDs remain part of exact identity. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Invalid/valueless variant can throw; sink/limit errors propagate. |
| cost | O(all encoded names/column IDs) work and output bytes. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 141–164](../../../../../src/planner/candidate_binding.hpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class TableView> void table(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode every current table field in deterministic record order. |
| inputs / outputs | Name/columns/source version/constraints/statistics/distinct estimates/key hints. |
| invariants | Metadata/hints are retained as identity data, never promoted into enforced facts. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Caller validation is separate; nested sink/content failures propagate. |
| cost | Full declaration/metadata traversal and byte copies, including hint text and estimate column lists. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 165–196](../../../../../src/planner/candidate_binding.hpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Scalar> void scalar(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Type-frame exact native/public scalar payloads. |
| inputs / outputs | Variant index plus integer/string/bool/date-days/canonical decimal. |
| invariants | Decimal text and string bytes remain distinct through variant framing; no binary float conversion. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Unsupported/valueless kind throws candidate_binding_kind; export/format/sink errors propagate. |
| cost | Ordinary sink can allocate Decimal/rendered text; accounted sink uses bounded InlineDecimal stack rendering and only native output storage. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 197–209](../../../../../src/planner/candidate_binding.hpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class TermView> void term(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve variable, exact constant and ignored-column term distinctions. |
| inputs / outputs | Term variant index then corresponding ID/scalar or no ignored payload. |
| invariants | Ignored columns are not replaced by invented variables or dropped from ordered terms. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Unsupported variant throws candidate_binding_kind; nested failures propagate. |
| cost | Fixed tag plus actual scalar/ID payload work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 210–215](../../../../../src/planner/candidate_binding.hpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> void catalog(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the complete current catalog binding. |
| inputs / outputs | Catalog version and ordered full table declarations. |
| invariants | No semantic alpha-remapping/hash-only identity is performed. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Nested validation is assumed; sink/content errors propagate. |
| cost | Traverses every encoded table/metadata byte. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 216–239](../../../../../src/planner/candidate_binding.hpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class QueryView> void query(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete direct-CQ identity with occurrence and output order. |
| inputs / outputs | Variables/name/type, atom label/table/ordered terms, head variable/alias, contradiction. |
| invariants | Aliases, duplicate scopes, repeated outputs and ignored terms remain distinct. This is Catalog/Query binding, not every external SQL artifact field. |
| ownership | Borrows stable input during synchronous encoding; sink owns emitted bytes. |
| failure | Requires coherent validated view; sink/variant/content errors propagate. |
| cost | Full direct-query names/terms/head traversal and payload bytes. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0028

[Lines 240–241](../../../../../src/planner/candidate_binding.hpp#L240); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L240-L241:sha256:fe20eaed297b189a3d9ffb0fcf9e7b0a1ab42f068664f26ad932e06fd464edcc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define alias BindingEncoder in src/planner/candidate_binding.hpp. |
| inputs / outputs | A type alias or forward declaration has no runtime inputs or outputs; it gives following declarations a compile-time name. |
| invariants | The alias or incomplete type does not construct an object, validate data, or grant proof authority. |
| ownership | No runtime owner is created; any object lifetime comes from a later complete type and its members. |
| failure | Invalid or inconsistent type declarations fail compilation; no runtime failure is added. |
| cost | Compile-time name and type processing only; no runtime branch or allocation. |
| Design | [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0029

[Lines 242–248](../../../../../src/planner/candidate_binding.hpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string encode(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return ordinary complete-binding bytes without exposing sink or budget pointers. |
| inputs / outputs | Catalog/Query views and optional Budget to std::string. |
| invariants | Constructs full current v2 stream; not an exported checkpoint or public migration format. |
| ownership | Moves the local string member into caller ownership; input/budget borrows end with the call. |
| failure | Admission/variant/length/allocation failures discard the local partial string; counter debits need not roll back. |
| cost | Full encoding plus genuine string ownership move; explicit member move avoids an unnecessary ordinary copy. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0030

[Lines 249–254](../../../../../src/planner/candidate_binding.hpp#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline AllocatedBytes::String encode(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return complete-binding bytes under explicit native account attribution. |
| inputs / outputs | Views, account/purpose/owner and optional logical Budget to OwnerAllocator string. |
| invariants | Ordinary/accounted variants emit identical bytes; logical counters are distinct from actual memory-account grants. |
| ownership | Returned string retains its allocator/account and owns storage; no input-view or budget pointer escapes. |
| failure | Native memory/content/variant failures discard the private sink; no partial token returned. |
| cost | Full encoding/accounted storage growth and allocator-preserving member move, without ordinary JSON/string mirror. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0031

[Lines 255–255](../../../../../src/planner/candidate_binding.hpp#L255); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L255-L255:sha256:b1583dd1865796fdbff3bd5b9661e466e8ea50b4b6a4cf33c8713e25daba0513
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::binding_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |
