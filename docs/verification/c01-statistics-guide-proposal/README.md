# C01 runtime statistics API guide proposal

Documentation-only, excluded preparation, 2026-11-07. **C01 remains `not_started`.** The candidate guide is `overlay/docs/statistics.md`; it changes no native source, header, test, CMake target, tool, report or schema. It documents the accepted owner-generalized state-capture and online workload-observation proposals separately. It makes no claim that their APIs have already been merged into one native interface.

## Pinned inputs

The accepted owner-generalized revision is pinned by manifest digest `dc7276b9c6427784f67372a95efa0365de3859203a0c1706fe2fe494ef02869e`. The accepted online-collector proposal is pinned by manifest digest `61281d60312f371930a6ddcb4c2c51570eb6d5c70264432715a7da0a3d247281`. The exact package manifests, public headers and implementation files consulted are in `input-pins.sha256`.

The guide also pins the owner, online, literal-reference and component-benchmark root result notes, plus the established native observability documents. Those results establish each preparation slice separately; they do not establish their joint integration or C01 acceptance.

## Snippet compile status

The owner and online examples were each extracted with stub runtime parameters into distinct `/tmp/crown-c01-guide-*` translation units. Both were compiled with `-std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -O3 -c` against their corresponding accepted overlay. Both attempts stopped before reaching the examples' API expressions because the workspace include set lacks the transitive `<nlohmann/json.hpp>` dependency included through `crown/frontend/parser.hpp`. No object file was produced and no successful snippet compile is claimed. No executable, test, checker, CMake, CTest or `nm` command was run.

The examples use actual public API types and accessors but intentionally leave table/node/field and descriptor identities as caller-supplied values from an already validated, initialized runtime. They do not invent a runnable query or IDs.

## Scope

The guide records exact population, status, budget, sampling, freshness, lifecycle, memory and schema boundaries from the pinned packages. It notes that current O07 v2 EXPLAIN/report and tree schemas do not contain C01 fields, and that compatible report/schema integration plus native engine overhead remain pending. Component benchmark medians are labeled synthetic component replay measurements, not engine throughput or query latency.

Root will reconcile this guide with the separately merged API package before any native documentation publication. `package.sha256` pins this proposal's files except the manifest itself; its digest is the proposal identity.
