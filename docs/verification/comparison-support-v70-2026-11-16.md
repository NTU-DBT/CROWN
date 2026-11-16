# V70 comparison-aware query support acceptance

X04 is verified for the explicit non-null public-IR comparison route in
[the guide](../comparisons.md). The owner uses ordinary propagation and exact
after-state recomputation, with owning current results and exact endpoint set
deltas. Comparison predicates remain separate from equality-CQ admission/proofs.
The existing SQL route still rejects cross-relation residuals. This accepts the
literal X04 scope and costs, not a specialized P9 algorithm, new SQL family,
complete comparison theorem or release image.

## Source and correctness argument

Current inventory is 885 code/configuration paths: 487 primary, 398 test/helper,
404 production. All 400 earlier production files retain exact V69 bytes. Four new
production files implement immutable typed predicate admission and one atomic
comparison owner; three new tests exercise it. Old CMake has an exact V69 prefix
plus an optional target/export/install/test block. Stripping the one comparison
context, four roles and two exact routing branches from the offline helper yields
the exact old AST. The [entry verification](../../build/verification/v70-comparisons-entry-v1/README.md)
received all 4,936 original live/provider pairs and 878 code/configuration paths.

The [independent bounded review](../../build/verification/v70-comparison-independent-review-v1/README.md)
reads all four production files, 529 lines, and the supporting full-witness,
variable-order, alias-drain, zero-crossing, commit and allocator boundaries. The
reviewer authored admission/tests but did not author the runtime; this distinction
is explicit. Root separately reviews native ownership, budgets, endpoint merging
and publication. No production correctness defect was found in the current scope.

Predicates are a conjunction of six same-type relations over bound variables or
constants. Every complete assignment retains hidden operands until predicates
finish; only then are the original ordered/repeated head and DISTINCT applied.
The full witness cursor selects all survivor factors and sorted variable IDs.
If no native zero/positive crossing occurs after all aliases drain, the logical
occurrence relations and every assignment remain unchanged, so skipping answer
recomputation is sound for these exact-set predicates.

All fallible after-state enumeration, deduplication, funded output and endpoint
set difference work completes before the existing source token commits. A
same-account vector swap publishes the prepared answer without allocation. One
writing guard outlives source publication and temporary/old-state retirement.
Source/account/sequence failure therefore preserves both original sources and
comparison answers, using the existing source rollback rather than another
journal. Metadata constants, retained answers, private rows and output payloads
all retain the original account.

## Actual native evidence

Final V5 strict Release and ASan/UBSan builds pass, with 885 source/configuration
hashes unchanged. Final V3 CTest executes both newly registered commands in each
profile. Each profile passes 63,308 unit checks, 470 authenticated persistent
allocation-denial prefixes (139/93 reference insertion/deletion; 140/98 indexed),
and 86 native oracle cases with 1,528 source events on two backends. Actual JUnit
stdout, commands and source hashes are in the
[Release receipt](../../build/verification/v70-comparisons-root-v1/release-checks-v3/receiving.json)
and [sanitizer receipt](../../build/verification/v70-comparisons-root-v1/sanitizer-checks-v3/receiving.json).

The unit compares full original A04 assignments and predicate-aware projection,
including all six relations, hidden last witnesses, Boolean/repeated heads,
self-join fanout, constants/contradictions, integer/date/decimal/string/Boolean
boundaries, full source constraints, independent owners and returned ownership.
Every calibrated allocation cut now requires its trigger flag and refusal;
unchanged state and retry on the same owner/sequence are checked. A separate
cumulative producer 128 case exhausts while scanning the prepared after-state,
verifies rollback, then accepts a valid alternative event at the same sequence.
This is distinguished from retrying the same over-budget event under an unchanged
producer cap. Allocator callback retirement coverage is a static guard argument,
not a separately injected callback test.

The Python oracle first joins complete original sources and filters comparisons
before projection; exact Fraction and UTF8 byte ordering supply scalar truth.
Independent SQLite applies explicit predicates/constraints. Decimal SQL ordering
uses 77-digit biased fixed-width scaled-integer TEXT, never floating point.
Its model-only packet checks 43 base cases / 764 events / 807 initial-prefix states,
including four source denials. Native capture subsequently executes the actual
registered oracle command with its capture-only artifact option and retains full
requests, native wire and summaries: [Release raw capture](../../build/verification/v70-comparisons-root-v1/release-oracle-capture-v1/receiving.json),
[sanitizer raw capture](../../build/verification/v70-comparisons-root-v1/sanitizer-oracle-capture-v1/receiving.json).
The driver binary hashes are identical before/after those executions. The current
unit output is extracted from actual V3 JUnit; capture does not rerun the unit.

CTest now lists 391 registrations. All 389 prior command/property definitions remain
exact, excluding CTest scheduling COST and CMake backtrace provenance. V68's full
387-test profiles and V69's added star checks keep their own source vintages.
V70 runs only the two added registrations per profile and separately captures the
oracle; no new complete 391-test run is claimed.

## Installed SDK and preserved failures

The [actual SDK verification](../../build/verification/v70-comparisons-sdk-v1/README.md)
physically relocates a 279-file installation and links a standalone public-header
consumer only through CROWN::comparisons. Actual dependencies and archives resolve
under the relocated prefix and archives match producer bytes. The consumer passes
12,472 checks across 42 scenarios and 876 full-source checkpoints; a separate Python
join rechecks all 876 answers. It includes a held-out three-relation chain with
hidden long comparisons, six operators, repeated/Boolean heads, three-alias
self-joins, 52 source FK/no-advance denials, 2 row denials and 6 finite work/snapshot
denials on both source backends. Snapshot/Epoch/Binding ownership and independent
owners survive the tested lifetimes. The SDK guide retains its pinned pre-final
documentation vintage; native payloads/public headers match reviewed source.

The closed SDK README still names its initial `logs/consumer.log`; the actual
passing [consumer log](../../build/verification/v70-comparisons-sdk-v1/logs/consumer-v2.log)
is retained as `logs/consumer-v2.log`. This successor supplies the exact pointer
without changing the closed SDK packet.

Initial failures remain. V1 strict builds rejected a reference obtained through a
temporary RowView; a cheap ScalarView copy removes the compiler warning while
retaining native borrowed-string ownership. V2 builds caught the root unit's
TreeNode children initializer. Initial CTests caught unquoted uppercase fixture
table names and a driver choosing a nonempty tree for contradiction; fixture
corrections preserve the original guards. Their preimages/diffs and passing
successors are retained. The first installed consumer had the same children-field
fixture error, preserved before a fresh consumer build against the same moved SDK.
An early documentation checker started before generation ended; its failure stays
separate from the authoritative completed final check. None is relabeled as a
production runtime defect or erased by later success.

## Inspection, costs and continuation

Current source maps cover 883 files / 199,030 lines / 22,111 regions. All 18,819
nonblank regions have scoped seven-field usage contracts; 3,292 blank regions
retain structural descriptions. There are 21,323 cards: 157 new, 1,823 old bindings
with nine semantic context/routing amendments, and 19,343 exact unrelated old
records. Actual generation/checking passes 155,408 local links with zero errors.
Independent [mechanical receiving](../../build/verification/v70-comparison-spec-receiving-v1/README.md)
binds canonical adoption, source spans and saved maps separately from native
correctness. These offline maps add no runtime overhead or proof authority.

The [primary reference observation](../../build/verification/v70-comparisons-root-v1/p9-primary-source.json)
records the 14-page SIGMOD 2022 author PDF and DOI. Full assignments can greatly
outnumber final answers; source/equality work, after-view startup, cumulative
enumeration, predicate/scalar/byte work, ordered deduplication, materialization,
endpoint merging and cleanup retain their real costs. No specialized P9/static
bound is promoted to an unproved dynamic or constant-delay guarantee.

X04 is verified, leaving X06 and X08 open. Approximation, shared-query optimization
and parallel/distributed execution remain deferred; query owners stay independent
and serial. All earlier closed source/SDK/release decisions remain immutable and
retain their original vintages. No new release is accepted. The implementation
goal stays ACTIVE; [the handoff](../handoff.md) records the exact successor.
