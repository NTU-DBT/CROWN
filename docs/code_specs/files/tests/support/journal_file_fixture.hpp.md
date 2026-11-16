# `tests/support/journal_file_fixture.hpp` — block usage map

[Source](../../../../../tests/support/journal_file_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `21df93de34ba426835df35e1095aa4dc3bc4be99afb1f3dd9f2b85b0de71f104`. 41 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/support/journal_file_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../tests/support/journal_file_fixture.hpp#L12) | Callable definition: inline void check(bool condition,const char* message) | calls std::runtime_error; guard inline void check(bool condition,const char* message){if(!condition)throw std::runtime_error(messag… · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../tests/support/journal_file_fixture.hpp#L13) | Explanatory comments or spacing. | source comment (unverified): // Borrowed view: keep Encoded alive; converting it to string copies ordinary bytes. · [reviewed contract](#b0003) |
| [B0004 · 14–14](../../../../../tests/support/journal_file_fixture.hpp#L14) | Callable definition: inline std::string_view bytes(const jp::Encoded& value) | calls data, size; returns {value.bytes.data(),value.bytes.size()}; source comment (unverified): // Borrowed view: keep Encoded alive; converting it to string copies ordinary bytes. · [reviewed contract](#b0004) |
| [B0005 · 15–15](../../../../../tests/support/journal_file_fixture.hpp#L15) | Explanatory comments or spacing. | source comment (unverified): // Use one uncopied lexical owner; implicit copies duplicate the cleanup pathname. · [reviewed contract](#b0005) |
| [B0006 · 16–21](../../../../../tests/support/journal_file_fixture.hpp#L16) | Type/record definition: struct Directory | guard Directory(){char path\[\]="/tmp/crown-journal-XXXXXX";const auto result=::mkdtemp(path);check(result!…; returns name+@ +std::string(leaf); source comment (unverified): // Use one uncopied lexical owner; implicit copies duplicate the cleanup pathname. · [reviewed contract](#b0006) |
| [B0007 · 22–22](../../../../../tests/support/journal_file_fixture.hpp#L22) | Explanatory comments or spacing. | source comment (unverified): // Stream flags are unchecked here; callers inspect/assert the resulting fixture bytes. · [reviewed contract](#b0007) |
| [B0008 · 23–23](../../../../../tests/support/journal_file_fixture.hpp#L23) | Callable definition: inline std::string contents(const std::string& path) | calls f; returns {std::istreambuf_iterator&lt;char&gt;(f),{}}; source comment (unverified): // Stream flags are unchecked here; callers inspect/assert the resulting fixture bytes. · [reviewed contract](#b0008) |
| [B0009 · 24–24](../../../../../tests/support/journal_file_fixture.hpp#L24) | Callable definition: inline void put(const std::string& path,std::string_view data) | calls f, write, data, size; guard inline void put(const std::string& path,std::string_view data){std::ofstream f(path,std::ios::binar… · [reviewed contract](#b0009) |
| [B0010 · 25–25](../../../../../tests/support/journal_file_fixture.hpp#L25) | Callable definition: inline std::size_t descriptors() | calls std::filesystem::directory_iterator; returns n; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 26–26](../../../../../tests/support/journal_file_fixture.hpp#L26) | Callable definition: inline std::size_t temporaries(const Directory& directory) | calls std::filesystem::directory_iterator, path, filename, native; returns n; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 27–31](../../../../../tests/support/journal_file_fixture.hpp#L27) | Callable definition: inline std::string fixture(const std::string& directory,const char* leaf) | calls f, check, empty, size; guard std::ifstream f(directory+"/"+leaf+".hex");std::string text,result;f&gt;&gt;text;check(!text.empty() && t…; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 32–32](../../../../../tests/support/journal_file_fixture.hpp#L32) | Explanatory comments or spacing. | source comment (unverified): // Frozen header/input, but commit uses the production encoder and is not independent. · [reviewed contract](#b0013) |
| [B0014 · 33–40](../../../../../tests/support/journal_file_fixture.hpp#L33) | Type/record definition: struct Frames | source comment (unverified): // Frozen header/input, but commit uses the production encoder and is not independent. · [reviewed contract](#b0014) |
| [B0015 · 41–41](../../../../../tests/support/journal_file_fixture.hpp#L41) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::journal_file_test · [reviewed contract](#b0015) |

## B0001

[Lines 1–11](../../../../../tests/support/journal_file_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:e17cf25ef99fb1f3b1c919cf0bddca033b23d3698d6372eeb0c75f236fba5434
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare journal_file_fixture.hpp: include "crown/recovery/journal_file.hpp", &lt;algorithm&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;unistd.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–12](../../../../../tests/support/journal_file_fixture.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void check(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a journal fixture assertion with its diagnostic. |
| inputs / outputs | False throws runtime_error(message); true returns. |
| invariants | Only assertion evidence, not recovery classification or a proof handle. |
| ownership | message is borrowed during potential ordinary exception-message construction. |
| failure | runtime_error construction can allocate; false is intentionally fatal to the test boundary. |
| cost | Fixed branch on success; exception construction/unwind on failure. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 13–13](../../../../../tests/support/journal_file_fixture.hpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:f05ac09aacd874c4257f337a4734932b66c8018db4ebbaffa24176b92c438750
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Borrowed view: keep Encoded alive; converting it to string copies ordinary bytes. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 14–14](../../../../../tests/support/journal_file_fixture.hpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string_view bytes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow encoded journal bytes for immediate comparisons/copy. |
| inputs / outputs | Returns data/size view into jp::Encoded.bytes. |
| invariants | Encoded owner must outlive every view use; no temporary lifetime extension or validation occurs. |
| ownership | No byte copy or owner retention; funded Encoded remains the real owner. |
| failure | No explicit failure path; accessing an already dead owner is invalid caller use. |
| cost | Fixed view construction; downstream string assignment in Frames performs a separate ordinary copy. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 15–15](../../../../../tests/support/journal_file_fixture.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:9ad43632f5a25a219133769be8f37654d7436f05fa62a5fb78a6e1270fa38b75
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Use one uncopied lexical owner; implicit copies duplicate the cleanup pathname. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 16–21](../../../../../tests/support/journal_file_fixture.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Directory
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a temporary test-directory pathname and schedule best-effort recursive cleanup. |
| inputs / outputs | Constructor calls mkdtemp with a mutable template, checks success, then copies the returned path; file builds owning child path strings. |
| invariants | Actual callers use an uncopied lexical Directory. Implicit copy duplicates the path/cleanup responsibility; the user destructor suppresses implicit move. This is test setup, not a durable directory owner protocol. |
| ownership | String owns pathname only, not an open descriptor. Destructor removes filesystem entries; sessions in enclosing fixtures die before the Directory. |
| failure | mkdtemp/check or subsequent string allocation can fail; allocation after creation can leave a directory. remove_all(error_code) ignores filesystem error reporting but is not an allocation-free/no-terminate OOM guarantee. |
| cost | One real directory creation, pathname copy, and teardown proportional to remaining directory contents; ordinary filesystem/string allocations lie outside native query-account accounting. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

```text
  Directory(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the fixture's unique filesystem directory. |
| inputs / outputs | Passes a writable XXXXXX template to mkdtemp; copies the resulting path after a non-null check. |
| invariants | Template buffer remains live for the synchronous call and has a terminating NUL; no user pathname is interpreted. |
| ownership | On success the Directory string retains the path. Raw created directory precedes string ownership and is not guarded during failed string assignment. |
| failure | OS failure is asserted with runtime_error; ordinary allocation may throw after mkdir succeeded. Current callers create fixtures before injected failures. |
| cost | Fixed template preparation, one mkdtemp operation, and one ordinary pathname copy/allocation. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

```text
~Directory()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attempt to remove this test directory and its remaining files on scope exit. |
| inputs / outputs | Calls filesystem::remove_all(name,error_code) and ignores the returned count and error code. |
| invariants | Use one uncopied lexical instance; copies would attempt cleanup of the same path. This is cleanup convenience rather than a durability or descriptor-release assertion. |
| ownership | Destroys filesystem entries named by an owned string; does not close arbitrary session descriptors itself. |
| failure | Reported filesystem errors are deliberately ignored. The destructor is implicitly noexcept, and general allocation failure is not guaranteed impossible by error_code. |
| cost | Filesystem traversal/deletion proportional to remaining entries; library/path allocation may occur. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::string file(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an owning path beneath the temporary directory for trusted test leaf names. |
| inputs / outputs | Concatenates name, slash and leaf; default is state.wal. |
| invariants | Trusted leaf is not sanitized against slashes or traversal; this is not an untrusted path admission function. |
| ownership | Return owns independent ordinary string bytes; leaf/name are not retained as views. |
| failure | String/length allocation failures propagate; no filesystem operation is attempted. |
| cost | O(directory path + leaf bytes) copying and possible ordinary allocation. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 22–22](../../../../../tests/support/journal_file_fixture.hpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:6d4411b8e47fb769425ff3140fdf3d13d41e776d2c570e5418024841a7ff23ee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Stream flags are unchecked here; callers inspect/assert the resulting fixture bytes. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 23–23](../../../../../tests/support/journal_file_fixture.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string contents(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read fixture file contents into an ordinary owning byte string. |
| inputs / outputs | Opens binary ifstream and constructs string from streambuf iterators. |
| invariants | Default stream state is not checked here: unreadable input may yield empty/partial text. Callers must assert/inspect resulting content; this is not the checked production reader. |
| ownership | Local stream closes on exit; returned string owns bytes after the file/stream disappear. |
| failure | Ordinary allocations and exceptional stream/library failures propagate; default failbit/badbit alone are not translated. |
| cost | Real file read plus O(bytes) string construction/growth, with no native MemoryAccount or durable snapshot guarantee. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 24–24](../../../../../tests/support/journal_file_fixture.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void put(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a trusted test file with supplied bytes. |
| inputs / outputs | Binary truncating ofstream writes the view and checks stream state before destruction. |
| invariants | No fsync, atomic publication or close-error check; this intentionally edits test fixture files. |
| ownership | View is borrowed through write; stream owns its descriptor and returned function retains nothing. |
| failure | Open/write flag failure is asserted; allocation/stream exceptions propagate. Failure may leave a truncated/partial file. |
| cost | O(bytes) actual I/O plus ordinary stream/path allocations; no native account funding. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 25–25](../../../../../tests/support/journal_file_fixture.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::size_t descriptors()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe a Linux process descriptor count for relative leak assertions. |
| inputs / outputs | Iterates /proc/self/fd and returns number of entries observed. |
| invariants | Includes iterator's own descriptor and concurrent process changes; relative tests control their environment. This is not a native account or whole-process resource proof. |
| ownership | Iterator/path objects are local and owned; return is a scalar count. |
| failure | Filesystem iteration/open/allocation errors propagate; counter has no saturation guard for arbitrary unbounded input. |
| cost | O(open descriptors) directory traversal with actual filesystem/library allocation work. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 26–26](../../../../../tests/support/journal_file_fixture.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::size_t temporaries(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count the owner-specific temporary filename prefix in the test directory. |
| inputs / outputs | Scans entries whose filename begins .crown-journal-. |
| invariants | Matches only this prefix, not all temporary files or every leaked resource; caller supplies the live Directory. |
| ownership | Borrows Directory during scan and returns numeric count; iteration paths are transient owned objects. |
| failure | Filesystem/path allocation errors propagate; no cleanup or recovery is attempted. |
| cost | O(entries and inspected filename bytes) filesystem scan; not query operation/byte accounting. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 27–31](../../../../../tests/support/journal_file_fixture.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string fixture(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one frozen lowercase hexadecimal journal fixture into owning bytes. |
| inputs / outputs | Reads the first whitespace-delimited token at directory/leaf.hex, checks nonempty/even length, reserves half and decodes pairs. |
| invariants | Only lowercase 0..f accepted; trailing tokens are ignored. This validates hex shape, not journal checksum/schema/source authority. |
| ownership | Owns input text and result ordinary strings; returned bytes survive local input stream destruction. |
| failure | Missing/odd/invalid hex assertions and allocation failures propagate; no result on failure. |
| cost | O(token bytes) read/scan/decode, two ordinary buffers and result reserve. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 32–32](../../../../../tests/support/journal_file_fixture.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L32:sha256:c706d43e05b31bb9489c94ed5e3a37ead58fcb3dc3aed5b9af2f9066dacc71f8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Frozen header/input, but commit uses the production encoder and is not independent. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 33–40](../../../../../tests/support/journal_file_fixture.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Frames
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble frozen header/input and one production-encoded matching commit frame. |
| inputs / outputs | Reads header.hex and physical-input.hex, inspects bindings, encodes commit ordinal 2 with input ordinal/physical/command sequence 1. |
| invariants | Frozen header/input provide corpus independence; commit is made by production jp::encode and is not an independent wire encoder. |
| ownership | Three ordinary strings and fixed Header are owned. Temporary encoded commit owns account-funded bytes, then commit=bytes(encoded) deep-copies before its account/owner dies. |
| failure | Fixture I/O/inspection/account creation/encode/copy failures propagate; no durable publication is performed by construction. |
| cost | Reads/scans two frozen frames; creates a 1 MiB limit account, encodes/inspects/checksums and ordinary-copies commit bytes. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

```text
explicit Frames(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the matching journal header/input/commit set. |
| inputs / outputs | Loads two fixtures, derives fixed binding and input hash via production inspect, creates one encoded commit and copies its view. |
| invariants | Commit links exactly inspected input hash and ordinal/sequence values; this is editable test data, not admission evidence. |
| ownership | Initializer strings own copies; local account/Encoded can expire after commit assignment. |
| failure | Any initializer or body failure unwinds completed owned members; ordinary directory fixture cleanup is separate. |
| cost | Full fixture reads plus two inspections, one account controller/encode allocation path and one ordinary commit copy. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/unit/journal_file_fault_test.cpp](../../../../../tests/unit/journal_file_fault_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal-files.md](../../../../journal-files.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 41–41](../../../../../tests/support/journal_file_fixture.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L41:sha256:6ef5edf82d05fa5349f9eabfeb2380f59c219c50a91cfc5e210e40d19b5660c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in journal_file_fixture.hpp: namespace crown::journal_file_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |
