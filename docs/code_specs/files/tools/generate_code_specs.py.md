# `tools/generate_code_specs.py` — block usage map

[Source](../../../../tools/generate_code_specs.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `9e643d99c3a34a8a218c36b6244f7eee98711ca827f1e1b6c2a6f2f928a2570a`. 456 lines partitioned into 32 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–27](../../../../tools/generate_code_specs.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 28–28](../../../../tools/generate_code_specs.py#L28) | Callable definition: def digest(text): return hashlib.sha256(text.encode()).hexdigest() | calls sha256, encode, hexdigest; returns hashlib.sha256(text.encode()).hexdigest() · [reviewed contract](#b0002) |
| [B0003 · 29–45](../../../../tools/generate_code_specs.py#L29) | Callable definition: def contract_line(text, anchor): | calls strip, startswith, fullmatch, L; returns None; None; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 46–46](../../../../tools/generate_code_specs.py#L46) | Explanatory comments or spacing. |  |
| [B0005 · 47–49](../../../../tools/generate_code_specs.py#L47) | Callable definition: def short(text, limit=180): | calls sub, strip, len; returns text if len(text) &lt;= limit else text\[:limit - 1\] + '…' · [reviewed contract](#b0005) |
| [B0006 · 50–51](../../../../tools/generate_code_specs.py#L50) | Callable definition: def md(text): | calls str, replace; returns str(text).replace('\|','\\\|').replace('\n',' ').replace('\[','\\\[').replace('\]','\\\]').replace('\`','\… · [reviewed contract](#b0006) |
| [B0007 · 52–56](../../../../tools/generate_code_specs.py#L52) | Callable definition: def link(path, page, label=None): | calls relpath; returns f'\[{label or path}\]({rel})'; source comment (unverified): # All destinations are repository-relative paths. Final links are relative · [reviewed contract](#b0007) |
| [B0008 · 57–57](../../../../tools/generate_code_specs.py#L57) | Explanatory comments or spacing. |  |
| [B0009 · 58–68](../../../../tools/generate_code_specs.py#L58) | Callable definition: def reference(value, page): | calls startswith, split, is_file, or; returns f'\[exact paper reference\]({value})'; link(path, page, value) · [reviewed contract](#b0009) |
| [B0010 · 69–69](../../../../tools/generate_code_specs.py#L69) | Explanatory comments or spacing. |  |
| [B0011 · 70–113](../../../../tools/generate_code_specs.py#L70) | Callable definition: def lex_cpp(text): | calls list, len, mask, range; returns ''.join(chars), tokens, comments, literals; 5 loop sites; source comment (unverified): # Regex suffix slicing can copy repeatedly; this lexer is not guaranteed linear-time. · [reviewed contract](#b0011) |
| [B0012 · 114–114](../../../../tools/generate_code_specs.py#L114) | Explanatory comments or spacing. |  |
| [B0013 · 115–121](../../../../tools/generate_code_specs.py#L115) | Callable definition: def mask_preprocessor(code): | calls splitlines, lstrip, startswith, rstrip; returns ''.join(result); 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 122–122](../../../../tools/generate_code_specs.py#L122) | Explanatory comments or spacing. |  |
| [B0015 · 123–175](../../../../tools/generate_code_specs.py#L123) | Callable definition: def cpp_regions(text): | calls lex_cpp, mask_preprocessor, enumerate, append; returns text.count('\n', 0, position) + 1; definitions, {'kind': 'lexical_cpp', 'unmatched_open_braces': le…; 3 loop sites; source comment (unverified): # A constructor's braced member initializer is not its body. · [reviewed contract](#b0015) |
| [B0016 · 176–176](../../../../tools/generate_code_specs.py#L176) | Explanatory comments or spacing. |  |
| [B0017 · 177–189](../../../../tools/generate_code_specs.py#L177) | Callable definition: def python_regions(text): | calls parse, splitlines, visit, isinstance; returns result, {'kind': 'python_ast'}; 2 loop sites · [reviewed contract](#b0017) |
| [B0018 · 190–190](../../../../tools/generate_code_specs.py#L190) | Explanatory comments or spacing. |  |
| [B0019 · 191–204](../../../../tools/generate_code_specs.py#L191) | Callable definition: def cmake_regions(text): | calls splitlines, len, match, sub; returns result, {'kind': 'cmake_commands'}; 2 loop sites; source comment (unverified): # Quoted paths can contain parentheses; exclude quoted values. · [reviewed contract](#b0019) |
| [B0020 · 205–205](../../../../tools/generate_code_specs.py#L205) | Explanatory comments or spacing. |  |
| [B0021 · 206–236](../../../../tools/generate_code_specs.py#L206) | Callable definition: def regions(path, text): | calls Path, cpp_regions, endswith, python_regions; returns complete, parser; 5 loop sites; source comment (unverified): # Scaffolding gaps use at most36 lines; these are not semantic declaration boundaries. · [reviewed contract](#b0021) |
| [B0022 · 237–237](../../../../tools/generate_code_specs.py#L237) | Explanatory comments or spacing. |  |
| [B0023 · 238–272](../../../../tools/generate_code_specs.py#L238) | Callable definition: def local_facts(path, text): | calls Path, lex_cpp, findall, finditer; returns dict(calls=calls, guards=checks, throws=throws, catches=catches,; growth allocate, allocate_raw, allocate_shared, clone, copy_of, emplace; 14 loop sites; source comment (unverified): # A declaration-region fragment need not be a complete module. · [reviewed contract](#b0023) |
| [B0024 · 273–273](../../../../tools/generate_code_specs.py#L273) | Explanatory comments or spacing. |  |
| [B0025 · 274–294](../../../../tools/generate_code_specs.py#L274) | Callable definition: def structural_role(path, kind, body, signature): | calls short, lex_cpp, Path, strip; returns 'Callable definition: ' + short(signature, 130); 'Definitions sharing source lines: ' + short(signa… · [reviewed contract](#b0025) |
| [B0026 · 295–295](../../../../tools/generate_code_specs.py#L295) | Explanatory comments or spacing. |  |
| [B0027 · 296–304](../../../../tools/generate_code_specs.py#L296) | Callable definition: def load_overrides(): | calls in, exists, loads, read_text; returns result; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 305–305](../../../../tools/generate_code_specs.py#L305) | Explanatory comments or spacing. |  |
| [B0029 · 306–314](../../../../tools/generate_code_specs.py#L306) | Callable definition: def source_inventory(): | calls in, extend, rglob, is_file; returns sorted(result); 3 loop sites; source comment (unverified): # Admit only these maintained Scala helpers; legacy Scala trees remain excluded. · [reviewed contract](#b0029) |
| [B0030 · 315–316](../../../../tools/generate_code_specs.py#L315) | Explanatory comments or spacing. |  |
| [B0031 · 317–454](../../../../tools/generate_code_specs.py#L317) | Callable definition: def main(): | calls mkdir, Counter, load_overrides, set; growth new; 27 loop sites; source comment (unverified): # Documentation writes are sequential; regenerate before checking saved review flags. · [reviewed contract](#b0031) |
| [B0032 · 455–456](../../../../tools/generate_code_specs.py#L455) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0032) |

## B0001

[Lines 1–27](../../../../tools/generate_code_specs.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load the offline structural source-map generator and fixed repository destinations. |
| inputs / outputs | Imports stdlib and sibling context data; module execution defines helpers/constants, __main__ invokes generation without parsing CLI arguments. |
| invariants | Import defines functions/data but does not call main. Normal execution writes docs/code_specs; it does not edit maintained/native code or certify behavior. --help is not a supported inert flag here. |
| ownership | Python owns imported module objects, path values, constant strings/sets/tuples and subsequently generated lists/DOMs; no native MemoryAccount. |
| failure | Import/syntax/filesystem/encoding/OOM failures propagate normally; main writes are not a multi-file transaction. |
| cost | Import/data allocation and later full repository/file/JSON/Markdown scans are offline work; no native runtime instrumentation. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
ROOT = Path(__file__).resolve().parents[1]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define ROOT for the offline documentation pipeline. |
| inputs / outputs | Resolved directory above tools, derived from this source file. Read by helpers/main; no direct filesystem write in this assignment. |
| invariants | Module constants are Python objects, not independent source/proof authority. Changing roots programmatically changes later IO assumptions; no CLI configuration is implemented. |
| ownership | Path/tuple/set/string value retained by module; containers are owning ordinary Python memory. |
| failure | Expression/import/OOM failure can prevent module load; no exception handler here. |
| cost | Fixed-size initialization; ROOT.resolve may access filesystem, no source inventory traversal yet. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
SNAPSHOT = ROOT
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define SNAPSHOT for the offline documentation pipeline. |
| inputs / outputs | Aliases ROOT for source-relative paths and conditional exclusions. Read by helpers/main; no direct filesystem write in this assignment. |
| invariants | Module constants are Python objects, not independent source/proof authority. Changing roots programmatically changes later IO assumptions; no CLI configuration is implemented. |
| ownership | Path/tuple/set/string value retained by module; containers are owning ordinary Python memory. |
| failure | Expression/import/OOM failure can prevent module load; no exception handler here. |
| cost | Fixed-size initialization; ROOT.resolve may access filesystem, no source inventory traversal yet. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
OVERLAY = ROOT
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define OVERLAY for the offline documentation pipeline. |
| inputs / outputs | Aliases ROOT for displayed local links and staged path calculation. Read by helpers/main; no direct filesystem write in this assignment. |
| invariants | Module constants are Python objects, not independent source/proof authority. Changing roots programmatically changes later IO assumptions; no CLI configuration is implemented. |
| ownership | Path/tuple/set/string value retained by module; containers are owning ordinary Python memory. |
| failure | Expression/import/OOM failure can prevent module load; no exception handler here. |
| cost | Fixed-size initialization; ROOT.resolve may access filesystem, no source inventory traversal yet. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
DOCS = ROOT / 'docs/code_specs'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define DOCS for the offline documentation pipeline. |
| inputs / outputs | Fixed ROOT/docs/code_specs output destination. Read by helpers/main; no direct filesystem write in this assignment. |
| invariants | Module constants are Python objects, not independent source/proof authority. Changing roots programmatically changes later IO assumptions; no CLI configuration is implemented. |
| ownership | Path/tuple/set/string value retained by module; containers are owning ordinary Python memory. |
| failure | Expression/import/OOM failure can prevent module load; no exception handler here. |
| cost | Fixed-size initialization; ROOT.resolve may access filesystem, no source inventory traversal yet. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
BASE = DOCS
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define BASE for the offline documentation pipeline. |
| inputs / outputs | Aliases DOCS as the manual-contract input location. Read by helpers/main; no direct filesystem write in this assignment. |
| invariants | Module constants are Python objects, not independent source/proof authority. Changing roots programmatically changes later IO assumptions; no CLI configuration is implemented. |
| ownership | Path/tuple/set/string value retained by module; containers are owning ordinary Python memory. |
| failure | Expression/import/OOM failure can prevent module load; no exception handler here. |
| cost | Fixed-size initialization; ROOT.resolve may access filesystem, no source inventory traversal yet. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
FIELDS = ('purpose', 'inputs_outputs', 'invariants', 'ownership', 'failure', 'cost', 'references')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define FIELDS for the offline documentation pipeline. |
| inputs / outputs | Seven canonical semantic-card fields in rendering order. Read by helpers/main; no direct filesystem write in this assignment. |
| invariants | Module constants are Python objects, not independent source/proof authority. Changing roots programmatically changes later IO assumptions; no CLI configuration is implemented. |
| ownership | Path/tuple/set/string value retained by module; containers are owning ordinary Python memory. |
| failure | Expression/import/OOM failure can prevent module load; no exception handler here. |
| cost | Fixed-size initialization; ROOT.resolve may access filesystem, no source inventory traversal yet. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
CPP = {'.c', '.h', '.cpp', '.hpp', '.cc', '.inc'}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define CPP for the offline documentation pipeline. |
| inputs / outputs | Recognized C/C++ suffix set for lexical segmentation/facts. Read by helpers/main; no direct filesystem write in this assignment. |
| invariants | Module constants are Python objects, not independent source/proof authority. Changing roots programmatically changes later IO assumptions; no CLI configuration is implemented. |
| ownership | Path/tuple/set/string value retained by module; containers are owning ordinary Python memory. |
| failure | Expression/import/OOM failure can prevent module load; no exception handler here. |
| cost | Fixed-size initialization; ROOT.resolve may access filesystem, no source inventory traversal yet. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 28–28](../../../../tools/generate_code_specs.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest(text): return hashlib.sha256(text.encode()).hexdigest()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash the exact supplied Unicode text after default UTF8 encoding. |
| inputs / outputs | str in; lowercase SHA256 hex string out. |
| invariants | No file read or newline normalization occurs inside digest. main decodes valid UTF8 source bytes without newline conversion and caches this digest once per file; re-encoding preserves the original valid UTF8 bytes. |
| ownership | Owns encoded temporary bytes and64-character result; input string borrowed. |
| failure | Encoding/type/OOM failure propagates. |
| cost | O(text UTF8 bytes) encode+hash with full encoded-byte temporary allocation. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 29–45](../../../../tools/generate_code_specs.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def contract_line(text, anchor):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a unique literal anchor or a checksum-bound exact source span without guessing between repeated syntax. |
| inputs / outputs | Source text and authored anchor string in; one-based start line or None out. Reserved span syntax is @source-span:Lfirst-Llast:sha256:lowercase64hex. |
| invariants | Span endpoints are canonical positive ASCII integers, ordered and inside the source line count; the digest binds exact UTF-8 line text including line endings. Impossible endpoint digit widths reject before integer conversion. A malformed reserved span never falls back to literal matching. Other anchors keep exact-then-whitespace-flexible uniqueness lookup. This is content/location identity, not AST identity or proof authority. |
| ownership | Borrows source/anchor strings. Literal lookup owns regex matches; span lookup owns a split line list, selected text and digest. Returns only a scalar location; no source mutation or retained owner. |
| failure | Malformed, out-of-file, reversed or checksum-mismatched spans and ambiguous/absent literal anchors return None. Type, regex, allocation and source-encoding errors propagate. Very wide numeric endpoints return None without relying on conversion exceptions. |
| cost | Literal mode scans the source once or twice and counts prefix newlines, retaining match lists. Span mode scans the anchor, splits source lines, joins/hashes the selected span and returns its start: offline O(anchor length plus source text plus span bytes) work/storage, no native process or update hook. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md), [docs/code_specs/anchor_format.md](../../anchor_format.md) |

## B0005

[Lines 47–49](../../../../tools/generate_code_specs.py#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def short(text, limit=180):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a bounded one-line display signature. |
| inputs / outputs | Text and display limit(default180) in; collapsed whitespace text or truncated text+ellipsis out. |
| invariants | Limit is display width, not parser/semantic input limit; no guard for arbitrary nonpositive custom limits. |
| ownership | Owns normalized/truncated string; source unchanged. |
| failure | Type/regex/OOM failure propagates. |
| cost | O(input characters) regex normalization/copy; truncation allocates another bounded string. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 50–51](../../../../tools/generate_code_specs.py#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def md(text):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Escape selected Markdown table/inline syntax in a display value. |
| inputs / outputs | Any str-convertible object in; string with pipe/newline/bracket/backtick/angle replacements out. |
| invariants | This is a fixed display escape sequence, not a full Markdown/HTML sanitizer or URL encoder. |
| ownership | Several successive owning string replacements; no source mutation. |
| failure | str conversion/OOM errors propagate. |
| cost | Several O(string length) passes/temporary strings; output may grow through escapes. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0007

[Lines 52–56](../../../../tools/generate_code_specs.py#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def link(path, page, label=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render a repository-oriented relative Markdown link. |
| inputs / outputs | Path string, destination page Path, optional label in; Markdown link string out via os.path.relpath(OVERLAY/path,page.parent). |
| invariants | Assumes trusted repository-relative authored paths; does not itself enforce containment, percent-encode spaces/parentheses, or prove target existence. Checker later examines recognized links. |
| ownership | Owns Path/relative/output text temporaries; does not retain linked file or open it. |
| failure | Path/relpath/type/OOM failures propagate; no output write here. |
| cost | O(path/label bytes) path manipulation/string construction; not a filesystem traversal. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0009

[Lines 58–68](../../../../tools/generate_code_specs.py#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def reference(value, page):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render recognized design references or escaped plain descriptive text. |
| inputs / outputs | Reference string and page Path in; http-prefixed link, existing local-file link, exact P1/P2 arXiv fallback, or md(value) out. |
| invariants | Local path drops trailing " §" description for existence check. Unknown/missing references become plain text and are not rejected; checker cannot validate an unrendered reference as a link. |
| ownership | Owning returned text; filesystem is only queried for local existence. |
| failure | Path/stat/type/format/OOM errors propagate; absence takes fallback rather than failure. |
| cost | Fixed branch tests plus up to two file-existence queries and O(reference bytes) formatting. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0011

[Lines 70–113](../../../../tools/generate_code_specs.py#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def lex_cpp(text):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mask C++ comments/literals for structural scans while retaining complete literal bytes in token evidence. |
| inputs / outputs | Full/fragment source text in; same-position masked string, tool-defined lexical token list, comment offsets/text and literal token list out. |
| invariants | Preserves newline/offset positions and leaves @ at each literal start; recognizes line/block comments, supported prefixed quoted/raw literals and numeric digit separators. This is a lexical heuristic, not C++ preprocessing/grammar/compilation. |
| ownership | Owns full char list/masked string, copied token/comment/literal slices and lists; token/literal equality includes raw bodies and spelling, not just placeholders. |
| failure | Unterminated block comment/raw string raises ValueError. Ordinary quote EOF has no dedicated diagnostic; malformed trailing escape can overrun mask indexing. Type/regex/OOM failures propagate. |
| cost | O(source+token/comment/literal storage); repeated text\[i:\] regex argument slices can make many short tokens quadratic total copied characters. No linear-time or allocation-free claim. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
def mask(a, b):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Blank one lexical comment/literal span while preserving its source newlines. |
| inputs / outputs | Nested mask(a,b) mutates captured chars for positions in range. |
| invariants | Caller supplies valid span; newline bytes stay newline, every other character becomes space before optional @ insertion. |
| ownership | Borrows captured full chars list; no new backing owner or source mutation. |
| failure | Invalid indices would propagate; lex_cpp controls boundaries. |
| cost | O(span length) list writes; only fixed loop state beyond existing char array. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
while i < n:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tokenize by advancing a source offset through whitespace, comments, literals or one regex token. |
| inputs / outputs | Each branch appends owning evidence and advances i; returns only after entire input consumed. |
| invariants | Comment markers inside recognized literals remain literal bytes; apostrophe after alphanumeric is treated as digit-separator context, not a full numeric/C++ grammar check. |
| ownership | Owns evidence slices; substring regex matching materializes suffix strings repeatedly. |
| failure | Malformed block/raw literal raises before return; quoted EOF is not separately rejected. |
| cost | Full logical traversal with possible quadratic suffix-copy overhead and O(source+evidence) retained storage. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0013

[Lines 115–121](../../../../tools/generate_code_specs.py#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def mask_preprocessor(code):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide preprocessor directive lines and their backslash continuations from brace recognition. |
| inputs / outputs | Already masked code string in; string retaining nondirective lines/newline structure out. |
| invariants | Line starts after lstrip # or prior continuation define directives; continuation tests last nonspace backslash. Does not evaluate macros/conditional branches or full line-splicing grammar. |
| ownership | Owns per-line/result strings and list; input unchanged. |
| failure | Type/regex/OOM failures propagate. |
| cost | O(source characters) split/regex/copy with additional full output storage. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0015

[Lines 123–175](../../../../tools/generate_code_specs.py#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def cpp_regions(text):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify approximate C++ definitions and brace diagnostics from lexical text. |
| inputs / outputs | Text in; line-range definition tuples and lexical_cpp unmatched brace counts out. |
| invariants | Pairs braces after masking comments/literals/directives, recursively enters namespaces and types spanning&gt;22 line difference; stores shorter types as one region. Parentheses/signatures/initializers/function-try handlers are heuristics, not compiler AST. |
| ownership | Owns masked strings, brace stacks/dictionaries, definition tuples and recursive scan state; no source edits. |
| failure | Lexer/regex/recursion/OOM failures propagate; unmatched braces are returned metadata, not automatic rejection by checker. |
| cost | Brace scan O(source); repeated head/tail slices and prefix newline counts add source×definition work, lexical suffix-copy costs persist; recursion can hit Python recursion limit. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
def line(position): return text.count('\n', 0, position) + 1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate a character offset to the original source line. |
| inputs / outputs | Nested line(position) in; text.count newline prefix+1 out. |
| invariants | Offsets belong to same unchanged text; no cached line index. |
| ownership | Borrows original source; scalar result. |
| failure | Bad type/range assumptions not explicitly guarded. |
| cost | O(prefix characters) scan on every invocation, not O(1) lookup. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
def scan(begin, end, parent=''):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Walk one brace-bounded lexical scope and append candidate definition spans. |
| inputs / outputs | begin/end/parent in; mutates captured definitions by recursively visiting namespaces/long types and recording short types/callables. |
| invariants | Semicolon/closing brace boundaries determine candidate head. Braced member initializer is skipped as callable body; repeated catches extend same callable. Only paired braces are entered. |
| ownership | Captured code/pairs/text borrowed; fresh head/cleaned/tail strings and tuple records owned. |
| failure | Regex/lexer/recursive depth/OOM failures propagate; classification is approximate and complete line coverage comes later from gap filling. |
| cost | Visits scope characters plus repeated head/tail/prefix scans; nested calls retain recursive frames, with no compiler-complexity guarantee. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
# A constructor's braced member initializer is not its body.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate likely constructor member-initializer braces from function bodies. |
| inputs / outputs | Head parenthesis balance/colon/name suffix heuristics in; initializer Boolean used to retain pending signature. |
| invariants | Heuristic supports ordinary maintained patterns but cannot certify all template/requires/initializer syntax. |
| ownership | Owning temporary cleaned head strings; no symbol graph. |
| failure | No explicit unknown-syntax error; unmatched patterns fall into structural gaps. |
| cost | Regex/head-length work per candidate brace. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
elif callable_body:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extend an observed callable over adjacent catch handlers. |
| inputs / outputs | Paired body end in; repeatedly consumes whitespace+catch(...) { paired body } and records one full callable span. |
| invariants | Catch regex does not parse arbitrary nested parentheses in exception declarations; only recognized adjacent syntax is included. |
| ownership | Owns repeated tail slices; definitions hold scalar ranges/signatures. |
| failure | Missing paired handler brace stops extension rather than proving valid C++. |
| cost | Repeated remaining-scope tail copies plus regex checks; exceptional runtime behavior is not executed or analyzed. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0017

[Lines 177–189](../../../../tools/generate_code_specs.py#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def python_regions(text):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Locate Python function definitions using the standard AST rather than executing source. |
| inputs / outputs | Python text in; definition spans and python_ast metadata out. |
| invariants | Visits module/class bodies for functions/async functions and decorators; does not descend into function bodies or functions nested inside if/try/other module statements. Classes themselves are not emitted; uncovered lines become scaffolding. |
| ownership | Owns full AST, split lines and result records during call; no module import or user execution. |
| failure | SyntaxError/AST recursion/MemoryError propagate; no broad parser-error catch. |
| cost | AST parse/storage O(source/AST size), traversal of visited definition/class lists; line splitting and signature copy costs add. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
def visit(nodes, parent=''):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit direct module/class Python definitions and track class parent label. |
| inputs / outputs | Nested visit(nodes,parent) appends function/decorator ranges or recursively visits class.body. |
| invariants | Does not recursively enumerate local functions within a function or arbitrary control-flow nodes. Absence from callable list is not absence of executable code. |
| ownership | Borrows AST/lists/lines; appends independent scalar/signature tuples. |
| failure | AST metadata/recursion/OOM errors propagate. |
| cost | O(visited direct definitions); class recursion stack, no call graph or runtime execution. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0019

[Lines 191–204](../../../../tools/generate_code_specs.py#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def cmake_regions(text):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group likely CMake commands by parenthesis balance. |
| inputs / outputs | CMake lines in; build-command line spans plus cmake_commands marker out. |
| invariants | Matches leading identifier followed by (, strips simple double-quoted fragments then # suffix, counts parentheses until depth&lt;=0/EOF. Bracket arguments/comments, escaping and full CMake grammar are not parsed. |
| ownership | Owns split lines, stripped strings and result tuples; no cmake process or configure/build writes. |
| failure | No explicit unmatched-parenthesis error; EOF span can still be emitted. Regex/OOM errors propagate. |
| cost | Line scanning/regex/copy proportional to visited text under simple matches; result storage proportional to recognized commands. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0021

[Lines 206–236](../../../../tools/generate_code_specs.py#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def regions(path, text):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine detected definitions with declaration chunks so every saved source line belongs to a region. |
| inputs / outputs | Path/text in; contiguous inclusive regions covering splitlines plus parser metadata out. |
| invariants | Dispatches known C++/Python/CMake, including .cmake.in templates; substitution placeholders remain structural gaps and are not configured/executed. Other scripts get gap regions. Overlapping/shared-line definitions merge; remaining gaps split at most36 lines, preferring a blank after the first5. Structural chunks do not establish complete declarations or semantic proof. |
| ownership | Owns sorted/merged/full result lists and source lines; source unchanged. |
| failure | Underlying parser/type/OOM failures propagate; no human-contract creation from mere region coverage. |
| cost | Sorting O(definitions log definitions), line/body splitting/signature strings and gap chunks; parser/lexical costs dominate for complex sources. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
def gap(start, end):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Partition unmatched lines into bounded declaration/scaffolding ranges. |
| inputs / outputs | Nested gap(start,end) appends inclusive chunks with display title from first two nonempty lines. |
| invariants | stop&lt;=start+35 gives36-line chunks; blank preference is formatting-sensitive and can split an owning dict/declaration across chunks. This is not an AST-body proof boundary. |
| ownership | Borrows split lines and complete list; owns chunk records/display strings. |
| failure | No code execution or semantic failure inference; allocation/type errors propagate. |
| cost | O(gap lines) slices/filtering with small bounded chunk scans, plus title normalization. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0023

[Lines 238–272](../../../../tools/generate_code_specs.py#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def local_facts(path, text):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect syntactic calls/guards/errors/growth/loops/returns/comments as inspection evidence. |
| inputs / outputs | Path/body fragment in; dict of detected evidence lists/counts out. |
| invariants | C++ masks comments/literals first. Python/other code retains ordinary text for regex facts, so literals/comments can create false positives. Calls deduplicate names and exclude a fixed ignore set; indirect/transitive effects and actual complexity/allocation are not certified. |
| ownership | Owns regex match-derived strings/lists/sets and Python comment-token offsets; no executable source or native owner retained. |
| failure | Only Python fragment TokenError/IndentationError is suppressed to retain partial comment evidence; all other errors propagate. |
| cost | Several body regex scans, optional lex_cpp and tokenizer; unique-call list membership can be quadratic in distinct names; comments count prefix newlines separately. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
try:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain comment tokens observed before incomplete Python fragment tokenization stops. |
| inputs / outputs | Token stream for body fragment in; append comment offset/text to local evidence. |
| invariants | Declaration chunks may not be complete Python modules; these two tokenizer errors do not invalidate source-level AST parsing performed separately for a complete module. |
| ownership | Tokenizer/StringIO and partial comment list owned locally. |
| failure | Catches exactly TokenError and IndentationError, then continues evidence extraction; not a semantic-validation success or catch-all. |
| cost | Fragment tokenization/time/storage and partial-prefix work still incurred when exception is suppressed. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0025

[Lines 274–294](../../../../tools/generate_code_specs.py#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def structural_role(path, kind, body, signature):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign a display-only structural role to a mapped region. |
| inputs / outputs | Path/kind/body/signature in; human-readable kind or regex-derived declaration role out. |
| invariants | Callable/type/CMake kind returns fast description; scaffolds use token/string heuristics for imports/preprocessor/aliases/types/signatures/defaults. No semantic proof or owning-data invariant inferred. |
| ownership | Owns role strings/list and optional C++ masked body. |
| failure | Lexer/regex/type/OOM errors propagate. |
| cost | Fixed regex passes over scaffold body plus optional lexical work; exact short role output allocated. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0027

[Lines 296–304](../../../../tools/generate_code_specs.py#L296); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def load_overrides():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load authored semantic overrides from the canonical JSON input. |
| inputs / outputs | BASE/reviewed_contracts.json when present in; list or dict.blocks/dict.contracts records extended into result out. |
| invariants | Missing file gives empty list. No comprehensive schema/type/duplicate/hash/anchor validation here; main and checker perform their narrower stages later. |
| ownership | Owns parsed full ordinary JSON/list data; nested card strings/lists retained for whole generation. |
| failure | Malformed JSON/encoding/types/filesystem/OOM errors propagate; no fallback to generic semantic certification. |
| cost | O(canonical JSON bytes) read/parse/storage; all authored cards remain resident while per-source matching runs. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0029

[Lines 306–314](../../../../tools/generate_code_specs.py#L306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def source_inventory():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate maintained code within explicit roots and suffix/name filters, plus the two exact maintained Scala verification helpers when present. |
| inputs / outputs | ROOT in; sorted selected Paths from root CMakeLists.txt and seven maintained roots out, adding tools/support/CrownReplay.scala and tools/support/ComponentReplay.scala only when each is a file. |
| invariants | Suffix/name filters remain unchanged. Only the two explicit Scala helpers are admitted; unrelated/legacy/vendor Scala stays excluded. Generic script regions do not claim Scala AST or method completeness. Existing directory traversal has no implicit gitignore pruning. |
| ownership | Owns the sorted Path list; filesystem resources are borrowed during traversal/is_file checks; source files are not written. |
| failure | Traversal/stat/permission/OOM errors propagate; an absent explicit helper is omitted. Source read/decode failures belong to the later caller. |
| cost | Existing explicit-root traversal/stat and sorting O(selected files log selected files), plus two fixed is_file checks; selected Path-list storage is proportional to its output. Offline only. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/support/CrownReplay.scala](../../../../tools/support/CrownReplay.scala), [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py), [docs/code_specs/README.md](../../README.md), [docs/legacy_baselines.md](../../../legacy_baselines.md), [tools/support/ComponentReplay.scala](../../../../tools/support/ComponentReplay.scala), [docs/verification/full-scope-review-v58-2026-11-15.md](../../../verification/full-scope-review-v58-2026-11-15.md) |

## B0031

[Lines 317–454](../../../../tools/generate_code_specs.py#L317); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate saved structural maps and attach only explicitly authored scoped contracts. |
| inputs / outputs | Fixed roots plus canonical overrides/current code in; per-file Markdown, coverage.json, subsystem_contracts.md, README.md and primitives.md tail out. |
| invariants | Normal writes stay under DOCS, but are sequential/nontransactional and may leave mixed output after failure. No native code write/build/process. Does not delete obsolete pages; unmatched overrides only print here, checker enforces later. |
| ownership | Owns all entries/evidence/cards/overrides/comments and per-page strings/JSON dumps; inherits shared context through shallow dict copy with separately filtered references. |
| failure | IO/parse/anchor-field/type/regex/OOM errors propagate; unused overrides do not make main return nonzero itself. Existing primitives prefix before heading is preserved. |
| cost | Full inventory/source parsing, one source digest per file, repeated per-file override and block/location scans, page rendering and whole-manifest JSON. Offline heap/IO work; no native complexity claim. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
for source in source_inventory():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read each inventoried source and build its scoped map against fixed current bytes. |
| inputs / outputs | File Path in; exact UTF8 source text, one cached whole-file hash, family context, spans and matching-card line table built. |
| invariants | read_bytes().decode(UTF8) preserves CRLF and all accepted source bytes for hashing. staged Path is computed but not written. Only path-matching anchors are located; absent/ambiguous anchors remain unused. |
| ownership | Owns source string/context copy/spans/locations; no code import or source mutation. |
| failure | Read/encoding/parser/invalid override fields errors propagate; source disappearance is skipped after is_file check, with no snapshot lock. |
| cost | One full source read, decode and encode/hash per file plus parser work; scans all overrides for each file and regex scans each matching anchor. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
for number, span in enumerate(spans, 1):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Save one complete line-region record and syntactic evidence. |
| inputs / outputs | Inclusive span in; body joined, role/evidence/default structural_only and up to12 preceding // comment lines attached. |
| invariants | Nearby documentation is evidence only; it does not turn block into scoped semantic certification. Body chunks can be declaration fragments. |
| ownership | Owns body/evidence/comment lists and block dict; source unchanged. |
| failure | Lexer/tokenizer/schema/OOM failures propagate; only local_facts narrow tokenizer suppression applies. |
| cost | Per-block body copy/regex/lex work; nearby scan bounded12 lines, total records retained until serialization. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
for oi, location in locations.items():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach matching authored cards and preserve whole-file review staleness. |
| inputs / outputs | Per-source anchor locations and override records in; matching block gets anchor+seven fields, ORed manual_review_stale, review level and used mark. |
| invariants | Card scope is its anchor, not all code sharing the block. A reviewed_source_sha256 differing from the cached exact source hash marks the block stale; unused anchors remain reportable. |
| ownership | Copies card dict fields shallowly into entry; original nested references/strings share Python objects until JSON rendering. |
| failure | Malformed required anchor access or data types may raise; missing fields copied selectively then checker detects emptiness. Hash update must follow actual human review, not silence staleness. |
| cost | Each block scans matching locations and compares cached hash strings for attached cards. Source bytes are hashed once per file, without per-card re-encoding/hashing. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if Path(path).suffix in CPP:
            _, _, found_comments, _ = lex_cpp(text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inventory C++ source comments without asserting individual correctness. |
| inputs / outputs | Whole C++ text re-lexed; each comment range/text/temporal-marker/disposition appended to local comments list. |
| invariants | Temporal marker is regex suspicion only. This list is accumulated but not inserted into payload or written by main; saved block evidence separately retains comments. |
| ownership | Owns another whole lex result and comment dicts for duration of generation; no output audit mutation. |
| failure | Lexer/regex/OOM failures propagate. |
| cost | Additional full-file lexical pass and comment-prefix newline counts, with retained unused comments storage. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
entry = dict(source_path=path, before_sha256=source_hash, staged_sha256=source_hash,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record file-level source hash/line count/parser/context and current blocks. |
| inputs / outputs | Exact source text, cached source_hash, family and blocks in; entry and aggregate Counter updated. |
| invariants | before/staged hashes both use the exact current UTF8 source hash; source_changed=false records no source write. Exact-path ROLES labels take priority, then stem roles, then family purpose. |
| ownership | Entries retain full evidence/card lists; file-role strings are shared immutable Python text. |
| failure | Hash/field/OOM errors propagate; no semantic validation from subsystem role. |
| cost | Cached hash assignment, path-priority/stem dictionary lookups and totals over blocks; ordinary metadata allocations. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
page = DOCS / 'files' / (path + '.md'); page.parent.mkdir(parents=True, exist_ok=True)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render a per-source inspection page with exact current line links. |
| inputs / outputs | Entry/blocks/context in; local rows built then page.write_text replaces one Markdown file under DOCS/files. |
| invariants | Table explicitly says structural-only; snippets bounded while JSON facts retained; reviewed contract headings apply only to authored anchor. Links are relative and later checked by recognized syntax. |
| ownership | Owns row list/full page string and filesystem output; no atomic temporary/rename used. |
| failure | mkdir/write/format/reference errors can leave partial/current page with other pages still old. |
| cost | O(displayed blocks+all rendered card/text bytes) construction/write; OOM/IO outside native runtime. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
exclusions = [dict(path=p, reason='Active W02 source and contract belong to root; integrate root-authored blocks after the rewrite.')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build descriptive exclusions and coverage manifest payload. |
| inputs / outputs | Entry/totals/unused override state in; compact coverage.json object written. |
| invariants | Coverage meaning is line partition only. Weighted exclusions are conditional on absence; general fixture/vendor description does not override source_inventory recursion inside roots. |
| ownership | Payload shares entry/override graph until json.dumps allocates full serialized manifest; write is direct/truncating. |
| failure | Serialization/IO/OOM failure propagates after already-written per-file pages; unused override records remain explicit. |
| cost | Full retained manifest serialization and output bytes, not streaming or multi-file transactional publication. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
page = DOCS / 'subsystem_contracts.md'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render shared subsystem context separately from block contracts. |
| inputs / outputs | CONTRACTS mapping in; per-family seven-field Markdown context under subsystem_contracts.md out. |
| invariants | Does not assign family invariants to arbitrary scaffolds; filters nonexistent local reference paths, so typo/deleted reference can silently disappear. |
| ownership | Shallow references/string reads; page rows/output own ordinary text. |
| failure | Missing expected family fields/write/OOM errors propagate; filtered references are not an error here. |
| cost | O(all context text/reference existence queries) plus page construction/write. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
page = DOCS / 'README.md'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render the overall source index and explicit review workflow/limitations. |
| inputs / outputs | Totals and entry summaries in; README.md rewritten with counts, context, source tables and reproduction commands. |
| invariants | Generated counts identify this run only; test inventory is not execution, structural maps are not full semantics. Link/source/hash validation remains separate checker invocation. Comment-only edits preserve executable tokens; diagnostic-string corrections intentionally change literal tokens and require separate evidence. |
| ownership | Owns complete index rows/string; stored context strings reused until render. |
| failure | Write/format/OOM errors propagate after earlier outputs may already have changed. |
| cost | O(file count+README text bytes), direct filesystem replacement. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
primitive=DOCS/'primitives.md'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render a compact per-source index linking to every retained individual block contract. |
| inputs / outputs | Saved entries, block contracts and preserved primitive-guide prefix in; one file link/count/usage row per source containing scoped contracts out. |
| invariants | All individual seven-field contracts remain in their per-source pages. Counts are scoped-card totals; a listed file is not certified fully reviewed. Full structural inventory and missing review scopes remain in README/coverage. |
| ownership | Owns compact index row strings; it does not duplicate every contract purpose/cost into a second long table. |
| failure | Read/write/format/OOM failure propagates; no rollback for earlier output pages. |
| cost | One scan of saved source blocks plus one short output row per source with contracts; offline formatting/IO, no native runtime work. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0032

[Lines 455–456](../../../../tools/generate_code_specs.py#L455); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__': main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run generation only when this source is executed as the entry script. |
| inputs / outputs | __name__ test calls main; ordinary import does not call main. |
| invariants | No argparse/sys.argv gate; callers must not assume --help or unknown arguments avoid writes. |
| ownership | main owns resulting documentation paths/objects; script itself owns no runtime account. |
| failure | Uncaught errors yield interpreter failure; unused anchor diagnostic alone does not force failure. |
| cost | Full main generation cost only on script-entry branch. |
| Design | [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tools/check_code_specs.py](../../../../tools/check_code_specs.py), [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |
