# Build evidence and attributed root execution

The author used Ubuntu GCC 13.3.0, C++23, all six strict warning/error flags,
`-UNDEBUG`, and the exact flags/paths recorded per object. No produced binary,
Python checker, CMake/CTest, symbol tool or benchmark was executed by the author.

## Terminal compile/link results

| Build | Implementation/reference TUs | Main consumer TUs | Main archives/links | Additional normalized-fault consumer |
| --- | ---: | ---: | --- | --- |
| Strict | 82 | 10 | 7 archives, 10 executable links; all exit 0 | 1 TU + 1 link, both exit 0 |
| ASan/UBSan | 82 | 10 | 7 archives, 10 executable links; all exit 0 | 1 TU + 1 link, both exit 0 |

Thus the final artifact set has 93 compiled project TUs and 11 consumer links
per configuration. The implementation contains 67 distinct source paths; the
15 runtime/adapter paths are compiled separately with and without
CROWN_RUNTIME_TESTING. Every linked project C++ object uses the same patched
Json header. Only matching parser C archives are reused. No report archive is
linked. All final compiler and linker logs are empty.

Strict artifacts are under `/tmp/crown-c02-baseline-coherent-strict-1` and the
supplemental `/tmp/crown-c02-baseline-normalized-fault-strict-1`. Sanitized
counterparts replace `strict` with `sanitize`. Exact sources, defines, commands,
full dependencies, logs, exit records, before-after source/header hashes,
archive members and artifact hashes are retained. The complete compiler
dependency inventories include system compiler headers; this is a pinned build
context, not a reproducible-container or all-system-libraries claim.

The earlier draft compile diagnostics remain under the distinct
`/tmp/crown-c02-baseline-strict-attempt-*`, `production-draft-2`,
`payload-draft-1`, and `tests-draft-1` directories. Resolved draft errors were
strict indentation/sign-conversion diagnostics and a fixture variant
initializer/brace issue. They were not hidden by changing the strict flags.
Those old-ABI/old-header objects are not final link inputs. The separate
integer-checkpoint-1 object remains historical and is not substituted for the
current ABI.

## Held execution checkpoints

`checkpoints/strict-1` has nine manifest entries. Its three repository-root
guards contain 619 input rows, 109 object/archive/executable rows, and 685
command/evidence rows. The source overlay manifest has 12 paths (two existing
destinations and ten new paths), SHA
`50e919ce4384ce7e7d4ca550ed09d5ae74b3579549441b6ba4be0c401aa56bf6`.

`checkpoints/sanitize-1` has six manifest entries and explicitly lists 12 root
commands: the ten matching sanitizer consumers/checker plus the strict and
sanitized supplemental normalized-replay fault consumers. Its input guard
has 641 rows, including both configurations' full dependency paths and the
accepted frozen design. Its main artifact/evidence inventories contain 109
and 685 rows; the supplemental guard contains 25 source/artifact/evidence rows.
Relative input/evidence paths resolve from repository root; isolated/system
paths are absolute. Checkpoint package manifests resolve from their own
directories. The full packet `PACKAGE_SHA256SUMS` resolves from this packet's
directory. No manifest includes itself.

The full `INPUT_SHA256SUMS` and its copied sanitizer checkpoint input guard
have SHA
`b3d99557190b7ac1d6109f054ebafdb5a47a3aa298e9f45820a6e2a780a11587`.
Both configs' library/object source manifests state exact macro variants; all
matching implementation/header/archive bytes are held through root guards.

## Completed root receipts at this cutoff

These are root executions, distinct from author compilation. Exact receipt
hashes are in `build-evidence/ROOT_RESULTS_SHA256SUMS`.

| Root receipt | Observed terminal scope |
| --- | --- |
| `build/verification/c02-producer-strict-root-attempt-2.json`, SHA `295bbefe40b04f00554cf41860ac31ab1948dedb5765cf6f4d3aa33093ccf447` | All ten strict gates passed; 1,424 lexical pins / 1,423 physical files stable. Direct all-policy persistent faults covered 8,112 allocation positions, zero cleanup recoveries; complete owner/workload/prior result checks passed. P07 binding bytes/prefix allocation profile preserved; inherited report checker covered 35 records and 54 schema mutations. |
| `build/verification/c02-independent-strict-root-attempt-2.json`, SHA `4dbaea8b8bea1308b024f6b8353515e8ef20868e8af40a6835d7b6bea9cd6645` | Eight independent public groups and the 54-operand / 2,916-pair arithmetic suite passed with 1,205 pins stable. This used the current ABI and coherent patched-header production closure. |
| `build/verification/c02-json-cleanup-root-attempt-2.json`, SHA `54450d525d1b474773f0eac81285a175142684289f722da8fa6d36c7d3c44f2e` | Original failure control reproduced abort(-6, std::bad_alloc). Patched ordinary and ASan/UBSan/leak probes each passed 30 cases / 96 fault points. Original/patched serialization and sizeof output were exactly equal. Custom container and deep-input limitations are stated in JSON_REPAIR.md. |

Initial root launch guards stopped before execution over legitimate dependency
aliases or retained old diagnostic logs; attempt 2 corrected the runner,
preserved those failures and required no source/assertion weakening. The later
root receipts, rather than a first launch or an unobserved running session,
support the passed rows above.

At this packet cutoff, full matching sanitizer execution, supplemental
normalized-owner fault execution and independent public sanitizer execution
remain root-owned pending gates. Their compiled inputs are ready and frozen
in the named checkpoints. A future root receipt can accept them without
rewriting this historical preparation packet. Native C02 registration, clean
native matrix/source gates and card completion remain separate. C02 stays
`not_started`; no native, ledger or handoff file was changed by this author.
