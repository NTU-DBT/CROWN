# `tests/support/sql_aggregate_file_fixture.hpp` — block usage map

[Source](../../../../../tests/support/sql_aggregate_file_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `60c16b0bd6a5a22cc0b5c537fb73b6b1fbb7986ef6edae2fd7e99092922d4708`. 106 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Test-only lexical directory owner. Cleanup is best effort and runs outside · [reviewed contract](#b0001) |
| [B0002 · 21–28](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L21) | Type/record definition: struct Directory | guard char pattern\[\]="/tmp/crown-r2-files-XXXXXX";const auto path=::mkdtemp(pattern);assert(path);name=pa…; returns name+@ +std::string(leaf); source comment (unverified): // Test-only lexical directory owner. Cleanup is best effort and runs outside · [reviewed contract](#b0002) |
| [B0003 · 29–31](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L29) | Callable definition: inline void put(const std::string& path,std::string_view bytes) | calls out, write, data, size; guard std::ofstream out(path,std::ios::binary\|std::ios::trunc);out.write(bytes.data(),static_cast&lt;std::st… · [reviewed contract](#b0003) |
| [B0004 · 32–34](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L32) | Callable definition: inline std::string contents(const std::string& path) | calls in; returns {std::istreambuf_iterator&lt;char&gt;(in),std::istreambuf_iterator&lt;char&gt;()} · [reviewed contract](#b0004) |
| [B0005 · 35–37](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L35) | Callable definition: inline std::size_t descriptors() | calls std::filesystem::directory_iterator; returns count; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 38–42](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L38) | Callable definition: inline std::size_t temporaries(const Directory& dir) | calls std::filesystem::directory_iterator, path, filename, native; returns count; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 43–43](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L43) | Callable definition: inline ar::Hash hash(char value) | calls fill; returns result · [reviewed contract](#b0007) |
| [B0008 · 44–44](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L44) | Callable definition: inline Cell number(std::int64_t value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0008) |
| [B0009 · 45–46](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L45) | Explanatory comments or spacing. | source comment (unverified): // Genuine original SQL and actual native tree; record tests never fabricate a · [reviewed contract](#b0009) |
| [B0010 · 47–66](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L47) | Type/record definition: struct Schema | guard assert(std::holds_alternative&lt;frontend::SqlAggregateProgram&gt;(result));; returns ar::admit_into(receiving,std::move(program),*selected.tree,{},options); source comment (unverified): // Genuine original SQL and actual native tree; record tests never fabricate a · [reviewed contract](#b0010) |
| [B0011 · 67–71](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L67) | declares types or opens a type body. | source comment (unverified): // Three commands: a real nullable-key commit, a transport Reject at I2/C1, · [reviewed contract](#b0011) |
| [B0012 · 72–92](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L72) | Callable definition: explicit Packets(Schema& s) | calls program, number, push_back, ar::encode; guard const auto output=s.admitted.runtime.prepare_batch({1,edits}).commit();assert(output.output.size()=…; growth push_back · [reviewed contract](#b0012) |
| [B0013 · 93–95](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L93) | Callable definition: \[\[nodiscard\]\] static std::string prefix(const std::vector&lt;ar::Frame&gt;& frames,std::size_t count) | calls bytes; returns result; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 96–96](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L96) | Closes surrounding scope/type. |  · [reviewed contract](#b0014) |
| [B0015 · 97–99](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L97) | Callable definition: template&lt;class Action&gt; void refused(Action action) | calls action, assert; guard bool failed=false;try { action(); } catch(const std::exception&) { failed=true; }assert(failed); · [reviewed contract](#b0015) |
| [B0016 · 100–101](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L100) | Explanatory comments or spacing. | source comment (unverified): // Recompute both protected checksums so hostile complete frames reach actual · [reviewed contract](#b0016) |
| [B0017 · 102–105](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L102) | Callable definition: inline void reseal(std::string& bytes) | calls sha256_fixed, std::string_view, substr, std::copy; source comment (unverified): // Recompute both protected checksums so hostile complete frames reach actual · [reviewed contract](#b0017) |
| [B0018 · 106–106](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L106) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::sql_aggregate_file_test · [reviewed contract](#b0018) |

## B0001

[Lines 1–20](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:2acfad62fd6a5c44c49d48fb7ec56e3684f038158ade6ff62270bf445c40356a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_file_fixture.hpp: include "crown/recovery/sql_aggregate_files.hpp", "crown/ir/digest.hpp", "crown/planner/oracle.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;cassert&gt;, &lt;cstdlib&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;string&gt;, &lt;vector&gt;, &lt;unistd.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/sql_aggregate_file_fixture.hpp](../../../../../tests/support/sql_aggregate_file_fixture.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–28](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Directory {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Give each file test an isolated actual temporary directory and a simple path builder. |
| inputs / outputs | Default construction calls mkdtemp and stores its returned path; file(leaf) returns a joined string, defaulting to file. |
| invariants | The object owns one lexical directory name; tests place their destinations and .crown-r2- temporaries beneath it, and the fixture does not model namespace recovery. |
| ownership | The std::string is owned by the stack fixture. Destruction calls remove_all after nested file owners leave scope and ignores its error_code. |
| failure | A failed mkdtemp trips an assertion. Cleanup is best effort, so an error can leave test files behind without changing a production owner. |
| cost | One directory creation and a small path-string construction are bounded by this fixture; filesystem removal walks only this test directory and is not a production cleanup guarantee. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:21-28, docs/sql_aggregate_files.md:27-33, src/recovery/sql_aggregate_file_detail.cpp:197-236 |

## B0003

[Lines 29–31](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void put(const std::string& path,std::string_view bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install raw bytes for malformed-prefix and external-change cases. |
| inputs / outputs | The helper accepts a pathname and borrowed byte span, opens binary/truncate mode, writes the span, and returns no value. |
| invariants | The caller-supplied bytes are the exact file preimage used by subsequent open/repair assertions; this helper does not construct a validated frame. |
| ownership | The stream is local and closes on return; the caller owns the path and source buffer for the duration of the write. |
| failure | The assert(out) checks stream state after write; with assertions disabled this helper would not report an output error separately. |
| cost | The test materializes its input buffers before this call and writes exactly bytes.size() bytes; stream buffering and kernel work are outside any memory-account claim. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:29-31, tests/unit/sql_aggregate_files_test.cpp:50-70, docs/sql_aggregate_files.md:94-111 |

## B0004

[Lines 32–34](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::string contents(const std::string& path) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual file bytes back for exact-prefix and no-mutation comparisons. |
| inputs / outputs | A path is opened in binary mode and the iterator range is returned as an independently owned std::string. |
| invariants | Tests compare all returned bytes; unreadable and empty files both yield an empty string because the helper does not separately assert open success. |
| ownership | The input pathname is borrowed; the return string and local input stream have ordinary lexical lifetimes. |
| failure | Open/read failure is not represented as a distinct error result, so callers must use surrounding expected-byte assertions to catch most failures. |
| cost | The returned string grows with file size and copies the complete fixture file; these bytes are ordinary test allocations, separate from owner-account accounting. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:32-34, tests/unit/sql_aggregate_files_test.cpp:16-46, tests/unit/sql_aggregate_files_fault_test.cpp:72-83, docs/sql_aggregate_files.md:35-41 |

## B0005

[Lines 35–37](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::size_t descriptors() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sample the process descriptor count around owner failures and closes. |
| inputs / outputs | It takes no argument and counts entries yielded by iterating /proc/self/fd. |
| invariants | The comparison is a test-local leak signal, not a stable global descriptor inventory; the iterator's own transient descriptor can participate in the count. |
| ownership | The directory iterator is scoped to the call and the returned integer outlives it; no owner descriptor is retained here. |
| failure | A missing /proc/self/fd or iterator error propagates as a filesystem exception rather than being translated into a test assertion. |
| cost | The helper walks entries proportional to visible descriptors and allocates implementation-dependent iterator state. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:35-37, tests/unit/sql_aggregate_files_fault_test.cpp:87-105, src/recovery/sql_aggregate_file_detail.cpp:35-40, docs/sql_aggregate_files.md:56-60 |

## B0006

[Lines 38–42](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::size_t temporaries(const Directory& dir) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count private R2 temporary-name entries left in one fixture directory. |
| inputs / outputs | The caller supplies a live Directory; the result counts entries whose native basename starts with .crown-r2-. |
| invariants | It measures names in this directory only and cannot distinguish live from orphaned temporary inodes or infer a successful destination publication. |
| ownership | The Directory remains caller-owned; each iterator entry is transient and only the count escapes. |
| failure | Filesystem enumeration errors propagate. A matching unrelated test file also increments the result because the predicate is prefix-only. |
| cost | One directory scan and filename-prefix checks scale with entries in this isolated directory; no contents are copied. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:38-42, src/recovery/sql_aggregate_file_detail.cpp:199-220, src/recovery/sql_aggregate_file_detail.cpp:231-235, tests/unit/sql_aggregate_files_fault_test.cpp:97-105 |

## B0007

[Lines 43–43](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline ar::Hash hash(char value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a deterministic fixed-width hash-shaped test value. |
| inputs / outputs | One character is repeated into every element of a value-initialized ar::Hash and returned by value. |
| invariants | The result is a synthetic identity/checksum fixture, not a digest of any frame or an authentication proof. |
| ownership | The fixed-size result is returned as a value and carries no reference to the input character. |
| failure | There is no data-dependent failure path; this helper does not validate that the repeated character is hexadecimal. |
| cost | Work and storage are fixed by ar::Hash width; it performs no frame hashing and creates no dynamic byte copy. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:43-43, tests/support/sql_aggregate_file_fixture.hpp:43-44, docs/sql_aggregate_records.md:1-25 |

## B0008

[Lines 44–44](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Cell number(std::int64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap integer scalars in the runtime cell representation used by fixture rows. |
| inputs / outputs | An int64_t becomes a storage::ScalarView returned through the Cell alias. |
| invariants | This constructs the nullable/runtime test value view expected by the SQL aggregate fixture; it is not a serialized cell image. |
| ownership | The returned scalar view is a value object; there is no heap-owned row or alias to a temporary buffer. |
| failure | The helper has no explicit validation or catch layer; conversion follows the scalar constructor contract. |
| cost | A single fixed-size scalar wrapper is formed; this helper does not allocate a tuple or charge a frame buffer. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:44-44, tests/support/sql_aggregate_file_fixture.hpp:16-18, tests/unit/sql_aggregate_files_test.cpp:92-103, docs/sql_aggregate_files.md:62-77 |

## B0009

[Lines 45–46](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L46:sha256:f46adb9abccd04f81118d5259ae4e8994d90037b02776d5b822be57021fbe9a6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Genuine original SQL and actual native tree; record tests never fabricate a descriptor from editable metadata. Capture is on for full before/after frames. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/sql_aggregate_file_fixture.hpp](../../../../../tests/support/sql_aggregate_file_fixture.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 47–66](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Schema {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a genuine bound SQL aggregate, selected native tree, and matching WAL/sink headers for file tests. |
| inputs / outputs | Default construction creates a 128 MiB MemoryAccount, binds the fixed query against catalog r(g,x), selects a minimum tree, admits capture-enabled runtime state, then fills query/descriptor/header identities. |
| invariants | The descriptor comes from the binder and selected actual tree; tests do not synthesize descriptor metadata. Capture is enabled so fixture commits yield complete before/after output frames. |
| ownership | The Schema stack object owns the receiving account, admitted descriptor/runtime and header values. Packets borrows it only while constructing retained Frame vectors. |
| failure | Binder choice, planner tree selection and admission are assertion-guarded in this fixture; allocation or runtime exceptions propagate to the test process. |
| cost | The account cap is 128 MiB, not a claim that setup consumes that amount. Binding, tree selection and runtime admission perform real native allocations charged to that account. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:47-66, docs/sql_aggregate_descriptor.md:1-45, src/recovery/sql_aggregate_wal_file.cpp:26-35, src/recovery/sql_aggregate_sink_file.cpp:64-70 |

## B0011

[Lines 67–71](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Packets {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the immutable frame sequence shared by behavioral and syscall-fault cases. |
| inputs / outputs | Construction fills wal with a header, three Inputs, one Commit, one Reject and another Commit; sink holds its header and two complete epochs. |
| invariants | The packet set includes a real nullable-key change, a transport-only Reject fixture, and a real empty no-op epoch. The Reject is not an independent native replay semantics proof. |
| ownership | The vectors own their Frame objects for the fixture lifetime; encoding uses the Schema account. Helper methods only borrow these vectors during calls. |
| failure | Frame encoding/runtime preparation failures propagate; prefix assumes a valid requested count and does not bounds-check it. |
| cost | The retained frame set is finite and small, but its encoded buffers and runtime commit rows are native account allocations; prefix strings add explicit byte copies. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:70-96, docs/sql_aggregate_files.md:62-83, src/recovery/sql_aggregate_wal_file.cpp:67-77, src/recovery/sql_aggregate_sink_file.cpp:94-122 |

## B0012

[Lines 72–92](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Packets(Schema& s) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the fixed WAL/sink scenarios from genuine runtime output and transport records. |
| inputs / outputs | A mutable Schema supplies account, program and headers; construction produces seven WAL frames and three sink frames with fixed sequence values in their bodies. |
| invariants | The first sink epoch is derived from a committed native batch. The middle WAL Reject only gives the file cursor a transport disposition; it does not validate semantic replay of that rejected input. |
| ownership | The constructor borrows Schema during encoding and commit preparation; finished Frames become owned by this Packets object. |
| failure | Assertions require one output from the nullable-key commit and successful fixture binding upstream; encode and account-denial exceptions are not hidden. |
| cost | It prepares two tiny runtime batches and encodes ten frames. Row/frame buffers are real native account allocations, unlike the fault hook's fixed observation array. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:72-92, docs/sql_aggregate_files.md:62-83, src/recovery/sql_aggregate_wal_file.cpp:67-77, src/recovery/sql_aggregate_sink_file.cpp:94-122 |

## B0013

[Lines 93–95](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static std::string prefix(const std::vector<ar::Frame>& frames,std::size_t count) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize an exact concatenation of the first N encoded fixture frames. |
| inputs / outputs | The method borrows a frame vector and count, then returns a new string containing frames\[0..count) bytes. |
| invariants | No header or boundary validation is performed, and the caller must provide count &lt;= frames.size(); callers use known fixture counts. |
| ownership | Frame storage remains caller-owned while each Frame::bytes() view is appended; the result string owns its copied bytes. |
| failure | An invalid count can index out of bounds, while string growth can propagate allocation failure; neither condition is translated here. |
| cost | The loop performs count appends and copies the sum of those frame sizes into one additional ordinary test string. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:93-95, tests/unit/sql_aggregate_files_test.cpp:50-64, tests/unit/sql_aggregate_files_fault_test.cpp:41-47, docs/sql_aggregate_files.md:43-47 |

## B0014

[Lines 96–96](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L96); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L96:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_file_fixture.hpp: struct Packets. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/sql_aggregate_file_fixture.hpp](../../../../../tests/support/sql_aggregate_file_fixture.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 97–99](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void refused(Action action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an operation exits by throwing some standard exception. |
| inputs / outputs | A callable is invoked once; the helper marks a caught std::exception as refusal and asserts that one occurred. |
| invariants | It deliberately does not distinguish FileFailure, ImageFailure, bad_alloc, or another standard exception; tests needing a category assert that separately. |
| ownership | The action closure and referenced owners remain with the caller for the synchronous invocation. |
| failure | A non-standard exception escapes, and assertions disabled would remove the helper's refusal check. |
| cost | One call and a boolean are added; exception construction/unwinding costs depend on the selected failing path and are not a cost measurement. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:97-99, tests/unit/sql_aggregate_files_test.cpp:16-46, include/crown/recovery/sql_aggregate_files.hpp:17-32, docs/sql_aggregate_files.md:133-136 |

## B0016

[Lines 100–101](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L100); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L100-L101:sha256:5cf139722f98e803c1e8c9b0e37da01299f5e33251e945423b6776104eda99ef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Recompute both protected checksums so hostile complete frames reach actual structure/sequence/schema checks rather than stopping at a stale digest. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/sql_aggregate_file_fixture.hpp](../../../../../tests/support/sql_aggregate_file_fixture.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 102–105](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void reseal(std::string& bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute both protected checksums after a deliberate hostile-frame mutation. |
| inputs / outputs | A mutable byte string is hashed from frame_header_size for the body, then the body digest and protected prefix digest are written at fixed offsets. |
| invariants | The helper assumes a complete frame large enough for both offsets; it makes test bytes checksum-consistent but does not make their kind, sequence or schema valid. |
| ownership | The caller owns the modified std::string; hash results are fixed values and are not retained by the helper. |
| failure | There is no frame-length guard, so callers must pass a valid-size test frame; malformed contents are intentionally left for parser checks. |
| cost | Two SHA-256 passes process body/prefix data; no second frame string is allocated inside this helper. |
| Design | tests/support/sql_aggregate_file_fixture.hpp:102-105, docs/sql_aggregate_records.md:1-35, include/crown/recovery/sql_aggregate_files.hpp:10-16, src/recovery/sql_aggregate_file_detail.cpp:59-78 |

## B0018

[Lines 106–106](../../../../../tests/support/sql_aggregate_file_fixture.hpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L106:sha256:ac211d04d27e71f53ef94860c527ea2bfd765bdcf41cc472c6c87b6add24b4bc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_file_fixture.hpp: namespace crown::sql_aggregate_file_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/sql_aggregate_file_fixture.hpp](../../../../../tests/support/sql_aggregate_file_fixture.hpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |
