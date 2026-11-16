# S05 native invariant diagnostics

9 November 2026. Incremental implementation of Refactor.md S05. The full goal
remains active; ledger41 verified,3 in progress (A02/S05/O06),34 not started.
Whole-query and full native/fresh-source acceptance remain open.

## Implemented change

Invariant issue arrays and compact owned keys now use the original query account
under capture:15. Support expected candidate/survivor/projection collections,
physical database/derivation/native-record comparisons and Delta expected live
factors, separators and regrouped buckets use actual accounted native storage.
The private physical record-row helper returns native rows; check_invariants no
longer creates an ordinary full support snapshot internally. Native database
validation reuses already admitted immutable catalog metadata.

The independent invariant computations, localized fields, issue order, work
counters, issue/work stops and version1 encoded bytes remain intact. Copies fund
new issue payload from their original account; moves and final release allocate
nothing. Memory failure preserves the runtime and prior reports. Existing native
cursors/projections retain their own attributions in the same account. See
[the public contract](../invariant_memory.md).

## Focused evidence

Production source1 compiles without diagnostics. Source3 adds only the new
fixture/tests and corrects one new-test indentation warning. Focused Debug passes
3/3 in13.20s: invariant_memory, runtime_inspection and operator_memory_report.
All existing tests and the runtime diagnostic schema are unchanged.

The new actual test covers42 owner/backend/tree/scalar configurations: three
owners, both backends, three C02 shapes with integer and wide NUL-string data,
plus a singleton containing string, Boolean, date and38-digit decimal values.
Every upstream request is reconciled with original-account successful requests
for healthy/corrupt inspection, check_invariants and report copying. All22–171
persistent inspection positions per case, and every copy position, are faulted.
Current storage and older reports survive; retry and corruption restoration pass.
Exact/one-under work and issue limits, genuine hoarded-report byte peaks with
same-cap release/retry, retained readability and controller-only release pass.

An independent probe was compiled against all frozen predecessor headers and
untouched old Release archives before rebuilding those modes. It emitted210
actual reports: healthy, corrupt, zero-work, zero-issue and partial, for all42
configurations. Every new packet matches the predecessor byte for byte and
satisfies the unchanged runtime-diagnostic-v1 schema. The new invariant_wire case
checks those independent reference digests from a clean source tree too.

Source4 adds the repeatable frozen-wire test. Source5 explicitly includes both
new guides and freezes982 paths; its C++/tool/fixture inputs are unchanged from4.
Final source7 changes documentation only from5. Draft6 and the failed first
closer are preserved; they initially described the dependency diagnostics too
broadly as zero compiler warnings.

| Mode | Scope | Result | Seconds |
| --- | --- | --- | ---: |
| Debug | Full registration |227/227 PASS |911.41 |
| Release |117 selected cases |117/117 PASS |21.00 |
| Clang18 Debug |117 selected cases |117/117 PASS |101.28 |
| ASan+UBSan/leaks |117 selected cases |117/117 PASS |567.85 |
| Fresh source-only Release |Full registration |227/227 PASS |155.29 |

The selected set uses105 actual native targets per mode. Full Debug names190
native executables. The first inventory pins505 actual binaries and four caches;
the fresh inventory pins190 additional freshly built binaries. All210 reference
packets also pass the repeatable wire case in each tested mode. No predecessor
broad result is treated as verification of this code.

The fresh snapshot contains exactly982 pinned source files, including local
dependency archives. It starts with no cache, object or library. Its actual334
project C++ commands/objects are inside that snapshot, use C++23 and strict
warnings, and use no original source include paths. The local parser contributes
96 freshly compiled C objects. Its27 libraries and436 generated native flag/link
records are pinned. All eight successful build attempts have zero project
compiler diagnostics. The fresh dependency build emits the exact three previously
documented diagnostics: one Make scheduling warning and two upb
`-Wmaybe-uninitialized` warnings for `sv.data`/`sv.size`. Exact lines/counts,
the archive pin, recipe/lock and unchanged extracted Makefile/upb source are
checked against [the existing narrow policy](observability-matrix-review-2026-11-07.md).
These warnings are not claimed safe, fixed or false positives. Every project
warning or additional/changed dependency diagnostic still fails the audit. No
compiler flag, assertion, fixture value or timeout was weakened.

## Preserved history and next work

The sealed [operator report predecessor](s05-operator-memory-native-2026-11-09.md)
has976 verified source preimages. All source maps, raw failures, old/current210
report packets, old probe sources/executables/archive hashes and executed helpers
remain under `build/verification/s05-invariant-diagnostics-native-*`.

The first new memory test hit a strict indentation warning; the next source
separates the same loop and following declaration. The first old-probe compiler
helper lacked the preserved vendor include path; its successor adds that path.
The first comparison helper needed a local schema base URI for the unchanged
sibling CQ schema; its successor resolves locally. Failed helpers/receipts remain
intact. None required changing production code, old tests or schemas.

All27 recorded jobs are closed. Every terminal CTest stdout was saved before
another run/enumeration. The source review confirms zero existing test/schema/
tool changes. A bounded62-match runtime allocation/caller census distinguishes
accounted containers, explicit DTO exports, borrowed inputs and public exception
presentation; runtime owner statistics uses the native capture path. This census
is not an exhaustive compiler/I/O allocation proof.

Final [progress](../../build/verification/s05-invariant-diagnostics-native-progress-v1.json),
[source inputs](../../build/verification/s05-invariant-diagnostics-native-inputs-v7.json),
[wire comparison](../../build/verification/s05-invariant-diagnostics-native-wire-compatibility-v2.json),
[fresh build audit](../../build/verification/s05-invariant-diagnostics-native-fresh-build-audit-v1.json)
and [checkpoint seal](../../build/verification/s05-invariant-diagnostics-native-checkpoint-seal-v1.json)
bind this scope. The separate post-seal-audit-v1.json records independent readback
of sources, preimages, packets, actual binaries/objects/libraries, flags and links.
The exact pre-existing dependency warning disposition is retained in
pinned-dependency-diagnostics-v1.json; close-checkpoint-v2.py supersedes the
preserved failed first closer without changing code or rerunning tests.

Root performs the implementation and verification. A requested small Luna Max
census could not start because the agent thread limit was reached; root completed
it directly. No Astra was used. Keep terminal CTest stdout before another run or
enumeration, and do not build during CTest in the same directory.

Next: complete the compiler/I/O ownership/work review and full Clang/sanitizer
registration before S05 acceptance. Fresh Release full227 is already verified
for this code; preserve that scope when later code changes. Continue from
[the handoff](../handoff.md); the full78-card goal stays active.
