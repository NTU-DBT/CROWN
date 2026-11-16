# `include/crown/runtime/session.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/session.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Own input-to-output and durable lifecycle transitions for one creator-thread query session.

Snapshot SHA-256: `00de8d9be24ed77c620969c7728059f1aac3863297edb18e14985550151a9397`. 367 lines partitioned into 36 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/native-replay.md](../../../../../native-replay.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/runtime/session.hpp#L1) | Imports dependencies; guards repeated header inclusion. |  · [reviewed contract](#b0001) |
| [B0002 · 14–38](../../../../../../include/crown/runtime/session.hpp#L14) | declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0002) |
| [B0003 · 39–39](../../../../../../include/crown/runtime/session.hpp#L39) | Type/record definition: enum class SessionBegin |  · [reviewed contract](#b0003) |
| [B0004 · 40–40](../../../../../../include/crown/runtime/session.hpp#L40) | Type/record definition: enum class SessionState |  · [reviewed contract](#b0004) |
| [B0005 · 41–41](../../../../../../include/crown/runtime/session.hpp#L41) | Type/record definition: enum class SessionPhase |  · [reviewed contract](#b0005) |
| [B0006 · 42–55](../../../../../../include/crown/runtime/session.hpp#L42) | Type/record definition: struct SessionStatus |  · [reviewed contract](#b0006) |
| [B0007 · 56–64](../../../../../../include/crown/runtime/session.hpp#L56) | Type/record definition: struct SnapshotLimits | source comment (unverified): // Actual retained collection/control/capacity requests plus each native · [reviewed contract](#b0007) |
| [B0008 · 65–73](../../../../../../include/crown/runtime/session.hpp#L65) | Type/record definition: struct SessionOptions | source comment (unverified): // Input options own ordinary token/text storage; copying them may allocate. · [reviewed contract](#b0008) |
| [B0009 · 74–74](../../../../../../include/crown/runtime/session.hpp#L74) | Type/record definition: enum class SessionInputKind |  · [reviewed contract](#b0009) |
| [B0010 · 75–76](../../../../../../include/crown/runtime/session.hpp#L75) | Explanatory comments or spacing. | source comment (unverified): // Constructed once during session admission, never copied by observation hooks. · [reviewed contract](#b0010) |
| [B0011 · 77–88](../../../../../../include/crown/runtime/session.hpp#L77) | Type/record definition: struct SessionRunContext | source comment (unverified): // Constructed once during session admission, never copied by observation hooks. · [reviewed contract](#b0011) |
| [B0012 · 89–99](../../../../../../include/crown/runtime/session.hpp#L89) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Immutable snapshot collection. Copies retain the original funded storage; · [reviewed contract](#b0012) |
| [B0013 · 100–100](../../../../../../include/crown/runtime/session.hpp#L100) | Callable definition: \[\[nodiscard\]\] bool empty() const noexcept | calls size; returns size()==0 · [reviewed contract](#b0013) |
| [B0014 · 101–101](../../../../../../include/crown/runtime/session.hpp#L101) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0014) |
| [B0015 · 102–102](../../../../../../include/crown/runtime/session.hpp#L102) | Callable definition: \[\[nodiscard\]\] const storage::Tuple& operator\[\](std::size_t i) const noexcept | calls ; returns data()\[i\] · [reviewed contract](#b0015) |
| [B0016 · 103–103](../../../../../../include/crown/runtime/session.hpp#L103) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0016) |
| [B0017 · 104–104](../../../../../../include/crown/runtime/session.hpp#L104) | Callable definition: \[\[nodiscard\]\] const storage::Tuple& front() const noexcept | calls ; returns (*this)\[0\] · [reviewed contract](#b0017) |
| [B0018 · 105–105](../../../../../../include/crown/runtime/session.hpp#L105) | Callable definition: \[\[nodiscard\]\] const storage::Tuple& back() const noexcept | calls size; returns (*this)\[size()-1\] · [reviewed contract](#b0018) |
| [B0019 · 106–106](../../../../../../include/crown/runtime/session.hpp#L106) | Callable definition: \[\[nodiscard\]\] const_iterator begin() const noexcept | calls data, size; returns std::span&lt;const storage::Tuple&gt;{data(),size()}.begin() · [reviewed contract](#b0019) |
| [B0020 · 107–107](../../../../../../include/crown/runtime/session.hpp#L107) | Callable definition: \[\[nodiscard\]\] const_iterator end() const noexcept | calls data, size; returns std::span&lt;const storage::Tuple&gt;{data(),size()}.end() · [reviewed contract](#b0020) |
| [B0021 · 108–108](../../../../../../include/crown/runtime/session.hpp#L108) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |
| [B0022 · 109–109](../../../../../../include/crown/runtime/session.hpp#L109) | Callable definition: \[\[nodiscard\]\] resource::MemoryStatistics account_statistics() const | calls statistics; returns account_.statistics() · [reviewed contract](#b0022) |
| [B0023 · 110–112](../../../../../../include/crown/runtime/session.hpp#L110) | declares types or opens a type body. |  · [reviewed contract](#b0023) |
| [B0024 · 113–113](../../../../../../include/crown/runtime/session.hpp#L113) | Callable definition: explicit SessionRows(const resource::MemoryAccount& account) noexcept:account_(account) | calls account_ · [reviewed contract](#b0024) |
| [B0025 · 114–120](../../../../../../include/crown/runtime/session.hpp#L114) | declares callable signatures; declares values/defaults or compile-time conditions. | growth reserve · [reviewed contract](#b0025) |
| [B0026 · 121–130](../../../../../../include/crown/runtime/session.hpp#L121) | Type/record definition: struct SessionSnapshot | source comment (unverified): // Copies share SessionRows; copying exported progress maps/text may allocate. · [reviewed contract](#b0026) |
| [B0027 · 131–132](../../../../../../include/crown/runtime/session.hpp#L131) | Explanatory comments or spacing. | source comment (unverified): // Immutable metadata-only handle sharing the actual accounted program. · [reviewed contract](#b0027) |
| [B0028 · 133–154](../../../../../../include/crown/runtime/session.hpp#L133) | Type/record definition: class SessionReportMetadata | returns plan_; options_; source comment (unverified): // Immutable metadata-only handle sharing the actual accounted program. · [reviewed contract](#b0028) |
| [B0029 · 155–157](../../../../../../include/crown/runtime/session.hpp#L155) | Explanatory comments or spacing. | source comment (unverified): // One guarded runtime-only diagnostic boundary. Factory-produced and owning; · [reviewed contract](#b0029) |
| [B0030 · 158–178](../../../../../../include/crown/runtime/session.hpp#L158) | Type/record definition: class SessionStatisticsContext | returns *this; source comment (unverified): // One guarded runtime-only diagnostic boundary. Factory-produced and owning; · [reviewed contract](#b0030) |
| [B0031 · 179–214](../../../../../../include/crown/runtime/session.hpp#L179) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Synchronous, creator-thread writer ownership. Owns the input stream and all · [reviewed contract](#b0031) |
| [B0032 · 215–250](../../../../../../include/crown/runtime/session.hpp#L215) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Null while private session work exists or after runtime release. This · [reviewed contract](#b0032) |
| [B0033 · 251–286](../../../../../../include/crown/runtime/session.hpp#L251) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Admission is allowed before start, but not while paused or terminal. · [reviewed contract](#b0033) |
| [B0034 · 287–322](../../../../../../include/crown/runtime/session.hpp#L287) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Select a durable checkpoint/log pair through a separately locked root. · [reviewed contract](#b0034) |
| [B0035 · 323–358](../../../../../../include/crown/runtime/session.hpp#L323) | controls preprocessing; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Stop is terminal; abort unpublished work, release source/output buffers, · [reviewed contract](#b0035) |
| [B0036 · 359–367](../../../../../../include/crown/runtime/session.hpp#L359) | controls preprocessing; declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0036) |

## B0001

[Lines 1–13](../../../../../../include/crown/runtime/session.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one stable synchronous query/session owner. |
| inputs / outputs | Includes native/typed input, window, Delta, reoptimization, workload and original-account ownership interfaces. |
| invariants | Facade coordinates real source/engine/output/durable barriers; header flags do not grant them. |
| ownership | No live session admitted by inclusion. |
| failure | Compile-time dependency boundary. |
| cost | No runtime action at inclusion. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 14–38](../../../../../../include/crown/runtime/session.hpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace crown::recovery {struct SessionImage;struct SessionImageLimits;struct CheckpointFileLimits;struct PublishedCheckpoint;struct GenerationRoot;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward declare durable/compiler/session helper types. |
| inputs / outputs | Recovery headers/images/limits/receipts/roots, compiler artifact and session option/status types remain defined in dedicated headers. |
| invariants | Forward declarations are not public durable/native authority or hidden file-open operations. |
| ownership | No owner allocated; later concrete methods adopt their actual locks/accounts/files. |
| failure | Compile-time declaration only. |
| cost | No runtime work. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [include/crown/runtime/session_journal.hpp](../../../../../../include/crown/runtime/session_journal.hpp), [include/crown/runtime/session_generation.hpp](../../../../../../include/crown/runtime/session_generation.hpp), [include/crown/runtime/session_local_sink.hpp](../../../../../../include/crown/runtime/session_local_sink.hpp) |

```text
void begin_reoptimization(QuerySession&,const CurrentSelection&,reoptimization::Options);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin reoptimization from current measured typed selection. |
| inputs / outputs | QuerySession, CurrentSelection and Options; selection adapter revalidates current capture/policy/source/options and measured preparation time before private candidate creation. |
| invariants | Equal fields/labels do not substitute typed selection; session creator-thread/committed-delivered barrier still enforced. |
| ownership | Borrows selection during call; candidate retains its actual checked plan/evidence on original account. |
| failure | Unmeasured/stale/source-policy mismatch rejects before candidate; later native candidate failure propagates. |
| cost | Cold current-evidence capture/validation and candidate construction; measured selection time carried into actual preparation accounting. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp) |

## B0003

[Lines 39–39](../../../../../../include/crown/runtime/session.hpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SessionBegin { pending, would_block, end };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify attempted next-input admission. |
| inputs / outputs | pending/would_block/end. |
| invariants | would_block includes open-empty queue, frozen reoptimization or pending durable delivery; end only validated EOF. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 40–40](../../../../../../include/crown/runtime/session.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SessionState { created, running, paused, stopped, dropped };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify session control lifecycle. |
| inputs / outputs | created/running/paused/stopped/dropped. |
| invariants | Control is distinct from private/output phase; stopped retains committed runtime, dropped releases it. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 41–41](../../../../../../include/crown/runtime/session.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SessionPhase { ready, pending, paused_pending, draining, prepared, output };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify work/output phase. |
| inputs / outputs | ready/pending/paused_pending/draining/prepared/output. |
| invariants | Output includes pending recovery/durable delivery; it is not a durability certificate. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 42–55](../../../../../../include/crown/runtime/session.hpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionStatus {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy current session control/phase diagnostics. |
| inputs / outputs | Control/phase, committed/private sequence/work, failure/EOF, queue/window progress and optional committed UpdatePatternStatus. |
| invariants | Private work is not committed acceptance. Command and physical sequences differ. Pattern status names the actual owning tree and distinguishes fresh enforcement from trusted restored history; it grants no structural or CPU-bound authority. |
| ownership | Caller owns fixed fields and an optional immutable Declaration handle. That handle can retain its original account-funded metadata after Session destruction; no runtime rows are copied. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed fields and shared-handle copy; no rule-vector allocation, table scan or clock. Final declaration-owner release can destroy O(R) metadata. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0007

[Lines 56–64](../../../../../../include/crown/runtime/session.hpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SnapshotLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound explicit snapshot enumeration and retained result storage. |
| inputs / outputs | Row bound65536, byte bound64MiB and fixed ResultCursorOptions. |
| invariants | Byte sublimit includes actual collection control/capacity and native tuple ownership/framing; excludes progress/shared metadata/cursor scratch. Original query cap also funds transient old/new capacities. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Fixed inline scalar/enum/optional/array storage and bounded copies; no dynamic payload, scan, clock or allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 65–73](../../../../../../include/crown/runtime/session.hpp#L65); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own caller session admission settings. |
| inputs / outputs | Ordinary InputOptions, Delta/Snapshot settings, shared benchmark context and optional UpdatePatternOptions containing a requested declaration and capture limits. |
| invariants | Typed factories reject unrelated wire profiles; native runtime factories validate actual plan/options. Benchmark strings remain caller claims. |
| ownership | Input text/map copies own ordinary storage; benchmark/declaration copies share their actual owners. Session admission explicitly copies declaration metadata into its original query account. |
| failure | Ordinary options copy can allocate/throw; admission failures release unpublished graph/owned stream. |
| cost | O(input token/text bytes) owning copy plus fixed settings/refcounts. Opt-in native admission additionally validates/copies R rules under explicit limits. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0009

[Lines 74–74](../../../../../../include/crown/runtime/session.hpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SessionInputKind { owned_stream, typed_physical, typed_window };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify admitted source ownership kind. |
| inputs / outputs | owned_stream/typed_physical/typed_window. |
| invariants | Input source kind is captured actual admission metadata; public tag alone cannot reconstruct a source or authorize restore. |
| ownership | Caller owns inline numeric/tag fields; this record retains no backing runtime, rows, strings or allocation grant. |
| failure | The declaration does not validate public fields or translate failure. Actual factories/consumers perform the stated checks. |
| cost | Constant-size enum/tag, no allocation, scan or clock. Arbitrary enum casts are not admitted automatically. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 75–76](../../../../../../include/crown/runtime/session.hpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L76:sha256:ade3e14590f1e8ed3f85794f22b0ccb46576cabda89fe70d2d47d1adfdea71e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct SessionRunContext\`: Constructed once during session admission, never copied by observation hooks. Exact native bytes remain native bytes; strict text encoding is an export duty. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/session.hpp:L74; use that declaration for the actual input/output shape. |
| invariants | The source note states: Constructed once during session admission, never copied by observation hooks. Exact native bytes remain native bytes; strict text encoding is an export duty. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0011

[Lines 77–88](../../../../../../include/crown/runtime/session.hpp#L77); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionRunContext {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable actual session admission context. |
| inputs / outputs | Actual input kind/options, queue/window/snapshot/initialization/mode settings and optional admitted source-bound declaration. |
| invariants | Admission records the actual receiving declaration. Replacement checks the same source and retains the immutable request. Live monitor progress is in SessionStatus, not this immutable record. |
| ownership | Context copies share immutable input, window-table and declaration owners; initial admission/import funds their receiving copies. Final release can destroy those graphs. |
| failure | Native admission/import may throw; fixed/shared-handle context copies themselves do not allocate payload. |
| cost | Context control allocation at admission; direct copy fixed refcounts/settings, final input-map/table-owner teardown may be larger. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0012

[Lines 89–99](../../../../../../include/crown/runtime/session.hpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SessionRows {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share an immutable published snapshot row collection. |
| inputs / outputs | Private Data owns funded vector&lt;storage::Tuple&gt;; public read-only methods expose size/data/index/iterators and actual collection usage. |
| invariants | QuerySession alone mutates before publication; prepare rejects data_.use_count()!=1. Default/moved empty has no rows. Copies share actual row/vector/control storage; standard move transfers it. |
| ownership | Account retained separately from Data; Data/tuple payload/layout owners remain alive through last SessionRows copy. Borrowed references/iterators retain nothing. |
| failure | Capture construction can throw; plain collection copy/refcount does not deep-copy rows. Default unbound account_statistics can throw; unchecked element access requires valid bounds. |
| cost | Handle copy O(1), explicit snapshot scan/vector/tuple creation charged separately; final release visits Tuple owners and frees vector/control/account. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionRows() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty unbound row collection. |
| inputs / outputs | Default account/data empty. |
| invariants | size/capacity0 and data null; no allowance created. |
| ownership | Owns no row storage. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1), no allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::size_t size() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read snapshot row size. |
| inputs / outputs | Returns row count. |
| invariants | Default/moved empty safely returns zero/null. |
| ownership | Any pointer borrows shared Data; retain SessionRows owner. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::size_t capacity() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read snapshot row capacity. |
| inputs / outputs | Returns actual vector capacity. |
| invariants | Default/moved empty safely returns zero/null. |
| ownership | Any pointer borrows shared Data; retain SessionRows owner. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 100–100](../../../../../../include/crown/runtime/session.hpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool empty() const noexcept {return size()==0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test snapshot row emptiness. |
| inputs / outputs | Returns size()==0. |
| invariants | Does not scan or enumerate. |
| ownership | Independent boolean. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 101–101](../../../../../../include/crown/runtime/session.hpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const storage::Tuple* data() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read snapshot row data pointer. |
| inputs / outputs | Returns Tuple pointer or nullptr. |
| invariants | Default/moved empty safely returns zero/null. |
| ownership | Any pointer borrows shared Data; retain SessionRows owner. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 102–102](../../../../../../include/crown/runtime/session.hpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const storage::Tuple& operator[](std::size_t i) const noexcept {return data()[i];}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow snapshot tuple by unchecked index. |
| inputs / outputs | Returns data()\[i\]. |
| invariants | Requires i&lt;size; no bounds-handling overhead. |
| ownership | Tuple reference borrows SessionRows Data; copying Tuple retains its own immutable payload/layout if desired. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0016

[Lines 103–103](../../../../../../include/crown/runtime/session.hpp#L103); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const storage::Tuple& at(std::size_t) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow snapshot tuple with bounds check. |
| inputs / outputs | Returns indexed tuple, throws std::out_of_range for i&gt;=size. |
| invariants | No element copy or runtime access. |
| ownership | Reference borrows Data. |
| failure | Bounds failure constructs/throws standard exception; no local catch. |
| cost | O(1), no allocation on successful read. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 104–104](../../../../../../include/crown/runtime/session.hpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const storage::Tuple& front() const noexcept {return (*this)[0];}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow snapshot front tuple. |
| inputs / outputs | Returns first/last via unchecked index. |
| invariants | Requires nonempty collection. |
| ownership | Reference borrows retained Data. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 105–105](../../../../../../include/crown/runtime/session.hpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const storage::Tuple& back() const noexcept {return (*this)[size()-1];}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow snapshot back tuple. |
| inputs / outputs | Returns first/last via unchecked index. |
| invariants | Requires nonempty collection. |
| ownership | Reference borrows retained Data. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0019

[Lines 106–106](../../../../../../include/crown/runtime/session.hpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const_iterator begin() const noexcept {return std::span<const storage::Tuple>{data(),size()}.begin();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow snapshot begin iterator. |
| inputs / outputs | Returns span&lt;const Tuple&gt; iterator. |
| invariants | Empty range valid; no ownership on iterator. |
| ownership | Keep SessionRows sharing Data alive during iteration. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 107–107](../../../../../../include/crown/runtime/session.hpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const_iterator end() const noexcept {return std::span<const storage::Tuple>{data(),size()}.end();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow snapshot end iterator. |
| inputs / outputs | Returns span&lt;const Tuple&gt; iterator. |
| invariants | Empty range valid; no ownership on iterator. |
| ownership | Keep SessionRows sharing Data alive during iteration. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0021

[Lines 108–108](../../../../../../include/crown/runtime/session.hpp#L108); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] resource::MemoryUsage memory_usage() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual row-collection control/capacity usage. |
| inputs / outputs | Adds saved Data/control allocation delta plus exact vector allocation_usage(capacity). |
| invariants | Excludes each tuple payload/layout, progress/cursor and total query usage; SessionSnapshot.accounted_bytes adds actual tuple payload separately. |
| ownership | Returns fixed MemoryUsage; retains no new owner. |
| failure | Can propagate allocator contract if private invariants broken; no handler. |
| cost | O(1) allocation-header reads/fixed sums, no scan/clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0022

[Lines 109–109](../../../../../../include/crown/runtime/session.hpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] resource::MemoryStatistics account_statistics() const {return account_.statistics();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the retained snapshot original account counters. |
| inputs / outputs | Returns account_.statistics() by value. |
| invariants | Account-wide current/history counters, not just collection; default unbound collection has no readable account. |
| ownership | Collection retains account, returned fixed counters do not. |
| failure | Empty account can throw MemoryFailure(contract); signature is not noexcept. |
| cost | O(1) fixed counter copy, no ledger scan. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0023

[Lines 110–112](../../../../../../include/crown/runtime/session.hpp#L110); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
friend class QuerySession;
  struct Data;
  explicit SessionRows(const resource::MemoryAccount& account) noexcept:account_(account) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict snapshot row mutation to the actual session factory. |
| inputs / outputs | Private QuerySession friendship and incomplete Data declaration precede funded preparation helpers. |
| invariants | Public row references/iterators are const; only prepublication unique Data is mutable through private helpers. |
| ownership | Data/control/capacity retain actual original account, not a caller grant inferred from public fields. |
| failure | Compile-time access boundary; prepare additionally checks actual unique ownership at runtime. |
| cost | No runtime action for friendship/forward declaration. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0024

[Lines 113–113](../../../../../../include/crown/runtime/session.hpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit SessionRows(const resource::MemoryAccount& account) noexcept:account_(account) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind an empty private snapshot collection to query account. |
| inputs / outputs | QuerySession-only constructor copies MemoryAccount. |
| invariants | No control/vector/row allocation until prepare/reserve/append. |
| ownership | Retains same grant; no new allowance. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) account retain. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0025

[Lines 114–120](../../../../../../include/crown/runtime/session.hpp#L114); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare unique mutable snapshot Data before publication. |
| inputs / outputs | If existing Data require sole owner; otherwise allocate accounted Data/control with empty vector and record exact before/after allocation delta. |
| invariants | No shared published collection may be mutated. Constructor has no nested allocation, so control delta is exact. |
| ownership | Private Data uses output:0 original account; no rows copied. |
| failure | OOM/account failure frees unpublished control; existing data unchanged. |
| cost | One actual control allocation/counter sampling, no row scan. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void reserve(std::size_t);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve private snapshot row capacity. |
| inputs / outputs | Calls prepare then vector.reserve(capacity). |
| invariants | Only prepublication unique Data may mutate; snapshot caller preflights retained sublimit and actual query cap. |
| ownership | Vector allocation stays on original account; old/new capacity can coexist transiently. |
| failure | Reserve failure preserves prior vector; allocation history may change. |
| cost | O(existing row count) Tuple ownership moves on growth plus capacity allocation; no deep row-byte clone by vector move. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void append(storage::Tuple);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one owned native snapshot tuple. |
| inputs / outputs | prepare, verify tuple.is_accounted and matching actual account owner, then move tuple into values. |
| invariants | No foreign/free allowance row may enter collection; QuerySession funds/preflights capacity. |
| ownership | Destination tuple adopts existing payload/layout ownership; no caller borrow retained. |
| failure | Validation/allocation failure occurs before public snapshot return; private result unwinds, runtime/unread output unchanged. |
| cost | O(1) tuple move with reserved capacity, possible vector growth if internal caller omitted reserve; no row export. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] resource::MemoryUsage owner_usage() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read saved collection control allocation usage. |
| inputs / outputs | Returns Data.control_usage or zero. |
| invariants | Only Data/control request, excludes vector and row payload. |
| ownership | Fixed counter return. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
resource::MemoryAccount account_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain snapshot account plus immutable-by-public-API Data. |
| inputs / outputs | MemoryAccount and shared_ptr&lt;Data&gt;. |
| invariants | Private helpers enforce unique mutation before publication; public methods cannot mutate vector. |
| ownership | Copies retain shared row storage/account; standard moves can empty source handles. Last release visits Tuple owners then frees vector/control. |
| failure | No allocating cleanup; public account stats require nonempty account. |
| cost | Fixed handle copy/transfer; final teardown O(row owners) and their last payload/layout graphs. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0026

[Lines 121–130](../../../../../../include/crown/runtime/session.hpp#L121); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionSnapshot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a detached committed session snapshot. |
| inputs / outputs | Sequence, ordinary exported InputProgress map/text, shared layout token, SessionRows handle, accounted byte total and optional fixed WindowProgress. |
| invariants | Copying does not reenumerate rows: it shares collection/layout, but progress owns ordinary map/string bytes. Sequence/flags/byte totals are public DTO facts, not native/durable authority. |
| ownership | Owns progress outside native account; row collection and tuple payload/control remain funded actual account; layout shares immutable owner. |
| failure | Snapshot factory can throw at enumeration/progress export/caps. Ordinary DTO copy/assignment can allocate via progress and has no special whole-record strong publication guarantee. |
| cost | Copy O(progress source map/text)+O(1) row/layout retention; factory enumerates all result rows/bytes. Release visits progress map and last actual row owners. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp) |

## B0027

[Lines 131–132](../../../../../../include/crown/runtime/session.hpp#L131); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L131-L132:sha256:14140865121cc6be1f6579a833874707158bb3a57b8a0642cced68ffc005f909
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class SessionReportMetadata\`: Immutable metadata-only handle sharing the actual accounted program. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/session.hpp:L129; use that declaration for the actual input/output shape. |
| invariants | The source note states: Immutable metadata-only handle sharing the actual accounted program. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Immutable metadata-only handle sharing the actual accounted program. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0028

[Lines 133–154](../../../../../../include/crown/runtime/session.hpp#L133); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SessionReportMetadata {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable actual program and fixed session report metadata. |
| inputs / outputs | Private factory plan/options/profile/owner/sequence/optional DeltaState. |
| invariants | After drop state becomes disengaged while retained plan/options/owner/sequence remain. Profile text points to static literals; copied labels are not proof/durable authority. |
| ownership | CompiledProgram handle retains actual admitted graph/account, not runtime. Fixed options/profile refs do not own copied table rows. |
| failure | Explicit copy constructor/assignment noexcept; no implicit move declared, so rvalue copying still shares plan. Last plan release can destroy metadata graph. |
| cost | O(1) refcount plus fixed options/profile copy; final actual plan cleanup may be larger. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/delta.hpp](../../../../../../include/crown/runtime/delta.hpp) |

```text
SessionReportMetadata(const SessionReportMetadata&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy report metadata by construction. |
| inputs / outputs | Copies CompiledProgram shared owner and fixed options/profile/scalars. |
| invariants | Does not refresh current runtime or mint evidence. |
| ownership | Retains actual plan; assignment may release last old plan. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | Fixed refcount/settings copy plus possible last-plan teardown. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionReportMetadata& operator=(const SessionReportMetadata&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy report metadata by assignment. |
| inputs / outputs | Copies CompiledProgram shared owner and fixed options/profile/scalars. |
| invariants | Does not refresh current runtime or mint evidence. |
| ownership | Retains actual plan; assignment may release last old plan. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | Fixed refcount/settings copy plus possible last-plan teardown. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const CompiledProgram& plan() const noexcept { return plan_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read report metadata plan. |
| inputs / outputs | Returns const CompiledProgram&. |
| invariants | Admitted metadata, not a mutable runtime reference. |
| ownership | Scalar values independent; reference results borrow this metadata/retained plan. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const DeltaOptions& options() const noexcept { return options_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read report metadata requested Delta options. |
| inputs / outputs | Returns const DeltaOptions&. |
| invariants | Exact stored options, not a request to change runtime. |
| ownership | Scalar values independent; reference results borrow this metadata/retained plan. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const DeltaRuntimeProfile& profile() const noexcept { return profile_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read report metadata runtime profile. |
| inputs / outputs | Returns const DeltaRuntimeProfile&. |
| invariants | Bounds are qualified static text, no new measured cost claim. |
| ownership | Scalar values independent; reference results borrow this metadata/retained plan. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] SupportOwnerId owner() const noexcept { return owner_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read report metadata support owner. |
| inputs / outputs | Returns SupportOwnerId. |
| invariants | Process-local actual capture label, not durable authority. |
| ownership | Scalar values independent; reference results borrow this metadata/retained plan. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::uint64_t sequence() const noexcept { return sequence_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read report metadata committed sequence. |
| inputs / outputs | Returns uint64_t. |
| invariants | As-of report metadata, not live freshness. |
| ownership | Scalar values independent; reference results borrow this metadata/retained plan. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::optional<DeltaState> state() const noexcept { return state_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read report metadata runtime state. |
| inputs / outputs | Returns optional&lt;DeltaState&gt;. |
| invariants | Disengaged after release; retained graph still readable. |
| ownership | Scalar values independent; reference results borrow this metadata/retained plan. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionReportMetadata(CompiledProgram plan,DeltaOptions options,DeltaRuntimeProfile profile,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct private metadata from actual session owner. |
| inputs / outputs | Adopts CompiledProgram by value and copies fixed settings/profile/owner/sequence/state. |
| invariants | QuerySession alone creates this pairing at guarded reads/retained teardown. |
| ownership | Plan retains actual graph/account, no runtime/pins. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | Fixed handle adoption/copy, no new graph allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0029

[Lines 155–157](../../../../../../include/crown/runtime/session.hpp#L155); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L155-L157:sha256:188ecc521b516dbdd684841ac624c422eca0f6dbabf8ef3783449f565cc84414
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class SessionStatisticsContext\`: One guarded runtime-only diagnostic boundary. Factory-produced and owning; no report/observability dependency or public metadata constructor. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/session.hpp:L154; use that declaration for the actual input/output shape. |
| invariants | The source note states: One guarded runtime-only diagnostic boundary. Factory-produced and owning; no report/observability dependency or public metadata constructor. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: One guarded runtime-only diagnostic boundary. Factory-produced and owning; no report/observability dependency or public metadata constructor. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0030

[Lines 158–178](../../../../../../include/crown/runtime/session.hpp#L158); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SessionStatisticsContext {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share one guarded runtime statistics context. |
| inputs / outputs | Private immutable Data owns metadata/status, native captured trace, optional CombinedCapture, workload options, cursor snapshot and state-request flag. |
| invariants | Factory synchronizes actual session observation, owner/workload/pending scope under one creator-thread Guard. Caller cannot public-construct arbitrary metadata pairings. |
| ownership | Shared handle retains actual captured trace/counter/owner graphs and program account, not session runtime. Copies/copy-like moves share Data; views borrow. |
| failure | Capture can allocate/throw; ordinary handle copies/moves noexcept, last release destroys actual nested native payload. |
| cost | Handle copy O(1); factory trace O(R), workload arrays O(D), optional state population scans plus Data/control; final capture graph cleanup real. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionStatisticsContext(const SessionStatisticsContext&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide context copy construction. |
| inputs / outputs | Retains shared Data; explicit moves copy shared pointer. |
| invariants | Both factory-produced handles remain readable; old destination views require another retaining handle. |
| ownership | Shares actual capture graphs; assignment may free old last graph. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) refcount plus old last graph teardown; no deep trace/state copy. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionStatisticsContext(SessionStatisticsContext&& other) noexcept:data_(other.data_) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide context copy-like move construction. |
| inputs / outputs | Retains shared Data; explicit moves copy shared pointer. |
| invariants | Both factory-produced handles remain readable; old destination views require another retaining handle. |
| ownership | Shares actual capture graphs; assignment may free old last graph. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) refcount plus old last graph teardown; no deep trace/state copy. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionStatisticsContext& operator=(const SessionStatisticsContext&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide context copy assignment. |
| inputs / outputs | Retains shared Data; explicit moves copy shared pointer. |
| invariants | Both factory-produced handles remain readable; old destination views require another retaining handle. |
| ownership | Shares actual capture graphs; assignment may free old last graph. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) refcount plus old last graph teardown; no deep trace/state copy. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionStatisticsContext& operator=(SessionStatisticsContext&& other) noexcept {data_=other.data_;return *this;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide context copy-like move assignment. |
| inputs / outputs | Retains shared Data; explicit moves copy shared pointer. |
| invariants | Both factory-produced handles remain readable; old destination views require another retaining handle. |
| ownership | Shares actual capture graphs; assignment may free old last graph. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) refcount plus old last graph teardown; no deep trace/state copy. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const SessionReportMetadata& metadata() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read context metadata. |
| inputs / outputs | Returns const SessionReportMetadata&. |
| invariants | Exact same guarded owner/plan boundary. |
| ownership | All references borrow Data; retain a SessionStatisticsContext handle during use. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const SessionStatus& status() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read context status. |
| inputs / outputs | Returns const SessionStatus&. |
| invariants | Phase/private diagnostics are not public results. |
| ownership | All references borrow Data; retain a SessionStatisticsContext handle during use. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const CapturedObservationTrace& trace() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read context trace. |
| inputs / outputs | Returns const CapturedObservationTrace&. |
| invariants | Native vector capture owned inside Data; borrowing it does not deep-copy. |
| ownership | All references borrow Data; retain a SessionStatisticsContext handle during use. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const std::optional<statistics::CombinedCapture>& combined() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read context combined state/workload capture. |
| inputs / outputs | Returns const optional&lt;CombinedCapture&gt;&. |
| invariants | A released session has no runtime capture. Pending state capture is metadata-only; workload cells contain committed facts while live diagnostic Metadata may already include the unfinished attempt. |
| ownership | All references borrow Data; retain a SessionStatisticsContext handle during use. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const workload::Options& workload_options() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read context workload options. |
| inputs / outputs | Returns const workload::Options&. |
| invariants | Current or retained settings independent from O07 timing. |
| ownership | All references borrow Data; retain a SessionStatisticsContext handle during use. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const std::optional<CursorObservation>& cursor() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read context cursor observation. |
| inputs / outputs | Returns const optional&lt;CursorObservation&gt;&. |
| invariants | Fixed diagnostic cursor lifetime, not a live lease. |
| ownership | All references borrow Data; retain a SessionStatisticsContext handle during use. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool state_requested() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read context state requested flag. |
| inputs / outputs | Returns bool. |
| invariants | Distinguishes absent state request from engaged empty selections; not proof facts available. |
| ownership | All references borrow Data; retain a SessionStatisticsContext handle during use. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) fixed member/view lookup; no allocation or clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit SessionStatisticsContext(std::shared_ptr<const Data> data) noexcept:data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt privately complete context Data. |
| inputs / outputs | QuerySession moves shared_ptr&lt;const Data&gt;. |
| invariants | All captures were prepared under one guard before handle publication. |
| ownership | Shares actual original-account Data/captured owners. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) transfer, no new payload copy. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0031

[Lines 179–214](../../../../../../include/crown/runtime/session.hpp#L179); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class QuerySession {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one stable synchronous query session and its durable/resources lifecycle. |
| inputs / outputs | AccountedUnique facade/Impl, owned source stream or typed queue, Delta runtime, private/output/window/candidate and optional durable owners. |
| invariants | All instance operations creator-thread/nonreentrant; destructor exclusive lifetime. No mutable runtime/token exposed. Initialization rows remain epoch0, accepted source starts0. |
| ownership | Session owns actual native account allocations/files/locks; shared returned metadata/rows/captures can retain their actual owners after stop/drop without retaining facade. |
| failure | Factories throw before publication on validation/OOM. Methods preserve their actual source/engine/durable barriers; destructor uses private nonthrowing cleanup, not throwing public Guard. |
| cost | Initial compile/freeze/build/copy can scan/allocate; per-epoch engine work/output preparation explicit. Stop/drop release owned graphs rather than constant-time labels. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
using Owner=resource::AccountedUnique<QuerySession>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define account-funded session facade ownership. |
| inputs / outputs | Owner=AccountedUnique&lt;QuerySession&gt;. |
| invariants | Stored MemoryDelete retains original account through destructor/facade free; ordinary unique_ptr default deleter is not equivalent. |
| ownership | Unique facade ownership, no session copy or move. |
| failure | Destroy requires exclusive lifetime, no new allocation. |
| cost | Fixed owner transfer; destruction performs actual session/resource cleanup. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp) |

```text
[[nodiscard]] static Owner create(PhysicalPlan plan,
      std::unique_ptr<std::istream> input,SessionOptions options={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create stream session from PhysicalPlan at empty epoch zero. |
| inputs / outputs | By-value plan/settings; takes owned unique_ptr&lt;istream&gt;. |
| invariants | Creator thread captured during admission. Empty runtime/accepted progress0. Owned stream required. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create(CompiledProgram plan,
      std::unique_ptr<std::istream> input,SessionOptions options={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create stream session from CompiledProgram at empty epoch zero. |
| inputs / outputs | By-value plan/settings; takes owned unique_ptr&lt;istream&gt;. |
| invariants | Creator thread captured during admission. Empty runtime/accepted progress0. Owned stream required. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create(PhysicalPlan plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create stream session from PhysicalPlan and initial database. |
| inputs / outputs | By-value plan/settings, borrowed initial Database and BuildOptions; takes owned unique_ptr&lt;istream&gt;. |
| invariants | Creator thread captured during admission. Initial rows validated/built, not fabricated input events; accepted progress0. Owned stream required. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create(CompiledProgram plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create stream session from CompiledProgram and initial database. |
| inputs / outputs | By-value plan/settings, borrowed initial Database and BuildOptions; takes owned unique_ptr&lt;istream&gt;. |
| invariants | Creator thread captured during admission. Initial rows validated/built, not fabricated input events; accepted progress0. Owned stream required. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create_typed(PhysicalPlan plan,
      io::QueueLimits limits={},SessionOptions options={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create typed session from PhysicalPlan at empty epoch zero. |
| inputs / outputs | By-value plan/settings; takes queue limits. |
| invariants | Creator thread captured during admission. Empty runtime/accepted progress0. Typed wire-format options rejected. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create_typed(CompiledProgram plan,
      io::QueueLimits limits={},SessionOptions options={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create typed session from CompiledProgram at empty epoch zero. |
| inputs / outputs | By-value plan/settings; takes queue limits. |
| invariants | Creator thread captured during admission. Empty runtime/accepted progress0. Typed wire-format options rejected. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create_typed(PhysicalPlan plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create typed session from PhysicalPlan and initial database. |
| inputs / outputs | By-value plan/settings, borrowed initial Database and BuildOptions; takes queue limits. |
| invariants | Creator thread captured during admission. Initial rows validated/built, not fabricated input events; accepted progress0. Typed wire-format options rejected. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create_typed(CompiledProgram plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create typed session from CompiledProgram and initial database. |
| inputs / outputs | By-value plan/settings, borrowed initial Database and BuildOptions; takes queue limits. |
| invariants | Creator thread captured during admission. Initial rows validated/built, not fabricated input events; accepted progress0. Typed wire-format options rejected. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create_windowed(PhysicalPlan plan,WindowOptions window,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create window session from PhysicalPlan at empty epoch zero. |
| inputs / outputs | By-value plan/settings; takes queue limits and WindowOptions. |
| invariants | Creator thread captured during admission. Empty runtime/accepted progress0. Typed wire-format options rejected. Managed window tables must initially be empty; static unmanaged rows permitted. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create_windowed(CompiledProgram plan,WindowOptions window,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create window session from CompiledProgram at empty epoch zero. |
| inputs / outputs | By-value plan/settings; takes queue limits and WindowOptions. |
| invariants | Creator thread captured during admission. Empty runtime/accepted progress0. Typed wire-format options rejected. Managed window tables must initially be empty; static unmanaged rows permitted. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create_windowed(PhysicalPlan plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create window session from PhysicalPlan and initial database. |
| inputs / outputs | By-value plan/settings, borrowed initial Database and BuildOptions; takes queue limits and WindowOptions. |
| invariants | Creator thread captured during admission. Initial rows validated/built, not fabricated input events; accepted progress0. Typed wire-format options rejected. Managed window tables must initially be empty; static unmanaged rows permitted. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner create_windowed(CompiledProgram plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create window session from CompiledProgram and initial database. |
| inputs / outputs | By-value plan/settings, borrowed initial Database and BuildOptions; takes queue limits and WindowOptions. |
| invariants | Creator thread captured during admission. Initial rows validated/built, not fabricated input events; accepted progress0. Typed wire-format options rejected. Managed window tables must initially be empty; static unmanaged rows permitted. |
| ownership | Runtime/Impl/facade/source metadata/queue/window use actual original account; owned stream adopted, initial Database copied into native owner; returned unique owner. |
| failure | Plan/input/options/build/native account/allocation failure unwinds unpublished graph and owned stream; no existing session mutated. |
| cost | Compile/freeze actual plan and optional full database build; copy input metadata, admit queue/window controls/options/digest. Work/bytes real construction, no promise O(1)/allocation-free. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/batches_windows.md](../../../../../batches_windows.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
~QuerySession();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy session with exclusive lifetime. |
| inputs / outputs | Sets busy then private drop; Impl destructor also idempotently drops. |
| invariants | Never call throwing public thread Guard in destructor. Reentrant callbacks must not destroy session whose operation uses them. |
| ownership | Aborts private work, releases source/output/runtime/durable owners then actual facade/Impl account; returned owners may outlive independently. |
| failure | Nonthrowing private cleanup; no rescue allocation. |
| cost | Visits pending/output/window/candidate/runtime/input/file/lock ownership; potentially large deallocation/close graph, no next-input read. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
QuerySession(const QuerySession&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject QuerySession copy construction. |
| inputs / outputs | Deleted operation. |
| invariants | Stable creator-thread identity and private resources cannot be duplicated/transferred by facade value. |
| ownership | Unique owner may be moved as an owner, facade itself stays fixed. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
QuerySession& operator=(const QuerySession&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject QuerySession copy assignment. |
| inputs / outputs | Deleted operation. |
| invariants | Stable creator-thread identity and private resources cannot be duplicated/transferred by facade value. |
| ownership | Unique owner may be moved as an owner, facade itself stays fixed. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0032

[Lines 215–250](../../../../../../include/crown/runtime/session.hpp#L215); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession(QuerySession&&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject QuerySession move construction. |
| inputs / outputs | Deleted operation. |
| invariants | Stable creator-thread identity and private resources cannot be duplicated/transferred by facade value. |
| ownership | Unique owner may be moved as an owner, facade itself stays fixed. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
QuerySession& operator=(QuerySession&&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject QuerySession move assignment. |
| inputs / outputs | Deleted operation. |
| invariants | Stable creator-thread identity and private resources cannot be duplicated/transferred by facade value. |
| ownership | Unique owner may be moved as an owner, facade itself stays fixed. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] SessionStatus status() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current session status. |
| inputs / outputs | Returns fixed SessionStatus with current phase/sequence/queue/window/output counters. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Readable after stop/drop; derives phase without advancing source/engine/output. |
| ownership | Returned fixed diagnostics can retain the optional declaration metadata owner; no rows or rule vector are cloned. |
| failure | Guard can report session_wrong_thread/session_busy; No phase availability check after Guard; fixed getters can reveal tombstone diagnostics. |
| cost | One Session guard, fixed diagnostics and optional immutable handle copy; final last-owner metadata teardown can be O(R). |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
[[nodiscard]] SessionReportMetadata report_metadata() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual session report metadata. |
| inputs / outputs | Returns current runtime metadata or saved metadata with state disengaged after drop. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Does not capture rows/gauges or establish durable acceptance. |
| ownership | Copies actual CompiledProgram owner plus fixed profile/options; no runtime retained. |
| failure | Guard can report session_wrong_thread/session_busy; Guard can throw; metadata copy does not allocate payload. |
| cost | O(1) shared plan retain/settings copy, old owner release as applicable. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::optional<CommittedStateGauges> report_gauges() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture ordinary exported committed state gauges. |
| inputs / outputs | Returns optional&lt;CommittedStateGauges&gt;, absent during private work or runtime release. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Committed unread output allowed; no implicit drain/update. Unavailable facts stay flagged rather than zero. |
| ownership | Owns ordinary caller gauge vectors; no runtime pointer. |
| failure | Guard can report session_wrong_thread/session_busy; Allocation/lower-level readable failure propagates; live runtime/unread output unchanged. |
| cost | Explicit table/node count enumeration and vector allocation O(base tables+nodes); no full row export. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/support.hpp](../../../../../../include/crown/runtime/support.hpp) |

```text
[[nodiscard]] std::optional<CapturedStateGauges> capture_state_gauges() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture native funded committed state gauges. |
| inputs / outputs | Returns optional&lt;CapturedStateGauges&gt;, absent during private work or runtime release. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Committed unread output allowed; no implicit drain/update. Unavailable facts stay flagged rather than zero. |
| ownership | Owns original-account gauge vectors; no runtime pointer. |
| failure | Guard can report session_wrong_thread/session_busy; Allocation/lower-level readable failure propagates; live runtime/unread output unchanged. |
| cost | Explicit table/node count enumeration and vector allocation O(base tables+nodes); no full row export. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/support.hpp](../../../../../../include/crown/runtime/support.hpp) |

```text
[[nodiscard]] std::optional<statistics::OwnerCapture> capture_statistics(const statistics::OwnerRequest&,statistics::Limits limits={}) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture selected actual owner populations. |
| inputs / outputs | OwnerRequest/Limits return optional OwnerCapture; dropped none, private state metadata-only pending, otherwise actual committed scan. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Request width/count validation remains even on pending path; no tentative table scan/drain. |
| ownership | Native report deep owns requested fields/distributions/keys on original account; request borrowed only synchronously. |
| failure | Guard can report session_wrong_thread/session_busy; Validation/logical exhaustion status and OOM/contract failures preserve their callee semantics. |
| cost | Explicit population scan/group/sort/allocation; pending metadata fixed except request width/count checks. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp) |

```text
[[nodiscard]] std::optional<statistics::Freshness> statistics_freshness(const statistics::OwnerCapture&,std::uint64_t max_event_lag=0) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare retained owner capture freshness with current native owner. |
| inputs / outputs | Optional Freshness, none after runtime release; max lag default0. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Compares actual owner/committed sequence/layer, not storage revision/equal rows or durable sequence. |
| ownership | Borrow capture synchronously; return fixed enum. |
| failure | Guard can report session_wrong_thread/session_busy; Guard/native owner read can fail; no row capture. |
| cost | O(1) stamp comparison, no allocation/clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::optional<statistics::CombinedCapture> capture_combined_statistics(const statistics::OwnerRequest&,statistics::Limits limits={}) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture bound state and workload under one session barrier. |
| inputs / outputs | Optional CombinedCapture; dropped none, private returns pending state plus copied committed workload marked pending. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Combined factory checks actual owner/epoch/plan/pending; statuses/denominators not merged. |
| ownership | Owns native state report and immutable workload Data; request not retained. |
| failure | Guard can report session_wrong_thread/session_busy; Population/OOM/binding failures propagate before return; no session update. |
| cost | State scan/allocations plus O(D) workload arrays; private with_pending deep-copies report arrays again. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp) |

```text
[[nodiscard]] std::shared_ptr<const SessionRunContext> run_context() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable session run context. |
| inputs / outputs | Returns shared_ptr&lt;const SessionRunContext&gt;, also after runtime release. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Admission labels/options are not current runtime/proof/durable authority. |
| ownership | Shared actual native context/options/table-list graph only, not session. |
| failure | Guard can report session_wrong_thread/session_busy; After Guard, shared pointer copy cannot allocate. |
| cost | O(1) refcount; final returned-owner release may tear down metadata graph. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::optional<resource::MemoryStatistics> accounted_memory_statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual current query-account counters. |
| inputs / outputs | Optional MemoryStatistics; none after runtime release. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Requested bytes include all retained original-account owners; counters are not RSS, phase peak or future requirement. |
| ownership | Fixed value, no new account owner retained. |
| failure | Guard can report session_wrong_thread/session_busy; Guard/native query account read failures propagate. |
| cost | O(1) fixed account counters, no ledger scan/allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ObservationSnapshot observations() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy session-decorated observation snapshot. |
| inputs / outputs | Current runtime or retained snapshot with session_context and committed sequence decoration. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Allowed after drop; fixed copied flags do not assert durable acceptance. |
| ownership | Fixed arrays/shared actual immutable admission handles; no trace-vector deep copy or runtime retain. |
| failure | Guard can report session_wrong_thread/session_busy; After Guard current copy nonallocating/noexcept; last old-context release can free metadata. |
| cost | Fixed metric array/refcounts, no table/trace scan. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void configure_workload_statistics(const workload::Options&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconfigure C01 workload counters at true writer barrier. |
| inputs / outputs | Options configure runtime and then save actual settings. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Runtime must exist/no private session work; native Delta writable check also rejects unread output/readers. C01 independent from O07 mode. |
| ownership | New route/descriptors/counter slabs on original account prepared before publication. |
| failure | Guard can report session_wrong_thread/session_busy; Invalid settings/resource/OOM leaves previous configuration intact; Guard/lifecycle errors propagate. |
| cost | O(plan strata/routes) scans/new arrays, old/new overlap at admission; not a hot hook. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp) |

```text
void reset_workload_statistics();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset C01 interval at true writer barrier. |
| inputs / outputs | Clears runtime workload history/sample ordinals, leaves committed query epoch unchanged. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Runtime/no private plus Delta writable output/reader barrier required. |
| ownership | Reuses owned collector storage; returned old snapshots remain independent. |
| failure | Guard can report session_wrong_thread/session_busy; Lifecycle guards before reset; saturated reset generation is visible capped diagnostic. |
| cost | O(descriptor/cell slabs) fixed numeric clears; no row scan or new grant. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp) |

```text
[[nodiscard]] std::optional<workload::Snapshot> workload_statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture immutable workload counters with pending scope. |
| inputs / outputs | Optional Snapshot; dropped none; private session work causes private with_pending deep copy. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Committed-only counters remain visible, private window metadata work still marks pending. |
| ownership | Owns copied numeric Data/plan on original account; handle copies thereafter share Data. |
| failure | Guard can report session_wrong_thread/session_busy; Allocation failure frees private report only, live collector untouched. |
| cost | O(D) capture arrays, plus O(D) additional with_pending clone for private session work. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp) |

```text
[[nodiscard]] workload::Options workload_statistics_options() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current or retained C01 settings. |
| inputs / outputs | Returns workload::Options by value, including after drop. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Does not capture an interval or configure observation clocks. |
| ownership | Inline settings only. |
| failure | Guard can report session_wrong_thread/session_busy; Guard may throw, fixed read otherwise. |
| cost | O(1), no allocation/clock. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] SessionStatisticsContext capture_statistics_context(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one guarded native session statistics context. |
| inputs / outputs | Optional OwnerRequest plus Limits; absent request distinct from engaged empty request. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Single Guard synchronizes metadata/status/trace/combined/cursor/options; dropped context retains metadata with no combined runtime. Pending returns no tentative population facts. |
| ownership | Owns funded trace/counter/state copies plus shared program/session contexts. Owning request is viewed synchronously, never retained. |
| failure | Guard can report session_wrong_thread/session_busy; Account/scan/export/native failures propagate, private result unwinds; no session advancement. |
| cost | O(R+D) trace/workload copies and optional population scans; captured Data/control allocate on original account. Handle copy after capture is O(1). |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] SessionStatisticsContext capture_statistics_context_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one guarded native session statistics context from borrowed selections. |
| inputs / outputs | Optional OwnerRequestView span plus Limits; absent request distinct from engaged empty request. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Single Guard synchronizes metadata/status/trace/combined/cursor/options; dropped context retains metadata with no combined runtime. Pending returns no tentative population facts. |
| ownership | Owns funded trace/counter/state copies plus shared program/session contexts. Span/nested fields borrowed only for call. |
| failure | Guard can report session_wrong_thread/session_busy; Account/scan/export/native failures propagate, private result unwinds; no session advancement. |
| cost | O(R+D) trace/workload copies and optional population scans; captured Data/control allocate on original account. Handle copy after capture is O(1). |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::optional<CursorObservation> last_cursor_observation() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read last cursor observation. |
| inputs / outputs | Returns fixed optional CursorObservation from runtime or retained drop metadata. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; No live cursor lease or new enumeration. |
| ownership | Inline diagnostic value only. |
| failure | Guard can report session_wrong_thread/session_busy; Guard can fail; fixed read otherwise. |
| cost | O(1) fixed metric copy. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ObservationTrace observation_trace() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture ordinary caller observation trace. |
| inputs / outputs | Returns ObservationTrace with session decoration; dropped returns empty records plus retained summary. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Explicit allocating diagnostic, never hot hook; shared context labels are not durable acceptance. |
| ownership | Records own ordinary vector outside query account; summary shares immutable contexts; runtime not retained. |
| failure | Guard can report session_wrong_thread/session_busy; Record copy may allocate/throw; live session/trace unchanged. |
| cost | O(used trace records) allocation/copy plus fixed metadata; dropped empty has no record allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] CapturedObservationTrace capture_observation_trace() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture funded native observation trace. |
| inputs / outputs | Returns CapturedObservationTrace with session decoration; dropped returns empty records plus retained summary. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Explicit allocating diagnostic, never hot hook; shared context labels are not durable acceptance. |
| ownership | Records own original-account capture storage; summary shares immutable contexts; runtime not retained. |
| failure | Guard can report session_wrong_thread/session_busy; Record copy may allocate/throw; live session/trace unchanged. |
| cost | O(used trace records) allocation/copy plus fixed metadata; dropped empty has no record allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] io::InputProgress progress() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export accepted source progress. |
| inputs / outputs | Returns ordinary InputProgress (sequence and source-position map/text); dropped rejects. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Accepted progress advances only at completed source/command acknowledgment, not private attempt. |
| ownership | Owns ordinary map/string copy outside native account; source not retained. |
| failure | Guard can report session_wrong_thread/session_busy; Export allocation can throw, native accepted progress unchanged. |
| cost | O(source position count/name bytes) copy/allocation; no next input read. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/io/ingest.hpp](../../../../../../include/crown/io/ingest.hpp) |

```text
void begin_reoptimization(const planner::MinimumHeightCandidate&,reoptimization::Options={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare checked reoptimization candidate on original account. |
| inputs / outputs | MinimumHeightCandidate and Options; direct wrapper carries selection_ns0. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Require started/paused-ok live session, no active candidate, private/output/recovery/delivery-free committed writer-ready barrier. verified does not imply publication. |
| ownership | Cold candidate/dual-runtime copy and staging ownership on same account; old session can continue until requested barrier. |
| failure | Guard can report session_wrong_thread/session_busy; Validation/native/account/allocation failure unwinds unpublished candidate and preserves old runtime. |
| cost | Native source snapshot/row copies, re-lowering/build/capture and dual-owner peak; not an update hook. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
void request_reoptimization_barrier();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request candidate admission freeze barrier. |
| inputs / outputs | Requires active candidate; sets candidate barrier request. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Does not itself drain old admitted input/output or verify/publish. |
| ownership | Existing candidate retained, no new ownership. |
| failure | Guard can report session_wrong_thread/session_busy; Live/active guards can throw; no local allocation. |
| cost | O(1) state change, no clock/row scan in wrapper. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] reoptimization::Status advance_reoptimization(std::uint64_t quantum=64);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance candidate and requested old-session barrier work. |
| inputs / outputs | Quantum default64; no candidate/default, inactive/verified/quantum0 returns status. Frozen candidate drains only already-admitted private/head work and waits on output/delivery. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Preserves empty journal/complete window/queue publication guards; exact source/result verification only after frozen caught-up. |
| ownership | Uses original-account old/candidate runtime and staged rows; caller gets fixed Status. |
| failure | Guard can report session_wrong_thread/session_busy; Native drain failure aborts pending, cancels candidate (recovery_required when latched) and rethrows; candidate lower-level statuses remain. |
| cost | Up to requested quantum native producer/replay actions plus controlled equality verification scans/allocations; real work/clock/account costs, no promised constant step time. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
[[nodiscard]] UpdatePatternStatus update_pattern_status() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual committed Session monitor diagnostics. |
| inputs / outputs | Return UpdatePatternStatus from the owning runtime/context under the creator-thread guard. |
| invariants | Diagnostics distinguish requested rules, enforced prefix and trusted restored history; no structural or CPU theorem authority. |
| ownership | Fixed result retains immutable declaration metadata; no rows or rule vector copied. |
| failure | Existing availability/reentry errors; dropped owner is unavailable. |
| cost | Fixed data/refcount copy; final last-owner metadata destruction can be O(R). |
| Design | [docs/update_patterns.md](../../../../../update_patterns.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md) |

## B0033

[Lines 251–286](../../../../../../include/crown/runtime/session.hpp#L251); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cancel_reoptimization();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cancel retained candidate preparation. |
| inputs / outputs | If candidate exists call cancel; journal must be healthy. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Does not roll back already committed old-source epochs or durable selection. |
| ownership | Releases target/staging ownership and unfreezes admission through candidate. |
| failure | Guard can report session_wrong_thread/session_busy; Guard/journal recovery-required can throw; cancellation cleanup nonallocating. |
| cost | O(backlog/target owned graph) cleanup; not constant full release. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] reoptimization::Status reoptimization_status() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read candidate lifecycle diagnostics. |
| inputs / outputs | Returns candidate status or default Status. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Status flags do not authorize publication/recovery. |
| ownership | Inline status copy; no new owner. |
| failure | Guard can report session_wrong_thread/session_busy; Guard may throw, fixed read otherwise. |
| cost | O(1) status read. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] reoptimization::Status publish_reoptimization(const io::CompilerPlanArtifact&,reoptimization::PublicationOptions={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish verified candidate through durable generation root. |
| inputs / outputs | CompilerPlanArtifact and PublicationOptions; require verified candidate, managed generation+journal, healthy unfinished source and all input/window/output/delivery barriers. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Exact actual artifact/source/physical/policy/sink lineage checked. Prepare target context/checkpoint/descriptor/files privately, publish root, then install runtime with nonthrowing ownership moves. Root uncertainty latches recovery-required and retains authority. |
| ownership | Same original account holds old/target/checkpoint/descriptor graphs until selection; root/file/lock owners retained; no caller flag can substitute artifact/receipt. |
| failure | Guard can report session_wrong_thread/session_busy; Failures before selection preserve old executable state but may leave unselected files; attempted/uncertain durable selection requires recovery, never ordinary rollback. |
| cost | Cold whole checkpoint/row/hash/descriptor/artifact preparation plus durable checkpoint/log/plan/root writes+syncs; final install moves owners, later old runtime teardown explicit. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
void start();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start or resume admission. |
| inputs / outputs | created/running/paused→running; resume paused pending Delta token if present. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Stopped/dropped terminal reject; draining/prepared/output phases have no invented resume state. |
| ownership | Mutates fixed control/native pending state only. |
| failure | Guard can report session_wrong_thread/session_busy; Invalid control errors before mutation; no source read. |
| cost | O(1) state changes, no allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void pause();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pause producer admission without releasing pending/output. |
| inputs / outputs | Started live session, paused idempotent; pending_delta token pauses then control paused. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Draining/prepared/output have no lower pause state; explicit one-epoch drain remains allowed. |
| ownership | Retains all current resources; no new graph. |
| failure | Guard can report session_wrong_thread/session_busy; Lifecycle/native pause errors propagate before control update. |
| cost | O(1) control changes, no input read/allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] io::Admission enqueue(io::TransportBatch& batch);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one typed transport batch. |
| inputs / outputs | Borrow mutable TransportBatch; typed queue returns accepted/full; ownership transferred only on accepted. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Allowed created/running, rejects paused/terminal/frozen/not-typed/closed. Preserves event order/barriers, no coalescing. |
| ownership | Queue privately copies native funded nodes/rows/source text before consuming offered ordinary batch. Full/OOM leaves batch intact. |
| failure | Guard can report session_wrong_thread/session_busy; Native admission/budget/validation errors preserve queue/offered batch guarantee; semantic head validation deferred. |
| cost | O(offered items/bytes) preflight/copy and actual node/payload allocation; full can stop early. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/io/batch.hpp](../../../../../../include/crown/io/batch.hpp) |

```text
void finish_input();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close typed admission while retaining queued prefix. |
| inputs / outputs | Calls queue.finish after admission-available guard. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Not valid for stream/paused/terminal/frozen session; queue prefix can still be consumed. |
| ownership | No ownership transfer, existing queue stays. |
| failure | Guard can report session_wrong_thread/session_busy; Guard/closed/lifecycle errors propagate. |
| cost | O(1) close flag, no input read/allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] SessionBegin begin_next_result();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin next admitted input with three-state result. |
| inputs / outputs | Peeks at most next source/head, validates and prepares Window step/Delta pending; returns pending/would_block/end. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Require running, no private work or unread ordinary/recovered output, writer-ready/native-source progress match. Durable delivery or frozen unadmitted head may block without reading. |
| ownership | Retains immutable decoded/queued head through retry; native pending/window prepared own private resources; no internal token exposed. |
| failure | Guard can report session_wrong_thread/session_busy; Semantic source/window errors sticky; native/OOM failure aborts private attempt but preserves accepted progress/head. Control/phase rejection does not abort legitimate work. |
| cost | Source decode/validation/ack preparation and actual native begin may scan/allocate; first watermark whole-expiration preflight; no eager drain of entire input. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool begin_next();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin next admitted input with Boolean result. |
| inputs / outputs | Peeks at most next source/head, validates and prepares Window step/Delta pending; returns false only EOF, would_block throws input_would_block. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Require running, no private work or unread ordinary/recovered output, writer-ready/native-source progress match. Durable delivery or frozen unadmitted head may block without reading. |
| ownership | Retains immutable decoded/queued head through retry; native pending/window prepared own private resources; no internal token exposed. |
| failure | Guard can report session_wrong_thread/session_busy; Semantic source/window errors sticky; native/OOM failure aborts private attempt but preserves accepted progress/head. Control/phase rejection does not abort legitimate work. |
| cost | Source decode/validation/ack preparation and actual native begin may scan/allocate; first watermark whole-expiration preflight; no eager drain of entire input. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] DeltaStep step();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform one pending producer or metadata preparation step. |
| inputs / outputs | Running session with private input; metadata-only window sets ready and returns prepared, otherwise Delta pending.step. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; No public query output before commit; does not read another source event. |
| ownership | Mutates existing private epoch/prepared ownership. |
| failure | Guard can report session_wrong_thread/session_busy; Engine step failure aborts private epoch/window and rethrows; source head/old committed state retained for retry. |
| cost | Actual native one-step work/output allocation plus bounded fixed metadata branch; no constant public delay claim. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void commit();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit prepared physical or metadata input. |
| inputs / outputs | Requires private prepared Delta epoch or metadata_ready; writes durable decision first if journal enabled, then native commit and source/window acknowledgment. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; All post-engine publication actions are nonthrowing prepared moves/scalars/cleanup. Accepted command advances only complete window step; no automatic durable output acceptance. |
| ownership | Publishes retained output/committed state, releases private journal/prepared ownership as dictated by epoch. |
| failure | Guard can report session_wrong_thread/session_busy; Predecision errors abort private work. A durable decision followed by failure latches recovery_required; never claim durable transaction rolled back by memory cleanup. |
| cost | Optional encode/WAL append/sync before native publication; native commit work plus prepared metadata tree operations and real teardown. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/session-journal.md](../../../../../session-journal.md) |

```text
void start_drain();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable retention and enter current private-input drain. |
| inputs / outputs | Paused allowed, private input required; attached local sink rejects. Metadata window sets metadata_draining, native epoch delegates start_drain. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Retains only current source/head; no next read. |
| ownership | Native private/output ownership retained/released as drain policy specifies. |
| failure | Guard can report session_wrong_thread/session_busy; Engine drain-start failure aborts private attempt and rethrows. |
| cost | Native transition/cleanup costs, fixed metadata branch; no arbitrary source scan. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void drain();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish/discard only current private or committed output. |
| inputs / outputs | Paused allowed; attached local sink rejects. Pending physical drains/commits; window metadata finishes; otherwise discards ordinary/recovered output. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Never reads another input event. Durable journal decision preserved; drains can leave admission paused. |
| ownership | Releases current output/journal/row owners, acknowledges only completed source command. |
| failure | Guard can report session_wrong_thread/session_busy; Native/durable failure aborts private work and rethrows, recovery latch when already decided; invalid lifecycle before mutation. |
| cost | May enumerate all remaining current-epoch producer/output work and cleanup; not O(1) or whole-stream drain. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::optional<SignedResult> next_output();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer one owning committed signed result. |
| inputs / outputs | Paused allowed; no private input/recovered-output backlog/attached local sink. Returns optional SignedResult, absent when no output. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Output transfer is not durable acknowledgment; final record releases epoch journals/pins. No next input read. |
| ownership | Moves actual tuple payload/layout ownership to caller; earlier returned rows survive session drop. |
| failure | Guard can report session_wrong_thread/session_busy; Lifecycle/source-scope guards before transfer; existing epoch next semantics retained. |
| cost | O(1) prepared spool-node move per record plus final epoch/native journal teardown; no Row export. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] SessionSnapshot snapshot(std::optional<SnapshotLimits> limits=std::nullopt) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate actual committed query results into retained snapshot. |
| inputs / outputs | Optional limits override; allowed created/paused/stopped and unread committed output, rejects dropped/private/recovery-required. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Includes epoch-zero Boolean/nullary answers. Snapshot byte sublimit accounts actual collection/control/tuple requests; progress/shared metadata/cursor scratch outside it still use their real ownership/account. |
| ownership | Progress ordinary map exported; actual tuple/SessionRows control/capacity funded original account, layout shared. No output consumption. |
| failure | Guard can report session_wrong_thread/session_busy; Cursor/work/row/byte/OOM failures close local result/cursor and preserve committed session/unread output. |
| cost | Full result enumeration, actual tuple payload allocations, geometric vector moves with old/new overlap, progress map export; no constant enumeration delay claim. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] std::optional<WindowCanonicalState> window_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export committed-step window diagnostics. |
| inputs / outputs | Optional WindowCanonicalState; nonwindow none, dropped/private reject. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; A completed physical substep can still have active watermark prefix; canonical flags are not quiescent durable checkpoint. |
| ownership | Ordinary exported full-row/vector graph independent from runtime. |
| failure | Guard can report session_wrong_thread/session_busy; Ordinary allocation/export errors unwind DTO, live controller unchanged. |
| cost | O(all window labels/counts/row bytes/directories/active IDs) scan/copy/allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void enable_journal(std::string_view checkpoint_path,std::string_view journal_path,const SessionJournalOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable WAL against an exactly matching existing durable checkpoint. |
| inputs / outputs | Checkpoint/journal paths and SessionJournalOptions; no active journal, terminal/failure/EOF; quiescent checkpoint barrier. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Encode current native session and compare exact stored bytes; never replace existing checkpoint. Create bound WAL only after match. |
| ownership | Borrows paths synchronously; session retains actual journal File/account; native captured image temporary. |
| failure | Guard can report session_wrong_thread/session_busy; Checkpoint mismatch/I/O/hash/native/limit/allocation failures propagate; no partial in-memory journal published. |
| cost | Full checkpoint capture/encode/read/byte compare/hash plus O_EXCL log header write+fsync; native/file budgets explicit. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/session-journal.md](../../../../../session-journal.md) |

```text
[[nodiscard]] SessionJournalState journal_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read last confirmed journal diagnostics. |
| inputs / outputs | Returns fixed SessionJournalState. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Confirmation labels are not a reopened durable authority; recovery_required blocks dependent methods. |
| ownership | Inline record only. |
| failure | Guard can report session_wrong_thread/session_busy; Guard may throw; no I/O. |
| cost | O(1) fixed read. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static Owner restore_journal(CompiledProgram,std::string_view checkpoint_path,std::string_view journal_path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore checkpoint and WAL. |
| inputs / outputs | CompiledProgram, checkpoint/log paths, finite recovery options, optional owned continuation. |
| invariants | Validate source/checkpoint/WAL binding/order/commit decisions and exact reader/window progress before admitting replay; continuation required only live owned-stream input. Recovered unconsumed outputs use bounded identity-bearing native backlog. |
| ownership | New receiving original account funds final holder before permitted tail repair; session retains actual WAL/source/file/lock ownership, input paths borrowed. |
| failure | Corruption/limits/IO/allocation/native failure destroys new session; durable validated incomplete tails may already have been repaired, no global rollback promise. |
| cost | Full checkpoint read/validate/materialize/runtime rebuild plus WAL scan/hash/record replay and native rows; optional sink scan/hash/equality. Recovered outputs bounded rows/bytes. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/local-sink.md](../../../../../local-sink.md) |

```text
[[nodiscard]] static Owner restore_journal_with_local_sink(CompiledProgram,std::string_view checkpoint_path,std::string_view journal_path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore checkpoint and WAL with actual local sink. |
| inputs / outputs | CompiledProgram, checkpoint/log paths, finite recovery options, optional owned continuation, sink path/options. |
| invariants | Validate source/checkpoint/WAL binding/order/commit decisions and exact reader/window progress before admitting replay; continuation required only live owned-stream input. Open/authenticate sink before replay and compare already accepted complete epochs without writing/backlog. |
| ownership | New receiving original account funds final holder before permitted tail repair; session retains actual WAL/source/file/lock ownership, input paths borrowed. |
| failure | Corruption/limits/IO/allocation/native failure destroys new session; durable validated incomplete tails may already have been repaired, no global rollback promise. |
| cost | Full checkpoint read/validate/materialize/runtime rebuild plus WAL scan/hash/record replay and native rows; optional sink scan/hash/equality. Recovered outputs bounded rows/bytes. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/local-sink.md](../../../../../local-sink.md) |

```text
[[nodiscard]] SessionJournalRecoveryStatus recovery_status() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read recovery replay/output diagnostics. |
| inputs / outputs | Returns saved SessionJournalRecoveryStatus, current remaining output rows/bytes when retained. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Status flags are not proof of durable output acceptance. |
| ownership | Fixed record; no output consumed. |
| failure | Guard can report session_wrong_thread/session_busy; Guard may throw. |
| cost | O(1) counters, no WAL scan/I/O. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

## B0034

[Lines 287–322](../../../../../../include/crown/runtime/session.hpp#L287); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::optional<RecoveredResult> next_recovered_output();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer one identity-bearing recovered result. |
| inputs / outputs | Paused allowed; no private work or attached local sink; optional RecoveredResult. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Any transfer makes full replay output coverage unavailable for later whole-epoch sink attachment. |
| ownership | Moves native owning tuple; drops exhausted backlog/control; caller value survives drop. |
| failure | Guard can report session_wrong_thread/session_busy; Guards before transfer; no file read. |
| cost | One row owner move/counter update, possible final backlog teardown. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void discard_recovered_output();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discard recovered output backlog. |
| inputs / outputs | Paused allowed; attached sink rejects. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Clears complete replay coverage marker; does not alter already committed native/runtime/durable decisions. |
| ownership | Releases bounded native result/backlog graph. |
| failure | Guard can report session_wrong_thread/session_busy; Guards can throw before release; cleanup nonallocating. |
| cost | O(retained row owners) teardown, no replay or source read. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void enable_generation(std::string_view root_path,const SessionGenerationOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable managed checkpoint/WAL root ownership. |
| inputs / outputs | Root path/options with positive retained generations/generation, healthy unfinished nonjournaled session and full checkpoint barrier. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Publish candidate checkpoint/log then durable root; selected root determines authority. Historical pairs retained; input/output consumption cannot retire them. |
| ownership | Actual root lock and managed file owner retained on session, same account new images/control. |
| failure | Guard can report session_wrong_thread/session_busy; File/root uncertainty latches recovery_required and retains authority owner; unselected files may remain. No catch removal/ordinary rollback. |
| cost | Full checkpoint encode/hash/write+sync, log creation/sync, root replace/directory sync; finite IO/work/retention. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/generations.md](../../../../../generations.md) |

```text
void promote_journal(std::string_view root_path,const SessionGenerationOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Promote an existing journal under a separately locked root. |
| inputs / outputs | Healthy journal, no generation, complete input/no cached head, positive retention and quiescent delivered checkpoint. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Attached sink requires authenticated prefix. New generation is prior+1; publish exact checkpoint/new log/root before replacing journal owner. |
| ownership | Prepare managed lock/file holder first; retain old journal until selection; new owner becomes authority. |
| failure | Guard can report session_wrong_thread/session_busy; SelectionGuard latches recovery_required and retains attempted root owner on uncertainty; failures before selection leave old native state, unselected files possible. |
| cost | Whole checkpoint/hash/file/sync plus next-generation root publication; not a constant label change. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/generations.md](../../../../../generations.md) |

```text
void rotate_generation();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rotate checkpoint/log under selected durable root. |
| inputs / outputs | Managed healthy journal, no pending WAL, all checkpoint/delivery barriers and retained-generation allowance. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Authenticated attached sink prefix required; rotation retains history and optional immutable plan descriptor lineage. |
| ownership | Same root lock, new checkpoint/log/optional plan files prepared before root; old live journal replaced only after successful selection. |
| failure | Guard can report session_wrong_thread/session_busy; Root attempt uncertainty requires recovery; existing selected authority held by SelectionGuard, no history deletion here. |
| cost | Whole checkpoint/descriptor encode+hash/write/sync and root selection; retains old/new files and native scratch until completion. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/generations.md](../../../../../generations.md) |

```text
void retire_generation_history();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retire only pre-selected-checkpoint historical generations. |
| inputs / outputs | Healthy managed quiescent session, no pending/output/delivery/WAL work, attached actual sink verified through committed sequence/prefix. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Require native receipt/header/lineage/prefix equality and exact selected checkpoint binding. Only generation files before selected checkpoint may be removed, never output-consumption inference. |
| ownership | Keep actual root/sink/file owners and receipt; read selected checkpoint on query account before retirement intent/deletion. |
| failure | Guard can report session_wrong_thread/session_busy; Failure in GenerationOwner retirement latches recovery_required; crash-safe intent/selected authority retained for recovery. |
| cost | Read/hash/validate complete checkpoint, actual sink/lineage checks, directory/file history validation and unlink/sync per retained generation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/generations.md](../../../../../generations.md) |

```text
[[nodiscard]] SessionGenerationState generation_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read managed generation diagnostics. |
| inputs / outputs | Returns default if no generation, otherwise selected root/operations/validation/retirement metadata. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Read flags are not an unlocked replacement for actual held root owner/receipt. |
| ownership | Fixed value only. |
| failure | Guard can report session_wrong_thread/session_busy; Guard may throw; no file scan. |
| cost | O(1) stored metadata. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static Owner restore_generation(CompiledProgram,std::string_view root_path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore legacy selected generation. |
| inputs / outputs | Expected CompiledProgram/root path, recovery options/retention and optional owned continuation. |
| invariants | Acquire/hold actual root lock; bound retained interval. Descriptor-aware v3 selection rejects here and requires locked recovery API. Retirement intent requires actual sink. |
| ownership | Fund final ManagedGeneration in receiving account before replay/tail repair; install owner by nonthrowing move after restore. |
| failure | Validation/IO/native/limit/allocation failures propagate; do not reopen root into an unlocked numeric DTO or claim tail repair rollback. |
| cost | Root/read/history validation, selected checkpoint/log scan/restore/replay, optional sink verification/retirement completion; actual file hashes/syncs. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/generations.md](../../../../../generations.md) |

```text
[[nodiscard]] static Owner restore_generation_with_local_sink(CompiledProgram,std::string_view root_path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore legacy selected generation with local sink. |
| inputs / outputs | Expected CompiledProgram/root path, recovery options/retention and optional owned continuation, sink path/options. |
| invariants | Acquire/hold actual root lock; bound retained interval. Descriptor-aware v3 selection rejects here and requires locked recovery API. Retirement intent requires actual sink. |
| ownership | Fund final ManagedGeneration in receiving account before replay/tail repair; install owner by nonthrowing move after restore. |
| failure | Validation/IO/native/limit/allocation failures propagate; do not reopen root into an unlocked numeric DTO or claim tail repair rollback. |
| cost | Root/read/history validation, selected checkpoint/log scan/restore/replay, optional sink verification/retirement completion; actual file hashes/syncs. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/generations.md](../../../../../generations.md) |

```text
[[nodiscard]] static resource::AccountedUnique<LockedGenerationRecovery> lock_generation_recovery(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lock selected generation while compiler artifact is decoded. |
| inputs / outputs | Expected admitted source, root path and finite recovery policy return AccountedUnique&lt;LockedGenerationRecovery&gt;. |
| invariants | Require source/positive retention; acquire actual root lock, validate selected descriptor/source/catalog/sink lineage/retention, no caller plan token bypass. |
| ownership | Holder owns root lock, receiving account, immutable expected program and copied actual descriptor/artifact bytes. |
| failure | IO/binding/limit/OOM failures unwind holder/lock before return; no session or input replay yet. |
| cost | Root/checkpoint header read and optional full plan-descriptor hash/inspect/allocation; no native replay in this phase. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp) |

```text
[[nodiscard]] static Owner restore_selected_generation(resource::AccountedUnique<LockedGenerationRecovery>,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore descriptor-selected generation from live lock. |
| inputs / outputs | Consumes AccountedUnique&lt;LockedGenerationRecovery&gt;, actual CompilerPlanArtifact and continuation. |
| invariants | Validate artifact bytes/native source/physical plan and original descriptor/sink lineage while actual lock held; retirement intent requires sink. |
| ownership | Move root/plan authority into pre-funded final holder before replay; new session uses same receiving account and actual chosen artifact, not public flags. |
| failure | Binding/IO/native/OOM errors destroy consumed holder/new session; permitted validated tail repairs may persist. |
| cost | Selected checkpoint/WAL/sink read/hash/replay/native rebuild and optional history retirement; holder move itself nonallocating. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
[[nodiscard]] static Owner restore_selected_generation_with_local_sink(resource::AccountedUnique<LockedGenerationRecovery>,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore descriptor-selected generation from live lock and sink. |
| inputs / outputs | Consumes AccountedUnique&lt;LockedGenerationRecovery&gt;, actual CompilerPlanArtifact and continuation, sink path/options. |
| invariants | Validate artifact bytes/native source/physical plan and original descriptor/sink lineage while actual lock held; retirement intent requires sink. |
| ownership | Move root/plan authority into pre-funded final holder before replay; new session uses same receiving account and actual chosen artifact, not public flags. |
| failure | Binding/IO/native/OOM errors destroy consumed holder/new session; permitted validated tail repairs may persist. |
| cost | Selected checkpoint/WAL/sink read/hash/replay/native rebuild and optional history retirement; holder move itself nonallocating. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
void create_local_sink(std::string_view,const SessionLocalSinkOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create actual durable local sink. |
| inputs / outputs | Path/options; healthy journaled committed nonterminal session, no private work. Requires journal checkpoint boundary/no output and no bound sink delivery anchor. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Native File binds actual schema/query/plan/generation/prefix; poisoned attachment can only reopen same identity. Store failed=true before file work so all failures remain blocked. |
| ownership | Session retains File/schema/native owner; paths borrowed, no receipt constructed from caller flags. |
| failure | Guard can report session_wrong_thread/session_busy; Open/create/schema/prefix/torn-tail/IO/allocation errors propagate with failed attachment latched. File uncertainty remains its own required boundary. |
| cost | Full sink header/schema/prefix scan/hash/validation, optional tail truncate+fsync; control/schema/funded IO allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/local-sink.md](../../../../../local-sink.md) |

```text
void open_local_sink(std::string_view,const SessionLocalSinkOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open/reopen actual durable local sink. |
| inputs / outputs | Path/options; healthy journaled committed nonterminal session, no private work. Requires same sink identity; late attachment needs complete unconsumed replay coverage. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Native File binds actual schema/query/plan/generation/prefix; poisoned attachment can only reopen same identity. Store failed=true before file work so all failures remain blocked. |
| ownership | Session retains File/schema/native owner; paths borrowed, no receipt constructed from caller flags. |
| failure | Guard can report session_wrong_thread/session_busy; Open/create/schema/prefix/torn-tail/IO/allocation errors propagate with failed attachment latched. File uncertainty remains its own required boundary. |
| cost | Full sink header/schema/prefix scan/hash/validation, optional tail truncate+fsync; control/schema/funded IO allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/local-sink.md](../../../../../local-sink.md) |

```text
[[nodiscard]] SessionLocalSinkState local_sink_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read attached sink lifecycle diagnostics. |
| inputs / outputs | Default if absent, otherwise file/failed/replaying/verified/working/prefix flags. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Persisted file coverage and native verified_sequence remain distinct; flags cannot prove a new sink valid. |
| ownership | Fixed stored state, no row copy. |
| failure | Guard can report session_wrong_thread/session_busy; Guard may throw; no file reread. |
| cost | O(1) stored counters/state. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] LocalDelivery deliver_local_epoch();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Durably accept exactly the next complete committed output epoch. |
| inputs / outputs | Paused allowed, healthy attached actual sink, no private input; idle if already verified, otherwise next consecutive sequence. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Must retain full unconsumed live/replayed epoch. File append verifies duplicate or syncs complete frame before acknowledgment/release; ordinary transfer/discard cannot bypass attached sink contract. |
| ownership | Temporary funded RowView list borrows retained epoch tuples only during call; after acceptance release rows and advance native prefix/verified sequence. |
| failure | Guard can report session_wrong_thread/session_busy; Sink Failure latches failed; output releases only after acceptance. Actual IO outcome/File poison remains authoritative; pre-acceptance Image/resource/allocation failures leave output unacknowledged. |
| cost | Scan whole epoch rows+scalar encoding/hash, funded frame/descriptor buffers, file append/duplicate comparison and fsync. Prefix lookup/verified scalar update is fixed stored metadata, not new IO. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/local-sink.md](../../../../../local-sink.md) |

```text
[[nodiscard]] recovery::sink::Epoch read_local_epoch(std::uint64_t);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one durable sink epoch into native ownership. |
| inputs / outputs | Sequence, healthy attached sink, paused allowed. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Actual File uses validated ordinal index then reads/validates/decodes requested complete frame; caller labels cannot substitute payload. |
| ownership | Returned Epoch owns decoded native records/rows on sink original account. |
| failure | Guard can report session_wrong_thread/session_busy; File Failure latches sink.failed; corruption/IO/limit/allocation propagate with File semantics. |
| cost | O(1) admitted index lookup, then O(requested frame bytes/rows) read/hash/inspect/decode and native row/array allocation; two stat checks and cumulative codec work remain. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/local-sink.md](../../../../../local-sink.md) |

```text
[[nodiscard]] recovery::sink::Receipt local_sink_receipt() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain actual verified local sink receipt. |
| inputs / outputs | Requires healthy journal/sink, no delivery/private work, verified through committed boundary. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Receipt comes only from actual File; diagnostic SessionLocalSinkState/public DTO cannot authorize history retirement. |
| ownership | Returns native receipt identity/prefix bound to actual file state; no output row retained. |
| failure | Guard can report session_wrong_thread/session_busy; Guards/File poison/uncertainty failures propagate. |
| cost | Fixed verified metadata read/receipt construction; no output replay, no durability manufactured. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/local-sink.md](../../../../../local-sink.md) |

```text
[[nodiscard]] SessionCheckpoint checkpoint_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture complete native session checkpoint with default limits. |
| inputs / outputs | Returns move-only SessionCheckpoint under default finite image/source/window/matching bounds. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Runtime exists/ready, no private/output/recovered/delivery work, empty input queue, matching source/window/physical sequences; active watermark even stopped is not checkpointable. |
| ownership | Owns funded native source options/progress/window rows and runtime image, same query account; no direct durable serialized-file authority. |
| failure | Guard can report session_wrong_thread/session_busy; Busy/identity/limit/account/OOM errors unwind partial capture, live session unchanged. |
| cost | Full runtime image/source/window row scans/clones and byte/hash serialization; prior/new graphs coexist. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] SessionCheckpoint checkpoint_state(const SessionCheckpointLimits&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture complete native session checkpoint. |
| inputs / outputs | Returns move-only SessionCheckpoint under supplied finite image/source/window/matching bounds. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Runtime exists/ready, no private/output/recovered/delivery work, empty input queue, matching source/window/physical sequences; active watermark even stopped is not checkpointable. |
| ownership | Owns funded native source options/progress/window rows and runtime image, same query account; no direct durable serialized-file authority. |
| failure | Guard can report session_wrong_thread/session_busy; Busy/identity/limit/account/OOM errors unwind partial capture, live session unchanged. |
| cost | Full runtime image/source/window row scans/clones and byte/hash serialization; prior/new graphs coexist. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

```text
[[nodiscard]] static Owner restore_state(CompiledProgram,const SessionCheckpoint&,
      std::unique_ptr<std::istream> continuation={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore native in-memory session checkpoint with defaults. |
| inputs / outputs | CompiledProgram, SessionCheckpoint, default RestoreOptions and optional owned continuation. |
| invariants | Validate version/control/input kind/source progress/options/window/sequence plus actual native runtime/source matching; continuation iff active stream. Mutable checkpoint fields alone grant no authority. |
| ownership | New original receiving account/runtime; clone/import native metadata/source/window under cap; returned unique session owns source. |
| failure | Corruption/binding/resource/OOM failure frees new graph/stream; checkpoint borrowed and unchanged. |
| cost | Native image inspect/rebuild/source-window matching plus funded row/options/progress/control allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
[[nodiscard]] static Owner restore_state(CompiledProgram,const SessionCheckpoint&,
      const SessionRestoreOptions&,std::unique_ptr<std::istream> continuation={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore native in-memory session checkpoint. |
| inputs / outputs | CompiledProgram, SessionCheckpoint, explicit RestoreOptions and optional owned continuation. |
| invariants | Validate version/control/input kind/source progress/options/window/sequence plus actual native runtime/source matching; continuation iff active stream. Mutable checkpoint fields alone grant no authority. |
| ownership | New original receiving account/runtime; clone/import native metadata/source/window under cap; returned unique session owns source. |
| failure | Corruption/binding/resource/OOM failure frees new graph/stream; checkpoint borrowed and unchanged. |
| cost | Native image inspect/rebuild/source-window matching plus funded row/options/progress/control allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/checkpoints.md](../../../../../checkpoints.md) |

## B0035

[Lines 323–358](../../../../../../include/crown/runtime/session.hpp#L323); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] recovery::SessionImage checkpoint_image() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete session binary envelope with defaults. |
| inputs / outputs | Native checkpoint default limits; returns SessionImage. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Same strict checkpoint barrier; envelope structural checksum is separate from native plan/source admission and durable publication. |
| ownership | Owned binary bytes on original account, native checkpoint scratch released afterward. |
| failure | Guard can report session_wrong_thread/session_busy; State/native/image/account/allocation failures unwind private outputs; no file written. |
| cost | Full checkpoint clones + encode/validate/hash bytes; image/native scratch can coexist. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp) |

```text
[[nodiscard]] recovery::SessionImage checkpoint_image(const SessionCheckpointLimits&,const recovery::SessionImageLimits&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete session binary envelope. |
| inputs / outputs | Native checkpoint explicit native/image limits; returns SessionImage. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Same strict checkpoint barrier; envelope structural checksum is separate from native plan/source admission and durable publication. |
| ownership | Owned binary bytes on original account, native checkpoint scratch released afterward. |
| failure | Guard can report session_wrong_thread/session_busy; State/native/image/account/allocation failures unwind private outputs; no file written. |
| cost | Full checkpoint clones + encode/validate/hash bytes; image/native scratch can coexist. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp) |

```text
[[nodiscard]] static Owner restore_image(CompiledProgram,std::string_view,std::unique_ptr<std::istream> continuation={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore borrowed binary session envelope using default restore/image limits. |
| inputs / outputs | CompiledProgram, stable immutable string_view bytes, options/limits and optional owned continuation. |
| invariants | First validate envelope structure/checksum; then materialize and native semantic/catalog/base/window matching in restore_funded. Bytes live unchanged through call only. |
| ownership | New receiving account funds decoded metadata/window/runtime; runtime blob view remains borrowed only through final restore. No borrowed input bytes retained. |
| failure | Malformed/binding/limit/OOM/native failure frees new session; no file IO mutation. |
| cost | O(envelope bytes) checksum/structural passes plus full native rebuild/matching and receiver allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp) |

```text
[[nodiscard]] static Owner restore_image(CompiledProgram,std::string_view,const SessionRestoreOptions&,
      std::unique_ptr<std::istream> continuation={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore borrowed binary session envelope using explicit restore, default image limits. |
| inputs / outputs | CompiledProgram, stable immutable string_view bytes, options/limits and optional owned continuation. |
| invariants | First validate envelope structure/checksum; then materialize and native semantic/catalog/base/window matching in restore_funded. Bytes live unchanged through call only. |
| ownership | New receiving account funds decoded metadata/window/runtime; runtime blob view remains borrowed only through final restore. No borrowed input bytes retained. |
| failure | Malformed/binding/limit/OOM/native failure frees new session; no file IO mutation. |
| cost | O(envelope bytes) checksum/structural passes plus full native rebuild/matching and receiver allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp) |

```text
[[nodiscard]] static Owner restore_image(CompiledProgram,std::string_view,const SessionRestoreOptions&,
      const recovery::SessionImageLimits&,std::unique_ptr<std::istream> continuation={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore borrowed binary session envelope using explicit restore and image limits. |
| inputs / outputs | CompiledProgram, stable immutable string_view bytes, options/limits and optional owned continuation. |
| invariants | First validate envelope structure/checksum; then materialize and native semantic/catalog/base/window matching in restore_funded. Bytes live unchanged through call only. |
| ownership | New receiving account funds decoded metadata/window/runtime; runtime blob view remains borrowed only through final restore. No borrowed input bytes retained. |
| failure | Malformed/binding/limit/OOM/native failure frees new session; no file IO mutation. |
| cost | O(envelope bytes) checksum/structural passes plus full native rebuild/matching and receiver allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [src/recovery/session_image.cpp](../../../../../../src/recovery/session_image.cpp) |

```text
[[nodiscard]] recovery::PublishedCheckpoint checkpoint_file(std::string_view path) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish standalone durable checkpoint file with defaults. |
| inputs / outputs | Destination path, default native/file limits; no attached WAL. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Strict quiescent checkpoint barrier; native in-memory capture alone is not durable. Actual file publisher uses temp/write/sync/replace/directory sync outcome. |
| ownership | Temporary original-account checkpoint/image; retains no new session file owner after publication, result describes actual publication. |
| failure | Guard can report session_wrong_thread/session_busy; File/native/limit/allocation failures preserve stage/outcome semantics; selection may be uncertain after file replacement, no blanket rollback claim. |
| cost | Full capture/encode/hash plus write+fsync/atomic rename/directory fsync and temp cleanup. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
[[nodiscard]] recovery::PublishedCheckpoint checkpoint_file(std::string_view path,const SessionCheckpointLimits&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish standalone durable checkpoint file. |
| inputs / outputs | Destination path, explicit native/file limits; no attached WAL. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Strict quiescent checkpoint barrier; native in-memory capture alone is not durable. Actual file publisher uses temp/write/sync/replace/directory sync outcome. |
| ownership | Temporary original-account checkpoint/image; retains no new session file owner after publication, result describes actual publication. |
| failure | Guard can report session_wrong_thread/session_busy; File/native/limit/allocation failures preserve stage/outcome semantics; selection may be uncertain after file replacement, no blanket rollback claim. |
| cost | Full capture/encode/hash plus write+fsync/atomic rename/directory fsync and temp cleanup. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
[[nodiscard]] static Owner restore_file(CompiledProgram,std::string_view path,std::unique_ptr<std::istream> continuation={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore checkpoint file using defaults. |
| inputs / outputs | CompiledProgram/path/options and optional owned continuation. |
| invariants | Actual SessionFileReader obtains bounded bytes, structural/native checks validate selected plan/source/window; no caller hash/flag grants admission. |
| ownership | Reader owns file only during call; receiver original account holds bytes/decoded/native graph, returned session owns source. |
| failure | File/binding/corruption/limit/OOM/native errors unwind new graph; existing file not repaired/replaced by this API. |
| cost | O(file/envelope bytes) read/hash/validate plus native rebuild/matching/allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
[[nodiscard]] static Owner restore_file(CompiledProgram,std::string_view path,const SessionRestoreOptions&,
      std::unique_ptr<std::istream> continuation={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore checkpoint file using explicit restore/default file limits. |
| inputs / outputs | CompiledProgram/path/options and optional owned continuation. |
| invariants | Actual SessionFileReader obtains bounded bytes, structural/native checks validate selected plan/source/window; no caller hash/flag grants admission. |
| ownership | Reader owns file only during call; receiver original account holds bytes/decoded/native graph, returned session owns source. |
| failure | File/binding/corruption/limit/OOM/native errors unwind new graph; existing file not repaired/replaced by this API. |
| cost | O(file/envelope bytes) read/hash/validate plus native rebuild/matching/allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
[[nodiscard]] static Owner restore_file(CompiledProgram,std::string_view path,const SessionRestoreOptions&,
      const recovery::CheckpointFileLimits&,std::unique_ptr<std::istream> continuation={});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore checkpoint file using explicit restore/file limits. |
| inputs / outputs | CompiledProgram/path/options and optional owned continuation. |
| invariants | Actual SessionFileReader obtains bounded bytes, structural/native checks validate selected plan/source/window; no caller hash/flag grants admission. |
| ownership | Reader owns file only during call; receiver original account holds bytes/decoded/native graph, returned session owns source. |
| failure | File/binding/corruption/limit/OOM/native errors unwind new graph; existing file not repaired/replaced by this API. |
| cost | O(file/envelope bytes) read/hash/validate plus native rebuild/matching/allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
void stop();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop input permanently while retaining committed runtime. |
| inputs / outputs | Idempotent private stop, including after dropped. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Abort unpublished work, discard output, close source/queue, stop window expansion and retain committed diagnostic metadata. No public guard inside cleanup; stop itself remains guarded. |
| ownership | Releases source buffers/pending/output/candidate target, retains committed runtime/window prefix/options/durable owners for diagnostics. |
| failure | Guard can report session_wrong_thread/session_busy; Only public Guard can fail before cleanup; private native cleanup is nonthrowing and allocates no new native payload; owned external stream runs its destructor. |
| cost | Actual owned source/output/private graph teardown; no next input read, no total-history retirement. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void drop();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drop native runtime after terminal stop. |
| inputs / outputs | Idempotent stop then release runtime/window/candidate/journal/generation/sink and clear final native progress. |
| invariants | Creator-thread/nonreentrant public Guard precedes mutable state; Status/retained metadata/context remain; snapshots/progress reject, capture APIs return released/absent as specified. Drop does not revoke independently returned owners. |
| ownership | Releases actual live runtime graphs/files/locks; retained plan/session context/captured outputs can keep original account allocations. |
| failure | Guard can report session_wrong_thread/session_busy; Only public Guard can fail before cleanup; private native drop nonthrowing with no new native allocation. |
| cost | Potentially full native graph/file/lock teardown; no guarantee O(1) or entire account becomes empty. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
friend void selection::begin_reoptimization(QuerySession&,const selection::CurrentSelection&,reoptimization::Options);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict measured selection-to-candidate handoff. |
| inputs / outputs | Friend selection::begin_reoptimization may call private cost-aware preparation. |
| invariants | Public DTO fields cannot bypass CurrentSelection revalidation or session barriers. |
| ownership | No ownership created by friendship. |
| failure | Compile-time access control. |
| cost | No runtime action. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void begin_reoptimization_with_cost(const planner::MinimumHeightCandidate&,reoptimization::Options,std::uint64_t selection_ns);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidate while carrying measured selection cost. |
| inputs / outputs | Same public candidate/options plus selection_ns from validated adapter; actual code enforces active/committed-delivered barrier then constructs State. |
| invariants | No stale-selection or durable-publication shortcut. Direct public candidate wrapper supplies0. |
| ownership | New candidate on original account; existing session held until preparation succeeds. |
| failure | Guard/validation/build/OOM failures preserve old runtime, unpublished candidate unwinds. |
| cost | Cold native copy/re-lowering/build and time/account metrics; selection cost counted separately. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp) |

```text
void local_sink_impl(std::string_view,const SessionLocalSinkOptions&,bool create);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Centralize actual local sink create/open lifecycle. |
| inputs / outputs | Private path/options/create switch, takes public Guard and same journal/committed/output/prefix conditions as wrappers. |
| invariants | Sets failed=true before any File/open/schema/prefix/tail work; success installs actual File then clears failed. No redundant catch is required or proposed. |
| ownership | Retains actual schema/File/account; old attached File reset before reopen, same identity required. |
| failure | All failure paths naturally leave failed latch true; callee File poison/uncertainty/cleanup boundaries remain necessary. |
| cost | Sink scan/hash/repair/sync and funded schema/control buffers as real requested operation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/local-sink.md](../../../../../local-sink.md) |

```text
[[nodiscard]] static Owner restore_journal_selected(CompiledProgram,std::string_view,std::string_view,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore selected WAL with optional root/sink/receiving authority. |
| inputs / outputs | Private complete program/path/recovery/source/root/sink/retirement/context/origin/target arguments unify public restore entry points. |
| invariants | Validate actual selection and whole replay decisions/source/sink lineage before final admission. Fund holder before permitted tail repair; selected root owner stays locked. |
| ownership | Consumes owned continuation/context, borrows file paths/expected metadata for call; retains actual resulting journal/root/sink ownership only. |
| failure | Native/IO/corruption/work/account failures unwind new graph; allowed validated incomplete-tail repair may already persist. |
| cost | Full checkpoint/WAL/sink scan/hash/replay; bounded recovered output rows/bytes and native rebuild. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/generations.md](../../../../../generations.md) |

```text
[[nodiscard]] static Owner restore_locked_generation(resource::AccountedUnique<LockedGenerationRecovery>,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore from a live descriptor-aware root lock. |
| inputs / outputs | Consumes LockedGenerationRecovery and actual artifact, continuation and optional sink path/options. |
| invariants | Native bytes/source/physical/descriptor/sink lineage checked under retained root lock; cannot substitute unlocked inspected fields. |
| ownership | Moves locked authority into funded final holder before replay, uses same receiving account. |
| failure | Failure releases consumed authority/new graph; no ordinary in-memory rollback of durable repair/selection. |
| cost | Descriptor compare/hash, selected file replay/native construction and optional sink verification/retirement. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp) |

```text
[[nodiscard]] static Owner restore_generation_impl(CompiledProgram,std::string_view,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore legacy generation under actual root ownership. |
| inputs / outputs | Private expected program/root/options/continuation and optional sink. |
| invariants | Reject v3 descriptor root here; enforce retention/retirement sink and final-holder-before-tail-repair ordering. |
| ownership | Retains actual locked root in receiving account final holder, not just selected DTO. |
| failure | IO/identity/native/OOM errors propagate, retaining required scope until unwind; validated tail repairs may persist. |
| cost | Root/history validation plus checkpoint/WAL/sink read/hash/replay and receiver graph creation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [docs/generations.md](../../../../../generations.md) |

```text
[[nodiscard]] static Owner restore_funded(CompiledProgram,const SessionCheckpoint&,const SessionRestoreOptions&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a fully validated native session on receiving account. |
| inputs / outputs | Program/checkpoint/RestoreOptions/owned continuation, optional pre-funded StorageWorkContext and stable runtime bytes. |
| invariants | Validate state/source-kind/progress/options/window shapes, then restore actual runtime with catalog/source/base matching. Caller envelope validation alone insufficient. |
| ownership | New account if none supplied; all session/native imports funded on actual receiver; source owned, runtime bytes borrowed only until copied/restored. |
| failure | Any version/state/sequence/binding/work/OOM error unwinds new graph; old checkpoint/program untouched. |
| cost | Full native image rebuild and managed base/window matching; source/options/progress/row/control allocations. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp) |

## B0036

[Lines 359–367](../../../../../../include/crown/runtime/session.hpp#L359); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Impl;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide stable session implementation. |
| inputs / outputs | Impl forward declaration and unique private ownership follow factory helpers. |
| invariants | No mutable native runtime, pending token or lease exposed through public header. |
| ownership | QuerySession retains actual AccountedUnique&lt;Impl&gt;. |
| failure | No runtime action at declaration. |
| cost | No cost until construction/destruction. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
explicit QuerySession(resource::AccountedUnique<Impl> data) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a complete private session implementation. |
| inputs / outputs | Constructor moves AccountedUnique&lt;Impl&gt; into data_. |
| invariants | Factories already funded facade and implementation; creator-thread stored inside Impl. |
| ownership | Unique actual native implementation account ownership. |
| failure | noexcept for a live readable object; borrowing does not validate lifetime or extend it. |
| cost | O(1) ownership move, no allocation. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
using PlanSource=std::variant<PhysicalPlan,CompiledProgram>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accept verified physical or admitted compiled input in factory. |
| inputs / outputs | PlanSource variant&lt;PhysicalPlan,CompiledProgram&gt;. |
| invariants | Variant tag alone is not proof; Delta admission validates/freezes into original execution account. |
| ownership | PhysicalPlan owns ordinary graph and can deep-copy; CompiledProgram shares immutable admitted graph. By-value variant ownership follows actual alternative. |
| failure | Physical graph/argument copies can allocate/throw; factory consumes privately. |
| cost | Physical input graph move/copy costs differ from compiled handle copy; no blanket allocation-free variant claim. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] static Owner create_impl(PlanSource,const Database*,std::unique_ptr<std::istream>,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement all initial session admission variants. |
| inputs / outputs | PlanSource, optional initial Database pointer, owned input, optional queue limits, SessionOptions, optional WindowOptions and BuildOptions. |
| invariants | Typed profile validation first; initialize/build actual Delta; managed tables checked initially empty; then fund Impl/facade on runtime original account. |
| ownership | Owns/moves source/settings/window/native resources; initial Database borrowed and imported, not retained. |
| failure | Allocation/validation/build failure releases unpublished Impl/runtime/source; no existing session or file modified. |
| cost | Actual plan freeze/initial build, catalog digest/options copying, native queue/window/control admission; static plan/input copies may allocate before call. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |

```text
resource::AccountedUnique<Impl> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain unique account-funded session state. |
| inputs / outputs | data_ owns Impl via AccountedUnique; facade also stored in same account via Owner deleter. |
| invariants | Stable creator-thread/nonreentrant state; drop can release runtime while metadata/context still retained. |
| ownership | Final facade cleanup drops source/runtime/files/locks then frees Impl/facade under retained original account. |
| failure | No allocating cleanup or rescue allowance. |
| cost | Real owned-graph teardown, plus constant control/facade frees. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/code_review.md](../../../../../code_review.md) |
