# `tests/unit/input_specialization_cache_test.cpp` — block usage map

[Source](../../../../../tests/unit/input_specialization_cache_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `083c4da9aa5b7a6bb8517443c80db5ff4e23afd3f21ff515de361a1c6b1751f6`. 218 lines partitioned into 24 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/input_specialization_cache_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 17–20](../../../../../tests/unit/input_specialization_cache_test.cpp#L17) | Type/record definition: struct SqlFamily |  · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../tests/unit/input_specialization_cache_test.cpp#L21) | Explanatory comments or spacing. |  |
| [B0004 · 22–36](../../../../../tests/unit/input_specialization_cache_test.cpp#L22) | Callable definition: SqlFamily normalized_family() | calls frontend::bind_sql, check, frontend::normalize_sql, std::move; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(bound), "X09 SQL bind failed");; returns {std::move(program), std::move(candidates)} · [reviewed contract](#b0004) |
| [B0005 · 37–37](../../../../../tests/unit/input_specialization_cache_test.cpp#L37) | Explanatory comments or spacing. |  |
| [B0006 · 38–46](../../../../../tests/unit/input_specialization_cache_test.cpp#L38) | Callable definition: CompiledProgram prepared(const PhysicalPlan& basis, program::InputPreparationLimits limits) | calls CompiledProgram::standalone, resource::MemoryAccount::create, options, work; returns CompiledProgram::prepare_inputs(account, interpreted, limits, &work); CompiledProgram::prepare_inpu… · [reviewed contract](#b0006) |
| [B0007 · 47–47](../../../../../tests/unit/input_specialization_cache_test.cpp#L47) | Explanatory comments or spacing. |  |
| [B0008 · 48–52](../../../../../tests/unit/input_specialization_cache_test.cpp#L48) | Callable definition: ps::Request height_only() | calls ; returns request · [reviewed contract](#b0008) |
| [B0009 · 53–53](../../../../../tests/unit/input_specialization_cache_test.cpp#L53) | Explanatory comments or spacing. |  |
| [B0010 · 54–57](../../../../../tests/unit/input_specialization_cache_test.cpp#L54) | Callable definition: ps::Selection select(const planner::CandidateSnapshot& candidates, const ps::Source& source, ps::PlanCache& cache) | calls complete, ps::select, height_only; returns complete(ps::select(candidates, source, height_only(), {}, &cache, ps::CacheUse::read_write)) · [reviewed contract](#b0010) |
| [B0011 · 58–58](../../../../../tests/unit/input_specialization_cache_test.cpp#L58) | Explanatory comments or spacing. |  |
| [B0012 · 59–65](../../../../../tests/unit/input_specialization_cache_test.cpp#L59) | Callable definition: void require_mode(const ps::Selection& selected, std::string_view source_sha256, const PhysicalOptions& options, program::InputEx… | calls check, plan, input_execution, physical_source_sha256; guard check(selected.plan().input_execution() == mode, message); · [reviewed contract](#b0012) |
| [B0013 · 66–66](../../../../../tests/unit/input_specialization_cache_test.cpp#L66) | Explanatory comments or spacing. |  |
| [B0014 · 67–100](../../../../../tests/unit/input_specialization_cache_test.cpp#L67) | Callable definition: void mode_order(const planner::CandidateSnapshot& candidates, std::string_view source_sha256, const PhysicalOptions& options, con… | calls ps::PlanCache::create, select, check, cache_observation; guard check(first.cache_observation().disposition == ps::CacheDisposition::inserted, · [reviewed contract](#b0014) |
| [B0015 · 101–101](../../../../../tests/unit/input_specialization_cache_test.cpp#L101) | Explanatory comments or spacing. |  |
| [B0016 · 102–133](../../../../../tests/unit/input_specialization_cache_test.cpp#L102) | Callable definition: void preparation_limits(const planner::CandidateSnapshot& candidates, std::string_view source_sha256, const PhysicalOptions& opti… | calls prepared, check, input_execution, physical_sha256; guard check(prepared_a.input_execution() == program::InputExecution::threaded_v1 && · [reviewed contract](#b0016) |
| [B0017 · 134–134](../../../../../tests/unit/input_specialization_cache_test.cpp#L134) | Explanatory comments or spacing. |  |
| [B0018 · 135–151](../../../../../tests/unit/input_specialization_cache_test.cpp#L135) | Callable definition: void legacy_interpreter_bytes(const planner::CandidateSnapshot& candidates, std::string_view source_sha256, const PhysicalOptions… | calls CompiledProgram::standalone, ps::PlanCache::create, select, check; guard check(from_plan.cache_observation().disposition == ps::CacheDisposition::inserted && · [reviewed contract](#b0018) |
| [B0019 · 152–152](../../../../../tests/unit/input_specialization_cache_test.cpp#L152) | Explanatory comments or spacing. |  |
| [B0020 · 153–185](../../../../../tests/unit/input_specialization_cache_test.cpp#L153) | Callable definition: void payload_budget(const planner::CandidateSnapshot& candidates, std::string_view source_sha256, const PhysicalOptions& options,… | calls ps::PlanCache::create, select, statistics, check; guard check(interpreter_charge != 0, "X09 interpreter cache payload charge is empty"); · [reviewed contract](#b0020) |
| [B0021 · 186–186](../../../../../tests/unit/input_specialization_cache_test.cpp#L186) | Explanatory comments or spacing. |  |
| [B0022 · 187–204](../../../../../tests/unit/input_specialization_cache_test.cpp#L187) | Callable definition: void backend(const SqlFamily& fixture, const PhysicalOptions& options) | calls planner::lower_normalized, candidate, tree, check; guard check(basis.normalized().has_value() && basis.options().indexed_storage == options.indexed_storage, · [reviewed contract](#b0022) |
| [B0023 · 205–206](../../../../../tests/unit/input_specialization_cache_test.cpp#L205) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0023) |
| [B0024 · 207–218](../../../../../tests/unit/input_specialization_cache_test.cpp#L207) | Callable definition: int main() | calls normalized_family, s04_runtime::options, backend, what; returns 0; 1; 1 loop sites · [reviewed contract](#b0024) |

## B0001

[Lines 1–16](../../../../../tests/unit/input_specialization_cache_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:a3c2c0443740e33c0fe7dc6b2dd7c64efcaa3bb273eda0bf81e412d838e8793f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the public selection API, normalized SQL frontend, C02 fixture and both backend options. |
| inputs / outputs | Header declarations in; one translation unit with anonymous test helpers and main out. |
| invariants | Uses public planner::selection::select and existing C02/test support; adds no private production hook. |
| ownership | Declarations own no runtime state; functions create local candidate/program/cache objects. |
| failure | Missing APIs or fixture declarations fail compilation. |
| cost | Compile-time declarations only. |
| Design | [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../selection.md) |

## B0002

[Lines 17–20](../../../../../tests/unit/input_specialization_cache_test.cpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L20:sha256:970026b5bd13cc1ab876cce019d46e7df66cf43c0cb90f7daed46f1b1c9aa645
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the normalized SQL program and proven candidate snapshot as one test fixture. |
| inputs / outputs | NormalizedSql and CandidateSnapshot in; owned SqlFamily value out. |
| invariants | The candidate family comes from exact C02 proof/provider execution over the normalized core. |
| ownership | The struct owns the normalized value and snapshot handles through backend scenarios. |
| failure | Member construction failures propagate from fixture setup. |
| cost | Small aggregate; proof/family work is performed by normalized_family(). |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0004

[Lines 22–36](../../../../../tests/unit/input_specialization_cache_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L36:sha256:de631f6a7b7fc7ec7caab054cd21e0ddfc3b5f1d9a5c75a5aa32c72aa56d99e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and normalize a real SQL query, then build its nonempty C02 family. |
| inputs / outputs | Catalog and fixed SQL in; normalized program and CandidateSnapshot out. |
| invariants | Checks bind/normalize success and uses c02_test::candidates, not a mocked candidate list. |
| ownership | Locals move into the returned SqlFamily; proof-backed candidate controls retain their normal ownership. |
| failure | Failed bind/normalize or an empty family throws and fails the executable. |
| cost | One finite fixture bind, normalization, exact proof and family generation. |
| Design | [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [tests/unit/selection_source_test.cpp](../../../../../tests/unit/selection_source_test.cpp) |

## B0006

[Lines 38–46](../../../../../tests/unit/input_specialization_cache_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L46:sha256:7227c993e71434fa76ce625829e167d6e75690fbfe1bed4ded283ca33e2ccbf9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a normalized physical basis with the requested input-work limits. |
| inputs / outputs | PhysicalPlan/limits in; threaded CompiledProgram in a receiving account out. |
| invariants | Indexed plans pass a work allowance derived from their per-operation grant; reference plans use the ordinary public overload. |
| ownership | The returned program retains its receiving account; local allowance/account handles do not outlive their owners. |
| failure | Preparation, account or work denial propagates and fails setup. |
| cost | Per invocation this constructs one finite input program; cache accounting is tested separately. |
| Design | [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/ir/input_program.hpp](../../../../../src/ir/input_program.hpp) |

## B0008

[Lines 48–52](../../../../../tests/unit/input_specialization_cache_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L52:sha256:df1b181749d4ba36dbe3b55863213573c38d638f81dda177e1fb04cc1507a81d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the constant height-only request used for every cache-source comparison. |
| inputs / outputs | No input; Request with Policy::height_only out. |
| invariants | Request policy stays identical so cache differences isolate source mode/limits. |
| ownership | Caller-owned scalar value. |
| failure | No special failure path. |
| cost | Scalar initialization only. |
| Design | [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../selection.md) |

## B0010

[Lines 54–57](../../../../../tests/unit/input_specialization_cache_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L57:sha256:55bb77650617058bf88b077ea546681f31da84b22367a856cf32c0272638c313
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the public selection factory with fixed policy and explicit read-write cache participation. |
| inputs / outputs | CandidateSnapshot/source/cache in; complete Selection out. |
| invariants | All regression calls use one public API/request; result exposes cache disposition and binding. |
| ownership | Selection owns its immutable result; caller keeps the PlanCache. |
| failure | Incomplete/failed selection throws through complete(). |
| cost | Normal finite selection plus lookup or insertion. |
| Design | [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../selection.md), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp) |

## B0012

[Lines 59–65](../../../../../tests/unit/input_specialization_cache_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L65:sha256:f3570e97f3b76f18143813934aea6f19c4fdaba0d667b0e83fb3aaedfff7dc32
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selected input mode and source/backend identity without assuming the chosen candidate tree. |
| inputs / outputs | Selection, source digest, physical options and expected mode in; assertion result out. |
| invariants | Checks physical_source_sha256 and backend options; another selected family member may have a different plan hash. |
| ownership | Borrows values from live arguments; creates no cache/account. |
| failure | Any mode/source/backend mismatch fails the test. |
| cost | Constant-sized accessor/equality checks. |
| Design | [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp) |

## B0014

[Lines 67–100](../../../../../tests/unit/input_specialization_cache_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L100:sha256:b574d71510ead045aba6de8032727747fc1b58d94480053cb43343f6cd089f34
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove cache separation in both interpreted/threaded orders and reuse within each mode. |
| inputs / outputs | One C02 family, same physical/source identity, interpreted/prepared sources and order flag in; cache assertions out. |
| invariants | Second distinct mode must insert a distinct binding; repeat lookup for each mode must hit its own exact binding. |
| ownership | Local PlanCache retains the two artifacts; Selection handles retain results during checks. |
| failure | Wrong-mode hit, collapsed key, unstable hit or counter mismatch fails the test. |
| cost | Four public selections per order: two inserts and two hits; runs on both backends. |
| Design | [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0016

[Lines 102–133](../../../../../tests/unit/input_specialization_cache_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L133:sha256:a763bf99058279831e55d77f876beb211986b7f863bdfd0a310cd86934b66fbc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate two successful threaded preparations with different limits and verify same-limit hits. |
| inputs / outputs | Two limit sets and common normalized source in; distinct bindings/insertions and repeat hits out. |
| invariants | Both sources keep threaded mode and source identity; cache binding distinguishes limits with all other inputs fixed. |
| ownership | Each prepared program has a receiving account; cache owns selected artifact copies. |
| failure | Preparation failure, aliased limits or same-limit miss fails the test. |
| cost | Two finite preparations, two insertions and two hits per backend. |
| Design | [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0018

[Lines 135–151](../../../../../tests/unit/input_specialization_cache_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L151:sha256:c3f8374e98f5f611e314471a191514a175d73b4792200adf0160dd75908163d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve legacy cache bytes for an interpreted PhysicalPlan and equivalent CompiledProgram. |
| inputs / outputs | Same normalized basis represented as both source forms; one insertion and one exact-binding hit out. |
| invariants | Both remain interpreted with unchanged SQL source/backend identity; binding text and byte length match. |
| ownership | Cache owns the inserted plan; both Selection handles survive checks. |
| failure | Miss or changed binding/mode/source fails the regression. |
| cost | Two public selections and byte/binding comparisons. |
| Design | [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0020

[Lines 153–185](../../../../../tests/unit/input_specialization_cache_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L185:sha256:6ae5b277dda9c344dec69771e10cf73e09cf8ee55ad587002ceab6b66547fb34
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check prepared table payload accounting and the one-under cache capacity boundary. |
| inputs / outputs | Interpreter/prepared artifacts, metadata_bytes and cache payload stats in; prepared rejection with empty cache and interpreter insertion under same cap out. |
| invariants | Prepared charge must be at least interpreter charge plus metadata_bytes; failed insertion leaves counters unchanged. |
| ownership | Each probe uses an isolated cache; program/source accounts stay live through checks. |
| failure | Missing charge, cache mutation, wrong failure resource or interpreter refusal fails the test. |
| cost | Two probes measure payload; one prepared insertion is rejected and one interpreter entry fits. |
| Design | [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [docs/selection_accounting.md](../../../../selection_accounting.md), [src/planner/ranking_payload.cpp](../../../../../src/planner/ranking_payload.cpp) |

## B0022

[Lines 187–204](../../../../../tests/unit/input_specialization_cache_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L187-L204:sha256:9b8e12bf4794a52ffa3f0df8b49d06ae26038480aae3922c1eed4dd43f7fdb9d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the cache regression suite for reference and indexed physical options. |
| inputs / outputs | Normalized SQL family/options in; lowered basis and mode/limit/payload checks out. |
| invariants | Basis remains normalized and carries the requested backend; prepared/interpreted sources preserve source identity. |
| ownership | All basis/program/cache owners are local to one backend suite. |
| failure | Any setup, preparation or cache failure propagates to main. |
| cost | Runs each scenario once for each backend option set. |
| Design | [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp) |

## B0023

[Lines 205–206](../../../../../tests/unit/input_specialization_cache_test.cpp#L205); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L205-L206:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous test namespace. |
| inputs / outputs | No runtime inputs or outputs. |
| invariants | Helpers remain translation-unit local. |
| ownership | Owns no values/resources. |
| failure | No runtime failure path. |
| cost | Compile-time scope closure only. |
| Design | [tests/unit/input_specialization_cache_test.cpp](../../../../../tests/unit/input_specialization_cache_test.cpp) |

## B0024

[Lines 207–218](../../../../../tests/unit/input_specialization_cache_test.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L207-L218:sha256:35788e36a2f5c07985a584cda28aeaebcc2e23b8297aa29cd316d3b0631eb42b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both-backend cache scenarios and report success or a concise failure. |
| inputs / outputs | No CLI arguments; construct one SQL/C02 fixture, run two backends, print success/return zero or print exception/return one. |
| invariants | Success output is emitted only after all cache assertions complete. |
| ownership | Stack locals own fixture/program/cache lifetimes through execution. |
| failure | Caught test exceptions print to stderr and become exit status one. |
| cost | One finite fixture and both backend scenario groups; no timing benchmark. |
| Design | [tests/unit/input_specialization_cache_test.cpp](../../../../../tests/unit/input_specialization_cache_test.cpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp) |
