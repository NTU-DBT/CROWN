# `tools/verify_residual_reports.py` — block usage map

[Source](../../../../tools/verify_residual_reports.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `fcf2756ab710f9dc7a4ce960ca3ddb567bf8ac9e2bf331752d905cf6537f8a6b`. 141 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../tools/verify_residual_reports.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 12–14](../../../../tools/verify_residual_reports.py#L12) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None: · [reviewed contract](#b0002) |
| [B0003 · 15–16](../../../../tools/verify_residual_reports.py#L15) | Explanatory comments or spacing. |  |
| [B0004 · 17–133](../../../../tools/verify_residual_reports.py#L17) | Callable definition: def main() -&gt; None: | calls require, len, str, Path; guard require(len(sys.argv) == 3,; returns store\[uri\]; raise RuntimeError(f"schema accepted malformed report: {label}"); 9 loop sites; source comment (unverified): # A schema rejection is the expected negative result; other failures must surface. · [reviewed contract](#b0004) |
| [B0005 · 134–141](../../../../tools/verify_residual_reports.py#L134) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–11](../../../../tools/verify_residual_reports.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define finite typed residual-report schema/authority controls. |
| inputs / outputs | Imports stdlib at module load, imports jsonschema inside guarded main; expects native --emit executable and repository root. |
| invariants | Native typed reports are produced externally; schema labels/certificates in DTOs do not create independent proof authority. Local URI store and explicit deny handlers bound schema resolution. |
| ownership | Owns imports, then full schema maps/validators/captured output/records and mutation clones during main. |
| failure | Import/schema/IO/native failures propagate to narrow script wrapper; explicit require RuntimeError remains active under -O. |
| cost | Fixed import setup; all file/meta/schema/report scans and native producer work deferred to main. |
| Design | [tools/verify_residual_reports.py](../../../../tools/verify_residual_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [tests/unit/residual_io_test.cpp](../../../../tests/unit/residual_io_test.cpp), [schemas/residual-report-v1.schema.json](../../../../schemas/residual-report-v1.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 12–14](../../../../tools/verify_residual_reports.py#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a false caller-supplied condition in this tool. |
| inputs / outputs | Truth-tested value and diagnostic text in; None on truth, RuntimeError on false. |
| invariants | Explicit conditional raise remains active under Python -O; this is a local assertion of the stated predicate, not native/proof validation. |
| ownership | Borrows condition/message; exception retains message until released. |
| failure | Raises RuntimeError at the caller check before subsequent operations; does not catch or undo earlier IO. |
| cost | O(truth conversion) plus exception construction only on failure; arbitrary user-defined __bool__ is outside these primitive callers. |
| Design | [tools/verify_residual_reports.py](../../../../tools/verify_residual_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [tests/unit/residual_io_test.cpp](../../../../tests/unit/residual_io_test.cpp), [schemas/residual-report-v1.schema.json](../../../../schemas/residual-report-v1.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 17–133](../../../../tools/verify_residual_reports.py#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate residual trace/upper/progress/original-proof scope across emitted versions and focused mutants. |
| inputs / outputs | Exactly executable/root args; loads/meta-validates local schemas, captures --emit JSON records, checks required cases/versions and negative mutations, prints counts. |
| invariants | Requires exact record fields/unique names, versions1/2/3 and twelve artifact cases. Trace/checked upper/partial or induced lower evidence cannot become original minimum proof; original completed certificate binding retained. |
| ownership | Owns all schema DOMs/validators/store, complete child stdout/stderr/records and per-mutant graph; native child has separate lifetime. |
| failure | 180s --emit timeout, nonzero/stderr explicitly rejects; schema/JSON/field errors propagate. Nested reject counts only ValidationError, not arbitrary exceptions. |
| cost | Full schema directory reads/meta-validation, one native producer with uncapped captured output, finite whole-report schema/authority scans and repeated deep mutation/revalidation; no independent search/theorem replay by this Python code. |
| Design | [tools/verify_residual_reports.py](../../../../tools/verify_residual_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [tests/unit/residual_io_test.cpp](../../../../tests/unit/residual_io_test.cpp), [schemas/residual-report-v1.schema.json](../../../../schemas/residual-report-v1.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def local_file(uri: str) -> dict:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return only a preloaded local schema for a recognized file URI. |
| inputs / outputs | URI in; captured store DOM out. |
| invariants | Unknown URI rejects through require; no arbitrary file or remote fetch. |
| ownership | Returns borrowed alias retained by store/validator, no deepcopy. |
| failure | RuntimeError on unrecognized URI; type/key errors propagate. |
| cost | Expected O(1) dictionary lookup with diagnostic formatting on failure. |
| Design | [tools/verify_residual_reports.py](../../../../tools/verify_residual_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [tests/unit/residual_io_test.cpp](../../../../tests/unit/residual_io_test.cpp), [schemas/residual-report-v1.schema.json](../../../../schemas/residual-report-v1.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def deny_network(uri: str) -> dict:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail any attempted remote schema fetch. |
| inputs / outputs | http/https URI in; raises RuntimeError. |
| invariants | Handler performs no network operation; local schema use still needs semantic checks. |
| ownership | Owns exception/message; URI borrowed. |
| failure | Always throws during reference resolution. |
| cost | O(URI text) diagnostic allocation only. |
| Design | [tools/verify_residual_reports.py](../../../../tools/verify_residual_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [tests/unit/residual_io_test.cpp](../../../../tests/unit/residual_io_test.cpp), [schemas/residual-report-v1.schema.json](../../../../schemas/residual-report-v1.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def reject(base: str, path: tuple, value: object, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mutate one residual report and require schema-level rejection. |
| inputs / outputs | Base case name, nested key/index tuple, replacement value and label in; increments captured rejection count only on ValidationError. |
| invariants | Deepcopy isolates base. Rejects premature/upper-promoted certificates, forged minima, enum/bool/resource/scope violations; not an engine mutation or native proof verifier. |
| ownership | Owns complete mutant; replacement may alias supplied other graph, original base unchanged. |
| failure | ValidationError expected/counts; accepted mutant RuntimeError, unexpected copy/path/schema failures propagate. |
| cost | O(base graph) deep clone plus path walk and full schema validation per twelve controlled cases. |
| Design | [tools/verify_residual_reports.py](../../../../tools/verify_residual_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [tests/unit/residual_io_test.cpp](../../../../tests/unit/residual_io_test.cpp), [schemas/residual-report-v1.schema.json](../../../../schemas/residual-report-v1.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0005

[Lines 134–141](../../../../tools/verify_residual_reports.py#L134); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the residual-report audit only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | Catches ImportError/RuntimeError/ValueError/OSError/subprocess.TimeoutExpired, prints contextual stderr and exits1; other exception classes remain visible, no fallback acceptance. |
| cost | Fixed presentation plus main; no retries or broad recovery overhead. |
| Design | [tools/verify_residual_reports.py](../../../../tools/verify_residual_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [tests/unit/residual_io_test.cpp](../../../../tests/unit/residual_io_test.cpp), [schemas/residual-report-v1.schema.json](../../../../schemas/residual-report-v1.schema.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
