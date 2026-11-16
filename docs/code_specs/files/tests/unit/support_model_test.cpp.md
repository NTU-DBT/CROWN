# `tests/unit/support_model_test.cpp` — block usage map

[Source](../../../../../tests/unit/support_model_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `eca58dafabd7c97bb8eae5026c0053a5fa620b057f863365c6ccf112223409dd`. 408 lines partitioned into 28 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–28](../../../../../tests/unit/support_model_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 29–29](../../../../../tests/unit/support_model_test.cpp#L29) | Callable definition: void check(bool value,const std::string& message) | calls std::runtime_error; guard void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0002) |
| [B0003 · 30–33](../../../../../tests/unit/support_model_test.cpp#L30) | Callable definition: std::string read(const std::filesystem::path& path) | calls stream, check, bool, string; guard std::ifstream stream(path); check(bool(stream),"cannot open "+path.string());; returns {std::istreambuf_iterator&lt;char&gt;{stream},std::istreambuf_iterator&lt;char&gt;{}} · [reviewed contract](#b0003) |
| [B0004 · 34–34](../../../../../tests/unit/support_model_test.cpp#L34) | Callable definition: Row row(const io::Json& values) | calls push_back, io::read_scalar; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 35–37](../../../../../tests/unit/support_model_test.cpp#L35) | Callable definition: VariableSet intersection(const auto& a,const auto& b) | calls std::set_intersection, begin, end, std::inserter; returns result · [reviewed contract](#b0005) |
| [B0006 · 38–42](../../../../../tests/unit/support_model_test.cpp#L38) | Callable definition: Assignment assignment(const Row& row,const auto& scope) | calls check, size, begin, emplace; guard check(row.size()==scope.size(),"oracle scope width mismatch"); Assignment result; auto value=row.be…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 43–45](../../../../../tests/unit/support_model_test.cpp#L43) | Callable definition: Row project(const Assignment& value,const auto& scope) | calls push_back, at; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 46–57](../../../../../tests/unit/support_model_test.cpp#L46) | Callable definition: Assignments join(const Assignments& left,const Assignments& right) | calls emplace, insert, std::move; returns result; growth emplace, insert; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 58–63](../../../../../tests/unit/support_model_test.cpp#L58) | Type/record definition: struct ExpectedNode |  · [reviewed contract](#b0009) |
| [B0010 · 64–64](../../../../../tests/unit/support_model_test.cpp#L64) | Type/record definition: struct Oracle |  · [reviewed contract](#b0010) |
| [B0011 · 65–117](../../../../../tests/unit/support_model_test.cpp#L65) | Callable definition: Oracle recompute(const auto& plan,const std::vector&lt;Relation&gt;& inputs) | calls reference::input::query, query, tree, empty; guard check(found!=tree.nodes.end(),"oracle lost occurrence"); const auto id=static_cast&lt;std::size_t&gt;(fou…; returns result; result; growth emplace, emplace_back, insert, push_back, reserve, resize; 15 loop sites; source comment (unverified): // An independent ordinary CQ over one relation per logical occurrence also · [reviewed contract](#b0011) |
| [B0012 · 118–120](../../../../../tests/unit/support_model_test.cpp#L118) | Callable definition: Counts counts(const std::vector&lt;ProjectionKeySnapshot&gt;& keys) | calls check, emplace, crown::storage::export_row, values; guard Counts result; for (const auto& key : keys) check(result.emplace(crown::storage::export_row(key.key…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 121–134](../../../../../tests/unit/support_model_test.cpp#L121) | Callable definition: Members members(const SupportRuntime& runtime,const SupportSnapshot& snapshot) | calls check, emplace, get, values; guard check(result.emplace(Membership{node,role,values},handle).second,"duplicate runtime membership");; returns result; growth emplace; 5 loop sites · [reviewed contract](#b0013) |
| [B0014 · 135–164](../../../../../tests/unit/support_model_test.cpp#L135) | Callable definition: void compare(const SupportRuntime& runtime,const std::vector&lt;Relation&gt;& inputs) | calls check_invariants, snapshot, recompute, plan; guard check(actual.has_answer==!expected.answers.empty(),"root answer presence differs from A04");; growth insert, push_back; 7 loop sites · [reviewed contract](#b0014) |
| [B0015 · 165–170](../../../../../tests/unit/support_model_test.cpp#L165) | Type/record definition: struct ReferenceValueState |  · [reviewed contract](#b0015) |
| [B0016 · 171–173](../../../../../tests/unit/support_model_test.cpp#L171) | Callable definition: template&lt;class Left,class Right&gt;bool same_state(const Left& a,const Right& b) | calls std::ranges::equal; returns a.member==b.member && a.satisfied==b.satisfied && std::ranges::equal(a.child_present,b.child_presen… · [reviewed contract](#b0016) |
| [B0017 · 174–174](../../../../../tests/unit/support_model_test.cpp#L174) | Type/record definition: struct AuditValue |  · [reviewed contract](#b0017) |
| [B0018 · 175–175](../../../../../tests/unit/support_model_test.cpp#L175) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 176–188](../../../../../tests/unit/support_model_test.cpp#L176) | Callable definition: AuditState audit_state(const SupportSnapshot& snapshot,const Members& handles) | calls check, emplace, at, std::move; guard const Membership key{node,role,values}; check(result.emplace(key,AuditValue{handles.at(key),std::mo…; returns result; growth emplace; 5 loop sites · [reviewed contract](#b0019) |
| [B0020 · 189–242](../../../../../tests/unit/support_model_test.cpp#L189) | Callable definition: void audit_journal(const SupportRuntime& runtime,const SupportEpoch& epoch,AuditState before,const AuditState& after) | calls size, storage::export_row, tuple, values; guard check(record.ordinal==i+1 && record.cause&gt;0 && record.cause&lt;=epoch.metrics.events_applied,"journal …; growth insert, push_back; 5 loop sites · [reviewed contract](#b0020) |
| [B0021 · 243–283](../../../../../tests/unit/support_model_test.cpp#L243) | Callable definition: SupportEpoch update(SupportRuntime& runtime,std::vector&lt;Relation&gt;& inputs,NodeId node,SetOperation operation,Row values) | calls snapshot, members, insert, erase; guard check(effect.native_changed==changed,"native set/no-op result differs"); compare(runtime,inputs);; returns effect; growth emplace, insert; 4 loop sites · [reviewed contract](#b0021) |
| [B0022 · 284–293](../../../../../tests/unit/support_model_test.cpp#L284) | Callable definition: Value sample(ScalarType type,std::uint64_t value) | calls std::string, Date::parse, Decimal::parse, std::runtime_error; returns static_cast&lt;std::int64_t&gt;(value); std::string(value==0 ? @ : value==1 ? @ : @ ) · [reviewed contract](#b0022) |
| [B0023 · 294–318](../../../../../tests/unit/support_model_test.cpp#L294) | Callable definition: void manual(const std::filesystem::path& root) | calls io::Json::parse, read, at, io::read_document; guard check(effect.sequence==event.at("sequence").get&lt;std::uint64_t&gt;() && effect.native_changed==expected…; returns result; growth emplace, insert; 5 loop sites · [reviewed contract](#b0023) |
| [B0024 · 319–347](../../../../../tests/unit/support_model_test.cpp#L319) | Callable definition: void randomized(const std::filesystem::path& root) | calls io::Json::parse, read, at, io::read_document; guard check(!fifo.has_answer() && !lifo.has_answer(),"complete cleanup retained answer truth");; growth insert, push_back; 7 loop sites · [reviewed contract](#b0024) |
| [B0025 · 348–371](../../../../../tests/unit/support_model_test.cpp#L348) | Callable definition: void reverse_lookup_and_deep_queue() | calls reset, runtime, planner::lower_tree, apply; guard check(effect.metrics.native_record_visits==2 && effect.metrics.copied_rows==0 && runtime.snapshot()…; returns value.handle.node==NodeId{0} && value.handle.role==SupportRole::records; growth insert, push_back; 3 loop sites · [reviewed contract](#b0025) |
| [B0026 · 372–402](../../../../../tests/unit/support_model_test.cpp#L372) | Callable definition: void physical_derivations_bridge() | calls frontend::bind_sql, check, frontend::normalize_sql, planner::lower_normalized; guard const auto bound=frontend::bind_sql("SELECT DISTINCT x FROM r",catalog); check(std::holds_alternati…; growth insert, resize; 5 loop sites · [reviewed contract](#b0026) |
| [B0027 · 403–403](../../../../../tests/unit/support_model_test.cpp#L403) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0027) |
| [B0028 · 404–408](../../../../../tests/unit/support_model_test.cpp#L404) | Callable definition: int main(int argc,char** argv) | calls check, manual, randomized, reverse_lookup_and_deep_queue; guard check(argc==2,"usage: crown_support_model_test REPOSITORY"); manual(argv\[1\]); randomized(argv\[1\]); …; returns 1 · [reviewed contract](#b0028) |

## B0001

[Lines 1–28](../../../../../tests/unit/support_model_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L28:sha256:d617ae7f20a2b29ae3fb2a5918b74d09223700fd4660ecc6bf65669d3c2b776b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare support_model_test.cpp: include "crown/runtime/support.hpp", "crown/io/support.hpp", "crown/io/tree.hpp", "crown/planner/lower.hpp", "crown/frontend/adapter.hpp", "evaluator.hpp", "native_input.hpp", &lt;algorithm&gt;, &lt;deque&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;random&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;tuple&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 29–29](../../../../../tests/unit/support_model_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a model-test assertion with its local diagnostic when a condition is false. |
| inputs / outputs | Boolean condition and borrowed message string in; no value out. A true condition returns normally; a false one throws \`std::runtime_error(message)\`. |
| invariants | The helper body performs no coercion or recovery and throws only when the condition is false. Callers passing literals convert them to std::string before entry, so failure-only use in the body does not defer argument construction. |
| ownership | The caller owns the message for the call. On failure the exception owns its diagnostic representation; no test state is retained by the helper. |
| failure | Failure is the intended assertion signal; exception construction can itself fail under allocation pressure. The top-level test driver catches standard exceptions. |
| cost | One Boolean branch in the helper body on success. C++ evaluates caller argument expressions before every call, even when the predicate is true; literal arguments convert to std::string, and dynamic concatenations may allocate (short messages may fit small-string storage). Failure constructs and throws std::runtime_error from the supplied message. No production work counter covers this harness path; no CPU, allocator-byte, all-heap, or RSS measurement is made. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0003

[Lines 30–33](../../../../../tests/unit/support_model_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const std::filesystem::path& path)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one fixture file into an owned string for the test parsers. |
| inputs / outputs | Filesystem path in; stream text yielded by \`std::istreambuf_iterator\` as an owned \`std::string\` out. |
| invariants | The stream must open successfully. This helper does not check tree-scope width or parsing; callers perform those checks after reading. |
| ownership | The function owns the \`ifstream\` for the call and returns a new string owning the read bytes; the caller owns that string after return. |
| failure | Open failure is converted to the supplied \`check\` exception. There is no explicit post-read I/O-state check; allocation and parser failures propagate to the test driver. |
| cost | Reads the file into an owned string, so byte work and retained string capacity grow with file length. Before every check call, including a successful open, \`path.string()\` and the \`"cannot open " + path.string()\` diagnostic are evaluated; concatenation may allocate. Stream buffers and output storage are ordinary test-process work. No CPU, allocator-byte, all-heap, or RSS measurement is made. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0004

[Lines 34–34](../../../../../tests/unit/support_model_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row row(const io::Json& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one JSON array of scalar cells to the typed row shape used by fixture updates and expected projection keys. |
| inputs / outputs | \`io::Json\` array in; a \`Row\` of \`Value\` objects in the same element order out. |
| invariants | Each element is decoded by \`io::read_scalar\`; this helper does not check tree-scope width or sort columns. |
| ownership | The result owns its vector and scalar values, including string payloads; it does not borrow JSON storage. |
| failure | Invalid scalar JSON or vector/value allocation failures propagate; arity is checked later when assigned to a compiled scope. |
| cost | One scalar conversion and one result-vector append per array element; bytes and allocations grow with total scalar payload. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0005

[Lines 35–37](../../../../../tests/unit/support_model_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet intersection(const auto& a,const auto& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the shared variable IDs for a pair of sorted scopes in the independent test oracle. |
| inputs / outputs | Two ordered variable sets in; a new ordered \`VariableSet\` containing their intersection out. |
| invariants | Uses \`std::set_intersection\` over the input iteration order and leaves both arguments unchanged. |
| ownership | The output owns its set nodes; inputs remain caller-owned. |
| failure | No domain error is handled here; iterator/container allocation exceptions propagate. |
| cost | Scans the ordered unique std::set inputs in linear comparison work in \|a\|+\|b\|; each common variable is inserted into a new ordered set node (with the end-position hint supplied by std::inserter). This is oracle work, not a runtime index probe. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0006

[Lines 38–42](../../../../../tests/unit/support_model_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Assignment assignment(const Row& row,const auto& scope)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair a projected row with the exact variable IDs of one node scope for full-join oracle calculations. |
| inputs / outputs | Row and ordered scope in; \`std::map&lt;VariableId,Value&gt;\` assignment out. |
| invariants | Requires row width equal to scope width, then consumes row values in scope iteration order and inserts one value per variable. |
| ownership | The map owns copied \`Value\`s and its nodes; the input row/scope are borrowed only during construction. |
| failure | Width mismatch throws through \`check\`; value/map allocation failures propagate. Duplicate scope IDs are not expected because scopes are sets. |
| cost | For each scope member, copies one Value into an ordered std::map insertion; comparison work grows with scope width (logarithmic map search per insertion), with one map node and any scalar payload storage per binding. This is test-oracle allocation, not a runtime bound. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0007

[Lines 43–45](../../../../../tests/unit/support_model_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row project(const Assignment& value,const auto& scope)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project one full oracle assignment into the variable order of a requested scope. |
| inputs / outputs | Assignment map and ordered variable scope in; a new ordered \`Row\` out. |
| invariants | For each variable, reads \`value.at(variable)\` in scope order; output arity and order therefore follow that scope. |
| ownership | The returned row owns copied values; the assignment and scope remain unmodified. |
| failure | A missing variable throws \`std::out_of_range\`; output/value allocation failures propagate. |
| cost | Per projected variable, std::map::at performs an ordered lookup (logarithmic in assignment width), then copies a Value and appends it to the owned output vector. Work and payload storage grow with scope width and scalar sizes. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0008

[Lines 46–57](../../../../../tests/unit/support_model_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Assignments join(const Assignments& left,const Assignments& right)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the natural join of two assignment sets for the independent subtree and visible-key oracle. |
| inputs / outputs | Two sets of ordered variable/value maps in; a deduplicated set of compatible merged assignments out. |
| invariants | Tests every left/right pair, starts each candidate as a copy of the left assignment, and rejects the pair at the first unequal shared value. Compatible results are unique by \`std::set\` ordering. |
| ownership | Input sets are borrowed; each combined map and retained result node owns copies of participating values. |
| failure | There is no resource cap or fallback. Standard map/set allocation failures propagate; incompatible pairs are skipped normally. |
| cost | Enumerates up to \|left\|×\|right\| candidate pairs. Each candidate copies the left ordered map, attempts an ordered insertion/lookup for each right binding until mismatch, and inserts a compatible merged map into an ordered result set. Intermediate candidate and result storage can grow with the full join; no runtime work counter bounds this oracle. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0009

[Lines 58–63](../../../../../tests/unit/support_model_test.cpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExpectedNode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the recomputed relation and metadata expectations for one node in the support model. |
| inputs / outputs | No constructor arguments; fields collect expected records, survivors, parent projection counts, optional visible projection counts, and per-record child-presence flags. |
| invariants | The oracle gives \`visible\` a value only for nodes in the derived C* region; \`children\` associates each record row with one Boolean per ordered child. |
| ownership | This is test-owned value state: relation/map/set nodes, rows, values, and child vectors are owned by this object. |
| failure | No methods validate field consistency; the construction path and later \`compare\` assertions do. Container allocation failures propagate. |
| cost | Storage grows with all materialized node records/survivors, distinct P/E keys, and child flags in the oracle state. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0010

[Lines 64–64](../../../../../tests/unit/support_model_test.cpp#L64); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Oracle {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle the per-node recomputed support state and the independently evaluated answer relation. |
| inputs / outputs | No inputs at construction; owns \`nodes\` and \`answers\` fields populated by \`recompute\`. |
| invariants | Node-vector positions are indexed by \`NodeId\`; answers are a set of output rows. |
| ownership | The vectors and answer relation own their contents; the bundle has no runtime handle or borrowed plan reference. |
| failure | No methods catch allocation or recomputation failures. |
| cost | Retained size is proportional to materialized per-node oracle state plus distinct final answers; it is not bounded by support-runtime work counters. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0011

[Lines 65–117](../../../../../tests/unit/support_model_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Oracle recompute(const auto& plan,const std::vector<Relation>& inputs)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild expected support from complete input relations by materializing subtree assignment joins, then independently evaluate the query answer. |
| inputs / outputs | Verified plan and one test-owned input relation per tree node in; \`Oracle\` with node records/survivors/P/E counts/child flags and answers out. |
| invariants | Contradiction returns empty expected state; an empty atom list returns the one empty answer. Otherwise it derives parent/order and C* membership, computes bottom-up full assignments and local projections, and calls \`reference::evaluate\` over one relation per logical occurrence. |
| ownership | Inputs and plan are borrowed; all assignment sets, expected relations, key maps, catalog/query expansion, and result rows are locally owned and released on return. |
| failure | Requires a valid lowered plan/tree and an inputs vector aligned by NodeId, with native rows matching each node scope. It indexes tree and input vectors directly, so misalignment is not bounds-checked here. Query/tree parsing and lowering happen in callers; lost occurrence/scope checks, reference evaluation, and allocation failures propagate. |
| cost | Potentially large: repeatedly materializes complete subtree assignment sets and joins; cost/memory follow intermediate Cartesian candidates and ordered-container operations, not the maintained runtime’s affected-record counters. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [docs/support_invariants.md](../../../../support_invariants.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp) |

## B0012

[Lines 118–120](../../../../../tests/unit/support_model_test.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Counts counts(const std::vector<ProjectionKeySnapshot>& keys)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a runtime projection-key snapshot into the row-to-exact-support map used by the independent oracle comparisons. |
| inputs / outputs | Projection-key snapshot vector in; \`Counts\` map from exported key row to support count out. |
| invariants | Each key is inserted once; duplicate exported rows fail instead of silently combining or overwriting counts. |
| ownership | The result map owns exported rows; snapshot tuple storage is read only during conversion. |
| failure | Duplicate key triggers \`check\`; row export and ordered-map allocation failures propagate. |
| cost | One export and ordered-map insertion per snapshot key; comparisons and owned scalar bytes scale with key count and row widths. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0013

[Lines 121–134](../../../../../tests/unit/support_model_test.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Members members(const SupportRuntime& runtime,const SupportSnapshot& snapshot)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a row-identity map of all live record, survivor, P, and E memberships together with their public stable handles. |
| inputs / outputs | Runtime and owning snapshot in; \`Members\` keyed by \`(node, role, exported row)\` out. |
| invariants | Rejects duplicate logical memberships and checks each handle resolves through \`runtime.get\` to the same tuple. Survivor handles are obtained by \`runtime.find\`; P/E and records use handles carried by snapshots. |
| ownership | Map keys own exported row copies and values own \`SupportHandle\`s; runtime/snapshot are borrowed for the call. |
| failure | Duplicate membership or a mismatched handle returned by the checked add path throws via check; handle, export, and allocation failures propagate. For each survivor the code dereferences \`runtime.find(...)\` before calling add, without checking the optional; the live snapshot survivor is a precondition, and its violation is not converted to a diagnostic check. |
| cost | Walks the full support snapshot, exports every key, performs handle lookups, and inserts into an ordered map; this is full-state audit work, not a local-update bound. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0014

[Lines 135–164](../../../../../tests/unit/support_model_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare(const SupportRuntime& runtime,const std::vector<Relation>& inputs)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a complete owning runtime snapshot with the independent materialized subtree and answer oracle after each modeled update. |
| inputs / outputs | Runtime plus test-owned native input relations in; no value out, with assertion failure on any state mismatch. |
| invariants | Calls \`check_invariants\`, checks root answer presence and node count, then compares every record’s child flags/count/survival, local record/survivor sets, exact P/E support maps, C* membership, and the joined visible answer set against \`recompute\`. |
| ownership | Runtime and inputs are borrowed; \`snapshot\`, oracle, exported rows, relation sets, assignments, and joined answers are temporary test-owned copies. |
| failure | Any failed equality or invariant throws a diagnostic \`runtime_error\`; runtime snapshot, oracle, or allocation errors propagate. This helper does not catch or roll back failures. |
| cost | Each call scans a full runtime snapshot and builds the recomputed subtree assignment joins plus the independent reference-evaluator answer. Snapshot tuple output may use the runtime query account; ordinary oracle maps/sets and diagnostics use test-process allocators. SupportMetrics are logical counters, not byte totals; no CPU, all-heap, or RSS measurement is made. This full-state check may cost more than one incremental update. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp) |

## B0015

[Lines 165–170](../../../../../tests/unit/support_model_test.cpp#L165); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReferenceValueState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one membership and its role-specific metadata while independently replaying public journal records. |
| inputs / outputs | Default construction yields absent membership with empty metadata; fields can hold child count/flags or projection support for a present value. |
| invariants | Records use \`satisfied\` and child flags; survivors carry no counter metadata; P/E entries carry a positive projection count. These shape rules are asserted by \`audit_journal\`. |
| ownership | The struct owns its \`child_present\` vector and optional values; it holds no pointer into runtime state. |
| failure | No validation is automatic at construction; malformed combinations are detected only when audited. |
| cost | Copying a state copies the Boolean vector and scalar optionals; cost follows child count for records. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0016

[Lines 171–173](../../../../../tests/unit/support_model_test.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Left,class Right>bool same_state(const Left& a,const Right& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare an independent state representation with a public \`SupportValueState\` record without taking ownership of either. |
| inputs / outputs | Two state-like values exposing \`member\`, \`satisfied\`, \`child_present\`, and \`support\` in; equality Boolean out. |
| invariants | Requires exact equality of membership, optionals, child-flag sequence, and support; \`std::ranges::equal\` makes vector length and flag order significant. |
| ownership | Both arguments are borrowed; the function creates no retained state. |
| failure | Template instantiation requires compatible fields/ranges; comparison or iterator failures propagate normally. |
| cost | Constant field checks plus a linear comparison in the child-flag length; no container allocation. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0017

[Lines 174–174](../../../../../tests/unit/support_model_test.cpp#L174); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AuditValue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair a public stable handle with the independent state captured for that same membership key. |
| inputs / outputs | No constructor arguments; aggregate contains \`SupportHandle\` and \`ReferenceValueState\`. |
| invariants | The handle identifies the runtime/node/role/tuple membership; the copied state describes member/count/flags at the audited point. |
| ownership | Stores the handle value and owns the copied state vector; it does not own or borrow a runtime pointer. |
| failure | No validation is automatic; \`audit_state\` and \`audit_journal\` enforce correspondence. |
| cost | Copy/move cost is constant except for the child-flag vector inside the state. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0018

[Lines 175–175](../../../../../tests/unit/support_model_test.cpp#L175); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using AuditState=std::map<Membership,AuditValue>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the ordered test-side map used to replay journal state by logical membership identity. |
| inputs / outputs | \`Membership\` is \`(NodeId, SupportRole, Row)\`; map value is \`AuditValue\`. |
| invariants | Each logical \`(node, role, row)\` key is unique; map order is only a deterministic audit container order, not the runtime’s physical storage order. |
| ownership | Map nodes own key rows and \`AuditValue\`; this alias does not share storage with \`SupportRuntime\`. |
| failure | Map allocation failures propagate to the enclosing helper; duplicate keys are rejected where inserted. |
| cost | Lookup/insert/erase use ordered-map comparisons and key copies; full maps consume memory proportional to audited memberships and row widths. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0019

[Lines 176–188](../../../../../tests/unit/support_model_test.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AuditState audit_state(const SupportSnapshot& snapshot,const Members& handles)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert an owning support snapshot into an independent before/after audit map with stable handles for every membership. |
| inputs / outputs | Snapshot and previously derived handle map in; complete \`AuditState\` out for records, survivors, P keys, and present E keys. |
| invariants | Uses role-specific state shapes and requires an exact handle entry for each membership; duplicate identities fail. |
| ownership | The result map owns row keys, flags, and copied metadata; snapshot and handle map are borrowed for construction. |
| failure | Missing \`handles.at\` entry, duplicate membership, row export, or allocation failure propagates as an exception. |
| cost | Walks the entire snapshot and copies each membership row/metadata into ordered maps; cost is proportional to snapshot size and row/flag widths. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0020

[Lines 189–242](../../../../../tests/unit/support_model_test.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void audit_journal(const SupportRuntime& runtime,const SupportEpoch& epoch,AuditState before,const AuditState& after)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay the public epoch journal against an independent before map and verify exact final metadata, causal trace, and undo-related counters. |
| inputs / outputs | Runtime, committed \`SupportEpoch\`, owned before-map by value, and after-map by reference in; assertion-only result. |
| invariants | Checks contiguous journal ordinal and valid cause, before membership/handle/state, role-specific before/after metadata shape, and replayed final map equality. It requires \`metadata_changes\` to count every non-survivor journal record and \`saved_child_flags\` to equal flags saved for record member-to-member changes. With tracing enabled it checks event ID/sequence/ordinal uniqueness, polarity, causal precedence, FIFO/LIFO dequeue order, full drain, and exact queue peak; disabled tracing must have no event payloads. |
| ownership | The by-value \`before\` map is the private replay map; \`after\` and runtime are borrowed. Each public JournalRecord holds a retained tuple pin in \`epoch.journal\`; those pins remain while the SupportEpoch/shared journal has any owner, possibly beyond this helper call. Local ordering/causal maps, queue, pointers, and IDs are temporary and used while the epoch is alive. |
| failure | The helper dereferences \`epoch.journal\` without a null guard. Its current caller (\`update\`) checks that a changed effect has a journal before calling it; a direct call with an empty journal violates that precondition rather than producing a checked missing-journal error. Malformed records/events, queue/counter mismatches, and allocation failures propagate; it does not inspect private undo nodes or inject failures. |
| cost | Replays the full before map assembled by \`audit_state\`, compares the separately assembled after map, and scans journal records/events. It builds ordered causal-group maps, an event-order vector, and a deque; the by-value before parameter is replay-mutated (the current call supplies a temporary). Ordinary replay-container allocation and copied flags are test work. It checks public counters, not private undo bytes, allocator totals, CPU, or RSS. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc) |

## B0021

[Lines 243–283](../../../../../tests/unit/support_model_test.cpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportEpoch update(SupportRuntime& runtime,std::vector<Relation>& inputs,NodeId node,SetOperation operation,Row values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one logical native set operation and independently prove the full resulting support state and exact public membership transitions. |
| inputs / outputs | Mutable runtime, mutable per-node oracle relation set, node, insert/erase operation, and owned row in; \`SupportEpoch\` out. |
| invariants | Snapshots before and after; changes the oracle input set by exactly set-insert/erase semantics; checks \`native_changed\`, then \`compare\`. Derives expected transition rows from complete old/current membership maps and requires returned transitions and S/P/E/generalized-candidate metrics to match exact zero crossings. The four \`copied_*\` metrics are whole-state-copy counters only; their zero assertion is not proof of no affected-state copying. A no-op has zero logical \`SupportMetrics.work\`, no transitions, and no journal, but \`apply\` still validates/builds the tuple, probes the native table, and advances sequence; indexed lookup may consume separate IndexWork. A real update must have journal sequence/record count, storage-change count, one native plus child-key event per parent-key crossing, and a replayable journal. |
| ownership | Oracle input sets and runtime storage are separate owners. \`values\` moves into \`NativeSetUpdate\`; returned transition and journal artifacts own their tuple values/pins. The epoch shares its journal, so retained tuple pins live until the last epoch/journal owner is released. Old/current maps and snapshots are temporary audit state; stable handles persist for unchanged memberships and stop resolving after erasure. |
| failure | Runtime input/plan/sequence/work/resource failures propagate. Assertion failures throw after the attempt; the helper does not restore its oracle set itself, so it is not a failure-injection harness. |
| cost | The runtime validates the row, builds a tuple and probes membership even on no-op; zero \`SupportMetrics.work\` means zero logical propagation charge, not zero execution. Indexed lookup has separate finite IndexWork; the reference and indexed backends use different table/index paths. On changes, affected metadata, journal pins, and pending child-key clones add work; zero \`copied_*\` whole-state counters do not exclude affected RecordState/flag/key copies. This test helper adds full before/after snapshots, membership maps, full recomputation/joins, symmetric differences, and public-journal replay. Runtime table storage and tuple payload copies may use the default 256 MiB query account; standard snapshot/oracle containers, fixture parsing, and diagnostics use test-process allocators; SupportMetrics are not bytes and no CPU/all-heap/RSS measurement is made. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp) |

## B0022

[Lines 284–293](../../../../../tests/unit/support_model_test.cpp#L284); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value sample(ScalarType type,std::uint64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate a small deterministic typed scalar used in seeded structural update sequences. |
| inputs / outputs | Scalar type and integer selector in; one \`Value\` of that type out. Values 0/1/other map to int64, strings \`a\`/\`b\`/\`é\`, booleans by evenness, three fixed dates, or decimals \`0\`/\`-1.25\`/\`1.25\`. |
| invariants | Only the five listed scalar types are accepted; output remains a valid value of the selected schema type. |
| ownership | Returns a value owning any string or decimal payload; no shared generator state is retained. |
| failure | An unrecognized enum throws \`runtime_error\`; date/decimal parse and allocation errors propagate. |
| cost | Fixed case dispatch plus scalar construction/parsing; string bytes are bounded by the three fixture literals. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json) |

## B0023

[Lines 294–318](../../../../../tests/unit/support_model_test.cpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void manual(const std::filesystem::path& root)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive the support model over the checked-in hand-authored runtime support fixtures and compare each event with its recorded expected state. |
| inputs / outputs | Repository root in; no value out. Reads the runtime-support manifest, each query/tree, and events, builds one runtime/input relation vector per case, then calls \`update\` for each fixture operation. \`SupportOptions::capture_transitions\` is enabled; default support work limit is 1,000,000 and default query account is 256 MiB. |
| invariants | Exactly three fixture cases contain 34 logical events: native-root projection/child support has 14 (7 inserts, 7 erases; 12 native changes, 2 no-ops); generalized three-child intersection has 10 (5/5; 8 changes, 2 no-ops); Boolean/nullary generalized intersection has 10 (5/5; 8 changes, 2 no-ops). Each event checks sequence, native change, answer presence, node record/survivor cardinalities, and the fixture’s exact P/E support maps and C* visibility. |
| ownership | Manifest/JSON/query/tree values, \`inputs\` sets, plan, and runtime are separately owned per case. Runtime owns its stored tuples; test relations own their own \`Row\` copies. The helper prints only the total event count after completing all cases. |
| failure | Open, parse/lower/runtime, assertion, and allocation failures propagate to \`main\`; no case-level recovery or resource-failure injection is performed. |
| cost | One plan/runtime per case; full support snapshots and recomputation for each of 34 events dominate the small fixture input. Fixture parsing, test sets, and diagnostic/output allocations are outside support work metrics. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [tests/runtime/support/manifest.json](../../../../../tests/runtime/support/manifest.json), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0024

[Lines 319–347](../../../../../tests/unit/support_model_test.cpp#L319); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void randomized(const std::filesystem::path& root)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Differentially drive the valid lowering fixtures through independent FIFO and LIFO support runtimes under deterministic generated updates and cleanup. |
| inputs / outputs | Repository root in; no value out. Loads lowering cases, plans valid structures, makes two empty input-relation vectors/runtimes, and applies the same generated operations to both schedules. |
| invariants | There are 19 manifest cases, 14 valid families, and two valid constant-only cases with no native nodes. The other 12 families use two fixed \`mt19937_64\` seeds and 40 generated operations each: 960 generated logical inputs (597 insert, 363 erase; replayed state gives 484 native changes and 476 no-ops), followed by 104 cleanup erases total. Thus the \`events\` counter is 1,064 logical inputs and the two schedules receive 2,128 \`update\` calls. Each update checks full recomputed state; final cleanup requires both runtimes to have no answer. |
| ownership | FIFO and LIFO runtimes, their \`inputs\`/\`other\` sets, plans, RNGs, and oracle snapshots are separate; each chosen \`Row\` is copied into the independent input set and moved to its runtime update. Capture is on; the support work limit is reset for these runs. |
| failure | Fixture parsing/lowering, generated update, assertion, and allocation failures propagate. This is not a resource-cap/failure-cut test: it resets the logical \`SupportOptions::work_limit\` and injects no allocator failures. The indexed fixture still supplies finite per-operation IndexWork limits. |
| cost | There are 2,184 \`compare\` invocations: 2,128 from the 1,064 logical inputs applied in FIFO and LIFO, plus 56 initial comparisons (14 valid families × 2 seeds × 2 schedules). Each invokes \`recompute\`; constant-only cases take its early branch. Materialized assignment joins and full runtime snapshots can dominate. No runtime time or byte/CPU/RSS measurement is made; the indexed route uses one aggregate grant per composed operation, with five IndexWork dimensions each capped at 1,000,000,000. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [tests/structural/lowering/manifest.json](../../../../../tests/structural/lowering/manifest.json), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [docs/support_invariants.md](../../../../support_invariants.md) |

## B0025

[Lines 348–371](../../../../../tests/unit/support_model_test.cpp#L348); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reverse_lookup_and_deep_queue()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one selective child-to-parent lookup and one long propagation chain against exact runtime visit, journal, transition, and answer assertions. |
| inputs / outputs | No input; constructs a two-node string query and a 128-node unary chain, applies their updates directly, and returns no value. The local \`SupportOptions\` resets the default logical work limit; transition capture remains off and the default query account remains 256 MiB. |
| invariants | For the selective case, inserts 32 distinct parent rows then child key \`7\`; \`native_record_visits==2\` is one child native insert plus one matching parent row returned by the bucket. It also asserts \`copied_rows==0\` (that named whole-state-copy counter only), one parent survivor, and exactly one parent-record journal record. For the chain, inserts one value at 127 nodes, then inserts and erases at the deepest node; each asserts 128 survivor transitions, with 127 child-key events on insertion and answer truth toggling true then false. |
| ownership | Each \`SupportRuntime\` owns its plan/storage; the test-created catalog, query, tree, and tuple values are local. The 32 setup \`apply\` results are discarded as temporaries. The named \`effect\`, \`appeared\`, and \`vanished\` epochs remain alive until helper return; their shared journals retain public tuple pins for that lifetime. The chain setup results are temporaries. |
| failure | Plan construction, runtime update, invariant or assertion errors propagate. \`SupportOptions::work_limit\` is reset, so this does not inject a logical work-limit or allocation failure. On the indexed route, the fixture’s separate finite IndexWork grants remain active. |
| cost | The selective setup performs 32 parent inserts before a child lookup. \`native_record_visits\` counts the child row and returned matching parent row; it excludes index-key lookup, bucket/list traversal, tuple fetch work, and the returned handle-buffer materialization. Reference storage uses ordered buckets; indexed storage uses hash-directory lookup and linked bucket members, with separate IndexWork. The chain has 127 setup inserts plus trigger insert/delete and drains propagation iteratively. These structural counts give no general time, stack, or whole-runtime complexity bound. Kernel route: the reference twin lowers with default \`PhysicalOptions\`; this packet contains no timing or allocator-byte benchmark. |
| Design | [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp) |

## B0026

[Lines 372–402](../../../../../tests/unit/support_model_test.cpp#L372); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_derivations_bridge()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that complete physical source rows with different payloads share one projected logical support key until the last source derivation is erased. |
| inputs / outputs | No input; binds and normalizes one SQL projection, creates one-node support runtime, adapter state, and reference session, then feeds four ordered physical updates with transition capture enabled and the default 1,000,000 logical work limit/256 MiB query account. |
| invariants | Feeds insert \`(7,a)\`, insert \`(7,b)\`, erase \`(7,a)\`, erase \`(7,b)\` through AdapterState and the reference Session. Adapter source semantics emit a logical added delta at derivation count 0→1 and a removed delta at 1→0; the test loops returned added/removed rows into \`SupportRuntime::apply\`. It does not directly assert either epoch’s \`input_changed\` or maintain a call counter. After each physical step it compares the runtime visible-key relation with \`expected.current\` and checks runtime invariants; it asserts the E handle/support stays live at 1 for the first three points and the handle stops resolving/answer becomes false after the last. |
| ownership | The adapter receives complete two-column physical rows; runtime receives a newly projected one-column logical tuple only at derivation-count crossings. Adapter derivation counts and the reference session own independent state; the runtime owns its logical tuple and stable handle, and \`get\` resolves only while the E membership remains live. |
| failure | Bind/normalize variant failures become assertions; parser, adapter, session, runtime, or allocation errors propagate. No physical constraint or resource-failure boundary is injected. |
| cost | Four AdapterState updates copy physical, logical, and derivation-support state, including no-op paths; the reference Session evaluates the full query before and after each physical update and copies its database. For these returned deltas, source control flow calls SupportRuntime twice (first insertion and final erase), but the test has no direct call-count assertion. Runtime snapshots/invariant checks add full-state work. Runtime query-account allocations and ordinary adapter/session/test-container allocations are separate; no CPU, total allocator-byte, all-heap, or RSS measurement is made. Kernel route: default reference physical backend and default \`SupportOptions\` (1,000,000 logical support work; 256 MiB query account); no timing or allocator-byte benchmark. |
| Design | [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/frontend/adapter.hpp](../../../../../include/crown/frontend/adapter.hpp), [src/frontend/adapter.cpp](../../../../../src/frontend/adapter.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp) |

## B0027

[Lines 403–403](../../../../../tests/unit/support_model_test.cpp#L403); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L403-L403:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in support_model_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0028

[Lines 404–408](../../../../../tests/unit/support_model_test.cpp#L404); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the four support-model fixture groups and report an executable failure directly. |
| inputs / outputs | Require one repository-root argument; call manual, randomized, reverse_lookup_and_deep_queue and physical_derivations_bridge in order. Helper progress goes to stdout; a caught std::exception prints to stderr and returns 1. Falling off main returns 0. |
| invariants | The first exception skips later groups. Reference and indexed programs share this driver; their lowering wrappers choose the backend. Main does not directly count runtime calls or establish a paper/performance bound. |
| ownership | argv text is borrowed during the process. Path temporaries and each helper own their own fixture/container/runtime state; this entrypoint retains no query graph between helper calls. |
| failure | Wrong argc fails through check and the outer std::exception handler. Other standard setup/update/assertion failures reach the same handler; non-std exceptions are not caught here. |
| cost | Four helper invocations include manifest reads, full oracle joins/snapshots, paired FIFO/LIFO updates, selective/deep propagation and the four-step physical bridge. Their source-derived counts are detailed in the helper cards; this receiving review executes no native test. |
| Design | [tests/unit/support_model_test.cpp](../../../../../tests/unit/support_model_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/support_invariants.md](../../../../support_invariants.md) |
