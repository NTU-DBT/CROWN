#!/usr/bin/env bash
# Root-only targeted compile/link; this recipe never runs the correction.
set -u
set -o pipefail
cd /home/userroot/Codex/CROWN
c05_fix_packet=docs/verification/c05-selection-independent-cache-correction-proposal
c05_fix_original=docs/verification/c05-selection-independent-tests-proposal
c05_fix_impl=docs/verification/c05-selection-implementation-proposal
c05_fix_closure=/tmp/crown-c05-selection-implementation-strict-3
c05_fix_output=${1:?fresh correction output directory required}
case "$c05_fix_output" in /tmp/crown-c05-selection-independent-cache-correction-*) ;; *) exit 2 ;; esac
if [ -e "$c05_fix_output" ]; then printf 'refusing existing output: %s\n' "$c05_fix_output" >&2; exit 2; fi
mkdir -p "$c05_fix_output/objects" "$c05_fix_output/logs" "$c05_fix_output/bin" || exit 2
sha256sum --check --strict "$c05_fix_packet/PACKAGE_SHA256SUMS" > "$c05_fix_output/package-check.log" 2>&1 || exit 2
sha256sum --check --strict "$c05_fix_packet/INPUT_SHA256SUMS" > "$c05_fix_output/input-check.log" 2>&1 || exit 2
sha256sum --check --strict "$c05_fix_packet/LINK_INPUT_SHA256SUMS" > "$c05_fix_output/link-check.log" 2>&1 || exit 2
: > "$c05_fix_output/commands.sh"
: > "$c05_fix_output/status.tsv"
c05_fix_failed=0
c05_fix_run() {
  local c05_fix_name=$1; shift
  printf '%q ' "$@" >> "$c05_fix_output/commands.sh"
  printf '\n' >> "$c05_fix_output/commands.sh"
  "$@" > "$c05_fix_output/logs/$c05_fix_name.stdout" 2> "$c05_fix_output/logs/$c05_fix_name.stderr"
  local c05_fix_status=$?
  printf '%s\t%s\n' "$c05_fix_name" "$c05_fix_status" >> "$c05_fix_output/status.tsv"
  if [ "$c05_fix_status" -ne 0 ]; then c05_fix_failed=1; fi
  return "$c05_fix_status"
}
c05_fix_run compile /usr/bin/c++ -std=c++23 -O3 -UNDEBUG \
  -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror \
  -I "$c05_fix_impl/overlay/include" -I include -I "$c05_fix_original/tests" \
  -I "$c05_fix_impl/overlay/src/planner" -I src/planner -isystem third_party \
  -MD -MF "$c05_fix_output/objects/selection_cache_independent.d" \
  -c "$c05_fix_packet/tests/selection_cache_independent_test.cpp" \
  -o "$c05_fix_output/objects/selection_cache_independent.o"
c05_fix_compile_status=$?
if [ "$c05_fix_compile_status" -eq 0 ]; then
  c05_fix_run link /usr/bin/c++ "$c05_fix_output/objects/selection_cache_independent.o" \
    -o "$c05_fix_output/bin/selection_cache_independent" \
    "$c05_fix_closure/lib/libcrown_selection_runtime.a" "$c05_fix_closure/lib/libcrown_selection.a" \
    build/release/libcrown_ranking_runtime.a build/release/libcrown_ranking.a \
    build/release/libcrown_runtime.a build/release/libcrown_plan.a build/release/libcrown_sql.a \
    build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a build/release/libcrown_core.a
fi
sha256sum --check --strict "$c05_fix_packet/PACKAGE_SHA256SUMS" > "$c05_fix_output/package-after-check.log" 2>&1 || c05_fix_failed=1
sha256sum --check --strict "$c05_fix_packet/INPUT_SHA256SUMS" > "$c05_fix_output/input-after-check.log" 2>&1 || c05_fix_failed=1
sha256sum --check --strict "$c05_fix_packet/LINK_INPUT_SHA256SUMS" > "$c05_fix_output/link-after-check.log" 2>&1 || c05_fix_failed=1
rg --files "$c05_fix_output/objects" "$c05_fix_output/bin" | LC_ALL=C sort > "$c05_fix_output/artifact-paths.txt" || exit 2
while IFS= read -r c05_fix_path; do sha256sum "$c05_fix_path" || exit 2; done < "$c05_fix_output/artifact-paths.txt" > "$c05_fix_output/ARTIFACT_SHA256SUMS"
cat "$c05_fix_output/status.tsv"
exit "$c05_fix_failed"
