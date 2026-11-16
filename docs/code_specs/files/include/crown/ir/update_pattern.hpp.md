# `include/crown/ir/update_pattern.hpp` — block usage map

[Source](../../../../../../include/crown/ir/update_pattern.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `0e94f57364b4f2a101e63b92632dde3461f96f97c11a9f349767b0b6ac22618a`. 94 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../../include/crown/ir/update_pattern.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Source-bound assumptions, independent of planner ranking and runtime state. · [reviewed contract](#b0001) |
| [B0002 · 22–27](../../../../../../include/crown/ir/update_pattern.hpp#L22) | Type/record definition: struct TableRule | source comment (unverified): // insertion_only forbids ending a physical full-row lifetime. Zero means no · [reviewed contract](#b0002) |
| [B0003 · 28–28](../../../../../../include/crown/ir/update_pattern.hpp#L28) | Explanatory comments or spacing. | source comment (unverified): // Logical construction limits; the actual receiving account is a separate cap. · [reviewed contract](#b0003) |
| [B0004 · 29–31](../../../../../../include/crown/ir/update_pattern.hpp#L29) | Type/record definition: struct Limits | source comment (unverified): // Logical construction limits; the actual receiving account is a separate cap. · [reviewed contract](#b0004) |
| [B0005 · 32–35](../../../../../../include/crown/ir/update_pattern.hpp#L32) | Type/record definition: struct Usage |  · [reviewed contract](#b0005) |
| [B0006 · 36–36](../../../../../../include/crown/ir/update_pattern.hpp#L36) | Type/record definition: enum class Fault |  · [reviewed contract](#b0006) |
| [B0007 · 37–37](../../../../../../include/crown/ir/update_pattern.hpp#L37) | Explanatory comments or spacing. | source comment (unverified): // Fixed diagnostics cross this construction boundary without allocating text. · [reviewed contract](#b0007) |
| [B0008 · 38–47](../../../../../../include/crown/ir/update_pattern.hpp#L38) | Type/record definition: class Failure final : public std::exception | returns fault_; @; source comment (unverified): // Fixed diagnostics cross this construction boundary without allocating text. · [reviewed contract](#b0008) |
| [B0009 · 48–48](../../../../../../include/crown/ir/update_pattern.hpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Ordinary caller-owned import/export DTO; it grants no runtime authority. · [reviewed contract](#b0009) |
| [B0010 · 49–53](../../../../../../include/crown/ir/update_pattern.hpp#L49) | Type/record definition: struct Record | source comment (unverified): // Ordinary caller-owned import/export DTO; it grants no runtime authority. · [reviewed contract](#b0010) |
| [B0011 · 54–75](../../../../../../include/crown/ir/update_pattern.hpp#L54) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth copy_of; source comment (unverified): // A validated declaration is a requested assumption, never observed history or · [reviewed contract](#b0011) |
| [B0012 · 76–76](../../../../../../include/crown/ir/update_pattern.hpp#L76) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns bool(data_) · [reviewed contract](#b0012) |
| [B0013 · 77–90](../../../../../../include/crown/ir/update_pattern.hpp#L77) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Views/pointers borrow this handle's storage; temporary-handle borrows are deleted. · [reviewed contract](#b0013) |
| [B0014 · 91–91](../../../../../../include/crown/ir/update_pattern.hpp#L91) | Callable definition: explicit Declaration(std::shared_ptr&lt;const detail::Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0014) |
| [B0015 · 92–94](../../../../../../include/crown/ir/update_pattern.hpp#L92) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::patterns · [reviewed contract](#b0015) |

## B0001

[Lines 1–21](../../../../../../include/crown/ir/update_pattern.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:2d57d11071111d84109a97deebc3a42b10d0aee3789ea75a45e3e19b7feb4d0a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the declaration API’s standard-library and compiler/resource forward declarations, then open the IR pattern namespace and name its private Data/Factory implementation types. |
| inputs / outputs | Includes provide fixed arrays, exceptions, shared ownership, spans, and caller-owned vectors; CompiledProgram and MemoryAccount remain forward declared. |
| invariants | The header states source-bound assumptions below planner ranking/runtime and adds no runtime implementation or dependency on those layers. |
| ownership | No object or account allocation occurs in this scaffolding block. |
| failure | There is no runtime failure path in includes or declarations. |
| cost | Compile-time declarations only; no runtime work or storage. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0002

[Lines 22–27](../../../../../../include/crown/ir/update_pattern.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L27:sha256:1d13f9dbcc8c6113b00836cdc4acdcdb16f4f7ae03ebf1c23194e7543b38281c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one requested per-table update assumption. |
| inputs / outputs | TableId, insertion_only flag, and raw fifo_scope ID enter as a value; equality compares all fields. |
| invariants | Insertion-only means no physical full-row lifetime ends; scope zero asks for no FIFO premise; equal positive IDs explicitly identify one joint scope. One value per table prevents inferred unions. |
| ownership | TableRule is an ordinary small value; Declaration later stores canonical copies in account-funded immutable data. |
| failure | No validation occurs in this aggregate type; declaration construction rejects unknown/duplicate table IDs. |
| cost | O(1) value construction and comparison; no allocation. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0003

[Lines 28–28](../../../../../../include/crown/ir/update_pattern.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:0946748ea040b3cf16fec8bb65d55817b05e221999f3939e4f5698e7492849b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clarify that logical Limits are distinct from the receiving MemoryAccount cap. |
| inputs / outputs | The adjacent Limits fields bound processing work, cells, and payload bytes; actual account capacity is independent. |
| invariants | Logical usage does not include allocator framing and cannot grant more account bytes. |
| ownership | No storage or owner is introduced by the comment. |
| failure | No failure path is introduced here; Factory reports logical limits separately from allocator failures. |
| cost | Documentation only; it prevents treating logical counters as a byte-cap substitute. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0004

[Lines 29–31](../../../../../../include/crown/ir/update_pattern.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L31:sha256:c8a7ef4298ca0d46553cfc8141df6883bf76ca791a4d6fa8e8976e37c194e8fd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set finite construction limits for declaration processing. |
| inputs / outputs | Defaults are 1,000,000 work units, 1,000,000 cells, and 16 MiB logical payload bytes. |
| invariants | Each dimension is independent; the receiving account still applies its own immutable actual-allocation cap. |
| ownership | Stack value copied by callers; no heap owner. |
| failure | The type itself does not reject values; budget checkpoints raise the corresponding Fault during construction. |
| cost | Three fixed-width counters; O(1) storage and initialization. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0005

[Lines 32–35](../../../../../../include/crown/ir/update_pattern.hpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L35:sha256:967311de66947aeb87e4daeeb712f399d28ce2b0a78cd4b62947f80adc919970
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the logical costs successfully charged to declaration construction. |
| inputs / outputs | Carries work, cells, payload_bytes; value equality permits exact grant/result comparisons. |
| invariants | Counters describe this API’s defined checkpoints and payload model, not CPU instructions or allocator framing. |
| ownership | Returned by value; no retained allocation. |
| failure | No failure path in the counter aggregate. |
| cost | O(1) value operations. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0006

[Lines 36–36](../../../../../../include/crown/ir/update_pattern.hpp#L36); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:1fef47accd644c096d0d28cb2ef98627df6f01de58b231a9d6298c5964e99a08
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the four declaration-processing rejection classes. |
| inputs / outputs | invalid_declaration covers malformed shape; work_limit, cell_limit, and byte_limit identify separate logical caps. |
| invariants | Fault is diagnostic category only and does not encode runtime monitoring status. |
| ownership | Enum value has no ownership. |
| failure | Failure transports one of these categories across the declaration boundary. |
| cost | O(1) enum storage. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0007

[Lines 37–37](../../../../../../include/crown/ir/update_pattern.hpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L37:sha256:1945d11eb87d55141a098205ce25e7ae52922774e0d94a08088b3f731d132383
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the fixed diagnostic boundary used by declaration construction. |
| inputs / outputs | Failure carries a Fault without constructing dynamic text. |
| invariants | The diagnostic message remains fixed and non-owning across the boundary. |
| ownership | No owned message buffer is allocated. |
| failure | The following Failure type may be thrown for invalid input or a logical grant stop. |
| cost | Fixed enum and static message; no dynamic formatting cost. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0008

[Lines 38–47](../../../../../../include/crown/ir/update_pattern.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L47:sha256:3b6e00014a0a96926ca027102b083fba1b8b8e98af0e47dff1477744f59f4f83
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transport a declaration Fault through the API without allocating diagnostic text. |
| inputs / outputs | Constructor stores the Fault; fault() returns it and what() returns a static message. |
| invariants | The object preserves the supplied category and never builds a per-error string. |
| ownership | No dynamic resource ownership. |
| failure | Construction failures throw this exception; it is not an allocation-failure translator. |
| cost | O(1) construction/access; fixed storage. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0009

[Lines 48–48](../../../../../../include/crown/ir/update_pattern.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L48:sha256:eeb48ba03225112e5fabf3a661c736966b4d9005e96cb9eea8839ce517cc41b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clarify that Record is an ordinary caller-owned interchange DTO, not runtime or proof authority. |
| inputs / outputs | The following struct contains a source digest, source-table count, and standard vector of rules. |
| invariants | Import must validate shape and later match the actual source; the DTO does not replay history. |
| ownership | Its vector is managed by the caller’s ordinary allocator, outside the query account. |
| failure | Ordinary vector allocation may throw; no query-cap guarantee is implied. |
| cost | O(R) if populated/exported; ordinary caller-owned storage. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0010

[Lines 49–53](../../../../../../include/crown/ir/update_pattern.hpp#L49); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L53:sha256:3b8c2c78c6890e57d44eaf2e84b0f19522990b5da13f42a3ea5e0cf61758cb00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the serializable declaration record shape. |
| inputs / outputs | Stores 64-character source SHA-256 bytes, source_tables, and std::vector&lt;TableRule&gt; rules. |
| invariants | The record preserves raw TableRule values and scope IDs; it does not contain derived scope groups or enforcement state. |
| ownership | The vector is ordinary caller-owned memory, unlike Declaration’s account-funded immutable storage. |
| failure | Allocation when building/exporting the vector may propagate std::bad_alloc; import validates values. |
| cost | O(R) retained vector cells for R rules. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0011

[Lines 54–75](../../../../../../include/crown/ir/update_pattern.hpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L75:sha256:778d7bca50358e943f35c0a8067c43b3a5cb177fc4c79a5a8d790f16b1e85c10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare capture, import, and explicit receiving-account copy operations for a source-bound requested assumption. |
| inputs / outputs | capture accepts an actual program and borrowed rules; import accepts Record or hash/table-count/rule span; copy_of accepts a validated handle and receiving account, with optional explicit limits. |
| invariants | Declaration remains requested metadata. Import checks shape, matches checks the actual source, ordinary copies share immutable storage. Two-argument copy_of requires caller logical pre-admission; the three-argument overload performs that admission before allocating. Span import avoids an ordinary decoder Record vector. |
| ownership | New captured/copied rule data is funded by the specified account; shared_ptr handle copies retain the original Data owner. |
| failure | Invalid source/shape and logical limits use Failure; the receiving account may independently reject allocation. |
| cost | Capture is O(R log R); copy_of is O(R); ordinary handle copy shares O(1) control/data ownership. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0012

[Lines 76–76](../../../../../../include/crown/ir/update_pattern.hpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L76:sha256:97dc45bb9885bdd0388f6f214da7c7b65592f7223005ba157410f3c56773a027
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whether a Declaration has a non-null immutable Data handle. |
| inputs / outputs | Converts to bool; true iff data_ is present. |
| invariants | A true handle says only that a value exists; it does not prove compatibility or enforcement. |
| ownership | Reads the handle’s shared ownership pointer without exporting it. |
| failure | Noexcept and no failure path. |
| cost | O(1), no allocation. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0013

[Lines 77–90](../../../../../../include/crown/ir/update_pattern.hpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L90:sha256:0fa0b411741be038b051fbe3ded9070aaf77b901fd3fd24b600d28526432df30
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose source binding, constraint presence, table count, recorded usage, and lvalue-only borrowed rule/hash views. |
| inputs / outputs | matches checks a CompiledProgram; inspectors return metadata; rules/find/source_sha256 return borrowed references or pointers from an lvalue handle, and rvalue overloads are deleted. |
| invariants | Empty handles yield false/zero/empty as implemented; matching includes digest and table count. Borrowed results require the Declaration to stay alive; rules are sorted by table. |
| ownership | Views point into immutable Data funded by its original MemoryAccount; a copied handle shares that owner. |
| failure | matches and scalar inspectors are noexcept; source_sha256 on empty handle throws Failure. No view may be obtained from a temporary handle. |
| cost | Scalar access O(1); find is O(log R); view creation O(1); no allocation. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |

## B0014

[Lines 91–91](../../../../../../include/crown/ir/update_pattern.hpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L91:sha256:d81abe443ab2097edc53e4bd247e2ef7753d41bb3d2116b073213f156b789654
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the private constructor used by Factory to wrap immutable declaration data. |
| inputs / outputs | Accepts shared_ptr&lt;const detail::Data&gt; and moves it into data_. |
| invariants | Only detail::Factory is a friend, so public callers cannot manufacture arbitrary Data handles. |
| ownership | Moving the shared_ptr transfers one handle reference while Data remains funded by its creating account. |
| failure | Noexcept; no new allocation. |
| cost | O(1) shared_ptr move. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0015

[Lines 92–94](../../../../../../include/crown/ir/update_pattern.hpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L94:sha256:2d2bb69818615475010d91a88cf46a7b345c97d07f91e877785c36d0cab90811
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the immutable declaration payload through shared ownership. |
| inputs / outputs | data_ points to const detail::Data or is empty for a default Declaration. |
| invariants | The Data object owns the sorted TableRule vector and source metadata; the handle stores no CapturedRule, scope_index, grouped-scope index, or row history. |
| ownership | The last shared_ptr release destroys the Data and its allocations under the original capture account. |
| failure | Empty handle is permitted; operations requiring a valid declaration reject it or return empty metadata as specified. |
| cost | O(1) handle storage; retained payload is O(R) cells. |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md) |
