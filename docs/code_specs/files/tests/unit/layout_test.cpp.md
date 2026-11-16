# `tests/unit/layout_test.cpp` — block usage map

[Source](../../../../../tests/unit/layout_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ef7f8635516dca0a74583b68f02fd5eeb0aa1efd1e1ab1c586320be37d456897`. 108 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/layout_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../tests/unit/layout_test.cpp#L12) | Callable definition: void check(bool value,const std::string& message) | calls std::runtime_error; guard void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0002) |
| [B0003 · 13–16](../../../../../tests/unit/layout_test.cpp#L13) | Callable definition: void error(const std::function&lt;void()&gt;& action,std::string_view code) | calls void, action, check, code; guard try { action(); } catch (const Error& failure) { check(failure.code()==code,"wrong error: "+failure… · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../tests/unit/layout_test.cpp#L17) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 18–18](../../../../../tests/unit/layout_test.cpp#L18) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0005) |
| [B0006 · 19–53](../../../../../tests/unit/layout_test.cpp#L19) | Callable definition: void tuples_and_keys() | calls static_assert, tuple, n, s; guard static_assert(!std::is_convertible_v&lt;TableId,RelationId&gt; && !std::is_convertible_v&lt;OccurrenceId,Nod… · [reviewed contract](#b0006) |
| [B0007 · 54–79](../../../../../tests/unit/layout_test.cpp#L54) | Callable definition: void shared_keys_and_facts() | calls check, apply, tuple, n; guard check(l.apply(left.tuple({n(7),s("match")}))==r.apply(right.tuple({s("match"),n(9)})),"different re… · [reviewed contract](#b0007) |
| [B0008 · 80–94](../../../../../tests/unit/layout_test.cpp#L80) | Callable definition: void catalog_scope_and_width() | calls table_layout, check, context, origin; guard check(source.context().catalog_version==12 && source.origin()==LayoutOrigin{TableId{0},7},"physical…; growth push_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 95–95](../../../../../tests/unit/layout_test.cpp#L95) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 96–108](../../../../../tests/unit/layout_test.cpp#L96) | Callable definition: int main(int argc,char** argv) | calls std::string_view, projected_layout, io::write_layout, io::write_projection; guard check(argc==1,"usage: crown_layout_test \[--artifacts\]");; returns 0; 1 · [reviewed contract](#b0010) |

## B0001

[Lines 1–11](../../../../../tests/unit/layout_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:3cf7f7c63c7b41f2a7ab99c215fb94df63cbc872fe47b0a3c3f62c38e5b81680
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare layout_test.cpp: include "crown/storage/layout.hpp", "crown/io/layout.hpp", "crown/api/error.hpp", &lt;functional&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;type_traits&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/layout_test.cpp](../../../../../tests/unit/layout_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–12](../../../../../tests/unit/layout_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fails the layout test when a predicate is false. |
| inputs / outputs | Accepts bool and const message reference. |
| invariants | True returns normally; the message expression may be eagerly formed by caller. |
| ownership | No message retention. |
| failure | False throws std::runtime_error. |
| cost | One assertion branch only. |
| Design | [tests/unit/layout_test.cpp](../../../../../tests/unit/layout_test.cpp) |

## B0003

[Lines 13–16](../../../../../tests/unit/layout_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void error(const std::function<void()>& action,std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Asserts a callable throws a requested layout Error. |
| inputs / outputs | Accepts const std::function reference and code; invokes it and checks caught crown::Error.code(). |
| invariants | Only the code is compared; another Error code is not equivalent. |
| ownership | Callable and code view are borrowed during invocation. |
| failure | No expected Error or wrong code raises runtime_error; other exception types propagate. |
| cost | One invocation; does not count allocation attempts. |
| Design | [tests/unit/layout_test.cpp](../../../../../tests/unit/layout_test.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp) |

## B0004

[Lines 17–17](../../../../../tests/unit/layout_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Creates an integer Value for tuple fixtures. |
| inputs / outputs | Takes int64 by value and returns Value. |
| invariants | The helper uses the scalar constructor without type coercion. |
| ownership | Returned Value is owned by the caller. |
| failure | Construction errors propagate. |
| cost | One scalar creation. |
| Design | [tests/unit/layout_test.cpp](../../../../../tests/unit/layout_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0005

[Lines 18–18](../../../../../tests/unit/layout_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Creates a string Value for tuple fixtures. |
| inputs / outputs | Moves the supplied string into a returned Value. |
| invariants | String bytes are used as supplied. |
| ownership | Value owns the moved string after the local parameter ends. |
| failure | Allocation/construction failures propagate. |
| cost | One string scalar plus any owned bytes; ordinary fixture allocation. |
| Design | [tests/unit/layout_test.cpp](../../../../../tests/unit/layout_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0006

[Lines 19–53](../../../../../tests/unit/layout_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void tuples_and_keys()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks tuple layout tokens, typed slots, projection binding, and scalar row keys. |
| inputs / outputs | Builds typed source/projected/nullary layouts, tuples, hashes, and serialized layout/projection values, then tests read, bind, apply, copy, and move behavior. |
| invariants | Wire decode can preserve descriptor equality while creating a distinct TupleLayout runtime token; Projection::apply requires the input layout token. Projection context compatibility uses LayoutContext value equality, not layout-token identity. |
| ownership | Layouts/projections retain shared context handles; tuple values own scalar payloads; references are valid only while owners remain. |
| failure | Bad tokens, slots, tuple shapes, and invalid moved-from use produce CROWN Errors asserted by the helper. |
| cost | Finite small layouts and tuples, including one reordered/repeated projection; JSON and hash fixture allocations are ordinary. |
| Design | [tests/unit/layout_test.cpp](../../../../../tests/unit/layout_test.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0007

[Lines 54–79](../../../../../tests/unit/layout_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void shared_keys_and_facts()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercises shared layout facts, repeated variables, and decimal-domain projection. |
| inputs / outputs | Constructs query contexts and table layouts, then checks accepted/rejected key/projection combinations and decimal widening/narrowing. |
| invariants | Projection construction compares LayoutContext values; both source projections share the same target layout token for interoperable keys. Repeated target variables need the same source slot or a repeated source variable; decimal widening is exact and narrowing rejects. |
| ownership | Projection/layout handles retain context ownership; tuple values stay independently owned. |
| failure | Invalid repeated-value, anonymous/shared-scope, out-of-range, context, and narrowing cases throw checked Errors. |
| cost | Small explicit token and decimal cases; no asymptotic or allocation-free claim. |
| Design | [tests/unit/layout_test.cpp](../../../../../tests/unit/layout_test.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [include/crown/storage/layout.hpp](../../../../../include/crown/storage/layout.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0008

[Lines 80–94](../../../../../tests/unit/layout_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void catalog_scope_and_width()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks schema-version provenance and wide catalog-derived layouts. |
| inputs / outputs | Builds table and scope layouts from a catalog, verifies source schema version/origin and ordered repeated fields, then projects a 70-field scope in reverse. |
| invariants | Nullable source is rejected; field order and duplicates are preserved; width is not capped at a 64-bit slot mask. |
| ownership | Layout handles retain shared context metadata while catalog fixture is separately owned. |
| failure | Invalid nullable or out-of-scope field requests are rejected by checked constructors. |
| cost | One fixed 70-field layout/projection fixture; no performance measurement. |
| Design | [tests/unit/layout_test.cpp](../../../../../tests/unit/layout_test.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0009

[Lines 95–95](../../../../../tests/unit/layout_test.cpp#L95); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L95:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in layout_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/layout_test.cpp](../../../../../tests/unit/layout_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 96–108](../../../../../tests/unit/layout_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs layout assertions or exports two layout artifacts. |
| inputs / outputs | With --artifacts, writes layout and projection JSON; otherwise requires argc==1 and runs three groups. |
| invariants | Only the explicit argument forms are accepted; the three helpers cover tuple/key, shared-fact, and catalog-scope cases. |
| ownership | JSON output is written from local owned layouts; no state escapes. |
| failure | Unexpected arguments or helper exceptions are printed by the std::exception catch and return nonzero. |
| cost | Three finite fixture groups or two artifact serializations; no runtime resource claim. |
| Design | [tests/unit/layout_test.cpp](../../../../../tests/unit/layout_test.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [src/io/layout.cpp](../../../../../src/io/layout.cpp), [docs/physical_plans.md](../../../../physical_plans.md) |
