# Narrow repair after root attempt 1

The first C02 audit package remains frozen at manifest
`fcaaccae1a37880c65b648c953465d706f17967c92b7abb8154fc4304c30ee4a`;
its script is `44ee844bf3b8fc0a38f6cfe0772e74bdc63e12773731f6b381813a3d26875b03`.
Root's first actual attempt is preserved at
`build/verification/ranking-matrix-evidence-audit-attempt-1.json`, SHA-256
`cae96f4154a9188eeafb6024b251fa9d4789d6cf641e18d7e3d169cad9b891aa`.
The earlier root launch-guard failure stopped before auditor execution and is a
separate event. Neither failed receipt nor any native source is changed here.

The first audit accepted the clean-source leg but rejected the three terminal
incremental legs at a cached dependency lookup. The compiler's dependency file
for `crown_reference` / `tests/reference/tree_oracle.cpp` spells a header as
`tests/reference/../../src/planner/search_budget.hpp`. The fresh integration
baseline records its canonical name `src/planner/search_budget.hpp`. Comparing
the spelling directly to baseline keys wrongly reported a changed dependency.

The revision resolves dependencies within the actual source root and uses the
canonical relative name for the freeze and cached-byte baseline. It retains
every project dependency's compiler spelling, source-relative spelling, canonical
relative name and frozen SHA-256. The observed and canonical working-tree paths
must resolve to the same file and both match the exact current frozen bytes.
Aliases crossing the source boundary, paths absent from the execution inventory,
or contradictory identities fail. The clean source directory has already been
removed; its retained dependency spelling is mapped to the frozen current source
counterpart, without claiming a new post-removal file read. All actual compiler,
JSON-header, fresh/cached, linkage, numeric and allocation rules remain intact.

Root also observed two still-unapproved Clang allocation differences: 8,127 versus
8,112 positions in `ranking_exceptions`, and 38,778 versus 38,763 in the normalized
fixture. Both retain zero recovered cleanup positions and the original semantic
assertions. This packet approves neither difference and changes no expectation.
The auditor will expose the corresponding exact preparation and cross-config
differences for root review. No allocation waiver or fixed numeric-row total is
introduced. The sanitizer leg remains pending until its terminal evidence exists.

The author only read, hashed and authored files. Root alone runs the revision,
including any syntax checks. This packet cannot advance C02 or the full goal.
