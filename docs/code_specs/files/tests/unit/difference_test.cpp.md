# `tests/unit/difference_test.cpp` — block usage map

[Source](../../../../../tests/unit/difference_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `314b41110b06c3ab8015c8380a79cd0845f1999f2428c8984e151c1047c503aa`. 305 lines partitioned into 30 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/unit/difference_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 22–25](../../../../../tests/unit/difference_test.cpp#L22) | Callable definition: void check(bool condition,const char* message) | calls std::runtime_error; guard void check(bool condition,const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 26–33](../../../../../tests/unit/difference_test.cpp#L26) | Callable definition: template&lt;class F&gt;void refusal(F action,std::string_view code={}) | calls action, check, empty, code; guard catch(const Error& e){failed=true;check(code.empty()\|\|code==e.code(),"unexpected difference error c… · [reviewed contract](#b0003) |
| [B0004 · 34–36](../../../../../tests/unit/difference_test.cpp#L34) | Callable definition: Row ints(std::initializer_list&lt;std::int64_t&gt; values) | calls emplace_back; returns row; growth emplace_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 37–38](../../../../../tests/unit/difference_test.cpp#L37) | Explanatory comments or spacing. | source comment (unverified): // Test-only Cartesian definition: select every physical row combination first, · [reviewed contract](#b0005) |
| [B0006 · 39–58](../../../../../tests/unit/difference_test.cpp#L39) | Callable definition: Bag operand(const Query& query,const Database& database) | calls selected, size, void, combinations; returns {}; result; growth push_back; 4 loop sites; source comment (unverified): // Test-only Cartesian definition: select every physical row combination first, · [reviewed contract](#b0006) |
| [B0007 · 59–59](../../../../../tests/unit/difference_test.cpp#L59) | Type/record definition: struct Fixture |  · [reviewed contract](#b0007) |
| [B0008 · 60–69](../../../../../tests/unit/difference_test.cpp#L60) | Callable definition: Fixture unary(bool self=false,bool boolean=false) | calls ; returns f · [reviewed contract](#b0008) |
| [B0009 · 70–82](../../../../../tests/unit/difference_test.cpp#L70) | Callable definition: Fixture joins(bool cyclic,bool aliases,std::vector&lt;std::size_t&gt; head={0,2}) | calls push_back, std::to_string, size; returns f; growth push_back; 2 loop sites · [reviewed contract](#b0009) |
| [B0010 · 83–91](../../../../../tests/unit/difference_test.cpp#L83) | Callable definition: Bag expected(const Fixture& f,const Database& database,pd::Mode mode) | calls operand, find, end, std::uint64_t; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 92–97](../../../../../tests/unit/difference_test.cpp#L92) | Callable definition: Changes changes(const Bag& before,const Bag& after) | calls find, end, contains; returns result; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 98–103](../../../../../tests/unit/difference_test.cpp#L98) | Callable definition: template&lt;class Range&gt;Bag rows(const Range& input) | calls check, is_accounted, emplace, storage::export_row; guard Bag result;for(const auto& value:input){check(value.multiplicity.value&gt;0,"zero residual count escap…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 104–109](../../../../../tests/unit/difference_test.cpp#L104) | Callable definition: template&lt;class Range&gt;Changes replacements(const Range& input) | calls check, is_accounted, emplace, storage::export_row; guard Changes result;for(const auto& value:input){check(value.before!=value.after,"unchanged endpoint emi…; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 110–111](../../../../../tests/unit/difference_test.cpp#L110) | declares types or opens a type body. |  · [reviewed contract](#b0014) |
| [B0015 · 112–114](../../../../../tests/unit/difference_test.cpp#L112) | Callable definition: Trial(Fixture f,bool indexed,pd::Mode semantics,dr::Options options={}) :original(std::move(f)),mode(semantics),selected(pd::admi… | calls original, std::move, mode, selected · [reviewed contract](#b0015) |
| [B0016 · 115–115](../../../../../tests/unit/difference_test.cpp#L115) | Callable definition: Bag answer() const | calls expected, database; returns expected(original,sources.database(),mode) · [reviewed contract](#b0016) |
| [B0017 · 116–128](../../../../../tests/unit/difference_test.cpp#L116) | Callable definition: void verify() | calls check, ready, sequence, source_snapshot; guard check(owner.ready(),"difference owner remained busy");check(owner.sequence()==sources.sequence(),"d…; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 129–134](../../../../../tests/unit/difference_test.cpp#L129) | Callable definition: dr::Epoch apply(std::size_t table,SetOperation operation,Row values) | calls answer, sequence, std::move, check; guard check(actual.input.input.physical_changed==model.input_changed,"difference source membership flag d…; returns actual · [reviewed contract](#b0018) |
| [B0019 · 135–135](../../../../../tests/unit/difference_test.cpp#L135) | Closes surrounding scope/type. |  · [reviewed contract](#b0019) |
| [B0020 · 136–155](../../../../../tests/unit/difference_test.cpp#L136) | Callable definition: void admission() | calls unary, pd::admit, check, profile; guard check(p.profile().mode==pd::Mode::set_except&&p.source_only().query().atoms.empty(),"difference def… · [reviewed contract](#b0020) |
| [B0021 · 156–178](../../../../../tests/unit/difference_test.cpp#L156) | Callable definition: void transitions(bool indexed,pd::Mode mode) | calls t, unary, apply, ints; guard check(!first.changes.empty(),"right insertion did not retract membership/count");; growth insert, push_back · [reviewed contract](#b0021) |
| [B0022 · 179–186](../../../../../tests/unit/difference_test.cpp#L179) | Callable definition: void generated(bool indexed,pd::Mode mode) | calls random, t, joins, apply; growth insert; 4 loop sites · [reviewed contract](#b0022) |
| [B0023 · 187–200](../../../../../tests/unit/difference_test.cpp#L187) | Callable definition: void constants(bool indexed,pd::Mode mode) | calls boolean, unary, apply, ints; guard check(boolean.answer()==(mode==pd::Mode::set_except?Bag{}:Bag{{Row{},1}}),"Boolean EXCEPT ALL stopp…; growth insert, push_back · [reviewed contract](#b0023) |
| [B0024 · 201–224](../../../../../tests/unit/difference_test.cpp#L201) | Callable definition: void typed(bool indexed,pd::Mode mode) | calls t, apply, run, std::string; growth insert; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 225–253](../../../../../tests/unit/difference_test.cpp#L225) | Callable definition: void constraints_and_limits(bool indexed,pd::Mode mode) | calls unary, push_back, constrained, refusal; guard } else {counts.apply(0,SetOperation::insert,ints({1,3}));check(counts.answer()==Bag{{ints({1}),1}},…; growth insert, push_back; source comment (unverified): // The per-operand cap is explicit even if the final residual would be empty. · [reviewed contract](#b0025) |
| [B0026 · 254–265](../../../../../tests/unit/difference_test.cpp#L254) | Callable definition: void cumulative_work(bool indexed,pd::Mode mode) | calls push_back, ints, control, unary; guard check(work&gt;1,"difference successful control has no cumulative work");; growth insert, push_back; 3 loop sites · [reviewed contract](#b0026) |
| [B0027 · 266–283](../../../../../tests/unit/difference_test.cpp#L266) | Callable definition: void allocation_cuts(bool indexed,pd::Mode mode,bool deletion) | calls unary, apply, ints, sequence; guard check(failed&&triggered,"difference persistent allocation refusal was not authenticated");t-&gt;verify…; returns t; PhysicalSetUpdate{t.owner.sequence()+1,TableId{1},deletion?SetOperation::erase:SetOperation::ins…; growth insert, make_unique; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 284–297](../../../../../tests/unit/difference_test.cpp#L284) | Callable definition: void lifetime(bool indexed,pd::Mode mode) | calls t, unary, apply, ints; guard check(rows(snapshot.rows)==Bag{{ints({7}),mode==pd::Mode::set_except?1U:2U}},"retained difference s…; returns t.owner.snapshot(); t.apply(1,SetOperation::insert,ints({7,9})); growth insert · [reviewed contract](#b0028) |
| [B0029 · 298–298](../../../../../tests/unit/difference_test.cpp#L298) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0029) |
| [B0030 · 299–305](../../../../../tests/unit/difference_test.cpp#L299) | Callable definition: int main() | calls admission, transitions, generated, constants; returns 0; 1; 2 loop sites · [reviewed contract](#b0030) |

## B0001

[Lines 1–21](../../../../../tests/unit/difference_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:d185672466236176778b4115a677fab21acbf2cf664f6f152bcdf3d92bf431cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the actual difference owner and independent source/reference/fault tools. |
| inputs / outputs | Declare local mode/runtime aliases, ordered reference count/replacement maps and a check counter. |
| invariants | The expected bag implementation is test-owned; production difference execution is linked separately. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Compile dependencies and fixed test declarations. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0002

[Lines 22–25](../../../../../tests/unit/difference_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L25:sha256:2ff4e55fa17e5503ffe33b650881e8f1712a3d196ef4f0b5fe829bcfc0effdf1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count an assertion independently of NDEBUG. |
| inputs / outputs | A Boolean condition either increments checks or throws a test failure. |
| invariants | False assertions cannot disappear in an optimized build. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | One branch/counter update, exception only on failure. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0003

[Lines 26–33](../../../../../tests/unit/difference_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L33:sha256:193d1ef9d622e78027d6a10aed0479f09930a7a24ba3a4e88f2e23e0e1d7302a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a selected operation to refuse with its declared error category. |
| inputs / outputs | Run a callable once and inspect native Error, memory or index failure. |
| invariants | A requested diagnostic cannot silently accept a different failure domain; this is a test helper, not production retry logic. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | One invocation and finite assertion/diagnostic work. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0004

[Lines 34–36](../../../../../tests/unit/difference_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L36:sha256:0c91e69931aa2fefcbcc45860c4bc5f6da1dc057a73d724b2dd8c986218578f9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct exact integer fixture rows. |
| inputs / outputs | Initializer-list int64 values become ordinary owning Row cells. |
| invariants | No floating conversion or native evaluator supplies reference values. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Linear in row width with ordinary allocations. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0005

[Lines 37–38](../../../../../tests/unit/difference_test.cpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L38:sha256:e5271ff90fa9095369426960c9703884e487a2ed761e3da307fd97c4c9908033
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the Cartesian oracle independence boundary. |
| inputs / outputs | The adjacent note states that row choices precede term unification. |
| invariants | The note does not execute or certify the production binding-trail algorithm. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | No executable work. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0006

[Lines 39–58](../../../../../tests/unit/difference_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L58:sha256:6bc5659cb4f6f570649c57ba29bccc955e845650dd7df032916f2663b0feb146
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define original bag multiplicities without native traversal helpers. |
| inputs / outputs | Recursively enumerate all physical row combinations, then unify variables/constants and count ordered projected keys. |
| invariants | Ignored-column physical witnesses and aliases remain distinct choices; contradiction yields none and a true empty body yields one empty tuple. No DISTINCT precedes counting. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Full Cartesian products, per-combination copied assignments, projection and ordered reference insertion; intentionally expensive test work. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0007

[Lines 59–59](../../../../../tests/unit/difference_test.cpp#L59); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L59:sha256:1846e408874079a769bef9c7d9b1b40cef9ea2cc70515575e3ed57ac5e92cf96
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep original pair metadata as caller-owned fixture data. |
| inputs / outputs | Catalog and two positive Query DTOs form Fixture. |
| invariants | These mutable test DTOs are not admitted executable or recovery authority. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Storage follows fixture metadata. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0008

[Lines 60–69](../../../../../tests/unit/difference_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L69:sha256:d179190195daab21df8d63cc57ebf6e86a6645118fb9591d6ff3b0e6c889dbbc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct projected unary operands with hidden physical row identity. |
| inputs / outputs | Separate or identical source tables, optional empty heads and an unused source produce a pair. |
| invariants | Different full rows sharing v produce bag witnesses; left/right aliases may differ while ordered output types agree. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Small fixed metadata construction. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0009

[Lines 70–82](../../../../../tests/unit/difference_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L82:sha256:8b153c2a55e127c71c761c6d815f6d0a8176907d839bcc143e221cd11cb43771
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct path/cyclic pairs with optional physical aliases and repeated heads. |
| inputs / outputs | R/S/T atoms and a positive RHS filter create both arbitrary structural and alias cases. |
| invariants | The right operand is a positive CQ, not a negative recursive dependency; original ordered heads remain literal. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Finite metadata copies proportional to fixture/head width. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0010

[Lines 83–91](../../../../../tests/unit/difference_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L91:sha256:a5d5352cd77c96978c26e5e6b6acaeab1bb6cba772fa1cbd8a955c064ae2b03a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define set EXCEPT and bag EXCEPT ALL from independent operand Counters. |
| inputs / outputs | Original pair plus physical database and mode produce positive residual keys/counts. |
| invariants | Set mode uses left presence/right absence; bag mode branches before subtraction to clamp at zero. Physical sources remain sets. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Two complete Cartesian definitions and ordered residual lookup/insertion. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0011

[Lines 92–97](../../../../../tests/unit/difference_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L97:sha256:847a324f493317afcae3813a6578b86c40122c8f9f0a6abc7b135b6c7c351882
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact reference endpoint count replacements. |
| inputs / outputs | Before/after residual maps yield one old/new pair per changed key. |
| invariants | Positive-to-positive count changes are retained; unchanged counts and duplicate keys are absent. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Two reference-map traversals and logarithmic lookup/output insertion. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0012

[Lines 98–103](../../../../../tests/unit/difference_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L98-L103:sha256:7b6a805e5fe0c42017c6dbc42c86c885e44763e0eab306187af254960b82cb34
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export compressed native residuals for independent comparison. |
| inputs / outputs | Native Entry ranges become ordinary row/count maps. |
| invariants | Every count is positive, every tuple is accounted and every key appears once; exports retain test ownership. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Full scalar export and ordered test-map insertion. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0013

[Lines 104–109](../../../../../tests/unit/difference_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L109:sha256:9d5454a96a6d20fc44064be1998d432ee00644cdb29b52475e3eec6e0a8d2fa1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export actual nonnegative endpoint replacements. |
| inputs / outputs | Native Change ranges become ordinary key to before/after maps. |
| invariants | Every emitted replacement changes a count, retains native tuple ownership and appears once. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Full scalar export and ordered test-map insertion. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0014

[Lines 110–111](../../../../../tests/unit/difference_test.cpp#L110); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L111:sha256:7b689a5ca904aa3db3e97a5b4aecdc06f19d1563046a049aa24c9e82abc83f63
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own pair DTOs, selected plan, native runtime and independent source session. |
| inputs / outputs | Trial fields retain all comparison inputs and the chosen mode. |
| invariants | The original reference database is separate from native state and other Trials. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Both independent test/native states coexist. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0015

[Lines 112–114](../../../../../tests/unit/difference_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L114:sha256:30fc6c186665406c766bebda6ba1d92bd84c70f47f8865f6af867592039d44d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a genuinely admitted pair and empty independent source model. |
| inputs / outputs | Fixture/backend/mode/options initialize the selected plan, native owner and original-catalog source-only reference session, then verify. |
| invariants | The reference session validates complete original sources and constraints but does not compute the production difference. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Cold admission/import plus initial reference and native state verification. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0016

[Lines 115–115](../../../../../tests/unit/difference_test.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L115:sha256:e157067cf4630f06ed8be368e81ab677ea37dfc383ff06590ea9c5b25fa02988
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the reference residual at the committed original source state. |
| inputs / outputs | Trial original pair and reference Database produce a Bag. |
| invariants | No maintained native answers supply expected values. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Full test-only Cartesian operand evaluation. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0017

[Lines 116–128](../../../../../tests/unit/difference_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L128:sha256:5f153d7eea8815ff8e54dcf7e2772fd9a5ebbbe1afa675782d52ba23ae92c83f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare committed native sources, counts, bindings and diagnostics. |
| inputs / outputs | Read readiness/sequence, snapshot, full source export and EXPLAIN against the independent model. |
| invariants | Both original operands and source-only coordination remain visible; actual source/result counts, semantic mode and existence agree. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Full native export plus repeated slow reference recomputation; no timing claim. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0018

[Lines 129–134](../../../../../tests/unit/difference_test.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L134:sha256:e7e79f2841d73b4a42ac3de640e2cbd0aa9cc1b7ebf3044babcb88c15613c369
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one physical update and every exact endpoint replacement. |
| inputs / outputs | Apply one contiguous input to independent sources and the native owner, then compare before/after counts and full state. |
| invariants | Physical membership/no-op identity and numeric endpoint changes must agree at every prefix. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | One native update plus independent source validation and repeated complete oracle work. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0019

[Lines 135–135](../../../../../tests/unit/difference_test.cpp#L135); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L135:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the Trial helper declaration. |
| inputs / outputs | The lexical terminator ends its fields and methods. |
| invariants | No extra state change or proof occurs. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | No executable work. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0020

[Lines 136–155](../../../../../tests/unit/difference_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L155:sha256:bb1a438c6eb14b575d277609978579d6b9b48349a11fc37b7b63a100e681ee47
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise explicit admission, immutable copies and conservative estimates. |
| inputs / outputs | Malformed modes, limits, heads/types/nullability and advisory counts drive positive/negative cases. |
| invariants | Head compatibility is positional; aliases remain separate. Source rows count once and RHS upper bounds are never subtracted. Boolean bag key and multiplicity bounds remain distinct. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Finite cold admission and estimate calls only. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0021

[Lines 156–178](../../../../../tests/unit/difference_test.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L156-L178:sha256:a264f47dfd21d93cf332557fef1d4de3e1e4335a13689cfc0c6006166a121dc9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate membership transitions from count transitions through updates. |
| inputs / outputs | Projected duplicates, RHS insertion/removal, no-ops, unused sources, independent aliases and identical operands run in either mode/backend. |
| invariants | EXCEPT blocks on any right witness; EXCEPT ALL subtracts complete row-choice counts. Boolean bag aliases multiply and identical operands never publish a source-prefix artifact. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Finite state/update/oracle traces with full prefix checks. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0022

[Lines 179–186](../../../../../tests/unit/difference_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L179-L186:sha256:fa2e22c0fd93ef2dbf6921fb8bc21c3d620b1cd8d54a2cd780f20f5b5acafda5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare generated arbitrary positive pair traces. |
| inputs / outputs | Seeded path/cyclic, aliased and ordered/repeated/Boolean head fixtures receive 80 events each. |
| invariants | Every prefix and endpoint is checked independently, not merely the final snapshot. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Sum of finite native and Cartesian-oracle traces; no scalability bound. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0023

[Lines 187–200](../../../../../tests/unit/difference_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L187-L200:sha256:af8028af19bed5c3f9fbbb894b18834a2ade9318e0ee49c4c0b2b9bfdf87a79a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check Boolean, empty/nullary, contradictory and term-filtered operands. |
| inputs / outputs | Empty heads, true/false bodies, nullary table changes, literals and repeated variables drive exact transitions. |
| invariants | Bag Boolean counts every witness; set Boolean is existence. Constants/repeated terms are applied before repeated-head projection. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Small complete model/native traces. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0024

[Lines 201–224](../../../../../tests/unit/difference_test.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L201-L224:sha256:f5d15c4603804024d4a53c698a8e852742638e5d7d3fb39ec20f56f8687bf1a2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check typed boundaries and differing Decimal source specifications. |
| inputs / outputs | Int64 extrema, NUL/UTF8 strings, Boolean, dates and exact decimals produce projected counts on both sides. |
| invariants | The RHS can hold a Decimal outside the left column specification without coercion; equal canonical decimals still block/subtract correctly. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Finite typed trace products with exact scalar export/reference comparison. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0025

[Lines 225–253](../../../../../tests/unit/difference_test.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L225-L253:sha256:699169935fdcf35191a3514056c1ab15982aa4382b3a48eadb01ed34dcb827ce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify original constraints and finite result/image/work/count refusals. |
| inputs / outputs | FK/UNIQUE violations, per-operand/snapshot caps, unused image rows, zero budgets and small W01 limits are attempted. |
| invariants | Refusal preserves source/result/sequence and readiness. Set presence saturates repeated witnesses; bag per-key overflow refuses before publication. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Small deliberate resource/constraint failures plus unchanged-state verification. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0026

[Lines 254–265](../../../../../tests/unit/difference_test.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L254-L265:sha256:1253662b0d19167dfcdd1fce35f48647a4629cbbf915955139f9c386ce4ef12e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exhaust the single cumulative operation balance near a successful control. |
| inputs / outputs | Measure actual final-update work, reconstruct with one fewer unit and attempt that same endpoint. |
| invariants | The whole image/both operands/residual/delta operation shares one grant; denial preserves state, then an unused-source event at the same sequence can commit. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | One control trace and one bounded denial/retry fixture. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0027

[Lines 266–283](../../../../../tests/unit/difference_test.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L266-L283:sha256:a6dfe3b1d132e23dfda77b32227bcea63f699c3208979ca420c95c780752d100
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Authenticate every allocation-prefix failure on insertion and retraction. |
| inputs / outputs | Count a successful actual update, deny each observed allocation persistently, then verify and retry on the same owner/sequence. |
| invariants | Both modes/backends/directions must trigger the seam. The old reference advances only after successful native retry, and all exact endpoint replacements are compared. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | One control plus reconstructed fixture/refusal/retry per observed allocation; finite paths, not exhaustive all-query fault proof. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0028

[Lines 284–297](../../../../../tests/unit/difference_test.cpp#L284); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L284-L297:sha256:919fe72ff0e9ad41bfb3f2d1cc0dbd1df487b405c633de18d9216cbd919ac23c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain native outputs/bindings and independent query ownership. |
| inputs / outputs | Snapshots and epochs outlive their owners; uint64 endpoint extremes exercise delta sign/magnitude; separate Trials remain isolated. |
| invariants | Native account-backed payloads and original pair metadata survive teardown. Signed magnitudes do not narrow to int64 or become aggregate payloads. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Finite retained handles, direct integer boundary checks and independent-owner updates. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0029

[Lines 298–298](../../../../../tests/unit/difference_test.cpp#L298); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L298-L298:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private test namespace. |
| inputs / outputs | Lexical scope ends before main. |
| invariants | No mutation or runtime guarantee is added. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | No executable work. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |

## B0030

[Lines 299–305](../../../../../tests/unit/difference_test.cpp#L299); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L299-L305:sha256:ec65fd0f46e2b4a515fbd080d8874f60c3dfd88e75c5a6da210598537cc172a0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run admission and both-mode/backend correctness and failure suites. |
| inputs / outputs | Actual process executes all fixtures and reports the counted successful assertions. |
| invariants | Escaping standard exceptions return failure; a source card predicts no pass or numerical check count. |
| ownership | Ordinary fixtures/reference Counters belong to the test; native plans/owners/results retain independently funded original accounts. Borrowed values stay within their live owners. |
| failure | Assertion/reference/native failures propagate to the stated helper or process boundary; allocation injection and test catches install no production retry framework. |
| cost | Sum of finite suites and process-boundary failure formatting. |
| Design | [tests/unit/difference_test.cpp](../../../../../tests/unit/difference_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../../difference.md), [docs/annotations.md](../../../../annotations.md) |
