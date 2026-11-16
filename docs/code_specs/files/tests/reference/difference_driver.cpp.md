# `tests/reference/difference_driver.cpp` — block usage map

[Source](../../../../../tests/reference/difference_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `bf2913ece761e2565bec98ba22340dad92b212950a4c698b971e5db8e9b9f9a9`. 141 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/reference/difference_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Actual public-IR execution/export only. Expected operand bags, physical · [reviewed contract](#b0001) |
| [B0002 · 18–25](../../../../../tests/reference/difference_driver.cpp#L18) | Callable definition: std::string query_class(planner::QueryClass value) | calls std::runtime_error; returns @; @; source comment (unverified): // Actual public-IR execution/export only. Expected operand bags, physical · [reviewed contract](#b0002) |
| [B0003 · 26–34](../../../../../tests/reference/difference_driver.cpp#L26) | Callable definition: std::string reason(planner::fallback::Reason value) | calls std::runtime_error; returns @; @ · [reviewed contract](#b0003) |
| [B0004 · 35–45](../../../../../tests/reference/difference_driver.cpp#L35) | Callable definition: Json profile(const pd::Profile& value) | calls std::string, query_class, reason; returns {{@ ,value.mode == pd::Mode::set_except ? @ : @ }, · [reviewed contract](#b0004) |
| [B0005 · 46–46](../../../../../tests/reference/difference_driver.cpp#L46) | Callable definition: Json number(std::optional&lt;std::uint64_t&gt; value) | calls Json; returns value ? Json(*value) : Json(nullptr) · [reviewed contract](#b0005) |
| [B0006 · 47–51](../../../../../tests/reference/difference_driver.cpp#L47) | Callable definition: Json row(const storage::Tuple& tuple) | calls Json::array, storage::export_row, values, push_back; returns values; growth push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 52–56](../../../../../tests/reference/difference_driver.cpp#L52) | Callable definition: Json entries(const rd::OutputVector&lt;rd::Entry&gt;& input) | calls Json::array, push_back, row; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 57–65](../../../../../tests/reference/difference_driver.cpp#L57) | Callable definition: Json changes(const rd::OutputVector&lt;rd::Change&gt;& input) | calls Json::array, delta, push_back, row; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 66–70](../../../../../tests/reference/difference_driver.cpp#L66) | Callable definition: Json operand_estimates(const planner::fallback::Estimates& value) | calls number; returns {{@ ,number(value.source_rows)},{@ ,number(value.assignments_upper)}, · [reviewed contract](#b0009) |
| [B0010 · 71–76](../../../../../tests/reference/difference_driver.cpp#L71) | Callable definition: Json estimates(const pd::Estimates& value) | calls operand_estimates, number; returns {{@ ,operand_estimates(value.left)},{@ ,operand_estimates(value.right)}, · [reviewed contract](#b0010) |
| [B0011 · 77–100](../../../../../tests/reference/difference_driver.cpp#L77) | Callable definition: Json snapshot(const rd::Runtime& owner, const pd::Plan& plan) | calls source_snapshot, explain, Json::array, push_back; returns {{@ ,image.sequence},{@ ,owner.sequence()},{@ ,owner.ready()},; growth push_back; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 101–110](../../../../../tests/reference/difference_driver.cpp#L101) | Callable definition: Json apply(rd::Runtime& owner, const PhysicalSetUpdate& update) | calls changes, code; returns {{@ ,nullptr},{@ ,epoch.input.input.physical_changed},{@ ,changes(epoch.changes)},; {{@ ,error.code… · [reviewed contract](#b0012) |
| [B0013 · 111–134](../../../../../tests/reference/difference_driver.cpp#L111) | Callable definition: Json evaluate(const Json& request) | calls io::read_document, at, dump, empty; returns {{@ ,request.at(@ )},{@ ,profile(plan.profile())},; growth insert, push_back; 3 loop sites · [reviewed contract](#b0013) |
| [B0014 · 135–135](../../../../../tests/reference/difference_driver.cpp#L135) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 136–141](../../../../../tests/reference/difference_driver.cpp#L136) | Callable definition: int main() | calls std::getline, evaluate, Json::parse, dump; returns 0; 1; 1 loop sites · [reviewed contract](#b0015) |

## B0001

[Lines 1–17](../../../../../tests/reference/difference_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:792f2264f7c39d0f034482b0b5f57d62e22f45cf59ff6b7d5bf708d776f707d3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import production difference ownership, exact JSON DTO support and the finite indexed fixture. |
| inputs / outputs | Includes, crown/Json aliases and pd/rd namespace aliases precede private export helpers. |
| invariants | These are test-driver compile dependencies; the native owner is linked separately. Expected difference computation remains in Python/SQLite. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | Compile dependencies and namespace declarations only. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0002

[Lines 18–25](../../../../../tests/reference/difference_driver.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L25:sha256:63e4f27acf9866cb8aba6865542b174f7f2d38decb434e8d335c2941339b602d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the actual operand structural classification. |
| inputs / outputs | One QueryClass becomes its stable free_connex/acyclic_non_free_connex/cyclic spelling. |
| invariants | No recognition is performed here; an unknown enum fails instead of receiving a class. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | One fixed enum switch and ordinary string construction. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 26–34](../../../../../tests/reference/difference_driver.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L34:sha256:58d328ff72d859651e26cdd9c094fba96241fc6ce18f071f3ab5f0c8eba2908d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the actual operand admission reason. |
| inputs / outputs | One fallback Reason becomes its stable reason spelling. |
| invariants | Contradiction, structural fallback and explicit reference choice remain distinct; the driver invents no proof reason. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | One fixed enum switch and ordinary string construction. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 35–45](../../../../../tests/reference/difference_driver.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L45:sha256:30b9f090ade9eb687d606608c6a5fcaa80b484e4100ae8b6cb084f0b21e2c0d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export every actual difference guarantee-profile field. |
| inputs / outputs | A production Profile becomes mode/backend/semantics/arithmetic/output/delta/state/cost/class/reason JSON. |
| invariants | Mode arrives from genuine validated admission. Original operand classes/reasons remain visible; no CROWN/GHD/P11 guarantee is inferred from the empty source coordinator. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | Fixed field serialization and ordinary JSON/string allocations. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 46–46](../../../../../tests/reference/difference_driver.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L46:sha256:c239fc4543f4aefeb48143bf337849e7b51d249a07043fd66e59c3da54bb5421
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve overflow/unknown advisory numbers in JSON. |
| inputs / outputs | An optional uint64 is encoded as its integer value or null. |
| invariants | Missing is not encoded as zero or silently wrapped. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | One optional test and scalar JSON construction. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 47–51](../../../../../tests/reference/difference_driver.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L51:sha256:2641c3d4e9665fe82b28009564aee0639755e9b81f7fcad764200e023adce207
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export one native output tuple for verification. |
| inputs / outputs | TupleValuesView is exported to ordinary Row scalars, then exact scalar JSON cells. |
| invariants | This is the caller-side diagnostic boundary; production evaluation retains native funded tuples and does not use this helper. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | Full tuple width/payload export and JSON allocation. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 52–56](../../../../../tests/reference/difference_driver.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L56:sha256:de7c9d845174374d4ed2861088d5cda14bc13dcd681a9484dc337e69ef86deba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export compressed positive result entries without expanding copies. |
| inputs / outputs | Each actual Entry becomes values plus its uint64 multiplicity. |
| invariants | One native key is serialized once regardless of count. Python checks positivity, uniqueness and exact counts independently. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | Linear in compressed key count and exported payload widths; independent of expanded bag mass. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 57–65](../../../../../tests/reference/difference_driver.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L65:sha256:7848be4ac1c18d06e938be503cb55941ae31f806de28c4172f8e7f4ac544c543
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export exact numeric endpoint replacements and computed signed magnitude. |
| inputs / outputs | Each actual Change yields tuple, before, after and delta().negative/magnitude. |
| invariants | Before/after counts, not aggregate payloads or membership flags, define the change. No signed int64 cast can truncate a uint64 delta. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | Linear in changed compressed keys and exported tuple widths. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 66–70](../../../../../tests/reference/difference_driver.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L70:sha256:d95ce295cab59890013746662dccad2e37f43947d4323fde3aa1f1edd77bfab5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one operand's actual planner row estimates. |
| inputs / outputs | Fallback Estimates optionals and overflow/advisory flags become JSON. |
| invariants | Logical row bounds and unknown values retain their public meanings; these are not peak-byte or timing estimates. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | Fixed field serialization. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 71–76](../../../../../tests/reference/difference_driver.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L76:sha256:11decdd690c23821acb00638e2c10e659ee2af99f03bb08a45e67bc6dfab99a9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export actual combined difference admission estimates. |
| inputs / outputs | Both operand estimates plus source/key/mass/state bounds and flags become JSON. |
| invariants | Operand bounds are not subtracted by the driver; the genuine Plan supplies the combined profile. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | Fixed field serialization plus both operand estimate exports. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0011

[Lines 77–100](../../../../../tests/reference/difference_driver.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L100:sha256:22d21e0314bf62b4edd108e9b1e37213f26fea15b5173a5c3203bf48d0f44d64
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture actual committed sources, compressed answers and explanation metadata. |
| inputs / outputs | Runtime snapshot/source_snapshot/explain and Plan estimates over actual exported table counts become one JSON checkpoint. |
| invariants | Original left/right atoms/head, source-only zero atoms, source/runtime sequence, original account, profiles and multiplicity limit remain separately observable. Source/result exports are test-only copies, not another runtime owner. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | Full source export, owning snapshot-handle copies, explanation allocation and planner bound calculations at every checkpoint; no maintenance timing claim. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 101–110](../../../../../tests/reference/difference_driver.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L110:sha256:5b5df8ec29a22aed1cbe28b24a03358971ec6ca72f1d562d8897612171b36661
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one actual physical set event and expose its result or typed refusal. |
| inputs / outputs | One update yields actual source-changed/alias metrics, compressed Changes and selected runtime metrics, or Error.code(). |
| invariants | Constraint refusal is recorded without advancing a reference model here. Unexpected standard/resource failures escape to the process boundary. No retry or alternate execution path is installed. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | One real native apply plus explicit delta/metrics serialization; refused operations retain their production rollback cost. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0013

[Lines 111–134](../../../../../tests/reference/difference_driver.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L134:sha256:75d71d0fd5d8d48680c07bf4c582e63fc0d1dc252bf36680bbfc1e5a7f111080
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and execute an original public-IR query pair against one empty source owner. |
| inputs / outputs | JSON document/right_query/mode/backend/events become a genuine Plan, Runtime, initial checkpoint and actual per-event trace. |
| invariants | Right document clones the same original catalog and replaces only its query. Inputs begin empty; modes and set-event spellings are checked. No expected join, bag subtraction or query-specific C++ class exists in this driver. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | Cold DTO parsing/admission/runtime construction plus one real apply and full checkpoint export per requested event. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0014

[Lines 135–135](../../../../../tests/reference/difference_driver.cpp#L135); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L135:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private driver-helper namespace. |
| inputs / outputs | The anonymous namespace ends before the process entry point. |
| invariants | This lexical delimiter creates no query state or validation. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | No executable work. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0015

[Lines 136–141](../../../../../tests/reference/difference_driver.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L141:sha256:62dc99cb0b141b4faddbb95d4c81e0ea92240f3230390879bd88f5dfcd80a8f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute independent JSONL requests through the actual driver. |
| inputs / outputs | Each input line is parsed/executed and emits one JSON line; a standard exception prints one process diagnostic and returns failure. |
| invariants | Requests each construct an independent owner. This process-level catch is test transport, not a runtime recovery/retry layer. |
| ownership | The independent driver owns ordinary input/output JSON/compiler DTOs and explicit diagnostic exports; each actual Runtime and its native tuples retain their own original query account. No expected model is retained inside production. |
| failure | Source parsing, allocation or unexpected native failures propagate to the process boundary; apply() records only production Error codes for deliberate constraint-refusal traces. No production catch/retry or rollback mechanism is added by this test block. |
| cost | Sum of requested genuine admissions/updates/exports, JSON parsing and I/O. |
| Design | [tests/reference/difference_driver.cpp](../../../../../tests/reference/difference_driver.cpp), [include/crown/runtime/difference.hpp](../../../../../include/crown/runtime/difference.hpp), [tests/integration/key_specialization_oracle.py](../../../../../tests/integration/key_specialization_oracle.py), [tests/integration/fallback_oracle.py](../../../../../tests/integration/fallback_oracle.py), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp), [Refactor.md](../../../../../Refactor.md) |
