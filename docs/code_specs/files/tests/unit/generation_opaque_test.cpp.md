# `tests/unit/generation_opaque_test.cpp` — block usage map

[Source](../../../../../tests/unit/generation_opaque_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6a2df941708eab2619ec98e20bc51b1a15f4cab532e4100c7edb0034f6fd2938`. 120 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/generation_opaque_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../tests/unit/generation_opaque_test.cpp#L16) | Callable definition: std::array&lt;char,32&gt; id() | calls fill; returns value · [reviewed contract](#b0002) |
| [B0003 · 17–19](../../../../../tests/unit/generation_opaque_test.cpp#L17) | Callable definition: void put(const std::string& path,std::string_view bytes) | calls out, write, data, size; guard std::ofstream out(path,std::ios::binary\|std::ios::trunc);out.write(bytes.data(),static_cast&lt;std::st… · [reviewed contract](#b0003) |
| [B0004 · 20–20](../../../../../tests/unit/generation_opaque_test.cpp#L20) | Callable definition: std::string_view view(const ImageVector&lt;char&gt;& bytes) | calls data, size; returns {bytes.data(),bytes.size()} · [reviewed contract](#b0004) |
| [B0005 · 21–32](../../../../../tests/unit/generation_opaque_test.cpp#L21) | Type/record definition: struct Fixture | source comment (unverified): // Lower opaque publisher intentionally decodes no checkpoint/WAL. · [reviewed contract](#b0005) |
| [B0006 · 33–34](../../../../../tests/unit/generation_opaque_test.cpp#L33) | Explanatory comments or spacing. | source comment (unverified): // Only read-operation hooks are installed, after the root/lock owner exists. · [reviewed contract](#b0006) |
| [B0007 · 35–56](../../../../../tests/unit/generation_opaque_test.cpp#L35) | Type/record definition: struct Hook | guard assert(written==1 && closed==0);}; returns result; source comment (unverified): // Only read-operation hooks are installed, after the root/lock owner exists. · [reviewed contract](#b0007) |
| [B0008 · 57–60](../../../../../tests/unit/generation_opaque_test.cpp#L57) | Type/record definition: struct Installed |  · [reviewed contract](#b0008) |
| [B0009 · 61–63](../../../../../tests/unit/generation_opaque_test.cpp#L61) | Callable definition: template&lt;class Action&gt; void rejected(Action action) | calls action, assert; guard bool failed=false;try { action(); } catch(const GenerationFailure&) { failed=true; }assert(failed); · [reviewed contract](#b0009) |
| [B0010 · 64–91](../../../../../tests/unit/generation_opaque_test.cpp#L64) | Callable definition: void round_trip_and_limits() | calls resource::MemoryAccount::create, owner, id, read_checkpoint; guard assert(view(bytes)==f.payload && view(owner.read_plan(account))==f.descriptor);; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 92–118](../../../../../tests/unit/generation_opaque_test.cpp#L92) | Callable definition: void failures_and_identity() | calls resource::MemoryAccount::create, contents, owner, id; guard {detail::GenerationOwner owner(f.root,id(),false,{});Hook h;{Installed installed(h);auto bytes=owne…; 4 loop sites · [reviewed contract](#b0011) |
| [B0012 · 119–119](../../../../../tests/unit/generation_opaque_test.cpp#L119) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 120–120](../../../../../tests/unit/generation_opaque_test.cpp#L120) | Callable definition: int main() | calls round_trip_and_limits, failures_and_identity · [reviewed contract](#b0013) |

## B0001

[Lines 1–15](../../../../../tests/unit/generation_opaque_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:84b59a77bb5e83aa1bad73ed86e6f8e20ee54e2c4ddd6d32f96a636dbc6795ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare generation_opaque_test.cpp: include "generation_detail.hpp", "generation_file_probe.hpp", "journal_file_fixture.hpp", "index_allocation.hpp", "crown/ir/digest.hpp", &lt;cassert&gt;, &lt;cerrno&gt;, &lt;fcntl.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–16](../../../../../tests/unit/generation_opaque_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,32> id() { std::array<char,32> value{};value.fill('a');return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the fixed query identifier used to select the test generation root. |
| inputs / outputs | Returns 32 lowercase \`a\` bytes, a deterministic local fixture identity. |
| invariants | Only test data is represented; the helper does not authenticate a production descriptor. |
| ownership | Returns a fixed stack array by value. |
| failure | No failure path. |
| cost | Fixed 32-byte initialization. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

## B0003

[Lines 17–19](../../../../../tests/unit/generation_opaque_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void put(const std::string& path,std::string_view bytes) {
  std::ofstream out(path,std::ios::binary|std::ios::trunc);out.write(bytes.data(),static_cast<std::streamsize>(bytes.size()));assert(out);
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write exact binary fixture bytes to a private temporary file for later malformed-file probes. |
| inputs / outputs | Opens/truncates with binary mode, writes the requested view length and asserts stream success. |
| invariants | Preserves embedded NUL and arbitrary checkpoint payload bytes. |
| ownership | Temporary filesystem owns the written copy; caller retains input view during the write. |
| failure | Failed open/write is a test assertion; host filesystem errors are not production recovery results. |
| cost | O(payload bytes) test setup I/O. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

## B0004

[Lines 20–20](../../../../../tests/unit/generation_opaque_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view view(const ImageVector<char>& bytes) { return {bytes.data(),bytes.size()}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow exact bytes from the returned account-backed ImageVector for fixture assertions. |
| inputs / outputs | Returns data pointer and size without copying or interpreting the opaque payload. |
| invariants | The ImageVector owner must remain alive while the view is compared. |
| ownership | Test scope retains the vector through each assertion. |
| failure | No explicit failure path. |
| cost | O(1), no allocation. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

## B0005

[Lines 21–32](../../../../../tests/unit/generation_opaque_test.cpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
  Directory directory;
  std::string root=directory.file("opaque.root"),checkpoint=root+".g0000000000000001.ckpt",plan=root+".g0000000000000001.plan";
  std::string payload{"binary\0checkpoint",17},descriptor="opaque descriptor";
  explicit Fixture(bool with_plan=true,bool empty=false) {
    if(empty)payload.clear();
    detail::GenerationOwner owner(root,id(),true,{});
    owner.publish_checkpoint(1,payload);if(with_plan)owner.publish_plan(1,descriptor);
    GenerationRoot selected{id(),1,1,sha256_fixed(payload),0,1};if(with_plan)selected.plan_sha256=sha256_fixed(descriptor);
    owner.publish_root(selected); // Lower opaque publisher intentionally decodes no checkpoint/WAL.
  }
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an isolated generation root containing opaque checkpoint bytes and optionally a plan file. |
| inputs / outputs | Owns a temporary directory/root path, raw checkpoint payload with embedded NUL, descriptor-like plan bytes, and writes selected metadata with matching SHA values. |
| invariants | Uses lower \`GenerationOwner\` publication only to construct file/root fixtures; no descriptor parsing, SQL binding, WAL replay or admission is performed. |
| ownership | The Directory fixture owns temporary files; its GenerationOwner lock is scoped during initial publication. |
| failure | Filesystem setup assertions fail the test; \`empty\` mode permits a zero-length checkpoint and omits the plan. |
| cost | Test-only temp directory and small file writes. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

## B0006

[Lines 33–34](../../../../../tests/unit/generation_opaque_test.cpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L34:sha256:7fbac1c233e1ff6a49999948dc1f50e03aa1da9dd0f57dbaa339de759e03b556
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Only read-operation hooks are installed, after the root/lock owner exists. Fixed records keep hook observation itself outside the allocation seam. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 35–56](../../../../../tests/unit/generation_opaque_test.cpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L56:sha256:8271f37d079e8f55822c30061608c0f9cd3b6a5c05292d7027fa244eaea1bbbc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide test-only observation and fault injection for selected-file read syscalls. |
| inputs / outputs | Counts before-operation events; can inject before/after EIO, cap transfer size, or mutate checkpoint/root bytes on a completed read event. |
| invariants | Installed only after the real root/lock owner is constructed; mutation is an external fixture action, not a new production repair path. The external mutation branch captures pwrite and close status before checking that exactly one byte was written and close returned zero. Existing -UNDEBUG keeps these assertions active in Release; no production syscall wrapper or warning suppression is added. |
| ownership | Test hook context is a stack object whose lifetime covers Installed. If open succeeds, the callback attempts close immediately after pwrite and before asserting both results; it retains no mutation fd after a successful callback. |
| failure | Hook remains noexcept. If open succeeds, a failed/short pwrite or failed close aborts through assert rather than silently continuing. If open fails, no local mutation occurs and the existing encompassing expected GenerationFailure/done checks remain unchanged; no open error is converted into a production recovery result. |
| cost | Fixed counters/flags and optional test-only open, lseek, one-byte pwrite and close; no new production allocation, retry or query-update work. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

## B0008

[Lines 57–60](../../../../../tests/unit/generation_opaque_test.cpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {
  explicit Installed(Hook& hook) { testing::set_generation_hook(Hook::call,&hook); }
  ~Installed() { testing::set_generation_hook(nullptr,nullptr); }
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install and automatically clear the global generation syscall hook around one test scope. |
| inputs / outputs | Constructor selects Hook::call and context; destructor resets both hook slots. |
| invariants | RAII limits global fault injection to the exact owner call under test. |
| ownership | Borrows Hook until destructor; test scope must destroy Installed before Hook. |
| failure | No throwing cleanup; hook restoration is unconditional. |
| cost | Two hook pointer updates. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp) |

## B0009

[Lines 61–63](../../../../../tests/unit/generation_opaque_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void rejected(Action action) {
  bool failed=false;try { action(); } catch(const GenerationFailure&) { failed=true; }assert(failed);
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an opaque generation read fails with the generation subsystem’s failure type. |
| inputs / outputs | Runs one action and catches GenerationFailure; the helper does not inspect the particular fault/stage. |
| invariants | Callers’ surrounding checks establish expected file/root/account state; this helper alone proves only failure class. |
| ownership | Action-local owner/byte values unwind before the assertion completes. |
| failure | No GenerationFailure is an assertion failure; other exceptions propagate. |
| cost | Constant test bookkeeping around the operation. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp) |

## B0010

[Lines 64–91](../../../../../tests/unit/generation_opaque_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void round_trip_and_limits() {
  Fixture f;const auto account=resource::MemoryAccount::create(1024*1024);std::uint64_t operations=0,work=0,peak=0;
  {detail::GenerationOwner owner(f.root,id(),false,{});auto bytes=owner.read_checkpoint(account);
    assert(view(bytes)==f.payload && view(owner.read_plan(account))==f.descriptor);
    operations=owner.operations();work=owner.validation_work();peak=account.statistics().peak_requested_bytes;}
  assert(account.statistics().current.allocations==1);
  for(unsigned which=0;which<4;++which) {
    GenerationLimits limits;
    if(which==0)limits.operations=operations;
    if(which==1)limits.validation_work=work;
    if(which==2)limits.operations=operations-1;
    if(which==3)limits.validation_work=work-1;
    const auto before=descriptors();bool failed=false;
    try {detail::GenerationOwner owner(f.root,id(),false,limits);auto bytes=owner.read_checkpoint(account);auto plan=owner.read_plan(account);}
    catch(const GenerationFailure& error) {failed=error.fault()==GenerationFault::limit;}
    assert(failed==(which>=2) && descriptors()==before && account.statistics().current.allocations==1);
  }
  {auto exact=resource::MemoryAccount::create(peak);detail::GenerationOwner owner(f.root,id(),false,{});
    auto bytes=owner.read_checkpoint(exact);auto plan=owner.read_plan(exact);assert(exact.statistics().peak_requested_bytes==peak);}
  {auto low=resource::MemoryAccount::create(peak-1);bool failed=false;
    try {detail::GenerationOwner owner(f.root,id(),false,{});auto bytes=owner.read_checkpoint(low);auto plan=owner.read_plan(low);}
    catch(const resource::MemoryFailure& error) {failed=error.fault()==resource::MemoryFault::limit;}
    assert(failed && low.statistics().current.allocations==1);}
  {auto cap=GenerationLimits{};cap.checkpoint_bytes=f.payload.size()-1;detail::GenerationOwner owner(f.root,id(),false,cap);
    s04_alloc::Scope deny(0);rejected([&]{auto bytes=owner.read_checkpoint(account);});assert(s04_alloc::calls==0);}
  {Fixture empty(false,true);detail::GenerationOwner owner(empty.root,id(),false,{});
    assert(owner.read_checkpoint(account).empty());rejected([&]{auto bytes=owner.read_plan(account);});}
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify opaque checkpoint/plan reads, their separate caps, and receiving-account/work boundaries. |
| inputs / outputs | Reads selected checkpoint and plan into ImageVectors, measures combined operations/work and account peak, then tests exact and one-under operation/work/account grants, checkpoint byte cap, zero-byte checkpoint, and missing-plan rejection. |
| invariants | Checkpoint bytes are returned unchanged, including NUL; empty is valid at this lower file boundary. Plan remains nonempty and separately hash-bound. Work is bounded I/O/hash validation, not parser/SQL work. |
| ownership | Returned vectors are scoped and funded by the supplied account; after scopes close only the account controller allocation remains. |
| failure | Expected limit/missing-selection cases fail with GenerationFailure or MemoryFailure as asserted; one-under account failures leave no retained user allocation. |
| cost | Reads the small fixture files and measures requested bytes/operation/work counters; not CPU or global allocator accounting. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/recovery/generation.hpp](../../../../../include/crown/recovery/generation.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

## B0011

[Lines 92–118](../../../../../tests/unit/generation_opaque_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void failures_and_identity() {
  Fixture f;const auto account=resource::MemoryAccount::create(1024*1024);const auto root=contents(f.root);std::uint64_t count=0;
  {detail::GenerationOwner owner(f.root,id(),false,{});Hook h;{Installed installed(h);auto bytes=owner.read_checkpoint(account);assert(view(bytes)==f.payload);}count=h.count;}
  for(std::uint64_t point=1;point<=count;++point)for(const bool after:{false,true}) {
    const auto before=descriptors();
    {detail::GenerationOwner owner(f.root,id(),false,{});Hook h;h.fail=point;h.after=after;Installed installed(h);
      rejected([&]{auto bytes=owner.read_checkpoint(account);});}
    assert(descriptors()==before && account.statistics().current.allocations==1 && contents(f.checkpoint)==f.payload && contents(f.root)==root);
  }
  {detail::GenerationOwner owner(f.root,id(),false,{});Hook h;h.maximum=3;Installed installed(h);
    assert(view(owner.read_checkpoint(account))==f.payload);}
  for(unsigned kind=0;kind<3;++kind) {
    detail::GenerationOwner owner(f.root,id(),false,{});Hook h;h.mutate=kind==2?f.root.c_str():f.checkpoint.c_str();h.append=kind==1;
    {Installed installed(h);rejected([&]{auto bytes=owner.read_checkpoint(account);});}assert(h.done);
    put(f.checkpoint,f.payload);put(f.root,root);
  }
  for(const auto& bad:{f.payload.substr(0,3),f.payload+"extra",std::string(f.payload.size(),'x')}) {
    put(f.checkpoint,bad);detail::GenerationOwner owner(f.root,id(),false,{});rejected([&]{auto bytes=owner.read_checkpoint(account);});
  }
  put(f.checkpoint,f.payload);
  std::filesystem::remove(f.checkpoint);const auto victim=f.directory.file("victim");put(victim,f.payload);
  assert(::symlink(victim.c_str(),f.checkpoint.c_str())==0);
  {detail::GenerationOwner owner(f.root,id(),false,{});rejected([&]{auto bytes=owner.read_checkpoint(account);});}
  assert(contents(victim)==f.payload);std::filesystem::remove(f.checkpoint);std::filesystem::create_directory(f.checkpoint);
  {detail::GenerationOwner owner(f.root,id(),false,{});rejected([&]{auto bytes=owner.read_checkpoint(account);});}
  assert(account.statistics().current.allocations==1);account.check_invariants();
}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise opaque read syscall failure cuts, short transfers, file/root races, checksum and regular-file enforcement. |
| inputs / outputs | Injects every observed read operation failure before/after, allows a 3-byte transfer chunk, mutates checkpoint/root after read, tests short/extra/wrong bytes, symlink and directory replacements. |
| invariants | Every read must either return bytes matching selected root/hash/stamp/EOF or fail; failure does not publish/repair root or change fixture bytes. Coverage is for the read helper only. |
| ownership | Actual GenerationOwner retains root lock; Hook is test-only. Account-backed returned bytes are destroyed before leak/current checks. |
| failure | Expected failures are GenerationFailure; callback injection is per operation and surrounding assertions restore temporary fixtures. |
| cost | Many bounded fixture I/O attempts and SHA/file identity checks; not durable descriptor validation or replay. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [tests/support/generation_file_probe.hpp](../../../../../tests/support/generation_file_probe.hpp), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

## B0012

[Lines 119–119](../../../../../tests/unit/generation_opaque_test.cpp#L119); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L119:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in generation_opaque_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [docs/generations.md](../../../../generations.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 120–120](../../../../../tests/unit/generation_opaque_test.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {round_trip_and_limits();failures_and_identity();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the opaque selected-checkpoint round-trip/limit and fault/identity suites. |
| inputs / outputs | No command-line input; executes both independent test routines. |
| invariants | The oracle verifies the lower reader boundary only. It makes no claim that opaque bytes decode as a valid checkpoint or establish durable R2 recovery. |
| ownership | Test routines own their temporary roots, owners, hook contexts and account-backed buffers. |
| failure | Any assertion or uncaught exception fails the CTest process. |
| cost | Test-only filesystem/syscall-hook exercises over small fixture bytes. |
| Design | [tests/unit/generation_opaque_test.cpp](../../../../../tests/unit/generation_opaque_test.cpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |
