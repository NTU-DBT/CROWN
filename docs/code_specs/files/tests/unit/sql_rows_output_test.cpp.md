# `tests/unit/sql_rows_output_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_rows_output_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2169b98c47d66743d33ac105db3cfc2c148f2729003bfb5bbdc7c91462fc95c9`. 285 lines partitioned into 29 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–27](../../../../../tests/unit/sql_rows_output_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 28–28](../../../../../tests/unit/sql_rows_output_test.cpp#L28) | Type/record definition: enum class Mode |  · [reviewed contract](#b0002) |
| [B0003 · 29–30](../../../../../tests/unit/sql_rows_output_test.cpp#L29) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 31–31](../../../../../tests/unit/sql_rows_output_test.cpp#L31) | Callable definition: Cell integer(std::int64_t value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0004) |
| [B0005 · 32–32](../../../../../tests/unit/sql_rows_output_test.cpp#L32) | Callable definition: Cell text(std::string_view value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0005) |
| [B0006 · 33–39](../../../../../tests/unit/sql_rows_output_test.cpp#L33) | Callable definition: Row own(std::span&lt;const Cell&gt; cells) | calls emplace_back, storage::export_scalar; returns row; growth emplace_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 40–42](../../../../../tests/unit/sql_rows_output_test.cpp#L40) | Callable definition: Catalog catalog() | calls ; returns {1,{{@ ,{{@ ,ScalarType::int64,false},{@ ,ScalarType::int64,true},{@ ,ScalarType::string,true}}}}} · [reviewed contract](#b0007) |
| [B0008 · 43–49](../../../../../tests/unit/sql_rows_output_test.cpp#L43) | Callable definition: frontend::SqlRowsProgram compile(std::string_view sql,const Catalog& schema=catalog(), const frontend::SqlRowsBindOptions& option… | calls catalog, frontend::bind_sql_rows, Error, std::move; returns std::get&lt;frontend::SqlRowsProgram&gt;(std::move(result)) · [reviewed contract](#b0008) |
| [B0009 · 50–57](../../../../../tests/unit/sql_rows_output_test.cpp#L50) | Callable definition: runtime::SqlRowsRuntime create(const frontend::SqlRowsProgram& program,bool indexed) | calls contradiction, export_core, planner::minimum_tree, assert; guard assert(chosen.status==planner::OracleStatus::proven_minimum && chosen.tree);tree=*chosen.tree;; returns runtime::SqlRowsRuntime(program,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0009) |
| [B0010 · 58–62](../../../../../tests/unit/sql_rows_output_test.cpp#L58) | Callable definition: Bag results(const runtime::SqlRowsRuntime& owner) | calls next, assert, emplace, export_values; guard while(auto row=cursor.next())assert(result.emplace(row-&gt;tuple.export_values(),row-&gt;multiplicity).se…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 63–67](../../../../../tests/unit/sql_rows_output_test.cpp#L63) | Callable definition: template&lt;class Action&gt; void error(Action action,std::string_view expected) | calls action, assert, code; guard try {action();}catch(const Error& failure) {assert(failure.code()==expected);failed=true;} · [reviewed contract](#b0011) |
| [B0012 · 68–68](../../../../../tests/unit/sql_rows_output_test.cpp#L68) | Callable definition: std::uint64_t add(std::uint64_t left,std::uint64_t right) | calls assert; guard std::uint64_t add(std::uint64_t left,std::uint64_t right) {assert(right&lt;=UINT64_MAX-left);return le…; returns left+right · [reviewed contract](#b0012) |
| [B0013 · 69–69](../../../../../tests/unit/sql_rows_output_test.cpp#L69) | Callable definition: std::uint64_t product(std::uint64_t left,std::uint64_t right) | calls assert; guard std::uint64_t product(std::uint64_t left,std::uint64_t right) {assert(!left \|\| right&lt;=UINT64_MAX/le…; returns left*right · [reviewed contract](#b0013) |
| [B0014 · 70–72](../../../../../tests/unit/sql_rows_output_test.cpp#L70) | Explanatory comments or spacing. | source comment (unverified): // Direct physical-row evaluation, independent of native factors/delta traversal. · [reviewed contract](#b0014) |
| [B0015 · 73–89](../../../../../tests/unit/sql_rows_output_test.cpp#L73) | Callable definition: Bag oracle(const Bag& source,Mode mode,bool selfjoin) | calls add, product, empty; returns {{Row{Value{!bag.empty()}},1}}; bag; 3 loop sites; source comment (unverified): // Direct physical-row evaluation, independent of native factors/delta traversal. · [reviewed contract](#b0015) |
| [B0016 · 90–98](../../../../../tests/unit/sql_rows_output_test.cpp#L90) | Callable definition: Changes difference(const Bag& before,const Bag& after) | calls contains, at, emplace; returns changes; growth emplace; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 99–112](../../../../../tests/unit/sql_rows_output_test.cpp#L99) | Callable definition: Changes decode(const runtime::SqlRowsRuntime::PreparedBatch& batch) | calls assert, output_size, scratch, program; guard assert(batch.output_size());Cells scratch(batch.program().outputs().size());Changes changes;; returns changes; growth emplace; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 113–113](../../../../../tests/unit/sql_rows_output_test.cpp#L113) | Explanatory comments or spacing. |  |
| [B0019 · 114–147](../../../../../tests/unit/sql_rows_output_test.cpp#L114) | Callable definition: void sql_trace(bool indexed,Mode mode,bool selfjoin) | calls std::string, create, compile, long_text; guard assert(prepared.output_size()==expected.size() && prepared.output_work()==0);; growth push_back; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 148–148](../../../../../tests/unit/sql_rows_output_test.cpp#L148) | Explanatory comments or spacing. |  |
| [B0021 · 149–178](../../../../../tests/unit/sql_rows_output_test.cpp#L149) | Callable definition: void budgets_contracts_and_rollback(bool indexed) | calls create, compile, integer, text; guard auto old=owner.prepare_batch({1,{}});assert(!old.output_size() && old.output_work()==0); · [reviewed contract](#b0021) |
| [B0022 · 179–179](../../../../../tests/unit/sql_rows_output_test.cpp#L179) | Explanatory comments or spacing. |  |
| [B0023 · 180–207](../../../../../tests/unit/sql_rows_output_test.cpp#L180) | Callable definition: void wide_and_owner_lifetime(bool indexed) | calls create, compile, integer, prepare_output_batch; guard assert((decode(batch)==Changes{{Row{Value{std::int64_t{7}}},Signed{false,wide}}}));static_cast&lt;void…; growth emplace · [reviewed contract](#b0023) |
| [B0024 · 208–210](../../../../../tests/unit/sql_rows_output_test.cpp#L208) | Explanatory comments or spacing. | source comment (unverified): // Compare the exact prior signature recipe, then rebind/freeze through genuine · [reviewed contract](#b0024) |
| [B0025 · 211–248](../../../../../tests/unit/sql_rows_output_test.cpp#L211) | Callable definition: void binding_image_and_freeze() | calls catalog, compile, assert, binding_image; guard assert(ordinary.binding_image().empty());options.retain_binding_image=true;; source comment (unverified): // Compare the exact prior signature recipe, then rebind/freeze through genuine · [reviewed contract](#b0025) |
| [B0026 · 249–249](../../../../../tests/unit/sql_rows_output_test.cpp#L249) | Explanatory comments or spacing. |  |
| [B0027 · 250–273](../../../../../tests/unit/sql_rows_output_test.cpp#L250) | Callable definition: void optional_binding_memory() | calls catalog, payload, compile, assert; guard assert(ordinary.binding_image().empty()); · [reviewed contract](#b0027) |
| [B0028 · 274–274](../../../../../tests/unit/sql_rows_output_test.cpp#L274) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0028) |
| [B0029 · 275–285](../../../../../tests/unit/sql_rows_output_test.cpp#L275) | Callable definition: int main() | calls sql_trace, budgets_contracts_and_rollback, wide_and_owner_lifetime, binding_image_and_freeze; returns 1; 3 loop sites · [reviewed contract](#b0029) |

## B0001

[Lines 1–27](../../../../../tests/unit/sql_rows_output_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L27:sha256:4ea2d4f8747bdc671dbea0d92eba325f2c03ca1581ebfd8edde8698f5ffe72d8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include test dependencies and declare local nullable-row/bag/change aliases. |
| inputs / outputs | Open the private test namespace; alias Cell/Cells/Row/Bag/Signed/Changes using ordinary vector/map storage. |
| invariants | No oracle, native call, result drain or assertion executes in this region. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0002

[Lines 28–28](../../../../../tests/unit/sql_rows_output_test.cpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:59a6b786858f7b0bb01843fb210d9d545e6afdd8b92c8cc8405e3fd39bcbf9e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the three SQL presentation modes selected by test fixtures. |
| inputs / outputs | Mode has bag, distinct and exists values. |
| invariants | Selecting a value does not create a query or evaluate any rows. |
| ownership | Fixed enum value only; no borrow or dynamic storage. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0003

[Lines 29–30](../../../../../tests/unit/sql_rows_output_test.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L30:sha256:45220eac942fb6d4a8f64ff732ebc601c08b180802fd724ecf1e94b5012d2aa8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the two zero-initialized test progress counters. |
| inputs / outputs | transactions and decodes are private uint64 counters initialized to zero. |
| invariants | Their increments occur in later test functions; declarations do not validate transaction/delta correctness. |
| ownership | Static scalar test storage; no query-owned memory. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0004

[Lines 31–31](../../../../../tests/unit/sql_rows_output_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:1c1bb764cac7af45863ba42cc2e002ce6225f094079fa8067fabe23b0376f4c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap one integer in a present borrowed-cell descriptor. |
| inputs / outputs | int64 value -&gt; Cell containing ScalarView{value}. |
| invariants | The returned cell is non-NULL and keeps the int64 alternative. |
| ownership | The scalar value is owned inline; no borrowed string or heap storage. |
| failure | No intentional failure for the fixed scalar conversion. |
| cost | O(1) scalar/optional construction; no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0005

[Lines 32–32](../../../../../tests/unit/sql_rows_output_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L32:sha256:5ba24e42fa862f4014274c991c62aa0ea50110a8dc2d883bdfc67831f8ec72cc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap one string view in a present borrowed-cell descriptor. |
| inputs / outputs | string_view value -&gt; Cell containing ScalarView{value}. |
| invariants | The returned cell is non-NULL; text bytes are not validated or copied here. |
| ownership | Returned string_view borrows caller bytes. |
| failure | No intentional failure for the fixed descriptor conversion. |
| cost | O(1) pointer/length/optional construction; no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0006

[Lines 33–39](../../../../../tests/unit/sql_rows_output_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L39:sha256:7d2c44fa8628c94479416d3a833c87d9788360dd8731bd93c6eb6b54a187bcc9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a borrowed nullable cell row into the test oracle owning row type. |
| inputs / outputs | span&lt;const Cell&gt; -&gt; Row with present exported scalars or disengaged NULL cells. |
| invariants | Preserves order and NULL; storage::export_scalar copies owning scalar/string representations. |
| ownership | Returned ordinary vector/scalars own copied strings independently of the input. |
| failure | Vector/string export allocation failures propagate. |
| cost | O(fields + copied string bytes) with ordinary test allocations; no native evaluation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0007

[Lines 40–42](../../../../../tests/unit/sql_rows_output_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L42:sha256:1aae5f2e913b03467000dc20ffef307b55e70a960e038fcf1c5793f70268d36d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the three-column physical catalog used by output tests. |
| inputs / outputs | No arguments -&gt; version-1 Catalog containing r(id non-NULL int64,x nullable int64,t nullable string). |
| invariants | This is a schema DTO; binding and native admission occur later. |
| ownership | Returned ordinary Catalog owns names and vectors. |
| failure | Ordinary DTO allocation failures propagate. |
| cost | Fixed-size catalog construction with ordinary test allocations; no binder/tree/runtime work. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0008

[Lines 43–49](../../../../../tests/unit/sql_rows_output_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L49:sha256:16d894252f792a6413640a7934ab1ced5716e9d628a6566d5e27e4b380be978a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a genuine SQL-row test program and expose a binder diagnostic as Error. |
| inputs / outputs | SQL string_view, Catalog and SqlRowsBindOptions -&gt; SqlRowsProgram from bind_sql_rows. |
| invariants | Diagnostic alternative is rejected; successful result is moved from the factory variant. |
| ownership | Inputs are borrowed for binding; returned immutable program retains its own account-backed metadata. |
| failure | BindingDiagnostic becomes Error with its exact code/message; exceptions otherwise propagate. |
| cost | Actual cold binding/metadata allocation for this SQL/schema/options; no query execution or test-oracle scan. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0009

[Lines 50–57](../../../../../tests/unit/sql_rows_output_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L57:sha256:72a23d44fe18c4cc5f40bf808d05e3ab64979a96b9513fc169c3f4516f3abe9b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose a finite test tree and create one genuine SQL runtime on the selected backend. |
| inputs / outputs | Genuine program and indexed flag -&gt; SqlRowsRuntime with chosen tree and default or indexed PhysicalOptions. |
| invariants | Noncontradictory programs require minimum_tree status proven_minimum plus tree; contradictory programs use the empty tree. |
| ownership | Cold exported core/tree DTOs are temporary; returned runtime owns its native/source state. |
| failure | Oracle assertion or runtime/compiler/resource failures fail the test. |
| cost | Cold core export/tree search/lowering/runtime allocation; no production update-path cost claim. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0010

[Lines 58–62](../../../../../tests/unit/sql_rows_output_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L62:sha256:c287a52b3ab563e421ac11e97a9d4044c95d21f279cf23ed9e2561a91e100eac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain committed SQL results into an independent owning test map. |
| inputs / outputs | Const SqlRowsRuntime -&gt; Bag keyed by exported nullable rows and cursor multiplicity. |
| invariants | Each distinct cursor row must insert once; repeated complete output keys fail the assertion. |
| ownership | Local cursor holds a reader lease until terminal iteration; returned ordinary map/rows own exported values. |
| failure | Cursor/export/allocation failures propagate; duplicate output record asserts. |
| cost | Actual complete result enumeration/export plus map insertion/string copies; this eager test drain is not used by native updates. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0011

[Lines 63–67](../../../../../tests/unit/sql_rows_output_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L67:sha256:7ca94b82eca96488163d20722c8f0ea5cee790e696652e632a9b658340968e9f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one action to throw the exact expected public Error code. |
| inputs / outputs | Callable action and expected string_view -&gt; normal return only after catching Error with matching code. |
| invariants | Normal action completion or wrong Error code fails an assertion; unrelated exception types escape. |
| ownership | Action is passed by value; expected bytes are borrowed through the call. |
| failure | Catches only Error for comparison; assertion/other exceptions fail the test. |
| cost | One action invocation plus fixed result/code comparison; action cost is separate and exception storage follows Error. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0012

[Lines 68–68](../../../../../tests/unit/sql_rows_output_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L68:sha256:0bbeab901b1f3d62402af07b622248f4dd8f879cef0957a4f9756062ec1f6b58
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add oracle unsigned weights after asserting representable sum. |
| inputs / outputs | uint64 left,right -&gt; left+right. |
| invariants | Requires right&lt;=UINT64_MAX-left before addition; no signed conversion. |
| ownership | Fixed scalar values only. |
| failure | Assertion fails on overflow input under maintained -UNDEBUG. |
| cost | O(1) arithmetic; no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0013

[Lines 69–69](../../../../../tests/unit/sql_rows_output_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L69:sha256:f50dcfad23a18602a9fbc1e141bc4b934618d10bfa8a25e87947b493efe8e572
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Multiply oracle unsigned weights after asserting representable product. |
| inputs / outputs | uint64 left,right -&gt; left*right. |
| invariants | Requires left==0 or right&lt;=UINT64_MAX/left; no division by zero or signed conversion. |
| ownership | Fixed scalar values only. |
| failure | Assertion fails on overflow input under maintained -UNDEBUG. |
| cost | O(1) arithmetic; no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0014

[Lines 70–72](../../../../../tests/unit/sql_rows_output_test.cpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L72:sha256:17d85dcaa5921f8408b08129ff84b9845152d45ae612ae7ca9d0dca7b133067d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain that the next oracle evaluates complete physical rows with compressed unsigned arithmetic. |
| inputs / outputs | Human-readable comment only; no runtime arguments or result. |
| invariants | The comment describes the adjacent code; it performs no check or state transition. |
| ownership | No runtime storage, borrow or owner is created. |
| failure | No executable failure or handler. |
| cost | No executable cost. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0015

[Lines 73–89](../../../../../tests/unit/sql_rows_output_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L89:sha256:ae39297cf04d78e011ca8791769bef80cb9a2a0e9e24db205729d0c565ceccdd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate weighted plain/self-join physical rows independently, then apply bag, DISTINCT or EXISTS presentation without native factors. |
| inputs / outputs | Bounded declared fixtures/public views in; owning ordinary test values, checked expectations or the declared test object out. |
| invariants | Reference models use full assignment joins or direct physical SQL rows, not incremental factor/output code. Tests keep source/full-group/SQL tuple identities and signed uint64 output units distinct. Assertions require maintained -UNDEBUG. |
| ownership | Test snapshots/maps/source copies are explicit verification workspace. Public output borrows are consumed within token/scratch lifetime; allocation-denial checks avoid owning diagnostics inside the denied scope. |
| failure | Unexpected diagnostics or assertion failures fail the test. Expected contract/resource errors are checked at exact boundaries and original state/account preservation is inspected. |
| cost | Finite test oracle/JSON/deep export costs belong to verification, not the production update path or a performance qualification. No release completeness claim follows from finite tests. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0016

[Lines 90–98](../../../../../tests/unit/sql_rows_output_test.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L98:sha256:b59b45b2f91523cba7cecc6bf7803e6cc66170930a692f4fe5d7c1fec09ed5de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact signed uint64 SQL endpoint differences without narrowing or dropping retractions. |
| inputs / outputs | Bounded declared fixtures/public views in; owning ordinary test values, checked expectations or the declared test object out. |
| invariants | Reference models use full assignment joins or direct physical SQL rows, not incremental factor/output code. Tests keep source/full-group/SQL tuple identities and signed uint64 output units distinct. Assertions require maintained -UNDEBUG. |
| ownership | Test snapshots/maps/source copies are explicit verification workspace. Public output borrows are consumed within token/scratch lifetime; allocation-denial checks avoid owning diagnostics inside the denied scope. |
| failure | Unexpected diagnostics or assertion failures fail the test. Expected contract/resource errors are checked at exact boundaries and original state/account preservation is inspected. |
| cost | Finite test oracle/JSON/deep export costs belong to verification, not the production update path or a performance qualification. No release completeness claim follows from finite tests. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0017

[Lines 99–112](../../../../../tests/unit/sql_rows_output_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L112:sha256:a5b3f1ebbd7b060c289438501e2ce819acdc486364cf91c52cdcc6eeb5ed576a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read each prepared SQL change under a denied-new guard, verify borrowed scratch/unit rules and collect independent owned answers. |
| inputs / outputs | Bounded declared fixtures/public views in; owning ordinary test values, checked expectations or the declared test object out. |
| invariants | Reference models use full assignment joins or direct physical SQL rows, not incremental factor/output code. Tests keep source/full-group/SQL tuple identities and signed uint64 output units distinct. Assertions require maintained -UNDEBUG. |
| ownership | Test snapshots/maps/source copies are explicit verification workspace. Public output borrows are consumed within token/scratch lifetime; allocation-denial checks avoid owning diagnostics inside the denied scope. |
| failure | Unexpected diagnostics or assertion failures fail the test. Expected contract/resource errors are checked at exact boundaries and original state/account preservation is inspected. |
| cost | Finite test oracle/JSON/deep export costs belong to verification, not the production update path or a performance qualification. No release completeness claim follows from finite tests. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0019

[Lines 114–147](../../../../../tests/unit/sql_rows_output_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L147:sha256:280b8152fcc06d107528a9776b6645f4591e97db2b9b67ca62d3d362556c3999
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two complete prepared decode passes, cumulative work, native capture kind and committed cursor against physical-row SQL endpoint oracles. |
| inputs / outputs | Bounded declared fixtures/public views in; owning ordinary test values, checked expectations or the declared test object out. |
| invariants | Reference models use full assignment joins or direct physical SQL rows, not incremental factor/output code. Tests keep source/full-group/SQL tuple identities and signed uint64 output units distinct. Assertions require maintained -UNDEBUG. |
| ownership | Test snapshots/maps/source copies are explicit verification workspace. Public output borrows are consumed within token/scratch lifetime; allocation-denial checks avoid owning diagnostics inside the denied scope. |
| failure | Unexpected diagnostics or assertion failures fail the test. Expected contract/resource errors are checked at exact boundaries and original state/account preservation is inspected. |
| cost | Finite test oracle/JSON/deep export costs belong to verification, not the production update path or a performance qualification. No release completeness claim follows from finite tests. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0021

[Lines 149–178](../../../../../tests/unit/sql_rows_output_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L178:sha256:9d0be3d50c4039fbb9f10ab9723998e8bb9c3f10ed8ddf55a9d5296cff094026
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test legacy output-disabled mode, exact/one-under row/work caps, scratch/index contracts, rollback/reused sequence, zero-allocation funded commit and empty zero-grant output. |
| inputs / outputs | Bounded declared fixtures/public views in; owning ordinary test values, checked expectations or the declared test object out. |
| invariants | Reference models use full assignment joins or direct physical SQL rows, not incremental factor/output code. Tests keep source/full-group/SQL tuple identities and signed uint64 output units distinct. Assertions require maintained -UNDEBUG. |
| ownership | Test snapshots/maps/source copies are explicit verification workspace. Public output borrows are consumed within token/scratch lifetime; allocation-denial checks avoid owning diagnostics inside the denied scope. |
| failure | Unexpected diagnostics or assertion failures fail the test. Expected contract/resource errors are checked at exact boundaries and original state/account preservation is inspected. |
| cost | Finite test oracle/JSON/deep export costs belong to verification, not the production update path or a performance qualification. No release completeness claim follows from finite tests. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0023

[Lines 180–207](../../../../../tests/unit/sql_rows_output_test.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L207:sha256:dbd5f01ee309bffa3c344d1622e56f923060ccf970da4d15ad894161d23475e3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check &gt;INT64 bag insertion/retraction and preview validity after source DTO destruction plus facade/token moves, then original-account release. |
| inputs / outputs | Bounded declared fixtures/public views in; owning ordinary test values, checked expectations or the declared test object out. |
| invariants | Reference models use full assignment joins or direct physical SQL rows, not incremental factor/output code. Tests keep source/full-group/SQL tuple identities and signed uint64 output units distinct. Assertions require maintained -UNDEBUG. |
| ownership | Test snapshots/maps/source copies are explicit verification workspace. Public output borrows are consumed within token/scratch lifetime; allocation-denial checks avoid owning diagnostics inside the denied scope. |
| failure | Unexpected diagnostics or assertion failures fail the test. Expected contract/resource errors are checked at exact boundaries and original state/account preservation is inspected. |
| cost | Finite test oracle/JSON/deep export costs belong to verification, not the production update path or a performance qualification. No release completeness claim follows from finite tests. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0024

[Lines 208–210](../../../../../tests/unit/sql_rows_output_test.cpp#L208); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L208-L210:sha256:b39c4b7721183cacd49136795d85f4167255fcfc20e5a7825b2816509f79afc2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the next test compares the former binding recipe and genuine freeze/rebind behavior. |
| inputs / outputs | Human-readable comment only; no runtime arguments or result. |
| invariants | The comment describes the adjacent code; it performs no check or state transition. |
| ownership | No runtime storage, borrow or owner is created. |
| failure | No executable failure or handler. |
| cost | No executable cost. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0025

[Lines 211–248](../../../../../tests/unit/sql_rows_output_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L211-L248:sha256:0d6a2787e4168fdb3f0b078c5745681a9a47ea152fc3660fcce7167cda245fca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare canonical binding bytes/hash and explicit retention, genuine rebind, changed inputs and receiving freeze behavior. |
| inputs / outputs | No arguments -&gt; void after the exact int64-parameter query/catalog fixtures and receiving-account assertions. |
| invariants | Default image is empty but hash/work equal opted-in output; retained bytes/hash equal independently assembled former CBOR. Parameter/null/catalog changes alter image; cross-account copy, same-account no-allocation alias and tiny-account failure are checked. |
| ownership | Named genuine program owners outlive all borrowed image views; cold Json/vector fixtures are ordinary test workspace. |
| failure | Exact MemoryFailure(limit) is required for tiny receiving account; unexpected exceptions/assertions fail the test. |
| cost | Finite cold bind/CBOR/freeze/equality/account checks; no SQL row scan or incremental update cost claim. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0027

[Lines 250–273](../../../../../tests/unit/sql_rows_output_test.cpp#L250); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L250-L273:sha256:e455430ee36da266a7247c34be699b483209020f532258689b0c22d82ed6307d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check explicit image retention costs using a one-MiB text parameter and genuine receiving freeze. |
| inputs / outputs | No arguments -&gt; void after binding default/retained programs and freezing each into separate receiving accounts. |
| invariants | Asserts default and frozen-empty images are empty with &lt;2MiB retained/peak storage, identical source hash/work across the flag, and additional retained image bytes are charged. Literal lookup uses the genuine output ExpressionId. |
| ownership | Local programs/accounts own all tested metadata; payload/options/receiving owners are ordinary bounded test fixtures. |
| failure | Unexpected binder/freeze/account failure or assertion fails the test; no old test threshold is changed. |
| cost | Finite cold binding/CBOR/hash/freeze copies for two one-MiB cases; no update-path/performance or general memory theorem. |
| Design | [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/sql_rows_binding_test.cpp](../../../../../tests/unit/sql_rows_binding_test.cpp) |

## B0028

[Lines 274–274](../../../../../tests/unit/sql_rows_output_test.cpp#L274); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L274-L274:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private test namespace. |
| inputs / outputs | No runtime arguments or result. |
| invariants | Only a lexical namespace boundary; it validates and executes nothing. |
| ownership | No runtime object is created or destroyed by this namespace closure. |
| failure | No executable failure. |
| cost | No executable cost. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0029

[Lines 275–285](../../../../../tests/unit/sql_rows_output_test.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L275-L285:sha256:4cd3c79f19b17809fa1b739e224606b4e715c2f7eb437098c99564437dd3af10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the finite two-backend prepared-output, binding and opt-in memory assertion families. |
| inputs / outputs | No arguments -&gt; 0 after named tests; unexpected std::exception prints to stderr and returns 1. |
| invariants | Runs bag/DISTINCT/EXISTS with and without selfjoin on reference/indexed storage, budget/rollback/lifetime cases, binding freeze and optional image memory cases. Finite success requires assertions enabled. |
| ownership | Called tests own their local fixtures; main owns only control flow and report streaming. |
| failure | Only unexpected std::exception is caught for failure reporting; assertions stop on failed expectations. |
| cost | Sum of explicit finite test work plus report output; no production overhead/performance claim. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |
