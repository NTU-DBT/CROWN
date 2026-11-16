#!/usr/bin/env bash
# Direct compile/link only. This script never executes a project binary.
set -euo pipefail
cd /home/userroot/Codex/CROWN
c01_out=${1:-/tmp/crown-c01-online-root-normal}
case "$c01_out" in /tmp/crown-c01-online-*) ;; *) exit 2 ;; esac
mkdir -p "$c01_out"
c01_overlay=docs/verification/c01-statistics-online-proposal/overlay
c01_compiler=${CXX:-c++}
c01_flags=(-std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror
  -UNDEBUG -DCROWN_RUNTIME_TESTING -O0 -g -pthread
  -I "$c01_overlay/include" -I "$c01_overlay/src/runtime" -I "$c01_overlay/tests/unit"
  -I include -I third_party -I tests/support -I src/runtime)
c01_sources=("$c01_overlay/src/runtime/support.cpp" "$c01_overlay/src/runtime/physical.cpp"
  "$c01_overlay/src/runtime/delta.cpp" "$c01_overlay/src/runtime/session.cpp"
  "$c01_overlay/src/runtime/statistics_collection.cpp" "$c01_overlay/src/runtime/workload_statistics.cpp"
  src/io/support.cpp src/io/inspection.cpp src/runtime/replay.cpp src/runtime/window.cpp src/runtime/observation.cpp)
c01_objects=()
for c01_source in "${c01_sources[@]}"; do
  c01_name=${c01_source#"$c01_overlay/"}
  c01_name=${c01_name//\//_}
  c01_object="$c01_out/$c01_name.o"
  "$c01_compiler" "${c01_flags[@]}" -MMD -MF "$c01_out/$c01_name.d" -c "$c01_source" -o "$c01_object" > "$c01_out/$c01_name.log" 2>&1 || {
    cat "$c01_out/$c01_name.log"; exit 1;
  }
  c01_objects+=("$c01_object")
done
c01_archives=(build/release/libcrown_plan.a build/release/libcrown_sql.a build/release/libcrown_core.a
  build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a)
for c01_test in statistics_collection_test workload_statistics_test workload_statistics_exception_test; do
  "$c01_compiler" "${c01_flags[@]}" -MMD -MF "$c01_out/$c01_test.d" -c "$c01_overlay/tests/unit/$c01_test.cpp" \
    -o "$c01_out/$c01_test.o" > "$c01_out/$c01_test.log" 2>&1 || { cat "$c01_out/$c01_test.log"; exit 1; }
  "$c01_compiler" "${c01_flags[@]}" "${c01_objects[@]}" "$c01_out/$c01_test.o" \
    -Wl,--start-group "${c01_archives[@]}" -Wl,--end-group -o "$c01_out/$c01_test" \
    > "$c01_out/$c01_test-link.log" 2>&1 || { cat "$c01_out/$c01_test-link.log"; exit 1; }
done
