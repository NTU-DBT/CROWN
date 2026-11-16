# `tests/support/ranking_fixture.hpp` — block usage map

[Source](../../../../../tests/support/ranking_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `b8d493d9ad3c6dec53468eaeef40f60c9bca5df548a920dea2cdfc1f948d90a1`. 27 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../tests/support/ranking_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 7–7](../../../../../tests/support/ranking_fixture.hpp#L7) | Callable definition: inline void check(bool x,const char* s) | calls std::runtime_error; guard inline void check(bool x,const char* s){if(!x){throw std::runtime_error(s);}} · [reviewed contract](#b0002) |
| [B0003 · 8–8](../../../../../tests/support/ranking_fixture.hpp#L8) | Explanatory comments or spacing. | source comment (unverified): // Ordinary owning source/data DTOs; proof, candidate and runtime admission run later. · [reviewed contract](#b0003) |
| [B0004 · 9–9](../../../../../tests/support/ranking_fixture.hpp#L9) | Type/record definition: struct Fixture | source comment (unverified): // Ordinary owning source/data DTOs; proof, candidate and runtime admission run later. · [reviewed contract](#b0004) |
| [B0005 · 10–15](../../../../../tests/support/ranking_fixture.hpp#L10) | Callable definition: inline Fixture fixture() | calls ; returns f · [reviewed contract](#b0005) |
| [B0006 · 16–16](../../../../../tests/support/ranking_fixture.hpp#L16) | Explanatory comments or spacing. | source comment (unverified): // The actual checked optimum supplies authority; height/count are only assertions. · [reviewed contract](#b0006) |
| [B0007 · 17–25](../../../../../tests/support/ranking_fixture.hpp#L17) | Callable definition: inline planner::CandidateSnapshot candidates(const Fixture& f,std::size_t height=2,std::size_t count=3) | calls planner::ExactSearch::create, optimum, advance, check; guard for(std::size_t step=0;step&lt;100'000 && !exact.optimum();++step){const auto a=exact.advance({1000,{}…; returns provider.snapshot(); 2 loop sites; source comment (unverified): // The actual checked optimum supplies authority; height/count are only assertions. · [reviewed contract](#b0007) |
| [B0008 · 26–26](../../../../../tests/support/ranking_fixture.hpp#L26) | Callable definition: inline int shape(const FreeConnexTree& t) | calls at, check, size, contains; guard inline int shape(const FreeConnexTree& t){const auto& root=t.nodes.at(t.root-&gt;value);if(root.kind==…; returns 0; root.scope.contains(VariableId{0})?1:2 · [reviewed contract](#b0008) |
| [B0009 · 27–27](../../../../../tests/support/ranking_fixture.hpp#L27) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |

## B0001

[Lines 1–6](../../../../../tests/support/ranking_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:6eeda0869c05327b3c74f37736b1e72ecc2dd5d9cf469540b7ebd7b9733064fd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_fixture.hpp: include "crown/planner/ranking.hpp", "crown/planner/lower.hpp", &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 7–7](../../../../../tests/support/ranking_fixture.hpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void check(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a test assertion with the supplied ordinary diagnostic. |
| inputs / outputs | Returns for true, otherwise throws std::runtime_error(s). |
| invariants | A check result is test expectation, never typed admission/proof authority or an engine recovery instruction. |
| ownership | Input diagnostic pointer is borrowed synchronously; thrown exception owns its message. |
| failure | Message/exception allocation may itself fail, especially if used inside an armed new seam. Actual fault sweeps check outcomes after disarming. |
| cost | Fixed successful branch; failing path constructs an owning diagnostic and unwinds. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [tests/unit/ranking_contract_test.cpp](../../../../../tests/unit/ranking_contract_test.cpp), [tests/unit/ranking_empty_test.cpp](../../../../../tests/unit/ranking_empty_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 8–8](../../../../../tests/support/ranking_fixture.hpp#L8); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L8:sha256:64a39ae21055dd10a5217792f414629140cee24ba8b7871d733f9f759cddeb34
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Ordinary owning source/data DTOs; proof, candidate and runtime admission run later. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 9–9](../../../../../tests/support/ranking_fixture.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own ordinary source/query/data inputs for the literal R(x),S(x,y),T(y) Boolean test. |
| inputs / outputs | Catalog/query/database are editable owning DTOs with vectors/sets/strings, not compiled programs, checked minimum-height proofs or actual-owner statistics. |
| invariants | No custom special members: ordinary copies deep-copy nested metadata and Relation rows/strings; moves transfer those containers subject to their element semantics. This aggregate does not share all keys or admit rows by construction. |
| ownership | Owns independent ordinary input graphs; later ExactSearch/lowering/runtime admission copies or retains its own checked owners. |
| failure | Construction/copy allocation failures propagate; no fixture-level handler or fallback account. |
| cost | Payload cost follows metadata and rows, including set nodes and text bytes; copying is not universally constant or allocation-free. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [tests/unit/ranking_contract_test.cpp](../../../../../tests/unit/ranking_contract_test.cpp), [tests/unit/ranking_empty_test.cpp](../../../../../tests/unit/ranking_empty_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 10–15](../../../../../tests/support/ranking_fixture.hpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Fixture fixture()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the fixed three-relation Boolean chain with one witness. |
| inputs / outputs | R int64 x={1}; S int64(x,y)={(1,1)}; T int64 y={1}; variables x,y and three atoms follow dense table/variable IDs; query head remains empty. |
| invariants | Expected Boolean answer is true. DTO construction alone establishes no structural proof, source progress or native query account; consumer admission still runs. |
| ownership | Returns an ordinary owning Fixture; initializer strings/vectors/Relation nodes are independently allocated as needed. |
| failure | Ordinary metadata/row allocation failures propagate; no catch or hidden test skip. |
| cost | Fixed small fixture population with actual vector/set/string allocations; no search/runtime build until requested. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [tests/unit/ranking_contract_test.cpp](../../../../../tests/unit/ranking_contract_test.cpp), [tests/unit/ranking_empty_test.cpp](../../../../../tests/unit/ranking_empty_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 16–16](../../../../../tests/support/ranking_fixture.hpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L16:sha256:2db7a0a3f16cb65ee5666a3f52d97d8a8aaff1f19b8f9110c4e209c4e47781ba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: The actual checked optimum supplies authority; height/count are only assertions. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 17–25](../../../../../tests/support/ranking_fixture.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline planner::CandidateSnapshot candidates(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain genuine checked minimum-height authority and a complete retained alternative family for a finite fixture. |
| inputs / outputs | Creates ExactSearch with 50M producer/replay work, advances up to 100k quanta of 1000 until optimum, asserts requested height, creates CandidateProvider and advances up to 100k quanta until family_exhausted; asserts count only when nonzero then snapshots. |
| invariants | Only actual published VerifiedOptimum constructs provider authority. Requested height/count are assertions, not inputs that manufacture proof. count==0 disables only final count assertion; completion is still required. Resource/failure cannot silently become a partial accepted family. |
| ownership | Search/provider own copied admitted bindings/proofs; returned immutable Snapshot retains its actual prefix handles independently. Snapshot/candidate/proof copy shares their real immutable controls; default moves of those handles can leave source invalid. Creating snapshot itself allocates handle/event arrays. |
| failure | Failed proof/provider phase, exhausted guards, height/count mismatch or actual allocation throws through check/underlying APIs; no broad recovery or fallback fixture. |
| cost | Real finite exact search, independent replay, alternative enumeration/validation/canonicalization and snapshot admission; large explicit quantum guards are not timing bounds or O(1) fixture setup. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [tests/unit/ranking_contract_test.cpp](../../../../../tests/unit/ranking_contract_test.cpp), [tests/unit/ranking_empty_test.cpp](../../../../../tests/unit/ranking_empty_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 26–26](../../../../../tests/support/ranking_fixture.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline int shape(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify only the fixture's three known minimum-height root shapes. |
| inputs / outputs | Reads existing root via nodes.at; native root maps 0, otherwise requires one-variable generalized root and maps x to 1, the other singleton fixture root y to 2. |
| invariants | Requires nonempty admitted tree and the known x/y family. It does not validate a general tree, inspect all geometry or create a global structural key/proof. |
| ownership | Borrows tree; returns inline integer and retains no metadata. |
| failure | Absent/invalid root is outside fixture precondition; at/check can reject mismatched fixtures. No catch or automatic repair. |
| cost | Fixed root/scope checks and set contains, with no successful graph copy or allocation. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [tests/unit/ranking_contract_test.cpp](../../../../../tests/unit/ranking_contract_test.cpp), [tests/unit/ranking_empty_test.cpp](../../../../../tests/unit/ranking_empty_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 27–27](../../../../../tests/support/ranking_fixture.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_fixture.hpp: namespace c02_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |
