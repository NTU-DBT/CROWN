# Epoch views and fragment cursors (D02)

Status: D02 is implemented and verified. At that checkpoint, all 49 tests passed GCC Debug/Release,
ASan/UBSan, Clang18 and a fresh source-only Release build; see the
[verification packet](verification/fragment-cursors-2026-11-06.md). The
[47-test foundation packet](verification/epoch-views-2026-11-06.md) records the
predecessor checkpoint. This page makes no D05 delay-bound claim and does not
specify delta or sink acceptance. The [D04 delta owner](delta_runtime.md)
adds private stage-local contexts and E-factor scans to this foundation.
D05 adds indexed restored-key/separator access and `visible_bucket`;
the current 66-test five-configuration matrix is recorded in the
[pending lifecycle packet](verification/delta-lifecycle-2026-11-06.md).
Its delta-specific production bound is separate from these general partial
binding/fragment cursor costs.

The API is declared in
[`support.hpp`](../include/crown/runtime/support.hpp) and implemented in
[`support.cpp`](../src/runtime/support.cpp). `PhysicalRuntime` forwards
pending and committed view calls through
[`physical.hpp`](../include/crown/runtime/physical.hpp) and
[`physical.cpp`](../src/runtime/physical.cpp). The underlying owner-only
tentative table cursors are `ReferenceTable::Journal::live()` and
`bucket_cursor()` in [`reference.hpp`](../include/crown/storage/reference.hpp)
and [`reference.cpp`](../src/storage/reference.cpp).

## What an epoch view represents

`PendingEpoch::view(side)` freezes the staged prefix while it is held. Its
`before` side represents the state immediately before the pending epoch; its
`after` side represents the current staged state. The view does not clone the
runtime state or materialize the answer relation. It shares a `Group` with
other views of that pending prefix and their cursors. The group keeps the plan,
the journal-backed patches, and one read lease on the runtime.

The `after` side traverses live support tables. While the epoch is tentative,
it opens the matching journal's owner-only live or bucket cursor; after
commit, new traversal uses ordinary live or bucket cursors. The
`ReferenceTable::Journal` reader token is created lazily by its first live or
bucket cursor factory. A valid raw storage `next()` does not allocate. An
active journal accepts reads through its own token; a cursor from a different
journal does not inherit that access. A cursor already open through the owning
token remains usable after commit unless a different journal has started,
while rollback marks the token aborted. Ordinary public runtime reads remain
blocked while the pending epoch is active.

The `before` side overlays the journal's membership changes on the current
staged tables:

- Rows inserted by the pending epoch are excluded from the live table walk.
- Rows deleted by the pending epoch are restored from journal-pinned tuples.
- Journal records that do not change relation membership need no visibility
  patch.

For a fully determined relation step, the cursor constructs the tuple from its
fixed, outer-fragment, and previously selected values, then checks the primary
live-table lookup and a full-key restored-tuple lookup. Group construction
indexes restored tuples by full value key and by every existing compiled
relation index. A parent-key bucket walk uses only the matching restored
separator bucket after its live bucket ends; an empty bucket does not scan
unrelated restored tuples. Excluded live members are still filtered by tuple
ID. These indexes own affected keys and point to journal-pinned tuples.
Whole-relation walks still traverse the full restored set. No new compiled
indexes are added to survivor relations: a partial witness-factor scan uses
its live cursor and the full before-side restored overlay.

The journal pins keep deleted tuples available to before-side cursors after
commit. Commit changes the shared group to committed without invalidating its
views or cursors. A later input is blocked while any view or cursor still
holds the group's read lease. This includes inputs that would otherwise be
no-ops.

`current_view()` creates an independent committed group with side `after` and
both sequence values equal to the current committed sequence. It is valid and
not tentative. `valid()`, `tentative()`, `side()`, `sequence()`, `owner()`, and
`metrics()` describe the handle/group. `close()` drops only that handle; copies
and cursors retain their own references.

## Projected completions

`EpochView::results()` is shorthand for `completions({}, {})`. A completion
cursor enumerates projected core rows; it does not apply the SQL output
mapping. `PhysicalRuntime::results()` and `core_results()` keep their D01
behavior: SQL plans still use the SQL mapping through `results()`, and
`core_results()` still returns core output.

`completions(fixed, fragment, options)` validates every fixed assignment at
construction. The variable must be in the query's variable range and the
value must have its exact scalar type. Repeating the same variable/value is
accepted; conflicting values for one variable fail with `invalid_binding`.
Bindings may name visible or hidden query variables. A hidden binding is a
witness restriction; it is not added to the output schema.

With no fragment root, the cursor keeps the original core head order and the
normal D01 visible-relation enumeration. With a root, the root must be a valid
C* (`connex`) node or construction fails with `invalid_fragment`. The cursor
enumerates that node's C* descendants and outputs their visible variables in
sorted variable-ID order. This fragment schema is distinct from the core head
schema. A binding absent from the entire chosen physical subtree, including
its hidden branches, is validated and has no effect. Hidden variables in
those branches remain relevant even though they do not appear in E or in the
output schema.

For a hidden binding that occurs in the selected physical subtree, each candidate
projected row is checked by an iterative existential search over that entire
local `S` survivor subtree. The probe is correlated with the visible candidate
and all fixed values. It stops at the first successful witness in each child
subtree. The running-intersection property makes child existence tests
independent once their shared parent assignment is fixed, so the cursor does
not enumerate a hidden Cartesian product or retain witness history. The probe
acts only as a yes/no filter: a candidate is emitted once if any compatible
hidden witness exists, regardless of how many witnesses match. Therefore
hidden multiplicity cannot duplicate projected completions. If a hidden
binding variable does not occur in the selected subtree, it has no effect
after validation.

The existential probe uses ordinary fixed-value and join checks, so a mismatch
rejects that candidate. A fully determined factor tuple uses primary lookup;
partial witness factors are scanned through their live/ghost cursor path. The
D01 path remains `E`-only when no hidden binding requires the existential
probe.

## Full local witness assignments

`witnesses(fixed, fragment, options)` is a separate cursor over local survivor
factors. It emits a full assignment to the selected factors: every selected
factor variable appears once, sorted by variable ID, including hidden
variables. It does not project assignments onto the query head and does not
apply an outside-parent restriction.

`WitnessFragment` selects factors as follows:

- With neither `root` nor `nodes`, it selects the whole physical tree.
- `root` selects that physical node and its entire subtree, including nodes
  outside C*.
- `nodes` selects exactly that set of physical factors. The set may be
  disconnected or non-adjacent; repeated or out-of-range node IDs fail with
  `invalid_fragment`.
- `root` and `nodes` cannot both be present. An explicit empty `nodes` set is
  the nullary identity and emits one empty assignment.

Each selected factor is its node's `S` survivor relation, which already
records the existence of the node's original descendants. It is not a raw
subset of base atoms. When factors share a variable, tuple values must agree;
the cursor enforces those joins even if the factors are non-adjacent or
disconnected in the physical tree. A fully determined factor tuple can use a
primary lookup, while partially bound factors scan the current live members
and the before-side restored overlay as applicable.

Fixed bindings for `witnesses` use the same query-range, exact-type, and
duplicate-value validation as `completions`. A binding that does not occur in
any selected factor is validated and then ignored. Every returned tuple owns
its scalar values and remains valid after the cursor closes.

## Prefix and handle lifetime

Holding any view or an active cursor from it seals the pending prefix. A
further `stage()` fails with `runtime_busy` before staging work and leaves the
pending epoch active; it does not auto-abort. Once every view and cursor handle
has been closed or destroyed, the next `stage()` drops the pending token's
cached group and can continue the epoch. Calling `close()` on one copied view
does not close its other copies or any cursors. Exhausted, failed and cancelled
cursors release their group reference; keeping such a closed cursor object
only retains its metrics and fixed query/output metadata.

Commit preserves the group, before-side deleted values, and active cursors.
Those handles continue to block the next input until they are all released.
Rollback marks the group aborted and closes its intrusive cursors without
allocation before metadata and storage undo runs. It then releases the read
lease. Held view handles become invalid but do not prevent a retry at the same
sequence. Tuples returned from a tentative view are owner-only: keep them
private until commit and discard them if rollback occurs.

View and cursor construction failures do not auto-abort the pending epoch.
`EpochViewOptions::work_limit` applies while the shared group is first built.
Later `view()` calls for the same pending prefix reuse that group, so their
options do not rebuild its patches or apply a second group-construction limit.

## Work limits and scope

`EpochViewOptions::work_limit` defaults to 1,000,000 abstract units. Group
construction charges one unit per support journal record scanned, one more
for each relation-membership change, and one more for each restored or
excluded row recorded in the patch. It also charges each restored full-key
entry, each restored entry in an existing relation index, and the fields
projected/copied for those keys. `EpochViewMetrics` exposes these as
`restored_key_entries`, `restored_bucket_entries` and `key_fields` in addition
to the original patch counts. The view does not count copied plan data,
container allocation, dictionary comparison cost, or bytes copied.

`ResultCursorOptions::work_limit` independently caps one cursor's cumulative
abstract startup, result, termination, and failure work. The cursor reports
these phases separately. `CursorWork` includes `binding_values`,
`binding_checks`, `binding_rejections`, `direct_lookups`, `overlay_rows`,
`fragment_steps`, `descriptor_steps`, `witness_probes`, `witness_rows`, and `join_rejections`,
along with live cursor and tuple operations. Witness probes and selected
witness rows are charged against the same cursor-wide limit as projected
results. Mandatory frame cleanup on cancellation or failure is reported by
`cleanup_frames`; it is uncharged and bounded by the number of frames.
`descriptor_steps` charges each inspected compiled step when locating a
visible bucket's enumeration descriptor, including query-size setup work.

These counters describe selected abstract operations. They do not measure
bytes, wall-clock time, or a delay bound. A before-side bucket can revisit its
matching restored rows for multiple outer assignments, and an unindexed
existential witness search can inspect multiple candidate factor rows before
finding a witness or proving none exists. No D05 delay guarantee is claimed.

`visible_keys(node)` reads exactly one C* E relation in the selected context,
including globally unlive keys. Its output layout is that relation's complete
sorted visible schema. It uses the same before patches, table writers, reader
lease and cursor-abort rules. `visible_bucket(node, separator)` restricts one
nonroot C* E factor to its compiled parent-separator index. The separator uses
sorted separator-variable order and exact arity/scalar types; a nullary
separator is valid for a product edge. Root/outside-C* nodes fail with
`invalid_fragment`, invalid key values with `invalid_tuple`. It returns full
local E keys and does not join descendants or apply global liveness.
`has_answer()` reports the context's core truth;
closed or rolled-back contexts reject the call. `result_layout(view)` reads
immutable core/SQL layout metadata without opening a reader.

The [D04 delta owner](delta_runtime.md) uses a private checkpoint to select an
adjacent alias-stage interval while preserving these public whole-epoch
`before` semantics. Delta maintenance, publication and sink behavior remain
outside this D02 contract.
