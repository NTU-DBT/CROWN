# `src/io/json.hpp` — block usage map

[Source](../../../../../src/io/json.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `6312b2931ab34c94b0753e248571937b05b8476925ee8f998dccbc62caccfc22`. 57 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/io/json.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–12](../../../../../src/io/json.hpp#L10) | Callable definition: \[\[noreturn\]\] inline void fail(const std::string& path, const std::string& message) | calls Error · [reviewed contract](#b0002) |
| [B0003 · 13–23](../../../../../src/io/json.hpp#L13) | Callable definition: inline void fields(const Json& value, const std::string& path, std::initializer_list&lt;std::string_view&gt; required, std::initializer… | calls is_object, fail, contains, std::string; 2 loop sites · [reviewed contract](#b0003) |
| [B0004 · 24–27](../../../../../src/io/json.hpp#L24) | Callable definition: inline const Json::array_t& array(const Json& value, std::string_view path) | calls is_array, fail, std::string; returns value.get_ref&lt;const Json::array_t&&gt;() · [reviewed contract](#b0004) |
| [B0005 · 28–31](../../../../../src/io/json.hpp#L28) | Callable definition: inline std::string string(const Json& value, const std::string& path) | calls is_string, fail; returns value.get&lt;std::string&gt;() · [reviewed contract](#b0005) |
| [B0006 · 32–35](../../../../../src/io/json.hpp#L32) | Callable definition: inline std::uint64_t unsigned_integer(const Json& value, const std::string& path) | calls is_number_integer, is_number_unsigned, fail; returns value.get&lt;std::uint64_t&gt;() · [reviewed contract](#b0006) |
| [B0007 · 36–38](../../../../../src/io/json.hpp#L36) | Callable definition: inline void version(const Json& value, const std::string& path, std::uint64_t expected = 1) | calls unsigned_integer, Error, std::to_string · [reviewed contract](#b0007) |
| [B0008 · 39–56](../../../../../src/io/json.hpp#L39) | Callable definition: inline Json parse_json(std::string_view text) | calls Error, emplace_back, back, insert; returns true; Json::parse(text, callback); growth emplace_back, insert; source comment (unverified): // DOM and duplicate-key sets allocate ordinary memory; depth is the only size cap here. · [reviewed contract](#b0008) |
| [B0009 · 57–57](../../../../../src/io/json.hpp#L57) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io::detail · [reviewed contract](#b0009) |

## B0001

[Lines 1–9](../../../../../src/io/json.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share strict DOM parsing and small typed-document field helpers among explicit IO readers. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–12](../../../../../src/io/json.hpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] inline void fail(const std::string& path, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an invalid_document error with path-qualified context. |
| inputs / outputs | Owning-string references path/message in; never returns, throws Error with path+separator+message. |
| invariants | Used only for document rejection, not to translate arbitrary allocation/native failures. |
| ownership | Diagnostic owns ordinary concatenated text; inputs remain borrowed. |
| failure | String allocation and Error/exception construction can themselves fail; no local catch. |
| cost | O(path+message bytes) formatting/storage plus exception unwind cost. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 13–23](../../../../../src/io/json.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void fields(const Json& value, const std::string& path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce exact object shape with required and optional field-name sets. |
| inputs / outputs | Const DOM/path and initializer_list&lt;string_view&gt; names in; returns only if object has each required and no unknown member. |
| invariants | No field values are validated here; duplicate key rejection belongs to parse_json before this helper receives its DOM. |
| ownership | Borrows DOM and static/caller name lists, no new set/hash container on success; path/message expressions at call sites may allocate. |
| failure | Wrong kind/missing/unknown field calls fail; no JSON/OOM catch in this helper. |
| cost | Required names use DOM object lookup; every member linearly searches required and optional lists: O(R log M+M(R+O)) comparisons plus name bytes. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 24–27](../../../../../src/io/json.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const Json::array_t& array(const Json& value, std::string_view path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual array storage after checking its DOM type. |
| inputs / outputs | Const Json plus path view in; const Json::array_t& out. |
| invariants | Returned reference expires with DOM destruction/mutation; no array deep copy. |
| ownership | Borrowed DOM array, no owner retained. |
| failure | Wrong type allocates path/message then throws invalid_document. |
| cost | O(1) successful type/ref access; no array scan or allocation. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 28–31](../../../../../src/io/json.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string string(const Json& value, const std::string& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a document string as an independent owning ordinary value. |
| inputs / outputs | Const Json/path in; std::string copy out. |
| invariants | Checks string kind; does not otherwise validate names/semantics/UTF8 beyond parser behavior. |
| ownership | get&lt;std::string&gt;() deep-copies DOM text; returned string is not a view. |
| failure | Wrong type calls fail; string allocation can propagate independently. |
| cost | O(string bytes) copy and possible ordinary allocation. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 32–35](../../../../../src/io/json.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::uint64_t unsigned_integer(const Json& value, const std::string& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a nonnegative64-bit integer without coercing booleans or floating numbers. |
| inputs / outputs | Json number/path in; uint64_t out. |
| invariants | Requires integer type and rejects negative signed representation; unsigned values retain full domain. |
| ownership | Scalar result owns no dynamic payload; input DOM is borrowed. |
| failure | Wrong kind/sign calls fail; no success mutation or catch. |
| cost | O(1) successful numeric tests/conversion; error path formats context. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 36–38](../../../../../src/io/json.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void version(const Json& value, const std::string& path, std::uint64_t expected = 1) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an exact document schema version. |
| inputs / outputs | Json numeric version/path and expected(default1) in; void out. |
| invariants | Delegates strict unsigned parsing before comparing expected version. |
| ownership | Borrows DOM; stores no state. |
| failure | Type/sign errors remain invalid_document; unequal numeric version throws unsupported_version with expected-version text. |
| cost | O(1) success; rejection builds ordinary path/version diagnostic strings. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 39–56](../../../../../src/io/json.hpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Json parse_json(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a strict ordinary JSON DOM while rejecting duplicate keys and excessive parser nesting. |
| inputs / outputs | Borrowed full text in; owning Json out; synchronous callback maintains an active-object stack of key sets. |
| invariants | Callback rejects depth&gt;256 and duplicate key bytes before a successful DOM return. There is no independent input-byte/member-count/heap cap in this helper. |
| ownership | DOM plus vector&lt;set&lt;string&gt;&gt; tracking use ordinary allocation. Key strings are copied into sets; popped object key sets are freed when object closes. |
| failure | Only Json::exception is translated to invalid_document. Explicit Error(resource_limit/duplicate), bad_alloc and unrelated failures propagate with their real category; partial DOM/key tracking unwinds. |
| cost | Full input parsing plus O(sum object-key log-member comparisons/key-byte copies); retained DOM O(document size), active key sets/stack extra scratch, no native-account charging. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
const auto callback = [&object_keys](int depth, Json::parse_event_t event, Json& parsed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track nesting and uniqueness during each JSON parser callback. |
| inputs / outputs | depth/event/parsed node in; mutates local object_keys stack and returns true for accepted events. |
| invariants | object_start pushes a set; key checks active object; object_end pops. Parser event nesting is the authority for back()/pop_back() safety. |
| ownership | Captures vector by reference for synchronous parse only; each set owns ordinary copied key strings. |
| failure | Depth/duplicate reject via Error; set/vector/string OOM propagates rather than being recategorized. |
| cost | One callback per parser event, ordered-set insertion O(log keys) comparisons with string-byte costs; key copying/allocation is real. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
} catch (const Json::exception& error) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate only nlohmann syntax/DOM exceptions at the parse boundary. |
| inputs / outputs | Catches const Json::exception& and throws invalid_document using its what() text. |
| invariants | Does not flatten explicitly thrown repository Error or bad_alloc into malformed input. |
| ownership | Temporary parser/DOM/key storage unwinds; replacement diagnostic copies ordinary message text. |
| failure | New diagnostic allocation may fail; source text and caller state remain unchanged. |
| cost | Exceptional only: unwind partially allocated parser graphs plus O(message bytes) translation. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 57–57](../../../../../src/io/json.hpp#L57); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L57:sha256:e75574b225d635cb469e050a484ebdf6a963046faaad8e8dda0e77c4f871ec43
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io::detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/json.hpp](../../../../../src/io/json.hpp), [docs/code_specs/files/src/io/json.hpp.md](json.hpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/query_memory.md](../../../../query_memory.md) |
