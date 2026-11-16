# R2 JSONL/CLI and human inspection — V31

The [public reader and usage guide](../sql_aggregate_input.md) now connect
nullable atomic physical-row commands to the genuine R2 Session through
`crown aggregate create/run/status/snapshot/checkpoint`. The original set CLI
retains its own formats and workflow. W06 remains in progress for exact
varying-int32 admission and its complete acceptance audit.

## Implementation and review

The reader validates strict JSON fields, genuine SQL binding, physical source
schema/type/nullability, W+1, framing and resource extents. Returned commands own
flat TEXT/cell/edit buffers; the reader retains its largest accounted raw-line
capacity. Source monotonicity and native decisions remain Session obligations.
JSON DOM/lexer/stream/compiler/report workspace follows the existing ordinary
allocation boundary. Decoder failure latches reopen before consuming input;
there is no new decoder catch/retry or native rollback framework.

Run drains existing output, resolves the actual WAL-owned head, then constructs
the next reader from logged W and its continuation. The decoded command is freed
after log and before decide. Reject progresses I/reader without C/D, while
resource failures retain the same head or require reopen after uncertain I/O.
Report failure cannot undo a durable decision. Snapshot/status are recovery
operations and can repair admissible tails unless explicitly disabled.

Independent source review corrected tagged DATE/DECIMAL limits, raw-buffer cost
wording, symbolic SQL kind output, storage resource diagnostics and three guide
ambiguities: contradiction/tree-search scope, terminal continuation after a
consumed unterminated record, and decoder versus Session responsibilities.
Receiving checks also found the reserved allocator-purpose mistake and two
fixture assumptions (unsupported decimal SUM and global empty-group presence).
The JSON library's own destructor fallback was investigated with GDB; it needs
no new product exception handling. The final boundary has six short typed
presentation translations; existing Session's three catches are unchanged.

The [structural schema](../../schemas/sql-aggregate-input-v1.schema.json) is
installed with the new usage guide. It does not authorize binding, native state,
duplicate/lexical acceptance or progress/resource claims. Installed source/design
cross-references require a matching source checkout; complete installed-document
navigation is not certified.

## Receiving evidence

| Check | Actual scope/result |
| --- | --- |
| Affected Debug | 15/15, 120.36s |
| Full selected ASan/UBSan/leaks | 15/15, 394.93s, parallel 2 |
| Final current Debug | reader and actual CLI 2/2, 3.66s |
| Final current ASan/UBSan/leaks | reader and actual CLI 2/2, 30.36s |
| Production OFF Release | complete build passes, zero registered tests |
| Relocated current SDK | 229 files unchanged on move; 4/4, 3.19s |
| Additional installed CLI | five source shapes × two backends, 20 commands, checkpoint after each |
| New input allocation sweep | 144 reached covered C++ new refusals: 141 propagate, three valid cleanup fallbacks |
| Receiving account | exact 13,151-byte peak passes; one below refuses |
| Prior registrations | 345 definitions/properties preserved, 347 total |
| Actual strict flags | 14 Debug/SAN/OFF/SDK records |

The 15-test cohorts include existing set workflow/EXPLAIN/process-boundary checks,
Session unit/fault sweeps and R2 file/codec/descriptor/checkpoint checks. Final
production C++ is identical to those runs. A subsequent Python-only test extends
unterminated-file continuation coverage; a packaging-only rule installs the guide,
and a structural JSON schema is added. Current two-test and package checks cover
those final bytes; earlier execution is not relabeled as a later run.

Each main CLI profile uses DuckDB 1.5.4 and both physical backends: 11 ordered
commands per backend, including three count/weight Rejects, plus a separate
two-command signed-bigint SUM overflow/retry case. The latter keeps COUNT in
range while `SUM(CAST(2 AS INT))` exceeds bigint, checkpoints after Reject and
successfully retries a valid row. Actual sink frames/hashes and nullable
before/after tuples are decoded independently. Public-API helper processes leave
real Input/Commit states for CLI resume; they are not injected process-crash
experiments. Existing Session's separate fault matrix is rerun by the cohorts.

The extra installed Release gate covers no-FROM, typed NULL/no-FROM, contradiction,
self-join and two-table join on both backends. It checks initial/after snapshots
against independent DuckDB results, actual sink epochs and checkpoint/recovery
after every command. It does not claim Debug/SAN execution of that extra matrix.

All previous public headers and all 20 non-recovery archives (19 CROWN plus the
pinned parser) match the prior SDK exactly. Only main.cpp changes among the 351
predecessor production paths: its include, help line and dispatch branch.
New reader/CLI code lives in separate files; no ordinary source/native/group
field or handler is added. No CPU benchmark, current Clang, full 347-test,
whole-W06 or release claim is made.

## Specifications and provenance

The [map](../code_specs/README.md) now has 15,206 usage contracts over 748 files,
171,238 lines and 19,341 blocks; 12,795 blocks carry scoped contracts. This pass
adds 152 cards: 72 existing epoch/view/transport test cards, 38 reader/test cards
and 42 root CLI/build/declaration cards. Root updates 1,480 predecessor cards for
the exact three existing-file changes: four semantic/signature updates and 1,476
source-hash/review-attribution refreshes. A separate immutable cost amendment
corrects the caller-diagnostic wording in one new test card.

All selected non-test regions have usage cards. Of 5,423 selected test regions,
4,076 are reviewed and 1,347 remain. Every maintained line is structurally mapped;
card presence is not a mathematical or complete semantic proof. Transport,
durability and allocation protocols are local engineering, with source/spec
references; the [paper map](../code_review.md) keeps theorem claims separate.

There are 40 recorder jobs, 35 zero command exits including four diagnostic GDB
commands. Five initial build/test failures are retained. A GDB zero exit does
not mean its stopped inferior passed a receiving test. Current native inputs
are 1,193: seven intended additions and three changed predecessor inputs. Original
recorded keys do not change during commands. The recorder does not detect all
later additions, so no global no-additions claim is made.

Root evidence is `build/verification/w06-r2-jsonl-cli-implementation-v1`, with
current receiving/input/coverage v2 amendments, terminal logs, compiler/link/SDK
comparisons, schema and actual source-shape checks. Four immutable author/review
controls are pinned separately. V31 is frozen at
`build/verification/human-inspection-v31-source-v1` and sealed by
`build/verification/human-inspection-v31-progress-v1.json`.

Root implements/verifies; Luna Max supplies two bounded card reviews and a
normal-model lane independently reviews the new authority/lifecycle/cost paths.
No Astra invocation was needed. Full ledger remains 56 verified / 2 in progress /
20 not started. A02 still blocks B01/C04. See the [handoff](../handoff.md) and
exact [V30 history](../handoff-history-v30-2026-11-13.md) for continuation.
