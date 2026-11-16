# `include/crown/runtime/weighted.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/weighted.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Execute weighted logical replacements and projected tuple/multiplicity enumeration with separate full messages, local visible factors and compact undo.

Snapshot SHA-256: `6e04c18d98b716246811e7e225e6c5f73556c13814037fbd35233a66e022a6c3`. 320 lines partitioned into 50 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [weighted](../../../../subsystem_contracts.md#weighted). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/annotations.md](../../../../../annotations.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../../include/crown/runtime/weighted.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 22–30](../../../../../../include/crown/runtime/weighted.hpp#L22) | Type/record definition: struct Options | source comment (unverified): // Per logical epoch, shared across stages; nullopt disables this counter cap. · [reviewed contract](#b0002) |
| [B0003 · 31–32](../../../../../../include/crown/runtime/weighted.hpp#L31) | Explanatory comments or spacing. | source comment (unverified): // Shapes are compiled/checked by the existing compiler. This binding explicitly · [reviewed contract](#b0003) |
| [B0004 · 33–37](../../../../../../include/crown/runtime/weighted.hpp#L33) | Type/record definition: struct Binding | source comment (unverified): // Shapes are compiled/checked by the existing compiler. This binding explicitly · [reviewed contract](#b0004) |
| [B0005 · 38–45](../../../../../../include/crown/runtime/weighted.hpp#L38) | Type/record definition: struct Profile |  · [reviewed contract](#b0005) |
| [B0006 · 46–50](../../../../../../include/crown/runtime/weighted.hpp#L46) | Type/record definition: struct Replacement | source comment (unverified): // Complete native scope in ascending variable-ID order. · [reviewed contract](#b0006) |
| [B0007 · 51–54](../../../../../../include/crown/runtime/weighted.hpp#L51) | Type/record definition: struct Update |  · [reviewed contract](#b0007) |
| [B0008 · 55–68](../../../../../../include/crown/runtime/weighted.hpp#L55) | Type/record definition: struct Metrics | source comment (unverified): // The one shared indexed grant consumed, including reserved undo work and · [reviewed contract](#b0008) |
| [B0009 · 69–69](../../../../../../include/crown/runtime/weighted.hpp#L69) | Type/record definition: enum class Phase |  · [reviewed contract](#b0009) |
| [B0010 · 70–70](../../../../../../include/crown/runtime/weighted.hpp#L70) | Type/record definition: struct Attempt |  · [reviewed contract](#b0010) |
| [B0011 · 71–73](../../../../../../include/crown/runtime/weighted.hpp#L71) | Explanatory comments or spacing. | source comment (unverified): // Live records own one cached array. Diagnostic copies are immutable through · [reviewed contract](#b0011) |
| [B0012 · 74–80](../../../../../../include/crown/runtime/weighted.hpp#L74) | Type/record definition: struct RecordValue | source comment (unverified): // Live records own one cached array. Diagnostic copies are immutable through · [reviewed contract](#b0012) |
| [B0013 · 81–81](../../../../../../include/crown/runtime/weighted.hpp#L81) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 82–87](../../../../../../include/crown/runtime/weighted.hpp#L82) | Type/record definition: struct RowChange | source comment (unverified): // Null is absent, distinct from an existing zero-valued row. · [reviewed contract](#b0014) |
| [B0015 · 88–93](../../../../../../include/crown/runtime/weighted.hpp#L88) | Type/record definition: struct MessageChange |  · [reviewed contract](#b0015) |
| [B0016 · 94–99](../../../../../../include/crown/runtime/weighted.hpp#L94) | Type/record definition: struct FactorChange |  · [reviewed contract](#b0016) |
| [B0017 · 100–100](../../../../../../include/crown/runtime/weighted.hpp#L100) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |
| [B0018 · 101–101](../../../../../../include/crown/runtime/weighted.hpp#L101) | Type/record definition: enum class EventKind |  · [reviewed contract](#b0018) |
| [B0019 · 102–105](../../../../../../include/crown/runtime/weighted.hpp#L102) | Explanatory comments or spacing. | source comment (unverified): // Committed native events contain logical row totals. An aborted journal is a · [reviewed contract](#b0019) |
| [B0020 · 106–113](../../../../../../include/crown/runtime/weighted.hpp#L106) | Type/record definition: struct Event | source comment (unverified): // Committed native events contain logical row totals. An aborted journal is a · [reviewed contract](#b0020) |
| [B0021 · 114–120](../../../../../../include/crown/runtime/weighted.hpp#L114) | Type/record definition: struct Journal |  · [reviewed contract](#b0021) |
| [B0022 · 121–124](../../../../../../include/crown/runtime/weighted.hpp#L121) | Explanatory comments or spacing. | source comment (unverified): // Logical-CQ output only. These facts confer no SQL source or checked-proof authority. · [reviewed contract](#b0022) |
| [B0023 · 125–125](../../../../../../include/crown/runtime/weighted.hpp#L125) | Type/record definition: enum class DeltaCapture | source comment (unverified): // Logical-CQ output only. These facts confer no SQL source or checked-proof authority. · [reviewed contract](#b0023) |
| [B0024 · 126–126](../../../../../../include/crown/runtime/weighted.hpp#L126) | Type/record definition: struct SignedMagnitude |  · [reviewed contract](#b0024) |
| [B0025 · 127–127](../../../../../../include/crown/runtime/weighted.hpp#L127) | Type/record definition: struct BagDelta |  · [reviewed contract](#b0025) |
| [B0026 · 128–132](../../../../../../include/crown/runtime/weighted.hpp#L128) | Type/record definition: struct BagDeltaMetrics | source comment (unverified): // mutations counts charged insert/update/release units, including prefunded cleanup. · [reviewed contract](#b0026) |
| [B0027 · 133–134](../../../../../../include/crown/runtime/weighted.hpp#L133) | Explanatory comments or spacing. | source comment (unverified): // A committed handle owns nonzero consolidated facts under the original account. · [reviewed contract](#b0027) |
| [B0028 · 135–148](../../../../../../include/crown/runtime/weighted.hpp#L135) | Type/record definition: class BagDeltas | returns bool(data_); source comment (unverified): // A committed handle owns nonzero consolidated facts under the original account. · [reviewed contract](#b0028) |
| [B0029 · 149–153](../../../../../../include/crown/runtime/weighted.hpp#L149) | Explanatory comments or spacing. | source comment (unverified): // DISTINCT support only: each entry is an encoded native tuple with unit signed · [reviewed contract](#b0029) |
| [B0030 · 154–166](../../../../../../include/crown/runtime/weighted.hpp#L154) | Type/record definition: class SupportDeltas | returns bool(data_); source comment (unverified): // DISTINCT support only: each entry is an encoded native tuple with unit signed · [reviewed contract](#b0030) |
| [B0031 · 167–167](../../../../../../include/crown/runtime/weighted.hpp#L167) | Explanatory comments or spacing. |  |
| [B0032 · 168–176](../../../../../../include/crown/runtime/weighted.hpp#L168) | Type/record definition: struct Epoch | source comment (unverified): // Full-root summary, not projected bag output. · [reviewed contract](#b0032) |
| [B0033 · 177–177](../../../../../../include/crown/runtime/weighted.hpp#L177) | Explanatory comments or spacing. |  |
| [B0034 · 178–178](../../../../../../include/crown/runtime/weighted.hpp#L178) | Type/record definition: struct RowSnapshot |  · [reviewed contract](#b0034) |
| [B0035 · 179–179](../../../../../../include/crown/runtime/weighted.hpp#L179) | Type/record definition: struct MessageSnapshot |  · [reviewed contract](#b0035) |
| [B0036 · 180–186](../../../../../../include/crown/runtime/weighted.hpp#L180) | Type/record definition: struct NodeSnapshot | source comment (unverified): // Visible keys, not full separator messages. · [reviewed contract](#b0036) |
| [B0037 · 187–194](../../../../../../include/crown/runtime/weighted.hpp#L187) | Type/record definition: struct Snapshot |  · [reviewed contract](#b0037) |
| [B0038 · 195–195](../../../../../../include/crown/runtime/weighted.hpp#L195) | Type/record definition: struct SnapshotLimits |  · [reviewed contract](#b0038) |
| [B0039 · 196–198](../../../../../../include/crown/runtime/weighted.hpp#L196) | Explanatory comments or spacing. | source comment (unverified): // Compressed bag output: one owning row per distinct core tuple. The logical · [reviewed contract](#b0039) |
| [B0040 · 199–199](../../../../../../include/crown/runtime/weighted.hpp#L199) | Type/record definition: struct Result | source comment (unverified): // Compressed bag output: one owning row per distinct core tuple. The logical · [reviewed contract](#b0040) |
| [B0041 · 200–200](../../../../../../include/crown/runtime/weighted.hpp#L200) | Type/record definition: enum class CursorState |  · [reviewed contract](#b0041) |
| [B0042 · 201–201](../../../../../../include/crown/runtime/weighted.hpp#L201) | Type/record definition: struct CursorOptions |  · [reviewed contract](#b0042) |
| [B0043 · 202–208](../../../../../../include/crown/runtime/weighted.hpp#L202) | Type/record definition: struct CursorMetrics |  · [reviewed contract](#b0043) |
| [B0044 · 209–244](../../../../../../include/crown/runtime/weighted.hpp#L209) | declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::weighted · [reviewed contract](#b0044) |
| [B0045 · 245–280](../../../../../../include/crown/runtime/weighted.hpp#L245) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Drains one replacement; any error aborts every stage in this token. · [reviewed contract](#b0045) |
| [B0046 · 281–300](../../../../../../include/crown/runtime/weighted.hpp#L281) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Freeze the shape into the supplied account. Its actual limit is · [reviewed contract](#b0046) |
| [B0047 · 301–301](../../../../../../include/crown/runtime/weighted.hpp#L301) | Callable definition: \[\[nodiscard\]\] static constexpr weighted::Profile profile() noexcept | calls ; returns {} · [reviewed contract](#b0047) |
| [B0048 · 302–315](../../../../../../include/crown/runtime/weighted.hpp#L302) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0048) |
| [B0049 · 316–316](../../../../../../include/crown/runtime/weighted.hpp#L316) | Callable definition: explicit WeightedRuntime(std::shared_ptr&lt;Impl&gt; value) noexcept : impl_(std::move(value)) | calls impl_, std::move · [reviewed contract](#b0049) |
| [B0050 · 317–320](../../../../../../include/crown/runtime/weighted.hpp#L317) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0050) |

## B0001

[Lines 1–21](../../../../../../include/crown/runtime/weighted.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:2eaee8a7fab9aed832e616b1a387a1f348b02f5da60138dc840b0f57a3b719df
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the direct-CQ weighted public types and their required ownership/storage dependencies. |
| inputs / outputs | Compile-time includes, multiplicity alias and original-account output-vector alias; no runtime instance. |
| invariants | OutputVector uses OwnerAllocator; &lt;utility&gt; supplies the new private adoption constructor's std::move. |
| ownership | Aliases only; instances inherit their documented receiving account. |
| failure | Missing declarations are compile errors; this block handles no runtime failure. |
| cost | No runtime initialization, allocation or registry. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

```text
#pragma once #include "crown/annotations/policy.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make the private cold bridge name available to WeightedRuntime without adding a public cold API. |
| inputs / outputs | Only the forward-declared detail bridge receives friendship; public WeightedRuntime factories and operations are unchanged. |
| invariants | The bridge cannot be reached through the installed public interface; only source-private code can call it. |
| ownership | No owner/state created by the declaration. |
| failure | Compilation catches namespace/access mismatch. |
| cost | No runtime cost or record layout change. |
| Design | [include/crown/runtime/weighted.hpp](../../../../../../include/crown/runtime/weighted.hpp), [src/runtime/sql_cold_rebuild.hpp](../../../../../../src/runtime/sql_cold_rebuild.hpp) |

## B0002

[Lines 22–30](../../../../../../include/crown/runtime/weighted.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L30:sha256:470418273b9b3b26aec38f772e90978e5201da0a31126532afe3eb85aa4f697e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure exact multiplicity bounds, query heap, executed-work limit and optional diagnostics. |
| inputs / outputs | Copied at creation. Standalone constructors create the configured heap cap; create_into reports the supplied account's actual cap instead. Captures default off. |
| invariants | The receiver cap is authoritative and cannot be enlarged by options. One epoch work counter spans all stages; capture_events enables change capture. |
| ownership | Stored inline in the runtime using its one original or receiving account. |
| failure | Zero/invalid arithmetic bound is rejected by MultiplicityPolicy. |
| cost | Fixed option reads/copies; explicit captures add per-change allocation/copy costs. Reading the account cap does not traverse allocations. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../../Refactor.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0003

[Lines 31–32](../../../../../../include/crown/runtime/weighted.hpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L32:sha256:c4bf2854566fb4689a235ac413c04e39ce29ee86df3f8d35769a152be13e1371
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why weighted execution requires a separate semantic identity. |
| inputs / outputs | Human guidance for Binding and structural compiler artifacts. |
| invariants | A structural set identity alone is not weighted execution authority. |
| ownership | Comment only; Binding owns fixed digest arrays. |
| failure | Do not treat a source-plan hash as a weighted cache/replay proof. |
| cost | No runtime work. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 supplies aggregation context; these ownership, adapter and work contracts are local engineering, not a theorem of the paper](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0004

[Lines 33–37](../../../../../../include/crown/runtime/weighted.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L37:sha256:755f0704c13475896325fcbff9b3de03971c373c3650c3a4d2ea506c4c851df3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish full weighted subtree execution from structural set-plan identity. |
| inputs / outputs | Structural SHA256 plus weighted policy/version and configured maximum produce weighted SHA256. |
| invariants | A structural binding cannot authorize weighted execution. |
| ownership | Fixed arrays stored with runtime; copied in snapshots. |
| failure | Malformed structural binding rejected before use. |
| cost | Fixed stack encoding and fixed-length SHA256; performed at admission. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../../Refactor.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0005

[Lines 38–45](../../../../../../include/crown/runtime/weighted.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L45:sha256:96ef981fa5a6611d25adc9ab7b7895715155da003bce208a6570e7c78908c823
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the versioned scope of exact weighted logical-row execution. |
| inputs / outputs | Fixed string_views describe arithmetic, logical replacement, full messages and compressed output. |
| invariants | Contribution shares normalize to the same logical replacements. Profile claims no SQL adapter, signed weights, Boolean maintenance bound or W05 completion. |
| ownership | Views point at static literals; profile copies contain no owning metadata. |
| failure | No runtime failure or dynamic registration. |
| cost | Fixed inline fields, no allocation. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 supplies aggregation context; these ownership, adapter and work contracts are local engineering, not a theorem of the paper](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0006

[Lines 46–50](../../../../../../include/crown/runtime/weighted.hpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L50:sha256:2878181b9ce2fdf43cf830cf0d56a63ca55c28c01eb59a8173f1fb9de12206cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one native logical scope tuple weight with an expected-value precondition. |
| inputs / outputs | Node, complete typed row, before and after uint64 weights; zero denotes absence. |
| invariants | Generalized nodes are internal; before must equal current local weight. |
| ownership | Caller owns input; runtime creates an accounted typed key. |
| failure | Wrong node, shape, type, old value or numeric maximum aborts the entire pending epoch. |
| cost | One lookup plus affected-row propagation; hidden witnesses can cause numeric-only changes. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../../Refactor.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0007

[Lines 51–54](../../../../../../include/crown/runtime/weighted.hpp#L51); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L54:sha256:99d9099e6b704c1168a24be3f37c1a79aaeae17ca4368cf4f127faa3c6972a29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Package one absolute replacement with its committed logical sequence. |
| inputs / outputs | Sequence and owning Replacement feed WeightedRuntime::apply. |
| invariants | Sequence must be the next contiguous value; apply remains the absolute-total port. |
| ownership | Caller owns Row until synchronous apply copies native key data. |
| failure | begin/stage errors preserve the prior epoch; the DTO adds no handler. |
| cost | DTO construction owns its Row; native execution cost is separate. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0008

[Lines 55–68](../../../../../../include/crown/runtime/weighted.hpp#L55); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L68:sha256:3d7f3bfaad63aa1fcf386dd160e85650e94280a76a220d04f3c27b7ca0f026b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose executed maintenance operations and separate native index work consumption. |
| inputs / outputs | Epoch counters and original grant debit totals. |
| invariants | Counters measure actual work; they are not CPU instructions or a Boolean height bound. |
| ownership | Value state in epoch/last attempt. |
| failure | Configured work exhaustion preserves committed state. |
| cost | Counters are scalar increments; diagnostic child copies are counted only when requested. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../../Refactor.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0009

[Lines 69–69](../../../../../../include/crown/runtime/weighted.hpp#L69); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L69:sha256:219499b2b7fdbeff99f66bd6d3a4028b7eb6fc656de4d14367714d45d818dd61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish private, successfully published and aborted attempt diagnostics. |
| inputs / outputs | pending, committed or aborted values annotate journals/last attempts. |
| invariants | Aborted diagnostics cannot be replayed as committed transitions. |
| ownership | Inline enum, no owner or allocator. |
| failure | The tag conveys status; it does not recover a failed operation. |
| cost | Fixed scalar storage. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0010

[Lines 70–70](../../../../../../include/crown/runtime/weighted.hpp#L70); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L70:sha256:6dff9b277f62b3af4f220b9c6784a54ae3f87def377e046f091e34cf35fbe059
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain only the most recently closed epoch's status and spent counters. |
| inputs / outputs | Sequence, committed/aborted phase and Metrics value returned by last_attempt. |
| invariants | A live pending epoch is not a closed attempt; no accumulated old-attempt history. |
| ownership | Inline value retained by Impl and copied to callers. |
| failure | Aborted metrics describe attempted work, not a committed state change. |
| cost | Fixed metric copy; no per-attempt allocation. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0011

[Lines 71–73](../../../../../../include/crown/runtime/weighted.hpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L73:sha256:e0cd3a24f157957628094867fb5c76ada316be73780e259746418f651fb77c4c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate mutable live caches from explicitly requested immutable diagnostic images. |
| inputs / outputs | Human guidance for RecordValue/Record ownership and generalized unit weight. |
| invariants | Default numeric changes do not copy cached child arrays. |
| ownership | Live rows own arrays; Record owns a distinct const diagnostic image. |
| failure | Capture allocation can abort a private stage under the same account. |
| cost | Comment has no cost; optional image cost scales with child arity. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0012

[Lines 74–80](../../../../../../include/crown/runtime/weighted.hpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L80:sha256:ae9d05c7d2ecc3a3d9c9397c9695824f0708e8d3175fab31147f50ba62b91084
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cache native/generalized local weight, full subtree product, local visible contribution and child messages in one live row. |
| inputs / outputs | Cached array has node child arity; supported_children counts positive entries. |
| invariants | Generalized local=1; missing support makes subtree/factor zero. Outside-C* rows have factor0. A C* contribution excludes enumerated children, and its positive support follows the full subtree. |
| ownership | Live map owns one array per row; external Record is a const diagnostic copy. |
| failure | Construction may reject heap allocation; private undo preserves state. |
| cost | One child array at row creation. Numeric edits save scalars/one slot; required local-factor recomputation visits only precompiled outside-child slots, while positive inside changes reuse the cached contribution. Diagnostic array copies are opt-in. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../../Refactor.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0013

[Lines 81–81](../../../../../../include/crown/runtime/weighted.hpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L81:sha256:12f7e13ff8194941dc29c00ee93c27ff13796045e3d700320a1339ce6f0ba490
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose immutable owning diagnostic row images. |
| inputs / outputs | shared_ptr&lt;const RecordValue&gt;; null denotes absent diagnostic image. |
| invariants | The pointer must never alias mutable live record arrays. |
| ownership | Retains original-account control/array storage across facade release. |
| failure | Pointer retention is nonallocating; image creation may reject funded allocation. |
| cost | Shared ownership copy/release, including final destruction when last. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0014

[Lines 82–87](../../../../../../include/crown/runtime/weighted.hpp#L82); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L87:sha256:b0caaf6457a32568253bd1aa44b7377004d2ad6286fef3ff27727802d76b9cb4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a tentative or committed full-row/cache transition. |
| inputs / outputs | Native node, retained key pin, immutable before/after images and causal event ID. |
| invariants | Null image means absence, unlike an existing zero-subtree candidate. |
| ownership | Journal pins retain erased tuples; images own independent child caches. |
| failure | Aborted changes are partial attempted diagnostics; capture failure aborts the stage. |
| cost | Requested capture only: key pin and O(child arity) images. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0015

[Lines 88–93](../../../../../../include/crown/runtime/weighted.hpp#L88); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L93:sha256:123bcf590a9d4e3acc3bfd83ea6c44313d4deab8f8e9da47235197958336e8f3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a full-subtree separator-sum transition. |
| inputs / outputs | Node, retained separator key, before/after sums and causal event ID. |
| invariants | These full messages are distinct from local visible factors or final projected answers. |
| ownership | Original-account journal owns the key pin and inline counts. |
| failure | Aborted diagnostics are not committed deltas; capture can exhaust heap/work. |
| cost | One optional record/pin per captured numeric separator change. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 supplies aggregation context; these ownership, adapter and work contracts are local engineering, not a theorem of the paper](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0016

[Lines 94–99](../../../../../../include/crown/runtime/weighted.hpp#L94); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L99:sha256:c83812ec8c22f37525b95a4ef6a6f5959b8535a35b86d9fdd888d8525704fb9d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a local visible-key sum change separately from a full subtree message. |
| inputs / outputs | Node/key pin, numeric before/after and causal event ID are immutable capture data. |
| invariants | A factor change is local state, not a complete projected-answer delta; it creates no ancestor event. |
| ownership | The optional journal owns a pin in the original account, keeping deleted E keys readable. |
| failure | Capture allocation is inside the private stage rollback boundary. |
| cost | Only requested capture adds a record/pin; no capture work when both options are off. |
| Design | [Refactor.md §10.2 and W03](../../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0017

[Lines 100–100](../../../../../../include/crown/runtime/weighted.hpp#L100); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L100-L100:sha256:6e32c726e4bc51b77eb935d637f7af2e2e77707b3f137280e7eff6ec94262f26
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store three explicitly different owning transition forms in one capture stream. |
| inputs / outputs | Inline variant of RowChange, MessageChange and FactorChange. |
| invariants | Inspect the active alternative; do not confuse subtree sums and local output factors. |
| ownership | Variant owns the active record's pins/images through the original account. |
| failure | No catch/translation framework is added by the discriminated union. |
| cost | Fixed variant payload plus explicitly requested owning captures. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0018

[Lines 101–101](../../../../../../include/crown/runtime/weighted.hpp#L101); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L101:sha256:e78e520e22e6521b523c8c51ccdc9848e162cb0d312c02111e20e5354f9d73c8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the public event vocabulary as logical native totals or child messages. |
| inputs / outputs | native_weight and child_message annotate captured diagnostics. |
| invariants | The new private contribution kind is normalized to native_weight; no public source identity or child-event extension. |
| ownership | Inline enum stored in optional captured Event values. |
| failure | Interpret values with Journal::phase; an aborted native attempt can still hold shares. |
| cost | Fixed scalar tag; no new public per-event payload. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0019

[Lines 102–105](../../../../../../include/crown/runtime/weighted.hpp#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L105:sha256:26341e84d43224e9846b221668ceac69dec396d42571548a4b9bb6cc8d082041
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the precise diagnostic boundary for contribution normalization and abort. |
| inputs / outputs | Guidance for Event before/after and applied_ordinal interpretation. |
| invariants | Committed native events contain actual totals; aborted journals can contain raw failing shares/requested absolute weights. applied_ordinal marks execution entry. |
| ownership | Comment only; journal owns retained diagnostic values. |
| failure | Never replay aborted diagnostics as committed transitions or interpret an ordinal as completion. |
| cost | No executable tokens or runtime cost. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0020

[Lines 106–113](../../../../../../include/crown/runtime/weighted.hpp#L106); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L113:sha256:3e8709a7f61f388e9100d1403da9b3afc0ce0358abef5d3bf9ff4679170cbc0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a causal event's execution-entry status without retaining a second key. |
| inputs / outputs | IDs/cause/ordinal, public kind/target, optional edge/change-record index, and before/after multiplicities. |
| invariants | IDs increase in enqueue order; cause is an earlier event or zero. Successful normalized native values are totals; aborted input may remain shares. Child values retain FIFO before/after semantics. |
| ownership | Inline counts/indices belong to the optional original-account Journal; key ownership is in corresponding record pins. |
| failure | Aborted trace may include an event not queued or not completed; journal phase limits its meaning. |
| cost | Fixed metadata per requested event; no added native Pending fields. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0021

[Lines 114–120](../../../../../../include/crown/runtime/weighted.hpp#L114); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L120:sha256:d3d80ed058bcb9947cd3184514a379317e0743c5d399fddabd7a17d611f60ace
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain optional before/after records and causal numeric events for human inspection. |
| inputs / outputs | Created only for capture_changes or capture_events; Epoch::journal otherwise null. |
| invariants | Phase moves pending to committed or aborted. Committed native events contain actual logical totals; aborted traces may retain unnormalized shares/requested weights. applied_ordinal denotes execution entry, not successful completion. |
| ownership | Original-account owning captures may outlive the facade. Copy a preview journal shared pointer before abort to inspect it afterward; aborted records are not replay/publication authority. |
| failure | Diagnostic allocation can abort the private epoch under the same heap/work limits. |
| cost | O(captured changes and child slots); default execution allocates no diagnostic record images. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../../Refactor.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0022

[Lines 121–124](../../../../../../include/crown/runtime/weighted.hpp#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L124:sha256:8e226584ea22dc2b4fb919813f2d217ae3510b84cc5f7530fdfce4ff3928a2a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare separate opt-in numeric/support capture requests, owning support changes and prepared preview access without changing numeric root endpoints. |
| inputs / outputs | Existing disabled/enabled modes retain values/meaning; support selects unit encoded-tuple changes. Epoch retains separate bag_deltas/support_deltas handles; preview names remain distinct. |
| invariants | Support entries are nonzero unit signed changes; numeric bag facts remain arbitrary exact uint64 magnitudes. The same active-token lifetime and single-writer rules apply; no mutable external count graph is authority. |
| ownership | SupportDeltas shares the already-accounted immutable per-epoch accumulator. Its spans/metrics borrow a live unmoved handle; prepared views expire on stage/commit/rollback as existing capture does. |
| failure | Default/closed handle access has an explicit capture/epoch error; rvalue borrowed views are compile-time rejected. Declarations introduce no catch or recovery policy. |
| cost | One scalar request and one shared owning handle; support storage exists only when explicitly selected. No snapshot or persistent result-count map is declared. |
| Design | [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [Refactor.md §W02-W03/W05-W06](../../../../../../Refactor.md) |

## B0023

[Lines 125–125](../../../../../../include/crown/runtime/weighted.hpp#L125); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L125:sha256:a8deecaf2f09030b339cbccad2986085a3f76d3ffda0f1c8a3dca5101cfaefe9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare separate opt-in numeric/support capture requests, owning support changes and prepared preview access without changing numeric root endpoints. |
| inputs / outputs | Existing disabled/enabled modes retain values/meaning; support selects unit encoded-tuple changes. Epoch retains separate bag_deltas/support_deltas handles; preview names remain distinct. |
| invariants | Support entries are nonzero unit signed changes; numeric bag facts remain arbitrary exact uint64 magnitudes. The same active-token lifetime and single-writer rules apply; no mutable external count graph is authority. |
| ownership | SupportDeltas shares the already-accounted immutable per-epoch accumulator. Its spans/metrics borrow a live unmoved handle; prepared views expire on stage/commit/rollback as existing capture does. |
| failure | Default/closed handle access has an explicit capture/epoch error; rvalue borrowed views are compile-time rejected. Declarations introduce no catch or recovery policy. |
| cost | One scalar request and one shared owning handle; support storage exists only when explicitly selected. No snapshot or persistent result-count map is declared. |
| Design | [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../../Refactor.md) |

## B0024

[Lines 126–126](../../../../../../include/crown/runtime/weighted.hpp#L126); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L126-L126:sha256:84a12cbbbf2ec227709c92b6dac76a2ef3c1d5d7226dcf1c0a9ba0211025cef3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent either sign of an unsigned count difference. |
| inputs / outputs | Boolean sign and Multiplicity magnitude; no int64 conversion. |
| invariants | Library-produced stored facts have positive magnitude; cancellation removes zero. This carrier alone supplies no authority. |
| ownership | Inline fixed-width fields. |
| failure | Checked same-sign addition can reject through the native policy. |
| cost | Fixed unsigned comparison/subtraction or checked addition. |
| Design | [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0025

[Lines 127–127](../../../../../../include/crown/runtime/weighted.hpp#L127); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L127-L127:sha256:0ed686357a903b39331ace2ebf5187d52356acbe918a82222b73efcd7b243e9a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one complete compiled output key and its signed net change. |
| inputs / outputs | AccountedTuple plus SignedMagnitude in declared output order. |
| invariants | Library entries are unique by full projected value and have nonzero magnitude. |
| ownership | Move-only tuple transfers original-account payload; the owning BagDeltas handle retains it. |
| failure | Construction/storage can fail during private preparation. |
| cost | One retained payload per current net key; copying the shared outer handle copies no tuple. |
| Design | [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0026

[Lines 128–132](../../../../../../include/crown/runtime/weighted.hpp#L128); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L132:sha256:038aad0780c1e0179bfa8afaef37dcefd0d519356ae31e805ae6a5fe47a0bb39
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose capture-specific logical debits. |
| inputs / outputs | Work, rows, fields, bytes, factors, products, comparisons, terms and mutations. |
| invariants | Counters are subsets of admitted cumulative epoch work; mutation units include prefunded release. |
| ownership | Inline counters retained in immutable output. |
| failure | A failed charge rejects before its covered operation. |
| cost | Selected logical work, neither CPU nor all allocator operations. |
| Design | [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0027

[Lines 133–134](../../../../../../include/crown/runtime/weighted.hpp#L133); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L134:sha256:0599e5fb65cad463a31578ca7b19531f86dcc670c4c1c3b7392241f491e67a38
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class BagDeltas\`: A committed handle owns nonzero consolidated facts under the original account. Iterators/spans borrow this handle. Order is unspecified; no lookup index escapes. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/weighted.hpp:L133; use that declaration for the actual input/output shape. |
| invariants | The source note states: A committed handle owns nonzero consolidated facts under the original account. Iterators/spans borrow this handle. Order is unspecified; no lookup index escapes. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: A committed handle owns nonzero consolidated facts under the original account. Iterators/spans borrow this handle. Order is unspecified; no lookup index escapes. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0028

[Lines 135–148](../../../../../../include/crown/runtime/weighted.hpp#L135); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L148:sha256:f18cac58966cf0354a7def7f864d5966fdc96a63357000dc291423452136c887
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share immutable committed net facts without retaining mutable runtime state. |
| inputs / outputs | Default empty handle; entries/metrics require engagement; spans/references borrow the handle. |
| invariants | No owning pending output escapes; enabled zero net is an engaged empty handle. Entry order is unspecified. |
| ownership | Original account owns data, vector capacity and payloads; copying shares one const owner. |
| failure | Empty/default/moved access raises delta_capture_disabled. |
| cost | Fixed handle copy; final release destroys retained capacity/payloads; no mutable lookup survives commit. |
| Design | [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0029

[Lines 149–153](../../../../../../include/crown/runtime/weighted.hpp#L149); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L153:sha256:e8e3852cc0e4f11e804e8d4cea3f9a02a17fb088b18375649a7fbf23247a45b8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare separate opt-in numeric/support capture requests, owning support changes and prepared preview access without changing numeric root endpoints. |
| inputs / outputs | Existing disabled/enabled modes retain values/meaning; support selects unit encoded-tuple changes. Epoch retains separate bag_deltas/support_deltas handles; preview names remain distinct. |
| invariants | Support entries are nonzero unit signed changes; numeric bag facts remain arbitrary exact uint64 magnitudes. The same active-token lifetime and single-writer rules apply; no mutable external count graph is authority. |
| ownership | SupportDeltas shares the already-accounted immutable per-epoch accumulator. Its spans/metrics borrow a live unmoved handle; prepared views expire on stage/commit/rollback as existing capture does. |
| failure | Default/closed handle access has an explicit capture/epoch error; rvalue borrowed views are compile-time rejected. Declarations introduce no catch or recovery policy. |
| cost | One scalar request and one shared owning handle; support storage exists only when explicitly selected. No snapshot or persistent result-count map is declared. |
| Design | [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../../Refactor.md) |

## B0030

[Lines 154–166](../../../../../../include/crown/runtime/weighted.hpp#L154); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L166:sha256:6b5a80e66d32e62849e136da0bc4e691932b92c511659bc2ef9517998a529571
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare separate opt-in numeric/support capture requests, owning support changes and prepared preview access without changing numeric root endpoints. |
| inputs / outputs | Existing disabled/enabled modes retain values/meaning; support selects unit encoded-tuple changes. Epoch retains separate bag_deltas/support_deltas handles; preview names remain distinct. |
| invariants | Support entries are nonzero unit signed changes; numeric bag facts remain arbitrary exact uint64 magnitudes. The same active-token lifetime and single-writer rules apply; no mutable external count graph is authority. |
| ownership | SupportDeltas shares the already-accounted immutable per-epoch accumulator. Its spans/metrics borrow a live unmoved handle; prepared views expire on stage/commit/rollback as existing capture does. |
| failure | Default/closed handle access has an explicit capture/epoch error; rvalue borrowed views are compile-time rejected. Declarations introduce no catch or recovery policy. |
| cost | One scalar request and one shared owning handle; support storage exists only when explicitly selected. No snapshot or persistent result-count map is declared. |
| Design | [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../../Refactor.md) |

## B0032

[Lines 168–176](../../../../../../include/crown/runtime/weighted.hpp#L168); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L168-L176:sha256:554d463efc02fe7ae7de50674a1d8656aca7e2188d8f97a89a722f7617d6eb16
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare separate opt-in numeric/support capture requests, owning support changes and prepared preview access without changing numeric root endpoints. |
| inputs / outputs | Existing disabled/enabled modes retain values/meaning; support selects unit encoded-tuple changes. Epoch retains separate bag_deltas/support_deltas handles; preview names remain distinct. |
| invariants | Support entries are nonzero unit signed changes; numeric bag facts remain arbitrary exact uint64 magnitudes. The same active-token lifetime and single-writer rules apply; no mutable external count graph is authority. |
| ownership | SupportDeltas shares the already-accounted immutable per-epoch accumulator. Its spans/metrics borrow a live unmoved handle; prepared views expire on stage/commit/rollback as existing capture does. |
| failure | Default/closed handle access has an explicit capture/epoch error; rvalue borrowed views are compile-time rejected. Declarations introduce no catch or recovery policy. |
| cost | One scalar request and one shared owning handle; support storage exists only when explicitly selected. No snapshot or persistent result-count map is declared. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [Refactor.md §W02-W03/W05-W06](../../../../../../Refactor.md) |

## B0034

[Lines 178–178](../../../../../../include/crown/runtime/weighted.hpp#L178); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L178-L178:sha256:96a46e4f557c9a1d99d05e283a0cd24b62d905fa6653e4626c5949857ec5dd18
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one full scope tuple and independent row-value image for inspection. |
| inputs / outputs | AccountedTuple and const Record value. |
| invariants | Later runtime mutation cannot change snapshot tuple/scalars/child array. |
| ownership | Original-account copies retain their layout and payload. |
| failure | Capture failure rejects a partial snapshot without publishing it. |
| cost | O(fields, string bytes and child arity) explicit capture. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0035

[Lines 179–179](../../../../../../include/crown/runtime/weighted.hpp#L179); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L179-L179:sha256:8418f33807d2825e42a32d354457a9abc7a8c9d0db2707627b8b12eabedb359d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one separator/visible key and exact scalar sum for a snapshot. |
| inputs / outputs | AccountedTuple key and inline Multiplicity. |
| invariants | Containing NodeSnapshot vector determines full-message or local-factor meaning. |
| ownership | Key bytes/layout remain in the runtime's original account. |
| failure | Copy funding failure discards partial capture. |
| cost | O(key fields/bytes) copied payload plus fixed count. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0036

[Lines 180–186](../../../../../../include/crown/runtime/weighted.hpp#L180); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L186:sha256:6dfe203969d92e5ea4a0674a08eebd9fe16191508972fcc99522d34b3f157d10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group bounded owning diagnostic entries for one compiled node. |
| inputs / outputs | Node ID and original-account vectors of records, full messages and local factors. |
| invariants | Vector roles stay separate; captures are inspection rather than import authority. |
| ownership | All vectors and their tuple/image payloads are funded by the selected account. |
| failure | Snapshot row/heap/work exhaustion rejects capture. |
| cost | Storage proportional to explicitly captured entries and child/key payloads. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0037

[Lines 187–194](../../../../../../include/crown/runtime/weighted.hpp#L187); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L187-L194:sha256:22ec86d20f8a57d3dabeaf8e7053c023e842ab873aefc63d5c3996007890db79
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish an owning explicit copy of current or private weighted state. |
| inputs / outputs | Binding, shape, root summary, full records/caches, separator messages and local visible factors are copied into an owning bounded snapshot. |
| invariants | Private snapshots are marked tentative and cannot authorize imports. |
| ownership | Original-account copies outlive later mutation/facade destruction. |
| failure | Row cap, heap or native grant exhaustion rejects capture. |
| cost | O(captured rows plus child slots), requested explicitly. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../../Refactor.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0038

[Lines 195–195](../../../../../../include/crown/runtime/weighted.hpp#L195); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L195-L195:sha256:5644228955ba12d843b0721360c3a9589c1129e88a8509f25ffac8c982be5ed9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound total row/message/factor entries copied by an explicit snapshot. |
| inputs / outputs | rows defaults to 65,536; capture checks it before each append. |
| invariants | This entry cap supplements, rather than replaces, heap and indexed work limits. |
| ownership | Inline caller options, no retained state. |
| failure | snapshot_limit rejects excess entries; committed runtime remains valid. |
| cost | One scalar comparison per captured entry. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0039

[Lines 196–198](../../../../../../include/crown/runtime/weighted.hpp#L196); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L196-L198:sha256:6c04fa7229e985a623d468e186bb578df7d80c6458812133f5f54c987da57f31
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify the cursor's compressed output size convention. |
| inputs / outputs | One owning result per distinct core tuple, with exact positive multiplicity. |
| invariants | Expanded logical size is sum of weights; record count is distinct tuples. |
| ownership | Returned tuples own their payload; no automatic expansion buffer. |
| failure | Output funding can reject a cursor step without invalidating earlier results. |
| cost | Comment only; expanding repetitions would require separately charged work. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 supplies aggregation context; these ownership, adapter and work contracts are local engineering, not a theorem of the paper](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0040

[Lines 199–199](../../../../../../include/crown/runtime/weighted.hpp#L199); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L199-L199:sha256:454280b72e6d5d871616026f06355947249c6734d36171e232e357d630a424d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer one compressed projected core tuple with its positive exact multiplicity. |
| inputs / outputs | Owning storage::Tuple plus checked uint64 multiplicity; output head order/repetitions preserved. |
| invariants | One record per distinct tuple, no zero record. Empty-head bags emit at most one empty tuple; SQL EXISTS/COUNT empty-row synthesis is not this API. |
| ownership | Tuple payload/layout remain valid after cursor or runtime release under the original account. |
| failure | Output allocation may fail; earlier returned rows remain valid. |
| cost | Work/output records count distinct tuples; expanded logical size is the sum of multiplicities, without materializing repeats. |
| Design | [Refactor.md §10.2 and W03](../../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0041

[Lines 200–200](../../../../../../include/crown/runtime/weighted.hpp#L200); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L200:sha256:7c2abfaee5d8a2edbc3f5eda70b335f03a3626d6e1e490b3ee6dad00b9e671b5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the committed result cursor lifecycle. |
| inputs / outputs | active, exhausted, cancelled and failed states. |
| invariants | Exhausted/cancelled next returns nullopt; failed next rejects invalid_cursor. |
| ownership | Inline state; reader/grant release follows the cursor implementation contract. |
| failure | The state records terminal failure without hiding its original exception. |
| cost | Fixed scalar storage/read. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0042

[Lines 201–201](../../../../../../include/crown/runtime/weighted.hpp#L201); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L201-L201:sha256:b5a47e56cd59a7d7de68a09ee5f36755ccfd9d35dc9953270b65d917e88852a0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set a cumulative work cap for one committed compressed result stream. |
| inputs / outputs | Optional uint64 cap; nullopt disables this abstract counter only. |
| invariants | No refill between next calls; native per-operation allowance is a separate original retained grant. |
| ownership | Options are copied into cursor data; heap remains the existing query account limit. |
| failure | Startup/next reject exhausted work; startup publishes no reader if it fails. |
| cost | One scalar admission check per charged operation; no elapsed-time or constant-delay guarantee. |
| Design | [Refactor.md §10.2 and W03](../../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0043

[Lines 202–208](../../../../../../include/crown/runtime/weighted.hpp#L202); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L202-L208:sha256:56d00a04a880f26593a36fcbd3cab3834f02b5168c26f8c635e0a4353f577b86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose actual cursor startup/selection/output/termination/failure work and native grant debit. |
| inputs / outputs | Cumulative operation counters plus startup/last/max-result/termination/failed work and native balance difference. |
| invariants | Compressed rows_emitted does not count repeated multiplicities. Cleanup frames are separate from the admitted forward-work budget. |
| ownership | Value state remains readable after close while the cursor data lives. |
| failure | Failed next retains spent work before dropping the reader; counters do not suppress the original failure. |
| cost | Fixed scalar counter updates; native allocation, map comparisons, payload bytes and final-owner destruction have additional costs. |
| Design | [Refactor.md §10.2 and W03](../../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0044

[Lines 209–244](../../../../../../include/crown/runtime/weighted.hpp#L209); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L209-L244:sha256:c97f36a268b0e79a21a72deb538f059142db74a5c85c8b5d6b788e106c065ef1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one committed weighted epoch through a move-only tuple/multiplicity stream. |
| inputs / outputs | results creates a reader; next returns an owning Result or terminal null; cancel closes early. Metadata/metrics remain inspectable after close. |
| invariants | Multiple readers coexist; all writes including no-ops are blocked. Exhaustion requires terminal null; failed next closes and later next throws invalid_cursor. |
| ownership | Active data retains runtime and one grant; closed data retains program/layout/binding without mutable query state. Moves transfer original ownership. |
| failure | Construction failure leaves reader count unchanged; one next failure boundary closes and rethrows. Moves/cancel are nonallocating. |
| cost | O(C*) frames plus O(ordered head width, including repetitions) row-view scratch at startup; actual live/bucket traversal and prefix products, with no output set, deduplication history or hidden Cartesian enumeration. Close visits all frames; final runtime destruction is separately attributable. |
| Design | [Refactor.md §10.2 and W03](../../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0045

[Lines 245–280](../../../../../../include/crown/runtime/weighted.hpp#L245); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L245-L280:sha256:2a37852bf8765536e1fdf8cde79906fa468a4e32837174b2f1fce3d9a1394922
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare ResultCursor private storage and the PendingEpoch transaction interface. |
| inputs / outputs | Complete ResultCursor constructor/data()/AccountedUnique storage; declare PendingEpoch move-only lifecycle, active, stage, stage_contribution, numeric/support delta previews, epoch preview, explicit snapshot, commit/rollback and private stage_native boundary. |
| invariants | These are declarations. PendingEpoch uses one staged epoch and distinct numeric versus unit-support preview methods; execution, arithmetic and rollback checks belong to their bodies. A preview borrow requires its active token and expires on stage/commit/rollback/destruction. |
| ownership | Declared ResultCursor data_ is account-owned; PendingEpoch private constructor accepts its owning Data handle, whose member continues in the next span. Stage inputs are borrowed for the call and preview views borrow the token. |
| failure | Declaration/type checking only here; called methods retain their actual epoch, stage, account and work-failure contracts. This span installs no catch or recovery path. |
| cost | No executed stage, decode, snapshot or allocation merely from declarations. Actual method costs are specified at their implementations; snapshot remains an explicit operation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../../Refactor.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../../Refactor.md) |

```text
[[nodiscard]] bool stage_contribution(NodeId,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the synchronous adapter-owned share replacement primitive. |
| inputs / outputs | Native NodeId, complete-scope borrowed TupleValuesView, before/after shares return logical native change. |
| invariants | Compute total - before + after once at existing lookup; adapter proves identity/old share. Valid equality can be a charged no-op. |
| ownership | Caller cells/string bytes live until return. The pending transaction owns copied native keys afterward. |
| failure | Invalid scope/kind, underflow, overflow, allocation or work rejection abort every private stage. |
| cost | One existing lookup, one extra charged fixed arithmetic replacement, existing propagation; no count map. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0046

[Lines 281–300](../../../../../../include/crown/runtime/weighted.hpp#L281); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L281-L300:sha256:5e4a8dcec8efd9263561fc74ce99684c03864732e11c620d3518c941ed8c1e1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare PendingEpoch storage plus weighted-runtime creation, lifecycle and immutable metadata borrows. |
| inputs / outputs | Complete PendingEpoch AccountedUnique&lt;Data&gt;; declare create_into for PhysicalPlan/CompiledProgram, standalone constructors, deleted copying, noexcept moves, destructor and const-lvalue structural_program()/binding() access with rvalue borrows deleted. |
| invariants | Declarations create no runtime. The stated create_into contract uses the supplied actual receiving account; executable factories enforce genuine physical/compiler identity and configured arithmetic/work policy. |
| ownership | PendingEpoch unique Data member owns its existing token. Runtime factories return an owning facade; structural-program/binding references borrow live immutable runtime metadata. |
| failure | Declaration/type checking only here. Factory allocation/identity/account failures and empty-facade getter failures are defined in their implementation bodies. |
| cost | No executed construction, freeze, hash, capture or allocation from this declaration span. Runtime admission and handle teardown keep their actual cold/lifetime costs. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [Refactor.md §W02-W03/W05-W06](../../../../../../Refactor.md) |

```text
[[nodiscard]] static WeightedRuntime create_into(const resource::MemoryAccount&,
      const CompiledProgram&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import an immutable compiler/cache artifact into an existing weighted account. |
| inputs / outputs | Nonempty account, CompiledProgram and optional Options produce receiving-owned metadata/state. |
| invariants | A foreign source account is not mutated; a deliberately shared source/receiver account is valid. Runtime lifetime is independent of source facade. |
| ownership | New metadata, context and native state all use receiver; source is borrowed during freeze only. |
| failure | Empty account rejects before helper fallback or allocation; normalized SQL and finite-cap failures retain prior account residents. |
| cost | Native metadata clone/import, no retained compiler DTO mirror. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0047

[Lines 301–301](../../../../../../include/crown/runtime/weighted.hpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L301-L301:sha256:c0e8119d88cb8bc7a0efb821d29d72b7b16f7db60a6bd790cb13d4bbfab62410
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the fixed weighted execution description. |
| inputs / outputs | No input; a constexpr Profile value containing static string_views. |
| invariants | Description identifies logical weighted execution, not full SQL/W05 admission. |
| ownership | Static literals only; no owner lookup or live-state borrowing. |
| failure | noexcept; cannot fail. |
| cost | Compile-time/fixed inline value, no allocation. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0048

[Lines 302–315](../../../../../../include/crown/runtime/weighted.hpp#L302); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L302-L315:sha256:ac064fb9a940e4a56146ca66b9f026971a47882f39e1aa36a8d6f1bb402b529c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare facade observations and exclusive update/cursor entry points. |
| inputs / outputs | Admitted options/account/sequence/status/root/attempt/stats; begin/apply/snapshot/results APIs. |
| invariants | Reads distinguish committed and explicit tentative state. Ordinary root/snapshot reject a private epoch; readers exclude all writers. |
| ownership | References borrow a live facade; owning snapshots/results retain the account. All calls are serialized. |
| failure | Moved facade rejects; state-dependent reads/admission enforce busy/sequence/resource checks in implementations. |
| cost | Scalar observations are fixed cost; updates/captures/cursors charge actual traversed state separately. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

```text
[[nodiscard]] const weighted::Options& options() const; [[nodiscard]] std::uint64_t owner() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the bridge-facing declaration separate from existing weighted runtime public accessors. |
| inputs / outputs | The accessor group continues to expose ordinary options/owner/sequence/readiness; cold sequence/storage construction remains friend-only. |
| invariants | No accessor sets sequence, substitutes a StorageWorkContext or fabricates a weighted binding. |
| ownership | Ordinary references/spans retain their existing owner lifetimes. |
| failure | Existing moved/closed owner errors remain unchanged. |
| cost | No new public operation or hot-field cost. |
| Design | [include/crown/runtime/weighted.hpp](../../../../../../include/crown/runtime/weighted.hpp), [src/runtime/weighted.cpp](../../../../../../src/runtime/weighted.cpp), [docs/weighted_messages.md §Ownership, transaction and identity](../../../../../weighted_messages.md) |

## B0049

[Lines 316–316](../../../../../../include/crown/runtime/weighted.hpp#L316); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L316-L316:sha256:ff2205c0f9a16f2e3e19644fda22801a65e833149067d74eab998344bd7166ee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt an already funded implementation for static create_into factories. |
| inputs / outputs | An owning shared_ptr&lt;Impl&gt; moves into impl_. |
| invariants | Only private callers that completed native admission can construct this way. |
| ownership | Move shared ownership; no new control block or source graph. |
| failure | noexcept; admission failures occur before adoption. |
| cost | Fixed owner move, allocation-free. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |

## B0050

[Lines 317–320](../../../../../../include/crown/runtime/weighted.hpp#L317); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L317-L320:sha256:eae40857704065cef8ac2f36300f13b8259314b759d129366aac08e206966d35
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the facade's sole implementation owner and validated borrowing helper. |
| inputs / outputs | Private impl() returns active Impl; shared_ptr retains its state. |
| invariants | Moved-from facade has no owner; pending/cursor tokens can independently retain it. |
| ownership | One shared owner handle, not duplicated numeric state. |
| failure | impl() rejects invalid_runtime when moved from. |
| cost | Fixed indirection/check; final release destroys actual funded state. |
| Design | [docs/weighted_messages.md](../../../../../weighted_messages.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md) |
