# `tests/support/window_checkpoint_test_fixture.hpp` — block usage map

[Source](../../../../../tests/support/window_checkpoint_test_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7d7988ebe17c02c3cd07bd6b1ccdb0f85eea5c1e768c1aba419b7a9394516eaa`. 71 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; controls preprocessing; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L16) | Callable definition: inline void check(bool value,const char* message) | calls std::runtime_error; guard inline void check(bool value,const char* message){if(!value)throw std::runtime_error(message);} · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L17) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 18–23](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L18) | Callable definition: inline PhysicalPlan plan(bool indexed) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0004) |
| [B0005 · 24–24](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L24) | Explanatory comments or spacing. | source comment (unverified): // Spare capacity seven is deliberate copy/checkpoint accounting coverage. · [reviewed contract](#b0005) |
| [B0006 · 25–27](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L25) | Callable definition: inline WindowOptions config(WindowFifoPolicy fifo) | calls reserve; returns result; growth reserve; source comment (unverified): // Spare capacity seven is deliberate copy/checkpoint accounting coverage. · [reviewed contract](#b0006) |
| [B0007 · 28–35](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L28) | Callable definition: inline void grant(const QuerySession& session,bool indexed) | calls RuntimeTestProbe::index_work, check; guard check(indexed?(value && value-&gt;fresh_operations==1):!value,"window session restore refilled indexed… · [reviewed contract](#b0007) |
| [B0008 · 36–40](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L36) | Callable definition: inline Relation rows(const QuerySession& session) | calls snapshot, check, insert, storage::export_row; guard for(const auto& row:snapshot.rows)check(result.insert(storage::export_row(row.values())).second,"du…; returns result; growth insert; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 41–44](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L41) | Callable definition: inline void enqueue(QuerySession& session,io::WindowCommand command) | calls batch, std::move, check, empty; guard check(session.enqueue(batch)==io::Admission::accepted && batch.empty(),"window command not admitted… · [reviewed contract](#b0009) |
| [B0010 · 45–51](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L45) | Callable definition: inline Output finish(QuerySession& session) | calls step, commit, next_output, check; guard check(value-&gt;ordinal==++ordinal && result.emplace(value-&gt;operation,storage::export_row(value-&gt;tuple…; returns result; growth emplace; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 52–52](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L52) | Explanatory comments or spacing. | source comment (unverified): // One command may span epochs; signed-set union is not a counted delivery oracle. · [reviewed contract](#b0011) |
| [B0012 · 53–59](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L53) | Callable definition: inline Output command(QuerySession& session,io::WindowCommand value) | calls enqueue, std::move, check, begin_next; guard check(session.begin_next(),"window command disappeared");const auto output=finish(session);result.i…; returns result; growth insert; 2 loop sites; source comment (unverified): // One command may span epochs; signed-set union is not a counted delivery oracle. · [reviewed contract](#b0012) |
| [B0013 · 60–62](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L60) | Callable definition: io::WindowCommand insertion(std::uint64_t sequence,std::uint64_t label,TableId table,std::int64_t value,std::uint64_t timestamp) | calls ; returns {sequence,io::WindowInsert{label,table,{value},timestamp},{}} · [reviewed contract](#b0013) |
| [B0014 · 63–66](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L63) | Callable definition: inline void seed(QuerySession& session) | calls start, command, insertion · [reviewed contract](#b0014) |
| [B0015 · 67–70](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L67) | Callable definition: template&lt;class Action&gt; void rejected(Action action) | calls action, check; guard check(failed,"inconsistent session state accepted"); · [reviewed contract](#b0015) |
| [B0016 · 71–71](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L71) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::window_checkpoint_test · [reviewed contract](#b0016) |

## B0001

[Lines 1–15](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:cdc6414b45d39bbb1adc84db8b289049799b72c1d70cbfe691a8fa5b9cd16e69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare window_checkpoint_test_fixture.hpp: include "crown/runtime/session_checkpoint.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", "runtime_probe.hpp", &lt;iostream&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;thread&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–16](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L16); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 17–17](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 18–23](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan plan(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a unary result query with a second unqueried but window-managed table. |
| inputs / outputs | Catalog version9 has r(x),s(x); query/head r(x), one native root; indexed selects finite test options. |
| invariants | Window management of s exercises input state that does not affect result rows; compiler admission remains real. |
| ownership | Returns owning immutable PhysicalPlan handle; temporary DTOs expire. |
| failure | Validation/lowering/ordinary allocations propagate before runtime construction. |
| cost | Bounded catalog/tree creation plus actual lowering. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 24–24](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:618f6ba85298c3c226633c7e47076f626e26e322393971c0c72952f8cb2b54c1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Spare capacity seven is deliberate copy/checkpoint accounting coverage. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 25–27](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline WindowOptions config(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare width10 FIFO window options with deliberate spare managed-table capacity. |
| inputs / outputs | Reserves seven entries then stores tables0/1, supplied FIFO policy and width10. |
| invariants | Capacity7 versus size2 is intentional copy/checkpoint accounting coverage; this is ordinary options storage until native admission. |
| ownership | Returns owning vector/options; copying options can allocate and may choose actual copied capacity. |
| failure | reserve/copy allocation failures propagate; no native grant is created here. |
| cost | One reserve for seven IDs plus fixed two-element assignment and scalar fields. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 28–35](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L28); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 36–40](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L36); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 41–44](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void enqueue(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Submit one real typed window command with a deterministic source position. |
| inputs / outputs | Takes command by value, assigns window offset sequence*10, moves it into a batch and requires acceptance/consumption. |
| invariants | Source position metadata remains descriptive until actual queue admission validates it; multiplication is safe only for these bounded sequences. |
| ownership | Owns local command/batch until session consumes; copied/moved Row/string payload follows ordinary members. |
| failure | Local copy/allocation/admission/assertion failures propagate. |
| cost | One command/source construction, batch storage and actual native input admission. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 45–51](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L45); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 52–52](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L52:sha256:39840a94e76baa8c4ea77c7d7002bb852fb3123e32b942dadedafd1badc7422e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: One command may span epochs; signed-set union is not a counted delivery oracle. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 53–59](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Output command(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete all physical epochs needed for one logical window command. |
| inputs / outputs | Saves command sequence, enqueues, repeatedly begins/finishes and unions signed outputs until progress reaches sequence. |
| invariants | One logical expiration/watermark may span multiple physical epochs. Set union collapses repeated signed rows across substeps, so this is not a counted delivery oracle. |
| ownership | Owns returned ordinary Output; session keeps actual input/progress state. |
| failure | No independent iteration cap; native failures and export/assertion failures propagate after any prior commits. |
| cost | All physical step/commit/drain work plus repeated ordinary set unions/progress reads. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 60–62](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::WindowCommand insertion(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a trusted one-column insertion command. |
| inputs / outputs | Returns sequence,label,table,one int64 row,timestamp with no source position; enqueue later supplies one. |
| invariants | No table/label/timestamp validation occurs in this constructor. Single-TU test header function is not inline. |
| ownership | Return owns its ordinary Row/variant payload. |
| failure | Row/vector allocation may throw; no session mutation. |
| cost | One small row allocation plus fixed DTO construction. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 63–66](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void seed(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Populate a repeatable live window and progress baseline. |
| inputs / outputs | Starts session; insert r1 labels1/2 at times0/1, withdraw1, insert s2 label3 time2, advance watermark2. |
| invariants | Duplicate row labels and unqueried managed table are deliberate. Every command passes real queue/session execution. |
| ownership | Borrows live session; returned state remains owned by it, not by this helper. |
| failure | Any start/command failure propagates with earlier accepted/committed commands retained. |
| cost | Five real command executions including native window metadata and exported signed sets. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 67–70](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L67); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/unit/window_checkpoint_test.cpp](../../../../../tests/unit/window_checkpoint_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 71–71](../../../../../tests/support/window_checkpoint_test_fixture.hpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L71:sha256:4e230a28dad3804838c3c19f9849664932e2aa00562f213a8d840d93a276a502
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in window_checkpoint_test_fixture.hpp: namespace crown::window_checkpoint_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |
