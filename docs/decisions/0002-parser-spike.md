# Decision 0002: libpg_query parser build spike

Historical spike decision. The production wrapper and offline dependency
integration now follow [sql_parser.md](../sql_parser.md); their verification
is recorded separately from the spike results below.

Date: 2026-11-05.
Status: Spike built and smoke-tested; dependency pinned in `dependencies.lock.json`.

## Decision

Use the official `pganalyze/libpg_query` 18.1.0 release for the A01 build
spike. The immutable tag resolves to commit
`c1546e7e97edc93fe8474d7a59881e91fbf48cfc`. It contains PostgreSQL 18.6's
parser. The release is pinned by the source archive SHA-256, rather than by a
moving branch or the short tag alone.

The committed smoke tool downloads the source archive when absent, checks its
SHA-256 before extraction and on every run, then builds the upstream static
library through `make`. The 18.1.0 release includes the generated PostgreSQL
18.6 parser sources. The upstream `make build` target compiles those bundled
sources and does not download PostgreSQL. The separate `extract_source` target
regenerates the bundled files from PostgreSQL source and is outside this
smoke.

## Pin and provenance

| Item | Pinned value |
| --- | --- |
| Official repository | <https://github.com/pganalyze/libpg_query> |
| Release | `18.1.0` |
| Full commit | `c1546e7e97edc93fe8474d7a59881e91fbf48cfc` |
| Release archive URL | <https://codeload.github.com/pganalyze/libpg_query/tar.gz/refs/tags/18.1.0> |
| Release archive SHA-256 | `2d3486cf6a9d3955b53e66235db39d62b54216c820cd392ab66dc842c5b1316d` |

The libpg_query release page publishes the matching source archive checksum and
identifies the tag commit. The official GitHub API confirmed the full commit
SHA. These pin values are recorded in the project dependency lock. The spike
is optional and separate from the root CMake build.

## License notes

libpg_query's README says its non-PostgreSQL library parts are under the
3-clause BSD license in the repository `LICENSE`. It also identifies the
bundled PostgreSQL server source as PostgreSQL License, `vendor/upb` as
3-clause BSD, `utf8_range` as MIT, and `xxHash` as 2-clause BSD. The PostgreSQL
server sources included in the release retain their PostgreSQL License.
Preserve each component notice when redistributing these sources.

## Smoke behavior

`tools/parser_spike/smoke.c` calls `pg_query_parse` for a valid
`SELECT DISTINCT category FROM sample;` and malformed `SELECT FROM ;`. It
requires a `SelectStmt` without error for the first and an error for the
second, then calls `pg_query_free_parse_result` on both result structs. This
exercises the C API's allocation/free lifecycle on both return paths.

Run from the repository root:

```sh
mkdir -p build/parser-spike
./tools/parser_spike/run.sh > build/parser-spike/run.log 2>&1
```

All download, extraction, library build, smoke executable, and captured log
outputs are under the ignored `build/parser-spike/` directory. The upstream
build step is `make -C build/parser-spike/work/libpg_query-18.1.0 CC=cc build`.
The script uses the `CC` environment variable when set; otherwise it uses
`cc`.

## Run evidence

The clean run on 2026-11-05 passed archive checksum verification, upstream
`make build`, C compilation/linking, and the smoke executable. The compiler was
`cc` / GCC 13.3.0 (`Ubuntu 13.3.0-6ubuntu2~24.04.1`). The smoke output was:

```text
SELECT DISTINCT parsed successfully
malformed SQL rejected: syntax error at or near ";"
both parse results freed
```

The upstream build emitted two `-Wmaybe-uninitialized` warnings in bundled
`vendor/upb/upb.c` about `sv.data` and `sv.size`; it still produced
`libpg_query.a` and the linked smoke passed. No second compiler was available
to this spike (`clang` and `clang-18` were not found), so this parser library
was not separately built with one. No compiler was installed.

The syntax parser accepting a statement says only that its SQL is syntactically
valid for this PostgreSQL parser version. It does not establish catalog
binding, supported CROWN semantics, a CQ translation, or query admission.
Parser success must not be treated as admission; those checks belong to the
binder and frontend acceptance path.

