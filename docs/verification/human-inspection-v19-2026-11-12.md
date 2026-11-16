# Inspectable prepared source batches

This checkpoint has **11,307 source-pinned contracts in 8,952 blocks**, across
696 maintained code files / 161,315 lines / 18,093 mapped blocks. Every inventoried
line is structurally mapped. All selected production, root CMake, module,
example and tool scopes have authored contracts. Remaining selected manual gaps
are 4,201 test scopes. These maps support examination; they are not universal
semantic or execution proof. Start with the [source index](../code_specs/README.md)
and [primitive cards](../code_specs/primitives.md).

After [v18](human-inspection-v18-2026-11-12.md), this adds 78 contracts: 37 for
the source-batch API/implementation, one root cursor-type followup, 34 test
callables and six CMake commands.
It reconciles 45 existing SQL cards and all 1,261 existing CMake cards. Complete
command comparison preserves 1,259 bodies, modifies the one sanitizer list and
adds six registrations; the extra contextual card is updated too. Root further
corrects seven cost/ownership descriptions, including logarithmic node-insertion
comparisons and fixed status reads. Both review packets remain unchanged.
Adding the prepared token split the lexical header map and exposed one uncarded
ResultCursor type region. Root checked its unchanged complete declaration body
and supplied the missing ownership/lifecycle card; no native code changed.

The [usage contract](../sql_rows_batches.md) explains complete-row expected
weight chains, final-only caps, final touched UNIQUE/FK counters, all-alias
decreases before increases, borrowed/owning lifetimes and one retained native
epoch. No new production catch or second source undo framework is added. The
single-row preparation/publication and result-cursor bodies remain byte-identical.
Explicit token close now releases its backing native workspace immediately.
The new test fails against the preserved retaining implementation at the exact
workspace assertion and passes against current code.

[Final receiving checks](w06-source-batches-2026-11-12.md) pass all four SQL tests
in strict Debug and ASan/UBSan/leak profiles: 54.22 / 65.23 seconds. The new test
takes 0.78 / 3.28 seconds and exercises both backends, explicit result bags,
resource cuts, exact shared source work, retry, final constraints and ownership.
The complete test-disabled production Release build and moved installed strict
C++23 SDK consumer pass. All 326 predecessor test commands/properties remain
except source-line backtraces; sql_rows_batch is the only addition, making 327.
No full327-suite execution or Clang gate is claimed.

Actual old/new ordered Release probes preserve allocation counts, selected
source/native work and outputs across construction and five single-row cases.
Shared ownership adds a fixed 48 accounted payload/requested bytes, with facade
size 40→16. This is build-specific storage evidence, not CPU timing, a global
heap bound or a portable ABI guarantee. Enabled batch preparation still pays
for touched proposals, output consolidation, comparisons and teardown.

Root evidence: build/verification/w06-source-batch-implementation-v1. Its 29
terminal recorder jobs have no in-command source drift: 27 succeed, including
one explicitly excluded old-mtime no-op; two negative-control setup failures
are preserved and corrected. Final execution pins 1,132 maintained inputs.
Only the two existing SQL production files change from the 327-file v18
production inventory; the other 325 remain byte-identical. Build directories
remain active and reusable; frozen source and the relocated SDK are immutable.

Seal: build/verification/human-inspection-v19-progress-v1.json; frozen source:
build/verification/human-inspection-v19-source-v1. Earlier evidence closures
remain preserved. Root owns adoption, direct cleanup, cost corrections and
receiving execution; Luna Max supplies bounded test/block reviews. No new Astra
review was used for this component.

The aggregate-batch author proposal and independent static acceptance remain
separate. Root's private variant isolates four batch-only counters from legacy
records and passes its exact private Debug test, but is not adopted at this
checkpoint. Genuine compiler binding, group-only coordinated publication,
durable terminal outcomes, sessions/checkpoints/recovery and the operational CLI
remain W06 work. The full ledger remains 56 verified / two in progress / 20 not
started. See the [handoff](../handoff.md) for the concrete next step.
