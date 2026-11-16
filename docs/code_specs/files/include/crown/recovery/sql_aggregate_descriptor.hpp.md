# `include/crown/recovery/sql_aggregate_descriptor.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `36d25bcbf849144bd588e5e344a784874495a270c5c9bede5c96f76b2200c3b7`. 71 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 7–11](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L7) | Type/record definition: struct DescriptorLimits |  · [reviewed contract](#b0002) |
| [B0003 · 12–14](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L12) | Explanatory comments or spacing. | source comment (unverified): // Cold receiving limits, separate from the stored operational runtime policy. · [reviewed contract](#b0003) |
| [B0004 · 15–19](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L15) | Type/record definition: struct AdmissionLimits | source comment (unverified): // Cold receiving limits, separate from the stored operational runtime policy. · [reviewed contract](#b0004) |
| [B0005 · 20–24](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L20) | Type/record definition: struct InspectedDescriptor | source comment (unverified): // Borrow the exact supplied frame. · [reviewed contract](#b0005) |
| [B0006 · 25–28](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L25) | Explanatory comments or spacing. | source comment (unverified): // Immutable genuine compiler/native metadata and original operational policy. · [reviewed contract](#b0006) |
| [B0007 · 29–51](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L29) | Type/record definition: class Descriptor | returns bool(data_); source comment (unverified): // Immutable genuine compiler/native metadata and original operational policy. · [reviewed contract](#b0007) |
| [B0008 · 52–56](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L52) | Type/record definition: struct Admitted | source comment (unverified): // Genuine empty/static state at C0. · [reviewed contract](#b0008) |
| [B0009 · 57–71](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L57) | declares values/defaults or compile-time conditions. | source comment (unverified): // Both factories require capture_changes=true and preserve all supplied normal · [reviewed contract](#b0009) |

## B0001

[Lines 1–6](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace detail { class DescriptorFactory; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward-declare the internal factory type used by the later private \`Descriptor\` construction boundary. |
| inputs / outputs | The declaration names \`recovery::sql_aggregate::detail::DescriptorFactory\` and provides no methods or object. The later \`Descriptor\` declaration grants that type friendship. |
| invariants | This declaration alone grants no construction access. A separate friend and private constructor form the later factory boundary; neither an editable DTO nor this forward declaration creates a genuine descriptor. |
| ownership | No storage or owner is created here. A factory-produced \`Descriptor\` later retains shared immutable data, including admitted program/native objects, options, frame bytes, and digest under its receiving account. |
| failure | There is no runtime failure at declaration. Factory methods separately validate admission/rebind inputs and may propagate image, contract, or supplied-account resource failures. |
| cost | No runtime work occurs at declaration. Factory methods separately run compiler/codec checks and retain account-owned metadata; their grants and allocations are not properties of this forward declaration. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp §private factory](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [src/recovery/sql_aggregate_descriptor.cpp §DescriptorFactory](../../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/sql_aggregate_descriptor.md §genuine descriptor](../../../../../sql_aggregate_descriptor.md) |

## B0002

[Lines 7–11](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DescriptorLimits {
  ImageLimits image;
  std::uint64_t cbor_items = 1000000;
  std::size_t cbor_depth = 128;
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set finite descriptor wire/CBOR admission caps independent from compiler and runtime grants. |
| inputs / outputs | \`image\` bounds frame bytes, shared byte work, table/row/field/scalar dimensions; \`cbor_items\` and \`cbor_depth\` bound the CBOR preflight. |
| invariants | Limits only admit or reject descriptor representations; they do not set the stored operational runtime policy. |
| ownership | The value is a plain caller-owned cap; factories copy no external buffer through this type. |
| failure | Excessive depth, item count, frame size or image work produces the fixed image-limit path before DOM admission. |
| cost | Fixed-size option values; no per-request work by the type itself. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../../sql_aggregate_descriptor.md) |

## B0003

[Lines 12–14](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L14:sha256:791ed89d640ea73ffd35b30b73c18ab43c75fd3ed298447f374d1165514cea9a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Cold receiving limits, separate from the stored operational runtime policy. The binder/lowerer work counters must be finite. Their ordinary compiler/DOM workspace is separate from account-owned retained metadata and runtime state. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_descriptor.hpp lines 10-16; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_descriptor.hpp.md](sql_aggregate_descriptor.hpp.md), [docs/sql_aggregate_descriptor.md](../../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md) |

## B0004

[Lines 15–19](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AdmissionLimits {
  DescriptorLimits descriptor;
  frontend::SqlAggregateBindOptions binding;
  PhysicalLimits lowering;
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle the descriptor cap with finite receiving binder/lowerer host grants. |
| inputs / outputs | \`descriptor\` bounds frame and schema, \`binding\` supplies real SQL binder caps, and \`lowering\` supplies host physical work and identity limits. |
| invariants | These receiving caps are distinct from the preserved normal runtime and physical producer policies stored in the descriptor. |
| ownership | Caller owns this small value for a factory call; parser/compiler workspace follows their ordinary conventions. |
| failure | Missing finite work limits or recursion above the supported cap is rejected before the receiving compiler/lowerer path. |
| cost | Fixed policy data; actual parse and lowering costs occur in their factory phases. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../../sql_aggregate_descriptor.md) |

## B0005

[Lines 20–24](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InspectedDescriptor {
  std::string_view binding_image, recipe; // Borrow the exact supplied frame.
  Hash sha256; // Whole-frame identity used by a separately selected root.
  ImageStatistics statistics;
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return fixed identity/statistics plus borrowed binding and recipe spans from wire inspection. |
| inputs / outputs | \`binding_image\` and \`recipe\` refer to exact subranges of the supplied CROWNAD2 frame; \`sha256\` hashes the full frame. |
| invariants | The spans are not copied and do not authorize either a root selection or a native program import. |
| ownership | The caller must keep the original frame bytes alive and unchanged while using either view. |
| failure | Invalid wire never yields the view object; bounded parse errors use ImageFailure. |
| cost | Fixed metadata and string_view values only; successful inspector storage is allocation-free under the covered C++ new seam. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../../sql_aggregate_descriptor.md) |

## B0006

[Lines 25–28](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L28:sha256:a2801347966dad0f9d4265dc421c7a59ff4784d4517f89cc02a84fb2e21103ff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Immutable genuine compiler/native metadata and original operational policy. Sharing retains their receiving account. No DTO constructor/import path exists; file selection, durable output and source-row recovery are separate boundaries. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_descriptor.hpp lines 23-30; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_descriptor.hpp.md](sql_aggregate_descriptor.hpp.md), [docs/sql_aggregate_descriptor.md](../../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md) |

## B0007

[Lines 29–51](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Descriptor {
  struct Data;
 public:
  Descriptor() noexcept = default;
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] const frontend::SqlAggregateProgram& program() const &;
  const frontend::SqlAggregateProgram& program() const && = delete;
  [[nodiscard]] const CompiledProgram& native_program() const &;
  const CompiledProgram& native_program() const && = delete;
  [[nodiscard]] const runtime::weighted::Binding& native_binding() const &;
  const runtime::weighted::Binding& native_binding() const && = delete;
  [[nodiscard]] const runtime::sql_aggregate::Options& options() const &;
  const runtime::sql_aggregate::Options& options() const && = delete;
  [[nodiscard]] const Hash& sha256() const &;
  const Hash& sha256() const && = delete;
  [[nodiscard]] std::string_view bytes() const &;
  std::string_view bytes() const && = delete;
 private:
  friend class detail::DescriptorFactory;
  explicit Descriptor(std::shared_ptr<const Data> data) noexcept : data_(std::move(data)) {}
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold immutable authentic compiler/native metadata, original runtime policy, exact descriptor bytes and full-frame identity. |
| inputs / outputs | Accessors expose the genuine SQL program, compiled native program, weighted binding, normal options, frame hash and borrowed bytes. |
| invariants | Only the private factory can build Data; deleted rvalue accessors prevent obtaining borrowed references/views from a temporary handle. |
| ownership | Copies share the Data owner; all returned references and the byte view require a surviving Descriptor copy. Final owner release frees account-owned metadata and bytes. |
| failure | An empty default handle throws the fixed binding failure when a data accessor is used; the bool conversion only reports whether Data exists. |
| cost | One account-funded shared Data control/object plus the retained frame vector; copies share rather than duplicate the payload. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../../sql_aggregate_descriptor.md) |

## B0008

[Lines 52–56](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Admitted {
  Descriptor descriptor;
  runtime::SqlAggregateRuntime runtime; // Genuine empty/static state at C0.
  ImageStatistics statistics; // Codec byte visits only; compiler grants are separate.
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an admitted descriptor beside a genuine runtime initialized at C0 and codec byte/work statistics. |
| inputs / outputs | The result groups the immutable Descriptor, move-only \`SqlAggregateRuntime\`, and \`ImageStatistics\`; row count in descriptor stats is zero. |
| invariants | The runtime starts from the authentic empty/static source route, not imported checkpoint rows or replayed epochs. |
| ownership | Each owner follows its own receiving-account lifetime; moving the result transfers handles without cloning the byte frame. |
| failure | Factory failure returns no Admitted object; local runtime and account-owned partial objects unwind normally. |
| cost | Contains handles/statistics only; construction costs are those of the descriptor and genuine runtime factories. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../../sql_aggregate_descriptor.md) |

## B0009

[Lines 57–71](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp#L57); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Admitted admit_into(const resource::MemoryAccount&,
    frontend::SqlAggregateProgram,const FreeConnexTree&,const PhysicalOptions&,
    runtime::sql_aggregate::Options,const AdmissionLimits& = {});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit an actual compiler-owned SQL aggregate program/tree/options into a receiving-account C0 runtime and descriptor. |
| inputs / outputs | Inputs are a genuine \`SqlAggregateProgram\`, a supplied \`FreeConnexTree\`, original \`PhysicalOptions\`, original SQL aggregate \`Options\`, and finite host/descriptor caps. |
| invariants | Requires a valid program and \`capture_changes=true\`; preserves the original tree and stored policies without proving that the tree is minimum-height. |
| ownership | The receiving account funds runtime metadata, retained descriptor bytes and shared metadata; the caller retains the original inputs it passed by reference. |
| failure | Image limits/invalid capture policy fail admission; genuine binder/lowerer/runtime and account exceptions propagate without a new catch or retry. |
| cost | Cold work includes finite-cap validation and genuine runtime construction; when producer work/identity limits are already finite and no greater than host caps, runtime lowering itself supplies the finite bound, otherwise a finite host lowering pass is also performed. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [src/recovery/sql_aggregate_descriptor.cpp](../../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../../sql_aggregate_descriptor.md) |

```text
[[nodiscard]] InspectedDescriptor inspect_descriptor(std::string_view,DescriptorLimits = {});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect a complete CROWNAD2 frame and return identity plus borrowed binding/recipe bytes. |
| inputs / outputs | The input is an immutable byte view; the return contains exact subviews, full-frame hash and wire byte/work counts. |
| invariants | Validates magic/version/reserved bits, lengths, protected prefix/body hashes, exact end, and both bounded CBOR documents before returning; it does not bind SQL or construct a runtime. |
| ownership | All returned views borrow the input bytes. The inspector creates no account-owned owner and does not retain a view. |
| failure | Bad frame/CBOR/limits fail with fixed ImageFailure before any DOM allocation. |
| cost | Linear envelope hashing/parsing plus charged map-key comparison extents under shared finite limits; no covered C++ allocation on success. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [src/recovery/sql_aggregate_cbor.hpp](../../../../../../src/recovery/sql_aggregate_cbor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../../sql_aggregate_descriptor.md) |

```text
[[nodiscard]] Admitted rebind_into(const resource::MemoryAccount&,std::string_view,
    const AdmissionLimits& = {});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct and authenticate a descriptor through the original SQL/catalog/compiler factories. |
| inputs / outputs | Takes a receiving account, exact stored descriptor bytes and finite descriptor/binder/lowerer caps; returns the re-created C0 runtime and authentic descriptor. |
| invariants | Preflight precedes DOM parsing; original SQL, catalog, typed parameters and AVG are rebound; exact binding image and complete regenerated recipe/frame bytes must match. |
| ownership | The input frame is borrowed only during the call; returned metadata/bytes and runtime are owned through the receiving account. |
| failure | Malformed wire fails before DOM; unsupported original SQL/tree/policies fail through binding/lowering/runtime paths; account failures propagate and partial owners unwind. |
| cost | Cold work includes bounded wire passes, compiler/DOM work, and one or conditionally two deterministic lowerings; counters exclude ordinary DOM/compiler CPU and allocator work. |
| Design | [include/crown/recovery/sql_aggregate_descriptor.hpp](../../../../../../include/crown/recovery/sql_aggregate_descriptor.hpp), [src/recovery/sql_aggregate_descriptor.cpp](../../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/sql_aggregate_descriptor.md §What is authenticated](../../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../../sql_aggregate_descriptor.md) |
