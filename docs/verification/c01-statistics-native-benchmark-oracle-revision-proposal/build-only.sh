#!/usr/bin/env bash
set -eu

if [ "$#" -lt 1 ] || [ "$#" -gt 2 ]; then
  printf '%s\n' "usage: $0 /tmp/crown-c01-native-benchmark-oracle-revision-<label> [pinned-object-dir]" >&2
  exit 2
fi

build_root=$1
object_root=${2:-/tmp/crown-c01-native-benchmark-author}
case "$build_root" in
  /tmp/crown-c01-native-benchmark-oracle-revision-*) ;;
  *) printf '%s\n' "build output must be under /tmp/crown-c01-native-benchmark-oracle-revision-*" >&2; exit 2 ;;
esac
case "$object_root" in
  /tmp/crown-c01-native-benchmark-*) ;;
  *) printf '%s\n' "pinned objects must be under /tmp/crown-c01-native-benchmark-*" >&2; exit 2 ;;
esac

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/../../.." && pwd)
overlay="$repo_root/docs/verification/c01-statistics-combined-proposal/overlay"
compiler=${CXX:-c++}
mkdir -p "$build_root"

# Reuse exactly the 15 successful O3 runtime/collector/storage objects from
# the frozen benchmark's author build. A changed or missing object is fatal.
(
  cd "$object_root"
  sha256sum --check --status <<'EOF'
498194b88732948c1e3dace183c0fd46c7f8b8372d17b2cee7e13adaea352a34  io_inspection.o
b252f506d402f09bdc0be9f9d928b8744d23eec4075a227cce00534e48ec790e  io_support.o
6a08b4d43baf6d7711c21620cdaf7c3c6e838960e3bcfcf69f760c765c556eba  runtime_combined_statistics.o
a27744d1433829d03cf2f155532a1625a3e8c30f833d57014bde9078e97480db  runtime_delta.o
237cb03f8d5ad145b83a1ba54241e63e2c744133754a527028743539ab188586  runtime_observation.o
b1e8489f6a526bc81b3105b294f06035299cdac3cfc5e9036fcedc23d3b6b3e2  runtime_owner_statistics.o
b1ddc4be03375537ba36146921dee7137491e57ede810582bf47a4571cccff68  runtime_physical.o
748b0cb1a4064ef160af19c4059e1e40557212a067e41b6331f6d3312e52196d  runtime_replay.o
22fa9df9698ccf03d3ad3b7c4e836a7779dc163254613bd6c9bcd3d53373b890  runtime_session.o
dcbe29819ad01ba7f4656f77dd90077b47fb139a24cbc397017631a666620054  runtime_statistics.o
38344ef47ed62e3b9299a588cffa23d7ef61bd2c00745f85e3fc0a3ce2406d94  runtime_statistics_collection.o
daea53ef1a4220926f11dfd476f9acc56d9f7e4bdc68e5bd36368c3631909e35  runtime_support.o
38f0be2ceafa598e7e37f1b8a9cf4b493759d6228edae128c406646e2f84c8c7  runtime_window.o
71e37e44b7993c5819c6727f57b6b7f32c757ce4c137678e712fbeca32e6a184  runtime_workload_statistics.o
2827e2263ef2fdc124564dab2ec6dd50bf4813162896122707314d735a80f9e  storage_reference.o
EOF
) || {
  printf '%s\n' "pinned O3 runtime/collector/storage objects do not match" >&2
  exit 1
}
(
  cd "$repo_root"
  sha256sum --check --status <<'EOF'
92a96fd0f01ade3862fb4fbbabe316337719f71eb43361f5eb6b250cdfe04d6a  build/release/libcrown_plan.a
6ba92b30615a1b35c7b499d1067647be49be47757b8ee58cb1098c65d275d26e  build/release/libcrown_sql.a
784b820ff9284ad75033552056fd2a81113f7eb54be5db56959f31ce778bcf9d  build/release/libcrown_core.a
c254ea2e05708d5cf5e8526bad19d69d314d05a9af4f7a8b0be4b08e069e2174  build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a
EOF
) || {
  printf '%s\n' "pinned Release dependency archives do not match" >&2
  exit 1
}

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

"$compiler" "${common_flags[@]}" \
  -MMD -MF "$build_root/native_benchmark.d" \
  -c "$repo_root/docs/verification/c01-statistics-native-benchmark-oracle-revision-proposal/native_benchmark.cpp" \
  -o "$build_root/native_benchmark.o" \
  >"$build_root/native_benchmark.log" 2>&1

"$compiler" -std=c++23 -O3 -DNDEBUG \
  -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread \
  "$build_root/native_benchmark.o" \
  "$object_root/runtime_support.o" \
  "$object_root/runtime_physical.o" \
  "$object_root/runtime_delta.o" \
  "$object_root/io_support.o" \
  "$object_root/io_inspection.o" \
  "$object_root/runtime_replay.o" \
  "$object_root/runtime_session.o" \
  "$object_root/runtime_window.o" \
  "$object_root/runtime_observation.o" \
  "$object_root/runtime_statistics.o" \
  "$object_root/runtime_statistics_collection.o" \
  "$object_root/runtime_owner_statistics.o" \
  "$object_root/runtime_workload_statistics.o" \
  "$object_root/runtime_combined_statistics.o" \
  "$object_root/storage_reference.o" \
  -Wl,--start-group \
  "$repo_root/build/release/libcrown_plan.a" \
  "$repo_root/build/release/libcrown_sql.a" \
  "$repo_root/build/release/libcrown_core.a" \
  "$repo_root/build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a" \
  -Wl,--end-group \
  -o "$build_root/crown_c01_native_benchmark" \
  >"$build_root/link.log" 2>&1
