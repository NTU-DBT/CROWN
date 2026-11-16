# `tools/plot_experimental_report.py` — block usage map

[Source](../../../../tools/plot_experimental_report.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `b7bf3c97c0faa0c22966c96185dcf04bcc63417c9d6465877606b89b5d4e76a9`. 160 lines partitioned into 11 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../tools/plot_experimental_report.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 18–20](../../../../tools/plot_experimental_report.py#L18) | Callable definition: def require(condition, message): | calls ValueError; guard def require(condition, message): · [reviewed contract](#b0002) |
| [B0003 · 21–22](../../../../tools/plot_experimental_report.py#L21) | Explanatory comments or spacing. |  |
| [B0004 · 23–25](../../../../tools/plot_experimental_report.py#L23) | Callable definition: def digest(path): | calls open, file_digest, hexdigest; returns hashlib.file_digest(stream, 'sha256').hexdigest() · [reviewed contract](#b0004) |
| [B0005 · 26–27](../../../../tools/plot_experimental_report.py#L26) | Explanatory comments or spacing. |  |
| [B0006 · 28–30](../../../../tools/plot_experimental_report.py#L28) | Callable definition: def csv_rows(path): | calls open, list, DictReader; returns list(csv.DictReader(stream)) · [reviewed contract](#b0006) |
| [B0007 · 31–32](../../../../tools/plot_experimental_report.py#L31) | Explanatory comments or spacing. |  |
| [B0008 · 33–144](../../../../tools/plot_experimental_report.py#L33) | Callable definition: def run(args): | calls resolve, require, exists, loads; guard require(not output.exists(), 'figure output must be new'); growth new; 28 loop sites; source comment (unverified): # Reuse the reviewed B05 plot API and its complete selected-family appendix. · [reviewed contract](#b0008) |
| [B0009 · 145–146](../../../../tools/plot_experimental_report.py#L145) | Explanatory comments or spacing. |  |
| [B0010 · 147–156](../../../../tools/plot_experimental_report.py#L147) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, run; returns 1; 0 · [reviewed contract](#b0010) |
| [B0011 · 157–160](../../../../tools/plot_experimental_report.py#L157) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |

## B0001

[Lines 1–17](../../../../tools/plot_experimental_report.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:dd6ebbdced97f3cb9b1bc02f2e54464ecbf9dd86aa5e4dbed51ee71a06c4ccb1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare static scientific plotting support without importing Matplotlib early. |
| inputs / outputs | Imports exact CSV/rational/hash/statistics helpers; bytecode writes are disabled for relocated read-only tools. |
| invariants | Matplotlib loads only after a new output/cache is selected. No benchmark or source mutation occurs during import. |
| ownership | Module state belongs to the Python plot process. |
| failure | Missing standard library support fails import; plotting dependency is checked later. |
| cost | Cold interpreter setup; excluded from all reported historical measurements. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0002

[Lines 18–20](../../../../tools/plot_experimental_report.py#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L20:sha256:771470ca6047ea7b84814e6cc23c2357b927e95ad29ed2fbd7b34f2969c68de4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject invalid plot admission or byte binding. |
| inputs / outputs | False predicate raises ValueError with a concrete message. |
| invariants | Invalid inputs are not repaired into empty or zero charts. |
| ownership | Borrows arguments and owns only a possible exception. |
| failure | Failure reaches the single plot CLI diagnostic boundary. |
| cost | Constant branch outside experiment timing. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0004

[Lines 23–25](../../../../tools/plot_experimental_report.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L25:sha256:1d0332a1d9055bae62af270d2a7698f8118c50a5215446e50040d3fecc7408f8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash actual plot input/output files using streamed SHA256. |
| inputs / outputs | A readable path returns the exact file digest. |
| invariants | The same helper binds input CSV/index bytes, plot files and the reused source module. |
| ownership | The context manager owns the temporary file handle; file contents remain unchanged. |
| failure | Missing/unreadable files or hash errors propagate. |
| cost | Linear file-byte work with streaming hash memory. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0006

[Lines 28–30](../../../../tools/plot_experimental_report.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L30:sha256:da8749d5a06f2115d9948ed361f4d930545c5edd1438443fde6b495bf06ee1a9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load one report-owned exact CSV table for plotting. |
| inputs / outputs | A CSV path becomes an ordered list of string-valued row dictionaries. |
| invariants | Rational conversion is deferred until a selected metric cell is displayed; unavailable cells remain identifiable. |
| ownership | Owns parsed rows and closes the input handle. |
| failure | File/CSV decoding errors propagate. |
| cost | Offline memory and parsing proportional to table cells/bytes. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0008

[Lines 33–144](../../../../tools/plot_experimental_report.py#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L144:sha256:1ff0ebb8350e274d4285acf77fdd5af988dc548e0cbb54327674f17465d8fa9c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render hash-bound portable PNG/PDF panels without conflating source/protocol families. |
| inputs / outputs | Report directory and fresh figure root produce B05 reused family/sentinel plots, newer study/facet panels, exact source-row ids, index and rendering provenance. |
| invariants | Input metric/index hashes are checked first. Agg/cache precede pyplot. B05 uses the existing reviewed API; other panels retain study/facet/series and actual units. Selected subsets are named. Medians and observed min/max are display floats, missing stays unavailable and zeros are not log-filtered. Legend/footer space and axis labels describe categorical coordinates. Manifest records actual font/backend/version and data/source hashes; figure-byte portability is not promised. |
| ownership | Owns new figure/cache files and temporary Matplotlib figures, closed after save. Historical sources and CSVs remain read-only; no child native program executes. |
| failure | Existing destination, changed inputs, absent Matplotlib/reused helper, malformed table values or render/I/O errors fail visibly; no empty success chart is substituted. |
| cost | Offline grouping/filtering and plotting work in table rows, series and output pixels. The implementation favors direct report code over a reusable runtime abstraction; these costs are not engine measurements. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [Refactor.md §11.11 B06](../../../../Refactor.md) |

## B0010

[Lines 147–156](../../../../tools/plot_experimental_report.py#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L147-L156:sha256:b33893c955befdd835b8ce9636147c56d7e5ca415ae33ccb07967c647a4c11c9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the report-to-figures command and one error boundary. |
| inputs / outputs | Required input/output paths invoke run and return zero only after actual figure publication. |
| invariants | The command never runs a measurement, creates no source fixture and accepts no preexisting output tree. |
| ownership | Owns argparse state; run owns its new plot output. |
| failure | Run failures print one diagnostic and return nonzero; no catch/retry stack is added. |
| cost | Cold CLI dispatch only. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0011

[Lines 157–160](../../../../tools/plot_experimental_report.py#L157); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L157-L160:sha256:8a794f2c6b77bf5133b639a55d99eb34900b5c835e6fff07e6a511fd4502719a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute plots only when invoked as a script. |
| inputs / outputs | Module guard raises SystemExit from main status. |
| invariants | Import supports reviewed function reuse without creating plots. |
| ownership | Interpreter module lifetime only. |
| failure | Propagates the documented success/failure process status. |
| cost | Constant dispatch. |
| Design | [tools/plot_experimental_report.py](../../../../tools/plot_experimental_report.py) |
