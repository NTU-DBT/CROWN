# `tests/unit/journal_file_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/journal_file_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4440afc6696f38380c26a35abc7baba9587388a0fe07e2a9b186f3ba57d79bbf`. 146 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/journal_file_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 9–26](../../../../../tests/unit/journal_file_fault_test.cpp#L9) | Type/record definition: struct Hook | returns result · [reviewed contract](#b0002) |
| [B0003 · 27–30](../../../../../tests/unit/journal_file_fault_test.cpp#L27) | Type/record definition: struct Installed |  · [reviewed contract](#b0003) |
| [B0004 · 31–31](../../../../../tests/unit/journal_file_fault_test.cpp#L31) | Type/record definition: enum class Mode |  · [reviewed contract](#b0004) |
| [B0005 · 32–32](../../../../../tests/unit/journal_file_fault_test.cpp#L32) | Callable definition: const char* name(Mode mode) | calls ; returns @; @ · [reviewed contract](#b0005) |
| [B0006 · 33–38](../../../../../tests/unit/journal_file_fault_test.cpp#L33) | Callable definition: std::string initial(Mode mode,const Frames& f) | calls substr; returns {}; f.header+f.input+f.commit · [reviewed contract](#b0006) |
| [B0007 · 39–39](../../../../../tests/unit/journal_file_fault_test.cpp#L39) | Callable definition: void setup(Mode mode,const std::string& path,const Frames& f) | calls std::filesystem::remove, put, initial · [reviewed contract](#b0007) |
| [B0008 · 40–46](../../../../../tests/unit/journal_file_fault_test.cpp#L40) | Callable definition: void exercise(Mode mode,const std::string& path,const Frames& f,const resource::MemoryAccount& account,jp::FileLimits limits={}) | calls jp::File::create, close, jp::File::open, append · [reviewed contract](#b0008) |
| [B0009 · 47–56](../../../../../tests/unit/journal_file_fault_test.cpp#L47) | Callable definition: void surviving(Mode mode,const std::string& path,const Frames& f,const resource::MemoryAccount& account) | calls std::filesystem::exists, check, contents, initial; guard if(!std::filesystem::exists(path)){check(mode==Mode::create,"existing journal disappeared");return;} · [reviewed contract](#b0009) |
| [B0010 · 57–59](../../../../../tests/unit/journal_file_fault_test.cpp#L57) | Callable definition: Hook trace(Mode mode,const std::string& path,const Frames& f,const resource::MemoryAccount& account) | calls setup, install, exercise; returns hook · [reviewed contract](#b0010) |
| [B0011 · 60–72](../../../../../tests/unit/journal_file_fault_test.cpp#L60) | Callable definition: jp::FileOutcome expected_outcome(Mode mode,const Hook& trace,std::uint64_t point) | calls ; returns point&lt;link?jp::FileOutcome::unchanged:point&lt;=directory?jp::FileOutcome::unknown:jp::FileOutcome::du…; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 73–129](../../../../../tests/unit/journal_file_fault_test.cpp#L73) | Callable definition: void faults(const Frames& f) | calls file, resource::MemoryAccount::create, trace, setup; guard {Installed install(failure);s04_alloc::Scope count;try{exercise(mode,path,f,account);}catch(const j…; returns !e.after && e.stage==stage; 7 loop sites; source comment (unverified): // Errors after an actual commit write leave that commit recoverable even · [reviewed contract](#b0012) |
| [B0013 · 130–144](../../../../../tests/unit/journal_file_fault_test.cpp#L130) | Callable definition: void crashes(const Frames& f) | calls file, resource::MemoryAccount::create, trace, setup; guard setup(mode,path,f);const pid_t child=::fork();check(child&gt;=0,"crash fork failed");; 4 loop sites · [reviewed contract](#b0013) |
| [B0014 · 145–145](../../../../../tests/unit/journal_file_fault_test.cpp#L145) | Closes surrounding scope/type. |  · [reviewed contract](#b0014) |
| [B0015 · 146–146](../../../../../tests/unit/journal_file_fault_test.cpp#L146) | Callable definition: int main(int argc,char** argv) | calls check, f, std::string_view, crashes; guard int main(int argc,char** argv){try{check(argc==3,"expected mode and fixtures");const Frames f(argv\[…; returns 1 · [reviewed contract](#b0015) |

## B0001

[Lines 1–8](../../../../../tests/unit/journal_file_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:040fef3bcbe54c2a2e483b1f5106e3bcb5a3449ab1fb4d8bae2e5fc98f33ed61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare journal_file_fault_test.cpp: include "journal_file_fixture.hpp", "journal_file_probe.hpp", "index_allocation.hpp", &lt;sys/wait.h&gt;, &lt;cerrno&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–26](../../../../../tests/unit/journal_file_fault_test.cpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Hook {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record and perturb actual journal-file test seams for error, short-transfer, interruption and process-exit cases. |
| inputs / outputs | Holds a fixed 8192-event trace, selected ordinal/sides, errno and transfer/entropy controls; static call returns a FileDecision or exits 77. |
| invariants | Trace recording stops at array capacity; fault/crash matching still uses event ordinals. Decisions are supplied at before events. For open_directory/open_file/create_temporary the File wrapper translates requested after-errors to before-errors; close-before errors still execute close. After-event result/errno already include that adjustment. |
| ownership | Callers keep the stack Hook alive for the lexical Installed registration. Installed borrows its pointer and does not extend its lifetime; the fixed trace owns values, not file/lock capabilities. |
| failure | The callback is noexcept and uses _exit for simulated process death; it cannot unwind fixture owners. Persistent EINTR and cleanup error are explicit controls. |
| cost | Constant callback work per observed event and fixed stack storage; it adds no instrumentation to non-test production targets. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp) |

## B0003

[Lines 27–30](../../../../../tests/unit/journal_file_fault_test.cpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope registration of one stack Hook in the journal-file testing seam. |
| inputs / outputs | Constructor installs Hook::call/context; destructor clears both callback and context. |
| invariants | The helper expects a single lexical, non-overlapping registration; it clears rather than restores an older callback. |
| ownership | Borrows Hook until destruction; Hook must outlive Installed. Normal exception unwinding resets registration. |
| failure | No local recovery/catch is needed; _exit deliberately bypasses the destructor in crash children. |
| cost | Two fixed callback-pointer registrations; no heap or file operation. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp) |

## B0004

[Lines 31–31](../../../../../tests/unit/journal_file_fault_test.cpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Mode {create,open,append,repair}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select which concrete journal-file operation the common fault harness exercises. |
| inputs / outputs | Four enum values feed setup, exercise, survival and expected-outcome classification. |
| invariants | Each value has a separate prior-byte image and allowed result set; the harness does not conflate append uncertainty with file creation. |
| ownership | Plain by-value test selector, with no owner or durable authority. |
| failure | Invalid enum values are outside fixture callers; name has a defensive diagnostic fallback. |
| cost | Constant-size selector. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [docs/journal-files.md](../../../../journal-files.md) |

## B0005

[Lines 32–32](../../../../../tests/unit/journal_file_fault_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(Mode mode)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render one fault-test operation name for progress output. |
| inputs / outputs | Maps the four Mode values to static literals and otherwise returns invalid. |
| invariants | The result is diagnostic text only and cannot change which operation is performed. |
| ownership | Returns a process-lifetime literal pointer; caller owns no string. |
| failure | No throwing conversion or exception-based enum mapping is used. |
| cost | Fixed switch. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [docs/journal-files.md](../../../../journal-files.md) |

## B0006

[Lines 33–38](../../../../../tests/unit/journal_file_fault_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string initial(Mode mode,const Frames& f)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the exact starting byte image for one operation mode. |
| inputs / outputs | Returns empty for create, header+Input+Commit for open, header+Input+20 Commit bytes for repair, and header+Input for append. |
| invariants | The repair fixture intentionally has an incomplete Commit while retaining a complete pending Input. |
| ownership | Returns an owning ordinary std::string assembled from caller-owned frame bytes. |
| failure | Ordinary test string allocation failures propagate; no file has been changed by this helper. |
| cost | Copies the selected bounded frame extents; it is test preparation outside measured production file buffers. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp) |

## B0007

[Lines 39–39](../../../../../tests/unit/journal_file_fault_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void setup(Mode mode,const std::string& path,const Frames& f)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset the destination to the chosen independent fault-trial starting state. |
| inputs / outputs | Removes any old test file and writes initial bytes except in create mode. |
| invariants | Callers close earlier File owners before invoking setup; this bypass is only fixture construction in a private directory. |
| ownership | Borrows path/Frames; filesystem data is owned by the fixture directory. |
| failure | Filesystem or checked fixture-write failure escapes and fails the test. |
| cost | One removal plus at most one complete bounded image write. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp) |

## B0008

[Lines 40–46](../../../../../tests/unit/journal_file_fault_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exercise(Mode mode,const std::string& path,const Frames& f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the actual File create/open/append/repair path under caller-supplied limits and hook. |
| inputs / outputs | Create mode creates/closes; other modes open, optionally append the Commit or repair the tail, then checked-close. |
| invariants | Uses real production APIs and explicit close; no mock filesystem result is substituted for subsequent survivor inspection. |
| ownership | A local move-only File owns descriptor/flock/account buffers until checked close or unwinding. |
| failure | File/codec/account failures propagate unchanged to the surrounding trial, where the expected outcome is checked. |
| cost | Actual bounded file I/O/scan work for the selected mode; wrapper dispatch is constant. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0009

[Lines 47–56](../../../../../tests/unit/journal_file_fault_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void surviving(Mode mode,const std::string& path,const Frames& f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reopen and validate an allowed old/new journal image after an error or child exit. |
| inputs / outputs | Reads actual surviving bytes and compares mode-specific possibilities; then opens with the real expected header and checks progress/pending state. |
| invariants | Only create may leave no destination. Repair must preserve the complete pending Input; all modes forbid minting a command beyond one. Reopen adopts/syncs the actual complete visible prefix. |
| ownership | Owns a temporary file-content string and a new healthy File, with no reuse of a poisoned writer. |
| failure | Unexpected bytes/progress or inability to reopen fail the fixture. This helper does not silently repair the suffix. |
| cost | Whole-file comparison plus a complete reopen scan/sync for each trial. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [docs/journal-files.md](../../../../journal-files.md) |

## B0010

[Lines 57–59](../../../../../tests/unit/journal_file_fault_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Hook trace(Mode mode,const std::string& path
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe one successful bounded operation to determine actual fault/crash ordinals. |
| inputs / outputs | Resets the fixture, installs a default Hook, executes the selected production path and returns its fixed trace. |
| invariants | The baseline is specific to this mode and fixture; later loops cover those observed ordinals, not every possible system workload. |
| ownership | Registration ends before the returned Hook is copied/moved; no pointer to the local survives. |
| failure | A baseline operation failure escapes instead of inventing a trace. |
| cost | One complete fixture reset and operation plus fixed trace copy/move. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [tests/support/journal_file_probe.hpp](../../../../../tests/support/journal_file_probe.hpp) |

## B0011

[Lines 60–72](../../../../../tests/unit/journal_file_fault_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
jp::FileOutcome expected_outcome(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify the file API outcome expected at one ordinal of a known baseline trace. |
| inputs / outputs | Finds link/directory-sync/write-or-truncate/file-sync ordinals, then returns unchanged, unknown or durable for the mode/point. |
| invariants | Input trace must be the successful matching mode. Classification concerns the attempted File operation; it does not declare all visible unsynced bytes durable. |
| ownership | Borrows fixed trace values, retaining no owner or file handle. |
| failure | This comparison helper performs no I/O and no repair; a mismatch is rejected by its caller. |
| cost | Linear scan of the recorded events per classification, so sweeping all points adds quadratic trace-comparison work in the test. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp) |

## B0012

[Lines 73–129](../../../../../tests/unit/journal_file_fault_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void faults(const Frames& f)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep actual file syscall error positions and exceptional I/O controls while checking uncertainty and cleanup. |
| inputs / outputs | For four modes, injects both error sides at each observed operation, lower operation caps, EINTR and short transfers; also tests poisoned append, partial write, zero progress, bounded entropy-name collision and failed cleanup. |
| invariants | Per-ordinal EIO trials recheck descriptors/account residency/temporary names and actual survivor bytes. Quota, EINTR, short-I/O and special controls check their explicit local subsets. An uncertain writer cannot retry; a complete written Commit is recovered through reopen, while only incomplete tails are repairable. Cleanup failure is explicit. |
| ownership | Trial-local Hook registration and Files close before setup/reopen. Failed cleanup leaves temporary names only for explicit fixture cleanup. |
| failure | Checks FileFailure outcome/category and cleanup metadata separately. The ENOENT exception used in generation tests is not assumed here; each selected File syscall injection must reject. |
| cost | Many bounded file resets/operations/reopens plus per-point trace classification; all observed-error, cap and special-control loops are test-only, with no CPU/durability theorem. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [docs/journal-files.md](../../../../journal-files.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0013

[Lines 130–144](../../../../../tests/unit/journal_file_fault_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void crashes(const Frames& f)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exit a child process before and after every observed journal-file syscall and validate its survivor in the parent. |
| inputs / outputs | For each mode/baseline ordinal/side, forks a child with crash_at and checks exit77, then runs surviving and removes private orphan temporaries. |
| invariants | The hook must be reached at the selected actual boundary. Tests process termination and lock release on the current filesystem, not power-loss behavior or an external sink. |
| ownership | Parent owns fixture paths/account; child receives forked state and _exit bypasses C++ cleanup. Parent reopens with a fresh File. |
| failure | Wrong exit status or invalid survivor bytes/state fails; unexpected child exceptions exit3 and missed hooks exit4. |
| cost | Two child processes per observed ordinal per mode, each with actual filesystem operations and a parent reopen. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [docs/journal-files.md](../../../../journal-files.md) |

## B0014

[Lines 145–145](../../../../../tests/unit/journal_file_fault_test.cpp#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L145:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in journal_file_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 146–146](../../../../../tests/unit/journal_file_fault_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch journal syscall-error coverage or process-exit coverage over one Frames fixture. |
| inputs / outputs | Requires mode plus fixture-directory arguments; literal crash selects crashes, other strings select faults. |
| invariants | The dispatcher does not validate an enumerated command grammar beyond argument count; each selected group performs its own checks. |
| ownership | Frames and group-local owners remain lexical; test hooks clear on ordinary unwinding. |
| failure | Final std::exception handler prints a diagnostic and returns one. |
| cost | Fixed dispatch plus the selected finite sweep; no tests run by authoring this contract. |
| Design | [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp) |
