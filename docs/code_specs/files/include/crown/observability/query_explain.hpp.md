# `include/crown/observability/query_explain.hpp` — block usage map

[Source](../../../../../../include/crown/observability/query_explain.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `ff73337f90ec64cb632c4be6655242598c361dfca0fc63a8b8f5006132145177`. 42 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../../include/crown/observability/query_explain.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 5–5](../../../../../../include/crown/observability/query_explain.hpp#L5) | Type/record definition: enum class QueryExplainSource |  · [reviewed contract](#b0002) |
| [B0003 · 6–6](../../../../../../include/crown/observability/query_explain.hpp#L6) | Type/record definition: enum class QueryHeightStatus |  · [reviewed contract](#b0003) |
| [B0004 · 7–7](../../../../../../include/crown/observability/query_explain.hpp#L7) | Type/record definition: struct QueryExplainLimits |  · [reviewed contract](#b0004) |
| [B0005 · 8–42](../../../../../../include/crown/observability/query_explain.hpp#L8) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Immutable owning read. Capture requires the producer's existing exclusive · [reviewed contract](#b0005) |

## B0001

[Lines 1–4](../../../../../../include/crown/observability/query_explain.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the observability query_explain public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

## B0002

[Lines 5–5](../../../../../../include/crown/observability/query_explain.hpp#L5); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class QueryExplainSource {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the genuine typed producer of query evidence. |
| inputs / outputs | Exact search, replay, checked upper, verified optimum/infeasibility or checked certificate; no editable source flag constructor. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

## B0003

[Lines 6–6](../../../../../../include/crown/observability/query_explain.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class QueryHeightStatus {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish published typed witnesses from numeric producer progress. |
| inputs / outputs | Unknown, owner checked upper not yet published, checked upper, verified optimum or verified infeasible. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

## B0004

[Lines 7–7](../../../../../../include/crown/observability/query_explain.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QueryExplainLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound admitted witness/certificate entry counts. |
| inputs / outputs | Default100,000 witness nodes and one million certificate lower-bound entries. |
| invariants | Count checks occur after ordinary report Data preparation; they do not cap all retained proof/model bytes. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

## B0005

[Lines 8–42](../../../../../../include/crown/observability/query_explain.hpp#L8); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class QueryExplanation
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one exclusive-read typed query-evidence report. |
| inputs / outputs | Closed capture/from factories preserve exact producer binding/progress and actual typed witness/optimum/infeasibility/certificate handles. |
| invariants | No constructor accepts editable progress, flags, raw trees or legacy aggregates. Capture/export performs no search advance, replay, recognition or JSON work. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Invalid/moved producer/evidence, count limit or ordinary allocation failure propagates before a result. |
| cost | One ordinary shared Data allocation plus producer value/typed-handle copies and count checks; potentially large original immutable model/proof graphs remain retained. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
static QueryExplanation capture(const planner::ExactSearch&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture or retain genuine typed query evidence. |
| inputs / outputs | Read exact search binding/progress/policy/limits/incumbent/optimum/infeasibility under caller-exclusive access. |
| invariants | Sharing existing evidence does not produce a new proof. Exact producer-exclusive access and binding validity remain mandatory. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Moved/invalid typed access, witness/certificate count caps or ordinary Data allocation errors propagate; no mutable producer advancement. |
| cost | Ordinary Data allocation and fixed producer-value/typed-handle copies, then count checks; no proof replay/tree cloning or hidden recognition pass. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
static QueryExplanation capture(const planner::CertificateReplay&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture or retain genuine typed query evidence. |
| inputs / outputs | Read replay binding/progress/options and its actual checked result without advancing replay. |
| invariants | Sharing existing evidence does not produce a new proof. Exact producer-exclusive access and binding validity remain mandatory. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Moved/invalid typed access, witness/certificate count caps or ordinary Data allocation errors propagate; no mutable producer advancement. |
| cost | Ordinary Data allocation and fixed producer-value/typed-handle copies, then count checks; no proof replay/tree cloning or hidden recognition pass. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
static QueryExplanation from(planner::ValidatedIncumbent,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture or retain genuine typed query evidence. |
| inputs / outputs | Retain the already checked original-bound upper witness. |
| invariants | Sharing existing evidence does not produce a new proof. Exact producer-exclusive access and binding validity remain mandatory. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Moved/invalid typed access, witness/certificate count caps or ordinary Data allocation errors propagate; no mutable producer advancement. |
| cost | Ordinary Data allocation and fixed producer-value/typed-handle copies, then count checks; no proof replay/tree cloning or hidden recognition pass. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
static QueryExplanation from(planner::VerifiedOptimum,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture or retain genuine typed query evidence. |
| inputs / outputs | Retain genuine verified optimum and normalize its upper witness into report state. |
| invariants | Sharing existing evidence does not produce a new proof. Exact producer-exclusive access and binding validity remain mandatory. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Moved/invalid typed access, witness/certificate count caps or ordinary Data allocation errors propagate; no mutable producer advancement. |
| cost | Ordinary Data allocation and fixed producer-value/typed-handle copies, then count checks; no proof replay/tree cloning or hidden recognition pass. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
static QueryExplanation from(planner::VerifiedInfeasible,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture or retain genuine typed query evidence. |
| inputs / outputs | Retain genuine verified empty height-family evidence. |
| invariants | Sharing existing evidence does not produce a new proof. Exact producer-exclusive access and binding validity remain mandatory. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Moved/invalid typed access, witness/certificate count caps or ordinary Data allocation errors propagate; no mutable producer advancement. |
| cost | Ordinary Data allocation and fixed producer-value/typed-handle copies, then count checks; no proof replay/tree cloning or hidden recognition pass. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
static QueryExplanation from(planner::CheckedCertificate,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture or retain genuine typed query evidence. |
| inputs / outputs | Retain genuine checked replay evidence, extracting any verified optimum/infeasibility. |
| invariants | Sharing existing evidence does not produce a new proof. Exact producer-exclusive access and binding validity remain mandatory. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Moved/invalid typed access, witness/certificate count caps or ordinary Data allocation errors propagate; no mutable producer advancement. |
| cost | Ordinary Data allocation and fixed producer-value/typed-handle copies, then count checks; no proof replay/tree cloning or hidden recognition pass. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const planner::SearchBinding& binding() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow exact original query binding. |
| inputs / outputs | Returns retained immutable Catalog/Query binding. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked Data/reference access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
QueryExplainSource source() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual producer/evidence origin. |
| inputs / outputs | Returns its recorded closed-factory source enum. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked Data/value access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
QueryHeightStatus height_status() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual height-evidence availability. |
| inputs / outputs | Verified outcomes take precedence; numeric search upper without witness is explicitly unpublished. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed optional/enum checks. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
std::optional<std::size_t> lower() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a safe original-height lower bound. |
| inputs / outputs | Infeasible returns absent, optimum exact height, otherwise universal0 for no atoms or1 for a nonempty body. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed tests; no recognition, search or certificate replay. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
std::optional<std::size_t> upper() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the typed or numeric producer upper. |
| inputs / outputs | Uses optimum, then checked witness, then search progress upper; the last need not expose a tree. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed tests; no witness publication/advance. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<planner::SearchProgress>& search_progress() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured exact-search progress. |
| inputs / outputs | Absent for other producer types. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked reference. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<planner::ReplayProgress>& replay_progress() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured certificate-replay progress. |
| inputs / outputs | Absent for other producer types. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked reference. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<planner::SearchPolicy>& policy() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured actual search policy. |
| inputs / outputs | Not an editable override or proof of completion. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked reference. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<planner::ContinuationLimits>& search_limits() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured producer continuation limits. |
| inputs / outputs | Those are the producer limits, separate from report limits. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked reference. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<planner::ReplayOptions>& replay_limits() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured replay options. |
| inputs / outputs | No replay is performed by access. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked reference. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<planner::ValidatedIncumbent>& witness() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual published checked upper witness. |
| inputs / outputs | A numeric upper alone does not populate this handle. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked reference. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<planner::VerifiedOptimum>& optimum() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow retained genuine optimum evidence. |
| inputs / outputs | No new minimum proof is inferred from progress. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked reference. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<planner::VerifiedInfeasible>& infeasibility() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow genuine checked empty-family evidence. |
| inputs / outputs | Distinct from selected constant-false operator or missing report facts. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked reference. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const std::optional<planner::CheckedCertificate>& checked_certificate() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow actual replay-checked evidence. |
| inputs / outputs | No editable certificate DTO is accepted by the report constructor. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed checked reference. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const planner::HeightCertificate* certificate() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the certificate underlying a verified outcome. |
| inputs / outputs | Pointer from retained optimum/infeasibility, otherwise nullptr; no clone or replay. |
| invariants | Reported facts keep exact original producer/evidence scope; tree encoders separately require witness(). |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | data() rejects moved-from report; typed evidence access retains its existing validity conditions. |
| cost | Fixed tests and borrowed pointer; no independent retention. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
struct Data;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide immutable query-report storage. |
| inputs / outputs | Private closed report preparation/access/storage. |
| invariants | Only genuine typed sources populate Data; count checks do not create proof authority. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Invalid binding/count/access/allocation errors propagate; no recovery wrapper. |
| cost | Declaration only. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
explicit QueryExplanation(std::shared_ptr<const Data>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a prepared query-report graph. |
| inputs / outputs | Private closed report preparation/access/storage. |
| invariants | Only genuine typed sources populate Data; count checks do not create proof authority. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Invalid binding/count/access/allocation errors propagate; no recovery wrapper. |
| cost | Fixed shared descriptor move. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
static QueryExplanation finish(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize existing evidence handles and enforce report count caps. |
| inputs / outputs | Private closed report preparation/access/storage. |
| invariants | Only genuine typed sources populate Data; count checks do not create proof authority. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Invalid binding/count/access/allocation errors propagate; no recovery wrapper. |
| cost | Fixed typed-handle extraction and node/entry count reads after Data allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
const Data& data() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject moved-from query-report access. |
| inputs / outputs | Private closed report preparation/access/storage. |
| invariants | Only genuine typed sources populate Data; count checks do not create proof authority. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Invalid binding/count/access/allocation errors propagate; no recovery wrapper. |
| cost | Fixed pointer check. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |

```text
std::shared_ptr<const Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable binding/progress/proof report Data. |
| inputs / outputs | Private closed report preparation/access/storage. |
| invariants | Only genuine typed sources populate Data; count checks do not create proof authority. |
| ownership | Ordinary shared immutable Data retains exact SearchBinding, copied producer progress/options and typed proof/witness handles. No mutable search/replay owner pointer remains. Returned references/pointers borrow this report graph; default copies share and implicit moves can empty the source. |
| failure | Invalid binding/count/access/allocation errors propagate; no recovery wrapper. |
| cost | Fixed shared retention; final release can destroy substantial retained model/proof graphs. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../../src/observability/query_explain.cpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/observability.md](../../../../../observability.md) |
