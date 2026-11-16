# Native EXPLAIN CLI acceptance revision

This is a new, excluded black-box test package for the frozen native EXPLAIN CLI. It does not change native sources, register CTest targets, run the CLI, or claim O07 acceptance. Root owns execution and any later migration into native test tooling.

## Inputs and portability

`native_cli_acceptance.py` accepts a native CROWN executable, repository working directory, schema directory, fixture directory, and output directory. The package includes the four copied schema files, the P08 lowering manifest, and a preserved copy of the fixture subtrees it references. The default fixture directory is next to the script. A later native test copy can pass its own schema and fixture paths without reading any `docs/verification` files.

The core run does not require an older `build/release/crown` binary. Existing non-EXPLAIN commands remain covered by the native regression suite. Any before/after binary comparison can be added as a separately requested preintegration check.

The runner uses Python 3 standard-library process, JSON, hashing, and filesystem support plus `jsonschema` 4. It resolves the four pinned schemas locally with `RefResolver`, rejects file/network references outside that set, and does not require the `referencing` package or network access.

## Coverage encoded in the harness

- Every valid case in the copied P08 lowering manifest is independently lowered by the supplied CROWN CLI. The emitted P08 plan is passed to `crown explain physical`; report routes, identity hashes, checked heights, native occurrence IDs, scopes, children, separators, C* membership, visible scopes, and fixture expectations are compared directly.
- Physical reports and standalone trees are validated offline against the closed V2 schemas. Query reports and witness payloads are also validated against the standalone V1 schemas. Schema mutation checks cover version, authority, route/status enums, unknown fields, metric availability/payloads, owner ID types, registry units, and extra cost claims. A cross-field height mismatch is documented as schema-valid and is checked semantically for actual reports.
- Human, JSON, DOT, and tree-JSON output are checked for physical, runtime, session, and query forms. Byte ceilings are tested at the exact emitted length, one byte below, and zero. Failures require the documented resource-limit status and empty stdout.
- Real runtime and owned JSONL-session reports exercise observation, mode, live-maintenance, completion, result-view, pending input, retain/discard/transfer, and preserve/stop/drop states. The generated event includes the native catalog fingerprint reconstructed from the actual lowered plan's source catalog; only the CLI's successful admission and committed report are treated as runtime evidence.
- Query, progress, exact-search optimum, verified infeasibility, and certificate replay forms are checked. A P06 tree-oracle certificate must match the exact query/plan binding before a physical report can claim a verified minimum. Wrong-query, wrong-height, corrupted, and orphan `--proof-work` cases require empty stdout.
- Invalid, duplicate, unknown, dangling, and inapplicable flags and malformed/missing plan inputs are checked against their expected exit codes and empty stdout.
- A P08-admitted UTF-8/control-label fixture checks JSON preservation and text/DOT escaping. DOT is checked lexically only; Graphviz rendering and parsing are not performed.

## Run command

From the repository root, after root has reviewed the package and selected the frozen production binary:

```sh
python3 docs/verification/o07-native-explain-cli-test-revision-proposal/native_cli_acceptance.py \
  --crown /tmp/crown-o07-native-integration-production/crown \
  --expected-crown-sha256 399b83154aa16c1a12e946729d60e5d5fd3c2f9844aaffac3d58468c9f56e9ff \
  --repo-root /home/userroot/Codex/CROWN \
  --schema-dir docs/verification/o07-native-explain-cli-test-revision-proposal/schemas \
  --fixture-dir docs/verification/o07-native-explain-cli-test-revision-proposal/fixtures/p08 \
  --outputdir /tmp/crown-o07-native-explain-acceptance
```

The preparatory CLI SHA-256 remains recorded as provenance in `readiness.json`. `--expected-crown-sha256` enforces an optional caller-selected binary pin. When omitted, the harness records the actual selected binary path and hash, allowing native Debug, Release, sanitizer, Clang and clean-build executables without rewriting this test package. Artifact, fixture and schema hashes remain mandatory. `--outputdir` defaults to `/tmp/crown-native-explain-acceptance`; each run still creates its own fresh child directory. The output parent must be under `/tmp` or the repository's `build/verification`. Each run creates a fresh subdirectory with every command's argv, expected/actual return code, input hashes, stdout, stderr, parse result, and a final check summary. For a copied native test package, pass that copy's matching `--schema-dir` and `--fixture-dir`; keep the runner, readiness, source map, schemas, and fixture tree together.

This package is authored but not executed. Its readiness identifies proposal inputs and pins, not behavioral test results. Root's run determines whether any encoded expectation needs correction.


## Narrow revision and preserved evidence

Original package `../o07-native-explain-cli-test-proposal/`, SHA
`cea50af149ef1e3993108f63b3566eaf1ac4f691c5c7dffb5e610d6aa8fcceba`,
is preserved byte-for-byte. Root attempt 1 stopped after two CLI invocations
and 168 checks; all 294 input pins matched. The erroneous test required every
registry `includes` string to be nonempty. `support.work` legitimately has an
empty inclusion string: it has no nested inclusion. This revision requires
nonempty unit, scope and accounting, plus a string-valued inclusion field;
physical inclusive/exclusive work and delta work retain explicit, exact
inclusion/exclusion relationship assertions. No schema or semantic gate is
removed. Raw original failure: `build/verification/o07-native-explain-cli-acceptance-attempt-1.{json,log}`.

Binary-hash and output-argument portability changes are documented above;
additional source-derived fixture/schema corrections are listed below. Root's preparatory runner must continue to
pass the `399b831...` production hash explicitly or independently pin that
input. The package is authored but not executed: no binary, harness, Python
test, CMake or CTest was launched by the revision author.

Source-derived fixture corrections preserve the intended gates:

- Intended-success incremental runtime/session and byte-boundary cases now use
  explicit `anchored` completion. The frozen resolver permits this combination;
  explicit `on_output` plus `ordered_replay` remains a separate positive case.
  The original incompatible incremental/ordered-replay pair is tested for both
  runtime and session as a negative: exit 1, empty stdout and the exact
  `invalid_options` error, so parser/document failure cannot satisfy the gate.
- The query report's embedded witness summary is not a standalone witness
  artifact. An actual optimum `tree-json` invocation now supplies the V2 wrapper
  and genuine V1 witness export for both schema validation and the existing
  malformed-binding/unknown-field mutations. Its binding, height and tree must
  exactly match the genuine optimum query report. No wrapper or authority flag
  is synthesized by the harness.
- Query DOT has the exact graph name `checked_query_witness`; the other three
  report forms use `crown`. Lexical validation selects the expected name from
  the requested artifact form instead of incorrectly requiring `crown` for all
  forms. Every byte-baseline format now invokes its format validator, including
  text/DOT; complete boundaries and control-byte checks remain mandatory.

These corrections were derived from frozen runtime/exporter source, not from
running the revised harness. All previous semantic checks remain, with the
invalid completion combinations and actual standalone witness checks added.
