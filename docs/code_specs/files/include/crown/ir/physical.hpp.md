# `include/crown/ir/physical.hpp` — block usage map

[Source](../../../../../../include/crown/ir/physical.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `bca14b04987f9658a0c779319135ca508fc039e52624992fdc6c37b689bcaa8c`. 159 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../../include/crown/ir/physical.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../../include/crown/ir/physical.hpp#L15) | Type/record definition: enum class PhysicalRoute |  · [reviewed contract](#b0002) |
| [B0003 · 16–16](../../../../../../include/crown/ir/physical.hpp#L16) | Type/record definition: enum class RelationRole |  · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../../include/crown/ir/physical.hpp#L17) | Type/record definition: enum class IndexUse |  · [reviewed contract](#b0004) |
| [B0005 · 18–24](../../../../../../include/crown/ir/physical.hpp#L18) | Type/record definition: struct PhysicalRelation |  · [reviewed contract](#b0005) |
| [B0006 · 25–30](../../../../../../include/crown/ir/physical.hpp#L25) | Type/record definition: struct IndexRequirement |  · [reviewed contract](#b0006) |
| [B0007 · 31–31](../../../../../../include/crown/ir/physical.hpp#L31) | Type/record definition: struct InputEquality |  · [reviewed contract](#b0007) |
| [B0008 · 32–32](../../../../../../include/crown/ir/physical.hpp#L32) | Type/record definition: struct InputConstant |  · [reviewed contract](#b0008) |
| [B0009 · 33–42](../../../../../../include/crown/ir/physical.hpp#L33) | Type/record definition: struct PhysicalInput | source comment (unverified): // Original physical catalog, including SQL aliases. · [reviewed contract](#b0009) |
| [B0010 · 43–59](../../../../../../include/crown/ir/physical.hpp#L43) | Type/record definition: struct PhysicalNode | source comment (unverified): // Native records or generalized candidate union. · [reviewed contract](#b0010) |
| [B0011 · 60–66](../../../../../../include/crown/ir/physical.hpp#L60) | Type/record definition: struct PhysicalEdge |  · [reviewed contract](#b0011) |
| [B0012 · 67–67](../../../../../../include/crown/ir/physical.hpp#L67) | Type/record definition: struct AssignmentSlot |  · [reviewed contract](#b0012) |
| [B0013 · 68–68](../../../../../../include/crown/ir/physical.hpp#L68) | Type/record definition: struct AssignmentEquality |  · [reviewed contract](#b0013) |
| [B0014 · 69–76](../../../../../../include/crown/ir/physical.hpp#L69) | Type/record definition: struct EnumerationStep |  · [reviewed contract](#b0014) |
| [B0015 · 77–82](../../../../../../include/crown/ir/physical.hpp#L77) | Type/record definition: struct EnumerationProgram | source comment (unverified): // Parent-before-child order over C* only. · [reviewed contract](#b0015) |
| [B0016 · 83–84](../../../../../../include/crown/ir/physical.hpp#L83) | Explanatory comments or spacing. | source comment (unverified): // Work and identity limits count selected checkpoints; neither caps elapsed time · [reviewed contract](#b0016) |
| [B0017 · 85–88](../../../../../../include/crown/ir/physical.hpp#L85) | Type/record definition: struct PhysicalLimits | source comment (unverified): // Work and identity limits count selected checkpoints; neither caps elapsed time · [reviewed contract](#b0017) |
| [B0018 · 89–94](../../../../../../include/crown/ir/physical.hpp#L89) | Type/record definition: struct PhysicalOptions | source comment (unverified): // Absent preserves the exact reference v1 format and binding. · [reviewed contract](#b0018) |
| [B0019 · 95–113](../../../../../../include/crown/ir/physical.hpp#L95) | Type/record definition: struct GuaranteeProfile | source comment (unverified): // These are compile-time capabilities. No maintained runtime or cursor · [reviewed contract](#b0019) |
| [B0020 · 114–149](../../../../../../include/crown/ir/physical.hpp#L114) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Explicit caller-owned export of an immutable native program. Ordinary · [reviewed contract](#b0020) |
| [B0021 · 150–159](../../../../../../include/crown/ir/physical.hpp#L150) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Execute only compiled input/assembly programs, not join maintenance. · [reviewed contract](#b0021) |

## B0001

[Lines 1–14](../../../../../../include/crown/ir/physical.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CompiledProgram;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward-declare the immutable compiled-program class used by the physical-plan export API. |
| inputs / outputs | The incomplete type is accepted by reference in \`PhysicalPlan::from_compiled\`; its full public operations are defined in the program header. |
| invariants | The forward declaration creates no plan/program instance and says nothing about execution, ownership, or validation. |
| ownership | No storage is introduced. The referenced \`CompiledProgram\` remains owned by its separate shared control block. |
| failure | No runtime behavior is attached to the declaration; \`from_compiled\` checks access through its implementation. |
| cost | No runtime cost for the declaration; explicit \`from_compiled\` performs a caller-owned ordinary DTO export and copies selected metadata. |
| Design | [include/crown/ir/physical.hpp §forward declaration and from_compiled](../../../../../../include/crown/ir/physical.hpp), [include/crown/ir/program.hpp §CompiledProgram](../../../../../../include/crown/ir/program.hpp), [src/planner/lower.cpp §PhysicalPlan::from_compiled](../../../../../../src/planner/lower.cpp) |

## B0002

[Lines 15–15](../../../../../../include/crown/ir/physical.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class PhysicalRoute {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Labels the lowered operator route for tree evaluation or constant true/false results. |
| inputs / outputs | Selects which physical plan descriptor set is meaningful after lowering. |
| invariants | The enum by itself does not establish that the route matches the query or that runtime execution exists; lowering chooses it after admission. |
| ownership | Value-sized tag stored in PhysicalPlan data. |
| failure | No intrinsic failure; route/query consistency is a lowerer invariant. |
| cost | Constant-size value. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [include/crown/planner/lower.hpp](../../../../../../include/crown/planner/lower.hpp) |

## B0003

[Lines 16–16](../../../../../../include/crown/ir/physical.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class RelationRole {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Names the intended role of a physical relation descriptor. |
| inputs / outputs | Distinguishes physical base, native record, generalized candidate, survivor, parent support, and visible relations. |
| invariants | The tag does not create or populate a relation; relation IDs remain plan-local and role/layout/node/base binding is produced by lowering. |
| ownership | Value-sized enum in a descriptor. |
| failure | No intrinsic failure; invalid combinations are possible in a stand-alone aggregate and are not self-checked. |
| cost | Constant-size value. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp) |

## B0004

[Lines 17–17](../../../../../../include/crown/ir/physical.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class IndexUse {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Names why a compiled projection is indexed. |
| inputs / outputs | Distinguishes reverse child-support lookups from visible enumeration buckets. |
| invariants | This is usage metadata only; it does not register or build a runtime index. |
| ownership | Value-sized enum in an IndexRequirement. |
| failure | No intrinsic failure; lowerer/backend consumers interpret valid requirements. |
| cost | Constant-size value. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp) |

## B0005

[Lines 18–24](../../../../../../include/crown/ir/physical.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalRelation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describes one plan-local relation ID, role, layout, and optional node/base owner. |
| inputs / outputs | Carries RelationId, RelationRole, a TupleLayout, and optional NodeId/TableId bindings. |
| invariants | The aggregate does not enforce ID range, role/owner compatibility, or storage population. TupleLayout token identity matters beyond LayoutId equality. |
| ownership | Owns only scalar descriptor fields and optional values; TupleLayout is a shared immutable descriptor handle and may keep account-backed layout metadata alive. |
| failure | Arbitrary field combinations are storable; validated lowering supplies consistent bindings and storage checks the actual layout token. |
| cost | Fixed descriptor copy plus shared-handle refcount; no rows. Lowering creates relation entries proportional to number of relations. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp) |

## B0006

[Lines 25–30](../../../../../../include/crown/ir/physical.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexRequirement {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describes a plan-local index ID, owning relation, projection, and intended lookup uses. |
| inputs / outputs | Provides an ordered projection and zero or more IndexUse tags to a storage backend. |
| invariants | Does not itself create an index or check requirement/relation IDs. The Projection source token must match the relation and its target token binds keys. |
| ownership | Owns the uses vector; Projection is a shared immutable handle and may retain account-backed source/target layout metadata. |
| failure | No validation at aggregate construction; lowerer checks shared key tokens and backend registration can reject mismatched bindings. |
| cost | Copy cost is O(number of uses) plus shared descriptor refcount; storage index construction has separate row/key costs. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp) |

## B0007

[Lines 31–31](../../../../../../include/crown/ir/physical.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputEquality {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describes one repeated-column equality guard for a source occurrence row. |
| inputs / outputs | Names two FieldId slots that PhysicalPlan::adapt_input compares before projection. |
| invariants | The indices are meaningful only in the source tuple layout; the aggregate does not prove bounds or equality. |
| ownership | Two scalar field IDs; no row ownership. |
| failure | Invalid slots are representable; the compiled lowerer derives these from admitted atom terms and adapt_input validates the source row layout before indexed checks. |
| cost | Constant-size value; each guard costs one scalar equality when adapt_input runs. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp) |

## B0008

[Lines 32–32](../../../../../../include/crown/ir/physical.hpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputConstant {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describes one fixed-value guard for a source occurrence row. |
| inputs / outputs | Names a field and expected Value; adapt_input rejects rows whose field differs before projecting. |
| invariants | The field must belong to the physical source layout and the Value must be compatible with that field; aggregate construction checks neither. |
| ownership | Owns a Value variant; a string value may own bytes. |
| failure | Invalid field/value combinations are representable; valid plans derive them from validated query terms and row/layout admission. |
| cost | Value storage/copy is constant for scalar alternatives and proportional to string bytes; guard execution is one field comparison. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp) |

## B0009

[Lines 33–42](../../../../../../include/crown/ir/physical.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalInput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describes the physical-to-logical adapter for one atom occurrence. |
| inputs / outputs | Carries occurrence/node/base/logical table IDs, physical layout, projection, repeated-field equalities, and constants. |
| invariants | Physical base may be an original SQL catalog alias while logical_table is the normalized core table. Row adaptation filters equalities/constants before the projection; no names are resolved in this kernel. |
| ownership | Owns equality/constant vectors and descriptor handles; TupleLayout/Projection copies share immutable metadata when native-backed and can retain its account blocks. |
| failure | The aggregate does not validate port/table/layout coherence. adapt_input rejects a missing occurrence or invalid row/layout, and returns empty for normalized-adapter, equality, or constant-filter mismatch. |
| cost | Descriptor copies are fixed/shared; guard/vector storage is proportional to guard counts and Value bytes. adapt_input validates/scans row fields and guards, then copies projected values; normalized input also runs its typed adapter. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/frontend/admission.cpp](../../../../../../src/frontend/admission.cpp), [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp) |

## B0010

[Lines 43–59](../../../../../../include/crown/ir/physical.hpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalNode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describes one lowered node, its full/visible scopes, key projections, and relation bindings. |
| inputs / outputs | Carries node kind/occurrence/topology, ordered child list, scope vectors, connex membership, layout/projections, and records/survivor/support/visible relation IDs. |
| invariants | It is a compile-time state descriptor, not maintained S/P/E storage. visible_scope and visible_relation reflect head projection and maximal root-connected C* membership; full native scope is retained. |
| ownership | Owns children/scope/visible_scope vectors and optionals; layout/projection handles share metadata rather than copy field arrays when native-backed. |
| failure | No self-validation of IDs, kind/occurrence, scope, projections or relation roles; the lowerer derives them from a checked tree. |
| cost | Storage/copy proportional to child and scope vectors plus fixed shared descriptor handles; no relation rows or joins are built. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [docs/tree_plans.md](../../../../../tree_plans.md), [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp) |

## B0011

[Lines 60–66](../../../../../../include/crown/ir/physical.hpp#L60); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalEdge {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describes one parent-child connection and the parent's separator projection. |
| inputs / outputs | Stores parent/child IDs, original child slot, parent-key projection, and optional reverse index requirement. |
| invariants | child_slot preserves supplied tree order and arbitrary fan-out. A reverse lookup is optional where the route does not need a native-parent index; this is not an allocated index. |
| ownership | Small value fields plus a Projection descriptor handle that may share account-backed metadata. |
| failure | The aggregate does not check endpoint references or projection compatibility; lowering computes separators and target-token bindings from the checked tree. |
| cost | Fixed fields and shared descriptor copy; work/storage per edge is created by lowering. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp) |

## B0012

[Lines 67–67](../../../../../../include/crown/ir/physical.hpp#L67); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AssignmentSlot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Addresses one field in one enumeration assignment step. |
| inputs / outputs | Combines a step index with a FieldId used to read a result variable. |
| invariants | The pair is valid only relative to EnumerationProgram.steps and that step relation layout; it carries no bounds proof. |
| ownership | Two scalar values with no tuple/plan ownership. |
| failure | Any pair is representable; the lowerer generates slots and assembly validates assignment count/layout, but does not validate arbitrary standalone slot instructions. |
| cost | Constant-size value; lookup is constant time for a valid compiled program. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp) |

## B0013

[Lines 68–68](../../../../../../include/crown/ir/physical.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AssignmentEquality {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describes a required equality between fields from two assignment steps. |
| inputs / outputs | Stores left and right AssignmentSlot references checked by result assembly. |
| invariants | The instruction describes cross-assignment agreement for shared variables; it does not enforce equality until assemble_result executes it. |
| ownership | Two small slot values; no assignment or tuple ownership. |
| failure | Invalid steps/fields are representable in isolation. Lowering emits valid instructions; assembly throws invalid_assignment when the selected values disagree. |
| cost | Constant-size value; one compiled equality check per instruction. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp) |

## B0014

[Lines 69–76](../../../../../../include/crown/ir/physical.hpp#L69); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EnumerationStep {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describes one parent-before-child visible relation read in the enumeration program. |
| inputs / outputs | Carries node/relation IDs, depth, optional parent-step and separator projection, and optional bucket index. |
| invariants | Steps cover C* only in tree order; this is a traversal description, not a running cursor or guarantee of minimum-height choice. |
| ownership | Optional Projection is a shared immutable descriptor handle; the step owns only scalar instruction values. |
| failure | Aggregate construction checks no sequence or token rules; lowering produces a valid sequence and backend/cursor code must bind the descriptors. |
| cost | Fixed-size fields and shared descriptor copy; execution work is separate and depends on relation/index contents. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp) |

## B0015

[Lines 77–82](../../../../../../include/crown/ir/physical.hpp#L77); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EnumerationProgram {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collects traversal steps and output/equality slot instructions for the core query head. |
| inputs / outputs | Owns parent-before-child steps over C*, ordered/repeated output slots, cross-step equality checks, and maximum depth. |
| invariants | It describes how later runtime assembly maps assignments to answers; no join state or runtime cursor is created, and the program does not establish minimum tree height. |
| ownership | Owns three vectors of instruction values; nested optional projections share descriptor metadata. |
| failure | No instruction validation occurs on aggregate construction; validated lowering emits the program from the independently checked tree. |
| cost | Storage is O(steps + output slots + equalities), excluding shared descriptor metadata; execution/output cost is separate and data-dependent. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0016

[Lines 83–84](../../../../../../include/crown/ir/physical.hpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L84:sha256:ff721caffa8a0a10d7e9fd8f69c26e3723f1b3f57984e832461343c63713ecf0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Work and identity limits count selected checkpoints; neither caps elapsed time or allocator bytes, and tree validation/serialization have separate costs. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/ir/physical.hpp lines 81-86; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/code_specs/files/include/crown/ir/physical.hpp.md](physical.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0017

[Lines 85–88](../../../../../../include/crown/ir/physical.hpp#L85); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separates the lowering work ceiling from query-identity work ceiling. |
| inputs / outputs | Provides an optional selected-checkpoint work limit and a nested IdentityLimits ceiling; defaults are one million each. |
| invariants | These limits count explicit checkpoints in separate operations. They do not bound elapsed time, allocator bytes, validation, identity, JSON/hash, or all work inside a checkpoint. |
| ownership | Two optional uint64 values; no resource owner. |
| failure | A finite work stop throws resource_limit before publishing a partial plan; identity exhaustion is separately reported by identity generation. Null means no producer cap, while host caps can reduce it. |
| cost | Constant-size fields; enforcement increments counters at selected checkpoints, not every operation. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp) |

## B0018

[Lines 89–94](../../../../../../include/crown/ir/physical.hpp#L89); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Selects cache identity policy, lowering/identity limits, and optional storage backend. |
| inputs / outputs | Carries CachePolicy, PhysicalLimits, and optional IndexedBackendSpec; absent indexed_storage preserves reference v1 output/binding. |
| invariants | This is configuration only: it does not instantiate storage. Policy strings participate in identity; backend choice affects lowering/output format. |
| ownership | Owns policy strings and optional scalar backend configuration by value. |
| failure | Aggregate construction accepts arbitrary policy strings/limits; option/artifact readers and lowering validate supported formats/configuration at their boundary. |
| cost | Copy cost proportional to policy text; backend spec and limits are fixed-size values. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [include/crown/io/identity.hpp](../../../../../../include/crown/io/identity.hpp), [include/crown/storage/backend.hpp](../../../../../../include/crown/storage/backend.hpp), [src/io/physical.cpp](../../../../../../src/io/physical.cpp) |

## B0019

[Lines 95–113](../../../../../../include/crown/ir/physical.hpp#L95); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GuaranteeProfile {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reports the declared semantics, backend assumptions, operation modes, and implementation status of a physical artifact. |
| inputs / outputs | Defaults to exact set semantics, valid upper-bound tree status, compile/reference initialization modes, and runtime_not_implemented bounds; lowering adjusts route/backend labels. |
| invariants | Public mutable strings/vectors are descriptors, not proofs or enforced guarantees. Constructing a profile or PhysicalPlan does not install maintenance/cursors or certify runtime bounds; tree validation is an upper-bound check only. |
| ownership | Owns dynamic strings and vectors as ordinary values; profile does not own runtime state. |
| failure | Any strings/status combinations can be built directly; validated PhysicalPlan production derives a profile and serialization/replay compares rebuilt descriptors. |
| cost | Storage/copy proportional to string lengths and vector entries; no query execution or measurement. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/io/physical.cpp](../../../../../../src/io/physical.cpp) |

## B0020

[Lines 114–149](../../../../../../include/crown/ir/physical.hpp#L114); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class PhysicalPlan {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Holds an immutable lowered plan and exposes compiled descriptors, input adaptation, and result assembly. |
| inputs / outputs | Factory from_compiled exports a caller-owned DTO; accessors return const references/views to route, source/query/tree, validation/identity, descriptors, options/profile, work, and result layout. adapt_input filters/projects a row; assemble_result checks assignments and emits an ordered/repeated core-head tuple. |
| invariants | Validated lowering checks tree routes with validate_tree; constant routes use canonical empty trees and route-specific checks. from_compiled exports an already factory-produced CompiledProgram and copies its existing validation/profile without rerunning P02 or proving a new minimum. Tree routes retain checked upper evidence; constant routes record checked constant operators rather than CROWN-tree minimum proofs for their retained body. This class is not a maintained runtime/storage engine. |
| ownership | The handle is shared_ptr&lt;const Data&gt;; copy construction shares immutable Data. Ordinary exported strings/vectors/model fields are copied, but TupleLayout/Projection descriptors use AccountedLayout/AccountedProjection::descriptor and share their existing Data/control blocks, account, metadata, and projection source/target tokens. This can retain those metadata blocks after CompiledProgram destruction without retaining the whole native program graph or tuple/row arena. |
| failure | Moved-from access reports invalid_physical_plan; missing input port, malformed row/layout or incompatible assignments throw, nonmatching input guards return empty, and constant_false assembly throws empty_plan. The class has no public mutable Data constructor. |
| cost | Plan copy/move construction takes fixed handle work; copy/move assignment can additionally destroy the old destination Data and all final-owned payload in proportion to its size. from_compiled recursively copies ordinary payload proportional to strings/vectors/JSON, while descriptor handles add refcount operations without another native metadata control block. adapt_input pays typed row/adapter validation, guard scalar comparisons, projection and copied payload costs. assemble_result checks assignment tokens and equality instructions, pays the bytes examined by scalar comparisons, copies output scalars and validates/constructs the result tuple. Native-backed descriptors can allocate the output payload/control block under their retained account. Lowering work counters do not meter these calls or cap allocator bytes. |
| Design | [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [include/crown/planner/lower.hpp](../../../../../../include/crown/planner/lower.hpp), [src/planner/compiled_source.cpp](../../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../../src/planner/compiled_source.hpp), [include/crown/storage/layout.hpp](../../../../../../include/crown/storage/layout.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_layout.cpp](../../../../../../src/storage/accounted_layout.cpp), [src/storage/accounted_projection.cpp](../../../../../../src/storage/accounted_projection.cpp) |

```text
PhysicalPlan(const PhysicalPlan&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy an immutable physical-plan handle. |
| inputs / outputs | Retain the source shared Data owner without copying plan payload. |
| invariants | No revalidation, new minimum-height proof or runtime execution follows from a handle operation. |
| ownership | Source and destination share const Data; self-copy is allowed. |
| failure | Declared noexcept; moved-from content access is checked by the existing invalid_physical_plan boundary. |
| cost | Fixed shared-pointer/refcount work; no new payload allocation. |
| Design | [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../../src/planner/compiled_source.cpp) |

```text
PhysicalPlan(PhysicalPlan&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move an immutable physical-plan handle. |
| inputs / outputs | Transfer the source shared Data owner without copying plan payload. |
| invariants | No revalidation, new minimum-height proof or runtime execution follows from a handle operation. |
| ownership | The source shared_ptr is moved; self-move follows shared_ptr semantics. |
| failure | Declared noexcept; moved-from content access is checked by the existing invalid_physical_plan boundary. |
| cost | Fixed shared-pointer/refcount work; no new payload allocation. |
| Design | [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../../src/planner/compiled_source.cpp) |

```text
PhysicalPlan& operator=(const PhysicalPlan&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy an immutable physical-plan handle into an existing destination. |
| inputs / outputs | Retain the source shared Data owner and release the previous destination owner. |
| invariants | No revalidation, new minimum-height proof or runtime execution follows from a handle operation. |
| ownership | Source and destination share const Data; self-copy is allowed. Replacing the final old owner can synchronously release its model, descriptors and other payload. |
| failure | Declared noexcept; moved-from content access is checked by the existing invalid_physical_plan boundary. |
| cost | Fixed handle work plus potentially size-dependent last-owner destination teardown; no new payload allocation. |
| Design | [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../../src/planner/compiled_source.cpp) |

```text
PhysicalPlan& operator=(PhysicalPlan&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move an immutable physical-plan handle into an existing destination. |
| inputs / outputs | Transfer the source shared Data owner and release the previous destination owner. |
| invariants | No revalidation, new minimum-height proof or runtime execution follows from a handle operation. |
| ownership | The source shared_ptr is moved; self-move follows shared_ptr semantics. Replacing the final old owner can synchronously release its model, descriptors and other payload. |
| failure | Declared noexcept; moved-from content access is checked by the existing invalid_physical_plan boundary. |
| cost | Fixed handle work plus potentially size-dependent last-owner destination teardown; no new payload allocation. |
| Design | [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../../src/planner/compiled_source.cpp) |

## B0021

[Lines 150–159](../../../../../../include/crown/ir/physical.hpp#L150); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::optional<storage::Tuple> adapt_input(OccurrenceId occurrence, const Row& row) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute the compiled input adapter and output assignment program exposed by the plan. |
| inputs / outputs | adapt_input maps a physical port row to an optional logical tuple; assemble_result maps ordered step assignments to the ordered/repeated core head. |
| invariants | These programs do not maintain joins or enumerate results. Shared-variable equalities and normalized repeated-column/constant guards must hold. |
| ownership | Methods borrow immutable plan data and supplied rows/assignments; returned tuples own copied projected/output values. |
| failure | Invalid port/row/layout or inconsistent assignments throw; nonmatching input guards return empty. constant_false assembly throws empty_plan. |
| cost | Input adaptation performs typed row/adapter validation, guard comparisons and projection, including bytes examined/copied. Result assembly performs assignment-token checks, scalar equality comparisons, output copies and result-layout validation/construction; equal strings can require scanning their full byte lengths even when only one equality is present. Account-backed descriptors can allocate output payload/control blocks under their retained account. These caller-facing operations are outside lowering-work counters. |
| Design | [docs/physical_plans.md](../../../../../physical_plans.md), [src/planner/lower.cpp](../../../../../../src/planner/lower.cpp), [src/planner/compiled_source.cpp](../../../../../../src/planner/compiled_source.cpp) |
