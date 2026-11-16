# W06 complete physical checkpoint — 2026-11-13

The [checkpoint API and wire contract](../sql_aggregate_checkpoint.md) now have
scoped receiving evidence. It preserves all original nullable physical bags,
including filtered and unused rows, and restores through the genuine whole-image
factory. Actual R2 WAL/sink owners, durable coordination/replay, nullable JSONL/CLI
and varying-int32 admission remain open. W06 and the full goal stay in progress.

## Implemented behavior

CROWNAC2 version1 binds genuine descriptor identity, query/generation, runtime C,
command I, delivery-anchor data and optional reader position. C≤I allows semantic
Rejects without a physical epoch. Sorted source positions and complete positive
nullable physical rows retain the original schemas and empty-table identity.
The codec rejects duplicate full physical keys, malformed/foreign rows, zero or
out-of-domain weights, unsupported framing, damaged digests and trailing bytes.
C0 is empty physical data; authentic static/global state initializes once.

Encode authenticates the source carrier against the genuine original/source/
native/weighted binding. Editable snapshot data does not prove constraints or
arithmetic. The genuine cold factory validates those before exposing the restored
runtime. Restore checks complete expected metadata before receiving allocation.
This comparison is data validation; actual root selection and sink acknowledgement
still require genuine durable owners. A delivery DTO is not a receipt.

Cold canonicalization uses one packed key buffer and an index vector. The packed
buffer dies before final-frame allocation; the index vector remains during write.
Inspection uses fixed/transient borrowed data. Materialization reuses one Cell
vector and owns each physical tuple under the receiver. Those temporary tuples
overlap rebuilding live state, then die before return. Returned runtime and source
positions survive the input frame and producer. Codec passes share one work
budget; genuine source/native/indexed/group construction uses separate finite
build grants. Selected work is not all CPU or a memory-byte count.

There is no new production catch, ordinary-update field, retained source mirror,
per-row allowance refill, second rollback mechanism or runtime framework.

## Receiving gates

| Gate | Result |
| --- | --- |
| Strict GCC C++23 Debug | Selected 8/8, 120.65s |
| Full ASan/UBSan/leak profile | Same 8/8, 243.39s |
| Complete OFF Release | Pass |
| Relocated 224-file public SDK | Full copied maintained checkpoint test passes in strict Release |
| Additional installed consumer | Producer/compiler/descriptor/frame/source payload destroyed; C/I and UTF8 positions survive; next exact removal; both receiving accounts balance |
| Registration continuity | All previous 336 commands/properties exact except backtraces; 339 registered |
| Existing binary artifacts | 20 existing archives, entire native runtime archive and CLI binary byte-identical; only upper recovery archive changes |

The selected tests are normal SQL aggregate oracle, physical rebuild and its
oracle, R2 records/descriptor, checkpoint unit, independent wire and checkpoint
oracle. Each SQL mode uses the actual DuckDB 1.5.4 oracle: 99 cases, 198 backend
requests, 3,436 atomic epochs and 3,634 snapshots per profile, with AVG scales
0–18. The checkpoint mode serializes/restores after every epoch, including C0:
3,634 actual checkpoints per profile. It compares current snapshots and subsequent
raw changes against independent SQL. Varying-int32 columns remain excluded.

The independent Python wire test constructs all 611 expected bytes and checks
the complete frame, SHA256
`472844b8dcc516b11f251e1e827ce6c25902adeb64ea51b9f0bdf123a58eeece`.
The unit covers both backends, complete NULL keys, filtered/unused bags, C/I,
source/reader positions, next updates, terminal sequence, static state, exact/
one-under codec/receiving limits and checksum-valid hostile data. Byte equality
and actual semantic cold reconstruction are distinct checks.

No full-339, Clang, actual durable recovery or CPU speedup acceptance is claimed.
The unchanged archives establish code continuity, not a latency measurement.

## Evidence and review

Root packet: `build/verification/w06-r2-checkpoint-implementation-v1`.
All 23 recorder jobs are terminal, 21 successful, zero in-command source drift;
the current map has 1,167 native inputs. Two original failures remain: a test-only
first-NULL array initializer, and the first private SDK probe retaining its output
Epoch while expecting the receiver account to be alone. A fresh v2 consumer/build
closes that owning Epoch before checking balance; production code did not change.

Four maintained code files are new: checkpoint header/implementation/unit and
Python wire oracle. Existing executable changes are confined to CMake and the
mature SQL driver/oracle's optional checkpoint mode. Three old test files have
six exact wording substitutions: ordinary-global-new interception replaces
overbroad allocation claims, and rollback-restored tuple IDs replace copied-state
wording. Source preimages and exact substitutions are retained; those tests'
nonliteral executable tokens are unchanged.

The independent static review is sealed at
`build/verification/w06-r2-checkpoint-review-v1`, manifest SHA256
`46bf1cfc899e5e2e4e03d2092e2a0d93984d2183f1b111836c97904b4c4facf8`.
Root rechecks every manifest payload and the three current source pins. The
reviewer found no outstanding blocker within the checkpoint component; it ran
no native tests. Luna Max authors separate human-contract packets, and root
verifies their source/anchor/reference projections before adoption. No Astra call
is used. P1 §7.3 supplies weighted context only; see the
[corrected source map](../code_review.md).
