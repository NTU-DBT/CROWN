#!/usr/bin/env bash
# Root alone invokes this targeted compile/link recipe. No binary execution.
set -u
cd /home/userroot/Codex/CROWN
c05_revision=docs/verification/c05-selection-independent-strict-revision-proposal
c05_original=docs/verification/c05-selection-independent-tests-proposal
c05_implementation=docs/verification/c05-selection-implementation-proposal
c05_closure=/tmp/crown-c05-selection-implementation-strict-3
c05_revision_output=${1:?fresh independent strict revision output required}
case "$c05_revision_output" in /tmp/crown-c05-selection-independent-strict-revision-*) ;; *) exit 2 ;; esac
if [ -e "$c05_revision_output" ]; then printf 'refusing existing output: %s\n' "$c05_revision_output" >&2; exit 2; fi
mkdir -p "$c05_revision_output/objects" "$c05_revision_output/logs" "$c05_revision_output/bin"
sha256sum --check --strict "$c05_revision/PACKAGE_SHA256SUMS" > "$c05_revision_output/package-check.log" 2>&1 || exit 2
sha256sum --check --strict "$c05_revision/INPUT_SHA256SUMS" > "$c05_revision_output/input-check.log" 2>&1 || exit 2
sha256sum --check --strict "$c05_revision/REUSED_ARTIFACT_SHA256SUMS" > "$c05_revision_output/reused-check.log" 2>&1 || exit 2
# The old package check hashes its INPUT manifest FILE without interpreting it.
sha256sum --check --strict "$c05_original/PACKAGE_SHA256SUMS" > "$c05_revision_output/original-package-check.log" 2>&1 || exit 2
: > "$c05_revision_output/commands.sh"
: > "$c05_revision_output/status.tsv"
c05_revision_failed=0
c05_revision_run() {
  local c05_revision_name=$1; shift
  printf '%q ' "$@" >> "$c05_revision_output/commands.sh"
  printf '\n' >> "$c05_revision_output/commands.sh"
  "$@" > "$c05_revision_output/logs/$c05_revision_name.stdout" 2> "$c05_revision_output/logs/$c05_revision_name.stderr"
  local c05_revision_status=$?
  printf '%s\t%s\n' "$c05_revision_name" "$c05_revision_status" >> "$c05_revision_output/status.tsv"
  if [ "$c05_revision_status" -ne 0 ]; then c05_revision_failed=1; fi
  return "$c05_revision_status"
}
c05_revision_tail=(build/release/libcrown_plan.a build/release/libcrown_sql.a
  build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a build/release/libcrown_core.a)
for c05_revision_name in selection_binding_independent selection_publication_fault_independent; do
  c05_revision_run "$c05_revision_name.compile" /usr/bin/c++ -std=c++23 -O3 -UNDEBUG \
    -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror \
    -I "$c05_implementation/overlay/include" -I include -I "$c05_original/tests" \
    -I "$c05_implementation/overlay/src/planner" -I src/planner -isystem third_party \
    -MD -MF "$c05_revision_output/objects/$c05_revision_name.d" \
    -c "$c05_revision/tests/${c05_revision_name}_test.cpp" -o "$c05_revision_output/objects/$c05_revision_name.o"
  c05_revision_compile_status=$?
  if [ "$c05_revision_compile_status" -ne 0 ]; then continue; fi
  if [ "$c05_revision_name" = selection_binding_independent ]; then
    c05_revision_libraries=("$c05_closure/lib/libcrown_selection.a" build/release/libcrown_ranking.a "${c05_revision_tail[@]}")
  else
    c05_revision_libraries=("$c05_closure/lib/libcrown_selection_runtime.a" "$c05_closure/lib/libcrown_selection.a"
      build/release/libcrown_ranking_runtime.a build/release/libcrown_ranking.a build/release/libcrown_runtime.a "${c05_revision_tail[@]}")
  fi
  c05_revision_run "$c05_revision_name.link" /usr/bin/c++ "$c05_revision_output/objects/$c05_revision_name.o" \
    -o "$c05_revision_output/bin/$c05_revision_name" "${c05_revision_libraries[@]}"
done
sha256sum --check --strict "$c05_revision/PACKAGE_SHA256SUMS" > "$c05_revision_output/package-after-check.log" 2>&1 || c05_revision_failed=1
sha256sum --check --strict "$c05_revision/INPUT_SHA256SUMS" > "$c05_revision_output/input-after-check.log" 2>&1 || c05_revision_failed=1
sha256sum --check --strict "$c05_revision/REUSED_ARTIFACT_SHA256SUMS" > "$c05_revision_output/reused-after-check.log" 2>&1 || c05_revision_failed=1
rg --files "$c05_revision_output/objects" "$c05_revision_output/bin" | LC_ALL=C sort > "$c05_revision_output/artifact-paths.txt"
while IFS= read -r c05_revision_path; do sha256sum "$c05_revision_path" || exit 2; done < "$c05_revision_output/artifact-paths.txt" > "$c05_revision_output/ARTIFACT_SHA256SUMS"
cat "$c05_revision_output/status.tsv"
exit "$c05_revision_failed"
