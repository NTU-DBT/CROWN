# `tests/observability/cli/native_cli_acceptance.py` — block usage map

[Source](../../../../../../tests/observability/cli/native_cli_acceptance.py) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3e486cb3121027ad909d02e531446609b9305db90db4bf178ee33b0fb2c4279b`. 1213 lines partitioned into 74 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../../code_review.md), [docs/reference_fuzz.md](../../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–36](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 37–37](../../../../../../tests/observability/cli/native_cli_acceptance.py#L37) | Explanatory comments or spacing. |  |
| [B0003 · 38–39](../../../../../../tests/observability/cli/native_cli_acceptance.py#L38) | Callable definition: def sha256_bytes(value: bytes) -&gt; str: | calls sha256, hexdigest; returns hashlib.sha256(value).hexdigest() · [reviewed contract](#b0003) |
| [B0004 · 40–41](../../../../../../tests/observability/cli/native_cli_acceptance.py#L40) | Explanatory comments or spacing. |  |
| [B0005 · 42–47](../../../../../../tests/observability/cli/native_cli_acceptance.py#L42) | Callable definition: def sha256_file(path: Path) -&gt; str: | calls sha256, open, iter, read; returns digest.hexdigest(); 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 48–49](../../../../../../tests/observability/cli/native_cli_acceptance.py#L48) | Explanatory comments or spacing. |  |
| [B0007 · 50–51](../../../../../../tests/observability/cli/native_cli_acceptance.py#L50) | Callable definition: def json_bytes(value: Any) -&gt; bytes: | calls dumps, encode; returns (json.dumps(value, ensure_ascii=False, indent=2) + "\n").encode("utf-8") · [reviewed contract](#b0007) |
| [B0008 · 52–53](../../../../../../tests/observability/cli/native_cli_acceptance.py#L52) | Explanatory comments or spacing. |  |
| [B0009 · 54–56](../../../../../../tests/observability/cli/native_cli_acceptance.py#L54) | Callable definition: def read_json(path: Path) -&gt; Any: | calls open, load; returns json.load(stream) · [reviewed contract](#b0009) |
| [B0010 · 57–58](../../../../../../tests/observability/cli/native_cli_acceptance.py#L57) | Explanatory comments or spacing. |  |
| [B0011 · 59–64](../../../../../../tests/observability/cli/native_cli_acceptance.py#L59) | Callable definition: def inside(path: Path, root: Path) -&gt; bool: | calls relative_to; returns True; False · [reviewed contract](#b0011) |
| [B0012 · 65–66](../../../../../../tests/observability/cli/native_cli_acceptance.py#L65) | Explanatory comments or spacing. |  |
| [B0013 · 67–68](../../../../../../tests/observability/cli/native_cli_acceptance.py#L67) | Callable definition: def safe_name(value: str) -&gt; str: | calls sub, strip; returns re.sub(r"\[^A-Za-z0-9_.-\]+", "_", value).strip("_") or "item" · [reviewed contract](#b0013) |
| [B0014 · 69–81](../../../../../../tests/observability/cli/native_cli_acceptance.py#L69) | declares types or opens a type body. |  · [reviewed contract](#b0014) |
| [B0015 · 82–95](../../../../../../tests/observability/cli/native_cli_acceptance.py#L82) | Callable definition: def __init__(self, repo: Path, native_cli: Path, schema_dir: Path, | calls resolve · [reviewed contract](#b0015) |
| [B0016 · 96–96](../../../../../../tests/observability/cli/native_cli_acceptance.py#L96) | Explanatory comments or spacing. |  |
| [B0017 · 97–103](../../../../../../tests/observability/cli/native_cli_acceptance.py#L97) | Callable definition: def check(self, condition: bool, label: str, detail: str = "") -&gt; None: | calls append, AssertionError; guard def check(self, condition: bool, label: str, detail: str = "") -&gt; None: · [reviewed contract](#b0017) |
| [B0018 · 104–104](../../../../../../tests/observability/cli/native_cli_acceptance.py#L104) | Explanatory comments or spacing. |  |
| [B0019 · 105–113](../../../../../../tests/observability/cli/native_cli_acceptance.py#L105) | Callable definition: def setup_output(self) -&gt; None: | calls Path, resolve, inside, check; guard self.check(allowed, "output directory is under /tmp or build/verification", str(self.outputdir)) · [reviewed contract](#b0019) |
| [B0020 · 114–114](../../../../../../tests/observability/cli/native_cli_acceptance.py#L114) | Explanatory comments or spacing. |  |
| [B0021 · 115–119](../../../../../../tests/observability/cli/native_cli_acceptance.py#L115) | Callable definition: def out(self) -&gt; Path: | calls RuntimeError; returns self.run_dir · [reviewed contract](#b0021) |
| [B0022 · 120–120](../../../../../../tests/observability/cli/native_cli_acceptance.py#L120) | Explanatory comments or spacing. |  |
| [B0023 · 121–169](../../../../../../tests/observability/cli/native_cli_acceptance.py#L121) | Callable definition: def verify_frozen_inputs(self) -&gt; dict\[str, Path\]: | calls read_json, get, check, isinstance; guard self.check(isinstance(files, dict) and bool(files), "test readiness has a closed file-hash map"); returns schema_paths; 2 loop sites · [reviewed contract](#b0023) |
| [B0024 · 170–170](../../../../../../tests/observability/cli/native_cli_acceptance.py#L170) | Explanatory comments or spacing. |  |
| [B0025 · 171–202](../../../../../../tests/observability/cli/native_cli_acceptance.py#L171) | Callable definition: def prepare_schemas(self, schema_paths: dict\[str, Path\]) -&gt; None: | calls catch_warnings, simplefilter, RuntimeError, items; guard self.check(set(self.validators) == {"report", "tree", "query", "witness"},; returns store\[uri\]; 2 loop sites · [reviewed contract](#b0025) |
| [B0026 · 203–203](../../../../../../tests/observability/cli/native_cli_acceptance.py#L203) | Explanatory comments or spacing. |  |
| [B0027 · 204–212](../../../../../../tests/observability/cli/native_cli_acceptance.py#L204) | Callable definition: def input_hashes(self, inputs: dict\[str, Path\]) -&gt; dict\[str, dict\[str, Any\]\]: | calls sorted, items, resolve, is_file; returns result; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 213–213](../../../../../../tests/observability/cli/native_cli_acceptance.py#L213) | Explanatory comments or spacing. |  |
| [B0029 · 214–254](../../../../../../tests/observability/cli/native_cli_acceptance.py#L214) | Callable definition: def invoke(self, name: str, argv: list\[str\], inputs: dict\[str, Path\], expected_rc: int, | calls len, safe_name, mkdir, input_hashes; guard self.check(returncode == expected_rc, f"CLI exit status: {name}", f"expected {expected_rc}, got {re…; returns invocation · [reviewed contract](#b0029) |
| [B0030 · 255–255](../../../../../../tests/observability/cli/native_cli_acceptance.py#L255) | Explanatory comments or spacing. |  |
| [B0031 · 256–260](../../../../../../tests/observability/cli/native_cli_acceptance.py#L256) | Callable definition: def generated(self, relative: str, data: Any) -&gt; Path: | calls mkdir, write_bytes, json_bytes; returns path · [reviewed contract](#b0031) |
| [B0032 · 261–261](../../../../../../tests/observability/cli/native_cli_acceptance.py#L261) | Explanatory comments or spacing. |  |
| [B0033 · 262–274](../../../../../../tests/observability/cli/native_cli_acceptance.py#L262) | Callable definition: def report_schema(self, report: Any, label: str) -&gt; None: | calls list, iter_errors, AssertionError, check; guard self.check(True, f"offline V2 report schema accepts {label}") · [reviewed contract](#b0033) |
| [B0034 · 275–275](../../../../../../tests/observability/cli/native_cli_acceptance.py#L275) | Explanatory comments or spacing. |  |
| [B0035 · 276–284](../../../../../../tests/observability/cli/native_cli_acceptance.py#L276) | Callable definition: def tree_schema(self, tree: Any, label: str) -&gt; None: | calls list, iter_errors, AssertionError, check; guard self.check(True, f"offline V2 tree schema accepts {label}") · [reviewed contract](#b0035) |
| [B0036 · 285–285](../../../../../../tests/observability/cli/native_cli_acceptance.py#L285) | Explanatory comments or spacing. |  |
| [B0037 · 286–306](../../../../../../tests/observability/cli/native_cli_acceptance.py#L286) | Callable definition: def validate_export(self, format_name: str, invocation: Invocation, label: str, | calls isinstance, AssertionError, report_schema, tree_schema; guard self.check(bool(text), f"{label}: {format_name} export is nonempty"); returns invocation.parsed_json; invocation.parsed_json; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 307–307](../../../../../../tests/observability/cli/native_cli_acceptance.py#L307) | Explanatory comments or spacing. |  |
| [B0039 · 308–310](../../../../../../tests/observability/cli/native_cli_acceptance.py#L308) | Callable definition: def variable_ids(document: dict\[str, Any\]) -&gt; dict\[str, int\]: | calls enumerate; returns {entry\["name"\]: index for index, entry in enumerate(document\["query"\]\["variables"\])}; 1 loop sites · [reviewed contract](#b0039) |
| [B0040 · 311–311](../../../../../../tests/observability/cli/native_cli_acceptance.py#L311) | Explanatory comments or spacing. |  |
| [B0041 · 312–314](../../../../../../tests/observability/cli/native_cli_acceptance.py#L312) | Callable definition: def occurrence_ids(document: dict\[str, Any\]) -&gt; dict\[str, int\]: | calls enumerate; returns {entry\["id"\]: index for index, entry in enumerate(document\["query"\]\["atoms"\])}; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 315–315](../../../../../../tests/observability/cli/native_cli_acceptance.py#L315) | Explanatory comments or spacing. |  |
| [B0043 · 316–389](../../../../../../tests/observability/cli/native_cli_acceptance.py#L316) | Callable definition: def compare_tree(self, report: dict\[str, Any\], plan: dict\[str, Any\], case: dict\[str, Any\]) -&gt; None: | calls variable_ids, occurrence_ids, enumerate, check; guard self.check(child not in parent_by_id, f"{case_id}: actual P08 tree has at most one parent", child); 16 loop sites · [reviewed contract](#b0043) |
| [B0044 · 390–390](../../../../../../tests/observability/cli/native_cli_acceptance.py#L390) | Explanatory comments or spacing. |  |
| [B0045 · 391–458](../../../../../../tests/observability/cli/native_cli_acceptance.py#L391) | Callable definition: def compare_physical_report(self, report: dict\[str, Any\], plan: dict\[str, Any\], case: dict\[str, Any\]) -&gt; None: | calls check, in, join, list; guard self.check(report\["schema_version"\] == 2 and report\["artifact"\] == "crown_explain" and; 6 loop sites · [reviewed contract](#b0045) |
| [B0046 · 459–459](../../../../../../tests/observability/cli/native_cli_acceptance.py#L459) | Explanatory comments or spacing. |  |
| [B0047 · 460–524](../../../../../../tests/observability/cli/native_cli_acceptance.py#L460) | Callable definition: def run_physical_families(self) -&gt; list\[dict\[str, Any\]\]: | calls read_json, check, bool, safe_name; guard self.check(bool(cases), "lowering manifest contains valid physical plan cases"); returns results; 2 loop sites · [reviewed contract](#b0047) |
| [B0048 · 525–525](../../../../../../tests/observability/cli/native_cli_acceptance.py#L525) | Explanatory comments or spacing. |  |
| [B0049 · 526–621](../../../../../../tests/observability/cli/native_cli_acceptance.py#L526) | Callable definition: def schema_mutations(self, physical: dict\[str, Any\], session: dict\[str, Any\], query: dict\[str, Any\], | calls mutate, deepcopy, append, check; guard self.check(not validator.is_valid(document), f"V2 schema rejects {label}"); returns {"v2_report_rejected": len(mutations) + observation_mutations,; 4 loop sites · [reviewed contract](#b0049) |
| [B0050 · 622–622](../../../../../../tests/observability/cli/native_cli_acceptance.py#L622) | Explanatory comments or spacing. |  |
| [B0051 · 623–678](../../../../../../tests/observability/cli/native_cli_acceptance.py#L623) | Callable definition: def proof_cases(self, fixture: dict\[str, Any\], other_fixture: dict\[str, Any\]) -&gt; dict\[str, Any\]: | calls invoke, str, isinstance, get; guard self.check(report\["height_evidence"\]\["status"\] == "verified_original_minimum",; returns a certificate"); {"matching": "verified_original_minimum", "wrong_query": "rejected", · [reviewed contract](#b0051) |
| [B0052 · 679–679](../../../../../../tests/observability/cli/native_cli_acceptance.py#L679) | Explanatory comments or spacing. |  |
| [B0053 · 680–738](../../../../../../tests/observability/cli/native_cli_acceptance.py#L680) | Callable definition: def session_input(self, plan: dict\[str, Any\]) -&gt; Path: | calls get, append, dumps, encode; returns path; growth insert; 6 loop sites · [reviewed contract](#b0053) |
| [B0054 · 739–739](../../../../../../tests/observability/cli/native_cli_acceptance.py#L739) | Explanatory comments or spacing. |  |
| [B0055 · 740–906](../../../../../../tests/observability/cli/native_cli_acceptance.py#L740) | Callable definition: def run_runtime_and_sessions(self, fixture: dict\[str, Any\]) -&gt; dict\[str, Any\]: | calls str, invoke, isinstance, AssertionError; guard self.check(runtime\["kind"\] == "runtime" and runtime\["mode"\]\["runtime_presence"\] == "live",; returns {"runtime_reports": 4, "session_pending_reports": 1,; 5 loop sites · [reviewed contract](#b0055) |
| [B0056 · 907–907](../../../../../../tests/observability/cli/native_cli_acceptance.py#L907) | Explanatory comments or spacing. |  |
| [B0057 · 908–917](../../../../../../tests/observability/cli/native_cli_acceptance.py#L908) | Callable definition: def triangle_infeasible(self) -&gt; Path: | calls range, in, generated; returns self.generated("query/triangle-full-head-infeasible.cq.json", document); 3 loop sites · [reviewed contract](#b0057) |
| [B0058 · 918–918](../../../../../../tests/observability/cli/native_cli_acceptance.py#L918) | Explanatory comments or spacing. |  |
| [B0059 · 919–995](../../../../../../tests/observability/cli/native_cli_acceptance.py#L919) | Callable definition: def run_query_forms(self, fixture: dict\[str, Any\], progress_fixture: dict\[str, Any\]) -&gt; dict\[str, Any\]: | calls invoke, str, report_schema, check; guard self.check(admitted\["kind"\] == "query" and admitted\["query_explanation"\]\["source"\] == "exact_search…; returns {"admitted": admitted, "partial": partial, "optimum": optimum, "infeasible": impossible, · [reviewed contract](#b0059) |
| [B0060 · 996–996](../../../../../../tests/observability/cli/native_cli_acceptance.py#L996) | Explanatory comments or spacing. |  |
| [B0061 · 997–1031](../../../../../../tests/observability/cli/native_cli_acceptance.py#L997) | Callable definition: def invalid_cli_cases(self, fixture: dict\[str, Any\]) -&gt; int: | calls mkdir, write_bytes, str, invoke; guard self.check(call.stdout == b"", f"invalid CLI invocation has empty stdout: {name}"); returns len(cases); 1 loop sites · [reviewed contract](#b0061) |
| [B0062 · 1032–1032](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1032) | Explanatory comments or spacing. |  |
| [B0063 · 1033–1057](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1033) | Callable definition: def format_byte_limits(self, artifacts: dict\[str, tuple\[list\[str\] \| dict\[str, list\[str\]\], | calls items, isinstance, invoke, validate_export; guard self.check(length &gt; 0, f"{artifact_name}/{fmt}: baseline encoding is nonempty"); returns result; 2 loop sites · [reviewed contract](#b0063) |
| [B0064 · 1058–1058](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1058) | Explanatory comments or spacing. |  |
| [B0065 · 1059–1104](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1059) | Callable definition: def escaped_label_fixture(self) -&gt; dict\[str, Any\]: | calls generated, invoke, str, report_schema; guard self.check(report\["structure"\]\["selected_tree"\]\["nodes"\]\[0\]\["label"\] == node_label,; returns {"node_label": node_label, "occurrence": occurrence, "graphviz_render_parse": "not performed"}; 3 loop sites · [reviewed contract](#b0065) |
| [B0066 · 1105–1105](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1105) | Explanatory comments or spacing. |  |
| [B0067 · 1106–1159](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1106) | Callable definition: def run(self) -&gt; dict\[str, Any\]: | calls setup_output, verify_frozen_inputs, prepare_schemas, run_physical_families; guard self.check(True, "standalone V1 query schema accepts emitted exact-search optimum"); returns {; 3 loop sites · [reviewed contract](#b0067) |
| [B0068 · 1160–1160](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1160) | Explanatory comments or spacing. |  |
| [B0069 · 1161–1176](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1161) | Callable definition: def finish(self, status: str, result: dict\[str, Any\] \| None, error: str \| None = None, | calls len, sum, write_bytes, json_bytes; returns record = {; 2 loop sites · [reviewed contract](#b0069) |
| [B0070 · 1177–1178](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1177) | Explanatory comments or spacing. |  |
| [B0071 · 1179–1196](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1179) | Callable definition: def parse_args() -&gt; argparse.Namespace: | calls ArgumentParser, add_argument, package, Path; returns args; 1 loop sites · [reviewed contract](#b0071) |
| [B0072 · 1197–1198](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1197) | Explanatory comments or spacing. |  |
| [B0073 · 1199–1209](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1199) | Callable definition: def main() -&gt; int: | calls parse_args, Harness, run, finish; returns 1; 0 · [reviewed contract](#b0073) |
| [B0074 · 1210–1213](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1210) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0074) |

## B0001

[Lines 1–36](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define an offline acceptance entry point and its explicit process/file dependencies. |
| inputs / outputs | Caller-supplied native executable and fixture paths; actual campaign is started only by module entry guard. |
| invariants | Source review is not a new execution result. Existing v14 campaign evidence is historical; this packet adds no runtime instrumentation. |
| ownership | Python module owns imported bindings, source constants and helper definitions; native ownership is exercised only in child processes. |
| failure | Import/dependency/encoding failures can precede the main diagnostic boundary. |
| cost | Import/definition and later explicit test work only; no production query cost. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0003

[Lines 38–39](../../../../../../tests/observability/cli/native_cli_acceptance.py#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sha256_bytes(value: bytes) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash supplied bytes for evidence identity. |
| inputs / outputs | Bytes to SHA256 hex. |
| invariants | No file read or text normalization. |
| ownership | Borrows bytes; owns hex string. |
| failure | Hash/type/allocation failure propagates. |
| cost | Linear in byte length with fixed digest state. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0005

[Lines 42–47](../../../../../../tests/observability/cli/native_cli_acceptance.py#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sha256_file(path: Path) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash an evidence file in bounded read chunks. |
| inputs / outputs | Path to SHA256 hex. |
| invariants | Reads binary 1 MiB blocks until EOF; no source modification. |
| ownership | Context manager owns descriptor; chunk buffers and digest state remain local. |
| failure | Open/read/allocation failures propagate. |
| cost | Linear file bytes; fixed-size 1 MiB reads and bounded chunk-buffer storage. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0007

[Lines 50–51](../../../../../../tests/observability/cli/native_cli_acceptance.py#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def json_bytes(value: Any) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode readable UTF8 JSON evidence with final newline. |
| inputs / outputs | JSON value to bytes. |
| invariants | Preserves insertion order and Unicode, using two-space indentation. |
| ownership | Owns JSON text and encoded-byte temporaries. |
| failure | Serialization/encoding/allocation failures propagate. |
| cost | Whole-value serialization with temporary text and byte buffers. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0009

[Lines 54–56](../../../../../../tests/observability/cli/native_cli_acceptance.py#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def read_json(path: Path) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load one explicitly UTF8 JSON document. |
| inputs / outputs | Path to decoded Python object. |
| invariants | Does not independently validate schema or reject duplicate object keys. |
| ownership | File descriptor closes; decoded tree is owned by caller. |
| failure | IO/Unicode/JSON failures propagate. |
| cost | Full parse and JSON tree allocation. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0011

[Lines 59–64](../../../../../../tests/observability/cli/native_cli_acceptance.py#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def inside(path: Path, root: Path) -> bool:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test lexical containment of already resolved paths. |
| inputs / outputs | Path and root to boolean. |
| invariants | relative_to catches only non-containment ValueError; this helper itself does not resolve or prevent later symlink races. |
| ownership | Borrows immutable Paths. |
| failure | Non-containment returns false; other failures propagate. |
| cost | Path-component comparison and relative-Path creation. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0013

[Lines 67–68](../../../../../../tests/observability/cli/native_cli_acceptance.py#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def safe_name(value: str) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make a nonempty filename label from arbitrary test text. |
| inputs / outputs | Text to sanitized label. |
| invariants | ASCII letter/digit/dot/dash/underscore retained; runs of other characters become underscore. Collisions are possible; invocation ordinal provides uniqueness. |
| ownership | Owns regex result. |
| failure | Regex/type/allocation failures propagate. |
| cost | Linear label scan and result allocation. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0014

[Lines 69–81](../../../../../../tests/observability/cli/native_cli_acceptance.py#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Invocation:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a completed CLI call and its saved evidence location. |
| inputs / outputs | Name/path/status/raw streams/optional parsed JSON fields. |
| invariants | Dataclass is mutable; bytes are Python-owned, not native borrowed memory. |
| ownership | Record retains both streams and parsed tree until harness release. |
| failure | Construction/allocation failures propagate. |
| cost | Metadata plus retained full outputs; no fixed global memory cap. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

```text
class Harness:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Coordinate offline black-box EXPLAIN acceptance and retain all evidence. |
| inputs / outputs | Resolved repository/binary/schema/fixture/output paths to mutable runner. |
| invariants | Checks actual selected CLI; pinned fixture/schema package is distinct from optional binary pin. No native build or maintained-source edit occurs. |
| ownership | Owns checks, invocations, validators, hash records and a Path naming the unique persistent output directory; it holds no open directory descriptor. |
| failure | Methods fail fast; main attempts a recorded failed summary after exceptions. |
| cost | Many subprocesses plus retained output/JSON/evidence IO; no native-resource or runtime-complexity guarantee. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0015

[Lines 82–95](../../../../../../tests/observability/cli/native_cli_acceptance.py#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def __init__(self, repo: Path, native_cli: Path, schema_dir: Path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize resolved test inputs and empty owned evidence collections. |
| inputs / outputs | Paths and optional expected CLI digest to fresh Harness. |
| invariants | Does not create output, validate files or launch native code. |
| ownership | Owns resolved Paths, mutable lists/maps and optional pin string. |
| failure | Path resolution/allocation errors propagate before main run boundary. |
| cost | Fixed metadata initialization plus filesystem path resolution. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0017

[Lines 97–103](../../../../../../tests/observability/cli/native_cli_acceptance.py#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check(self, condition: bool, label: str, detail: str = "") -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one assertion before raising on failure. |
| inputs / outputs | Condition, label and optional detail to stored check record. |
| invariants | Failed assertion remains in checks for finish; successful record also consumes storage. |
| ownership | Harness owns immutable strings and mutable record dict. |
| failure | False raises AssertionError after append. |
| cost | Constant append/branch plus supplied diagnostic text. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0019

[Lines 105–113](../../../../../../tests/observability/cli/native_cli_acceptance.py#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def setup_output(self) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a unique acceptance run beneath an allowed output root. |
| inputs / outputs | Configured outputdir to fresh run_dir. |
| invariants | Resolved output must be at or below /tmp or this repository build/verification; this policy is a harness path rule, not a security sandbox. |
| ownership | Owns parent/run Paths; saved directory intentionally persists. |
| failure | Invalid location or mkdir failure aborts; may leave created parent directory. |
| cost | Path checks and two mkdir operations with time/PID/UUID label creation. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0021

[Lines 115–119](../../../../../../tests/observability/cli/native_cli_acceptance.py#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def out(self) -> Path:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require initialized output directory before writing evidence. |
| inputs / outputs | Harness to run_dir Path. |
| invariants | No directory creation or validation occurs in property getter. |
| ownership | Returns retained immutable Path handle. |
| failure | Unset run_dir raises RuntimeError. |
| cost | Constant access/branch. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0023

[Lines 121–169](../../../../../../tests/observability/cli/native_cli_acceptance.py#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def verify_frozen_inputs(self) -> dict[str, Path]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate readiness file map, selected fixture copies, schemas and CLI identity. |
| inputs / outputs | Pinned package/selected paths to four schema Paths and hash_record. |
| invariants | Package hash derives sorted closed map; CLI hash is checked only if caller supplied a pin. This does not authenticate a trusted binary origin. |
| ownership | Owns decoded readiness, complete hash maps and schema Paths. |
| failure | Missing/hash-mismatched files or malformed metadata fail before CLI cases. |
| cost | Reads/hashes all listed package files and selected copies plus binary; canonical map serialization allocates. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0025

[Lines 171–202](../../../../../../tests/observability/cli/native_cli_acceptance.py#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def prepare_schemas(self, schema_paths: dict[str, Path]) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create four offline-only Draft202012 validators. |
| inputs / outputs | Verified schema Paths to retained schemas/validators. |
| invariants | file/http/https handlers reject references outside the preloaded four-schema store; no network fallback intended. |
| ownership | Owns schema trees, store, resolver closures and validators. |
| failure | ImportError becomes actionable RuntimeError; schema/reference failures propagate. |
| cost | Parses/checks four schemas and builds resolver state; ordinary Python heap work. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

```text
def local_file(uri: str) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve only a preloaded file-schema URI. |
| inputs / outputs | URI to exact stored schema object. |
| invariants | Unknown file URI is rejected rather than read from filesystem. |
| ownership | Returns shared mutable Python schema object retained by store. |
| failure | Unknown URI raises RuntimeError. |
| cost | Average constant dictionary lookup. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

```text
def deny_network(uri: str) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject HTTP/HTTPS schema resolution. |
| inputs / outputs | URI to unconditional failure. |
| invariants | No network operation occurs in this handler. |
| ownership | Uses URI only in diagnostic. |
| failure | Always raises RuntimeError. |
| cost | Diagnostic construction and exception unwind only. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0027

[Lines 204–212](../../../../../../tests/observability/cli/native_cli_acceptance.py#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def input_hashes(self, inputs: dict[str, Path]) -> dict[str, dict[str, Any]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record existing or absent per-invocation inputs. |
| inputs / outputs | Label/Path map to sorted path/existence/raw-hash records. |
| invariants | This is a pre-call observation; it does not assert files remain unchanged during a child call. |
| ownership | Owns resolved Paths/metadata; file hashing is chunked. |
| failure | Filesystem races or unreadable files propagate. |
| cost | Sorts labels, resolves/stats inputs and reads every existing file completely. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0029

[Lines 214–254](../../../../../../tests/observability/cli/native_cli_acceptance.py#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invoke(self, name: str, argv: list[str], inputs: dict[str, Path], expected_rc: int,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one CLI call and persist raw streams, arguments, hashes and parsing result. |
| inputs / outputs | Name/argv/inputs/exact expected status and optional JSON requirement to Invocation. |
| invariants | Timeout maps to 124; invocation.json marks any 124 as timed out. Exact status checked after artifacts persist; malformed requested JSON fails successful calls. |
| ownership | Owns full byte streams/optional JSON and retains Invocation; evidence files persist. |
| failure | Timeout output is retained; launch/write/decode/assertion failures propagate. |
| cost | One child with timeout, full captured output, input hashing and several evidence writes; no global byte bound. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0031

[Lines 256–260](../../../../../../tests/observability/cli/native_cli_acceptance.py#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def generated(self, relative: str, data: Any) -> Path:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write one generated JSON test artifact beneath run output. |
| inputs / outputs | Internal relative name and JSON data to created Path. |
| invariants | Callers supply trusted relative names; this function performs no independent containment validation. |
| ownership | Owns encoded buffer and persistent file. |
| failure | Directory/write/serialization failures propagate. |
| cost | Full JSON serialization/write plus parent mkdir. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0033

[Lines 262–274](../../../../../../tests/observability/cli/native_cli_acceptance.py#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def report_schema(self, report: Any, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate V2 report and nested V1 query payload where applicable. |
| inputs / outputs | Report/label to acceptance record. |
| invariants | Schema validity does not establish semantic cross-field equalities; stale native-integration gate is rejected separately. |
| ownership | Materializes all schema errors, then displays first if any. |
| failure | First reported schema violation raises AssertionError; nested validator failure propagates. |
| cost | Full schema traversal and all-error list allocation. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0035

[Lines 276–284](../../../../../../tests/observability/cli/native_cli_acceptance.py#L276); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def tree_schema(self, tree: Any, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate V2 tree and nested V1 witness for query trees. |
| inputs / outputs | Tree/label to recorded acceptance. |
| invariants | Report-specific semantic tree/height checks are elsewhere. |
| ownership | Owns full error list transiently; validators retained by harness. |
| failure | Schema violations fail; first error gains path context. |
| cost | Tree/schema traversal and error materialization. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0037

[Lines 286–306](../../../../../../tests/observability/cli/native_cli_acceptance.py#L286); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_export(self, format_name: str, invocation: Invocation, label: str,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check JSON/tree schemas or lexical text/DOT output. |
| inputs / outputs | Format and Invocation to report/tree object or decoded text. |
| invariants | Text permits newline and bytes &gt;=32 only; this DOT branch checks the expected graph name and complete lexical boundaries. Other harness methods check node counts and escaped labels; Graphviz parsing/rendering is not performed. |
| ownership | Returns retained parsed object or newly decoded text. |
| failure | Wrong shape, invalid UTF8, controls or format boundaries raise. |
| cost | Full output scan/decode/schema traversal; no native byte-resource measurement. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0039

[Lines 308–310](../../../../../../tests/observability/cli/native_cli_acceptance.py#L308); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def variable_ids(document: dict[str, Any]) -> dict[str, int]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct declared variable-name positions for plan comparisons. |
| inputs / outputs | Source document to name/index dictionary. |
| invariants | Uses listed order; duplicate names would overwrite, relying on admitted document validity. |
| ownership | Owns the index dictionary, which retains strong references to the immutable name strings; the returned map does not borrow the source document lifetime. |
| failure | Missing/wrong document fields propagate. |
| cost | Linear variables and map storage. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0041

[Lines 312–314](../../../../../../tests/observability/cli/native_cli_acceptance.py#L312); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def occurrence_ids(document: dict[str, Any]) -> dict[str, int]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct atom-label positions for plan comparisons. |
| inputs / outputs | Source document to atom-id/index dictionary. |
| invariants | Uses listed order and assumes admitted unique occurrence labels. |
| ownership | Owns index dictionary. |
| failure | Missing/malformed document data propagates. |
| cost | Linear atoms and map storage. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0043

[Lines 316–389](../../../../../../tests/observability/cli/native_cli_acceptance.py#L316); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def compare_tree(self, report: dict[str, Any], plan: dict[str, Any], case: dict[str, Any]) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exported selected-tree metadata against actual P08 plan and fixture expectations. |
| inputs / outputs | Report, emitted plan and case to detailed assertions. |
| invariants | Independently recomputes parent/separator/ID mappings; P08 plan itself is native-produced, not an independent minimum-height oracle. |
| ownership | Owns lookup maps, scope sets and transient ordered lists. |
| failure | Any fixture/native/export inconsistency or malformed field fails. |
| cost | Repeated node/parent-scope lookup and set/sort work; may be quadratic in nodes, acceptable offline. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0045

[Lines 391–458](../../../../../../tests/observability/cli/native_cli_acceptance.py#L391); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def compare_physical_report(self, report: dict[str, Any], plan: dict[str, Any], case: dict[str, Any]) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check diagnostic identity, native height/tree, observation registry and unavailable fields. |
| inputs / outputs | V2 physical report, P08 plan and manifest case to assertions. |
| invariants | Plan without independent certificate remains checked-upper; constant-false has distinct authority. Never infer minimum or cost optimality from report presence. |
| ownership | Owns transient registry/index maps and lists; borrows input trees. |
| failure | Schema-assumed field mismatch or malformed registry fails. |
| cost | Traverses report/registry and calls full compare_tree; offline checking cost. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0047

[Lines 460–524](../../../../../../tests/observability/cli/native_cli_acceptance.py#L460); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_physical_families(self) -> list[dict[str, Any]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower every valid pinned physical fixture and check four exports. |
| inputs / outputs | Manifest/CLI to list of actual plans/reports/case inputs. |
| invariants | Each fixture is lowered by selected CLI; exports compare native plan metadata and independent manifest fields. DOT validation stays lexical. |
| ownership | Owns child results, parsed plans/reports and persistent evidence directories. |
| failure | Any lower/export/schema/assertion failure aborts remaining cases. |
| cost | Five child processes per valid case plus all output/JSON/hash checking. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0049

[Lines 526–621](../../../../../../tests/observability/cli/native_cli_acceptance.py#L526); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def schema_mutations(self, physical: dict[str, Any], session: dict[str, Any], query: dict[str, Any],
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe closed schema rejection separately from semantic equality checks. |
| inputs / outputs | Actual physical/session/query/witness reports to mutation counts. |
| invariants | Changes copies only; intentionally confirms cross-field height mismatch is schema-valid. These are validator tests, not native input rejection cases. |
| ownership | Deep-copies complete report graphs for mutants. |
| failure | Unexpected acceptance/rejection or absent expected observed metric fails. |
| cost | Multiple full deep copies and schema traversals, proportional to corpus and report size. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

```text
def mutate(base: dict[str, Any], label: str, path: tuple[str | int, ...], value: Any) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one deep-copied schema mutant at a supplied field path. |
| inputs / outputs | Base, label, nonempty path and value to appended mutation. |
| invariants | Traverses supplied existing path; does not edit original base. |
| ownership | Owns whole deep copy; inserted mutable value is assigned directly. |
| failure | Bad path/key/type or allocation failures propagate. |
| cost | Full base deep copy plus path traversal. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0051

[Lines 623–678](../../../../../../tests/observability/cli/native_cli_acceptance.py#L623); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def proof_cases(self, fixture: dict[str, Any], other_fixture: dict[str, Any]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact certificate binding and deliberately mismatched proof inputs. |
| inputs / outputs | Two valid fixture contexts to matching/rejection outcomes. |
| invariants | Certificate producer is selected CLI tree-oracle; replay/binding checks are not an external optimum oracle. Wrong query/height/corruption must emit empty stdout. |
| ownership | Owns copied/mutated certificate JSON and evidence files. |
| failure | Absent certificate, unexpected status or partial stdout fails. |
| cost | Seven child invocations and full certificate serializations/checks; configured proof-work cap is native replay work, not total CPU. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0053

[Lines 680–738](../../../../../../tests/observability/cli/native_cli_acceptance.py#L680); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def session_input(self, plan: dict[str, Any]) -> Path:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one catalog-bound typed JSONL insert for owned-session tests. |
| inputs / outputs | Admitted plan source catalog to generated event Path. |
| invariants | Rebuilds canonical catalog field order/hash and chooses first-table typed values; successful CLI admission later checks the constructed binding. |
| ownership | Owns reconstructed catalog/event JSON and written binding/event files. |
| failure | Unsupported/malformed type metadata, empty tables or IO errors propagate. |
| cost | Visits full catalog metadata and serializes binding/event; not a native row hot path. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0055

[Lines 740–906](../../../../../../tests/observability/cli/native_cli_acceptance.py#L740); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_runtime_and_sessions(self, fixture: dict[str, Any]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check four runtime configurations and real owned-session states/output dispositions. |
| inputs / outputs | One physical fixture to retained reports and summarized outcomes. |
| invariants | Validates pending/committed, retain/discard/transfer and preserve/stop/drop plus wire rejection. runtime_reports=4 counts the four actual runtime configuration calls; global invocation_count is recorded separately. |
| ownership | Owns multiple reports and generated event files; reports are Python trees. |
| failure | Any mode/owner/source/observation/output assertion or child failure aborts. |
| cost | Four runtime and multiple session children plus report/schema copies and validations; no per-query instrumentation added. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0057

[Lines 908–917](../../../../../../tests/observability/cli/native_cli_acceptance.py#L908); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def triangle_infeasible(self) -> Path:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate a cyclic full-head three-relation CQ for exact infeasibility testing. |
| inputs / outputs | No external input to generated JSON Path. |
| invariants | Triangle scopes xy/yz/xz use the same x/y/z variables; this is a fixture, not an infeasibility proof by itself. |
| ownership | Owns JSON tree and persistent generated file. |
| failure | Generation/write failures propagate. |
| cost | Fixed small JSON construction/serialization. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0059

[Lines 919–995](../../../../../../tests/observability/cli/native_cli_acceptance.py#L919); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_query_forms(self, fixture: dict[str, Any], progress_fixture: dict[str, Any]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check admitted, partial, optimum, infeasible and certificate-replay reports. |
| inputs / outputs | Two fixtures to reports and standalone typed witness. |
| invariants | Zero/one-work forms cannot assert minimum; complete forms need typed certificate/witness authority. Infeasible query carries certificate and no witness. |
| ownership | Owns reports/certificate fixtures and returned nested witness. |
| failure | Unexpected authority/status/binding/schema or child failure aborts. |
| cost | Several exact-search/replay subprocesses with finite configured native work; whole result graphs retained. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0061

[Lines 997–1031](../../../../../../tests/observability/cli/native_cli_acceptance.py#L997); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invalid_cli_cases(self, fixture: dict[str, Any]) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check ten option/document rejection cases with empty stdout. |
| inputs / outputs | One valid fixture to count of rejection cases. |
| invariants | Distinguishes usage status 2 from runtime/document status 1; incompatible completion must have exact invalid_options stderr. |
| ownership | Owns malformed test file and argv/input lists. |
| failure | Unexpected code/output or failed launch/write fails. |
| cost | Ten child invocations plus input hashing and captured streams. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0063

[Lines 1033–1057](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1033); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def format_byte_limits(self, artifacts: dict[str, tuple[list[str] | dict[str, list[str]],
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test emitted byte ceilings for four formats across supplied artifact kinds. |
| inputs / outputs | Per-kind argv/input maps to baseline byte lengths. |
| invariants | Baseline is validated; N must succeed within ceiling, N-1/zero fail with status 4 and no partial stdout. This measures encoded output limits, not preparation/RSS caps. |
| ownership | Retains baseline/exact/failing call streams via harness. |
| failure | Unexpected limits/export/status or child failure fails. |
| cost | Four processes per format/artifact plus full output capture/validation. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0065

[Lines 1059–1104](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1059); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def escaped_label_fixture(self) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check embedded control and Unicode labels through lowering and all exports. |
| inputs / outputs | Fixed adversarial names to recorded label metadata. |
| invariants | JSON retains Unicode and escapes controls; text/DOT require escaped tokens and no raw embedded control bytes. Graphviz parsing is not performed. |
| ownership | Owns fixture documents, reports and captured byte outputs. |
| failure | Lost labels, invalid schema/escaping or unexpected CLI status fails. |
| cost | Fixed fixture plus five child calls and full byte scans. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0067

[Lines 1106–1159](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run(self) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute the complete ordered EXPLAIN acceptance campaign. |
| inputs / outputs | Configured Harness to summary after all checks. |
| invariants | Frozen inputs/schema setup precede physical/runtime/query/proof/byte/escaping cases. Caller-selected CLI runs; no native build occurs. |
| ownership | Retains all check records, Invocation outputs and generated artifacts. |
| failure | Any phase failure escapes to main, which attempts failed summary persistence. |
| cost | Entire subprocess campaign and retained graphs; no aggregate memory/time bound beyond child timeouts. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0069

[Lines 1161–1176](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def finish(self, status: str, result: dict[str, Any] | None, error: str | None = None,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Persist summary and render one terminal report if output initialized. |
| inputs / outputs | Status/result/optional error+traceback to run-summary.json and stdout. |
| invariants | Unset run_dir returns; no rollback or cleanup of evidence. Summary write/print can itself fail. |
| ownership | Writes owned record with complete checks/hash metadata; evidence remains for inspection. |
| failure | IO/serialization/print failure propagates; not a guaranteed failure logger. |
| cost | Serializes all accumulated checks and summary data, writes and prints full JSON. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0071

[Lines 1179–1196](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def parse_args() -> argparse.Namespace:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse selected CLI and portable package/output paths. |
| inputs / outputs | CLI arguments to argparse Namespace. |
| invariants | Optional binary SHA must be exactly 64 hex chars and is lowercased; parser does not check binary contents or executable mode. |
| ownership | Owns Namespace and Paths. |
| failure | argparse usage exits; later filesystem/content validation belongs to harness. |
| cost | Linear argument text parsing and bounded SHA regex. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0073

[Lines 1199–1209](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate campaign exceptions into saved failure evidence and nonzero process status. |
| inputs / outputs | Parsed command line to status 0 or 1. |
| invariants | Harness construction precedes try; run exceptions get traceback summary, not native retries. A failure inside finish can still escape. |
| ownership | Owns Harness until return; saved evidence persists. |
| failure | Campaign exceptions are caught once; parse/constructor/final-summary failures follow their own propagation. |
| cost | Runs entire campaign and one summary; formatting traceback is exceptional offline work. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |

## B0074

[Lines 1210–1213](../../../../../../tests/observability/cli/native_cli_acceptance.py#L1210); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the test campaign once when launched as a script. |
| inputs / outputs | Module execution mode to main invocation and process exit. |
| invariants | Native executable is not launched by importing these definitions; entry wrappers only translate test failure status. |
| ownership | Process owns campaign temporaries; persistent EXPLAIN evidence remains, workflow TemporaryDirectory data is scoped. |
| failure | main catches campaign exceptions and attempts summary persistence; this guard only passes its status to sys.exit. |
| cost | One explicit campaign; no native hot-path handler or retry added. |
| Design | [tests/observability/cli/native_cli_acceptance.py](../../../../../../tests/observability/cli/native_cli_acceptance.py), [CMakeLists.txt](../../../../../../CMakeLists.txt), [docs/cli.md](../../../../../cli.md), [docs/code_review.md](../../../../../code_review.md), [tests/observability/cli/readiness.json](../../../../../../tests/observability/cli/readiness.json), [tests/observability/cli/schemas/explain-report-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-report-v2.schema.json), [tests/observability/cli/schemas/explain-tree-v2.schema.json](../../../../../../tests/observability/cli/schemas/explain-tree-v2.schema.json), [tests/observability/cli/schemas/query-explain-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-explain-v1.schema.json), [tests/observability/cli/schemas/query-witness-v1.schema.json](../../../../../../tests/observability/cli/schemas/query-witness-v1.schema.json) |
