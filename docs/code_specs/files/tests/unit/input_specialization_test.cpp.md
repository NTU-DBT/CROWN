# `tests/unit/input_specialization_test.cpp` — block usage map

[Source](../../../../../tests/unit/input_specialization_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a64b5dcde6b42607a0eeac7480b60dac47434ee04f2fbe82a2a943a7e84d42a2`. 241 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/input_specialization_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../tests/unit/input_specialization_test.cpp#L16) | Callable definition: void check(bool value,const char* message) | calls std::runtime_error; guard void check(bool value,const char* message) {if(!value)throw std::runtime_error(message);} · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../tests/unit/input_specialization_test.cpp#L17) | Type/record definition: struct Case |  · [reviewed contract](#b0003) |
| [B0004 · 18–30](../../../../../tests/unit/input_specialization_test.cpp#L18) | Callable definition: Case compile(std::string_view text,const Catalog& catalog,bool indexed) | calls frontend::admit_sql, check, has_value, std::move; guard check(admitted.status==frontend::AdmissionStatus::admitted && admitted.program.has_value(),"special…; returns {std::move(sql),std::move(plan)} · [reviewed contract](#b0004) |
| [B0005 · 31–38](../../../../../tests/unit/input_specialization_test.cpp#L31) | Callable definition: CompiledProgram prepared(const resource::MemoryAccount& account,const CompiledProgram& source, program::InputPreparationLimits li… | calls options, work, CompiledProgram::prepare_inputs; returns CompiledProgram::prepare_inputs(account,source,limits,&work); CompiledProgram::prepare_inputs(accou… · [reviewed contract](#b0005) |
| [B0006 · 39–45](../../../../../tests/unit/input_specialization_test.cpp#L39) | Callable definition: CompiledProgram frozen(const resource::MemoryAccount& account,const CompiledProgram& source) | calls options, work, CompiledProgram::freeze; returns CompiledProgram::freeze(account,source,&work); CompiledProgram::freeze(account,source) · [reviewed contract](#b0006) |
| [B0007 · 46–55](../../../../../tests/unit/input_specialization_test.cpp#L46) | Callable definition: Relation expected(const frontend::NormalizedSql& sql,const Database& physical) | calls resize, size, frontend::adapt_row, insert; returns frontend::map_sql_result(sql,reference::evaluate(sql.core_catalog,sql.core,core)); growth insert, resize; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 56–60](../../../../../tests/unit/input_specialization_test.cpp#L56) | Callable definition: Relation snapshot(runtime::DeltaRuntime& owner) | calls results, next, check, insert; guard while(auto tuple=cursor.next())check(result.insert(storage::export_row(tuple-&gt;values())).second,"du…; returns result; growth insert; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 61–61](../../../../../tests/unit/input_specialization_test.cpp#L61) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 62–66](../../../../../tests/unit/input_specialization_test.cpp#L62) | Callable definition: Changes apply(runtime::DeltaRuntime& owner,const PhysicalSetUpdate& update) | calls next, check, emplace, storage::export_row; guard while(auto tuple=epoch.next())check(result.emplace(tuple-&gt;operation,storage::export_row(tuple-&gt;tupl…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 67–72](../../../../../tests/unit/input_specialization_test.cpp#L67) | Callable definition: Changes difference(const Relation& before,const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 73–101](../../../../../tests/unit/input_specialization_test.cpp#L73) | Callable definition: void input_work(const CompiledProgram& plain,const CompiledProgram& threaded,const Catalog& catalog) | calls inputs, emplace_back, std::string, Date::parse; guard check(bool(left)==bool(right) && (!left \|\| left-&gt;values()==right-&gt;values()),"prepared input differs…; growth emplace_back, push_back; 4 loop sites; source comment (unverified): // A real just-short scalar grant must fail in either executor, without a · [reviewed contract](#b0012) |
| [B0013 · 102–151](../../../../../tests/unit/input_specialization_test.cpp#L102) | Callable definition: void bounds(const CompiledProgram& source,const CompiledProgram& threaded) | calls resource::MemoryAccount::create, statistics, input_preparation, prepared; guard check(denied && receiver.statistics().current==before,"preparation denial retained state/metadata");; 2 loop sites; source comment (unverified): // Before the fix, analyze consumed this one excess step and made the · [reviewed contract](#b0013) |
| [B0014 · 152–192](../../../../../tests/unit/input_specialization_test.cpp#L152) | Callable definition: void scenario(std::string_view text,const Catalog& catalog,const std::vector&lt;PhysicalSetUpdate&gt;& updates,bool indexed) | calls compile, CompiledProgram::standalone, resource::MemoryAccount::create, prepared; guard check(plain.input_execution()==program::InputExecution::interpreted_v1 &&; growth insert, resize; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 193–216](../../../../../tests/unit/input_specialization_test.cpp#L193) | Callable definition: void replan(bool indexed) | calls c02_test::fixture, planner::minimum_tree, check, has_value; guard check(native_minimum.tree.has_value(),"plain CQ fixture has no tree");; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 217–217](../../../../../tests/unit/input_specialization_test.cpp#L217) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 218–241](../../../../../tests/unit/input_specialization_test.cpp#L218) | Callable definition: int main() | calls std::move, Date::parse, Decimal::parse, row; returns Row{x,std::move(tag),flag,Date::parse(@ ),Decimal::parse(@ )}; 1; growth insert; 2 loop sites · [reviewed contract](#b0017) |

## B0001

[Lines 1–15](../../../../../tests/unit/input_specialization_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:ceb25edf0bd11b399c3f9da0b7623eee98561124072ca95ae58fd892b0019d2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind Release-active specialization checks to genuine planners, native runtime and independent reference evaluation. |
| inputs / outputs | Admit/lower/program/runtime/physical IO and existing proof fixtures; finite 64MiB and fixed work test grants. |
| invariants | No assert-dependent acceptance; test checks remain active under NDEBUG. Reference frontend adaptation and relational oracle do not call the prepared worker. |
| ownership | Test process owns fixtures and finite accounts; no installed API/runtime overhead. |
| failure | Missing dependencies are compile diagnostics; test exceptions are handled at main. |
| cost | Test-only constants/includes; no production hot path. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0002

[Lines 16–16](../../../../../tests/unit/input_specialization_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L16:sha256:a9ff6b3e11dc9998d0f1ef41a6eca18b8a53aed57f3c6ee1c691842d0b35c90b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make semantic checks effective in Release builds. |
| inputs / outputs | Boolean condition and concrete message; throws on false. |
| invariants | Never depends on assert/NDEBUG. |
| ownership | Borrows message; exception owns diagnostic. |
| failure | Runtime_error reaches test main failure exit. |
| cost | Constant branch per check; test-only. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0003

[Lines 17–17](../../../../../tests/unit/input_specialization_test.cpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:0d8ac23aeeb7ab93b30e10691f5a9d9498f404637a3465c52c4862f757849f3b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep admitted SQL and its physical lowering together in test fixtures. |
| inputs / outputs | Owning NormalizedSql and PhysicalPlan DTO. |
| invariants | Fixture is data, not proof authority; compile obtains genuine admission/minimum. |
| ownership | Owns ordinary test DTOs outside native query accounts. |
| failure | Ordinary fixture allocation may fail; no production behavior. |
| cost | Fixture metadata size only. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0004

[Lines 18–30](../../../../../tests/unit/input_specialization_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L30:sha256:7e6610ef651dfd34d1b15fc3531efa5614e2e8c42f70b65612851ad9231caef5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a genuinely admitted test source for either storage backend. |
| inputs / outputs | SQL/catalog/backend in; normalized SQL and lower_normalized physical plan out. |
| invariants | Active routes obtain real minimum_tree; constant_empty uses canonical empty executable tree, distinct from retained original-body structural witness. |
| ownership | Returns owning compiler DTOs; temporary admission/proof objects are test-local. |
| failure | Admission/minimum errors fail with concrete test diagnostic; lower errors propagate. |
| cost | Cold genuine compiler/planner work per finite test case. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0005

[Lines 31–38](../../../../../tests/unit/input_specialization_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L38:sha256:f403362bbd04ea6ac712b607b4801befe03e70d914d278a71474d2d4d49d41b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare through the real native public factory with explicit indexed authority. |
| inputs / outputs | Receiving account/source/limits; indexed path borrows a fresh test-declared capped per_operation allowance, reference path needs no indexed allowance. |
| invariants | No compiler-MAX allowance is passed to indexed receiving admission; production cap checks remain exercised. |
| ownership | Returned program owns receiver metadata; allowance is local for this test operation. |
| failure | Real preparation failures propagate to test/denial controls. |
| cost | Actual cold receiving base copy/preparation cost; no mock instructions. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0006

[Lines 39–45](../../../../../tests/unit/input_specialization_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L45:sha256:57024167cfdb7dcf0f79e99936d4ae3a797a019d8e7ccf439c94294dd4581391
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise public freeze with the backend-specific receiving grant. |
| inputs / outputs | Receiving account/source in; real frozen program out. |
| invariants | Prepared source mode is preserved by the factory, and indexed allowance stays finite/capped. |
| ownership | Result owns receiver metadata; source stays borrowed. |
| failure | Real freeze/resource faults propagate. |
| cost | Cold full program admission; test-only wrapper. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0007

[Lines 46–55](../../../../../tests/unit/input_specialization_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L55:sha256:39ff0ffe60dde5c4bfae133695a73d9aa98922b905834f5f2020867a71a9e62f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact SQL snapshot independently of prepared instruction execution. |
| inputs / outputs | Normalized SQL and physical set Database; per-occurrence frontend::adapt_row core database then reference::evaluate and map_sql_result. |
| invariants | Rebuilds set state and SQL result definition from source each prefix. Does not use CompiledProgram::adapt_input or native support state for expected answer. |
| ownership | Owns independent ordinary database/result sets; physical input remains borrowed. |
| failure | Oracle/adaptation errors fail the test instead of inventing an expected result. |
| cost | Full recomputation is intentionally acceptable for tiny correctness cases. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0008

[Lines 56–60](../../../../../tests/unit/input_specialization_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L60:sha256:3ba825285495930e0dfd9db555477d95ebb8458970037eb5650f7c0878bbae3e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain actual SQL results and reject duplicate native snapshot rows. |
| inputs / outputs | Native DeltaRuntime in; ordinary Relation set out. |
| invariants | Cursor uses genuine runtime result view; each returned tuple must be unique. |
| ownership | Result owns exported rows; cursor and borrowed tuple lifetimes stay inside function. |
| failure | Cursor/native/duplicate errors fail test. |
| cost | Full output drain/copy, outside production primitive. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0009

[Lines 61–61](../../../../../tests/unit/input_specialization_test.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L61:sha256:718f6d53acee3617cae723680a007c640036d28851bb778f292a47695b610941
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent expected actual signed changes as operation/row pairs. |
| inputs / outputs | Test-only ordered set alias. |
| invariants | Set preserves operation tag and rejects identical repeated signed records. |
| ownership | Owns row values. |
| failure | Alias itself cannot fail. |
| cost | Output-size storage in tests. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0010

[Lines 62–66](../../../../../tests/unit/input_specialization_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L66:sha256:e7e1a0fc3d0862dc544e50040ad05689d56a000c650323257b434b7352c668d8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit a real native epoch and drain exact signed changes. |
| inputs / outputs | Owner and physical set update in; distinct operation/row changes out. |
| invariants | Duplicate signed records fail; this does not infer deltas only from final snapshot. |
| ownership | Epoch lease is released on return; exported rows are owned by test set. |
| failure | Real update/delta/duplicate exceptions fail test. |
| cost | Full native update and delta drain. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0011

[Lines 67–72](../../../../../tests/unit/input_specialization_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L72:sha256:6131d2ed73d70cc3b25873af30f22c433a0ecf4b12a784204e5fb515fd0ee752
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive reference signed set changes by ordinary before/after difference. |
| inputs / outputs | Independent before/after Relation sets; erase before-only and insert after-only pairs. |
| invariants | Implements exact set CP output definition without native support state or prepared evaluator. |
| ownership | Owns result pair set and copied rows. |
| failure | Ordinary allocation exceptions fail test. |
| cost | Finite set membership/copy work proportional to both snapshots. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0012

[Lines 73–101](../../../../../tests/unit/input_specialization_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L101:sha256:89bcddfa23d832ed1501e12a096c0e7e7c0115dad5589a358a7dc8979468ac7b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare scalar/NULL output and exact consumed IndexWork for both adapters. |
| inputs / outputs | Plain and prepared source plus catalog; one valid typed row per real port and real one-short scalar allowance controls. |
| invariants | Native adapted tuples and remaining five-domain grants must match. Just-short denial uses actual public code and produces no caller tuple/refill. |
| ownership | Test owns scalar row/views and temporary tuples; both compiled sources remain borrowed. |
| failure | Unexpected mismatch or missing storage_work_limit denial fails Release-active check. |
| cost | Small actual per-port executions; not an exhaustive scalar-domain theorem. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0013

[Lines 102–151](../../../../../tests/unit/input_specialization_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L151:sha256:5128243d9c7fbdf34124aceb9b2767bd4edb0f63d33ed3c4320b06944ed8edb4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check meaningful cold preparation work/cap/account and original indexed-grant boundaries. |
| inputs / outputs | Genuine source/prepared usage; zero, exact, one-under, low-memory, missing grant, exact cap and one-over-cap controls. |
| invariants | One-over indexed allowance must reject unchanged before analysis consumes it for both prepare and freeze(prepared). Failure leaves current account state unchanged while successful owner release returns it. Work/peak refund is not asserted. |
| ownership | Temporary receiver/tiny accounts own all attempted metadata; source remains immutable. |
| failure | Only documented work/capacity/contract/memory denials count; unrelated failures do not satisfy controls. |
| cost | Finite repeated actual admission; no huge fault sweep or runtime overhead. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0014

[Lines 152–192](../../../../../tests/unit/input_specialization_test.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L152-L192:sha256:e974dbb33d4e09010c0646f072997570b9529e50a3b06934a7b3fbad0a60ab7d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check both modes through real updates, ownership transfer and checkpoint reconstruction. |
| inputs / outputs | SQL/catalog/valid physical updates/backend; compare independent every-prefix snapshot and signed differences. |
| invariants | Physical/source hashes and serialized plan stay identical. Compiler account can retire. Receiving freeze preserves mode. Actual native restore with prepared CompiledProgram preserves mode; PhysicalPlan-only reconstruction defaults interpreter until explicit preparation. Restored continuation must match. |
| ownership | Separate finite owners/accounts and detached prepared copy test lifetime. Checkpoint bytes are owned during restore. |
| failure | Every source/result/work/account/mode/restore discrepancy fails the executable test. |
| cost | Tiny full recomputation and native execution per prefix; no performance or power-loss claim. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0015

[Lines 193–216](../../../../../tests/unit/input_specialization_test.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L193-L216:sha256:0e1de06a2bfc04ee036f4ec1f8fdcc785bcecc9643e5d1e92d4459297ea23e88
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check actual-basis mode preservation across candidate replans and reject plain-CQ false mode labels. |
| inputs / outputs | Genuine c02 fixture/proof family and normalized SQL basis; both replan and replan_into. |
| invariants | Plain CQ preparation rejects without retained receiving allocation, plain freeze stays interpreted. Repeated canonical-basis flattening keeps actual threaded mode and preserves adapter values/work. |
| ownership | Each new graph belongs to explicit account; canonical source owns borrowed views, not prior graph chains. |
| failure | Missing proof/family/mode/work match fails test; native replan faults propagate. |
| cost | Small genuine candidate family only; no unimplemented search guarantee. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0016

[Lines 217–217](../../../../../tests/unit/input_specialization_test.cpp#L217); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L217-L217:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close test fixture helper scope. |
| inputs / outputs | Namespace closure. |
| invariants | No test is disabled by this syntax. |
| ownership | No independent owner. |
| failure | No failure. |
| cost | No runtime work. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0017

[Lines 218–241](../../../../../tests/unit/input_specialization_test.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L218-L241:sha256:b38b1908ec1368aad9bc8e62cc41d934928e4535f6de1a4ed80582e150b91bb0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the finite independent scalar/SQL/lifetime/resource/replan/recovery matrix for both backends. |
| inputs / outputs | Ten admitted SQL shapes including date/decimal/string, casts/repeated/fixed projections, NULL logic, aliases, EXISTS and constant false; duplicate/absent set updates. |
| invariants | Checks execute in Release and sanitizer; genuine native/independent results must agree. Physical NULL ingestion and arbitrary unsupported SQL remain outside admitted scope. |
| ownership | Main owns catalog/update corpus; each scenario releases finite accounts/owners. |
| failure | Any exception emits stderr and nonzero exit; success emits one precise finite PASS line. |
| cost | Bounded unit workload; no timing or universal correctness inference. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |
