# `tests/unit/fallback_test.cpp` — block usage map

[Source](../../../../../tests/unit/fallback_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3c076731ea603b4849aa5e76a2f4d88ce931cff5a7d367bd27e143bfd297fd16`. 215 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/fallback_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 17–20](../../../../../tests/unit/fallback_test.cpp#L17) | Callable definition: void check(bool value,const char* message) | calls std::runtime_error; guard void check(bool value,const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 21–28](../../../../../tests/unit/fallback_test.cpp#L21) | Callable definition: template&lt;class F&gt;void refusal(F action,std::string_view code={}) | calls action, check, empty, code; guard catch(const Error& e){failed=true;check(code.empty()\|\|e.code()==code,"unexpected Error category");} · [reviewed contract](#b0003) |
| [B0004 · 29–31](../../../../../tests/unit/fallback_test.cpp#L29) | Callable definition: Row ints(std::initializer_list&lt;std::int64_t&gt; values) | calls emplace_back; returns out; growth emplace_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 32–34](../../../../../tests/unit/fallback_test.cpp#L32) | Callable definition: template&lt;class Range&gt;Relation rows(const Range& values) | calls check, insert, storage::export_row, values; guard Relation out;for(const auto& t:values)check(out.insert(storage::export_row(t.values())).second,"dup…; returns out; growth insert; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 35–35](../../../../../tests/unit/fallback_test.cpp#L35) | Type/record definition: struct Fixture |  · [reviewed contract](#b0006) |
| [B0007 · 36–48](../../../../../tests/unit/fallback_test.cpp#L36) | Callable definition: Fixture triangle(std::vector&lt;std::size_t&gt; head={0,2},bool cyclic=true,bool self=false) | calls push_back, std::to_string, size; returns f; growth push_back; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 49–53](../../../../../tests/unit/fallback_test.cpp#L49) | declares types or opens a type body. |  · [reviewed contract](#b0008) |
| [B0009 · 54–56](../../../../../tests/unit/fallback_test.cpp#L54) | Callable definition: Trial(Fixture f,bool indexed,fr::Options options={}) :original(std::move(f)),selected(pf::admit(original.catalog,original.query,i… | calls original, std::move, selected, pf::admit · [reviewed contract](#b0009) |
| [B0010 · 57–71](../../../../../tests/unit/fallback_test.cpp#L57) | Callable definition: void verify() | calls check, ready, sequence, source_snapshot; guard check(owner.ready(),"fallback owner stayed busy");check(owner.sequence()==model.sequence(),"fallbac…; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 72–77](../../../../../tests/unit/fallback_test.cpp#L72) | Callable definition: fr::Epoch apply(std::size_t table,SetOperation operation,Row values) | calls sequence, std::move, check, rows; guard check(rows(epoch.added)==reference.delta.added&&rows(epoch.removed)==reference.delta.removed,"fallb…; returns epoch · [reviewed contract](#b0011) |
| [B0012 · 78–78](../../../../../tests/unit/fallback_test.cpp#L78) | Closes surrounding scope/type. |  · [reviewed contract](#b0012) |
| [B0013 · 79–97](../../../../../tests/unit/fallback_test.cpp#L79) | Callable definition: void admission() | calls triangle, pf::admit, check, structure; guard check(p.structure().query_class==planner::QueryClass::cyclic&&p.profile().reason==pf::Reason::cycli…; growth push_back · [reviewed contract](#b0013) |
| [B0014 · 98–114](../../../../../tests/unit/fallback_test.cpp#L98) | Callable definition: void semantics(bool indexed) | calls random, t, triangle, apply; guard const auto unused=t.apply(3,SetOperation::insert,ints({99}));check(!unused.metrics.recomputed,"unus…; growth insert; 3 loop sites · [reviewed contract](#b0014) |
| [B0015 · 115–137](../../../../../tests/unit/fallback_test.cpp#L115) | Callable definition: void terms_and_constants(bool indexed) | calls t, apply, std::string, ints; guard check(nonlast.removed.empty(),"nonlast projected physical witness retracted fallback output");; growth insert · [reviewed contract](#b0015) |
| [B0016 · 138–152](../../../../../tests/unit/fallback_test.cpp#L138) | Callable definition: void typed(bool indexed) | calls t, apply, run, std::string; growth insert; 4 loop sites · [reviewed contract](#b0016) |
| [B0017 · 153–170](../../../../../tests/unit/fallback_test.cpp#L153) | Callable definition: void wide_and_estimates(bool indexed) | calls reserve, push_back, std::to_string, emplace_back; guard check(e.witness_product==0&&!e.prefix_product_sum,"late zero erased an overflowing prefix estimate"…; growth emplace_back, insert, push_back, reserve; 2 loop sites · [reviewed contract](#b0017) |
| [B0018 · 171–185](../../../../../tests/unit/fallback_test.cpp#L171) | Callable definition: void constraints_and_limits(bool indexed) | calls triangle, push_back, constrained, refusal; growth insert, push_back · [reviewed contract](#b0018) |
| [B0019 · 186–203](../../../../../tests/unit/fallback_test.cpp#L186) | Callable definition: void allocation_cuts(bool indexed,bool deletion) | calls triangle, apply, ints, sequence; guard check(failed&&triggered,"fallback allocation refusal not authenticated");t-&gt;verify();; returns t; PhysicalSetUpdate{t.owner.sequence()+1,TableId{2},deletion?SetOperation::erase:SetOperation::ins…; growth insert, make_unique; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 204–209](../../../../../tests/unit/fallback_test.cpp#L204) | Callable definition: void lifetime() | calls t, triangle, apply, ints; guard check(rows(snapshot.rows)==Relation{ints({1,10})},"fallback snapshot did not survive owner teardown…; returns t.owner.snapshot(); growth insert · [reviewed contract](#b0020) |
| [B0021 · 210–210](../../../../../tests/unit/fallback_test.cpp#L210) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0021) |
| [B0022 · 211–215](../../../../../tests/unit/fallback_test.cpp#L211) | Callable definition: int main() | calls admission, lifetime, semantics, terms_and_constants; returns 0; 1; 1 loop sites · [reviewed contract](#b0022) |

## B0001

[Lines 1–16](../../../../../tests/unit/fallback_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:1565930272866786f8a910bf46e0d7a443dd62f6b2455e87c743d7ecc62e71ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the real fallback owner and independent A04/full-allocation test support. |
| inputs / outputs | Includes/private namespaces and assertion counter. |
| invariants | A04 remains a separate full original-query reference. Allocation injection is test-only single-TU support, not production fallback exception machinery. |
| ownership | Ordinary fixture/model DTOs surround separate native accounts; serial process counter only. |
| failure | Ordinary compilation/link failures. |
| cost | Compile-time setup plus later actual suite execution. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0002

[Lines 17–20](../../../../../tests/unit/fallback_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L20:sha256:2a2b7e18989b68db65f21e7bd5955e01f2d43fa194a9fe4fa199f088be7c658e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count meaningful unit assertions independently of NDEBUG. |
| inputs / outputs | Boolean/static diagnostic in; increment checks only on true. |
| invariants | False cannot silently pass an optimized build. |
| ownership | Inline serial test counter; no native mutation. |
| failure | Throws runtime_error for process boundary. |
| cost | One condition/increment plus failure formatting. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp) |

## B0003

[Lines 21–28](../../../../../tests/unit/fallback_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L28:sha256:8b0f12fde933edfc9edd1b93e435228d35cb374581a9707be1711720f2ecd52c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a real fallback operation to reject with an optional exact domain. |
| inputs / outputs | Callable and optional code in; accepts Error, MemoryFailure or IndexFailure only after code checks. |
| invariants | No specific code accepts an unrelated diagnostic; absence of refusal fails. This helper installs no production retry policy. |
| ownership | Synchronous callable and diagnostic borrows. |
| failure | Unexpected failure type escapes; wrong/missing failure throws test assertion. |
| cost | One actual action and finite diagnostic checks. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0004

[Lines 29–31](../../../../../tests/unit/fallback_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L31:sha256:ac7c8219d6134541e555df1d4644bcbd8c6c44b9f312bf90fdacb54d3d5db3a4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct exact ordinary integer physical rows for native/reference fixtures. |
| inputs / outputs | initializer_list&lt;int64&gt; in; owning Row out. |
| invariants | No floating conversion or native evaluator supplies expected values. |
| ownership | Ordinary Row/vector owns all scalar descriptors. |
| failure | Allocation failure propagates. |
| cost | O(row width) descriptor allocation/construction. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0005

[Lines 32–34](../../../../../tests/unit/fallback_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L34:sha256:ec14945962ea9b9e29f53d1778af4bb31bea540e1308fbbdc5d924f0d460766f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export native endpoint/snapshot tuples and require distinct projected output. |
| inputs / outputs | Native tuple range in; ordinary exact Relation out. |
| invariants | Every tuple insertion must be unique; native duplicates fail instead of being hidden by set comparison. |
| ownership | Tuple payloads remain borrowed during export; ordinary exported rows own reference copies. |
| failure | Duplicate/export/allocation errors fail through check/main. |
| cost | Full scalar export, payload copies and ordered insertion per result row. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0006

[Lines 35–35](../../../../../tests/unit/fallback_test.cpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L35:sha256:06741f17d4822566823d4f5344618de6f57f973d6c4c2f184367103df00d66f5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own original catalog/query test DTOs independently of admitted/native state. |
| inputs / outputs | Fixture aggregates Catalog and Query. |
| invariants | Fixture is mutable caller data, not an admission/certificate or runtime Binding. |
| ownership | Ordinary compiler ownership of metadata and literal payloads. |
| failure | Construction/copy allocation follows normal C++ failures. |
| cost | Storage proportional to fixture metadata. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp) |

## B0007

[Lines 36–48](../../../../../tests/unit/fallback_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L48:sha256:3395f5b681f5e43047be3c788fd95131f6129429a4ebe76dbc4de18c94d2289b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct literal path/triangle and self-source-alias original CQs with configurable heads. |
| inputs / outputs | Ordered/repeated/Boolean variable IDs plus cycle/self flags in; four-source Fixture out. |
| invariants | Every alias keeps an independent occurrence ID and original two-field scope. self=true maps all active occurrences to R; unused source remains physical. No tree or original free-connex certificate is requested. |
| ownership | Owns ordinary complete original catalog/query/head metadata. |
| failure | Invalid head IDs are not repaired here and must be refused by admission; normal allocation errors propagate. |
| cost | Fixed small graph plus O(head width) aliases/output descriptors. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0008

[Lines 49–53](../../../../../tests/unit/fallback_test.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L53:sha256:0134b4a2e43505195c6971dcc909d136e9aca89e7365b517bbbd0c7b24e8404b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group independently owned original data, admitted plan, actual owner and full A04 session. |
| inputs / outputs | Trial field declarations. |
| invariants | Native answers and reference state do not share storage or computation; declaration order keeps original DTOs available for cold admission and reference creation. |
| ownership | Ordinary original/Plan/reference DTOs plus separately funded native Runtime account. |
| failure | Partial Trial construction unwinds prior fields. |
| cost | Stores both models and one runtime; not a production shared-query design. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0009

[Lines 54–56](../../../../../tests/unit/fallback_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L56:sha256:f1cc9e1bcebb2dba0ebab950084cb056d0ceede9b360f26eb07dd36af91e2a62
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a genuine explicit fallback owner and independent original-query reference from empty sources. |
| inputs / outputs | Fixture/backend/runtime Options in; admitted Plan, native Runtime and reference Session constructed then verified. |
| invariants | Original catalog/query copies remain independent. Both backend policies use the same unchanged CQ; source-only lowering is owned by admission. Initial Boolean/constant behavior is checked immediately. |
| ownership | Trial owns ordinary immutable Plan and independent A04 Database/Session; Runtime freezes original metadata into its account. |
| failure | Admission, construction, allocation or initial disagreement fails construction without a published successful trial. |
| cost | Cold admission, original-account native freeze and full verification work. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0010

[Lines 57–71](../../../../../tests/unit/fallback_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L71:sha256:ee2b8fb958b9b45d0c7bf34dce33244afc65d18a680056922e125ada7fb39eed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify committed native source/result/sequence/class observations against original A04 state. |
| inputs / outputs | Live Trial in; checks ready/sequence/full sources/snapshot/existence/original atom count/zero coordinator/class/cardinalities. |
| invariants | Full original database and exact projected answers must match. Binding retains original occurrences; source coordinator has none. EXPLAIN class equals real admission analysis and counts every source, including unused tables. Does not infer correctness solely from matching metadata or check peak-byte estimates. |
| ownership | Temporary native Snapshot/Explain own their outputs; ordinary exports and A04 recomputation are explicit test copies. Serial owner reads only. |
| failure | Any mismatch or native export/read failure fails; no state repair. |
| cost | Full source export, snapshot export, repeated A04 recomputation and table-count scans per verification. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0011

[Lines 72–77](../../../../../tests/unit/fallback_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L77:sha256:aa3073e22c8ae8ec95dbf9389ccc052ae84716381c47db7d975c7032f0078913
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one actual update and exact projected endpoint difference against A04. |
| inputs / outputs | Physical table/operation/full Row in; apply same next sequence to reference and native, then return owning native Epoch. |
| invariants | Full original-query A04 delta defines added/removed, including alias fanout and final projection witness loss. Physical membership flags and complete post-state must agree. This helper is for valid updates; expected refusal tests bypass it so model does not advance first. |
| ownership | Owns update Row and returned Epoch; reference/native sessions remain independent. |
| failure | Unexpected native failure after reference advance fails the trial/test immediately; no production retry is hidden. |
| cost | One full reference update, one real native apply, full endpoint exports and poststate verification. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0012

[Lines 78–78](../../../../../tests/unit/fallback_test.cpp#L78); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L78:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the Trial independent-owner helper. |
| inputs / outputs | Type delimiter only. |
| invariants | No additional runtime behavior or certificate. |
| ownership | No owner created here. |
| failure | No branch. |
| cost | No runtime work. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp) |

## B0013

[Lines 79–97](../../../../../tests/unit/fallback_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L97:sha256:02356beaf9fbec6ba8e0449a76d6c5aff3cf201c1780be89303bc584dd1a7f3e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test genuine structural reasons, immutable original ownership, checked estimates and admission refusal. |
| inputs / outputs | Literal cyclic/non-free-connex/free-connex fixtures, count arrays and malformed/zero-limit inputs. |
| invariants | Class/reason are actual; mutating caller head cannot change admitted copy. Constant coordinator retains all sources without joins. Checked source+assignment/output/state counts are exact; zero factor wins product despite source-sum overflow. Wrong width, work/recognition exhaustion, invalid head and nullable source refuse. No original-tree/GHD proof is fabricated. |
| ownership | Independent ordinary DTOs/Plans/estimate scalars; no native runtime or shared-query state required. |
| failure | Typed work errors required where specified; other invalid premises must actually refuse via helper. |
| cost | Finite cold validation/recognition/lowering/copy/estimate operations, including deliberate refusal paths. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [src/planner/fallback.cpp](../../../../../src/planner/fallback.cpp), [docs/fallback.md](../../../../fallback.md) |

## B0014

[Lines 98–114](../../../../../tests/unit/fallback_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L98-L114:sha256:a279c511800f8e484103abdea0a920542328e869c166a656966a483cb849120b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare cyclic and projected path updates with original A04 through seeded insertions/deletions and self aliases. |
| inputs / outputs | Backend flag; eight head/body combinations each receive 100 seeded operations, then explicit self-source trace. |
| invariants | Repeated/Boolean/all-variable heads preserve exact semantics. Unused source changes and duplicate inserts must skip recompute. Self-cycle uses real alias joins; its control requires three projected rows before further mutation. Every accepted prefix and endpoint passes Trial verification. |
| ownership | Each Trial has independent reference/native state; deterministic RNG reused serially within backend. |
| failure | Any semantic/trigger/delta mismatch fails, with no approximate fallback. |
| cost | Hundreds of finite native operations plus full A04/export observations; no throughput/complexity claim. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/fallback.md](../../../../fallback.md) |

## B0015

[Lines 115–137](../../../../../tests/unit/fallback_test.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L137:sha256:3039c743ec11ae207914fc28a1494948583688165d38ed01c78ab50831f74477
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discriminate repeated-variable/ignored-field/constant filtering and last projected witness deletion. |
| inputs / outputs | Backend flag; exact full rows, constant filters, nullary/empty-body and contradictory fixtures. |
| invariants | Mismatched repeated terms cannot satisfy; ignored payloads still distinguish physical witnesses. Removing one payload retains output; removing last retracts exactly once. Empty body is one empty tuple regardless unused nullary events; nullary atom needs actual presence. Contradiction retains reason and never recomputes body on source updates. |
| ownership | Separate Trials own native/reference state; NUL string physical payload is copied explicitly. |
| failure | Any missing/spurious answer/delta/recompute mismatch fails. |
| cost | Finite complete native/A04 updates and original-source captures; projection/dedup/cleanup costs remain real. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/fallback.md](../../../../fallback.md) |

## B0016

[Lines 138–152](../../../../../tests/unit/fallback_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L138-L152:sha256:0112705f979d722ffc8797962ee56b7e946a68977b42280140eefb6da45e3896
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact same-kind source equality and ordered/repeated output across scalar domains. |
| inputs / outputs | Backend flag; typed scalar value grids for int64, string, bool, finite Date and DecimalSpec(38,4). |
| invariants | One repeated variable binds both source fields; only exact equality passes. All value pairs are inserted then erased, with full original reference checks. Int64 extremes, empty/NUL/UTF8 strings, date extremes and large exact decimals avoid floating conversion. |
| ownership | Owns ordinary Value fixture grids/metadata and separate Trial per scalar kind; native payloads remain original-account owned. |
| failure | Parser/spec/admission/runtime/ref disagreement fails; no coercion or approximation is allowed. |
| cost | Cartesian finite value grids times insert/delete and both backends, with full A04 and export work. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0017

[Lines 153–170](../../../../../tests/unit/fallback_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L170:sha256:3555eda2d4f7ce3869f00fc72184be164e221f68f72b29a760fb3721dd748a85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify width beyond64 and distinguish raw product overflow from exact later-zero assignment bounds. |
| inputs / outputs | Backend flag; one70-variable atom and66-atom aliases plus late ignored-field source. |
| invariants | No uint64 variable/alias mask truncates admission/runtime. 65 repeated unary source factors overflow advisory prefix/product, yet later empty table yields exact full product0 while prefix remains unknown. Plan pre-scan also yields assignment0; filling late source makes product/prefix unknown without wrapping. A04 checks actual small answers independently. |
| ownership | Owns complete wide metadata/rows, original/reference/native states and Explain outputs. |
| failure | Any truncation, overflow wrapping, wrong zero handling or semantic disagreement fails. |
| cost | Finite70-column and66-occurrence interpretation plus potentially long failed prefixes; no CPU bound from final product0. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/fallback.md](../../../../fallback.md) |

## B0018

[Lines 171–185](../../../../../tests/unit/fallback_test.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L171-L185:sha256:f774b1bf249da320de3340dcd70bf1261047e5105862f9341d638c4ee76cfac4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify source constraints and finite answer/source/snapshot/construction refusal preserve published state. |
| inputs / outputs | Backend flag; enforced UNIQUE/FK, one-answer cap, zero snapshot grant, two-source-row capture cap and zero constructor work. |
| invariants | Missing FK and referenced-parent deletion refuse atomically. Result-row refusal preserves old state and permits same-sequence valid alternative. Snapshot work refusal leaves ready. Source capture cap includes unused physical rows; refusal is checked against unchanged A04 state. Constructor zero budget cannot publish owner. |
| ownership | Separate constrained/limited/capture Trials with independently owned native/reference state; refused native calls never advance reference. |
| failure | Required fallback_row_limit, fallback_work_limit and source_image_row_limit are authenticated by actual code checks; all negative calls must refuse. |
| cost | Finite source validation, private source-image/evaluation/delta preparation and full unchanged-state observations; tests do not cap all diagnostic CPU/memory. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp) |

## B0019

[Lines 186–203](../../../../../tests/unit/fallback_test.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L186-L203:sha256:0dc513ae45464d39b6872b0a1f5518396f7a3fa1bc50fe37c1e928217eb223fe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep authenticated persistent allocation prefixes through real fallback added/removed endpoint preparation. |
| inputs / outputs | Backend/deletion direction in; successful control counts all observed C++ new attempts, each prefix denied in a fresh discriminating Trial. |
| invariants | Both insertion and deletion change an actual projected output. Every cut requires failed and s04_alloc::triggered; verify old original source/result/sequence before retry. Same owner accepts same update/sequence after denial ends, then exact retry deltas match A04. Seam is test-only C++ new coverage, not universal allocator/callback fault completeness. |
| ownership | Nonnested thread-local denial scope persists through attempted apply cleanup; owner and A04 state remain separate. Successful owning Epoch lives through delta verification. |
| failure | catch(...) records refusal only; authenticated trigger plus unchanged-state and retry checks prevent unrelated early exceptions passing. Zero-allocation control fails. |
| cost | One successful control plus setup/denial/full verification/same-owner retry per observed allocation, across both backends/directions. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0020

[Lines 204–209](../../../../../tests/unit/fallback_test.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L204-L209:sha256:fbe8515c4930b06555ab73e444ca331afcd270d33e44e3c19bd06c11c40f15b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify original-account output survives owner teardown and independent runtimes remain isolated. |
| inputs / outputs | Returned owning Snapshot from destroyed Trial and two independent triangle owners. |
| invariants | Snapshot retains exact rows plus native accounted payload and original head metadata. Updating owner a cannot change untouched owner b; no shared-query state. |
| ownership | Snapshot retains Binding/account/tuples independently of Runtime lifetime; a/b each own a new query account and reference model. |
| failure | Dangling/unaccounted/mismatched output or isolation failure fails the unit. |
| cost | One retained snapshot plus finite independent-owner updates/exports. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0021

[Lines 210–210](../../../../../tests/unit/fallback_test.cpp#L210); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L210-L210:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close private fallback unit helpers. |
| inputs / outputs | Namespace delimiter only. |
| invariants | No runtime registration, callback or hidden recovery logic. |
| ownership | No owner. |
| failure | No executable failure branch. |
| cost | No runtime work. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp) |

## B0022

[Lines 211–215](../../../../../tests/unit/fallback_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L211-L215:sha256:fcefd2e1eae2372559671ca1416edd03cf8576630d0841e16bcf5e8fa99fa745
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run actual finite fallback/A04 semantics, ownership, estimates, refusal and allocation tests. |
| inputs / outputs | Process executes admission/lifetime and both-backend semantic/type/wide/constraint/allocation suites, then prints actual check count. |
| invariants | Success requires all actual tests complete; source contracts are not passing receipts or full-suite/proof acceptance. Tests are independent serial owners, not shared/distributed queries. |
| ownership | All owners/reference models are scoped within tests; retained outputs intentionally extend account lifetime. |
| failure | One standard-exception diagnostic returns one. No production catch/retry machinery is introduced. |
| cost | Sum of finite suite work and diagnostic formatting only. |
| Design | [tests/unit/fallback_test.cpp](../../../../../tests/unit/fallback_test.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/fallback.md](../../../../fallback.md) |
