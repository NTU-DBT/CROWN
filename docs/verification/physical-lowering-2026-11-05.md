# P08 physical lowering verification, 2026-11-05

Historical P08 checkpoint. The subsequent logical support kernel and current
source fingerprints are in [support verification](support-2026-11-05.md).

Input revision: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. P08 is verified at the compiled
physical-plan/reference-storage boundary. The full 78-card Refactor.md goal
and release gates remain open. Maintained query execution starts with R01;
the test-only static interpreter is not that runtime.

Use the [physical contract](../physical_plans.md),
[decision 0010](../decisions/0010-physical-lowering.md), and
[source fingerprints](physical-lowering-sources.sha256) for this checkpoint.
All 415 source/build/contract/fixture fingerprints pass verification.
Prior [storage evidence](storage-2026-11-05.md) describes the historical S01/S02
snapshot; its fingerprints intentionally precede P08.

## Acceptance audit

| Required artifact or behavior | Evidence |
| --- | --- |
| Verified physical construction | `PhysicalPlan` owns immutable shared data; its data constructor is private. Factories independently validate the actual catalog/query/tree. A caller-modified `ValidationReport.valid` has no authority. Only this plan type can initialize `ReferencePlanStorage`; serialized flags/slots are rebuilt before use. |
| Generic layouts and projections | `crown_plan` compiles atom constants, repeated-column equalities, ignored columns and ordered logical scope projections. Physical-base, native-record, survivor, candidate, parent-support and visible relations have explicit roles/IDs. Compatible layouts can share tokens while relation identity remains separate. No query classes are registered. |
| Child indexes and event routing | Edges retain parent/child IDs, child slot and compiled separator projection. Native reverse indexes share identical fields/semantics without merging child ports. Both endpoints use the same target token. Generalized Guard makes child support keys equal the whole parent scope, avoiding a Cartesian candidate relation. |
| Enumeration and head assembly | Parent-before-child N-ary steps contain exactly maximal C*. A visible variable outside C* does not create an E relation. Parent probes and child visible buckets share separator targets. Numeric output slots preserve ordered/repeated heads and check shared-variable equality. Parent-support and E descriptors remain distinct; runtime support counters are future R03 work. |
| Structural families | Luna Max authored 14 manually expected valid families and five invalid Cover/Connect/Guard/Above/Connex cases. Valid cases include native/projected roots, Boolean/nullary atoms, disconnected products, same-table self-join, three/eight children, nested generalized nodes, visible hidden branches, mixed-type/reordered composite keys and a 65-field scope. A 128-node chain checks native height, edge depth and program depth separately. |
| Independent execution evidence | A test-only static interpreter executes the emitted input/projection/index/enumeration programs on three databases per valid family: 42 snapshots. Expected local survivors come from independent full subtree assignment joins; final answers also match A04. Every visible result is emitted once, including hidden-witness collisions. These are full rebuilds, not incremental maintenance. |
| Typed inputs and owning SQL adapters | API tests cover int64/string/bool/date/fixed-decimal constants, repeated variables and ignored values. SQL lowering replays the complete program, owns source/expression/adapter buffers, preserves physical base-to-alias routes and filters each alias independently. Caller mutation and plan copy/move preserve ownership. |
| Legacy grounding | The frozen v1 fixed-head program grounds to v2 before tree checking. A stale v1 tree rejects; a handwritten grounded native tree succeeds and applies constant guards to original physical rows. The artifact retains the grounded program and SQL output/wrapper mapping. |
| Exact bindings and strict artifacts | Two v1 schemas define physical plans/options. Native readers replay source/query/tree and compare every generated field, including layouts, indexes, routes, work and guarantees. Corrupt/future/duplicate fields, false verification, bad slots/hashes and runtime-bound claims reject. Python hashlib independently checks the physical domain envelope and exact source digest. Database contents do not change compilation artifacts. |
| Resource stops and profiles | Lowering/identity exact-budget and n−1 boundaries pass. Host caps bound stored unlimited producers without rewriting their recorded options. Failure returns no partial program/digest. Profiles retain checked upper-bound height for tree routes; constants describe a zero-height operator and do not certify their retained bodies. Execution is `lowered_not_started`, and runtime bounds remain unimplemented. |

The conditional preservation argument is appended to
[planner_proofs.md](../planner_proofs.md). For noncontradictory tree routes it
assumes later exact S/E maintenance and proves the meaning/uniqueness of the
compiled visible-assignment join. Luna Max's internal read-only review found
the argument consistent under those assumptions and identified wording fixes
for constants, future counters and public copy/move constructors; those fixes
are incorporated. This is not external G2/V02 signoff or a delay/update proof.

## Final verification

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 29/29 pass | 17.45 s |
| GCC 13.3 Release | 29/29 pass | 4.03 s |
| ASan/UBSan including parser C | 29/29 pass | 125.24 s |
| Clang 18.1.3 C/C++ Debug | 29/29 pass | 14.36 s |
| Fresh source-only Release | 29/29 pass | 4.03 s |

The final fresh configure/build/test took 178.26 s and removed its temporary
source/build tree. Sanitizers enable leak detection and halt on errors in
project C++ and parser C. All prior frontend, exact scalar, storage
failure-atomicity, independent structural and height-certificate tests pass.

The CLI suite passes 125 checks over the manual cases and all 17 successful
normalization corpus programs. It also passes under Python `-O`, with explicit
checks retained. Optional JSON Schema validation passes 16 schema meta-checks,
26 normalized, 19 identity, 59 admission, two layout/projection and 31 physical
artifacts (14 direct and 17 normalized), plus their physical options.
`jsonschema` remains optional; ordinary builds/CTest use standard Python only.

```sh
cmake --build --preset debug --parallel 2
ctest --preset debug
cmake --build --preset release --parallel 2
ctest --preset release
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 -O tests/integration/physical.py build/debug/crown .
python3 tools/verify_schemas.py build/debug/crown
python3 tools/verify_clean_build.py --log build/verification/physical-clean-source.log
sha256sum -c docs/verification/physical-lowering-sources.sha256
```

Final outputs are under ignored `build/verification/physical-*.log`. The clean
snapshot excludes caches, VCS/build and legacy directories. The source
manifest includes code, contracts, fixtures, schemas, tools, build inputs and
pinned dependencies; verification packets/manifests and mutable handoff/ledger
files are excluded as at previous checkpoints.

## Remaining work

P08 lowers a supplied tree. It does not select a strict minimum-height/cost
policy or upgrade a checked upper bound to an optimum. Canonical hashes do not
replace independent certificate replay. Constant routes retain source atoms
and use explicit empty operators rather than accepting an invalid tree.

`ReferencePlanStorage` instantiates empty standard-container relations/indexes.
R01 native support, R02 generalized intersections and R03 exact parent/visible
counts are next. S03 arena ownership/pinning precedes R04 journaling; R05 must
connect physical full-row/alias derivations to one logical epoch. Cursors,
recovery, sinks, benchmarks and later stages retain all original criteria.
A02 license disposition, P04/P06 partial features and G2/V02 remain open;
no runtime complexity or release gate is closed.
