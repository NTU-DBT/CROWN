#!/usr/bin/env bash
# Compile/link only. This script never executes a test or changes native files.
set -euo pipefail
cd /home/userroot/Codex/CROWN
proposal=docs/verification/c01-statistics-owner-capture-proposal/overlay
owner_build=${1:-/tmp/crown-c01-owner-max-strict}
owner_dependencies=${2:-build/release}
owner_mode=${3:-strict}
case "$owner_build" in /tmp/crown-c01-owner-max-*) ;; *) exit 2 ;; esac
mkdir -p "$owner_build"
flags=(-std=c++23 -O2 -g -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread
  -I "$proposal/include" -I include -I src/runtime -I tests/reference -isystem third_party)
if [[ "$owner_mode" == sanitized ]]; then
  flags+=(-O1 -fsanitize=address,undefined -fno-omit-frame-pointer)
elif [[ "$owner_mode" != strict ]]; then
  exit 2
fi
objects=()
commands="$owner_build/commands.sh"
printf '#!/usr/bin/env bash\nset -euo pipefail\ncd /home/userroot/Codex/CROWN\n' > "$commands"
for source in "$proposal/src/storage/reference.cpp" "$proposal/src/runtime/statistics.cpp" \
  "$proposal/src/runtime/owner_statistics.cpp" "$proposal/src/runtime/support.cpp" \
  "$proposal/src/runtime/physical.cpp" "$proposal/src/runtime/delta.cpp" \
  "$proposal/src/runtime/session.cpp" src/io/support.cpp src/io/inspection.cpp \
  src/runtime/replay.cpp src/runtime/window.cpp src/runtime/observation.cpp; do
  stem=${source##*/}
  category=${source%/*}
  category=${category##*/}
  object="$owner_build/${category}-${stem%.cpp}.o"
  printf '%q ' c++ "${flags[@]}" -c "$source" -o "$object" >> "$commands"
  printf '\n' >> "$commands"
  if c++ "${flags[@]}" -c "$source" -o "$object" > "$object.log" 2>&1; then
    printf 'compiled %s\n' "$source"
  else
    cat "$object.log"
    exit 1
  fi
  objects+=("$object")
done
archives=("$owner_dependencies/libcrown_reference.a" "$owner_dependencies/libcrown_plan.a"
  "$owner_dependencies/libcrown_sql.a"
  "$owner_dependencies/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a"
  "$owner_dependencies/libcrown_core.a")
sha256sum "${archives[@]}" > "$owner_build/DEPENDENCY_SHA256SUMS"
for name in owner_statistics_test owner_statistics_exception_test statistics_capture_test statistics_capture_exception_test; do
  object="$owner_build/$name.o"
  printf '%q ' c++ "${flags[@]}" -c "$proposal/tests/unit/$name.cpp" -o "$object" >> "$commands"
  printf '\n' >> "$commands"
  if ! c++ "${flags[@]}" -c "$proposal/tests/unit/$name.cpp" -o "$object" > "$object.log" 2>&1; then
    cat "$object.log"
    exit 1
  fi
  printf '%q ' c++ "${flags[@]}" "$object" "${objects[@]}" "${archives[@]}" -o "$owner_build/$name" >> "$commands"
  printf '\n' >> "$commands"
  if ! c++ "${flags[@]}" "$object" "${objects[@]}" "${archives[@]}" -o "$owner_build/$name" > "$owner_build/$name.link.log" 2>&1; then
    cat "$owner_build/$name.link.log"
    exit 1
  fi
  printf 'linked %s\n' "$name"
done
