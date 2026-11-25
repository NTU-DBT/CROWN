# W05 SQL oracle environment inventory v1

Captured 2026-11-12. This is a bounded local environment check for W05 oracle
planning. SQL probes used DuckDB in-memory databases. No packages were installed,
no PostgreSQL server was started, and no maintained source or evidence packet was
changed.

## Local PostgreSQL availability

`/usr/bin/pg_config` is supplied by `libpq-dev`; it reports PostgreSQL 16.15 and
`/usr/lib/postgresql/16/bin`. That directory does not exist. `psql`, `postgres`,
and `initdb` are absent from PATH and from the reported bindir. No matching
PostgreSQL 16/18 server or client packages are installed, and no PostgreSQL
package archives were found in `/var/cache/apt/archives`.

APT's local package index has a `postgresql-16` candidate (16.15), but does not
list `postgresql-18`. This is repository metadata, not an installed or cached
server. No download or installation was attempted.

## DuckDB probes

| Interface | Version | Result |
|---|---|---|
| `/home/userroot/.local/bin/duckdb` | 1.5.0 (`3a3967aa81`) | In-memory CLI probe of the mixed DECIMAL `UNION ALL` returned the 38-digit integer and `0`. Default `NUMERIC` labels were `DECIMAL(18,3)`; DATE and BOOLEAN type labels were available. |
| Python `duckdb` module | 1.5.4, Python 3.12.3 | Explicit `DECIMAL(38,0)` retained a 38-digit integer; `DECIMAL(38,38)` retained `1E-38`; basic DATE and BOOLEAN literals worked. |

The Python probe also shows why a successful fixed DECIMAL cast does not make
DuckDB a complete oracle for CROWN's decimal value domain:

* `DECIMAL(39,0)` is rejected; DuckDB's maximum DECIMAL precision is 38.
* Unqualified `NUMERIC` is `DECIMAL(18,3)` here, and the 38-digit integer fails
  conversion to it.
* In a `UNION ALL` of `DECIMAL(38,0)` and `DECIMAL(38,38)`, DuckDB chooses
  `DECIMAL(38,0)` and converts `1E-38` to `0`. This loses an exact value.

CROWN's `Decimal` is itself bounded: at most 38 coefficient digits and scale
0..38, but it is a value type rather than SQL `DECIMAL(p,s)` coercion
(`include/crown/ir/scalar.hpp:30-32`). A fixed-scale DuckDB oracle is suitable for
cases whose SQL type/casts are explicitly fixed and matched. Do not use DuckDB's
mixed-scale union result as the expected CROWN result. The W05 contract also
requires matching casts, collation and types (`Refactor.md:389,1321-1324`); this
inventory did not audit DuckDB collation behavior. Full mixed-scale SQL NUMERIC
comparison may need an actual PostgreSQL server, which is not available in this
environment.

The DuckDB Python module version differs from the CLI version; this record
identifies which interface produced each observation.
Evidence, commands, outputs, local package status and source hashes are in
[`source-environment-evidence.json`](source-environment-evidence.json).
