# Decision 0008: grounded equality admission with honest stage results

F06 connects the existing frontend and structural recognizer and reports
seven explicit outcomes. Admission checks normalized equality-CQ semantics
and H/H+F shape. Physical lowering, strict minimum-height certification and
runtime installation remain separate. No partial recognition class survives
work exhaustion. Legacy unbounded recognition commands retain their behavior.

Integration found a concrete constant-normalization completeness gap:
`SELECT DISTINCT r.a,s.c FROM r JOIN s ON r.b=s.b WHERE r.a=1` retained `a`
as a free core variable in format 1. The resulting endpoint head failed
free-connex recognition, although the grounded CQ `Q(1,c):R(1,b),S(b,c)` has
H={{b},{b,c}}, F={c}. Data semantics were correct; its shape was unnecessarily
restrictive.

Normalized format 2 propagates each final equality-class constant to explicit
guards on every participating occurrence/column, removes fixed variables
from core projections/scopes and maps fixed output positions to constants.
All mutable atoms survive, including zero-column projections. Per-occurrence
support counts still retain complete physical row identity. Typed parameters
participate only after specialization; OR/NOT predicates do not form
unconditional equality facts. This does not introduce general predicate
implication, function-dependency simplification or relation elimination.

The normal producer now emits version 2. Format-1 replay remains frozen,
including work counters and IDs. `upgrade-normalized` explicitly migrates
1→2; all downgrades reject. Admission upgrades validated v1 input before
recognition with an independent host cap. Both version-1 compatibility
fixtures are retained. Geometry may change on upgrade, so regenerate and
revalidate plans/certificates for the new core even when SQL answers agree.

Contradictions have an explicit constant-empty admission route. Recognition
still records the actual normalized body/head shape, including a cyclic body.
The native free-connex route requires both GYO reductions to complete acyclic.
Plain row-producing bags, nullable source columns and unsupported SQL features
remain rejected; whole-result EXISTS retains its separate scalar wrapper.

The [admission contract](../sql_admission.md), v1 admission/v2 normalization
schemas and SQL matrix record these decisions. The
[verification packet](../verification/admission-2026-11-05.md) records the completed
F06 matrix and finite evidence; the full task ledger remains active.
