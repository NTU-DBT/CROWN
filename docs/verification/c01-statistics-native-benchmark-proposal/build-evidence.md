# Compile/link evidence

The final author command compiled and linked successfully with exit code 0. It
did not execute the resulting binary. There was no CROWN_RUNTIME_TESTING define.
The benchmark's correctness guards use explicit runtime checks, so the exact
production flags include DNDEBUG without relying on assert.

Compiler: c++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0.

Every benchmark, runtime, and collector source object was compiled from source
with this exact flag set:

    -std=c++23 -O3 -DNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread

The include order was the frozen combined overlay include and private runtime
include, then native include and private runtime include, with third_party
system headers:

    -I docs/verification/c01-statistics-combined-proposal/overlay/include
    -I docs/verification/c01-statistics-combined-proposal/overlay/src/runtime
    -I include -I src/runtime -isystem third_party

Each object compile additionally used -MMD -MF <output>.d -c <source> -o
<output>.o. The exact source list, output naming, compiler invocation and
logging are in the frozen build-only.sh. That script compiled these 16 objects:
the benchmark source; native support, physical, Delta, IO support/inspection,
replay, session, window and observation runtime sources; combined overlay
statistics, collector, owner, workload and combined-statistics sources; and
combined overlay reference storage.

The exact author build command was:

    CXX=c++ bash docs/verification/c01-statistics-native-benchmark-proposal/build-only.sh /tmp/crown-c01-native-benchmark-author

The link used the same C++23/O3/DNDEBUG/six-warning/-Werror/pthread policy and
all 16 fresh objects, followed by the pinned Release archives inside a linker
start/end group:

    build/release/libcrown_plan.a
    build/release/libcrown_sql.a
    build/release/libcrown_core.a
    build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a

No CROWN runtime archive or previous O2 combined-overlay object was reused.
The linked executable hash is 5512cb54f1edad66b05f0215ee9bcd685629b22e5f8b69ea0ca6f8e0bfe05c15.

## Object and dependency identities

| Object | SHA-256 | Generated dependency file SHA-256 |
| --- | --- | --- |
| native_benchmark.o | d41e0ab57f1a429d150e2dc944daebc31561ba06d5ec29d2406be1e8176b1e88 | cf06f0679b295bf17654e7a6d5e4a18a7d638ef2fd3be35cdb67a9e81ef1ab8d |
| runtime_support.o | daea53ef1a4220926f11dfd476f9acc56d9f7e4bdc68e5bd36368c3631909e35 | 6834e5aa413929e5426a112854744cccd327311fb4f094489df2c2bc961273ed |
| runtime_physical.o | b1ddc4be03375537ba36146921dee7137491e57ede810582bf47a4571cccff68 | cf694065ee154cb63acf6be01fbcd182a3e33ee9b36416b7ca30325fa688230b |
| runtime_delta.o | a27744d1433829d03cf2f155532a1625a3e8c30f833d57014bde9078e97480db | be2fe134144b8958eebaa68c6c3efe6373998f874a5125f6d1f642a23f4b35bb |
| io_support.o | b252f506d402f09bdc0be9f9d928b8744d23eec4075a227cce00534e48ec790e | c317d3b6ab647482477fa3f513fc19c3132787912af65327bc1262c5dc7f23ee |
| io_inspection.o | 498194b88732948c1e3dace183c0fd46c7f8b8372d17b2cee7e13adaea352a34 | 7e6041e916839bfe54eb1c88d4af9313ba514e9a19d8996ff31d6a50ee87d9e8 |
| runtime_replay.o | 748b0cb1a4064ef160af19c4059e1e40557212a067e41b6331f6d3312e52196d | 52ff4b3ff85aad570f836cd0b33d98ad9d171c0aae5874f966474533fe6a4c04 |
| runtime_session.o | 22fa9df9698ccf03d3ad3b7c4e836a7779dc163254613bd6c9bcd3d53373b890 | f1b0c298462babf847bd3f4c92bbdae262e36911a384cfda6b2b30ca6a373371 |
| runtime_window.o | 38f0be2ceafa598e7e37f1b8a9cf4b493759d6228edae128c406646e2f84c8c7 | 836cf63712335c97fe881700bb9d59c068467e3d40a5dc10ff721f6b635c49df |
| runtime_observation.o | 237cb03f8d5ad145b83a1ba54241e63e2c744133754a527028743539ab188586 | a62f5e34cd3b5aaca30c12ed8fc60b471cc3f9b17354e800ccd1088a520aab87 |
| runtime_statistics.o | dcbe29819ad01ba7f4656f77dd90077b47fb139a24cbc397017631a666620054 | 0117bcb162a64279a34bb26e8c6dac3360db889d240dd4899b1d7228d201858a |
| runtime_statistics_collection.o | 38344ef47ed62e3b9299a588cffa23d7ef61bd2c00745f85e3fc0a3ce2406d94 | 8126d8d08553a5f1089c0633fcd80102700d289b9b5550633449381d2ed1d15a |
| runtime_owner_statistics.o | b1e8489f6a526bc81b3105b294f06035299cdac3cfc5e9036fcedc23d3b6b3e2 | 7d557783460416f5fac8632fa6358ba5ec8699b91e09c3579d932ec43739ceb7 |
| runtime_workload_statistics.o | 71e37e44b7993c5819c6727f57b6b7f32c757ce4c137678e712fbeca32e6a184 | 72e3589808f762264eced9f9f83e6925d5fedc768fc71b72299ed03eb054aae8 |
| runtime_combined_statistics.o | 6a08b4d43baf6d7711c21620cdaf7c3c6e838960e3bcfcf69f760c765c556eba | 7c491323394e62eadd46a652be3acf4a807f1fee1a203eb2403fe190fb225bf0 |
| storage_reference.o | 2827e2263ef2fdc124564dab2dec6dd50bf4813162896122707314d735a80f9e | a63e27b411604240a107269f52cefb5ea15be9ed49e7a59523b94b09f59e3cd2 |

All 16 compile logs and the link log were empty; each has SHA-256
e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855. The
benchmark translation-unit source SHA-256 is
e74d0f5d63c36734ea31d28fa02be70dd9b94740759e566dd414afb479c5d027.

## Cached dependencies and distinction

The prebuilt CROWN plan, SQL and core archives are pinned in input-pins.sha256.
The existing Release compile_commands.json is also pinned and records -O3
-DNDEBUG and the six project warning flags for those C++ targets. Those
archives are dependencies, not runtime objects in this benchmark build.
libpg_query is a separately pinned external Release archive; this packet does
not claim its source was recompiled by the benchmark script or infer its
optimization flags. All native runtime and C01 collector objects used by the
executable were compiled fresh at O3 by this build.

The current benchmark source and build script SHA-256 values are recorded by
package.sha256. input-pins.sha256 contains the frozen combined proposal
manifest/source inventory, direct native source/header dependencies, CMake
source list, compile database and cached archive hashes. No benchmark
execution, test, checker, CMake, CTest or nm command was run by the author.
