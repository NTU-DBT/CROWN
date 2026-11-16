# Root-only sanitizer execution

Start at `/home/userroot/Codex/CROWN`. The author does not run either executable
or any checker. Verify the frozen packet and its live current inputs/artifacts:

```sh
c02_san_packet=docs/verification/c02-ranking-independent-sanitize-proposal
sha256sum --check --strict "$c02_san_packet/PACKAGE_SHA256SUMS"
sha256sum --check --strict "$c02_san_packet/SOURCE_SHA256SUMS"
sha256sum --check --strict "$c02_san_packet/INPUT_SHA256SUMS"
sha256sum --check --strict "$c02_san_packet/ARTIFACT_SHA256SUMS"
sha256sum --check --strict "$c02_san_packet/COMMAND_EVIDENCE_SHA256SUMS"
```

Run the two final binaries separately with these exact argv and environment
overrides, retaining exit status, elapsed time, stdout and stderr:

```sh
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
  /tmp/crown-c02-independent-sanitize-current-2/ranking_integer_independent_test
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
  /tmp/crown-c02-independent-sanitize-current-2/ranking_public_independent_test /home/userroot/Codex/CROWN
```

`commands.json` records the same argv/environment structurally. After execution,
repeat the manifest checks. No warning/sanitizer output is pre-waived. Root must
resolve any nonzero exit or diagnostic before accepting this scope.

Expected ordinary semantic output remains unchanged: arithmetic three groups,
54 operands, 2,916 ordered pairs and 16 boundaries; public eight groups, three
Boolean candidates, 200 hot-table inputs, slot scores `24,32,32` and the
Decimal/repeated-head slot bound `13`. These are the strict observations and
frozen assertions, not claimed sanitizer results before root runs them.

For a fresh consumer-only rebuild, the preserved script is byte-identical to
the frozen strict package's compile-only recipe. It reads that packet's original
test sources and writes only the selected new output directory:

```sh
bash "$c02_san_packet/provenance/consumer-reproduce-build.sh" sanitize \
  /tmp/crown-c02-independent-sanitize-root-1 \
  /tmp/crown-c02-baseline-coherent-sanitize-1
```

The actual author invocation used the original frozen script with output
`/tmp/crown-c02-independent-sanitize-current-2`; all exact compiler/link commands,
zero/failed exit records as applicable and logs are retained under
`build/sanitize`. The production archive/source mapping is in
`provenance/PRODUCTION_OBJECTS.tsv`; the full producer inventory also includes
15 testing-runtime rows that these consumers do not use. Archive inputs do not
imply that every archive member was pulled into each binary.

The producer's matching library manifest is pinned at
`51850a9886a14511de7a727eb0f5987a9e628432f2871d5ad879123a8c1ac66a`.
Its sanitized parser C archive is
`build/sanitize/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a`, SHA-256
`1e59d1caaf15beb5a2e0aaf664fa3f853f058c7eefdd4b80bae3a37c5f0f9bfc`.
Do not substitute the Release parser, a strict CROWN object, a native cached
C++ archive, or the testing runtime.

If the complete dependency closure must be recreated, use the exact preserved
producer compile-only recipe and a fresh producer output prefix. These four
stages compile all 67 required producer units without running producer tests:

```sh
c02_san_dependency=/tmp/crown-c02-baseline-independent-root-sanitize-2
for c02_stage in core sql_plan ranking_reference runtime; do
  bash "$c02_san_packet/provenance/producer-compile-closure.sh" sanitize \
    "$c02_san_dependency" "$c02_stage" /home/userroot/Codex/CROWN
done
bash "$c02_san_packet/provenance/consumer-reproduce-build.sh" sanitize \
  /tmp/crown-c02-independent-sanitize-root-2 "$c02_san_dependency"
```

Pin any fresh build's actual inputs, commands, artifacts and resulting binary
hashes before executing it. The compiler recipe uses only the patched JSON
include root for third-party C++ headers and asserts the production runtime ABI
by omitting `CROWN_RUNTIME_TESTING`. The wrapper does not infer or bless a supplied
closure: the root must verify its exact configuration/variant/source identities.

The unchanged strict packet's old pending-execution prose records its original
freeze state; root's terminal strict attempt 2 is the later acceptance evidence.
Do not edit that packet or recheck the pre-ABI integer checkpoint's obsolete
live-entry manifests. This sanitizer packet never advances a task ledger.
