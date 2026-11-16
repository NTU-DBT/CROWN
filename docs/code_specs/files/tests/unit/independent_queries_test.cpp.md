# `tests/unit/independent_queries_test.cpp` — block usage map

[Source](../../../../../tests/unit/independent_queries_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `8a422dd5c4c841510bc266022fdf191d9daa99e7520404986e09a051e5c269c5`. 423 lines partitioned into 38 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/unit/independent_queries_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 22–24](../../../../../tests/unit/independent_queries_test.cpp#L22) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 25–25](../../../../../tests/unit/independent_queries_test.cpp#L25) | Explanatory comments or spacing. |  |
| [B0004 · 26–35](../../../../../tests/unit/independent_queries_test.cpp#L26) | Callable definition: template&lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls action, check, code, std::runtime_error; guard check(error.code() == code, "unexpected CROWN error code"); · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/unit/independent_queries_test.cpp#L36) | Explanatory comments or spacing. |  |
| [B0006 · 37–42](../../../../../tests/unit/independent_queries_test.cpp#L37) | Callable definition: SessionOptions session_options() | calls ; returns result · [reviewed contract](#b0006) |
| [B0007 · 43–43](../../../../../tests/unit/independent_queries_test.cpp#L43) | Explanatory comments or spacing. |  |
| [B0008 · 44–48](../../../../../tests/unit/independent_queries_test.cpp#L44) | Callable definition: reoptimization::Options migration_options() | calls ; returns result · [reviewed contract](#b0008) |
| [B0009 · 49–49](../../../../../tests/unit/independent_queries_test.cpp#L49) | Explanatory comments or spacing. |  |
| [B0010 · 50–52](../../../../../tests/unit/independent_queries_test.cpp#L50) | Callable definition: QuerySession::Owner make_session(const PhysicalPlan& plan, const Database& initial) | calls QuerySession::create_typed, session_options; returns QuerySession::create_typed(plan, initial, {}, session_options()) · [reviewed contract](#b0010) |
| [B0011 · 53–53](../../../../../tests/unit/independent_queries_test.cpp#L53) | Explanatory comments or spacing. |  |
| [B0012 · 54–59](../../../../../tests/unit/independent_queries_test.cpp#L54) | Callable definition: Rows rows(QuerySession& session) | calls snapshot, check, insert, storage::export_row; guard check(result.insert(storage::export_row(tuple.values())).second, "duplicate session snapshot row");; returns result; growth insert; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 60–60](../../../../../tests/unit/independent_queries_test.cpp#L60) | Explanatory comments or spacing. |  |
| [B0014 · 61–66](../../../../../tests/unit/independent_queries_test.cpp#L61) | Callable definition: Rows rows(const SessionSnapshot& snapshot) | calls check, insert, storage::export_row, values; guard check(result.insert(storage::export_row(tuple.values())).second, "duplicate retained snapshot row");; returns result; growth insert; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 67–67](../../../../../tests/unit/independent_queries_test.cpp#L67) | Explanatory comments or spacing. |  |
| [B0016 · 68–82](../../../../../tests/unit/independent_queries_test.cpp#L68) | Callable definition: SignedRows update(QuerySession& session, const PhysicalSetUpdate& item) | calls batch, check, enqueue, empty; guard check(session.enqueue(batch) == io::Admission::accepted && batch.empty(), "session input was not ad…; returns result; growth emplace; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 83–83](../../../../../tests/unit/independent_queries_test.cpp#L83) | Explanatory comments or spacing. |  |
| [B0018 · 84–91](../../../../../tests/unit/independent_queries_test.cpp#L84) | Type/record definition: struct Fingerprint |  · [reviewed contract](#b0018) |
| [B0019 · 92–92](../../../../../tests/unit/independent_queries_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0020 · 93–99](../../../../../tests/unit/independent_queries_test.cpp#L93) | Callable definition: Fingerprint fingerprint(QuerySession& session) | calls accounted_memory_statistics, check, has_value, status; guard check(memory.has_value(), "live session did not report its native account");; returns {session.progress(), rows(session), std::string(session.report_metadata().plan().physical_sha256()), · [reviewed contract](#b0020) |
| [B0021 · 100–100](../../../../../tests/unit/independent_queries_test.cpp#L100) | Explanatory comments or spacing. |  |
| [B0022 · 101–108](../../../../../tests/unit/independent_queries_test.cpp#L101) | Callable definition: void unchanged(QuerySession& session, const Fingerprint& expected) | calls fingerprint, check; guard check(actual.progress == expected.progress && actual.result == expected.result && · [reviewed contract](#b0022) |
| [B0023 · 109–109](../../../../../tests/unit/independent_queries_test.cpp#L109) | Explanatory comments or spacing. |  |
| [B0024 · 110–114](../../../../../tests/unit/independent_queries_test.cpp#L110) | Callable definition: Database empty_database(std::size_t tables) | calls resize; returns result; growth resize · [reviewed contract](#b0024) |
| [B0025 · 115–115](../../../../../tests/unit/independent_queries_test.cpp#L115) | Explanatory comments or spacing. |  |
| [B0026 · 116–191](../../../../../tests/unit/independent_queries_test.cpp#L116) | Callable definition: void interleaved_ids_and_snapshot(const PhysicalPlan& plan, const Database& initial) | calls directory, make_session, empty_database, size; guard check(!first && !second && first_native != second_native, "admission merged or retained caller owne…; growth insert; source comment (unverified): // The C02 fixture has an empty query head: its true Boolean witness is Row{}. · [reviewed contract](#b0026) |
| [B0027 · 192–192](../../../../../tests/unit/independent_queries_test.cpp#L192) | Explanatory comments or spacing. |  |
| [B0028 · 193–248](../../../../../tests/unit/independent_queries_test.cpp#L193) | Callable definition: void admission_limits(const PhysicalPlan& plan, const Database& initial) | calls zero_slots, expect_error, admit, check; guard check(!null_owner && zero_slots.size() == 0, "null-owner rejection changed a zero-slot directory"); · [reviewed contract](#b0028) |
| [B0029 · 249–249](../../../../../tests/unit/independent_queries_test.cpp#L249) | Explanatory comments or spacing. |  |
| [B0030 · 250–305](../../../../../tests/unit/independent_queries_test.cpp#L250) | Callable definition: void failures_are_independent(const PhysicalPlan& plan, const Database& initial) | calls directory, session_options, QuerySession::create, make_session; guard check(parse_failed && directory.at(malformed_id).status().input_failed &&; growth allocate, insert, make_unique, reserve; source comment (unverified): // Keep the same empty-head Boolean witness in the healthy query. · [reviewed contract](#b0030) |
| [B0031 · 306–306](../../../../../tests/unit/independent_queries_test.cpp#L306) | Explanatory comments or spacing. |  |
| [B0032 · 307–319](../../../../../tests/unit/independent_queries_test.cpp#L307) | Callable definition: reoptimization::Status verify_replan(QuerySession& session) | calls pause, request_reoptimization_barrier, advance_reoptimization, std::runtime_error; returns status; 1 loop sites · [reviewed contract](#b0032) |
| [B0033 · 320–320](../../../../../tests/unit/independent_queries_test.cpp#L320) | Explanatory comments or spacing. |  |
| [B0034 · 321–397](../../../../../tests/unit/independent_queries_test.cpp#L321) | Callable definition: void replan_and_recovery_are_independent(const PhysicalPlan& basis, const planner::CandidateSnapshot& family, const PhysicalOptio… | calls directory, make_session, empty_database, size; guard check(update(directory.at(other_id), {1, TableId{0}, SetOperation::insert, Row{std::int64_t{1}}}).e…; growth insert · [reviewed contract](#b0034) |
| [B0035 · 398–398](../../../../../tests/unit/independent_queries_test.cpp#L398) | Explanatory comments or spacing. |  |
| [B0036 · 399–408](../../../../../tests/unit/independent_queries_test.cpp#L399) | Callable definition: void backend_case(bool indexed, const c02_test::Fixture& fixture, const planner::CandidateSnapshot& family) | calls s04_runtime::options, planner::lower_tree, candidate, tree · [reviewed contract](#b0036) |
| [B0037 · 409–410](../../../../../tests/unit/independent_queries_test.cpp#L409) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0037) |
| [B0038 · 411–423](../../../../../tests/unit/independent_queries_test.cpp#L411) | Callable definition: int main() | calls c02_test::fixture, c02_test::candidates, check, candidate_count; guard check(family.candidate_count() == 3, "independent-query C06 candidate family changed");; returns 0; 1; 1 loop sites · [reviewed contract](#b0038) |

## B0001

[Lines 1–21](../../../../../tests/unit/independent_queries_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:fd475e66a3e37987582360687a92d97f0a4443e017beff2b6b224340a5017d9a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the public query directory API, C06/recovery fixtures, and test-only standard helpers. |
| inputs / outputs | The file consumes the public IndependentQueries and QuerySession interfaces plus existing C02 candidate, indexed-backend, and generation-recovery fixtures; local aliases and test helpers feed the test functions. |
| invariants | The unit is scoped to serial independent QuerySession owners and the declared X10 directory contract. Imported C06/recovery helpers supply real native factories and durable paths, not mocked session state. |
| ownership | Imports and aliases create no session or account ownership. Factory results later own sessions; ID values and references returned by at(id) remain borrowed/non-owning. |
| failure | Missing or incompatible declarations stop compilation; runtime behavior is asserted by the following tests. |
| cost | Preprocessing and template/type checking contribute compile-time cost. This block makes no runtime or test-pass claim. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [include/crown/runtime/queries.hpp](../../../../../include/crown/runtime/queries.hpp), [src/runtime/queries.cpp](../../../../../src/runtime/queries.cpp) |

## B0002

[Lines 22–24](../../../../../tests/unit/independent_queries_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L24:sha256:36760bf0ac3e0954ae0ba67f0a04474242529918551994055eeb8347a23cbd61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a concise test failure when one condition is false. |
| inputs / outputs | Accepts a boolean and message; returns normally when the condition holds and throws std::runtime_error otherwise. |
| invariants | Only test control flow changes; this helper does not reinterpret a CROWN status or make a production decision. |
| ownership | Borrows the message view for the call and owns no query state. |
| failure | A false condition throws a test exception and fails the unit. |
| cost | One boolean branch and, on failure, exception construction; no repeated native work. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0004

[Lines 26–35](../../../../../tests/unit/independent_queries_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L35:sha256:263e379ce5e8c7294d22046961a9ae780d45e5de214758dd4a602a791fb99cd9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert a requested public CROWN error code from one action. |
| inputs / outputs | Invokes the callable once and returns only when a caught crown::Error has the expected code. |
| invariants | Only the named CROWN error family is accepted; unexpected codes fail the test and unrelated exception types propagate. |
| ownership | Borrows the callable and code view; owns no session or result. |
| failure | No CROWN error or a wrong code raises std::runtime_error; other exceptions are not swallowed. |
| cost | One action and one catch/compare path. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0006

[Lines 37–42](../../../../../tests/unit/independent_queries_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L42:sha256:4814001c9b78290428ae41e1d06907c97089717cde06637cc2bd7d362f641651
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the real sessions to delta mode with a finite per-query native budget. |
| inputs / outputs | Returns SessionOptions selecting DeltaMode::delta and a 64 MiB support-memory limit. |
| invariants | This is a fixture limit for exercising independent query accounts, not a combined directory allowance. |
| ownership | Returns a small value object; the session factory copies its configuration into the new owner. |
| failure | No explicit runtime rejection is implemented here; factory validation errors propagate. |
| cost | Fixed-size option construction. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0008

[Lines 44–48](../../../../../tests/unit/independent_queries_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L48:sha256:a8f6e28b9a8fe0c6e0cb7bbe4a8884718a3cf5d19a12efab05d06215802ea93a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide an eligible caller forecast for the C06 switch fixture. |
| inputs / outputs | Returns reoptimization options with a finite measured/current baseline and a deliberately favorable caller forecast. |
| invariants | The forecast enables the publication path but is test input, not an observed performance claim. |
| ownership | Returns value data and retains no session, account, or candidate. |
| failure | No helper-specific failure branch; API errors occur when the session consumes the options. |
| cost | Constant-size options construction. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0010

[Lines 50–52](../../../../../tests/unit/independent_queries_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L52:sha256:b3c9750acdf65265e03903fd6409abfc198e4353219bf181d0c6f5290ca97d14
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a genuine typed QuerySession from an existing physical plan and database. |
| inputs / outputs | Passes the plan, supplied initial database, default queue limits, and local test options to QuerySession::create_typed. |
| invariants | Every call uses the production public factory and obtains an independent QuerySession account. |
| ownership | Returns the factory-owned QuerySession::Owner to the caller. |
| failure | Factory admission, plan, or native memory failures propagate. |
| cost | Cost is session initialization on the supplied physical plan and source rows. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0012

[Lines 54–59](../../../../../tests/unit/independent_queries_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L59:sha256:fde357f043ba61a84822c055ea333f0a36649f1533fc818c1f6a87a2ffb7234d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export committed native snapshot tuples into an ordinary test relation. |
| inputs / outputs | Calls the public snapshot method and copies each tuple into a set of host-owned rows. |
| invariants | Duplicate output rows are rejected; the resulting set is a test comparison, not a second native runtime. |
| ownership | The returned rows own copied scalar values; the temporary SessionSnapshot retains its normal lifetime. |
| failure | Snapshot budget or duplicate-row assertion failures fail the test. |
| cost | Visits each returned snapshot tuple once and allocates host set nodes per row. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0014

[Lines 61–66](../../../../../tests/unit/independent_queries_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L66:sha256:7650ee7bc0fa14ec9941da9494e618eae62a2e7434bd83b7bae96e6289e4b7fb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy rows from an already owning SessionSnapshot. |
| inputs / outputs | Converts each snapshot tuple into an ordinary set for checking its post-session lifetime. |
| invariants | The helper reads only the supplied snapshot; it never looks up or dispatches through a directory ID. |
| ownership | Borrows the SessionSnapshot and returns independently copied row values. |
| failure | Duplicate rows fail the unit. |
| cost | Linear in the retained result rows plus host-set insertion cost. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0016

[Lines 68–82](../../../../../tests/unit/independent_queries_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L82:sha256:ba5c5249c2743e307d14fe91c9fa56a7488b6e74902e05dc4ddb9e349efcec99
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute and drain one actual typed physical input on a QuerySession. |
| inputs / outputs | Enqueues a one-event TransportBatch, begins it, steps to prepared, commits, and returns its signed native output as copied rows. |
| invariants | The batch must be accepted and consumed; only committed output is returned. A finite step guard prevents a nonterminating test loop. |
| ownership | The session reference is borrowed; the session retains native state, while returned output owns copied values. |
| failure | Admission, native-memory, or runtime errors propagate; guard failures fail the test without suppressing them. |
| cost | One input plus its actual native propagation steps, output transfer, and test set insertions. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0018

[Lines 84–91](../../../../../tests/unit/independent_queries_test.cpp#L84); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L91:sha256:5f4744287f5be902eab0dc431bcd2a5a819fbee287e22b16e9005af8cf6f8f44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the independent query attributes captured for noninterference checks. |
| inputs / outputs | Stores copied progress, result rows, physical plan digest, query owner ID, native account ID, and committed sequence. |
| invariants | The fingerprint is used only as an equality witness around work on another session; IDs are not treated as security capabilities. |
| ownership | Value fields own their copies; no session, account control, or borrowed query reference is retained. |
| failure | No runtime failure path; allocation failures while copying data propagate. |
| cost | Copies progress/result values and a fixed set of scalar identifiers. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [include/crown/runtime/queries.hpp](../../../../../include/crown/runtime/queries.hpp), [src/runtime/queries.cpp](../../../../../src/runtime/queries.cpp) |

## B0020

[Lines 93–99](../../../../../tests/unit/independent_queries_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L99:sha256:2f03d73dff7ec0ff83cb4a0e85115ae92ec257acfb435a608acfafce4300f750
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one query’s current progress, results, plan identity, and account identity. |
| inputs / outputs | Reads public progress, snapshot, plan metadata, account statistics, and committed status into Fingerprint. |
| invariants | The snapshot and metadata refer to one serial test observation; captured fields do not authorize mutation. |
| ownership | Returns copied values; temporary metadata/snapshot handles end with this call. |
| failure | Missing native account state fails the test; query observation errors propagate. |
| cost | Visits the committed result rows and copies the progress/plan digest. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0022

[Lines 101–108](../../../../../tests/unit/independent_queries_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L108:sha256:e4466948eff4e6b6c3063a14593dd8b2429cdc4ee1bbef7e6b14d57e78fc2c5d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify that work on a different query left every captured state field unchanged. |
| inputs / outputs | Recomputes a Fingerprint and compares progress, results, physical plan, query/account IDs, and commit sequence. |
| invariants | Every field is compared; a matching result alone cannot hide changed source progress or owner identity. |
| ownership | Borrows the session and expected value; owns no native state. |
| failure | Any mismatch throws a test failure. |
| cost | Repeats one snapshot/fingerprint capture and fixed field comparisons. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0024

[Lines 110–114](../../../../../tests/unit/independent_queries_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L114:sha256:91f8878ac0fdfbb876eeae3c774251376b231354c3bfcadab86b01571983be90
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a source database with the requested number of empty tables. |
| inputs / outputs | Resizes and returns a new Database table vector. |
| invariants | The helper creates ordinary test input only; it does not initialize or share a native runtime. |
| ownership | The returned database owns its relation containers. |
| failure | Allocation failures propagate. |
| cost | Allocates one table slot per requested table. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp) |

## B0026

[Lines 116–191](../../../../../tests/unit/independent_queries_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L191:sha256:9418decb6d25c90441bd74e3efa39f1a4ee15b185d47933373f8123a2bd03507
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise interleaved owners, foreign/stale IDs, erase/release, and owning-snapshot survival for the empty-head Boolean witness. |
| inputs / outputs | Runs two real C02 QuerySessions against independently initialized source databases. The fixture head is empty, so a true Boolean answer is Row{}; interleaved source updates produce the expected signed witness and snapshots. |
| invariants | Query IDs remain directory-scoped and monotonic; each session owns separate progress/native account. The C02 fixture head is intentionally empty, preserving its family/min-height contract, and the Boolean result is represented by the zero-column Row{}. |
| ownership | The directory owns admitted QuerySession owners; at() references are used only while their IDs are live. A copied SessionSnapshot retains its documented native row storage after erase. |
| failure | Wrong IDs must raise query_id; rejected interleavings, duplicate rows, and ownership discrepancies fail the test. |
| cost | Runs a bounded five-event interleaving plus a small number of admissions, lookups, and snapshot copies; native work is confined to the real fixture updates. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [include/crown/runtime/queries.hpp](../../../../../include/crown/runtime/queries.hpp), [src/runtime/queries.cpp](../../../../../src/runtime/queries.cpp) |

## B0028

[Lines 193–248](../../../../../tests/unit/independent_queries_test.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L193-L248:sha256:5925aa5762759fda7651e77c1d7f3f22e95d41116ea08ac9bb34848ace2c0199
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check null-owner, zero-slot, query-count, and directory-memory admission rejection while retaining the incoming session owner. |
| inputs / outputs | Attempts admission with a null owner, a real owner into a zero-query directory, a second owner into a full directory, and a second owner after calibrating the exact one-node metadata budget. |
| invariants | Every rejected live owner remains with the caller and keeps its original native account; no rejected admission changes existing query state or directory accounting. Null-owner rejection does not mutate the empty zero-slot directory. |
| ownership | The incoming owner stays caller-owned on failure; the directory owns only the admitted first session. |
| failure | Count exhaustion must report query_limit. Metadata exhaustion must report resource::MemoryFailure(limit); other exceptions fail the test. |
| cost | Per backend, performs bounded directory admissions and one calibrated map-node failure; no query work is advanced. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [include/crown/runtime/queries.hpp](../../../../../include/crown/runtime/queries.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0030

[Lines 250–305](../../../../../tests/unit/independent_queries_test.cpp#L250); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L250-L305:sha256:ce0d5def4e4049c3c6fe1d8d3dbe45387e94eff75c946eb4b78cbc7487b19c28
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show malformed input and native-account exhaustion remain local to their query. |
| inputs / outputs | Uses a malformed real session input and a separately native-budget-constrained real session, while a healthy C02 Boolean query accepts its own source prefix and publishes the Row{} witness. |
| invariants | Parse failure and native allocation failure remain local to their session; failed input does not advance committed progress or publish partial output. The healthy empty-head Boolean query can continue and later erase its Row{} witness. |
| ownership | The directory owns all three session owners; the temporary MemoryBlock holds only the deliberately reserved bytes and is released before post-failure assertions. |
| failure | The malformed stream must become input_failed. The constrained native update must fail with MemoryFault::limit and preserve sequence zero; all unrelated errors propagate. |
| cost | Exercises three actual session inputs, one parse failure, one large temporary account reservation, and bounded continuation updates. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [include/crown/runtime/queries.hpp](../../../../../include/crown/runtime/queries.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0032

[Lines 307–319](../../../../../tests/unit/independent_queries_test.cpp#L307); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L307-L319:sha256:a674802d3e5e3bae20529d06cc68c4b653fba774b7ec88fae65e34fddd93c3b3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance the real C06 candidate barrier until it reaches a terminal result. |
| inputs / outputs | Pauses the session, requests its reoptimization barrier, and repeatedly advances with finite quanta until verified, failed, or rejected. |
| invariants | Only verified is accepted by the caller; the loop has a fixed upper bound and does not infer verification from plan construction. |
| ownership | Borrows the caller-owned QuerySession; retains no candidate or result handles. |
| failure | Exhausting the finite test guard throws; terminal C06 failure is returned for explicit assertion. |
| cost | At most 10,000 native candidate advances with a 10,000-unit quantum each. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [tests/unit/reoptimization_install_test.cpp](../../../../../tests/unit/reoptimization_install_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0034

[Lines 321–397](../../../../../tests/unit/independent_queries_test.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L321-L397:sha256:b532da154ee89a6d084a87a1dd42890ca273b3d10d5dd8585e484fb3a6a9c269
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Switch, recover, and readmit one query while checking the other remains unchanged. |
| inputs / outputs | Creates two real sessions and a non-switching C06 reference; uses a checked alternative candidate, processes an update, verifies and publishes the target compiler artifact, releases the durable owner, locks/replays/restores the selected generation, readmits it under a fresh QueryId, then commits the next update. |
| invariants | The target plan digest must actually change; publication preserves the switching query’s native account; recovery resumes exact progress/results; the second query fingerprint stays identical throughout. The recovered ID must advance beyond the released ID. |
| ownership | The directory owns sessions only between admission and release. Compiler accounts, locked recovery ownership, recovered owners, the reference session, and the temporary generation files follow their existing public lifetimes. |
| failure | Missing candidate/recovery descriptor, failed verification/publication, incorrect next output, or interference fails the test; errors propagate. |
| cost | Per backend performs two query inputs around real bounded reoptimization/publication and durable generation recovery, plus compiler artifact preparation/replay. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0036

[Lines 399–408](../../../../../tests/unit/independent_queries_test.cpp#L399); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L399-L408:sha256:c1e0b5a3b172ed818414bcd469dd410793cb8b7fa7389f4363f59726e9d52f46
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the independent-query scenarios with one physical backend configuration. |
| inputs / outputs | Lowers the checked fixture’s original candidate for reference or indexed storage, then calls interleaving/lifetime, admission-limit, isolated-failure, and real C06 publication/recovery cases. |
| invariants | The same semantic fixture and tests run once for each backend; the only switch is the existing physical options value. |
| ownership | The candidate family and fixture are borrowed; each called scenario creates and destroys its own native owners. |
| failure | Any scenario failure propagates to main and fails the executable. |
| cost | Lowers one physical basis and invokes four bounded test groups. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [include/crown/runtime/queries.hpp](../../../../../include/crown/runtime/queries.hpp), [src/runtime/queries.cpp](../../../../../src/runtime/queries.cpp) |

## B0037

[Lines 409–410](../../../../../tests/unit/independent_queries_test.cpp#L409); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L409-L410:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the local test namespace. |
| inputs / outputs | Ends the anonymous namespace containing helpers and test cases. |
| invariants | No runtime behavior is introduced. |
| ownership | Closes only lexical scope. |
| failure | Malformed scope is a compile error. |
| cost | No runtime cost. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [include/crown/runtime/queries.hpp](../../../../../include/crown/runtime/queries.hpp), [src/runtime/queries.cpp](../../../../../src/runtime/queries.cpp) |

## B0038

[Lines 411–423](../../../../../tests/unit/independent_queries_test.cpp#L411); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L411-L423:sha256:90331e226a4c19d10c0735bf16f7d4d8aa03f130884e31c10d0feb30fe07ab1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the checked fixture and run every scenario on both backends. |
| inputs / outputs | Creates the existing C02 exact candidate family, checks its expected three-member fixture, and runs backend_case for reference and indexed storage. |
| invariants | The check is not a global optimizer claim; it supplies the real public candidate needed to test session publication. Main returns failure on any exception and emits PASS only after both backends complete. |
| ownership | Main owns the ordinary fixture and immutable candidate snapshot; each backend case owns its temporary sessions and files. |
| failure | Fixture proof/candidate, native session, recovery, or assertion failures are printed and return exit status one. |
| cost | Builds the finite C02 fixture once and runs the bounded test cases for two physical configurations; no timing is collected. |
| Design | [tests/unit/independent_queries_test.cpp](../../../../../tests/unit/independent_queries_test.cpp), [build/verification/independent-queries-v61-v1/DESIGN.md](../../../../../build/verification/independent-queries-v61-v1/DESIGN.md), [include/crown/runtime/queries.hpp](../../../../../include/crown/runtime/queries.hpp), [src/runtime/queries.cpp](../../../../../src/runtime/queries.cpp) |
