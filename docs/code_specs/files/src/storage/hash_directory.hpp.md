# `src/storage/hash_directory.hpp` — block usage map

[Source](../../../../../src/storage/hash_directory.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Provide separately chained stable-node hash lookup and prepared bucket-array growth.

Snapshot SHA-256: `62e57a2660102bf1cc4e71863d73808e28b1a2a8e99023abef9428689791f464`. 336 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../src/storage/hash_directory.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // One hook per directory membership. Node ownership and public live-order · [reviewed contract](#b0001) |
| [B0002 · 18–40](../../../../../src/storage/hash_directory.hpp#L18) | Type/record definition: template &lt;class Node&gt; struct HashDirectoryHook | source comment (unverified): // One hook per directory membership. Node ownership and public live-order · [reviewed contract](#b0002) |
| [B0003 · 41–61](../../../../../src/storage/hash_directory.hpp#L41) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::numeric_limits&lt;std::size_t&gt;::digits &lt;= 64);; source comment (unverified): // Stable separately chained nodes; array entries are nonowning pointers. · [reviewed contract](#b0003) |
| [B0004 · 62–91](../../../../../src/storage/hash_directory.hpp#L62) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | returns owner_ != nullptr; active() && !replacement_.empty(); source comment (unverified): // A consumed/moved-from token reports zero, not its retained obsolete array. · [reviewed contract](#b0004) |
| [B0005 · 92–125](../../../../../src/storage/hash_directory.hpp#L92) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | returns size_; buckets_.size(); 1 loop sites; source comment (unverified): // Does not own nodes. Their hooks must not be reused after this directory · [reviewed contract](#b0005) |
| [B0006 · 126–159](../../../../../src/storage/hash_directory.hpp#L126) | declares callable signatures; declares values/defaults or compile-time conditions. | returns prepare_growth(required_nodes, allowance, maximum_slots_); result; source comment (unverified): // No published pointers change during preparation. Slot initialization and · [reviewed contract](#b0006) |
| [B0007 · 160–186](../../../../../src/storage/hash_directory.hpp#L160) | declares callable signatures; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): // Caller has already admitted any aggregate table capacity and all remaining · [reviewed contract](#b0007) |
| [B0008 · 187–215](../../../../../src/storage/hash_directory.hpp#L187) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Undo can restore the original resident position without comparing keys, · [reviewed contract](#b0008) |
| [B0009 · 216–243](../../../../../src/storage/hash_directory.hpp#L216) | declares callable signatures; declares values/defaults or compile-time conditions. | returns buckets_.get_allocator().allocation_usage(buckets_.data(), buckets_.capacity()); source comment (unverified): // Available to allocator-aware owners. This reads the actual capacity block. · [reviewed contract](#b0009) |
| [B0010 · 244–274](../../../../../src/storage/hash_directory.hpp#L244) | declares callable signatures; declares values/defaults or compile-time conditions. | guard require(buckets_.empty() \|\| (buckets_.size() &gt;= 8 && (buckets_.size() & (buckets_.size() - 1)) == 0…; 4 loop sites; source comment (unverified): // Nonallocating diagnostic. Each resident must occur in its exact hash chain; · [reviewed contract](#b0010) |
| [B0011 · 275–305](../../../../../src/storage/hash_directory.hpp#L275) | declares callable signatures; declares values/defaults or compile-time conditions. | guard require(buckets_.empty() \|\| (buckets_.size() &gt;= 8 &&; growth insert; 3 loop sites; source comment (unverified): // Explicit full diagnostic, separate from probes/cursors and their grants. · [reviewed contract](#b0011) |
| [B0012 · 306–336](../../../../../src/storage/hash_directory.hpp#L306) | declares callable signatures; declares values/defaults or compile-time conditions. | returns node.*Hook; node.*Hook; 1 loop sites; source comment (unverified): // namespace crown::storage::detail · [reviewed contract](#b0012) |

## B0001

[Lines 1–17](../../../../../src/storage/hash_directory.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:22d45d88c244e353a960e27790e16a1f6f369487f6536c7a8ab3a4d31b87f586
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/hash_directory.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/index_work.hpp"\`, \`&lt;cstddef&gt;\`, \`&lt;cstdint&gt;\`, \`&lt;exception&gt;\`, \`&lt;limits&gt;\`, \`&lt;memory&gt;\`, \`&lt;type_traits&gt;\`, \`&lt;set&gt;\`, \`&lt;utility&gt;\`, \`&lt;vector&gt;\` for compilation; opens namespace \`crown::storage::detail\`. Source comment: One hook per directory membership. Node ownership and public live-order lists belong to the table; a directory may also contain private empty keys. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: One hook per directory membership. Node ownership and public live-order lists belong to the table; a directory may also contain private empty keys. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: One hook per directory membership. Node ownership and public live-order lists belong to the table; a directory may also contain private empty keys. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 18–40](../../../../../src/storage/hash_directory.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct HashDirectoryHook {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Embed independent nonowning hash and resident-list membership in a stable node. |
| inputs / outputs | Node-local hook holds cached hash, directory owner, chain back-link and resident neighbors. |
| invariants | Owner/links determine membership; hash zero is valid and hash survives reset for prepaid undo. |
| ownership | The surrounding table owns the node; directory arrays and hooks never own each other. |
| failure | Membership operations rely on the hook belonging to the chosen template member. |
| cost | Fixed pointers/scalar per directory membership; reset is O(1) and allocation-free. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

## B0003

[Lines 41–61](../../../../../src/storage/hash_directory.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L61:sha256:f424ca1853298acbb9720a2b58e2e7ecb9957dfd7fb09f721f6b4b4163b3aff7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/hash_directory.hpp: imports or aliases \`HookType = HashDirectoryHook&lt;Node&gt;\`; defines/starts \`class HashDirectory\` in this range; declares constant-initialized constexpr/static metadata \`link_actions\`, \`unlink_actions\`, \`rehash_actions_per_node\`. Source comment: Stable separately chained nodes; array entries are nonowning pointers. Usage: prepare_growth may allocate/throw, then publish_growth and prepaid link/unlink only rewrite admitted pointers. Nodes and their hooks outlive membership; live-order iteration is separate. See docs/code_specs/primitives.md. Expected lookup cost assumes distributed hashes. Full-hash collisions still invoke exact equality and may consume a linear number of admitted visits. Upper bounds on structural pointer writes; callers reserve these before using the nonthrowing publication methods. Rehash reserves separately Member/state declarations in this range include \`static constexpr std::uint64_t unlink_actions = 12\`; \`static constexpr std::uint64_t rehash_actions_per_node = 5\`. |
| inputs / outputs | This span declares/carries these members or local values: \`static constexpr std::uint64_t unlink_actions = 12\`; \`static constexpr std::uint64_t rehash_actions_per_node = 5\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | The constexpr/static metadata is initialized as a constant expression and has no per-instance owner. The source note says: Stable separately chained nodes; array entries are nonowning pointers. Usage: prepare_growth may allocate/throw, then publish_growth and prepaid link/unlink only rewrite admitted pointers. Nodes and their hooks outlive membership; live-order iteration is separate. See docs/code_specs/primitives.md. Expected lookup cost assumes distributed hashes. Full-hash collisions still invoke exact equality and may consume a linear number of admitted visits. Upper bounds on structural pointer writes; callers reserve these before using the nonthrowing publication methods. Rehash reserves separately. Prose alone does not enforce the rule. |
| ownership | The generic template default uses std::allocator unless an instantiation supplies another allocator/storage type. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 62–91](../../../../../src/storage/hash_directory.hpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Growth {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own unpublished replacement buckets and the admission snapshot for one directory. |
| inputs / outputs | prepare_growth returns a move-only token; active/capacity observers identify unconsumed preparation. |
| invariants | Token belongs to exactly one directory and original capacity. Consumed/moved tokens report zero capacity. |
| ownership | Before publication it owns the replacement array; afterwards it retains the obsolete pointer array until destruction. Node storage is never owned. |
| failure | Abandoning a token frees its array without changing directory membership. |
| cost | Fixed token plus actual replacement capacity; moving transfers storage without cloning node payloads. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

## B0005

[Lines 92–125](../../../../../src/storage/hash_directory.hpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Node* find(std::uint64_t hash, Equal&& equal,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe one hash chain for an exact key without taking node ownership. |
| inputs / outputs | Precomputed full hash, equality callback and remaining work allowance in; matching node pointer or null out. |
| invariants | Hash equality only filters; exact equality decides a match. Every bucket/chain visit is admitted before traversal. |
| ownership | Returned node is borrowed from the enclosing table. Directory storage contains nonowning pointers; the callback may borrow payload. |
| failure | Work/equality failure propagates without changing the directory. Caller supplies a valid directory and live nodes. |
| cost | One admitted bucket step plus visited chain nodes and exact scalar equality. Expected short chains require distributed hashes; worst case is linear in resident collisions. No direct allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0006

[Lines 126–159](../../../../../src/storage/hash_directory.hpp#L126); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t additional_slot_room)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a replacement bucket array, reserving all rehash work before it can be published. |
| inputs / outputs | Required resident count, shared allowance and aggregate additional-slot room in; move-only Growth token out. |
| invariants | required_nodes includes all current residents; per-directory and aggregate capacity both hold. Preparation changes no published node links. |
| ownership | Growth owns only its replacement array and borrows this directory; the directory and original-size relation must remain valid until publication. |
| failure | Overflow/capacity/work/allocation failures leave original buckets and membership intact. A no-growth token is still tied to its owner. |
| cost | Growth initializes O(new bucket slots) and reserves O(resident nodes) rehash/link work; no-growth has fixed admission checks. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md) |

## B0007

[Lines 160–186](../../../../../src/storage/hash_directory.hpp#L160); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void publish_growth(Growth&& growth)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a previously admitted bucket array and rebuild only hash-chain links. |
| inputs / outputs | Matching live Growth token in; directory capacity/chains changed in place. |
| invariants | Owner, old capacity and admitted resident bound must still match; caller has admitted all remaining mutation work. |
| ownership | Nodes remain table-owned and retain live/resident order. After swap, the consumed token owns only the obsolete pointer array. |
| failure | Declared noexcept; invalid prepaid state terminates instead of attempting rollback allocation. Successful publication cannot throw. |
| cost | O(resident nodes) pointer rewrites when growth occurs; O(1) for no-growth. No payload copy, hash recomputation or new allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md) |

```text
void link_prepaid(Node& node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append an admitted detached node to resident order and its hash chain. |
| inputs / outputs | Stable node and cached hash are linked at the resident tail. |
| invariants | Caller already reserved growth, pointer work and capacity; node hook is detached. |
| ownership | Adds nonowning links only; the enclosing table retains node lifetime. |
| failure | Invalid internal membership/capacity terminates; prepaid publication must not unwind. |
| cost | O(1) pointer rewrites via link_between_prepaid; no lookup, allocation, equality or hash recomputation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

## B0008

[Lines 187–215](../../../../../src/storage/hash_directory.hpp#L187); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void link_between_prepaid(Node& node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore or insert an admitted node at exact resident neighbors. |
| inputs / outputs | Detached node/hash and current previous/next resident pointers produce one directory membership. |
| invariants | Saved neighbors are valid in reverse undo order; capacity is already admitted; no pointer into an obsolete bucket array is retained. |
| ownership | Borrows stable node/neighbors and current directory array. |
| failure | Wrong owner, nonadjacent neighbors, attached node or insufficient capacity terminates. |
| cost | O(1) chain/resident link rewrites; no key search, payload copy or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

## B0009

[Lines 216–243](../../../../../src/storage/hash_directory.hpp#L216); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unlink_prepaid(Node& node)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one known resident node from its hash chain and resident list. |
| inputs / outputs | A node linked to this directory in; detached hooks and decremented size out. |
| invariants | Saved pointer-to-link and resident neighbors identify current membership; caller has prepaid the inverse/publication actions. |
| ownership | Detachment does not destroy the node or its immutable hash; owning table/journal controls lifetime. |
| failure | Noexcept internal membership checks terminate on corruption. No search or allocation is attempted during inverse cleanup. |
| cost | O(1) pointer rewrites independent of chain length; exact payload equality and bucket scans are unnecessary. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md) |

```text
static void detach_prepaid(Node& node)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Unlink a node during owner-controlled destruction if it is still attached. |
| inputs / outputs | Node hook either has no owner (no-op) or names its concrete directory for unlink_prepaid. |
| invariants | Directory owner must outlive every still-linked node; template hook fixes its directory type. |
| ownership | Does not destroy the node or own its owner. |
| failure | Noexcept; a stale owner is outside the node-lifetime contract. |
| cost | O(1), no allowance refill, key comparison or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

```text
[[nodiscard]] auto allocation_usage() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect actual directory backing-array capacity for allocator-aware owners. |
| inputs / outputs | The stored allocator receives buckets_.data() and capacity() and returns its exact usage. |
| invariants | Only instantiated when the allocator supports allocation_usage; retained spare slots remain charged. |
| ownership | Borrows array allocation; no export of nodes. |
| failure | Allocator framing/ownership contracts apply. |
| cost | O(1) direct allocation-header observation; no bucket scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

## B0010

[Lines 244–274](../../../../../src/storage/hash_directory.hpp#L244); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_invariants_noalloc() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Diagnose both directory-chain and resident-list consistency without scratch allocation. |
| inputs / outputs | Current directory in; success or fixed contract failure out. |
| invariants | Bound walks by size to reject cycles; verify owner/backlinks/bucket choice and equal populations. |
| ownership | Reads borrowed node hooks only; it neither owns nor repairs corrupt structures. |
| failure | A violated condition fails through the configured error policy. Nonallocation is the successful path property; this is not a production probe. |
| cost | O(bucket capacity + nodes + sum of chain searches); worst-case O(capacity + n²) when each resident is searched in a colliding chain. Keep outside per-row maintenance. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0011

[Lines 275–305](../../../../../src/storage/hash_directory.hpp#L275); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_invariants() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the explicit allocating directory diagnostic. |
| inputs / outputs | Checks bucket chains and resident list describe the same unique node population and consistent owners/links. |
| invariants | This is separate from operational probes and work grants; it may allocate std::set scratch. |
| ownership | Borrows stable nodes under caller synchronization. Temporary std::set storage uses ordinary diagnostic allocations outside the directory allocator/grant; sets own only pointers. |
| failure | Contract failures use Errors policy; scratch allocation failure propagates without repairing/mutating the directory. |
| cost | O(bucket capacity + n log n) time and O(n) temporary pointer-set storage; keep out of a hot probe or cursor next. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

## B0012

[Lines 306–336](../../../../../src/storage/hash_directory.hpp#L306); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static std::size_t load_limit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the admitted three-quarter bucket occupancy boundary. |
| inputs / outputs | Slot count returns slots-slots/4. |
| invariants | Published nonempty arrays have power-of-two capacity at least eight; zero permits an empty unallocated directory. |
| ownership | Pure scalar calculation. |
| failure | Noexcept. |
| cost | O(1), no allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

```text
[[nodiscard]] static std::size_t bucket_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a bucket from a cached full hash. |
| inputs / outputs | Hash and positive power-of-two capacity return low-bit masked bucket index. |
| invariants | Caller must not invoke with zero capacity; capacity layout is checked/admitted elsewhere. |
| ownership | No node or array ownership. |
| failure | Noexcept under established capacity invariant. |
| cost | O(1) mask; exact equality and full-hash checks remain in find. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |

```text
[[nodiscard]] std::size_t capacity_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the smallest reachable doubled bucket capacity admitting the required population. |
| inputs / outputs | Required node count returns current capacity when sufficient or a power-of-two growth target. |
| invariants | Never exceeds maximum_slots; minimum nonempty target is eight; no contraction occurs. |
| ownership | Pure preflight before replacement allocation. |
| failure | Capacity failure uses Errors policy before mutating buckets. |
| cost | O(number of doublings), bounded by size_t width; no row scan or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/primitives.md](../../../primitives.md) |
