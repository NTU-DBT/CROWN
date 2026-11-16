# Decision 0010: validated physical plans and an explicit runtime boundary

Status: P08 verified, 2026-11-05. Maintained runtime and release gates remain open.

Lowering accepts the actual catalog, query and supplied tree, then constructs
an immutable `PhysicalPlan` through private factory access. The public
`lower_tree` and `lower_normalized` entry points revalidate their inputs; a
caller-supplied `valid` bit or validation report cannot authorize a plan.
Validating a supplied tree establishes a structural upper bound, not a
minimum-height result. Minimum selection and proof remain in planner and
height-evidence stages.

The constant routes are explicit. An empty-body true query uses an empty tree
and has no physical tree nodes. A contradiction uses the canonical empty tree
even when its retained body is nonempty or cyclic; its atoms stay in the source
binding, while the physical route is constant false. A supplied nonempty tree
for that route is rejected instead of being silently discarded.

The physical descriptor separates complete node scope, parent-separator
support and visible projection. Parent-support and visible relations have
distinct IDs; future counters must remain separate. Compatible ordered layouts
may share a token. The visible projection is
`F ∩ B_v`; enumeration includes only the maximal root-connected `C*` subtree,
whose edges have separators contained in the distinct core head. A node can
contain a visible variable and remain outside `C*`; it contributes support,
not an enumeration step. Compiled child slots preserve input tree order and
support arbitrary fan-out, composite keys and empty keys.

Direct CQ inputs use compiled numeric equality, constant and projection
programs. Normalized SQL lowering replays the full F04 program, grounds legacy
v1 to v2, and retains its typed adapters. The physical kernel has no source
SQL AST or string field-name lookup. Output assembly maps numeric assignment
slots to the core head's original order, preserves repeated output variables,
and checks equality where assignments overlap.

`ReferencePlanStorage` is an internal empty-storage construction from a
validated plan. It creates ordered reference relations and indexes, but does
not load rows or maintain joins, updates, epochs or cursors. The guarantee
profile therefore reports `lowered_not_started` and runtime bounds as
`runtime_not_implemented`; no execution or delay claim follows from plan
construction.

F05's semantic, output-contract, cost-input and cache identities remain
separate. The exact physical binding includes local IDs, the supplied tree and
policy, but excludes database contents and live runtime state. The v1
reader rebuilds descriptors from owned source/query/tree input and compares
the complete artifact under host work caps; imported validity, optimality or
compiled-slot claims are not trusted. Exact wire fields are defined by the
[physical-plan](../../schemas/physical-plan-v1.schema.json) and
[physical options](../../schemas/physical-plan-options-v1.schema.json) schemas.

See the [P08 contract](../physical_plans.md), the
[structural fixtures](../../tests/structural/lowering/manifest.json), and the
[verification packet](../verification/physical-lowering-2026-11-05.md).
All 29 tests pass GCC Debug/Release/sanitizers, Clang and a fresh source build.
The conditional enumeration argument assumes later exact S/E maintenance;
G2/V02 external mathematical review remains open. Constant-route zero height
describes its operator, without certifying a tree for a retained cyclic body.
