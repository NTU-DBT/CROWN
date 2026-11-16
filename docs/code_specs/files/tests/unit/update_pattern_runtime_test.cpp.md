# `tests/unit/update_pattern_runtime_test.cpp` — block usage map

[Source](../../../../../tests/unit/update_pattern_runtime_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a861a49ba2f061dfce754a5ed965bef21ffc4bb2c0d6c8158e89c77871fed2c5`. 483 lines partitioned into 43 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/unit/update_pattern_runtime_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 22–28](../../../../../tests/unit/update_pattern_runtime_test.cpp#L22) | Callable definition: PhysicalPlan source_plan(bool indexed) | calls push_back, planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}); growth push_back; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 29–33](../../../../../tests/unit/update_pattern_runtime_test.cpp#L29) | Callable definition: SessionOptions declared(const CompiledProgram& program,std::span&lt;const ip::TableRule&gt; rules) | calls ip::Declaration::capture, account; returns options · [reviewed contract](#b0003) |
| [B0004 · 34–37](../../../../../tests/unit/update_pattern_runtime_test.cpp#L34) | Callable definition: WindowOptions window_options(WindowFifoPolicy policy=WindowFifoPolicy::unrestricted) | calls ; returns options · [reviewed contract](#b0004) |
| [B0005 · 38–38](../../../../../tests/unit/update_pattern_runtime_test.cpp#L38) | Callable definition: std::string_view bytes(const recovery::SessionImage& image) | calls data, size; returns {image.bytes.data(),image.bytes.size()} · [reviewed contract](#b0005) |
| [B0006 · 39–43](../../../../../tests/unit/update_pattern_runtime_test.cpp#L39) | Callable definition: void physical(QuerySession& session,PhysicalSetUpdate update) | calls batch, std::move, check, enqueue; guard check(session.enqueue(batch)==io::Admission::accepted,"physical fixture admission failed"); · [reviewed contract](#b0006) |
| [B0007 · 44–48](../../../../../tests/unit/update_pattern_runtime_test.cpp#L44) | Callable definition: void rejects(QuerySession& session,const char* code) | calls begin_next, code, check; guard check(failed,"event did not take its exact declared rejection path"); · [reviewed contract](#b0007) |
| [B0008 · 49–51](../../../../../tests/unit/update_pattern_runtime_test.cpp#L49) | Explanatory comments or spacing. | source comment (unverified): // No-op erases are deliberately rejected in the cheap nonwindow policy. Both · [reviewed contract](#b0008) |
| [B0009 · 52–82](../../../../../tests/unit/update_pattern_runtime_test.cpp#L52) | Callable definition: void insertion_contract(bool indexed,bool stream) | calls CompiledProgram::standalone, source_plan, declared, QuerySession::create; guard if(stream){check(session-&gt;begin_next(),"stream insertion missing");static_cast&lt;void&gt;(win::finish(*s…; growth insert, make_unique; source comment (unverified): // No-op erases are deliberately rejected in the cheap nonwindow policy. Both · [reviewed contract](#b0009) |
| [B0010 · 83–85](../../../../../tests/unit/update_pattern_runtime_test.cpp#L83) | Explanatory comments or spacing. | source comment (unverified): // Whole-command validation must detect B's premature final reference even when · [reviewed contract](#b0010) |
| [B0011 · 86–111](../../../../../tests/unit/update_pattern_runtime_test.cpp#L86) | Callable definition: void watermark_contract(bool indexed,WindowFifoPolicy policy) | calls CompiledProgram::standalone, source_plan, QuerySession::create_windowed, window_options; guard check(*session-&gt;window_state()==prefix && win::rows(*session)==rows && session-&gt;progress().sequence…; source comment (unverified): // Whole-command validation must detect B's premature final reference even when · [reviewed contract](#b0011) |
| [B0012 · 112–112](../../../../../tests/unit/update_pattern_runtime_test.cpp#L112) | Explanatory comments or spacing. |  |
| [B0013 · 113–127](../../../../../tests/unit/update_pattern_runtime_test.cpp#L113) | Callable definition: void duplicate_contract(bool indexed) | calls CompiledProgram::standalone, source_plan, QuerySession::create_windowed, window_options; guard check(session-&gt;status().committed_sequence==1 && session-&gt;progress().sequence==3 && · [reviewed contract](#b0013) |
| [B0014 · 128–132](../../../../../tests/unit/update_pattern_runtime_test.cpp#L128) | declares types or opens a type body. | source comment (unverified): // Independent lifetime-list model: it neither uses native birth IDs nor the · [reviewed contract](#b0014) |
| [B0015 · 133–133](../../../../../tests/unit/update_pattern_runtime_test.cpp#L133) | Type/record definition: struct Label |  · [reviewed contract](#b0015) |
| [B0016 · 134–134](../../../../../tests/unit/update_pattern_runtime_test.cpp#L134) | Type/record definition: struct Life |  · [reviewed contract](#b0016) |
| [B0017 · 135–135](../../../../../tests/unit/update_pattern_runtime_test.cpp#L135) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |
| [B0018 · 136–150](../../../../../tests/unit/update_pattern_runtime_test.cpp#L136) | Callable definition: bool remove(std::uint64_t id,bool per_table) | calls std::find_if, begin, end, check; guard const auto at=std::find_if(labels.begin(),labels.end(),\[&\](const auto& x){return x.id==id;});check(…; returns x.id==id; x.table==target.table && x.value==target.value · [reviewed contract](#b0018) |
| [B0019 · 151–165](../../../../../tests/unit/update_pattern_runtime_test.cpp#L151) | Callable definition: bool apply(const io::WindowCommand& command,bool per_table) | calls std::none_of, begin, end, push_back; returns x.table==table && x.value==value; true; growth emplace_back, insert, push_back; 2 loop sites · [reviewed contract](#b0019) |
| [B0020 · 166–166](../../../../../tests/unit/update_pattern_runtime_test.cpp#L166) | Closes surrounding scope/type. |  · [reviewed contract](#b0020) |
| [B0021 · 167–194](../../../../../tests/unit/update_pattern_runtime_test.cpp#L167) | Callable definition: void model_contract(bool indexed,bool per_table) | calls CompiledProgram::standalone, source_plan, QuerySession::create_windowed, window_options; guard check(failed && *session-&gt;window_state()==before,"lifetime-list oracle rejection differs or leaked …; growth insert; 2 loop sites · [reviewed contract](#b0021) |
| [B0022 · 195–197](../../../../../tests/unit/update_pattern_runtime_test.cpp#L195) | Explanatory comments or spacing. | source comment (unverified): // Separate scope IDs never imply a joint FIFO restriction. Metadata removal · [reviewed contract](#b0022) |
| [B0023 · 198–207](../../../../../tests/unit/update_pattern_runtime_test.cpp#L198) | Callable definition: void separate_scopes() | calls CompiledProgram::standalone, source_plan, QuerySession::create_windowed, window_options; guard check(session-&gt;window_state()-&gt;counts.size()==1 && !session-&gt;update_pattern_status().violation,; source comment (unverified): // Separate scope IDs never imply a joint FIFO restriction. Metadata removal · [reviewed contract](#b0023) |
| [B0024 · 208–208](../../../../../tests/unit/update_pattern_runtime_test.cpp#L208) | Explanatory comments or spacing. |  |
| [B0025 · 209–232](../../../../../tests/unit/update_pattern_runtime_test.cpp#L209) | Callable definition: void current_selection_contract() | calls c02_test::fixture, c02_test::candidates, CompiledProgram::standalone, planner::lower_tree; guard check(selected.stop==ps::Stop::complete && selected.selection && · [reviewed contract](#b0025) |
| [B0026 · 233–235](../../../../../tests/unit/update_pattern_runtime_test.cpp#L233) | Explanatory comments or spacing. | source comment (unverified): // Denial stays enabled through private cleanup. A retryable resource failure · [reviewed contract](#b0026) |
| [B0027 · 236–263](../../../../../tests/unit/update_pattern_runtime_test.cpp#L236) | Callable definition: void allocation_contract() | calls CompiledProgram::standalone, source_plan, QuerySession::create_windowed, window_options; guard {auto value=make();s04_alloc::Scope count;check(value-&gt;begin_next(),"healthy preflight missing");po…; returns value; 1 loop sites; source comment (unverified): // Denial stays enabled through private cleanup. A retryable resource failure · [reviewed contract](#b0027) |
| [B0028 · 264–266](../../../../../tests/unit/update_pattern_runtime_test.cpp#L264) | Explanatory comments or spacing. | source comment (unverified): // Error construction is fallible too. Denial remains active through unwinding; · [reviewed contract](#b0028) |
| [B0029 · 267–293](../../../../../tests/unit/update_pattern_runtime_test.cpp#L267) | Callable definition: void rejection_allocation_contract() | calls CompiledProgram::standalone, source_plan, QuerySession::create_windowed, window_options; guard check(positions&gt;0 && positions&lt;1000,"rejection allocation control not finite");; returns value; 1 loop sites; source comment (unverified): // Error construction is fallible too. Denial remains active through unwinding; · [reviewed contract](#b0029) |
| [B0030 · 294–296](../../../../../tests/unit/update_pattern_runtime_test.cpp#L294) | Explanatory comments or spacing. | source comment (unverified): // Measure the controller's abstract work, then use fresh identical histories · [reviewed contract](#b0030) |
| [B0031 · 297–324](../../../../../tests/unit/update_pattern_runtime_test.cpp#L297) | Callable definition: void work_contract() | calls CompiledProgram::standalone, source_plan, window_options, QuerySession::create_windowed; guard const auto work=measured-&gt;checkpoint_state().window-&gt;last_command_work;check(work&gt;1,"missing prefli…; returns value; value-&gt;checkpoint_state().window-&gt;last_command_work; 2 loop sites; source comment (unverified): // Measure the controller's abstract work, then use fresh identical histories · [reviewed contract](#b0031) |
| [B0032 · 325–327](../../../../../tests/unit/update_pattern_runtime_test.cpp#L325) | Explanatory comments or spacing. | source comment (unverified): // A v2 checkpoint survives actual file/log reconstruction, including a logged · [reviewed contract](#b0032) |
| [B0033 · 328–351](../../../../../tests/unit/update_pattern_runtime_test.cpp#L328) | Callable definition: void journal_contract(bool indexed) | calls file, CompiledProgram::standalone, source_plan, QuerySession::create_windowed; guard win::enqueue(*value,{3,io::AdvanceWatermark{10},{}});check(value-&gt;begin_next(),"pending journal mar…; 1 loop sites; source comment (unverified): // A v2 checkpoint survives actual file/log reconstruction, including a logged · [reviewed contract](#b0033) |
| [B0034 · 352–355](../../../../../tests/unit/update_pattern_runtime_test.cpp#L352) | Explanatory comments or spacing. | source comment (unverified): // Bind a measured pattern-conditioned choice to the real owner, publish its · [reviewed contract](#b0034) |
| [B0035 · 356–383](../../../../../tests/unit/update_pattern_runtime_test.cpp#L356) | Callable definition: void replacement_contract() | calls c02_test::fixture, c02_test::candidates, CompiledProgram::standalone, planner::lower_tree; guard check(selected.selection.has_value(),"measured declared selection failed");; source comment (unverified): // Bind a measured pattern-conditioned choice to the real owner, publish its · [reviewed contract](#b0035) |
| [B0036 · 384–386](../../../../../tests/unit/update_pattern_runtime_test.cpp#L384) | Explanatory comments or spacing. | source comment (unverified): // Public checkpoint records are trusted history, but source, version, shape, · [reviewed contract](#b0036) |
| [B0037 · 387–422](../../../../../tests/unit/update_pattern_runtime_test.cpp#L387) | Callable definition: void checkpoint_contract() | calls CompiledProgram::standalone, source_plan, QuerySession::create_typed, declared; guard check(failed,"v2 inspection ignored its rule grant");; growth insert; source comment (unverified): // Public checkpoint records are trusted history, but source, version, shape, · [reviewed contract](#b0037) |
| [B0038 · 423–426](../../../../../tests/unit/update_pattern_runtime_test.cpp#L423) | Explanatory comments or spacing. | source comment (unverified): // Export actual owner-bound diagnostics for schema validation. Requested rules · [reviewed contract](#b0038) |
| [B0039 · 427–450](../../../../../tests/unit/update_pattern_runtime_test.cpp#L427) | Callable definition: void report_contract(const std::filesystem::path& directory) | calls CompiledProgram::standalone, source_plan, QuerySession::create_typed, declared; guard check(profile.at("history_evidence")==history && profile.at("state")==state &&; growth insert; source comment (unverified): // Export actual owner-bound diagnostics for schema validation. Requested rules · [reviewed contract](#b0039) |
| [B0040 · 451–451](../../../../../tests/unit/update_pattern_runtime_test.cpp#L451) | Explanatory comments or spacing. |  |
| [B0041 · 452–467](../../../../../tests/unit/update_pattern_runtime_test.cpp#L452) | Callable definition: void admission_contract() | calls CompiledProgram::standalone, source_plan, QuerySession::create_typed, declared; guard catch(const Error& e){failed=e.code()=="unsupported_update_pattern";}check(failed,"nonwindow FIFO m… · [reviewed contract](#b0041) |
| [B0042 · 468–468](../../../../../tests/unit/update_pattern_runtime_test.cpp#L468) | Closes surrounding scope/type. |  · [reviewed contract](#b0042) |
| [B0043 · 469–483](../../../../../tests/unit/update_pattern_runtime_test.cpp#L469) | Callable definition: int main(int argc,char** argv) | calls admission_contract, separate_scopes, current_selection_contract, allocation_contract; returns 1; 1 loop sites · [reviewed contract](#b0043) |

## B0001

[Lines 1–21](../../../../../tests/unit/update_pattern_runtime_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:f5b1929949112b4f8ca7ca0a06e23bbaf4f723b8eefa6a270d40ebe2e850e675
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the test fixtures and public runtime, recovery, ingest, artifact, report, and generation interfaces in one anonymous namespace. |
| inputs / outputs | No runtime input/output; aliases expose the existing CROWN test/API types to later blocks. |
| invariants | Test-only scaffolding; no production hooks or behavior are introduced. |
| ownership | The translation unit owns its aliases and local namespace; included objects keep their normal owners. |
| failure | Missing/incompatible declarations fail compilation; no runtime failure path. |
| cost | Compile-time setup only. These tests are not paper evidence. |
| Design | [docs/update_patterns.md § test boundary](../../../../update_patterns.md), [docs/batches_windows.md § window identity](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0002

[Lines 22–28](../../../../../tests/unit/update_pattern_runtime_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L28:sha256:b72bee1037d9b4053d5529c3c2a40bd1eaae7e74d43c447a725caeb903d25e3a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a deterministic physical plan over four catalog tables and choose reference or indexed runtime setup. |
| inputs / outputs | indexed bool in; PhysicalPlan by value out. The query reads table r; four tables have stable IDs 0–3. |
| invariants | Only backend setup varies; catalog, query, and tree remain the same for paired tests. |
| ownership | Local catalog/query/tree are temporary; returned plan is an ordinary value. |
| failure | Planner/lowering errors propagate and fail the test. |
| cost | Small fixture creation, not a backend benchmark. |
| Design | [docs/physical_plans.md § admission and routes](../../../../physical_plans.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0003

[Lines 29–33](../../../../../tests/unit/update_pattern_runtime_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L33:sha256:1720309f29013eaea8f2f09594eab38beb78dcf9d2af5c77d7f953317c8d8cc4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture table rules against the actual compiled source and place the declaration in SessionOptions. |
| inputs / outputs | Program and borrowed rule span in; SessionOptions containing an immutable declaration handle out. |
| invariants | This requests source-bound metadata only; it does not establish an enforced prefix or prior history. |
| ownership | Declaration retains its account-backed owner; rules span is borrowed only during capture. |
| failure | Invalid rules or capture grant failures propagate. |
| cost | Rule-count capture work and retained metadata only. |
| Design | [docs/update_patterns.md § Declare a requested source contract](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0004

[Lines 34–37](../../../../../tests/unit/update_pattern_runtime_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L37:sha256:429fe7e755965bae05d192a967dc0a05bab622314fd8d7fce753a312d9ffecbb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create shared width-10 window options over all four fixture tables. |
| inputs / outputs | Optional FIFO policy in; WindowOptions with managed tables 0–3 and width 10 out. |
| invariants | Baseline policy is separate from explicit declaration scope and insertion-only rules. |
| ownership | Returns options by value; retains no session. |
| failure | Downstream admission failures propagate; no local failure. |
| cost | Fixed scalar/vector setup. |
| Design | [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0005

[Lines 38–38](../../../../../tests/unit/update_pattern_runtime_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:1c50d098cac0e4e7d7b4a472f49089b709b2382b2585b4513d25fcf63f1ebe18
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a non-owning byte view over a session image. |
| inputs / outputs | Image reference in; string_view of its exact bytes out. |
| invariants | View is valid only while the image storage remains alive and unchanged. |
| ownership | Image owns bytes; view does not extend lifetime. |
| failure | Caller misuse after image destruction is outside helper checks. |
| cost | O(1) view construction. |
| Design | [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0006

[Lines 39–43](../../../../../tests/unit/update_pattern_runtime_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L43:sha256:8aaab974e15a23093ab332905d2f22b7e173325774d85a4039bd86e538551dd1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and finish one physical update through the session fixture. |
| inputs / outputs | Borrowed QuerySession and owned update in; helper checks enqueue, begin, and fixture completion. |
| invariants | Requires accepting session and compatible update. |
| ownership | Session remains caller-owned; update moves into the accepted input event. |
| failure | Admission/begin mismatch fails check; other exceptions propagate. |
| cost | One event and its ordinary physical work. |
| Design | [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0007

[Lines 44–48](../../../../../tests/unit/update_pattern_runtime_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L48:sha256:4ab5601e3bd8494e231f8eeb26da93876a8cae72bccf5ae746d46ae45b0f9575
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require begin_next to throw Error with the exact expected code. |
| inputs / outputs | Borrowed session and code string in; returns only on exact error match. |
| invariants | Does not inspect full post-failure state; callers add those assertions. |
| ownership | Session owned by caller; code string borrowed. |
| failure | Unexpected success or code fails the test check; non-Error exceptions propagate. |
| cost | One begin and constant-size code comparison. |
| Design | [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0008

[Lines 49–51](../../../../../tests/unit/update_pattern_runtime_test.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L51:sha256:5226a0b4861a745a07249573d1df4de8260289a258e846cbd1b79feafe206e32
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the strict nonwindow insertion-only no-op erase case used below. |
| inputs / outputs | Comment only; the next test exercises typed and owned-stream paths. |
| invariants | Describes the intended case; not independent evidence of journal ordering or every input mode. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § Enforce a declaration through QuerySession](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0009

[Lines 52–82](../../../../../tests/unit/update_pattern_runtime_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L82:sha256:342159018893b6ecf2bc5bf603de77760b166d388658bf819568704ae9e4e218
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject absent-row erase commands on typed and owned-stream nonwindow sessions, then inspect committed diagnostics, runtime prefix, v2 image, and restored violation metadata. |
| inputs / outputs | Backend and stream selectors in; accepts one physical insert, proposes erase of value 999, checks update_pattern_violation, accepted-prefix status, sticky input_failed on the next begin, unchanged native image, v2 inspection with zero scoped s04_alloc calls, and restored status. |
| invariants | Even no-op erases are command violations. The committed native image remains unchanged. Scoped inspection check is limited to the C++ new test seam. The neighboring comment names journal/native preparation order, but this fixture attaches no journal and makes no journal-ordering assertion. |
| ownership | Session owns queue/reader/status; image owns bytes; restored session owns reconstructed state and history metadata. |
| failure | Any code/profile/image/version/allocation/restore mismatch fails check; setup and recovery errors propagate. |
| cost | Four cases: two backends × typed/owned-stream, each with one accepted and one rejected command plus checkpoint/restore. |
| Design | [docs/update_patterns.md § Enforce a declaration through QuerySession](../../../../update_patterns.md), [docs/update_patterns.md § Restore the declared contract](../../../../update_patterns.md), [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0010

[Lines 83–85](../../../../../tests/unit/update_pattern_runtime_test.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L85:sha256:46a0dd149ddbb0bc5a05e198942af89f695162b91cf29cd8ce8451959581b513
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the whole-watermark counterexample: unrelated expiration order precedes a later shared-scope final-reference violation. |
| inputs / outputs | Comment only; frames the next test. |
| invariants | The tested contract is no-prefix publication for a rejected proposal, not one sorting implementation. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § Validate before publication](../../../../update_patterns.md), [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0011

[Lines 86–111](../../../../../tests/unit/update_pattern_runtime_test.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L111:sha256:e49d81bbc781018bc4ac3ce26237681666d392cdd436ac60b6749e8c402711a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a full watermark proposal before any effect when its ordered expirations end a nonoldest lifetime, under two backend and two baseline-policy choices. |
| inputs / outputs | Backend and FIFO policy in; builds labels for A/B/A plus an unrelated table-3 row, proposes watermark 11, checks unchanged rows/window/progress/image and fifo_scope at table 1 label 2; restored state then proves surviving A label metadata does not replace its original physical birth ordering. |
| invariants | Declaration scope 7 joins tables 0/1. Whole-proposal validation includes earlier unrelated expirations. Explicit removal uses physical birth order, not surviving label IDs. |
| ownership | Sessions own labels/counts; checkpoint copies and result rows are test observations; restore owns new state. |
| failure | Wrong violation context, changed prefix/image, or incorrect restored withdrawal result fails checks. |
| cost | Four paired cases (reference/indexed × unrestricted/physical_per_relation), with four inserts, rejected watermark, restore, and explicit withdrawals. |
| Design | [docs/update_patterns.md § Validate before publication](../../../../update_patterns.md), [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0013

[Lines 113–127](../../../../../tests/unit/update_pattern_runtime_test.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L127:sha256:dee436463b8879cebef7f56e685c163df1d762d24a741fc055f5688acc7c7189
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check duplicate-label reference counting and restore: one expiration is metadata-only; ending the remaining row lifetime violates insertion-only. |
| inputs / outputs | Backend selector in; two labels reference the same row, watermark expires the first, then restored session withdraws the last label. |
| invariants | Only one-to-zero physical lifetime termination violates the insertion-only rule; metadata-only duplicate removal does not. |
| ownership | Window session owns labels/counts; image owns bytes; restore reconstructs state. |
| failure | Wrong physical sequence, diagnostic kind, or accepted final removal fails a check. |
| cost | One duplicate pair, metadata expiration, checkpoint/restore, and final withdrawal per backend. |
| Design | [docs/update_patterns.md § Enforce a declaration through QuerySession](../../../../update_patterns.md), [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0014

[Lines 128–132](../../../../../tests/unit/update_pattern_runtime_test.cpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L132:sha256:8b6350db1b0db1aed007436283a04970758c32094c8014d187bd95c66a1664df
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain that the differential oracle owns a separate lifetime list and does not reuse native birth IDs or sorted-prefix code. |
| inputs / outputs | Comment only. |
| invariants | Oracle is an independent finite test model, not exhaustive input coverage. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § Validate before publication](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0015

[Lines 133–133](../../../../../tests/unit/update_pattern_runtime_test.cpp#L133); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L133:sha256:63f70d86d30d60525b047d3e81fc81192d8aea9c9fe74ef10f43919672832c55
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the test model active-label record. |
| inputs / outputs | Label ID, table, one-column int64 value, timestamp. |
| invariants | Fields match the small generated fixture domain. |
| ownership | Copied scalar record owned by Model vectors; no native row pointer. |
| failure | Ordinary construction/vector allocation may fail. |
| cost | Fixed scalar record. |
| Design | [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0016

[Lines 134–134](../../../../../tests/unit/update_pattern_runtime_test.cpp#L134); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L134-L134:sha256:63bb1c9a875eb78d551e0db1d33688bde6c3cc99eb0cc2fd612a5b60f301ac8a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the model distinct-lifetime record. |
| inputs / outputs | Table and int64 row value; birth order is represented by vector position. |
| invariants | One entry per active table/value physical lifetime. |
| ownership | Model vector owns records independently of native count state. |
| failure | Ordinary vector growth may fail. |
| cost | Fixed scalar record. |
| Design | [docs/update_patterns.md § Validate before publication](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0017

[Lines 135–135](../../../../../tests/unit/update_pattern_runtime_test.cpp#L135); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L135:sha256:0d222ec1539560aa3f14ed0e54646adfe64acd9b25ba3ed40e0e330dd5b542a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store active labels, distinct lifetime births, and watermark in the test oracle. |
| inputs / outputs | Model fields: label vector, birth-order Life vector, watermark initially zero. |
| invariants | Birth vector order is the oracle ordering and contains no native IDs. |
| ownership | Model owns storage; a copied Model is a proposal snapshot. |
| failure | Vector copy/growth can throw. |
| cost | Space linear in labels plus distinct live lifetimes. |
| Design | [docs/update_patterns.md § Validate before publication](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0018

[Lines 136–150](../../../../../tests/unit/update_pattern_runtime_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L150:sha256:1452cf010f18a7c87b14954bd3e9d9f6d8cbc75e01eca26478693cf286dd9741
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply an independent linear final-reference removal rule to the oracle. |
| inputs / outputs | Label ID and per_table selector in; bool allowed out. Counts row references; table 2 cannot end; scope 7 joins tables 0/1; optional per-table scopes govern other tables; final removal must match first live birth in scope. |
| invariants | Nonfinal removal is metadata-only. False leaves this proposed model’s row/birth state unchanged. No native IDs or sorted-prefix algorithm are used. |
| ownership | Mutates only supplied Model; caller passes a proposal copy before deciding to commit. |
| failure | Missing oracle label fails through check; allocation errors propagate. |
| cost | Linear scans/counts over labels and births, deliberately test-only. |
| Design | [docs/update_patterns.md § Validate before publication; model is independent of native preflight](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0019

[Lines 151–165](../../../../../tests/unit/update_pattern_runtime_test.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L151-L165:sha256:ad3625aa20f67551b69d18c52b4a6b5f3c74c6a826e6e3ab32d1f4df70f649ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply insert, withdraw, or whole-watermark operations to the independent model. |
| inputs / outputs | WindowCommand and per_table selector in; bool accepted out. Inserts add a birth only on zero-to-one, withdrawal delegates to remove, and watermark expiration sorts by deadline then label. |
| invariants | Watermark advances only after every removal succeeds. Caller discards failed proposal copy. Generated timestamps avoid overflow. |
| ownership | Mutates only caller-owned Model. |
| failure | Variant, sort, allocation, or oracle check errors propagate; false means modeled semantic rejection. |
| cost | Linear row lookup and repeated removals plus O(E log E) expiration ordering; not a product cost claim. |
| Design | [docs/update_patterns.md § Validate before publication](../../../../update_patterns.md), [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0020

[Lines 166–166](../../../../../tests/unit/update_pattern_runtime_test.cpp#L166); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L166-L166:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the test-only Model type. |
| inputs / outputs | Scope delimiter only. |
| invariants | No native type or owner is closed. |
| ownership | Member storage follows local Model lifetime. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § test scope](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0021

[Lines 167–194](../../../../../tests/unit/update_pattern_runtime_test.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L167-L194:sha256:6321517b1138dc669a41c3380fb3de310376ea95e731c9879d7ae2a1cae98798
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare deterministic model proposals to real session behavior for backend and per-table combinations. |
| inputs / outputs | Seed 9017; 140 insert/withdraw/watermark proposals per call. Allowed proposal commits to session/model; rejected proposal must leave live window unchanged, then session restores the accepted checkpoint. Each step compares table-0 rows and progress/monitor sequence. |
| invariants | Called for reference/indexed × unrestricted/physical_per_relation: 560 seeded proposals. Reject may be declaration or baseline window FIFO. This differential fixture is not exhaustive. |
| ownership | Helper owns Model, PRNG, session, proposal copy, and checkpoint observations; restore creates a new owner. |
| failure | Wrong error class, prefix/result/counter mismatch, or no accepted/rejected outcomes fails check; other setup/restore failures propagate. |
| cost | 560 proposals with model and checkpoint copies; test workload, not benchmark. |
| Design | [docs/update_patterns.md § Validate before publication](../../../../update_patterns.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0022

[Lines 195–197](../../../../../tests/unit/update_pattern_runtime_test.cpp#L195); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L195-L197:sha256:0a335cbde93ea0d6986595b6a6c308789bcd7efc7586421c156939944b269e13
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain that distinct positive scope IDs remain independent. |
| inputs / outputs | Comment only; frames a two-scope control. |
| invariants | Checks no inferred union; not a joint-FIFO theorem. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § Declare a requested source contract](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0023

[Lines 198–207](../../../../../tests/unit/update_pattern_runtime_test.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L198-L207:sha256:7c27c7c191f9597cddbe7617f81fcd5e20aa881534c8dbd1b4628387bfcf02db
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify scope IDs 1 and 2 are not silently united. |
| inputs / outputs | Unrestricted window session inserts one row in table 0/scope 1 and table 1/scope 2, withdraws table 1, and checks one count remains without violation. |
| invariants | Only equal positive scope IDs share order. |
| ownership | Session owns declaration and window state. |
| failure | Admission/operation or assertion mismatch fails. |
| cost | Two inserts and one withdrawal. |
| Design | [docs/update_patterns.md § Declare a requested source contract](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0025

[Lines 209–232](../../../../../tests/unit/update_pattern_runtime_test.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L209-L232:sha256:2152606d65d0cc9cb19148fb3e6a31715d8e38fb3e445bc768dabc2149b8431c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check conditional current selection against the actual Session monitor, with bare-runtime and rule-mismatch negative controls. |
| inputs / outputs | Builds real fixture candidates and table-2 rule; configures workload statistics; select_current with PhysicalBasis/height_only must select expected tree shape. Bare PhysicalRuntime returns unsupported_model; changed table-0 declaration returns binding_mismatch. |
| invariants | One fixture path only; does not prove general selection soundness or ranking quality. |
| ownership | Helper owns candidate/program/session/request/source and temporary selection. |
| failure | Wrong stop/result/shape fails a check. |
| cost | One current selection and two negative attempts over fixture candidates. |
| Design | [docs/selection.md § Conditional update-pattern admissibility](../../../../selection.md), [docs/update_patterns.md § Read the committed prefix and bind current selection](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0026

[Lines 233–235](../../../../../tests/unit/update_pattern_runtime_test.cpp#L233); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L233-L235:sha256:b2acfa5ec60eaabba64090bceb91c8cf3fe87e2e00607e9b3b2adfd352d2611a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the retryable healthy-preflight allocation-denial control. |
| inputs / outputs | Comment only. |
| invariants | The failpoint covers the test C++ new seam only, not native MemoryAccount allocation or every allocator. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § Actual costs and persistence](../../../../update_patterns.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0027

[Lines 236–263](../../../../../tests/unit/update_pattern_runtime_test.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L236-L263:sha256:55768eb101a09354c98a99ab4d70cb9d9acf70d476bc8f8ce8246e0e1a7b0a7b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deny each measured C++ new allocation during healthy metadata-only watermark preflight, require cleanup, and retry the queued command. |
| inputs / outputs | Two labels for one row plus watermark; healthy run measures positions. Each fresh-session cut must throw bad_alloc, keep input/monitor state and window unchanged, and restore account resident bytes; retry completes metadata step without another physical epoch. |
| invariants | Scoped s04_alloc intercepts C++ new only. The code counts positions dynamically and checks positive finite count. Resource failure is retryable, not semantic. |
| ownership | Each cut owns fresh session, account handle, saved prefix, and scope; command remains queued for retry. |
| failure | Missed denial, sticky status, leaked bytes, changed prefix, or failed retry fails check. |
| cost | Current fixture has 3 successful-path C++ new cut positions; every cut reconstructs and retries a session. |
| Design | [docs/update_patterns.md § Actual costs and persistence; C++ new only](../../../../update_patterns.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0028

[Lines 264–266](../../../../../tests/unit/update_pattern_runtime_test.cpp#L264); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L264-L266:sha256:fcc5e6efb348d8943994db6a0c8c4b7aa0baa8b4b41c6c68b768f9b68a61080c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain that construction of the semantic Error can fail and only a completed error may latch rejection. |
| inputs / outputs | Comment only. |
| invariants | Allocation denial scope is the test C++ new seam only. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § Enforce a declaration through QuerySession](../../../../update_patterns.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0029

[Lines 267–293](../../../../../tests/unit/update_pattern_runtime_test.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L267-L293:sha256:b60f253ffe27f1c1c074bddd25a6b83449a472e06fc42bdbbe712dc942e81fbc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deny each measured C++ new cut while constructing whole-watermark semantic rejection; retry must then latch the violation without publishing a prefix. |
| inputs / outputs | A/B/A in shared scope 9 plus watermark 11; healthy rejection counts positions. Each fresh cut requires bad_alloc, no input_failed/violation, unchanged window/account resident bytes; subsequent retry requires update_pattern_violation, sticky input_failed, and unchanged state. |
| invariants | Only C++ new is intercepted. Current path has 5 measured semantic-error construction cuts; source counts dynamically and asserts finite positive count. |
| ownership | Fresh session/account/prefix observations per cut; allocator scope covers the attempted begin and cleanup. |
| failure | Wrong exception, early latch, prefix/account change, or retry mismatch fails. |
| cost | Five current C++ new cut positions plus one retry per cut; no universal allocation guarantee. |
| Design | [docs/update_patterns.md § Enforce a declaration through QuerySession; C++ new only](../../../../update_patterns.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0030

[Lines 294–296](../../../../../tests/unit/update_pattern_runtime_test.cpp#L294); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L294-L296:sha256:5b869661d2c86805beb3c3942bc3a4756119b92e4cd802c63ebee5ffd83533f6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain that the work comparison is an abstract controller counter, not elapsed CPU time. |
| inputs / outputs | Comment only. |
| invariants | No CPU/delay bound is inferred. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § Actual costs and persistence](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0031

[Lines 297–324](../../../../../tests/unit/update_pattern_runtime_test.cpp#L297); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L297-L324:sha256:2571f0f8f97847cab3c5c7464a2f5f4f26410cb1fc518a5498f18e93eb8f894d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure abstract watermark work, test exact versus one-under grant, and compare grouped versus interleaved unrestricted expirations. |
| inputs / outputs | First builds eight duplicate labels, measures watermark work, then accepts at exact grant and rejects at one less without changing prefix. An unordered_work control builds 15 distinct rows in tables 1–3 in grouped and interleaved insertion orders; all expire at mark 10 and both abstract work totals must match. |
| invariants | The counter is abstract command work, not CPU. The second control has table-0 insertion-only declaration but no live positive FIFO scope, and proves only that these two orders receive equal counted work. |
| ownership | Each scenario owns fresh session/window state; observations are the committed window state and last_command_work scalar. |
| failure | Incorrect grant boundary, retained expired rows, semantic latch, prefix mutation, or unequal totals fails check. |
| cost | Three primary grant histories plus two 15-row ordering controls; no timing claim. |
| Design | [docs/update_patterns.md § Actual costs and persistence](../../../../update_patterns.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0032

[Lines 325–327](../../../../../tests/unit/update_pattern_runtime_test.cpp#L325); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L325-L327:sha256:f401181aee7b47b53f80e7f0e02e334b778e309002f99bd6661f231bff0f1111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain real checkpoint/log reconstruction with a pending input lacking a durable decision and guarded replay. |
| inputs / outputs | Comment only. |
| invariants | Prior v2 checkpoint is the trusted-history premise; test focuses on pending boundary and resumed enforcement. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/session-journal.md § Recovery and replay](../../../../session-journal.md), [docs/update_patterns.md § Restore the declared contract](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0033

[Lines 328–351](../../../../../tests/unit/update_pattern_runtime_test.cpp#L328); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L328-L351:sha256:5835932baf2476764cc75387bc49f7986298c33b6b2b2bca405cb6294337cf77
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise monitor continuity through checkpoint file, journal input without durable decision, replay, then forbidden final withdrawal. |
| inputs / outputs | Backend selector in; commits checkpoint prefix, enables journal, records duplicate label and begins watermark input to prepared, destroys owner, restores journal, checks restored checkpoint/completed/pending sequence, retries and finishes pending input, then rejects last-label withdrawal with unchanged window/log bytes. |
| invariants | This is one actual file/log pending-input scenario per backend. Restored checkpoint is trusted history; not all crash cuts or entire prefix history are independently verified. |
| ownership | Temporary directory owns paths; QuerySession owns recovered journal state; prefix/log bytes are copied observations. |
| failure | Wrong replay boundary, failure category, log/window change, or monitor sequence fails checks; IO/recovery errors propagate. |
| cost | Two backend cases, each with file reconstruction, one replayed pending command, and one rejected withdrawal. |
| Design | [docs/session-journal.md § Recovery and replay](../../../../session-journal.md), [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [docs/update_patterns.md § Restore the declared contract](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0034

[Lines 352–355](../../../../../tests/unit/update_pattern_runtime_test.cpp#L352); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L352-L355:sha256:fcf7769062652c80b7ece2234367c732a39cdfea93c0f80ad103ac2a07c98323
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain owner-bound measured selection, durable replacement, actual target hash, enforcement, and restore. |
| inputs / outputs | Comment only. |
| invariants | One scenario; not every migration path or a planner theorem. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/selection.md § Conditional update-pattern admissibility](../../../../selection.md), [docs/reoptimization.md § Optional C05 integration](../../../../reoptimization.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0035

[Lines 356–383](../../../../../tests/unit/update_pattern_runtime_test.cpp#L356); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L356-L383:sha256:ea06236c2ebc43068862fc27eb028d1e52f9a5b60a7e3efae0264c2901f71e8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select for a real Session owner, publish a different plan through reoptimization/generation, then enforce and restore the declaration against target identity. |
| inputs / outputs | Creates fixture candidates/session/generation; measured selection must succeed, barrier and advance must verify, CompilerPlanArtifact publication must complete. Checks declaration matches target, target profile hash differs from original, then checkpoints/restores and rejects final withdrawal. |
| invariants | Covers one finite fixture/forecast path only; no optimality, theorem, full migration, or complete durability claim. |
| ownership | Session/generation/artifact manage their normal owners; restored session owns separate receiving state. |
| failure | Any failed phase, stale hash, missing restored profile, or accepted erase fails a check; operation errors propagate. |
| cost | One measured selection, one publication and one checkpoint/restore sequence. |
| Design | [docs/selection.md § Conditional update-pattern admissibility](../../../../selection.md), [docs/reoptimization.md § Optional C05 integration](../../../../reoptimization.md), [docs/update_patterns.md § Read the committed prefix and bind current selection](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0036

[Lines 384–386](../../../../../tests/unit/update_pattern_runtime_test.cpp#L384); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L384-L386:sha256:2565e8ba13c0567527ceeb6f9f8eb20e0f8741d5dd4bda32332794100840c1f2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State that checkpoint metadata represents trusted history while admission still checks source, version, shape, context, and grants. |
| inputs / outputs | Comment only. |
| invariants | Restore does not independently replay the historical accepted prefix. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § Restore the declared contract](../../../../update_patterns.md), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0037

[Lines 387–422](../../../../../tests/unit/update_pattern_runtime_test.cpp#L387); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L387-L422:sha256:d5104e816daa69208c58d0a4f06421e9f69bb5aa8e4db6f763f8d4e1594eb5d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check v2 inspection and receiving grants, reject malformed public metadata, and verify restored declaration storage is independent. |
| inputs / outputs | Typed insertion-only session and image; zero inspection cells and zero checkpoint work must fail. Mutated version/origin/source hash/violation records must fail restore; zero receiving copy cells must fail; normal restore must have different rules storage. |
| invariants | Trusted checkpoint history is assumed. Tests schema/admission/grant rules and receiving ownership, not historical replay or corruption fuzzing. |
| ownership | Sender owns original declaration; state/records are temporary; restore must copy declaration into receiver account. |
| failure | Unexpected acceptance, ignored grant, shared rules buffer, or wrong fault fails checks. |
| cost | Several bounded export/import/restore controls and one image inspection. |
| Design | [docs/update_patterns.md § Restore the declared contract](../../../../update_patterns.md), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0038

[Lines 423–426](../../../../../tests/unit/update_pattern_runtime_test.cpp#L423); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L423-L426:sha256:59364004896f43b1ded9975a3e49b03e865b7869a2f6130bf5d609b440ccda5d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain separation between requested run-context rules and live session enforcement/provenance in report JSON; default sessions omit pattern fields. |
| inputs / outputs | Comment only. |
| invariants | maintenance_bound remains not_asserted; this is schema evidence, not a complexity theorem. |
| ownership | No runtime owner. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § Read the committed prefix and bind current selection](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0039

[Lines 427–450](../../../../../tests/unit/update_pattern_runtime_test.cpp#L427); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L427-L450:sha256:95e067b71f5fc6a5b756044173748449ebdfc2539700bbe445f07cac93782e04
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate actual EXPLAIN JSON for enforced, rejected, restored-rejected, and unconfigured sessions, optionally writing three reports. |
| inputs / outputs | Optional output directory in; parser checks history/state, not_asserted maintenance bound, and requested rules in run_context; exercises absent erase rejection, stop/checkpoint/restore, then verifies unconfigured report omits pattern objects. |
| invariants | Requested rules and actual owner status remain distinct JSON objects. Restore reports trusted checkpoint history. File output is optional. This native control checks selected field values; full Draft 2020-12 schema validation is a separate root receipt over the three written reports. |
| ownership | Sessions own state; JSON strings/DOMs local; optional files live under caller path. |
| failure | Wrong expected field value, accidental default fields, or failed output write fails check; parse/filesystem failures propagate. |
| cost | Three configured captures/writes plus one unconfigured capture. |
| Design | [docs/update_patterns.md § Read the committed prefix and bind current selection](../../../../update_patterns.md), [docs/query_memory.md § Reports and evidence](../../../../query_memory.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0041

[Lines 452–467](../../../../../tests/unit/update_pattern_runtime_test.cpp#L452); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L452-L467:sha256:159dbab39cd0f2449fe9e445f214c730c7a0cb8f9f51713d7135652478c2885c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check startup admission for nonwindow FIFO, foreign source, insufficient capture work, and legacy v1 for undeclared sessions. |
| inputs / outputs | Nonwindow typed creation must report unsupported_update_pattern; altered source hash must report invalid_update_pattern; zero capture work must report work_limit; plain session image stays v1. |
| invariants | FIFO is not silently treated as nonwindow history; declaration is bound to exact source; opt-in absence preserves v1 format. |
| ownership | Local sessions/options/records; declaration uses program account. |
| failure | Exact expected code/fault required; unexpected success or version fails check. |
| cost | Four small admission/format controls, no history replay. |
| Design | [docs/update_patterns.md § Declare a requested source contract](../../../../update_patterns.md), [docs/update_patterns.md § Enforce a declaration through QuerySession](../../../../update_patterns.md), [docs/checkpoints.md § CROWNSI1 session envelope format 1](../../../../checkpoints.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0042

[Lines 468–468](../../../../../tests/unit/update_pattern_runtime_test.cpp#L468); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L468-L468:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous namespace containing helpers and the oracle. |
| inputs / outputs | Scope delimiter only. |
| invariants | No behavior or assertion. |
| ownership | Translation-unit declarations end scope; object lifetimes remain ordinary C++. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md § test scope](../../../../update_patterns.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |

## B0043

[Lines 469–483](../../../../../tests/unit/update_pattern_runtime_test.cpp#L469); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L469-L483:sha256:61a00560b5d56b1b1744e1d0efa6d02a6501dbecf19e408bce5f6ae1e50c42da
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the test contracts and expose optional report output path through main. |
| inputs / outputs | Runs singleton admission/scope/selection/fault/work/checkpoint/replacement/report controls; loops both backends over journal, typed/stream insertion, two watermark policies, duplicate test, and two oracle modes. Catches std::exception, prints, returns 1. |
| invariants | The model calls comprise 2 backends × 2 FIFO modes × 140 = 560 seeded proposals. Calls show scheduled coverage, not evidence of test execution. No whole-suite claim. |
| ownership | main owns argv-derived path and stack scopes; helpers own fixtures/sessions. |
| failure | std::exception reaches one outer catch and nonzero exit; non-std exceptions are not caught. |
| cost | Sum of helper work, dominated by dynamic C++ new cut sweeps and model/checkpoint copies; no benchmark. |
| Design | [docs/update_patterns.md § paper/planner boundary](../../../../update_patterns.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [docs/session-journal.md § Recovery and replay](../../../../session-journal.md), [docs/update_patterns.md § paper/planner boundary; no theorem claim from this test](../../../../update_patterns.md) |
