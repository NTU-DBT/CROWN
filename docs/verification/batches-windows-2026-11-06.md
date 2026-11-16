# O03 transport batches and operational windows, 2026-11-06

O03 is implemented and verified. All 79 tests pass GCC Debug/Release,
ASan/UBSan, Clang and fresh source-only Release with stable native sources.
Independent source/contract/coverage acceptance is satisfied. The complete
78-card goal remains active: 32 verified, four in progress (A02/P04/P06/O06),
42 not started. No broader recovery, durable delivery or release gate is inferred.
Baseline remains uncommitted master at
`e369a623517723b3be3ea3e9806779f3c591e7f9`; preserve original Refactor.md and
all legacy trees. The prior [R06 packet](runtime-initialization-2026-11-06.md)
and 513-input manifest remain historical and unchanged.

Original requirement: [Refactor.md](../../Refactor.md), O03. Architecture is
in the preceding [Astra preflight](o03-design-preflight-2026-11-06.md).
Mandatory scope is ordered R1 transport plus operational windows. Optional
R2 atomic net batches are explicitly disabled for this increment.
The full goal still includes later R2/W06/V04 transaction and release work;
disabled optional R2 does not imply that those cards are complete.

## Implementation and requirement scope

- Root: [transport types](../../include/crown/io/batch.hpp),
  [owned typed queue](../../src/io/batch.cpp), shared validation and build wiring.
- Astra: [window types/controller](../../include/crown/runtime/window.hpp),
  [prepared label/count/index steps](../../src/runtime/window.cpp),
  [session API](../../include/crown/runtime/session.hpp) and
  [session coupling](../../src/runtime/session.cpp).
- Luna Max: independent transport partitions/A04, plain-label window reference,
  and persistent-allocation fixtures are authored separately.

Transport batches preserve event order and commit/output barriers; admission
bounds owned storage and leaves rejected caller batches intact. Queue head
validation preserves earlier accepted prefixes, and open-empty is distinct
from closed-empty. Engine failures retain the head for retry.

Window policy uses explicit managed tables, initially empty, positive checked
uint64 width, strict late insertion rejection and deadline <= watermark
expiration. Positive insertion labels increase without reuse. Global or
per-relation FIFO means oldest live insertion label, with whole-watermark
preflight before its first effect. This establishes no physical-row FIFO
theorem when duplicate labels share one row. Full physical rows are counted;
only zero crossings produce physical events.

External command sequence, physical sequence and watermark expansion progress
remain separate. A prepared step allocates metadata before genuine D06 engine
work; after publication only nonthrowing node/scalar changes and whole-command
source acknowledgement remain. Metadata-only steps do not fabricate epochs.
Pause/one-step drain/output/stop/drop and partial-watermark snapshots retain
the O02 ownership rules. Diagnostics are not recovery/checkpoint state.

| Original O03 obligation | Acceptance evidence |
| --- | --- |
| Ordered R1 individual-event semantics | All eight partitions of a four-event insert/erase trace, self-join aliases, projection collisions, typed initial data and raw signed/snapshot comparisons with independent A04 preserve every barrier. |
| Expiration queue and declared late/watermark policy | Plain label-list model checks boundary equality, nonmonotone times, overflow, decreasing watermarks, duplicate full rows, zero/many expiration steps and exact prefix/source progress. |
| FIFO labels or explicit violation rejection | Global and per-relation oldest-live-label rules and whole-watermark preflight reject actual order violations before the first effect. Label FIFO makes no physical-lifetime theorem claim. |
| Separate atomic net semantics if enabled | R2 is disabled; TransportBatch remains ordered R1. Later R2/W06/V04 work must implement its separately typed whole-transaction API and independent acceptance. |
| Operational ownership and failure integrity | Bounded transactional admission, private real D06 or metadata steps, per-step drain, delayed acknowledgement, persistent failure/retry, sequence maximum and allocation-free publication/cleanup pass. |

## Independent acceptance and failure disposition

The initial Debug module integration build passed. Existing session semantic
and persistent-failure suites both pass (0.41 s combined). New transport
partition/A04 and actual-owner physical-sequence boundary tests both pass
(0.03 s combined). Retained logs are under ignored
`build/verification/batch-window-*`, including integration builds,
`batch-window-existing-session-tests.log` and
`batch-window-transport-boundary-tests.log`.

Independent read-only Astra review found one real source defect: session begin
rejected every window command at physical sequence maximum, including count-only
changes and empty watermarks. The fix checks advancement only for real physical
transitions and reports retryable resource exhaustion. Four additional private
testing-archive probes seed actual support/physical/live/window/session sequence
tags together; the boundary fixture verifies metadata-only commitment at max,
unchanged physical-failure prefix/cache and same-head retry from max-1 to max.
Production defines no corresponding probe. Follow-up source/contract review
found no remaining source-level blocker, conditional on independent acceptance.

The first transport run exposed an empty-batch descriptor assumption. Empty
batches now retain no allocation and work with zero capacities. The frozen
transport fixture then passed. A draft window fixture's namespace typo was
corrected before compilation. No behavioral assertion was weakened.

All four targeted suites now pass: transport and sequence boundary 0.03 s,
independent window reference 0.05 s and persistent failures 1.67 s. The list
oracle checks exact labels/full-row counts/FIFO/expiration state, expansion and
source progress, self-join/projection results, and raw signed SQL output.
Its SQL EXISTS reference uses an explicit physical-source Boolean CQ and
independent Boolean wrapper, keeping the actual normalized SQL runtime path.
Observed fault positions are constructor typed/windowed 52/57, queue admission
1, new-source peek 1, alias begin/step 21/364, window insert begin/step 31/84,
duplicate metadata 6, watermark preflight/first step 20/60, and later-watermark
begin/step 18/65. Full successful targeted fault output is retained in
`build/verification/batch-window-targeted-fault-output.log`.

Fixture-only corrections preserved oracle/rollback checks: exact expiration
deadline, physical versus normalized core SQL schema, counter capture before
assertion-text allocation, and finishing the already-pending successful
metadata-begin sweep. Independent Astra acceptance of actual sources and
fixtures found no remaining blocker. Their final-matrix condition is now
satisfied. Reviewers provided no external mathematical or release signoff.

The final 79-test five-configuration matrix passes. Frozen native/test
fingerprint (435 inputs):
`e035d699fe49312aea9307c43e597eb70af6989db295b84205baf85c806a64b0`.
Definition is sorted path/NUL/content/NUL over CMake files and
include/src/apps/tests/cmake, excluding Python caches. No native source changed
during the final matrix. The ordinary inventory has 522 inputs; the current
manifest and independent hash/link/ledger audit are recorded after the source
seal below. Handoff, ledger and verification files are excluded.

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 79/79 pass | 191.67 s |
| GCC 13.3 Release | 79/79 pass | 22.73 s |
| ASan/UBSan, including parser C | 79/79 pass | 842.91 s |
| Clang 18.1.3 C/C++ Debug | 79/79 pass | 147.02 s |
| Fresh source-only Release | 79/79 pass | 21.56 s |

All five processes are terminal/successful and closed. Clean verification
took 395.09 s overall and removed
`/tmp/crown-clean-source-5p2rv3h3`, independently confirmed absent. Per-config
summaries/logs and retained successful output use
`build/verification/batches-windows-*`. No observation timeout was treated as
completion or used to restart a live process.

Final Release schema audit passes 20 meta, 26 normalized, 19 identity,
59 admission, two layout/projection, 31 physical, three support, two rejected
reports, two physical input events and three actual runtime diagnostics.

A separate read-only Luna Max audit confirms every in-place raw CTest log has
79 passed markers and no failures, the same five D04 2712/1408/2504 records,
and four D05 N=2/64 insert 69/63/10 and erase 62/77/10 profile rows with
preparation/finalization retained. All thirteen O03 sweep counts above match
across Debug, Release, Clang and sanitizer. O01 constructor/peek/replay counts
remain 18/18/18, 33/15/10 and 79/122; O02 create/begin/prepare/snapshot/drain
remain 57/48/75/7/14. R06 initialize/rebuild/session/writer counts match its
preceding record. These are observed quantities, not API allocation guarantees.
The clean wrapper confirms its aggregate 79/79 result; detailed passing-test
stdout is retained for the in-place runs.

Generated compiler metadata confirms GCC C/C++ 13.3.0 and Clang C/C++ 18.1.3.
Sanitizer compile commands instrument batch.cpp, production/testing session.cpp
and window.cpp, all four new fixtures, and the parser C recipe with address/
undefined sanitizers and frame pointers. `nm -gC --defined-only` confirms zero
RuntimeTestProbe methods in the production archive and eleven in testing.
The audit is retained in
`build/verification/batches-windows-matrix-evidence-audit.json`; its sanitizer
pending flag is false. The reviewer ran no builds/tests and restarted no jobs.

## Source seal and reproduction

The [522-input manifest](batches-windows-sources.sha256) adds eight native/test
files and the batch/window contract to R06's 513 inputs. Manifest SHA-256:
`8316958f70a7edbfd7eb07a331f98de74b3a999b5b1471e93a30db2e4cf4cd11`.
Independent Luna Max validation passes `sha256sum -c` for all 522 entries,
separately rediscovers the exact same inventory and recomputes the 435-input
native fingerprint. Historical hashes match. All five summaries report exit
zero/79 tests; the clean temporary path is absent. The ledger has 78 unique
original card IDs, and table/footer/handoff agree on 32 verified, four in
progress and 42 not started, with P04 next and the full goal active.
Across 42 documents (README, root documentation guides, current packet and
O03/P04 preflights), all 475 checked local destinations resolve; 16 external
links were excluded. Full checksum output and independent JSON records are
under `build/verification/batches-windows-audit/`, including
`sha256-check.stdout.log`, `o03-independent-audit.json` and
`o03-markdown-link-audit.json`. Aggregate proof is retained under ignored
`build/verification/batches-windows-summary.json`.
The audit found one stale O02 ledger cross-reference listing O03 as open;
it now identifies O03 as separately verified. Only the excluded ledger changed,
so the sealed ordinary sources, native fingerprint and manifest hash stayed
unchanged. The audit-result placeholder was replaced with the evidence above.

Historical manifest file hashes remain R06
`aad918ee2b93ccc511d7c72c2de47d354c281a285b40c5d2825dd189e03475a4`,
O02 `ed176b672510b915328cda857bd1d7ec8b6c9e58c71de3001b689a9a98896b1a`,
O01 `394ea5788f1d2dd41a465f8cc591c6e8d535fdff421c8887f1ca14255119fb6d`,
D06 `3300aa4d412930322bbbeb74fe88b0ec3be78586794616cc226d1d67545e1665`.
Refactor.md remains
`bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce`.
Historical manifests identify their own snapshots and are not resealed against
the current tree. The existing Clang directory binds Clang 18.1.3 for C/C++;
the [native guide](../native_build.md) records toolchain prerequisites.

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug --output-on-failure
cmake --preset release
cmake --build --preset release --parallel 2
ctest --preset release --output-on-failure
cmake --preset sanitize
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize --output-on-failure
cmake -S . -B build/clang-debug
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 tools/verify_schemas.py build/release/crown
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/batches-windows-clean-source.log
sha256sum -c docs/verification/batches-windows-sources.sha256
```

Next is P04's remaining certified exact planner paths; its
[read-only Astra preflight](p04-design-preflight-2026-11-06.md) is preserved.
The full 78-card goal remains active. S04/S05, complete recovery/durable delivery,
later R2 transaction/weighted work, external review and release gates remain open.
