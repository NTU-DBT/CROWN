# `src/planner/native_physical_binding.hpp` — block usage map

[Source](../../../../../src/planner/native_physical_binding.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `ec4a06bbc9fd614fae2d8e4fd71a75c6b1ea901a9cdb8d4428f12869cc267f8b`. 113 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/planner/native_physical_binding.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Exact nlohmann default object order/UTF-8 spelling for physical v1/v2. · [reviewed contract](#b0001) |
| [B0002 · 15–16](../../../../../src/planner/native_physical_binding.hpp#L15) | Callable definition: Writer(const resource::MemoryAccount& account,resource::MemoryAttribution owner) :output(resource::MemoryAllocator&lt;char&gt;(account,… | calls output · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../src/planner/native_physical_binding.hpp#L17) | Callable definition: static void require(bool valid) | calls storage::IndexFailure; guard static void require(bool valid) {if(!valid)throw storage::IndexFailure(storage::IndexFault::contrac… · [reviewed contract](#b0003) |
| [B0004 · 18–18](../../../../../src/planner/native_physical_binding.hpp#L18) | Callable definition: void raw(std::string_view value) | calls append · [reviewed contract](#b0004) |
| [B0005 · 19–20](../../../../../src/planner/native_physical_binding.hpp#L19) | Explanatory comments or spacing. | source comment (unverified): // JSON compatibility check, not P02 validity: native planner byte strings · [reviewed contract](#b0005) |
| [B0006 · 21–33](../../../../../src/planner/native_physical_binding.hpp#L21) | Callable definition: static void utf8(std::string_view value) | calls size, require; guard else require(false);; 2 loop sites; source comment (unverified): // JSON compatibility check, not P02 validity: native planner byte strings · [reviewed contract](#b0006) |
| [B0007 · 34–35](../../../../../src/planner/native_physical_binding.hpp#L34) | Explanatory comments or spacing. | source comment (unverified): // Validate before writing a quote. Later allocation failure may leave · [reviewed contract](#b0007) |
| [B0008 · 36–49](../../../../../src/planner/native_physical_binding.hpp#L36) | Callable definition: void text(std::string_view value) | calls utf8, raw; 1 loop sites; source comment (unverified): // Validate before writing a quote. Later allocation failure may leave · [reviewed contract](#b0008) |
| [B0009 · 50–53](../../../../../src/planner/native_physical_binding.hpp#L50) | Callable definition: void number(std::uint64_t value) | calls std::to_chars, data, size, require; guard require(encoded.ec==std::errc{});raw({bytes.data(),static_cast&lt;std::size_t&gt;(encoded.ptr-bytes.data(… · [reviewed contract](#b0009) |
| [B0010 · 54–54](../../../../../src/planner/native_physical_binding.hpp#L54) | Callable definition: void limit(const std::optional&lt;std::uint64_t&gt;& value) | calls number, raw · [reviewed contract](#b0010) |
| [B0011 · 55–57](../../../../../src/planner/native_physical_binding.hpp#L55) | Callable definition: template&lt;class Range,class Function&gt; void array(const Range& values,Function emit) | calls raw, emit; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 58–61](../../../../../src/planner/native_physical_binding.hpp#L58) | Closes surrounding scope/type. | source comment (unverified): // Keep default JSON object key order/spelling exactly. The legacy v1 · [reviewed contract](#b0012) |
| [B0013 · 62–80](../../../../../src/planner/native_physical_binding.hpp#L62) | Callable definition: inline void options(Writer& out,const program::PhysicalOptions& options) | calls raw, number, limit, text; source comment (unverified): // Keep default JSON object key order/spelling exactly. The legacy v1 · [reviewed contract](#b0013) |
| [B0014 · 81–82](../../../../../src/planner/native_physical_binding.hpp#L81) | Explanatory comments or spacing. | source comment (unverified): // Caller supplies a P02-checked candidate. These range/kind checks are · [reviewed contract](#b0014) |
| [B0015 · 83–98](../../../../../src/planner/native_physical_binding.hpp#L83) | Callable definition: inline void tree(Writer& out,const program::FreeConnexTree& tree,const program::Catalog& catalog,const program::Query& query) | calls Writer::require, size, text, array; guard const auto node=\[&\](NodeId id){Writer::require(id.value&lt;tree.nodes.size());out.text(tree.nodes\[id.v…; source comment (unverified): // Caller supplies a P02-checked candidate. These range/kind checks are · [reviewed contract](#b0015) |
| [B0016 · 99–100](../../../../../src/planner/native_physical_binding.hpp#L99) | Explanatory comments or spacing. | source comment (unverified): // Build full accounted bytes, then hash; this is not streaming/constant · [reviewed contract](#b0016) |
| [B0017 · 101–112](../../../../../src/planner/native_physical_binding.hpp#L101) | Callable definition: inline std::array&lt;char,64&gt; digest(const CompiledProgram& basis,const program::FreeConnexTree& candidate, resource::MemoryAttribut… | calls out, identity, bool, options; returns sha256_fixed(out.output); source comment (unverified): // Build full accounted bytes, then hash; this is not streaming/constant · [reviewed contract](#b0017) |
| [B0018 · 113–113](../../../../../src/planner/native_physical_binding.hpp#L113) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::native_binding_detail · [reviewed contract](#b0018) |

## B0001

[Lines 1–14](../../../../../src/planner/native_physical_binding.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build exact legacy-compatible physical binding JSON bytes without an unaccounted JSON DOM. |
| inputs / outputs | Internal raw/text/integer/array emitters append to one MemoryAllocator string using supplied receiving account, scratch purpose and attribution. |
| invariants | Fixed key order and JSON spelling must match ordinary lower.cpp/nlohmann default output. No implicit semantic validation, work metering or streamed hashing is provided. |
| ownership | Writer owns buffer and account allocator handle; borrows source views only while appending. Dynamic capacity is accounted to receiver, which may differ from immutable basis account under replan_into. |
| failure | Invalid account/attribution, contract, memory limit/allocation or length errors propagate; private partial bytes never publish a digest. |
| cost | Full encoded binding retained in one string, with possible reallocation/copy and inline storage. No DOM nodes; not constant space or a CPU deadline. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0002

[Lines 15–16](../../../../../src/planner/native_physical_binding.hpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Writer(const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the byte sink with the receiving query allocator provenance. |
| inputs / outputs | MemoryAccount and MemoryAttribution construct output string allocator with MemoryPurpose::scratch. |
| invariants | No fresh account/grant is created. Subsequent dynamic buffer allocations use the exact supplied account/purpose/owner. |
| ownership | String allocator retains shared account state; caller source data is not retained. |
| failure | Allocator validates account/purpose/attribution and may throw MemoryFailure(contract); empty string can use inline storage without heap allocation. |
| cost | Constant shell/owner construction; later capacity growth is separate. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0003

[Lines 17–17](../../../../../src/planner/native_physical_binding.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static void require(bool valid)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an internal binding serialization contract violation with a fixed fault. |
| inputs / outputs | True returns; false throws IndexFailure(IndexFault::contract). |
| invariants | Does not allocate strings or transform invalid data into a hash result. |
| ownership | No retained input/output ownership. |
| failure | Fixed exception propagates; no local catch. |
| cost | Constant branch/payload. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0004

[Lines 18–18](../../../../../src/planner/native_physical_binding.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void raw(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append already-framed bytes directly to the private accounted string. |
| inputs / outputs | Borrowed byte view is appended verbatim. |
| invariants | Caller supplies JSON syntax or already validated data; raw does not quote, validate UTF-8 or meter logical work. |
| ownership | Copies bytes into owned output; source view need only live for call. |
| failure | Account limits, allocation or string length errors propagate; output may hold a valid prior prefix rather than a complete document. |
| cost | O(appended bytes) plus possible whole-buffer growth/relocation; dynamic capacity uses receiver account. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0005

[Lines 19–20](../../../../../src/planner/native_physical_binding.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L20:sha256:b89d0ab211440640de10c0a31b7e77ba359d33d296a51bff9f931d383faf5d10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for utf8: JSON compatibility check, not P02 validity: native planner byte strings can be broader than this strict UTF-8 digest/transport boundary. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies utf8; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for utf8 come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/native_physical_binding.hpp](../../../../../src/planner/native_physical_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection.md](../../../../selection.md) |

## B0006

[Lines 21–33](../../../../../src/planner/native_physical_binding.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static void utf8(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the strict UTF-8 string domain required by legacy JSON digest spelling. |
| inputs / outputs | Scan ASCII or 2/3/4-byte sequences, reject illegal leads/continuations, truncation, overlong encodings, surrogates and code points above U+10FFFF. |
| invariants | Checks bounds before continuation reads; NUL/control bytes are allowed here and escaped later. This is JSON transport compatibility, not a general restriction on native planner byte strings. |
| ownership | Read-only synchronous borrow; no output mutation or auxiliary allocation. |
| failure | Bad UTF-8 throws fixed IndexFailure(contract); no partial text was appended by this validator. |
| cost | O(input bytes), constant scalar scratch. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0007

[Lines 34–35](../../../../../src/planner/native_physical_binding.hpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L35:sha256:7fe980870fe8ded8b5b0b440d6e13a3244d5484b9f7d22921cfcbed3225b423a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for text: Validate before writing a quote. Later allocation failure may leave a private prefix; the caller publishes only a completed digest. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies text; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for text come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/native_physical_binding.hpp](../../../../../src/planner/native_physical_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection.md](../../../../selection.md) |

## B0008

[Lines 36–49](../../../../../src/planner/native_physical_binding.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void text(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one JSON string with the exact default nlohmann UTF-8/escape spelling. |
| inputs / outputs | Validate complete UTF-8 first; append quotes, standard short escapes, lowercase u00xx control escapes and other raw UTF-8 bytes. |
| invariants | Quotes/backslashes/control bytes are escaped; slash and valid non-ASCII are not gratuitously escaped. Prevalidation prevents invalid text from appending a prefix, but later allocation failure need not roll back the private sink. |
| ownership | Borrows input while copying bytes to owned accounted output; local per-character buffer does not escape. |
| failure | Invalid UTF-8 or append/account/allocation/length failures propagate; caller discards incomplete digest construction. |
| cost | Two passes over text with up to six output bytes per input control byte, plus sink capacity growth; no JSON DOM allocation. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0009

[Lines 50–53](../../../../../src/planner/native_physical_binding.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void number(std::uint64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit an unsigned integer using locale-independent decimal JSON spelling. |
| inputs / outputs | to_chars writes into a 32-byte stack array; require success and append the exact digit range. |
| invariants | Buffer exceeds the 20 decimal digits needed for uint64; no sign/leading formatting or locale dependency. |
| ownership | Owns only fixed local scratch; output copies bytes. |
| failure | Unexpected conversion failure is contract fault; append account/allocation/length failures propagate. |
| cost | Bounded integer conversion and at most 20 appended bytes, plus possible sink relocation. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0010

[Lines 54–54](../../../../../src/planner/native_physical_binding.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void limit(const std::optional<std::uint64_t>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve nullable/unlimited work ceiling spelling in physical options. |
| inputs / outputs | Present optional emits number, absent emits literal null. |
| invariants | Zero is emitted as zero; absent is unlimited policy data, not authorization to raise host caps. |
| ownership | Borrows optional during call; output owns bytes. |
| failure | Append/conversion failures propagate. |
| cost | Constant branch plus bounded emitted text/capacity work. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0011

[Lines 55–57](../../../../../src/planner/native_physical_binding.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Range,class Function> void array(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit an ordered framed JSON array via an internal synchronous element emitter. |
| inputs / outputs | Write brackets and commas, invoke emit once per input element in iteration order. |
| invariants | Preserves order/duplicates. Empty range emits \[\]; emitter is a caller-supplied trusted internal callable, not a background callback or validator. |
| ownership | Borrows range/callable only for call; sink owns produced bytes. |
| failure | Emitter or append failure propagates with private partial output; no transactional rollback or hidden catch. |
| cost | O(element count) framing plus all emitter/byte/capacity costs; fixed local first flag. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0012

[Lines 58–61](../../../../../src/planner/native_physical_binding.hpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L61:sha256:cf89759b206f7e7e4d54aa2025cffd4df1c8725a5d29f261fa72cd2e6fa64e65
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. Its attached note introduces nearby behavior: Keep default JSON object key order/spelling exactly. The legacy v1 digest omits explicit options; indexed v2 includes this whole object. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/native_physical_binding.hpp](../../../../../src/planner/native_physical_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection.md](../../../../selection.md) |

## B0013

[Lines 62–80](../../../../../src/planner/native_physical_binding.hpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void options(Writer& out,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reproduce physical option JSON field order and supported indexed v2 envelope exactly. |
| inputs / outputs | Emit optional indexed capacities/work contract, nullable lowering/identity ceilings, policy strings and version determined by indexed presence. |
| invariants | Constant keys are lexicographically ordered as the default JSON object writer. Values are already admitted metadata; this does not validate backend resource sufficiency. digest includes this object only for indexed v2. |
| ownership | Borrows immutable options; sink owns all copied bytes. |
| failure | Invalid policy UTF-8 or sink/account/allocation failures propagate. No newly authorized policy or budget is created. |
| cost | Fixed member count plus variable policy text and buffer growth. Does not scan table contents or allocate a JSON object graph. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [schemas/physical-plan-options-v1.schema.json](../../../../../schemas/physical-plan-options-v1.schema.json), [schemas/physical-plan-options-v2.schema.json](../../../../../schemas/physical-plan-options-v2.schema.json) |

## B0014

[Lines 81–82](../../../../../src/planner/native_physical_binding.hpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L82:sha256:24bab072e8cb4e82f178727cb610a4a12028e3ba95d0fea6e0627fcccaadc8e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for tree: Caller supplies a P02-checked candidate. These range/kind checks are not a second full tree validator; exact display IDs/claims stay bound. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies tree; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for tree come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/native_physical_binding.hpp](../../../../../src/planner/native_physical_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection.md](../../../../selection.md) |

## B0015

[Lines 83–98](../../../../../src/planner/native_physical_binding.hpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void tree(Writer& out,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit the checked candidate tree in exact legacy physical binding JSON form. |
| inputs / outputs | Serialize catalog version, optional claimed connex/height, ordered nodes/children/scopes/claims and root, using query names and occurrence labels. |
| invariants | Caller supplies an admitted P02-checked candidate; local ID-range/kind/occurrence checks are not complete topology/cover/connect/guard/connex validation. Display IDs and optional claims are intentionally retained in physical binding. |
| ownership | Borrows native catalog/query/tree views; copies all text/frames into private accounted sink. Lambdas do not escape. |
| failure | Out-of-range IDs, illegal kind/occurrence or invalid UTF-8 throw fixed contract fault; buffer failures propagate. No partial hash is returned. |
| cost | Visits all serialized nodes/edges/scopes/claims and text bytes, plus buffer capacity growth. No source/query graph clone or JSON DOM. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0016

[Lines 99–100](../../../../../src/planner/native_physical_binding.hpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L100:sha256:9e193dca0d4fea425f1ba03231db09be59333d8057e45a7db6390a34bc57cb92
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for digest: Build full accounted bytes, then hash; this is not streaming/constant space. Exact source admission belongs to NativeLowering before this call. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies digest; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for digest come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/native_physical_binding.hpp](../../../../../src/planner/native_physical_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection.md](../../../../selection.md) |

## B0017

[Lines 101–112](../../../../../src/planner/native_physical_binding.hpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::array<char,64> digest(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the deterministic physical v1/v2 digest for a checked replacement tree under an immutable source basis. |
| inputs / outputs | Build domain/lowerer, occurrence map, indexed v2 options if present, cache/source digests, exact candidate tree, variable map and version; sha256_fixed returns 64 lowercase hex bytes. |
| invariants | Compatibility envelope matches lower.cpp: legacy v1 omits explicit options, indexed v2 includes them. Reuses admitted source/cache identities, does not authorize candidate binding or prove optimum; caller replan checks exact source separately. |
| ownership | Borrows basis/candidate during call, owns one temporary receiver-account scratch buffer; result is a value array independent of its lifetime. |
| failure | Invalid handles/view data, UTF-8/contracts, account/allocation/length or SHA length-domain errors propagate before digest publication. |
| cost | O(full encoded binding bytes) serialization/hash plus variable growth; retains full byte buffer while hashing rather than streaming. No extra logical checkpoint per emitted byte. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0018

[Lines 113–113](../../../../../src/planner/native_physical_binding.hpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L113:sha256:8508e3ab3e952f9fd7fcb2d9c68cc68a88818f268395ee18c1410ee290b9de4d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::native_binding_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/native_physical_binding.hpp](../../../../../src/planner/native_physical_binding.hpp), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection.md](../../../../selection.md) |
