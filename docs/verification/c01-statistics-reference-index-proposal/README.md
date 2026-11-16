# C01 small-data reference revision

## Revision record

The original packet under `docs/verification/c01-statistics-reference-proposal/` is preserved. Root validation attempt 1 failed before semantic checks with `JSONDecodeError` at `fixtures.json` line 155, column 268: the decimal native derivation object lacked its closing brace before the derivation list ended. This revision fixes that syntax only; the prior numerical expectations remain unchanged. It adds explicit replay states and counters so the checker derives update denominators, no-ops, touched degrees, derivation counts, support changes, and crossings from the listed rows and events. Root's failed-attempt files remain at `build/verification/c01-statistics-literal-reference-attempt-1.{json,log}`.

The original packet inputs and their hashes are pinned in `pins.json`. The revision packet's validation command is listed below.

This packet records small, exact set and map calculations for the C01 acceptance work. It is independent of the C01 collector and O07 metrics. The expected counts below are derived from the literal rows, equality groups, joins, and positive-support maps in `fixtures.json`.

## Conventions

- A source table is a set of full physical rows. Its cardinality is the number of distinct full rows. A catalog table unused by the query still has a source population.
- A native population is the set of distinct tuples produced by an occurrence's native projection. Its derivation map counts accepted physical rows mapping to each native tuple. Derivations can change while native membership stays fixed.
- `S` is the set of surviving node tuples. A source or native row can exist while its tuple is absent from `S`.
- `P` and `E` are maps from their exact ordered projection keys to positive support counts. Every stored key has positive multiplicity. For each applicable map, `sum(multiplicities) == |S|`; a zero support is represented by a missing key, not a histogram bin.
- Ordered projection NDVs retain the requested field order. The empty projection has NDV 1 for a nonempty population and 0 for an empty population.
- A degree histogram counts each existing nonempty index bucket once. Its count is the number of keys, and the degree sum is the index membership count. The touched-degree event histogram counts each applied child-key event once, including a degree-zero event if one were present. The two histograms have different populations and weights.
- An empty positive-key histogram has key count and sum 0; its mean, minimum, maximum, and quantiles are unknown and are omitted. No empty histogram is invented for an index that does not exist.
- Top-K sorts by count descending, then by exact native key order ascending. These fixtures use single-type keys where that order is unambiguous: integers ascending and byte strings lexicographically by their exact bytes (a shorter prefix sorts first).
- `crossing_fraction` uses `(zero_to_positive + positive_to_zero) / support_count_changes`. A positive-to-positive change is in the denominator and not the numerator. A zero denominator has an unknown rate.
- Source insert/erase no-ops are committed physical inputs but do not route to occurrences. They remain separate from adapter rejections.
- A capture below `PhysicalRuntime` can report support state while source-table facts and the physical-input denominator are unavailable. Those are unavailable facts, not zero counts.

The JSON uses `{"bytes_hex":"..."}` for a string's exact bytes and `{"decimal":"..."}` for a canonical native decimal. `decimal_input` appears only in an input-attempt description to preserve the test spelling; it is parsed to the canonical decimal before row equality. No JSON `null` is used as a native value.

The revised checker reconstructs physical source sets from the baseline and replays each literal insert/erase. It derives no-op counts, occurrence routes, physical-input denominators, projection derivation maps, touched degrees from parent rows, and P/E support changes one S tuple at a time. It compares every listed post-input source/native/S/P/E state and the zero-crossing denominator. The weighting control also records and checks every intermediate child/S/P/E map.

## Fixture 1: native R root and S child

The query shape is `R(x,y), S(y)`, with native R as the root, S as the child, and head `(x,y)`. The physical R rows are `(1,7),(2,7),(3,8)`. The physical S rows move from `{7}` to `{7,8}` and then `{8}`. `Unused(w)={(99)}` is catalogued but unused by the query.

For R, source and native cardinality stay 3. The existing reverse index on R.y has keys `{7:2, 8:1}`, so its positive-key degree bins are `{1:1, 2:1}` and its key 7 is first at K=1. At baseline, only `(1,7),(2,7)` survive: `S` has 2 rows, P's empty key has support 2, and E has two full assignments with support 1 each. Inserting S(8) adds `(3,8)` to S: P changes `2→3` without crossing zero, and E adds one key (`0→1`). Deleting S(7) removes two rows: P changes `3→2→1` without a zero crossing, while E removes two keys (`1→0`). These update counts exclude initialization and are independently summarized in the JSON.

## Fixture 2: repeated derivations of one native tuple

Physical `R(x,z)` starts with `(7,10),(7,11)`. Its occurrence projects only `x`, so native tuple `(7)` has two derivations and S contains one tuple. Adding `(7,12)` changes source cardinality and the derivation count to 3, but does not change native or S membership. Reinserting `(7,12)` and erasing absent `(7,99)` are physical no-ops with no occurrence route. Deleting the three present rows in turn changes derivations `3→2→1→0`; only the last deletion removes native/S membership and the sole P/E key.

## Fixture 3: empty and nullary projections

The empty unary relation has NDV 0 for both `(x)` and `()`, with empty S/P/E populations. The empty nullary relation has cardinality 0 and empty-projection NDV 0. The one-row nullary relation `{()}` has cardinality 1, empty-projection NDV 1, and one positive P and E key of multiplicity 1.

The nullary rows are mathematical set fixtures under the preflight's empty-projection rule. They do not assert that every existing runtime constructor can build a zero-column relation or that a particular Boolean-output wrapper is in scope. No aggregate semantics are assigned.

## Fixture 4: tied heavy keys, byte strings, and decimals

The byte-string root has rows `("a",1),("a",2),("a\0",1),("a\0",2)`, encoded by bytes `61` and `6100`. Full source/native/S cardinality is 4. P groups by `k` and has two keys, each with support 2. Thus K=1 is the byte key `61`, K=2 is `61` then `6100`; the result is deterministic despite the tie. E has four full assignments of support 1, sorted by exact key order. The repeated byte value `61` groups exactly, while `61` and its NUL-extended value remain distinct.

The decimal source has rows `(7.0,1),(7.00,2)`. Canonical native decimal equality makes the projection NDV of `amount` equal 1; the full source rows remain distinct because `suffix` differs. A later insert of `(7.00,1)` is a duplicate full physical row after decimal parsing and leaves source cardinality and the native derivation count unchanged. Decimal zero, NULL, rounding, and SQL type coercion are outside this fixture.

## Weighting control and lower-only view

The packet includes an index weighting control with key degrees `{a:1,b:1,h:2}` and a nine-event trace `[+a,-a,+a,-a,+a,-a,+b,-b,+h]`. Positive-key weighting gives three observations with degree sum 4. Touched-event weighting gives nine observations with degree sum 10 (`1` occurs 8 times and `2` once). It demonstrates why a state degree distribution cannot be substituted for a workload event distribution.

The `lower_only_capture` record explicitly marks source table populations and the physical-input denominator unavailable. Its support maps are still exact for the stated state. This is a scope statement for the API design, not a claim that a particular C01 implementation exists.

## Unsupported scope

These fixtures do not define SQL NULL, aggregates, general SQL collation, fuzzy string equivalence, sketches, sampling guarantees, cost estimates, or runtime support for unrepresentable layouts. They do not invent indexes: only indexes named in the packet receive degree histograms. A table with no named existing index has `existing_indexes: []`, which is not an empty histogram for an index.

## Root validation

Run this standalone, standard-library-only reference replay from the repository root:

```sh
python3 docs/verification/c01-statistics-reference-index-proposal/reference_check.py
```

This revision checker was not run by the preparatory agent. Root owns execution and review; this packet remains reference evidence, not a C01 verification claim.

The three revised payload hashes and frozen original input hashes are in `pins.json`. `SHA256SUMS` covers the revision files, including `pins.json`; it does not hash itself.

## Explicit no-op crossing metadata revision

Root attempt 2 parsed and replayed the R/S fixture, then failed with KeyError
for `native_membership_crossing` on a duplicate insert in the projection
fixture. The absent erase omitted the same required expected field. Root
adds explicit false expectations for those two inputs, independently derived
from full-row set membership and native derivation counts before/after each
input. All old fixture values and checker assertions are preserved. The
semantic checker source is byte-identical to the prior revision; no assertion
is skipped or defaulted. Both earlier packets and attempt-1/2 artifacts are
preserved and pinned. This new packet has not yet passed root execution.

Root command: `python3 docs/verification/c01-statistics-reference-index-proposal/reference_check.py`.

## Explicit index-key projection metadata revision

Root attempt 3 completed the R/S, derivation and Decimal sections, then found
that the weighting control's already declared `Parent.k.reverse` index omitted
`key_fields`, required by its independent grouping check. This revision adds
`key_fields: ["k"]`, identifying the existing key projection over `(k,id)`.
No index, row, numerical expectation or checker assertion is changed. All prior
packets and failed attempts are preserved. At creation this package is frozen
for root execution; later root-result records carry its validation status.
