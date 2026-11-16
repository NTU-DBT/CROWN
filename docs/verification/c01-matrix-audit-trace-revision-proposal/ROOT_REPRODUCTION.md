# Root-only invocation

Start at `/home/userroot/Codex/CROWN`. This package's author has not executed the
auditor or a Python syntax checker. First verify the frozen authoring identity:

```sh
c01_audit_package=docs/verification/c01-matrix-audit-trace-revision-proposal
sha256sum --check --strict "$c01_audit_package/PACKAGE_SHA256SUMS"
sha256sum --check --strict "$c01_audit_package/INPUT_SHA256SUMS"
sha256sum --check --strict "$c01_audit_package/source-files.sha256"
python3 "$c01_audit_package/audit.py" \
  --output build/verification/statistics-matrix-evidence-audit-attempt-2.json
```

The script reads only evidence; it starts no build, test, symbol command, helper
or project import. Exit codes are 0 for complete accepted matrix evidence, 1 for
an evidence error, 2 for pending evidence, and 3 for unapproved allocation-only
differences. Every written JSON has a same-stem `.log`. Existing output files are
never overwritten. A pending result must not be treated as an acceptance pass
even if the shell runner ignores the nonzero exit code.

Run checksum commands from the repository root: manifest row paths are already
repository-relative. Do not prefix them with the package directory. Preserve
`statistics-matrix-audit-launch-preflight-attempt-1.json` (which stopped before
execution), the original failed audit attempt 1, and its frozen package.
The revision changes trace classification/normalization only; it does not
approve or waive any numeric or allocation difference found by the next run.

If a terminal matrix/symbol record is not yet available, preserve that audit and
run a new numbered attempt later. Do not point this auditor at live process
handles or old O07 test summaries as substitutes for new C01 evidence. It uses
actual generated CTest registration order; do not impose the freeze's sorted
test-name order on LastTest execution.

## Allocation review

If `allocation_differences` contains an unapproved change, inspect its exact
before/after rows, test source and retained raw outputs. Review whether the
implementation/layout/compiler change legitimately alters only the recorded
allocation count. No semantic, budget, limit, output-cardinality or work change
can be waived with this record. The auditor identifies a candidate, not an
approved explanation.

After that separate review, root may create a new
`build/verification/statistics-allocation-review-attempt-1.json` with:

- `reviewer` equal to `root` and `decision` equal to `accepted_allocation_only`;
- the exact `native` and `execution` freeze objects;
- an `entries` array, each with the observed `id`, a nonempty root-written
  `reason`, and the exact `difference` object containing only `kind`, `test`,
  `configuration`, `baseline_configuration`, `row_index`, `before`, and `after`.

[allocation-review.example.json](allocation-review.example.json) is a shape
example with an intentionally invalid decision, not an approval. The script
recomputes each difference ID and restricts changes to recognized allocation
fields. Every distinct comparison needs its exact review entry. Old O07 numeric
waiver tables are not imported. When all raw matrix results are available,
unused approval entries fail as stale or misbound evidence.

Then run a new output attempt:

```sh
python3 "$c01_audit_package/audit.py" \
  --allocation-review build/verification/statistics-allocation-review-attempt-1.json \
  --output build/verification/statistics-matrix-evidence-audit-attempt-3.json
```

Release is the fixed cross-configuration baseline, so partial-run IDs do not
change merely because Debug finishes later. Missing Release evidence still
leaves cross-configuration verification pending. Approvals for configurations
that have not finished remain unapplied and cannot grant acceptance.

## Final binding

After all five terminal gates and all reviews pass, root may run a fresh final
output at `build/verification/statistics-matrix-evidence-audit.json`, with the
same review argument if necessary. Only `accepted: true` together with
`audit_state: accepted_final_matrix` qualifies as the final matrix evidence.
Bind the final source audit to that exact JSON/log hash, this frozen auditor,
the C01 freeze metadata, the per-configuration generated registration/outcomes,
and its `read_evidence_sha256` map. Do not overwrite a failed/pending canonical
record; choose another designated numbered path instead and bind that exact
accepted path.

The script never updates task status or goals. Root's independent source audit,
new ordinary seal, ledger/handoff and final acceptance remain required. All ten
historical native manifests are checked as files only, never revalidated entry
by entry against the C01 source tree.
