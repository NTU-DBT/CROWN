#!/usr/bin/env bash
# Supplemental compile/link only; preserves the strict-1 held recipe/artifacts.
set -euo pipefail
c02_mode=${1:?strict or sanitize}
c02_out=${2:?distinct /tmp/crown-c02-baseline-* output directory}
c02_closure=${3:?matching completed coherent closure}
case "$c02_out" in /tmp/crown-c02-baseline-*) ;; *) exit 64;; esac
case "$c02_mode" in strict) c02_config=release;; sanitize) c02_config=sanitize;; *) exit 64;; esac
c02_packet=docs/verification/c02-baseline-ranking-proposal
c02_overlay=$c02_packet/overlay
c02_source=$c02_packet/tests/ranking_normalized_exception_test.cpp
c02_pg=build/$c02_config/_deps/libpg_query/libpg_query-18.1.0
mkdir -p "$c02_out"
c02_flags=(-std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread
  -I "$c02_overlay/include" -I include -I "$c02_overlay/src/planner" -I "$c02_packet/tests"
  -isystem "$c02_overlay/third_party" -isystem "$c02_pg")
c02_links=(-pthread)
if [[ "$c02_mode" == sanitize ]]; then c02_flags+=(-O1 -fsanitize=address,undefined -fno-omit-frame-pointer);c02_links+=(-fsanitize=address,undefined -fno-omit-frame-pointer);fi
c02_object=$c02_out/ranking_normalized_exception_test.o
c02_command=("${CXX:-c++}" "${c02_flags[@]}" -MD -MF "$c02_object.d" -c "$c02_source" -o "$c02_object")
printf '%q ' "${c02_command[@]}" > "$c02_object.command"
printf '\n' >> "$c02_object.command"
sha256sum "$c02_source" "$c02_packet/tests/ranking_exception_support.hpp" "$c02_overlay/third_party/nlohmann/json.hpp" > "$c02_object.before.sha256"
if "${c02_command[@]}" > "$c02_object.log" 2>&1; then printf '0\n' > "$c02_object.exit";else c02_status=$?;printf '%s\n' "$c02_status" > "$c02_object.exit";cat "$c02_object.log";exit "$c02_status";fi
sha256sum "$c02_source" "$c02_packet/tests/ranking_exception_support.hpp" "$c02_overlay/third_party/nlohmann/json.hpp" > "$c02_object.after.sha256"
cmp "$c02_object.before.sha256" "$c02_object.after.sha256"
c02_command=("${CXX:-c++}" "${c02_links[@]}" "$c02_object" -Wl,--start-group
  "$c02_closure/archives/libc02_runtime.a" "$c02_closure/archives/libc02_ranking.a"
  "$c02_closure/archives/libc02_plan.a" "$c02_closure/archives/libc02_sql.a" "$c02_closure/archives/libc02_core.a"
  -Wl,--end-group "$c02_pg/libpg_query.a" -o "$c02_out/ranking_normalized_exception_test")
printf '%q ' "${c02_command[@]}" > "$c02_out/link.command"
printf '\n' >> "$c02_out/link.command"
if "${c02_command[@]}" > "$c02_out/link.log" 2>&1;then printf '0\n' > "$c02_out/link.exit";else c02_status=$?;printf '%s\n' "$c02_status" > "$c02_out/link.exit";cat "$c02_out/link.log";exit "$c02_status";fi
printf 'compiled and linked supplemental normalized fault consumer %s; no execution\n' "$c02_mode"
