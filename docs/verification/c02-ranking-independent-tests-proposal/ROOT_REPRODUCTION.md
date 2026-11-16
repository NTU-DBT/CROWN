# Root execution and reproduction

Start at `/home/userroot/Codex/CROWN`. The author compiled and linked only.
Root owns all binary/checker/sanitizer execution and acceptance. Both consumers
use the production ABI, without `CROWN_RUNTIME_TESTING` or its runtime archive.
No native C++ archive is reused: the producer rebuilt every linked CROWN unit
against the repaired JSON header. Only the unchanged parser C archive is reused.

The separately accepted integer checkpoint remains historical. Preserve its
files and root's copied input snapshot. Do not recheck its old live-entry
manifests after the active-time header revision. Hashing those manifest files
is safe; their old live entries are not the current full-suite inputs.

## Verify and run the author-linked strict binaries

The top-level manifests use repository-root-relative or absolute paths:

```sh
c02_independent_package=docs/verification/c02-ranking-independent-tests-proposal
sha256sum --check --strict "$c02_independent_package/PACKAGE_SHA256SUMS"
sha256sum --check --strict "$c02_independent_package/SOURCE_SHA256SUMS"
sha256sum --check --strict "$c02_independent_package/INPUT_SHA256SUMS"
sha256sum --check --strict "$c02_independent_package/ARTIFACT_SHA256SUMS"
```

Then run each executable separately, retaining stdout, stderr, exit status,
elapsed time and before/after input/package/artifact checks:

```sh
/tmp/crown-c02-independent-current-3/ranking_integer_independent_test
/tmp/crown-c02-independent-current-3/ranking_public_independent_test /home/userroot/Codex/CROWN
```

The integer binary SHA-256 is
`8f491047df0ac160e48cbf6e2cd1d2cfdeb1997444ad3eef2daf2e81e3b5004e`;
the public binary is
`89b2fbae1a126c634e5f239f9a9c3b8363c05fbcfad4451f327437f325c96f19`.
The exact compiler/linker argument vectors, empty logs, zero exits, dependency
records and producer-input before/after checks are copied under `build/strict`.
The corresponding current binary/object files remain under the isolated `/tmp`
prefix and are pinned by `ARTIFACT_SHA256SUMS`.

Expected successful public output ends with eight groups, three Boolean
candidates, 200 hot-table inputs, literal slot scores `24,32,32`, and the
Decimal/repeated-head slot bound `13`. The arithmetic driver ends with three
groups and 16 boundaries. Root observed 54 operands and 2,916 ordered pairs in
the old checkpoint; the current execution must establish those facts again
under the revised ABI. Assertions are enabled by `-UNDEBUG`.

## Fresh strict consumer build with the held coherent closure

The script only compiles and links. It requires a new output directory and a
matching ready producer closure as its third argument:

```sh
bash "$c02_independent_package/reproduce-build.sh" strict \
  /tmp/crown-c02-independent-root-strict-1 \
  /tmp/crown-c02-baseline-coherent-strict-1
```

The integer consumer links only its matching `ranking_integer.cpp` object.
The public consumer uses a static linker group containing the rebuilt production
runtime, ranking, reference, plan, SQL and core archives, followed by the parser
C archive. `provenance/PRODUCTION_OBJECTS.tsv` lists all 67 producer units in
those archives: 31 core, 10 SQL, 3 plan, 3 ranking, 15 production runtime and
5 reference units. An archive being an input does not claim that every archive
member was pulled into the executable. The producer's full 82-row inventory
also records its 15 testing-runtime units; none is used by these two consumers.

The patched JSON include directory is the only third-party C++ include root.
Never substitute any old CROWN C++ archive, checkpoint-1 object, testing-runtime
archive, mismatched active-time ABI, or ordinary object in a sanitizer closure.

## Rebuild all coherent production dependencies

`provenance/producer-compile-closure.sh` is an exact preserved copy of the
producer's compile-only recipe at SHA-256
`c68bd85288c21b99bf1cb2c4fceea3fde007a3dba1819fcdbb25587470141342`.
The following stages rebuild every production dependency needed by this packet;
they neither invoke the producer's tests nor run a produced executable:

```sh
c02_dependency_out=/tmp/crown-c02-baseline-independent-root-strict-1
for c02_stage in core sql_plan ranking_reference runtime; do
  bash "$c02_independent_package/provenance/producer-compile-closure.sh" \
    strict "$c02_dependency_out" "$c02_stage" /home/userroot/Codex/CROWN
done
bash "$c02_independent_package/reproduce-build.sh" strict \
  /tmp/crown-c02-independent-root-strict-2 "$c02_dependency_out"
```

Use a new dependency prefix. Preserve its generated `.command`, `.log`, `.exit`,
`.d`, `.input.tsv`, before/after source checks and archive `.members` records,
and pin the actual compiler/linker/parser inputs and resulting artifacts.
The copied producer recipe has additional test/testing stages; they are not
required for these production consumers and are outside this package's claimed
build result. Its source lists and include order remain part of this packet's
reproducible contract.

## Matching sanitizer reproduction remains a root gate

Root must first validate the native sanitized parser C archive and preserve its
actual hash. The CROWN C++ dependency closure must be rebuilt with the repaired
header and sanitizer flags, even if older native sanitized archives exist:

```sh
c02_dependency_san=/tmp/crown-c02-baseline-independent-root-sanitize-1
for c02_stage in core sql_plan ranking_reference runtime; do
  bash "$c02_independent_package/provenance/producer-compile-closure.sh" \
    sanitize "$c02_dependency_san" "$c02_stage" /home/userroot/Codex/CROWN
done
bash "$c02_independent_package/reproduce-build.sh" sanitize \
  /tmp/crown-c02-independent-root-sanitize-1 "$c02_dependency_san"
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  /tmp/crown-c02-independent-root-sanitize-1/ranking_integer_independent_test
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  /tmp/crown-c02-independent-root-sanitize-1/ranking_public_independent_test /home/userroot/Codex/CROWN
```

A producer-supplied coherently rebuilt sanitizer closure may be used instead
only after root pins and validates its source/header/variant/compiler identities.
The author has not built or run this sanitizer variant. Strict linking alone
does not establish its outcome, the JSON persistent-failure controls, native
integration, matrix acceptance, or completion of C02.
