# `tools/verify_schemas.py` — block usage map

[Source](../../../../tools/verify_schemas.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `70584bb41b7488f4ff15a7a936dd16034badf2b90f7f7f96c14bf099e2141d6b`. 200 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../tools/verify_schemas.py#L1) | Imports dependencies. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 17–19](../../../../tools/verify_schemas.py#L17) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None: · [reviewed contract](#b0002) |
| [B0003 · 20–21](../../../../tools/verify_schemas.py#L20) | Explanatory comments or spacing. |  |
| [B0004 · 22–192](../../../../tools/verify_schemas.py#L22) | Callable definition: def main() -&gt; None: | calls require, len, str, Path; guard require(len(sys.argv) == 2, "usage: verify_schemas.py EXECUTABLE"); returns json.loads(result.stdout); growth insert; 16 loop sites; source comment (unverified): # The local store covers current references; no explicit deny-network handlers are set. · [reviewed contract](#b0004) |
| [B0005 · 193–200](../../../../tools/verify_schemas.py#L193) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–16](../../../../tools/verify_schemas.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define optional broad frontend/identity/physical schema audit orchestration. |
| inputs / outputs | Imports stdlib only at module load; guarded main imports jsonschema and invokes crown plus sibling test exporters. |
| invariants | The module documentation now states this audit and registered report-schema tests need installed jsonschema. main uses a local URI/$id store without explicit remote-deny handlers; that resolver boundary is unchanged by the documentation correction. |
| ownership | Owns imports; main owns all schema/report/temporary-file graphs and captured outputs. |
| failure | Top-level imports visible; guarded wrapper catches only declared operational classes, no universal exception handler. |
| cost | Fixed import cost; main full schema/corpus/native matrix is offline validation, no native runtime instrumentation. |
| Design | [tools/verify_schemas.py](../../../../tools/verify_schemas.py), [docs/native_build.md](../../../native_build.md), [docs/sql_support.md](../../../sql_support.md), [tests/frontend/normalization/manifest.json](../../../../tests/frontend/normalization/manifest.json), [tests/frontend/admission/manifest.json](../../../../tests/frontend/admission/manifest.json), [tests/structural/lowering/manifest.json](../../../../tests/structural/lowering/manifest.json), [tests/runtime/support/manifest.json](../../../../tests/runtime/support/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 17–19](../../../../tools/verify_schemas.py#L17); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tools/verify_schemas.py](../../../../tools/verify_schemas.py), [docs/native_build.md](../../../native_build.md), [docs/sql_support.md](../../../sql_support.md), [tests/frontend/normalization/manifest.json](../../../../tests/frontend/normalization/manifest.json), [tests/frontend/admission/manifest.json](../../../../tests/frontend/admission/manifest.json), [tests/structural/lowering/manifest.json](../../../../tests/structural/lowering/manifest.json), [tests/runtime/support/manifest.json](../../../../tests/runtime/support/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 22–192](../../../../tools/verify_schemas.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate actual native frontend/identity/certificate/physical/input exports and focused controls against local schema graphs. |
| inputs / outputs | Exactly crown executable arg; infers repo/sibling test executables, reads fixtures, prints finite artifact counts. |
| invariants | Loads all schemas with fileURI/$id store but no enforced remote-deny handlers. Normalization/admission/identity/lowering/support/input fixtures checked; constructs valid legacy v1 proof and sends it to actual native verify-height, not merely schema parse. |
| ownership | Owns schemas/validators, captured native DOMs and temporary program/core/tree/certificate/input files removed by context managers. |
| failure | Explicit RuntimeError for predicate/exit issues, timeout30 for invoke, schema/JSON/IO errors propagate; sibling exporter direct subprocess branch uses its actual parameters. |
| cost | Many captured native CLI operations plus complete schema/fixture scans, JSON serialization/parse, native proof verification and temporary file writes; finite controls, no universal correctness/performance claim. |
| Design | [tools/verify_schemas.py](../../../../tools/verify_schemas.py), [docs/native_build.md](../../../native_build.md), [docs/sql_support.md](../../../sql_support.md), [tests/frontend/normalization/manifest.json](../../../../tests/frontend/normalization/manifest.json), [tests/frontend/admission/manifest.json](../../../../tests/frontend/admission/manifest.json), [tests/structural/lowering/manifest.json](../../../../tests/structural/lowering/manifest.json), [tests/runtime/support/manifest.json](../../../../tests/runtime/support/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def invoke(arguments: list[str], code: int = 0) -> dict:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one crown CLI command with an exact expected exit and empty stderr. |
| inputs / outputs | Argument list and expected exit default0 in; parsed stdout JSON out. |
| invariants | check=False/default, timeout30 and full text captures; expected code may be1 for controlled rejection. No output-byte cap or typed authority from parse alone. |
| ownership | Owns argument/capture strings and parsed DOM; inputs borrowed. |
| failure | RuntimeError on wrong exit/diagnostic, TimeoutExpired/OSError/JSON errors propagate. |
| cost | One native subprocess plus full uncapped output capture/JSON parse; temporary input handling belongs to main. |
| Design | [tools/verify_schemas.py](../../../../tools/verify_schemas.py), [docs/native_build.md](../../../native_build.md), [docs/sql_support.md](../../../sql_support.md), [tests/frontend/normalization/manifest.json](../../../../tests/frontend/normalization/manifest.json), [tests/frontend/admission/manifest.json](../../../../tests/frontend/admission/manifest.json), [tests/structural/lowering/manifest.json](../../../../tests/structural/lowering/manifest.json), [tests/runtime/support/manifest.json](../../../../tests/runtime/support/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0005

[Lines 193–200](../../../../tools/verify_schemas.py#L193); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the broad schema audit only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | Catches ImportError/RuntimeError/ValueError/OSError/TimeoutExpired into stderr/exit1; schema ValidationError and unrelated errors may retain traceback. |
| cost | Fixed wrapper plus full main; no broad new handler. |
| Design | [tools/verify_schemas.py](../../../../tools/verify_schemas.py), [docs/native_build.md](../../../native_build.md), [docs/sql_support.md](../../../sql_support.md), [tests/frontend/normalization/manifest.json](../../../../tests/frontend/normalization/manifest.json), [tests/frontend/admission/manifest.json](../../../../tests/frontend/admission/manifest.json), [tests/structural/lowering/manifest.json](../../../../tests/structural/lowering/manifest.json), [tests/runtime/support/manifest.json](../../../../tests/runtime/support/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
