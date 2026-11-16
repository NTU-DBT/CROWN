# `include/crown/frontend/sql_aggregate.hpp` — block usage map

[Source](../../../../../../include/crown/frontend/sql_aggregate.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare immutable original-SQL/source/kernel binding with physical-origin decoding; no executable plan or recovery authority.

Snapshot SHA-256: `b1117d58bf879fdf96d430a29e0d34f53bd6b4a4ee4123963b2c5124272a1e49`. 85 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../../sql_support.md), [docs/sql_parser.md](../../../../../sql_parser.md), [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_admission.md](../../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/frontend/sql_aggregate.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // One resolved physical SQL column, with separate normalized decode metadata. · [reviewed contract](#b0001) |
| [B0002 · 13–18](../../../../../../include/crown/frontend/sql_aggregate.hpp#L13) | Type/record definition: struct SqlAggregateInput | source comment (unverified): // One resolved physical SQL column, with separate normalized decode metadata. · [reviewed contract](#b0002) |
| [B0003 · 19–21](../../../../../../include/crown/frontend/sql_aggregate.hpp#L19) | Type/record definition: struct SqlAggregateIdentity |  · [reviewed contract](#b0003) |
| [B0004 · 22–25](../../../../../../include/crown/frontend/sql_aggregate.hpp#L22) | Type/record definition: struct SqlAggregateWork |  · [reviewed contract](#b0004) |
| [B0005 · 26–33](../../../../../../include/crown/frontend/sql_aggregate.hpp#L26) | Type/record definition: struct SqlAggregateBindOptions |  · [reviewed contract](#b0005) |
| [B0006 · 34–44](../../../../../../include/crown/frontend/sql_aggregate.hpp#L34) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Created only from original SQL/catalog/options through actual row/aggregate · [reviewed contract](#b0006) |
| [B0007 · 45–45](../../../../../../include/crown/frontend/sql_aggregate.hpp#L45) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns bool(data_) · [reviewed contract](#b0007) |
| [B0008 · 46–70](../../../../../../include/crown/frontend/sql_aggregate.hpp#L46) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Cold provenance: occurrence-order original references -&gt; canonical inputs. · [reviewed contract](#b0008) |
| [B0009 · 71–71](../../../../../../include/crown/frontend/sql_aggregate.hpp#L71) | Callable definition: explicit SqlAggregateProgram(std::shared_ptr&lt;const Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0009) |
| [B0010 · 72–85](../../../../../../include/crown/frontend/sql_aggregate.hpp#L72) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Parser/JSON/upb/deparser/cold binder workspace follows existing frontend · [reviewed contract](#b0010) |

## B0001

[Lines 1–12](../../../../../../include/crown/frontend/sql_aggregate.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare resolved physical-column grouping identity separately from actual value decoding. |
| inputs / outputs | Imports actual factories/types and documents the SQL-origin/value boundary. |
| invariants | Equal native outputs do not authorize collapsing distinct SQL grouping references; no edited descriptor admission route. |
| ownership | Declarations alone create no program/payload owner. |
| failure | No executable failure handling in these imports/comments. |
| cost | No runtime work from scaffolding. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../../include/crown/frontend/aggregate.hpp) |

## B0002

[Lines 13–18](../../../../../../include/crown/frontend/sql_aggregate.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlAggregateInput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one genuine physical SQL column origin and a separate normalized decoder. |
| inputs / outputs | SqlType, BoundColumn occurrence/column, representative source ordinal and field-or-constant descriptor. |
| invariants | Grouping uses origin+complete type; equal payload/presence or shared NULL slots may repeat for different origins. Same-origin aliases share one record. |
| ownership | Origin/descriptor are inline values; actual source program/fact owns borrowed payload and constants. |
| failure | Public record alone grants no opaque program or live source authority. |
| cost | One input record per distinct physical origin/type; native payload bytes are borrowed, not cloned. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../../include/crown/frontend/aggregate.hpp) |

## B0003

[Lines 19–21](../../../../../../include/crown/frontend/sql_aggregate.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlAggregateIdentity {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate original/catalog/source/kernel/decode/whole-binding identities. |
| inputs / outputs | Six fixed lowercase SHA-256 arrays populated by the real factory. |
| invariants | Original SQL bytes and actual derived source SQL have distinct meanings; hashes grant no checked tree/plan authority. |
| ownership | Inline arrays belong to immutable Data. |
| failure | Only the factory populates the opaque program; this public record is not a deserialize constructor. |
| cost | Six fixed 64-byte arrays. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp) |

## B0004

[Lines 22–25](../../../../../../include/crown/frontend/sql_aggregate.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlAggregateWork {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the actual extra genuine origin binding separately from existing selected work. |
| inputs / outputs | composition, origin_binding, source_normalization and kernel_binding uint64 counters. |
| invariants | origin_binding is BoundSql.work for the extra bind; real row factory internal binding consumption is still not exposed; counters do not measure full cold CPU/memory. |
| ownership | Inline report retained by immutable Data. |
| failure | No work grant/refill or fallback is supplied by this record. |
| cost | One additional uint64 in this new, unadopted composition API. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/oom-contract.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/receiving-findings.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp), src/frontend/bind.cpp:270-285,396-456,550-574, src/frontend/sql_rows.cpp:438-447,559-568, [src/frontend/aggregate.cpp](../../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../../sql_aggregate_binding.md), [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../../include/crown/frontend/aggregate.hpp) |

## B0005

[Lines 26–33](../../../../../../include/crown/frontend/sql_aggregate.hpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SqlAggregateBindOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure existing authentic source/kernel factories and explicit composition limits. |
| inputs / outputs | Nested SqlRowsBindOptions, AggregateBindOptions, ParseLimits, selected work, derived SQL cap and standalone receiving bytes. |
| invariants | _into keeps one supplied receiver; nested standalone memory options are not refills; no custom/fixed upb allocator is installed. |
| ownership | Options borrow synchronously; parameters are validated/frozen by actual source factory and binding image. |
| failure | Actual source/kernel/parser/composition rejection stays explicit; aggregate argument parameters remain unsupported. |
| cost | Fixed settings plus caller-owned parameter declarations/values. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../../src/frontend/aggregate.cpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp) |

## B0006

[Lines 34–44](../../../../../../include/crown/frontend/sql_aggregate.hpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text

// Created only from original SQL/catalog/options through actual row/aggregate
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose an immutable original-SQL binding handle and same/foreign-account freeze operation. |
| inputs / outputs | Actual bind result or freeze of an actual handle returns original SQL, source/kernel handles, decode inputs/origins, identity/binding image, static source weight, work and account metadata. |
| invariants | Only the genuine SQL factory creates descriptors. Freeze preserves identities and historic compiler work; it creates no checked source tree, plan proof, descriptor-DTO import or recovery authority. |
| ownership | Copies share immutable owner; same-account freeze shares. Foreign freeze copies/rebases retained strings, arrays, decoder and source/kernel handles into receiver; borrowed spans/views need a surviving handle. |
| failure | Parser/compiler diagnostics remain factory results; account/copy failures propagate. Freeze performs no parse or bind. |
| cost | O(1) same-owner share; cold metadata copy and receiver-account allocations on foreign freeze. No update-path instrumentation. |
| Design | [docs/sql_aggregate_binding.md](../../../../../sql_aggregate_binding.md), [include/crown/frontend/aggregate.hpp](../../../../../../include/crown/frontend/aggregate.hpp), [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [src/frontend/sql_aggregate.cpp](../../../../../../src/frontend/sql_aggregate.cpp) |

## B0007

[Lines 45–45](../../../../../../include/crown/frontend/sql_aggregate.hpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test opaque composition handle presence. |
| inputs / outputs | Returns bool(data_). |
| invariants | A valid empty-width binding is still nonempty; default/moved-from pointer absence is false. |
| ownership | Reads shared Data pointer without copying its payload. |
| failure | Noexcept and nonallocating. |
| cost | Constant. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp) |

## B0008

[Lines 46–70](../../../../../../include/crown/frontend/sql_aggregate.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] std::string_view original_sql() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare borrowed actual-program/decode/provenance views and explicit static-source bootstrap information. |
| inputs / outputs | Getters expose original SQL, actual source/kernel handles, head arity, canonical inputs/reference mapping, identities, CBOR binding, static 0/1 marker, work and account. |
| invariants | Views require a surviving lvalue handle; rvalue view calls are deleted. Static marker is only for actual zero-occurrence sources and is not permission for arbitrary row injection. |
| ownership | References/spans borrow immutable Data; copied program handles retain their real factory metadata independently. |
| failure | Empty handles reject through data(); no accessor installs source/session/recovery behavior. |
| cost | Constant getters; no full state/output cloning. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp) |

## B0009

[Lines 71–71](../../../../../../include/crown/frontend/sql_aggregate.hpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  explicit SqlAggregateProgram(std::shared_ptr<const Data> value) noexcept : data_(std::move(value)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt privately assembled immutable composition Data. |
| inputs / outputs | shared_ptr&lt;const Data&gt; moves into the handle. |
| invariants | Only friend SqlAggregateCompiler can invoke this boundary after both actual factories and binding checks succeed. |
| ownership | Transferred shared owner retains original/source/kernel/decode and receiving account. |
| failure | Noexcept pointer move; all allocation occurred before it. |
| cost | Constant. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../../src/frontend/aggregate.cpp), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/text.hpp](../../../../../../include/crown/resource/text.hpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp) |

## B0010

[Lines 72–85](../../../../../../include/crown/frontend/sql_aggregate.hpp#L72); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const Data& data() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose original-SQL factory signatures without editable descriptor admission. |
| inputs / outputs | Public bind_sql_aggregate\[_into\](SQL,Catalog,Options) returns opaque handle or existing BindingDiagnostic shape. |
| invariants | No BoundSql/program-data/raw-row constructor or public prior-weight bypass exists; source parameters and unsupported kernel parameters are explicitly distinct. |
| ownership | data_ shares const Data; cold workspace ends with factory call; retained metadata uses the receiver. |
| failure | SQL diagnostics preserve existing style; parser-contract/allocation failures can propagate. |
| cost | Cold parse/derive/bind work; no runtime update loop is introduced. |
| Design | [build/verification/w06-sql-aggregate-compiler-repair-v2/design.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/design.md), [build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md](../../../../../../build/verification/w06-sql-aggregate-compiler-repair-v2/private-contribution-port.md), [build/verification/w06-contract-assessment-v1/assessment.md](../../../../../../build/verification/w06-contract-assessment-v1/assessment.md), Refactor.md:1317-1327, [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/aggregate.hpp](../../../../../../include/crown/frontend/aggregate.hpp), [src/frontend/sql_rows.cpp](../../../../../../src/frontend/sql_rows.cpp), [src/frontend/aggregate.cpp](../../../../../../src/frontend/aggregate.cpp), Refactor.md:1325-1333, [docs/sql_aggregate_binding.md §Usage and authority](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Group identity and nullable decoding](../../../../../sql_aggregate_binding.md), [docs/sql_aggregate_binding.md §Scope and identity](../../../../../sql_aggregate_binding.md), [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp) |
