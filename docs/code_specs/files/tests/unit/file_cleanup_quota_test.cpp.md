# `tests/unit/file_cleanup_quota_test.cpp` — block usage map

[Source](../../../../../tests/unit/file_cleanup_quota_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2e6442b07d11e6e88974d82e48d10acd58afa0322393056c1f113c86845724c7`. 76 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/file_cleanup_quota_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Repeat EINTR at ordinary post-link unlink and its emergency cleanup. Record · [reviewed contract](#b0001) |
| [B0002 · 18–34](../../../../../tests/unit/file_cleanup_quota_test.cpp#L18) | Type/record definition: struct Interrupt | returns result; static_cast&lt;Interrupt*&gt;(context)-&gt;visit&lt;jp::testing::FileEvent,jp::testing::FileDecision&gt;(e…; source comment (unverified): // Repeat EINTR at ordinary post-link unlink and its emergency cleanup. Record · [reviewed contract](#b0002) |
| [B0003 · 35–36](../../../../../tests/unit/file_cleanup_quota_test.cpp#L35) | Explanatory comments or spacing. | source comment (unverified): // All three owners must fail at the configured quota, report the bounded · [reviewed contract](#b0003) |
| [B0004 · 37–72](../../../../../tests/unit/file_cleanup_quota_test.cpp#L37) | Callable definition: void legacy_owners(const jp::Header& header) | calls resource::MemoryAccount::create, crown::journal_file_test::descriptors, jp::testing::set_file_hook, jp::File::create; guard jp::testing::set_file_hook(nullptr,nullptr);assert(failed && hook.last==cap+8 && hook.unlinks&gt;8);; source comment (unverified): // All three owners must fail at the configured quota, report the bounded · [reviewed contract](#b0004) |
| [B0005 · 73–73](../../../../../tests/unit/file_cleanup_quota_test.cpp#L73) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 74–76](../../../../../tests/unit/file_cleanup_quota_test.cpp#L74) | Callable definition: int main(int argc,char** argv) | calls assert, frames, legacy_owners; guard assert(argc==2);const crown::journal_file_test::Frames frames(argv\[1\]);legacy_owners(frames.binding… · [reviewed contract](#b0006) |

## B0001

[Lines 1–17](../../../../../tests/unit/file_cleanup_quota_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:f378d87edecbe00b81581e75a4bdf62c7f1d01ca69773925b7222155e5520221
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare file_cleanup_quota_test.cpp: include "journal_file_fixture.hpp", "journal_file_probe.hpp", "local_sink_probe.hpp", "generation_file_probe.hpp", "generation_detail.hpp", &lt;cassert&gt;, &lt;cerrno&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/file_cleanup_quota_test.cpp](../../../../../tests/unit/file_cleanup_quota_test.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–34](../../../../../tests/unit/file_cleanup_quota_test.cpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Interrupt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt three independent test syscall hooks to repeat EINTR only for temporary unlink and retain a shared ordinal/count observation. |
| inputs / outputs | Each callback receives one journal, local-sink, or generation event and returns that API's decision type with error_before=EINTR only at unlink_temporary. |
| invariants | Callbacks observe actual syscall attempts; they do not substitute a fake filesystem or allocator. The ordinal includes ordinary and emergency cleanup calls. |
| ownership | A stack Interrupt remains live until its hook is cleared; legacy_owners installs and clears one API hook at a time. |
| failure | The noexcept callbacks have no catch path; a dangling or wrong-context pointer would be a test bug, and after-phase decisions are not used to inject EINTR. |
| cost | The object stores two fixed counters; each callback returns a small value and performs no dynamic trace allocation. |
| Design | tests/unit/file_cleanup_quota_test.cpp:18-34, tests/support/journal_file_probe.hpp:4-17, tests/support/local_sink_probe.hpp:4-10, tests/support/generation_file_probe.hpp:4-17, src/recovery/journal_file.cpp:54-100, src/recovery/local_sink.cpp:65-108, src/recovery/generation.cpp:127-172 |

## B0003

[Lines 35–36](../../../../../tests/unit/file_cleanup_quota_test.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L36:sha256:a7333ed764a1583206cc6380645c19f04f803be1ed29dda233dd0c5ed7debf8e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: All three owners must fail at the configured quota, report the bounded cleanup failure, release their actual locks/FDs, and preserve linked bytes. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/file_cleanup_quota_test.cpp](../../../../../tests/unit/file_cleanup_quota_test.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 37–72](../../../../../tests/unit/file_cleanup_quota_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void legacy_owners(const jp::Header& header) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Regress the operation-cap escape hatch for bounded emergency temporary cleanup in three existing file owners. |
| inputs / outputs | With operation limit 32 and repeated unlink EINTR, it expects journal, standalone local sink, and generation checkpoint publication to fail with limit plus cleanup-failed metadata at ordinal cap+8. |
| invariants | The journal/sink final linked headers remain reopenable and the generation candidate remains byte-exact without a published root. The test proves only these cleanup paths, not native replay or arbitrary unlink errors. |
| ownership | One fixture directory and 8 MiB account outlive the three sequential scopes. Hooks are cleared before reopening; reopened owners close before final FD/account baseline assertions. |
| failure | A quota failure is required after ordinary calls reach the cap and eight emergency calls return EINTR. Candidate temporary removal at the end belongs to Directory cleanup, not the tested production owner. |
| cost | Each case uses a 32-attempt ordinary quota plus at most eight cleanup attempts; actual account-backed file/header work and OS descriptors are used, with no allocator or filesystem fake. |
| Design | tests/unit/file_cleanup_quota_test.cpp:37-72, docs/journal-files.md:16-25, docs/journal-files.md:57-66, docs/local-sink.md:110-127, docs/generations.md:45-57, src/recovery/journal_file.cpp:54-139, src/recovery/local_sink.cpp:65-149, src/recovery/generation.cpp:127-249 |

## B0005

[Lines 73–73](../../../../../tests/unit/file_cleanup_quota_test.cpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L73:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in file_cleanup_quota_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/file_cleanup_quota_test.cpp](../../../../../tests/unit/file_cleanup_quota_test.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 74–76](../../../../../tests/unit/file_cleanup_quota_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load the frozen journal fixture argument and invoke the cross-owner quota regression. |
| inputs / outputs | The executable asserts one argument, constructs journal_file_test::Frames from that fixture directory, and passes its inspected header into legacy_owners. |
| invariants | The fixture supplies frozen header/input bytes while its commit frame is encoded by the production journal encoder; this harness does not independently construct all journal wire semantics. |
| ownership | Frames owns its strings and header through the call; the fixture encoder's temporary account is local to its constructor and file-test accounts are separate. |
| failure | Wrong argument count asserts; absent or malformed fixture data throws from the support fixture rather than yielding a false pass. |
| cost | It loads two small hex fixtures and encodes one commit before three bounded owner cases; fixture and actual file allocations are distinct from the 8 MiB receiving-account cap. |
| Design | tests/unit/file_cleanup_quota_test.cpp:74-76, tests/support/journal_file_fixture.hpp:27-40, tests/unit/file_cleanup_quota_test.cpp:37-72, docs/journal-files.md:16-25 |
