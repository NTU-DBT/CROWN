# Native memory/storage migration checkpoint — 8 November 2026

This is the historical frozen reference-storage checkpoint. The successor
[accounted optimized record](memory-indexed-2026-11-08.md) describes later
implementation and verification; the statements below apply to this packet's
own source and execution evidence.

S05 is **in progress**. This packet verifies the native allocation/metadata/arena
and accounted reference-table journal foundation. Actual runtime facade/value
binding, optimized storage allocation, complete plan/query ownership and full
native S05 acceptance remain open. The complete 78-card objective remains active.

The production `crown_core` CMake target now compiles the new implementation.
Immutable input is `build/verification/s05-native-storage-source-attempt-2/`
(864 staged files). Four fresh selected builds compile 54 actual C++ commands
from 50 distinct sources each. All 11 selected CTests pass in each mode: the
new memory-account fixture with 31 top-level checks, plus 10 existing layout,
arena, reference/journal and indexed-facade/collision regressions.

| Mode | Actual build seconds | CTest real seconds | Selected tests |
| --- | ---: | ---: | ---: |
| GCC Debug | 90.861 | 29.17 | 11/11 |
| GCC Release | 108.413 | 2.74 | 11/11 |
| Clang Debug | 78.211 | 21.13 | 11/11 |
| GCC ASan+UBSan/leaks | 154.159 | 106.99 | 11/11 |

Test durations describe this verification run; they are not a runtime speedup
claim. GCC 13 and Clang 18 compiler/driver identities, all helper/tool inputs,
source bytes, raw commands and terminal receipts are pinned in the execution
freeze and accepted audits.

Root audits compare the actual complete selected dependency commands with the
configured database and exact strict flags/include roots. GNU archive member
bytes, including duplicate basenames, match the fresh objects. Final test links
use only their actual selected objects and native archives. The five production/
testing archives contain no allocating replacement global new/delete hooks;
the new test object and executable contain all 20 expected replacement hooks.
One arena and one storage-owner authority serve legacy and accounted owners.
Sanitizer builds instrument every selected unit/archive and test link, with
actual address/undefined/leak-check environment in verbose test output.

All 26 source8 foundation checks remain, with five new native table/ledger
checks. Native table results independently agree in all four modes:

| Operation | Observed allocation positions |
| --- | ---: |
| Insert, including existing/new secondary buckets | 11 |
| Build another secondary index | 7 |
| Erase one handle | 6 |
| Erase a complete secondary bucket | 12 |
| Insert through an existing journal | 15 |
| Erase through an existing journal | 4 |
| Owning snapshot collection | 3 |
| Independent table copy under the same account | 24 |
| Owning key collection | 2 |
| Owning bucket-handle collection | 2 |
| Live cursor | 1 |
| Journal reader/control | 2 |
| Another table State/control and arena | 2 |

The erase-key and bucket-handle fixtures include construction of their
accounted lookup key. The constructor fixture creates a second table under an
already prepared account. Allocation positions describe these complete fixture
operations.

Each of the 91 positions is failed persistently. Failed operations preserve
previous row addresses/IDs and index membership, release temporary allocations,
restore current purpose/lifetime partitions and retry successfully. Recovery
performs no ordinary new allocation. Actual allocation histories still record
successful temporary requests. Two-record preparation and third-row insertion
have a measured fixture peak of **38,972 requested bytes**. Exact-limit success,
one-byte-under rejection and a smaller-row retry pass. This measurement includes
controlled metadata/input setup and overlapping preparation blocks.

The 256-step model compares membership, row hashes and key census with the
existing independent standard-container reference table. Slot metadata is bounded
by five in that fixture. Replacement chains restore old addresses, original
pinned generations and committed ID counters; separate committed histories
release independently. Retained pins, outputs, journals and weak cursor controls
remain accounted through final release, including an active writer outliving
its table facade. Diagnostic and final teardown paths allocate no bookkeeping.

These measurements cover actual ordinary operator-new requests, including
controlled allocation framing and alignment. They do not establish allocator
usable-size, RSS, exception-runtime storage or a complete runtime query cap.
The retained nested-string coverage-gap witness remains explicit.

Authoritative local evidence:

- `build/verification/s05-native-storage-matrix-accepted-v1.json`
- `build/verification/s05-native-storage-execution-freeze-attempt-2.json`
- `build/verification/s05-native-storage-{debug,release,clang,sanitize}-attempt-2-records/`
- Matching `-audit-v1/summary.json` and actual `-terminal-closure.json` records.
- `build/verification/s05-native-adoption-preimages-v1/`

Executed helpers, source1's earlier passing native Debug run and the source8
component checkpoint remain preserved. S04's 199-test five-mode matrix/source
seal is historical as-of evidence. Its predecessor source/INPUT entries must
never be tested against successor native code. No new Astra was used; Luna Max
only mapped native facade type boundaries. Root implemented and verified the
new native storage. See [the contract](../memory_accounts.md) and
[handoff](../handoff.md) for remaining scope and continuation.
