# `src/frontend/sql_scalar.hpp` — block usage map

[Source](../../../../../src/frontend/sql_scalar.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics.

Snapshot SHA-256: `b1353cfb115c7e745fb632ddddef1ab9608d7217f0af528570a22aa470b70c51`. 88 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../src/frontend/sql_scalar.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Strings borrow the caller/program payload; other scalar alternatives are · [reviewed contract](#b0001) |
| [B0002 · 13–18](../../../../../src/frontend/sql_scalar.hpp#L13) | Callable definition: inline std::uint64_t scalar_bytes(const storage::ScalarView& value) | calls size, parts; returns static_cast&lt;std::uint64_t&gt;(text-&gt;size()); static_cast&lt;std::uint64_t&gt;(decimal-&gt;parts().digits.size()); source comment (unverified): // Strings borrow the caller/program payload; other scalar alternatives are · [reviewed contract](#b0002) |
| [B0003 · 19–21](../../../../../src/frontend/sql_scalar.hpp#L19) | Callable definition: inline void admit_value(storage::IndexWorkAllowance* work, const storage::ScalarView& value) | calls admit, scalar_bytes · [reviewed contract](#b0003) |
| [B0004 · 22–26](../../../../../src/frontend/sql_scalar.hpp#L22) | Callable definition: inline std::optional&lt;bool&gt; truth(const Cell& value) | calls storage::IndexFailure; returns {}; std::get&lt;bool&gt;(*value) · [reviewed contract](#b0004) |
| [B0005 · 27–27](../../../../../src/frontend/sql_scalar.hpp#L27) | Callable definition: inline Cell boolean(std::optional&lt;bool&gt; value) | calls ; returns value ? Cell{storage::ScalarView{*value}} : Cell{} · [reviewed contract](#b0005) |
| [B0006 · 28–31](../../../../../src/frontend/sql_scalar.hpp#L28) | Callable definition: inline const Cell& cell_at(std::span&lt;const Cell&gt; values, ExpressionId id) | calls size, storage::IndexFailure; returns values\[id.value\] · [reviewed contract](#b0006) |
| [B0007 · 32–37](../../../../../src/frontend/sql_scalar.hpp#L32) | Explanatory comments or spacing. | source comment (unverified): // The binder/compiler has admitted operator arity and operand types. Each · [reviewed contract](#b0007) |
| [B0008 · 38–87](../../../../../src/frontend/sql_scalar.hpp#L38) | Callable definition: inline Cell evaluate(SqlOperator operation, std::span&lt;const ExpressionId&gt; arguments, std::span&lt;const Cell&gt; values, storage::Index… | calls size, storage::IndexFailure, cell_at, arg; returns cell_at(values, arguments\[i\]); arg(0); 1 loop sites; source comment (unverified): // The binder/compiler has admitted operator arity and operand types. Each · [reviewed contract](#b0008) |
| [B0009 · 88–88](../../../../../src/frontend/sql_scalar.hpp#L88) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend::sql_detail · [reviewed contract](#b0009) |

## B0001

[Lines 1–12](../../../../../src/frontend/sql_scalar.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Cell = std::optional<storage::ScalarView>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the private borrowed nullable SQL scalar boundary shared by native adapter and future SQL-row compilation. |
| inputs / outputs | Existing typed SQL operator/ExpressionId declarations, inline native scalar alternatives and optional work allowance are dependencies; Cell is optional&lt;ScalarView&gt;. |
| invariants | SQL NULL is absence here, without adding a NULL alternative to classical Value, ScalarView or core layouts. Includes and aliases do not enable bags or new syntax. |
| ownership | A Cell owns its inline numeric/date/Boolean value, while string_view bytes remain owned by the caller or immutable program. |
| failure | These declarations do not execute admission or allocate a runtime owner. |
| cost | Compile-time aliases/includes and fixed-size slot representation; no registry, control block or per-operation grant. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

## B0002

[Lines 13–18](../../../../../src/frontend/sql_scalar.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::uint64_t scalar_bytes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure variable scalar width for explicit adaptation grant debits. |
| inputs / outputs | String uses view length, InlineDecimal uses coefficient digit count, other scalar kinds return zero. |
| invariants | This reports logical scalar bytes and does not allocate, format or scan text contents. |
| ownership | Borrows scalar during call; decimal parts view remains local. |
| failure | Valid native scalar representation is assumed; this helper does not validate field domains. |
| cost | Variant probes plus stored-length access; bounded inline decimal parts inspection, independent of string contents. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

## B0003

[Lines 19–21](../../../../../src/frontend/sql_scalar.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void admit_value(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge one scalar field and its variable-width payload to the existing adaptation grant. |
| inputs / outputs | Optional allowance and ScalarView; null work suppresses debit. |
| invariants | Counter admission precedes the corresponding guarded comparison/projected-field copy where called; it does not meter all validation or allocator instructions. |
| ownership | Borrows work and scalar; no retained state. |
| failure | Allowance exhaustion propagates without changing program metadata. |
| cost | Fixed counter admission plus scalar-width measurement; subsequent text comparison/copy is separate. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

## B0004

[Lines 22–26](../../../../../src/frontend/sql_scalar.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::optional<bool> truth(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Interpret nullable expression values as SQL three-valued booleans. |
| inputs / outputs | Disengaged Cell returns nullopt; an engaged boolean ScalarView returns its bool, including false. |
| invariants | No truthiness coercion of strings, integers or dates. |
| ownership | Returns inline optional bool; no borrowed text escapes. |
| failure | Nonboolean engaged value throws IndexFailure(contract). |
| cost | Fixed variant/type branch. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

## B0005

[Lines 27–27](../../../../../src/frontend/sql_scalar.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Cell boolean(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a three-valued boolean result back to a nullable scalar slot. |
| inputs / outputs | An engaged optional&lt;bool&gt; becomes an inline bool Cell; nullopt becomes an empty Cell. |
| invariants | Engaged false remains a value and is not confused with SQL null. |
| ownership | Inline value result. |
| failure | No dynamic construction or checked failure in the valid bool conversion. |
| cost | Fixed optional/variant construction. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

## B0006

[Lines 28–31](../../../../../src/frontend/sql_scalar.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const Cell& cell_at(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one already evaluated SQL slot by its resolved expression ID. |
| inputs / outputs | Read-only Cell span and ExpressionId in; const Cell reference out while the supplied span/storage remains live. |
| invariants | The helper bounds-checks the accessed ID and never recursively evaluates, coerces or materializes the value. |
| ownership | No owner is acquired. Neither slot nor referenced string bytes may outlive its caller/program backing. |
| failure | An out-of-range ID throws fixed IndexFailure(contract) before reading a slot; no owning diagnostic text or recovery state. |
| cost | One comparison and one indexed read on success, with no payload scan or allocation. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

## B0007

[Lines 32–37](../../../../../src/frontend/sql_scalar.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// The binder/compiler has admitted operator arity and operand types.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the trusted scalar-program preconditions, SQL filter responsibility and preserved charge boundary. |
| inputs / outputs | These comments apply to the following evaluate helper and its typed caller, not arbitrary unvalidated ASTs or physical source rows. |
| invariants | The binder/compiler admits arity/types. evaluate returns a nullable scalar; its caller admits a row only when predicate truth is TRUE. Core equality remains non-null. |
| ownership | Comments create no owner; evaluation borrows caller slots and returns inline values/views. |
| failure | The prose describes propagated bounds/type/work failures without adding catches or validation frameworks. |
| cost | No runtime instrumentation. Boolean visits and comparison operands are selected charges, not complete CPU timing or allocator-byte accounting. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

## B0008

[Lines 38–87](../../../../../src/frontend/sql_scalar.hpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Cell evaluate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one admitted SQL adapter opcode over already available expression slots. |
| inputs / outputs | An admitted SqlOperator, positional ExpressionId span, existing borrowed Cell slot span and optional existing allowance in; one nullable ScalarView out. |
| invariants | Caller admits arity/types and supplies already evaluated slots. Identity/literal/widen operations copy the admitted representation, and USING returns its left argument under a separate mandatory equality. Unary null/truth tests and NOT preserve SQL three-valued rules; AND/OR short-circuit in stored argument order. Comparisons require equal scalar alternatives and return NULL if either operand is NULL. |
| ownership | Spans and slot references borrow caller/program storage. Result copies inline alternatives or a string_view only; neither dependencies nor string bytes are retained or materialized. |
| failure | Accessed argument/value bounds, engaged nonboolean truth values, scalar-alternative mismatch and unsupported opcode throw fixed IndexFailure(contract). Supplied allowance exhaustion preserves its selected fixed/dynamic failure family. No catch, translation, state publication or work refund occurs. |
| cost | Fixed-arity operations use bounded slot/type work; AND/OR cost follows visited arguments. Non-NULL comparisons admit both stored field widths before exact comparison; string common-prefix bytes and bounded decimal coefficients retain real costs. Valid scalar evaluation performs no owning payload allocation, but this does not make the caller adapter allocation-free. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

```text
const auto arg = [&](std::size_t i) -> const Cell&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a compiled operation’s positional argument to an existing expression value. |
| inputs / outputs | Check the requested argument position, then use its ExpressionId to borrow a Cell from the supplied slot span. |
| invariants | Does not evaluate dependencies recursively or coerce the selected value. |
| ownership | Returns a borrowed slot reference for this evaluation only. |
| failure | Either accessed span bound throws IndexFailure(contract); invalid value IDs no longer use the old private vector.at out_of_range path. Valid frozen/replayed metadata remains unchanged. |
| cost | Two indexed accesses with bounds checks; no scalar payload scan. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

```text
case SqlOperator::identity_cast: case SqlOperator::literal_cast:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse already normalized scalar representation for admitted identity/literal/widen/USING opcodes. |
| inputs / outputs | Returns arg(0) by nullable scalar-view value. |
| invariants | These opcodes operate on a representation already resolved by binding. No numeric/string parsing or general SQL cast occurs here; USING ignores its right slot because its mandatory join equality is checked separately. |
| ownership | Copies inline scalar or borrowed string view, never an owning row payload. |
| failure | Argument bounds faults propagate. |
| cost | Fixed slot/view copy for these opcodes. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

```text
case SqlOperator::is_null: case SqlOperator::is_unknown:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement total SQL null/truth predicates and nullable boolean negation. |
| inputs / outputs | Null/unknown tests inspect engagement; true/false predicates compare optional&lt;bool&gt;; negation preserves null. |
| invariants | IS NOT TRUE/FALSE includes null as dictated by optional comparison; engaged nonboolean truth arguments are rejected. |
| ownership | Returns inline boolean or null only. |
| failure | Argument/type checks propagate; null tests do not force boolean interpretation. |
| cost | Fixed bounded slot checks per unary predicate. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

```text
case SqlOperator::conjunction: case SqlOperator::disjunction: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate SQL AND/OR in argument order with decisive-value short circuit. |
| inputs / outputs | Debits each visited argument, records nulls, returns decisive false/true or null if no decisive value and null occurred. |
| invariants | Admitted source programs have nonempty Boolean argument lists. The loop retains the former empty-list identities internally, but that is not new SQL syntax admission. Decisive false/true stops further reads and charges; otherwise any NULL produces UNKNOWN. |
| ownership | Borrowed slot reads and inline result; no nested evaluation stack. |
| failure | Visited malformed/nonboolean slots or allowance exhaustion propagate before further arguments. |
| cost | Linear in visited argument count, with early exit possible and fixed work per truth interpretation. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

```text
case SqlOperator::equal: case SqlOperator::not_equal: case SqlOperator::less:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two nonnull matching native scalar alternatives under admitted SQL comparison opcodes. |
| inputs / outputs | A NULL operand returns NULL with no comparison scalar debit. Otherwise admit left field/bytes, then right field/bytes, compare exact inline alternatives and return one bool. |
| invariants | Cross-alternative comparison is contract failure; this branch does not silently coerce SQL kinds. |
| ownership | Inputs remain borrowed views; output is inline bool. |
| failure | Accessed bounds, kind mismatch and work exhaustion propagate. The left debit can remain consumed if the right debit fails, matching the original order; no comparison or data mutation follows that failure. |
| cost | Two scalar-width debits plus exact comparison; string comparison can scan common prefix and decimal ordering uses bounded exact coefficient work. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md) |

## B0009

[Lines 88–88](../../../../../src/frontend/sql_scalar.hpp#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L88:sha256:7387ff25b3f8cd22ebc6a6823d3f1010580551333e4c52aa00595f41ec7eb80e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend::sql_detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/code_specs/files/src/frontend/sql_scalar.hpp.md](sql_scalar.hpp.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |
