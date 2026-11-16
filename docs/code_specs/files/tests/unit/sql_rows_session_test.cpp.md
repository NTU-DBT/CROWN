# `tests/unit/sql_rows_session_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_rows_session_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `b8ff2918f1a7e2368c1d7a90abacbd7ff42efa01f1ef26ac0de241afe4450184`. 462 lines partitioned into 30 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/sql_rows_session_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Resolve the bag oracle row against crown::Row. · [reviewed contract](#b0001) |
| [B0002 · 17–22](../../../../../tests/unit/sql_rows_session_test.cpp#L17) | Callable definition: template&lt;std::size_t N&gt; void log_input(sr::Session& session, const std::array&lt;Replacement, N&gt;& replacements, std::uint64_t comman… | calls log · [reviewed contract](#b0002) |
| [B0003 · 23–23](../../../../../tests/unit/sql_rows_session_test.cpp#L23) | Explanatory comments or spacing. |  |
| [B0004 · 24–51](../../../../../tests/unit/sql_rows_session_test.cpp#L24) | Callable definition: template&lt;std::size_t N&gt; DecodedRowEpoch commit(sr::Session& session, const frontend::SqlRowsProgram& program, const std::array&lt;Re… | calls state, log_input, decide, assert; guard assert(!decision.rejected && decision.command_sequence == command);; returns epoch · [reviewed contract](#b0004) |
| [B0005 · 52–52](../../../../../tests/unit/sql_rows_session_test.cpp#L52) | Explanatory comments or spacing. |  |
| [B0006 · 53–69](../../../../../tests/unit/sql_rows_session_test.cpp#L53) | Callable definition: template&lt;std::size_t N&gt; sr::Decision reject(sr::Session& session, const std::array&lt;Replacement, N&gt;& replacements, sr::RejectReaso… | calls state, log_input, decide, assert; guard assert(decision.rejected == expected && decision.command_sequence == command);; returns decision · [reviewed contract](#b0006) |
| [B0007 · 70–70](../../../../../tests/unit/sql_rows_session_test.cpp#L70) | Explanatory comments or spacing. |  |
| [B0008 · 71–73](../../../../../tests/unit/sql_rows_session_test.cpp#L71) | Callable definition: void check_current(sr::Session& session, const Bag& expected) | calls assert, current_bag; guard assert(current_bag(session) == expected); · [reviewed contract](#b0008) |
| [B0009 · 74–74](../../../../../tests/unit/sql_rows_session_test.cpp#L74) | Explanatory comments or spacing. |  |
| [B0010 · 75–90](../../../../../tests/unit/sql_rows_session_test.cpp#L75) | Callable definition: void plain_bag_uint64_retraction(bool indexed) | calls f, create, number, text; guard assert(session.source_weight(TableId{0}, physical) == large);; growth insert · [reviewed contract](#b0010) |
| [B0011 · 91–91](../../../../../tests/unit/sql_rows_session_test.cpp#L91) | Explanatory comments or spacing. |  |
| [B0012 · 92–103](../../../../../tests/unit/sql_rows_session_test.cpp#L92) | Callable definition: Bag self_join_oracle(const Bag& source) | calls add, multiply; returns result; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 104–104](../../../../../tests/unit/sql_rows_session_test.cpp#L104) | Explanatory comments or spacing. |  |
| [B0014 · 105–137](../../../../../tests/unit/sql_rows_session_test.cpp#L105) | Callable definition: void nullable_projection_and_self_join(bool indexed) | calls f, bag_schema, create, number; guard assert((current_bag(session) == Bag{{Row{std::nullopt}, 4}}));; source comment (unverified): // A witness loses two physical copies; both aliases see the weight change. · [reviewed contract](#b0014) |
| [B0015 · 138–138](../../../../../tests/unit/sql_rows_session_test.cpp#L138) | Explanatory comments or spacing. |  |
| [B0016 · 139–173](../../../../../tests/unit/sql_rows_session_test.cpp#L139) | Callable definition: void distinct_and_exists_zero_crossings(bool indexed) | calls number, text, f, bag_schema; growth insert; source comment (unverified): // Visible DISTINCT support does not cross zero. · [reviewed contract](#b0016) |
| [B0017 · 174–174](../../../../../tests/unit/sql_rows_session_test.cpp#L174) | Explanatory comments or spacing. |  |
| [B0018 · 175–183](../../../../../tests/unit/sql_rows_session_test.cpp#L175) | Callable definition: Catalog foreign_key_schema() | calls push_back; returns catalog; growth push_back · [reviewed contract](#b0018) |
| [B0019 · 184–184](../../../../../tests/unit/sql_rows_session_test.cpp#L184) | Explanatory comments or spacing. |  |
| [B0020 · 185–235](../../../../../tests/unit/sql_rows_session_test.cpp#L185) | Callable definition: void net_batch_foreign_key_and_semantic_overflow(bool indexed) | calls f, create, number, commit; guard assert(epoch.rows.empty() && epoch.changed == false);; growth insert; source comment (unverified): // Delivery consumed the exact empty epoch spool. · [reviewed contract](#b0020) |
| [B0021 · 236–236](../../../../../tests/unit/sql_rows_session_test.cpp#L236) | Explanatory comments or spacing. |  |
| [B0022 · 237–270](../../../../../tests/unit/sql_rows_session_test.cpp#L237) | Callable definition: void pending_input_resource_retry_and_reopen() | calls number, text, create, log_input; guard assert(failed && !session.requires_reopen()); · [reviewed contract](#b0022) |
| [B0023 · 271–271](../../../../../tests/unit/sql_rows_session_test.cpp#L271) | Explanatory comments or spacing. |  |
| [B0024 · 272–300](../../../../../tests/unit/sql_rows_session_test.cpp#L272) | Callable definition: void committed_undelivered_reopen_and_exact_retry() | calls number, text, create, log_input; guard assert(!session.decide().rejected);; source comment (unverified): // Header and one exact epoch. · [reviewed contract](#b0024) |
| [B0025 · 301–301](../../../../../tests/unit/sql_rows_session_test.cpp#L301) | Explanatory comments or spacing. |  |
| [B0026 · 302–363](../../../../../tests/unit/sql_rows_session_test.cpp#L302) | Callable definition: void checkpoint_restore_next_update_and_history_cap(bool indexed) | calls f, number, text, create; guard assert(session.source_weight(TableId{0}, physical) == 2);; growth insert · [reviewed contract](#b0026) |
| [B0027 · 364–364](../../../../../tests/unit/sql_rows_session_test.cpp#L364) | Explanatory comments or spacing. |  |
| [B0028 · 365–446](../../../../../tests/unit/sql_rows_session_test.cpp#L365) | Callable definition: void false_decision_and_sink_fail_before_torn_repair() | calls number, text, create, commit; guard assert(reject(session, invalid, sr::RejectReason::weight_mismatch).physical_sequence == 1);; growth insert; 1 loop sites; source comment (unverified): // Replace the valid typed value 4 with 5 and recompute both frame checksums. · [reviewed contract](#b0028) |
| [B0029 · 447–449](../../../../../tests/unit/sql_rows_session_test.cpp#L447) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0029) |
| [B0030 · 450–462](../../../../../tests/unit/sql_rows_session_test.cpp#L450) | Callable definition: int main() | calls plain_bag_uint64_retraction, nullable_projection_and_self_join, distinct_and_exists_zero_crossings, net_batch_foreign_key_and_semantic_overflow; 1 loop sites · [reviewed contract](#b0030) |

## B0001

[Lines 1–16](../../../../../tests/unit/sql_rows_session_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:fd2ea10458a1f473d884ae2b19a7370d2358dc69d8a3da30c5cf65c14e9a40fe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare dependencies and resolve the test’s expected bag Row type explicitly. |
| inputs / outputs | Imports the shared fixture and test helpers, then locally aliases Row to runtime::aggregate::Row so the intended output-row type wins over the crown::Row imported by namespace directives. |
| invariants | This test oracle uses nullable runtime::aggregate::Row values. The local alias removes lookup ambiguity without changing fixture data or runtime behavior. |
| ownership | This declaration region owns no runtime state; imported headers define their own lifetimes. |
| failure | Missing/incompatible declarations fail compilation; the alias itself has no runtime failure path. |
| cost | Compile-time declarations only. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0002

[Lines 17–22](../../../../../tests/unit/sql_rows_session_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L22:sha256:444b646d837bf31efc8b602d16220bee516bd9007665ba2fc1d857bff26f18f3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Log one command with source and reader positions. |
| inputs / outputs | Takes Session, replacements, command and source offset; logs using source id rows and ReaderPosition(offset, command). |
| invariants | The command is forwarded unchanged and source/reader progress are recorded together. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | One log operation for a fixed replacement array. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0004

[Lines 24–51](../../../../../tests/unit/sql_rows_session_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L51:sha256:550264d80292d3ccd680736d613144ab7f500b0a70955ab78a43e131527f39fa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit, decode, compare, and deliver one row epoch. |
| inputs / outputs | Takes Session, program, replacements, expected changes and source-changed flag; returns decoded epoch. |
| invariants | Checks frontiers, sequence values, independent typed changes, delivery, source offset and reader position. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | One log/decide/deliver cycle plus frame decode. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0006

[Lines 53–69](../../../../../tests/unit/sql_rows_session_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L69:sha256:56c13ab1362343b3e729ae55b282a34e73a23988b18526a7fae83e2bd1beffba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert one semantic rejection. |
| inputs / outputs | Logs replacements and calls decide; checks expected reason and progress/frontier outcome. |
| invariants | Rejected command is disposed; physical commit/delivery and output stay unchanged. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | One log and semantic decision. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0008

[Lines 71–73](../../../../../tests/unit/sql_rows_session_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L73:sha256:ae163fe4eb987ad74960b9068a6e2d2e4ea5f0230867077ee600b5c0f502a00a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare current Session bag to expected bag. |
| inputs / outputs | Drains current_bag and compares exact output-row weights. |
| invariants | Uses typed tuple equality and uint64 multiplicities. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | One full result cursor drain. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0010

[Lines 75–90](../../../../../tests/unit/sql_rows_session_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L90:sha256:4bb9db5708362e8ceadc0e5ac0ab635ab1550e094460b7c6e38693b6a966f11f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise plain bag weight above INT64_MAX and exact retraction. |
| inputs / outputs | On both backends inserts 2^63+12345 copies, verifies row epoch/current/source weight, then retracts all copies. |
| invariants | Oracle preserves unsigned magnitude and retraction sign without signed narrowing. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Two durable updates with one-row output checks. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0012

[Lines 92–103](../../../../../tests/unit/sql_rows_session_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L103:sha256:eb9de36a8a2dfef5fcfe5ebad66f70631b808a9767c8d3a4ba97d4809e8530b8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute independent expected bag for a self-join. |
| inputs / outputs | Joins each positive-id source row pair with equal key and projects nullable x. |
| invariants | Products/sums use checked uint64 arithmetic and NULL remains a tuple value. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Quadratic pair loop over this small fixture bag. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0014

[Lines 105–137](../../../../../tests/unit/sql_rows_session_test.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L137:sha256:5dcd8b5a78ab733738b5d3bd6ce0bcbdd437e847249b846e5520a0b9f812a44f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check nullable projection and self-join witness weight changes. |
| inputs / outputs | On both backends applies four physical updates and compares every signed delta to before/after oracle bags. |
| invariants | Covers NULL projection, matched aliases, positive-id filter, weight changes and deletion. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Four durable updates and small pairwise oracle scans. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0016

[Lines 139–173](../../../../../tests/unit/sql_rows_session_test.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L139-L173:sha256:40ccbac3ea39663c64be7b6dc3ada8a849612d396dbc337c90bd35d7e49dd701
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check DISTINCT and EXISTS zero crossings. |
| inputs / outputs | DISTINCT adds/removes multiple witnesses; EXISTS toggles false-to-true and true-to-false. |
| invariants | Visible DISTINCT support has unit weight; EXISTS Boolean rows are unit weight and change in opposite signs. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Four DISTINCT and two EXISTS updates plus cursor checks. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0018

[Lines 175–183](../../../../../tests/unit/sql_rows_session_test.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L175-L183:sha256:eb8053c139c7f1e8313d714784c78f522b0bb945e0412482c188fee846d4cd7f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build enforced parent/child key schema. |
| inputs / outputs | Returns catalog with parent primary key and child foreign key on pid. |
| invariants | Constraint identifiers and enforced status match the small fixed catalog. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Small schema construction. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0020

[Lines 185–235](../../../../../tests/unit/sql_rows_session_test.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L235:sha256:df440f68403422bbf445ec4c53a636dd56fe0380b1992b6ad0de4bd6a14ff88d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check net batches, foreign keys and semantic annotation overflow. |
| inputs / outputs | Three subcases test canceling net edits, FK insert/delete ordering, and self-join overflow rejection followed by retry. |
| invariants | Empty net output has no changed flag; FK validates final net state; semantic rejection preserves prior source and physical state. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Fixed finite batches on both backends. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0022

[Lines 237–270](../../../../../tests/unit/sql_rows_session_test.cpp#L237); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L237-L270:sha256:a455c733ee602d10b56ea023d67a904ed0f87df75201191cfbf3558e4e836d43
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check pending input survives resource failure and reopen. |
| inputs / outputs | Denies first intercepted allocation during decide, verifies pending state, destroys owner, recovers and successfully decides/delivers. |
| invariants | Resource failure is retryable and not a semantic Reject; logged progress remains distinct from applied progress. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | One injected failure plus one recovery and update. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0024

[Lines 272–300](../../../../../tests/unit/sql_rows_session_test.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L272-L300:sha256:36820ff9cb5ccfa2c9368935a6963b6b098c059ffcd26748372993254504d35f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check committed undelivered frame is recovered and delivered once. |
| inputs / outputs | Copies committed output, reopens and compares exact bytes, delivers, then reopens to verify one sink epoch and no spool. |
| invariants | Commit precedes delivery; reopen retains exact frame; repeat delivery adds no duplicate. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | One commit, two recoveries, one delivery. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0026

[Lines 302–363](../../../../../tests/unit/sql_rows_session_test.cpp#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L302-L363:sha256:dcdcf8b093b205503d55f0c6210c7d4c8c56572b57f7b3b798346b4a766202cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check checkpoint restoration, next update and history cap. |
| inputs / outputs | Across both backends recovers/checkpoints generation 2, applies next update/checkpoints generation 3, verifies final progress; separate cap fixture refuses beyond two generations. |
| invariants | Checks source weights, current bag, reader positions, replay work and selected roots; cap refusal leaves owner healthy. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Finite updates/checkpoints/recoveries with one output row. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_checkpoint.hpp](../../../../../include/crown/recovery/sql_rows_checkpoint.hpp) |

## B0028

[Lines 365–446](../../../../../tests/unit/sql_rows_session_test.cpp#L365); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L365-L446:sha256:6c134c3de3e200df8d422afc416dc16876b0d30a4b92f8e95d86f311d077e749
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject false decisions and sink output before torn-tail repair. |
| inputs / outputs | Re-encodes false Reject; then separately changes typed sink value and rebinds commit hash/bytes; both append torn suffixes and require public recovery refusal before files change. |
| invariants | Recovery replays semantic decision and generated output against durable bytes before repair; valid restored files recover. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Two corruption fixtures, bounded frame rewrites and receiver passes. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [src/recovery/sql_rows_session_replay.cpp](../../../../../src/recovery/sql_rows_session_replay.cpp) |

## B0029

[Lines 447–449](../../../../../tests/unit/sql_rows_session_test.cpp#L447); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L447-L449:sha256:ca577cbc6a8d67316fef9a0d7f55d33179b8f6889d41ade799bac8ac78469ed5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous test namespace. |
| inputs / outputs | Ends private helpers before main. |
| invariants | No extra callable behavior is declared. |
| ownership | This declaration/comment region owns no runtime state; object lifetimes are defined by the adjacent callable or type. |
| failure | No executable failure path is introduced by this declaration/comment region. |
| cost | Compile-time delimiter. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |

## B0030

[Lines 450–462](../../../../../tests/unit/sql_rows_session_test.cpp#L450); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L450-L462:sha256:ace76bbfa68eb87b3884562c3e79e5335fff10b6886062db36c3482304c8ee69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the finite durable row-session cases. |
| inputs / outputs | Runs bag, self-join, DISTINCT/EXISTS, net-batch/FK/overflow, resource reopen, undelivered output, checkpoint, corruption cases and prints success. |
| invariants | The enumerated cases are regression coverage, not general SQL conformance or performance evidence. |
| ownership | Parameters are borrowed unless the called API copies or moves them; return values own storage according to their declared types. Session state is held by an explicit test fixture or returned Session. |
| failure | A false assert fails the test process; allocation, binding, cursor, and filesystem errors propagate unless this test case catches the specific expected failure. |
| cost | Finite deterministic fixture suite and small oracle loops. |
| Design | [tests/unit/sql_rows_session_test.cpp](../../../../../tests/unit/sql_rows_session_test.cpp), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp) |
