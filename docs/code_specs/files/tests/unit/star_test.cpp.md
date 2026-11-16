# `tests/unit/star_test.cpp` — block usage map

[Source](../../../../../tests/unit/star_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `47297e5b0e1557bf308ad86f76b84a9666863bb42496137e70b8aa3080f7b20a`. 502 lines partitioned into 37 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–24](../../../../../tests/unit/star_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 25–28](../../../../../tests/unit/star_test.cpp#L25) | Callable definition: void check(bool value, const char* message) | calls std::runtime_error; guard void check(bool value, const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 29–33](../../../../../tests/unit/star_test.cpp#L29) | Callable definition: Row row(std::initializer_list&lt;std::int64_t&gt; values) | calls emplace_back; returns result; growth emplace_back; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 34–34](../../../../../tests/unit/star_test.cpp#L34) | Type/record definition: struct Fixture |  · [reviewed contract](#b0004) |
| [B0005 · 35–62](../../../../../tests/unit/star_test.cpp#L35) | Callable definition: Fixture fixture(std::size_t d, std::vector&lt;std::size_t&gt; head, std::vector&lt;std::size_t&gt; satellites = {}) | calls empty, push_back, std::to_string, emplace_back; returns out; growth emplace_back, insert, push_back; 4 loop sites · [reviewed contract](#b0005) |
| [B0006 · 63–69](../../../../../tests/unit/star_test.cpp#L63) | Callable definition: PhysicalPlan lower(const Fixture& f, bool indexed) | calls s04_runtime::options, std::max, size, planner::lower_tree; returns planner::lower_tree(f.catalog, f.query, f.tree,options) · [reviewed contract](#b0006) |
| [B0007 · 70–77](../../../../../tests/unit/star_test.cpp#L70) | Callable definition: template&lt;class Action&gt; void refusal(Action action, std::string_view code = {}) | calls action, check, empty, code; guard catch (const Error& e) { refused = true; check(code.empty() \|\| e.code() == code, "unexpected refusa… · [reviewed contract](#b0007) |
| [B0008 · 78–85](../../../../../tests/unit/star_test.cpp#L78) | Callable definition: Relation results(const st::Runtime& owner, st::CursorMetrics* metrics = nullptr) | calls next, check, insert, storage::export_row; guard check(out.insert(storage::export_row(tuple-&gt;values())).second, "duplicate projected result escaped"…; returns out; growth insert; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 86–88](../../../../../tests/unit/star_test.cpp#L86) | Explanatory comments or spacing. | source comment (unverified): // Deliberately slow original-source definition, independent of maintained H, · [reviewed contract](#b0009) |
| [B0010 · 89–104](../../../../../tests/unit/star_test.cpp#L89) | Callable definition: std::uint64_t exact_h(const std::map&lt;Value,std::uint64_t&gt;& degrees, std::size_t d) | calls size; returns h; 3 loop sites; source comment (unverified): // Deliberately slow original-source definition, independent of maintained H, · [reviewed contract](#b0010) |
| [B0011 · 105–107](../../../../../tests/unit/star_test.cpp#L105) | Callable definition: st::Options bounded_options() | calls ; returns options · [reviewed contract](#b0011) |
| [B0012 · 108–112](../../../../../tests/unit/star_test.cpp#L108) | declares types or opens a type body. |  · [reviewed contract](#b0012) |
| [B0013 · 113–116](../../../../../tests/unit/star_test.cpp#L113) | Callable definition: explicit Trial(Fixture f, bool indexed, st::Options options = bounded_options()) : original(std::move(f)), plan(planner::star::ad… | calls bounded_options, original, std::move, plan · [reviewed contract](#b0013) |
| [B0014 · 117–144](../../../../../tests/unit/star_test.cpp#L117) | Callable definition: void verify() | calls check, ready, sequence, source_snapshot; guard check(owner.ready(), "star owner retained a private lease");; 3 loop sites · [reviewed contract](#b0014) |
| [B0015 · 145–153](../../../../../tests/unit/star_test.cpp#L145) | Callable definition: st::Epoch apply(std::size_t table, SetOperation operation, Row values) | calls sequence, std::move, check, verify; guard check(actual.sequence == expected.sequence && actual.physical_changed == expected.input_changed, "p…; returns actual · [reviewed contract](#b0015) |
| [B0016 · 154–155](../../../../../tests/unit/star_test.cpp#L154) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 156–182](../../../../../tests/unit/star_test.cpp#L156) | Callable definition: void admission(bool indexed) | calls fixture, lower, physical_sha256, planner::star::admit; guard check(admitted.dimension() == 3 && admitted.distinct_head() == 2 && admitted.head_coordinates().siz…; growth emplace_back, insert, push_back · [reviewed contract](#b0017) |
| [B0018 · 183–183](../../../../../tests/unit/star_test.cpp#L183) | Explanatory comments or spacing. |  |
| [B0019 · 184–208](../../../../../tests/unit/star_test.cpp#L184) | Callable definition: void every_relation(bool indexed) | calls t, fixture, row, apply; guard check(!duplicate.physical_changed && !absent.physical_changed &&; growth insert; 5 loop sites · [reviewed contract](#b0019) |
| [B0020 · 209–209](../../../../../tests/unit/star_test.cpp#L209) | Explanatory comments or spacing. |  |
| [B0021 · 210–232](../../../../../tests/unit/star_test.cpp#L210) | Callable definition: void cubes(bool indexed) | calls t, fixture, apply, row; guard check(dimension.h == static_cast&lt;std::uint64_t&gt;(side), "complete cube generalized H is wrong");; growth insert; 12 loop sites · [reviewed contract](#b0021) |
| [B0022 · 233–233](../../../../../tests/unit/star_test.cpp#L233) | Explanatory comments or spacing. |  |
| [B0023 · 234–275](../../../../../tests/unit/star_test.cpp#L234) | Callable definition: void heavy_light(bool indexed) | calls t, fixture, apply, row; guard for (const auto& dimension : t.owner.state().dimensions) check(dimension.h == 1,"one huge degree wa…; growth insert; 4 loop sites · [reviewed contract](#b0023) |
| [B0024 · 276–276](../../../../../tests/unit/star_test.cpp#L276) | Explanatory comments or spacing. |  |
| [B0025 · 277–298](../../../../../tests/unit/star_test.cpp#L277) | Callable definition: void projected_groups(bool indexed) | calls t, fixture, apply, row; guard check(answer.size() == 1 && metrics.candidates == 2 && metrics.duplicates == 1 && metrics.outputs =…; growth insert; 2 loop sites · [reviewed contract](#b0025) |
| [B0026 · 299–299](../../../../../tests/unit/star_test.cpp#L299) | Explanatory comments or spacing. |  |
| [B0027 · 300–358](../../../../../tests/unit/star_test.cpp#L300) | Callable definition: void lifecycle_and_limits(bool indexed) | calls t, fixture, apply, row; guard check(output && storage::export_row(output-&gt;values()) == row({8,7,8}),"ordered/repeated head change…; growth allocate, emplace, insert; 1 loop sites; source comment (unverified): // Exhaust the actual original account, then retry the same sequence after · [reviewed contract](#b0027) |
| [B0028 · 359–363](../../../../../tests/unit/star_test.cpp#L359) | Explanatory comments or spacing. | source comment (unverified): // Actual source/view transaction cuts, including an insertion whose temporary · [reviewed contract](#b0028) |
| [B0029 · 364–418](../../../../../tests/unit/star_test.cpp#L364) | Callable definition: void allocation_rollback(bool indexed) | calls fixture, planner::star::admit, lower, push_back; guard check(allocations &gt; 10,"allocation discriminator did not enter staged view work");; growth insert, push_back; 7 loop sites; source comment (unverified): // Actual source/view transaction cuts, including an insertion whose temporary · [reviewed contract](#b0029) |
| [B0030 · 419–419](../../../../../tests/unit/star_test.cpp#L419) | Explanatory comments or spacing. |  |
| [B0031 · 420–445](../../../../../tests/unit/star_test.cpp#L420) | Callable definition: void source_constraints_and_independence(bool indexed) | calls fixture, push_back, t, refusal; guard check(first.account().statistics().owner != second.account().statistics().owner,"independent owners…; growth insert, push_back · [reviewed contract](#b0031) |
| [B0032 · 446–446](../../../../../tests/unit/star_test.cpp#L446) | Explanatory comments or spacing. |  |
| [B0033 · 447–460](../../../../../tests/unit/star_test.cpp#L447) | Callable definition: void wide_and_unfiltered(bool indexed) | calls free_coordinate, fixture, apply, row; guard check(free_coordinate.owner.key(2,storage::ScalarView{std::int64_t{3}})-&gt;present,"satellite-free co…; growth emplace_back, insert; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 461–461](../../../../../tests/unit/star_test.cpp#L461) | Explanatory comments or spacing. |  |
| [B0035 · 462–488](../../../../../tests/unit/star_test.cpp#L462) | Callable definition: void hindex_model() | calls check, HIndex::power, resource::MemoryAccount::create, index; guard check(HIndex::power(0,0) == 1 && HIndex::power(0,70) == 0 && HIndex::power(1,7000) == 1,; growth emplace; 3 loop sites; source comment (unverified): // Inactive/moved-from publication is inert. · [reviewed contract](#b0035) |
| [B0036 · 489–490](../../../../../tests/unit/star_test.cpp#L489) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0036) |
| [B0037 · 491–502](../../../../../tests/unit/star_test.cpp#L491) | Callable definition: int main() | calls hindex_model, admission, every_relation, cubes; returns 0; 1; 1 loop sites · [reviewed contract](#b0037) |

## B0001

[Lines 1–24](../../../../../tests/unit/star_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L24:sha256:bb324f6feb7129bdf2092d2d9d9820c577cfed30d0cbb9741759a284553c4d53
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the real star APIs, original A04 evaluator and private allocation/H-index test support. |
| inputs / outputs | C++ headers, local aliases and successful-check counter; no query executes in this declaration region. |
| invariants | The unit calls the actual runtime and HIndex. Original reference::Session remains the full-state semantic oracle; global allocation injection is test-only support. |
| ownership | Declarations acquire no runtime/account ownership. Local test functions construct their own finite native owners and ordinary oracle DTOs. |
| failure | Incompatible includes or types fail compilation; no exception handler is installed here. |
| cost | Compile-time dependencies and fixed test declarations only. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/runtime/star_hindex.hpp](../../../../../src/runtime/star_hindex.hpp) |

## B0002

[Lines 25–28](../../../../../tests/unit/star_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L28:sha256:f2c6afd9fbcf88946f31ec75e8646a4e30cbbc63180750a2131b2e4fb2ff0bfb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one explicit assertion or count its successful completion. |
| inputs / outputs | Boolean condition and static message in; normal return with checks incremented or runtime_error out. |
| invariants | A false condition cannot be disabled by NDEBUG and does not change production state. |
| ownership | Borrows message for the call and owns no query/result. |
| failure | False condition throws std::runtime_error to the unit process boundary. |
| cost | One branch/counter increment, plus exception construction only on failure. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp) |

## B0003

[Lines 29–33](../../../../../tests/unit/star_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L33:sha256:b3868c78dc79869c27c62257aa606d13276b213463d04124093c6be0bb3d040f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an exact owning int64 physical row for fixtures/events. |
| inputs / outputs | Initializer-list of int64 values in; ordinary Row with corresponding Value alternatives out. |
| invariants | No floating conversion or production coordinate/projection helper is used. |
| ownership | Returned ordinary vector owns scalar Values; no native query allowance is allocated here. |
| failure | Ordinary vector allocation failure propagates. |
| cost | O(row width) copies and vector growth. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0004

[Lines 34–34](../../../../../tests/unit/star_test.cpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L34:sha256:8be265d7845074be89e5d7b4d7b9fe24f4739be76340081d2e5ce2b79523b631
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group original catalog/query and the explicit checked-upper fixture tree. |
| inputs / outputs | Fixture type with Catalog, Query and FreeConnexTree owning fields. |
| invariants | The fixture retains the original CQ independently of specialized execution metadata; its tree is not a minimum-height certificate. |
| ownership | Ordinary caller/compiler DTO ownership; no runtime account or mutable native table. |
| failure | Type declaration has no executable failure branch. |
| cost | Storage follows supplied schemas/query/tree only upon construction. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp) |

## B0005

[Lines 35–62](../../../../../tests/unit/star_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L62:sha256:5c0888c08303a26745d0fc49da6511919dd1a6bdc540b21b31423043fef191f8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct original all-variable-center/unary-satellite fixtures with exact head positions. |
| inputs / outputs | Positive test arity, ordered/repeated center-coordinate head and optional satellite-coordinate list in; owning Fixture out. |
| invariants | Empty satellite list selects all coordinates for these fixtures. Center is table/occurrence0 with distinct variables; each declared satellite has a distinct physical source and unary child. Head aliases/order/repetitions survive. Lowerer performs the actual plan validation. |
| ownership | Owns ordinary strings/vectors/sets in returned original metadata; no production star group/H state is consulted. |
| failure | Fixture allocation errors propagate; invalid production shape checks occur later in lower/admit. |
| cost | O(d+satellite count+head width) metadata construction plus set/string/container costs. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0006

[Lines 63–69](../../../../../tests/unit/star_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L69:sha256:3167f368c04bddef11d24557a952c06253a25141c19a6c512ea0c0b39d0a3ecd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a genuine general comparison fixture under the selected source backend. |
| inputs / outputs | Original Fixture and indexed flag in; validated PhysicalPlan out. |
| invariants | Indexed fixture retains finite original limits and raises only per-table index capacity enough for wide declared trees. This is explicit test configuration, not an unbounded backend or optimizer registration. |
| ownership | Borrows original DTOs during lowering; returned compiler plan owns its immutable metadata. |
| failure | Existing lowerer validation, cold work and allocation failures propagate. |
| cost | Cold genuine lowering/identity/validation, separate from star update/cursor cost. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0007

[Lines 70–77](../../../../../tests/unit/star_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L77:sha256:380a1314f9d8c2bb01d8a2b7ea61906d6e58a648be42189b3154e39949d53142
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one named native Error refusal or an explicitly unnamed resource/index refusal. |
| inputs / outputs | One callable and optional Error code in; returns only after crown::Error, MemoryFailure or IndexFailure is caught under the documented expectation. |
| invariants | Executes the action once. A nonempty expected code is compared only with crown::Error and cannot be satisfied by memory/index failure; either requires an unnamed expectation. Unexpected success or wrong family/code fails. Other exception types propagate. |
| ownership | Borrows action/code for this synchronous test call; owns no native state or replacement retry mechanism. |
| failure | Expected refusal is test evidence. check() throws for success/mismatch. This added IndexFailure catch permits explicit cold metadata_work denial without presenting it as a semantic shape error. |
| cost | One real attempted operation plus bounded catch/code checks; actual constructor/update/cursor work remains additional. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0008

[Lines 78–85](../../../../../tests/unit/star_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L85:sha256:dc81bba00d58561d57620e5ace282272c4dd745e1e1d17c4cb86dcd343e326a9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exhaust a real result cursor while detecting duplicate projected output before set conversion. |
| inputs / outputs | Const Runtime and optional metrics output pointer in; owning exact Relation out. |
| invariants | Each exported tuple must insert exactly once. Terminal cursor metrics are captured only after full enumeration; no new reference evaluator is substituted. |
| ownership | Cursor/native tuples retain their original account during traversal; exported Row/Relation is ordinary test memory; caller may receive copied scalar metrics. |
| failure | Duplicate check or native/export/allocation failure propagates; RAII closes the cursor. |
| cost | Full enumeration and owning set exports with ordered comparisons; deliberately outside production maintenance accounting. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0009

[Lines 86–88](../../../../../tests/unit/star_test.cpp#L86); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L88:sha256:72830b50cba8bc1108bd97097705f3b759ebacf7eb20969b9d5110674e499408
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark the degree/H helper as an independent slow original-source definition. |
| inputs / outputs | Comment separating oracle-only scans from maintained histogram/labels/groups/cursor logic. |
| invariants | The following exact_h recomputes expected H from caller degree counts and is not an implementation of the production mechanism or its paper cost. |
| ownership | Comment creates no owner. |
| failure | No executable failure branch. |
| cost | No runtime work. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [build/verification/v68-star-proof-v1/audit.txt](../../../../../build/verification/v68-star-proof-v1/audit.txt), [src/runtime/star_hindex.hpp](../../../../../src/runtime/star_hindex.hpp) |

## B0010

[Lines 89–104](../../../../../tests/unit/star_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L104:sha256:ab3e0f676f1aeb30b37f142ec480b0025552eebef749c73aaeb6787bb216c255
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute generalized H independently by enumerating its exact integer definition. |
| inputs / outputs | Positive-degree map and positive center arity d in; max r with at least r degrees&gt;=r^(d-1) out. |
| invariants | Checked uint64 multiplication treats an overflowing mathematical threshold as unattainable. Center degree counts, not satellite volume/max degree, determine H. Test fixtures keep d positive. |
| ownership | Borrows the ordinary model map, uses scalar scratch, retains no production histogram or key owner. |
| failure | No explicit native failure path; caller fixture/assertions establish model inputs. |
| cost | Quadratic degree-key scans plus exponent arithmetic per call; intentional oracle work, not a native H-maintenance bound. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [build/verification/v68-star-proof-v1/audit.txt](../../../../../build/verification/v68-star-proof-v1/audit.txt), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0011

[Lines 105–107](../../../../../tests/unit/star_test.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L107:sha256:2c97133b9df2859cff07e40c372e51e79367c7b07a7e2ddfe0cf138096d49a39
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose a bounded original-account memory grant for ordinary Trial fixtures. |
| inputs / outputs | No input; Options with32MiB source/support memory limit out. |
| invariants | The configured limit belongs to each actual runtime owner and is not replenished per update or combined across queries. |
| ownership | Small caller-owned option value; the later Runtime establishes the account. |
| failure | No allocation or admission here; factory errors arise when options are consumed. |
| cost | Fixed value initialization. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0012

[Lines 108–112](../../../../../tests/unit/star_test.cpp#L108); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L112:sha256:354462a5a2150bcd5dd8f64e5e9841fc3ca1846225124142d339a7defb0ad7c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain original fixture, genuine star plan, native owner and original full-state A04 session together. |
| inputs / outputs | Trial member declarations for original, plan, owner and oracle. |
| invariants | Semantic comparisons use the original CQ/catalog and full physical database. The native source-only query never becomes expected-answer authority. |
| ownership | Trial owns native and ordinary reference state separately; reverse destruction keeps compiler/original fixture owners alive while execution/reference fields release. |
| failure | Declarations alone have no executable failure branch. |
| cost | State is allocated only by the following constructor; declared fields do not execute updates. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp) |

## B0013

[Lines 113–116](../../../../../tests/unit/star_test.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L116:sha256:012fceab0d92def666c83be5f734c887f6145978d8c1309ca214eff82c578189
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty genuine star owner beside an independent original-query A04 session. |
| inputs / outputs | Owned original Fixture, backend and finite runtime options in; initialized Trial verified at sequence0 out. |
| invariants | Uses real lower/admit/Runtime factories. Reference database has one empty physical table per original catalog table. Both owners start empty; no native initialization bypass exists. |
| ownership | Moves fixture into Trial, retains compiler Plan and native account-backed owner; oracle owns separate ordinary Catalog/Query/Database copies. |
| failure | Lower/admission/runtime/oracle construction or initial verification failures unwind the private Trial. |
| cost | Cold lowering/admission/native setup plus original A04 empty-state verification; not ordinary event cost. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp) |

## B0014

[Lines 117–144](../../../../../tests/unit/star_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L144:sha256:b6f8c9fe385ff142f08e6b146c85994ada3d887a42386e039485eb6d678d8e5f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check committed semantics, complete sources and center-only H/key observations at every Trial prefix. |
| inputs / outputs | Live Trial in; returns only when ready/sequence/source/current set/existence/gauges/keys and native invariants agree with the original full-state A04 database. |
| invariants | Brute-force degrees come from original center table0. Expected real satellite presence comes from original physical source sets or conceptual truth for unfiltered coordinates. Positive-degree key count and heavy gauge are checked separately; no production histogram is reused as expected H. |
| ownership | Borrows native/oracle state; owns temporary ordinary degree maps/results/source exports and account-funded diagnostic state gauges/cursor results. |
| failure | Any mismatch or native/oracle/resource failure fails the unit; it does not repair committed data. |
| cost | Full source/result/oracle recomputation plus per-coordinate degree/H scans and cold native inspection; intentional verification overhead. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [build/verification/v68-star-proof-v1/audit.txt](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0015

[Lines 145–153](../../../../../tests/unit/star_test.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L153:sha256:c7e929104b6ec3efa9a0c04cdc84554ae1da3fee60479c508da6dd6eeef84034
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one contiguous original physical set event to native owner and A04 oracle, then verify. |
| inputs / outputs | Physical table, sign and owned Row in; native Epoch out after matching sequence/change outcome and prefix verification. |
| invariants | Expected semantics are from original reference::Session. Native source aliases/crossings must remainzero, distinguishing actual specialized production from maintaining the general original join. |
| ownership | Moves input values into a synchronous event; native and oracle own their resulting independent state; returned Epoch is scalar diagnostics. |
| failure | Native/oracle/check failures propagate. Invalid/refused event tests use refusal() directly so neither oracle sequence nor expected state is advanced. |
| cost | One real source/star update plus intentionally slow full verification; counters do not include oracle-side work. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp) |

## B0016

[Lines 154–155](../../../../../tests/unit/star_test.cpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L155:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the Trial fixture definition before the independent acceptance cases. |
| inputs / outputs | Class closing brace and spacing. |
| invariants | No additional mutable test or native state is declared here. |
| ownership | No ownership transfer. |
| failure | No executable failure branch. |
| cost | No runtime work. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp) |

## B0017

[Lines 156–182](../../../../../tests/unit/star_test.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L156-L182:sha256:f295e6d3da429981d9feb7d67dd193a799d7d9f39313d5bf13359afe74f740b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test literal structural/head admission, immutable provenance and precise refusals. |
| inputs / outputs | Source-backend flag in; genuine comparison fixtures and public star admission actions execute. |
| invariants | Checks d/j and every repeated/permuted output coordinate, unchanged original plan identity, complete source-only catalog and surviving Plan move source. Wrong center, zero selected grant, missing hidden satellite, physical self-join and nonunary spoke must refuse. |
| ownership | Owns local ordinary fixtures/compiler plans and shared immutable admitted wrappers; no live native query is required for these cold checks. |
| failure | Unexpected success/code, provenance mismatch or propagated lowerer failure fails the unit; supplied comparison plans remain available. |
| cost | Finite cold fixture/lowering/admission work only; no paper runtime theorem is inferred. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [src/planner/star.cpp](../../../../../src/planner/star.cpp), [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0019

[Lines 184–208](../../../../../tests/unit/star_test.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L184-L208:sha256:3de29f99ffe1c72b0ef10b71fa984fd04ec67bfe16897e7a94d675bd23917aa9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise exact insert/delete/no-op semantics on every source under six head presentations. |
| inputs / outputs | Backend flag in; original three-coordinate star traces run for one/two/full/Boolean/repeated/reordered heads. |
| invariants | Projection collisions retain output while other witnesses survive; final support deletion removes it. Duplicate center insert and absent satellite erase advance valid sequence without operator mutation. Every prefix uses original A04 verification. |
| ownership | Each head owns a separate Trial/account and ordinary oracle state; event rows are copied/moved through public input boundaries. |
| failure | Any semantic, route, no-op or lifecycle mismatch fails through check/native error propagation. |
| cost | Finite traces with complete per-prefix oracle/source/result/invariant scans; not a latency benchmark. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [docs/star.md](../../../../star.md) |

## B0021

[Lines 210–232](../../../../../tests/unit/star_test.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L210-L232:sha256:81c608bd2b7b4c1074a20170969d8924d218f94b16d122d7cb4dc909aa2c9752
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Force exact generalized-H threshold crossings with literal1/2/3-dimensional-side cubes. |
| inputs / outputs | Backend flag in; d=3 center cube insertions/deletions with present satellites execute. |
| invariants | Complete side m cube has m keys of degree m^2 per coordinate and H=m. Removing(3,3,3) drops H3-&gt;2; outer-shell deletion and removing(2,2,2) drops H2-&gt;1. Reinsertion must restore exact state without changing projection semantics. |
| ownership | Local Trial owns native/oracle state; integer loop rows are caller-owned test inputs. |
| failure | Wrong H or original-query/state/invariant mismatch fails; no recomputation recovery is installed. |
| cost | Finite cube traces plus full independent per-prefix verification; observes real maintenance without deriving an amortized bound from small tests. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [build/verification/v68-star-proof-v1/audit.txt](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/star.md](../../../../star.md) |

## B0023

[Lines 234–275](../../../../../tests/unit/star_test.cpp#L234); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L234-L275:sha256:f5bf57bfed1399e860144b14579cfdabfb0c06612d76a57c8947663c622651a2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish real heavy/light update routes and historical hysteresis on an H=1 skew trace. |
| inputs / outputs | Backend flag in;128 center rows(7,i,i), corresponding satellites, real heavy/light toggles and center deletions execute. |
| invariants | Every nonempty center prefix has exact H1 despite degree128. Promotion boundary8/9, heavy retention atdegree2 and demotion atdegree1 require actual relabel/migration. Heavy satellite toggles visitzero center rows/one group; a light toggle visitsone bucket fact. After center empties, the actual still-present satellite must retain a degree0,present=true,heavy=false key until that satellite is explicitly erased; reclamation then follows. |
| ownership | Owns Trial/account and event rows; degree/key observations borrow only during synchronous checks. Real source membership is independent of positive center-degree metadata. |
| failure | Wrong branch counters, labels, source-key lifetime, H or A04 state fail. This card must not be adopted against the known failed preimage assertion demanding immediate key absence. |
| cost | Finite skew/hysteresis trace plus full oracle checks; counters discriminate actual source/group/bucket operations, not a P2 end-to-end bound. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0025

[Lines 277–298](../../../../../tests/unit/star_test.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L277-L298:sha256:514cff392c70a7423801de5be3580707bdaf557c5b212c10f1205d2cdf0e80bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test distinct projected support spanning heavy/light masks and last-witness deletion. |
| inputs / outputs | Backend flag in; center witnesses(7,i,0) and(8,999,0) run under z/repeated-z/full/Boolean heads. |
| invariants | Projected duplicate groups must emitone row with two candidates/one duplicate; local projected quantum is2 and full-head quantum1. Removing a heavy or light witness branch cannot remove output supported by the other; every prefix remains A04-exact. |
| ownership | Owns local Trial and copied terminal cursor metrics; output Relations are ordinary test DTOs. |
| failure | Duplicate, quantum, liveness or native invariant mismatch fails the unit. |
| cost | Finite cross-mask trace, complete enumeration and oracle scans. Small counter checks are implementation acceptance, not a completeness proof. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [docs/star.md](../../../../star.md) |

## B0027

[Lines 300–358](../../../../../tests/unit/star_test.cpp#L300); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L300-L358:sha256:bf2bee6610a8c6d85a8707f5046bb725c3f537f82ae704dded3fcdf22cb68b11
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise cursor leases/output lifetime and atomic update, metadata and later-next resource boundaries. |
| inputs / outputs | Backend flag in; real owner/cursor creation, updates, teardown, work/account denial and original A04 comparisons execute. |
| invariants | Retains the existing lease/sequence/original-account checks. Zero metadata_work must refuse Runtime construction before publishing a usable owner. A d1 two-result cursor with lifetime work7 must emit the first exact row, refuse a later next() with star_cursor_work_limit, release its reader lease and preserve the already owning first tuple. A fresh complete verification must still match original sources/results. |
| ownership | Local Trials own independent original accounts and A04 state. Retained cursor/tuple/account handles survive facade teardown. A temporary blocker consumes the existing account, not another grant; the later first tuple owns its payload after cursor failure. |
| failure | Expected refusals use the narrow helper; invalid sequence/wrong code/lease/output/state mismatch fails. Metadata IndexFailure is accepted only as an unnamed refusal. RAII releases failed private construction/cursor/blocker state; no production retry wrapper is installed. |
| cost | Finite lifecycle/resource scenarios plus full oracle/source/invariant verification. The new cold metadata refusal and work7 cursor are boundary regressions, not universal latency/cost measurements. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/star.md](../../../../star.md) |

## B0028

[Lines 359–363](../../../../../tests/unit/star_test.cpp#L359); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L359-L363:sha256:584981383194b1785d93acf091f9c8671dec2ed760c7385a50c56fb40810bf18
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the allocation-cut regression purpose and same-owner retry obligation before its implementation. |
| inputs / outputs | Comment-only region introducing source/view transaction cuts at reachable one/two-coordinate promotion updates. |
| invariants | The next test targets temporary projections/groups that can be inserted and extracted in one transaction. Each measured allocation prefix must preserve the complete original CQ epoch; the fault is disarmed before retrying that same owner and sequence. The comment is not a passing receipt or proof of the production journal repair. |
| ownership | Comments create no owner; the following function explicitly owns all test/reference/native state. |
| failure | No executable failure branch in the comment. |
| cost | No runtime work; describes the following finite test protocol only. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/star.md](../../../../star.md) |

## B0029

[Lines 364–418](../../../../../tests/unit/star_test.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L364-L418:sha256:cb3b090cd92c0caeb814b4c842ff1002bcb7147d019b7804010383322f96a4a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep every measured allocation prefix through reachable one/two-promotion updates and verify rollback then same-owner retry. |
| inputs / outputs | Backend flag in; two literal setup/target traces, original A04 before/after images, measured native target allocation counts and per-cut pass/failure checks out. |
| invariants | The d2 trace inserts(7,5) after degree4 and the d3 trace inserts(7,8,9) after two degree8 keys, reaching promotion edits with transient projection/group extraction. Original reference::Session supplies complete source/answer endpoints. Every successful calibration allocation position is denied persistently through that attempted apply and unwind. After refusal, source/sequence/results/groups/live groups/H/key count/scale/heavy count/threshold and native invariants must match the prior epoch. After disarming the fault, the SAME owner applies the SAME sequence and must match the original A04 after-state. Coverage is the observed allocation count, not every possible trace or repeated failed apply retries under one armed fault. |
| ownership | Owns ordinary fixture/setup/reference source/result DTOs and independent fresh native owners for calibration and each allocation cut. The per-cut prior State retains original-account diagnostic storage. Allocation denial remains armed until the failed operation unwinds; it is closed before observations/oracle comparison and before same-owner retry. |
| failure | Only std::bad_alloc (including MemoryFailure) satisfies a cut. Missing the measured cut, a nonallocation exception, any rollback gauge/source/answer mismatch or failed same-owner retry fails the unit. The test does not repair state or catch/retry internally while allocation denial is armed. |
| cost | One target calibration plus one fresh setup, denied target, full original-source/result/gauge/invariant inspection and successful retry for each measured allocation position, for both shapes/backends. This is deliberately expensive finite fault coverage; allocation count&gt;10 is a discriminator, not a runtime complexity theorem. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [docs/star.md](../../../../star.md) |

## B0031

[Lines 420–445](../../../../../tests/unit/star_test.cpp#L420); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L420-L445:sha256:073fdfab964b307d13bd42b9fe0ed9ab7a73290c661c77f0f1a1eac348e12bda
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check full-source FK enforcement, independent serial owners and indexed capacity rollback. |
| inputs / outputs | Backend flag in; enforced UNIQUE/FK star sources, two separate Runtime owners and optional one-row indexed cap execute. |
| invariants | Missing referenced parent and referenced-parent deletion refuse without sequence/source change. Different owners have different accounts and isolated progress/results. Indexed row-cap refusal preserves exact prior epoch and a same-sequence valid erase succeeds. |
| ownership | Owns ordinary constrained fixtures, independent native owners/accounts and pre-refusal source DTOs; no shared mutable query state or parallel execution. |
| failure | Expected constraint/cap refusals are checked; state isolation or rollback mismatch fails the unit. |
| cost | Finite source validation and cap scenarios, including real full-source constraint scan cost and explicit snapshot exports. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp), [docs/star.md](../../../../star.md) |

## B0033

[Lines 447–460](../../../../../tests/unit/star_test.cpp#L447); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L447-L460:sha256:0474d86bdadf9234d44ba71f56e043cd441beef81e4ced478140dacdc94d8626
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify conceptual unfiltered coordinates and an actual70-coordinate result path. |
| inputs / outputs | Backend flag in; partial-satellite d3/head-z star and full-satellite d70/head(69,0,69) trace execute. |
| invariants | A free center coordinate without a satellite is always present. Seventy coordinate/satellite slots must work without64-bit mask truncation; ordered repeated wide output remains exact. |
| ownership | Each case owns a separate Trial/native account/reference state; wide input row is ordinary owning test memory. |
| failure | Artificial arity cap, wrong key presence/output or propagated native/oracle failure fails. |
| cost | Query-sized wide metadata and finite event trace plus full verification; no unlimited resource guarantee is asserted. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [docs/star.md](../../../../star.md) |

## B0035

[Lines 462–488](../../../../../tests/unit/star_test.cpp#L462); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L462-L488:sha256:ada78afcc8c62013a2c4cfc2302f7a64007b7650ffdc817cbdff775cab389c52
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare transactional HIndex with an independent exact degree model and exercise inactive/moved-from token publication. |
| inputs / outputs | No input; deterministic 1500-step degree walks for d=1,2,3,5,70, exact power boundary cases and retired/moved-from token moves and commit calls execute. |
| invariants | The finite original-account index is compared with independently held 24-key degrees and exact_h. Abandoned preparations preserve h/keys. Active commit under zero-allocation injection must perform no covered C++ new. Immediately afterward the now inactive pending token is moved once, its moved-from object is moved again, and both resulting tokens receive inert commit calls; the subsequent independent H/key comparison and native invariants must still hold. These added lines exercise inactive iterator lifecycle after possible bucket erasure; they do not inspect internal iterator values. Exact overflow and d=1 exponent-zero conventions remain checked. |
| ownership | Each dimension owns its finite 8 MiB account, HIndex and ordinary degree/model scratch. Pending, retired and moved_from are local move-only Prepared objects borrowing that one live index. The tested two moves occur after publication has retired the token; no live prepared token overlaps a later index mutation. |
| failure | Wrong power/H/key/abandonment/publication observations or native invariants fail through check/Error. Moves and inert commit calls must complete without an abort or exception. No catch converts lifecycle failure to success. No native or debug-iterator pass is established by card authorship. |
| cost | Five finite 1500-step walks plus deliberately slow independent H scans and native diagnostic scans. Each step adds two inactive token moves and two inert commit calls. Only active publication is inside the zero-new scope; this test makes no separate measured allocation bound for the added inactive calls and no general O(1) H-update claim. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [src/runtime/star_hindex.hpp](../../../../../src/runtime/star_hindex.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [build/verification/v68-star-proof-v1/audit.txt](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0036

[Lines 489–490](../../../../../tests/unit/star_test.cpp#L489); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L489-L490:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close translation-unit-private fixtures and tests before process entry. |
| inputs / outputs | Anonymous namespace brace/comment and spacing. |
| invariants | No public runtime API or mutable query state is introduced here. |
| ownership | No ownership transfer. |
| failure | No executable failure branch. |
| cost | No runtime work. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp) |

## B0037

[Lines 491–502](../../../../../tests/unit/star_test.cpp#L491); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L491-L502:sha256:e920bcb89ffe953d1690944c82355b11cc77d8c49b4ce854095588cb2730d615
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the H model and both-backend star cases including the new real allocation-rollback sweep. |
| inputs / outputs | Unit process entry; invokes existing model/admission/semantics/H/routes/projection/lifecycle/source/wide checks and allocation_rollback(indexed), then prints check count only on completion. |
| invariants | Both reference and indexed source backends must complete the full sequence, including every measured one/two-promotion allocation cut. Code authorship and this contract do not establish native/build/sanitizer pass; those require root source-bound receipts. |
| ownership | No shared mutable native owner persists between cases; function scopes own and release independent native/query/reference state. |
| failure | The real std::exception process boundary prints diagnostic and returns1. It does not translate a failed allocation regression into pass or retry the whole suite. |
| cost | Complete finite unit workload plus expensive per-prefix fault/oracle verification; no production performance measurement is claimed. |
| Design | [tests/unit/star_test.cpp](../../../../../tests/unit/star_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/star_driver.cpp](../../../../../tests/reference/star_driver.cpp), [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py), [docs/star.md](../../../../star.md) |
