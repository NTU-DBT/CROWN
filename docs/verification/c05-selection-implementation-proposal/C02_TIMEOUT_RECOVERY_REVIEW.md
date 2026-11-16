# C02 sanitizer watchdog: read-only audit and conditional recovery

This is a source/retained-metadata review, not a test result or authorization to
alter an active run. At assignment root reported native sanitizer test 139 still
running near its 3600-second CTest ceiling, with no failure yet. The author did
not poll, interrupt, restart, compile, configure or execute any helper, checker
or binary. All existing inputs, F1 evidence and helpers remain unchanged.

The plan below applies only if the terminal raw result actually reports that
external watchdog timeout. A sanitizer diagnostic, assertion failure or other
failure requires its own investigation. If the existing run completes normally,
no timeout correction or revision bridge is needed.

## Actual compiler and test settings

The native test's generated compile command contains `-g -std=c++23 -UNDEBUG`,
all six warning/error flags, `-fsanitize=address,undefined` and
`-fno-omit-frame-pointer`, with no `-O` option. Its ranking and runtime libraries
also have `-g` and no optimization option. This is the GNU compiler's default
unoptimized build. The exact native command was read from
`build/sanitize/compile_commands.json`; generated flags.make files agree.

The accepted excluded preparation command contains `-O2 -g -UNDEBUG` followed
later by `-O1 -fsanitize=address,undefined -fno-omit-frame-pointer`, so its
effective optimization is O1. The retained ranking and physical-runtime object
commands use the same effective O1 setting. Thus the accepted preparation's
1416-second time, as reported by root, is not a native O0 runtime bound.
The difference is a plausible cost factor, not proof of the active process's
remaining time or eventual result.

The native and excluded normalized fault test have identical source hash
`1714ba11a6caa9b795afafe2ce5639eedc340e596a318ce67a1d9a3ceec0429c`.
Their support header is also identical at
`467961d8731b38de08ef5ba2eb85063af199749795ac8304ad323035e6e99a80`.
The native CTest metadata assigns 3600 seconds and retains leak checking,
immediate ASan failure and UBSan stack traces.

The test measures each successful policy call's actual allocation count, then
visits every position with persistent allocation failure. Every position also
checks complete owner canonical state, workload descriptors/cells/metadata,
snapshot/proof/key validity and the complete prior result image/usage. The
normalized memory policy replays/lower-builds every retained candidate; a later
capture sweep checks every reached capture allocation. This has substantially
more work than one successful ranking, including expensive repeated checks
outside the injected interval. The existing 100,000 per-call guard is not an
instruction to skip positions.

Root reported completed native test-139 times of Debug 724.35 seconds, Release
94.46, Clang 592.09 and clean Release 96.78. These are context supplied by root,
not new executions by this reviewer. The accepted excluded sanitizer packet
reported 38,763 positions. A new native run must complete its own measured
position set and normal teardown; this note does not assert an unobserved O0
position count merely because the source matches O1.

## Static input identities

| Input | SHA-256 |
| --- | --- |
| `build/verification/ranking-execution-freeze.json` (F1) | `1f97f84d7d2a09fb992668fcfa071d0065241b0a5de5395244a966216657d036` |
| `CMakeLists.txt` | `d3ff1a2723af0e8a7d7a6c23b6c9a82d2bba39caa26b70fd509bcf48f6e9d3b8` |
| `build/sanitize/compile_commands.json` | `204521b03e58293dcb62aa7ed0afa87439e7af222c6e18c09c8ff34f6c6b4819` |
| Native normalized-test `flags.make` | `f3b4f3b91728897030c4c1dae0eab57df1cf6a68a3a7aa752503890ec19ebf99` |
| Native ranking/runtime `flags.make` (each) | `b1625d9f8be6b51d8735da404473a2a3c0729fb37d2a663b22ffcc1a74e2eb66` |
| `build/sanitize/CTestTestfile.cmake` | `c31f9d1b26de31d2f27a1649f4003b9dfabc8c6c33a1039a4aabeb2491e63851` |
| Native `crown_ranking_normalized_exceptions_test` binary | `c1ac9512a78fff09691c18fc03eaf81d738c9b8736c4cc5d2019a6eee51d348c` |
| Excluded normalized SAN consumer `.o.command` | `204d9297dfdf928047d339c92f62d0c662694633c78905eb6ae1a4fe9fe69d9e` |
| Excluded SAN ranking `.o.command` | `359babf63944a17b390c60e4bca2eed895627b19784c6d419b06ca2dcc801b3b` |
| Excluded SAN physical runtime `.o.command` | `405a0d2c8166264bc56c49dee143798515e5916fe1a3ca8460d262185b22f733` |
| `build/verification/c02-preparation-execution-completion.json` | `4c39ded5d7d09d2802181e476f236c403f8f7533d8606e6fe3f3a53fa58e2d60` |
| `/tmp/crown-ranking-matrix.py` | `e8a068ceaf27922a433b0e73c16929eea95ff956cd228f080c0d8bf016176fa7` |
| `docs/verification/p05-watchdog-bridge-2026-11-07.md` | `f66caa0836efbd9696c027b7a86a7017ab58d1c44f8f951d9f3d3c7f11c6ff2c` |

The excluded command files are under
`/tmp/crown-c02-baseline-normalized-fault-sanitize-1/` and
`/tmp/crown-c02-baseline-coherent-sanitize-1/objects/{ranking,runtime}/`,
respectively. F1's native inventory has 648 files and fingerprint
`726b6ac99057cab64b3b2ee37e437641554bc9165bd832c0cb86ff16d27e705a`;
its project execution inventory has 705 and fingerprint
`87455c8e07579b7d3689e90c4a5989a63ec438ea21bedc72b63bb959a4c9a2e5`.
Root helpers are separately pinned in F1's `root_execution_helpers`; they are
not members of that 705-file project inventory.

## Conditional recovery sequence

1. Let the current run reach its actual terminal result. If it times out,
   preserve the raw failed summary, combined CTest output, full
   `build/sanitize/Testing` tree, command/environment records, input guards,
   binary/object/archive/dependency hashes and all four successful F1 legs.
   Do this before any reconfiguration or rerun can overwrite Testing output.
   The current runner breaks on nonzero CTest return **before** copying
   LastTest.log and extracting test_count, so that preservation cannot be
   inferred from its normal-success branch. A timed-out process did not
   complete the final sweep/normal leak-checking teardown and remains failed.
2. Wait for every C05 guard containing CMakeLists.txt to close and retain its
   terminal before/after result. Do not alter native CMake while those guards
   are active. Do not rewrite any historical manifest, F1 freeze, helper,
   summary, approval or diagnostic as a successful current record.
3. Prepare a new, explicitly reviewed F2 whose only native/project-execution
   source change is an additional sanitizer-conditional setting for
   `ranking_normalized_exceptions`. A concrete candidate is TIMEOUT 7200,
   leaving the 3600-second default in other configurations. This doubles the
   external allowance; it is not a measured upper bound or an advance waiver.
   Keep compiler optimization, every assertion/position, internal work/time
   cap, labels, argv and ASan/UBSan/leak settings unchanged. A further timeout
   would require another evidence review, not silent repeated escalation.
4. Save the exact F1/F2 CMake snapshots and minimal diff. Reconfigure using
   root-owned commands only after the holds close. Verify the complete 143
   names/order/argv/environment and all unchanged effective settings.
   Non-sanitizer generated policy must remain identical; sanitizer metadata
   must differ only in the one TIMEOUT value. Compare compile/link commands,
   compiler/dependency/variant pins and all reused object/archive/binary hashes.
   A test-property-only change should require no C++/parser recompile, but that
   conclusion must be established by actual metadata/artifact equality. Any
   unexpected changed build input requires rebuilding/revalidating its closure.
5. Retain and reuse the four complete F1 non-sanitizer runs only through an
   explicit conditional-policy bridge. Existing build directories allow exact
   generated-policy comparison. If the clean build's generated metadata was
   removed, record that limit: use the preserved clean helper/configuration
   showing sanitizers OFF plus the unchanged default and inactive conditional;
   do not claim a nonexistent byte comparison. A fresh clean configuration may
   strengthen this evidence. If the bridge cannot establish unchanged effective
   policy, rerun that leg instead of treating it as equivalent.
6. Run a **complete 143-test native sanitizer matrix at F2**, including normal
   completion of the unchanged normalized fault sweep and leak-checking
   teardown. A standalone longer-time binary run may be diagnostic but does
   not turn the failed native F1 CTest into a pass. Do not substitute the O1
   preparation binary or omit already passing tests from the complete F2 run.
7. Create new runner/auditor/completion evidence names and pin them separately.
   The preserved F1 matrix runner hardcodes the F1 freeze filename and exclusive
   `ranking-sanitize-*` output names; overwriting those would destroy provenance.
   A new runner must read F2 and use a new output namespace, retaining raw
   failure output as well as success output. A new bridge-aware aggregation
   must name four successful F1 configurations plus successful F2 sanitizer,
   exact source/policy differences, inherited artifact identities and the
   preserved failed attempt. It must not assert one identical five-leg frozen
   revision. Old strict auditors/helpers remain immutable; any revised helper
   is a separately reviewed input, not a weakened old predicate.
8. Reconcile the final source audit, current source seal and completion helper
   against the actual current F2 CMake bytes and accepted bridge. Preserve all
   historical seal FILE identities and their historical scope. The planned
   current seal's path inventory need not change for a timeout-only edit, but
   its current CMake digest must. Verification/status publication remains gated
   on actual complete evidence; no timeout is accepted by prose alone.

The historical P05 record supplies a source precedent for this narrow form of
bridge: four configurations at A, complete sanitizer rerun at B, one conditional
watchdog change, identical implementation/assertions/compile commands and
honest clean-metadata limits. It is not automatic authority for C02. The new
C02 record must establish its own concrete inputs, exact difference, complete
rerun and independent matrix/source-audit acceptance.
