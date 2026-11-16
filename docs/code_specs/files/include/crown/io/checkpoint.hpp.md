# `include/crown/io/checkpoint.hpp` — block usage map

[Source](../../../../../../include/crown/io/checkpoint.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `d4ea75931270fcf0786fb57de41cc65ac251fe8468b38eeecc3e626e22728b98`. 33 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/io/checkpoint.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–11](../../../../../../include/crown/io/checkpoint.hpp#L8) | Type/record definition: struct SourceStateLimits |  · [reviewed contract](#b0002) |
| [B0003 · 12–14](../../../../../../include/crown/io/checkpoint.hpp#L12) | Explanatory comments or spacing. | source comment (unverified): // Native source components for the versioned session envelope. A queue must · [reviewed contract](#b0003) |
| [B0004 · 15–23](../../../../../../include/crown/io/checkpoint.hpp#L15) | Type/record definition: struct QueueCheckpoint | source comment (unverified): // Native source components for the versioned session envelope. A queue must · [reviewed contract](#b0004) |
| [B0005 · 24–32](../../../../../../include/crown/io/checkpoint.hpp#L24) | Type/record definition: struct ReaderCheckpoint |  · [reviewed contract](#b0005) |
| [B0006 · 33–33](../../../../../../include/crown/io/checkpoint.hpp#L33) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0006) |

## B0001

[Lines 1–7](../../../../../../include/crown/io/checkpoint.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io checkpoint public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

## B0002

[Lines 8–11](../../../../../../include/crown/io/checkpoint.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceStateLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound source checkpoint/restore preparation. |
| inputs / outputs | Selected work, retained positions and CSV permutation width limits. |
| invariants | Work is an explicit model, not a bound on all allocator/CPU/I/O cost; CSV permutation checks can be quadratic within it. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
std::uint64_t work=16*1024*1024;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The cumulative selected source-state preparation work cap. |
| inputs / outputs | Stores/exposes the cumulative selected source-state preparation work cap. |
| invariants | Work is an explicit model, not a bound on all allocator/CPU/I/O cost; CSV permutation checks can be quadratic within it. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
std::size_t positions=1024,csv_fields=4096;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The independent retained source-position and CSV field-count caps. |
| inputs / outputs | Stores/exposes the independent retained source-position and CSV field-count caps. |
| invariants | Work is an explicit model, not a bound on all allocator/CPU/I/O cost; CSV permutation checks can be quadratic within it. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

## B0003

[Lines 12–14](../../../../../../include/crown/io/checkpoint.hpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L14:sha256:c9ec86285272803247f2be3f815ea66f897893e174e92f5f53ba19cb021e1d0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Native source components for the versioned session envelope. A queue must be empty and a reader must have no unacknowledged cached record. Snapshots own their positions/fields and retain immutable original-account options. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/io/checkpoint.hpp lines 10-16; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [docs/code_specs/files/include/crown/io/checkpoint.hpp.md](checkpoint.hpp.md), [docs/ingestion.md](../../../../../ingestion.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0004

[Lines 15–23](../../../../../../include/crown/io/checkpoint.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QueueCheckpoint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one empty typed-queue component snapshot. |
| inputs / outputs | Accepted progress, mode/limits/closed state, catalog fingerprint and spent capture work. |
| invariants | Native component is mutable data and requires empty/unfailed source capture; restore revalidates its fields/binding. It is not a full session/root authority. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Capture/restore validates positions and recomputes canonical catalog fingerprint; progress copying allocates native nodes. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
AccountedInputProgress progress;
  QueueMode mode;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The accepted source prefix snapshot, excluding pending input. |
| inputs / outputs | Stores/exposes the accepted source prefix snapshot, excluding pending input. |
| invariants | Native component is mutable data and requires empty/unfailed source capture; restore revalidates its fields/binding. It is not a full session/root authority. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Capture/restore validates positions and recomputes canonical catalog fingerprint; progress copying allocates native nodes. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
QueueMode mode;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The captured physical/window queue mode. |
| inputs / outputs | Stores/exposes the captured physical/window queue mode. |
| invariants | Native component is mutable data and requires empty/unfailed source capture; restore revalidates its fields/binding. It is not a full session/root authority. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Capture/restore validates positions and recomputes canonical catalog fingerprint; progress copying allocates native nodes. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
QueueLimits limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The queue capacity configuration. |
| inputs / outputs | Stores/exposes the queue capacity configuration. |
| invariants | Native component is mutable data and requires empty/unfailed source capture; restore revalidates its fields/binding. It is not a full session/root authority. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Capture/restore validates positions and recomputes canonical catalog fingerprint; progress copying allocates native nodes. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
InputLimits input_limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The typed head/source validation configuration. |
| inputs / outputs | Stores/exposes the typed head/source validation configuration. |
| invariants | Native component is mutable data and requires empty/unfailed source capture; restore revalidates its fields/binding. It is not a full session/root authority. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Capture/restore validates positions and recomputes canonical catalog fingerprint; progress copying allocates native nodes. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
bool closed=false;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Whether future enqueue was finished. |
| inputs / outputs | Stores/exposes whether future enqueue was finished. |
| invariants | Native component is mutable data and requires empty/unfailed source capture; restore revalidates its fields/binding. It is not a full session/root authority. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Capture/restore validates positions and recomputes canonical catalog fingerprint; progress copying allocates native nodes. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
std::array<char,64> catalog_sha256{};
  std::uint64_t work=0;
};
struct ReaderCheckpoint {

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The complete canonical catalog/source-schema binding bytes. |
| inputs / outputs | Stores/exposes the complete canonical catalog/source-schema binding bytes. |
| invariants | Native component is mutable data and requires empty/unfailed source capture; restore revalidates its fields/binding. It is not a full session/root authority. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Capture/restore validates positions and recomputes canonical catalog fingerprint; progress copying allocates native nodes. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
std::uint64_t work=0;
};
struct ReaderCheckpoint {

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The capture preparation work already spent. |
| inputs / outputs | Stores/exposes the capture preparation work already spent. |
| invariants | Native component is mutable data and requires empty/unfailed source capture; restore revalidates its fields/binding. It is not a full session/root authority. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Capture/restore validates positions and recomputes canonical catalog fingerprint; progress copying allocates native nodes. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

## B0005

[Lines 24–32](../../../../../../include/crown/io/checkpoint.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReaderCheckpoint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one reader continuation component snapshot. |
| inputs / outputs | Native options/progress, owned CSV permutation, decoded counters/flags, catalog binding and capture work. |
| invariants | Capture requires no cached event and no broken reader. The caller/session supplies a correctly positioned continuation; copied flags do not validate stream prefix or durable state. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Source/options scans, funded progress/CSV copies, fingerprint validation; restore validates CSV permutation with pair comparisons. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
AccountedInputOptions options;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The immutable retained source-format/options handle. |
| inputs / outputs | Stores/exposes the immutable retained source-format/options handle. |
| invariants | Capture requires no cached event and no broken reader. The caller/session supplies a correctly positioned continuation; copied flags do not validate stream prefix or durable state. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Source/options scans, funded progress/CSV copies, fingerprint validation; restore validates CSV permutation with pair comparisons. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
AccountedInputProgress progress;
  recovery::ImageVector<std::size_t> csv_fields;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The accepted source prefix, excluding an unacknowledged cached event. |
| inputs / outputs | Stores/exposes the accepted source prefix, excluding an unacknowledged cached event. |
| invariants | Capture requires no cached event and no broken reader. The caller/session supplies a correctly positioned continuation; copied flags do not validate stream prefix or durable state. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Source/options scans, funded progress/CSV copies, fingerprint validation; restore validates CSV permutation with pair comparisons. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
recovery::ImageVector<std::size_t> csv_fields;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The owning native CSV physical-column permutation. |
| inputs / outputs | Stores/exposes the owning native CSV physical-column permutation. |
| invariants | Capture requires no cached event and no broken reader. The caller/session supplies a correctly positioned continuation; copied flags do not validate stream prefix or durable state. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Source/options scans, funded progress/CSV copies, fingerprint validation; restore validates CSV permutation with pair comparisons. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
std::uint64_t bytes=0,records=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The decoder byte and completed-record counters, distinct from accepted sequence. |
| inputs / outputs | Stores/exposes the decoder byte and completed-record counters, distinct from accepted sequence. |
| invariants | Capture requires no cached event and no broken reader. The caller/session supplies a correctly positioned continuation; copied flags do not validate stream prefix or durable state. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Source/options scans, funded progress/CSV copies, fingerprint validation; restore validates CSV permutation with pair comparisons. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
bool header_read=false,ended=false;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The decoder CSV-header and end-of-input flags. |
| inputs / outputs | Stores/exposes the decoder CSV-header and end-of-input flags. |
| invariants | Capture requires no cached event and no broken reader. The caller/session supplies a correctly positioned continuation; copied flags do not validate stream prefix or durable state. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Source/options scans, funded progress/CSV copies, fingerprint validation; restore validates CSV permutation with pair comparisons. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
std::array<char,64> catalog_sha256{};
  std::uint64_t work=0;
};
} // namespace crown::io

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The complete canonical catalog/source-schema binding bytes. |
| inputs / outputs | Stores/exposes the complete canonical catalog/source-schema binding bytes. |
| invariants | Capture requires no cached event and no broken reader. The caller/session supplies a correctly positioned continuation; copied flags do not validate stream prefix or durable state. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Source/options scans, funded progress/CSV copies, fingerprint validation; restore validates CSV permutation with pair comparisons. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

```text
std::uint64_t work=0;
};
} // namespace crown::io

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The source checkpoint preparation work already spent. |
| inputs / outputs | Stores/exposes the source checkpoint preparation work already spent. |
| invariants | Capture requires no cached event and no broken reader. The caller/session supplies a correctly positioned continuation; copied flags do not validate stream prefix or durable state. |
| ownership | Snapshot owns native source-position nodes and CSV field vectors where present, and retains immutable original-account options. Copying progress/CSV vectors can allocate; implicit options copies share immutable native values. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Source/options scans, funded progress/CSV copies, fingerprint validation; restore validates CSV permutation with pair comparisons. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../../src/io/checkpoint_detail.hpp), [docs/checkpoints.md](../../../../../checkpoints.md) |

## B0006

[Lines 33–33](../../../../../../include/crown/io/checkpoint.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L33:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [docs/code_specs/files/include/crown/io/checkpoint.hpp.md](checkpoint.hpp.md), [docs/ingestion.md](../../../../../ingestion.md), [docs/query_memory.md](../../../../../query_memory.md) |
