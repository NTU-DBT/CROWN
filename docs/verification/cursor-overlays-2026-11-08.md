# Cursor/view allocation ownership — 8 November 2026

S05 remains in progress. The full Refactor.md objective remains active: 41 cards
verified, three in progress (A02/S05/O06), 34 not started, 78 total.

## Actual maintained ownership

EpochView patches now use account-bound map/set nodes at every nesting level.
Restored full keys and projected index keys own compact AccountedRow copies.
Transparent RowView comparisons probe those keys directly, without standard Row
exports. Nested buckets are explicitly constructed with the same account;
operator[] cannot silently create an unfunded default-allocator map.

ResultCursor fixed assignments own each unique scalar in a one-cell AccountedRow.
String bytes are copied; inline scalar alternatives remain exact. Repeated
bindings compare borrowed ScalarView without retaining another value. Packed
key/scalar blocks retain tuple_values purpose; map nodes use cursor purpose.
All use the existing query account. Patch::memory() returns its account by value
because get_allocator() returns a temporary allocator.

Cursor fragment positions, first-field/outer maps, selected sets, variable/stack
buffers and direct-initialization postorder/stack scratch also use MemoryAllocator.
Empty outer maps have explicit account binding. Patch-array words consume the
original canonical native work grant before allocation; no budget is minted or
refilled. Native metadata/output descriptors remain a separate open boundary.

## Direct resource and lifetime evidence

The runtime memory test adds an 8,194-byte binary binding containing NUL and 0xff.
Its charged tuple payload grows by at least the byte length. The overlay fixture
uses the same binary key in both a restored complete record and its restored
secondary-index bucket, proving at least three owned byte copies are charged.

Measured Debug fixture peaks (requested upstream bytes, including account
framing) are:

| Fixture | Reference | Indexed |
|---|---:|---:|
| Four concurrent ordinary cursors | 35,573 | 39,372 |
| Long binary fixed binding | 36,429 | 38,962 |
| Before-side binary overlay | 131,062 | 127,790 |

Each exact peak succeeds; one byte below rejects. Failed binding startup restores
exact routed ownership, canonical state and lease count, then a shorter binding
succeeds. Failed overlay construction releases partial map nodes/keys while its
prepared epoch stays active. Explicit rollback under fail-every-allocation makes
zero allocation calls, restores the previous canonical state and admits a smaller
current view. Retained committed before-views, witnesses and completions preserve
binary ghost/direct lookups after temporary binding input and facade destruction.
Final owners release the query account to its controller alone; purpose/lifetime
sums reconcile.

Existing epoch/resource checks still preserve native payloads and pins while
allowing charged reusable table capacity, and require stable warmed churn. The
support sweeps retain all 110/124 upstream fault positions and integrated physical
sweeps all 126/142. Existing independent cursor, journal, support/join and rollback
oracles were not weakened. No executed checker or pinned report baseline changed.
These peaks describe specific testing-runtime fixtures, not production or whole
query peak guarantees.

## Scoped native verification

All **48 selected tests** pass in every configuration, with zero final compiler
warnings and the original sanitizer timeouts unchanged.

| Configuration | Selected names | Elapsed seconds |
|---|---:|---:|
| GCC Debug | 48/48 | 122.41 |
| GCC Release | 48/48 | 14.90 |
| Clang18 Debug | 48/48 | 93.83 |
| GCC ASan+UBSan/leaks | 48/48 | 511.54 |

This includes memory40 and the new resource cases, support models, journal/
prepared/epoch/result/fragment failure and lifetime suites, indexed budgets,
physical/delta/session/initialization/scale integrations, captures/observation,
original strict report checks and physical/support CLI fixtures. The actual
implementation stayed unchanged during this final matrix; documentation was
completed afterward. These are incremental live-source checks, not a fresh
frozen-source execution or full native/compiler acceptance gate.

Current records under build/verification use the s05-cursor-overlays prefix:
checkpoint/matrix/root-review/inputs/current-source-audit v1, immutable close
helper, selection-v1, raw build/CTest/full per-test outputs, original preimages-v1
and mutable jobs-v1. Continuation is s05-native-query-integration-next-v10.json.
All processes are closed. Root implemented/reviewed/executed; Luna Max supplied
only bounded read-only fixture/accessor inventories. No Astra was used.

## Full ownership and acceptance still open

Complete retained PhysicalPlan/catalog/query/tree/SQL/validation/identity JSON,
legacy layout/output descriptors and actual input-adapter ownership remain open.
Public get/result/snapshot/trace/child-flag and capture/diagnostic outputs,
delta/session/imported queues/output/rebuild/async state, compiled-operator
byte/record reconciliation and full native/source/compiler acceptance remain
required. The unused legacy work alias also remains. Keeping an unmeasured old
plan or declaring its retained graph external is not completion of this scope.
