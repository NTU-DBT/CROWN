# Genuine SQL aggregate runtime: receiving verification

The [public runtime](../sql_aggregate_runtime.md) composes original SQL/catalog
binding, one actual physical source/native transaction and touched group state.
Its only mutation input is a physical `sql_rows::NetBatch`. It keeps no joined-row
ledger and introduces no production catch or second undo system. The shared
private arithmetic helper preserves the existing single-row aggregate behavior.
This verifies in-memory composition; W06 durable recovery remains open.

## Executed maintained checks

Strict C++23 warnings-as-errors builds and **24/24 selected tests pass in each
profile**: Debug **129.34s**, full ASan/UBSan/leaks **293.94s**. The cohort includes
parser/binding/normalization, W04 arithmetic/binding/runtime/SQL, W05 source/batch/
SQL, weighted propagation/capture and the two new composed runtime tests. Both
storage backends run in the new runtime and independent SQL controls.

All 328 predecessor test commands and execution properties remain, excluding
source-line backtraces. Two additions bring registration to 330. These results do
not establish execution of all 330. Complete test-disabled Release builds the new
library by default and excludes its test/driver. A relocated **220-file SDK** and
strict public C++23 consumer pass: a real joined aggregate retains its hidden
separator key, survives caller-text and facade destruction before commit, and
returns its receiving account to the controller after retained results close.

Actual old/new Release archives produce identical observations in five ordinary
W04 cases: constructor and per-operation allocation/account totals, selected
work, explicit outputs and value layouts. Legacy Metrics/Epoch remain 72/160
bytes on this build. Existing uncaptured-row updates still allocate zero covered
C++ objects and report the same 168 selected work units with 512 repeated aliases.
These are allocation/work/layout observations, not CPU timing or portable ABI claims.

## Independent SQL and resource evidence

Each maintained oracle run compares **99 cases / 198 backend requests / 3,436
atomic epochs / 3,634 snapshots**, including 64 seeded traces of 24 commands.
DuckDB executes joins, predicates, grouping, COUNT and SUM over bounded expanded
physical bags; AVG uses exact engine SUM/COUNT followed by Fraction rounding at
scales 0..18. Full hidden keys, nullable values, names/types, before/final batch
diffs, physical/logical changed flags and coherent sequences are compared. Source
weights are at most eight and expanded source copies at most 24 per table.

Separate root-private runs of the identical source-frozen driver/script pass
DuckDB 1.5.4 with Debug and PostgreSQL 16.15 with private sanitizer instrumentation.
The private UTF8/C PostgreSQL cluster closes successfully. That private sanitizer
instruments the five proposal CPPs and tests; its underlying SDK dependency
archives are Release. The maintained full sanitizer cohort above is separate.
No author or documentation reviewer executed these native/SQL jobs.

Resource probes observe a constant **939 additional accounted result bytes** for
8/64/256 native facts feeding one global group, with native D capture absent from
returned epochs. One touched group among 8/64/256 resident groups finalizes one
state field and reports group work 16. Source/native work remains separate;
ordered-map comparisons and allocator/cleanup costs are not fully metered.
Real receiver exact/one-under grants pass at 229,866 ordered / 229,777 indexed
requested bytes. Commit/rollback under covered C++ new denial, update failure
cuts, retries, workspace release and owner/output lifetime controls pass. Group
output capture reserves touched-group capacity even when equal outputs suppress
every event; that capacity lasts until the returned epoch closes.

## Source and failure provenance

Root adopts 16 source files from exact sealed runtime/oracle proposals plus the
explicit receiving overlays: preserve the compiler sanitizer setting, add the
runtime/oracle settings, use the tested fixture repairs and add six offline file
roles. Role-map function/class ASTs are unchanged. Original runtime CPP production
postimages require no repair after static review and private testing.

The original first joined unit fixture omits the join separator from its source
head and fails actual CROWN tree admission. The receiving query groups by hidden
`a.id` as well as `a.g` and compares full keys. A source-work failure test originally
catches the wrong carrier; it now catches actual fixed `storage::IndexFailure` at
that one assertion. The private diagnostic helper reports unsupported source
SQL when plan admission fails. Production admission/error policy is preserved.

Root evidence is `build/verification/w06-sql-aggregate-runtime-implementation-v1`.
Its **48 recorder jobs preserve 43 successes and five failed attempts**: three
original fixture aborts and two private cost builds before their target was
generated. Every in-command source-drift list is empty. Failed logs and source
preimages remain; no failed attempt was overwritten. Main cohorts pin 1,142
maintained native inputs. Later lifecycle/session-test wording corrections change
two hashes: 32/27 diagnostic literals and explanatory comments, with identical
non-literal C++ tokens, assertions, calls and helper identifiers. No implementation
rerun is claimed for those wording changes. Full token identity would be incorrect
because literals changed; exact phase differences remain in input-cohorts-v2.json.

The runtime proposal checksum is
`3e9b336057c473ebd0f356b5c10dad8017d2af2cfa5ffd469428dce3c46bf257`;
the oracle checksum is
`a23797b752787fc343c73078b147834208a5510ac70317fe698c748d809c44e9`.
A focused Astra static review finds no new blocking production defect, while
identifying the two original fixture issues. Root's canonical review reconciles
the shared helper, authentic metadata freezes, lifetime/cost contracts, CMake,
installed target, role metadata and independent oracle against actual receiving bytes.

Varying int32-column admission remains unavailable; constant integer-SUM and
private wide arithmetic tests do not close that integration case. Operational
WAL/dispositions, source and output frontiers, sink, authoritative physical
checkpoint/cold rebuild and CLI remain separate W06 work. The sealed durable
assessment and root continuation notes specify missing APIs rather than claiming
they exist. Paper provenance remains in the [source review](../code_review.md);
this bridge does not acquire a Boolean-update or arbitrary aggregate-delay theorem.
