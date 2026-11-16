# `tests/support/selection_fixture.hpp` — block usage map

[Source](../../../../../tests/support/selection_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `13175dafa101a09d4b40b83fd5abe39fbcf499242dbe090f705abd9e7d156187`. 97 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/support/selection_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–25](../../../../../tests/support/selection_fixture.hpp#L18) | Callable definition: inline ps::Selection complete(ps::Attempt value) | calls std::runtime_error, std::to_string; returns *value.selection · [reviewed contract](#b0002) |
| [B0003 · 26–33](../../../../../tests/support/selection_fixture.hpp#L26) | Callable definition: inline rs::CurrentSelection complete(rs::Attempt value) | calls std::runtime_error, std::to_string; returns *value.selection · [reviewed contract](#b0003) |
| [B0004 · 34–34](../../../../../tests/support/selection_fixture.hpp#L34) | Explanatory comments or spacing. | source comment (unverified): // Exact root inputs survive sparse/zero-detail sampling; root slab work remains. · [reviewed contract](#b0004) |
| [B0005 · 35–38](../../../../../tests/support/selection_fixture.hpp#L35) | Callable definition: inline runtime::workload::Options counters() | calls ; returns options; source comment (unverified): // Exact root inputs survive sparse/zero-detail sampling; root slab work remains. · [reviewed contract](#b0005) |
| [B0006 · 39–46](../../../../../tests/support/selection_fixture.hpp#L39) | Callable definition: inline void heat(runtime::PhysicalRuntime& owner, const Fixture& f, bool hot_r = true) | calls configure_workload_statistics, counters, apply, sequence; growth insert; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 47–52](../../../../../tests/support/selection_fixture.hpp#L47) | Callable definition: inline rr::RuntimeEvidence capture(const planner::CandidateSnapshot& snapshot, const runtime::PhysicalRuntime& owner, rr::Capture… | calls rr::capture, check, has_value; guard check(result.stop == pr::Stop::complete && result.evidence.has_value(), "C05 fixture actual capture…; returns *result.evidence · [reviewed contract](#b0007) |
| [B0008 · 53–53](../../../../../tests/support/selection_fixture.hpp#L53) | Explanatory comments or spacing. | source comment (unverified): // Explicit ordinary row export/set construction, separate from native cursor ownership. · [reviewed contract](#b0008) |
| [B0009 · 54–58](../../../../../tests/support/selection_fixture.hpp#L54) | Callable definition: inline Relation answers(const runtime::PhysicalRuntime& owner) | calls results, next, insert, crown::storage::export_row; returns result; growth insert; 1 loop sites; source comment (unverified): // Explicit ordinary row export/set construction, separate from native cursor ownership. · [reviewed contract](#b0009) |
| [B0010 · 59–61](../../../../../tests/support/selection_fixture.hpp#L59) | Callable definition: inline ps::Request request(ps::Policy policy) | calls ; returns out · [reviewed contract](#b0010) |
| [B0011 · 62–65](../../../../../tests/support/selection_fixture.hpp#L62) | Callable definition: inline const pr::Result& assessment(const ps::Selection& selected, pr::Policy policy) | calls assessments, request, std::runtime_error; returns item.result; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 66–75](../../../../../tests/support/selection_fixture.hpp#L66) | Callable definition: inline void depth_oracle(const pr::Result& result, bool hot_r = true) | calls check, scores, size, c02_test::shape; guard check(result.scores().size() == 3, "C05 depth retained set incomplete");; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 76–84](../../../../../tests/support/selection_fixture.hpp#L76) | Callable definition: inline void slot_oracle(const pr::Result& result) | calls check, scores, size, c02_test::shape; guard check(result.scores().size() == 3, "C05 slot retained set incomplete");; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 85–90](../../../../../tests/support/selection_fixture.hpp#L85) | Callable definition: inline void valid_plan(const ps::Selection& selected, const Database& database) | calls runtime::PhysicalRuntime::initialize, plan, check, has_answer; guard check(owner.has_answer(), "C05 selected plan changed Boolean answer"); · [reviewed contract](#b0014) |
| [B0015 · 91–96](../../../../../tests/support/selection_fixture.hpp#L91) | Callable definition: inline planner::CandidateSnapshot prefix(const planner::VerifiedOptimum& proof) | calls planner::CandidateProvider::create, candidate_count, advance, check; guard check(provider.candidate_count() == 1, "C05 finite prefix admission failed"); return provider.snaps…; returns provider.snapshot(); 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 97–97](../../../../../tests/support/selection_fixture.hpp#L97) | Closes surrounding scope/type. | source comment (unverified): // namespace c05_test · [reviewed contract](#b0016) |

## B0001

[Lines 1–17](../../../../../tests/support/selection_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:3b6dd09794323397b20fb54800932fc83beabd688598de7ecf09dbe29c7ddecc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_fixture.hpp: include "ranking_fixture.hpp", "crown/runtime/selection.hpp", "crown/io/physical.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;sstream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–25](../../../../../tests/support/selection_fixture.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline ps::Selection complete(ps::Attempt value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a successfully published pure Selection and return an owning handle. |
| inputs / outputs | Takes Attempt by value; missing selection/noncomplete stop throws a diagnostic naming stop/stage/resource, otherwise returns a copy of its contained handle. |
| invariants | This checks the API outcome, not arbitrary DTO content or future owner freshness. It cannot manufacture an actual selection without the private producer. |
| ownership | Selection and CurrentSelection actual copy-like special members share immutable Data controls; their moves retain source validity. Attempt copy shares contained handles but does not clone score/key graphs. Diagnostic strings are ordinary owning values. |
| failure | Failed status constructs runtime_error with to_string/string allocations; no exception swallowing. Used after fault guards in sweeps. |
| cost | Fixed success checks/owner copy; failure text construction allocates. Last-owner destruction of an older destination can still release a large graph. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 26–33](../../../../../tests/support/selection_fixture.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline rs::CurrentSelection complete(rs::Attempt value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a successfully published actual CurrentSelection and return an owning handle. |
| inputs / outputs | Takes Attempt by value; missing selection/noncomplete stop throws a diagnostic naming stop/stage/resource, otherwise returns a copy of its contained handle. |
| invariants | This checks the API outcome, not arbitrary DTO content or future owner freshness. It cannot manufacture an actual selection without the private producer. |
| ownership | Selection and CurrentSelection actual copy-like special members share immutable Data controls; their moves retain source validity. Attempt copy shares contained handles but does not clone score/key graphs. Diagnostic strings are ordinary owning values. |
| failure | Failed status constructs runtime_error with to_string/string allocations; no exception swallowing. Used after fault guards in sweeps. |
| cost | Fixed success checks/owner copy; failure text construction allocates. Last-owner destruction of an older destination can still release a large graph. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 34–34](../../../../../tests/support/selection_fixture.hpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L34:sha256:e5ad3ffa868383e5dc8232dea30771476569aa4441ef32315f874a672a8dd08b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Exact root inputs survive sparse/zero-detail sampling; root slab work remains. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 35–38](../../../../../tests/support/selection_fixture.hpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline runtime::workload::Options counters()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose sparse detail sampling while retaining exact physical input census for C05 fixture heating. |
| inputs / outputs | Returns counters mode with period=64 and detail_budget=0; other Options defaults retained. |
| invariants | Exact committed physical roots include all inputs, including duplicate no-ops; zero detail budget does not mean zero root lifecycle work or disabled observation. |
| ownership | Inline options only, no array/account/clock owner. |
| failure | No configuration occurs here; actual owner.configure validates/funds slabs later. |
| cost | Fixed scalar initialization, no runtime scan/allocation. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 39–46](../../../../../tests/support/selection_fixture.hpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void heat(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce the literal 90/5/5 committed physical-input weights over an already initialized fixture owner. |
| inputs / outputs | Configures counters, then applies duplicate inserts using each table's first fixture row: 90 to R (or T), 5 to each other table, advancing actual owner sequence each time. |
| invariants | Requires the three source rows already present and writer-ready owner; this helper itself does not assert physical_changed=false (independent noop helper does). It creates real committed events and query observation state, not fabricated numeric Evidence. |
| ownership | Fixture rows are borrowed to construct update Row copies; returned epochs are discarded and own their cleanup. Observation slabs/native update controls use actual owner account. |
| failure | Configuration/update/sequence/account failures propagate; previously committed heating events are not rolled back as one fixture transaction. |
| cost | 100 real updates/no-op paths plus configuration allocations; root numeric lifecycle scans remain even with zero detail budget. No current source data is intentionally added under the precondition. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 47–52](../../../../../tests/support/selection_fixture.hpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline rr::RuntimeEvidence capture(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture genuine bounded statistics/evidence from the supplied actual PhysicalRuntime. |
| inputs / outputs | Calls rr::capture(snapshot,owner,options), requires complete stop and evidence, returns its owning RuntimeEvidence handle. |
| invariants | Snapshot authority and current owner/capture binding are checked by real runtime capture; fixture never inserts private Evidence factories or caller-written counts. |
| ownership | RuntimeEvidence copies share its actual immutable Data; underlying capture can own compact copied keys and funded numeric arrays. Runtime is borrowed only for synchronous read. |
| failure | Incomplete/failing capture throws fixture assertion rather than accepting synthetic fallback; real capture can allocate under owner account. |
| cost | Full requested native state/census and numeric snapshot processing plus fixed handle return; no generic allocation-free capture claim. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 53–53](../../../../../tests/support/selection_fixture.hpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L53:sha256:d473f08e6a905161f14580c179c87283405db954de147a4d4252d2775e18faa3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Explicit ordinary row export/set construction, separate from native cursor ownership. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 54–58](../../../../../tests/support/selection_fixture.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Relation answers(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export the current result cursor into an independent ordinary set of rows. |
| inputs / outputs | Iterates owner.results(), exports each tuple values to ordinary Row and inserts into Relation until terminal null. |
| invariants | Set semantics deduplicate exported rows. Cursor runs only on stable readable owner and pins its committed epoch per runtime contract; it is fully consumed here. |
| ownership | Relation owns copied scalar/string/Decimal payload and set nodes outside native account; cursor/control uses runtime owners until destruction. Source row views expire independently. |
| failure | Cursor/work/account/ordinary export/allocation failures propagate; local Relation/cursor clean up through RAII and no partial Relation is returned. |
| cost | Actual result enumeration plus deep payload exports and O(results log results) set comparisons, including variable bytes; not a fixed flag check. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 59–61](../../../../../tests/support/selection_fixture.hpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline ps::Request request(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select an explicit C05 policy while preserving default request limits/fallback. |
| inputs / outputs | Default-constructs Request and assigns policy. |
| invariants | This creates editable request metadata, not a ranking result, typed proof or owner capture. |
| ownership | Returned Request owns its normal members; current defaults contain no caller source/row reference. |
| failure | No local validation/catch; select admission validates actual request later. |
| cost | Fixed initialization/enum assignment; no candidate enumeration or runtime read. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 62–65](../../../../../tests/support/selection_fixture.hpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const pr::Result& assessment(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the first retained completed assessment requested for the named ranking policy. |
| inputs / outputs | Scans selected.assessments and compares each result.request().policy; returns const Result reference or throws missing assessment. |
| invariants | Callers choose a selection whose retained assessments have expected policy; this does not recompute scores, change purpose or revalidate actual owner. |
| ownership | Returned reference borrows Selection's immutable assessment graph; retain selected while using it. |
| failure | Missing policy throws runtime_error; no fallback assessment or vector copy. |
| cost | Linear number of retained assessments, fixed request tag reads; failure diagnostic can allocate. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 66–75](../../../../../tests/support/selection_fixture.hpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void depth_oracle(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check literal C02 native-depth scores for the full three-shape 90/5/5 workload. |
| inputs / outputs | Requires three scores, height 2, denominator 100 and shape-indexed numerators: native S 195, generalized x 105/y190 (swapped for hot T), plus three occurrence/table reproduction terms. |
| invariants | Expected weighted native path depths are 2/1/2 for native S, 1/1/2 for generalized x, 2/1/1 for generalized y. Numeric score is a workload proxy, not elapsed time or a proof of new minimum height. |
| ownership | Reads owning Result; fixed expected arrays own ordinary strings and may allocate depending library representation. |
| failure | Mismatch throws fixture check; shape helper requires the admitted known tree family. |
| cost | Linear score/reproduction-size checks with fixed three expected values; no production scoring helper generates expected numerators. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 76–84](../../../../../tests/support/selection_fixture.hpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void slot_oracle(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check literal candidate-local tuple/index-slot proxy and complete reproduction presence. |
| inputs / outputs | Requires three scores: native S slots=24 and 12 terms, generalized roots slots=32 and 14 terms; every score must retain modeled plan and one population record per modeled node. |
| invariants | Slots are C02 modeled logical tuple/index slots, not requested allocator bytes, measured time, allocation counts or permission to replace original proof. |
| ownership | Borrows Result/modeled plans; comparisons materialize no new runtime/table population. |
| failure | Mismatch throws through fixture check; no fallback to a score computed by the same production helper. |
| cost | Linear retained scores with fixed shape/term checks; no full native scan beyond existing result. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 85–90](../../../../../tests/support/selection_fixture.hpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void valid_plan(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise the selected typed native plan and preserve original structural-height authority in this true Boolean fixture. |
| inputs / outputs | Initializes a fresh PhysicalRuntime from selected.plan/database, requires has_answer, selected height==original proof height and guarantee height_status==valid_upper_bound. |
| invariants | This checks the expected true Boolean answer/profile for supplied fixture, not every full output tuple or a new optimality proof. Runtime receives the genuine selected CompiledProgram; original candidate proof remains the height authority. |
| ownership | Fresh public PhysicalRuntime initialization creates a new query account and freezes/imports the selected CompiledProgram plus ordinary database rows under it. The selection retains its earlier native plan/account independently; input database is borrowed during import. No fixture DTO constructs a VerifiedOptimum. |
| failure | Native initialization/row/domain/constraint/account/allocation errors or assertions propagate; owner teardown releases actual state. |
| cost | Full runtime initialization/native source import and maintenance plus a Boolean check; not a cheap profile-only assertion. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 91–96](../../../../../tests/support/selection_fixture.hpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline planner::CandidateSnapshot prefix(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Take a genuine immutable one-candidate prefix without claiming family exhaustion. |
| inputs / outputs | Creates provider from supplied VerifiedOptimum; advances up to 100k quanta of 1000 until any candidate, asserts count==1, then snapshots. |
| invariants | Provider yields at each new candidate; one candidate does not imply exhausted family or global optimal alternative choice. Required original minimum-height authority is retained. |
| ownership | Provider takes a proof-handle copy; Snapshot admission allocates/copies handle/event vectors then returned handle owns immutable prefix. Later provider changes do not rewrite it. |
| failure | Guard/provider/metadata/allocation failures propagate or fail assertion; no invented candidate/partial-proof acceptance. |
| cost | Real initial enumeration/validation/canonicalization plus snapshot allocation; bounded driver loop is a test guard, not CPU/memory proof. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 97–97](../../../../../tests/support/selection_fixture.hpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L97:sha256:4ff4422f17ed7a6607697f3571285bcf816b40adab756a7c9a21651ba17d0c0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_fixture.hpp: namespace c05_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |
