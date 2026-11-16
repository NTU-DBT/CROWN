# Source and reuse map

| Target | Source | Object/binary provenance |
| --- | --- | --- |
| selection_public_independent | Original frozen tests/selection_public_independent_test.cpp | Reuse original strict-1 object, dependency record and binary |
| selection_cache_independent | Original frozen tests/selection_cache_independent_test.cpp | Reuse original strict-1 object, dependency record and binary |
| selection_resources_independent | Original frozen tests/selection_resources_independent_test.cpp | Reuse original strict-1 object, dependency record and binary |
| selection_binding_independent | This packet's tests/selection_binding_independent_test.cpp | New compile/link; one closing brace added |
| selection_publication_fault_independent | This packet's tests/selection_publication_fault_independent_test.cpp | New compile/link; common non-inline release and explicit replacement boundaries |

All use the unchanged shared fixture from the original frozen packet. No target
uses a private factory to manufacture proof, Evidence or Selection. The byte
driver's diagnostic raw records remain non-authoritative. Every numerical,
byte, scope, FIFO, lifetime, budget and failure assertion is preserved.

The two exact patches compare against the frozen original copies. Reused inputs
are listed with exact FILE identities in `REUSED_ARTIFACT_SHA256SUMS`. The root
strict-1 status/logs and root strict-3 implementation source/archive provenance
remain input FILEs, not successful independent runtime evidence. No native
destination, registration or status change is part of this revision.
