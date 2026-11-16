#!/usr/bin/env bash
# Root-owned direct compiler/archive/link recipe. Never runs a produced binary.
set -u
cd /home/userroot/Codex/CROWN
c05_packet=docs/verification/c05-selection-implementation-proposal
c05_output=${1:?distinct output directory required}
c05_variant=${2:?strict or sanitize required}
case "$c05_output" in /tmp/crown-c05-selection-implementation-*) ;; *) exit 2 ;; esac
case "$c05_variant" in
  strict) c05_native=build/release; c05_flags=(-O3 -UNDEBUG); c05_link_flags=() ;;
  sanitize) c05_native=build/sanitize; c05_flags=(-g -UNDEBUG -fsanitize=address,undefined -fno-omit-frame-pointer); c05_link_flags=(-g -fsanitize=address,undefined) ;;
  *) exit 2 ;;
esac
if [ -e "$c05_output" ]; then printf 'output already exists: %s\n' "$c05_output" >&2; exit 2; fi
mkdir -p "$c05_output/objects" "$c05_output/logs" "$c05_output/lib" "$c05_output/bin"
rg --files "$c05_packet/overlay" include src tests/support | LC_ALL=C sort > "$c05_output/source-paths.txt"
printf '%s\n' "$c05_packet/build-checkpoint.sh" build/verification/ranking-execution-freeze.json \
  build/verification/c05-selection-design-root-review-2026-11-07.json third_party/nlohmann/json.hpp \
  "$c05_native/compile_commands.json" /usr/bin/c++ /usr/bin/ar >> "$c05_output/source-paths.txt"
c05_archives=("$c05_native/libcrown_ranking_runtime.a" "$c05_native/libcrown_ranking_runtime_testing.a"
  "$c05_native/libcrown_ranking.a" "$c05_native/libcrown_runtime.a" "$c05_native/libcrown_runtime_testing.a"
  "$c05_native/libcrown_plan.a" "$c05_native/libcrown_sql.a"
  "$c05_native/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a" "$c05_native/libcrown_core.a")
printf '%s\n' "${c05_archives[@]}" >> "$c05_output/source-paths.txt"
while IFS= read -r c05_path; do sha256sum "$c05_path"; done < "$c05_output/source-paths.txt" > "$c05_output/INPUT_BEFORE_SHA256SUMS" || exit 2
: > "$c05_output/commands.sh"; : > "$c05_output/status.tsv"; : > "$c05_output/targets.tsv"
c05_failed=0
c05_run() {
  local c05_name=$1; shift
  printf '%q ' "$@" >> "$c05_output/commands.sh"; printf '\n' >> "$c05_output/commands.sh"
  "$@" > "$c05_output/logs/$c05_name.stdout" 2> "$c05_output/logs/$c05_name.stderr"
  local c05_status=$?
  printf '%s\t%s\n' "$c05_name" "$c05_status" >> "$c05_output/status.tsv"
  if [ "$c05_status" -ne 0 ]; then c05_failed=1; fi
  return "$c05_status"
}
c05_compile() {
  local c05_name=$1 c05_source=$2 c05_macro=$3
  local c05_definitions=()
  if [ "$c05_macro" = testing ]; then c05_definitions=(-DCROWN_RUNTIME_TESTING=1); fi
  printf '%s\t%s\t%s\t%s\n' "$c05_name" "$c05_variant" "$c05_macro" "$c05_source" >> "$c05_output/targets.tsv"
  c05_run "$c05_name.compile" /usr/bin/c++ -std=c++23 "${c05_flags[@]}" \
    -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror "${c05_definitions[@]}" \
    -I "$c05_packet/overlay/include" -I include -I "$c05_packet/overlay/src/planner" -I src/planner \
    -I "$c05_packet/overlay/tests/support" -I tests/support -isystem third_party \
    -MMD -MF "$c05_output/objects/$c05_name.d" -c "$c05_source" -o "$c05_output/objects/$c05_name.o"
}
c05_pure=()
for c05_unit in selection selection_budget selection_binding selection_payload selection_cache; do
  c05_compile "planner_$c05_unit" "$c05_packet/overlay/src/planner/$c05_unit.cpp" production
  c05_pure+=("$c05_output/objects/planner_$c05_unit.o")
done
c05_compile runtime_selection "$c05_packet/overlay/src/runtime/selection.cpp" production
c05_compile runtime_selection_testing "$c05_packet/overlay/src/runtime/selection.cpp" testing
c05_run pure.archive /usr/bin/ar rcs "$c05_output/lib/libcrown_selection.a" "${c05_pure[@]}"
c05_run runtime.archive /usr/bin/ar rcs "$c05_output/lib/libcrown_selection_runtime.a" "$c05_output/objects/runtime_selection.o"
c05_run runtime_testing.archive /usr/bin/ar rcs "$c05_output/lib/libcrown_selection_runtime_testing.a" "$c05_output/objects/runtime_selection_testing.o"
c05_tail=("$c05_native/libcrown_plan.a" "$c05_native/libcrown_sql.a" \
  "$c05_native/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a" "$c05_native/libcrown_core.a")
for c05_test in pure_link contract cache source current binding resources census exception normalized_exception; do
  c05_name="selection_$c05_test"
  c05_macro=production
  if [ "$c05_test" = census ]; then c05_macro=testing; fi
  c05_compile "$c05_name" "$c05_packet/overlay/tests/unit/${c05_name}_test.cpp" "$c05_macro"
  if [ "$c05_test" = pure_link ]; then
    c05_libraries=("$c05_output/lib/libcrown_selection.a" "$c05_native/libcrown_ranking.a" "${c05_tail[@]}")
  elif [ "$c05_macro" = testing ]; then
    c05_libraries=("$c05_output/lib/libcrown_selection_runtime_testing.a" "$c05_output/lib/libcrown_selection.a"
      "$c05_native/libcrown_ranking_runtime_testing.a" "$c05_native/libcrown_ranking.a" "$c05_native/libcrown_runtime_testing.a" "${c05_tail[@]}")
  else
    c05_libraries=("$c05_output/lib/libcrown_selection_runtime.a" "$c05_output/lib/libcrown_selection.a"
      "$c05_native/libcrown_ranking_runtime.a" "$c05_native/libcrown_ranking.a" "$c05_native/libcrown_runtime.a" "${c05_tail[@]}")
  fi
  c05_run "$c05_name.link" /usr/bin/c++ "${c05_link_flags[@]}" "$c05_output/objects/$c05_name.o" \
    -o "$c05_output/bin/$c05_name" "${c05_libraries[@]}"
done
c05_compile selection_api "$c05_packet/overlay/examples/selection_api.cpp" production
c05_compile selection_api_testing "$c05_packet/overlay/examples/selection_api.cpp" testing
while IFS= read -r c05_path; do sha256sum "$c05_path"; done < "$c05_output/source-paths.txt" > "$c05_output/INPUT_AFTER_SHA256SUMS" || c05_failed=1
cmp "$c05_output/INPUT_BEFORE_SHA256SUMS" "$c05_output/INPUT_AFTER_SHA256SUMS" || c05_failed=1
rg --files "$c05_output/objects" "$c05_output/lib" "$c05_output/bin" | LC_ALL=C sort > "$c05_output/artifact-paths.txt"
while IFS= read -r c05_path; do sha256sum "$c05_path"; done < "$c05_output/artifact-paths.txt" > "$c05_output/ARTIFACT_SHA256SUMS"
cat "$c05_output/status.tsv"
exit "$c05_failed"
