# `tests/support/session_checkpoint_test_fixture.hpp` — block usage map

[Source](../../../../../tests/support/session_checkpoint_test_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4d47fc93f307928eb50af8dbacf572e1f7289a42a5f026735cf5303f6c4c509c`. 119 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; controls preprocessing; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 18–18](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L18) | Callable definition: inline void check(bool value,const char* message) | calls std::runtime_error; guard inline void check(bool value,const char* message){if(!value)throw std::runtime_error(message);} · [reviewed contract](#b0002) |
| [B0003 · 19–19](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L19) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 20–27](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L20) | Callable definition: inline void grant(const QuerySession& session,bool indexed) | calls RuntimeTestProbe::index_work, check; guard check(indexed?(value && value-&gt;fresh_operations==1):!value,"session restore minted another indexed … · [reviewed contract](#b0004) |
| [B0005 · 28–28](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L28) | Explanatory comments or spacing. | source comment (unverified): // Native snapshot capture is separate from these ordinary deep row exports. · [reviewed contract](#b0005) |
| [B0006 · 29–33](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L29) | Callable definition: inline Relation rows(const QuerySession& session) | calls snapshot, check, insert, storage::export_row; guard for(const auto& value:snapshot.rows)check(result.insert(storage::export_row(value.values())).second…; returns result; growth insert; 1 loop sites; source comment (unverified): // Native snapshot capture is separate from these ordinary deep row exports. · [reviewed contract](#b0006) |
| [B0007 · 34–39](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L34) | Callable definition: inline Output difference(const Relation& before,const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 40–48](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L40) | Callable definition: inline Output finish(QuerySession& session) | calls step, commit, next_output, check; guard check(value-&gt;ordinal==++ordinal,"noncontiguous session output ordinal");; returns result; growth emplace; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 49–51](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L49) | Callable definition: inline void enqueue(QuerySession& session,const io::InputItem& item) | calls batch, check, empty; guard io::TransportBatch batch({item});check(session.enqueue(batch)==io::Admission::accepted && batch.emp… · [reviewed contract](#b0009) |
| [B0010 · 52–52](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L52) | Explanatory comments or spacing. | source comment (unverified): // Supported kinds are 0..5; plan admission is real, update/model data is ordinary. · [reviewed contract](#b0010) |
| [B0011 · 53–53](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L53) | Type/record definition: struct Case | source comment (unverified): // Supported kinds are 0..5; plan admission is real, update/model data is ordinary. · [reviewed contract](#b0011) |
| [B0012 · 54–100](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L54) | Callable definition: inline Case fixture(bool indexed,unsigned kind) | calls s04_runtime::options, planner::lower_tree, frontend::bind_sql, check; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(bound),"SQL fixture did not bind");; returns {planner::lower_tree(catalog,query,tree,options),{{1,TableId{0},SetOperation::insert,{std::int64_t{…; growth insert; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 101–105](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L101) | Callable definition: inline Relation oracle(const Case& fixture,const Database& database) | calls empty, insert, reference::evaluate, source_catalog; returns Relation{{Row{!database.tables\[0\].empty()}}}; result; growth insert; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 106–106](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L106) | Explanatory comments or spacing. | source comment (unverified): // Native commit precedes model/export assertions; later failure cannot roll it back. · [reviewed contract](#b0014) |
| [B0015 · 107–114](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L107) | Callable definition: inline Output step(QuerySession& session,const Case& fixture,Database& database,const PhysicalSetUpdate& update,DeltaMode mode) | calls oracle, insert, erase, enqueue; guard check(session.begin_next(),"session had no admitted event");const auto output=finish(session);; returns output; growth insert; source comment (unverified): // Native commit precedes model/export assertions; later failure cannot roll it back. · [reviewed contract](#b0015) |
| [B0016 · 115–118](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L115) | Callable definition: template&lt;class Action&gt; void rejected(Action action) | calls action, check; guard check(failed,"invalid session checkpoint accepted"); · [reviewed contract](#b0016) |
| [B0017 · 119–119](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L119) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::session_checkpoint_test · [reviewed contract](#b0017) |

## B0001

[Lines 1–17](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:23d37efe0c95f51cd0a9a7c781c2cfcc88d56f56258922d43704e71992e1fc52
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_checkpoint_test_fixture.hpp: include "crown/runtime/session_checkpoint.hpp", "crown/frontend/normalize.hpp", "indexed_runtime_fixture.hpp", "evaluator.hpp", "index_allocation.hpp", "runtime_probe.hpp", &lt;iostream&gt;, &lt;sstream&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;thread&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–18](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void check(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the fixture's expected native/session behavior. |
| inputs / outputs | False throws runtime_error from borrowed literal diagnostic; true returns. |
| invariants | Does not turn arbitrary errors into expected rejection or construct native authority. |
| ownership | No retained message reference; exception owns its diagnostic when constructed. |
| failure | Assertion/message allocation failures propagate to the test boundary. |
| cost | Fixed success branch, ordinary exception allocation/unwind on failure. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 19–19](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Output=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a set of expected signed rows for fixture comparisons. |
| inputs / outputs | Each key is pair&lt;SetOperation,Row&gt;; equal operation/row duplicates collapse. |
| invariants | A signed set is not a weighted multiset or an ordered delivery log; finish separately asserts per-epoch ordinal uniqueness. |
| ownership | Ordinary map-node/Row/scalar storage is deep-owned and copied on set copy; no native account retention. |
| failure | Insert/copy/export allocation failures propagate. |
| cost | O(log N) set insertion plus row/scalar comparison and explicit ordinary copies. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 20–27](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void grant(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that indexed native restoration did not mint a fresh aggregate work allowance. |
| inputs / outputs | Testing build reads RuntimeTestProbe::index_work; indexed expects fresh_operations==1, ordered expects absent. Non-testing build is an explicit no-op. |
| invariants | Numeric private probe observation is not total CPU, bytes, memory coverage or public capability. It examines the actual session owner. |
| ownership | Borrows session synchronously and returns no owned native data. |
| failure | Only a failed fixture assertion throws; compile-time-disabled branch performs no check. |
| cost | Fixed flag/probe/optional read and assertion; actual owner admission cost occurred elsewhere. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 28–28](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:486e4078826341a4c9ad51ad9189b56120b91417266489568f732f357ec0502a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Native snapshot capture is separate from these ordinary deep row exports. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 29–33](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Relation rows(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a session's current result into an ordinary set for comparison. |
| inputs / outputs | Obtains an owning native snapshot, exports each row and rejects duplicate result rows. |
| invariants | Snapshot ownership/funding belongs to the actual native owner; the exported set is a separate ordinary copy, not an accounted view. |
| ownership | Returned Relation owns all exported rows/scalars; snapshot owner remains local until export completes. |
| failure | Snapshot account/work admission, ordinary export/insertion or assertion can fail; session data is not rolled back by this read helper. |
| cost | Snapshot capture plus O(rows log rows) insertions and scalar copies/comparisons; ordinary exports are outside native-account counts. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 34–39](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Output difference(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the signed set delta by the mathematical before/after definition. |
| inputs / outputs | Rows only in before become erases; rows only in after become inserts. |
| invariants | Ordinary set semantics mean duplicate native answers are checked elsewhere; operation identity distinguishes equal insert/erase keys. |
| ownership | Borrows two Relations and returns a deep-owning ordinary Output. |
| failure | Set insertion/copy failures propagate without native state changes. |
| cost | O((B+A) log(max(B,A))) membership checks plus copied delta rows; not an incremental oracle. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 40–48](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Output finish(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare, commit and fully drain one active physical epoch. |
| inputs / outputs | Steps until prepared, commits, then requires one-based contiguous output ordinals and unique signed rows while exporting. |
| invariants | Loop has no independent step/time bound; engine grants govern progress. Commit precedes ordinary result allocation/assertions, so later failure cannot undo the epoch. |
| ownership | Returns owning ordinary signed rows; native output tuples are consumed under their actual session/cursor lifetime. |
| failure | Native step/commit/read failures propagate. Export/allocation/assertion after commit does not promise joint rollback. |
| cost | All engine work through preparation/commit plus linear output drain, O(log rows) set insertion and ordinary scalar copies. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 49–51](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void enqueue(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exactly one typed input item through the real session queue. |
| inputs / outputs | Copies the item into TransportBatch and requires accepted plus batch.empty after consumption. |
| invariants | Typed DTO construction alone is not source authority; actual session admission establishes queue/source checks. |
| ownership | Batch owns an ordinary input copy until consumed; session retains its actual admitted representation. |
| failure | Copy/admission/assertion failures propagate; only accepted-and-empty meets the helper's contract. |
| cost | One batch/vector/input copy plus native admission validation and possible accounted queue work. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 52–52](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L52:sha256:0f698949c138e41b67db03de81d0ccc204e651102c9d26c551d929e859dc0a15
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Supported kinds are 0..5; plan admission is real, update/model data is ordinary. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 53–53](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Case
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one real lowered plan and its finite physical update trace. |
| inputs / outputs | plan, four updates and kind select fixture and oracle behavior; callers support kinds 0 through 5. |
| invariants | Editable update/kind metadata is not a proof/source capability. PhysicalPlan is the real admitted compiler handle. |
| ownership | Plan copies share its immutable control; vector/Rows copy deeply. Default moves follow those members. |
| failure | Source/lowering/copy failures happen during construction; no runtime work is implied by holding the DTO. |
| cost | Small trace storage plus actual lowering costs; copying rows/strings is not a cheap shared-key operation. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 54–100](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Case fixture(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build six bounded session/checkpoint scenarios with real lowering/admission. |
| inputs / outputs | indexed selects finite indexed limits; kind 0 unary, 1 self-join, 2 disconnected maintenance, 3 nullary, 4 normalized filter, 5 normalized EXISTS. |
| invariants | Trusted supported kinds are 0..5. kind&gt;=4 selects SQL, but oracle special-cases only 4/5; arbitrary other kinds are not a general fixture API. |
| ownership | Returns owning plan handle and independent ordinary update vector; temporary Catalog/Query/tree/normalized DTOs die afterward. |
| failure | Bind/normalize assertions, lowering/validation and ordinary allocations propagate; no fake typed proof is fabricated. |
| cost | Bounded source construction plus real compiler normalization/tree admission; each trace owns four deep row copies. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

```text
if(kind==1)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up a two-occurrence self-join on the same e(x,y) table. |
| inputs / outputs | Generalized root {z}, native scopes {x,z}/{z,y}, head x,z,y; inserts (1,2),(2,3),(2,2), then erases (1,2). |
| invariants | Both occurrences receive physical-table changes; this exercises joins/duplicates and generalized support, not two independent source tables. |
| ownership | Only local owning compiler-source DTOs; real lower_tree/lower_normalized returns the retained plan. |
| failure | Construction/allocation/compiler validation failures propagate before a returned Case. |
| cost | Bounded fixture DTO copies and actual lowering, independent of measured runtime update quanta. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

```text
if(kind==2)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up a disconnected r(x) × s(y) scenario. |
| inputs / outputs | Nullary generalized root with two native children; +r1,+s7,+r2,-s7 trace. |
| invariants | Session mode is maintenance in journal fixtures; oracle still checks complete Cartesian current rows while expected signed delivery is empty. |
| ownership | Only local owning compiler-source DTOs; real lower_tree/lower_normalized returns the retained plan. |
| failure | Construction/allocation/compiler validation failures propagate before a returned Case. |
| cost | Bounded fixture DTO copies and actual lowering, independent of measured runtime update quanta. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

```text
if(kind==3)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up a native nullary relation and empty head. |
| inputs / outputs | Trace inserts empty row twice, erases, then inserts again. |
| invariants | Second insertion is a set no-op; nullary truth is zero/one empty row, not a scalar Boolean output. |
| ownership | Only local owning compiler-source DTOs; real lower_tree/lower_normalized returns the retained plan. |
| failure | Construction/allocation/compiler validation failures propagate before a returned Case. |
| cost | Bounded fixture DTO copies and actual lowering, independent of measured runtime update quanta. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

```text
if(kind>=4)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up normalized SQL output/filter semantics. |
| inputs / outputs | Kind4 SELECT DISTINCT x WHERE x&gt;=0; kind5 SELECT EXISTS, with actual bind/normalize results and a native core tree. |
| invariants | Normalized evaluator semantics are tested by manual predicate/Boolean oracle; supported kind range remains 4/5. |
| ownership | Only local owning compiler-source DTOs; real lower_tree/lower_normalized returns the retained plan. |
| failure | Construction/allocation/compiler validation failures propagate before a returned Case. |
| cost | Bounded fixture DTO copies and actual lowering, independent of measured runtime update quanta. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

```text
Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},{{VariableId{0},"x"}},false};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up the direct unary kind0 plan. |
| inputs / outputs | One r(x) native root with head x and ordinary +1,+2,-1,-2 trace. |
| invariants | This branch is for trusted kind0; no general kind validation is added. |
| ownership | Only local owning compiler-source DTOs; real lower_tree/lower_normalized returns the retained plan. |
| failure | Construction/allocation/compiler validation failures propagate before a returned Case. |
| cost | Bounded fixture DTO copies and actual lowering, independent of measured runtime update quanta. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 101–105](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Relation oracle(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate expected current answers outside the incremental engine. |
| inputs / outputs | Kind5 emits one Boolean row from table emptiness; kind4 manually filters x&gt;=0; other supported kinds call reference::evaluate. |
| invariants | Manual output semantics cover normalized cases; reference evaluator scans ordinary source sets. It does not use incremental support/message counters. |
| ownership | Borrows Case/Database and returns owning ordinary rows; plan source DTO borrows stay within the call. |
| failure | Trusted database arity/types/kind required; get/index/evaluator/allocation errors propagate. |
| cost | Manual scan or exhaustive reference evaluation plus ordinary set construction; intentionally independent and potentially expensive. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 106–106](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L106:sha256:2af219c0c2ce1cb19d338483b7c5720c6c6b7f233cf5aec8480282193beddfec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Native commit precedes model/export assertions; later failure cannot roll it back. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 107–114](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Output step(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one real committed session update with an independent before/after model. |
| inputs / outputs | Copies ordinary Database, applies set update, enqueues feed offset sequence*10, commits/drains; checks delta or maintenance silence then current rows. |
| invariants | Model application uses trusted table index and row shape. Engine commits before result assertions/model publication; no strong joint rollback contract. |
| ownership | Owns before/after model/results; native session retains separate actual state. Model publishes by move only after delta check. |
| failure | Any input/engine/export/model allocation/assertion failure propagates; engine may already be committed when model verification fails. |
| cost | Deep Database copy plus independent before/after scans, real native update and full result export/comparison; not a production hot path. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 115–118](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void rejected(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an expected checkpoint rejection from a supplied negative-test action. |
| inputs / outputs | Copies/moves callable by value, invokes it, catches only ImageFailure or public Error, then asserts a rejection happened. |
| invariants | Any fault kind/code inside those two families is accepted; this helper does not prove a specific diagnostic or absorb bad_alloc/unrelated failures. |
| ownership | Action value is local; captured references retain caller lifetime requirements. |
| failure | Two narrow catches are necessary expected-test classification; unexpected exceptions propagate. |
| cost | One invocation and fixed flag/catch dispatch; actual attempted validation/restoration cost remains. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 119–119](../../../../../tests/support/session_checkpoint_test_fixture.hpp#L119); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L119:sha256:e68683f32a8111cba6ab2f00efc2811bac43b7b353a2a14c6a06ef1658405155
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_checkpoint_test_fixture.hpp: namespace crown::session_checkpoint_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |
