# Evidence at this source-review freeze

All entries below are root-produced terminal records, read as immutable FILEs.
The review did not rerun their tools or historical input-entry checks. Exact
receipt and cited log hashes are in INPUT_SHA256SUMS. Later receipts must be
considered separately; this as-of document is not rewritten to absorb them.

| Record under build/verification | Observed result and scope |
| --- | --- |
| c05-selection-design-root-review-2026-11-07.json | Accepted design baseline; not implementation execution |
| c05-independent-strict-root-attempt-1.json | Public seven groups passed; original cache fixture failed; remaining consumers not run in that attempt |
| c05-independent-cache-diagnostic-root-attempt-1.json | Confirmed call 33 rejected unsupported arithmetic at lowering; unchanged diagnostic expectation exited 1 |
| c05-independent-cache-corrected-strict-root-attempt-1.json | Corrected cache consumer passed five groups, supported five/rejected one; stable guards |
| c05-independent-strict-root-remaining-attempt-1.json | Resources three, byte framing five, focused publication-failure two groups passed; stable guards |
| c05-producer-strict-root-attempt-1-smoke.json | Eight producer consumers passed with stable source guards |
| c05-producer-strict-root-attempt-1-faults.json | Two producer persistent-failure consumers passed with stable source guards |
| c05-selection-sanitize-root-checkpoint-1.json | Matching producer sanitizer closure: 19 fresh units, three archives, ten links; build-only evidence |
| c05-independent-sanitize-build-root-attempt-1.json | Five fresh matching sanitizer units/links, session 94093 closed, 801 source inputs and link inputs stable; explicitly runtime pending |

The selected strict independent lineage totals five consumers / 22 groups:
public 7, corrected cache 5, resources 3, bytes 5 and focused failures 2.
Recorded literal values are depth 195/105/190, slots 24/32/32, caps 23/24/31/32,
alias/unused input 10/7, Decimal/repeated head 13 and zero 0. Recorded byte checks
include five scalar types, 17 tree mutations, 38 core mutations and 79 normalized
byte mutations. The focused consumer observed 22 selected failure positions,
two publication failures and zero completed fault positions.

Producer strict persistent sweeps observed 32,966 direct positions and 20,420
normalized positions, with zero cleanup recoveries in both. Those complete
sweeps and the focused independent positions are different populations; their
counts are not added to manufacture a new exhaustive coverage claim.

Sanitizer runtime acceptance is not claimed by this packet. At the task handoff,
producer sanitizer execution remained live and independent execution had not
been accepted. The fixed build receipt explicitly says runtime acceptance is
pending. No live job was polled. Root may attach later terminal receipts without
changing this source-review package.

The active C02 native execution freeze is pinned only as a FILE identity and
context for delegated code. Current status prose, old source-manifest entries,
mutable progress records and the unfrozen C05 publication overlay are excluded.
This packet makes no native C05 verification or ledger claim.
