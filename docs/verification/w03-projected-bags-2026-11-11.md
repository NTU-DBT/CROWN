# W03 projected multiplicities and inspection contracts

W03 implements compressed projected bags for checked direct-CQ logical weight
replacements. The full Refactor.md implementation remains active. This component
does not admit SQL bags, physical bag-source updates, SUM/AVG or weighted recovery;
those retain their W04–W06 contracts. No release or measured speedup is claimed.

The [factor specification](../weighted_enumeration.md) defines the full-row local
contribution and visible-key sum, proves the component factorization and gives
the caller protocol. An enumerated child's weight enters its own cursor factor
once. Hidden outside children enter their parent's local contribution instead.
Corrected [P1 v2 §7.3, equations 10–14](https://arxiv.org/pdf/2301.04003v2) supplies
the projected-annotation context; the bounded arithmetic, native ownership,
atomic inverse and cost contracts are explicit local engineering rules.

## Implementation and cost boundaries

Maintenance remains in weighted.cpp. A small private header shares owner/state
declarations with weighted_cursor.cpp; it introduces no registry, allocator,
runtime framework or extra owner. Full messages and visible sums have distinct
maps and inspection records, with one common exact replacement operation.
Numeric edits save inline scalars and one child slot. Detached map nodes fund
erasure rollback; diagnostic child-array images are opt-in.

One immutable flat outside-child list avoids rescanning enumerated siblings
during local-factor computation. Positive inside-child numeric changes reuse
the row's cached contribution. Full subtree products retain their documented
child-arity cost. The cursor uses compiled live/bucket traversal, C* frames and
ordered-head scratch; it stores no result history or hidden witness relation.
Each output is an owning tuple with an exact multiplicity, including values
above 2^53. Expanded logical size is the sum of counts.

The single caller may interleave readers. Every writer, including no-ops, waits
until readers close. Startup publishes a reader only after preparation succeeds;
failure releases borrowed frames before the runtime owner. One native grant and
cumulative cursor budget span all next calls. Close visits every allocated frame;
destroying the last runtime owner can additionally release all maintained state.
These are actual cost mechanisms, not a constant-delay or Boolean update bound.

The two metric helpers now use cumulative charging to prove both total and
category additions fit. Each managed category begins at zero and is a subset of
work, so a second category overflow guard was redundant. The stage rollback and
cursor cleanup catches remain necessary, each with one clear failure boundary.

## Executed validation

| Configuration | Selected checks | CTest elapsed |
| --- | ---: | ---: |
| GCC Debug | 8 passed | 9.86 s |
| GCC Release | 8 passed | 4.25 s |
| Clang 18 Release | 8 passed | 4.36 s |
| ASan + UBSan, leak detection | 8 passed | 40.67 s |

Each configuration checks 2,910 states against an independent unbounded-integer
projected oracle and 1,516 states against the full-subtree oracle. Raw duplicate
bags are folded to logical weights at the test boundary. The oracle enumerates
complete native assignments, not incremental message/factor caches.

Cases cover the mandatory 60-versus-720 double-counting example, hidden sums,
nested generalized scopes, a sole output root, disconnected/empty scopes,
96-node hidden and visible chains, repeated head fields, typed strings/dates/
booleans/decimals, exact large counts and empty/constant routes. Arithmetic
failure in a later stage reverses earlier factor changes.

Every configuration executes 1,108 update-allocation cuts and 26 cursor-allocation
cuts across both storage backends. Failed updates and successful retries are
checked against factor and projected-bag references as well as subtree state.
Cursor cuts cover startup, first output and later backtracking. Exact/one-under
work, requested-byte heap and native-grant tests include 4,096 compressed outputs.
Owning rows, reader moves, facade destruction, cancellation and bounded churn
are exercised. Existing set result-cursor and annotation-admission checks pass.

A relocated installed SDK consumer links only CROWN::runtime through installed
headers. It independently checks the counted path, ordered/repeated output,
precision, new query ownership, reader exclusion, terminal metadata, output/
cursor lifetimes and both normalized-SQL constructor rejections. A separate
translation unit includes weighted.hpp alone. All 15 installed CROWN archives
match the final Clang build. The testing runtime also compiles.

All 311 predecessor test commands/properties and install declarations are
preserved; the three W03 checks bring registration to 314. This packet runs the
eight selected checks per configuration; it does not claim a full 314-test run.
One early GCC Release build failed on a nested-variant temporary in a test
fixture. Constructing its VariableId alternative directly fixes that warning;
all final builds retain warnings as errors. Early exploratory receipts remain
separate from the stable-source final gates.

## Human inspection and evidence

The [inspection index](../code_specs/README.md) maps 664 maintained files,
152,240 lines and 16,810 structural blocks. There are 132 authored, scoped
seven-field usage contracts, including the weighted helper and public-forwarding
methods. The checker validates current hashes, complete line partitions and
24,245 local links; ten malformed negative controls are rejected. Structural
coverage is not individually authored semantics for every repository block,
and retained comments are not blanket-certified. That wider review remains open.

One independent Astra Max reviewer found no W03 correctness blocker. Root
applied its three small findings: redundant metric guards, precise close/head
scratch costs and a central cursor usage protocol. The reviewer ran no builds
or tests. Root owns the implementation, additional helper contracts and final
validation; a bounded Luna Max task supplied only an independent Python oracle.

Raw logs, receipts, registration comparison, review findings, relocated consumer
and source/artifact hashes are retained under build/verification/w03-*. The
acceptance record is build/verification/w03-acceptance-v1.json; the progress/source
closure is build/verification/w03-progress-v1.json. All 2,425 predecessor source
paths have preserved before-images. Existing sealed W02/W01/C06 evidence is
unchanged. Consult [handoff.md](../handoff.md) for the next task and exact paths.
