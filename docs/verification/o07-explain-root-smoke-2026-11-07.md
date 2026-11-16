# Root-observed O07 EXPLAIN smoke — 2026-11-07

This is excluded standalone preparation, not native O07 acceptance. O07 remains
not started while native P07 is frozen. The root executed the stable mode-binding
variant of the [EXPLAIN proposal](o07-explain-proposal/README.md).

Ten actual CLI calls pass: the verified native Release CLI lowers the existing
singleton fixture to a P08 artifact, then the new CLI emits JSON, human text and
DOT, each at the default ceiling, its exact encoded byte length, and one byte
less. Exact ceilings return byte-identical complete output. All three short
ceilings reject with exit 4 and empty stdout. The actual JSON passes the closed
v1 schema through the repository's installed jsonschema/RefResolver with network
and outside-file retrieval denied.

Independent assertions check native height one, diagnostic-only authority,
checked upper without an attached proof, compile-only mode, unavailable runtime
metrics, unimplemented cost selection and no global cost-optimality claim.
No Graphviz renderer/parser is installed or was run; the DOT result is output
and byte-limit evidence only.

The complete package SHA-256 is
`1062120b94a5733506186cb93cd6dac2bc99c7b4b3d3ab95e8c9c1882afbdb93`.
The new-mode CLI SHA-256 is
`5187c47b1cb39e3604fe514a36010a647bfcbbb35fdbd90deb81ae1531e7d314`.
Every individual package pin matches before execution. Input/output/error files,
commands and exit/timing records are in
`build/verification/o07-explain-root-smoke/`; `summary.json` records the scope.
The root helper is `/tmp/crown-o07-explain-smoke.py`.

An initial harness attempt found that the optional Python referencing module
is absent before any artifact execution. The corrected helper uses the existing
repository offline RefResolver pattern without installing dependencies. This
was a harness environment correction, not a product defect.

Independent fourteen-fixture CLI/schema/proof/mutation checks and runtime mode
binding tests remain pending. Initialization/input/output context, current
cursor timing, progress/infeasible-query reporting, native integration and the
full O07 matrix remain separate gates. Existing runtime-slice sanitizer passes
do not cover these newer report and mode proposals.
