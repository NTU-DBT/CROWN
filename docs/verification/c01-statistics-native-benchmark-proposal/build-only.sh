#!/usr/bin/env bash
set -eu

if [ "$#" -ne 1 ]; then
  printf '%s\n' "usage: $0 /tmp/crown-c01-native-benchmark-<label>" >&2
  exit 2
fi

build_root=$1
case "$build_root" in
  /tmp/crown-c01-native-benchmark-*) ;;
  *) printf '%s\n' "build output must be under /tmp/crown-c01-native-benchmark-*" >&2; exit 2 ;;
esac

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/../../.." && pwd)
overlay="$repo_root/docs/verification/c01-statistics-combined-proposal/overlay"
compiler=${CXX:-c++}
mkdir -p "$build_root"

common_flags=(
  -std=c++23 -O3 -DNDEBUG
  -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror
  -pthread
  -I"$overlay/include"
  -I"$overlay/src/runtime"
  -I"$repo_root/include"
  -I"$repo_root/src/runtime"
  -isystem "$repo_root/third_party"
)

compile_one() {
  source=$1
  stem=$2
  "$compiler" "${common_flags[@]}" -MMD -MF "$build_root/$stem.d" \
    -c "$repo_root/$source" -o "$build_root/$stem.o" \
    >"$build_root/$stem.log" 2>&1
}

compile_one \
  docs/verification/c01-statistics-native-benchmark-proposal/native_benchmark.cpp \
  native_benchmark
compile_one docs/verification/c01-statistics-combined-proposal/overlay/src/runtime/support.cpp runtime_support
compile_one docs/verification/c01-statistics-combined-proposal/overlay/src/runtime/physical.cpp runtime_physical
compile_one docs/verification/c01-statistics-combined-proposal/overlay/src/runtime/delta.cpp runtime_delta
compile_one src/io/support.cpp io_support
compile_one src/io/inspection.cpp io_inspection
compile_one src/runtime/replay.cpp runtime_replay
compile_one docs/verification/c01-statistics-combined-proposal/overlay/src/runtime/session.cpp runtime_session
compile_one src/runtime/window.cpp runtime_window
compile_one src/runtime/observation.cpp runtime_observation
compile_one docs/verification/c01-statistics-combined-proposal/overlay/src/runtime/statistics.cpp runtime_statistics
compile_one docs/verification/c01-statistics-combined-proposal/overlay/src/runtime/statistics_collection.cpp runtime_statistics_collection
compile_one docs/verification/c01-statistics-combined-proposal/overlay/src/runtime/owner_statistics.cpp runtime_owner_statistics
compile_one docs/verification/c01-statistics-combined-proposal/overlay/src/runtime/workload_statistics.cpp runtime_workload_statistics
compile_one docs/verification/c01-statistics-combined-proposal/overlay/src/runtime/combined_statistics.cpp runtime_combined_statistics
compile_one docs/verification/c01-statistics-combined-proposal/overlay/src/storage/reference.cpp storage_reference

"$compiler" -std=c++23 -O3 -DNDEBUG -Wall -Wextra -Wpedantic -Wconversion \
  -Wsign-conversion -Werror -pthread \
  "$build_root/native_benchmark.o" \
  "$build_root/runtime_support.o" \
  "$build_root/runtime_physical.o" \
  "$build_root/runtime_delta.o" \
  "$build_root/io_support.o" \
  "$build_root/io_inspection.o" \
  "$build_root/runtime_replay.o" \
  "$build_root/runtime_session.o" \
  "$build_root/runtime_window.o" \
  "$build_root/runtime_observation.o" \
  "$build_root/runtime_statistics.o" \
  "$build_root/runtime_statistics_collection.o" \
  "$build_root/runtime_owner_statistics.o" \
  "$build_root/runtime_workload_statistics.o" \
  "$build_root/runtime_combined_statistics.o" \
  "$build_root/storage_reference.o" \
  -Wl,--start-group \
  "$repo_root/build/release/libcrown_plan.a" \
  "$repo_root/build/release/libcrown_sql.a" \
  "$repo_root/build/release/libcrown_core.a" \
  "$repo_root/build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a" \
  -Wl,--end-group \
  -o "$build_root/crown_c01_native_benchmark" \
  >"$build_root/link.log" 2>&1
