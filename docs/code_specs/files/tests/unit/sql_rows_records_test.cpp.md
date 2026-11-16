# `tests/unit/sql_rows_records_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_rows_records_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `999652ee48ee57fafafb00df2b0901f5c031881d8f2614784424334aa96deee1`. 167 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/sql_rows_records_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../tests/unit/sql_rows_records_test.cpp#L15) | Callable definition: Catalog schema() | calls ; returns {1,{{@ ,{{@ ,ScalarType::int64,true},{@ ,ScalarType::string,true}}}}} · [reviewed contract](#b0002) |
| [B0003 · 16–16](../../../../../tests/unit/sql_rows_records_test.cpp#L16) | Callable definition: Cell n(std::int64_t value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../tests/unit/sql_rows_records_test.cpp#L17) | Callable definition: Cell text(std::string_view value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0004) |
| [B0005 · 18–23](../../../../../tests/unit/sql_rows_records_test.cpp#L18) | Callable definition: frontend::SqlRowsProgram bind(std::string_view sql,bool retain=true) | calls frontend::bind_sql_rows, schema, assert, std::move; guard assert(std::holds_alternative&lt;frontend::SqlRowsProgram&gt;(result));; returns std::get&lt;frontend::SqlRowsProgram&gt;(std::move(result)) · [reviewed contract](#b0005) |
| [B0006 · 24–27](../../../../../tests/unit/sql_rows_records_test.cpp#L24) | Callable definition: FreeConnexTree tree(const frontend::SqlRowsProgram& program) | calls export_core, planner::minimum_tree, assert; guard assert(chosen.status==planner::OracleStatus::proven_minimum && chosen.tree);return *chosen.tree;; returns *chosen.tree · [reviewed contract](#b0006) |
| [B0007 · 28–28](../../../../../tests/unit/sql_rows_records_test.cpp#L28) | Callable definition: rr::Hash hash(char c) | calls fill; returns value · [reviewed contract](#b0007) |
| [B0008 · 29–29](../../../../../tests/unit/sql_rows_records_test.cpp#L29) | Callable definition: rr::Id id(char c) | calls fill; returns value · [reviewed contract](#b0008) |
| [B0009 · 30–32](../../../../../tests/unit/sql_rows_records_test.cpp#L30) | Callable definition: void integer(std::string& bytes,std::uint64_t value,unsigned width=8) | calls push_back; growth push_back; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 33–33](../../../../../tests/unit/sql_rows_records_test.cpp#L33) | Explanatory comments or spacing. | source comment (unverified): // Independent wire construction pins all framing bytes, not merely codec info. · [reviewed contract](#b0010) |
| [B0011 · 34–38](../../../../../tests/unit/sql_rows_records_test.cpp#L34) | Callable definition: std::string envelope(std::string body) | calls result, integer, size, sha256_fixed; returns result+body; source comment (unverified): // Independent wire construction pins all framing bytes, not merely codec info. · [reviewed contract](#b0011) |
| [B0012 · 39–42](../../../../../tests/unit/sql_rows_records_test.cpp#L39) | Callable definition: std::string body(std::uint64_t sequence,bool changed,std::uint64_t rows) | calls integer, append; returns result · [reviewed contract](#b0012) |
| [B0013 · 43–47](../../../../../tests/unit/sql_rows_records_test.cpp#L43) | Callable definition: void reseal(std::string& bytes) | calls size, std::uint64_t, sha256_fixed, std::string_view; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 48–50](../../../../../tests/unit/sql_rows_records_test.cpp#L48) | Callable definition: template&lt;class Action&gt; void rejected(Action action) | calls action, assert; guard bool failed=false;try{action();}catch(const recovery::ImageFailure&){failed=true;}assert(failed); · [reviewed contract](#b0014) |
| [B0015 · 51–62](../../../../../tests/unit/sql_rows_records_test.cpp#L51) | Callable definition: void inspect_checks(const frontend::SqlRowsProgram& program,std::string_view bytes) | calls deny, rr::inspect, assert, size; guard rr::Inspected checked{};{s04_alloc::Scope deny(0);checked=rr::inspect(program,bytes);assert(s04_all…; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 63–88](../../../../../tests/unit/sql_rows_records_test.cpp#L63) | Callable definition: void binding_opt_in() | calls bind, assert, binding_image, empty; guard assert(ordinary.binding_image().empty() && !retained.binding_image().empty());; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 89–110](../../../../../tests/unit/sql_rows_records_test.cpp#L89) | Callable definition: void magnitudes_and_wire(bool indexed) | calls bind, resource::MemoryAccount::create, runtime::SqlRowsRuntime::create_into, tree; guard assert(frame.bytes()==envelope(expected));assert(std::get&lt;rr::RowInfo&gt;(frame.info().payload).rows==… · [reviewed contract](#b0017) |
| [B0018 · 111–137](../../../../../tests/unit/sql_rows_records_test.cpp#L111) | Callable definition: void support_and_constants(bool indexed) | calls bind, resource::MemoryAccount::create, runtime::SqlRowsRuntime::create_into, tree; guard assert(info.output_changed && info.rows==(exists?2U:1U));; 1 loop sites; source comment (unverified): // The constant7 is typed bigint and must remain7 even in checksum-valid frames. · [reviewed contract](#b0018) |
| [B0019 · 138–160](../../../../../tests/unit/sql_rows_records_test.cpp#L138) | Callable definition: void input_and_wal() | calls bind, resource::MemoryAccount::create, n, text; guard assert(view.source-&gt;source=="feed" && view.reader==(rr::ReaderPosition{12,1}) && view.replacements\[… · [reviewed contract](#b0019) |
| [B0020 · 161–161](../../../../../tests/unit/sql_rows_records_test.cpp#L161) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0020) |
| [B0021 · 162–167](../../../../../tests/unit/sql_rows_records_test.cpp#L162) | Callable definition: int main() | calls magnitudes_and_wire, support_and_constants, binding_opt_in, input_and_wal; returns 1; 1 loop sites · [reviewed contract](#b0021) |

## B0001

[Lines 1–14](../../../../../tests/unit/sql_rows_records_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:1e741e4354813b16c6db79c96e7f0c4e87a0a16c0d338165a08012f05c7b5bfc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare finite record-test dependencies, aliases and memory cap. |
| inputs / outputs | Include public row records/hash/planner and test storage/allocation/assertion helpers; define local Cell/rr aliases and 64MiB fixture cap. |
| invariants | Declarations are test setup only; no assertion receipt or runtime action is produced. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0002

[Lines 15–15](../../../../../tests/unit/sql_rows_records_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:b4ae50c250f718391e3153aa7d04affaf9a543b99e80bd6c360de3f07236f815
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the concrete typed physical schema used by this independent finite assertion family. |
| inputs / outputs | No arguments; returns the concrete Catalog tables/columns/constraints/hints written in this fixture. |
| invariants | Returned metadata is editable; no catalog validator is called here. |
| ownership | The returned ordinary vectors/strings own fixture metadata; no receiving account is used. |
| failure | Ordinary fixture allocation failures propagate. |
| cost | Construct the listed finite metadata and name/hint bytes; ordinary allocations occur. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0003

[Lines 16–16](../../../../../tests/unit/sql_rows_records_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L16:sha256:2bf319f40c73e12c8458e1b1453226df5170ad7bbb109d4048da8c938b9de137
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one inline int64 test Cell. |
| inputs / outputs | The int64_t argument becomes an engaged optional ScalarView Cell. |
| invariants | The helper performs no schema admission or owning tuple conversion. |
| ownership | Returned inline int64 value is copied; no borrowed payload or account owner. |
| failure | No intentional validation/failure for int64 input. |
| cost | Fixed optional/variant construction; no allocation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0004

[Lines 17–17](../../../../../tests/unit/sql_rows_records_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:b826961c6119aee9e9a2f24a51e2b651ab77cc083130cd11295c195204eb4e99
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a test string; production ownership is tested separately. |
| inputs / outputs | The string_view argument becomes an engaged optional ScalarView Cell. |
| invariants | No UTF8/schema/ownership validation occurs. |
| ownership | Returned string_view borrows caller backing; no text copy or owner. |
| failure | No intentional validation/failure for a live string_view. |
| cost | Fixed pointer/length optional/variant construction; no byte traversal or allocation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0005

[Lines 18–23](../../../../../tests/unit/sql_rows_records_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L23:sha256:18dcba4863072ed7b51609423d65304723837dd4ee10336e1564a83dbc5c2b2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require genuine original nonaggregate SQL factory admission for the test query. |
| inputs / outputs | SQL plus retain flag (default true) -&gt; genuine SqlRowsProgram via bind_sql_rows(sql,schema(),options with retain_binding_image=retain). |
| invariants | Asserts the factory returns SqlRowsProgram for this fixture. Retention flag controls cold recovery metadata only; actual source hash equivalence is asserted by binding_opt_in. |
| ownership | Factory program owns immutable metadata through its account; fixture strings/catalog are ordinary caller values. |
| failure | A diagnostic fails assert; parser/allocation exceptions propagate to main. |
| cost | Actual cold SQL parsing/binding/normalization and metadata allocation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp) |

## B0006

[Lines 24–27](../../../../../tests/unit/sql_rows_records_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L27:sha256:fdd87b30bd15855a0d8d9cd3d86e866430d285ca33f12941da1e9d8dcb3c27f0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ask the exact planner for this fixture and assert its proven-minimum result. |
| inputs / outputs | A genuine fixture program exports its core; planner::minimum_tree supplies the returned FreeConnexTree. |
| invariants | Asserts the tree/status or certificate flag explicitly present in this body; this helper does not independently replay a certificate. |
| ownership | Core/tree DTOs own ordinary metadata; the immutable program is borrowed. |
| failure | Failed fixture assertions or planner/resource exceptions stop the test. |
| cost | Cold core export and actual finite exact search; may allocate and is not a per-update operation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0007

[Lines 28–28](../../../../../tests/unit/sql_rows_records_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:f783b777f955ec178e7391ae47e726b17c0c90fa9214e7f1e5013ad2c3bb90de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fill a fixed test Hash with the caller-supplied character. |
| inputs / outputs | The char argument fills all64 bytes of the returned rr::Hash. |
| invariants | Fixture callers pass hexadecimal chars; the helper itself checks no character domain. |
| ownership | Returned fixed array owns all64 bytes. |
| failure | No intentional failure. |
| cost | Fixed64-byte fill; no allocation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0008

[Lines 29–29](../../../../../tests/unit/sql_rows_records_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:94cea08188f5b2eb82aa4aaeb87ba457af2a62634301de05e307e31c2eff7fa3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fill a fixed test ID with the caller-supplied character. |
| inputs / outputs | The char argument fills all32 bytes of the returned rr::Id. |
| invariants | Fixture callers pass hexadecimal chars; the helper itself checks no character domain. |
| ownership | Returned fixed array owns all32 bytes. |
| failure | No intentional failure. |
| cost | Fixed32-byte fill; no allocation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0009

[Lines 30–32](../../../../../tests/unit/sql_rows_records_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L32:sha256:beb18906068d8c03b854e593a372e7b1f2d9670d1b3ae47c649da6f7ed4311cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently append exact little-endian words for expected wire bytes. |
| inputs / outputs | Append one uint64 little-endian value to the supplied ordinary string; records helper also takes width. |
| invariants | Callers supply the valid1/8-byte widths used by these fixtures; this helper is not an input validator. |
| ownership | Mutates the caller string, which can grow its ordinary allocation. |
| failure | String allocation failures propagate. |
| cost | A fixed width loop plus actual string growth; no receiving account or native operation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0010

[Lines 33–33](../../../../../tests/unit/sql_rows_records_test.cpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L33:sha256:312afeb4087daa04d81599c19485207cef96fe5632ae24e5597bb2ad5a4d62fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0011

[Lines 34–38](../../../../../tests/unit/sql_rows_records_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L38:sha256:7e1c82c3f5841fa924b60d536874013caa30a09719edf0c000f527f49046f5f8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently construct protected family framing and both checksums for goldens/hostile complete frames. |
| inputs / outputs | Owned std::string body -&gt; complete ordinary CROWNRW2 expected frame string. |
| invariants | Independent layout writes version/reserved/body length, body SHA and84-byte prefix SHA. Uses the same sha256_fixed primitive as production, not an independent hash implementation. |
| ownership | By-value body owns its bytes; returned string owns complete copied framing/body. No receiving account. |
| failure | Ordinary string allocations propagate. |
| cost | Append/copy actual body+148-byte header and hash body/prefix; ordinary string allocations only, no program/native calls. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp) |

## B0012

[Lines 39–42](../../../../../tests/unit/sql_rows_records_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L42:sha256:b44e53a8e025b456b3910bd2f431cc2325ccb4fcf06d497b02f6fa19e415e1aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify the complete row-epoch fixed prefix independently of the production codec. |
| inputs / outputs | Sequence, source-changed flag and row count produce this fixture’s fixed RowEpoch prefix bytes. |
| invariants | Uses generation1/hash a and the fixture I=C=sequence convention; it does not validate arbitrary metadata. |
| ownership | Returns an ordinary owning string. |
| failure | String allocation failures propagate. |
| cost | Fixed prefix construction; no native work. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0013

[Lines 43–47](../../../../../tests/unit/sql_rows_records_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L47:sha256:8316adc6b249cedc085a297f5b6a2c33f4ecc517332dcef1bd3db5a676b77715
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute both hashes so a deliberate mutation exercises semantic/structure rejection beyond checksum validation. |
| inputs / outputs | A mutable complete candidate string gets updated length/body/prefix hashes in place. |
| invariants | Caller must supply at least148 bytes. Rehashing does not make edited payload semantics valid. |
| ownership | Only the supplied string is mutated; fixed hash arrays are temporary. |
| failure | Invalid fixture length would violate the helper premise; no rejection carrier is promised. |
| cost | Hash the actual body and84-byte prefix, then fixed field copies; no account/native change. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0014

[Lines 48–50](../../../../../tests/unit/sql_rows_records_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L50:sha256:7363eaa4615067276b5902688ffd70f74c98eb1d6bc241cc5a34a2a20fd9ca0a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the fixed image rejection carrier for this deliberate invalid input. |
| inputs / outputs | Invoke the supplied Action; assert that it throws ImageFailure. |
| invariants | Only the asserted exception occurrence is established; the action’s semantic state is checked by its caller. |
| ownership | The helper owns no runtime/output data. |
| failure | A missing expected exception fails assert; exceptions outside the caught type propagate. |
| cost | One action call and fixed exception/assert logic, plus the action’s own costs. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0015

[Lines 51–62](../../../../../tests/unit/sql_rows_records_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L62:sha256:377a9fc7b5a61e3e24ee090047196c9406a6f91c92deef0373b8b4af5cdf8013
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect a supplied genuine-program/frame fixture without covered C++ allocation; assert exact/one-under work/bytes plus every truncation and bit mutation refusal. |
| inputs / outputs | Const Program and complete borrowed frame bytes -&gt; void after inspection/limits/corruption assertions. |
| invariants | This is a finite test helper/assertion body, not an execution receipt or proof for other inputs. |
| ownership | Fixture DTOs/expected bytes/maps use ordinary test storage; actual programs/runtimes/codecs use the explicitly created accounts and local owners. |
| failure | The exact catches/assertions in this body check expected refusals; all unhandled failures reach main. No production catch or recovery action is introduced. |
| cost | One allocation-denied inspection, exact/one-under byte/work inspections, every strict truncation and one-bit mutation in this fixture. Ordinary hostile string copies allocate; no SQL bind, runtime factory/update or result cursor. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0016

[Lines 63–88](../../../../../tests/unit/sql_rows_records_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L88:sha256:7348843b125c88a6e39d0391996a7b6dac21982e62fef2e62c29e0d4f877d487
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove optional metadata preserves source identity and ordinary output, while codecs reject absent durable binding. |
| inputs / outputs | No arguments. Compile identical SELECT x twice with retention false/true, prepare a real unretained output row and test both record identity boundaries plus inspection. |
| invariants | Asserts equal source_sha256, empty versus retained binding, real row weight3, binding-tag denial for missing codec program and missing token metadata, and binding-tag inspector denial. Account/current token/output work are unchanged; pending ordinary command can still commit. |
| ownership | Ordinary and retained genuine compiler owners stay live. Account owns runtime/frame; PreparedBatch retains its genuine SQL/native owner independently of the runtime facade. Returned output values borrow the live token and supplied scratch; fixtures use ordinary arrays. |
| failure | Explicit local catches require ImageFailure(binding); any different carrier or absent refusal fails assertions or reaches main. This adds no production catch. |
| cost | Two finite cold fixture compiles, one real factory/update/output read, one header encode and three early-denial calls. No benchmark or universal fault result. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [src/recovery/sql_rows_records.cpp](../../../../../src/recovery/sql_rows_records.cpp) |

## B0017

[Lines 89–110](../../../../../tests/unit/sql_rows_records_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L110:sha256:dc97d591327d0478ffc35fa19572e8515efa4cd8012b1836af0cf172086bf3bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | For the selected backend, compare whole UINT64_MAX insertion/retraction frames and reject the listed protected forgeries. |
| inputs / outputs | Indexed backend flag -&gt; void after nullable UINT64_MAX insertion/retraction wire assertions. |
| invariants | This is a finite test helper/assertion body, not an execution receipt or proof for other inputs. |
| ownership | Fixture DTOs/expected bytes/maps use ordinary test storage; actual programs/runtimes/codecs use the explicitly created accounts and local owners. |
| failure | The exact catches/assertions in this body check expected refusals; all unhandled failures reach main. No production catch or recovery action is introduced. |
| cost | One cold compile/tree/runtime setup, two genuine output-prepared updates/commits and row encodes, delegated inspect_checks loops plus three protected semantic forgeries. Ordinary expected/hostile strings and actual native/codec owners allocate; no result cursor. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0018

[Lines 111–137](../../../../../tests/unit/sql_rows_records_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L137:sha256:dda10dea85fbd145c42d4f6bbf495c34a0070e15b3963be085991bdf3db16edc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise DISTINCT/EXISTS first support, positive-only numeric change and last loss; assert unit/count/constant rules and255-byte empty epochs for this fixture. |
| inputs / outputs | Indexed backend flag -&gt; void after the DISTINCT and EXISTS fixture assertion sequences. |
| invariants | This is a finite test helper/assertion body, not an execution receipt or proof for other inputs. |
| ownership | Fixture DTOs/expected bytes/maps use ordinary test storage; actual programs/runtimes/codecs use the explicitly created accounts and local owners. |
| failure | The exact catches/assertions in this body check expected refusals; all unhandled failures reach main. No production catch or recovery action is introduced. |
| cost | For each of two fixed SQL modes: cold compile/tree/runtime, three genuine prepared-output updates/commits and row encodes, first-frame inspection; DISTINCT adds two semantic forgeries. Actual native/codec storage and ordinary hostile strings allocate; no result cursor/full result snapshot. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0019

[Lines 138–160](../../../../../tests/unit/sql_rows_records_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L138-L160:sha256:c7fa711a3b26a257ef15006d2cb3aaf5a558b903bb6b20f496f7e9f49ffac4ba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check owned input string/source views, uint64 weights, the declared Input/Commit/Reject sequence, failed-feed state preservation and one typed input refusal. |
| inputs / outputs | No arguments -&gt; void after owned-input and fixed WAL-state assertions. |
| invariants | This is a finite test helper/assertion body, not an execution receipt or proof for other inputs. |
| ownership | Fixture DTOs/expected bytes/maps use ordinary test storage; actual programs/runtimes/codecs use the explicitly created accounts and local owners. |
| failure | The exact catches/assertions in this body check expected refusals; all unhandled failures reach main. No production catch or recovery action is introduced. |
| cost | Cold SQL binding, input encode/decode, fixed-header/decision encodes, ordered WalCursor feeds and two hostile controls. Actual frame/flat-array storage and ordinary strings allocate; no native runtime creation, update or result cursor. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0020

[Lines 161–161](../../../../../tests/unit/sql_rows_records_test.cpp#L161); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L161-L161:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |

## B0021

[Lines 162–167](../../../../../tests/unit/sql_rows_records_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L162-L167:sha256:c01a6365bf224ab4d1d06278ba5450bae8f25815debfeab09ef45d1a49dd458f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run wire/support assertions for both backends and the single opt-in/WAL assertion families. |
| inputs / outputs | No arguments; invokes exactly the assertion families listed here and returns0, or1 for an unexpected std::exception. |
| invariants | Passing this body establishes only those finite assertions when run with asserts enabled. |
| ownership | Local test fixtures unwind normally; the harness owns stdout/stderr. |
| failure | Expected helper catches are local; main prints unexpected exceptions and returns failure. |
| cost | Sum of called finite tests and report output; not a benchmark or production operation. |
| Design | [tests/unit/sql_rows_records_test.cpp](../../../../../tests/unit/sql_rows_records_test.cpp) |
