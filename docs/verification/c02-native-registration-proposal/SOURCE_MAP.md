# Native destination and provenance map

`source-map.tsv` is the exact machine-readable overlay-to-native mapping.
`source-provenance.tsv` records each native destination's kind, pre-edit hash,
proposal hash, origin file/hash and transformation. `pre-edit.sha256` pins the
seven overwritten native files; `new-paths.txt` lists the 31 new files, which
must be absent before the guarded application. No native removal is proposed.

| Source family | Native destinations | Treatment |
| --- | --- | --- |
| Frozen C02 baseline overlay | Two public headers, eight private implementation/helper files, existing candidates.cpp and active JSON header | All 12 files exact copies; the two existing implementation/vendor destinations retain their original pins |
| Producer tests/helpers | Eight ranking test sources and three support headers | Exact copies; helper relocation needs only the target's private tests/support include |
| Independent tests | Public eight-group and private decimal-oracle sources | Exact copies; actual native fixture tree paths retained |
| Frozen guide | tests/examples/ranking_usage.cpp and docs/ranking.md | Functions are exact compiled source; prose adapted to native linkage/status and completed with exact formulas/resources |
| Frozen accounting document | docs/ranking_accounting.md | Exact copy of the implementation's detailed accounting contract |
| Independent JSON probe | tests/unit/json_cleanup_test.cpp | Two accurate labels and three noinline annotations/comment; no assertion/numeric change |
| Preserved upstream header and local diff | third_party/nlohmann/upstream/nlohmann/json.hpp and patches/crown-cleanup-oom.patch | Exact original/patch copies; original MIT notice already remains native and unchanged |
| Existing native publication files | CMakeLists.txt, README.md, dependencies.lock.json, docs/native_build.md, docs/source_baselines.md | Narrow registration, current provenance and documentation changes; pre-edit bytes pinned |
| New publication support | tools/verify_json_cleanup.py and third_party/nlohmann/README.crown.md | Authored wrapper and explicit local vendor notice |

The active JSON hash is f763c58b..., original hash aaf127c0..., and patch hash
65acb363.... CMake and the lock use the complete values. The original control's
include root is isolated and its executable links only compiler/standard
runtime support, never crown_json or a CROWN archive. Existing MIT license
hash is pinned independently; the patch introduces no project license choice.

The proposed tests/examples/helpers live under tests; the wrapper lives under
tools; original/patch/notice live under third_party. These are all included by
the existing clean-source copier. CMake, tests and wrapper contain no dependency
on this verification packet, its source map, historical temporary archives or
the guide author's temporary source. Only the author's direct reproduction
uses accepted immutable C++ objects, with explicit provenance.

The 72 reused direct-build implementation objects are 31 core, ten SQL, three
plan and 14 per runtime variant. They were all built with the same patched
JSON header. The final optimized publication check rebuilds the three pure
ranking units and both bridges, then ten consumers, two guide variants and
two isolated JSON probes. Runtime archives are rebuilt from exactly their 14
base objects, removing the old combined-build bridge member. No reference or
report archive is linked. The pure consumer cannot acquire a runtime edge;
testing consumers use only their matching testing bridge/runtime.

All source/header/compiler/object/archive inputs and actual command/log/exit
files are pinned in the build evidence. This proves which direct compiler
inputs were used, not that CMake configured the same graph. Root must inspect
the native generated commands, archive membership and successful pure/matching
links in every required configuration after applying the reviewed mapping.
