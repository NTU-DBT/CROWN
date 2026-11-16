# Root-only preparation and invocation

This packet is frozen for root validation and remains unexecuted. The actual
execution-freeze/native/execution identities and the reviewed matrix field
contract are installed. Root owns all syntax, negative, preliminary and final
checks. The author runs no parser, checker, compiler, helper or test.

Exclude ongoing handoff, ledger, the evolving C05 evidence packet and current
`c05-native-root-jobs.json` from immutable INPUT rows. Final native status-guide
bytes also belong to their separate approval transition, not an old before-byte
INPUT requirement. Pin historical snapshots explicitly if needed. The runtime
audit reads and closing-hashes current metadata without freezing its lifecycle
in advance.

Preserve the exact actual `FREEZE_SHA`, `NATIVE.sha256` and `EXECUTION.sha256`
stated in `README.md`. The reviewed source-auditor body is
`ba1045e327b1f28a18b04895b7afabb03841184e31511f76dc15fe1ec1953197`.
The two future
root authority identities are explicit invocation arguments, not invented
constants or acceptance records written by this package. Pin exact
compiler/helper scope. Preserve the two unchanged upstream copies. Their
source difference remains directly reviewable without executing either file.

Hash frozen historical INPUT manifests as FILEs only. Never invoke their
checksum rows after native application. The current 764-entry predecessor
seal was already evaluated by the integration transaction; do not run that
check again. The C05 ordinary inventory is derived from current files and the
captured integration baseline.

After the meaningful isolated guard cases pass, root may use a fresh output
name for preliminary evidence with its already captured new C05 seal:

```sh
python3 docs/verification/c05-native-source-audit-proposal/audit.py \
  --seal docs/verification/selection-sources-preliminary.sha256 \
  --output build/verification/selection-source-preliminary-attempt-1.json
```

Missing final gates remain pending; an altered or unset freeze pin is an error. If a
matrix or completion-metadata authority already exists, pass its exact reviewed
FILE identity so the preliminary run can audit it. Do not delete a gate merely
to make it appear pending. Supplying an authority digest without its designated
FILE is an error; final mode requires both explicit digests.
The captured preliminary seal and its inventory receipt are immutable; retain
them when final status-guide hashes change. Separately named current C05
preliminary manifests under `build/verification/selection-preliminary-sources*.sha256`
remain available for isolated review cases. Final mode admits only the official
new seal.

Final invocation, only after actual terminal matrix and status-only metadata
review, uses the official new C05 seal and both explicit root authorities:

```sh
python3 docs/verification/c05-native-source-audit-proposal/audit.py --final \
  --matrix-authority-sha256 ROOT_REVIEWED_MATRIX_AUTHORITY_SHA256 \
  --metadata-approval-sha256 ROOT_REVIEWED_METADATA_APPROVAL_SHA256 \
  --output build/verification/selection-source-evidence-audit.json
```

Require exit zero, an accepted final receipt, zero errors/pending and stable
closing pins. Keep all global verification Markdown and current metadata
unchanged during this run. Retain both JSON and sibling log. Root may then
write a completion checkpoint that cites this result; the checkpoint is not
an input to its own acceptance. No command in this document has been run by
the author.
