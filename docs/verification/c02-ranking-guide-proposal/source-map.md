# Source map for the C02 usage guide

The guide describes draft declarations only. Header identity pins are in
`input-pins.sha256`; compile commands and outputs are in `compile-evidence.md`.

| Guide subject | Existing source | Use and limit |
| --- | --- | --- |
| Ranking request/result | [draft ranking header](../c02-baseline-ranking-proposal/overlay/include/crown/planner/ranking.hpp) | Supplies `Policy`, `Fallback`, `Request`, `Evidence`, `Result`, `Attempt`, `rank`, and the draft result accessors. This proposal header is not accepted native API. |
| Current owner evidence | [draft runtime evidence header](../c02-baseline-ranking-proposal/overlay/include/crown/runtime/ranking_evidence.hpp) | Supplies `CaptureOptions`, owning `RuntimeEvidence`, `capture`, policy-specific `Revalidation`, `revalidate`, and synchronous `rank_current` declarations. |
| Typed retained candidates | [P07 candidate header](../../../include/crown/planner/candidates.hpp) | `CandidateSnapshot` is factory-owned and exposes its original proof, retained members, and `family_exhausted()` state. The guide starts after this snapshot exists; it shows no proof-search/provider loop. |
| Actual owner types | [physical runtime header](../../../include/crown/runtime/physical.hpp), [C01 combined statistics header](../../../include/crown/runtime/combined_statistics.hpp), [C01 statistics guide](../../../docs/statistics.md) | Physical owner and existing C01 capture semantics. The guide does not change collection mode or reset counters. |
| Draft preparation and time accounting | `docs/verification/c02-baseline-ranking-proposal/overlay/src/runtime/ranking_evidence.cpp`, `overlay/src/planner/ranking.cpp`, `overlay/src/planner/ranking_detail.hpp` | Source-grounded explanation for carrying `Usage.active_nanoseconds` from capture preparation into rank accounting. These proposed sources are pinned for context, not compiled or executed in this task. |
| Required height and evidence limits | [C02 design contract](../c02-ranking-preflight-proposal/CONTRACT.md), [C02 source map](../c02-ranking-preflight-proposal/SOURCE_MAP.md), [C01 requirements](../../../Refactor.md) | Explains proof authority, current-vs-as-of evidence, full retained-prefix evaluation, per-policy usability, and proxy exclusions. These are preparation sources, not accepted implementation claims. |

The ranking result retains the original P07 snapshot and required-height proof;
its selected alternative is not a replacement proof. A complete score over a
provider's retained prefix is not a claim that the provider exhausted the
candidate family. Statistical evidence is validated against the actual owner
when current use is requested; immutable earlier results remain historical.
