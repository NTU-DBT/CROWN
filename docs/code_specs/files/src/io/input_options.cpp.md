# `src/io/input_options.cpp` — block usage map

[Source](../../../../../src/io/input_options.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `b01abcdeea5b84ccfef41e10f20475fd9e7be48298d561f3b9f312ee0467ac3e`. 55 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../src/io/input_options.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 5–7](../../../../../src/io/input_options.cpp#L5) | Callable definition: AccountedInputOptions::Values::Values(const resource::MemoryAccount& account) :relation_tokens(resource::AccountedTextLess{},Toke… | calls relation_tokens, Tokens::allocator_type · [reviewed contract](#b0002) |
| [B0003 · 8–8](../../../../../src/io/input_options.cpp#L8) | Explanatory comments or spacing. | source comment (unverified): // Friend codec passes freshly prepared nested allocations under this same account. · [reviewed contract](#b0003) |
| [B0004 · 9–11](../../../../../src/io/input_options.cpp#L9) | Callable definition: AccountedInputOptions::AccountedInputOptions(const resource::MemoryAccount& account,Values&& input) :account_(account),values_(re… | calls account_, values_, std::move; growth make_accounted_shared; source comment (unverified): // Friend codec passes freshly prepared nested allocations under this same account. · [reviewed contract](#b0004) |
| [B0005 · 12–20](../../../../../src/io/input_options.cpp#L12) | Callable definition: AccountedInputOptions::Values::Values(const resource::MemoryAccount& account,const InputOptions& input) :format(input.format),lim… | calls format, limits, table, delimiter; growth copy_of, emplace; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 21–23](../../../../../src/io/input_options.cpp#L21) | Callable definition: AccountedInputOptions::AccountedInputOptions(const resource::MemoryAccount& account,const InputOptions& input) :account_(account)… | calls account_, values_; growth make_accounted_shared · [reviewed contract](#b0006) |
| [B0007 · 24–32](../../../../../src/io/input_options.cpp#L24) | Callable definition: AccountedInputOptions::Values::Values(const resource::MemoryAccount& account,const Values& input) :format(input.format),limits(in… | calls format, limits, table, delimiter; growth copy_of, emplace; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 33–35](../../../../../src/io/input_options.cpp#L33) | Callable definition: AccountedInputOptions::AccountedInputOptions(const resource::MemoryAccount& account,const AccountedInputOptions& input) :account_… | calls account_, values_, get; growth make_accounted_shared · [reviewed contract](#b0008) |
| [B0009 · 36–38](../../../../../src/io/input_options.cpp#L36) | Callable definition: const AccountedInputOptions::Values& AccountedInputOptions::get() const noexcept | calls ; returns values_?*values_:empty · [reviewed contract](#b0009) |
| [B0010 · 39–39](../../../../../src/io/input_options.cpp#L39) | Explanatory comments or spacing. | source comment (unverified): // Explicit ordinary DTO export; retained native map/text ownership stays separate. · [reviewed contract](#b0010) |
| [B0011 · 40–48](../../../../../src/io/input_options.cpp#L40) | Callable definition: InputOptions AccountedInputOptions::export_value() const | calls get, emplace, std::string, view; returns result; growth emplace; 1 loop sites; source comment (unverified): // Explicit ordinary DTO export; retained native map/text ownership stays separate. · [reviewed contract](#b0011) |
| [B0012 · 49–54](../../../../../src/io/input_options.cpp#L49) | Callable definition: bool AccountedInputOptions::same_values(const AccountedInputOptions& other) const noexcept | calls get; returns a.format==b.format && a.limits==b.limits && a.table==b.table && a.delimiter==b.delimiter && a.heade… · [reviewed contract](#b0012) |
| [B0013 · 55–55](../../../../../src/io/input_options.cpp#L55) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0013) |

## B0001

[Lines 1–4](../../../../../src/io/input_options.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L4:sha256:2de61a8c4af408e98bdb174300b0511cb024a5e77191644116a1b1b24415655b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/input_options.hpp, crown/io/input_progress.hpp) and opens crown::io scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [docs/code_specs/files/src/io/input_options.cpp.md](input_options.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0002

[Lines 5–7](../../../../../src/io/input_options.cpp#L5); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputOptions::Values::Values(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize an empty native relation-token map under an existing query account. |
| inputs / outputs | Values(account) installs AccountedTextLess and a map allocator using immutable_metadata purpose and input memory_owner. |
| invariants | No catalog/options validity is proved; empty construction does not reserve map nodes or create another account. |
| ownership | Allocator retains the supplied controller; no key text/node storage exists until insertion. |
| failure | Handle/comparator construction has no explicit throw path; later nested allocations can fail under the account. |
| cost | Fixed empty map/allocator setup, no token/name scan or heap node allocation. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 8–8](../../../../../src/io/input_options.cpp#L8); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L8:sha256:70b30637364801a3e52a5d13b867380aaf3e525fe24ac880d16ba4fd198d9c09
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Friend codec passes freshly prepared nested allocations under this same account. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/input_options.cpp lines 6-10; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [docs/code_specs/files/src/io/input_options.cpp.md](input_options.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0004

[Lines 9–11](../../../../../src/io/input_options.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputOptions::AccountedInputOptions(const resource::MemoryAccount& account,Values&& input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt codec-built native options without exporting an ordinary DTO. |
| inputs / outputs | Private constructor copies account handle and funds shared Values/control while moving the already prepared Values graph. |
| invariants | Only SessionImageAccess friend passes Values whose nested map/text allocations already use this same receiving account. This constructor does not independently validate/migrate nested allocator identity. |
| ownership | Shared immutable Values retains its actual funded map/text owners; no source InputOptions graph or original bytes are borrowed. |
| failure | Shared object/control admission/allocation failure releases prepared owners; caller codec established nested-account/semantic preconditions. |
| cost | One funded shared object/control allocation plus map/text ownership moves; no deep reparse, ordinary DTO mirror or extra token copy. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 12–20](../../../../../src/io/input_options.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputOptions::Values::Values(const resource::MemoryAccount& account,const InputOptions& input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-import ordinary input options into explicitly funded native owners. |
| inputs / outputs | Copies scalar format/limits/table/delimiter/header/operation/offset, inserts each copied relation-token text/ID and optional null/source text. |
| invariants | Copying options does not validate format/catalog/progress semantics or enforce source order. Native reader initialization validates those after ownership is retained. |
| ownership | Map nodes use immutable_metadata; AccountedText copies use default scalar_payload with input memory_owner. The supplied account funds every nested nonempty text and actual node request. |
| failure | Overflow/account-cap/allocation failure unwinds partially built map/text through RAII; no manual catch or fallback account. |
| cost | Visits/copies all token/source/null bytes and inserts ordered-map nodes, with O(tokens log tokens) comparisons including compared string prefixes and real allocator framing. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 21–23](../../../../../src/io/input_options.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputOptions::AccountedInputOptions(const resource::MemoryAccount& account,const InputOptions& input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct immutable native options and their shared control under one existing account. |
| inputs / outputs | Funds shared Values/control and invokes Values(account, InputOptions) for the nested deep import. |
| invariants | The ordinary public DTO is caller-owned and may expire afterward; no input semantic authority arises merely from copying it. |
| ownership | Wrapper retains account plus shared_ptr&lt;const Values&gt;; every nested map/text request is explicitly funded by the same account. |
| failure | Partial construction/deep-copy failure returns no wrapper and releases built owners via standard shared/map RAII. |
| cost | Shared object/control allocation plus all nested text/map import costs; an implicit ordinary wrapper copy later shares these owners instead of cloning them. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 24–32](../../../../../src/io/input_options.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputOptions::Values::Values(const resource::MemoryAccount& account,const Values& input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-clone a native Values graph into an explicitly selected account. |
| inputs / outputs | Copies scalar options and deep-copies every token and optional null/source text using supplied account rather than source text copy constructors. |
| invariants | Explicit rehome is distinct from cheap shared wrapper copying; it preserves values while replacing actual nested allocation ownership. It does not itself validate formats/source/catalog. |
| ownership | New map nodes and text blocks belong to destination account; source Values remains independent and unchanged. |
| failure | Account/overflow/allocation failure unwinds local partial graph; no source mutation, budget refill or ordinary export. |
| cost | Full metadata/text copying and ordered-map insertions; old and destination graphs coexist at peak until actual releases. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 33–35](../../../../../src/io/input_options.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedInputOptions::AccountedInputOptions(const resource::MemoryAccount& account,const AccountedInputOptions& input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an independent funded options clone from another immutable wrapper. |
| inputs / outputs | Uses input.get() and the supplied account to construct/fund shared Values with the explicit deep-clone constructor. |
| invariants | Default/empty input contributes static default values; nonempty input is not silently shared across accounts through this overload. |
| ownership | Result owns new funded shared control/map/text. Ordinary same-type copy instead shares original Values/account handles. |
| failure | Account/allocation/overflow failure returns no clone; source wrapper remains unchanged. |
| cost | Shared allocation plus full token/text clone and map comparison costs; no source-schema scan or stream access. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 36–38](../../../../../src/io/input_options.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const AccountedInputOptions::Values& AccountedInputOptions::get() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable native options or static read-only defaults. |
| inputs / outputs | Returns *values_ when present, otherwise one static const Values empty with default settings. |
| invariants | Default settings are not an admitted account/control owner. Caller must check account() where native same-account retention is required. |
| ownership | Nonempty result borrows shared Values; retain a wrapper owner while using it. Static fallback has program lifetime and an empty unallocated map. |
| failure | Declared noexcept; no rejection or dynamic default-owner fallback is performed. |
| cost | Fixed shared-pointer branch/reference return; no options graph copy, stream read or successful per-call allocation. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 39–39](../../../../../src/io/input_options.cpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L39:sha256:538161b50e8888be89eb09c57e4f0f46e84fd95ff7d51b8da3f6b98193055787
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Explicit ordinary DTO export; retained native map/text ownership stays separate. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/input_options.cpp lines 37-41; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [docs/code_specs/files/src/io/input_options.cpp.md](input_options.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0011

[Lines 40–48](../../../../../src/io/input_options.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputOptions AccountedInputOptions::export_value() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export immutable native options to a caller-editable ordinary DTO. |
| inputs / outputs | Copies scalars, converts every token/source/null AccountedText view to std::string and populates an ordinary InputOptions map. |
| invariants | This export does not preserve native account ownership or confer catalog/progress authority on edited options. |
| ownership | Returned ordinary map/strings own independent bytes; source wrapper remains retained/unchanged and its native account is not charged for ordinary export allocation. |
| failure | Ordinary allocation failures discard local DTO; no native source/option mutation or retry. |
| cost | Visits/deep-copies all names/text and inserts map nodes, with actual ordered comparison/string costs and ordinary allocation. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 49–54](../../../../../src/io/input_options.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedInputOptions::same_values(const AccountedInputOptions& other) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete immutable option values without comparing account authority. |
| inputs / outputs | Compares format/limits/table/delimiter/header/operation, token map, optional null/source text and byte_offset using get defaults as needed. |
| invariants | Equal values can belong to different accounts or an empty/default wrapper; same_values is not permission to retain foreign-account options or accept source progress. |
| ownership | Reads existing immutable graphs; returned bool retains no owner and creates no clone. |
| failure | Declared noexcept with scalar/map/AccountedText comparisons that own no new text; no semantic validation/catch. |
| cost | Short-circuits differences; equal maps/text can require O(token count plus compared byte lengths), not universally O(1). No heap allocation on successful comparison. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/resource/text.hpp](../../../../../include/crown/resource/text.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/session_image_detail.hpp](../../../../../src/recovery/session_image_detail.hpp), [docs/ingestion.md](../../../../ingestion.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 55–55](../../../../../src/io/input_options.cpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L55:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/input_options.cpp](../../../../../src/io/input_options.cpp), [docs/code_specs/files/src/io/input_options.cpp.md](input_options.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
