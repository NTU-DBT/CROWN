# `tools/component_analysis.py` — block usage map

[Source](../../../../tools/component_analysis.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `c6d04eae147718d8a91bfbde6532238318a22cce940ec85528b6d8b0e38459ac`. 129 lines partitioned into 8 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../tools/component_analysis.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 14–27](../../../../tools/component_analysis.py#L14) | Callable definition: def exact_ratio(value): | calls require, isinstance, set, in; guard require(isinstance(value, dict) and set(value) == {'numerator', 'denominator'}, 'invalid native rat…; returns None; Fraction(*numbers); 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 28–29](../../../../tools/component_analysis.py#L28) | Explanatory comments or spacing. |  |
| [B0004 · 30–39](../../../../tools/component_analysis.py#L30) | Callable definition: def native_choice(report, keys): | calls get, require, type, len; guard require(type(index) is int and 0 &lt;= index &lt; len(keys) and keys\[index\] == key, 'native choice is out…; returns {'selected_key': key, 'availability': 'native_choice' if key is not None else 'native_unavailable', · [reviewed contract](#b0004) |
| [B0005 · 40–41](../../../../tools/component_analysis.py#L40) | Explanatory comments or spacing. |  |
| [B0006 · 42–88](../../../../tools/component_analysis.py#L42) | Callable definition: def event_choice(report, keys, height): | calls get, require, len, set; guard require(len(by_key) == len(rows) and set(by_key) &lt;= set(keys), 'event estimates contain duplicate o…; returns {'selected_key': selected, 'availability': availability,; 2 loop sites; source comment (unverified): # planner::ranking::Stop::complete. · [reviewed contract](#b0006) |
| [B0007 · 89–90](../../../../tools/component_analysis.py#L89) | Explanatory comments or spacing. |  |
| [B0008 · 91–129](../../../../tools/component_analysis.py#L91) | Callable definition: def freeze_choices(exported): | calls require, sha256, canonical, encode; guard require(exported\['kind'\] == 'b04_cold_component_planning_export', 'wrong component export kind'); returns frozen; deepcopy(frozen); 7 loop sites; source comment (unverified): # Own the nested evidence once at this cold boundary. Later caller edits to · [reviewed contract](#b0008) |

## B0001

[Lines 1–13](../../../../tools/component_analysis.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:62e664d081ba62cbb977cbe6385eaee45be8b0410d295d70cfbace5eaeb6469b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load exact-rational, canonical-export and validation helpers for the offline component selector. |
| inputs / outputs | The module exposes pure Python functions over native C02/C03 report mappings; import-time definitions create no CROWN runtime or plan. |
| invariants | This is an offline C03 forecast/choice artifact only. Importing it does not install C05 maintenance_cost or validate a query proof. |
| ownership | Python modules and Fraction/dict/list values are ordinary process-owned objects outside CROWN allocation accounts. |
| failure | Import errors prevent the offline runner from starting; helper-level malformed input failures propagate to the caller. |
| cost | One module import plus declarations; no engine update-path or runtime cost. |
| Design | [tools/component_analysis.py](../../../../tools/component_analysis.py), [examples/component-planning/main.cpp](../../../../examples/component-planning/main.cpp), [docs/verification/c03-maintenance-cost-acceptance-2026-11-10.md](../../../verification/c03-maintenance-cost-acceptance-2026-11-10.md) |

## B0002

[Lines 14–27](../../../../tools/component_analysis.py#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L27:sha256:2f0c70474f4dd5276b815651785b28bea80c397772cabd9a82724051404265f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one serialized native ratio to an exact Python Fraction. |
| inputs / outputs | Null yields no score; otherwise require exactly numerator/denominator as nonnegative integers or ASCII decimal strings, with positive denominator. |
| invariants | No float conversion. Downstream eligibility separately requires successful native estimate, issue-free terms and within-budget captured memory. |
| ownership | Fraction is ordinary Python-owned arbitrary precision; the input mapping is borrowed during conversion. |
| failure | Malformed shape/type, negative values or zero denominator raise ValueError; malformed decimal text propagates conversion failure. |
| cost | Integer parsing and Fraction reduction use arbitrary-precision conversion/GCD work proportional to numeric bit length; no CPU/input-size cap. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../src/runtime/maintenance_cost.cpp), [examples/component-planning/main.cpp](../../../../examples/component-planning/main.cpp) |

## B0004

[Lines 30–39](../../../../tools/component_analysis.py#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L39:sha256:70995ab950c39516e9c687e5ef36816557787a87839d846354aad17e084d3dfa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve one validated native C02 rank choice or explicit unavailability. |
| inputs / outputs | Native rank report and ordered family keys in; chosen key/availability plus native stop/reasons out. |
| invariants | Published index must be a built-in integer in range naming the same key. An unavailable choice cannot carry an index. |
| ownership | Output is a new ordinary Python mapping; native candidate/program ownership remains upstream. |
| failure | Index/key mismatch or index without a key raises ValueError; missing required mapping fields may raise KeyError. |
| cost | Constant indexed validation and scalar/key reads; no candidate ranking. |
| Design | [examples/component-planning/main.cpp](../../../../examples/component-planning/main.cpp), [include/crown/planner/ranking.hpp](../../../../include/crown/planner/ranking.hpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0006

[Lines 42–88](../../../../tools/component_analysis.py#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L88:sha256:e5ebdb500962361db7f28ccc7511258946b36e255c69b6b42193a9a38c2b79d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select event cost only for a complete successful family with known, issue-free, as-of in-budget scores. |
| inputs / outputs | Native event estimate, exact family keys and validated height choice in; exact-ratio winner or explicit fallback, unavailable/excluded keys, stamps and stop details out. |
| invariants | Cost choice requires stop=complete, unique nonforeign row for every family key, numeric total_ns, issues=0 and captured requested bytes within each budget. Missing/partial rows, unknown ratios/memory, nonzero issues, memory exclusion or noncomplete stop cause height fallback. A known-overbudget height candidate cannot be selected. Exact ties use structural_key. Stamps/future-memory-unknown are preserved without a freshness claim. |
| ownership | Inputs are borrowed; output dictionaries/lists/Fractions are ordinary Python values. The function retains stamp objects by reference until the outer freeze deep-copies the completed artifact. No CROWN account is used. |
| failure | Duplicate/foreign keys or malformed rows raise ValueError/field errors; incomplete native output falls back rather than becoming zero cost. |
| cost | O(E+K) map/list work and exact arbitrary-precision ratio comparisons over E estimate rows and K family keys; no general CPU or allocation bound. |
| Design | [examples/component-planning/main.cpp](../../../../examples/component-planning/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../src/runtime/maintenance_cost.cpp), [docs/verification/c03-maintenance-cost-acceptance-2026-11-10.md](../../../verification/c03-maintenance-cost-acceptance-2026-11-10.md), [tests/integration/component_analysis.py](../../../../tests/integration/component_analysis.py) |

## B0008

[Lines 91–129](../../../../tools/component_analysis.py#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L129:sha256:15eea0d66435ed572c23c7a0337ac866d0d37a5e54ec5f3848eeacb2c3ed23ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze the training-mix C03 choice summaries with export provenance before evaluation. |
| inputs / outputs | Cold component-planning export in; canonical input hash, selected/height summaries, source/catalog/training/calibration hashes, declared-input sum, candidate keys and four stats variants out. |
| invariants | Validates export kind/status, source/catalog/calibration identity hashes, nonempty unique keys, unique family IDs and exactly full/sampled/stale/absent variants. forecast_inputs sums supplied input-demand rows; it does not itself prove the exporter listed every table/operation or that measurements occurred. No held-out measurements are consumed by the selector. |
| ownership | Final deepcopy owns nested captures, stamps, calibration fit and demand values, so later parsed-export mutation cannot change the frozen result. All storage remains ordinary Python memory outside CROWN accounts. |
| failure | Identity, shape, duplicate or variant failures raise ValueError or mapping-access errors. Missing original minimum is recorded as unavailable and returns without candidate families. |
| cost | Canonical serialization/hash scale with export bytes; traversal/copy scale with families, candidates, variants and payload size. Ordinary process memory is not query-accounted. |
| Design | [examples/component-planning/main.cpp](../../../../examples/component-planning/main.cpp), [docs/verification/c03-maintenance-cost-acceptance-2026-11-10.md](../../../verification/c03-maintenance-cost-acceptance-2026-11-10.md), [build/verification/v58-b04-design-review-v1/README.md](../../../../build/verification/v58-b04-design-review-v1/README.md), [tests/integration/component_analysis.py](../../../../tests/integration/component_analysis.py) |
