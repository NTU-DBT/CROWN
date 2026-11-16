# `tools/build_experimental_report.py` — block usage map

[Source](../../../../tools/build_experimental_report.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `71de74a9c7a22bce23ef4b9d5cb495750acc86abba88ca1a91bb7bde58e57ba0`. 562 lines partitioned into 59 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../tools/build_experimental_report.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 24–26](../../../../tools/build_experimental_report.py#L24) | Callable definition: def require(condition, message): | calls ValueError; guard def require(condition, message): · [reviewed contract](#b0002) |
| [B0003 · 27–28](../../../../tools/build_experimental_report.py#L27) | Explanatory comments or spacing. |  |
| [B0004 · 29–30](../../../../tools/build_experimental_report.py#L29) | Callable definition: def canonical(value): | calls dumps; returns json.dumps(value, sort_keys=True, separators=(',', ':'), ensure_ascii=False, allow_nan=False) · [reviewed contract](#b0004) |
| [B0005 · 31–32](../../../../tools/build_experimental_report.py#L31) | Explanatory comments or spacing. |  |
| [B0006 · 33–34](../../../../tools/build_experimental_report.py#L33) | Callable definition: def digest(data): | calls sha256, hexdigest; returns hashlib.sha256(data).hexdigest() · [reviewed contract](#b0006) |
| [B0007 · 35–36](../../../../tools/build_experimental_report.py#L35) | Explanatory comments or spacing. |  |
| [B0008 · 37–38](../../../../tools/build_experimental_report.py#L37) | Callable definition: def write_json(path, value): | calls write_text, dumps · [reviewed contract](#b0008) |
| [B0009 · 39–40](../../../../tools/build_experimental_report.py#L39) | Explanatory comments or spacing. |  |
| [B0010 · 41–44](../../../../tools/build_experimental_report.py#L41) | Callable definition: def write_csv(path, rows, fields): | calls open, DictWriter, writeheader, writerows · [reviewed contract](#b0010) |
| [B0011 · 45–48](../../../../tools/build_experimental_report.py#L45) | declares types or opens a type body. |  · [reviewed contract](#b0011) |
| [B0012 · 49–55](../../../../tools/build_experimental_report.py#L49) | Callable definition: def __init__(self, output, maximum, single_file, mappings=(), replay=None): | calls sorted, len, str, loads · [reviewed contract](#b0012) |
| [B0013 · 56–56](../../../../tools/build_experimental_report.py#L56) | Explanatory comments or spacing. |  |
| [B0014 · 57–94](../../../../tools/build_experimental_report.py#L57) | Callable definition: def read(self, path, expected=None): | calls str, Path, require, is_absolute; guard require(original in self.prior\['original_paths'\], 'evidence missing from portable store: '+original); returns data, {'path': self.files\[key\]\['path'\], 'sha256': key, 'original_path': original}; growth new; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 95–95](../../../../tools/build_experimental_report.py#L95) | Explanatory comments or spacing. |  |
| [B0016 · 96–98](../../../../tools/build_experimental_report.py#L96) | Callable definition: def json(self, path, expected=None): | calls read, loads; returns json.loads(data), reference · [reviewed contract](#b0016) |
| [B0017 · 99–99](../../../../tools/build_experimental_report.py#L99) | Explanatory comments or spacing. |  |
| [B0018 · 100–106](../../../../tools/build_experimental_report.py#L100) | Callable definition: def reference(self, path, expected=None): | calls str, Path, read, require; guard require(expected is None or key == expected, 'cached evidence hash differs: '+original); returns self.read(path, expected)\[1\]; {'path': self.files\[key\]\['path'\], 'sha256': key, 'original_path': ori… · [reviewed contract](#b0018) |
| [B0019 · 107–107](../../../../tools/build_experimental_report.py#L107) | Explanatory comments or spacing. |  |
| [B0020 · 108–112](../../../../tools/build_experimental_report.py#L108) | Callable definition: def finish(self): | calls write_json · [reviewed contract](#b0020) |
| [B0021 · 113–114](../../../../tools/build_experimental_report.py#L113) | Explanatory comments or spacing. |  |
| [B0022 · 115–128](../../../../tools/build_experimental_report.py#L115) | Callable definition: def command_evidence(store, directory, record): | calls require, get, read, int; guard require(record\['exit_code'\] == 0 and not record.get('timed_out', False), 'unqualified command canno…; returns json.loads(data), reference; 1 loop sites; source comment (unverified): # Only declared data arguments are copied, never producer binaries/archives. · [reviewed contract](#b0022) |
| [B0023 · 129–130](../../../../tools/build_experimental_report.py#L129) | Explanatory comments or spacing. |  |
| [B0024 · 131–135](../../../../tools/build_experimental_report.py#L131) | Callable definition: def exact(value): | calls isinstance, Fraction, int, require; guard require(isinstance(value, (int, Fraction)) and not isinstance(value, bool), 'metric must be exact i…; returns Fraction(int(value\['numerator'\]), int(value\['denominator'\])); Fraction(value) · [reviewed contract](#b0024) |
| [B0025 · 136–138](../../../../tools/build_experimental_report.py#L136) | declares types or opens a type body. |  · [reviewed contract](#b0025) |
| [B0026 · 139–142](../../../../tools/build_experimental_report.py#L139) | Callable definition: def __init__(self, store, selection): | calls  · [reviewed contract](#b0026) |
| [B0027 · 143–143](../../../../tools/build_experimental_report.py#L143) | Explanatory comments or spacing. |  |
| [B0028 · 144–151](../../../../tools/build_experimental_report.py#L144) | Callable definition: def groups(self, study, available): | calls sorted, set, get, require; guard require(isinstance(chosen, list) and chosen and len(set(chosen)) == len(chosen) and set(chosen) &lt;= …; returns set(chosen); 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 152–152](../../../../tools/build_experimental_report.py#L152) | Explanatory comments or spacing. |  |
| [B0030 · 153–158](../../../../tools/build_experimental_report.py#L153) | Callable definition: def environment(self, study, packet): | calls get, digest, canonical, encode; returns key · [reviewed contract](#b0030) |
| [B0031 · 159–159](../../../../tools/build_experimental_report.py#L159) | Explanatory comments or spacing. |  |
| [B0032 · 160–169](../../../../tools/build_experimental_report.py#L160) | Callable definition: def metric(self, base, name, value, unit, reference, pointer='', availability='available'): | calls exact, str, digest, canonical · [reviewed contract](#b0032) |
| [B0033 · 170–170](../../../../tools/build_experimental_report.py#L170) | Explanatory comments or spacing. |  |
| [B0034 · 171–174](../../../../tools/build_experimental_report.py#L171) | Callable definition: def decision(self, study, group, kind, details, reference, pointer): | calls append, canonical · [reviewed contract](#b0034) |
| [B0035 · 175–175](../../../../tools/build_experimental_report.py#L175) | Explanatory comments or spacing. |  |
| [B0036 · 176–181](../../../../tools/build_experimental_report.py#L176) | Callable definition: def samples(self, base, name, values, unit, reference, pointer): | calls sorted, in, len, metric; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 182–183](../../../../tools/build_experimental_report.py#L182) | Explanatory comments or spacing. |  |
| [B0038 · 184–204](../../../../tools/build_experimental_report.py#L184) | Callable definition: def b03_metrics(tables, base, report, record, reference, release=False): | calls len, require, metric, Fraction; guard require(count &gt; 0, 'empty measured B03 horizon'); 11 loop sites · [reviewed contract](#b0038) |
| [B0039 · 205–206](../../../../tools/build_experimental_report.py#L205) | Explanatory comments or spacing. |  |
| [B0040 · 207–255](../../../../tools/build_experimental_report.py#L207) | Callable definition: def read_b05(tables, root, analysis): | calls json, require, read, list; guard require(packet\['kind'\] == 'b05_parameterized_native_stress' and packet\['status'\] == 'complete', 'B0…; 12 loop sites · [reviewed contract](#b0040) |
| [B0041 · 256–257](../../../../tools/build_experimental_report.py#L256) | Explanatory comments or spacing. |  |
| [B0042 · 258–289](../../../../tools/build_experimental_report.py#L258) | Callable definition: def read_planning(tables, directory): | calls json, require, read, environment; guard require(packet\['status'\] == 'complete_conditional_dependencies' and packet\['correctness_gate'\] ==; 8 loop sites · [reviewed contract](#b0042) |
| [B0043 · 290–291](../../../../tools/build_experimental_report.py#L290) | Explanatory comments or spacing. |  |
| [B0044 · 292–318](../../../../tools/build_experimental_report.py#L292) | Callable definition: def component_metrics(tables, base, report, record, reference): | calls require, len, str, index; guard require(len(passes) == 1, 'component invocation must have one measured owner'); 10 loop sites · [reviewed contract](#b0044) |
| [B0045 · 319–320](../../../../tools/build_experimental_report.py#L319) | Explanatory comments or spacing. |  |
| [B0046 · 321–349](../../../../tools/build_experimental_report.py#L321) | Callable definition: def read_components(tables, directory, study): | calls json, require, read, environment; guard require(packet\['status'\] == expected and packet\['correctness_gate'\] == 'all_preflights_pass' and pa…; 6 loop sites · [reviewed contract](#b0046) |
| [B0047 · 350–351](../../../../tools/build_experimental_report.py#L350) | Explanatory comments or spacing. |  |
| [B0048 · 352–380](../../../../tools/build_experimental_report.py#L352) | Callable definition: def read_search(tables, directory): | calls json, require, read, environment; guard require(packet\['status'\] == 'finite_conditional_study_complete' and packet\['correctness_gate'\] ==; 6 loop sites · [reviewed contract](#b0048) |
| [B0049 · 381–382](../../../../tools/build_experimental_report.py#L381) | Explanatory comments or spacing. |  |
| [B0050 · 383–416](../../../../tools/build_experimental_report.py#L383) | Callable definition: def read_specialization(tables, directory): | calls json, require, read, environment; guard require(packet\['kind'\] == 'b04_input_specialization_study_v1' and; 6 loop sites · [reviewed contract](#b0050) |
| [B0051 · 417–418](../../../../tools/build_experimental_report.py#L417) | Explanatory comments or spacing. |  |
| [B0052 · 419–436](../../../../tools/build_experimental_report.py#L419) | Callable definition: def summarize(metrics): | calls defaultdict, append, sorted, items; returns result; 7 loop sites · [reviewed contract](#b0052) |
| [B0053 · 437–438](../../../../tools/build_experimental_report.py#L437) | Explanatory comments or spacing. |  |
| [B0054 · 439–449](../../../../tools/build_experimental_report.py#L439) | Callable definition: def reproduction_text(): | calls ; returns '''# Reproduce the method in a fresh prefix; growth new; 1 loop sites · [reviewed contract](#b0054) |
| [B0055 · 450–451](../../../../tools/build_experimental_report.py#L450) | Explanatory comments or spacing. |  |
| [B0056 · 452–536](../../../../tools/build_experimental_report.py#L452) | Callable definition: def run(args): | calls resolve, require, exists, read_bytes; guard output = args.output.resolve(); require(not output.exists(), 'report output must be new'); growth new; 16 loop sites · [reviewed contract](#b0056) |
| [B0057 · 537–538](../../../../tools/build_experimental_report.py#L537) | Explanatory comments or spacing. |  |
| [B0058 · 539–558](../../../../tools/build_experimental_report.py#L539) | Callable definition: def main(): | calls ArgumentParser, in, add_argument, parse_args; guard require(args.replay is not None or all(getattr(args, name) is not None for name in (*STUDIES, 'b05_…; returns 1; 0; 2 loop sites · [reviewed contract](#b0058) |
| [B0059 · 559–562](../../../../tools/build_experimental_report.py#L559) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0059) |

## B0001

[Lines 1–23](../../../../tools/build_experimental_report.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:4bffd3c48467a287ffc42003aec160b127eb58a77303b12565b7b3ab5e3e01db
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare offline experimental-table and portable-evidence support. |
| inputs / outputs | Imports standard-library exact arithmetic, CSV/JSON, bounded gzip, hashing and path tools; declares five mandatory studies and the metric-column schema. |
| invariants | Import launches no compiler, native driver or benchmark. A raw metric carries its original source path, original hash and portable link; warmups are not measured repetitions. |
| ownership | Only interpreter globals exist; subsequent Evidence and Tables objects own report-building state. |
| failure | Unavailable Python dependencies or syntax fail import; there is no alternative data provider. |
| cost | Cold interpreter setup, outside all historical measured stages and query accounts. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [Refactor.md §11.11 B06](../../../../Refactor.md), [Refactor.md §14.4](../../../../Refactor.md) |

## B0002

[Lines 24–26](../../../../tools/build_experimental_report.py#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L26:sha256:771470ca6047ea7b84814e6cc23c2357b927e95ad29ed2fbd7b34f2969c68de4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a violated local receiving condition. |
| inputs / outputs | A predicate and explanatory message either return normally or raise ValueError. |
| invariants | Failure never becomes zero, an unavailable metric or a successful report. |
| ownership | Borrows its arguments and owns only a possible exception. |
| failure | False conditions propagate to the single CLI diagnostic boundary. |
| cost | One predicate branch plus exception construction only on failure. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0004

[Lines 29–30](../../../../tools/build_experimental_report.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L30:sha256:b80616886a625d55367f6b5e896b67ba6f4f76871b4151845b930737b248ced9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Give structured metadata an unambiguous comparison/fingerprint representation. |
| inputs / outputs | A JSON-compatible value becomes compact Unicode JSON with sorted object keys. |
| invariants | NaN is rejected; order of array members remains significant. This is metadata normalization, not rewriting original evidence bytes. |
| ownership | Owns the returned string and borrows the caller value. |
| failure | Unsupported objects or non-finite numbers raise normal JSON errors. |
| cost | Linear encoding in the represented metadata size, with JSON object-key sorting. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0006

[Lines 33–34](../../../../tools/build_experimental_report.py#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L34:sha256:50b76bfffc27cbd7a792c95d031f6fd8e49777b6241b96ed8c4c4773edc356cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind already-read original or generated bytes with SHA256. |
| inputs / outputs | A bytes-like payload produces its lowercase hexadecimal digest. |
| invariants | The hash identifies exact bytes; it does not establish correctness or source/build lineage. |
| ownership | Borrows payload memory; returns a small owned string. |
| failure | Invalid input types propagate from hashlib. |
| cost | Linear byte hashing with bounded hash state. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0008

[Lines 37–38](../../../../tools/build_experimental_report.py#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L38:sha256:5a79aea961089931606600bcd37bf40fb7e009bf3274fa74acd7dc617bad9d91
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write stable human-inspectable report JSON. |
| inputs / outputs | A destination path and JSON value produce sorted, indented UTF-8 text ending in a newline. |
| invariants | NaN is forbidden. Callers use this only inside their newly created output tree; the final manifest is written after payloads. |
| ownership | Borrows values and writes one caller-owned report file. |
| failure | Encoding, serialization or filesystem errors remain failures. |
| cost | Serialization and file work scale with the actual output size. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0010

[Lines 41–44](../../../../tools/build_experimental_report.py#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L44:sha256:532ae9fc3ef6571d0034fc4c5e3b6a8288d3e8d3d0efff2183164a989f54cd07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one exact table without silently overwriting an existing table. |
| inputs / outputs | Rows plus ordered field names create an exclusive CSV file with a header; unrelated dictionary fields are omitted by the declared schema. |
| invariants | Rational numerator/denominator strings and explicit availability are preserved, rather than rounded into decimal samples. |
| ownership | The context manager owns the file; row dictionaries stay caller-owned. |
| failure | Existing paths, malformed rows or I/O failures propagate. |
| cost | Streaming CSV work is proportional to rows and encoded cell bytes. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0011

[Lines 45–48](../../../../tools/build_experimental_report.py#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L48:sha256:f16b5e76d18d17ee13f367d957b9ef0afd27330fddcb6b8500367958a91f0727
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the finite, content-addressed original-byte evidence store. |
| inputs / outputs | The class groups admission, replay, cached references and final inventory operations. |
| invariants | Portable replay has no fallback to historical workspace paths; compressed and decompressed hashes represent different byte layers. |
| ownership | Each instance belongs to one new report directory. |
| failure | Construction/method errors propagate rather than selecting an older report. |
| cost | The declaration has no runtime data traversal. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0012

[Lines 49–55](../../../../tools/build_experimental_report.py#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L55:sha256:ee7502e2cc74b8c329c6f7ae2d30f255593c9f233e5aa798f9bcd5caf0da7184
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a bounded store for one report build or replay. |
| inputs / outputs | New output, aggregate/single-file byte grants, optional root mappings and optional prior bundle establish empty content/path indexes and a new evidence directory. |
| invariants | Longest mapped prefix wins; replay uses only the prior evidence index. The caller has already admitted a fresh output root. |
| ownership | Owns indexes, limits and prior index DTO; borrows immutable input directories. |
| failure | Unreadable prior index or inability to create the evidence directory fails construction. |
| cost | Cold mapping sort and prior-index parse; no native execution or bulk evidence read. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0014

[Lines 57–94](../../../../tools/build_experimental_report.py#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L94:sha256:2e0582a981049d085808c2513fea8272f9e500cc59197223404d907bfe10743e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive exact original bytes into a finite portable gzip member. |
| inputs / outputs | An original path and optional expected SHA return original bytes and a portable reference; original input may resolve through explicit path maps or a prior indexed gzip member. |
| invariants | Replay admits only safe relative members, checks compressed size/SHA, caps decompression and checks original SHA. New content is deduplicated by original digest; unique files, cumulative original bytes and individual files are bounded. One original path cannot change bytes within the build. Gzip timestamp/name are fixed. |
| ownership | Owns newly written gzip bytes/index records and returned payload; input source/member bytes remain read-only. The method does not copy executables implicitly. |
| failure | Missing, changed, unsafe, oversized, corrupt or grant-exceeding evidence rejects before a complete artifact manifest is emitted. Partial owned output remains for inspection. |
| cost | Per read: file/decompression/hash work in actual bytes; first unique content also costs compression and output bytes. Payload memory is bounded by the single-file grant. These are offline costs, not experiment timers. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [tests/integration/experimental_report.py](../../../../tests/integration/experimental_report.py) |

## B0016

[Lines 96–98](../../../../tools/build_experimental_report.py#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L98:sha256:0229d608e2bcba4770faa4cc1f8fbc2a0442ea48ec82267e20f1510adbba0975
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one byte-qualified JSON evidence member. |
| inputs / outputs | Original path/expected hash pass through read; decoded JSON and the same exact-byte reference are returned. |
| invariants | Decoding does not alter the saved source bytes or weaken the underlying finite/hash checks. |
| ownership | Owns the decoded DTO; original payload lifetime is local to the call. |
| failure | Invalid JSON or read qualification errors propagate. |
| cost | Read/compression work plus JSON parsing proportional to the admitted member. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0018

[Lines 100–106](../../../../tools/build_experimental_report.py#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L100-L106:sha256:d2fe3af4c4ab6c351883750b06bd4311797a26ed3b6b0d264c395b9b659f891c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse a previously qualified raw-member reference without repeated large-file reads. |
| inputs / outputs | An original path/optional SHA returns its known reference or receives it once through read. |
| invariants | A supplied expected hash must still agree. Cached reference use assumes the already received original bytes; it makes no fresh external-file stability claim. |
| ownership | Returns a small new reference dictionary backed by this instance content/path indexes. |
| failure | Unknown files receive the full admission checks; cached expected-hash disagreement rejects. |
| cost | Expected constant dictionary lookup for known paths; first use incurs Evidence.read costs. This avoids rereading B05 raw reports once per probe row. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py) |

## B0020

[Lines 108–112](../../../../tools/build_experimental_report.py#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L112:sha256:271ba50822dd547dca084c4604be2a6b95fe440759069093b384196dd6143843
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the evidence index after selected source ingestion. |
| inputs / outputs | Stored content/path entries and totals become evidence-index.json with Python/zlib/level/timestamp provenance. |
| invariants | SHA keys bind decompressed originals; compressed hashes bind the chosen serialization. Same-runtime determinism is distinct from cross-platform compressor-byte identity. |
| ownership | Writes a new report-owned index; does not mutate original sources or prior bundles. |
| failure | Serialization/I/O failure prevents complete publication. |
| cost | Offline output proportional to the inventory size, not total decompressed payload size. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0022

[Lines 115–128](../../../../tools/build_experimental_report.py#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L128:sha256:3016da047058e3b81321c7dd2bf7e1b3a511d656c02ccf81bc22d365a3dbefa3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive a genuinely successful retained process record and its data arguments. |
| inputs / outputs | A study directory/command record returns decoded stdout and its reference, with an actual resource reference when supplied. |
| invariants | Exit must be zero without timeout, stdout/stderr hashes must match and successful stderr must be empty. GNU-time resource text equals recorded RSS. Only declared JSON/JSONL/SQL arguments are copied; binary provenance is not invented from command argv. |
| ownership | Owns decoded DTOs/references in the parent report process; published native executables and baseline archives remain untouched. |
| failure | Failed commands, diagnostics, hash/RSS mismatch, absent data arguments or invalid JSON reject the receiving path. |
| cost | Offline reads/hash/compression/JSON parse in actual report and declared-data bytes; no child process is executed. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [tools/run_measurements.py](../../../../tools/run_measurements.py) |

## B0024

[Lines 131–135](../../../../tools/build_experimental_report.py#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L131-L135:sha256:790601e88e82d6ded97a82cfafaaf6d08b83da39370cf25094d22ec5483c2acf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize exact metric values without introducing floating arithmetic. |
| inputs / outputs | An integer, Fraction or numerator/denominator DTO becomes a Fraction. |
| invariants | Booleans are not integer measurements. Zero denominators reject; normalization preserves the mathematical value. |
| ownership | Returns an owned immutable rational. |
| failure | Unsupported types, invalid integers or invalid denominators fail. |
| cost | Integer conversion and rational reduction depend on integer bit width. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0025

[Lines 136–138](../../../../tools/build_experimental_report.py#L136); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L138:sha256:2192364a44785eb3fddfcc477bc0d92067e49afa45e4ef1baf574a116a95fb51
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group report metric, decision, scope and environment accumulation. |
| inputs / outputs | The class associates selected original study scopes with exact output rows. |
| invariants | Metric availability and source identity stay explicit; data-table completion confers no B06 acceptance. |
| ownership | One table collector is owned by one report invocation. |
| failure | Methods propagate malformed-data and admission failures. |
| cost | The declaration allocates no experiment state. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0026

[Lines 139–142](../../../../tools/build_experimental_report.py#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L139-L142:sha256:5441e4db2c9ce578679cd43457d02de0d58fcf612523867c645f62a3a0fca1c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create empty per-report table accumulators. |
| inputs / outputs | Evidence store and caller selection establish metric/decision/environment/scope lists and retained B05 plot tables. |
| invariants | No source is selected or assumed complete before its reader enumerates the actual available groups. |
| ownership | Owns lists/dictionaries while referencing the caller store and selection. |
| failure | Ordinary allocation errors propagate. |
| cost | Constant empty-container initialization; later memory follows selected report rows. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0028

[Lines 144–151](../../../../tools/build_experimental_report.py#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L144-L151:sha256:3a2e1a54735255861db42bbdccf3016c12fc332ad8d9e63fd345f3897acfaa9d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve an explicit finite study selection against actual available groups. |
| inputs / outputs | Study name and available identifiers return a chosen set and record included/available/full-scope metadata. |
| invariants | Selections must be nonempty lists of unique known ids. Omitted selection means all available groups. A subset never acquires a full-source label. |
| ownership | Owns sorted identifiers and the returned chosen set. |
| failure | Unknown, empty, duplicate or malformed selections reject. |
| cost | Sort/set work in the number and length of group ids. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [tests/integration/experimental_report.py](../../../../tests/integration/experimental_report.py) |

## B0030

[Lines 153–158](../../../../tools/build_experimental_report.py#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L158:sha256:303c23739dd0ef3c374b322ab9818993ffb0814561144081d543fd227206bfb8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind source/build/machine metadata without merging historical vintages. |
| inputs / outputs | A study packet yields a canonical metadata fingerprint and retained environment/build/configuration/scope DTO. |
| invariants | The fingerprint is a grouping identity, not a new source or toolchain qualification. Different actual source/environment records remain separate in summaries. |
| ownership | Stores a parent metadata record; actual native owners/accounts are unrelated. |
| failure | Unserializable metadata fails canonicalization. |
| cost | Hash/encoding work in the metadata size; outside measured runs. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [docs/measurement.md](../../../measurement.md) |

## B0032

[Lines 160–169](../../../../tools/build_experimental_report.py#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L160-L169:sha256:91e25788a14b7371bd0ee85f8abb144ed5ffc3f2983075ec26045d62c294ea0e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one exact per-repetition observation with reachable raw provenance. |
| inputs / outputs | Base identity, metric name/value/unit, reference and optional JSON pointer produce a rational row and stable row id. |
| invariants | None becomes explicitly unavailable with empty numerator/denominator. A real zero remains available. The row names the actual original bytes and portable member; derived metrics point to their contributing structure. |
| ownership | Owns the appended row; input metadata/reference dictionaries are not mutated. |
| failure | Invalid exact values or noncanonical metadata propagate. |
| cost | One small record allocation plus rational normalization and metadata hash; no native update overhead. |
| Design | [docs/experimental_report.md](../../../experimental_report.md) |

## B0034

[Lines 171–174](../../../../tools/build_experimental_report.py#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L171-L174:sha256:d573531857b7080f69d5f747399099d49b7206c1eaa3ee2fb62991993d47c2a5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain non-scalar policy, stop, preparation and reconstruction evidence. |
| inputs / outputs | Study/group/kind/details/reference/pointer append a canonical details row with exact raw linkage. |
| invariants | Limited searches, fallbacks and owner reconstruction remain visible; a detail blob is not converted to a successful score or timing. |
| ownership | Owns the output row and canonical details string. |
| failure | Unsupported/nonfinite JSON details or missing reference fields fail. |
| cost | Encoding cost follows actual selected details size. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [docs/component_evaluation.md](../../../component_evaluation.md) |

## B0036

[Lines 176–181](../../../../tools/build_experimental_report.py#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L176-L181:sha256:28461e182a49db5e1d9b36278eb148db6e6fa44222dbed69124b7b3cb9dbb67d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one measured run latency population using nearest-rank tails. |
| inputs / outputs | A sequence of exact samples produces p50/p95/p99 and maximum metric rows under one base repetition. |
| invariants | Empty populations are unavailable. Percentiles are within-run descriptors, not independent process repetitions or confidence intervals. One sort serves all four descriptors. |
| ownership | Owns a sorted sample list and appended metric rows; caller sequence remains unchanged. |
| failure | Incomparable/invalid samples fail naturally; no synthetic zero population is inserted. |
| cost | O(n log n) offline comparison work and O(n) temporary references per latency population. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [Refactor.md §14.1](../../../../Refactor.md) |

## B0038

[Lines 184–204](../../../../tools/build_experimental_report.py#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L184-L204:sha256:fc5cf0c256d840ab564e654bf666972db1eb4d56e5ad0cc2ffb8c0609508d865
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract B05 or planning native/event/output/account scopes from actual epoch reports. |
| inputs / outputs | A nonempty raw report and process resource record emit per-input means, latency tails, cursor-call distributions, records and requested-byte/RSS metrics. |
| invariants | B05 native cost is prepare/commit; planning explicitly adds epoch release. Physical epochs supply denominators. First-result samples are output setup plus first successful call after commit, so eager staging stays in native/event work. RSS points to the actual resource member, not stdout. Missing call populations remain unavailable. |
| ownership | Reads decoded reports and appends parent-only table rows; owns temporary sample arrays. No report mutation, cursor use or engine state exists here. |
| failure | Empty horizons, missing required raw fields or invalid exact values reject receiving. |
| cost | Several linear passes plus sample sorting over selected epochs/calls. Counter layers and whole-process RSS are not summed into total CPU work. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [docs/measurement.md](../../../measurement.md), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), [examples/workload-measurement/main.cpp](../../../../examples/workload-measurement/main.cpp) |

## B0040

[Lines 207–255](../../../../tools/build_experimental_report.py#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L207-L255:sha256:eeb5f669d99c5a142b69400e017bba02e1e912434aa9e5a3de74460c120f78c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive selected accepted adversarial measurements and their actual gate/warmup evidence. |
| inputs / outputs | B05 root plus accepted analyzer root provide source-bound rows, child experiments/commands, measured raw reports, support/storage metrics and selected sentinel probes. |
| invariants | Root/child completion, exact analysis input binding, measured hashes/event counts and named correctness gates must match. Warmups and gates are included as evidence but never metric repetitions. Probe links reuse received exact originals; arena slot counts describe population, not tombstone visits. |
| ownership | Owns selected decoded child metadata and table rows in the report process; historical experiment/analyzer sources remain immutable. |
| failure | Missing child/gate, hash/count mismatch, unavailable required fields or byte-grant exhaustion reject the report. |
| cost | Offline work scales with selected raw byte volume and epochs/probes. Per-child cache and reference reuse prevent redundant source ingestion by group/probe. |
| Design | [docs/adversarial_scalability.md](../../../adversarial_scalability.md), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/experimental_report.md](../../../experimental_report.md), [Refactor.md §11.11 B05](../../../../Refactor.md) |

## B0042

[Lines 258–289](../../../../tools/build_experimental_report.py#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L258-L289:sha256:bdbc1a8bd7c40e8c0e1fa19af3b9571c27e3d9217d1d7a99cca85fa7ee8bc2fb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive held-out plan timings separately from offline policy/statistics decisions. |
| inputs / outputs | A completed planning packet yields selected query/backend/trace scopes, all their physical-plan raw runs, related preflights/exports/calibration and policy-analysis rows. |
| invariants | The declared all-envelope/all-split gate is required. Raw prepare-plus-release per-input cost must exactly match recorded cost. Warmups remain evidence only. Physical hashes separate plans; rank-deficient models, fallbacks and feasible regret are retained as decisions rather than upgraded into completeness. |
| ownership | Owns parent source DTOs and selected metrics; existing plans, forecasts and native binaries are read-only. |
| failure | Incomplete gates, failed commands, binding/cost disagreement or evidence limits fail receiving. |
| cost | Selected stdout/data reads plus epoch extraction; selection includes all actual plans within the chosen scope. Offline model work is not charged again as native measured work. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [tools/run_component_planning.py](../../../../tools/run_component_planning.py), [docs/experimental_report.md](../../../experimental_report.md), [Refactor.md §14.4](../../../../Refactor.md) |

## B0044

[Lines 292–318](../../../../tools/build_experimental_report.py#L292); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L292-L318:sha256:5ab39d3ef72737443207e92a3cbe6230eef9bd59d40176c8b23b3cf3b5977163
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve component owner, source, transaction, transport and output timing/memory units. |
| inputs / outputs | Exactly one measured pass supplies physical-input-normalized loop/stage clocks, within-unit tails, owner setup/teardown/account fields, RSS and reconstruction decisions. |
| invariants | Warmups are excluded. Epochs, transactions and batches keep distinct latency populations; absent clocks/accounts stay unavailable. Account samples are before teardown; final-owner peak and sampled peaks across destroyed owners stay separate. Reconstruction pointers locate the actual measured pass. Whole-process RSS is not query memory. |
| ownership | Borrows the report and appends table/decision DTOs; no owner reconstruction or source update is executed. |
| failure | Wrong measured-owner count, empty/invalid physical horizon or malformed required metrics reject. |
| cost | Offline traversal and one sort per actual timing population; no runtime instrumentation is added. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [docs/experimental_report.md](../../../experimental_report.md), [tools/run_operational_evaluation.py](../../../../tools/run_operational_evaluation.py) |

## B0046

[Lines 321–349](../../../../tools/build_experimental_report.py#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L321-L349:sha256:87eed5f81ca27203aff7bee83c274b36e8e527c81644654f2d48c9d4ffbb73e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive finite operational or matched studies without collapsing their semantic arms. |
| inputs / outputs | A completed frozen-input packet provides chosen arms, correctness/service controls, repeated raw invocations and declared paired comparisons. |
| invariants | Status/gate/frozen-input requirements are exact. Each actual owner schedule equals declared warmups plus one measured pass. Program/protocol/adapter/backend/width remain named. Supplemental service gates are evidence, not measured none-output delivery. Comparisons require both selected endpoints. |
| ownership | Owns selected report metadata; immutable legacy/native inputs are only referenced through their original provenance. |
| failure | Missing/failed gates, mismatched owner schedules, invalid arm/source data or evidence limits fail. |
| cost | Offline work follows selected raw captures and stage samples. Whole implementations retain parser/layout/scalar/format/framework/JVM effects; this reader supplies no pure-dispatch attribution. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [docs/legacy_baselines.md](../../../legacy_baselines.md), [tools/run_operational_evaluation.py](../../../../tools/run_operational_evaluation.py), [tools/run_baseline_evaluation.py](../../../../tools/run_baseline_evaluation.py), [Refactor.md §14.4](../../../../Refactor.md) |

## B0048

[Lines 352–380](../../../../tools/build_experimental_report.py#L352); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L352-L380:sha256:0179132590c5452c8c2d89efa9d4858731db78a2a5acca6872e5a75f3de01171
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive bounded candidate-search attempts while keeping actual limits and retained families visible. |
| inputs / outputs | A finite completed study supplies selected case/method/work scopes, relevant preflights, raw timers/candidates/stops and outer wall/RSS values. |
| invariants | The study gate and empty external failures are required. Copied run timings, candidate count and status must equal actual stdout before emission. Algorithm timers/candidates point to raw stdout; process wall points to its experiment row and RSS to actual resource text. A bounded prefix never becomes a complete family. |
| ownership | Owns parent raw DTOs and decision rows; executes no searcher or proof replay. |
| failure | Incomplete gates, semantically inconsistent metadata/raw output or command/hash failures reject. Valid limited outcomes remain retained. |
| cost | Read/hash/decode work plus selected metadata/candidate traversal. Search algorithm timings are observations, not the report builder time. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [tools/run_search_evaluation.py](../../../../tools/run_search_evaluation.py), [docs/component_evaluation.md](../../../component_evaluation.md), [Refactor.md §14.1](../../../../Refactor.md) |

## B0050

[Lines 383–416](../../../../tools/build_experimental_report.py#L383); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L383-L416:sha256:822f39d74178b31675ed825507d5585f6227466e4056e3d6294d110dffe5635b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Optionally receive the same-engine interpreted/threaded input-program comparison. |
| inputs / outputs | A genuinely completed specialization study provides selected execution/backend/case runs, preflights, inclusive receiving-freeze/preparation metrics and declared comparisons. |
| invariants | No supplied study means no sixth claim. Kind/status/gate, execution/key and every supplied physical/source/SQL/catalog/input SHA must match raw reports. Warmups stay nonmeasured; execution keys remain distinct from unchanged physical identity. Preparation metadata describes extra tables, not JIT machine code or a global cache. |
| ownership | Owns decoded optional evidence and table rows; production execution programs, caches and native accounts are not modified. |
| failure | Preflight-only/failed studies, mismatched identities, malformed reports or evidence limits reject optional receiving. |
| cost | Offline component extraction plus small preparation metadata capture. Shared SQL/lowering, receiving base freeze and per-owner loops retain separate costs; no general specialization speedup is inferred. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [Refactor.md §14.4](../../../../Refactor.md) |

## B0052

[Lines 419–436](../../../../tools/build_experimental_report.py#L419); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L419-L436:sha256:a840f5ebccf358259dec24e3ef76d5253688d727834223e5c83413155381b4e7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Aggregate repeated observations only within the same source/group/metric/unit. |
| inputs / outputs | Per-repetition rows produce exact min/median/max/mean, available/unavailable counts, source row/raw links and a display sample standard deviation. |
| invariants | Source identities and units prevent cross-vintage or semantic pooling. Missing samples are excluded, not zeroed. Intervals are observed ranges, not confidence intervals; process repetition counts are distinct from event percentiles. |
| ownership | Owns grouping lists, rational aggregates and returned summary rows. |
| failure | Malformed rationals or nonfinite display conversions propagate; an empty group cannot silently yield a numeric statistic. |
| cost | Group/sort work in metric-row volume with exact integer arithmetic; standard deviation alone uses display floats. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [Refactor.md §11.11 B06](../../../../Refactor.md) |

## B0054

[Lines 439–449](../../../../tools/build_experimental_report.py#L439); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L439-L449:sha256:61649f6d4bbad561059e5d574417a60f92e891893731a371c83af84cac2bc909
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply a portable methodological entry page without asserting historical replay success. |
| inputs / outputs | Returns prose naming fresh-prefix source/toolchain restoration, correctness-gated runners, baseline qualification and bundle-only regeneration. |
| invariants | Historical source preimages are required; current sources are not relabelled. Original published test failure remains explicit. Another machine records new timings and must use fresh destinations. |
| ownership | Owns a constant returned string; no filesystem or process action occurs. |
| failure | No dynamic failure path beyond ordinary string allocation. |
| cost | Constant cold report text construction. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [docs/legacy_baselines.md](../../../legacy_baselines.md), [docs/component_evaluation.md](../../../component_evaluation.md) |

## B0056

[Lines 452–536](../../../../tools/build_experimental_report.py#L452); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L452-L536:sha256:6da4b555b7c7c9b1f8d79ff1e4b06b7618052515e95afffe8ff8bd8bb4a7adc7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a new portable exact-table package from all five required studies and optional sixth data. |
| inputs / outputs | CLI-selected roots or a prior bundle, finite grants, optional selections/maps/preimages produce metrics, summaries, stops, raw links, source/environment indexes, replay tools, guides and a final payload manifest. |
| invariants | Existing output rejects before mutation. Replay first binds input/evidence indexes and optionally the published root manifest; every used member then receives byte checks. Five readers must finish before complete output. Scope selection and preimage-file presence are explicit independent fields; arbitrary archive presence is not lineage qualification. B06_accepted is always false. No native/build/timing command runs. |
| ownership | Owns only its new output tree and parent decoded evidence/tables. Inputs, prior bundles, binaries and baseline prefixes remain read-only; copied scripts/guides make offline replay self-contained. |
| failure | Any read/schema/hash/gate/selection/grant/write failure aborts publication and is recorded by main in this invocation-owned directory. No rollback/retry framework hides partial offline evidence. |
| cost | Dominated by selected original bytes, deterministic compression and metric/summary rows. Finite grants bound raw payload ingestion, not arbitrary Python metadata overhead. Full multi-GB bundling is explicitly scheduled separately from tiny development runs. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [Refactor.md §11.11 B06](../../../../Refactor.md), [Refactor.md §14.4](../../../../Refactor.md), [tests/integration/experimental_report.py](../../../../tests/integration/experimental_report.py) |

## B0058

[Lines 539–558](../../../../tools/build_experimental_report.py#L539); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L539-L558:sha256:a1cadecf6e840c9c25818ff58ee1eba67268ec783264c5f24336e799f57beb2a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose explicit offline report/replay controls with one diagnostic boundary. |
| inputs / outputs | Argparse admits five source roots plus accepted B05 analysis, optional sixth/replay/maps/preimages and finite byte grants, then returns process success/failure. |
| invariants | Normal mode requires all five sources; replay uses its catalog. A created-output marker permits failure.json only in newly owned output, preserving rejected reuse. Failure never yields a complete manifest. |
| ownership | Owns CLI values and a possible diagnostic file; does not own or rebuild input artifacts. |
| failure | Argument errors remain nonzero; run exceptions print one diagnostic and record failed status. Diagnostic I/O failure may propagate. |
| cost | Cold CLI and one error boundary; no per-update exception mechanism. |
| Design | [docs/experimental_report.md](../../../experimental_report.md), [tests/integration/experimental_report.py](../../../../tests/integration/experimental_report.py) |

## B0059

[Lines 559–562](../../../../tools/build_experimental_report.py#L559); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L559-L562:sha256:8a794f2c6b77bf5133b639a55d99eb34900b5c835e6fff07e6a511fd4502719a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the builder only for direct execution. |
| inputs / outputs | Module guard forwards main return status through SystemExit. |
| invariants | Importing helper definitions creates no report or subprocess. |
| ownership | Only interpreter module globals are involved. |
| failure | Preserves main process exit code. |
| cost | Constant dispatch. |
| Design | [tools/build_experimental_report.py](../../../../tools/build_experimental_report.py) |
