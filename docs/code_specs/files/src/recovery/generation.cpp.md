# `src/recovery/generation.cpp` — block usage map

[Source](../../../../../src/recovery/generation.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Read/publish durable generation roots with exact identity and selection outcome.

Snapshot SHA-256: `d45af59fef4bc832377e9a0441a05fc34e1ac9532857b5713a5f4d77fb97e540`. 346 lines partitioned into 39 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../src/recovery/generation.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 19–19](../../../../../src/recovery/generation.cpp#L19) | Callable definition: void set_generation_hook(GenerationHook value,void* context) noexcept | calls  · [reviewed contract](#b0002) |
| [B0003 · 20–22](../../../../../src/recovery/generation.cpp#L20) | controls preprocessing; declares namespace scope. |  · [reviewed contract](#b0003) |
| [B0004 · 23–25](../../../../../src/recovery/generation.cpp#L23) | Callable definition: \[\[noreturn\]\] void fail(GenerationFault fault,GenerationStage stage,GenerationOutcome outcome,int error=0) | calls GenerationFailure · [reviewed contract](#b0004) |
| [B0005 · 26–28](../../../../../src/recovery/generation.cpp#L26) | Callable definition: bool hex(std::string_view value) | calls std::all_of, begin, end; returns std::all_of(value.begin(),value.end(),\[\](char c){return (c&gt;=@ && c&lt;=@ ) \|\| (c&gt;=@ && c&lt;=@ ) · [reviewed contract](#b0005) |
| [B0006 · 29–34](../../../../../src/recovery/generation.cpp#L29) | Callable definition: bool valid(const GenerationRoot& root) | calls hex, data, size; returns hex({root.query_id.data(),root.query_id.size()}) && hex({root.checkpoint_sha256.data(),root.checkpo… · [reviewed contract](#b0006) |
| [B0007 · 35–39](../../../../../src/recovery/generation.cpp#L35) | Callable definition: bool same(const struct stat& a,const struct stat& b) | calls ; returns a.st_dev==b.st_dev && a.st_ino==b.st_ino && a.st_size==b.st_size && · [reviewed contract](#b0007) |
| [B0008 · 40–42](../../../../../src/recovery/generation.cpp#L40) | Callable definition: template&lt;std::size_t N&gt; void put(std::array&lt;char,N&gt;& bytes,std::size_t& offset,std::uint64_t value,unsigned width) | calls ; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 43–45](../../../../../src/recovery/generation.cpp#L43) | Callable definition: std::uint64_t get(std::string_view bytes,std::size_t& offset,unsigned width) | calls std::uint64_t; returns value; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 46–46](../../../../../src/recovery/generation.cpp#L46) | Type/record definition: struct RootBytes |  · [reviewed contract](#b0010) |
| [B0011 · 47–60](../../../../../src/recovery/generation.cpp#L47) | Callable definition: RootBytes encode(const GenerationRoot& root) | calls valid, fail, std::copy, begin; returns result · [reviewed contract](#b0011) |
| [B0012 · 61–64](../../../../../src/recovery/generation.cpp#L61) | Callable definition: std::array&lt;char,16&gt; generation_hex(std::uint64_t generation) | calls fill, std::to_chars, data, size; returns result · [reviewed contract](#b0012) |
| [B0013 · 65–65](../../../../../src/recovery/generation.cpp#L65) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0013) |
| [B0014 · 66–89](../../../../../src/recovery/generation.cpp#L66) | Callable definition: GenerationRoot inspect_generation_root(std::string_view bytes) | calls size, fail, sha256_fixed, substr; returns result · [reviewed contract](#b0014) |
| [B0015 · 90–91](../../../../../src/recovery/generation.cpp#L90) | declares namespace scope. |  · [reviewed contract](#b0015) |
| [B0016 · 92–117](../../../../../src/recovery/generation.cpp#L92) | Callable definition: GenerationOwner::GenerationOwner(std::string_view path,const std::array&lt;char,32&gt;& query,bool create,GenerationLimits limits) :lim… | calls limits_, query_id_, size, max · [reviewed contract](#b0016) |
| [B0017 · 118–124](../../../../../src/recovery/generation.cpp#L118) | Callable definition: GenerationOwner::GenerationOwner(GenerationOwner&& other) noexcept :limits_(other.limits_),root_path_(other.root_path_),root_name… | calls limits_, root_path_, root_name_, selected_ · [reviewed contract](#b0017) |
| [B0018 · 125–128](../../../../../src/recovery/generation.cpp#L125) | Callable definition: void GenerationOwner::consume_work(std::uint64_t amount) | calls fail · [reviewed contract](#b0018) |
| [B0019 · 129–131](../../../../../src/recovery/generation.cpp#L129) | Callable definition: void GenerationOwner::healthy() const | calls fail · [reviewed contract](#b0019) |
| [B0020 · 132–182](../../../../../src/recovery/generation.cpp#L132) | Callable definition: std::int64_t GenerationOwner::call(GenerationStage stage,std::size_t requested,int fd,const char* name, const char* other_name,vo… | calls close, fail, defined, testing::hook; returns result · [reviewed contract](#b0020) |
| [B0021 · 183–191](../../../../../src/recovery/generation.cpp#L183) | Callable definition: std::int64_t GenerationOwner::checked(GenerationStage stage,std::size_t count,int fd,const char* name,const char* other_name,void… | calls call, fail; returns result; 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 192–199](../../../../../src/recovery/generation.cpp#L192) | Callable definition: void GenerationOwner::transfer(bool write,int fd,char* data,std::size_t size,std::uint64_t offset) | calls checked, std::min, fail; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 200–221](../../../../../src/recovery/generation.cpp#L200) | Callable definition: GenerationRoot GenerationOwner::read_root(bool missing_ok,bool adopt) | calls call, get, data, fail; returns {}; result; 2 loop sites · [reviewed contract](#b0023) |
| [B0024 · 222–225](../../../../../src/recovery/generation.cpp#L222) | Callable definition: std::array&lt;char,4096&gt; GenerationOwner::path(std::uint64_t generation,std::string_view suffix) const | calls root, data, generation_hex, begin; returns result · [reviewed contract](#b0024) |
| [B0025 · 226–229](../../../../../src/recovery/generation.cpp#L226) | Callable definition: std::array&lt;char,256&gt; GenerationOwner::name(std::uint64_t generation,std::string_view suffix) const | calls root, data, generation_hex, begin; returns result · [reviewed contract](#b0025) |
| [B0026 · 230–230](../../../../../src/recovery/generation.cpp#L230) | Callable definition: std::array&lt;char,4096&gt; GenerationOwner::checkpoint_path(std::uint64_t generation) const | calls path; returns path(generation,@ ) · [reviewed contract](#b0026) |
| [B0027 · 231–231](../../../../../src/recovery/generation.cpp#L231) | Callable definition: std::array&lt;char,4096&gt; GenerationOwner::journal_path(std::uint64_t generation) const | calls path; returns path(generation,@ ) · [reviewed contract](#b0027) |
| [B0028 · 232–232](../../../../../src/recovery/generation.cpp#L232) | Callable definition: std::array&lt;char,4096&gt; GenerationOwner::plan_path(std::uint64_t generation) const | calls path; returns path(generation,@ ) · [reviewed contract](#b0028) |
| [B0029 · 233–245](../../../../../src/recovery/generation.cpp#L233) | Callable definition: void GenerationOwner::prepare_next(std::uint64_t generation) | calls healthy, has_selection, fail, read_root; 2 loop sites; source comment (unverified): // Only the immediate unselected checkpoint/WAL/plan candidate names may · [reviewed contract](#b0029) |
| [B0030 · 246–248](../../../../../src/recovery/generation.cpp#L246) | Callable definition: bool GenerationOwner::cleanup_temporary(const char* name) noexcept | calls call, get; returns true; false; 1 loop sites · [reviewed contract](#b0030) |
| [B0031 · 249–274](../../../../../src/recovery/generation.cpp#L249) | Callable definition: void GenerationOwner::publish(std::string_view bytes,const char* destination,bool replace,bool selection) | calls size, checked, data, fail; 5 loop sites; source comment (unverified): // Private candidate publication does not select a root. Root link/rename · [reviewed contract](#b0031) |
| [B0032 · 275–282](../../../../../src/recovery/generation.cpp#L275) | Callable definition: void GenerationOwner::publish_checkpoint(std::uint64_t generation,std::string_view bytes) | calls healthy, has_selection, fail, size · [reviewed contract](#b0032) |
| [B0033 · 283–291](../../../../../src/recovery/generation.cpp#L283) | Callable definition: void GenerationOwner::publish_plan(std::uint64_t generation,std::string_view bytes) | calls healthy, empty, has_selection, fail · [reviewed contract](#b0033) |
| [B0034 · 292–294](../../../../../src/recovery/generation.cpp#L292) | Callable definition: ImageVector&lt;char&gt; GenerationOwner::read_plan(const resource::MemoryAccount& account) | calls read_selected; returns read_selected(account,true) · [reviewed contract](#b0034) |
| [B0035 · 295–297](../../../../../src/recovery/generation.cpp#L295) | Callable definition: ImageVector&lt;char&gt; GenerationOwner::read_checkpoint(const resource::MemoryAccount& account) | calls read_selected; returns read_selected(account,false) · [reviewed contract](#b0035) |
| [B0036 · 298–322](../../../../../src/recovery/generation.cpp#L298) | Callable definition: ImageVector&lt;char&gt; GenerationOwner::read_selected(const resource::MemoryAccount& account,bool plan) | calls healthy, has_selection, fail, read_root; returns bytes; growth resize; source comment (unverified): // Both selected files use the same lock/root/stamp/EOF discipline. Selection · [reviewed contract](#b0036) |
| [B0037 · 323–336](../../../../../src/recovery/generation.cpp#L323) | Callable definition: void GenerationOwner::publish_root(const GenerationRoot& next) | calls healthy, has_selection, fail, encode; source comment (unverified): // Select only privately bound durable candidates. All throwing account · [reviewed contract](#b0037) |
| [B0038 · 337–344](../../../../../src/recovery/generation.cpp#L337) | Callable definition: void GenerationOwner::select_retirement_floor() | calls fail, encode, consume_work, publish · [reviewed contract](#b0038) |
| [B0039 · 345–346](../../../../../src/recovery/generation.cpp#L345) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0039) |

## B0001

[Lines 1–18](../../../../../src/recovery/generation.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "generation_detail.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble generation root codec and single-root Linux publication authority. |
| inputs / outputs | Private generation/retirement owner, SHA helper, Linux calls and thread-local hooks guarded by either the full runtime-testing macro or the separate concrete-generation-I/O testing macro. |
| invariants | Root selection authority is local durable engineering, not a paper theorem. Trusted parent/stable lock sentinel and cooperating API writers are required. The five widened guards affect test code only; production statements and GenerationOwner data layout remain unchanged. |
| ownership | Fixed declarations create no query account or descriptor owner. |
| failure | No dynamic I/O, allocation or exception boundary in setup declarations. |
| cost | No production runtime work for declarations; fault hooks are testing-only. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–19](../../../../../src/recovery/generation.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set_generation_hook(GenerationHook value,void* context) noexcept {hook=value;hook_context=context;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the current thread's test generation-syscall hook. |
| inputs / outputs | GenerationHook and opaque context replace thread-local callback pair. |
| invariants | Compiled only under CROWN_RUNTIME_TESTING or the concrete-I/O-only CROWN_GENERATION_FILE_TESTING. The owner of the borrowed context restores/unsets the thread-local hook before teardown. |
| ownership | Borrows context; owns no fd or query account. |
| failure | noexcept fixed assignments; no callback invoked here. |
| cost | Two test-only TLS writes. Both hook guards are absent from production; the file-only macro adds no layout-sensitive runtime work-context fields. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0003

[Lines 20–22](../../../../../src/recovery/generation.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L22:sha256:2cdf9576c15c73a8f4ece08282d4cdd2a44bb5fb31869defd3a37f40b7b45aed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the CROWN_GENERATION_FILE_TESTING hook scope and preprocessor guard, then opens the anonymous namespace for production generation-file helpers. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | Only the CROWN_GENERATION_FILE_TESTING-enabled build sees the preceding thread-local test hook; the following anonymous-namespace helpers are compiled for the file implementation. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | The preprocessor guard does not catch filesystem errors. Later checked file operations preserve their declared stage/outcome failure carriers. |
| cost | Preprocessor/scope boundary only; test hook code is not present when its testing macro is absent. |
| Design | [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/code_specs/files/src/recovery/generation.cpp.md](generation.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0004

[Lines 23–25](../../../../../src/recovery/generation.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void fail(GenerationFault fault,GenerationStage stage,GenerationOutcome outcome,int error=0) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise fixed stage/outcome metadata for a generation operation failure. |
| inputs / outputs | GenerationFault, Stage, root-selection Outcome and native errno construct GenerationFailure. |
| invariants | Outcome concerns authoritative root selection, not whether an unselected candidate/temp/lock name exists. |
| ownership | Fixed enums/errno/flags only; no message allocation or query state. |
| failure | Throws to factory/session/publication boundary; no rollback action inside helper. |
| cost | Fixed failure object; called only on failure. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0005

[Lines 26–28](../../../../../src/recovery/generation.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool hex(std::string_view value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate lowercase hexadecimal metadata bytes. |
| inputs / outputs | string_view returns true iff every character is ASCII0-9/a-f; private fixed-width callers separately supply field lengths. |
| invariants | Empty span is vacuously true; this helper does not validate length or authenticate the value. |
| ownership | Borrows input for this scan. |
| failure | No allocation or exception for a readable view. |
| cost | O(view bytes) comparisons, no hash/syscall. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0006

[Lines 29–34](../../../../../src/recovery/generation.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool valid(const GenerationRoot& root) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check decoded/constructed root field invariants before encode or acceptance. |
| inputs / outputs | GenerationRoot requires fixed IDs/digests lowercase hex, positive first_generation&lt;=generation, optional plan hash valid and optional delivery sequence equal physical_sequence with positive byte count. |
| invariants | Checks structure/binding shape, not actual checkpoint/sink contents or permission to mutate/retire. Public inspection remains descriptive. |
| ownership | Borrows inline root fields and returns Boolean. |
| failure | No filesystem effect or allocation; encode/inspect decide the fixed error category. |
| cost | Fixed-size field scans, at most bounded root payload width. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0007

[Lines 35–39](../../../../../src/recovery/generation.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same(const struct stat& a,const struct stat& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare root/plan file identity and change-sensitive stat fields. |
| inputs / outputs | Device/inode/size/mtime/ctime incl nanoseconds must match. |
| invariants | Used with exact EOF/hash checks inside trusted stable namespace; not an adversarial race-proof filesystem snapshot. |
| ownership | Borrows fixed records. |
| failure | No syscall or exception inside comparator. |
| cost | Constant field comparisons. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0008

[Lines 40–42](../../../../../src/recovery/generation.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t N> void put(std::array<char,N>& bytes,std::size_t& offset,std::uint64_t value,unsigned width) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one fixed-format unsigned integer in little-endian root storage. |
| inputs / outputs | Private fixed array, offset, U64 and width&lt;=8 append width bytes and advance offset. |
| invariants | Callers use compile-time layout sizes/widths and prevalidated root variant; this internal helper does not add per-byte bounds checks. |
| ownership | Writes only stack-owned codec bytes; retains no source. |
| failure | No throw for its admitted bounded buffer/width domain; invalid private dimensions are outside contract. |
| cost | O(width), at most eight stores, no heap/syscall. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0009

[Lines 43–45](../../../../../src/recovery/generation.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t get(std::string_view bytes,std::size_t& offset,unsigned width) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one fixed-format little-endian integer from an admitted root view. |
| inputs / outputs | Readable bytes, offset and width&lt;=8 produce U64 and advance offset. |
| invariants | inspect_generation_root establishes exact legal frame length/variant before fixed-field reads. No user-supplied arbitrary width reaches this helper. |
| ownership | Borrows bytes; returns inline integer. |
| failure | No allocation/error translation for valid private range; enclosing inspector checks layout/end. |
| cost | At most eight shifts/loads. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0010

[Lines 46–46](../../../../../src/recovery/generation.cpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RootBytes {std::array<char,generation_root_plan_delivery_size> bytes{};std::size_t size=generation_root_size;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry encoded root variants on the stack without a heap buffer. |
| inputs / outputs | Fixed array holds largest v3+delivery root; size defaults v1 and encoder selects actual212/324/276/388 bytes. |
| invariants | Only bytes\[0:size\] are published and hashed; inactive capacity is not wire payload. |
| ownership | Owns fixed array and length locally. |
| failure | Initialization does not allocate or access filesystem. |
| cost | 388-byte array plus size field; bounded initialization. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0011

[Lines 47–60](../../../../../src/recovery/generation.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RootBytes encode(const GenerationRoot& root) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode and checksum an admitted v1/v2/v3 generation selection. |
| inputs / outputs | GenerationRoot passes valid(), selects variant/flags/length, writes exact fixed fields, optional delivery/plan hash and ASCII64 SHA256 of preceding bytes. |
| invariants | CROWNGR1 fixed wire shape; root metadata/hash is descriptive until privately published under GenerationOwner. Checksums detect corruption in trusted namespace, not signatures. |
| ownership | Stack RootBytes and fixed SHA result; no query account or serialized ordinary string allocated. |
| failure | Invalid fields raise corrupt/state/unchanged before publication; caller separately charges selected encoded length work. |
| cost | O(root variant bytes) fixed copies/hash; bounded at388 bytes. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0012

[Lines 61–64](../../../../../src/recovery/generation.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,16> generation_hex(std::uint64_t generation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Format a U64 generation as sixteen lowercase hexadecimal filename digits. |
| inputs / outputs | Zero-filled fixed arrays plus to_chars(base16) right-align the minimal hexadecimal digits. |
| invariants | Sixteen bytes fit every U64, so private conversion range cannot overflow buffer; no NUL terminator is returned/needed for this segment. |
| ownership | Returns owning fixed array; no borrowed string or allocator. |
| failure | No filesystem action or dynamic error path in this admitted integer domain. |
| cost | At most sixteen formatted/copied bytes. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0013

[Lines 65–65](../../../../../src/recovery/generation.cpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L65:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/code_specs/files/src/recovery/generation.cpp.md](generation.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0014

[Lines 66–89](../../../../../src/recovery/generation.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GenerationRoot inspect_generation_root(std::string_view bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect a complete checksummed generation root without granting owner authority. |
| inputs / outputs | Exact legal212/324/276/388-byte string_view validates magic/hash/version/flags/body shape, decodes fields and checks final offset/valid(). |
| invariants | Truncated, extra/malformed or bad-checksum data rejects. Query ID match to a caller and actual checkpoint/plan/sink validation are later owner/factory obligations. |
| ownership | Returns owning inline GenerationRoot with optional fixed arrays; retains no bytes/fd/lock. |
| failure | Fixed GenerationFailure(corrupt/truncated,read_data,unchanged); no repair or mutation. |
| cost | Bounded root copy/hash/field scan, at most388 bytes, no heap allocation. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0015

[Lines 90–91](../../../../../src/recovery/generation.cpp#L90); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L91:sha256:2fb1ccd015c87682509518c26fbecd92ee36bceb2639519b495621d9e1628745
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Opens the internal generation detail namespace for GenerationOwner implementation methods declared in the companion private header. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/code_specs/files/src/recovery/generation.cpp.md](generation.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0016

[Lines 92–117](../../../../../src/recovery/generation.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GenerationOwner::GenerationOwner(std::string_view path,const std::array<char,32>& query,bool create,GenerationLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit stable root namespace and lock ownership before selected generation recovery/publication. |
| inputs / outputs | Root path,32-byte hex query ID, create flag and limits validate fixed path capacity/derived-name room/chunk/off_t domains, open trusted parent and regular no-follow lock sentinel, flock+sync lock/parent, read/adopt root and inspect pending retirement. |
| invariants | Lock sentinel/name and parent must remain stable. create permits missing root but rejects existing selection. Root lock persists across selected pair reconstruction and uncertainty; no fallback directory/candidate guessing. |
| ownership | Fixed arrays on owner/stack; FileDescriptor members own parent and lock and close automatically if construction fails. Root bytes/selected metadata are inline; no query heap account here. |
| failure | Invalid path/limits/query, busy/type/I/O/hash/binding/retirement failure unwinds only owned descriptors. Lock sentinel creation may persist although root-selection Outcome remains unchanged. |
| cost | O(path bytes) fixed copies, open/stat/flock/file+directory fsync, bounded root and retirement reads/hash; no native reconstruction or directory listing in this constructor. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp) |

## B0017

[Lines 118–124](../../../../../src/recovery/generation.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GenerationOwner::GenerationOwner(GenerationOwner&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move the unique root namespace/lock authority without another filesystem operation. |
| inputs / outputs | Moves fixed selected/retirement/query/candidate/counter/outcome state; releases source directory/lock into destination and clears source selected root. |
| invariants | No duplicate advisory lock authority or new allowance; moved-from owner is not usable for generation operations. |
| ownership | FileDescriptor.reset/release transfer existing fds; copies only fixed metadata arrays/options. |
| failure | noexcept; no allocation, reopening, fsync or retry. |
| cost | Fixed metadata copy and two fd transfers. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp) |

## B0018

[Lines 125–128](../../../../../src/recovery/generation.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::consume_work(std::uint64_t amount) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge extra generation validation/encoding units cumulatively. |
| inputs / outputs | Amount increments work_ iff it fits limits_.validation_work-work_. |
| invariants | Counter starts within cap and never refunds/refills. Declared units are separate from actual byte copies, SHA passes, I/O attempts and native checkpoint validation. |
| ownership | One scalar owner counter only. |
| failure | Fixed limit/state/current-outcome failure before over-cap addition. |
| cost | Constant checked arithmetic. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0019

[Lines 129–131](../../../../../src/recovery/generation.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::healthy() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject reuse after an attempted but unresolved authoritative root selection. |
| inputs / outputs | attempted_ true raises state failure; otherwise returns. |
| invariants | Once root link/rename is admitted, old owner cannot blindly continue until successful publication clears attempted_ or owner is released/reopened. |
| ownership | Reads private selection-authority flag; no runtime row or metadata export. |
| failure | Fixed state failure preserving current root-selection outcome. |
| cost | Constant branch, no syscall. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0020

[Lines 132–182](../../../../../src/recovery/generation.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int64_t GenerationOwner::call(GenerationStage stage,std::size_t requested,int fd,const char* name,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch one finite generation syscall attempt with root-selection uncertainty. |
| inputs / outputs | Stage/target, fd/name/buffer/offset/request drive open/lock/stat/read/write/sync/create/link/rename/unlink/close; result plus errno returned. |
| invariants | Attempt counter includes interruptions; temp cleanup bypasses ordinary cap only. Before root-target link or any rename_root call, outcome becomes unknown and attempted_=true. Candidate write/link does not itself change root outcome. Close is executed once even on budget rejection. Test after-open errors become before-open to avoid hidden fd leaks. Only the explicit emergency_cleanup flag from the eight-attempt failure helper bypasses the ordinary operation cap; normal post-link unlink/EINTR does not. |
| ownership | Borrows buffers/names for call; callers promptly wrap returned fds in FileDescriptor. Fixed dispatcher owns no payload. |
| failure | Fixed limit/state exceptions or errno/result; no rollback/retry here. Testing hook can inject short/error/zero-entropy behavior only in testing builds. |
| cost | One syscall plus constant dispatch; selected byte/request and attempt bounds do not bound kernel/fsync latency. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [tests/unit/file_cleanup_quota_test.cpp](../../../../../tests/unit/file_cleanup_quota_test.cpp) |

```text
if(stage==GenerationStage::rename_root || (stage==GenerationStage::link_file && target_==GenerationTarget::root)) {outcome_=GenerationOutcome::unknown;attempted_=true;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Latch authoritative selection uncertainty before root namespace mutation. |
| inputs / outputs | Admitting root rename/link sets root outcome unknown and attempted flag before real syscall or injected error. |
| invariants | Candidate/private inode writes do not select a root; root syscall failure/EINTR may still have changed the named selection. Only successful durable selection or a fresh reopened owner resolves this. |
| ownership | Mutates fixed owner authority fields while root lock stays owned. |
| failure | No catch clears the latch on failure; upper session retains recovery-required ownership until drop/reopen. |
| cost | Two scalar writes on root publication path, no allocation/extra filesystem operation. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0021

[Lines 183–191](../../../../../src/recovery/generation.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int64_t GenerationOwner::checked(GenerationStage stage,std::size_t count,int fd,const char* name,const char* other_name,void* buffer,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retry only safe interrupted generation operations and preserve publication ambiguity. |
| inputs / outputs | checked loops call until result&gt;=0, retrying EINTR except close,link_file,rename_root; flock EWOULDBLOCK/EAGAIN maps busy. |
| invariants | Root link/rename are never retried or assumed undone. All retries share one finite operations counter. |
| ownership | No new fd/buffer owner inside wrapper; caller owns call arguments. |
| failure | GenerationFailure preserves stage/current selection outcome/errno; no source/native state rollback. |
| cost | One syscall per iteration, capped by operations except bounded cleanup helper. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0022

[Lines 192–199](../../../../../src/recovery/generation.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::transfer(bool write,int fd,char* data,std::size_t size,std::uint64_t offset) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer generation checkpoint/plan/root bytes over bounded short positional I/O. |
| inputs / outputs | Owned fd, readable/writable buffer, size and admitted offset loop pread/pwrite chunks until complete. |
| invariants | Caller supplies dimensions within path/file/off_t policies; zero progress is io/EIO for write or truncated for read. |
| ownership | Synchronous borrowed bytes, no copied heap buffer or new account. |
| failure | Syscall/limit failures propagate; partial temporary/candidate bytes do not themselves select a root. |
| cost | O(bytes) kernel traffic and chunk count plus bounded EINTR retries. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0023

[Lines 200–221](../../../../../src/recovery/generation.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GenerationRoot GenerationOwner::read_root(bool missing_ok,bool adopt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and optionally adopt exactly the currently named root under the root lock. |
| inputs / outputs | missing_ok may accept ENOENT as empty selection; otherwise opens no-follow root, checks regular exact variant length, reads fixed bytes, exact EOF/stamp, root codec/query binding, and optionally fsyncs file+directory. |
| invariants | No discovery from old files/temporaries. adopt marks root outcome durable only after both syncs; false performs validation without asserting new durability. |
| ownership | Temporary FileDescriptor and fixed&lt;=388-byte buffer; returns inline selected root, not lock authority. |
| failure | Type/size/hash/query/changed/limit/I/O failure propagates and closes temporary fd. Missing_ok affects only ENOENT. |
| cost | Bounded root reads/hash, two stat checks, EOF probe and checked close; adopt adds two fsyncs. Declared work charges2*actual variant bytes. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0024

[Lines 222–225](../../../../../src/recovery/generation.cpp#L222); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,4096> GenerationOwner::path(std::uint64_t generation,std::string_view suffix) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Form a full derived generation sibling path in fixed storage. |
| inputs / outputs | Private root_path, U64 generation and trusted short suffix concatenate root + .g +16 hex digits+suffix into zeroed4096-byte array. |
| invariants | Constructor reserves23 extra bytes for the longest internal suffix; caller uses fixed .ckpt/.wal/.plan forms. Not a general arbitrary-suffix API. |
| ownership | Returned owning array, no account allocation or persistent borrow. |
| failure | No I/O; valid private sizes fit by construction, without repeated bounds guards. |
| cost | O(root path bytes +16+suffix), with fixed array initialization. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0025

[Lines 226–229](../../../../../src/recovery/generation.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,256> GenerationOwner::name(std::uint64_t generation,std::string_view suffix) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Form a basename for openat/link/unlink inside the already owned directory. |
| inputs / outputs | root_name+ .g +16 generation hex digits+trusted suffix populate zeroed256-byte array. |
| invariants | Constructor root basename&lt;=232 leaves room for longest23-byte suffix under255-byte component limit. Parent namespace remains the same locked/trusted directory. |
| ownership | Returns fixed owning array, no string allocation. |
| failure | No syscall/validation on admitted private suffix lengths. |
| cost | O(root basename bytes +16+suffix), bounded255 bytes. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0026

[Lines 230–230](../../../../../src/recovery/generation.cpp#L230); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,4096> GenerationOwner::checkpoint_path(std::uint64_t generation) const {return path(generation,".ckpt");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the selected-generation checkpoint sibling path. |
| inputs / outputs | U64 generation forwards to path(generation,".ckpt") and returns fixed4096-byte array. |
| invariants | This names a candidate/selected file but does not open it or grant selection/retirement authority. |
| ownership | Owns returned fixed path bytes; no caller/runtime pointer retained. |
| failure | No dynamic error path or filesystem effect for admitted private root state. |
| cost | Fixed forwarding plus bounded path concatenation. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0027

[Lines 231–231](../../../../../src/recovery/generation.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,4096> GenerationOwner::journal_path(std::uint64_t generation) const {return path(generation,".wal");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the selected-generation journal sibling path. |
| inputs / outputs | U64 generation forwards to path(generation,".wal") and returns fixed4096-byte array. |
| invariants | This names a candidate/selected file but does not open it or grant selection/retirement authority. |
| ownership | Owns returned fixed path bytes; no caller/runtime pointer retained. |
| failure | No dynamic error path or filesystem effect for admitted private root state. |
| cost | Fixed forwarding plus bounded path concatenation. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0028

[Lines 232–232](../../../../../src/recovery/generation.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,4096> GenerationOwner::plan_path(std::uint64_t generation) const {return path(generation,".plan");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the selected-generation plan descriptor sibling path. |
| inputs / outputs | U64 generation forwards to path(generation,".plan") and returns fixed4096-byte array. |
| invariants | This names a candidate/selected file but does not open it or grant selection/retirement authority. |
| ownership | Owns returned fixed path bytes; no caller/runtime pointer retained. |
| failure | No dynamic error path or filesystem effect for admitted private root state. |
| cost | Fixed forwarding plus bounded path concatenation. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0029

[Lines 233–245](../../../../../src/recovery/generation.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::prepare_next(std::uint64_t generation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clear only the next unselected candidate names before a rotation retry. |
| inputs / outputs | Healthy selected owner and exact next generation reread authoritative root, require stored selection, unlink only next .ckpt/.wal/.plan if present, then fsync directory. |
| invariants | Reject active retirement, absent selection, overflow or non-successor. Selected/older history and root are never deleted; no initial-create cleanup inference. |
| ownership | Keeps root/parent locks; uses fixed names and same cumulative syscall/work counters. |
| failure | Unlink/dir-sync may leave partial candidate cleanup; root selection remains unchanged. No catch rolls back name deletions; caller can recover/retry under root protocol. |
| cost | One bounded root reread/hash, three candidate unlink loops and one directory sync; no directory enumeration or historical generation scan. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0030

[Lines 246–248](../../../../../src/recovery/generation.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool GenerationOwner::cleanup_temporary(const char* name) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove a generation private temporary best effort during publication failure. |
| inputs / outputs | Generated sibling name gets up to eight unlink attempts; success/ENOENT true, non-EINTR/throw false. |
| invariants | Cleanup may exceed ordinary operation budget but never U64 counter range. Does not unlink selected root or published candidate as rollback. This fixed helper alone requests emergency_cleanup; normal publication cannot inherit the exemption by syscall stage. |
| ownership | Borrows directory fd/name; no persistent state owner. |
| failure | noexcept catch prevents masking the original publishing exception and exposes cleanup failure through typed catch. |
| cost | At most eight unlink calls, no allocation or directory scan. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [tests/unit/file_cleanup_quota_test.cpp](../../../../../tests/unit/file_cleanup_quota_test.cpp) |

## B0031

[Lines 249–274](../../../../../src/recovery/generation.cpp#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::publish(std::string_view bytes,const char* destination,bool replace,bool selection) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish fully synced private bytes as a candidate or authoritative root. |
| inputs / outputs | Bytes/destination, replace flag and selection flag create entropy-named exclusive temp, write/fsync/checked-close; use no-replace link+temp unlink or atomic rename; directory sync completes publication. |
| invariants | Caller sets target consistently. Only root selection mutates attempted_/root outcome; candidate existence is not selection. Random temp naming has16 bounded collisions; interrupted link/rename is never retried or undone. selection=true marks durable only after directory sync. |
| ownership | Fixed temp name and scoped FileDescriptor; bytes borrowed synchronously. No account/buffer allocation follows root-link/rename admission on the successful production path; exception-runtime machinery is outside that claim. |
| failure | Typed catch closes temp before bounded cleanup and rethrows original fault/stage/outcome/errno plus cleanup flag. Broad catch cleans temp and preserves original exception. Never rolls back final destination or clears unresolved selection latch. |
| cost | O(payload bytes) write plus entropy/create attempts, inode fsync/checked close, link-or-rename/unlink and directory fsync. No old-state/native clone. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp) |

```text
}catch(const GenerationFailure& error) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve generation publication outcome while cleaning only the private temporary. |
| inputs / outputs | Close private fd, attempt bounded temp unlink, then rethrow fixed original fault/stage/outcome/errno plus cleanup-failed flag. |
| invariants | Do not unlink final root/candidate as rollback; root link/rename uncertainty and attempted_ remain sticky. |
| ownership | FileDescriptor reset releases private fd; cleanup uses stable owned directory. |
| failure | Cleanup cannot mask original typed failure; unknown root outcome must reach session/recovery boundary. |
| cost | Best-effort close plus &lt;=8 unlink attempts; no heap or prefix scan. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0032

[Lines 275–282](../../../../../src/recovery/generation.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::publish_checkpoint(std::uint64_t generation,std::string_view bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one fresh checkpoint candidate and retain its private selection binding. |
| inputs / outputs | Healthy owner, positive current/next generation and checkpoint bytes within cap charge bytes work, hash content, target .ckpt and publish no-replace candidate. |
| invariants | When selected, only exact successor is admitted; initial positive generation remains caller chosen. Candidate hash/generation become usable only after successful candidate publication; root selection unchanged. |
| ownership | Borrows checkpoint bytes; retains only fixed generation/hash and owned directory/lock. Native checkpoint encoding belongs to caller/account. |
| failure | State/limit/hash-work/publication failure leaves root unchanged; candidate/temp may survive a failed publication and require normal candidate cleanup before retry. |
| cost | O(checkpoint bytes) SHA plus write, file+directory fsync and fixed naming; no native checkpoint decode in this helper. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0033

[Lines 283–291](../../../../../src/recovery/generation.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::publish_plan(std::uint64_t generation,std::string_view bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a self-contained plan descriptor candidate and bind its hash. |
| inputs / outputs | Healthy owner, positive exact next/initial generation and nonempty bytes within plan cap charge/hash then publish .plan without replacement. |
| invariants | Does not parse descriptor semantics here; supplied root can select it only with matching private generation/hash. Current plan format/source validation remains factory responsibility. |
| ownership | Borrows descriptor bytes; retains fixed hash/generation, not a second byte mirror. |
| failure | Invalid generation/empty/limit/work/I/O fails before private candidate binding update; root stays unchanged. |
| cost | O(plan bytes) hash/write plus file+directory sync and fixed name construction. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0034

[Lines 292–294](../../../../../src/recovery/generation.cpp#L292); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ImageVector<char> GenerationOwner::read_plan(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the selected self-contained plan descriptor into a receiving-account byte owner. |
| inputs / outputs | Healthy selected owner with plan hash rereads exact root, opens no-follow .plan, checks regular positive bounded size, reads/checks exact EOF/stamp/hash, closes and rereads root again. |
| invariants | Both root reads must equal stored selection. Hash binding is actual selected bytes; this helper does not parse/execute/import the descriptor or repair files. |
| ownership | One ImageVector&lt;char&gt; allocated on explicit receiving account returns by ownership; scoped fd/stack stat close on every failure. |
| failure | State/root change/type/size/work/allocation/hash/I/O failure drops only private bytes/fd. No live selected state or disk mutation here. |
| cost | O(plan bytes) read/hash and one retained buffer, two bounded root rereads/hash, EOF/stats/close; charges2*plan bytes plus each root read's declared work. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0035

[Lines 295–297](../../../../../src/recovery/generation.cpp#L295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ImageVector<char> GenerationOwner::read_checkpoint(const resource::MemoryAccount& account) {
  return read_selected(account,false);
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the selected checkpoint as opaque bytes through the locked generation owner. |
| inputs / outputs | Delegates to the shared selected-file path with checkpoint mode; returns the exact bytes funded by the supplied MemoryAccount. |
| invariants | Requires a selected root and validates checkpoint path, checkpoint cap/hash, regular-file identity, exact EOF and root continuity. It does not decode CROWN image/SQL metadata. |
| ownership | The caller owns the ImageVector; its bytes are account-backed. GenerationOwner retains the root lock and selected metadata during the call. |
| failure | Missing selection, changed/root/file/hash errors, operation/work/size limits and account failures propagate; no tail repair or durable owner is created. |
| cost | One bounded file read plus extra-byte EOF probe, stamp checks and SHA pass; work consumes twice the file size. Empty payload is permitted at this lower layer. |
| Design | [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

## B0036

[Lines 298–322](../../../../../src/recovery/generation.cpp#L298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ImageVector<char> GenerationOwner::read_selected(const resource::MemoryAccount& account,bool plan) {
  // Both selected files use the same lock/root/stamp/EOF discipline. Selection
  // of cap/hash/path is fixed before I/O; this does not decode either format.
  healthy();
  if(!has_selection() || (plan && !selected_.plan_sha256))fail(GenerationFault::state,GenerationStage::state,outcome_);
  if(read_root(false,false)!=selected_)fail(GenerationFault::changed,GenerationStage::state,outcome_);
  const auto cap=plan?limits_.plan_bytes:limits_.checkpoint_bytes;
  const auto expected=plan?*selected_.plan_sha256:selected_.checkpoint_sha256;
  target_=plan?GenerationTarget::plan:GenerationTarget::checkpoint;
  const auto source=name(selected_.generation,plan?".plan":".ckpt");FileDescriptor file;
  file.reset(static_cast<int>(checked(GenerationStage::open_root,0,directory_.get(),source.data())));
  struct stat original{},current{};static_cast<void>(checked(GenerationStage::stat_file,0,file.get(),nullptr,nullptr,nullptr,0,&original));
  if(!S_ISREG(original.st_mode))fail(GenerationFault::not_regular,GenerationStage::stat_file,outcome_);
  if(original.st_size<0 || (plan && original.st_size==0) || static_cast<std::uint64_t>(original.st_size)>cap ||
      static_cast<std::uint64_t>(original.st_size)>SIZE_MAX)fail(GenerationFault::limit,GenerationStage::read_data,outcome_);
  const auto size=static_cast<std::size_t>(original.st_size);consume_work(2*static_cast<std::uint64_t>(size));
  ImageVector<char> bytes(image_allocator<char>(account));bytes.resize(size);transfer(false,file.get(),bytes.data(),size);
  char extra=0;if(checked(GenerationStage::read_data,1,file.get(),nullptr,nullptr,&extra,size)!=0)fail(GenerationFault::changed,GenerationStage::read_data,outcome_);
  static_cast<void>(checked(GenerationStage::stat_file,0,file.get(),nullptr,nullptr,nullptr,0,&current));
  if(!same(original,current))fail(GenerationFault::changed,GenerationStage::stat_file,outcome_);
  if(sha256_fixed({bytes.data(),bytes.size()})!=expected)fail(GenerationFault::binding,GenerationStage::read_data,outcome_);
  static_cast<void>(checked(GenerationStage::close_file,0,file.release()));
  if(read_root(false,false)!=selected_)fail(GenerationFault::changed,GenerationStage::state,outcome_);
  return bytes;
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the selected plan/checkpoint read procedure while choosing each file’s identity and cap before I/O. |
| inputs / outputs | The private boolean selects \`.plan\` vs \`.ckpt\`, corresponding byte cap and selected hash; both paths check root, open/regular file, size, read, EOF, stat stamp, SHA, checked close and root again. |
| invariants | Plan remains nonempty and requires a plan hash; checkpoint may be empty. This method only returns opaque selected bytes and never parses or repairs either format. |
| ownership | Borrows the account for the new byte vector and operates while this noncopyable internal owner retains the root lock. |
| failure | GenerationFailure identifies state/changed/not-regular/limit/binding or syscall stages; allocator failures propagate, with RAII closing the file. |
| cost | Two file-size work units before allocation, one account-backed vector of the exact file size, plus bounded syscall/checksum work; counters are not CPU timing. |
| Design | [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

## B0037

[Lines 323–336](../../../../../src/recovery/generation.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::publish_root(const GenerationRoot& next) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select only the exact already-published checkpoint/optional plan candidate. |
| inputs / outputs | Next GenerationRoot must match query ID, candidate checkpoint generation/hash, first-generation rules, nondecreasing physical/command bases and optional private plan binding; encode/charge then publish root by first no-replace link or replacement rename. |
| invariants | Cannot drop an existing plan-descriptor lineage. encode validates all root fields. Only successful directory sync updates selected_, clears candidate slots and attempted_; publication errors keep authority/latch for reopen. |
| ownership | Fixed root bytes and metadata; existing directory/lock stay owned. Caller prepares final native holder/journal before this no-alloc selection barrier. |
| failure | Binding/codec/work failure precedes root attempt. After root link/rename admission uncertainty is sticky; do not blindly retry or revert selected disk name. |
| cost | Bounded root encode/hash and publication write/fsync/rename-or-link/dir-sync; fixed nonthrowing metadata publication after success. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [tests/unit/generation_fault_test.cpp](../../../../../tests/unit/generation_fault_test.cpp) |

## B0038

[Lines 337–344](../../../../../src/recovery/generation.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::select_retirement_floor() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a retirement floor only from the privately recorded intent lineage. |
| inputs / outputs | RetirementIntent.before plus current authenticated delivery anchor form next root with first_generation=current generation; already-selected next is idempotent, otherwise require exact before lineage and publish replacement root. |
| invariants | Does not accept public frontier/report as authority. Called within retire_history after actual receipt/checkpoint/intent validation; selecting floor precedes unlinking old history. Retained delivery/plan identity remains intact. |
| ownership | Fixed root copy and existing root lock; no query rows or fresh account. |
| failure | Missing intent/binding/work/publication failure preserves recorded intent for recovery. Successful publish updates selected_ and clears attempted_; no local catch discards uncertainty. |
| cost | Fixed metadata comparison/encode/hash plus root write/sync/rename/dir-sync; actual history unlink loop is separate. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0039

[Lines 345–346](../../../../../src/recovery/generation.cpp#L345); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L345-L346:sha256:bc35ccfa76017c7d2a38da5b1b1fc45d8e4fff8ae83ea60ef3e226ed8247caf2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the generation detail namespace and outer crown::recovery namespace after durable-root owner methods. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/code_specs/files/src/recovery/generation.cpp.md](generation.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |
