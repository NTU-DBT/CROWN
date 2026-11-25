#!/usr/bin/env bash
set -euo pipefail

if [[ $# != 1 ]]; then
  printf 'Usage: %s WORK_DIR\n' "$0" >&2
  exit 2
fi

here=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
work=$(realpath -- "$1")
fivm="$work/FIVM"
stage="$work/native"
for header in probe/generated.hpp probe/generated_numeric.hpp; do
  if [[ ! -f "$work/$header" ]]; then
    tar -xzf "$here/generated-cpp.tar.gz" -C "$work" "$header"
  fi
done
mkdir -p "$stage/signed/ring"
patch --quiet -o "$stage/signed/ring/ring_factorized.hpp" \
  "$fivm/examples/include/ring/ring_factorized.hpp" "$here/signed-factorized.patch"

build() {
  local variant=$1 generated=$2
  shift 2
  local destination="$stage/$variant"
  mkdir -p "$destination"
  cp -- "$generated" "$destination/generated.hpp"
  "${CXX:-g++}" -std=c++23 -O3 -DNDEBUG "$@" \
    -I"$destination" -I"$fivm/runtime/include" \
    -I"$fivm/runtime/include/dbtoaster" -I"$fivm/examples/include" \
    "$here/replay.cpp" -o "$destination/replay" >"$destination/build.log" 2>&1
}

build numeric "$work/probe/generated_numeric.hpp"
build factorized "$work/probe/generated.hpp" -DFIVM_FACTOR_PAYLOAD
build signed "$work/probe/generated.hpp" -DFIVM_FACTOR_PAYLOAD
