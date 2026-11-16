# `examples/component-runtime/native_rows.cpp` — block usage map

[Source](../../../../../examples/component-runtime/native_rows.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `6f6cf677c0d516e88daf1e1951b58dd5a24b2e31549ff6fb45604ecbb898fb7a`. 139 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../examples/component-runtime/native_rows.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–134](../../../../../examples/component-runtime/native_rows.cpp#L13) | Callable definition: int run(int argc, char** argv) | calls Clock::now, read_request, elapsed, require; guard require(request.document.at("output") == "compressed_bag", "SQL rows require compressed_bag output"…; returns report({{@ ,1},{@ ,@ },; growth push_back, reserve; 4 loop sites; source comment (unverified): // Repeated full-row edits form genuine before/after chains. The native · [reviewed contract](#b0002) |
| [B0003 · 135–135](../../../../../examples/component-runtime/native_rows.cpp#L135) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 136–139](../../../../../examples/component-runtime/native_rows.cpp#L136) | Callable definition: int main(int argc, char** argv) | calls run, what; returns run(argc,argv); 1 · [reviewed contract](#b0004) |

## B0001

[Lines 1–12](../../../../../examples/component-runtime/native_rows.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:b029614abc53dd51a524b328c11c6a79f401e5d353c0508dd2caa6e3efb27d0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the weighted nullable SQL-row adapter to genuine source/runtime factories. |
| inputs / outputs | Imports SqlRowsProgram, SqlRowsRuntime, batching utilities and optional owner storage under local aliases. Includes the public checked-tree JSON writer. |
| invariants | This execution family preserves original SQL bag/DISTINCT semantics and remains separately labeled from native_set. |
| ownership | Imports hold no source rows; the per-pass runtime owns actual weighted state and account. |
| failure | Missing public API or link closure fails compilation before any source event runs. |
| cost | Compilation/type declarations only. No additional per-row string or tracing hook is enabled. |
| Design | [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0002

[Lines 13–134](../../../../../examples/component-runtime/native_rows.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L134:sha256:b6f42358a9d925ff032d9b9406a5758fac022b8495d624e8ac689f36b24ea85d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare genuine weighted SQL rows under single replacements or atomic net commands at shared observation boundaries. |
| inputs / outputs | Binds original SQL/catalog to SqlRowsProgram, proves its source tree, applies real prepare_batch(SourceReplacements) exact chains, then drains compressed nullable result/multiplicity records only at declared physical boundaries. Reports separate transaction sequence and input begin/end offsets. The final report exports the actual selected source tree; contradiction exports null. |
| invariants | Bag versus DISTINCT comes from the actual original SQL; this is not unweighted set execution. A set artifact cannot select this source and DeltaMode is unsupported. Observation interval is a positive multiple of transaction size; final partial commands/observations are explicit. Native preparation consolidates duplicate-row chains/cancellation without exposing intermediate output. Runtime tree identity comes from that selected tree, not an inferred head/body shape. |
| ownership | Compiler metadata is immutable input. A fresh account/runtime owns each pass. Current-transaction cells/spans are bounded ordinary input buffers destroyed in the release phase; the native token imports its own storage. No adapter source/group/joined-row ledger or measured result graph is retained. |
| failure | Binding/proof/cold-control/actual source-weight/constraint/account/work/arithmetic/output failure propagates. Genuine prepare_batch owns rollback; after commit, output failure cannot undo a transaction. No failed check is bypassed or converted into correctness authority. |
| cost | Transaction preparation includes constructing stable input spans. Apply includes actual source/native consolidation, preparation and commit. Native/source work facts come from the actual returned epoch, not synthetic estimates. Common-boundary cursor work is fully charged; report JSON and account sampling have their declared separate scope. Only representation-specific record counts are reported. Tree export is once in final report construction, outside transaction/API clocks; no update hook or per-row tree traversal is added. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/measurement.md](../../../../measurement.md), [Refactor.md §8.1 and §14.4](../../../../../Refactor.md) |

## B0003

[Lines 135–135](../../../../../examples/component-runtime/native_rows.cpp#L135); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L135:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the implementation helper scope before its public executable entrypoint. |
| inputs / outputs | Ends the enclosing C++ namespace; helper names retain their declared linkage. |
| invariants | The brace changes lexical scope only and grants no execution, proof or durable authority. |
| ownership | No separate runtime resource is created or released by this lexical closure. |
| failure | A malformed scope is a compilation error; no runtime handler is installed. |
| cost | No executable work. |
| Design | [examples/component-runtime/native_rows.cpp](../../../../../examples/component-runtime/native_rows.cpp) |

## B0004

[Lines 136–139](../../../../../examples/component-runtime/native_rows.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L139:sha256:7aae8c742e4167d8eeef2e0d4abb84b0ab94a876cff8629f740bf8545de8fe8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate this native_rows adapter process to a single checked CLI exit status. |
| inputs / outputs | Calls run once, forwards its flushed-report status, and catches std::exception to stderr/nonzero. |
| invariants | The only added exception boundary is the CLI. Zero exit is completed observation transport, not independent correctness or B04 acceptance. |
| ownership | Ordinary unwinding destroys local owners and releases locks/buffers; already committed durable files remain inspectable. |
| failure | Standard exceptions become failure status. No retry, source reapplication, rollback of committed work or fabricated success report is introduced. |
| cost | Normal call/return plus failure diagnostics; final report encoding/flush is outside native service clocks. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |
