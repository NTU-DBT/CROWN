# Durable plain SQL rows

`recovery::sql_rows::Session` joins the public nullable SQL-row runtime to a
local write-ahead log, signed-output sink and physical-source checkpoint. It
preserves plain `SELECT` bag multiplicities; it does not substitute an aggregate
query. `SELECT DISTINCT` and `EXISTS` use their own SQL presentation rules.
The implementation is being qualified under V04; this guide does not declare
an R2 release. The accepted R1 archive keeps its separate exact byte identity.

## Public objects and normal workflow

Include `crown/recovery/sql_rows_session.hpp` and link the installed
`CROWN::sql_rows_recovery` target. Bind SQL/catalog/typed parameters with
`frontend::bind_sql_rows_into` with
`SqlRowsBindOptions::retain_binding_image=true`, export its core for tree
selection, and pass the genuine program and checked tree to
`Session::create_into`. Ordinary in-memory binding leaves this flag false and
avoids retaining another copy of large parameter bytes. The canonical source
hash and selected binder work remain identical in both modes. An unrequested
`binding_image()` is empty; recovery codecs/descriptor admission reject absent
metadata before treating it as an identity. Descriptor admission
checks the actual immutable compiler/native metadata. A descriptor digest or
caller-edited core/tree DTO never replaces genuine runtime construction.
Minimum-height claims still need their existing independent planner evidence;
the session does not choose or certify a different default height policy.

Factories borrow paths and cold configuration during the call. The returned
owner retains the supplied memory account, genuine metadata, source/native
state, selected root, WAL/sink locks and live bounds. Use a fresh namespace for
creation; existing files are not silently replaced. Calls and borrowed views on
one owner must be serialized. Each query has an independent owner and files.

| Method | Usage and visibility |
| --- | --- |
| `create_into` | Create a genuine empty/static C0 owner with explicit runtime and output policies, a sink header and a selected initial checkpoint. |
| `log` | Own one complete physical net batch and prepay progress before syncing its Input record. It changes no SQL result. |
| `decide` | Prepare that same head, encode canonical signed SQL output, sync Commit, then publish native/source/progress state. An explicit semantic Reject advances input progress alone. |
| `output` | Borrow the one committed row-epoch frame awaiting local delivery. It expires on delivery or owner destruction/move. |
| `deliver` | Sync that frame to the actual sink, or confirm every byte of an already recorded epoch. Release the spool after receipt. |
| `results` | Read current SQL tuples with compressed exact multiplicities. A reader lease blocks mutation until terminal advance/cancellation/destruction. |
| `checkpoint` | At quiescence, capture physical source rows, publish matching descriptor/checkpoint/WAL candidates, then select one root. |
| `recover_into` | Rebind the selected descriptor, rebuild physical rows, replay the selected WAL and check actual sink coverage before repairing torn suffixes. |

`SourceReplacement` supplies a complete physical row and its expected before/
after uint64 weight. Repeated edits for one full row must form an exact chain.
Final source/key/FK validation and all alias effects belong to one private native
epoch. Filtered and unused physical rows still belong to source state. Successful
empty/no-op commands advance the committed sequence and have an empty sink epoch.

## Frontiers and failures

`SessionState` exposes four separate frontiers:

| Field | Meaning |
| --- | --- |
| `logged` (W) | Command sequence of the last synced Input. |
| `disposed` (I) | Last input with a durable Commit or semantic Reject. |
| `committed` (C) | Published physical/native sequence; Reject does not advance it. |
| `delivered` (D) | Physical sequence confirmed by the actual local sink. |

One owner holds at most one logged head and one committed output spool. Logging
another command requires W=I and D=C, with neither head nor spool. Reject can
make I greater than C. Reader/source offsets advance with disposition, including
Reject; JSONL byte/record progress stays distinct from C.

The semantic allowlist is weight mismatch, source-weight overflow, UNIQUE/FK
violation and annotation overflow. Preparation resource/contract failures never
become a fabricated Reject. They leave the same logged head pending, with no
native/source/progress publication. The genuine prepared token owns rollback.
The descriptor preserves the source/native policies and per-command output
limits. Recovery uses the supplied receiving account and SessionLimits for its
admission/rebuild, checkpoint/capture, file/generation, history/replay and repair
bounds. These receiving settings can differ on reopen without changing the
descriptor policy.

All native/output/progress storage needed for Commit publication is funded before
the Commit append. Publication uses the existing prepared token and prepared
progress node. The session does not add a second undo engine. File append and
repair failures require reopening. After checkpoint file mutation starts, one
fail-stop latch remains set until root selection and local owner publication
finish; uncertainty is resolved by reopening actual files, without per-stage
retry/catch machinery. Failed creation or unselected candidates can leave files
for inspection; creating a fresh owner never adopts those files by assumption.

## Prepared SQL changes

The lower public `SqlRowsRuntime::prepare_output_batch` explicitly requests SQL
output. Existing `prepare_batch` defaults and raw native bag previews retain
their meanings. A prepared SQL token exposes the number of changes and decodes
one indexed change into an exact-width caller scratch row. It borrows immutable
payload/constant strings instead of creating another owning SQL delta vector.
Scratch reuse or token closure ends those borrows.

| SQL presentation | Exact output difference |
| --- | --- |
| Plain bag | One consolidated signed uint64 magnitude per changed SQL tuple. Retractions above INT64_MAX remain exact; no signed narrowing/subtraction is used. |
| DISTINCT | Signed unit changes in membership, using explicit native support capture. Positive-to-positive counts still maintain numeric state but need no support-output walk. |
| EXISTS | Compare the full-root before/after presence. A change retracts the old Boolean row and inserts the new one; unchanged presence emits nothing. |

EXISTS current results always contain one Boolean row matching inner presence.
Empty named input gives FALSE at C0; a true static no-FROM query can give TRUE
already at C0. Sink epochs are differences from that actual SQL state, not an
implicit empty initial result. Consumers that need a baseline read the C0/current result under the
normal workflow before applying deltas.

The correctness argument uses the checked factorization in
[weighted enumeration](weighted_enumeration.md). For a native output assignment,
its multiplicity is the product of its visible factors; its support is the
product of their positivity indicators. Replacing one visible factor changes
support only on a zero crossing with all other compatible factors positive.
The existing anchor walk enumerates those assignments before factor publication.
Those private unit differences telescope through all stages; intermediate loss/
restoration cancels. No persistent result/support graph is required.

The genuine SQL compiler's payload/presence/constant mapping decodes the complete
native head into ordered SQL columns. Repeated columns and constants preserve
that mapping; canonical nullable encoding makes the admitted mapping injective
on native output assignments. The codec therefore sorts already consolidated
SQL rows and rejects duplicate packed keys. This is a local engineering argument
for the admitted checked fragment, not a new paper update/delay theorem.

## Costs and ownership

| Bound or resource | What it covers |
| --- | --- |
| Receiving `MemoryAccount` | Retained compiler metadata, physical/native state, undo, capture, frame/key/index scratch, pending Input and one output spool. Host/compiler workspace and process RSS retain their separate scopes. |
| Runtime source/native/index limits | Actual replacement/alias/kernel maintenance and native output capture. Existing policies, including explicitly disabled caps, are preserved. |
| `OutputLimits.rows` | Final consolidated SQL change count. It does not bound all intermediate traversal/consolidation or its peak memory. |
| `OutputLimits.work` | One row plus one unit per decoded SQL field, spent across all reads of that active token. Borrowed strings add no byte scan here. |
| Record/file limits | Codec byte visits, typed validation, packed-key sorting/serialization/hashing and bounded regular-file operations/scans. These have their own cumulative grants. |
| Replay limits | Commands and codec work across the selected replay; native preparations retain the original per-command policies. These are logical admissions, not preemptive CPU limits. |

The row encoder decodes each SQL change once into one accounted scratch row. It
retains packed canonical key bytes and small sort/sign metadata, then creates
the canonical frame before Commit. Native capture can visit/store intermediate
keys beyond the final net output. Byte copies, key comparisons, hashes and
cleanup are explicit preparation/output costs; no final-output-only delay or
zero-overhead claim is made.

Shared immutable program backing gives normal session updates a constant-time
binding identity check. Independently created genuine program handles use an
exact, charged binding-image comparison. The compiler retains its existing
canonical binding image only when explicitly requested for recovery. That cold
metadata storage/copy is accounted, and the descriptor's full image can overlap
it. Ordinary binding preserves its existing large-constant memory bound; the
source hash is unchanged by this retention policy.
Support capture and SQL preview add fixed policy/handle fields. Unrequested
capture allocates no output-capture buffers. There is no scheduler, network
worker, virtual output framework or full-state copy on an ordinary update.

## Files, replay and checkpoint identity

The row descriptor (`CROWNRD2`), record (`CROWNRW2`) and checkpoint (`CROWNRC2`)
families are distinct from aggregate/R1 state. They use the existing protected
length/body envelope and bounded binary helpers. File stages/limits and fixed
transport metadata are shared data types; typed row descriptors, frames,
WAL cursors, file owners, receipts and sessions retain their own authority.
The reused POSIX primitive takes an eight-byte framing magic and performs no
SQL/native interpretation.

Descriptor rebind checks original SQL/catalog/typed parameters through the real
factory, then compares complete binding/recipe/native identity bytes. It retains
the original source/native/backend policy and fixed output limits. Ordinary
checksums identify bytes; they do not mint native admission or a sink receipt.

Checkpoints contain complete physical rows/weights, command and physical
sequences, source/reader progress and actual delivery anchor. They contain no
joined-result/group/native-index mirror. Restoration validates framing, types,
canonical uniqueness and expected selected metadata before materialization, then
uses genuine whole-image rebuild for final source constraints and arithmetic.
Filtered, unmatched and unused rows are retained for the next update.

Recovery checks the selected checkpoint against its actual sink prefix. For each
selected-WAL Commit it prepares the real command, regenerates signed output and
checks both hash/length and actual recorded sink bytes where delivered. One final
undelivered Commit retains one spool; an earlier missing epoch cannot be hidden
behind another Input. It does not recompute every pre-checkpoint generation's
native history. Complete selected-root/native/output coverage and current file
identity/EOF checks precede either tail truncation. A complete pending Input is
preserved; only a validated incomplete suffix is repairable.

The default history cap is 128 absolute selected generations, with retained floor
one. Reopening does not refill it. Retirement and arbitrary external exactly-once
delivery are outside this workflow. Local idempotency confirms actual epoch
bytes under the sink protocol; it does not authorize another external service.
The existing [recovery/file premises](sql_aggregate_files.md) about regular Linux
files, cooperating advisory locks and namespace/fsync behavior still apply.

Use matching headers/libraries from one SDK build. The new support handle changes
fixed layouts; recompile consumers when moving to this SDK. Existing R1 frozen
artifacts remain intact. R2 compatibility/migration, independent numeric/SQL and
recovery tests, extended-report receiving and an extracted public SDK workflow
remain separate V04 release requirements.
