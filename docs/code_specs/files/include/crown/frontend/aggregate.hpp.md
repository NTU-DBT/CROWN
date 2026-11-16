# `include/crown/frontend/aggregate.hpp` — block usage map

[Source](../../../../../../include/crown/frontend/aggregate.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare immutable aggregate input/group/measure/output descriptors and checked integer-column guards.

Snapshot SHA-256: `026b75a4ef6b85e46e87431220b521837b98cb61d74d27e26555ac9104126b68`. 83 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../../sql_support.md), [docs/sql_parser.md](../../../../../sql_parser.md), [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_admission.md](../../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../../include/crown/frontend/aggregate.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Argument views borrow the immutable program's accounted literal backing. · [reviewed contract](#b0001) |
| [B0002 · 16–21](../../../../../../include/crown/frontend/aggregate.hpp#L16) | Type/record definition: struct AggregateMeasure | source comment (unverified): // A SUM or AVG output needs the exact numerator. · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../../include/crown/frontend/aggregate.hpp#L22) | Type/record definition: enum class AggregateOutputKind |  · [reviewed contract](#b0003) |
| [B0004 · 23–28](../../../../../../include/crown/frontend/aggregate.hpp#L23) | Type/record definition: struct AggregateOutput | source comment (unverified): // Group-key position or measure ID; unused for COUNT(*). · [reviewed contract](#b0004) |
| [B0005 · 29–33](../../../../../../include/crown/frontend/aggregate.hpp#L29) | Type/record definition: struct AggregateBindOptions |  · [reviewed contract](#b0005) |
| [B0006 · 34–44](../../../../../../include/crown/frontend/aggregate.hpp#L34) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Factory-owned aggregate descriptors; this grants no CROWN tree/height proof. · [reviewed contract](#b0006) |
| [B0007 · 45–45](../../../../../../include/crown/frontend/aggregate.hpp#L45) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns bool(data_) · [reviewed contract](#b0007) |
| [B0008 · 46–68](../../../../../../include/crown/frontend/aggregate.hpp#L46) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Original input positions whose contributing, non-NULL values must fit SQL · [reviewed contract](#b0008) |
| [B0009 · 69–69](../../../../../../include/crown/frontend/aggregate.hpp#L69) | Callable definition: explicit AggregateProgram(std::shared_ptr&lt;const Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0009) |
| [B0010 · 70–83](../../../../../../include/crown/frontend/aggregate.hpp#L70) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // SQL errors return a diagnostic; parser contract failures propagate. · [reviewed contract](#b0010) |

## B0001

[Lines 1–15](../../../../../../include/crown/frontend/aggregate.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using AggregateArgument =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate a resolved input position from a nullable retained constant. |
| inputs / outputs | ColumnId reads one logical row; optional ScalarView represents a constant or SQL NULL. |
| invariants | NULL remains outside crown::Value. String alternatives borrow immutable program backing. |
| ownership | A surviving AggregateProgram owns constant bytes; copying this variant does not extend that owner. |
| failure | This alias performs no admission; compiler construction must establish valid positions and lifetimes. |
| cost | Inline variant copy; no owning string or expression tree. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

## B0002

[Lines 16–21](../../../../../../include/crown/frontend/aggregate.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AggregateMeasure {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one deduplicated argument and the sufficient statistics its consumers need. |
| inputs / outputs | Stores argument SqlType and resolved argument; sum requests a numerator, int64_sum requests bigint SUM range admission. |
| invariants | COUNT/SUM/AVG outputs may share one measure. int64_sum concerns SUM(int32), independently of AVG output type. |
| ownership | Descriptor strings borrow the owning program; booleans and type are inline. |
| failure | Declaration does not validate aggregate support or compute numeric state. |
| cost | Fixed record per distinct typed argument; no per-output duplicate state. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

## B0003

[Lines 22–22](../../../../../../include/crown/frontend/aggregate.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class AggregateOutputKind
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the runtime interpretation of one ordered SELECT output. |
| inputs / outputs | Enumerates group projection, row count, non-NULL count, sum, and average. |
| invariants | COUNT(*) reads total group rows; count_value reads a measure count. |
| ownership | Inline discriminant with no owner. |
| failure | Declaration has no executable rejection path. |
| cost | Constant dispatch descriptor. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../../aggregates.md) |

## B0004

[Lines 23–28](../../../../../../include/crown/frontend/aggregate.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AggregateOutput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain ordered output label, type, and resolved source index. |
| inputs / outputs | index selects a group-key field or measure; COUNT(*) leaves it unused. |
| invariants | Output order and repetition survive compilation. Name views must remain backed by the program. |
| ownership | Label is borrowed immutable text; type/index are inline. |
| failure | Compiler establishes legal index/kind combinations; this record does not check them. |
| cost | One fixed descriptor per SELECT target. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

## B0005

[Lines 29–33](../../../../../../include/crown/frontend/aggregate.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AggregateBindOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set cold compiler bounds and the explicit AVG output scale. |
| inputs / outputs | Carries BindLimits, standalone compiler byte limit, and default scale 18. |
| invariants | Admitted scale is 0..18; _into uses the supplied account grant rather than minting this limit. |
| ownership | Caller retains options only through synchronous binding. |
| failure | Factory rejects unsupported scale and propagates account/allocation failures. |
| cost | Inline configuration; limits do not claim to meter all parser or catalog CPU. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../../aggregates.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0006

[Lines 34–44](../../../../../../include/crown/frontend/aggregate.hpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AggregateProgram {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one immutable factory-owned aggregate descriptor handle and receiver-account freeze operation. |
| inputs / outputs | Factory/freeze yields a shared immutable handle; borrowed source, physical input types, group positions, sorted integer-guard positions, measures, outputs and account accompany scalar flags/scale/work. |
| invariants | No CROWN tree/height proof. Same-account freeze shares; foreign freeze copies guard positions and rebases literals/names. Physical bigint types stay unchanged by aggregate casts; rvalue views stay deleted. |
| ownership | Copies share the source owner. Freeze into another account owns copied metadata there; all returned spans/views borrow a surviving handle. Moving empties the source. |
| failure | Empty-handle access and receiving-account/copy failures propagate; freeze does not parse, rebind or validate a plan. |
| cost | O(1) same-owner sharing; cold foreign metadata/string copy and receiver-account allocations. No per-epoch work. |
| Design | [docs/sql_aggregate_binding.md](../../../../../sql_aggregate_binding.md), [include/crown/resource/memory.hpp](../../../../../../include/crown/resource/memory.hpp), [src/frontend/aggregate.cpp](../../../../../../src/frontend/aggregate.cpp) |

## B0007

[Lines 45–45](../../../../../../include/crown/frontend/aggregate.hpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] explicit operator bool() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether this program handle retains compiled Data. |
| inputs / outputs | Returns shared-owner presence without borrowing any metadata. |
| invariants | Presence alone does not assert a tree proof or execute a query. |
| ownership | Reads its shared pointer without adding ownership. |
| failure | Noexcept and nonallocating. |
| cost | Constant pointer-presence test. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

## B0008

[Lines 46–68](../../../../../../include/crown/frontend/aggregate.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::string_view source() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare borrowed access to immutable source and compiled descriptors. |
| inputs / outputs | source/input_types/group_columns/checked_int32_columns/measures/outputs/account expose borrowed immutable metadata; flags/scale/work return scalar values. |
| invariants | Deleted rvalue overloads prevent borrowing directly from a temporary; a surviving handle is still required. |
| ownership | Returned spans and string views do not retain Data independently. |
| failure | Definitions reject empty handles; this declaration provides no range validation to callers. |
| cost | Direct getters make no deep copy or allocation. work() reports selected compiler charges; an empty guard list still requires its accessor/empty-loop check at runtime. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md) |

## B0009

[Lines 69–69](../../../../../../include/crown/frontend/aggregate.hpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit AggregateProgram(std::shared_ptr<const Data> value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish an already constructed immutable Data owner into a factory-only handle. |
| inputs / outputs | Takes a shared pointer by value and moves it into data_. |
| invariants | Only the friend compiler can call this constructor; no descriptor is rebuilt here. |
| ownership | The pointer transfers into the handle and retains its existing account. |
| failure | Noexcept move; no allocation. |
| cost | Constant pointer transfer. |
| Design | [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/memory_accounts.md §Account and ownership contract](../../../../../memory_accounts.md) |

## B0010

[Lines 70–83](../../../../../../include/crown/frontend/aggregate.hpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using AggregateBindResult =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish a bound immutable program from an ordinary SQL diagnostic. |
| inputs / outputs | Factories return AggregateProgram or BindingDiagnostic; _into also receives an existing account. |
| invariants | Parser workspace is separate from retained metadata. A new standalone account is finite. |
| ownership | Success owns compiled metadata; diagnostics own their strings. Caller source/catalog may then expire. |
| failure | SQL/catalog Error inside binding becomes a diagnostic; parser-contract and allocation/account exceptions may escape. |
| cost | Cold parse/bind work and retained-source copy; not a per-update operation. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../../aggregates.md), [docs/aggregates.md §Logical input and publication](../../../../../aggregates.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |
