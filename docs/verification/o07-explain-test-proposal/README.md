# Excluded O07 EXPLAIN CLI and schema acceptance proposal

This is an independent harness for the frozen report/CLI proposal. It changes
only this excluded directory. It does not compile native code, apply the
proposal overlay, edit existing tests, or update any project status. The root
owner runs the harness after selecting the matching native `crown` binary.

The proposal is currently compiler/link preparation only. The harness pins the
mode-binding-compatible standalone CLI, its report schema, the complete
nine-unit mode-binding runtime archive, linked archives, and the source
dependency hashes from the frozen readiness/evidence files. It refuses an
unrecognized or changed explain binary or dependency package. The native CLI is
an explicit input and its hash is recorded on every run.

## Run command

Use Python 3.10+ with `jsonschema` 4 installed. Schema validation uses the local
Draft 2020-12 schema and only its local `$defs`; it does not access the network.
The output path must be under `/tmp` or the repository's `build/verification`
directory.

```sh
python3 docs/verification/o07-explain-test-proposal/acceptance.py \
  --native-cli /absolute/path/to/crown \
  --explain-cli /tmp/crown-o07-explain-mode-binding/crown-explain-proposal \
  --repo /home/userroot/Codex/CROWN \
  --outputdir /tmp/crown-o07-explain-acceptance
```

The harness creates a unique run directory. Each invocation retains its
`stdout.bin`, `stderr.bin`, parsed `result.json`, exact argument and exit status
in `invocation.json`, and SHA256s for all file inputs in `inputs.json`. The
top-level `run-summary.json` records the frozen source/dependency/archive,
schema, native CLI, and explain CLI hashes, check outcomes, and actual fixture
and invocation counts. Generated queries, trees, plans, certificates, and
mutations are written inside that run directory.

## Coverage

The harness selects every `valid: true` record from
`tests/structural/lowering/manifest.json`. For each, it asks the native CLI to
lower the query and checked tree into an actual P08 physical plan, then asks
the standalone EXPLAIN CLI for JSON, human text, and DOT. It validates JSON
offline against the pinned schema and compares route, plan identity, native
height, edge depth, tree root, node kinds, occurrence IDs, scope and children,
parent/separator relationships, visible scopes, and C* membership with both
the physical plan and the literal fixture expectation. It also checks that
no-certificate reports retain `checked_upper`, compile-only mode, unavailable
observations, and cost `not_implemented` / `global_optimality: false` claims.
Metric registry IDs, names, units, and scopes are checked as emitted.

An actual small native `tree-oracle` certificate is replayed against its exact
P08 plan and may report `verified_original_minimum` only at the matching native
height. Certificates for a different query, an altered minimum height, and a
corrupted lower-bound claim are rejected with empty stdout. A truncated
certificate is also rejected with no partial report.

Schema mutations cover a wrong schema version, authority, route/status enums,
unknown fields, malformed metric availability/value combinations, registry
units, owner ID and option types, and an added global-cost-optimal claim. A
separate check demonstrates that Draft 2020-12 validation alone accepts a
selected-height cross-field mismatch; the harness compares those heights
semantically for every emitted report. Synthetic observation/configuration
objects are used only as schema-shape inputs and never treated as runtime
evidence.

The harness checks invalid format/flags, malformed and missing input, exact
encoded-byte ceilings, and the one-byte-below failure for each output format.
It sends a non-ASCII and embedded NUL/control-label query and tree through the
native `lower-plan` path, then checks JSON/text/DOT escaping and safe UTF-8.
Graphviz is not installed in the target environment; the harness does not
install or invoke it. DOT is checked lexically only, and Graphviz parse/render
is explicitly reported as not performed.

## Scope and limits

The harness does not generate plans outside the native P08 path, call a report
writer directly, or treat schema-valid JSON as proof. It does not compare
runtime snapshots, historical mode transitions, candidate-family admission,
SQL-normalized plans, allocation failures, or the frozen five-configuration
sanitizer matrix. Runtime mode-binding tests remain in the separate excluded
`o07-mode-binding-test-proposal` package. Full O07 acceptance and all existing
root-owned execution gates remain pending.
