#!/usr/bin/env bash
# Direct compile/link only. Never executes a project test or diagnostic.
set -euo pipefail
cd /home/userroot/Codex/CROWN
c01_out=${1:-/tmp/crown-c01-report-production}
c01_variant=${2:-production}
c01_dependencies=${3:-build/release}
c01_mode=${4:-strict}
case "$c01_out" in /tmp/crown-c01-report-*) ;; *) exit 2 ;; esac
case "$c01_variant" in production|testing) ;; *) exit 2 ;; esac
case "$c01_mode" in strict|sanitized) ;; *) exit 2 ;; esac
mkdir -p "$c01_out"
c01_overlay=docs/verification/c01-statistics-report-proposal/overlay
c01_flags=(-std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread
  -I "$c01_overlay/include" -I "$c01_overlay/src/runtime" -I "$c01_overlay/tests/unit" -I "$c01_overlay/tests/support"
  -I include -I src/runtime -I tests/reference -I tests/support -isystem third_party)
if [[ "$c01_variant" == testing ]]; then c01_flags+=(-DCROWN_RUNTIME_TESTING); fi
if [[ "$c01_mode" == sanitized ]]; then c01_flags+=(-O1 -fsanitize=address,undefined -fno-omit-frame-pointer); fi
c01_sources=("$c01_overlay/src/storage/reference.cpp" "$c01_overlay/src/runtime/statistics.cpp"
  "$c01_overlay/src/runtime/owner_statistics.cpp" "$c01_overlay/src/runtime/statistics_collection.cpp"
  "$c01_overlay/src/runtime/workload_statistics.cpp" "$c01_overlay/src/runtime/combined_statistics.cpp"
  "$c01_overlay/src/runtime/support.cpp" "$c01_overlay/src/runtime/physical.cpp"
  "$c01_overlay/src/runtime/delta.cpp" "$c01_overlay/src/runtime/session.cpp"
  src/io/support.cpp src/io/inspection.cpp src/runtime/replay.cpp src/runtime/window.cpp src/runtime/observation.cpp
  "$c01_overlay/src/observability/explain.cpp" "$c01_overlay/src/observability/statistics_explain.cpp" "$c01_overlay/src/io/statistics_explain.cpp"
  src/io/explain.cpp src/io/run_context.cpp src/io/cursor_observation.cpp src/io/query_explain.cpp src/observability/query_explain.cpp)
c01_objects=()
printf '#!/usr/bin/env bash\nset -euo pipefail\ncd /home/userroot/Codex/CROWN\n' > "$c01_out/commands.sh"
for c01_source in "${c01_sources[@]}"; do
  c01_name=${c01_source#"$c01_overlay/"}
  c01_name=${c01_name//\//_}
  c01_object="$c01_out/$c01_name.o"
  printf '%q ' c++ "${c01_flags[@]}" -MMD -MF "$c01_out/$c01_name.d" -c "$c01_source" -o "$c01_object" >> "$c01_out/commands.sh"
  printf '\n' >> "$c01_out/commands.sh"
  if ! c++ "${c01_flags[@]}" -MMD -MF "$c01_out/$c01_name.d" -c "$c01_source" -o "$c01_object" > "$c01_out/$c01_name.log" 2>&1; then
    cat "$c01_out/$c01_name.log"
    exit 1
  fi
  printf 'compiled %s %s\n' "$c01_variant" "$c01_source"
  c01_objects+=("$c01_object")
done
c01_archives=("$c01_dependencies/libcrown_reference.a" "$c01_dependencies/libcrown_plan.a"
  "$c01_dependencies/libcrown_sql.a" "$c01_dependencies/libcrown_core.a"
  "$c01_dependencies/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a")
sha256sum "${c01_archives[@]}" > "$c01_out/DEPENDENCY_SHA256SUMS"
if [[ "$c01_variant" == production ]]; then
  c01_tests=(statistics_explain_test statistics_explain_exception_test statistics_legacy_control combined_statistics_test statistics_runtime_only_test)
else
  c01_tests=(statistics_explain_test statistics_explain_exception_test statistics_legacy_control combined_statistics_test workload_statistics_test statistics_runtime_only_test)
fi
for c01_test in "${c01_tests[@]}"; do
  printf '%q ' c++ "${c01_flags[@]}" -MMD -MF "$c01_out/$c01_test.d" -c "$c01_overlay/tests/unit/$c01_test.cpp" -o "$c01_out/$c01_test.o" >> "$c01_out/commands.sh"
  printf '\n' >> "$c01_out/commands.sh"
  if ! c++ "${c01_flags[@]}" -MMD -MF "$c01_out/$c01_test.d" -c "$c01_overlay/tests/unit/$c01_test.cpp" -o "$c01_out/$c01_test.o" > "$c01_out/$c01_test.log" 2>&1; then
    cat "$c01_out/$c01_test.log"
    exit 1
  fi
  c01_link_objects=("${c01_objects[@]}")
  # The first 15 units are the complete runtime-only closure. This consumer
  # must link with zero observability or report-IO objects.
  if [[ "$c01_test" == statistics_runtime_only_test ]]; then c01_link_objects=("${c01_objects[@]:0:15}"); fi
  printf '%q ' c++ "${c01_flags[@]}" "${c01_link_objects[@]}" "$c01_out/$c01_test.o" -Wl,--start-group "${c01_archives[@]}" -Wl,--end-group -o "$c01_out/$c01_test" >> "$c01_out/commands.sh"
  printf '\n' >> "$c01_out/commands.sh"
  if ! c++ "${c01_flags[@]}" "${c01_link_objects[@]}" "$c01_out/$c01_test.o" -Wl,--start-group "${c01_archives[@]}" -Wl,--end-group -o "$c01_out/$c01_test" > "$c01_out/$c01_test-link.log" 2>&1; then
    cat "$c01_out/$c01_test-link.log"
    exit 1
  fi
  printf 'linked %s %s\n' "$c01_variant" "$c01_test"
done
