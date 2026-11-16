# `src/frontend/sql_rows_eval.hpp` — block usage map

[Source](../../../../../src/frontend/sql_rows_eval.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics.

Snapshot SHA-256: `ef138564e86e6d0c6db7af579dc1ceebf6bb09f2e6ac76afce81e3e82f6dc9bc`. 66 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/frontend/sql_rows_eval.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–9](../../../../../src/frontend/sql_rows_eval.hpp#L7) | Callable definition: inline void step(storage::IndexWorkAllowance* work) | calls admit · [reviewed contract](#b0002) |
| [B0003 · 10–14](../../../../../src/frontend/sql_rows_eval.hpp#L10) | Callable definition: inline bool same(const SqlRowCell& left, const SqlRowCell& right, storage::IndexWorkAllowance* work) | calls sql_detail::admit_value; returns !left && !right; *left == *right · [reviewed contract](#b0003) |
| [B0004 · 15–20](../../../../../src/frontend/sql_rows_eval.hpp#L15) | Explanatory comments or spacing. | source comment (unverified): // Use an occurrence from this live program, a complete validated input, and · [reviewed contract](#b0004) |
| [B0005 · 21–65](../../../../../src/frontend/sql_rows_eval.hpp#L21) | Callable definition: inline bool adapt(const SqlRowsProgram& program, const SqlRowsOccurrence& occurrence, std::span&lt;const SqlRowCell&gt; input, std::spa… | calls initial_values, step, same, ~Borrows; returns false; false; 9 loop sites; source comment (unverified): // Use an occurrence from this live program, a complete validated input, and · [reviewed contract](#b0005) |
| [B0006 · 66–66](../../../../../src/frontend/sql_rows_eval.hpp#L66) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend::rows_detail · [reviewed contract](#b0006) |

## B0001

[Lines 1–6](../../../../../src/frontend/sql_rows_eval.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:8d12368044cc9dffe1e485d85676b2509180ea912d8f7e11794a2003b98fef0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (sql_rows_value.hpp, sql_scalar.hpp) and opens crown::frontend::rows_detail scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/frontend/sql_rows_eval.hpp](../../../../../src/frontend/sql_rows_eval.hpp), [docs/code_specs/files/src/frontend/sql_rows_eval.hpp.md](sql_rows_eval.hpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0002

[Lines 7–9](../../../../../src/frontend/sql_rows_eval.hpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void step(storage::IndexWorkAllowance* work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit adapter steps and compare NULL-aware fixed-key values. |
| inputs / outputs | step admits one structural unit; same treats two NULLs equal and present cells by typed scalar equality. |
| invariants | same is used for IS NULL/fixed keys; ordinary equality checks NULL separately. Present operands are charged left then right. |
| ownership | Borrows cells and original caller allowance. |
| failure | Work failure preserves earlier successful debits. |
| cost | O(1) step; present equality includes scalar byte comparison. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp §L13-20](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp), [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/storage/index_work.hpp §L36-52](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/storage/index_work.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0003

[Lines 10–14](../../../../../src/frontend/sql_rows_eval.hpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool same(const SqlRowCell& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare NULL-aware grounding/key identity. |
| inputs / outputs | Two optional scalar views and optional existing grant to Boolean. |
| invariants | Two absent cells are equal here for IS NULL/key identity; ordinary equality callers reject NULL before calling. |
| ownership | Borrows cells and grant; admits present left then right fields/bytes. |
| failure | Later failure keeps prior debits; fixed/legacy error mode belongs to the supplied grant. |
| cost | Constant NULL tests; otherwise scalar comparison, including text/decimal width, with no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0004

[Lines 15–20](../../../../../src/frontend/sql_rows_eval.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L20:sha256:e91e76e81fb9cceaf32c526bc3ce3bd8c637554fbffbbf1d8f95816860d0090b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Use an occurrence from this live program, a complete validated input, and disjoint scratch initialized once from initial_values(); output must fit the projection. On true, strings borrow input/program until the caller freezes the native view. On false/throw, output is unspecified and must not be read. Written dynamic slots are cleared on every exit. No Row or per-call allocation. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/frontend/sql_rows_eval.hpp lines 13-22; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/frontend/sql_rows_eval.hpp](../../../../../src/frontend/sql_rows_eval.hpp), [docs/code_specs/files/src/frontend/sql_rows_eval.hpp.md](sql_rows_eval.hpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0005

[Lines 21–65](../../../../../src/frontend/sql_rows_eval.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool adapt(const SqlRowsProgram& program, const SqlRowsOccurrence& occurrence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cheap physical guards before dynamic slot writes. |
| inputs / outputs | Same-program occurrence, validated full input, initialized scratch and output capacity enter; guards can filter early. |
| invariants | Non-null/equality/fixed indices are trusted; ordinary equality never admits NULL=NULL. Input remains alive and stable. |
| ownership | No retained row/copy/allocation; caller owns disjoint buffers. |
| failure | False leaves output unspecified; work exceptions propagate before current guarded action. |
| cost | O(visited guards + compared byte widths); no allocation. |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §borrow item 4](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

```text
struct Borrows {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate dynamic reads/opcodes and clear all temporary borrows. |
| inputs / outputs | Copy input descriptors to dynamic targets; execute topological instructions; count successful writes. |
| invariants | Known constant targets are excluded; counters advance only after nonthrowing assignments; cleanup visits exactly completed writes. |
| ownership | Borrows destructor resets scratch cells on normal/early/exception exit; output has independent borrowed descriptors. |
| failure | Evaluator/work exception triggers cleanup and propagates unchanged. |
| cost | O(executed inputs + operations + scalar work), same-order cleanup, no owning allocations. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/storage/accounted_row.cpp §L17-19](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/storage/accounted_row.cpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp §L38-86](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

```text
for (const auto predicate : occurrence.predicates) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Filter by SQL truth and emit complete native encoded row. |
| inputs / outputs | Only TRUE predicates pass; projection writes present payloads or canonical NULL payload/presence. |
| invariants | Every output field is written on success; value-kind NULL is a contract violation. No output is valid on false/exception. |
| ownership | Successful output text borrows input/program until caller freezes it. |
| failure | Work/contract faults propagate; Borrows resets dynamic scratch. |
| cost | O(predicates + projection count), scalar copies only. |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §encoding and borrow arguments](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0006

[Lines 66–66](../../../../../src/frontend/sql_rows_eval.hpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L66:sha256:685b7aeb8c0c362afd49ed324cf9944a60b9d99d90ee456586559ff86c24670d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend::rows_detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/sql_rows_eval.hpp](../../../../../src/frontend/sql_rows_eval.hpp), [docs/code_specs/files/src/frontend/sql_rows_eval.hpp.md](sql_rows_eval.hpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |
