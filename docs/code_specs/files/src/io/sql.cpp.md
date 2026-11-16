# `src/io/sql.cpp` — block usage map

[Source](../../../../../src/io/sql.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `1fac5afa526e817eca777248f07783a7b0eb32a0750e659200022c9298de9cd5`. 24 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–3](../../../../../src/io/sql.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 4–23](../../../../../src/io/sql.cpp#L4) | Callable definition: nlohmann::json write_sql_parse(const frontend::SqlParseResult& result) | calls Json, optional; returns value ? Json(*value) : Json(nullptr); output; source comment (unverified): // Syntax export deep-copies the ordinary AST/source; semantic admission is separate. · [reviewed contract](#b0002) |
| [B0003 · 24–24](../../../../../src/io/sql.cpp#L24) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0003) |

## B0001

[Lines 1–3](../../../../../src/io/sql.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/sql.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export parser syntax/diagnostics as ordinary owning JSON before binding or admission. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/sql.cpp](../../../../../src/io/sql.cpp), [include/crown/io/sql.hpp](../../../../../include/crown/io/sql.hpp), [include/crown/frontend/parser.hpp](../../../../../include/crown/frontend/parser.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 4–23](../../../../../src/io/sql.cpp#L4); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
nlohmann::json write_sql_parse(const frontend::SqlParseResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize an existing libpg_query parse result without reparsing or claiming admission. |
| inputs / outputs | SqlParseResult in; fixed parser/version envelope with syntax source/span/AST or diagnostic positions out. |
| invariants | admission_status stays not_checked. parser_version/postgres_version labels are fixed compatibility metadata; supplied AST/result is serialized, not independently checked here. |
| ownership | Successful branch deep-copies source text and the complete owning Json AST; failure copies diagnostic strings and scalar/null positions. All DOM is ordinary caller-owned. |
| failure | Valueless result std::get/DOM/OOM failures propagate; no catch or external publication. |
| cost | O(source bytes+AST nodes/strings) deep copy on success, O(diagnostic bytes)+fixed position fields on failure; no native-account/no-allocation claim. |
| Design | [src/io/sql.cpp](../../../../../src/io/sql.cpp), [include/crown/io/sql.hpp](../../../../../include/crown/io/sql.hpp), [include/crown/frontend/parser.hpp](../../../../../include/crown/frontend/parser.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

```text
const auto optional = [](std::optional<std::size_t> value) { return value ? Json(*value) : Json(nullptr); };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional diagnostic coordinates without inventing a missing offset. |
| inputs / outputs | Optional size_t position in; inline Json number/null out through local lambda. |
| invariants | Preserves parser-provided units; serializer performs no byte-to-character conversion. |
| ownership | No captured backing or owner. |
| failure | No intentional failure branch. |
| cost | O(1), scalar/null constructor only. |
| Design | [src/io/sql.cpp](../../../../../src/io/sql.cpp), [include/crown/io/sql.hpp](../../../../../include/crown/io/sql.hpp), [include/crown/frontend/parser.hpp](../../../../../include/crown/frontend/parser.hpp), [docs/sql_support.md](../../../../sql_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 24–24](../../../../../src/io/sql.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/sql.cpp](../../../../../src/io/sql.cpp), [docs/code_specs/files/src/io/sql.cpp.md](sql.cpp.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |
