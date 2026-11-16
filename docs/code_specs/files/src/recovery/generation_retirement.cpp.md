# `src/recovery/generation_retirement.cpp` — block usage map

[Source](../../../../../src/recovery/generation_retirement.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Retire only history authorized by durable root/delivery state.

Snapshot SHA-256: `2f7a7627a19de19466f0da5bd552cf206685f73abed4b56ae94ce5cec94d58b6`. 137 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/recovery/generation_retirement.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–12](../../../../../src/recovery/generation_retirement.cpp#L10) | Callable definition: \[\[noreturn\]\] void fail(GenerationFault fault,GenerationStage stage=GenerationStage::state,GenerationOutcome outcome=GenerationOut… | calls GenerationFailure · [reviewed contract](#b0002) |
| [B0003 · 13–15](../../../../../src/recovery/generation_retirement.cpp#L13) | Callable definition: bool hex(std::span&lt;const char&gt; bytes) | calls std::all_of, begin, end; returns std::all_of(bytes.begin(),bytes.end(),\[\](char c){return (c&gt;=@ && c&lt;=@ ) \|\| (c&gt;=@ && c&lt;=@ ) · [reviewed contract](#b0003) |
| [B0004 · 16–25](../../../../../src/recovery/generation_retirement.cpp#L16) | Callable definition: void valid(const RetirementIntent& value) | calls hex, fail, runtime::detail::checkpoint_options · [reviewed contract](#b0004) |
| [B0005 · 26–26](../../../../../src/recovery/generation_retirement.cpp#L26) | Explanatory comments or spacing. | source comment (unverified): // The intent omits delivery; retain the actual selected root delivery anchor. · [reviewed contract](#b0005) |
| [B0006 · 27–29](../../../../../src/recovery/generation_retirement.cpp#L27) | Callable definition: bool anchor(const RetirementIntent& intent,const GenerationRoot& selected) | calls ; returns selected==before \|\| selected==after; source comment (unverified): // The intent omits delivery; retain the actual selected root delivery anchor. · [reviewed contract](#b0006) |
| [B0007 · 30–32](../../../../../src/recovery/generation_retirement.cpp#L30) | Callable definition: void proof(const RetirementIntent& intent,const sink::Header& header,std::uint64_t generation,std::uint64_t sequence) | calls fail · [reviewed contract](#b0007) |
| [B0008 · 33–37](../../../../../src/recovery/generation_retirement.cpp#L33) | Callable definition: bool same(const struct stat& a,const struct stat& b) | calls ; returns a.st_dev==b.st_dev && a.st_ino==b.st_ino && a.st_size==b.st_size && · [reviewed contract](#b0008) |
| [B0009 · 38–38](../../../../../src/recovery/generation_retirement.cpp#L38) | Explanatory comments or spacing. | source comment (unverified): // Fixed layouts fit 724/788 bytes; internal field helpers rely on those sizes. · [reviewed contract](#b0009) |
| [B0010 · 39–43](../../../../../src/recovery/generation_retirement.cpp#L39) | Type/record definition: struct Writer | 1 loop sites; source comment (unverified): // Fixed layouts fit 724/788 bytes; internal field helpers rely on those sizes. · [reviewed contract](#b0010) |
| [B0011 · 44–48](../../../../../src/recovery/generation_retirement.cpp#L44) | Type/record definition: struct Reader | returns value; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 49–50](../../../../../src/recovery/generation_retirement.cpp#L49) | Closes surrounding scope/type. | source comment (unverified): // Plan-aware v2 appends 64 bytes; legacy v1 keeps its exact layout. · [reviewed contract](#b0012) |
| [B0013 · 51–60](../../../../../src/recovery/generation_retirement.cpp#L51) | Callable definition: RetirementBytes encode_retirement_intent(const RetirementIntent& intent) | calls valid, text, integer, fail; returns result; 1 loop sites; source comment (unverified): // Plan-aware v2 appends 64 bytes; legacy v1 keeps its exact layout. · [reviewed contract](#b0013) |
| [B0014 · 61–74](../../../../../src/recovery/generation_retirement.cpp#L61) | Callable definition: RetirementIntent inspect_retirement_intent(std::string_view bytes) | calls size, fail, sha256_fixed, substr; returns result; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 75–77](../../../../../src/recovery/generation_retirement.cpp#L75) | Callable definition: std::array&lt;char,256&gt; GenerationOwner::retirement_name() const | calls root, data, std::copy, begin; returns value · [reviewed contract](#b0015) |
| [B0016 · 78–91](../../../../../src/recovery/generation_retirement.cpp#L78) | Callable definition: void GenerationOwner::read_retirement() | calls retirement_name, call, get, data; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 92–98](../../../../../src/recovery/generation_retirement.cpp#L92) | Callable definition: void GenerationOwner::validate_retirement(const sink::File& file) const | calls state, anchor, fail, prefix · [reviewed contract](#b0017) |
| [B0018 · 99–100](../../../../../src/recovery/generation_retirement.cpp#L99) | Explanatory comments or spacing. | source comment (unverified): // Caller just read and validated bytes under the generation lock. · [reviewed contract](#b0018) |
| [B0019 · 101–110](../../../../../src/recovery/generation_retirement.cpp#L101) | Callable definition: void GenerationOwner::confirm_checkpoint(std::string_view bytes) | calls size, fail, consume_work, sha256_fixed; source comment (unverified): // Caller just read and validated bytes under the generation lock. · [reviewed contract](#b0019) |
| [B0020 · 111–112](../../../../../src/recovery/generation_retirement.cpp#L111) | Explanatory comments or spacing. | source comment (unverified): // Session first checks quiescence and privately verified native delivery. · [reviewed contract](#b0020) |
| [B0021 · 113–136](../../../../../src/recovery/generation_retirement.cpp#L113) | Callable definition: void GenerationOwner::retire_history(const sink::Receipt& receipt,std::string_view checkpoint_bytes,const resource::MemoryAccount… | calls healthy, has_selection, read_root, fail; 3 loop sites; source comment (unverified): // Session first checks quiescence and privately verified native delivery. · [reviewed contract](#b0021) |
| [B0022 · 137–137](../../../../../src/recovery/generation_retirement.cpp#L137) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::detail · [reviewed contract](#b0022) |

## B0001

[Lines 1–9](../../../../../src/recovery/generation_retirement.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:f8623b7613da66b5dc7ca27acf5dfb3d2aa0760cb0d5e78570a141f8f33d2a10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (generation_detail.hpp, crown/ir/digest.hpp, ../runtime/checkpoint_policy.hpp, algorithm, cerrno, sys/stat.h) and opens crown::recovery::detail scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [docs/code_specs/files/src/recovery/generation_retirement.cpp.md](generation_retirement.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0002

[Lines 10–12](../../../../../src/recovery/generation_retirement.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void fail(GenerationFault fault,GenerationStage stage=GenerationStage::state,GenerationOutcome outcome=GenerationOutcome::unchanged,int error=0)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Throw the fixed typed generation failure record. |
| inputs / outputs | Supplied fault/stage/root-outcome/native errno produce GenerationFailure; omitted stage/outcome use state/unchanged. |
| invariants | GenerationOutcome describes root selection, not a promise that no intent/temporary/I/O effect occurred. Fixed what() avoids building owning diagnostic strings. |
| ownership | Exception owns only copied enum/int/bool values; no frame or owner reference retained. |
| failure | Always throws GenerationFailure; no catch, retry or rollback at this helper. |
| cost | Failure-only small exception value construction; no successful-path call or dynamic diagnostic formatting. |
| Design | [docs/history-retirement.md §Persistence and continuation](../../../../history-retirement.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp) |

## B0003

[Lines 13–15](../../../../../src/recovery/generation_retirement.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool hex(std::span<const char> bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the fixed retirement identity/digest character domain. |
| inputs / outputs | Returns whether all supplied bytes are lowercase ASCII hexadecimal; empty span is vacuously accepted by helper. |
| invariants | Callers provide fixed 32/64-byte arrays and separately validate numerical/native relationships. Hex syntax does not authenticate a sink or checkpoint. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | Boolean predicate only, no exception or I/O. |
| cost | O(span bytes), fixed widths for real calls; no heap allocation. |
| Design | [docs/history-retirement.md §Format and costs](../../../../history-retirement.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

## B0004

[Lines 16–25](../../../../../src/recovery/generation_retirement.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid(const RetirementIntent& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the retirement intent structural binding projection. |
| inputs / outputs | Checks valid native query/checkpoint/optional plan hashes, nonempty older retained range, matching sink query and valid sink identities/policy, generation/base/acknowledgment inequalities. |
| invariants | Acknowledged generation lies within sink origin/current selection and sequence covers checkpoint. Does not establish actual file/root/Receipt/session authority or native correctness; delivery anchor is deliberately omitted from intent wire and checked from selected root separately. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | GenerationFailure(binding) for explicit predicates; checkpoint_options can propagate ImageFailure(corrupt) for malformed policy words. No local translation or owning diagnostics. |
| cost | Fixed hash and 26-policy-word validation, constant stack and no account allocation. |
| Design | [docs/history-retirement.md §Persistence and continuation](../../../../history-retirement.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [docs/history-retirement.md §Format and costs](../../../../history-retirement.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp) |

## B0005

[Lines 26–26](../../../../../src/recovery/generation_retirement.cpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:c496c34101d49074b68dba626bc8896bad27f96f578da465b6d0d9bfcef51d03
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: The intent omits delivery; retain the actual selected root delivery anchor. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/generation_retirement.cpp lines 24-28; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [docs/code_specs/files/src/recovery/generation_retirement.cpp.md](generation_retirement.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0006

[Lines 27–29](../../../../../src/recovery/generation_retirement.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool anchor(const RetirementIntent& intent,const GenerationRoot& selected)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Match an intent to the currently selected native root before or after floor advancement. |
| inputs / outputs | Copies intent.before, substitutes actual selected delivery anchor, and compares selected with that native root or the same root with first_generation=current. |
| invariants | All immutable native/plan/frontier fields and cleanup range remain exact; the selected root retains delivery authority because intent does not serialize it. A public metadata comparison alone cannot authorize deletion. |
| ownership | Reads intent and selected synchronously; returns bool with no retained borrowed data. |
| failure | Boolean predicate only; no throwing recovery mechanism. |
| cost | Two fixed root copies and field comparisons; no I/O, account allocation or directory scan. |
| Design | [docs/history-retirement.md §Persistence and continuation](../../../../history-retirement.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

## B0007

[Lines 30–32](../../../../../src/recovery/generation_retirement.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void proof(const RetirementIntent& intent,const sink::Header& header,std::uint64_t generation,std::uint64_t sequence)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the actual sink header and acknowledged frontier to cover an existing intent. |
| inputs / outputs | Exact whole Header equality plus generation&gt;=recorded acknowledged generation and sequence&gt;=recorded acknowledged sequence. |
| invariants | Accepts later compatible acknowledged prefix; bytes/fingerprint/native verification are checked from actual File/session separately. Integers or a forged State cannot substitute for the private owner/Receipt call chain. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | GenerationFailure(binding) on mismatch, with default state/unchanged metadata; no retry or rollback. |
| cost | Fixed identity/binding/header field comparisons and scalar predicates, no I/O or allocation. |
| Design | [docs/history-retirement.md §Persistence and continuation](../../../../history-retirement.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md) |

## B0008

[Lines 33–37](../../../../../src/recovery/generation_retirement.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same(const struct stat& a,const struct stat& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the file stamps used to reject a changed retirement intent read. |
| inputs / outputs | Requires equal device, inode, size, mtime seconds/nanoseconds and ctime seconds/nanoseconds. |
| invariants | Does not compare contents, permissions or cryptographically bind a namespace. Used together with complete read/checksum/EOF under the cooperating lifetime lock and trusted stable namespace assumptions. |
| ownership | Borrows immutable input synchronously; changes only private codec preparation. Returned fixed metadata owns its fields. No filesystem or native query state changes. |
| failure | Boolean predicate only; read_retirement chooses the changed-file failure category. |
| cost | Fixed field comparisons, no syscall or allocation within this predicate. |
| Design | [docs/history-retirement.md §Persistence and continuation](../../../../history-retirement.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [docs/history-retirement.md §Format and costs](../../../../history-retirement.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

## B0009

[Lines 38–38](../../../../../src/recovery/generation_retirement.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:8d8c4a9824e82c2cb45105a42fa22fca18655a675f4f665a8c632fd14675a5c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Fixed layouts fit 724/788 bytes; internal field helpers rely on those sizes. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/generation_retirement.cpp lines 36-40; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [docs/code_specs/files/src/recovery/generation_retirement.cpp.md](generation_retirement.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0010

[Lines 39–43](../../../../../src/recovery/generation_retirement.cpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Writer
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the fixed retirement wire into bounded stack storage. |
| inputs / outputs | Writer owns zeroed 788-byte maximum intent buffer and offset; text copies fixed spans, integer emits caller-selected little-endian width (2 or 8). |
| invariants | Methods have no independent bounds checks: only fixed encode_retirement_intent layout calls them, producing 660/724 prehash bytes then 64 digest bytes within 724/788 total. Changing layout requires updating sizes and exact final offset check. |
| ownership | Writer owns its stack buffer; input arrays/spans are synchronously borrowed, result bytes copied into RetirementBytes. |
| failure | No per-field exception handling; caller validates intent and checks exact final offset before checksum publication. |
| cost | Fixed zero initialization plus O(copied bytes) stores, no heap/account allocation or filesystem effect. |
| Design | [docs/history-retirement.md §Format and costs](../../../../history-retirement.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/reoptimization.md §Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp) |

## B0011

[Lines 44–48](../../../../../src/recovery/generation_retirement.cpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Reader
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode fixed retirement wire fields after full framing admission. |
| inputs / outputs | Reader borrows bytes and offset; text copies known fixed array widths, integer reads 2/8 little-endian bytes. |
| invariants | No per-field bounds check: inspect_retirement_intent first requires exact 724/788 length, checksum and matching version/body/flags, then consumes the fixed layout and verifies offset==size-64. This private helper is not a general untrusted span reader. |
| ownership | Borrowed input remains immutable during inspect; fields copied into owning fixed arrays in RetirementIntent. |
| failure | No direct throw handler; outer framing and exact-offset checks reject before any result is returned. |
| cost | O(fixed wire bytes), constant stack and no allocation; no repeated owning strings or DOM. |
| Design | [docs/history-retirement.md §Format and costs](../../../../history-retirement.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/reoptimization.md §Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp) |

## B0012

[Lines 49–50](../../../../../src/recovery/generation_retirement.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L50:sha256:307ef9938a5a5df1e0493f9c98bde778b4bf07adb1cf860b3435d83a1b4cc2a6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing implementation scope at this source boundary; this is a lexical delimiter, not an operation. Trailing source note states: Plan-aware v2 appends 64 bytes; legacy v1 keeps its exact layout. It remains prose guidance, not a certified executable claim. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. Any trailing comment in this block is guidance only and adds no runtime invariant. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [docs/code_specs/files/src/recovery/generation_retirement.cpp.md](generation_retirement.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0013

[Lines 51–60](../../../../../src/recovery/generation_retirement.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RetirementBytes encode_retirement_intent(const RetirementIntent& intent)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a checksummed immutable retirement-range intent. |
| inputs / outputs | Valid intent produces owning fixed RetirementBytes: CROWNRT1 v1/724 bytes or v2/788 when selected plan_sha256 exists, zero flags and body 640/704. |
| invariants | Serializes native root projection, exact sink header and acknowledged generation/sequence; v2 appends plan hash. Selected delivery anchor stays in actual root, not this intent. Checked offset precedes final SHA256; no filesystem publication occurs here. |
| ownership | Returns fixed owning bytes with explicit length; no references to supplied intent survive. |
| failure | Structural/policy faults as valid; GenerationFailure(state) if fixed writer offset disagrees. No partially published file/result. |
| cost | Fixed stack 788-byte buffers/copies, fixed validation and SHA256 of 660/724 bytes; no account allocation. v1 wire remains unchanged. |
| Design | [docs/history-retirement.md §Format and costs](../../../../history-retirement.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/reoptimization.md §Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp) |

## B0014

[Lines 61–74](../../../../../src/recovery/generation_retirement.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RetirementIntent inspect_retirement_intent(std::string_view bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the exact fixed retirement intent formats without granting deletion authority. |
| inputs / outputs | Accepts only exact 724/788 bytes, checks magic/SHA256, version/zero flags/body length, decodes fixed fields and optional plan hash, then applies valid. |
| invariants | Unknown size/version/layout or trailing bytes reject. Inspection does not compare to a selected root, actual sink prefix or native session; those checks are private owner/session responsibilities. |
| ownership | Input borrowed synchronously; RetirementIntent owns fixed arrays and optional root/plan metadata, no frame byte view. |
| failure | GenerationFailure(truncated/corrupt/read_data) for framing/checksum/layout, binding/state faults from validation; malformed policy can propagate ImageFailure. No partial return. |
| cost | SHA256 over 660/724 bytes plus fixed copies/checks; constant stack, no account allocation or filesystem I/O. |
| Design | [docs/history-retirement.md §Format and costs](../../../../history-retirement.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/reoptimization.md §Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp) |

## B0015

[Lines 75–77](../../../../../src/recovery/generation_retirement.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,256> GenerationOwner::retirement_name() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive the private sibling retirement-intent basename. |
| inputs / outputs | Copies admitted root basename and .retire into zero-initialized char\[256\], retaining a NUL terminator. |
| invariants | GenerationOwner construction bounds basename to 232 bytes, so suffix fits. Does not enumerate directory entries or derive cleanup range from names. |
| ownership | Returns owning fixed character array; references only already-admitted owner basename during copying. |
| failure | No local throwing check; depends on constructor-established basename bound. |
| cost | O(root basename length), at most 232 bytes plus suffix; fixed 256-byte stack value, no heap allocation. |
| Design | [docs/history-retirement.md §Persistence and continuation](../../../../history-retirement.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp) |

## B0016

[Lines 78–91](../../../../../src/recovery/generation_retirement.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::read_retirement()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a compatible actual retirement intent under the generation lock. |
| inputs / outputs | Opens .retire no-follow, treats ENOENT as no intent, otherwise requires regular exact-size file, reads all bytes plus EOF, checks unchanged stamp/checksum/root/query binding, syncs file+directory, checks close, then stores intent. |
| invariants | EINTR retries consume owner operation count. Existing selected root can be before/after floor; incompatible or malformed intent cannot choose deletion scope. Cached retirement is replaced only after complete validation/sync, except explicit absent-file reset. |
| ownership | Temporary FileDescriptor owns the opened inode until checked release/close; owner retains fixed intent metadata only, lock/directory stay owned. |
| failure | GenerationFailure with stage/outcome/errno for I/O/regularity/change/binding/limits; inspect policy ImageFailure may propagate. RAII closes on rejection; checked Linux close is never retried. |
| cost | Reads fixed 724/788 bytes in admitted chunks plus EOF, two fstats, fsync file/directory and checked close; consumes 2*size validation units. Fixed stack buffer/no account allocation; cumulative syscalls/work are not refilled. |
| Design | [docs/history-retirement.md §Persistence and continuation](../../../../history-retirement.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [docs/history-retirement.md §Format and costs](../../../../history-retirement.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/reoptimization.md §Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp) |

## B0017

[Lines 92–98](../../../../../src/recovery/generation_retirement.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::validate_retirement(const sink::File& file) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Match pending cleanup continuation against the actual admitted sink owner. |
| inputs / outputs | No-op when no intent. Otherwise reads actual File state, rejects recovery-required/root-anchor mismatch, checks selected delivery ID/byte length/fingerprint at checkpoint or exact legacy sink base, then exact intent sink/header/frontier proof. |
| invariants | Uses the private File index/prefix and selected durable root, not a supplied mutable State. This validates local durable coverage; session restore must still complete native/source replay before exposing or deleting history. |
| ownership | Borrows actual File synchronously; retains no Receipt/state/prefix references. |
| failure | GenerationFailure(binding) for checks; File state/prefix failures propagate sink::Failure or ImageFailure. No file repair/deletion or state publication. |
| cost | Fixed state/header copies and constant-time indexed File::prefix lookup, not a sink-file or row scan; no I/O/new account allocation here. |
| Design | [docs/history-retirement.md §Persistence and continuation](../../../../history-retirement.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [src/recovery/local_sink.cpp](../../../../../src/recovery/local_sink.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/history-retirement.md §Checkpoint delivery binding](../../../../history-retirement.md) |

## B0018

[Lines 99–100](../../../../../src/recovery/generation_retirement.cpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L100:sha256:efb39c5267842c1b292d52521f9f7a61a7e0b49bd6792b4c08650d6ca82e7133
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Caller just read and validated bytes under the generation lock. Rehash and sync the selected inode/name here; no checkpoint reread occurs. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/generation_retirement.cpp lines 97-102; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [docs/code_specs/files/src/recovery/generation_retirement.cpp.md](generation_retirement.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0019

[Lines 101–110](../../../../../src/recovery/generation_retirement.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::confirm_checkpoint(std::string_view bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconfirm durability of the selected checkpoint after caller-native validation. |
| inputs / outputs | Checks supplied checkpoint byte limit/hash against selected root, opens selected .ckpt no-follow, requires regular file with same length, then syncs inode/directory and checked-closes. |
| invariants | Does not reread the opened checkpoint contents: QuerySession just read and fully validated those bytes under the lifetime generation lock and trusted stable namespace. Hashing input alone is not a generic file-content or native-state proof. |
| ownership | Borrows caller checkpoint buffer synchronously; temporary FileDescriptor owns opened inode; selected/root/lock ownership stays in GenerationOwner. |
| failure | GenerationFailure(limit/binding/changed/I/O) with relevant stage/outcome; caller enters required recovery for GenerationFailure. RAII closes private descriptor, no deletion starts here. |
| cost | O(supplied checkpoint bytes) SHA256 charged once; one open/fstat, file/directory fsync and checked close. No checkpoint buffer allocation/read in this helper; caller already owns receiving-account bytes. |
| Design | [docs/history-retirement.md §Persistence and continuation](../../../../history-retirement.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [docs/history-retirement.md §Format and costs](../../../../history-retirement.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp) |

## B0020

[Lines 111–112](../../../../../src/recovery/generation_retirement.cpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L112:sha256:5ae4f01ef5df27196d3d30564526947ea104dc2ec132407a5b5e1f55028c70f5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Session first checks quiescence and privately verified native delivery. The durable intent fixes cleanup scope; select its root floor before unlinking. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/recovery/generation_retirement.cpp lines 109-114; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [docs/code_specs/files/src/recovery/generation_retirement.cpp.md](generation_retirement.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0021

[Lines 113–136](../../../../../src/recovery/generation_retirement.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void GenerationOwner::retire_history(const sink::Receipt& receipt,std::string_view checkpoint_bytes,const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retire only the older generation range fixed by a durable intent and selected native checkpoint. |
| inputs / outputs | Healthy private owner rechecks/adopts root, reads intent, validates actual private Receipt coverage, optionally rereads selected plan under account, reconfirms checkpoint, publishes intent if new, selects first=current, unlinks older .ckpt/.wal/.plan and syncs after each, then removes/syncs intent last. |
| invariants | QuerySession first requires quiescent healthy journal/native state and privately verified sink bytes/fingerprint/current epoch, plus selected checkpoint native binding/frontiers. No-op if no older range/intent. Selected generation/files/output are preserved; ENOENT history is idempotent. Intent alone/Receipt alone cannot establish all caller authority. |
| ownership | Borrows immutable Receipt/checkpoint synchronously; owner retains selected root/intent and lifetime lock. Optional plan buffer is private receiving-account ownership released before intent publication; caller checkpoint buffer remains alive through operation. |
| failure | Typed validation/account/I/O failures propagate. Effects after intent/root publication may require restart; there is no rollback of completed deletion. Session catches GenerationFailure and latches required recovery; root rename uncertainty latches owner. Resume validates same recorded range and actual sink before retrying cleanup. |
| cost | Before publication: root/intent/checkpoint validation and optional whole plan read/hash/account buffer. After publication: fixed stack encode/names plus O(old generation count) three unlink attempts+directory syncs per generation, then intent unlink/sync; retries bounded by cumulative operation grant. Successful suffix has no new account allocation or directory scan. |
| Design | [docs/history-retirement.md §Persistence and continuation](../../../../history-retirement.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [docs/history-retirement.md §Format and costs](../../../../history-retirement.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/reoptimization.md §Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/history-retirement.md §Checkpoint delivery binding](../../../../history-retirement.md) |

## B0022

[Lines 137–137](../../../../../src/recovery/generation_retirement.cpp#L137); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L137-L137:sha256:acdf1b5fc75d5c18b842bb7fb52e994294982fe0260b6a9937115ce51c7d9072
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [docs/code_specs/files/src/recovery/generation_retirement.cpp.md](generation_retirement.cpp.md), [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md) |
