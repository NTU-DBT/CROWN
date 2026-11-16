# `include/crown/planner/difference.hpp` — block usage map

[Source](../../../../../../include/crown/planner/difference.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare explicit set/bag difference admission, immutable positive operands, actual structural profiles and advisory residual bounds.

Snapshot SHA-256: `3c9183667f690351c7e97d202e1fdeed3d60e7b0b49acf26e3b7f7acb7e5b9ee`. 82 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [difference](../../../../subsystem_contracts.md#difference). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/difference.md](../../../../../difference.md), [docs/source_images.md](../../../../../source_images.md), [docs/annotations.md](../../../../../annotations.md), [Refactor.md](../../../../../../Refactor.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/planner/difference.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../../include/crown/planner/difference.hpp#L13) | Type/record definition: enum class Mode |  · [reviewed contract](#b0002) |
| [B0003 · 14–30](../../../../../../include/crown/planner/difference.hpp#L14) | Type/record definition: struct Profile |  · [reviewed contract](#b0003) |
| [B0004 · 31–39](../../../../../../include/crown/planner/difference.hpp#L31) | Type/record definition: struct Estimates | source comment (unverified): // Committed logical rows and compressed residual keys, not peak bytes. · [reviewed contract](#b0004) |
| [B0005 · 40–43](../../../../../../include/crown/planner/difference.hpp#L40) | Type/record definition: struct Limits | source comment (unverified): // Pair entry and positional head checks only. · [reviewed contract](#b0005) |
| [B0006 · 44–47](../../../../../../include/crown/planner/difference.hpp#L44) | Explanatory comments or spacing. | source comment (unverified): // Immutable explicit difference between two positive classical CQ operands. · [reviewed contract](#b0006) |
| [B0007 · 48–69](../../../../../../include/crown/planner/difference.hpp#L48) | Type/record definition: class Plan | returns *this; source comment (unverified): // Immutable explicit difference between two positive classical CQ operands. · [reviewed contract](#b0007) |
| [B0008 · 70–82](../../../../../../include/crown/planner/difference.hpp#L70) | declares values/defaults or compile-time conditions. | source comment (unverified): // Compare ordered output positions by ScalarType; aliases/variable IDs may · [reviewed contract](#b0008) |

## B0001

[Lines 1–12](../../../../../../include/crown/planner/difference.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:43e190f8c1c408f14c95aedbd65cc821b30eeafb6c51654ae202f8dde76d543d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare cold difference admission dependencies and namespace. |
| inputs / outputs | Idempotent header imports checked multiplicity policy, fallback plans and standard immutable metadata types. |
| invariants | Includes/namespace declarations select no runtime or theorem. MultiplicityPolicy contributes its named checked arithmetic contract. |
| ownership | Compile-time declarations create no native account or source owner. |
| failure | Compilation and included-definition errors retain normal compiler/API boundaries. |
| cost | Compilation dependencies only; no per-update action. |
| Design | [include/crown/planner/difference.hpp](../../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../../Refactor.md), [docs/fallback.md](../../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |

## B0002

[Lines 13–13](../../../../../../include/crown/planner/difference.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:c627ae5310053cec5ec5763777e6405214a140154bf2f73006305c1a27e5f074
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the literal set or bag subtraction meaning. |
| inputs / outputs | Mode is set_except or bag_except_all; invalid cast values are refused by admit. |
| invariants | Set means left positive/right absent; bag means nonnegative residual count. Neither mode denotes aggregate payload subtraction. |
| ownership | One inline enum value is copied into immutable profile metadata. |
| failure | This declaration cannot refuse; the cold admit checks values. |
| cost | Fixed enum storage and comparisons. |
| Design | [include/crown/planner/difference.hpp](../../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../../Refactor.md), [docs/fallback.md](../../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |

## B0003

[Lines 14–30](../../../../../../include/crown/planner/difference.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L30:sha256:30589433209b83410be0be50d342f808f54bd19c6d443f6366e38613c2a7a541
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the difference semantics, changed guarantee and actual operand classes. |
| inputs / outputs | Profile contains mode, fixed descriptive labels, two QueryClasses and two genuine fallback reasons. |
| invariants | Input rows remain physical sets. Compressed result multiplicity and exact endpoint before/after replacements are separate from aggregate signed payload changes; no CROWN/GHD/P11 certificate or constant-delay claim is made. |
| ownership | Inline enums and static string_views own no mutable source state; containing immutable Plan or runtime Binding retains the profile. |
| failure | Profile defaults are descriptive; admit replaces mode/semantics/classes/reasons before publication. |
| cost | Fixed metadata copying plus any explicit diagnostic serialization; no evaluation occurs here. |
| Design | [include/crown/planner/difference.hpp](../../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../../Refactor.md), [docs/fallback.md](../../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |

## B0004

[Lines 31–39](../../../../../../include/crown/planner/difference.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L39:sha256:a61d5e6ea9f59da13ea85f4cd5205591a666fac8f9ba810c951b3adbb709d40b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe advisory operand, residual-key, residual-multiplicity and committed-row bounds. |
| inputs / outputs | Two fallback estimates and optional uint64 source/key/multiplicity/state bounds accompany overflow/advisory flags. |
| invariants | Upper bounds are not subtracted from each other. Source rows count each physical table once. State excludes simultaneous images, operand maps, journal and old/new scratch, so it is not peak memory. |
| ownership | Cold ordinary DTO values belong to their caller, outside retained native state. |
| failure | Overflow is represented by missing bounds plus overflow=true, never wrapped integers or a successful resource grant. |
| cost | Fixed result fields; computing estimates additionally scans provided source counts and original atom occurrences. |
| Design | [include/crown/planner/difference.hpp](../../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../../Refactor.md), [docs/fallback.md](../../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |

## B0005

[Lines 40–43](../../../../../../include/crown/planner/difference.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L43:sha256:69dc13d1896e5b1eb0767a8a8455ce8f77acd47b8b0242ec0d18ec5f04cf4aee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep pair compatibility work separate from each operand cold admission grant. |
| inputs / outputs | work defaults to one million; left/right each carry metadata, recognition and lowering limits. |
| invariants | Pair work counts entry and each positional head check. It does not replenish or merge operand grants and does not represent runtime recomputation work. |
| ownership | Caller-owned fixed limit DTO; no source account or lease. |
| failure | Exhausted selected admission becomes difference_work_limit in admit; allocation retains its native type. |
| cost | Fixed configuration storage; actual operand validation/copy/lowering costs remain separate. |
| Design | [include/crown/planner/difference.hpp](../../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../../Refactor.md), [docs/fallback.md](../../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |

## B0006

[Lines 44–47](../../../../../../include/crown/planner/difference.hpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L47:sha256:97fb11dbca8d80181d61a3d2001789c7e61807ac8f181c0a4c4de66b8aa561ea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the cold composition and single execution-owner boundary. |
| inputs / outputs | The note describes two positive classical operand Plans admitted from identical Catalog/options. |
| invariants | Copying/lowering happens for both cold operands. Runtime must instantiate only source_only(), never two independently committed source owners. |
| ownership | Documentation creates no owner; the following Plan shares immutable cold Data. |
| failure | The note does not enforce runtime publication; follow the runtime contract. |
| cost | No executable work; explicitly records duplicated cold work. |
| Design | [include/crown/planner/difference.hpp](../../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../../Refactor.md), [docs/fallback.md](../../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |

## B0007

[Lines 48–69](../../../../../../include/crown/planner/difference.hpp#L48); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L69:sha256:8f5578bff305271edc58febe321d5d77b40c58eaf1c9ee7f209b002dc0995674
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable original operands and their one selected source coordinator. |
| inputs / outputs | Plan exposes lvalue-only left/right/source_only/profile borrows, pair work and explicit estimates; only admit can construct Data. |
| invariants | Both operands arise from the same catalog/options. Move copies the shared immutable handle, preserving valid provenance in both objects. source_only is left source coordination, not original difference proof. |
| ownership | shared_ptr&lt;const Data&gt; retains both cold fallback Plans and profile. Borrowed references require their Plan ownership to survive; runtime must freeze execution metadata under its own original account. |
| failure | No default/foreign constructor is public. Copy/move/getters are noexcept; estimates/admit expose their explicit failure boundaries. |
| cost | Fixed handle copy/refcount work and retained cold DTO metadata; no sources or query execution. |
| Design | [include/crown/planner/difference.hpp](../../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../../Refactor.md), [docs/fallback.md](../../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |

## B0008

[Lines 70–82](../../../../../../include/crown/planner/difference.hpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L82:sha256:6478d3b53b2d7243383d2dbc112dd0a9ae43eee967a2e5e825f72511f0808ce9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare explicit positional admission and its set/bag/value-domain contract. |
| inputs / outputs | admit receives one Catalog, two Queries, Mode, common PhysicalOptions and separate pair/operand Limits, returning immutable Plan. |
| invariants | Head positions share ScalarType while names/IDs may differ. Canonical decimal values compare without SQL coercion; residual rows retain left layout. Queries contain positive CQ terms only, so recursion/negation/difference cycles cannot enter. Physical duplicate insertion remains a set no-op. |
| ownership | Cold compiler DTOs are copied via fallback admission; returned Plan owns immutable cold metadata. Runtime source state is not created here. |
| failure | Invalid mode/shape/types/operand admission use difference_admission; selected work refusal uses difference_work_limit; native allocation failures propagate. |
| cost | Two complete cold operand admissions plus bounded positional checks. No SQL grammar, automatic routing or dynamic maintenance theorem is supplied. |
| Design | [include/crown/planner/difference.hpp](../../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../../Refactor.md), [docs/fallback.md](../../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |
