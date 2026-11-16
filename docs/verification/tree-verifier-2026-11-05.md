# P02 tree-verifier verification packet, 2026-11-05

Historical P02 snapshot. Use [exact-oracle-2026-11-05.md](exact-oracle-2026-11-05.md)
and its manifest for the current worktree; subsequent P03 changes intentionally
change the source checksums recorded here.

Input revision: uncommitted worktree on `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. Exact current build and contract
inputs are fingerprinted in [tree-verifier-sources.sha256](tree-verifier-sources.sha256).
This packet supersedes the foundation packet as the current worktree audit;
the original [foundation evidence](foundation-2026-11-05.md) is historical.

## Disposition and boundary

P02 is verified for the structural-tree contract in Refactor.md §5.1–5.2
and its task card. The verifier checks supplied trees; it constructs none.
Successful output is `height_status:valid_upper_bound`. It does not prove
minimum height, lower a physical execution plan, or claim a runtime guarantee.
P03, P04/P06 optimality evidence, the remaining frontend and runtime tasks,
and G2 remain open. G0 remains open for A02's recorded disposition. No R0/R1
release is claimed.

Artifacts:

- `include/crown/ir/tree.hpp`: native/generalized tree nodes, typed node IDs,
  optional separator/connex/height claims.
- `src/planner/verify.cpp`: independent Cover/Connect/Guard/Above checker,
  topology validation, maximal connex traversal and native-height accounting.
- `src/io/document.cpp` / `include/crown/io/tree.hpp`: strict plan codec,
  shared duplicate-key/version parsing, deterministic tree/report serialization.
- `apps/crown/main.cpp`: standalone `validate-plan QUERY.cq.json PLAN.tree.json`.
- `schemas/tree-v1.schema.json` / [tree_plans.md](../tree_plans.md): versioned
  input contract, diagnostics and exact interpretation of the metrics.
- `tests/unit/tree_verifier_test.cpp`: rule corruptions, claimed metadata,
  independent connex-subtree enumeration, dynamic arity/depth, strict codec.
- `tests/structural/plans/manifest.json`: 19 hand-authored structural cases.
- `tests/integration/validate_plans.py`: CLI exit/report/witness assertions,
  including malformed input and checks that remain active under Python `-O`.

## Actual verification outcomes

| Build / check | Result |
| --- | --- |
| GCC 13.3 Debug | 7/7 CTest tests passed |
| GCC 13.3 Release | 7/7 passed |
| GCC 13.3 Debug with ASan + UBSan | 7/7 passed; no sanitizer findings |
| Clang 18.1.3 Debug with libstdc++ 13 | 7/7 passed |
| Fresh final source snapshot under `/tmp` | Configure/build and all 7 tests passed |
| Structural CLI runner under Python `-O` | 19 cases plus malformed input passed |
| Draft 2020-12 schema audit | Schema valid; 18 CQ files and 19 tree files validated |
| Focused independent source review | Luna Max found no implementation/safety defect; identified four coverage gaps, addressed below |

CTest retains the five foundation tests and adds `tree_verifier` and
`plan_fixtures`. Full local outputs are in `build/verification/p02-release.log`,
`p02-sanitize.log`, `p02-clang.log`, `p02-clean-source.log` and each build's
CTest `Testing/Temporary/LastTest.log`. The ignored raw outputs remain local;
the source manifest, fixtures, docs and commands are durable handoff artifacts.
The clean snapshot copied only declared native build inputs, schemas, tests,
tools and vendored dependencies, and removed its temporary source/build tree
after success. It was a fresh source copy, not a committed checkout.

Build/test commands used below also reproduce the checks. After the review
additions, all variants were rebuilt and retested using these configurations:

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug
cmake --preset release
cmake --build --preset release --parallel 2
ctest --preset release
cmake --preset sanitize
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize
cmake -S . -B build/clang-debug -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_COMPILER="$PWD/build/toolchains/clang18/root/usr/bin/clang++-18"
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 -O tests/integration/validate_plans.py build/debug/crown tests/structural/plans
sha256sum -c docs/verification/tree-verifier-sources.sha256
```

Compiler package versions/hashes, CMake/Python versions, dependency pins and
the sandbox execution issue are unchanged from the foundation packet. Clang
was extracted into ignored build output; nothing was installed globally.

## Finite scope and independent checks

The CLI corpus contains ten valid and nine invalid cases. Valid cases cover
native/projected singleton roots, Boolean queries, a full two-edge generalized
root, a projected native-root path, a disconnected empty-scope root, equal
scopes with distinct occurrences, an empty-body tree, and both seven- and
nine-atom residual counterexample trees with checked height three. These two
trees are **upper witnesses**, not minimum certificates. Invalid cases isolate
Cover, Connect, Guard, Above, Connex, separator, height underclaim, height
overclaim and connex-certificate failures, with concrete node/variable/
occurrence witnesses. Malformed JSON separately produces exit 2; structural
rejection produces exit 1 with a report on stdout.

Native unit tests independently enumerate every parent-closed root-containing
subset of a four-node tree for all 16 head subsets and compare admissible
output-subtree existence with C*. This checks the connex lemma without
reusing its traversal. Separate tests verify smaller valid connex claims,
hidden-separator certificate rejection, empty head/separators, nullary input
versus empty body, duplicate scopes, unary generalized validity, missing/
duplicate occurrences, projected native scopes, invalid roots/edges/cycles,
and arbitrary fan-out. A 70-variable example and a 1,500-node chain exercise
dynamic sets and iterative traversal. One tree's maximum native count and
maximum edge depth arise on different paths and must remain separate metrics.

Codec tests reject unknown fields/references, duplicate keys/IDs/scope
entries, catalog/version mismatches, a generalized occurrence binding, a
missing native binding, and bool/negative/floating numeric claims. Unsigned
64-bit catalog versions retain precision; a uint64-maximum height claim is
either checked and rejected as false on the supported 64-bit platform or
rejected as out of range on a smaller platform. Invalid tree reports expose
no checked height; unknown topology exposes no invented separators.

The focused review identified output consistency, untested root/occurrence/
connex lookups, hidden-separator certificates and numeric boundaries as test
coverage gaps. These assertions were added and the final matrix/clean snapshot
rerun. The implementation's core validity logic was unchanged after that
review. No external human mathematical/optimality review is asserted.

## Next dependency

P03 must search the full admissible family using the normal-form argument in
Refactor.md §5.4: at most m−1 generalized nodes, all relevant native-scope
subsets including empty, and native-count height. Preserve unary-node
contraction proof, occurrence identity, arbitrary fan-out and honest resource
statuses. Check every returned tree through this verifier. The seven-/nine-atom
fixtures must never acquire an unproved height-two optimum label. F05 still
needs canonical query/plan identity and full certificate versioning; P06 still
needs independent optimality/budget evidence before strict compilation.
