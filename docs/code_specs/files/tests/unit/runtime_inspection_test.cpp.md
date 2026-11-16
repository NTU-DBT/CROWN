# `tests/unit/runtime_inspection_test.cpp` — block usage map

[Source](../../../../../tests/unit/runtime_inspection_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d3ad391a49f2a78d89bcd5759bdaaf2e3218694db8f03c656eae90ddaecca057`. 457 lines partitioned into 32 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../tests/unit/runtime_inspection_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 20–22](../../../../../tests/unit/runtime_inspection_test.cpp#L20) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 23–23](../../../../../tests/unit/runtime_inspection_test.cpp#L23) | Explanatory comments or spacing. |  |
| [B0004 · 24–24](../../../../../tests/unit/runtime_inspection_test.cpp#L24) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../tests/unit/runtime_inspection_test.cpp#L25) | Explanatory comments or spacing. |  |
| [B0006 · 26–30](../../../../../tests/unit/runtime_inspection_test.cpp#L26) | Callable definition: VariableSet variables(std::initializer_list&lt;std::size_t&gt; values) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 31–31](../../../../../tests/unit/runtime_inspection_test.cpp#L31) | Explanatory comments or spacing. |  |
| [B0008 · 32–51](../../../../../tests/unit/runtime_inspection_test.cpp#L32) | Callable definition: PhysicalPlan inspection_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0008) |
| [B0009 · 52–52](../../../../../tests/unit/runtime_inspection_test.cpp#L52) | Explanatory comments or spacing. |  |
| [B0010 · 53–58](../../../../../tests/unit/runtime_inspection_test.cpp#L53) | Callable definition: Database inspection_database() | calls resize, insert, n, std::string; returns database; growth insert, resize · [reviewed contract](#b0010) |
| [B0011 · 59–59](../../../../../tests/unit/runtime_inspection_test.cpp#L59) | Explanatory comments or spacing. |  |
| [B0012 · 60–74](../../../../../tests/unit/runtime_inspection_test.cpp#L60) | Callable definition: const InvariantIssue& expect_issue(const InvariantReport& report, InvariantCode code, InvariantComponent component, const Row& ke… | calls std::runtime_error; returns issue; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 75–75](../../../../../tests/unit/runtime_inspection_test.cpp#L75) | Explanatory comments or spacing. |  |
| [B0014 · 76–80](../../../../../tests/unit/runtime_inspection_test.cpp#L76) | Callable definition: void expect_clean(const InvariantReport& report, const std::string& label) | calls check, valid, empty; guard check(report.complete, label + ": invariant inspection was incomplete"); · [reviewed contract](#b0014) |
| [B0015 · 81–81](../../../../../tests/unit/runtime_inspection_test.cpp#L81) | Explanatory comments or spacing. |  |
| [B0016 · 82–87](../../../../../tests/unit/runtime_inspection_test.cpp#L82) | Callable definition: PhysicalRuntimeOptions tiny_physical_update_budget() | calls ; returns options · [reviewed contract](#b0016) |
| [B0017 · 88–88](../../../../../tests/unit/runtime_inspection_test.cpp#L88) | Explanatory comments or spacing. |  |
| [B0018 · 89–95](../../../../../tests/unit/runtime_inspection_test.cpp#L89) | Callable definition: DeltaOptions tiny_delta_update_budget() | calls tiny_physical_update_budget; returns options · [reviewed contract](#b0018) |
| [B0019 · 96–96](../../../../../tests/unit/runtime_inspection_test.cpp#L96) | Explanatory comments or spacing. |  |
| [B0020 · 97–175](../../../../../tests/unit/runtime_inspection_test.cpp#L97) | Callable definition: void canonical_state_is_owner_independent() | calls inspection_plan, inspection_database, PhysicalRuntime::initialize, tiny_physical_update_budget; guard check(physical.owner() != replayed.owner(),; returns left.key &lt; right.key; left.node &lt; right.node; 5 loop sites · [reviewed contract](#b0020) |
| [B0021 · 176–176](../../../../../tests/unit/runtime_inspection_test.cpp#L176) | Explanatory comments or spacing. |  |
| [B0022 · 177–268](../../../../../tests/unit/runtime_inspection_test.cpp#L177) | Callable definition: void diagnostic_writer_is_deterministic_bounded_and_typed() | calls inspection_plan, inspection_database, PhysicalRuntime::initialize, canonical_state; guard check(physical_json == io::write_runtime_state(physical_state), · [reviewed contract](#b0022) |
| [B0023 · 269–269](../../../../../tests/unit/runtime_inspection_test.cpp#L269) | Explanatory comments or spacing. |  |
| [B0024 · 270–320](../../../../../tests/unit/runtime_inspection_test.cpp#L270) | Callable definition: void physical_inspection_localizes_actual_counter_corruption() | calls inspection_plan, inspection_database, PhysicalRuntime::initialize, tiny_physical_update_budget; guard check(!satisfied.valid(), "corrupt satisfied-child counter was reported clean"); · [reviewed contract](#b0024) |
| [B0025 · 321–321](../../../../../tests/unit/runtime_inspection_test.cpp#L321) | Explanatory comments or spacing. |  |
| [B0026 · 322–348](../../../../../tests/unit/runtime_inspection_test.cpp#L322) | Callable definition: void inspection_budgets_never_report_clean_after_stopping() | calls inspection_plan, inspection_database, PhysicalRuntime::initialize, tiny_physical_update_budget; guard check(!stopped_for_work.complete && !stopped_for_work.valid(), · [reviewed contract](#b0026) |
| [B0027 · 349–349](../../../../../tests/unit/runtime_inspection_test.cpp#L349) | Explanatory comments or spacing. |  |
| [B0028 · 350–406](../../../../../tests/unit/runtime_inspection_test.cpp#L350) | Callable definition: void delta_inspection_localizes_actual_live_counter_corruption() | calls inspection_plan, inspection_database, DeltaRuntime::initialize, tiny_delta_update_budget; guard check(canonical.live.has_value(), "delta initialization omitted live state");; returns item.node == NodeId{1}; 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 407–407](../../../../../tests/unit/runtime_inspection_test.cpp#L407) | Explanatory comments or spacing. |  |
| [B0030 · 408–438](../../../../../tests/unit/runtime_inspection_test.cpp#L408) | Callable definition: int dump_diagnostic(const std::string& mode) | calls inspection_plan, inspection_database, PhysicalRuntime::initialize, io::write_runtime_state; returns 0; 0 · [reviewed contract](#b0030) |
| [B0031 · 439–441](../../../../../tests/unit/runtime_inspection_test.cpp#L439) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0031) |
| [B0032 · 442–457](../../../../../tests/unit/runtime_inspection_test.cpp#L442) | Callable definition: int main(int argc, char** argv) | calls dump_diagnostic, std::runtime_error, canonical_state_is_owner_independent, diagnostic_writer_is_deterministic_bounded_and_typed; returns dump_diagnostic(argv\[1\]); 0 · [reviewed contract](#b0032) |

## B0001

[Lines 1–19](../../../../../tests/unit/runtime_inspection_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:5d4c483edd9835c656434991b3bdad88439ad6e9e4a7bd43613be874451f8ed8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare runtime_inspection_test.cpp: include "crown/planner/lower.hpp", "crown/io/document.hpp", "crown/io/inspection.hpp", "crown/runtime/delta.hpp", "runtime_probe.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;initializer_list&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 20–22](../../../../../tests/unit/runtime_inspection_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a runtime-inspection assertion with an owning diagnostic message. |
| inputs / outputs | Inputs: condition and const std::string reference. |
| invariants | Throws runtime_error with message if false; call-site expressions such as label + suffix construct their string before entering this helper, even on true conditions. |
| ownership | Message borrowed during call; runtime_error owns failure text. |
| failure | False throws; eager call-site concatenation may itself allocate before the predicate is checked. |
| cost | One predicate check; not allocation-instrumented in this file. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp) |

## B0004

[Lines 24–24](../../../../../tests/unit/runtime_inspection_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one int64 test scalar to the IR Value alternative. |
| inputs / outputs | Input: int64 value. Output: Value. |
| invariants | No range/domain conversion beyond constructing the variant alternative. |
| ownership | Scalar value copied into returned variant. |
| failure | Ordinary variant construction errors propagate. |
| cost | Fixed value construction. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0006

[Lines 26–30](../../../../../tests/unit/runtime_inspection_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet variables(std::initializer_list<std::size_t> values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an owning VariableSet from initializer-list indices. |
| inputs / outputs | Input: initializer_list&lt;size_t&gt;. Output: set of corresponding VariableId values. |
| invariants | Each element is inserted; duplicate indices collapse by set semantics. |
| ownership | Returned set owns its nodes; initializer list is borrowed only during the call. |
| failure | Ordinary set allocation failure propagates; no runtime account is supplied. |
| cost | O(n log u) insertion for n listed ids and u unique ids. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/ir/tree.hpp](../../../../../include/crown/ir/tree.hpp) |

## B0008

[Lines 32–51](../../../../../tests/unit/runtime_inspection_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan inspection_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the generalized-root fixture plan used by inspection assertions. |
| inputs / outputs | No inputs. Output: plan over one unary int64/string table, four query occurrences and six tree nodes: one generalized root, a three-child generalized node, and four native leaves. |
| invariants | Tree routes root and three-way child structure to occurrences 0..3; returned plan is used for physical and Delta runtime initialization. |
| ownership | Catalog/query/tree are ordinary local fixture objects; plan owns lowered metadata. |
| failure | Planner validation/allocation errors propagate. |
| cost | Fixed six-node/four-occurrence setup and lowering. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/tree.hpp](../../../../../include/crown/ir/tree.hpp) |

## B0010

[Lines 53–58](../../../../../tests/unit/runtime_inspection_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database inspection_database() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-row source database with typed integer and string cells. |
| inputs / outputs | No input. Output: one-table Database containing (11, "row-11"). |
| invariants | The database owns ordinary caller-side row/string storage. |
| ownership | No account is attached by this helper. |
| failure | Ordinary allocation failure propagates. |
| cost | Fixed one-row fixture construction. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/catalog/catalog.hpp](../../../../../include/crown/catalog/catalog.hpp) |

## B0012

[Lines 60–74](../../../../../tests/unit/runtime_inspection_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const InvariantIssue& expect_issue(const InvariantReport& report,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find an exact localized issue and return a reference into its report. |
| inputs / outputs | Inputs: report, code/component, Row key, optional node/occurrence/table, expected and actual values. Output: const reference to matching InvariantIssue. |
| invariants | All compared fields must match; search is linear. Returned reference is valid only while the report and its issue storage remain alive. |
| ownership | Key input is borrowed for comparison; report owns issue/key payload. No issue copy is returned. |
| failure | Missing match throws runtime_error. |
| cost | O(number of report issues), plus typed key comparisons; no export or scan of runtime state. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0014

[Lines 76–80](../../../../../tests/unit/runtime_inspection_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_clean(const InvariantReport& report, const std::string& label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a complete, valid report with no remaining issues. |
| inputs / outputs | Inputs: report and label string. |
| invariants | Checks complete, valid(), and empty issues separately. Call-site label concatenations are eagerly built before check even when checks succeed. |
| ownership | Report is borrowed; labels are caller-owned values. |
| failure | Any failed condition throws runtime_error; eager label concatenation can allocate first. |
| cost | Three constant-field/container checks; no allocation-count assertion. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp) |

## B0016

[Lines 82–87](../../../../../tests/unit/runtime_inspection_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntimeOptions tiny_physical_update_budget() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a physical options fixture whose update/support work allowances are zero. |
| inputs / outputs | No input. Output: PhysicalRuntimeOptions with work_limit=0 and support.work_limit=0. |
| invariants | These are runtime update budgets; they are not InspectionOptions.work_limit. |
| ownership | Returns an options value only. |
| failure | No validation here; runtime paths enforce budgets later. |
| cost | Fixed assignments. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0018

[Lines 89–95](../../../../../tests/unit/runtime_inspection_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions tiny_delta_update_budget() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create Delta options in delta mode with both update work budgets zero. |
| inputs / outputs | No input. Output: DeltaOptions with mode delta and physical options from tiny_physical_update_budget(). |
| invariants | Sets update work limits, not inspection report limits; other fields keep defaults. |
| ownership | Returns ordinary options value. |
| failure | Invalid later use propagates runtime error. |
| cost | Fixed option initialization. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0020

[Lines 97–175](../../../../../tests/unit/runtime_inspection_test.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void canonical_state_is_owner_independent() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare canonical physical and Delta DTOs across independent direct and insertion-replay initializations. |
| inputs / outputs | No inputs. Initializes two PhysicalRuntime and two DeltaRuntime facades from same fixture/database, one direct and one insertion_replay. |
| invariants | Requires distinct owner ids and equal canonical DTOs for each runtime pair; checks selected sorted source/derivation/support/live rows and bucket fields. This tests exported-value equality for this fixture, not account sharing, universal owner independence, or proof validity. |
| ownership | Canonical state methods create ordinary owning DTOs; their nested std::vector/string/Row allocations are caller exports. Runtime owners remain local through checks. |
| failure | Plan/build/inspection errors or ordering mismatch fail; no allocation hook/cap assertions. |
| cost | Four runtime initializations, canonical DTO exports/equality and ordering checks, and four full invariant inspections over the one-row, six-node fixture; no measured CPU or byte count. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 177–268](../../../../../tests/unit/runtime_inspection_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void diagnostic_writer_is_deterministic_bounded_and_typed() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check canonical-state and invariant-report JSON determinism, typed values, byte limits, and one localized corruption. |
| inputs / outputs | No inputs. Exports physical and Delta canonical states; parses typed envelopes; mutates support parent count to 5, exports report, restores it; repeats exact-size and size-minus-one limits for all three writers. |
| invariants | Assertions cover v1 kind/schema, selected int/string row types, Delta live presence, deterministic text, and a parent support_count issue with expected old count/actual 5/key 11/node 1. It explicitly restores the prior projection and then checks a clean inspection. Exact encoded byte cap succeeds; one-byte less yields Error code resource_limit. No report authenticity, memory-account byte cap, operator-new count, or whole-export temporary limit is asserted. |
| ownership | Canonical DTOs and JSON parse trees are ordinary owning exports; report issue key uses runtime account while held. Probe corruption mutates live test runtime directly and is explicitly restored before clean inspection. |
| failure | Writer limit failures accept crown::Error only with resource_limit; other exceptions escape. Probe mutation has no automatic rollback; explicit set_projection restore is required. |
| cost | Serializes/parses finite small canonical graphs and one report. Byte limit is output string size; JSON DOM/output temporaries and scalar export may allocate outside query account. No CPU/RSS claim. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0024

[Lines 270–320](../../../../../tests/unit/runtime_inspection_test.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_inspection_localizes_actual_counter_corruption() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Corrupt and restore four physical/support counters, checking their exact localized reports. |
| inputs / outputs | No inputs. Initializes fixture, then separately changes child satisfied count to 2, parent projection to 8, visible projection to 9, and occurrence-0 derivation to 7. |
| invariants | Each report must contain exact code/component/key/node and expected/actual tuple; each is invalid. For satisfied/parent/visible/derivation expected values are 3/old parent/old visible/1 respectively. Probe returns old value; test restores after each and requires a clean report. |
| ownership | RuntimeTestProbe edits actual private state without normal propagation; report owns issue keys; explicit restoration happens before subsequent check. No restoration guard protects exceptional early exit. |
| failure | Any missing/mismatched issue or failure to restore fails; inspection resource failures propagate. |
| cost | Eight full physical inspections over the fixture: four after counter corruptions and four clean checks after explicit restoration. No allocator-call or runtime work-cap measurement. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0026

[Lines 322–348](../../../../../tests/unit/runtime_inspection_test.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void inspection_budgets_never_report_clean_after_stopping() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show that zero work or zero issue budgets cannot produce a clean invariant report. |
| inputs / outputs | No inputs. Runs physical inspection with work_limit 0, mutates parent projection, then issue_limit 0, restores and inspects again. |
| invariants | Zero-work report must be incomplete and invalid. Corrupt zero-issue report must be incomplete, invalid and empty. Clean report required after explicit restoration. |
| ownership | Reports own issue arrays/keys under runtime account; direct probe mutation bypasses normal update propagation and restoration is explicit. |
| failure | Assertion failure throws; inspection stop is represented in report fields rather than expected exception. |
| cost | One early-stopped inspection, one issue-stopped inspection and one restored full inspection. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0028

[Lines 350–406](../../../../../tests/unit/runtime_inspection_test.cpp#L350); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void delta_inspection_localizes_actual_live_counter_corruption() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Corrupt and restore Delta live buckets and aggregate totals, checking independent live-invariant diagnostics. |
| inputs / outputs | No inputs. Initializes Delta fixture; uses exported canonical live factors to select first parent and child bucket for node 1, mutates each count by +5/+6, then mutates live factor/parent/child aggregate totals by +1. |
| invariants | Each report must localize exact component/key/expected/actual and be invalid; each mutation is restored explicitly before clean inspection. Canonical factor/bucket data is an ordinary export used to select fixture keys, not a proof token. |
| ownership | Probe changes actual private Delta index/count state; canonical DTO copies rows. Report keys are independently owned under account; restore is explicit and not exception-safe. |
| failure | Missing bucket, wrong report fields, or failed restoration fails; inspection exceptions propagate. |
| cost | Ten full Delta inspections: one after each of two bucket and three aggregate corruptions, plus one clean inspection after restoring each value. Each includes physical inspection and live re-derivation/grouping. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0030

[Lines 408–438](../../../../../tests/unit/runtime_inspection_test.cpp#L408); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int dump_diagnostic(const std::string& mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serve three test-only JSON dump modes and restore the intentional report corruption. |
| inputs / outputs | Input: mode string. Outputs physical canonical JSON, Delta canonical JSON, or a corrupted-then-restored invariant report JSON to stdout; returns 0 on recognized mode. |
| invariants | Physical mode initializes default runtime; Delta mode uses zero-update-budget fixture. Report mode changes parent count, writes report, restores old count, and requires clean follow-up. Unknown mode throws runtime_error. |
| ownership | Plans/database/DTO and output strings are caller-owned; test probe mutates runtime state and explicit restoration is required. No native report is retained beyond branch. |
| failure | Unknown mode or restore/clean assertion failure throws; outer main translates std::exception to status 1. |
| cost | Builds the small plan/database first; a recognized mode initializes one runtime and performs physical/Delta canonical-state JSON export or invariant inspection plus report JSON. Report mode performs a second clean inspection after restoration. No byte limit, account cap, or allocation counter is measured here. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp) |

## B0031

[Lines 439–441](../../../../../tests/unit/runtime_inspection_test.cpp#L439); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L439-L441:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in runtime_inspection_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0032

[Lines 442–457](../../../../../tests/unit/runtime_inspection_test.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc, char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run runtime inspection semantic tests or dispatch one diagnostic dump mode. |
| inputs / outputs | Inputs: argc/argv. With one argument dispatches dump_diagnostic; with no args runs five fixture groups. Other arities throw. |
| invariants | No-argument groups cover canonical owner independence, writer behavior, physical corruption, stop budgets, and Delta live corruption. Catches std::exception, writes message and returns 1; success prints completion and returns 0. |
| ownership | All plans/runtimes/reports remain local to each called function. |
| failure | Unknown args or any thrown failure produce status 1. |
| cost | Finite single-row/six-node fixtures; each full inspection may scan state. This packet did not execute it. |
| Design | [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp) |
