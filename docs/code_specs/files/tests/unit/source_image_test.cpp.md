# `tests/unit/source_image_test.cpp` — block usage map

[Source](../../../../../tests/unit/source_image_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7dfac8ce4649a0edbb29e1810d3f139570c967ce181ba4066b275f3f49e100b0`. 127 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/source_image_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–18](../../../../../tests/unit/source_image_test.cpp#L15) | Callable definition: void check(bool condition,const char* message) | calls std::runtime_error; guard void check(bool condition,const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 19–26](../../../../../tests/unit/source_image_test.cpp#L19) | Callable definition: template&lt;class F&gt; void refusal(F action,std::string_view code={}) | calls action, check, empty, code; guard catch(const Error& e){failed=true;check(code.empty()\|\|e.code()==code,"unexpected Error category");} · [reviewed contract](#b0003) |
| [B0004 · 27–30](../../../../../tests/unit/source_image_test.cpp#L27) | Callable definition: Catalog catalog() | calls ; returns {1,{{@ ,{{@ ,ScalarType::int64},{@ ,ScalarType::string}}}, · [reviewed contract](#b0004) |
| [B0005 · 31–35](../../../../../tests/unit/source_image_test.cpp#L31) | Callable definition: PhysicalPlan plan(bool indexed,std::optional&lt;std::uint64_t&gt; scalar_limit={}) | calls s04_runtime::options, planner::lower_tree, catalog; returns planner::lower_tree(catalog(),Query{},FreeConnexTree{},options) · [reviewed contract](#b0005) |
| [B0006 · 36–36](../../../../../tests/unit/source_image_test.cpp#L36) | Callable definition: Row row(std::int64_t id,std::string text=std::string("a\0b",3)) | calls std::string, std::move; returns {Value{id},Value{std::move(text)}} · [reviewed contract](#b0006) |
| [B0007 · 37–39](../../../../../tests/unit/source_image_test.cpp#L37) | Callable definition: Relation exported(const runtime::physical::SourceImage& image,std::size_t table=0) | calls at, insert, storage::export_row, values; returns out; growth insert; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 40–47](../../../../../tests/unit/source_image_test.cpp#L40) | Callable definition: void same_account(const runtime::physical::SourceImage& image) | calls account, statistics, check, get_allocator; guard check(image.tables.get_allocator().account().statistics().owner==id,"image directory has foreign ac…; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 48–75](../../../../../tests/unit/source_image_test.cpp#L48) | Callable definition: void epochs(bool indexed) | calls owner, plan, source_image, check; guard auto empty=owner.source_image();check(empty.sequence==0&&empty.tables.size()==2,"empty capture meta…; growth insert · [reviewed contract](#b0009) |
| [B0010 · 76–93](../../../../../tests/unit/source_image_test.cpp#L76) | Callable definition: void indexed_lease() | calls owner, plan, payload, apply; guard try{auto image=pending.source_image();check(image.tables\[0\].size()==3,"repeated after-image differs…; growth insert; 1 loop sites; source comment (unverified): // Each explicit image has a fresh selected grant, but all captures inside · [reviewed contract](#b0010) |
| [B0011 · 94–116](../../../../../tests/unit/source_image_test.cpp#L94) | Callable definition: void allocation_cuts(bool indexed,bool unpublished) | calls plan, apply, row, make; guard check(allocations&gt;0,"capture control observed no allocations");; returns owner; growth insert, make_unique; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 117–120](../../../../../tests/unit/source_image_test.cpp#L117) | Callable definition: void lifetime() | calls owner, plan, apply, row; guard check(exported(image)==Relation{row(9,"owned")},"image payload did not survive runtime teardown");s…; returns owner.source_image(); growth insert · [reviewed contract](#b0012) |
| [B0013 · 121–122](../../../../../tests/unit/source_image_test.cpp#L121) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;runtime::physical::SourceImage&gt;);; source comment (unverified): // namespace · [reviewed contract](#b0013) |
| [B0014 · 123–127](../../../../../tests/unit/source_image_test.cpp#L123) | Callable definition: int main() | calls lifetime, epochs, allocation_cuts, indexed_lease; returns 0; 1; 1 loop sites · [reviewed contract](#b0014) |

## B0001

[Lines 1–14](../../../../../tests/unit/source_image_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:cfe1dd07d9be2dde656717cfec63f5f0db9a5dbf29f5f0533d2553f47ef89415
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import real source capture plus test-only finite indexed and allocation-denial support. |
| inputs / outputs | Includes/private aliases and counted successful assertions. |
| invariants | Fault replacement new is linked only into this test TU; no runtime implementation or expected source image is faked. |
| ownership | Ordinary fixture/export data surrounds independently funded native owners; test counter is serial process state. |
| failure | Compile/link failures remain ordinary; authoring is not native acceptance. |
| cost | Compile-time setup; actual tests run later through main. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0002

[Lines 15–18](../../../../../tests/unit/source_image_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L18:sha256:2ff4e55fa17e5503ffe33b650881e8f1712a3d196ef4f0b5fe829bcfc0effdf1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert source-image expectations independently of build assertion settings. |
| inputs / outputs | Boolean and static message in; increments checks on success. |
| invariants | NDEBUG cannot erase a failed condition; false does not continue the suite. |
| ownership | Inline test counter and borrowed static message; no production mutation. |
| failure | False throws runtime_error for main to report. |
| cost | One branch/increment; failure diagnostic construction only on failure. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp) |

## B0003

[Lines 19–26](../../../../../tests/unit/source_image_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L26:sha256:42b72a03cd7e265508dd76408a338d11ea7a96f9cf8a69e815440d4930012443
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one source-image operation to refuse in its requested diagnostic domain. |
| inputs / outputs | Callable plus optional code in; runs once and asserts recognized Error/IndexFailure/MemoryFailure. |
| invariants | A specified code cannot accept another domain. MemoryFailure is accepted only when no specific code was requested. Missing refusal fails; this is no production retry policy. |
| ownership | Callable/diagnostic borrowed only during test invocation. |
| failure | Unexpected standard exceptions escape to main; wrong/missing typed refusal throws assertion failure. |
| cost | One actual operation plus failure-code checks; no retries hidden inside helper. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0004

[Lines 27–30](../../../../../tests/unit/source_image_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L30:sha256:f4caa30306964502b7d27474a989f76698021c3bb2fe5133a5b5a11a15e85b9e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create full physical schema including an unused source for image coverage. |
| inputs / outputs | No input; Catalog with rows(id,text) and unused(id) out. |
| invariants | The unused source must appear in images although the coordinator query is constant. |
| ownership | Ordinary owning cold Catalog DTO. |
| failure | Ordinary allocation failure propagates. |
| cost | Fixed small metadata construction. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0005

[Lines 31–35](../../../../../tests/unit/source_image_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L35:sha256:8d28e371bdc6b27e5edbe37bab8d5b2bfb276534d047a8617f7fb5024370080b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a genuine zero-atom coordinator under reference or finite indexed storage. |
| inputs / outputs | Indexed flag and optional indexed scalar-byte ceiling in; validated source PhysicalPlan out. |
| invariants | Uses original two-table catalog with Query{} and FreeConnexTree{}. Optional scalar limit is supplied only by indexed_lease, so indexed_storage is present. No original-query tree certificate is fabricated. |
| ownership | Owns ordinary options and returned genuine cold plan; runtime later opens its original account. |
| failure | Existing lowering/admission/allocation errors propagate. |
| cost | Cold validation/lowering/identity work with fixed schema, plus ordinary metadata ownership. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0006

[Lines 36–36](../../../../../tests/unit/source_image_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:3ca8008ac5397abbf9f25676635e93548bab51b7831990601cb7ba3b28641d79
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct full exact source rows including embedded NUL payload. |
| inputs / outputs | int64 id and owning text defaulting to three bytes a-NUL-b in; ordinary Row out. |
| invariants | Full source row retains text width; no C-string truncation or native projection is used. |
| ownership | Row owns integer and moved string payload. |
| failure | Ordinary vector/string allocation errors propagate. |
| cost | Row descriptor construction plus exact payload ownership/copy at call sites. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp) |

## B0007

[Lines 37–39](../../../../../tests/unit/source_image_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L39:sha256:d59bd09d35071191296c20dd4db27a326089e7ddde7ba42f12fcb6b388b40933
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one captured physical table for equality with an independently constructed source set. |
| inputs / outputs | SourceImage and table index in; full ordinary Relation out. |
| invariants | Compares full rows, not fallback query answers. This set helper does not independently reject duplicate image rows; the source storage itself supplies set rows. |
| ownership | Image stays borrowed while exported ordinary rows own their payloads. |
| failure | Out-of-range/export/allocation errors propagate. |
| cost | Full tuple export and ordered set insertion per image row, explicitly test-boundary work. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp) |

## B0008

[Lines 40–47](../../../../../tests/unit/source_image_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L47:sha256:b742cb7d1b6bfe4078ac6112dcfd638d97581494c430aced0a92181945d1e106
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check original account identity through every produced image ownership layer. |
| inputs / outputs | SourceImage in; verifies program owner, directory allocator, row allocator and tuple layout owner identities. |
| invariants | No nested directory/row/tuple may silently use an unrelated account. This identity check is distinct from byte-total or universal-allocation coverage. |
| ownership | Borrows image/program and inline statistics; no exported native views escape. |
| failure | Any owner mismatch fails check; no account is repaired. |
| cost | O(tables + captured tuples) identity observations. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp) |

## B0009

[Lines 48–75](../../../../../tests/unit/source_image_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L75:sha256:97b9283b421a554b516bddda738dece400a77d7be484c6a3572c8ed44897ba0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise committed/private epochs, noops, row/work refusal and retained after-image ownership. |
| inputs / outputs | Backend flag in; serial native insert/erase/rollback/commit plus capture assertions. |
| invariants | Empty image has all tables. Public read is busy during prepare; pending work/row refusals leave token active. Pending after-image is real unpublished insertion/deletion state; rollback preserves committed epoch but cannot invalidate its owning image. Noop commits advance source sequence; unused tables remain captured. Committed capture refusal preserves owner and invariants. |
| ownership | Independent image owners survive source token rollback; private token owns one real source/logical journal until closed. Tests are serial, not concurrent readers/writers. |
| failure | Named runtime_busy/source_image_* errors are required. Any unexpected state/account/output mismatch fails the process. |
| cost | Finite full captures, original source updates and invariant checks under both backends; no constant-time/image reuse claim. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/source_images.md](../../../../source_images.md) |

## B0010

[Lines 76–93](../../../../../tests/unit/source_image_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L93:sha256:7da8e164c04628c7f665ce4fb621b1262190951d1704c7bb4abdb132a2fa4649
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discriminate fresh selected image grants from the single retained indexed update allowance. |
| inputs / outputs | One indexed owner with 8,192 scalar-byte ceiling, three 256-byte rows and repeated pending captures. |
| invariants | At least one capture must succeed and a later one must exhaust storage_work_limit within 100 attempts. Each call has a fresh SourceImageLimits, but resumed calls spend the same five-domain lease. Refusal leaves pending active; rollback restores source/sequence and subsequent fresh committed capture succeeds. |
| ownership | One native owner/token, temporary owning images retired each iteration; no second source owner or parallel operation. |
| failure | Only the expected Error/IndexFailure storage_work_limit is accepted; no exhaustion or prematurely closed token fails assertions. |
| cost | Finite repeated full copies until cumulative native lease exhaustion; printed count is actual execution evidence only. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [docs/source_images.md](../../../../source_images.md) |

## B0011

[Lines 94–116](../../../../../tests/unit/source_image_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L116:sha256:83910c41744e276158df9a285c1347afb8e1b964f680eefe8423c51f1a90bcfc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep authenticated persistent allocation denial across committed and pending image capture. |
| inputs / outputs | Backend and private-after-state flag in; successful control counts allocation attempts, each prefix is denied in a reconstructed independent owner. |
| invariants | Every cut requires both failure and s04_alloc::triggered. Pending refusal must retain active token; same-token retry captures both rows before rollback. All cuts leave committed source/sequence ready and unchanged. The seam covers C++ new, not arbitrary libc allocations or a universal fault proof. |
| ownership | Nonnested test-only thread-local denial scope stays active through attempted capture cleanup, then retires before recovery observations. Every setup owns its own native account. |
| failure | catch(...) records attempted failure only; authentication/state checks prevent an unrelated exception from passing. Retry failure propagates; zero-allocation control fails. |
| cost | One successful control and one setup/denial/verification (plus pending retry) per observed allocation across both backends and both capture modes. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0012

[Lines 117–120](../../../../../tests/unit/source_image_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L120:sha256:c4cf1f4ff2ca13b4e728bd8f531391d1e4c262c733261eec5c98eddb335a1dfb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify captured native payload survives complete source-runtime teardown. |
| inputs / outputs | Local runtime returns an owning image; compare row9/owned and nested account identities afterward. |
| invariants | Neither source table/journal nor facade lifetime may be required by captured payloads. |
| ownership | Returned image retains original program/account/layout/tuple owners independently. |
| failure | Dangling/mismatched output or account fails; construction/export errors propagate. |
| cost | One owner/update/deep capture plus post-destruction full export/identity check. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0013

[Lines 121–122](../../../../../tests/unit/source_image_test.cpp#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L122:sha256:7435407ba49a5054fc72a840aa791f4d552961eb02daab7b1976262e52b7919a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close private test helpers and enforce the public image move contract at compile time. |
| inputs / outputs | Namespace delimiter and is_nothrow_move_constructible static assertion. |
| invariants | Moving a SourceImage must satisfy its declared nonthrowing ownership boundary; no semantic/runtime pass follows from this trait alone. |
| ownership | No live owner created. |
| failure | Trait mismatch fails compilation. |
| cost | Compile-time check only. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp) |

## B0014

[Lines 123–127](../../../../../tests/unit/source_image_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L123-L127:sha256:2e76dff09dcc9eda35f8575c7d49e614b9b6be4aededde7cb954e3880dc85ca1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the finite source-image semantics/lease/lifetime/allocation test cohort. |
| inputs / outputs | Process runs lifetime, both-backend epochs and committed/pending allocation sweeps, then indexed lease test; reports actual checks. |
| invariants | Success text is emitted only after actual complete execution. Standard exception yields process failure; no production recovery path or full-suite guarantee. |
| ownership | Tests run serially with independent owner scopes; no shared query or thread scheduling is introduced. |
| failure | std::exception diagnostic returns one; uncaught nonstandard failures remain failures. |
| cost | Sum of explicit finite suites and external diagnostic formatting. |
| Design | [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/source_images.md](../../../../source_images.md) |
