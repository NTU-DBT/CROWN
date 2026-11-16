# O07 independent EXPLAIN results — 2026-11-07

This is excluded standalone report/CLI evidence, not native O07 acceptance.
Root executed the [independent harness](o07-explain-test-proposal/README.md)
against frozen package `1062120b94a5733506186cb93cd6dac2bc99c7b4b3d3ab95e8c9c1882afbdb93`.
Attempt 4 passes 2,136 checks over 82 actual CLI invocations in 3.675 seconds.
The native Release CLI supplied every P08 physical plan used in the checks.

All 14 valid lowering families pass exact comparisons of root, kinds, original
occurrences, scopes/children, physical separators, parents, visible scope and C*
against actual P08 artifacts and the separate literal fixture manifest. All 42
JSON/text/DOT exports pass. No-proof reports remain checked upper/compile only,
with unavailable runtime metrics and no cost-ranking/global-optimality claim.
A matching native P06 certificate is replayed before minimum-height reporting;
wrong query, altered height, corrupt claim and malformed input are rejected.

The offline closed schema rejects 12 meaningful mutations. A separate check
shows a cross-field height mismatch is schema-valid, so semantic equalities are
checked independently on each emitted artifact. Synthetic summaries are used
only for schema shape, never as runtime evidence. Six invalid CLI cases reject.
Each format accepts its exact encoded size and rejects N-1 with empty stdout.
Unicode, NUL and other controls survive exact JSON decoding and are escaped in
human/DOT labels. DOT is checked lexically; Graphviz parse/render was not run.

Raw root receipt: `build/verification/o07-explain-independent-attempt-4*`.
Per-invocation stdout/stderr, inputs, hashes and result records are retained at
`/tmp/crown-o07-explain-acceptance/o07-explain-acceptance-20261106T220602Z-1023799-89fae0eb/`.
The accepted harness SHA-256 is
`130b5639cf8f285d0bcc6212aa4c1386b124d20ddb2ecd33b7102a6f86bf2524`.
CLI SHA-256 is
`5187c47b1cb39e3604fe514a36010a647bfcbbb35fdbd90deb81ae1531e7d314`.
Attempts 1–3 are retained unaccepted harness preparations: numeric P08 IDs,
DOT fixture field coverage and Invocation-versus-byte-result access were corrected.
No report code, expected authority rule or native test was relaxed.

The separate live `PlanExplanation::capture(runtime)` emitter/verifier now
passes six real reports and 186 checks in 0.515 seconds. Captures cover initial,
pending, committed, no-op switch, successful switch and saturation; the final
owning report is serialized after runtime destruction. It preserves the old
attempt's delta/generation-max-minus-one binding while current configuration
moves through maintenance/exact maximum and delta/saturated maximum. Every
requested nested option, schema, disabled/unavailable null payload and owner
binding is checked. Evidence: `build/verification/o07-explain-live-attempt-1*`;
raw reports: `/tmp/crown-o07-runtime-report-verification/o07-runtime-report-20261106T221026Z-1024996-fad0e6c6/`.
Emitter source SHA is `29e732d631e3aeeec7da1d924fdced300fd804b5c01f307af48314f5bbbdf63a`;
binary SHA is `cc6642539dcd876b29034abcacbfa1c7e0486d0cf664e7773077026e5295b679`.
The first compile's test enum qualification was corrected; no product behavior
changed. Candidate-family/native factory fault cases, newer run-context
and cursor APIs, final schema/human wiring, progress/infeasible reporting and the
full native matrix remain open. O07 remains not started before native integration.
