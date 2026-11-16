# `tests/support/frozen_binding_v2.hpp` — block usage map

[Source](../../../../../tests/support/frozen_binding_v2.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `5afddf07483d5872cb171968e170f926471c73d7b2f8ac391c61a1b0d4647ad4`. 193 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–27](../../../../../tests/support/frozen_binding_v2.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(CHAR_BIT == 8);; source comment (unverified): // Private binding format v2 directly records every Catalog/Query field. It · [reviewed contract](#b0001) |
| [B0002 · 28–33](../../../../../tests/support/frozen_binding_v2.hpp#L28) | Callable definition: void word(std::uint64_t value) | calls push_back; growth push_back; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 34–37](../../../../../tests/support/frozen_binding_v2.hpp#L34) | Callable definition: void unsigned_integer(std::uint64_t value) | calls push_back, word; growth push_back · [reviewed contract](#b0003) |
| [B0004 · 38–41](../../../../../tests/support/frozen_binding_v2.hpp#L38) | Callable definition: void signed_integer(std::int64_t value) | calls push_back, word; growth push_back · [reviewed contract](#b0004) |
| [B0005 · 42–45](../../../../../tests/support/frozen_binding_v2.hpp#L42) | Callable definition: template&lt;class Enum&gt; void enumeration(Enum value) | calls push_back, word; growth push_back · [reviewed contract](#b0005) |
| [B0006 · 46–49](../../../../../tests/support/frozen_binding_v2.hpp#L46) | Callable definition: void boolean(bool value) | calls push_back; growth push_back · [reviewed contract](#b0006) |
| [B0007 · 50–54](../../../../../tests/support/frozen_binding_v2.hpp#L50) | Callable definition: void string(std::string_view value) | calls push_back, word, size, append; growth push_back · [reviewed contract](#b0007) |
| [B0008 · 55–58](../../../../../tests/support/frozen_binding_v2.hpp#L55) | Callable definition: void record(std::string_view kind) | calls push_back, string; growth push_back · [reviewed contract](#b0008) |
| [B0009 · 59–62](../../../../../tests/support/frozen_binding_v2.hpp#L59) | Callable definition: void sequence(std::size_t count) | calls push_back, word; growth push_back · [reviewed contract](#b0009) |
| [B0010 · 63–66](../../../../../tests/support/frozen_binding_v2.hpp#L63) | Callable definition: void presence(bool present) | calls push_back; growth push_back · [reviewed contract](#b0010) |
| [B0011 · 67–70](../../../../../tests/support/frozen_binding_v2.hpp#L67) | Callable definition: void column_ids(const std::vector&lt;ColumnId&gt;& ids) | calls sequence, size, unsigned_integer; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 71–83](../../../../../tests/support/frozen_binding_v2.hpp#L71) | Callable definition: void column(const Column& value) | calls record, string, enumeration, boolean · [reviewed contract](#b0012) |
| [B0013 · 84–99](../../../../../tests/support/frozen_binding_v2.hpp#L84) | Callable definition: void constraint(const Constraint& value) | calls record, string, column_ids, enumeration · [reviewed contract](#b0013) |
| [B0014 · 100–123](../../../../../tests/support/frozen_binding_v2.hpp#L100) | Callable definition: void table(const Table& value) | calls record, string, sequence, size; 4 loop sites · [reviewed contract](#b0014) |
| [B0015 · 124–141](../../../../../tests/support/frozen_binding_v2.hpp#L124) | Callable definition: void scalar(const Value& value) | calls record, unsigned_integer, index, signed_integer; source comment (unverified): // Explicit native variant index distinguishes every scalar type, including · [reviewed contract](#b0015) |
| [B0016 · 142–154](../../../../../tests/support/frozen_binding_v2.hpp#L142) | Callable definition: void term(const Term& value) | calls record, unsigned_integer, index, scalar; source comment (unverified): // IgnoredColumn has no payload. · [reviewed contract](#b0016) |
| [B0017 · 155–160](../../../../../tests/support/frozen_binding_v2.hpp#L155) | Callable definition: void catalog(const Catalog& value) | calls record, unsigned_integer, sequence, size; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 161–184](../../../../../tests/support/frozen_binding_v2.hpp#L161) | Callable definition: void query(const Query& value) | calls record, sequence, size, string; 4 loop sites · [reviewed contract](#b0018) |
| [B0019 · 185–186](../../../../../tests/support/frozen_binding_v2.hpp#L185) | Closes surrounding scope/type. | source comment (unverified): // Test byte equivalence only: editable source metadata is not admission authority. · [reviewed contract](#b0019) |
| [B0020 · 187–192](../../../../../tests/support/frozen_binding_v2.hpp#L187) | Callable definition: std::string binding_bytes(const Catalog& catalog, const Query& query) | calls catalog, query, std::move; returns std::move(encoder.bytes); source comment (unverified): // Test byte equivalence only: editable source metadata is not admission authority. · [reviewed contract](#b0020) |
| [B0021 · 193–193](../../../../../tests/support/frozen_binding_v2.hpp#L193) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::frozen_binding_v2 · [reviewed contract](#b0021) |

## B0001

[Lines 1–27](../../../../../tests/support/frozen_binding_v2.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BindingEncoder
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the frozen v2 candidate-binding byte format independent of the current production encoder for equivalence tests. |
| inputs / outputs | Mutable bytes starts with CROWN-CANDIDATE-BINDING;2; and append methods serialize every ordered Catalog/Query field. |
| invariants | Editable metadata encoding is not semantic validation, typed admission, proof authority or a digest. Eight-bit bytes and size_t no wider than uint64 are compile-time requirements. |
| ownership | Owns ordinary std::string storage; implicit copy deep-copies bytes, implicit move follows std::string ownership. It constructs no JSON DOM or MemoryAccount. |
| failure | Append/allocation and unsupported scalar/term errors propagate; a failed encoder can retain an unreturned partial prefix. |
| cost | Visits every serialized field/byte with ordinary string growth; decimal rendering has separate temporary cost. No per-enumeration quantum claim. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::string bytes =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the exact frozen wire prefix and subsequently appended bytes. |
| inputs / outputs | Initially the literal version prefix; helpers mutate it and binding_bytes moves it into the return. |
| invariants | Literal tags, field order, sequence lengths and variant indices are versioned comparison evidence, not collision-resistant hashing. |
| ownership | Ordinary independent string payload; source DTOs are borrowed only during append. |
| failure | Construction/growth can fail; successful return alone does not validate input semantics. |
| cost | Prefix initialization plus amortized growth/copy of appended bytes; no hidden query-account funding. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 28–33](../../../../../tests/support/frozen_binding_v2.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void word(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one fixed-width big-endian word. |
| inputs / outputs | Input uint64 produces exactly eight bytes, shifts 56 through 0. |
| invariants | Host endian is irrelevant and every octet is retained. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | Eight push_back operations and possible capacity growth. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 34–37](../../../../../tests/support/frozen_binding_v2.hpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unsigned_integer(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame an unsigned field. |
| inputs / outputs | Appends U then the eight-byte word. |
| invariants | No range reduction or semantic identifier validation. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | One tag plus eight-byte append. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 38–41](../../../../../tests/support/frozen_binding_v2.hpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void signed_integer(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame a signed int64 field without text conversion. |
| inputs / outputs | Appends I then modulo-2^64 cast to uint64. |
| invariants | Negative values preserve their specified modulo representation. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | Fixed tag/cast/eight-byte append. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 42–45](../../../../../tests/support/frozen_binding_v2.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Enum> void enumeration(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame an enum representation. |
| inputs / outputs | Appends E then the cast uint64 representation. |
| invariants | No enum-domain validation; test DTOs must supply intended values. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | Fixed tag/cast/eight-byte append. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 46–49](../../../../../tests/support/frozen_binding_v2.hpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boolean(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame a Boolean value. |
| inputs / outputs | Appends B then exactly zero or one byte. |
| invariants | Boolean payload differs from numeric and optional-presence tags. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | Two byte appends. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 50–54](../../../../../tests/support/frozen_binding_v2.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void string(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame an exact byte string. |
| inputs / outputs | Appends S, uint64 length and all view bytes. |
| invariants | Embedded NUL and invalid UTF-8 are retained; view must remain valid until append finishes. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | O(length) copy plus framing and possible growth. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 55–58](../../../../../tests/support/frozen_binding_v2.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void record(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame a record type name. |
| inputs / outputs | Appends R then the length-framed kind string. |
| invariants | Kind bytes and following field order identify the private schema. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | O(kind length) copy plus framing. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 59–62](../../../../../tests/support/frozen_binding_v2.hpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sequence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame an ordered collection count. |
| inputs / outputs | Appends A then size_t count as uint64. |
| invariants | The file static_assert proves the supported width; caller must append exactly that many items. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | Fixed tag and word append. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 63–66](../../../../../tests/support/frozen_binding_v2.hpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void presence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame optional-field presence. |
| inputs / outputs | Appends P then a zero/one byte. |
| invariants | Caller appends payload only when present; absent and empty payload remain different. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | Two byte appends. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 67–70](../../../../../tests/support/frozen_binding_v2.hpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void column_ids(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode ordered column IDs. |
| inputs / outputs | Appends array size and each ID as unsigned field. |
| invariants | Order and duplicates are retained without catalog validation. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | O(number of IDs) fixed-width writes plus growth. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 71–83](../../../../../tests/support/frozen_binding_v2.hpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void column(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete column metadata. |
| inputs / outputs | Name, type, nullable, collation and optional decimal precision/scale are appended in fixed order. |
| invariants | Optional decimal presence is encoded even for malformed editable metadata; no schema admission occurs. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | O(name bytes) plus fixed metadata and growth. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 84–99](../../../../../tests/support/frozen_binding_v2.hpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constraint(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode either unique or foreign-key constraint metadata. |
| inputs / outputs | Unique includes name/columns/status; foreign key additionally references table and ordered target columns. |
| invariants | Variant branch and record tag differ; no uniqueness, foreign-key truth or status evidence is established. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | O(name bytes + participating column IDs) writes. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 100–123](../../../../../tests/support/frozen_binding_v2.hpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void table(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode table schema and every statistics/hint field. |
| inputs / outputs | Appends columns, source schema version, constraints, optional row count, ordered distinct estimates and key hints. |
| invariants | Stats/hints are descriptive metadata; sequence order, optionals and hint flags all bind exactly. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | Visits all table metadata and strings; output growth proportional to wire size. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 124–141](../../../../../tests/support/frozen_binding_v2.hpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a Value with explicit variant identity. |
| inputs / outputs | Appends value record and variant index, then int64, string, bool, Date epoch days or Decimal canonical text. |
| invariants | Date/int64 and decimal/string stay distinct; raw string bytes are retained. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | String growth/decimal conversion can throw; scalar/term reject unsupported alternatives with candidate_binding_kind. No local catch or rollback is promised. |
| cost | Fixed numeric encoding or O(string/decimal text size) copies; Decimal::to_string may allocate. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 142–154](../../../../../tests/support/frozen_binding_v2.hpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void term(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a query term with its variant tag. |
| inputs / outputs | Appends term index then variable ID, scalar constant or no extra payload for Ignored. |
| invariants | Ignored is distinct from every Value and variable; no variable-scope admission. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | String growth/decimal conversion can throw; scalar/term reject unsupported alternatives with candidate_binding_kind. No local catch or rollback is promised. |
| cost | Fixed framing plus the scalar payload's actual cost. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 155–160](../../../../../tests/support/frozen_binding_v2.hpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void catalog(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode catalog version and all tables. |
| inputs / outputs | Appends catalog record, version, count and ordered table encodings. |
| invariants | Binding includes unreferenced catalog tables and descriptive statistics too. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | Visits the full catalog; not only the query's referenced source subset. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 161–184](../../../../../tests/support/frozen_binding_v2.hpp#L161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void query(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode all variables, atom occurrences/terms, outputs and contradiction. |
| inputs / outputs | Appends ordered variable declarations, atoms with occurrence/table IDs, head variable/alias pairs and Boolean contradiction. |
| invariants | Aliases, repetition and declared-but-unused metadata stay binding-sensitive; arbitrary Query DTO is not normalized or admitted. |
| ownership | Mutates only this encoder's owning ordinary string; input references/views are not retained. |
| failure | Ordinary string allocation/length errors propagate; no recovery or rollback wrapper is added. |
| cost | Visits all query fields/strings/terms, including nested scalar conversion. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 185–186](../../../../../tests/support/frozen_binding_v2.hpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L186:sha256:7ba10656821c40a461e37372990712fe2af3f8852914fe18493b5ea9ef31dad3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in frozen_binding_v2.hpp: struct BindingEncoder. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 187–192](../../../../../tests/support/frozen_binding_v2.hpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string binding_bytes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the frozen complete binding used against the production v2 encoder in test executables. |
| inputs / outputs | Borrows Catalog and Query, serializes catalog then query, and moves the local string out. |
| invariants | This test-header function is not inline; current includers are single test translation units. Equality proves the exercised byte format, not validity/proof authority. |
| ownership | Returned ordinary string owns all bytes after sources/encoder die; no shared native key or account is returned. |
| failure | Any construction/append/unsupported-kind failure propagates with no result; private partial bytes are destroyed. |
| cost | O(total encoded metadata bytes) traversal/copy/growth plus decimal rendering; return moves ordinary storage where supported. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/unit/ranking_binding_test.cpp](../../../../../tests/unit/ranking_binding_test.cpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [third_party/nlohmann/patches/crown-cleanup-oom.patch](../../../../../third_party/nlohmann/patches/crown-cleanup-oom.patch), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 193–193](../../../../../tests/support/frozen_binding_v2.hpp#L193); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L193-L193:sha256:e8a9e7dce23d88ee4589cfb4519993a8d8f4c005de2cdacdac2cf087c4827447
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in frozen_binding_v2.hpp: namespace crown::planner::frozen_binding_v2. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |
