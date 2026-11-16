# `include/crown/planner/keys.hpp` — block usage map

[Source](../../../../../../include/crown/planner/keys.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare immutable guarded key-specialization plans, source/reduced provenance, finite cold grants and safe borrowed metadata.

Snapshot SHA-256: `8f9655cf98f7e7e4c7cb444b3643f2916ca856fc0f858447d38360cd24037acd`. 74 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [keys](../../../../subsystem_contracts.md#keys). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/key_specialization.md](../../../../../key_specialization.md), [Refactor.md](../../../../../../Refactor.md), [docs/catalog.md](../../../../../catalog.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/planner_proofs.md](../../../../../planner_proofs.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/planner/keys.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–7](../../../../../../include/crown/planner/keys.hpp#L7) | Type/record definition: enum class Reason |  · [reviewed contract](#b0002) |
| [B0003 · 8–9](../../../../../../include/crown/planner/keys.hpp#L8) | Explanatory comments or spacing. | source comment (unverified): // All IDs name the original query/catalog. Constraint indices address the · [reviewed contract](#b0003) |
| [B0004 · 10–13](../../../../../../include/crown/planner/keys.hpp#L10) | Type/record definition: struct Elimination | source comment (unverified): // All IDs name the original query/catalog. Constraint indices address the · [reviewed contract](#b0004) |
| [B0005 · 14–18](../../../../../../include/crown/planner/keys.hpp#L14) | Type/record definition: struct Limits | source comment (unverified): // One shared selected guard/mapping grant. · [reviewed contract](#b0005) |
| [B0006 · 19–22](../../../../../../include/crown/planner/keys.hpp#L19) | Type/record definition: struct Usage |  · [reviewed contract](#b0006) |
| [B0007 · 23–35](../../../../../../include/crown/planner/keys.hpp#L23) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Cold, opt-in direct-CQ set specialization. The original comparison plan and · [reviewed contract](#b0007) |
| [B0008 · 36–36](../../../../../../include/crown/planner/keys.hpp#L36) | Callable definition: Plan(Plan&& other) noexcept : data_(other.data_) | calls data_ · [reviewed contract](#b0008) |
| [B0009 · 37–37](../../../../../../include/crown/planner/keys.hpp#L37) | Callable definition: Plan& operator=(Plan&& other) noexcept | returns *this · [reviewed contract](#b0009) |
| [B0010 · 38–57](../../../../../../include/crown/planner/keys.hpp#L38) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // New -&gt; original. · [reviewed contract](#b0010) |
| [B0011 · 58–58](../../../../../../include/crown/planner/keys.hpp#L58) | Callable definition: explicit Plan(std::shared_ptr&lt;const Data&gt; data) : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0011) |
| [B0012 · 59–74](../../../../../../include/crown/planner/keys.hpp#L59) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // A rule needs a distinct live witness, an enforced FK and enforced target key. · [reviewed contract](#b0012) |

## B0001

[Lines 1–6](../../../../../../include/crown/planner/keys.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:ffb590070ff08d588b6c78059bbe7b4185166a8d2f1d90bb789ee07dc58f52e7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the opt-in key-specialization declarations beside existing lowering and exact-search APIs. |
| inputs / outputs | Include the genuine PhysicalPlan/lowering and SearchLimits/certificate types; open the planner::keys namespace. |
| invariants | This header adds no automatic selection, runtime owner, update hook or SQL admission. |
| ownership | Compile-time declarations only; included public types retain their existing owners. |
| failure | Missing dependencies are ordinary compilation failures; no native exception handling is installed. |
| cost | Header parsing/type declarations only; no query-update work. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [docs/key_specialization.md](../../../../../key_specialization.md) |

## B0002

[Lines 7–7](../../../../../../include/crown/planner/keys.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L7:sha256:53c757eda43b20d32974015de0028f53af842f7517fd1d4aab30878b21011bad
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the actual selected or unchanged key-rewrite outcome. |
| inputs / outputs | Reason distinguishes specialized execution from normalized_sql, constant_route and no_match preservation. |
| invariants | Resource refusal throws before a Plan escapes; these values are completed result reasons, not partial-success statuses. |
| ownership | Plain by-value enum in immutable result metadata. |
| failure | Constructing/reading this enum does not fail. |
| cost | Constant-size metadata. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../../key_specialization.md) |

## B0003

[Lines 8–9](../../../../../../include/crown/planner/keys.hpp#L8); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L9:sha256:1637f6e1289bbc9450c188c086c7cc4e6e5af4198bb4d5b3c69e87ae0676f933
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain which original ID domains an elimination record uses. |
| inputs / outputs | Comment binds removed/witness occurrences and FK/UNIQUE indices to the original query/catalog. |
| invariants | Records do not use compacted executable occurrence IDs or an all-UNIQUE-only index space. |
| ownership | Documentation beside the non-owning numeric record. |
| failure | The comment grants no rewrite or proof authority. |
| cost | Documentation only. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../../key_specialization.md) |

## B0004

[Lines 10–13](../../../../../../include/crown/planner/keys.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L13:sha256:a1d4c880ca430690444b83a83dfb7f58d0d317151f018fbf1852aa80357cfe32
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the source-bound witness for one sequential removal. |
| inputs / outputs | Store original removed and witness OccurrenceIds plus their actual table-constraint indices. |
| invariants | The factory records a distinct currently live witness, enforced FK and enforced target UNIQUE before removal. |
| ownership | Four numeric fields are owned by the immutable Plan vector; original plan metadata supplies their domains. |
| failure | The record itself does not validate a database or accept caller-made evidence. |
| cost | Constant-size record; vector capacity and retained original metadata have separate cold costs. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../../build/verification/v67-key-design-v1/design.md) |

## B0005

[Lines 14–18](../../../../../../include/crown/planner/keys.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L18:sha256:aba223a84356fe158a8e7d24b4bc02960c479a26a3f761b79c28571d9cefb96d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply separate finite guard, exact-search and host-lowering allowances. |
| inputs / outputs | work funds one selected guard/mapping balance; search uses existing producer/replay limits; lowering optionally restricts existing lowering/identity ceilings. |
| invariants | Limits are not a CPU/RSS cap and cannot increase the original native runtime account or bypass actual tree validation. |
| ownership | Caller-owned cold value copied/borrowed during the synchronous factory call. |
| failure | Zero/exhausted guard/search/lowering allowances may refuse construction before publication. |
| cost | Constant-size policy; actual scans, copying, scalar widths and search have their stated costs. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [include/crown/planner/oracle.hpp](../../../../../../include/crown/planner/oracle.hpp), [include/crown/planner/lower.hpp](../../../../../../include/crown/planner/lower.hpp), [docs/key_specialization.md](../../../../../key_specialization.md) |

## B0006

[Lines 19–22](../../../../../../include/crown/planner/keys.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L22:sha256:6908292112c39c0df64dc7b9be9e512269d82e8b15fd6f9928324e50a9ab06aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report actual selected guard, search and lowering work categories. |
| inputs / outputs | Usage retains cumulative selected guard/mapping units, exact-search statistics and lowerer work from a completed call. |
| invariants | The categories retain separate scopes; they are not elapsed CPU, total pointer/string work, allocator bytes or an update-time bound. |
| ownership | Plain counters owned by immutable Plan data; getters borrow them. |
| failure | No partial Usage escapes when specialization fails. |
| cost | Constant-size report; observation itself adds no runtime-update state. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../../key_specialization.md) |

## B0007

[Lines 23–35](../../../../../../include/crown/planner/keys.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L35:sha256:d58e3a5347a4b2f9d7f931a110b37461f6f9626260b8386ee79aa4abee796e7b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the immutable cold specialization facade and its ownership boundary. |
| inputs / outputs | A completed Plan keeps the original comparison plan, actual execution plan, provenance, selected reason and optional reduced-query proof. |
| invariants | The complete original source catalog is retained by execution; constraint enforcement belongs to existing PhysicalRuntime. Normalized SQL is not rebound to this family. |
| ownership | The new wrapper/control and vector payload are ordinary cold compiler storage. Retained PhysicalPlan/layout handles keep their existing ownership; ordinary runtime admission freezes only its chosen executable plan into that receiving query account without raising its cap. Copies share immutable control; move operations intentionally preserve the source handle. |
| failure | Public callers cannot construct Data or mint a Plan. Last-owner release can destroy the retained compiler/proof graph. |
| cost | Handle copying is constant-size; last-owner destruction and destination replacement can be proportional to retained graph/array/string payload. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../../src/planner/keys.cpp), [include/crown/runtime/physical.hpp](../../../../../../include/crown/runtime/physical.hpp), [docs/key_specialization.md](../../../../../key_specialization.md) |

## B0008

[Lines 36–36](../../../../../../include/crown/planner/keys.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:f8c2020b9061d5c7c5f57329c678a51c2097149b23c9584670e9b5f53064fcb2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move a Plan handle while preserving the source handle for existing borrows. |
| inputs / outputs | Copy the shared immutable control from the source into a newly constructed handle. |
| invariants | Both handles remain valid; this operation does not move the underlying PhysicalPlan or provenance vectors. |
| ownership | Shares the same immutable Data control and existing plan/layout ownership. |
| failure | Declared noexcept and allocates no new wrapper/control. |
| cost | Constant-size shared-handle copy. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../../key_specialization.md) |

## B0009

[Lines 37–37](../../../../../../include/crown/planner/keys.hpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L37:sha256:2d0b27e62f918ab627b414815b74bd71f2200b29736177e6bdd95ae131478f2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a Plan handle by sharing another handle without invalidating that source. |
| inputs / outputs | Assign the immutable shared control and return this handle. |
| invariants | Source validity survives, including self assignment; old destination borrows expire if their last owner is released. |
| ownership | Shares new Data and releases the old destination control. |
| failure | Declared noexcept; no new allocation, but old graph destruction is real work. |
| cost | Constant-size handle assignment plus possible linear last-owner release of the previous destination. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../../key_specialization.md) |

## B0010

[Lines 38–57](../../../../../../include/crown/planner/keys.hpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L57:sha256:5326769341995f5a82f83c8d28f0c8345ec50ca13f8611955cec37933184f4ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose borrowed plans/provenance/usage and explicitly scope reduced proof authority. |
| inputs / outputs | Lvalue getters borrow immutable plans, elimination spans, new-to-original maps, Usage and an optional reduced HeightCertificate; scalar reason/selected accessors return values. |
| invariants | All reference/span borrows reject rvalue Plan calls. Occurrence/variable map domains are distinct. The certificate belongs to execution().query(), not the original query. |
| ownership | Borrows require a live owning Plan control; copying/moving a Plan preserves shared data, while last-owner release/replacement invalidates borrows. |
| failure | Rvalue metadata borrows are compile-time deleted; valid lvalue getters are noexcept. No public factory/proof authority is conferred by format_version. |
| cost | Constant-size access; no allocation, copy of arrays, search or runtime work. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../../key_specialization.md), [include/crown/planner/oracle.hpp](../../../../../../include/crown/planner/oracle.hpp) |

## B0011

[Lines 58–58](../../../../../../include/crown/planner/keys.hpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L58:sha256:f4b25bc173383cb1cf8f6ce915a6b76453968424f051e5f2ec3b3670d5037f85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Privately adopt the completed immutable specialization data. |
| inputs / outputs | Receive the factory-created shared Data control and store it in the Plan. |
| invariants | Only the friend factory reaches this constructor after complete guard/mapping/search/lowering work. |
| ownership | Transfers the incoming shared control; underlying compiler graph ownership remains shared. |
| failure | No new allocation in this constructor; allocation refusal occurs before its argument exists. |
| cost | Constant-size shared-control move. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../../key_specialization.md) |

## B0012

[Lines 59–74](../../../../../../include/crown/planner/keys.hpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L74:sha256:48ee9be7c8cd06747a41ec6b496d8ac4f0df736a24d6ee95f533ed7ca5d5aa70
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the sole Plan factory and summarize the exact local rewrite contract. |
| inputs / outputs | The friend factory accepts a genuine physical basis and Limits, or throws before returning a Plan. |
| invariants | A distinct live FK witness and enforced UNIQUE must entail key terms and unconstrained/private parent payload. Constants/repeated/nonlocal non-key terms block. Normalized/constant/no-match paths preserve execution, and no-match does no search. |
| ownership | The new wrapper/control and vector payload are ordinary cold compiler storage. Retained PhysicalPlan/layout handles keep their existing ownership; ordinary runtime admission freezes only its chosen executable plan into that receiving query account without raising its cap. |
| failure | A refusal or allocation/validation/search/lowering exception unwinds private cold locals; the genuine input plan is not mutated and no partial Plan is published. No catch/retry or runtime rollback layer is added. Existing scalar-width/copy/search/identity costs remain outside the selected guard grant. |
| cost | Cold query/constraint scans and mapping; optional bounded exact tree search/lowering. No ordinary update hook or new maintained owner. |
| Design | [include/crown/planner/keys.hpp](../../../../../../include/crown/planner/keys.hpp), [src/planner/keys.cpp](../../../../../../src/planner/keys.cpp), [docs/key_specialization.md](../../../../../key_specialization.md), [build/verification/v67-key-design-v1/design.md](../../../../../../build/verification/v67-key-design-v1/design.md), [Refactor.md](../../../../../../Refactor.md) |
