#!/usr/bin/env bash
# Build the per-query F-IVM replay binaries into WORK_DIR/bin/<query>.
#
#   build-queries.sh WORK_DIR [--codegen] [QUERY ...]
#
# WORK_DIR must contain the upstream F-IVM checkout at WORK_DIR/FIVM (e55304d).
# Generated trigger headers live in WORK_DIR/queries/<query>.hpp. Missing headers
# are restored from generated-queries.tar.gz, so a rebuild needs only g++.
# --codegen regenerates them from queries/<query>.sql with the upstream compiler
# jar (needs java). All plans compile against private patched copies of two
# upstream headers (the upstream checkout is left untouched):
#   ring/ring_factorized.hpp + signed-factorized.patch (correct deletions), and
#   dbtoaster/mmap.hpp + mmap-erase.patch (MultiHashMap::erase no longer scans a
#   buffer of every past insert; see record.txt). STOCK_MMAP=1 skips the latter.
# Set JOBS (default 4) to bound parallel compiles; the caller pins CPUs.
set -euo pipefail

if [[ $# -lt 1 ]]; then
  printf 'Usage: %s WORK_DIR [--codegen] [QUERY ...]\n' "$0" >&2
  exit 2
fi
here=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
work=$(realpath -- "$1")
shift
codegen=0
if [[ ${1:-} == --codegen ]]; then
  codegen=1
  shift
fi
all=(length3_filter length3_project length4_filter length4_project star_cnt twocomb dumbbell_full dumbbell)
queries=("$@")
[[ ${#queries[@]} -gt 0 ]] || queries=("${all[@]}")

fivm="$work/FIVM"
generated="$work/queries"
bin="$work/bin"
mkdir -p "$generated" "$bin/include/ring" "$bin/include/dbtoaster"
patch --quiet -o "$bin/include/ring/ring_factorized.hpp" \
  "$fivm/examples/include/ring/ring_factorized.hpp" "$here/signed-factorized.patch"
rm -f "$bin/include/dbtoaster/mmap.hpp"
if [[ ${STOCK_MMAP:-0} != 1 ]]; then
  patch --quiet -o "$bin/include/dbtoaster/mmap.hpp" \
    "$fivm/runtime/include/dbtoaster/mmap.hpp" "$here/mmap-erase.patch"
fi

for q in "${queries[@]}"; do
  if [[ $codegen == 1 ]]; then
    cp -- "$here/queries/$q.sql" "$here/queries/$q.order" "$generated/"
    java -Xmx4g -XX:ActiveProcessorCount=4 -jar "$fivm/compiler/target/scala-2.12/FIVM-assembly-1.1.jar" \
      "$generated/$q.sql" -l cpp -o "$generated/$q.hpp"
  elif [[ ! -f "$generated/$q.hpp" ]]; then
    tar -xzf "$here/generated-queries.tar.gz" -C "$generated" "$q.hpp"
  fi
done

compile() {
  local q=$1
  "${CXX:-g++}" -std=c++23 -O3 -DNDEBUG \
    -I"$bin/include" -I"$generated" -I"$here" -I"$here/plans" \
    -I"$fivm/runtime/include" -I"$fivm/runtime/include/dbtoaster" -I"$fivm/examples/include" \
    "$here/plans/$q.cpp" -o "$bin/$q" >"$bin/$q.build.log" 2>&1 \
    || { cat "$bin/$q.build.log" >&2; return 1; }
  printf '%s %s\n' "$(sha256sum "$bin/$q" | cut -c1-16)" "$bin/$q"
}
export -f compile
export bin generated here fivm
printf '%s\n' "${queries[@]}" | xargs -P "${JOBS:-4}" -I{} bash -c 'compile {}'
