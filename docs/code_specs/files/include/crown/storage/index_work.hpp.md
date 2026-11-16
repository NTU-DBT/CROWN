# `include/crown/storage/index_work.hpp` — block usage map

[Source](../../../../../../include/crown/storage/index_work.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit every work dimension atomically from one noncopyable operation balance.

Snapshot SHA-256: `fac6d9fa65fd9cfcf78cf89ed098fad4239a2d68c84debbcc8c49970addc405d`. 76 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/storage/index_work.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Conservative admissions, not elapsed time or allocator bytes. A single · [reviewed contract](#b0001) |
| [B0002 · 14–23](../../../../../../include/crown/storage/index_work.hpp#L14) | Type/record definition: struct IndexWork | source comment (unverified): // Conservative admissions, not elapsed time or allocator bytes. A single · [reviewed contract](#b0002) |
| [B0003 · 24–25](../../../../../../include/crown/storage/index_work.hpp#L24) | declares types or opens a type body. |  · [reviewed contract](#b0003) |
| [B0004 · 26–28](../../../../../../include/crown/storage/index_work.hpp#L26) | Callable definition: public: explicit IndexWorkAllowance(IndexWork limit, bool fixed_diagnostics = false) noexcept : budget_(limit), fixed_diagnostics… | calls budget_, fixed_diagnostics_ · [reviewed contract](#b0004) |
| [B0005 · 29–34](../../../../../../include/crown/storage/index_work.hpp#L29) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Borrow the canonical balance. A diagnostic alias never refills it. · [reviewed contract](#b0005) |
| [B0006 · 35–35](../../../../../../include/crown/storage/index_work.hpp#L35) | Callable definition: \[\[nodiscard\]\] const IndexWork& remaining() const noexcept | calls balance; returns balance(); source comment (unverified): // Borrow the canonical balance. A diagnostic alias never refills it. · [reviewed contract](#b0006) |
| [B0007 · 36–36](../../../../../../include/crown/storage/index_work.hpp#L36) | Callable definition: \[\[nodiscard\]\] bool fixed_diagnostics() const noexcept | calls ; returns fixed_diagnostics_ · [reviewed contract](#b0007) |
| [B0008 · 37–54](../../../../../../include/crown/storage/index_work.hpp#L37) | Callable definition: void admit(IndexWork amount) | calls balance, IndexFailure, Error; source comment (unverified): // Check every domain before consuming any of them. A failed multi-domain · [reviewed contract](#b0008) |
| [B0009 · 55–59](../../../../../../include/crown/storage/index_work.hpp#L55) | declares types or opens a type body. | source comment (unverified): // An internal diagnostic view borrows the canonical balance. It neither · [reviewed contract](#b0009) |
| [B0010 · 60–63](../../../../../../include/crown/storage/index_work.hpp#L60) | Callable definition: IndexWorkAllowance(IndexWorkAllowance& root, bool fixed) noexcept :budget_(&root),fixed_diagnostics_(fixed),alias_(true) | calls budget_, fixed_diagnostics_, alias_, std::terminate; source comment (unverified): // An internal diagnostic view borrows the canonical balance. It neither · [reviewed contract](#b0010) |
| [B0011 · 64–64](../../../../../../include/crown/storage/index_work.hpp#L64) | Callable definition: \[\[nodiscard\]\] IndexWork& balance() noexcept | calls ; returns alias_ ? budget_.root-&gt;budget_.remaining : budget_.remaining · [reviewed contract](#b0011) |
| [B0012 · 65–65](../../../../../../include/crown/storage/index_work.hpp#L65) | Callable definition: \[\[nodiscard\]\] const IndexWork& balance() const noexcept | calls ; returns alias_ ? budget_.root-&gt;budget_.remaining : budget_.remaining · [reviewed contract](#b0012) |
| [B0013 · 66–76](../../../../../../include/crown/storage/index_work.hpp#L66) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0013) |

## B0001

[Lines 1–13](../../../../../../include/crown/storage/index_work.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:2c258525f0d18d44bac4d14324508699132b9d12303614c9f375dcc9a8a02342
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/index_work.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/api/error.hpp"\`, \`"crown/storage/index_failure.hpp"\`, \`&lt;compare&gt;\`, \`&lt;cstdint&gt;\` for compilation; opens namespace \`crown::storage\`; opens namespace \`detail\`; forward-declares \`struct IndexWorkAlias\` without defining object layout; closes \`namespace detail\`. Source comment: Conservative admissions, not elapsed time or allocator bytes. A single allowance is passed through a composed operation; reservations for its undo and finalization are consumed before tentative publication and never refunded. |
| inputs / outputs | Compile-time consumers may name \`struct IndexWorkAlias\` while their definitions remain owned by the declaring headers/source files. |
| invariants | Forward declarations permit references to incomplete types; consumers that need layout or members include the defining header. Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: Conservative admissions, not elapsed time or allocator bytes. A single allowance is passed through a composed operation; reservations for its undo and finalization are consumed before tentative publication and never refunded. Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 14–23](../../../../../../include/crown/storage/index_work.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexWork {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent five conservative native index-work quantities. |
| inputs / outputs | structural_steps/scalar_fields/scalar_bytes/pointer_slots/link_actions are unsigned component counts; the default spaceship comparison is lexicographic. |
| invariants | These units are separate from elapsed time, actual requested bytes, logical support work and CPU cost. A vector of zero grants no work. Lexicographic ordering cannot replace the five independent admission comparisons. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | A declaration/value copy does not validate the represented configuration or grant authority to publish mutations. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../../src/storage/index_work_alias.hpp), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 24–25](../../../../../../include/crown/storage/index_work.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class IndexWorkAllowance {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce one noncopyable finite five-domain operation balance. |
| inputs / outputs | admit checks every requested component before debiting any; remaining exposes a const vector. Private aliases change diagnostics but share the canonical root. |
| invariants | Denial leaves this reservation undecremented, but already admitted earlier work is not refunded. Undo/finalization work is reserved before tentative links publish. |
| ownership | Root stores counters inline; private alias borrows a root whose lifetime must exceed the alias. |
| failure | Denial throws fixed IndexFailure or legacy Error according to policy. Nested aliases terminate as an internal invariant failure. |
| cost | Fixed five-domain comparisons/debits; no scan/allocation on success. Legacy failure formatting and exception runtime are separate costs. |
| Design | [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../../src/storage/index_work_alias.hpp), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 26–28](../../../../../../include/crown/storage/index_work.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit IndexWorkAllowance(IndexWork limit, bool fixed_diagnostics = false) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a noncopyable finite operation balance. |
| inputs / outputs | The public constructor stores the supplied IndexWork and fixed/legacy diagnostic policy as the canonical root balance. |
| invariants | No copy, move or refill operation is available. Independent construction is an admission decision owned by the caller, not a nested-call reset. |
| ownership | The root stores five counters inline and must outlive any private diagnostic alias. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../../src/storage/index_work_alias.hpp), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 29–34](../../../../../../include/crown/storage/index_work.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance(const IndexWorkAllowance&) = delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make one IndexWorkAllowance noncopyable and nonmovable. |
| inputs / outputs | The constructor installs a balance; this block forbids copy/move construction and assignment. |
| invariants | A caller cannot duplicate or transfer the canonical balance through ordinary object operations. |
| ownership | The allowance remains at its original address; internal aliases borrow it separately. |
| failure | Copy/move use is rejected at compile time; admit() reports exhausted domains at runtime. |
| cost | Deleted declarations add no runtime work; ordinary admit() work is defined by the allowance implementation. |
| Design | [include/crown/storage/index_work.hpp §IndexWorkAllowance](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp §IndexWorkAlias](../../../../../../src/storage/index_work_alias.hpp), [docs/indexed_storage.md](../../../../../indexed_storage.md) |

## B0006

[Lines 35–35](../../../../../../include/crown/storage/index_work.hpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const IndexWork& remaining() const noexcept { return balance(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the current canonical remaining work vector. |
| inputs / outputs | Returns balance(), which reads this root or the canonical root borrowed by a private alias. |
| invariants | Reading does not reserve work; callers cannot modify the returned const vector or infer total CPU/allocator usage from it. |
| ownership | The returned pointer/reference/view borrows its named owner; retain that owner and keep the backing bytes stable for every use. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../../src/storage/index_work_alias.hpp), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 36–36](../../../../../../include/crown/storage/index_work.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool fixed_diagnostics() const noexcept { return fixed_diagnostics_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read which exception carrier this diagnostic view uses. |
| inputs / outputs | Returns fixed_diagnostics_, independent of the shared balance. |
| invariants | A legacy diagnostic alias changes presentation without creating additional work. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../../src/storage/index_work_alias.hpp), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 37–54](../../../../../../include/crown/storage/index_work.hpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void admit(IndexWork amount)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Atomically reserve all work dimensions from a single finite operation balance. |
| inputs / outputs | Requested structural/scalar-field/scalar-byte/pointer/link amounts in; remaining balance debited on success. |
| invariants | Check every dimension first, then subtract all. A failed multidomain admission must consume none of the domains. |
| ownership | The noncopyable allowance owns its balance or borrows one canonical root through the private alias constructor; aliasing does not refill it. |
| failure | Exhaustion emits either fixed IndexFailure or the explicit legacy Error policy before any subtraction. |
| cost | Five bounded comparisons and five debits, O(1); legacy diagnostic formatting exists only on failure. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0009

[Lines 55–59](../../../../../../include/crown/storage/index_work.hpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
friend struct detail::IndexWorkAlias;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Grant the internal IndexWorkAlias access to the private borrowed-alias constructor. |
| inputs / outputs | The helper can request fixed or legacy diagnostic mode over a caller-supplied root allowance. |
| invariants | The alias uses the root's canonical balance; it creates no independent budget or refill. |
| ownership | The alias stores a borrowed root pointer, so the caller retains a non-alias root for its full lifetime. |
| failure | Friendship itself cannot fail; requesting an alias from an alias terminates in the private constructor. |
| cost | The access declaration does no work; alias construction is inline and allocates no owner. |
| Design | [include/crown/storage/index_work.hpp §IndexWorkAllowance](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp §fixed and legacy views](../../../../../../src/storage/index_work_alias.hpp), [src/runtime/storage_work.hpp §StorageWorkState](../../../../../../src/runtime/storage_work.hpp), [docs/memory_accounts.md §Optimized table work and ownership](../../../../../memory_accounts.md) |

## B0010

[Lines 60–63](../../../../../../include/crown/storage/index_work.hpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance(IndexWorkAllowance& root, bool fixed) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one canonical work root with a different diagnostic policy. |
| inputs / outputs | The private alias constructor stores a pointer to the root and sets alias_=true. |
| invariants | Aliases cannot alias another alias. Every debit reaches root.budget_.remaining; the internal bridge must retain the actual root separately. |
| ownership | The alias owns no allowance storage or root lifetime; it requires the root to stay alive and unmoved. |
| failure | Aliasing an alias calls terminate as an internal invariant failure; otherwise construction is noexcept. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../../src/storage/index_work_alias.hpp), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0011

[Lines 64–64](../../../../../../include/crown/storage/index_work.hpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] IndexWork& balance() noexcept { return alias_ ? budget_.root->budget_.remaining : budget_.remaining; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the mutable canonical balance without copying limits. |
| inputs / outputs | Selects this root's inline remaining vector or the one immediate root pointer permitted by the alias invariant. |
| invariants | Only the active union member selected by alias_ is read; no recursive alias chain is admitted. |
| ownership | The returned pointer/reference/view borrows its named owner; retain that owner and keep the backing bytes stable for every use. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../../src/storage/index_work_alias.hpp), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 65–65](../../../../../../include/crown/storage/index_work.hpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const IndexWork& balance() const noexcept { return alias_ ? budget_.root->budget_.remaining : budget_.remaining; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the const canonical balance without copying limits. |
| inputs / outputs | Selects this root's inline remaining vector or the one immediate root pointer permitted by the alias invariant. |
| invariants | Only the active union member selected by alias_ is read; no recursive alias chain is admitted. |
| ownership | The returned pointer/reference/view borrows its named owner; retain that owner and keep the backing bytes stable for every use. |
| failure | The shown inline operation is noexcept and has no throwing body or exception translation. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../../src/storage/index_work_alias.hpp), [tests/unit/indexed_cursor_test.cpp](../../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 66–76](../../../../../../include/crown/storage/index_work.hpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
union Budget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent either an allowance's local remaining counters or a borrowed pointer to its root. |
| inputs / outputs | Canonical construction stores IndexWork; internal alias construction stores an IndexWorkAllowance pointer. |
| invariants | alias_ selects the active union member; the root pointer does not own or refill its target. |
| ownership | Alias lifetime is bounded by the caller-retained canonical root; nested aliases are rejected. |
| failure | The union declaration cannot fail; alias construction terminates if root.alias_ is already true. |
| cost | Inline fixed-size state with no allocation; balance() selects the local or root balance. |
| Design | [include/crown/storage/index_work.hpp §Budget and balance](../../../../../../include/crown/storage/index_work.hpp), [src/storage/index_work_alias.hpp §IndexWorkAlias](../../../../../../src/storage/index_work_alias.hpp), [src/runtime/storage_work.hpp §StorageWorkState](../../../../../../src/runtime/storage_work.hpp), [docs/indexed_storage.md](../../../../../indexed_storage.md) |
