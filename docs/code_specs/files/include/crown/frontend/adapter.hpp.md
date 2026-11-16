# `include/crown/frontend/adapter.hpp` — block usage map

[Source](../../../../../../include/crown/frontend/adapter.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Apply occurrence-local constants/repeated-variable tests and positional projection.

Snapshot SHA-256: `fc07b4c7a91f57e59e569150096bb832d5c90e5c06f7acf895af962cbf5269b0`. 36 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../../sql_support.md), [docs/sql_parser.md](../../../../../sql_parser.md), [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_admission.md](../../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/frontend/adapter.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../../include/crown/frontend/adapter.hpp#L8) | Type/record definition: struct OccurrenceTransition |  · [reviewed contract](#b0002) |
| [B0003 · 9–13](../../../../../../include/crown/frontend/adapter.hpp#L9) | Type/record definition: struct AdaptedEpoch |  · [reviewed contract](#b0003) |
| [B0004 · 14–19](../../../../../../include/crown/frontend/adapter.hpp#L14) | Explanatory comments or spacing. | source comment (unverified): // Correctness-first adapter state, independent of the maintained join runtime. · [reviewed contract](#b0004) |
| [B0005 · 20–35](../../../../../../include/crown/frontend/adapter.hpp#L20) | Type/record definition: class AdapterState | returns query_; physical_; source comment (unverified): // Correctness-first adapter state, independent of the maintained join runtime. · [reviewed contract](#b0005) |
| [B0006 · 36–36](../../../../../../include/crown/frontend/adapter.hpp#L36) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend · [reviewed contract](#b0006) |

## B0001

[Lines 1–7](../../../../../../include/crown/frontend/adapter.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using SupportCounts = std::map<Row, std::uint64_t>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map each distinct projected core row to the number of full physical rows supporting it in one occurrence. |
| inputs / outputs | The map key is an owning \`Row\`; the mapped \`uint64_t\` is the occurrence-local support count maintained by \`AdapterState\`. |
| invariants | Physical row identity is retained before projection, so different full rows may contribute to one logical row. The alias itself does not constrain counts to be positive or reject overflow. |
| ownership | \`std::map\` owns its copied row keys and ordering; \`AdapterState\` owns the per-occurrence maps alongside logical relations. |
| failure | \`AdapterState\` checks \`UINT64_MAX\` before increment and reports \`support_overflow\`; ordinary map/row allocation failures can also interrupt preparation. |
| cost | Operations compare and copy full \`Row\` keys. The reference \`apply\` also copies physical, logical, and support state even for a valid no-op. |
| Design | [include/crown/frontend/adapter.hpp §support alias and state](../../../../../../include/crown/frontend/adapter.hpp), [src/frontend/adapter.cpp §add_support and copy-commit apply](../../../../../../src/frontend/adapter.cpp), [docs/sql_normalization.md §projection supports](../../../../../sql_normalization.md) |

## B0002

[Lines 8–8](../../../../../../include/crown/frontend/adapter.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OccurrenceTransition {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report one alias's membership change for a physical event. |
| inputs / outputs | Occurrence ID and SetDelta, including an empty delta. |
| invariants | Epoch order follows the base route; no-op aliases remain represented. |
| ownership | Owns delta sets/rows. |
| failure | Allocation occurs during candidate epoch preparation, before publication. |
| cost | Delta storage/copy and ordered-set operations scale with emitted values. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0003

[Lines 9–13](../../../../../../include/crown/frontend/adapter.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AdaptedEpoch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the committed physical event and all alias deltas together. |
| inputs / outputs | Sequence, physical membership-change flag and ordered occurrence transitions. |
| invariants | Valid no-op can have input_changed=false and still consume a sequence. |
| ownership | Owns all transitions independently of later adapter updates. |
| failure | No partial epoch is returned if preparation fails. |
| cost | Vector/delta allocation during preparation; move-return transfers the prepared owner. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0004

[Lines 14–19](../../../../../../include/crown/frontend/adapter.hpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L19:sha256:255b48a064b04da168b9eb18d0746d3efee9bd3b94dca75e80c60933f0843e4a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Correctness-first adapter state, independent of the maintained join runtime. Full physical row identity is retained. A public physical update commits all affected aliases together, after constraint checks and output allocation. Each apply copies physical, logical and support state, including valid no-ops; this reference adapter does not carry the native runtime's update cost bound. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/frontend/adapter.hpp lines 12-21; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/frontend/adapter.hpp](../../../../../../include/crown/frontend/adapter.hpp), [docs/code_specs/files/include/crown/frontend/adapter.hpp.md](adapter.hpp.md), [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_admission.md](../../../../../sql_admission.md) |

## B0005

[Lines 20–35](../../../../../../include/crown/frontend/adapter.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AdapterState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a correctness-reference copy-commit physical-to-logical adapter. |
| inputs / outputs | Owns query/physical/logical/support state; apply returns a committed alias epoch. |
| invariants | Full physical identity and projected support counts survive every atomic update; getters expose read-only borrows. |
| ownership | Caller keeps this object alive; returned references are not independent snapshots across apply/destruction. |
| failure | Constructor/apply rely on ordinary RAII of owned candidate copies; no transaction is externally visible before swaps. |
| cost | Construction scans/adapts bases; every apply copies all three state collections and validates constraints, including no-ops. Not the optimized native runtime. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

```text
query() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the current specialized NormalizedSql. |
| inputs / outputs | Returns a const reference to the corresponding member. |
| invariants | No mutation, validation or independent snapshot is performed. |
| ownership | Member reference requires AdapterState lifetime; it is not a historical snapshot of later content. |
| failure | Declared noexcept; apply does not replace query_, and owner destruction ends the borrow. |
| cost | Fixed reference return; no allocation or population scan. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

```text
physical() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the current full physical Database. |
| inputs / outputs | Returns a const reference to the corresponding member. |
| invariants | No mutation, validation or independent snapshot is performed. |
| ownership | Member reference requires AdapterState lifetime; it is not a historical snapshot of later content. |
| failure | Declared noexcept; member reference survives apply, whose swaps replace contents and can invalidate nested row/map iterators. |
| cost | Fixed reference return; no allocation or population scan. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

```text
logical() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the current occurrence-level logical Database. |
| inputs / outputs | Returns a const reference to the corresponding member. |
| invariants | No mutation, validation or independent snapshot is performed. |
| ownership | Member reference requires AdapterState lifetime; it is not a historical snapshot of later content. |
| failure | Declared noexcept; member reference survives apply, whose swaps replace contents and can invalidate nested row/map iterators. |
| cost | Fixed reference return; no allocation or population scan. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

```text
supports() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the current per-occurrence support-map vector. |
| inputs / outputs | Returns a const reference to the corresponding member. |
| invariants | No mutation, validation or independent snapshot is performed. |
| ownership | Member reference requires AdapterState lifetime; it is not a historical snapshot of later content. |
| failure | Declared noexcept; member reference survives apply, whose swaps replace contents and can invalidate nested row/map iterators. |
| cost | Fixed reference return; no allocation or population scan. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

```text
sequence() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the last committed contiguous physical sequence. |
| inputs / outputs | Returns uint64 by value, starting at0. |
| invariants | Only successful apply advances it, including valid membership no-ops. |
| ownership | Independent scalar copy. |
| failure | Declared noexcept; no validation. |
| cost | Fixed value read, no allocation. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../../semantics.md) |

## B0006

[Lines 36–36](../../../../../../include/crown/frontend/adapter.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:2fc33ff8830b8cd06d6971e8e31b29a8803f152d87e09a3fc4092b3efecdac93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/frontend/adapter.hpp](../../../../../../include/crown/frontend/adapter.hpp), [docs/code_specs/files/include/crown/frontend/adapter.hpp.md](adapter.hpp.md), [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_admission.md](../../../../../sql_admission.md) |
