# `tests/support/weighted_fixture.hpp` — block usage map

[Source](../../../../../tests/support/weighted_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1668d793176f9163de3e84448f3b6e5c50c692e98d079d4344c0ecf37abd877d`. 229 lines partitioned into 29 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/support/weighted_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Test-only exhaustive join oracle for Refactor.md §10.2. It enumerates full · [reviewed contract](#b0001) |
| [B0002 · 24–26](../../../../../tests/support/weighted_fixture.hpp#L24) | Callable definition: inline void check(bool condition, const std::string& message) | calls std::runtime_error; guard inline void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 27–27](../../../../../tests/support/weighted_fixture.hpp#L27) | Callable definition: inline Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 28–30](../../../../../tests/support/weighted_fixture.hpp#L28) | Callable definition: inline PhysicalOptions options(bool indexed) | calls s04_runtime::options; returns indexed ? s04_runtime::options() : PhysicalOptions{} · [reviewed contract](#b0004) |
| [B0005 · 31–32](../../../../../tests/support/weighted_fixture.hpp#L31) | Explanatory comments or spacing. | source comment (unverified): // Hidden native variables force sum-over-witnesses before parent propagation. · [reviewed contract](#b0005) |
| [B0006 · 33–47](../../../../../tests/support/weighted_fixture.hpp#L33) | Callable definition: inline PhysicalPlan path(bool indexed) | calls planner::lower_tree, options; returns planner::lower_tree(catalog,query,tree,options(indexed)); source comment (unverified): // Hidden native variables force sum-over-witnesses before parent propagation. · [reviewed contract](#b0006) |
| [B0007 · 48–50](../../../../../tests/support/weighted_fixture.hpp#L48) | Explanatory comments or spacing. | source comment (unverified): // G(x,z) must sum its full-scope products to parent key x. Both child scopes · [reviewed contract](#b0007) |
| [B0008 · 51–69](../../../../../tests/support/weighted_fixture.hpp#L51) | Callable definition: inline PhysicalPlan generalized(bool indexed) | calls planner::lower_tree, options; returns planner::lower_tree(catalog,query,tree,options(indexed)); source comment (unverified): // G(x,z) must sum its full-scope products to parent key x. Both child scopes · [reviewed contract](#b0008) |
| [B0009 · 70–72](../../../../../tests/support/weighted_fixture.hpp#L70) | Explanatory comments or spacing. | source comment (unverified): // One R(y) update changes several Q(x,y,z) rows sharing parent key x. Their · [reviewed contract](#b0009) |
| [B0010 · 73–89](../../../../../tests/support/weighted_fixture.hpp#L73) | Callable definition: inline PhysicalPlan fanout(bool indexed, std::optional&lt;std::uint64_t&gt; structural_limit={}) | calls options, planner::lower_tree; returns planner::lower_tree(catalog,query,tree,configured); source comment (unverified): // One R(y) update changes several Q(x,y,z) rows sharing parent key x. Their · [reviewed contract](#b0010) |
| [B0011 · 90–90](../../../../../tests/support/weighted_fixture.hpp#L90) | Explanatory comments or spacing. |  |
| [B0012 · 91–101](../../../../../tests/support/weighted_fixture.hpp#L91) | Callable definition: inline PhysicalPlan unary(bool indexed, bool nullary=false, bool boolean=false) | calls planner::lower_tree, options; returns planner::lower_tree(catalog,query,tree,options(indexed)) · [reviewed contract](#b0012) |
| [B0013 · 102–102](../../../../../tests/support/weighted_fixture.hpp#L102) | Explanatory comments or spacing. |  |
| [B0014 · 103–105](../../../../../tests/support/weighted_fixture.hpp#L103) | Callable definition: inline std::uint64_t add(std::uint64_t a, std::uint64_t b) | calls check; guard check(b&lt;=UINT64_MAX-a,"test oracle sum overflow");return a+b;; returns a+b · [reviewed contract](#b0014) |
| [B0015 · 106–108](../../../../../tests/support/weighted_fixture.hpp#L106) | Callable definition: inline std::uint64_t multiply(std::uint64_t a, std::uint64_t b) | calls check; guard check(!a \|\| b&lt;=UINT64_MAX/a,"test oracle product overflow");return a*b;; returns a*b · [reviewed contract](#b0015) |
| [B0016 · 109–114](../../../../../tests/support/weighted_fixture.hpp#L109) | Callable definition: inline Assignment assignment(const Row& row, const auto& scope) | calls check, size, emplace; guard check(row.size()==scope.size(),"test oracle row width");; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 115–117](../../../../../tests/support/weighted_fixture.hpp#L115) | Callable definition: inline Row project(const Assignment& value, const auto& scope) | calls push_back, at; returns row; growth push_back; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 118–120](../../../../../tests/support/weighted_fixture.hpp#L118) | Explanatory comments or spacing. | source comment (unverified): // Exhaustive natural join of complete assignments. This does not use runtime · [reviewed contract](#b0018) |
| [B0019 · 121–132](../../../../../tests/support/weighted_fixture.hpp#L121) | Callable definition: inline Assignments join(const Assignments& a, const Assignments& b) | calls emplace, add, multiply; returns result; growth emplace; 3 loop sites; source comment (unverified): // Exhaustive natural join of complete assignments. This does not use runtime · [reviewed contract](#b0019) |
| [B0020 · 133–138](../../../../../tests/support/weighted_fixture.hpp#L133) | Type/record definition: struct ExpectedRow |  · [reviewed contract](#b0020) |
| [B0021 · 139–139](../../../../../tests/support/weighted_fixture.hpp#L139) | Type/record definition: struct ExpectedNode |  · [reviewed contract](#b0021) |
| [B0022 · 140–140](../../../../../tests/support/weighted_fixture.hpp#L140) | Type/record definition: struct Expected |  · [reviewed contract](#b0022) |
| [B0023 · 141–143](../../../../../tests/support/weighted_fixture.hpp#L141) | Explanatory comments or spacing. | source comment (unverified): // Enumerate all subtree witness assignments, then project and sum. Candidate · [reviewed contract](#b0023) |
| [B0024 · 144–194](../../../../../tests/support/weighted_fixture.hpp#L144) | Callable definition: inline Expected recompute(const CompiledProgram& plan, const Inputs& inputs) | calls resize, nodes, size, route; returns result; result; growth emplace, insert, push_back, resize; 13 loop sites; source comment (unverified): // Enumerate all subtree witness assignments, then project and sum. Candidate · [reviewed contract](#b0024) |
| [B0025 · 195–195](../../../../../tests/support/weighted_fixture.hpp#L195) | Explanatory comments or spacing. |  |
| [B0026 · 196–211](../../../../../tests/support/weighted_fixture.hpp#L196) | Callable definition: inline void compare(const w::Snapshot& actual, const Expected& expected) | calls check, size, push_back, emplace; guard check(actual.root.value==expected.root,"root differs from exhaustive weighted join");; growth emplace, push_back; 4 loop sites · [reviewed contract](#b0026) |
| [B0027 · 212–214](../../../../../tests/support/weighted_fixture.hpp#L212) | Explanatory comments or spacing. | source comment (unverified): // Keep the model inputs separate from the runtime. Compare every row/message · [reviewed contract](#b0027) |
| [B0028 · 215–228](../../../../../tests/support/weighted_fixture.hpp#L215) | Type/record definition: struct Model | returns epoch; source comment (unverified): // Keep the model inputs separate from the runtime. Compare every row/message · [reviewed contract](#b0028) |
| [B0029 · 229–229](../../../../../tests/support/weighted_fixture.hpp#L229) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::weighted_test · [reviewed contract](#b0029) |

## B0001

[Lines 1–23](../../../../../tests/support/weighted_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Inputs =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain oracle input weights by native plan-node ID. |
| inputs / outputs | Vector element is map&lt;Row,uint64&gt;; positive stored weights represent native local multiplicities. |
| invariants | Indices are NodeId, not physical TableId or distinct occurrence table numbers; generalized node inputs stay empty. |
| ownership | Vector/maps/rows own ordinary deep-copy data independent of runtime storage. |
| failure | Container allocation/copy failures propagate; aliases provide no admission or overflow handling by themselves. |
| cost | Deep row-key copies and O(log rows) ordered-map access; no native funding. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

```text
using Assignment =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a complete variable-to-scalar valuation. |
| inputs / outputs | Ordered map&lt;VariableId,Value&gt; represents compatible equality bindings. |
| invariants | Each variable has one value; keys are semantic variable IDs from the admitted plan. |
| ownership | Ordinary map and Value payload own their bytes; copying strings deep-copies. |
| failure | Container allocation/copy failures propagate; aliases provide no admission or overflow handling by themselves. |
| cost | Per-variable node allocation/copy and ordered comparisons. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

```text
using Assignments =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect exhaustive full valuations with summed uint64 witness weights. |
| inputs / outputs | Map&lt;Assignment,uint64&gt; groups equal full assignments. |
| invariants | Bounded test weights only; explicit native overflow tests do not rely on this uint64 oracle. |
| ownership | Deeply owning ordinary nested maps, not native tuple handles. |
| failure | Container allocation/copy failures propagate; aliases provide no admission or overflow handling by themselves. |
| cost | Potential Cartesian/exponential growth with deep assignment-key comparisons/copies. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

```text
using Counts =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Aggregate projected row multiplicities for the independent oracle. |
| inputs / outputs | Map&lt;Row,uint64&gt; groups ordered output/separator fields. |
| invariants | Order/repetition in Row matter; scalar equality/type distinguishes keys. |
| ownership | Ordinary owning Row/scalar map, independent of accounted native snapshots. |
| failure | Container allocation/copy failures propagate; aliases provide no admission or overflow handling by themselves. |
| cost | O(log distinct rows) map operations plus scalar comparison/copy. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 24–26](../../../../../tests/support/weighted_fixture.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void check(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a weighted oracle mismatch with a test diagnostic. |
| inputs / outputs | False throws runtime_error(message); true returns. |
| invariants | The const std::string argument can already allocate when called with a literal, even on success; not an allocation-free assertion seam. |
| ownership | Borrows message during call; exception construction owns its diagnostic. |
| failure | Assertion or message allocation errors propagate; no native repair/rollback. |
| cost | Branch plus any argument string construction; ordinary exception/unwind on false. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 27–27](../../../../../tests/support/weighted_fixture.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Value n(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the int64 scalar alternative explicitly. |
| inputs / outputs | Returns Value from signed int64. |
| invariants | Does not parse text or coerce to Boolean/date/decimal. |
| ownership | Return owns inline scalar value. |
| failure | No explicit failure path for this scalar alternative. |
| cost | Fixed variant/scalar construction. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 28–30](../../../../../tests/support/weighted_fixture.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalOptions options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose actual indexed test storage limits or default ordered storage options. |
| inputs / outputs | indexed true delegates to s04_runtime::options, false returns default PhysicalOptions. |
| invariants | Options are descriptive until lower_tree/native admission; this does not create a work allowance itself. |
| ownership | Returns owning options; no borrowed runtime state. |
| failure | Option construction/copy failures propagate according to actual members. |
| cost | Fixed finite option setup; physical plan/native setup is separate. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 31–32](../../../../../tests/support/weighted_fixture.hpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L32:sha256:779a463994159fe55ace6ea7fdee4562a85e84f4bf182e4777f8c35f41c2ae74
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Hidden native variables force sum-over-witnesses before parent propagation. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 33–47](../../../../../tests/support/weighted_fixture.hpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan path(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a hidden-witness native chain for weighted message tests. |
| inputs / outputs | p(x,y)→q(y,z)→r(z), projected head x. |
| invariants | Hidden y/z witnesses must be summed before parent propagation; real tree lowerer validates scope/occurrence structure. |
| ownership | Local Catalog/Query/tree own ordinary metadata; returned PhysicalPlan retains actual immutable compiler control. |
| failure | Allocation/lowering/validation failures propagate before a plan is returned; no fake proof or runtime mutation. |
| cost | Small fixed source/tree construction and actual lowering. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 48–50](../../../../../tests/support/weighted_fixture.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L50:sha256:afa73817d66718e03dbbcbf3e993436353af25194d13d0a1af93a4fcd09456a0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: G(x,z) must sum its full-scope products to parent key x. Both child scopes strictly contain G's scope, so this also catches separator/full-row confusion. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 51–69](../../../../../tests/support/weighted_fixture.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan generalized(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build nested generalized support scopes with strict-superset native children. |
| inputs / outputs | G(x) has p(x) and G(x,z); G(x,z) has r(x,z,r),s(x,z,s); head x. |
| invariants | Full-scope product and parent separator are different; tests can detect treating child full rows as parent keys. |
| ownership | Local Catalog/Query/tree own ordinary metadata; returned PhysicalPlan retains actual immutable compiler control. |
| failure | Allocation/lowering/validation failures propagate before a plan is returned; no fake proof or runtime mutation. |
| cost | Small fixed multi-node source/tree creation and lowering. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 70–72](../../../../../tests/support/weighted_fixture.hpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L72:sha256:5d0e6ad2a3c412448ee1a2b1b60f1fd23317e909b40bf334ecbdd1538664ccac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: One R(y) update changes several Q(x,y,z) rows sharing parent key x. Their queued numeric totals must reach a newly created G(x) candidate in order. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 73–89](../../../../../tests/support/weighted_fixture.hpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan fanout(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build queued fanout updates sharing a parent key. |
| inputs / outputs | G(x) children Q(x,y,z)→R(y) and B(x); optional structural_steps override. |
| invariants | When structural_limit is present indexed must be true; actual callers pass true. No optional dereference safety is claimed for arbitrary false+limit. |
| ownership | Local Catalog/Query/tree own ordinary metadata; returned PhysicalPlan retains actual immutable compiler control. |
| failure | Allocation/lowering/validation failures propagate before a plan is returned; no fake proof or runtime mutation. |
| cost | Fixed plan setup/lowering; real runtime fanout work occurs only when applied. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 91–101](../../../../../tests/support/weighted_fixture.hpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan unary(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build unary, nullary or Boolean-projected weighted cases. |
| inputs / outputs | One native r node; nullary removes x, Boolean removes unary head, otherwise head x. |
| invariants | Full native scope is retained even with empty projected head; empty-head witness multiplicity differs from ordinary Boolean set collapse. |
| ownership | Local Catalog/Query/tree own ordinary metadata; returned PhysicalPlan retains actual immutable compiler control. |
| failure | Allocation/lowering/validation failures propagate before a plan is returned; no fake proof or runtime mutation. |
| cost | Small fixed DTO construction and actual tree lowering. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 103–105](../../../../../tests/support/weighted_fixture.hpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::uint64_t add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound oracle sums to representable uint64 weights. |
| inputs / outputs | Requires b&lt;=UINT64_MAX-a then returns a+b. |
| invariants | Small-weight fixtures satisfy the bound; this is not arbitrary-precision overflow reference coverage. |
| ownership | Only scalar inputs/return; message construction remains ordinary test work. |
| failure | check rejects overflow with runtime_error; allocation for diagnostic can also fail. |
| cost | Fixed arithmetic/branch plus ordinary diagnostic argument construction. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 106–108](../../../../../tests/support/weighted_fixture.hpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::uint64_t multiply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound oracle products to uint64 without division by zero. |
| inputs / outputs | Requires !a or b&lt;=UINT64_MAX/a then returns a*b. |
| invariants | Zero times any b is admitted; multiplication happens only after the overflow precondition. |
| ownership | Inline scalar values only. |
| failure | Overflow assertion/message allocation propagates; not a native overflow exception mapper. |
| cost | Fixed arithmetic/short-circuit/division for nonzero a plus diagnostic argument construction. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 109–114](../../../../../tests/support/weighted_fixture.hpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Assignment assignment(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy row fields into variable-indexed oracle bindings. |
| inputs / outputs | Checks row/scope widths, iterates scope order and emplaces each corresponding Value. |
| invariants | Scope must be ordered unique admitted variable IDs; width equality alone is not semantic row admission. |
| ownership | Returned ordinary map deep-owns values after source Row expires. |
| failure | Width assertion or ordinary node/string-copy allocation failures propagate. |
| cost | O(fields log fields) map insertions and scalar/string copies. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 115–117](../../../../../tests/support/weighted_fixture.hpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Row project(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy selected variables into an ordered ordinary row. |
| inputs / outputs | Looks up every scope variable with at and appends Value, preserving requested order/repetition. |
| invariants | All requested bindings must exist; this is projection of complete assignments rather than a native tuple layout conversion. |
| ownership | Result owns deep ordinary Value copies; Assignment is borrowed synchronously. |
| failure | Missing variable throws out_of_range; vector/string allocation failures propagate. |
| cost | O(fields log assignment-size) lookups plus vector growth/scalar byte copies. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 118–120](../../../../../tests/support/weighted_fixture.hpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L120:sha256:7a9a07fa3cbe2c42ec0704843766cc4c08df67f7a9da045e83abdb7b8d03747e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Exhaustive natural join of complete assignments. This does not use runtime child caches, incremental messages, native indices or contribution replace. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 121–132](../../../../../tests/support/weighted_fixture.hpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Assignments join(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute an exhaustive natural join of complete weighted assignments. |
| inputs / outputs | For each left/right pair copies left, merges right bindings rejecting conflicts, checked-multiplies weights and checked-sums matching full assignments. |
| invariants | Uses no incremental child cache, queue, native index or contribution replacement; this algebraic path provides independence within bounded uint64 range. |
| ownership | All intermediate/returned nested maps and Value payloads are ordinary deep owners. |
| failure | Allocation/asserted numeric overflow propagates; private partially built result is discarded, input maps stay const. |
| cost | Cartesian pair enumeration with deep map copies/merges and ordered-map aggregation; may be exponential over query inputs and is intentionally not optimized runtime work. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 133–138](../../../../../tests/support/weighted_fixture.hpp#L133); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExpectedRow
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own expected per-full-row weighted support metadata. |
| inputs / outputs | local/subtree counts, ordered child weights, supported-positive-child count and default value equality. |
| invariants | Children order follows admitted shape.children; zero subtree candidates remain observable, supported counts only nonzero children. |
| ownership | Owns ordinary child vector, scalar counts; copies allocate for child payload. |
| failure | No automatic numeric validation; vector copy/allocation can throw. |
| cost | O(child count) copy/compare, no native account or key sharing. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 139–139](../../../../../tests/support/weighted_fixture.hpp#L139); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExpectedNode
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain independent expected row records and separator messages. |
| inputs / outputs | records maps full Row to ExpectedRow; messages maps separator Row to weight. |
| invariants | Full rows and separator keys have different scopes and must not be interchanged. |
| ownership | Both ordinary maps deep-own row/scalar/child data. |
| failure | Container copies/insertions can throw; this is an editable oracle DTO. |
| cost | Storage proportional to retained oracle rows/messages with ordered comparisons/copies. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 140–140](../../../../../tests/support/weighted_fixture.hpp#L140); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Expected {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the complete independently recomputed node result and root witness count. |
| inputs / outputs | nodes indexed by dense compiled NodeId; root scalar is the nullary root message or constant route count. |
| invariants | Valid admitted connected tree provides dense reachable IDs; no arbitrary graph validation here. |
| ownership | Ordinary node vector/maps deeply own all expected state. |
| failure | Copy/allocation failures propagate; fields alone provide no typed runtime authority. |
| cost | Deep container copy proportional to oracle state, including all row/message keys. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 141–143](../../../../../tests/support/weighted_fixture.hpp#L141); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L143:sha256:c4d7b01d8d79e4ca5e0c99cc8262f1da85a785c01ab684bb4ba6f52be79734d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Enumerate all subtree witness assignments, then project and sum. Candidate union is checked separately so rows with zero product remain observable. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 144–194](../../../../../tests/support/weighted_fixture.hpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Expected recompute(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute every weighted row/cache/message from complete subtree assignments. |
| inputs / outputs | Builds root-first traversal, processes reverse order, joins native local assignments with child subtrees, projects/sums full scopes and separators, then separately enumerates candidates and cached children. |
| invariants | Requires valid admitted dense reachable tree and matching node-indexed positive native inputs. Generalized candidate union preserves zero-product candidates; constant routes return0/1. No incremental numerical cache supplies expected weights. |
| ownership | Return/intermediate nested maps, candidate sets, separator vectors and row exports own ordinary copies; plan/inputs are borrowed. |
| failure | Checked uint64 add/multiply, map at/preconditions and ordinary allocations can fail; no runtime mutation or recovery. |
| cost | Potential exponential witness join storage/time plus repeated projection/search/sort-map work over all nodes; no claim of linear native complexity. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::vector<NodeId> order{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose a children-before-parent recomputation order. |
| inputs / outputs | Expands admitted root-first tree then consumes reverse iterators. |
| invariants | Each dense reachable native/generalized node appears once in the valid compiled tree. |
| ownership | Private owning vectors/maps/sets within recompute; no native key/owner retained. |
| failure | Trusted admitted shapes plus ordinary allocation/overflow/lookup failures; entire private recomputation unwinds on failure. |
| cost | O(nodes+edges) traversal and vector growth. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

```text
Counts full;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Aggregate complete subtree witnesses into full rows and parent-separator messages. |
| inputs / outputs | Projects each assignment onto shape.scope and intersection with parent scope; checked-sums weights. |
| invariants | Hidden variable witnesses sum before propagation; root separator is empty. |
| ownership | Private owning vectors/maps/sets within recompute; no native key/owner retained. |
| failure | Trusted admitted shapes plus ordinary allocation/overflow/lookup failures; entire private recomputation unwinds on failure. |
| cost | Full witness scans plus repeated separator construction/lookups and map/string copies. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::set<Row> candidates;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check candidate membership independently of positive subtree support. |
| inputs / outputs | Native uses all input keys; generalized unions all positive child message keys; then computes each row's local/subtree/child/support values. |
| invariants | A candidate can have zero product, so positive full witness enumeration alone cannot define expected record membership. |
| ownership | Private owning vectors/maps/sets within recompute; no native key/owner retained. |
| failure | Trusted admitted shapes plus ordinary allocation/overflow/lookup failures; entire private recomputation unwinds on failure. |
| cost | Set unions, full/child map lookups and ordinary row/key copies. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 196–211](../../../../../tests/support/weighted_fixture.hpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void compare(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare actual weighted snapshot records/messages to exhaustive expected values. |
| inputs / outputs | Checks root/node count, exports each actual record/key, rejects duplicates, builds ordinary numeric maps and compares exact values per node ID. |
| invariants | Actual numeric fields are observed only on the comparison side; independent Expected came from inputs/joins. Layout/funding of actual snapshots is not inferred from ordinary map ownership. |
| ownership | Snapshot retains actual native row/metadata owners during export; local comparison maps deep-own ordinary copies. |
| failure | Snapshot construction occurs at caller; export/allocation/assertion can throw without repairing or rolling back runtime. |
| cost | Full snapshot traversal plus O(log rows/messages) map operations and explicit scalar/key copies. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 212–214](../../../../../tests/support/weighted_fixture.hpp#L212); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L212-L214:sha256:fd92c5938b0bfc1212ad1972d7f76f786ba5e912139d40d308eff8b5ab7c53e2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Keep the model inputs separate from the runtime. Compare every row/message after every logical update, including updates that leave membership unchanged. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |

## B0028

[Lines 215–228](../../../../../tests/support/weighted_fixture.hpp#L215); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Model
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep independent oracle inputs beside one real weighted runtime owner. |
| inputs / outputs | Constructs WeightedRuntime from admitted plan/options and sizes Inputs to compiled node count; set drives one update then recomputes/compares. |
| invariants | Native runtime and ordinary model never share map keys. Only after runtime.apply succeeds is the ordinary input map updated. |
| ownership | WeightedRuntime deletes copy and transfers ownership on move; Inputs copy is deep ordinary storage. Composite is noncopyable via runtime. |
| failure | Ordinary model/assertion failure after successful native apply cannot roll back the committed native epoch. |
| cost | Real runtime admission plus independent input vector; each update includes expensive exhaustive verification, not a production wrapper. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

```text
explicit Model(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a real weighted runtime and allocate an empty independent per-node input model. |
| inputs / outputs | Moves PhysicalPlan into runtime and sizes Inputs from runtime.structural_program().nodes().size. |
| invariants | Options/plan pass actual runtime initialization; a vector of oracle maps does not establish native authority. |
| ownership | Runtime owns its admitted account/state; Inputs owns ordinary empty map objects; plan argument follows handle move semantics. |
| failure | Native admission or vector allocation can throw before Model exists; completed runtime unwinds. |
| cost | Actual compiler/native setup plus O(nodes) empty ordinary map initialization. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

```text
w::Epoch set(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit a native weighted update then verify all state against the separate model. |
| inputs / outputs | Finds prior model weight, runtime.apply at sequence+1 with before/after counts, updates/erases model map, snapshots and compares exhaustive recompute, returns epoch. |
| invariants | Trusted native node/row and bounded sequences; no model mutation before apply succeeds. Post-apply ordinary insertion/export/oracle failure is not joint strong rollback. |
| ownership | Input Row is local owning value, native apply copies/adopts per API, model insert deep-copies separately; returned Epoch owns its documented fields. |
| failure | Native failure leaves model unchanged; later ordinary/assertion failures propagate after native success and may leave model partially published. |
| cost | Actual native update + ordinary map change + full snapshot and potentially exponential oracle recomputation. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [tests/unit/weighted_messages_test.cpp](../../../../../tests/unit/weighted_messages_test.cpp), [tests/unit/weighted_limits_test.cpp](../../../../../tests/unit/weighted_limits_test.cpp), [tests/unit/weighted_oracle_driver.cpp](../../../../../tests/unit/weighted_oracle_driver.cpp), [tests/reference/weighted_oracle.py](../../../../../tests/reference/weighted_oracle.py), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md](../../../../../Refactor.md), [docs/code_review.md](../../../../code_review.md) |

## B0029

[Lines 229–229](../../../../../tests/support/weighted_fixture.hpp#L229); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L229-L229:sha256:e3e0d6ed285ee7d6b125a50e4e786e09eff84b033609cd7064be9e446b1450b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in weighted_fixture.hpp: namespace crown::weighted_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/weighted_fixture.hpp](../../../../../tests/support/weighted_fixture.hpp), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/code_review.md](../../../../code_review.md) |
