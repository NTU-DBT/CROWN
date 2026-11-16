# B02 reproducible workload manifest acceptance

B02 is verified on11 November2026 against its manifest/source-classification/
generation/replay requirements. The full [Refactor.md](../../Refactor.md) goal
remains active:48 verified cards, A02 in progress,29 not started;78 total.
Work is uncommitted on baseline `e369a623517723b3be3ea3e9806779f3c591e7f9`.
No controlled timing, full official-suite qualification or R1 release is claimed.

## Artifacts and contracts

The [workload guide](../workloads.md) explains the generator, closed schema,
[generated manifest](../../benchmarks/workloads/manifest.json),
[CROWN inventory](../../benchmarks/legacy/manifest.json),
[DynaGox inventory](../../benchmarks/legacy/dynagox/manifest.json) and
[external source registry](../../benchmarks/external_imports.json).

The generated corpus contains24 SQL definitions/144 finite traces. Twenty
admitted set-query families have140 runnable cases; cyclic, non-free-connex,
bag and aggregate controls are separately rejected. Every runnable case binds
SQL, catalog, exact input/oracle bytes, semantics, ordered head/output expressions,
atom scopes and structure, physical update/source/no-op contract, expected
admission/backends and output demand. Independent assignment joins and SQLite
agree on2507 physical events, including controls;2486 belong to admitted cases.

Families cover full/projected paths, Boolean heads, high-fanout full/projected
stars, hidden witnesses, composite separators, nested/contained/equal scopes,
eight-column relations, wide UTF-8/NUL strings, disconnected products and
multi-alias self-joins. Seven regimes include insertion-only, explicitly charged
loading then deletion, global/per-relation FIFO, mixed updates, churn/no-ops and
input-mix shifts. Actual promises are validated. Seed/data scale and query size
are separate axes; generated outputs are byte-reproducible within declared
finite oracle limits. This finite mechanism corpus is not all-free-connex proof.

## Native and package acceptance

| Configuration | Native corpus evidence | Imported source evidence |
| --- | --- | --- |
| GCC Debug |560 replays /9944 epochs /644 commands|24 parsed and shape-checked|
| GCC Release |560 replays /9944 epochs /644 commands|24 parsed and shape-checked|
| Clang18 Debug |560 replays /9944 epochs /644 commands|24 parsed and shape-checked|
| ASan+UBSan/leaks Debug |560 replays /9944 epochs /644 commands|24 parsed and shape-checked|
| Clean source-only GCC Release |All10 selected CTests pass in13.39s|Included in selected cohort|

Every epoch compares actual signed deltas, complete current rows, sequence and
source positions with independent expected results on both reference/indexed
storage and delta/maintenance modes. Full snapshots are taken for correctness
in both modes, so these are not performance measurements. The exporter is a
generic test-boundary public-API consumer with no relational oracle or query
class dispatch, linked only to production archives. The four control builds
use unchanged sealed C03 libraries; their exact archive hashes are checked.

The integrated fresh cohort covers workload manifest/replay/imports, workflow/
installation, schema/admission/reference-fuzz and C03/C02 compatibility. It
builds all15 production libraries plus the CLI reference library. The source
copy contains exactly1650 files, with no previous cache/objects. All274 C03
predecessor test definitions and both local B02 commands/properties remain;
277 tests are registered. All277 current sanitizer definitions retain ASan
leak/halt and UBSan halt/stacktrace settings. Registration checks are separate
from native control execution; this packet is not full277 release acceptance.

All actual compiled units retain strict C++23 warnings/errors; executable test
checks remain enabled. Only reviewed unchanged pinned upstream C/Make diagnostics
appear. Existing runtime implementation, old tests, the C++ exporter and all336
generated SQL/catalog/event/oracle files are unchanged through import integration.

The earlier [local checkpoint](b02-workload-local-corpus-2026-11-11.md) preserves
its original8/9 fresh invocation: root omitted the selection archive from its
verification build targets. Completing that target and rerunning only the failed
install test passed. The integrated driver includes the complete package closure
and passes10/10 in one invocation. No source, flag, assertion, cap or timeout
was weakened; original failure and repair receipts remain.

## Source-grounded classification

The CROWN inventory covers13 distinct labels/116 scenarios across all five
local specs. Root checked122 source fingerprints/120 exact Git blobs at the
original CROWN pin. Backend predicates, heads, window/bag/aggregate semantics
and missing trace contracts remain distinct. Source inspection grants no legacy
build, runtime-equivalence or timing evidence.

All24 original DynaGox Queries.md definitions are imported at commit
`c6811db68a34ab3b32722968c4e1e821f730c5ac`, with exact source Git blobs and
per-file hashes. Original COUNT/SUM/MAX/distinct/grouping outputs are retained;
all are aggregate queries. Root independently extracted occurrence/equality
scopes from the parser AST and checked22 acyclic equality bodies and two cyclic
ones, DUMBBELL and TPCH-Q5. Body acyclicity is not aggregate or set-CQ admission.
The automated check repeats source/SQL/shape checks and rejects false source
pins, replacement SQL, data availability and native timing eligibility.

The two inspected C++ source files supply scoped insertion/milestone observations;
other update/output contracts remain explicitly unknown. No algorithm from those
sources is copied into the native engine. Imported JOB/CEB/LSQB/TPC-H/TPC-DS
definitions are the pinned DynaGox experiment variants, not qualification of
complete official suites. CROWN SNB windowed variants are independently recorded.

## Evidence and limits

Under `build/verification/`, prefix `b02-workload-` retains predecessor/control/
documentation preimages, frozen inputs, exact source copies, raw phase receipts,
all original native replay reports, import controls, sanitizer registration,
eight-requirement review and final seals. `import-matrix-audit-v1.json` binds3519
actual native/raw artifacts, including126 newly compiled units, five ELFs and16
CROWN archives in the final fresh build, plus preserved local-control evidence.
All current jobs closed successfully and no build overlapped CTest. Earlier
failed receipts remain historical evidence.

Root implemented/reviewed generation, validation, exporter and native acceptance.
Luna Max supplied two bounded classification proposals, independently checked
and corrected by root. No Astra was used. The local audit's reference-library
assertion check and imported-body extraction's local-constant handling were
corrected in verification tooling; runtime source and finite case bytes stayed
unchanged.

Runnable data is newly synthetic and checksummed. Real external dataset bytes,
catalogs, licenses and runtime contracts are unavailable and explicitly excluded
from timing eligibility. A02's distribution license remains unresolved; the
manifest grants no rights. Real dataset acquisition/qualification, controlled
measurements, baseline reproduction, held-out cost quality, remaining Refactor
cards and full release gates remain separate work. No timing or general coverage
claim follows from corpus correctness.
