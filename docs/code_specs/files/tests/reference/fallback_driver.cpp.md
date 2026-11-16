# `tests/reference/fallback_driver.cpp` — block usage map

[Source](../../../../../tests/reference/fallback_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `5c893f3eed080a6bfcc48d0a1398a1688f3367f0eda6ee634925bc85bb439d34`. 112 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/reference/fallback_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // This is actual fallback execution only. The Python/SQLite process defines · [reviewed contract](#b0001) |
| [B0002 · 18–25](../../../../../tests/reference/fallback_driver.cpp#L18) | Callable definition: std::string query_class(planner::QueryClass value) | calls std::runtime_error; returns @; @; source comment (unverified): // This is actual fallback execution only. The Python/SQLite process defines · [reviewed contract](#b0002) |
| [B0003 · 26–34](../../../../../tests/reference/fallback_driver.cpp#L26) | Callable definition: std::string reason(pf::Reason value) | calls std::runtime_error; returns @; @ · [reviewed contract](#b0003) |
| [B0004 · 35–41](../../../../../tests/reference/fallback_driver.cpp#L35) | Callable definition: Json profile(const pf::Profile& value) | calls std::string, query_class, reason; returns {{@ ,std::string(value.backend)},{@ ,std::string(value.semantics)}, · [reviewed contract](#b0004) |
| [B0005 · 42–42](../../../../../tests/reference/fallback_driver.cpp#L42) | Callable definition: Json number(std::optional&lt;std::uint64_t&gt; value) | calls Json; returns value ? Json(*value) : Json(nullptr) · [reviewed contract](#b0005) |
| [B0006 · 43–49](../../../../../tests/reference/fallback_driver.cpp#L43) | Callable definition: Json tuples(const rf::TupleVector& input) | calls insert, storage::export_row, values, std::runtime_error; returns io::write_relation(rows); growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 50–56](../../../../../tests/reference/fallback_driver.cpp#L50) | Callable definition: Json metrics(const rf::Metrics& m) | calls ; returns {{@ ,m.work},{@ ,m.source_work},{@ ,m.source_rows}, · [reviewed contract](#b0007) |
| [B0008 · 57–77](../../../../../tests/reference/fallback_driver.cpp#L57) | Callable definition: Json snapshot(const rf::Runtime& owner, const pf::Plan& plan) | calls source_snapshot, explain, Json::array, push_back; returns {{@ ,owner.sequence()},{@ ,owner.ready()},{@ ,tuples(image.rows)},; growth push_back; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 78–86](../../../../../tests/reference/fallback_driver.cpp#L78) | Callable definition: Json apply(rf::Runtime& owner, const PhysicalSetUpdate& update) | calls tuples, metrics, code, std::string; returns {{@ ,nullptr},{@ ,epoch.input.input.physical_changed},; {{@ ,error.code()}} · [reviewed contract](#b0009) |
| [B0010 · 87–105](../../../../../tests/reference/fallback_driver.cpp#L87) | Callable definition: Json evaluate(const Json& request) | calls io::read_document, at, dump, empty; returns {{@ ,request.at(@ )},{@ ,profile(plan.profile())},; growth insert, push_back; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 106–106](../../../../../tests/reference/fallback_driver.cpp#L106) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 107–112](../../../../../tests/reference/fallback_driver.cpp#L107) | Callable definition: int main() | calls std::getline, evaluate, Json::parse, dump; returns 0; 1; 1 loop sites · [reviewed contract](#b0012) |

## B0001

[Lines 1–17](../../../../../tests/reference/fallback_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:e2433bd5027ac75dbd825126fc341790864349cf4bdc21e74eba1064206476d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import real fallback execution and external JSON/source-backend fixture facilities. |
| inputs / outputs | Includes, private aliases and driver scope comments; no expected answers. |
| invariants | Every test request executes a real fallback owner. Python/SQLite, not this C++ driver, define original-CQ expected behavior. |
| ownership | Ordinary wire/compiler DTOs and JSON traces are explicit test-boundary ownership. |
| failure | Compile/include failures are ordinary; source authorship is not a passing receipt. |
| cost | Compile-time setup followed by actual selected native work. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py) |

## B0002

[Lines 18–25](../../../../../tests/reference/fallback_driver.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L25:sha256:99c7b295a812abad1593f3814e7f80caff649ffa662482d253a3f59df82c19cc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the actual original structural query class. |
| inputs / outputs | QueryClass in; one exact class-name string out. |
| invariants | All three admitted classes have distinct wire names; no unknown enum defaults to cyclic/free-connex. |
| ownership | Returned ordinary string owns its bytes. |
| failure | Unknown value throws runtime_error and fails the driver. |
| cost | Bounded switch plus small string construction. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |

## B0003

[Lines 26–34](../../../../../tests/reference/fallback_driver.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L34:sha256:8755b51163705365ed12c030f5d19785c1e946b727309c64809070e617106a1e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the actual explicit admission reason. |
| inputs / outputs | Reason enum in; exact reason-name string out. |
| invariants | Contradiction, cyclic body, non-free-connex head and explicit reference choice remain distinguishable. |
| ownership | Returned ordinary string is test-owned. |
| failure | Unknown enum throws runtime_error; no guessed reason. |
| cost | Bounded switch and string allocation. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py) |

## B0004

[Lines 35–41](../../../../../tests/reference/fallback_driver.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L41:sha256:d069f3e0970a280a9595e281f8ee96ac3adc75e2d0781d55c3c8e581075f8c8b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the complete real guarantee profile as wire observations. |
| inputs / outputs | Borrowed planner Profile in; JSON static-text/class/reason fields out. |
| invariants | Copies actual strings/enums verbatim; no CROWN height, GHD width or constant-delay result is synthesized. |
| ownership | Profile views remain borrowed only during copying; JSON owns ordinary string payloads. |
| failure | Invalid class/reason or JSON allocation failure propagates. |
| cost | Fixed field count plus actual string/JSON copying. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [docs/fallback.md](../../../../fallback.md) |

## B0005

[Lines 42–42](../../../../../tests/reference/fallback_driver.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L42:sha256:c239fc4543f4aefeb48143bf337849e7b51d249a07043fd66e59c3da54bb5421
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve known versus unknown estimate values in JSON. |
| inputs / outputs | optional&lt;uint64&gt; in; exact JSON integer or null out. |
| invariants | No zero substitution for overflow/unknown estimates and no floating conversion. |
| ownership | Inline optional input and JSON scalar output. |
| failure | JSON construction errors propagate. |
| cost | O(1) value conversion. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp) |

## B0006

[Lines 43–49](../../../../../tests/reference/fallback_driver.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L49:sha256:3c2dfe27af1dc98a69d6686826ad42313118d23c4069c4940cf77b8e1d36189d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize all actual endpoint rows while rejecting native duplicate emissions. |
| inputs / outputs | Native owning TupleVector in; io::write_relation JSON out. |
| invariants | Every row is exported; Relation collision throws rather than silently hiding duplicate native output. |
| ownership | Borrows native tuple payloads during complete export; ordinary Relation and JSON are external test-owned copies. |
| failure | Duplicate output, export/allocation/wire failure fails the driver. |
| cost | Full scalar/row export, ordered set insertion and JSON construction for every endpoint. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp) |

## B0007

[Lines 50–56](../../../../../tests/reference/fallback_driver.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L56:sha256:577a5978de41e7d56022d05238390ff909ae11d29d0eda7c332fb3065d144f1b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present real selected runtime work counters and recomputation status. |
| inputs / outputs | Metrics in; all fallback counter fields and recomputed Boolean out. |
| invariants | Copies counters rather than deriving expected work, wall speedups or algorithmic bounds. |
| ownership | Borrowed scalar aggregate; JSON owns its values. |
| failure | JSON allocation errors propagate. |
| cost | Fixed field presentation plus JSON allocation. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [docs/fallback.md](../../../../fallback.md) |

## B0008

[Lines 57–77](../../../../../tests/reference/fallback_driver.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L77:sha256:c40b8f8cc28d49a4b274caccfa02dfeb5d803410bb8e1b6c962f1a62b37fd529
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture real committed answers, all sources, original binding identity and advisory estimates. |
| inputs / outputs | Runtime plus original Plan in; sequence/readiness/existence/rows/source/original counts/account and EXPLAIN/estimate JSON out. |
| invariants | Snapshot Binding exposes original atom/head counts but source-only compiled query has zero atoms. Source rows come from native export; Explain table counts/profile/products/results come from real owner; Plan estimates use those complete per-table cardinalities. Account equality is observed directly, not assumed from plan choice. |
| ownership | Local owning snapshot retains tuples/binding; Database, count vector and JSON are ordinary external test exports. No native tuple view escapes serialization. |
| failure | Any native read/export/estimate error or duplicate row fails the request; no repaired state replaces observations. |
| cost | Native funded snapshot, complete source export, O(tables+atoms) estimate/EXPLAIN work and complete JSON copies. These are observation costs, not uncharged production-delay claims. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py) |

## B0009

[Lines 78–86](../../../../../tests/reference/fallback_driver.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L86:sha256:d2f1faa314ae190cc4478bbea3fc80fdaf3e3d6980133f48ee19e91cac54bee3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attempt one actual serial fallback update and report exact endpoint output or typed refusal. |
| inputs / outputs | Runtime and complete PhysicalSetUpdate in; native changed/added/removed/metrics/zero-coordinator-alias observation or error code out. |
| invariants | Physical change is Epoch.input.input.physical_changed; added/removed are the fallback result deltas. No expected answer or source constraint decision is computed in the driver. |
| ownership | Local Epoch owns native output/binding through serialization; caller update and owner retain their own lifetimes. |
| failure | crown::Error and MemoryFailure codes are captured per event. Other exceptions terminate through main; no retry hides refusal. |
| cost | One real apply plus complete endpoint serialization; full recomputation/state/delta costs remain actual runtime work. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py) |

## B0010

[Lines 87–105](../../../../../tests/reference/fallback_driver.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L87-L105:sha256:31e65d36b284f5eedc16cc7275e428e67cdbc8f287764dc380627409915b3603
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one original-query JSONL fixture against an independent actual fallback owner. |
| inputs / outputs | Empty initial Document, backend choice and serial physical events in; actual profile/initial/each-prefix observations out. |
| invariants | Reject nonempty initial physical sources; call planner::fallback::admit directly with original catalog/query and finite reference/indexed policy. No minimum-tree or original free-connex lowering is called. Every event is a full physical row; only insert/delete are accepted. |
| ownership | One local Runtime owns its genuine account; cold request/Plan and accumulated wire trace are ordinary test objects. Each request has a separate native owner. |
| failure | Malformed/admission/construction errors fail main; per-event named refusal is retained and snapshot observes the actual unchanged or committed owner. |
| cost | Actual cold admission/native construction, serial updates and complete observations per event; whole captured trace is external test memory, not a streaming guarantee. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [include/crown/planner/fallback.hpp](../../../../../include/crown/planner/fallback.hpp), [include/crown/runtime/fallback.hpp](../../../../../include/crown/runtime/fallback.hpp), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py) |

## B0011

[Lines 106–106](../../../../../tests/reference/fallback_driver.cpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L106:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close private actual-driver serialization and execution helpers. |
| inputs / outputs | Namespace delimiter. |
| invariants | No model implementation or production backend registration is introduced. |
| ownership | No owner. |
| failure | No runtime failure branch. |
| cost | No runtime work. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp) |

## B0012

[Lines 107–112](../../../../../tests/reference/fallback_driver.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L112:sha256:62dc99cb0b141b4faddbb95d4c81e0ea92240f3230390879bd88f5dfcd80a8f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run serial actual JSONL requests behind one process diagnostic boundary. |
| inputs / outputs | stdin JSON lines in; one actual evaluate response per line, exit zero on completion or one with diagnostic. |
| invariants | No canned model response or pass flag is generated; requests execute separate owners and output exact captured observations. |
| ownership | Line/DOM and response own external test data; evaluate scopes retire native owners after owning outputs are serialized. |
| failure | std::exception prints diagnostic and returns one; no retry, result substitution or broad safety recovery. |
| cost | Full JSON parse/dump and real owner workload for every line. |
| Design | [tests/reference/fallback_driver.cpp](../../../../../tests/reference/fallback_driver.cpp), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py) |
