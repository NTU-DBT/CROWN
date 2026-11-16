# `src/planner/difference.cpp` — block usage map

[Source](../../../../../src/planner/difference.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit both original operands over the same catalog and check ordered output types without subtracting unrelated upper bounds.

Snapshot SHA-256: `2dd4848a08389fb58d8c00750b375e0d98518c1ca15a399774b8ebcc92f14da4`. 75 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [difference](../../../subsystem_contracts.md#difference). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/difference.md](../../../../difference.md), [docs/source_images.md](../../../../source_images.md), [docs/annotations.md](../../../../annotations.md), [Refactor.md](../../../../../Refactor.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/planner/difference.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–13](../../../../../src/planner/difference.cpp#L7) | Type/record definition: struct Budget |  · [reviewed contract](#b0002) |
| [B0003 · 14–16](../../../../../src/planner/difference.cpp#L14) | Callable definition: void require(bool condition, const char* message) | calls Error; guard void require(bool condition, const char* message) { · [reviewed contract](#b0003) |
| [B0004 · 17–18](../../../../../src/planner/difference.cpp#L17) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 19–23](../../../../../src/planner/difference.cpp#L19) | Type/record definition: struct Plan::Data |  · [reviewed contract](#b0005) |
| [B0006 · 24–24](../../../../../src/planner/difference.cpp#L24) | Callable definition: const fallback::Plan& Plan::left() const & noexcept | calls ; returns data_-&gt;left · [reviewed contract](#b0006) |
| [B0007 · 25–25](../../../../../src/planner/difference.cpp#L25) | Callable definition: const fallback::Plan& Plan::right() const & noexcept | calls ; returns data_-&gt;right · [reviewed contract](#b0007) |
| [B0008 · 26–26](../../../../../src/planner/difference.cpp#L26) | Callable definition: const PhysicalPlan& Plan::source_only() const & noexcept | calls source_only; returns data_-&gt;left.source_only() · [reviewed contract](#b0008) |
| [B0009 · 27–27](../../../../../src/planner/difference.cpp#L27) | Callable definition: const Profile& Plan::profile() const & noexcept | calls ; returns data_-&gt;profile · [reviewed contract](#b0009) |
| [B0010 · 28–28](../../../../../src/planner/difference.cpp#L28) | Callable definition: std::uint64_t Plan::work() const noexcept | calls ; returns data_-&gt;work · [reviewed contract](#b0010) |
| [B0011 · 29–29](../../../../../src/planner/difference.cpp#L29) | Explanatory comments or spacing. |  |
| [B0012 · 30–47](../../../../../src/planner/difference.cpp#L30) | Callable definition: Estimates Plan::estimates(std::span&lt;const std::uint64_t&gt; tablecounts) const | calls require, size, originalcatalog, estimates; guard require(tablecounts.size() == data_-&gt;left.originalcatalog().tables.size(),; returns result · [reviewed contract](#b0012) |
| [B0013 · 48–48](../../../../../src/planner/difference.cpp#L48) | Explanatory comments or spacing. |  |
| [B0014 · 49–74](../../../../../src/planner/difference.cpp#L49) | Callable definition: Plan admit(const Catalog& catalog, const Query& leftquery, const Query& rightquery, Mode mode, const PhysicalOptions& options, co… | calls require, take, fallback::admit, query; guard require(mode == Mode::set_except \|\| mode == Mode::bag_except_all, "unknown difference mode");; returns Plan(std::make_shared&lt;Plan::Data&gt;(Plan::Data{std::move(left), std::move(right), profile, budget.use…; growth make_shared; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 75–75](../../../../../src/planner/difference.cpp#L75) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::difference · [reviewed contract](#b0015) |

## B0001

[Lines 1–6](../../../../../src/planner/difference.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:7ab89916b53eb3c75083b32673451995cbd1053ca9b99ad38921d146c0eb7a73
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the difference admission implementation in its dedicated namespace. |
| inputs / outputs | Public difference declarations, owning Error and uint64 limits are available to implementation-local helpers. |
| invariants | The anonymous helper namespace changes linkage only; no source runtime or shared global query state is constructed. |
| ownership | Imports and namespace declarations have no native owning allocation. |
| failure | Compilation/included API failures retain their normal boundaries. |
| cost | Compile/link dependency work only. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0002

[Lines 7–13](../../../../../src/planner/difference.cpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L13:sha256:82e3fce44b29da1ea0cd461f0c949bbef1c85a2b7a682a84286bb54f71844ef9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge one cumulative selected pair-admission balance. |
| inputs / outputs | Budget holds remaining/used uint64; take spends one unit or throws difference_work_limit. |
| invariants | The zero guard precedes decrement; used never exceeds the original limit, so increment cannot wrap. No per-head reset occurs. |
| ownership | Stack-local cold scalar counters; no runtime account or observer. |
| failure | Exhaustion throws before the guarded positional check; partial cold values unwind through RAII. |
| cost | One check/decrement/increment per admitted unit; exception construction only on refusal. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0003

[Lines 14–16](../../../../../src/planner/difference.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L16:sha256:5ac5a0e53c83800ff3bb7ebad6f3fd16d4b2a4b6e81cbf07dcb34322162597dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Refuse a malformed cold difference condition with its own domain. |
| inputs / outputs | Boolean and static diagnostic message either return or throw owning Error(difference_admission). |
| invariants | This helper supplies no runtime retry, rollback journal or source mutation. |
| ownership | Diagnostic strings use ordinary cold exception ownership. |
| failure | The false branch propagates through the single admit translation boundary or directly from estimates. |
| cost | One condition branch and failure-only diagnostic allocation. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0004

[Lines 17–18](../../../../../src/planner/difference.cpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L18:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the implementation-private helper namespace. |
| inputs / outputs | Lexical terminator precedes the immutable Plan::Data definition. |
| invariants | Helpers retain translation-unit-local linkage; Plan member definitions follow in the public difference namespace. |
| ownership | No value/owner is created by the scope boundary. |
| failure | No executable failure path. |
| cost | No runtime work. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0005

[Lines 19–23](../../../../../src/planner/difference.cpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L23:sha256:7358ea607da12fc2a601150b30a0c00d232e8a194ccafb1d5567b98e9bf3ce73
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the admitted pair and descriptive difference profile. |
| inputs / outputs | Data stores left/right fallback Plans, Profile and selected pair work. |
| invariants | Both Plans are produced in one admit call from identical original Catalog/options. The right source plan remains cold metadata and must not create another execution owner. |
| ownership | Immutable shared Data owns two cold plan handles; those own their Catalog/Query/PhysicalPlan metadata. |
| failure | Data publishes only after both admissions and compatibility checks; allocation failure leaves no visible Plan. |
| cost | Fixed pair/profile fields plus both retained operand DTO graphs; no physical source data. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0006

[Lines 24–24](../../../../../src/planner/difference.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:a82c72959cb1b3590e2337870e62ee2d51c3b68e861a01e1b20fdba491023c10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the validated original left operand from a retained Plan. |
| inputs / outputs | Return data_-&gt;left by const lvalue reference. |
| invariants | No copying, validation or new execution authority is produced. The caller retains Plan ownership while borrowing. |
| ownership | Reference borrows immutable shared Data. |
| failure | Valid privately constructed Plan makes this noexcept getter nonfailing. |
| cost | One pointer/member access. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0007

[Lines 25–25](../../../../../src/planner/difference.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L25:sha256:e59449872c7782eb08a506b1b31dcda5c7de4b4cd6afd70c988e7107aadbcaa4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the validated original right operand from a retained Plan. |
| inputs / outputs | Return data_-&gt;right by const lvalue reference. |
| invariants | The right operand shares the admitted catalog/options provenance but is not an independent live source owner. |
| ownership | Reference borrows immutable shared Data. |
| failure | Valid privately constructed Plan makes this noexcept getter nonfailing. |
| cost | One pointer/member access. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0008

[Lines 26–26](../../../../../src/planner/difference.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:759d9d23f97a6bcedfe584d32e6bbbabfaadd08a74c7ee37c3771723e6765fa6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the single genuine source-only coordinator plan. |
| inputs / outputs | Return the left fallback Plan source_only() by const lvalue reference. |
| invariants | Both operands were admitted from identical catalog/options; this empty-query coordinator covers every original source/constraint. Its identity/certificate does not describe the original difference. |
| ownership | Reference borrows the left cold plan retained by shared Data. |
| failure | No allocation or runtime preparation; noexcept inherited getter. |
| cost | Fixed nested pointer/member access; no source scan. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0009

[Lines 27–27](../../../../../src/planner/difference.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:51ec5e81fec7c19d8303525d5e9f74df9823b66ab94524c644aca7d6cc58c801
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the immutable difference guarantee profile. |
| inputs / outputs | Return data_-&gt;profile by const lvalue reference. |
| invariants | Mode, semantics and both original structural classes/reasons reflect successful admit, not an original-query proof. |
| ownership | Reference borrows shared Data lifetime. |
| failure | Noexcept getter on a privately constructed valid Plan. |
| cost | Fixed pointer/member access. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0010

[Lines 28–28](../../../../../src/planner/difference.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:37eaf0d09ce2f0e5205c069fc6e63fa9e3ff5c684ff694835880e5116cfa43b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report selected pair compatibility work. |
| inputs / outputs | Return Data.work counted by pair Budget. |
| invariants | This excludes both fallback metadata/recognition/lowering costs and all runtime work; left/right retain their own work observations. |
| ownership | Copied inline uint64 value, no borrow after return. |
| failure | Noexcept getter. |
| cost | Fixed scalar load. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0012

[Lines 30–47](../../../../../src/planner/difference.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L47:sha256:7d2c0052a6dbb2fefe9b937cbcb6318501b58167e0d5919c26225b830d4a1d08
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute conservative difference bounds without subtracting incompatible upper bounds. |
| inputs / outputs | One count per physical table yields both operand fallback estimates, shared source rows, left-bounded residual key/multiplicity bounds and checked source-plus-key state rows. |
| invariants | For set mode total residual units cannot exceed distinct left keys; bag mode total residual multiplicity cannot exceed left complete assignments. Right bounds never reduce a left bound. Nullopt and overflow preserve unknowns; committed-row bounds exclude private peak scratch. |
| ownership | Caller-provided counts are borrowed only during this cold observation. Returned Estimates owns ordinary scalar DTOs. |
| failure | Wrong count-vector arity throws difference_admission. Underlying bounded integer products/sums report unknown; final state addition tests overflow before computing. |
| cost | Two inherited per-physical-source/per-occurrence estimate scans plus fixed optional arithmetic; no database scan, query evaluation or source state change. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0014

[Lines 49–74](../../../../../src/planner/difference.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L74:sha256:c328065e4216b321643cc779e93adc71ce2b9b08fe24a1576ff4548121593423
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit two positive CQ operands under explicit positional set/bag semantics. |
| inputs / outputs | Catalog, left/right Query, valid Mode, common options and Limits produce immutable Data with two checked fallback Plans, original classes/reasons and selected pair work. |
| invariants | Check mode, fund pair entry, admit both operands, require equal head arity and matching ordered ScalarTypes, then publish. Query validation proves head indices before indexed type reads. Decimal precision/scale can differ because residual rows always come from the left and equality is exact scalar-domain equality. No negative/recursive nodes exist in Query. |
| ownership | Private cold Plans/strings/copies use ordinary compiler ownership until one shared immutable Data is published. There is no native source owner or query memory account here. |
| failure | One outer Error boundary preserves difference categories, translates inherited selected resource failures to difference_work_limit and other typed admission errors to difference_admission. Memory/native allocation exceptions are not caught; private RAII values unwind. |
| cost | Two full cold metadata/validation/recognition/lowering passes and catalog/query copies, plus one pair unit per output position. No runtime catch layer, maintenance state or specialized theorem is added. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0015

[Lines 75–75](../../../../../src/planner/difference.cpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L75:sha256:0a9ff0a8e3fb6fa770c65f629733b69bf1abe12ab1173b011c46769a46641792
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the dedicated difference planner namespace. |
| inputs / outputs | Lexical scope terminates after immutable accessors, estimates and admission. |
| invariants | No initializer, publication or additional validation occurs. |
| ownership | No owner is created or transferred. |
| failure | No executable failure path. |
| cost | No runtime work. |
| Design | [src/planner/difference.cpp](../../../../../src/planner/difference.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |
