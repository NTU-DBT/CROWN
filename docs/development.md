# Add a query or extend CROWN Next

## Add a supported query

Start with the [quickstart](quickstart.md) and [interface contract](guarantees.md).
For an already supported query, contribute only data:

1. Write SQL and a catalog with physical column order, exact scalar types and
   nullability. Keep each self-join occurrence explicit.
2. Add ordered update templates and expected current rows and signed deltas from
   an independent relational implementation. Include duplicate insertion,
   absent deletion and loss of one of several projected supports where relevant.
3. Bind the catalog digest with `prepare_workflow_input.py`; compile, validate the
   artifact, inspect EXPLAIN and run `verify-trace` before any timing experiment.
4. Exercise a fresh session, a checkpoint and a separate-process restore using
   the same input prefix. Compare sequence, current rows, signed output and source
   positions with the expected trace.

The [route-labels SQL](examples/route-labels/query.sql),
[catalog](examples/route-labels/catalog.json),
[update template](examples/route-labels/events.template.jsonl) and
[SQLite expectations](examples/route-labels/expected.json) show this contribution.
For a maintained regression, register the fixture in the existing appropriate
test corpus. Its [workflow manifest](../tests/workflow/manifest.json) and
[runner](../tests/integration/workflow.py) define that corpus's format; admission
fixtures alone do not test runtime execution. Never add a query-specific operator
or job class to accommodate another query in the supported family.

## Extend semantics or a primitive

A new SQL feature, backend or public guarantee is an implementation task, not a
fixture change. Follow the relevant [Refactor task](../Refactor.md), document its
semantic contract first, and keep unsupported behavior explicitly rejected until
the actual runtime, recovery and independent-oracle gates pass. Preserve original
atom identity, physical support, arithmetic, account/work grants and proof scope.
Do not silently replace exactness with a heuristic or narrower query family.

Keep the main path direct. Use ownership to release private partial work. Retain
a catch only when it performs a distinct obligation such as aborting a caller-held
token, latching consumed input, separating durable decisions, or translating a
public diagnostic. Do not add defensive wrappers, retries or per-update inspection
state without an actual contract. [Handler dispositions](code_specs/error_handling.md)
explain existing boundaries; [memory ownership](memory_accounts.md) explains the
accounted primitives. Performance claims must include real preparation, lookup,
payload, publication and teardown work.

## Write code for human inspection

Explain purpose, inputs/outputs, invariants, ownership, failure behavior and cost
for each meaningful primitive or block. Link the actual source/caller and local
design contract; cite a paper section only for the claim it actually establishes.
Use concise structural descriptions for imports, aliases and non-operative
boundaries. A comment next to a method is not proof of neighboring methods.

The [source index](code_specs/README.md) records exact ranges and current hashes.
The [review guide](code_review.md) connects code to paper versions and engineering
arguments. After a source edit, review affected contracts, regenerate with
`python3 tools/generate_code_specs.py`, then run `python3 tools/check_code_specs.py`.
Do not refresh a review hash merely to hide a stale contract. Use focused existing
tests for affected behavior; a comment-only correction can be checked by an exact
diff and unchanged executable tokens. Record commands, actual outcomes, limits and
remaining work in the [ledger](task_ledger.md) and [handoff](handoff.md).
