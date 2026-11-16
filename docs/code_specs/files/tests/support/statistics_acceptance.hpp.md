# `tests/support/statistics_acceptance.hpp` — block usage map

[Source](../../../../../tests/support/statistics_acceptance.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `488f77e10408f15db116a16920081884d3fdd52d79ada451d3168f632c235526`. 169 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/support/statistics_acceptance.hpp#L1) | Imports dependencies; guards repeated header inclusion; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Bounded sequential test coverage counts, not atomic/saturating runtime counters. · [reviewed contract](#b0001) |
| [B0002 · 24–26](../../../../../tests/support/statistics_acceptance.hpp#L24) | Callable definition: inline void require(bool value, const std::string& label) | calls std::runtime_error; guard inline void require(bool value, const std::string& label) { · [reviewed contract](#b0002) |
| [B0003 · 27–32](../../../../../tests/support/statistics_acceptance.hpp#L27) | Callable definition: inline ws::Options census() | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 33–36](../../../../../tests/support/statistics_acceptance.hpp#L33) | Callable definition: inline void enable(runtime::DeltaRuntime& runtime) | calls require, options, configure_workload_statistics, census; guard require(runtime.options().physical.support.order == requested_order, "actual Delta propagation orde… · [reviewed contract](#b0004) |
| [B0005 · 37–40](../../../../../tests/support/statistics_acceptance.hpp#L37) | Callable definition: inline void enable(runtime::QuerySession& session) | calls require, report_metadata, options, configure_workload_statistics; guard require(session.report_metadata().options().physical.support.order == requested_order, "actual sess… · [reviewed contract](#b0005) |
| [B0006 · 41–46](../../../../../tests/support/statistics_acceptance.hpp#L41) | Callable definition: inline st::OwnerRequest source_request(const Database& database) | calls size, push_back; returns request; growth push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 47–69](../../../../../tests/support/statistics_acceptance.hpp#L47) | Callable definition: inline void sources(const st::CombinedCapture& capture, const Database& database, runtime::SupportOwnerId owner, std::uint64_t se… | calls state, workload, require, stamp; guard require(state.stamp().owner == owner && work.stamp().owner == owner &&; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 70–74](../../../../../tests/support/statistics_acceptance.hpp#L70) | Callable definition: inline void sources(const runtime::DeltaRuntime& runtime, const Database& database, const std::string& label) | calls capture_combined_statistics, source_request, owner, sequence · [reviewed contract](#b0008) |
| [B0009 · 75–80](../../../../../tests/support/statistics_acceptance.hpp#L75) | Callable definition: inline void sources(const runtime::QuerySession& session, const Database& database, const std::string& label) | calls capture_combined_statistics, source_request, require, has_value; guard require(capture.has_value(), label + ": active session capture absent"); · [reviewed contract](#b0009) |
| [B0010 · 81–81](../../../../../tests/support/statistics_acceptance.hpp#L81) | Explanatory comments or spacing. | source comment (unverified): // This accumulator is independent of Cell::observe/merge and the collector. · [reviewed contract](#b0010) |
| [B0011 · 82–90](../../../../../tests/support/statistics_acceptance.hpp#L82) | Callable definition: inline void observe(ws::Cell& cell, std::uint64_t value) | calls std::min, std::max; 1 loop sites; source comment (unverified): // This accumulator is independent of Cell::observe/merge and the collector. · [reviewed contract](#b0011) |
| [B0012 · 91–92](../../../../../tests/support/statistics_acceptance.hpp#L91) | Explanatory comments or spacing. | source comment (unverified): // Roots use supplied inputs; optional derivation details use the public audit. · [reviewed contract](#b0012) |
| [B0013 · 93–162](../../../../../tests/support/statistics_acceptance.hpp#L93) | Callable definition: inline void event(const ws::Snapshot& before, const ws::Snapshot& after, const std::optional&lt;PhysicalSetUpdate&gt;& input, bool chan… | calls require, options, census, descriptors; guard require(before.options() == census() && after.options() == census(), label + ": census not enabled"…; growth insert; 2 loop sites; source comment (unverified): // Roots use supplied inputs; optional derivation details use the public audit. · [reviewed contract](#b0013) |
| [B0014 · 163–168](../../../../../tests/support/statistics_acceptance.hpp#L163) | Callable definition: inline void print() | calls  · [reviewed contract](#b0014) |
| [B0015 · 169–169](../../../../../tests/support/statistics_acceptance.hpp#L169) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::statistics_acceptance · [reviewed contract](#b0015) |

## B0001

[Lines 1–23](../../../../../tests/support/statistics_acceptance.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::uint64_t checked_events
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count how many bounded acceptance assertions were exercised in one executable. |
| inputs / outputs | Four inline globals accumulate events, derivations, source components and metadata-only steps. |
| invariants | Non-atomic, nonsaturating test counters require sequential bounded callers. They are coverage summaries, not runtime query counters or proof authority. |
| ownership | Static scalar test storage; no native account or heap owner. |
| failure | No overflow/concurrency guard; caller scope excludes those cases. |
| cost | Fixed scalar increments; no production instrumentation is added. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
inline constexpr auto requested_order = runtime::PropagationOrder::lifo;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the expected propagation order in the LIFO acceptance compile variant. |
| inputs / outputs | CROWN_STATISTICS_LIFO branch chooses lifo; alternate source branch chooses fifo. |
| invariants | Compile selection is an expectation; enable checks actual runtime configuration rather than changing it silently. |
| ownership | Static constexpr scalar with no owner/borrow. |
| failure | No runtime failure; actual mismatch is rejected by enable. |
| cost | Compile-time constant; runtime comparison at enable only. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
inline constexpr auto requested_order = runtime::PropagationOrder::fifo;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the expected order in the ordinary acceptance compile variant. |
| inputs / outputs | No CROWN_STATISTICS_LIFO selects fifo. |
| invariants | Does not configure native propagation by itself. |
| ownership | Static constexpr scalar. |
| failure | No runtime failure in declaration. |
| cost | Compile-time value only. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 24–26](../../../../../tests/support/statistics_acceptance.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void require(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert acceptance evidence with a prefixed owning diagnostic. |
| inputs / outputs | False throws runtime_error(C01 acceptance:+label); true returns. |
| invariants | Caller label concatenations and literal-to-string conversions may allocate even when condition succeeds. |
| ownership | Borrows label synchronously; thrown exception owns its message. |
| failure | Assertion/message allocation failures propagate, without mutating native state. |
| cost | Fixed branch plus any caller label construction; exception string assembly on failure. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 27–32](../../../../../tests/support/statistics_acceptance.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline ws::Options census(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select exact bounded workload counter collection for acceptance cases. |
| inputs / outputs | Mode counters, detail_budget1,000,000 and default period/offset select all bounded events. |
| invariants | Large finite detail budget is not infinite, a CPU bound or a native byte allowance; arrival timing remains unavailable in this mode. |
| ownership | Returns owning options value. |
| failure | No explicit rejection during fixed option setup; runtime configure validates it. |
| cost | Fixed option construction; real statistics slab allocation happens at configure. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 33–36](../../../../../tests/support/statistics_acceptance.hpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void enable(runtime::DeltaRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable real workload collection after checking the intended propagation order. |
| inputs / outputs | Requires actual DeltaRuntime physical.support.order then configures census workload statistics. |
| invariants | Uses real current owner/options and may reset collection interval per actual API. |
| ownership | Borrows actual live owner; native collection storage is funded/retained by that owner, not by test counters. |
| failure | Mismatch assertion or native configuration/account/grant failures propagate. |
| cost | Actual configuration and possible statistics slab allocation plus metadata/option comparison. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 37–40](../../../../../tests/support/statistics_acceptance.hpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void enable(runtime::QuerySession&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable real workload collection after checking the intended propagation order. |
| inputs / outputs | Reads actual session report metadata order then configures census workload statistics. |
| invariants | Session metadata is observed synchronously; supported lifecycle/admission checks remain in actual configure API. |
| ownership | Borrows actual live owner; native collection storage is funded/retained by that owner, not by test counters. |
| failure | Mismatch assertion or native configuration/account/grant failures propagate. |
| cost | Actual configuration and possible statistics slab allocation plus metadata/option comparison. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 41–46](../../../../../tests/support/statistics_acceptance.hpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline st::OwnerRequest source_request(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request one cardinality-only public source component per ordinary model table. |
| inputs / outputs | Builds SourceScope TableId0..N-1 selections with fields=nullopt. |
| invariants | No distributions or row values are requested; actual bounded fixtures stay within256 selections. This request is editable descriptive data. |
| ownership | Returns ordinary owning vector; database is borrowed only for its table count. |
| failure | Vector allocation errors propagate; native capture later validates request cardinality/IDs. |
| cost | O(tables) ordinary request construction/allocation. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 47–69](../../../../../tests/support/statistics_acceptance.hpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void sources(const st::CombinedCapture&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check source cardinalities and coherent actual owner/epoch workload capture. |
| inputs / outputs | Asserts available state/nonpending work stamps, ordered source scopes/no fields, exact model table sizes/no distribution, census exact detail and unavailable arrival timing. |
| invariants | Only cardinalities are compared; equal sizes do not prove row equality or query correctness. Public capture owns real actual-owner evidence; ordinary Database is separate. |
| ownership | Borrows owning capture/model for call; increments static test counts only. |
| failure | Assertion/diagnostic allocation failure propagates; no native repair or lifetime extension. |
| cost | O(source components) checks and label construction; capture work/allocation already occurred before this overload. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 70–74](../../../../../tests/support/statistics_acceptance.hpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void sources(const runtime::DeltaRuntime&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual Delta state/workload then check against model cardinalities. |
| inputs / outputs | Builds request, calls capture_combined_statistics, passes actual runtime owner/sequence to validator. |
| invariants | Synchronous exclusive test use keeps separate owner/sequence reads coherent; not a concurrent snapshot protocol. |
| ownership | Local owning CombinedCapture retains native result until validation ends; request/model data are ordinary. |
| failure | Actual capture/request allocation/grant or assertion failures propagate. |
| cost | Full native combined capture cost plus ordinary request and component validation; numeric work is not all CPU. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 75–80](../../../../../tests/support/statistics_acceptance.hpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void sources(const runtime::QuerySession&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture/check a present active-session combined observation. |
| inputs / outputs | Requires optional capture engaged; validates against report_metadata owner and committed_sequence. |
| invariants | Active valid lifecycle is required; capture absence is a mismatch, not a generic empty result. Synchronous caller avoids mutation between reads. |
| ownership | Optional owns actual capture; metadata views remain within session lifetime. |
| failure | Native capture/allocation or assertion failures propagate. |
| cost | Actual combined capture plus metadata reads/request construction and O(tables) checks. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 81–81](../../../../../tests/support/statistics_acceptance.hpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L81:sha256:e77eb85d32f73a180e7780b749e2febb1cde966c4076eafc549626b5e42ee729
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: This accumulator is independent of Cell::observe/merge and the collector. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 82–90](../../../../../tests/support/statistics_acceptance.hpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void observe(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate bounded expected cell min/max/count/sum/log2-bin independently of production collector methods. |
| inputs / outputs | Sets extrema on first value, updates scalar totals and increments bin equal to bit length(value), with0 in bin0. |
| invariants | Uses no Cell::observe/merge; input maxuint64 maps bin64. Arithmetic counters/sum are not saturating and fixtures stay below overflow. |
| ownership | Mutates caller-owned Cell including fixed bin array; no retained views. |
| failure | No explicit numerical/overflow rejection; does not independently verify collector saturation behavior. |
| cost | At most64 divisions plus fixed array/scalar updates; no helper container allocation. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 91–92](../../../../../tests/support/statistics_acceptance.hpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L92:sha256:f6a60f4eda0f5764ba455818cbd5f2de9f2b2a4781e4627d3c509cbc5267336f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Roots use supplied inputs; optional derivation details use the public audit. With input present, other detail roles are outside this helper's comparison. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 93–162](../../../../../tests/support/statistics_acceptance.hpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void event(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check workload admission/commit/root counters and optional audited derivation details for one physical or metadata-only step. |
| inputs / outputs | Compares stable options/descriptors/owner/reset/config/segment; checks metadata increments; reconstructs input roots and optional derivation counts/distribution; checks epoch and updates test totals. |
| invariants | Root input facts derive from supplied command/update. Derivation expectations derive from public DerivationChange audit, not independent relational truth. With input present other detail roles are not compared; absent audit leaves derivation cells unchecked. |
| ownership | Before/after own their real snapshots; optional span borrows caller audit only for call. Local expected Cell copies own numeric data. |
| failure | Mismatch/diagnostic allocation errors propagate. Valid factory snapshot dimensions and bounded nonsaturating test arithmetic are prerequisites. |
| cost | O(cells + matching descriptors*provided derivations), bit-length observation loops and label copies; no production state mutation. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
const auto admission_increment
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish a root admitted before the before-snapshot from fresh input admission. |
| inputs / outputs | already_admitted requires input, pending before and exactly one unclosed attempt; suppresses attempts/selected increment while commit/complete still increment. |
| invariants | This reflects a real private physical root stage, not a source-progress or logical-command counter. |
| ownership | Only borrowed snapshots/audit and local numeric Cell copy; globals count successful test coverage. |
| failure | Assertion/diagnostic allocation errors propagate; actual engine step already occurred at caller. |
| cost | Descriptor/audit scans and fixed numeric accumulation, plus ordinary diagnostic strings. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
if (descriptor.role == ws::Role::input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct physical table/op root changed/noop counts. |
| inputs / outputs | Copies before cell and increments inputs/complete detail and changed/noop for the unique matching table/op. |
| invariants | Root is one per actual physical event; no-input metadata step permits zero matching roots. |
| ownership | Only borrowed snapshots/audit and local numeric Cell copy; globals count successful test coverage. |
| failure | Assertion/diagnostic allocation errors propagate; actual engine step already occurred at caller. |
| cost | Descriptor/audit scans and fixed numeric accumulation, plus ordinary diagnostic strings. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
} else if (derivations && descriptor.role == ws::Role::derivation)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cross-check optional derivation-cell observations against public audit entries. |
| inputs / outputs | Matches occurrence and input scope/op, requires changed before/after, updates crossings and manual distribution, compares whole cell. |
| invariants | Public audit is the expected-data source here; this check does not independently establish derivation values from source rows. |
| ownership | Only borrowed snapshots/audit and local numeric Cell copy; globals count successful test coverage. |
| failure | Assertion/diagnostic allocation errors propagate; actual engine step already occurred at caller. |
| cost | Descriptor/audit scans and fixed numeric accumulation, plus ordinary diagnostic strings. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

```text
} else if (!input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert workload silence on metadata-only window steps. |
| inputs / outputs | All remaining cells equal before when no physical input is supplied. |
| invariants | With input present this branch does not check support/occurrence/degree roles; coverage is intentionally bounded. |
| ownership | Only borrowed snapshots/audit and local numeric Cell copy; globals count successful test coverage. |
| failure | Assertion/diagnostic allocation errors propagate; actual engine step already occurred at caller. |
| cost | Descriptor/audit scans and fixed numeric accumulation, plus ordinary diagnostic strings. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 163–168](../../../../../tests/support/statistics_acceptance.hpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void print()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish bounded acceptance coverage counts for the test log. |
| inputs / outputs | Writes expected propagation order and four global counts to stdout. |
| invariants | These are test-assertion coverage counts, not timing, bytes, native work totals or semantic proof completeness. |
| ownership | Uses static scalars/ostream, retains no borrowed data. |
| failure | Default ostream flags are not explicitly checked; exceptional I/O/formatting allocation follows standard stream behavior. |
| cost | Fixed number of formatted numeric writes and actual output I/O. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [tests/unit/delta_runtime_test.cpp](../../../../../tests/unit/delta_runtime_test.cpp), [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 169–169](../../../../../tests/support/statistics_acceptance.hpp#L169); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L169-L169:sha256:9bf00afc726c98a7641ee2b7edebf230f0293856afe3529bff85145486d10db8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in statistics_acceptance.hpp: namespace crown::statistics_acceptance. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/statistics_acceptance.hpp](../../../../../tests/support/statistics_acceptance.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |
