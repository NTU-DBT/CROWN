# `include/crown/frontend/sql_rows.hpp` — block usage map

[Source](../../../../../../include/crown/frontend/sql_rows.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics.

Snapshot SHA-256: `3f3e0cc99d6e4b42b8c9a455e4233e192aad75435adcb0b3bced25f9016626b6`. 138 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../../sql_support.md), [docs/sql_parser.md](../../../../../sql_parser.md), [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_admission.md](../../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../../include/crown/frontend/sql_rows.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // These spans borrow a factory-owned immutable program. NULL belongs to this · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../../include/crown/frontend/sql_rows.hpp#L16) | Type/record definition: struct SqlRowsColumn | source comment (unverified): // These spans borrow a factory-owned immutable program. NULL belongs to this · [reviewed contract](#b0002) |
| [B0003 · 17–24](../../../../../../include/crown/frontend/sql_rows.hpp#L17) | Type/record definition: struct SqlRowsSource |  · [reviewed contract](#b0003) |
| [B0004 · 25–34](../../../../../../include/crown/frontend/sql_rows.hpp#L25) | Type/record definition: struct SqlRowsConstraint | source comment (unverified): // A missing parent denotes UNIQUE with NULLS DISTINCT. Foreign columns are · [reviewed contract](#b0004) |
| [B0005 · 35–35](../../../../../../include/crown/frontend/sql_rows.hpp#L35) | Type/record definition: struct SqlRowsInput |  · [reviewed contract](#b0005) |
| [B0006 · 36–40](../../../../../../include/crown/frontend/sql_rows.hpp#L36) | Type/record definition: struct SqlRowsOperation |  · [reviewed contract](#b0006) |
| [B0007 · 41–41](../../../../../../include/crown/frontend/sql_rows.hpp#L41) | Type/record definition: struct SqlRowsEquality |  · [reviewed contract](#b0007) |
| [B0008 · 42–43](../../../../../../include/crown/frontend/sql_rows.hpp#L42) | Explanatory comments or spacing. | source comment (unverified): // The constant slot can contain SQL NULL for an IS NULL guard. Ordinary · [reviewed contract](#b0008) |
| [B0009 · 44–44](../../../../../../include/crown/frontend/sql_rows.hpp#L44) | Type/record definition: struct SqlRowsConstant | source comment (unverified): // The constant slot can contain SQL NULL for an IS NULL guard. Ordinary · [reviewed contract](#b0009) |
| [B0010 · 45–45](../../../../../../include/crown/frontend/sql_rows.hpp#L45) | Type/record definition: enum class SqlRowsFieldKind |  · [reviewed contract](#b0010) |
| [B0011 · 46–51](../../../../../../include/crown/frontend/sql_rows.hpp#L46) | Type/record definition: struct SqlRowsProjection |  · [reviewed contract](#b0011) |
| [B0012 · 52–63](../../../../../../include/crown/frontend/sql_rows.hpp#L52) | Type/record definition: struct SqlRowsOccurrence | source comment (unverified): // Ascending variable IDs: the actual native node scope/input order. · [reviewed contract](#b0012) |
| [B0013 · 64–67](../../../../../../include/crown/frontend/sql_rows.hpp#L64) | Type/record definition: struct SqlRowsResultField |  · [reviewed contract](#b0013) |
| [B0014 · 68–68](../../../../../../include/crown/frontend/sql_rows.hpp#L68) | Type/record definition: struct SqlRowsExistsOutput |  · [reviewed contract](#b0014) |
| [B0015 · 69–74](../../../../../../include/crown/frontend/sql_rows.hpp#L69) | Type/record definition: struct SqlRowsOutput | source comment (unverified): // ExpressionId selects a constant initial slot, including NULL. · [reviewed contract](#b0015) |
| [B0016 · 75–75](../../../../../../include/crown/frontend/sql_rows.hpp#L75) | Type/record definition: struct SqlRowsCore |  · [reviewed contract](#b0016) |
| [B0017 · 76–84](../../../../../../include/crown/frontend/sql_rows.hpp#L76) | Type/record definition: struct SqlRowsBindOptions | source comment (unverified): // Recovery opts into an additional accounted copy of the canonical binding. · [reviewed contract](#b0017) |
| [B0018 · 85–92](../../../../../../include/crown/frontend/sql_rows.hpp#L85) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // A separate SQL family preserves frozen normalization v1/v2 meanings. Source · [reviewed contract](#b0018) |
| [B0019 · 93–93](../../../../../../include/crown/frontend/sql_rows.hpp#L93) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns bool(data_) · [reviewed contract](#b0019) |
| [B0020 · 94–124](../../../../../../include/crown/frontend/sql_rows.hpp#L94) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Empty unless binding opted into retention. Otherwise exact genuine · [reviewed contract](#b0020) |
| [B0021 · 125–125](../../../../../../include/crown/frontend/sql_rows.hpp#L125) | Callable definition: explicit SqlRowsProgram(std::shared_ptr&lt;const Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0021) |
| [B0022 · 126–138](../../../../../../include/crown/frontend/sql_rows.hpp#L126) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Parsing/binding workspace is cold caller/compiler work. Retained metadata · [reviewed contract](#b0022) |

## B0001

[Lines 1–15](../../../../../../include/crown/frontend/sql_rows.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:9603b2998db2b8ebdd17cf6f09f05ab739843e59fde57482468b7afa045b928c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe nullable physical sources. |
| inputs / outputs | SqlRowCell is optional ScalarView; source descriptors expose complete schema, constraint indices and affected occurrences. |
| invariants | SQL NULL is disengaged; engaged false/zero/empty text remain values. Sources include unused catalog tables. |
| ownership | All names and spans borrow a live immutable program; scalar strings also borrow. |
| failure | No validation or allocation occurs in descriptors. |
| cost | Constant-size descriptor copies; iteration is proportional to exposed metadata. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/frontend/bind.hpp §L9-15](../../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/frontend/bind.hpp), [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/ir/model.hpp §L27-68](../../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/ir/model.hpp), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md) |

## B0002

[Lines 16–16](../../../../../../include/crown/frontend/sql_rows.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L16:sha256:fba48a81073fdd4a2072e742e3a5b5eb3b5f6fcd7446ef9bb790ef045abe4dca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one physical column declaration. |
| inputs / outputs | Borrowed name and exact SqlType out. |
| invariants | Physical integer columns are bigint; nullable flags and decimal typmods describe validation. |
| ownership | Names/spans borrow the live immutable program; copying a descriptor does not extend that lifetime. |
| failure | Descriptors perform no checks or allocation; only factory-produced program metadata is runtime authority. |
| cost | Fixed-size descriptor copies; traversals cost the exposed span lengths. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0003

[Lines 17–24](../../../../../../include/crown/frontend/sql_rows.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L24:sha256:a9501fdb642a451ff59a8ca81ec9d324ade758814730864d21d1bae4898fd27b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a complete physical source port. |
| inputs / outputs | Table ID, schema version, columns, constraint IDs and occurrence routes. |
| invariants | All catalog tables remain available, including unused sources; routes contain original occurrence IDs. |
| ownership | Names/spans borrow the live immutable program; copying a descriptor does not extend that lifetime. |
| failure | Descriptors perform no checks or allocation; only factory-produced program metadata is runtime authority. |
| cost | Fixed-size descriptor copies; traversals cost the exposed span lengths. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0004

[Lines 25–34](../../../../../../include/crown/frontend/sql_rows.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L34:sha256:70ac103000fb4f8cd674f2e3ae51c16597d38f69a5307ae0079d78b6ead48078
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe enforced source keys and their dependency graph. |
| inputs / outputs | A UNIQUE has no parent; FK columns are ordered to match its UNIQUE parent; referenced_by contains child constraint indices. |
| invariants | Runtime fixes NULLS DISTINCT and MATCH SIMPLE; empty keys preserve at-most-one/target-nonempty catalog semantics. Column ordering aligns FK projections with their parent. |
| ownership | Spans and names belong to program backing arrays. |
| failure | Descriptors alone do not enforce source data. |
| cost | Traversal proportional to key width/reference count. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp §L18-24,89-110](../../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp), [build/verification/w05-sql-rows-human-review-v1/sources/docs/catalog.md §L106-125](../../../../../../build/verification/w05-sql-rows-human-review-v1/sources/docs/catalog.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md) |

## B0005

[Lines 35–35](../../../../../../include/crown/frontend/sql_rows.hpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L35:sha256:9f029b47b3f14412a911e79093e2260dc25f9d20d73bfef9cb95de9bf90f0c0e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose resolved local adapter instructions. |
| inputs / outputs | Input reads, topological opcodes, guards, predicates and sorted projections describe one occurrence. |
| invariants | Dynamic targets exclude known constants; equal-column guards reject NULL; fixed NULL means IS NULL; projection order is ascending VariableId. |
| ownership | Borrowed immutable spans; arguments are program-owned. |
| failure | Only factory-generated descriptors are executable. |
| cost | Runtime work proportional to listed guards/reads/operations/projections and scalar payload comparison. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp §L33-86](../../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp), [build/verification/w05-sql-rows-human-review-v1/README.md §encoding/borrow argument](../../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md) |

## B0006

[Lines 36–40](../../../../../../include/crown/frontend/sql_rows.hpp#L36); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L40:sha256:435a5325c57ed38da257fc521b71124b6af4060ac562cae7b4740ce20deac812
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one resolved local scalar operation. |
| inputs / outputs | Target slot, opcode and argument IDs. |
| invariants | The factory publishes checked topological operations; constants are not dynamic targets. |
| ownership | Names/spans borrow the live immutable program; copying a descriptor does not extend that lifetime. |
| failure | Descriptors perform no checks or allocation; only factory-produced program metadata is runtime authority. |
| cost | Fixed-size descriptor copies; traversals cost the exposed span lengths. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0007

[Lines 41–41](../../../../../../include/crown/frontend/sql_rows.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L41:sha256:c47b8a743287e080bf43fd122454bab7ce850c4197527a2220b4f322084e3120
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record an ordinary local SQL equality guard. |
| inputs / outputs | Two physical column IDs. |
| invariants | Runtime requires both operands present before equality; two NULLs do not join. |
| ownership | Names/spans borrow the live immutable program; copying a descriptor does not extend that lifetime. |
| failure | Descriptors perform no checks or allocation; only factory-produced program metadata is runtime authority. |
| cost | Fixed-size descriptor copies; traversals cost the exposed span lengths. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0008

[Lines 42–43](../../../../../../include/crown/frontend/sql_rows.hpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L43:sha256:39a98d2819a6b2d8c90f20f83c5c70533dc0b382f473fbe7f019b0105df4cb1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: The constant slot can contain SQL NULL for an IS NULL guard. Ordinary equality with NULL is compiled as contradiction, never as matching NULLs. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/frontend/sql_rows.hpp lines 40-45; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [docs/code_specs/files/include/crown/frontend/sql_rows.hpp.md](sql_rows.hpp.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

## B0009

[Lines 44–44](../../../../../../include/crown/frontend/sql_rows.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:0212c417e8a63ed5e76328b90bda08ae98b9ea449519f77dc099df64be1aab2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record a physical-column grounding guard. |
| inputs / outputs | Physical column and program constant slot ID. |
| invariants | A NULL constant means IS NULL, while ordinary equality to NULL is a contradiction. |
| ownership | Names/spans borrow the live immutable program; copying a descriptor does not extend that lifetime. |
| failure | Descriptors perform no checks or allocation; only factory-produced program metadata is runtime authority. |
| cost | Fixed-size descriptor copies; traversals cost the exposed span lengths. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0010

[Lines 45–45](../../../../../../include/crown/frontend/sql_rows.hpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L45:sha256:90bfdc5af7df7d390b66966fd964485dfde5214473561a4ec3fb298645b30644
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish payload and presence writes. |
| inputs / outputs | value, nullable_payload or presence. |
| invariants | Only nullable_payload may substitute a canonical zero for a missing expression. |
| ownership | Names/spans borrow the live immutable program; copying a descriptor does not extend that lifetime. |
| failure | Descriptors perform no checks or allocation; only factory-produced program metadata is runtime authority. |
| cost | Fixed-size descriptor copies; traversals cost the exposed span lengths. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0011

[Lines 46–51](../../../../../../include/crown/frontend/sql_rows.hpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L51:sha256:c604a149fb7e9daa9fae2a8f065393943a08893401039a6064310372f74027c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one native field emitted by an adapter. |
| inputs / outputs | Variable ID, expression, core scalar type and field kind. |
| invariants | Published projections are sorted by ascending variable ID, matching actual native scope order. |
| ownership | Names/spans borrow the live immutable program; copying a descriptor does not extend that lifetime. |
| failure | Descriptors perform no checks or allocation; only factory-produced program metadata is runtime authority. |
| cost | Fixed-size descriptor copies; traversals cost the exposed span lengths. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0012

[Lines 52–63](../../../../../../include/crown/frontend/sql_rows.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L63:sha256:efd0cbe31c95e33d3a572886f796c156bccdd4375b900c099e44e0e0fc77d4bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one alias-local adapter program. |
| inputs / outputs | Source/occurrence IDs and immutable instruction/guard/projection spans. |
| invariants | Each alias has its own guards and needed slot closure; SQL equality classes may share native variables. |
| ownership | Names/spans borrow the live immutable program; copying a descriptor does not extend that lifetime. |
| failure | Descriptors perform no checks or allocation; only factory-produced program metadata is runtime authority. |
| cost | Fixed-size descriptor copies; traversals cost the exposed span lengths. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0013

[Lines 64–67](../../../../../../include/crown/frontend/sql_rows.hpp#L64); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L67:sha256:1562db288566fdc39ce49978af03bb93573340847da454366c259f0b946fe03f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a selected value from the core head. |
| inputs / outputs | Payload position and optional presence position. |
| invariants | Present values use their payload; missing values decode to NULL independently of sentinel payload. |
| ownership | Names/spans borrow the live immutable program; copying a descriptor does not extend that lifetime. |
| failure | Descriptors perform no checks or allocation; only factory-produced program metadata is runtime authority. |
| cost | Fixed-size descriptor copies; traversals cost the exposed span lengths. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0014

[Lines 68–68](../../../../../../include/crown/frontend/sql_rows.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L68:sha256:b27f838902600f6ebd866a28ba2ba682f2ff737086e7f7c6d081e3d83f6bdf70
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark an EXISTS decoder without inventing a constant slot. |
| inputs / outputs | Empty marker alternative. |
| invariants | EXISTS samples root presence; an empty inner expression array remains valid. |
| ownership | Names/spans borrow the live immutable program; copying a descriptor does not extend that lifetime. |
| failure | Descriptors perform no checks or allocation; only factory-produced program metadata is runtime authority. |
| cost | Fixed-size descriptor copies; traversals cost the exposed span lengths. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0015

[Lines 69–74](../../../../../../include/crown/frontend/sql_rows.hpp#L69); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L74:sha256:d03a0fa726bb9fa90d67417b5564835c1d9205a4c4852c4654b19bf53afb4fa9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe ordered SQL output decoding and cold core export. |
| inputs / outputs | Each output selects head payload/presence, a constant slot, or EXISTS. |
| invariants | Presence and payload index the query head, not occurrence projection order; repeated outputs may reuse indices. |
| ownership | Output names borrow program; exported Catalog/Query own ordinary DTO storage. |
| failure | Decoder must honor contradiction and wrapper behavior externally. |
| cost | One descriptor per SELECT output; core export is cold allocation work. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/build/verification/w05-start-v1/design-notes-v1.md §L43-71](../../../../../../build/verification/w05-sql-rows-human-review-v1/sources/build/verification/w05-start-v1/design-notes-v1.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md) |

## B0016

[Lines 75–75](../../../../../../include/crown/frontend/sql_rows.hpp#L75); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L75:sha256:31bb4009d8212dce66bd470d75d6aae37d8e3a5dab399df7132794307b6eb436
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export mutable planner input explicitly. |
| inputs / outputs | Ordinary Catalog and Query values. |
| invariants | An exported DTO is not a runtime admission token; runtime exports again from the immutable program. |
| ownership | Caller owns ordinary DTO allocations; this is a cold boundary. |
| failure | Export/validation may throw before any runtime exists. |
| cost | Linear metadata copying plus catalog/query validation and ordinary allocator costs. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0017

[Lines 76–84](../../../../../../include/crown/frontend/sql_rows.hpp#L76); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L84:sha256:f45289035ac6454d65cb98a46eac8cf2ded4d8550c19417ef4a7a4f68892df3c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare cold binding configuration with explicit optional immutable binding-image retention. |
| inputs / outputs | Members are BindOptions binding, owning nullable Value parameters, work_limit=1000000, memory_limit_bytes=16MiB and trailing retain_binding_image=false. |
| invariants | The DTO itself does not bind or validate. Retention flag controls only an additional stored canonical image, never source SHA or selected compiler work. |
| ownership | Ordinary parameter/vector values own caller data through binding; actual immutable program metadata is separately retained by its factory. |
| failure | Member construction/copy allocation rules apply; no custom validation/handler in this type. |
| cost | Fixed limits/flag plus ordinary parameter-vector construction/copy; no compile/hash/image copy is executed merely by declaration. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows.cpp §L422-454](../../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows.cpp), [build/verification/w05-sql-rows-human-review-v1/README.md §F2 and cost item 2](../../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md) |

## B0018

[Lines 85–92](../../../../../../include/crown/frontend/sql_rows.hpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L92:sha256:551fd942e11af30543a1a19a4361b9445412862df16283c4233f36bb240fa66f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own and inspect an immutable SQL rows program. |
| inputs / outputs | Default handle is empty; freeze shares same account or clones into another; lvalue accessors borrow immutable metadata. |
| invariants | Factory-only Data prevents mutable DTOs becoming executable authority. Runtime must re-export from actual program. |
| ownership | Shared handle extends lifetime; naked spans do not. Rvalue borrowed accessors are deleted. |
| failure | Empty handle access and invalid receiving account fail. Allocation can fail on cross-account clone/export. |
| cost | Handle copies O(1); clone/export proportional to retained metadata/payload. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/resource/ownership.hpp](../../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/resource/ownership.hpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows.cpp §L460-534](../../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows.cpp), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md) |

## B0019

[Lines 93–93](../../../../../../include/crown/frontend/sql_rows.hpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L93:sha256:97dc45bb9885bdd0388f6f214da7c7b65592f7223005ba157410f3c56773a027
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether the program owns metadata. |
| inputs / outputs | Program handle to Boolean. |
| invariants | An empty handle is false; this does not inspect tree validity. |
| ownership | Reads shared ownership without changing it. |
| failure | Noexcept; empty handles do not throw here. |
| cost | Constant work, no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0020

[Lines 94–124](../../../../../../include/crown/frontend/sql_rows.hpp#L94); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L124:sha256:e493be658b25104ee9ff1c9fe4f07c1852d7034aa619f8dd982903d848d50425
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare immutable program metadata borrows, exact binding-image access and cold core export. |
| inputs / outputs | Declare freeze/account/source/binding_image/source_sha256, semantics/wrapper/contradiction/work, source/constraint/occurrence/output/initial spans and export_core. |
| invariants | Borrowed accessors delete const-rvalue overloads. The signatures do not bind, freeze, copy or hash; corresponding bodies establish those behaviors. |
| ownership | Const-lvalue views/references borrow immutable Data; explicit freeze/export may return owning handles/DTOs in their implementations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/frontend/sql_rows.hpp §SqlRowsProgram declaration group](../../../../../../include/crown/frontend/sql_rows.hpp), [src/frontend/sql_rows.cpp §accessors, freeze, and export_core](../../../../../../src/frontend/sql_rows.cpp), [docs/sql_rows_runtime.md §program lifetime and freeze](../../../../../sql_rows_runtime.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../../Refactor.md) |

## B0021

[Lines 125–125](../../../../../../include/crown/frontend/sql_rows.hpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L125:sha256:63a4447d1c2b36d42ac5fc51847918eea3ca9ae4ca4fc081904f5d46d532ed73
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt factory-created immutable ownership. |
| inputs / outputs | Private shared Data handle to program. |
| invariants | Only the compiler/freeze paths can invoke this ownership constructor. |
| ownership | Moves the shared handle; no deep copy. |
| failure | Noexcept. |
| cost | Constant handle transfer, no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0022

[Lines 126–138](../../../../../../include/crown/frontend/sql_rows.hpp#L126); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L126-L138:sha256:bcefdf8d5609aa395e87323dcf11a865da5d531fbdaa6f37402df5b5445a092f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind SQL into the owned program or a diagnostic. |
| inputs / outputs | Convenience binding creates the stated cap; _into requires an existing account. |
| invariants | Corrected comment: compiler allocation/account failures propagate; bind_sql keeps its own exception/diagnostic rules. |
| ownership | Parsing/binding workspace remains cold standard storage; retained data uses account. |
| failure | Compiler allocation/account failures propagate. Parsing/binding retain bind_sql existing exception/diagnostic boundaries, including Binder resource-limit translation. |
| cost | Cold binding plus normalization/freeze/export; no update-time parser. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp §L550-567](../../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp), [build/verification/w05-sql-rows-human-review-v1/README.md §F2](../../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md) |
