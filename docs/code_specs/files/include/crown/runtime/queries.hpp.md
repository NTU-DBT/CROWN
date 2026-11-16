# `include/crown/runtime/queries.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/queries.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain Boolean CROWN record/survivor/projected-support state and enumerate current answers from factorized visible relations.

Snapshot SHA-256: `4145d89edcda795fded387deb8340cdf9b69bf81918ff9ed51d97209345d9aa1`. 64 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../../support_invariants.md), [docs/runtime_support.md](../../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/runtime/queries.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // A process-local directory name, not a recovery token or proof capability. · [reviewed contract](#b0001) |
| [B0002 · 13–17](../../../../../../include/crown/runtime/queries.hpp#L13) | Type/record definition: struct QueryId | source comment (unverified): // A process-local directory name, not a recovery token or proof capability. · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../../include/crown/runtime/queries.hpp#L18) | Explanatory comments or spacing. |  |
| [B0004 · 19–22](../../../../../../include/crown/runtime/queries.hpp#L19) | Type/record definition: struct QueryDirectoryLimits | source comment (unverified): // Zero admits an empty directory only. · [reviewed contract](#b0004) |
| [B0005 · 23–39](../../../../../../include/crown/runtime/queries.hpp#L23) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Serial, non-reentrant ownership directory. Each Session keeps its independent · [reviewed contract](#b0005) |
| [B0006 · 40–40](../../../../../../include/crown/runtime/queries.hpp#L40) | Callable definition: \[\[nodiscard\]\] std::size_t size() const noexcept | calls ; returns entries_.size() · [reviewed contract](#b0006) |
| [B0007 · 41–64](../../../../../../include/crown/runtime/queries.hpp#L41) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Borrow survives changes to other entries. It ends at erase/release of this · [reviewed contract](#b0007) |

## B0001

[Lines 1–12](../../../../../../include/crown/runtime/queries.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:9b1cac8d06b7b1736ed8085804d82772a530b078414dae23640c25975929f95c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the public optional serial query directory and its standard-container dependencies. |
| inputs / outputs | Header inclusion exposes QuerySession ownership, ordered storage and comparable numeric IDs. |
| invariants | Inclusion creates no query, thread, scheduler or shared operator state. |
| ownership | Definitions only; live ownership begins at construction/admission. |
| failure | Missing public dependency is a compile-time error. |
| cost | No execution on inclusion; this header adds no runtime instrumentation. |
| Design | [docs/independent_queries.md](../../../../../independent_queries.md), [Refactor.md §X10](../../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0002

[Lines 13–17](../../../../../../include/crown/runtime/queries.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L17:sha256:305c2bcc84616273802d13ac2100733585a4d4a96b736240de3aa449be7d3489
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name one admitted session inside one process-local directory. |
| inputs / outputs | Directory account identity plus monotonic ordinal; default pair is absent. |
| invariants | Comparison compares both numbers; IDs are local names and cannot authorize durable recovery. |
| ownership | Plain values neither own nor prolong a session. |
| failure | Foreign or removed IDs are rejected by the directory lookup. |
| cost | Fixed two-word storage and comparison. |
| Design | [docs/independent_queries.md](../../../../../independent_queries.md), [Refactor.md §X10](../../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0004

[Lines 19–22](../../../../../../include/crown/runtime/queries.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L22:sha256:0574a28dfcced01ed78c78e72685ad2340076a05fc67c2aaaab518f2b67fd915
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select independent finite directory count and requested-byte limits. |
| inputs / outputs | Default1024 live sessions and256KiB metadata; zero slots allows an empty directory. |
| invariants | These limits govern directory bookkeeping, not the independent sessions own memory grants. |
| ownership | Values copied into one directory; no resources yet. |
| failure | Insufficient controller memory fails directory construction; count exhaustion fails admission. |
| cost | Fixed value storage. |
| Design | [docs/independent_queries.md](../../../../../independent_queries.md), [Refactor.md §X10](../../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0005

[Lines 23–39](../../../../../../include/crown/runtime/queries.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L39:sha256:b7da89107488094d6bc50cb65e01ef7984eef3b46339c73b78b7d04be48571c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose stable serial ownership and failure-preserving admission without changing native query execution. |
| inputs / outputs | Constructor takes directory limits; admit takes a nonnull QuerySession::Owner lvalue; contains inspects IDs. |
| invariants | Directory is noncopyable/nonmovable; admission reserves storage before transferring the caller owner. |
| ownership | Directory owns its map and admitted session owners; caller owns fixed facade storage. |
| failure | Typed query_owner/query_limit/query_id_overflow errors precede transfer; account allocation failure preserves caller ownership. |
| cost | One controller and ordered-map nodes; admission/contains O(logQ); native updates need no directory lookup if caller holds a borrow. |
| Design | [docs/independent_queries.md](../../../../../independent_queries.md), [Refactor.md §X10](../../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0006

[Lines 40–40](../../../../../../include/crown/runtime/queries.hpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L40:sha256:b68d36ef491273627d9b344e218b349d9b02dff2218ca7a4d583af4a1c44d80a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the number of currently admitted owners. |
| inputs / outputs | No arguments; returns map size. |
| invariants | Removed sessions and historical IDs do not contribute. |
| ownership | Scalar result only. |
| failure | No failure and no allocation. |
| cost | O(1). |
| Design | [docs/independent_queries.md](../../../../../independent_queries.md), [Refactor.md §X10](../../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0007

[Lines 41–64](../../../../../../include/crown/runtime/queries.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L64:sha256:7bf68680b1a248beafa40f7693c244e48a307d325d992ae1fc4c7856ca55da39
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define inspection, borrowing, release and removal together with the separate map/account state. |
| inputs / outputs | directory_memory returns requested-byte statistics; at borrows a session; release transfers its owner; erase destroys that owner. |
| invariants | Other map entries do not invalidate a borrow; own removal/release/group destruction ends it. Rvalue at is deleted. IDs never reuse ordinals. |
| ownership | Allocator and controller live through entries destruction by member order; owning snapshots retain their separate existing lifetime. |
| failure | Invalid ID rejects before mutation; too-small metadata budget never borrows a query budget. |
| cost | Map storage O(Q), no dropped-query history; lookup/release/erase O(logQ); session destruction has its existing independent cost. |
| Design | [docs/independent_queries.md](../../../../../independent_queries.md), [Refactor.md §X10](../../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../../query_memory.md) |
