# `src/storage/live_list.hpp` — block usage map

[Source](../../../../../src/storage/live_list.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Provide intrusive nonowning membership and O(1) prepaid link/unlink for live traversal.

Snapshot SHA-256: `b154699ed5ac832596676dd1fc58d2009829d60d90d4be4a260babba59bf4e51`. 130 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/storage/live_list.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–20](../../../../../src/storage/live_list.hpp#L10) | Type/record definition: template &lt;class Node&gt; struct LiveListHook |  · [reviewed contract](#b0002) |
| [B0003 · 21–50](../../../../../src/storage/live_list.hpp#L21) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | returns size_; first_; source comment (unverified): // Nonowning live membership. A row can own its member nodes through one hook · [reviewed contract](#b0003) |
| [B0004 · 51–84](../../../../../src/storage/live_list.hpp#L51) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Saved neighbors are restored in reverse undo order. This validates only · [reviewed contract](#b0004) |
| [B0005 · 85–120](../../../../../src/storage/live_list.hpp#L85) | declares callable signatures; declares values/defaults or compile-time conditions. | guard require(size_ &lt;= maximum_nodes_);; 1 loop sites; source comment (unverified): // Used by owning node destructors. The hook's concrete list type is fixed · [reviewed contract](#b0005) |
| [B0006 · 121–130](../../../../../src/storage/live_list.hpp#L121) | declares values/defaults or compile-time conditions. | returns node.*Hook; node.*Hook; source comment (unverified): // namespace crown::storage::detail · [reviewed contract](#b0006) |

## B0001

[Lines 1–9](../../../../../src/storage/live_list.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:a02f275d74ac3513fba9d5473461b0c0aae553a96672e3afce7d45c0d6ddf3bc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/live_list.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/index_work.hpp"\`, \`&lt;cstddef&gt;\`, \`&lt;exception&gt;\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::storage::detail\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 10–20](../../../../../src/storage/live_list.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LiveListHook {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Embed one nonowning live-list membership independently of row annotations. |
| inputs / outputs | A node-local hook holds owner plus previous/next pointers. |
| invariants | Hooks are noncopyable/nonmovable so pointer identity stays stable; each membership uses its own hook. |
| ownership | Enclosing table owns node storage and controls list-before-node teardown. |
| failure | Hook lifetime/membership contracts are internal, not a user-facing recovery mechanism. |
| cost | Three fixed pointers per membership; no allocation or numerical annotation inspection. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

## B0003

[Lines 21–50](../../../../../src/storage/live_list.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::pair<Node*, Node*> neighbors(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture exact live neighbors for prepaid reverse-order undo. |
| inputs / outputs | An attached node yields its current previous/next pointers. |
| invariants | Node belongs to this list; saved neighbors are only restorable under the corresponding reverse undo ordering. |
| ownership | Pointers borrow nodes/list and retain no payload independently. |
| failure | Foreign/detached node terminates because this is an internal prepaid-undo primitive. |
| cost | O(1), no scan or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

## B0004

[Lines 51–84](../../../../../src/storage/live_list.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void insert_between_prepaid(Node& node, Node* previous_node, Node* next_node)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Link a detached node at saved live neighbors, including reverse-order journal restoration. |
| inputs / outputs | Detached node and currently adjacent neighbors in; live membership and size updated. |
| invariants | The hook is unowned, capacity was admitted, and both neighbors are live/adjacent in this list. Replay inverses in reverse order. |
| ownership | The list borrows nodes; node/table owner must outlive membership. Different hook members can represent distinct memberships of the same node. |
| failure | Noexcept invariant checks terminate on misuse; mutation allocates nothing and does not call arbitrary comparison code. |
| cost | Fixed O(1) pointer writes. No row/payload/annotation scan determines membership. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md) |

```text
void prepare_insert(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit fixed pointer work and check live-node capacity before publication. |
| inputs / outputs | Original work allowance is charged for one structural step and insertion actions. |
| invariants | No list mutation occurs here; the caller still funds/constructs node storage separately. |
| ownership | Borrows the caller allowance without creating a new grant. |
| failure | Allowance or configured capacity failure propagates before list insertion. |
| cost | O(1) admission/checks, no allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

```text
void prepare_erase(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit fixed unlink work and validate list ownership before removal. |
| inputs / outputs | Node plus original allowance charges one structural step and erase actions. |
| invariants | Only attached nodes from this exact list can be erased; prepaid method runs after successful preparation. |
| ownership | Borrows node and grant; creates no pin or inverse itself. |
| failure | Work or foreign-membership failure uses Errors policy before pointer mutation. |
| cost | O(1), no allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

```text
void append_prepaid(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a fully prepared detached node at the live tail. |
| inputs / outputs | Node becomes attached after insert_between_prepaid(node,last,null). |
| invariants | Capacity and pointer work are already reserved; caller owns the stable node. |
| ownership | Nonowning membership only. |
| failure | Noexcept; invalid internal state terminates. |
| cost | O(1) pointer updates, no payload scan/allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

## B0005

[Lines 85–120](../../../../../src/storage/live_list.hpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void erase_prepaid(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Unlink one known attached node and clear its live hook. |
| inputs / outputs | Node is detached; first/last/neighbors and list size are updated. |
| invariants | Node belongs to this list, whose size is positive; prepare_erase or inverse funding already admitted work. |
| ownership | Does not destroy/reclaim node payload, which may still be retained by a journal. |
| failure | Noexcept; incorrect membership terminates. |
| cost | O(1) pointer rewrites; independent of row/value/annotation size. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

```text
static void detach_prepaid(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach a still-linked node from its concrete live owner during destruction. |
| inputs / outputs | Absent owner is harmless; present hook owner routes to erase_prepaid. |
| invariants | Concrete template hook fixes owner type; owner must outlive linked node. |
| ownership | Nonowning unlink; node destructor remains the caller. |
| failure | Noexcept; stale owner violates teardown ordering. |
| cost | O(1), nonallocating. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

```text
void check_invariants() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Diagnose bounded live-list population and bidirectional link consistency. |
| inputs / outputs | Walk first-to-last and compare owner, predecessor, count and endpoint invariants. |
| invariants | Count bound rejects a cycle before unbounded traversal; size cannot exceed configured maximum. |
| ownership | Borrows nodes under caller synchronization; uses no visited collection. |
| failure | Errors policy reports contract failures; this routine repairs nothing. |
| cost | O(live nodes), O(1) scratch, no allocation; ordinary cursor/list traversal still follows one link per step. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

## B0006

[Lines 121–130](../../../../../src/storage/live_list.hpp#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L130:sha256:c500566d21dd3b945a943f5ad3a4e9346552e7f89874502288c68c522a85fbf4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/live_list.hpp: closes \`block opened at line 122\`, \`block opened at line 123\`, \`class LiveList\`, \`namespace crown::storage::detail\`; defines helper body/bodies \`hook\` Member/state declarations in this range include \`} const std::size_t maximum_nodes_\`; \`std::size_t size_ = 0\`; \`Node* first_ = nullptr\`; \`Node* last_ = nullptr\`. |
| inputs / outputs | This span declares/carries these members or local values: \`} const std::size_t maximum_nodes_\`; \`std::size_t size_ = 0\`; \`Node* first_ = nullptr\`; \`Node* last_ = nullptr\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::storage::detail Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
