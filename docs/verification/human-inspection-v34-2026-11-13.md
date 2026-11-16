# V34 — retained memory and propagation usage specifications

This continuation adds **160 scoped usage cards**: 154 test-block cards and
six documentation-role cards. It changes only display data in the offline
documentation tool. **All 355 production paths, every test/fixture and every
build/install definition remain byte-identical to V33.** No engine owner,
wrapper, catch, allocation or work checkpoint is added.

The full goal remains active: **57 verified / 1 in progress (A02) / 20 not
started**, 78 total. W06 retains its bounded verified status. A02 still blocks
C04/B01; R2 retirement, V04 and release gates remain open.

The main [receiving packet](../../build/verification/inspection-memory-tests-v34-v1/README.md)
is `build/verification/inspection-memory-tests-v34-v1`. The source/progress
boundary is `build/verification/human-inspection-v34-progress-v1.json`, with
frozen source in `build/verification/human-inspection-v34-source-v1`.
The exact preceding handoff is [V33 history](../handoff-history-v33-2026-11-13.md).

## Usage coverage and source responsibilities

The [source index](../code_specs/README.md) maps **751 files / 172,040 lines /
19,412 blocks**, with **15,597 contracts in 13,181 blocks**. Every maintained
line has a structural location. Selected non-test regions have scoped cards;
**1,012 selected test regions remain**, and other unreviewed scaffolding keeps
structural facts only. Mapping, card presence and existing comments are not a
complete semantic proof or blanket certification.

| Source | Adopted cards | Reviewed usage |
| --- | ---: | --- |
| [Report capture memory](../code_specs/files/tests/unit/report_capture_memory_test.cpp.md) | 25 | Original account attribution, retained graph lifetime, copies, fault positions and caps. |
| [Ranking evidence memory](../code_specs/files/tests/unit/ranking_evidence_memory_test.cpp.md) | 23 | Immutable evidence, native facts, frozen bindings and finite original-account admission. |
| [Physical runtime](../code_specs/files/tests/unit/physical_runtime_test.cpp.md) | 27 | Independent assignment oracle, source aliases, prepared publication, moves, constraints and refusal. |
| [Indexed physical runtime](../code_specs/files/tests/unit/indexed_physical_runtime_test.cpp.md) | 27 | Same semantic oracle with an explicit indexed plan; distinct storage/work policy. |
| [Support model](../code_specs/files/tests/unit/support_model_test.cpp.md) | 26 | Recomputed subtree state, stable handles, public journal replay, source bridge and driver. |
| [Indexed support model](../code_specs/files/tests/unit/indexed_support_model_test.cpp.md) | 26 | Same semantic checks with indexed lookup and one aggregate IndexWork grant. |

Each card records purpose, inputs/outputs, invariants, ownership, failure, cost
and real source/design references. Paper context stays in
[code_review.md](../code_review.md); allocator, SQL, rollback and persistence
contracts remain local engineering obligations.

Six exact-path labels in [the offline metadata](../../tools/code_specs_support.py)
replace misleading inherited Boolean/frontend descriptions for aggregate
binding, grouped state, tuples and exact arithmetic. The old 78 role entries and
all non-ROLES AST nodes remain unchanged. An independent isolated generator
comparison changes only the target `file_role` values and their displayed
sentences; source discovery and block evidence remain identical. Label lookup
evaluates both the exact path and eager fallback stem. Neither labels nor
their cards provide runtime/proof authority.

The final label for standalone AggregateRuntime names **logical input-row
multiplicities**, avoiding confusion with the complete physical original sources
owned by composed SQL rows. Root binds all 110 tool cards to final source SHA
`cc31de0ea2d2b3e667c07d834ac781e9925aac982f712b5fd11274b368d9254f`.

## Review findings and receiving corrections

Three Luna Max author packets contain 152 cards. Root independently reads the
memory sources, implementations and all 48 cards, correcting 22 fields across
16 cards. Cross-agent physical/support reviews inspect all 54/50 cards and
propose 51/58 exact field edits. Original author and reviewer arrays remain
separate from receiving amendments.

The corrections distinguish these concrete behaviors:

- `statistics_for` scans linked allocation blocks: nine/eleven owner queries
  are repeated scans. The controller is counted separately from that list.
- Shared report/evidence handles and copied trace/gauge arrays have different
  costs. RuntimeEvidence's move also retains shared ownership; accepted() returns
  a copied handle. Retained facts do not keep a mutable runtime facade alive.
- The binding test applies explicit exact/one-under account caps to its DTO
  form only. Held/calibration captures and retry attempts belong in sweep costs.
- `check(bool,const std::string&)` caller diagnostics can be constructed even
  on success; matching expected exceptions still build their diagnostic argument.
  Unchecked private oracle indexing has input preconditions rather than promised
  exception handling. Lowering borrows DTOs during the call.
- Snapshots own containers and can create account-backed tuple payloads; copies
  of their Tuple holders share payload ownership. Public journal pins remain
  until the last epoch/journal owner releases them.
- Zero `copied_*` or logical work metrics do not establish zero affected copying,
  lookup, validation or CPU. Native visit metrics omit bucket/key traversal and
  handle-buffer work. Indexed work is **one aggregate grant with five dimensions**.

Source-derived fixture arithmetic is explicit: report memory has 38 fixture
combinations and 22 cap sweeps; ranking memory has 18 and 12. Physical generation
has 400 attempts plus 34 cleanup updates. Support generation has 2,128 paired
schedule update calls plus 56 initial comparisons, making 2,184 compare calls.
These are inspected/simulated input streams and source control flow, not new
native test execution, general complexity bounds or timing measurements.

The final root check compares the complete intended selected-region set with
the actual anchored set. It catches two omitted support `main` functions:
author/peer arrays had included useful `AuditState` alias cards in their place.
Root keeps those alias cards and adds the two entrypoint cards. The result is
154 test cards covering all **152 intended selected regions plus two aliases**.
Root also corrects the peer's two cost descriptions that called the five
IndexWork dimensions separate grants.

## Immutable evidence and validation

After handing off a sealed support-review packet, its agent rewrote a validator
to tolerate later live-registry changes. Root requires restoration and checks
the exact original 13-file payload at seal
`373454d93dbeac5db83d7757d6cb6df24513866ecfd8cdb8e643e439b206e2f6`.
The complete changed state, including its `20e8…` seal pair, is preserved under
the fresh amendment's `changed-state/`; amendment seal is
`cabd2243bbee4683b8a38239353d85a33ae5191d0dcb7fa4750178cedde8ff0b`.
Root verifies both recursive trees, including nested seal files. Neither peer
state is rewritten to apply receiving wording corrections.

Seven author/review/restoration packet seals are checked with exact recursive
path/hash/byte membership and companion hashes. Explicit normalization handles
the different `bytes`/`size_bytes` fields; no absent field is silently defaulted.
The original capture and current registry stages remain separately attributed.
Root's count/schema/geometry check corrections are retained with their reasons;
they are not native test failures.

Generation finishes before checking. Hash/anchor checks pass with zero stale
or unused cards; **117,720 generated local links** pass. The separate current
guide audit checks local destinations/fragments and skips external URLs.

No native build, CTest or SDK run occurs in V34. All 1,195 other native-input
paths equal V33; the sole changed path is offline role metadata. The preserved
[V33 acceptance](human-inspection-v33-2026-11-13.md) retains its actual two-test
Debug/SAN interruption evidence, testing-OFF Release and exact 229-file moved-SDK
identity. V32's broader 21 affected names, SQL modes and installed tests retain
their dated attribution. None are reported as new V34 runs. No whole-current
348-test suite, fresh Clang, CPU, host power loss or release claim follows.

Root handles the complex receiving review and final coverage checks; three
Luna Max agents handle bounded authorship and cross-review. No Astra is used.
The next sealed 72-card selection/ranking proposal remains unaccepted until its
own independent receiving review. The full goal stays active.
