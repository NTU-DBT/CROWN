# `src/io/native_input.hpp` — block usage map

[Source](../../../../../src/io/native_input.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `0d0cf206e1600b86d98cbacd69fb3ac2b4946f1a8142e80ceaa5f7267e9f6937`. 38 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../src/io/native_input.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–14](../../../../../src/io/native_input.hpp#L12) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& account) | calls ; returns resource::MemoryAllocator&lt;T&gt;(account,resource::MemoryPurpose::scratch,memory_owner) · [reviewed contract](#b0002) |
| [B0003 · 15–27](../../../../../src/io/native_input.hpp#L15) | Type/record definition: class Buffer | returns {bytes_.empty()?@ :bytes_.data(),bytes_.size()}; bytes_.size(); growth insert, push_back, reserve; source comment (unverified): // Owns native scratch capacity; view() borrows it and clear() keeps its charge. · [reviewed contract](#b0003) |
| [B0004 · 28–32](../../../../../src/io/native_input.hpp#L28) | Type/record definition: struct Decoded |  · [reviewed contract](#b0004) |
| [B0005 · 33–38](../../../../../src/io/native_input.hpp#L33) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::io::input_detail · [reviewed contract](#b0005) |

## B0001

[Lines 1–11](../../../../../src/io/native_input.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare native-account input scratch, owned decoded backing and physical event/catalog codec entry points. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
template<class T> using Vector=std::vector<T,resource::MemoryAllocator<T>>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the real original-account allocator for internal input arrays. |
| inputs / outputs | Vector&lt;T&gt; aliases std::vector&lt;T,MemoryAllocator&lt;T&gt;&gt;. |
| invariants | Array capacity is funded; nested T allocations are funded only by T implementation, not automatically by the outer vector allocator. |
| ownership | Owning standard vector; copy construction deep-copies elements/capacity under source allocator; move assignment may allocate when nonpropagating allocators differ. |
| failure | Element/allocator allocation and construction can fail; plain alias itself executes nothing. |
| cost | Storage proportional to capacity*sizeof(T) plus account framing and any element-owned payload; teardown destroys elements then capacity. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–14](../../../../../src/io/native_input.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> auto allocator(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a scratch allocator with the shared input/session attribution. |
| inputs / outputs | Valid MemoryAccount in; MemoryAllocator&lt;T&gt;(scratch,session:2) out. |
| invariants | Retains original account identity; does not create a refill or change attribution. |
| ownership | Copies account handle; allocator owns no element array yet. |
| failure | Invalid account/purpose/attribution throws native contract failure during construction. |
| cost | O(1) handle retention/setup, no element allocation until container requests storage. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 15–27](../../../../../src/io/native_input.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Buffer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own growable actual native scratch characters for parsing/encoding. |
| inputs / outputs | Account constructor establishes an empty Vector&lt;char&gt;; methods expose borrowed view or append/clear/reserve bytes. |
| invariants | No terminator promise; view length is exact size. clear preserves funded capacity. Copy is an owning deep vector copy; unequal-account assignment can allocate. |
| ownership | bytes_ owns actual capacity under account/scratch/session:2; views retain no backing. Last destruction releases capacity/account handle. |
| failure | Allocator or growth failure propagates; no blanket nonallocating/never-throwing claim for this owning Buffer. |
| cost | O(capacity) native storage; append/push growth amortized, reserve may copy existing size; view/size/clear constant work for char elements. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
explicit Buffer(const resource::MemoryAccount& account):bytes_(allocator<char>(account)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create empty character scratch funded by the supplied native account. |
| inputs / outputs | Valid account in; empty bytes_ with matching allocator out. |
| invariants | Constructor does not reserve or consume a byte-array request. |
| ownership | Retains account handle through allocator; no character ownership yet. |
| failure | Invalid allocator contract rejects immediately. |
| cost | O(1), no character allocation. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
[[nodiscard]] std::string_view view() const noexcept {return {bytes_.empty()?"":bytes_.data(),bytes_.size()};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow current bytes safely even for an empty vector. |
| inputs / outputs | Returns string_view(data,size) or static empty bytes. |
| invariants | View can expire after append/push/reserve that reallocates, clear, move/assignment/destruction. |
| ownership | No owner retention or copied characters. |
| failure | noexcept; caller must respect backing lifetime. |
| cost | O(1), no allocation. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
[[nodiscard]] std::size_t size() const noexcept {return bytes_.size();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current scratch logical byte length. |
| inputs / outputs | Returns bytes_.size(); no mutation. |
| invariants | Length excludes spare capacity and account framing. |
| ownership | Inline result only. |
| failure | noexcept. |
| cost | O(1), no scan/allocation. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
void append(std::string_view value) {bytes_.insert(bytes_.end(),value.begin(),value.end());}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append a borrowed byte range into owned native scratch. |
| inputs / outputs | string_view in; bytes_.insert appends its character range. |
| invariants | Input range must remain valid during insertion and not be invalidated by aliased reallocation; codec callers append distinct/static/token sources. |
| ownership | Copies bytes into account-funded vector; new capacity overlaps old capacity during growth. |
| failure | Length/account/OOM failures propagate; no catch or semantic validation. |
| cost | O(input bytes) plus up to O(existing size) relocation when capacity grows; allocation depends on spare capacity. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
void push_back(char value) {bytes_.push_back(value);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one byte to native parsing scratch. |
| inputs / outputs | char in; vector size increases by one. |
| invariants | No UTF8/field/record validation implied by a successful append. |
| ownership | Owns appended byte under vector allocator/account. |
| failure | Capacity growth can fail through length/account/OOM errors. |
| cost | Amortized O(1), occasional O(size) relocation/native capacity request. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
void reserve(std::size_t size) {bytes_.reserve(size);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare native scratch capacity before a bounded codec operation. |
| inputs / outputs | Requested size in; vector reserve may grow capacity but leaves logical size unchanged. |
| invariants | No shrink and no semantic limit check performed here. |
| ownership | New capacity funded under existing allocator; old/new capacity can coexist until transfer completes. |
| failure | Length/account/OOM failure propagates and existing byte content remains usable for char vector. |
| cost | O(size_current) if growth is needed, O(1) otherwise; storage up to actual reserved capacity. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
void clear() noexcept {bytes_.clear();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset token contents while keeping reusable charged capacity. |
| inputs / outputs | clear() sets bytes_ size to zero. |
| invariants | Not a capacity release or account refund; outstanding logical views must not be reused. |
| ownership | Buffer retains vector allocation/account. |
| failure | noexcept for char destruction. |
| cost | O(1) for trivial char elements; future growth may reuse capacity. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
Vector<char> bytes_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the real character-array allocation rather than an unaccounted string mirror. |
| inputs / outputs | Private Vector&lt;char&gt; used by all Buffer methods. |
| invariants | Capacity/request framing belong to the allocator/account established at construction. |
| ownership | Owning vector, deep-copy semantics and allocator-sensitive move assignment; view() borrows it. |
| failure | Allocation on growth/copy may fail; final release is native deallocation. |
| cost | capacity*sizeof(char) plus account overhead; copy O(size), teardown O(1) character destruction plus deallocation. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 28–32](../../../../../src/io/native_input.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Decoded {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tie decoded physical input views to the exact native row/source backing that owns their payload. |
| inputs / outputs | Decoded owns AccountedRow and AccountedText; event fields point into those after Builder::finish/source attachment. |
| invariants | Event remains usable while matching row/source are alive. Move transfers heap backing without rebasing its bytes; moved-from event views must not be consumed. AccountedRow makes deep implicit copying unavailable. |
| ownership | Real native row/source blocks, not the input string/JSON DOM; event itself borrows those blocks and retains no additional owner. |
| failure | Decoder allocation/validation can fail before returning a complete Decoded; partial blocks unwind. No native runtime publication occurs here. |
| cost | O(row fields+text bytes) native payload storage; parse scratch plus frozen payload overlap during finish, move transfers owners. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
storage::AccountedRow row;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the decoded compact row used by event.update.values. |
| inputs / outputs | Builder explicitly copy_of freezes scalar views into an AccountedRow. |
| invariants | Row is move-only; borrowed scalar backing survives decoder scratch release because payload is copied. |
| ownership | Actual original-account row metadata/cell/text block ownership. |
| failure | copy_of can fail before event is admitted; destruction releases actual row blocks. |
| cost | O(fields+string bytes) freeze/copy and retained payload; no ordinary Row mirror. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
resource::AccountedText source;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the source identity used by decoded optional metadata. |
| inputs / outputs | AccountedText is explicitly copied/moved into Decoded when source_position exists. |
| invariants | event.source_position source view must reference this exact owned block. |
| ownership | Original-account character block; AccountedText copy would deep-clone but Decoded row prevents ordinary implicit aggregate copy. |
| failure | Source character allocation can fail before complete decode return. |
| cost | O(source bytes) copy/storage; moves transfer existing block. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
InputEventView event;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the decoded scalar envelope and views into its sibling native owners. |
| inputs / outputs | InputEventView holds sequence/table/operation/values and optional source position. |
| invariants | No independent checked/accepted status follows from public fields; full validation precedes decoder return and source acceptance remains separate. |
| ownership | Borrowed values/source only in this construction; retains no input text backing. |
| failure | Constructing views is fixed/nonallocating; consuming stale moved-from event is caller misuse. |
| cost | O(1) fields/views; native owned row/source cost belongs to siblings. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 33–38](../../../../../src/io/native_input.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Decoded decode_json(const resource::MemoryAccount&,std::string_view,const CatalogSource&,const InputLimits&,std::string_view);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one complete JSON physical record into original-account owned native backing. |
| inputs / outputs | Account/text/CatalogSource/InputLimits/expected catalog fingerprint in; Decoded out after native_decode.cpp parsing, binding and typed-row validation. |
| invariants | CatalogSource must hold admitted immutable program catalog or already-validated standalone schema; expected fingerprint must match that source. Does not enforce stream sequence/offset order. |
| ownership | Input/schema/fingerprint borrowed during call; result owns compact row/source. Token/cell/value arrays use account-funded scratch; no general JSON DOM. |
| failure | Syntax/version/binding/envelope/row/limit/native OOM failures propagate before return. Fullrow validation occurs after frozen payload allocation, so rejection may still have incurred that work. |
| cost | O(record bytes+linear table-name lookup+row field/payload freeze and validation); scratch and frozen strings can overlap. JSON token scratch can approach record_bytes before field_bytes acceptance. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
[[nodiscard]] Decoded decode_binary(const resource::MemoryAccount&,std::string_view,const CatalogSource&,const InputLimits&,std::string_view);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one complete binary physical record into original-account owned native backing. |
| inputs / outputs | Account/text/CatalogSource/InputLimits/expected catalog fingerprint in; Decoded out after native_decode.cpp parsing, binding and typed-row validation. |
| invariants | CatalogSource must hold admitted immutable program catalog or already-validated standalone schema; expected fingerprint must match that source. Does not enforce stream sequence/offset order. |
| ownership | Input/schema/fingerprint borrowed during call; result owns compact row/source. Token/cell/value arrays use account-funded scratch; no general JSON DOM. |
| failure | Syntax/version/binding/envelope/row/limit/native OOM failures propagate before return. Fullrow validation occurs after frozen payload allocation, so rejection may still have incurred that work. |
| cost | O(record bytes+linear table-name lookup+row field/payload freeze and validation); scratch and frozen strings can overlap. JSON token scratch can approach record_bytes before field_bytes acceptance. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
[[nodiscard]] resource::AccountedText catalog_fingerprint(const resource::MemoryAccount&,const CatalogSource&,bool admitted);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash the complete catalog binding into retained native fingerprint text. |
| inputs / outputs | Account/CatalogSource/admitted flag in; AccountedText containing64 lowercase hash bytes out. |
| invariants | admitted=true is internal caller authority to skip standalone catalog validation, not a user DTO flag. Full canonical schema still serialized/hashed. |
| ownership | Account-funded Buffer owns canonical byte scratch; result owns64-byte text+terminator under immutable_metadata/session:2. admitted=false also invokes public catalog validation with ordinary set/string/diagnostic scratch. |
| failure | Invalid source, catalog validation or account/OOM failure propagates before returned fingerprint. |
| cost | O(canonical catalog bytes) serialization+SHA256 and scratch capacity, plus validation if not admitted; hash text has its actual native allocation. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
[[nodiscard]] std::array<char,64> catalog_digest(const resource::MemoryAccount&,const Catalog&,bool admitted);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a fixed digest of Catalog using native scratch. |
| inputs / outputs | Account/schema/admitted in; array&lt;char,64&gt; digest out. |
| invariants | Only validated/retained admitted schema permits skip of catalog validation; no schema authority is created by a hash label. |
| ownership | Schema borrowed; account-funded canonical Buffer is temporary, result is inline64-byte value. admitted=false additionally allocates ordinary catalog name/column/constraint sets and eager diagnostic text. |
| failure | Catalog/native scratch/OOM failure propagates; no retained text block result. |
| cost | O(canonical schema bytes) serialization+hash and scratch capacity, plus standalone validation when admitted=false. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
[[nodiscard]] std::array<char,64> catalog_digest(const resource::MemoryAccount&,const program::Catalog&,bool admitted);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a fixed digest of program::Catalog using native scratch. |
| inputs / outputs | Account/schema/admitted in; array&lt;char,64&gt; digest out. |
| invariants | Only validated/retained admitted schema permits skip of catalog validation; no schema authority is created by a hash label. |
| ownership | Schema borrowed; account-funded canonical Buffer is temporary, result is inline64-byte value. admitted=false additionally allocates ordinary catalog name/column/constraint sets and eager diagnostic text. |
| failure | Catalog/native scratch/OOM failure propagates; no retained text block result. |
| cost | O(canonical schema bytes) serialization+hash and scratch capacity, plus standalone validation when admitted=false. |
| Design | [src/io/native_input.hpp](../../../../../src/io/native_input.hpp), [src/io/native_decode.cpp](../../../../../src/io/native_decode.cpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/io/catalog_source.hpp](../../../../../include/crown/io/catalog_source.hpp), [docs/code_review.md](../../../../code_review.md) |
