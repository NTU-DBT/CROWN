# `tests/support/ranking_exception_support.hpp` — block usage map

[Source](../../../../../tests/support/ranking_exception_support.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `67d4f88d9e76a49a49d34cb7a01b719293f9b88de38e6de8f1e28b61c27705eb`. 53 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/support/ranking_exception_support.hpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Single test translation unit only. This older seam covers ordinary new/new\[\]; · [reviewed contract](#b0001) |
| [B0002 · 17–17](../../../../../tests/support/ranking_exception_support.hpp#L17) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t n) | calls std::malloc; returns p; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../tests/support/ranking_exception_support.hpp#L18) | Explanatory comments or spacing. | source comment (unverified): // Caller bounds positions below 100000; use one uncopied, nonnested lexical guard. · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../tests/support/ranking_exception_support.hpp#L19) | Type/record definition: struct Fault | source comment (unverified): // Caller bounds positions below 100000; use one uncopied, nonnested lexical guard. · [reviewed contract](#b0004) |
| [B0005 · 20–20](../../../../../tests/support/ranking_exception_support.hpp#L20) | declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |
| [B0006 · 21–21](../../../../../tests/support/ranking_exception_support.hpp#L21) | Callable definition: auto metadata(const ws::Metadata& m) | calls ; returns std::tuple{m.attempts,m.committed,m.aborted,m.selected,m.complete,m.aborted_selected,m.truncated,m.… · [reviewed contract](#b0006) |
| [B0007 · 22–22](../../../../../tests/support/ranking_exception_support.hpp#L22) | Callable definition: auto stamp(const ws::Stamp& s) | calls ; returns std::tuple{s.owner,s.committed_epoch,s.interval_start_epoch,s.reset_generation,s.configuration_gene… · [reviewed contract](#b0007) |
| [B0008 · 23–23](../../../../../tests/support/ranking_exception_support.hpp#L23) | Callable definition: auto memory(const ws::Memory& m) | calls ; returns std::tuple{m.object_bytes,m.descriptors_bytes,m.committed_bytes,m.attempt_bytes,m.previous_bytes,m.… · [reviewed contract](#b0008) |
| [B0009 · 24–24](../../../../../tests/support/ranking_exception_support.hpp#L24) | Callable definition: template&lt;class T&gt; bool same(std::span&lt;const T&gt; a,std::span&lt;const T&gt; b) | calls size, std::equal, begin, end; returns a.size()==b.size() && std::equal(a.begin(),a.end(),b.begin()) · [reviewed contract](#b0009) |
| [B0010 · 25–34](../../../../../tests/support/ranking_exception_support.hpp#L25) | Callable definition: void same_workload_complete(const ws::Snapshot& a,const ws::Snapshot& b) | calls c02_test::check, plan, physical_sha256, stamp; guard c02_test::check(a.plan().physical_sha256()==b.plan().physical_sha256() && stamp(a.stamp())==stamp(b… · [reviewed contract](#b0010) |
| [B0011 · 35–46](../../../../../tests/support/ranking_exception_support.hpp#L35) | Callable definition: std::vector&lt;std::string&gt; result_image(const crown::planner::ranking::Result& result) | calls selected, structural_key, scores, push_back; returns out; growth push_back; 5 loop sites · [reviewed contract](#b0011) |
| [B0012 · 47–47](../../../../../tests/support/ranking_exception_support.hpp#L47) | Closes surrounding scope/type. |  · [reviewed contract](#b0012) |
| [B0013 · 48–48](../../../../../tests/support/ranking_exception_support.hpp#L48) | Definitions sharing source lines: void* operator new(std::size_t n) / void* operator new\[\](std::size_t n) | calls allocate; returns allocate(n); allocate(n); growth allocate, new · [reviewed contract](#b0013) |
| [B0014 · 49–49](../../../../../tests/support/ranking_exception_support.hpp#L49) | Callable definition: void* operator new(std::size_t n,const std::nothrow_t&) noexcept | calls allocate; returns allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0014) |
| [B0015 · 50–50](../../../../../tests/support/ranking_exception_support.hpp#L50) | Callable definition: void* operator new\[\](std::size_t n,const std::nothrow_t&) noexcept | calls ; returns allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0015) |
| [B0016 · 51–51](../../../../../tests/support/ranking_exception_support.hpp#L51) | Definitions sharing source lines: void operator delete(void* p) noexcept / void operator delete\[\](void* p) noexcept | calls std::free · [reviewed contract](#b0016) |
| [B0017 · 52–52](../../../../../tests/support/ranking_exception_support.hpp#L52) | Definitions sharing source lines: void operator delete(void* p,std::size_t) noexcept / void operator delete\[\](void* p,std::size_t) noexcept | calls std::free · [reviewed contract](#b0017) |
| [B0018 · 53–53](../../../../../tests/support/ranking_exception_support.hpp#L53) | Definitions sharing source lines: void operator delete(void* p,const std::nothrow_t&) noexcept / void operator delete\[\](void* p,const std::nothrow_t&) noexcept | calls std::free · [reviewed contract](#b0018) |

## B0001

[Lines 1–16](../../../../../tests/support/ranking_exception_support.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
thread_local std::ptrdiff_t fail_after
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the older ordinary-new ranking fault seam's per-thread calibration state. |
| inputs / outputs | fail_after&lt;0 permits requests, positive counts down, zero persistently denies; allocations increments on every covered ordinary new call, triggered marks injection reached. |
| invariants | This header defines replacement functions without an include guard and must appear in one test translation unit only. It does not replace aligned new forms, raw malloc/realloc, placement new, other-thread state or MemoryAccount accounting. |
| ownership | Thread-local scalar state, no account/payload ownership. |
| failure | Configured denial throws through allocate; size counter has no saturation guard and test caller bounds calibration below 100,000. |
| cost | Fixed per-call counter/checks even outside Fault; counts failed attempts too, not bytes/live/frees/peak/timings. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–17](../../../../../tests/support/ranking_exception_support.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count and fault ordinary ranking-test new before its malloc-backed request. |
| inputs / outputs | Increments allocations, persistently throws at fail_after==0, decrements positive fail_after, otherwise returns malloc(n?n:1) or throws on null. |
| invariants | The failed position is counted. triggered distinguishes configured zero from an underlying malloc-null. No aligned-new or libc-failure injection coverage is implied. |
| ownership | Caller owns compatible raw storage; global replacement delete frees it. No query-account handle is created. |
| failure | bad_alloc propagates for injection/actual malloc null; no new_handler retry or automatic disarm. |
| cost | One scalar calibration step and real malloc request per covered ordinary new; actual size/framing are not measured. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 18–18](../../../../../tests/support/ranking_exception_support.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L18:sha256:447710770ebf95eada987e876d9da59a738e840ffc3b3a0d084a7c5bfd696951
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Caller bounds positions below 100000; use one uncopied, nonnested lexical guard. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 19–19](../../../../../tests/support/ranking_exception_support.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fault {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Temporarily install one persistent ordinary-new denial point for the normalized ranking sweep. |
| inputs / outputs | Constructor clears triggered and casts supplied size_t position to ptrdiff_t fail_after; destructor restores -1 without resetting allocations. |
| invariants | Actual caller guards count&lt;100,000 before constructing positions, so they fit the supported host ptrdiff_t. This older helper does not range-check arbitrary positions. No copy/move is deleted; copying/rvalue copying is possible but caller protocol is one nonnested lexical guard. |
| ownership | Controls shared thread-local state only; no independent allocation budget, owner or byte accounting. |
| failure | Destructor disarms while unwinding. Invalid out-of-range direct input is outside the finite test precondition; no new recovery added. |
| cost | Fixed cast/flag stores, no buffer allocation by guard; remaining-zero persists through all covered new attempts until scope exit. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 20–20](../../../../../tests/support/ranking_exception_support.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L20:sha256:fae15d1bcb60d6f8d0aeaa16ae88fe8b59c277b3cd88188819be7a5f4ad1b93c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_exception_support.hpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 21–21](../../../../../tests/support/ranking_exception_support.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto metadata(const ws::Metadata& m)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project all current workload lifecycle/protocol metadata into an owning numeric tuple. |
| inputs / outputs | Copies attempts/committed/aborted/selected/complete, aborted-selected/truncated/committed-truncated, guards/detail actions/cleared/merged cells and all saturation/descriptor/protocol/ordinal flags. |
| invariants | Tuple values do not retain a Metadata reference or row payload; this projection is a test comparator, not source/commit authority. |
| ownership | Tuple owns inline IDs/integers/booleans only; input snapshot struct is borrowed during construction. |
| failure | No explicit handler or allocation on valid numeric tuple construction. |
| cost | Fixed field copies; no descriptor/row/account-ledger scan. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 22–22](../../../../../tests/support/ranking_exception_support.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto stamp(const ws::Stamp& s)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project all workload owner/interval identity metadata into an owning numeric tuple. |
| inputs / outputs | Copies owner, committed epoch, interval start, reset/configuration generation, segment, format and saturation flags. |
| invariants | Same stamp alone does not imply equal counters/modes/pending/history; workload comparison checks those separately. |
| ownership | Tuple owns inline IDs/integers/booleans only; input snapshot struct is borrowed during construction. |
| failure | No explicit handler or allocation on valid numeric tuple construction. |
| cost | Fixed field copies; no descriptor/row/account-ledger scan. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 23–23](../../../../../tests/support/ranking_exception_support.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto memory(const ws::Memory& m)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project workload component-capacity accounting for exact regression comparison. |
| inputs / outputs | Copies object/descriptor/committed/attempt/previous/routes capacity bytes and retained_payload_bytes. |
| invariants | These are component logical payload capacities, not whole-query requested bytes, allocator framing, detached snapshots, process memory or allocation timings. |
| ownership | Tuple owns inline IDs/integers/booleans only; input snapshot struct is borrowed during construction. |
| failure | No explicit handler or allocation on valid numeric tuple construction. |
| cost | Fixed field copies; no descriptor/row/account-ledger scan. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 24–24](../../../../../tests/support/ranking_exception_support.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> bool same(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare numeric spans without exporting or copying their arrays. |
| inputs / outputs | Checks equal sizes then std::equal over all elements until first mismatch. |
| invariants | Span owners must remain stable; equality of a partial field alone is not complete snapshot/proof equivalence. |
| ownership | Borrows both arrays; bool result owns nothing. |
| failure | Element equality requirements are supplied by current numeric Descriptor/Cell types; no local catch or failure injection. |
| cost | O(compared elements), with Cell equality including fixed histogram members; no array/key allocation. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 25–34](../../../../../tests/support/ranking_exception_support.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void same_workload_complete(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require unchanged complete public workload snapshot fields after an attempted operation. |
| inputs / outputs | Compares plan hash, full stamps/options/modes/current+previous descriptors/cells/metadata/capacity accounting, pending/history flags, prior interval bounds and detail availability; fails through fixture check. |
| invariants | Reads detached snapshot facts; it does not compare live row/account-ledger state, which test callers verify separately. Equality is on exposed content, not shared-pointer identity or an actual-owner freshness grant. |
| ownership | Inputs are borrowed owning snapshots; no snapshot graph clone. Numeric tuple projections copy values only. |
| failure | Mismatch throws runtime_error outside the intended measured/fault invocation in actual callers. Existing allocation counters may observe unrelated diagnostic construction when enabled. |
| cost | Linear descriptor/current/previous Cell comparisons and fixed metadata/hash fields; no owning row export or new query capture within this helper itself. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 35–46](../../../../../tests/support/ranking_exception_support.hpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::string> result_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the ranking facts exercised by fault tests into independent ordinary byte strings. |
| inputs / outputs | Copies selected structural key; every score key/height/numerator/denominator/slots, occurrence/table depth reproduction, populations/visible availability, slot terms and optional modeled plan physical SHA. |
| invariants | This selected-field image is not a complete serialized Result: request/evidence/account/cache/state/usage are not all included. Caller separately checks retained usage/proofs/owner/workload. Raw strings cannot manufacture ranking/proof authority. |
| ownership | Returned vector and strings own independent ordinary memory, including key/decimal text copies. Typed candidate/Result handles are only borrowed during export; structural key text is not assumed shared. |
| failure | String/vector formatting/allocation failures propagate; actual caller creates/compares images after fault guard exits. |
| cost | O(all score/reproduction records plus copied text bytes), vector growth and std::to_string allocations; plan image here is only its stored hash, not full physical JSON. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 47–47](../../../../../tests/support/ranking_exception_support.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L47:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_exception_support.hpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 48–48](../../../../../tests/support/ranking_exception_support.hpp#L48); `inline-cluster`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n){return allocate(n);}void* operator new[](std::size_t n){return allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary throwing global new/new\[\] pair. |
| inputs / outputs | Forwards raw size to allocate; returns raw storage or propagates bad_alloc. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; this older family covers ordinary forms only; aligned/default-library/placement/raw-malloc calls are not observed by this helper. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Configured denial, arithmetic overflow where applicable and actual allocator failure propagate; no new_handler retry is added. |
| cost | Fixed forwarding plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 49–49](../../../../../tests/support/ranking_exception_support.hpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n,const std::nothrow_t&) noexcept{try{return allocate(n);}catch(...){return nullptr;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary nothrow global new overload. |
| inputs / outputs | Forwards raw size to allocate; catches every exception and returns nullptr. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; this older family covers ordinary forms only; aligned/default-library/placement/raw-malloc calls are not observed by this helper. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Nothrow catch is required by its noexcept/null contract; it does not report engine recovery or retry. |
| cost | Fixed forwarding and exception-to-null mapping on failure plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 50–50](../../../../../tests/support/ranking_exception_support.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n,const std::nothrow_t&) noexcept{try{return allocate(n);}catch(...){return nullptr;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary nothrow global new overload. |
| inputs / outputs | Forwards raw size to allocate; catches every exception and returns nullptr. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; this older family covers ordinary forms only; aligned/default-library/placement/raw-malloc calls are not observed by this helper. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Nothrow catch is required by its noexcept/null contract; it does not report engine recovery or retry. |
| cost | Fixed forwarding and exception-to-null mapping on failure plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 51–51](../../../../../tests/support/ranking_exception_support.hpp#L51); `inline-cluster`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p) noexcept{std::free(p);}void operator delete[](void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete/delete\[\] pair for the executable allocation seam. |
| inputs / outputs | Forwards pointer to std::free; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 52–52](../../../../../tests/support/ranking_exception_support.hpp#L52); `inline-cluster`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t) noexcept{std::free(p);}void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete/delete\[\] pair for the executable allocation seam. |
| inputs / outputs | Forwards pointer to std::free; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 53–53](../../../../../tests/support/ranking_exception_support.hpp#L53); `inline-cluster`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,const std::nothrow_t&) noexcept{std::free(p);}void operator delete[](void* p,const std::nothrow_t&) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete/delete\[\] pair for the executable allocation seam. |
| inputs / outputs | Forwards pointer to std::free; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/ranking_exception_support.hpp](../../../../../tests/support/ranking_exception_support.hpp), [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |
