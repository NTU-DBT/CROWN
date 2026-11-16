# `examples/component-runtime/native_set.cpp` — block usage map

[Source](../../../../../examples/component-runtime/native_set.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `9da81f727352f5043407e2255a441ae55a93f85f58271f380e424254b33b23cb`. 114 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../examples/component-runtime/native_set.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. | source comment (unverified): // Read genuine epoch-zero results, including nullary truth and EXISTS(false). · [reviewed contract](#b0001) |
| [B0002 · 11–16](../../../../../examples/component-runtime/native_set.cpp#L11) | Callable definition: U64 initial_cardinality(runtime::DeltaRuntime& owner, U64 work) | calls results, next, add_records; returns result; 1 loop sites; source comment (unverified): // Read genuine epoch-zero results, including nullary truth and EXISTS(false). · [reviewed contract](#b0002) |
| [B0003 · 17–20](../../../../../examples/component-runtime/native_set.cpp#L17) | Callable definition: void fold_cardinality(U64& count, SetOperation sign) | calls add_records, require; guard else { require(count &gt; 0, "set delta would underflow cardinality"); --count; }; growth insert · [reviewed contract](#b0003) |
| [B0004 · 21–109](../../../../../examples/component-runtime/native_set.cpp#L21) | Callable definition: int run(int argc, char** argv) | calls Clock::now, read_request, elapsed, at; guard require(output == "cardinality" \|\| output == "delta_and_snapshot", "unsupported native set output");; returns report({{@ ,1}, {@ ,@ },; growth push_back; 4 loop sites; source comment (unverified): // These are actual projected DISTINCT set records. Folding them retains · [reviewed contract](#b0004) |
| [B0005 · 110–110](../../../../../examples/component-runtime/native_set.cpp#L110) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 111–114](../../../../../examples/component-runtime/native_set.cpp#L111) | Callable definition: int main(int argc, char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0006) |

## B0001

[Lines 1–10](../../../../../examples/component-runtime/native_set.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:c7988e55e86070ae26c0efd781ae67de8053a5b9330fdedd502788e24325e52c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the direct unweighted set adapter to the native request and borrowed-update APIs. |
| inputs / outputs | Imports cold admission/observation helpers, PhysicalUpdateView and optional owner/epoch storage; opens local names. |
| invariants | Only public unweighted DeltaRuntime execution is used; no weighted DISTINCT route or handwritten query class is substituted. |
| ownership | No owner is instantiated by these imports; run creates each actual account-backed facade. |
| failure | Header/link incompatibility is a build failure, not runtime error recovery. |
| cost | Compilation/type declarations only; later actual setup, epoch and output costs are measured separately. |
| Design | [include/crown/runtime/update_view.hpp](../../../../../include/crown/runtime/update_view.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md) |

## B0002

[Lines 11–16](../../../../../examples/component-runtime/native_set.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L16:sha256:9be748162f4627e31a14358159e6f585285e3ec1afe8e00687fa57ff8412bf9d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the scalar cardinality from actual epoch-zero SQL set results. |
| inputs / outputs | Drains owner.results under the real cursor work grant and increments a checked uint64 count. |
| invariants | Handles ordinary empty sources, nullary truth and the always-present EXISTS Boolean result without assuming zero. No row dictionary survives. |
| ownership | One genuine cursor/owning result at a time; only the scalar remains after terminal next closes the reader lease. |
| failure | Cursor/account/work failure or scalar overflow stops construction of this pass; existing owner cleanup releases native state. |
| cost | Included in initialization; actual cursor startup/rows/termination/destruction costs apply. It is not a free COUNT shortcut. |
| Design | [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/ordered_delta.md](../../../../ordered_delta.md) |

## B0003

[Lines 17–20](../../../../../examples/component-runtime/native_set.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L20:sha256:fafb773eae534181225cadd9281b585759e74696004aa789e3a6cf01891319b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one exact projected set delta to the scalar cardinality without wraparound. |
| inputs / outputs | Insert uses bounded addition; erase requires a positive count before decrement. |
| invariants | Only genuine signed distinct-result records enter. The scalar represents set cardinality, not join-witness COUNT(*). |
| ownership | Mutates one caller-owned integer and retains no row, key or runtime metadata. |
| failure | Overflow/underflow throws at the wrapper boundary instead of silently wrapping; it cannot roll back a committed native event. |
| cost | Constant per signed output check/arithmetic, explicitly part of output/fold cost; no core hook is added. |
| Design | [docs/ordered_delta.md](../../../../ordered_delta.md), [Refactor.md §14.4](../../../../../Refactor.md) |

## B0004

[Lines 21–109](../../../../../examples/component-runtime/native_set.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L109:sha256:ee115cc8b9d5aec6cf53d061aa6b9b841e9b28badd407a494439f29a47f725f6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the direct unweighted original-SQL set comparison with genuine signed-output cardinality or full observations. |
| inputs / outputs | Reads/compiles once, resolves physical tables and runtime policy, creates each fresh owner, applies one physical event per epoch, drains exact signed deltas and optionally complete current results; emits per-event observations/clocks/account facts. |
| invariants | One transaction per input remains explicit. Cardinality initializes from real epoch0 and folds checked projected DISTINCT deltas; maintenance cardinality scans genuine current results. delta_and_snapshot requires delta mode and every-input observation. Longer cardinality intervals still drain/fold all internal deltas; final partial observation is marked. |
| ownership | Compiler/input/report DTOs stay outside the receiving native account. Each pass owns one DeltaRuntime and one transient epoch/cursor; only one scalar is retained across outputs. JSON rows exist only for verification, not measured query state. |
| failure | Cold unsupported controls, actual compiler/runtime/cursor/resource failures and report failures propagate through one CLI catch. Atomic engine preparation retains its own rollback; postcommit observation failure terminates without reapplying input. |
| cost | Shared cold setup is charged once. Initialization includes epoch0 enumeration. Apply includes genuine preparation/commit; output includes signed transfer/fold and requested full drain, release closes the epoch, loop wall includes metadata/clocks, teardown destroys the owner. No steady-state, delay or dispatch-only theorem follows. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/query_memory.md](../../../../query_memory.md), [docs/measurement.md](../../../../measurement.md), [Refactor.md §14.3–14.4](../../../../../Refactor.md) |

## B0005

[Lines 110–110](../../../../../examples/component-runtime/native_set.cpp#L110); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L110:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the implementation helper scope before its public executable entrypoint. |
| inputs / outputs | Ends the enclosing C++ namespace; helper names retain their declared linkage. |
| invariants | The brace changes lexical scope only and grants no execution, proof or durable authority. |
| ownership | No separate runtime resource is created or released by this lexical closure. |
| failure | A malformed scope is a compilation error; no runtime handler is installed. |
| cost | No executable work. |
| Design | [examples/component-runtime/native_set.cpp](../../../../../examples/component-runtime/native_set.cpp) |

## B0006

[Lines 111–114](../../../../../examples/component-runtime/native_set.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L114:sha256:7aae8c742e4167d8eeef2e0d4abb84b0ab94a876cff8629f740bf8545de8fe8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate this native_set adapter process to a single checked CLI exit status. |
| inputs / outputs | Calls run once, forwards its flushed-report status, and catches std::exception to stderr/nonzero. |
| invariants | The only added exception boundary is the CLI. Zero exit is completed observation transport, not independent correctness or B04 acceptance. |
| ownership | Ordinary unwinding destroys local owners and releases locks/buffers; already committed durable files remain inspectable. |
| failure | Standard exceptions become failure status. No retry, source reapplication, rollback of committed work or fabricated success report is introduced. |
| cost | Normal call/return plus failure diagnostics; final report encoding/flush is outside native service clocks. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |
