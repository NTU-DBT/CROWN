#!/usr/bin/env python3
"""O07 source/seal metadata audit; never executes builds, tests, or historical checksums.
Only --output JSON and sibling log are written. The seal is always read-only.
--final requires every final gate; default keeps unfinished gates pending.
"""
from __future__ import annotations
import argparse, collections, hashlib, json, re
from pathlib import Path
from urllib.parse import unquote,urlsplit
ROOT=Path('/home/userroot/Codex/CROWN')
VERIFY=ROOT/'build/verification'
OLD_SEAL='docs/verification/candidate-alternatives-sources.sha256'
NEW_SEAL='docs/verification/observability-sources.sha256'
REFACTOR_SHA='bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce'
NATIVE={'count':585,'sha256':'9ca9005001bda9e56faa0951077e53fc106450d7350bf185cd62556a7af25d0a'}
EXECUTION={'count':635,'sha256':'8ae45108daed5530d67372c93b46bb198bf694a5c8bf429cb6905d4b367bbf12'}
SCHEMAS=['explain-report-v2.schema.json','explain-tree-v2.schema.json','query-explain-v1.schema.json','query-witness-v1.schema.json']
CONFIGS=['debug','release','sanitize','clang','clean-source']
ERRORS=[];PENDING=[]
def need(ok,message):
 if not ok:ERRORS.append(message)
def pending(message,final):
 if final:ERRORS.append(message)
 else:PENDING.append(message)
def pin(path):return {'path':str(path),'sha256':file_sha(path)}
ROOT_FILES = [".gitignore", "CMakeLists.txt", "CMakePresets.json", "README.md", "Refactor.md", "dependencies.lock.json"]

INVENTORY_ROOTS = ["include", "src", "apps", "tests", "cmake", "docs", "schemas", "third_party", "tools"]

def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()

def file_sha(path: Path):
    return sha(path.read_bytes()) if path.is_file() else None

def read(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="replace")

def ordinary_inventory(root: Path):
    paths = set()
    for rel in ROOT_FILES:
        if (root / rel).is_file(): paths.add(rel)
    for rel_root in INVENTORY_ROOTS:
        base = root / rel_root
        if not base.is_dir(): continue
        for path in base.rglob("*"):
            if not path.is_file(): continue
            rel = path.relative_to(root).as_posix()
            if rel.startswith("docs/verification/") or rel in {"docs/handoff.md", "docs/task_ledger.md"}: continue
            if "__pycache__" in path.parts or path.suffix in {".pyc", ".pyo"}: continue
            paths.add(rel)
    return sorted(paths)

def inventory_under(root: Path, roots, extras=()):
    paths = set(extras)
    for rel_root in roots:
        base = root / rel_root
        if not base.is_dir(): continue
        for path in base.rglob("*"):
            if path.is_file() and "__pycache__" not in path.parts and path.suffix not in {".pyc", ".pyo"}:
                paths.add(path.relative_to(root).as_posix())
    return sorted(paths)

def pathset_digest(root: Path, paths):
    h = hashlib.sha256()
    for rel in sorted(paths):
        h.update(rel.encode("utf-8")); h.update(b"\0")
        h.update((root / rel).read_bytes()); h.update(b"\0")
    return h.hexdigest()

def parse_manifest_paths(path: Path):
    entries, errors = [], []
    if not path.is_file(): return entries, ["manifest missing"]
    for no, line in enumerate(read(path).splitlines(), 1):
        m = re.fullmatch(r"([0-9a-fA-F]{64})  (.+)", line)
        if not m:
            errors.append(f"line {no}: invalid sha256sum row")
            continue
        digest, rel = m.groups()
        if rel.startswith("./") or "\\" in rel: errors.append(f"line {no}: noncanonical path {rel!r}")
        entries.append((rel, digest.lower()))
    return entries, errors

def strip_fences(lines):
    visible, blocks, in_block, marker, size = [], 0, False, None, 0
    for no, line in enumerate(lines, 1):
        m = re.match(r"^\s{0,3}(`{3,}|~{3,})", line)
        if not in_block and m:
            in_block, marker, size = True, m.group(1)[0], len(m.group(1)); blocks += 1; continue
        if in_block:
            if m and m.group(1)[0] == marker and len(m.group(1)) >= size: in_block, marker, size = False, None, 0
            continue
        visible.append((no, line))
    return visible, blocks

def strip_inline_code(line):
    return re.sub(r"(?<!`)`+[^`]*?`+(?!`)", " ", line)

def norm_label(s): return re.sub(r"\s+", " ", s.strip()).lower()

def local_destination(root: Path, source_rel: str, raw):
    raw = raw.strip()
    if raw.startswith("<") and raw.endswith(">") : raw = raw[1:-1].strip()
    if not raw: return {"kind": "empty", "raw": raw, "exists": True}
    if raw.startswith("\\"): raw = raw[1:]
    parsed = urlsplit(raw)
    if parsed.scheme or parsed.netloc: return {"kind": "remote_or_scheme", "raw": raw, "exists": True}
    p = unquote(parsed.path)
    if not p: return {"kind": "anchor_or_query", "raw": raw, "exists": True}
    target = Path(p) if p.startswith(str(root.resolve())+"/") else (root / p.lstrip("/") if p.startswith("/") else (root / source_rel).parent / p)
    target = target.resolve(strict=False)
    try: rel = target.relative_to(root.resolve()).as_posix(); inside = True
    except ValueError: rel, inside = str(target), False
    return {"kind": "local", "raw": raw, "resolved": rel, "inside_root": inside, "exists": inside and target.exists()}

DIRECT_LINK = re.compile(r"!?\[[^\]]*\]\s*\(\s*(<[^>]+>|(?:\\.|[^)\s])+)(?:\s+[^)]*)?\)")

REF_DEF = re.compile(r"^\s{0,3}\[([^\]]+)\]:\s*(?:<([^>]+)>|(\S+))")

REF_USE = re.compile(r"(?<!!)\[([^\]]+)\](?:\s*\[([^\]]*)\])?")

def markdown_paths(root: Path, inventory):
    docs = {p for p in inventory if Path(p).suffix.lower() in {".md", ".markdown"}}
    extras = {"handoff_ledger": [], "verification": []}
    for rel in ("docs/handoff.md", "docs/task_ledger.md"):
        if (root / rel).is_file(): docs.add(rel); extras["handoff_ledger"].append(rel)
    ver = root / "docs/verification"
    if ver.is_dir():
        for p in ver.rglob("*"):
            if p.is_file() and p.suffix.lower() in {".md", ".markdown"}:
                rel = p.relative_to(root).as_posix(); docs.add(rel); extras["verification"].append(rel)
    return sorted(docs), extras

def audit_markdown(root: Path, inventory):
    docs, groups = markdown_paths(root, inventory)
    links, missing_docs = [], []
    counts = {"fenced_blocks_skipped": 0, "inline_links": 0, "reference_definitions": 0, "reference_uses": 0, "inline_code_lines_removed": 0}
    for source in docs:
        p = root / source
        if not p.is_file(): missing_docs.append(source); continue
        visible, skipped = strip_fences(read(p).splitlines()); counts["fenced_blocks_skipped"] += skipped
        defs, body = {}, []
        for no, line in visible:
            m = REF_DEF.match(line)
            if m:
                label, angled, plain = m.groups(); dest = angled if angled is not None else plain
                key = norm_label(label); defs[key] = (dest, no); counts["reference_definitions"] += 1; continue
            stripped = strip_inline_code(line)
            if stripped != line: counts["inline_code_lines_removed"] += 1
            body.append((no, stripped))
        for no, line in body:
            occupied = []
            for m in DIRECT_LINK.finditer(line):
                counts["inline_links"] += 1; occupied.append((m.start(), m.end()))
                item = local_destination(root, source, m.group(1)); item.update({"source": source, "line": no, "syntax": "inline"}); links.append(item)
            for m in REF_USE.finditer(line):
                if any(a <= m.start() < b for a, b in occupied): continue
                if line[m.end():].lstrip().startswith("("): continue
                label, explicit = m.groups(); key = norm_label(explicit if explicit else label)
                if key not in defs: continue
                counts["reference_uses"] += 1; dest, def_line = defs[key]
                item = local_destination(root, source, dest); item.update({"source": source, "line": no, "definition_line": def_line, "syntax": "reference"}); links.append(item)
        for label, (dest, def_line) in defs.items():
            item = local_destination(root, source, dest); item.update({"source": source, "line": def_line, "syntax": "reference_definition", "label": label}); links.append(item)
    broken = [x for x in links if x["kind"] == "local" and not x["exists"]]
    local = [x for x in links if x["kind"] == "local"]
    return {
        "scope": "all ordinary sealed Markdown, docs/handoff.md, docs/task_ledger.md, and every docs/verification Markdown file; fenced/inline code excluded from link parsing",
        "documents_scanned": len(docs) - len(missing_docs), "documents_missing": missing_docs,
        "ordinary_sealed_markdown_count": sum(Path(p).suffix.lower() in {".md", ".markdown"} for p in inventory),
        "handoff_ledger_markdown_count": len(groups["handoff_ledger"]),
        "verification_markdown_count": len(groups["verification"]), "verification_paths": sorted(groups["verification"]),
        **counts, "local_destination_occurrences": len(local),
        "unique_resolved_local_paths": len({x.get("resolved") for x in local if x["exists"]}),
        "external_or_scheme_destinations": sum(x["kind"] == "remote_or_scheme" for x in links),
        "anchor_or_query_destinations": sum(x["kind"] == "anchor_or_query" for x in links),
        "broken_local_destinations": broken,
    }

def audit_schema_refs(root: Path, docs):
    pat = re.compile(r"(?:[A-Za-z0-9_.-]+/)*[A-Za-z0-9_.-]+\.schema\.json")
    refs, missing = [], []
    for rel in docs:
        p = root / rel
        if not p.is_file(): continue
        visible, _ = strip_fences(read(p).splitlines())
        for no, line in visible:
            for m in pat.finditer(line):
                raw = m.group(0)
                if "/" in raw: candidates = [(p.parent / raw), (root / raw)]
                else: candidates = [(p.parent / raw), (p.parent / "schemas" / raw), (root / raw), (root / "schemas" / raw)]
                resolved = None
                for c in candidates:
                    c = c.resolve(strict=False)
                    if c.is_file():
                        try: resolved = c.relative_to(root.resolve()).as_posix()
                        except ValueError: resolved = None
                        if resolved: break
                item = {"source": rel, "line": no, "raw": raw, "resolved": resolved}; refs.append(item)
                if not resolved: missing.append(item)
    return {"occurrences": len(refs), "unique_raw_references": sorted({x["raw"] for x in refs}), "missing": missing,
            "all_exist": not missing, "basename_resolution_order": ["document_parent", "document_local_schemas", "repository_root", "schemas_root"]}

def task_rows(path: Path, ledger=False):
    if not path.is_file(): return []
    out = []
    if ledger:
        pat = re.compile(r"^\|\s*([A-Z][0-9]{2})\s+[^|]*\|\s*(not_started|in_progress|implemented|verified|blocked)\s*\|", re.I)
        for no, line in enumerate(read(path).splitlines(), 1):
            m = pat.match(line)
            if m: out.append({"id": m.group(1), "status": m.group(2).lower(), "line": no})
    else:
        lines = read(path).splitlines()
        start = next((i for i, line in enumerate(lines) if re.match(r"^11\.\s+Detailed coding-agent work breakdown", line)), None)
        end = next((i for i, line in enumerate(lines) if i > (start if start is not None else -1) and re.match(r"^11\.13\s+Dependency and parallel-work summary", line)), len(lines))
        section = lines[(start + 1 if start is not None else 0):end]
        pat = re.compile(r"^([A-Z][0-9]{2})\s+[—-]")
        for offset, line in enumerate(section, start + 2 if start is not None else 1):
            m = pat.match(line.strip())
            if m: out.append({"id": m.group(1), "line": offset})
    return out

def frozen():
 p=VERIFY/'observability-execution-freeze.json';f=json.loads(read(p));need(f.get('card')=='O07','wrong freeze card');out={'freeze':pin(p)}
 for kind,dirs,extras,want in [('native',['include','src','apps','tests','cmake'],['CMakeLists.txt','CMakePresets.json'],NATIVE),('execution',['include','src','apps','tests','cmake','schemas','tools','third_party'],['CMakeLists.txt','CMakePresets.json','dependencies.lock.json'],EXECUTION)]:
  paths=inventory_under(ROOT,dirs,extras);actual={'count':len(paths),'sha256':pathset_digest(ROOT,paths)};fm={r:file_sha(ROOT/r) for r in paths}
  need(actual==want==f.get(kind),kind+': aggregate freeze drift');need(fm==f.get(kind+'_file_sha256'),kind+': per-file freeze drift');out[kind]=actual
 for label,r in f['historical_manifest_file_hashes'].items():need(file_sha(ROOT/r['path'])==r['sha256'],label+': historical manifest FILE changed')
 need(len(f['historical_manifest_file_hashes'])==9,'historical manifest FILE inventory not9');need(file_sha(ROOT/'Refactor.md')==REFACTOR_SHA,'original Refactor.md changed')
 out['historical_manifest_files']=f['historical_manifest_file_hashes'];out['original_Refactor_sha256']=REFACTOR_SHA
 return out,f

def inventory_and_seal(final):
 ordinary=ordinary_inventory(ROOT);entries,errors=parse_manifest_paths(ROOT/OLD_SEAL);old=[p for p,_ in entries]
 need(not errors and len(old)==592 and len(set(old))==592,'historical P07 PATH inventory malformed')
 added=sorted(set(ordinary)-set(old));removed=sorted(set(old)-set(ordinary))
 need(len(ordinary)==691 and len(added)==99 and not removed,'ordinary inventory not592+99 with no removals')
 out={'ordinary_count':len(ordinary),'old_manifest_path_count':len(old),'added':added,'removed':removed,'old_entries_policy':'Only paths read. No old entry checksum is evaluated against current files.'}
 seal=ROOT/NEW_SEAL
 if not seal.is_file():pending('new ordinary source seal not produced',final);out['seal']={'status':'pending','path':NEW_SEAL}
 else:
  now,malformed=parse_manifest_paths(seal);names=[p for p,_ in now];need(not malformed and names==ordinary and len(set(names))==len(names),'new seal must exactly equal sorted unique691 ordinary inventory')
  wrong=[p for p,h in now if p.startswith('/') or '..' in Path(p).parts or file_sha(ROOT/p)!=h];need(not wrong,'new seal current checksums mismatch: '+str(wrong))
  out['seal']={'status':'audited_pass' if not malformed and names==ordinary and not wrong else 'audit_error','identity':pin(seal),'mismatches':wrong}
 return ordinary,out

def schema_references():
 documents={p.resolve():json.loads(read(p)) for p in (ROOT/'schemas').glob('*.schema.json')};ids={v['$id']:p for p,v in documents.items() if '$id' in v};refs=[];remote=[]
 def walk(v):
  if isinstance(v,dict):
   yield v
   for x in v.values():yield from walk(x)
  elif isinstance(v,list):
   for x in v:yield from walk(x)
 for source,document in documents.items():
  for item in walk(document):
   for key in ('$ref','$dynamicRef'):
    if key not in item:continue
    ref=item[key];u=urlsplit(ref)
    if u.scheme and ref.split('#',1)[0] not in ids:remote.append({'source':str(source),'ref':ref});continue
    target=ids.get(ref.split('#',1)[0]) if u.scheme else (source.parent/unquote(u.path)).resolve() if u.path else source
    ok=target in documents;node=documents.get(target);fragment=unquote(u.fragment)
    if ok and fragment.startswith('/'):
     try:
      for token in fragment[1:].split('/'):
       token=token.replace('~1','/').replace('~0','~');node=node[int(token)] if isinstance(node,list) else node[token]
     except (KeyError,IndexError,ValueError,TypeError):ok=False
    elif ok and fragment:ok=any(n.get('$anchor')==fragment or n.get('$dynamicAnchor')==fragment for n in walk(node))
    refs.append({'source':str(source.relative_to(ROOT)),'ref':ref,'exists':ok});need(ok,'local schema ref missing: '+str(source.relative_to(ROOT))+' '+ref)
 for name in SCHEMAS:
  d=documents[(ROOT/'schemas'/name).resolve()];branches=d.get('oneOf',[d])
  for branch in branches:
   if '$ref' in branch:
    target=d
    for k in branch['$ref'].removeprefix('#/').split('/'):target=target[k]
    branch=target
   need(branch.get('additionalProperties') is False,name+': top-level alternative not closed')
 return {'documents':len(documents),'references':refs,'external_refs_not_fetched':remote,'new_closed_schemas':SCHEMAS}

def integration(freeze):
 cm=read(ROOT/'CMakeLists.txt');graph={}
 need('docs/verification/' not in cm and '/tmp/crown' not in cm,'native CMake requires excluded preparatory paths')
 for body in re.findall(r'\btarget_link_libraries\s*\(([^)]*)\)',cm,re.S):
  words=body.split();graph.setdefault(words[0],set()).update(w for w in words[1:] if w.startswith('crown_'))
 cycles=[]
 def visit(n,trail):
  if n in trail:cycles.append(trail+[n]);return
  for dest in graph.get(n,set()):visit(dest,trail+[n])
 for n in graph:visit(n,[])
 need(not cycles,'CMake crown target cycle: '+str(cycles))
 anchors=['add_library(crown_query_explain src/observability/query_explain.cpp src/io/query_explain.cpp)','target_link_libraries(crown_query_explain PUBLIC crown_core PRIVATE crown_options)','add_library(crown_runtime ${CROWN_RUNTIME_SOURCES})','add_library(crown_runtime_testing STATIC ${CROWN_RUNTIME_SOURCES})','target_compile_definitions(crown_runtime_testing PUBLIC CROWN_RUNTIME_TESTING)','add_library(crown_explain ${CROWN_EXPLAIN_SOURCES})','add_library(crown_explain_testing STATIC ${CROWN_EXPLAIN_SOURCES})','apps/crown/explain.cpp','tools/verify_observability_reports.py','tests/observability/cli/native_cli_acceptance.py']
 for a in anchors:need(a in cm,'native CMake anchor absent: '+a)
 for variable,count in [('CROWN_RUNTIME_SOURCES',9),('CROWN_EXPLAIN_SOURCES',4)]:
  match=re.search(r'set\('+variable+r'\s+([^)]*)\)',cm,re.S);files=match[1].split() if match else [];need(len(files)==count and all((ROOT/f).is_file() for f in files),'wrong complete source set '+variable)
 names=re.findall(r'\badd_test\s*\(\s*NAME\s+([^\s)]+)',cm);need(names==freeze['expected_test_names'] and len(set(names))==99,'native registrations differ from99-name freeze')
 public={'include/crown/observability/explain.hpp':['class ModeDescriptor','class PlanExplanation','planner::VerifiedOptimum','planner::MinimumHeightCandidate','std::shared_ptr<const Data>','trace_records()'], 'include/crown/observability/query_explain.hpp':['class QueryExplanation','planner::ExactSearch','planner::CertificateReplay','planner::CheckedCertificate','std::shared_ptr<const Data>'], 'include/crown/runtime/observation.hpp':['ObservationMode::timed','class ObservationConfiguration','struct ObservationSummary','struct ObservationSnapshot','current_configuration','std::vector<TraceRecord> records']}
 for rel,markers in public.items():
  t=read(ROOT/rel)
  for marker in markers:need(marker in t,rel+': public API anchor absent '+marker)
 for p in (ROOT/'include/crown').rglob('*.hpp'):
  for target in re.findall(r'#\s*include\s+"(crown/[^\"]+)"',read(p)):need((ROOT/'include'/target).is_file(),'public include missing '+target)
 for p in (ROOT/'src/runtime').glob('*.cpp'):
  need(not re.search(r'#\s*include\s+"crown/(?:observability/|io/(?:explain|query_explain))',read(p)),'runtime has report-layer include dependency '+str(p))
 wrapper=read(ROOT/'tools/verify_observability_reports.py');query=read(ROOT/'tools/support/check_query_reports.py');cli=read(ROOT/'tests/observability/cli/native_cli_acceptance.py')
 need('Path(__file__).resolve().parents[2]' in query,'query checker does not use native repository schemas')
 need('"--repo-root", str(root), "--schema-dir", str(root / "schemas")' in wrapper,'composed checker fallback not overridden with native roots')
 need('--expected-crown-sha256' in cli and 'default=Path("/tmp/crown-native-explain-acceptance")' in cli,'CLI portable binary pin/output interface absent')
 for name in ['runtime_observation','observation_mode_binding','observation_run_context','cursor_observation','query_explain','composed_explain']:
  t=read(ROOT/f'tests/unit/{name}_test.cpp');need('docs/verification/' not in t and '/tmp/crown-o07' not in t,'native C++ test needs preparatory path '+name)
 for name in SCHEMAS:need(file_sha(ROOT/'schemas'/name)==file_sha(ROOT/'tests/observability/cli/schemas'/name),'portable CLI pinned schema differs '+name)
 return {'target_graph':{k:sorted(v) for k,v in graph.items()},'cycles':cycles,'registered_tests':names,'public_headers':list(public),'portability_note':'Native wrappers pass schemas/roots explicitly. Composed checker retains an unused preparatory default; /tmp CLI path is a fresh output destination, never an input dependency.'}

def matrix_prerequisite(final,freeze):
 p=VERIFY/'observability-matrix-evidence-audit.json'
 if not p.is_file():pending('final independent matrix audit absent',final);return {'status':'pending','path':str(p)}
 d=json.loads(read(p));accepted=d.get('accepted') is True and d.get('audit_state')=='accepted_final_matrix'
 if not accepted:
  need(not d.get('errors'),'independent matrix audit reports errors');pending('final independent matrix audit not accepted',final);return {'status':'pending','identity':pin(p)}
 need(not d.get('errors') and not d.get('pending'),'accepted matrix contains pending/errors')
 for item in [d.get('auditor',{}),d.get('freeze',{}).get('freeze',{})]:
  need(bool(item.get('sha256')) and file_sha(Path(item.get('path','/nonexistent')))==item.get('sha256'),'accepted matrix auditor/freeze identity changed')
 need(d.get('freeze',{}).get('native')==NATIVE and d.get('freeze',{}).get('execution')==EXECUTION,'matrix audited different freeze')
 for name in CONFIGS:
  r=d.get('matrix',{}).get(name,{});tests=r.get('tests',[]);need(r.get('status')=='audited_pass' and [t['name'] for t in tests]==freeze['expected_test_names'] and all(t['passed'] and not t['failed'] for t in tests),'matrix lacks exact successful99 records '+name)
  for key in ['summary','raw_verbose','raw_lasttest']:
   item=r.get(key,{});need(file_sha(Path(item.get('path','/nonexistent')))==item.get('sha256') and bool(item.get('sha256')),'matrix raw artifact changed/missing '+name+' '+key)
 need(d.get('structured_rows',{}).get('status')=='audited_pass' and d.get('compiler_parser_exports',{}).get('status')=='audited_pass','matrix compiler/export/rows scope incomplete')
 return {'status':'audited_pass','identity':pin(p),'all_five_exact99':True}

def ledger_and_claims(final,matrix,seal):
 rows=task_rows(ROOT/'docs/task_ledger.md',True);cards=task_rows(ROOT/'Refactor.md');ids=[r['id'] for r in rows];by={r['id']:r['status'] for r in rows};counts=dict(collections.Counter(by.values()));is_verified=by.get('O07')=='verified'
 need(len(rows)==len(set(ids))==78 and set(ids)=={r['id'] for r in cards},'ledger not original78 unique card set')
 expected={'verified':37,'in_progress':2,'not_started':39} if is_verified else {'verified':36,'in_progress':3,'not_started':39};need(counts==expected,'ledger phase counts mismatch');need(by.get('O07') in ['in_progress','verified'],'O07 invalid phase')
 need(sorted(k for k,v in by.items() if v=='in_progress')==(['A02','O06'] if is_verified else ['A02','O06','O07']),'unexpected in-progress card set')
 ledger=read(ROOT/'docs/task_ledger.md').lower();need('full 78-card scope remains active' in ledger and 'release gate disposition remains open' in ledger,'full78/release boundaries missing')
 if is_verified:need(matrix['status']=='audited_pass' and seal.get('status')=='audited_pass','O07 verified before matrix+new current seal pass')
 elif final:pending('O07 ledger remains in_progress',True)
 else:pending('final O07 verified ledger/document transition not yet made',False)
 packet=read(ROOT/'docs/verification/observability-2026-11-07.md');handoff=read(ROOT/'docs/handoff.md').split('## P07',1)[0];active=' '.join((packet,handoff)).lower()
 current_headers=' '.join(packet.splitlines()[:12]+handoff.splitlines()[:32]).lower()
 if is_verified:
  need(not re.search(r'o07.{0,80}in progress',current_headers) and 'verification in progress' not in current_headers,'final current headers retain in-progress claim')
  need(not re.search(r'(?:full matrix|new o07 seal|source seal).{0,60}(?:remain[s]? )?pending',current_headers),'final current headers retain unfinished matrix/seal claim')
  need(bool(re.search(r'o07.{0,35}(?:is |\*\*)?verified',active)),'final O07 verified statement missing')
  need(all(w in active for w in ['debug','release','clang','sanitizer']) and ('clean' in active or 'fresh source' in active),'final five configuration documentation missing')
  need('99' in active and NEW_SEAL.rsplit('/',1)[1] in active and str(file_sha(ROOT/NEW_SEAL)) in active,'final99/new seal hash citation missing')
 else:need('in progress' in active and 'pending' in active,'pending native phase not documented')
 return {'counts':counts,'O07':by.get('O07'),'expected':expected,'unique_cards':len(set(ids)),'full_scope_active':True}

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--final',action='store_true');ap.add_argument('--output',type=Path,default=VERIFY/'observability-source-evidence-audit.json');args=ap.parse_args()
 fr,freeze=frozen();ordinary,inv=inventory_and_seal(args.final);links=audit_markdown(ROOT,ordinary)
 broken=[]
 for item in links['broken_local_destinations']:
  if item.get('resolved')==NEW_SEAL and not (ROOT/NEW_SEAL).exists():pending('Markdown link awaits new seal',args.final)
  else:broken.append(item)
 need(not broken,'broken Markdown local destinations: '+json.dumps(broken));docs,_=markdown_paths(ROOT,ordinary);schema_mentions=audit_schema_refs(ROOT,docs);need(schema_mentions['all_exist'],'documented local schema files missing')
 schema=schema_references();anchors=integration(freeze);matrix=matrix_prerequisite(args.final,freeze);ledger=ledger_and_claims(args.final,matrix,inv['seal'])
 accepted=not ERRORS and not PENDING and matrix['status']=='audited_pass' and inv['seal']['status']=='audited_pass' and ledger['O07']=='verified'
 state='accepted_final_source_seal' if accepted else 'source_needs_review' if ERRORS else 'preliminary_pending_final_gates'
 out={'card':'O07','audit_state':state,'accepted':accepted,'requested_final':args.final,'auditor':pin(Path(__file__)),'freeze':fr,'inventory_and_new_seal':inv,'markdown':links,'documented_schema_paths':schema_mentions,'schema_refs':schema,'integration':anchors,'matrix_prerequisite':matrix,'ledger':ledger,'pending':PENDING,'errors':ERRORS,'limitations':'Static anchors do not replace runtime tests or independent semantic review. Historical seals are file identities/path inventories only. Markdown checks resolve local file destinations; fragment anchors/external sites are not fetched/validated.'}
 args.output.parent.mkdir(parents=True,exist_ok=True);args.output.write_text(json.dumps(out,indent=2,sort_keys=True)+'\n');lines=[state,'accepted='+str(accepted),'ordinary='+str(len(ordinary)),'pending='+json.dumps(PENDING),'errors='+json.dumps(ERRORS)];args.output.with_suffix('.log').write_text('\n'.join(lines)+'\n');print('\n'.join(lines));return 1 if ERRORS else 0
if __name__=='__main__':raise SystemExit(main())
