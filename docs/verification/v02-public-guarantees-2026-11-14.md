# V47 human inspection and V02 acceptance

V02 is verified for the documented conditional source arguments. Root received
the independent arguments, counterexamples, actual caller joins and final usage
cards. The full Refactor goal remains active: **59 verified / 1 in progress (A02)
/ 18 not started**, 78 total. V01 and bounded V33 W06 remain verified.

## Inspect the code

Use the [inspection guide](../code_review.md), [line/block index](../code_specs/README.md),
[primitive costs](../code_specs/primitives.md), [error-handling dispositions](../code_specs/error_handling.md)
and [27-family matrix](../independent_review.md). Each scoped contract describes
usage, inputs/outputs, invariant, ownership, failure phase, cost and source/design
references. Paper algorithms and local engineering choices are identified
separately. The map covers 751 files, 172,040 lines and 19,412 blocks.

**16,796 authored contracts cover 14,380 blocks.** This pass adds 79 contracts:
33 Python entry blocks and 46 formerly structural behavior blocks. Root reviewed
the source and corrected assertion-mode, import, allocation, command, timeout,
partial-output and cleanup descriptions. Independent receiving checks all 96
draft amendments and the accepted postimages. Four existing semantic fields are
corrected; 12 existing source hashes are rebound after the one-line tool fix.
See [exact registry replay/coverage](../../build/verification/v02-public-guarantee-closure-v1/coverage-final-v2.json)
and [independent card correspondence](../../build/verification/v47-generator-fix-review-v1/report.md).

Selected callable/type/substantive inline-cluster gaps are zero, including 5,461
selected test regions. The remaining 5,032 structural blocks span 13,973 lines
in 660 files, including 2,884 blank blocks. They retain structural descriptions;
they are not individually certified semantic contracts. A source map or test
usage card does not prove correctness or record test execution.

## Arguments and boundaries

The [closure audit](../../build/verification/v02-closure-audit-v1/review.md) and
[six new leaf arguments](../../build/verification/v02-closure-audit-v1/leaf-arguments.md)
resolve ordinary input codecs, diagnostics, transport/replay joins, D01/D02
hidden-witness enumeration and installed example callers. Separate
[public export/identity/native-pack](../../build/verification/v02-public-export-review-v1/review.md),
[CLI/package](../../build/verification/v02-cli-package-review-v1/report.md) and
[C07 evaluation](../../build/verification/v02-baseline-evaluation-review-v1/report.md)
arguments supply actual positive semantics beyond historical finite tests.

[Root dependency dispositions](../../build/verification/v02-public-guarantee-closure-v1/dependency-dispositions-v1.json)
record acceptance. No identified internal advertised argument leaf remains in
the investigated catalogue. External C++/library/parser/JSON, recorded native
ABI, integrity, borrowed-buffer, serialized-owner, trusted Linux filesystem/clock
and empirical-model premises remain explicit. Finite models and fault sweeps
supplement the arguments; hashes and counts establish provenance.

The [receiving record](../../build/verification/v02-public-guarantee-closure-v1/proof-receiving-v1.json)
preserves 23 evidence folders: 22 independently authored review, inventory or
draft packets and one root digest argument. These are not 23 independent proofs.
Full, partial and inherited source scopes remain distinct. The 139-header census
is breadth inventory. Forty-four guide substitutions clarify actual contracts;
the final matrix/status/handoff edits are recorded separately.

| Area | Contract boundary |
| --- | --- |
| Class and planner | The class bridge proves admitted-tree existence for recognized H/H+F acyclicity. Generalized nodes can improve height. Exact search/replay supplies optimum authority; resource stops are not infeasibility. |
| Statistics and selection | Cells are committed facts; live Metadata can include pending attempts. Direct Support begin_epoch admits before staged probes. C02 height-only rank_current does not capture freshness; valid C05 select_current checks its owner boundary. |
| Resources and costs | Actual owner/grant chains preserve one receiving account and retained operation lease. Requested bytes, work units, CPU and RSS differ. Hidden-witness scans, preparation, diagnostics and teardown retain their real costs. |
| Recovery and retirement | Validations precede sequential repair; optional seek may precede final sink gates. Caller preserves external consumed prefix bytes. Genuine intent relies on the trusted namespace; checkpoint confirmation reopens/size-checks/syncs without comparing an old inode. R2 retirement is open. |
| Identity and codecs | Genuine replay/reconstruction supplies authority. Legacy v1 physical SHA omits some limits. UTF8 JSON serialization is narrower than native binary strings. JSON depth/duplicate callbacks execute during DOM construction. |
| Cost and measurement | Checked C03 forecasts differ from approximate fit and future accuracy. C05 maintenance_cost selection is unsupported. C07 receives finite same-family evaluation, not C03 forecast quality. B03 JSONL file payload checks are stronger than discard/none counts; failed-record capture has a protected execution/save scope. |

## Direct implementation and regression

No engine catch, guard, retained field, instrumentation or update-path code was
added. Necessary rollback, cursor cleanup and uncertain-I/O latching retain their
documented purpose. Offline documentation adds no engine runtime overhead.
No speedup or reduced CPU/RSS result is claimed.

One tooling bug was found: tests/workflow/generate_fixtures.py resolved ROOT one
parent too high. The fix changes OUT.parents[2] to OUT.parents[1]; all 12
function/class AST bodies are unchanged. The
[isolated before/after regression](../../build/verification/v02-public-guarantee-closure-v1/workflow-generator-regression-v1.json)
reproduces the old partial-write FileNotFoundError and completes five cases and
34 events with the fix. All 21 fixture payload/README files are byte-identical.
The manifest changes only source/specification hashes. Exactly two of the 1,196
recorder inputs differ from V46: the script and manifest. All 355 production
paths and all C++/CMake code remain byte-identical.

The generated-specification checker passes **126,747 local references** across
the complete map. The final separate 102-guide audit checks local destinations
and fragments; external URLs are skipped. These are linkage checks, not proofs.

Six terminal digest compile/run recorder commands precede the tool fix. SDK and
sanitizer profiles each pass 1,294 independent byte-vector comparisons; the ABI
probe and NIST FIPS 180-4 constant/initial-word comparison pass. The
[digest argument](../../build/verification/v02-digest-leaf-review-v1/root-argument-v2.md)
is conditional on the recorded word-expression ABI, not every exotic host.

After the tool/manifest successor, the existing Debug workflow CTest passes
**1/1 in 12.37 seconds**, stable across all 1,196 inputs during that run.
[Terminal receipt](../../build/verification/v47-workflow-generator-debug-ctest-v1.json)
and [independent receiving](../../build/verification/v47-generator-fix-review-v1/report.md)
retain that scope. V46's selected 33/33 Debug and 33/33 ASan/UBSan/leak checks
remain tied to their exact earlier cohort. No fresh whole-suite/compiler/install
matrix or controlled performance comparison is claimed.

Use the [handoff](../handoff.md), [ledger](../task_ledger.md) and exact
[V46 handoff history](../handoff-history-v46-2026-11-14.md). V47 freezes final
source/docs and evidence; its postcheck records the raw seal SHA. Previous
packets, snapshots and private SDK/builds remain immutable. The .git directory
remains read-only; no commit was made. A02's license decision, R2 retirement,
remaining experiments/extensions and release gates remain open.
