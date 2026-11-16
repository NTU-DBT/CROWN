# Independent fixture lineage and authority

The author did not write the C05 selection implementation. The author previously
wrote the accepted C02 independent public/integer consumers, then reused their
literal row sets and human-derived three-tree/alias/Decimal expectations here.
The current native `tests/unit/ranking_public_independent_test.cpp` is therefore
prior work by this author, not an independent implementation of C05. Existing
C02 nullary/unary/constant tests supply a cross-check of already published
semantics: populated nullary Q4, unary Q14, empty Q0.

The frozen design manifest and root design-review receipt are input FILEs. The
producer's public headers and API checkpoint define call signatures, and its
separate BINDING/ACCOUNTING documents define versioned transport/resource
contracts. The byte oracle is a separate byte-vector algorithm and literal
record sequence; it never invokes production framing to construct expected
bytes. The unchanged P07 v2 header was read for its existing field order. Its
private encoder is not called by the oracle side.

Before reading C05 implementation bodies for source review, this packet retains
an authoring checkpoint containing the literal oracle, shared fixture and five
consumers. Public tests only use real factory-created P06/P07/P08/C02 artifacts.
The framing driver calls four private byte-only diagnostic endpoints. The
resource driver uses private Budget with neutral numeric Usage to test the
published preparation equation; that creates no Evidence or Selection. None
uses private Factory, SelectionData, raw cache Entry or fabricated proof data.

Certificate permutation is a public claim submitted to real CertificateReplay.
The checked result is required before a new CandidateProvider can use it. No
editable certificate or Boolean validation result is treated as authority.

The fault driver follows native allocation-harness conventions but uses separate
focused scenarios: a current depth selection that would evict the oldest of two
entries, and a warm current hit. It measures successful call allocation positions
with request/source construction outside the interval, then tests early/middle/
last-eight persistent-failure positions. It does not duplicate the producer's
complete sweeps or claim complete allocation coverage. Any completed fault
position is retained explicitly for root review; successful complete recovery is
not mislabeled as a failed transaction.

The author has not compiled, linked, run, syntax-checked or polled these sources.
No native, earlier frozen package, root helper/evidence, ledger or handoff bytes
were changed. Root alone produces execution evidence. Final source-review notes
must distinguish flaws discovered after these fixtures from fixture/API mistakes
and preserve both original and revised source checkpoints when needed.
