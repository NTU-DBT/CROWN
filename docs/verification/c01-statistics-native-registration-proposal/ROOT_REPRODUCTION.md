# Root-only application and reproduction

All commands start at `/home/userroot/Codex/CROWN`. The author executed only
the narrow direct compiler/link script, not any command below that configures,
inspects symbols, runs producers, or invokes checkers/CTest. Keep each new root
attempt's logs and pins outside this frozen package. Native integration remains
conditional on root's accepted report sanitizer and benchmark gates.

## Review the frozen proposal

```sh
c01_registration_package=docs/verification/c01-statistics-native-registration-proposal
sha256sum -c "$c01_registration_package/PACKAGE_SHA256SUMS"
sha256sum -c "$c01_registration_package/INPUT_SHA256SUMS"
sha256sum -c "$c01_registration_package/source-files.sha256"
sha256sum -c "$c01_registration_package/PREEDIT_DESTINATIONS_SHA256SUMS"
while IFS= read -r c01_destination; do
  test ! -e "$c01_destination" || exit 1
done < "$c01_registration_package/NEW_DESTINATIONS.txt"
```

The input manifest includes historical compiler objects for the narrow relink
evidence and original `/tmp` baseline outputs. Native builds do not depend on
them: after acceptance the committed sources, schemas, checker and baseline
copies are the complete build/test inputs. If an old temporary artifact has
been removed, preserve that fact and use its sealed predecessor evidence;
do not fabricate a successful historical manifest check.

## Execute the publication-only change before copying native sources

The completed strict binaries are in
`/tmp/crown-c01-native-registration-{production,testing}`. Their exact pins and
link closure are in `build-evidence/`. Recompilation is unnecessary unless inputs
changed. Stage only the files the native wrapper needs, alongside the unchanged
v2 schema; this permits checking the new publication format before native edits.
Use a fresh staging path for each attempt.

```sh
c01_registration_stage=/tmp/crown-c01-native-registration-root-stage-attempt-1
test ! -e "$c01_registration_stage"
mkdir -p "$c01_registration_stage/schemas" "$c01_registration_stage/tools" \
  "$c01_registration_stage/tests/statistics"
cp -a "$c01_registration_package/overlay/tools/." "$c01_registration_stage/tools/"
cp -a "$c01_registration_package/overlay/tests/statistics/legacy-v2" \
  "$c01_registration_stage/tests/statistics/"
cp "$c01_registration_package/overlay/schemas/statistics-explain-v3.schema.json" \
  schemas/explain-report-v2.schema.json "$c01_registration_stage/schemas/"
for c01_variant in production testing; do
  python3 "$c01_registration_stage/tools/verify_statistics_reports.py" \
    --executable "/tmp/crown-c01-native-registration-$c01_variant/statistics_explain_test" \
    --repo-root "$c01_registration_stage" --variant "$c01_variant"
  "/tmp/crown-c01-native-registration-$c01_variant/statistics_explain_exception_test"
done
```

Record producer, independent checker, gate rejection and fault exits separately.
The wrapper labels its phases and prints checker results. The copied checker
retains 31 production/32 testing reports, two original-v2 byte comparisons and
15/17 semantic/schema mutations; the wrapper adds one removed-field rejection.
Failed corpora are retained automatically. This execution is still excluded
preparation and does not configure or verify native CMake.

## Apply only after the native-entry gates pass

First root must verify the current 691-entry O07 seal exactly once against the
still-unmodified native baseline, record the manifest file hash
`f4acf6ea043859d350aa0dd2d56c86afca24535d7288eb5774f94b26ab0ea21e`, preserve the
historical manifest snapshots, and retain the original Refactor.md identity.
Root owns this action; the author did not repeat that source audit. Follow the
[integration preflight](../c01-native-integration-preflight-2026-11-07.md).

Before overwriting any destination, save every existing destination and its
hash to a new root-owned backup directory outside proposal packages. The source
map has a header and four tab-separated columns. The following explicit copy
loop uses only its first two columns; the same map supplies the pre-edit list.
Root should use a fresh backup path and `set -euo pipefail` in its recorded runner.

```sh
c01_registration_backup=build/verification/c01-native-preedit-attempt-1
test ! -e "$c01_registration_backup"
mkdir -p "$c01_registration_backup"
cp "$c01_registration_package/PREEDIT_DESTINATIONS_SHA256SUMS" \
  "$c01_registration_package/NEW_DESTINATIONS.txt" "$c01_registration_backup/"
while IFS=$'\t' read -r c01_overlay c01_destination c01_origin c01_change; do
  test "$c01_overlay" != overlay_file || continue
  if test -e "$c01_destination"; then
    mkdir -p "$c01_registration_backup/$(dirname "$c01_destination")"
    cp -p "$c01_destination" "$c01_registration_backup/$c01_destination"
  fi
done < "$c01_registration_package/source-map.tsv"
while IFS=$'\t' read -r c01_overlay c01_destination c01_origin c01_change; do
  test "$c01_overlay" != overlay_file || continue
  mkdir -p "$(dirname "$c01_destination")"
  cp -p "$c01_overlay" "$c01_destination"
done < "$c01_registration_package/source-map.tsv"
```

Do not check old O07/native-input entry manifests against the modified tree or
rewrite historical manifests. Root records the new C01 native freeze, updates
the ledger/handoff to `in_progress`, and generates new evidence. No ledger,
handoff, historical seal or acceptance file is included in this overlay.

## Native configuration and registration check

After applying and freezing the native source, configure the normal builds.
The following illustrates Debug; repeat the repository's full existing compiler,
sanitizer and fresh-source matrix rather than treating this subset as acceptance.

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --test-dir build/debug --show-only=json-v1 \
  > build/verification/c01-native-debug-registered-tests.json
ctest --test-dir build/debug -L C01 --output-on-failure
ctest --preset debug
```

Root must independently compare all names with `expected-ctests.txt` (131 unique
names), all original commands with `registered-ctests.tsv`, and original target
definitions with the pre-edit CMake. Confirm the added 32 have label C01 and no
old target acquired acceptance macros. Inspect actual compile commands so the
testing macro flows only from the matching runtime library; ensure optimized
numeric consumers retain `-UNDEBUG`. Inspect the two runtime-only link commands:
they must not contain either report library or query-explanation library.

Each report CTest invokes the matching native producer via the native wrapper.
The existing sanitizer CTest environment applies to the additions. Root extends
its symbol inspection to the C01 saturation seam and preserves distinct
production/testing closure evidence; this proposal has run no symbol inspector.
The existing complete O07/v2 fixtures remain part of all native runs.

Only after full native builds/tests, fresh-source reconstruction, legacy report
compatibility, independent source/symbol review and the new source seal agree
may root mark C01 verified. The selected FIFO/LIFO tests and accepted engine
benchmark do not silently establish untested policy combinations, production
performance thresholds, C02 ranking, proof authority, S05 or O08 acceptance.
