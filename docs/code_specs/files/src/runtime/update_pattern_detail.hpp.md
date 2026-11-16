# `src/runtime/update_pattern_detail.hpp` — block usage map

[Source](../../../../../src/runtime/update_pattern_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `c252833484c43b388a7058f28743de7256c983cd6562fb296f09e4621362d1ab`. 26 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/native-replay.md](../../../../native-replay.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/runtime/update_pattern_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Logical rule comparisons share the existing window command grant. The · [reviewed contract](#b0001) |
| [B0002 · 10–17](../../../../../src/runtime/update_pattern_detail.hpp#L10) | Callable definition: template&lt;class Charge&gt; const patterns::TableRule* find( const patterns::Declaration& declaration, TableId table, Charge& charge) | calls rules, std::lower_bound, begin, end; returns rule.table &lt; key; item != rules.end() && item-&gt;table == table ? &*item : nullptr; source comment (unverified): // Logical rule comparisons share the existing window command grant. The · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../../src/runtime/update_pattern_detail.hpp#L18) | Explanatory comments or spacing. | source comment (unverified): // Fill only caller-owned scalar scratch. A failed Error allocation is a · [reviewed contract](#b0003) |
| [B0004 · 20–25](../../../../../src/runtime/update_pattern_detail.hpp#L20) | Callable definition: inline void require(bool condition, PatternViolationKind kind, TableId table, std::uint64_t command, std::uint64_t label, Pattern… | calls Error; guard inline void require(bool condition, PatternViolationKind kind, TableId table,; source comment (unverified): // Fill only caller-owned scalar scratch. A failed Error allocation is a · [reviewed contract](#b0004) |
| [B0005 · 26–26](../../../../../src/runtime/update_pattern_detail.hpp#L26) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::pattern_detail · [reviewed contract](#b0005) |

## B0001

[Lines 1–9](../../../../../src/runtime/update_pattern_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:076cb89cbe552651223675e6b6811188cf5e21588d9f97c36d2dde50287987cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide private session helpers for matching declarations and recording violations. |
| inputs / outputs | This block contains includes, namespace scope, and the helper comment; it has no callable input or output. |
| invariants | The comment describes reuse of immutable declaration rules; P4 proof conditions are not introduced here. |
| ownership | No runtime owner is created by includes or namespace declarations. |
| failure | No runtime failure path; ordinary compilation depends on the runtime declaration and Error APIs. |
| cost | No runtime work; compile-time dependencies only. |
| Design | [include/crown/runtime/update_pattern.hpp](../../../../../include/crown/runtime/update_pattern.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0002

[Lines 10–17](../../../../../src/runtime/update_pattern_detail.hpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L17:sha256:4af6fa4965ce575e15cc0785ffbd8c5c5d6d49b4dd1e9cb8d35eda783e9a8e57
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a declared rule for one table while charging the existing caller grant. |
| inputs / outputs | Window preflight passes the immutable Declaration, table ID, and a Charge callback; the helper returns a borrowed TableRule pointer or null. |
| invariants | Rules are sorted by Declaration construction. A missing rule means no declaration for that table; the helper does not infer a joined FIFO scope or establish P4 compliance beyond the checked event. |
| ownership | The returned pointer borrows declaration storage; the caller retains the declaration for its lifetime. No index or scratch owner is created. |
| failure | The supplied charge callback may throw on work exhaustion; the helper catches nothing. |
| cost | O(log R) comparisons plus the final charge callback, where R is rule count; no allocation. |
| Design | [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [include/crown/ir/update_pattern.hpp](../../../../../include/crown/ir/update_pattern.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0003

[Lines 18–19](../../../../../src/runtime/update_pattern_detail.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L19:sha256:7c9e0713e8150f3b1723411dd34968435bd1a86a5e8a26545d3df0a2256c6b98
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the violation helper’s scratch and error-allocation boundary. |
| inputs / outputs | No runtime input or output; the comment describes the following require helper. |
| invariants | Session latches only a completed semantic Error, so failed Error text allocation remains an allocation failure; no P4 claim is made. |
| ownership | The comment owns no data; the output diagnostic is caller-provided fixed scratch. |
| failure | No runtime failure path in the comment itself. |
| cost | No runtime cost. |
| Design | [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0004

[Lines 20–25](../../../../../src/runtime/update_pattern_detail.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L25:sha256:fc0bd48462c9552ec98bb8fad215e3dc6c7791139f87304e067dd4eac0357825
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed local predicate into a fixed diagnostic plus the existing runtime Error. |
| inputs / outputs | Callers supply the predicate, violation kind/table/command/label, and an optional PatternViolation output pointer. |
| invariants | Success returns immediately. On failure the helper fills caller scratch before throwing; session/window callers decide whether a fully constructed semantic error is latched. The helper itself does not prove the paper’s global history assumptions. |
| ownership | The diagnostic pointer is borrowed and receives fixed fields only; Error owns its message strings. |
| failure | The Error constructor may allocate. No catch, translation, or retry layer is added here. |
| cost | Constant predicate/field work plus Error construction on failure; string allocation is not part of the fixed diagnostic. |
| Design | [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0005

[Lines 26–26](../../../../../src/runtime/update_pattern_detail.hpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:46438a41c48ba728d2feadac48141639d60d4818400cdf98b5cf05d0c146d2dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private runtime helper namespace. |
| inputs / outputs | No runtime input or output. |
| invariants | This delimiter changes visibility scope only and adds no monitored history or P4 authority. |
| ownership | No object ownership is introduced. |
| failure | No explicit runtime failure path. |
| cost | No algorithmic runtime cost. |
| Design | [src/runtime/update_pattern_detail.hpp](../../../../../src/runtime/update_pattern_detail.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |
