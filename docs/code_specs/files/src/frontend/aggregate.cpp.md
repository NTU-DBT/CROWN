# `src/frontend/aggregate.cpp` — block usage map

[Source](../../../../../src/frontend/aggregate.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Bind admitted aggregate SQL into exact typed grouping, COUNT/SUM/AVG measures and immutable cast guards.

Snapshot SHA-256: `bedd26b3116b52830ac2b7428dbbfe87afbafcb63371a57cd57dcf4d86dd957b`. 405 lines partitioned into 46 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../src/frontend/aggregate.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 17–20](../../../../../src/frontend/aggregate.cpp#L17) | Callable definition: template&lt;class T&gt; resource::MemoryAllocator&lt;T&gt; allocator(const resource::MemoryAccount& account) | calls ; returns resource::MemoryAllocator&lt;T&gt;(account, resource::MemoryPurpose::immutable_metadata, · [reviewed contract](#b0002) |
| [B0003 · 21–23](../../../../../src/frontend/aggregate.cpp#L21) | Callable definition: \[\[noreturn\]\] void fail(std::string code, std::string message) | calls Error, std::move · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../src/frontend/aggregate.cpp#L24) | Callable definition: bool integer(SqlKind kind) | calls ; returns kind == SqlKind::int32 \|\| kind == SqlKind::int64 · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../src/frontend/aggregate.cpp#L25) | Callable definition: bool int32(std::int64_t value) | calls ; returns value &gt;= INT32_MIN && value &lt;= INT32_MAX · [reviewed contract](#b0005) |
| [B0006 · 26–31](../../../../../src/frontend/aggregate.cpp#L26) | Callable definition: std::optional&lt;std::int64_t&gt; integer_text(std::string_view text) | calls std::from_chars, data, size; returns {}; value · [reviewed contract](#b0006) |
| [B0007 · 32–42](../../../../../src/frontend/aggregate.cpp#L32) | Callable definition: SqlType column_type(const Column& column) | calls ; returns {kind, column.nullable, column.decimal} · [reviewed contract](#b0007) |
| [B0008 · 43–44](../../../../../src/frontend/aggregate.cpp#L43) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 45–65](../../../../../src/frontend/aggregate.cpp#L45) | Type/record definition: struct AggregateProgram::Data | source comment (unverified): // Backing rows/names precede their borrowed views and remain stable. · [reviewed contract](#b0009) |
| [B0010 · 66–69](../../../../../src/frontend/aggregate.cpp#L66) | declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 70–73](../../../../../src/frontend/aggregate.cpp#L70) | Type/record definition: struct Argument |  · [reviewed contract](#b0011) |
| [B0012 · 74–78](../../../../../src/frontend/aggregate.cpp#L74) | Type/record definition: struct MeasureKey |  · [reviewed contract](#b0012) |
| [B0013 · 79–94](../../../../../src/frontend/aggregate.cpp#L79) | declares values/defaults or compile-time conditions. | source comment (unverified): // Compiler-only deduplication. One retained guard per original column also · [reviewed contract](#b0013) |
| [B0014 · 95–100](../../../../../src/frontend/aggregate.cpp#L95) | Callable definition: void charge(std::uint64_t amount = 1) | calls fail; source comment (unverified): // Selected compiler checkpoints and retained text lengths, not all parser, · [reviewed contract](#b0014) |
| [B0015 · 101–109](../../../../../src/frontend/aggregate.cpp#L101) | Callable definition: void keys(const Json& node, std::initializer_list&lt;std::string_view&gt; allowed) | calls charge, is_object, fail, items; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 110–114](../../../../../src/frontend/aggregate.cpp#L110) | Callable definition: const Json& tagged(const Json& node, std::string_view tag) const | calls is_object, size, contains, at; returns node.at(tag) · [reviewed contract](#b0016) |
| [B0017 · 115–117](../../../../../src/frontend/aggregate.cpp#L115) | Callable definition: std::string identifier(const Json& node) const | calls tagged, value; returns tagged(node, @ ).value(@ , std::string{}) · [reviewed contract](#b0017) |
| [B0018 · 118–130](../../../../../src/frontend/aggregate.cpp#L118) | Callable definition: ColumnId column(const Json& expression) | calls tagged, keys, at, fail; returns catalog::resolve_column(catalog_, std::span&lt;const catalog::RelationBinding&gt;(&*input_, 1), · [reviewed contract](#b0018) |
| [B0019 · 131–150](../../../../../src/frontend/aggregate.cpp#L131) | Callable definition: Argument literal(const Json& node) | calls keys, value, contains, at; returns {{SqlKind::unknown, true, {}}, std::optional&lt;Value&gt;{}}; {{int32(value) ? SqlKind::int32 : SqlKind::… · [reviewed contract](#b0019) |
| [B0020 · 151–165](../../../../../src/frontend/aggregate.cpp#L151) | Callable definition: SqlType cast_type(const Json& node) | calls keys, contains, fail, at; returns {SqlKind::int64, false, {}}; {SqlKind::int32, false, {}} · [reviewed contract](#b0020) |
| [B0021 · 166–201](../../../../../src/frontend/aggregate.cpp#L166) | Callable definition: Argument argument(const Json& expression, std::size_t depth = 0) | calls charge, fail, contains, column; returns {result_-&gt;inputs\[id.value\], id}; literal(tagged(expression, @ )); growth insert · [reviewed contract](#b0021) |
| [B0022 · 202–203](../../../../../src/frontend/aggregate.cpp#L202) | Explanatory comments or spacing. | source comment (unverified): // Find with an ephemeral borrowed literal. Only the first distinct argument · [reviewed contract](#b0022) |
| [B0023 · 204–226](../../../../../src/frontend/aggregate.cpp#L204) | Callable definition: std::size_t measure(Argument value) | calls storage::borrow_scalar, find, end, size; returns found-&gt;second; index; growth copy_of, emplace, push_back; source comment (unverified): // Find with an ephemeral borrowed literal. Only the first distinct argument · [reviewed contract](#b0023) |
| [B0024 · 227–245](../../../../../src/frontend/aggregate.cpp#L227) | Callable definition: void from(const Json& node) | calls tagged, keys, contains, fail; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 246–296](../../../../../src/frontend/aggregate.cpp#L246) | Callable definition: void output(const Json& expression) | calls tagged, keys, at, contains; growth emplace_back, push_back · [reviewed contract](#b0025) |
| [B0026 · 297–299](../../../../../src/frontend/aggregate.cpp#L297) | Callable definition: public: AggregateCompiler(const SqlSyntax& syntax, const Catalog& catalog, const AggregateBindOptions& options, const resource::M… | calls syntax_, catalog_, options_, account_ · [reviewed contract](#b0026) |
| [B0027 · 300–338](../../../../../src/frontend/aggregate.cpp#L300) | Callable definition: AggregateProgram run() | calls fail, charge, size, tagged; returns AggregateProgram(std::move(result_)); growth emplace, make_accounted_shared, push_back, reserve; 3 loop sites; source comment (unverified): // Name views may point into SSO storage: reserve once before any view exists. · [reviewed contract](#b0027) |
| [B0028 · 339–341](../../../../../src/frontend/aggregate.cpp#L339) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0028) |
| [B0029 · 342–369](../../../../../src/frontend/aggregate.cpp#L342) | Callable definition: AggregateProgram AggregateProgram::freeze(const resource::MemoryAccount& account, const AggregateProgram& source) | calls resource::MemoryFailure, data, statistics, assign; returns source; AggregateProgram(std::move(out)); growth copy_of, emplace_back, make_accounted_shared, push_back, reserve; 2 loop sites; source comment (unverified): // Historic compilation work, not copy-work metering. · [reviewed contract](#b0029) |
| [B0030 · 370–370](../../../../../src/frontend/aggregate.cpp#L370) | Explanatory comments or spacing. |  |
| [B0031 · 371–374](../../../../../src/frontend/aggregate.cpp#L371) | Callable definition: const AggregateProgram::Data& AggregateProgram::data() const | calls fail; returns *data_ · [reviewed contract](#b0031) |
| [B0032 · 375–375](../../../../../src/frontend/aggregate.cpp#L375) | Callable definition: std::string_view AggregateProgram::source() const & | calls data; returns data().source · [reviewed contract](#b0032) |
| [B0033 · 376–376](../../../../../src/frontend/aggregate.cpp#L376) | Callable definition: bool AggregateProgram::has_input() const | calls data; returns data().has_input · [reviewed contract](#b0033) |
| [B0034 · 377–377](../../../../../src/frontend/aggregate.cpp#L377) | Callable definition: bool AggregateProgram::full_input_group_key() const | calls data; returns data().full_input_key · [reviewed contract](#b0034) |
| [B0035 · 378–378](../../../../../src/frontend/aggregate.cpp#L378) | Callable definition: std::span&lt;const SqlType&gt; AggregateProgram::input_types() const & | calls data; returns data().inputs · [reviewed contract](#b0035) |
| [B0036 · 379–379](../../../../../src/frontend/aggregate.cpp#L379) | Callable definition: std::span&lt;const ColumnId&gt; AggregateProgram::group_columns() const & | calls data; returns data().groups · [reviewed contract](#b0036) |
| [B0037 · 380–380](../../../../../src/frontend/aggregate.cpp#L380) | Callable definition: std::span&lt;const ColumnId&gt; AggregateProgram::checked_int32_columns() const & | calls data; returns data().checked_int32 · [reviewed contract](#b0037) |
| [B0038 · 381–381](../../../../../src/frontend/aggregate.cpp#L381) | Callable definition: std::span&lt;const AggregateMeasure&gt; AggregateProgram::measures() const & | calls data; returns data().measures · [reviewed contract](#b0038) |
| [B0039 · 382–382](../../../../../src/frontend/aggregate.cpp#L382) | Callable definition: std::span&lt;const AggregateOutput&gt; AggregateProgram::outputs() const & | calls data; returns data().outputs · [reviewed contract](#b0039) |
| [B0040 · 383–383](../../../../../src/frontend/aggregate.cpp#L383) | Callable definition: std::uint8_t AggregateProgram::average_scale() const | calls data; returns data().scale · [reviewed contract](#b0040) |
| [B0041 · 384–384](../../../../../src/frontend/aggregate.cpp#L384) | Callable definition: std::uint64_t AggregateProgram::work() const | calls data; returns data().work · [reviewed contract](#b0041) |
| [B0042 · 385–385](../../../../../src/frontend/aggregate.cpp#L385) | Callable definition: const resource::MemoryAccount& AggregateProgram::account() const & | calls data; returns data().account · [reviewed contract](#b0042) |
| [B0043 · 386–386](../../../../../src/frontend/aggregate.cpp#L386) | Explanatory comments or spacing. |  |
| [B0044 · 387–400](../../../../../src/frontend/aggregate.cpp#L387) | Callable definition: AggregateBindResult bind_aggregate_sql_into(const resource::MemoryAccount& account, std::string_view source, const Catalog& catal… | calls parse_sql, catalog::validate_catalog, fail, detail::AggregateCompiler; returns BindingDiagnostic{@ , *error}; detail::AggregateCompiler(std::get&lt;SqlSyntax&gt;(parsed), catalog_value… · [reviewed contract](#b0044) |
| [B0045 · 401–404](../../../../../src/frontend/aggregate.cpp#L401) | Callable definition: AggregateBindResult bind_aggregate_sql(std::string_view source, const Catalog& catalog_value, const AggregateBindOptions& options) | calls bind_aggregate_sql_into, resource::MemoryAccount::create; returns bind_aggregate_sql_into(resource::MemoryAccount::create(options.memory_limit_bytes), source, catalo… · [reviewed contract](#b0045) |
| [B0046 · 405–405](../../../../../src/frontend/aggregate.cpp#L405) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend · [reviewed contract](#b0046) |

## B0001

[Lines 1–16](../../../../../src/frontend/aggregate.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using Items =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select accounted retained metadata containers for the compiler result. |
| inputs / outputs | Items uses MemoryAllocator; Text uses the same allocator family for source and labels. |
| invariants | Allocator propagation is explicit; standard compiler workspace containers remain a separate boundary. |
| ownership | Each resulting container retains its supplied account through its allocator. |
| failure | Aliases do not themselves allocate or catch errors. |
| cost | No runtime path or new abstraction beyond standard containers. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0002

[Lines 17–20](../../../../../src/frontend/aggregate.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> resource::MemoryAllocator<T> allocator(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind metadata allocation to the compiler account and attribution. |
| inputs / outputs | Returns a typed MemoryAllocator with immutable_metadata purpose/owner ID zero. |
| invariants | It shares an existing allowance; it never creates a new grant. |
| ownership | Returned allocator retains the passed account. |
| failure | Allocator construction is nonallocating; later allocations propagate account/upstream failures. |
| cost | Fixed handle/configuration copy. |
| Design | [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0003

[Lines 21–23](../../../../../src/frontend/aggregate.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void fail(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a typed frontend rejection at the point of failed admission. |
| inputs / outputs | Owns code/message strings and throws Error. |
| invariants | Ordinary SQL rejections are converted once at the public binding boundary. |
| ownership | Error owns moved diagnostic strings during unwinding. |
| failure | Always throws; no retry, fallback, or nested recovery state. |
| cost | Failure-path string/exception work only. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/sql_support.md](../../../../sql_support.md) |

## B0004

[Lines 24–24](../../../../../src/frontend/aggregate.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool integer(SqlKind kind)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize the initially admitted SUM/AVG argument domains. |
| inputs / outputs | Returns true for int32 or int64 only. |
| invariants | Decimal and unknown NULL are not implicitly admitted as integer aggregates. |
| ownership | Inline enum input and bool output. |
| failure | No failure or allocation. |
| cost | Two fixed comparisons. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md) |

## B0005

[Lines 25–25](../../../../../src/frontend/aggregate.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool int32(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether an exact integer belongs to the SQL integer range. |
| inputs / outputs | Tests inclusive INT32_MIN..INT32_MAX. |
| invariants | No cast truncation or floating-point conversion is used. |
| ownership | Inline numeric values only. |
| failure | Returns false for out-of-range values; does not throw. |
| cost | Two fixed signed comparisons. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md) |

## B0006

[Lines 26–31](../../../../../src/frontend/aggregate.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::int64_t> integer_text(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a complete exact signed integer without allocating conversion scratch. |
| inputs / outputs | Borrowed text in; optional int64 out using from_chars. |
| invariants | Success requires no parse error and consumption of every input byte. |
| ownership | Borrows text only for the call; result is inline. |
| failure | Malformed or overflowing text returns absence; caller selects a diagnostic or other literal domain. |
| cost | Linear text scan; no heap request. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md) |

## B0007

[Lines 32–42](../../../../../src/frontend/aggregate.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlType column_type(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate catalog scalar/nullability metadata into aggregate input types. |
| inputs / outputs | Maps all five catalog ScalarType values and preserves optional DecimalSpec. |
| invariants | Catalog int64 remains bigint; int32 is introduced by admitted literal/cast typing. |
| ownership | Copies only inline metadata from a validated catalog column. |
| failure | Catalog validation occurs in callers; no runtime cast is performed here. |
| cost | Fixed enum switch and record copy. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0008

[Lines 43–44](../../../../../src/frontend/aggregate.cpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L44:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [docs/code_specs/files/src/frontend/aggregate.cpp.md](aggregate.cpp.md), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0009

[Lines 45–65](../../../../../src/frontend/aggregate.cpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AggregateProgram::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own all retained source, names, literals, and resolved aggregate metadata. |
| inputs / outputs | Owns account, physical input types, groups, sorted unique checked_int32 positions, measures, outputs, source, scale/work/flags. |
| invariants | Literal backing and reserved names preserve borrowed views. Guards record original columns independently of final measure dedup/type, so an inner narrowing survives widening. |
| ownership | All retained containers use the compiler account; parser/catalog/workspace references are absent. |
| failure | Partial Data is RAII-owned until factory publication; member allocation failures propagate. |
| cost | Source/label/literal/descriptors plus U ColumnIds of guard backing. One extra accounted vector member enlarges fixed Data even for U=0; empty backing adds no allocation. No mutable per-row/group/operator field. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

```text
explicit Data(const resource::MemoryAccount& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize every retained metadata container with the same account. |
| inputs / outputs | One compiler account constructs all empty retained containers, including the integer-guard vector. |
| invariants | No member silently receives a default standard allocator or independent allowance. |
| ownership | Data and its member allocators retain account handles. |
| failure | Member construction uses ordinary RAII; subsequent growing operations may fail. |
| cost | Fixed empty-container construction; the new vector header has fixed storage cost even without a backing allocation. |
| Design | [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0010

[Lines 66–69](../../../../../src/frontend/aggregate.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Json = nlohmann::json;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the parser AST representation inside the private compiler. |
| inputs / outputs | Alias refers to trusted versioned parser JSON nodes. |
| invariants | AST ownership stays in SqlSyntax; no AST becomes retained runtime state. |
| ownership | Compiler borrows the syntax only during synchronous binding. |
| failure | This declaration has no executable rejection path. |
| cost | Compile-time alias only. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/sql_support.md](../../../../sql_support.md) |

## B0011

[Lines 70–73](../../../../../src/frontend/aggregate.cpp#L70); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Argument {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry an argument through cold binding before stable metadata is frozen. |
| inputs / outputs | SqlType accompanies a resolved column ID or optional owning Value. |
| invariants | An absent Value is SQL NULL; temporary owning constants are not runtime row storage. |
| ownership | Value strings own compiler workspace bytes until measure() copies a first distinct literal. |
| failure | Literal construction/parsing may fail in the producing helper. |
| cost | One temporary argument; string/decimal parsing may allocate outside retained metadata. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0012

[Lines 74–78](../../../../../src/frontend/aggregate.cpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct MeasureKey {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deduplicate state by exact typed argument rather than output function name. |
| inputs / outputs | Default comparison orders SqlType and ColumnId/nullable ScalarView alternatives. |
| invariants | Stored literal views refer only to stable accounted backing; temporary lookup views expire after lookup. |
| ownership | Workspace map stores borrowed views backed by result_; its destruction does not free those bytes. |
| failure | Valid-key comparison has no allocation; invalid lifetime would violate compiler preconditions. |
| cost | Ordered-map comparisons include variable-width string/decimal comparisons. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0013

[Lines 79–94](../../../../../src/frontend/aggregate.cpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SqlSyntax& syntax_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain synchronous compiler inputs, private workspace indices and unpublished result ownership. |
| inputs / outputs | Borrows syntax/catalog/options; owns unpublished result/account and cold maps/set for group/measure/guard deduplication. |
| invariants | Compiler lifetime ends before caller inputs may expire. Workspace maps are not retained by AggregateProgram. |
| ownership | Map/set nodes and qualifier strings are ordinary compiler workspace; final descriptors and sorted guard backing use account_. |
| failure | RAII releases partial maps/result on rejection; no persistent undo or fallback ledger. |
| cost | Workspace scales with unique groups, measures and guarded columns. Ordered comparisons/allocator CPU are outside selected compiler charges and retained-account accounting. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0014

[Lines 95–100](../../../../../src/frontend/aggregate.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge(std::uint64_t amount = 1)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound and record selected binding charges. |
| inputs / outputs | Adds amount only after unsigned-overflow and optional-cap checks. |
| invariants | work_ starts at zero and never exceeds a present fixed limit, so cap subtraction is safe. |
| ownership | Mutates only private compiler work_, not published state. |
| failure | resource_limit precedes counter mutation. |
| cost | Fixed arithmetic per selected checkpoint; excludes parser, catalog validation and map comparison CPU. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0015

[Lines 101–109](../../../../../src/frontend/aggregate.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void keys(const Json& node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject unadmitted AST fields instead of silently dropping SQL semantics. |
| inputs / outputs | Object node and allowed field names in; validates every actual key after one selected charge. |
| invariants | All fields, including optional unsupported syntax, must belong to the local allowlist. |
| ownership | Borrows node and string-view initializer list for this call. |
| failure | invalid_ast for nonobject; unsupported_sql for unknown field; resource limit can fail first. |
| cost | Linear node keys times small allowlist length; error text allocates only on rejection. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0016

[Lines 110–114](../../../../../src/frontend/aggregate.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Json& tagged(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the expected single-tag parser node and borrow its object body. |
| inputs / outputs | Node/tag in; reference to the tagged object out. |
| invariants | Requires one object member, matching tag, and object-valued body. |
| ownership | Returned reference stays inside borrowed SqlSyntax AST. |
| failure | Malformed/unsupported node shape raises unsupported_expression; no catch here. |
| cost | Small object lookup and shape checks, not AST copying. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/sql_support.md](../../../../sql_support.md) |

## B0017

[Lines 115–117](../../../../../src/frontend/aggregate.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string identifier(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an owning identifier string from a parser String node. |
| inputs / outputs | Uses tagged() and reads sval, with empty-string default. |
| invariants | Identifier case/quoting normalization is already represented by the upstream parser. |
| ownership | Returns ordinary workspace string; it is not retained output metadata. |
| failure | Tag/JSON conversion failures propagate to the declared boundary. |
| cost | Identifier-length copy; may allocate for non-SSO strings. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/sql_support.md](../../../../sql_support.md) |

## B0018

[Lines 118–130](../../../../../src/frontend/aggregate.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ColumnId column(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve an unqualified or visible-alias-qualified input column once. |
| inputs / outputs | ColumnRef in; numeric ColumnId in the sole logical relation out. |
| invariants | No input means no columns. Exactly one or two identifier components are admitted; aliases hide base names. |
| ownership | AST/catalog and the single input binding are borrowed; no one-element qualifier copy is made. |
| failure | Rejects missing input or unsupported qualification; catalog resolver supplies unknown/ambiguous diagnostics. |
| cost | Identifier copies plus catalog resolver scans/revalidation; not constant binding work. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/sql_support.md](../../../../sql_support.md) |

## B0019

[Lines 131–150](../../../../../src/frontend/aggregate.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Argument literal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Type and own supported parser constants during compilation. |
| inputs / outputs | Recognizes NULL, integer, decimal, boolean and string constant fields. |
| invariants | int32-range integer literals retain integer typing; larger exactly parsed integers use bigint; decimal syntax stays decimal. |
| ownership | Temporary Value owns string/Decimal data until distinct-measure freezing. |
| failure | Unsupported literal rejects; bounded Decimal parsing or workspace allocation failures propagate. |
| cost | Linear literal parsing/copy; no per-update AST interpretation. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0020

[Lines 151–165](../../../../../src/frontend/aggregate.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlType cast_type(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve only the admitted aggregate argument cast type names. |
| inputs / outputs | TypeName in; SqlType with target kind out, before source nullability is transferred. |
| invariants | Only unqualified or pg_catalog names are admitted; explicit typmods are rejected. |
| ownership | Names are temporary workspace strings; returned type is inline. |
| failure | Rejects unsupported qualification, modifiers or type name. |
| cost | Small field/name lookup and copied identifier bytes. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md) |

## B0021

[Lines 166–201](../../../../../src/frontend/aggregate.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Argument argument(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile columns/constants and exact admitted casts into one typed argument. |
| inputs / outputs | Expression and cast depth in; resolved ColumnId or owned optional literal with SqlType out. |
| invariants | Physical column types are never overwritten. Integer-to-integer casts change only argument type; every int64-to-int32 step records the original column before final type/measure dedup. NULL passes, constants cast eagerly and exactly. Other column conversions reject. |
| ownership | Only cold compiler temporaries own literals; recursion borrows AST and catalog. |
| failure | Selected work/depth checks precede descent; unsupported syntax/conversion rejects without publishing metadata. |
| cost | Recursion/AST/lookup/parse costs plus cold ordered-set insertion for each narrowing occurrence; unique guards receive selected charges when retained. No runtime expression tree. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0022

[Lines 202–203](../../../../../src/frontend/aggregate.cpp#L202); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L202-L203:sha256:ce0cfec870f28753ee6b1d0dbfcb615dc58db151c04c109a8765996c1233ae64
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Find with an ephemeral borrowed literal. Only the first distinct argument copies its literal into stable accounted backing retained by the program. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/frontend/aggregate.cpp lines 200-205; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [docs/code_specs/files/src/frontend/aggregate.cpp.md](aggregate.cpp.md), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0023

[Lines 204–226](../../../../../src/frontend/aggregate.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t measure(Argument value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share one measure for repeated exact typed arguments and freeze only new constants. |
| inputs / outputs | Typed Argument in; stable numeric measure index out. |
| invariants | Find uses a temporary borrowed scalar; an inserted map key uses the accounted stable literal copy. Repeats allocate no retained backing. |
| ownership | New non-NULL literals get one AccountedRow retained in result_; map nodes remain compiler workspace. |
| failure | Expression limit or allocation failure unwinds unpublished result. There is no local undo ledger. |
| cost | Ordered lookup plus one retained copy for a new literal; vector growth and map insertion occur only during compilation. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0024

[Lines 227–245](../../../../../src/frontend/aggregate.cpp#L227); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void from(const Json& node)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the sole flat logical source and freeze its input types. |
| inputs / outputs | RangeVar in; input_ binding, has_input flag and copied SqlType array out. |
| invariants | Schema/catalog qualification and alias column lists are not admitted. Relation inheritance flags add no catalog hierarchy. |
| ownership | Compiler qualifier owns workspace text; only type metadata survives in AggregateProgram. |
| failure | Unsupported fields/qualification or catalog lookup rejects before program publication. |
| cost | Catalog validation/lookup plus linear column-type copy; selected charge counts column count. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/sql_support.md](../../../../sql_support.md) |

## B0025

[Lines 246–296](../../../../../src/frontend/aggregate.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void output(const Json& expression)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile one SELECT target into an ordered output descriptor. |
| inputs / outputs | ResTarget in; label backing, descriptor and any new/shared measure out. |
| invariants | Only COUNT/SUM/AVG are admitted; all aggregate DISTINCT is explicit rejection. Plain outputs must resolve to grouped columns. Integer SUM/AVG type rules are attached here. |
| ownership | names was reserved before views are created; retained labels use account_. Measures share stable typed arguments. |
| failure | Unsupported syntax/type/grouping or allocation rejects the entire unpublished program. |
| cost | One target plus argument/map work and label copy; repeated outputs share measure state. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0026

[Lines 297–299](../../../../../src/frontend/aggregate.cpp#L297); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateCompiler(const SqlSyntax& syntax,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up a synchronous private compiler without allocating result metadata. |
| inputs / outputs | Borrows syntax/catalog/options and retains the receiving account. |
| invariants | Inputs must outlive run(); account_ shares the caller grant. |
| ownership | Reference members borrow; account handle is copied. |
| failure | No admission or parse occurs in this constructor. |
| cost | Fixed member initialization. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0027

[Lines 300–338](../../../../../src/frontend/aggregate.cpp#L300); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateProgram run()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and freeze the complete initial aggregate query contract. |
| inputs / outputs | Uses parsed single SELECT/catalog/options; returns immutable factory-owned AggregateProgram. |
| invariants | Requires an aggregate, at most one flat source, grouped raw-column outputs and admitted scale. Groups retain original order; guard positions are sorted unique and charged/copied once before immutable publication. |
| ownership | Creates accounted Data/source/arrays; reserves names before borrowed SSO views; leaves no AST/catalog owner in the result. |
| failure | Any rejection or allocation failure destroys unpublished metadata. No partially valid program escapes. |
| cost | Cold source/targets/groups/guards plus catalog/ordered-container work. work_ charges U retained guards; ordered comparisons and all allocator CPU are not fully metered. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0028

[Lines 339–341](../../../../../src/frontend/aggregate.cpp#L339); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L339-L341:sha256:c4992b56c86bac4eff299a3f71382697416f38beddb6139a217c634c53eba93e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ends the private aggregate Builder type and its detail namespace; the public AggregateProgram freeze/bind definitions follow outside that helper scope. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [docs/code_specs/files/src/frontend/aggregate.cpp.md](aggregate.cpp.md), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0029

[Lines 342–369](../../../../../src/frontend/aggregate.cpp#L342); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateProgram AggregateProgram::freeze(const resource::MemoryAccount& account, const AggregateProgram& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import genuine AggregateProgram immutable metadata into receiving account without re-admission. |
| inputs / outputs | Receiving account + genuine source handle -&gt; shared same-account or independently receiver-owned aggregate metadata. |
| invariants | Copies source, physical inputs, groups, sorted guards, types, flags, scale and historic work; rebases constants/names before exposing views. No foreign backing remains. |
| ownership | Accounted shared Data/control plus exact nested allocator purposes; literal backing precedes measure views and names precede outputs. Source remains immutable throughout. |
| failure | Empty account/handle or allocation/account limit propagates; partial destination dies, no parser/catch/DTO authority or source change. |
| cost | Same-owner sharing is O(1) without allocation; foreign copy scales with retained metadata/bytes plus U guards. Historic compiler work is preserved, not a copy-work counter. |
| Design | [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), src/frontend/sql_rows.cpp:514, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [docs/aggregates.md](../../../../aggregates.md) |

## B0031

[Lines 371–374](../../../../../src/frontend/aggregate.cpp#L371); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AggregateProgram::Data& AggregateProgram::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Centralize checked access to an aggregate program owner. |
| inputs / outputs | Returns a const reference to Data for a nonempty handle. |
| invariants | No getter silently substitutes an empty descriptor set. |
| ownership | Reference borrows the existing shared owner. |
| failure | Empty handle raises invalid_aggregate_program. |
| cost | Constant pointer test; no successful allocation. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0032

[Lines 375–375](../../../../../src/frontend/aggregate.cpp#L375); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view AggregateProgram::source() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read retained SQL source. |
| inputs / outputs | Valid program in; string view out. |
| invariants | Reads immutable compiled metadata; does not execute SQL or recompute retained SQL source. |
| ownership | Returned view borrows source bytes; keep a program handle alive. |
| failure | data() rejects an empty handle; no allocation on success. |
| cost | Constant getter; no deep copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0033

[Lines 376–376](../../../../../src/frontend/aggregate.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AggregateProgram::has_input() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read presence of a named input relation. |
| inputs / outputs | Valid program in; bool out. |
| invariants | Reads immutable compiled metadata; does not execute SQL or recompute presence of a named input relation. |
| ownership | Returns an inline value; no additional owner. |
| failure | data() rejects an empty handle; no allocation on success. |
| cost | Constant getter; no deep copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0034

[Lines 377–377](../../../../../src/frontend/aggregate.cpp#L377); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AggregateProgram::full_input_group_key() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exact all-input-columns group-key flag. |
| inputs / outputs | Valid program in; bool out. |
| invariants | Reads immutable compiled metadata; does not execute SQL or recompute exact all-input-columns group-key flag. |
| ownership | Returns an inline value; no additional owner. |
| failure | data() rejects an empty handle; no allocation on success. |
| cost | Constant getter; no deep copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0035

[Lines 378–378](../../../../../src/frontend/aggregate.cpp#L378); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const SqlType> AggregateProgram::input_types() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read resolved complete logical input types. |
| inputs / outputs | Valid program in; span out. |
| invariants | Reads immutable compiled metadata; does not execute SQL or recompute resolved complete logical input types. |
| ownership | Returned view borrows input array; keep a program handle alive. |
| failure | data() rejects an empty handle; no allocation on success. |
| cost | Constant getter; no deep copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0036

[Lines 379–379](../../../../../src/frontend/aggregate.cpp#L379); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const ColumnId> AggregateProgram::group_columns() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read deduplicated group column order. |
| inputs / outputs | Valid program in; span out. |
| invariants | Reads immutable compiled metadata; does not execute SQL or recompute deduplicated group column order. |
| ownership | Returned view borrows group array; keep a program handle alive. |
| failure | data() rejects an empty handle; no allocation on success. |
| cost | Constant getter; no deep copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0037

[Lines 380–380](../../../../../src/frontend/aggregate.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const ColumnId> AggregateProgram::checked_int32_columns() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the immutable sorted distinct integer-cast guard positions. |
| inputs / outputs | Live program -&gt; borrowed const ColumnId span, empty without narrowing. |
| invariants | Positions refer to original physical input slots; nested casts and measure dedup do not erase a guard. |
| ownership | Caller retains a program handle for the borrow. |
| failure | Empty handle rejects through data(); no parser or allocation. |
| cost | Fixed accessor; no payload copy. |
| Design | [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [docs/aggregates.md](../../../../aggregates.md) |

## B0038

[Lines 381–381](../../../../../src/frontend/aggregate.cpp#L381); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const AggregateMeasure> AggregateProgram::measures() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read deduplicated typed argument descriptors. |
| inputs / outputs | Valid program in; span out. |
| invariants | Reads immutable compiled metadata; does not execute SQL or recompute deduplicated typed argument descriptors. |
| ownership | Returned view borrows measure array and literal backing; keep a program handle alive. |
| failure | data() rejects an empty handle; no allocation on success. |
| cost | Constant getter; no deep copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0039

[Lines 382–382](../../../../../src/frontend/aggregate.cpp#L382); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const AggregateOutput> AggregateProgram::outputs() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read ordered SELECT descriptors. |
| inputs / outputs | Valid program in; span out. |
| invariants | Reads immutable compiled metadata; does not execute SQL or recompute ordered SELECT descriptors. |
| ownership | Returned view borrows output array and name backing; keep a program handle alive. |
| failure | data() rejects an empty handle; no allocation on success. |
| cost | Constant getter; no deep copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0040

[Lines 383–383](../../../../../src/frontend/aggregate.cpp#L383); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint8_t AggregateProgram::average_scale() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read declared fixed AVG scale. |
| inputs / outputs | Valid program in; uint8 out. |
| invariants | Reads immutable compiled metadata; does not execute SQL or recompute declared fixed AVG scale. |
| ownership | Returns an inline value; no additional owner. |
| failure | data() rejects an empty handle; no allocation on success. |
| cost | Constant getter; no deep copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0041

[Lines 384–384](../../../../../src/frontend/aggregate.cpp#L384); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t AggregateProgram::work() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read selected compilation charges. |
| inputs / outputs | Valid program in; uint64 out. |
| invariants | Reads immutable compiled metadata; does not execute SQL or recompute selected compilation charges. |
| ownership | Returns an inline value; no additional owner. |
| failure | data() rejects an empty handle; no allocation on success. |
| cost | Constant getter; no deep copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0042

[Lines 385–385](../../../../../src/frontend/aggregate.cpp#L385); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& AggregateProgram::account() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read retained compiler account. |
| inputs / outputs | Valid program in; reference out. |
| invariants | Reads immutable compiled metadata; does not execute SQL or recompute retained compiler account. |
| ownership | Returned view borrows Data account handle; keep a program handle alive. |
| failure | data() rejects an empty handle; no allocation on success. |
| cost | Constant getter; no deep copy. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md) |

## B0044

[Lines 387–400](../../../../../src/frontend/aggregate.cpp#L387); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateBindResult bind_aggregate_sql_into(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse and bind against a supplied finite metadata account with one diagnostic conversion boundary. |
| inputs / outputs | Source/catalog/options/account in; immutable program or phase-tagged BindingDiagnostic out. |
| invariants | Parser runs first. Catalog and binding Error rejections become diagnostics; successful source metadata owns no caller references. |
| ownership | Parser and compiler workspace are ordinary temporaries; retained result is funded by the supplied account. |
| failure | Syntax diagnostics return directly. MemoryFailure/bad_alloc and parser-contract failures propagate rather than becoming SQL rejection. |
| cost | One cold parse/bind pass; no broad catch, retry, fallback or hot-path recovery state. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0045

[Lines 401–404](../../../../../src/frontend/aggregate.cpp#L401); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AggregateBindResult bind_aggregate_sql(std::string_view source,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the standalone compiler allowance and delegate to receiver-based binding. |
| inputs / outputs | Uses options.memory_limit_bytes for a new finite account; returns the ordinary binding result. |
| invariants | Separate invocations have separate compiler owners; this is not an update-time budget refill. |
| ownership | Successful AggregateProgram retains its compiler account beyond this temporary handle. |
| failure | Account creation/binding allocation failures propagate; SQL diagnostics remain result alternatives. |
| cost | One controller allocation plus the delegated cold compilation. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../memory_accounts.md) |

## B0046

[Lines 405–405](../../../../../src/frontend/aggregate.cpp#L405); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L405-L405:sha256:2fc33ff8830b8cd06d6971e8e31b29a8803f152d87e09a3fc4092b3efecdac93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [docs/code_specs/files/src/frontend/aggregate.cpp.md](aggregate.cpp.md), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |
