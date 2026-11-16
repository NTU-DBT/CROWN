# `tools/generate_adversarial_workloads.py` — block usage map

[Source](../../../../tools/generate_adversarial_workloads.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `61aa0ebbf123f47e57104c81fa4cd1fbcfc1d1e9f194650cb1655967ee2fc3cc`. 239 lines partitioned into 11 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../tools/generate_adversarial_workloads.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 27–66](../../../../tools/generate_adversarial_workloads.py#L27) | Callable definition: def churn_case(family, scale): | calls in, query, range, len; returns spec, events, dict(family=family, scale_selector=scale, axis='history_cycles',; growth insert; 13 loop sites · [reviewed contract](#b0002) |
| [B0003 · 67–68](../../../../tools/generate_adversarial_workloads.py#L67) | Explanatory comments or spacing. |  |
| [B0004 · 69–117](../../../../tools/generate_adversarial_workloads.py#L69) | Callable definition: def case(family, scale): | calls startswith, query, range, update; returns churn_case(family, scale); spec, events, dimensions; growth insert; 14 loop sites · [reviewed contract](#b0004) |
| [B0005 · 118–119](../../../../tools/generate_adversarial_workloads.py#L118) | Explanatory comments or spacing. |  |
| [B0006 · 120–133](../../../../tools/generate_adversarial_workloads.py#L120) | Callable definition: def live_counts(events): | calls defaultdict, Counter, tuple, add; returns counts, sum(peaks.values()); growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 134–135](../../../../tools/generate_adversarial_workloads.py#L134) | Explanatory comments or spacing. |  |
| [B0008 · 136–212](../../../../tools/generate_adversarial_workloads.py#L136) | Callable definition: def build(seed=20261114, scale=1, selected=None): | calls ValueError, list, len, set; returns {'path': path, 'sha256': sha(files\[path\])}; files; 9 loop sites · [reviewed contract](#b0008) |
| [B0009 · 213–214](../../../../tools/generate_adversarial_workloads.py#L213) | Explanatory comments or spacing. |  |
| [B0010 · 215–235](../../../../tools/generate_adversarial_workloads.py#L215) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, build; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 236–239](../../../../tools/generate_adversarial_workloads.py#L236) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |

## B0001

[Lines 1–26](../../../../tools/generate_adversarial_workloads.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the finite synthetic B05 workload profile and direct-script entry. |
| inputs / outputs | Import defines the module and checks its checkout relationship; direct execution parses output, seed, scale, family and check choices. |
| invariants | The B02 helper module supplies shared oracle behavior. Import does not write a pack; generation starts only through build() or main(). |
| ownership | Module owns the family tuple and ordinary Python intermediates; no native runtime owner is created. |
| failure | Import, checkout-comparison ValueError and delegated helper errors propagate; there is no module-level catch. |
| cost | Fixed import/definition work. Pack generation and writes are described by build()/main(). |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
from generate_workloads import (BACKENDS, OUTPUT_MODES, ROOT, acyclic, canonical,
                                oracle, query, sha, verify_regime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse B02 query, ordering, regime and independent oracle primitives for B05. |
| inputs / outputs | Imports shared backend/mode constants, root, query/acyclic helpers, canonical JSON, SHA, regime validator and epoch oracle. |
| invariants | Executes trusted sibling Python definitions; its guarded pack CLI remains inactive. This is not a sandbox. |
| ownership | Imported module/functions remain in Python module state; oracle results are ordinary temporary values. |
| failure | Import, compilation and helper failures propagate. |
| cost | Loads one module and dependencies; per-case oracle cost occurs later. |
| Design | [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
if ROOT != Path(__file__).resolve().parents[1]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a B05 generator loaded beside a B02 oracle from a different checkout. |
| inputs / outputs | Compare imported ROOT with this file’s repository parent; mismatch raises ValueError at import. |
| invariants | Binds helper and generator to one resolved path only; it does not attest source bytes or build lineage. |
| ownership | Path metadata only; no native or file owner. |
| failure | Mismatch raises ValueError; path resolution errors propagate. |
| cost | One path comparison at import. |
| Design | [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
FAMILIES = (
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | List the exact 19 family names accepted by the finite B05 profile, including six churn shapes. |
| inputs / outputs | Immutable tuple used by build() selection and CLI choices. |
| invariants | Unknown and duplicate names are rejected in build(); a suite label alone does not add a family. |
| ownership | Module-owned constant tuple. |
| failure | Constant construction can fail on import/allocation; name validation occurs in build(). |
| cost | Fixed tuple storage and bounded membership checks. |
| Design | [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [docs/measurement.md](../../../measurement.md), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0002

[Lines 27–66](../../../../tools/generate_adversarial_workloads.py#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def churn_case(family, scale):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one of six fixed-live-set histories for singleton, projected, star, path or self-join queries. |
| inputs / outputs | Churn family and scale in; typed query, ordered load/insert/delete/sentinel/drain/empty events and axes out. |
| invariants | History cycles are 16*scale². Each shape has fixed live rows, at most one transient row and a distinct-churn-row count; per-table high-water is computed separately from global live population. |
| ownership | Returns ordinary Python query/events/axes; no native source/runtime owner. |
| failure | Unknown non-churn family enters the self-join branch if called directly; build() restricts names. Helper/oracle/allocation failures propagate. |
| cost | Creates finite events per cycle and initial/drain rows; no native execution. |
| Design | [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/measurement.md](../../../measurement.md), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0004

[Lines 69–117](../../../../tools/generate_adversarial_workloads.py#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def case(family, scale):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one family’s typed query, ordered events and explicit experiment axes. |
| inputs / outputs | Registered family and finite scale in; query specification, event list and dimensions out. |
| invariants | Volume, fan-out, skew, arity and path use separate formulas; every churn family delegates to churn_case(). Histories keep their shape-specific live window fixed, add at most one transient row, probe no-ops, then drain. |
| ownership | Returns ordinary Python data; it retains no native source/query state. |
| failure | Malformed input/helper/allocation failures propagate; no external pack is written here. |
| cost | Constructs finite query metadata, row values and ordered events; it does not execute either oracle. build() evaluates the per-epoch oracle later. |
| Design | [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/measurement.md](../../../measurement.md), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0006

[Lines 120–133](../../../../tools/generate_adversarial_workloads.py#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def live_counts(events):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute per-epoch physical live population and the sum of per-table live high-water marks. |
| inputs / outputs | Ordered events in; (population list, integer sum of table peaks) out. |
| invariants | Maintains a set per table; duplicate insert/absent delete leave population unchanged. The summed per-table peak is a reference for fixed-slot-reuse analysis, not a native slot observation. |
| ownership | Owns a dict of table-specific Python sets, a per-table high-water map and a result list; unrelated to native arena state. |
| failure | Unpacking, hashing or allocation errors propagate; malformed event semantics are not checked here. |
| cost | For each event, updates one set/high-water and sums live sizes across tables: O(events * tables + tuple hashing), with retained row sets and one total per event. This is generator work. |
| Design | [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0008

[Lines 136–212](../../../../tools/generate_adversarial_workloads.py#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def build(seed=20261114, scale=1, selected=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one reproducible B02-format B05 pack as an in-memory path-to-bytes map. |
| inputs / outputs | Seed, scale and selected family names plus read-only source assets in; path-to-bytes map out. Reads benchmarks/legacy/manifest.json, benchmarks/external_imports.json, tools/generate_workloads.py and its own source to bind the generated provenance. main() performs pack writes. |
| invariants | Checks both shared oracles, analytic final cardinality, regime and the 4096-event ceiling. Seed is recorded provenance; this profile makes no random choices. axes.json also records source_slot_reuse_reference as sum of per-table live high-waters; this is a generator-side reference, not a measured arena slot count. free_connex requires both body alpha-acyclicity and augmented H+F alpha-acyclicity; the full-head triangle remains false despite an acyclic augmentation. |
| ownership | Returned dict owns generated bytes and ordinary Python/SQLite intermediates; no native query account is involved. |
| failure | Invalid selector/profile, oracle disagreement, cardinality/horizon mismatch, source-asset read or allocation errors propagate before pack-directory creation. |
| cost | Constructs each selected case and per-epoch relational/SQLite oracles, serializes generated files in memory, and reads/hashes the named source assets. Cost follows event/output volume, oracle work and asset bytes; no native process or output writes. |
| Design | [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [docs/measurement.md](../../../measurement.md), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0010

[Lines 215–235](../../../../tools/generate_adversarial_workloads.py#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose fresh pack generation and exact existing-byte check through the CLI. |
| inputs / outputs | --output required; finite seed/scale defaults; repeatable named --query; --check compares the complete existing file map. |
| invariants | Without --check output must be new. Check mode reads files and does not write. Successful path prints family count and scale. |
| ownership | Process owns args/generated map; destination filesystem retains written pack. |
| failure | Argparse/build/compare/mkdir/write errors propagate; sequential writes may leave a partial fresh directory. |
| cost | Builds pack, then either reads/compares all files or writes them sequentially. |
| Design | [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0011

[Lines 236–239](../../../../tools/generate_adversarial_workloads.py#L236); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the pack CLI only on direct script execution. |
| inputs / outputs | Main-name guard delegates to main(); import leaves pack generation unstarted. |
| invariants | Imports and repository-root validation still execute on import. |
| ownership | Process owns argparse/files; wrapper creates no separate owner. |
| failure | Delegated errors use normal traceback/exit; no catch is added. |
| cost | One guard and delegated CLI work. |
| Design | [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |
