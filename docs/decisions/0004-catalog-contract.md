# Decision 0004: catalog metadata and committed constraints

Standalone catalog format 1 and CQ format 3 share one strict typed payload.
The previous CQ formats keep their shapes; old writers reject metadata they
cannot preserve. Catalog and per-table source schema versions are positive
unsigned 64-bit values. IDs are scoped to their catalog version. The owner
must advance the catalog version when its schema changes; sessions own their
catalog copy. No online schema mutation or migration is implemented.

Constraint declarations carry `enforced` or `untrusted` status. There is no
unchecked externally trusted flag. Enforced foreign keys require an enforced
unique target with the same column set and compatible typed positions. The
reference path validates the complete proposed database, so updates to either
side, including self-references, are checked before commit. Keys may be
composite, reordered or empty. No cascade or constraint-driven rewrite is
performed. Indexed enforcement and safe specializations remain later work.

Statistics and key hints are distinct metadata with no semantic authority.
Their values may be inaccurate and become stale as data changes. They cannot
remove an occurrence or bypass admission checks. Catalog validation checks
their shape/references, not their empirical truth.

Sources may declare nullable columns, but the current direct-CQ value domain
has no NULL and rejects nullable catalogs explicitly. F04/W05 must implement
the source/adapter boundary before admitting nullable SQL sources. Binary
string collation is the only supported collation. Catalog lookup reports
ambiguous visible column names with their candidate qualifiers. Explicit
casts are checked before equality normalization: only identity casts are
implemented, including unchanged decimal precision/scale and nullability.
A cast never supplies a non-null proof. Bare equality of
exact decimal values across compatible declared scales remains exact and is
not a cast.

Optional decimal `(P,S)` metadata bounds exact representability. The canonical
value does not acquire spelling-dependent scale, and no value is rounded or
truncated. Value/row equality and hashes retain the scalar contract. Decimal
rvalue operations preserve canonical source and destination values by using
its bounded coefficient's copy semantics.

Height certificate bindings use CQ format 3 when nondefault metadata exists,
otherwise format 2 for date/decimal catalogs and format 1 for primitive
catalogs. Metadata changes therefore cannot silently reuse a certificate with
a different exact binding. These are structural certificates, not executable
physical plans; F05/P08 still need the full physical schema identity and
invalidation contract.
