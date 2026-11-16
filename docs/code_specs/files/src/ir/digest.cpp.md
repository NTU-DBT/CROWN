# `src/ir/digest.cpp` — block usage map

[Source](../../../../../src/ir/digest.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Compute and encode canonical SHA-256 digests used for artifact identity.

Snapshot SHA-256: `5386298128ba6f3e3b2a2f865e3827ba7ba399f77d67ee64d3696fe79deb6fcd`. 70 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_identity.md](../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../src/ir/digest.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 21–45](../../../../../src/ir/digest.cpp#L21) | Callable definition: void compress(std::array&lt;std::uint32_t,8&gt;& state, const unsigned char* block) | calls size, std::rotr; 3 loop sites · [reviewed contract](#b0002) |
| [B0003 · 46–47](../../../../../src/ir/digest.cpp#L46) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 48–66](../../../../../src/ir/digest.cpp#L48) | Callable definition: std::array&lt;char,64&gt; sha256_fixed(std::string_view bytes) | calls size, max, Error, data; returns result; 5 loop sites; source comment (unverified): // Successful hashing uses fixed scratch; the owning string export is explicit. · [reviewed contract](#b0004) |
| [B0005 · 67–69](../../../../../src/ir/digest.cpp#L67) | Callable definition: std::string sha256(std::string_view bytes) | calls sha256_fixed, data, size; returns {result.data(),result.size()} · [reviewed contract](#b0005) |
| [B0006 · 70–70](../../../../../src/ir/digest.cpp#L70) | Closes surrounding scope/type. | source comment (unverified): // namespace crown · [reviewed contract](#b0006) |

## B0001

[Lines 1–20](../../../../../src/ir/digest.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::array<std::uint32_t,64> constants
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the fixed digest compression round data. |
| inputs / outputs | 64 immutable 32-bit constants used by compress. |
| invariants | Format/hash identity depends on exact bytes; this is local digest support, not a CROWN maintenance theorem. |
| ownership | Static fixed array; no owner allocation. |
| failure | Compile-time initialization. |
| cost | Fixed static storage. |
| Design | [include/crown/ir/digest.hpp](../../../../../include/crown/ir/digest.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/ingestion.md](../../../../ingestion.md), [exact paper reference](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf#page=16) |

## B0002

[Lines 21–45](../../../../../src/ir/digest.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compress(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Update eight digest state words from one complete 64-byte block. |
| inputs / outputs | Reads valid block bytes, expands 64 stack words and adds 64 rounds to caller state. |
| invariants | Caller guarantees the block extent. On the recorded native ABI, promoted word expressions remain unsigned32 and wrap modulo2^32; a different target must establish suitable integer-promotion behavior before using this argument. |
| ownership | Borrows input and mutable state; stack scratch owns the schedule. |
| failure | No input validation/catch; invalid pointer is caller error. |
| cost | Fixed 64-word scratch and 64 rounds per block, no ordinary allocation. |
| Design | [include/crown/ir/digest.hpp](../../../../../include/crown/ir/digest.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/ingestion.md](../../../../ingestion.md), [exact paper reference](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf#page=27) |

## B0003

[Lines 46–47](../../../../../src/ir/digest.cpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L47:sha256:6f5a6e0206d06f87eab0bec0b359f6f69c014bf7870f3d50533e20a819ba7abf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. Trailing source note states: Successful hashing uses fixed scratch; the owning string export is explicit. It remains prose guidance, not a certified executable claim. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. Any trailing comment in this block is guidance only and adds no runtime invariant. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [docs/code_specs/files/src/ir/digest.cpp.md](digest.cpp.md), [docs/query_identity.md](../../../../query_identity.md), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0004

[Lines 48–66](../../../../../src/ir/digest.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,64> sha256_fixed(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash arbitrary bytes into an inline lowercase hexadecimal fingerprint. |
| inputs / outputs | Borrows bytes, processes 64-byte blocks, pads one/two tail blocks, returns 64 non-terminated chars. |
| invariants | Rejects byte length beyond uint64 bit-length domain before hashing. A digest alone is no admission/proof authority. |
| ownership | Input borrowed for call; result and 128-byte tail/eight-word state are inline/stack. |
| failure | Oversize throws Error(resource_limit), which may allocate diagnostic storage; successful hashing allocates no ordinary buffer. |
| cost | Linear input-byte/block work with fixed scratch; no query work-limit argument is supplied here. |
| Design | [include/crown/ir/digest.hpp](../../../../../include/crown/ir/digest.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/ingestion.md](../../../../ingestion.md), [exact paper reference](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf#page=18) |

## B0005

[Lines 67–69](../../../../../src/ir/digest.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string sha256(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the fixed digest as an ordinary owning string. |
| inputs / outputs | Calls sha256_fixed then constructs a 64-byte string. |
| invariants | Same digest bytes; wrapper adds no source/proof verification. |
| ownership | Returned std::string owns its copy outside native account storage. |
| failure | Digest domain and ordinary string allocation failures propagate. |
| cost | Full hash work plus fixed-size output copy/allocation. |
| Design | [include/crown/ir/digest.hpp](../../../../../include/crown/ir/digest.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/ingestion.md](../../../../ingestion.md) |

## B0006

[Lines 70–70](../../../../../src/ir/digest.cpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L70:sha256:250c3e1595f7269cedf50435b03d999ca6184ec33c6daa9baf0e4bd97c55f07a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [docs/code_specs/files/src/ir/digest.cpp.md](digest.cpp.md), [docs/query_identity.md](../../../../query_identity.md), [docs/physical_plans.md](../../../../physical_plans.md) |
