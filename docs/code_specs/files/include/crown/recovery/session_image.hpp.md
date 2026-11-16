# `include/crown/recovery/session_image.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/session_image.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `6028d25866a7259efd7f6c0cc668dfa34e7bd3f35a96559daf233e33331f1afa`. 39 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../../include/crown/recovery/session_image.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–9](../../../../../../include/crown/recovery/session_image.hpp#L6) | Type/record definition: struct SessionImageLimits |  · [reviewed contract](#b0002) |
| [B0003 · 10–17](../../../../../../include/crown/recovery/session_image.hpp#L10) | Type/record definition: struct SessionImageManifest |  · [reviewed contract](#b0003) |
| [B0004 · 18–24](../../../../../../include/crown/recovery/session_image.hpp#L18) | Type/record definition: struct SessionImage | source comment (unverified): // This record owns funded bytes; copying it can allocate and duplicate them. · [reviewed contract](#b0004) |
| [B0005 · 25–29](../../../../../../include/crown/recovery/session_image.hpp#L25) | Type/record definition: struct InspectedSessionImage |  · [reviewed contract](#b0005) |
| [B0006 · 30–39](../../../../../../include/crown/recovery/session_image.hpp#L30) | declares values/defaults or compile-time conditions. | source comment (unverified): // Complete CROWNSI1 session envelope, including its CROWNRI1 runtime component. · [reviewed contract](#b0006) |

## B0001

[Lines 1–5](../../../../../../include/crown/recovery/session_image.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose complete native session binary envelope metadata. |
| inputs / outputs | Includes SessionCheckpoint native state. |
| invariants | Runtime component alone insufficient; source options/progress/window state serialized here, actual Program/schema/window matching later. |
| ownership | No graph allocated by inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action. |
| Design | [include/crown/recovery/session_image.hpp](../../../../../../include/crown/recovery/session_image.hpp), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 6–9](../../../../../../include/crown/recovery/session_image.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionImageLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound complete session envelope structure/byte work. |
| inputs / outputs | Envelope128MiB/512Mi work/tables4096/rows2M/fields1024/scalar1MiB plus relation tokens and managed capacity4096. |
| invariants | Actual native source/window/runtime restore limits compose separately; metadata text/CSV shape and both parse passes counted, not CPU/RSS. Limits alone no account. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/session_image.hpp](../../../../../../include/crown/recovery/session_image.hpp), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 10–17](../../../../../../include/crown/recovery/session_image.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionImageManifest {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe complete session envelope frontiers and state. |
| inputs / outputs | Runtime manifest,state version/control/source kind/failure/EOF, physical committed and external accepted sequences. |
| invariants | Default state version is legacy 1. Codec admits declared version 2 separately. Public manifest is structural metadata; native source/window matching and durable publication remain independent checks. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/session_image.hpp](../../../../../../include/crown/recovery/session_image.hpp), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0004

[Lines 18–24](../../../../../../include/crown/recovery/session_image.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own complete encoded session envelope bytes. |
| inputs / outputs | ImageVector&lt;char&gt;, ImageStatistics and SessionImageManifest. |
| invariants | Wire checksum/manifest does not itself prove native semantics or durable file. Publisher re-inspects bytes rather than trusting mutable fields. |
| ownership | Owns receiving/original-account byte vector; copies allocate/deep-copy, moves transfer storage. |
| failure | Aggregate copies can throw/no whole-record assignment guarantee; encoder privately prepares complete output. |
| cost | O(B) owning byte copy; fixed metadata; release one trivial vector block, no hash or native rebuild. |
| Design | [include/crown/recovery/session_image.hpp](../../../../../../include/crown/recovery/session_image.hpp), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 25–29](../../../../../../include/crown/recovery/session_image.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InspectedSessionImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return allocation-free session envelope inspection metadata. |
| inputs / outputs | Manifest, fixed DeltaOptions and ImageStatistics. |
| invariants | All bytes/structure/inner runtime checked and future parse budget reserved. No decoded native graph, Program/source/window semantic admission or durable authority. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/session_image.hpp](../../../../../../include/crown/recovery/session_image.hpp), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 30–39](../../../../../../include/crown/recovery/session_image.hpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] SessionImage encode_session_image(const resource::MemoryAccount&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete native checkpoint into one envelope. |
| inputs / outputs | Account, stable SessionCheckpoint, finite native/envelope limits. |
| invariants | Inspect nested runtime image, epoch/policy coherence, source/window metadata structure; preflight both writer passes before final buffer. Public checkpoint may be caller-constructed, so no claim semantic native admission already happened. |
| ownership | Funded final byte vector, native state/row views borrowed through unchanged passes; no ordinary row mirror. |
| failure | ImageFailure/work/limit/binding/scalar/account/OOM unwinds new envelope; source state unchanged, no file IO. |
| cost | O(envelope+inner runtime bytes/metadata row structure+CSV/source validation comparisons) preflight/write/SHA; real output plus existing native graph coexist. |
| Design | [include/crown/recovery/session_image.hpp](../../../../../../include/crown/recovery/session_image.hpp), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] InspectedSessionImage inspect_session_image(std::string_view,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect complete session wire structure without decoded heap graph. |
| inputs / outputs | Stable immutable byte view, native/envelope limits return fixed InspectedSessionImage. |
| invariants | Validate outer SHA/length/version/state/source/options/window structure and nested runtime epoch/policy; reserves materialization pass work. Program/catalog/base/window semantic joins belong to QuerySession restore. |
| ownership | No input retained in public fixed result, no receiving account or row/metadata graph allocated. |
| failure | Fixed ImageFailure on invalid/resource input; no repair/native mutation. |
| cost | O(bytes+metadata comparisons) hash/parse/inner image inspection; CSV/source/permutation comparisons actual, allocation-free. |
| Design | [include/crown/recovery/session_image.hpp](../../../../../../include/crown/recovery/session_image.hpp), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
inline constexpr std::size_t session_image_header_size=84;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set complete session envelope header width. |
| inputs / outputs | session_image_header_size=84. |
| invariants | CROWNSI1 header/body SHA framing; nested CROWNRI1 has separate84-byte header/checksum. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/recovery/session_image.hpp](../../../../../../include/crown/recovery/session_image.hpp), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |
