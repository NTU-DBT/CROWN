# `tests/unit/session_file_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/session_file_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a07114d691ceb371814457db7040d1072f0f0327494abe5a09d867ea0fd8a851`. 174 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/session_file_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 21–35](../../../../../tests/unit/session_file_fault_test.cpp#L21) | Callable definition: static testing::FileDecision call(const testing::FileEvent& event,void* pointer) noexcept | calls size, _exit; returns result · [reviewed contract](#b0002) |
| [B0003 · 36–36](../../../../../tests/unit/session_file_fault_test.cpp#L36) | Callable definition: void install() | calls testing::set_file_hook · [reviewed contract](#b0003) |
| [B0004 · 37–37](../../../../../tests/unit/session_file_fault_test.cpp#L37) | Callable definition: static void clear() | calls testing::set_file_hook · [reviewed contract](#b0004) |
| [B0005 · 38–38](../../../../../tests/unit/session_file_fault_test.cpp#L38) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 39–42](../../../../../tests/unit/session_file_fault_test.cpp#L39) | Type/record definition: struct Installed |  · [reviewed contract](#b0006) |
| [B0007 · 43–50](../../../../../tests/unit/session_file_fault_test.cpp#L43) | Callable definition: void assert_epoch(const Pair& pair,const std::string& path,std::uint64_t sequence) | calls QuerySession::restore_file, typed::grant, options, has_value; guard check(value-&gt;status().committed_sequence==sequence && value-&gt;progress().sequence==sequence,"publish…; growth insert, resize; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 51–90](../../../../../tests/unit/session_file_fault_test.cpp#L51) | Callable definition: void io_faults(bool indexed) | calls file, pair, publish_session_image, hook; guard {Installed hook(trace);s04_alloc::Scope deny(0);baseline=publish_session_image(path,pair.new_image,…; returns e.stage==stage && !e.after; 6 loop sites · [reviewed contract](#b0008) |
| [B0009 · 91–107](../../../../../tests/unit/session_file_fault_test.cpp#L91) | Callable definition: void crashes(bool indexed) | calls file, pair, hook, publish_session_image; guard Hook::clear();static_cast&lt;void&gt;(publish_session_image(path,pair.old_image,{},limits));const auto pr…; 2 loop sites; source comment (unverified): // Included: complete directory sync already happened. · [reviewed contract](#b0009) |
| [B0010 · 108–121](../../../../../tests/unit/session_file_fault_test.cpp#L108) | Callable definition: void namespace_collisions() | calls pair, file, std::string, hook; guard check(rejected && !std::filesystem::exists(path),"temporary basename collision exposed destination … · [reviewed contract](#b0010) |
| [B0011 · 122–139](../../../../../tests/unit/session_file_fault_test.cpp#L122) | Type/record definition: struct ChangeFile | returns {} · [reviewed contract](#b0011) |
| [B0012 · 140–154](../../../../../tests/unit/session_file_fault_test.cpp#L140) | Callable definition: void changing_files() | calls pair, file, publish_session_image, c_str; guard Hook::clear();check(change.changed && rejected && descriptors()==fds,"concurrent truncation/growth/…; returns !e.after && e.stage==FileStage::read_data; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 155–167](../../../../../tests/unit/session_file_fault_test.cpp#L155) | Callable definition: void cleanup_failures() | calls file, pair, hook, publish_session_image; guard check(event!=trace.events.begin()+static_cast&lt;std::ptrdiff_t&gt;(trace.size),"cleanup write trace miss…; returns !e.after && e.stage==FileStage::write_data; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 168–168](../../../../../tests/unit/session_file_fault_test.cpp#L168) | Closes surrounding scope/type. |  · [reviewed contract](#b0014) |
| [B0015 · 169–174](../../../../../tests/unit/session_file_fault_test.cpp#L169) | Callable definition: int main(int argc,char** argv) | calls check, std::string_view, namespace_collisions, changing_files; guard try {check(argc==2,"file fault mode missing");if(std::string_view(argv\[1\])=="collisions"){namespace…; returns 0; 1; 1 loop sites · [reviewed contract](#b0015) |

## B0001

[Lines 1–20](../../../../../tests/unit/session_file_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:199e92de8a4eb0dc24a9032b9afa40915ccf697663890dfd5b1e0505da1551f4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_file_fault_test.cpp: include "session_file_fixture.hpp", "checkpoint_file_probe.hpp", &lt;sys/wait.h&gt;, &lt;cerrno&gt;, &lt;csignal&gt;, &lt;fcntl.h&gt;; bind local aliases/name imports; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–35](../../../../../tests/unit/session_file_fault_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static testing::FileDecision call(const testing::FileEvent& event,void* pointer) noexcept {
    auto& self=*static_cast<Hook*>(pointer);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject one before/after syscall error, bounded transfer, entropy override, cleanup failure, or child exit through a fixed event recorder. |
| inputs / outputs | A callback receives borrowed FileEvent data, stores up to 4096 events, and returns FileDecision fields selected by ordinal/stage. |
| invariants | Events are actual checkpoint-file syscall attempts; after-events can mean the effect already occurred. The static array avoids allocating in the hook; callbacks are test-only, thread-local controls. |
| ownership | Installed hook borrows Hook context; caller keeps it alive through synchronous publication/load and clears the callback before scope end. |
| failure | Out-of-range events are detected by measured trace checks; configured child exit deliberately bypasses C++ cleanup. |
| cost | Fixed 4096-event storage is embedded in Hook; each callback is constant work; the OS file syscall is real and staging/load allocations are owned by the session API. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0003

[Lines 36–36](../../../../../tests/unit/session_file_fault_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void install()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register the current Hook for file tests and clear the callback explicitly. |
| inputs / outputs | install passes the static callback/context to the test-only setter; clear removes both. |
| invariants | The setter borrows context and is not a durable or production callback API. |
| ownership | Hook context lifetime belongs to the test caller; file implementation reads it only during hook-enabled calls. |
| failure | A stale callback would dangle; RAII wrapper clears it before local Hook destruction. |
| cost | One thread-local callback registration change; no file or query allocation. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0004

[Lines 37–37](../../../../../tests/unit/session_file_fault_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static void clear()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guarantee that a test hook is cleared after one file operation's lexical scope. |
| inputs / outputs | Construction installs Hook&, destruction clears it. |
| invariants | C++ exceptions unwind through cleanup; \`_exit\` in crash cases intentionally skips the destructor and terminates the process. |
| ownership | The hook context is borrowed from the surrounding scope and must outlive Installed. |
| failure | An \`_exit\` case cannot rely on Installed cleanup, so the next parent iteration clears explicitly. |
| cost | Two setter calls; no native file state is owned by this wrapper. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0005

[Lines 38–38](../../../../../tests/unit/session_file_fault_test.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_file_fault_test.cpp: struct Hook. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 39–42](../../../../../tests/unit/session_file_fault_test.cpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope test-hook lifetime over a file API operation. |
| inputs / outputs | RAII Installed stores no state; constructor receives Hook& and installs it, destructor clears the global test seam. |
| invariants | This only controls test instrumentation; it does not own descriptors, temporary names, or checkpoint bytes. |
| ownership | Caller owns the Hook and filesystem fixture for the entire Installed scope. |
| failure | If the process terminates through \`_exit\`, destructor is skipped by design. |
| cost | Constant-size wrapper and two setter operations. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0007

[Lines 43–50](../../../../../tests/unit/session_file_fault_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void assert_epoch(const Pair& pair,const std::string& path,std::uint64_t sequence)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a published checkpoint by restoring its native state and advancing one real next update. |
| inputs / outputs | Restores through QuerySession::restore_file, checks committed/source sequence and independent fixture oracle rows, then consumes one more update. |
| invariants | The loaded file must represent a complete usable CROWNSI1 session, not merely expected bytes or a reported publication state. |
| ownership | Restore result owns a new receiving account; Pair owns fixture plan/update definitions; row exports/database are test-side copies. |
| failure | Wrong epoch, source sequence, rows, indexed grant, or next-update behavior fails. |
| cost | Restores a bounded two-row image and executes one update; file buffer/native rebuild use receiving account, oracle Rows use ordinary memory. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0008

[Lines 51–90](../../../../../tests/unit/session_file_fault_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void io_faults(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault each actual save/load syscall side and check publication outcome, stable state, retries, short I/O, EINTR, and operation limits. |
| inputs / outputs | Measures publication and read traces with 64-byte chunks, injects before/after EIO at every ordinal, checks descriptor/temp cleanup and old/new artifact via restore, then tests short transfers, selected EINTR stages and every lower operation cap. |
| invariants | The publication enum distinguishes not-published, unknown rename result, visible-unsynced, and durable close errors; a complete new file can be visible before durability confirmation. |
| ownership | Session image already exists under the source query account; filesystem descriptors/temp names belong to API; Hook is borrowed; each successful restore owns a separate receiving account. |
| failure | Every injected failure must report expected FileFailure stage/state without leaking fds/temp or corrupting old/new complete state; zero-progress and insufficient operation quota reject. |
| cost | Loops are bounded by measured file syscall counts and operation quota; 64-byte chunks create multiple actual syscalls; native checkpoint image is reused, while file buffer/query restore use the API's actual accounts. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0009

[Lines 91–107](../../../../../tests/unit/session_file_fault_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void crashes(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fork and exit before/after every publication syscall, then classify the actual file through native restore. |
| inputs / outputs | Creates an initial valid image, records one publication trace, resets to old image, forks for each event side, exits child with code 77, and restores the parent-visible path. |
| invariants | Visibility is old before rename, new after rename; directory sync/close follows a visible complete file. This process-exit test is not a power-loss or hardware-cache simulation. |
| ownership | Fork child owns its Hook copy; parent owns Directory/Pair and does subsequent restore; directory names and inodes are shared. |
| failure | Unexpected exit code, wrong old/new epoch, or a non-restorable visible artifact fails; leftover private temps are explicitly removed by the fixture. |
| cost | One child per recorded syscall side; actual file publication and native restore repeat, but each trace is finite and bounded by the fixed image/chunk limit. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0010

[Lines 108–121](../../../../../tests/unit/session_file_fault_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void namespace_collisions()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise temporary-name collision, existing entry preservation, and leaf-symlink replacement with real filesystem objects. |
| inputs / outputs | Forces deterministic entropy, tests a colliding private basename, preserves a sentinel at an occupied temporary name, then publishes over a symlink entry. |
| invariants | Temporary creation must be exclusive; destination replacement is atomic entry replacement and must not follow the leaf symlink. |
| ownership | Directory owns all names; regular files/symlink inodes are OS-owned; publish API owns temporary descriptors only for each call. |
| failure | Collision must reject without exposing destination, sentinel must remain unchanged, and linked path must become a regular checkpoint while the other file remains old. |
| cost | Three bounded path operations and small string/file checks; syscall resources are actual OS objects, expected contents are test copies. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0011

[Lines 122–139](../../../../../tests/unit/session_file_fault_test.cpp#L122); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ChangeFile
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mutate the checkpoint inode once during the post-stat read hook to test stable-file validation. |
| inputs / outputs | Borrowed path and kind select one POSIX truncation, growth, or overwrite after the actual stat_read event. |
| invariants | A successful mutation is external test interference; it must cause restore rejection and never be mistaken for a coherent captured checkpoint. |
| ownership | The test path pointer borrows Directory's stable string; callback owns no descriptor beyond its short syscall scope. |
| failure | Failed open/write may leave changed=false and is exposed by the caller assertion; successful mutation followed by accepted restore is a failure. |
| cost | At most one open/mutation/close per hook and three mutations overall; the loader's file buffer/accounting belongs to restore, not this hook. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0012

[Lines 140–154](../../../../../tests/unit/session_file_fault_test.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void changing_files()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject in-place truncation/growth/overwrite during load, then prove EINTR reads resume at the same file position. |
| inputs / outputs | Runs each ChangeFile mutation during stat_read, verifies FileFailure/ImageFailure and descriptor closure, and injects EINTR at an actual read_data event. |
| invariants | Loader accepts an atomic old inode if replacement occurs, but these cases mutate the opened inode itself; stable metadata/size/checksum must reject inconsistent content. |
| ownership | Directory owns the file; callback borrows its path; restored session owns its account only on success. |
| failure | Each changed inode must reject; EINTR must be retried without losing offset or changing epoch. |
| cost | Three mutation cases plus one successful load trace/retry; buffers and native runtime are accounted by the loader; hook POSIX writes are real direct filesystem operations. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0013

[Lines 155–167](../../../../../tests/unit/session_file_fault_test.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cleanup_failures()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make cleanup unlink fail with EACCES and repeated EINTR and require bounded failure reporting with the old artifact intact. |
| inputs / outputs | First causes a write_data error, then injects cleanup_error at unlink_temporary; verifies not_published, temporary_cleanup_failed, original stage, descriptor count, and one remaining temp. |
| invariants | The caller must not infer rollback beyond rename; in this prepublication case old target remains valid, and the test manually removes the intentionally stranded private temp. |
| ownership | File API owns its descriptor and attempts bounded cleanup; Directory/test explicitly removes the residual name after asserting the failure report. |
| failure | Hidden cleanup failure, wrong publication/stage, leaked descriptor, missing surviving temp, or damaged old checkpoint fails. |
| cost | Two cleanup fault variants; API retries its documented bounded unlink quota (up to eight attempts); actual filesystem cleanup is explicit after inspection. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |

## B0014

[Lines 168–168](../../../../../tests/unit/session_file_fault_test.cpp#L168); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L168-L168:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_file_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 169–174](../../../../../tests/unit/session_file_fault_test.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select syscall crash, collision-only, or normal fault suites. |
| inputs / outputs | Requires one mode; \`collisions\` runs only namespace cases, \`crash\` runs process exits on both backends, and any other mode adds mutation/cleanup plus ordinary I/O faults. |
| invariants | The hook is installed only around actual file API calls; all fixture directories are lexical owners and cleaned after each scenario. |
| ownership | Every failure unwinds through the top-level exception handler except deliberate \`_exit\` in child processes, which the parent waits for. |
| failure | Missing/invalid argc, unexpected hook/file state, or any thrown invariant failure returns nonzero. |
| cost | Finite selection from two backend modes and measured syscall traces; all per-case files are bounded by test image and operation limits. |
| Design | [tests/unit/session_file_fault_test.cpp](../../../../../tests/unit/session_file_fault_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [tests/support/checkpoint_file_probe.hpp](../../../../../tests/support/checkpoint_file_probe.hpp), [docs/checkpoints.md § Atomic durable checkpoint files](../../../../checkpoints.md), [src/recovery/session_file.cpp](../../../../../src/recovery/session_file.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp) |
