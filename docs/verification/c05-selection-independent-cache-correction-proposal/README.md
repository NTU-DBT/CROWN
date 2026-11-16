# C05 cache fixture: supported and unsupported arithmetic

Root confirmed that the first cache-suite failure was the fixture's arithmetic
mutation, not a numerical mismatch. Diagnostic call 33, physical-options field
0, returned `lowering_failure` at `lowering`, with no resource stop, component
stop or selection. The preceding 32 calls reached their expected results. The
terminal diagnostic receipt is
`build/verification/c05-independent-cache-diagnostic-root-attempt-1.json`, FILE
`9cad99e6147feb3eb30126c7627c1e96ac2695b223b70cd8b13fa2de06ad3bb0`.
Its exit 1 preserves the old failed success assertion; it is diagnosis, not a
passing acceptance test.

Native identity admits only the arithmetic policy `exact-nonnull-v1`, as
specified in `docs/query_identity.md` and enforced by `src/io/identity.cpp`.
The old fixture appended `-namespace` and incorrectly expected successful
lowering. This new source keeps the same unsupported mutation but checks the
actual rejection contract and complete cache-statistics equality. It then
checks every previously inserted entry by a read-only hit, requiring the same
binding and immutable compiled artifact, with only the exact expected hit
counter increments. Restoring the supported arithmetic value must hit the
original same-configuration artifact and preserve all other statistics.

The five supported options retain the original distinct-key assertions:
planner, optimization and cost-model version strings, lowering work limit and
identity work limit. All other original assertions, scalar/score values, FIFO,
capacity, proof refresh, raw-tree, lifecycle and owner checks remain unchanged.
The success line now reports `physical_options_supported=5` and
`physical_options_rejected=1`; it no longer implies six supported namespaces.
The exact source change is `supported-arithmetic-correction.diff`.

This is a separate correction packet. The original source, failed ordinary
receipt, diagnostic source/result, earlier two-consumer revision and held
sanitizer draft are untouched. No selection/ranking/native implementation or
API is changed. The current root build recipe compiles and links only this
cache consumer against the unchanged strict3 production closure. The author
has not compiled, linked or executed it. Passing root execution remains required
before this source can replace the cache source in the unsealed sanitizer
recipe or native-publication overlay.
