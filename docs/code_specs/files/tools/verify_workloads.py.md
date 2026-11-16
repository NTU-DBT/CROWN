# `tools/verify_workloads.py` — block usage map

[Source](../../../../tools/verify_workloads.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `8fd52cc7319983ae5f11b45f057db483c059df9078bbf85d5e9d7324b5aedf9f`. 264 lines partitioned into 21 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../tools/verify_workloads.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–22](../../../../tools/verify_workloads.py#L21) | Callable definition: def require(value, message): | calls ValueError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 23–24](../../../../tools/verify_workloads.py#L23) | Explanatory comments or spacing. |  |
| [B0004 · 25–26](../../../../tools/verify_workloads.py#L25) | Callable definition: def canonical(value): | calls dumps; returns json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(',', ':')) · [reviewed contract](#b0004) |
| [B0005 · 27–28](../../../../tools/verify_workloads.py#L27) | Explanatory comments or spacing. |  |
| [B0006 · 29–30](../../../../tools/verify_workloads.py#L29) | Callable definition: def digest(path): | calls sha256, read_bytes, hexdigest; returns hashlib.sha256(path.read_bytes()).hexdigest() · [reviewed contract](#b0006) |
| [B0007 · 31–32](../../../../tools/verify_workloads.py#L31) | Explanatory comments or spacing. |  |
| [B0008 · 33–39](../../../../tools/verify_workloads.py#L33) | Callable definition: def file_entry(pack, entry): | calls PurePosixPath, require, is_absolute, resolve; guard require(not relative.is_absolute() and '..' not in relative.parts and '\\' not in entry\['path'\], 'u…; returns path · [reviewed contract](#b0008) |
| [B0009 · 40–41](../../../../tools/verify_workloads.py#L40) | Explanatory comments or spacing. |  |
| [B0010 · 42–46](../../../../tools/verify_workloads.py#L42) | Callable definition: def module(source, generator='tools/generate_workloads.py'): | calls require, in, spec_from_file_location, module_from_spec; guard require(generator in ('tools/generate_workloads.py', 'tools/generate_adversarial_workloads.py'), 'u…; returns out · [reviewed contract](#b0010) |
| [B0011 · 47–48](../../../../tools/verify_workloads.py#L47) | Explanatory comments or spacing. |  |
| [B0012 · 49–52](../../../../tools/verify_workloads.py#L49) | Callable definition: def row_keys(rows): | calls canonical, require, len, set; guard require(len(encoded) == len(set(encoded)), 'duplicate native row or signed delta'); returns set(encoded); 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 53–54](../../../../tools/verify_workloads.py#L53) | Explanatory comments or spacing. |  |
| [B0014 · 55–110](../../../../tools/verify_workloads.py#L55) | Callable definition: def legacy_verify(source, manifest): | calls loads, file_entry, read_text, require; guard require(legacy\['schema_version'\] == 1 and legacy\['kind'\] == 'crown_legacy_workload_inventory', 'unk…; returns {'legacy_labels': len(labels), 'legacy_scenarios': len(scenarios),; 14 loop sites · [reviewed contract](#b0014) |
| [B0015 · 111–113](../../../../tools/verify_workloads.py#L111) | Module statements. | source comment (unverified): # Static means no native replay here; trusted generator code and SQLite still execute. · [reviewed contract](#b0015) |
| [B0016 · 114–175](../../../../tools/verify_workloads.py#L114) | Callable definition: def static_verify(source, pack): | calls loads, read_text, check_schema, Draft202012Validator; guard require(digest(source / options\['path'\]) == options\['sha256'\], 'generator checksum mismatch'); returns manifest, {**legacy_verify(source, manifest), 'queries': len(queries), 'workloads': len(seen), 'phy…; growth insert; 12 loop sites; source comment (unverified): # Explicit malformed descriptors and FIFO promises must be rejected too. · [reviewed contract](#b0016) |
| [B0017 · 176–177](../../../../tools/verify_workloads.py#L176) | Explanatory comments or spacing. |  |
| [B0018 · 178–235](../../../../tools/verify_workloads.py#L178) | Callable definition: def native_verify(source, pack, manifest, crown, replay, directory): | calls invoke, run, str, map; guard require(result.returncode == expected, f'{arguments\[0\]} exit {result.returncode}: {result.stderr\[-1…; returns value; {'native_replays': replays, 'native_physical_epochs_checked': records, 'commands': len(calls…; 12 loop sites · [reviewed contract](#b0018) |
| [B0019 · 236–237](../../../../tools/verify_workloads.py#L236) | Explanatory comments or spacing. |  |
| [B0020 · 238–257](../../../../tools/verify_workloads.py#L238) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, resolve; guard require(args.crown and args.replay, 'native verification needs --crown and --replay') · [reviewed contract](#b0020) |
| [B0021 · 258–264](../../../../tools/verify_workloads.py#L258) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |

## B0001

[Lines 1–20](../../../../tools/verify_workloads.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define B02 exact-byte/regime/legacy checks and optional native epoch replay. |
| inputs / outputs | Imports stdlib and installed jsonschema, disables process bytecode writes; imported-source verifier is loaded lazily by legacy_verify. Guarded CLI selects --static-only or native binaries. |
| invariants | Static mode still dynamically executes trusted generator and runs independent SQLite/relational regeneration. It does not run native processes unless native_verify requested, except imported optional parse supplied elsewhere. |
| ownership | Owns imports; later complete corpus bytes/manifest/results/captures ordinary process memory. |
| failure | Import errors visible; explicit require ValueError, script wrapper contextualizes Exception. |
| cost | Fixed setup; full regeneration/filesystem/hash/oracle and optional native work later. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 21–22](../../../../tools/verify_workloads.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value, message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a false caller-supplied condition in this tool. |
| inputs / outputs | Truth-tested value and diagnostic text in; None on truth, ValueError on false. |
| invariants | Explicit conditional raise remains active under Python -O; this is a local assertion of the stated predicate, not native/proof validation. |
| ownership | Borrows condition/message; exception retains message until released. |
| failure | Raises ValueError at the caller check before subsequent operations; does not catch or undo earlier IO. |
| cost | O(truth conversion) plus exception construction only on failure; arbitrary user-defined __bool__ is outside these primitive callers. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 25–26](../../../../tools/verify_workloads.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an ordinary JSON-compatible value deterministically for this packet format. |
| inputs / outputs | JSON graph in; ensure_ascii=False, sorted-key, compact-separator Unicode JSON string out. |
| invariants | Preserves array order and JSON scalar kinds; standard json.dumps defaults still apply to unsupported/nonfinite values unless caller checks them. No native canonicalization authority. |
| ownership | Input graph borrowed; returned full serialization and encoder temporaries owned. |
| failure | JSON/type/encoding-memory errors propagate; no source mutation. |
| cost | O(serialized graph bytes) plus per-object key sorting and full output allocation. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 29–30](../../../../tools/verify_workloads.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute SHA256 for an entire file as raw bytes. |
| inputs / outputs | Path-like input; lowercase SHA256 hex output; file content read completely. |
| invariants | Digest binds exact bytes supplied, including line endings and literal spelling; it does not attest semantic correctness or build lineage. |
| ownership | Owns full read_bytes temporary and hash/hex result; filesystem source unchanged. |
| failure | IO/OOM/type failure propagates before a digest result. |
| cost | O(file bytes) read+hash with full file-sized temporary. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0008

[Lines 33–39](../../../../tools/verify_workloads.py#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def file_entry(pack, entry):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a workload manifest file's path containment and exact raw SHA. |
| inputs / outputs | Root and entry path/hash in; constructed pack-relative Path out after resolved containment/existence checks. |
| invariants | PurePosix path must be relative with no .. or backslash, resolved target contained in root; SHA validates bytes only, not result semantics. |
| ownership | Owns Path/full read_bytes temporary/hash; filesystem input unchanged. |
| failure | ValueError on invalid path/missing file/hash; IO/type/OOM errors propagate. |
| cost | Path resolve/is_file plus O(file bytes) full read/hash, no streaming cap. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0010

[Lines 42–46](../../../../tools/verify_workloads.py#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def module(source, generator='tools/generate_workloads.py'):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load and execute only one of two named local workload generators. |
| inputs / outputs | Source root and generator relative path in; importlib-executed module out. |
| invariants | Allowlist contains B02 and B05 paths. Executes trusted Python top-level code; it is not a sandbox. Generator main guard stays inactive. |
| ownership | Owns module/spec/imported objects; import cache may retain dependencies. |
| failure | Unknown path raises ValueError; loader/syntax/import/top-level errors propagate. |
| cost | Reads, compiles and executes selected generator plus imports. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [schemas/workload-manifest-v1.schema.json](../../../../schemas/workload-manifest-v1.schema.json), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0012

[Lines 49–52](../../../../tools/verify_workloads.py#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def row_keys(rows):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare result rows through type-sensitive canonical JSON keys while requiring set uniqueness. |
| inputs / outputs | Row records in; set of canonical strings out. |
| invariants | Rejects duplicate row spellings; distinguishes bool/int in JSON and ignores overall row ordering via set. Does not normalize arbitrary SQL scalar equivalence. |
| ownership | Owns key list/set and serialization strings; original rows borrowed. |
| failure | ValueError on duplicate, JSON/type/OOM failures propagate. |
| cost | O(total row serialized bytes) plus key hashing and set allocation; transient list+set coexist. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0014

[Lines 55–110](../../../../tools/verify_workloads.py#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def legacy_verify(source, manifest):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact retained legacy source inventory and imported/unavailable-data boundaries. |
| inputs / outputs | Source root and workload manifest with legacy_inventory/external_imports entries in; metadata summary out after SHA/Git blob/properties/task/scenario/registry checks. |
| invariants | Pinned source-only/unavailable datasets cannot become native timing eligible. Source metadata does not claim external result reproduction, dataset availability or license permission. |
| ownership | Owns parsed inventories/properties/source bytes, regex grouping and imported summary; source unchanged. |
| failure | ValueError on source/description/data eligibility discrepancy; IO/JSON/imported checks propagate. |
| cost | Full reads/SHA/Git-blob hashes and properties scans across retained source files, then imported inventory verification; no legacy workload execution. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0015

[Lines 111–113](../../../../tools/verify_workloads.py#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L113:sha256:79eaf4a70473df3222bd8cdeff9a1cbf627695d23f253ca4c07c9c3a08f4536c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: Static means no native replay here; trusted generator code and SQLite still execute. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [docs/workloads.md](../../../workloads.md), [docs/code_review.md](../../../code_review.md) |

## B0016

[Lines 114–175](../../../../tools/verify_workloads.py#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def static_verify(source, pack):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Regenerate selected B02 or B05 workload pack and check schema, exact bytes, oracle/regime and provenance fields. |
| inputs / outputs | Source/pack Paths in; workload-v1 manifest and validation summary out. |
| invariants | Selects generator through manifest allowlist, checks its SHA, calls build() and requires complete relative-path/byte map equality. Checks event positions, structural labels, licenses, malformed metadata and regime controls. Secondary scale/seed control uses B02 generator. Finite checks are not universal trace proof. Compare free_connex using body AND augmented acyclicity; a universal head edge cannot admit a cyclic body. |
| ownership | Owns schema/manifest, generated/actual bytes, decoded event/oracle lists and secondary B02 pack; source files unchanged. |
| failure | Expected malformed-control errors are caught locally; other mismatches raise ValueError; generator/SQLite/JSON/IO/allocation failures propagate. |
| cost | Regenerates selected pack and per-epoch oracles, scans bytes/events, builds secondary B02 scale/seed pack and checks legacy inventories. No native execution here. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [schemas/workload-manifest-v1.schema.json](../../../../schemas/workload-manifest-v1.schema.json), [docs/workloads.md](../../../workloads.md), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0018

[Lines 178–235](../../../../tools/verify_workloads.py#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def native_verify(source, pack, manifest, crown, replay, directory):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile/admit/validate each workload query and compare every retained physical epoch across backends/modes. |
| inputs / outputs | Source/pack/manifest/crown/replay/private directory in; writes query plans/bound inputs/reports/commands and returns finite replay counts/hashes. |
| invariants | Negative admission controls stay rejected; admitted compiled artifacts must report valid proven minimum. Canonical catalog digest binds events; exact initial/current/signed delta/source positions/horizons checked for delta and maintenance snapshots. Compare free_connex using body AND augmented acyclicity; a universal head edge cannot admit a cyclic body. |
| ownership | Owns definitions/compiled artifacts, bound input lists, complete expected/actual reports and retained command ledger; caller owns persistent/temporary directory choice. |
| failure | First discrepancy raises ValueError; native timeout180/IO/JSON errors propagate. commands.json written only at normal end, not guaranteed failure journal. |
| cost | Per-query multiple native subprocesses plus every admitted workload×backend×two modes full replay; complete capture/parse and per-epoch JSON row-key serialization comparisons, files retained as selected by caller. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def invoke(executable, arguments, expected=0, output=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke one workload native operation and record successful exact stdout binding. |
| inputs / outputs | Executable/arguments, expected code and optional output Path in; parsed JSON out and captured calls list appended. |
| invariants | Timeout180; exact expected exit and empty stderr required before parsing/writing/ledger append. A failed call is not appended and ledger not saved here. |
| ownership | Owns full captured output/DOM and command metadata; optional file retains original stdout text. |
| failure | Wrong exit/stderr ValueError, spawn/timeout/JSON/write failures propagate without contextual catch. |
| cost | One native child with uncapped text capture, JSON parse, optional full write and SHA of re-encoded stdout; not raw-byte-preserving if platform text newline transforms occurred. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0020

[Lines 238–257](../../../../tools/verify_workloads.py#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select exact static checking or native replay with explicit artifact retention policy. |
| inputs / outputs | --source/--pack/--static-only/--crown/--replay/--artifact-dir in; prints B02 summary. |
| invariants | Always runs full static verification first. Native mode requires both executables; artifact-dir must be new and persists, otherwise TemporaryDirectory removes artifacts on success/failure. |
| ownership | Owns manifest/summary; persistent output chosen by caller or context-owned temp directory. |
| failure | Argparse/validation/native/IO errors reach script Exception wrapper; temp context cleanup still executes. New persistent partial artifacts not rolled back. |
| cost | Full static rebuild plus optional native matrix and summary writing; no native job in --static-only, but SQLite/generator work remains. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0021

[Lines 258–264](../../../../tools/verify_workloads.py#L258); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the B02 corpus verifier only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | Catches Exception, prints B02 verification failed diagnostic and exits1; no rollback of persistent artifacts, SystemExit/interrupts unhandled. |
| cost | Fixed wrapper then full selected verification. |
| Design | [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tools/generate_workloads.py](../../../../tools/generate_workloads.py), [tools/verify_imported_workloads.py](../../../../tools/verify_imported_workloads.py), [docs/workloads.md](../../../workloads.md), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [benchmarks/external_imports.json](../../../../benchmarks/external_imports.json), [benchmarks/workloads/manifest.json](../../../../benchmarks/workloads/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
