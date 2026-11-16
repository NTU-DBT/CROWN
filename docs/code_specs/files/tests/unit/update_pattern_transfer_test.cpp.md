# `tests/unit/update_pattern_transfer_test.cpp` — block usage map

[Source](../../../../../tests/unit/update_pattern_transfer_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3cb5014f0864edea44c8b5a6c6c366906791f7a4c6a317260009aa1f0c15f002`. 238 lines partitioned into 19 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/update_pattern_transfer_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–21](../../../../../tests/unit/update_pattern_transfer_test.cpp#L18) | Type/record definition: struct SqlFixture |  · [reviewed contract](#b0002) |
| [B0003 · 22–23](../../../../../tests/unit/update_pattern_transfer_test.cpp#L22) | Explanatory comments or spacing. | source comment (unverified): // Physical table 0 is unused; core table IDs are occurrences, not physical · [reviewed contract](#b0003) |
| [B0004 · 24–38](../../../../../tests/unit/update_pattern_transfer_test.cpp#L24) | Callable definition: SqlFixture sql_fixture(bool indexed,bool taller) | calls frontend::admit_sql, check, has_value, c02_test::candidates; guard check(admitted.status==frontend::AdmissionStatus::admitted && admitted.program.has_value(),"SQL tra…; returns {std::move(program),std::move(family)}; 1 loop sites; source comment (unverified): // Physical table 0 is unused; core table IDs are occurrences, not physical · [reviewed contract](#b0004) |
| [B0005 · 39–42](../../../../../tests/unit/update_pattern_transfer_test.cpp#L39) | Callable definition: SessionOptions monitored(const CompiledProgram& program,std::span&lt;const ip::TableRule&gt; rules) | calls ip::Declaration::capture, account; returns options · [reviewed contract](#b0005) |
| [B0006 · 43–47](../../../../../tests/unit/update_pattern_transfer_test.cpp#L43) | Callable definition: void physical(QuerySession& owner,std::uint64_t sequence,TableId table,SetOperation operation,Row row) | calls batch, std::move, check, enqueue; guard check(owner.enqueue(batch)==io::Admission::accepted && owner.begin_next(),"transfer input missing"); · [reviewed contract](#b0006) |
| [B0007 · 48–48](../../../../../tests/unit/update_pattern_transfer_test.cpp#L48) | Callable definition: std::string_view bytes(const recovery::SessionImage& image) | calls data, size; returns {image.bytes.data(),image.bytes.size()} · [reviewed contract](#b0007) |
| [B0008 · 49–52](../../../../../tests/unit/update_pattern_transfer_test.cpp#L49) | Explanatory comments or spacing. | source comment (unverified): // A logical insertion condition belongs to physical participating sources. · [reviewed contract](#b0008) |
| [B0009 · 53–106](../../../../../tests/unit/update_pattern_transfer_test.cpp#L53) | Callable definition: void sql_contract(bool indexed,bool taller) | calls sql_fixture, ip::Declaration::capture, account, candidate_count; guard check(good.stop==planner::ranking::Stop::complete && good.analysis-&gt;sufficient==pp::SufficientCase:…; growth insert; 3 loop sites; source comment (unverified): // A logical insertion condition belongs to physical participating sources. · [reviewed contract](#b0009) |
| [B0010 · 107–109](../../../../../tests/unit/update_pattern_transfer_test.cpp#L107) | Explanatory comments or spacing. | source comment (unverified): // Higher mixed trees retain the lifetime gate. A dropped column and a genuine · [reviewed contract](#b0010) |
| [B0011 · 110–133](../../../../../tests/unit/update_pattern_transfer_test.cpp#L110) | Callable definition: void mixed_transfer_refusals() | calls c02_test::fixture, push_back, emplace_back, c02_test::candidates; guard check(result.analysis && result.analysis-&gt;sufficient==pp::SufficientCase::unknown &&; growth emplace_back, push_back; 3 loop sites; source comment (unverified): // Higher mixed trees retain the lifetime gate. A dropped column and a genuine · [reviewed contract](#b0011) |
| [B0012 · 134–137](../../../../../tests/unit/update_pattern_transfer_test.cpp#L134) | Explanatory comments or spacing. | source comment (unverified): // The proof's explicit seven-atom tree uses non-topological IDs (root is 7). · [reviewed contract](#b0012) |
| [B0013 · 138–148](../../../../../tests/unit/update_pattern_transfer_test.cpp#L138) | Callable definition: PhysicalPlan oscillator_plan(bool indexed) | calls pattern_test::height_three_fixture, planner::lower_tree, s04_runtime::options; returns planner::lower_tree(fixture.catalog,fixture.query,tree,indexed?s04_runtime::options():PhysicalOptio…; source comment (unverified): // The proof's explicit seven-atom tree uses non-topological IDs (root is 7). · [reviewed contract](#b0013) |
| [B0014 · 149–152](../../../../../tests/unit/update_pattern_transfer_test.cpp#L149) | Explanatory comments or spacing. | source comment (unverified): // Actual global raw FIFO plus internal insertion-only does not prevent 2mn R · [reviewed contract](#b0014) |
| [B0015 · 153–181](../../../../../tests/unit/update_pattern_transfer_test.cpp#L153) | Callable definition: void oscillator_contract(bool indexed,std::uint64_t n,std::uint64_t m) | calls CompiledProgram::standalone, oscillator_plan, push_back, QuerySession::create_windowed; guard check(win::rows(*session)==c05_test::answers(native) && !session-&gt;update_pattern_status().violation…; growth insert, push_back; 6 loop sites; source comment (unverified): // Actual global raw FIFO plus internal insertion-only does not prevent 2mn R · [reviewed contract](#b0015) |
| [B0016 · 182–184](../../../../../tests/unit/update_pattern_transfer_test.cpp#L182) | Explanatory comments or spacing. | source comment (unverified): // The new postorder scratch and retained edge report must obey the same public · [reviewed contract](#b0016) |
| [B0017 · 185–227](../../../../../tests/unit/update_pattern_transfer_test.cpp#L185) | Callable definition: void analysis_resource_contract() | calls pattern_test::height_three_fixture, pattern_test::height_three_family, candidate, CompiledProgram::standalone; guard check(measured.analysis && measured.analysis-&gt;sufficient==pp::SufficientCase::subtree_edges,"resour…; growth insert, push_back; 4 loop sites; source comment (unverified): // The new postorder scratch and retained edge report must obey the same public · [reviewed contract](#b0017) |
| [B0018 · 228–228](../../../../../tests/unit/update_pattern_transfer_test.cpp#L228) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0018) |
| [B0019 · 229–238](../../../../../tests/unit/update_pattern_transfer_test.cpp#L229) | Callable definition: int main() | calls mixed_transfer_refusals, analysis_resource_contract, sql_contract, oscillator_contract; returns 1; 2 loop sites · [reviewed contract](#b0019) |

## B0001

[Lines 1–17](../../../../../tests/unit/update_pattern_transfer_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:75e94f47356516cb93cc3ac166175af04ad883e35690f21dc9f4014066e2a66e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the transfer-test dependencies and bind short local names for the test APIs. |
| inputs / outputs | Includes fixture, window/session, SQL admission, recovery image, and array declarations; opens an anonymous namespace and aliases the test/runtime APIs. |
| invariants | Aliases shorten names but preserve each included API’s own contract. This block does not execute a test or establish engine correctness. |
| ownership | No query owner is created by includes, using declarations, or namespace aliases. |
| failure | Missing headers or invalid names fail compilation. |
| cost | Compile-time preprocessing/name lookup only. |
| Design | [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [include/crown/planner/update_pattern.hpp](../../../../../include/crown/planner/update_pattern.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0002

[Lines 18–21](../../../../../tests/unit/update_pattern_transfer_test.cpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L21:sha256:b90cd6b5898f742cf32c1b6bb8fd7b0de67451d48625ea1eca05a73448e8b16c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the compiled SQL program and its retained candidate family together for one fixture. |
| inputs / outputs | Aggregate members are a CompiledProgram and CandidateSnapshot, initialized by sql_fixture(). |
| invariants | The aggregate associates program and candidate context for a test; it does not independently prove their binding. |
| ownership | Each member is an owning handle with its own retained backing storage; ordinary aggregate moves transfer those handles. |
| failure | Member construction failures propagate; the aggregate has no recovery path. |
| cost | Fixed-size handle storage; member construction/allocation costs are charged to their own APIs. |
| Design | [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [tests/unit/update_pattern_transfer_test.cpp](../../../../../tests/unit/update_pattern_transfer_test.cpp) |

## B0003

[Lines 22–23](../../../../../tests/unit/update_pattern_transfer_test.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L23:sha256:1fdec450f212e802fb9011b4708c6c35649ad416cab9046b1510cb4090af66cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the SQL fixture’s physical/core ID distinction and deliberate projection collisions. |
| inputs / outputs | Source comment documents the relationship used by the following helper. |
| invariants | The comment describes test intent only; the helper’s explicit base-ID check is executable evidence. |
| ownership | Comment text only. |
| failure | No runtime failure behavior. |
| cost | No runtime cost. |
| Design | [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [build/verification/v53-taller-mixed-proof-v1/implementation-transfer.md](../../../../../build/verification/v53-taller-mixed-proof-v1/implementation-transfer.md) |

## B0004

[Lines 24–38](../../../../../tests/unit/update_pattern_transfer_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L38:sha256:3c696344fcdbe34f953b80e66411de752d1cc6f88d16f23931ab597efc7ee744
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile either a two-alias or three-alias normalized SQL transfer fixture over one physical base table. |
| inputs / outputs | Boolean selectors choose the SQL and indexed backend. The helper admits/normalizes SQL, obtains the requested candidate fixture, lowers it, checks every compiled input has physical base ID 1 (table 0 is unused), then returns program and family. |
| invariants | The physical catalog contains an unused table and r with x/y/flag/payload; core occurrence IDs may differ. Base 1 is the only participating physical input. The helper establishes test inputs, not an independent minimum proof. |
| ownership | Catalog/SQL admission locals are ordinary temporary values; returned program/family retain their own owners. |
| failure | Admission, candidate construction, lowering, assertions, or allocations may fail and propagate; there is no fallback candidate. |
| cost | Parsing, normalization, candidate creation, lowering, and an input scan; fixture work is test setup, not a runtime performance measurement. |
| Design | [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0005

[Lines 39–42](../../../../../tests/unit/update_pattern_transfer_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L42:sha256:0bafcaa4ac8a7a5cc24b8175029e70219351e32048d9ff7c5a986753d2395873
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a typed SessionOptions fixture with a captured declaration and counter observations enabled. |
| inputs / outputs | Takes the program and a borrowed rule span; returns options containing a source-captured UpdatePatternOptions and counter-mode support observation. |
| invariants | Declaration capture binds the rules to this program; it records requested assumptions and does not prove history compliance. |
| ownership | Capture uses the program account; returned options retain the immutable declaration handle. The input span is borrowed only during capture. |
| failure | Invalid/duplicate/out-of-range rules or account allocation failure propagate. |
| cost | Rule validation/canonicalization and allocation follow Declaration::capture; enabling counters is configuration only. |
| Design | [include/crown/ir/update_pattern.hpp](../../../../../include/crown/ir/update_pattern.hpp), [include/crown/runtime/update_pattern.hpp](../../../../../include/crown/runtime/update_pattern.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0006

[Lines 43–47](../../../../../tests/unit/update_pattern_transfer_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L47:sha256:21c37a37a1ae8d6bcb3760d93a564a63253a652dfedee2b929b327e3137dcc6b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Submit and finish one physical event through a typed QuerySession in a test. |
| inputs / outputs | Takes session, sequence, base table, operation, and an owning Row; builds one InputEvent batch, requires enqueue and begin_next acceptance, then runs the fixture completion helper. |
| invariants | The helper checks only that this event was accepted and completed through the session fixture. It does not compare output or claim constant event cost. |
| ownership | Row moves into the batch and then through the session; the session owns committed input state. |
| failure | Failed admission/completion throws via check; runtime semantic/resource exceptions propagate. |
| cost | One end-to-end event including native maintenance and fixture completion; work depends on the actual runtime/query and is not bounded here. |
| Design | [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0007

[Lines 48–48](../../../../../tests/unit/update_pattern_transfer_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L48:sha256:72b7f07df615a8e5a2664d64f27ca7a35a0ba7786a83ed8d2d1601a1a496b1af
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a borrowed view of an image’s encoded bytes for restore tests. |
| inputs / outputs | Takes a const SessionImage and returns a string_view over its byte vector. |
| invariants | The view is valid only while the image and its bytes remain alive and unmodified; it performs no copy. |
| ownership | Non-owning view; caller keeps the image alive across restore_image(). |
| failure | No new failure boundary beyond the source image’s existing validity. |
| cost | Constant-size view construction; no allocation or byte traversal. |
| Design | [include/crown/recovery/session_image.hpp](../../../../../include/crown/recovery/session_image.hpp), [tests/unit/update_pattern_transfer_test.cpp](../../../../../tests/unit/update_pattern_transfer_test.cpp) |

## B0008

[Lines 49–52](../../../../../tests/unit/update_pattern_transfer_test.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L52:sha256:91b9465f13b6de4d01ac57b3dad9d7e0d2e88fad19b3f5502d50cd8f80e6f032
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the test’s distinction between physical insertion assumptions and the conservative mixed-height transfer. |
| inputs / outputs | Comments summarize expected source-level behavior for the adjacent SQL contract. |
| invariants | Comments are explanatory only; executable assertions and planner/runtime implementations determine behavior. |
| ownership | Source text only. |
| failure | No runtime failure behavior. |
| cost | No runtime cost. |
| Design | [build/verification/v53-taller-mixed-proof-v1/implementation-transfer.md](../../../../../build/verification/v53-taller-mixed-proof-v1/implementation-transfer.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0009

[Lines 53–106](../../../../../tests/unit/update_pattern_transfer_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L106:sha256:efc4cdd0b0080fcf17f7971b800a8a81abbff1e5c2e441d0f4b777e0ccbf6c9a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise normalized SQL source binding, actual-base lookup, bounded height-one transfer, current selection, cache binding, collisions, and restored enforcement. |
| inputs / outputs | Runs for both SQL shapes and storage options. It compares insertion-only rules on physical table 1 with wrong rules on unused table 0 and a FIFO-only request; checks analyzer outcomes for each candidate; selects and checks exact cache reuse; starts a monitored session; inserts/erases the unused table; inserts physical rows that collide under projection; checks source/native-crossing counters and query result; checkpoints/restores; then verifies a prohibited erase is rejected with committed sequence/output unchanged. |
| invariants | Assertions distinguish all-source insertion-only from higher normalized mixed rejection and arbitrary height-one mapping. Physical base ID 1 is the rule key; source rows can collide in projected occurrence state; only committed monitor state is expected after restore. This is a test scenario, not a theorem about every SQL adapter. |
| ownership | Each declaration is captured under the program account. Program/family/session/image own their respective state; row values and helper batches move through the session. |
| failure | c02_test::check failures throw. The expected restored semantic violation is caught narrowly and checked; unrelated API/allocation failures propagate. |
| cost | Multiple candidate analyses/selections, cache access, physical updates, checkpoint encoding/restore, and an expected rejected command; no throughput, CPU, or delay claim. |
| Design | [include/crown/planner/update_pattern.hpp](../../../../../include/crown/planner/update_pattern.hpp), [src/planner/update_pattern.cpp](../../../../../src/planner/update_pattern.cpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md) |

## B0010

[Lines 107–109](../../../../../tests/unit/update_pattern_transfer_test.cpp#L107); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L109:sha256:669b47adb2be5fd94fa86eacc18d180d82ea34c4bccf59e5468952fafd371cd5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark the unsupported higher-mixed transfer cases exercised next. |
| inputs / outputs | Comments name dropped payload and a three-alias self-join as negative transfer contexts. |
| invariants | The comment does not imply impossibility; the following assertions check only that this sufficient analyzer refuses these examples. |
| ownership | Source text only. |
| failure | No runtime failure behavior. |
| cost | No runtime cost. |
| Design | [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0011

[Lines 110–133](../../../../../tests/unit/update_pattern_transfer_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L133:sha256:3b39177b64263cfdec57364a53e615726948a21c6723b629a953a0d041bf3282
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep higher-mixed ignored-column and self-join cases unknown unless all sources are insertion-only. |
| inputs / outputs | Builds two direct typed CQ fixtures: one adds an ignored source column, the other creates a three-occurrence self-join. It gives every source the same FIFO scope, checks the analyzer returns unknown with the corresponding transfer reason, then marks every rule insertion-only and checks the source-wide sufficient case. |
| invariants | The negatives show that FIFO plus a projection/self-join is not accepted by this conservative higher-mixed transfer. The insertion-only path bypasses that gate. Unknown is a sufficient-condition result, not hardness. |
| ownership | Fixtures and rule vectors are ordinary heap-owned test DTOs; compiled programs/candidate family/declarations retain their own accounts. |
| failure | Check, compiler, declaration capture, and analyzer failures propagate; no rejection is silently skipped. |
| cost | Two small fixture constructions and repeated analysis; no runtime update or scalability claim. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [include/crown/planner/update_pattern.hpp](../../../../../include/crown/planner/update_pattern.hpp), [src/planner/update_pattern.cpp](../../../../../src/planner/update_pattern.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md) |

## B0012

[Lines 134–137](../../../../../tests/unit/update_pattern_transfer_test.cpp#L134); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L134-L137:sha256:a3099243308c360238bde82eed4bb94060506132f3079fd1e81ce6fb7ba55171
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the explicit proof tree and separate lowering validation from minimum-height authority. |
| inputs / outputs | Comments describe the following non-topological tree IDs and where validation/minimum evidence comes from. |
| invariants | The tree fixture is not itself the exact-minimum proof; the shared fixture’s exact search/provider helper supplies that authority. |
| ownership | Comment text only. |
| failure | No runtime failure behavior. |
| cost | No runtime cost. |
| Design | [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md) |

## B0013

[Lines 138–148](../../../../../tests/unit/update_pattern_transfer_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L138-L148:sha256:115fef087589e411c6a78f28923de18e027e21e1aed3b2d0ae4ce9408338877e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the seven-atom height-three support tree for indexed and unindexed native runs. |
| inputs / outputs | Boolean selects default or indexed PhysicalOptions; returns lower_tree() for the explicit native tree rooted at generalized node ID 7. |
| invariants | The node IDs intentionally differ from topological order; lowering independently validates the supplied tree. The proof relation layout and candidate minimum are separate fixtures. |
| ownership | The returned PhysicalPlan owns its lowered data; local fixture/tree values are temporary. |
| failure | Lowering validation/allocation errors propagate; no catch or fallback tree. |
| cost | Fixed-size tree lowering and optional index construction; this is setup for event-count capture, not a benchmark. |
| Design | [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md) |

## B0014

[Lines 149–152](../../../../../tests/unit/update_pattern_transfer_test.cpp#L149); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L152:sha256:cab5518eb947e471c5e3a15e94687ae05dace0ee40dff2bffa5d3edb0591346a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the oscillator’s closed-form support-transition controls and the absence of a timing claim. |
| inputs / outputs | Comments state the expected 2mn R transitions, total updates, and instrumentation boundary for oscillator_contract(). |
| invariants | The formula is checked by executable assertions below; the comment explicitly says capture is test instrumentation and makes no wall-clock claim. |
| ownership | Source text only. |
| failure | No runtime failure behavior. |
| cost | No runtime cost. |
| Design | [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0015

[Lines 153–181](../../../../../tests/unit/update_pattern_transfer_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L181:sha256:bb3c88af9c9fd1c9a98c51daea9481a8f82eae560ec273f5fcc1974d74bdf990
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the raw FIFO oscillator against both the reference PhysicalRuntime and monitored window Session. |
| inputs / outputs | Takes backend flag and n/m sizes; constructs the proof tree, one explicit joint scope, insertion-only declarations for the other relations, a window session, and a native transition-capturing runtime. The local apply helper advances both, compares outputs and violation status, and counts total and native-R survivor transitions. Loops create n/m supports, trigger each R survivor cycle, withdraw matching FIFO labels, and asserts sequence/update and transition formulas. |
| invariants | The fixture preserves the proof packet’s distinction: global raw FIFO with mutable R/V and insertion-only interior leaves still produces 2mn native-R survivor transitions. It checks exact logical transition counts and result agreement only for these finite cases. |
| ownership | Session/runtime own their states; each Row moves into the appropriate command. Counters and transition lists are test instrumentation; no exported performance receipt is created. |
| failure | Any mismatch throws through check; native/session errors propagate. |
| cost | For these input sizes, work includes 3n+2m+3 physical commands and recorded support transitions proportional to 2mn; indexed and unindexed paths are selected separately. No CPU, worst-case per-update, or broad benchmark bound follows. |
| Design | [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/update_patterns.md](../../../../update_patterns.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md) |

## B0016

[Lines 182–184](../../../../../tests/unit/update_pattern_transfer_test.cpp#L182); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L182-L184:sha256:2109a07814efb911755517254fb89a6a76d449b9559c7f90dc111f5a1af2bd29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the analyzer’s budget-boundary and persistent-allocation failure controls. |
| inputs / outputs | Comments describe the adjacent resource contract test. |
| invariants | The comment states test intent only; measured grants and denial sweeps below supply assertions. |
| ownership | Source text only. |
| failure | No runtime failure behavior. |
| cost | No runtime cost. |
| Design | [include/crown/planner/update_pattern.hpp](../../../../../include/crown/planner/update_pattern.hpp), [src/planner/update_pattern.cpp](../../../../../src/planner/update_pattern.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 185–227](../../../../../tests/unit/update_pattern_transfer_test.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L227:sha256:ca8f09e4684f345e908ce9a9cab63c6a1174cc5fa34e7683306f3ce7b9fd8d50
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify the taller condition affects selection and that analyzer grants/failure cleanup are exact. |
| inputs / outputs | Builds a genuine height-three candidate/program; makes the native root non-insertion-only while retaining insertion-only child subtrees; requires subtree_edges from direct analysis and real selection/current-session selection. It retries at exact measured work/cell/payload/key-byte grants, then lowers each selected dimension by one and requires the matching stop plus account baseline restoration. Finally it counts persistent C++ new points and denies each point in turn, requiring allocation_failure, no report, and no account leak. |
| invariants | The constructed root’s own mutable flag does not invalidate edge condition 1 where each child subtree is insertion-only. Selection sees the retained report. One-less grants test logical admission; allocator denials test rollback/no partial report. The loop count is measured dynamically, not fixed. |
| ownership | Search/provider/program/declaration/report/session use their documented owners. Test vectors/rules/loop bookkeeping and global new injector are ordinary test-side resources outside the analyzer account. |
| failure | Failures are asserted with check; analyzer maps each denial to its existing stop and returns no partial Analysis; no new catch layer is tested or added here. |
| cost | Includes exact search/candidate setup, multiple analyses/selections and a full sweep over the measured allocation sites; this is a bounded test control, not a planner CPU theorem. |
| Design | [include/crown/planner/update_pattern.hpp](../../../../../include/crown/planner/update_pattern.hpp), [src/planner/update_pattern.cpp](../../../../../src/planner/update_pattern.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/update_patterns.md](../../../../update_patterns.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md) |

## B0018

[Lines 228–228](../../../../../tests/unit/update_pattern_transfer_test.cpp#L228); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L228-L228:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous test namespace. |
| inputs / outputs | No input/output; closes the local test scope. |
| invariants | Structural delimiter only; no contract for earlier test helpers is implied. |
| ownership | No runtime ownership. |
| failure | Mismatched syntax fails compilation. |
| cost | No runtime cost. |
| Design | [tests/unit/update_pattern_transfer_test.cpp](../../../../../tests/unit/update_pattern_transfer_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 229–238](../../../../../tests/unit/update_pattern_transfer_test.cpp#L229); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L229-L238:sha256:6cee239a1a81feb86e3aae5d5d2522176d5d9da937fd47f5aa2201ae603789b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the transfer, taller-analysis, SQL, and oscillator test scenarios with a single failure boundary. |
| inputs / outputs | main() invokes mixed-transfer/resource controls, both SQL shapes on indexed and unindexed backends, and n=m values 1, 4, and 8 on both backends; success prints a summary and returns zero. std::exception failures print a diagnostic and return one. |
| invariants | The driver is evidence only when an external build/test runner executes it. It does not assert the whole suite ran, and its finite oscillator cases do not prove a universal runtime bound. |
| ownership | All local test owners unwind on return/exception; stdout/stderr are borrowed process streams. |
| failure | Any standard exception is caught at the test entry point and turns the test into a nonzero exit; non-standard exceptions are not caught. |
| cost | Runs the listed finite setup, planner, session and support-event cases; actual runtime cost depends on those scenarios and is not a production benchmark. |
| Design | [tests/unit/update_pattern_test.cpp](../../../../../tests/unit/update_pattern_test.cpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [docs/update_patterns.md](../../../../update_patterns.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md) |
