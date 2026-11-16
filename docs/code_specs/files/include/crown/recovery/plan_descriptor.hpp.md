# `include/crown/recovery/plan_descriptor.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/plan_descriptor.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode/decode exact selected-plan descriptor identity for generation recovery.

Snapshot SHA-256: `dab117da52503b11c532319b38c4dcfe4052fdfa466f31f5167baeca0dc9c28c`. 42 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/recovery/plan_descriptor.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–10](../../../../../../include/crown/recovery/plan_descriptor.hpp#L7) | Type/record definition: struct PlanDescriptorLimits |  · [reviewed contract](#b0002) |
| [B0003 · 11–19](../../../../../../include/crown/recovery/plan_descriptor.hpp#L11) | Type/record definition: struct PlanSelection | source comment (unverified): // v2 separates the last actual native switch from later metadata selections. · [reviewed contract](#b0003) |
| [B0004 · 20–23](../../../../../../include/crown/recovery/plan_descriptor.hpp#L20) | Type/record definition: struct EncodedPlanDescriptor |  · [reviewed contract](#b0004) |
| [B0005 · 24–32](../../../../../../include/crown/recovery/plan_descriptor.hpp#L24) | Type/record definition: struct InspectedPlanDescriptor | source comment (unverified): // Fixed selection metadata owns no artifact bytes; the view borrows input. · [reviewed contract](#b0005) |
| [B0006 · 33–42](../../../../../../include/crown/recovery/plan_descriptor.hpp#L33) | declares values/defaults or compile-time conditions. | source comment (unverified): // Fixed metadata and an opaque compiler artifact, with a whole-frame SHA256. · [reviewed contract](#b0006) |

## B0001

[Lines 1–6](../../../../../../include/crown/recovery/plan_descriptor.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose selected-plan metadata and opaque artifact codec. |
| inputs / outputs | Includes root and actual sink header/receipt types. |
| invariants | Native equivalence/checked compiler admission and durable root publication are separate from descriptor structure/hash checks. |
| ownership | No artifact or file owner created by inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action. |
| Design | [include/crown/recovery/plan_descriptor.hpp](../../../../../../include/crown/recovery/plan_descriptor.hpp), [src/recovery/plan_descriptor.cpp](../../../../../../src/recovery/plan_descriptor.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 7–10](../../../../../../include/crown/recovery/plan_descriptor.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PlanDescriptorLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound self-contained plan descriptor bytes/work. |
| inputs / outputs | Frame/artifact each64MiB, work256Mi byte-visits, fields1024. |
| invariants | Current codec charges exactly4*frame bytes conservatively, separately from compiler decode/validation and native rebuild grants; no timing claim. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/plan_descriptor.hpp](../../../../../../include/crown/recovery/plan_descriptor.hpp), [src/recovery/plan_descriptor.cpp](../../../../../../src/recovery/plan_descriptor.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 11–19](../../../../../../include/crown/recovery/plan_descriptor.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PlanSelection {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one generation plan selection with original sink lineage. |
| inputs / outputs | Predecessor root, source/target ImageBinding,new generation/physical/command frontiers, optional immutable sink origin and optional last native-switch epoch. |
| invariants | Codec checks source/catalog/policy continuity and lineage, not native result/source equivalence or actual root selection. v2 last_switch differs from later metadata rotations. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/plan_descriptor.hpp](../../../../../../include/crown/recovery/plan_descriptor.hpp), [src/recovery/plan_descriptor.cpp](../../../../../../src/recovery/plan_descriptor.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const PlanSelection&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare plan selection descriptions. |
| inputs / outputs | Default equality compares predecessor/source/target/frontiers/sink origin/last switch. |
| invariants | Value equality does not prove actual source/native admission, live file/lock ownership or durable acceptance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Bounded fixed-member comparison, no allocation/IO/clock. |
| Design | [include/crown/recovery/plan_descriptor.hpp](../../../../../../include/crown/recovery/plan_descriptor.hpp), [src/recovery/plan_descriptor.cpp](../../../../../../src/recovery/plan_descriptor.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 20–23](../../../../../../include/crown/recovery/plan_descriptor.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EncodedPlanDescriptor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own encoded self-contained descriptor bytes. |
| inputs / outputs | ImageVector&lt;char&gt; plus ImageStatistics. |
| invariants | Contains opaque compiler artifact and fixed checked framing, not an admitted executable plan or selected root lock. |
| ownership | Receiver-account byte buffer; copies deep-copy/allocate, moves transfer actual account/storage. |
| failure | Owning copy may throw; no special aggregate whole-record assignment guarantee; codec prepares privately. |
| cost | O(B) copy allocation, trivial vector block release; no compile/native replay on copy. |
| Design | [include/crown/recovery/plan_descriptor.hpp](../../../../../../include/crown/recovery/plan_descriptor.hpp), [src/recovery/plan_descriptor.cpp](../../../../../../src/recovery/plan_descriptor.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 24–32](../../../../../../include/crown/recovery/plan_descriptor.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InspectedPlanDescriptor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow inspected opaque artifact while copying fixed selection. |
| inputs / outputs | PlanSelection, string_view compiler_artifact and fixed statistics. |
| invariants | Inspection validates metadata/whole-frame SHA, not compiler payload syntax or native authority. Native admission must compare actual checked artifact/source/physical plan. |
| ownership | Artifact view borrows immutable descriptor bytes; fixed metadata owned, no buffer/account/lock retained. |
| failure | Successful copy cannot extend descriptor lifetime; invalid bytes throw before result. |
| cost | Fixed metadata/view copy, no heap allocation; caller must keep artifact backing alive. |
| Design | [include/crown/recovery/plan_descriptor.hpp](../../../../../../include/crown/recovery/plan_descriptor.hpp), [src/recovery/plan_descriptor.cpp](../../../../../../src/recovery/plan_descriptor.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 33–42](../../../../../../include/crown/recovery/plan_descriptor.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] EncodedPlanDescriptor encode_plan_descriptor(const resource::MemoryAccount&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode fixed selection and opaque nonempty compiler artifact. |
| inputs / outputs | Account/PlanSelection/stable artifact bytes/finite limits. |
| invariants | Validate predecessor→next generation/frontier/last-switch, exact logical source-policy continuity, sink-origin/anchor framing and bounds. Never compiles/executes artifact. |
| ownership | One exact-size funded output vector copies artifact+metadata; source view only borrowed through call. |
| failure | ImageFailure limit/work/binding/corrupt or account/OOM frees private result; no files selected. |
| cost | O(frame bytes) metadata/artifact copy/SHA; precharge4B before resize; fixed overhead932+optional112/64/496/8 bytes plus artifact. |
| Design | [include/crown/recovery/plan_descriptor.hpp](../../../../../../include/crown/recovery/plan_descriptor.hpp), [src/recovery/plan_descriptor.cpp](../../../../../../src/recovery/plan_descriptor.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] InspectedPlanDescriptor inspect_plan_descriptor(std::string_view,PlanDescriptorLimits={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect descriptor without owning artifact. |
| inputs / outputs | Immutable bytes and finite PlanDescriptorLimits return InspectedPlanDescriptor. |
| invariants | Check whole-frame final SHA/magic/version1or2/flags/body/metadata/opaque nonempty artifact length. No native/candidate proof, IO or compiler validation. |
| ownership | Fixed selection/stats copied, artifact slice borrows source descriptor, retain it unchanged during compiler use. |
| failure | ImageFailure work/limit/version/binding/corrupt; no allocating fallback. |
| cost | O(B) SHA/parse with conservative4B work debit, no heap graph or clock. |
| Design | [include/crown/recovery/plan_descriptor.hpp](../../../../../../include/crown/recovery/plan_descriptor.hpp), [src/recovery/plan_descriptor.cpp](../../../../../../src/recovery/plan_descriptor.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_review.md](../../../../../code_review.md) |

```text
inline constexpr std::size_t plan_descriptor_header_size=20;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set descriptor fixed leading header width. |
| inputs / outputs | plan_descriptor_header_size=20. |
| invariants | Descriptor has64-byte trailing whole-frame SHA; body field excludes84 combined header/trailer bytes. Not runtime/session84-byte header format. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/plan_descriptor.hpp](../../../../../../include/crown/recovery/plan_descriptor.hpp), [src/recovery/plan_descriptor.cpp](../../../../../../src/recovery/plan_descriptor.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_review.md](../../../../../code_review.md) |
