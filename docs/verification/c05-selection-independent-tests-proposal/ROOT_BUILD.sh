#!/usr/bin/env bash
# Source authoring only: root owns every invocation of this recipe.
# Compiles/links consumers only; never executes a produced binary.
set -u
cd /home/userroot/Codex/CROWN
c05_independent_packet=docs/verification/c05-selection-independent-tests-proposal
c05_independent_impl=docs/verification/c05-selection-implementation-proposal
c05_independent_closure=${1:?matching complete implementation closure required}
c05_independent_output=${2:?fresh independent output directory required}
c05_independent_variant=${3:?strict or sanitize required}
case "$c05_independent_closure" in /tmp/crown-c05-selection-implementation-*) ;; *) exit 2 ;; esac
case "$c05_independent_output" in /tmp/crown-c05-selection-independent-*) ;; *) exit 2 ;; esac
case "$c05_independent_variant" in
  strict) c05_independent_native=build/release; c05_independent_flags=(-O3 -UNDEBUG); c05_independent_link_flags=() ;;
  sanitize) c05_independent_native=build/sanitize; c05_independent_flags=(-g -UNDEBUG -fsanitize=address,undefined -fno-omit-frame-pointer); c05_independent_link_flags=(-g -fsanitize=address,undefined) ;;
  *) exit 2 ;;
esac
if [ -e "$c05_independent_output" ]; then printf 'refusing existing output: %s\n' "$c05_independent_output" >&2; exit 2; fi
mkdir -p "$c05_independent_output/objects" "$c05_independent_output/logs" "$c05_independent_output/bin"
sha256sum --check --strict "$c05_independent_packet/PACKAGE_SHA256SUMS" > "$c05_independent_output/package-check.log" 2>&1 || exit 2
sha256sum --check --strict "$c05_independent_packet/INPUT_SHA256SUMS" > "$c05_independent_output/input-check.log" 2>&1 || exit 2
# The implementation archives must already have a successful root-owned build
# for these exact held headers/sources and this variant. Preserve that receipt;
# this recipe does not rebuild them or infer provenance from archive filenames.
c05_independent_archives=(
  "$c05_independent_closure/lib/libcrown_selection_runtime.a"
  "$c05_independent_closure/lib/libcrown_selection.a"
  "$c05_independent_native/libcrown_ranking_runtime.a"
  "$c05_independent_native/libcrown_ranking.a"
  "$c05_independent_native/libcrown_runtime.a"
  "$c05_independent_native/libcrown_plan.a"
  "$c05_independent_native/libcrown_sql.a"
  "$c05_independent_native/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a"
  "$c05_independent_native/libcrown_core.a")
printf '%s\n' "${c05_independent_archives[@]}" /usr/bin/c++ > "$c05_independent_output/link-input-paths.txt"
while IFS= read -r c05_independent_path; do sha256sum "$c05_independent_path" || exit 2; done < "$c05_independent_output/link-input-paths.txt" > "$c05_independent_output/LINK_INPUT_BEFORE_SHA256SUMS" || exit 2
: > "$c05_independent_output/commands.sh"
: > "$c05_independent_output/status.tsv"
c05_independent_failed=0
c05_independent_run() {
  local c05_independent_name=$1; shift
  printf '%q ' "$@" >> "$c05_independent_output/commands.sh"
  printf '\n' >> "$c05_independent_output/commands.sh"
  "$@" > "$c05_independent_output/logs/$c05_independent_name.stdout" 2> "$c05_independent_output/logs/$c05_independent_name.stderr"
  local c05_independent_status=$?
  printf '%s\t%s\n' "$c05_independent_name" "$c05_independent_status" >> "$c05_independent_output/status.tsv"
  if [ "$c05_independent_status" -ne 0 ]; then c05_independent_failed=1; fi
  return "$c05_independent_status"
}
for c05_independent_name in selection_public_independent selection_cache_independent selection_resources_independent selection_binding_independent selection_publication_fault_independent; do
  c05_independent_run "$c05_independent_name.compile" /usr/bin/c++ -std=c++23 "${c05_independent_flags[@]}" \
    -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror \
    -I "$c05_independent_impl/overlay/include" -I include \
    -I "$c05_independent_packet/tests" -I "$c05_independent_impl/overlay/src/planner" -I src/planner \
    -isystem third_party -MD -MF "$c05_independent_output/objects/$c05_independent_name.d" \
    -c "$c05_independent_packet/tests/${c05_independent_name}_test.cpp" \
    -o "$c05_independent_output/objects/$c05_independent_name.o"
  c05_independent_compile_status=$?
  if [ "$c05_independent_compile_status" -ne 0 ]; then continue; fi
  if [ "$c05_independent_name" = selection_binding_independent ]; then
    c05_independent_libraries=("$c05_independent_closure/lib/libcrown_selection.a"
      "$c05_independent_native/libcrown_ranking.a" "$c05_independent_native/libcrown_plan.a"
      "$c05_independent_native/libcrown_sql.a" "$c05_independent_native/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a"
      "$c05_independent_native/libcrown_core.a")
  else
    c05_independent_libraries=("${c05_independent_archives[@]}")
  fi
  c05_independent_run "$c05_independent_name.link" /usr/bin/c++ "${c05_independent_link_flags[@]}" \
    "$c05_independent_output/objects/$c05_independent_name.o" -o "$c05_independent_output/bin/$c05_independent_name" \
    "${c05_independent_libraries[@]}"
done
while IFS= read -r c05_independent_path; do sha256sum "$c05_independent_path" || exit 2; done < "$c05_independent_output/link-input-paths.txt" > "$c05_independent_output/LINK_INPUT_AFTER_SHA256SUMS" || c05_independent_failed=1
cmp "$c05_independent_output/LINK_INPUT_BEFORE_SHA256SUMS" "$c05_independent_output/LINK_INPUT_AFTER_SHA256SUMS" || c05_independent_failed=1
sha256sum --check --strict "$c05_independent_packet/PACKAGE_SHA256SUMS" > "$c05_independent_output/package-after-check.log" 2>&1 || c05_independent_failed=1
sha256sum --check --strict "$c05_independent_packet/INPUT_SHA256SUMS" > "$c05_independent_output/input-after-check.log" 2>&1 || c05_independent_failed=1
rg --files "$c05_independent_output/objects" "$c05_independent_output/bin" | LC_ALL=C sort > "$c05_independent_output/artifact-paths.txt"
while IFS= read -r c05_independent_path; do sha256sum "$c05_independent_path" || exit 2; done < "$c05_independent_output/artifact-paths.txt" > "$c05_independent_output/ARTIFACT_SHA256SUMS" || c05_independent_failed=1
cat "$c05_independent_output/status.tsv"
exit "$c05_independent_failed"
