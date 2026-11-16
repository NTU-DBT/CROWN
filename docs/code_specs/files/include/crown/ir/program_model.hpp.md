# `include/crown/ir/program_model.hpp` — block usage map

[Source](../../../../../../include/crown/ir/program_model.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Define account-funded native equivalents of compiler metadata.

Snapshot SHA-256: `77861229bc601a06c676423f0ce15bffdc7ba988c37036a54d0a4c75438f7899`. 302 lines partitioned into 54 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../../include/crown/ir/program_model.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Read-only views over immutable native program storage. All text, spans, and · [reviewed contract](#b0001) |
| [B0002 · 20–26](../../../../../../include/crown/ir/program_model.hpp#L20) | Type/record definition: struct Column |  · [reviewed contract](#b0002) |
| [B0003 · 27–27](../../../../../../include/crown/ir/program_model.hpp#L27) | Explanatory comments or spacing. |  |
| [B0004 · 28–32](../../../../../../include/crown/ir/program_model.hpp#L28) | Type/record definition: struct UniqueConstraint |  · [reviewed contract](#b0004) |
| [B0005 · 33–39](../../../../../../include/crown/ir/program_model.hpp#L33) | Type/record definition: struct ForeignKeyConstraint |  · [reviewed contract](#b0005) |
| [B0006 · 40–41](../../../../../../include/crown/ir/program_model.hpp#L40) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 42–45](../../../../../../include/crown/ir/program_model.hpp#L42) | Type/record definition: struct DistinctEstimate |  · [reviewed contract](#b0007) |
| [B0008 · 46–49](../../../../../../include/crown/ir/program_model.hpp#L46) | Type/record definition: struct TableStatistics |  · [reviewed contract](#b0008) |
| [B0009 · 50–53](../../../../../../include/crown/ir/program_model.hpp#L50) | Type/record definition: struct KeyHint |  · [reviewed contract](#b0009) |
| [B0010 · 54–61](../../../../../../include/crown/ir/program_model.hpp#L54) | Type/record definition: struct Table |  · [reviewed contract](#b0010) |
| [B0011 · 62–65](../../../../../../include/crown/ir/program_model.hpp#L62) | Type/record definition: struct Catalog |  · [reviewed contract](#b0011) |
| [B0012 · 66–66](../../../../../../include/crown/ir/program_model.hpp#L66) | Explanatory comments or spacing. |  |
| [B0013 · 67–70](../../../../../../include/crown/ir/program_model.hpp#L67) | Type/record definition: struct Variable |  · [reviewed contract](#b0013) |
| [B0014 · 71–71](../../../../../../include/crown/ir/program_model.hpp#L71) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0014) |
| [B0015 · 72–76](../../../../../../include/crown/ir/program_model.hpp#L72) | Type/record definition: struct Atom |  · [reviewed contract](#b0015) |
| [B0016 · 77–80](../../../../../../include/crown/ir/program_model.hpp#L77) | Type/record definition: struct Output |  · [reviewed contract](#b0016) |
| [B0017 · 81–86](../../../../../../include/crown/ir/program_model.hpp#L81) | Type/record definition: struct Query |  · [reviewed contract](#b0017) |
| [B0018 · 87–87](../../../../../../include/crown/ir/program_model.hpp#L87) | Explanatory comments or spacing. |  |
| [B0019 · 88–95](../../../../../../include/crown/ir/program_model.hpp#L88) | Type/record definition: struct TreeNode |  · [reviewed contract](#b0019) |
| [B0020 · 96–101](../../../../../../include/crown/ir/program_model.hpp#L96) | Type/record definition: struct FreeConnexTree |  · [reviewed contract](#b0020) |
| [B0021 · 102–102](../../../../../../include/crown/ir/program_model.hpp#L102) | Explanatory comments or spacing. |  |
| [B0022 · 103–110](../../../../../../include/crown/ir/program_model.hpp#L103) | Type/record definition: struct PlanViolation |  · [reviewed contract](#b0022) |
| [B0023 · 111–118](../../../../../../include/crown/ir/program_model.hpp#L111) | Type/record definition: struct ValidationReport |  · [reviewed contract](#b0023) |
| [B0024 · 119–119](../../../../../../include/crown/ir/program_model.hpp#L119) | Explanatory comments or spacing. |  |
| [B0025 · 120–120](../../../../../../include/crown/ir/program_model.hpp#L120) | Type/record definition: struct BoundLiteral |  · [reviewed contract](#b0025) |
| [B0026 · 121–122](../../../../../../include/crown/ir/program_model.hpp#L121) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0026) |
| [B0027 · 123–126](../../../../../../include/crown/ir/program_model.hpp#L123) | Type/record definition: struct BoundOperation |  · [reviewed contract](#b0027) |
| [B0028 · 127–127](../../../../../../include/crown/ir/program_model.hpp#L127) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0028) |
| [B0029 · 128–132](../../../../../../include/crown/ir/program_model.hpp#L128) | Type/record definition: struct BoundExpression |  · [reviewed contract](#b0029) |
| [B0030 · 133–139](../../../../../../include/crown/ir/program_model.hpp#L133) | Type/record definition: struct BoundOccurrence |  · [reviewed contract](#b0030) |
| [B0031 · 140–143](../../../../../../include/crown/ir/program_model.hpp#L140) | Type/record definition: struct BoundOutput |  · [reviewed contract](#b0031) |
| [B0032 · 144–158](../../../../../../include/crown/ir/program_model.hpp#L144) | Type/record definition: struct BoundSql |  · [reviewed contract](#b0032) |
| [B0033 · 159–160](../../../../../../include/crown/ir/program_model.hpp#L159) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0033) |
| [B0034 · 161–164](../../../../../../include/crown/ir/program_model.hpp#L161) | Type/record definition: struct ColumnConstant |  · [reviewed contract](#b0034) |
| [B0035 · 165–175](../../../../../../include/crown/ir/program_model.hpp#L165) | Type/record definition: struct OccurrenceAdapter |  · [reviewed contract](#b0035) |
| [B0036 · 176–176](../../../../../../include/crown/ir/program_model.hpp#L176) | Type/record definition: struct ConstantOutput |  · [reviewed contract](#b0036) |
| [B0037 · 177–181](../../../../../../include/crown/ir/program_model.hpp#L177) | Type/record definition: struct NormalizedOutput |  · [reviewed contract](#b0037) |
| [B0038 · 182–194](../../../../../../include/crown/ir/program_model.hpp#L182) | Type/record definition: struct NormalizedSql |  · [reviewed contract](#b0038) |
| [B0039 · 195–195](../../../../../../include/crown/ir/program_model.hpp#L195) | Explanatory comments or spacing. |  |
| [B0040 · 196–201](../../../../../../include/crown/ir/program_model.hpp#L196) | Type/record definition: struct CachePolicy |  · [reviewed contract](#b0040) |
| [B0041 · 202–206](../../../../../../include/crown/ir/program_model.hpp#L202) | Type/record definition: struct PhysicalOptions |  · [reviewed contract](#b0041) |
| [B0042 · 207–223](../../../../../../include/crown/ir/program_model.hpp#L207) | Type/record definition: struct GuaranteeProfile |  · [reviewed contract](#b0042) |
| [B0043 · 224–233](../../../../../../include/crown/ir/program_model.hpp#L224) | Type/record definition: struct QueryIdentity |  · [reviewed contract](#b0043) |
| [B0044 · 234–234](../../../../../../include/crown/ir/program_model.hpp#L234) | Explanatory comments or spacing. |  |
| [B0045 · 235–241](../../../../../../include/crown/ir/program_model.hpp#L235) | Type/record definition: struct PhysicalRelation |  · [reviewed contract](#b0045) |
| [B0046 · 242–242](../../../../../../include/crown/ir/program_model.hpp#L242) | Type/record definition: struct SourceTable |  · [reviewed contract](#b0046) |
| [B0047 · 243–248](../../../../../../include/crown/ir/program_model.hpp#L243) | Type/record definition: struct IndexRequirement |  · [reviewed contract](#b0047) |
| [B0048 · 249–252](../../../../../../include/crown/ir/program_model.hpp#L249) | Type/record definition: struct InputConstant |  · [reviewed contract](#b0048) |
| [B0049 · 253–262](../../../../../../include/crown/ir/program_model.hpp#L253) | Type/record definition: struct PhysicalInput |  · [reviewed contract](#b0049) |
| [B0050 · 263–279](../../../../../../include/crown/ir/program_model.hpp#L263) | Type/record definition: struct PhysicalNode |  · [reviewed contract](#b0050) |
| [B0051 · 280–286](../../../../../../include/crown/ir/program_model.hpp#L280) | Type/record definition: struct PhysicalEdge |  · [reviewed contract](#b0051) |
| [B0052 · 287–294](../../../../../../include/crown/ir/program_model.hpp#L287) | Type/record definition: struct EnumerationStep |  · [reviewed contract](#b0052) |
| [B0053 · 295–300](../../../../../../include/crown/ir/program_model.hpp#L295) | Type/record definition: struct EnumerationProgram |  · [reviewed contract](#b0053) |
| [B0054 · 301–302](../../../../../../include/crown/ir/program_model.hpp#L301) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::program · [reviewed contract](#b0054) |

## B0001

[Lines 1–19](../../../../../../include/crown/ir/program_model.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:fea2c7778a67569cdb4643948f083058573842c2e08731ae890b04968b9d8723
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Header guard and borrowed-view, accounted layout/projection, and physical-plan dependencies; opens crown::program for immutable native program view declarations. Embedded source note records intended usage: Read-only views over immutable native program storage. All text, spans, and nested views borrow storage owned elsewhere. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The header guard prevents repeat inclusion in a translation unit; imported declarations determine compile-time names. The note/type comments in this span are guidance and do not add runtime validation or a capability. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path is introduced by the guard/imports; incompatible or missing declarations fail during compilation or linking. |
| cost | Preprocessor/compiler work only for these lines; the guard adds no per-operation runtime work. |
| Design | [include/crown/ir/program_model.hpp](../../../../../../include/crown/ir/program_model.hpp), [docs/code_specs/files/include/crown/ir/program_model.hpp.md](program_model.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0002

[Lines 20–26](../../../../../../include/crown/ir/program_model.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Column {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one borrowed catalog column. |
| inputs / outputs | Carries name, scalar type, nullability, collation and optional decimal spec. |
| invariants | Mirrors Column metadata; catalog validation, rather than this view, checks schema policy. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L20-26](../../../../../../include/crown/ir/program_model.hpp), [src/catalog/catalog.cpp §L52-70](../../../../../../src/catalog/catalog.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0004

[Lines 28–32](../../../../../../include/crown/ir/program_model.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct UniqueConstraint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one borrowed unique declaration. |
| inputs / outputs | Carries name, column-ID span and status. |
| invariants | Default status is untrusted; a view does not certify uniqueness. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L28-32](../../../../../../include/crown/ir/program_model.hpp), [src/catalog/catalog.cpp §L117-135](../../../../../../src/catalog/catalog.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0005

[Lines 33–39](../../../../../../include/crown/ir/program_model.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ForeignKeyConstraint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one borrowed foreign-key declaration. |
| inputs / outputs | Carries child IDs, referenced table/column IDs and status with name. |
| invariants | The declaration records a mapping; catalog and database validators check structural and enforced-reference rules. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L33-39](../../../../../../include/crown/ir/program_model.hpp), [src/catalog/catalog.cpp §L89-109,136-145](../../../../../../src/catalog/catalog.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0006

[Lines 40–41](../../../../../../include/crown/ir/program_model.hpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Constraint = std::variant<UniqueConstraint, ForeignKeyConstraint>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent native catalog constraints as a discriminated read-only view. |
| inputs / outputs | The alias selects \`program::UniqueConstraint\` or \`program::ForeignKeyConstraint\`, whose names and column lists borrow native metadata. |
| invariants | This is distinct from the owning \`crown::Constraint\`; it does not copy or validate constraint records. |
| ownership | \`string_view\` and \`program::Span\` fields borrow immutable \`CompiledProgram\` storage and must not outlive its retained owner. |
| failure | The alias checks no indices or semantics; validation/provenance is established at program creation and consumers must retain the program. |
| cost | The variant and views do not allocate on copy; any traversal/comparison costs belong to the caller. |
| Design | [include/crown/ir/program_model.hpp §constraint views](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/program_span.hpp §borrowed Span](../../../../../../include/crown/ir/program_span.hpp), [include/crown/ir/program.hpp §CompiledProgram lifetime](../../../../../../include/crown/ir/program.hpp) |

## B0007

[Lines 42–45](../../../../../../include/crown/ir/program_model.hpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DistinctEstimate {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose an estimated count for a borrowed column set. |
| inputs / outputs | Pairs ColumnId span and uint64 estimate. |
| invariants | Estimate is advisory metadata, not a certified cardinality. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L42-45](../../../../../../include/crown/ir/program_model.hpp), [src/catalog/catalog.cpp §L79-83](../../../../../../src/catalog/catalog.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0008

[Lines 46–49](../../../../../../include/crown/ir/program_model.hpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TableStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose optional row count and distinct estimates. |
| inputs / outputs | Carries optional count and a span of estimates. |
| invariants | Statistics do not certify database contents. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L46-49](../../../../../../include/crown/ir/program_model.hpp), [src/catalog/catalog.cpp §L79-83](../../../../../../src/catalog/catalog.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0009

[Lines 50–53](../../../../../../include/crown/ir/program_model.hpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct KeyHint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose hinted columns and reason text. |
| inputs / outputs | Carries ColumnId span and string_view reason. |
| invariants | A hint does not establish a key constraint. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L50-53](../../../../../../include/crown/ir/program_model.hpp), [src/catalog/catalog.cpp §L84-87](../../../../../../src/catalog/catalog.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0010

[Lines 54–61](../../../../../../include/crown/ir/program_model.hpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Table {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one borrowed table schema and metadata lists. |
| inputs / outputs | Groups name, columns, source schema version, constraints, statistics and key hints. |
| invariants | Catalog validation owns nested schema consistency checks. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L54-61](../../../../../../include/crown/ir/program_model.hpp), [src/catalog/catalog.cpp §L52-110](../../../../../../src/catalog/catalog.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0011

[Lines 62–65](../../../../../../include/crown/ir/program_model.hpp#L62); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Catalog {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a versioned borrowed table sequence. |
| inputs / outputs | Table positions provide lookup order for TableId references. |
| invariants | This view does not range-check IDs held by other records. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L62-65](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/ids.hpp §L8-10](../../../../../../include/crown/ir/ids.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0013

[Lines 67–70](../../../../../../include/crown/ir/program_model.hpp#L67); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Variable {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one query variable name and scalar tag. |
| inputs / outputs | VariableId refers to its position in the query variable span. |
| invariants | Checked query validation establishes names, bounds and compatible types. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L67-70](../../../../../../include/crown/ir/program_model.hpp), [src/ir/model.cpp §L86-113](../../../../../../src/ir/model.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0014

[Lines 71–71](../../../../../../include/crown/ir/program_model.hpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Term = std::variant<VariableId, storage::ScalarView, ::crown::IgnoredColumn>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent native atom terms with compact scalar views instead of the owning public \`Value\` term. |
| inputs / outputs | The native \`Term\` holds a variable ID, \`storage::ScalarView\`, or ignored-column marker. |
| invariants | It preserves the source alternative but performs no type/index validation and is not an owning replacement for public \`crown::Term\`. |
| ownership | The \`ScalarView\` string alternative borrows bytes from the program arena; int64, bool, date, and \`InlineDecimal\` alternatives are stored inline. References/spans to the containing native term still require the \`CompiledProgram\` owner to remain alive. |
| failure | No failure path exists in the alias; invalid terms are rejected before publication or when separately checked. |
| cost | The variant is fixed-size: copying a string alternative copies only its view, while other scalar alternatives copy inline values. Exporting a borrowed string into an owning DTO can allocate. |
| Design | [include/crown/ir/program_model.hpp §Term alias](../../../../../../include/crown/ir/program_model.hpp), [include/crown/storage/accounted_row.hpp §ScalarView](../../../../../../include/crown/storage/accounted_row.hpp), [include/crown/ir/program.hpp §program owner](../../../../../../include/crown/ir/program.hpp) |

## B0015

[Lines 72–76](../../../../../../include/crown/ir/program_model.hpp#L72); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Atom {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a table occurrence and its borrowed term sequence. |
| inputs / outputs | Carries occurrence, TableId and term span. |
| invariants | Arity/type/ID consistency belongs to checked query validation. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L72-76](../../../../../../include/crown/ir/program_model.hpp), [src/ir/model.cpp §L91-110](../../../../../../src/ir/model.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0016

[Lines 77–80](../../../../../../include/crown/ir/program_model.hpp#L77); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Output {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one selected variable and borrowed output alias. |
| inputs / outputs | Carries VariableId and alias view. |
| invariants | Whether the ID is bound is established by query validation. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L77-80](../../../../../../include/crown/ir/program_model.hpp), [src/ir/model.cpp §L112-113](../../../../../../src/ir/model.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0017

[Lines 81–86](../../../../../../include/crown/ir/program_model.hpp#L81); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Query {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose borrowed core query vectors and contradiction marker. |
| inputs / outputs | Carries spans for variables, atoms and ordered head plus bool marker. |
| invariants | The contradiction flag defines an empty source query when set; it is not a proof that an otherwise unmarked body is contradictory. Enclosing validation checks names/IDs/types/arity and variable bindings. No minimum-height or execution authority follows from the record. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L81-86](../../../../../../include/crown/ir/program_model.hpp), [src/ir/model.cpp §L75-113](../../../../../../src/ir/model.cpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0019

[Lines 88–95](../../../../../../include/crown/ir/program_model.hpp#L88); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TreeNode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a tree node, scope, children and optional claims. |
| inputs / outputs | Carries id/kind, variable Set, child span, optional occurrence and separator claim. |
| invariants | Claims and IDs are checked by tree validation; Set find/contains use lower_bound and need ordered backing. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L88-95](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/program_span.hpp §L9-43](../../../../../../include/crown/ir/program_span.hpp), [include/crown/planner/verify.hpp](../../../../../../include/crown/planner/verify.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0020

[Lines 96–101](../../../../../../include/crown/ir/program_model.hpp#L96); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FreeConnexTree {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose root, nodes and optional connex/height claims. |
| inputs / outputs | Carries optional root ID, node span, optional claimed connex nodes and native height. |
| invariants | Claim fields are metadata; checked tree verification establishes validity and interpretation. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L96-101](../../../../../../include/crown/ir/program_model.hpp), [include/crown/planner/verify.hpp](../../../../../../include/crown/planner/verify.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0022

[Lines 103–110](../../../../../../include/crown/ir/program_model.hpp#L103); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PlanViolation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one rule/message diagnostic and optional affected IDs. |
| inputs / outputs | Carries borrowed rule/message and node/variable/occurrence/related-node positions. |
| invariants | A violation record is diagnostic data, not an independent validation result. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L103-110](../../../../../../include/crown/ir/program_model.hpp), [include/crown/planner/verify.hpp](../../../../../../include/crown/planner/verify.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0023

[Lines 111–118](../../../../../../include/crown/ir/program_model.hpp#L111); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ValidationReport {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the tree validator outcome and detail spans. |
| inputs / outputs | Carries valid flag, optional heights, maximal connex nodes, separators and violations. |
| invariants | The fields report validator output; the record does not run or repeat verification. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L111-118](../../../../../../include/crown/ir/program_model.hpp), [include/crown/planner/verify.hpp](../../../../../../include/crown/planner/verify.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0025

[Lines 120–120](../../../../../../include/crown/ir/program_model.hpp#L120); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundLiteral { std::optional<storage::ScalarView> value; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose an optional SQL scalar literal. |
| inputs / outputs | Engaged ScalarView carries a value; disengaged optional represents SQL NULL at the SQL boundary. |
| invariants | NULL remains outside crown::Value; binding owns resolution/type checks. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L120-120](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/bind.hpp §L17-18](../../../../../../include/crown/frontend/bind.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0026

[Lines 121–122](../../../../../../include/crown/ir/program_model.hpp#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using BoundColumn=frontend::BoundColumn;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse frontend bound-column and bound-parameter types inside the immutable native bound view. |
| inputs / outputs | \`program::BoundColumn\` and \`program::BoundParameter\` are exact aliases to frontend value types: a column occurrence/column ID pair and a one-based parameter number. |
| invariants | The aliases do not create independent identities or copy a bound program’s surrounding strings/spans; the containing native structures are read-only views. |
| ownership | \`BoundColumn\` stores two typed IDs and \`BoundParameter\` stores one size value; copies retain no owner. Any expression arrays, aliases, or scalar storage are separate fields in the containing compiled-program view. |
| failure | The aliases do not validate occurrence/column/parameter ranges; trusted compiler construction and later checked consumers establish validity. |
| cost | The aliases add no wrapper conversion or dynamic allocation; copying stores the small ID/number fields. Traversal of separate containing expression arrays is caller work. |
| Design | [include/crown/ir/program_model.hpp §bound aliases](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/bind.hpp §source types](../../../../../../include/crown/frontend/bind.hpp), [include/crown/ir/program.hpp §immutable owner](../../../../../../include/crown/ir/program.hpp) |

## B0027

[Lines 123–126](../../../../../../include/crown/ir/program_model.hpp#L123); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundOperation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a SQL operator and expression argument IDs. |
| inputs / outputs | Carries SqlOperator and argument span. |
| invariants | Operator arity and type rules belong to the binder. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L123-126](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/bind.hpp §L20-27](../../../../../../include/crown/frontend/bind.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0028

[Lines 127–127](../../../../../../include/crown/ir/program_model.hpp#L127); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using BoundNode = std::variant<BoundColumn, BoundLiteral, BoundParameter, BoundOperation>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tag each expression alternative in an immutable native SQL binding view. |
| inputs / outputs | \`BoundNode\` selects a frontend bound column/parameter, \`BoundLiteral\` with an optional \`storage::ScalarView\`, or \`BoundOperation\` with an argument \`Span&lt;ExpressionId&gt;\` into native expression storage. |
| invariants | The discriminant is data, not proof that IDs or spans are valid; the native compiler copies/fixes this metadata from checked binding. |
| ownership | Expression nodes and operation spans belong to immutable compiled-program storage. A literal string view borrows its bytes from that arena; non-string \`ScalarView\` alternatives, including \`InlineDecimal\`, are stored inline. References/spans into the node array require the program owner. |
| failure | Wrong-kind access or invalid IDs are handled by consumers; alias construction performs no range/type validation. |
| cost | The variant is inline; argument traversal and scalar export incur work only when consumers visit them. |
| Design | [include/crown/ir/program_model.hpp §BoundNode and BoundExpression](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/program.hpp §native program owner](../../../../../../include/crown/ir/program.hpp), [src/planner/compiled_source.cpp §DTO export](../../../../../../src/planner/compiled_source.cpp) |

## B0029

[Lines 128–132](../../../../../../include/crown/ir/program_model.hpp#L128); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundExpression {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a typed SQL expression node and optional source location. |
| inputs / outputs | Combines SqlType, BoundNode variant and location. |
| invariants | Binding resolves identifiers and type; the record does not bind itself. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L128-132](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/bind.hpp §L28-32](../../../../../../include/crown/frontend/bind.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0030

[Lines 133–139](../../../../../../include/crown/ir/program_model.hpp#L133); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundOccurrence {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a bound table occurrence and requested scan metadata. |
| inputs / outputs | Carries table, alias, column-name span, source location and include_descendants. |
| invariants | include_descendants records requested scan; flat catalogs currently have no inheritance edges. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L133-139](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/bind.hpp §L33-39](../../../../../../include/crown/frontend/bind.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0031

[Lines 140–143](../../../../../../include/crown/ir/program_model.hpp#L140); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundOutput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one ordered SQL output name and expression ID. |
| inputs / outputs | Carries borrowed name and ExpressionId. |
| invariants | Binder establishes output resolution and order; this record does not evaluate it. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L140-143](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/bind.hpp §L40-40](../../../../../../include/crown/frontend/bind.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0032

[Lines 144–158](../../../../../../include/crown/ir/program_model.hpp#L144); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundSql {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the bound SQL source, schema and ordered expression graph. |
| inputs / outputs | Carries source/catalog, parameters, semantics/wrapper, occurrences, expressions, predicates, outputs, limits and work. |
| invariants | It is binder output; it does not itself bind SQL or admit a physical plan. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L144-158](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/bind.hpp §L52-76](../../../../../../include/crown/frontend/bind.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0033

[Lines 159–160](../../../../../../include/crown/ir/program_model.hpp#L159); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using SqlValue = std::optional<storage::ScalarView>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent nullable SQL values in the native normalized view using borrowed scalar storage. |
| inputs / outputs | \`SqlValue\` is \`optional&lt;storage::ScalarView&gt;\`; an empty optional carries SQL NULL and a present view carries an exact scalar. |
| invariants | This is a native read-only view, not the owning frontend \`optional&lt;Value&gt;\` and not a nullable core \`Value\`. |
| ownership | A present string alternative borrows bytes from the compiled-program arena; other \`ScalarView\` alternatives, including \`InlineDecimal\`, are inline values. References/spans exposing the \`SqlValue\` descriptor still require the program owner. |
| failure | The alias does not validate the scalar against its SQL type or source column; binder/compiler checks occur separately. |
| cost | The descriptor is optional plus scalar view; it avoids copying the payload when read, while export may materialize owning DTO data. |
| Design | [include/crown/ir/program_model.hpp §SqlValue](../../../../../../include/crown/ir/program_model.hpp), [include/crown/storage/accounted_row.hpp §ScalarView](../../../../../../include/crown/storage/accounted_row.hpp), [include/crown/ir/program.hpp §lifetime](../../../../../../include/crown/ir/program.hpp) |

## B0034

[Lines 161–164](../../../../../../include/crown/ir/program_model.hpp#L161); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ColumnConstant {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a constant attached to a logical column. |
| inputs / outputs | Pairs ColumnId with ScalarView. |
| invariants | Normalization and checked program construction establish mapping/type compatibility. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L161-164](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/normalize.hpp §L19-20](../../../../../../include/crown/frontend/normalize.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0035

[Lines 165–175](../../../../../../include/crown/ir/program_model.hpp#L165); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OccurrenceAdapter {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one occurrence’s filtering/equality/projection program. |
| inputs / outputs | Carries occurrence/base plus spans for predicates, non-null columns, equal columns, classes, projections, expressions and constants. |
| invariants | The owning normalizer documents its expression program as topologically ordered; the view does not execute it. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L165-175](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/normalize.hpp §L20-31](../../../../../../include/crown/frontend/normalize.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0036

[Lines 176–176](../../../../../../include/crown/ir/program_model.hpp#L176); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ConstantOutput { storage::ScalarView value; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one normalized scalar constant output. |
| inputs / outputs | Carries ScalarView. |
| invariants | Output position/type mapping is represented by NormalizedOutput and established during normalization. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L176-176](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/normalize.hpp §L32-38](../../../../../../include/crown/frontend/normalize.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0037

[Lines 177–181](../../../../../../include/crown/ir/program_model.hpp#L177); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NormalizedOutput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a named typed output mapped to core output or constant. |
| inputs / outputs | Carries name, SqlType and CoreOutput/ConstantOutput variant. |
| invariants | The variant records the selected source; admission establishes mapping correctness. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L177-181](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/normalize.hpp §L32-38](../../../../../../include/crown/frontend/normalize.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0038

[Lines 182–194](../../../../../../include/crown/ir/program_model.hpp#L182); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NormalizedSql {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose bound SQL specialized into a classical core and adapters. |
| inputs / outputs | Carries parameter/constants spans, core catalog/query, adapters/routes/outputs, limits, work and schema version. |
| invariants | Constants include SQL NULL and unused sentinel slots in the owning model; dependency metadata belongs to compiler use. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L182-194](../../../../../../include/crown/ir/program_model.hpp), [include/crown/frontend/normalize.hpp §L39-63](../../../../../../include/crown/frontend/normalize.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0040

[Lines 196–201](../../../../../../include/crown/ir/program_model.hpp#L196); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CachePolicy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose four policy tag strings for identity/cache consumers. |
| inputs / outputs | Carries arithmetic, planner, optimization and cost-model labels. |
| invariants | Tags are labels/configuration, not a cache hit or compatibility proof. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L196-201](../../../../../../include/crown/ir/program_model.hpp), [include/crown/io/identity.hpp §L8-13,25-32](../../../../../../include/crown/io/identity.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0041

[Lines 202–206](../../../../../../include/crown/ir/program_model.hpp#L202); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose selected physical policy, limits and optional indexed backend spec. |
| inputs / outputs | Groups CachePolicy, PhysicalLimits and optional indexed_storage. |
| invariants | Options describe configuration; they do not imply that execution has started or has a runtime bound. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L202-206](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/physical.hpp §L83-94](../../../../../../include/crown/ir/physical.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0042

[Lines 207–223](../../../../../../include/crown/ir/program_model.hpp#L207); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GuaranteeProfile {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose compile-time semantic/status labels and mode/assumption/accounting lists. |
| inputs / outputs | Carries semantic/backend/status tags and spans for operation modes, assumptions and output accounting. |
| invariants | PhysicalPlan documents these as compile-time capabilities; construction implies no maintained runtime/cursor performance bound. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L207-223](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/physical.hpp §L95-113](../../../../../../include/crown/ir/physical.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0043

[Lines 224–233](../../../../../../include/crown/ir/program_model.hpp#L224); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QueryIdentity {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose canonical JSON, digest labels, order maps and producer work. |
| inputs / outputs | Carries canonical view, four SHA-256 strings, occurrence/variable order spans and work. |
| invariants | Order maps mean canonical position to original ID; a cache consumer translates IDs and producer computes the identity. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L224-233](../../../../../../include/crown/ir/program_model.hpp), [include/crown/io/identity.hpp §L14-32](../../../../../../include/crown/io/identity.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0045

[Lines 235–241](../../../../../../include/crown/ir/program_model.hpp#L235); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalRelation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one relation role, accounted layout and optional provenance. |
| inputs / outputs | Carries relation ID/role, AccountedLayout, optional node and base table. |
| invariants | Relation/layout/provenance consistency is established by checked program construction. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. Embedded AccountedLayout/AccountedProjection handles independently retain their immutable funded metadata, not every other borrowed member. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. Copying embedded shared layout/projection handles retains their control; final handle release can destroy metadata. |
| Design | [include/crown/ir/program_model.hpp §L235-241](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/physical.hpp §L18-24](../../../../../../include/crown/ir/physical.hpp), [include/crown/storage/accounted_layout.hpp §L38-66](../../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0046

[Lines 242–242](../../../../../../include/crown/ir/program_model.hpp#L242); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceTable {RelationId relation;storage::AccountedLayout layout;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Associate a relation with its accounted source layout. |
| inputs / outputs | Carries RelationId and AccountedLayout. |
| invariants | The aggregate itself does not verify that relation and layout IDs agree. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. Embedded AccountedLayout/AccountedProjection handles independently retain their immutable funded metadata, not every other borrowed member. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. Copying embedded shared layout/projection handles retains their control; final handle release can destroy metadata. |
| Design | [include/crown/ir/program_model.hpp §L242-242](../../../../../../include/crown/ir/program_model.hpp), [include/crown/storage/accounted_layout.hpp §L38-66](../../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0047

[Lines 243–248](../../../../../../include/crown/ir/program_model.hpp#L243); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexRequirement {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe an index projection and its declared uses. |
| inputs / outputs | Carries requirement/relation IDs, AccountedProjection and IndexUse span. |
| invariants | Index compatibility/existence belongs to checked lowering/storage construction. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. Embedded AccountedLayout/AccountedProjection handles independently retain their immutable funded metadata, not every other borrowed member. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. Copying embedded shared layout/projection handles retains their control; final handle release can destroy metadata. |
| Design | [include/crown/ir/program_model.hpp §L243-248](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/physical.hpp §L25-30](../../../../../../include/crown/ir/physical.hpp), [include/crown/storage/accounted_projection.hpp §L26-50](../../../../../../include/crown/storage/accounted_projection.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0048

[Lines 249–252](../../../../../../include/crown/ir/program_model.hpp#L249); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputConstant {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a scalar value attached to one physical field. |
| inputs / outputs | Pairs FieldId with ScalarView. |
| invariants | Field/value compatibility belongs to checked input-adapter construction. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L249-252](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/physical.hpp §L31-32](../../../../../../include/crown/ir/physical.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0049

[Lines 253–262](../../../../../../include/crown/ir/program_model.hpp#L253); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalInput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose physical/logical source mapping and adapter conditions. |
| inputs / outputs | Carries occurrence/node/base/logical IDs, accounted layout/projection and spans of equalities/constants. |
| invariants | Field mapping consistency is established by compiler construction, not the carrier. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. Embedded AccountedLayout/AccountedProjection handles independently retain their immutable funded metadata, not every other borrowed member. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. Copying embedded shared layout/projection handles retains their control; final handle release can destroy metadata. |
| Design | [include/crown/ir/program_model.hpp §L253-262](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/physical.hpp §L31-42](../../../../../../include/crown/ir/physical.hpp), [include/crown/storage/accounted_layout.hpp §L38-66](../../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp §L26-50](../../../../../../include/crown/storage/accounted_projection.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0050

[Lines 263–279](../../../../../../include/crown/ir/program_model.hpp#L263); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalNode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose physical tree topology, scopes, layouts and relation IDs. |
| inputs / outputs | Carries node links/scopes, connex flag, accounted layout/projections and record/survivor/support/visible IDs. |
| invariants | Topology and field mappings are checked by plan validation/lowering, not by this aggregate. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. Embedded AccountedLayout/AccountedProjection handles independently retain their immutable funded metadata, not every other borrowed member. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. Copying embedded shared layout/projection handles retains their control; final handle release can destroy metadata. |
| Design | [include/crown/ir/program_model.hpp §L263-279](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/physical.hpp §L43-59](../../../../../../include/crown/ir/physical.hpp), [include/crown/storage/accounted_layout.hpp §L38-66](../../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp §L26-50](../../../../../../include/crown/storage/accounted_projection.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0051

[Lines 280–286](../../../../../../include/crown/ir/program_model.hpp#L280); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalEdge {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one parent-child edge and lookup projection. |
| inputs / outputs | Carries parent/child IDs, child slot, AccountedProjection and optional reverse-index ID. |
| invariants | Topology/index consistency belongs to checked lowering and validation. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. Embedded AccountedLayout/AccountedProjection handles independently retain their immutable funded metadata, not every other borrowed member. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. Copying embedded shared layout/projection handles retains their control; final handle release can destroy metadata. |
| Design | [include/crown/ir/program_model.hpp §L280-286](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/physical.hpp §L60-66](../../../../../../include/crown/ir/physical.hpp), [include/crown/storage/accounted_projection.hpp §L26-50](../../../../../../include/crown/storage/accounted_projection.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0052

[Lines 287–294](../../../../../../include/crown/ir/program_model.hpp#L287); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EnumerationStep {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one node/relation enumeration step. |
| inputs / outputs | Carries depth, optional parent step/key and optional bucket index. |
| invariants | Step links/order are emitted by compiler enumeration construction; the aggregate does not validate them. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. Embedded AccountedLayout/AccountedProjection handles independently retain their immutable funded metadata, not every other borrowed member. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. Copying embedded shared layout/projection handles retains their control; final handle release can destroy metadata. |
| Design | [include/crown/ir/program_model.hpp §L287-294](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/physical.hpp §L69-76](../../../../../../include/crown/ir/physical.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0053

[Lines 295–300](../../../../../../include/crown/ir/program_model.hpp#L295); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EnumerationProgram {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the ordered enumeration schedule and output/equality assignments. |
| inputs / outputs | Carries step, output-slot and equality spans plus depth. |
| invariants | The owning physical model documents parent-before-child steps over C* and preserves ordered/repeated core head slots; view does not execute or prove this. |
| ownership | string_view, Span, Set and JsonView members borrow stable backing and do not retain it. ScalarView stores integer/Boolean/date/inline-decimal values inline; only its text alternative borrows bytes. For views returned by CompiledProgram, retain that immutable owner; independently assembled carriers require caller-owned backing and confer no admission authority. |
| failure | A correctly initialized carrier copy does not validate bounds, source binding or proof. Borrowed storage must remain live/unchanged. Checked factories establish admission; later view access and consumers keep their own validation/error contracts. |
| cost | Fixed-size record/view copying does not copy the referenced arrays or text. Deep freeze/import, validation, traversal and DTO export are separate costs. |
| Design | [include/crown/ir/program_model.hpp §L295-300](../../../../../../include/crown/ir/program_model.hpp), [include/crown/ir/physical.hpp §L67-82](../../../../../../include/crown/ir/physical.hpp), [include/crown/ir/program.hpp §L26-29,57-102](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §L226-245,269-286,386-400,441-478](../../../../../../src/ir/program.cpp) |

## B0054

[Lines 301–302](../../../../../../include/crown/ir/program_model.hpp#L301); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L301-L302:sha256:4ff6c26b9f05e6d8d89670faf10680de2de856f8133233e2581053c2039529ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::program at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/ir/program_model.hpp](../../../../../../include/crown/ir/program_model.hpp), [docs/code_specs/files/include/crown/ir/program_model.hpp.md](program_model.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |
