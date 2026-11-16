# Exact annotation policies

W01 defines arithmetic and capability admission used by W02–W06.
The public interface is `crown/annotations/policy.hpp`, linked through
`CROWN::core`. Arithmetic alone does not enable bag SELECT, aggregate SQL,
transactions or weighted recovery. [W02 messages](weighted_messages.md) add a
separate exact multiplicity runtime; [W03 factors/cursors](weighted_enumeration.md)
provide direct-CQ logical projected counts. Existing structural physical
plans still require `exact-nonnull-v1` and retain their exact-set identities.

## Support and payload

`Multiplicity` is an exact nonnegative `uint64` count. Its zero/nonzero boundary
defines presence. `IntegerPayload` and `DecimalPayload` are separate signed
numeric types; their zero says nothing about row/group existence.
`Annotation<Payload>` stores both support and payload. For example, two contributions
of +7 and -7 leave support two and SUM zero: the group remains present.

`ValueChange` retains complete before/after values. It separately reports
membership appearance/disappearance, any support-count change, and any payload
change. A count change from two to three does not create a membership event;
a replacement from +7 to +9 can change the payload without changing support.
This interface does not coalesce physical epochs or prescribe weighted message
propagation. W02 must propagate numerical changes as well as zero crossings.

## Arithmetic domains

| Policy | Representation | Operations and limits |
| --- | --- | --- |
| `checked-uint64-multiplicity-v1` | `uint64`, optional positive maximum | Exact addition/product, checked removal, replacement; no negative multiplicities |
| `checked-int64-payload-v1` | `int64` | Exact signed addition/product/removal/replacement and multiplication by a full unsigned multiplicity |
| `checked-fixed-decimal-payload-v1` | existing canonical `Decimal` plus explicit `DecimalSpec{p,s}` | `1 <= p <= 38`, `0 <= s <= p`; every operand and final result must fit the declared fixed scale and precision |

Decimal arithmetic aligns scales exactly. Multiplication adds operand scales,
then removes only insignificant fractional zeroes. A result requiring rounding,
more fractional digits than `s`, or too many integer digits is an error. There
is no epsilon, binary floating-point conversion, implicit widening, truncation,
saturation, or wrapping. Zero fits `DECIMAL(p,p)` and remains canonical positive
scale-zero. No division/AVG rounding policy is admitted by W01.

Signed/decimal temporary arithmetic uses bounded stack digits (80 slots). Two
38-digit coefficients aligned to scales 0..38 need at most76 digits; a product
needs at most76, and a three-term replacement needs at most77. Only the final
canonical `Decimal` owns an ordinary scalar string. The policy layer is not a
native query-account allocation claim: W02 must account any retained weighted
state and arithmetic/output allocation when it integrates these operations.

Arithmetic on the finite domains is partial: capabilities describe the exact
underlying arithmetic when the operation succeeds, not closure beyond the
declared range. Each operation takes immutable inputs and returns a new value.
Failures use `Error` codes `annotation_overflow`, `annotation_underflow`, or
`invalid_annotation`; allocation failure may also propagate from Decimal/error
construction. Inputs remain unchanged.

## Deletion and replacement

Removal of a multiplicity verifies that the removed contribution does not
exceed the current total. Signed payload removal is exact subtraction. A caller
must retain the actual old contribution; a numeric sum alone cannot establish
which row was deleted. Boolean support has no arithmetic retraction: knowing
`true OR true` does not let a caller recover the remainder from a Boolean value.
Its admitted deletion strategy is replacement from separately maintained
witness/support state, as the existing set runtime does.

All replacements compute `total - old + next` in exact scratch arithmetic and
check the final result. For example, replacing -1 with -1 at INT64_MAX is a
valid no-op even though `INT64_MAX - (-1)` cannot be stored in int64. Decimal
replacement follows the same rule. Nonnegative counts retract first, then add;
all supplied operands must be in the configured count domain.

`replace_contribution` prepares support and payload together. Absent
contributions require zero payload; removing the last support must leave zero
payload. It returns a new value only after all checks pass. The caller publishes
it at its own transaction barrier. This is local preparation, not W06 ancestor
rollback or aggregate transaction implementation. It does not verify that an
old row is actually contained in a group; the owning state must establish that
provenance before using the arithmetic operation.

SQL global-empty aggregation is a separate W04 output rule. An ordinary group
with support zero is absent; a global COUNT must later expose a zero row and a
global SUM/AVG a NULL row. W01 does not synthesize those SQL outputs or use a
nonzero payload as a presence surrogate.

## Closed capability admission

`admit(Request, Backend)` returns an explicit status and capabilities for the
closed built-in domains. Capabilities distinguish exactness, zero-sum-free
addition, absence of zero divisors, additive cancellation, exact retraction,
replacement and representation cost. Here additive cancellation means
`a+c=b+c => a=b`; it does not mean that a nonempty SQL group cannot sum to zero.
Nonnegative multiplicities are zero-sum-free, while signed integer/decimal
payloads are not. Neither makes an arbitrary payload a valid multiplicity.

The arithmetic-policy route admits the implemented exact kernels and explicit
valid decimal specifications. General semirings, approximation, unknown enum
values, inappropriate decimal specifications and unsupported deletion modes
fail closed. Callers cannot supply algebra traits to grant themselves a backend
certificate. In particular, a generic type with `add` and `multiply` is not
admission authority; zero divisors, cancellation and deletion need a separate
audited implementation.

The certified set-tree route accepts only Boolean support with the existing
set policy. Exact multiplicity and signed/decimal kernels cannot select it.
Actual query-identity and physical-options readers use the same gate, so both
reference and indexed physical lowering reject their policy names with
`invalid_policy`. The explicit weighted-subtree route admits only implemented
nonnegative multiplicities; signed/decimal payload kernels do not gain that
backend. Its runtime uses a separate weighted binding/profile over the checked
structural plan. Kernel availability alone confers no maintenance, enumeration,
delay or space bound; the weighted cards verify their own execution contracts.

## Verification

W01 is verified as a component. New CTest controls are
`annotation_policy`, `annotation_admission` and `annotation_arithmetic_oracle`.
The arithmetic oracle uses Python unbounded integers and exact fractions,
independently checks declared precision/scale, and compares each result/error
with the C++ policies. The admission control exercises actual reference/indexed
lowering, canonical identity and physical-options reads. Existing scalar,
frontend, physical-plan and identity controls remain separate regressions.

All 27 selected GCC Debug checks pass in 271.23 seconds; all 33 fresh source-only
GCC Release checks pass in 327.44 seconds; all 14 Clang Release checks pass in
329.82 seconds; nine ASan/UBSan/leak checks pass in 665.61 seconds. Four moved
installed-package workflows pass in 58.42 seconds, plus a separate strict Clang
consumer using only moved installed annotation headers/library. Each arithmetic
oracle checks 15,588 cases with Python unbounded integers and exact fractions.
The broader review fixes and their limits are in the
[human examination guide](code_review.md).

The [acceptance audit](../build/verification/w01-review-acceptance-v1.json)
binds 15 requirements, 1,750 frozen source paths, 1,082 matching code inputs,
143 top-level native archives/executables, 696 actual C++ compilation records,
ten final receipts and raw logs. All 302 predecessor test commands/properties
and install declarations are preserved; 308 tests are registered. This is scoped
acceptance, not a full 308 execution or release. The complete Refactor.md goal
remains active. Later W02/W03 evidence is linked above and does not enlarge this
dated W01 acceptance scope.
