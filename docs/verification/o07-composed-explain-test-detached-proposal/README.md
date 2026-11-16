# Independent composed EXPLAIN detached-owner acceptance revision

Excluded O07 preparation, dated 2026-11-07. This package is independently
written against frozen composed package
`a4e759965fea2efcb3578080f0445d80579bb6f0daf1a5c36ea4149c6310f30a`.
Only strict compiler/linker evidence is supplied here. The author has not run
the test binaries, Python checker, CMake, CTest, or native acceptance. O07
remains not started until the root's actual integration/acceptance work.

## Files and portability

- `composed_test.cpp`: self-contained test main, explicit native fixtures,
  persistent allocator, fake optional clock, native sidecar writers. No other
  test `.cpp` is included. No proposal path appears in the C++ source.
- `check_reports.py`: offline strict V2 schema/semantic checker; requires
  Python 3.10+ and `jsonschema` with Draft 2020-12 support. It rejects duplicate
  JSON keys and non-JSON numeric constants; all references must be local.
- `build_test.py`: **preparatory-only**, strict compile/link orchestration;
  configurable `--repo-root`, frozen include layers and pinned inputs, `/tmp`
  output only. It never launches the binary or checker.
- `compile-evidence-o0.json`, `compile-evidence-o3.json`, `readiness.json`:
  final source/dependency/object/archive/binary hashes and compile commands.

The native packaging closure is just `composed_test.cpp`, `check_reports.py`,
existing `tests/reference/tree_oracle.hpp` and the existing separately compiled
`crown_reference` library (whose implementation independently enumerates labelled
topologies and native power sets). The test additionally links final native
runtime, report/IO/core, plan, SQL and libpg_query targets. No data fixture file,
proposal source/helper, generated header, overlay archive, or CLI main is a
native test dependency. Native placement can be `tests/unit/` for the C++
source and `tools/support/` for the checker. Pass explicit `--schema-dir` and
`--repo-root` to the checker after moving it. The native schema directory must
contain the final `explain-report-v2.schema.json` and
`explain-tree-v2.schema.json`; these contain their query definitions locally.
The standalone query V1 schemas remain separately required by their own tests.

For this excluded compilation, highest-first headers are composed, cursor,
run-context, mode-binding, runtime, original explain, query explain, native.
The six report objects exclude CLI main. The matching complete nine-TU runtime
archive is rebuilt with the nontrivial observation ABI and
`CROWN_RUNTIME_TESTING`; this test uses that macro too. Both test optimization
levels link the same pinned O0 testing runtime/report closure. An O3 test TU
is not evidence of an independently optimized production runtime.

## Actual-owner scenarios

Five independently invocable groups are `lifecycle`, `sessions`, `caps`,
`authority`, and `faults`; `all` runs all five. Every owner and every typed
proof/candidate is produced through its genuine public API. No mutable report,
progress flag, forged snapshot or caller-provided validation boolean enters a
report factory.

`lifecycle` covers explicit off/counters/timed/trace modes; direct and insertion
replay construction, rebuild and empty construction; actual pending, paused,
draining, prepared, committed and moved runtime owners. It records full
requested options separately from resolved current and immutable begin policy,
uses distinctive nested limits, keeps historical labels after declarations and
mode switches, rejects switches during pending work, and checks no-op generation
stability. The existing test-only **new-owner** generation seed reaches genuine
successful switch saturation without modifying a live capture or rejecting a
semantic switch. It is reset immediately after construction and on failure.

Literal fixture: `R(x,y)` over `(7,9)` and initially empty `S(y)`, head `x`,
native R root with native S child. Inserting `S(9)` has mandatory support work
40, physical inclusive work 44 and exclusive work 4. Actual native event ID 1,
child event ID 2 with cause 1, and parent/leaf node IDs are checked directly.
Callback failure/retry, owning transfer, unread discard, trace capacity 3,
unsampled sequence and actual rollback are separate cases. All four explicit
observation modes retain identical mandatory literal work; off/counters make
zero optional clock calls. Capture compares pre/post native owner facts and
pending mandatory work, without advancing any owner.

`sessions` captures real created/running/pending/paused/draining/prepared,
committed, cursor, stopped and dropped facades. Stopped retains gauges; drop
releases runtime gauges/trace storage but keeps owned metadata and last summary.
Earlier captures remain byte-identical after mode changes, drop, facade
teardown and move. Typed window metadata-only pending work specifically has a
ready DeltaRuntime but unavailable gauges until the enclosing command commits.
Input, queue, window and snapshot limits are compared with native admission
context; they are not inferred from observations or benchmark labels.

`caps` preserves both actual accounting boundaries: cap 43 after raw physical
work 4 and completed support 40, and an enforced uniqueness scan with 100
existing S rows, cap 130 after raw physical work 107 and completed support 40
(uncapped total would be 147). Inclusive and exclusive physical registry
values must both remain **unavailable**, even when the retained raw numeric
payload exceeds support work. The heavy case independently requires 102
constraint rows and one validation. Neither cap changes committed results.

`authority` joins genuine upper, optimum and P07 candidate/family handles to
selected plans, rejects tree/binding/policy/family mismatches, and checks exact
node-budget boundaries. A relabelled equivalent selected tree may carry the
original minimum proof, but cannot masquerade as that exact upper/candidate.
The reference oracle independently checks the small positive fixture and the
nonempty cyclic triangle. A contradiction-marked nonempty triangle remains
P06 structurally infeasible while P08 supplies executable constant-false
operator height zero. An empty-body query has genuine original minimum zero.
This does not rerun or replace the separate full 437-input query corpus.

Native raw query values and caller benchmark labels can contain invalid UTF-8;
report capture still succeeds. Strict text export fails separately. Structure-
only tree/DOT export does not inspect unrelated benchmark labels. NUL/quote/
backslash/newline labels are transported exactly. This does not broaden P08's
existing admission domain or fabricate a P08 handle from raw invalid JSON.

`faults` exhaustively increments every allocation failure position until the
first success, with **persistent** failure through unwinding and no trial cap.
It covers composed capture, trace copy, committed gauges and all four exports,
plus pending/stopped/dropped session captures. After each failure, the same
operation succeeds on the same owner, and a deep native-value baseline, fake
clock count and retained report bytes must remain unchanged. No JSON DOM is
constructed by the test's native admission/fault helpers.

## Independent artifact checking

Each actual report emits `.json`, `.txt`, `.tree.json`, `.dot` and a line-based
`.expected` sidecar made from actual native owners/plans **before** capture.
Expected facts never come from serialized reports. Sidecars preserve raw
unavailable metric payloads, but the checker requires null wire values for
those unavailable measurements. It checks every runtime metric, complete
sampled numeric causal records, initialization, labels, begin/current options,
output actions, session status/admission fields, per-node gauges, cursor
configuration, every mandatory CursorWork field, and every cursor metric.
Selected tree nodes/scopes/edges/separators/connex membership come from the
actual admitted physical plan. DOT nodes/edges and human trace JSON are checked
against those native expectations; both V2 schemas are closed and are also
required to reject unknown top-level fields.

The C++ suite checks exact encoded length N succeeds and N-1/zero fails for
all four exports, including retained session reports after owner destruction.
The checker requires all scenario labels and all four modes for each repeated
runtime lifecycle point; partial output cannot satisfy `--require-all`.

Root execution examples (not executed by this author):

```sh
/tmp/crown-o07-composed-detached-tests-o0/composed-test /tmp/crown-composed-acceptance all
python3 docs/verification/o07-composed-explain-test-detached-proposal/check_reports.py \
  /tmp/crown-composed-acceptance --require-all \
  --repo-root /home/userroot/Codex/CROWN \
  --schema-dir docs/verification/o07-composed-explain-proposal/schemas
```

Native checker invocation substitutes `--schema-dir schemas`. No schema fetch
or generated report content is used to manufacture expected proof authority.

## Acceptance limits

Compiler success is not runtime acceptance. Root must run both test binaries,
checker, appropriate sanitizer/fault acceptance and native target closure,
with all subject pins checked before/after. Earlier layer suites remain
required: the full query oracle family, arbitrary session-input profiles,
cursor algorithms, configuration failure cases and mandatory work parity.
This suite exercises generation saturation through the existing sanctioned
construction hook; it does not claim to execute 2^64 trace drops or fabricate
a saturated trace snapshot. Native trace-drop saturation fields are copied and
checked at their actual values. Allocation-accounting, durability, recovery,
benchmark validity and cost optimality remain outside O07's established claims.

## Revision diagnosis and preservation

Original package `../o07-composed-explain-test-proposal/`, package SHA
`43d0cfd99fc93769d996b3e284e66bfaeb02d40d5aa12cd9223850b54a8d26e7`,
remains byte-identical. Root attempt 1 ran all five C++ groups successfully but
placed artifacts in subdirectories while the checker expected the documented
flat directory. Root attempt 2 used the flat layout: all five C++ groups passed,
73 reports were emitted, all 225 checked pins matched, and the checker exposed
a genuine **test-side expected-data omission** in the detached-owner fixture.
The detached report captured a real runtime, but its sidecar contained only
plan/height facts, so the checker correctly rejected its nonempty gauge bases
against the missing expected base records. Evidence remains in
`build/verification/o07-composed-explain-acceptance-attempt-{1,2}*`.

The revised lambda copies `owner_native(local)` before report capture and owner
teardown, checks that capture changes neither those native facts nor the fake
clock, and returns the independently captured facts alongside the report. After
the runtime has been destroyed, export uses that complete native sidecar plus
the independent literal-oracle height. No expected value is recovered from the
report. All original assertions, scenarios, exact schema/semantic comparisons,
required modes and persistent fault sweeps remain. The checker only gains file
context around its existing failure paths; no validation is relaxed.

Both strict builds pin the original test package as well as the frozen subject
and dependencies. This author only compiled/linked the revision; root must run
its binaries and checker anew. Earlier root results do not constitute runtime
acceptance of this revised package.
