# `src/storage/accounted_index_scalar_work.hpp` — block usage map

[Source](../../../../../src/storage/accounted_index_scalar_work.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `81d2521ccf5f229a2553bcce305aaf1ace51281e36243e43e19e5292259b5d59`. 91 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../src/storage/accounted_index_scalar_work.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::numeric_limits&lt;std::size_t&gt;::digits &lt;= 64);; source comment (unverified): // These scalar work units admit tags/lengths before the later native · [reviewed contract](#b0001) |
| [B0002 · 17–31](../../../../../src/storage/accounted_index_scalar_work.hpp#L17) | Callable definition: inline void accounted_admit_scalar_copy(const ScalarView& value, IndexWorkAllowance& allowance) | calls admit, size, IndexFailure; source comment (unverified): // These scalar work units admit tags/lengths before the later native · [reviewed contract](#b0002) |
| [B0003 · 32–32](../../../../../src/storage/accounted_index_scalar_work.hpp#L32) | Explanatory comments or spacing. |  |
| [B0004 · 33–50](../../../../../src/storage/accounted_index_scalar_work.hpp#L33) | Callable definition: inline void accounted_admit_scalar_hash(const ScalarView& value, IndexWorkAllowance& allowance) | calls admit, size, IndexFailure; source comment (unverified): // Inline decimal rendering is at most sign + "0." +38 digits. · [reviewed contract](#b0004) |
| [B0005 · 51–51](../../../../../src/storage/accounted_index_scalar_work.hpp#L51) | Explanatory comments or spacing. |  |
| [B0006 · 52–60](../../../../../src/storage/accounted_index_scalar_work.hpp#L52) | Callable definition: \[\[nodiscard\]\] inline std::uint64_t accounted_admitted_hash(const AccountedTuple& tuple, IndexWorkAllowance& allowance) | calls admit, values, cells, accounted_admit_scalar_hash; returns tuple.hash(); 1 loop sites; source comment (unverified): // Native row length framing. · [reviewed contract](#b0006) |
| [B0007 · 61–61](../../../../../src/storage/accounted_index_scalar_work.hpp#L61) | Explanatory comments or spacing. |  |
| [B0008 · 62–72](../../../../../src/storage/accounted_index_scalar_work.hpp#L62) | Callable definition: \[\[nodiscard\]\] inline bool accounted_admitted_equal(const AccountedTuple& left, const AccountedTuple& right, IndexWorkAllowance& a… | calls layout, same_token, values, size; returns false; false; 2 loop sites; source comment (unverified): // Admit both complete payloads before row/scalar equality. This · [reviewed contract](#b0008) |
| [B0009 · 73–73](../../../../../src/storage/accounted_index_scalar_work.hpp#L73) | Explanatory comments or spacing. |  |
| [B0010 · 74–77](../../../../../src/storage/accounted_index_scalar_work.hpp#L74) | Callable definition: inline void accounted_admit_tuple_copy(const AccountedTuple& tuple, IndexWorkAllowance& allowance) | calls values, cells, accounted_admit_scalar_copy; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 78–78](../../../../../src/storage/accounted_index_scalar_work.hpp#L78) | Explanatory comments or spacing. |  |
| [B0012 · 79–89](../../../../../src/storage/accounted_index_scalar_work.hpp#L79) | Callable definition: \[\[nodiscard\]\] inline AccountedTuple accounted_admitted_projection(const AccountedProjection& projection, const AccountedTuple& tu… | calls source, same_token, layout, IndexFailure; returns projection.apply(tuple, tag); 1 loop sites; source comment (unverified): // Repeated slots were charged repeatedly; nullary projections copy no cells. · [reviewed contract](#b0012) |
| [B0013 · 90–91](../../../../../src/storage/accounted_index_scalar_work.hpp#L90) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage::detail · [reviewed contract](#b0013) |

## B0001

[Lines 1–16](../../../../../src/storage/accounted_index_scalar_work.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:1894c6d82d8e0b85992c551e54632222b10299e32406f814da47e8e4eefa36f6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_index_scalar_work.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/index_work.hpp"\`, \`"crown/storage/accounted_projection.hpp"\`, \`&lt;cstddef&gt;\`, \`&lt;cstdint&gt;\`, \`&lt;limits&gt;\`, \`&lt;variant&gt;\` for compilation; opens namespace \`crown::storage::detail\`. Source comment: These scalar work units admit tags/lengths before the later native helper. They are conservative payload domains, not total instruction counts, object sizeof, allocator bytes or a CPU measurement. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: These scalar work units admit tags/lengths before the later native helper. They are conservative payload domains, not total instruction counts, object sizeof, allocator bytes or a CPU measurement. Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 17–31](../../../../../src/storage/accounted_index_scalar_work.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void accounted_admit_scalar_copy(const ScalarView& value, IndexWorkAllowance& allowance) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one compact scalar's conservative copy/equality payload domain. |
| inputs / outputs | accounted_admit_scalar_copy reads ScalarView kind/length after admitting its field charge; it performs no actual payload copy. |
| invariants | String bytes remain borrowed; numeric/bool/date/InlineDecimal alternatives are inline. A failed later byte debit does not refund the already admitted field charge. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. An invalid compact scalar rejects with fixed IndexFailure(storage_contract). |
| cost | Debits two scalar_fields, then bytes: int64/date 8, bool 1, string length, bounded decimal 38. It reads tags/lengths rather than copying bytes; these are conservative scalar work units, not sizeof, allocator requests or elapsed CPU. |
| Design | [src/storage/accounted_index_scalar_work.hpp](../../../../../src/storage/accounted_index_scalar_work.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 33–50](../../../../../src/storage/accounted_index_scalar_work.hpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void accounted_admit_scalar_hash(const ScalarView& value, IndexWorkAllowance& allowance) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit compact hash framing and worst-case bounded decimal text. |
| inputs / outputs | accounted_admit_scalar_hash accounts tag plus type-specific hash payload/framing before a later native hash call. |
| invariants | Decimal text_capacity=41 is a bound for every admitted InlineDecimal; text length and tag framing are separate work debits, not physical allocations. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. An invalid compact scalar rejects with fixed IndexFailure(storage_contract). |
| cost | Debits two scalar_fields and one tag byte, then int64/date 8, bool 1, string length framing 8 plus actual length, or decimal framing 8 plus worst-case render 41. Admission itself is fixed tag/length work, not a hash execution or heap allocation. |
| Design | [src/storage/accounted_index_scalar_work.hpp](../../../../../src/storage/accounted_index_scalar_work.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 52–60](../../../../../src/storage/accounted_index_scalar_work.hpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline std::uint64_t accounted_admitted_hash(const AccountedTuple& tuple,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash an immutable native tuple only after complete scalar-domain admission. |
| inputs / outputs | Admits eight row-length bytes, walks every compact cell through accounted_admit_scalar_hash, then calls tuple.hash(). |
| invariants | This helper assumes a valid existing tuple; layout-token validation belongs to its caller. Publication/undo use cached hashes rather than invoking it. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. |
| cost | An admission pass over all fields followed by actual typed hash over fields/string bytes. InlineDecimal uses bounded stack rendering; no ordinary owning decimal text export. The returned uint64 is not equality proof. |
| Design | [src/storage/accounted_index_scalar_work.hpp](../../../../../src/storage/accounted_index_scalar_work.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 62–72](../../../../../src/storage/accounted_index_scalar_work.hpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline bool accounted_admitted_equal(const AccountedTuple& left, const AccountedTuple& right,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare token-matched native tuples after conservative complete-payload admission. |
| inputs / outputs | Returns false immediately for different layout tokens or sizes; otherwise debits copy units for both entire rows and evaluates left==right. |
| invariants | Debit can exceed short-circuit comparison work, including when the first field differs. A completed false comparison does not refund admitted work. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. |
| cost | Fixed early token/size checks; matching inputs pay two full admission traversals plus exact scalar/lexicographic deep-byte equality through the first difference. No row copy or allocation occurs on successful native comparison. |
| Design | [src/storage/accounted_index_scalar_work.hpp](../../../../../src/storage/accounted_index_scalar_work.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 74–77](../../../../../src/storage/accounted_index_scalar_work.hpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void accounted_admit_tuple_copy(const AccountedTuple& tuple, IndexWorkAllowance& allowance) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve native tuple copy/retirement scalar units without copying. |
| inputs / outputs | Walks all compact cells and calls accounted_admit_scalar_copy; callers use it before explicit copy or conservative retirement cleanup. |
| invariants | The function does not allocate a tuple, reserve allocator bytes or prove that a later operation will fit its memory account. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. |
| cost | O(fields) kind/length admission with type-specific scalar byte debits; it does not scan/copy the referenced string contents. Actual copying or destruction remains in the caller. |
| Design | [src/storage/accounted_index_scalar_work.hpp](../../../../../src/storage/accounted_index_scalar_work.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 79–89](../../../../../src/storage/accounted_index_scalar_work.hpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline AccountedTuple accounted_admitted_projection(const AccountedProjection& projection,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit selected native fields then execute the prevalidated projection path. |
| inputs / outputs | Requires exact projection source token, admits copy units for each ordered FieldId, then applies AccountedProjection(tuple, attribution). |
| invariants | Repeated slots debit repeatedly; nullary mapping debits no scalar cells. The compact AccountedTuple path uses its admitted source token and avoids full source-value revalidation. |
| ownership | Inputs/mapping are borrowed synchronously; result retains target metadata and owns copied selected bytes in the projection's original query account. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. Token mismatch throws fixed layout_mismatch; invalid projection or account/allocation failure propagates before a result escapes. |
| cost | Selected-field admission followed by selected bounds/sizing/copy/deep-string bytes and one funded row allocation. No temporary owning Row, public adapter or source-wide scan is introduced. |
| Design | [src/storage/accounted_index_scalar_work.hpp](../../../../../src/storage/accounted_index_scalar_work.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 90–91](../../../../../src/storage/accounted_index_scalar_work.hpp#L90); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L91:sha256:05825db20eae5643716749fd9f1dad1a40400e47f28da6432edfadc3bbd3864e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/accounted_index_scalar_work.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
