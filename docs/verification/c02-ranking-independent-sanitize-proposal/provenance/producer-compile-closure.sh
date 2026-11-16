#!/usr/bin/env bash
# Compile/link only. This script never runs any produced executable.
set -euo pipefail
c02_mode=${1:?strict or sanitize}
c02_out=${2:?distinct /tmp/crown-c02-baseline-* output directory}
c02_stage=${3:-all}
c02_repo=${4:-/home/userroot/Codex/CROWN}
case "$c02_out" in /tmp/crown-c02-baseline-*) ;; *) exit 64;; esac
case "$c02_mode" in strict) c02_config=release;; sanitize) c02_config=sanitize;; *) exit 64;; esac
cd "$c02_repo"
c02_packet=docs/verification/c02-baseline-ranking-proposal
c02_overlay=$c02_packet/overlay
c02_pg=build/$c02_config/_deps/libpg_query/libpg_query-18.1.0
c02_cxx=${CXX:-c++}
mkdir -p "$c02_out/objects" "$c02_out/archives" "$c02_out/executables" "$c02_out/metadata"
c02_flags=(-std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread
  -I "$c02_overlay/include" -I include -I "$c02_overlay/src/planner" -I "$c02_overlay/src/runtime"
  -I src/planner -I src/runtime -I tests/support -I tests/reference -I "$c02_packet/tests"
  -isystem "$c02_overlay/third_party" -isystem "$c02_pg")
c02_linkflags=(-pthread)
if [[ "$c02_mode" == sanitize ]]; then
  c02_flags+=(-O1 -fsanitize=address,undefined -fno-omit-frame-pointer)
  c02_linkflags+=(-fsanitize=address,undefined -fno-omit-frame-pointer)
fi
c02_core=(src/ir/model.cpp src/ir/scalar.cpp src/ir/digest.cpp src/catalog/catalog.cpp src/io/catalog.cpp src/io/document.cpp
  src/io/recognition.cpp src/io/layout.cpp src/storage/layout.cpp src/storage/arena.cpp src/storage/reference.cpp
  src/planner/recognize.cpp src/planner/verify.cpp src/planner/exact.cpp src/planner/certificate.cpp
  src/planner/fast_paths.cpp src/planner/search_session.cpp src/planner/residual.cpp src/planner/residual_reduce.cpp
  src/planner/residual_view.cpp src/planner/residual_trace.cpp src/planner/residual_reconstruct.cpp
  src/io/ingest.cpp src/io/ingest_text.cpp src/io/batch.cpp src/io/search.cpp src/io/residual.cpp
  "$c02_overlay/src/planner/candidates.cpp" src/planner/candidate_generator.cpp src/planner/candidate_key.cpp src/io/candidates.cpp)
c02_sql=(src/frontend/parser.cpp src/frontend/bind.cpp src/frontend/normalize.cpp src/frontend/adapter.cpp src/frontend/admission.cpp
  src/io/sql.cpp src/io/binding.cpp src/io/normalization.cpp src/io/identity.cpp src/io/admission.cpp)
c02_plan=(src/planner/lower.cpp src/io/physical.cpp src/storage/physical.cpp)
c02_ranking=("$c02_overlay/src/planner/ranking.cpp" "$c02_overlay/src/planner/ranking_integer.cpp" "$c02_overlay/src/planner/ranking_payload.cpp")
c02_runtime=(src/runtime/support.cpp src/runtime/physical.cpp src/runtime/delta.cpp src/io/support.cpp src/io/inspection.cpp
  src/runtime/replay.cpp src/runtime/session.cpp src/runtime/window.cpp src/runtime/observation.cpp src/runtime/statistics.cpp
  src/runtime/owner_statistics.cpp src/runtime/statistics_collection.cpp src/runtime/workload_statistics.cpp src/runtime/combined_statistics.cpp
  "$c02_overlay/src/runtime/ranking_evidence.cpp")
c02_reference=(tests/reference/evaluator.cpp tests/reference/tree_oracle.cpp tests/reference/delta_model.cpp
  tests/reference/residual_oracle.cpp tests/reference/candidate_set.cpp)
c02_tests=(ranking_binding_test ranking_contract_test ranking_pure_link_test ranking_empty_test ranking_exception_test ranking_payload_time_test ranking_census_test)
c02_legacy=(candidates_test candidates_exception_test candidates_io_test)

c02_compile() {
  local c02_group=$1 c02_source=$2 c02_define=$3 c02_name=$4
  local c02_object="$c02_out/objects/$c02_group/$c02_name.o"
  mkdir -p "$c02_out/objects/$c02_group"
  local -a c02_command=("$c02_cxx" "${c02_flags[@]}")
  if [[ -n "$c02_define" ]]; then c02_command+=("-D$c02_define"); fi
  c02_command+=(-MD -MF "$c02_object.d" -c "$c02_source" -o "$c02_object")
  printf '%q ' "${c02_command[@]}" > "$c02_object.command"
  printf '\n' >> "$c02_object.command"
  printf '%s\t%s\t%s\n' "$c02_source" "$c02_define" "$c02_object" > "$c02_object.input.tsv"
  sha256sum "$c02_source" "$c02_overlay/third_party/nlohmann/json.hpp" > "$c02_object.before.sha256"
  if "${c02_command[@]}" > "$c02_object.log" 2>&1; then
    printf '0\n' > "$c02_object.exit"
  else
    local c02_exit=$?
    printf '%s\n' "$c02_exit" > "$c02_object.exit"
    cat "$c02_object.log"
    return "$c02_exit"
  fi
  sha256sum "$c02_source" "$c02_overlay/third_party/nlohmann/json.hpp" > "$c02_object.after.sha256"
  cmp "$c02_object.before.sha256" "$c02_object.after.sha256"
}
c02_library() {
  local c02_group=$1 c02_define=$2
  shift 2
  local c02_source c02_name
  local -a c02_objects=()
  for c02_source in "$@"; do
    c02_name=${c02_source#"$c02_overlay/"}
    c02_name=${c02_name//\//_}
    c02_compile "$c02_group" "$c02_source" "$c02_define" "$c02_name"
    c02_objects+=("$c02_out/objects/$c02_group/$c02_name.o")
  done
  local -a c02_command=(ar rcs "$c02_out/archives/libc02_$c02_group.a" "${c02_objects[@]}")
  printf '%q ' "${c02_command[@]}" > "$c02_out/archives/libc02_$c02_group.a.command"
  printf '\n' >> "$c02_out/archives/libc02_$c02_group.a.command"
  printf '%s\n' "${c02_objects[@]}" > "$c02_out/archives/libc02_$c02_group.a.members"
  "${c02_command[@]}" > "$c02_out/archives/libc02_$c02_group.a.log" 2>&1
  printf 'compiled %s %s\n' "$c02_mode" "$c02_group"
}
c02_test_objects() {
  local c02_name c02_define
  for c02_name in "${c02_tests[@]}"; do
    c02_define=
    if [[ "$c02_name" == ranking_census_test ]]; then c02_define=CROWN_RUNTIME_TESTING; fi
    c02_compile tests "$c02_packet/tests/$c02_name.cpp" "$c02_define" "$c02_name"
  done
  for c02_name in "${c02_legacy[@]}"; do c02_compile tests "tests/unit/$c02_name.cpp" '' "$c02_name"; done
  printf 'compiled %s tests\n' "$c02_mode"
}
c02_link() {
  local c02_name=$1 c02_runtime_variant=$2
  local -a c02_command=("$c02_cxx" "${c02_linkflags[@]}" "$c02_out/objects/tests/$c02_name.o" -Wl,--start-group)
  if [[ -n "$c02_runtime_variant" ]]; then c02_command+=("$c02_out/archives/libc02_$c02_runtime_variant.a"); fi
  c02_command+=("$c02_out/archives/libc02_ranking.a" "$c02_out/archives/libc02_reference.a"
    "$c02_out/archives/libc02_plan.a" "$c02_out/archives/libc02_sql.a" "$c02_out/archives/libc02_core.a"
    -Wl,--end-group "$c02_pg/libpg_query.a" -o "$c02_out/executables/$c02_name")
  printf '%q ' "${c02_command[@]}" > "$c02_out/executables/$c02_name.command"
  printf '\n' >> "$c02_out/executables/$c02_name.command"
  "${c02_command[@]}" > "$c02_out/executables/$c02_name.log" 2>&1
}
c02_links() {
  local c02_name
  for c02_name in ranking_binding_test ranking_pure_link_test "${c02_legacy[@]}"; do c02_link "$c02_name" ''; done
  for c02_name in ranking_contract_test ranking_empty_test ranking_exception_test ranking_payload_time_test; do c02_link "$c02_name" runtime; done
  c02_link ranking_census_test runtime_testing
  printf 'linked %s all ten consumers; no execution\n' "$c02_mode"
}
case "$c02_stage" in
  core) c02_library core '' "${c02_core[@]}";;
  sql_plan) c02_library sql '' "${c02_sql[@]}"; c02_library plan '' "${c02_plan[@]}";;
  ranking_reference) c02_library ranking '' "${c02_ranking[@]}"; c02_library reference '' "${c02_reference[@]}";;
  runtime) c02_library runtime '' "${c02_runtime[@]}";;
  runtime_testing) c02_library runtime_testing CROWN_RUNTIME_TESTING "${c02_runtime[@]}";;
  tests) c02_test_objects;;
  link) c02_links;;
  all)
    c02_library core '' "${c02_core[@]}"; c02_library sql '' "${c02_sql[@]}"; c02_library plan '' "${c02_plan[@]}"
    c02_library ranking '' "${c02_ranking[@]}"; c02_library reference '' "${c02_reference[@]}"
    c02_library runtime '' "${c02_runtime[@]}"; c02_library runtime_testing CROWN_RUNTIME_TESTING "${c02_runtime[@]}"
    c02_test_objects; c02_links;;
  *) exit 64;;
esac
