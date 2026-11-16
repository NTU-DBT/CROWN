# `src/frontend/normalize.cpp` — block usage map

[Source](../../../../../src/frontend/normalize.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Normalize bound equality predicates, contradictions and SQL output semantics into a typed CQ.

Snapshot SHA-256: `9abd85f334f1621320b5351ea7dcbd92361ea99726f85285f3c4d35f18139aee`. 467 lines partitioned into 37 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/frontend/normalize.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 14–14](../../../../../src/frontend/normalize.cpp#L14) | Type/record definition: struct Failure |  · [reviewed contract](#b0002) |
| [B0003 · 15–17](../../../../../src/frontend/normalize.cpp#L15) | Callable definition: \[\[noreturn\]\] void fail(std::string code, std::string message, std::optional&lt;std::size_t&gt; location = {}) | calls std::move · [reviewed contract](#b0003) |
| [B0004 · 18–18](../../../../../src/frontend/normalize.cpp#L18) | Explanatory comments or spacing. | source comment (unverified): // All callers pass literals; construct owned diagnostic text only on failure. · [reviewed contract](#b0004) |
| [B0005 · 19–21](../../../../../src/frontend/normalize.cpp#L19) | Callable definition: void contract(bool condition, const char* message) | calls Error; source comment (unverified): // All callers pass literals; construct owned diagnostic text only on failure. · [reviewed contract](#b0005) |
| [B0006 · 22–33](../../../../../src/frontend/normalize.cpp#L22) | Callable definition: SqlDiagnostic diagnostic(const Failure& failure, std::string_view source) | calls size, reset; returns result; result; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 34–34](../../../../../src/frontend/normalize.cpp#L34) | Callable definition: bool integer(SqlKind kind) | calls ; returns kind == SqlKind::int32 \|\| kind == SqlKind::int64 · [reviewed contract](#b0007) |
| [B0008 · 35–45](../../../../../src/frontend/normalize.cpp#L35) | Callable definition: ScalarType scalar(SqlKind kind) | calls Error; returns ScalarType::int64; ScalarType::string · [reviewed contract](#b0008) |
| [B0009 · 46–56](../../../../../src/frontend/normalize.cpp#L46) | Callable definition: SqlType sql_type(const Column& column) | calls ; returns {kind, column.nullable, column.decimal} · [reviewed contract](#b0009) |
| [B0010 · 57–65](../../../../../src/frontend/normalize.cpp#L57) | Callable definition: bool fits(const SqlValue& value, const SqlType& type) | calls type_of, scalar, min, max; returns type.nullable; false · [reviewed contract](#b0010) |
| [B0011 · 66–70](../../../../../src/frontend/normalize.cpp#L66) | Callable definition: std::optional&lt;bool&gt; truth(const SqlValue& value) | calls contract; returns {}; std::get&lt;bool&gt;(*value) · [reviewed contract](#b0011) |
| [B0012 · 71–71](../../../../../src/frontend/normalize.cpp#L71) | Callable definition: SqlValue boolean(std::optional&lt;bool&gt; value) | calls ; returns value ? SqlValue{Value{*value}} : SqlValue{} · [reviewed contract](#b0012) |
| [B0013 · 72–112](../../../../../src/frontend/normalize.cpp#L72) | Callable definition: SqlValue evaluate_operation(const BoundOperation& node, const std::vector&lt;SqlValue&gt;& values) | calls at, arg, has_value, truth; returns values.at(node.arguments.at(i).value); arg(0); 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 113–114](../../../../../src/frontend/normalize.cpp#L113) | declares types or opens a type body. |  · [reviewed contract](#b0014) |
| [B0015 · 115–119](../../../../../src/frontend/normalize.cpp#L115) | Callable definition: public: Normalizer(const BoundSql& bound, const NormalizeOptions& options) | calls  · [reviewed contract](#b0015) |
| [B0016 · 120–120](../../../../../src/frontend/normalize.cpp#L120) | declares callable signatures. |  · [reviewed contract](#b0016) |
| [B0017 · 121–126](../../../../../src/frontend/normalize.cpp#L121) | Callable definition: private: void charge() | calls max, fail · [reviewed contract](#b0017) |
| [B0018 · 127–130](../../../../../src/frontend/normalize.cpp#L127) | Callable definition: const BoundExpression& expression(ExpressionId id) const | calls contract, size; returns result_.binding.expressions\[id.value\] · [reviewed contract](#b0018) |
| [B0019 · 131–137](../../../../../src/frontend/normalize.cpp#L131) | Callable definition: std::size_t root(std::size_t column) | calls charge; returns current; 2 loop sites · [reviewed contract](#b0019) |
| [B0020 · 138–144](../../../../../src/frontend/normalize.cpp#L138) | Callable definition: void unite(std::size_t left, std::size_t right) | calls root, std::swap · [reviewed contract](#b0020) |
| [B0021 · 145–147](../../../../../src/frontend/normalize.cpp#L145) | declares callable signatures. |  · [reviewed contract](#b0021) |
| [B0022 · 148–153](../../../../../src/frontend/normalize.cpp#L148) | Callable definition: VariableId variable(ScalarType type) | calls charge, size, push_back, std::to_string; returns id; growth push_back · [reviewed contract](#b0022) |
| [B0023 · 154–164](../../../../../src/frontend/normalize.cpp#L154) | Member/declaration region. |  · [reviewed contract](#b0023) |
| [B0024 · 165–232](../../../../../src/frontend/normalize.cpp#L165) | Callable definition: void Normalizer::analyze_expressions() | calls resize, size, charge, contract; growth insert, resize; 5 loop sites; source comment (unverified): // Unused pre-resolution string/NULL nodes may still have unknown kind. · [reviewed contract](#b0024) |
| [B0025 · 233–233](../../../../../src/frontend/normalize.cpp#L233) | Explanatory comments or spacing. |  |
| [B0026 · 234–268](../../../../../src/frontend/normalize.cpp#L234) | Callable definition: void Normalizer::predicate(ExpressionId id) | calls charge, expression, contract, unite; growth emplace_back, push_back; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 269–269](../../../../../src/frontend/normalize.cpp#L269) | Explanatory comments or spacing. |  |
| [B0028 · 270–285](../../../../../src/frontend/normalize.cpp#L270) | Callable definition: void Normalizer::program(OccurrenceAdapter& adapter) | calls push_back, empty, charge, back; growth insert, push_back; 3 loop sites · [reviewed contract](#b0028) |
| [B0029 · 286–286](../../../../../src/frontend/normalize.cpp#L286) | Explanatory comments or spacing. |  |
| [B0030 · 287–417](../../../../../src/frontend/normalize.cpp#L287) | Callable definition: NormalizedSql Normalizer::run() | calls charge, catalog::validate_catalog, fail, size; returns std::move(result_); growth emplace, insert, push_back, resize; 13 loop sites; source comment (unverified): // Only top-level AND is an unconditional conjunction. Equalities below OR, · [reviewed contract](#b0030) |
| [B0031 · 418–419](../../../../../src/frontend/normalize.cpp#L418) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0031) |
| [B0032 · 420–427](../../../../../src/frontend/normalize.cpp#L420) | Callable definition: SqlNormalizeResult normalize_sql(const BoundSql& binding, const NormalizeOptions& options) | calls Error, Normalizer, run, diagnostic; returns Normalizer(binding,options).run(); BindingDiagnostic{phase,diagnostic(failure,binding.source)} · [reviewed contract](#b0032) |
| [B0033 · 428–428](../../../../../src/frontend/normalize.cpp#L428) | Explanatory comments or spacing. |  |
| [B0034 · 429–451](../../../../../src/frontend/normalize.cpp#L429) | Callable definition: std::optional&lt;Row&gt; adapt_row(const NormalizedSql& query, OccurrenceId occurrence, const Row& physical) | calls at, validate_row, contract, evaluate_operation; returns {}; {}; growth push_back; 5 loop sites; source comment (unverified): // Each call copies query-wide constant slots before its local evaluation. · [reviewed contract](#b0034) |
| [B0035 · 452–452](../../../../../src/frontend/normalize.cpp#L452) | Explanatory comments or spacing. |  |
| [B0036 · 453–466](../../../../../src/frontend/normalize.cpp#L453) | Callable definition: Relation map_sql_result(const NormalizedSql& query, const Relation& core_result) | calls empty, contract, size, push_back; returns Relation{Row{Value{!core_result.empty()}}}; result; growth insert, push_back; 2 loop sites · [reviewed contract](#b0036) |
| [B0037 · 467–467](../../../../../src/frontend/normalize.cpp#L467) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend · [reviewed contract](#b0037) |

## B0001

[Lines 1–13](../../../../../src/frontend/normalize.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:b8261544a1256c2b2e93ec4a09f0895000d8fca203b17ab5aa5ed714845b8bc8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/frontend/normalize.hpp, crown/api/error.hpp, crown/catalog/catalog.hpp, algorithm, limits, map) and opens crown::frontend scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/code_specs/files/src/frontend/normalize.cpp.md](normalize.cpp.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0002

[Lines 14–14](../../../../../src/frontend/normalize.cpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Failure {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry an expected normalization rejection to the public diagnostic boundary. |
| inputs / outputs | Owned code/message and optional zero-based SQL byte location. |
| invariants | Used for declared unsupported/parameter/resource outcomes, not internal contract failures. |
| ownership | Owns strings; contains no source view. |
| failure | Unwinds only temporary Normalizer state; constructing strings may allocate. |
| cost | String construction/destruction scales with diagnostic bytes. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0003

[Lines 15–17](../../../../../src/frontend/normalize.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void fail(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a declared normalization rejection without returning a partial program. |
| inputs / outputs | Moves code/message and copies location into Failure. |
| invariants | Only the public Failure catch turns this path into SqlNormalizeResult diagnostics. |
| ownership | Failure owns the moved text. |
| failure | Always throws Failure after argument construction; allocation failure remains an allocation failure. |
| cost | No additional formatting or container; exception runtime cost is not a hot-path guarantee. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0004

[Lines 18–18](../../../../../src/frontend/normalize.cpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L18:sha256:f8feaa2534fca8d59ed956b227f915d1354033e828ca7d420fb6c33f5916c324
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: All callers pass literals; construct owned diagnostic text only on failure. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/frontend/normalize.cpp lines 16-20; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/code_specs/files/src/frontend/normalize.cpp.md](normalize.cpp.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0005

[Lines 19–21](../../../../../src/frontend/normalize.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void contract(bool condition,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate malformed internal bound/program state from supported-input rejection. |
| inputs / outputs | Accepts a condition and literal diagnostic pointer; returns only for true. |
| invariants | All internal callers pass string literals; false conditions are normalization_contract Error, not expected SQL diagnostics. |
| ownership | Borrows static literal; Error constructs owned diagnostic text only on failure. |
| failure | Throws Error on false; diagnostic construction may allocate on that failure path. |
| cost | Fixed branch with no success-path string construction or allocation; no checks are removed. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0006

[Lines 22–33](../../../../../src/frontend/normalize.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlDiagnostic diagnostic(const Failure&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map an expected failure to SQL byte and human source coordinates. |
| inputs / outputs | Copies diagnostic text, then scans the prefix ending at a valid byte location. |
| invariants | Positions are one-based; UTF-8 continuation bytes do not advance characters; out-of-range offsets are cleared. |
| ownership | Borrows source only during the scan; result owns its text and numbers. |
| failure | Text allocation may propagate; this helper does not validate source encoding independently. |
| cost | O(prefix bytes + copied diagnostic bytes), not constant diagnostic work. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0007

[Lines 34–34](../../../../../src/frontend/normalize.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool integer(SqlKind kind)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize the two SQL integer kinds for compatible comparisons. |
| inputs / outputs | SqlKind to bool. |
| invariants | Only int32 and int64 return true; unknown is false. |
| ownership | Value-only operation. |
| failure | No throwing operation. |
| cost | Fixed enum comparisons without allocation. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0008

[Lines 35–45](../../../../../src/frontend/normalize.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarType scalar(SqlKind kind)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map resolved SQL representation kinds to classical scalar tags. |
| inputs / outputs | int32/int64 both map to int64; other exact kinds retain their tag. |
| invariants | Width and decimal-domain constraints remain in SqlType even though core tags are coarser. |
| ownership | Returns an enum value. |
| failure | Unknown kind throws normalization_contract Error. |
| cost | Fixed switch; failure text may allocate. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0009

[Lines 46–56](../../../../../src/frontend/normalize.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlType sql_type(const Column&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover SQL type/nullability/domain metadata from a catalog column. |
| inputs / outputs | Column to SqlType; native int64 has SQL int64 kind. |
| invariants | Preserves nullability and DecimalSpec; does not coerce row values. |
| ownership | Copies only value metadata. |
| failure | Assumes a validated catalog enum/domain. |
| cost | Fixed switch and bounded metadata copy. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0010

[Lines 57–65](../../../../../src/frontend/normalize.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool fits(const SqlValue&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check specialized parameters and typed literals against exact SQL types. |
| inputs / outputs | Optional Value and expected SqlType to acceptance bool. |
| invariants | NULL requires nullable; non-NULL kind, int32 bounds and decimal domain must fit; no rounding. |
| ownership | Borrows values and type. |
| failure | Valid SqlType/Value alternatives are required; mismatches return false rather than converting. |
| cost | Type/range checks plus decimal_fits, which formats an owning canonical decimal string and may allocate; no complete row copy. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0011

[Lines 66–70](../../../../../src/frontend/normalize.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<bool> truth(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read SQL three-valued truth from an evaluated predicate. |
| inputs / outputs | NULL becomes disengaged optional; Boolean Value returns its contained truth. |
| invariants | Non-NULL predicate storage must contain bool. |
| ownership | Returns inline truth, retaining no source. |
| failure | Non-Boolean value throws normalization_contract Error. |
| cost | Fixed check/extraction; failure diagnostic may allocate. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0012

[Lines 71–71](../../../../../src/frontend/normalize.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlValue boolean(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a three-valued Boolean result into SQL optional Value storage. |
| inputs / outputs | Engaged optional true/false becomes bool Value; disengaged becomes SQL NULL. |
| invariants | Tests optional presence, preserving a contained false. |
| ownership | Returns an inline bool or empty optional. |
| failure | No allocating/throwing payload on this path. |
| cost | Fixed work and no heap buffer. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0013

[Lines 72–112](../../../../../src/frontend/normalize.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlValue evaluate_operation(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate one resolved local operation over already evaluated child slots. |
| inputs / outputs | BoundOperation and indexed SqlValue scratch to SqlValue. |
| invariants | Casts/USING use resolved representation; NULL comparisons yield UNKNOWN; AND/OR follow three-valued truth and short circuit the value scan. |
| ownership | Borrows slots; returned string/decimal values may be owning copies. |
| failure | Checked child indexing and internal truth/representation contracts throw; unsupported enum throws Error. |
| cost | Visits required arguments, comparison bytes and returned payload copies; using_value returns only its first argument, protected by the separate join equality. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0014

[Lines 113–114](../../../../../src/frontend/normalize.cpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Normalizer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own temporary state for occurrence-preserving equality normalization. |
| inputs / outputs | Copies BoundSql/options, then builds a normalized CQ, local programs and SQL output mapping. |
| invariants | Only unconditional top-level conjunctive equalities union physical occurrence/column identities; all atoms remain. |
| ownership | Owns binding, parameters, dependency sets and union-find vectors; no mutable input alias or native query account. |
| failure | Failure discards the entire temporary; Error and allocation failures propagate to their owning boundary. |
| cost | Compiler allocations/copies and set/map processing are explicit; selected work checkpoints are not a total CPU/memory cap. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0015

[Lines 115–119](../../../../../src/frontend/normalize.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Normalizer(const BoundSql& bound,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot the binding and specialization before normalization work starts. |
| inputs / outputs | BoundSql and NormalizeOptions to owned result_ seed. |
| invariants | Schema, limits and parameter values are copied exactly. |
| ownership | Deep copies binding/catalog/source/expression containers and parameter payloads. |
| failure | Allocation may fail before the first normalization work charge; member RAII discards partial state. |
| cost | O(copied binding/catalog/source/parameter storage), outside the selected charge counter. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0016

[Lines 120–120](../../../../../src/frontend/normalize.cpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L120:sha256:e41c832acfa8716b9c808c26eec7db3b166d231b8fc4c41d92d3e50bf308b7e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declares Normalizer::run as the private normalization entry point returning its completed NormalizedSql; its out-of-line definition performs conversion and validation. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/code_specs/files/src/frontend/normalize.cpp.md](normalize.cpp.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0017

[Lines 121–126](../../../../../src/frontend/normalize.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void charge() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one selected normalization work unit before its increment. |
| inputs / outputs | Reads optional limit and uint64 work; increments once on success. |
| invariants | At the finite limit or uint64 maximum, no increment occurs. |
| ownership | Mutates temporary result_ only. |
| failure | Raises resource_limit Failure; diagnostic construction may allocate. |
| cost | Fixed counter checks; does not charge every copy, catalog scan or allocation. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0018

[Lines 127–130](../../../../../src/frontend/normalize.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const BoundExpression& expression(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Access an expression through a checked binding-local ID. |
| inputs / outputs | ExpressionId to const BoundExpression reference. |
| invariants | ID must index the owned topological binding vector. |
| ownership | Reference borrows Normalizer-owned binding until its move/destruction. |
| failure | Out-of-range ID throws normalization_contract Error. |
| cost | Fixed ID check and indexed access; owned diagnostic text is constructed only on failure. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0019

[Lines 131–137](../../../../../src/frontend/normalize.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t root(std::size_t column)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find and compress one physical-column equality representative. |
| inputs / outputs | Valid flattened column index to representative index. |
| invariants | Parent links form a forest; traversed links are compressed only toward the same root. |
| ownership | Mutates temporary parent_ vector; does not retain row values. |
| failure | Work exhaustion during traversal discards the Normalizer; invalid raw IDs are outside the bound-program contract. |
| cost | Two path walks; first charges visited non-root links, compression writes are uncharged. Union-by-rank plus compression controls amortized paths. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0020

[Lines 138–144](../../../../../src/frontend/normalize.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unite(std::size_t left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Merge two unconditional typed column-equality classes. |
| inputs / outputs | Two valid flattened column indices; no public output. |
| invariants | Union by rank preserves one representative and avoids changing an already equal class. |
| ownership | Mutates parent_/rank_ temporary metadata. |
| failure | root charges can fail; no program is published on failure. |
| cost | Two finds plus fixed rank/link work; no container allocation in the merge. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0021

[Lines 145–147](../../../../../src/frontend/normalize.cpp#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L147:sha256:286e989df147a66179934e7a956eb0ee162d6219828bbe2e2021b2f4c9ab6e58
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declares Normalizer’s expression, predicate, and occurrence-program passes; these methods build the normalized CQ and use the class work counter. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/code_specs/files/src/frontend/normalize.cpp.md](normalize.cpp.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0022

[Lines 148–153](../../../../../src/frontend/normalize.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableId variable(ScalarType type)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one classical variable with deterministic generated identity. |
| inputs / outputs | ScalarType to current vector-size VariableId, with vN label. |
| invariants | ID equals its insertion position and type remains exact at the core tag level. |
| ownership | Owns generated label and variable vector entry. |
| failure | Charge/label/vector allocation failures discard the temporary program. |
| cost | Integer formatting/label bytes and possible vector growth; one selected work charge. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0023

[Lines 154–164](../../../../../src/frontend/normalize.cpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L164:sha256:36a4ccc19b013c3696535943ee8345812259de69191a9b134dbb9c36cac98109
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declares Normalizer’s result object and scratch vectors/maps for expression dependencies, union-find classes, required outputs, and equal constants; result is retained output while the other members support the bounded pass. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/code_specs/files/src/frontend/normalize.cpp.md](normalize.cpp.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0024

[Lines 165–232](../../../../../src/frontend/normalize.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Normalizer::analyze_expressions()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate expression dependencies, representation and topological evaluation. |
| inputs / outputs | Owned binding to dependency sets, direct-column aliases and constant slots. |
| invariants | Children precede parents; column identity includes occurrence; inner USING depends on the left value while its mandatory predicate checks the right. |
| ownership | Allocates per-expression sets/vectors and owning constant copies. |
| failure | Malformed binding throws Error; selected work/expected outcomes use Failure; allocation propagates. |
| cost | Visits expressions, edges and inserted dependency memberships with ordered-set costs; folds constants using actual payload comparisons/copies. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0026

[Lines 234–268](../../../../../src/frontend/normalize.cpp#L234); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Normalizer::predicate(ExpressionId id)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify one unconditional predicate into core equality, local filter or contradiction. |
| inputs / outputs | Resolved Boolean expression ID; mutates classes, local predicates and constant/NULL guards. |
| invariants | Cross-occurrence predicates must be direct column equality; constant FALSE/UNKNOWN marks contradiction; occurrence identity is preserved. |
| ownership | Stores IDs and owning equality constants inside temporary metadata. |
| failure | Unsupported cross-relation predicate raises located Failure; malformed expression state raises Error. |
| cost | Dependency/class lookups, union-find paths and optional upper_bound over occurrence offsets; appends may allocate. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0028

[Lines 270–285](../../../../../src/frontend/normalize.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Normalizer::program(OccurrenceAdapter& adapter)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the local evaluation order needed by an occurrence adapter. |
| inputs / outputs | Local predicates/projections to sorted unique nonconstant ExpressionIds. |
| invariants | Every selected nonconstant dependency belongs to the adapter occurrence; ascending IDs give topological order; USING visits its first argument. |
| ownership | Temporary set/stack become an owning vector in the adapter. |
| failure | Work exhaustion and allocation abort normalization; nonlocal dependency is an internal Error. |
| cost | Visits reachable expression edges and ordered-set insertions; duplicate pending IDs can still be processed before deduplication. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0030

[Lines 287–417](../../../../../src/frontend/normalize.cpp#L287); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NormalizedSql Normalizer::run()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce specialized equality CQ, per-occurrence adapters and SQL mapping. |
| inputs / outputs | Owned bound query/options to a fully built NormalizedSql, moved on success. |
| invariants | Validates catalog, non-null source columns and concrete parameters; rejects row bags; flattens only top-level AND; schema2 grounds constants while v1 retains geometry. |
| ownership | Owns all new core/catalog/adapter/output state; source atoms and base routes remain distinct. |
| failure | Expected unsupported/resource/parameter outcomes throw Failure; malformed binding/validation/allocation errors propagate without partial publication. |
| cost | Full catalog validation, all referenced columns/expressions, DSU paths, ordered maps/sets, local-program reachability and copied payloads. Work counter is selected checkpoints, not total execution cost. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0031

[Lines 418–419](../../../../../src/frontend/normalize.cpp#L418); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L418-L419:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/code_specs/files/src/frontend/normalize.cpp.md](normalize.cpp.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md) |

## B0032

[Lines 420–427](../../../../../src/frontend/normalize.cpp#L420); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlNormalizeResult normalize_sql(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose normalization with typed expected diagnostics and explicit internal failures. |
| inputs / outputs | Coherent BoundSql and options to NormalizedSql or BindingDiagnostic. |
| invariants | Only schema1/2 supported; only Failure is translated; parameter errors use parameters phase, other expected rejections normalization. |
| ownership | Successful result owns its copied binding/specialization; diagnostics own text. |
| failure | Version Error precedes construction; internal Error, allocation and invalid-artifact failures are not swallowed by the Failure catch. |
| cost | Whole normalization cost, plus source-prefix diagnostic scan on expected rejection; no extra rollback wrapper. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0034

[Lines 429–451](../../../../../src/frontend/normalize.cpp#L429); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<Row> adapt_row(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Filter and project one physical row under a specialized occurrence program. |
| inputs / outputs | Valid NormalizedSql, occurrence ID and full physical Row to optional owning logical Row. |
| invariants | Validates the full base row; checks fixed/equal columns before evaluation; only TRUE predicates pass; no SQL NULL enters the core. |
| ownership | Borrows query/input while executing; copies the entire expression-constant vector and emitted cells into ordinary scratch/output. |
| failure | Invalid IDs/types/internal program throw; allocation failures propagate before any caller state publication. |
| cost | Full row validation, fixed/equality checks, a copy of all query.constants (including unused slots), local program and output payloads; not solely proportional to projected width. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0036

[Lines 453–466](../../../../../src/frontend/normalize.cpp#L453); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation map_sql_result(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct ordered/repeated/constant SQL row outputs or a Boolean EXISTS row. |
| inputs / outputs | Core set relation to independently owned SQL-facing set relation. |
| invariants | EXISTS always emits one Boolean row; row mapping checks core arity and preserves output positions before set deduplication. |
| ownership | Copies mapped cells into rows and the ordinary ordered relation; retains no core borrow. |
| failure | Invalid arity/positions and allocation failures propagate; no partial result escapes. |
| cost | EXISTS reads emptiness and constructs one set row; other mapping visits each output of each core row plus ordered-set comparison/insertion and payload copying. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/decisions/0006-sql-normalization.md](../../../../decisions/0006-sql-normalization.md), [docs/semantics.md](../../../../semantics.md) |

## B0037

[Lines 467–467](../../../../../src/frontend/normalize.cpp#L467); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L467-L467:sha256:2fc33ff8830b8cd06d6971e8e31b29a8803f152d87e09a3fc4092b3efecdac93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/code_specs/files/src/frontend/normalize.cpp.md](normalize.cpp.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md) |
