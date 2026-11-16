# P07 excluded proposal review

Status: Astra static review of preparation only, 2026-11-07. P07 remains
`not_started`. No ordinary source or frozen P05 input changed for this review.

The review covered [Refactor.md](../../Refactor.md) §5.4/P07, the
[design preflight](p07-design-preflight-2026-11-07.md),
[implementation seams](p07-implementation-seams-2026-11-07.md),
[draft API](p07-api-proposal-2026-11-07.hpp),
[generator](p07-generator-proposal/README.md),
[structural key](p07-key-proposal/README.md),
[independent collector](p07-reference-proposal/README.md), and
[facade/cache](p07-facade-proposal/README.md).

No blocking implementation defect was found. Root/parent enumeration and
dynamic anchor/subset digits cover the finite normal-form family without
fixed-width scope masks. Structural pruning preserves every requested-height
member. Each seed/generated draft reaches independent P02 validation and the
original proved-height gate; alternatives retain the supplied original
`VerifiedOptimum` and its unchanged witness/certificate.

Framed structural tokens retain root, scopes, original native occurrences and
grouping. Complete binding serialization and admitted context fields fence
cache reuse; full token comparisons establish equality. Saved stages preserve
actual generator/validator/key positions. Candidate vector/payload preparation
precedes dedup membership, after which publication cannot allocate. Cache
insertion prepares its new node before eviction. Immutable ownership avoids
snapshot chains/cycles, and workers clean up flat state.

Variable-width comparisons, vector relocation, admission serialization and
excluded validator scratch are stated costs consistent with logical-step
limits. They do not imply allocator-byte or hard-time guarantees. The README
cleanup statement was clarified: cancellation after failure/exhaustion is
inert, matching P06/P05; owner destruction releases terminal-state scratch.

Root's complete 225-query family/key comparison and separate proposal fault
probes support these findings but do not replace integration acceptance.
Root's separate public-P06 `CertificateReplay` witness probe additionally
preserves a unary-generalized original witness alongside the normal-form tree,
retains its original certificate, and attaches a newly supplied provider proof
to reused cached uppers. This closes that supplemental witness case; its native
regression registration remains an integration gate.

## Typed report follow-up review

The review additionally read every file under
[p07-report-proposal](p07-report-proposal/README.md), including its three typed
writers, strict schema, actual-artifact probe and mutation validator. No
blocking report implementation defect was found. This follow-up was read-only
apart from this review amendment; it did not repeat the reported O0/O3 runs.

- [report.hpp:9](p07-report-proposal/report.hpp#L9) accepts a live provider or
  immutable candidate/snapshot handle, not editable progress or upper-only
  aggregates. Export is allocating IO outside enumeration quanta and creates
  no checked authority. Moved candidate/snapshot handles are explicitly
  rejected; a moved provider fails through its original-proof accessor.
- [report.cpp:66](p07-report-proposal/report.cpp#L66) derives the outer exact
  binding from the supplied original proof and delegates its full certificate
  to native `write_verified_optimum`. Supported context and family versions are
  checked. [report.cpp:89](p07-report-proposal/report.cpp#L89) checks candidate
  height and binding against that proof, and writes the alternative tree only
  under `checked_upper` with `checked_upper_only`. It never substitutes that
  tree into the original witness. P02 validity is trusted through the private
  candidate artifact rather than asserted by a caller-provided Boolean.
- [report.cpp:102](p07-report-proposal/report.cpp#L102) preserves primary source,
  original generation sequence, residual last-step and typed residual trace.
  The absence of a public reuse-ledger accessor is disclosed; the report does
  not invent cache-reuse provenance or a globally unique sequence meaning.
- [report.cpp:107](p07-report-proposal/report.cpp#L107) samples live diagnostic
  status, limits and counters without advancing it. Snapshot export reads the
  immutable prefix's own exhaustion flag, not its current source provider or
  requested candidate count. Every envelope explicitly restricts optimization
  to structural height and exhaustion to admitted seeds plus normal form.
- The schema's certificate refinement requires a non-null minimum and witness
  through the existing required certificate fields. Context/family/status
  constants, strict named objects, residual-source requirements and progress
  phase/exhaustion relationships agree with the typed writer. Repeated full
  binding/certificate exports in snapshots increase explicit IO cost but do
  not violate advance accounting or ownership contracts.
- [report-probe.cpp:58](p07-report-proposal/report-probe.cpp#L58) checks exact
  native proof export equality, independently replays embedded original
  certificates, and checks candidate P02 validity and distinct alternative
  export. The v1/date-v2/metadata-v3 fixtures, frozen-prefix checks, no-advance
  check and legacy-reader rejection are meaningful supplemental evidence.
  [validate-probe.py:38](p07-report-proposal/validate-probe.py#L38) exercises
  strict extra-field, null evidence, scope/status, numeric, provenance and
  inconsistent-exhaustion mutations across the three report kinds.

The schema does not prove cross-field binding/height equality, prefix count,
key validity/uniqueness, provenance truth, or actual exhaustion. For example,
consistently editing an exhausted phase and flag is not independent completion
evidence. This is an explicitly documented boundary, not a schema-validity
claim of proof authority. There is no new reader; any future reader must check
those invariants and independently replay proof/upper validity before creating
checked artifacts. The 23 reports/48 rejected mutations per build are the
report author's recorded runs, not runs repeated by this review.

## Remaining integration gates

P07 remains `not_started`. Before native acceptance, register the reviewed
implementation/report/schema and independent regressions through the ordinary
public/build/tool boundaries; retain the original-proof/alternative-upper
separation in that integration. Required remaining coverage includes mandatory
height-three/P05 cases, broader exact-binding mutations (including ordered and
repeated heads, aliases, typed constants, ignored terms and catalog metadata),
malformed-claim/type boundaries, large-query bounded work, residual/cache
failure paths, varied slicing and resource extensions, and the ordinary
five-build verification matrix. Carry the unary-generalized original-witness
probe into native regressions.

For report integration specifically, add a genuinely published distinct
residual-source candidate and its cached provenance path, resource-stopped and
failed diagnostic reports, and fuller typed/catalog/head binding fixtures.
Preserve explicit allocating-export costs and treat schema checks as structural
validation only. The current corpus discloses its missing residual-source
case; none of the report evidence supplies that coverage implicitly. The
original P05 sanitizer gate and source seal remain separate and root-owned.
