# Structural tree plans (schema version 1)

`crown validate-plan QUERY.cq.json PLAN.tree.json` checks a supplied CROWN tree
against the catalog and query in a version-1 CQ document. The command reads the
catalog and query from the first file and the plan from the second. It does not
construct or optimize a plan, run SQL, or execute the query.

The plan's local JSON shape is described by
[`tree-v1.schema.json`](../schemas/tree-v1.schema.json). The CROWN reader also
checks constraints that JSON Schema cannot express across files: duplicate
object keys, unique node IDs, valid root/child/connex references, known
variables and atom occurrences, exact native scopes, schema versions, and a
matching catalog version. Unknown keys are rejected at every plan-object
level.

## Plan document

The required top-level fields are:

| Field | Meaning |
| --- | --- |
| `schema_version` | Must be integer `1`. |
| `catalog_version` | Positive uint64 equal to `catalog.version` in the CQ document. |
| `semantics` | Must be `"set"`, matching the CQ document. |
| `root` | Nonempty node ID for a nonempty tree; `null` only with an empty `nodes` array. |
| `nodes` | Array of tree nodes. A nonempty query must cover its atom occurrences with native nodes. |

Optional top-level claims are `connex`, an array of node IDs claiming a
root-connected output subtree, and `native_height`, a nonnegative integer
claiming the native height. The checker verifies either claim; neither changes
the structure it checks.

Each node has a nonempty `id`, `kind`, `scope`, and `children`:

- `kind` is `"native"` or `"generalized"`.
- `scope` is an array of unique query variable names and may be empty. A
  native node must include its **complete normalized atom scope**, including
  variables that are not in the query head; it cannot be reduced to a selected
  projection.
- `children` is an array of child node IDs. References must resolve and the
  nodes must form one rooted tree.
- A native node must have `occurrence`, the ID of the CQ atom it represents.
  Every atom occurrence must appear exactly once. A generalized node must not
  have `occurrence`.
- Either kind may include `separator`, a unique-variable array claiming the
  intersection with its parent's scope. The root's actual separator is empty.

The reader rejects unknown keys, duplicate JSON object keys, duplicate node
IDs, repeated scope entries, unknown node/variable/occurrence references, and
incompatible schema or catalog versions. The schema gives the local JSON
shape; the query-aware reader and verifier remain authoritative.

## What is checked

The verifier independently checks that every atom occurrence is covered once,
leaves are native, and node scopes use known query variables. It checks the
tree topology and that, for each variable, the nodes containing it induce a
connected subtree. Every generalized node's scope must be contained in every
child scope, and no generalized node may be below a native node. These are the
cover, topology, connect, guard, and above checks.

For the output-connectivity check, the verifier computes the maximal set
`C*`: start at the root and traverse only edges whose separator contains no
variable outside the query head. The scopes in `C*` must cover the full head.
This check depends on the query projection even though the body and node tree
may be unchanged. Optional `separator` and `native_height` claims must match
the exact computed values. A claimed `connex` subtree may be smaller than
`C*`; it must independently contain the root, be parent-connected, cross only
output separators, and cover the head. It need not equal the maximal set.

Generalized nodes with one child are accepted when the checks pass. Contracting
them is a planner normal-form step, not a validity requirement for this
checker.

## Example: two-edge path with a generalized root

For the query `Q(x,y,z) :- R(x,y), S(y,z)`, save this full CQ document as
`path.cq.json`:

```json
{
  "schema_version": 1,
  "semantics": "set",
  "catalog": {
    "version": 1,
    "tables": [
      {"name": "R", "columns": [{"name": "c0", "type": "string"}, {"name": "c1", "type": "string"}]},
      {"name": "S", "columns": [{"name": "c0", "type": "string"}, {"name": "c1", "type": "string"}]}
    ]
  },
  "query": {
    "variables": [
      {"name": "x", "type": "string"},
      {"name": "y", "type": "string"},
      {"name": "z", "type": "string"}
    ],
    "atoms": [
      {"id": "r", "table": "R", "terms": [{"var": "x"}, {"var": "y"}]},
      {"id": "s", "table": "S", "terms": [{"var": "y"}, {"var": "z"}]}
    ],
    "head": [{"var": "x"}, {"var": "y"}, {"var": "z"}]
  }
}
```

Save this plan as `path.tree.json`:

```json
{
  "schema_version": 1,
  "catalog_version": 1,
  "semantics": "set",
  "root": "g",
  "nodes": [
    {"id": "g", "kind": "generalized", "scope": ["y"], "children": ["r_node", "s_node"]},
    {"id": "r_node", "kind": "native", "scope": ["x", "y"], "children": [], "occurrence": "r"},
    {"id": "s_node", "kind": "native", "scope": ["y", "z"], "children": [], "occurrence": "s"}
  ]
}
```

Run:

```sh
crown validate-plan path.cq.json path.tree.json
```

The report is valid with `native_height: 1` and `edge_depth: 1`. Native height
maximizes the number of native nodes over root-to-leaf paths; edge depth
independently maximizes the number of edges. Those maxima can come from
different paths. Here each root-to-leaf path contains the generalized root and
one native child, so it has one native node and one edge. The computed maximal
connex set is `["g", "r_node", "s_node"]`, because both separators are
`["y"]` and all three query variables are in the head.

Now keep the same body and plan, but project the query to head `[x,z]`. The
separator `[y]` is no longer contained in the head, so traversal from `g`
cannot enter either native child. Then `C*` contains only `g` and covers
neither `x` nor `z`; the plan fails the `connex` rule. The output projection
can therefore invalidate a tree that was valid for the full-head query.

For an empty-body constant query, the empty plan is exactly `root: null` and
`nodes: []`; it has native height `0` and edge depth `0`. A claimed height may
be written as `"native_height": 0`.

## Report and exit status

A validation report contains `schema_version`, `tree_valid`, `native_height`,
`edge_depth`, `height_status`, `maximal_connex`, `separators`, and `violations`.
On a valid plan, heights are integers and `height_status` is
`"valid_upper_bound"`. On a structurally invalid plan, both heights are
`null` and the status is `"invalid"`. Each separator entry has `node` and
`variables`; each violation has `rule` and `message`, plus any applicable
`node`, `variable`, `occurrence`, or `related_node` witness.
Separators and maximal-connex nodes are left empty when invalid topology
prevents the corresponding traversal.

Exit codes are `0` for a valid tree, `1` for a structurally invalid tree with
the report on stdout, and `2` for malformed or incompatible input with a JSON
error on stderr. A successful report certifies only that the supplied tree is
valid and its native height is an upper bound on the minimum. It does not
certify height optimality, an execution plan, or runtime/SQL behavior. The
execution-plan and canonical-query-hash certificate work tracked by F05 is
still pending.
