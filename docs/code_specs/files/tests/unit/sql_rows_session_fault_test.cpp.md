# `tests/unit/sql_rows_session_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_rows_session_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ebc8250961aaf901b4c33dec4b1f932243fa317d8ba5a186980b436029e0c991`. 160 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L10) | Type/record definition: enum class Mode |  · [reviewed contract](#b0002) |
| [B0003 · 11–12](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L11) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 13–16](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L13) | Callable definition: void log_row(sr::Session& session) | calls log · [reviewed contract](#b0004) |
| [B0005 · 17–19](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L17) | Explanatory comments or spacing. | source comment (unverified): // Each action starts from a genuine closed root. Namespace copies below are · [reviewed contract](#b0005) |
| [B0006 · 20–26](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L20) | Callable definition: void prepare(Fixture& fixture,Mode mode) | calls create, log_row, assert, decide; guard assert(!owner.decide().rejected);if(mode==Mode::deliver)return;; source comment (unverified): // Each action starts from a genuine closed root. Namespace copies below are · [reviewed contract](#b0006) |
| [B0007 · 27–27](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L27) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 28–33](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L28) | Callable definition: Namespace capture(const Fixture& fixture) | calls std::filesystem::directory_iterator, emplace_back, path, string; returns result; growth emplace_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 34–38](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L34) | Callable definition: void restore(Fixture& fixture,const Namespace& image) | calls std::filesystem::directory_iterator, std::filesystem::remove_all, path, put; 2 loop sites · [reviewed contract](#b0009) |
| [B0010 · 39–47](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L39) | Callable definition: void perform(Fixture& fixture,Mode mode,std::optional&lt;sr::Session&gt;& owner) | calls log_row, assert, decide, deliver; guard case Mode::commit:assert(!owner-&gt;decide().rejected);return;; growth emplace · [reviewed contract](#b0010) |
| [B0011 · 48–64](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L48) | Callable definition: void receive(Fixture& fixture) | calls recover, state, assert, decide; guard assert(state.delivered&lt;=state.committed && state.committed&lt;=state.disposed && · [reviewed contract](#b0011) |
| [B0012 · 65–68](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L65) | Explanatory comments or spacing. | source comment (unverified): // The existing two syscall seams exercise the same bounded POSIX implementation · [reviewed contract](#b0012) |
| [B0013 · 69–129](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L69) | Callable definition: void syscall_failures_and_cuts(bool indexed) | calls fixture, prepare, generation_file, put; guard assert(fixture.account.statistics().current.allocations==memory);; growth emplace; 3 loop sites; source comment (unverified): // The existing two syscall seams exercise the same bounded POSIX implementation · [reviewed contract](#b0013) |
| [B0014 · 130–132](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L130) | Explanatory comments or spacing. | source comment (unverified): // The first append stat occurs after native output/frame/index funding. Deny · [reviewed contract](#b0014) |
| [B0015 · 133–153](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L133) | Callable definition: void prepaid_publication(bool indexed) | calls fixture, prepare, capture, emplace; guard assert(hook.deny&gt;0);; growth emplace; 2 loop sites; source comment (unverified): // The first append stat occurs after native output/frame/index funding. Deny · [reviewed contract](#b0015) |
| [B0016 · 154–155](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L154) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 156–160](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L156) | Callable definition: int main() | calls syscall_failures_and_cuts, prepaid_publication; 1 loop sites · [reviewed contract](#b0017) |

## B0001

[Lines 1–9](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:7e88d6f6d34ce4dd64994ff746fe0b9ccdabaeb67ae0b40a13e1fe4522d50ea9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include the genuine Session fixture and existing syscall/allocation test probes. |
| inputs / outputs | Open test namespace and expose fixture/probe helpers. |
| invariants | No fault injection, fork or native operation executes in this include region. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0002

[Lines 10–10](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L10:sha256:f0c68716c9e735977eeccee87981180fb9a703e2541703d0d575bf1949e934fa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the five fault-test operation stages. |
| inputs / outputs | Mode has log,commit,deliver,checkpoint,recover values. |
| invariants | The enum performs no fault injection or operation. |
| ownership | Fixed enum only. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0003

[Lines 11–12](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L12:sha256:b0c454f91b6fcaecfe57b70b2c8a832c8d3e49489c11a63593b1a48d7c195420
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the one-cell NULL physical row used by fault-test edits. |
| inputs / outputs | cells is a const one-Cell array containing NULL. |
| invariants | The array definition does not construct or submit a SourceReplacement. |
| ownership | Static test array owns its Cell descriptor; later edits borrow that stable array. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0004

[Lines 13–16](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L16:sha256:099979fe0de82255b7dc5eee72241cea55290eb28bff25bb0ef92fb4d106dcc6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Log one genuine nullable physical-row command with exact 0→2 weight and source/reader progress. |
| inputs / outputs | The declared tiny nullable row, genuine fixture root and selected public action in; assertions, actual reopened survivor state and finite probe counters out. |
| invariants | Fault coverage is bounded by observed actions/syscalls, not every possible workload. EIO/real process outcomes are validated by reopening rather than inferred from fsync. Surviving W/I/C/D and NULL bag weight 2/source offset 10 must agree. |
| ownership | Namespace copies are disposable test workspace, never a replacement production checkpoint. Parent/child FD and Session lifetimes are explicitly closed before receiving; allocation-denial guards use the existing test-only seams. |
| failure | Expected typed file/generation failures require reopen on retained owners; unexpected outcomes/assertions fail the test. forked cuts must exit 77; no production catch/repair framework is introduced. |
| cost | Test-only trace/copy/fork/oracle work; descriptor/allocation baselines are checked. The no-new claim is only the actually tested funded append-publication/acknowledgment interval, not a global allocation or latency theorem. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0005

[Lines 17–19](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L19:sha256:61d57d5b2ad98cf5bac07337fd9e7950951aea15ef6812668b6e60865e280d5b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent reviewed ownership/barrier rule in this comment block. |
| inputs / outputs | No executable input/output; the nearby callable supplies the actual protocol. |
| invariants | The prose is guidance tied to the adjacent code and pinned bytes, not an independent correctness or delay proof. |
| ownership | No runtime object, borrow or FD is created by comments. |
| failure | No failure/repair behavior is installed by prose. |
| cost | No executable cost. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0006

[Lines 20–26](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L26:sha256:4ccd1a43ee212133d66dc91347232f8aa8aca8a1a2c59951ce7eded93de00ea7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Establish the genuine closed-root/logged/committed/delivered prefix needed by one fault action. |
| inputs / outputs | The declared tiny nullable row, genuine fixture root and selected public action in; assertions, actual reopened survivor state and finite probe counters out. |
| invariants | Fault coverage is bounded by observed actions/syscalls, not every possible workload. EIO/real process outcomes are validated by reopening rather than inferred from fsync. Surviving W/I/C/D and NULL bag weight 2/source offset 10 must agree. |
| ownership | Namespace copies are disposable test workspace, never a replacement production checkpoint. Parent/child FD and Session lifetimes are explicitly closed before receiving; allocation-denial guards use the existing test-only seams. |
| failure | Expected typed file/generation failures require reopen on retained owners; unexpected outcomes/assertions fail the test. forked cuts must exit 77; no production catch/repair framework is introduced. |
| cost | Test-only trace/copy/fork/oracle work; descriptor/allocation baselines are checked. The no-new claim is only the actually tested funded append-publication/acknowledgment interval, not a global allocation or latency theorem. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0007

[Lines 27–27](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:f9603ba6b6332ee018e4b51eebee3e876565e49f28339199329a70a920822e17
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name an ordinary captured test namespace image. |
| inputs / outputs | Namespace aliases vector&lt;pair&lt;string,string&gt;&gt; for file-name/byte snapshots. |
| invariants | The alias does not read files or replace durable state; only later helper calls use it. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0008

[Lines 28–33](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L33:sha256:61e9a63850312d336c5a8848a5cfabf725e7291d60cb170e02a473fe95af0f68
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy only this disposable fixture namespace's actual file bytes for restoring the same pre-action test prefix. |
| inputs / outputs | The declared tiny nullable row, genuine fixture root and selected public action in; assertions, actual reopened survivor state and finite probe counters out. |
| invariants | Fault coverage is bounded by observed actions/syscalls, not every possible workload. EIO/real process outcomes are validated by reopening rather than inferred from fsync. Surviving W/I/C/D and NULL bag weight 2/source offset 10 must agree. |
| ownership | Namespace copies are disposable test workspace, never a replacement production checkpoint. Parent/child FD and Session lifetimes are explicitly closed before receiving; allocation-denial guards use the existing test-only seams. |
| failure | Expected typed file/generation failures require reopen on retained owners; unexpected outcomes/assertions fail the test. forked cuts must exit 77; no production catch/repair framework is introduced. |
| cost | Test-only trace/copy/fork/oracle work; descriptor/allocation baselines are checked. The no-new claim is only the actually tested funded append-publication/acknowledgment interval, not a global allocation or latency theorem. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0009

[Lines 34–38](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L38:sha256:d3ae6099da98016ed3b02b875684704c59b7584dd3229812caff25873d38ebd9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a previously captured disposable fixture namespace while no live Session owns its files. |
| inputs / outputs | The declared tiny nullable row, genuine fixture root and selected public action in; assertions, actual reopened survivor state and finite probe counters out. |
| invariants | Fault coverage is bounded by observed actions/syscalls, not every possible workload. EIO/real process outcomes are validated by reopening rather than inferred from fsync. Surviving W/I/C/D and NULL bag weight 2/source offset 10 must agree. |
| ownership | Namespace copies are disposable test workspace, never a replacement production checkpoint. Parent/child FD and Session lifetimes are explicitly closed before receiving; allocation-denial guards use the existing test-only seams. |
| failure | Expected typed file/generation failures require reopen on retained owners; unexpected outcomes/assertions fail the test. forked cuts must exit 77; no production catch/repair framework is introduced. |
| cost | Test-only trace/copy/fork/oracle work; descriptor/allocation baselines are checked. The no-new claim is only the actually tested funded append-publication/acknowledgment interval, not a global allocation or latency theorem. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0010

[Lines 39–47](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L47:sha256:460928629fe312414d63633f5ccd3445a4e5ec67399612a65c108897df42590b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run exactly one selected public log/decide/deliver/checkpoint/recover operation under installed probes. |
| inputs / outputs | The declared tiny nullable row, genuine fixture root and selected public action in; assertions, actual reopened survivor state and finite probe counters out. |
| invariants | Fault coverage is bounded by observed actions/syscalls, not every possible workload. EIO/real process outcomes are validated by reopening rather than inferred from fsync. Surviving W/I/C/D and NULL bag weight 2/source offset 10 must agree. |
| ownership | Namespace copies are disposable test workspace, never a replacement production checkpoint. Parent/child FD and Session lifetimes are explicitly closed before receiving; allocation-denial guards use the existing test-only seams. |
| failure | Expected typed file/generation failures require reopen on retained owners; unexpected outcomes/assertions fail the test. forked cuts must exit 77; no production catch/repair framework is introduced. |
| cost | Test-only trace/copy/fork/oracle work; descriptor/allocation baselines are checked. The no-new claim is only the actually tested funded append-publication/acknowledgment interval, not a global allocation or latency theorem. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0011

[Lines 48–64](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L64:sha256:4998d062f5335e008736a32767cbcc9ba818171728fce54c7ee74e6c867150e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reopen through the genuine public recovery factory, resolve any pending input/output, and verify exact allowed native/progress survivors. |
| inputs / outputs | The declared tiny nullable row, genuine fixture root and selected public action in; assertions, actual reopened survivor state and finite probe counters out. |
| invariants | Fault coverage is bounded by observed actions/syscalls, not every possible workload. EIO/real process outcomes are validated by reopening rather than inferred from fsync. Surviving W/I/C/D and NULL bag weight 2/source offset 10 must agree. |
| ownership | Namespace copies are disposable test workspace, never a replacement production checkpoint. Parent/child FD and Session lifetimes are explicitly closed before receiving; allocation-denial guards use the existing test-only seams. |
| failure | Expected typed file/generation failures require reopen on retained owners; unexpected outcomes/assertions fail the test. forked cuts must exit 77; no production catch/repair framework is introduced. |
| cost | Test-only trace/copy/fork/oracle work; descriptor/allocation baselines are checked. The no-new claim is only the actually tested funded append-publication/acknowledgment interval, not a global allocation or latency theorem. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0012

[Lines 65–68](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L68:sha256:180db91932b1dfc4a5e7e3750686a1e7cab39275c1ffe5146a47503e7f02c246
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent reviewed ownership/barrier rule in this comment block. |
| inputs / outputs | No executable input/output; the nearby callable supplies the actual protocol. |
| invariants | The prose is guidance tied to the adjacent code and pinned bytes, not an independent correctness or delay proof. |
| ownership | No runtime object, borrow or FD is created by comments. |
| failure | No failure/repair behavior is installed by prose. |
| cost | No executable cost. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0013

[Lines 69–129](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L129:sha256:35270c57ef96a0d381f19d77ed881acac155dec98cb39af685cdebaef058a4cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject supported observed syscall errors and real process cuts, then inspect genuine recovered survivors. |
| inputs / outputs | Backend flag -&gt; void after tracing log/commit/deliver/checkpoint/recover actions, injecting each supported event and reopening the surviving namespace. |
| invariants | Skip only after-hook events whose actual syscall result was already negative, since that seam cannot override an existing optional failure. Every supported injected error must throw; durability-event fork cuts must exit 77. W/I/C/D, NULL bag weight and source progress are checked by receive(). |
| ownership | Disposable namespace copies are test-only; parent/child Session and FD owners are released before genuine recovery. Memory/FD baselines are checked per case. |
| failure | Expected FileFailure/GenerationFailure require reopen on retained owners; unexpected success/error/assertion fails. Complete actual survivor bytes are received rather than durability inferred from a prior call. |
| cost | Finite trace/copy/fork/recovery loops under observed events only; this function makes no global no-allocation, timing or universal-fault claim. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0014

[Lines 130–132](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L130); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L130-L132:sha256:57b400a69deed75d5a5d0d5ec4f30e381f5b3a493054b173cf8df1f5671b7bcf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent reviewed ownership/barrier rule in this comment block. |
| inputs / outputs | No executable input/output; the nearby callable supplies the actual protocol. |
| invariants | The prose is guidance tied to the adjacent code and pinned bytes, not an independent correctness or delay proof. |
| ownership | No runtime object, borrow or FD is created by comments. |
| failure | No failure/repair behavior is installed by prose. |
| cost | No executable cost. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0015

[Lines 133–153](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L153:sha256:6d0e94edc0d12ba8a2e6083cbe10a247348d9cb2214748727a498dd057165b92
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deny covered C++ allocations from the observed first append stat through the committed publication or acknowledged delivery boundary. |
| inputs / outputs | The declared tiny nullable row, genuine fixture root and selected public action in; assertions, actual reopened survivor state and finite probe counters out. |
| invariants | Fault coverage is bounded by observed actions/syscalls, not every possible workload. EIO/real process outcomes are validated by reopening rather than inferred from fsync. Surviving W/I/C/D and NULL bag weight 2/source offset 10 must agree. |
| ownership | Namespace copies are disposable test workspace, never a replacement production checkpoint. Parent/child FD and Session lifetimes are explicitly closed before receiving; allocation-denial guards use the existing test-only seams. |
| failure | Expected typed file/generation failures require reopen on retained owners; unexpected outcomes/assertions fail the test. forked cuts must exit 77; no production catch/repair framework is introduced. |
| cost | Test-only trace/copy/fork/oracle work; descriptor/allocation baselines are checked. The no-new claim is only the actually tested funded append-publication/acknowledgment interval, not a global allocation or latency theorem. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |

## B0016

[Lines 154–155](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L155:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the surrounding namespace/type at this exact lexical boundary. |
| inputs / outputs | No runtime arguments, results or state transition. |
| invariants | A scope delimiter carries no admission, replay, invariant or rollback authority. |
| ownership | Namespace/type closure does not destroy objects merely by being declared here. |
| failure | No runtime failure or handler exists in this delimiter. |
| cost | No executable or per-query cost. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0017

[Lines 156–160](../../../../../tests/unit/sql_rows_session_fault_test.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L156-L160:sha256:28a0c245b87041038c7690d3cbce2cb63939061a1fbfa3be0eb300a80139f544
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both ordered/reference and indexed finite Session fault/publication scenarios. |
| inputs / outputs | The declared tiny nullable row, genuine fixture root and selected public action in; assertions, actual reopened survivor state and finite probe counters out. |
| invariants | Fault coverage is bounded by observed actions/syscalls, not every possible workload. EIO/real process outcomes are validated by reopening rather than inferred from fsync. Surviving W/I/C/D and NULL bag weight 2/source offset 10 must agree. |
| ownership | Namespace copies are disposable test workspace, never a replacement production checkpoint. Parent/child FD and Session lifetimes are explicitly closed before receiving; allocation-denial guards use the existing test-only seams. |
| failure | Expected typed file/generation failures require reopen on retained owners; unexpected outcomes/assertions fail the test. forked cuts must exit 77; no production catch/repair framework is introduced. |
| cost | Test-only trace/copy/fork/oracle work; descriptor/allocation baselines are checked. The no-new claim is only the actually tested funded append-publication/acknowledgment interval, not a global allocation or latency theorem. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md), [tests/support/sql_rows_session_fixture.hpp](../../../../../tests/support/sql_rows_session_fixture.hpp), [tests/support/sql_aggregate_session_probe.hpp](../../../../../tests/support/sql_aggregate_session_probe.hpp) |
