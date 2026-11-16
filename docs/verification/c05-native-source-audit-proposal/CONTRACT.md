# Source-audit contract

## Current ownership and historical FILEs

The applied integration receipt is
`build/verification/c05-native-integration-start.json`, SHA-256
`9f8824f17f90bf6c1cc8caf89d3abc66adedd0083e38b88fcc8a11b944be66e0`.
The accepted staged receipt is
`build/verification/c05-publication-stage-build-attempt-1.json`, SHA-256
`38ce409eca1d52cffcf5d3478f7fdc8820135822ed6c611146e5d5bffdf60479`.
The actual execution freeze at SHA-256
`affcb8fa29b193e57f9501c5a88054eaba9467b7040273f36f28c507f3146711`
binds both. Stage evidence remains scoped to its
24 fresh compiles, three archives, 15 links and 15 new tests; it does not replace
the full native matrix.

The integration's `baseline_entry_pins` provides 764 ordinary path identities
captured before copying. Its one additional prior-seal FILE entry is excluded
from the ordinary set. Exactly 31 mapped destinations are new, exactly three
replace existing files, and no baseline path may disappear. Unmapped current
bytes must match that captured baseline. Every mapped source must still match
its recorded applied bytes. No nested `manifest_input_pins` entry is replayed.

After application, all twelve historical source seals are hashed as files only.
Historical package INPUT manifests may also be hashed as files, but their rows
are never interpreted as current native checksums. The only parsed current
seal is `docs/verification/selection-sources.sha256`, the exact new root capture
`docs/verification/selection-sources-preliminary.sha256`, or an explicitly named
`build/verification/selection-preliminary-sources*.sha256` file. The root capture
and its inventory receipt have exact FILE pins. Symlink or
historical-seal substitutions are rejected before parsing.

The active patched JSON header must remain
`f763c58b102e65242d09275aec4b2f343268280ab4587b15587ad143b2e2a406`.
C05 changes no vendor header, schema, JSON wire format or licensing disposition.
The fresh native/execution per-file inventories also cover that boundary.

## Freeze and accepted matrix interface

The captured `selection-execution-freeze.json` retains the C02 structural
fields: `native`, `execution`, per-file maps, expected test names/order, old
legacy order, expected compile units, predecessor toolchain caches and root
execution helpers. The C05 additions are `added_compile_units` (24),
`symbol_roles` (12), `stage_receipt_sha256`, `immutable_publication_file_pins`
and `manifest_file_pins`. The last two maps are FILE-only inputs.
Its 158 unique ordered names must agree with its sorted inventory and preserve
the exact 143-name legacy prefix. The 238-entry count, five configuration names,
and stated incremental/clean expectations are checked independently of whether
a matrix receipt is already present.

The independent final matrix receipt and its root authority use the
`selection-matrix-*` namespace. The explicit root authority SHA is supplied
at invocation. Its `canonical_matrix` must identify the exact accepted receipt,
and its auditor/package FILE identities must close over a complete immutable
auditor package. No completion checkpoint is an input to this source audit.

Require all five actual configurations, all 158 ordered passed outcomes, exact
raw command bindings, and numeric rows derived from every test's retained
output. There is no inherited 1090-row total. Every allocation difference must
have its exact applied root approval and no unused or unresolved approvals.
The C02 decision `612f174c...` covers only its four exact historical Clang rows;
it grants no approval to any new C05 row or future counter difference.
Every underlying summary must be terminal, passed, exit zero and source/identity
stable for the exact freeze. Every symbol receipt must be terminal, captured
and exit zero for that freeze; a complete-looking row list in a running or
failed receipt is insufficient.

Each configuration must expose 238 target/source entries, 14 runtime units per
variant, six report units per variant, three pure ranking units, one ranking
bridge per variant, five pure selection units and one selection bridge per
variant. Ranking and selection example objects have no link recipe. The
12 archive roles are plan, planner_testing, ranking, ranking_runtime,
ranking_runtime_testing, runtime, runtime_testing, explain, explain_testing,
selection, selection_runtime and selection_runtime_testing; sanitizer parser
undefined-symbol evidence is an additional capture role.

Dependencies use neutral `actual_recompiled_units` and
`unchanged_units_not_recompiled` fields. Their disjoint union must be all 238
units and match the observed compiler commands. The reviewed incremental
expectation is 24 fresh new units and 214 unchanged predecessor units; clean
source must establish all 238 fresh. An unexpected partition needs explicit
review, not an assertion that cached units were newly compiled.

For cached units the coordinated matrix interface includes
`cached_predecessor_provenance`, with `status: audited_pass`, `unit_count: 214`,
the exact capture FILE record, and true `object_bytes_equal_to_capture`,
`normalized_compile_argv_equal` and `frozen_project_dependency_bytes_equal`
results. Its `historical_system_header_bytes_compared` and
`historical_generated_header_bytes_compared` fields must both be false.
The capture is `c05-c02-predecessor-build-evidence.json`, SHA-256
`b21d69747ea69f0a7d7d86ffd9c372dc47eee5020ee4f0e386a5b45cc1616561`.
The matrix auditor must establish those results from exact per-unit retained
object, command and project-dependency pins. Current generated/system input
observations are separate: the C02 predecessor did not hash their historical
contents, so these fields cannot claim that history. This source auditor binds the reviewed
matrix and every raw input; the booleans alone are not an independent proof.
The independent matrix author confirmed this field shape. Source review of
the actual emitted fields matches this contract; runtime validation of the
actual receipts remains root-owned.

The C05 clean adapter directly retains all 238 `.o.d` files and metadata before
cleanup. It records `included_inputs` references per unit and unique
`dependency_inputs` with `snapshot_source`, `generated_build` or
`external_system` scope. Generated inputs have retained byte copies; source
inputs bind frozen execution files; external inputs are current observations.
Its post-test snapshot and actual-input guards must pass before cleanup.
Do not require or reuse the C02 214-row watcher sidecar. Helpers and
compilers remain mandatory exact FILE pins. Canonical internal Clang aliases
stay internal; only the exact observed canonical external files belong in the
root's external whitelist. Conflicting alias hashes fail.

## Documentation, status and final authority

Apply Markdown publication projection only through the captured C01, C02 and
C05 integration mappings. Frozen overlay documents are checked against their
original applied bytes, while their local links resolve from the actual native
destination. All ordinary Markdown, handoff/ledger and every verification
Markdown document participate, including the new in-progress C05 evidence
packet. Native local schema references and documented schema path mentions
remain checked; external resources and fragment anchors are not fetched.

The baseline is exactly 39 verified, three in progress (A02/O06/C05), and 36
not started. Final C05 completion changes only C05: 40 verified, two in progress
(A02/O06), and 36 not started. Both parsed rows and explicit current totals must
agree. Historical handoff sections are not reinterpreted as current status.

The current progress registry is `c05-native-root-jobs.json`. It is read and
closing-hashed as progress metadata, not as acceptance authority. The older
`c05-selection-root-jobs.json` stays immutable at
`286a1350f919811805f73c1c039c6183eb2a59dceffdf2722b50655f454fd3d7`.
The current registry, ledger, handoff and evolving C05 evidence packet must
not enter this package's immutable INPUT manifest. Immutable historical
snapshots may be inputs; current metadata is bound by the final invocation
and its explicit approval, with a temporary root-coordinated hold.

Final ordinary-byte changes are restricted to status-only edits of `README.md`,
`docs/native_build.md` and `docs/selection.md`. Root must explicitly classify
each change, pin before/after bytes and retain its exact diff in
`selection-completion-metadata-approval.json`. The approval's exact SHA is an
explicit invocation argument; the auditor does not infer prose semantics.
Both other selection guides remain unchanged.

Preliminary mode always remains unaccepted. Final mode requires the official
new seal, accepted full matrix, exact metadata approval, C05 verified ledger,
matching registry status, final evidence citations, and closing source/Markdown
inventory guards. Root writes the completion checkpoint afterward, avoiding a
circular final-acceptance dependency.
