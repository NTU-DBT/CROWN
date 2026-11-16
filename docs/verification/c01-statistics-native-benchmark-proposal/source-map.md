# Source map

| Proposal file | Purpose | Future destination or treatment |
| --- | --- | --- |
| native_benchmark.cpp | Production-only native runtime update benchmark, independent literal replay guards, JSON output | Standalone verification consumer; never compiled into the native product |
| build-only.sh | Strict O3 compile/link script for the benchmark and complete runtime/collector source closure against pinned Release dependencies | Reproduction command only; no CMake target is added |
| README.md | Workload, timing boundary, collection profiles, independent checks, accounting limits, and root build/run commands | Proposal record only |
| build-evidence.md | Exact compile/link command, compiler/optimization distinction, source/object/dependency/log/binary hashes | Author compile/link evidence; no execution evidence |
| input-pins.sha256 | Frozen combined package, native source/header dependencies, CMake source map, and cached optimized dependency archives | Inputs for this isolated proposal |
| source-map.md | File roles and exclusion boundary | Proposal record only |
| package.sha256 | Hash manifest for all proposal files except itself | Proposal identity |

The production benchmark includes no test-only APIs or macros. The build-only
script compiles the combined overlay's support, physical, Delta, session,
statistics, collector, and reference-storage sources with the unchanged native
runtime source closure. It then links pinned plan, SQL, core, and pg_query
Release archives. The cached Release archives are dependencies, not new
benchmark objects; their optimization flags and byte hashes are recorded
separately.

The candidate uses the actual public C01 overlay API and existing runtime
initialization/update/result interfaces. It does not publish any API or change
O07 output, schema, test, tool, or build target.
