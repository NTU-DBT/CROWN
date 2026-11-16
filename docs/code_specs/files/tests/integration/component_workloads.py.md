# `tests/integration/component_workloads.py` — block usage map

[Source](../../../../../tests/integration/component_workloads.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `422426ca6e636f27c8aaa13844e297962c6abfb3227b0192213b4e5657acb408`. 314 lines partitioned into 21 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../../tests/integration/component_workloads.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 26–39](../../../../../tests/integration/component_workloads.py#L26) | Callable definition: def _changed_paths(left, right, prefix=''): | calls isinstance, sorted, set, append; returns changed; \[prefix\]; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 40–41](../../../../../tests/integration/component_workloads.py#L40) | Explanatory comments or spacing. |  |
| [B0004 · 42–47](../../../../../tests/integration/component_workloads.py#L42) | Callable definition: def _arm(manifest, identifier): | calls len, AssertionError; returns found\[0\]; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 48–52](../../../../../tests/integration/component_workloads.py#L48) | declares types or opens a type body. |  · [reviewed contract](#b0005) |
| [B0006 · 53–72](../../../../../tests/integration/component_workloads.py#L53) | Callable definition: def test_fraction_rounding_ties_zero_and_eighteen_places(self): | calls Fraction, subTest, assertEqual, numeric; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 73–77](../../../../../tests/integration/component_workloads.py#L73) | declares types or opens a type body. |  · [reviewed contract](#b0007) |
| [B0008 · 78–123](../../../../../tests/integration/component_workloads.py#L78) | Callable definition: def test_cancelling_and_negative_edits_preserve_set_but_change_bag(self): | calls catalog, event, base_request, evaluate_request; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 124–124](../../../../../tests/integration/component_workloads.py#L124) | Explanatory comments or spacing. |  |
| [B0010 · 125–179](../../../../../tests/integration/component_workloads.py#L125) | Callable definition: def test_count_sum_and_average_use_exact_integer_sqlite_state(self): | calls COUNT, SUM, AVG, catalog · [reviewed contract](#b0010) |
| [B0011 · 180–180](../../../../../tests/integration/component_workloads.py#L180) | Explanatory comments or spacing. |  |
| [B0012 · 181–193](../../../../../tests/integration/component_workloads.py#L181) | Callable definition: def test_duplicate_insert_and_absent_erase_are_rejected(self): | calls catalog, event, subTest, base_request; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 194–194](../../../../../tests/integration/component_workloads.py#L194) | Explanatory comments or spacing. |  |
| [B0014 · 195–238](../../../../../tests/integration/component_workloads.py#L195) | Callable definition: def test_invalid_layer_families_and_cohort_bounds_are_rejected(self): | calls assertRaises, layered_events, operational_events, build_operational_cohorts · [reviewed contract](#b0014) |
| [B0015 · 239–239](../../../../../tests/integration/component_workloads.py#L239) | Explanatory comments or spacing. |  |
| [B0016 · 240–258](../../../../../tests/integration/component_workloads.py#L240) | Callable definition: def test_full_head_snapshot_exposes_the_peak_output_cardinality(self): | calls build_operational_cohorts, _arm, assertEqual, evaluate_request; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 259–259](../../../../../tests/integration/component_workloads.py#L259) | Explanatory comments or spacing. |  |
| [B0018 · 260–285](../../../../../tests/integration/component_workloads.py#L260) | Callable definition: def test_net_batching_retains_common_source_endpoints_including_final_partial(self): | calls build_operational_cohorts, _arm, assertEqual, evaluate_request; 4 loop sites · [reviewed contract](#b0018) |
| [B0019 · 286–286](../../../../../tests/integration/component_workloads.py#L286) | Explanatory comments or spacing. |  |
| [B0020 · 287–310](../../../../../tests/integration/component_workloads.py#L287) | Callable definition: def test_comparison_paths_and_baseline_cd_mode(self): | calls build_operational_cohorts, assertTrue, subTest, _changed_paths; 6 loop sites · [reviewed contract](#b0020) |
| [B0021 · 311–314](../../../../../tests/integration/component_workloads.py#L311) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |

## B0001

[Lines 1–25](../../../../../tests/integration/component_workloads.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:509523d343b1efb266fbda03a405cd566c8d3a723b8b8dbaa4530dc8d60f61c8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up a pure-Python regression module for component workload oracle behavior. |
| inputs / outputs | Imports unittest, exact Fraction, the repository tools path, and the cohort/oracle helpers under test. |
| invariants | Disables bytecode writes; tests execute no native binary and create no build or persistent output artifacts. |
| ownership | The test process owns fixture requests and its temporary SQLite connections through evaluate_request. |
| failure | A missing helper import or failed assertion terminates the unittest run. |
| cost | Module setup is constant; work is in the bounded tests below. |
| Design | [tools/component_workloads.py](../../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0002

[Lines 26–39](../../../../../tests/integration/component_workloads.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L39:sha256:6b4d919cab89fffe19297265b4860f178e646198be0ccb737a77532c0eebb104
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact dotted JSON request differences for comparison review. |
| inputs / outputs | Two values return sorted changed object paths; arrays and scalar values are treated as leaf fields. |
| invariants | Type changes count as differences even when Python equality equates values such as true and one. |
| ownership | Allocates a result list and visits each dict key once; it does not mutate either input. |
| failure | Mixed non-string dictionary keys may not be sortable; cohort requests use JSON string keys. |
| cost | Work is linear in the visited dictionary members. |
| Design | [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0004

[Lines 42–47](../../../../../tests/integration/component_workloads.py#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L47:sha256:574c7e8b27cf8d5302874df2ba3bb76b48d1eb850ee99a8431b829dfe9fa30ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select exactly one arm by its manifest identifier. |
| inputs / outputs | A manifest and identifier return the matching arm. |
| invariants | Zero or multiple matches raise AssertionError so tests cannot silently select an ambiguous arm. |
| ownership | Returns the existing arm mapping without modifying it. |
| failure | Missing/ambiguous identifiers raise AssertionError. |
| cost | Scans the finite arm list once. |
| Design | [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0005

[Lines 48–52](../../../../../tests/integration/component_workloads.py#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L52:sha256:9f05fe90630d112a5cbef144aefd63474391ac19493ce4324c2a8bb49ee0138e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group exact numeric formatting assertions. |
| inputs / outputs | The unittest class contains the direct numeric rounding cases in its method region. |
| invariants | The class declaration itself has no fixture or import side effect. |
| ownership | Python unittest owns discovery of the contained test method. |
| failure | A malformed test definition fails module parsing or discovery. |
| cost | No independent runtime cost beyond class registration. |
| Design | [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0006

[Lines 53–72](../../../../../tests/integration/component_workloads.py#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L72:sha256:adad5e55742bbb70f6a739365c1da0dac3cca2e016303cfbbd5072be6fef3979
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pin exact half-away Fraction formatting for positive, negative, tie, zero, and long values. |
| inputs / outputs | A table of Fractions and scales asserts the exact canonical decimal dictionaries returned by numeric. |
| invariants | Covers negative ties, rounding to zero without negative zero, repeating thirds/sixths, an 18-place boundary, and a 20-digit integer. |
| ownership | Each input Fraction and expected literal is local to the test. |
| failure | Any rounding or formatting mismatch fails the corresponding unittest subtest. |
| cost | A small fixed list of exact integer arithmetic cases. |
| Design | [tools/component_workloads.py](../../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0007

[Lines 73–77](../../../../../tests/integration/component_workloads.py#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L77:sha256:d49d9e7bdec5b64620acd4f500e4d2ddc87114f53b2159983d597634b9d8c95e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group SQLite prefix, aggregate, rejection, and cohort-shape assertions. |
| inputs / outputs | The unittest class contains the physical-prefix and manifest tests in separate methods. |
| invariants | The class declaration has no database or native side effects; each test controls its own fixtures. |
| ownership | Python unittest owns discovery and per-test assertion reporting. |
| failure | A malformed method definition fails module parsing or discovery. |
| cost | Runtime is the sum of the bounded direct test methods. |
| Design | [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0008

[Lines 78–123](../../../../../tests/integration/component_workloads.py#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L123:sha256:fd01356838ab6587ff1dedf665fb14f9bdb205b020adf76abf192f46c12ed2c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check SQLite set deltas and bag multiplicities over cancelling and negative source updates. |
| inputs / outputs | A two-table join fixture is evaluated from empty state through every insert and erase; selected frames assert rows, cardinality, bag weights, and signed membership changes. |
| invariants | A temporary row insert/erase changes intermediate bag counts but leaves set membership and delta unchanged; negative joined source values and subsequent erases are applied as physical unit-set updates. |
| ownership | The request/event list and returned frame data are test-local; evaluate_request owns and closes the SQLite database on success. |
| failure | Oracle validation or any unexpected prefix output fails the test. |
| cost | Runs a ten-event trace and evaluates its small joined result after every event. |
| Design | [tools/component_workloads.py](../../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0010

[Lines 125–179](../../../../../tests/integration/component_workloads.py#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L179:sha256:92ef4c31c329f7c5390fa2755b347ac29d76039abebc9bb8c1073ab0a18f1648
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact COUNT, SUM, and AVG group semantics over joined multiplicity. |
| inputs / outputs | A group-by query is paired with an independent SQL SUM/COUNT rewrite and exact output mapping; expected frames assert fractional positive and negative averages and group disappearance. |
| invariants | Multiple r0 facts share a group key, so each matching r1 fact contributes multiplicity; aggregate sum/average is over r0.c1 with exact SQLite integer sums and Fraction formatting. |
| ownership | All catalogs, physical events, and oracle outputs are local to the test. |
| failure | A SQL, key, numeric, or replacement mismatch fails the test. |
| cost | Runs a finite 14-event prefix trace over small in-memory tables. |
| Design | [tools/component_workloads.py](../../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0012

[Lines 181–193](../../../../../tests/integration/component_workloads.py#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L181-L193:sha256:b2dec1d0148a44f953cbd63c0b5e91f154c56ccbb960ac3a8ff9bb8624971e88
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify the oracle rejects duplicate insertions and erases of absent unit facts. |
| inputs / outputs | Two invalid traces are evaluated independently under subtests and must raise ValueError. |
| invariants | The accepted physical source model is a set of table/value pairs rather than a weighted multiset. |
| ownership | Each invalid request and SQLite connection lifetime is confined to the test call. |
| failure | If either invalid trace is accepted, assertRaises fails. |
| cost | Two short traces stop at the first invalid physical update. |
| Design | [tools/component_workloads.py](../../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0014

[Lines 195–238](../../../../../tests/integration/component_workloads.py#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L195-L238:sha256:6970849a9d8f4ca1f55702bc5bd9e29137a9e226113b18da0e30c98ee7ea6254
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise family, width, cycle, scale, and width-strata input guards. |
| inputs / outputs | Invalid unknown family, boolean/float/non-range bounds, empty/repeated widths, and invalid numeric scales are each expected to raise ValueError. |
| invariants | Boolean values are not accepted as integers; widths and cycles are strict and finite; numeric scale is within the declared range. |
| ownership | Each rejected call uses a fresh temporary argument and has no persistent side effect. |
| failure | An unraised ValueError fails the direct assertion. |
| cost | Only a small finite set of early-rejection calls. |
| Design | [tools/component_workloads.py](../../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0016

[Lines 240–258](../../../../../tests/integration/component_workloads.py#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L240-L258:sha256:9869ff6d013672bf5e09e9d724ee128274e389b03c2fd141a48936c9628e6f86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure the exact full-head snapshot peak for the maximum allowed operational width. |
| inputs / outputs | The width-eight full_discard request is evaluated for every physical prefix; loaded and transient zero-row cardinalities are checked against exact formulas and compared to the full_serialize request source/oracle. |
| invariants | Loaded output is 2*w^3 rows; the temporary r1(100,0) insertion contributes w additional distinct rows, so the exact peak is 2*w^3+w. This is a pure SQLite oracle assertion, not native serializer timing. |
| ownership | The test owns its manifest, request, and returned frames. |
| failure | Any query, endpoint, output peak, or arm mismatch fails. |
| cost | Evaluates the bounded width-eight source through its finite trace; SQLite retains only in-memory tables/result frames. |
| Design | [tools/component_workloads.py](../../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0018

[Lines 260–285](../../../../../tests/integration/component_workloads.py#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L260-L285:sha256:e3ecacb70c555c3a284d027ae6525470e147e036aa75969a6582c6aac79d6ac7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check common net-batch observation endpoints including the final partial group. |
| inputs / outputs | The width-three single/net request event streams and batch/interval settings are checked; both complete SQLite oracle traces are projected onto the selected endpoints and compared. |
| invariants | Observation endpoints are physical input multiples of four plus the final input count; all-prefix oracle frames remain present, while transaction_batch_size is the only request change. |
| ownership | No native adapter is launched; all endpoint and result objects are test-local. |
| failure | Different endpoint states or an omitted final partial endpoint fail the assertion. |
| cost | Evaluates two identical 37-event SQLite traces and compares ten selected frames. |
| Design | [tools/component_workloads.py](../../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0020

[Lines 287–310](../../../../../tests/integration/component_workloads.py#L287); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L287-L310:sha256:5a4082fc9a35458313d6478ae8cc106dbcf5a8b690e2fda852f065719fd9c933
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify exact operational comparison paths and the native L5 distinct-count scalar mode. |
| inputs / outputs | Each operational comparison is checked against recursive request differences plus adapter changes. A width-two baseline manifest then selects the two native L5 distinct-count arms and checks their backend IDs, cardinality output, and delta mode. |
| invariants | Object key additions/removals are dotted paths; arrays remain one field. Both reference and indexed native CD arms must use mode delta with cardinality output. |
| ownership | The finite operational and baseline manifests are test-local and are not mutated. |
| failure | Missing, extra, or misplaced paths, backend arms, outputs, or modes fail direct assertions. |
| cost | Builds two small manifests and inspects all operational comparisons plus two scalar baseline arms. |
| Design | [tools/component_workloads.py](../../../../../tools/component_workloads.py), [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |

## B0021

[Lines 311–314](../../../../../tests/integration/component_workloads.py#L311); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L311-L314:sha256:d40df7781769826cf2c98b2122a93ca752b602c64753327dc2d232eb2230b192
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run unittest only when this file is executed as a script. |
| inputs / outputs | The standard __main__ guard delegates to unittest.main(). |
| invariants | Importing the module defines test classes and helpers without executing tests. |
| ownership | The process entry point owns unittest execution. |
| failure | Failed assertions propagate as a nonzero test process status. |
| cost | No import-time test trace; direct execution runs the bounded suite. |
| Design | [tests/integration/component_workloads.py](../../../../../tests/integration/component_workloads.py) |
