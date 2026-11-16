# `tests/reference/star_driver.cpp` — block usage map

[Source](../../../../../tests/reference/star_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `26993ba3545e28e148621abecb490f738cd5eec0fb84f9d554eb600c31a2b7f5`. 91 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/reference/star_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Execution only. The separate Python oracle joins the complete original CQ; · [reviewed contract](#b0001) |
| [B0002 · 17–29](../../../../../tests/reference/star_driver.cpp#L17) | Callable definition: FreeConnexTree original_tree(const Query& query,std::size_t center) | calls size, std::runtime_error, insert, push_back; returns tree; growth insert, push_back; 3 loop sites; source comment (unverified): // Execution only. The separate Python oracle joins the complete original CQ; · [reviewed contract](#b0002) |
| [B0003 · 30–47](../../../../../tests/reference/star_driver.cpp#L30) | Callable definition: Json snapshot(const st::Runtime& owner) | calls results, next, insert, storage::export_row; returns {{@ ,owner.sequence()},{@ ,owner.ready()},{@ ,io::write_relation(answer)},; growth insert, push_back; 3 loop sites · [reviewed contract](#b0003) |
| [B0004 · 48–58](../../../../../tests/reference/star_driver.cpp#L48) | Callable definition: Json apply(st::Runtime& owner,const PhysicalSetUpdate& update) | calls code, std::string; returns {{@ ,nullptr},{@ ,event.physical_changed},; {{@ ,error.code()}} · [reviewed contract](#b0004) |
| [B0005 · 59–83](../../../../../tests/reference/star_driver.cpp#L59) | Callable definition: Json evaluate(const Json& request) | calls io::read_document, at, dump, empty; returns {{@ ,request.at(@ )},{@ ,plan.dimension()},{@ ,plan.distinct_head()},; growth insert, push_back; 3 loop sites · [reviewed contract](#b0005) |
| [B0006 · 84–85](../../../../../tests/reference/star_driver.cpp#L84) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0006) |
| [B0007 · 86–91](../../../../../tests/reference/star_driver.cpp#L86) | Callable definition: int main() | calls std::getline, evaluate, Json::parse, dump; returns 0; 1; 1 loop sites · [reviewed contract](#b0007) |

## B0001

[Lines 1–16](../../../../../tests/reference/star_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:7bcc3a7d7066158c0b4807771f6c1fd90848102806ca65588d025cb28d693cc8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the genuine star/public document APIs and isolate the execution-only JSONL driver. |
| inputs / outputs | C++ includes, crown/JSON/star aliases and the execution-only comment; no request is consumed yet. |
| invariants | Expected relations and constraint decisions belong to the separate original-CQ Python/SQLite model, not this driver or the source-only native query. |
| ownership | Declarations acquire no runtime state; later evaluate() owns each independent Runtime. |
| failure | Missing declarations or incompatible interfaces fail compilation; this region installs no handler. |
| cost | Compile-time dependencies and static declarations only. |
| Design | [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py) |

## B0002

[Lines 17–29](../../../../../tests/reference/star_driver.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L29:sha256:39b1ac011d0c290680de8198f799cd6bfa99ca04f505ab17e15c17d7f32aeea7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a checked-upper test tree with the explicitly selected original center as native root. |
| inputs / outputs | Original Query and center occurrence index in; owning FreeConnexTree with one native node per original atom out. |
| invariants | Each node retains its complete variable scope and original occurrence ID; all noncenter nodes attach to the center. No minimum-height search or proof is claimed. |
| ownership | Borrows Query during construction; returned vectors/scopes/IDs are ordinary caller-owned test metadata. |
| failure | Out-of-range center throws std::runtime_error. Container allocation errors propagate; lower_tree subsequently validates structural admissibility. |
| cost | O(total atom terms plus atom count) construction with ordered-set insertion costs and allocations. |
| Design | [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0003

[Lines 30–47](../../../../../tests/reference/star_driver.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L47:sha256:122a6de8ba847a49e588a492ef581ef34a9336484cb1be227458dea9dbad4465
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one committed star result/source/state observation for independent comparison. |
| inputs / outputs | Const named Runtime in; JSON sequence/readiness, exact current rows, complete physical tables, H/scale/key gauges and cursor counters out. |
| invariants | Exhaust cursor before reading state. Duplicate output causes failure before set conversion can hide it. Source DTO covers every original physical table; metrics are observations, not expected values. |
| ownership | Cursor and native tuples retain original-account owners while open; exported Relations/JSON and source_snapshot() are ordinary owning test DTOs. |
| failure | A duplicate throws std::runtime_error; cursor/source/state/JSON resource or native errors propagate to main. RAII releases temporary readers. |
| cost | Full current enumeration, full physical source export and JSON allocation; no constant-delay or maintenance-cost inference. |
| Design | [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0004

[Lines 48–58](../../../../../tests/reference/star_driver.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L58:sha256:5c40bbb65750347ca83e0617ccd2ac1e11cd275c5b0883a14141a5d2e13fa1b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one real physical source event and preserve its typed native refusal in driver output. |
| inputs / outputs | Mutable Runtime plus PhysicalSetUpdate in; JSON error or changed/maintenance/source-route counters out. |
| invariants | Calls apply exactly once. Successful generic_aliases/native_crossings counters expose whether original generic query routes were maintained; counters are not synthesized expectations. |
| ownership | Borrows Runtime/update for the call; the runtime owns committed state and the returned JSON owns diagnostic values. |
| failure | Only crown::Error and resource::MemoryFailure become error-code JSON. Other failures propagate; no driver retry or replacement state is installed. |
| cost | Actual source and heavy/light maintenance plus JSON conversion; source work remains separate from star counters. |
| Design | [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp), [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py) |

## B0005

[Lines 59–83](../../../../../tests/reference/star_driver.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L83:sha256:b58a55bc8c9a8687217077e7bf2510fd8f8df104b545b515c7d1a63607fbd5c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and execute one source-bound empty-start star trace through the public APIs. |
| inputs / outputs | Parsed request containing document, original center, backend flag and events in; metadata, initial observation and every event/prefix observation out. |
| invariants | Rejects nonempty initial tables and invalid operation strings. Genuine lower_tree/admit bind the complete original CQ; each post-event state passes native inspection. Output records original atom count and empty source-only atom count separately. |
| ownership | Owns parsed original document, compiler plans, one Runtime and JSON observations for this request. No runtime or account is shared across input lines. |
| failure | Document/lowering/admission/inspection/JSON failures propagate. Expected apply refusals are reported by the narrower apply helper; no partial request JSON escapes main on failure. |
| cost | Cold parsing/lowering/admission and full per-prefix snapshots/invariant scans dominate this test driver; not an operational update benchmark. |
| Design | [tests/reference/star_driver.cpp](../../../../../tests/reference/star_driver.cpp), [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py), [include/crown/planner/star.hpp](../../../../../include/crown/planner/star.hpp), [include/crown/runtime/star.hpp](../../../../../include/crown/runtime/star.hpp) |

## B0006

[Lines 84–85](../../../../../tests/reference/star_driver.cpp#L84); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L85:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the driver-private helper namespace before its process entry point. |
| inputs / outputs | Namespace closing brace/comment; no request, output or query operation. |
| invariants | Helpers remain translation-unit local; the following main is the only process entry point. |
| ownership | No payload or account ownership changes. |
| failure | No executable failure branch. |
| cost | No runtime work. |
| Design | [tests/reference/star_driver.cpp](../../../../../tests/reference/star_driver.cpp) |

## B0007

[Lines 86–91](../../../../../tests/reference/star_driver.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L91:sha256:62dc99cb0b141b4faddbb95d4c81e0ea92240f3230390879bd88f5dfcd80a8f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Process JSONL requests and return a failing process status on an unexpected driver error. |
| inputs / outputs | stdin lines in; one compact JSON result per complete request on stdout, or diagnostic stderr and status1 out. |
| invariants | Each line is parsed/evaluated independently; status0 means this driver completed its requested execution, not that an external oracle comparison passed. |
| ownership | Line/parsed request/output temporaries own ordinary process memory; evaluate() owns native query state per line. |
| failure | The process boundary catches std::exception, emits its message and exits1; it does not retry a native epoch or swallow a comparison failure. |
| cost | Line reading, complete request execution, JSON serialization and stream I/O. |
| Design | [tests/reference/star_driver.cpp](../../../../../tests/reference/star_driver.cpp), [tests/integration/star_oracle.py](../../../../../tests/integration/star_oracle.py) |
