# Root-only reproduction

The author has not executed or syntax-checked this auditor. Root reported successful AST and source review of the exact body before authorizing this freeze. Root verifies the final package/input manifests, writes a separate immutable execution authority using the exact auditor/package identities, then invokes from `/home/userroot/Codex/CROWN`:

```text
python3 docs/verification/c05-native-matrix-independent-audit-proposal/audit.py \
  --authority build/verification/selection-matrix-audit-authority-execution-v1.json \
  --authority-sha256 AUTHORITY_SHA \
  --output build/verification/selection-matrix-evidence-audit-attempt-1.json
```

`AUTHORITY_SHA` is a documentation placeholder, replaced with the exact reviewed FILE hash. The unsuffixed final source authority is not valid here. The output may remain pending while other legs are live; an expected nonzero preliminary status is not native test failure or final acceptance.

If the auditor reports an allocation-only difference, root investigates and may create a new exact content-bound review FILE. A subsequent new output uses both additional arguments:

```text
--allocation-review build/verification/selection-allocation-review-REVIEW_ID.json \
--allocation-review-sha256 ALLOCATION_REVIEW_SHA
```

No approval is inferred from a compiler name, an old C02 count, matching aggregate deltas, or a prior narrow approval. Semantic changes fail independently. Preserve every previous output and log. If the auditor itself needs correction after freezing or execution, author a separate sibling revision rather than editing this packet.

The later source-audit authority and canonical matrix receipt are root-owned artifacts created after matrix closure; they are not appended to this immutable auditor package. Full native acceptance still requires that source/status audit. The scope remains C05 selection and its declared logical proxies, not C03 optimization, S05 allocator/peak measurement or deployment readiness.
