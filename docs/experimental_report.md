# Reproducible experimental report

The report tools assemble exact tables, reachable raw evidence and static figures
from received measurements. They execute no native benchmark or build. Study
completion, source/build qualification, statistical uncertainty and B04/B06
acceptance remain separate fields. Historical source images are never pooled
into a same-build speedup claim.

## Assemble a data bundle

Supply all five completed study directories and the accepted B05 analyzer output.
Paths are caller-selected; no private workspace is assumed:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 tools/build_experimental_report.py \
  --b05 "$task_b05_packet" --b05-analysis "$task_b05_analysis" \
  --planning "$task_planning_packet" --operational "$task_operational_packet" \
  --matched "$task_matched_packet" --search "$task_search_packet" \
  --output "$task_new_report" --max-evidence-bytes 17179869184
```

The source packets must have completed their exact correctness gates before
timing. Each included raw command must have exit zero, matching stdout/stderr
hashes and a matching GNU-time RSS resource record. Report generation does not
replace those independent SQL/relational checks with a new success flag.

`--selection FILE.json` selects explicit genuine groups for development. Omitted
studies retain their full input scope; the resulting report visibly records
included/available counts. Group ids are:

| Study | Group selector |
| --- | --- |
| B05 | `family|scale|backend|mode` |
| Planning | `query|backend|trace` (all physical plans for that scope) |
| Operational or matched | Exact arm id |
| Search | `case|method|work_limit` |
| Optional specialization | `case|backend|execution` |

An optional `--specialization DIR` receives the completed
`b04_input_specialization_study_v1` same-engine interpreted/threaded experiment.
It is absent until actual measured data exists. Execution keys, inclusive
receiving-freeze/preparation time and extra-table metadata remain separate from
the unchanged physical/source identity. This is not JIT machine-code generation.

The default uncompressed evidence grant is 512 MiB, suitable for tiny genuine
subsets. Full historical B05 measured raw reports exceed 5 GB; schedule full
bundling explicitly and set a finite sufficient grant. No gigabyte copy is
required for tool development. `--max-file-bytes` also bounds each decoded file.

## Portable raw links and source preimages

Every per-repetition metric has an exact rational numerator/denominator,
availability, unit, repetition, raw link, original SHA256 and JSON pointer. The
builder writes deterministic per-file gzip members with fixed timestamp/name
metadata. The evidence index binds both compressed hashes and original
decompressed hashes. Original packet bytes are preserved.

`--path-map ORIGINAL_ROOT=NEW_ROOT` relocates an input root while retaining its
expected hashes. Deterministic recompression uses the recorded Python/zlib
runtime; another compressor may produce different compressed bytes while
preserving exact original bytes. It does not rewrite original JSON or accept changed
bytes. To regenerate tables on another machine without any original private
prefix, copy the whole report bundle and use its included tools:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 "$task_bundle/report-tools/build_experimental_report.py" \
  --replay "$task_bundle" --expected-manifest-sha256 "$task_published_manifest_sha256" \
  --output "$task_fresh_report" --max-evidence-bytes 17179869184
```

Replay reads only the indexed gzip members and never falls back to original
paths. A missing/tampered member, wrong published manifest hash or exceeded
grant rejects. Choose a new output directory; rejected reuse preserves existing
evidence.

Data replay alone is not a complete rebuild/publication package. Supply reachable
source-preimage files/archives with repeatable
`--source-preimage STUDY=FILE` for each included study. Keep the historical
compiler/dependency/machine records and pinned fetch URLs with those preimages.
The generated report explicitly flags missing source preimages. A supplied
file hash identifies bytes; it does not prove that an arbitrary archive is the
correct source image. Publication receiving must join the archive inventory to
the study's qualified source/build records. B04/B06 acceptance is never inferred.

V48 B05, V59 planning and V60 runtime/search have different source images. In
particular, the B05 generator's later docstring changes its self-hash even when
the generated computation is unchanged. Historical replay uses its preserved
preimage. A fresh run of current sources records new identities and new timing
values.

## Generate standalone scientific figures

Matplotlib is a report-only dependency. Use a separate environment and cache:

```sh
python3 -m venv "$task_report_python"
"$task_report_python/bin/python" -m pip install 'matplotlib==3.10.7'
PYTHONDONTWRITEBYTECODE=1 MPLCONFIGDIR="$task_new_plot_cache" \
  "$task_report_python/bin/python" tools/plot_experimental_report.py \
  --input "$task_new_report" --output "$task_new_report/figures"
```

The received B05 environment has a resolved wheel/version/hash manifest; retain
that lock for its Linux/Python platform, or record the compatible resolved wheel
hashes on a new platform. The plot manifest records the actual Matplotlib version,
Agg backend, source hashes and input table hash. PNG/PDF byte identity across
platforms is not promised. The reviewed B05 plotting API supplies the complete
selected family/sentinel appendix; newer plots facet programs/protocols rather
than average unrelated queries into one curve.

Figures show medians and observed min/max over measured process repetitions.
Summary CSVs retain mean and sample standard deviation. Three repetitions do not
justify an invented confidence interval; event percentiles are within-run latency
descriptors, not extra independent repetitions. Zero remains zero; unavailable
metrics are not zero samples. Exact tables remain authoritative when display
coordinates convert to floats.
Stage tables retain p50/p95/p99 and maxima in their actual epoch, transaction,
batch or call units. Cursor-first-result samples start at output setup after
commit; eager preparation/staging remains charged in native/event phases and
is not a constant input-to-answer delay claim.

## Run the methodology in a fresh workspace

Set task-specific paths beneath a new workspace. Restore the desired source
preimage, then build the existing clients with explicit compiler and dependency
lock. Do not point commands at accepted immutable prefixes:

```sh
cmake -S "$task_source" -B "$task_build" -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_TESTING=OFF
cmake --build "$task_build" --parallel 2 --target crown crown_measure_workload \
  crown_export_components crown_component_set crown_component_rows \
  crown_component_session crown_component_aggregate crown_search_components
```

The [B05 guide](adversarial_scalability.md) gives the scale workload/analyzer
commands. The [component guide](component_evaluation.md) gives planning,
operational and matched runner invocations and exact cohort factories. Run
`tools/run_search_evaluation.py` with the same source/build/crown/collector paths,
`--searcher "$task_build/crown_search_components"`, fresh `--output`, a permitted
`--cpu`, declared work grants, three repetitions and one warmup. Every runner
checks correctness before timing and records its actual environment. Serialize
controlled driver execution; caches/frequency/unrelated host activity remain
observed limits.

For original Scala/Flink, stage the pinned original commit from
[the baseline guide](legacy_baselines.md) into a fresh directory, select its
qualified Java 8 and private Maven repository, and compile unchanged sources:

```sh
JAVA_HOME="$task_java8" PATH="$task_java8/bin:$PATH" \
  mvn -f "$task_original_scala/pom.xml" -Dmaven.repo.local="$task_m2" compile
JAVA_HOME="$task_java8" PATH="$task_java8/bin:$PATH" \
  mvn -f "$task_original_scala/pom.xml" -Dmaven.repo.local="$task_m2" \
  package -DskipTests=true
JAVA_HOME="$task_java8" PATH="$task_java8/bin:$PATH" \
  mvn -f "$task_original_scala/pom.xml" -Dmaven.repo.local="$task_m2" \
  dependency:build-classpath -DincludeScope=test -Dmdep.outputFile="$task_test_cp_file"
mkdir "$task_new_helper_classes"
task_compiler_cp="$task_m2/org/scala-lang/scala-compiler/2.12.7/scala-compiler-2.12.7.jar:$task_m2/org/scala-lang/scala-library/2.12.7/scala-library-2.12.7.jar:$task_m2/org/scala-lang/scala-reflect/2.12.7/scala-reflect-2.12.7.jar"
task_test_cp="$(cat "$task_test_cp_file")"
"$task_java8/bin/java" -cp "$task_compiler_cp" scala.tools.nsc.Main \
  -cp "$task_original_scala/target/classes:$task_test_cp" \
  -d "$task_new_helper_classes" "$task_source/tools/support/ComponentReplay.scala"
```

The helper class directory precedes original main classes and test/runtime JARs
in `--scala-classpath`. Run the independent tiny replay before timing; retain
raw signed records and full drains after every event. Preserve the published
`OutputResultTest` failure separately from successful unmodified compile/package
and independent replay. No published-suite or delta-only qualification is added.

For original C++, follow the baseline guide's pinned source/fmt/Catch2/formatter
configuration and build only its admitted target in a fresh directory. Install
the new engine into a fresh SDK, then build installed `component-runtime` with
the three explicit legacy source/build/fmt paths. Original archives remain
unsanitized Release inputs.

Create new expected qualification inventories from the actual fresh artifacts;
never reuse this machine's old path list as if it qualified a new build. The
matched runner's qualification keys are relative to its `--source` prefix, so
stage Java, the private dependency repository, original classes and helper
classes beneath that same fresh source prefix:

```sh
TASK_REPORT_SOURCE="$task_source" TASK_REPORT_JAVA="$task_java8/bin/java" \
TASK_REPORT_HELPER="$task_new_helper_classes" \
TASK_REPORT_CLASSES="$task_original_scala/target/classes" \
TASK_REPORT_CP_FILE="$task_test_cp_file" TASK_REPORT_QUAL="$task_new_scala_qualification" \
PYTHONDONTWRITEBYTECODE=1 python3 - <<'PY'
import hashlib, json, os
from pathlib import Path
source = Path(os.environ['TASK_REPORT_SOURCE']).resolve()
inputs = [Path(os.environ[key]) for key in
          ('TASK_REPORT_JAVA', 'TASK_REPORT_HELPER', 'TASK_REPORT_CLASSES')]
inputs += [Path(name) for name in Path(os.environ['TASK_REPORT_CP_FILE'])
           .read_text().strip().split(os.pathsep)]
pins = {}
for entry in inputs:
    files = [p for p in entry.rglob('*') if p.is_file()] if entry.is_dir() else [entry]
    for path in files:
        pins[str(path.resolve().relative_to(source))] = hashlib.sha256(path.read_bytes()).hexdigest()
with Path(os.environ['TASK_REPORT_QUAL']).open('x') as output:
    json.dump({'relative_sha256': pins}, output, indent=2)
PY
```

The inventory is a byte-binding mechanism. Git-blob source checks, genuine build
receipts, independent result checks and source-to-class/JAR lineage supply its
qualification. Include all resolved classpath entries. The matched runner rejects
unqualified bytes. C++ uses the analogous `relative_sha256` inventory including
the actual wrapper executable and its qualified source/library inputs.

## Interpretation and remaining limits

B05 reports data/query scale, output demand and fixed-population churn; slots
are populations rather than tombstone visits. Counter layers overlap and do not
sum to CPU work. Planning separates candidate completeness, scoring quality,
forecast error and measured feasible regret. Rank-deficient C03 fits and explicit
sampled/stale/absent fallbacks stay visible; C05 `maintenance_cost` is unsupported.

Operational tables separate source inputs, atomic transactions, transport batches
and observation endpoints. Synthetic consumer wait overlaps output/loop clocks;
owner-specific requested-byte peaks differ from whole-process RSS. Clean-owner
reconstruction is not power-loss recovery. Exact AVG uses its admitted fixed-scale
rounding contract, not floating SQLite AVG.

Matched whole implementations include plan/layout/parser/scalar/formatting/JVM/JIT
and allocator effects. Search timings include bounded attempts; a family prefix
never becomes a complete family. Limited/unavailable outcomes are retained in
the decisions table. All historical goals, all ten B04 axes and release acceptance
keep their explicit status; publication tables do not turn implementation aims
into measured facts.
