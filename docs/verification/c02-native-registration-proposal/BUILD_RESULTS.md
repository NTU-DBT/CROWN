# Publication build evidence and limits

The author performed direct compiler/archive/link preparation only. No generated
binary, Python checker, CMake, CTest, symbol tool or benchmark was executed.
No native file or frozen predecessor packet was edited.

## Final optimized publication check

`/tmp/crown-c02-native-registration-release-1` contains 19 successful C++23
compiles: three pure ranking units, two bridge variants, ten ranking consumers,
two guide variants and two isolated original/patched JSON probes. It has five
successful archive constructions and 12 executable links. All 36 command exit
records are zero; all final diagnostic logs are empty. This is a direct `-O3`
check, not a native CMake Release build or execution result.

Every compile uses `-O3 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion
-Wsign-conversion -Werror -pthread`. The testing macro is present only for
the testing bridge, census consumer and testing guide object. Project include
paths select the publication headers and patched JSON. The original probe
instead has only its separate original-header include root and standard-library
dependencies. Both JSON executables link without CROWN archives. No diagnostic
suppression, `-fpermissive`, optimizer downgrade or assertion removal was used.

Three accepted coherent C++ archives (core/SQL/plan) are copied unchanged.
Two matching runtime archives are constructed from exactly 14 pinned base
objects each, omitting the predecessor combined-build bridge object. Three
new pure objects and each separately compiled bridge form three further
archives. Thus the direct check has eight C++ archives and 77 total
implementation objects: 72 reused coherent inputs plus five new pure/bridge
objects. The unchanged matching Release parser C archive is separately pinned.
No cached native C++ archive, reference archive or report archive is linked.

`build-evidence/reused-objects.tsv` records all 72 reused sources/definitions/
objects. Their original command, dependency, input and before/after records
are pinned as provenance files, not rerun as historical source-entry checks.
The final publication source/object/command/artifact manifests identify the
fresh inputs and exact archives used. Pure consumers link only ranking/plan/
SQL/core/parser. Runtime consumers link precisely one variant's bridge/runtime.
The native generated commands must still establish this graph independently.

Compiler: Ubuntu GCC 13.3.0, with compiler/frontend/assembler/linker/archiver
paths and file hashes in `build-evidence/compiler.sha256`. System headers are
included in compiler dependency records and the input manifest. Host paths
belong to preparation evidence; no installed/native API depends on them.

## Retained earlier direct checks

`/tmp/crown-c02-native-registration-strict-1` compiled the two bridge variants,
ten consumers and two guide variants at `-O2`, then linked the pure and split
bridge graph. Its initial patched JSON probe compile failed because GCC inlined
the replacement delete/free pair and diagnosed mismatched allocation under
`-Werror`; the complete failed command/log/status remains in
`initial-json-diagnostics`. The narrowly scoped `noinline` annotations resolved
it, with no changed assertion or warning flag. Both final JSON variants compile
and link cleanly at `-O2` and separately at `-O3` under
`/tmp/crown-c02-native-registration-release-json-1`. The final full `-O3` check
recompiled all 19 new TUs from the final publication bytes and supersedes those
earlier compile checks. None of these author outputs was executed.

## Accepted root preparation execution

Root's immutable completion record is
`build/verification/c02-preparation-execution-completion.json`, SHA-256
`4c39ded5d7d09d2802181e476f236c403f8f7533d8606e6fe3f3a53fa58e2d60`.
Its five accepted raw receipts are:

| Receipt | SHA-256 |
| --- | --- |
| c02-producer-strict-root-attempt-2.json | 295bbefe40b04f00554cf41860ac31ab1948dedb5765cf6f4d3aa33093ccf447 |
| c02-independent-strict-root-attempt-2.json | 4dbaea8b8bea1308b024f6b8353515e8ef20868e8af40a6835d7b6bea9cd6645 |
| c02-json-cleanup-root-attempt-2.json | 54450d525d1b474773f0eac81285a175142684289f722da8fa6d36c7d3c44f2e |
| c02-independent-sanitize-root-attempt-1.json | f2de554cf3ffccaaad2156b4ef92125960a26156e2a704d57eebcabfe178484e |
| c02-producer-sanitize-root-attempt-1.json | cb50105893664d5e414c10d0b3ba7adea9f818b1f414cfe215e8f0e703911c62 |

All five had stable input/artifact guards. Producer strict passed ten consumers,
including 8,112 persistent-failure positions. The full matching sanitizer
packet passed its ten sanitizer consumers and supplemental normalized strict
and sanitizer sweeps. Each normalized sweep exercised 38,763 positions and
reported zero recovered-cleanup positions while preserving complete committed
owner/workload state and old results. Both independent variants passed eight
public groups and the 54-operand/2,916-pair/16-boundary decimal oracle.

Original-header cleanup reproduced abort with bad_alloc. Patched ordinary and
ASan/UBSan/leak probes each passed 30 cases/96 fault positions, and original/
patched sizeof/serialization outputs matched at 254,074 bytes with SHA-256
`3affc55d1305636b4d6e7ad77c7a89cec58f1649ad40f74b1ca68a967fb5fdb0`.
Those exact outputs contain the old `deque_json` label. The new native label
and noinline probe copy have compile-only evidence here; their actual native
output/control execution remains pending. No old output hash is asserted for
the newly labelled complete stdout. Deep cleanup is covered; deep serialization
and unsupported allocator/container profiles are not claimed.

The producer sanitizer raw driver retains an outdated pending entry for its
sanitizer closure. The accepted completion record resolves that entry from all
12 terminal stage results and stable guards; neither raw receipt is rewritten.
Full native C02 registration, all 143 tests in five configurations, generated
214-command/variant/source inventories, complete JSON rebuild/legacy behavior
and final source/metadata acceptance remain root-owned pending gates.
