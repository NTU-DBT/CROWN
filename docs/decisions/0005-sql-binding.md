# Decision 0005: owned SQL binding before CQ normalization

F03 introduces an owned SQL IR between libpg_query syntax and the normalized
CQ. Expressions have typed IDs, explicit operators, source positions, and
SQL type/nullability metadata. Physical occurrence IDs remain distinct from
table IDs. The catalog snapshot and original source are owned; no parser or
caller pointer survives binding.

Join construction has both an ordered unqualified column view and visible
qualified references. USING/NATURAL merge the unqualified keys and add SQL
equality predicates, retaining original qualified columns. Inner/cross joins
can flatten to occurrence products and predicates after binding. Join aliases
hide inner names; alias column lists rename an ordered prefix. ON scopes are
the joined inputs and exclude separate preceding comma items. These rules
are tested against manual output layouts and an independent interpreter,
with SQLite comparison where its dialect matches.

The catalog denotes flat physical relations with no inheritance edges or
SQL namespaces. The binding explicitly records `catalog_inheritance:none`
and each occurrence's requested `include_descendants` flag. Default scans and
ONLY therefore read the same declared flat rows; this is not a PostgreSQL
server inheritance catalog. Importers must preserve that boundary rather
than assume descendant relations are represented.

Requested set/bag semantics are retained. An outer SELECT EXISTS has a
separate singleton Boolean wrapper and records the inner SPJ mode independently
of its outer mode. Binding never supplies native admission or a runtime.
SQL NULL belongs only to the SQL expression boundary; it does not become a
classical core value.

The initial expression subset binds scalar comparisons, Boolean composition,
NULL/Boolean tests, validated literal casts, identity casts and typed positional
parameters. Integer widths and decimal specifications are retained. Supported
integer promotion has an explicit node; a width-changing column cast cannot
masquerade as identity. Arithmetic/functions, broader conversions, namespaces,
outer joins, CTEs, ordering/limits and non-EXISTS subqueries require further
implemented contracts and currently fail explicitly.

F04 must check casts/NULL conditions before merging equality classes, preserve
occurrence routing and local predicates, and define executable adapters.
F05 must supply full normalized identities and schema evolution. The v1
binding output is deterministic for a binding, not an alias-independent query
hash or serialized executable physical plan.
