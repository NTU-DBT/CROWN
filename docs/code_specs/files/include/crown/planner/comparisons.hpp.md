# `include/crown/planner/comparisons.hpp` — block usage map

[Source](../../../../../../include/crown/planner/comparisons.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare immutable opt-in exact comparison predicates and typed cold admission over genuine equality-CQ plans.

Snapshot SHA-256: `f3bdb0297d31bb4cfd5d1cae4c0f773e2911bfe8d5fbb3431769784cd27b8779`. 52 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [comparisons](../../../../subsystem_contracts.md#comparisons). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/comparisons.md](../../../../../comparisons.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/planner/comparisons.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../../include/crown/planner/comparisons.hpp#L11) | Type/record definition: enum class Operator |  · [reviewed contract](#b0002) |
| [B0003 · 12–12](../../../../../../include/crown/planner/comparisons.hpp#L12) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 13–13](../../../../../../include/crown/planner/comparisons.hpp#L13) | Type/record definition: struct Predicate |  · [reviewed contract](#b0004) |
| [B0005 · 14–14](../../../../../../include/crown/planner/comparisons.hpp#L14) | Type/record definition: struct Limits |  · [reviewed contract](#b0005) |
| [B0006 · 15–19](../../../../../../include/crown/planner/comparisons.hpp#L15) | Explanatory comments or spacing. | source comment (unverified): // Cold opt-in comparison metadata over a genuine direct exact-set CQ plan. · [reviewed contract](#b0006) |
| [B0007 · 20–36](../../../../../../include/crown/planner/comparisons.hpp#L20) | Type/record definition: class Plan | returns *this; source comment (unverified): // Cold opt-in comparison metadata over a genuine direct exact-set CQ plan. · [reviewed contract](#b0007) |
| [B0008 · 37–52](../../../../../../include/crown/planner/comparisons.hpp#L37) | declares values/defaults or compile-time conditions. | source comment (unverified): // Every variable operand must occur in an original query atom. Both operands · [reviewed contract](#b0008) |

## B0001

[Lines 1–10](../../../../../../include/crown/planner/comparisons.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:20106cabce55a05ad9d020737e7c8e10981b8f793510c724a40cbc5ce0d24d58
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the genuine physical-plan, scalar, ownership and span vocabulary for explicit comparison admission. |
| inputs / outputs | Header guard/includes and comparisons namespace; no executable input/output. |
| invariants | Uses existing exact non-null direct-CQ types; no SQL parser, expression coercion or runtime backend is installed by inclusion. |
| ownership | Declares no owner in this scaffolding. |
| failure | Compile errors remain ordinary compiler failures; no runtime catch. |
| cost | Compile-time declarations only. |
| Design | [include/crown/planner/comparisons.hpp](../../../../../../include/crown/planner/comparisons.hpp), [include/crown/ir/physical.hpp](../../../../../../include/crown/ir/physical.hpp), [docs/comparisons.md](../../../../../comparisons.md) |

## B0002

[Lines 11–11](../../../../../../include/crown/planner/comparisons.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L11:sha256:c0d68cce0f41ad909eb2907eb2be23953406c7475079f4185c3fccf85766ade1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the six explicit exact comparison operations. |
| inputs / outputs | Scoped Operator enum identifies equality, inequality and four order predicates. |
| invariants | Enumerator identity is separate from CQ equality classes; forged values still require admit validation. |
| ownership | Inline enum value; no borrowed payload. |
| failure | Invalid enum values are rejected by admission, not repaired or defaulted. |
| cost | Fixed-size value. |
| Design | [include/crown/planner/comparisons.hpp](../../../../../../include/crown/planner/comparisons.hpp), [src/planner/comparisons.cpp](../../../../../../src/planner/comparisons.cpp), [docs/comparisons.md](../../../../../comparisons.md) |

## B0003

[Lines 12–12](../../../../../../include/crown/planner/comparisons.hpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L12:sha256:cbeebfe504549f125da79d4c9b43c0b4e9d10e7747ca9c5178e68c82f852faa1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a comparison operand as one original variable ID or an exact scalar literal. |
| inputs / outputs | Operand aliases variant&lt;VariableId,Value&gt;. |
| invariants | No SQL NULL or parameter alternative exists. Value retains its existing exact scalar domain. |
| ownership | Variable ID is inline; literal string/decimal ownership is ordinary caller/compiler ownership until copied. |
| failure | Valueless variants are refused by admission; variant allocation failures follow ordinary C++ ownership. |
| cost | Fixed descriptor plus literal payload-copy cost. |
| Design | [include/crown/planner/comparisons.hpp](../../../../../../include/crown/planner/comparisons.hpp), [include/crown/ir/model.hpp](../../../../../../include/crown/ir/model.hpp), [src/planner/comparisons.cpp](../../../../../../src/planner/comparisons.cpp) |

## B0004

[Lines 13–13](../../../../../../include/crown/planner/comparisons.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:59a99d65d8124e8a771b12c8254aef8bd067d6559fb1b45c675b0c91bd8798b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep a complete binary predicate separate from its original CQ. |
| inputs / outputs | Two Operand values and an Operator form one conjunction member. |
| invariants | Operand order is semantic for strict/non-strict order; no swapping or equality merging occurs. |
| ownership | Public mutable caller DTO owns its literals; admitted Plan copies them. |
| failure | Construction alone is no admission; admit checks all values. |
| cost | Two operand descriptors and their scalar payloads. |
| Design | [include/crown/planner/comparisons.hpp](../../../../../../include/crown/planner/comparisons.hpp), [src/planner/comparisons.cpp](../../../../../../src/planner/comparisons.cpp) |

## B0005

[Lines 14–14](../../../../../../include/crown/planner/comparisons.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L14:sha256:184f88169a96299282f8d339209b46b0c6bfecbfa6efb21b26f4b1379db75a3e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare one finite selected admission-work balance. |
| inputs / outputs | Limits.work defaults to 1,000,000 selected units. |
| invariants | Zero grants no entry step. No nested operand gets a fresh limit; this is not a memory or elapsed-time cap. |
| ownership | Inline caller policy value copied into the cold builder. |
| failure | Exhaustion is comparison_work_limit. |
| cost | Fixed policy descriptor; actual builder charges remain explicit. |
| Design | [include/crown/planner/comparisons.hpp](../../../../../../include/crown/planner/comparisons.hpp), [src/planner/comparisons.cpp](../../../../../../src/planner/comparisons.cpp) |

## B0006

[Lines 15–19](../../../../../../include/crown/planner/comparisons.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L19:sha256:95c9fdbde215925e86ae972ef08d73098bb4657ca1566fbe574260cd09fb17c1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the cold compiler ownership and conjunction/provenance boundary. |
| inputs / outputs | Comment-only introduction to Plan. |
| invariants | Ordinary immutable compiler metadata does not supply native receiving-account storage automatically; runtime must freeze it. |
| ownership | Caller literals are copied by the following admitted owner. |
| failure | No executable branch or passing receipt. |
| cost | No runtime work from comments. |
| Design | [include/crown/planner/comparisons.hpp](../../../../../../include/crown/planner/comparisons.hpp), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../../comparisons.md) |

## B0007

[Lines 20–36](../../../../../../include/crown/planner/comparisons.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L36:sha256:cf5d77cffaf0d22b0a58d52e7b6343779dd67b2eea74c686db3878d60e14fa7b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose immutable admitted comparison metadata with lifetime-safe borrowed accessors. |
| inputs / outputs | Private shared-const Data construction; general(), predicates() and work() expose original plan, conjunction and spent work. |
| invariants | Only admit constructs Plan. Copies/moves retain shared Data and leave both handles valid. Borrowing general/predicates from rvalues is deleted. No default empty Plan or mutable predicate span is exposed. |
| ownership | Shared compiler owner retains the genuine PhysicalPlan handle and copied literal DTOs; spans/references borrow the live Plan. |
| failure | Valid copies/moves/getters are noexcept. Final owner destruction can release the compiler graph; no runtime publication or exception wrapper. |
| cost | O(1) handle copy/getter/move; final shared-owner teardown has graph/payload destruction costs. |
| Design | [include/crown/planner/comparisons.hpp](../../../../../../include/crown/planner/comparisons.hpp), [src/planner/comparisons.cpp](../../../../../../src/planner/comparisons.cpp), [docs/comparisons.md](../../../../../comparisons.md) |

## B0008

[Lines 37–52](../../../../../../include/crown/planner/comparisons.hpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L52:sha256:6cddd5eed08bdf630f72530e8338a1681ab32d011ca551273ae0e48b73e017f8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare exact direct-CQ comparison admission and its honest resource/profile contract. |
| inputs / outputs | Genuine PhysicalPlan, predicate span and Limits in; immutable Plan out. |
| invariants | All variable operands occur in original atoms, both operands share ScalarType, all six operations and constant/contradictory routes are allowed, and an empty conjunction is true. Original equality-only plan/proof/profile remains unchanged. |
| ownership | Input DTOs and source plan survive refusal; admitted predicates are independent compiler-owned copies requiring runtime freeze. |
| failure | Unsupported normalized SQL/predicates use comparison_admission; selected work exhaustion uses comparison_work_limit. Inherited invalid-plan and allocation failures keep their original boundaries. |
| cost | Entry, variable slots, atom/term, predicate/operand and literal-string-byte charges are shared; allocation, inherited validation and bounded Date/Decimal copies remain additional cold costs. |
| Design | [include/crown/planner/comparisons.hpp](../../../../../../include/crown/planner/comparisons.hpp), [src/planner/comparisons.cpp](../../../../../../src/planner/comparisons.cpp), [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md) |
