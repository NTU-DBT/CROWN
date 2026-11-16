# `src/frontend/parser_detail.hpp` — block usage map

[Source](../../../../../src/frontend/parser_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Share one internal parser/deparser mutex across cold JSON/protobuf frontend calls.

Snapshot SHA-256: `8e543dcc1a6a527926500f3924c11f826c8cee9f07430f4160fc9098374657e9`. 8 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/frontend/parser_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures. | source comment (unverified): // One gate for the existing JSON wrapper and composed protobuf/deparse calls. · [reviewed contract](#b0001) |

## B0001

[Lines 1–8](../../../../../src/frontend/parser_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the narrow common native parser gate without exposing parser AST mutation APIs. |
| inputs / outputs | Private header declares std::mutex& parser_detail::mutex(). |
| invariants | Definition resides in existing crown_sql parser.cpp; all child calls release lock before rebinding. |
| ownership | Reference borrows one static mutex; no account/arena/fresh grant. |
| failure | Declaration does not handle parse failures or alter public parser ABI. |
| cost | No runtime work except callers later access the same gate. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/pg_query.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/protobuf/pg_query.upb.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb/generated_code_support.h), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/vendor/upb/upb.c), [build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/source/pinned-libpg-query/Makefile), Refactor.md:1325-1333, [docs/sql_parser.md §Lifecycle](../../../../sql_parser.md), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [src/frontend/parser_detail.hpp](../../../../../src/frontend/parser_detail.hpp), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp) |
