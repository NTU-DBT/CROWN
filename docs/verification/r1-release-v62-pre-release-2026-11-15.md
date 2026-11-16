# V62 R1 candidate receiving

V03 is in progress. The full implementation goal remains active; this record
does not yet accept an R1 or R2 release. The
[method and gate checklist](../releases/r1.md) define the candidate scope.
The exact [V61 review](full-scope-review-v61-2026-11-15.md) remains the parent
authority, with its source/evidence hashes and separate validation vintages.

The current map covers 832 code files, 189,103 lines and 20,886 regions.
All 17,734 nonblank regions have exact usage contracts; 3,152 blank regions
retain structural descriptions. The registry has 20,199 adopted contracts.
All 373 production include/src/apps files retain their reviewed V61 bytes.
V62 changes only offline packaging/build/test code and human documentation.

## Source and artifact changes

The [candidate assembler](../../tools/package_release.py) installs the selected
build and copies explicit source, SDK, report, figure and evidence inputs. It
emits a regular-file normalized archive, a complete payload manifest and standard
checksums. It never converts copied files into a release decision. Source/build
identity still requires independent compiler/dependency and fresh-source checks.
Payload grants exclude installer staging, metadata, compressed output and host
resources, as the guide and source-bound cards specify.

Independent source review repaired output aliases containing parent components,
an imprecise native-version substring check and absent CMake-home provenance.
The tool resolves paths, compares the exact installed version/API and rejects a
missing source association. No retry or query-runtime framework was introduced.

The clean-source copier now includes root README/.gitignore and complete filtered
documentation. This makes the packaging regression usable from a real source
copy; root-only leaf copying precedes the one docs tree copy. Its fixture and
real-copy guards retain distinct scopes. CMake appends the new regression at EOF;
the preceding 1,790 lines retain their exact bytes and prior tests/properties.

Strict GCC Release exposed three test-source build issues: an ignored injected
pwrite result and two SQL drivers' temporary optional/variant constructions.
The hook now checks write/close results, retaining noexcept and active assertions.
Both drivers directly emplace the same NULL/scalar alternatives before creating
borrowed views. No warning was suppressed and no production code changed.
Original failed builds and all source preimages remain retained.

## Receiving completed so far

| Obligation | Actual evidence and scope |
| --- | --- |
| Entry integrity | 4,817 live/frozen source pairs and 202,815 immutable evidence paths pass, with zero byte mismatches. Private prefixes retain exact 926/4,701 is_file membership; an old dangling changelog symlink is separately classified. |
| Source/usage review | Root and independent workhorse reads cover the new assembler/test, source copier, CMake addition and three repaired test bodies. 1,632 prior cards are received with scoped amendments; 41 new cards are adopted. |
| Complete native builds | Current strict Release and Debug ASan/UBSan both build all targets after the repairs. Earlier failed Release attempts remain failures. |
| Complete current suites | Release and Debug ASan/UBSan each pass all 376 registered tests, with zero failures/skips. Root checks each JUnit name against the full registration list. Both coordinators rehash 4,703 source/data/document inputs after execution and report no drift. |
| Extracted SDK regression | Both profiles pass actual normalized archive/manifest/checksum/source checks and negative controls. Outside strict consumers use the extracted SDK and match 13 independent SQLite prefixes through fresh-process recovery, without original producer includes or private libraries. These use small genuine packaging fixtures, not a full benchmark qualification. |
| Fresh source build | A private Release/OFF source build passes all targets; 163 actual C++ objects, 389 project dependencies, nine archive-matched parser headers and 425 system dependencies are joined. Its extracted SDK also passes the strict outside-consumer regression. |
| Final SDK semantics | The fresh extracted SDK passes 34 independently checked signed/current prefixes across two properly projected SQL forms with renamed/reordered aliases, height two, restart/rotation/retirement and proof/memory denial. All 258 SDK file hashes remain unchanged. Literal four/eight-child generalized stars additionally pass 40 SQLite signed/current prefixes at height one. |
| Named cases | A source-bound applicability matrix maps all 44 Q01–Q20/U01–U24 cases to existing registered tests and source fixtures. A mapping is not a current execution pass; R2 cases retain their separate applicability. |

The [full report](../../build/verification/v61-full-experimental-report-v1/report/report.md)
and all historical measured source/build identities remain unchanged. No new
controlled timing is required for unchanged production code. Report methods,
adverse observations, output/memory scopes and source vintages stay explicit.

## Remaining release gates

Receive the full final source/SDK/report candidate and join its exact archive,
source/compiler dependencies and tested SDK byte image to the completed
G0–G9/G11 source, case and execution records. All 376 current registrations pass
both profiles, and the fresh-source/SDK semantic checks above are complete.
Record source/compiler/dependency/target identities and preserve every failed
attempt. A complete build or archive regression alone does not prove these
remaining requirements. Licensing disposition remains deferred by the user;
rights/notices stay preserved. V04 and the requested exact extensions remain
separate later work.
