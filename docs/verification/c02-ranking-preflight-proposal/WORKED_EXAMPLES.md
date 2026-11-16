# Hand-checkable score examples

These are proposed test oracles computed from the definitions in CONTRACT.md.
They are not executed C02 results. Existing fixture bytes are pinned by the
input manifest. A later test must obtain actual P06/P07 typed handles, not turn
these numbers or tree names into proof authority.

## Equal-height hot-relation reversal

Use `tests/candidates/queries/boolean_rst.cq.json`: R(x), S(x,y), T(y), Boolean
head. Existing trees are `boolean_rst_native_s_root.tree.json`,
`boolean_rst_generalized_x_root.tree.json`, and
`boolean_rst_generalized_y_root.tree.json`. The current P07 tests independently
compare this three-member family and replay replacement witnesses. Their
native depth vectors are directly visible in the fixture trees:

| Tree | R depth | S depth | T depth | Native height |
| --- | ---: | ---: | ---: | ---: |
| Native S root | 2 | 1 | 2 | 2 |
| Generalized x root | 1 | 1 | 2 | 2 |
| Generalized y root | 2 | 1 | 1 | 2 |

The later test must assert the independently verified optimum is 2 and that
these are the actual three retained structural keys before asserting the full
ranking. Do not assume enumeration order identifies a tree.

With committed insert-plus-erase input counts R=90, S=5, T=5, W=100:

| Tree | N | Exact score |
| --- | ---: | --- |
| Native S root | 90*2 + 5*1 + 5*2 = 195 | 195/100 |
| Generalized x root | 90*1 + 5*1 + 5*2 = 105 | 105/100 |
| Generalized y root | 90*2 + 5*1 + 5*1 = 190 | 190/100 |

Swap R and T's counts: native S remains 195; generalized x becomes 190;
generalized y becomes 105. Required height and query semantics remain unchanged.
The statistical ranker changes only the preferred candidate handle.

A concrete executable-test trace can initialize one row in each source, enable
collection, and issue 90 duplicate inserts to R plus 5 to each other table.
Every event is a successful no-op commit. The physical input census changes and
all three query results remain unchanged. Reset at the quiescent boundary and
mirror the hot table for the second interval. Add a separate changed-row trace
with independently counted successful insert/erase events so the acceptance
test is not limited to no-op behavior. Current-only rules forbid combining the
two reset intervals.

## Aliases and irrelevant physical tables

Suppose one physical table A supplies two actual occurrences with native depths
1 and 2 in a certified candidate, and B supplies one occurrence at depth 2.
Record A inserts=3, A erases=2, B inserts=1, B erases=1. Then:

```
D(A)=1+2=3; D(B)=2
W=3+2+1+1=7
N=(3+2)*3+(1+1)*2=19
score=19/7
```

Do not use W=12 by counting A twice. If two additional commits target an unused
source table C, W=9 and N=19; the ordering across this fixed candidate family
is unchanged. If an attempted A update fails admission or rolls back, it does
not alter either W or N. A committed no-op does. The test must derive occurrence
routes from the real lowered/normalized plan, not these symbolic letters.

## Nullary and empty-tuple slot behavior

For a valid one-native-node nullary Boolean query, records/S/P/E all have empty
layouts. With a nonempty physical source, every projected population bound is
1, not source cardinality. The root has a visible empty assignment and no
indexes. Its proxy is Q=1+1+1+1=4. With an exactly empty physical source, Q=0.
This checks that a zero-field tuple is not treated as zero memory slots.

For a one-native-node unary Boolean query and source count n=3, the lowered
records and survivors each have width 1; root P and visible E have width 0.
No index is required. Thus R=S=3, P=E=1 and
Q=3*(1+1)+3*(1+1)+1+1=14. With n=0, all four bounds are zero. Actual runtime
metadata and variable payload bytes are outside this proxy.

## Candidate-local slot ordering for the R/S/T fixtures

For positive source counts r, s, t in the Boolean R/S/T query, only the root is
in the visible connex subtree: every outgoing separator contains a hidden
variable. The native-S tree has two reverse indexes on S.records, by x and y.
The generalized-x tree has one reverse index on S.records, by y; generalized-y
has one by x. The lowerer must independently confirm those facts in the test.

The CONTRACT.md formula yields:

```
Q(native S root)    = 6*r + 10*s + 6*t + 2
Q(generalized x)    = 10*r + 14*s + 6*t + 2
Q(generalized y)    = 6*r + 14*s + 10*t + 2
```

For r=s=t=1, those are 24, 32, and 32. Memory proxy therefore prefers native S,
while the hot-R depth example prefers generalized x. This is intentional:
the policies ask different questions and never silently add their units.

Derivation for generalized x: R/S/T relation terms are `6*r`, `8*s`, `6*t`;
S's single index contributes `2*s`. The generalized root has record bound
r+s, two width-1 relations contributing `4*(r+s)`, and its nullary P/E each
contribute 1. Summing gives `10*r+14*s+6*t+2`. A generalized record bound r+s
is a union bound; it is not an assertion that the actual source x keys are
disjoint. Zero counts require the explicit `P(n,0)` formula, not the positive-
count shorthand above.

## Arithmetic and availability edges

- `w = UINT64_MAX`, depth 1, and no other inputs yields an exact numerator and
  denominator of `UINT64_MAX` only if native root availability remains exact.
  The same weight at depth 2 yields the exact numerator
  `36893488147419103230`, not an unavailable score or a wrapped zero. A caller's
  explicit 64-bit score cap would cause a resource stop with no fallback; the
  default 512-bit cap handles it normally.
- With exact source n=`UINT64_MAX` in the unary Boolean memory example,
  Q=`4*n+2`=`73786976294838206462`. A source count's 64-bit representation does
  not restrict this valid derived slot value to 64 bits.
- Two individually exact roots whose sum exceeds `UINT64_MAX` have no usable
  shared denominator. Do not divide their saturated sum.
- A period-64 collector with zero complete detail samples can still provide
  exact positive physical roots. Weighted depth is eligible; sample event-cost
  means remain unavailable and are unused.
- A pending capture or a rotated current interval with W=0 cannot borrow the
  last segment's weights. Explicit fallback, if requested, is height-only over
  the complete retained snapshot.

The independent arithmetic oracle in future tests should use a different
representation/algorithm (for example a tiny decimal-digit integer reference
in test code) and compare configured bit-limit status as well as values. Test
carry propagation across all limb boundaries and values above 64/128/192 bits.
It must not call
the production score helpers to calculate expected results.
