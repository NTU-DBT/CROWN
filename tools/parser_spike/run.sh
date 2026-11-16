#!/bin/sh
set -eu

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
repo_root=$(CDPATH= cd -- "$script_dir/../.." && pwd)
build_dir="$repo_root/build/parser-spike"
work_dir="$build_dir/work"
source_dir="$work_dir/libpg_query-18.1.0"
download_dir="$build_dir/download"
archive="$download_dir/libpg_query-18.1.0.tar.gz"
archive_url=https://codeload.github.com/pganalyze/libpg_query/tar.gz/refs/tags/18.1.0
archive_sha256=2d3486cf6a9d3955b53e66235db39d62b54216c820cd392ab66dc842c5b1316d
cc_bin=${CC:-cc}

curl_bin=$(command -v curl) || {
  echo "parser spike requires curl" >&2
  exit 1
}
sha256sum_bin=$(command -v sha256sum) || {
  echo "parser spike requires sha256sum" >&2
  exit 1
}
command -v "$cc_bin" >/dev/null 2>&1 || {
  printf 'parser spike compiler not found: %s\n' "$cc_bin" >&2
  exit 1
}
command -v make >/dev/null 2>&1 || {
  echo "parser spike requires make" >&2
  exit 1
}

mkdir -p "$download_dir" "$work_dir"
if [ ! -f "$archive" ]; then
  download_tmp="$archive.tmp.$$"
  trap 'rm -f "$download_tmp"' 0 HUP INT TERM
  "$curl_bin" --fail --location --retry 2 --proto '=https' --tlsv1.2 \
    --output "$download_tmp" "$archive_url"
  printf '%s  %s\n' "$archive_sha256" "$download_tmp" \
    | "$sha256sum_bin" --check -
  mv "$download_tmp" "$archive"
  trap - 0 HUP INT TERM
fi
printf '%s  %s\n' "$archive_sha256" "$archive" | "$sha256sum_bin" --check -

# Always build from a fresh extraction of the verified archive.
rm -rf "$source_dir"
tar -xzf "$archive" -C "$work_dir"

printf 'Building libpg_query 18.1.0 with %s via upstream make build\n' "$cc_bin"
make -C "$source_dir" CC="$cc_bin" build

"$cc_bin" -std=c11 -Wall -Wextra -Werror \
  -I"$source_dir" \
  "$script_dir/smoke.c" "$source_dir/libpg_query.a" -pthread \
  -o "$build_dir/parser-smoke"

"$build_dir/parser-smoke"
