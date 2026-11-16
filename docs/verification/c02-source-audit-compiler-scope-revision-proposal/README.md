# C02 source-auditor compiler-scope revision

This is a narrow source-only revision of the frozen, executed source-auditor
repair. The predecessor package FILE remains
`e2382d50e4a2040476ed355869551af8893c941abe22e1314ce71315d925b978`;
its script remains
`43669daf321dc5e40e23fdc33374f1da826ba678410b2f0a5ca6c9acb81a790e`.
The preserved preliminary attempt 2 receipt has FILE SHA-256
`a3ee5b28d0ba693f7615eccc07fa3c7b48ffcc4a3465dee596430d1923e5d18e`.
No predecessor file or receipt was changed.

Root found that the predecessor's final matrix branch treated every mandatory
compiler as external. Both frozen Clang aliases resolve to the repository-local
`build/toolchains/clang18/root/usr/lib/llvm-18/bin/clang`. Requiring that path in an
external-only whitelist contradicted the whitelist's correct scope restriction.
The preliminary receipt did not exercise this final accepted-matrix branch.

The new `source_audit_revision.py` retains every mandatory compiler, helper and
watcher hash. It canonicalizes mandatory and actual raw pins, rejects conflicting
hashes for aliases, and checks each mandatory canonical FILE against both the raw
map and current bytes. Only tools outside the repository must additionally occur
in the exact external whitelist. An internal mandatory tool must occur in the
actual internal raw pins; it cannot be omitted merely because its path is internal.
The matrix receipt adds `mandatory_tool_file_pins`, including scope, canonical
path, expected hash, frozen spellings and observed raw spellings. This records the
two Clang aliases without pretending that they name two independent binaries.

All other acceptance checks, final-mode requirements, status-document approval
rules, matrix authority binding, source counts and allocation-review rules are
unchanged. `revision.diff` is the complete source change. This packet grants no
allocation waiver, project status or final source acceptance.

The reviewer only read, hashed and authored files. No Python invocation, syntax
checker, compiler, binary, build system, symbol tool, process poll, network or git
operation was performed. The root-only checks in `REVIEW_CASES.md` remain proposed
until root runs them or the final branch. The old 843 input paths are preserved as
FILE inputs and extended with this revision's predecessor receipt and tool aliases;
historical source-manifest entries are never re-evaluated.

Author lineage is unchanged: this reviewer authored the independent ranking
fixtures and matrix auditor, and authored the earlier source-auditor repair after
reviewing the root draft. This is an authored correction with root review, not a
claim of a second independent implementation.
