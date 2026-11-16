# `include/crown/frontend/bind.hpp` — block usage map

[Source](../../../../../../include/crown/frontend/bind.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Resolve table/column aliases, expressions and exact typed literals against catalog metadata.

Snapshot SHA-256: `37dfc7fb511397a3654a2838ccf6c51db60fd0822071d731db7388e9d89c6e79`. 79 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../../sql_support.md), [docs/sql_parser.md](../../../../../sql_parser.md), [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_admission.md](../../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/frontend/bind.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../../include/crown/frontend/bind.hpp#L8) | Type/record definition: struct ExpressionId |  · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../../include/crown/frontend/bind.hpp#L9) | Type/record definition: enum class SqlKind |  · [reviewed contract](#b0003) |
| [B0004 · 10–15](../../../../../../include/crown/frontend/bind.hpp#L10) | Type/record definition: struct SqlType |  · [reviewed contract](#b0004) |
| [B0005 · 16–16](../../../../../../include/crown/frontend/bind.hpp#L16) | Type/record definition: struct BoundColumn |  · [reviewed contract](#b0005) |
| [B0006 · 17–17](../../../../../../include/crown/frontend/bind.hpp#L17) | Explanatory comments or spacing. | source comment (unverified): // NULL belongs only to the SQL boundary. It is not a crown::Value. · [reviewed contract](#b0006) |
| [B0007 · 18–18](../../../../../../include/crown/frontend/bind.hpp#L18) | Type/record definition: struct BoundLiteral | source comment (unverified): // NULL belongs only to the SQL boundary. It is not a crown::Value. · [reviewed contract](#b0007) |
| [B0008 · 19–19](../../../../../../include/crown/frontend/bind.hpp#L19) | Type/record definition: struct BoundParameter | source comment (unverified): // One based. · [reviewed contract](#b0008) |
| [B0009 · 20–25](../../../../../../include/crown/frontend/bind.hpp#L20) | Type/record definition: enum class SqlOperator |  · [reviewed contract](#b0009) |
| [B0010 · 26–26](../../../../../../include/crown/frontend/bind.hpp#L26) | Type/record definition: struct BoundOperation |  · [reviewed contract](#b0010) |
| [B0011 · 27–27](../../../../../../include/crown/frontend/bind.hpp#L27) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 28–32](../../../../../../include/crown/frontend/bind.hpp#L28) | Type/record definition: struct BoundExpression |  · [reviewed contract](#b0012) |
| [B0013 · 33–39](../../../../../../include/crown/frontend/bind.hpp#L33) | Type/record definition: struct BoundOccurrence | source comment (unverified): // Requested SQL scan; this catalog has no inheritance edges. · [reviewed contract](#b0013) |
| [B0014 · 40–40](../../../../../../include/crown/frontend/bind.hpp#L40) | Type/record definition: struct BoundOutput |  · [reviewed contract](#b0014) |
| [B0015 · 41–41](../../../../../../include/crown/frontend/bind.hpp#L41) | Type/record definition: enum class SqlSemantics |  · [reviewed contract](#b0015) |
| [B0016 · 42–42](../../../../../../include/crown/frontend/bind.hpp#L42) | Type/record definition: enum class SqlWrapper |  · [reviewed contract](#b0016) |
| [B0017 · 43–47](../../../../../../include/crown/frontend/bind.hpp#L43) | Type/record definition: struct BindLimits |  · [reviewed contract](#b0017) |
| [B0018 · 48–51](../../../../../../include/crown/frontend/bind.hpp#L48) | Type/record definition: struct BindOptions |  · [reviewed contract](#b0018) |
| [B0019 · 52–66](../../../../../../include/crown/frontend/bind.hpp#L52) | Type/record definition: struct BoundSql | source comment (unverified): // Ordered SELECT outputs; inner outputs for EXISTS, whose outer name is wrapper_alias. · [reviewed contract](#b0019) |
| [B0020 · 67–67](../../../../../../include/crown/frontend/bind.hpp#L67) | Type/record definition: struct BindingDiagnostic |  · [reviewed contract](#b0020) |
| [B0021 · 68–79](../../../../../../include/crown/frontend/bind.hpp#L68) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Parse and resolve one SELECT against an owned catalog snapshot. The returned · [reviewed contract](#b0021) |

## B0001

[Lines 1–7](../../../../../../include/crown/frontend/bind.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using OccurrenceId = crown::OccurrenceId;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse the core occurrence identifier type in SQL binding APIs. |
| inputs / outputs | \`frontend::OccurrenceId\` names the same typed ID as \`crown::OccurrenceId\`; bound occurrences and column references use it. |
| invariants | This is a type alias, so it adds no separate ID range or namespace-specific identity. The binder assigns occurrence positions in its bound representation. |
| ownership | The alias owns no storage; IDs are small values stored by the surrounding bound program. |
| failure | The alias performs no range validation. Binding or a later consumer checks the ID against the relevant occurrence list. |
| cost | No wrapper object or conversion is introduced; storage and lookup costs come from the containing expression/program. |
| Design | [include/crown/frontend/bind.hpp §OccurrenceId alias](../../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp §Binder occurrence resolution](../../../../../../src/frontend/bind.cpp), [docs/sql_binding.md §occurrences](../../../../../sql_binding.md) |

## B0002

[Lines 8–8](../../../../../../include/crown/frontend/bind.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExpressionId {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify an expression by its dense zero-based position in one BoundSql expression vector. |
| inputs / outputs | Stores size_t value and supplies memberwise comparison; append returns IDs and consumers use value as the vector subscript. |
| invariants | The ID is local to its owning BoundSql, has no invalid sentinel and does not establish bounds by construction; copying an ID does not copy the expression. |
| ownership | Owns only the numeric index; it neither retains nor borrows a pointer to its BoundSql. |
| failure | The aggregate and defaulted comparisons do no validation and throw no semantic diagnostic; callers must retain the matching result and use valid indexes. |
| cost | Constant-size storage, constant-time construction and numeric comparison; no allocation. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../../src/frontend/normalize.cpp) |

## B0003

[Lines 9–9](../../../../../../include/crown/frontend/bind.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SqlKind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the scalar kinds used at the SQL binding boundary, including unresolved literals and integer widths. |
| inputs / outputs | Enumerates unknown, int32, int64, string, boolean, date and decimal; sql_kind_name supplies stable serialized spellings. |
| invariants | unknown is a resolution state for SQL string/NULL literals, not a new core Value type. Both integer widths use the int64 Value alternative; catalog integers map to int64. |
| ownership | A value-sized enum with no owned external data. |
| failure | The enum itself rejects nothing; sql_kind_name throws binding_contract for an out-of-domain enum value. |
| cost | Constant-size storage and comparisons, with no allocation in the type itself. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp) |

## B0004

[Lines 10–15](../../../../../../include/crown/frontend/bind.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlType {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the full SQL kind, nullable bit and optional exact decimal specification attached to an expression. |
| inputs / outputs | Defaults to unknown, non-nullable and no decimal specification; defaulted comparison includes every member. |
| invariants | Identity casts compare the full type, including integer width, decimal precision/scale and nullability. Binary collation is checked on declarations rather than represented here. This aggregate alone does not enforce kind/spec consistency. |
| ownership | Owns scalar metadata and an inline optional DecimalSpec; no borrowed catalog metadata. |
| failure | No validation or diagnostic occurs on aggregate construction; bind_sql validates catalog/parameter declarations and binding code checks conversions. |
| cost | Fixed-size inline storage and constant memberwise comparison; no allocation. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [docs/scalars.md](../../../../../scalars.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp) |

## B0005

[Lines 16–16](../../../../../../include/crown/frontend/bind.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundColumn {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route a bound column to one occurrence and one physical catalog column position. |
| inputs / outputs | Carries OccurrenceId and ColumnId; the occurrence selects a table through BoundSql.occurrences. |
| invariants | Self-join occurrences remain distinct even when table IDs coincide. Alias column renaming changes visible names, not this physical position. |
| ownership | Owns two index values and no relation or column object; the surrounding BoundSql owns their targets. |
| failure | The aggregate does not check either index; generated bindings create them from vector positions and normalization separately checks references. |
| cost | Constant-size value storage and copying; no allocation. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../../src/frontend/normalize.cpp) |

## B0006

[Lines 17–17](../../../../../../include/crown/frontend/bind.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:e20b08a910fdd2c7dbad19285c3adc2947bf1ebb25cd44b9e958a063058f85de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: NULL belongs only to the SQL boundary. It is not a crown::Value. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/frontend/bind.hpp lines 15-19; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp), [docs/code_specs/files/include/crown/frontend/bind.hpp.md](bind.hpp.md), [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_parser.md](../../../../../sql_parser.md) |

## B0007

[Lines 18–18](../../../../../../include/crown/frontend/bind.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundLiteral {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a checked scalar literal or SQL NULL without adding NULL to the classical core Value domain. |
| inputs / outputs | optional&lt;Value&gt; is disengaged for SQL NULL and engaged for int64/string/bool/date/decimal values; the enclosing expression supplies SqlType. |
| invariants | String and NULL literals may initially have unknown kind. Literal casts can replace the stored value and type before appending a cast operation; NULL never becomes a crown::Value alternative. |
| ownership | Owns any scalar value, including string and Decimal coefficient storage; copying duplicates those payloads. |
| failure | The aggregate performs no parsing or type/value consistency checks; literal and cast perform those checks before successful binding returns. |
| cost | Inline variant/optional metadata plus owned scalar payload; copying is linear in string length or bounded Decimal coefficient size and may allocate. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp) |

## B0008

[Lines 19–19](../../../../../../include/crown/frontend/bind.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundParameter {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Refer to a declared positional SQL parameter without binding its concrete value. |
| inputs / outputs | Stores the one-based PostgreSQL parameter number; expression type comes from BoundSql.parameters\[number-1\]. |
| invariants | Parameter numbers differ from zero-based expression IDs. bind_sql requires a declaration for every referenced number but does not require every declaration to be referenced. |
| ownership | Owns only the number; the BoundSql owns the signature and a later normalization option supplies values. |
| failure | The aggregate does not validate zero or range; bind_expression reports unbound_parameter before constructing an invalid parameter node. |
| cost | Constant-size value storage, no allocation or lookup in the type itself. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../../src/frontend/normalize.cpp) |

## B0009

[Lines 20–25](../../../../../../include/crown/frontend/bind.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SqlOperator {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the finite operations that binding can retain for comparisons, Boolean/NULL tests, casts, widening and merged INNER JOIN values. |
| inputs / outputs | Operation tags accompany ordered argument IDs in BoundOperation and serialize through sql_operator_name. |
| invariants | No arithmetic, function, aggregate or outer-join operation is represented. using_value is the left value under a separately retained mandatory inner equality predicate; these tags do not themselves evaluate SQL. |
| ownership | A scalar tag owns no expression data. |
| failure | The enum itself checks nothing; unsupported AST operators fail while binding and invalid enum values fail in spelling/evaluation consumers. |
| cost | Constant-size storage and comparisons; no allocation. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../../src/frontend/normalize.cpp) |

## B0010

[Lines 26–26](../../../../../../include/crown/frontend/bind.hpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundOperation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store an operator and its ordered dependencies in the bound expression DAG. |
| inputs / outputs | Carries SqlOperator plus vector&lt;ExpressionId&gt;; binder emits one argument for casts/tests/NOT, two for comparisons/USING and a nonempty vector for AND/OR. |
| invariants | Generated operation argument IDs precede the operation in BoundSql.expressions. The aggregate does not enforce arity, type compatibility or acyclicity itself. |
| ownership | Owns the argument vector but no child expressions; IDs are local to the surrounding BoundSql. |
| failure | Vector creation/copying may throw allocation exceptions; semantic arity and type failures are handled by binder or checked later by normalization. |
| cost | O(argument count) ID storage and copy, with vector allocation when nonempty; moving transfers the vector buffer. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../../src/frontend/normalize.cpp) |

## B0011

[Lines 27–27](../../../../../../include/crown/frontend/bind.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using BoundNode = std::variant<BoundColumn, BoundLiteral, BoundParameter, BoundOperation>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tag the four kinds of expression node retained by the SQL binder. |
| inputs / outputs | A \`BoundNode\` holds a bound column, literal/SQL NULL, positional parameter, or operation with expression-ID arguments. |
| invariants | The variant distinguishes alternatives but does not validate expression IDs, types, argument arity, or nullability; \`Binder\` constructs those links. |
| ownership | The selected alternative stores IDs/values directly and operation arguments in an owned \`std::vector\` within its containing \`BoundExpression\`. |
| failure | The alias adds no validation. Binder checks expression IDs, types, operation arity, and nullability while building nodes; consumers must still check links when reading externally assembled DTOs. The variant tag itself is not a binding-validation result. |
| cost | The variant stores one alternative and its payload; operation vector allocation and recursive binding work are separate. |
| Design | [include/crown/frontend/bind.hpp §BoundNode and BoundExpression](../../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp §expression construction](../../../../../../src/frontend/bind.cpp), [docs/sql_binding.md §expression kinds](../../../../../sql_binding.md) |

## B0012

[Lines 28–32](../../../../../../include/crown/frontend/bind.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundExpression {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Associate SQL type and source location with one owned node in the dense binding expression list. |
| inputs / outputs | Contains SqlType, the BoundNode variant and an optional zero-based byte offset into BoundSql.source. |
| invariants | Node type and payload must agree in successful bindings; operations are topological. A source reference to a visible column is appended as a new expression with its use-site location. |
| ownership | Owns the variant payload; column/parameter/operation references are numeric IDs, while literal and operation vectors own their data. Offsets refer to the owning result source by number. |
| failure | Aggregate construction has no contract checks; payload copies may allocate, and the binder checks limits before append. |
| cost | Fixed envelope plus any literal bytes or argument vector; vector growth can relocate/copy expression payloads, so references must not survive an append. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../../src/frontend/normalize.cpp) |

## B0013

[Lines 33–39](../../../../../../include/crown/frontend/bind.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundOccurrence {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a distinct physical-table use and its SQL-visible relation/column metadata. |
| inputs / outputs | Stores table ID, alias, ordered column names, optional source offset and requested include_descendants flag. |
| invariants | Every RangeVar creates an occurrence, including self joins. Column names incorporate base-relation alias prefix renames. Join aliases affect scope separately. Flat catalogs contain no inheritance edges, so the flag records SQL intent only. |
| ownership | Owns alias and column-name strings; table is an index into the result-owned catalog snapshot. |
| failure | The aggregate does not validate table IDs or names; Binder::from resolves names, applies alias checks and appends the record. |
| cost | O(alias bytes + visible column-name bytes) owned storage and copying; no physical table rows are retained here. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp) |

## B0014

[Lines 40–40](../../../../../../include/crown/frontend/bind.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundOutput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one select-list position and its visible output name without coalescing repeated columns. |
| inputs / outputs | Pairs an owned name with an ExpressionId; BoundSql.outputs preserves target-list and wildcard expansion order. |
| invariants | Duplicate names and repeated expression IDs are valid. For an EXISTS wrapper these are the inner SELECT outputs, while wrapper_alias names the outer Boolean result. |
| ownership | Owns the output name and a numeric reference to an expression owned by the same BoundSql. |
| failure | No name uniqueness or ID check occurs in the aggregate; allocation can fail when copying a name or growing outputs. |
| cost | O(name bytes) name storage/copy and constant ID storage; no expression subtree is copied by this record. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [src/io/binding.cpp](../../../../../../src/io/binding.cpp) |

## B0015

[Lines 41–41](../../../../../../include/crown/frontend/bind.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SqlSemantics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve whether the SELECT requests ordinary bag rows or DISTINCT set projection. |
| inputs / outputs | A set/bag tag is stored as outer semantics, with optional separate inner_semantics for EXISTS. |
| invariants | Plain SELECT remains bag; binding never silently introduces DISTINCT. The tag records requested semantics and does not admit or execute them. |
| ownership | Value-sized enum, no external ownership. |
| failure | No validation in the enum; select rejects DISTINCT ON and unsupported clauses before returning a successful binding. |
| cost | Constant-size metadata and no allocation. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_support.md](../../../../../sql_support.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp) |

## B0016

[Lines 42–42](../../../../../../include/crown/frontend/bind.hpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SqlWrapper {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish ordinary row results from the supported whole-result EXISTS wrapper. |
| inputs / outputs | rows is the BoundSql default; exists is set only for one top-level EXISTS target with no outer FROM/filter. |
| invariants | EXISTS is a Boolean result wrapper, distinct from a nullary core CQ answer. Inner output bindings remain available for checking and downstream processing. |
| ownership | Value-sized enum retaining no query object. |
| failure | No validation in the enum; Binder::run checks the allowed outer wrapper shape and otherwise the expression binder rejects sublinks. |
| cost | Constant-size metadata; no allocation. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [docs/semantics.md](../../../../../semantics.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp) |

## B0017

[Lines 43–47](../../../../../../include/crown/frontend/bind.hpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BindLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure binder checkpoint work, expression-count and active-recursion bounds. |
| inputs / outputs | Defaults are work_limit=1,000,000, expression_limit=100,000 and recursion_limit=128; disengaged work_limit disables its configured threshold. |
| invariants | Zero is a real limit for each bound. Work counter overflow still rejects when the configured work bound is absent. These checkpoints do not count all metadata validation, string comparison, copying, allocation or CPU work; parser limits are separate. |
| ownership | Owns fixed-size numeric limit values, copied into BoundSql. |
| failure | The aggregate performs no validation; charge, append and Frame throw resource_limit before their respective checked increments/appends. |
| cost | Constant storage and copy; enforcing a checkpoint is constant work, not an account of total time or bytes. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [include/crown/frontend/parser.hpp](../../../../../../include/crown/frontend/parser.hpp) |

## B0018

[Lines 48–51](../../../../../../include/crown/frontend/bind.hpp#L48); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BindOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide an owned positional parameter type declaration list and binder limits for bind_sql. |
| inputs / outputs | parameters is a vector of Column metadata in positional order; names are replaced with $1, $2, ... for parameter validation. limits selects binder bounds. |
| invariants | Parameters use catalog scalar kinds, nullable metadata, binary collation and optional decimal specs; no int32 parameter kind exists in Column. Concrete parameter values are not bound here. |
| ownership | The caller owns the options; bind_sql borrows it for the call, validates a copy and copies mapped SqlTypes/limits into the result. |
| failure | Invalid metadata becomes a parameters-phase Error diagnostic; allocation failures during pre-Binder parameter copying/validation are outside the Binder bad_alloc catch. |
| cost | O(parameter metadata bytes) input storage and validation-copy cost; result signatures keep only fixed SqlType metadata per declaration. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [src/io/binding.cpp](../../../../../../src/io/binding.cpp) |

## B0019

[Lines 52–66](../../../../../../include/crown/frontend/bind.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BoundSql {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a complete typed SQL binding snapshot for serialization and later normalization/admission. |
| inputs / outputs | Stores source/catalog, parameter types, row semantics and wrapper metadata, occurrences, expressions, predicate IDs, ordered outputs, applied limits and consumed checkpoint work. |
| invariants | IDs are local and zero-based except parameter numbers. Predicates include ON/WHERE and USING equalities; occurrences and repeated outputs are retained. Successful binding makes no CQ admission, plan, execution, incremental-runtime or paper-theorem claim. |
| ownership | All text/catalog/node vectors are owned; copy duplicates them and move transfers their containers. No borrowed parser/caller catalog pointers escape. Defaulted aggregate lifetime imposes no runtime cursor obligations. |
| failure | The aggregate itself accepts malformed manually assembled state; normalizer/replay consumers perform their own checks. Binding returns only a complete value or diagnostic, discarding private partial state. |
| cost | Owns O(source + catalog metadata + parameter types + occurrence/column names + expressions/edges + predicates + output names) storage; copying is proportional to these owned contents and may allocate. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../../src/frontend/normalize.cpp), [src/io/binding.cpp](../../../../../../src/io/binding.cpp) |

## B0020

[Lines 67–67](../../../../../../include/crown/frontend/bind.hpp#L67); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BindingDiagnostic {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an owning phase-labeled SQL diagnostic from parse/catalog/parameter/binding failures. |
| inputs / outputs | Pairs phase string (syntax, catalog, parameters or binding here) with SqlDiagnostic code/message and optional coordinates. |
| invariants | Catalog and parameter declaration failures carry no SQL location. Binding offsets are zero-based source bytes with one-based code-point positions when a valid offset is available. A diagnostic is an alternative to BoundSql, not a partial binding. |
| ownership | Owns both strings and the nested diagnostic; it outlives caller inputs and Binder destruction. |
| failure | Constructing/copying diagnostic strings can itself allocate and throw; this is not a no-throw error container. |
| cost | O(phase/code/message bytes) owned storage and copy; coordinate calculation belongs to the binder diagnostic helper. |
| Design | [docs/sql_binding.md](../../../../../sql_binding.md), [include/crown/frontend/parser.hpp](../../../../../../include/crown/frontend/parser.hpp), [src/frontend/bind.cpp](../../../../../../src/frontend/bind.cpp) |

## B0021

[Lines 68–79](../../../../../../include/crown/frontend/bind.hpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using SqlBindResult = std::variant<BoundSql, BindingDiagnostic>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the SQL binding result and the binder/name-rendering entry points. |
| inputs / outputs | \`bind_sql\` accepts source text, a catalog, and positional parameter options; it returns an owning \`BoundSql\` or a phase-tagged \`BindingDiagnostic\`. The name helpers render SQL type/operator enums. |
| invariants | A successful value owns source, catalog snapshot, occurrences, expressions, predicates, and outputs. Binding does not normalize, admit, plan, or execute the statement. |
| ownership | Success fields are ordinary owning strings/vectors/catalog values; the source and caller catalog/options may expire after return. |
| failure | Syntax, catalog, parameter, and caught binder failures use diagnostics. Parse/declaration validation and failures outside the documented Binder catches can still throw, including some allocation/contract failures. |
| cost | Parsing, catalog/parameter validation, copies, allocations, and Binder work are distinct; \`BindLimits\` count selected compiler steps rather than all workspace or elapsed time. |
| Design | [include/crown/frontend/bind.hpp §result and public declarations](../../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp §bind_sql catches](../../../../../../src/frontend/bind.cpp), [docs/sql_binding.md §binding result](../../../../../sql_binding.md) |
