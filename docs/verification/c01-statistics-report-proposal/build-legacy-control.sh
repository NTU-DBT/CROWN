#!/usr/bin/env bash
# Compile/link only. Uses one complete frozen production variant as the control.
set -euo pipefail
cd /home/userroot/Codex/CROWN
c01_out=${1:-/tmp/crown-c01-report-legacy-control}
c01_frozen=${2:-/tmp/crown-c01-combined-production}
case "$c01_out" in /tmp/crown-c01-report-*) ;; *) exit 2 ;; esac
mkdir -p "$c01_out"
c01_overlay=docs/verification/c01-statistics-combined-proposal/overlay
c01_flags=(-std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread
  -I "$c01_overlay/include" -I "$c01_overlay/src/runtime" -I "$c01_overlay/tests/unit"
  -I include -I src/runtime -I tests/reference -I tests/support -isystem third_party)
c01_names=(src_storage_reference.cpp src_runtime_statistics.cpp src_runtime_owner_statistics.cpp
  src_runtime_statistics_collection.cpp src_runtime_workload_statistics.cpp src_runtime_combined_statistics.cpp
  src_runtime_support.cpp src_runtime_physical.cpp src_runtime_delta.cpp src_runtime_session.cpp
  src_io_support.cpp src_io_inspection.cpp src_runtime_replay.cpp src_runtime_window.cpp src_runtime_observation.cpp
  compat_src_observability_explain.cpp compat_src_io_explain.cpp compat_src_io_run_context.cpp compat_src_io_cursor_observation.cpp)
c01_objects=()
for c01_name in "${c01_names[@]}"; do c01_objects+=("$c01_frozen/$c01_name.o"); done
sha256sum "${c01_objects[@]}" > "$c01_out/FROZEN_OBJECT_SHA256SUMS"
printf '#!/usr/bin/env bash\nset -euo pipefail\ncd /home/userroot/Codex/CROWN\n' > "$c01_out/commands.sh"
for c01_source in src/io/query_explain.cpp src/observability/query_explain.cpp docs/verification/c01-statistics-report-proposal/overlay/tests/unit/statistics_legacy_control.cpp; do
  c01_name=${c01_source##*/}
  if [[ "$c01_source" == src/observability/* ]]; then c01_name=observability_$c01_name; fi
  c01_object="$c01_out/$c01_name.o"
  printf '%q ' c++ "${c01_flags[@]}" -MMD -MF "$c01_out/$c01_name.d" -c "$c01_source" -o "$c01_object" >> "$c01_out/commands.sh"
  printf '\n' >> "$c01_out/commands.sh"
  if ! c++ "${c01_flags[@]}" -MMD -MF "$c01_out/$c01_name.d" -c "$c01_source" -o "$c01_object" > "$c01_out/$c01_name.log" 2>&1; then cat "$c01_out/$c01_name.log"; exit 1; fi
  c01_objects+=("$c01_object")
done
c01_archives=(build/release/libcrown_reference.a build/release/libcrown_plan.a build/release/libcrown_sql.a
  build/release/libcrown_core.a build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a)
sha256sum "${c01_archives[@]}" > "$c01_out/DEPENDENCY_SHA256SUMS"
printf '%q ' c++ "${c01_flags[@]}" "${c01_objects[@]}" -Wl,--start-group "${c01_archives[@]}" -Wl,--end-group -o "$c01_out/statistics_legacy_control" >> "$c01_out/commands.sh"
printf '\n' >> "$c01_out/commands.sh"
if ! c++ "${c01_flags[@]}" "${c01_objects[@]}" -Wl,--start-group "${c01_archives[@]}" -Wl,--end-group -o "$c01_out/statistics_legacy_control" > "$c01_out/link.log" 2>&1; then cat "$c01_out/link.log"; exit 1; fi
printf 'linked frozen-combined legacy control\n'
