# C05 version-1 diagnostic and artifact bytes

This is the field-order specification for the excluded implementation's private
byte visitors. They return diagnostic bytes only. They cannot admit a proof,
construct a Selection/CurrentSelection, or install an artifact. Public selection
first requires actual P07/P08/C02 handles and supported request values. There is
no wire decoder or import API for these bytes.

## Primitive frames

All quoted tags below denote single ASCII bytes. `be64(n)` is exactly eight
big-endian bytes, unsigned. Strings contain their original bytes, including NUL,
0x80 and 0xff, with no escaping. Counts/IDs use their uint64-representable native
domain. All sequences retain order/multiplicity; sets iterate stable ID order.

| Notation | Bytes |
| --- | --- |
| U(n), an unsigned scalar or ID | `U` + be64(n) |
| I(n), signed int64 | `I` + be64(n modulo 2^64) |
| E(n), enum underlying value | `E` + be64(n) |
| B(false), B(true) | `B` + one byte 0 or 1 |
| S(bytes) | `S` + be64(byte length) + raw bytes |
| R(name) | `R` + S(name) |
| absent optional | `P` + byte 0 |
| present optional(value) | `P` + byte 1 + encoded value |
| sequence(values) | `A` + be64(element count) + each encoded value |
| IDs(values) | sequence of U(id.value) |

The initial domain is an unframed literal ASCII prefix ending in `;1;`.
No separator is appended between subsequent framed fields. Optional callbacks
encode their contained value without another wrapper unless listed. A variant
uses the listed U(index), followed by its payload in the enclosing record.

## Diagnostic entry domains and exact records

| Entry | Prefix | Following record |
| --- | --- | --- |
| scalar_binding_record | `CROWN-SELECTION-SCALAR;1;` | Value |
| tree_binding_record | `CROWN-SELECTION-TREE;1;` | RawTree |
| program_binding_record | `CROWN-SELECTION-PROGRAM;1;` | NormalizedSql |
| core_binding_record | `CROWN-SELECTION-CORE;1;` | Core |

Fields in the following tables are written strictly left to right. Unmentioned
padding, addresses, capacities and C++ object representations never enter.

| Record | Fields after its R(name) |
| --- | --- |
| Value: `value` | U(Value variant index); payload below |
| Core: `candidate-binding-v2` | S(complete unchanged P07 v2 Catalog/Query binding bytes) |
| Catalog: `catalog-with-empty-query` | Core(catalog, empty Query) |
| RawTree: `raw-tree` | optional U(root.value); sequence RawNode; optional IDs(claimed_connex); optional U(claimed_native_height) |
| RawNode: `raw-node` | S(id); E(kind); sequence U(scope variable.value); IDs(children); optional U(occurrence); optional sequence U(claimed_separator variable.value) |
| SqlType: `sql-type` | E(kind); B(nullable); optional [U(decimal.precision), U(decimal.scale)] |
| BindLimits: `bind-limits` | optional U(work_limit); U(expression_limit); U(recursion_limit) |
| NormalizeLimits: `normalize-limits` | optional U(work_limit) |

Value index 0 writes I(int64), index 1 writes S(string), index 2 writes B(bool),
index 3 writes I(Date.epoch_days()), and index 4 writes S(Decimal.to_string()).
The Decimal formatter is the existing canonical public formatter: equivalent
spellings encode identically, negative zero is canonical zero, sign and
significant scale remain in canonical text. A Date and its integer day count
remain distinct through the Value variant tag. SQL NULL is an absent optional
Value; it is not one of these five Value alternatives.

| Record | Ordered fields |
| --- | --- |
| BoundSql: `bound-sql` | S(source); Catalog(original catalog); sequence SqlType(parameters); E(semantics); optional E(inner_semantics); E(wrapper); S(wrapper_alias); sequence BoundOccurrence; sequence BoundExpression; IDs(predicates); sequence [S(output.name), U(output.expression.value)]; BindLimits; U(work) |
| BoundOccurrence: `bound-occurrence` | U(table.value); S(alias); sequence S(column_names); optional U(location); B(include_descendants) |
| BoundExpression: `bound-expression` | SqlType(type); U(node variant index); node payload below; optional U(location) |
| OccurrenceAdapter: `occurrence-adapter` | U(occurrence.value); U(base.value); IDs(predicates); IDs(non_null_columns); sequence [U(equal.left.value), U(equal.right.value)]; sequence optional U(column_classes variable.value); sequence [U(projection.variable.value), U(projection.expression.value)]; IDs(program); sequence [U(constant.column.value), Value(constant.value)] |
| NormalizedOutput: `normalized-output` | S(name); SqlType(type); U(output variant index); U(core.column) for index 0 or Value(constant.value) for index 1 |
| NormalizedSql: `normalized-sql` | BoundSql(binding); sequence optional Value(parameters); sequence optional Value(constants); Core(core_catalog, core); sequence OccurrenceAdapter; sequence IDs(base_routes); sequence NormalizedOutput; NormalizeLimits; U(work); U(schema_version) |

BoundExpression node index 0 writes U(column.occurrence.value), U(column.column.value).
Index 1 writes optional Value(literal.value). Index 2 writes U(parameter.number).
Index 3 writes E(operation), IDs(arguments). Bound fields such as source offsets,
original output names, producer limits and recorded work are deliberately
preserved, even when they do not change the normalized CQ.

## Physical source and artifact frames

The source-equivalence domain is `CROWN-SELECTION-SOURCE;1;`. It writes one
PhysicalSource record. The compiled-input check domain is
`CROWN-SELECTION-COMPILED-INPUT;1;`; it writes PhysicalSource followed by RawTree.
Both comparisons use full framed bytes, not a digest.

| Record | Ordered fields |
| --- | --- |
| PhysicalOptions: `physical-options` | S(policy.arithmetic); S(policy.planner); S(policy.optimization); S(policy.cost_model); optional U(limits.work_limit); optional U(limits.identity.work_limit) |
| PhysicalSource: `physical-source` | Core(plan catalog, plan query); Catalog(physical source catalog); optional NormalizedSql(program); PhysicalOptions |
| CandidateContext: `candidate-context` | E(updates); S(arithmetic); S(planner); S(optimization); S(cost_model); S(canonicalization) |
| RankingLimits: `ranking-limits` | U(work), U(cells), U(binding_key_bytes), U(payload_bytes), U(lowering_work), U(identity_work), U(binding_replay_work), U(normalization_work), U(candidates), U(score_bits); optional I(active_time nanoseconds) |
| Request: `selection-request` | E(policy); E(fallback); E(family); E(layout); E(indexes); U(constraint index); no payload for monostate, S(maximum) for slot constraint; RankingLimits |

DirectCQ's PhysicalSource uses the original proof's Catalog/Query and that
Catalog as the physical catalog, no normalized program, and requested options.
A PhysicalBasis uses its actual complete plan source/options. Source equivalence
omits the owner's current tree; the separately selected raw tree is mandatory
for compiled artifact equality.

`cache_binding` starts `CROWN-SELECTION-ARTIFACT;1;`, then writes:

1. R(`implementation-domain`), U(1), U(2), U(1), U(1), S(`crown-lower-v1`),
   U(1), U(1), U(2), S(`reference_ordered_v1`). These fixed v1 namespace values
   bind the C05 decision, P07 binding, C02 result/arithmetic, lower, physical,
   identity and normalized-format domains; layout/index choices also enter Request.
2. Core(original proof binding), U(required checked height), CandidateContext,
   E(CandidateFamily), B(family_exhausted), then a sequence of
   [S(full structural key), U(checked height), RawTree] for every retained member
   in snapshot order.
3. R(`explicit-source`), U(Source variant index), PhysicalSource, then RawTree
   of the basis only for the PhysicalBasis alternative.
4. Request, R(`decision`), E(effective policy), U(fallback mask), U(selected index),
   S(selected full structural key), RawTree(selected), sequence
   [U(candidate index), E(eligibility)].
5. E(origin: absent=0, as_of=1, physical=2, delta=3, session=4), optional Evidence.

Evidence is R(`ranking-evidence`) followed by all fields below:

| Group | Ordered fields |
| --- | --- |
| Identity unsigned values | owner, epoch, interval_start, reset, configuration, segment, format, collection_mode, max_cells, period, offset, detail_budget, each U |
| Modes | B(delta_owner), then U(requested_mode), U(resolved_mode), U(requested_completion), U(resolved_completion), U(live_maintenance), U(view) |
| Boundary flags | B(pending), B(reset_saturated), B(configuration_saturated), B(segment_saturated) |
| Weights | sequence [U(table.value), U(inserts), U(erases), U(changed), U(noop)] |
| Sources | sequence [U(table.value), U(rows)] |
| Source observations | sequence [U(table.value), E(state), optional U(cardinality)] |
| Policy facts | U(denominator), U(depth_reasons), U(memory_reasons) |
| Capture configuration | R(`capture-configuration`), RankingLimits(processing_limits), E(state), B(state_requested), U(requested_components), U(returned_components), U(state_work_limit), U(state_rows_limit), U(state_keys_limit), U(state_bytes_limit), U(state_projection_width), U(state_heavy_keys), U(snapshot_descriptors), U(snapshot_cells) |

Preparation Usage and actual state-consumption counters are deliberately absent.
So are fresh session cursor/unread/diagnostic attempt-abort details, certificate
bytes/provenance, elapsed measurements, cache-use mode and retention capacities.
These exclusions cannot authorize stale proof/evidence reuse: every call has
already obtained its own typed snapshot, full assessment and actual capture when
requested. An artifact stores only its whole plan, exact key and component
payload, never these excluded records. Complete key equality is only an artifact
reuse condition. Conservative fields can reduce hit rate without weakening it.

The analytical invalidation argument and full authority boundary are retained
in the accepted [preflight cache contract](../c05-selection-preflight-proposal/CACHE_KEY.md).
The producer's mutation records and the separate independent byte-vector oracle
must be compiled/executed by root; this specification is not a claim that those
runtime checks have passed.
