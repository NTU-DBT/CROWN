#!/usr/bin/env bash
# Compile/link the sole changed C++ unit against matching frozen report objects.
# Never configure a native build or execute a produced consumer.
set -euo pipefail
cd /home/userroot/Codex/CROWN
c01_registration_variant=${1:-production}
c01_registration_out=${2:-/tmp/crown-c01-native-registration-production}
case "$c01_registration_variant" in production|testing) ;; *) exit 2 ;; esac
case "$c01_registration_out" in /tmp/crown-c01-native-registration-*) ;; *) exit 2 ;; esac
c01_registration_package=docs/verification/c01-statistics-native-registration-proposal
c01_registration_overlay="$c01_registration_package/overlay"
c01_registration_base="/tmp/crown-c01-report-$c01_registration_variant-final"
mkdir -p "$c01_registration_out"
c01_registration_flags=(-std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread
  -I "$c01_registration_overlay/include" -I "$c01_registration_overlay/src/runtime"
  -I "$c01_registration_overlay/tests/unit" -I "$c01_registration_overlay/tests/support"
  -I include -I src/runtime -I tests/reference -I tests/support -isystem third_party)
if [[ "$c01_registration_variant" == testing ]]; then c01_registration_flags+=(-DCROWN_RUNTIME_TESTING); fi
c01_registration_units=(src_storage_reference src_runtime_statistics src_runtime_owner_statistics src_runtime_statistics_collection
  src_runtime_workload_statistics src_runtime_combined_statistics src_runtime_support src_runtime_physical
  src_runtime_delta src_runtime_session src_io_support src_io_inspection src_runtime_replay src_runtime_window src_runtime_observation
  src_observability_explain src_observability_statistics_explain src_io_statistics_explain
  src_io_explain src_io_run_context src_io_cursor_observation src_io_query_explain src_observability_query_explain)
c01_registration_objects=()
c01_registration_inputs=()
for c01_registration_unit in "${c01_registration_units[@]}"; do
  if [[ "$c01_registration_unit" == src_io_statistics_explain ]]; then
    c01_registration_objects+=("$c01_registration_out/$c01_registration_unit.cpp.o")
  else
    c01_registration_objects+=("$c01_registration_base/$c01_registration_unit.cpp.o")
    c01_registration_inputs+=("$c01_registration_base/$c01_registration_unit.cpp.o")
  fi
done
c01_registration_archives=(build/release/libcrown_reference.a build/release/libcrown_plan.a
  build/release/libcrown_sql.a build/release/libcrown_core.a
  build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a)
c01_registration_inputs+=("${c01_registration_archives[@]}" "$c01_registration_base/commands.sh"
  "$c01_registration_base/statistics_explain_test.o" "$c01_registration_base/statistics_explain_exception_test.o"
  docs/verification/c01-statistics-report-proposal/PACKAGE_SHA256SUMS)
sha256sum "${c01_registration_inputs[@]}" > "$c01_registration_out/BORROWED_INPUT_SHA256SUMS"
printf '#!/usr/bin/env bash\nset -euo pipefail\ncd /home/userroot/Codex/CROWN\n' > "$c01_registration_out/commands.sh"
c01_registration_source="$c01_registration_overlay/src/io/statistics_explain.cpp"
c01_registration_object="$c01_registration_out/src_io_statistics_explain.cpp.o"
printf '%q ' c++ "${c01_registration_flags[@]}" -MMD -MF "$c01_registration_out/writer.d" -c "$c01_registration_source" -o "$c01_registration_object" >> "$c01_registration_out/commands.sh"
printf '\n' >> "$c01_registration_out/commands.sh"
c++ "${c01_registration_flags[@]}" -MMD -MF "$c01_registration_out/writer.d" -c "$c01_registration_source" -o "$c01_registration_object" > "$c01_registration_out/writer.log" 2>&1
for c01_registration_test in statistics_explain_test statistics_explain_exception_test; do
  printf '%q ' c++ "${c01_registration_flags[@]}" "${c01_registration_objects[@]}" "$c01_registration_base/$c01_registration_test.o" -Wl,--start-group "${c01_registration_archives[@]}" -Wl,--end-group -o "$c01_registration_out/$c01_registration_test" >> "$c01_registration_out/commands.sh"
  printf '\n' >> "$c01_registration_out/commands.sh"
  c++ "${c01_registration_flags[@]}" "${c01_registration_objects[@]}" "$c01_registration_base/$c01_registration_test.o" -Wl,--start-group "${c01_registration_archives[@]}" -Wl,--end-group -o "$c01_registration_out/$c01_registration_test" > "$c01_registration_out/$c01_registration_test-link.log" 2>&1
done
printf '%q ' c++ "${c01_registration_flags[@]}" -MMD -MF "$c01_registration_out/example.d" -c "$c01_registration_package/examples/statistics_report.cpp" -o "$c01_registration_out/example.o" >> "$c01_registration_out/commands.sh"
printf '\n' >> "$c01_registration_out/commands.sh"
c++ "${c01_registration_flags[@]}" -MMD -MF "$c01_registration_out/example.d" -c "$c01_registration_package/examples/statistics_report.cpp" -o "$c01_registration_out/example.o" > "$c01_registration_out/example.log" 2>&1
sha256sum -c --quiet "$c01_registration_out/BORROWED_INPUT_SHA256SUMS"
printf '%s publication writer and guide example compiled; producer/fault consumers linked; nothing executed.\n' "$c01_registration_variant"
