# `tools/verify_json_cleanup.py` — block usage map

[Source](../../../../tools/verify_json_cleanup.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `99e5fbbfd1ef04c81fc1a95731bf99708418a8ba8fde70e9303aae912fbfdd91`. 103 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../tools/verify_json_cleanup.py#L1) | Imports dependencies; declares types or opens a type body; declares callable signatures. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 23–45](../../../../tools/verify_json_cleanup.py#L23) | Callable definition: def run(executable: Path, mode: str, label: str, output: Path) -&gt; int: | calls str, with, open, VerificationError; returns result.returncode · [reviewed contract](#b0002) |
| [B0003 · 46–47](../../../../tools/verify_json_cleanup.py#L46) | Explanatory comments or spacing. |  |
| [B0004 · 48–74](../../../../tools/verify_json_cleanup.py#L48) | Callable definition: def verify(original: Path, patched: Path, output: Path) -&gt; None: | calls in, run, or, stat; 2 loop sites; source comment (unverified): # This control is intentionally a separate process. Its upstream destructor · [reviewed contract](#b0004) |
| [B0005 · 75–76](../../../../tools/verify_json_cleanup.py#L75) | Explanatory comments or spacing. |  |
| [B0006 · 77–99](../../../../tools/verify_json_cleanup.py#L77) | Callable definition: def main() -&gt; int: | calls ArgumentParser, add_argument, parse_args, resolve; returns 1; 1; 1 loop sites; source comment (unverified): # CROWN's native build supports Linux. Disable core files for the · [reviewed contract](#b0006) |
| [B0007 · 100–103](../../../../tools/verify_json_cleanup.py#L100) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–22](../../../../tools/verify_json_cleanup.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define isolated upstream/patched JSON serialization and expected-abort controls. |
| inputs / outputs | Imports stdlib/Linux resource support; guarded CLI receives two explicit native binaries. |
| invariants | Compatibility means exact serialization/sizeof bytes and one known upstream bad_alloc abort, not arbitrary nonzero exit or patched destructor proof by this script alone. |
| ownership | Owns module imports; child captures written to private temporary files, status JSON retained on failure. |
| failure | Import failure visible; VerificationError contextualizes expected process/compatibility failures. |
| cost | Fixed setup; later three child invocations and full raw-output comparison. |
| Design | [tools/verify_json_cleanup.py](../../../../tools/verify_json_cleanup.py), [docs/native_build.md](../../../native_build.md), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
class VerificationError(RuntimeError):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name isolated JSON compatibility/control failures. |
| inputs / outputs | RuntimeError subclass; main catches this with OSError/ValueError. |
| invariants | No exception suppression/cleanup built into class. |
| ownership | Owns diagnostic/cause as normal exception. |
| failure | Thrown on process/compatibility failure; main retains evidence directory. |
| cost | Fixed type allocation; failure messages/tracebacks only when thrown. |
| Design | [tools/verify_json_cleanup.py](../../../../tools/verify_json_cleanup.py), [docs/native_build.md](../../../native_build.md), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 23–45](../../../../tools/verify_json_cleanup.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run(executable: Path, mode: str, label: str, output: Path) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one serializer/cleanup control with raw capture and a finally-written status record. |
| inputs / outputs | Executable/mode/label/output directory in; actual returncode out. |
| invariants | stdin DEVNULL, stdout/stderr files, timeout120 and check=False; writes status on success, timeout or OSError. Status-write failure can supersede prior error; no claim of unconditional process success. |
| ownership | Owns file handles/status dict; filesystem retains raw/status artifacts, handles close via contexts. |
| failure | Timeout/OSError become chained VerificationError with status error; finally serializes status and may itself fail. |
| cost | One native child with120s limit, streaming raw capture files, then small status write; raw output uncapped but not PIPE-buffered. |
| Design | [tools/verify_json_cleanup.py](../../../../tools/verify_json_cleanup.py), [docs/native_build.md](../../../native_build.md), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 48–74](../../../../tools/verify_json_cleanup.py#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def verify(original: Path, patched: Path, output: Path) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require identical serializer bytes and a separate upstream SIGABRT/bad_alloc cleanup failure. |
| inputs / outputs | Original/patched binary Paths and output directory in; prints compatibility bytes/SHA on success. |
| invariants | Both --serialize zero/no stderr, nonempty byte-identical stdout; upstream --cleanup must -SIGABRT and bad_alloc, and no ASan/leak/UB unrelated diagnostic. Does not run patched cleanup branch here. |
| ownership | Owns full before/after/diagnostic byte buffers; filesystem retains command outputs. |
| failure | VerificationError on exact control mismatch; run/IO errors propagate. |
| cost | Three child invocations, two full output reads/byte comparison, diagnostic marker scans and SHA; no engine hot-path overhead. |
| Design | [tools/verify_json_cleanup.py](../../../../tools/verify_json_cleanup.py), [docs/native_build.md](../../../native_build.md), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 77–99](../../../../tools/verify_json_cleanup.py#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run JSON compatibility controls in a private directory with expected core dumps disabled. |
| inputs / outputs | --original/--patched distinct existing Paths in; returns0 after success+cleanup,1 on verification/cleanup failure. |
| invariants | RLIMIT_CORE0 applies wrapper and children on supported Linux; no global source/build mutation. Failure evidence retained; success removes temporary directory. |
| ownership | Owns mkdtemp directory and child artifacts; cleanup only after verified success. |
| failure | Catches VerificationError/OSError/ValueError to report retained path; rmtree OSError separately returns1. Other exceptions propagate, no broad swallowing. |
| cost | Child/control costs plus recursive success cleanup; full-file compare/hash buffers and small status records. |
| Design | [tools/verify_json_cleanup.py](../../../../tools/verify_json_cleanup.py), [docs/native_build.md](../../../native_build.md), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0007

[Lines 100–103](../../../../tools/verify_json_cleanup.py#L100); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the JSON cleanup control only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | SystemExit(main code); declared main failures returned, no additional catch. |
| cost | Fixed guard plus control suite. |
| Design | [tools/verify_json_cleanup.py](../../../../tools/verify_json_cleanup.py), [docs/native_build.md](../../../native_build.md), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
