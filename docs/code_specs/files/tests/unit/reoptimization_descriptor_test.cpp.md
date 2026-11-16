# `tests/unit/reoptimization_descriptor_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_descriptor_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `db0ddd33e1946faf91718e6c592ee63e842354118f4cdd1b6406b9994042b1d3`. 92 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 9–17](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L9) | Callable definition: std::string unhex(std::string_view text) | calls check, push_back; guard const int digit=c&gt;='0' && c&lt;='9'?c-'0':c&gt;='a' && c&lt;='f'?c-'a'+10:-1;check(digit&gt;=0,"descriptor gold…; returns out; growth push_back; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 18–21](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L18) | Callable definition: template&lt;class Function&gt; void rejected(Function&& function,std::optional&lt;ImageFault&gt; expected={}) | calls function, check, fault, std::runtime_error; guard try{function();}catch(const ImageFailure& failure){check(!expected \|\| failure.fault()==*expected,"d… · [reviewed contract](#b0003) |
| [B0004 · 22–29](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L22) | Callable definition: PlanSelection selection(const detail::RetirementIntent& seed,bool sink=true,bool parent_plan=true,bool delivery=false) | calls sha256_fixed; returns out · [reviewed contract](#b0004) |
| [B0005 · 30–37](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L30) | Callable definition: void golden(const detail::RetirementIntent& seed,std::string_view bytes) | calls resource::MemoryAccount::create, selection, encode_plan_descriptor, check; guard check(bytes.size()==1529 && std::string_view(encoded.bytes.data(),encoded.bytes.size())==bytes,"nat… · [reviewed contract](#b0005) |
| [B0006 · 38–56](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L38) | Callable definition: void variants(const detail::RetirementIntent& seed) | calls resource::MemoryAccount::create, statistics, selection, encode_plan_descriptor; guard check(decoded.selection==input && decoded.compiler_artifact==artifact && encoded.bytes.get_allocato…; 4 loop sites · [reviewed contract](#b0006) |
| [B0007 · 57–66](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L57) | Callable definition: void corruption(std::string_view packet) | calls size, rejected, inspect_plan_descriptor, substr; 3 loop sites · [reviewed contract](#b0007) |
| [B0008 · 67–82](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L67) | Callable definition: void bindings_and_allocation(const detail::RetirementIntent& seed) | calls resource::MemoryAccount::create, selection, statistics, sha256_fixed; guard check(failed && account.statistics().current==before,"descriptor allocation failure changed receivi… · [reviewed contract](#b0008) |
| [B0009 · 83–83](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L83) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 84–92](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L84) | Callable definition: int main(int argc,char** argv) | calls check, detail::inspect_retirement_intent, unhex, session_file_test::contents; guard check(argc==3,"usage: reoptimization_descriptor RETIREMENT_GOLDEN DESCRIPTOR_GOLDEN");; returns 0; 1 · [reviewed contract](#b0010) |

## B0001

[Lines 1–8](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:39c9ddfb4a6927813eeafc7b1e4a647ead9a3c9a70b6560053e82c4d32b2fe6f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_descriptor_test.cpp: include "crown/recovery/plan_descriptor.hpp", "history_retirement_fixture.hpp"; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/reoptimization_descriptor_test.cpp](../../../../../tests/unit/reoptimization_descriptor_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–17](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string unhex(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a whitespace-tolerant lowercase hexadecimal test file into packet bytes. |
| inputs / outputs | Input text; skips ASCII space/tab/CR/LF and pairs lowercase or numeric hex digits into a string. |
| invariants | Uppercase hex and all nonhex characters are rejected; an odd final nibble is invalid. |
| ownership | Returns an owning standard string. |
| failure | check throws for nonhex input or trailing half-byte. |
| cost | Linear scan over input characters and one output byte per pair. |
| Design | [tests/unit/reoptimization_descriptor_test.cpp § std::string unhex(std::string_view text) (lines 9-17)](../../../../../tests/unit/reoptimization_descriptor_test.cpp) |

## B0003

[Lines 18–21](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> void rejected(Function&& function,std::optional<ImageFault> expected={}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that a descriptor action rejects with an optional expected ImageFault. |
| inputs / outputs | Callable input and optional fault; invokes once and catches only ImageFailure. |
| invariants | If an expected fault is set it must match; other exception types escape to main. |
| ownership | Borrows the callable through Function&& and invokes the named parameter as an lvalue; it retains no callable or descriptor bytes. |
| failure | Throws runtime_error if accepted, or check failure for wrong fault. |
| cost | One action invocation. |
| Design | [tests/unit/reoptimization_descriptor_test.cpp § template<class Function> void rejected(Function&& function,std::optional<ImageFault> expected={}) (lines 18-21)](../../../../../tests/unit/reoptimization_descriptor_test.cpp), [include/crown/recovery/plan_descriptor.hpp § descriptor codec API (lines 39-42)](../../../../../include/crown/recovery/plan_descriptor.hpp) |

## B0004

[Lines 22–29](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PlanSelection selection(const detail::RetirementIntent& seed,bool sink=true,bool parent_plan=true,bool delivery=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build synthetic PlanSelection metadata from the decoded retirement golden plus optional sink, predecessor-plan and delivery fields. |
| inputs / outputs | Inputs retirement seed and three booleans; copies predecessor/source/sink bindings, gives target a fixed physical hash, sets generation 8, physical sequence 11, command sequence 14, and optionally sets predecessor plan hash/delivery anchor. |
| invariants | Delivery is only generated when sink is present in variants; an invalid delivery-without-sink case is intentionally skipped there and tested by binding rejection. |
| ownership | Returns owning value copy of fixed metadata; no compiler validation is done here. |
| failure | Invalid combinations are left for encoder validation. |
| cost | Constant-size metadata copy and optional fields. |
| Design | [tests/unit/reoptimization_descriptor_test.cpp § PlanSelection selection(const detail::RetirementIntent& seed,bool sink=true,bool parent_plan=true,bool delivery=false) (lines 22-29)](../../../../../tests/unit/reoptimization_descriptor_test.cpp), [include/crown/recovery/plan_descriptor.hpp § PlanSelection (lines 12-20)](../../../../../include/crown/recovery/plan_descriptor.hpp), [tests/recovery/retirement/intent.hex](../../../../../tests/recovery/retirement/intent.hex) |

## B0005

[Lines 30–37](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void golden(const detail::RetirementIntent& seed,std::string_view bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one 1529-byte descriptor with the independent golden and check metadata/artifact decoding. |
| inputs / outputs | Inputs retirement seed and golden bytes; encodes the fixed literal artifact, inspects bytes, compares selection and opaque compiler_artifact, and checks image statistics. |
| invariants | The literal {"compiler_input":"golden-test-only"} is preserved as opaque bytes and is not replayed by a compiler. statistics.work==4*bytes is the codec's conservative work charge, not a measured count of memory reads. This helper has no allocation-denial scope or allocation-count assertion. |
| ownership | A local memory account funds encoded bytes; inspection result borrows compiler artifact bytes from the packet. |
| failure | check fails on size, bytes, decoded metadata, artifact bytes, or work mismatch; codec errors propagate. |
| cost | One encode and one inspect over the fixture packet. |
| Design | [tests/unit/reoptimization_descriptor_test.cpp § void golden(const detail::RetirementIntent& seed,std::string_view bytes) (lines 30-37)](../../../../../tests/unit/reoptimization_descriptor_test.cpp), [src/recovery/plan_descriptor.cpp § validate, statistics, encode and inspect (lines 20-114)](../../../../../src/recovery/plan_descriptor.cpp), [tests/recovery/reoptimization/descriptor-v1.hex](../../../../../tests/recovery/reoptimization/descriptor-v1.hex) |

## B0006

[Lines 38–56](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void variants(const detail::RetirementIntent& seed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise accepted combinations of optional descriptor metadata and exact byte/work/artifact grants. |
| inputs / outputs | Loops sink, parent-plan, delivery and switched booleans, skipping delivery without sink. Each accepted iteration performs normal encode and inspection under Scope deny(0), then exact-limit encode/inspect and three one-under limit attempts. |
| invariants | There are 12 accepted iterations: four without a sink and eight with a sink; switched adds last_switch_epoch with value zero. Each iteration owns both normal and exact-limit encodings, which are destroyed before the next iteration. Whole-account current usage is compared with baseline only after the loop. The source success diagnostic reports twelve, matching the loop. |
| ownership | Encoded descriptor is account-funded and iteration-local; inspect borrows its bytes; account outlives all descriptors. |
| failure | Normal inspection must return correctly with persistent covered-new denial active; this body does not separately assert calls or triggered. One-under encoded bytes, encoded work and inspected artifact-byte limits must report the named limit/work faults. Account current usage must equal baseline after the entire loop. |
| cost | 12 encodes and inspections, plus limit re-encodes/inspections per iteration; every codec pass is proportional to frame bytes. |
| Design | [tests/unit/reoptimization_descriptor_test.cpp § void variants(const detail::RetirementIntent& seed) (lines 38-56)](../../../../../tests/unit/reoptimization_descriptor_test.cpp), [src/recovery/plan_descriptor.cpp § validate, statistics, encode and inspect (lines 20-114)](../../../../../src/recovery/plan_descriptor.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp) |

## B0007

[Lines 57–66](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void corruption(std::string_view packet) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject every strict golden prefix and XOR-1 mutation at each golden byte, then reject resealed mutations at six fixed framing/selection offsets. |
| inputs / outputs | Input golden packet view; loops all cut lengths and byte positions, creating an ordinary string per bit flip; separately flips listed fixed offsets and recomputes integrity. |
| invariants | The test covers this finite packet and six offsets only. Resealing integrity does not confer semantic or compiler-admission authority. |
| ownership | Input packet is borrowed; each mutated copy is a temporary string. |
| failure | Every candidate must raise ImageFailure via rejected(). |
| cost | For packet length n, performs n strict-prefix attempts, n full-string copy/mutation attempts and six resealed full copies. Prefixes below the codec minimum of 932 bytes reject early; longer valid-magic prefixes hash before declared-size rejection. O(n²) is an aggregate copied/scanned-byte upper bound, not a claim that every prefix receives a full parse or hash. |
| Design | [tests/unit/reoptimization_descriptor_test.cpp § void corruption(std::string_view packet) (lines 57-66)](../../../../../tests/unit/reoptimization_descriptor_test.cpp), [src/recovery/plan_descriptor.cpp § validate, statistics, encode and inspect (lines 20-114)](../../../../../src/recovery/plan_descriptor.cpp), [tests/support/history_retirement_fixture.hpp § checksum (line 41)](../../../../../tests/support/history_retirement_fixture.hpp) |

## B0008

[Lines 67–82](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bindings_and_allocation(const detail::RetirementIntent& seed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject selected source/target/sink binding, generation, limit, and allocation failures while preserving retryability. |
| inputs / outputs | Builds a valid selection and mutates source hash, catalog, policy, generation, sink source, missing sink for delivery, switch epoch, and descriptor field limit; also denies first instrumented allocation then retries. |
| invariants | Exact expected faults are asserted only for cases that name one. Allocation denial must leave account current unchanged; successful retry must decode to the original selection. |
| ownership | Account owns any successful encoded bytes; temporary mutations are value copies. |
| failure | Malformed binding/limits must reject; bad_alloc must be observed and not leak receiving-account bytes. |
| cost | Eight metadata/limit cases, one denied allocation, and one encode/inspect retry. |
| Design | [tests/unit/reoptimization_descriptor_test.cpp § void bindings_and_allocation(const detail::RetirementIntent& seed) (lines 67-82)](../../../../../tests/unit/reoptimization_descriptor_test.cpp), [src/recovery/plan_descriptor.cpp § validate, statistics, encode and inspect (lines 20-114)](../../../../../src/recovery/plan_descriptor.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp) |

## B0009

[Lines 83–83](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L83:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_descriptor_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_descriptor_test.cpp](../../../../../tests/unit/reoptimization_descriptor_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 84–92](../../../../../tests/unit/reoptimization_descriptor_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load independent retirement/descriptor hex files and run the golden, variant, corruption, and binding campaigns. |
| inputs / outputs | Requires two paths; unhexes retirement intent and descriptor, inspects retirement intent to seed selection, then runs each helper. |
| invariants | Runs codec framing/metadata tests using the opaque golden-only artifact; compiler semantic admission is separate. variants executes 12 accepted combinations including last_switch_epoch presence; the source success diagnostic now reports twelve, matching that finite fixture count. |
| ownership | Main owns decoded strings and seed; helpers borrow the packet. |
| failure | Requires exactly two paths; exceptions print and return 1. |
| cost | Reads and converts two fixture files, then executes finite campaigns bounded by the 1529-byte golden. |
| Design | [tests/unit/reoptimization_descriptor_test.cpp § int main(int argc,char** argv) (lines 84-92)](../../../../../tests/unit/reoptimization_descriptor_test.cpp), [tests/recovery/retirement/intent.hex](../../../../../tests/recovery/retirement/intent.hex), [tests/recovery/reoptimization/descriptor-v1.hex](../../../../../tests/recovery/reoptimization/descriptor-v1.hex), [CMakeLists.txt § reoptimization_descriptor registration (lines 732-737)](../../../../../CMakeLists.txt) |
