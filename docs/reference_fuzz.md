# Direct-CQ reference fuzzing

tests/property/reference_fuzz_test.py generates versioned direct-CQ documents,
validates each document through crown validate-cq, and compares the complete
crown oracle trace against a separate SQLite evaluator.

The generator chooses among singleton projection, two-edge path, star,
disconnected product, self-join with an ignored physical support column, and
repeated-variable/constant filters. A seed selects the shape and scalar type.
Generated values cover int64, string, and bool. The bounded driver checks
generator-owned schema, typing, binding, set-row uniqueness, and sequence
invariants separately from the CLI validation and semantic comparison.

The SQLite side builds SELECT DISTINCT directly from CQ atoms. It represents
each occurrence with a separate SQL alias, emits equality predicates for
repeated variables and joins, binds constants as SQL parameters, and omits
ignored physical columns from predicates and projection. It applies set
updates against its own in-memory row sets and re-runs the query before and
after each update to compute exact current answers and deltas. Boolean values
are stored as SQLite integers and decoded using the declared CQ output type.
Rows are sorted before comparison. JSON comparisons preserve array order and
distinguish booleans from integers.

## Run

    python3 tests/property/reference_fuzz_test.py ./build/debug/crown
    python3 -O tests/property/reference_fuzz_test.py ./build/debug/crown

The defaults run 12 seeds with 12 updates each. --seeds, --updates, and
--seed-start bound or shift the run. Documents with a sequence gap and an
update value of the wrong type must be rejected with the declared CLI error
codes, including an unsupported update operation.

The shrinker holds the CQ and catalog fixed. It removes chunks of initial rows
and update events without changing row or event values, then resequences every
candidate contiguously. It minimizes rows first and events second; the returned
trace is not guaranteed to be globally minimal across both dimensions. A
failing semantic comparison produces a packet with the seed, normalized CQ,
SQL, parameter values, full input, actual and expected outputs, and minimized
trace. CLI failures and timeouts also preserve seed, CQ, SQL, parameters, and
the original trace in a failure packet.
The test driver also wraps a clean CLI result with an injected duplicate-delta
fault. This fault exists only in the Python test wrapper; it checks that the
shrinker detects the corruption and reduces the seeded singleton trace to one
relevant update.

## Hand-fixture registry

This maps the separately hand-calculated regression documents to the closest
Section 13 query/update gates. The native oracle checks semantics only;
structural admission remains outside these fixtures.

| Fixture | Query/update shape | Related gate |
| --- | --- | --- |
| ancestor_child_deletion | R(x), S(x,y); delete the child row | U04 |
| boolean_query | Q():R(x); insert, duplicate insert, delete | Q03, Q11, U01 |
| contradiction | Contradictory CQ remains empty through updates | Q12 |
| disconnected_query | R(x), S(y); Cartesian output and deletion | Q11 |
| empty_body_true | Empty CQ returns one nullary tuple | A03, A04 |
| equal_scope_distinct_tables | Equal scopes from distinct relations | Q10 |
| projection_collision | Q(x):R(x,z); first/last hidden witness | Q02, U02, U06 |
| repeated_variable_constant_filters | R(x,x,"keep") with matching and rejected rows | Q12 |
| root_witness | Q(x):R(x); singleton insertion | Q01, U03 |
| self_join_cross_term | Two Edge aliases; one physical self-edge creates a tuple | Q13, U07 |
| singleton_insert_delete_noop | Q(x):R(x); insert, duplicate, absent delete, delete | Q01, U01, U09 |
| two_edge_path | Q(a,c):Edge(a,b),Edge(b,c) | Q07 semantic reference only |
| unused_column_projection_supports | Q(x):R(x,ignore); ignored-column support boundary | Q02, U08 |

## Scope

This is finite randomized evidence for the direct-CQ parser and slow reference
evaluator. It does not test a production planner, propagation algorithm,
generated SQL frontend, NULL semantics, bags, large integer boundaries, or
completeness over arbitrary CQ shapes. SQLite and the CLI share the declared
set-semantics contract, but use separate query execution implementations.
