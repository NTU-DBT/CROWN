# `src/storage/index_scalar_work.hpp` — block usage map

[Source](../../../../../src/storage/index_scalar_work.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `dcb53840b6d32f46169491ca75571d491d3d943078ca7e3742aa7d5761f586d9`. 96 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../src/storage/index_scalar_work.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::numeric_limits&lt;std::size_t&gt;::digits &lt;= 64);; source comment (unverified): // Scalar grants below describe explicit payload domains. They are not · [reviewed contract](#b0001) |
| [B0002 · 18–32](../../../../../src/storage/index_scalar_work.hpp#L18) | Callable definition: inline void admit_scalar_copy(const Value& value, IndexWorkAllowance& allowance) | calls admit, size, Error; source comment (unverified): // Scalar grants below describe explicit payload domains. They are not · [reviewed contract](#b0002) |
| [B0003 · 33–35](../../../../../src/storage/index_scalar_work.hpp#L33) | Callable definition: inline void admit_scalar_copy(const ScalarView& value,IndexWorkAllowance& allowance) | calls accounted_admit_scalar_copy · [reviewed contract](#b0003) |
| [B0004 · 36–36](../../../../../src/storage/index_scalar_work.hpp#L36) | Explanatory comments or spacing. |  |
| [B0005 · 37–54](../../../../../src/storage/index_scalar_work.hpp#L37) | Callable definition: inline void admit_scalar_hash(const Value& value, IndexWorkAllowance& allowance) | calls admit, size, Error; source comment (unverified): // Public canonical Decimal::to_string is at most sign + "0." +38 digits. · [reviewed contract](#b0005) |
| [B0006 · 55–57](../../../../../src/storage/index_scalar_work.hpp#L55) | Callable definition: inline void admit_scalar_hash(const ScalarView& value,IndexWorkAllowance& allowance) | calls accounted_admit_scalar_hash · [reviewed contract](#b0006) |
| [B0007 · 58–58](../../../../../src/storage/index_scalar_work.hpp#L58) | Explanatory comments or spacing. |  |
| [B0008 · 59–66](../../../../../src/storage/index_scalar_work.hpp#L59) | Callable definition: \[\[nodiscard\]\] inline std::uint64_t admitted_hash(const Tuple& tuple, IndexWorkAllowance& allowance) | calls admit, values, admit_scalar_hash, hash; returns tuple.hash(); 1 loop sites; source comment (unverified): // Native row length framing. · [reviewed contract](#b0008) |
| [B0009 · 67–67](../../../../../src/storage/index_scalar_work.hpp#L67) | Explanatory comments or spacing. |  |
| [B0010 · 68–77](../../../../../src/storage/index_scalar_work.hpp#L68) | Callable definition: \[\[nodiscard\]\] inline bool admitted_equal(const Tuple& left, const Tuple& right, IndexWorkAllowance& allowance) | calls layout, same_token, values, size; returns false; false; 2 loop sites; source comment (unverified): // Admit both complete payloads before public exact-value comparison. This · [reviewed contract](#b0010) |
| [B0011 · 78–78](../../../../../src/storage/index_scalar_work.hpp#L78) | Explanatory comments or spacing. |  |
| [B0012 · 79–81](../../../../../src/storage/index_scalar_work.hpp#L79) | Callable definition: inline void admit_tuple_copy(const Tuple& tuple, IndexWorkAllowance& allowance) | calls values, admit_scalar_copy; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 82–82](../../../../../src/storage/index_scalar_work.hpp#L82) | Explanatory comments or spacing. |  |
| [B0014 · 83–94](../../../../../src/storage/index_scalar_work.hpp#L83) | Callable definition: \[\[nodiscard\]\] inline Tuple admitted_projection(const Projection& projection, const Tuple& tuple, IndexWorkAllowance& allowance) | calls source, same_token, layout, Error; returns projection.apply(tuple); 1 loop sites; source comment (unverified): // Repeated slots were charged repeatedly; nullary projections copy no cells. · [reviewed contract](#b0014) |
| [B0015 · 95–96](../../../../../src/storage/index_scalar_work.hpp#L95) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage::detail · [reviewed contract](#b0015) |

## B0001

[Lines 1–17](../../../../../src/storage/index_scalar_work.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:8e040b1a6e5f742411c149be3abca13a81a6706aba3923894e29eb3907b28466
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/index_scalar_work.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/index_work.hpp"\`, \`"crown/storage/layout.hpp"\`, \`"accounted_index_scalar_work.hpp"\`, \`&lt;cstddef&gt;\`, \`&lt;cstdint&gt;\`, \`&lt;limits&gt;\`, \`&lt;variant&gt;\` for compilation; opens namespace \`crown::storage::detail\`. Source comment: Scalar grants below describe explicit payload domains. They are not object sizeof, allocator bytes or a complete CPU/scalar-touch measurement for later public descriptor adapters. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Scalar grants below describe explicit payload domains. They are not object sizeof, allocator bytes or a complete CPU/scalar-touch measurement for later public descriptor adapters. Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 18–32](../../../../../src/storage/index_scalar_work.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void admit_scalar_copy(const Value& value, IndexWorkAllowance& allowance) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a public Value's conservative copy/equality scalar domain. |
| inputs / outputs | admit_scalar_copy(Value) debits its field charge before inspecting type/size and emits the same scalar copy units as the compact helper. |
| invariants | Public strings are owning Values but this helper borrows them; Decimal is bounded by its own construction contract. No Value/string copy occurs here. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. A valueless public scalar rejects with owning Error(storage_contract), whose diagnostic construction can allocate. |
| cost | Debits two scalar_fields, then bytes: int64/date 8, bool 1, string length, bounded decimal 38. It reads tags/lengths rather than copying bytes; these are conservative scalar work units, not sizeof, allocator requests or elapsed CPU. |
| Design | [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [tests/unit/index_scalar_work_test.cpp](../../../../../tests/unit/index_scalar_work_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 33–35](../../../../../src/storage/index_scalar_work.hpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void admit_scalar_copy(const ScalarView& value,IndexWorkAllowance& allowance) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use compact scalar copy admission through the public helper overload set. |
| inputs / outputs | admit_scalar_copy(ScalarView) delegates directly to accounted_admit_scalar_copy. |
| invariants | TupleValuesView iteration yields ScalarView, so this forwarding overload prevents an implicit owning Value/Row conversion. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. An invalid compact scalar rejects with fixed IndexFailure(storage_contract). |
| cost | Fixed forwarding plus the compact helper's tag/length and five-domain debit operations; no scalar allocation or deep byte scan. |
| Design | [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [tests/unit/index_scalar_work_test.cpp](../../../../../tests/unit/index_scalar_work_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 37–54](../../../../../src/storage/index_scalar_work.hpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void admit_scalar_hash(const Value& value, IndexWorkAllowance& allowance) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit public hash payload framing and bounded Decimal formatting allowance. |
| inputs / outputs | admit_scalar_hash(Value) emits type-specific units before a later opaque public hash; Decimal render allowance is 8+41 bytes after the tag. |
| invariants | The allowance does not eliminate later Decimal::to_string allocation or measure total CPU. A string's length framing and content length are distinct debits. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. A valueless public scalar rejects with owning Error(storage_contract), whose diagnostic construction can allocate. |
| cost | Debits two scalar_fields and one tag byte, then int64/date 8, bool 1, string length framing 8 plus actual length, or decimal framing 8 plus worst-case render 41. Admission itself is fixed tag/length work, not a hash execution or heap allocation. |
| Design | [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [tests/unit/index_scalar_work_test.cpp](../../../../../tests/unit/index_scalar_work_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 55–57](../../../../../src/storage/index_scalar_work.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void admit_scalar_hash(const ScalarView& value,IndexWorkAllowance& allowance) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward compact scalar hash admission without public scalar export. |
| inputs / outputs | admit_scalar_hash(ScalarView) uses accounted_admit_scalar_hash on the already compact descriptor. |
| invariants | String views stay borrowed and InlineDecimal remains inline; this adapter itself does not choose the tuple's final hash representation. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. An invalid compact scalar rejects with fixed IndexFailure(storage_contract). |
| cost | Fixed forwarding plus compact tag/length/framing debits. Later tuple.hash may still choose a legacy public representation; its cost belongs to admitted_hash. |
| Design | [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [tests/unit/index_scalar_work_test.cpp](../../../../../tests/unit/index_scalar_work_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 59–66](../../../../../src/storage/index_scalar_work.hpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline std::uint64_t admitted_hash(const Tuple& tuple,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit every public tuple field before its representation-specific hash. |
| inputs / outputs | Admits eight row-framing bytes, traverses tuple.values() via scalar-view overloads, and then calls tuple.hash(). |
| invariants | Layout-token validity is a caller precondition, not established by this helper. Preparation/probe callers cache the result before pointer publication/undo. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. Tuple-derived views/iterators retain existing immutable payload while traversing, without an owning Row export. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. |
| cost | Admission visits all fields; actual hash scans field/string bytes. Legacy Decimal hashing can allocate owning formatted text, while compact InlineDecimal hashing uses a bounded stack buffer. Public view/iterator refcounts add fixed per-object overhead, not a payload clone. |
| Design | [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [tests/unit/index_scalar_work_test.cpp](../../../../../tests/unit/index_scalar_work_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 68–77](../../../../../src/storage/index_scalar_work.hpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline bool admitted_equal(const Tuple& left, const Tuple& right,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit both full public payloads before exact token-aware equality. |
| inputs / outputs | Rejects different tokens or sizes without scalar debit; otherwise admits both complete TupleValuesView rows then evaluates tuple equality. |
| invariants | Full-payload debit deliberately overstates early-difference equality work; work is not refunded for a false result. It does not materialize std::vector/Row. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. Invalid public values can reject during scalar adaptation; no exception translation is added. |
| cost | Two full field/length admission passes plus exact value comparison through first difference, including deep string bytes and bounded inline decimal comparison. Retaining public views do not deep-copy rows. |
| Design | [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [tests/unit/index_scalar_work_test.cpp](../../../../../tests/unit/index_scalar_work_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 79–81](../../../../../src/storage/index_scalar_work.hpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void admit_tuple_copy(const Tuple& tuple, IndexWorkAllowance& allowance) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit public tuple copy/retirement units without cloning payload. |
| inputs / outputs | Traverses tuple.values() and admits each ScalarView copy domain. |
| invariants | This work reservation is not allocator-byte funding, a tuple clone or a complete CPU bound for a later public operation. |
| ownership | Borrows the caller's existing allowance and immutable input; debits mutate only its canonical balance, never create/refill a grant or retain payload. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. |
| cost | O(fields) type/length admission with retaining iterator/view handle work; no deep string copy or owning Row allocation in this helper. |
| Design | [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [tests/unit/index_scalar_work_test.cpp](../../../../../tests/unit/index_scalar_work_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 83–94](../../../../../src/storage/index_scalar_work.hpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline Tuple admitted_projection(const Projection& projection,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit selected public projection fields before explicit owning output. |
| inputs / outputs | Checks exact source token, debits each selected scalar copy domain, then calls Projection::apply(tuple). |
| invariants | Repeated/nullary fields retain their literal debit semantics. A native-backed public Projection adapter additionally validates the full source, while direct compact AccountedTuple projection has its separate fast path. |
| ownership | Input tuple/program are borrowed synchronously. Output owns selected values through the descriptor's ordinary or retained-account native factory. |
| failure | Work denial propagates according to the allowance's fixed/legacy diagnostic policy. Earlier successful debits remain consumed; no input/membership mutation or catch/retry occurs. Token mismatch throws public layout_mismatch; descriptor/domain/allocation failures propagate. No temporary recovery owner or grant is created. |
| cost | Selected-field admission plus actual public apply. Standalone apply exports selected Values and validates target; native-backed public apply validates source and funds compact/output owners. The debit is not a total scalar-touch or CPU measurement of those adapters. |
| Design | [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [tests/unit/index_scalar_work_test.cpp](../../../../../tests/unit/index_scalar_work_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 95–96](../../../../../src/storage/index_scalar_work.hpp#L95); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L96:sha256:05825db20eae5643716749fd9f1dad1a40400e47f28da6432edfadc3bbd3864e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/index_scalar_work.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
