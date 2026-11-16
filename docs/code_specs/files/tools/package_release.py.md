# `tools/package_release.py` — block usage map

[Source](../../../../tools/package_release.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `0a68f4efab7c96fcc5d864ddd3e120432830f784f41e73c40cfe69bdd6aaeae7`. 252 lines partitioned into 13 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../tools/package_release.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–23](../../../../tools/package_release.py#L21) | Callable definition: def require(value, message): | calls ValueError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 24–25](../../../../tools/package_release.py#L24) | Explanatory comments or spacing. |  |
| [B0004 · 26–31](../../../../tools/package_release.py#L26) | Callable definition: def sha(path): | calls sha256, open, iter, read; returns digest.hexdigest(); 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 32–33](../../../../tools/package_release.py#L32) | Explanatory comments or spacing. |  |
| [B0006 · 34–37](../../../../tools/package_release.py#L34) | Callable definition: def positive(value): | calls int, require; guard require(number &gt; 0, 'grant must be positive'); returns number · [reviewed contract](#b0006) |
| [B0007 · 38–39](../../../../tools/package_release.py#L38) | Explanatory comments or spacing. |  |
| [B0008 · 40–52](../../../../tools/package_release.py#L40) | Callable definition: def regular_files(directory): | calls require, is_dir, sorted, rglob; guard require(directory.is_dir(), f'missing input directory: {directory}'); returns result; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 53–54](../../../../tools/package_release.py#L53) | Explanatory comments or spacing. |  |
| [B0010 · 55–62](../../../../tools/package_release.py#L55) | Callable definition: def arguments(): | calls ArgumentParser, in, add_argument, parse_args; returns parser.parse_args(); 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 63–64](../../../../tools/package_release.py#L63) | Explanatory comments or spacing. |  |
| [B0012 · 65–244](../../../../tools/package_release.py#L65) | Callable definition: def main(): | calls arguments, resolve, require, exists; guard require(not output.exists(), f'output already exists: {output}'); growth new; 23 loop sites · [reviewed contract](#b0012) |
| [B0013 · 245–252](../../../../tools/package_release.py#L245) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |

## B0001

[Lines 1–20](../../../../tools/package_release.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:35d0701af03b195b7c4ee2cd797a067362e14cf2c5b5344c59085438fbf15c60
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the offline R1/R2 candidate assembler and its selected source inventory policy. |
| inputs / outputs | Imports standard-library path, argument, compression, hash, JSON, regex, copy, subprocess and tar support. Declares six root source files, eleven maintained directories and ignored account/VCS/cache names. |
| invariants | Import alone launches no installer, native CLI, archive write or query. This inventory includes selected legacy pins later, not every historical legacy tree. |
| ownership | Module globals own immutable tuple/set configuration; factories in main own all subsequent files and process results. |
| failure | Syntax or unavailable interpreter modules fail import before main; there is no fallback provider. |
| cost | Cold Python import and small fixed configuration allocations; no query update-path work or S05 query-account charge. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

## B0002

[Lines 21–23](../../../../tools/package_release.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L23:sha256:fba5518dbbe127c5d736b6a2ef99ebbb28b24be84759bc3ce649d93a6815e637
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject one failed packaging precondition at its actual phase. |
| inputs / outputs | A condition and diagnostic string in; returns None when true, raises ValueError when false. |
| invariants | Performs no retry, rollback, input mutation or release acceptance. Earlier completed output is retained if a later requirement fails. |
| ownership | Borrows both arguments and creates only an exception on failure. |
| failure | False condition reaches the executable entry boundary as ValueError and exit1; direct imported callers receive the exception. |
| cost | Constant branch cost apart from message creation by the caller and failure allocation. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |

## B0004

[Lines 26–31](../../../../tools/package_release.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L31:sha256:7ec3c2faf6dfd2cb1de71315622f8b8653673cae5baf6b7afaa5902dbcd6c752
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute an exact SHA-256 digest without loading an entire payload into Python memory. |
| inputs / outputs | Path to a readable file in; lowercase hexadecimal digest of bytes read through EOF out. |
| invariants | Reads from a fresh binary stream in 1MiB chunks. It supplies content identity only, not source lineage, metadata identity or a concurrent atomic snapshot. |
| ownership | Context owns and closes the stream; the function owns one hash object and a bounded live read chunk. |
| failure | Open/read filesystem errors propagate; the executable entry reports OSError. No alternative hash or swallowed read error. |
| cost | O(file bytes) hashing/read time with 1MiB read scratch plus the hash state, outside native query accounts. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |

## B0006

[Lines 34–37](../../../../tools/package_release.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L37:sha256:c94ada77ab3b022f2fd77ab6170440dc5012f4aead8a5e0a53d3c3bb2539fca4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a positive integer CLI packaging grant. |
| inputs / outputs | Argument text in; Python int greater than zero out. |
| invariants | Zero and negatives never become disabled/unlimited grants. This is a host payload count/byte setting, not a native engine limit. |
| ownership | Owns the parsed immutable integer; no file/process owner is created. |
| failure | int conversion or positivity failure is reported by argparse as argument failure before main creates output. |
| cost | O(argument digits) parsing and Python integer representation; no payload or query traversal. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |

## B0008

[Lines 40–52](../../../../tools/package_release.py#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L52:sha256:a12f50a2b969c85995fee744c6db36d72a21552ea9e18b407fc1e9da2aebcec8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a sorted nonempty inventory of regular local files while excluding specified cache/account entries. |
| inputs / outputs | Directory path in; sorted Path list for eligible regular descendants out. |
| invariants | Directory must exist. Ignored path parts and pyc files are omitted. Eligible symlink entries reject, including directory links; other nonregular entries are not payload. Caller must keep directory membership quiescent for whole-image consistency. |
| ownership | Returns an owned Path list; it does not retain open file handles or copy file bytes. |
| failure | Missing/empty directory or an eligible symlink raises ValueError; traversal/stat filesystem errors propagate. There is no symlink-following fallback. |
| cost | Directory traversal plus O(F log F) path ordering and O(F) retained path metadata; payload bytes are not read here. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |

## B0010

[Lines 55–62](../../../../tools/package_release.py#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L62:sha256:d68b0b7c0b2fd2d6fa47ba26db2f4fe3dead9560ec59e34f9ea241cae722b706
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse explicit packaging inputs, a selected R1/R2 scope label and finite positive payload grants. |
| inputs / outputs | CLI arguments in; Namespace with six required Paths, profile default R1 from choices R1/R2, max-total-bytes default2GiB and max-files default50000 out. |
| invariants | The caller explicitly chooses report/figure/evidence inputs. Omitted and explicit R1 select the same branch. A profile is a declared package scope, not evidence qualification; positive grants still cover staged regular payload only. |
| ownership | Argparse owns parser/Namespace strings and Paths; filesystem/process ownership begins in main. |
| failure | Missing/unknown/invalid argument triggers argparse SystemExit before output creation; positivity conversion has no unlimited mode. |
| cost | Cold argument parsing proportional to argument text; fixed small configuration state. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

## B0012

[Lines 65–244](../../../../tools/package_release.py#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L244:sha256:57ec908f8e24ff3becbf9f3112edd8fe68fd1ee8fb20c2b90e327f5e345830d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble a versioned R1 or R2 candidate from explicit source, installed SDK and evidence inputs. |
| inputs / outputs | Resolved input Paths and positive grants in; fresh output containing command logs, staged source/SDK/report/figures/evidence, payload manifest/checksums, normalized tar.gz and candidate.json out. |
| invariants | Known source/role inventories and lower-bound grants are checked before output creation. R2 also requires its method/API guides and r2-report.md entry. Output must be new and outside maintained/evidence roots after resolution. Header/CMake versions, build-home association and the same exact-set CLI version/API string are checked. Profile selects only archive-root/README/manifest labels, without changing query defaults or granting acceptance. Copied content is checked during copy and at final closure. Inputs/output require caller serialization; this is not an atomic snapshot or proof arbitrary build bytes came from current source. Every profile remains candidate_unqualified/release_accepted=false. |
| ownership | Owns only the fresh output/stage, logs, manifests and archive. Source/evidence files are borrowed read-only. Installer may update its ordinary build-side install manifest; reusable producer inputs are not frozen. Payload/list/hash/compressor resources are offline host costs, not S05 query state. |
| failure | Preflight rejection creates no output. A later install/version/grant/copy/hash/compression/IO failure leaves inspectable partial new output and completed command logs; there is no cleanup/rollback or release-status promotion. Process termination can leave the last command without a completed receipt. |
| cost | Traverses/sorts metadata, installs SDK, repeatedly copies/hashes payload and streams tar/gzip, then hashes compressed output. Memory includes O(F) inventory/manifest/path data and bounded per-stream buffers; installer staging, metadata/archive sizes, time and process resources are outside payload grants. No query runtime branch, callback or shared state is introduced. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [include/crown/version.hpp](../../../../include/crown/version.hpp), [apps/crown/main.cpp](../../../../apps/crown/main.cpp), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

```text
    source, build = args.source.resolve(), args.build_dir.resolve()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve filesystem locations and reject output aliases before mutation. |
| inputs / outputs | Source/build/output and report/figure/evidence Paths plus selected profile in; validated resolved roots, captured evidence files, required R2 entry paths when selected, and declared version/API/build metadata out. |
| invariants | Resolution collapses parent components and ancestor symlinks before containment tests. Output cannot lie within maintained source or an evidence root. A missing CMAKE_HOME_DIRECTORY is rejected rather than defaulting to cwd. Version and CMake declarations must agree; cache association is a consistency check, not compiled-source proof. |
| ownership | Owns Path/configuration/list temporaries; reads existing source/header/CMake/cache files only. |
| failure | Bad path/inventory/profile-required-guide/report-entry/version/build-home inputs reject before output.mkdir; read/parse failures propagate to the entry boundary. |
| cost | Metadata traversal/sort and small header/cache reads before writes; not a process-wide work/byte grant. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [include/crown/version.hpp](../../../../include/crown/version.hpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

```text
    source_files = {source / name for name in SOURCE_ROOT_FILES}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture the source closure and authenticate the manifest-selected historical baseline inputs. |
| inputs / outputs | Maintained tree, six root files, baseline source_sha256_local mapping and root PDFs in; deduplicated source-file set out. |
| invariants | Baseline paths must be relative with no parent component; each must be regular, nonsymlink and match its pinned content hash. Current maintained files are copied as current bytes; selected legacy sources remain exact pins. Root build/VCS/account trees are not swept into the source image. |
| ownership | Owns an inventory of Path handles, not open descriptors or a copied source tree at this phase. |
| failure | Invalid/missing/symlink source or mismatched baseline hash rejects before output creation; malformed manifest/IO errors propagate. |
| cost | O(F) path/stat state, directory sorting and complete reads of pinned baseline bytes; cold host work. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [dependencies.lock.json](../../../../dependencies.lock.json) |

```text
    known_inputs = [*source_files, *(path for _, paths in roles.values() for path in paths)]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject already-known impossible payload grants before installation or output mutation. |
| inputs / outputs | Source set and each role file list plus max-files/max-total-bytes in; successful lower-bound count/size admission out. |
| invariants | Each separate staged copy counts, even if roles share an original. Count reserves one README file. SDK count/bytes and actual README bytes are not yet known; later record checks still govern the complete payload and may fail after staging. |
| ownership | Owns a temporary flattened Path list; no file content or installer staging is allocated here. |
| failure | Known count or byte exceedance raises ValueError before output.mkdir; stat failure propagates. This does not promise that every possible later grant denial is preflighted. |
| cost | O(F) temporary path entries/stat visits and Python integer summation; no byte hashing or native execution. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |

```text
    def run(command):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one actual offline installation/version command and retain its completed receipt. |
| inputs / outputs | Argument sequence in; exclusive numbered stdout/stderr files, appended argv/exit receipt in commands.json and no return payload out. |
| invariants | No shell interpolation. On completed subprocess return, both logs close before the receipt is saved and exit0 is required. Receipt recording is completion-based; kill/launch/write failure may leave logs without a completed row. |
| ownership | Context owns both binary log streams; subprocess owns its child execution. Parent owns commands list and output metadata. |
| failure | Nonzero exit raises ValueError naming retained stderr. Launch, log or receipt write failure propagates; there is no retry or rollback of installer/partial output. |
| cost | Waits for actual command completion; installer/CLI CPU, logging and metadata rewrite costs are host work, not historical benchmark observations. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [apps/crown/main.cpp](../../../../apps/crown/main.cpp) |

```text
    run(['cmake', '--install', build, '--prefix', stage / 'sdk'])
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the explicit producer build and check the installed CLI project/API string. |
| inputs / outputs | Build directory in; stage/sdk plus retained cmake-install and crown--version logs out. |
| invariants | Installed version text must exactly match declared project version/API and the existing exact-set CLI format in both profiles. The package profile does not rewrite the CLI identity. Installation precedes SDK payload charging and does not itself qualify source lineage or release acceptance. |
| ownership | Installer populates only the fresh package SDK prefix plus ordinary build-side installation metadata; the subsequent subprocess executes its installed CLI. |
| failure | Installer/CLI failure or exact version/API mismatch aborts with partial output/logs retained. A matching version is not a substitute for later fresh-source/SDK receiving. |
| cost | Actual native installation and one version command; SDK materialization can precede payload-grant rejection by explicit design. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [apps/crown/main.cpp](../../../../apps/crown/main.cpp), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

```text
    def record(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge and hash one staged regular payload file for the manifest. |
| inputs / outputs | Staged Path in; checked total_bytes increment and path/size/SHA row appended to payload. |
| invariants | File count is checked before append and remaining byte grant before increment. Python integers do not wrap. Only regular staged SDK/source/role/README files are payload; generated manifest/checksums/archive/logs are separate declared metadata. |
| ownership | Owns one payload row and cumulative count/byte state; SHA helper owns its transient read stream. |
| failure | Count/byte excess raises before state increment. Stat/hash failure propagates; if a hash fails after increment, the enclosing candidate construction aborts rather than publishing successful metadata. |
| cost | One stat plus O(file bytes) SHA read and O(path length) retained row metadata; payload totals do not bound Python/process or disk metadata resources. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |

```text
    def copy(original, relative):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one source/evidence file into its disjoint staged role while checking content stability. |
| inputs / outputs | Original Path and safe relative destination produced by main in; copied mode-normalized target, original-content closure pin and recorded payload row out. |
| invariants | Count/byte admission is checked before target copy. Successful copy requires target hash and re-read original hash to equal the pre-copy hash; targets receive0755 for executable inputs and0644 otherwise. A later whole-input recheck covers selected originals. It is not an atomic membership/metadata snapshot under concurrent external writers. |
| ownership | Owns target directory/file and closure tuple; borrows original read-only. Relative destinations come from source/role relative_to roots, not unvalidated arbitrary paths. |
| failure | Grant, copy/chmod, hash mismatch or record failure aborts and retains the partial fresh stage; no source edit or generic rollback handler. |
| cost | One physical copy plus four complete hash passes on success through copy/record, followed by a later caller original-hash closure pass. O(F) retained closure/manifest metadata; SHA scratch remains bounded. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |

```text
    for path in regular_files(stage / 'sdk'):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Account the installed SDK, exclude private test archives and copy each declared source/evidence role. |
| inputs / outputs | Fresh installed SDK inventory, sorted source set and sorted per-role paths in; disjoint sdk/source/report/figures/evidence payload entries out. |
| invariants | SDK regular files are charged after installation. Testing-named .a and libcrown_reference.a are rejected. This check is not an audit of arbitrary library ABIs; independent relocated-consumer validation remains required. Role/source relative paths cannot collide with each other at stage root. |
| ownership | Stage owns every installed/copied file. Input roots remain borrowed; immutable source handles are not native query owners. |
| failure | SDK symlink/empty/private archive, quota or copy failure aborts with inspectable partial SDK/stage; no silent exclusion of a failed input. |
| cost | SDK inventory/hash traversal plus complete source/role copies; sorting/inventory and repeated byte reads are explicit offline packaging costs. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake) |

```text
    readme = stage / 'README.md'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write the candidate entry points while preserving the distinction between packaging and qualification. |
| inputs / outputs | Declared version, selected profile and previously selected scope/guide/report strings in; staged README with source/SDK/report/figure entry points and explicit ABI, rights and historical-link limits out. |
| invariants | README calls every archive unqualified. R1 text remains byte-identical for the same version; R2 describes the admitted native SQL bag/COUNT/SUM/AVG workflows and bounded contracts while preserving the exact-set CLI identity/defaults. Separately gated interfaces, system libraries and historical old-path fallback are not granted by these links. Input report/evidence content still requires independent qualification. |
| ownership | Stage owns the generated text and its charged payload row. |
| failure | Write or subsequent payload-grant failure aborts; generated text does not create release acceptance. |
| cost | Small generated text allocation/write and ordinary record hash/charge; separate from native query work. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

```text
    require(all(sha(path) == expected for path, expected in originals), 'input closure changed')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recheck all selected original content before emitting final candidate metadata. |
| inputs / outputs | Original/hash tuples recorded by successful copies in; all selected contents still match or a ValueError out. |
| invariants | Checks every selected original at this phase and does not refund prior work. It does not re-enumerate directory membership, authenticate system/build bytes or lock an input filesystem; caller keeps inputs/stage serialized. |
| ownership | Borrows closure tuples and each original file; SHA stream closes for each visit. |
| failure | First changed original or read failure aborts without final successful candidate metadata; partial stage remains inspectable. |
| cost | One additional full SHA read per selected original, O(total original bytes) time with bounded live stream scratch. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |

```text
    manifest = {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the exact regular payload and declared packaging/build boundary without granting release status. |
| inputs / outputs | Sorted payload rows, declared version/API, observed cache configuration/compiler and actual charged totals in; release-manifest.json out. |
| invariants | schema_version1/kind crown_release_candidate_v1 and the chosen profile R1/R2 are explicit; status remains candidate_unqualified and release_accepted false. Build fields are cache observations, not verified compiler transcripts. Profile labels do not change runtime, height defaults, payload grants or semantic/evidence acceptance. |
| ownership | Stage owns deterministic sorted-key JSON metadata; the in-memory manifest shares payload rows already owned by main. |
| failure | JSON/write failures propagate; presence of a manifest is not proof of source lineage, passed tests, valid benchmark data or a complete release decision. |
| cost | O(F) row/path/hash metadata serialization and output size, excluded from regular payload-byte/count grants. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

```text
    checksums = [(row['path'], row['sha256']) for row in payload]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create sorted payload-plus-manifest checksum metadata without self-referential hashing. |
| inputs / outputs | Payload path/SHA rows and actual release-manifest bytes in; CHECKSUMS.sha256 rows sorted by relative path out. |
| invariants | Every charged payload plus release-manifest is listed. CHECKSUMS excludes itself; the later outer archive SHA covers it. Checksums identify bytes, not semantic correctness or qualification. |
| ownership | Owns an extra O(F) checksum list/string and the staged checksum file. |
| failure | Manifest-read/hash or checksum write failure aborts; there is no alternate checksum interpretation or release promotion. |
| cost | O(F log F) path sorting, O(metadata bytes) string construction/write and one manifest hash, all outside payload grant. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |

```text
    archive = output / (name + '.tar.gz')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream a deterministic regular-file candidate tar/gzip with normalized metadata. |
| inputs / outputs | Complete quiescent stage in; exclusive output tar.gz with one versioned root and sorted regular members out. |
| invariants | Uses USTAR regular files, uid/gid/mtime0 and empty owner names from TarInfo defaults, normalized0755/0644 executable modes, gzip filename empty/mtime0/compresslevel6. No source mtimes/uid/gid are copied. Identical staged bytes/modes and the same Python/zlib context determine archive bytes; no cross-compressor guarantee or compiled-binary reproducibility is implied. |
| ownership | Nested contexts own and close exclusive outer file, gzip compressor, tar stream and one current member stream. Stage stays for inspection after completion/failure. |
| failure | Unsupported USTAR names, changed/missing stage input, disk/write/compressor errors abort with partial output retained; this stream does not create a rollback framework or accepted release. |
| cost | O(F log F) stage inventory plus full staged-byte read/compression/write; tar/gzip buffers and member list are host memory. Compressed archive and filesystem space are excluded from payload grants. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |

```text
    result = {'status': 'candidate_unqualified', 'archive': archive.name,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the completed archive byte identity and packaging totals as an unqualified candidate receipt. |
| inputs / outputs | Closed archive and release manifest in; candidate.json plus stdout JSON with SHA/byte totals and candidate_unqualified out. |
| invariants | Archive closes before hashing/reporting. The result field set is unchanged for both profiles: the archive suffix and embedded manifest carry profile identity; no redundant top-level result profile is added. Totals cover regular payload only; no field says tests passed or release accepted. Logs/stage/archive remain for independent receiving. |
| ownership | Output directory owns candidate metadata and archive; returned print serialization creates only temporary host strings. |
| failure | Archive/manifest hash, metadata write or stdout error can fail after a complete archive exists; the failure does not erase or automatically qualify it. |
| cost | One O(compressed archive bytes) hash plus a small manifest hash and metadata write/print; no new native benchmark or query execution. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

```text
    if args.profile == 'R2':
        for name in
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the selected R2 package entry documents before any output mutation. |
| inputs / outputs | Resolved source/report roots and profile in; five source-guide existence checks and r2-report.md existence admission out. |
| invariants | Only R2 runs this branch; default/explicit R1 keep their original input requirements. Existing source/role enumeration separately rejects eligible symlink entries. Presence supplies a link target, not truthful report contents or release acceptance. |
| ownership | Borrows Path roots and fixed name literals; creates no native object or file. |
| failure | Missing selected guide or report entry raises ValueError before output.mkdir. |
| cost | Five small path checks plus one report-entry check; cold packaging work. |
| Design | [tools/package_release.py](../../../../tools/package_release.py), [tests/integration/release_package.py](../../../../tests/integration/release_package.py), [docs/releases/r1.md](../../../releases/r1.md), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

```text
    output.mkdir()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the one selected candidate namespace after preflight. |
| inputs / outputs | New resolved output path, parsed profile and declared version in; output/stage directories plus empty command ledger out. |
| invariants | Lowercase profile suffix names exactly one -r1 or -r2 stage. No accepted historical artifact is replaced and no query/runtime state is changed. |
| ownership | Main owns the new directories and ledger; callers must serialize inputs/output. |
| failure | Directory creation races or IO errors abort, retaining any newly created prefix; no replacement/retry. |
| cost | Fixed directory operations and version/profile path construction before actual install. |
| Design | [tools/package_release.py](../../../../tools/package_release.py), [tests/integration/release_package.py](../../../../tests/integration/release_package.py), [docs/releases/r1.md](../../../releases/r1.md), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

```text
    profile_scope = ('R1 covers
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the profile-specific README strings without varying package execution. |
| inputs / outputs | Parsed profile in; scope paragraph, guide links and report entry string out. |
| invariants | R1 defaults reproduce the original literal. R2 names exact native SQL workflows, their bounded contracts and separate CLI identity; profile labels never enable a backend or validate evidence. |
| ownership | Local immutable strings live through README serialization only. |
| failure | Ordinary string allocation failure propagates; these assignments have no filesystem effect. |
| cost | Fixed-sized cold string/reference selection, independent of database/input/output cardinality. |
| Design | [tools/package_release.py](../../../../tools/package_release.py), [tests/integration/release_package.py](../../../../tests/integration/release_package.py), [docs/releases/r1.md](../../../releases/r1.md), [docs/releases/r2.md](../../../releases/r2.md), [docs/r2_compatibility.md](../../../r2_compatibility.md), [Refactor.md §11.12 V04](../../../../Refactor.md) |

## B0013

[Lines 245–252](../../../../tools/package_release.py#L245); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L245-L252:sha256:6816390bff4cc352123e7f4a3423b4d770d3770fc76dac0f75fa2381c8c3fac0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the assembler as a script and provide one concise packaging failure boundary. |
| inputs / outputs | __name__ guard invokes main; successful main prints candidate JSON and exits normally. Caught ValueError/OSError/SubprocessError prints its message to stderr and exits1. |
| invariants | Import does not enter main. Catches are at the offline executable boundary, not per-file/query retries. No catch claims cleanup or a valid archive after failure; argparse SystemExit and interrupts retain their own behavior. |
| ownership | Main owns all output resources; the wrapper owns only the caught exception and diagnostic. |
| failure | Expected packaging/IO/subprocess exceptions are reported. Programming errors outside the selected classes and process interruption are not silently converted into passing results. |
| cost | Fixed guard/exception-dispatch overhead plus main on script execution; zero native query execution work. |
| Design | [docs/releases/r1.md](../../../releases/r1.md), [Refactor.md §11.12 V03](../../../../Refactor.md) |
