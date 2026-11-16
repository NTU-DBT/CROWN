#!/usr/bin/env bash
# Compile/link only. Root owns test execution and acceptance.
set -euo pipefail
cd /home/userroot/Codex/CROWN

c02_build_mode=${1:?strict or sanitize}
c02_build_out=${2:?fresh /tmp/crown-c02-independent-* output directory}
c02_closure=${3:?matching coherently rebuilt producer closure directory}
case "$c02_build_out" in
  /tmp/crown-c02-independent-*) ;;
  *) printf '%s\n' 'output must use /tmp/crown-c02-independent-*' >&2; exit 2 ;;
esac
if [[ -e "$c02_build_out" ]]; then
  printf '%s\n' 'output directory already exists; select a new numbered path' >&2
  exit 2
fi

c02_overlay=docs/verification/c02-baseline-ranking-proposal/overlay
c02_tests=docs/verification/c02-ranking-independent-tests-proposal/tests
c02_cxx=${CXX:-c++}
c02_flags=(-std=c++23 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread)
c02_includes=(-I"$c02_overlay/include" -Iinclude -I"$c02_overlay/src/planner" -Isrc/planner
  -isystem "$c02_overlay/third_party")
case "$c02_build_mode" in
  strict) c02_flags+=(-O2); c02_native_config=release ;;
  sanitize)
    c02_flags+=(-O1 -fsanitize=address,undefined -fno-omit-frame-pointer)
    c02_native_config=sanitize
    ;;
  *) printf '%s\n' 'mode must be strict or sanitize' >&2; exit 2 ;;
esac
c02_parser=build/$c02_native_config/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a
c02_integer_object=$c02_closure/objects/ranking/src_planner_ranking_integer.cpp.o
c02_archives=()
for c02_library in runtime ranking reference plan sql core; do
  c02_archives+=("$c02_closure/archives/libc02_$c02_library.a")
done
for c02_input in "$c02_integer_object" "${c02_archives[@]}" "$c02_parser"; do
  if [[ ! -f "$c02_input" ]]; then
    printf 'missing coherent input: %s\n' "$c02_input" >&2
    exit 2
  fi
done
mkdir -p "$c02_build_out"
sha256sum "$c02_integer_object" "${c02_archives[@]}" "$c02_parser" \
  > "$c02_build_out/link-inputs.before.sha256"
rg --files "$c02_overlay" "$c02_tests" | LC_ALL=C sort | xargs sha256sum \
  > "$c02_build_out/sources.before.sha256"

c02_record_command() {
  local c02_record=$1
  shift
  printf '%q ' "$@" > "$c02_record.command"
  printf '\n' >> "$c02_record.command"
  if "$@" > "$c02_record.log" 2>&1; then
    printf '0\n' > "$c02_record.exit"
  else
    local c02_status=$?
    printf '%s\n' "$c02_status" > "$c02_record.exit"
    cat "$c02_record.log"
    return "$c02_status"
  fi
}

# Both consumers and all linked runtime units use the production ABI.
# Do not substitute a testing archive or any cached native C++ archive.
for c02_consumer in ranking_integer_independent_test ranking_public_independent_test; do
  c02_record_command "$c02_build_out/$c02_consumer.compile" \
    "$c02_cxx" "${c02_flags[@]}" "${c02_includes[@]}" \
    -MD -MF "$c02_build_out/$c02_consumer.d" \
    -c "$c02_tests/$c02_consumer.cpp" -o "$c02_build_out/$c02_consumer.o"
done
c02_record_command "$c02_build_out/ranking_integer_independent_test.link" \
  "$c02_cxx" "${c02_flags[@]}" "$c02_build_out/ranking_integer_independent_test.o" \
  "$c02_integer_object" -o "$c02_build_out/ranking_integer_independent_test"
c02_record_command "$c02_build_out/ranking_public_independent_test.link" \
  "$c02_cxx" "${c02_flags[@]}" "$c02_build_out/ranking_public_independent_test.o" \
  -Wl,--start-group "${c02_archives[@]}" -Wl,--end-group "$c02_parser" \
  -o "$c02_build_out/ranking_public_independent_test"

sha256sum "$c02_integer_object" "${c02_archives[@]}" "$c02_parser" \
  > "$c02_build_out/link-inputs.after.sha256"
rg --files "$c02_overlay" "$c02_tests" | LC_ALL=C sort | xargs sha256sum \
  > "$c02_build_out/sources.after.sha256"
cmp "$c02_build_out/link-inputs.before.sha256" "$c02_build_out/link-inputs.after.sha256"
cmp "$c02_build_out/sources.before.sha256" "$c02_build_out/sources.after.sha256"
printf 'compiled and linked two %s independent consumers; no execution\n' "$c02_build_mode"
