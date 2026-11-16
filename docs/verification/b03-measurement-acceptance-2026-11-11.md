# B03 measurement harness acceptance

B03 is verified on11 November2026. The full Refactor goal remains active:
49 verified, one in progress (A02),28 not started,78 total. No R1 release,
fixed speedup or comparative performance result is claimed.

Root implemented and reviewed the collector, runner, schemas and acceptance.
Luna Max provided one bounded read-only public-API inventory; no Astra was used.
Baseline is `e369a623517723b3be3ea3e9806779f3c591e7f9`; the broad worktree is
uncommitted, so exact source/artifact hashes identify the tested implementation.

## Result and implementation

The [measurement guide](../measurement.md) documents the finite controlled
runner and public native example. Every admitted case/backend/output mode passes
a separate independent native verification before compilation warm-ups,
compilation samples or execution repetitions. Actual native storage and runtime
modes supply report labels. Measured children do not load oracle data.

Raw records separate query compilation, buffered file input, artifact validation,
empty owner/reader/sink setup, decoding, native prepare/commit and pending-owner
cleanup, full cursor or committed delta-spool calls, external encoding, sink
write/wait, tuple/cursor/epoch cleanup and acknowledgment. Diagnostic capture,
loop wall, sink close and teardown retain their own scopes. Every loading prefix
is processed from empty and remains in inclusive totals and phase partitions.

O07 counters preserve registry units, availability, saturation and overlap rules;
C01 cells retain descriptors, histogram bins and collection metadata. Mandatory
delta counters are explicitly at commit. Optional disabled observations remain
disabled. Native current/payload/allocation/cumulative-peak bytes are distinct
from process maximum RSS. Raw per-event/per-call samples and exact nearest-rank
p50/p95/p99/max, means, sample standard deviations and power-of-two histograms
retain empty/singleton availability. Warm-ups remain raw and are excluded from
measured summaries.

Actual sources/headers, objects, binaries, linked archives, compile/link commands,
compiler binary/version, CMake cache, dependency lock, harness sources, repository
HEAD/change status and environment identify a run. CPU, affinity, actual thread
count, governor observations and allocator context are recorded. Source/header
newer than its object is rejected. Compiler dependency records require Makefiles
in this version; loaded system libraries are not archived.

## Actual checks

All12 selected fresh-source Release CTests pass in22.05s. Both new B03 tests and
ten predecessor tests run: workload manifest/replay/imports, CLI workflow/moved
installation, schema/admission fixtures, reference fuzz, C03 model and C02 ranking.
The predecessor replay again checks560 native replays/9944 physical epochs.
This is selected integration, not a full279-test release run.

The exact copied source has1659 files and no old cache/objects. All1651 sealed
B02 predecessor paths remain; existing runtime, public headers, tests and
generated query/trace bytes are unchanged. Six predecessor build/documentation
files change and eight new B03 files are added. All277 generated predecessor
test commands and properties are preserved, with only the two B03 additions:
279 registered. Every sanitizer registration retains ASan leak/halt and UBSan
halt/stacktrace settings.

The native collector passes30 configurations/60 actual invocations in each of
GCC Debug, GCC Release, Clang18 Debug and ASan+UBSan/leaks Debug. Five independent
B02 mechanisms cover composite separators, Boolean results, self-join churn,
wide strings and projection with charged deletion loading. Both storage backends,
all three output modes and optional off/counters/timed observations are checked.
Verification/current/delta results and encoded measured rows match the independent
oracles; mode labels, memory peaks and disjoint timing sums agree.

Persistent final controlled packets retain12 mode/backend configurations ×three
runs (one warm-up/two measured), plus a separate two-mode Boolean packet with
disabled observations/workload/codec, actual single-CPU affinity and100us sink
wait. The integration check independently recomputes raw distribution totals and
histogram memberships, checks the complete correctness gate before any timing
run, validates closed schemas and confirms compile warm-ups are excluded.

Six native negative cases reject a corrupted oracle, Boolean request version,
zero encoded-byte grant, one-call grant, one-byte native memory grant and zero
event grant without emitting a measurement. The encoded-byte failure writes no
sink bytes. An owned-child timeout retains its raw command/failure record;
unknown report fields are rejected. The earlier failed controlled packet has
no timing runs and remains labeled failed.

The moved installed example passes12 independent SQL/backend/mode cases and33
commands. Its separate CMake project compiles under strict C++23 against moved
public headers and production archives, without source/build/test/reference
dependencies. This also runs in the final fresh-source integration.

## Audited evidence

The [matrix audit](../../build/verification/b03-matrix-audit-v1.json) passes:
2082 actual artifacts,127 fresh C++ translation units, six fresh ELFs,16 build
CROWN archives, four compiler controls and all ten requirement mappings. Strict
project warning/error flags and test `-UNDEBUG` remain. Only previously reviewed,
unchanged pinned parser/Make diagnostics appear; no warning relaxation is used.

Authoritative records under `build/verification/`:

- [Tested source manifest](../../build/verification/b03-measurement-inputs-v1.json)
  and [exact fresh copy](../../build/verification/b03-measurement-fresh-source-v1.json).
- [Fresh closed driver](../../build/verification/b03-fresh-driver-v1.json),
  [CTest receipt](../../build/verification/b03-fresh-ctest-v1.json) and
  [archived raw output](../../build/verification/b03-fresh-ctest-v1.stdout.log).
- [Final persistent runner acceptance](../../build/verification/b03-controlled-acceptance-v3.json)
  and [raw controlled packet](../../build/verification/b03-controlled-acceptance-v3/controlled-file/experiment.json).
- [Moved-install acceptance](../../build/verification/b03-installed-development-v2.json)
  and [sanitizer registration audit](../../build/verification/b03-sanitize-registration-v1.json).
- [Ten-requirement/source review](../../build/verification/b03-requirement-audit-v2.json),
  [documentation successor](../../build/verification/b03-measurement-inputs-v2.json),
  [final seal](../../build/verification/b03-checkpoint-seal-v1.json) and
  [post-seal audit](../../build/verification/b03-post-seal-v1.json).

All original1651 preimages remain in `b03-measurement-preimages-v1`. Historical
failures stay preserved: early strict compile errors, actual backend mislabel
rejected before timing, GNU-extension example rejected before functional runs,
and an audit-only missing receipt-field assumption. Corrected evidence supersedes
them without weakening flags, contracts or checks. All jobs are closed.

## Limits and continuation

This profile measures the volatile native core, funded EventReader and external
codec/sink. It performs no WAL, checkpoint or sink fsync. O08's durable-file CLI
benchmark has a separate broader scope. Query account bytes exclude caller
streams, standalone compiler/report/encoding DTOs and process overhead; its peak
is cumulative, not a phase-local peak. Raw stdout/stderr limits are checked after
each child, with separate per-child encoded/report grants. Cache/frequency state
is observed, not controlled; finite quantiles are not confidence intervals.

Real dataset/license qualification, baseline reproduction, C07 held-out ranking,
B04 component comparisons, B05 scalability/churn curves and full release gates
remain open. Do not infer a project license, pool unlike output/durability scopes
or turn functional methodology acceptance into a speedup claim. Continue from
the [handoff](../handoff.md); the complete goal remains active.
