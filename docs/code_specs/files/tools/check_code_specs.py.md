# `tools/check_code_specs.py` — block usage map

[Source](../../../../tools/check_code_specs.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `5a45319d42f9de14b14529a3f59e86cf5863ac7243e2f54df7f254804ccd3686`. 89 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../tools/check_code_specs.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 18–30](../../../../tools/check_code_specs.py#L18) | Callable definition: def headings(path): | calls set, read_text, splitlines, startswith; returns result; 1 loop sites; source comment (unverified): # This accepts a limited ATX/backtick grammar rather than parsing all Markdown. · [reviewed contract](#b0002) |
| [B0003 · 31–31](../../../../tools/check_code_specs.py#L31) | Explanatory comments or spacing. |  |
| [B0004 · 32–84](../../../../tools/check_code_specs.py#L32) | Callable definition: def check(root=ROOT, docs=DOCS): | calls loads, read_text, set, add; guard def check(root=ROOT, docs=DOCS):; returns {'status':'pass' if not errors else 'fail','coverage':counts,'local_links_checked':links,'errors':e…; 11 loop sites; source comment (unverified): # Canonical card edits require regeneration; this checker reads saved flags/contracts. · [reviewed contract](#b0004) |
| [B0005 · 85–85](../../../../tools/check_code_specs.py#L85) | Explanatory comments or spacing. |  |
| [B0006 · 86–88](../../../../tools/check_code_specs.py#L86) | Callable definition: def main(): | calls check, print, dumps; guard result=check();print(json.dumps(result,indent=2)); returns 0 if result\['status'\]=='pass' else 1 · [reviewed contract](#b0006) |
| [B0007 · 89–89](../../../../tools/check_code_specs.py#L89) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–17](../../../../tools/check_code_specs.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load the offline saved-map/link checker without running native code. |
| inputs / outputs | Stdlib imports and ROOT/DOCS defaults defined; module import does not invoke main. |
| invariants | Checks persisted structural evidence after generation. It does not execute tests/builds, independently review semantics or regenerate missing maps. |
| ownership | Python module/path objects and later JSON/text/cache containers own ordinary memory. |
| failure | Import/syntax/OOM errors propagate; no native state or document write in module setup. |
| cost | Fixed module setup; full JSON/file/link scans happen only through check/main. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
ROOT=Path(__file__).resolve().parents[1]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the default repository root from the checker source location. |
| inputs / outputs | Resolved source-parent path out; passed as captured default to check(root=ROOT,...). |
| invariants | Custom callers must pass compatible docs explicitly; changing root argument does not recompute the already-captured docs default. |
| ownership | Owns Path value, no source/directory ownership. |
| failure | Resolve/filesystem/OOM failure propagates. |
| cost | Fixed path resolution, no inventory scan. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
DOCS=ROOT/'docs/code_specs'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the default saved-document directory. |
| inputs / outputs | ROOT/docs/code_specs Path retained for check default. |
| invariants | Checker only reads this directory; it does not regenerate documentation. |
| ownership | Ordinary Path value. |
| failure | Path/OOM failure only. |
| cost | O(path length) construction. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 18–30](../../../../tools/check_code_specs.py#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def headings(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect supported Markdown heading fragments and explicit HTML anchor IDs. |
| inputs / outputs | Markdown file Path in; set of simplified lowercase ATX slugs, duplicate numeric suffixes and a/span id strings out. |
| invariants | Only column-zero triple-backtick fence toggles and # headings recognized; no full GFM parser/tilde/bracket/fence grammar. Slug normalization is the implemented regex, not every renderer convention. |
| ownership | Owns two read_text buffers over successive reads, lines, slug counts/set and regex matches; no file mutation. |
| failure | Read/encoding/regex/OOM failures propagate; assumes document stable across its two reads. |
| cost | Two full file reads/scans plus slug string/set bookkeeping O(headings/IDs), not cached within helper. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
for line in path.read_text().splitlines():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scan heading lines while suppressing simple backtick-fenced blocks. |
| inputs / outputs | Local line iteration toggles fenced and assigns duplicate suffix from seen count. |
| invariants | Simple startswith(\`\`\`) toggles regardless of full Markdown fence matching; ignores unsupported heading forms. |
| ownership | Owns line/slug temporary values, result set and count dict. |
| failure | Regex/read/OOM errors propagate; unsupported syntax is omitted, not a parse error. |
| cost | O(file text+heading bytes), hash/dict/set storage proportional to headings. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 32–84](../../../../tools/check_code_specs.py#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check(root=ROOT, docs=DOCS):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check saved source coverage/hash/manual flags and recognized local links without writing files. |
| inputs / outputs | root and docs Paths in; status/counts/local_links_checked/errors dict out. |
| invariants | Reads coverage.json, not canonical reviewed_contracts.json; trusts saved anchor attachment/staleness flags from previous generation. Verifies current raw source hashes, inclusive line partition/counts and inventory; this is not semantic certification or re-segmentation. Independently includes exactly tools/support/CrownReplay.scala when present, matching generation without importing its inventory implementation; no broad Scala suffix or Scala AST certification is added. |
| ownership | Owns full manifest, error/name/contract sets and Markdown heading cache; source/document bytes borrowed via reads, no write/process/native resource. |
| failure | Validation mismatches accumulate errors; malformed JSON/schema/types/IO/encoding/OOM may escape instead of returning status fail. No broad handler. |
| cost | Full manifest parse+all saved raw hashes/line reads, filesystem inventory, Markdown scans and cached heading parses; memory scales with manifest/cards/links/errors. The Scala exception adds one exact helper is_file check. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
manifest=json.loads((docs/'coverage.json').read_text());errors=[];source_names=set();contracts=set();counts={'files':0,'lines':0,'blocks':0}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load persisted coverage and initialize run-local structural accounting. |
| inputs / outputs | docs/coverage.json parsed; empty errors/source_names/contracts/counts created. |
| invariants | No canonical card reload or generated-page content equivalence check; input manifest must have expected schema shape. |
| ownership | Owns full ordinary JSON graph and result sets/dicts. |
| failure | Missing/malformed/encoding/schema/OOM errors propagate. |
| cost | O(manifest bytes) read/parse/storage before individual validation begins. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
for item in manifest['files']:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check each saved file against current raw bytes and saved inclusive line coverage. |
| inputs / outputs | Manifest file record in; missing/stale/gap/manual/count errors and aggregate counters updated. |
| invariants | Reads raw SHA256 and independently normalized line count. Each block must start at cursor and end&gt;=cursor; final cursor equals saved line count+1. Parser unmatched-brace metadata itself is not a checker failure condition. |
| ownership | Source_names holds path strings; each source read buffers raw/text; blocks/contracts borrowed from manifest. |
| failure | Missing source adds error/continues; read races and schema/hash/type exceptions propagate. |
| cost | One raw hash read plus one text line-count read per saved file, per-block/per-card iterations; not source recompilation or body-hash verification. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
for contract in block.get('contracts',[]):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate nonempty saved card fields and unique saved (source,anchor) keys. |
| inputs / outputs | Attached contract dicts in; missing fields/duplicate anchor errors recorded. |
| invariants | Only truthiness checked for anchor+seven fields; no field type/reference-resolution/author/source-hash/actual-anchor text recomputation here. Canonical changes require regeneration first. |
| ownership | Reads nested manifest dicts; contracts set owns pair keys but shares immutable strings. |
| failure | Empty fields/duplicates append errors; malformed incompatible schema may raise uncaught. |
| cost | Fixed field checks per contract plus hash-set key bookkeeping; no source-wide regex anchor scans. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
suffixes={'.cpp','.cc','.c','.hpp','.h','.inc','.py','.sh','.cmake'}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile current maintained filenames against saved source names. |
| inputs / outputs | Current files in seven explicit roots plus root CMakeLists.txt and the two exact maintained Scala helpers when present; missing/surplus saved-map membership becomes errors. |
| invariants | Independent suffix/name/root policy matches generation, including .cmake.in and exactly CrownReplay.scala/ComponentReplay.scala. No global .scala suffix or implicit root pruning. The source-name set does not independently reject duplicate manifest file entries. |
| ownership | Owns filesystem Path temporaries, expected/source-name sets and sorted differences. |
| failure | Filesystem/OOM failure propagates; missing/surplus is returned error evidence. |
| cost | Full directory traversal/stat, two exact helper is_file checks and sorted set differences; this phase does not read source bytes. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md), [tools/support/ComponentReplay.scala](../../../../tools/support/ComponentReplay.scala), [docs/verification/full-scope-review-v58-2026-11-15.md](../../../verification/full-scope-review-v58-2026-11-15.md) |

```text
if manifest.get('unused_manual_overrides'):errors.append('unmatched manual contract anchors')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject unused authored anchors recorded by the prior generation. |
| inputs / outputs | Truthy manifest.unused_manual_overrides adds unmatched-manual-anchor error. |
| invariants | Does not reload current canonical to discover new/deleted/modified cards after saved generation; requires documented regenerate-then-check workflow. |
| ownership | Only reads saved manifest field; error owns small string. |
| failure | Mismatch recorded rather than thrown; malformed surrounding manifest may fail earlier. |
| cost | O(1) truth test; actual anchor matching cost belongs to generator. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
for page in docs.rglob('*.md'):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect inline non-image Markdown links matching the checker regex. |
| inputs / outputs | Every docs/**/*.md page text in; recognized destinations parsed using urlsplit. |
| invariants | Pattern omits image/escaped labels, whitespace/closing-parenthesis destinations and non-inline reference links. Scheme/netloc links are skipped without network access; no claim all renderer-supported links are covered. |
| ownership | Owns page strings/regex match lists/url records and error/cache state; no browser or network. |
| failure | Malformed URL/path/read/OOM exceptions can propagate; normal missing/bad links accumulate errors. |
| cost | Full Markdown file reads/regex scans; per-local-link filesystem resolution/checks, external links do not increment local count. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
path=(page.parent/unquote(url.path)).resolve() if url.path else page
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve recognized local links and ensure they remain inside root. |
| inputs / outputs | Decoded URL path or same page in; resolved Path checked with relative_to(root.resolve()). |
| invariants | Containment uses resolved symlinks and percent-decoded path; fragment checked separately. Count increments before validation; it is links examined, not valid-link count. |
| ownership | Owns resolved Path/strings; no linked file retained. |
| failure | Only ValueError from relative_to is caught to append escape error/continue. Other path/IO/OOM errors propagate; missing target file adds error. |
| cost | Path resolution/stat per link; no caching of source target line counts. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
try:path.relative_to(root.resolve())
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate only repository-containment ValueError into a specific link error. |
| inputs / outputs | Resolved target versus resolved root in; escape appends contextual error then skips target checks. |
| invariants | The narrow catch is necessary for malformed local links; no broad exception swallowing or retry. |
| ownership | Error string includes page/raw URL; no source/document mutation. |
| failure | Other failures remain exceptions; validation result is fail due appended error. |
| cost | Exceptional fixed branch plus O(path/URL bytes) error formatting. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if path.suffix=='.md':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check supported Markdown or source-line fragments of existing local files. |
| inputs / outputs | Decoded fragment/path in; cached heading set or Lnumber\[-Lnumber\] endpoint range checks out. |
| invariants | Markdown uses headings() limited grammar. Non-Markdown supports numeric line endpoints within file only; does not check reversed endpoint order or semantic definition targets. Other fragment shapes reject. |
| ownership | Heading cache owns per-target sets; non-Markdown each link rereads target text for line count. |
| failure | Missing fragment/range adds errors; read/parser/OOM failures propagate. |
| cost | Heading file parsed once per target; repeated source-line links each incur full target read/splitlines. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
return {'status':'pass' if not errors else 'fail','coverage':counts,'local_links_checked':links,'errors':errors}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return measured checker outcome without asserting runtime or complete semantics. |
| inputs / outputs | errors empty -&gt; pass else fail; current counters and local links examined returned. |
| invariants | Does not validate manifest aggregate totals independently or return native/test proof; early missing-source records do not add coverage counters. |
| ownership | Result takes references to run-owned errors/counts; caller owns returned dict graph. |
| failure | Ordinary result allocation can fail; no write. |
| cost | O(1) container assembly beyond accumulated evidence. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 86–88](../../../../tools/check_code_specs.py#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Print saved-map/link-check result and expose a conventional validation exit status. |
| inputs / outputs | Invokes check() with captured defaults; prints indented JSON; returns0 for pass or1 for fail. |
| invariants | No argparse; unhandled check exception bypasses normal JSON/result path. Does not run generator/build/tests. |
| ownership | Owns printed JSON temporary and result graph; writes stdout only. |
| failure | IO/validation exception propagates; computed validation failures return1. |
| cost | Full check cost plus result/errors JSON encode/stdout bytes. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0007

[Lines 89–89](../../../../tools/check_code_specs.py#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':sys.exit(main())
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exit with main return status only for script execution. |
| inputs / outputs | __name__ branch calls sys.exit(main()); import does not start check. |
| invariants | CLI flags are not parsed; script is read-only except stdout/stderr interpreter output. |
| ownership | No native/runtime/document owner or mutation. |
| failure | SystemExit carries0/1; other exceptions remain interpreter failures. |
| cost | Entry dispatch plus complete main cost when executed. |
| Design | [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |
