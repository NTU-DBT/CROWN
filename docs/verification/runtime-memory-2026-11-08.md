# S05 actual runtime owner and metadata adoption (in progress)

Historical owner/metadata checkpoint. The successor
[compact physical source evidence](compact-sources-2026-11-08.md) describes current
source storage, work views and added coverage. Do not apply this older source
binding or byte observations to successor implementation.

S05 and the complete 78-card Refactor.md goal remain active. Root implemented,
reviewed and executed this scoped migration of the maintained runtime. One
focused Astra Max read-only architecture review completed; no implementation or
execution was delegated. The user asked to reduce Astra Max usage and rely more
on root.

## Change and scope

Actual Support/Physical/Delta construction and session forwarding now use one
finite account independently of indexed work. Rebuild shares the original account
across old/new state and receives a separate target work context. Implementation
controls, indexed leases/grants, and support record/counter/flag/queue/undo arrays
use actual accounted requests. Saved flags and extracted nodes keep compatible
immutable allocators. Undo restores the original ownership without allocation.
Privately generated metadata IDs use a separate authority and preserve the
existing public runtime-owner sequence.

The [contract](../memory_accounts.md) describes the migrated ownership and gaps.
Legacy PhysicalPlan, standard tuple/table payloads, public outputs, delta/session
collections and complete operator reconciliation remain open. Map lifetime
classification uses the existing O(outstanding account allocations) ledger
search. No uniform runtime speed or delay is claimed. Requested ordinary-new
bytes exclude RSS, allocator usable size, exception-runtime storage and all
allocations still outside the account.

## Validation

All **16 selected tests** pass in GCC Debug/Release, Clang18 C/C++ Debug, and
GCC ASan+UBSan with leaks. Final CTest times are 30.50/11.94/26.35/102.42 seconds.
The set includes the existing 40-check compact-memory fixture, new actual-runtime
memory checks, existing support/physical/delta allocation-failure suites, session,
aggregate indexed work, and six observation/strict report checks. Builds reuse
existing directories incrementally; this is not a fresh full native suite or
complete compiler-command audit. Full S05 acceptance remains open.

The new fixture observes routed support peaks **10,383 bytes reference** and
**10,757 indexed**. Exact limits commit; one byte less restores the previous
populated epoch and current routed ownership, followed by a successful valid
retry. It persistently fails every **116 reference / 127 indexed** allocation
position on real propagation and checks successful retry. It also checks
allocation-free rollback, retained cursor/journal controls through final release,
shared account identity and old/new rebuild overlap, session forwarding,
nondefault configuration/trace round trips, and 40 no-op/churn cycles for each
backend. These are fixture-specific routed peaks, not complete query peaks.

Original strict report checkers and pinned v2 legacy bytes pass unchanged.
Custom memory limits are emitted explicitly; the default remains implicit in
existing report formats. Schemas admit that optional setting.

## Preserved failures

The initial build used old allocator-specific map parameter types in three
lambdas; all were corrected. The initial memory test compared current bytes
before an inert pending token released its still-owned indexed lease; comparison
now occurs after token destruction. Initial strict report checks exposed changed
default v2 bytes; conditional custom-limit emission restored compatibility.
A later 15/16 run exposed the real public-owner regression (owner 2 became 4)
when metadata consumed the public sequence. The separate metadata authority fixes
that regression. Failed logs, successive source preimages v1–v5, and retained
/tmp artifacts are listed in the jobs record; none were overwritten.

## Receipts and continuation

Under `build/verification/`, `s05-runtime-owner-matrix-v1.json` pins the final
16-test outputs and selected executables. `s05-runtime-owner-tested-inputs-v1.json`
records 886 maintained inputs excluding mutable handoff; the final source audit
allows reviewed documentation changes only. This is a post-run live-source
binding, not execution from an independently frozen source tree. The scoped
checkpoint, root review and current-source audit record those limits explicitly.
`s05-runtime-owner-jobs-v1.json` is the mutable job record. All build/test handles
are closed.

Next: freeze the runtime program using existing accounted storage tokens, adopt
compact tables/values in the actual support/physical paths, and release retained
legacy plan data. Then finish remaining delta/session/imported queues/outputs,
operator reconciliation and complete native S05 gates. The full 78-card scope,
A02 licensing disposition and all other open cards remain required.
