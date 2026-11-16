# `tools/verify_candidate_reports.py` — block usage map

[Source](../../../../tools/verify_candidate_reports.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `eb0e4214bf8a2e0973d0c5f729ee6ceb23723d8c16ee12acfd02842b41327f85`. 195 lines partitioned into 13 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../tools/verify_candidate_reports.py#L1) | Imports dependencies; declares callable signatures; declares values/defaults or compile-time conditions. | 3 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 26–29](../../../../tools/verify_candidate_reports.py#L26) | Callable definition: def local_file(uri): | calls RuntimeError; returns store\[uri\] · [reviewed contract](#b0002) |
| [B0003 · 30–30](../../../../tools/verify_candidate_reports.py#L30) | Explanatory comments or spacing. |  |
| [B0004 · 31–32](../../../../tools/verify_candidate_reports.py#L31) | Callable definition: def deny_network(uri): | calls RuntimeError · [reviewed contract](#b0004) |
| [B0005 · 33–68](../../../../tools/verify_candidate_reports.py#L33) | declares values/defaults or compile-time conditions. | 2 loop sites · [reviewed contract](#b0005) |
| [B0006 · 69–71](../../../../tools/verify_candidate_reports.py#L69) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 72–74](../../../../tools/verify_candidate_reports.py#L72) | Callable definition: def pick(artifact, **fields): | calls next, all, get, items; returns next(r\["document"\] for r in records if r\["document"\]\["artifact"\] == artifact; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 75–80](../../../../tools/verify_candidate_reports.py#L75) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 81–87](../../../../tools/verify_candidate_reports.py#L81) | Callable definition: def reject(base, path, value): | calls deepcopy, append, join, map; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 88–123](../../../../tools/verify_candidate_reports.py#L88) | declares values/defaults or compile-time conditions. | 4 loop sites · [reviewed contract](#b0010) |
| [B0011 · 124–136](../../../../tools/verify_candidate_reports.py#L124) | declares values/defaults or compile-time conditions. | 3 loop sites · [reviewed contract](#b0011) |
| [B0012 · 137–162](../../../../tools/verify_candidate_reports.py#L137) | declares values/defaults or compile-time conditions. | 2 loop sites; source comment (unverified): # The second native producer isolates finite-batch provenance, including both · [reviewed contract](#b0012) |
| [B0013 · 163–195](../../../../tools/verify_candidate_reports.py#L163) | declares values/defaults or compile-time conditions. | 3 loop sites · [reviewed contract](#b0013) |

## B0001

[Lines 1–25](../../../../tools/verify_candidate_reports.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute the P07 native candidate-report/schema acceptance checker, including at module import. |
| inputs / outputs | Exactly fixture executable/repository root argv required; module loads all local schemas, then --emit subprocess and validation/mutation corpus. Optional fourth argv entry enables actual finite-proposal and EXPLAIN fixture production; existing two-argument use remains supported. |
| invariants | There is no __main__ guard: importing invokes argv/IO/native work. DeprecationWarning suppressed only while importing RefResolver; no runtime error suppression. JSON/schema pass cannot create typed original-proof authority. |
| ownership | Owns schema store, captured native output/DOMs and mutation list; records selected later alias corpus, mutants deep-copy. |
| failure | Usage SystemExit, import/IO/schema/subprocess failures visible; many checks are bare assert and require normal Python. |
| cost | Full schema glob/read+meta checks, one180s native subprocess with complete captured output and allocating mutation suite. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md), [docs/candidate_alternatives.md](../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../meta_decompositions.md) |

## B0002

[Lines 26–29](../../../../tools/verify_candidate_reports.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def local_file(uri):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve only schema URIs already present in the local schema store. |
| inputs / outputs | URI in; existing parsed schema DOM out. |
| invariants | Unknown file URI raises; known schemas retain actual $id/fileURI identity, no network fetch. |
| ownership | Returns alias to store-owned schema graph; no deep copy. |
| failure | RuntimeError on unknown URI; key/type errors propagate. |
| cost | Expected O(1) dict membership/lookup, no IO in accepted branch. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 31–32](../../../../tools/verify_candidate_reports.py#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def deny_network(uri):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an attempted http/https schema resolution. |
| inputs / outputs | URI in; no normal result. |
| invariants | Explicit handlers bind both http/https in RefResolver; this rejects network rather than certifying schema semantics. |
| ownership | Exception owns diagnostic URI text. |
| failure | Always raises RuntimeError at resolution phase. |
| cost | O(URI bytes) diagnostic allocation; no network call. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0005

[Lines 33–68](../../../../tools/verify_candidate_reports.py#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
schema_path = schema_dir / "candidate-report-v1.schema.json"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the candidate validator and emit the actual native candidate fixture corpus. |
| inputs / outputs | Local schema store in; Draft202012Validator with deny handlers, --emit capture and parsed records out. |
| invariants | Meta-validates candidate schema; child timeout180, requires zero exit and empty stderr before parsing. Captured output has no byte cap. |
| ownership | Owns validator/schema references and full captured strings/parsed records; child is separate native owner. |
| failure | Subprocess timeout/nonzero/stderr/JSON/schema errors abort; no catch cleanup or acceptance fallback. |
| cost | One native producer plus complete schema/JSON parse; corpus and captures can coexist in process memory. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
artifacts = set()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Audit each candidate artifact's exact record shape and original-proof bindings. |
| inputs / outputs | Parsed records in; collects unique names, versions and artifact kinds while validating each document. |
| invariants | Candidate checked upper equals original proof height but retains checked_upper_only; progress/snapshot retain original query proof scope. Export labels do not become an independently replayed proof. |
| ownership | Borrows records, owns names/version/artifact sets; proof aliases document. |
| failure | Schema failure or bare AssertionError aborts before mutations; malformed fields propagate. |
| cost | O(records+prefix candidates+proof comparison size) traversal and schema validation. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 69–71](../../../../tools/verify_candidate_reports.py#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
assert versions == {1, 2, 3}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require all three binding versions and all three candidate artifact families. |
| inputs / outputs | Collected versions/artifacts in; asserts exact sets {1,2,3} and minimum/progress/snapshot families. |
| invariants | Coverage is finite emitted fixtures, not all query formats or candidate families. |
| ownership | Borrows sets; fixed expected set allocations. |
| failure | Bare AssertionError on missing/extra coverage. |
| cost | Fixed set comparisons, no native work. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0007

[Lines 72–74](../../../../tools/verify_candidate_reports.py#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def pick(artifact, **fields):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select an existing candidate artifact matching explicit field predicates. |
| inputs / outputs | Artifact label and keyword field values in; first matching document object out. |
| invariants | Does not require uniqueness itself; outer records already have unique names. Selected graph remains mutable DTO, not typed evidence. |
| ownership | Returns alias to retained native parsed document; no deepcopy. |
| failure | StopIteration if no match; field/type errors propagate. |
| cost | O(records×requested fields) linear scan until first match. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0008

[Lines 75–80](../../../../tools/verify_candidate_reports.py#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
candidate = pick("minimum_height_candidate")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose candidate/progress/exhausted-snapshot bases and initialize the retained mutant list. |
| inputs / outputs | pick results in; aliases three corpus docs and owns empty mutations list. |
| invariants | Original bases never mutated by reject; alias selection is not a native handle. |
| ownership | Retains original documents; mutants later each own deep copies. |
| failure | Missing fixture StopIteration aborts before mutations. |
| cost | Three linear scans, fixed assignments/list allocation. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0009

[Lines 81–87](../../../../tools/verify_candidate_reports.py#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def reject(base, path, value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a schema-negative candidate mutation for later validation. |
| inputs / outputs | Base document, key/index path and replacement value in; appends (path text,mutant) to module mutations. |
| invariants | Despite name, does not validate/reject immediately; final loop requires each mutant invalid. No native proof state is touched. |
| ownership | Deep-copies base; replacement value retained without additional deepcopy, result list owns clone. |
| failure | Path/deepcopy/type/OOM failures propagate; partial previous mutants remain in process. |
| cost | O(base graph) clone plus O(path length) walk and label join per mutation; all mutants retained simultaneously. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0010

[Lines 88–123](../../../../tools/verify_candidate_reports.py#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
for base in (candidate, progress, snapshot):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build focused unknown-field/proof-scope/height/cost/family candidate negative controls. |
| inputs / outputs | Three selected bases in; reject adds deep-cloned mutants for top/nested unknowns and invalid authority/limit/status fields. |
| invariants | Local cost labels never grant globally optimal proof; negative tests intentionally mutate DTOs, not native engine code. |
| ownership | Owns one whole clone per registered mutation; original corpus unchanged. |
| failure | Unexpected mutation construction errors propagate; no catch acceptance. |
| cost | Repeated full document deep copies and path walks, accumulating mutant memory. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0011

[Lines 124–136](../../../../tools/verify_candidate_reports.py#L124); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
assert any(r["document"].get("stop_reason") == "allocation_failure" for r in records)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require allocation/failed fixture cases and schema rejection of every retained mutant. |
| inputs / outputs | Native records plus mutation list in; adds remaining numeric/enum negatives, validator.is_valid each, prints record/mutation count. |
| invariants | Includes structural-key/allocation/byte/signature invalids; only explicitly covered schema mutations are demonstrated, no full runtime proof replay. The optional finite corpus adds five actual documents and fourteen one-field cross-family/schema negatives, with local-only resolution. |
| ownership | Borrows retained native/mutant graphs; output formatting temporary. |
| failure | Bare fixture asserts; accepted mutant explicitly raises AssertionError; schema resolution/IO errors surface. |
| cost | Scans records for required cases and revalidates every whole mutant; no further producer execution. |
| Design | [tools/verify_candidate_reports.py](../../../../tools/verify_candidate_reports.py), [docs/residual_candidates.md](../../../residual_candidates.md), [schemas/candidate-report-v1.schema.json](../../../../schemas/candidate-report-v1.schema.json), [tests/unit/candidates_io_test.cpp](../../../../tests/unit/candidates_io_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md), [docs/candidate_alternatives.md](../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../meta_decompositions.md) |

## B0012

[Lines 137–162](../../../../tools/verify_candidate_reports.py#L137); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L137-L162:sha256:ac49d79389e13d7901621dca57f7540a175dd2f91695805b2e07e0619b51742a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate five actual native finite-proposal and EXPLAIN reports when the optional producer is supplied. |
| inputs / outputs | Native producer path and local schemas in; validated named document/validator pairs out. |
| invariants | Real producer succeeds without stderr; exactly three finite candidate artifacts and two EXPLAIN family controls are present; network schema resolution rejects. |
| ownership | Local JSON corpus, schema store and validators are owned by this checker process. |
| failure | Native failure/timeout, malformed or unexpected document, invalid schema or report fails the checker. |
| cost | One bounded native subprocess plus parsing/local schema validation over full document sizes; diagnostic test only. |
| Design | [docs/candidate_alternatives.md](../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../meta_decompositions.md), [Refactor.md](../../../../Refactor.md) |

## B0013

[Lines 163–195](../../../../tools/verify_candidate_reports.py#L163); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L163-L195:sha256:4d1806b6f32b2757cec47f4605d2e84ebdef264ae38aea16bd6b6a31935d55cc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject fourteen one-field finite-family/source/exhaustion schema mutations. |
| inputs / outputs | Previously validated native documents in; deep-copied mutants and rejection count out. |
| invariants | Both EXPLAIN family directions and snapshot/member labels are checked; edited JSON creates no typed proof authority. Parent/member fence isolation has a separate receiving control. |
| ownership | Each mutant owns a deep copy; source documents and actual engine artifacts remain unchanged. |
| failure | An accepted mutant raises AssertionError with its path; native/schema failures remain failures. |
| cost | Fourteen deep copies and full schema validations; cost scales with document size outside production execution. |
| Design | [docs/candidate_alternatives.md](../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../meta_decompositions.md), [Refactor.md](../../../../Refactor.md) |
