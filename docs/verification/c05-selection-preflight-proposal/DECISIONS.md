# Design decisions for root review

The following choices are concrete proposals, not claims that C05 has shipped.
They resolve source/API limitations explicitly instead of silently narrowing a
future implementation after tests are written.

1. **Compile-artifact cache after fresh ranking.** P07 keys erase representation
   and P08 binds raw tree/source IDs. The cache retains only an exact whole plan,
   never a proof/family/score decision. Each selection reruns full C02 admission
   and scoring. This sacrifices decision-cache speedup to make invalidation and
   typed authority auditable. It can save a height/depth winner lower; it does
   not save Q's per-candidate lowering. Root endorsed this separation in review.

2. **Explicit owned source.** A direct CQ needs only its snapshot binding and
   owned PhysicalOptions. Normalized SQL uses an existing immutable P08 basis,
   admitting its full source/program before C05. This incurs an explicit initial
   lower/replay before selection and is a real usability cost. It avoids treating
   a mutable NormalizedSql aggregate as a source-admission handle. A later
   convenience source factory may remove that awkward preliminary physical
   compilation only if it provides the same bounded replay/binding semantics;
   it is not assumed to exist now.

3. **Source equality is stricter than C02's core gate.** C02 can legitimately
   rank two different actual normalized programs that share a core CQ in their
   separate contexts. C05's explicit source requires full original source,
   predicate/parameter/output and options equivalence before using that Evidence.
   Existing owner/basis trees may differ. Artifact reuse separately requires
   the chosen exact raw tree. Full byte equality, not hashes, proves equality.

4. **C02 baseline only.** Default is required height, exact committed-input depth,
   then full structural key. Height-only and Q are explicit policies; C03 requests
   fail unsupported_model. Current P08 has one layout and sharing strategy, so
   the API names and preserves those and rejects unknown alternatives. Custom
   PhysicalOptions namespace labels are not calibration or a new backend.

5. **Unit-safe constraints.** A bounded canonical integer slot limit filters a
   complete Q assessment. Predicted allocator/live/peak byte constraints always
   fail honestly, including zero, rather than being compared to Q. Depth plus
   slots pays for two full C02 assessments and retains both. No fallback can
   bypass an unavailable mandatory constraint. This addresses the C05 memory
   acceptance condition through truthful failure where prediction is unsupported,
   not an invented S05 guarantee.

6. **Fresh means freshly captured from the actual owner.** The runtime bridge
   captures even for height-only and rejects private pending/released/mismatched
   boundaries. It offers no old-evidence/current-Boolean overload. Pure evidence
   stays as-of. The underlying owner is exclusive throughout the synchronous
   call, with no callbacks. C02 revalidate currently uses fixed internal defaults
   and returns no Usage; calling it would hide work from an aggregate budget,
   so this baseline uses the bounded capture API instead.

7. **Current interval only, per-policy availability.** Root input census,
   denominator and generation/protocol checks govern depth; exact physical
   source cardinalities govern Q. Sampling/truncated detail does not inherently
   invalidate exact roots. Disabled depth does not inherently invalidate Q.
   No-op commits are weights; abort diagnostics are not committed counts.
   Previous segments are never silently merged, and absent/saturated facts are
   never zero. Arrival Hz and plan-local P/E/degree observations are not used.

8. **One aggregate work contract.** Delegated rank requests use P+(L−U) and
   charge returned V−P, preserving preparation once. The four native work caps
   remain finite. The existing API copies finite size_t producer expression/
   recursion ceilings; C05 does not advertise an override it cannot enforce
   through rank. Timed as-of use exposes unmeasured prior preparation explicitly.
   The logical payload model and raw native capture/temp exclusions stay visible.

9. **Transactional explicit cache behavior.** Positive-capacity read-write
   admission failure is a selection resource failure, not a silent cache skip.
   Callers can choose bypass/read-only/disabled explicitly. New entry and final
   wrapper are prepared before a no-throw commit; failure preserves all cache
   counters/order and old handles. Read-only lookup can hit read-write entries:
   CacheUse and cache capacities govern effects/storage, not key identity.
   FIFO is deterministic and has bounded linear full-key comparisons.

10. **Coverage is retained-family coverage.** Exhaustion is exactly P07's declared
    seeds plus normal-form family, not all physical plans/global cost optimum.
    Provider timeout/cancellation history is not in CandidateSnapshot and will
    not be fabricated. Require-exhausted is explicit; default fully evaluates
    the retained prefix and reports that scope. Selection does not advance the
    provider or run an exact solver on behalf of the caller.

11. **No deployment or new proof transport.** Selection owns a compiled plan and
    current typed provenance; it does not open a runtime, switch a session,
    migrate data, reoptimize or publish an optimality flag. It keeps original
    certificate witness and PhysicalPlan's valid-upper-bound profile separate.
    C06 deployment and C03/C07 calibration/evaluation remain independent cards.

The main implementation risks are an omitted full-source key field, double-counted
or uncharged multi-assessment preparation, a late wrapper allocation after cache
commit, accidental token/ID transplantation, and unbounded hidden native work.
ACCEPTANCE.md gives targeted tests for each. The design is ready for review when
its input identities and packet manifest are frozen; no compile or runtime
success has been asserted for these proposed interfaces.
