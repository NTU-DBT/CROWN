# `include/crown/recovery/sql_rows_records.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/sql_rows_records.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `051eee1308939191e50f75568b0f72a9c30d86c7d6aec200c39506111c0a5fd7`. 130 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–24](../../../../../../include/crown/recovery/sql_rows_records.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // These are transport data only; aliases convey no aggregate/runtime authority. · [reviewed contract](#b0001) |
| [B0002 · 25–28](../../../../../../include/crown/recovery/sql_rows_records.hpp#L25) | Type/record definition: enum class RejectReason : std::uint8_t | source comment (unverified): // Stable plain-row semantic allowlist; resource/contract failures have no tag. · [reviewed contract](#b0002) |
| [B0003 · 29–35](../../../../../../include/crown/recovery/sql_rows_records.hpp#L29) | Type/record definition: struct Reject |  · [reviewed contract](#b0003) |
| [B0004 · 36–37](../../../../../../include/crown/recovery/sql_rows_records.hpp#L36) | Explanatory comments or spacing. | source comment (unverified): // Borrow the genuine prepared SQL presentation through encode(). No snapshots, · [reviewed contract](#b0004) |
| [B0005 · 38–43](../../../../../../include/crown/recovery/sql_rows_records.hpp#L38) | Type/record definition: struct RowEpochView | source comment (unverified): // Borrow the genuine prepared SQL presentation through encode(). No snapshots, · [reviewed contract](#b0005) |
| [B0006 · 44–44](../../../../../../include/crown/recovery/sql_rows_records.hpp#L44) | Type/record definition: enum class Kind : std::uint8_t |  · [reviewed contract](#b0006) |
| [B0007 · 45–45](../../../../../../include/crown/recovery/sql_rows_records.hpp#L45) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 46–50](../../../../../../include/crown/recovery/sql_rows_records.hpp#L46) | Type/record definition: struct RowInfo |  · [reviewed contract](#b0008) |
| [B0009 · 51–57](../../../../../../include/crown/recovery/sql_rows_records.hpp#L51) | Type/record definition: struct Inspected |  · [reviewed contract](#b0009) |
| [B0010 · 58–60](../../../../../../include/crown/recovery/sql_rows_records.hpp#L58) | Explanatory comments or spacing. | source comment (unverified): // Immutable owned record bytes. A frame is neither a durable receipt nor native · [reviewed contract](#b0010) |
| [B0011 · 61–76](../../../../../../include/crown/recovery/sql_rows_records.hpp#L61) | Type/record definition: class Frame | returns {bytes_.data(),bytes_.size()}; info_; source comment (unverified): // Immutable owned record bytes. A frame is neither a durable receipt nor native · [reviewed contract](#b0011) |
| [B0012 · 77–79](../../../../../../include/crown/recovery/sql_rows_records.hpp#L77) | Explanatory comments or spacing. | source comment (unverified): // One owned frame and two flat view arrays; TEXT and source names borrow the · [reviewed contract](#b0012) |
| [B0013 · 80–96](../../../../../../include/crown/recovery/sql_rows_records.hpp#L80) | Type/record definition: class DecodedInput | returns frame_; source comment (unverified): // One owned frame and two flat view arrays; TEXT and source names borrow the · [reviewed contract](#b0013) |
| [B0014 · 97–113](../../../../../../include/crown/recovery/sql_rows_records.hpp#L97) | declares values/defaults or compile-time conditions. | source comment (unverified): // Durable codecs require an explicit retain_binding_image=true compilation. · [reviewed contract](#b0014) |
| [B0015 · 114–128](../../../../../../include/crown/recovery/sql_rows_records.hpp#L114) | Type/record definition: class WalCursor | returns state_; source comment (unverified): // Fixed candidate state publishes only after complete validation. Actual file · [reviewed contract](#b0015) |
| [B0016 · 129–130](../../../../../../include/crown/recovery/sql_rows_records.hpp#L129) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::recovery::sql_rows · [reviewed contract](#b0016) |

## B0001

[Lines 1–24](../../../../../../include/crown/recovery/sql_rows_records.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L24:sha256:c1bfa1d06d7bc4c18d48a8ca500b87570bf42d6b4ea9ffb0bbab0bd3adcdfdba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare shared transport POD aliases and the row runtime dependency. |
| inputs / outputs | Include aggregate transport data and sql_rows runtime headers; alias Hash/Id/Binding/headers/progress/Input/Commit/record+scan limits/PendingInput/WalState. |
| invariants | Aliases import no aggregate Program, runtime, descriptor or admission authority. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0002

[Lines 25–28](../../../../../../include/crown/recovery/sql_rows_records.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L28:sha256:2cad3ec962c36bd290c1bfbed6e5c32e3783a18eb9edb42284182c8838012d82
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate five stable semantic rejection reasons for the plain-row wire family. |
| inputs / outputs | Define RejectReason values 0=weight_mismatch, 1=source_overflow, 2=unique_violation, 3=foreign_key_violation, 4=annotation_overflow. |
| invariants | No resource/contract failure value is declared. Enum construction alone does not check that an integer is one of these values. |
| ownership | One uint8-backed value; no borrowed data or owner. |
| failure | No executable validation path in the enum. |
| cost | Compile-time value/type declaration; no runtime work or allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0003

[Lines 29–35](../../../../../../include/crown/recovery/sql_rows_records.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L35:sha256:3bdd50009d1b80c8c184e92e40cab299c856f903c87066d7c36880eb1cbe8018
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the input identity, I/C frontiers and selected semantic Reject reason. |
| inputs / outputs | Fields are input_ordinal, input_sha256, command_sequence I, physical_sequence C and reason, with default equality. |
| invariants | Editable DTO only: hex, ordinal, I/C and reason-domain checks are performed by valid(Reject), not by this struct. |
| ownership | Own fixed scalar/array values; no frame/runtime reference. |
| failure | No custom validation; default value initialization/equality do not throw. |
| cost | Fixed field layout/copy/equality; no parse/hash/native work or allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0004

[Lines 36–37](../../../../../../include/crown/recovery/sql_rows_records.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L37:sha256:d15b92b0346b45e2486c7da7fa7542a29ca5512db95243cec1fe5f3d40d74330
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0005

[Lines 38–43](../../../../../../include/crown/recovery/sql_rows_records.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L43:sha256:646cd4ff524a352025858977f57b97fb8ca6bf9104e821687f49539cbf6ae500
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry borrowed prepared SQL output and the epoch metadata needed by encode. |
| inputs / outputs | Fields are generation, disposed input I, native C, input_sha256, source-changed flag and const PreparedBatch pointer. |
| invariants | No defaults or validation: caller must initialize all fields and keep an active output-prepared token through encoding. The declaration does not check token identity/sequence. |
| ownership | Only fixed metadata is copied; output pointer does not retain its token/runtime. |
| failure | No executable validation path. |
| cost | Fixed DTO layout/copy; no output decode, scratch, sort or allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0006

[Lines 44–44](../../../../../../include/crown/recovery/sql_rows_records.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:f1d825436b2c70b3f50af42efd6c4e4b19b07985c85087723320d5df3e3b543a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign the six stable row-record kind tags. |
| inputs / outputs | Kind values are 0 wal_header, 1 input, 2 commit, 3 reject, 4 sink_header, 5 row_epoch. |
| invariants | The encoder/decoder enforce valid tags and ordinal rules; this enum declaration does not. |
| ownership | One uint8-backed value. |
| failure | No executable validation path. |
| cost | Compile-time declaration only. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0007

[Lines 45–45](../../../../../../include/crown/recovery/sql_rows_records.hpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L45:sha256:3e9af7a9b349f218c610ef9026226dc4ffd68b7ce967f7894236b0d8a2996816
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the closed row payload input variant. |
| inputs / outputs | PayloadView is variant&lt;WalHeader,InputView,Commit,Reject,SinkHeader,RowEpochView&gt;. |
| invariants | Variant order matches Kind values; constructing a payload does not validate it. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0008

[Lines 46–50](../../../../../../include/crown/recovery/sql_rows_records.hpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L50:sha256:b08f64c2a5d405a99b5467f6f505c43cc58c27e5bc51f8183e5152080181917f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry inspected SQL row-epoch metadata without output row ownership. |
| inputs / outputs | Fixed fields hold generation, input I, native C, row count, input SHA and source/output-changed flags. |
| invariants | Defaults are zero/false; the type itself does not check I/C, hash, output_changed or actual delta correctness. |
| ownership | Own scalar/array values, no cells/token/frame borrow. |
| failure | No custom validation path. |
| cost | Fixed layout/copy; no parse/hash/sort or allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0009

[Lines 51–57](../../../../../../include/crown/recovery/sql_rows_records.hpp#L51); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L57:sha256:743ebc1b9b4ffa4088e27ce2a07f49c2a46ffc821a3c1f883fd99b233c940427
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one parsed row-record tag, payload summary, body hash and codec statistics. |
| inputs / outputs | Inspected contains Kind, ordinal, body_sha256, ImageStatistics and variant&lt;WalHeader,InputInfo,Commit,Reject,SinkHeader,RowInfo&gt;. |
| invariants | The carrier adds no checks. A default/manually edited Inspected is not a validated frame or native/file authority. |
| ownership | Payload alternatives contain fixed transport summaries; this object owns no wire bytes or SQL rows. |
| failure | Member/variant operations apply; no custom validation/error translation. |
| cost | Fixed-size member storage/copy/move; no parser, hash, native call or heap buffer. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0010

[Lines 58–60](../../../../../../include/crown/recovery/sql_rows_records.hpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L60:sha256:e6eb61a2cd95b19fe5d2facc97c3b0fa2d0ca61198adf62dc207759de3f44e1d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0011

[Lines 61–76](../../../../../../include/crown/recovery/sql_rows_records.hpp#L61); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L76:sha256:c6f712a4d00c298fc84fe8a06c60d14314012c3344e9ff41188e4645d1c0dc9e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one immutable accounted row-family frame with move-only byte/info borrows. |
| inputs / outputs | Private Frame(ImageVector&lt;char&gt;,Inspected) moves one byte owner and fixed record metadata into Frame; lvalue bytes()/info() return borrowed views/references. |
| invariants | Copy and rvalue borrows are deleted; move operations are defaulted noexcept. Constructor/getters do not validate checksums/schema/native state; factories establish those premises. |
| ownership | bytes_ owns its receiving buffer; info_ owns fixed metadata. Moves transfer vector storage; borrows require the same live unmoved handle. |
| failure | Declared constructors/moves/accessors are noexcept; no parser/error translation. Final destruction releases the owned vector. |
| cost | Fixed vector/metadata moves and pointer-length/reference getters; no payload traversal/new backing allocation by getters. Teardown releases existing storage. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0012

[Lines 77–79](../../../../../../include/crown/recovery/sql_rows_records.hpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L79:sha256:3e5ccb9d60b4cd0051b36f48cf3829c74d574f93298160e414509cd1aa74a673
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0013

[Lines 80–96](../../../../../../include/crown/recovery/sql_rows_records.hpp#L80); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L96:sha256:659924b1fc78418b638cf3476c6bc4ef963a5adc979440a3f0525a0f51dcb656
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one input frame and flat cell/replacement view arrays; strings borrow that frame. |
| inputs / outputs | Private constructor accepts Frame, Cell vector and SourceReplacement vector; lvalue frame() returns the stored Frame reference, and view() is implemented separately. |
| invariants | Copy and rvalue borrows are deleted; moves are defaulted noexcept. This declaration/inline frame getter performs no schema/frame validation. |
| ownership | Frame owns bytes; flat vectors own Cell/replacement descriptors whose TEXT/row/source views depend on that frame. Moves preserve heap addresses, while old handle borrows must not be retained. |
| failure | Declared constructor/moves/frame accessor are noexcept; view() has its separately specified implementation. |
| cost | Fixed ownership metadata moves/reference getter; no frame/cell traversal or new backing allocation by inline access. Teardown releases the three owned buffers. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0014

[Lines 97–113](../../../../../../include/crown/recovery/sql_rows_records.hpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L113:sha256:6b8ac5b3f49fcc80a3680303221de6dad8e29df102e4dec78892eb500b608e7b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the four record encode/inspect/owned-input entry points. |
| inputs / outputs | Signatures accept genuine SqlRowsProgram, input bytes/payload/ordinal, receiver where ownership is returned and Limits default arguments. |
| invariants | No call occurs in this span. Comments require an explicitly retained binding image; implementations reject missing metadata and define actual schema/work/ownership checks. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0015

[Lines 114–128](../../../../../../include/crown/recovery/sql_rows_records.hpp#L114); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L128:sha256:b7464ba552f0b6640361d0e0f205ee510e0edeeb9642f9acd30795c0b5a548e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own bounded fixed WAL validation state, independent of file locks, native replay and sink delivery. |
| inputs / outputs | ScanLimits initialize retained fixed WalState/limits; feed implementation is separate. |
| invariants | Class declaration itself validates no frame/order/sink state. |
| ownership | Fixed POD state only; no command bytes or heap buffer. |
| failure | Construction/moves declared noexcept; feed failures are separate. |
| cost | Fixed state initialization/move/access; no allocation or native work. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |

## B0016

[Lines 129–130](../../../../../../include/crown/recovery/sql_rows_records.hpp#L129); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L130:sha256:06309b943e20743f40968bc433e2f27f5fe3e2b2150bb979e79d541423a6681e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the protected envelope sizes and close the namespace. |
| inputs / outputs | frame_prefix_size=84 and frame_header_size=148. |
| invariants | Constants describe wire byte extents, not a validated frame. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp) |
