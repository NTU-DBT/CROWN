# Tuple layouts and storage backends (S01–S04)

This page describes the implemented and verified S01/S02 API in [Refactor.md](../Refactor.md)
§6.2. The verification audit and build records are in
[storage verification](verification/storage-2026-11-05.md).
The payload owner is now the [S03 generational tuple arena](tuple_arenas.md);
the original S01/S02 verification packet predates that integration.

S04 adds the separately verified [indexed backend and runtime route](indexed_storage.md).
The early19-test Debug/SAN preparation is historical; the [ledger](task_ledger.md)
records the completed native matrices and source gates. The reference API below
remains the default and semantic comparison target.

## Typed layouts and owned tuples

`TupleLayout` is an immutable ordered descriptor. A field records its
`ScalarType`, optional fixed-decimal domain, and optional logical variable.
The layout also carries a catalog/binding context and optional physical table
and source-schema origin. `table_layout`, `scope_layout`, and
`projected_layout` provide common constructors. Field names are resolved
before storage programs are compiled; storage operations use numeric
`FieldId` positions.

Layout copies share an immutable runtime token. `same_token` checks that
identity; `same_descriptor` checks the descriptor values, including the layout
ID, fields, context, and origin. Equal descriptors constructed independently
do not share a token. Constructing a tuple validates arity, exact scalar
types, decimal bounds, and equality between positions annotated with the same
variable. Tuples own their values and strings and expose read-only views.

Layout and projection `fields()` return immutable ranges; a layout's context
contains a borrowed binding string. Keep a handle sharing the descriptor token
alive while using those views. Make an explicit vector or string copy when an
independent, mutable value is needed.

`AccountedLayout::make` constructs a native descriptor from borrowed fields,
context and origin, copying its storage into the query account. Its `descriptor()`
method, and the corresponding method on `AccountedProjection`, return readable
handles sharing that allocation and token without another array, string or
control-block allocation. A returned tuple can therefore keep its funded layout
alive after its cursor and runtime are destroyed.

Plan/catalog IDs are scoped to their compiled document. A table's tuple and
index IDs are nonzero, monotonically allocated within its storage owner, and
not reused after erase or clear. A `TupleHandle` carries the owner, relation,
and tuple ID, so a handle from another owner or relation is rejected. ID
exhaustion fails without wrapping. `ReferenceTable::get` returns a borrowed
tuple pointer valid only until erase, clear, or table destruction.
The internal [reversible journal](storage_journal.md) adds tentative handles:
aborted insert IDs can be reused, so they must remain unpublished until commit.

## Compiled projections

`Projection` stores an ordered sequence of numeric source slots and an
explicit target `TupleLayout`. Applying it checks the source token and copies
selected values into a tuple carrying the target token. It performs no
rounding or value conversion. Source and target layouts must have equal
contexts, selected scalar kinds must match, and decimal compatibility allows
only exact domain widening. A generic decimal target can accept fixed decimal
sources with different bounds; a fixed target must contain the source's full
precision/scale domain. Repeated target variables are accepted only when the
selected source positions are the same or are already proven equal by a
repeated source variable; annotated source and target variable IDs must also
agree.

Projections may be composite, reordered, repeated, or nullary. Key layout
identity is explicit: projections from different source layouts can
interoperate when they share the same target token and output meaning. Equal
target descriptors with independent tokens do not interoperate in an index.
All projections that address the same nullary key also need the same target
token. Exact typed values decide key equality; hashes only select candidates.
See [scalar semantics](scalars.md) for value encoding and decimal behavior.
Storage values are non-null; this layer adds no SQL NULL or coercion rules.

## Reference table and cursors

`ReferenceTable` is a movable, noncopyable set relation implemented with
ordered `map`/`set` containers. Its tuple arena owns immutable values; the
primary map borrows their stable addresses and provides exact full-row lookup.
The ID map records each live allocation's slot and generation. Secondary
indexes map projected keys to live tuple
handles. Buckets with no members are removed. Duplicate insertion, deletion
of an absent row/handle/key, adding the same projection program again, dropping
an absent index, and clearing an empty table are no-ops. Independently compiled
projection programs may have separate indexes even when they select the same
fields.

The table revision advances for row insert/delete, a nonempty clear, and
index add/drop. Each real mutation invalidates its live cursors. `live()` and
`bucket_cursor()` return weak-owner, fail-fast cursors over handles; `next()`
fails if the owner is destroyed or the table revision changed. Cursors do not
pin records. `pin(handle)` explicitly retains an immutable tuple payload across
erase, clear or table destruction; it does not retain membership or a cursor.
`arena_statistics()` reports live/retired/pin/free/exhausted slot counts.
`snapshot()` returns an owning `std::vector<Tuple>` copy;
it is not a cursor and remains usable independently of later table changes.
The API also provides `find`, `get`, `bucket`, `keys`, `erase_key`,
`check_invariants`, and index inspection.

Mutations provide a per-table strong exception guarantee: if validation,
allocation, projection, or a container update throws, primary rows, every
secondary bucket, ID counters, and revision remain unchanged. Insertions roll
back staged changes; a temporary successful arena allocation can leave free
high-water slot metadata or advance a private slot generation after a later
map failure. Erasures finish all potentially throwing preparation
before removing records. This does not provide transactions across multiple
tables or update epochs. Operations are single-threaded; callers must
externally synchronize concurrent access.

`journal()` opens an exclusive reversible insert/erase scope. It prepares undo
keys, pins affected allocations and retains extracted map/set nodes; rollback
restores original row IDs, generations, addresses and indexes without allocating.
Commit retains ordered change views until the journal is freed. Revisions stay
advanced after real tentative changes, so cursors remain invalid after rollback.
Ordinary mutators and cursor creation/advance reject while the scope is active;
internal reads can inspect tentative rows. See the
[journal contract](storage_journal.md) for lifetime and publication rules.
The support kernel combines touched-table scopes with metadata undo for a
logical and physical alias updates; the actual indexed route is documented separately.

### API sketch

Different source layouts can address one index by sharing the target layout
token explicitly:

```cpp
#include "crown/storage/reference.hpp"
#include <cstdint>

using namespace crown;
using namespace crown::storage;

int main() {
  const LayoutContext context{1, "join"};
  const TupleLayout left_layout{LayoutId{1}, {{ScalarType::int64, {}, {}}}, context};
  const TupleLayout right_layout{LayoutId{2}, {{ScalarType::int64, {}, {}}}, context};
  const TupleLayout key_layout{LayoutId{3}, {{ScalarType::int64, {}, {}}}, context};

  const Projection left_key{left_layout, key_layout, {FieldId{0}}};
  const Projection right_key{right_layout, key_layout, {FieldId{0}}};
  ReferenceTable right{RelationId{2}, right_layout};
  const auto index = right.add_index(right_key);
  static_cast<void>(right.insert(right_layout.tuple({std::int64_t{7}})));

  const auto probe = left_key.apply(left_layout.tuple({std::int64_t{7}}));
  const auto matches = right.bucket(index, probe);
  return matches.size() == 1 ? 0 : 1;
}
```

`matches` contains right-table handles whose projected key equals the probe.
The two source layouts differ, while both projections produce keys with the
same `key_layout` token.

## Versioned artifacts

The wire formats are defined by [tuple-layout v1](../schemas/tuple-layout-v1.schema.json)
and [key-projection v1](../schemas/key-projection-v1.schema.json). They store
descriptors, not runtime tokens. `io::read_layout` creates a fresh layout
token; callers that need an existing runtime identity must compare the full
descriptor and retain/rebind to their caller-owned layout. `io::read_projection`
requires caller-supplied source and target layouts, checks both complete
descriptors, then constructs the projection with those supplied tokens.

## Verification

S01/S02 acceptance is verified. The final build matrix, independent storage
model, failure-atomicity checks, schema audit, and reproduction commands are
recorded in the [storage verification packet](verification/storage-2026-11-05.md).
The current arena/journal integration and all previous tests pass the 39-test
matrix; see [R04 verification](verification/runtime-journal-2026-11-05.md).

## Scope boundary

This verified foundation provides typed layouts, compiled projections, and the
standard-container reference backend with [generational arena ownership and
explicit pins](tuple_arenas.md). This S01–S03 scope predates later work: S04 verified optimized indexes;
S05 verified the native query-byte account; later R/D work verified physical epochs
and result cursors. See the [task ledger](task_ledger.md) for their separate scope
and acceptance. The separate
[support kernel](runtime_support.md) maintains logical S/P/E state on this
backend using affected-record metadata/storage journals.
