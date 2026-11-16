# `include/crown/runtime/selection.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/selection.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `bb263f759bbd7de99eec78d036c9212ebc6dc3e9d04b43c90e15f14dbb5cf172`. 78 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../../ranking.md), [docs/selection.md](../../../../../selection.md), [docs/selection_binding.md](../../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/runtime/selection.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Qualify the selected plan with a real Session's captured source premises. · [reviewed contract](#b0001) |
| [B0002 · 14–29](../../../../../../include/crown/runtime/selection.hpp#L14) | Type/record definition: class PatternGuarantee | returns *this; source comment (unverified): // Qualify the selected plan with a real Session's captured source premises. · [reviewed contract](#b0002) |
| [B0003 · 30–48](../../../../../../include/crown/runtime/selection.hpp#L30) | Type/record definition: class CurrentSelection | returns *this; source comment (unverified): // Available only from the explicit measured reoptimization selection entry. · [reviewed contract](#b0003) |
| [B0004 · 49–59](../../../../../../include/crown/runtime/selection.hpp#L49) | Type/record definition: struct Attempt |  · [reviewed contract](#b0004) |
| [B0005 · 60–78](../../../../../../include/crown/runtime/selection.hpp#L60) | declares values/defaults or compile-time conditions. | source comment (unverified): // A fresh bounded capture is made even for height-only. The caller preserves · [reviewed contract](#b0005) |

## B0001

[Lines 1–13](../../../../../../include/crown/runtime/selection.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare current selection and its selected-plan/as-of-Session pattern profile interface. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. Adjacent comments distinguish selected and installed plans, immutable captured prefixes and trusted restore history. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0002

[Lines 14–29](../../../../../../include/crown/runtime/selection.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L29:sha256:54037ec2a18edbb6d76f5323810189d8bfc15cc2abd228e1b403a1cbafc482c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain selected-plan conditions together with actual captured Session premises. |
| inputs / outputs | Private CurrentSelection construction shares existing Data. selected() returns the pure profile; enforcement()/stamp() expose immutable monitor/owner context; selected_plan_matches_capture() reports exact compiled physical identity equality. |
| invariants | Successful current-selection admission already binds source, canonical rules, physical prefix, owner and modes. A target plan can differ from the installed plan. This is as-of data, not future freshness or retrospective work accounting. Trusted checkpoint history stays explicit; replacement starts charged initialization. |
| ownership | One shared existing Data pointer retains selection and capture; no row/rule/edge copy or new account. Reference getters need this profile to survive; moves retain source validity. |
| failure | No public raw constructor or new catch/translation boundary. Existing current-selection factory failures publish no instance. |
| cost | O(1) handle/field access, except fixed64-byte identity comparison; no allocation/update hook. Final release can destroy the retained capture/selection graph. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../../selection.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0003

[Lines 30–48](../../../../../../include/crown/runtime/selection.hpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CurrentSelection {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an actual-source-bound checked selection and its capture. |
| inputs / outputs | Closed source-aware selection factories return the typed plan/candidate selection, original owner facts and optional explicit preparation measurement. |
| invariants | CurrentSelection is not itself an authorization to switch a live session: freshness, source/configuration, equivalence, output and durable barriers remain required. The new optional profile shares this exact selection/capture and requires real unrejected Session premises. It reports selected-plan conditions, an as-of owner/prefix and a full-physical-plan match; no live freshness, retrospective work measurement or extra update hook. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | No public arbitrary result constructor; preparation failures return typed Attempt outcomes. |
| cost | Accounted wrapper allocated before cache finalization; descriptor copies share the prepared selection/capture graphs. Final release can destroy substantial metadata/captured facts. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
CurrentSelection(const CurrentSelection&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the immutable current-selection result. |
| inputs / outputs | Operate on the already prepared actual-bound immutable handle. |
| invariants | Copy-like moves/closed factories preserve nonempty Data required by noexcept getters; scores are not inferred nanoseconds. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | Declared shared operations/getters do not throw. |
| cost | Fixed shared reference operation. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
CurrentSelection& operator=(const CurrentSelection&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace by shared current-selection copy. |
| inputs / outputs | Operate on the already prepared actual-bound immutable handle. |
| invariants | Copy-like moves/closed factories preserve nonempty Data required by noexcept getters; scores are not inferred nanoseconds. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | Declared shared operations/getters do not throw. |
| cost | Retention plus actual replaced graph release. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
CurrentSelection(CurrentSelection&& other) noexcept :
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-like move keeping both selections usable. |
| inputs / outputs | Operate on the already prepared actual-bound immutable handle. |
| invariants | Copy-like moves/closed factories preserve nonempty Data required by noexcept getters; scores are not inferred nanoseconds. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | Declared shared operations/getters do not throw. |
| cost | Fixed shared retention; source remains valid. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
CurrentSelection& operator=(CurrentSelection&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-like current-selection move assignment. |
| inputs / outputs | Operate on the already prepared actual-bound immutable handle. |
| invariants | Copy-like moves/closed factories preserve nonempty Data required by noexcept getters; scores are not inferred nanoseconds. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | Declared shared operations/getters do not throw. |
| cost | Shared retention/source preservation and actual old graph release. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
const ps::Selection& selection() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the genuine typed selected candidate/plan. |
| inputs / outputs | Operate on the already prepared actual-bound immutable handle. |
| invariants | Copy-like moves/closed factories preserve nonempty Data required by noexcept getters; scores are not inferred nanoseconds. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | Declared shared operations/getters do not throw. |
| cost | Fixed reference, no new lowering or native application. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
const ranking::RuntimeEvidence& capture() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow original actual-owner selection evidence. |
| inputs / outputs | Operate on the already prepared actual-bound immutable handle. |
| invariants | Copy-like moves/closed factories preserve nonempty Data required by noexcept getters; scores are not inferred nanoseconds. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | Declared shared operations/getters do not throw. |
| cost | Fixed reference, no fresh owner read. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
std::optional<std::uint64_t> preparation_nanoseconds() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read optional measured complete selection preparation time. |
| inputs / outputs | Operate on the already prepared actual-bound immutable handle. |
| invariants | Copy-like moves/closed factories preserve nonempty Data required by noexcept getters; scores are not inferred nanoseconds. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | Declared shared operations/getters do not throw. |
| cost | Fixed optional read; only explicit measured route can populate it, and clock failure can leave it absent. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
friend struct detail::Factory;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict actual-bound result construction to selection factory. |
| inputs / outputs | Private constructor/storage declaration. |
| invariants | No caller can mint the result from raw flags, paired snapshots or guessed owner IDs. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | Declaration/private descriptor publication adds no handler. |
| cost | Fixed shared descriptor storage; last release retains actual graph destruction cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
explicit CurrentSelection(std::shared_ptr<const detail::Data> data)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish prepared actual-bound selection Data. |
| inputs / outputs | Private constructor/storage declaration. |
| invariants | No caller can mint the result from raw flags, paired snapshots or guessed owner IDs. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | Declaration/private descriptor publication adds no handler. |
| cost | Fixed shared descriptor storage; last release retains actual graph destruction cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
@source-span:L30-L48:sha256:9601f41ae799969951f6bd26c573236e32340a600fdc81484c6590eef6496a85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain selected typed plan, capture and optional measured time. |
| inputs / outputs | Private constructor/storage declaration. |
| invariants | No caller can mint the result from raw flags, paired snapshots or guessed owner IDs. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | Declaration/private descriptor publication adds no handler. |
| cost | Fixed shared descriptor storage; last release retains actual graph destruction cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
std::optional<PatternGuarantee> pattern_guarantee() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the optional captured actual-Session support-action profile. |
| inputs / outputs | Return the corresponding owning immutable profile handle when its required proof/premises exist; absence remains explicit. |
| invariants | The method does not refresh live state, infer a total CPU bound, or add an update path. Detailed callable/class contracts state exact qualification. |
| ownership | Shares the existing funded graph; no clone or fresh account. |
| failure | Noexcept; unsupported/absent qualification returns none. |
| cost | O(1) and no allocation; last-owner graph teardown remains separately sized. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../../selection.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0004

[Lines 49–59](../../../../../../include/crown/runtime/selection.hpp#L49); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Attempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return source-aware selection result and diagnostics. |
| inputs / outputs | Stop/stage, optional CurrentSelection, processing usage/component stop/resource/reasons/timing availability and retained/evaluated counts. |
| invariants | Failure does not manufacture a valid selection or usable zero facts. The completed handle preserves its own typed authority, separate from session publication. |
| ownership | Fixed diagnostics plus optional genuine shared CurrentSelection; copying does not recapture or lower. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed value/handle copy plus actual shared release cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
ps::Stop stop =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The source-aware selection outcome, default internal_error. |
| inputs / outputs | Stores/exposes the source-aware selection outcome, default internal_error. |
| invariants | Failure does not manufacture a valid selection or usable zero facts. The completed handle preserves its own typed authority, separate from session publication. |
| ownership | Fixed diagnostics plus optional genuine shared CurrentSelection; copying does not recapture or lower. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy plus actual shared release cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
ps::Stage stage =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The selection stage associated with outcome/usage. |
| inputs / outputs | Stores/exposes the selection stage associated with outcome/usage. |
| invariants | Failure does not manufacture a valid selection or usable zero facts. The completed handle preserves its own typed authority, separate from session publication. |
| ownership | Fixed diagnostics plus optional genuine shared CurrentSelection; copying does not recapture or lower. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy plus actual shared release cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
std::optional<CurrentSelection> selection;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional genuine completed actual-bound selection. |
| inputs / outputs | Stores/exposes the optional genuine completed actual-bound selection. |
| invariants | Failure does not manufacture a valid selection or usable zero facts. The completed handle preserves its own typed authority, separate from session publication. |
| ownership | Fixed diagnostics plus optional genuine shared CurrentSelection; copying does not recapture or lower. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy plus actual shared release cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
planner::ranking::Usage usage;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The selected processing work/byte/time observation. |
| inputs / outputs | Stores/exposes the selected processing work/byte/time observation. |
| invariants | Failure does not manufacture a valid selection or usable zero facts. The completed handle preserves its own typed authority, separate from session publication. |
| ownership | Fixed diagnostics plus optional genuine shared CurrentSelection; copying does not recapture or lower. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy plus actual shared release cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
std::optional<planner::ranking::Stop> component_stop;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional delegated ranking/lowering component outcome. |
| inputs / outputs | Stores/exposes the optional delegated ranking/lowering component outcome. |
| invariants | Failure does not manufacture a valid selection or usable zero facts. The completed handle preserves its own typed authority, separate from session publication. |
| ownership | Fixed diagnostics plus optional genuine shared CurrentSelection; copying does not recapture or lower. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy plus actual shared release cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
ps::Resource resource =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The exhausted/failed resource domain. |
| inputs / outputs | Stores/exposes the exhausted/failed resource domain. |
| invariants | Failure does not manufacture a valid selection or usable zero facts. The completed handle preserves its own typed authority, separate from session publication. |
| ownership | Fixed diagnostics plus optional genuine shared CurrentSelection; copying does not recapture or lower. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy plus actual shared release cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
planner::ranking::Reasons reasons{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The explicit boundary/fact failure reasons. |
| inputs / outputs | Stores/exposes the explicit boundary/fact failure reasons. |
| invariants | Failure does not manufacture a valid selection or usable zero facts. The completed handle preserves its own typed authority, separate from session publication. |
| ownership | Fixed diagnostics plus optional genuine shared CurrentSelection; copying does not recapture or lower. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy plus actual shared release cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
ps::PreparationTiming preparation_timing =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Whether component preparation timing is present/available. |
| inputs / outputs | Stores/exposes whether component preparation timing is present/available. |
| invariants | Failure does not manufacture a valid selection or usable zero facts. The completed handle preserves its own typed authority, separate from session publication. |
| ownership | Fixed diagnostics plus optional genuine shared CurrentSelection; copying does not recapture or lower. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy plus actual shared release cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
std::size_t retained{}, constraint_evaluated{}, primary_evaluated{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The retained, constrained and primary evaluated candidate counts. |
| inputs / outputs | Stores/exposes the retained, constrained and primary evaluated candidate counts. |
| invariants | Failure does not manufacture a valid selection or usable zero facts. The completed handle preserves its own typed authority, separate from session publication. |
| ownership | Fixed diagnostics plus optional genuine shared CurrentSelection; copying does not recapture or lower. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed value/handle copy plus actual shared release cost. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

## B0005

[Lines 60–78](../../../../../../include/crown/runtime/selection.hpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const PhysicalRuntime&, const ps::Request&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select against a fresh actual PhysicalRuntime boundary. |
| inputs / outputs | Takes candidate snapshot/source/request/state limits and optional borrowed cache/use policy; returns typed Attempt. |
| invariants | Always makes fresh bounded capture even for height-only. Caller preserves exclusive synchronous owner access; source/candidate/boundary admission precedes result. |
| ownership | Owner/source/cache are borrowed during call; result owns genuine selected plan/evidence via native accounted shared graphs. |
| failure | noexcept translates component/resource/allocation/internal failures into exact Attempt diagnostics; no native source application or session switch. |
| cost | Fresh metadata/workload/state capture as requested, ranking/lowering and explicit cache lookup/prepare/finalization work; wrapper funding precedes cache effects. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
const DeltaRuntime&, const ps::Request&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select against a fresh actual DeltaRuntime boundary. |
| inputs / outputs | Takes candidate snapshot/source/request/state limits and optional borrowed cache/use policy; returns typed Attempt. |
| invariants | Always makes fresh bounded capture even for height-only. Caller preserves exclusive synchronous owner access; source/candidate/boundary admission precedes result. |
| ownership | Owner/source/cache are borrowed during call; result owns genuine selected plan/evidence via native accounted shared graphs. |
| failure | noexcept translates component/resource/allocation/internal failures into exact Attempt diagnostics; no native source application or session switch. |
| cost | Fresh metadata/workload/state capture as requested, ranking/lowering and explicit cache lookup/prepare/finalization work; wrapper funding precedes cache effects. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
const QuerySession&, const ps::Request&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select against a fresh actual QuerySession boundary. |
| inputs / outputs | Takes candidate snapshot/source/request/state limits and optional borrowed cache/use policy; returns typed Attempt. |
| invariants | Always makes fresh bounded capture even for height-only. Caller preserves exclusive synchronous owner access; source/candidate/boundary admission precedes result. |
| ownership | Owner/source/cache are borrowed during call; result owns genuine selected plan/evidence via native accounted shared graphs. |
| failure | noexcept translates component/resource/allocation/internal failures into exact Attempt diagnostics; no native source application or session switch. |
| cost | Fresh metadata/workload/state capture as requested, ranking/lowering and explicit cache lookup/prepare/finalization work; wrapper funding precedes cache effects. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
select_for_reoptimization(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an explicitly measured source-aware selection for the C03 bridge. |
| inputs / outputs | Runs the same genuine QuerySession selection with a full preparation interval, returning optional measured nanoseconds in CurrentSelection. |
| invariants | Measurement includes capture, ranking, lowering, cache and temporary teardown. Normal select_current does not infer this timing from scores. |
| ownership | Factory-only shared immutable Data owns the pure typed Selection, genuine RuntimeEvidence and optional measured time. Custom moves share Data and keep source valid. No mutable runtime/cache pointer is retained; returned references borrow this handle. |
| failure | noexcept returns normal Attempt failures; clock regression can leave the selection measurement absent, which bridge rejects. |
| cost | All source-aware selection costs plus two steady-clock reads; no automatic reoptimization enablement. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |

```text
void begin_reoptimization(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a measured current selection to the native session candidate path. |
| inputs / outputs | Revalidates actual boundary/policy facts/configuration/source, requires measured selection time, installs exact expected owner/epoch fence and charges measured selection plus bridge validation. |
| invariants | Rejects unmeasured/stale/foreign/differently configured result. C02 height/depth/slot scores never become a time forecast; native source/equivalence/output/durable barriers remain. |
| ownership | Borrows CurrentSelection and mutates the actual QuerySession only through its guarded native begin API; Options is fixed caller configuration. |
| failure | Measured/binding/staleness/clock/cost/native preparation failures propagate; no blind retry or root rollback. |
| cost | Fresh actual capture/revalidation may allocate/scan; exact source/options comparison and timing arithmetic precede actual target build/metadata/backlog preparation. |
| Design | [include/crown/runtime/selection.hpp](../../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../../selection.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/selection_binding.md](../../../../../selection_binding.md) |
