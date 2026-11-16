# `include/crown/planner/fallback.hpp` — block usage map

[Source](../../../../../../include/crown/planner/fallback.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare immutable explicit classical-CQ fallback admission, actual structural class, guarantee profile and advisory row estimates.

Snapshot SHA-256: `fda659f309c95fd041097e0675aba2b8fea31a13cde928b4a4f1e8a7557317fa`. 79 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [fallback](../../../../subsystem_contracts.md#fallback). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/fallback.md](../../../../../fallback.md), [docs/source_images.md](../../../../../source_images.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md](../../../../../../Refactor.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/planner/fallback.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../../include/crown/planner/fallback.hpp#L13) | Type/record definition: enum class Backend |  · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../../include/crown/planner/fallback.hpp#L14) | Type/record definition: enum class Reason |  · [reviewed contract](#b0003) |
| [B0004 · 15–26](../../../../../../include/crown/planner/fallback.hpp#L15) | Type/record definition: struct Profile |  · [reviewed contract](#b0004) |
| [B0005 · 27–32](../../../../../../include/crown/planner/fallback.hpp#L27) | Type/record definition: struct Estimates | source comment (unverified): // Logical committed source/answer rows, not peak bytes or image/journal space. · [reviewed contract](#b0005) |
| [B0006 · 33–37](../../../../../../include/crown/planner/fallback.hpp#L33) | Type/record definition: struct Limits |  · [reviewed contract](#b0006) |
| [B0007 · 38–45](../../../../../../include/crown/planner/fallback.hpp#L38) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Cold explicit reference-backend choice for any validated non-null set CQ. · [reviewed contract](#b0007) |
| [B0008 · 46–46](../../../../../../include/crown/planner/fallback.hpp#L46) | Callable definition: Plan(Plan&& other) noexcept : data_(other.data_) | calls data_ · [reviewed contract](#b0008) |
| [B0009 · 47–47](../../../../../../include/crown/planner/fallback.hpp#L47) | Callable definition: Plan& operator=(Plan&& other) noexcept | returns *this · [reviewed contract](#b0009) |
| [B0010 · 48–63](../../../../../../include/crown/planner/fallback.hpp#L48) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Selected metadata admission only. · [reviewed contract](#b0010) |
| [B0011 · 64–64](../../../../../../include/crown/planner/fallback.hpp#L64) | Callable definition: explicit Plan(std::shared_ptr&lt;const Data&gt; data) : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0011) |
| [B0012 · 65–79](../../../../../../include/crown/planner/fallback.hpp#L65) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Preserves every original atom/constant/repeated or ignored term and ordered · [reviewed contract](#b0012) |

## B0001

[Lines 1–12](../../../../../../include/crown/planner/fallback.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:2b346f64c20ca278ad1e2b329d69b580be536fa93b264dc429cb22e0bbc3f7a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import existing typed lowering, recognition and immutable-owner vocabulary for explicit fallback admission. |
| inputs / outputs | Header guard, includes and planner::fallback namespace; no executable input/output. |
| invariants | Inclusion does not select fallback, rewrite equality planning or extend SQL admission. |
| ownership | No retained owner in this scaffolding. |
| failure | Ordinary compiler/include failures only. |
| cost | Compile-time declarations. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [include/crown/planner/lower.hpp](../../../../../../include/crown/planner/lower.hpp), [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp), [docs/fallback.md](../../../../../fallback.md) |

## B0002

[Lines 13–13](../../../../../../include/crown/planner/fallback.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:f7ab4acc615aa48480ac518952c563ad5dfa7193ef299582d2e6052bca30ac95
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the implemented conservative backend family. |
| inputs / outputs | Backend enum has the exact_recompute_v1 identity. |
| invariants | This enum is vocabulary, not a dispatch mechanism, GHD implementation or CROWN guarantee. |
| ownership | Inline enum value; no allocation or borrowed payload. |
| failure | No runtime admission or failure is performed here. |
| cost | Fixed-size declaration. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp), [docs/fallback.md](../../../../../fallback.md) |

## B0003

[Lines 14–14](../../../../../../include/crown/planner/fallback.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L14:sha256:1b359a0fb6073137a1cc879308c6ec881b0856f6014f211ef06847d91441e5a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make the explicit fallback admission reason visible independently of backend identity. |
| inputs / outputs | Reason distinguishes cyclic body, acyclic non-free-connex head, explicit reference choice and contradiction. |
| invariants | Contradiction is a semantic reason; actual structural classification remains separately available. |
| ownership | Inline enum value. |
| failure | No default resource-exhaustion or unsupported-semantics acceptance is represented. |
| cost | Fixed-size declaration. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp), [docs/fallback.md](../../../../../fallback.md) |

## B0004

[Lines 15–26](../../../../../../include/crown/planner/fallback.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L26:sha256:5c6eccff5280ddaf8cd34326a0b42e8897601aa3553121f189b04b68cf1def3f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the exact set evaluator and its real materialization/publication boundary. |
| inputs / outputs | Profile contains static text plus QueryClass and Reason; cold admission fills the actual class/reason. |
| invariants | Full-row serial source events, materialized distinct answers and endpoint deltas are explicit. Delay text disclaims constant delay; height text disclaims CROWN/GHD certification. Defaults are not classification evidence before admit. |
| ownership | String views refer to static literals; profile copies retain no caller strings or native account. |
| failure | Constructing the POD profile does not validate a query or catch a failure. |
| cost | Fixed descriptor copies; the named eager evaluation/state/cleanup retain their actual separate runtime costs. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp), [docs/fallback.md](../../../../../fallback.md) |

## B0005

[Lines 27–32](../../../../../../include/crown/planner/fallback.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L32:sha256:1466e2aff2feec6f615d5ae49765689de4d67b89761eaf5ca85db744bd28c6c0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return optional checked advisory logical row bounds without implying peak-memory or CPU bounds. |
| inputs / outputs | source_rows, assignments_upper, output_rows_upper and state_rows_upper are optional uint64 values with overflow/advisory flags. |
| invariants | Unknown arithmetic remains disengaged; overflow marks arithmetic loss. State means committed sources plus answers, excluding private images, journals and peak bytes. |
| ownership | Inline optional values copied out of Plan; no borrowed count span escapes. |
| failure | Estimates are not allocation admission or a promise of feasible memory. |
| cost | Fixed result descriptor; calculating it scans tables and original atom factors. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp), [docs/fallback.md](../../../../../fallback.md) |

## B0006

[Lines 33–37](../../../../../../include/crown/planner/fallback.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L37:sha256:8d4f3adcb3c98036e0f0c4d8474057e85c914d6513cd14ddedb3b163f9995e93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep selected metadata, structural recognition and source lowering budgets separate. |
| inputs / outputs | Limits carries one million selected cold units by default, RecognitionLimits and PhysicalLimits. |
| invariants | A finite work field is not an elapsed-time, validation, allocation or native account cap; recognition exhaustion must not invent a class. |
| ownership | Caller-owned inline policy passed synchronously to admission. |
| failure | Exhausted selected or bounded recognition/lowering work is reported by admit as fallback_work_limit. |
| cost | Fixed policy object; each called mechanism retains its documented cost. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp), [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp) |

## B0007

[Lines 38–45](../../../../../../include/crown/planner/fallback.hpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L45:sha256:01cd911faea0f3718792c10ecd33a719dc0415f144e30c1a34adced8a986477a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a cold immutable explicit fallback plan with shared copy lifetime. |
| inputs / outputs | Plan declaration and noexcept default copy operations; only the later friend factory constructs Data. |
| invariants | The source coordinator retains all catalog constraints/backends, but its constant query identity/tree certifies only that coordinator. Copies preserve the actual original query/class independently. |
| ownership | Ordinary compiler shared-const Data owner; this is not native original-account storage. |
| failure | Copying a valid handle is noexcept; final owner destruction releases ordinary metadata. |
| cost | O(1) shared handle copy; final graph/string destruction has real payload cost. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp), [docs/fallback.md](../../../../../fallback.md) |

## B0008

[Lines 46–46](../../../../../../include/crown/planner/fallback.hpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L46:sha256:f8c2020b9061d5c7c5f57329c678a51c2097149b23c9584670e9b5f53064fcb2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve both Plan handles when syntactically moving an immutable cold owner. |
| inputs / outputs | Plan rvalue in; destination shares other.data_ without clearing the source. |
| invariants | Moved-from Plan remains a valid admitted handle; no null default owner is introduced. |
| ownership | Shared immutable compiler ownership is copied. |
| failure | Noexcept handle construction. |
| cost | O(1) shared reference count operation. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |

## B0009

[Lines 47–47](../../../../../../include/crown/planner/fallback.hpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L47:sha256:2d0b27e62f918ab627b414815b74bd71f2200b29736177e6bdd95ae131478f2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign an immutable Plan while retaining validity of the source handle. |
| inputs / outputs | Plan rvalue in; destination replaces its shared Data and returns itself. |
| invariants | Assignment copies the source shared owner, including self-assignment safety; original-source handle remains valid. |
| ownership | Previous destination Data may be destroyed if this releases its final shared owner. |
| failure | Noexcept shared-pointer assignment; no admission/evaluation performed. |
| cost | O(1) handle operation plus possible destruction of prior compiler metadata/payloads. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |

## B0010

[Lines 48–63](../../../../../../include/crown/planner/fallback.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L63:sha256:9af608da5218b309285fb25a9c00233a8a889b5bf8e2c4da8292134d11a70627
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact original metadata and genuine source coordinator, and declare count-based estimates. |
| inputs / outputs | Live Plan exposes originalcatalog/query/source_only/structure/profile by const lvalue reference, spent work by value, and estimates from one count per physical table. |
| invariants | Borrowing getters from rvalues is deleted. Original ordered head/atoms remain available separately from the zero-atom coordinator. Alias factors repeat per occurrence; unused physical sources still count once in source_rows. |
| ownership | References borrow shared Data for the Plan lifetime. estimates retains no caller span. Private Data is incomplete outside the implementation. |
| failure | Valid getters are noexcept; wrong estimate width throws fallback_admission and arithmetic overflow is explicit in the result. |
| cost | Getters O(1); estimate calculation O(catalog tables + original occurrences), without estimating peak bytes or all nested-loop prefix work. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp), [docs/fallback.md](../../../../../fallback.md) |

## B0011

[Lines 64–64](../../../../../../include/crown/planner/fallback.hpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L64:sha256:f4b25bc173383cb1cf8f6ce915a6b76453968424f051e5f2ec3b3670d5037f85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish only a completed private immutable Data owner through Plan construction. |
| inputs / outputs | Factory-created shared_ptr&lt;const Data&gt; in; nonempty admitted Plan handle out. |
| invariants | Constructor is private; public callers cannot manufacture a mutable or default empty Plan. |
| ownership | Moves the factory local shared handle into Plan without copying payloads. |
| failure | No additional allocation in this constructor; factory construction failures occur before entry. |
| cost | O(1) handle move. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp) |

## B0012

[Lines 65–79](../../../../../../include/crown/planner/fallback.hpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L79:sha256:2f5526b04a87f0076b04f820ffac683c3b758a2d672a0bb4bf36bc33b7d56d4f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the sole explicit general-CQ admission boundary and its honest ownership/resource contract. |
| inputs / outputs | Catalog, Query, optional PhysicalOptions and Limits in; immutable Plan out. Friend factory owns the private shared Data. |
| invariants | Preserves original constants, ignored/repeated terms, self-aliases and ordered/repeated/Boolean head. All three real structural classes are accepted explicitly; resource exhaustion is not a class. No SQL or GHD/CROWN extension is implied. |
| ownership | Factory copies ordinary cold Catalog/Query, owns genuine source-only lowering, and leaves caller DTOs unchanged. Runtime must freeze original metadata into its own original query account. |
| failure | Typed invalid-input errors become fallback_admission; selected/recognition/lowering resource exhaustion becomes fallback_work_limit; allocation exceptions keep their native type. |
| cost | Separate selected metadata/string/literal-byte, GYO and lowering limits; validation, copies, identity work, allocations and destruction retain actual additional costs. |
| Design | [include/crown/planner/fallback.hpp](../../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../../src/planner/fallback.cpp), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp), [Refactor.md](../../../../../../Refactor.md), [docs/fallback.md](../../../../../fallback.md) |
