# `tools/verify_report_memory_schema_v2.py` — block usage map

[Source](../../../../tools/verify_report_memory_schema_v2.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `4403ad451beb1c1253df8a1cb12552e68ff22d6d336f566c89b39ad37607e8f7`. 146 lines partitioned into 13 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–28](../../../../tools/verify_report_memory_schema_v2.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 29–30](../../../../tools/verify_report_memory_schema_v2.py#L29) | Callable definition: def read(path): | calls loads, read_text; returns json.loads(path.read_text(encoding="utf-8")) · [reviewed contract](#b0002) |
| [B0003 · 31–32](../../../../tools/verify_report_memory_schema_v2.py#L31) | Explanatory comments or spacing. |  |
| [B0004 · 33–34](../../../../tools/verify_report_memory_schema_v2.py#L33) | Callable definition: def deny_remote(uri): | calls RuntimeError · [reviewed contract](#b0004) |
| [B0005 · 35–36](../../../../tools/verify_report_memory_schema_v2.py#L35) | Explanatory comments or spacing. |  |
| [B0006 · 37–57](../../../../tools/verify_report_memory_schema_v2.py#L37) | Callable definition: def validator(directory): | calls read, check_schema, resolve, as_uri; returns store\[uri\]; Draft202012Validator(report, resolver=resolver), report; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 58–59](../../../../tools/verify_report_memory_schema_v2.py#L58) | Explanatory comments or spacing. |  |
| [B0008 · 60–70](../../../../tools/verify_report_memory_schema_v2.py#L60) | Callable definition: def memory_fields(value, path=()): | calls isinstance, items, update, enumerate; returns result; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 71–72](../../../../tools/verify_report_memory_schema_v2.py#L71) | Explanatory comments or spacing. |  |
| [B0010 · 73–79](../../../../tools/verify_report_memory_schema_v2.py#L73) | Callable definition: def replace(document, path, value): | calls deepcopy; returns result; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 80–81](../../../../tools/verify_report_memory_schema_v2.py#L80) | Explanatory comments or spacing. |  |
| [B0012 · 82–142](../../../../tools/verify_report_memory_schema_v2.py#L82) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, resolve; guard def check(condition, message):; 10 loop sites; source comment (unverified): # Check both affected option objects exactly. Later Session/window features · [reviewed contract](#b0012) |
| [B0013 · 143–146](../../../../tools/verify_report_memory_schema_v2.py#L143) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |

## B0001

[Lines 1–28](../../../../tools/verify_report_memory_schema_v2.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the maintained v2 additive-memory schema audit using installed local RefResolver. |
| inputs / outputs | Defines four schema names, two exact memory-limit paths and uint64 maximum; guarded main reads current/frozen schemas and native outputs. |
| invariants | v2 restricts file/http/https resolution to supplied local stores; current CMake uses this revision. Frozen package is checked by its actual readiness hashes, whose parent-applied scoped drift is recorded separately. |
| ownership | Owns constants/imports and validators/DOMs; generated corpus is deliberately retained, no native query ownership. |
| failure | Import/schema/IO failures propagate. Explicit check raises AssertionError, not disabled by -O. |
| cost | Fixed module declarations; main allocates full current/frozen schema graphs, native outputs and many deep mutation copies. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
MAXIMUM = (1 << 64) - 1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the exact uint64 schema maximum. |
| inputs / outputs | MAXIMUM=(1&lt;&lt;64)-1, reused in expected property and boundary tests. |
| invariants | Boundary is schema integer range, not a runtime grant currently in force. |
| ownership | Module owns immutable big integer. |
| failure | Import allocation failure only. |
| cost | Fixed integer shift/subtract. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
NAMES = ("explain-report-v2.schema.json", "explain-tree-v2.schema.json",
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fix four schema files used to compare current/frozen report formats. |
| inputs / outputs | NAMES tuple in report/tree/query-explain/query-witness order. |
| invariants | Only these explicitly named schemas are loaded; report is first. No discovery of arbitrary schema roots. |
| ownership | Owning tuple/strings. |
| failure | Missing actual files fail validator later. |
| cost | Fixed four-name setup. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
PATHS = (
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the two exact optional memory-limit locations in emitted reports. |
| inputs / outputs | PATHS tuple contains physical.support.memory_limit_bytes and session.requested_delta.memory_limit_bytes key paths. |
| invariants | Fields are requested configuration values, not new memory ownership/proof/durable authority. |
| ownership | Owns immutable tuples/string labels. |
| failure | Import allocation failure only. |
| cost | Two bounded key paths; recursive discovery later scans all report nodes. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 29–30](../../../../tools/verify_report_memory_schema_v2.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def read(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one complete local schema/report/readiness JSON document. |
| inputs / outputs | Path in; json.loads(read_text UTF8) graph out. |
| invariants | Uses default duplicate/nonfinite policies; additional validators/checks apply afterward, no stronger strict-JSON hook claimed. |
| ownership | Owns text and complete DOM; source read-only. |
| failure | IO/Unicode/JSON/OOM failures propagate. |
| cost | O(file bytes) full read/parse and graph allocation. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 33–34](../../../../tools/verify_report_memory_schema_v2.py#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def deny_remote(uri):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject resolution outside the supplied local schema corpus. |
| inputs / outputs | URI string in; RuntimeError with local-corpus diagnostic, no normal result. |
| invariants | Used as registry retrieve in v1 or http/https handlers in v2; no network request performed by this function. |
| ownership | Owns exception/message, borrows URI. |
| failure | Always raises RuntimeError during schema reference resolution. |
| cost | O(URI length) message allocation. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 37–57](../../../../tools/verify_report_memory_schema_v2.py#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validator(directory):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load four local schemas into the maintained offline RefResolver store. |
| inputs / outputs | Directory Path in; report validator plus primary report schema DOM out. |
| invariants | Meta-validates all files, maps resolved URI and $id, denies unknown local file and http/https. This guarantees local resolver boundary, not report semantic proof. |
| ownership | Owns complete schema DOMs and registry/store/validator retaining graphs; returned schema aliases retained primary graph. |
| failure | File/JSON/metaschema/reference/package-version/OOM failures propagate; no fallback network or ignored validation error. |
| cost | Four full file reads/meta-validations and resource/store construction; validators retain entire schemas, resolution may revisit graph refs. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def local_file(uri):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serve only preloaded schema file URIs for v2 resolution. |
| inputs / outputs | URI in; aliased store schema out. |
| invariants | Unknown URI explicitly rejects; no filesystem read for arbitrary reference. |
| ownership | Borrows captured store; returned DOM alias retained by validator. |
| failure | RuntimeError on missing URI; no catch. |
| cost | Expected O(1) lookup, no native/file/network work. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0008

[Lines 60–70](../../../../tools/verify_report_memory_schema_v2.py#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def memory_fields(value, path=()):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find every memory_limit_bytes field anywhere in an exported JSON graph. |
| inputs / outputs | Value plus optional path tuple in; path-tuple-&gt;original value dict out. |
| invariants | Recurses all object/list values; caller compares exact two paths or empty omission. Discovery does not validate value kind/range by itself. |
| ownership | Owns result maps/path tuples recursively; field values alias original DOM values. |
| failure | Recursion/OOM/type errors propagate; no mutation. |
| cost | O(graph nodes) traversal but repeated path tuple construction/map merging adds depth/descendant-copy work; stores every matching path. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0010

[Lines 73–79](../../../../tools/verify_report_memory_schema_v2.py#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def replace(document, path, value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy a report then replace one exact nested field. |
| inputs / outputs | Document/key-index path/replacement value in; independent mutant out. |
| invariants | Base untouched; replacement value is retained as supplied, not deep-copied again. |
| ownership | Owns complete clone, aliases replacement if mutable. |
| failure | Deepcopy/path/index/type/OOM failures propagate. |
| cost | O(document graph) clone plus O(path length) traversal, one clone per negative/boundary check. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0012

[Lines 82–142](../../../../tools/verify_report_memory_schema_v2.py#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the exact two optional memory-option object additions, frozen package hashes and actual emitted account limits. |
| inputs / outputs | --executable/--repo-root in; creates retained corpus, captures native driver output, validates default/limited/max and eight invalid values at each path plus zero. |
| invariants | Both affected option objects must equal their frozen object plus exactly one optional uint64 memory_limit_bytes property. Unrelated independently tested Session/window schema additions are allowed. Native default remains legacy-compatible and omits both fields; finite/max reports must put exact integer values at both locations. Frozen package identity is checked by all declared readiness hashes. |
| ownership | Owns both validator sets/schema clones, driver capture and report/mutant DOMs. mkdtemp corpus intentionally retained on success and failure; no cleanup finally. |
| failure | Explicit AssertionError on transition/hash/native/value discrepancy; IO/subprocess/JSON/schema errors propagate. Driver has no intrinsic timeout here; CMake v2 supplies outer timeout120. |
| cost | Load/check four current and four frozen schema DOMs, copy and compare the two affected option objects, hash every frozen readiness member, run three actual account/report fixtures, then validate default and finite/max documents with positive boundaries and invalid-value mutations. Offline test/report work only; no engine hot path. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def check(condition, message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count a successful explicit schema-audit predicate or reject it. |
| inputs / outputs | Condition/message and captured checks counter in; increments on success. |
| invariants | Explicit if/raise remains active under -O; count covers completed predicates only. |
| ownership | Borrows condition/text, mutates local counter only. |
| failure | AssertionError on false before increment; no cleanup/retry. |
| cost | Fixed branch/integer increment; diagnostic allocation only on failure. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0013

[Lines 143–146](../../../../tools/verify_report_memory_schema_v2.py#L143); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the memory-option schema audit only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | No outer catch; all failures retain traceback and any already-created native corpus. |
| cost | Guard constant plus full main; v1 retained history, current CMake calls v2. |
| Design | [tools/verify_report_memory_schema_v2.py](../../../../tools/verify_report_memory_schema_v2.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/explain-report-v2.schema.json](../../../../schemas/explain-report-v2.schema.json), [tests/observability/cli/readiness.json](../../../../tests/observability/cli/readiness.json), [tests/unit/report_memory_schema_test.cpp](../../../../tests/unit/report_memory_schema_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
