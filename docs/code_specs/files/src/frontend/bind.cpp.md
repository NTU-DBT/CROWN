# `src/frontend/bind.cpp` — block usage map

[Source](../../../../../src/frontend/bind.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Resolve table/column aliases, expressions and exact typed literals against catalog metadata.

Snapshot SHA-256: `b94a848e0bcf3a091ef2ff9747593fd99563ef7e0df9977cb689b668371f261b`. 608 lines partitioned into 51 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/frontend/bind.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../src/frontend/bind.cpp#L15) | Type/record definition: struct Failure |  · [reviewed contract](#b0002) |
| [B0003 · 16–18](../../../../../src/frontend/bind.cpp#L16) | Callable definition: \[\[noreturn\]\] void fail(std::string code, std::string message, std::optional&lt;std::size_t&gt; location = {}) | calls std::move · [reviewed contract](#b0003) |
| [B0004 · 19–31](../../../../../src/frontend/bind.cpp#L19) | Callable definition: SqlDiagnostic diagnostic(const Failure& failure, std::string_view source) | calls size, reset; returns result; result; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 32–42](../../../../../src/frontend/bind.cpp#L32) | Callable definition: SqlType sql_type(const Column& column) | calls ; returns {kind, column.nullable, column.decimal} · [reviewed contract](#b0005) |
| [B0006 · 43–43](../../../../../src/frontend/bind.cpp#L43) | Callable definition: bool integer_kind(SqlKind kind) | calls ; returns kind == SqlKind::int32 \|\| kind == SqlKind::int64 · [reviewed contract](#b0006) |
| [B0007 · 44–46](../../../../../src/frontend/bind.cpp#L44) | Callable definition: bool fits_int32(std::int64_t value) | calls min, max; returns value &gt;= std::numeric_limits&lt;std::int32_t&gt;::min() && value &lt;= std::numeric_limits&lt;std::int32_t&gt;::ma… · [reviewed contract](#b0007) |
| [B0008 · 47–52](../../../../../src/frontend/bind.cpp#L47) | Callable definition: std::optional&lt;std::int64_t&gt; integer_text(std::string_view text) | calls std::from_chars, data, size; returns {}; result · [reviewed contract](#b0008) |
| [B0009 · 53–53](../../../../../src/frontend/bind.cpp#L53) | Type/record definition: struct VisibleColumn |  · [reviewed contract](#b0009) |
| [B0010 · 54–57](../../../../../src/frontend/bind.cpp#L54) | Type/record definition: struct Scope |  · [reviewed contract](#b0010) |
| [B0011 · 58–59](../../../../../src/frontend/bind.cpp#L58) | declares types or opens a type body. |  · [reviewed contract](#b0011) |
| [B0012 · 60–67](../../../../../src/frontend/bind.cpp#L60) | Callable definition: public: Binder(const SqlSyntax& syntax, const Catalog& catalog, const BindOptions& options) : syntax_(syntax) | calls syntax_, push_back, sql_type; growth push_back; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 68–68](../../../../../src/frontend/bind.cpp#L68) | declares callable signatures. |  · [reviewed contract](#b0013) |
| [B0014 · 69–81](../../../../../src/frontend/bind.cpp#L69) | Type/record definition: private: class Frame |  · [reviewed contract](#b0014) |
| [B0015 · 82–83](../../../../../src/frontend/bind.cpp#L82) | Explanatory comments or spacing. | source comment (unverified): // Count selected binding checkpoints. Catalog validation, string work and · [reviewed contract](#b0015) |
| [B0016 · 84–88](../../../../../src/frontend/bind.cpp#L84) | Callable definition: void charge() | calls max, fail; source comment (unverified): // Count selected binding checkpoints. Catalog validation, string work and · [reviewed contract](#b0016) |
| [B0017 · 89–96](../../../../../src/frontend/bind.cpp#L89) | Callable definition: std::optional&lt;std::size_t&gt; location(const Json& node) const | calls is_object, contains, at, size; returns {}; {} · [reviewed contract](#b0017) |
| [B0018 · 97–104](../../../../../src/frontend/bind.cpp#L97) | Callable definition: void keys(const Json& node, std::initializer_list&lt;std::string_view&gt; allowed) | calls charge, is_object, fail, items; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 105–108](../../../../../src/frontend/bind.cpp#L105) | Callable definition: const Json& tagged(const Json& node, std::string_view name) const | calls is_object, size, contains, at; returns node.at(name) · [reviewed contract](#b0019) |
| [B0020 · 109–109](../../../../../src/frontend/bind.cpp#L109) | Callable definition: std::string identifier(const Json& node) const | calls tagged, value; returns tagged(node, @ ).value(@ , std::string{}) · [reviewed contract](#b0020) |
| [B0021 · 110–116](../../../../../src/frontend/bind.cpp#L110) | Callable definition: ExpressionId append(SqlType type, BoundNode node, std::optional&lt;std::size_t&gt; where) | calls charge, size, fail, push_back; returns id; growth push_back · [reviewed contract](#b0021) |
| [B0022 · 117–117](../../../../../src/frontend/bind.cpp#L117) | Callable definition: const BoundExpression& expression(ExpressionId id) const | calls ; returns result_.expressions\[id.value\] · [reviewed contract](#b0022) |
| [B0023 · 118–120](../../../../../src/frontend/bind.cpp#L118) | Callable definition: ExpressionId operation(SqlOperator op, std::vector&lt;ExpressionId&gt; arguments, SqlType type, std::optional&lt;std::size_t&gt; where) | calls append, std::move; returns append(type, BoundOperation{op, std::move(arguments)}, where) · [reviewed contract](#b0023) |
| [B0024 · 121–129](../../../../../src/frontend/bind.cpp#L121) | Callable definition: void resolve_unknown(ExpressionId id, SqlType target) | calls fail, has_value · [reviewed contract](#b0024) |
| [B0025 · 130–134](../../../../../src/frontend/bind.cpp#L130) | Callable definition: ExpressionId boolean(ExpressionId id) | calls resolve_unknown, expression, fail; returns id · [reviewed contract](#b0025) |
| [B0026 · 135–136](../../../../../src/frontend/bind.cpp#L135) | Explanatory comments or spacing. | source comment (unverified): // Comparisons require compatible kinds; same-kind decimals may retain · [reviewed contract](#b0026) |
| [B0027 · 137–151](../../../../../src/frontend/bind.cpp#L137) | Callable definition: void comparable(ExpressionId& left, ExpressionId& right, std::optional&lt;std::size_t&gt; where) | calls expression, resolve_unknown, integer_kind, operation; source comment (unverified): // Comparisons require compatible kinds; same-kind decimals may retain · [reviewed contract](#b0027) |
| [B0028 · 152–156](../../../../../src/frontend/bind.cpp#L152) | Callable definition: ExpressionId comparison(SqlOperator op, ExpressionId left, ExpressionId right, std::optional&lt;std::size_t&gt; where) | calls comparable, expression, operation; returns operation(op, {left,right}, {SqlKind::boolean, nullable, {}}, where) · [reviewed contract](#b0028) |
| [B0029 · 157–175](../../../../../src/frontend/bind.cpp#L157) | Callable definition: ExpressionId literal(const Json& node) | calls keys, location, value, append; returns append({SqlKind::unknown,true,{}}, BoundLiteral{{}}, where); append({fits_int32(value) ? SqlKind::i… · [reviewed contract](#b0029) |
| [B0030 · 176–206](../../../../../src/frontend/bind.cpp#L176) | Callable definition: SqlType cast_type(const Json& node) | calls keys, location, at, empty; returns target · [reviewed contract](#b0030) |
| [B0031 · 207–242](../../../../../src/frontend/bind.cpp#L207) | Callable definition: ExpressionId cast(const Json& node, const Scope& scope) | calls keys, cast_type, at, location; returns operation(SqlOperator::literal_cast, {argument}, target, where); operation(SqlOperator::identity_ca…; source comment (unverified): // Validate and retag a literal leaf before retaining its explicit cast node. · [reviewed contract](#b0031) |
| [B0032 · 243–271](../../../../../src/frontend/bind.cpp#L243) | Callable definition: ExpressionId lookup(const Scope& scope, std::optional&lt;std::string&gt; qualifier, const std::string& name, std::optional&lt;std::size_t&gt;… | calls find, end, fail, charge; returns *qualifier + @ + name; alias + @ + name; 3 loop sites · [reviewed contract](#b0032) |
| [B0033 · 272–347](../../../../../src/frontend/bind.cpp#L272) | Callable definition: ExpressionId bind_expression(const Json& node, const Scope& scope) | calls frame, charge, is_object, size; returns append(definition.type,definition.node,where); literal(value); growth push_back; 2 loop sites · [reviewed contract](#b0033) |
| [B0034 · 348–357](../../../../../src/frontend/bind.cpp#L348) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0034) |
| [B0035 · 358–365](../../../../../src/frontend/bind.cpp#L358) | Callable definition: Scope Binder::merge(Scope left, Scope right, std::optional&lt;std::size_t&gt; where) | calls charge, emplace, std::move, fail; returns left; growth emplace, insert; 1 loop sites · [reviewed contract](#b0035) |
| [B0036 · 366–366](../../../../../src/frontend/bind.cpp#L366) | Explanatory comments or spacing. |  |
| [B0037 · 367–379](../../../../../src/frontend/bind.cpp#L367) | Callable definition: Scope Binder::alias_scope(Scope scope, const Json& alias, std::optional&lt;std::size_t&gt; where) | calls keys, at, empty, fail; returns scope; growth emplace; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 380–380](../../../../../src/frontend/bind.cpp#L380) | Explanatory comments or spacing. |  |
| [B0039 · 381–460](../../../../../src/frontend/bind.cpp#L381) | Callable definition: Scope Binder::from(const Json& node) | calls frame, charge, is_object, size; returns scope; combined; growth emplace, insert, push_back; 8 loop sites; source comment (unverified): // An INNER equality can be TRUE only for two non-NULL values. · [reviewed contract](#b0039) |
| [B0040 · 461–461](../../../../../src/frontend/bind.cpp#L461) | Explanatory comments or spacing. |  |
| [B0041 · 462–474](../../../../../src/frontend/bind.cpp#L462) | Callable definition: std::string Binder::output_name(const Json& node) const | calls contains, at, empty, back; returns identifier(names.back()); output_name(*underlying); 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 475–475](../../../../../src/frontend/bind.cpp#L475) | Explanatory comments or spacing. |  |
| [B0043 · 476–518](../../../../../src/frontend/bind.cpp#L476) | Callable definition: void Binder::select(const Json& node) | calls frame, keys, value, fail; growth push_back; 3 loop sites; source comment (unverified): // PostgreSQL permits nullary SELECT. · [reviewed contract](#b0043) |
| [B0044 · 519–519](../../../../../src/frontend/bind.cpp#L519) | Explanatory comments or spacing. |  |
| [B0045 · 520–547](../../../../../src/frontend/bind.cpp#L520) | Callable definition: BoundSql Binder::run() | calls at, contains, fail, size; returns std::move(result_); std::move(result_); source comment (unverified): // Only a whole-result EXISTS wrapper is supported, with no outer FROM or · [reviewed contract](#b0045) |
| [B0046 · 548–549](../../../../../src/frontend/bind.cpp#L548) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0046) |
| [B0047 · 550–568](../../../../../src/frontend/bind.cpp#L550) | Callable definition: SqlBindResult bind_sql(std::string_view source, const Catalog& catalog, const BindOptions& options) | calls parse_sql, catalog::validate_catalog, code, what; returns BindingDiagnostic{@ ,*failure}; BindingDiagnostic{@ ,{error.code(),error.what(),{},{},{},{}}}; growth push_back; 1 loop sites; source comment (unverified): // These handlers cover Binder construction/run. Parsing and declaration · [reviewed contract](#b0047) |
| [B0048 · 569–569](../../../../../src/frontend/bind.cpp#L569) | Explanatory comments or spacing. |  |
| [B0049 · 570–581](../../../../../src/frontend/bind.cpp#L570) | Callable definition: std::string sql_kind_name(SqlKind kind) | calls Error; returns @; @ · [reviewed contract](#b0049) |
| [B0050 · 582–607](../../../../../src/frontend/bind.cpp#L582) | Callable definition: std::string sql_operator_name(SqlOperator op) | calls Error; returns @; @ · [reviewed contract](#b0050) |
| [B0051 · 608–608](../../../../../src/frontend/bind.cpp#L608) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend · [reviewed contract](#b0051) |

## B0001

[Lines 1–14](../../../../../src/frontend/bind.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:c21217f245b1d85faf6a3a017aee9af0c8f430fcaf916038e5886ac0c6f547fb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/frontend/bind.hpp, crown/api/error.hpp, crown/catalog/catalog.hpp, algorithm, charconv, limits) and opens crown::frontend scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [docs/code_specs/files/src/frontend/bind.cpp.md](bind.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0002

[Lines 15–15](../../../../../src/frontend/bind.cpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Failure {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry an internal binder rejection to the public binding boundary without exposing partial state. |
| inputs / outputs | Owns diagnostic code/message plus optional source byte location; fail and one Boolean-tag branch throw this exact payload. |
| invariants | This local type is not crown::Error or std::exception. Its location may be absent and diagnostic later checks it against source length. |
| ownership | Exception payload owns its strings and numeric optional; it holds no references to AST or Binder state. |
| failure | Caught specifically by bind_sql and converted to a binding-phase diagnostic; allocating its strings may throw separately. |
| cost | O(code/message bytes) storage and construction; exception unwinding cost depends on active binding depth. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0003

[Lines 16–18](../../../../../src/frontend/bind.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void fail(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop binding with a classified owning rejection and optional source location. |
| inputs / outputs | Takes code/message by value and optional byte offset, then throws Failure after moving the strings. |
| invariants | Never returns and does not construct a successful or partial BoundSql; classification/offset are supplied by the rejecting caller. |
| ownership | Moves caller-provided strings into the thrown payload; Binder local containers unwind normally. |
| failure | Always throws Failure; allocation while preparing arguments or exception storage may instead propagate another allocation failure. |
| cost | Constant payload-transfer work after argument creation, plus exception allocation/unwinding; not a normal successful-path branch. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0004

[Lines 19–31](../../../../../src/frontend/bind.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlDiagnostic diagnostic(const Failure& failure, std::string_view source) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate a binder byte location to the parser-compatible one-based UTF-8 coordinates. |
| inputs / outputs | Copies Failure code/message and location into SqlDiagnostic; scans the source prefix only for an offset in \[0,source.size()\]. |
| invariants | Absent/out-of-range offsets yield all coordinates absent. Offset zero and end-of-input are valid. Continuation bytes do not increment character/column counts; newline resets column to one. Source is assumed parser-validated UTF-8. |
| ownership | Borrows failure/source for the call and returns owning diagnostic strings; no source view escapes. |
| failure | No semantic failure on a missing location; string copies can allocate and throw, including while handling another failure. |
| cost | O(offset) byte scan on located rejection, O(code/message bytes) copy; constant coordinate state and no source-sized temporary. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp) |

## B0005

[Lines 32–42](../../../../../src/frontend/bind.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlType sql_type(const Column& column) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map validated catalog/parameter scalar metadata into a SQL expression type. |
| inputs / outputs | Maps ScalarType int64/string/boolean/date/decimal to SqlKind and copies nullable/decimal metadata. |
| invariants | Catalog integers stay int64; int32 is introduced only by SQL literals/casts. Caller validation establishes valid ScalarType and decimal specification; an invalid enum would fall through to unknown. |
| ownership | Borrows Column and returns independent inline metadata; no name/collation string is retained. |
| failure | No throw or validation in this helper; bind_sql catalog/parameter validation is the required prior boundary. |
| cost | Constant switch work and fixed-size metadata copy; no allocation. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp) |

## B0006

[Lines 43–43](../../../../../src/frontend/bind.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool integer_kind(SqlKind kind) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize the two SQL integer widths for explicit widening and literal-cast validation. |
| inputs / outputs | Returns true exactly for int32 or int64, false for all other enum values. |
| invariants | Kind recognition neither changes width nor converts a Value; catalog/core Value representation remains int64. |
| ownership | Takes and returns scalar values with no ownership transfer. |
| failure | No diagnostic or exception. |
| cost | Two enum comparisons, constant work and no allocation. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0007

[Lines 44–46](../../../../../src/frontend/bind.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool fits_int32(std::int64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify a stored int64 value by the signed int32 domain without narrowing it. |
| inputs / outputs | Returns whether min(int32) &lt;= value &lt;= max(int32), used for literal width and checked integer casts. |
| invariants | Inclusive boundaries preserve exact representability; no arithmetic overflow or floating-point conversion occurs. |
| ownership | All arguments/results are scalar values. |
| failure | No diagnostic or exception. |
| cost | Two integer comparisons, constant work and no allocation. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0008

[Lines 47–52](../../../../../src/frontend/bind.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::int64_t> integer_text(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one complete signed int64 text representation without locale or floating point. |
| inputs / outputs | Uses from_chars over the entire borrowed view; returns an engaged number only when parsing succeeds and consumes every byte. |
| invariants | Rejects overflow, empty/partial text, whitespace and leading plus according to signed integer from_chars syntax; a leading minus is accepted. Failure is distinct from numeric zero. |
| ownership | Borrows text only during parsing and returns an inline optional value. |
| failure | Conversion failure returns an empty optional rather than throwing a semantic diagnostic; callers select unsupported_type/unsupported_cast or decimal parsing. |
| cost | O(text bytes) conversion, constant temporary space and no allocation. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0009

[Lines 53–53](../../../../../src/frontend/bind.cpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct VisibleColumn {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Associate one SQL-visible name with the existing expression that defines that scope column. |
| inputs / outputs | Owns a name and stores ExpressionId; scopes use these entries for unqualified, qualified and wildcard references. |
| invariants | Several entries may have the same name, including alias prefix renames; scalar lookup rejects ambiguity while star expansion preserves duplicates. Names need not equal physical catalog column names. |
| ownership | Owns name text and a numeric link into Binder.result_.expressions; it does not own or retain that expression. |
| failure | No validation in the aggregate; name copies or vector growth may allocate and throw. |
| cost | O(name bytes) owned storage/copy and constant ID storage. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0010

[Lines 54–57](../../../../../src/frontend/bind.cpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Scope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the ordered unqualified join view separate from each visible relation qualifier. |
| inputs / outputs | columns drives unqualified lookup and star order; a std::map owns qualifier-to-column-vector views for alias.column and alias.*. |
| invariants | USING/NATURAL merge only columns while original qualifier views retain physical inputs. Whole-join aliases replace qualifier visibility; USING aliases add a merged-key view. No enclosing comma scope is injected into an ON input. |
| ownership | Owns duplicated VisibleColumn names/vectors and qualifier strings; all entries reference Binder-owned expressions by value ID. |
| failure | The aggregate imposes no uniqueness check; merge/alias/from enforce qualifier rules. Container copy/allocation may fail. |
| cost | Storage includes both unqualified entries and all qualifier views, so column names may be duplicated. Copying is proportional to all stored names/entries; qualifier lookup is logarithmic in qualifier count plus string-comparison cost. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp) |

## B0011

[Lines 58–59](../../../../../src/frontend/bind.cpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L59:sha256:3161fe0db1c339a75bd958ca294307bb3c284880e4c66e127d1cc030bc4ff6a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begins the private Binder class that resolves a parsed SQL syntax tree against catalog and binding options; methods and state are declared in following class blocks. |
| inputs / outputs | This span declares a helper type and its member layout; it does not call its operations. Member signatures and constructors in the enclosing file define the actual input/output boundary. |
| invariants | The type is an implementation detail at this scope; callers must use its neighboring validated factory/owner path rather than treat the declaration as a proof. |
| ownership | Construction initializes declared members according to their types; ownership follows each member type, with no extra owner introduced by the class declaration. |
| failure | The declaration itself does not translate runtime errors; construction and member operations may fail according to their definitions and allocation sources. |
| cost | No per-call cost is incurred by the declaration. Object construction/member operations may allocate or traverse according to their concrete member types and definitions. |
| Design | [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [docs/code_specs/files/src/frontend/bind.cpp.md](bind.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0012

[Lines 60–67](../../../../../src/frontend/bind.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Binder(const SqlSyntax& syntax, const Catalog& catalog, const BindOptions& options)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a private owning result while borrowing the parser-owned syntax for the binding pass. |
| inputs / outputs | Copies syntax.source and the complete Catalog into result_, copies limits and appends mapped SqlTypes for every parameter declaration. |
| invariants | Public bind_sql validates catalog/parameter metadata first. No source/catalog references escape in the result; the borrowed syntax must remain alive through run. |
| ownership | syntax_ is a call-local borrow; result_ owns source, catalog and signature. Constructor failure destroys any partially initialized result. |
| failure | Copies/vector growth can throw bad_alloc or other standard container exceptions; construction occurs inside bind_sql's Binder catch boundary. |
| cost | O(source bytes + catalog metadata bytes + parameter count) copying and multiple container/string allocations; these costs are not charged by Binder::charge and no rows are read. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp) |

## B0013

[Lines 68–68](../../../../../src/frontend/bind.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L68:sha256:e3e3bc70ef432a7a9462a6fb0ec8c385c52ffaf707e790a81e5fe89837560a5b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declares Binder::run as the private compilation entry point returning the completed BoundSql; the out-of-line definition later performs binding and may raise the binder’s internal Failure. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [docs/code_specs/files/src/frontend/bind.cpp.md](bind.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0014

[Lines 69–81](../../../../../src/frontend/bind.cpp#L69); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Frame {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound and restore active recursive binding depth with RAII. |
| inputs / outputs | Construction borrows Binder, rejects depth &gt;= recursion_limit, then increments depth; destruction decrements it. Copy/assignment are deleted. |
| invariants | Only successfully constructed frames decrement, including exception unwinding. select, from and bind_expression share the same active-depth counter; this measures nested binder calls rather than raw JSON depth. |
| ownership | Nonowning Binder reference is valid for the frame's lexical lifetime; no heap storage or transferred ownership. |
| failure | Construction throws Failure(resource_limit) before increment on exhaustion. Destructor only decrements and introduces no failure path. |
| cost | Constant work and stack-sized state per active call; O(active depth) frame memory overall. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp) |

## B0015

[Lines 82–83](../../../../../src/frontend/bind.cpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L83:sha256:14faf33364914782b917d1a60849a653cf3b994a27a5927d83fe96dce17ba94b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Count selected binding checkpoints. Catalog validation, string work and container allocation/copy costs are not all represented by this counter. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/frontend/bind.cpp lines 80-85; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [docs/code_specs/files/src/frontend/bind.cpp.md](bind.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0016

[Lines 84–88](../../../../../src/frontend/bind.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count selected binder work checkpoints without allowing counter wrap or a configured threshold overrun. |
| inputs / outputs | Reads result_.limits.work_limit and result_.work; increments exactly once on success. |
| invariants | Configured zero rejects the first charge; absent configured bound still rejects uint64 maximum. Checks precede increment. It does not account for every loop, metadata validation, string/container operation or byte allocation. |
| ownership | Mutates only the private result work counter. |
| failure | Throws Failure(resource_limit) with no location before modifying work on overflow/limit exhaustion; partial result is discarded by the public boundary. |
| cost | Constant work and no successful-path allocation; error construction/unwinding may allocate. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0017

[Lines 89–96](../../../../../src/frontend/bind.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::size_t> location(const Json& node) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an optional AST byte location and reject offsets beyond the owned SQL source. |
| inputs / outputs | Nonobjects, omitted location or negative int64 location yield no location; an in-range nonnegative location becomes size_t, including source.size(). |
| invariants | Locations are source bytes, not character positions. Parser supplies the AST and valid UTF-8 source; this helper does not validate code-point boundaries. |
| ownership | Borrows JSON and syntax source; returns numeric optional data only. |
| failure | Out-of-source offset throws Failure(invalid_ast); incompatible JSON value conversions throw Json::exception for the public invalid_ast handler. |
| cost | Constant-size conversion plus JSON member lookups (logarithmic in object field count for the default ordered JSON object); no explicit allocation on success. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0018

[Lines 97–104](../../../../../src/frontend/bind.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void keys(const Json& node, std::initializer_list<std::string_view> allowed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject AST fields that would otherwise be silently ignored at a supported binding node. |
| inputs / outputs | Charges one work step, requires an object, then checks each key against the supplied fixed allowlist. |
| invariants | Allowed keys need not all be present and value shapes are checked by later reads; unknown fields fail in JSON object iteration order. This is a supported-field guard, not a complete AST schema validator. |
| ownership | Borrows the node and call-local allowlist; no persistent state except the work counter. |
| failure | Nonobject yields invalid_ast, unknown key yields unsupported_sql with location(node); bad location/JSON type errors may precede that final rejection. |
| cost | O(field count × allowlist count) string-view comparisons, plus member lookups for a failure location; allowlists are small and no success container allocation is introduced. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0019

[Lines 105–108](../../../../../src/frontend/bind.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Json& tagged(const Json& node, std::string_view name) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one named AST wrapper whose payload is an object, and borrow that payload. |
| inputs / outputs | Accepts an object with exactly one field equal to name and object-valued content; returns node.at(name). |
| invariants | Rejects extra wrapper members, a different tag and nonobject payloads; it does not check payload keys or semantic content. |
| ownership | Returns a const reference into the supplied AST; it is valid only while that JSON subtree remains alive and unchanged. |
| failure | Shape mismatch throws Failure(invalid_ast) without a location; JSON member operations can throw JSON exceptions for unexpected upstream representations. |
| cost | Fixed number of JSON object checks/lookups, logarithmic in field count; no success-path payload copy. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0020

[Lines 109–109](../../../../../src/frontend/bind.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string identifier(const Json& node) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract the parser-folded or quoted identifier text from a String wrapper. |
| inputs / outputs | Calls tagged(node,"String") and returns its string sval, defaulting to an empty string when the field is absent. |
| invariants | Does not perform case folding, schema lookup, key validation or nonempty-name checks; PostgreSQL parsing and the consuming context supply those rules. |
| ownership | Returns an owning string copied from AST data; the AST remains borrowed. |
| failure | Bad wrapper produces invalid_ast; an incompatible sval JSON type raises Json::exception and string allocation may fail. |
| cost | O(identifier bytes) copy/allocation plus wrapper/member lookup; no table lookup occurs here. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0021

[Lines 110–116](../../../../../src/frontend/bind.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpressionId append(SqlType type, BoundNode node, std::optional<std::size_t> where) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one fully owned expression and assign its dense result-local ID. |
| inputs / outputs | Charges work, rejects expressions.size() &gt;= expression_limit, then pushes type, moved node and location and returns the former size. |
| invariants | Limit check precedes vector mutation, but charging happens before the expression-limit check. Child IDs must already be valid/topological; append does not inspect them. Reallocation invalidates expression references. |
| ownership | Takes node by value and moves it into result_.expressions; caller argument construction/copying may occur before the check. |
| failure | Throws Failure(resource_limit) at either checked bound; vector/payload allocation failures unwind to bind_sql. No partially built result is exposed. |
| cost | Amortized constant vector insertion in element count, with potentially linear payload copies/moves on capacity growth; owns the new literal bytes or argument vector and may allocate. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp) |

## B0022

[Lines 117–117](../../../../../src/frontend/bind.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const BoundExpression& expression(ExpressionId id) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an existing private result expression by its trusted local ID. |
| inputs / outputs | Returns result_.expressions\[id.value\] using unchecked vector subscripting. |
| invariants | Caller must supply an in-range ID from this Binder. The reference must not be retained across append/operation that can grow the expression vector. |
| ownership | Returns a nonowning const reference; the Binder owns the expression and may relocate it. |
| failure | No diagnostic or bounds check; invalid IDs violate the helper precondition and can cause undefined behavior. |
| cost | Constant indexed access, no allocation, no work charge. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0023

[Lines 118–120](../../../../../src/frontend/bind.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpressionId operation(SqlOperator op, std::vector<ExpressionId> arguments, SqlType type, std::optional<std::size_t> where) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append an operation node with an already determined SQL result type and argument list. |
| inputs / outputs | Takes operator, owned argument vector, type and location; moves arguments into BoundOperation and delegates to append. |
| invariants | Does not infer type or check operator arity; comparison/Boolean/cast/join callers establish these. Child IDs precede the appended operation in generated bindings. |
| ownership | Transfers the argument vector into the result expression; children remain ID references, not copied subtrees. |
| failure | append enforces work/expression limits; argument vector creation before this call and expression growth can allocate and fail. |
| cost | Constant wrapper work plus append cost; O(argument count) owned vector storage supplied by the caller, typically allocated for nonempty initializer lists. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp) |

## B0024

[Lines 121–129](../../../../../src/frontend/bind.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void resolve_unknown(ExpressionId id, SqlType target) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve an unknown literal to an allowed contextual type in place. |
| inputs / outputs | For an already known expression this is a no-op; otherwise requires BoundLiteral, rejects a non-NULL literal unless target kind is string, then assigns target with literal-derived nullability. |
| invariants | SQL NULL can adopt the contextual kind/decimal specification. An unknown non-NULL string never acquires integer/date/bool/decimal by implicit parsing. No new expression is appended. |
| ownership | Mutates the Binder-owned expression type only; literal payload remains owned and unchanged. |
| failure | Unknown nonliteral yields invalid_ast; a non-NULL string targeting a nonstring kind yields unsupported_implicit_cast at the original literal location. Trusted ID access is unchecked. |
| cost | Constant variant/type work and no allocation on success; no work checkpoint is charged here. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0025

[Lines 130–134](../../../../../src/frontend/bind.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpressionId boolean(ExpressionId id) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a Boolean expression for WHERE, ON or Boolean operators/tests. |
| inputs / outputs | First resolves unknown to nullable Boolean, then requires kind boolean and returns the same ID. |
| invariants | NULL may become Boolean NULL; a non-NULL untyped string is rejected by resolve_unknown rather than truth-parsed. Existing nullable Boolean expressions remain nullable. |
| ownership | Mutates an unknown literal's type through resolve_unknown and returns its value ID; no new node or borrowed reference escapes. |
| failure | resolve_unknown can reject implicit string conversion; a known non-Boolean yields type_mismatch at that expression's location. |
| cost | Constant checks and no success allocation or added work charge. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0026

[Lines 135–136](../../../../../src/frontend/bind.cpp#L135); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L136:sha256:3594292a01c8e2d1e26c669c3d607dedb4c6989a68cca3b58276f0ef8de46503
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Comparisons require compatible kinds; same-kind decimals may retain different declared precision/scale. Only integer width widening adds a node. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/frontend/bind.cpp lines 133-138; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [docs/code_specs/files/src/frontend/bind.cpp.md](bind.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0027

[Lines 137–151](../../../../../src/frontend/bind.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void comparable(ExpressionId& left, ExpressionId& right, std::optional<std::size_t> where) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve comparison operand kinds and make permitted integer width promotion explicit. |
| inputs / outputs | Takes operand IDs by reference; resolves unknowns against their counterpart (both unknown become string) and may replace one int32 ID with an appended widen_integer ID. |
| invariants | Only int32-to-int64 widening is implicit. Different noninteger kinds reject. Equal decimal kinds may carry different fixed specs without a cast; NULL resolution inherits the counterpart type. Operand nullability is retained. |
| ownership | Mutates unknown expression metadata and caller IDs; any widening node/vector becomes result-owned. It copies types before appending to avoid keeping expression references across growth. |
| failure | Unsupported string resolution or mismatched kinds yields unsupported_implicit_cast; widening can fail work/expression/allocation bounds. Intermediate private mutations are discarded on rejected binding. |
| cost | Constant checks plus at most one widening append/vector allocation; diagnostic kind-name/message construction allocates only on mismatch. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp) |

## B0028

[Lines 152–156](../../../../../src/frontend/bind.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpressionId comparison(SqlOperator op, ExpressionId left, ExpressionId right, std::optional<std::size_t> where) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append a nullable SQL Boolean comparison after compatible operand resolution. |
| inputs / outputs | Copies operand IDs, invokes comparable, ORs their nullable flags and emits op(left,right) with Boolean SqlType. |
| invariants | Caller supplies a comparison tag; this helper does not validate the tag. NULL-capable operands produce nullable comparison type; no Boolean value evaluation or equality-class merging occurs here. |
| ownership | Owns the appended two-ID argument vector in the result; operands remain result-local IDs. |
| failure | Compatibility errors and append resource/allocation failures propagate to the public binding boundary. |
| cost | Constant compatibility/type work plus optional widening and one comparison append; typically one or two small argument-vector allocations and possible expression-vector growth. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp) |

## B0029

[Lines 157–175](../../../../../src/frontend/bind.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpressionId literal(const Json& node) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the supported PostgreSQL A_Const payloads into exact scalar or SQL-NULL expressions. |
| inputs / outputs | Checks allowed fields; handles NULL, integer payloads, textual numeric payloads, strings and booleans. Integers are classified int32/int64; strings start unknown and NULL starts unknown/nullable. |
| invariants | Textual numeric input first attempts complete int64 parsing; a failed token without .eE is rejected as outside int64 rather than silently becoming decimal. Other numeric text goes to exact Decimal::parse, which rejects exponent and missing-side decimal notation. No floating point conversion is used. |
| ownership | New literal expression owns copied string/Decimal payloads; JSON is borrowed. Decimal errors are translated to Failure at the literal location. |
| failure | Unsupported shapes yield unsupported_literal, oversized integer text unsupported_type, scalar parsing retains invalid_scalar/scalar_overflow. JSON errors and allocation failures reach the public catch boundary; the local Error catch preserves scalar code/message/location. |
| cost | O(text bytes) numeric/string work and owned payload copy, plus append; Decimal stores at most 38 significant coefficient digits but parsing can scan the full token. The field/append checkpoints do not charge per byte. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [docs/scalars.md](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0030

[Lines 176–206](../../../../../src/frontend/bind.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlType cast_type(const Json& node) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize the bounded explicit cast type names and optional exact decimal precision/scale. |
| inputs / outputs | Accepts an unqualified name or pg_catalog.name for int8/bigint, int4/integer, text, bool/boolean, date, numeric/decimal; returns SqlType, optionally with decimal(p\[,s\]). |
| invariants | Only decimal accepts one or two literal integer typmods, with 1&lt;=p&lt;=38 and 0&lt;=s&lt;=p; omitted scale is zero. typemod is allowed in the AST key set but not interpreted. Nullability is set later from the argument. |
| ownership | Borrows AST, copies identifier strings and returns inline type metadata. |
| failure | Unsupported name/qualification/decimal range yields unsupported_type; bad modifier form yields unsupported_cast; missing/wrong JSON shape can yield invalid_ast through Json::exception. |
| cost | A bounded number of name/modifier checks and JSON lookups plus O(type-name bytes) copies; no scan of catalog or source data. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0031

[Lines 207–242](../../../../../src/frontend/bind.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpressionId cast(const Json& node, const Scope& scope) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind explicit literal validation or a full-type identity cast without erasing the cast node. |
| inputs / outputs | Resolves target type before binding the argument, inherits its nullability, mutates a literal payload/type when exactly representable, then appends literal_cast; nonliteral arguments require equal SqlType and append identity_cast. |
| invariants | String-to-text/date/decimal/int32/int64 and integer-to-integer exact casts are supported, plus same-kind bool/date/decimal literals and NULL to a supported target. String-to-Boolean, integer-to-decimal/text and representation-changing nonliteral casts reject. Fixed decimal casts must fit without rounding; an already-cast expression is nonliteral for further conversions. |
| ownership | Borrows scope/AST; copies the original literal Value before conversion, replaces the result-owned literal, then owns one cast argument vector. The reference to the literal is not used after the final append. |
| failure | unsupported_cast classifies unsupported/inexact conversions; Date/Decimal/catalog Error codes are retained at cast/type location by the local catch. JSON, work/expression and allocation failures propagate; private literal mutation is never returned on failure. |
| cost | Recursive argument-binding cost plus O(literal text bytes) copying/parsing and decimal fit formatting, then one operation append; can allocate multiple copies of a string/Decimal and a small argument vector. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [docs/scalars.md](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0032

[Lines 243–271](../../../../../src/frontend/bind.cpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpressionId lookup(const Scope& scope, std::optional<std::string> qualifier, const std::string& name, std::optional<std::size_t> where) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve exactly one visible column and produce candidate-specific unknown/ambiguity diagnostics. |
| inputs / outputs | Selects a qualifier vector or the ordered unqualified columns, scans for name matches and returns the existing defining expression ID. |
| invariants | Qualified lookup never falls back to unqualified names. A second matching entry is ambiguous even if its expression ID matches. For unqualified first matches, candidate description eagerly scans qualifier views; a merged key with no qualifying view is described as a merged JOIN column. |
| ownership | Borrows Scope and name; owns local diagnostic candidate strings and any optional qualifier copy, returning only a value ID. |
| failure | Reports unknown_qualifier, unknown_column or ambiguous_column at the supplied offset. Scanned entries and diagnostic candidate entries charge work and may cause resource_limit before the name diagnostic. |
| cost | O(selected column entries + all qualifier-view entries) visits in the worst case, including eager diagnostic description on successful unqualified lookup; qualifier selection adds logarithmic map lookup and string comparisons. Candidate text can allocate on success. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp) |

## B0033

[Lines 272–347](../../../../../src/frontend/bind.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpressionId bind_expression(const Json& node, const Scope& scope) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recursively bind the finite scalar/Boolean SQL expression subset into typed topological nodes. |
| inputs / outputs | Handles one-tag ColumnRef, A_Const, ParamRef, TypeCast, binary scalar A_Expr comparisons, AND/OR/NOT, scalar NullTest and BooleanTest. Returns a new or delegated expression ID. |
| invariants | Only column or alias.column references are allowed; wildcards are target-only. Supported comparisons are =, &lt;&gt;, !=, &lt;, &lt;=, &gt;, &gt;=, optionally pg_catalog-qualified. Parameters require declared types. AND/OR require nonempty arguments; NOT requires one. NULL/Boolean IS tests produce non-null Boolean type; Boolean operands use nullable SQL typing. |
| ownership | Borrows AST/scope, creates result-owned nodes/vectors and copies a selected column definition for use-site location. Fixed operator recognition stores only an enum and short-lived extracted name; no lookup-map nodes are constructed. |
| failure | Unknown expression/operator/qualification, missing parameter, wrong Boolean type, row NULL test and bad arity reject explicitly. Scalar operator recognition precedes child binding; BooleanTest binds and checks its Boolean argument before extracting/selecting the truth test. Frame/charge/append can stop resources; malformed JSON is translated by the public boundary. |
| cost | Recursive AST traversal plus scope lookup/cast/literal costs, O(arity) argument vectors and O(active depth) stack. Scalar and Boolean-test spellings use fixed short branch chains without per-expression lookup-map construction; real AST/container/payload allocations remain. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp) |

## B0034

[Lines 348–357](../../../../../src/frontend/bind.cpp#L348); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L348-L357:sha256:b9907eea172725758f2f3d649fb81795c07fb2622af35bb22a1c819166a3b277
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declares Binder’s remaining scope/source/select helpers and its borrowed SqlSyntax reference, owned BoundSql result, and recursion depth; the class closes at the end of this block. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [docs/code_specs/files/src/frontend/bind.cpp.md](bind.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0035

[Lines 358–365](../../../../../src/frontend/bind.cpp#L358); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scope Binder::merge(Scope left, Scope right, std::optional<std::size_t> where) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine disjoint visible relation qualifiers and concatenate ordered unqualified columns. |
| inputs / outputs | Takes two scopes by value, inserts every right qualifier into left with one charge each, copies right columns after left columns, and returns the combined scope. |
| invariants | Duplicate qualifier names fail rather than overwrite; duplicate column names remain visible for later ambiguity checks. It does not merge USING columns or expose preceding comma inputs inside a separately built ON scope. |
| ownership | Owns incoming scope values, moves qualifier vectors, copies qualifier keys/right column entries and returns the resulting owning scope. Lvalue callers copy complete input scopes before entering. |
| failure | Duplicate qualifier yields duplicate_alias at supplied location, possibly after earlier private insertions. charge/container allocation failures abort the enclosing binding; no shared caller state is mutated. |
| cost | O(right qualifier count × log(combined qualifier count) + right column entries) container operations plus string/payload copies; lvalue input copies add O(all stored scope names/entries), and column vector growth may copy existing left entries. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp) |

## B0037

[Lines 367–379](../../../../../src/frontend/bind.cpp#L367); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scope Binder::alias_scope(Scope scope, const Json& alias, std::optional<std::size_t> where) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a relation or whole joined-table qualifier view and optionally rename an ordered column prefix. |
| inputs / outputs | Consumes a scope, validates aliasname/colnames, rewrites at most the first columns.size() names and replaces all qualifier views with one alias-to-column copy. |
| invariants | Alias must be nonempty; a rename list cannot exceed input arity, but duplicate visible column names are retained. A whole-join alias hides underlying relation qualifiers; physical expression IDs are unchanged. |
| ownership | Owns the input scope, copies alias and optional renamed strings, clears old qualifier vectors and creates one owning copy of the visible columns. |
| failure | Empty alias yields invalid_ast; excess names alias_column_count; JSON/identifier, work and allocation failures propagate. Prefix renames are private until success. |
| cost | O(renamed prefix + old qualifier storage destruction + all visible column-name bytes) work/copy and one map/vector view allocation; per-name charges do not cover the final whole-view copy. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp) |

## B0039

[Lines 381–460](../../../../../src/frontend/bind.cpp#L381); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scope Binder::from(const Json& node) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build physical occurrences and SQL-visible scopes for relations and INNER/CROSS/USING/NATURAL joins. |
| inputs / outputs | RangeVar resolves a flat catalog table and emits an occurrence plus one canonical BoundColumn per physical column. JoinExpr recursively binds two inputs, retains predicates and returns their merged or aliased visible scope. |
| invariants | Schema/catalog-qualified tables and non-INNER joins reject. Each base reference is distinct and keeps inh intent. NATURAL discovers unique common names in left-input order; USING preserves listed order, emits equalities and non-null left using_value outputs, then remaining left/right columns. Qualified inputs remain physical. ON sees only its join inputs; a USING alias adds only merged keys, while a whole alias hides inputs. |
| ownership | Owns scopes and new result records; merge(left,right) copies both input scopes while they remain available for key lookup. Occurrence names, using lists/sets, merged column vectors and qualifier views own copied strings. |
| failure | Table Error is caught and relocated at RangeVar; unknown/ambiguous keys, duplicate aliases/USING names, unsupported joins/namespaces and mixed conditions reject. Join-level errors use statement.begin because join AST has no location here; Frame/work/expression/JSON/allocation failures propagate. |
| cost | Each RangeVar repeats full catalog validation inside find_table plus a linear table scan and O(table width) nodes. NATURAL performs O(left width × right width) charged name pairs; USING adds repeated linear lookups and O((left+right width)×key count) uncharged membership searches. Nested joins copy accumulated scopes and can incur quadratic aggregate scope-copy work; this is no runtime join execution bound. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp) |

## B0041

[Lines 462–474](../../../../../src/frontend/bind.cpp#L462); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string Binder::output_name(const Json& node) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive a default select-list label from a column reference, cast or generic expression. |
| inputs / outputs | ColumnRef returns its final String field; casts strip nested casts to preserve an underlying column name, otherwise use the outer cast type name; other expressions return ?column?. |
| invariants | No scope lookup, alias resolution or semantic validation occurs. select uses an explicit target name when present, although this default expression is still evaluated by the value call. |
| ownership | Borrows AST and returns an owning name string copied from its fields or a fixed label. |
| failure | Malformed expected cast/column JSON can throw Json::exception; identifier can reject wrappers. String allocation can fail. Unsupported expressions are normally rejected before this helper. |
| cost | O(nested cast depth) traversal plus name-copy bytes and JSON lookups; no Frame/work charges. At most one recursive return into a column case after iterative cast stripping. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp) |

## B0043

[Lines 476–518](../../../../../src/frontend/bind.cpp#L476); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Binder::select(const Json& node) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind one ordinary SELECT body while preserving requested semantics, visible output order and separate filters. |
| inputs / outputs | Checks supported SELECT fields, builds FROM scope, appends Boolean WHERE predicate, then binds scalar targets or expands * / alias.* into outputs; absent targetList preserves nullary SELECT. |
| invariants | DISTINCT requires exactly one empty marker and means set; absent DISTINCT means bag. Set operations/LIMIT options and unrecognized clauses reject. FROM is bound before WHERE and targets. Wildcards use current visible names/order, ignore a scalar target alias per expansion rules and require an input qualifier even for zero-column tables. Unknown scalar outputs resolve to string. |
| ownership | Owns local scopes and result outputs, copying names but retaining expression IDs for wildcard entries. Scalar target binding can append fresh expressions; previous comma scope is moved into merge. |
| failure | Unsupported fields/clauses, DISTINCT ON, wildcard qualification/no FROM and expression/name/type failures produce binding rejection. Work/depth/expression/allocation/JSON failures discard all private outputs rather than return a prefix. |
| cost | FROM/expression costs plus O(expanded column count + output-name bytes); each wildcard output charges once. Repeated scalar references repeat lookup/append, and output_name is computed even when an explicit alias exists. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp) |

## B0045

[Lines 520–547](../../../../../src/frontend/bind.cpp#L520); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
BoundSql Binder::run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the parsed SELECT and recognize the single supported whole-result EXISTS form. |
| inputs / outputs | Reads the parser-guaranteed first statement. Ordinary SELECT delegates to select; a sole EXISTS_SUBLINK target binds the inner SELECT and records wrapper mode/alias before moving out the complete result. |
| invariants | Non-SELECT statements reject. EXISTS outer body may contain only target, ordinary DISTINCT and default op/limitOption: no outer FROM/filter or extra targets. Inner select-list binding still diagnoses unsupported/name/type errors. Outer requested semantics and inner semantics are retained separately; this path does not produce a nullary CQ. |
| ownership | Borrows syntax until completion and transfers result_ ownership by move; local Binder has no returned AST references. |
| failure | unsupported_statement or unsupported wrapper clauses/DISTINCT ON reject; malformed AST wrappers produce invalid_ast/JSON failure. Any delegated binding failure destroys the private result. |
| cost | Constant wrapper-shape work and JSON lookups plus the complete select cost; final move transfers containers without copying the catalog/source payload. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [tests/unit/binding_test.cpp](../../../../../tests/unit/binding_test.cpp) |

## B0046

[Lines 548–549](../../../../../src/frontend/bind.cpp#L548); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L548-L549:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [docs/code_specs/files/src/frontend/bind.cpp.md](bind.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0047

[Lines 550–568](../../../../../src/frontend/bind.cpp#L550); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlBindResult bind_sql(std::string_view source, const Catalog& catalog, const BindOptions& options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse and name/type-bind one SQL statement into an owning result or phase-specific diagnostic. |
| inputs / outputs | Borrows source/catalog/options. Parses with default parser limits, validates catalog, validates a copied parameter table with positional names, constructs Binder and returns its complete result. |
| invariants | Failure priority is syntax, catalog, parameters, then binding. A valid binding preserves bag/set and wrapper intent but does not normalize, prove CQ structure, plan or execute. Binder limits do not govern parsing or declaration-validation cost. |
| ownership | The returned alternative owns all data; caller source/catalog/options may be changed or destroyed after return. Temporary parse tree and private partial binding are released on exit. |
| failure | Parser diagnostic becomes syntax; catalog/parameter Error becomes matching phase without coordinates. Binder Failure preserves code/source coordinates; JSON exceptions become binding invalid_ast; bad_alloc only within Binder construction/run becomes binding resource_limit. Parser contract errors, earlier allocation failures, other exception kinds and allocations while constructing diagnostics may escape; API is not noexcept. |
| cost | Parses/scans bounded source and allocates AST, copies source/catalog/parameter metadata, validates catalog once at entry and again per RangeVar via find_table, then incurs expression/scope costs. Memory is AST plus full owned binding snapshot; no database rows are evaluated. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_support.md](../../../../sql_support.md), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp) |

## B0049

[Lines 570–581](../../../../../src/frontend/bind.cpp#L570); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string sql_kind_name(SqlKind kind) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the stable serialized name of each supported SQL type kind. |
| inputs / outputs | Maps unknown/int32/int64/string/boolean/date/decimal to unknown/int32/int64/string/bool/date/decimal strings. |
| invariants | The spelling bool is intentional and distinct from the C++ enum name boolean. Mapping neither validates the full SqlType nor performs a conversion. |
| ownership | Returns an owning std::string; no borrowed storage is exposed. |
| failure | An out-of-domain enum throws Error(binding_contract,"unknown SQL type"); returned/error strings may allocate. |
| cost | Constant switch work and a fixed-length string construction, with allocation behavior determined by std::string implementation. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp) |

## B0050

[Lines 582–607](../../../../../src/frontend/bind.cpp#L582); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string sql_operator_name(SqlOperator op) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide stable serialized operator spellings for the complete binding enum. |
| inputs / outputs | Maps each comparison, Boolean/null test, cast, integer widening and using_value tag to its corresponding schema string. |
| invariants | Does not inspect arity/types, evaluate SQL or infer unsupported operations; its switch covers the current SqlOperator declaration. |
| ownership | Returns an owning std::string independent of Binder or AST lifetime. |
| failure | An out-of-domain tag throws Error(binding_contract,"unknown SQL operator"); string construction may allocate. |
| cost | Constant switch work and fixed bounded output length; no dynamic lookup table is constructed. |
| Design | [docs/sql_binding.md](../../../../sql_binding.md), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp) |

## B0051

[Lines 608–608](../../../../../src/frontend/bind.cpp#L608); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L608-L608:sha256:2fc33ff8830b8cd06d6971e8e31b29a8803f152d87e09a3fc4092b3efecdac93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [docs/code_specs/files/src/frontend/bind.cpp.md](bind.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_parser.md](../../../../sql_parser.md) |
