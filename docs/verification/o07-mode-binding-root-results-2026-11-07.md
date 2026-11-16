# O07 mode-binding root results — 2026-11-07

This is excluded standalone evidence, not native O07 acceptance. The root
executed the independent [mode-binding tests](o07-mode-binding-test-proposal/README.md)
against the complete matching nine-unit runtime archive. Attempt 3 passes all
seven scenario groups in 0.032 seconds. The dynamic bootstrap sweep covers all
16 observed allocation positions with persistent failure, two failed attempts
on the same owner, unchanged semantic/configuration state and successful
same-owner recovery: 32 actual injected bad_alloc requests.

The scenarios cover exact requested options versus resolved policy, current and
historical generations, direct/replay initialization, mode switches and failed
bootstrap, busy output, detached values, moves/rebuilt owners, generation maximum
and saturation, lower-only unbound summaries, off/counters/timed equivalence,
nonallocating reads and mutation hooks, optional clocks, and session drain/drop.
The Q(x)=R(x,y),S(y) fixture has two physical nodes but one C* factor: separator
y is not a head variable, so the S child is outside C*. Valid off fixtures use
legacy transition capture false; the invalid off-plus-capture combination remains
explicitly rejected. Enabled round-trip coverage retains legacy capture true.

The complete runtime and independent test were rebuilt with strict warnings,
ASan and UBSan; leak checking was enabled. All seven groups pass in 0.265
seconds, 68.244 seconds including compilation/linking. Session 14511 is terminal
and closed. All 57 pinned predecessors/native inputs and the three mode mirrors
remain unchanged. Raw logs and summaries are
`build/verification/o07-mode-binding-proposal-attempt-3*` and
`build/verification/o07-mode-binding-proposal-sanitize-*`.

Accepted source SHA-256:
`7771cd1bc0861dfd4ad1f4c63388697226c509d1c72002079047fa3207049f54`.
Ordinary linked test SHA-256:
`1d3c66e5ccea728fcc91f3a11fff1d8e8632a1cfd9fd9b6fd97d7a892f5e3a06`.
Complete mode runtime archive SHA-256:
`3a51a21032690940c3c7c83f05ddd56e275811f61955f2ed438f9487b7bcb2b9`.
Attempts 1/2 remain retained, unaccepted fixture/injector preparations. These
passes do not cover the later nontrivial run-context ABI, cursor observation,
report extensions or full native configuration matrix. O07 remains not started.
