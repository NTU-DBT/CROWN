# `include/crown/recovery/sql_rows_descriptor.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `946d8884e18ffa544d165469c40ddf15b08110073e76fcab4aec49ddf79693aa`. 72 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Exact shared wire/CBOR limits POD, with no program/native authority. · [reviewed contract](#b0001) |
| [B0002 · 13–17](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L13) | Type/record definition: struct AdmissionLimits | source comment (unverified): // Cold receiving limits, separate from the stored operational runtime policy. · [reviewed contract](#b0002) |
| [B0003 · 18–22](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L18) | Type/record definition: struct InspectedDescriptor | source comment (unverified): // Borrow the exact supplied frame. · [reviewed contract](#b0003) |
| [B0004 · 23–30](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L23) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Immutable genuine compiler/native metadata and original operational policy. · [reviewed contract](#b0004) |
| [B0005 · 31–31](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L31) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns bool(data_) · [reviewed contract](#b0005) |
| [B0006 · 32–47](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L32) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 48–48](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L48) | Callable definition: explicit Descriptor(std::shared_ptr&lt;const Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0007) |
| [B0008 · 49–51](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L49) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 52–56](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L52) | Type/record definition: struct Admitted | source comment (unverified): // Genuine empty/static state at C0. · [reviewed contract](#b0009) |
| [B0010 · 57–72](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L57) | declares values/defaults or compile-time conditions. | source comment (unverified): // Admission requires retained binding bytes; cold rebind opts in explicitly. · [reviewed contract](#b0010) |

## B0001

[Lines 1–12](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:a8f8e75f178719ed009ebde300758e68f0931b4b4328b50b8ac54dc7d27a3dba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the exact shared neutral DescriptorLimits alias. |
| inputs / outputs | Include row records and aggregate descriptor headers; alias sql_aggregate::DescriptorLimits and forward-declare own DescriptorFactory. |
| invariants | Only wire/CBOR bounds are shared; row program/runtime/factory remain separately typed. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_descriptor.hpp](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) |

## B0002

[Lines 13–17](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L17:sha256:75575de6b25f09ab69e7d759f01932107b500181016021283d597b475522dc5d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group the three independent cold receiving limit domains. |
| inputs / outputs | AdmissionLimits contains DescriptorLimits, SqlRowsBindOptions and PhysicalLimits with their existing defaults. |
| invariants | The declaration neither enforces finite counters nor spends a grant. Stored runtime/output policy is passed separately to factories. |
| ownership | Members retain ordinary bind-option metadata/value owners; no runtime/frame owner is added. |
| failure | Default/member construction, copy and allocation rules apply; no custom check. |
| cost | Construct/copy declared members only; option vectors may allocate on copy, but no bind/lower/image traversal executes. |
| Design | [include/crown/recovery/sql_rows_descriptor.hpp](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) |

## B0003

[Lines 18–22](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L22:sha256:b5ec6980ef7fd078820806599dc8d4fc0ec811594e05412864aa84a1e1e97ba8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry borrowed descriptor sections, whole-frame hash and inspection work counters. |
| inputs / outputs | InspectedDescriptor fields are binding_image and recipe string_views, fixed Hash sha256 and ImageStatistics. |
| invariants | No checks occur in this DTO; only inspect_descriptor populates these from validated framing/CBOR. SQL/native identity is still separate. |
| ownership | Views require the original unchanged frame backing; hash/statistics are copied values. |
| failure | No custom validation/error translation. |
| cost | Fixed pointer/length/scalar/array storage; no DOM, parse/hash or allocation. |
| Design | [include/crown/recovery/sql_rows_descriptor.hpp](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) |

## B0004

[Lines 23–30](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L30:sha256:b3d371cbb21a27440dd94a7d2fd45b449c70d9bc28888f1788317a998df75633
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare Descriptor as an empty-default shared immutable handle. |
| inputs / outputs | Forward-declare private Data, open Descriptor and default its empty noexcept constructor. |
| invariants | Default construction creates no authority; operator bool/getters/factory are specified separately. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_descriptor.hpp](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) |

## B0005

[Lines 31–31](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:97dc45bb9885bdd0388f6f214da7c7b65592f7223005ba157410f3c56773a027
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe handle presence without revalidation or allocation. |
| inputs / outputs | This Descriptor handle → bool(data_). |
| invariants | Presence only; no validation. |
| ownership | No ownership change. |
| failure | noexcept. |
| cost | Fixed pointer check; no allocation. |
| Design | [include/crown/recovery/sql_rows_descriptor.hpp](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) |

## B0006

[Lines 32–47](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L47:sha256:cb1d857aed28c5ef5ecf79d52ff73b6f4caa8acd0bba9f90f50f46cce045b08b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare lifetime-restricted Descriptor metadata getters. |
| inputs / outputs | Declare program/native/binding/normal/output policy/hash/byte getters for const lvalues and delete corresponding const-rvalue overloads; grant factory friendship. |
| invariants | Declarations alone perform no access or validation; live nonempty owner is required by implementations. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_descriptor.hpp](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) |

## B0007

[Lines 48–48](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L48:sha256:7863c71230fec1724eda8eaaa8da324dfe1876a84caf393887217d1018af5fed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share a factory-owned immutable descriptor control; public DTOs cannot construct it. |
| inputs / outputs | Shared const Data pointer → Descriptor handle. |
| invariants | Private constructor does not inspect its input; factory friendship is the calling boundary. |
| ownership | Moves control pointer. |
| failure | Declared noexcept. |
| cost | Fixed pointer move; no allocation. |
| Design | [include/crown/recovery/sql_rows_descriptor.hpp](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) |

## B0008

[Lines 49–51](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L51:sha256:c6de740edb502c13c1d8640c9c13c9994e890fe1d764429183d2efa996522ba6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare Descriptor storage and its private checked accessor. |
| inputs / outputs | Declare data() and shared_ptr&lt;const Data&gt; data_, then close Descriptor. |
| invariants | The private accessor implementation rejects empty handles; member declaration itself does not. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_descriptor.hpp](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) |

## B0009

[Lines 52–56](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L56:sha256:c0018432ce35ecb811bd3051d30710de178cc8a01c7a425400d81415a6289682
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the factory-created descriptor, C0 runtime and codec statistics together. |
| inputs / outputs | Admitted aggregates Descriptor, SqlRowsRuntime and ImageStatistics. |
| invariants | The struct constructor performs no additional admission. The actual factory must supply genuine matching descriptor/runtime members. |
| ownership | Descriptor shares immutable receiving-owned metadata; runtime is the genuine move-only owner; statistics are values. |
| failure | Member construction/move/teardown rules apply; this struct adds no checks or catch. |
| cost | Only member ownership transfer/layout; factory construction/hash/codec costs belong to the caller implementation. |
| Design | [include/crown/recovery/sql_rows_descriptor.hpp](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) |

## B0010

[Lines 57–72](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp#L57); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L72:sha256:bf43a87ac67fbe894b7a293e9f5bca2d97e950ac6aee0927642db39ec5e285e3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare genuine descriptor admission, inspection and cold-rebind APIs. |
| inputs / outputs | Declare admit_into(account,program,tree,physical,normal,output,limits), inspect_descriptor(bytes,limits) and rebind_into(account,bytes,limits). |
| invariants | No operation runs in this span. Admission requires retained compiler binding bytes; cold rebind explicitly requests retention while preserving supplied normal/output policy. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_descriptor.hpp](../../../../../../include/crown/recovery/sql_rows_descriptor.hpp) |
