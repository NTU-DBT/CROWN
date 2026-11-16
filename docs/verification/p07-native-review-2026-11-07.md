# P07 native source and acceptance review

Status: independent static review, 2026-11-07; no blocking implementation
finding. Native integration and runtime acceptance remain root-owned and in
progress. This review ran no build or test and does not promote excluded
prototype results into native acceptance.

Reviewed Refactor.md §5.4–5.6/P07; the native candidate public API, generator,
key machine, facade/cache, typed IO and report schema; the alternative-plan
contract and P07 proof paragraph; and the current semantic/reference,
exception and IO test sources. The earlier excluded proposal review supplies
context only.

## Source conclusions

- **Family and authority.** `candidate_generator.cpp:122–266` visits every
  generalized count through m−1, every labelled root/parent assignment and
  every tuple from the union of native power sets. Dynamic subset digits do
  not impose a machine-word scope cutoff. Connectivity, Above, branching and
  target native-height filters preserve every requested-height normal-form
  member. The normal-form contraction argument establishes existence of a
  minimum representative, not preservation of globally best maintenance cost.
  Separately admitted exact/residual/cache seeds may retain unary generalized
  nodes. Empty-body handling is explicit.
- **Independent admission.** `candidates.cpp:294–325` sends every seed and
  generated tree through the existing full P02 `ValidationMachine` under the
  owned original binding. Invalid generated drafts and taller checked trees
  are filtered; a checked tree below the supplied optimum causes an internal
  contradiction. Private candidate construction requires the completed gate.
  `InputData` retains the supplied original `VerifiedOptimum`; no alternative
  replaces its certificate witness or creates a new lower bound.
- **Identity and fences.** `candidate_key.cpp:210–260` frames complete rooted
  tokens containing kind, original occurrence, scope and child structure;
  sorting complete child tokens removes order/display differences without
  merging occurrence identities, scopes or generalized grouping. Full bytes,
  not a digest, decide deduplication. `candidates.cpp:397–419,558–603` fences
  prefix/cache reuse with full deterministic catalog/query serialization,
  supported context and matching original height. Reused trees still pass
  P02/height/key admission and acquire the new provider's unchanged proof.
- **Retry and publication.** Saved external operations preserve pending
  generator/key work after allocation failure. Facade stages preserve P02,
  key and publication positions. `candidates.cpp:352–373` prepares output
  capacity and payload before dedup membership; subsequent publication uses
  reserved capacity and nonthrowing handle operations. New cache-node
  allocation precedes eviction. Cumulative construction charges commit after
  successful allocation. Unexpected exceptions produce terminal failure.
- **Ownership and limits.** Candidates/snapshots do not retain a live provider
  or a chain of prior snapshots. Shared tree aliases preserve immutable owner
  lifetime without introducing a back edge. Generator/key stacks and trees
  use flat ownership; cursor teardown does not recursively unwind tree depth.
  Nonterminal cancellation releases unpublished workers; cancellation after
  failure/exhaustion is intentionally inert. Logical construction and depth
  limits are distinct from allocator bytes, width and caller-retained history.
  Variable-width comparisons, relocation, cleanup and excluded admission/P02
  scratch costs are explicitly disclosed. Active time is sampled between
  indivisible operations, not promised as a hard deadline.
- **Report boundary.** `src/io/candidates.cpp:66–138` accepts checked handles
  or a live provider, exports the unchanged original certificate, and puts an
  alternative solely under `checked_upper_only`. It samples rather than
  advances the owner. Snapshot completion belongs to the immutable snapshot.
  The strict schema checks shape/versions and selected diagnostic relations;
  it does not prove binding/height equality, key identity, provenance truth,
  prefix count or actual exhaustion. No report reader creates authority.

## Native acceptance coverage and remaining gates

The current sources contain a separate Prüfer/subset reference collector and
complete-set/key-bijection comparisons over the declared 225-query small
family, retaining frozen P03 minimum authority. They also contain unit/varied
slicing, resource extension and lifetime tests; exact binding/context
mutations; unary-generalized original witnesses and new-proof cache reuse;
mandatory seven/nine-atom height-three seeds; and bounded 70-occurrence,
70-variable work. The wide and height-three cases are bounded prefix checks,
not complete family comparisons.

Exception sources sweep observed allocation positions in generator, key,
provider, admission, snapshot and cache paths, including a distinct residual
source. The IO corpus now obtains an actual distinct residual candidate from
N(), R(x,y), S(x), output y, preserves its cached provenance, and creates
resource/allocation stops and terminal internal failure through real live
operations. Failed diagnostics are not manufactured by editing progress.
Certificate replay, typed writer boundaries, legacy-reader rejection and
schema mutations remain separate checks.

A minor test weakness was reported to root: the seeded factory-admission
fault sweep contained `same_snapshot(prefix, prefix)`. That self-comparison
cannot establish preservation and should compare retained pre-fault evidence;
this is a coverage issue, not a demonstrated implementation defect.

Before acceptance, root must record successful current-source semantic,
exception and report/schema results, the required five-configuration matrix,
and the final source/link/ledger/manifest reconciliation. Preserve the original
P05 seal and distinguish all historical prototype evidence. No runtime result
is asserted by this review; no additional blocking source finding remains.

## Focused native-byte domain finding (before source freeze)

A subsequent focused check found a concrete supported-domain admission defect
in `src/planner/candidates.cpp:44–45`: `.dump()` of the complete binding DOM
requires UTF-8, while the native typed IR accepts arbitrary string bytes.
This finding supersedes the earlier no-blocking-findings conclusion until
corrected and covered by native acceptance.

`src/ir/model.cpp:12–15,87,93` checks identifier nonemptiness/uniqueness, not
encoding; constant admission at lines 103–107 checks scalar type and decimal
representability, not string encoding. Catalog names and metadata likewise
have no UTF-8 admission check (`src/catalog/catalog.cpp:13–15,55,59,73,85`).
P06 `search_session.cpp:18–21,307–312` admits the validated typed binding
without JSON serialization. `docs/semantics.md:27–28` specifies exact binary
string equality and byte ordering; `docs/scalars.md:96–97` preserves exact
bytes including NUL. More explicitly, `docs/runtime_initialization.md:170–171`
distinguishes native non-UTF-8 byte strings from the JSON diagnostic codec.
The JSON/SQL/ingestion UTF-8 limits are transport boundaries, not a native P06
or P07 precondition.

The vendored nlohmann dumper defaults to strict handling
(`third_party/nlohmann/json.hpp:21313–21316`) and throws type_error 316 on an
invalid UTF-8 sequence (lines 19228–19234). A singleton string-column atom
with a constant containing lone byte 0x80 and an empty head is a valid native
height-one query; P07 admission nevertheless fails during binding dumping.
Arbitrary-byte names, aliases and metadata expose the same issue. This is a
source-derived counterexample; no build or runtime probe was run here.

Recommended correction: retain complete deterministic binding identity but
encode it as a private versioned, injective type/length-framed binary token
with raw string bytes and deterministic object order. Reusing the existing
complete binding DOM as the encoder's input avoids a second partial catalog
field inventory. Compare complete tokens. Lossy replacement/ignore modes and
digest-only equality are unsuitable. Required regression coverage includes
native invalid-UTF-8 constants and identifiers/metadata, embedded NUL, exact
hits, and misses between distinct invalid byte strings. Textual report
encoding can retain its separate documented UTF-8 boundary.

## Native-byte correction review

The replacement in `src/planner/candidates.cpp:45–110` resolves the identified
source defect, conditional on root's upcoming raw-byte native regressions.
The private `CROWN-CANDIDATE-BINDING;1;` token keeps the complete existing
binding DOM as its input. Distinct N/B/I/U/S/A/O tags, fixed eight-byte
big-endian integer words, length-prefixed raw strings and counted recursive
arrays/objects make every supported value uniquely decodable. Signed integer
conversion to uint64 is modulo 2^64 under a separate tag from unsigned values;
strings and object keys preserve all bytes, including NUL and malformed UTF-8.
Ordered native JSON objects give deterministic entry order. Width assertions
cover eight-bit bytes, representable size/count words and the expected JSON
integer widths. Unexpected floating/binary/discarded kinds fail explicitly.
Admission serialization still has allocating, variable-width cost outside
advance quanta, and schema nesting bounds the recursive encoder depth.

All original/residual admission, immutable-prefix comparisons, cache lookups
and cache replacements compare/store this same complete token. No digest or
lossy text conversion replaces full equality. The existing complete binding
writer continues to preserve catalog fields, term variants, typed constants,
ordered/repeated outputs, names and metadata; this correction does not add a
second partial field inventory.

Report writers still construct JSON DOMs, which can retain arbitrary native
string bytes. Text serialization through strict `.dump()` remains a separate
UTF-8 boundary and can reject those DOMs. This source change neither broadens
the JSON text/report schema domain nor changes original-proof authority.

Disposition: no unresolved source blocker from the native-byte finding.
Root must still record actual raw-byte constant/name/metadata/NUL hit/miss
coverage, original/residual/prefix paths, and fresh fault/matrix acceptance
against the corrected source. This reviewer ran no build or test. Root also
reports replacing the earlier fault-test self-comparison with deep retained
value baselines; its runtime acceptance remains root-owned.

## Direct v2 binding correction and persistent-OOM disposition

Root's subsequent persistent-allocation-failure sweep exposed another concrete
admission failure in the intermediate DOM-based encoder. The retained
`build/verification/candidate-alternatives-targeted-attempt-2-dom-unwind/candidate-alternatives-debug-exceptions-backtrace.log`
shows termination through nlohmann `json_value::destroy`, `write_document`,
`query_binding` and P07 factory admission. The vendored destructor constructs
and grows a flattening vector (`json.hpp:20583–20621`), so its teardown can
allocate while the fault remains armed. This reviewer inspected that recorded
backtrace and source; the failure was reproduced by root, not by this review.
The intermediate DOM-based correction above is superseded.

The current direct encoder at `src/planner/candidates.cpp:45–227` removes all
IO/JSON/query-binding construction from native admission. Independent field
comparison against `model.hpp` found complete coverage of Catalog version and
table order; table names, columns, source versions, constraints, statistics
and hints; every column policy and optional decimal specification; both
constraint kinds and all IDs/statuses; estimates and optional row counts;
query variables, occurrences, table IDs, ordered terms, ordered/repeated head
outputs and aliases, and contradiction. Term/scalar variant indices distinguish
ignored terms, variables and every constant type. Date epoch days are unique
within its native domain; canonical Decimal text is unique within its native
value domain. No physical data or unrelated Document field is part of this
Catalog/Query identity.

The `CROWN-CANDIDATE-BINDING;2;` prefix fixes the record grammar and field order.
Framed record names distinguish variant records; counted ordered sequences,
optional presence bytes, explicit variant indices and tagged fixed-width
payloads make the complete encoding injective on supported native bindings.
Strings include exact length and all raw bytes. Eight-bit-byte and size_t-width
assertions avoid length/ID truncation; signed int64 conversion is defined modulo
2^64, and Date int32 days widen without loss. Every supported enum occupies a
known field and is encoded numerically. Traversal is deterministic and its call
depth follows fixed native schema nesting, not query cardinality.

Encoder ownership is an ordinary string. Canonical Decimal conversion uses
ordinary temporary strings, whose lifetime extends through the string_view
append call and whose cleanup does not allocate. Native Catalog/Query copies
also unwind through ordinary vectors/strings/variants. No allocating DOM
teardown remains in this factory/cache path. Factory admission mutates no
caller artifact; cache lookup finishes token construction before changing
counters; installation retains allocation-before-eviction ordering. The
original/residual/prefix/cache fences continue to compare full v2 token bytes.

Current disposition: both the native-byte rejection and DOM-unwind termination
are corrected at source by the direct v2 encoder; no unresolved static blocker
was found. Closure still requires root's final-source raw-byte regressions,
uncapped persistent-OOM sweeps with deep retained VALUE baselines, and fresh
build/report/matrix reconciliation. The earlier DOM approval established its
framing properties but did not establish persistent-OOM cleanup safety.
Textual report JSON retains its separate strict UTF-8 and allocating IO
boundary. No build or test was run by this reviewer.
