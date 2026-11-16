# V63 durable SQL rows: implementation and receiving

V04 remains in progress. This receives a genuine public durable plain-SELECT-bag
path and its current component evidence; it does not accept an R2 release.
The full implementation goal stays active. The
[V62 R1 decision](../../build/r1-release-v62-v1/candidate-v1/release-decision.json)
and accepted archive remain unchanged.

## Implemented path

The [public row session](../sql_rows_session.md) uses genuine SQL-row compiler
metadata and native state. Plain bags emit exact signed uint64 changes;
DISTINCT emits unit support changes; EXISTS emits the old/new Boolean-row pair.
One prepared token, one logged Input and one committed output spool bound the
coordinator. Numeric source/kernel maintenance remains separate from output
presentation. No aggregate surrogate, per-update database snapshot, persistent
result graph, generic transaction engine or new retry/catch framework was added.

Typed row records/descriptors/checkpoints use distinct format magic. Shared
bounded POSIX I/O, CBOR validation and neutral transport data avoid duplicate
implementations; genuine row owners retain their own admission/publication
authority. Checkpoints contain complete physical rows and progress. Recovery
rebinds/rebuilds through actual factories, reproduces committed output, verifies
actual sink bytes and validates the complete selected-root/file barrier before
either torn suffix can be truncated.

The maintained inventory is 856 code files: ten existing paths changed and 24
new paths. The production scope is 389 files, comprising 364 unchanged V62 files,
nine changed files and 16 new files. CMake appends registrations and SDK export/
installation after the exact preceding V62 prefix. Root adopts 20,671 contracts
with exact lineage and independently receives all changed source anchors; the
current generated maps/checker pass for 856 files, 193,228 lines, 21,400 regions
and 150,804 local links. All 18,206 nonblank regions have usage contracts; 3,194
blank regions retain structural descriptions. Proposal counts alone do not
prove semantic coverage.

## Review findings and repairs

The old large-parameter compiler test found an actual memory regression:
unconditional recovery-image retention duplicated a 1 MiB parameter. Retention
is now explicit with `retain_binding_image=true` for durable use. Ordinary
binding preserves its original large-parameter memory bound, source hash and
selected binder-work accounting;
the original <2 MiB assertion passes without threshold changes. Recovery
boundaries reject absent images, including mismatched prepared-output handles.

Normal shared program backing avoids a full SQL/catalog scan during output
encoding. Independent genuine handles take an exact charged comparison fallback.
The duplicate CBOR validator was replaced by the existing validator and neutral
limits alias. Cold descriptor recipes pin the parser archive/PG version; zero
receiving binder work remains a resource/work refusal, with no semantic Reject.

Strict compilation caught ambiguous one-line guards, temporary borrowed getter
calls and test Row-name ambiguity. Direct guards/named owners/explicit nullable
types repair them without warning suppression or relaxed API lifetime rules.
The new fault harness also attempted unsupported after-effect injections on
already-negative optional syscalls. It now follows actual supported observations;
every supported injection still must fail, with the same crash/recovery checks.
Original source cohorts and failed attempts remain retained.

Independent semantic review tightened usage cards that initially assigned
module-wide factory/cost claims to simple helpers/getters. The current codec
proposal has 201 block-specific contracts, independently checked against all
11 files and 1,592 lines. That review found no unresolved current source/card
defect. Unchanged aggregate rebind's broader binding diagnostic under a cold
resource stop remains a separately scoped diagnostic-precision note; it does
not publish invalid state or manufacture a semantic Reject.

## Current execution evidence

| Check | Actual result and scope |
| --- | --- |
| Entry | All 4,826 V62 live/frozen source pairs and inherited binding dictionaries match. The accepted R1 archive and decision hashes match. A copied timestamp field is explicitly qualified; sealed bytes are preserved. |
| Complete builds | Current strict GCC Release and Debug ASan/UBSan both build the full default native target set. Both rehash 858 code/configuration inputs with no drift. |
| Current source contracts | All 20,671 adopted cards and 856 current code files pass source hashes, exact anchors, full nonblank coverage and generated links. |
| Full current regression | Both profiles pass all 383 registered tests with exact names, stable registrations and zero failures/skips/source or build-metadata drift. No native rebuild/configure command runs during these suites. |
| Current affected tests | 22/22 Release and 22/22 ASan/UBSan pass, with no failures/skips/source drift. All seven new registrations and directly affected existing weighted/SQL/aggregate-file/session/generation contracts are included. |
| Support/output | Each profile checks 258 support transactions/484 stages and 84 SQL output transactions/164 decoded changes across both backends. Retractions above INT64_MAX remain exact. |
| Durable row owner | Nullable bags, witness multiplicities, self-joins, DISTINCT/EXISTS, rejection/resource separation, net cancellation, pending/undelivered reopen, checkpoint/next update, progress and bounded history pass. |
| File/process faults | Each profile passes 378 supported syscall failures and 70 real process cuts per backend: 756 failures/140 cuts total. Actual reopen/replay receives survivors. Publication and delivery use no covered C++ allocation after append funding. These are process-cut tests, not a hardware power-loss experiment. |
| Fresh source | A 4,806-file source copy builds all public targets in GNU Release with BUILD_TESTING=OFF. Actual closure receives 171 C++ units, 405 project/nine generated/425 system dependencies, nine parser headers/96 C objects and 37 native target hashes; unexpected workspace inputs are zero. All 265 SDK payloads join exact source/native/generated origins and retained archive members. The existing R1-default package fixture separately passes 13 set-query SQLite prefixes. |
| Relocated SDK | The provisional SDK-v2 and fresh extracted SDK each pass the strict outside C++23 consumer using only public SDK headers and 16 SDK archives. Each 265-file SDK retains its exact pre/post hashes; compiler dependencies contain no original source headers/build libraries. |
| Independent SQL | Each of those two SDK images independently passes the same seven positive queries, 82 fresh-process prefixes and 25 committed/delivered epochs against independent SQLite Counters, raw row-wire decoding, progress/source-weight checks and actual sink-byte equality. |
| Negative admission | The separate hidden-join-key/head-spanning query is completely unsupported, with no selected tree/height/lower/upper. Public default finite grants and the checked structural witness are recorded. It is not counted as positive SQL coverage or a resource stop. |

Native build/test records are in
[the root packet](../../build/verification/v63-sql-rows-session-v1/README.md).
The provisional SDK trial is
[separately received](../../build/verification/v63-rows-sdk-oracle-run-v4/README.md).
The [fresh source closure](../../build/verification/v63-fresh-source-audit-v1/README.md)
and [fresh SDK SQL trial](../../build/verification/v63-fresh-source-rows-sdk-v1/README.md)
retain their own exact source/build/SDK vintage. Current guides are a documentary
successor; maintained code/configuration bytes are unchanged.
The [full current regression](../../build/verification/v63-full-current-tests-v1/README.md)
passes 383/383 in each profile. Both jobs are terminal. Their full JUnit names,
registrations, 858 code/configuration pins and build metadata are independently
received; all remain unchanged through execution. Incidental elapsed values
are validation data, with no controlled performance qualification.

The [additional fresh-SDK aggregate fixture](../../build/verification/v63-fresh-sdk-aggregate-v1/README.md)
exercises public in-memory COUNT/SUM against SQLite, using four SDK archives and
378 compiler dependencies. All 265 SDK files remain unchanged. This fixture has
its own scope; nullable/AVG and durable SQL-aggregate behavior are covered by the
separate current native tests.

## Remaining V04 work

Current source contracts/maps, compatibility/migration guidance, full regression
and independent source/build identity are received. Complete scoped
extended-report receiving and the
versioned R2 artifact/checklist. Only their exact joined evidence can accept
V04. Existing measured report cohorts keep their original source/cost vintages;
no new weighted/durable speedup is inferred from historical timing.

R1 default height and semantics remain explicit. Requested exact extensions
keep separate gates; comparisons, top-k and difference may use ordinary change
propagation or exact recomputation. Approximation and parallel/distributed
execution stay deferred. Queries retain independent serial owners. Licensing
disposition remains user-deferred, with existing rights/notices preserved.
