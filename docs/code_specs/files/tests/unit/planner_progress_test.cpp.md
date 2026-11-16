# `tests/unit/planner_progress_test.cpp` — block usage map

[Source](../../../../../tests/unit/planner_progress_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `aa10d13988ad3f35fa7dd468fb31b1d60bcfe81a57482d7c6e6da4fe7fc33dd7`. 357 lines partitioned into 24 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/planner_progress_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 21–23](../../../../../tests/unit/planner_progress_test.cpp#L21) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 24–24](../../../../../tests/unit/planner_progress_test.cpp#L24) | Explanatory comments or spacing. |  |
| [B0004 · 25–28](../../../../../tests/unit/planner_progress_test.cpp#L25) | Type/record definition: struct Fixture |  · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../tests/unit/planner_progress_test.cpp#L29) | Explanatory comments or spacing. |  |
| [B0006 · 30–39](../../../../../tests/unit/planner_progress_test.cpp#L30) | Callable definition: Fixture two_relation_fixture() | calls push_back; returns fixture; growth push_back · [reviewed contract](#b0006) |
| [B0007 · 40–40](../../../../../tests/unit/planner_progress_test.cpp#L40) | Explanatory comments or spacing. |  |
| [B0008 · 41–55](../../../../../tests/unit/planner_progress_test.cpp#L41) | Callable definition: Fixture triangle_fixture() | calls push_back, std::to_string; returns fixture; growth push_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 56–56](../../../../../tests/unit/planner_progress_test.cpp#L56) | Explanatory comments or spacing. |  |
| [B0010 · 57–63](../../../../../tests/unit/planner_progress_test.cpp#L57) | Callable definition: Fixture date_fixture(bool with_catalog_metadata) | calls push_back, Date::parse; returns fixture; growth push_back · [reviewed contract](#b0010) |
| [B0011 · 64–66](../../../../../tests/unit/planner_progress_test.cpp#L64) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 67–70](../../../../../tests/unit/planner_progress_test.cpp#L67) | Callable definition: std::string certificate_schema(const io::Json& document) | calls std::to_string, at; returns @ + std::to_string(document.at(@ ).get&lt;int&gt;()) + · [reviewed contract](#b0012) |
| [B0013 · 71–71](../../../../../tests/unit/planner_progress_test.cpp#L71) | Explanatory comments or spacing. |  |
| [B0014 · 72–75](../../../../../tests/unit/planner_progress_test.cpp#L72) | Callable definition: void add_record(RecordList& records, std::string name, std::string schema, io::Json document) | calls push_back, std::move; growth push_back · [reviewed contract](#b0014) |
| [B0015 · 76–76](../../../../../tests/unit/planner_progress_test.cpp#L76) | Explanatory comments or spacing. |  |
| [B0016 · 77–88](../../../../../tests/unit/planner_progress_test.cpp#L77) | Callable definition: planner::SearchAdvance advance_to_search_completion(planner::ExactSearch& owner) | calls advance, check, std::runtime_error; guard check(advanced.progress.result != planner::ResultKind::failed,; returns advanced; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 89–89](../../../../../tests/unit/planner_progress_test.cpp#L89) | Explanatory comments or spacing. |  |
| [B0018 · 90–104](../../../../../tests/unit/planner_progress_test.cpp#L90) | Callable definition: planner::CheckedCertificate finish_replay(planner::CertificateReplay& owner, const std::string& label) | calls advance, check, checked, valid; guard check(advanced.progress.valid && owner.checked() && owner.checked()-&gt;valid(),; returns *owner.checked(); 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 105–105](../../../../../tests/unit/planner_progress_test.cpp#L105) | Explanatory comments or spacing. |  |
| [B0020 · 106–115](../../../../../tests/unit/planner_progress_test.cpp#L106) | Callable definition: void reject_legacy_reader(const io::Json& document, const Fixture& fixture, const std::string& label) | calls io::read_height_certificate, dump, check; guard check(rejected, label + " was accepted by the height-certificate reader"); · [reviewed contract](#b0020) |
| [B0021 · 116–116](../../../../../tests/unit/planner_progress_test.cpp#L116) | Explanatory comments or spacing. |  |
| [B0022 · 117–338](../../../../../tests/unit/planner_progress_test.cpp#L117) | Callable definition: RecordList build_records() | calls two_relation_fixture, planner::ExactSearch::create, io::write_search_progress, check; guard check(strict_admitted.at("artifact") == "search_progress" &&; returns records; 4 loop sites; source comment (unverified): // Typed writers have no overload or public conversion that can turn an · [reviewed contract](#b0022) |
| [B0023 · 339–341](../../../../../tests/unit/planner_progress_test.cpp#L339) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0023) |
| [B0024 · 342–357](../../../../../tests/unit/planner_progress_test.cpp#L342) | Callable definition: int main(int argc, char** argv) | calls build_records, std::string_view, io::Json, dump; guard check(argc == 1, "usage: crown_planner_progress_test \[--emit\]");; returns 0; 0 · [reviewed contract](#b0024) |

## B0001

[Lines 1–20](../../../../../tests/unit/planner_progress_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:0de1d2816e7cb86f20c4fb564f88f39176636b5650427bbeaef496dba2e677ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_progress_test.cpp: include "crown/api/error.hpp", "crown/io/search.hpp", "crown/planner/verify.hpp", "planner_probe.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–23](../../../../../tests/unit/planner_progress_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a progress/serialization assertion with a diagnostic. |
| inputs / outputs | Takes a condition and borrowed message; returns only when true. |
| invariants | False throws std::runtime_error. |
| ownership | No retained state. |
| failure | Exception construction may fail; otherwise exception propagates to main. |
| cost | One condition branch in the helper. The const std::string diagnostic is formed by the caller before entry, including for passing assertions; concatenation or non-SSO string construction can add test-harness cost. runtime_error construction is only on failure. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tools/verify_search_progress.py](../../../../../tools/verify_search_progress.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 25–28](../../../../../tests/unit/planner_progress_test.cpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the catalog/query pair consumed by progress serialization fixtures. |
| inputs / outputs | Stores Catalog and Query values used by record generation. |
| invariants | The wrapper carries test data, not a search result or authority handle. |
| ownership | Both model values are owned. |
| failure | Fixture construction can allocate and throw. |
| cost | Variable-sized input storage. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tools/verify_search_progress.py](../../../../../tools/verify_search_progress.py), [schemas/search-progress-v1.schema.json](../../../../../schemas/search-progress-v1.schema.json), [schemas/height-certificate-v1.schema.json](../../../../../schemas/height-certificate-v1.schema.json), [schemas/height-certificate-v2.schema.json](../../../../../schemas/height-certificate-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 30–39](../../../../../tests/unit/planner_progress_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture two_relation_fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the two-relation query whose verified minimum is two. |
| inputs / outputs | Builds relation scopes R(x,y), S(y) and output head x for search, serialization and binding tests. |
| invariants | This is a fixed representative fixture; its expected minimum is asserted by callers. |
| ownership | Returns an owning Fixture. |
| failure | Model allocation errors propagate. |
| cost | Small fixed query. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tools/verify_search_progress.py](../../../../../tools/verify_search_progress.py), [schemas/search-progress-v1.schema.json](../../../../../schemas/search-progress-v1.schema.json), [schemas/height-certificate-v1.schema.json](../../../../../schemas/height-certificate-v1.schema.json), [schemas/height-certificate-v2.schema.json](../../../../../schemas/height-certificate-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0008

[Lines 41–55](../../../../../tests/unit/planner_progress_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture triangle_fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a full-head triangle fixture used for verified infeasibility serialization. |
| inputs / outputs | Builds three pairwise relation scopes over three variables and returns all variables in the head. |
| invariants | The test relies on this fixture being a cyclic full-head case; this is not a generic infeasibility classifier. |
| ownership | Returns an owning Fixture. |
| failure | Model allocation errors propagate. |
| cost | Small fixed query. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0010

[Lines 57–63](../../../../../tests/unit/planner_progress_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture date_fixture(bool with_catalog_metadata) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a date-typed one-relation fixture with optional source-schema metadata. |
| inputs / outputs | Returns a query containing the leap date 2024-02-29, optionally setting catalog source_schema_version=2. |
| invariants | The serialized certificate document schema remains v2; the embedded query-binding version is 2 without metadata and 3 with it. |
| ownership | Returns owned catalog/query values. |
| failure | Invalid construction or allocation failures propagate. |
| cost | Fixed small typed query; metadata adds one field. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tools/verify_search_progress.py](../../../../../tools/verify_search_progress.py), [schemas/search-progress-v1.schema.json](../../../../../schemas/search-progress-v1.schema.json), [schemas/height-certificate-v1.schema.json](../../../../../schemas/height-certificate-v1.schema.json), [schemas/height-certificate-v2.schema.json](../../../../../schemas/height-certificate-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0011

[Lines 64–66](../../../../../tests/unit/planner_progress_test.cpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L66:sha256:b0eee5f9a21e95dae71a33ae3f85ad2e632fa8ab101da4eafd8c083e9f51f875
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_progress_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 67–70](../../../../../tests/unit/planner_progress_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string certificate_schema(const io::Json& document) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the height-certificate JSON schema path from the document schema_version. |
| inputs / outputs | Reads document.at("schema_version").get&lt;int&gt;() and concatenates the integer into "height-certificate-vN.schema.json". Current fixture documents yield v1 or v2 names. |
| invariants | The current caller supplies certificate documents with schema_version 1 or 2. This helper has no version whitelist, schema-file lookup, or validation; embedded query_binding.schema_version is a separate field and can be 1, 2, or 3. |
| ownership | Document is borrowed; output is an owning string. |
| failure | A missing schema_version or a value that cannot be read as int throws through io::Json::at/get. Another integer value simply produces a filename string; this helper does not reject it or confirm the file exists. |
| cost | One JSON lookup and integer conversion, then std::to_string and string concatenation; the resulting filename may allocate. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tools/verify_search_progress.py](../../../../../tools/verify_search_progress.py), [schemas/search-progress-v1.schema.json](../../../../../schemas/search-progress-v1.schema.json), [schemas/height-certificate-v1.schema.json](../../../../../schemas/height-certificate-v1.schema.json), [schemas/height-certificate-v2.schema.json](../../../../../schemas/height-certificate-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0014

[Lines 72–75](../../../../../tests/unit/planner_progress_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add_record(RecordList& records, std::string name, std::string schema, io::Json document) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one named JSON document with its expected schema to the record list. |
| inputs / outputs | Takes RecordList& plus name, schema filename, and io::Json document by value; appends a JSON object containing the three values. |
| invariants | This associates a schema filename with an example document; it does not open or validate the schema. The Python CTest caller performs schema validation after --emit. |
| ownership | The appended JSON record owns its name, schema string, and document. Calls that pass lvalue strings/documents first copy into the by-value parameters; record construction passes moved values into JSON field initializers, whose conversion may copy according to the JSON initializer-list constructor. |
| failure | JSON/vector growth can throw. |
| cost | Constructs a JSON record and appends it to the vector. Lvalue document arguments are copied into the by-value parameter before record assembly; JSON payload copying/object construction and vector growth depend on document size and capacity. Schema validation is not done here. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tools/verify_search_progress.py](../../../../../tools/verify_search_progress.py), [schemas/search-progress-v1.schema.json](../../../../../schemas/search-progress-v1.schema.json), [schemas/height-certificate-v1.schema.json](../../../../../schemas/height-certificate-v1.schema.json), [schemas/height-certificate-v2.schema.json](../../../../../schemas/height-certificate-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0016

[Lines 77–88](../../../../../tests/unit/planner_progress_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::SearchAdvance advance_to_search_completion(planner::ExactSearch& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a producer to completion using 4,096-work grants with a transition-count guard. |
| inputs / outputs | Returns the completing SearchAdvance or throws after one million calls. |
| invariants | Only complete succeeds; interim stops must be quantum_work/time and result nonfailed. The guard counts calls, not elapsed CPU time. |
| ownership | Borrows the ExactSearch owner, which retains its continuation. |
| failure | Failed status, unexpected stop or guard exhaustion throws. |
| cost | Repeated bounded advancement and progress checks. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0018

[Lines 90–104](../../../../../tests/unit/planner_progress_test.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::CheckedCertificate finish_replay(planner::CertificateReplay& owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish replay and return its checked certificate after a valid complete result. |
| inputs / outputs | Advances with 4,096-work grants; returns a copy of checked authority only when complete, valid and checked. |
| invariants | Nonterminal calls may stop only for quantum work/time; the one-million guard is a call count, not a CPU cap. |
| ownership | Borrows replay owner; returned CheckedCertificate owns/carries typed authority. |
| failure | Invalid completion, unexpected stop or guard exhaustion throws. |
| cost | Repeated replay advancement proportional to evidence. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0020

[Lines 106–115](../../../../../tests/unit/planner_progress_test.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reject_legacy_reader(const io::Json& document, const Fixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that a serialized artifact is rejected by the ordinary height-certificate reader. |
| inputs / outputs | Dumps a JSON document and calls read_height_certificate against the fixture; catches CROWN Error and asserts rejection. |
| invariants | This is a compatibility rejection check for selected progress/upper documents, not a schema-validation replacement. |
| ownership | Document and fixture are borrowed; dump text is temporary. |
| failure | Only CROWN Error is interpreted as expected rejection; other exceptions propagate. |
| cost | Serializes the document then parses/validates it against bound inputs. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tools/verify_search_progress.py](../../../../../tools/verify_search_progress.py), [schemas/search-progress-v1.schema.json](../../../../../schemas/search-progress-v1.schema.json), [schemas/height-certificate-v1.schema.json](../../../../../schemas/height-certificate-v1.schema.json), [schemas/height-certificate-v2.schema.json](../../../../../schemas/height-certificate-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0022

[Lines 117–338](../../../../../tests/unit/planner_progress_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RecordList build_records() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build fourteen named examples covering admitted/suspended progress, upper bounds, checked optimum/infeasibility, replay and binding versions. |
| inputs / outputs | Creates strict and best-found searches; serializes progress and typed artifacts; pauses replay at total work, raises limits, validates v1/v2 and corrupt replay, checks infeasibility and date bindings, then returns records. |
| invariants | Progress serialization keeps certificate null; best-found upper is not minimum authority; typed optimum/infeasibility requires completed proof/replay. Total-work pause is a cumulative stop, distinct from quantum. Certificate document schema v1/v2 differs from query-binding schema v1/v2/v3. This is a fixed record set, not broad property coverage. |
| ownership | Search/replay owners retain admitted snapshots; JSON records own their serialized data. |
| failure | Any semantic mismatch, binding mismatch, unexpected stop or reader acceptance throws; ordinary CROWN/JSON allocation errors propagate. |
| cost | Runs the selected search/replay fixtures and builds exactly fourteen named JSON examples. Work follows finite proof fixtures, replay grants and serialized payload size; check diagnostics are built at call sites even when assertions pass. This function creates local JSON records but does not run the Python schema driver. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tools/verify_search_progress.py](../../../../../tools/verify_search_progress.py), [schemas/search-progress-v1.schema.json](../../../../../schemas/search-progress-v1.schema.json), [schemas/height-certificate-v1.schema.json](../../../../../schemas/height-certificate-v1.schema.json), [schemas/height-certificate-v2.schema.json](../../../../../schemas/height-certificate-v2.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0023

[Lines 339–341](../../../../../tests/unit/planner_progress_test.cpp#L339); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L339-L341:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in planner_progress_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 342–357](../../../../../tests/unit/planner_progress_test.cpp#L342); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc, char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build and optionally emit progress/certificate record examples; the CTest schema path is driven by Python. |
| inputs / outputs | Builds the records first. With exactly one argument --emit it dumps the JSON array and returns zero; with no arguments it checks nonempty records, prints a status line and returns zero; other argument lists fail. |
| invariants | CTest planner_progress_schemas runs tools/verify_search_progress.py, which invokes --emit, checks local schemas, validates the emitted records and rejects six authority/limit mutations. The native executable performs its own semantic assertions and labels/emits fourteen records; it does not perform JSON Schema validation. Its no-argument branch is not the schema-driver contract. |
| ownership | Records are owned until output and then released on process exit. |
| failure | Catches std::exception, prints it and returns nonzero. |
| cost | Always builds all fourteen records before checking argv. --emit additionally serializes the full JSON array; the no-argument path also pays fixture/search/replay and record-construction costs before printing. CTest then adds Python schema loading/validation and six negative mutations. |
| Design | [tests/unit/planner_progress_test.cpp](../../../../../tests/unit/planner_progress_test.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/io/oracle.hpp](../../../../../include/crown/io/oracle.hpp), [src/io/search.cpp](../../../../../src/io/search.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [tools/verify_search_progress.py](../../../../../tools/verify_search_progress.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
