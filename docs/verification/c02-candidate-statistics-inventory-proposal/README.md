# C02 candidate statistics inventory — excluded preparation

**Status: C02 `not_started`.** This packet inventories existing P07 candidate
and proof APIs alongside the current native C01 owner/workload statistics APIs.
It does not propose a ranking algorithm, design C03, or claim cost/byte
optimality. It adds no native integration or report format.

Read [the inventory](inventory.md) for the acquisition path, typed scopes,
freshness and denominator limits. [The source map](source-map.md) connects each
claim to current public headers, implementations, and existing fixtures.
`input-pins.sha256` records exact hashes for the cited source, fixture, and
historical context inputs; `PACKAGE_SHA256SUMS` pins the packet outputs.

The inventory was prepared by source and fixture inspection only. No candidate
provider, runtime, binary, checker, or project build was executed. The cited
`c01-statistics-*-root-results-2026-11-07.md` files describe earlier isolated
preparation slices; they predate the current native C01 integration and are
historical evidence, not a current integration-status statement.

All NodeId, OccurrenceId, IndexRequirementId, route, depth, and owner-capture
facts below are scoped to one exact Catalog/Query binding and one lowered plan.
Capture statistics from the actual initialized owner for each candidate plan;
do not transfer plan-local values between candidates.
