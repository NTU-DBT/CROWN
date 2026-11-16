# `include/crown/io/input_progress.hpp` — block usage map

[Source](../../../../../../include/crown/io/input_progress.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Track exact resumable record/source position independently of runtime/output sequence.

Snapshot SHA-256: `c36063da7a2daaf00602414a620b5569bec536440392f76b322f412acc94baf6`. 82 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../../include/crown/io/input_progress.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Read-only source positions with native object/node/key ownership. Copies are · [reviewed contract](#b0001) |
| [B0002 · 24–37](../../../../../../include/crown/io/input_progress.hpp#L24) | Type/record definition: class Prepared | source comment (unverified): // A preparation belongs to its original live map. It is not a foreign-safe · [reviewed contract](#b0002) |
| [B0003 · 38–45](../../../../../../include/crown/io/input_progress.hpp#L38) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 46–46](../../../../../../include/crown/io/input_progress.hpp#L46) | Callable definition: \[\[nodiscard\]\] bool empty() const noexcept | calls size; returns size()==0 · [reviewed contract](#b0004) |
| [B0005 · 47–49](../../../../../../include/crown/io/input_progress.hpp#L47) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |
| [B0006 · 50–50](../../../../../../include/crown/io/input_progress.hpp#L50) | Callable definition: \[\[nodiscard\]\] bool contains(std::string_view name) const | calls find, end; returns find(name)!=end() · [reviewed contract](#b0006) |
| [B0007 · 51–55](../../../../../../include/crown/io/input_progress.hpp#L51) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Uses an existing iterator or prepaid node. No new allocation; ordered · [reviewed contract](#b0007) |
| [B0008 · 56–58](../../../../../../include/crown/io/input_progress.hpp#L56) | Callable definition: \[\[nodiscard\]\] bool operator==(const InputPositions& other) const | calls begin, end; returns std::equal(begin(),end(),other.begin(),other.end()) · [reviewed contract](#b0008) |
| [B0009 · 59–62](../../../../../../include/crown/io/input_progress.hpp#L59) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 63–81](../../../../../../include/crown/io/input_progress.hpp#L63) | Type/record definition: struct AccountedInputProgress | returns *this; source comment (unverified): // Explicit caller-owned DTO export. Operational owners retain this native · [reviewed contract](#b0010) |
| [B0011 · 82–82](../../../../../../include/crown/io/input_progress.hpp#L82) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0011) |

## B0001

[Lines 1–23](../../../../../../include/crown/io/input_progress.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io input_progress public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
namespace input_detail {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind source allocations to their stable attribution label. |
| inputs / outputs | memory_owner is session attribution ID2, used by native option/source objects. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Fixed constexpr metadata, not a source/account owner. |
| failure | No runtime failure. |
| cost | No allocation or traversal at declaration. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
inline constexpr resource::MemoryAttribution memory_owner
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the source-state allocation attribution. |
| inputs / outputs | Classifies allocations under their real account; does not reserve or duplicate them. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Fixed inline metadata. |
| failure | No runtime failure. |
| cost | Fixed constexpr storage. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
class InputPositions {

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a native accepted source-position map with prepaid publication. |
| inputs / outputs | Lookup/copy/export callers read source-name offsets; prepare allocates a missing node and publish later links it or updates an existing offset. |
| invariants | The container alone does not validate names, monotonicity, source count or sequence. Source owner validates those before preparation. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Native allocation/contract/out_of_range failures propagate; prepared owner/protocol violations at noexcept publish are not recoverable foreign-token errors. |
| cost | Ordered lookups and private node/text preparation; owning copies allocate Data, map nodes and nonempty key character blocks and copy their bytes; valid publish adds no allocation. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
struct Data;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide the source map/account owner. |
| inputs / outputs | Data retains original MemoryAccount and native Map. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Declaration creates no live owner. |
| cost | No runtime action. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
using Map=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify the real native source map allocator/key order. |
| inputs / outputs | AccountedText keys, uint64 offsets, transparent text comparator and MemoryAllocator-funded nodes. |
| invariants | Key byte ownership and node storage are actual accounted objects, not a capacity ticket. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Type declaration itself has no runtime failure. |
| cost | No hidden secondary ordinary map. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
using const_iterator=Map::const_iterator;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose read-only borrowed map traversal. |
| inputs / outputs | Iterator refers to this exact map storage and does not retain Data. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Iterator invalidation follows actual map replacement/release; no runtime liveness check. |
| cost | Fixed iterator descriptor. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0002

[Lines 24–37](../../../../../../include/crown/io/input_progress.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Prepared
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one exact-map prepaid source-position update. |
| inputs / outputs | Move-only existing-entry iterator/offset or privately owned extracted new node. |
| invariants | Publish only into the original still-live map, with no conflicting change to its prepared name/entry. This token contains no foreign-owner validation. |
| ownership | A new-node preparation owns its native node/key handles; an existing iterator does not keep its map alive. |
| failure | Unused node destruction releases private ownership. Default preparation is empty. Foreign/stale/multiply published use violates the internal protocol. |
| cost | Fixed token fields plus optional prepaid map node/key allocation done by prepare; publish adds none. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
Prepared() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty no-op preparation. |
| inputs / outputs | Operate on the move-only Prepared value. |
| invariants | The exact original map and nonconflicting prepared entry must remain valid; moves do not add validation. |
| ownership | Node handle owns new-node storage; existing iterator borrows its map. |
| failure | Declared noexcept/default operations do not throw; deleted operations fail compilation. |
| cost | Fixed transfer plus release of any replaced node/key handle; no new allocation. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
Prepared(Prepared&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a private pending node/iterator preparation. |
| inputs / outputs | Operate on the move-only Prepared value. |
| invariants | The exact original map and nonconflicting prepared entry must remain valid; moves do not add validation. |
| ownership | Node handle owns new-node storage; existing iterator borrows its map. |
| failure | Declared noexcept/default operations do not throw; deleted operations fail compilation. |
| cost | Fixed transfer plus release of any replaced node/key handle; no new allocation. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
Prepared& operator=(Prepared&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace and transfer pending preparation ownership. |
| inputs / outputs | Operate on the move-only Prepared value. |
| invariants | The exact original map and nonconflicting prepared entry must remain valid; moves do not add validation. |
| ownership | Node handle owns new-node storage; existing iterator borrows its map. |
| failure | Declared noexcept/default operations do not throw; deleted operations fail compilation. |
| cost | Fixed transfer plus release of any replaced node/key handle; no new allocation. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
Prepared(const Prepared&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject duplicate prepared publication tokens. |
| inputs / outputs | Operate on the move-only Prepared value. |
| invariants | The exact original map and nonconflicting prepared entry must remain valid; moves do not add validation. |
| ownership | Node handle owns new-node storage; existing iterator borrows its map. |
| failure | Declared noexcept/default operations do not throw; deleted operations fail compilation. |
| cost | Fixed transfer plus release of any replaced node/key handle; no new allocation. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
Prepared& operator=(const Prepared&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject prepared-token copy assignment. |
| inputs / outputs | Operate on the move-only Prepared value. |
| invariants | The exact original map and nonconflicting prepared entry must remain valid; moves do not add validation. |
| ownership | Node handle owns new-node storage; existing iterator borrows its map. |
| failure | Declared noexcept/default operations do not throw; deleted operations fail compilation. |
| cost | Fixed transfer plus release of any replaced node/key handle; no new allocation. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
friend class InputPositions;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict access to pending map links/iterator fields. |
| inputs / outputs | Private Prepared state; populated only by InputPositions::prepare. |
| invariants | Flags/iterator/node must obey the exact-map publication protocol; they are not caller-authored acceptance authority. |
| ownership | New node handle owns storage; iterator only borrows; offset/flag are inline. |
| failure | No field-side validation or recovery. |
| cost | Fixed metadata/node-handle descriptor; releasing owned node/key retains actual cleanup cost. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
Map::iterator existing_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the original existing source entry. |
| inputs / outputs | Private Prepared state; populated only by InputPositions::prepare. |
| invariants | Flags/iterator/node must obey the exact-map publication protocol; they are not caller-authored acceptance authority. |
| ownership | New node handle owns storage; iterator only borrows; offset/flag are inline. |
| failure | No field-side validation or recovery. |
| cost | Fixed metadata/node-handle descriptor; releasing owned node/key retains actual cleanup cost. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
Map::node_type node_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a prepaid extracted new map node. |
| inputs / outputs | Private Prepared state; populated only by InputPositions::prepare. |
| invariants | Flags/iterator/node must obey the exact-map publication protocol; they are not caller-authored acceptance authority. |
| ownership | New node handle owns storage; iterator only borrows; offset/flag are inline. |
| failure | No field-side validation or recovery. |
| cost | Fixed metadata/node-handle descriptor; releasing owned node/key retains actual cleanup cost. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::uint64_t offset_=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the offset to publish. |
| inputs / outputs | Private Prepared state; populated only by InputPositions::prepare. |
| invariants | Flags/iterator/node must obey the exact-map publication protocol; they are not caller-authored acceptance authority. |
| ownership | New node handle owns storage; iterator only borrows; offset/flag are inline. |
| failure | No field-side validation or recovery. |
| cost | Fixed metadata/node-handle descriptor; releasing owned node/key retains actual cleanup cost. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
bool existing=false;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Indicate that existing_ is valid for this original map. |
| inputs / outputs | Private Prepared state; populated only by InputPositions::prepare. |
| invariants | Flags/iterator/node must obey the exact-map publication protocol; they are not caller-authored acceptance authority. |
| ownership | New node handle owns storage; iterator only borrows; offset/flag are inline. |
| failure | No field-side validation or recovery. |
| cost | Fixed metadata/node-handle descriptor; releasing owned node/key retains actual cleanup cost. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0003

[Lines 38–45](../../../../../../include/crown/io/input_progress.hpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPositions() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty unbound positions descriptor. |
| inputs / outputs | No Data/account until explicit account construction. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Fixed empty initialization. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
explicit InputPositions(const resource::MemoryAccount&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty positions map on its real account. |
| inputs / outputs | Allocates funded Data and configures map allocator. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | One native Data owner; empty map has no nodes. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
~InputPositions();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release this native positions snapshot. |
| inputs / outputs | Destroys map nodes and retained key/account handles. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Releases this snapshot Data, map nodes and their independently owned key character blocks. The shared MemoryAccount controller may remain retained by other owners. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
InputPositions(const InputPositions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a value snapshot on the original account. |
| inputs / outputs | Clones native Data/map nodes and each nonempty AccountedText key character block on the source account, copying its bytes and offset value. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Linear map-node construction plus total key-byte copies and native character-block allocations on the source account; no replacement query allowance. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
InputPositions& operator=(const InputPositions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace positions with a strongly prepared value copy. |
| inputs / outputs | Constructs temporary copied snapshot then moves it in. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Prepared Data/nodes/key character blocks overlap old/new snapshots, potentially on different retained accounts. Failure preserves this value; successful replacement releases the old map and key blocks. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
InputPositions(InputPositions&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer positions Data ownership. |
| inputs / outputs | Moves the native unique Data descriptor. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Fixed transfer, no node/text clone. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
InputPositions& operator=(InputPositions&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace and transfer positions Data. |
| inputs / outputs | Releases old map then transfers descriptor. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Fixed transfer plus actual old map/key release, no new allocation. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
std::size_t size() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read accepted source-name population. |
| inputs / outputs | Absent Data returns0. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Fixed count read. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0004

[Lines 46–46](../../../../../../include/crown/io/input_progress.hpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool empty() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether the positions map is empty. |
| inputs / outputs | Uses size(), without allocating Data. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Fixed count test. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0005

[Lines 47–49](../../../../../../include/crown/io/input_progress.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const_iterator begin() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the first source-position entry. |
| inputs / outputs | Uses live map or a static empty map sentinel. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Fixed iterator access; empty sentinel allocates no node. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
const_iterator end() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the source-position end sentinel. |
| inputs / outputs | Uses the same empty range sentinel as begin when absent. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Fixed iterator access. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
const_iterator find(std::string_view) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find one source identifier by borrowed text. |
| inputs / outputs | Transparent map lookup; absent map returns end. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | O(log positions) ordered comparisons with actual source-name bytes; no key copy. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0006

[Lines 50–50](../../../../../../include/crown/io/input_progress.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool contains(std::string_view name) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether a source name exists. |
| inputs / outputs | Compares one transparent find with end. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | One ordered lookup, no second scan/export. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0007

[Lines 51–55](../../../../../../include/crown/io/input_progress.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::uint64_t& at(std::string_view) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an existing source offset. |
| inputs / outputs | Finds name or throws std::out_of_range. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Ordered lookup and fixed reference; failure may construct an ordinary exception message. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
Prepared prepare(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare exactly one source-position publication without changing the map. |
| inputs / outputs | Existing name returns borrowed iterator/offset; missing name allocates AccountedText/map node in a private temporary then extracts its node handle. |
| invariants | Name validity, count limits and strict offset increase are checked by the calling source owner; prepare itself does not enforce them. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Empty Data rejects MemoryFailure(contract); private key/node allocation failure leaves map membership/offsets unchanged. |
| cost | One ordered lookup plus optional native key character-block and map-node allocation; the existing MemoryAccount controller is retained, not separately allocated per key. No source acceptance. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
void publish(Prepared&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a valid original-map prepared position without allocating. |
| inputs / outputs | Inserts the prepaid node, updates the prepared existing offset or does nothing for empty preparation. |
| invariants | Requires the original map/iterator and no conflicting entry change; this low-level token is not foreign-safe and does not validate source monotonicity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Empty Data or duplicate inserted key terminates as an internal protocol invariant; no recovery catch or validation registry. |
| cost | Ordered insertion/link of an already allocated node or fixed offset update. No new node/text allocation, though tree search/link work remains. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0008

[Lines 56–58](../../../../../../include/crown/io/input_progress.hpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool operator==(const InputPositions& other) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare source-name/offset values. |
| inputs / outputs | std::equal over both native ordered maps. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Linear entries/key bytes until mismatch; no source/account identity proof. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0009

[Lines 59–62](../../../../../../include/crown/io/input_progress.hpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool operator==(const std::map<std::string,std::uint64_t>&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare to an ordinary exported positions map. |
| inputs / outputs | Checks size then ordered key text/offset values. |
| invariants | Positions are source data; map equality is not account, stream-prefix, sequence or durable identity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Construction/copy can fail native allocation; at can throw absent-key error. Declared noexcept moves/accessors do not throw. |
| cost | Linear entries/key bytes until mismatch, no ordinary export/allocation. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
resource::AccountedUnique<Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the sole native map snapshot descriptor. |
| inputs / outputs | Null means empty/unbound; actual map object/account remains in Data. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Data preparation can fail, descriptor moves do not. |
| cost | Fixed descriptor; final map release traverses real nodes. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0010

[Lines 63–81](../../../../../../include/crown/io/input_progress.hpp#L63); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedInputProgress {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a native accepted sequence and positions snapshot. |
| inputs / outputs | Inline accepted sequence plus native InputPositions; explicit DTO/account imports and ordinary export are named. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Implicit copies clone Data, map nodes and nonempty key character blocks on the source account. Explicit receiving imports clone those values into the supplied account. Moves transfer native Data. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
std::uint64_t sequence=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The accepted source sequence, excluding pending records. |
| inputs / outputs | Stores/exposes the accepted source sequence, excluding pending records. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Implicit copies clone Data, map nodes and nonempty key character blocks on the source account. Explicit receiving imports clone those values into the supplied account. Moves transfer native Data. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
InputPositions source_positions;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The owning native accepted source-name/offset snapshot. |
| inputs / outputs | Stores/exposes the owning native accepted source-name/offset snapshot. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Implicit copies clone Data, map nodes and nonempty key character blocks on the source account. Explicit receiving imports clone those values into the supplied account. Moves transfer native Data. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
AccountedInputProgress() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, copy or transfer accepted progress. |
| inputs / outputs | Create zero sequence and empty unbound positions. |
| invariants | Sequence and positions form one accepted value; copying it does not accept input or prove source-prefix continuity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Copy/import native allocations may fail. Declared noexcept empty/move operations do not throw. |
| cost | Fixed empty initialization. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
explicit AccountedInputProgress(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, copy or transfer accepted progress. |
| inputs / outputs | Create zero sequence and empty native positions Data on the account. |
| invariants | Sequence and positions form one accepted value; copying it does not accept input or prove source-prefix continuity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Copy/import native allocations may fail. Declared noexcept empty/move operations do not throw. |
| cost | Native positions Data allocation; no source nodes yet. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
AccountedInputProgress(const resource::MemoryAccount&,const InputProgress&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, copy or transfer accepted progress. |
| inputs / outputs | Import ordinary accepted sequence/source names into the receiving account. |
| invariants | Sequence and positions form one accepted value; copying it does not accept input or prove source-prefix continuity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Copy/import native allocations may fail. Declared noexcept empty/move operations do not throw. |
| cost | O(positions log positions + source bytes) fresh Data/node/text imports. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
AccountedInputProgress(const resource::MemoryAccount&,const AccountedInputProgress&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, copy or transfer accepted progress. |
| inputs / outputs | Clone native accepted data into an explicit receiving account. |
| invariants | Sequence and positions form one accepted value; copying it does not accept input or prove source-prefix continuity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Copy/import native allocations may fail. Declared noexcept empty/move operations do not throw. |
| cost | Fresh Data/map nodes and nonempty key character blocks/byte copies in the supplied receiving account. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
AccountedInputProgress(const AccountedInputProgress&)=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, copy or transfer accepted progress. |
| inputs / outputs | Copy the accepted native value snapshot on its original account. |
| invariants | Sequence and positions form one accepted value; copying it does not accept input or prove source-prefix continuity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Copy/import native allocations may fail. Declared noexcept empty/move operations do not throw. |
| cost | InputPositions Data/map-node construction plus each nonempty key character block and byte copy on the original source account. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
AccountedInputProgress& operator=(const AccountedInputProgress& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, copy or transfer accepted progress. |
| inputs / outputs | Strongly prepare accepted-value copy before replacement. |
| invariants | Sequence and positions form one accepted value; copying it does not accept input or prove source-prefix continuity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Copy/import native allocations may fail. Declared noexcept empty/move operations do not throw. |
| cost | Old/new Data, map nodes and key character blocks overlap during preparation; failure preserves prior sequence and map as one value. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
AccountedInputProgress(AccountedInputProgress&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, copy or transfer accepted progress. |
| inputs / outputs | Transfer native accepted snapshot. |
| invariants | Sequence and positions form one accepted value; copying it does not accept input or prove source-prefix continuity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Copy/import native allocations may fail. Declared noexcept empty/move operations do not throw. |
| cost | Fixed sequence/Data move, no node/text clone. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
AccountedInputProgress& operator=(AccountedInputProgress&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct, copy or transfer accepted progress. |
| inputs / outputs | Replace and transfer native accepted snapshot. |
| invariants | Sequence and positions form one accepted value; copying it does not accept input or prove source-prefix continuity. |
| ownership | InputPositions uniquely owns native map Data on its original account. Copy construction clones Data, map nodes and every nonempty AccountedText key character block on that original account; no key characters are shared between snapshots. Moves transfer Data. Iterators/references and existing Prepared iterators borrow the exact live map. |
| failure | Copy/import native allocations may fail. Declared noexcept empty/move operations do not throw. |
| cost | Transfer plus actual old map/key release, no new allocation. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
bool operator==(const AccountedInputProgress&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare accepted sequence and native position values. |
| inputs / outputs | Reads accepted sequence/positions; export returns a separate owning DTO. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Comparisons borrow maps; export owns new ordinary strings/nodes. |
| failure | Export allocation failures propagate; no source progress mutation. |
| cost | Fixed sequence comparison plus linear native map/key comparison. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
bool operator==(const InputProgress&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare accepted native values to an ordinary DTO. |
| inputs / outputs | Reads accepted sequence/positions; export returns a separate owning DTO. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Comparisons borrow maps; export owns new ordinary strings/nodes. |
| failure | Export allocation failures propagate; no source progress mutation. |
| cost | Fixed sequence comparison plus linear native/ordinary ordered map comparison. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
InputProgress export_value() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export ordinary owned accepted progress. |
| inputs / outputs | Reads accepted sequence/positions; export returns a separate owning DTO. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Comparisons borrow maps; export owns new ordinary strings/nodes. |
| failure | Export allocation failures propagate; no source progress mutation. |
| cost | Ordinary map-node/string copies, O(positions log positions + source bytes); outside native account storage. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../../src/io/input_progress.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0011

[Lines 82–82](../../../../../../include/crown/io/input_progress.hpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L82:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/io/input_progress.hpp](../../../../../../include/crown/io/input_progress.hpp), [docs/code_specs/files/include/crown/io/input_progress.hpp.md](input_progress.hpp.md), [docs/ingestion.md](../../../../../ingestion.md), [docs/session_lifecycle.md](../../../../../session_lifecycle.md) |
