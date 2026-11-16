# `src/ir/update_pattern_detail.hpp` — block usage map

[Source](../../../../../src/ir/update_pattern_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `5ffbe173951a4c2d47a249aaeb9c4b9c5a2bf50d58d79c524da8e42e05c9acbb`. 36 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_identity.md](../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../src/ir/update_pattern_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Attribution identifies this component inside the original query cap. · [reviewed contract](#b0001) |
| [B0002 · 12–15](../../../../../src/ir/update_pattern_detail.hpp#L12) | Callable definition: template&lt;class T&gt; resource::OwnerAllocator&lt;T&gt; allocator(const resource::MemoryAccount& account, resource::MemoryPurpose purpose =… | calls ; returns resource::OwnerAllocator&lt;T&gt;(account, purpose, owner) · [reviewed contract](#b0002) |
| [B0003 · 16–18](../../../../../src/ir/update_pattern_detail.hpp#L16) | Callable definition: inline void require(bool value) | calls Failure; guard inline void require(bool value) { · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../src/ir/update_pattern_detail.hpp#L19) | Explanatory comments or spacing. | source comment (unverified): // Store a canonical, immutable declaration; no observed row history is retained. · [reviewed contract](#b0004) |
| [B0005 · 20–28](../../../../../src/ir/update_pattern_detail.hpp#L20) | Type/record definition: struct Data | source comment (unverified): // Store a canonical, immutable declaration; no observed row history is retained. · [reviewed contract](#b0005) |
| [B0006 · 29–30](../../../../../src/ir/update_pattern_detail.hpp#L29) | Explanatory comments or spacing. | source comment (unverified): // One validated builder and one already-validated account transfer, without a · [reviewed contract](#b0006) |
| [B0007 · 31–35](../../../../../src/ir/update_pattern_detail.hpp#L31) | Type/record definition: struct Factory | source comment (unverified): // One validated builder and one already-validated account transfer, without a · [reviewed contract](#b0007) |
| [B0008 · 36–36](../../../../../src/ir/update_pattern_detail.hpp#L36) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::patterns::detail · [reviewed contract](#b0008) |

## B0001

[Lines 1–11](../../../../../src/ir/update_pattern_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:6cf008643982905e1c7546259dbf3c9166f31935cda23cee9a3c8969b3f436e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up private declaration construction, capture attribution, and account-aware internal type names. |
| inputs / outputs | Includes public declarations, owner allocator/ownership helpers, and algorithm support; \`owner\` is capture attribution kind with component code 16. |
| invariants | This namespace is implementation support only; capture attribution does not create an additional account or runtime enforcement mode. |
| ownership | Data allocations are charged to the MemoryAccount passed to Factory. |
| failure | No runtime failure in include/namespace setup. |
| cost | Compile-time scaffolding and one constexpr attribution value. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 12–15](../../../../../src/ir/update_pattern_detail.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L15:sha256:eb6c87aa318d2e55b1031e20bf6d162a8afbcb871805758bd6e7beac3d713c41
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the declaration’s typed owner allocator for a selected account and purpose. |
| inputs / outputs | T and MemoryAccount enter; returns OwnerAllocator&lt;T&gt; with capture owner attribution and default capture purpose. |
| invariants | Allocator delegates actual byte enforcement to the supplied account; it does not create a group index or hidden account. |
| ownership | Returned allocator carries the receiving/original account reference according to caller choice. |
| failure | Later allocation may fail at the account cap. |
| cost | O(1), no allocation until container growth. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0003

[Lines 16–18](../../../../../src/ir/update_pattern_detail.hpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L18:sha256:8b52ca0b5488588329e9261f1959dc54bd46a786adad7fc469c5c7af65993fb5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one failed declaration-shape predicate into the fixed invalid_declaration failure. |
| inputs / outputs | Boolean predicate in; returns normally when true or throws Failure(Fault::invalid_declaration). |
| invariants | Does not translate logical work/cell/byte stops or allocator failures. |
| ownership | No owned storage. |
| failure | Throws fixed Failure on false. |
| cost | O(1) predicate branch. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 19–19](../../../../../src/ir/update_pattern_detail.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:dde3a8c006d7a5d2bf15cf1467f8ec3a66bb8c53cd9d5040573f02bf4226a5a6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document Data as canonical immutable declaration metadata without observed row history. |
| inputs / outputs | The following record stores source binding, table count, constrained summary, usage, and rule values. |
| invariants | Data represents requested assumptions only; it is not a capture of row history or enforcement state. |
| ownership | Factory creates Data under the capture owner account. |
| failure | Construction may fail through logical or account limits in Factory. |
| cost | No additional cost beyond the represented O(R) rule vector. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0005

[Lines 20–28](../../../../../src/ir/update_pattern_detail.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L28:sha256:956ebfb6394c6f931d2c8207798d620bcef8d1b3bcf3d50834230a9ebd7ca6a6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define immutable declaration storage and initialize its account-funded TableRule vector. |
| inputs / outputs | Stores 64-byte source hash, table count, constrained flag, Usage, and Vector&lt;TableRule&gt;; constructor takes account/hash/count. |
| invariants | Published Data holds canonical table-sorted TableRule values and exact raw scope IDs. Factory mutates private Data during preparation before wrapping it in a const shared owner. No CapturedRule, scope index, group index or group scratch is retained. |
| ownership | Vector uses the account-specific capture allocator; shared Declaration handles keep this original owner alive. |
| failure | Vector allocation can fail when Factory reserves; construction does not publish a handle until complete. |
| cost | O(1) fixed metadata plus O(R) retained cells; sorting happens once in Factory at O(R log R). |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0006

[Lines 29–30](../../../../../src/ir/update_pattern_detail.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L30:sha256:1272781d7efc33b9f90b9fc5379e40888ba19008320564a6b4233fb6b06b74b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the narrow Factory boundary: one validated builder and one validated account transfer, without callback or catch layers. |
| inputs / outputs | Adjacent Factory declares make for a requested record and copy for an existing valid Declaration. |
| invariants | Validation and ownership remain explicit in these two operations; no generic retry/translation framework is introduced. |
| ownership | Each operation creates Data in its passed account. |
| failure | Their definitions may propagate Failure or allocator failures to the public caller boundary. |
| cost | Make sorts O(R log R); copy transfers O(R) values without sorting. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0007

[Lines 31–35](../../../../../src/ir/update_pattern_detail.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L35:sha256:c18562900b9d6858fe58cbd0b26f8b3e73170e76563fbf26c77acee4a1251fd9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the private construction and explicit copy operations used by Declaration. |
| inputs / outputs | make takes account, source hash, table count, rules span, and Limits; copy takes receiving account and existing Declaration. |
| invariants | make performs canonicalization/validation before returning; copy expects previously validated sorted values and preserves raw IDs. |
| ownership | Both construct distinct Data funded by their specified account. |
| failure | Signatures alone do not translate failures; callers observe Failure/account allocation errors. |
| cost | make O(R log R), copy O(R); no retained derived group index. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0008

[Lines 36–36](../../../../../src/ir/update_pattern_detail.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:31ee3c98bbbf6b9301f323cc84c15468504c1ddf192b668eeeb560e9bd6602ee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private declaration detail namespace. |
| inputs / outputs | No inputs or outputs. |
| invariants | Namespace closure has no object or semantic effect. |
| ownership | No ownership effect. |
| failure | No failure path. |
| cost | No runtime cost. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |
