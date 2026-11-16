# `include/crown/ir/tree.hpp` — block usage map

[Source](../../../../../../include/crown/ir/tree.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `982c7a07601b22b337438e92c3417520be0e32797e4e841487854685c8e24955`. 27 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/ir/tree.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../../include/crown/ir/tree.hpp#L8) | Type/record definition: enum class NodeKind |  · [reviewed contract](#b0002) |
| [B0003 · 9–10](../../../../../../include/crown/ir/tree.hpp#L9) | Explanatory comments or spacing. | source comment (unverified): // This aggregate records proposed structure; validate_tree checks its references, · [reviewed contract](#b0003) |
| [B0004 · 11–18](../../../../../../include/crown/ir/tree.hpp#L11) | Type/record definition: struct TreeNode | source comment (unverified): // This aggregate records proposed structure; validate_tree checks its references, · [reviewed contract](#b0004) |
| [B0005 · 19–20](../../../../../../include/crown/ir/tree.hpp#L19) | Explanatory comments or spacing. | source comment (unverified): // This aggregate carries optional claims; validate_tree checks them and reports · [reviewed contract](#b0005) |
| [B0006 · 21–26](../../../../../../include/crown/ir/tree.hpp#L21) | Type/record definition: struct FreeConnexTree | source comment (unverified): // This aggregate carries optional claims; validate_tree checks them and reports · [reviewed contract](#b0006) |
| [B0007 · 27–27](../../../../../../include/crown/ir/tree.hpp#L27) | Closes surrounding scope/type. | source comment (unverified): // namespace crown · [reviewed contract](#b0007) |

## B0001

[Lines 1–7](../../../../../../include/crown/ir/tree.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using VariableSet = std::set<VariableId>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the ordered variable-scope container used by proposed tree nodes. |
| inputs / outputs | \`VariableSet\` is \`std::set&lt;VariableId&gt;\` and is stored in \`TreeNode::scope\` and optional separator claims. |
| invariants | Ordering is the ID ordering of the set; the alias does not validate IDs or certify a tree/scope/separator. |
| ownership | Each set owns its ID nodes; \`FreeConnexTree\` and its \`TreeNode\` values own their scope sets. |
| failure | Out-of-range or invalid scopes are rejected by \`validate_tree\`, not by the alias or insertion operation. |
| cost | Insertion may allocate a tree node for a new ID; lookup uses ordered comparisons without inserting or allocating a node. Verification separately traverses supplied scopes and graph edges. |
| Design | [include/crown/ir/tree.hpp §VariableSet and tree DTOs](../../../../../../include/crown/ir/tree.hpp), [src/planner/verify.cpp §validate_tree](../../../../../../src/planner/verify.cpp), [docs/tree_oracle.md §independent tree verification](../../../../../tree_oracle.md) |

## B0002

[Lines 8–8](../../../../../../include/crown/ir/tree.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class NodeKind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tags a tree node as native or generalized. |
| inputs / outputs | Selects which occurrence and generalized-guard rules apply to a TreeNode. |
| invariants | The tag alone does not make a tree valid; native occurrence coverage and generalized-node constraints are checked by validate_tree. |
| ownership | Value-sized enum held by TreeNode; no node/tree ownership. |
| failure | No intrinsic failure; invalid combinations of kind and fields are rejected by the verifier. |
| cost | Constant-size storage and comparison. |
| Design | [include/crown/ir/tree.hpp](../../../../../../include/crown/ir/tree.hpp), [docs/tree_plans.md](../../../../../tree_plans.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp), [include/crown/planner/verify.hpp](../../../../../../include/crown/planner/verify.hpp) |

## B0003

[Lines 9–10](../../../../../../include/crown/ir/tree.hpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L10:sha256:e0e17fa8c107cf5cdda426f8d05093c551ba481ade08ee010447a7b9192c7f83
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: This aggregate records proposed structure; validate_tree checks its references, scopes, occurrence rules, topology, and claimed separator before acceptance. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/ir/tree.hpp lines 7-12; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/ir/tree.hpp](../../../../../../include/crown/ir/tree.hpp), [docs/code_specs/files/include/crown/ir/tree.hpp.md](tree.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0004

[Lines 11–18](../../../../../../include/crown/ir/tree.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TreeNode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describes one named CROWN-tree node and its proposed structure. |
| inputs / outputs | Stores a string label, kind, variable scope, child NodeIds, optional atom occurrence, and optional claimed separator. |
| invariants | This public aggregate does not validate references, scope membership, native occurrence rules, generalized rules, topology, or separator claims. A generalized node has no occurrence; claims are checked against computed values. |
| ownership | Owns its string, ordered VariableSet, child vector, and optional set. Copying copies dynamic members. |
| failure | Arbitrary combinations can be constructed. validate_tree reports structural/query violations and checks any separator claim. |
| cost | Storage/copy is proportional to label length, scope size, and child count; no traversal occurs on construction. |
| Design | [include/crown/ir/tree.hpp](../../../../../../include/crown/ir/tree.hpp), [docs/tree_plans.md](../../../../../tree_plans.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp), [include/crown/planner/verify.hpp](../../../../../../include/crown/planner/verify.hpp) |

## B0005

[Lines 19–20](../../../../../../include/crown/ir/tree.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L20:sha256:d770267c937c0dbb3fb4991a081a681dafbf4492302ab41168df4df451f5fb88
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: This aggregate carries optional claims; validate_tree checks them and reports a valid upper bound, not proof that the supplied tree has minimum height. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/ir/tree.hpp lines 17-22; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/ir/tree.hpp](../../../../../../include/crown/ir/tree.hpp), [docs/code_specs/files/include/crown/ir/tree.hpp.md](tree.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0006

[Lines 21–26](../../../../../../include/crown/ir/tree.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FreeConnexTree {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carries a supplied tree plus optional connex-subtree and native-height claims. |
| inputs / outputs | Stores an optional root, vector of nodes, optional claimed connex node list, and optional claimed native height. |
| invariants | Construction does not check root/node references, tree shape, output connectivity, or claims. validate_tree checks validity and claims; its success proves only a valid upper bound, not minimum height. A claimed connex subtree may be smaller than maximal C*. |
| ownership | Owns node vector and optional claim vector; child/root IDs are scalar references, not owning pointers. |
| failure | Malformed tree and false claims are representable; validate_tree returns an invalid report. Empty-body canonical tree uses no root and no nodes. |
| cost | Copy/storage proportional to node data and claimed-node list; verifier separately traverses/copies these inputs. |
| Design | [include/crown/ir/tree.hpp](../../../../../../include/crown/ir/tree.hpp), [docs/tree_plans.md](../../../../../tree_plans.md), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/verify.cpp](../../../../../../src/planner/verify.cpp), [include/crown/planner/verify.hpp](../../../../../../include/crown/planner/verify.hpp) |

## B0007

[Lines 27–27](../../../../../../include/crown/ir/tree.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:250c3e1595f7269cedf50435b03d999ca6184ec33c6daa9baf0e4bd97c55f07a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/ir/tree.hpp](../../../../../../include/crown/ir/tree.hpp), [docs/code_specs/files/include/crown/ir/tree.hpp.md](tree.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |
