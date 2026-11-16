# Runtime initialization, rebuild and inspection (R06)

Status: R06 is verified. Independent semantic, corruption, record-scale and
persistent-failure fixtures pass, and its historical 75-test matrix passed GCC Debug/Release,
ASan/UBSan, Clang and a fresh source-only build. See the
[R06 acceptance record](verification/runtime-initialization-2026-11-06.md).
The newer [O03 matrix](verification/batches-windows-2026-11-06.md) passes
all 79 tests; the R06 source seal describes its preceding snapshot.
The preceding [O02 snapshot](verification/session-lifecycle-2026-11-06.md)
remains historical; its hashes do not describe these initialization edits.

The common APIs are [initialization.hpp](../include/crown/runtime/initialization.hpp)
and [inspection.hpp](../include/crown/runtime/inspection.hpp). Physical and delta
owners provide `initialize`, `rebuilt`, `initialization_metrics`,
`canonical_state` and `inspect_invariants`. Existing constructors still create
empty owners. The [session API](session_lifecycle.md) additionally accepts an
initial Database before its owned input stream. No new CLI command is added.

## Snapshot initialization

```cpp
BuildOptions build{BuildMethod::direct, 1000000};
auto runtime = DeltaRuntime::initialize(plan, initial_database, options, build);
auto report = runtime.inspect_invariants();
if (!report.valid()) { /* handle issues or incomplete inspection */ }
// First actual external input has sequence 1.
```

The plan is a verified physical program; Database contains every source table
in catalog order, including unused tables, and complete typed set rows in
source-column order. Physical identity includes unused columns. Before either
build path, the entire final snapshot is checked for row shape, scalar/decimal
domains and enforced unique/FK constraints. Runtime validation borrows the
already-admitted compiled catalog and caller row values. Projected fields and
ordered constraint keys use the original query memory account; scalar and
decimal checks avoid ordinary row/string formatting scratch.

A valid snapshot may have cyclic foreign keys and no legal first public
insertion. Validation therefore precedes unpublished construction and applies
to the full snapshot. Ordinary external events retain after-state constraint
validation; the initializer does not expose an option to bypass those checks.

Initialization returns a new owner at sequence zero. It emits no physical/
delta epoch, acknowledges no source event and manufactures no source position.
The caller's Database is borrowed only during construction; the new owner has
its own source values. Allocation, exact-counter or work failure destroys only
the unpublished replacement. No partially built owner escapes.

The initialized session factory is
`QuerySession::create(plan, initial_database, input, session_options, build)`.
It preserves all O02 states and thread/ownership rules. Its initial snapshot
has the real nonempty query result, while accepted input progress remains
zero with an empty source-position map. It is a new query initialization, not
checkpoint restore or source-offset recovery.

## Distinct construction methods

Both methods first insert complete source rows and visit compiled alias routes
in deterministic table/row/alias order. Exact derivation maps remain separate
per occurrence; filters/constants/repeated variables and physical projection
collisions use the existing F04 adapters. A positive native key contributes
one support seed even when several physical rows derive it.

`direct` constructs support without propagation transactions or event queues:

1. Populate native record tables from positive derivation keys.
2. Compute an iterative children-first postorder from tree edges.
3. Form each generalized record relation as the union of child P keys, using
   destination layout tokens. Child flags count presence, not multiplicity.
4. Probe child P keys for each record, compute its satisfied-child count and
   retain S exactly when every child is present.
5. Independently aggregate parent P and visible E projections from S, retaining
   their exact counters even when their schemas coincide.

Registered ReferenceTable inserts maintain compiled indexes. Constant true/
false routes retain their explicit semantics. No answer product is constructed.

`insertion_replay` processes the positive native seeds through private
sequence-zero R04 transactions and actual native/child-key queues. Each finished
seed's journal and pins are released immediately. Public apply/begin APIs are
not used with fabricated sequence numbers, and no published owner is reset.
This is an independent support construction path, not an alias for direct build.
Sharing source routing/checked scalar arithmetic is intentional; independent
fixtures also check expected adapters and answers rather than relying only on
agreement between the two builders.

Delta mode then bootstraps L and both parent/child separator indexes using
actual factor E relations, without enumerating query answers. Maintenance mode
retains no live image. Bootstrap does not use an output spool: a zero output
quota still permits initialization of a query with many answers.

## Work budgets and build metrics

`BuildOptions.work_limit` is cumulative across source validation/routing,
support construction/replay and live bootstrap. Rebuild additionally charges
its source snapshot before materializing tuple vectors and source sets.
Repeated enforced unique/FK key projections and referenced-table passes are
conservatively precharged before the reference validator runs. Metadata and
row-width checks are included. Ordinary support/physical/delta update caps
remain the caller's values and are not substituted for build limits.

The counter measures checked abstract operations and conservative precharges,
not wall time or every comparison/instruction. Ordered-map/set comparisons,
scalar payload widths and allocator costs remain separate. A low build budget
can stop before a later invalid-row/constraint error would be discovered.
Support and derivation limits still enforce their exact configured counters.

`initialization_metrics()` records the construction of that owner, not later
update history. Source rows, alias visits/rejections and derivation changes
describe complete source routing. Native/generalized/S/P/E/storage/index counts
describe final retained records. `replay_inputs` counts positive native seeds;
it is not the number of physical source rows. `replay_events`/`replay_work`
measure actual propagation. All three replay counters remain zero for direct
build. Live bootstrap work and actual L/parent/child row totals are separate.

## Rebuild and ownership

`rebuilt(build)` requires a writer-ready committed owner: pending updates,
read leases and unread delta output reject. It returns a distinct owner with
the same source state, committed sequence, current mode and caller options.
The original remains unchanged on success and failure. Callers choose when to
replace it using the existing nonthrowing move assignment.

The new owner has new backend/tuple identities. Old handles and pins still
refer to the original owner; they cannot silently address the replacement.
Owner-bound OrderedReplay cannot be switched implicitly. Rebuild does not
emit input/delta output or manufacture source progress. The next actual event
uses the preserved sequence plus one.

Retaining the old owner, native source snapshot, new owner and caller pins
creates temporary dual-state memory under the same original finite account.
The operational snapshot keeps compact rows and accounted capacity, sorted in
full-row order for deterministic direct and insertion-replay construction on
both backends. Work precharges precede snapshot copying. Budget/allocation
failure releases partial replacement and scratch state while preserving the
old owner. Public diagnostic Database exports remain a separate boundary.
Rebuild can compact arena history; complete S05 byte budgets and O04 persistence
semantics remain open.

## Canonical state and localized inspection

Canonical typed state contains physical-program/catalog/arithmetic identity,
source/logical sequences, source sets, per-occurrence derivations, node records,
child bits/satisfied counts/S and separate P/E counters. Delta state includes
actual mode, core/SQL view, L factors, both separator indexes with exact bucket
rows/counts, aggregate live totals and live sequence. E absent differs from E
present-but-empty. Owners, tuple IDs/generations, pointers, revisions, metrics,
pins and history/capacity are excluded. Sorted typed rows preserve all F01
scalar distinctions. Equality is for the same bound physical program, not a
cross-plan query-equivalence proof.

`inspect_invariants` reads actual storage and private metadata safely. It
checks missing/orphan entries, child presence and counts, generalized candidate
unions, S/P/E, source-derived alias counts, actual native membership and full
live/index contents. Parent/child bucket checks regroup observed L separately
from the top-down expected L calculation. A bad counter identifies component,
node/occurrence/table, typed key and expected/actual value where applicable.
It does not merely compare a rebuilt image or inspect a detached snapshot.

Diagnostics have independent cumulative work and issue limits. Exhausting a
limit sets `complete=false`; `issues.empty()` alone never proves validity.
Always use `report.valid()`, which requires complete inspection with no issues.
Healthy reports expose actual source/derivation/support/live/index record counts
and arena live-record reconciliation. Allocation failures propagate without
changing the inspected owner. Legacy throwing `check_invariants` remains a
compatibility convenience.

The separate testing runtime defines private probes only with
`CROWN_RUNTIME_TESTING`. Tests corrupt and restore actual satisfied-child, P,
E, derivation, parent/child bucket and aggregate live counters. Production
provides no mutation setter or mutable internal runtime reference.

## Diagnostic encoding and record-space bound

[IO diagnostics](../include/crown/io/inspection.hpp) provide deterministic
bounded UTF-8 JSON for physical/delta canonical state and invariant reports.
[runtime-diagnostic-v1.schema.json](../schemas/runtime-diagnostic-v1.schema.json)
defines structural version 1 with exact scalar tags and uint64 counters.
Embedded NUL is escaped; native byte strings that are not UTF-8 cannot be
represented in this JSON codec. Direct encoding uses no allocating JSON DOM
teardown during persistent OOM. Encoded-byte limits exclude caller state,
allocator capacity/slack and bounded scalar scratch.

A dump can describe deliberately corrupted observed state. Schema validation
checks shape and report validity flags, not semantic invariants. There is no
state reader/restore API, pointer serialization, source-position manifest or
checksum/durability protocol. This diagnostic is not a checkpoint.

Let N be total full source rows, including unused tables, and keep the verified
query fixed. Native keys per occurrence are at most source rows. A generalized
candidate belongs to a child P union, so its record count is at most the sum
of child P counts. S is a subset of records; P/E key counts are at most S;
L is a subset of E. Flags and registered indexes add fixed-query degree
factors. Parent-index row copies total parent L sizes over live edges; child
copies total nonroot L sizes. Hence maintained logical records/memberships
are `O_Q(1+N)`, independently of answer-product cardinality.

This bound covers counted records, not RSS or arbitrary payload widths.
Scalar bytes, descriptors, allocator/reserved arena metadata, initialization/
inspection scratch, old/new rebuild owners and caller-retained history are
additional. Arena high-water slots can outlive deleted rows; rebuild's new
owner can compact them. The scale fixture reports these separately, verifies
N-by-N answers without enumerating them, and reconciles actual arena/live
records instead of inferring a byte bound. S05 and the recovery/delivery/release
cards remain open.
