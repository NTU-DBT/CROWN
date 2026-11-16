# Root-only invocation

From the repository root, verify this packet's advertised manifest FILE hash,
then check its repository-relative rows and the separate input manifest. The
author has not executed the helper or a syntax checker.

```sh
c02_compiler_scope=docs/verification/c02-source-audit-compiler-scope-revision-proposal
sha256sum --check --strict "$c02_compiler_scope/PACKAGE_SHA256SUMS"
sha256sum --check --strict "$c02_compiler_scope/INPUT_SHA256SUMS"
python3 "$c02_compiler_scope/source_audit_revision.py" \
  --seal build/verification/ranking-preliminary-sources.sha256 \
  --output build/verification/ranking-source-preliminary-audit-attempt-3.json
```

Preserve prior outputs. Use another fresh numbered output if that name already
exists. Preliminary mode can return exit 0 with pending gates and cannot return
final acceptance. The final invocation is:

```sh
python3 "$c02_compiler_scope/source_audit_revision.py" --final \
  --matrix-authority-sha256 ROOT_APPROVED_AUTHORITY_SHA256 \
  --output build/verification/ranking-source-evidence-audit.json
```

The authority and immutable three-document approval contracts remain those in
[the predecessor reproduction notes](../c02-source-audit-independent-review-proposal/ROOT_REPRODUCTION.md),
with one corrected scope statement: `allowed_external_file_pins` contains exactly
the observed canonical raw FILEs outside the repository. Mandatory tool values
cannot be overridden. Repository-local compiler FILEs instead require matching
canonical internal raw pins and current bytes. Both original Clang alias spellings
may occur in raw pins, but collapse to one mandatory canonical FILE.

No new authority field or standard-library import is required. The exact-hashed
predecessor utility is still the only imported non-stdlib source, and only its
pure helpers are called. The final accepted-matrix branch must be exercised by
root before this revision is accepted for final use.
