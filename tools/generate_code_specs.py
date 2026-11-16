#!/usr/bin/env python3
"""Generate reviewable source-block maps without editing executable code.

C++ segmentation is lexical, Python segmentation uses ast, and CMake uses
balanced commands. The output explicitly separates these facts from manually
reviewed semantic contracts. No compiler/call-graph completeness is claimed.
"""
from __future__ import annotations
import ast
import hashlib
import io
import json
import os
from pathlib import Path
import re
import tokenize
from collections import Counter
from code_specs_support import CONTRACTS, ROLES, family

ROOT = Path(__file__).resolve().parents[1]
SNAPSHOT = ROOT
OVERLAY = ROOT
DOCS = ROOT / 'docs/code_specs'
BASE = DOCS
FIELDS = ('purpose', 'inputs_outputs', 'invariants', 'ownership', 'failure', 'cost', 'references')
CPP = {'.c', '.h', '.cpp', '.hpp', '.cc', '.inc'}

def digest(text): return hashlib.sha256(text.encode()).hexdigest()
def contract_line(text, anchor):
    """Locate one authored source anchor without guessing between declarations."""
    if not anchor.strip(): return None
    if anchor.startswith('@source-span:'):
        match = re.fullmatch(r'@source-span:L([1-9][0-9]*)-L([1-9][0-9]*):sha256:([0-9a-f]{64})', anchor)
        if not match: return None
        lines = text.splitlines(keepends=True)
        max_digits = len(str(len(lines)))
        if len(match[1]) > max_digits or len(match[2]) > max_digits: return None
        first, last = int(match[1]), int(match[2])
        if first > last or last > len(lines): return None
        return first if digest(''.join(lines[first - 1:last])) == match[3] else None
    matches = list(re.finditer(re.escape(anchor), text))
    if len(matches) != 1:
        matches = list(re.finditer(r'\s+'.join(re.escape(word) for word in anchor.split()), text))
    if len(matches) != 1: return None
    return text.count('\n', 0, matches[0].start()) + 1

def short(text, limit=180):
    text = re.sub(r'\s+', ' ', text).strip()
    return text if len(text) <= limit else text[:limit - 1] + '…'
def md(text):
    return str(text).replace('|','\\|').replace('\n',' ').replace('[','\\[').replace(']','\\]').replace('`','\\`').replace('<','&lt;').replace('>','&gt;')
def link(path, page, label=None):
    # All destinations are repository-relative paths. Final links are relative
    # to the generated page so the overlay can be copied into the repository.
    rel = os.path.relpath(OVERLAY / path, page.parent)
    return f'[{label or path}]({rel})'

def reference(value, page):
    if value.startswith('http'):
        return f'[exact paper reference]({value})'
    path = value.split(' §', 1)[0]
    if (ROOT / path).is_file() or (OVERLAY / path).is_file():
        return link(path, page, value)
    if value.startswith('P1 arXiv:2301.04003v2'):
        return f'[{value}](https://arxiv.org/pdf/2301.04003v2)'
    if value.startswith('P2 arXiv:2603.14754v1'):
        return f'[{value}](https://arxiv.org/pdf/2603.14754v1)'
    return md(value)

def lex_cpp(text):
    """Mask comments/strings while retaining offsets and newlines; retain tokens.

    The returned token stream keeps literal bytes, including raw-string bodies,
    so token equality cannot mistake text inside a literal for a comment edit.
    """
    # Regex suffix slicing can copy repeatedly; this lexer is not guaranteed linear-time.
    chars = list(text)
    tokens, comments, literals = [], [], []
    i, n = 0, len(text)
    def mask(a, b):
        for j in range(a, b):
            if chars[j] != '\n': chars[j] = ' '
    while i < n:
        if text[i].isspace(): i += 1; continue
        if text.startswith('//', i):
            end = text.find('\n', i)
            if end < 0: end = n
            comments.append((i, end, text[i:end])); mask(i, end); i = end; continue
        if text.startswith('/*', i):
            end = text.find('*/', i + 2)
            if end < 0: raise ValueError('unterminated block comment')
            end += 2; comments.append((i, end, text[i:end])); mask(i, end); i = end; continue
        raw = re.match(r'(?:u8|u|U|L)?R"([^ ()\\\t\r\n]{0,16})\(', text[i:])
        if raw:
            stop = ')' + raw.group(1) + '"'
            end = text.find(stop, i + raw.end())
            if end < 0: raise ValueError('unterminated raw string')
            end += len(stop)
            tokens.append(text[i:end]); literals.append(text[i:end]); mask(i, end)
            chars[i] = '@'; i = end; continue
        quoted = re.match(r'(?:u8|u|U|L)?["\']', text[i:])
        # Digit separators (1'000) are not character literals.
        if quoted and not (text[i] == "'" and i > 0 and text[i - 1].isalnum()):
            quote = quoted.group()[-1]; end = i + quoted.end()
            while end < n:
                if text[end] == '\\': end += 2
                elif text[end] == quote: end += 1; break
                else: end += 1
            tokens.append(text[i:end]); literals.append(text[i:end]); mask(i, end)
            chars[i] = '@'; i = end; continue
        token = re.match(r'[A-Za-z_]\w*|[0-9][A-Za-z0-9_.\']*|::|->\*|->|<=>|<<=|>>=|&&|\|\||==|!=|<=|>=|\+\+|--|\+=|-=|\*=|/=|%=|<<|>>|\.\.\.|##|.', text[i:])
        value = token.group(); tokens.append(value); i += len(value)
    return ''.join(chars), tokens, comments, literals

def mask_preprocessor(code):
    result, continuation = [], False
    for line in code.splitlines(keepends=True):
        is_directive = continuation or line.lstrip().startswith('#')
        continuation = is_directive and line.rstrip('\r\n').rstrip().endswith('\\')
        result.append(re.sub(r'[^\n]', ' ', line) if is_directive else line)
    return ''.join(result)

def cpp_regions(text):
    masked, _, _, _ = lex_cpp(text)
    code = mask_preprocessor(masked)
    stack, pairs, unmatched = [], {}, []
    for i, ch in enumerate(code):
        if ch == '{': stack.append(i)
        elif ch == '}':
            if stack: pairs[stack.pop()] = i
            else: unmatched.append(i)
    definitions = []
    def line(position): return text.count('\n', 0, position) + 1
    def scan(begin, end, parent=''):
        segment, i = begin, begin
        while i < end:
            ch = code[i]
            if ch == ';': segment = i + 1
            elif ch == '{' and i in pairs:
                close = pairs[i]
                if close > end: break
                raw_head = code[segment:i]
                head = re.sub(r'\s+', ' ', raw_head).strip()
                first = segment + len(raw_head) - len(raw_head.lstrip())
                is_namespace = bool(re.search(r'\bnamespace(?:\s+[\w:]+)?\s*$', head)) or head.startswith('extern @')
                cleaned = re.sub(r'template\s*<[^;{}]+?>', '', head).strip()
                is_type = bool(re.search(r'^(?:(?:public|private|protected):\s*)?(?:enum(?:\s+class)?|struct|class)\s+[\w:]+[^;()]*$', cleaned))
                # A constructor's braced member initializer is not its body.
                initializer = bool(head.count('(')>head.count(')') or (re.search(r'\)\s*(?:noexcept\s*)?:', head) and re.search(r'\b\w+\s*$', head) and not head.endswith(('noexcept','try','const','override','final'))))
                callable_body = '(' in head and not is_type and not is_namespace and not initializer
                if is_namespace:
                    scan(i + 1, close, head)
                elif is_type:
                    if line(close) - line(first) > 22:
                        scan(i + 1, close, head)
                    else:
                        definitions.append((line(first), line(close), 'type', short(text[first:i]), parent))
                elif callable_body:
                    # Include function-try-block handlers in the same operation.
                    final = close
                    while True:
                        tail = code[final + 1:end]
                        match = re.match(r'\s*catch\s*\([^)]*\)\s*\{', tail)
                        if not match: break
                        brace = final + match.end()
                        if brace not in pairs: break
                        final = pairs[brace]
                    definitions.append((line(first), line(final), 'callable', short(text[first:i]), parent))
                    close = final
                # Keep a braced initializer in the pending declaration/signature.
                if not initializer: segment = close + 1
                i = close
            i += 1
    scan(0, len(code))
    return definitions, {'kind': 'lexical_cpp', 'unmatched_open_braces': len(stack), 'unmatched_close_braces': len(unmatched)}

def python_regions(text):
    tree = ast.parse(text)
    result = []
    lines = text.splitlines()
    def visit(nodes, parent=''):
        for node in nodes:
            if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef)):
                start = min([node.lineno] + [d.lineno for d in node.decorator_list])
                result.append((start, node.end_lineno, 'callable', short(lines[node.lineno - 1]), parent))
            elif isinstance(node, ast.ClassDef):
                visit(node.body, node.name)
    visit(tree.body)
    return result, {'kind': 'python_ast'}

def cmake_regions(text):
    lines = text.splitlines(); result = []; i = 0
    while i < len(lines):
        if re.match(r'^\s*[A-Za-z_]\w*\s*\(', lines[i]):
            start = i; depth = 0
            while i < len(lines):
                # Quoted paths can contain parentheses; exclude quoted values.
                stripped = re.sub(r'"(?:\\.|[^"\\])*"', '""', lines[i]).split('#', 1)[0]
                depth += stripped.count('(') - stripped.count(')')
                if depth <= 0: break
                i += 1
            result.append((start + 1, min(i + 1, len(lines)), 'build-command', short(lines[start]), ''))
        i += 1
    return result, {'kind': 'cmake_commands'}

def regions(path, text):
    # Scaffolding gaps use at most36 lines; these are not semantic declaration boundaries.
    if Path(path).suffix in CPP: found, parser = cpp_regions(text)
    elif path.endswith('.py'): found, parser = python_regions(text)
    elif path.endswith(('.cmake', '.cmake.in', 'CMakeLists.txt')): found, parser = cmake_regions(text)
    else: found, parser = [], {'kind': 'script_regions'}
    total = len(text.splitlines())
    # Multiple inline definitions may share a source line; group that line once.
    merged = []
    for start, end, kind, signature, scope in sorted(found):
        start = max(start, 1); end = min(end, total)
        if merged and start <= merged[-1][1]:
            old = merged.pop()
            merged.append((old[0], max(end, old[1]), 'inline-cluster', old[3] + ' / ' + signature, scope or old[4]))
        else: merged.append((start, end, kind, signature, scope))
    lines = text.splitlines(); complete = []; cursor = 1
    def gap(start, end):
        while start <= end:
            stop = min(end, start + 35)
            # Prefer a blank boundary; avoid giant unrelated declaration groups.
            blanks = [n for n in range(start + 5, stop + 1) if not lines[n - 1].strip()]
            if stop != end and blanks: stop = blanks[-1]
            code = [s.strip() for s in lines[start - 1:stop] if s.strip()]
            title = short(' '.join(code[:2])) if code else 'Spacing between adjacent source blocks'
            complete.append((start, stop, 'declarations-or-scaffolding', title, ''))
            start = stop + 1
    for item in merged:
        if item[0] > cursor: gap(cursor, item[0] - 1)
        complete.append(item); cursor = item[1] + 1
    if cursor <= total: gap(cursor, total)
    return complete, parser

def local_facts(path, text):
    suffix = Path(path).suffix
    if suffix in CPP:
        code, tokens, comments, literals = lex_cpp(text)
    else:
        code, tokens, comments, literals = text, [], [], re.findall(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', text)
        if suffix == '.py':
            starts=[0]
            for match in re.finditer('\n',text):starts.append(match.end())
            try:
                for token in tokenize.generate_tokens(io.StringIO(text).readline):
                    if token.type==tokenize.COMMENT:
                        offset=starts[token.start[0]-1]+token.start[1]
                        comments.append((offset,offset+len(token.string),token.string))
            except (tokenize.TokenError,IndentationError):
                pass  # A declaration-region fragment need not be a complete module.
        elif suffix in ('.cmake','.sh') or path.endswith(('.cmake.in','CMakeLists.txt')):
            comments=[(m.start(),m.end(),m.group()) for m in re.finditer(r'^\s*#[^\n]*',text,re.M)]
    calls = []
    ignore = {'if','for','while','switch','catch','return','sizeof','alignof','decltype','noexcept','requires','static_cast','const_cast','reinterpret_cast','dynamic_cast'}
    for name in re.findall(r'([A-Za-z_~]\w*(?:::[A-Za-z_~]\w*)*)\s*\(', code):
        if name not in ignore and name not in calls: calls.append(name)
    checks = []
    for line in text.splitlines():
        if re.search(r'\b(?:require|assert|static_assert|check|bounded|raise|EXPECT_\w+|ASSERT_\w+)\s*\(', line):
            checks.append(short(line, 220))
    throws = [short(m.group(), 150) for m in re.finditer(r'\b(?:throw|raise)\b[^;\n]*', code)]
    catches = [short(m.group(), 100) for m in re.finditer(r'\bcatch\s*\([^)]*\)|\bexcept\b[^:\n]*', code)]
    growth = sorted(set(re.findall(r'\b(?:allocate|allocate_raw|allocate_shared|make_accounted_unique|make_accounted_shared|make_unique|make_shared|reserve|resize|push_back|emplace|emplace_back|insert|clone|copy_of|malloc|new)\b', code)))
    # Keep all detected regex facts in JSON; neither JSON nor display proves full semantics.
    returns = [short(m.group(1), 180) for m in re.finditer(r'\breturn\s+([^;\n]+)', code)]
    return dict(calls=calls, guards=checks, throws=throws, catches=catches,
                growth_sites=growth, loops=len(re.findall(r'\b(?:for|while|do)\b', code)),
                returns=returns, comments=[{'offset_line':text.count('\n',0,a)+1,'text':c}
                                          for a,_,c in comments])

def structural_role(path, kind, body, signature):
    if kind == 'callable': return 'Callable definition: ' + short(signature, 130)
    if kind == 'inline-cluster': return 'Definitions sharing source lines: ' + short(signature, 130)
    if kind == 'type': return 'Type/record definition: ' + short(signature, 130)
    if kind == 'build-command': return 'CMake command: ' + short(signature, 130)
    masked = lex_cpp(body)[0] if Path(path).suffix in CPP else body
    stripped = masked.strip()
    if not stripped: return 'Explanatory comments or spacing.'
    roles=[]
    if '#include' in stripped or re.search(r'^\s*(?:from .+ import|import )',stripped,re.M): roles.append('Imports dependencies')
    if '#pragma once' in stripped: roles.append('guards repeated header inclusion')
    if re.search(r'^\s*#(?:if|else|endif|define)',stripped,re.M): roles.append('controls preprocessing')
    if re.fullmatch(r'[\s};]+',stripped): return 'Closes surrounding scope/type.'
    if 'namespace' in stripped: roles.append('declares namespace scope')
    if re.search(r'\b(?:using|typedef)\b',stripped): roles.append('declares aliases')
    if re.search(r'\b(?:class|struct|enum)\b',stripped): roles.append('declares types or opens a type body')
    if re.search(r'\([^{}]*\)[^{};]*;',stripped): roles.append('declares callable signatures')
    if re.search(r'\b(?:constexpr|const|static_assert)\b|=',stripped): roles.append('declares values/defaults or compile-time conditions')
    if not roles:
        roles.append('Module statements' if path.endswith(('.py','.sh')) else 'Member/declaration region')
    return '; '.join(roles) + '.'

def load_overrides():
    result = []
    for name in ('reviewed_contracts.json',):
        path = BASE / name
        if path.exists():
            items = json.loads(path.read_text())
            if isinstance(items, dict): items = items.get('blocks', items.get('contracts', []))
            result.extend(items)
    return result

def source_inventory():
    suffixes={'.cpp','.cc','.c','.hpp','.h','.inc','.py','.sh','.cmake'}
    result=[ROOT/'CMakeLists.txt']
    for scope in ('include','src','apps','tools','examples','cmake','tests'):
        result.extend(p for p in (ROOT/scope).rglob('*') if p.is_file() and (p.suffix in suffixes or p.name=='CMakeLists.txt' or p.name.endswith('.cmake.in')))
    # Admit only these maintained Scala helpers; legacy Scala trees remain excluded.
    for replay in (ROOT/'tools/support/CrownReplay.scala', ROOT/'tools/support/ComponentReplay.scala'):
        if replay.is_file(): result.append(replay)
    return sorted(result)


def main():
    # Documentation writes are sequential; regenerate before checking saved review flags.
    DOCS.mkdir(parents=True, exist_ok=True)
    entries, comments, totals = [], [], Counter()
    overrides = load_overrides(); unused = set(range(len(overrides)))
    for source in source_inventory():
        if not source.is_file(): continue
        path = str(source.relative_to(SNAPSHOT)); original = source.read_bytes().decode('utf-8')
        source_hash = digest(original)
        staged = OVERLAY / path
        text = original
        group = family(path); inherited = dict(CONTRACTS[group])
        inherited['references'] = [p for p in inherited['references'] if (ROOT / p).exists()]
        spans, parser = regions(path, text)
        locations = {oi: contract_line(text, override['anchor']) for oi, override in enumerate(overrides)
                     if override.get('path') == path}
        lines = text.splitlines(); blocks = []
        for number, span in enumerate(spans, 1):
            start, end, kind, signature, scope = span
            body = '\n'.join(lines[start - 1:end])
            item = dict(id=f'B{number:04}', start_line=start, end_line=end, kind=kind,
                        signature=signature, role=structural_role(path,kind,body,signature),
                        evidence=local_facts(path,body), contracts=[], review_level='structural_only')
            # Preserve adjacent source documentation as evidence, not a new
            # semantic certification. Multiline comments inside a mapped range
            # are retained in evidence.comments with their exact source text.
            nearby=[];j=start-2
            while j>=0 and len(nearby)<12 and lines[j].lstrip().startswith('//'):
                nearby.append({'line':j+1,'text':lines[j]});j-=1
            item['nearby_comments']=list(reversed(nearby))
            for oi, location in locations.items():
                override = overrides[oi]
                if location is not None and start <= location <= end:
                    item['contracts'].append({k:override[k] for k in ('anchor',)+FIELDS if k in override})
                    stale = override.get('reviewed_source_sha256') != source_hash
                    item['manual_review_stale'] = item.get('manual_review_stale', False) or stale
                    item['review_level'] = 'manual_recheck_required' if item['manual_review_stale'] else 'contains_scoped_manual_contract'
                    unused.discard(oi)
            blocks.append(item)
        if Path(path).suffix in CPP:
            _, _, found_comments, _ = lex_cpp(text)
            for start, end, content in found_comments:
                start_line = text.count('\n', 0, start) + 1
                suspicious = bool(re.search(r'\b(?:draft|migration|future|TODO|FIXME|in progress|being ported|temporary|not yet|excluded)\b', content, re.I))
                comments.append(dict(path=path, start_line=start_line, end_line=text.count('\n',0,end)+1,
                    text=content, temporal_marker=suspicious,
                    disposition='inventory_only; not individually certified'))
        entry = dict(source_path=path, before_sha256=source_hash, staged_sha256=source_hash,
                     line_count=len(lines), subsystem=group, source_changed=False,
                     parser=parser, file_role=ROLES.get(path, ROLES.get(Path(path).stem, inherited['purpose'])),
                     contract_ref=group, blocks=blocks)
        entries.append(entry); totals['files'] += 1; totals['lines'] += len(lines)
        totals['blocks'] += len(blocks); totals['manual_blocks'] += sum(bool(b['contracts']) for b in blocks)
        totals['manual_contracts'] += sum(len(b['contracts']) for b in blocks)
        page = DOCS / 'files' / (path + '.md'); page.parent.mkdir(parents=True, exist_ok=True)
        rows = [f'# `{path}` — block usage map', '',
                f'{link(path, page, "Source")} · {link("docs/code_specs/README.md",page,"Source index")} · {link("docs/code_specs/subsystem_contracts.md",page,"Subsystem contracts")} · {link("docs/code_specs/primitives.md",page,"Reviewed primitives")}', '',
                entry['file_role'], '',
                f'Snapshot SHA-256: `{entry["staged_sha256"]}`. {len(lines)} lines partitioned into {len(blocks)} blocks using `{parser["kind"]}`. Line ranges apply to these bytes; regenerate after a source edit.', '',
                f'Module context: {link("docs/code_specs/subsystem_contracts.md#" + group,page,group)}. This context is not assigned as an invariant to imports, declarations or scope closures. Design: ' + ', '.join(link(p,page) for p in inherited['references']) + '.', '',
                'The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.', '',
                '| Block / lines | Observed role / declaration | Local body evidence |', '| --- | --- | --- |']
        for b in blocks:
            facts=b['evidence']; evidence=[]
            if facts['calls'] and b['kind'] in ('callable','inline-cluster'):
                evidence.append('calls '+', '.join(facts['calls'][1:5]))
            if facts['guards']:evidence.append('guard '+short(facts['guards'][0],100))
            if facts['returns']:evidence.append('returns '+short('; '.join(facts['returns'][:2]),100))
            if facts['growth_sites']:evidence.append('growth '+', '.join(facts['growth_sites'][:6]))
            if facts['loops']:evidence.append(str(facts['loops'])+' loop sites')
            comment=(b['nearby_comments'][0]['text'] if b['nearby_comments'] else facts['comments'][0]['text'] if facts['comments'] else '')
            if comment:evidence.append('source comment (unverified): '+short(comment,120))
            extra=' · [reviewed contract](#'+b['id'].lower()+')' if b['contracts'] else ''
            where=link(path+'#L'+str(b['start_line']),page,b['id']+' · '+str(b['start_line'])+'–'+str(b['end_line']))
            rows.append(f'| {where} | {md(b["role"])} | {md("; ".join(evidence))}{extra} |')
        for b in blocks:
            if not b['contracts']: continue
            rows += ['', f'## {b["id"]}', '',
                     f'{link(path + "#L" + str(b["start_line"]),page,"Lines " + str(b["start_line"]) + "–" + str(b["end_line"]))}; `{b["kind"]}`; `{b["review_level"]}`.', '',
                     'The contract is scoped to its anchor, not a proof of every declaration sharing this line range.']
            for contract in b['contracts']:
                rows += ['', '```text',contract['anchor'],'```','', '| Field | Reviewed usage contract |', '| --- | --- |']
                for field in FIELDS[:-1]: rows.append(f'| {field.replace("_"," / ")} | {md(contract[field])} |')
                rows.append('| Design | ' + ', '.join(reference(p,page) for p in contract['references']) + ' |')
        page.write_text('\n'.join(rows) + '\n')
    exclusions = [dict(path=p, reason='Active W02 source and contract belong to root; integrate root-authored blocks after the rewrite.')
                  for p in ('include/crown/runtime/weighted.hpp','src/runtime/weighted.cpp') if not (SNAPSHOT / p).exists()]
    exclusions.append(dict(path='data/fixtures/schemas/vendor/baseline/build outputs',reason='JSON/SQL/hex fixtures, third_party and preserved Scala/external baselines are data or excluded historical/vendor sources; this maintained-code map does not certify them.'))
    payload = dict(schema_version=1, scope='maintained native sources, scripts, examples, CMake and tests',
                   coverage_meaning='every saved source line belongs to one block; semantic review only where explicitly marked',
                   totals=dict(totals), exclusions=exclusions, unused_manual_overrides=[overrides[i] for i in sorted(unused)], files=entries)
    (DOCS / 'coverage.json').write_text(json.dumps(payload, separators=(',',':')) + '\n')
    # Comment audit evidence is maintained separately from generated source maps.
    page = DOCS / 'subsystem_contracts.md'
    rows = ['# Subsystem usage contracts','', 'These contracts describe module boundaries and intended use. Source maps link this context separately; they do not assign it to every declaration or prove all branches or paper bounds. A block-specific reviewed contract has its own explicit scope.', '']
    for name, contract in CONTRACTS.items():
        rows += [f'## {name}', '', '| Field | Contract |', '| --- | --- |']
        for field in FIELDS[:-1]: rows.append(f'| {field.replace("_"," / ")} | {md(contract[field])} |')
        refs = [p for p in contract['references'] if (ROOT / p).exists()]
        rows += ['| Design | ' + ', '.join(link(p,page) for p in refs) + ' |', '']
    page.write_text('\n'.join(rows))
    page = DOCS / 'README.md'
    rows = ['# Human inspection and block usage specifications', '',
        'Start with the concrete lifecycle and hot primitives in [primitives.md](primitives.md), then follow a source file below. The [subsystem contracts](subsystem_contracts.md) define the common input/output, invariant, ownership, failure and cost boundary; source pages attach exact block ranges and local evidence.', '',
        f'This snapshot maps **{totals["files"]} files, {totals["lines"]:,} lines and {totals["blocks"]:,} blocks**. **{totals["manual_contracts"]} scoped semantic contracts** appear within {totals["manual_blocks"]} blocks. Other blocks provide structural facts only, with module context linked separately. They are not individually written usage specifications or a complete semantic review. The compact machine-readable inventory is [coverage.json](coverage.json).', '',
        'A mapped line is inspectable, not proven correct. C++ segmentation is lexical and includes declaration/scaffolding regions; Python uses the standard AST; CMake uses command boundaries. Return/call/guard/allocation lists are syntax evidence. They omit indirect/transitive effects and cannot establish no-allocation or asymptotic bounds. Existing comments are inventoried, with focused corrections recorded in the verification artifact; retained comments are not blanket-certified.', '',
        'The documentation tools add no runtime checks, instrumentation, framework or dependencies. Comment-only corrections preserve executable tokens; separately recorded diagnostic wording changes alter string literals. A direct enum-to-diagnostic conversion removes one redundant throw/catch; see [error-handling dispositions](error_handling.md). Source hashes make stale maps and reviewed-source changes visible.', '',
        'Paper provenance uses [the corrected source map](../code_review.md): P1 is arXiv:2301.04003v2, 20 pages; P2 is arXiv:2603.14754v1. Support/enumeration context does not prove native allocator, rollback, SQL, durability or every public delay bound. Most primitives are local engineering contracts.', '',
        '## Coverage boundaries', '',
        'The W02/W03 weighted files include scoped semantic contracts and source hashes; regenerate after source changes and recheck affected contracts. JSON/SQL/hex fixtures, schemas, preserved historical Scala/external baselines, vendored dependencies and generated build output are not maintained code in this map. Code under tests is included; listing a test does not say it was executed.', '',
        '## Source index', '', '| Source | Lines | Blocks | Subsystem | Reviewed blocks |', '| --- | ---: | ---: | --- | ---: |']
    where=rows.index('## Source index')
    rows[where:where]=['## Inspection workflow','',
        '1. Check the source hash and run `python3 tools/check_code_specs.py` to detect stale maps.',
        '2. Follow a reviewed primitive card where available; read its owner and callers before applying that contract elsewhere.',
        '3. Use the structural table to locate exact declarations, calls, guards, returns, growth and nearby comment evidence. Retained source comments are not automatically certified.',
        '4. Consult [error-handling dispositions](error_handling.md) before removing a catch, lock, inverse record or allocator boundary.',
        '5. After edits, recheck affected semantic cards, run `python3 tools/generate_code_specs.py`, then the checker. Change reviewed-source hashes only after that review.','']
    for item in entries:
        target='files/'+item['source_path']+'.md'
        rows.append(f'| [{item["source_path"]}]({target}) | {item["line_count"]} | {len(item["blocks"])} | {item["subsystem"]} | {sum(bool(b["contracts"]) for b in item["blocks"])} |')
    rows += ['', '## Reproduction', '',
             'Run `python3 tools/generate_code_specs.py`, then `python3 tools/check_code_specs.py` from the repository. Generation reads maintained sources and writes only docs/code_specs. The checker verifies complete source coverage, current hashes, local source links and Markdown fragments. Reviewed contracts live in reviewed_contracts.json with reviewed_source_sha256; a source change marks its manual review stale until a reviewer checks the anchor/behavior and updates that hash. Do not update review hashes merely to silence the checker. tools/code_specs_support.py stores shared context and file-role mapping. Historical comment/token evidence remains in the dated verification packet.', '']
    page.write_text('\n'.join(rows))
    primitive=DOCS/'primitives.md'
    prefix=primitive.read_text().split('## Reviewed source cards',1)[0] if primitive.exists() else '# Reviewed primitives\n\nFull contracts are scoped to the anchors below.\n\n'
    cards=['## Reviewed source cards','',
           'Each source page keeps every scoped anchor, seven-field usage/cost contract and reference. '
           'This compact index avoids duplicating those contracts; a listed source is not automatically fully reviewed.', '',
           '| Source | Scoped contracts | Usage context |','| --- | ---: | --- |']
    for entry in entries:
        count=sum(len(block['contracts']) for block in entry['blocks'])
        if not count: continue
        target='files/'+entry['source_path']+'.md'
        cards.append('| ['+md(entry['source_path'])+']('+target+') | '+str(count)+' | '+md(entry['file_role'])+' |')
    primitive.write_text(prefix+'\n'.join(cards)+'\n\nSee [error-handling dispositions](error_handling.md) and the [source index](README.md).\n')
    print(json.dumps(dict(totals), sort_keys=True))
    if unused: print('Unused manual anchors:', len(unused))

if __name__ == '__main__': main()
