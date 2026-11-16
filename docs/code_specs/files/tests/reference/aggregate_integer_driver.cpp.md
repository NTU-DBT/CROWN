# `tests/reference/aggregate_integer_driver.cpp` — block usage map

[Source](../../../../../tests/reference/aggregate_integer_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `008c3dd24845fa0a64a1a7935502bdeb668461a7f6e3bcfd8bae33f5e6db1ad5`. 73 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/reference/aggregate_integer_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 14–18](../../../../../tests/reference/aggregate_integer_driver.cpp#L14) | Callable definition: std::string text(const crown::storage::InlineDecimal& value) | calls render, data; returns {buffer.data(), length} · [reviewed contract](#b0002) |
| [B0003 · 19–21](../../../../../tests/reference/aggregate_integer_driver.cpp#L19) | Explanatory comments or spacing. | source comment (unverified): // Observe only public numeric results. The Python side uses unbounded integers · [reviewed contract](#b0003) |
| [B0004 · 22–38](../../../../../tests/reference/aggregate_integer_driver.cpp#L22) | Callable definition: Json observe(const IntegerSum& sum, std::uint64_t count, std::uint8_t scale) | calls no_heap, value, average, fits_int64; guard assert(s04_alloc::calls == 0);; returns {{@ , text(total)}, {@ , count}, {@ , fits},; source comment (unverified): // Observe only public numeric results. The Python side uses unbounded integers · [reviewed contract](#b0004) |
| [B0005 · 39–39](../../../../../tests/reference/aggregate_integer_driver.cpp#L39) | Explanatory comments or spacing. |  |
| [B0006 · 40–61](../../../../../tests/reference/aggregate_integer_driver.cpp#L40) | Callable definition: Json evaluate(const Json& request) | calls at, assert, Json::array, push_back; guard assert(scale &lt;= 18);; returns {{@ , request.at(@ )}, {@ , std::move(trace)}}; growth push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 62–63](../../../../../tests/reference/aggregate_integer_driver.cpp#L62) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 64–73](../../../../../tests/reference/aggregate_integer_driver.cpp#L64) | Callable definition: int main() | calls std::getline, evaluate, Json::parse, dump; returns 0; 1; 1 loop sites · [reviewed contract](#b0008) |

## B0001

[Lines 1–13](../../../../../tests/reference/aggregate_integer_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Json = nlohmann::json;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the line-oriented numeric oracle driver separate from the zero-allocation arithmetic interval. |
| inputs / outputs | Trusted Python-generated JSON requests describe bounded scale and legal add/retract history; output is public numeric observations only. |
| invariants | The single-TU replacement new/delete hooks are test instrumentation, not runtime library code. Driver assertions are retained by the target’s -UNDEBUG; this is not an adversarial JSON/public aggregate admission API. |
| ownership | JSON, input/output strings and trace containers own ordinary test memory outside guarded scopes; IntegerSum/InlineDecimal are inline. |
| failure | Malformed requests can throw or assert; main reports exceptions as process failure. No SQL/group/transaction acceptance is established. |
| cost | Protocol parsing/serialization/trace storage may allocate proportional to encoded input/output; only explicitly scoped native arithmetic is denied operator-new requests. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0002

[Lines 14–18](../../../../../tests/reference/aggregate_integer_driver.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string text(const crown::storage::InlineDecimal& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one canonical native decimal to an owning test string after numeric observation. |
| inputs / outputs | Renders into41-byte stack buffer, then returns string of the produced length. |
| invariants | Canonical native decimals fit the supplied text_capacity; the test compares numeric value rather than fixed padding. |
| ownership | Return string owns copied bytes; no view into the stack escapes. |
| failure | Invalid/native render contract or string allocation failure propagates to main. This function is deliberately outside no_heap scopes. |
| cost | At most41 rendered bytes plus ordinary owning string construction; formatting/export allocation is not attributed to state arithmetic. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0003

[Lines 19–21](../../../../../tests/reference/aggregate_integer_driver.cpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Observe only public numeric results.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define an independent result interface that exposes no implementation limb representation. |
| inputs / outputs | Observation includes SUM text, external count, int64 fit/value and optional AVG text after every replacement. |
| invariants | Python recomputes full signed integers and rational rounding without reading Magnitude words or reusing native arithmetic. |
| ownership | The resulting JSON owns exported numeric observations; it contains no native state owner. |
| failure | A passing trace proves tested primitive outputs only; count/group/NULL/transaction/compiler acceptance stays separate. |
| cost | A complete observation is bounded numeric work plus allocating test JSON/text outside the scoped heap denial. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md) |

## B0004

[Lines 22–38](../../../../../tests/reference/aggregate_integer_driver.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json observe(const IntegerSum& sum,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture every numeric result under heap denial, then serialize it outside that interval. |
| inputs / outputs | Borrowed sum, coherent count and supported scale; yields SUM/count/fits/int64-or-null/AVG-or-null JSON. |
| invariants | AVG is skipped at count0, and int64_value is called only after fits_int64. No_heap covers value(), average(), range/value access and inline optional assignments; calls must remain zero after Scope disables hooks. |
| ownership | Native result values/options are local inline objects; returned JSON/string payload owns ordinary test storage. |
| failure | Any caught or uncaught allocation attempt causes recorded-call assertion or driver failure; numerical precondition assertions remain required. JSON/text allocation failure is reported normally outside guard. |
| cost | One bounded SUM/optional AVG conversion plus scalar checks; ordinary JSON/text result allocation follows separately. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

```text
s04_alloc::Scope no_heap(0);
    total = sum.value();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deny every replacement operator-new request during requested native numeric conversion. |
| inputs / outputs | Scope sets per-thread remaining=0 and calls=0, then value/AVG/fit extraction executes. |
| invariants | Replacement ordinary/array/aligned/nothrow new seams record attempts; Scope destructor disables but does not reset calls, so the following calls==0 assertion remains meaningful. Error/exception/runtime malloc is not a measured whole-process memory total. |
| ownership | Guard and all numeric temporary storage are stack/inline; serialization happens after it closes. |
| failure | First throwing new attempt throws bad_alloc; swallowed/nothrow attempts still leave nonzero calls and fail assertion. No nested Scope is permitted. |
| cost | Fixed test hook setup and bounded arithmetic; no account/grant or successful query-memory measurement is created. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0006

[Lines 40–61](../../../../../tests/reference/aggregate_integer_driver.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json evaluate(const Json& request)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay one trusted compressed contribution history and observe every prefix. |
| inputs / outputs | Request id/scale/operations produces initial-zero observation plus one observation per add/retract. |
| invariants | Driver asserts scale&lt;=18 after conversion and count bounds on each operation. It updates external count before arithmetic; valid per-value retractions/coherence are supplied by the generator, not independently checked against a row registry. |
| ownership | Owns one inline IntegerSum/count and allocating JSON trace; request is borrowed for synchronous replay. |
| failure | Bad request fields/conversions can throw; invalid arithmetic/count/heap assertions terminate the gate. This is a test driver, not a checked public mutation boundary. |
| cost | One fixed replace and bounded observation per encoded operation, never expanded multiplicity; trace/JSON allocation scales with operation count. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md) |

```text
s04_alloc::Scope no_heap(0);
      sum.replace(value, weight, erase);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject hidden C++ heap requests in each primitive state replacement. |
| inputs / outputs | After count assertions, one replace(value,weight,erase) runs with fail_after0. |
| invariants | The following calls==0 assertion checks attempts even if a nothrow/caught request would continue. Count/schema/trace work is outside this interval. |
| ownership | Scope and sum/product state are inline; no output owner is prepared inside this hook. |
| failure | Any allocating replace path fails the process (replace is noexcept) or the recorded-call assertion; no allocation retry/fallback is accepted. |
| cost | Fixed hook setup and fixed arithmetic per encoded operation; no dependence on expanded weight. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0007

[Lines 62–63](../../../../../tests/reference/aggregate_integer_driver.cpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L63:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in aggregate_integer_driver.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 64–73](../../../../../tests/reference/aggregate_integer_driver.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serve one numeric test case per JSON line until EOF with a process failure on exception. |
| inputs / outputs | Reads stdin lines, evaluates and writes one JSON response line per case; exits0 on complete input,1 on std::exception. |
| invariants | Outputs are observations, not private limbs or SQL/group state. Assertions are deliberately enabled by the build target; process success alone is not the Python oracle comparison. |
| ownership | Input/JSON/output buffers are ordinary test-owned allocations; no runtime account or query owner is created. |
| failure | Parsing/evaluation/serialization errors print what() to stderr and fail. Assertion/noexcept termination is not swallowed by the exception handler. |
| cost | Linear stream/serialization work in encoded bytes plus all evaluated arithmetic/observations; no internal time limit is enforced. |
| Design | [tests/integration/aggregate_integer_oracle.py](../../../../../tests/integration/aggregate_integer_oracle.py), [tests/reference/aggregate_integer_driver.cpp](../../../../../tests/reference/aggregate_integer_driver.cpp), [docs/aggregates.md §Required acceptance](../../../../aggregates.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |
