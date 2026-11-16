# Canonical query and cache identities

`fingerprint-cq INPUT.json [WORK_LIMIT]` and
`fingerprint-normalized PROGRAM.json [WORK_LIMIT]` produce a complete v1
canonical identity or an explicit resource stop. The normalized input first
passes the [bounded replay reader](schema_evolution.md). Neither command
classifies a query, proves a height, installs a cached plan or starts a runtime.

## Four separate digests

| Field | Content and invalidation |
| --- | --- |
| `semantic_sha256` | Canonical relational structure, every mutable atom, ordered/repeated output positions, constants, types, catalog/source schema versions and arithmetic semantics. For SQL, include local adapters, column classes, parameter signature/values and output/EXISTS semantics. |
| `output_contract_sha256` | Ordered output names and types, including the EXISTS scalar label. Renaming a label preserves relational identity but changes this contract. |
| `cost_inputs_sha256` | Complete source catalog, including statistics and key hints. Cost metadata does not enter semantic identity. |
| `plan_cache_sha256` | All three digests plus arithmetic, planner, optimization and cost-model version identifiers. Statistics/hint changes conservatively invalidate the entire cost-dependent key. |

The supported arithmetic policy is `exact-nonnull-v1`. The other policy fields
are nonempty caller-supplied version identifiers; the default profile uses
`crown-tree-v1`, `structural-height-v1`, `no-cost-v1`. They label cache inputs;
they do not select or implement a new planner. A source-schema/catalog-version
or semantics change alters the semantic identity itself. Runtime data,
initial rows, updates, SQL source text/locations and compile work limits are
excluded from query identity.

The implementation uses independently written SHA-256 according to
[FIPS 180-4](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf), with
known digest vectors and independent Python `hashlib` comparisons. No new
native dependency is required. Each digest hashes this UTF-8 JSON envelope:

```json
{"domain":"crown.query.semantic","version":1,"value":{}}
```

Replace `value` with the complete corresponding payload. Object keys are
lexicographically ordered, with compact separators, exact integer tokens,
unescaped UTF-8 except required JSON escapes and no Unicode normalization.
Dates and decimals use their canonical typed encodings. The other domains
are `crown.query.output`, `crown.query.cost-inputs` and `crown.plan.cache`.
This is CROWN's versioned sorted-JSON encoding, not a claim to implement a
different JSON canonicalization standard.

The C++ compiler/identity entry points serialize their source catalog, query
constants and metadata through JSON. These strings must be serializable UTF-8;
embedded NUL is representable by an escape. Direct storage/runtime values have a
broader binary-byte domain. Catalog/query descriptor validation alone does not
establish JSON serializability. An encoding failure returns no complete identity
or artifact; it is not evidence of tree-class infeasibility. Ordinary compiler
DTO allocation and serialization failures retain their existing exception boundary.

## Intended canonical equivalence

Variable names/IDs, SQL aliases and occurrence labels do not affect semantic
identity. The canonicalizer also erases conjunction/occurrence order within
the same fixed source-catalog snapshot. It preserves all atoms, including
contained/equal scopes and repeated aliases of one physical table. Output
positions and repetition remain meaningful. The output-contract digest
preserves labels separately.

Atoms are colored by physical base ID and local adapter/term structure.
Colors define an invariant ordering. For each equal-color group the search
enumerates all occurrence permutations, relabels variables by first use and
chooses the least complete serialized candidate. This handles self-join
symmetries instead of relying on the textual alias order. Physical source
catalog/table/column order and names are schema identity and stay fixed;
catalog reordering requires its own version/mapping policy.

SQL local expressions replace parser IDs with local column indices and typed
specialized constants. Checked identity/literal casts and lossless integer
widening do not change values; inner USING chooses the left value with its
separate equality. Local AND/OR operands and `=`/`<>` operands
are sorted; AND/OR are flattened; `>`/`>=` become reversed `<`/`<=`.
Non-null source and bounded total-expression rules justify these operations.
General SQL equivalence, atom containment/elimination, distributivity,
predicate implication, functional dependencies and algebraic minimization
are not part of this canonical profile.

Normalized-format-2 constant guards enter this same canonical profile as
typed local equality filters. Its wire-format version is separate from the
identity representation version. Grounding can change variable geometry and
therefore a digest even when a v1→v2 upgrade preserves SQL answers; the
canonical profile does not prove equivalence across every algebraic rewrite.

`occurrence_order` and `variable_order` map canonical positions back to the
original IDs. A future plan-cache consumer must translate and validate the
plan against the actual query; reusing raw IDs would be wrong after a FROM
or variable reordering. Structural certificates continue to use their exact
query binding and independent replay. A matching new digest does not replace
that certificate contract.

## Resource behavior and schemas

Equal-color enumeration can be factorial. `IdentityLimits` defaults to one
million abstract labeling/expression operations. The command accepts an
unsigned work limit or `unlimited`. There is no fixed occurrence/arity mask.
On exhaustion it returns `identity_valid:false`, `status:resource_limit`,
exit 1 and no digest/canonical candidate. It never labels a best-so-far
candidate canonical. Valid complete output uses exit 0; malformed input and
unsupported policies/versions use exit 2 on stderr.

[query-identity-v1.schema.json](../schemas/query-identity-v1.schema.json)
defines complete and resource-stop output. `canonical` contains the full
semantic payload so the digest can be checked independently. The native
hash-table FNV functions remain separate and unchanged. This identity API
does not supply a physical plan cache, runtime checkpoint or authentication.
