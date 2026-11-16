# Query memory contract

Native SupportRuntime, PhysicalRuntime, DeltaRuntime and QuerySession enforce
one memory account per admitted query. Configure its requested-byte ceiling with
`SupportOptions::memory_limit_bytes` (256 MiB by default), nested under physical,
Delta and session options as appropriate. A runtime created from an existing
native compiler/cache program admits its own complete executable metadata into
that receiving account. Internal rebuilds, pending updates and resumed cursors
keep the original account and cap.

The account covers engine-created executable metadata, table/index/arena storage,
support and derivation state, journals/pins, Delta live indexes and spools,
session/window/reader/queue storage, tuple payloads, cursor state, observations,
statistics, ranking/selection results and cache insertions, and retained native
reports. Temporary work and overlapping old/new state consume the same cap.
Query operations cannot create a new allowance to evade it. Indexed admission,
initialization and execution also retain their existing work-grant contracts.

The limit counts actual upstream allocation requests, including component
headers and alignment. Payload bytes are reported separately. It is not a
process-RSS or allocator-private-overhead limit. Allocation statistics distinguish
active, retained and reusable free-pool storage, peak requested bytes, and
successful/freed allocation history. Logical row/slot/work limits and C02/C05
modeled slot costs retain their own units; they do not substitute for this cap.

Memory or configured counter overflow rejects the operation while preserving
the valid committed epoch. Rollback, publication and final release do not need
new allocations. Historical counters can record failed speculative work that
allocated successfully before a later stop; current resident storage is restored.
Repeated no-op/churn does not retain a history of logical rows. Reusable capacity
and exhausted handle-generation slots remain visible and charged. Holding old
epochs, outputs or reports can intentionally consume the budget; release permits
retry under the same cap.

## Boundaries

The account governs engine allocations after query admission. The following are
explicit caller/component resources:

- Caller-provided streams and their existing I/O buffers; caller input batches,
  rows and options before native import.
- Supplied immutable proof/candidate/compiler/declaration artifacts and existing
  cache entries. New query-owned program admission and fresh result/cache storage
  are funded; a cache hit can share a previously funded immutable artifact.
- Initial standalone compiler/search/parser work before a runtime exists.
  Standalone component APIs can own separate accounts. Current-owner ranking and
  selection use the receiving query/evidence account and native lowering.
- Explicit JSON/text/physical-plan/canonical-state/snapshot exports and existing
  formatted exception presentation. C++ exception-runtime storage is also outside
  operator-new accounting. MemoryFailure itself carries a fixed nonowning error.

These boundaries do not permit an internal runtime path to export an ordinary
graph and silently retain it. Native stream/queue decoding, runtime statistics,
program replanning and invariant checking use their funded native paths. Caller
serialization limits bound the encoded result, rather than all export temporaries.

## Reports and evidence

[Operator memory reports](memory_reports.md) reconcile actual table/operator
counts with account allocation owners and arena/index storage. Their allocation
partition is account-wide, including held generations and report storage; logical
counts describe the captured committed runtime. Pending/released reports do not
invent committed counts. Shared bindings reference each owner without duplicating
bytes in the owner partition.

[Invariant diagnostics](invariant_memory.md) fund both localized issue keys and
independently derived expected state. Retained reports survive runtime changes
and closure. The existing version1 wire format remains unchanged.

The [acceptance record](verification/s05-native-acceptance-2026-11-09.md) maps the
S05 requirements to code, allocation/failure tests, exact report checks and the
full native/fresh-source matrix. Historical migration notes remain in
[memory_accounts.md](memory_accounts.md).
