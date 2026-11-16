# `tests/reference/evaluator.cpp` — block usage map

[Source](../../../../../tests/reference/evaluator.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1fdb300c522f70d16deb76e5ab3ebb0001eed2d8fb2561fa90be9941c44830fb`. 80 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/reference/evaluator.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 11–47](../../../../../tests/reference/evaluator.cpp#L11) | Callable definition: Relation evaluate(const Catalog& catalog, const Query& query, const Database& database) | calls validate, validate_database, Assignment, size; returns {}; answer; growth insert, push_back; 6 loop sites; source comment (unverified): // Expand compatible assignments one occurrence at a time. Keep all physical · [reviewed contract](#b0002) |
| [B0003 · 48–48](../../../../../tests/reference/evaluator.cpp#L48) | Explanatory comments or spacing. |  |
| [B0004 · 49–53](../../../../../tests/reference/evaluator.cpp#L49) | Callable definition: Session::Session(Catalog catalog, Query query, Database database) : catalog_(std::move(catalog)), query_(std::move(query)), datab… | calls catalog_, std::move, query_, database_ · [reviewed contract](#b0004) |
| [B0005 · 54–54](../../../../../tests/reference/evaluator.cpp#L54) | Callable definition: Relation Session::snapshot() const | calls evaluate; returns evaluate(catalog_, query_, database_) · [reviewed contract](#b0005) |
| [B0006 · 55–55](../../../../../tests/reference/evaluator.cpp#L55) | Explanatory comments or spacing. |  |
| [B0007 · 56–79](../../../../../tests/reference/evaluator.cpp#L56) | Callable definition: CommittedReferenceEpoch Session::apply(const PhysicalSetUpdate& update) | calls max, Error, validate_row, snapshot; returns epoch; growth insert; source comment (unverified): // Commit only after both evaluation and all owned output allocations succeed. · [reviewed contract](#b0007) |
| [B0008 · 80–80](../../../../../tests/reference/evaluator.cpp#L80) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::reference · [reviewed contract](#b0008) |

## B0001

[Lines 1–10](../../../../../tests/reference/evaluator.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:a5db61c13182a6c99eb580a2c3f967ce4ad073a6c2aa6ef7a4076f3fec957d73
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare evaluator.cpp: include "evaluator.hpp", "crown/api/error.hpp", &lt;algorithm&gt;, &lt;iterator&gt;, &lt;limits&gt;, &lt;optional&gt;, &lt;utility&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/semantics.md](../../../../semantics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–47](../../../../../tests/reference/evaluator.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation evaluate(const Catalog& catalog,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute the literal materializing set-CQ definition used by reference checks and the oracle CLI. |
| inputs / outputs | Validates query/database, expands compatible full assignments occurrence by occurrence, applies constants/repeated-variable equality and projects into an exact owning Relation. |
| invariants | Keeps all physical row witnesses until final set projection. Contradiction is empty; empty conjunction/head gives the declared nullary semantics. No native support/planner/cursor implementation evaluates the join, though model validation is shared. |
| ownership | Borrows catalog/query/database; assignment vectors and final rows own copied Values. Returned relation does not borrow input rows. |
| failure | Validation, optional-bound-variable, allocation and scalar-copy failures propagate without a fallback result. |
| cost | Full prefix-assignment×table-row expansion and repeated map-free vector copies may be exponential; final ordered-set projection adds comparison/storage work. This is the slow oracle, not the incremental engine. |
| Design | [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0004

[Lines 49–53](../../../../../tests/reference/evaluator.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Session::Session(Catalog catalog,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the independent reference session inputs and validate the initial set database. |
| inputs / outputs | Takes catalog/query/database by value, moves them into members and validates query plus database; sequence starts at0. |
| invariants | Construction exposes no session if validation fails. It has no native program, journal, sink, work grant or delayed cursor state. |
| ownership | Owns ordinary copies/moves of all supplied semantic data; passing lvalues may copy before entry. |
| failure | Input copy/validation allocation/domain failures unwind members normally; no status translation is promised. |
| cost | Input copy/move cost plus complete model/database validation, separate from each later full evaluation. |
| Design | [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md) |

## B0005

[Lines 54–54](../../../../../tests/reference/evaluator.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation Session::snapshot() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute an owning current answer from the reference database. |
| inputs / outputs | Calls evaluate with this session’s catalog/query/database and returns the full Relation. |
| invariants | Does not read a cached native answer or advance sequence; every call reevaluates the literal definition. |
| ownership | Returned Values/rows own their storage independently of the session; inputs remain borrowed during evaluation. |
| failure | Evaluation/allocation errors propagate while current session state remains unchanged. |
| cost | Full materializing evaluation cost on every snapshot, not constant-time observation. |
| Design | [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md) |

## B0007

[Lines 56–79](../../../../../tests/reference/evaluator.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CommittedReferenceEpoch Session::apply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical set update atomically in the deliberately copying reference session. |
| inputs / outputs | Checks next nonwrapping sequence and row shape, computes before, copies the complete Database, applies insert/erase, reevaluates after, builds added/removed sets and owning epoch, then swaps database and publishes sequence. |
| invariants | Duplicate insert/absent erase may be physical no-ops but still consume the contiguous epoch. Candidate constraints and all owned output allocations finish before publication. Whole-state copying belongs to this independent oracle, not the native transaction design. |
| ownership | Owns candidate database and before/after/output relations locally; final default-allocator table-vector swap and sequence assignment publish the prepared result. |
| failure | Invalid sequence/operation/row/candidate constraints or allocation aborts before commit. The function adds no catch/retry/undo framework. |
| cost | Copies all physical tables, evaluates twice and computes ordered set differences plus owning output copies per update; intentionally expensive reference work. |
| Design | [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/semantics.md §Updates, epochs and failure atomicity](../../../../semantics.md) |

## B0008

[Lines 80–80](../../../../../tests/reference/evaluator.cpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L80:sha256:e6b42e4915271f267594118fd022698431af47758d71d1b08d7db51a0d7f1921
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in evaluator.cpp: namespace crown::reference. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/semantics.md](../../../../semantics.md), [docs/code_review.md](../../../../code_review.md) |
