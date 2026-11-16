#!/usr/bin/env bash
# Direct compiler/archive/link preparation only. Never executes a consumer.
set -euo pipefail
repo=${1:-/home/userroot/Codex/CROWN}
out=${2:-/tmp/crown-c02-native-registration-strict-1}
stage=${3:-all}
optimization=${4:-2}
case "$out" in /tmp/crown-c02-native-registration-*) ;; *) exit 2 ;; esac
case "$optimization" in 0|1|2|3) ;; *) exit 2 ;; esac
cd "$repo"
packet=docs/verification/c02-native-registration-proposal
overlay=$packet/overlay
accepted=/tmp/crown-c02-baseline-coherent-strict-1
parser=build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a
mkdir -p "$out/objects" "$out/archives" "$out/executables"

record() {
  local stem=$1
  shift
  printf '%q ' "$@" > "$stem.command"
  printf '\n' >> "$stem.command"
  set +e
  "$@" > "$stem.log" 2>&1
  local code=$?
  set -e
  printf '%s\n' "$code" > "$stem.exit"
  if (( code != 0 )); then
    cat "$stem.log"
    return "$code"
  fi
}

flags=(-std=c++23 "-O$optimization" -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion
  -Wsign-conversion -Werror -pthread)
includes=(-I "$overlay/include" -I include -I "$overlay/tests/support"
  -I tests/support -I "$overlay/src/planner" -I "$overlay/src/runtime"
  -I src/runtime -isystem "$overlay/third_party")

compile() {
  local name=$1 source=$2 variant=${3:-production}
  local extra=()
  if [[ $variant == testing ]]; then extra=(-DCROWN_RUNTIME_TESTING); fi
  record "$out/objects/$name.compile" c++ "${flags[@]}" "${includes[@]}" \
    "${extra[@]}" -MD -MF "$out/objects/$name.d" -c "$source" \
    -o "$out/objects/$name.o"
}

if [[ $stage == all || $stage == archives ]]; then
  # These exact immutable archives were already rebuilt coherently with f763c58b.
  # No native C++ archive is reused. Runtime is re-archived without its old bridge.
  for library in core sql plan; do
    cp "$accepted/archives/libc02_$library.a" "$out/archives/libcrown_$library.a"
    cp "$accepted/archives/libc02_$library.a.members" "$out/archives/libcrown_$library.a.members"
  done
  for variant in runtime runtime_testing; do
    rg -v '/src_runtime_ranking_evidence\.cpp\.o$' \
      "$accepted/archives/libc02_$variant.a.members" > "$out/archives/libcrown_$variant.a.members"
    mapfile -t members < "$out/archives/libcrown_$variant.a.members"
    (( ${#members[@]} == 14 ))
    record "$out/archives/libcrown_$variant.a.archive" ar rcs \
      "$out/archives/libcrown_$variant.a" "${members[@]}"
  done
fi

if [[ $stage == all || $stage == pure ]]; then
  pure_objects=()
  for source in ranking ranking_integer ranking_payload; do
    compile "$source" "$overlay/src/planner/$source.cpp"
    pure_objects+=("$out/objects/$source.o")
  done
  printf '%s\n' "${pure_objects[@]}" > "$out/archives/libcrown_ranking.a.members"
  # A fresh output directory is required for a complete reproduction. Do not
  # append differently named objects to a copied predecessor archive.
  if [[ -e $out/archives/libcrown_ranking.a ]]; then exit 2; fi
  record "$out/archives/libcrown_ranking.a.archive" ar rcs \
    "$out/archives/libcrown_ranking.a" "${pure_objects[@]}"
fi

if [[ $stage == all || $stage == bridges ]]; then
  compile ranking_bridge_production "$overlay/src/runtime/ranking_evidence.cpp"
  compile ranking_bridge_testing "$overlay/src/runtime/ranking_evidence.cpp" testing
  for variant in production testing; do
    printf '%s\n' "$out/objects/ranking_bridge_$variant.o" \
      > "$out/archives/libcrown_ranking_runtime_$variant.a.members"
    record "$out/archives/libcrown_ranking_runtime_$variant.a.archive" ar rcs \
      "$out/archives/libcrown_ranking_runtime_$variant.a" "$out/objects/ranking_bridge_$variant.o"
  done
fi

if [[ $stage == all || $stage == consumers ]]; then
  for test in ranking_binding ranking_pure_link ranking_contract ranking_empty \
      ranking_payload_time ranking_exception ranking_normalized_exception \
      ranking_public_independent ranking_integer_independent; do
    compile "$test" "$overlay/tests/unit/${test}_test.cpp"
  done
  compile ranking_census "$overlay/tests/unit/ranking_census_test.cpp" testing
  compile ranking_usage_production "$overlay/tests/examples/ranking_usage.cpp"
  compile ranking_usage_testing "$overlay/tests/examples/ranking_usage.cpp" testing
fi

if [[ $stage == all || $stage == json ]]; then
  for variant in patched upstream; do
    include_root=$overlay/third_party
    if [[ $variant == upstream ]]; then include_root=$overlay/third_party/nlohmann/upstream; fi
    record "$out/objects/json_$variant.compile" c++ "${flags[@]}" \
      -isystem "$include_root" -MD -MF "$out/objects/json_$variant.d" \
      -c "$overlay/tests/unit/json_cleanup_test.cpp" -o "$out/objects/json_$variant.o"
    record "$out/executables/json_$variant.link" c++ "${flags[@]}" \
      "$out/objects/json_$variant.o" -o "$out/executables/json_$variant"
  done
fi

if [[ $stage == all || $stage == link ]]; then
  for test in ranking_binding ranking_pure_link ranking_contract ranking_empty \
      ranking_payload_time ranking_census ranking_exception ranking_normalized_exception \
      ranking_public_independent ranking_integer_independent; do
    libraries=()
    case "$test" in
      ranking_binding|ranking_pure_link|ranking_integer_independent) ;;
      ranking_census)
        libraries+=("$out/archives/libcrown_ranking_runtime_testing.a"
          "$out/archives/libcrown_runtime_testing.a") ;;
      *) libraries+=("$out/archives/libcrown_ranking_runtime_production.a"
           "$out/archives/libcrown_runtime.a") ;;
    esac
    libraries+=("$out/archives/libcrown_ranking.a" "$out/archives/libcrown_plan.a"
      "$out/archives/libcrown_sql.a" "$out/archives/libcrown_core.a")
    record "$out/executables/$test.link" c++ "${flags[@]}" "$out/objects/$test.o" \
      -Wl,--start-group "${libraries[@]}" -Wl,--end-group "$parser" \
      -o "$out/executables/$test"
  done
fi
