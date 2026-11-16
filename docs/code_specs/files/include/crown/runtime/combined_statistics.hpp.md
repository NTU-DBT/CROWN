# `include/crown/runtime/combined_statistics.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/combined_statistics.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `f4627780970995ab5395744f7da53ba7b89dd2385b4d93d435e7ef3e33f0efb8`. 28 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/runtime/combined_statistics.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // One synchronous actual-owner read under the native single-writer contract. · [reviewed contract](#b0001) |
| [B0002 · 10–27](../../../../../../include/crown/runtime/combined_statistics.hpp#L10) | Type/record definition: class CombinedCapture | returns *this; source comment (unverified): // One synchronous actual-owner read under the native single-writer contract. · [reviewed contract](#b0002) |
| [B0003 · 28–28](../../../../../../include/crown/runtime/combined_statistics.hpp#L28) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–9](../../../../../../include/crown/runtime/combined_statistics.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the runtime combined_statistics public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

## B0002

[Lines 10–27](../../../../../../include/crown/runtime/combined_statistics.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CombinedCapture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one genuine synchronous paired owner read. |
| inputs / outputs | Closed runtime/session factories join OwnerCapture and workload Snapshot at the same actual owner/committed epoch. |
| invariants | Owner/sequence/physical plan and pending-state consistency are checked; state and workload availability/interval domains remain separate. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Capture/binding/account allocation failures propagate before publication; mutable caller-paired snapshots cannot invoke the private constructor. |
| cost | Funded Data/control plus prepared native captures. Copying this handle does not deep-copy capture vectors/keys; independently copying returned OwnerCapture can. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
CombinedCapture(const CombinedCapture&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the immutable paired capture. |
| inputs / outputs | Operates on an already valid immutable paired capture. |
| invariants | Closed construction and copy-like moves preserve the nonempty Data invariant needed by noexcept access. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declared shared-copy/move/access operations do not throw. |
| cost | Fixed shared reference operation. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
CombinedCapture(CombinedCapture&& other) noexcept:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-like move keeping both paired handles valid. |
| inputs / outputs | Operates on an already valid immutable paired capture. |
| invariants | Closed construction and copy-like moves preserve the nonempty Data invariant needed by noexcept access. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declared shared-copy/move/access operations do not throw. |
| cost | Fixed shared reference operation; no source clearing. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
CombinedCapture& operator=(const CombinedCapture&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace by shared paired-capture copy. |
| inputs / outputs | Operates on an already valid immutable paired capture. |
| invariants | Closed construction and copy-like moves preserve the nonempty Data invariant needed by noexcept access. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declared shared-copy/move/access operations do not throw. |
| cost | Shared retention plus actual last release of any old capture graph. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
CombinedCapture& operator=(CombinedCapture&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-like move assignment preserving source handle. |
| inputs / outputs | Operates on an already valid immutable paired capture. |
| invariants | Closed construction and copy-like moves preserve the nonempty Data invariant needed by noexcept access. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declared shared-copy/move/access operations do not throw. |
| cost | Shared retention and actual replaced graph destruction. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
const OwnerCapture& state() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained owner-state capture. |
| inputs / outputs | Operates on an already valid immutable paired capture. |
| invariants | Closed construction and copy-like moves preserve the nonempty Data invariant needed by noexcept access. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declared shared-copy/move/access operations do not throw. |
| cost | Fixed reference access; explicit OwnerCapture value copy allocates original-account vectors/keys. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
const ::crown::runtime::workload::Snapshot& workload() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained workload snapshot. |
| inputs / outputs | Operates on an already valid immutable paired capture. |
| invariants | Closed construction and copy-like moves preserve the nonempty Data invariant needed by noexcept access. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declared shared-copy/move/access operations do not throw. |
| cost | Fixed reference access; no fresh collector read. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
static constexpr std::uint32_t format_version=1;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the paired capture format. |
| inputs / outputs | Operates on an already valid immutable paired capture. |
| invariants | Closed construction and copy-like moves preserve the nonempty Data invariant needed by noexcept access. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declared shared-copy/move/access operations do not throw. |
| cost | Compile-time constant. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
CombinedCapture(OwnerCapture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind prepared state/workload captures before publishing shared ownership. |
| inputs / outputs | Checks actual owner, committed sequence, physical plan digest and pending state agreement, then funds immutable Data on plan account. |
| invariants | Private factory authority plus consistency checks prevent caller-authored pair substitution. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | statistics_binding or original-account allocation failure returns no combined result. |
| cost | Fixed stamp/digest checks and funded Data/control allocation, then capture moves; state capture work happened beforehand. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
friend class ::crown::runtime::SupportRuntime;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow support owner genuine paired capture. |
| inputs / outputs | Private constructor access or shared storage declaration. |
| invariants | No public editable snapshot-pair constructor. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declaration creates no handler or runtime operation. |
| cost | Compile-time access/fixed descriptor storage; last handle release pays actual capture/key/metadata destruction. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
friend class ::crown::runtime::PhysicalRuntime;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow physical owner genuine paired capture. |
| inputs / outputs | Private constructor access or shared storage declaration. |
| invariants | No public editable snapshot-pair constructor. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declaration creates no handler or runtime operation. |
| cost | Compile-time access/fixed descriptor storage; last handle release pays actual capture/key/metadata destruction. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
friend class ::crown::runtime::DeltaRuntime;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow Delta owner genuine paired capture. |
| inputs / outputs | Private constructor access or shared storage declaration. |
| invariants | No public editable snapshot-pair constructor. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declaration creates no handler or runtime operation. |
| cost | Compile-time access/fixed descriptor storage; last handle release pays actual capture/key/metadata destruction. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
friend class ::crown::runtime::QuerySession;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow session genuine paired capture. |
| inputs / outputs | Private constructor access or shared storage declaration. |
| invariants | No public editable snapshot-pair constructor. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declaration creates no handler or runtime operation. |
| cost | Compile-time access/fixed descriptor storage; last handle release pays actual capture/key/metadata destruction. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
struct Data;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide retained immutable state/workload members. |
| inputs / outputs | Private constructor access or shared storage declaration. |
| invariants | No public editable snapshot-pair constructor. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declaration creates no handler or runtime operation. |
| cost | Compile-time access/fixed descriptor storage; last handle release pays actual capture/key/metadata destruction. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

```text
std::shared_ptr<const Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the immutable paired snapshot graph. |
| inputs / outputs | Private constructor access or shared storage declaration. |
| invariants | No public editable snapshot-pair constructor. |
| ownership | Shared immutable accounted Data owns its OwnerCapture and workload Snapshot. Those retain compiled metadata, native vectors and any copied heavy-key payloads. No live source-row pin, mutable owner pointer, cursor or lease is retained. Custom moves preserve both shared handles. |
| failure | Declaration creates no handler or runtime operation. |
| cost | Compile-time access/fixed descriptor storage; last handle release pays actual capture/key/metadata destruction. |
| Design | [include/crown/runtime/combined_statistics.hpp](../../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/combined_statistics.cpp](../../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/owner_statistics.hpp](../../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md](../../../../../statistics.md) |

## B0003

[Lines 28–28](../../../../../../include/crown/runtime/combined_statistics.hpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::statistics\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::statistics\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::statistics\` at its lexical source position in include/crown/runtime/combined_statistics.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::statistics\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../../statistics.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
