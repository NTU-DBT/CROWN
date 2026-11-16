# Physical plans and lowering (P08)

P08 compiles a validated CROWN tree into typed layouts, numeric projections,
index requirements, node wiring and a parent-before-child enumeration program.
The public API is in [`physical.hpp`](../include/crown/ir/physical.hpp),
[`lower.hpp`](../include/crown/planner/lower.hpp),
[`io/physical.hpp`](../include/crown/io/physical.hpp), and
[`storage/physical.hpp`](../include/crown/storage/physical.hpp). This contract
is verified at the compiled-plan/reference-storage boundary. Creating a `PhysicalPlan` does not
install a maintained join runtime or establish runtime performance bounds.
`PhysicalPlan` owns shared immutable data. Its data constructor is private;
validated lowering or replay originates a plan, while existing plans can be
copied and moved publicly.

See [tree plans](tree_plans.md) for structural tree validity,
[storage](storage.md) for typed layouts and reference tables, and
[Refactor.md §P08](../Refactor.md) for the acceptance target.

## Admission and routes

`planner::lower_tree(catalog, query, tree, options)` receives the actual
catalog, query and supplied tree. It performs its own query/tree validation;
a caller cannot authorize a tree by passing a mutable validation report or a
boolean. A structural validation result gives a valid upper bound only. The
lowering API does not choose a minimum-height tree, prove optimality, or accept
an `optimal` flag. Strict minimum-height selection belongs to the planner and
height-evidence work, not P08.

`planner::lower_normalized(program, tree, options, program_limits)` first
replays the complete normalized program. A legacy normalized v1 program is
grounded to v2 before the tree is checked against the resulting core catalog
and query. Thus the supplied tree must describe the grounded core, including
its surviving occurrences and scopes. This path retains the source catalog,
program and typed input adapters needed to lower SQL-normalized input.

There are three physical routes:

| Route | Input shape | Physical contents |
| --- | --- | --- |
| `tree` | A nonempty, noncontradictory core query and a valid supplied tree | Compiled node, relation, edge, input-adapter, index and enumeration descriptors. |
| `constant_true` | An empty body and its canonical empty tree | A constant true result with a nullary result layout and no tree nodes. |
| `constant_false` | An explicit contradiction, with its canonical empty tree even when the original body is nonempty or cyclic | A constant empty result with no runtime nodes. Original atoms remain in the source/query binding. |

The contradiction route takes precedence over the shape of the retained body.
The empty tree is part of this route's canonical input; a nonempty supplied
tree is rejected instead of being silently ignored. For the other routes,
invalid or unverified trees cannot produce a `PhysicalPlan`.

For a tree route, the checked tree reports `height_status: valid_upper_bound`.
Its native height and ordinary edge depth are structural measurements, not a
minimum-height proof. Cost policy, candidate choice and optimality evidence
remain separate planner responsibilities.
For a contradiction, zero height describes the constant operator; it does not
certify a CROWN tree for the retained body. The artifact's verification kind
is `constant_operator` for that route.

Native replanning and C02/C05 selection retain the original typed P07 candidate
and body proof separately from the executable operator. Only a nonempty
contradiction substitutes operator geometry; existing empty-body raw claims
and ordinary trees are preserved. A constant-false P08 artifact alone does
not supply a P07 minimum-height family. Ranking and selection still require
their normal typed family admission.

## Compiled input adapters

The direct CQ path compiles occurrence adapters from numeric catalog positions.
`PhysicalInput` records the occurrence and node, physical and logical table
IDs, physical tuple layout, projection, repeated-column equalities, and typed
constant guards. `PhysicalPlan::adapt_input` applies this compiled program to
a source row. Field names are resolved before this path; row processing does
not perform string-name lookup.

The normalized SQL path owns and reuses the typed F04 adapters in the replayed
`NormalizedSql`. Those adapters include the resolved per-occurrence
expression program, local predicates, non-null checks, equal-column guards,
constant-column guards and core projection. SQL AST interpretation is not part
of the physical node or storage kernel. The distinction between physical base
tables and logical normalized occurrence inputs remains explicit so one base
table can route to multiple occurrences without merging their state.

## Node state and relation layouts

Each `PhysicalNode` preserves its tree node ID, kind, occurrence, parent,
tree-ordered children, complete scope, visible scope, and `C*` membership. Its
layouts and projections are compiled once. `PhysicalRelation` roles identify
physical-base, native-record, generalized-candidate, survivor, parent-support
and visible relations. The role and optional node/base owner make relation
identity local to the physical plan rather than inferred from equal scopes.

For node `v`, let `B_v` be its scope and `K_v` its parent separator. The
parent-support projection is `π_Kv(S_v)`. A native node retains its complete
normalized occurrence tuple and is a survivor only when every child has
support for the child's separator key. A generalized node has no external
tuple input: its candidates come from child support keys at the generalized
scope, and a key survives when every child supports it. These are the logical
state descriptors; this API does not yet maintain them across updates.

For a node in the maximal root-connected connex subtree, the local visible
projection is `F ∩ B_v`, where `F` is the set of distinct core-head variables.
That projection has its own relation ID; its future support counters must
remain separate from parent support. Compatible ordered fields can share a layout token while their
relation IDs and state remain distinct. In particular, the native root's
scope need not be contained in the head: `Q(x):R(x,z)` still has a visible
projection containing only `x`.

Connex membership is computed from the tree and head. Starting at the root,
`C*` traverses an edge exactly when the separator is contained in `F`. A node
can have a nonempty `visible_scope` and still lie outside `C*`, because a hidden
variable in an earlier separator blocks the path. Such a node contributes
support, but it has no enumeration step or visible enumeration relation.
Visibility of a variable by itself never implies enumeration reachability.

An `IndexRequirement` associates a relation with a compiled projection and its
uses. Uses distinguish reverse child-support lookup from visible enumeration.
`PhysicalEdge` stores the parent/child IDs, original child slot, compiled
separator projection and optional reverse index. Child slots preserve tree
order and allow arbitrary fan-out. Separator keys can be composite,
reordered or nullary; projections use numeric fields and explicit typed target
layouts. On each edge, the child's support projection and the parent's reverse
lookup projection share the same separator target-layout token. This keeps key
identity exact when the two relations have different source layouts. The root
separator uses a plan-local nullary layout.

## Enumeration and result assembly

The `EnumerationProgram` contains only nodes in `C*`, in parent-before-child
order. Each step identifies its node and visible relation, depth, parent step,
separator projection and optional bucket index. Children remain in the
supplied tree's order; the program describes an N-ary traversal rather than a
binary rewrite or a materialized full join.

The program records where each core output position is read and which slots
from different assignments must agree on a shared variable. Runtime assembly
checks those cross-assignment equalities before constructing a result. Output
positions follow the core head's original order, including repeated variables;
`assemble_result` uses the compiled slots and does not look up names. Boolean
enumeration uses a nullary visible projection, which has either zero or one
tuple in the maintained runtime. The [current-result cursor](result_cursors.md)
executes this program lazily over the live E indexes.

The result layout and assembly program describe the core head. The retained
normalized program's ordered/constant SQL output mapping and EXISTS wrapper
remain a separate F04 step, available through `frontend::map_sql_result`.
An EXISTS wrapper therefore still produces its false scalar row when the core
route is constant false.

This is an execution program description, not an implemented cursor. No
maintained survivor state, snapshot cursor, pinned-witness cursor, delta cursor
or query update/epoch API is provided by P08.

## Reference storage boundary

`storage::ReferencePlanStorage` can be constructed only from an immutable
`PhysicalPlan`. It instantiates empty `ReferenceTable`s using the plan's
relation layouts and registers the compiled index requirements. It exposes
internal table and index access plus storage invariant checks. It does not
load a database, build query survivors, maintain generalized intersections,
apply updates, create epochs, or enumerate answers. A populated reference
storage object is therefore not a maintained query engine.

The separate [reference support runtime](runtime_support.md) consumes these
descriptors and maintains logical native/generalized S/P/E state. It adds
per-logical-update journal rollback, pinned affected values and causal event
accounting. The [physical coordinator](physical_runtime.md) supplies atomic
source/alias updates, and [current-result cursors](result_cursors.md) enumerate
committed answers. Fragment/delta/output delivery remains separate work.

The current profile uses the ordered standard-container backend and declares
single-writer, non-null exact binary-value and container-order assumptions.
These are backend assumptions, not a concurrency or delay guarantee. The
profile's output accounting records one action per emitted tuple and accounts
for retained snapshots and buffers separately; output accounting does not
certify a runtime cursor performance bound.

## Identity and versioned artifacts

`PhysicalPlan::identity()` carries F05's separate semantic, output-contract,
cost-input and plan-cache identities. The semantic identity describes the
query independently of local node/layout numbering; the output identity
retains the output contract, and the cache identity includes the declared
arithmetic, planner, optimization and cost-model policy. The identity also
retains canonical-to-local occurrence and variable order maps so a cache
consumer can translate IDs.

`physical_sha256()` hashes a versioned domain envelope containing the exact
owned source artifact's SHA-256, the F05 cache digest, canonical-to-local ID
maps, supplied tree and lowerer version. Numeric instructions are derived
deterministically from these inputs. This also distinguishes different typed
adapter programs with equal semantic identities. Indexed identity v2 additionally
commits the complete `PhysicalOptions`. Legacy identity v1 omits lowering-work
and identity-work limits even though the wire artifact serializes them. Therefore
this SHA is a plan identity, not the digest of every compiler-artifact byte.
Database rows/events and live index contents are excluded; IDs remain local to
the physical artifact. A matching digest alone never authorizes importing
compiled fields.

The v1 physical artifact is deterministic and replayable. The reader
reconstructs the normalized program and every compiled physical descriptor
from the owned source/query/tree, then compares the rebuilt artifact. It does
not trust imported validity, height, guarantee, projection-slot or other
compiled fields. Producer work limits are not host authorization: host
`PhysicalReadLimits` and program read limits independently cap replay, and a
stored unlimited limit cannot raise a finite host cap. Defaults are finite; a
caller can explicitly change or remove optional work limits. Direct
`read_physical` has no document-byte cap in `PhysicalReadLimits`. The higher-level
`CompilerPlanArtifact::replay` defaults to a64MiB byte check before JSON parsing;
its `prepare` path checks serialized size after producing the compiler DTO. These
are compiler-workspace boundaries, not total allocation, RSS or wall-time bounds.
The [independent compiler-descriptor argument](../build/verification/v02-compiler-descriptor-review-v1/report.md)
records replay, full-artifact comparison and selected-root receiving separately.

The wire contracts are [physical plan v1](../schemas/physical-plan-v1.schema.json)
and [physical plan options v1](../schemas/physical-plan-options-v1.schema.json).
The options contract carries lowering-work and identity-work limits plus the
cache policy; consult the schema for exact JSON fields and defaults.

## Commands

The command forms are:

```text
crown lower-plan QUERY TREE [OPTIONS]
crown lower-normalized PROGRAM TREE [OPTIONS]
crown validate-physical ARTIFACT
crown canonicalize-physical ARTIFACT
```

Successful lowering returns the complete artifact on stdout with exit 0.
Invalid trees and resource stops return a diagnostic with
`physical_lowered:false` and exit 1, with no partial program. Malformed
configuration/artifacts and replay mismatches use stderr and exit 2; internal
invariant failures use exit 3. Replay success returns `physical_valid:true` or
the canonical artifact. These commands do not install a query runtime.

Options use a version-1 document with required `policy` fields `arithmetic`,
`planner`, `optimization`, and `cost_model`, and required `limits.work` and
`limits.identity_work`. Defaults are one million abstract operations each;
JSON null means unlimited producer work. Host caps remain independent.
Lowering counters cover preflight and compiled-program construction;
independent tree checking, source replay, identity work and JSON/hash processing
are separate costs. No wall-time or memory quota follows from these counters.

## Guarantee profile and verification status

The API's default `GuaranteeProfile` deliberately marks this stage as
`lowered_not_started` and every runtime state, maintenance, cursor-startup,
cursor-delay and cursor-termination bound as `runtime_not_implemented`.
`height_status` is `valid_upper_bound`; it does not say `proven_minimum`.
Its current profile fields are:

| Field | Current value | Meaning |
| --- | --- | --- |
| `semantics` | `exact_set` | The lowered core uses exact set semantics. |
| `query_class` | `free_connex` or `constant_result` | Checked tree route or explicit constant operator. |
| `update_contract` | `physical_full_row_set_events` | The full-row input shape accepted by the physical runtime; the artifact itself holds no mutable session. |
| `arithmetic` | `exact-nonnull-v1` | The declared exact, non-null value policy. |
| `storage_backend` | `reference_ordered_v1` | The instantiated empty standard ordered-container backend. |
| `execution_status` | `lowered_not_started` | This immutable compilation artifact is not a live session status. |
| `height_status` | `valid_upper_bound` | Tree routes retain checked upper bounds; constants describe a zero-height operator, without a body-tree claim. |
| `state_bound`, `maintenance_bound` | `runtime_not_implemented` | This format certifies no runtime state/update complexity bound. |
| `cursor_startup_bound`, `cursor_delay_bound`, `cursor_termination_bound` | `runtime_not_implemented` | No cursor performance bound is available. |
| `assumptions` | `single_writer`, `nonnull_exact_binary_values`, `ordered_standard_containers` | Declared backend assumptions. |
| `operation_modes` | `compile_only`, `reference_storage_initialization` | Operations on the compilation/storage artifact. |
| `output_accounting` | `one_action_per_emitted_tuple`, `retained_snapshots_and_buffers_accounted_separately` | Output accounting policy, separate from cursor complexity guarantees. |

These values describe the capability boundary. They do not certify an
installed executor, update behavior or constant-delay enumeration.

P08 acceptance is verified. Native/generalized roots, arbitrary fan-out,
composite/reordered/empty keys, hidden branches, Boolean/nullary output,
constant routing, replay/host limits and invalid-tree rejection are covered.
The independent fixture inputs are listed in the
[physical lowering manifest](../tests/structural/lowering/manifest.json).
The complete matrix, finite coverage and reproduction record are in
[physical-lowering verification](verification/physical-lowering-2026-11-05.md).

## Explicit indexed backend successor

An explicit `PhysicalOptions::indexed_storage` selects the native indexed route through `PlanStorage`, Support/Physical/Delta/Session and owner capture. It emits strict version2 options/artifacts and binds all nine component limits and five native-work limits before layout construction. The semantic query identity stays unchanged. Absent configuration preserves reference version1 serialization and binding. `ReferencePlanStorage` rejects an indexed plan. See the [indexed contract](indexed_storage.md) and [S04 gate status](verification/indexed-runtime-2026-11-08.md); the earlier P08 record remains historical.
