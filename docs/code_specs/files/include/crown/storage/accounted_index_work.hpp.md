# `include/crown/storage/accounted_index_work.hpp` — block usage map

[Source](../../../../../../include/crown/storage/accounted_index_work.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `83bd30ca85483e64d4198d66141791b32f571585f94e25d3240b8dd4cf362825`. 42 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/storage/accounted_index_work.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // An owning composed-operation work grant, with object/control storage funded · [reviewed contract](#b0001) |
| [B0002 · 11–16](../../../../../../include/crown/storage/accounted_index_work.hpp#L11) | Type/record definition: struct Control |  · [reviewed contract](#b0002) |
| [B0003 · 17–18](../../../../../../include/crown/storage/accounted_index_work.hpp#L17) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 19–23](../../../../../../include/crown/storage/accounted_index_work.hpp#L19) | Callable definition: \[\[nodiscard\]\] static AccountedIndexWork create(const resource::MemoryAccount& account, IndexWork limit, bool fixed_diagnostics = … | calls AccountedIndexWork; returns AccountedIndexWork(resource::make_accounted_shared&lt;Control&gt;(account,; growth make_accounted_shared · [reviewed contract](#b0004) |
| [B0005 · 24–24](../../../../../../include/crown/storage/accounted_index_work.hpp#L24) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns bool(control_) · [reviewed contract](#b0005) |
| [B0006 · 25–26](../../../../../../include/crown/storage/accounted_index_work.hpp#L25) | Explanatory comments or spacing. | source comment (unverified): // Const handles still share a mutable balance; retain an owner while · [reviewed contract](#b0006) |
| [B0007 · 27–27](../../../../../../include/crown/storage/accounted_index_work.hpp#L27) | Callable definition: \[\[nodiscard\]\] IndexWorkAllowance* get() const & noexcept | calls ; returns control_ ? &control_-&gt;work : nullptr; source comment (unverified): // Const handles still share a mutable balance; retain an owner while · [reviewed contract](#b0007) |
| [B0008 · 28–28](../../../../../../include/crown/storage/accounted_index_work.hpp#L28) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 29–32](../../../../../../include/crown/storage/accounted_index_work.hpp#L29) | Callable definition: \[\[nodiscard\]\] IndexWorkAllowance& operator*() const & | calls ; returns control_-&gt;work · [reviewed contract](#b0009) |
| [B0010 · 33–33](../../../../../../include/crown/storage/accounted_index_work.hpp#L33) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 34–37](../../../../../../include/crown/storage/accounted_index_work.hpp#L34) | Callable definition: \[\[nodiscard\]\] bool same_account(const resource::MemoryAccount& account) const noexcept | calls ; returns control_ && account && resource::MemoryAllocator&lt;unsigned char&gt;(control_-&gt;account) == · [reviewed contract](#b0011) |
| [B0012 · 38–39](../../../../../../include/crown/storage/accounted_index_work.hpp#L38) | Callable definition: private: explicit AccountedIndexWork(std::shared_ptr&lt;Control&gt; control) noexcept : control_(std::move(control)) | calls control_, std::move · [reviewed contract](#b0012) |
| [B0013 · 40–42](../../../../../../include/crown/storage/accounted_index_work.hpp#L40) | Member/declaration region. |  · [reviewed contract](#b0013) |

## B0001

[Lines 1–10](../../../../../../include/crown/storage/accounted_index_work.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedIndexWork {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain and share exactly one finite native operation grant. |
| inputs / outputs | create funds Control once; copies share remaining work, get/operator* borrow it, and same_account checks the original account. |
| invariants | No refill, per-table grant or synchronization is implied by copying this handle. |
| ownership | shared Control retains its account and funded shared allocation; raw returned allowance aliases need a surviving owner. |
| failure | Construction may reject admission/allocation; empty dereference throws fixed storage_contract. Nullable get is the explicit absence path. |
| cost | One funded fixed control allocation at create, then handle/refcount operations; last release destroys that control and can release its account. |
| Design | [include/crown/storage/accounted_index_work.hpp](../../../../../../include/crown/storage/accounted_index_work.hpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 11–16](../../../../../../include/crown/storage/accounted_index_work.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Control {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the query account and one canonical finite allowance in its funded control. |
| inputs / outputs | Control copies the account handle and constructs IndexWorkAllowance from the supplied five limits and diagnostic policy. |
| invariants | Every AccountedIndexWork copy shares this same balance; concurrent mutation requires external coordination. |
| ownership | Control retains its account; make_accounted_shared funds the actual shared object and control storage from that account. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_index_work.hpp](../../../../../../include/crown/storage/accounted_index_work.hpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 17–18](../../../../../../include/crown/storage/accounted_index_work.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexWork() noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow an empty AccountedIndexWork handle as the invalid/default state. |
| inputs / outputs | Default construction produces an empty handle; create(account, limit) produces a funded work owner. |
| invariants | An empty handle converts to false and get() returns null. |
| ownership | The default handle owns no Control, account, or allowance. |
| failure | Default construction cannot fail; dereferencing an empty handle is checked by operator*. |
| cost | Default construction performs no allocation or grant creation. |
| Design | [include/crown/storage/accounted_index_work.hpp §AccountedIndexWork](../../../../../../include/crown/storage/accounted_index_work.hpp), [src/runtime/storage_work.hpp §StorageWorkState](../../../../../../src/runtime/storage_work.hpp), [docs/memory_accounts.md §Optimized table work and ownership](../../../../../memory_accounts.md) |

## B0004

[Lines 19–23](../../../../../../include/crown/storage/accounted_index_work.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static AccountedIndexWork create(const resource::MemoryAccount& account, IndexWork limit,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a funded owner for a composed storage operation grant. |
| inputs / outputs | The existing account, finite limit vector and fixed/legacy diagnostic selection produce one AccountedIndexWork. |
| invariants | Creating a new grant is an explicit admission boundary, not something nested storage calls may repeat to reset work. |
| ownership | The shared Control and rebound shared ownership allocation are funded under support_metadata in the supplied account. |
| failure | Account admission, allocator failure or size overflow propagates; no partial owner is returned and no fallback account is created. |
| cost | A fixed-size accounted shared allocation plus handle construction; allocator framing counts toward the account. |
| Design | [include/crown/storage/accounted_index_work.hpp](../../../../../../include/crown/storage/accounted_index_work.hpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 24–24](../../../../../../include/crown/storage/accounted_index_work.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] explicit operator bool() const noexcept { return bool(control_); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether a shared operation-grant owner exists. |
| inputs / outputs | Returns whether control_ is nonnull, including false for a default or moved-from owner. |
| invariants | Presence says nothing about remaining work or whether a particular operation fits. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_index_work.hpp](../../../../../../include/crown/storage/accounted_index_work.hpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 25–26](../../../../../../include/crown/storage/accounted_index_work.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L26:sha256:60eb1dd50a3d643bd3d8065e9dc9635558fef41c68d3b13ad961c9e527f30392
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`\[\[nodiscard\]\] IndexWorkAllowance* get() const & noexcept\`: Const handles still share a mutable balance; retain an owner while using this borrow. Sharing the handle supplies no thread synchronization. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/storage/accounted_index_work.hpp:L27; use that declaration for the actual input/output shape. |
| invariants | The source note states: Const handles still share a mutable balance; retain an owner while using this borrow. Sharing the handle supplies no thread synchronization. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Const handles still share a mutable balance; retain an owner while using this borrow. Sharing the handle supplies no thread synchronization. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0007

[Lines 27–27](../../../../../../include/crown/storage/accounted_index_work.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] IndexWorkAllowance* get() const & noexcept { return control_ ? &control_->work : nullptr; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the canonical mutable balance from a retained grant owner. |
| inputs / outputs | Returns a mutable IndexWorkAllowance pointer or nullptr; invoking on an rvalue is deleted. |
| invariants | Const qualification of the handle does not make the shared balance immutable; copying the handle does not refill it. |
| ownership | The returned pointer/reference/view borrows its named owner; retain that owner and keep the backing bytes stable for every use. Another AccountedIndexWork copy can retain the same Control. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_index_work.hpp](../../../../../../include/crown/storage/accounted_index_work.hpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 28–28](../../../../../../include/crown/storage/accounted_index_work.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance* get() const && = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forbid borrowing the mutable allowance pointer from a temporary AccountedIndexWork. |
| inputs / outputs | A valid lvalue handle can return its shared allowance pointer; an rvalue call is rejected at compile time. |
| invariants | The pointer borrows the Control-owned balance and does not create a new grant. |
| ownership | The AccountedIndexWork owner must remain alive while the pointer is used. |
| failure | Rvalue use is a compile-time error; lvalue get() returns null for an empty handle. |
| cost | The deleted overload has no runtime work; the lvalue getter checks a shared pointer and returns a borrowed pointer. |
| Design | [include/crown/storage/accounted_index_work.hpp §get](../../../../../../include/crown/storage/accounted_index_work.hpp), [src/runtime/storage_work.hpp §StorageWorkState](../../../../../../src/runtime/storage_work.hpp), [docs/memory_accounts.md §Optimized table work and ownership](../../../../../memory_accounts.md) |

## B0009

[Lines 29–32](../../../../../../include/crown/storage/accounted_index_work.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] IndexWorkAllowance& operator*() const & {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a present owner before borrowing its allowance. |
| inputs / outputs | Lvalue dereference returns the same canonical IndexWorkAllowance; empty handles reject. |
| invariants | The result is an alias, never a copied balance or replacement operation grant. |
| ownership | The returned pointer/reference/view borrows its named owner; retain that owner and keep the backing bytes stable for every use. |
| failure | An empty handle throws fixed IndexFailure(storage_contract); the carrier owns no formatted string. Exception-runtime storage is a separate concern. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_index_work.hpp](../../../../../../include/crown/storage/accounted_index_work.hpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 33–33](../../../../../../include/crown/storage/accounted_index_work.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance& operator*() const && = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forbid returning an allowance reference from a temporary AccountedIndexWork. |
| inputs / outputs | Dereferencing a valid lvalue returns its shared allowance; rvalue dereference is rejected at compile time. |
| invariants | The reference aliases the Control's single mutable balance. |
| ownership | The AccountedIndexWork owner must outlive use of the returned reference. |
| failure | Rvalue use is a compile-time error; empty lvalue dereference throws IndexFailure(contract). |
| cost | The deleted declaration has no runtime work; valid lvalue dereference performs a handle check. |
| Design | [include/crown/storage/accounted_index_work.hpp §operator*](../../../../../../include/crown/storage/accounted_index_work.hpp), [src/runtime/storage_work.hpp §StorageWorkState](../../../../../../src/runtime/storage_work.hpp), [docs/memory_accounts.md §Optimized table work and ownership](../../../../../memory_accounts.md) |

## B0011

[Lines 34–37](../../../../../../include/crown/storage/accounted_index_work.hpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool same_account(const resource::MemoryAccount& account) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether the operation grant belongs to a given existing account. |
| inputs / outputs | Returns false for an empty grant/account; otherwise compares default MemoryAllocator identities for the stored and supplied accounts. |
| invariants | Account identity is distinct from equal limits and is required by native facade journals. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_index_work.hpp](../../../../../../include/crown/storage/accounted_index_work.hpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 38–39](../../../../../../include/crown/storage/accounted_index_work.hpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit AccountedIndexWork(std::shared_ptr<Control> control) noexcept : control_(std::move(control)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt an already funded shared Control without another grant. |
| inputs / outputs | Private constructor moves one shared_ptr into control_. |
| invariants | Only create can supply the allocated control through this constructor; its current balance is unchanged. |
| ownership | Ownership of the existing shared control is transferred into this handle. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/accounted_index_work.hpp](../../../../../../include/crown/storage/accounted_index_work.hpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [src/storage/accounted_table.cpp](../../../../../../src/storage/accounted_table.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 40–42](../../../../../../include/crown/storage/accounted_index_work.hpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<Control> control_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the funded Control that contains the account and shared IndexWorkAllowance. |
| inputs / outputs | create(account, limit) initializes the Control; copies of the handle retain that same control. |
| invariants | Copies share one mutable balance, and same_account checks account identity rather than making an allowance. |
| ownership | The shared pointer owns the account-backed Control; its final release frees that allocation. |
| failure | The member declaration has no failure path; create can fail on account allocation or invalid account state. |
| cost | The field declaration allocates nothing; copies share ownership, and final cleanup includes Control/account release. |
| Design | [include/crown/storage/accounted_index_work.hpp §Control](../../../../../../include/crown/storage/accounted_index_work.hpp), [src/runtime/storage_work.hpp §StorageWorkState](../../../../../../src/runtime/storage_work.hpp), [docs/memory_accounts.md §Optimized table work and ownership](../../../../../memory_accounts.md), [docs/query_memory.md](../../../../../query_memory.md) |
