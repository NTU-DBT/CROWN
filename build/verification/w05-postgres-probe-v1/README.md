# PostgreSQL 16 engine capability probe

This packet records capabilities of an isolated PostgreSQL engine for planning W05 SQL-oracle comparisons. It is **not** evidence that CROWN/W05 agrees with PostgreSQL, and it is not a CROWN build or test result.

## Setup and identity

- PostgreSQL `16.15 (Ubuntu 16.15-0ubuntu0.24.04.1)`, `server_version_num=160015`; extracted server and client packages were used without installation.
- Server package SHA-256: `d60ae76fb862cd4cca7bfdcdcdcc271c5e1d75f6b7915305ce2d962735a4b666`. Client package SHA-256: `4796f72e1a7270ad8c17b1ecb025cd453f692b42c10aaf89f6b476da61761eac`.
- Explicit BKI path: `/tmp/w05-postgres-package-v1/extracted/usr/share/postgresql/16/postgres.bki`; SHA-256: `e7ccf0cbdf9a993e2bbfd99e3c4bb2161036ad33233d66281756750c409c983f`. Full package/toolchain receipt: [toolchain-evidence.json](../w05-postgres-toolchain-v1/toolchain-evidence.json).
- The cluster was initialized as the current UID 1000 user, with the extracted sharedir, UTF8 encoding, no locale, and dedicated role `w05oracle`. It listened only on a mode-0700 private Unix socket directory at `/tmp/w05-postgres-probe-v1/socket`; `listen_addresses` was empty. `psql` ran with `--no-psqlrc`.

## Captured SQL results

The fixed SQL is in [queries.sql](queries.sql). Decimal values and query outputs were converted to text/JSON strings; no client-side floating point was used.

| Capability | PostgreSQL result |
|---|---|
| One unconstrained `numeric` column | `atttypmod = -1`; exact ascending values were `0.00000000000000000000000000000000000001` and `99999999999999999999999999999999999999`; exact equality checks and integer-greater-than-tiny comparison were true. |
| SQL NULL equality | `NULL::numeric = NULL::numeric` was `UNKNOWN`; `IS NULL` was true and its text/JSON value was null. |
| GROUP BY and DISTINCT over duplicates and NULL | Group counts: NULL 2, `x` 2, `y` 1. DISTINCT values: NULL, `x`, `y`. |
| DATE and BOOLEAN | Date text `2024-02-29`; JSON booleans true and false. |
| Explicit `COLLATE "C"` | Same-text equality, `A < a`, and `z < é` all returned true. |

The numeric probe demonstrates these exact mixed-scale values in one unconstrained PostgreSQL `numeric` column. It is still a capability probe over selected values, not an exhaustive characterization of PostgreSQL NUMERIC or CROWN Decimal behavior.

## Attempt history and cleanup

Attempt 1 reached four successful JSON rows, then stopped on a probe-only catalog lookup that folded collation name `C` to `c`. Its SQL and command log are retained as `attempt-1-failed.sql` and `attempt-1-failed.log`. Attempt 2 removed that catalog lookup while keeping the explicit `COLLATE "C"` expressions. `psql` exited 0 and emitted all five rows. The first local aggregation check nevertheless reported a false result for its combined date/boolean/collation assertion; the psql output itself includes `C_same_text_equal=true`. Its failed-check receipt and log are preserved as `attempt-2-output-validator-failed.json` and `attempt-2-output-validator-failed.log`. A subsequent offline validation checked each returned field and passed; it started no database.

Both server starts were stopped in cleanup. The latest `pg_ctl status` returned exit code 3 (`no server running`), `postmaster.pid` was absent, the private socket directory was empty, and no owned postgres process remained. The data directory and logs remain in the private `/tmp/w05-postgres-probe-v1` tree for local evidence.

See [probe-evidence.json](probe-evidence.json) and [commands.log](commands.log) for structured results and command/exit records.
