# S05 native typed input ownership — 9 November 2026

Status: **in progress**. The full 78-card Refactor.md goal remains active at
41 verified / 3 in progress / 34 not started. Root implemented this checkpoint;
one existing Luna Max agent performed a read-only caller/test census. No Astra
was used. Use root for most work and reserve Astra Max sparingly. Artifacts live
in `build/verification/s05-typed-input-*`.

## Actual ownership and admission

Typed/windowed QuerySession constructs TypedQueue from its admitted CompiledProgram.
A thin crown_plan authority bridge supplies that program's existing account and
source-catalog alias, avoiding a core-to-plan dependency. Actual queue control,
intrusive batch/item owners, compact rows, source bytes/terminators and prepared/
committed/stopped progress consume the original finite grant. There is no
ordinary retained InputItem/Row/string mirror, accounting-only ticket or fresh
execution allowance. Legacy standalone queue construction has its own account;
offered TransportBatch construction remains an external DTO boundary.

Exact real-request preflight precedes copying. AccountedRow copying and sizing
share the same descriptor/string calculation; native byte totals include actual
batch/item framing. Import builds the complete private graph, reconciles the
current-byte increase and only then links it and empties the offered batch.
Full/OOM preserves caller ownership and all prior queue state. QueueStats bytes
now describe retained native requests; fixed queue/progress/catalog ownership
is additional under the same query cap. Batch DTO quotas retain their former
meaning. Destruction detaches long item/batch chains iteratively.

Stable InputItemView values expose native event/window rows. Envelope, shape,
type/decimal, field/source and sequence diagnostics retain reference order.
Permanent malformed-row issues can be retained as deferred diagnostics, including
valueless scalar/command variants, without keeping an unusable Row. They fail
only at the head. Semantic errors remain sticky; allocation failure and engine
rejection retain the same head for retry. Native validation renders decimal
lengths inline and uses the finite Date width, without ordinary formatting scratch.

InputPositions/AccountedInputProgress owns real controls/map nodes/key text under
session:2. Source nodes prepare before engine work; acknowledgement links them
or changes an offset without allocation. Value snapshots clone under the source
grant, with strong copy assignment. Moves/close/typed stop transfer storage
without allocation. Native accepted progress survives facade destruction; final
release leaves only the account controller. Session hot-path sequence checks do
not export a map; public progress/snapshot DTO exports are explicit caller boundaries.

## Source and verification scope

Source1 introduces the foundation; source2 wires native typed queue/progress and
view admission. Source3 completes direct test caller adaptation; source4 fixes
one misleading-indentation warning without relaxing flags. Source5 adds strong
outer progress copy assignment and actual memory/failure/late-diagnostic tests,
for 938 paths. Final source6 changes documentation only, for 939 paths.

| Configuration | Completed source5 scope |
| --- | --- |
| GCC Debug |213/213 full registered tests, 906.32s |
| GCC Release |37/37 selected checks, 16.40s |
| Clang18 Debug |37/37 selected checks, 99.88s |
| ASan+UBSan/leaks |37/37 selected checks, 528.05s |

Full Debug builds every target; other strict modes build the selected 37.
All accepted builds have zero compiler diagnostics. Complete stdout is preserved
before any subsequent registration/run, with no CTest enumeration overlap.
All 20 recorded jobs are closed. Progress-v2 binds exact sources,
raw attempts, current binaries, scope audit and handoff. Full compiler/sanitizer/
fresh-source/native acceptance remains separately open.

The actual typed_input_memory test reconciles upstream allocations against the
original account for construction, admission, head/progress staging and value
snapshots. It covers five scalar types, 38-digit decimals, long binary keys and
source names, spare DTO capacity, actual component bytes, zero-allocation full
rejection, exact/one-under query caps, caller-preserving denial and same-sequence
smaller retry, nonallocating ack/close, retained progress and final release.
Debug fixture batch requests are 118803 bytes; query peaks are 146695 reference /
147059 indexed. Persistent admission/peek/copy failures cover 10/2/3 positions
per backend. These are fixture measurements rather than universal peaks. Eight
malformed-event scenarios compare exact code/message/order with the unchanged
reference validator, including valueless scalars, type/decimal, envelope and
column-limit precedence, without changing prior committed state.

Three existing tests have only six native view type-name substitutions. Exact
whole-file reconstruction preserves every other byte, assertion and independent
DTO/reference algorithm; syntactic audit alone is not semantic proof. Eight
existing semantic/failure checks pass before the broad suite. The raw initial
formatting compile failure and source preimage stay immutable. No old test rule,
frozen schema/CLI verifier, prior source map/raw receipt or executed helper changes.

## Remaining work

Streaming EventReader controls/options/fingerprint/wire buffers/lexer/parser/
delimited cells/cached InputEvent/progress remain ordinary. The footer explicitly
distinguishes that legacy stream state from native typed progress. Nested session
run-context input options, retained observation/cursor/workload settings, capture/
report/diagnostic/invariant-checker/asynchronous graphs remain incomplete.
Authentic operator record/byte reconciliation, full overflow/no-op/churn and
compiler/sanitizer/fresh-source native matrices are still open. The
9-file 248-candidate next-owner inventory includes
funded aliases and explicit external/compiler DTOs and is not exhaustive proof.
S05 and whole-query memory acceptance remain **false**. See [handoff](../handoff.md),
[memory contract](../memory_accounts.md), [typed/window guide](../batches_windows.md)
and [ledger](../task_ledger.md).
