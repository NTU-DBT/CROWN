# `src/runtime/statistics.cpp` — block usage map

[Source](../../../../../src/runtime/statistics.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `4c486c1ec759956b3cca52130e5e6fc308a0a43ff871b04cc3554d123f9625c1`. 254 lines partitioned into 29 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../src/runtime/statistics.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 12–15](../../../../../src/runtime/statistics.cpp#L12) | Callable definition: void charge(std::uint64_t& used,std::uint64_t cap,std::uint64_t n) | calls  · [reviewed contract](#b0002) |
| [B0003 · 16–20](../../../../../src/runtime/statistics.cpp#L16) | Callable definition: std::uint64_t payload_bytes(std::size_t count,std::size_t width) | calls max; returns static_cast&lt;std::uint64_t&gt;(count)*static_cast&lt;std::uint64_t&gt;(width) · [reviewed contract](#b0003) |
| [B0004 · 21–23](../../../../../src/runtime/statistics.cpp#L21) | Explanatory comments or spacing. | source comment (unverified): // Charged native lexicographic comparison. std::string ordering uses unsigned · [reviewed contract](#b0004) |
| [B0005 · 24–42](../../../../../src/runtime/statistics.cpp#L24) | Callable definition: int compare(const Row& a,const Row& b,Budget& budget) | calls std::min, size, work, index; returns a\[i\].index()&lt;b\[i\].index()?-1:1; l&lt;r?-1:1; 2 loop sites; source comment (unverified): // Charged native lexicographic comparison. std::string ordering uses unsigned · [reviewed contract](#b0005) |
| [B0006 · 43–48](../../../../../src/runtime/statistics.cpp#L43) | Callable definition: void account_value(const storage::ScalarView& value,Budget& budget) | calls work, bytes, size · [reviewed contract](#b0006) |
| [B0007 · 49–49](../../../../../src/runtime/statistics.cpp#L49) | Callable definition: Value exported_value(const storage::ScalarView& value) | calls storage::export_scalar; returns storage::export_scalar(value) · [reviewed contract](#b0007) |
| [B0008 · 50–53](../../../../../src/runtime/statistics.cpp#L50) | Callable definition: Row copy(storage::RowView values,Budget& budget) | calls cells, account_value, storage::export_row, observe_capacities; returns result; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 54–57](../../../../../src/runtime/statistics.cpp#L54) | Callable definition: Row copy(storage::TupleValuesView values,Budget& budget) | calls account_value, storage::export_row, std::move, observe_capacities; returns result; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 58–58](../../../../../src/runtime/statistics.cpp#L58) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 59–62](../../../../../src/runtime/statistics.cpp#L59) | Callable definition: void admit(Groups& groups,Row key,std::uint64_t count,Budget& budget) | calls key, bytes, push_back, std::move; growth push_back · [reviewed contract](#b0011) |
| [B0012 · 63–93](../../../../../src/runtime/statistics.cpp#L63) | Callable definition: void finish(Distribution& out,Groups& groups,Budget& budget) | calls sort, work, compare, end; returns a.count!=b.count?a.count&gt;b.count:compare(a.key,b.key,budget)&lt;0; a.first&lt;b.first; growth emplace_back, push_back, reserve; 2 loop sites; source comment (unverified): // Standalone ordinary exports stay private until complete facts publish. · [reviewed contract](#b0012) |
| [B0013 · 94–96](../../../../../src/runtime/statistics.cpp#L94) | Callable definition: Capture start(const storage::ReferenceTable& table) | calls owner, relation, revision, layout; returns {{table.owner(),table.relation(),table.revision()},table.layout(),{},{},table.size(),{}} · [reviewed contract](#b0013) |
| [B0014 · 97–97](../../../../../src/runtime/statistics.cpp#L97) | Closes surrounding scope/type. |  · [reviewed contract](#b0014) |
| [B0015 · 98–102](../../../../../src/runtime/statistics.cpp#L98) | Callable definition: void Budget::observe_capacities(std::size_t row,std::size_t histogram,std::size_t heavy) noexcept | calls std::max · [reviewed contract](#b0015) |
| [B0016 · 103–103](../../../../../src/runtime/statistics.cpp#L103) | Callable definition: void Budget::work(std::uint64_t n) | calls charge · [reviewed contract](#b0016) |
| [B0017 · 104–104](../../../../../src/runtime/statistics.cpp#L104) | Callable definition: void Budget::row() | calls charge · [reviewed contract](#b0017) |
| [B0018 · 105–105](../../../../../src/runtime/statistics.cpp#L105) | Callable definition: void Budget::key() | calls charge · [reviewed contract](#b0018) |
| [B0019 · 106–106](../../../../../src/runtime/statistics.cpp#L106) | Callable definition: void Budget::bytes(std::uint64_t n) | calls charge · [reviewed contract](#b0019) |
| [B0020 · 107–132](../../../../../src/runtime/statistics.cpp#L107) | Callable definition: Distribution detail::projected_fields(const storage::ReferenceTable& table,std::span&lt;const FieldId&gt; fields,Budget& budget) | calls live, work, bytes, size; returns result; growth push_back, reserve; 5 loop sites; source comment (unverified): // Also enforces quiescence before publishing cardinality. · [reviewed contract](#b0020) |
| [B0021 · 133–139](../../../../../src/runtime/statistics.cpp#L133) | Callable definition: Capture projection(const storage::ReferenceTable& table,const storage::Projection& p,Budget& budget) | calls layout, same_token, source, Error; returns result · [reviewed contract](#b0021) |
| [B0022 · 140–153](../../../../../src/runtime/statistics.cpp#L140) | Callable definition: Capture index(const storage::ReferenceTable& table,IndexId id,Budget& budget) | calls index_keys, start, projection, work; returns result; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 154–189](../../../../../src/runtime/statistics.cpp#L154) | Callable definition: template&lt;class Table&gt; Distribution table_projected_fields(const Table& table,std::span&lt;const FieldId&gt; fields, Budget& budget,stor… | calls live, work, bytes, size; returns result; growth push_back, reserve; 5 loop sites; source comment (unverified): // This compatibility path exports ordinary keys and groups linearly. The · [reviewed contract](#b0023) |
| [B0024 · 190–191](../../../../../src/runtime/statistics.cpp#L190) | Callable definition: Distribution detail::projected_fields(const storage::StorageTable& table,std::span&lt;const FieldId&gt; fields, Budget& budget,storage:… | calls table_projected_fields; returns table_projected_fields(table,fields,budget,work) · [reviewed contract](#b0024) |
| [B0025 · 192–193](../../../../../src/runtime/statistics.cpp#L192) | Callable definition: Distribution detail::projected_fields(const storage::AccountedStorageTable& table,std::span&lt;const FieldId&gt; fields, Budget& budget… | calls table_projected_fields; returns table_projected_fields(table,fields,budget,work) · [reviewed contract](#b0025) |
| [B0026 · 194–199](../../../../../src/runtime/statistics.cpp#L194) | Callable definition: Capture projection(const storage::StorageTable& table,const storage::Projection& p,Budget& budget, storage::IndexWorkAllowance* w… | calls layout, same_token, source, Error; returns {{table.owner(),table.relation(),table.revision()},table.layout(),p,{},table.size(),std::move(distr… · [reviewed contract](#b0026) |
| [B0027 · 200–219](../../../../../src/runtime/statistics.cpp#L200) | Callable definition: Capture index(const storage::StorageTable& table,IndexId id,Budget& budget,storage::IndexWorkAllowance* work) | calls index_keys, owner, relation, revision; returns result; 1 loop sites; source comment (unverified): // The caller may catch admission failure before metadata is complete. No · [reviewed contract](#b0027) |
| [B0028 · 220–251](../../../../../src/runtime/statistics.cpp#L220) | Callable definition: Capture index(const storage::AccountedStorageTable& table,IndexId id,const storage::Projection& legacy, Budget& budget,storage::I… | calls index_keys, projection, descriptor, owner; returns left.same_descriptor(right); result; 1 loop sites; source comment (unverified): // Export the admitted index definition even if its diagnostic scan exhausts. · [reviewed contract](#b0028) |
| [B0029 · 252–254](../../../../../src/runtime/statistics.cpp#L252) | Closes surrounding scope/type. |  · [reviewed contract](#b0029) |

## B0001

[Lines 1–11](../../../../../src/runtime/statistics.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/statistics.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble explicit standalone table statistics export with shared logical capture budget. |
| inputs / outputs | Statistics/storage public types,Error,algorithm/list/limits and Exhausted alias. |
| invariants | This file emits ordinary Capture/Distribution/Row DTOs. Query-owned account-funded CapturedDistribution is implemented separately in native_statistics.cpp; do not label these ordinary allocations original-account native hot work. |
| ownership | Local/report ordinary vectors/list rows own exported values; metadata shares admitted layouts/projections. |
| failure | No runtime action or handler in includes/aliases. |
| cost | Compile-time setup only. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–15](../../../../../src/runtime/statistics.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge(std::uint64_t& used,std::uint64_t cap,std::uint64_t n) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit cumulative logical capture units without refund or saturation. |
| inputs / outputs | used&lt;=cap invariant and n&lt;=remaining permit increment,otherwise throw detail::Exhausted. |
| invariants | Usage private starts0 and only this helper changes it; no redundant used&gt;cap branch needed. Shared caller Budget composes multiple captures; failed components keep spent units. |
| ownership | One numeric counter,not MemoryAccount/RSS control. |
| failure | Fixed empty Exhausted carrier,handled only by explicit partial-distribution boundaries. |
| cost | Constant subtract/check/add,no allocation or clock. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0003

[Lines 16–20](../../../../../src/runtime/statistics.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t payload_bytes(std::size_t count,std::size_t width) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute requested ordinary payload-model bytes safely. |
| inputs / outputs | Element count and internal nonzero sizeof width require product fit size_t and U64,then return U64 bytes. |
| invariants | Width comes from concrete nonzero element types; no generic zero-width API. This models requested payload,not actual capacity/framing. |
| ownership | Inline size arithmetic only. |
| failure | Exhausted on overflow before container request. |
| cost | Constant bounds/division/multiply. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0004

[Lines 21–23](../../../../../src/runtime/statistics.cpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L23:sha256:de1d965005f8cfc2e5be4a3ab765d34db93203cfb4dfaa07685d06dbc38e165d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`int compare(const Row& a,const Row& b,Budget& budget)\`: Charged native lexicographic comparison. std::string ordering uses unsigned bytes, including embedded NUL and invalid UTF-8. Decimal work has a fixed conservative bound from its native 38-digit domain. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/statistics.cpp:L24; use that declaration for the actual input/output shape. |
| invariants | The source note states: Charged native lexicographic comparison. std::string ordering uses unsigned bytes, including embedded NUL and invalid UTF-8. Decimal work has a fixed conservative bound from its native 38-digit domain. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Charged native lexicographic comparison. std::string ordering uses unsigned bytes, including embedded NUL and invalid UTF-8. Decimal work has a fixed conservative bound from its native 38-digit domain. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 24–42](../../../../../src/runtime/statistics.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int compare(const Row& a,const Row& b,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact exported keys with explicitly charged native-compatible order. |
| inputs / outputs | Row keys lexicographically compare scalar tags then values; strings compare unsigned raw bytes including NUL/invalid UTF-8,decimals reserve bounded native-domain work,arity breaks ties. |
| invariants | No collation normalization or NULL added. Ordering agrees with native scalar representation; comparisons can exhaust shared Budget before result. |
| ownership | Borrows ordinary owning key rows; no new values retained. |
| failure | Exhausted propagates to capture boundary; local scratch may reorder during sort but no result facts are published yet. |
| cost | O(compared fields/string prefix bytes),fixed conservative256 decimal work per compared decimal field; no formatter allocation. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [tests/unit/scalar_statistics_test.cpp](../../../../../tests/unit/scalar_statistics_test.cpp) |

## B0006

[Lines 43–48](../../../../../src/runtime/statistics.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void account_value(const storage::ScalarView& value,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Precharge one exported scalar in the logical payload/work model. |
| inputs / outputs | ScalarView debits Value descriptor; text adds bytes+terminator and byte visits; inline decimal reserves38bytes/work without formatting. |
| invariants | Actual std::string/Decimal capacity,allocator links/slack and caller copies are outside this logical model. Native raw text bytes remain valid data. |
| ownership | No scalar is copied by accounting helper. |
| failure | Exhausted before ordinary export/allocation begins for that row/projection. |
| cost | Fixed type checks plus text length-based debit,not text scan itself. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0007

[Lines 49–49](../../../../../src/runtime/statistics.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value exported_value(const storage::ScalarView& value) { return storage::export_scalar(value); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export one native scalar to an owning caller DTO. |
| inputs / outputs | ScalarView forwards storage::export_scalar to Value. |
| invariants | Used only after appropriate scalar/model precharge; ordinary string/Decimal materialization is explicit export boundary. |
| ownership | Returned Value owns text/decimal DTO as needed,not charged to runtime MemoryAccount. |
| failure | Ordinary allocation/conversion errors propagate,not treated as valid incomplete-budget status. |
| cost | O(text/decimal exported bytes),fixed for inline primitives. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0008

[Lines 50–53](../../../../../src/runtime/statistics.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row copy(storage::RowView values,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Precharge then export an entire RowView key to ordinary owning Row. |
| inputs / outputs | Account every scalar,export_row and observe actual row vector capacity before return. |
| invariants | Logical payload excludes actual spare capacity; reported capacity high-water is observational. No account-backed query row copy is claimed. |
| ownership | Returned Row owns ordinary values; input view borrowed synchronously. |
| failure | Budget failure before export; allocation failure propagates with spent logical usage retained. |
| cost | O(arity+exported scalar bytes) preflight/copy,ordinary vector/value allocations. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0009

[Lines 54–57](../../../../../src/runtime/statistics.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row copy(storage::TupleValuesView values,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Precharge then export an entire TupleValuesView key to ordinary owning Row. |
| inputs / outputs | Account every scalar,export_row and observe actual row vector capacity before return. |
| invariants | Logical payload excludes actual spare capacity; reported capacity high-water is observational. No account-backed query row copy is claimed. |
| ownership | Returned Row owns ordinary values; input view borrowed synchronously. |
| failure | Budget failure before export; allocation failure propagates with spent logical usage retained. |
| cost | O(arity+exported scalar bytes) preflight/copy,ordinary vector/value allocations. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0010

[Lines 58–58](../../../../../src/runtime/statistics.cpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Groups=std::list<HeavyKey>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use a local linked list of complete heavy-key/count scratch groups. |
| inputs / outputs | Groups aliases std::list&lt;HeavyKey&gt; for standalone projection/index capture. |
| invariants | Local scratch is never public until final exact Distribution fields publish. Not maintained engine state or a query-account container. |
| ownership | Owns ordinary Row keys and list nodes during explicit capture. |
| failure | Alias adds no handler/account. |
| cost | One list node+owning key per distinct group once admitted. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0011

[Lines 59–62](../../../../../src/runtime/statistics.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void admit(Groups& groups,Row key,std::uint64_t count,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one newly discovered complete key/count group. |
| inputs / outputs | Shared Budget consumes one distinct key and HeavyKey+two-link payload model before list push_back. |
| invariants | Caller guarantees key is new and count is actual occurrence/degree; no duplicate-group search here. |
| ownership | Moves owning ordinary Row into local list; producer/view no longer borrowed. |
| failure | Budget failure precedes node allocation; ordinary OOM propagates and local groups unwind. |
| cost | Constant node admission/append plus ordinary list allocation,without key deep copy. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0012

[Lines 63–93](../../../../../src/runtime/statistics.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish(Distribution& out,Groups& groups,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish exact NDV,histogram and ordered heavy keys only after complete traversal/preparation. |
| inputs / outputs | Local Groups sort count descending then exact key order; build count-&gt;number-of-keys histogram,sort ascending count,move top min(K,heavy_limit) and finally set out fields/completion exact. |
| invariants | Count-descending group sort makes equal multiplicities contiguous. Only the last histogram bin can match the next group; all construction remains private until exact result publication. Exhaustion cannot leak prefix NDV/top-K/histogram. |
| ownership | Ordinary scratch groups/histogram/heavy vectors own exports; final moves avoid deep key copies. No original-query-account allocation claim. |
| failure | Exhausted/allocator/comparator errors before final assignment leave out unknown; local scratch only may be reordered/moved. |
| cost | K groups,H multiplicities: charged O(K log K) group sort, at most one histogram lookup probe per nonfirst group, then O(H log H) bin sort/top-K moves. Repeated reserve and cumulative modeled H^2 growth remain; no overall linear/time claim. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [tests/unit/statistics_capture_test.cpp](../../../../../tests/unit/statistics_capture_test.cpp) |

```text
out.ndv=groups.size(); out.histogram=std::move(histogram); out.heavy_keys=std::move(heavy);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish complete distribution facts only after every scratch sort/allocation succeeds. |
| inputs / outputs | Final moves set NDV,histogram,engaged top-K and exact completion; partial traversal/finalization never publishes prefix facts. |
| invariants | Visited prefix can remain diagnostic while completion unknown. Exact empty population has NDV0 and engaged empty heavy list. |
| ownership | Moves ordinary vectors/keys; source table unchanged. |
| failure | Earlier budget/OOM/comparator exceptions unwind locals; final fixed/default-allocator vector moves do not need a recovery catch. |
| cost | Constant vector moves plus dropping old default-empty output,not key deep copies. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

```text
if(found!=histogram.end()) ++found->second;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count multiplicity classes after groups are already ordered by count. |
| inputs / outputs | Existing loop finds a matching bin or appends a new one; group sort makes every equal count contiguous,so only last bin can match. |
| invariants | Sorted adjacency replaces repeated bin search. Empty histogram makes no lookup debit; each nonempty lookup spends one work unit. Fewer probes can allow more captures to finish inside the same unchanged allowance. Reserve/capacity/top-K rules remain. |
| ownership | Local ordinary histogram only,no runtime/table state. |
| failure | Budget/allocator failure still prevents exact output; no incomplete prefix is published as exact. |
| cost | O(K) lookup probes; repeated reserve/cumulative modeled H^2 costs remain separate. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0013

[Lines 94–96](../../../../../src/runtime/statistics.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Capture start(const storage::ReferenceTable& table) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind standalone reference-table report metadata and exact cardinality. |
| inputs / outputs | ReferenceTable returns owner/relation/revision Stamp,shared source layout,empty optional projection/index,table.size and unknown Distribution. |
| invariants | Storage revision invalidates table reads; it is not committed runtime epoch. Quiescence is enforced by calling live/index cursor before public capture. |
| ownership | Metadata ownership shares layout token; no rows copied here. |
| failure | Invalid table access propagates; no catch. |
| cost | Constant metadata/cardinality access. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0014

[Lines 97–97](../../../../../src/runtime/statistics.cpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L97:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/statistics.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/statistics.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/statistics.cpp\` at its lexical source position in src/runtime/statistics.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/statistics.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0015

[Lines 98–102](../../../../../src/runtime/statistics.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::observe_capacities(std::size_t row,std::size_t histogram,std::size_t heavy) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe actual standalone export capacities separately from modeled bytes. |
| inputs / outputs | Row/histogram/heavy capacity values update max_*_capacity in usage. |
| invariants | Monotone high-water observations,not additions to current retained model or heap authority. |
| ownership | Fixed caller Budget fields only. |
| failure | noexcept,no allocation. |
| cost | Three fixed max operations. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0016

[Lines 103–103](../../../../../src/runtime/statistics.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::work(std::uint64_t n){charge(usage_.work,limits_.work,n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume shared standalone statistics work units. |
| inputs / outputs | Budget::work forwards one or supplied amount to checked charge on usage_.work with its fixed configured cap. |
| invariants | Does not create/refill account,read clock or refund failed earlier component visits. accounted_bytes remains logical payload model. |
| ownership | Mutates existing private Budget only. |
| failure | Exhausted on insufficient remaining units. |
| cost | Constant checked arithmetic. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0017

[Lines 104–104](../../../../../src/runtime/statistics.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::row(){charge(usage_.rows,limits_.rows,1);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume shared standalone statistics rows units. |
| inputs / outputs | Budget::row forwards one or supplied amount to checked charge on usage_.rows with its fixed configured cap. |
| invariants | Does not create/refill account,read clock or refund failed earlier component visits. accounted_bytes remains logical payload model. |
| ownership | Mutates existing private Budget only. |
| failure | Exhausted on insufficient remaining units. |
| cost | Constant checked arithmetic. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0018

[Lines 105–105](../../../../../src/runtime/statistics.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::key(){charge(usage_.distinct_keys,limits_.distinct_keys,1);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume shared standalone statistics distinct_keys units. |
| inputs / outputs | Budget::key forwards one or supplied amount to checked charge on usage_.distinct_keys with its fixed configured cap. |
| invariants | Does not create/refill account,read clock or refund failed earlier component visits. accounted_bytes remains logical payload model. |
| ownership | Mutates existing private Budget only. |
| failure | Exhausted on insufficient remaining units. |
| cost | Constant checked arithmetic. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0019

[Lines 106–106](../../../../../src/runtime/statistics.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::bytes(std::uint64_t n){charge(usage_.accounted_bytes,limits_.accounted_bytes,n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume shared standalone statistics accounted_bytes units. |
| inputs / outputs | Budget::bytes forwards one or supplied amount to checked charge on usage_.accounted_bytes with its fixed configured cap. |
| invariants | Does not create/refill account,read clock or refund failed earlier component visits. accounted_bytes remains logical payload model. |
| ownership | Mutates existing private Budget only. |
| failure | Exhausted on insufficient remaining units. |
| cost | Constant checked arithmetic. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0020

[Lines 107–132](../../../../../src/runtime/statistics.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Distribution detail::projected_fields(const storage::ReferenceTable& table,std::span<const FieldId> fields,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a complete standalone projected-key distribution from a quiescent reference table. |
| inputs / outputs | Live cursor establishes quiescence; ordered/repeated FieldIds validate,width cap applies; rows project to ordinary keys,linear groups accumulate counts,finish publishes exact facts if all visits fit shared Budget. |
| invariants | An empty projection has one key for nonempty input. Fields and layout mismatches are real request errors. Exhaustion reports visited prefix only,with no NDV/histogram/heavy facts. |
| ownership | Temporary ordinary keys/list and returned Distribution own exported values; no index registration or table mutation. |
| failure | Exhausted swallowed only as explicit incomplete distribution; OOM/request/storage/state errors propagate. Cursor creation is outside this budget catch. |
| cost | N rows,K keys: O(N*K*key compare bytes) linear grouping plus projection/export and finish costs; no indexed-update/runtime-hot claim. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0021

[Lines 133–139](../../../../../src/runtime/statistics.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Capture projection(const storage::ReferenceTable& table,const storage::Projection& p,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose reference-table projection capture with bound layout identity. |
| inputs / outputs | Require projection source same_token(table.layout),scan ordered fields,then attach actual Stamp/layout/projection/cardinality. |
| invariants | Projection compiled beforehand; no hidden index creation or schema rewrite. Exact cardinality can survive unavailable distribution. |
| ownership | Shares immutable layout/projection metadata and owns ordinary Distribution. |
| failure | Foreign source throws layout_mismatch; incomplete scan remains typed unknown,other failures propagate. |
| cost | Constant metadata plus full projected distribution work. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0022

[Lines 140–153](../../../../../src/runtime/statistics.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Capture index(const storage::ReferenceTable& table,IndexId id,Budget& budget) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture reference index degree distribution from its actual key cursor. |
| inputs / outputs | Create index cursor/metadata,then shared Budget scans each exact key and degree,precharges/copies native key,admits distinct group and finishes. |
| invariants | Index key enumeration supplies unique keys,avoiding projection grouping scan. Counts are actual member degrees,not approximate means. Incomplete output retains only visited prefix metadata. |
| ownership | Ordinary exported key/list/report storage,shared compiled layout/index projection. |
| failure | Exhausted inside traversal returns unknown distribution; cursor/index metadata failure before try or OOM/other errors propagate. |
| cost | O(index keys+key export bytes) traversal plus finish sort/hist/top-K; no base-table per-row grouping search. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0023

[Lines 154–189](../../../../../src/runtime/statistics.cpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Table> Distribution table_projected_fields(const Table& table,std::span<const FieldId> fields,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share standalone projected-key traversal over StorageTable/AccountedStorageTable views. |
| inputs / outputs | Optional IndexWorkAllowance drives live/next_entry; projection width/field bounds and statistics Budget drive ordinary key export,linear grouping and final exact distribution. |
| invariants | Storage work and logical statistics work are separate finite domains. Even AccountedStorageTable overload returns explicit ordinary Distribution,not native query-owned capture. |
| ownership | Cursor borrows admitted table; ordinary local list/rows own copied keys. No mutation/hidden index registration. |
| failure | Exhausted and only storage_work_limit from typed IndexFailure/public Error become unknown distribution; all other contract/layout/state/corruption/resource errors propagate. |
| cost | O(N*K*compared key bytes) grouping+projection/finish,with actual native storage cursor work and ordinary export allocations. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp) |

## B0024

[Lines 190–191](../../../../../src/runtime/statistics.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Distribution detail::projected_fields(const storage::StorageTable& table,std::span<const FieldId> fields,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward StorageTable ordered-field statistics through one standalone implementation. |
| inputs / outputs | Table,FieldId span,Budget and optional storage allowance call table_projected_fields. |
| invariants | No new metadata/index registration or broader error suppression in overload. |
| ownership | Input views borrowed during call; returned ordinary Distribution owns exports. |
| failure | Same typed incomplete/storage-work handling and real-error propagation. |
| cost | Constant dispatch plus full underlying projected traversal/grouping. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0025

[Lines 192–193](../../../../../src/runtime/statistics.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Distribution detail::projected_fields(const storage::AccountedStorageTable& table,std::span<const FieldId> fields,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward AccountedStorageTable ordered-field statistics through one standalone implementation. |
| inputs / outputs | Table,FieldId span,Budget and optional storage allowance call table_projected_fields. |
| invariants | No new metadata/index registration or broader error suppression in overload. |
| ownership | Input views borrowed during call; returned ordinary Distribution owns exports. |
| failure | Same typed incomplete/storage-work handling and real-error propagation. |
| cost | Constant dispatch plus full underlying projected traversal/grouping. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0026

[Lines 194–199](../../../../../src/runtime/statistics.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Capture projection(const storage::StorageTable& table,const storage::Projection& p,Budget& budget,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind StorageTable projection identity around its standalone distribution. |
| inputs / outputs | Require source layout token,compute projected_fields and return actual owner/relation/revision/layout/projection/cardinality. |
| invariants | No committed epoch/freshness import; stable single-writer/quiescent table contract applies. |
| ownership | Owns ordinary distribution and shared layout metadata. |
| failure | Foreign source throws; storage/statistical exhaustion marked incomplete only in scan helper. |
| cost | Constant metadata plus projected scan/group/sort costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0027

[Lines 200–219](../../../../../src/runtime/statistics.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Capture index(const storage::StorageTable& table,IndexId id,Budget& budget,storage::IndexWorkAllowance* work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture StorageTable index keys with incomplete facts separated from admission errors. |
| inputs / outputs | Index cursor/projection metadata admitted before try; then shared Budget copies each key/degree and finalizes distribution. |
| invariants | No prefix NDV/hist/top-K escapes exhaustion. StorageWorkAllowance is passed through actual cursor; no refill/new index. |
| ownership | Ordinary report keys/list,vectors and shared metadata; no table mutation. |
| failure | Exhausted/public Error storage_work_limit inside traversal return unknown; unrelated errors propagate. Pre-metadata cursor/projection failure can be caught by outer caller; typed backend boundary semantics retained. |
| cost | O(index key bytes/keys) traversal plus finish costs and ordinary capture allocations. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0028

[Lines 220–251](../../../../../src/runtime/statistics.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Capture index(const storage::AccountedStorageTable& table,IndexId id,const storage::Projection& legacy,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export standalone accounted-index statistics under its actual validated metadata. |
| inputs / outputs | Accounted table/id, supplied legacy Projection, Budget and optional storage allowance; obtain the actual index descriptor and return its owning metadata plus a complete or incomplete ordinary distribution. |
| invariants | Validate complete source and target descriptors and exact ordered fields before an exact result; width equality is insufficient and token equality is unnecessary. Budget exhaustion before validation yields incomplete actual metadata without exact NDV/histogram/heavy keys. |
| ownership | Cursor borrows table. Capture shares the admitted index source/projection owners; exported keys own ordinary rows. Metadata validation creates no cloned descriptor or native retained row graph. |
| failure | Invalid metadata after successful comparison throws invalid_statistics_request. Cursor and actual projection acquisition precede the existing try. Only Exhausted and storage_work_limit inside it become incomplete; unrelated backend/corruption/allocation errors propagate. |
| cost | Existing index-definition lookup and key scan use the same native allowance. Precharge source/target field counts and binding bytes plus ordered projection fields against the existing statistics work budget; grouping/copy/sort costs remain explicit caller export work. |
| Design | [docs/statistics.md](../../../../statistics.md), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [src/runtime/native_statistics.cpp](../../../../../src/runtime/native_statistics.cpp) |

## B0029

[Lines 252–254](../../../../../src/runtime/statistics.cpp#L252); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L252-L254:sha256:0fc5d8ec7d53a9193325663dc0e7cbfbd83e87df77e1c966b6657fe657840e0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::statistics\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::statistics\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::statistics\` at its lexical source position in src/runtime/statistics.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::statistics\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
