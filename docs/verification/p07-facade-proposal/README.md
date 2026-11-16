# P07 facade/cache implementation proposal

Status: isolated design proposal, 2026-11-07. P07 remains `not_started`. This
folder is not registered in any target, build, schema, report or public API.
It does not establish P07 acceptance or completion of the frozen P05 rerun.

`facade.cpp` defines the bodies in `../p07-api-proposal-2026-11-07.hpp` against
P06's existing `VerifiedOptimum`, the independent P02 `ValidationMachine`,
`../p07-generator-proposal/machine.hpp`, and
`../p07-key-proposal/key_machine.hpp`. The root-owned draft API is still a
proposal, not an ABI commitment. No production source, CMake, test, schema or
tool is changed by this folder.

## Authority, identity and lifetime

Admission requires a valid, already supplied original-query `VerifiedOptimum`.
It validates the supported context and any seed's exact serialized binding.
The provider exposes that proof before its first candidate, retains it after
cancellation, and never alters its certificate or original upper witness.
Every emitted alternative owns a separate independently P02-checked upper,
with actual native height equal to the supplied proof's height. A checked
lower height is an internal failure. A taller residual seed is filtered.
Invalid generator drafts are rejected; invalid supposedly checked seeds fail
explicitly. Structural tokens confer no proof authority.

The accepted context is exactly mixed-full-row-set-v1, exact-nonnull-v1,
crown-tree-v1, structural-height-v1, no-cost-v1 and structural-tree-key-v1.
The family is exactly exact-seed/residual-seed/normal-form-v1. Unsupported
values fail admission. No cost ranking or maintenance complexity guarantee
follows from this namespace.

Exact binding uses the existing core `io/query_binding.hpp` deterministic JSON
serialization, as explicit allocating admission work. Full bytes are retained
and compared; no hash-only matching or `crown_sql`/F05 dependency is introduced.
The core writer retains source schemas, metadata/constraints/statistics/hints,
types, names and positions, terms/constants/ignored columns, ordered/repeated
head outputs and aliases, and contradiction state. Its synthetic empty database
and empty updates are deterministic framing, not runtime data. There is no
alpha-remapping or proof transplant. A new provider always attaches its own
supplied proof, including when processing an exact-binding cached tree.

The ownership graph is acyclic. Immutable `InputData` owns only the original
proof, context, independent binding copy and binding bytes. It never owns the
live provider or a snapshot. The live provider separately retains optional
residual and cache seed holders. Exact and residual trees use aliasing shared
owners of their existing checked handles; cached seeds share the stored
candidate's actual tree owner. No tree is borrowed. New candidates retain
InputData, their newly checked upper, key and generation provenance. Snapshots
own immutable handle vectors and a copy of reuse diagnostics. Candidates and
snapshots survive provider destruction, cache eviction, clear and destruction.

## Saved stages and deterministic ordering

The order is exact witness, optional residual seed, each stored prefix
candidate in order, then a newly created normal-form generator. Every seed is
revalidated and recanonicalized; stored key bytes or prior P02 authority do
not bypass the gate. The first publication of a structural key owns the
primary provenance. Cached seed provenance is copied unchanged, including its
original sequence and residual trace. A distinct internal reuse ledger records
prefix index, original generation provenance, and the reuse outcome; aggregate
`cache_seeded` counts attempted cached seed admissions, including duplicates.
A cancellation may retain a pending reuse event as diagnostic history.

Stages separately save proposal counting, validator construction/steps,
completed height checking, key construction/steps, deduplication, vector
reservation, immutable payload construction, membership/publication, and
release. A validator/generator/key transition delegates exactly one saved
worker step. No blocking worker drain, repeated search, or validator restart
is hidden in a facade unit. Counters are checked before increments.

Deduplication uses complete key comparisons in an ordered container. Those
comparisons have an explicitly variable-width cost; this proposal makes no
constant-time or hard-deadline claim for them. Vector growth, allocation and
cleanup similarly have variable execution costs and are included in active
time during `advance`. Capacity growth itself is excluded from logical content
accounting.

Publication reserves the vector and prepares the payload before inserting
seen membership. Insertion has the standard container strong guarantee on
allocation failure. After successful membership insertion, publication uses
only a noexcept handle move into reserved storage and nonthrowing accounting.
An allocation failure retains the exact saved pending stage and previously
published handles. In particular, failed dedup insertion does not lose the
candidate or mark it seen. A full candidate cap stops at the saved reservation
stage; raising it resumes that pending publication.

Fresh providers explicitly regenerate the family from its start even when a
cached snapshot was exhausted. They never claim to resume its cursor or inherit
its exhaustion bit. Exhaustion becomes true only when this provider finishes
all admitted seeds and its own normal-form generator. It covers the specified
normal form plus the stored/admitted seeds, not all conceivable tree shapes or
cost-optimal plans. Snapshot creation is an explicit allocating operation
outside quanta and freezes the current prefix and actual exhaustion state.

## Resource semantics

Work and active-time totals use the existing continuation ledger; one attempted
unit is charged even when its allocation or resource preparation stops. Failed
units do not increment committed transitions. Each call returns after a new
publication, a stop or actual exhaustion. Limits are checked at transition
boundaries, so an indivisible operation may overshoot a time ceiling. Caller
pauses, admission, snapshot/cache operations and explicit cancellation are
outside active advance time. Negative time grants are rejected; zero work or
zero time leaves all progress untouched, including last-stop and counters.

Generator, key and facade share one cumulative `ContentBudget`. Generator
records/cells and key bytes follow their own proposal definitions. The facade
adds one record per worker shell, one record and one cell per reuse event,
one record per immutable candidate payload, and one record plus two cells per
committed seen-key/output-handle publication. Discarded attempts remain counted.
Existing owned seed trees are shared, not cloned or charged again. Content
stops and allocation failures retain their actual pending stages.

Explicit exclusions are admission copies/serialization and immutable input,
P02 scratch and checked-report storage, allocator/container capacity and scalar
width, caller-retained history, snapshot copies, and cache nodes/storage. These
are logical construction limits, not S05 bytes or a global memory bound.
Maximum retained candidates and maximum cache entries are separate. The logical
depth ceiling is passed to every delegated worker; diagnostics track the active
worker's actual saved depth, including stopped or throwing outcomes. A blocked
frame push never increases owned current/peak depth. These diagnostics are not
a sum of unrelated suspended workers' frames. Logical work/content/statistic
counter overflow is terminal. Active nanoseconds retain the existing saturating
diagnostic contract; saturation alone is not terminal, and finite total-time
ceilings remain enforced. Monotone limit changes never reset consumed counters.
Nonterminal cancellation allocates nothing, releases unpublished workers and
holders, and keeps published candidates, original proof and reuse history.
Cancellation is inert after failure or exhaustion, matching P06/P05; owner
destruction releases any remaining terminal-state scratch.

## Cache transaction

The bounded cache is an explicit single-caller owner. Lookup serializes the
supplied proof's binding and compares exact bytes and all context fields.
Matching height is checked defensively. Hits leave FIFO order unchanged.
Installing a replacement preserves its existing FIFO position; replacement
uses an already prepared immutable snapshot handle. A new entry allocates its
complete list node before nonthrowing splice/eviction. Failure leaves entries,
order and counters intact. Capacity zero disables installs. Cache operations
and snapshot ownership copies are explicit admission costs outside advance
units. `clear` empties entries but retains cumulative statistics.

## Review notes and validation boundary

No additional API change is required by this implementation. The root's
`const CandidateContext& CandidateProvider::context() const` refinement is
used. A later diagnostic accessor could expose the retained reuse ledger;
this proposal exposes only `cache_seeded` through the existing API. Sequence
values describe their original generation stream and are not globally unique
IDs across cache reuse. Public invalid/moved artifact getters throw; noexcept
facade progress and indexed candidate access report moved/empty states.

## Isolated runtime evidence (2026-11-07)

Root's additional [witness probe](witness-probe.cpp) starts from a real
singleton P06 certificate, changes its untrusted witness to an admissible
unary-generalized tree, and obtains a new checked `VerifiedOptimum` only
through public independent `CertificateReplay`. The provider preserves that
non-normal-form witness and its unchanged certificate alongside the normal
form singleton. Exact-binding cache reuse under a separately supplied proof
retains both upper trees but attaches the new provider's own unchanged proof.
The retained old handle survives cancellation/cache clear. Strict O3 direct
compilation and runtime pass; raw output is
`build/verification/p07-non-normal-witness-preflight.log`. This remains
excluded proposal evidence, not a native acceptance result.

The separate [seed boundary probe](seed-boundary-probe.cpp) passes with the
mandatory seven-/nine-atom P05 original minimum-three proofs and checked
residual seeds. A 70-occurrence/70-variable identical-scope query supplies a
real P06 minimum-one proof, publishes its checked seed and resumes two bounded
1000-unit enumeration grants without a fixed-width cutoff or false exhaustion.
Retained seed trees/proofs survive cancellation in all three cases. Strict O3
direct compilation and execution pass; output is
`build/verification/p07-seed-boundary-preflight.log`. No complete enumeration
of these large families is claimed.

The excluded `runtime-probe.cpp` obtains every `VerifiedOptimum` through the
existing P06 `ExactSearch` API and independently P02-validates every retained
candidate. It reuses the allocator fault machinery from the existing P05
exception-test source under a renamed main; that original test main is never
run. It is not registered in CMake, CTest, the CLI or the public API.

Direct strict compilation and execution passed at both `-O0` and `-O3`, linking
only the existing `build/release/libcrown_core.a` and excluded proposal sources.
No repository configure/build or CTest operation was performed. Observed checks:

- Boolean `R(x), S(x,y), T(y)`: P06 height 2; 3 unique independently checked
  minimum-height candidates after exact-seed/normal-form deduplication.
- Boolean equal-scope three-occurrence self-join over one unary table: P06
  height 1; 4 unique independently checked minimum-height candidates.
- Unit slicing and large grants produce the same keys, logical content,
  committed transitions and generation statistics. The original certificate
  remains unchanged and is available before the first candidate.
- Zero/negative quanta preserve progress. Depth, record, cell, retained-count,
  total-work and total-time stops resume after monotone raises. A full nonzero
  candidate cap preserves the first handle and pending later publication.
- Partial and exhausted cached snapshots replay their actual prefixes, preserve
  first-generation provenance, deduplicate seeds and run a fresh generator.
  A newly supplied same-binding proof remains the authority on new candidates.
- Renamed occurrence and changed catalog row-count metadata distinguish exact
  bindings; mismatched cached and residual seeds are rejected. All six
  unsupported context fields are rejected by provider/cache admission.
- Cache hits and replacements preserve FIFO position; clear retains statistics;
  capacity zero disables installation; a failed new-node allocation leaves
  entries and insertion statistics unchanged and permits retry.
- Published candidate/snapshot handles survive cancellation and provider
  destruction. Explicit cancellation succeeds under a persistent allocation
  failure, preserves the original proof/published prefix and clears current depth.
- Each optimization level swept all **2,369 observed advance allocation
  positions** on the Boolean path. Each failure was retried twice with the
  allocator still failing, preserving saved stage/content/committed state, then
  resumed on the same owner to the uninterrupted family and accounting.

`diagnostic-probe.cpp` additionally compiles the facade implementation into an
isolated white-box translation unit. Its test-only private-access macro changes
no public file. It injects only resource counters, never proof handles: every
proof still comes from P06. Both optimization levels confirm that saturated
`active_nanoseconds` alone is nonterminal, a finite total-time ceiling still
stops it, logical attempted/committed counter overflow is terminal, blocked
first pushes report zero owned depth, and a resumed frame agrees with the
worker's actual saved depth.

Reproduction from the repository root (replace `-O0` with `-O3` for the second
configuration):

```sh
g++ -std=c++23 -O0 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -Iinclude -Isrc/planner -isystem third_party docs/verification/p07-facade-proposal/runtime-probe.cpp docs/verification/p07-facade-proposal/facade.cpp docs/verification/p07-generator-proposal/generator.cpp docs/verification/p07-key-proposal/key.cpp build/release/libcrown_core.a -o /tmp/p07-facade-runtime-O0
/tmp/p07-facade-runtime-O0
g++ -std=c++23 -O0 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -Iinclude -Isrc/planner -isystem third_party docs/verification/p07-facade-proposal/diagnostic-probe.cpp docs/verification/p07-generator-proposal/generator.cpp docs/verification/p07-key-proposal/key.cpp build/release/libcrown_core.a -o /tmp/p07-facade-diagnostic-O0
/tmp/p07-facade-diagnostic-O0
```

Logs and source/archive fingerprints are saved under
`build/verification/p07-facade-runtime-2026-11-07/`. These are supplemental
release-library-linked proposal checks, not sanitizer evidence, a complete
independent family oracle, an exhaustive query/binding corpus, or native P07
integration/acceptance. No production implementation change was needed for
these checks. P07 remains `not_started`; the frozen P05 matrix and ordinary
source fingerprint controls remain root-owned.
