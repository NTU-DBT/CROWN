# `tests/reference/residual_oracle.cpp` — block usage map

[Source](../../../../../tests/reference/residual_oracle.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `db5d99e6b6305990a3b1d4a7a1ba2ab3c9c21f2a1dd813a5e4448eaab92fd3b7`. 255 lines partitioned into 25 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/reference/residual_oracle.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 19–25](../../../../../tests/reference/residual_oracle.cpp#L19) | Callable definition: VariableSet scope_of(const Atom& atom) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 26–26](../../../../../tests/reference/residual_oracle.cpp#L26) | Explanatory comments or spacing. |  |
| [B0004 · 27–32](../../../../../tests/reference/residual_oracle.cpp#L27) | Callable definition: std::vector&lt;VariableSet&gt; scopes_of(const Query& query) | calls reserve, size, push_back, scope_of; returns scopes; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 33–33](../../../../../tests/reference/residual_oracle.cpp#L33) | Explanatory comments or spacing. |  |
| [B0006 · 34–42](../../../../../tests/reference/residual_oracle.cpp#L34) | Callable definition: VariableSet variables_of(const std::vector&lt;VariableSet&gt;& scopes, const std::vector&lt;std::size_t&gt;& members) | calls at, insert, begin, end; returns result; growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 43–43](../../../../../tests/reference/residual_oracle.cpp#L43) | Explanatory comments or spacing. |  |
| [B0008 · 44–50](../../../../../tests/reference/residual_oracle.cpp#L44) | Callable definition: VariableSet head_of(const Query& query, const VariableSet& variables) | calls contains, insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 51–51](../../../../../tests/reference/residual_oracle.cpp#L51) | Explanatory comments or spacing. |  |
| [B0010 · 52–57](../../../../../tests/reference/residual_oracle.cpp#L52) | Callable definition: VariableSet intersection(const VariableSet& left, const VariableSet& right) | calls std::set_intersection, begin, end, std::inserter; returns result · [reviewed contract](#b0010) |
| [B0011 · 58–58](../../../../../tests/reference/residual_oracle.cpp#L58) | Explanatory comments or spacing. |  |
| [B0012 · 59–64](../../../../../tests/reference/residual_oracle.cpp#L59) | Callable definition: VariableSet difference(const VariableSet& left, const VariableSet& right) | calls std::set_difference, begin, end, std::inserter; returns result · [reviewed contract](#b0012) |
| [B0013 · 65–65](../../../../../tests/reference/residual_oracle.cpp#L65) | Explanatory comments or spacing. |  |
| [B0014 · 66–68](../../../../../tests/reference/residual_oracle.cpp#L66) | Callable definition: bool subset_of(const VariableSet& subset, const VariableSet& superset) | calls std::includes, begin, end; returns std::includes(superset.begin(), superset.end(), subset.begin(), subset.end()) · [reviewed contract](#b0014) |
| [B0015 · 69–69](../../../../../tests/reference/residual_oracle.cpp#L69) | Explanatory comments or spacing. |  |
| [B0016 · 70–72](../../../../../tests/reference/residual_oracle.cpp#L70) | Callable definition: bool proper_subset_of(const VariableSet& subset, const VariableSet& superset) | calls size, subset_of; returns subset.size() &lt; superset.size() && subset_of(subset, superset) · [reviewed contract](#b0016) |
| [B0017 · 73–73](../../../../../tests/reference/residual_oracle.cpp#L73) | Explanatory comments or spacing. |  |
| [B0018 · 74–83](../../../../../tests/reference/residual_oracle.cpp#L74) | Callable definition: bool disjoint(const VariableSet& left, const VariableSet& right) | calls begin, end; returns false; true; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 84–84](../../../../../tests/reference/residual_oracle.cpp#L84) | Explanatory comments or spacing. |  |
| [B0020 · 85–114](../../../../../tests/reference/residual_oracle.cpp#L85) | Callable definition: bool is_q_hierarchical(const std::vector&lt;VariableSet&gt;& scopes, const std::vector&lt;std::size_t&gt;& members, const VariableSet& free) | calls variables_of, reserve, size, at; returns false; false; growth emplace_back, insert, reserve; 4 loop sites · [reviewed contract](#b0020) |
| [B0021 · 115–115](../../../../../tests/reference/residual_oracle.cpp#L115) | Explanatory comments or spacing. |  |
| [B0022 · 116–151](../../../../../tests/reference/residual_oracle.cpp#L116) | Callable definition: ResidualView make_terminal_view(const Query& original, const std::vector&lt;std::size_t&gt;& members, const std::vector&lt;VariableSet&gt;& s… | calls resize, size, at, variables_of; returns view; growth push_back, reserve, resize; 5 loop sites · [reviewed contract](#b0022) |
| [B0023 · 152–154](../../../../../tests/reference/residual_oracle.cpp#L152) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0023) |
| [B0024 · 155–253](../../../../../tests/reference/residual_oracle.cpp#L155) | Callable definition: planner::ResidualTraceRecord frozen_residual_trace(const Query& query) | calls scopes_of, live, size, variables_of; returns value.occurrence != ear.occurrence && remaining.contains(value.occurrence); result; growth insert, push_back; 9 loop sites · [reviewed contract](#b0024) |
| [B0025 · 254–255](../../../../../tests/reference/residual_oracle.cpp#L254) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::reference · [reviewed contract](#b0025) |

## B0001

[Lines 1–18](../../../../../tests/reference/residual_oracle.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:56c81acae45c0d283bbdd2ed6fba64a0e5e15ca063b9f9be4cb8b04ffb22fb88
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare residual_oracle.cpp: include "residual_oracle.hpp", &lt;algorithm&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;set&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–25](../../../../../tests/reference/residual_oracle.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet scope_of(const Atom& atom)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract an atom’s variable scope. |
| inputs / outputs | Reads one Atom and returns its distinct VariableId terms as a VariableSet. |
| invariants | Constants and ignored terms are omitted; repeated variables collapse in the set. |
| ownership | Returns a fresh set; the Atom is borrowed for the call. |
| failure | No domain rejection; set allocation can fail. |
| cost | Linear in the term count plus ordered-set insertion cost. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0004

[Lines 27–32](../../../../../tests/reference/residual_oracle.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<VariableSet> scopes_of(const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one variable scope per query occurrence. |
| inputs / outputs | Reads Query.atoms and returns a vector aligned to occurrence order. |
| invariants | Every result entry is scope_of for the corresponding atom; repeated occurrences remain separate entries. |
| ownership | The returned vector and sets are owned; Query is borrowed. |
| failure | Allocation may fail; no query validation is performed here. |
| cost | One pass over atoms and their terms. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0006

[Lines 34–42](../../../../../tests/reference/residual_oracle.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet variables_of(const std::vector<VariableSet>& scopes, const std::vector<std::size_t>& members)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Union scopes for the selected occurrence indices. |
| inputs / outputs | Reads a scope vector and member indices; returns the union set. |
| invariants | Occurrence lookup uses scopes.at, so invalid indices throw; repeated members do not duplicate variables. |
| ownership | Returns an owned VariableSet; inputs are borrowed. |
| failure | Out-of-range member indices raise std::out_of_range; allocation may fail. |
| cost | Visits each selected scope and inserts each variable into an ordered set. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0008

[Lines 44–50](../../../../../tests/reference/residual_oracle.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet head_of(const Query& query, const VariableSet& variables)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intersect query outputs with variables present in a selected residual. |
| inputs / outputs | Reads Query.head and the residual variable set; returns distinct present output variables. |
| invariants | Aliases and repeated head slots do not duplicate membership; output order is set order. |
| ownership | Returns a fresh set and borrows Query and variables. |
| failure | No semantic rejection; allocation may fail. |
| cost | Scans the ordered head list and inserts matches. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0010

[Lines 52–57](../../../../../tests/reference/residual_oracle.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet intersection(const VariableSet& left, const VariableSet& right)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the intersection of two ordered variable sets. |
| inputs / outputs | Reads two VariableSet values and returns their common members. |
| invariants | Both inputs use ordered-set iteration; duplicates are impossible by type. |
| ownership | Returns a new set; inputs are borrowed. |
| failure | No domain error; result allocation may fail. |
| cost | Linear merge over both set sizes. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0012

[Lines 59–64](../../../../../tests/reference/residual_oracle.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet difference(const VariableSet& left, const VariableSet& right)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Subtract the right variable set from the left. |
| inputs / outputs | Reads two ordered VariableSet values and returns left minus right. |
| invariants | The result contains only members of left absent from right. |
| ownership | Returns an owned set and borrows both inputs. |
| failure | No domain error; allocation may fail. |
| cost | Linear ordered-set difference. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0014

[Lines 66–68](../../../../../tests/reference/residual_oracle.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool subset_of(const VariableSet& subset, const VariableSet& superset)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether one ordered variable set is contained in another. |
| inputs / outputs | Returns whether every member of subset is present in superset. |
| invariants | std::includes is called with superset first, matching its required ordering. |
| ownership | No result storage; both sets are borrowed. |
| failure | No domain error. |
| cost | Linear in the two ordered-set sizes. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0016

[Lines 70–72](../../../../../tests/reference/residual_oracle.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool proper_subset_of(const VariableSet& subset, const VariableSet& superset)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test strict set inclusion for ordered variable sets. |
| inputs / outputs | Returns true only when subset is smaller and included in superset. |
| invariants | Equal sets are not a proper subset; subset_of performs the membership test. |
| ownership | No result storage; inputs are borrowed. |
| failure | No domain error. |
| cost | Size comparison plus the ordered inclusion scan when sizes permit. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0018

[Lines 74–83](../../../../../tests/reference/residual_oracle.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool disjoint(const VariableSet& left, const VariableSet& right)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether two ordered variable sets share no member. |
| inputs / outputs | Returns false on the first common value, otherwise true. |
| invariants | Two iterators advance monotonically; neither set is modified. |
| ownership | No result storage; inputs are borrowed. |
| failure | No domain error. |
| cost | Linear two-pointer scan, with early exit at a shared value. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0020

[Lines 85–114](../../../../../tests/reference/residual_oracle.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool is_q_hierarchical(const std::vector<VariableSet>& scopes, const std::vector<std::size_t>& members, const VariableSet& free)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check q-hierarchical incidence conditions for the selected residual. |
| inputs / outputs | Reads all scopes, selected occurrence IDs, and free variables; returns a Boolean. |
| invariants | Each variable’s incidence is the set of selected occurrences containing it; pairs must be nested or disjoint, and a free variable with a proper-subset incidence requires the larger-incidence variable to be free. |
| ownership | Incidence sets and vectors are local owned temporaries; input scopes and free set are borrowed. |
| failure | Invalid occurrence IDs propagate std::out_of_range from variables_of/scopes.at; allocation may fail. |
| cost | Builds incidences then checks every variable pair; this reference check is quadratic in distinct residual variables, with set comparisons inside each pair. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0022

[Lines 116–151](../../../../../tests/reference/residual_oracle.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualView make_terminal_view(const Query& original, const std::vector<std::size_t>& members, const std::vector<VariableSet>& scopes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a terminal residual Query view and dense local-ID maps. |
| inputs / outputs | Reads the original Query, selected occurrence IDs, and precomputed scopes; returns a ResidualView with original/local occurrence and variable maps plus a remapped Query. |
| invariants | Selected occurrences preserve input order; variables are ordered by VariableSet; constants, ignored terms, contradiction, aliases, and present output order are copied through. |
| ownership | The returned view owns copied Query data and optional mapping vectors; original Query and scopes are borrowed. |
| failure | Invalid indices can throw through at(); an output variable absent from the selected residual leaves an empty mapping and is omitted. |
| cost | Scans selected scopes, copies selected atoms and remaps their variable terms; allocates maps sized to the original occurrence and variable counts. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0023

[Lines 152–154](../../../../../tests/reference/residual_oracle.cpp#L152); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L152-L154:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in residual_oracle.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 155–253](../../../../../tests/reference/residual_oracle.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::ResidualTraceRecord frozen_residual_trace(const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce a deterministic frozen residual-trace record for one Query. |
| inputs / outputs | Reads Query and returns original scopes, round layers, ear/anchor conditions, deletion pairs, terminal classification, and a terminal dense view. |
| invariants | It has no initial validate_query or limits. Each layer freezes unique variables and both eligible anchor conditions before greedy deletions; later deletions do not discover new ears within that layer. Terminal IDs are remapped only in terminal_view. |
| ownership | The returned trace owns copied vectors, sets, records, and terminal Query data; input Query is borrowed. |
| failure | Invalid internal indices propagate at()/vector errors; allocation failures propagate. The helper does not convert malformed queries to a status. |
| cost | For each round it builds incidence and pairwise q-hierarchical checks, examines ear/anchor pairs, then greedily removes from the frozen list. The helper has no internal size cap or work meter; finite callers supply their own fixtures. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp) |

## B0025

[Lines 254–255](../../../../../tests/reference/residual_oracle.cpp#L254); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L254-L255:sha256:eb4a6d7eca0fbb1ee325a62b521f86ac21994585cdfc1ad5076d9f90286d82dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in residual_oracle.cpp: namespace crown::reference. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/residual_oracle.cpp](../../../../../tests/reference/residual_oracle.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |
