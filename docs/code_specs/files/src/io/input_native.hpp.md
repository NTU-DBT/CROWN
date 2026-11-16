# `src/io/input_native.hpp` — block usage map

[Source](../../../../../src/io/input_native.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `86e6c33a0f255553e60b620bc0e2febdb052cf3625002b7d238f266517799e98`. 16 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/io/input_native.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // A permanent row rejection can be retained instead of an unusable caller Row. · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../src/io/input_native.hpp#L8) | Type/record definition: enum class RowProblem | source comment (unverified): // A permanent row rejection can be retained instead of an unusable caller Row. · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../src/io/input_native.hpp#L9) | Type/record definition: struct RowIssue |  · [reviewed contract](#b0003) |
| [B0004 · 10–16](../../../../../src/io/input_native.hpp#L10) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::io::input_detail · [reviewed contract](#b0004) |

## B0001

[Lines 1–7](../../../../../src/io/input_native.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Connect deferred typed-row rejection metadata to the actual catalog/view validators. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–8](../../../../../src/io/input_native.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class RowProblem {none,table,arity,scalar,type,decimal_catalog,decimal_domain};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify the first permanent row/domain rejection without retaining the malformed caller row. |
| inputs / outputs | Finite none/table/arity/scalar/type/decimal_catalog/decimal_domain values are produced by issue_for and consumed by reject_row. |
| invariants | Classification is not a checked-row token; validators also check envelope and transport limits in their established order. |
| ownership | Inline enum only, with no payload/backing ownership. |
| failure | Enum creation does not throw; an invalid enum entering reject_row reaches its contract termination fallback. |
| cost | Fixed-size copy/comparison; no row scan until row_issue executes. |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 9–9](../../../../../src/io/input_native.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RowProblem problem=RowProblem::none;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the deferred row-problem discriminator. |
| inputs / outputs | Defaults none; issue_for assigns the first applicable RowProblem. |
| invariants | none is only a successful classification for the examined table/row, not a transferable checked-row token. |
| ownership | Inline enum, no row/catalog retained. |
| failure | Storing/copying cannot throw; reject_row handles the classification later. |
| cost | O(1). |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
field=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve first offending field index for contextual diagnostics. |
| inputs / outputs | field records current schema-field iteration; used for type/decimal_domain column name lookup. |
| invariants | Usable only with matching catalog/table/classification; arbitrary field edits may violate private callee preconditions. |
| ownership | Inline scalar, no copied name/row. |
| failure | No storage failure; reject_row builds diagnostic later. |
| cost | O(1). |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
std::size_t arity=0,field=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve supplied row arity for head-time limit precedence. |
| inputs / outputs | arity initialized from values.size(), including malformed row with wrong schema arity. |
| invariants | Envelope columns limit may reject before the saved schema arity error; no row backing required to preserve this count. |
| ownership | Inline size_t, independent of caller row lifetime. |
| failure | No allocation/failure while storing count. |
| cost | O(1). |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
struct RowIssue {RowProblem problem=RowProblem::none;std::size_t arity=0,field=0;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the minimal facts needed to report a rejected queued row at the correct head boundary. |
| inputs / outputs | problem defaults to none; arity records supplied cells; field identifies the first offending column. |
| invariants | Error fields must come from the same stable catalog/table/row classification used by the owned queue item; arbitrary edits are not safe validation authority. |
| ownership | Three inline scalar fields, freely copied; retains no catalog, row, scalar text or account. |
| failure | Construction/copy does not throw; reject_row uses the corresponding valid field/table context. |
| cost | O(1) record storage and copy; original classification scans fields separately. |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 10–16](../../../../../src/io/input_native.hpp#L10); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] RowIssue row_issue(const Catalog&,TableId,storage::TupleValuesView);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify a row against Catalog without formatting diagnostics. |
| inputs / outputs | Accepts table/borrowed values and returns RowIssue; no source mutation. |
| invariants | Catalog backing must remain stable; internal RowIssue is descriptive state, not a public proof factory. Sequence continuity and offset monotonicity are checked by the source owner. |
| ownership | Catalog and explicit row/source views are borrowed; copying a tuple-derived TupleValuesView can retain its existing payload without cloning it. |
| failure | Delegates to input_view.cpp; malformed rows can fail on scalar access, and validators construct allocating diagnostics on rejection; no catch/translation here. |
| cost | Classification is O(fields) plus inline decimal checks. Validation scans payload/source bytes and bounded decimal rendering; no new owned row on success. |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
[[nodiscard]] RowIssue row_issue(const program::Catalog&,TableId,storage::TupleValuesView);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify a row against program::Catalog without formatting diagnostics. |
| inputs / outputs | Accepts table/borrowed values and returns RowIssue; no source mutation. |
| invariants | Catalog backing must remain stable; internal RowIssue is descriptive state, not a public proof factory. Sequence continuity and offset monotonicity are checked by the source owner. |
| ownership | Catalog and explicit row/source views are borrowed; copying a tuple-derived TupleValuesView can retain its existing payload without cloning it. |
| failure | Delegates to input_view.cpp; malformed rows can fail on scalar access, and validators construct allocating diagnostics on rejection; no catch/translation here. |
| cost | Classification is O(fields) plus inline decimal checks. Validation scans payload/source bytes and bounded decimal rendering; no new owned row on success. |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
void validate(const InputEventView&,const Catalog&,const InputLimits&,RowIssue);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the event envelope and retained row issue against Catalog. |
| inputs / outputs | Accepts the input view, schema, explicit InputLimits and its matching RowIssue; returns void or a contextual Error. |
| invariants | Catalog backing must remain stable; internal RowIssue is descriptive state, not a public proof factory. Sequence continuity and offset monotonicity are checked by the source owner. |
| ownership | Catalog and explicit row/source views are borrowed; copying a tuple-derived TupleValuesView can retain its existing payload without cloning it. |
| failure | Delegates to input_view.cpp; malformed rows can fail on scalar access, and validators construct allocating diagnostics on rejection; no catch/translation here. |
| cost | Classification is O(fields) plus inline decimal checks. Validation scans payload/source bytes and bounded decimal rendering; no new owned row on success. |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
void validate(const InputEventView&,const program::Catalog&,const InputLimits&,RowIssue);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the event envelope and retained row issue against program::Catalog. |
| inputs / outputs | Accepts the input view, schema, explicit InputLimits and its matching RowIssue; returns void or a contextual Error. |
| invariants | Catalog backing must remain stable; internal RowIssue is descriptive state, not a public proof factory. Sequence continuity and offset monotonicity are checked by the source owner. |
| ownership | Catalog and explicit row/source views are borrowed; copying a tuple-derived TupleValuesView can retain its existing payload without cloning it. |
| failure | Delegates to input_view.cpp; malformed rows can fail on scalar access, and validators construct allocating diagnostics on rejection; no catch/translation here. |
| cost | Classification is O(fields) plus inline decimal checks. Validation scans payload/source bytes and bounded decimal rendering; no new owned row on success. |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
void validate(const WindowCommandView&,const Catalog&,const InputLimits&,RowIssue);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the window envelope and retained row issue against Catalog. |
| inputs / outputs | Accepts the input view, schema, explicit InputLimits and its matching RowIssue; returns void or a contextual Error. |
| invariants | Catalog backing must remain stable; internal RowIssue is descriptive state, not a public proof factory. Sequence continuity and offset monotonicity are checked by the source owner. |
| ownership | Catalog and explicit row/source views are borrowed; copying a tuple-derived TupleValuesView can retain its existing payload without cloning it. |
| failure | Delegates to input_view.cpp; malformed rows can fail on scalar access, and validators construct allocating diagnostics on rejection; no catch/translation here. |
| cost | Classification is O(fields) plus inline decimal checks. Validation scans payload/source bytes and bounded decimal rendering; no new owned row on success. |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
void validate(const WindowCommandView&,const program::Catalog&,const InputLimits&,RowIssue);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the window envelope and retained row issue against program::Catalog. |
| inputs / outputs | Accepts the input view, schema, explicit InputLimits and its matching RowIssue; returns void or a contextual Error. |
| invariants | Catalog backing must remain stable; internal RowIssue is descriptive state, not a public proof factory. Sequence continuity and offset monotonicity are checked by the source owner. |
| ownership | Catalog and explicit row/source views are borrowed; copying a tuple-derived TupleValuesView can retain its existing payload without cloning it. |
| failure | Delegates to input_view.cpp; malformed rows can fail on scalar access, and validators construct allocating diagnostics on rejection; no catch/translation here. |
| cost | Classification is O(fields) plus inline decimal checks. Validation scans payload/source bytes and bounded decimal rendering; no new owned row on success. |
| Design | [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |
