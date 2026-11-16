# F04 normalization and adapter verification packet, 2026-11-05

Input revision: uncommitted `master` worktree based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. The full Refactor.md goal and all
78 task cards remain active. This packet does not claim integrated SQL
admission, a maintained CROWN runtime, or a completed R0/R1 release.

F04 is verified for the declared bounded contract. Current source/build/
contract/fixture fingerprints are in
[normalization-sources.sha256](normalization-sources.sha256). Earlier packets
retain their historical fingerprints.
All 282 input checksums pass. As at earlier checkpoints, the manifest excludes
verification packets/manifests and mutable handoff/ledger files to avoid
self-referential fingerprints. Build logs are ignored local artifacts.
This historical F04 packet precedes the
[F05 schema/identity checkpoint](schema-2026-11-05.md); its fingerprints retain
the earlier source state.

## Acceptance audit

| Required artifact or behavior | Evidence |
| --- | --- |
| Occurrence-keyed equality classes | `src/frontend/normalize.cpp` validates resolved types, identity/literal casts and supported integer promotion before union-find. Nullable referenced sources reject. Only unconditional direct column equalities merge; AND is flattened, OR/NOT remain predicates. |
| Constant/contradiction rules | Variable-free predicates use SQL three-valued evaluation; FALSE/UNKNOWN contradict the query. Distinct constants on one final equality class contradict, and equality to a NULL parameter/literal cannot become ordinary value equality. |
| Local predicate/output IR | Each adapter has resolved expression IDs, local predicates, explicit repeated-column checks and an ordered projection program. Bounded local scalar comparisons, Boolean composition and NULL/Boolean tests execute before tuple insertion. Cross-occurrence theta/OR filters and computed outputs reject explicitly. |
| Distinct mutable atoms survive | Every bound FROM occurrence has its own adapter, core table and atom. Equal/contained scopes and self-join aliases remain separate; hidden SQL aliases may be reused without core ID collisions. No key/statistic/hint authorizes atom elimination. |
| Physical identity and projection supports | `AdapterState` stores complete physical rows and per-occurrence uint64 support counts. Multiple rows projecting to one tuple emit only the first insertion/last deletion transition, including empty projections. Duplicate inserts/absent deletes consume sequence numbers without changing support. Overflow is checked. |
| Occurrence-to-base routing and atomic preparation | Stable occurrence-ID routes prepare all affected aliases in copies, check complete proposed source constraints and allocate transition results before swap-commit. Invalid sequence/type, unique-constraint failure and injected second-alias failure leave physical/logical/support state and sequence unchanged. This is adapter preparation, not maintained join propagation. |
| SQL versus handwritten CQ under A04 | A literal repeated-variable/constant CQ and a handwritten self-join CQ use the separate reference evaluator on original physical tables. Both match normalized/adapted evaluation. Twelve seeds ×48 physical events add 576 exact update comparisons, including alias cross terms and set no-ops. The handwritten queries do not call the normalizer. |
| SQL output behavior | Ordered/repeated/constant outputs survive class merging; local non-null computed outputs are projected by adapters. EXISTS keeps a nullary core and maps it to one false/true scalar row. A NULL inner select-list value does not change existence. Plain row-producing bags are rejected. |

## Finite coverage and boundaries

The unit executable covers repeated variables, class-constant contradictions,
OR without class merging, local three-valued logic, NULL literals/parameters,
exact dates/decimals with different declared scales, identity/narrowing-cast
boundaries, typed specialization, local computed outputs, output constants and
repeated positions, empty/no-FROM/nullary sources, 70-column projection,
owned/copy/move behavior, zero normalization work budget and Unicode locations.

The independent fixture runner has 17 success cases, seven semantic/parameter
diagnostics and four CLI/configuration errors. Sixteen SQL cases also compare
manual expected rows and output names with SQLite. The hidden join-alias
case uses a manual expected layout because PostgreSQL and SQLite bind joined
column alias lists differently. The runner uses explicit checks active under
`python -O`, preserves named parameter indices, independently interprets local
SQL expressions, passes adapted core inputs to the separate A04 oracle and
checks the mapped SQL rows against manual/SQLite expectations. It does not
use production normalization to define the expected SQL results. Dynamic
C++ support-count behavior is tested in the unit executable separately.

All referenced source columns must declare non-null, including unused columns.
The physical `Value` model has no NULL. Constants are checked after parameter
specialization; nonconstant outputs require non-null bound types without
further inference from filters or specialized Boolean operands. Changing
parameters requires a new program/state. Arithmetic/functions, broad casts,
timestamps, nullable source rows, row bags, cross-relation theta predicates,
ordering/limit and broader SQL operators remain outside this bounded subset.
The source model remains flat, with no inheritance expansion.

`normalize-sql` always reports `admission_status:not_checked`. Its emitted
program is inspection output; F05 still owes the complete normalized schema,
reader/validator, canonical semantic identities and upgrade/rejection policy.
F06 still owes integrated structural/semantic admission. `AdapterState` uses
copy-commit for correctness; no maintenance complexity, cursor, recovery,
query delta enumeration or runtime performance claim follows from it.

## Verification matrix

| Configuration | Outcome | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 19/19 pass | 9.88 s |
| GCC 13.3 Release | 19/19 pass | 2.06 s |
| ASan/UBSan, parser C included | 19/19 pass | 59.31 s |
| Clang 18.1.3 C/C++ Debug | 19/19 pass | 8.02 s |
| Fresh source-only Release | 19/19 pass | 2.05 s |

The full clean configure/build/test run passed in 130.74 s and removed its
temporary source/build directory. All eight existing schemas pass Draft
2020-12 meta-validation; all 17 actual success artifacts' nested core and
binding documents validate against the CQ v3 and SQL-binding schemas. This
does not substitute for F05's complete normalized-program validator. The
fixture runner also passes under `python -O` with all 17/7/4 outcomes.

Reproduction:

```sh
cmake --build --preset debug --parallel 2
ctest --preset debug
cmake --build --preset release --parallel 2
ctest --preset release
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 -O tests/integration/normalization.py build/debug/crown tests/frontend/normalization
python3 tools/verify_clean_build.py --log build/verification/normalization-clean-source.log
```

The sanitizer preset instruments parser C as well as project C++, halts on
ASan/UBSan failures and enables leak detection. Clang 18 uses the locally
extracted C and C++ compilers described in the handoff. The clean snapshot
contains source/build/fixture/schema/dependency inputs and no existing build
directory, legacy tree or VCS data. Full command outputs are under ignored
`build/verification/normalization-*.log`.

## Next dependencies

Finish F05 with normalized/adapted program round-tripping, strict mandatory
fields, canonical alias-independent semantic identity and explicit schema
evolution. Include parameter values, full source schema/version/type policies,
adapters and output/wrapper semantics in identity; a core CQ hash alone is
insufficient. Then F06 can connect SQL normalization with the existing
recognizer and structured admission results. S01/S02, physical lowering and
maintained runtime work remain separate. A02 license disposition and G2/V02
independent mathematical review remain open.
