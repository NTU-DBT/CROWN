# C05 exact vendor diagnostic format revision

This excluded, evidence-only revision changes the clean-build diagnostic comparison in [audit.py](audit.py). The [source diff](diagnostic-format.patch) adds one helper and replaces the prior comparison call. All numeric, allocation-review, command, dependency, compiler, symbol, source, pending-state and final-acceptance gates remain byte-identical outside that diff.

Root's [first audit receipt](../../../build/verification/selection-matrix-evidence-audit-preliminary-1.json) recorded Release as `audited_pass` and rejected the clean comparison. The two GCC diagnostics used ASCII apostrophes, while the accepted historical logs used U+2018/U+2019. The third, make diagnostic was unchanged. Root's immutable [format review](../../../build/verification/selection-vendor-diagnostic-format-review-v1.json), SHA256 `f422c9fcdf30b77ee749fbcdd05e16cfb1dc0023f33f1ded803cdf411a9c6d79`, authorizes only the two complete line mappings.

The revision pins that review, its exact current log, both historical log FILEs and the original failure FILE. It compares the two literal source lines to their two literal historical counterparts. Each current line must occur exactly once, and the resulting multiset must contain exactly the original three warnings. There is no generic apostrophe replacement or diagnostic filtering.

| Observed change | Required result |
| --- | --- |
| The two exact reviewed ASCII lines, each once, plus the unchanged make line | Compare their exact historical counterparts and retain all three rows |
| A missing or duplicated warning | Reject |
| Different file, line, column, variable, wording, warning flag or an added warning | Reject |
| A changed review/log/failure FILE hash or mismatched native/execution scope | Reject |

`matrix.clean-source.warning_policy` retains `raw_observed_diagnostics`, canonical `exact_preserved_diagnostics`, the `format_review` FILE pin and the two `diagnostic_normalizations`. The same two records appear in the existing top-level `normalizations` list with `kind=vendor_diagnostic_format`, the complete raw/comparison lines, their zero-based warning indices and the review pin. No test numeric row is changed by this helper.

The presentation difference is consistent with the current explicit C locale; the historical locale value was not retained. This does not establish a compiler defect or make the existing warnings safe, fixed or suppressed. Compiler/source/flag identities remain independently checked. This correction grants no semantic/allocation waiver and no native acceptance.

The author has read, hashed and authored files only. Root owns syntax checks and every auditor or project execution. Future receipts and authorities remain outside this immutable source packet. The inherited [audit contract](../c05-native-matrix-independent-audit-proposal/CONTRACT.md) and [lineage](LINEAGE.md) continue to apply.
