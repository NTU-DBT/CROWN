# Prepared logical epoch foundation, 2026-11-06

Historical checkpoint. The later [physical source/alias coordinator](physical-runtime-2026-11-06.md)
wraps this logical token; its manifest describes the current checkpoint.
The manifest below describes this earlier foundation.

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. This is an R05 prerequisite,
not completion of physical-base routing or full-query delta publication.
R05 remains `in_progress`. The full 78-card goal remains active: 21 verified,
four in progress and 53 not started.

Contracts: [prepared epochs](../prepared_epochs.md),
[runtime support](../runtime_support.md),
[conditional invariants](../support_invariants.md),
[R04 journal decision](../decisions/0013-support-journals.md).
The [R04 packet](runtime-journal-2026-11-05.md) and its manifest are historical.

## Implementation and evidence

| Property | Implementation and check |
| --- | --- |
| One unpublished logical epoch | `begin_epoch(sequence, sign)` prepares a move-only `PendingEpoch`. Every stage drains before the next, sharing one metadata/table undo scope and one sequence. Public state reads and writes reject while busy; owner-only previews/snapshots remain unpublished. Semantic and fault tests exercise both sides of the publication boundary. |
| Same-sign composition and cross terms | All stages insert or all erase. Manually staged forward/reverse edge aliases form new–new loop terms before a single commit. Same-scope aliases and Boolean/nullary projections preserve local support counts. Published root answers match the independent A04 evaluator for these small fixtures. Physical routing is not exercised or claimed. |
| Shared events and work | Changed native stages each receive a new aggregate ID/cause 0. Descendant events identify their immediate causal enqueuer, forming a forest rooted at those native events. IDs, applied ordinals, journal ordinals and metrics span all stages. Only new applied-ID flags are scanned/charged after each drain. No-op stages add no events or work. |
| Whole-epoch rollback | Invalid tuples/nodes, work exhaustion, support overflow, explicit cancellation and destruction restore the pre-epoch snapshot, sequence and public handles. Free arena high-water capacity may grow; live/retained/pin counts match when no tentative preview pins are retained by the caller. A failed stage closes the token, allowing same-sequence retry. |
| Allocation failures at later stages | Isolated persistent `bad_alloc` sweeps reach 158 insertion and 101 deletion failure positions across begin and all three stages. Further allocations remain disabled through undo. Old journals, full snapshots, counts, truth, handles and sequence survive. Retrying yields the clean normalized epoch, including IDs, causes, ordinals and work. No valid commit allocation is observed. |
| Lifetime and no-throw barrier | An active token shares its original Impl through facade moves or destruction. Valid commit, explicit rollback, destructor cancellation and move assignment run with allocations forbidden. Closing releases the Impl. Returned journals retain affected pins/metadata, not a whole-state snapshot; later updates and owner destruction preserve pinned values. |
| Existing API compatibility | Single-row `apply` retains native event 1, its no-op fast path and its previous metrics. All 39 existing tests remain alongside two new executables. Current single-update allocation sweeps reach 120/74/36/66 failure positions, two more each for prepared token/transaction construction. Frozen v1 trace and v2 report schemas, physical-plan schema, support codecs and existing CLI tests are unchanged against the R04 manifest. |

The root reviewed transaction ownership, cleanup/publication ordering and
cross-stage event accounting. Luna Max supplied bounded semantic/fault tests
and contract updates; the root integrated and verified them. Two test
expectations were corrected during integration: non-connex Boolean child
nodes have no E relation, and rollback need not shrink reserved arena slots.
These were test defects, not changes to the runtime contract. This internal
review does not close the external G2/V02 review requirement.

## Verification matrix

All five configurations pass. All verification process handles are terminal
and successful. Native warnings remain errors; the sanitizer preset enables
leak detection and halts on ASan/UBSan failures, including parser C code.

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 41/41 pass | 52.66 s |
| GCC 13.3 Release | 41/41 pass | 7.23 s |
| ASan/UBSan including parser C | 41/41 pass | 268.36 s |
| Clang 18.1.3 C/C++ Debug | 41/41 pass | 40.37 s |
| Fresh source-only Release | 41/41 pass | 7.54 s |

The fresh configure/build/test took 210.68 s and removed its temporary source/
build tree. No runtime algorithm changed after these runs.

CLI: 25 checks/34 manual states pass through CTest and under Python `-O`.
Optional schema audit passes 18 schema meta-checks, 26 normalized artifacts,
19 identity artifacts, 59 admission artifacts, two layout/projection artifacts,
31 physical artifacts, three support input/report cases and two rejected
update reports. Support input is one v1 envelope with an `updates` array; the
prepared API adds no batch/physical trace format. Output remains report v2.

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
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/prepared-epochs-clean-source.log
sha256sum -c docs/verification/prepared-epochs-sources.sha256
```

Logs are under ignored `build/verification/prepared-epochs-*.log`.
The [source manifest](prepared-epochs-sources.sha256) covers 450 native source,
build, test, fixture, dependency and ordinary-contract inputs. All fingerprints
pass verification. It excludes verification packets/manifests and mutable
handoff/ledger files, following prior checkpoints.

## Remaining work

R05 still needs physical base-row identity, source constraints, per-occurrence
derivation counts over final adapted native tuples, deterministic compiled
alias fan-out, staged public output and integrated physical/delta acceptance.
Calling public `apply` separately for each alias would publish intermediate
state and consume several sequences. The new pending token is the logical
foundation for a physical coordinator, not that coordinator itself.

There is no full-query result/delta cursor or sink here. Local support
transitions are not full-query deltas; affected-value pins do not freeze
unrelated outside context. R06 initialization, D01 onward enumeration/liveness,
O06 delivery and S04/S05 optimized indexes/byte budgets retain their separate
acceptance criteria. Ordered-container costs, diagnostics, caller-retained
history and explicit snapshot copies remain outside the abstract work bound.
No physical SQL executor, certified update/delay guarantee or R1 release is
claimed.
