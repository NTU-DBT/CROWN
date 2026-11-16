# `examples/independent-queries/main.cpp` — block usage map

[Source](../../../../../examples/independent-queries/main.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `4d40068f2ca76bb7f8ef356fd992b36445711d294c3c15b71f45e1ac7aac0be7`. 81 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../examples/independent-queries/main.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–28](../../../../../examples/independent-queries/main.cpp#L15) | Callable definition: std::string read(const char* path) | calls input, Error, gcount, size; returns result; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 29–29](../../../../../examples/independent-queries/main.cpp#L29) | Explanatory comments or spacing. |  |
| [B0004 · 30–44](../../../../../examples/independent-queries/main.cpp#L30) | Callable definition: runtime::QuerySession::Owner create(const Catalog& catalog,const char* sql,const char* events) | calls frontend::admit_sql, read, Error, planner::minimum_tree; returns runtime::QuerySession::create(planner::lower_normalized(*admitted.program,tree),std::move(input)); growth make_unique · [reviewed contract](#b0004) |
| [B0005 · 45–47](../../../../../examples/independent-queries/main.cpp#L45) | Explanatory comments or spacing. | source comment (unverified): // Explicit serial execution uses the ordinary per-session API. The directory · [reviewed contract](#b0005) |
| [B0006 · 48–63](../../../../../examples/independent-queries/main.cpp#L48) | Callable definition: io::Json run(runtime::QuerySession& session) | calls start, begin_next, step, commit; returns {{@ ,snapshot.sequence},{@ ,std::move(rows)},; growth push_back; 5 loop sites; source comment (unverified): // Explicit serial execution uses the ordinary per-session API. The directory · [reviewed contract](#b0006) |
| [B0007 · 64–65](../../../../../examples/independent-queries/main.cpp#L64) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 66–81](../../../../../examples/independent-queries/main.cpp#L66) | Callable definition: int main(int argc,char** argv) | calls crown::Error, crown::io::read_catalog, read, create; returns std::cout ? 0 : 1; 1; growth push_back; 2 loop sites · [reviewed contract](#b0008) |

## B0001

[Lines 1–14](../../../../../examples/independent-queries/main.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:0c1f2fddb2c57ba64b8e8ebb6bb3624ce9a89f40e1ce447d63a3668462d37d66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use installed frontend/planner/session interfaces in a standalone consumer. |
| inputs / outputs | Public Crown headers, standard IO and a private helper namespace. |
| invariants | No private test/reference helper or handwritten query registration is included. |
| ownership | No runtime owner yet. |
| failure | Public dependency mismatch fails compilation. |
| cost | Compile-time dependency only. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 15–28](../../../../../examples/independent-queries/main.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L28:sha256:e28b758a46797ec628cdafef91f6f2617ac486e676293c2955f3f1321582fb60
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a bounded catalog or SQL text document. |
| inputs / outputs | Filesystem path in; owned text up to16MiB out. |
| invariants | Check incoming chunk against remaining capacity before append; reject stream read errors. |
| ownership | ifstream/string own temporary IO and text outside native query accounts. |
| failure | io_error on open/read, resource_limit on size, ordinary allocation failures propagate. |
| cost | O(document bytes), at most16MiB text plus fixed4KiB read buffer. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 30–44](../../../../../examples/independent-queries/main.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L44:sha256:ec0d11bd74ed4a0267e711426f55e8372074b920d7da8f0ecf95a75f1c7049da
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile arbitrary admitted SQL and create one independent owned input session. |
| inputs / outputs | Catalog, SQL path and event path in; QuerySession owner out. |
| invariants | Normal SQL admission/minimum-tree proof/lowering pipeline; constant-empty route needs no tree proof. |
| ownership | Returned owner retains its moved input stream and fresh query runtime/account; compiler temporaries are RAII. |
| failure | Reject SQL outside admitted class, unproved minimum or unopened input; failures free temporaries. |
| cost | Cold frontend/planner work and normal session construction; no query-specific registration. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 45–47](../../../../../examples/independent-queries/main.cpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L47:sha256:79b361204e642e737bf5bf2baadfb936346684880d8cb3c419769d5e3cfeacda
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain that the example serially invokes the ordinary per-session loop. |
| inputs / outputs | Comment preceding run(). |
| invariants | The directory contains no hidden fan-out, scheduler or update callback. |
| ownership | No ownership operation in these comments. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 48–63](../../../../../examples/independent-queries/main.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L63:sha256:2fad7699dbc2b1fbbbf1c6bf36313cf5d3c4f9ab4d7a2196c7edef41aff14494
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one admitted input independently and serialize its actual final result/progress. |
| inputs / outputs | Session reference in; JSON rows, committed sequence and native account identity out. |
| invariants | Start/begin/step/commit/drain order is the existing Session protocol; every update drains its normal output port. |
| ownership | Borrowed session stays owned by directory; snapshot owns its rows while JSON is assembled. |
| failure | Session/input/budget failures propagate to the one CLI boundary; no partial success report is emitted. |
| cost | Ordinary per-input execution plus final snapshot/JSON materialization; reporting is outside the update inner loop. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 64–65](../../../../../examples/independent-queries/main.cpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L65:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close private consumer helper scope. |
| inputs / outputs | Namespace delimiter only. |
| invariants | Helpers stay outside public library API. |
| ownership | No ownership operation. |
| failure | No runtime failure. |
| cost | No runtime cost. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 66–81](../../../../../examples/independent-queries/main.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L81:sha256:17cafa8dc557a6bfb29d438bcefad0e185ce3198505d2dba28d8aca126c04301
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Demonstrate two independently compiled/session-owned SQL streams through the public directory. |
| inputs / outputs | Five file arguments in; one JSON report and exit status out. |
| invariants | Both sessions constructed independently, admitted, run serially and erased; report includes remaining_queries zero and distinct actual account identities. |
| ownership | Local owners protect construction failures; directory owns admitted sessions; output JSON lives to write completion. |
| failure | One CLI std::exception handler prints failure and returns1; stdout flush failure returns1. |
| cost | Two cold compilations plus each real stream execution; directory stores two nodes; no shared query algorithm. |
| Design | [docs/independent_queries.md](../../../../independent_queries.md), [Refactor.md §X10](../../../../../Refactor.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |
