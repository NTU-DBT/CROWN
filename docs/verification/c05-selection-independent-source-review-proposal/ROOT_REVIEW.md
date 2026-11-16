# Root-only reproduction

The author did not execute these commands. From the repository root, root can
verify the frozen packet and its new explicit input scope:

```sh
sha256sum --check docs/verification/c05-selection-independent-source-review-proposal/PACKAGE_SHA256SUMS
sha256sum --check docs/verification/c05-selection-independent-source-review-proposal/source-files.sha256
sha256sum --check docs/verification/c05-selection-independent-source-review-proposal/INPUT_SHA256SUMS
cmp docs/verification/c05-selection-independent-source-review-proposal/INPUT_BEFORE_SHA256SUMS docs/verification/c05-selection-independent-source-review-proposal/INPUT_AFTER_SHA256SUMS
```

Check only the explicitly listed input FILEs. Do not recurse into old package,
input, source or historical seal manifests. No compilation, testing, native
copy, or status transition is part of this packet's recipe. Read REVIEW.md
together with EVIDENCE.md and the original receipts; a source-review conclusion
does not convert a pending runtime gate into a pass.

After this freeze, any implementation/API change needs a separate review
revision. Later terminal runtime evidence may be bound by a separate root
record. Review of the final C05 publication source map and build registration
also remains separate until the author freezes that package.
