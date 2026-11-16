# Accounted compiled-plan storage checkpoint — 8 November 2026

S05 is **in progress**. New native `crown_accounted_plan_storage` builds
`AccountedPlanStorage`. Its public constructor borrows an actual opaque
`PhysicalPlan` and retains funded storage metadata, compact-value tables and
numeric mappings. It retains no original plan, source spans or standard Row
mirror. Actual maintained runtime adoption, complete IR/catalog/query ownership
and full native S05 acceptance remain open.

Frozen source is `build/verification/s05-accounted-plan-source-attempt-1/`
(883 files). The selected dependency graph compiles **77 actual C++ commands
from 68 distinct sources**, with 13 native libraries and 14 test executables.
Three memory profiles execute all **40** top-level checks, retaining the previous
38/36/31/26 populations. Eleven existing storage/actual compiled-plan regressions
are also selected. The real physical-backend-plan test calls the public opaque
plan constructor for reference/indexed and SQL-normalized plans, compares exact
scalar rows/IDs, index tokens, key/bucket order and sparse copies with the legacy
backend, and checks physical binding and shared metadata.

All four runs and their source/command/object/archive/link/test audits pass:

| Mode | Actual build seconds | CTest real seconds | Selected tests |
| --- | ---: | ---: | ---: |
| GCC Debug | 265.389 | 30.75 | 14/14 |
| GCC Release | 307.020 | 3.14 | 14/14 |
| Clang C/C++ Debug | 195.670 | 22.60 | 14/14 |
| GCC ASan+UBSan/leaks | 538.193 | 113.96 | 14/14 |

All compiler/test handles are closed. The accepted matrix is
`build/verification/s05-accounted-plan-matrix-accepted-v1.json`; current work is
in `build/verification/s05-accounted-plan-jobs.json`. Durations describe these
verification runs and do not assert a runtime speedup.

The new memory checks use a test-executable-only borrowed-description shim to
invoke the same native constructor implementation without linking the SQL
compiler into each memory profile. Production libraries contain no construction
shim entry points. Native private variants apply each forced collision mode
before registering compiled indices; the production constructor requires its
ordinary mode. The separate actual-plan test covers the opaque adapter.

Each profile persistently fails every observed constructor/copy position:

| Backend | Empty storage binding | Populated same-account copy |
| --- | ---: | ---: |
| Accounted reference | 26 | 56 |
| Accounted indexed | 29 | 68 |

All **179** positions preserve existing row addresses, logical IDs, storage
metadata and current purpose/lifetime byte partitions; each then retries
successfully. Temporary successful requests still affect historical counters.
Metadata aliases are preserved, while descriptor-equal distinct projection
tokens stay distinct. Controlled input descriptors are destroyed before frozen
storage is used. Pins keep required layout bytes charged after both original
and copy are destroyed, until their actual final release.

Metadata/instance/native-table/arena/input/controller reports reconcile with
independently observed actual requests. Cross-account move assignment allocates
nothing and releases the old owner's state. Five positive initialization work
domains pass exact and one-under admission; missing, oversized, legacy-diagnostic
and zero grants are rejected without an allocating diagnostic or replacement
allowance. Metadata compilation costs remain separate from ordinary indexed
path guarantees; no universal startup/delay bound is asserted here.

Measured simultaneous construction/population fixture peaks are **47,912**
requested bytes for reference and **51,066** for production indexed storage.
Testing indexed State adds eight bytes per table, giving **51,090** across three
tables. Exact-limit success, one-byte-under denial and a smaller-row retry pass.
These are scoped fixture peaks, including allocation framing/alignment and
construction overlap. They do not establish allocator usable size, RSS or a
complete runtime query cap. Earlier 91 reference/104 indexed/134 dispatch fault
positions, 44 work boundaries, nine component limits and differential/sparse
models remain in every full profile.

The real compiled-plan path also builds the pinned libpg_query dependency.
Runner v2 pins C and C++ drivers explicitly. Auditor v5 compares all **1,156**
extracted original parser files with the frozen archive, verifies the actual
make invocation/compiler configuration, **96** compile echoes and fresh C
objects, archive member bytes and sanitizer symbols. Upstream hides individual
C command lines; this make/source/object evidence is separate from the exact
record of all 77 native C++ commands. The parser source remains unchanged.

Root audits bind all native source/tool/command/strict flags/include roots,
fresh objects, archive member bytes and final links. Test-only controls remain
separate from production; each memory profile object/executable contains all
20 allocation hooks. The actual physical test receives exactly its frozen
source root as its sole argument. Successful complete JUnit identities and each
test's full verbose output are required, with retained shortened JUnit prefixes
checked against their complete profiles.

Evidence uses the `s05-accounted-plan-` prefix under `build/verification/`:
source/freeze attempt1, per-mode raw records/audit-v5 summaries/actual terminal
closures, reviewed collector and source-binding receipts. The historical
[dispatch record](memory-dispatch-2026-11-08.md), earlier optimized/reference
records and S04 source/matrix seals apply to their own immutable sources only.
Never compare those historical input maps with successor implementation bytes.

Root implemented/reviewed the code and owns execution. Luna Max only read the
dependency map; no new Astra was used. See the [memory contract](../memory_accounts.md)
and [handoff](../handoff.md) for actual runtime adoption and the full 78-card goal.
