# `src/io/input_progress.cpp` — block usage map

[Source](../../../../../src/io/input_progress.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Track exact resumable record/source position independently of runtime/output sequence.

Snapshot SHA-256: `aff3888cc55d683b72b1708959809d714882a0ab1360d96cd41b9e3c2c39a68a`. 91 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/io/input_progress.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–13](../../../../../src/io/input_progress.cpp#L6) | Type/record definition: struct InputPositions::Data |  · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../src/io/input_progress.cpp#L14) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 15–17](../../../../../src/io/input_progress.cpp#L15) | Callable definition: InputPositions::InputPositions(const resource::MemoryAccount& account) :data_(resource::make_accounted_unique&lt;Data&gt;(input_detail:… | calls data_; growth make_accounted_unique · [reviewed contract](#b0004) |
| [B0005 · 18–20](../../../../../src/io/input_progress.cpp#L18) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |
| [B0006 · 21–24](../../../../../src/io/input_progress.cpp#L21) | Callable definition: InputPositions::InputPositions(const InputPositions& source) | calls ; growth make_accounted_unique · [reviewed contract](#b0006) |
| [B0007 · 25–27](../../../../../src/io/input_progress.cpp#L25) | Callable definition: InputPositions& InputPositions::operator=(const InputPositions& source) | calls std::move; returns *this · [reviewed contract](#b0007) |
| [B0008 · 28–28](../../../../../src/io/input_progress.cpp#L28) | Callable definition: std::size_t InputPositions::size() const noexcept | calls size; returns data_?data_-&gt;values.size():0 · [reviewed contract](#b0008) |
| [B0009 · 29–33](../../../../../src/io/input_progress.cpp#L29) | Callable definition: InputPositions::const_iterator InputPositions::begin() const noexcept | calls begin; returns data_-&gt;values.begin(); empty.begin() · [reviewed contract](#b0009) |
| [B0010 · 34–38](../../../../../src/io/input_progress.cpp#L34) | Callable definition: InputPositions::const_iterator InputPositions::end() const noexcept | calls end, begin; returns data_-&gt;values.end(); begin(); source comment (unverified): // Use the same empty range sentinel as begin(), without allocating a node. · [reviewed contract](#b0010) |
| [B0011 · 39–41](../../../../../src/io/input_progress.cpp#L39) | Callable definition: InputPositions::const_iterator InputPositions::find(std::string_view name) const | calls find, end; returns data_?data_-&gt;values.find(name):end() · [reviewed contract](#b0011) |
| [B0012 · 42–44](../../../../../src/io/input_progress.cpp#L42) | Callable definition: const std::uint64_t& InputPositions::at(std::string_view name) const | calls find, end, std::out_of_range; returns found-&gt;second · [reviewed contract](#b0012) |
| [B0013 · 45–54](../../../../../src/io/input_progress.cpp#L45) | Callable definition: InputPositions::Prepared InputPositions::prepare(std::string_view name,std::uint64_t offset) | calls resource::MemoryFailure, find, end, nodes; returns prepared; prepared; growth copy_of, emplace; source comment (unverified): // The source owner checks ordering/counts first; only detached storage is prepared here. · [reviewed contract](#b0013) |
| [B0014 · 55–61](../../../../../src/io/input_progress.cpp#L55) | Callable definition: void InputPositions::publish(Prepared& prepared) noexcept | calls std::terminate, insert, std::move; growth insert; source comment (unverified): // Link funded storage after commit; new-name insertion still performs tree comparisons. · [reviewed contract](#b0014) |
| [B0015 · 62–70](../../../../../src/io/input_progress.cpp#L62) | Callable definition: bool InputPositions::operator==(const std::map&lt;std::string,std::uint64_t&gt;& other) const | calls begin, view; returns false; false; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 71–76](../../../../../src/io/input_progress.cpp#L71) | Callable definition: AccountedInputProgress::AccountedInputProgress(const resource::MemoryAccount& account,const InputProgress& source) :sequence(sour… | calls sequence, source_positions, prepare, publish; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 77–79](../../../../../src/io/input_progress.cpp#L77) | Callable definition: bool AccountedInputProgress::operator==(const InputProgress& other) const | returns sequence==other.sequence && source_positions==other.source_positions · [reviewed contract](#b0017) |
| [B0018 · 80–85](../../../../../src/io/input_progress.cpp#L80) | Callable definition: AccountedInputProgress::AccountedInputProgress(const resource::MemoryAccount& account,const AccountedInputProgress& source) :sequ… | calls sequence, source_positions, prepare, view; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 86–90](../../../../../src/io/input_progress.cpp#L86) | Callable definition: InputProgress AccountedInputProgress::export_value() const | calls emplace, std::string, view; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 91–91](../../../../../src/io/input_progress.cpp#L91) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0020) |

## B0001

[Lines 1–5](../../../../../src/io/input_progress.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/input_progress.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement original-account source-position values and their prepare/acknowledge publication boundary. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 6–13](../../../../../src/io/input_progress.cpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputPositions::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the real source directory and its funding account behind InputPositions. |
| inputs / outputs | Account constructor creates an empty attributed map; copy constructor clones every node/key/value under the original account. |
| invariants | The map allocator uses support_metadata/session:2; AccountedText keys own their actual character blocks, not a shadow accounting ticket. |
| ownership | Data owns MemoryAccount plus Map. Its destruction traverses/frees nodes and key blocks, then releases account handles. |
| failure | Invalid allocator/account or node/key allocation can fail during private construction; fully constructed members unwind without publishing a directory. |
| cost | Empty construction O(1); copy O(N+key bytes), destruction O(N) node/key releases without rescanning text; original and clone simultaneously charged during copy. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
resource::MemoryAccount account;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the original funding domain for future directory control/node/key requests. |
| inputs / outputs | Copies the account handle into Data; no new byte grant is created. |
| invariants | Map allocation and copied text continue using this same account identity. |
| ownership | Shared MemoryAccount controller handle, not an owning byte mirror of the map. |
| failure | Handle copy itself does not perform a payload allocation; downstream constructors validate/use the account. |
| cost | O(1) reference retention/release, with final controller release following actual account lifetime. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
Map values;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store ordered immutable owned source names and mutable accepted offsets. |
| inputs / outputs | Map keys are AccountedText and mapped values uint64_t; comparisons support borrowed string_view lookup. |
| invariants | Only prepare creates detached nodes and publish links them or updates a mapped offset. |
| ownership | Owns node capacity and each key block under its allocator/account; map copy deep-copies keys. |
| failure | Node/key construction can fail; erasure/destruction releases actual allocations. |
| cost | N ordered nodes plus source bytes; lookup/insertion O(log N) string comparisons, worst O(L log N) bytes. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
explicit Data(const resource::MemoryAccount& memory)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize an empty map with the supplied original account and immutable source-directory attribution. |
| inputs / outputs | Input is a valid MemoryAccount; output is an empty Data with a matching map allocator. |
| invariants | No directory entries or accepted offsets are added by construction. |
| ownership | Copies the account handle into Data and allocator; empty map has no node allocation. |
| failure | Allocator rejects invalid account/purpose/attribution before usable Data construction. |
| cost | O(1) handle/setup work; outer make_accounted_unique separately funds the Data control/object request. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
Data(const Data& source):account(source.account),values(source.values) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy the directory while retaining its original funding domain. |
| inputs / outputs | Reads source.account and source.values; builds an independent map and offsets. |
| invariants | Standard select_on_container_copy_construction retains source allocator; AccountedText copy allocates original-account bytes. |
| ownership | Owns fresh nodes and key blocks, shares only account controller identity. |
| failure | Any key/node allocation failure destroys the partial map before construction returns. |
| cost | O(N+sum key bytes) clone work/storage; source remains charged throughout. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 14–14](../../../../../src/io/input_progress.cpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPositions::InputPositions() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an inert empty InputPositions without establishing a mutable directory. |
| inputs / outputs | No arguments; data_ remains empty; read-only empty-range APIs are supported. |
| invariants | prepare rejects and publish terminates on this inert/moved-from state. |
| ownership | No Data, nodes, key bytes or account retained. |
| failure | noexcept default construction; no admission or allocation. |
| cost | O(1). |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 15–17](../../../../../src/io/input_progress.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPositions::InputPositions(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund the real mutable directory object before accepting source positions. |
| inputs / outputs | Valid account in; an empty Data allocated with support_metadata/session:2 out. |
| invariants | A valid Data is required for prepare/publication; this does not validate any source name or offset. |
| ownership | AccountedUnique owns the Data allocation and its embedded map/account. |
| failure | Native account/allocator failure occurs before the InputPositions constructor returns. |
| cost | One accounted object/control request plus O(1) empty-map setup; no source-node request yet. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 18–20](../../../../../src/io/input_progress.cpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPositions::~InputPositions()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release a directory and all original-account node/key allocations. |
| inputs / outputs | Destruction consumes data_ and its map; produces no result. |
| invariants | No Prepared holding an iterator or directory-dependent pending node may be published after directory destruction. |
| ownership | Unique Data owns nodes/keys; borrowed iterators/references cease to be usable. |
| failure | Default destruction follows nonthrowing native deallocation contracts; allocator misuse can terminate. |
| cost | O(N) node/key releases; account controller release only after all its handles/blocks are gone. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
InputPositions::InputPositions(InputPositions&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a complete directory into a new owner. |
| inputs / outputs | Rvalue source in; destination receives its Data and source becomes inert. |
| invariants | No key/node clone or fresh grant is created. |
| ownership | Transfers AccountedUnique and the existing account graph; preexisting borrowed backing still belongs to the transferred Data. |
| failure | noexcept default move construction. |
| cost | O(1) owner transfer, without allocating. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
InputPositions& InputPositions::operator=(InputPositions&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a directory with an existing owned directory. |
| inputs / outputs | Rvalue source supplies Data; destination old Data is released. |
| invariants | Pending preparations must not rely on the directory that assignment destroys. |
| ownership | Moves unique ownership; does not clone names or rebind node allocators. |
| failure | noexcept default move assignment; old directory teardown must obey allocator contracts. |
| cost | O(1) transfer plus O(N_old) node/key teardown; not universally constant-time assignment. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 21–24](../../../../../src/io/input_progress.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPositions::InputPositions(const InputPositions& source) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an independent value snapshot under the source directory account. |
| inputs / outputs | Empty source yields empty data_; otherwise a new Data and full map clone are constructed. |
| invariants | Accepted source directory is unchanged if cloning fails. |
| ownership | Fresh Data/nodes/text own their blocks; account controller identity is shared with source. |
| failure | Control/node/key allocation may throw before the new snapshot exists; partial clone unwinds. |
| cost | O(N+key bytes) copy/storage with source+clone memory peak. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 25–27](../../../../../src/io/input_progress.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPositions& InputPositions::operator=(const InputPositions& source) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace accepted positions only after a complete snapshot clone succeeds. |
| inputs / outputs | Self-assignment returns unchanged; otherwise copy into temporary then move-assign. |
| invariants | Failure during copy leaves destination offsets/directory unchanged. |
| ownership | Temporary is funded by source account, not silently rebound to destination account; old destination is then released. |
| failure | Copy phase may throw; final move phase is noexcept. |
| cost | O(N_source+source key bytes+N_old releases); old and new directories overlap until publication. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 28–28](../../../../../src/io/input_progress.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t InputPositions::size() const noexcept {return data_?data_->values.size():0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read directory cardinality, including the inert empty state. |
| inputs / outputs | Returns map size or zero; no mutation. |
| invariants | Cardinality says nothing about source validity/monotonic offsets. |
| ownership | No owner transfer; data_ is only read. |
| failure | noexcept. |
| cost | O(1), no allocation or scan. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 29–33](../../../../../src/io/input_progress.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPositions::const_iterator InputPositions::begin() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a read-only begin iterator for active or inert empty directories. |
| inputs / outputs | Active data_ returns values.begin(); inert state returns the static empty Map begin. |
| invariants | The same static empty sentinel is reached by end() for an inert directory; no default-allocator node is requested. |
| ownership | Iterator borrows the directory or static empty map and retains no backing. |
| failure | noexcept; function-local empty Map initialization contains no node insertion. |
| cost | O(1), no directory scan/allocation. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 34–38](../../../../../src/io/input_progress.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPositions::const_iterator InputPositions::end() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the matching read-only end iterator without manufacturing nodes. |
| inputs / outputs | Active directory uses values.end(); inert directory delegates to begin(). |
| invariants | Empty-state begin/end share the same container sentinel. |
| ownership | Borrowed iterator; directory must survive dereference/iteration. |
| failure | noexcept. |
| cost | O(1), no allocation. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 39–41](../../../../../src/io/input_progress.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPositions::const_iterator InputPositions::find(std::string_view name) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find an accepted source position using transparent borrowed-name comparison. |
| inputs / outputs | string_view name in; const iterator or end out. |
| invariants | Lookup does not validate, copy, insert or advance a source. |
| ownership | Name is borrowed for this call; result borrows Data. |
| failure | No local handler or intentional failure on absence; source must provide valid string_view backing. |
| cost | O(log N) lexicographic key comparisons, worst O(L log N) examined bytes; no key allocation. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 42–44](../../../../../src/io/input_progress.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::uint64_t& InputPositions::at(std::string_view name) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a required accepted offset with ordinary map-style missing-key behavior. |
| inputs / outputs | Borrowed name in; const uint64_t reference out, or out_of_range on absence. |
| invariants | Reference remains valid only while the corresponding directory/node remains alive. |
| ownership | Returns a borrowed scalar reference and does not retain caller name. |
| failure | Missing source throws fixed-message std::out_of_range; ABI exception construction/unwind may allocate. |
| cost | One transparent O(log N) search plus O(1) reference return. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 45–54](../../../../../src/io/input_progress.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputPositions::Prepared InputPositions::prepare(std::string_view name,std::uint64_t offset) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare all fallible storage needed to publish a source offset after an input commits. |
| inputs / outputs | Name/offset in; Prepared holds existing iterator+new scalar or a fully funded detached map node. |
| invariants | Caller already validates name, source-count bound and strictly increasing offset; keep this Data alive and unchanged enough that the iterator is valid and no competing insertion duplicates the prepared new name. |
| ownership | Existing case borrows Data; new case owns a detached node+copied AccountedText until inserted or discarded. |
| failure | Inert data_ throws contract MemoryFailure; find/key/node allocation can fail before accepted map mutation. A failed emplace unwinds local nodes/text. |
| cost | One O(log N) search; existing O(1) extra storage; new O(L) text copy plus one key block/node under original account. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 55–61](../../../../../src/io/input_progress.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void InputPositions::publish(Prepared& prepared) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a previously funded source position without allocating after commit. |
| inputs / outputs | Prepared from this live directory in; links its detached node or writes its saved offset through the iterator. |
| invariants | Use preparations according to their single-owner caller lifecycle; new-name collision or inert data_ is a fatal invariant failure, not a retryable input rejection. |
| ownership | Node ownership transfers to Data; prepared.node_ becomes empty; existing_ remains a borrowed iterator. |
| failure | noexcept; invalid Data or rejected node insertion terminates. Valid caller path has no fallible allocation step. |
| cost | New-node insertion still performs O(log N) key comparisons; existing update O(1). Allocation-free does not mean search-free. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 62–70](../../../../../src/io/input_progress.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool InputPositions::operator==(const std::map<std::string,std::uint64_t>& other) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native positions with a caller-owned ordinary progress map. |
| inputs / outputs | Size mismatch returns false; otherwise compare ordered source bytes and offsets in lockstep. |
| invariants | Both maps use compatible lexicographic source ordering; no source normalization or offset validation occurs. |
| ownership | Both inputs borrowed; no exported strings or shadow map created. |
| failure | No intentional failure branch; valid iteration/backing required. |
| cost | O(N+compared source bytes), early exit on mismatch; no allocation on success or mismatch. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 71–76](../../../../../src/io/input_progress.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputProgress::AccountedInputProgress(const resource::MemoryAccount& account,const InputProgress& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import ordinary InputProgress into an explicitly chosen native funding domain. |
| inputs / outputs | Copies sequence; initializes source_positions(account); prepares/publishes each source name and offset. |
| invariants | Import copies values without proving their semantic validity; actual admission validates source names/counts and progress. Distinct account construction is explicit. |
| ownership | Destination owns fresh Data/nodes/key blocks under supplied account; source remains owned separately. |
| failure | Any allocation fails during private construction, releasing partial directory; source is never mutated. |
| cost | N insertions O(N log N) key comparisons plus total key-byte copies and O(N+bytes) retained native storage. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 77–79](../../../../../src/io/input_progress.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedInputProgress::operator==(const InputProgress& other) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare full native progress with its ordinary diagnostic/export counterpart. |
| inputs / outputs | Returns sequence equality AND source_positions value equality; no mutation. |
| invariants | Equal DTO values do not mint native/catalog or durable replay authority. |
| ownership | Both records borrowed; no ownership conversion. |
| failure | No intentional failure; delegates valid directory traversal. |
| cost | O(1) sequence test then O(N+source bytes) comparison if sequences match. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 80–85](../../../../../src/io/input_progress.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputProgress::AccountedInputProgress(const resource::MemoryAccount& account,const AccountedInputProgress& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import AccountedInputProgress into an explicitly chosen native funding domain. |
| inputs / outputs | Copies sequence; initializes source_positions(account); prepares/publishes each source name and offset. |
| invariants | Import copies values without proving their semantic validity; actual admission validates source names/counts and progress. Distinct account construction is explicit. |
| ownership | Destination owns fresh Data/nodes/key blocks under supplied account; source remains owned separately. |
| failure | Any allocation fails during private construction, releasing partial directory; source is never mutated. |
| cost | N insertions O(N log N) key comparisons plus total key-byte copies and O(N+bytes) retained native storage. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 86–90](../../../../../src/io/input_progress.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputProgress AccountedInputProgress::export_value() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make an explicit independent caller-owned progress DTO. |
| inputs / outputs | Reads sequence/directory; returns InputProgress containing ordinary std::map/std::string copies. |
| invariants | Export is diagnostic/value copying, not a native owner/account transfer or source-admission proof. |
| ownership | Result owns ordinary nodes and source strings; original native directory/account remain intact. |
| failure | Ordinary allocation may fail while local result is built; source unchanged. |
| cost | O(N log N) ordinary map insertion comparisons plus O(total name bytes) copies; source+DTO coexist until caller releases one. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 91–91](../../../../../src/io/input_progress.cpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L91:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [docs/code_specs/files/src/io/input_progress.cpp.md](input_progress.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
