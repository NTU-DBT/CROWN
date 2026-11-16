# `tools/verify_imported_workloads.py` — block usage map

[Source](../../../../tools/verify_imported_workloads.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `c11d52326293d04a5c5bf39c693b6710e1e91bfad93083ac350ee546c00c3b9e`. 154 lines partitioned into 13 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../tools/verify_imported_workloads.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 16–17](../../../../tools/verify_imported_workloads.py#L16) | Callable definition: def require(value, message): | calls ValueError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../tools/verify_imported_workloads.py#L18) | Explanatory comments or spacing. |  |
| [B0004 · 20–26](../../../../tools/verify_imported_workloads.py#L20) | Callable definition: def checked(source, entry): | calls PurePosixPath, require, is_absolute, str; guard require(not relative.is_absolute() and '..' not in relative.parts and '\\' not in str(relative), 'u…; returns path · [reviewed contract](#b0004) |
| [B0005 · 27–28](../../../../tools/verify_imported_workloads.py#L27) | Explanatory comments or spacing. |  |
| [B0006 · 29–34](../../../../tools/verify_imported_workloads.py#L29) | Callable definition: def walk(value): | calls isinstance, values; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 35–37](../../../../tools/verify_imported_workloads.py#L35) | Module statements. | source comment (unverified): # This resolver covers the pinned equality-join ASTs, without general SQL scope semantics. · [reviewed contract](#b0007) |
| [B0008 · 38–74](../../../../tools/verify_imported_workloads.py#L38) | Callable definition: def equality_body(ast): | calls walk, get, require, append; guard require(alias not in aliases, 'shadowed alias requires a scoped import review'); returns None; \[field\['String'\]\['sval'\] for field in fields\]; 8 loop sites · [reviewed contract](#b0008) |
| [B0009 · 75–76](../../../../tools/verify_imported_workloads.py#L75) | Explanatory comments or spacing. |  |
| [B0010 · 77–127](../../../../tools/verify_imported_workloads.py#L77) | Callable definition: def verify(source, packet, crown=None): | calls require, checked, read_bytes, get; guard require(packet\['schema_version'\] == 1 and packet\['kind'\] == 'crown_imported_query_inventory', 'unkn…; returns {'source_queries': len(queries), 'original_aggregate_queries': 24, 'acyclic_equality_bodies': 22,; growth new; 9 loop sites · [reviewed contract](#b0010) |
| [B0011 · 128–129](../../../../tools/verify_imported_workloads.py#L128) | Explanatory comments or spacing. |  |
| [B0012 · 130–147](../../../../tools/verify_imported_workloads.py#L130) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, resolve; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 148–154](../../../../tools/verify_imported_workloads.py#L148) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |

## B0001

[Lines 1–15](../../../../tools/verify_imported_workloads.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a source-pinned imported SQL inventory checker with optional native syntax parsing. |
| inputs / outputs | Imports stdlib and independent GYO helper; guarded CLI reads local DynaGox packet. |
| invariants | Preserves original aggregate SQL, no adapted set benchmark or data/license authorization. Optional parse-sql is syntax/shape only, not native R1 admission. |
| ownership | Owns module imports; verification owns parsed source/manifest/AST captures. |
| failure | Import failure visible; explicit require ValueError remains active under -O. |
| cost | Fixed setup; local hash/full source scans and optional24native parse subprocesses later. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 16–17](../../../../tools/verify_imported_workloads.py#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value, message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a false caller-supplied condition in this tool. |
| inputs / outputs | Truth-tested value and diagnostic text in; None on truth, ValueError on false. |
| invariants | Explicit conditional raise remains active under Python -O; this is a local assertion of the stated predicate, not native/proof validation. |
| ownership | Borrows condition/message; exception retains message until released. |
| failure | Raises ValueError at the caller check before subsequent operations; does not catch or undo earlier IO. |
| cost | O(truth conversion) plus exception construction only on failure; arbitrary user-defined __bool__ is outside these primitive callers. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 20–26](../../../../tools/verify_imported_workloads.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def checked(source, entry):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a manifest member's relative containment and exact raw-file SHA. |
| inputs / outputs | Source root and entry {path,sha256} in; constructed source-relative Path out after resolved containment/existence checks. |
| invariants | Rejects absolute/.. and resolved escape; SHA binds exact bytes, not imported query semantics or license. |
| ownership | Owns Path and full read_bytes/hash temporary; source file unchanged. |
| failure | ValueError on path/hash predicates; file/IO/type/OOM errors propagate. |
| cost | Path resolution/stat plus O(file bytes) complete read/hash. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 29–34](../../../../tools/verify_imported_workloads.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def walk(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Yield every nested dict in a parsed imported SQL AST/JSON graph. |
| inputs / outputs | Dict/list/scalar in; recursive iterator yielding dict objects including root. |
| invariants | Traverses representation values, not SQL lexical scopes; equality_body explicitly rejects alias shadowing. |
| ownership | Yields aliases to original dicts; recursive generator frames retain graph paths. |
| failure | Recursion/type/OOM failure propagates; no mutation. |
| cost | O(graph nodes) traversal and O(depth) generator stack. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0007

[Lines 35–37](../../../../tools/verify_imported_workloads.py#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L37:sha256:ae61eecaa75bd4adcff8dbaecea25f42979d685c75490ff40b23bf79cca97bd2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: This resolver covers the pinned equality-join ASTs, without general SQL scope semantics. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [docs/code_review.md](../../../code_review.md) |

## B0008

[Lines 38–74](../../../../tools/verify_imported_workloads.py#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def equality_body(ast):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify the pinned imported AST's column-equality join body using independent GYO reduction. |
| inputs / outputs | Parsed libpg_query AST in; occurrence (alias,table) order and Boolean acyclicity out. |
| invariants | Collects RangeVars, forbids alias shadowing, resolves known table-prefix columns, unions only column=column. Not general SQL scope/filter/aggregate equivalence or native admission. |
| ownership | Owns alias/order/prefix/union-find/scope maps and sets; AST borrowed unchanged. |
| failure | ValueError on unsupported/ambiguous names or shadowing; malformed AST/OOM propagate. |
| cost | Two recursive whole-AST walks, union-find/path compression and scope construction, then independent GYO subset scans; no SQL execution. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def column(node):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract a supported plain ColumnRef name path from the imported AST. |
| inputs / outputs | AST node in; None for noncolumn or fresh list of String.sval components. |
| invariants | Every field must be String; wildcard/other reference forms reject rather than guessed resolution. |
| ownership | Owns component list; immutable name values borrowed. |
| failure | ValueError on unsupported reference; malformed keys/type/OOM propagate. |
| cost | O(reference components) scan/copy, fixed small for pinned queries. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def resolve(names):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve imported one/two-part column names against fixed alias/prefix conventions. |
| inputs / outputs | Name component list in; alias.column string out. |
| invariants | Two-part alias must exist; unqualified name must match exactly one known table prefix. Rejects other lengths/ambiguity, no general SQL name resolver. |
| ownership | Owns choices list and combined string; alias metadata borrowed. |
| failure | ValueError on unknown/ambiguous/unsupported names; type/OOM propagate. |
| cost | O(aliases) prefix scan for unqualified names, O(name bytes) concatenation. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def find(name):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return/create a union-find representative with path-halving compression. |
| inputs / outputs | Qualified column string in; representative string out, captured parent dict mutated. |
| invariants | Used only for equality join variables; compression changes internal accounting graph, not source AST. |
| ownership | Parent map retains names; returns aliased immutable name. |
| failure | Hash/OOM or malformed cyclic internal map errors propagate; fixed callers create valid forest. |
| cost | Amortized union-find traversal/compression for admitted use, plus dict operations; no claimed engine update bound. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0010

[Lines 77–127](../../../../tools/verify_imported_workloads.py#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def verify(source, packet, crown=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify24 verbatim imported aggregate query definitions and unavailable-data/license boundaries. |
| inputs / outputs | Source root, packet and optional crown Path in; source/query/classification counts out. |
| invariants | Requires exact repo/commit/document Git blobs, SQL labels/order/text,22acyclic/2cyclic metadata and all queries/data native-ineligible. Optional parse preserves SQL/aggregates and independently compares occurrences/equality-body classification; not benchmark reproduction. |
| ownership | Owns source document texts, regex matches/query snippets and optional native AST/captures; packet/source borrowed. |
| failure | ValueError on pin/semantic/scope discrepancy; parse subprocess60s, nonzero/stderr rejects, IO/JSON/errors propagate. |
| cost | Hash/read/scan all pinned docs/24SQL files and metadata; optionally24 full captured parse processes plus AST/GYO checks, no query execution/timing. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0012

[Lines 130–147](../../../../tools/verify_imported_workloads.py#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the imported-source audit and four controlled metadata rejection cases. |
| inputs / outputs | --source/--manifest plus optional --crown in; prints finite summary after verify and four deep-clone corruption checks. |
| invariants | Negative controls must raise ValueError; source queries remain verbatim/unavailable for native timing. |
| ownership | Owns manifest and mutant deep copies; original packet retained unchanged. |
| failure | Unexpected accepted mutant raises ValueError; ordinary errors reach script wrapper. |
| cost | Full verify plus repeated manifest copies/reverification for selected corruptions; optional native parses per actual branch. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0013

[Lines 148–154](../../../../tools/verify_imported_workloads.py#L148); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the imported-source audit only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | Exception prints B02 imported-source diagnostic and exits1; no file/source mutation or rollback. |
| cost | Fixed error formatting plus full main. |
| Design | [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/dynagox/manifest.json](../../../../benchmarks/legacy/dynagox/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
