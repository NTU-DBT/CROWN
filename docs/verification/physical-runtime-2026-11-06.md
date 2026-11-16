# Physical source and alias coordinator, 2026-11-06

Historical checkpoint. The later [D01 result-cursor packet](result-cursors-2026-11-06.md)
adds committed live enumeration; its source manifest describes the current
checkpoint. The manifest below describes this earlier physical foundation.

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. Physical-row identity, deterministic
alias routing, final-native derivation counts and their atomic coordination
with support maintenance are implemented. **R05 remains in progress for
integrated full-query delta/output acceptance.** The full 78-card goal stays
active: 21 verified, four in progress and 53 not started.

Contracts: [physical coordinator](../physical_runtime.md),
[logical prepared epochs](../prepared_epochs.md),
[support invariants and physical composition argument](../support_invariants.md).
The [prepared foundation packet](prepared-epochs-2026-11-06.md) and its manifest
describe the previous checkpoint.

## Acceptance scope and evidence

| Requirement or invariant | Current evidence |
| --- | --- |
| Complete physical-row set identity | Source `ReferenceTable`s use every source column as the key. Ignored/filtered columns distinguish physical rows while final-native counts can collide. Duplicate insert/absent erase consumes one sequence with no source/alias/support changes or charged work. |
| All source tables and constraints | Source storage includes unused tables and constant routes, using compiled layouts or supplementary private descriptors. Enforced unique/FK checks see the full proposed after-state; self-referencing insertion sees its inserted row. Unused FK targets cannot be deleted while referenced; untrusted declarations do not enforce uniqueness. The temporary full validation image is discarded and is not rollback state. |
| Correct per-occurrence projection counts | Each accepted source row changes the map keyed by that occurrence's final adapted native tuple. Different aliases have separate maps. Positive-to-positive changes retain native membership/handles; first/last derivations insert/erase exactly once. Compiled constant, repeated-variable and SQL-local filters are exercised. |
| Deterministic same-sign alias epoch | Routes use the compiled occurrence order, draining one logical stage before the next under one pending epoch. Loop-edge new–new terms, same-scope aliases, nullary/Boolean projections and hidden source columns agree with full recomputation under FIFO and LIFO. No public raw kernel/table reference can bypass the driver busy boundary. |
| Independent maintained-state checks | A separate physical-row assignment interpreter derives counts, native records and full subtree joins, then checks every node's candidates, child flags, S/P/E counts and reconstructed complete results. Raw-CQ cases also agree with A04. It verifies 450 states: 448 physical events and two empty constant initial states. Constraint/publication/resource/lifetime fixtures add targeted checks outside that count. |
| Affected undo and one publication boundary | One source journal plus prepared count-map insert/change/extract undo remains open beside the logical pending epoch. Any preparation failure reverses kernel, counts and source before clearing busy state. `prepare` exposes only unpublished owner diagnostics; valid commit performs no allocation and publishes one sequence for all state. Filtered/count-only/unused updates use an empty logical commit when needed. |
| Allocation failures after earlier aliases | Four exhaustive persistent `bad_alloc` sweeps cover 204 new-projection insert, 124 last-derivation erase, 21 existing-projection insert and 16 shared-projection erase positions. Later allocations remain forbidden during cleanup. Full physical/support/count snapshots, old handles, truth, sequence, live/retained/pin counts and old artifacts survive. Same-sequence retry equals a clean full epoch modulo owner IDs, including metrics/causes/ordinals. No commit allocation occurs. |
| Moves, cancellation and retained values | Explicit rollback, token destruction/move assignment and valid commit run with allocations forbidden. Active facade moves preserve owner/handles/busy state. Commit and rollback after facade destruction are covered; returned full-row source pins and logical journals survive table destruction. Caller-held history retains affected payloads plus declared arena high-water metadata. |
| Preparation hook for later output | A caller can stage private output while the physical pending token keeps source/count/kernel unpublished. A forced allocation failure during private staging leaves cancellation/retry available and restores state. This test stages local diagnostic data; it is not full-query delta/spool/sink acceptance. |
| Compatibility | Frozen physical-plan v1, support-trace v1 and support-report v2 schemas, logical support API/kernel and support codecs are unchanged against the prior manifest. All 41 earlier tests remain alongside the two new physical-runtime executables. No physical trace codec or CLI execution command is introduced here. |

The root implemented the coordinator, semantic interpreter, physical composition
argument and integration. Luna Max supplied fault/lifetime/staging tests,
contract documentation and a separate read-only undo/publication review. That
review found no concrete ordering defect. Initial fixture/test issues were
corrected before the final runs (tree connectivity, null journal on a
projection-only update, and assertions outside allocation-forbidden scopes).
This is internal finite evidence, not the outstanding external G2/V02 review.

## Verification matrix

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 43/43 pass | 56.65 s |
| GCC 13.3 Release | 43/43 pass | 7.89 s |
| ASan/UBSan including parser C | 43/43 pass | 292.62 s |
| Clang 18.1.3 C/C++ Debug | 43/43 pass | 44.08 s |
| Fresh source-only Release | 43/43 pass | 8.14 s |

All verification process handles are terminal and successful. The fresh
configure/build/test took 218.12 s and removed its temporary source/build tree.
Native warnings remain errors; ASan/UBSan include parser C, enable leak
detection and halt on errors. Production/test algorithms were unchanged
through the final matrix.

Support CLI: 25 checks/34 manual logical states pass in CTest and under
Python `-O`. The optional schema audit passes 18 schema meta-checks,
26 normalized artifacts, 19 identity artifacts, 59 admission artifacts,
two layout/projection artifacts, 31 physical artifacts, three support traces/
reports and two rejected-update reports. The prepared
physical library has no new serialized input/report format; the existing
logical trace remains one v1 envelope containing an `updates` array.

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
python3 -O tests/integration/support.py build/debug/crown .
python3 tools/verify_schemas.py build/debug/crown
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/physical-runtime-clean-source.log
sha256sum -c docs/verification/physical-runtime-sources.sha256
```

Logs are ignored `build/verification/physical-runtime-*.log`. The
[455-input source manifest](physical-runtime-sources.sha256) records source,
build, test, fixture, dependency and ordinary-contract inputs. All fingerprints
pass. Packets/manifests and mutable handoff/ledger files remain excluded.

## Limits and continuation

`PhysicalRuntime` starts empty; R06 must define bootstrap and compare replay
with direct bottom-up construction. Full-result/fragment cursors, actual
full-query deltas, witness partition/liveness and bounded delivery remain
D01–D06/O06 work. Local membership events and a diagnostic join of E relations
are not emitted global deltas. Scalar EXISTS output also needs its Boolean-row
replacement semantics through the existing SQL output mapping.

The reference backend uses ordered containers. Aggregate physical work
includes nested support work but does not fully measure constraint scans,
comparisons, allocator bytes, value width, snapshots, serialization or cleanup.
The nested support cap is independently enforced; S04/S05 optimization and
budgets remain open. The frozen `GuaranteeProfile` remains a compile-time
artifact, not a certified runtime complexity profile. No cursor-delay bound,
integrated SQL output executor, durable recovery or R1 release is claimed.
