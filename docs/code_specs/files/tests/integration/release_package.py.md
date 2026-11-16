# `tests/integration/release_package.py` — block usage map

[Source](../../../../../tests/integration/release_package.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c20f463ec305040f7e19c4afe0049e38da05922f4911aca9922fa1bc4f00bb9d`. 312 lines partitioned into 21 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/integration/release_package.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 19–20](../../../../../tests/integration/release_package.py#L19) | Callable definition: def archive_root(profile): | calls lower; returns 'crown-next-0.1.0-' + profile.lower() · [reviewed contract](#b0002) |
| [B0003 · 21–22](../../../../../tests/integration/release_package.py#L21) | Explanatory comments or spacing. |  |
| [B0004 · 23–25](../../../../../tests/integration/release_package.py#L23) | Callable definition: def require(value, message): | calls RuntimeError; guard def require(value, message): · [reviewed contract](#b0004) |
| [B0005 · 26–27](../../../../../tests/integration/release_package.py#L26) | Explanatory comments or spacing. |  |
| [B0006 · 28–33](../../../../../tests/integration/release_package.py#L28) | Callable definition: def digest(path): | calls sha256, open, iter, read; returns result.hexdigest(); 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 34–35](../../../../../tests/integration/release_package.py#L34) | Explanatory comments or spacing. |  |
| [B0008 · 36–37](../../../../../tests/integration/release_package.py#L36) | Callable definition: def canonical(value): | calls dumps; returns json.dumps(value, sort_keys=True, ensure_ascii=False, separators=(',', ':')) · [reviewed contract](#b0008) |
| [B0009 · 38–40](../../../../../tests/integration/release_package.py#L38) | declares types or opens a type body. |  · [reviewed contract](#b0009) |
| [B0010 · 41–42](../../../../../tests/integration/release_package.py#L41) | Callable definition: def __init__(self, base): | calls  · [reviewed contract](#b0010) |
| [B0011 · 43–43](../../../../../tests/integration/release_package.py#L43) | Explanatory comments or spacing. |  |
| [B0012 · 44–56](../../../../../tests/integration/release_package.py#L44) | Callable definition: def run(self, arguments, success=True): | calls list, map, str, len; guard require((child.returncode == 0) == success,; returns child.stdout · [reviewed contract](#b0012) |
| [B0013 · 57–58](../../../../../tests/integration/release_package.py#L57) | Explanatory comments or spacing. |  |
| [B0014 · 59–139](../../../../../tests/integration/release_package.py#L59) | Callable definition: def inspect_archive(archive, destination, source, build, compiler, sanitize, profile='R1'): | calls archive_root, open, read, require; guard require(header\[:3\] == b'\x1f\x8b\x08' and len(header) == 10 and; returns manifest, hashes; 13 loop sites · [reviewed contract](#b0014) |
| [B0015 · 140–141](../../../../../tests/integration/release_package.py#L140) | Explanatory comments or spacing. |  |
| [B0016 · 142–154](../../../../../tests/integration/release_package.py#L142) | Callable definition: def sqlite_prefixes(sql, events): | calls connect, execute, r, KEY; returns snapshots; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 155–156](../../../../../tests/integration/release_package.py#L155) | Explanatory comments or spacing. |  |
| [B0018 · 157–209](../../../../../tests/integration/release_package.py#L157) | Callable definition: def installed_consumer(base, package, source, build, compiler, sanitize, runner): | calls require, run, list, rglob; guard require(runner.run(\[sdk / 'bin/crown', '--version'\]) ==; returns len(events); growth insert; 6 loop sites · [reviewed contract](#b0018) |
| [B0019 · 210–211](../../../../../tests/integration/release_package.py#L210) | Explanatory comments or spacing. |  |
| [B0020 · 212–304](../../../../../tests/integration/release_package.py#L212) | Callable definition: def main(): | calls ArgumentParser, in, add_argument, parse_args; guard require(sorted(p.name for p in occupied.iterdir()) == \['marker'\] and; returns 0; 10 loop sites; source comment (unverified): # Small documentation fixtures exercise portable entry paths, not report qualification. · [reviewed contract](#b0020) |
| [B0021 · 305–312](../../../../../tests/integration/release_package.py#L305) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |

## B0001

[Lines 1–18](../../../../../tests/integration/release_package.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:1bd40400b73b849be5761f4958b276ee5523e37843551d455800dd38793e74c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the independent standard-library archive/install regression and suppress bytecode-cache writes. |
| inputs / outputs | Python imports and sys.dont_write_bytecode setting in; offline byte-check and later native-receiving definitions out. |
| invariants | No native command or filesystem mutation executes on import; packaging remains candidate_unqualified. |
| ownership | Module owns imported names and changes the process bytecode-cache flag; it creates no native query owner, artifact directory or process. |
| failure | Import/syntax failures propagate; the guarded entry point owns runtime diagnostics. |
| cost | Fixed import/name setup; native/IO work occurs only inside explicit calls. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

## B0002

[Lines 19–20](../../../../../tests/integration/release_package.py#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def archive_root(profile):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive the expected current-version archive root for an internal profile fixture. |
| inputs / outputs | Internally selected R1/R2 string in; crown-next-0.1.0-r1 or -r2 string out. |
| invariants | This helper only names expected bytes; it does not admit user profiles or grant release status. Producer argparse is separately exercised for allowed choices. |
| ownership | Returns a new short string; retains no file or query owner. |
| failure | Invalid nonstring caller may fail lower(); defined fixture callers use R1/R2. |
| cost | O(profile length) lowercase/concatenation; fixed tiny fixture input. |
| Design | [tools/package_release.py](../../../../../tools/package_release.py), [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [docs/releases/r1.md](../../../../releases/r1.md), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

## B0004

[Lines 23–25](../../../../../tests/integration/release_package.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L25:sha256:8b14f7d5eb0d9a9cafc6d1aaa990a73bad9c261d2c3c97d6713ed7fa789c829b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop a failed independent assertion with one clear diagnostic. |
| inputs / outputs | Truth value and message in; normal return only for a passing predicate. |
| invariants | A failing condition is never accepted as a partial pass. |
| ownership | Borrows values and allocates only exception/diagnostic state on failure. |
| failure | Raises RuntimeError on false and relies on the single CLI boundary. |
| cost | Constant assertion dispatch plus diagnostic allocation on failure. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json) |

## B0006

[Lines 28–33](../../../../../tests/integration/release_package.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L33:sha256:661038cc62ebac05d4d93067fa60807689034325c7c524cb1701bd0d65179402
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash actual file bytes independently of the packager manifest. |
| inputs / outputs | Readable Path in; lowercase SHA-256 digest out. |
| invariants | The digest follows complete streamed file bytes, not path/mtime metadata. |
| ownership | Local binary handle closes on return or exception; no retained payload copy. |
| failure | File/hash errors propagate without changing the input. |
| cost | O(file bytes) reads/hash work with fixed1MiB chunk scratch; Python3.10-compatible streaming SHA-256. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json) |

## B0008

[Lines 36–37](../../../../../tests/integration/release_package.py#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L37:sha256:e367d4632aef975ad9f1a4b78bf4fb95007e9c9a59f432aa902a5dfd27cacd7a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize catalog bindings, typed test events and comparison diagnostics deterministically. |
| inputs / outputs | JSON-compatible object in; UTF-8-preserving sorted compact JSON text out. |
| invariants | Boolean/integer/string distinctions follow JSON values; dict ordering/whitespace do not alter catalog binding bytes. |
| ownership | Returned ordinary Python string belongs to the test caller. |
| failure | JSON serialization errors propagate to the sole CLI boundary. |
| cost | Visits the object and allocates its complete encoded text; cold test work. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json) |

## B0009

[Lines 38–40](../../../../../tests/integration/release_package.py#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L40:sha256:ebde8752a2d53f01943739f1976c559e17dd91575f6b85791742263a76b05795
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group subprocess recording for the one regression artifact owner. |
| inputs / outputs | Class declaration in; Runner methods share one artifact root and ordered records list. |
| invariants | Commands use explicit argv without a shell and each finished child has saved raw streams. |
| ownership | Instances own record lists and the path handle, not native query ownership. |
| failure | Method errors propagate; no retry or rollback framework is introduced. |
| cost | Class/name declaration only; instance/process work occurs in methods. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json) |

## B0010

[Lines 41–42](../../../../../tests/integration/release_package.py#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L42:sha256:c26133ad86338f13dbd6d31cc3c8e243e5113b5a840879c82d8e7b4291177043
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind command evidence to the newly allocated regression directory. |
| inputs / outputs | Artifact directory in; empty ordered process record ledger out. |
| invariants | No command runs while constructing the logger. |
| ownership | Instance retains base Path and owns its fresh records list. |
| failure | Ordinary allocation failures propagate. |
| cost | Fixed instance/list setup. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json) |

## B0012

[Lines 44–56](../../../../../tests/integration/release_package.py#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L56:sha256:d2b9964edbf0d69c6e30c741279995d84466f4ebddc7602a56c0a716de1742fd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one requested producer/consumer or negative control and retain its actual status/raw hashes. |
| inputs / outputs | Argv iterable and expected success boolean in; stdout text out after status admission. |
| invariants | Uses no shell; a nonzero child is accepted only for an explicitly negative control. Records are saved before asserting status. |
| ownership | subprocess.run waits for its direct child; instance retains command records and raw files in the exclusive artifact root. |
| failure | Timeout/IO/process failures propagate; unexpected exit status raises. No failed child is relabeled as a pass. |
| cost | Actual external-command cost plus complete stdout/stderr writes, hashes and cumulative small-ledger JSON serialization. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json) |

## B0014

[Lines 59–139](../../../../../tests/integration/release_package.py#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L139:sha256:3c014f6abf3063ff638a1a98750408135c343cb533326e7ca2e40f3ed50efe60
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently extract and authenticate the candidate payload, canonical tar/gzip metadata, full source prerequisites and baseline pins. |
| inputs / outputs | Archive, new destination, actual source/build/compiler/sanitizer and expected profile (default R1) in; validated manifest and actual member hash map out. |
| invariants | Only regular canonical nonescaping unique members under the expected version/profile root are extracted. Unqualified status/API/version/profile, observed build, manifest, checksums, complete maintained source and baseline pins must agree. README profile/relative destinations exist. For R2, the expected method/report/CLI boundary and public recovery target names appear in installed metadata; this is not execution of the SQL bag/aggregate APIs or release qualification. |
| ownership | Owns extraction files and temporary hash/index maps; uses streamed member copies and closes archive/file handles. |
| failure | Malformed/missing/mismatched metadata, files, source pins or permissions fail before any receiving success; partial new extraction remains inspectable in retained mode. |
| cost | Full archive decompression/write/hash, all original maintained-file hashes and manifest/CHECKSUMS metadata; O(member count) Python index memory, no native work. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

```text
    readme = (destination / 'README.md').read_text()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the extracted entry-page profile and its promised local destinations. |
| inputs / outputs | Extracted files, expected profile and actual README text in; passing page/link and optional R2-target-name checks out. |
| invariants | Every generated Markdown destination must be a file. R2 points to r2-report.md/r2 method and explains stable CLI identity. Installed target-name presence is an export-shape check, not SQL API execution or qualification. |
| ownership | Owns short README/config text and one-at-a-time regex matches; borrows the extracted tree. |
| failure | Missing/mismatched page, link, config or target fails independent receiving; no successful receipt. |
| cost | Reads short README/config files and performs one stat per page link; no native command. |
| Design | [tools/package_release.py](../../../../../tools/package_release.py), [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [docs/releases/r1.md](../../../../releases/r1.md), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

## B0016

[Lines 142–154](../../../../../tests/integration/release_package.py#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L142-L154:sha256:757cf95cda65908e7426379a49bcaae22712f9b71045ea0cbe6636021adb10ba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute independent set-SQL states for every physical trace prefix. |
| inputs / outputs | Unseen SQL and ordered pair-table events in; thirteen ordered logical snapshots out. |
| invariants | SQLite tables enforce exact pair identity; INSERT OR IGNORE and DELETE match native duplicate/absent no-ops; no native planner/runtime helper is used. |
| ownership | Owns one in-memory SQLite database and materialized expected rows, then closes the database. |
| failure | SQLite/schema/SQL errors propagate rather than creating default expected results. |
| cost | One SQLite statement and exact query materialization/sort per finite input prefix; no benchmark measurement. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json) |

## B0018

[Lines 157–209](../../../../../tests/integration/release_package.py#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L157-L209:sha256:bd3641cb30016d27807e8929806eede33ba60294f3afe0924e9f82b171dd6bea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the extracted relocated set-workflow example and verify unseen set SQL and durable prefix continuation against SQLite in either package profile. |
| inputs / outputs | Extracted package, original producer paths, compiler/sanitizer and command logger in; verified prefix count out. |
| invariants | The fixed packaged example links the extracted SDK using strict C++23 flags. Its observed command/link text must exclude original producer/source/build include/link roots and private/reference archives; this helper does not parse the compiler dependency file. Every fresh-process result checks API, sequence, durable verification, source offsets and SQLite set rows. The R2 call verifies retained R1 set compatibility, not SQL bag/aggregate Session behavior. |
| ownership | Owns outside-source/build, bound trace, local generation root/sink and child receipts under the new regression root; SQL results are decoded into test-owned JSON. |
| failure | Configure/build/version/admission/durability/output mismatches propagate; no partial state is called successful. |
| cost | One external consumer compile plus thirteen genuine run/restore processes; each performs actual compile/proof/recovery/delivery. Finite test costs, not controlled performance data. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

## B0020

[Lines 212–304](../../../../../tests/integration/release_package.py#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L212-L304:sha256:5f4cc3a1e73bcc4a7948cc1ea13b832de708fa45dfd70753be4fd7746c3fc2d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Coordinate profile-aware package denials, actual default/explicitR1 archive equality and full R1/R2 layout plus relocated set compatibility receiving. |
| inputs / outputs | SOURCE BUILD COMPILER SAN and optional new artifact path in; PASS receipt/stdout and zero status out only after all controls. |
| invariants | All original occupied/missing/symlink/aliased-output/unknown-option/tiny-grant negatives remain. Unknown profile and missing R2 report entry deny before output creation. Default/explicit R1 actual archives must hash identically under the same input point. R2 archive/source/role/hash/manifest/README/public-target checks remain unqualified. Both extracted SDKs run the set workflow; independent R2 SQL bag/aggregate qualification stays separate. Documentation fixture aliases are byte copies, not synthetic measured data. |
| ownership | Exclusive retained directory owns all artifacts, or TemporaryDirectory cleans on both success/failure. Runner owns command logs; candidate remains unqualified. |
| failure | Argument/IO/native/assertion failures reach the single entry boundary; retained partial evidence is not deleted or overwritten. |
| cost | Three genuine SDK installations/package archives (default R1, explicit R1 and R2), two full archive/source inspections and two outside consumer compiles with thirteen fresh-process prefixes each. Preflight negatives avoid installation. Temporary retained disk trees and repeated copy/hash/compression work are cold test resources, not a query-path or timing claim. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

```text
        # Small documentation fixtures exercise portable entry paths, not report qualification.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize small exact documentation aliases for expected report/figure entry names. |
| inputs / outputs | Repository report/component documentation in; report.md, r2-report.md and figures/index.md copies out. |
| invariants | Copied bytes remain documentation fixtures; neither a qualified full report nor synthetic performance data is created. Both profile packages receive the same role input point. |
| ownership | Regression owns new role files inside its context-owned or retained artifact directory. |
| failure | Copy/IO failure propagates before candidate command execution. |
| cost | Three ordinary cold file copies; no query or measurement run. |
| Design | [tools/package_release.py](../../../../../tools/package_release.py), [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [docs/releases/r1.md](../../../../releases/r1.md), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

```text
        unknown_profile = base / 'unknown-profile'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise profile-specific preflight refusal without weakening existing negative controls. |
| inputs / outputs | Profile R3 and an R2 report directory lacking its required entry in; two expected-failing process records out. |
| invariants | Unknown profile and missing R2 entry must leave their requested output paths absent. No negative child is counted as positive package/SQL coverage. |
| ownership | Owns one small missing-entry fixture directory and recorded subprocess results. |
| failure | Unexpected success or any created output fails the regression through require. |
| cost | Two cold Python argument/preflight processes and one documentation copy, with no SDK installation. |
| Design | [tools/package_release.py](../../../../../tools/package_release.py), [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [docs/releases/r1.md](../../../../releases/r1.md), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

```text
        explicit_r1 = base / 'candidate-explicit-r1'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive byte identity of default and explicit R1 packaging at one fixed input point. |
| inputs / outputs | Completed default R1 archive and identical explicit-R1 input arguments in; one additional candidate archive and exact SHA equality assertion out. |
| invariants | Equality compares actual compressed bytes in the same Python/zlib/input/build context. It does not claim equality to an older accepted R1 archive or cross-toolchain reproducibility. |
| ownership | Owns the second fresh output path; preserves the default candidate and all command logs. |
| failure | Installer/packager failure or unequal actual archive digests fails the regression. |
| cost | One complete install/copy/hash/compression plus both archive hashes; no additional SQL consumer here. |
| Design | [tools/package_release.py](../../../../../tools/package_release.py), [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [docs/releases/r1.md](../../../../releases/r1.md), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

```text
        r2_output = base / 'candidate-r2'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive the explicit R2 package image and rerun its retained set-SQL compatibility workflow. |
| inputs / outputs | Same source/build/roles plus R2 selector in; separately extracted and fully hashed R2 image, exact role checks and thirteen set-SQL prefixes out. |
| invariants | R2 root/manifest/README remain unqualified and match actual files. The public set-workflow receiver validates unchanged CLI/default behavior; independent SQL bag/aggregate/numeric/recovery qualification is separately joined by root. |
| ownership | Owns a fresh R2 output plus isolated extraction/consumer/state subtree; shares only the command-evidence logger. |
| failure | Any packaging, extraction, role-byte, compile, set-oracle or progress/recovery mismatch fails without promoting release status. |
| cost | One full package/source inspection and outside strict consumer compile with thirteen processes; cold correctness testing only. |
| Design | [tools/package_release.py](../../../../../tools/package_release.py), [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [docs/releases/r1.md](../../../../releases/r1.md), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

```text
        receipt = {'status': 'PASS_independent_release_archive_install_SQLite_receiving'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish only the completed profile/package/set-compatibility fixture results. |
| inputs / outputs | Passed controls, default/explicitR1 equality, R1/R2 actual archives/manifests and prefix counts in; JSON file/stdout receipt out. |
| invariants | Existing top-level R1 archive/payload/prefix fields retain their meanings. Nested R2 fields state set compatibility and package/export scope only; both release_accepted values stay false. |
| ownership | Owns one small summary object and serialized text in the artifact context. |
| failure | Write/stdout failure propagates; no receipt is emitted before all preceding controls pass. |
| cost | Small JSON serialization plus explicitly repeated archive SHA reads; no new native call. |
| Design | [tools/package_release.py](../../../../../tools/package_release.py), [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [docs/releases/r1.md](../../../../releases/r1.md), [docs/releases/r2.md](../../../../releases/r2.md), [docs/r2_compatibility.md](../../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../../Refactor.md) |

## B0021

[Lines 305–312](../../../../../tests/integration/release_package.py#L305); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L305-L312:sha256:b1baa28b67ece33418e52dc544de41a5dac041a95b3304787b8a6ded606f53c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the independent regression as a script and report one concise failure boundary. |
| inputs / outputs | __name__ guard invokes main; its status becomes process exit status. |
| invariants | Import is inactive; only completed receiving returns success. Argparse SystemExit keeps its own usage status. |
| ownership | main owns temporary/retained artifacts; this boundary only formats final exception text. |
| failure | Exception prints stderr and exits1; does not catch BaseException or hide failed controls. |
| cost | Fixed wrapper/diagnostic overhead around the explicit regression. |
| Design | [tests/integration/release_package.py](../../../../../tests/integration/release_package.py), [tools/package_release.py](../../../../../tools/package_release.py), [Refactor.md](../../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [examples/native-workflow/CMakeLists.txt](../../../../../examples/native-workflow/CMakeLists.txt), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp), [docs/cli.md](../../../../cli.md), [benchmarks/legacy/manifest.json](../../../../../benchmarks/legacy/manifest.json) |
