# `tests/unit/sql_aggregate_binding_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_binding_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Check genuine composed admission, origin/NULL decoding, identities, static-bootstrap metadata and explicit limits.

Snapshot SHA-256: `bbd1f4a775c4ce2ff1ab20425604a8a4692e10b426eaccd1322f4f32989dcb5f`. 235 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 10–14](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L10) | Callable definition: Catalog schema() | calls ; returns {1, {{@ , {{@ , ScalarType::int64, true}, {@ , ScalarType::string, true}, · [reviewed contract](#b0002) |
| [B0003 · 15–20](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L15) | Callable definition: SqlAggregateProgram compile(std::string_view sql, const Catalog& catalog = schema(), const SqlAggregateBindOptions& options = {}) | calls schema, bind_sql_aggregate, Error, std::move; returns std::get&lt;SqlAggregateProgram&gt;(std::move(result)) · [reviewed contract](#b0003) |
| [B0004 · 21–25](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L21) | Callable definition: void reject(std::string_view sql, std::string_view code, const SqlAggregateBindOptions& options = {}) | calls bind_sql_aggregate, schema, assert; guard assert(failure && failure-&gt;diagnostic.code == code); · [reviewed contract](#b0004) |
| [B0005 · 26–30](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L26) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, assert, statistics, resource::MemoryAccount::control_bytes; guard assert(account.statistics().current.allocations == 1 && · [reviewed contract](#b0005) |
| [B0006 · 31–33](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L31) | Explanatory comments or spacing. | source comment (unverified): // Only original SQL reaches the factory; no BoundSql/opaque descriptor editing · [reviewed contract](#b0006) |
| [B0007 · 34–58](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L34) | Callable definition: void joined_nullable_binding() | calls compile, assert, inputs, size; guard assert(program.inputs().size() == 3 && program.reference_columns().size() == 7);; 1 loop sites; source comment (unverified): // Only original SQL reaches the factory; no BoundSql/opaque descriptor editing · [reviewed contract](#b0007) |
| [B0008 · 59–59](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L59) | Explanatory comments or spacing. |  |
| [B0009 · 60–79](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L60) | Callable definition: void aliases_names_and_identity() | calls compile, assert, inputs, size; guard assert(a.inputs().size() == 1 && a.reference_columns().size() == 5 && a.kernel_program().measures()…; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 80–82](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L80) | Explanatory comments or spacing. | source comment (unverified): // Equal values from WHERE/JOIN/NULL normalization are not SQL grouping identity. · [reviewed contract](#b0010) |
| [B0011 · 83–111](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L83) | Callable definition: void grouping_origin_controls() | calls reject, compile, assert, inputs; guard assert(alias.inputs().size() == 1 && alias.inputs()\[0\].origin.occurrence == OccurrenceId{0} &&; 2 loop sites; source comment (unverified): // Equal values from WHERE/JOIN/NULL normalization are not SQL grouping identity. · [reviewed contract](#b0011) |
| [B0012 · 112–112](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L112) | Explanatory comments or spacing. |  |
| [B0013 · 113–132](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L113) | Callable definition: void count_star_constants_and_bootstrap() | calls compile, assert, inputs, empty; guard assert(count.inputs().empty() && count.source_program().outputs().empty());; source comment (unverified): // Neither kernel was implicitly loaded: the real coordinator owns the · [reviewed contract](#b0013) |
| [B0014 · 133–135](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L133) | Explanatory comments or spacing. | source comment (unverified): // Genuine source binding keeps the raw bigint column and its origin. Only the · [reviewed contract](#b0014) |
| [B0015 · 136–148](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L136) | Callable definition: void varying_integer_binding() | calls compile, assert, inputs, size; guard assert(program.inputs().size() == 1 && program.inputs()\[0\].type.kind == SqlKind::int64);; source comment (unverified): // Genuine source binding keeps the raw bigint column and its origin. Only the · [reviewed contract](#b0015) |
| [B0016 · 149–149](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L149) | Explanatory comments or spacing. |  |
| [B0017 · 150–179](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L150) | Callable definition: void parameters_and_rejections() | calls compile, schema, assert, identity; guard assert(first.identity().original_sql == second.identity().original_sql && first.identity().kernel =… · [reviewed contract](#b0017) |
| [B0018 · 180–180](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L180) | Explanatory comments or spacing. |  |
| [B0019 · 181–225](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L181) | Callable definition: void receiver_work_and_lifetime() | calls reset, resource::MemoryAccount::create, bind_sql_aggregate_into, schema; guard if (exact) assert(std::get&lt;SqlAggregateProgram&gt;(result).work().origin_binding == binding);; 3 loop sites · [reviewed contract](#b0019) |
| [B0020 · 226–226](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L226) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0020) |
| [B0021 · 227–235](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L227) | Callable definition: int main() | calls joined_nullable_binding, aliases_names_and_identity, grouping_origin_controls, count_star_constants_and_bootstrap; returns 0; 1 · [reviewed contract](#b0021) |

## B0001

[Lines 1–9](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/frontend/sql_aggregate.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import only public original-SQL composition/types and ordinary assertion helpers for finite binding controls. |
| inputs / outputs | Imports, declarations, comments, closure or spacing in the exact stated block. |
| invariants | No SQL admission, plan authority, output publication or execution claim from this scaffolding. |
| ownership | No new executable ownership beyond declarations explicitly described in surrounding cards. |
| failure | No runtime failure is handled by these lines. |
| cost | No runtime work from comments/spacing/declarations. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0002

[Lines 10–14](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog schema() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide an actual nullable Catalog for joined aggregate factory tests. |
| inputs / outputs | r has nullable id/g/x and flag; s has nullable id/y. |
| invariants | Uses only real ScalarType alternatives; no fabricated int32 catalog column. |
| ownership | Ordinary cold caller-owned fixture Catalog. |
| failure | Allocation can fail outside production ownership; no program authority exists yet. |
| cost | Two small schemas. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0003

[Lines 15–20](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateProgram compile(std::string_view sql, const Catalog& catalog = schema(),
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile fixture SQL solely through the authentic public original-SQL factory. |
| inputs / outputs | SQL/Catalog/options return SqlAggregateProgram; actual diagnostic becomes test Error. |
| invariants | No BoundSql mutation, opaque descriptor construction or caller-fed logical rows. |
| ownership | Returned factory program owns receiver metadata; input fixtures may later die. |
| failure | Rejection fails the fixture; native execution is not performed. |
| cost | Cold compiler call plus constant variant handling. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0004

[Lines 21–25](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reject(std::string_view sql, std::string_view code, const SqlAggregateBindOptions& options = {}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert explicit unsupported/admission diagnostic codes at the authentic factory boundary. |
| inputs / outputs | Original SQL, expected code and options enter bind_sql_aggregate. |
| invariants | Require BindingDiagnostic and exact actual code; no admitted fallback is substituted. |
| ownership | Result/diagnostic remain local cold fixture owners. |
| failure | The assertion reports a missing or wrong diagnostic. Parent V2 test and maintained Debug/SAN cohorts passed; a rejection control does not exercise runtime execution. |
| cost | One bounded compile attempt per case. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0005

[Lines 26–30](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert full retained receiver release after compilation/result scopes end. |
| inputs / outputs | MemoryAccount invariants/statistics must show controller-only allocation. |
| invariants | Does not compare total cold parser allocations to receiver allocations or claim native workspace is accounted. |
| ownership | External account handle intentionally keeps its controller alive. |
| failure | An invariant/statistics mismatch fails the test. Parent V2 and Debug/SAN receipts passed the controller-only checks; this observes receiver-owned allocations only. |
| cost | Constant account diagnostics. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0006

[Lines 31–33](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text

// Only original SQL reaches the factory; no BoundSql/opaque descriptor editing
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State that boundary controls never manufacture edited bound metadata or hand-fed aggregate input. |
| inputs / outputs | Imports, declarations, comments, closure or spacing in the exact stated block. |
| invariants | No SQL admission, plan authority, output publication or execution claim from this scaffolding. |
| ownership | No new executable ownership beyond declarations explicitly described in surrounding cards. |
| failure | No runtime failure is handled by these lines. |
| cost | No runtime work from comments/spacing/declarations. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0007

[Lines 34–58](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void joined_nullable_binding() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check nullable joined aggregate binding and complete decoder coverage through the genuine SQL factory. |
| inputs / outputs | Original inner-join SQL includes GROUP BY, COUNT forms, SUM/AVG and SUM(1). |
| invariants | Expect 7 cold references/outputs, 3 canonical inputs, actual head coverage, two real source occurrences and matching nullable payload/presence/type descriptors. |
| ownership | Only immutable program views are inspected; source SQL is independently rebound by the real row factory. |
| failure | Assertion failures fail the unit process. Parent receipts report the V2 test and maintained Debug/SAN 15-test cohorts passed; this test does not execute row updates. |
| cost | One joined compile and one genuine source rebind. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), src/frontend/sql_rows_eval.hpp:55-63, src/frontend/sql_rows_value.hpp:65-74, src/runtime/sql_rows.cpp:446-460, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0009

[Lines 60–79](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void aliases_names_and_identity() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify same-origin aliases, original output names, and independently scoped identity digests. |
| inputs / outputs | Qualified/unqualified x, original comments, AVG scale, schema versions and quoted names. |
| invariants | Five original references to one genuine BoundColumn/type yield one kernel input, regardless of newly appended pre-bind ExpressionIds. |
| ownership | Only immutable factory products are inspected; caller data is ordinary cold input. |
| failure | Assertion failures fail the unit process. Parent V2 test and Debug/SAN cohorts passed; the identity assertions do not prove runtime recovery. |
| cost | Fixed compile variants. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0010

[Lines 80–82](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text

// Equal values from WHERE/JOIN/NULL normalization are not SQL grouping identity.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label direct original-SQL controls for value equality versus original grouping identity. |
| inputs / outputs | Two comments apply to the new grouping_origin_controls fixture. |
| invariants | No edited descriptor or fabricated program is used by those tests. |
| ownership | No owner from comments. |
| failure | The comment adds no executable behavior; the referenced grouping fixture passes in parent V2 Debug/SAN receipts. |
| cost | No executable cost. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0011

[Lines 83–111](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void grouping_origin_controls() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise exact grouping blockers and positive physical-origin/alias controls at the genuine factory boundary. |
| inputs / outputs | Three reproduced negatives; same-origin qualifier positive; valid equal-payload/NULL/self-join grouped pairs; merged USING/NATURAL rejection; qualified USING; 512 COUNT refs. |
| invariants | Expect invalid originals to return ungrouped_column, distinct origins to remain separate despite identical decoders, and 512 same physical refs to give one input/two native nullable fields. |
| ownership | Only original SQL/Catalog enter real factory; immutable origins/decoder/native arity are inspected, no logical rows fed. |
| failure | Assertions fail on wrong diagnostics or merged origins. Parent V2 test and grouping reproducer passed, including the three ungrouped-column negatives; no aggregate runtime is exercised. |
| cost | Fixed small query corpus plus one 512-ref cold compile, not bag expansion. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0013

[Lines 113–132](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void count_star_constants_and_bootstrap() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify nullary source projection, constant/NULL decoding, and the coordinator-only static bootstrap marker. |
| inputs / outputs | COUNT(*), constant/NULL aggregates, WHERE x IS NULL, original no-FROM and no-FROM WHERE FALSE. |
| invariants | Nullary sources have no dummy payload; grounded NULL reads actual initial slot; all kernels have explicit FROM; only zero-occurrence source gets static 0/1 marker. |
| ownership | Metadata-only checks; no caller row seeds or arbitrary sequence setters occur. |
| failure | Assertions fail on incorrect metadata. Parent V2 test and Debug/SAN cohorts passed; the fixture does not perform bootstrap, update, or recovery. |
| cost | Five small source/kernel composition cases. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), src/frontend/sql_rows_eval.hpp:55-63, src/frontend/sql_rows_value.hpp:65-74, src/runtime/sql_rows.cpp:446-460, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0014

[Lines 133–135](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L133); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L135:sha256:c4013ace3f19a03c5ff58b543a908eefffc88aa5c195b4ce1297cbebf48bea7b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Genuine source binding keeps the raw bigint column and its origin. Only the kernel carries the deduplicated integer-cast guard and SQL result type. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_binding_test.cpp](../../../../../tests/unit/sql_aggregate_binding_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 136–148](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void varying_integer_binding()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check genuine original SQL source/kernel types and exact rebinding for varying integer casts. |
| inputs / outputs | Raw grouping plus narrow/raw/widened SUM/AVG/COUNT -&gt; actual factory programs and binding images. |
| invariants | Source and group stay bigint; one guard per raw slot; final argument width selects bigint versus numeric SUM; repeated original SQL reproduces exact binding bytes. |
| ownership | Factory handles own both genuine source and kernel metadata. |
| failure | Wrong type/guard/sharing/identity fails assertions. |
| cost | Finite cold binding/rebinding fixture; no native runtime execution in this function. |
| Design | [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0017

[Lines 150–179](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void parameters_and_rejections() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check source BindOptions/parameter forwarding and rejection of unsupported aggregate syntax. |
| inputs / outputs | WHERE parameter values change identities; origin_binding is nonzero/equal for identical SQL/types; missing value remains real aggregate_source/parameters rejection. |
| invariants | Aggregate argument parameters, unsupported original clauses, bigint-to-text conversion and computed arguments reject through real factories. Integer narrowing is separately admitted; derived diagnostic offsets remain cleared. |
| ownership | Caller parameters survive synchronous compilation; actual source owns validated values; no BoundSql is supplied externally. |
| failure | Wrong phase/code/identity/offset fails an assertion. Source predicate parameters remain separate from aggregate argument parameters; execution results are recorded in receiving receipts. |
| cost | Finite cold compile/rejection cases and counter checks. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0019

[Lines 181–225](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void receiver_work_and_lifetime() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate selected origin/composition work and retained receiving-account byte limits and lifetime. |
| inputs / outputs | Calibrate actual origin_binding and composition work; exact/one-under BindLimits/own limits and receiver peak; expire original SQL/Catalog. |
| invariants | Both genuine source binds use identical real declared options; work reports are not full cold native allocation/CPU meters. |
| ownership | Programs release receiver allocations after result scope; held opaque handle retains actual metadata. |
| failure | Exact/one-under work and account assertions fail the test when admission differs. Parent V2 test and Debug/SAN cohorts passed; these controls do not inject C malloc failure or meter cold CPU/global heap. |
| cost | Finite calibrations, two caps per checked resource and one lifetime case. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0020

[Lines 226–226](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L226); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
}  // namespace
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate fixture definitions or close the anonymous scope without executable behavior. |
| inputs / outputs | Imports, declarations, comments, closure or spacing in the exact stated block. |
| invariants | No SQL admission, plan authority, output publication or execution claim from this scaffolding. |
| ownership | No new executable ownership beyond declarations explicitly described in surrounding cards. |
| failure | No runtime failure is handled by these lines. |
| cost | No runtime work from comments/spacing/declarations. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0021

[Lines 227–235](../../../../../tests/unit/sql_aggregate_binding_test.cpp#L227); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the six direct original-SQL binding control groups and report process success or exception. |
| inputs / outputs | Six fixture functions and standard success/exception exit path. |
| invariants | No native runtime/source/group/session integration, recovery behavior, or global allocation-fault proof follows from this finite binding test. |
| ownership | Local fixture owners unwind normally. |
| failure | The top-level exception boundary prints the failure and exits nonzero. Parent private V2 and maintained Debug/SAN receipts pass; no runtime-coordinator, recovery, or native malloc-fault claim follows. |
| cost | Bounded declared original-SQL corpus. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Foreign AST ownership and costs](../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../sql_aggregate_binding.md), [src/frontend/sql_aggregate.cpp](../../../../../src/frontend/sql_aggregate.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |
