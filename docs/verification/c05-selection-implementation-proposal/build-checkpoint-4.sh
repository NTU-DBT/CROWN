#!/usr/bin/env bash
# Root-only targeted rebuild. Reuse only exact verified checkpoint-3 artifacts.
set -eu
cd /home/userroot/Codex/CROWN
c05_packet=docs/verification/c05-selection-implementation-proposal
c05_prior=/tmp/crown-c05-selection-implementation-strict-3
c05_output=${1:?fresh output directory required}
c05_changed="$c05_packet/overlay/tests/unit/selection_binding_test.cpp"
case "$c05_output" in /tmp/crown-c05-selection-implementation-*) ;; *) exit 2 ;; esac
if [ -e "$c05_output" ]; then printf 'output already exists: %s\n' "$c05_output" >&2; exit 2; fi
mkdir -p "$c05_output/objects" "$c05_output/lib" "$c05_output/bin" "$c05_output/logs"
# Exactly this one consumer differs from the terminal prior source guard.
awk -v changed="$c05_changed" '$2 != changed {print}' "$c05_prior/INPUT_BEFORE_SHA256SUMS" > "$c05_output/REUSED_INPUT_SHA256SUMS"
sha256sum --check --quiet "$c05_output/REUSED_INPUT_SHA256SUMS"
sha256sum --check --quiet "$c05_prior/ARTIFACT_SHA256SUMS"
awk -F '\t' '($1 == "selection_binding.compile" || $1 == "selection_binding.link") {if ($2 != 1) exit 1; next} $2 != 0 {exit 1}' "$c05_prior/status.tsv"
sha256sum "$c05_prior/INPUT_BEFORE_SHA256SUMS" "$c05_prior/INPUT_AFTER_SHA256SUMS" \
  "$c05_prior/ARTIFACT_SHA256SUMS" "$c05_prior/commands.sh" "$c05_prior/status.tsv" "$c05_prior/targets.tsv" \
  "$c05_prior/source-paths.txt" "$c05_packet/build-checkpoint-3.sh" /usr/bin/c++ /usr/bin/ar > "$c05_output/PROVENANCE_SHA256SUMS"
sha256sum "$c05_changed" "$c05_packet/build-checkpoint-4.sh" > "$c05_output/CHANGED_BEFORE_SHA256SUMS"
cp "$c05_prior/objects/"*.o "$c05_output/objects/"
for c05_dependency in "$c05_prior/objects/"*.d; do
  case "$c05_dependency" in */selection_binding.d) ;; *) cp "$c05_dependency" "$c05_output/objects/" ;; esac
done
cp "$c05_prior/lib/"*.a "$c05_output/lib/"
cp "$c05_prior/bin/"* "$c05_output/bin/"
cp "$c05_prior/commands.sh" "$c05_output/REUSED_COMMANDS.sh"
cp "$c05_prior/status.tsv" "$c05_output/REUSED_STATUS.tsv"
cp "$c05_prior/targets.tsv" "$c05_output/REUSED_TARGETS.tsv"
: > "$c05_output/commands.sh"; : > "$c05_output/status.tsv"
c05_run() {
  local c05_label=$1; shift
  printf '%q ' "$@" >> "$c05_output/commands.sh"; printf '\n' >> "$c05_output/commands.sh"
  local c05_status=0
  "$@" > "$c05_output/logs/$c05_label.stdout" 2> "$c05_output/logs/$c05_label.stderr" || c05_status=$?
  printf '%s\t%s\n' "$c05_label" "$c05_status" >> "$c05_output/status.tsv"
  return "$c05_status"
}
c05_run selection_binding.compile /usr/bin/c++ -std=c++23 -O3 -UNDEBUG \
  -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror \
  -I "$c05_packet/overlay/include" -I include -I "$c05_packet/overlay/src/planner" -I src/planner \
  -I "$c05_packet/overlay/tests/support" -I tests/support -isystem third_party -MD \
  -MF "$c05_output/objects/selection_binding.d" -c "$c05_changed" -o "$c05_output/objects/selection_binding.o"
c05_run selection_binding.link /usr/bin/c++ "$c05_output/objects/selection_binding.o" -o "$c05_output/bin/selection_binding" \
  "$c05_output/lib/libcrown_selection_runtime.a" "$c05_output/lib/libcrown_selection.a" \
  build/release/libcrown_ranking_runtime.a build/release/libcrown_ranking.a build/release/libcrown_runtime.a \
  build/release/libcrown_plan.a build/release/libcrown_sql.a \
  build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a build/release/libcrown_core.a
sha256sum --check --quiet "$c05_output/REUSED_INPUT_SHA256SUMS"
sha256sum --check --quiet "$c05_prior/ARTIFACT_SHA256SUMS"
sha256sum --check --quiet "$c05_output/PROVENANCE_SHA256SUMS"
sha256sum "$c05_changed" "$c05_packet/build-checkpoint-4.sh" > "$c05_output/CHANGED_AFTER_SHA256SUMS"
cmp "$c05_output/CHANGED_BEFORE_SHA256SUMS" "$c05_output/CHANGED_AFTER_SHA256SUMS"
rg --files "$c05_packet/overlay" | LC_ALL=C sort > "$c05_output/source-paths.txt"
while IFS= read -r c05_path; do sha256sum "$c05_path"; done < "$c05_output/source-paths.txt" > "$c05_output/CURRENT_SOURCE_SHA256SUMS"
rg --files "$c05_output/objects" "$c05_output/lib" "$c05_output/bin" | LC_ALL=C sort > "$c05_output/artifact-paths.txt"
while IFS= read -r c05_path; do sha256sum "$c05_path"; done < "$c05_output/artifact-paths.txt" > "$c05_output/ARTIFACT_SHA256SUMS"
cat "$c05_output/status.tsv"
