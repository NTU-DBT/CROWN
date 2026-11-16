# `src/planner/fallback.cpp` — block usage map

[Source](../../../../../src/planner/fallback.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Bound cold metadata work, recognize the original query and lower a full-catalog source-only coordinator without claiming a CROWN or GHD certificate.

Snapshot SHA-256: `25c92bf393e6807a4c617427430485c92df0718dfd3d2b6a11f16cfdcf883858`. 129 lines partitioned into 19 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [fallback](../../../subsystem_contracts.md#fallback). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/fallback.md](../../../../fallback.md), [docs/source_images.md](../../../../source_images.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md](../../../../../Refactor.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/planner/fallback.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–22](../../../../../src/planner/fallback.cpp#L9) | Type/record definition: struct Budget |  · [reviewed contract](#b0002) |
| [B0003 · 23–25](../../../../../src/planner/fallback.cpp#L23) | Callable definition: void require(bool condition, const char* message) | calls Error; guard void require(bool condition, const char* message) { · [reviewed contract](#b0003) |
| [B0004 · 26–28](../../../../../src/planner/fallback.cpp#L26) | Explanatory comments or spacing. | source comment (unverified): // Admit copied metadata and variable-width payload before publishing copies. · [reviewed contract](#b0004) |
| [B0005 · 29–61](../../../../../src/planner/fallback.cpp#L29) | Callable definition: void metadata(const Catalog& catalog, const Query& query, Budget& budget) | calls take, text, require, valueless_by_exception; guard budget.take(); require(!constraint.valueless_by_exception(), "invalid fallback constraint");; 13 loop sites; source comment (unverified): // Admit copied metadata and variable-width payload before publishing copies. · [reviewed contract](#b0005) |
| [B0006 · 62–65](../../../../../src/planner/fallback.cpp#L62) | Callable definition: std::optional&lt;std::uint64_t&gt; sum(std::uint64_t a, std::uint64_t b, bool& overflow) | calls max; returns {}; a + b · [reviewed contract](#b0006) |
| [B0007 · 66–67](../../../../../src/planner/fallback.cpp#L66) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 68–75](../../../../../src/planner/fallback.cpp#L68) | Type/record definition: struct Plan::Data |  · [reviewed contract](#b0008) |
| [B0009 · 76–76](../../../../../src/planner/fallback.cpp#L76) | Callable definition: const Catalog& Plan::originalcatalog() const & noexcept | calls ; returns data_-&gt;catalog · [reviewed contract](#b0009) |
| [B0010 · 77–77](../../../../../src/planner/fallback.cpp#L77) | Callable definition: const Query& Plan::query() const & noexcept | calls ; returns data_-&gt;query · [reviewed contract](#b0010) |
| [B0011 · 78–78](../../../../../src/planner/fallback.cpp#L78) | Callable definition: const PhysicalPlan& Plan::source_only() const & noexcept | calls ; returns data_-&gt;source · [reviewed contract](#b0011) |
| [B0012 · 79–79](../../../../../src/planner/fallback.cpp#L79) | Callable definition: const StructuralAnalysis& Plan::structure() const & noexcept | calls ; returns data_-&gt;structure · [reviewed contract](#b0012) |
| [B0013 · 80–80](../../../../../src/planner/fallback.cpp#L80) | Callable definition: const Profile& Plan::profile() const & noexcept | calls ; returns data_-&gt;profile · [reviewed contract](#b0013) |
| [B0014 · 81–81](../../../../../src/planner/fallback.cpp#L81) | Callable definition: std::uint64_t Plan::work() const noexcept | calls ; returns data_-&gt;work · [reviewed contract](#b0014) |
| [B0015 · 82–82](../../../../../src/planner/fallback.cpp#L82) | Explanatory comments or spacing. |  |
| [B0016 · 83–106](../../../../../src/planner/fallback.cpp#L83) | Callable definition: Estimates Plan::estimates(std::span&lt;const std::uint64_t&gt; tablecounts) const | calls require, size, sum, max; guard require(tablecounts.size() == data_-&gt;catalog.tables.size(), "fallback estimates require one count p…; returns result; 3 loop sites; source comment (unverified): // A zero factor wins over any otherwise overflowing prefix product. · [reviewed contract](#b0016) |
| [B0017 · 107–107](../../../../../src/planner/fallback.cpp#L107) | Explanatory comments or spacing. |  |
| [B0018 · 108–128](../../../../../src/planner/fallback.cpp#L108) | Callable definition: Plan admit(const Catalog& catalog, const Query& query, const PhysicalOptions& options, const Limits& limits) | calls take, metadata, analyze_bounded, Error; returns Plan(std::make_shared&lt;Plan::Data&gt;(Plan::Data{std::move(originalcatalog), std::move(originalquery), …; growth make_shared · [reviewed contract](#b0018) |
| [B0019 · 129–129](../../../../../src/planner/fallback.cpp#L129) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::fallback · [reviewed contract](#b0019) |

## B0001

[Lines 1–8](../../../../../src/planner/fallback.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:ca337347d79a0326a3a5150ae491b2ea6cd691196607aaab48145e1af18819e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind explicit fallback admission to its public contract and checked error/scalar facilities. |
| inputs / outputs | Implementation includes and private namespaces; no query is executed by this region. |
| invariants | No global registry or ordinary equality-plan routing is changed. |
| ownership | No retained owner. |
| failure | Compile/link errors remain ordinary. |
| cost | Compile-time scaffolding. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp) |

## B0002

[Lines 9–22](../../../../../src/planner/fallback.cpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L22:sha256:58fe3cbcc4685cf4d28cb3e673d87636779afa03485ba5e5a89c75644e9c6f2a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend one nonrefillable selected cold-admission balance before owned metadata copies. |
| inputs / outputs | Budget remaining/used and take/text/literal requests; accepted requests advance used and reduce remaining. |
| invariants | Refuse before subtraction when requested units exceed remaining. String/decimal digit extents are charged; valueless Value is rejected. These charges are selected work, not all validation/copy CPU or allocation bytes. |
| ownership | Builder-local counters borrow source strings/literals synchronously and retain no payload. |
| failure | Exhaustion throws fallback_work_limit; valueless literal throws fallback_admission; no retry or refill. |
| cost | Constant arithmetic per take, string size inspection and actual Decimal parts access; copying/allocation remain later costs. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0003

[Lines 23–25](../../../../../src/planner/fallback.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L25:sha256:992b14a93fd9da901d78e21776270fbca54748a91972a80ff0efa279b48f4c76
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an unsupported admission premise with its explicit typed code. |
| inputs / outputs | Condition and static diagnostic in; returns only when condition is true. |
| invariants | False is fallback_admission, never an accepted alternative or a classification result. |
| ownership | Borrows the static message during Error construction. |
| failure | Throws crown::Error directly. |
| cost | One branch plus actual error construction on failure. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0004

[Lines 26–28](../../../../../src/planner/fallback.cpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L28:sha256:2f2a76665255a97e2b6e7bea19d4b6560f4722ea3dafac4c324cfd3756bbd252
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the pre-copy selected metadata-admission boundary. |
| inputs / outputs | Comment preceding metadata; no executable input/output. |
| invariants | Separate validation, recognition and lowering costs remain visible and are not subsumed by the selected counter. |
| ownership | No owner or retained state. |
| failure | No executed branch or passing receipt. |
| cost | No runtime work from the comment. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp) |

## B0005

[Lines 29–61](../../../../../src/planner/fallback.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L61:sha256:c916af97902579bea699617a9775e2ad9067469d3b2bc109b908b78cbd9b36b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit every original catalog/query metadata region and variable-width text/literal extent before private copying. |
| inputs / outputs | Original Catalog/Query and shared Budget in; spent balance out, no copied metadata. |
| invariants | Visits unused tables, names, all column names, constraint names/columns and foreign targets, optional/statistics descriptors, key-hint reasons/columns, variables, occurrences/terms and output aliases. Variant validity is checked; term literals reuse the same balance. Semantic shape/ID/type validity remains validate responsibility. |
| ownership | All input graphs are borrowed; loops retain no caller pointers after return. No hidden native-account claim applies to these ordinary cold DTOs. |
| failure | Selected exhaustion and valueless constraints/terms/literals throw before published Plan or copied graph; malformed semantics are subsequently rejected by validation. |
| cost | Work visits scale with complete metadata plus admitted string/decimal-digit extents; does not bound allocation/copy, schema validation, GYO or source-only identity work. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp) |

## B0006

[Lines 62–65](../../../../../src/planner/fallback.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L65:sha256:3e56ef70e559ccd3bce0f3088b4bab42f4a8537c179655eeebea1bf3155ac4de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check uint64 addition without wrapping an advisory estimate. |
| inputs / outputs | Two uint64 summands and overflow flag in; engaged exact sum or disengaged optional out. |
| invariants | A failing addition sets overflow true and never returns a wrapped lower bound; existing true flag is never cleared. |
| ownership | Inline scalars and borrowed caller flag; no storage allocation. |
| failure | Arithmetic overflow is a result flag, not an exception. |
| cost | O(1) checked arithmetic. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp) |

## B0007

[Lines 66–67](../../../../../src/planner/fallback.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L67:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close private admission helpers before defining the immutable owner. |
| inputs / outputs | Namespace delimiter only. |
| invariants | Helpers do not become public fallback authority. |
| ownership | No owner. |
| failure | No executable failure branch. |
| cost | No runtime work. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |

## B0008

[Lines 68–75](../../../../../src/planner/fallback.cpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L75:sha256:406ebe7f981650fbb22fc6388aa063e6a06f819fd951b571c69f1c1cab262a37
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own original cold query/catalog and real structural analysis beside a separately genuine constant source plan. |
| inputs / outputs | Plan::Data contains Catalog, Query, PhysicalPlan source, StructuralAnalysis, Profile and spent-work value. |
| invariants | Original query is retained without a fabricated free-connex tree or rewritten head; source-only identity is not original-query provenance/certification. |
| ownership | Ordinary compiler-owned graph becomes shared const after factory publication; PhysicalPlan retains its genuine owned lowering metadata. |
| failure | Partial aggregate/shared allocation failures unwind before Plan exists. |
| cost | One shared control plus copied original graph, source lowering and analysis state; no linear/native-bound claim from this declaration. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp) |

## B0009

[Lines 76–76](../../../../../src/planner/fallback.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L76:sha256:877323c6659cc42fd7c7e49adb0d940761f164e659e9fa0f62b94ed81f708362
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the original Catalog from an admitted Plan. |
| inputs / outputs | Live Plan in; const reference to Data.catalog metadata out. |
| invariants | Every physical source and constraint is retained, including unused tables. |
| ownership | Reference borrows shared const Data; caller must keep an owning Plan alive. |
| failure | Noexcept for valid admitted handles; no allocation or new admission. |
| cost | O(1) reference access. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0010

[Lines 77–77](../../../../../src/planner/fallback.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L77:sha256:37990c97c3bbd540c39efab0c896d0fa61c2980cf227431c13ab408a42ae1bb8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the unchanged original Query from an admitted Plan. |
| inputs / outputs | Live Plan in; const reference to Data.query metadata out. |
| invariants | Original atoms, terms, contradiction and head order are not replaced by the constant coordinator. |
| ownership | Reference borrows shared const Data; caller must keep an owning Plan alive. |
| failure | Noexcept for valid admitted handles; no allocation or new admission. |
| cost | O(1) reference access. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0011

[Lines 78–78](../../../../../src/planner/fallback.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L78:sha256:d675c50752e8a78364096904f39688a4c3d0f6ef914a31ffa770a30f5208bc51
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the genuine zero-atom source PhysicalPlan from an admitted Plan. |
| inputs / outputs | Live Plan in; const reference to Data.source metadata out. |
| invariants | This reference supplies source storage/constraints/backend only, never an original-query tree or guarantee. |
| ownership | Reference borrows shared const Data; caller must keep an owning Plan alive. |
| failure | Noexcept for valid admitted handles; no allocation or new admission. |
| cost | O(1) reference access. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0012

[Lines 79–79](../../../../../src/planner/fallback.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L79:sha256:e57daaff5e7a0f5f9715422003f3fcef66cb13462f28c9e3b404d270038da17c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual StructuralAnalysis from an admitted Plan. |
| inputs / outputs | Live Plan in; const reference to Data.structure metadata out. |
| invariants | Recognition analysis remains the actual original query class and is not guessed from fallback choice. |
| ownership | Reference borrows shared const Data; caller must keep an owning Plan alive. |
| failure | Noexcept for valid admitted handles; no allocation or new admission. |
| cost | O(1) reference access. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0013

[Lines 80–80](../../../../../src/planner/fallback.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L80:sha256:51ec5e81fec7c19d8303525d5e9f74df9823b66ab94524c644aca7d6cc58c801
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the immutable explicit Profile from an admitted Plan. |
| inputs / outputs | Live Plan in; const reference to Data.profile metadata out. |
| invariants | Actual class/reason and explicit recomputation/materialization qualifiers remain visible. |
| ownership | Reference borrows shared const Data; caller must keep an owning Plan alive. |
| failure | Noexcept for valid admitted handles; no allocation or new admission. |
| cost | O(1) reference access. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0014

[Lines 81–81](../../../../../src/planner/fallback.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L81:sha256:37eaf0d09ce2f0e5205c069fc6e63fa9e3ff5c684ff694835880e5116cfa43b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the selected metadata-admission work actually charged. |
| inputs / outputs | Live Plan in; uint64 Data.work out. |
| invariants | Counter excludes separately bounded GYO/lowering and uncounted validation/copy/allocation work; it is not runtime complexity. |
| ownership | Inline scalar copy from immutable Data. |
| failure | Noexcept for valid admitted handles. |
| cost | O(1) getter. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0016

[Lines 83–106](../../../../../src/planner/fallback.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L106:sha256:e3d0912ecc98449c87e216fd7215e21d5f84dea358bfe86c1728acdabccf89bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calculate checked advisory original-assignment and logical committed state upper bounds. |
| inputs / outputs | Exactly one uint64 count per original catalog table in; Estimates out. |
| invariants | Sum every physical source once; multiply table counts once per original occurrence, including repeated aliases. Pre-scan zero body counts and contradiction before products, so zero wins over otherwise overflowing products. Empty body has one assignment unless contradiction; Boolean projection bounds output by one. Nonempty head upper bound is full assignments. Unknown arithmetic propagates without wrapping; state is source+output, not peak private images or nested-loop prefix CPU. |
| ownership | Borrows the caller count span only during this call; result is inline and Plan remains immutable. |
| failure | Wrong width throws fallback_admission. Overflow sets flag and disengages affected values; source-sum overflow remains visible even if body is zero. |
| cost | O(number of catalog tables + occurrences), constant auxiliary state. Exact products are advisory and may be much larger than answers; no admission-memory or CROWN/GHD bound. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0018

[Lines 108–128](../../../../../src/planner/fallback.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L128:sha256:a8c071e41f5de4613c30a869d65759db35ef67294db83b7148b0d969d63979f7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit any validated direct set CQ through real recognition and a separate constant source coordinator. |
| inputs / outputs | Original Catalog/Query, physical backend options and distinct finite policies in; immutable copied Plan out. |
| invariants | Selected metadata grant is spent before copies. analyze_bounded first validates the copied inputs and must return an actual analysis; all three classes are retained and contradiction changes only reason. No duplicate standalone validation traversal remains. lower_tree receives the complete original catalog/options with Query{} and FreeConnexTree{}, preserving constraints/backend while making no original-query tree. Only completed immutable state is published. |
| ownership | Local ordinary Catalog/Query copies, recognition result and genuine source plan unwind on refusal. Shared const Data independently owns caller metadata after return; native account freeze is deferred to runtime. |
| failure | Preserve fallback_admission/work_limit; recognition refusal and resource_limit become fallback_work_limit, other crown::Error becomes fallback_admission. Allocation exceptions propagate normally, with no catch-all or fallback success. |
| cost | Selected metadata/string/literal visits plus separately bounded validation/GYO/lowering, complete DTO copies, source-plan identity and allocations; no fallback runtime or paper-bound proof. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [Refactor.md](../../../../../Refactor.md), [docs/fallback.md](../../../../fallback.md) |

## B0019

[Lines 129–129](../../../../../src/planner/fallback.cpp#L129); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L129:sha256:cc20d595fc4f496f9a75d0bb2a94ab0a0ebccbc475de3c772fbe3d927c0ca7ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the opt-in fallback admission implementation namespace. |
| inputs / outputs | Namespace delimiter. |
| invariants | No implicit registration or global mutable backend is introduced. |
| ownership | No owner. |
| failure | No executable failure branch. |
| cost | No runtime work. |
| Design | [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp) |
