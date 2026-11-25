# Isolated PostgreSQL 16 toolchain v1

Prepared 2026-11-12 from exact packages in the local Ubuntu apt index. Both
`.deb` files were downloaded to `/tmp/w05-postgres-package-v1`, SHA-256 checked
against apt metadata, then extracted into its `extracted/` tree. No package was
installed, no system path was changed, no cluster initialization was performed,
and no server was started.

The extracted PostgreSQL server and client are both 16.15. `postgres`, `initdb`,
`pg_ctl`, and `psql` all ran their `--version` probes successfully. `ldd` found
no missing direct shared libraries for those four binaries. The report records
the exact packages, hashes, paths, command statuses, and compiler environment.

| Package | Version | Extracted executable(s) | SHA-256 |
|---|---|---|---|
| `postgresql-16` | `16.15-0ubuntu0.24.04.1` | `postgres`, `initdb`, `pg_ctl` | `d60ae76fb862cd4cca7bfdcdcdcc271c5e1d75f6b7915305ce2d962735a4b666` |
| `postgresql-client-16` | `16.15-0ubuntu0.24.04.1` | `psql` | `4796f72e1a7270ad8c17b1ecb025cd453f692b42c10aaf89f6b476da61761eac` |

Executables are in
`/tmp/w05-postgres-package-v1/extracted/usr/lib/postgresql/16/bin` and shared
support files are in
`/tmp/w05-postgres-package-v1/extracted/usr/share/postgresql/16`. The support
tree contains `postgres.bki`, `postgresql.conf.sample`, `pg_hba.conf.sample`,
`pg_ident.conf.sample`, `information_schema.sql`, and `system_views.sql`.

The system `pg_config` still reports `/usr/lib/postgresql/16/bin` and
`/usr/share/postgresql/16`; those system directories remain absent because the
packages were only extracted under `/tmp`. Use the extracted absolute paths for
the prepared executables. The current process has effective UID 1000, but no
cluster initialization or startup was attempted. `toolchain-evidence.json`
contains the package metadata, source hashes, `ldd` result, environment paths and
command/exit records. `package-hashes.sha256` is a `sha256sum -c` receipt; the
human-readable command record is in `commands.log`.
