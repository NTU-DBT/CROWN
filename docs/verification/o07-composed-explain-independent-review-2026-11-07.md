# Independent composed O07 EXPLAIN review — 2026-11-07

**Static disposition: no blocking source defect found in the frozen composition.**
This is acceptance for proceeding to independent composed-package execution and
native integration, not runtime acceptance or O07 completion. The reviewer ran
no executable, Python test/schema checker, CMake or CTest, and changed no native,
implementation, schema, test or frozen-package file.

Reviewed package:
`docs/verification/o07-composed-explain-proposal/readiness.json`, canonical SHA
`a4e759965fea2efcb3578080f0445d80579bb6f0daf1a5c36ea4149c6310f30a`.
Independent read-only hash verification matched all 30 package files, 172
baseline pins, 25 source-map paths, 65 distinct recorded compiler dependencies,
and all four final runtime/CLI artifacts. The compiler evidence records nine
runtime TUs and seven report/CLI TUs plus the link in each of O0/testing and
O3/production. These are the author's compiler/linker results, not executed
acceptance evidence. O07 remains NS.

## Authority, binding and structural domains

The final owning factory accepts immutable P08 plans and existing typed height
handles, not progress flags, JSON, caller-supplied validity or a supplied session
plan. Exact comparison covers every current Catalog/Query field: constraint
variants/status/FK targets and ordered columns, schema versions, statistics,
hints, types/nullability/collation/decimal metadata, raw Value bytes, occurrence
and output order, aliases and contradiction. It uses native equality, with no
JSON allocation or UTF-8 admission restriction. Candidate context includes the
update profile and all current policy/canonicalization fields. References:
composed `overlay/src/observability/explain.cpp:18–69,132–161`.

Selected upper/candidate evidence must match the selected tree and height.
VerifiedOptimum deliberately retains its original witness while a separately
P08-validated selected tree can share the proved minimum height. A P07 candidate
retains its original proof; report code does not replace that proof's witness.
Family exhaustion is explicitly scoped and never claims global cost completeness.
Session capture gets the actual owner plan through the private-construction
SessionReportMetadata handle; it does not join an arbitrary plan using a digest
(`explain.cpp:95–106,189–197`, `session.hpp:67–93`).

The constant-false route is correctly separated: absent structural evidence,
height 0 is `checked_constant_operator`, its original upper/minimum/witness and
claims are null, and the structure/tree transports identify an executable
operator domain. Genuine compatible empty-body structural-height-0 evidence is
still allowed. A nonempty structural minimum of at least 1 fails the selected
height fence against the operator; structural infeasibility remains available
through the separate owning QueryExplanation form. References: owning
`explain.cpp:151,166–169`; IO `explain.cpp:364–383,494–495,544–548`.

## Ownership, lifecycle and diagnostic scope

Current mode/profile and current configuration are separate from each attempt's
captured begin configuration. Historical options are complete native values,
with owner/generation and honest generation saturation, and historical guarantee
prose is not copied from a later profile. The inherited successful-switch hook
updates only after actual mode change; no-op, invalid/busy and failed bootstrap
paths do not advance it. No new mode-generation overflow throw appears.
References: cursor-layer `src/runtime/delta.cpp:141–155,1365–1377`; composed IO
`explain.cpp:233–251`.

Session metadata retention uses the immutable compiled plan, scalar options and
static-string-view profile. These copies and retained shared metadata handles
are nonallocating in the stop/drop/publication hooks. They retain schema/plan
metadata, not runtime tables, journals, leases or rows. Session drop removes the
runtime and trace storage; subsequent metadata has null runtime state, gauges
are unavailable, and newly captured traces have zero retained records. An older
report owns its copied numeric records. References: composed
`session.cpp:155–168,229–251,411–441`.

Gauges are an explicit allocating committed diagnostic read, including with
observation off; they do not create or advance a cursor. Private physical and
window-metadata work correctly makes session gauges unavailable, even if the
underlying delta owner is otherwise ready. Pending/prepared runtime capture
also withholds gauges. Stopped sessions retain readable committed state; dropped
sessions retain metadata only. References: composed owning
`explain.cpp:175–197`, session `418–421`; cursor-layer support
`support.cpp:1454–1465`, physical `physical.cpp:591–599`.

Unavailable registry payloads serialize as null, not stale numeric values.
Physical inclusive/exclusive work follows the inherited successful nested-charge
bookkeeping, not a magnitude heuristic; support work is not additive with the
inclusive total. Scope remains admitted-attempt attempted work, including aborts.
References: composed IO `explain.cpp:258–265,282–294`; cursor-layer
`physical.cpp:108–128,216–224`.

Trace capture is an owning copy from the real ObservationTrace, retaining only
numeric records. The bounded preallocated live buffer appends without allocation;
its explicit dropped saturation flag is used by the actual saturating increment.
Sampling, absent IDs, owner/attempt/sequence, truncation, abort and release are
reported honestly. The trace is not a complete committed event log and does not
pin tuple data. References: composed owning `explain.cpp:175–199`; IO
`explain.cpp:270–305`; cursor-layer observation `observation.cpp:149–174,203–240`,
`observation.hpp:202–247`.

ObservationSnapshot/Summary are now **nontrivial** due owning shared metadata.
They must not be memcpy-serialized or ABI-mixed with old objects. The final
runtime closure rebuild and compiler dependency pins are appropriate, but all
native test/application consumers still need rebuilding during integration.

## Encoding, schemas and CLI

The main manual writer enforces encoded append caps, validates UTF-8 at explicit
text export and escapes quotes, backslashes and controls/NUL. Nested query,
run-context, cursor and gauge writers receive the remaining encoded budget;
outer closing delimiters are checked too. Export returns a complete string or
throws, and admission/unwind does not construct JSON. DOT uses generated numeric
IDs and escaped labels. References: composed IO `explain.cpp:15–52,417–426,525–548`.

The byte cap is an **output** cap, not total diagnostic heap/CPU work: trace and
gauge copies, tree scratch and nested temporary strings are additional. Some
inherited component writers scan a full string for UTF-8 before append failure;
no bounded CPU/whole-memory claim should be inferred. Static closure of schemas
and their null/availability/domain branches was reviewed through `make_schema.py`;
no schema validator was executed here. Semantic equalities, node/cause references,
owner associations and proof publication still require independent assertions.

The CLI explicitly constructs/advances real owners when requested, defaults
query work to zero, and uses typed replay for optional proof admission. It does
not fabricate evidence during capture. Argument applicability, duplicate options,
16 MiB artifact input cap, output caps and sanitized error codes are present.
Its stream-session entry point is jsonl/binary; typed/window and broader workflow
coverage belong to library tests/O08, not an invented CLI claim.

## Native source-map checklist for root

1. Apply the consolidated `composed-native.patch`/25-path `source-map.json`
   against its pinned native baseline, or reproduce its exact final bytes.
   Do not apply both the full patch and the incremental patch. The incremental
   patch assumes all preceding layers. Exclude the obsolete prototype CLI.
2. Keep query owning/IO source units in an acyclic `crown_query_explain` target
   depending on core. Do not place them in core while also adding a reverse
   dependency on the report target. Existing P06/P07 authority remains unchanged.
3. Add `src/runtime/observation.cpp` and rebuild the complete runtime closure:
   support, physical, delta, session, replay, window, IO support and inspection,
   plus observation. Apply the final cursor-layer runtime headers and the
   composed session header. Rebuild testing and production objects separately,
   and rebuild every test/app/report consumer; never reuse old runtime archives.
4. Put owning physical report, final composed IO, run-context IO and cursor IO
   in the report target depending on runtime/plan/query-report/core (and SQL
   through the existing plan closure). Add the final `apps/crown-explain/main.cpp`
   executable. Its consumers must see the same final headers and testing macro
   as the linked complete runtime archive.
5. Install/version both composed v2 schemas. **Also add the two frozen standalone
   query v1 schemas** from `o07-query-explain-proposal/schemas/`: the full composed
   source map carries only the v2 schemas, while its public standalone query
   exporters still produce `crown_query_explain`/`crown_query_witness` v1. V2 embeds
   these definitions, so this is an integration-map addition, not a V2 codec
   defect. Do not install the superseded physical report v1 schema as the final
   composition contract.
6. Preserve legacy timing and transition-capture assertions. The frozen
   ObservationOptions default is `timed`, so untouched legacy fixtures with
   `capture_transitions=true` remain valid. Only an explicit observation `off`
   together with that legacy flag is rejected
   (`cursor.../src/runtime/support.cpp:132`). Do not automatically rewrite
   existing fixtures to counters or remove capture/timing/cost/fault assertions.
   Intentional mode changes need their own rationale and preserved coverage.
7. Keep literal off/counters/timed/trace parity tests at the same legacy-capture
   false setting. Reconcile mandatory work/results/event IDs, zero optional
   clock reads in off/counters, and persistent failure/cancel/noexcept cleanup.
   Allocation-index sweeps must remain complete after changed option/layout
   allocation patterns; changing the expected semantics to hide a failure is
   not migration.
8. Bring over independent tests as native targets/checks without including test
   CPPs or old-ABI objects. Run full original gates plus the composed lifecycle,
   JSON/human/DOT/tree, schema, CLI, exact binding, mode/context retention and
   fault corpus. Retain all 426+11 independent query-oracle inputs and the extra
   genuine post-upper-depth lifecycle fixture; resource outcomes remain failure,
   not accepted omissions.

## Remaining acceptance gates

No concrete source blocker remains from this review. Required unobserved gates
are execution of this exact composed source/ABI/schema package, then native
integration and the required full matrices/sanitizers. Prior layer or query
suite passes do not certify the newly composed report.

In particular require actual stopped/dropped and private-window reports,
pre-drop trace-copy lifetime plus post-drop release, unsampled/truncated/aborted
and saturated trace diagnostics, exact current-versus-historical mode/context,
strict hidden upper/no-witness rejection, constant_false0 versus structural
triangle negative, callback retry/output-disposition truth, cap43 and
constraint-scan incomplete-work gauges, raw UTF-8/NUL boundaries, and persistent
capture/export faults with unchanged owner work/clock/proof state. The native
legacy trace-fixture compatibility and standalone-schema additions above remain
integration work. No S05 whole-memory, durability/recovery, cost-optimality,
performance or arbitrary-query completeness acceptance is implied.
