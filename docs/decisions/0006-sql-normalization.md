# Decision 0006: occurrence-preserving SQL normalization

F04 is implemented and verified at the normalization/adapter boundary; see the
[verification packet](../verification/normalization-2026-11-05.md). It does not
claim structural admission or a maintained SQL runtime. See the detailed
[F04 normalization contract](../sql_normalization.md).

## Context

F03 owns a typed, occurrence-aware SQL binding, but a binding is not yet a
direct CQ. The next step must identify unconditional equality joins while
preserving the SQL behaviors that a classical non-null set CQ cannot express
by itself: local predicates, NULL filtering, ordered SQL outputs, `EXISTS`,
and projection from full physical rows. F04 also has to route a physical
update to every alias of that table without exposing partial alias state.

## Decision

Normalize by occurrence identity, not base-table identity. A direct CQ atom
is retained for every bound `FROM` occurrence, including self-join aliases
and equal or contained scopes. Union-find keys are `(occurrence ID, physical
column index)`. A union is permitted only for a direct unconditional column
equality after typed identity/widening, cast, and NULL checks. Equalities
inside `OR` or `NOT` are not unconditional CQ edges. Intra-occurrence repeated
columns become checks in that occurrence's adapter. Typed constants and
specialized parameters remain exact filters or constant results.

Each occurrence has a local adapter for its row predicates, local expression
program, repeated-column checks, and projection into the core atom. Local
scalar comparisons and Boolean/NULL tests use SQL three-valued logic, and a
filter passes only on `TRUE`. Cross-occurrence non-equality filters and
multi-occurrence Boolean predicates are outside this F04 contract. The core
value model still has no NULL.

All columns of a referenced physical source table must be declared
non-nullable; unused nullable columns are rejected too. NULL literals and
nullable parameter values may participate in local filters. Row outputs that
can be NULL and computed outputs spanning multiple occurrences are rejected.
Computed outputs confined to one occurrence may be evaluated by its adapter.
Output order, labels, types, and repeated positions survive equality-class
merging.

Plain row-producing bag `SELECT` is rejected without implicit `DISTINCT`.
`SELECT DISTINCT` is set-valued. The whole-result `EXISTS` wrapper is a
singleton SQL Boolean row over a nullary CQ result; its inner set/bag mode and
inner select-list values do not change existential truth. The wrapper is not
serialized as a nullary core row.

The normalization is specialized by one concrete value for every declared
parameter. `PARAMETER_VALUES.json` is `{ "schema_version": 1, "values": [...] }`
in positional order, using the declared scalar types and allowing JSON null
only for nullable parameters. Changing values requires a new normalized
program and a new adapter state.

When a physical table update occurs, route it to every occurrence in stable
occurrence-ID order. Preserve full physical row identity and support counts
through projection, so a logical row remains while any distinct physical row
supports it. Prepare all affected alias and support changes as one
`AdapterState` copy-commit. A constraint failure changes neither state nor
sequence. A valid duplicate insert or absent delete follows the reference
event policy and advances the sequence without changing rows.

## Consequences and remaining work

- `normalize-sql` is a binding-plus-normalization frontend command. Its
  command exit channels are success `0`, JSON diagnostics on stdout `1`,
  configuration errors on stderr `2`, and internal invariant failures on stderr
  `3`.
- Normalization does not check alpha-acyclicity/free-connexity, choose a
  structural plan, or provide maintained result deltas. Those stay separate
  planner and runtime tasks.
- F05 defines the normalized-program schema, canonical semantic hashes and
  explicit evolution/upgrade rules; see [decision 0007](0007-schema-identity.md).
  Physical plan/runtime compatibility remains a later boundary.
- The verification packet records SQL-versus-handwritten-CQ agreement under
  A04 and finite adapter/CLI evidence. Full Refactor.md release gates remain
  open.
