# `tools/run_search_evaluation.py` — block usage map

[Source](../../../../tools/run_search_evaluation.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `c8cb1446ce6c387b5b315fb6ec8f046d3a8f2344c32974774f807412348e58b9`. 343 lines partitioned into 21 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../tools/run_search_evaluation.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 22–24](../../../../tools/run_search_evaluation.py#L22) | Callable definition: def save(path, value, exclusive=False): | calls open, write, dumps · [reviewed contract](#b0002) |
| [B0003 · 25–26](../../../../tools/run_search_evaluation.py#L25) | Explanatory comments or spacing. |  |
| [B0004 · 27–53](../../../../tools/run_search_evaluation.py#L27) | Callable definition: def cohorts(): | calls add, sorted, str, range; returns result; 14 loop sites · [reviewed contract](#b0004) |
| [B0005 · 54–55](../../../../tools/run_search_evaluation.py#L54) | Explanatory comments or spacing. |  |
| [B0006 · 56–61](../../../../tools/run_search_evaluation.py#L56) | Callable definition: def request(case, method, work, proof_work): | calls ; returns {'schema_version': 1, 'command': 'verify', 'method': method, 'work_limit': work, · [reviewed contract](#b0006) |
| [B0007 · 62–63](../../../../tools/run_search_evaluation.py#L62) | Explanatory comments or spacing. |  |
| [B0008 · 64–83](../../../../tools/run_search_evaluation.py#L64) | Callable definition: def score_tree(case, tree): | calls enumerate, set, pop, require; guard require(node_id in nodes and node_id not in visited, 'invalid/repeated reported tree node'); returns Fraction(numerator, denominator), max(depths.values()); 6 loop sites · [reviewed contract](#b0008) |
| [B0009 · 84–85](../../../../tools/run_search_evaluation.py#L84) | Explanatory comments or spacing. |  |
| [B0010 · 86–106](../../../../tools/run_search_evaluation.py#L86) | Callable definition: def inspect(case, ask, report, source_path): | calls require, digest, all, values; guard require(report\['kind'\] == 'b04_finite_search_record_v1' and report\['schema_version'\] == 1 and; returns scores; 5 loop sites · [reviewed contract](#b0010) |
| [B0011 · 107–108](../../../../tools/run_search_evaluation.py#L107) | Explanatory comments or spacing. |  |
| [B0012 · 109–118](../../../../tools/run_search_evaluation.py#L109) | Callable definition: def outcome(report): | calls get; returns report\['algorithm'\]\['status'\]; report\['status'\] · [reviewed contract](#b0012) |
| [B0013 · 119–120](../../../../tools/run_search_evaluation.py#L119) | Explanatory comments or spacing. |  |
| [B0014 · 121–137](../../../../tools/run_search_evaluation.py#L121) | Callable definition: def semantic_identity(report): | calls get, outcome, sorted; returns {'status': report\['status'\], 'outcome': outcome(report),; 3 loop sites · [reviewed contract](#b0014) |
| [B0015 · 138–139](../../../../tools/run_search_evaluation.py#L138) | Explanatory comments or spacing. |  |
| [B0016 · 140–177](../../../../tools/run_search_evaluation.py#L140) | Callable definition: def compare(case, records): | calls get, append, require, len; guard require(reference is None or reference == current, 'complete reference families differ across budge…; returns rows; 8 loop sites · [reviewed contract](#b0016) |
| [B0017 · 178–179](../../../../tools/run_search_evaluation.py#L178) | Explanatory comments or spacing. |  |
| [B0018 · 180–327](../../../../tools/run_search_evaluation.py#L180) | Callable definition: def run(args): | calls resolve, require, startswith, hasattr; guard require(1 &lt;= args.repetitions &lt;= 20 and 0 &lt;= args.warmups &lt;= 5 and 1 &lt;= args.command_timeout &lt;= 360…; returns path; experiment.invoke(label, argv); 33 loop sites · [reviewed contract](#b0018) |
| [B0019 · 328–329](../../../../tools/run_search_evaluation.py#L328) | Explanatory comments or spacing. |  |
| [B0020 · 330–338](../../../../tools/run_search_evaluation.py#L330) | Callable definition: def main(): | calls ArgumentParser, add_argument, run, parse_args; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 339–343](../../../../tools/run_search_evaluation.py#L339) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |

## B0001

[Lines 1–21](../../../../tools/run_search_evaluation.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:4eaf8d1abed64c785ab21fac15d455d9a6b0e234a539bab3a717714ce1862f27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the offline finite-search driver and reuse established exact arithmetic, provenance and subprocess measurement helpers. |
| inputs / outputs | Imports Python CLI/JSON/time/hash modules, exact Fraction and existing Experiment/build/environment/ratio/canonical primitives; lists all five required methods. |
| invariants | Import performs no native command. No method aliases CLI tree-oracle to the literal reference; no engine or C05 policy is modified. |
| ownership | Module definitions and constants only; all file/process owners are created inside explicit functions. |
| failure | Missing helper imports stop the script instead of falling back to an unverified protocol. |
| cost | Cold interpreter import only; native clocks/RSS are recorded later per child. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0002

[Lines 22–24](../../../../tools/run_search_evaluation.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L24:sha256:95b5ec33882cbb8f3633a84069ca4cf7e4ab409e7ea52a3f42f0352b5b788a5d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a new frozen JSON document or update only a task-local progress checkpoint. |
| inputs / outputs | Path, JSON-compatible value and exclusive flag produce sorted indented JSON plus newline. |
| invariants | Frozen queries/requests/manifests/proofs use x mode; experiment progress intentionally uses w only within its freshly created directory. |
| ownership | Local stream context owns the file handle until close; the caller retains JSON ownership. |
| failure | Existing exclusive file, serialization, write/close and disk errors propagate; no overwrite recovery. |
| cost | Cold JSON serialization and disk bytes scale with the document; these are host driver costs, outside native phase clocks. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0004

[Lines 27–53](../../../../tools/run_search_evaluation.py#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L53:sha256:19a66e993abdfb0e88a0cc4ecd22c7b13e5af5a201bc4fa623c9d400cea2a0a2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare all23 deterministic source cases rather than hand-coded optimizer outputs. |
| inputs / outputs | Four typed-CQ shape families for native counts2..6 plus tiny C02, cyclic and physical-alias cases yield fresh documents and per-table training repetition counts. |
| invariants | All documents have empty initial state/no updates, set semantics and no asserted height/proof. Alias case has repeated occurrences of one physical table. All shapes/sizes remain scheduled regardless of later stops/infeasibility. |
| ownership | Returns owning nested Python dictionaries/lists; no data file or runtime owner is shared with a previous study. |
| failure | Construction/allocation errors stop setup; no difficult shape is omitted based on algorithm results. |
| cost | Small fixed setup proportional to23 declared cases; does not execute or predict native algorithms. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0006

[Lines 56–61](../../../../tools/run_search_evaluation.py#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L61:sha256:fe55ded5fad77a634a265f6819d108fe248d7c8184380cfa0c711f2b91b65075
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the explicit finite request for one method/work control. |
| inputs / outputs | Case, named method, method work and shared proof work produce all fourteen required request fields. |
| invariants | Retains separately named producer, memory, record/cell/depth/scope/output and rank caps. Declared physical repetition counts come only from the fixed case, not measured winners. |
| ownership | Returns fresh request mapping; training list is borrowed read-only until exclusive JSON serialization. |
| failure | Native receiver validates types/ranges and unknown fields; this helper never manufactures a fallback grant on resource stop. |
| cost | Constant-size request construction plus the finite table vector. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0008

[Lines 64–83](../../../../tools/run_search_evaluation.py#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L83:sha256:ce810a3ea476cb3f397ecc62ce9b257aaf35c24a71d10ef62c3a97c448342858
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently calculate actual-tree native height and declared-input weighted native depth. |
| inputs / outputs | Case source and emitted tree produce exact Fraction score and maximum native depth. |
| invariants | Checks unique/reachable nodes and exactly one native occurrence per source atom. Every native occurrence receives its physical table repetition count, including aliases. Generalized nodes add zero. It never constructs native Evidence or grants P02 authority. |
| ownership | Uses local node/atom/table maps, stack, visited/depth dictionaries; input JSON remains unchanged. |
| failure | Foreign/repeated/missing nodes or occurrences reject. Fixed cases guarantee a positive training denominator; malformed score inputs propagate. |
| cost | Linear traversal/indexing in emitted source/tree size plus exact integer arithmetic. Separate cold independent arithmetic, not a latency model. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0010

[Lines 86–106](../../../../tools/run_search_evaluation.py#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L106:sha256:78f83cf89871c42b8de83e8e6518e904dd4371dad813348d4f4f7f3f576cef69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Join every successful child report to its exact source/request and independently check published heights and C02 arithmetic. |
| inputs / outputs | Case, ask, report and query path produce a structural-key-to-Fraction score map after protocol/hash/dimension checks. |
| invariants | Verify timers must be null; published actual native height equals genuine original h*. Actual C02 event horizon, per-table insert/erase census, exact scores and key tie-breaking must match independently computed depth arithmetic. |
| ownership | Borrows files/JSON and returns a fresh scalar map; holds no native Candidate/Evidence handle. |
| failure | Any source/request/key/height/census/score mismatch aborts. Explicit scoring-unavailability remains distinct from an available zero score. |
| cost | Hashes source bytes and traverses each retained candidate tree; cold verification before timing and after every measured child. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0012

[Lines 109–118](../../../../tools/run_search_evaluation.py#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L109-L118:sha256:0fe0f6916977c3c65bf5b611e5e41a5f0edb13a84d6c1c930ee76ce83a77a2da
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify the actual reported outcome without dropping finite resource prefixes. |
| inputs / outputs | One native report becomes minimum/infeasible/resource/unavailable/literal-cap/empty-prefix/complete-declared-scope/retained-prefix label. |
| invariants | Only combined upstream+provider exhaustion earns complete_declared_scope. An empty retained family is explicit; caller metadata does not prove global exhaustion. |
| ownership | Borrows report and returns a scalar label. |
| failure | Malformed required native fields reject; no success default or missing-status substitution. |
| cost | Constant-size cold classification. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0014

[Lines 121–137](../../../../tools/run_search_evaluation.py#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L137:sha256:200066f934c67257b7b332278be745294f99657cbfefe13523418bf5d330ba07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the deterministic semantic boundary between verify and measure invocations. |
| inputs / outputs | One report yields source-result/height, original/residual/candidate/meta stop data, actual reference signatures/exhaustion and C02 scores/availability/reasons. |
| invariants | Ignores elapsed clocks while preserving decisions, published family and score identity. A measured child cannot silently change availability, stop kind, height or retained trees. |
| ownership | Returns new outer containers borrowing immutable native report values for immediate equality, with a fresh sorted signature list. |
| failure | Missing mandatory fields reject in direct lookup; mismatches are rejected by run instead of substituted or retried. |
| cost | Cold extraction plus sort in retained candidate count; not included in native call timers. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0016

[Lines 140–177](../../../../tools/run_search_evaluation.py#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L140-L177:sha256:8aa31d3907990fde48c9e9b3bed2359090b48eb862d5e7bfb0096caa01b956fe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare independent completed decisions and tiny normalized-family/scoring quality while retaining every other outcome. |
| inputs / outputs | All successful reports for one case yield per-method/budget comparison rows, exact coverage and C02 selected-score gap when a complete independent reference exists. |
| invariants | Every completed literal/P06 minimum or infeasibility must agree. Only completed tiny normalized reference permits subset/coverage and optimum claims; optimized/meta complete scope must match it. Partial reference or larger capped queries get null quality authority, not inferred completeness. |
| ownership | Builds fresh signature/decision/score collections and comparison dictionaries; source report JSON is borrowed and unchanged. |
| failure | Disagreeing decisions/families or a normalized tree outside complete reference reject. Stops/infeasibility/unavailable rows remain visible rather than shrinking the case set. |
| cost | Cold finite family set operations and exact rational comparisons. C02 gaps use structural units, never nanoseconds or C03 prediction errors. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0018

[Lines 180–327](../../../../tools/run_search_evaluation.py#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L327:sha256:9c3cfe4a3b20408ae9afec5487209238cf64836fcb0cf4f79c167cb63b9bb144
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the bounded all-method correctness gate and optional deterministic controlled search schedule with complete cold input/build closure. |
| inputs / outputs | Resolved CLI paths/grants produce one exclusively created study directory containing exact source/query/request/case manifests, raw commands/reports, wireproofs, comparisons, outcomes, runs and summaries. |
| invariants | Linux wait4 required; timing needs explicit allowed CPU. All23cases and all5methods/budgets remain declared. Every variant first verifies; genuine serialized original certificates replay through crown. Source/request/case templates are frozen and hashed before native consumption, rechecked per measured child/end. End also verifies actual build files, compiled sources/objects/dependency records/transitive dependencies/compiler/launchers and harness. Unexpected external failures retain raw rows and prevent timing; native bounded stops remain eligible actual outcomes. Warmups are retained/excluded. |
| ownership | Fresh directory owns all study files. Experiment waits and accounts each child. Native owners live only in subprocesses; Python retains parsed owning JSON and immutable filenames/hashes. Frozen inputs include each proof added before replay. |
| failure | Refuse existing output, invalid grants/CPU, stale build/input, wrong proof/family/scoring or end-closure changes. External timeout/resource errors are preserved without retry or dropped variants; fatal checks checkpoint failed state then propagate. |
| cost | Each child reruns/charges its real proof and training. Named call clocks differ from whole-process wall/RSS; RSS includes startup/source/proof/output/capture, not planner-only memory. Schedule is bounded&lt;=10000 estimated commands. No equal-work CPU claim, speedup, global cost theorem, all-input proof or full ten-axis B04 acceptance. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0020

[Lines 330–338](../../../../tools/run_search_evaluation.py#L330); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L330-L338:sha256:1ae1bfb97caebfbb316d1c0f6981ed77b02ac1f711e5e949c1641f492dcebce0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse the finite public study CLI and dispatch one run. |
| inputs / outputs | Six required source/build/executable/output paths and explicit case/work/proof/repetition/CPU/timeout/byte/preflight flags produce the argument DTO. |
| invariants | All five methods are fixed, budgets explicit, no option supplies fabricated heights/Evidence or excludes failed cases based on results. |
| ownership | ArgumentParser owns scalar/Path/list arguments; run owns processes and output files. |
| failure | Unknown/malformed flags fail argparse; semantic grants/CPU/source checks happen in run before directory creation. |
| cost | Cold CLI parsing only; no engine setup or native command during parser definition. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |

## B0021

[Lines 339–343](../../../../tools/run_search_evaluation.py#L339); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L339-L343:sha256:fadd581cead14d78c10f2169c4ec51e65f005066ee91577e02c2ac7e823cd7ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report one terminal driver error without retry machinery. |
| inputs / outputs | __main__ invokes main; a propagated exception prints the finite-study diagnostic to stderr and exits1. |
| invariants | Importing this module for cold tests never starts native work. Success is printed only after terminal packet/end-closure checks. |
| ownership | No subprocess/query owner persists here; Experiment/run scopes own and release them. |
| failure | Failure is nonzero; already-written raw failure/checkpoint evidence is retained. |
| cost | Process entry/exit and ordinary Python exception reporting only. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [docs/planner_proofs.md](../../../planner_proofs.md), [docs/residual_candidates.md](../../../residual_candidates.md), [docs/meta_candidate_adapter.md](../../../meta_candidate_adapter.md), [docs/ranking.md](../../../ranking.md), [tests/reference/tree_oracle.cpp](../../../../tests/reference/tree_oracle.cpp), [tests/reference/candidate_set.cpp](../../../../tests/reference/candidate_set.cpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2#page=3), [exact paper reference](https://arxiv.org/html/2603.14754v1), [exact paper reference](https://arxiv.org/html/2603.15465v2) |
