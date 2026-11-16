# Exact bounded score arithmetic

This is the concrete proposed arithmetic contract for C02. It adds no native
code or dependency. The chosen backend is portable base-2^32 unsigned limbs,
using existing standard fixed-width integer types. Source inspection found no
Boost reference in current CMake/include/src/test targets and no requested
Boost header in `third_party`, `/usr/include`, `/usr/local/include`, or `/opt`.
No claim about a system-wide package inventory or external dependency is needed.

## Supported domain and sufficient width

P07's `candidates.cpp` already statically requires eight-bit bytes and
`numeric_limits<size_t>::digits <= numeric_limits<uint64_t>::digits`. Native
IDs and tuple/projection widths are size_t; source cardinalities and physical
root counts are uint64. C02 preserves those existing domain assumptions.

Let U=2^64-1, m be the query occurrence count, h the admitted native height,
q the candidate's number of selected relation objects, i its number of unique
index requirements, and k the largest selected layout/key width. Then m,h,q,i,k
are at most U, and h<=m. An eligible native C01 denominator satisfies 0<W<=U.

```
N = sum_(r,o) w(r,o) * sum_(a:base(a)=r) depth(a)
  <= W * m * h
  <= U^3
  < 2^192
```

For the memory bounds, define F(v) as the first native nodes encountered below
v, including v itself when v is native. P02 requires a tree, so generalized
children's frontiers are disjoint. Native bound R_v<=U; for a generalized node,
R_v<=sum(child P)<=sum(child R)<=|F(v)|*U. Projecting to P/E or retaining survivors
cannot increase that bound. Therefore every modeled population bound is
at most m*U<2^128. This remains true for arbitrary admitted unary generalized
seeds: another union over one child does not replicate a frontier.

There are q+i selected relation/index terms, each bounded by m*U*(k+1):

```
Q <= (q+i) * m * U * (k+1)
  <= (2*U) * U * U * (U+1)
  < 2^257
```

The counts q and i are individually bounded by their actual owning vector
sizes; q+i is computed wide. Width+1 is also wide. This proof is about current
typed domains and the precise nonnegative formulas in CONTRACT.md, not about
the ranker's smaller default candidate/work limits. It covers valid inputs
whose derived values exceed 64 or 128 bits. Changed formulas or wider input
types require a new bound and policy/arithmetic version.

Default storage and `max_score_bits` are 512. V1 accepts a lower explicit cap
from 1 through 512; it accepts no unbounded cap. The default cannot overflow
on admitted current-format score calculations. A lower cap can return
`score_bit_limit`, which is a resource outcome, not statistical unavailability.
Crossing it produces no ranking and never activates height-only fallback.
If the default representation overflows on admitted inputs, report an internal
invariant failure; never publish a saturated/wrapped score.

## Representation and operations

The private representation uses 16 uint32 limbs, least significant first, plus
a normalized used-length. Zero has used-length zero and canonical text `0`.
Unused limbs are zero; public code cannot create malformed or negative values.
Promote uint64 and admitted size_t operands before any arithmetic. Never add
widths, depths, occurrence counts, or source-count products in size_t/uint64
and then convert the already-overflowed result.

Required operations are conversion, exact addition/multiplication, minimum
with 1, unsigned comparison, actual bit length, and canonical decimal output.
No general division, signed arithmetic, decimal input-value operation, or
floating-point conversion is needed for ranking. N/W ordering uses shared W
and compares N. The normalized representation determines numeric comparison;
decimal strings are presentation, not lexical numeric sort keys.

Use a separate fixed scratch result. Addition needs at most 17 limbs;
multiplication uses 32 limbs and standard schoolbook accumulation. With
B=2^32, one multiply stage fits uint64 exactly:

```
(B-1)*(B-1) + (B-1) + (B-1) = B^2-1
```

The terms are the limb product, existing destination limb, and carry. Carry
propagation must process all required scratch limbs. Retain the full result
before checking its actual bit length: a conservative sum of operand bit
lengths is insufficient to reject a borderline value. Examples such as
`1*1` with cap 1 and `2^k*1` with cap k+1 must succeed. Zero multiplication
and adding zero remain exact; budget charges are still explicit.

Only after work reservation, complete arithmetic, normalization, and the bit
cap check succeed may the destination be replaced. Failure leaves both
operands and any previously published result unchanged, including aliasing
cases where destination equals an operand. No allocation is needed for the
limb/scratch arrays. Their finite fixed storage is documented separately from
the ranker's result vectors/strings and is not an S05 peak-memory claim.

Canonical decimal output repeatedly divides a private scratch copy by 10,
processing limbs from most significant to least. With remainder<10,
`remainder*B+limb <= 10*B-1`, which fits uint64. At most 155 digits represent
a 512-bit unsigned value. Reserve/check the finite digit/payload budget before
publishing a string. On allocation or work failure no truncated string is a
score. Output has only ASCII digits, no sign, separators, exponent, locale,
or leading zero except zero itself. Any future JSON ranking artifact must
carry wide integer values as these exact strings, not rounded JSON consumer
numbers. No reader/import or existing-report schema change is promised here.

Charge a finite conservative limb-operation allowance before each indivisible
operation, and charge digit production/copies too. Multiplication is at most
16*16 limb product stages plus bounded carry/normalization scans; addition and
comparison inspect at most a fixed number of limbs. Decimal conversion uses
at most 155 passes over 16 limbs. Publish the arithmetic/accounting version and
consumed work. This bounds logical processing without pretending one helper
call or one large integer is constant-size uncharged work. A stop during a
ranking attempt does not leak a partial minimum or partial score record.

## Evidence saturation remains different

Wide integers preserve exact facts; they cannot recover the true value of an
observed saturated C01 root. Keep `input_share`'s exact positive denominator
gate and all root-health checks from CONTRACT.md. A raw value equal to U is
usable only when its native availability is exact. An unavailable/capped C01
denominator remains unavailable in this policy. The arithmetic backend does
not reinterpret lower bounds as exact or introduce a wider-denominator policy.

## Boundary and fault test obligations

- Compare against a separate decimal-digit arithmetic oracle for source roots
  0, 1, U-1, U, products above 64/128/192 bits, and slot terms with 65-bit
  width-plus-one. Verify the derived 257-bit memory envelope independently.
- Exercise carries/borrows as applicable to the chosen addition/conversion
  algorithm at every 32-bit limb boundary, maximum limbs, zero, multiplication
  by 0/1, equal values, and values with the same high limbs but differing low
  limbs. No subtraction is required by the score contract.
- Test lower caps at exact result bit length and one bit below, especially
  borderline operands whose summed bit lengths overestimate the product.
  Test operation work limits and decimal-string allocation failures with
  destinations aliased and unaliased. Operands/old result remain unchanged.
- Confirm a statistical ranking using an exact >U product completes under the
  default cap; the same request with a deliberately too-small cap returns no
  selection even when height-only fallback is configured.
- Preserve the zero/no-op commit scope, missing/saturated root distinctions,
  alias multiplicity, and complete structural-key tie-breaks. Arithmetic width
  must not alter proof/admission or evidence eligibility.

These are design obligations, not completed tests. Root will execute the later
implementation's strict/sanitized consumers after a separately frozen proposal.
