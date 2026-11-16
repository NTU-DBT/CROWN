# `tools/ranking_analysis.py` — block usage map

[Source](../../../../tools/ranking_analysis.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `e14df0a20d1778c343015f3803e5168ce6f7b9cd8591713810fa51385252620b`. 80 lines partitioned into 11 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../tools/ranking_analysis.py#L1) | Imports dependencies. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 10–11](../../../../tools/ranking_analysis.py#L10) | Callable definition: def require(value,message): | calls ValueError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 12–14](../../../../tools/ranking_analysis.py#L12) | Callable definition: def rational(value): | calls require, isinstance, Fraction; guard require(isinstance(value,(int,Fraction)) and not isinstance(value,bool),'expected exact rational va…; returns Fraction(value) · [reviewed contract](#b0003) |
| [B0004 · 15–17](../../../../tools/ranking_analysis.py#L15) | Callable definition: def ratio(value): | calls rational, str; returns None; {'numerator':str(value.numerator),'denominator':str(value.denominator)} · [reviewed contract](#b0004) |
| [B0005 · 18–39](../../../../tools/ranking_analysis.py#L18) | Callable definition: def fit_proxy(samples): | calls require, rational, all, len; guard require(samples,'empty calibration samples');pairs=\[(rational(x),rational(y)) for x,y in samples\]; returns {'algorithm':'exact_nonnegative_affine_least_squares_v1','intercept':intercept,'slope':slope,'desig…; 10 loop sites · [reviewed contract](#b0005) |
| [B0006 · 40–40](../../../../tools/ranking_analysis.py#L40) | Callable definition: def predict(model,value):return model\['intercept'\]+(model\['slope'\] or 0)*rational(value) | calls rational; returns model\['intercept'\]+(model\['slope'\] or 0)*rational(value) · [reviewed contract](#b0006) |
| [B0007 · 41–42](../../../../tools/ranking_analysis.py#L41) | Callable definition: def export_fit(model): | calls ratio, items; returns {k:ratio(v) if k in \['intercept','slope','calibration_squared_error'\] else v for k,v in model.items…; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 43–43](../../../../tools/ranking_analysis.py#L43) | Module statements. | source comment (unverified): # Ratios remain exact; RMSE alone converts the mean squared error to floating point. · [reviewed contract](#b0008) |
| [B0009 · 44–53](../../../../tools/ranking_analysis.py#L44) | Callable definition: def error_summary(predicted,actual): | calls require, len, rational, zip; guard require(len(predicted)==len(actual) and predicted,'empty/mismatched held-out error samples'); returns {'samples':n,'mean_absolute_error':ratio(absolute/n),'mean_signed_error':ratio(sum(errors,Fraction(…; 6 loop sites · [reviewed contract](#b0009) |
| [B0010 · 54–65](../../../../tools/ranking_analysis.py#L54) | Callable definition: def regret(costs,selected,eligible=None): | calls require, set, rational, items; guard require(costs and selected in costs,'selected plan has no measured cost'); returns {'selected':selected,'selected_cost':ratio(chosen),'best_measured_feasible_cost':ratio(best),; 4 loop sites · [reviewed contract](#b0010) |
| [B0011 · 66–80](../../../../tools/ranking_analysis.py#L66) | Callable definition: def ordering_quality(proxy,costs): | calls require, set, sorted, enumerate; guard require(set(proxy)==set(costs),'proxy/measurement candidate sets differ');keys=sorted(proxy);concor…; returns {'candidate_pairs':len(keys)*(len(keys)-1)//2,'concordant':concordant,'discordant':discordant,; 2 loop sites · [reviewed contract](#b0011) |

## B0001

[Lines 1–9](../../../../tools/ranking_analysis.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose exact finite proxy-fit/regret helpers for C07 evaluation only. |
| inputs / outputs | Imports Fraction/math and defines pure helpers; no CLI, native plan selection or IO at import. |
| invariants | Calibration is an explicit evaluation model; callers freeze it before held-out evaluation. Functions do not implement native C03 costs or establish statistical significance. |
| ownership | Fraction results and containers own ordinary Python big integers; input measurement graphs are borrowed. |
| failure | Import/OOM errors propagate; later helper checks use explicit ValueError. |
| cost | Fixed import work; rational arithmetic costs grow with numerator/denominator bit lengths. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 10–11](../../../../tools/ranking_analysis.py#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value,message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a false caller-supplied condition in this tool. |
| inputs / outputs | Truth-tested value and diagnostic text in; None on truth, ValueError on false. |
| invariants | Explicit conditional raise remains active under Python -O; this is a local assertion of the stated predicate, not native/proof validation. |
| ownership | Borrows condition/message; exception retains message until released. |
| failure | Raises ValueError at the caller check before subsequent operations; does not catch or undo earlier IO. |
| cost | O(truth conversion) plus exception construction only on failure; arbitrary user-defined __bool__ is outside these primitive callers. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 12–14](../../../../tools/ranking_analysis.py#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def rational(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exact integer/Fraction values and normalize them to Fraction. |
| inputs / outputs | int or Fraction, explicitly excluding bool; normalized Fraction out. |
| invariants | Float/Decimal/string inputs are rejected rather than silently approximated. |
| ownership | Fraction result is immutable; existing Fraction may be reused, integer numerator/denominator backing retained. |
| failure | ValueError on unaccepted type; arithmetic/OOM propagates. |
| cost | Integer/Fraction normalization with big-integer gcd/bit costs; no constant-cost claim for unbounded inputs. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 15–17](../../../../tools/ranking_analysis.py#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def ratio(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an exact rational as decimal numerator/denominator strings, preserving missingness. |
| inputs / outputs | None or rational-admitted value in; None or two-string dict out. |
| invariants | None remains unavailable, distinct from exact zero; denominator follows normalized Fraction positivity. |
| ownership | Owns result dict and decimal strings; immutable Fraction temporary. |
| failure | rational ValueError or integer-string/OOM errors propagate. |
| cost | Big-integer normalization and base10 conversion proportional to operand digits; two owning strings. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [docs/code_review.md](../../../code_review.md) |

## B0005

[Lines 18–39](../../../../tools/ranking_analysis.py#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def fit_proxy(samples):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fit a nonnegative affine least-squares evaluation mapping with an explicit constant-proxy case. |
| inputs / outputs | Nonempty nonnegative (training-only proxy, calibration cost) samples in; Fraction intercept/slope/SSE and metadata out. |
| invariants | Variance0 returns slope=None and rank1; otherwise nonnegative slope/intercept constraints and origin refit apply. No evaluation data or native selection is consumed by this helper. |
| ownership | Owns normalized pairs, exact residuals, Fraction accumulators and returned dict; input samples unchanged. |
| failure | ValueError rejects empty/negative/type inputs before result; arithmetic/OOM errors propagate. |
| cost | Several O(samples) passes and retained pairs/residuals with unbounded rational bit arithmetic; rank/status is local fit metadata, not event-cost identification. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 40–40](../../../../tools/ranking_analysis.py#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def predict(model,value):return model['intercept']+(model['slope'] or 0)*rational(value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the fitted evaluation mapping to one exact proxy. |
| inputs / outputs | Model intercept/slope and exact proxy in; intercept+(slope or0)*proxy out. |
| invariants | Unidentified slope=None uses intercept-only prediction; does not refit or mutate the model. |
| ownership | Borrows model; owns Fraction arithmetic results. |
| failure | Missing keys/type/ValueError/arithmetic/OOM propagate. |
| cost | Fixed number of rational operations whose cost depends on operand bit lengths. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [docs/code_review.md](../../../code_review.md) |

## B0007

[Lines 41–42](../../../../tools/ranking_analysis.py#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def export_fit(model):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize three rational model fields while preserving the other fit metadata. |
| inputs / outputs | Fit dict in; fresh shallow dict with intercept/slope/calibration_squared_error exported via ratio out. |
| invariants | Other fields remain their original values, so this is not a general deep clone. |
| ownership | Owns result dict and ratio subdicts/strings; unchanged metadata values borrowed/immutable in actual model. |
| failure | ratio/type/OOM failure propagates; input not changed. |
| cost | O(model fields) traversal plus three rational decimal-string conversions. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [docs/code_review.md](../../../code_review.md) |

## B0008

[Lines 43–43](../../../../tools/ranking_analysis.py#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L43:sha256:afefdd77cc270761662d34fb81eb4b81c9927365cc0e96f959b99666b21f8d02
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: Ratios remain exact; RMSE alone converts the mean squared error to floating point. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking.md](../../../ranking.md), [docs/code_review.md](../../../code_review.md) |

## B0009

[Lines 44–53](../../../../tools/ranking_analysis.py#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def error_summary(predicted,actual):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Summarize finite held-out prediction errors with exact ratios and one approximate RMSE. |
| inputs / outputs | Equal-length nonempty predicted/actual rational sequences in; error metrics dict out. |
| invariants | Relative error excludes actual0 and reports exclusions; RMSE uses math.sqrt(float(MSE)), so it is approximate and can overflow for huge exact inputs. |
| ownership | Owns normalized pairs, error/relative lists and output ratio records; inputs unchanged. |
| failure | ValueError on empty/mismatch/type; float conversion/overflow/arithmetic/OOM errors propagate. |
| cost | O(N) retained samples and several passes of rational arithmetic; float sqrt only for RMSE, not an exact-root guarantee. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [docs/code_review.md](../../../code_review.md) |

## B0010

[Lines 54–65](../../../../tools/ranking_analysis.py#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def regret(costs,selected,eligible=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one selected candidate with the best retained, measured eligible candidates. |
| inputs / outputs | Cost map, selected key and optional eligible keys in; exact selected/best/absolute/relative regret with sorted ties out. |
| invariants | Requires nonnegative costs, nonempty measured eligibility and selected membership; zero best yields unavailable relative regret. Minimum is restricted to supplied feasible family. |
| ownership | Owns eligibility set, normalized cost dict, result strings/lists; candidate keys retained by reference. |
| failure | ValueError rejects missing/invalid eligibility/negative/type values; sorting/arithmetic/OOM propagates. |
| cost | O(C) cost normalization/minimum/tie selection plus O(ties log ties) sorting; no global-plan search. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [docs/code_review.md](../../../code_review.md) |

## B0011

[Lines 66–80](../../../../tools/ranking_analysis.py#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def ordering_quality(proxy,costs):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count pairwise proxy/cost agreements and ties for a finite candidate family. |
| inputs / outputs | Same-key proxy and measured-cost maps in; pair counts and exact non-tie concordance out. |
| invariants | Ties counted separately; no statistical significance/confidence or full plan-space claim. |
| ownership | Owns sorted key list and output record; maps borrowed, per-pair Fractions temporary. |
| failure | ValueError for key/type mismatch; key comparison/arithmetic/OOM errors propagate. |
| cost | O(C²) pairs with rational conversion/subtraction and key-list slices; O(C) keys plus temporary slice storage. |
| Design | [tools/ranking_analysis.py](../../../../tools/ranking_analysis.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [tests/integration/ranking_evaluation.py](../../../../tests/integration/ranking_evaluation.py), [docs/code_review.md](../../../code_review.md) |
