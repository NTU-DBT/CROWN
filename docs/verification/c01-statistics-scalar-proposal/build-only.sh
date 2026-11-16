#!/usr/bin/env bash
# Compile/link a production-only consumer. Never execute its binary.
set -euo pipefail
cd /home/userroot/Codex/CROWN
c01_scalar_mode=${1:-strict}
c01_scalar_out=${2:-/tmp/crown-c01-scalar-production-strict-attempt-1}
case "$c01_scalar_out" in /tmp/crown-c01-scalar-*) ;; *) exit 2 ;; esac
case "$c01_scalar_mode" in
  strict) c01_scalar_closure=/tmp/crown-c01-combined-production; c01_scalar_dependencies=build/release ;;
  sanitized) c01_scalar_closure=/tmp/crown-c01-combined-root-production-sanitized-attempt-1; c01_scalar_dependencies=build/sanitize ;;
  *) exit 2 ;;
esac
mkdir -p "$c01_scalar_out"
c01_scalar_package=docs/verification/c01-statistics-scalar-proposal
c01_scalar_overlay=docs/verification/c01-statistics-combined-proposal/overlay
c01_scalar_flags=(-std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread
  -I "$c01_scalar_overlay/include" -I include -isystem third_party)
if [[ "$c01_scalar_mode" == sanitized ]]; then c01_scalar_flags+=(-O1 -fsanitize=address,undefined -fno-omit-frame-pointer); fi
c01_scalar_objects=()
for c01_scalar_unit in src_storage_reference src_runtime_statistics src_runtime_owner_statistics src_runtime_statistics_collection
do c01_scalar_objects+=("$c01_scalar_closure/$c01_scalar_unit.cpp.o"); done
for c01_scalar_unit in src_runtime_workload_statistics src_runtime_combined_statistics src_runtime_support src_runtime_physical src_runtime_delta src_runtime_session src_io_support src_io_inspection src_runtime_replay src_runtime_window src_runtime_observation
do c01_scalar_objects+=("$c01_scalar_closure/$c01_scalar_unit.cpp.o"); done
c01_scalar_archives=("$c01_scalar_dependencies/libcrown_reference.a" "$c01_scalar_dependencies/libcrown_plan.a"
  "$c01_scalar_dependencies/libcrown_sql.a" "$c01_scalar_dependencies/libcrown_core.a"
  "$c01_scalar_dependencies/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a")
sha256sum "${c01_scalar_objects[@]}" "${c01_scalar_archives[@]}" "$c01_scalar_closure/commands.sh" > "$c01_scalar_out/INPUT_SHA256SUMS"
printf '#!/usr/bin/env bash\nset -euo pipefail\ncd /home/userroot/Codex/CROWN\n' > "$c01_scalar_out/commands.sh"
printf '%q ' c++ "${c01_scalar_flags[@]}" -MMD -MF "$c01_scalar_out/scalar_statistics_test.d" -c "$c01_scalar_package/scalar_statistics_test.cpp" -o "$c01_scalar_out/scalar_statistics_test.o" >> "$c01_scalar_out/commands.sh"
printf '\n' >> "$c01_scalar_out/commands.sh"
if ! c++ "${c01_scalar_flags[@]}" -MMD -MF "$c01_scalar_out/scalar_statistics_test.d" -c "$c01_scalar_package/scalar_statistics_test.cpp" -o "$c01_scalar_out/scalar_statistics_test.o" > "$c01_scalar_out/compile.log" 2>&1; then cat "$c01_scalar_out/compile.log"; exit 1; fi
printf '%q ' c++ "${c01_scalar_flags[@]}" "${c01_scalar_objects[@]}" "$c01_scalar_out/scalar_statistics_test.o" -Wl,--start-group "${c01_scalar_archives[@]}" -Wl,--end-group -o "$c01_scalar_out/scalar_statistics_test" >> "$c01_scalar_out/commands.sh"
printf '\n' >> "$c01_scalar_out/commands.sh"
if ! c++ "${c01_scalar_flags[@]}" "${c01_scalar_objects[@]}" "$c01_scalar_out/scalar_statistics_test.o" -Wl,--start-group "${c01_scalar_archives[@]}" -Wl,--end-group -o "$c01_scalar_out/scalar_statistics_test" > "$c01_scalar_out/link.log" 2>&1; then cat "$c01_scalar_out/link.log"; exit 1; fi
sha256sum -c --quiet "$c01_scalar_out/INPUT_SHA256SUMS"
printf 'Production %s consumer compiled and linked; no binary executed.\n' "$c01_scalar_mode"
