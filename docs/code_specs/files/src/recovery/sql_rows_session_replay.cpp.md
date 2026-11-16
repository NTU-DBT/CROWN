# `src/recovery/sql_rows_session_replay.cpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_session_replay.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `42e027d6b66a88c5b1e724af12f25697322131bf240bf5e6e59c6844bdb7ada2`. 81 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/recovery/sql_rows_session_replay.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 6–34](../../../../../src/recovery/sql_rows_session_replay.cpp#L6) | Callable definition: void Session::replay(std::string_view bytes,const Inspected& info,const WalState& after,void* context) | calls state, require, sequence, decode_input; guard require(!d.head && !d.spool && d.native.sequence()&lt;=delivered,SessionFault::binding);; growth emplace; source comment (unverified): // Logging a later Input proves the previous C was already acknowledged. · [reviewed contract](#b0002) |
| [B0003 · 35–40](../../../../../src/recovery/sql_rows_session_replay.cpp#L35) | Callable definition: void Session::validate_files(Data& d) | calls validate, require, read_root, selected; guard require(d.root.read_root(false,false)==d.root.selected(),SessionFault::binding); · [reviewed contract](#b0003) |
| [B0004 · 41–80](../../../../../src/recovery/sql_rows_session_replay.cpp#L41) | Callable definition: Session Session::recover_into(const resource::MemoryAccount& account,SessionPaths paths,const Id& query_id,const SessionLimits& l… | calls require, root, selected, retirement; guard require(limits.history_generations&gt;0,SessionFault::limit);; returns std::move(admitted.descriptor); restore_checkpoint_into(account,descriptor,{bytes.data(),bytes.size…; growth emplace, make_accounted_unique; source comment (unverified): // Rebinding's empty/static C0 runtime dies before the actual checkpoint owner · [reviewed contract](#b0004) |
| [B0005 · 81–81](../../../../../src/recovery/sql_rows_session_replay.cpp#L81) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_rows · [reviewed contract](#b0005) |

## B0001

[Lines 1–5](../../../../../src/recovery/sql_rows_session_replay.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:81416527d4a3f16223ccec4e9919ce8c40f2bb8324e0082298c56bad161df027
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare concrete rows Session/file dependencies, transport aliases and private scopes; executable protocols are in adjacent operations. |
| inputs / outputs | Declared fixed metadata, limits, aliases, factories or borrows in/out as this exact source region states. |
| invariants | Shared transport PODs/aliases confer no aggregate/SQL/native/file authority; concrete genuine factories and current owners enforce it. Rows use signed uint64 SQL deltas, separate from aggregate group replacements. |
| ownership | Only actual owning members retain data/accounts/locks; declarations/aliases/comments do not create state. Borrowed public views require a live serialized owner. |
| failure | No declaration creates a fallback, retry, snapshot, handler framework or implicit acknowledgment; corresponding operation guards define failure. |
| cost | Fixed declarations/metadata; actual native, codec, file, cold-image and cleanup work is stated at the reviewed operation, not assigned as free instrumentation here. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0002

[Lines 6–34](../../../../../src/recovery/sql_rows_session_replay.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L6-L34:sha256:7f20c6a31b9a5bb575894654e7652149fcdd168455bfd368eb004b9026c7513c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay typed WAL inputs/decisions through real SQL source preparation and verify exact durable output lineage. |
| inputs / outputs | One complete inspected row-family frame and staged WAL state in; private receiving runtime/head/spool/progress out. |
| invariants | A later Input proves prior C delivered; genuine Reject reason or Commit C/output length/hash must reproduce. Delivered epochs compare actual sink bytes; at most one final undelivered spool exists. |
| ownership | New receiving owner stays unpublished until full root/WAL/sink validation; decoded head and real token own all temporary borrows. |
| failure | Any corruption/binding/resource/semantic mismatch abandons private recovery; no repair occurs before whole-state acceptance. |
| cost | Explicit bounded replay commands, codec work, original native/source/decode grants and actual sink verification; no previous result-graph import. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0003

[Lines 35–40](../../../../../src/recovery/sql_rows_session_replay.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L40:sha256:5ef3541d3bea9946168137c84c36f8c428ca7d2318efa3d3c704b51d78217e61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recheck actual sink/WAL EOF/stamps and selected root continuity while preserving the prior fail-stop latch. |
| inputs / outputs | Locked Data with a saved poison state in; unchanged validated file observations out. |
| invariants | Validation performs no truncation. If invoked during checkpoint it cannot clear the already-poisoned publication latch. |
| ownership | Actual owners/locks remain held; no receipt/DTO substitutes for current bytes. |
| failure | Any failure leaves poisoned true and requires reopen; normal success restores exactly the prior poison value. |
| cost | Bounded actual stat/read/root validation under existing file/generation grants. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0004

[Lines 41–80](../../../../../src/recovery/sql_rows_session_replay.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L80:sha256:92210d2d3a5a893ad8e2d3a3747966eb8a9c14e2db6fe2a7ba25282355601d3a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct a genuine SQL rows Session from the selected root, descriptor, physical checkpoint and typed WAL/sink. |
| inputs / outputs | Receiving account/paths/query ID and finite cold/replay limits in; fully validated locked Session out. |
| invariants | Require descriptor/delivery lineage, C≤I, generation-1 finite history and no retirement. Rebind genuine metadata, restore physical rows, replay decisions, verify exact sink coverage, then optionally repair only validated torn tails. |
| ownership | Empty descriptor-admission runtime dies before checkpoint runtime is built. Keep one actual native owner/head/spool and original receiving account; factory remains private through all checks. |
| failure | Any complete corruption, changed file, type/constraint/arithmetic/resource or coverage failure unwinds; no partial public owner or pre-barrier truncation. |
| cost | Explicit descriptor/cold source rebuild, replay and file work under separate finite grants; no implicit timing or dynamic-delay guarantee. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0005

[Lines 81–81](../../../../../src/recovery/sql_rows_session_replay.cpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L81:sha256:5a88989d646de8c904ac4cbcd84db92dc85500003eb77614a29dedc10d8206dd
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
