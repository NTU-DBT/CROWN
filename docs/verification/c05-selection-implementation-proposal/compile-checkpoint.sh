#!/usr/bin/env bash
set -u
cd /home/userroot/Codex/CROWN
c05_packet=docs/verification/c05-selection-implementation-proposal
c05_output=${1:?distinct output directory required}
case "$c05_output" in /tmp/crown-c05-selection-implementation-*) ;; *) exit 2 ;; esac
mkdir -p "$c05_output/objects" "$c05_output/logs"
rg --files "$c05_packet/overlay" | LC_ALL=C sort > "$c05_output/source-paths.txt"
while IFS= read -r c05_path; do sha256sum "$c05_path"; done < "$c05_output/source-paths.txt" > "$c05_output/SOURCE_BEFORE_SHA256SUMS"
sha256sum src/planner/ranking_detail.hpp src/planner/ranking_payload.hpp include/crown/planner/ranking.hpp include/crown/runtime/ranking_evidence.hpp third_party/nlohmann/json.hpp /usr/bin/c++ > "$c05_output/NATIVE_COMPILER_SHA256SUMS"
: > "$c05_output/commands.sh"
: > "$c05_output/status.tsv"
c05_failed=0
for c05_relative in planner/selection.cpp planner/selection_budget.cpp planner/selection_binding.cpp planner/selection_payload.cpp planner/selection_cache.cpp runtime/selection.cpp; do
  c05_name=${c05_relative//\//_}
  c05_name=${c05_name%.cpp}
  c05_command=(/usr/bin/c++ -std=c++23 -O3 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror
    -I "$c05_packet/overlay/include" -I include -I "$c05_packet/overlay/src/planner" -I src/planner
    -isystem third_party -MMD -MF "$c05_output/objects/$c05_name.d"
    -c "$c05_packet/overlay/src/$c05_relative" -o "$c05_output/objects/$c05_name.o")
  printf '%q ' "${c05_command[@]}" >> "$c05_output/commands.sh"
  printf '\n' >> "$c05_output/commands.sh"
  "${c05_command[@]}" > "$c05_output/logs/$c05_name.stdout" 2> "$c05_output/logs/$c05_name.stderr"
  c05_status=$?
  printf '%s\t%s\n' "$c05_name" "$c05_status" >> "$c05_output/status.tsv"
  if [ "$c05_status" -ne 0 ]; then c05_failed=1; fi
done
while IFS= read -r c05_path; do sha256sum "$c05_path"; done < "$c05_output/source-paths.txt" > "$c05_output/SOURCE_AFTER_SHA256SUMS"
cmp "$c05_output/SOURCE_BEFORE_SHA256SUMS" "$c05_output/SOURCE_AFTER_SHA256SUMS" || c05_failed=1
cat "$c05_output/status.tsv"
exit "$c05_failed"
