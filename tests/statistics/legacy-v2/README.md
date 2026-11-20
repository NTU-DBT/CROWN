# C01-off EXPLAIN v2 baselines

These two files are exact copies of root-produced runtime and session reports,
not manually written expectations or outputs of the new v3 writer. Their
[checksums](SHA256SUMS) are checked before each native statistics report test.

Root produced them on 2026-11-07 in the accepted strict-only report attempt 1,
using `/tmp/crown-c01-report-legacy-control/statistics_legacy_control` (SHA-256
`b042e8c80a99bcea6e6242235ae913046107664d3fd6d333662dfbf20d67258f`).
The original output directory was
`/tmp/crown-c01-report-root-attempt-1-legacy-baseline/`. The producer used the
frozen combined runtime and original v2 report objects; it did not use the v3
writer or the new report runtime sources. The preserved command, object pins,
archive pins and source are in the frozen report proposal's build evidence.
Root records the successful command and output comparisons in
`build/verification/c01-statistics-report-root-attempt-1.json`.

The combined package manifest is
`cb0ecb64935f80bf4915aa069de1bf01bcf1ea2f22a591f6f7408d405fcf4cfe`;
the report package manifest is
`730a7488e53a749b024b307dab27c09d58a324ae7603bccc8831364af289f947`.
The producer deliberately constructs the runtime and session in the same order
as the native statistics fixture, preserving process-local owner identifiers.
The independent checker compares exact bytes and validates the old v2 schema
in each production/testing report corpus. Clean native builds consume only
these checked-in baselines and need no historical temporary files or binaries.

The JSON files describe the original v2 scope, including its historical
capability strings. They do not declare acceptance of C01 or replace its v3
schema. Do not regenerate them with the implementation under test to make a
failed comparison pass; inspect the behavior and preserved provenance first.

2026-11-20: `legacy-session.json` was regenerated for one intentional change:
`InputLimits::records` now defaults to unbounded, so the embedded input policy
reads `"records":null` instead of `"records":1000000`. No other byte changed.
