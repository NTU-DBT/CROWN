# `tools/generate_ranking_evaluation.py` — block usage map

[Source](../../../../tools/generate_ranking_evaluation.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `e31d230f09395d47f088c93e19799b1be0958561369103f6819d4d1ad921cedf`. 114 lines partitioned into 9 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../tools/generate_ranking_evaluation.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 20–21](../../../../tools/generate_ranking_evaluation.py#L20) | Callable definition: def require(value,message): | calls ValueError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../tools/generate_ranking_evaluation.py#L22) | Callable definition: def sha(value):return hashlib.sha256(value).hexdigest() | calls sha256, hexdigest; returns hashlib.sha256(value).hexdigest() · [reviewed contract](#b0003) |
| [B0004 · 23–37](../../../../tools/generate_ranking_evaluation.py#L23) | Callable definition: def rows_for(spec,seed,split_index,fanout): | calls set, update, enumerate, require; guard require(atom\['table'\] not in result,'C07 generator currently requires distinct physical tables'); returns result; 3 loop sites; source comment (unverified): # Distinct value domains, including separator keys, make physical tuples · [reviewed contract](#b0004) |
| [B0005 · 38–53](../../../../tools/generate_ranking_evaluation.py#L38) | Callable definition: def make_trace(spec,seed,split_index,fanout,hot_index): | calls rows_for, list, items, sort; guard require(len(events)&lt;=4096,'C07 event grant exceeded'); returns pools,events; growth insert; 6 loop sites; source comment (unverified): # Exact input attempts include no-ops; they are not silently discarded from · [reviewed contract](#b0005) |
| [B0006 · 54–96](../../../../tools/generate_ranking_evaluation.py#L54) | Callable definition: def build(seed=20261111,selected=None): | calls require, isinstance, len, set; guard require(isinstance(seed,int) and not isinstance(seed,bool) and 0&lt;=seed&lt;2**32,'invalid split seed'); returns {'path':path,'sha256':sha(data),'bytes':len(data)}; files; 13 loop sites · [reviewed contract](#b0006) |
| [B0007 · 97–103](../../../../tools/generate_ranking_evaluation.py#L97) | Callable definition: def verify(source,pack): | calls loads, read_text, require, build; guard manifest=json.loads((pack/'manifest.json').read_text());require(manifest\['schema_version'\]==1 and m…; returns manifest,{'queries':len(manifest\['queries'\]),'traces':len(manifest\['traces'\]),'physical_events':sum…; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 104–111](../../../../tools/generate_ranking_evaluation.py#L104) | Callable definition: def main(): | calls ArgumentParser, add_argument, add_mutually_exclusive_group, parse_args; returns files=build(args.seed,args.query); 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 112–114](../../../../tools/generate_ranking_evaluation.py#L112) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |

## B0001

[Lines 1–19](../../../../tools/generate_ranking_evaluation.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the finite C07 disjoint-trace generator and independent-oracle dependencies. |
| inputs / outputs | Loads stdlib and generate_workloads helpers, defines ROOT, three query IDs and five train/calibration/evaluation scenarios; main is guarded. |
| invariants | sys.dont_write_bytecode is changed process-wide before sibling imports. Defaults describe one deterministic split, not query-family holdout or independent statistical replicates. |
| ownership | Module owns lists/tuples/strings/Path and imported modules; ordinary Python allocations, outside native query accounting. |
| failure | Import/encoding/IO/OOM failures propagate before CLI guard can catch import failures. |
| cost | Fixed registry/import setup; later build performs full synthetic generation and relational/SQLite scans. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
ROOT=Path(__file__).resolve().parents[1]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Locate the generator source root used for oracle and self-source hashes. |
| inputs / outputs | Resolved __file__.parents\[1\] Path retained; verify compares supplied source against it. |
| invariants | Root identity is a path check, not a reproducible-build certificate. |
| ownership | Module owns Path; no directory snapshot retained. |
| failure | Path/resolve failures propagate during import. |
| cost | Path resolution only; no recursive source scan here. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
DEFAULT_QUERIES=['boolean_path','full_star_3','composite_separator']
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fix the three C07 query families admitted by the generator. |
| inputs / outputs | DEFAULT_QUERIES list read by build/default main. |
| invariants | Subset selection must be nonempty, unique and contained here; SQL families are shared across splits. |
| ownership | Owning mutable list of strings; build does not mutate it. |
| failure | Construction/OOM on import; invalid selection rejected later. |
| cost | Three-element allocation and later small membership/set work. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
SCENARIOS=[('train','train',3,0),('calibration','calibration',4,0),
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the five split roles, fanouts and hot-table selectors. |
| inputs / outputs | Scenario tuples read in fixed order by build. |
| invariants | Index controls disjoint offset domains; rate shift changes relation mix, not wall-clock Hz. |
| ownership | Owning list with immutable tuple/scalar entries. |
| failure | No validation in declaration; build relies on fixed valid tuples. |
| cost | Five tuples; downstream event/oracle work is not incurred at declaration. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 20–21](../../../../tools/generate_ranking_evaluation.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value,message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a false caller-supplied condition in this tool. |
| inputs / outputs | Truth-tested value and diagnostic text in; None on truth, ValueError on false. |
| invariants | Explicit conditional raise remains active under Python -O; this is a local assertion of the stated predicate, not native/proof validation. |
| ownership | Borrows condition/message; exception retains message until released. |
| failure | Raises ValueError at the caller check before subsequent operations; does not catch or undo earlier IO. |
| cost | O(truth conversion) plus exception construction only on failure; arbitrary user-defined __bool__ is outside these primitive callers. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 22–22](../../../../tools/generate_ranking_evaluation.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sha(value):return hashlib.sha256(value).hexdigest()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute SHA256 for supplied encoded bytes. |
| inputs / outputs | Bytes-compatible input; lowercase SHA256 hex output; no file IO here. |
| invariants | Digest binds exact bytes supplied, including line endings and literal spelling; it does not attest semantic correctness or build lineage. |
| ownership | Input borrowed during hashing; hash state and hex result owned. |
| failure | Invalid input/type/OOM failure propagates. |
| cost | O(input bytes) hash and fixed-size result allocation. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 23–37](../../../../tools/generate_ranking_evaluation.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def rows_for(spec,seed,split_index,fanout):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct physically disjoint, separator-aware finite row pools for one split. |
| inputs / outputs | Spec, seed, split index and positive fixed scenario fanout in; table-&gt;ordered unique tuple list out. |
| invariants | Requires distinct physical tables; split offset and fixed variable positions define domains for the admitted three specs. Separator-only rows may collapse under set semantics. |
| ownership | Owns hot-variable set, result dict and tuple/list rows; spec is borrowed, unchanged. |
| failure | Duplicate table raises ValueError before return; bad variable/layout inputs or allocation errors propagate with partial local pools discarded. |
| cost | Visits sum(fanout+atom index) candidate rows×arity; variables.index adds linear variable search per cell; dict.fromkeys allocates dedup map and output list. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0005

[Lines 38–53](../../../../tools/generate_ranking_evaluation.py#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def make_trace(spec,seed,split_index,fanout,hot_index):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build charged-load, hot-relation, within-trace shift and committed no-op attempts. |
| inputs / outputs | Admitted spec/seed/split/fanout/hot-index in; owning pools and ordered (operation,table,row,phase) events out. |
| invariants | Loads from empty; includes16 hot delete/reinsert pairs,4 shift pairs and8 duplicate inserts. Event count is capped4096 after construction; no-op attempts remain part of the horizon. |
| ownership | Owns pools, flattened entries, SHA sorting keys, event tuples and copied row lists; returned pools/events share only immutable scalar elements. |
| failure | Bad hot index/empty pools propagate; grant violation raises after allocation; no files published. |
| cost | Pool construction plus sorting all rows by SHA/canonical JSON, repeated selected-pool sort, and O(events×arity) row copies; cap is post-construction. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 54–96](../../../../tools/generate_ranking_evaluation.py#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def build(seed=20261111,selected=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize a complete deterministic C07 pack with disjoint trace evidence and two independent result oracles. |
| inputs / outputs | Strict non-bool uint32 seed and nonempty unique allowed IDs in; path-&gt;UTF8 file bytes including manifest out. |
| invariants | Each split has disjoint (table,row) domains and distinct semantic trace hashes; all loading/no-ops charged. Training/calibration/evaluation metadata is a local protocol, not a theorem or unseen-query test. |
| ownership | Deep-copies each chosen spec; owns all files, manifests, events, repeated oracle snapshots and disjointness sets simultaneously until return. |
| failure | ValueError rejects seed/selection/domain/hash conditions; oracle/IO/JSON/OOM propagate before any pack output directory is created by main. |
| cost | Five traces per query; full relational joins and SQLite query after every event dominate; set intersections, SHA/JSON scans and retention of all encoded files add peak memory. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def put(path,value,raw=False):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one generated C07 member and bind its exact output bytes in metadata. |
| inputs / outputs | Captured files dict plus relative path/value/raw flag in; stores bytes and returns path/SHA256/byte count. |
| invariants | Paths are fixed trusted generator literals; repeated path would overwrite captured dict, no exclusive check inside helper. |
| ownership | Owns UTF8 bytes and metadata dict; raw text and nonraw graph borrowed until encoding finishes. |
| failure | Encoding/JSON/type/OOM errors stop build before disk writes. |
| cost | O(member bytes) JSON/UTF8 allocation plus hashing; retains each full encoded member. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0007

[Lines 97–103](../../../../tools/generate_ranking_evaluation.py#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def verify(source,pack):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the complete C07 pack and compare exact bytes, including extras. |
| inputs / outputs | Source Path and existing pack Path in; manifest and finite validation summary out. |
| invariants | Requires schema_version1/kind; builds from embedded seed/query selection, compares all rglob files exactly, then checks source.resolve()==ROOT. It does not merely trust manifest hashes. |
| ownership | Owns parsed manifest, complete regenerated files and complete actual-file byte dict concurrently; returned manifest retained by caller. |
| failure | IO/JSON/generator errors propagate; mismatched bytes or root raise ValueError, with no pack mutation. |
| cost | Full deterministic generation/oracles plus recursive pack read/hash summary; peak includes two complete packs and oracle intermediates. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0008

[Lines 104–111](../../../../tools/generate_ranking_evaluation.py#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check an existing C07 pack or create a fresh output directory from generated bytes. |
| inputs / outputs | argparse --seed/--query and exactly one --output/--check; prints result or generated file count. |
| invariants | Build/check happens before new output mkdir; new root uses exist_ok=False. Sequential writes are not an atomic multi-file publication and do not fsync. |
| ownership | Owns parsed args and all build bytes; filesystem retains files on success or partial write failure. |
| failure | Argparse exits for invalid usage; generation/IO failures reach script wrapper; partial newly created outputs are not rolled back. |
| cost | Full build or verify cost, then O(total bytes) directory/file writes or summary JSON serialization. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0009

[Lines 112–114](../../../../tools/generate_ranking_evaluation.py#L112); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the C07 generator only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | Catches Exception from main, prints text to stderr and exits1; SystemExit/KeyboardInterrupt pass through. No pack cleanup or rollback. |
| cost | Entry call plus one error-format/print only on failure; no native job unless future imported helpers change, current generator uses SQLite only. |
| Design | [tools/generate_ranking_evaluation.py](../../../../tools/generate_ranking_evaluation.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [docs/ranking_evaluation.md](../../../ranking_evaluation.md), [benchmarks/ranking/manifest.json](../../../../benchmarks/ranking/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
