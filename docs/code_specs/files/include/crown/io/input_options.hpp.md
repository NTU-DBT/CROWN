# `include/crown/io/input_options.hpp` — block usage map

[Source](../../../../../../include/crown/io/input_options.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `980036f10e884f0f520d71568b845582d3f019a8151c1fea15797b6c4a4a1b20`. 45 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/io/input_options.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Native option descriptors share original-account Values on ordinary copy. · [reviewed contract](#b0001) |
| [B0002 · 14–31](../../../../../../include/crown/io/input_options.hpp#L14) | Type/record definition: public: struct Values | growth insert · [reviewed contract](#b0002) |
| [B0003 · 32–35](../../../../../../include/crown/io/input_options.hpp#L32) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 36–36](../../../../../../include/crown/io/input_options.hpp#L36) | Callable definition: \[\[nodiscard\]\] const resource::MemoryAccount& account() const noexcept | calls ; returns account_ · [reviewed contract](#b0004) |
| [B0005 · 37–45](../../../../../../include/crown/io/input_options.hpp#L37) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0005) |

## B0001

[Lines 1–13](../../../../../../include/crown/io/input_options.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io input_options public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
class AccountedInputOptions
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable native source configuration on its real account. |
| inputs / outputs | Closed constructor/import/export boundary between caller InputOptions and funded immutable Values. |
| invariants | Sharing a handle preserves its allocation authority; equal values do not equate accounts or validate source compatibility. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | Construction/import allocations may fail before a new handle is returned; get/default handling does not validate options. |
| cost | Shared descriptor copies are fixed operations; explicit imports copy maps/text, export creates ordinary owning DTOs, final graph release may traverse nodes. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0002

[Lines 14–31](../../../../../../include/crown/io/input_options.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Values {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the immutable native source-option payload. |
| inputs / outputs | Fixed source configuration plus account-allocated token map and immutable AccountedText values. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. Direct memberwise copy assignment retains the destination map allocator (nonpropagating copy assignment), while text copies use their source accounts; it is not an account-import operation or an atomic immutable publication. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Empty defaults allocate no map nodes/text. Implicit copy construction clones map nodes and nonempty key/null/source character blocks and copies their bytes; explicit receiving-account imports clone into the supplied account. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
using Tokens=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The ordered AccountedText-to-table map using the actual MemoryAllocator. |
| inputs / outputs | Stores/exposes the ordered AccountedText-to-table map using the actual MemoryAllocator. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Empty fixed/default map initialization is distinct from imported map-node/text allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
InputFormat format=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The stored source-format tag. |
| inputs / outputs | Stores/exposes the stored source-format tag. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Empty fixed/default map initialization is distinct from imported map-node/text allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
InputLimits limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The stored wire/source limit configuration. |
| inputs / outputs | Stores/exposes the stored wire/source limit configuration. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Empty fixed/default map initialization is distinct from imported map-node/text allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
std::optional<TableId> table;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional explicit physical table. |
| inputs / outputs | Stores/exposes the optional explicit physical table. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Empty fixed/default map initialization is distinct from imported map-node/text allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
char delimiter=',';
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The stored single-byte delimiter. |
| inputs / outputs | Stores/exposes the stored single-byte delimiter. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Empty fixed/default map initialization is distinct from imported map-node/text allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
bool header=true;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The stored CSV header option. |
| inputs / outputs | Stores/exposes the stored CSV header option. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Empty fixed/default map initialization is distinct from imported map-node/text allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
SetOperation csv_operation=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The stored CSV set operation. |
| inputs / outputs | Stores/exposes the stored CSV set operation. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Empty fixed/default map initialization is distinct from imported map-node/text allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
Tokens relation_tokens;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The original-account map nodes and retained immutable token text. |
| inputs / outputs | Stores/exposes the original-account map nodes and retained immutable token text. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Empty fixed/default map initialization is distinct from imported map-node/text allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
std::optional<resource::AccountedText> null_token,source;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The native immutable null spelling and upstream source ID. |
| inputs / outputs | Stores/exposes the native immutable null spelling and upstream source ID. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Empty fixed/default map initialization is distinct from imported map-node/text allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
std::uint64_t byte_offset=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The stored external source origin. |
| inputs / outputs | Stores/exposes the stored external source origin. |
| invariants | Values are only configuration. EventReader validates actual format/source/schema compatibility; the private publication constructor remains closed. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Empty fixed/default map initialization is distinct from imported map-node/text allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
Values()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or import native source options. |
| inputs / outputs | Create empty default options/map with no published account owner. |
| invariants | Construction stores values; the source owner performs semantic format/schema validation. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Empty/default or allocator-only construction performs no element allocation. Populated import/copy can fail native allocation and unwinds the new value; copying standalone Values does not share a Values control block. |
| cost | Fixed defaults and empty map; no token allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
explicit Values(const resource::MemoryAccount&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or import native source options. |
| inputs / outputs | Configure the token map allocator for the supplied account. |
| invariants | Construction stores values; the source owner performs semantic format/schema validation. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Empty/default or allocator-only construction performs no element allocation. Populated import/copy can fail native allocation and unwinds the new value; copying standalone Values does not share a Values control block. |
| cost | Fixed defaults/allocator retention; empty map creates no nodes. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
Values(const resource::MemoryAccount&,const InputOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or import native source options. |
| inputs / outputs | Copy ordinary option fields and fresh native token/text storage into the account. |
| invariants | Construction stores values; the source owner performs semantic format/schema validation. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Empty/default or allocator-only construction performs no element allocation. Populated import/copy can fail native allocation and unwinds the new value; copying standalone Values does not share a Values control block. |
| cost | Ordered token-node/text imports plus optional text copies; original DTO remains caller owned. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

```text
Values(const resource::MemoryAccount&,const Values&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or import native source options. |
| inputs / outputs | Clone native option values into the receiving account. |
| invariants | Construction stores values; the source owner performs semantic format/schema validation. |
| ownership | Values directly owns its Tokens map and optional AccountedText fields. Its implicit copy constructor clones map nodes using the copied allocator and nonempty character blocks using each source text account. Explicit account-import constructors clone into the supplied account. The outer AccountedInputOptions descriptor separately shares a published const Values object. |
| failure | Empty/default or allocator-only construction performs no element allocation. Populated import/copy can fail native allocation and unwinds the new value; copying standalone Values does not share a Values control block. |
| cost | Fresh token nodes/text and optional text copies, even when the source already has native storage. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0003

[Lines 32–35](../../../../../../include/crown/io/input_options.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputOptions() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or import native source options. |
| inputs / outputs | Create an empty descriptor whose get uses static empty Values. |
| invariants | Construction stores values; the source owner performs semantic format/schema validation. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | Nonempty native construction can throw original-account MemoryFailure/bad_alloc; empty/default construction is nonthrowing as declared. |
| cost | Fixed empty account/shared descriptor. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
AccountedInputOptions(const resource::MemoryAccount&,const InputOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or import native source options. |
| inputs / outputs | Create funded Values/control directly from ordinary options. |
| invariants | Construction stores values; the source owner performs semantic format/schema validation. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | Nonempty native construction can throw original-account MemoryFailure/bad_alloc; empty/default construction is nonthrowing as declared. |
| cost | Native shared control/object plus full token-node/text import. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
AccountedInputOptions(const resource::MemoryAccount&,const AccountedInputOptions&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or import native source options. |
| inputs / outputs | Import/clone another descriptor into the explicit receiving account. |
| invariants | Construction stores values; the source owner performs semantic format/schema validation. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | Nonempty native construction can throw original-account MemoryFailure/bad_alloc; empty/default construction is nonthrowing as declared. |
| cost | New native control/object, map nodes and text; this is distinct from the implicit shared copy. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
const Values& get() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable native option values. |
| inputs / outputs | Returns stored Values, or static empty defaults for empty descriptor. |
| invariants | Immutable access/comparison never changes source progress or admits a source. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | No throwing operation; no implicit admission. |
| cost | Fixed borrowed reference access; an explicit caller Values value copy separately clones native map nodes and nonempty text character blocks. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0004

[Lines 36–36](../../../../../../include/crown/io/input_options.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& account() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained allocation account. |
| inputs / outputs | Returns the real account descriptor; empty options have no account. |
| invariants | Immutable access/comparison never changes source progress or admits a source. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | No throwing operation. |
| cost | Fixed reference access. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

## B0005

[Lines 37–45](../../../../../../include/crown/io/input_options.hpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputOptions(const resource::MemoryAccount&,Values&&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct or import native source options. |
| inputs / outputs | Privately publish already prepared native Values. |
| invariants | Construction stores values; the source owner performs semantic format/schema validation. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | Nonempty native construction can throw original-account MemoryFailure/bad_alloc; empty/default construction is nonthrowing as declared. |
| cost | Funded shared control/object and Values/map move; no ordinary export/reparse. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
InputOptions export_value() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export ordinary owned source options. |
| inputs / outputs | Copies fixed config, token text/map, optional source/null text into InputOptions. |
| invariants | Immutable access/comparison never changes source progress or admits a source. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | Ordinary allocation failures propagate without changing native Values. |
| cost | O(tokens log tokens + text bytes) map/string reconstruction outside native account storage. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
bool same_values(const AccountedInputOptions&) const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare option values independently of account identity. |
| inputs / outputs | Compares every fixed field, token map and optional text. |
| invariants | Immutable access/comparison never changes source progress or admits a source. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | No throwing comparison; equal values are not a shared grant/source capability. |
| cost | Linear token/text comparison in the worst case; no export or allocation. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
friend struct recovery::detail::SessionImageAccess;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict direct native Values publication to the session-image codec. |
| inputs / outputs | Private access/member storage for immutable options. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | Declaration/descriptor sharing adds no semantic validation or handler. |
| cost | Fixed descriptor storage/retention; last release pays actual control/map/text destruction. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
resource::MemoryAccount account_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the actual option allocation authority. |
| inputs / outputs | Private access/member storage for immutable options. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | Declaration/descriptor sharing adds no semantic validation or handler. |
| cost | Fixed descriptor storage/retention; last release pays actual control/map/text destruction. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |

```text
std::shared_ptr<const Values> values_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the immutable funded native option graph. |
| inputs / outputs | Private access/member storage for immutable options. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | account_ retains the original MemoryAccount and values_ shares its immutable native Values/control/map/text graph. An ordinary object copy shares this graph; explicit account-import constructors clone receiving-account nodes/text. |
| failure | Declaration/descriptor sharing adds no semantic validation or handler. |
| cost | Fixed descriptor storage/retention; last release pays actual control/map/text destruction. |
| Design | [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [src/io/input_options.cpp](../../../../../../src/io/input_options.cpp), [src/io/event_reader.cpp](../../../../../../src/io/event_reader.cpp), [docs/ingestion.md](../../../../../ingestion.md) |
