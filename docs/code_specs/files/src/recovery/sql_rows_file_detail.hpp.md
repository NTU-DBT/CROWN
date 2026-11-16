# `src/recovery/sql_rows_file_detail.hpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_file_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `66196906c30637f87350f116dc53948f327322fb0832de710643b00d1a346041`. 19 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../src/recovery/sql_rows_file_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases. | source comment (unverified): // Reuse one bounded POSIX implementation, with a distinct row-record magic. · [reviewed contract](#b0001) |
| [B0002 · 16–18](../../../../../src/recovery/sql_rows_file_detail.hpp#L16) | Callable definition: inline void binding(const Descriptor& descriptor,const Binding& expected) | calls binary_detail::require, bool, sha256; guard binary_detail::require(bool(descriptor) && expected.descriptor_sha256==descriptor.sha256(),ImageFau… · [reviewed contract](#b0002) |
| [B0003 · 19–19](../../../../../src/recovery/sql_rows_file_detail.hpp#L19) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_rows::file_detail · [reviewed contract](#b0003) |

## B0001

[Lines 1–15](../../../../../src/recovery/sql_rows_file_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:ddd01ac1134f21e1d3fdb48f165bae186fa3f6ec7a67dbfef3b439205c505d15
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the existing bounded POSIX helpers for typed rows file implementations. |
| inputs / outputs | Include row files/shared file detail/binary helper and alias Io,Path,view,fail,tail,chain. |
| invariants | Sharing the I/O implementation creates no row program/runtime authority; concrete owners supply CROWNRW2 magic. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0002

[Lines 16–18](../../../../../src/recovery/sql_rows_file_detail.hpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L18:sha256:b03472152cc6617f57bb25d3e6a0342d5fe6d291a9a1f21aa355d8c541b30aff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a present row descriptor with the expected descriptor hash. |
| inputs / outputs | Const Descriptor and Binding -&gt; void iff descriptor is nonempty and expected.descriptor_sha256 equals descriptor.sha256(). |
| invariants | Checks only descriptor presence/hash; does not validate query_id, inspect files or rebind SQL. |
| ownership | Both inputs are borrowed; retains no owner. |
| failure | ImageFailure(binding) for mismatch; no catch. |
| cost | O(1) handle test and fixed 64-byte comparison; no hash recomputation, allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0003

[Lines 19–19](../../../../../src/recovery/sql_rows_file_detail.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:314a2a36dd024dfe4bebadd3f5c20e54599a5daff34193a57e98a9b46e8ac104
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
