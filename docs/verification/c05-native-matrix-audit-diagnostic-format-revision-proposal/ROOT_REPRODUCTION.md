# Root-only reproduction

The author does not execute or syntax-check the auditor. Root verifies the frozen package and its 61 input FILE pins, reviews the exact source diff, then creates a new immutable execution authority that binds this revision's auditor and package hashes. The authority must use a suffixed filename; the unsuffixed final source-authority path remains reserved for binding the later canonical matrix receipt.

From `/home/userroot/Codex/CROWN`, root invokes:

```text
python3 docs/verification/c05-native-matrix-audit-diagnostic-format-revision-proposal/audit.py \
  --authority build/verification/selection-matrix-audit-authority-execution-v2.json \
  --authority-sha256 AUTHORITY_SHA \
  --output build/verification/selection-matrix-evidence-audit-preliminary-2.json
```

`AUTHORITY_SHA` is a placeholder for the exact root-approved authority FILE hash. The output path must be new. The review FILE for the two warning mappings is fixed by the source and does not grant allocation approval. If independently investigated allocation differences require a separate new root decision, the unchanged interface accepts both:

```text
--allocation-review build/verification/selection-allocation-review-REVIEW_ID.json \
--allocation-review-sha256 ALLOCATION_REVIEW_SHA
```

No historical C02 allocation decision automatically approves a C05 difference. Missing/live configurations remain pending. Exit 0 requires the unchanged complete five-configuration acceptance gates; errors, pending evidence and unapproved allocation differences retain their distinct nonzero results. Root preserves the first failed receipt and every later attempt.

The fixed review binds the existing terminal clean log; this formatter-only correction does not request another native build or test run. Future execution, allocation and final source authorities and output receipts are root-owned evidence outside this source packet. If this revision later requires a correction, create a separate sibling packet.
