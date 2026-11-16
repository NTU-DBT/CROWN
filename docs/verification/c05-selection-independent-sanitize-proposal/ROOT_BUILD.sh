#!/usr/bin/env bash
# Frozen root-only recipe using the recorded matching sanitizer closure.
# It compiles/links consumers only and never executes a produced binary.
set -u
set -o pipefail
cd /home/userroot/Codex/CROWN
c05_san_packet=docs/verification/c05-selection-independent-sanitize-proposal
c05_san_consumer=docs/verification/c05-selection-independent-tests-proposal
c05_san_revision=docs/verification/c05-selection-independent-strict-revision-proposal
c05_san_cache=docs/verification/c05-selection-independent-cache-correction-proposal
c05_san_impl=docs/verification/c05-selection-implementation-proposal
c05_san_output=${1:?fresh independent sanitizer output directory required}
case "$c05_san_output" in /tmp/crown-c05-selection-independent-sanitize-*) ;; *) exit 2 ;; esac
if [ -e "$c05_san_output" ]; then printf 'refusing existing output: %s\n' "$c05_san_output" >&2; exit 2; fi
for c05_san_required in PACKAGE_SHA256SUMS INPUT_SHA256SUMS LINK_INPUT_SHA256SUMS SAN_CLOSURE_PATH.txt; do
  if [ ! -f "$c05_san_packet/$c05_san_required" ]; then printf 'sanitizer preparation is not frozen: %s\n' "$c05_san_required" >&2; exit 2; fi
done
IFS= read -r c05_san_closure < "$c05_san_packet/SAN_CLOSURE_PATH.txt" || exit 2
case "$c05_san_closure" in /tmp/crown-c05-selection-implementation-*sanitize*) ;; *) exit 2 ;; esac
mkdir -p "$c05_san_output/objects" "$c05_san_output/logs" "$c05_san_output/bin" || exit 2
sha256sum --check --strict "$c05_san_packet/PACKAGE_SHA256SUMS" > "$c05_san_output/package-check.log" 2>&1 || exit 2
sha256sum --check --strict "$c05_san_packet/INPUT_SHA256SUMS" > "$c05_san_output/input-check.log" 2>&1 || exit 2
sha256sum --check --strict "$c05_san_packet/LINK_INPUT_SHA256SUMS" > "$c05_san_output/link-input-check.log" 2>&1 || exit 2
# This checks only files inside the unchanged consumer packet, including the
# old INPUT manifest FILE. It does not interpret that old manifest's rows.
sha256sum --check --strict "$c05_san_consumer/PACKAGE_SHA256SUMS" > "$c05_san_output/consumer-package-check.log" 2>&1 || exit 2
sha256sum --check --strict "$c05_san_revision/PACKAGE_SHA256SUMS" > "$c05_san_output/revision-package-check.log" 2>&1 || exit 2
sha256sum --check --strict "$c05_san_cache/PACKAGE_SHA256SUMS" > "$c05_san_output/cache-package-check.log" 2>&1 || exit 2
c05_san_archives=(
  "$c05_san_closure/lib/libcrown_selection_runtime.a"
  "$c05_san_closure/lib/libcrown_selection.a"
  build/sanitize/libcrown_ranking_runtime.a build/sanitize/libcrown_ranking.a
  build/sanitize/libcrown_runtime.a build/sanitize/libcrown_plan.a
  build/sanitize/libcrown_sql.a build/sanitize/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a
  build/sanitize/libcrown_core.a)
printf '%s\n' "${c05_san_archives[@]}" /usr/bin/c++ > "$c05_san_output/link-input-paths.txt"
while IFS= read -r c05_san_path; do sha256sum "$c05_san_path" || exit 2; done < "$c05_san_output/link-input-paths.txt" > "$c05_san_output/LINK_INPUT_BEFORE_SHA256SUMS"
cmp "$c05_san_packet/LINK_INPUT_SHA256SUMS" "$c05_san_output/LINK_INPUT_BEFORE_SHA256SUMS" || exit 2
: > "$c05_san_output/commands.sh"
: > "$c05_san_output/status.tsv"
: > "$c05_san_output/targets.tsv"
c05_san_failed=0
c05_san_run() {
  local c05_san_name=$1; shift
  printf '%q ' "$@" >> "$c05_san_output/commands.sh"
  printf '\n' >> "$c05_san_output/commands.sh"
  "$@" > "$c05_san_output/logs/$c05_san_name.stdout" 2> "$c05_san_output/logs/$c05_san_name.stderr"
  local c05_san_status=$?
  printf '%s\t%s\n' "$c05_san_name" "$c05_san_status" >> "$c05_san_output/status.tsv"
  if [ "$c05_san_status" -ne 0 ]; then c05_san_failed=1; fi
  return "$c05_san_status"
}
for c05_san_name in selection_public_independent selection_cache_independent selection_resources_independent selection_binding_independent selection_publication_fault_independent; do
  case "$c05_san_name" in
    selection_cache_independent) c05_san_source="$c05_san_cache/tests/${c05_san_name}_test.cpp" ;;
    selection_binding_independent|selection_publication_fault_independent) c05_san_source="$c05_san_revision/tests/${c05_san_name}_test.cpp" ;;
    *) c05_san_source="$c05_san_consumer/tests/${c05_san_name}_test.cpp" ;;
  esac
  printf '%s\tsanitize\tproduction\t%s\n' "$c05_san_name" "$c05_san_source" >> "$c05_san_output/targets.tsv"
  c05_san_run "$c05_san_name.compile" /usr/bin/c++ -std=c++23 -g -UNDEBUG \
    -fsanitize=address,undefined -fno-omit-frame-pointer \
    -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror \
    -I "$c05_san_impl/overlay/include" -I include -I "$c05_san_consumer/tests" \
    -I "$c05_san_impl/overlay/src/planner" -I src/planner -isystem third_party \
    -MD -MF "$c05_san_output/objects/$c05_san_name.d" \
    -c "$c05_san_source" -o "$c05_san_output/objects/$c05_san_name.o"
  c05_san_compile_status=$?
  if [ "$c05_san_compile_status" -ne 0 ]; then continue; fi
  if [ "$c05_san_name" = selection_binding_independent ]; then
    c05_san_libraries=("$c05_san_closure/lib/libcrown_selection.a"
      build/sanitize/libcrown_ranking.a build/sanitize/libcrown_plan.a build/sanitize/libcrown_sql.a
      build/sanitize/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a build/sanitize/libcrown_core.a)
  else
    c05_san_libraries=("${c05_san_archives[@]}")
  fi
  c05_san_run "$c05_san_name.link" /usr/bin/c++ -g -fsanitize=address,undefined \
    "$c05_san_output/objects/$c05_san_name.o" -o "$c05_san_output/bin/$c05_san_name" "${c05_san_libraries[@]}"
done
while IFS= read -r c05_san_path; do sha256sum "$c05_san_path" || exit 2; done < "$c05_san_output/link-input-paths.txt" > "$c05_san_output/LINK_INPUT_AFTER_SHA256SUMS"
cmp "$c05_san_output/LINK_INPUT_BEFORE_SHA256SUMS" "$c05_san_output/LINK_INPUT_AFTER_SHA256SUMS" || c05_san_failed=1
sha256sum --check --strict "$c05_san_packet/PACKAGE_SHA256SUMS" > "$c05_san_output/package-after-check.log" 2>&1 || c05_san_failed=1
sha256sum --check --strict "$c05_san_packet/INPUT_SHA256SUMS" > "$c05_san_output/input-after-check.log" 2>&1 || c05_san_failed=1
sha256sum --check --strict "$c05_san_consumer/PACKAGE_SHA256SUMS" > "$c05_san_output/consumer-package-after-check.log" 2>&1 || c05_san_failed=1
sha256sum --check --strict "$c05_san_revision/PACKAGE_SHA256SUMS" > "$c05_san_output/revision-package-after-check.log" 2>&1 || c05_san_failed=1
sha256sum --check --strict "$c05_san_cache/PACKAGE_SHA256SUMS" > "$c05_san_output/cache-package-after-check.log" 2>&1 || c05_san_failed=1
rg --files "$c05_san_output/objects" "$c05_san_output/bin" | LC_ALL=C sort > "$c05_san_output/artifact-paths.txt" || exit 2
while IFS= read -r c05_san_path; do sha256sum "$c05_san_path" || exit 2; done < "$c05_san_output/artifact-paths.txt" > "$c05_san_output/ARTIFACT_SHA256SUMS"
cat "$c05_san_output/status.tsv"
exit "$c05_san_failed"
