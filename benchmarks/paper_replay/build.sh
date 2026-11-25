#!/usr/bin/env bash
# Build the paper replay harnesses against the static libraries of one CMake
# build directory. Usage: build.sh BUILD_DIR OUT_DIR
set -euo pipefail
R=/home/userroot/Codex/CROWN
B=$(realpath "$1"); OUT=$(realpath -m "$2"); HERE=$(dirname "$(realpath "$0")")
mkdir -p "$OUT"
make -C "$B" -j48 crown_flat crown_runtime crown_plan crown_sql crown_storage_table crown_indexed \
  crown_accounted_plan_storage crown_accounted_storage_table crown_accounted_indexed crown_core \
  crown_fallback crown_aggregate crown_sql_aggregate crown_sql_aggregate_runtime crown_sql_rows >/dev/null
CXX_FLAGS=(-std=c++23 -O3 -g -fno-omit-frame-pointer -DNDEBUG -no-pie -I"$R/include"
  -I"$R/examples/component-runtime" -isystem "$R/third_party")
CORE=("$B/libcrown_flat.a" "$B/libcrown_runtime.a" "$B/libcrown_plan.a" "$B/libcrown_sql.a"
  "$B/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a" "$B/libcrown_storage_table.a"
  "$B/libcrown_indexed.a" "$B/libcrown_accounted_plan_storage.a" "$B/libcrown_accounted_storage_table.a"
  "$B/libcrown_accounted_indexed.a" "$B/libcrown_core.a")
build() {  # name source extra-libs...
  local name=$1 src=$2; shift 2
  g++ "${CXX_FLAGS[@]}" "$HERE/$src" "$HERE/sampler.cpp" -o "$OUT/$name" "$@" "${CORE[@]}" -lz -lpthread &
}
build paper_native_routed native_replay_routed.cpp
build paper_native_snb native_replay_snb.cpp
build paper_native_fallback native_replay_fallback.cpp "$B/libcrown_fallback.a"
build paper_native_aggregate native_replay_aggregate.cpp "$B/libcrown_sql_aggregate_runtime.a" \
  "$B/libcrown_sql_aggregate.a" "$B/libcrown_aggregate.a" "$B/libcrown_sql_rows.a"
wait
ls -la "$OUT"
