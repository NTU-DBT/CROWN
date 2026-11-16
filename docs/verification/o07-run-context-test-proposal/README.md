# O07 run-context independent test proposal

O07 remains excluded and **not_started**. This is a standalone test source for
the prepared run-context overlay in `../o07-run-context-proposal/`. It does not
modify that package, the earlier O07 proposals, native source, build files, or
the accepted runtime-observation test suite. The test source is intended to be
compiled and linked against a complete matching overlay archive; root owns all
execution and result recording.

## Six focused groups

1. **Initialization routes and exact build options.** Compare empty
   construction, empty direct initialization, empty insertion replay,
   populated direct/replay, rebuild, and a rejected zero-work build. Literal
   database state and the independent evaluator check semantics. Empty
   construction must have no applied `BuildOptions`; successful initialized
   and rebuilt routes retain the exact method and work cap.
2. **Owned session contexts and admission failure.** Exercise owned CSV stream,
   typed physical, and typed window session constructors with independently
   specified input, limits, queue/window settings, snapshot policy, build
   options, requested delta options, and resolved policy. Saved immutable
   handles are checked after stop, drop, and session destruction, including
   strict JSON export. A persistent global-`new` failure sweep checks that
   admission never publishes a partial session and that later construction
   recovers. The sweep does not claim allocation-free admission; creating the
   owned metadata is intentional.
3. **Actual output disposition.** Check retained and suppressed output,
   duplicate no-op publication, partial transfer then discard, rollback,
   late cleanup of an older empty epoch, paused completion drain, and a spool
   limit abort. Each case checks the actual disposition flags, literal signed
   rows where present, mandatory transfer/discard counts, and unchanged
   independent query results.
4. **Begin-bound labels and strict export.** Change declarations during open,
   committed, and aborted attempts. Missing and empty strings, embedded NUL,
   and invalid UTF-8 bytes are represented separately. Native labels remain
   accepted; only JSON export rejects invalid UTF-8. The test parses actual
   output, checks current and historical declarations independently, verifies
   the caller-declared/unmeasured provenance fields, and tests exact encoded
   size versus one byte too small.
5. **Callback retries and deferred discard.** Two serializer allocation
   failures, a failed sink, a successful retry, and a callback-triggered
   deferred discard exercise actual callbacks. Invocations, failures, and
   acknowledgments are asserted separately; callbacks see the same unacked row
   on retry, then the remaining literal output. A separate allocation fault
   path preserves the owning runtime state.
6. **Mode parity, work limits, clocks, and cleanup.** The same Q update uses
   valid `capture_transitions=false` options in off, counters, timed, and trace
   modes. Its independent result and state, support work 40, physical work 44,
   exclusive work 4, and 39/40 cap error/rollback are checked. A test clock
   must remain unread in off/counters and be read by timed/trace. Global
   allocation counts are compared across modes for mutation and cap-failure
   paths; pending rollback and already-owned output release are asserted to
   allocate zero times. Trace mode must retain a bounded begin-to-commit
   record sequence.

The shared Q fixture is the literal query `Q(x)=R(x,y),S(y)` with a native
root `R(x,y)`, native child `S(y)`, and initial `R(7,9)`. Inserting `S(9)` has
the independent SQL result `{7}`. The mode group pins the already-established
mandatory support and physical costs at 40 and 44. It does not infer its
expected result or those costs from observation snapshots. Observation
`delta_work` is cross-checked against the pre-existing epoch metric as a
registry reconciliation, not treated as an independent cost oracle.

## Build identity and handoff

The intended include precedence is **run-context → mode-binding → runtime →
native → tests/reference → system third-party**. Compile this source with
`CROWN_RUNTIME_TESTING` against all nine matching runtime translation units;
link the companion exporter object built against those same headers. The
matching test archive supplied for this proposal is:

`/tmp/crown-o07-run-context-testing/libcrown_runtime_o07_run_context.a`

SHA-256:

`f51517193ff96c7582f5066507cb59f2f9ab487248540579e0499bca689e75f2`

The companion `run_context.cpp` testing object is:

`/tmp/crown-o07-run-context-report-testing/0.o`

SHA-256:

`39c21d74855d00f89fdd86bccba1eef7a458f2201b40258436357a6b46b7566f`

The exporter source has SHA-256
`abf003f7966f36beb55cf831cc9481317514b3f682b5942c03e13680a0bf135b`.
Use the pinned Release non-runtime archives in this order after the test and
exporter objects: runtime archive, `libcrown_reference.a`, `libcrown_plan.a`,
`libcrown_sql.a`, `libpg_query.a`, then `libcrown_core.a`. Do not link a prior
run-context, mode-binding, or native runtime archive against this ABI.

The strict compiler-only source check used C++23, `-Wall -Wextra -Wpedantic
-Wconversion -Wsign-conversion -Werror -O0`, and `CROWN_RUNTIME_TESTING`.
Compilation and linking completed; the resulting test source and artifacts
are:

| Artifact | Path | SHA-256 |
| --- | --- | --- |
| Test source | `docs/verification/o07-run-context-test-proposal/run_context_test.cpp` | `368a6981bd1f9d938329582cdfa759e4cac43bc7892dbec8639743da23b9d732` |
| Test object | `/tmp/crown-o07-run-context-test.o` | `0f54294a1c777075ad33da72133748542ad07114fad97990a8c73da42a375424` |
| Linked test binary | `/tmp/crown-o07-run-context-test` | `1376a0f5937206facf1005f6d8e54d7a4bdb8d27e07a811067e1a486fbc74c0c` |

The source and README describe preparatory expectations only. No executable
is run by this proposal. A pass here would cover the six runtime-context
groups above only, not remaining O07 EXPLAIN/CLI/schema, cursor/report,
benchmark, S05, S04/A02, or full configuration-matrix acceptance.

## Subsequent root-owned correction and execution

Root corrected only two existing-contract fixture assumptions: typed queue and
window inputs leave wire total_bytes absent while retaining finite queue/batch
byte caps; the CSV stream still tests its finite wire cap. The mode trace must
include a commit marker before post-commit transfer, rather than require commit
as the final record after delivery. Original artifacts/hashes above describe the
author's unexecuted first revision. Accepted source is now
`ed2e415340cf7bc2bd9dab4c611713548e9a72238fbb358b9a04a4ed069a926a`;
root's rebuilt binary is `/tmp/crown-o07-run-context-root-attempt-3/test`, SHA
`22cdea75a5249ebbde5592e4c707930a0b83a7c0935fb1a28dc78e59274ba9ad`.
All six groups pass in root attempt 3; see
[the root result](../o07-run-context-root-results-2026-11-07.md). No product overlay
or native source changed. Separate sanitizer and remaining O07 gates are not
inferred from this standalone pass.
