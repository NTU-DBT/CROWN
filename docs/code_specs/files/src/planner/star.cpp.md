# `src/planner/star.cpp` — block usage map

[Source](../../../../../src/planner/star.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Check center/satellite/head structure and lower a full-catalog source coordinator with no generic occurrence routes.

Snapshot SHA-256: `743df9249d8a6d8f27e479cf961e2f5282c392e66ed03a8d8dd5035663f7b29c`. 111 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [star](../../../subsystem_contracts.md#star). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/planner/star.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // The one balance spans shape checks and output mapping. A failed private · [reviewed contract](#b0001) |
| [B0002 · 11–17](../../../../../src/planner/star.cpp#L11) | Type/record definition: struct Budget | source comment (unverified): // The one balance spans shape checks and output mapping. A failed private · [reviewed contract](#b0002) |
| [B0003 · 18–20](../../../../../src/planner/star.cpp#L18) | Callable definition: void require(bool condition, const char* message) | calls Error; guard void require(bool condition, const char* message) { · [reviewed contract](#b0003) |
| [B0004 · 21–22](../../../../../src/planner/star.cpp#L21) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 23–31](../../../../../src/planner/star.cpp#L23) | Type/record definition: struct Plan::Data |  · [reviewed contract](#b0005) |
| [B0006 · 32–32](../../../../../src/planner/star.cpp#L32) | Explanatory comments or spacing. |  |
| [B0007 · 33–33](../../../../../src/planner/star.cpp#L33) | Callable definition: const PhysicalPlan& Plan::general() const & noexcept | calls ; returns data_-&gt;general · [reviewed contract](#b0007) |
| [B0008 · 34–34](../../../../../src/planner/star.cpp#L34) | Callable definition: const PhysicalPlan& Plan::source_only() const & noexcept | calls ; returns data_-&gt;source_only · [reviewed contract](#b0008) |
| [B0009 · 35–35](../../../../../src/planner/star.cpp#L35) | Callable definition: OccurrenceId Plan::center() const noexcept | calls ; returns data_-&gt;center · [reviewed contract](#b0009) |
| [B0010 · 36–36](../../../../../src/planner/star.cpp#L36) | Callable definition: TableId Plan::center_table() const noexcept | calls ; returns data_-&gt;center_table · [reviewed contract](#b0010) |
| [B0011 · 37–37](../../../../../src/planner/star.cpp#L37) | Callable definition: std::size_t Plan::dimension() const noexcept | calls size; returns data_-&gt;satellites.size() · [reviewed contract](#b0011) |
| [B0012 · 38–38](../../../../../src/planner/star.cpp#L38) | Callable definition: std::size_t Plan::distinct_head() const noexcept | calls ; returns data_-&gt;distinct_head · [reviewed contract](#b0012) |
| [B0013 · 39–39](../../../../../src/planner/star.cpp#L39) | Callable definition: std::span&lt;const std::optional&lt;TableId&gt;&gt; Plan::satellite_tables() const & noexcept | calls ; returns data_-&gt;satellites · [reviewed contract](#b0013) |
| [B0014 · 40–40](../../../../../src/planner/star.cpp#L40) | Callable definition: std::span&lt;const std::size_t&gt; Plan::head_coordinates() const & noexcept | calls ; returns data_-&gt;head · [reviewed contract](#b0014) |
| [B0015 · 41–41](../../../../../src/planner/star.cpp#L41) | Callable definition: const Usage& Plan::usage() const & noexcept | calls ; returns data_-&gt;usage · [reviewed contract](#b0015) |
| [B0016 · 42–42](../../../../../src/planner/star.cpp#L42) | Explanatory comments or spacing. |  |
| [B0017 · 43–110](../../../../../src/planner/star.cpp#L43) | Callable definition: Plan admit(const PhysicalPlan& general, OccurrenceId center, const Limits& limits) | calls take, require, normalized, route; guard require(!general.normalized(), "star admission requires a direct CQ, without a SQL adapter");; returns Plan(std::make_shared&lt;Plan::Data&gt;(Plan::Data{general, std::move(source), center,; growth insert, make_shared, push_back; 5 loop sites; source comment (unverified): // Genuine PhysicalPlan admission already established dense in-range variable · [reviewed contract](#b0017) |
| [B0018 · 111–111](../../../../../src/planner/star.cpp#L111) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::star · [reviewed contract](#b0018) |

## B0001

[Lines 1–10](../../../../../src/planner/star.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:50e0845788db527f25498ce0fc65affc37e04e8e25818ee9198c3ef680cb6756
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the cold star plan implementation and introduce its private shared admission balance. |
| inputs / outputs | Includes/namespaces and explanation of one shape/output-mapping balance; no plan is admitted here. |
| invariants | Private builder failure must publish no Plan metadata and must preserve the supplied genuine general plan handle. |
| ownership | Declarations retain no source rows, runtime or account. |
| failure | Dependency/type errors are compile failures; runtime errors arise in following helpers. |
| cost | Compilation/static scaffolding only. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp) |

## B0002

[Lines 11–17](../../../../../src/planner/star.cpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L17:sha256:603e578c05a8f24f4b81f97813b3077b935f1cf56b712bcfe283a99f1a28a231
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit one selected cold shape/mapping unit without overflow or grant refill. |
| inputs / outputs | Budget.remaining/used and take() declaration/body; each successful take decrements remaining and increments used. |
| invariants | Zero is rejected before mutation; used cannot exceed the original uint64 work grant. This is not a CPU/byte bound. |
| ownership | Small private stack builder state; no query allowance is minted. |
| failure | Exhaustion throws Error(star_work_limit) before changing counters. |
| cost | One branch and two scalar updates per selected unit; Error formatting/allocation remains additional. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [docs/star.md](../../../../star.md) |

## B0003

[Lines 18–20](../../../../../src/planner/star.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L20:sha256:7d6e551048b2696811adf0a32bdb3dc68757afc107355a3bd54719c7c1677772
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a failed literal star structural/head premise. |
| inputs / outputs | Boolean premise and static diagnostic message in; normal return or star_admission Error out. |
| invariants | This guard does not repair an unsupported query or convert a comparison plan into a theorem. |
| ownership | Borrows message for immediate Error construction; owns no plan/source state. |
| failure | False premise throws Error(star_admission); no catch/retry is installed. |
| cost | One branch plus failure diagnostic/exception costs. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp) |

## B0004

[Lines 21–22](../../../../../src/planner/star.cpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L22:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the implementation-private admission helper namespace. |
| inputs / outputs | Namespace closing brace/comment only. |
| invariants | Budget/require remain private; Plan::Data definitions follow in planner::star. |
| ownership | No payload ownership change. |
| failure | No executable failure branch. |
| cost | No runtime work. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp) |

## B0005

[Lines 23–31](../../../../../src/planner/star.cpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L31:sha256:75c6028ea15ab861f64729b566f12205dbb4c5ba641f35b5249219ec5cc90465
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain completed immutable original/source-only plans and exact coordinate/head metadata. |
| inputs / outputs | Plan::Data holds general/source_only PhysicalPlans, original center/table IDs, per-coordinate optional satellites, ordered head coordinates, distinct head count and Usage. |
| invariants | The source-only operator is a source coordinator, not a result rewrite. Metadata records original physical IDs and exact repetitions; no dynamic H or degree state is stored in this cold wrapper. |
| ownership | shared_ptr&lt;const Data&gt; owns ordinary compiler vectors and retained immutable PhysicalPlan handles; native receiving account import is separate. |
| failure | Type declaration alone cannot fail; aggregate construction/allocation in admit() remains private until complete. |
| cost | O(d+head width) wrapper payload plus retained plan graphs, with ordinary container/control overhead. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [docs/star.md](../../../../star.md) |

## B0007

[Lines 33–33](../../../../../src/planner/star.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L33:sha256:547203c3ad89d4aacd38d6b74e3ffe3cbcf23fb962088b67d874fc7c387604fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the unchanged genuine original comparison plan. |
| inputs / outputs | Named valid Plan in; const PhysicalPlan& from Data.general out. |
| invariants | No source-only metadata replaces the original CQ or checked-upper profile. |
| ownership | Reference/span borrows Data held by a surviving Plan; copied scalar IDs/counts own no payload. Data is immutable. |
| failure | No validation/allocation/failure branch on a valid privately constructed Plan; noexcept accessor. |
| cost | Constant field/reference/span access; retaining and last-owner destruction are separate costs. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [docs/star.md](../../../../star.md) |

## B0008

[Lines 34–34](../../../../../src/planner/star.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L34:sha256:f3199359477ac8c45be613818083fc5c25ba8acce2d2be6f948784b2c553fb80
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the private complete-source coordinator plan. |
| inputs / outputs | Named valid Plan in; const PhysicalPlan& from Data.source_only out. |
| invariants | Its empty true query and alias routes are not the star answer or original-query proof. |
| ownership | Reference/span borrows Data held by a surviving Plan; copied scalar IDs/counts own no payload. Data is immutable. |
| failure | No validation/allocation/failure branch on a valid privately constructed Plan; noexcept accessor. |
| cost | Constant field/reference/span access; retaining and last-owner destruction are separate costs. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [docs/star.md](../../../../star.md) |

## B0009

[Lines 35–35](../../../../../src/planner/star.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L35:sha256:e3d84d2583b9d898313f82274bc9faa2dcd1191c9bd47d4933958c2d875cf8bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the original selected center occurrence ID. |
| inputs / outputs | Named valid Plan in; OccurrenceId from Data.center out. |
| invariants | The ID refers to the original general query, without occurrence compaction. |
| ownership | Reference/span borrows Data held by a surviving Plan; copied scalar IDs/counts own no payload. Data is immutable. |
| failure | No validation/allocation/failure branch on a valid privately constructed Plan; noexcept accessor. |
| cost | Constant field/reference/span access; retaining and last-owner destruction are separate costs. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [docs/star.md](../../../../star.md) |

## B0010

[Lines 36–36](../../../../../src/planner/star.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:dd36283ca041c55a8320d64f147e64c30114540acc20703d116203f2e22dd48a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the original physical center table ID. |
| inputs / outputs | Named valid Plan in; TableId from Data.center_table out. |
| invariants | Updates route by original complete physical catalog identity. |
| ownership | Reference/span borrows Data held by a surviving Plan; copied scalar IDs/counts own no payload. Data is immutable. |
| failure | No validation/allocation/failure branch on a valid privately constructed Plan; noexcept accessor. |
| cost | Constant field/reference/span access; retaining and last-owner destruction are separate costs. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [docs/star.md](../../../../star.md) |

## B0011

[Lines 37–37](../../../../../src/planner/star.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L37:sha256:61f3dbf056c74f96cff925a3e362a9fdba7d9be6b7c5a328f170f1c43a45d80f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report center arity from coordinate-slot count. |
| inputs / outputs | Named valid Plan in; size_t dimension from Data.satellites.size() out. |
| invariants | This d is center arity and is not automatically P2 structural dimension for all admitted head/satellite edge cases. |
| ownership | Reference/span borrows Data held by a surviving Plan; copied scalar IDs/counts own no payload. Data is immutable. |
| failure | No validation/allocation/failure branch on a valid privately constructed Plan; noexcept accessor. |
| cost | Constant field/reference/span access; retaining and last-owner destruction are separate costs. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [docs/star.md](../../../../star.md) |

## B0012

[Lines 38–38](../../../../../src/planner/star.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:40b48b9db261bc5074a6401a8035090ecbf27c1df4f432b67e9fcdc6257132b8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the distinct original head-variable count. |
| inputs / outputs | Named valid Plan in; size_t j from Data.distinct_head out. |
| invariants | Repeated output positions do not increase j or disappear from the separate ordered head map. |
| ownership | Reference/span borrows Data held by a surviving Plan; copied scalar IDs/counts own no payload. Data is immutable. |
| failure | No validation/allocation/failure branch on a valid privately constructed Plan; noexcept accessor. |
| cost | Constant field/reference/span access; retaining and last-owner destruction are separate costs. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [docs/star.md](../../../../star.md) |

## B0013

[Lines 39–39](../../../../../src/planner/star.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L39:sha256:96538c217b4a5cf02264eafe602997fcf4ca09711c32c0f1ebfb37747e6c8217
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the center-coordinate satellite-table map. |
| inputs / outputs | Named valid Plan in; span&lt;const optional&lt;TableId&gt;&gt; from Data.satellites out. |
| invariants | An absent entry means that free coordinate has no filtering source; original TableIds are preserved. |
| ownership | Reference/span borrows Data held by a surviving Plan; copied scalar IDs/counts own no payload. Data is immutable. |
| failure | No validation/allocation/failure branch on a valid privately constructed Plan; noexcept accessor. |
| cost | Constant field/reference/span access; retaining and last-owner destruction are separate costs. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [docs/star.md](../../../../star.md) |

## B0014

[Lines 40–40](../../../../../src/planner/star.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L40:sha256:b326415d2b08a203ec4e1cee302b8ba6ce101a4be6ebf0eaa504d07c84b038f3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow every ordered and repeated output coordinate. |
| inputs / outputs | Named valid Plan in; span&lt;const size_t&gt; from Data.head out. |
| invariants | Output order and repetition remain as admitted from the original head. |
| ownership | Reference/span borrows Data held by a surviving Plan; copied scalar IDs/counts own no payload. Data is immutable. |
| failure | No validation/allocation/failure branch on a valid privately constructed Plan; noexcept accessor. |
| cost | Constant field/reference/span access; retaining and last-owner destruction are separate costs. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [docs/star.md](../../../../star.md) |

## B0015

[Lines 41–41](../../../../../src/planner/star.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L41:sha256:11e0d7778de9fcf52c023110f507e789e7c6244e0006dabf68c39ff5ea67f9bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow completed cold work observations. |
| inputs / outputs | Named valid Plan in; const Usage& from Data.usage out. |
| invariants | Selected guard/mapping and source-only lowering counts remain separate from runtime and total physical costs. |
| ownership | Reference/span borrows Data held by a surviving Plan; copied scalar IDs/counts own no payload. Data is immutable. |
| failure | No validation/allocation/failure branch on a valid privately constructed Plan; noexcept accessor. |
| cost | Constant field/reference/span access; retaining and last-owner destruction are separate costs. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [docs/star.md](../../../../star.md) |

## B0017

[Lines 43–110](../../../../../src/planner/star.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L110:sha256:b9687ad6911791c05367263073ca66dff129423be15f09d0ee427102e22e8c12
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the literal central-relation/unary-satellite star and prepare its source-only coordinator privately. |
| inputs / outputs | Genuine direct-CQ general PhysicalPlan, explicit original center OccurrenceId and Limits in; immutable Plan retaining original/source-only plans, TableId/coordinate/head maps, j and Usage out. |
| invariants | Reject normalized/constant/contradictory routes, zero/incorrect center arity, nonvariable/repeated center terms, repeated physical tables, nonunary/nonvariable/duplicate-coordinate satellites and any hidden coordinate lacking a satellite. Genuine prior plan validation establishes in-range dense IDs/schemas. Preserve head order/repetition while j counts distinct coordinates. The source-only lowerer receives the complete original catalog/options/constraints and Query{}; no original join routes are executed and no height theorem is added. |
| ownership | Borrows general/query during checks. Private ordinary vectors/sets and source plan unwind on failure; final shared Data owns moved maps/source plus a retained unchanged general handle. This cold wrapper does not allocate a native execution allowance. |
| failure | star_work_limit or star_admission is thrown before publication; allocations and existing lower_tree failures propagate. std::make_shared constructs the final payload only after all guards and source-only lowering complete; caller general survives refusal. |
| cost | One selected shared grant charges entry, declared variables, center terms, atoms/satellite terms, head positions and hidden-coordinate checks. Ordered-set comparisons, copies, scalar widths, allocation and complete source-only lower/identity/validation cost are additional; lowering_work reports source.work(). |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt](../../../../../build/verification/v68-star-proof-v1/audit.txt), [Refactor.md](../../../../../Refactor.md) |

## B0018

[Lines 111–111](../../../../../src/planner/star.cpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L111:sha256:7ce4da34e53ef857ccbca38b56798af419ce9f5906e286057c2f7160c93a505e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the planner::star implementation namespace. |
| inputs / outputs | Final namespace brace/comment; no new input/output or admission step. |
| invariants | The public factory and getters remain in the intended opt-in namespace. |
| ownership | No plan/account ownership change. |
| failure | No executable failure branch. |
| cost | No runtime work. |
| Design | [src/planner/star.cpp](../../../../../src/planner/star.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp) |
