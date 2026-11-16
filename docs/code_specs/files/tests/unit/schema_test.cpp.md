# `tests/unit/schema_test.cpp` — block usage map

[Source](../../../../../tests/unit/schema_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `05411d54a8782f9d40fe15caf8372afef2320edf442e2ddd04f8a70cd7efb995`. 159 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/schema_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 17–17](../../../../../tests/unit/schema_test.cpp#L17) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../tests/unit/schema_test.cpp#L18) | Callable definition: Value text(std::string value) | calls ; returns value · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../tests/unit/schema_test.cpp#L19) | Callable definition: void check(bool value,const std::string& message) | calls std::runtime_error; guard void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0004) |
| [B0005 · 20–23](../../../../../tests/unit/schema_test.cpp#L20) | Callable definition: void error(const std::function&lt;void()&gt;& work,std::string_view code) | calls void, work, check, code; guard try { work(); } catch (const Error& failure) { check(failure.code()==code,"unexpected error: "+fail… · [reviewed contract](#b0005) |
| [B0006 · 24–25](../../../../../tests/unit/schema_test.cpp#L24) | Callable definition: Catalog catalog() | calls ; returns {3,{{@ ,{{@ ,ScalarType::int64},{@ ,ScalarType::int64},{@ ,ScalarType::string}}}, · [reviewed contract](#b0006) |
| [B0007 · 26–32](../../../../../tests/unit/schema_test.cpp#L26) | Callable definition: NormalizedSql program(std::string_view sql,const BindOptions& types={},const NormalizeOptions& values={}) | calls bind_sql, catalog, std::runtime_error, normalize_sql; returns std::get&lt;NormalizedSql&gt;(std::move(result)) · [reviewed contract](#b0007) |
| [B0008 · 33–35](../../../../../tests/unit/schema_test.cpp#L33) | Callable definition: Relation snapshot(const AdapterState& state) | calls map_sql_result, query, reference::evaluate, logical; returns map_sql_result(state.query(),reference::evaluate(state.query().core_catalog,state.query().core,stat… · [reviewed contract](#b0008) |
| [B0009 · 36–41](../../../../../tests/unit/schema_test.cpp#L36) | Callable definition: void digest_vectors() | calls check, sha256, std::string; guard check(sha256("")=="e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855","SHA-256 empty… · [reviewed contract](#b0009) |
| [B0010 · 42–88](../../../../../tests/unit/schema_test.cpp#L42) | Callable definition: void program_roundtrip_and_rejection() | calls program, io::write_sql_normalization, io::read_sql_normalization, dump; guard check(io::write_sql_normalization(restored).dump()==encoded.dump(),"full normalized round trip is b…; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 89–107](../../../../../tests/unit/schema_test.cpp#L89) | Callable definition: void version_migration() | calls n, text, io::write_document, dump; guard check(upgraded.schema_version==version,"explicit CQ target version retained");; growth insert; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 108–137](../../../../../tests/unit/schema_test.cpp#L108) | Callable definition: void direct_identities() | calls io::query_identity, check, std::swap, error; guard check(identity.canonical==renamed.canonical && identity.semantic_sha256==renamed.semantic_sha256 &&…; growth push_back · [reviewed contract](#b0012) |
| [B0013 · 138–152](../../../../../tests/unit/schema_test.cpp#L138) | Callable definition: void sql_identities() | calls program, io::query_identity, check, n; guard check(a.canonical==b.canonical && a.plan_cache_sha256==b.plan_cache_sha256,"SQL FROM/predicate orde… · [reviewed contract](#b0013) |
| [B0014 · 153–153](../../../../../tests/unit/schema_test.cpp#L153) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 154–159](../../../../../tests/unit/schema_test.cpp#L154) | Callable definition: int main() | calls digest_vectors, program_roundtrip_and_rejection, version_migration, direct_identities; returns 1 · [reviewed contract](#b0015) |

## B0001

[Lines 1–16](../../../../../tests/unit/schema_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:c595367d94970b1cb554c08f818d690a13518e7373a25c25494ad5b0856a9618
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare schema_test.cpp: include "crown/api/error.hpp", "crown/frontend/adapter.hpp", "crown/io/binding.hpp", "crown/io/identity.hpp", "crown/io/normalization.hpp", "crown/ir/digest.hpp", "evaluator.hpp", &lt;functional&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–17](../../../../../tests/unit/schema_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Constructs an integer Value for normalized document and query fixtures. |
| inputs / outputs | Accepts int64 and returns Value. |
| invariants | No widening or string conversion is performed here. |
| ownership | Returned scalar is owned by caller. |
| failure | Constructor failures propagate. |
| cost | One scalar construction. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0003

[Lines 18–18](../../../../../tests/unit/schema_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value text(std::string value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Constructs a text Value for schema fixtures. |
| inputs / outputs | Moves a by-value string into Value and returns it. |
| invariants | Text content is preserved as provided. |
| ownership | Returned Value owns the string payload. |
| failure | Allocation/construction failures propagate. |
| cost | One text scalar and its ordinary storage. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0004

[Lines 19–19](../../../../../tests/unit/schema_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raises a schema-test exception on false. |
| inputs / outputs | Takes bool and const message reference. |
| invariants | Successful calls do not enter the error branch; arguments may be evaluated eagerly. |
| ownership | Message is not retained. |
| failure | False throws runtime_error. |
| cost | Branch-only assertion. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp) |

## B0005

[Lines 20–23](../../../../../tests/unit/schema_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void error(const std::function<void()>& work,std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Asserts that a callable throws a CROWN Error with one requested code. |
| inputs / outputs | Accepts const std::function reference; calls named work parameter and checks Error.code(). |
| invariants | Only matching Error type/code passes; non-Crown exceptions propagate. |
| ownership | Callable is borrowed; no result is retained. |
| failure | Missing Error or wrong code throws runtime_error. |
| cost | One invocation; no allocator-attempt assertion. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0006

[Lines 24–25](../../../../../tests/unit/schema_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds the small catalog used by normalization and identity tests. |
| inputs / outputs | Returns catalog version 3 with r/s/zero schemas. |
| invariants | Table/column order is part of downstream binding and digest inputs. |
| ownership | Catalog owns its schemas/names. |
| failure | Fixture allocation failures propagate. |
| cost | One fixed catalog construction. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [src/catalog/catalog.cpp](../../../../../src/catalog/catalog.cpp) |

## B0007

[Lines 26–32](../../../../../tests/unit/schema_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NormalizedSql program(std::string_view sql,const BindOptions& types={},const NormalizeOptions& values={})
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Binds and normalizes a SQL string to an owned normalized program. |
| inputs / outputs | Uses the local catalog, BindOptions, and NormalizeOptions; converts a binding diagnostic to runtime_error, then returns normalized program by value from the variant. |
| invariants | Only binding and normalization success reaches return; the helper does not claim physical execution. |
| ownership | NormalizedSql owns its retained source/schema data; local catalog lifetime ends after return. |
| failure | Binding diagnostics are rendered into an exception; normalization errors propagate. |
| cost | One bind and normalization pipeline per call, with ordinary AST/program allocations. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0008

[Lines 33–35](../../../../../tests/unit/schema_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation snapshot(const AdapterState& state)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Maps a reference AdapterState to an owning relation snapshot. |
| inputs / outputs | Passes catalog/query/database into reference evaluation and maps the result to Relation. |
| invariants | Used as a semantic oracle snapshot, not a native runtime result. |
| ownership | Returned Relation owns result rows. |
| failure | Evaluation/mapping errors propagate. |
| cost | One finite reference evaluation and result mapping; no account counter. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0009

[Lines 36–41](../../../../../tests/unit/schema_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void digest_vectors()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks four SHA-256 input vectors through the digest API. |
| inputs / outputs | Hashes empty, abc, a two-block pattern, and one million a bytes, then compares fixed hexadecimal results. |
| invariants | Four named vectors are asserted; this is test evidence for those vectors, not a general cryptographic proof. |
| ownership | Digest output is fixed-size value; million-byte input string is local ordinary storage. |
| failure | Any digest mismatch fails via check. |
| cost | Four digest calls; the million-byte vector is built and processed, with no timing claim. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [include/crown/ir/digest.hpp](../../../../../include/crown/ir/digest.hpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp), [docs/query_identity.md](../../../../query_identity.md) |

## B0010

[Lines 42–88](../../../../../tests/unit/schema_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void program_roundtrip_and_rejection()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks normalized-program roundtrip, identity, rejection, and replay limits. |
| inputs / outputs | Roundtrips SQL normalization and binding, verifies repeated-output answer support, mutates ten document fields, tests unsupported version and zero work/normalization bounds, NULL EXISTS, Unicode alias output, and diagnostic-artifact writer rejection. |
| invariants | Canonical roundtrip is compared on encoded values; each listed mutation is expected to reject; replay limits are distinct from parsing and semantic results. |
| ownership | Program, Json, and reference snapshots own their values; caller SQL is not required after returned program construction. |
| failure | Invalid documents, versions, budgets, and diagnostic writer input reject at their respective boundaries. |
| cost | Ten mutation cases plus fixed roundtrip and limit probes; JSON and evaluator allocations are ordinary and no CPU metric is collected. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/query_identity.md](../../../../query_identity.md) |

## B0011

[Lines 89–107](../../../../../tests/unit/schema_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void version_migration()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks v1 document upgrades through v1/v2/v3 and reference event preservation. |
| inputs / outputs | Upgrades one old CQ1 document with updates to each supported version and compares schema version, initial snapshot, and all session events. |
| invariants | Upgrade is additive version conversion for these fixture inputs; writer preserves v1, and downgrade/latest4 requests reject. |
| ownership | Decoded Documents and Session states own their rows; snapshots are copied Relations. |
| failure | Unsupported upgrade targets must throw expected errors; altered snapshots/events fail. |
| cost | Three version outputs and finite reference event replays; no broad migration corpus claim. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/schema_evolution.md](../../../../schema_evolution.md) |

## B0012

[Lines 108–137](../../../../../tests/unit/schema_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void direct_identities()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks direct CQ semantic identity against explicit query-shape mutations. |
| inputs / outputs | Computes identities for alpha-renamed/reordered atoms, output labels/positions, statistics, schema/planner versions, unsupported arithmetic, zero work, containment, contradiction, and empty conjunction. |
| invariants | Assertions distinguish semantic from cost-cache identity; alpha and atom order are normalized for examples; 64-character digest length is checked for empty conjunction. |
| ownership | Identity results own digest and inverse-mapping data; inputs are local query/catalog values. |
| failure | Work-limited or unsupported identity cases return/throw the expected status; mismatches fail. |
| cost | Finite identity cases; symmetric/permutation work is synthetic identity work, not measured CPU or a general complexity bound. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [src/io/identity.cpp](../../../../../src/io/identity.cpp), [include/crown/io/identity.hpp](../../../../../include/crown/io/identity.hpp), [docs/query_identity.md](../../../../query_identity.md) |

## B0013

[Lines 138–152](../../../../../tests/unit/schema_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sql_identities()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks canonical SQL identity across aliases, ordering, symmetry, and parameter values. |
| inputs / outputs | Normalizes a base query, equivalent alias/FROM/predicate reorderings, one four-occurrence symmetric self-join and a textually permuted equivalent, concrete parameter variants, and a changed predicate. |
| invariants | The symmetric equivalences and semantic differences are asserted only for these statements; normalized programs preserve concrete parameter identity. |
| ownership | Each returned normalized program owns its source and canonicalized IR. |
| failure | Unexpected normalization or identity equality/difference fails. |
| cost | A finite set of SQL normalization and identity calls, including one four-occurrence symmetry pair; this helper asserts no timing, work-counter, or complexity bound. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/io/identity.cpp](../../../../../src/io/identity.cpp), [docs/query_identity.md](../../../../query_identity.md) |

## B0014

[Lines 153–153](../../../../../tests/unit/schema_test.cpp#L153); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L153:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in schema_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 154–159](../../../../../tests/unit/schema_test.cpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs the five schema and query-identity groups from main. |
| inputs / outputs | No arguments; runs digest vectors, program roundtrip/rejection, version migration, direct identities, and SQL identities. |
| invariants | Success output follows all five groups; the outer std::exception handler reports failure. |
| ownership | All normalized programs and documents are scoped to the helpers. |
| failure | Caught exceptions print and return nonzero. |
| cost | Five finite groups; no execution result or performance claim is encoded by the entry point. |
| Design | [tests/unit/schema_test.cpp](../../../../../tests/unit/schema_test.cpp), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md) |
