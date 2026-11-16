# Reopened C02/C05: nonempty constant-false replanning

Historical reproduction, 11 November 2026. The coordinated correction and scoped
reverification are recorded in [the 12 November repair](constant-route-repair-2026-11-12.md).

Root reproduced an existing native-plan defect while reviewing code. C02 and
C05 are reopened pending a coherent correction and fresh regression evidence.
The historical compiler matrices remain evidence for their frozen inputs;
they did not exercise this nonempty contradiction case. This is not caused by
the comment-only v7 edits.

## Reproduction

The probe uses `R(x:int64)`, body `R(x)`, head `x`, and `contradiction=true`.
Owned structural search and P07 produce a checked original candidate of native
height one. This authority concerns the retained body/tree problem.

Public lowering with the canonical empty tree produces a `constant_false`
operator with zero tree/runtime nodes and operator height zero. At this recorded checkpoint, native
`CompiledProgram::replan` retained that route, but freezes the original
candidate's one-node tree and height-one report. The runtime instruction vector
is empty. Export succeeds, while physical artifact replay fails with
`invalid_plan`: the public lowerer requires the canonical empty tree for the
constant-false route. The empty-body contradiction control roundtrips.

The executable result is in
[result.json](../../build/verification/inspection-v8-constant-route-probe-v1/result.json),
with [source](../../build/verification/inspection-v8-constant-route-probe-v1/probe.cpp)
and [link/compile provenance](../../build/verification/inspection-v8-constant-route-probe-v1/provenance.json).
It linked already sealed v6 libraries into a new probe directory; it did not
rebuild, retest or modify those libraries. Current v7 C++ changes have identical
executable tokens, and native IR implementation bodies are unchanged from v6.

## Required correction boundary

Preserve the public lowerer's refusal to silently discard an untrusted supplied
tree. Internal typed selection/replanning must explicitly choose the correct
constant operator representation. Preserve the original selected candidate,
proof, exact binding and required structural height separately; operator height
zero is not a new minimum-height proof for the retained body.

Compiler output, direct selection lowering, exact compiled binding, depth/slot
models and physical artifact replay must agree. Depth reporting must retain
the actual evidence denominator and zero table contributions. Slot ranking must
still perform eligibility, lowering, identity and payload checks. Reporting must
use constant-operator evidence without attaching an incompatible original body
proof to height zero. Empty-body optional tree claims and ordinary tree-route
behavior require explicit compatibility controls.

Independent design review is staged at
`build/verification/constant-route-design-v1`. No fix or new semantic acceptance
is claimed by this reproduction record. The full Refactor.md goal remains active.
