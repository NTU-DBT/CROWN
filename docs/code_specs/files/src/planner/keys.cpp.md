# `src/planner/keys.cpp` — block usage map

[Source](../../../../../src/planner/keys.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Prove sequential enforced-FK parent elimination, compact query IDs and lower a separately certified reduced plan without changing the source constraint owner.

Snapshot SHA-256: `1be9b255a555537649babde8be159291f505e96169c2dbfd3a19529de26a1183`. 187 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [keys](../../../subsystem_contracts.md#keys). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/key_specialization.md](../../../../key_specialization.md), [Refactor.md](../../../../../Refactor.md), [docs/catalog.md](../../../../catalog.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/planner_proofs.md](../../../../planner_proofs.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/planner/keys.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // One cold guard balance covers all candidates and the final ID mapping. · [reviewed contract](#b0001) |
| [B0002 · 8–14](../../../../../src/planner/keys.cpp#L8) | Type/record definition: struct Budget | source comment (unverified): // One cold guard balance covers all candidates and the final ID mapping. · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../src/planner/keys.cpp#L15) | Explanatory comments or spacing. |  |
| [B0004 · 16–23](../../../../../src/planner/keys.cpp#L16) | Callable definition: bool same_term(const Term& a, const Term& b, Budget& budget) | calls take; returns std::get_if&lt;VariableId&gt;(&b) && *variable == std::get&lt;VariableId&gt;(b); std::get_if&lt;Value&gt;(&b) && *val…; source comment (unverified): // Two ignored fields do not establish equality. · [reviewed contract](#b0004) |
| [B0005 · 24–26](../../../../../src/planner/keys.cpp#L24) | Explanatory comments or spacing. | source comment (unverified): // F01 validates the catalog; replay the exact enforced-key premise rather than · [reviewed contract](#b0005) |
| [B0006 · 27–46](../../../../../src/planner/keys.cpp#L27) | Callable definition: std::optional&lt;std::size_t&gt; target_key(const Table& table, const ForeignKeyConstraint& foreign, Budget& budget) | calls size, take; returns i; {}; 3 loop sites; source comment (unverified): // F01 validates the catalog; replay the exact enforced-key premise rather than · [reviewed contract](#b0006) |
| [B0007 · 47–49](../../../../../src/planner/keys.cpp#L47) | Explanatory comments or spacing. | source comment (unverified): // The FK witness fixes every matched key value. Other parent fields impose no · [reviewed contract](#b0007) |
| [B0008 · 50–67](../../../../../src/planner/keys.cpp#L50) | Callable definition: bool entailed(const Atom& source, const Atom& parent, const ForeignKeyConstraint& foreign, const std::vector&lt;std::size_t&gt;& uses, … | calls size, same_term, take; returns false; false; 3 loop sites; source comment (unverified): // The FK witness fixes every matched key value. Other parent fields impose no · [reviewed contract](#b0008) |
| [B0009 · 68–69](../../../../../src/planner/keys.cpp#L68) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 70–78](../../../../../src/planner/keys.cpp#L70) | Type/record definition: struct Plan::Data |  · [reviewed contract](#b0010) |
| [B0011 · 79–79](../../../../../src/planner/keys.cpp#L79) | Explanatory comments or spacing. |  |
| [B0012 · 80–80](../../../../../src/planner/keys.cpp#L80) | Callable definition: const PhysicalPlan& Plan::general() const & noexcept | calls ; returns data_-&gt;general · [reviewed contract](#b0012) |
| [B0013 · 81–81](../../../../../src/planner/keys.cpp#L81) | Callable definition: const PhysicalPlan& Plan::execution() const & noexcept | calls ; returns data_-&gt;execution · [reviewed contract](#b0013) |
| [B0014 · 82–82](../../../../../src/planner/keys.cpp#L82) | Callable definition: Reason Plan::reason() const noexcept | calls ; returns data_-&gt;reason · [reviewed contract](#b0014) |
| [B0015 · 83–83](../../../../../src/planner/keys.cpp#L83) | Callable definition: bool Plan::specialized() const noexcept | calls reason; returns reason() == Reason::specialized · [reviewed contract](#b0015) |
| [B0016 · 84–84](../../../../../src/planner/keys.cpp#L84) | Callable definition: std::span&lt;const Elimination&gt; Plan::eliminations() const & noexcept | calls ; returns data_-&gt;eliminations · [reviewed contract](#b0016) |
| [B0017 · 85–85](../../../../../src/planner/keys.cpp#L85) | Callable definition: std::span&lt;const OccurrenceId&gt; Plan::occurrences() const & noexcept | calls ; returns data_-&gt;occurrences · [reviewed contract](#b0017) |
| [B0018 · 86–86](../../../../../src/planner/keys.cpp#L86) | Callable definition: std::span&lt;const VariableId&gt; Plan::variables() const & noexcept | calls ; returns data_-&gt;variables · [reviewed contract](#b0018) |
| [B0019 · 87–87](../../../../../src/planner/keys.cpp#L87) | Callable definition: const Usage& Plan::usage() const & noexcept | calls ; returns data_-&gt;usage · [reviewed contract](#b0019) |
| [B0020 · 88–88](../../../../../src/planner/keys.cpp#L88) | Callable definition: const std::optional&lt;HeightCertificate&gt;& Plan::reduced_certificate() const & noexcept | calls ; returns data_-&gt;certificate · [reviewed contract](#b0020) |
| [B0021 · 89–89](../../../../../src/planner/keys.cpp#L89) | Explanatory comments or spacing. |  |
| [B0022 · 90–186](../../../../../src/planner/keys.cpp#L90) | Callable definition: Plan specialize(const PhysicalPlan& general, const Limits& limits) | calls take, query, catalog, live; returns Plan(std::make_shared&lt;Plan::Data&gt;(Plan::Data{general, std::move(execution), reason,; growth make_shared, push_back; 12 loop sites; source comment (unverified): // Every removal uses a different still-live occurrence. Updating use counts · [reviewed contract](#b0022) |
| [B0023 · 187–187](../../../../../src/planner/keys.cpp#L187) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::keys · [reviewed contract](#b0023) |

## B0001

[Lines 1–7](../../../../../src/planner/keys.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:eda618014adc37c80f153e563b3e6016791c8cc20ec75a731ca17487c0aacc1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the private key-rewrite implementation in its own planner namespace. |
| inputs / outputs | Include public keys declarations and existing Error; open private helper scope. |
| invariants | No global mutable rewrite state, cache, query owner or update hook is initialized. |
| ownership | Compile-time includes and namespaces; helpers own only per-call locals. |
| failure | Ordinary compilation errors remain at the tool boundary. |
| cost | Compilation/scaffolding only. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0002

[Lines 8–14](../../../../../src/planner/keys.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L14:sha256:f3b2c4f045e67f523afdb6b4e99ea71d252d758b8cf2c674f04ad395da95dc42
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge one shared selected guard/mapping unit before each admitted checkpoint. |
| inputs / outputs | A per-call remaining balance and used counter; take() either consumes one or throws key_work_limit. |
| invariants | used never exceeds the initial uint64 grant: every increment follows a positive remaining test/decrement. Helpers share this object by reference; search/lowering have separate allowances. |
| ownership | Private stack state for one synchronous factory call. |
| failure | Exhaustion throws existing Error before a partial Plan can escape; diagnostic allocation is ordinary compiler/exception storage. |
| cost | Constant work per checkpoint; this counter excludes scalar widths, copying, allocation and separate search/lowering. |
| Design | [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0004

[Lines 16–23](../../../../../src/planner/keys.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L23:sha256:b2cbcc84d726282289cf64016e6d32950fe98c976bc893693eb64ebf567d795e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove exact componentwise key-term equality without treating wildcards as equal. |
| inputs / outputs | Borrow two validated query Terms and the shared Budget; return true only for identical VariableIds or exact equal typed Values. |
| invariants | Variable and Value alternatives do not cross-match; IgnoredColumn never establishes key equality. Repeats/constants are safe only through the complete component match. |
| ownership | Borrow immutable terms; no term/string copy is made. |
| failure | Only the budget can refuse here under genuine validated term domains; it adds no catch/translation. |
| cost | One selected unit; ID/scalar-tag comparison is constant-size, string/exact scalar comparison retains its actual width cost outside that unit. |
| Design | [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../build/verification/v67-key-design-v1/design.md) |

## B0005

[Lines 24–26](../../../../../src/planner/keys.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L26:sha256:a68ebdac4a18ec479a0c3b4744adee9e48dd9fba75473805a844ac0b205938c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State why only genuine enforced constraint metadata can support a key rule. |
| inputs / outputs | Comment locates the premise already validated by F01 and replayed by target_key. |
| invariants | Hints, statistics and observed accidental uniqueness do not certify a rewrite. |
| ownership | Documentation only, attached to the private key-premise scanner. |
| failure | This note itself supplies no runtime data validation. |
| cost | Documentation only. |
| Design | [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/catalog.md](../../../../catalog.md), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0006

[Lines 27–46](../../../../../src/planner/keys.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L46:sha256:0ad51ece4fdfffa37b7a948a7234287a2455e6c52f69f41daf9f462a7aaf93cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the original target-table enforced UNIQUE for the complete referenced set. |
| inputs / outputs | Scan actual target constraints; return the first enforced UNIQUE index whose distinct columns equal the FK referenced-column set. |
| invariants | Catalog admission already validates column domains/distinctness and FK arity/types. Equal length plus membership proves set equality; declaration pairing order is not changed. Empty keys are genuine at-most-one/existence constraints. |
| ownership | Borrow catalog metadata and Budget; return only an original constraint index. |
| failure | No match returns empty; guard exhaustion throws before publication. No data snapshot or approximate dependency is consulted. |
| cost | Cold constraint scan with nested key-membership checks; selected units charge inspected constraints/comparisons, not catalog/string allocation. |
| Design | [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [docs/catalog.md](../../../../catalog.md), [docs/key_specialization.md](../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../build/verification/v67-key-design-v1/design.md) |

## B0007

[Lines 47–49](../../../../../src/planner/keys.cpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L49:sha256:e1d6d3ff00c7e0fa27e44709ff962bc2156152fe8561d29a8b44aec026ca8bcb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the local witness-extension premise for removed parent payload. |
| inputs / outputs | Comment separates FK-fixed key cells from ignored or independent private existential cells. |
| invariants | A parent predicate or cross-occurrence/head/repeated-payload equality cannot be discarded merely because an FK exists. |
| ownership | Documentation beside entailed(). |
| failure | The comment confers no P5 or automatic-selection bound. |
| cost | Documentation only. |
| Design | [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../build/verification/v67-key-design-v1/design.md) |

## B0008

[Lines 50–67](../../../../../src/planner/keys.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L67:sha256:3c48a92f040f395a462616354af247874a54e0e0bcec908a5ef088a5809fbf4f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that the guaranteed unique parent row satisfies the complete removed atom. |
| inputs / outputs | Borrow source/parent atoms, the actual FK, current all-term use counts, permanent head membership and shared Budget; return the local entailment decision. |
| invariants | Every paired key term is exact and non-Ignored. Each non-key field is Ignored or a variable with exactly one current live use and no head use. Repeated/private, key-to-payload, head and nonlocal equalities block. |
| ownership | Borrows immutable original atoms and private liveness vectors; makes no query or state edits. |
| failure | False is a non-applicable rule; budget refusal propagates. Genuine catalog/query admission makes indexed columns/variables valid. |
| cost | Cold paired-key checks plus parent-width/reference-key membership scans; scalar widths remain explicit comparison costs. |
| Design | [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../build/verification/v67-key-design-v1/design.md) |

## B0009

[Lines 68–69](../../../../../src/planner/keys.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L69:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close private helper scope before the owning Plan payload definition. |
| inputs / outputs | End anonymous implementation namespace. |
| invariants | Helpers remain per-call/private and expose no new native capability. |
| ownership | No runtime object or allocation. |
| failure | No executable failure path. |
| cost | Scope structure only. |
| Design | [src/planner/keys.cpp](../../../../../src/planner/keys.cpp) |

## B0010

[Lines 70–78](../../../../../src/planner/keys.cpp#L70); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L78:sha256:5ffbf8d6f03f83409e1216314ff379aa5a25a06110e04f846f932e2a1c87a711
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the complete completed specialization result in immutable shared data. |
| inputs / outputs | Store both genuine plans, reason, ordered original-ID elimination records, new-to-original maps, Usage and reduced-query certificate. |
| invariants | The original comparison binding is distinct from the reduced executable identity. Only complete factory construction publishes this aggregate. |
| ownership | The new wrapper/control and vector payload are ordinary cold compiler storage. Retained PhysicalPlan/layout handles keep their existing ownership; ordinary runtime admission freezes only its chosen executable plan into that receiving query account without raising its cap. |
| failure | Standard owned-member destruction releases private payload on failure/last-owner release; no manual undo/catch layer is required. |
| cost | Cold retained metadata proportional to maps/steps/proof plus shared genuine plan graphs; no extra maintained runtime owner. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0012

[Lines 80–80](../../../../../src/planner/keys.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L80:sha256:547203c3ad89d4aacd38d6b74e3ffe3cbcf23fb962088b67d874fc7c387604fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the unchanged genuine comparison basis. |
| inputs / outputs | Read a valid Plan handle; return general plan. |
| invariants | Original identity, source query/catalog and tree are retained rather than reconstructed from the reduced query. |
| ownership | Borrows immutable Data and requires a live owning Plan; the public header deletes the corresponding rvalue borrow. |
| failure | Noexcept for a valid handle; no allocation, search or native state change. |
| cost | Constant-size field/span access. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0013

[Lines 81–81](../../../../../src/planner/keys.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L81:sha256:f1402335965a47c6883b88aacc8118083cb91d47cd369a1d2237482c0a01ffa3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the actual genuine executable plan selected by this call. |
| inputs / outputs | Read a valid Plan handle; return execution plan. |
| invariants | For unchanged reasons it shares the original plan; specialized execution has its own reduced query/identity and full original catalog. |
| ownership | Borrows immutable Data and requires a live owning Plan; the public header deletes the corresponding rvalue borrow. |
| failure | Noexcept for a valid handle; no allocation, search or native state change. |
| cost | Constant-size field/span access. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0014

[Lines 82–82](../../../../../src/planner/keys.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L82:sha256:995f9d7d8ca1e2f35592206e5458121af60b31b7a413b6e52c7e79676903ee6e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the completed selection/preservation reason. |
| inputs / outputs | Read a valid Plan handle; return Reason value. |
| invariants | This is a completed result reason, not a resource-refusal or theorem certificate. |
| ownership | By-value scalar result. |
| failure | Noexcept for a valid handle; no allocation, search or native state change. |
| cost | Constant-size field/span access. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0015

[Lines 83–83](../../../../../src/planner/keys.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L83:sha256:071c164b59368311365a96923b0cab8abf0131192df442f4ebeb4d3f6073cdd8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether a completed nonempty rewrite was lowered. |
| inputs / outputs | Read a valid Plan handle; return Boolean selected flag. |
| invariants | True exactly when reason()==specialized; absence of a rule never silently reports specialization. |
| ownership | By-value scalar result. |
| failure | Noexcept for a valid handle; no allocation, search or native state change. |
| cost | Constant-size field/span access. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0016

[Lines 84–84](../../../../../src/planner/keys.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L84:sha256:ae87814b54cf99f20dd3f30bcb68c21b170fcb21a7ce1aeb2568806789eb6f46
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow sequential original-ID elimination evidence. |
| inputs / outputs | Read a valid Plan handle; return const Elimination span. |
| invariants | Removed/witness IDs and constraint indices address the original basis; the order is the actual sequence of valid live-anchor steps. |
| ownership | Borrows immutable Data and requires a live owning Plan; the public header deletes the corresponding rvalue borrow. |
| failure | Noexcept for a valid handle; no allocation, search or native state change. |
| cost | Constant-size field/span access. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0017

[Lines 85–85](../../../../../src/planner/keys.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L85:sha256:11a7670681437ef266049d24a9212bc7a2e7f56239b45bbe493261195de0ef2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the executable-occurrence to original-occurrence map. |
| inputs / outputs | Read a valid Plan handle; return const OccurrenceId span. |
| invariants | Entry i identifies the original occurrence used for executable occurrence i; TableIds are never compacted by this map. |
| ownership | Borrows immutable Data and requires a live owning Plan; the public header deletes the corresponding rvalue borrow. |
| failure | Noexcept for a valid handle; no allocation, search or native state change. |
| cost | Constant-size field/span access. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0018

[Lines 86–86](../../../../../src/planner/keys.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L86:sha256:3b6a0935d64c188bd72abb7b4a0cfd82c26edd8931ab84ba2057e32c6e3facc4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the executable-variable to original-variable map. |
| inputs / outputs | Read a valid Plan handle; return const VariableId span. |
| invariants | Entry i identifies the original variable whose type/name/value is used by executable variable i; head order/repetition is remapped separately. |
| ownership | Borrows immutable Data and requires a live owning Plan; the public header deletes the corresponding rvalue borrow. |
| failure | Noexcept for a valid handle; no allocation, search or native state change. |
| cost | Constant-size field/span access. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0019

[Lines 87–87](../../../../../src/planner/keys.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L87-L87:sha256:11e0d7778de9fcf52c023110f507e789e7c6244e0006dabf68c39ff5ea67f9bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow actual selected guard/search/lowering usage. |
| inputs / outputs | Read a valid Plan handle; return const Usage reference. |
| invariants | Counters retain separate selected scopes and do not imply a wall-time, allocation-byte or dynamic maintenance bound. |
| ownership | Borrows immutable Data and requires a live owning Plan; the public header deletes the corresponding rvalue borrow. |
| failure | Noexcept for a valid handle; no allocation, search or native state change. |
| cost | Constant-size field/span access. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0020

[Lines 88–88](../../../../../src/planner/keys.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L88:sha256:5c28bf70350e24aeaba854f83e062aa211e4e52c069802564bf7e9deae5a8930
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow optional exact-search evidence for the executable reduced query. |
| inputs / outputs | Read a valid Plan handle; return const optional HeightCertificate reference. |
| invariants | Present only after a completed independently checked reduced search; never authority for the original-query minimum. |
| ownership | Borrows immutable Data and requires a live owning Plan; the public header deletes the corresponding rvalue borrow. |
| failure | Noexcept for a valid handle; no allocation, search or native state change. |
| cost | Constant-size field/span access. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md) |

## B0022

[Lines 90–186](../../../../../src/planner/keys.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L186:sha256:b21cb74f6fbe1cea977f24d40bcc22705b7544d900408f227d7a4306adc69c53
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a completed opt-in guarded specialization over a genuine direct-CQ basis. |
| inputs / outputs | Borrow immutable original query/catalog; discover valid sequential removals, compact IDs/head, optionally search and lower a reduced plan, then publish one owning Plan. |
| invariants | Only enforced FK/UNIQUE premises and actual live anchors authorize deletion. Private payload variables have one live term use/no head use. All original sources/options remain; no firing rule performs no search. Reduced proof/identity stay distinct from original authority. |
| ownership | The new wrapper/control and vector payload are ordinary cold compiler storage. Retained PhysicalPlan/layout handles keep their existing ownership; ordinary runtime admission freezes only its chosen executable plan into that receiving query account without raising its cap. All mutable liveness, uses, maps, steps and reduced query are private compiler locals. |
| failure | A refusal or allocation/validation/search/lowering exception unwinds private cold locals; the genuine input plan is not mutated and no partial Plan is published. No catch/retry or runtime rollback layer is added. key_work_limit and key_search_limit identify the corresponding refusals; existing lowering errors propagate unchanged. |
| cost | Cold repeated atom/constraint/key/use scans, copies and ID compaction; optional independently bounded exact search and lowering. Full source/runtime constraint costs remain unchanged; no ordinary update-path hook. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../build/verification/v67-key-design-v1/design.md), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp) |

```text
@source-span:L90-L104:sha256:968b393a866f0f7f22ea7804d0e87ebd159c45785cf53e7eb4bca26cdd545e1e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one cold factory call and collect all-term/head use metadata. |
| inputs / outputs | Borrow genuine original query/catalog; initialize private liveness/use/head vectors and preservation reason. |
| invariants | Only direct-CQ tree routes enter key discovery. Head membership remains permanent; use counts include repeated terms, not just distinct occurrences. |
| ownership | The new wrapper/control and vector payload are ordinary cold compiler storage. Retained PhysicalPlan/layout handles keep their existing ownership; ordinary runtime admission freezes only its chosen executable plan into that receiving query account without raising its cap. |
| failure | A refusal or allocation/validation/search/lowering exception unwinds private cold locals; the genuine input plan is not mutated and no partial Plan is published. No catch/retry or runtime rollback layer is added. |
| cost | Selected cold checkpoints plus actual private vector/query/proof work; allocation, scalar widths and separate search/lowering retain their explicit costs. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../build/verification/v67-key-design-v1/design.md) |

```text
@source-span:L107-L137:sha256:348db58d3b21de76eaf6dbbe509af06f46e8e22e76613b8a108a88c196d8cb1d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply sequential valid removals to the private live query view. |
| inputs / outputs | Scan original removed/witness IDs and actual enforced constraint indices; append proof steps and decrement every removed variable term. |
| invariants | Each step uses a distinct currently live anchor. Key variables survive there; private variables alone may disappear. Later guards use current counts, and the final live occurrence cannot be removed. |
| ownership | The new wrapper/control and vector payload are ordinary cold compiler storage. Retained PhysicalPlan/layout handles keep their existing ownership; ordinary runtime admission freezes only its chosen executable plan into that receiving query account without raising its cap. |
| failure | A refusal or allocation/validation/search/lowering exception unwinds private cold locals; the genuine input plan is not mutated and no partial Plan is published. No catch/retry or runtime rollback layer is added. |
| cost | Selected cold checkpoints plus actual private vector/query/proof work; allocation, scalar widths and separate search/lowering retain their explicit costs. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../build/verification/v67-key-design-v1/design.md) |

```text
@source-span:L139-L163:sha256:88ec50e1c15bbe6b5361ee33f18c3d76a0a66eba8595aa8c9a0316dcc29a265f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compact only derived occurrence/variable IDs and retain original provenance. |
| inputs / outputs | Build new-to-original maps and a private reduced query; copy retained atoms/types/names and remap variable terms. |
| invariants | With no steps the maps are identity maps and execution stays original. Otherwise every retained term has positive use and a remap. Physical TableIds/catalog/layouts are untouched. |
| ownership | The new wrapper/control and vector payload are ordinary cold compiler storage. Retained PhysicalPlan/layout handles keep their existing ownership; ordinary runtime admission freezes only its chosen executable plan into that receiving query account without raising its cap. |
| failure | A refusal or allocation/validation/search/lowering exception unwinds private cold locals; the genuine input plan is not mutated and no partial Plan is published. No catch/retry or runtime rollback layer is added. |
| cost | Selected cold checkpoints plus actual private vector/query/proof work; allocation, scalar widths and separate search/lowering retain their explicit costs. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../build/verification/v67-key-design-v1/design.md) |

```text
@source-span:L167-L181:sha256:f3d0286d8e5bbfb22365d5c152c222e9f106a0c6321162383ba0bb8b6f748f0e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve ordered head outputs and obtain a genuinely checked reduced execution tree. |
| inputs / outputs | Remap every original head entry, search the actual reduced query, lower it with original options and host ceilings, and retain that reduced certificate. |
| invariants | Head variables cannot be lost by valid removal, including repeated/ordered outputs. Search refusal publishes no Plan; successful proof scope is only the reduced query. |
| ownership | The new wrapper/control and vector payload are ordinary cold compiler storage. Retained PhysicalPlan/layout handles keep their existing ownership; ordinary runtime admission freezes only its chosen executable plan into that receiving query account without raising its cap. |
| failure | A refusal or allocation/validation/search/lowering exception unwinds private cold locals; the genuine input plan is not mutated and no partial Plan is published. No catch/retry or runtime rollback layer is added. |
| cost | Selected cold checkpoints plus actual private vector/query/proof work; allocation, scalar widths and separate search/lowering retain their explicit costs. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../build/verification/v67-key-design-v1/design.md) |

```text
@source-span:L183-L186:sha256:da71025f69b2c26d5122c6aeeac8accfe2efa40e25cc50bf7a2624613c43d544
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the completed immutable result after all fallible cold phases. |
| inputs / outputs | Finalize selected guard usage, copy the unchanged original handle and move the completed execution/steps/maps/proof into one shared Data control. |
| invariants | No partially marked liveness/remap/search state is exposed. Genuine input data was never mutated; successful publication adds no runtime owner or query-update callback. |
| ownership | The new wrapper/control and vector payload are ordinary cold compiler storage. Retained PhysicalPlan/layout handles keep their existing ownership; ordinary runtime admission freezes only its chosen executable plan into that receiving query account without raising its cap. |
| failure | A refusal or allocation/validation/search/lowering exception unwinds private cold locals; the genuine input plan is not mutated and no partial Plan is published. No catch/retry or runtime rollback layer is added. |
| cost | Selected cold checkpoints plus actual private vector/query/proof work; allocation, scalar widths and separate search/lowering retain their explicit costs. |
| Design | [include/crown/planner/keys.hpp](../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../build/verification/v67-key-design-v1/design.md) |

## B0023

[Lines 187–187](../../../../../src/planner/keys.cpp#L187); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L187-L187:sha256:2625232a9196674be00b982f69fc9acb792b269c1decfc8087b20cae8b04ff97
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the key-specialization implementation namespace. |
| inputs / outputs | End planner::keys scope after the sole factory. |
| invariants | No extra state or selection action follows publication. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | Scope structure only. |
| Design | [src/planner/keys.cpp](../../../../../src/planner/keys.cpp) |
