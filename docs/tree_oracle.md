# Exact minimum-height tree oracle

P05's separate residual candidate provider is verified. It does not
change this CLI's exactness contract; reduction round counts and induced-query
proofs cannot establish the original query's minimum. See the
[verification record](verification/residual-candidates-2026-11-07.md) and
[residual contract](residual_candidates.md).

`crown tree-oracle` searches for a minimum-height CROWN tree for the direct CQ
in a version-1, version-2 or version-3 query document. It checks a candidate tree with the independent
P02 verifier and replays a lower-bound certificate before reporting a minimum.
It does not optimize cost, install a runtime, execute SQL, or run the query.

Input occurrences retain their complete declared scopes and tree coverage.
Contradiction-to-constant normalization and other SQL rewrites remain frontend
work; this command optimizes the supplied body/head structure.

## Commands and limits

```sh
crown tree-oracle QUERY.json [WORK_LIMIT]
crown verify-height QUERY.json CERT.json [WORK_LIMIT]
```

`QUERY.json` is a direct-CQ document in the format described by
[`cq-v1.schema.json`](../schemas/cq-v1.schema.json). Initial table rows and
updates do not affect the tree search. They are accepted as part of the input
document, but the certificate binding uses the same catalog and query with
empty rows for every initial table and `updates: []`.

The optional `WORK_LIMIT` is either an unsigned integer, including `0`, or the
word `unlimited`. It defaults to `10000000` work units for each search or
certificate replay. A limit of zero stops before work is charged. The limit
counts implementation work, not elapsed time. `unlimited` removes only the
work counter limit: both commands still stop at 256 logical owned frames.
The 4096 literal-scope limit belongs to literal/reference tests only; it is not
a CLI option or an additional limit on these commands.

Work is charged at explicit implementation checkpoints. This is not a hard
wall-clock or memory cap. Controlled tree-validation/copy/traversal transitions
are metered; input admission and standard-container/allocator/scalar-width costs
remain separate. The library's optional active-time limit is cooperative and
excludes caller pauses. The continuation_v1 counts are finer than P03/P04 totals.

The oracle's search and its independent certificate replay each receive a
fresh work budget. Likewise, `verify-height` starts its own replay budget. A
resource limit during any of those operations cannot establish either a
minimum or infeasibility.

## Oracle result

The result JSON includes `height_status`, `selected_height`, lower and upper
height bounds, `height_search_complete`, `height_evidence`, `tree`,
`certificate`, and work statistics. Cost is reported as `not_optimized`, and
the runtime backend as `not_installed`.

- `height_status: "proven_minimum"` means an admissible tree supplies the
  upper witness and the independently replayed lower bound proves no smaller
  height is possible. `selected_height` and both bounds are that minimum.
- `height_status: "unsupported"` means the search completed and proved that
  no admissible tree exists for this body and head. The result has no tree and
  a certificate with `minimum_height: null`; its root state is proved
  infeasible, and `height_search_complete` is `true`. This is a completed
  infeasibility result, not a resource error.
- `height_status: "resource_limit"` means the search or its certificate
  replay stopped at a limit. It has no tree or certificate, a null selected
  height and upper bound, and `height_search_complete: false`. Its lower bound
  is only the universal bound (zero for an empty body, otherwise one). Do not
  read this status as infeasibility.

The empty-body query is a special completed case: its minimum height is zero,
its tree is the empty version-1 tree, and its certificate has no lower-bound
states.

## Exact search and fast paths

The optimized public algorithm is `crown_partition_exact_v2`. An empty body
uses the height-zero constant tree. A single occurrence, including a nullary
one, uses that native occurrence as a height-one root. A contradiction marker
does not erase a nonempty direct-CQ body before structural planning; frontend
constant-false routing is a separate contract.

For each variable x, let A(x) be the set of distinct occurrence indices whose
complete scopes contain x. The hierarchy fast path accepts a query when every
pair of incidence sets is nested or disjoint and, whenever x is free and
A(x) is a proper subset of A(y), y is also free. Equal incidence sets may
contain both free and hidden variables. It groups equal sets and builds a
height-one tree, retaining every occurrence leaf. A failed recognition only
falls through to complete search; it does not mean `unsupported`.

For a disconnected nonhierarchical query, only the full-root minimum proof
uses the component rule: its height is the maximum of the independently proved
component heights. Component upper trees join below an empty generalized root.
Equal complete native scopes form symmetry classes for branch enumeration;
search can skip equivalent choices, while the output tree still contains each
mutable occurrence exactly once. Branch-and-bound skips a candidate only when
already established lower bounds show it cannot improve the checked incumbent.
Residual-round counts and other heuristic estimates do not prune. The optimum
interface proves one minimum. [P07](candidate_alternatives.md) separately enumerates
its finite normal-form family plus admitted seeds; exhaustion is scoped to that
family, not all unary-generalized representations or global runtime cost.
Formal preservation arguments are in [planner_proofs.md](planner_proofs.md).

## Height certificate

Optimized search now emits
[`height-certificate-v2.schema.json`](../schemas/height-certificate-v2.schema.json),
with `schema_version: 2` and `algorithm: "crown_partition_exact_v2"`.
The reader/verifier also retain
[`height-certificate-v1.schema.json`](../schemas/height-certificate-v1.schema.json)
with its original exhaustive replay and `algorithm: "crown_partition_exact_v1"`.
Schema/algorithm version mismatches are rejected.
Both formats have a
`query_binding`, `minimum_height`, `tree`, and `lower_bounds`.

The binding is the deterministic document produced from the exact catalog and
query, with empty initial rows and no updates. It uses version 3 for nondefault
catalog metadata, otherwise version 2 when any catalog column is a date or
decimal, and version 1 otherwise, independent of the surrounding input
document's format version. Primitive catalogs with default metadata keep
their existing version-1 binding bytes. The reader compares
the serialized canonical document exactly and preserves JSON types, so for
example a Boolean is not interchangeable with an integer. This is a
type-sensitive document binding, not a semantic-alias canonical hash: there is
no query alias normalization or semantic hash in this version. A certificate
for a different binding is rejected.

Each lower-bound state has:

- `occurrences`: sorted, unique, nonempty zero-based atom indices;
- `generalized_allowed`: whether a generalized root is available in that
  residual state;
- `connex_reachable`: whether that state remains reachable through the
  root-connected output region; and
- `bound`: a positive integer lower bound, or `null` to claim that the state
  has no admissible completion.

For a nonempty query, the root state contains all atom indices, with both
flags true. A completed minimum certificate pairs its root lower bound with an
independently validated tree of the claimed height. An infeasibility
certificate has a null root bound and no tree. In the empty-body case,
`minimum_height` is zero, `tree` is the empty tree, and `lower_bounds` is empty.

The verifier does not trust the producer's selected height. It validates the
upper tree independently. V1 then enumerates all structural native-root and
generalized-root child partitions to replay the supplied lower bounds in
dependency order. An omitted child state receives the universal lower bound
one. Supplied nontrivial bounds must follow from every applicable root and
partition alternative; false bounds, duplicate states, malformed occurrence
sets, and dependency misuse are rejected. `null` is accepted only when the
enumerated alternatives establish that the state has no completion. Schema
shape alone cannot establish these query-relative facts.

V2 additionally derives equal-complete-scope occurrence classes itself and
transports checked state bounds only within those permutation orbits, preserving
both flags and rejecting duplicate orbit entries. For the full-query root only,
it independently derives disconnected components and uses their checked maximum
lower bound. All other alternatives retain exhaustive replay. Actual native
occurrences remain distinct in the upper witness. The preservation arguments
and resource exclusions are in [planner_proofs.md](planner_proofs.md).

More specifically, the v2 state key counts selected occurrences from each
complete-scope class and retains both state flags. The verifier canonicalizes
that key independently. It first proves every serialized bound against the
actual occurrence IDs in that entry; only then can it use the bound for the
matching orbit key. Missing child states contribute only the universal bound
one. For a disconnected full root, the verifier recomputes each component,
its induced head and its state proof, then takes the maximum. No component
shortcut applies to an arbitrary residual state.

P04 is acceptance-verified. Independent source/proof, differential, corruption
and failure reviews pass, and all 82 tests pass the five-configuration
compiler/sanitizer/clean matrix on identical native inputs. The previous O03
79-test matrix and its fingerprint are historical. See the [P04 verification record](verification/planner-fast-paths-2026-11-06.md).
P06 now supplies owned strict/best-found search, independent replay and distinct
immutable authority; see [continuation contract](planner_continuations.md).

## Verify a certificate

Use the same query document that was used by `tree-oracle`:

```sh
crown verify-height QUERY.json CERT.json [WORK_LIMIT]
```

For example, save an oracle result and extract its certificate with Python's
standard library (no `jq` dependency):

```sh
crown tree-oracle QUERY.json > result.json
python3 - <<'PY'
import json
from pathlib import Path

result = json.loads(Path("result.json").read_text())
if result["height_status"] == "resource_limit" or result["certificate"] is None:
    raise SystemExit("oracle did not produce a completed certificate")
Path("height-certificate.json").write_text(
    json.dumps(result["certificate"], indent=2) + "\n"
)
PY
crown verify-height QUERY.json height-certificate.json
```

The verifier prints JSON with `certificate_valid`, `resource_limit`,
`message`, and `work`. Exit status `0` means verified. Exit status `1` means
the certificate is invalid or verification hit a resource limit; inspect the
two Boolean fields to distinguish those outcomes. Malformed JSON, unknown
fields, duplicate object keys, unsupported versions, and invalid field types
are input errors and exit with status `2`.

The reader and verifier also check conditions that JSON Schema cannot express,
including binding equality, atom-index range and ordering, duplicate states,
the full-query root state, valid tree/query references, the root bound's
agreement with `minimum_height`, and the complete lower-bound replay. The
native reader is authoritative for admission and requires exact integer JSON
tokens; for example, `1.0` is not accepted where an integer is required even
if a schema validator treats that value as an integer.

P06 is acceptance-verified: all 86 tests pass the five-configuration matrix on
one stable native snapshot. Owned input, genuine unit/varied continuation,
strict/best-found authority, independent v1/v2 corruption, persistent same-owner
allocation recovery, zero grants, active-time pause exclusion, logical depth and
lifetime/IO checks pass. Earlier P04/O03 matrices are historical; see the
[current P06 record](verification/planner-continuations-2026-11-06.md).
