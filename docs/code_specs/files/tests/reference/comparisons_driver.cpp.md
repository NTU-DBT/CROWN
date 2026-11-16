# `tests/reference/comparisons_driver.cpp` — block usage map

[Source](../../../../../tests/reference/comparisons_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `48a2c7d7074870114ffef1f538db97f6ee1e1e1b70bf1d1a7d943fc4d0599037`. 111 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/reference/comparisons_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Execution and wire presentation only. The external oracle evaluates complete · [reviewed contract](#b0001) |
| [B0002 · 21–29](../../../../../tests/reference/comparisons_driver.cpp#L21) | Callable definition: cp::Operator operation(const std::string& name) | calls std::runtime_error; returns cp::Operator::equal; cp::Operator::not_equal; source comment (unverified): // Execution and wire presentation only. The external oracle evaluates complete · [reviewed contract](#b0002) |
| [B0003 · 30–37](../../../../../tests/reference/comparisons_driver.cpp#L30) | Callable definition: cp::Operand operand(const Json& value, const Query& query) | calls size, std::runtime_error, contains, io::read_scalar; returns io::read_scalar(value.at(@ )); VariableId{i}; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 38–46](../../../../../tests/reference/comparisons_driver.cpp#L38) | Callable definition: FreeConnexTree tree(const Json& request, const Document& document) | calls contains, io::read_tree, at, dump; returns io::read_tree(request.at(@ ).dump(),document.catalog,document.query); {} · [reviewed contract](#b0004) |
| [B0005 · 47–53](../../../../../tests/reference/comparisons_driver.cpp#L47) | Callable definition: Json tuples(const cr::TupleVector& input) | calls insert, storage::export_row, values, std::runtime_error; returns io::write_relation(result); growth insert; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 54–60](../../../../../tests/reference/comparisons_driver.cpp#L54) | Callable definition: Json metrics(const cr::Metrics& m) | calls ; returns {{@ ,m.work},{@ ,m.producer_work},{@ ,m.view_work}, · [reviewed contract](#b0006) |
| [B0007 · 61–69](../../../../../tests/reference/comparisons_driver.cpp#L61) | Callable definition: Json snapshot(const cr::Runtime& owner) | calls source_snapshot, Json::array, push_back, io::write_relation; returns {{@ ,owner.sequence()},{@ ,owner.ready()},{@ ,tuples(current.rows)},; growth push_back; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 70–77](../../../../../tests/reference/comparisons_driver.cpp#L70) | Callable definition: Json apply(cr::Runtime& owner, const PhysicalSetUpdate& update) | calls tuples, metrics, code, std::string; returns {{@ ,nullptr},{@ ,epoch.input.input.physical_changed},; {{@ ,error.code()}} · [reviewed contract](#b0008) |
| [B0009 · 78–104](../../../../../tests/reference/comparisons_driver.cpp#L78) | Callable definition: Json evaluate(const Json& request) | calls io::read_document, at, dump, empty; returns {{@ ,request.at(@ )},{@ ,general.physical_sha256()==before},; growth insert, push_back; 4 loop sites · [reviewed contract](#b0009) |
| [B0010 · 105–105](../../../../../tests/reference/comparisons_driver.cpp#L105) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0010) |
| [B0011 · 106–111](../../../../../tests/reference/comparisons_driver.cpp#L106) | Callable definition: int main() | calls std::getline, evaluate, Json::parse, dump; returns 0; 1; 1 loop sites · [reviewed contract](#b0011) |

## B0001

[Lines 1–20](../../../../../tests/reference/comparisons_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:10022faf1b3b13e90a92bb95743935617c0f205e8944ded09696dd0f8a53deab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import only actual comparison execution and test-wire construction facilities. |
| inputs / outputs | Native driver includes, aliases and explanatory scope comments. |
| invariants | The driver supplies no expected predicate answers; separate Python/SQLite models define them. |
| ownership | Ordinary JSON and compiler DTO work is an explicit external test boundary. |
| failure | Compile/link errors stay ordinary; no executed acceptance follows from authoring. |
| cost | Compile-time scaffolding, then actual requested native work. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py) |

## B0002

[Lines 21–29](../../../../../tests/reference/comparisons_driver.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L29:sha256:96dceb0bdabee323146f368e9686209fc9f96c33dfb833f178003136ee2fb784
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode six wire operation names into the real public enum. |
| inputs / outputs | String name in; cp::Operator out. |
| invariants | No unknown name defaults to equality or another predicate. |
| ownership | Borrows wire string for synchronous decoding. |
| failure | Unknown names throw runtime_error and fail the driver. |
| cost | At most six bounded name comparisons. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp) |

## B0003

[Lines 30–37](../../../../../tests/reference/comparisons_driver.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L37:sha256:6ed415bb5a14e642b22e0b074a7658f09ddf8c4c79fe44fc733559c8a98309c3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a wire operand against original variable names or exact encoded scalar literals. |
| inputs / outputs | One-key JSON operand and original Query in; public Operand out. |
| invariants | Variable lookup returns its actual shuffled original ID. Scalar literal decoding uses the normal wire scalar reader; multi-key operands cannot masquerade as variables. |
| ownership | Returned literal owns ordinary compiler payload; query/string inputs remain borrowed. |
| failure | Bad JSON/name/scalar errors propagate; no fake comparison result is supplied. |
| cost | Variable-name scan or exact scalar parse/copy, with scalar width costs. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp) |

## B0004

[Lines 38–46](../../../../../tests/reference/comparisons_driver.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L46:sha256:0140958cd4efc27ea9c6e2524bc0751c7a297101ac46bdf72c2f2c3770702f73
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain genuine structural admission for the equality CQ used by the test. |
| inputs / outputs | Request and original Document in; checked/supplied FreeConnexTree out. |
| invariants | Explicit tree is read through the actual reader first. Without an explicit tree, an original contradictory query uses its required canonical empty tree before search; otherwise a genuinely proven minimum tree is required. The comparison predicate is not inserted into tree equality scopes. |
| ownership | Returns ordinary cold tree DTO; no runtime owner is shared. |
| failure | Bad supplied tree/read or missing proved choice throws; lower_tree subsequently validates actual structure. |
| cost | Cold tree decode, constant-size contradictory empty-tree selection or finite native planner search plus its own existing work; not comparison maintenance cost. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [include/crown/io/tree.hpp](../../../../../include/crown/io/tree.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0005

[Lines 47–53](../../../../../tests/reference/comparisons_driver.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L53:sha256:513f1417e81dbeb99a45d950a58ee48a3318be369bb1bd1aaba055f3664b6aaa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize actual endpoint tuple vectors while detecting duplicates. |
| inputs / outputs | Owning native TupleVector in; sorted JSON relation out. |
| invariants | Every actual row is exported; insertion collision throws rather than silently hiding duplicate native output. |
| ownership | Borrows native tuples and owns ordinary exported row set/JSON only at test boundary. |
| failure | Duplicate, export or allocation failure fails the native driver. |
| cost | Full tuple export, ordered insertion and JSON materialization for every row. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp) |

## B0006

[Lines 54–60](../../../../../tests/reference/comparisons_driver.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L60:sha256:9096076ce2ae548f8cf6a604eb4c2d0375c2deacad5daea784864953e67b2db0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the actual selected comparison work counters without deriving expected results. |
| inputs / outputs | Native Metrics in; JSON scalar fields for wrapper/producer/view/predicate/projection/difference work out. |
| invariants | Counters are copied verbatim, including recomputed; no wall-clock or CQC theorem is inferred. |
| ownership | Borrowed metric input; ordinary JSON output owns its scalars. |
| failure | JSON allocation failure propagates. |
| cost | Fixed field presentation plus JSON allocations. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0007

[Lines 61–69](../../../../../tests/reference/comparisons_driver.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L69:sha256:6d5fb2dcf76041e3b9d6bf797081482e4154790ae4466ccdd172d76390f0b605
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual committed comparison answers, original source state and binding/account observations. |
| inputs / outputs | Native comparison owner in; sequence/ready/rows/full sources/existence/predicate-count/account-equality JSON out. |
| invariants | Uses actual snapshot and source export, not projected equality answers or model rows. Snapshot Binding must use the original owner account. |
| ownership | Local owning snapshot retains rows/binding through serialization; physical Database/JSON are external ordinary DTOs. |
| failure | Native snapshot/source/read failures propagate; duplicate results fail through tuples(). |
| cost | Eager funded handle snapshot, complete source scan/copy and complete JSON output costs are real test observation work. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py) |

## B0008

[Lines 70–77](../../../../../tests/reference/comparisons_driver.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L77:sha256:e316a8ad867bbd820c5617772463ecb5d510008fa46a6fda42c82c18809f710d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attempt one genuine native source epoch and present exact comparison endpoint deltas. |
| inputs / outputs | Runtime and original PhysicalSetUpdate in; error or physical_changed/added/removed/native Metrics out. |
| invariants | Physical change comes from Epoch.input.input, comparison differences from the separate added/removed tuple vectors. No expected state is computed. |
| ownership | Epoch retains native output/binding through serialization; caller owns original update DTO. |
| failure | crown::Error and MemoryFailure are presented by code; other exceptions terminate through main. No retry or repair hides refusal. |
| cost | One real native apply plus full output serialization; actual recomputation/copy costs stay visible. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py) |

## B0009

[Lines 78–104](../../../../../tests/reference/comparisons_driver.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L104:sha256:bf0994c3140f32b0612c6e13117fa666f4be8ef3cdcf9016617d72fdb70b4b1b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one complete independent-owner JSONL comparison test request. |
| inputs / outputs | Original empty Document, predicates, backend flag and serial events in; initial/each-prefix native observations out. |
| invariants | Reject nonempty initial sources; lower actual original CQ/tree and admit explicit predicates. Indexed policy is finite and keeps needed indices. Caller general hash remains unchanged; every input is decoded as a complete original physical row. |
| ownership | One local Runtime owns the real query account; cold request/plan/predicate DTOs and full capture JSON are external test objects. |
| failure | Malformed protocol or admission/construction failure exits the request through main; per-event named refusal is retained without mutating expected source state inside this driver. |
| cost | Cold original planning/admission then real apply and full observations per event; full captured trace memory is unbounded external test work, not a production streaming claim. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py) |

## B0010

[Lines 105–105](../../../../../tests/reference/comparisons_driver.cpp#L105); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L105:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close private native driver helpers. |
| inputs / outputs | Namespace delimiter only. |
| invariants | No expected model or public backend registration is introduced. |
| ownership | No owner. |
| failure | No runtime branch. |
| cost | No runtime work. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp) |

## B0011

[Lines 106–111](../../../../../tests/reference/comparisons_driver.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L111:sha256:62dc99cb0b141b4faddbb95d4c81e0ea92240f3230390879bd88f5dfcd80a8f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the real JSONL native driver with one process-level diagnostic boundary. |
| inputs / outputs | stdin request lines in; one evaluate JSON line per completed request out, process status 0 or 1. |
| invariants | No canned pass/output; all requests execute actual owners. Requests are serial, with distinct Runtime scopes. |
| ownership | Each line/DOM/capture owns external test data; native account lifetimes end with its request owner unless owning outputs retain them locally. |
| failure | std::exception prints diagnostic and returns 1. No catch retries or substitutes an expected answer. |
| cost | Full line parse, native request execution and JSON dump; no timing/whole-suite acceptance claim. |
| Design | [tests/reference/comparisons_driver.cpp](../../../../../tests/reference/comparisons_driver.cpp), [tests/integration/comparisons_oracle.py](../../../../../tests/integration/comparisons_oracle.py) |
