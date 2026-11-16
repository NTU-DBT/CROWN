# `tests/integration/component_analysis.py` — block usage map

[Source](../../../../../tests/integration/component_analysis.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `622cff55f97b9ef9919aa05f91cb3f438c7ce3c178b8c50d7edb2a4d1f01e32d`. 201 lines partitioned into 49 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/integration/component_analysis.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | growth insert; 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 17–18](../../../../../tests/integration/component_analysis.py#L17) | Callable definition: def ratio(numerator, denominator=1): | calls ; returns {'numerator': numerator, 'denominator': denominator} · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../tests/integration/component_analysis.py#L19) | Explanatory comments or spacing. |  |
| [B0004 · 21–27](../../../../../tests/integration/component_analysis.py#L21) | Callable definition: def estimate(key, value, issues=0, captured=10, budget=100, stamp=None): | calls ; returns {'structural_key': key, 'maintenance_ns': None, 'total_ns': value, · [reviewed contract](#b0004) |
| [B0005 · 28–29](../../../../../tests/integration/component_analysis.py#L28) | Explanatory comments or spacing. |  |
| [B0006 · 30–31](../../../../../tests/integration/component_analysis.py#L30) | Callable definition: def report(rows, stop=0): | calls ; returns {'stop': stop, 'usage': {}, 'candidates': rows} · [reviewed contract](#b0006) |
| [B0007 · 32–33](../../../../../tests/integration/component_analysis.py#L32) | Explanatory comments or spacing. |  |
| [B0008 · 34–35](../../../../../tests/integration/component_analysis.py#L34) | Callable definition: def height(key): | calls ; returns {'selected_key': key, 'availability': 'native_choice', 'stop': 0, 'reasons': \[\]} · [reviewed contract](#b0008) |
| [B0009 · 36–37](../../../../../tests/integration/component_analysis.py#L36) | Explanatory comments or spacing. |  |
| [B0010 · 38–63](../../../../../tests/integration/component_analysis.py#L38) | Callable definition: def valid_export(): | calls in, estimate, ratio, append; returns {'schema_version':1, 'kind':'b04_cold_component_planning_export', 'status':'exported_conditional_da…; growth insert; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 64–66](../../../../../tests/integration/component_analysis.py#L64) | declares types or opens a type body. |  · [reviewed contract](#b0011) |
| [B0012 · 67–75](../../../../../tests/integration/component_analysis.py#L67) | Callable definition: def test_uint64_near_one_order_does_not_round_to_float_tie(self): | calls estimate, ratio, event_choice, report; source comment (unverified): # Both numerator and denominator stay in the native uint64 domain. · [reviewed contract](#b0012) |
| [B0013 · 76–76](../../../../../tests/integration/component_analysis.py#L76) | Explanatory comments or spacing. |  |
| [B0014 · 77–81](../../../../../tests/integration/component_analysis.py#L77) | Callable definition: def test_exact_rational_tie_uses_structural_key(self): | calls estimate, ratio, event_choice, report · [reviewed contract](#b0014) |
| [B0015 · 82–82](../../../../../tests/integration/component_analysis.py#L82) | Explanatory comments or spacing. |  |
| [B0016 · 83–86](../../../../../tests/integration/component_analysis.py#L83) | Callable definition: def test_ratio_parser_rejects_float_negative_and_zero_denominator(self): | calls in, ratio, subTest, assertRaises; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 87–89](../../../../../tests/integration/component_analysis.py#L87) | declares types or opens a type body. |  · [reviewed contract](#b0017) |
| [B0018 · 90–92](../../../../../tests/integration/component_analysis.py#L90) | Callable definition: def assert_height_fallback(self, got, key): | calls assertEqual · [reviewed contract](#b0018) |
| [B0019 · 93–93](../../../../../tests/integration/component_analysis.py#L93) | Explanatory comments or spacing. |  |
| [B0020 · 94–97](../../../../../tests/integration/component_analysis.py#L94) | Callable definition: def test_absent_estimate_rows_fall_back_to_native_height(self): | calls event_choice, report, height, assert_height_fallback · [reviewed contract](#b0020) |
| [B0021 · 98–98](../../../../../tests/integration/component_analysis.py#L98) | Explanatory comments or spacing. |  |
| [B0022 · 99–102](../../../../../tests/integration/component_analysis.py#L99) | Callable definition: def test_missing_candidate_estimate_row_falls_back_without_subset_ranking(self): | calls event_choice, report, estimate, ratio · [reviewed contract](#b0022) |
| [B0023 · 103–103](../../../../../tests/integration/component_analysis.py#L103) | Explanatory comments or spacing. |  |
| [B0024 · 104–108](../../../../../tests/integration/component_analysis.py#L104) | Callable definition: def test_unknown_score_falls_back_even_when_other_scores_are_numeric(self): | calls estimate, ratio, event_choice, report · [reviewed contract](#b0024) |
| [B0025 · 109–109](../../../../../tests/integration/component_analysis.py#L109) | Explanatory comments or spacing. |  |
| [B0026 · 110–115](../../../../../tests/integration/component_analysis.py#L110) | Callable definition: def test_native_stop_never_uses_attached_numeric_rows(self): | calls estimate, ratio, event_choice, report · [reviewed contract](#b0026) |
| [B0027 · 116–116](../../../../../tests/integration/component_analysis.py#L116) | Explanatory comments or spacing. |  |
| [B0028 · 117–121](../../../../../tests/integration/component_analysis.py#L117) | Callable definition: def test_any_known_asof_memory_exclusion_forces_height_fallback(self): | calls estimate, ratio, event_choice, report · [reviewed contract](#b0028) |
| [B0029 · 122–122](../../../../../tests/integration/component_analysis.py#L122) | Explanatory comments or spacing. |  |
| [B0030 · 123–127](../../../../../tests/integration/component_analysis.py#L123) | Callable definition: def test_native_memory_issue_bit_also_excludes_candidate(self): | calls estimate, ratio, event_choice, report · [reviewed contract](#b0030) |
| [B0031 · 128–128](../../../../../tests/integration/component_analysis.py#L128) | Explanatory comments or spacing. |  |
| [B0032 · 129–133](../../../../../tests/integration/component_analysis.py#L129) | Callable definition: def test_height_candidate_known_over_budget_has_no_fallback(self): | calls estimate, ratio, event_choice, report · [reviewed contract](#b0032) |
| [B0033 · 134–134](../../../../../tests/integration/component_analysis.py#L134) | Explanatory comments or spacing. |  |
| [B0034 · 135–139](../../../../../tests/integration/component_analysis.py#L135) | Callable definition: def test_unknown_asof_memory_cannot_complete_cost_choice(self): | calls estimate, ratio, event_choice, report · [reviewed contract](#b0034) |
| [B0035 · 140–140](../../../../../tests/integration/component_analysis.py#L140) | Explanatory comments or spacing. |  |
| [B0036 · 141–145](../../../../../tests/integration/component_analysis.py#L141) | Callable definition: def test_foreign_and_duplicate_estimate_keys_are_rejected(self): | calls in, estimate, ratio, subTest; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 146–148](../../../../../tests/integration/component_analysis.py#L146) | declares types or opens a type body. |  · [reviewed contract](#b0037) |
| [B0038 · 149–151](../../../../../tests/integration/component_analysis.py#L149) | Callable definition: def test_duplicate_family_keys_are_rejected(self): | calls valid_export, append, assertRaises, freeze_choices · [reviewed contract](#b0038) |
| [B0039 · 152–152](../../../../../tests/integration/component_analysis.py#L152) | Explanatory comments or spacing. |  |
| [B0040 · 153–155](../../../../../tests/integration/component_analysis.py#L153) | Callable definition: def test_duplicate_family_ids_are_rejected(self): | calls valid_export, append, deepcopy, assertRaises · [reviewed contract](#b0040) |
| [B0041 · 156–156](../../../../../tests/integration/component_analysis.py#L156) | Explanatory comments or spacing. |  |
| [B0042 · 157–160](../../../../../tests/integration/component_analysis.py#L157) | Callable definition: def test_calibration_identity_hash_mismatches_are_rejected(self): | calls in, valid_export, subTest, assertRaises; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 161–161](../../../../../tests/integration/component_analysis.py#L161) | Explanatory comments or spacing. |  |
| [B0044 · 162–176](../../../../../tests/integration/component_analysis.py#L162) | Callable definition: def test_training_mix_is_exact_forecast_denominator_and_family_is_retained(self): | calls valid_export, estimate, ratio, freeze_choices; source comment (unverified): # A missing estimate row forces fallback, but does not remove candidate B · [reviewed contract](#b0044) |
| [B0045 · 177–177](../../../../../tests/integration/component_analysis.py#L177) | Explanatory comments or spacing. |  |
| [B0046 · 178–186](../../../../../tests/integration/component_analysis.py#L178) | Callable definition: def test_stale_asof_stamp_and_variant_are_preserved_without_refresh_claim(self): | calls freeze_choices, valid_export, next, assertEqual; 1 loop sites · [reviewed contract](#b0046) |
| [B0047 · 187–187](../../../../../tests/integration/component_analysis.py#L187) | Explanatory comments or spacing. |  |
| [B0048 · 188–197](../../../../../tests/integration/component_analysis.py#L188) | Callable definition: def test_frozen_result_owns_nested_export_values(self): | calls valid_export, freeze_choices, canonical, assertEqual · [reviewed contract](#b0048) |
| [B0049 · 198–201](../../../../../tests/integration/component_analysis.py#L198) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0049) |

## B0001

[Lines 1–16](../../../../../tests/integration/component_analysis.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:38865cc01c21a73b3d3d81be9b4b9a967e42d01c6b563e7bd7abb52aa1054a3d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load the pure Python selector and unittest fixtures from the supplied worktree root. |
| inputs / outputs | Optional repository path in; selector module and finite test definitions become available. |
| invariants | Tests use no native binary, runtime owner or held-out measurement; they exercise only the offline exact-selection contract. |
| ownership | Imports and fixture values use ordinary process-owned Python storage. |
| failure | Invalid root/module imports stop collection and return failure. |
| cost | One Python module import; no native/runtime work. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [docs/verification/c03-maintenance-cost-acceptance-2026-11-10.md](../../../../verification/c03-maintenance-cost-acceptance-2026-11-10.md) |

## B0002

[Lines 17–18](../../../../../tests/integration/component_analysis.py#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L18:sha256:8405b9981193966c68084b59035defca9709adb81b2baaa40b5aad1ac5834f1d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create exact ratio mappings for synthetic report values. |
| inputs / outputs | Python integers and optional denominator in; JSON-compatible numerator/denominator mapping out. |
| invariants | Fixture helper performs no decimal/float conversion; native parser validation is tested separately. |
| ownership | New ordinary Python mapping; integer scalars are immutable. |
| failure | Python argument errors propagate. |
| cost | Constant fixture construction. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py) |

## B0004

[Lines 21–27](../../../../../tests/integration/component_analysis.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L27:sha256:a241f7aa434643fda5f8160b819470c2041332bdcf00bbf8556de1d48820f392
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one exporter-shaped candidate estimate row. |
| inputs / outputs | Key, ratio/null, C03 issue bits, captured bytes/budget and optional observed stamp in; candidate JSON mapping out. |
| invariants | Fields mirror the actual exporter, including future_memory_unknown, as-of bytes, stamp and terms. |
| ownership | Fixture row owns its dictionary; provided stamp is shared input data for mutation tests. |
| failure | Malformed row behavior is asserted at selector boundary. |
| cost | Constant mapping construction with at most uint64-width test integers. |
| Design | [examples/component-planning/main.cpp](../../../../../examples/component-planning/main.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0006

[Lines 30–31](../../../../../tests/integration/component_analysis.py#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L31:sha256:dc0cc74a12374db0022d829147325254d5ab436625f2588999d496505cd473e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap candidate estimate rows in a native report fixture. |
| inputs / outputs | Rows and native stop number in; report mapping out. |
| invariants | Stop 0 means planner::ranking::Stop::complete; noncomplete rows must not be selected. |
| ownership | Ordinary Python wrapper referencing the supplied row sequence. |
| failure | Selector tests assert fallback for noncomplete reports. |
| cost | Constant wrapper construction. |
| Design | [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [examples/component-planning/main.cpp](../../../../../examples/component-planning/main.cpp) |

## B0008

[Lines 34–35](../../../../../tests/integration/component_analysis.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L35:sha256:3a625ab5729f4c856afd75c5d3b5cc95702b34f953434b1dbf041cfc639df1c8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a native C02 height-choice fixture. |
| inputs / outputs | One family key in; selected-key/index/stop/reasons report out. |
| invariants | Height choice stays independent from C03 score ordering. |
| ownership | Ordinary Python mapping. |
| failure | Invalid native choice behavior is covered at its consumer boundary. |
| cost | Constant fixture construction. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [examples/component-planning/main.cpp](../../../../../examples/component-planning/main.cpp) |

## B0010

[Lines 38–63](../../../../../tests/integration/component_analysis.py#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L63:sha256:73cf95c6ee01af5727e3ba619af538efaac165220bde9689bb9289f7088ae093
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a minimal cold export with identity, training demand and all four statistics variants. |
| inputs / outputs | No files/native calls; emits a synthetic two-key B04 export with full, sampled, stale and absent cases. |
| invariants | Calibration identity binds source/catalog/calibration hashes; six insert/erase rows total 40 declared inputs. Stale row has an older stamp; absent estimate rows remain absent. |
| ownership | Fixture trees are ordinary Python objects and mutation cases deep-copy them. |
| failure | Malformed shape or mismatches fail via freeze_choices or assertions. |
| cost | Small constant fixture setup. |
| Design | [examples/component-planning/main.cpp](../../../../../examples/component-planning/main.cpp), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0011

[Lines 64–66](../../../../../tests/integration/component_analysis.py#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L66:sha256:a2ba593b7cbf1daa87116b20d888a13b25c35a31f19293b0488a3a49cb1c4771
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group finite exact ratio parsing/order regressions. |
| inputs / outputs | Unittest class groups uint64-adjacent ratios, exact rational ties and malformed ratios. |
| invariants | Synthetic cases show comparator behavior only; they do not establish model calibration quality. |
| ownership | Class definition retains no runtime state. |
| failure | Any failing assertion makes script nonzero. |
| cost | No execution cost until tests run. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [tests/integration/component_analysis.py](../../../../../tests/integration/component_analysis.py) |

## B0012

[Lines 67–75](../../../../../tests/integration/component_analysis.py#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L75:sha256:6165ceea6e07282f808ba954b1eb1fc5f02839b4efc812639e4665e442443a33
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Catch float-rounding reversal near the native uint64 range. |
| inputs / outputs | Two ratios use values &lt;= UINT64_MAX; keys a and z, where a scores 1 and z scores (MAX-1)/MAX. |
| invariants | Exact result must select z even though float conversion collapses scores to a tie; serialized result remains exact. |
| ownership | Local integers and ordinary result objects only. |
| failure | Wrong key or ratio fails assertion. |
| cost | Two exact big-integer comparisons; no native work. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0014

[Lines 77–81](../../../../../tests/integration/component_analysis.py#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L81:sha256:48b94511d30756b34aa07cf11709cb97f691b29fcf5fd97a1e33ceabfebcb565
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check structural-key tie-breaking for equal exact ratios. |
| inputs / outputs | 2/4 and 3/6 rows with z/a keys in; selected key and reduced score out. |
| invariants | Equal Fraction values choose ascending structural key independent of input order. |
| ownership | Local synthetic values only. |
| failure | Wrong key/score fails. |
| cost | Constant-size Fraction comparisons. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py) |

## B0016

[Lines 83–86](../../../../../tests/integration/component_analysis.py#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L86:sha256:76b703bb8892b7f05be377169c9b86a7513e20254fbedaa1cd7be2aecf0334bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject float, negative, zero-denominator and bool ratio encodings. |
| inputs / outputs | Four malformed ratios in; ValueError expected for each. |
| invariants | A Python bool is not accepted as a native unsigned integer; binary float is never coerced. |
| ownership | Local scalar fixtures. |
| failure | Missing exception fails assertion. |
| cost | Four finite parser calls. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py) |

## B0017

[Lines 87–89](../../../../../tests/integration/component_analysis.py#L87); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L87-L89:sha256:7e9815954bf4711ec059535221ad6493d72e76c3bb7cbe4f082fc1289da74da2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group unavailable, partial, budget and malformed candidate estimate regressions. |
| inputs / outputs | The unittest class groups explicit fallback and identity-rejection behaviors. |
| invariants | Finite tests do not assert native estimates are accurate or enable C05. |
| ownership | Class definition owns no native state. |
| failure | Assertion failure makes this pure test process fail. |
| cost | No work until contained tests run. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [docs/verification/c03-maintenance-cost-acceptance-2026-11-10.md](../../../../verification/c03-maintenance-cost-acceptance-2026-11-10.md) |

## B0018

[Lines 90–92](../../../../../tests/integration/component_analysis.py#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L92:sha256:122ba9001d40ebdbcdb4ed8fcf01c5da87318d44fc51d64c3f6f5feb5064817a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the exact explicit height-fallback result shape. |
| inputs / outputs | Selector result plus expected key in; checks key and fallback availability label. |
| invariants | Fallback key is the independent native height choice. |
| ownership | Reads result mapping only. |
| failure | Mismatch fails unittest assertion. |
| cost | Fixed scalar assertions. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py) |

## B0020

[Lines 94–97](../../../../../tests/integration/component_analysis.py#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L97:sha256:f0e3510441a1fd732c6a9c6bb47fb55fb2c3dcda2eda58925f9e27544ac669c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fallback when a nonempty family has no event rows. |
| inputs / outputs | Complete native stop, empty estimates and two family keys in; height key out. |
| invariants | Absent costs are unavailable, never zero, and do not remove family members. |
| ownership | Local dictionaries only. |
| failure | Wrong selection/label/unknown key list fails. |
| cost | Constant-size path. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [examples/component-planning/main.cpp](../../../../../examples/component-planning/main.cpp) |

## B0022

[Lines 99–102](../../../../../tests/integration/component_analysis.py#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L102:sha256:cc4e93e1a25b1baead137580fa3cc152950f00d250851af69380ef7086fc38e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fallback when a family estimate row is missing. |
| inputs / outputs | Family contains a/b while report contains only a. |
| invariants | The present subset cannot win; b remains unknown and native height is retained. |
| ownership | Local test mappings. |
| failure | Subset selection or hard failure instead of fallback fails. |
| cost | One row lookup and fixed checks. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py) |

## B0024

[Lines 104–108](../../../../../tests/integration/component_analysis.py#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L108:sha256:abc0d6ac7d0d42d57d6a328226d0f263a7fa7e12ec3e6a719dc9415a8152521c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fallback when any complete-family score carries a C03 issue or is unknown. |
| inputs / outputs | One exact score and one null total with detail_unavailable bit. |
| invariants | Unknown score is not zero; numeric rows cannot form a partial-family cost choice. |
| ownership | Local row/result values. |
| failure | Wrong choice, label or unknown set fails. |
| cost | Two row visits. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0026

[Lines 110–115](../../../../../tests/integration/component_analysis.py#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L115:sha256:ed95f049d28afdf78a69b841fe0c9921a9d39b92572d04bed0756ad0dce580a2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disallow score use after a noncomplete native estimate stop. |
| inputs / outputs | Full numeric rows and evidence_unavailable stop in; height fallback out. |
| invariants | Noncomplete native results do not publish a cost choice; prediction is null. |
| ownership | Synthetic Python mappings only. |
| failure | Non-null predicted value or wrong fallback fails. |
| cost | Constant fallback branch. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [examples/component-planning/main.cpp](../../../../../examples/component-planning/main.cpp) |

## B0028

[Lines 117–121](../../../../../tests/integration/component_analysis.py#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L121:sha256:b6896678dbc2b266122142e04a8e947bc54a9304a0e843da9b1b1d43648c47d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fallback if one family member is over the captured-state byte budget. |
| inputs / outputs | One eligible score and one row with requested bytes above budget; height selects eligible a. |
| invariants | An overbudget row makes family score coverage incomplete; do not cost-rank the remaining subset. This says nothing about future memory. |
| ownership | Synthetic as-of counters only. |
| failure | Partial selection or wrong label/key fails. |
| cost | Two finite candidate rows. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0030

[Lines 123–127](../../../../../tests/integration/component_analysis.py#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L123-L127:sha256:e2686da04bf9cded682c232048c7e0d1c752575d46a93a1619d396d3d288eca7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Honor the native memory_budget issue bit even when captured bytes appear within budget. |
| inputs / outputs | One row with issue bit 32 and captured bytes below its reported budget. |
| invariants | The issue bit excludes the row and requires whole-family fallback. |
| ownership | Local row/result values. |
| failure | Treating the flagged row as eligible fails. |
| cost | Two finite row visits. |
| Design | [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp) |

## B0032

[Lines 129–133](../../../../../tests/integration/component_analysis.py#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L133:sha256:f177c7466897acf14a3a08aeb9fd3264b415c7cfb16cae975f004698796289bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a native height fallback whose known as-of bytes exceed budget. |
| inputs / outputs | Height selects a known-overbudget row; another candidate is unavailable. |
| invariants | No known-overbudget key is returned as an available fallback. |
| ownership | Local synthetic values. |
| failure | Returning selected key fails. |
| cost | Two row checks and fixed assertions. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py) |

## B0034

[Lines 135–139](../../../../../tests/integration/component_analysis.py#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L139:sha256:bf1b4db67244fe4a42e2471ce3e9e6b253eee436b7765a155e63db658d64d48c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Treat unknown captured-state bytes as insufficient for cost selection. |
| inputs / outputs | Two numeric estimates, one with null asof_requested_bytes. |
| invariants | Missing as-of memory evidence prevents complete eligible-family scoring and triggers fallback. |
| ownership | Local report dictionaries. |
| failure | Cost choice or failure to expose unknown key fails. |
| cost | Two row visits. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0036

[Lines 141–145](../../../../../tests/integration/component_analysis.py#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L145:sha256:d1124d0c27cb5a49bbdff2265e27463e492173fe53428b28507317a81d52b5d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject foreign or duplicate estimate structural keys. |
| inputs / outputs | Test one foreign key and one duplicated row for a family key. |
| invariants | Report keys must be unique and a subset of candidate family keys; errors cannot become zero scores or silent drops. |
| ownership | Local lists/dictionaries. |
| failure | Each malformed report must raise ValueError. |
| cost | Two finite error paths. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py) |

## B0037

[Lines 146–148](../../../../../tests/integration/component_analysis.py#L146); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L148:sha256:8112b09fa7f5c148ee240fe810d14f9670b1094aa68d191650b1e210b7343a0c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group frozen export provenance and family/variant validation regressions. |
| inputs / outputs | Class tests clone exports, invoke freeze_choices and inspect returned summaries. |
| invariants | Passing behavior is finite functional evidence; the class does not prove a real runner freezes before held-out timing. |
| ownership | Fixture state is local ordinary Python data. |
| failure | Wrong result or missing ValueError fails tests. |
| cost | No execution cost until methods run. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [build/verification/v58-b04-design-review-v1/README.md](../../../../../build/verification/v58-b04-design-review-v1/README.md) |

## B0038

[Lines 149–151](../../../../../tests/integration/component_analysis.py#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L151:sha256:80c2447b8b15ef8c13f296309beba458f9769543183bf2ed5c6d921a56d08960
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject duplicate candidate keys within one family. |
| inputs / outputs | A cloned export appends a second candidate with key a. |
| invariants | Candidate family keys must be nonempty and unique before estimates are consumed. |
| ownership | Deep-copied fixture only. |
| failure | Missing ValueError fails. |
| cost | One short key scan. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py) |

## B0040

[Lines 153–155](../../../../../tests/integration/component_analysis.py#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L155:sha256:ee6502f977a023a7a92e277390304448ab31e6580317674b3b2d09ee6f13ef59
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject duplicate family identifiers. |
| inputs / outputs | A valid family is cloned and appended with the same id. |
| invariants | Frozen family identifiers are unique. |
| ownership | Deep-copied fixture only. |
| failure | Missing ValueError fails. |
| cost | Linear family-id set construction. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py) |

## B0042

[Lines 157–160](../../../../../tests/integration/component_analysis.py#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L157-L160:sha256:6644211c8824118c27fdf8d29cbb7a266029c94b63b787d5422b0d25f98226d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject calibration identity hashes that differ from export provenance. |
| inputs / outputs | Three cloned exports independently mutate source, catalog or calibration identity. |
| invariants | Each of the three compared identity hashes must equal the top-level frozen export hash. |
| ownership | Local clone/error values. |
| failure | Missing ValueError for any field fails. |
| cost | Three finite validations. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [examples/component-planning/main.cpp](../../../../../examples/component-planning/main.cpp) |

## B0044

[Lines 162–176](../../../../../tests/integration/component_analysis.py#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L162-L176:sha256:8cbaffa1606bc72a225510aff2d7c71c8e22443c4038005e046ef3311b9180bc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve the declared training-demand denominator and complete candidate family under fallback. |
| inputs / outputs | Training demand totals 40; the full variant has one missing event row but retains both original candidates and both capture records. |
| invariants | forecast_inputs comes from declared training demand. Fallback changes selection only; independent verification/measurement of all candidates belongs to the runner. |
| ownership | Result is ordinary Python data; freeze_choices deep-copies nested values at final boundary. |
| failure | Wrong total, demand, family, fallback or captures fails. |
| cost | One sum and a short family/variant traversal plus copy for output. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [examples/component-planning/main.cpp](../../../../../examples/component-planning/main.cpp), [docs/verification/c03-maintenance-cost-acceptance-2026-11-10.md](../../../../verification/c03-maintenance-cost-acceptance-2026-11-10.md) |

## B0046

[Lines 178–186](../../../../../tests/integration/component_analysis.py#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L178-L186:sha256:a0221de02f82c1e029bd5129a9c893a25423c522f4cc88edbb2aab477af48bfb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve stale variant and observed stamp without certifying freshness. |
| inputs / outputs | Stale candidate carries an older owner/epoch stamp; frozen result exposes the same values. |
| invariants | The selector does not compare against current state, refresh profile evidence or claim future memory fits. |
| ownership | Frozen output owns a deep copy; test fixture remains independently mutable. |
| failure | Dropped/relabelled/changed stamp or false freshness scope fails. |
| cost | One nested stamp transfer during selection/freeze. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [docs/verification/c03-maintenance-cost-acceptance-2026-11-10.md](../../../../verification/c03-maintenance-cost-acceptance-2026-11-10.md) |

## B0048

[Lines 188–197](../../../../../tests/integration/component_analysis.py#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L188-L197:sha256:5c9b4e6ffc2daa0f2c9278fdffa36cee3554e92ee110f40edf67467cdc307588
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ensure the frozen result owns nested payload instead of aliasing the parsed export. |
| inputs / outputs | Freeze a valid export, mutate nested demand, capture, stale stamp and fit values, compare canonical frozen output before/after. |
| invariants | The frozen record and export_content_sha256 remain stable after caller mutation of the parsed source mappings. |
| ownership | Deepcopy creates detached ordinary Python state; no CROWN ownership is involved. |
| failure | Any nested drift or denominator change fails assertions. |
| cost | One deep-copy at the cold freeze boundary; test makes four mutations and canonical comparisons; no per-update cost. |
| Design | [tools/component_analysis.py](../../../../../tools/component_analysis.py) |

## B0049

[Lines 198–201](../../../../../tests/integration/component_analysis.py#L198); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L198-L201:sha256:e54b7bacb2823c81024d3f0781cf184719295c84d5390fe691b3217e5be42bed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all pure selector regression cases as a standalone script. |
| inputs / outputs | Optional root argument is accepted and unittest discovers its test methods. |
| invariants | Execution uses synthetic in-process reports only; no CROWN exporter or held-out measurement is launched. |
| ownership | unittest owns method instances; fixture values are local. |
| failure | Any failed assertion exits nonzero. |
| cost | 18 finite exact-rational/validation cases; no native timing or cost claim. |
| Design | [tests/integration/component_analysis.py](../../../../../tests/integration/component_analysis.py), [tools/component_analysis.py](../../../../../tools/component_analysis.py) |
