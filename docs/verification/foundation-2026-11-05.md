# Foundation verification packet, 2026-11-05

Historical packet for the foundation snapshot. Later changes intentionally
change its source checksums. Use [exact-oracle-2026-11-05.md](exact-oracle-2026-11-05.md)
and its manifest for the current worktree; the older results remain a record
of the earlier checkpoint.

Input revision: uncommitted worktree based on
`e369a623517723b3be3ea3e9806779f3c591e7f9` (`master`). Build sources and
contracts are fingerprinted in [foundation-sources.sha256](foundation-sources.sha256).
The original task scope is [Refactor.md](../../Refactor.md), especially §16.2.

## Disposition

A01/A03/A04's first assignment has passed its foundation acceptance checks.
A05's seeded generator/shrinker acceptance also passed. P01 recognition has
passed its separate finite structural comparison and witness-replay checks.
G0 remains open for the unresolved A02 project-license/provenance disposition;
G1–G11 remain open. R0 is not complete: P02's checker and P03's exact tree
oracle are still required. This is no R1 runtime or release claim.

## Implemented semantic scope

Version-1 direct-CQ set semantics over non-null int64, binary strings and bool;
full physical row identity, insert/delete/no-op epochs, ordered/repeated heads,
projection, repeated-variable/constant filters, ignored physical columns,
Boolean/empty conjunctions, disconnected CQs and self-joins. The reference
materializes joins and computes exact before/after set differences independently
of a production planner, propagation engine or cursor. No floating tolerances
or approximate arithmetic are used.

GYO classification separately checks H and H+F, returns replayable reductions
or a failed core, preserves occurrence IDs, and reports height as unchecked.
The SQL parser spike proves syntax-library build/API use only. The reference
CLI cannot parse or admit SQL.

## Executed build and test matrix

| Configuration | Compiler / library | Outcome |
| --- | --- | --- |
| Debug | GCC 13.3.0 / libstdc++ 13 | 5/5 tests passed |
| Release | GCC 13.3.0 / libstdc++ 13 | 5/5 tests passed |
| ASan + UBSan Debug | GCC 13.3.0 / libstdc++ 13 | 5/5 tests passed; no sanitizer findings |
| Debug, second compiler | Clang 18.1.3 / libstdc++ 13 | 5/5 tests passed |
| Fresh source snapshot in `/tmp` | GCC 13.3.0 / libstdc++ 13 | Configure/build, 5/5 tests, version smoke passed |
| Optional parser build spike | C compiler GCC 13.3.0, libpg_query 18.1.0 | Checksum, clean upstream build and valid/invalid SQL smoke passed |

The five tests are `semantics`, `recognition`, `cli_smoke`, `fixtures`, and
`reference_fuzz`. Full local outputs are in `build/verification/`
(`gcc-release.log`, `gcc-sanitize.log`, `clang-debug.log`, `clean-source.log`)
and CTest's `Testing/Temporary/LastTest.log` files. Parser output is in
`build/parser-spike/run.log`. These ignored logs are local evidence; commands
below reproduce it. The clean source snapshot copied only declared native
build inputs, dependencies, tests and tools into a fresh directory and removed
that directory after success; it was not a committed checkout.

Reproduction:

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
./tools/parser_spike/run.sh
python3 -O tests/property/reference_fuzz_test.py ./build/debug/crown --seeds 18 --updates 12
python3 -O tests/integration/fixtures.py ./build/debug/crown tests/regression
sha256sum -c docs/verification/foundation-sources.sha256
```

## Finite coverage and independence

- Thirteen hand-calculated fixture pairs cover singleton/no-ops, proper
  projection and hidden supports, root witness, two-edge path, Boolean,
  ancestor/child deletion, self-join cross term, unused physical columns,
  repeated variables/constants, disconnected product, equal scopes on
  distinct tables, empty body and contradiction. Registry: [reference_fuzz.md](../reference_fuzz.md).
- Native tests cover exact integers above 2^53 and at both int64 limits,
  binary strings with embedded NUL, bools, repeated outputs/aliases,
  70-variable CQs, output ownership, rejected updates leaving state/sequence
  unchanged, and strict typing/schema/version/duplicate-key rejection.
- Independent SQLite 3.45.1 execution matched 18 seeds × 12 events: six query
  shapes × three scalar types. Three generated invalid variants (sequence,
  type, operation) were rejected. The duplicate-delta fault exists only in a
  test wrapper and shrank to one insertion with zero initial rows. The actual
  minimized query, SQL, seed, trace and corrupted/expected outputs are saved in
  [shrinker-example.json](shrinker-example.json). Both Python drivers also
  passed under `-O`, so their checks do not depend on `assert`.
- Structural tests enumerate ordinary undirected join trees separately from
  GYO, then check variable connectivity. All 4,681 ordered bodies with 0–4
  scopes over three variables agree, as do 4,680 body-plus-head hypergraphs
  for 0–3-edge bodies and every head subset. Every reduction witness is
  independently replayed. Hand cases cover projected endpoints, cyclic body
  with an acyclic augmented graph, no phantom head atom, and 70 variables.
- The published Draft 2020-12 JSON Schema and all 13 fixture inputs were
  checked with the locally available `jsonschema` validator. Native validation
  additionally enforces cross references and lexical integer-token rules.

The fuzz shrinker holds query/catalog/values fixed and reduces initial rows
then events. It does not prove globally minimal traces. Neither finite data
tests nor finite structural enumeration prove a new planning theorem.

## Environment and source provenance

Linux x86-64, GCC 13.3.0 (`13.3.0-6ubuntu2~24.04.1`), CMake 3.28.3,
Python 3.12.3, SQLite 3.45.1. Clang was not installed globally. Exact Ubuntu
packages were downloaded under `build/toolchains/clang18/packages` with:

```sh
apt-get download clang-18=1:18.1.3-1ubuntu1 \
  libclang-common-18-dev=1:18.1.3-1ubuntu1 \
  llvm-18-linker-tools=1:18.1.3-1ubuntu1
```

Each was extracted with `dpkg-deb -x` into `build/toolchains/clang18/root`,
using installed `libllvm18`, `libclang-cpp18`, `libclang1-18` version
`1:18.1.3-1ubuntu1` and libstdc++ 13. Package SHA-256 values:

| Package | SHA-256 |
| --- | --- |
| clang-18 | `628b16701014ef7ad648380b20ea74b90dd543857f933b3e34d2fc042783de25` |
| libclang-common-18-dev | `d41631bb752815a8196261d1030c096591c59678c8adfbf2e6a740a691b49e80` |
| llvm-18-linker-tools | `50f0bcfa784e42f8bf0eac31aeb6a20798fb6174cc31efe021f12ae71af91b23` |

Pinned JSON/parser dependencies and component notices are in
[dependencies.lock.json](../../dependencies.lock.json),
[source_baselines.md](../source_baselines.md) and the decision records. The
parser build emitted two upstream upb `-Wmaybe-uninitialized` warnings;
the native project code passed its warnings-as-errors builds. The parser
library itself was smoke-tested with GCC only, not under sanitizers or Clang.
Its parse results were freed on both success and failure paths; no broader
parser lifetime claim is made.

## Remaining gates and next work

A02 records both immutable source pins and environment discrepancies. An
intended project distribution license is still undecided; no legacy component
was copied. This does not block independent code. Full F01 scalar/catalog,
F02 owned parsing, SQL binding/equality normalization, complete CQ/plan
canonical schemas, P02/P03 tree validity/optimality, runtime, cursors and
recovery remain. There are no latency/space complexity or benchmark claims
for the reference path. No external mathematical reviewer has signed off on
G2/G5. User-requested Luna Max agents handled provenance, parser spike,
fixtures and generation; the root agent reviewed their artifacts and ran the
build/test matrix.
