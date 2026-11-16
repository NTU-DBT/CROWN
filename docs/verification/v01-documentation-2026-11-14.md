# V01 documentation acceptance and V45 source inspection

**V01 is verified against all ten artifact/acceptance obligations.** Its O08 and
C05 prerequisites remain verified. Full Refactor progress is now **58 verified /
1 in progress A02 /19 not started**, 78 total. V02 mathematical review, experiments,
licensing and release/extension gates remain separate and open.

The new [quickstart](../quickstart.md), [SQL/model/guarantees](../guarantees.md),
[query and extension workflow](../development.md), [troubleshooting](../troubleshooting.md)
and [complete cursor program](../cursor_example.md) give one current route into
the C++ system. README customization now routes supported queries to SQL and data
fixtures, with the original Scala/Flink workflow explicitly separated. The older
mixed-stage SQL table points to the current supported/rejected syntax matrix.

## Requirement-by-requirement acceptance

| Requirement | Artifact | Checked evidence |
| --- | --- | --- |
| Quickstart | [quickstart.md](../../docs/quickstart.md) | Fresh Release/OFF configure, build and installation; guide commands match the successful 77-command trial. |
| Supported SQL matrix | [guarantees.md](../../docs/guarantees.md) | Current supported/rejected SQL forms and interface boundaries checked by an independent reviewer against actual binders and component contracts. |
| Model and guarantees | [guarantees.md](../../docs/guarantees.md) | Rows/support/NULL/ownership, supplied trees versus height proofs, actual cost/resource/recovery boundaries and open release scope are explicit; current CLI validates the new plan as proven_minimum. |
| Plan and cursor examples | [cursor_example.md](../../docs/cursor_example.md) | All four EXPLAIN formats execute; C++/CMake blocks are extracted verbatim, compiled against the relocated public SDK and executed with owning-row/read-lease checks. |
| Troubleshooting | [troubleshooting.md](../../docs/troubleshooting.md) | Reviewed against actual diagnostic/reader/session contracts; rejected compilation does not require EXPLAIN and separate resource grants remain explicit. |
| Extension guide | [development.md](../../docs/development.md) | New semantics require explicit contracts and independent/runtime/recovery gates; existing cleanup/account/work/proof boundaries are preserved. |
| Minimal query contribution process | [development.md](../../docs/development.md) | SQL, catalog, ordered updates and independent expected results are sufficient; the existing corpus/runner registration path is linked. |
| New supported query uses SQL plus fixtures only | [query.sql](../../docs/examples/route-labels/query.sql) | Four new data files; all 1,196 native paths remain the same. The sole native byte change is two comment lines with complete executable-token/geometry equality; no query operator/class or executable code was added. |
| Examples run from a clean environment | [evidence-validation-v1.json](../../build/verification/v01-clean-user-workflow-v1/evidence-validation-v1.json) | Fresh default Release/OFF build retains 149 actual C++ objects; 229-file moved SDK, all five shipped public examples, 18 SQLite/current/delta/source/restart epochs, exact guide 5+checkpoint+13 flow and installed generic API run/restore pass without source/build headers or testing/reference libraries. |
| Limitations and exactness statuses match executable | [guarantees.md](../../docs/guarantees.md) | Independent source review plus actual plan/trace/current/delta/sink and cursor checks; no full-suite/compiler-matrix, hardware power-loss, CPU-optimality, whole-system mathematical review or release claim. |

## Actual clean-install execution

A fresh GCC Release build with `BUILD_TESTING=OFF`, C++23 and warnings as errors
completed from pinned local dependencies. All **149 configured C++ units have
actual retained objects**. The **229-file SDK** was installed and moved to a
prefix containing a space. Its native headers, libraries and CLI match the fresh
build. Outside consumers use that prefix without original source/build headers,
testing/reference libraries or package-registry lookup. Compiler/include/library
environment and source-stable command receipts are retained.

The new route-labels contribution adds only SQL, catalog, update-template and
expected-result files. SQLite independently executes the actual SQL after each
of **18 full-row set events**. Fresh installed CLI processes match every current
row, exact signed sink delta, committed/delivered sequence and source offset,
including shared projection support, duplicate insertion and absent deletion.
There are **18 separate-process snapshots and two checkpoints**. A second session
executes the documented **5 + checkpoint + 13** flow; the unchanged generic
installed API example executes run/restore on the same unseen query.

The final trial records **77 passing commands**. All four EXPLAIN formats execute.
The cursor C++/CMake blocks are extracted verbatim, built and run. The first trial
compiled the snippet but its strict dialect check caught default `gnu++23`;
the CMake example now disables extensions, and a fresh second trial passes.
Both attempts are preserved. Later peer corrections affect prose/support tables
only; every tested command and code fence remains identical to its saved version.

All **five shipped public examples** also run from fresh moved installations:
native workflow, measurement (12 SQL/backend/mode cases /33 commands), ranking
(48 candidate/mode checks /62 commands), calibration (five SQL/oracle/report
cases), and reoptimization (both backends /7 commands). Reports containing timings
are checked as functional output; this is no controlled performance
comparison, whole-current-suite, new Debug/SAN/Clang matrix or release acceptance.
The detailed [execution packet](../../build/verification/v01-clean-user-workflow-v1/README.md)
records the exact scope and original command results.

## Code clarity and performance

Only `src/io/event_reader.cpp:462–463` changes in maintained native code. The
comment now says every consuming preparation error latches failure: decoding,
record limits, source ordering and cache publication are all inside the existing
catch. Engine application occurs after `peek` returns, so a complete cached event
remains retryable after engine rejection. The handler is necessary; none is removed
without evidence. No executable token, literal, line count or source region changes.
No branch, allocation, wrapper, retry layer, state or instrumentation is added.

Root and the reviewer reconcile all **16,717 existing contracts**: exactly 44
source-hash rebindings under full token/geometry equivalence and one clarified
`peek` invariant. All other fields are preserved. The [handler guide](../code_specs/error_handling.md)
documents the boundary. Root checked the complete token stream/regions; the
independent receiver checked the exact two-comment diff and all registry changes.

The source index remains **751 files /172,040 lines /19,412 blocks**, with 16,717
contracts in 14,301 blocks and zero selected callable/type/inline-cluster gaps.
The exact **5,111 structural blocks /670 files /15,137 lines** and every remaining
raw block's bytes are unchanged from V44. These still need appropriate human
disposition; V01 acceptance is not universal comment or mathematical certification.
All 1,196 native paths remain; only that source file's bytes differ from V44.

## Review and handoff

Root authored/implemented the work and ran the native checks. A Luna Max reviewer
read all five guides and four fixture files, inspected backing sources and
reviewed the test receipts; it did not rerun native commands. The separate Luna
Max handler reviewer proposed and checked the reader wording and exact contract
diff. No Astra Max is used. All reviewed versions and test/prose amendments are
pinned, including the retained corrected receiving metadata.

Latest global seal: build/verification/human-inspection-v45-progress-v1.json;
frozen source: build/verification/human-inspection-v45-source-v1. The
[V45 receiving packet](../../build/verification/inspection-structural-dispositions-v45-v1/README.md)
pins the final coverage, requirements, reviews and execution evidence. The
[previous handoff](../handoff-history-v44-2026-11-14.md) is byte-identical to V44.
The [current handoff](../handoff.md) preserves prior native attribution and next work.
