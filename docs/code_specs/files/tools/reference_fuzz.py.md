# `tools/reference_fuzz.py` — block usage map

[Source](../../../../tools/reference_fuzz.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `c9e551b286e2791465bf0fc43746f7bc3e229f0b38ace2d11b6f0c074284e2c6`. 912 lines partitioned into 77 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–36](../../../../tools/reference_fuzz.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 37–42](../../../../tools/reference_fuzz.py#L37) | declares types or opens a type body; declares callable signatures. | source comment (unverified): # Diagnostic graphs are retained by reference; callers must preserve them until serialization. · [reviewed contract](#b0002) |
| [B0003 · 43–57](../../../../tools/reference_fuzz.py#L43) | Callable definition: def __init__( | calls super · [reviewed contract](#b0003) |
| [B0004 · 58–66](../../../../tools/reference_fuzz.py#L58) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 67–74](../../../../tools/reference_fuzz.py#L67) | Callable definition: def json_type(value: Any) -&gt; str: | calls isinstance, FuzzError; returns "bool"; "int64" · [reviewed contract](#b0005) |
| [B0006 · 75–76](../../../../tools/reference_fuzz.py#L75) | Explanatory comments or spacing. |  |
| [B0007 · 77–79](../../../../tools/reference_fuzz.py#L77) | Callable definition: def value_for(type_name: str, index: int) -&gt; Any: | calls len; returns domain\[index % len(domain)\] · [reviewed contract](#b0007) |
| [B0008 · 80–81](../../../../tools/reference_fuzz.py#L80) | Explanatory comments or spacing. |  |
| [B0009 · 82–83](../../../../tools/reference_fuzz.py#L82) | Callable definition: def random_value(rng: random.Random, type_name: str) -&gt; Any: | calls choice; returns rng.choice(VALUE_DOMAIN\[type_name\]) · [reviewed contract](#b0009) |
| [B0010 · 84–85](../../../../tools/reference_fuzz.py#L84) | Explanatory comments or spacing. |  |
| [B0011 · 86–94](../../../../tools/reference_fuzz.py#L86) | Callable definition: def unique_rows(rows: Iterable\[list\[Any\]\]) -&gt; list\[list\[Any\]\]: | calls set, dumps, add, append; returns result; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 95–96](../../../../tools/reference_fuzz.py#L95) | Explanatory comments or spacing. |  |
| [B0013 · 97–98](../../../../tools/reference_fuzz.py#L97) | Callable definition: def variable(name: str, type_name: str) -&gt; dict\[str, str\]: | calls ; returns {"name": name, "type": type_name} · [reviewed contract](#b0013) |
| [B0014 · 99–100](../../../../tools/reference_fuzz.py#L99) | Explanatory comments or spacing. |  |
| [B0015 · 101–102](../../../../tools/reference_fuzz.py#L101) | Callable definition: def column(name: str, type_name: str) -&gt; dict\[str, str\]: | calls ; returns {"name": name, "type": type_name} · [reviewed contract](#b0015) |
| [B0016 · 103–104](../../../../tools/reference_fuzz.py#L103) | Explanatory comments or spacing. |  |
| [B0017 · 105–106](../../../../tools/reference_fuzz.py#L105) | Callable definition: def atom(atom_id: str, table: str, terms: list\[dict\[str, Any\]\]) -&gt; dict\[str, Any\]: | calls ; returns {"id": atom_id, "table": table, "terms": terms} · [reviewed contract](#b0017) |
| [B0018 · 107–108](../../../../tools/reference_fuzz.py#L107) | Explanatory comments or spacing. |  |
| [B0019 · 109–110](../../../../tools/reference_fuzz.py#L109) | Callable definition: def var_term(name: str) -&gt; dict\[str, str\]: | calls ; returns {"var": name} · [reviewed contract](#b0019) |
| [B0020 · 111–112](../../../../tools/reference_fuzz.py#L111) | Explanatory comments or spacing. |  |
| [B0021 · 113–114](../../../../tools/reference_fuzz.py#L113) | Callable definition: def ignore_term() -&gt; dict\[str, bool\]: | calls ; returns {"ignore": True} · [reviewed contract](#b0021) |
| [B0022 · 115–116](../../../../tools/reference_fuzz.py#L115) | Explanatory comments or spacing. |  |
| [B0023 · 117–118](../../../../tools/reference_fuzz.py#L117) | Callable definition: def const_term(value: Any) -&gt; dict\[str, Any\]: | calls ; returns {"const": value} · [reviewed contract](#b0023) |
| [B0024 · 119–120](../../../../tools/reference_fuzz.py#L119) | Explanatory comments or spacing. |  |
| [B0025 · 121–233](../../../../tools/reference_fuzz.py#L121) | Callable definition: def build_shape(shape: str, type_name: str) -&gt; tuple\[list\[dict\[str, Any\]\], dict\[str, Any\], list\[dict\[str, Any\]\]\]: | calls value_for, column, variable, atom; returns tables, query, initial; 1 loop sites · [reviewed contract](#b0025) |
| [B0026 · 234–235](../../../../tools/reference_fuzz.py#L234) | Explanatory comments or spacing. |  |
| [B0027 · 236–281](../../../../tools/reference_fuzz.py#L236) | Callable definition: def make_updates( | calls tuple, random_row, random_value, range; returns \[; updates; growth insert; 6 loop sites · [reviewed contract](#b0027) |
| [B0028 · 282–283](../../../../tools/reference_fuzz.py#L282) | Explanatory comments or spacing. |  |
| [B0029 · 284–300](../../../../tools/reference_fuzz.py#L284) | Callable definition: def generate_case(seed: int, update_count: int = 12) -&gt; dict\[str, Any\]: | calls FuzzError, len, build_shape, Random; returns { · [reviewed contract](#b0029) |
| [B0030 · 301–302](../../../../tools/reference_fuzz.py#L301) | Explanatory comments or spacing. |  |
| [B0031 · 303–305](../../../../tools/reference_fuzz.py#L303) | Callable definition: def _require(condition: bool, message: str) -&gt; None: | calls FuzzError · [reviewed contract](#b0031) |
| [B0032 · 306–307](../../../../tools/reference_fuzz.py#L306) | Explanatory comments or spacing. |  |
| [B0033 · 308–379](../../../../tools/reference_fuzz.py#L308) | Callable definition: def validate_generated_document(document: dict\[str, Any\]) -&gt; None: | calls _require, get, isinstance, set; growth insert; 12 loop sites · [reviewed contract](#b0033) |
| [B0034 · 380–381](../../../../tools/reference_fuzz.py#L380) | Explanatory comments or spacing. |  |
| [B0035 · 382–383](../../../../tools/reference_fuzz.py#L382) | Callable definition: def _quote(identifier: str) -&gt; str: | calls replace; returns '"' + identifier.replace('"', '""') + '"' · [reviewed contract](#b0035) |
| [B0036 · 384–385](../../../../tools/reference_fuzz.py#L384) | Explanatory comments or spacing. |  |
| [B0037 · 386–389](../../../../tools/reference_fuzz.py#L386) | Callable definition: def _to_sql_value(value: Any) -&gt; Any: | calls isinstance, int; returns int(value); value · [reviewed contract](#b0037) |
| [B0038 · 390–391](../../../../tools/reference_fuzz.py#L390) | Explanatory comments or spacing. |  |
| [B0039 · 392–431](../../../../tools/reference_fuzz.py#L392) | Callable definition: def build_sql(document: dict\[str, Any\]) -&gt; SqlPlan: | calls enumerate, append, _quote, _to_sql_value; returns SqlPlan(statement, tuple(parameters), output_types); 7 loop sites · [reviewed contract](#b0039) |
| [B0040 · 432–433](../../../../tools/reference_fuzz.py#L432) | Explanatory comments or spacing. |  |
| [B0041 · 434–441](../../../../tools/reference_fuzz.py#L434) | Callable definition: def _decode_sql_value(value: Any, type_name: str) -&gt; Any: | calls bool, int, str, FuzzError; returns bool(value); int(value) · [reviewed contract](#b0041) |
| [B0042 · 442–443](../../../../tools/reference_fuzz.py#L442) | Explanatory comments or spacing. |  |
| [B0043 · 444–445](../../../../tools/reference_fuzz.py#L444) | Callable definition: def _sorted_json_rows(rows: Iterable\[tuple\[Any, ...\]\]) -&gt; list\[list\[Any\]\]: | calls list, sorted; returns \[list(row) for row in sorted(rows)\]; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 446–447](../../../../tools/reference_fuzz.py#L446) | Explanatory comments or spacing. |  |
| [B0045 · 448–536](../../../../tools/reference_fuzz.py#L448) | Callable definition: def sqlite_reference(document: dict\[str, Any\]) -&gt; tuple\[dict\[str, Any\], SqlPlan\]: | calls build_sql, connect, append, _quote; returns set(); {()} if raw_rows else set(); growth insert; 15 loop sites · [reviewed contract](#b0045) |
| [B0046 · 537–538](../../../../tools/reference_fuzz.py#L537) | Explanatory comments or spacing. |  |
| [B0047 · 539–545](../../../../tools/reference_fuzz.py#L539) | Callable definition: def json_equal(left: Any, right: Any) -&gt; bool: | calls dumps; returns json.dumps( · [reviewed contract](#b0047) |
| [B0048 · 546–547](../../../../tools/reference_fuzz.py#L546) | Explanatory comments or spacing. |  |
| [B0049 · 548–569](../../../../tools/reference_fuzz.py#L548) | Callable definition: def first_difference(actual: Any, expected: Any, path: str = "$") -&gt; str \| None: | calls type, differs, isinstance, set; returns f"{path}: type differs ({type(actual).__name__} != {type(expected).__name__})"; f"{path}: object ke…; 2 loop sites · [reviewed contract](#b0049) |
| [B0050 · 570–571](../../../../tools/reference_fuzz.py#L570) | Explanatory comments or spacing. |  |
| [B0051 · 572–606](../../../../tools/reference_fuzz.py#L572) | Callable definition: def _invoke(executable: str, command: str, document: dict\[str, Any\]) -&gt; Any: | calls TemporaryDirectory, Path, write_text, dumps; returns json.loads(result.stdout) · [reviewed contract](#b0051) |
| [B0052 · 607–608](../../../../tools/reference_fuzz.py#L607) | Explanatory comments or spacing. |  |
| [B0053 · 609–612](../../../../tools/reference_fuzz.py#L609) | Callable definition: def validate_with_cli(executable: str, document: dict\[str, Any\]) -&gt; None: | calls _invoke, get, FuzzError · [reviewed contract](#b0053) |
| [B0054 · 613–614](../../../../tools/reference_fuzz.py#L613) | Explanatory comments or spacing. |  |
| [B0055 · 615–619](../../../../tools/reference_fuzz.py#L615) | Callable definition: def cli_reference(executable: str, document: dict\[str, Any\]) -&gt; dict\[str, Any\]: | calls _invoke, isinstance, FuzzError; returns result · [reviewed contract](#b0055) |
| [B0056 · 620–621](../../../../tools/reference_fuzz.py#L620) | Explanatory comments or spacing. |  |
| [B0057 · 622–632](../../../../tools/reference_fuzz.py#L622) | Callable definition: def compare_case(executable: str, document: dict\[str, Any\]) -&gt; tuple\[dict\[str, Any\], dict\[str, Any\], SqlPlan\]: | calls validate_generated_document, validate_with_cli, cli_reference, sqlite_reference; returns actual, expected, plan · [reviewed contract](#b0057) |
| [B0058 · 633–634](../../../../tools/reference_fuzz.py#L633) | Explanatory comments or spacing. |  |
| [B0059 · 635–639](../../../../tools/reference_fuzz.py#L635) | Callable definition: def resequence(document: dict\[str, Any\]) -&gt; dict\[str, Any\]: | calls deepcopy, enumerate, get; returns result; 1 loop sites · [reviewed contract](#b0059) |
| [B0060 · 640–642](../../../../tools/reference_fuzz.py#L640) | Module statements. | source comment (unverified): # Deletion-local minimization can rerun native and SQLite oracles many times. · [reviewed contract](#b0060) |
| [B0061 · 643–676](../../../../tools/reference_fuzz.py#L643) | Callable definition: def _ddmin( | calls list, ceil, len, range; returns current; 4 loop sites · [reviewed contract](#b0061) |
| [B0062 · 677–678](../../../../tools/reference_fuzz.py#L677) | Explanatory comments or spacing. |  |
| [B0063 · 679–719](../../../../tools/reference_fuzz.py#L679) | Callable definition: def shrink_trace( | calls resequence, enumerate, get, append; returns resequence(candidate); resequence(candidate); 6 loop sites · [reviewed contract](#b0063) |
| [B0064 · 720–721](../../../../tools/reference_fuzz.py#L720) | Explanatory comments or spacing. |  |
| [B0065 · 722–731](../../../../tools/reference_fuzz.py#L722) | Callable definition: def inject_duplicate_delta_fault(result: dict\[str, Any\]) -&gt; dict\[str, Any\]: | calls deepcopy, get, in, append; returns corrupted; corrupted; 2 loop sites · [reviewed contract](#b0065) |
| [B0066 · 732–733](../../../../tools/reference_fuzz.py#L732) | Explanatory comments or spacing. |  |
| [B0067 · 734–738](../../../../tools/reference_fuzz.py#L734) | Callable definition: def fault_is_observed(executable: str, document: dict\[str, Any\]) -&gt; bool: | calls cli_reference, sqlite_reference, inject_duplicate_delta_fault, first_difference; returns first_difference(corrupted, expected) is not None · [reviewed contract](#b0067) |
| [B0068 · 739–740](../../../../tools/reference_fuzz.py#L739) | Explanatory comments or spacing. |  |
| [B0069 · 741–792](../../../../tools/reference_fuzz.py#L741) | Callable definition: def shrinker_fault_case(executable: str, seed: int = 0, update_count: int = 12) -&gt; dict\[str, Any\]: | calls generate_case, len, FuzzError, value_for; returns its minimized packet."""; {; growth insert; 1 loop sites · [reviewed contract](#b0069) |
| [B0070 · 793–794](../../../../tools/reference_fuzz.py#L793) | Explanatory comments or spacing. |  |
| [B0071 · 795–860](../../../../tools/reference_fuzz.py#L795) | Callable definition: def _invalid_variant( | calls deepcopy, get, FuzzError, next; 1 loop sites · [reviewed contract](#b0071) |
| [B0072 · 861–862](../../../../tools/reference_fuzz.py#L861) | Explanatory comments or spacing. |  |
| [B0073 · 863–867](../../../../tools/reference_fuzz.py#L863) | Callable definition: def check_invalid_variants(executable: str, document: dict\[str, Any\]) -&gt; int: | calls _invalid_variant; returns 3 · [reviewed contract](#b0073) |
| [B0074 · 868–869](../../../../tools/reference_fuzz.py#L868) | Explanatory comments or spacing. |  |
| [B0075 · 870–889](../../../../tools/reference_fuzz.py#L870) | Callable definition: def make_failure_packet( | calls len, str, deepcopy, get; returns { · [reviewed contract](#b0075) |
| [B0076 · 890–891](../../../../tools/reference_fuzz.py#L890) | Explanatory comments or spacing. |  |
| [B0077 · 892–912](../../../../tools/reference_fuzz.py#L892) | Callable definition: def make_error_packet(seed: int, document: dict\[str, Any\], error: BaseException) -&gt; dict\[str, Any\]: | calls build_sql, list, except, len; returns { · [reviewed contract](#b0077) |

## B0001

[Lines 1–36](../../../../tools/reference_fuzz.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
"""Seeded direct-CQ traces and an independent SQLite set-semantics oracle.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide seeded direct-CQ documents, an independent SQLite oracle and failure minimization for the property driver. |
| inputs / outputs | Imports stdlib only; defines six shapes, three scalar kinds and finite scalar domains, with no CLI or native execution at import. |
| invariants | SQL is generated independently of the production planner/tree/evaluator. Finite int/string/bool set semantics do not cover NULL/bag/date/decimal/all int64 boundaries or arbitrary CQ inputs. |
| ownership | Owns module registries/imported modules; each later document/SQLite result/CLI capture is ordinary Python memory, not native query-account charge. |
| failure | Import/syntax/OOM failure propagates; actual operational failures are represented by FuzzError subclasses. |
| cost | Fixed registry/import construction; randomized generation and native subprocess work occur only when called. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
SHAPES = (
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define SHAPES for the finite fuzz domain. |
| inputs / outputs | Six deterministic CQ layouts selected by seed modulo length. Read by shape/update generators; no mutation by normal callers. |
| invariants | Labels/domain membership bound test coverage, not full frontend admission or SQL semantics. |
| ownership | Module owns tuple/dict backing; scalar strings/ints/bools are immutable and reused in generated documents. |
| failure | Import allocation failures propagate; unsupported lookup fails at use site. |
| cost | Fixed small allocation; no row scan/native process here. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
SCALAR_TYPES = ("int64", "string", "bool")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define SCALAR_TYPES for the finite fuzz domain. |
| inputs / outputs | Ordered int64/string/bool scalar labels used by generation. Read by shape/update generators; no mutation by normal callers. |
| invariants | Labels/domain membership bound test coverage, not full frontend admission or SQL semantics. |
| ownership | Module owns tuple/dict backing; scalar strings/ints/bools are immutable and reused in generated documents. |
| failure | Import allocation failures propagate; unsupported lookup fails at use site. |
| cost | Fixed small allocation; no row scan/native process here. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
VALUE_DOMAIN = {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define VALUE_DOMAIN for the finite fuzz domain. |
| inputs / outputs | Small immutable scalar tuples: five ints, five strings and two bools. Read by shape/update generators; no mutation by normal callers. |
| invariants | Labels/domain membership bound test coverage, not full frontend admission or SQL semantics. |
| ownership | Module owns tuple/dict backing; scalar strings/ints/bools are immutable and reused in generated documents. |
| failure | Import allocation failures propagate; unsupported lookup fails at use site. |
| cost | Fixed small allocation; no row scan/native process here. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 37–42](../../../../tools/reference_fuzz.py#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class FuzzError(RuntimeError):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the explicit error category for generator, CLI, oracle and shrinker failures. |
| inputs / outputs | RuntimeError subclass declaration; callers construct with diagnostics and may chain original cause. |
| invariants | An exception category is not an accepted oracle result or partial-success marker. |
| ownership | Exception owns diagnostic arguments/cause references; module owns class. |
| failure | Thrown by operational helpers and normally caught by property driver; class declaration adds no handler. |
| cost | Fixed class construction at import; exception traceback/message allocation occurs only on failure. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
class Mismatch(FuzzError):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the first native-versus-SQLite mismatch and its diagnostic references. |
| inputs / outputs | FuzzError subclass with custom constructor retaining document, actual, expected, SQL and parameter fields. |
| invariants | Captured mutable graphs are references, not immutable/deep snapshots; driver must avoid altering them before packet creation. |
| ownership | Owns references to supplied graphs/text/parameters plus exception message; no deep-copy constructor. |
| failure | Represents a failing comparison; retained graphs remain until exception/packet references are released. |
| cost | Fixed field assignments in construction, but retaining references can keep complete input and both result graphs alive. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 43–57](../../../../tools/reference_fuzz.py#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def __init__(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a mismatch without copying potentially large input and oracle graphs. |
| inputs / outputs | Message/document/actual/expected/sql/parameters in; mutates newly constructed exception fields. |
| invariants | Does not resequence, normalize or validate stored graphs; diagnostic identity matches caller objects. |
| ownership | Aliases each supplied document/result/parameter object; only RuntimeError argument tuple/instance fields newly owned. |
| failure | Base-exception/OOM failure can interrupt construction; no IO/rollback. |
| cost | O(1) assignments after message construction; retained memory equals reachable aliased graphs, release depends on other owners. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 58–66](../../../../tools/reference_fuzz.py#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SqlPlan:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold independently generated SQL, positional parameters and declared output scalar types. |
| inputs / outputs | Frozen dataclass with statement:str, parameters:tuple and output_types:tuple; generated constructor/equality/repr apply. |
| invariants | Frozen prevents field reassignment, not arbitrary deep immutability; actual admitted parameter/type elements are immutable scalars/strings. |
| ownership | Retains supplied string/tuple objects; no deep copy or native plan/proof handle. |
| failure | Constructor type annotations are not runtime validation; malformed use fails in later SQL/oracle steps. |
| cost | Fixed dataclass field storage; repr/equality can traverse complete SQL/tuple contents, construction does not execute SQL. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
statement: str
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store SqlPlan.statement for the independent oracle. |
| inputs / outputs | Parameterized independently generated SQLite SQL text. Constructor stores supplied object reference. |
| invariants | Frozen dataclass prevents field reassignment; annotation does not enforce runtime type or deep immutability. |
| ownership | Retains immutable string/tuple backing for actual callers; no deep-copy or native handle. |
| failure | Bad supplied data is not rejected by this field declaration; later SQL/conversion fails. |
| cost | O(1) reference storage at construction; eventual repr/equality/release may traverse retained tuple elements/text. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [docs/code_review.md](../../../code_review.md) |

```text
parameters: tuple[Any, ...]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store SqlPlan.parameters for the independent oracle. |
| inputs / outputs | Ordered immutable tuple of scalar bind values; tuple construction belongs to build_sql. Constructor stores supplied object reference. |
| invariants | Frozen dataclass prevents field reassignment; annotation does not enforce runtime type or deep immutability. |
| ownership | Retains immutable string/tuple backing for actual callers; no deep-copy or native handle. |
| failure | Bad supplied data is not rejected by this field declaration; later SQL/conversion fails. |
| cost | O(1) reference storage at construction; eventual repr/equality/release may traverse retained tuple elements/text. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [docs/code_review.md](../../../code_review.md) |

```text
output_types: tuple[str, ...]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store SqlPlan.output_types for the independent oracle. |
| inputs / outputs | Ordered declared scalar labels used to reconstruct Python values after fetch. Constructor stores supplied object reference. |
| invariants | Frozen dataclass prevents field reassignment; annotation does not enforce runtime type or deep immutability. |
| ownership | Retains immutable string/tuple backing for actual callers; no deep-copy or native handle. |
| failure | Bad supplied data is not rejected by this field declaration; later SQL/conversion fails. |
| cost | O(1) reference storage at construction; eventual repr/equality/release may traverse retained tuple elements/text. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [docs/code_review.md](../../../code_review.md) |

## B0005

[Lines 67–74](../../../../tools/reference_fuzz.py#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def json_type(value: Any) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify the admitted generated scalar kinds with bool checked before int. |
| inputs / outputs | Scalar value in; bool/int64/string label out. |
| invariants | Python bool is an int subclass, so order preserves kind. Integers are not range-checked here; generation uses tiny fixed values. |
| ownership | Borrows scalar; returns module literal string. |
| failure | Unsupported values raise FuzzError with repr; malformed repr/OOM can propagate. |
| cost | Fixed isinstance checks; failure message repr can scale with arbitrary invalid value size. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0007

[Lines 77–79](../../../../tools/reference_fuzz.py#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def value_for(type_name: str, index: int) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a deterministic value from the fixed scalar domain modulo domain length. |
| inputs / outputs | Known type label and integer-like index in; existing immutable domain scalar out. |
| invariants | Finite domains are nonempty; modulo wraps negative/large indices. No sampling beyond declared domain. |
| ownership | Returns shared immutable scalar; no row/document allocation. |
| failure | Unknown type KeyError or invalid index/type arithmetic failure propagates. |
| cost | Dict lookup/modulo/tuple lookup, with index big-integer cost if unbounded. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0009

[Lines 82–83](../../../../tools/reference_fuzz.py#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def random_value(rng: random.Random, type_name: str) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Draw one value using the caller-owned seeded random generator. |
| inputs / outputs | random.Random and known scalar label in; shared immutable domain scalar out; advances RNG state. |
| invariants | Reproducibility depends on RNG state/seed and Python algorithm; no independent statistical replicate claim. |
| ownership | Borrows/mutates RNG and borrows domain scalar; no fresh owning row. |
| failure | Unknown type/invalid RNG failure propagates. |
| cost | Small fixed-domain random choice; RNG-state mutation only. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0011

[Lines 86–94](../../../../tools/reference_fuzz.py#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def unique_rows(rows: Iterable[list[Any]]) -> list[list[Any]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain first rows by type-sensitive JSON spelling without deep-copying them. |
| inputs / outputs | Iterable of row lists in; fresh first-occurrence row list out. |
| invariants | Canonical JSON keys distinguish True from1; order of first occurrence preserved. Does not mutate source rows. |
| ownership | Owns output list and seen-string set; retained rows alias original row objects. |
| failure | Serialization/type/OOM failure propagates; partial local result not published. |
| cost | O(total serialized row bytes) plus hash lookups; stores every unique JSON key and row reference. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0013

[Lines 97–98](../../../../tools/reference_fuzz.py#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def variable(name: str, type_name: str) -> dict[str, str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare one direct-CQ variable. |
| inputs / outputs | Name/type labels in; {name,type} dict out. |
| invariants | No uniqueness/type validation here; validator later enforces generated schema. |
| ownership | Owns tiny dict; immutable input strings retained. |
| failure | Allocation/type failure propagates before enclosing document is returned. |
| cost | Fixed small dict allocation/assignments; no native work or schema scan. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0015

[Lines 101–102](../../../../tools/reference_fuzz.py#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def column(name: str, type_name: str) -> dict[str, str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare one physical catalog column. |
| inputs / outputs | Name/type labels in; {name,type} dict out. |
| invariants | No arity/layout validation here; used by fixed shape constructors. |
| ownership | Owns tiny dict; immutable input strings retained. |
| failure | Allocation/type failure propagates before enclosing document is returned. |
| cost | Fixed small dict allocation/assignments; no native work or schema scan. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0017

[Lines 105–106](../../../../tools/reference_fuzz.py#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def atom(atom_id: str, table: str, terms: list[dict[str, Any]]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare one query atom occurrence. |
| inputs / outputs | Atom ID/table and terms list in; {id,table,terms} dict out. |
| invariants | Physical table and occurrence identity remain separate; terms are not copied. |
| ownership | Owns dict, aliases supplied mutable terms list. |
| failure | Allocation/type failure propagates before enclosing document is returned. |
| cost | Fixed small dict allocation/assignments; no native work or schema scan. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0019

[Lines 109–110](../../../../tools/reference_fuzz.py#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def var_term(name: str) -> dict[str, str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one named-variable term. |
| inputs / outputs | Variable name in; {var:name} dict out. |
| invariants | No binding check here; generated-document validator later checks declared/body/head bindings. |
| ownership | Owns dict and retains name. |
| failure | Allocation/type failure propagates before enclosing document is returned. |
| cost | Fixed small dict allocation/assignments; no native work or schema scan. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0021

[Lines 113–114](../../../../tools/reference_fuzz.py#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def ignore_term() -> dict[str, bool]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one physical column wildcard term. |
| inputs / outputs | No args; {ignore:True} dict out. |
| invariants | Ignored physical fields still affect support multiplicity; wildcard is not an output variable. |
| ownership | Owns fresh dict with singleton bool value. |
| failure | Allocation/type failure propagates before enclosing document is returned. |
| cost | Fixed small dict allocation/assignments; no native work or schema scan. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0023

[Lines 117–118](../../../../tools/reference_fuzz.py#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def const_term(value: Any) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one literal equality term. |
| inputs / outputs | Scalar in; {const:value} dict out. |
| invariants | No independent type/range admission here; downstream validates against column type. |
| ownership | Owns dict, retains supplied scalar/object without copying. |
| failure | Allocation/type failure propagates before enclosing document is returned. |
| cost | Fixed small dict allocation/assignments; no native work or schema scan. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0025

[Lines 121–233](../../../../tools/reference_fuzz.py#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def build_shape(shape: str, type_name: str) -> tuple[list[dict[str, Any]], dict[str, Any], list[dict[str, Any]]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one of six fixed CQ/catalog/initial-state layouts independently of production planning. |
| inputs / outputs | Known shape and admitted scalar label in; table declarations, query dict and initial table rows out. |
| invariants | Covers singleton projection, path, star, disconnected product, self-join support and repeated-variable/constant filter. Fixed narrow layouts are not a general query generator. |
| ownership | Owns nested dictionaries/lists; reused scalar values immutable; repeated-table atom terms and copied star rows follow explicit constructor ownership. |
| failure | Unknown shape raises FuzzError; unsupported type/structure/OOM failures propagate. |
| cost | Fixed small shapes/row counts, but allocated JSON graph/SQL-independent metadata contains all declared rows/terms. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0027

[Lines 236–281](../../../../tools/reference_fuzz.py#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def make_updates(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate deterministic insert/delete attempts while tracking current exact physical sets. |
| inputs / outputs | RNG, table declarations, initial rows and requested count in; ordered schema_version1 update records out. |
| invariants | Deletes existing rows with72% branch, duplicate inserts with20% branch, otherwise generated rows; sequence starts1 and no-op attempts remain explicit. |
| ownership | Owns membership sets, column map, event dicts and row lists; initial input graphs borrowed, not mutated. |
| failure | Malformed tables/types or OOM propagate; caller generate_case rejects negative count before entry. |
| cost | O(events×arity) generation plus repeated sorting of current table sets for reproducible choice; membership/current populations retained. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
def random_row(table_name: str) -> list[Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate one typed row from the captured table-column map. |
| inputs / outputs | Table name in; fresh scalar row list out; captured RNG advances. |
| invariants | Uses only fixed VALUE_DOMAIN kinds and current catalog arity; no input row aliasing. |
| ownership | Owns new list, borrows immutable chosen scalars and captured column metadata. |
| failure | Unknown table/type/RNG/OOM failure propagates. |
| cost | O(table arity) random choices and list storage. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0029

[Lines 284–300](../../../../tools/reference_fuzz.py#L284); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def generate_case(seed: int, update_count: int = 12) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble one seeded format1 set-semantics document with a finite physical update trace. |
| inputs / outputs | Seed and nonnegative update_count in; complete catalog/query/initial/updates dict out. |
| invariants | Seed selects shape/type by modular arithmetic and seeds random.Random; no arbitrary-query, bag or SQL parser dependence. |
| ownership | Owns constructed document and RNG, returned nested data retained by caller. |
| failure | Negative update_count raises FuzzError; construction/type/OOM errors propagate. |
| cost | Small fixed shape plus make_updates cost and O(trace bytes) owning document allocation. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0031

[Lines 303–305](../../../../tools/reference_fuzz.py#L303); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a false generator/oracle invariant with an explicit FuzzError. |
| inputs / outputs | Condition/message in; None on success, FuzzError otherwise. |
| invariants | Uses explicit raise rather than assert, so the property driver checks remain active under -O. |
| ownership | Condition/message borrowed; thrown exception retains diagnostic. |
| failure | Failure is immediate at caller phase; does not undo external CLI work. |
| cost | Fixed branch for admitted primitive conditions; failure exception allocation only. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0033

[Lines 308–379](../../../../tools/reference_fuzz.py#L308); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_generated_document(document: dict[str, Any]) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the independent generator's narrow direct-CQ and trace contract before oracle use. |
| inputs / outputs | Generated document in; None after checking version/set semantics, tables/columns/variables/atoms/head, initial rows and contiguous updates. |
| invariants | Checks bool/int/string kind, repeated bindings, no duplicate initial physical rows and known update ops; not a universal arbitrary frontend document validator or signed-int64 range checker. |
| ownership | Borrows document; owns declaration maps/sets and JSON row keys during checks. |
| failure | Explicit FuzzError on failed predicate; missing/ill-shaped fields may also raise ordinary Python errors; no source mutation. |
| cost | Scans complete catalog/query/initial/update graph and serializes rows for uniqueness; storage proportional to declaration and initial key counts. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0035

[Lines 382–383](../../../../tools/reference_fuzz.py#L382); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _quote(identifier: str) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote SQL identifiers for the independent SQLite translation. |
| inputs / outputs | Identifier string in; doubled-double-quote quoted identifier out. |
| invariants | Does not interpolate scalar values; build_sql parameters represent constants. |
| ownership | Owns replacement/quoted string; input unchanged. |
| failure | Type/OOM failure propagates. |
| cost | O(identifier characters) copy and result allocation. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0037

[Lines 386–389](../../../../tools/reference_fuzz.py#L386); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _to_sql_value(value: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt generated bools to SQLite integer storage while preserving other scalars. |
| inputs / outputs | Generated scalar in; int(bool) or original scalar out. |
| invariants | Output kind restoration uses declared output_types; SQLite integer representation alone is not Python bool authority. |
| ownership | Returns immutable scalar, no owning container or connection mutation. |
| failure | No explicit validation; unsupported objects pass through and may fail SQLite binding later. |
| cost | Fixed branch/conversion for admitted scalars. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0039

[Lines 392–431](../../../../tools/reference_fuzz.py#L392); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def build_sql(document: dict[str, Any]) -> SqlPlan:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate direct CQ occurrences/terms into independent parameterized SQL and output typing. |
| inputs / outputs | Admitted document in; SqlPlan containing statement, constant tuple and output-type tuple out. |
| invariants | Aliases each occurrence, adds repeated-variable/constant equalities, omits ignores; DISTINCT output or SELECT1 for nullary truth. Caller must validate document first; this function does not. |
| ownership | Owns SQL string/lists/maps then immutable parameter/type tuples; does not hold a native planner/tree object. |
| failure | FuzzError or malformed lookup/type/OOM errors propagate before SQLite execution. |
| cost | Visits all atom terms and output variables, constructs equality predicates/SQL text; map/list/string allocations proportional to query size. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0041

[Lines 434–441](../../../../tools/reference_fuzz.py#L434); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _decode_sql_value(value: Any, type_name: str) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore declared generated scalar kind after SQLite fetch. |
| inputs / outputs | SQLite value and known output label in; bool/int/string scalar out. |
| invariants | Expected type comes from independent CQ metadata; unsupported declared kind raises rather than silently coerces. |
| ownership | Owns converted scalar where conversion allocates; borrows source immutable values otherwise. |
| failure | Unsupported type FuzzError or conversion/OOM failure propagates. |
| cost | Fixed dispatch, integer/string conversion cost depends on value size. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0043

[Lines 444–445](../../../../tools/reference_fuzz.py#L444); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _sorted_json_rows(rows: Iterable[tuple[Any, ...]]) -> list[list[Any]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn the oracle's same-schema tuple set into deterministic JSON row lists. |
| inputs / outputs | Iterable of comparable homogeneous-schema row tuples in; sorted list of fresh row lists out. |
| invariants | Uses Python tuple order; row positions have fixed declared kinds in generated cases. |
| ownership | Owns sorted tuple-reference list and each copied row list; immutable scalars shared. |
| failure | Mixed incompatible comparison/type/OOM errors propagate. |
| cost | O(R log R) row comparisons plus O(R×arity) list copies. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0045

[Lines 448–536](../../../../tools/reference_fuzz.py#L448); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sqlite_reference(document: dict[str, Any]) -> tuple[dict[str, Any], SqlPlan]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay the generated physical set trace against a fresh independent SQLite database. |
| inputs / outputs | Validated narrow direct-CQ document in; full initial/epoch current+signed delta results and SqlPlan out. |
| invariants | Set membership suppresses duplicate inserts/absent deletes but preserves every input epoch; nullary result is {()} or empty. Connection closes in finally on both normal/error paths. |
| ownership | Owns in-memory SQL connection, Python physical sets, plan and all snapshot/delta JSON rows; no production evaluator import. |
| failure | SQLite/validation/conversion/OOM failures propagate after finally closes connection; no native session state changed. |
| cost | Full SQL query/fetchall after each physical attempt plus set differences and sorting; retains all epoch snapshots and transient SQL/join result memory. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
def evaluate() -> set[tuple[Any, ...]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fetch the current independent SQLite answer and restore declared scalar types. |
| inputs / outputs | Captures connection/SqlPlan; returns set of typed row tuples or nullary truth set. |
| invariants | Contradictory generated terms are handled through the SQL predicate; nullary output preserves truth, not witness multiplicity. |
| ownership | Borrows connection/plan; owns fetched SQL rows and converted tuple set. |
| failure | SQL/type/conversion/OOM errors escape enclosing try, whose finally closes connection. |
| cost | Full current SQL execution/fetchall and O(result×arity) conversion/dedup per evaluation. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0047

[Lines 539–545](../../../../tools/reference_fuzz.py#L539); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def json_equal(left: Any, right: Any) -> bool:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete result graphs by type-sensitive canonical JSON spelling. |
| inputs / outputs | Two JSON-compatible values in; Boolean sorted-key compact-serialization equality out. |
| invariants | Distinguishes True from1 and preserves array order; not tolerance/SQL coercion equality. |
| ownership | Owns both complete serialized strings while comparing; inputs unchanged. |
| failure | JSON/type/OOM errors propagate. |
| cost | O(total encoded bytes plus object-key sorting) time and two full serialized temporaries. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0049

[Lines 548–569](../../../../tools/reference_fuzz.py#L548); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def first_difference(actual: Any, expected: Any, path: str = "$") -> str | None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the first structural or scalar mismatch without Python numeric type erasure. |
| inputs / outputs | Actual/expected graphs and diagnostic path in; first difference text or None out. |
| invariants | Checks exact Python type before dict/list/value comparison, then sorted keys/list order; no tolerance or row reordering. |
| ownership | Borrows graphs; owns recursive path/error strings and sorted key lists. |
| failure | Incomparable arbitrary dict keys/recursion/OOM errors propagate; expected generated JSON keys are strings. |
| cost | Worst-case full graph traversal plus per-dict sorting and path-string copies; recursion stack proportional to graph depth. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0051

[Lines 572–606](../../../../tools/reference_fuzz.py#L572); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _invoke(executable: str, command: str, document: dict[str, Any]) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one native direct-CQ CLI operation with an isolated JSON input and bounded elapsed time. |
| inputs / outputs | Executable, mode and document in; parsed stdout JSON out after zero exit. |
| invariants | Temporary input is removed by context manager before contextual Timeout/OSError translation. Capture is UTF8 and timeout20s, without a captured-output byte cap. |
| ownership | Owns temporary directory/input bytes, completed subprocess stdout/stderr strings and parsed DOM; native child owns its separate memory. |
| failure | Timeout/OSError become chained FuzzError; nonzero includes both outputs, malformed stdout JSON becomes FuzzError; encoding/OOM may propagate. |
| cost | Serialize/write full document, spawn native process, capture entire output and parse full JSON; no native work/performance bound follows from20s timeout. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0053

[Lines 609–612](../../../../tools/reference_fuzz.py#L609); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_with_cli(executable: str, document: dict[str, Any]) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require native validate-cq to admit the generated set-semantics document. |
| inputs / outputs | Executable/document in; None after cq_valid true and semantics set checks. |
| invariants | Native validation is a separate admission check, not the independent result oracle or minimum-height proof. |
| ownership | Borrows document; owns invoked CLI response until check returns. |
| failure | _invoke failures or explicit FuzzError predicate failures escape. |
| cost | One temporary-input native subprocess plus full response capture/parse. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0055

[Lines 615–619](../../../../tools/reference_fuzz.py#L615); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def cli_reference(executable: str, document: dict[str, Any]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain the native oracle response while requiring its outer object shape. |
| inputs / outputs | Executable/document in; native oracle dict out. |
| invariants | Only outer dict shape checked here; compare_case performs complete independent equality afterward. |
| ownership | Returns owning parsed native response; document remains borrowed. |
| failure | _invoke failures/nonobject FuzzError escape. |
| cost | One native oracle subprocess, complete captured JSON parse; no separate incremental cost assertion. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0057

[Lines 622–632](../../../../tools/reference_fuzz.py#L622); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def compare_case(executable: str, document: dict[str, Any]) -> tuple[dict[str, Any], dict[str, Any], SqlPlan]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one native result graph to the independent SQLite result graph. |
| inputs / outputs | Executable/generated document in; actual/expected/SqlPlan on equality, Mismatch otherwise. |
| invariants | Runs local generator validation, native admission, native oracle, SQLite oracle, then exact first-difference; does not reuse production planner output to build SQL. |
| ownership | Owns both complete result graphs and plan; Mismatch retains references to these and document without copying. |
| failure | Validation/CLI/SQLite errors propagate; mismatch raises carrying first path and retained evidence. |
| cost | Two native subprocesses plus full SQLite replay, retained snapshots and full graph comparison; independent finite correctness test, not performance benchmark. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0059

[Lines 635–639](../../../../tools/reference_fuzz.py#L635); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def resequence(document: dict[str, Any]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy a document and renumber its update sequence contiguously from1. |
| inputs / outputs | Document in; independently mutable deep-copied document out. |
| invariants | Query/catalog/initial content retained by value; only update sequence fields change in returned copy. |
| ownership | Owns deepcopy of full graph; original untouched. |
| failure | Deepcopy/malformed update/type/OOM errors propagate. |
| cost | O(document reachable graph) copy plus O(updates) sequence writes; no native process. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0060

[Lines 640–642](../../../../tools/reference_fuzz.py#L640); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L640-L642:sha256:32b2d001ae215b0acec782cb59ff9a0532b704f9d7c3c447051a9d9158266a56
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: Deletion-local minimization can rerun native and SQLite oracles many times. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/code_review.md](../../../code_review.md) |

## B0061

[Lines 643–676](../../../../tools/reference_fuzz.py#L643); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _ddmin(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Minimize a list while preserving a caller-defined reproducing predicate. |
| inputs / outputs | Items, make_candidate(list)-&gt;document and preserves_failure(document) callbacks in; chunk-reduced then single-removal-fixed-point list out. |
| invariants | Returns a deletion-local minimum under this ordering/predicate, not a global minimal document or proof; callback may perform native+SQLite runs. |
| ownership | Owns candidate list slices/concatenations; item objects remain shared unless callback deep-copies. |
| failure | Callback exceptions propagate; nonreproducing candidates are rejected without replacing current list. |
| cost | Many predicate invocations, chunk/list copying and final repeated single-removal passes; no fixed polynomial total for arbitrary predicate behavior. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0063

[Lines 679–719](../../../../tools/reference_fuzz.py#L679); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def shrink_trace(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Minimize initial rows and updates while keeping query/catalog semantics fixed. |
| inputs / outputs | Document and preserves_failure callback in; deep-copied, resequenced reproducing document out. |
| invariants | Minimizes initial rows first, then updates; does not vary query/operators/values or guarantee joint/global minimality. |
| ownership | Owns working deep copies, flat row indices and candidate documents; caller original unchanged. |
| failure | Predicate/deepcopy/validation/OOM errors propagate; no persisted packet publication here. |
| cost | Repeated full-document deepcopy and _ddmin callbacks, potentially many native/oracle replays; peak includes current and candidate documents/results. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
def with_rows(keep: list[tuple[int, int]]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a resequenced candidate containing only selected initial-row positions. |
| inputs / outputs | Selected (initial-entry,row-index) pairs in; new complete candidate document out. |
| invariants | Captured current query/catalog/update contents stay fixed by deep copy; empty row groups remain as coded. |
| ownership | Owns full document clone and copied selected rows, then resequence makes another full clone. |
| failure | Index/deepcopy/OOM errors propagate to minimizer. |
| cost | O(full document+selected row bytes) copying per predicate candidate; temporary dual copies. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

```text
def with_updates(keep: list[int]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a resequenced candidate containing selected update records. |
| inputs / outputs | Selected update indices in; deep-copied candidate document with filtered updates and contiguous sequences out. |
| invariants | Captured minimized initial rows/query/catalog unchanged in value; original candidate records never renumbered in place. |
| ownership | Owns full clone, selected-index set and filtered list of cloned updates; resequence copies complete candidate again. |
| failure | Deepcopy/malformed update/OOM errors propagate. |
| cost | O(full document+all update indices) copying/filtering per attempted candidate, then full resequence copy and later predicate cost. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0065

[Lines 722–731](../../../../tools/reference_fuzz.py#L722); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def inject_duplicate_delta_fault(result: dict[str, Any]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a wrapper-only duplicate-delta negative control without altering native code. |
| inputs / outputs | Actual result graph in; deep clone with first nonempty added/removed row duplicated if found out. |
| invariants | Fault is in test wrapper output only; if no nonempty delta, returns unchanged-in-value clone. |
| ownership | Owns full cloned graph and copied injected row; actual input unchanged. |
| failure | Malformed graph/deepcopy/OOM errors propagate. |
| cost | Full deepcopy plus scan until first suitable epoch/delta; retains clone regardless of injection. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0067

[Lines 734–738](../../../../tools/reference_fuzz.py#L734); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def fault_is_observed(executable: str, document: dict[str, Any]) -> bool:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether the duplicate-delta wrapper fault differs from the independent oracle. |
| inputs / outputs | Executable/document in; bool exact graph inequality after injected native response out. |
| invariants | Exercises oracle sensitivity to one controlled transport mutation; no engine fault is injected. |
| ownership | Owns native and SQLite responses and full injected clone concurrently. |
| failure | CLI/SQLite/generation/OOM errors propagate rather than counting as observed fault. |
| cost | One native oracle, full SQLite replay, deep clone and whole JSON serialization comparison. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0069

[Lines 741–792](../../../../tools/reference_fuzz.py#L741); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def shrinker_fault_case(executable: str, seed: int = 0, update_count: int = 12) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Demonstrate wrapper-fault detection and one-update minimization for a singleton seed. |
| inputs / outputs | Executable, singleton-projection seed and update count in; minimized evidence packet out. |
| invariants | Adds focused physical insert, validates both sides, requires injected fault before/after shrinking and exactly one retained update. No universal shrinker minimality or engine bug claim. |
| ownership | Owns generated/minimized documents and deep-copied normalized query/trace; packet document field retains minimized document object. |
| failure | FuzzError for wrong shape/missed fault/non-one-event reduction; native/oracle/deepcopy errors propagate. |
| cost | Repeated native/SQLite predicates during minimization and final replay; full graph copies and retained packet snapshots. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0071

[Lines 795–860](../../../../tools/reference_fuzz.py#L795); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _invalid_variant(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mutate one generated document and require its native structured error code. |
| inputs / outputs | Executable/document plus sequence/type/operation variant and expected code in; None on expected nonzero coded rejection. |
| invariants | Requires an update to mutate; tests invalid_sequence/invalid_update/invalid_document. Does not require one specific nonzero exit or empty stdout. |
| ownership | Owns deep clone, temporary input, captured stdout/stderr and parsed error DOM; original untouched. |
| failure | Timeout/OSError become chained FuzzError; malformed stderr JSON/missing error fields are contextualized; wrong success/code explicitly fails. |
| cost | Full deepcopy/serialization, one20s-timeout native subprocess with unbounded captured output, error parse; temp cleanup via context manager. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0073

[Lines 863–867](../../../../tools/reference_fuzz.py#L863); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_invalid_variants(executable: str, document: dict[str, Any]) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all three focused generated-document rejection controls. |
| inputs / outputs | Executable/document in; integer3 after sequence/type/operation variants reject correctly. |
| invariants | Returned count names completed finite controls, not all invalid input coverage. |
| ownership | Document borrowed; each child helper owns an independent clone/capture. |
| failure | First variant failure aborts; no partial-success count returned. |
| cost | Three full clones and three native subprocesses sequentially, not concurrently retained. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0075

[Lines 870–889](../../../../tools/reference_fuzz.py#L870); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def make_failure_packet(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble reproducible mismatch metadata while making ownership limits explicit. |
| inputs / outputs | Seed/document/Mismatch in; evidence dict out. |
| invariants | Copies normalized query and trace, but document/actual/expected/SQL parameters retain original references. Packet is not a fully isolated immutable snapshot. |
| ownership | Owns result dict and deep query/trace clones; aliases document and mismatch graph/parameter fields. |
| failure | Malformed seed/document/deepcopy/OOM errors propagate during packet construction. |
| cost | O(query+initial+update graph) deep-copy work plus retained full original/both result graphs; later JSON writing costs full packet bytes. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0077

[Lines 892–912](../../../../tools/reference_fuzz.py#L892); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def make_error_packet(seed: int, document: dict[str, Any], error: BaseException) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve a noncomparison failure even when independent SQL construction is unavailable. |
| inputs / outputs | Seed/document/error in; evidence dict with SQL/parameters or None/\[\] fallback out. |
| invariants | Catches only FuzzError/KeyError/TypeError/IndexError from build_sql; diagnostic fallback is not acceptance of the document. |
| ownership | Owns deep query/trace copies and new parameter list; document field aliases original graph, error rendered to string. |
| failure | Other build_sql errors, str/deepcopy/OOM propagate; expected structure failures yield SQL missingness. |
| cost | Query traversal/SQL construction attempted once, full query/trace deep copies and error rendering; retains original document. |
| Design | [tools/reference_fuzz.py](../../../../tools/reference_fuzz.py), [docs/reference_fuzz.md](../../../reference_fuzz.md), [tests/property/reference_fuzz_test.py](../../../../tests/property/reference_fuzz_test.py), [schemas/cq-v1.schema.json](../../../../schemas/cq-v1.schema.json), [docs/code_review.md](../../../code_review.md) |
