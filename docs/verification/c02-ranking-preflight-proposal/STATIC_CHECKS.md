# Preflight integrity and inspection limits

Date: 2026-11-07. Author scope: excluded C02 design only. All authored files are
inside `docs/verification/c02-ranking-preflight-proposal/`; no native source,
frozen C01 package, ledger, handoff, or matrix helper was edited.

## Input identities

| Artifact | SHA-256 |
| --- | --- |
| This packet's `INPUT_SHA256SUMS` (58 repository inputs) | `06476999071290bac59db3bbebea72ac3f12f24aed262a08ff0c4013dd4c5616` |
| This packet's `input-paths.txt` (58 paths) | `51e7c49e2c08b092d1cfe70057e6bc6db1af7520cbd8a31dee0834a291b25d22` |
| Frozen C01 native registration `PACKAGE_SHA256SUMS` | `3a8ad914fabffc307f21f645c099f657cb6ad4484a42e93c5de0c52fbc6d2c18` |
| Frozen C01 native registration `source-files.sha256` | `9b46c92287ac1ba58e96108095305e89a0f03b8d56ea1954503c75627e75cf99` |

The input manifest pins the actual current native files used for this design
and two predecessor manifest identities. It does not revalidate the historical
C01 package's pre-edit manifests against a now-applied native tree. The C01
131-test matrix was active at assignment; this packet does not inspect its
jobs or adopt an unobserved acceptance result.

## Performed checks

- Read the C02/Section 9.2 requirements and adjacent C03/C05/C07 boundaries.
- Inspected actual P06/P07 handles, full-binding/context gates, structural-key
  encoding, native-depth verification, physical/normalized source mapping,
  lowering layouts/index sharing, C01 owner/workload capture and interval rules,
  transactional root publication, and current archive direction.
- Inspected existing candidate fixtures/tests and independent oracle interfaces.
  Checked the literal depth and abstract slot calculations in WORKED_EXAMPLES.md
  by source inspection and hand arithmetic. These are design oracles, not runtime
  test results or a C02 correctness proof.
- Derived the exact wide-score bounds from admitted native count/size domains
  and the structural formulas. Chose a portable bounded-limb backend; checked
  the schoolbook carry and decimal-conversion intermediate bounds. These are
  mathematical design checks, not a compiled or executed arithmetic library.
- Generated input hashes from the explicit path list. Ran the following ordinary
  file-integrity command from the repository root; all 58 entries returned OK:

  ```sh
  sha256sum --strict -c docs/verification/c02-ranking-preflight-proposal/INPUT_SHA256SUMS
  ```

- Reviewed the packet for consistent current-only interval handling, explicit
  unavailable/fallback reasons, root-versus-detail saturation treatment,
  full-snapshot score publication, and honest family/memory/resource limits.
- Sealed nine packet files in `PACKAGE_SHA256SUMS`, excluding the manifest
  itself. The final freeze check verifies that manifest from this directory
  and rechecks the 58 input hashes from the repository root. Its manifest hash
  is reported with the handoff rather than embedded circularly in this file.

## Explicit limits

No C02 implementation, compiler invocation, executable, Python checker,
benchmark, CMake, CTest, or `nm` was run. No network, Git command, or child agent
was used. This is not native integration, independent implementation review,
test acceptance, a schema/import guarantee, or a finished C02 card.

The test plan deliberately requires future execution for typed admission,
freshness/lifecycle transitions under the single-writer contract, allocation failures, arithmetic
limits, live same-owner traces, and clean archive linking. No static inspection
can replace those checks. Likewise, matching a baseline score cannot establish
runtime optimality, calibrated event costs, regret, arrival Hz, allocator/peak
memory, or future plan deployment safety.

Before implementation, recheck input identities and reconcile any later native
documentation/API changes. Preserve this frozen preflight as historical design
evidence; revisions belong in a new explicitly identified packet.
