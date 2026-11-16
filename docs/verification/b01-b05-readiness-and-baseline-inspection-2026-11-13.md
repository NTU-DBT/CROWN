# Unstarted Task Readiness, Legacy Baseline (B01) & Adversarial Scalability (B05) Inspection — 2026-11-13

## 1. Overview & Context

This record audits the 20 unstarted tasks in the CROWN Next implementation plan, examines task dependencies against the current verified baseline (56 verified / 2 in progress / 20 not started), executes the legacy comparison baseline build diagnostic (B01), and verifies the newly prepared adversarial scalability experimental runner (B05).

---

## 2. Unstarted Tasks Dependency & Readiness Audit

A complete audit of all 20 unstarted tasks from [Refactor.md](../../Refactor.md) and [task_ledger.md](../task_ledger.md):

| Task ID | Task Title | Declared Dependencies | Dependency Status | Can Start Now? | Readiness Assessment & Blockers |
| :--- | :--- | :--- | :--- | :---: | :--- |
| **C04** | Meta-decomposition candidate adapter | P07, A02 | P07 verified; A02 in progress | ⚠️ Partial | Blocked from full acceptance by A02 distribution licensing disposition; algorithmic adapter prototype can be designed. |
| **X01** | Update-pattern-aware planning | C05, B02, B03 | All verified | **YES** | Ready. C05 selection and B02/B03 benchmark workloads are available. |
| **X02** | Key-aware specializations | P08, S04, D04, D05 | All verified | **YES** | Ready. Physical lowering, indexed storage, and delta enumeration contracts are verified. |
| **X03** | Heavy/light star backend prototype | S04, R05, D05 | All verified | **YES** | Ready. Indexed storage and delta routing are verified. |
| **X04** | Comparison-aware query support | F03, F04, P08, S04 | All verified | **YES** | Ready. Desugaring, normalization, lowering, and storage are verified. |
| **X05** | Snapshot top-k | S04, D01, D05, W01 | All verified | **YES** | Ready. Result cursors, indexed storage, and annotation policies are verified. |
| **X06** | General-query fallback backends | F06, P01, O08 | All verified | **YES** | Ready. Admission, recognition, and CLI workflow are verified. |
| **X07** | Optional approximate aggregation | W04, W05, B03 | All verified | **YES** | Ready. Aggregate logic, SQL row runtime, and measurement harness are verified. |
| **X08** | Difference / anti-join contract | F04, P08, D04, D05 | All verified | **YES** | Ready. Normalization, delta enumeration, and physical lowering are verified. |
| **X09** | Specialization / codegen after profiling | B03, B04 | B03 verified; B04 not started | ❌ No | Blocked by B04 component evaluation. |
| **X10** | Multi-query shared state | P08, S04, R04, O02 | All verified | **YES** | Ready. Lowering, indexed storage, event scheduler, and session lifecycle are verified. |
| **X11** | Parallel / distributed execution | O05, O06, B03, X10 | O05/O06/B03 verified; X10 not started | ❌ No | Blocked by multi-query shared state (X10). |
| **B01** | Build legacy comparison environments | A02 | A02 in progress | **YES** | Research & diagnosis started. Pinned legacy Scala source is available in `crown/`. Build failure under modern JDKs documented below. |
| **B04** | Evaluate planner, runtime & optimizer separately | B03, C07, B01 | B03/C07 verified; B01 not started | ❌ No | Requires B01 legacy baseline for external comparison (though internal native ablations are executable). |
| **B05** | Run adversarial scalability & memory experiments | B03, D05, S05 | All verified | **YES** | **Fully unblocked.** B03 measurement harness, D05 lazy delta output, and S05 hierarchical query account are all verified. |
| **B06** | Publish reproducible experimental report | B04, B05 | Neither completed | ❌ No | Blocked by B04 and B05. |
| **V01** | Complete user/developer documentation | O08, V02 | O08 verified; V02 not started | ⚠️ Partial | Documentation drafting is ongoing; formal gate requires V02 review. |
| **V02** | Independent mathematical & semantic review | Core verification | Prerequisite met | ⚠️ Partial | Can begin parallel semantic audit of verified core. |
| **V03** | Package and freeze R1 | G1–G7 gates | G7 verified; G0 open | ❌ No | Final release packaging gate. |
| **V04** | Package R2 & manage extensions | W06, R2 gates | W06 in progress | ❌ No | Blocked by W06 aggregate transaction completion. |

---

## 3. B01 Legacy Comparison Environment Diagnostic

### Objective & Setup
Refactor.md §11.11 mandates:
> *B01 — Build legacy comparison environments. Depends: A02. Artifacts: isolated pinned CROWN Scala and C++ baseline builds, small supported replay examples, build-failure records. Distinguish published-artifact reproduction from local modifications. Acceptance: each usable baseline has verified output on at least one tiny supported workload before its timing is used; unsupported operations are excluded explicitly rather than silently ignored.*

### Toolchain & Dependency Inventory
- **Host Java Runtimes**: OpenJDK 17.0.21 (`/usr/lib/jvm/java-17-openjdk-amd64`), OpenJDK 21.0.13 (`/usr/lib/jvm/java-21-openjdk-amd64`).
- **Maven**: Apache Maven 3.8.7.
- **Legacy Source**: `crown/` at commit `e369a623517723b3be3ea3e9806779f3c591e7f9`.
- **Target Configurations in `crown/pom.xml`**:
  - `target.java.version`: `1.8`
  - `scala.binary.version`: `2.12`
  - `scala.version`: `2.12.7`
  - `flink.version`: `1.13.5`
  - `scala-maven-plugin`: `3.2.2`

### Build Attempt & Exact Failure Signature
Running `mvn -f crown/pom.xml clean compile` under Java 17 triggered a deterministic failure during Scala compilation:
```text
[ERROR] error: java.io.IOError: java.lang.RuntimeException: /packages cannot be represented as URI
    at java.base/jdk.internal.jrtfs.JrtPath.toUri(JrtPath.java:175)
    at scala.tools.nsc.classpath.JrtClassPath.asURLs(DirectoryClassPath.scala:204)
    at scala.tools.nsc.classpath.AggregateClassPath.$anonfun$asURLs$1(AggregateClassPath.scala:55)
...
[ERROR] Failed to execute goal net.alchim31.maven:scala-maven-plugin:3.2.2:compile (default) on project CROWN: wrap: org.apache.commons.exec.ExecuteException: Process exited with an error: 240 (Exit value: 240)
```

### Analysis & Resolution Path
1. **Root Cause**: Scala 2.12.7 and `scala-maven-plugin:3.2.2` contain an outdated JRT filesystem scanner incompatible with the modular runtime image in Java 16+. Java 17 `JrtPath.toUri()` throws an exception on `/packages`.
2. **Reproduction Tool Created**: [`tools/run_legacy_baseline.py`](../../tools/run_legacy_baseline.py) detects host toolchains, parses POM dependencies, executes the build with timeouts, and records failure signatures.
3. **Execution Artifact**: Generated [`build/legacy_baseline_report.json`](../../build/legacy_baseline_report.json) capturing the exact host environment, dependency tree, and failure trace.
4. **Conclusion for B01**: To execute the legacy Scala baseline without modifying pinned POM files, an isolated Java 8 (1.8) execution environment or container is strictly required.

---

## 4. B05 Adversarial Scalability & Memory Experiment Preparation

### Objective & Setup
Refactor.md §11.11 mandates:
> *B05 — Run adversarial scalability and memory experiments. Depends: B03, D05, S05. Artifacts: scale curves, fan-out/height/arity/skew stress, output-small/huge families, long churn runs. Measure internal operation counts as well as wall time. Acceptance: tests expose scans hidden by favorable datasets, tombstone iteration and memory growth with historical updates; unexpected trends are explained or filed as blockers, not averaged away.*

### Experiment Tool Implementation
Created [`tools/run_adversarial_scalability.py`](../../tools/run_adversarial_scalability.py), an automated driver utilizing the verified B03 controlled harness ([`tools/run_measurements.py`](../../tools/run_measurements.py)) and native measurement binary (`crown_measure_workload`).

The tool supports four stress suites:
1. `long_churn`: High insert/delete toggle ratios (`self_join_2`, `hidden_witnesses`, `projected_star`, `projected_prefix_path`) to stress tombstone iteration.
2. `fanout_skew_stress`: Wide stars vs deep chains (`full_star_3`, `full_star_6`, `full_path_4`, `wide_arity_8`).
3. `output_extremes`: Small projected output vs large Cartesian expansions.
4. `scale_curves`: Scaling input volumes across workload families.

### Verification Run Evidence
Executed verification on `output_extremes` suite (Release build `build/b03-measurement-fresh-release-v1`):

| Configuration | Workload Case | Storage Backend | Delta/Maintenance Mode | Duration | Result |
| :---: | :--- | :--- | :--- | :---: | :---: |
| 1 | `projected_star/insert_only` | `indexed_chained_v1` | `delta` | 5.17s | **PASSED** |
| 2 | `projected_star/insert_only` | `indexed_chained_v1` | `maintenance` | 5.22s | **PASSED** |
| 3 | `full_star_3/insert_only` | `indexed_chained_v1` | `delta` | 5.18s | **PASSED** |
| 4 | `full_star_3/insert_only` | `indexed_chained_v1` | `maintenance` | 5.19s | **PASSED** |
| 5 | `hidden_witnesses/delete_after_charged_load` | `indexed_chained_v1` | `delta` | 5.17s | **PASSED** |
| 6 | `hidden_witnesses/delete_after_charged_load` | `indexed_chained_v1` | `maintenance` | 5.16s | **PASSED** |

**Summary**: 6 / 6 configurations passed in 31.09s total execution time. Verified outputs and structured JSON generated in `build/adversarial_experiments_report/`.

---

## 5. Handover Protocol & Next Steps

### Handover Principles
1. **Never Make Unearned Claims**: Tasks B01 and B05 have established tooling and baseline evidence, but remain `not_started` in the official task ledger until the full evaluation matrices and comparative evaluations are completed.
2. **Deterministic Artifact Placement**:
   - Diagnostic tools in `tools/`.
   - Raw measurement packets in `build/` (e.g. `build/adversarial_experiments_report/`, `build/legacy_baseline_report.json`).
   - Markdown verification summaries in `docs/verification/`.
   - Master ledger maintained in `docs/task_ledger.md`.
   - Continuation context maintained in `docs/handoff.md`.

### Immediate Next Tasks for Subsequent Continuations
1. **W06 (Primary Active Line)**: Continue R2 aggregate session coordination, WAL replay, and recovery integration.
2. **B05 (Benchmark Line)**: Execute the full adversarial matrix (`--suite all`) across both `indexed_chained_v1` and `reference_ordered_v1` backends to produce scale curves and memory growth plots.
3. **B01 (Legacy Comparison Line)**: Establish a pinned Java 8 container environment to compile `crown/pom.xml` and generate baseline output traces on `length3_project` and `star_cnt`.
