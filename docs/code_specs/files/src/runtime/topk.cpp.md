# `src/runtime/topk.cpp` — block usage map

[Source](../../../../../src/runtime/topk.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Collect genuine SQL outputs, sort by explicit keys and identity, and return a compact exact prefix without query-update state.

Snapshot SHA-256: `63ede3c51343db1f2b94e92b6afb6504751a5895fab47ffeb20e43e28acedbac`. 146 lines partitioned into 19 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [topk](../../../subsystem_contracts.md#topk). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/aggregates.md](../../../../aggregates.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/runtime/topk.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // One balance is borrowed by every comparator copy and the complete selection. · [reviewed contract](#b0001) |
| [B0002 · 14–22](../../../../../src/runtime/topk.cpp#L14) | Type/record definition: struct Budget | source comment (unverified): // One balance is borrowed by every comparator copy and the complete selection. · [reviewed contract](#b0002) |
| [B0003 · 23–24](../../../../../src/runtime/topk.cpp#L23) | Explanatory comments or spacing. | source comment (unverified): // Admission runs even for k=0, before opening a producer or retaining candidates. · [reviewed contract](#b0003) |
| [B0004 · 25–33](../../../../../src/runtime/topk.cpp#L25) | Callable definition: void validate(std::span&lt;const Key&gt; order, std::size_t fields, Budget& budget) | calls take, Error; 1 loop sites; source comment (unverified): // Admission runs even for k=0, before opening a producer or retaining candidates. · [reviewed contract](#b0004) |
| [B0005 · 34–36](../../../../../src/runtime/topk.cpp#L34) | Explanatory comments or spacing. | source comment (unverified): // Present values inherit the genuine schema's exact scalar domain. Charge both · [reviewed contract](#b0005) |
| [B0006 · 37–48](../../../../../src/runtime/topk.cpp#L37) | Callable definition: std::strong_ordering compare(const Cell& left, const Cell& right, NullOrder nulls, Budget& budget) | calls take, size; returns std::strong_ordering::equal; nulls == NullOrder::first ? std::strong_ordering::less : std::strong_o…; source comment (unverified): // Present values inherit the genuine schema's exact scalar domain. Charge both · [reviewed contract](#b0006) |
| [B0007 · 49–51](../../../../../src/runtime/topk.cpp#L49) | Explanatory comments or spacing. | source comment (unverified): // Identity breaks rank ties without insertion-order, source-witness or pointer · [reviewed contract](#b0007) |
| [B0008 · 52–68](../../../../../src/runtime/topk.cpp#L52) | Callable definition: bool less(const Entry& left, const Entry& right, std::span&lt;const Key&gt; order, Budget& budget) | calls take, view, compare, std::min; returns relation &gt; 0; relation &lt; 0; 2 loop sites; source comment (unverified): // Identity breaks rank ties without insertion-order, source-witness or pointer · [reviewed contract](#b0008) |
| [B0009 · 69–71](../../../../../src/runtime/topk.cpp#L69) | Explanatory comments or spacing. | source comment (unverified): // The producer may decode one extra tuple to discover this bound. It remains · [reviewed contract](#b0009) |
| [B0010 · 72–77](../../../../../src/runtime/topk.cpp#L72) | Callable definition: void append(Candidates& candidates, Entry entry, Limits limits, Budget& budget) | calls size, Error, take, push_back; growth push_back; source comment (unverified): // The producer may decode one extra tuple to discover this bound. It remains · [reviewed contract](#b0010) |
| [B0011 · 78–80](../../../../../src/runtime/topk.cpp#L78) | Explanatory comments or spacing. | source comment (unverified): // Sorting mutates private owned handles only. A thrown comparison needs no undo · [reviewed contract](#b0011) |
| [B0012 · 81–104](../../../../../src/runtime/topk.cpp#L81) | Callable definition: void select(Snapshot& result, Candidates& candidates, std::span&lt;const Key&gt; order, Budget& budget) | calls std::sort, begin, end, less; returns less(a, b, order, budget); growth push_back, reserve; 2 loop sites; source comment (unverified): // Sorting mutates private owned handles only. A thrown comparison needs no undo · [reviewed contract](#b0012) |
| [B0013 · 105–106](../../../../../src/runtime/topk.cpp#L105) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0013) |
| [B0014 · 107–110](../../../../../src/runtime/topk.cpp#L107) | Callable definition: topk::Snapshot::Snapshot(const resource::MemoryAccount& account, std::uint64_t epoch, std::uint64_t k, Program source) : sequence… | calls sequence, requested_k, program, std::move · [reviewed contract](#b0014) |
| [B0015 · 111–111](../../../../../src/runtime/topk.cpp#L111) | Explanatory comments or spacing. |  |
| [B0016 · 112–127](../../../../../src/runtime/topk.cpp#L112) | Callable definition: topk::Snapshot snapshot_topk(const SqlRowsRuntime& owner, std::span&lt;const Key&gt; order, std::uint64_t k, Limits limits) | calls ready, Error, program, validate; returns result; result; 1 loop sites; source comment (unverified): // Release the native reader lease before sorting the owned snapshot. · [reviewed contract](#b0016) |
| [B0017 · 128–128](../../../../../src/runtime/topk.cpp#L128) | Explanatory comments or spacing. |  |
| [B0018 · 129–145](../../../../../src/runtime/topk.cpp#L129) | Callable definition: topk::Snapshot snapshot_topk(const SqlAggregateRuntime& owner, std::span&lt;const Key&gt; order, std::uint64_t k, Limits limits) | calls ready, Error, program, validate; returns result; result; growth reserve; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 146–146](../../../../../src/runtime/topk.cpp#L146) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0019) |

## B0001

[Lines 1–13](../../../../../src/runtime/topk.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:c3c6a14ca03684b3adbcc1b92363880a4db2d6a711878039f08ba085c15388ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up the private exact top-k implementation and account-funded candidate representation. |
| inputs / outputs | Headers, namespace aliases and source guidance make Candidates an existing OutputVector&lt;Entry&gt;. |
| invariants | Helpers are private to this translation unit. No ordinary query target links back to this optional operator. |
| ownership | Aliases/namespace setup hold no mutable runtime singleton; each call later creates its own local budget/vector. |
| failure | No runtime operation occurs in this scaffolding; Error diagnostics retain existing ordinary allocation conventions. |
| cost | Compile-time setup; producer work, allocation and row moves are explicitly excluded from the later selected logical-work counter. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0002

[Lines 14–22](../../../../../src/runtime/topk.cpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L22:sha256:b3225281dcb2d465ffa406de03140b6493a77ad7130d298712823afbcaa58662
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit one finite shared top-k balance and accumulate its actual charged work. |
| inputs / outputs | take(amount) accepts a uint64 amount, decreases remaining and increases metrics.work on success. |
| invariants | metrics.work + remaining equals the original finite balance. The check precedes subtraction, so work and each charged phase statistic cannot silently overflow or refill. |
| ownership | Budget is local to one operator; comparator copies borrow it by reference and do not copy/reset the allowance. |
| failure | amount above remaining throws topk_work_limit before debit. Ordinary Error diagnostic/exception storage is outside the query account; unwinding needs no new state owner. |
| cost | O(1) integer check/debit per charge; it is selected logical accounting rather than CPU measurement. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 23–24](../../../../../src/runtime/topk.cpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L24:sha256:8b76209429d7a081046dfddb37d6a3ca310bcebc39f8abfdfabbde9f330ae5b3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document pre-producer key admission, including the zero-result call. |
| inputs / outputs | Comment explains when validate is used; it neither examines the span nor opens an owner. |
| invariants | Actual validation below runs for k=0 and for positive k; the note does not certify arbitrary caller span lifetime. |
| ownership | No runtime ownership in this prose region. |
| failure | No executable error handler or validation mechanism is added by the comment. |
| cost | Prose only; validation work belongs to validate. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 25–33](../../../../../src/runtime/topk.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L33:sha256:dfe7ff87b42ff6700c20c25dba641672d7e47c701d0945d5dad451419429f517
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate each requested output index and the two enum domains before collection. |
| inputs / outputs | Borrowed Key span, genuine rendered-field count and shared Budget in; normal return admits every supplied key. |
| invariants | One unit is charged before each key is examined. Empty order is valid; repeated keys are permitted. Fields are zero-based and bounded by the genuine schema. |
| ownership | No metadata is retained or mutated. Caller keeps the rank span alive for the whole synchronous operator. |
| failure | Insufficient work can fail before a later invalid key is inspected. Invalid field/direction/NULL placement throws topk_order; no producer/candidate has opened. |
| cost | O(number of keys) fixed checks/charges; no dedup map, allocation, sorting or producer work. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 34–36](../../../../../src/runtime/topk.cpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L36:sha256:5ad9f6e70952f99fe946696353cd6e4f5137e99cb6e8e66569874b9837beb1d3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the exact scalar and string-extent contract used by cell comparison. |
| inputs / outputs | Source prose introduces compare, including NULL payload avoidance and complete string charges. |
| invariants | The genuine output/key schema supplies compatible present scalar kinds; this note is not independent type admission. |
| ownership | No owned values or views are created by the comment. |
| failure | No executable failure boundary; compare implements budget checks. |
| cost | Prose only; actual scalar/string costs are described in compare. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 37–48](../../../../../src/runtime/topk.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L48:sha256:094ffb40653c55dc5a1280458a107f89681f7f09e300134e03860712e5e1d781
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two nullable cells under explicit NULL placement and the genuine exact scalar order. |
| inputs / outputs | Borrowed compatible Cell references, a valid NullOrder and shared Budget produce a strong ordering. |
| invariants | NULL/NULL is equal and NULL placement does not depend on ASC/DESC. Present values use native int/Boolean/date/InlineDecimal and admitted valid-UTF8 SQL TEXT binary-byte order. Genuine schemas make both present alternatives compatible. |
| ownership | Cells borrow owning candidate Tuple backing for the comparator call only; no owning Row, string conversion or payload copy is made. |
| failure | Charge one field unit first; charge both complete string lengths before comparing text. Budget failure propagates on private state. Violating the internal same-schema precondition is not an admitted raw-row API. |
| cost | O(1) bounded scalar work or O(compared string/decimal extent), with a conservative charge of both full strings. It does not count allocator/stack/CPU instructions. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 49–51](../../../../../src/runtime/topk.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L51:sha256:994bf0d967107bc39b67d85ab123830f63cccac03f915670aedb9f950ec03a37
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain deterministic identity-only tie resolution after requested keys. |
| inputs / outputs | Usage note for less: source occurrence, insertion and pointer order are not tie keys. |
| invariants | Distinct aggregate keys remain distinct even when values project equally. Runtime proof is the comparator implementation and genuine producer identity invariant. |
| ownership | No runtime object or allocation is held by prose. |
| failure | No validation or theorem authority is created by the comment. |
| cost | Prose only; key/identity comparisons carry their actual field/byte cost. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 52–68](../../../../../src/runtime/topk.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L68:sha256:7b53947e5e1d27c1873a0fda81203250ca54ef65cf419f7b1932303fbae8f836
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order complete candidate identities by requested rendered fields followed directly by identity. |
| inputs / outputs | Two genuine same-family Entries, admitted Key span and one shared Budget return a strict less-than relation. |
| invariants | Charge a comparison unit. Reverse only unequal present rank values for DESC; leave NULL order explicit. Then lexicographically compare full identity ASC NULLS FIRST, including empty group keys, without an extra undeclared value-tie order. |
| ownership | Views borrow live candidate-owned Tuple backing. Only local Budget metrics mutate; no query row, source witness, owner identity or pointer is retained. |
| failure | A nested cell/budget failure propagates out of local std::sort. No comparator copy owns a replenished allowance and no catch/rollback framework is added. |
| cost | O(visited requested fields + visited identity fields + actual scalar/string extents) per call. Complete sorting uses ordinary O(N log N) comparator calls, not constant-delay CROWN work. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 69–71](../../../../../src/runtime/topk.cpp#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L71:sha256:dfbc0214b3dcc9e8964b356364e855f9a33a265e7c0c378e9c5cc50e9a1fa264
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain how row candidate excess is discovered without silently truncating the input. |
| inputs / outputs | Source note permits the genuine producer to return one additional owned tuple before append refuses it. |
| invariants | The limit is on compressed identities. Producer/account coverage of that transient does not make its decoding free or an expanded-bag admission. |
| ownership | The temporary tuple is locally owned and is released when the failed append unwinds. |
| failure | The note itself neither admits memory nor catches producer errors. |
| cost | Prose only; producer decoding, account allocation and append charges stay explicit. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 72–77](../../../../../src/runtime/topk.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L77:sha256:b0cbd0e42ebc8b31c92df68d09725b935c8713f2a96f8e09deb8b43215a83ea1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one genuine compressed candidate under the candidate cap and shared work grant. |
| inputs / outputs | Local candidate vector, owning Entry, Limits and Budget in; successful push retains the entry and increments candidate metrics. |
| invariants | Check cap before charging/push. Increment candidates only after a successful push. Genuine row weights are positive and aggregate entries have unit multiplicity. |
| ownership | Entry payload ownership moves into the same-account OwnerAllocator vector; private temporary ownership remains safe if cap/allocation admission fails. |
| failure | Candidate excess throws topk_result_limit; work or account/allocation failure propagates. Aggregate snapshot may reject its group cap earlier with aggregate_result_limit. |
| cost | Amortized vector growth plus O(1) handle/counter work per compressed entry; growth capacity and allocation framing consume the original account, never a new grant. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0011

[Lines 78–80](../../../../../src/runtime/topk.cpp#L78); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L80:sha256:d667da44e0f4357e92286bce09ab34aa9604f552a96bde2272f2d9b437e3c03a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe why sorting private owned handles needs no new query rollback mechanism. |
| inputs / outputs | Source note introduces select, which operates after producer closure on local candidates. |
| invariants | The note relies on the actual call scopes and owning vector handles; it does not assert restoration of observations or allocation history. |
| ownership | RAII owns the candidate/result vectors; no persistent query state has been published by top-k. |
| failure | The comment adds no handler. A thrown comparison unwinds private state normally. |
| cost | Prose only; sorting, selection and teardown costs remain charged/described separately. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 81–104](../../../../../src/runtime/topk.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L104:sha256:e91866fd9447fc8061f768c5dc81f50c6ff51a3ff36ef451555e6448a823383c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sort the complete compressed snapshot and form its exact k-copy prefix in compact result storage. |
| inputs / outputs | Local Snapshot/Candidates, admitted rank span and shared Budget in; final sorted Entry vector, selected_rows and metrics out. |
| invariants | std::sort comparator captures Budget by reference. Count selected identities using remaining -= min(remaining,multiplicity), charge each selection before final allocation, then copy exactly that prefix with bounded weights. selected_rows = requested_k - remaining cannot overflow. |
| ownership | The working vector remains private. Final entries share immutable identity/value Tuple handles through a fresh OwnerAllocator vector; N candidate slots are not retained in a small-k result. |
| failure | Comparison/work/reserve/push failure cannot return a partial Snapshot or alter the source. Valid moved handles destruct normally; no extra inverse owner is necessary. |
| cost | O(N log N) comparator calls plus O(M) selection/copy and vector storage for M selected identities. Actual field/string comparison extents, allocation, moves, producer costs and destruction are separate; huge multiplicities are never expanded. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0013

[Lines 105–106](../../../../../src/runtime/topk.cpp#L105); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L106:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the translation-unit-private helper namespace before the public definitions. |
| inputs / outputs | Namespace closing syntax separates private implementation helpers from public constructor/overloads. |
| invariants | No helper state escapes and no shared mutable global runtime state is introduced. |
| ownership | Syntax only; no owner or borrow. |
| failure | No runtime failure behavior. |
| cost | No runtime work or storage. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0014

[Lines 107–110](../../../../../src/runtime/topk.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L110:sha256:80a159af7eba5264dd5f2f22232c71f0704b52627ca315e4a0f67e67284feddf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a plain owning result with its original account, epoch, request and genuine family metadata. |
| inputs / outputs | MemoryAccount, sequence, uint64 k and Program handle initialize Snapshot and its empty output-buffer vector. |
| invariants | selected_rows and metrics start at zero. Constructor creates presentation ownership; it does not authenticate arbitrary public program fields or import native state. |
| ownership | Program moves/copies retain immutable metadata. OwnerAllocator retains the supplied original account and default query attribution; no candidate/result allocation occurs until reserve/push. |
| failure | An invalid account can fail allocator construction. Existing diagnostic/exception storage conventions remain separate; the constructor adds no retry or query mutation. |
| cost | O(1) handle/allocator metadata work, with no producer opening or heap payload allocation for the empty result. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0016

[Lines 112–127](../../../../../src/runtime/topk.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L127:sha256:b7598cb63b0ca9d41c5b1f4873041d8104bff5595d4f4b9364319f008e0e564e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect, rank and select the current genuine SQL row/bag/DISTINCT/EXISTS snapshot. |
| inputs / outputs | Ready SqlRowsRuntime, borrowed keys, k and finite limits yield one owning topk Snapshot with original program and committed sequence. |
| invariants | Check readiness then key admission. k=0 returns before producer creation. Otherwise one finite native cursor scans every compressed row or fails; full output tuple is identity and selected weight preserves exact bag/DISTINCT/EXISTS semantics. SQL TEXT validity is established by existing genuine source/binder admission; top-k does not broaden that domain. |
| ownership | program().account() is the runtime receiving account because SqlRowsRuntime freezes its genuine program into the owner. Braced entry initialization copies the identity handle before moving the same tuple to values. Cursor scope releases the reader lease before sorting. |
| failure | Busy/key/work/candidate/producer/account failures unwind local cursor/candidates/result. Source rows and committed sequence do not change; existing cursor observations and cumulative/peak account counters may record attempts. |
| cost | Complete existing row-cursor traversal/decoding plus O(N) candidate handles and ordinary full sorting/selection. One extra tuple may reveal a candidate-cap excess; retained final metadata is O(M). No update-path rank state is installed. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0018

[Lines 129–145](../../../../../src/runtime/topk.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L145:sha256:87ca0b71c2d1b507b7e097eadc56572b8245aa9e121528228dc047bd0f51e38c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect, rank and select genuine rendered SQL aggregate groups while preserving full grouping identity. |
| inputs / outputs | Ready SqlAggregateRuntime, borrowed keys, k and finite limits yield one owning topk Snapshot with genuine aggregate program and sequence. |
| invariants | Validate rendered output indices, return immediately for k=0, otherwise one existing bounded snapshot supplies all groups. Every candidate has unit weight, complete group key identity and actual rendered values; global-empty output remains present. |
| ownership | Use owner.account() for candidates/result. Move key/value owning handles from the scoped aggregate image into private entries; the image vector is destroyed before sorting and selected handles survive owner teardown. |
| failure | Existing snapshot group/render caps can fail before append, including aggregate_result_limit. All later work/memory/comparison failures release private state without source/native/group publication or sequence change. |
| cost | Existing eager O(G) group snapshot/render work and transient image plus O(N) candidate metadata, O(N log N) comparisons and O(M) retained output. No joined-row ledger, cached ranking or per-update hook. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |

## B0019

[Lines 146–146](../../../../../src/runtime/topk.cpp#L146); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L146:sha256:024a31d07f0690bcfeef2cd00cf111a56223bd48741eae7b548b6bc9143d9111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the public runtime namespace for the optional top-k implementation. |
| inputs / outputs | Namespace closing syntax ends the implementation translation unit. |
| invariants | No registration callback, static owner or additional query state is created. |
| ownership | Syntax only; no object lifetime. |
| failure | No executable failure behavior. |
| cost | No runtime cost. |
| Design | [docs/topk.md](../../../../topk.md), [Refactor.md](../../../../../Refactor.md) |
