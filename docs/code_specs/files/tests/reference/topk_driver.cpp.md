# `tests/reference/topk_driver.cpp` — block usage map

[Source](../../../../../tests/reference/topk_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1860b48078cd0cc5deb1831072b93eb9dd1b05cf1be9ca8efcffbc4d2fb19241`. 90 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/reference/topk_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 16–20](../../../../../tests/reference/topk_driver.cpp#L16) | Callable definition: Json tuple(const aggregate::Tuple& value) | calls Json::array, view, push_back, io::write_scalar_view; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 21–27](../../../../../tests/reference/topk_driver.cpp#L21) | Callable definition: std::vector&lt;topk::Key&gt; order(const Json& request) | calls push_back, at; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 28–42](../../../../../tests/reference/topk_driver.cpp#L28) | Callable definition: template&lt;class Owner&gt; Json snapshot(const Owner& owner,const Json& ranks) | calls Json::array, order, at, snapshot_topk; returns {{@ ,owner.sequence()},{@ ,std::move(output)}}; growth push_back; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 43–49](../../../../../tests/reference/topk_driver.cpp#L43) | Callable definition: FreeConnexTree tree(const frontend::SqlRowsProgram& program) | calls contradiction, export_core, planner::minimum_tree, Error; returns {}; *chosen.tree · [reviewed contract](#b0005) |
| [B0006 · 50–65](../../../../../tests/reference/topk_driver.cpp#L50) | Callable definition: template&lt;class Owner&gt; Json trace(Owner& owner,const Json& request) | calls Json::array, snapshot, at, is_null; returns result; growth emplace_back, push_back; 3 loop sites · [reviewed contract](#b0006) |
| [B0007 · 66–83](../../../../../tests/reference/topk_driver.cpp#L66) | Callable definition: Json evaluate(const Json& request) | calls io::read_catalog_payload, at, value, s04_runtime::options; returns {{@ ,request.at(@ )},{@ ,trace(owner,request)}}; {{@ ,request.at(@ )},{@ ,trace(owner,request)}} · [reviewed contract](#b0007) |
| [B0008 · 84–85](../../../../../tests/reference/topk_driver.cpp#L84) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 86–90](../../../../../tests/reference/topk_driver.cpp#L86) | Callable definition: int main() | calls std::getline, evaluate, Json::parse, dump; returns 1; 1 loop sites · [reviewed contract](#b0009) |

## B0001

[Lines 1–15](../../../../../tests/reference/topk_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:41862afb4c6f4aac2f8ebf44dd315b987388e53e8ae399010dcb65c7291cac04
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare isolated test dependencies, exact fixture types and constants. |
| inputs / outputs | Imports/includes and local aliases configure this one test module; they are not a production query primitive. |
| invariants | Python oracle imports no CROWN implementation. Native unit replacement new is confined to its one test translation unit and standard assertions must remain enabled. |
| ownership | Ordinary module definitions own no active native query or subprocess. |
| failure | Missing dependencies or build errors prevent this test from starting. |
| cost | Module/build setup only; no update-path or ranking-time charge is implied. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/topk_driver.cpp](../../../../../tests/reference/topk_driver.cpp) |

## B0002

[Lines 16–20](../../../../../tests/reference/topk_driver.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L20:sha256:ee7e1358d43504fcfb85609c00ab8d45e38fd4d86fd4a7e8a6b4db045077ff95
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode actual native tuple values for independent checking. |
| inputs / outputs | Tuple cells become a JSON array with existing exact scalar tags and NULL. |
| invariants | No expected values or rank decisions are computed here. |
| ownership | JSON owns presentation values; the tuple is borrowed only during encoding. |
| failure | Encoding/allocation errors propagate to the process boundary. |
| cost | Linear selected tuple fields/bytes; ordinary test transport allocation. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/topk_driver.cpp](../../../../../tests/reference/topk_driver.cpp) |

## B0003

[Lines 21–27](../../../../../tests/reference/topk_driver.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L27:sha256:413d62003fc701378b67b9f536524e9aeb438b3827a932006b10ce93f6bb2a69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the closed test rank request. |
| inputs / outputs | Known fixture field/direction/NULL strings become public topk::Key descriptors. |
| invariants | Fixtures contain only asc/desc and first/last; invalid public enum admission is tested directly in the native unit. |
| ownership | The ordinary descriptor vector owns keys. |
| failure | Malformed JSON/types throw and fail the driver. |
| cost | Linear requested-key decode; not engine ranking work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/topk_driver.cpp](../../../../../tests/reference/topk_driver.cpp) |

## B0004

[Lines 28–42](../../../../../tests/reference/topk_driver.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L42:sha256:dccde1c47f56393881d99f35c4ea43ab47efa7be17c134bbddc8ddd2a14f512a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Call the real public top-k operator for every rank request. |
| inputs / outputs | A quiescent genuine owner and fixture requests produce actual ordered identities, values, weights and metrics. |
| invariants | No full native snapshot is used as oracle expectation; this only reports actual public results. |
| ownership | Each ranked result owns data until copied into ordinary JSON; owner state is not changed. |
| failure | Top-k/resource/serialization failure aborts the request. |
| cost | Actual explicit top-k work plus separate test JSON copying; no benchmark timing. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/topk_driver.cpp](../../../../../tests/reference/topk_driver.cpp) |

## B0005

[Lines 43–49](../../../../../tests/reference/topk_driver.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L49:sha256:d5f0da2e3810dfc905375c4b36e74914b587aeadf5ef3a08046f6be4c1642281
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain checked source admission for a fixture query. |
| inputs / outputs | A genuine row program exports its CQ and obtains a completely checked minimum witness. |
| invariants | Unsupported source structure must fail; no hand-written query registration or proof DTO enters execution. |
| ownership | The cold tree DTO is copied to runtime factory admission. |
| failure | Missing proved tree throws topk_oracle_tree. |
| cost | Cold planner construction, separate from top-k sorting. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/topk_driver.cpp](../../../../../tests/reference/topk_driver.cpp) |

## B0006

[Lines 50–65](../../../../../tests/reference/topk_driver.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L65:sha256:ddeff74ff6c83ab42d6a389fe6eda19d7a4398811d36012b35d30053fabd9aa9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply physical replacements and report top-k after every committed epoch. |
| inputs / outputs | Initial owner plus ordered update/rank request arrays produce a complete native trace. |
| invariants | All source columns and before/after weights enter the real net-batch API; no expected tuple is injected. |
| ownership | Owned decode rows keep borrowed cells alive through synchronous preparation; output JSON owns retained transport. |
| failure | Decode/native/rank errors fail the process; no partial successful corpus is accepted by Python. |
| cost | Linear finite fixture decode plus genuine update and snapshot recomputation work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/topk_driver.cpp](../../../../../tests/reference/topk_driver.cpp) |

## B0007

[Lines 66–83](../../../../../tests/reference/topk_driver.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L83:sha256:bcf610386018073199cda0fb17884545446ed2d077fe26de026ba4dbbbd64735
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and execute one actual SQL fixture in either result family/backend. |
| inputs / outputs | Closed request SQL/catalog/family/backend/scale create a row or aggregate owner, then trace it. |
| invariants | Real public factories supply types/schema; aggregate source tree and declared AVG scale belong to that program. |
| ownership | Local genuine owner and immutable program retain native state for the request lifetime. |
| failure | BindingDiagnostic becomes Error; all other errors propagate to main. |
| cost | Cold bind/admit plus finite trace; no query-specific executor implementation. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/topk_driver.cpp](../../../../../tests/reference/topk_driver.cpp) |

## B0008

[Lines 84–85](../../../../../tests/reference/topk_driver.cpp#L84); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L85:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous fixture-helper namespace. |
| inputs / outputs | The scope delimiter exposes only the subsequent process entry point. |
| invariants | Fixture helper names remain local to this test translation unit. |
| ownership | No runtime ownership transfer occurs at the delimiter. |
| failure | No executable failure behavior. |
| cost | No executable work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/topk_driver.cpp](../../../../../tests/reference/topk_driver.cpp) |

## B0009

[Lines 86–90](../../../../../tests/reference/topk_driver.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L90:sha256:9184185c58691bb8fb2a00baa5d77114f4329d4c11b8f46db7537b27b867fd95
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame native test requests and preserve failing exit behavior. |
| inputs / outputs | One JSON request per stdin line yields one actual result line. |
| invariants | The independent checker must receive exactly one result per requested case/backend. |
| ownership | Per-line JSON and owner state are local; stdout contains actual transport only. |
| failure | The single test-process catch prints an exception and returns1; partial stdout never becomes a pass. |
| cost | Finite line transport and process orchestration, outside query-account promises. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/topk_driver.cpp](../../../../../tests/reference/topk_driver.cpp) |
