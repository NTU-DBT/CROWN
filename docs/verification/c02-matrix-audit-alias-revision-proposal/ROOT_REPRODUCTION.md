# Root-only reproduction

From `/home/userroot/Codex/CROWN`, verify this packet's frozen FILE identity from
the parent message, then check repository-relative manifest rows:

```sh
c02_audit_package=docs/verification/c02-matrix-audit-alias-revision-proposal
sha256sum --check --strict "$c02_audit_package/PACKAGE_SHA256SUMS"
sha256sum --check --strict "$c02_audit_package/INPUT_SHA256SUMS"
sha256sum --check --strict "$c02_audit_package/source-files.sha256"
python3 "$c02_audit_package/audit.py" \
  --output build/verification/ranking-matrix-evidence-audit-attempt-2.json
```

The author has not executed Python, including syntax/bytecode checks. Root may
perform its own syntax check and execution after verifying the package. The
script starts no subprocess or project import and never polls jobs. It only
reads evidence and exclusively creates the requested new JSON and sibling log.

Exit 0 means all five complete matrix legs accepted. Exit 1 means an evidence
error, exit 2 means pending evidence, and exit 3 means unapproved allocation-only
differences. A partial result remains unaccepted even if its shell exit is ignored.
Preserve every attempt; never overwrite an old output. Release is the fixed
cross-configuration baseline. Missing/live other legs remain pending while
already terminal Release/clean evidence is examined independently.

If exact allocation-only differences require review, root writes a new designated
`build/verification/ranking-allocation-review-<name>.json`. It must name reviewer
`root`, decision `accepted_allocation_only`, the exact native/execution objects,
and entries containing each observed ID, a nonempty root reason and the exact
seven-field difference object. The included template deliberately has an invalid
decision. No old waiver table or broad compiler/allocation exemption is imported.
Then use a new output path:

```sh
python3 "$c02_audit_package/audit.py" \
  --allocation-review build/verification/ranking-allocation-review-attempt-1.json \
  --output build/verification/ranking-matrix-evidence-audit-attempt-3.json
```

The difference ID is SHA-256 of the sorted, compact JSON difference object. The
script recomputes it and requires exact matching contents, including comparison
kind/configuration/row. Only listed allocation counters may differ; all other
bytes remain exact. Approval entries not used by a complete matrix fail as stale.
Future or missing configurations cannot be accepted through advance approvals.

For final matrix authority root may choose a new canonical output
`build/verification/ranking-matrix-evidence-audit.json`, or bind an exact accepted
numbered attempt. Require both `accepted: true` and
`audit_state: accepted_final_matrix`, then bind the final ordinary source audit
to the auditor/freeze/raw pins and per-config names/outcomes/commands. Status-only
README/ranking/native-build edits are separate approved metadata changes; the
raw auditor pins frozen publication copies instead of mutable native status prose.
Never recheck any historical source-manifest entries after native application.
