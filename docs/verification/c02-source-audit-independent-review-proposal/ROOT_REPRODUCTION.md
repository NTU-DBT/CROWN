# Root-only reproduction and authority records

The reviewer has not run Python, including syntax/bytecode checks. First verify
the package FILE identity from the parent message, then its repository-relative
rows. `INPUT_SHA256SUMS` contains current frozen execution files and immutable
evidence FILEs; it does not evaluate any historical source-entry manifest.

```sh
c02_source_review=docs/verification/c02-source-audit-independent-review-proposal
sha256sum --check --strict "$c02_source_review/PACKAGE_SHA256SUMS"
sha256sum --check --strict "$c02_source_review/INPUT_SHA256SUMS"
python3 "$c02_source_review/source_audit_revision.py" \
  --seal build/verification/ranking-preliminary-sources.sha256 \
  --output build/verification/ranking-source-preliminary-audit-attempt-2.json
```

The preliminary seal above is suitable only while its recorded current bytes
remain unchanged. Preserve every output; use a fresh numbered path for each run.
Exit 1 means errors; exit 0 can still mean a preliminary result with pending gates.
Acceptance requires both `accepted: true` and `audit_state: accepted_final_source_seal`.
The helper uses the standard library, imports only the exact hashed predecessor
utility module, and calls its pure inventory/link/schema/table functions. It never
calls an old audit entry point or starts a subprocess. Imports are argparse,
collections, difflib, hashlib, importlib.util, json, pathlib, re and sys. Bytecode
writing is disabled before the pinned utility import.

For final invocation, root supplies the reviewed FILE SHA-256 of
`build/verification/ranking-matrix-audit-authority.json` through
`--matrix-authority-sha256`. That record must include:

- `reviewer: root`, `decision: accepted_evidence_only_auditor`, and the exact
  current `native`/`execution` count/hash objects;
- `auditor` and `package_manifest`, each with an exact path and SHA-256; the
  auditor must be a member of the package's complete, checked FILE inventory;
- `allowed_external_file_pins`, the complete canonical absolute-path/hash map
  derived from the accepted matrix's external raw pins. Canonical aliases collapse
  to one entry with consistent bytes. It must contain the frozen six helpers,
  held compiler FILEs and dependency watcher with their mandatory hashes. No
  override or unused extra is accepted.

The designated canonical matrix result remains
`build/verification/ranking-matrix-evidence-audit.json`. It must already be an
accepted final five-configuration result. Authority creation does not turn a
partial or allocation-review result into acceptance.

Root stages the three guide changes and then creates a separate immutable
`build/verification/ranking-completion-metadata-approval.json` with:

- `card: C02`, `reviewer: root`, `decision: accepted_verification_status_only`;
- exact `native`, `execution`, and `integration_record_sha256`;
- `status_document_changes` with exactly `README.md`, `docs/native_build.md`,
  and `docs/ranking.md`. Every entry contains `reviewer: root`,
  `decision: accepted_verification_status_only`, `change_kind: verification_status_only`,
  `before` equal to that destination's published integration `after` hash, and
  `after` equal to its new current hash. The before/after hashes must differ.

Optional per-entry `diff_evidence` contains a path under `build/verification/`
and its SHA-256. If supplied, the contents must exactly match Python's default
`difflib.unified_diff` over the published/current text with retained line endings,
three context lines, and labels `<destination>:published` and `<destination>:verified`.
There is no timestamp field in this canonical diff. The example approval in this
packet is deliberately invalid and cannot authorize a change.

After all final metadata, evidence packet and official current seal exist, root
runs with `--final` and the externally reviewed authority digest. The marker below
must be replaced with that exact digest, which cannot be known before the final
authority exists:

```sh
python3 "$c02_source_review/source_audit_revision.py" --final \
  --matrix-authority-sha256 ROOT_APPROVED_AUTHORITY_SHA256 \
  --output build/verification/ranking-source-evidence-audit.json
```

Only after acceptance should root create the completion checkpoint referring to
the approval, source audit, seal and evidence packet hashes. That checkpoint is
not an audit input, preventing a hash cycle or post-audit mutation of pinned input.
