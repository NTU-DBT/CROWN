# `tests/unit/statistics_capture_test.cpp` — block usage map

[Source](../../../../../tests/unit/statistics_capture_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d8c4b290f5a4a3733f62e2e4ef58967824d0f842c4f48010219026905e6fa522`. 189 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/statistics_capture_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../tests/unit/statistics_capture_test.cpp#L12) | Callable definition: void check(bool b) | calls std::runtime_error; guard void check(bool b){if(!b)throw std::runtime_error("C01 proposal assertion failed");} · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../tests/unit/statistics_capture_test.cpp#L13) | Callable definition: template&lt;class F&gt; void error(F f) | calls f, std::runtime_error · [reviewed contract](#b0003) |
| [B0004 · 14–16](../../../../../tests/unit/statistics_capture_test.cpp#L14) | Explanatory comments or spacing. | source comment (unverified): // Standalone native captures must bind the supplied DTO to the actual index, · [reviewed contract](#b0004) |
| [B0005 · 17–115](../../../../../tests/unit/statistics_capture_test.cpp#L17) | Callable definition: void accounted_index_metadata(bool indexed) | calls resource::MemoryAccount::create, std::string, AccountedLayout::freeze, AccountedIndexWork::create; guard check(table.size()==2 && table.revision()==revision);; returns stats::index(table,index,metadata,budget,work.get()); growth insert; 1 loop sites; source comment (unverified): // Standalone native captures must bind the supplied DTO to the actual index, · [reviewed contract](#b0005) |
| [B0006 · 116–116](../../../../../tests/unit/statistics_capture_test.cpp#L116) | Explanatory comments or spacing. |  |
| [B0007 · 117–189](../../../../../tests/unit/statistics_capture_test.cpp#L117) | Callable definition: int main() | calls insert, tuple, add_index, stats::projection; guard check(cy.cardinality==3 && cy.distribution.ndv==2 && cx.distribution.ndv==3);; returns t.index_keys(t.add_index(p)); growth insert; 4 loop sites; source comment (unverified): // 1: literal cardinality, projection NDV and exact support-style grouping. · [reviewed contract](#b0007) |

## B0001

[Lines 1–11](../../../../../tests/unit/statistics_capture_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:f48837c6f769c138b00ab0dc5620c5c93f78cf2d86d99abbc4327e77f3fe4fe4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import statistics, accounted layouts/tables/projections, arrays and test helpers for the two storage backends. |
| inputs / outputs | Headers and namespace aliases expose standalone statistics and actual native metadata/work recipes; no query is constructed by these imports. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/statistics_capture_test.cpp](../../../../../tests/unit/statistics_capture_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–12](../../../../../tests/unit/statistics_capture_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool b){if(!b)throw std::runtime_error("C01 proposal assertion failed");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a storage-capture test assertion. |
| inputs / outputs | Boolean enters; normal return or std::runtime_error exits. |
| invariants | The check does not catch production Error or allocator failure. |
| ownership | No references escape; exception owns its fixed diagnostic. |
| failure | False throws std::runtime_error; expected crown::Error is handled separately by error(). |
| cost | Failure path constructs std::runtime_error; success path is one branch. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 13–13](../../../../../tests/unit/statistics_capture_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void error(F f){try{f();}catch(const Error&){return;}throw std::runtime_error("expected native error");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a supplied operation to throw some native crown::Error. |
| inputs / outputs | Callable enters; returns normally only after catching Error; otherwise throws std::runtime_error. |
| invariants | Only the broad Error base is required for this fixture; targeted production-code checks live in other tests. |
| ownership | Callable and captured test state are borrowed for invocation; no returned result is retained. |
| failure | Propagates non-Error exceptions; failure to throw Error becomes runtime_error. |
| cost | One operation invocation and exception dispatch. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 14–16](../../../../../tests/unit/statistics_capture_test.cpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L16:sha256:8f5bc52f61603429081bf7655acda9e8e478c54607ae248129177a6367b9c512
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the index statistics regression identity boundary. |
| inputs / outputs | Adjacent comments describe complete descriptor equality across recreated native/legacy tokens. |
| invariants | A comment provides human context; actual checks are in accounted_index_metadata and statistics::index. |
| ownership | Source text only. |
| failure | No executable failure behavior. |
| cost | No runtime work. |
| Design | [tests/unit/statistics_capture_test.cpp](../../../../../tests/unit/statistics_capture_test.cpp), [docs/statistics.md](../../../../statistics.md) |

## B0005

[Lines 17–115](../../../../../tests/unit/statistics_capture_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L115:sha256:2225e10098b35aa56b25c98fa7e42c140cbefacda394eaa6320e00f9ac33be00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify exact accounted-index metadata and all relevant finite scan budgets. |
| inputs / outputs | For reference or indexed storage, construct two rows/two indexes under a64MiB account and4096-byte binding; reject wrong field/schema/variable/origin/context/order and accept recreated equal descriptors. |
| invariants | Actual source/projection tokens are returned. Metadata exhaustion publishes no exact prefix facts. Exact/one-under logical work/bytes and native structural grants are checked; zero grant fails before scan. Final table size/revision/invariants stay unchanged. |
| ownership | Fixture owns table, layouts, temporary legacy DTOs and allowances; every capture shares native metadata and owns ordinary exported distribution. |
| failure | Only specified invalid_statistics_request and storage_work_limit controls are accepted; other errors or failed literal comparisons fail the test. |
| cost | Fixed two-row/two-index matrix for each backend plus full4096-byte binding comparison; test-only allocation/scanning, no timing claim. |
| Design | [tests/unit/statistics_capture_test.cpp](../../../../../tests/unit/statistics_capture_test.cpp), [src/runtime/statistics.cpp](../../../../../src/runtime/statistics.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [docs/statistics.md](../../../../statistics.md) |

## B0007

[Lines 117–189](../../../../../tests/unit/statistics_capture_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact storage projection/index statistics, shared-budget exhaustion, cursor invalidation, journal barriers, and owning capture lifetime. |
| inputs / outputs | Run the fourteen original reference-table groups and the new descriptor/field/budget regression under each accounted storage backend, reporting sixteen groups. |
| invariants | Exact NDV/histogram/top-K match literal positional grouping; empty projection is one nullary key on nonempty table and zero on empty; row/work/byte/key/width caps preserve only justified facts; shared budget is not renewed; no-op preserves cursor revision, mutation invalidates, journal rejects reads/capture; saved result survives clear; dropped/dead/moved cursor cases fail safely. The two additional backend groups reject conflicting complete metadata and accept independently recreated equal descriptors; exact/one-under logical and storage grants and authentic incomplete metadata are checked. |
| ownership | ReferenceTable owns rows and cursor control; the captured distribution ci owns its values after table mutation/clear. Cursor objects borrow live index identity and are tested only against invalidation state. |
| failure | Expected invalid cursor/journal/table cases must throw crown::Error; budget exhaustion returns unknown; other assertion or allocation failures fail main. |
| cost | Uses fixed rows and several captures, ordered-map oracle, and four cursor lifetime cases. It verifies local API behavior, not runtime owner-state theorem or benchmark. Each new backend uses two rows, two indexes and a4096-byte binding; this is a correctness regression, not a performance benchmark. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |
