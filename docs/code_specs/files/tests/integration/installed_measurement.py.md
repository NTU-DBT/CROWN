# `tests/integration/installed_measurement.py` — block usage map

[Source](../../../../../tests/integration/installed_measurement.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `8a487ef2ab8e3eaf225e1112d0b6181bdd51f48fd7070803665e17848cc93da4`. 65 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../tests/integration/installed_measurement.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 7–8](../../../../../tests/integration/installed_measurement.py#L7) | Callable definition: def require(value,message): | calls RuntimeError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../tests/integration/installed_measurement.py#L9) | Callable definition: def key(value):return json.dumps(value,sort_keys=True,separators=(',',':'),ensure_ascii=False) | calls dumps; returns json.dumps(value,sort_keys=True,separators=(',',':'),ensure_ascii=False) · [reviewed contract](#b0003) |
| [B0004 · 10–62](../../../../../tests/integration/installed_measurement.py#L10) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, Path; guard require(result.returncode==0,f'{command}: {result.stderr\[-2500:\]} {result.stdout\[-1500:\]}');return …; returns result; growth insert; 15 loop sites · [reviewed contract](#b0004) |
| [B0005 · 63–65](../../../../../tests/integration/installed_measurement.py#L63) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–6](../../../../../tests/integration/installed_measurement.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:3a5f3ba36a86860571d32c1d417801d91469a7a7f95b745b694237505b6d4f42
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for installed_measurement.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/installed_measurement.py](../../../../../tests/integration/installed_measurement.py), [docs/measurement.md](../../../../measurement.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 7–8](../../../../../tests/integration/installed_measurement.py#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value,message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce a relocated collector acceptance condition. |
| inputs / outputs | Returns None for a truthy value; otherwise raises RuntimeError(message). |
| invariants | Checks use if rather than assert and remain enabled under -O. |
| ownership | Borrows its arguments and does not mutate reports or artifacts. |
| failure | RuntimeError denotes the supplied mismatch; operand truth conversion can fail separately. |
| cost | Constant helper work after the caller computes the condition/message. |
| Design | [tests/integration/installed_measurement.py](../../../../../tests/integration/installed_measurement.py), [docs/measurement.md](../../../../measurement.md), [benchmarks/workloads/manifest.json](../../../../../benchmarks/workloads/manifest.json) |

## B0003

[Lines 9–9](../../../../../tests/integration/installed_measurement.py#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def key(value):return json.dumps(value,sort_keys=True,separators=(',',':'),ensure_ascii=False)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create compact canonical-style JSON text for requests, catalog digests and unordered row comparisons. |
| inputs / outputs | Serializes JSON-compatible value to sorted-key, unescaped-Unicode str. |
| invariants | List order is preserved; sorted dictionaries support stable text comparison. This helper does not reject nonfinite floats. |
| ownership | Allocates a complete string and borrows the input graph without copying its containers. |
| failure | Unsupported/cyclic inputs and incompatible keys raise json serialization exceptions. |
| cost | Full traversal plus object-key sorting and output-string storage. |
| Design | [tests/integration/installed_measurement.py](../../../../../tests/integration/installed_measurement.py), [docs/measurement.md](../../../../measurement.md), [benchmarks/workloads/manifest.json](../../../../../benchmarks/workloads/manifest.json) |

## B0004

[Lines 10–62](../../../../../tests/integration/installed_measurement.py#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accept the relocated installed public workload collector against independent encoded-row oracles. |
| inputs / outputs | Source/build/compiler/sanitizer arguments in; installed consumer build, two-query fixture outputs, raw reports and verification records under test artifacts. |
| invariants | Validates installed collector raw reports against v2 schema. It continues to test two queries, two backends and three modes through installed artifacts, without source/build headers or test/reference ABI in the consumer. |
| ownership | Test owns temporary consumer/build/output data; installed prefix and source fixtures are read-only. |
| failure | Install/configure/compile/consumer/schema/oracle mismatches fail the integration process; child timeouts/errors propagate. |
| cost | Configures/builds the small relocated consumer and runs finite collector cases plus independent row comparisons. |
| Design | [tests/integration/installed_measurement.py](../../../../../tests/integration/installed_measurement.py), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [examples/workload-measurement/CMakeLists.txt](../../../../../examples/workload-measurement/CMakeLists.txt), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0005

[Lines 63–65](../../../../../tests/integration/installed_measurement.py#L63); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Accept a relocated public workload collector against independent encoded-row oracles for two queries, two backends and three output modes. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only Exception to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/installed_measurement.py](../../../../../tests/integration/installed_measurement.py), [docs/development.md](../../../../development.md), [docs/measurement.md](../../../../measurement.md), [benchmarks/workloads/manifest.json](../../../../../benchmarks/workloads/manifest.json) |
