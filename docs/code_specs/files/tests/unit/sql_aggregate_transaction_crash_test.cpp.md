# `tests/unit/sql_aggregate_transaction_crash_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `8b2c517c3b6e70f1d43bf9f6c7e36b39784b22d8ede6bc31ee1e33d6d78ea80f`. 329 lines partitioned into 36 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // One true left anchor joins every right row, including itself. Compressed · [reviewed contract](#b0001) |
| [B0002 · 19–19](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L19) | Type/record definition: enum class Group |  · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L20) | Type/record definition: enum class Command |  · [reviewed contract](#b0003) |
| [B0004 · 21–21](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L21) | Type/record definition: enum class Action |  · [reviewed contract](#b0004) |
| [B0005 · 22–23](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L22) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |
| [B0006 · 24–24](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L24) | Callable definition: ag::SqlValue integer(std::int64_t value) | calls ; returns Value{value} · [reviewed contract](#b0006) |
| [B0007 · 25–25](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L25) | Callable definition: ag::SqlValue decimal(std::string_view value) | calls Decimal::parse; returns Value{Decimal::parse(value)} · [reviewed contract](#b0007) |
| [B0008 · 26–26](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L26) | Callable definition: bool present(Group group) | calls ; returns group != Group::empty && group != Group::erased · [reviewed contract](#b0008) |
| [B0009 · 27–36](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L27) | Callable definition: std::string hex(std::string_view bytes) | calls reserve, size; returns result; growth reserve; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 37–40](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L37) | Callable definition: Row key(Group group) | calls assert, present, integer, std::string; guard assert(present(group));; returns {integer(7), group == Group::seed ? ag::SqlValue{} : ag::SqlValue{Value{std::string(@ )}}} · [reviewed contract](#b0010) |
| [B0011 · 41–50](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L41) | Callable definition: Row values(Group group) | calls assert, present, key, integer; guard assert(present(group));; returns {key(group)\[1\], integer(count), integer(nonnull), integer(probe ? 1 : 0), · [reviewed contract](#b0011) |
| [B0012 · 51–55](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L51) | Callable definition: ag::Tuple tuple(const resource::MemoryAccount& account, const Row& row) | calls push_back, storage::borrow_scalar, ag::Tuple::copy_of; returns ag::Tuple::copy_of(account, cells); growth copy_of, push_back; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 56–57](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L56) | Explanatory comments or spacing. | source comment (unverified): // Five explicit before/final changes form the output oracle. The very small · [reviewed contract](#b0013) |
| [B0014 · 58–68](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L58) | Callable definition: std::vector&lt;ag::GroupChange&gt; changes(const resource::MemoryAccount& account, Group before, Group after) | calls present, key, push_back, tuple; returns result; growth push_back; source comment (unverified): // Five explicit before/final changes form the output oracle. The very small · [reviewed contract](#b0014) |
| [B0015 · 69–73](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L69) | Callable definition: Catalog catalog() | calls ; returns {1, {{@ , {{@ , ScalarType::int64, true}, {@ , ScalarType::string, true}, · [reviewed contract](#b0015) |
| [B0016 · 74–87](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L74) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // These caller-owned physical buffers survive every synchronous log call. · [reviewed contract](#b0016) |
| [B0017 · 88–90](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L88) | Callable definition: explicit Scenario(bool indexed) : Fixture(indexed, catalog(), "SELECT a.g,COUNT(*),COUNT(b.x::integer),SUM(b.x::integer),SUM(b.x)… | calls Fixture, catalog · [reviewed contract](#b0017) |
| [B0018 · 91–110](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L91) | Callable definition: Edits edits(Command command, bool erased = false) const | calls r, u, std::abort; returns runtime::sql_rows::SourceReplacement{TableId{0}, row, before, after}; runtime::sql_rows::SourceRepl… · [reviewed contract](#b0018) |
| [B0019 · 111–115](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L111) | Callable definition: void log_command(ar::Session& owner, Command command, bool erased = false) const | calls state, edits, log · [reviewed contract](#b0019) |
| [B0020 · 116–134](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L116) | Callable definition: void check(const ar::Session& owner, Group group) const | calls snapshot, assert, size, present; guard void check(const ar::Session& owner, Group group) const { · [reviewed contract](#b0020) |
| [B0021 · 135–148](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L135) | Callable definition: std::string expected_epoch(const ar::Session& owner, Group before, Group after) const | calls state, frames, contents, generation_file; guard assert(input);; returns std::string(frame.bytes()); 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 149–150](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L149) | Explanatory comments or spacing. | source comment (unverified): // Baseline preparation uses the same real API as later recovery. Expected · [reviewed contract](#b0022) |
| [B0023 · 151–158](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L151) | Callable definition: void apply(ar::Session& owner, Command command, Group before, Group after, bool deliver = true) | calls log_command, assert, decide, expected_epoch; guard assert(!owner.decide().rejected);; source comment (unverified): // Baseline preparation uses the same real API as later recovery. Expected · [reviewed contract](#b0023) |
| [B0024 · 159–163](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L159) | Callable definition: void reject(ar::Session& owner, Command command) | calls log_command, assert, decide, check; guard assert(owner.decide().rejected == ar::RejectReason::aggregate_overflow); · [reviewed contract](#b0024) |
| [B0025 · 164–166](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L164) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0025) |
| [B0026 · 167–172](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L167) | Callable definition: Namespace capture(const Scenario& f) | calls std::filesystem::directory_iterator, emplace_back, path, string; returns result; growth emplace_back; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 173–178](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L173) | Callable definition: void restore(Scenario& f, const Namespace& files, Action action, std::optional&lt;ar::Session&gt;& owner) | calls reset, std::filesystem::directory_iterator, std::filesystem::remove_all, path; growth emplace; 2 loop sites · [reviewed contract](#b0027) |
| [B0028 · 179–180](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L179) | Explanatory comments or spacing. | source comment (unverified): // The selected checkpoint at C1 already contains compressed weights at the · [reviewed contract](#b0028) |
| [B0029 · 181–206](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L181) | Callable definition: void prepare(Scenario& f, Action action, std::optional&lt;ar::Session&gt;& owner) | calls emplace, create, ar::encode, descriptor; guard f.expected_sink = header.bytes(); assert(contents(f.sink) == f.expected_sink);; growth emplace; source comment (unverified): // The selected checkpoint at C1 already contains compressed weights at the · [reviewed contract](#b0029) |
| [B0030 · 207–217](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L207) | Callable definition: void perform(Scenario& f, Action action, std::optional&lt;ar::Session&gt;& owner) | calls log_command, assert, decide, deliver; guard case Action::commit: assert(!owner-&gt;decide().rejected); break;; growth emplace · [reviewed contract](#b0030) |
| [B0031 · 218–219](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L218) | Explanatory comments or spacing. | source comment (unverified): // Resolve only the same surviving Input, compare complete state/sink, and then · [reviewed contract](#b0031) |
| [B0032 · 220–263](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L220) | Callable definition: Json surviving(Scenario& f, Action action, std::optional&lt;ar::Session&gt;& owner, bool reopen = true) | calls reset, emplace, recover, state; guard assert(action == Action::log && owner-&gt;state().logged == 1);; returns observation; growth emplace; source comment (unverified): // Resolve only the same surviving Input, compare complete state/sink, and then · [reviewed contract](#b0032) |
| [B0033 · 264–264](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L264) | Explanatory comments or spacing. |  |
| [B0034 · 265–320](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L265) | Callable definition: Json matrix(bool indexed) | calls Json::array, f, prepare, reset; guard assert(failed);; returns report; growth emplace, push_back; 3 loop sites; source comment (unverified): // The no-fault control probes the live owner too, before its first reopen. · [reviewed contract](#b0034) |
| [B0035 · 321–322](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L321) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0035) |
| [B0036 · 323–329](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L323) | Callable definition: int main(int argc, char** argv) | calls assert, Json::array, matrix, push_back; guard assert(argc == 2);; growth push_back; 2 loop sites · [reviewed contract](#b0036) |

## B0001

[Lines 1–18](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::uint64_t weight
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the compressed signed-cancellation fixture without expanding its bag. |
| inputs / outputs | K=(INT64_MAX-3)/2; Group labels expected group states, Command labels physical batches, Action labels interrupted API calls. |
| invariants | One true left anchor joins all same-id right rows including itself; seed COUNT(*)=2K+3=INT64_MAX. Individual opposite SUM contributions exceed bigint. |
| ownership | Compile-time constants and test aliases only. |
| failure | No fallible runtime step here. |
| cost | Fixed metadata; cardinality is a weight, not an allocation count. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0002

[Lines 19–19](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Group
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the six independently specified visible group states. |
| inputs / outputs | empty/seed/mixed/erased/probe_mixed/probe_small select oracle rows; empty and erased have no group. |
| invariants | Only the test harness interprets these labels. |
| ownership | Plain local scalar values. |
| failure | No runtime failure in this declaration; downstream row helpers assert that a visible group is present. |
| cost | Fixed enum/dispatch metadata. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 20–20](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Command
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the six original-source batch shapes. |
| inputs / outputs | seed/mixed/cast_reject/sum_reject/erase/probe dispatch edits(); these are test labels, not persistent record tags. |
| invariants | Only the test harness interprets these labels. |
| ownership | Plain local scalar values. |
| failure | Unknown command dispatch aborts; no product recovery policy is added. |
| cost | Fixed enum/dispatch metadata. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 21–21](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Action
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the seven real Session operations subject to persistence faults. |
| inputs / outputs | log/commit/two semantic Rejects/deliver/checkpoint/recover select prepare/perform/surviving paths. |
| invariants | Only the test harness interprets these labels. |
| ownership | Plain local scalar values. |
| failure | No runtime failure in this declaration; perform() dispatches the seven declared action values. |
| cost | Fixed enum/dispatch metadata. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 22–23](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L23:sha256:1b87cb149d72d9ca6903ed60ac93491b8fc14c99700cfe02716d81a34d73676d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_transaction_crash_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 24–24](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ag::SqlValue integer(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the oracle bigint alternative. |
| inputs / outputs | int64 -&gt; present SqlValue holding Value(int64). |
| invariants | Zero stays present; NULL is constructed separately. |
| ownership | Value returned by value. |
| failure | Ordinary value construction boundary. |
| cost | Fixed scalar construction. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 25–25](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ag::SqlValue decimal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an exact numeric oracle literal. |
| inputs / outputs | Known finite decimal spelling -&gt; present Decimal SqlValue. |
| invariants | Numeric zero/one/half remain distinct from bigint and NULL. |
| ownership | Returned Decimal owns its representation. |
| failure | Invalid spelling would propagate the existing parse failure. |
| cost | Small decimal parse; no physical-bag expansion. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 26–26](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool present(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decide whether an expected grouped result exists. |
| inputs / outputs | Group label -&gt; false for empty/erased and true for the other four. |
| invariants | Group absence is distinct from nullable group/output cells. |
| ownership | No retained state. |
| failure | No failure path. |
| cost | Two enum comparisons. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 27–36](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string hex(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a retained tape as lowercase hexadecimal for the Python oracle. |
| inputs / outputs | Borrowed bytes -&gt; owning two-characters-per-byte string. |
| invariants | Unsigned-byte conversion prevents sign extension. |
| ownership | Caller receives an ordinary heap-backed string. |
| failure | Allocation failure propagates through the test. |
| cost | Linear byte work/storage; only finite fixture tapes are passed. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 37–40](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row key(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify the internal expected group key independently of a native snapshot. |
| inputs / outputs | Present Group -&gt; \[bigint 7, NULL for seed or string next otherwise\]. |
| invariants | Hidden id remains in the key even though only a.g is selected. |
| ownership | Returned Row owns its values. |
| failure | Absent group asserts. |
| cost | Two-cell fixture Row; ordinary vector/string allocation. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0011

[Lines 41–50](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row values(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify the six exact aggregate output cells for each expected group. |
| inputs / outputs | Group -&gt; selected g, COUNT(*), COUNT(x::integer), SUM32, numeric SUM64, numeric AVG32. |
| invariants | Seed count is MAX; mixed is MAX-1; heavy probe returns MAX. Nonnull is MAX-2 except heavy probe MAX-1; small probe counts both 2. Sums are zero or one; AVG is zero or half. |
| ownership | Returned Row owns fixture values; key() supplies g. |
| failure | Absent group asserts through key(); parse/allocation failures propagate. |
| cost | Fixed-size rows and short decimal parses, independent of compressed multiplicity. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 51–55](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ag::Tuple tuple(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy oracle row values into an accounted owning tuple. |
| inputs / outputs | Oracle MemoryAccount and borrowed Row -&gt; owning aggregate Tuple. |
| invariants | NULL cells stay NULL and scalar views are copied before temporary cells die. |
| ownership | Temporary std::vector&lt;Cell&gt; is ordinary test workspace; tuple payload belongs to the explicit oracle account. |
| failure | Allocation/type failures propagate; no catch or product allocation path is added. |
| cost | Linear in the small fixture row/payload. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0013

[Lines 56–57](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L57:sha256:ae831506e690b77b1b0948f5ba79cd68e1551594ec442460f79b355947dfd928
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Five explicit before/final changes form the output oracle. The very small probe after the large state has AVG=1/(INT64_MAX-1), which rounds to zero at18. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 58–68](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<ag::GroupChange> changes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct canonical before/final group changes from the explicit oracle states. |
| inputs / outputs | Before/after Group labels -&gt; zero to two full-key GroupChanges. |
| invariants | Changed key deletes the old group before adding the next; unchanged key uses separately present before/after rows. No signed SUM-difference narrowing. |
| ownership | Vector owns changes; tuple payload uses the oracle account. |
| failure | Oracle construction failures propagate. |
| cost | At most two changes and fixed small rows; no multiplicity expansion. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0015

[Lines 69–73](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the genuine nullable self-join schema and retained unused source. |
| inputs / outputs | Return r(id bigint,g string,x bigint,flag bool), all nullable, plus unused(z nullable string). |
| invariants | Physical x remains bigint; integer narrowing is in genuine SQL expressions. |
| ownership | Returned catalog owns its schema labels/containers. |
| failure | Ordinary catalog construction failure propagates. |
| cost | Fixed five-column fixture metadata. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0016

[Lines 74–87](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Scenario : Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own all fixture input buffers and a separate expected-output allocation authority. |
| inputs / outputs | Eight four-cell r rows and one unused row survive synchronous logging; oracle account is 4MiB; expected_sink accumulates expected bytes. |
| invariants | Filtered row uses unmatched id9, so its huge x cannot enter b through the id7 anchor. bad uses id7 and INT32_MAX+1. No second mutable runtime is used as oracle. |
| ownership | Scenario owns cell arrays; string views refer to static literals; inherited Fixture owns real files/program/runtime account. |
| failure | Account creation or fixture setup failures propagate directly. |
| cost | Fixed physical row count plus finite expected tape storage; test-only account adds no product owner. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0017

[Lines 88–90](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Scenario(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the real original SQL for either existing physical backend. |
| inputs / outputs | Backend bool -&gt; Fixture for a.g, five aggregates, self-join on a.id=b.id, WHERE a.flag, GROUP BY a.id,a.g. |
| invariants | Both aliases use the same original r source; hidden a.id keeps the admitted two-sided source head. |
| ownership | Inherited Fixture owns the genuine factory program/account/files. |
| failure | Existing admission/setup failures fail the test. |
| cost | Cold fixed-size SQL binding; no hot-path design change. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0018

[Lines 91–110](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Edits edits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe exact chained before/after physical weights for six commands. |
| inputs / outputs | Command and erased-probe flag -&gt; vector of genuine SourceReplacements for r and unused. |
| invariants | Mixed lists addition before deletion and a net-zero positive chain; Reject batches also modify unused, which must roll back. Probe after erase creates a new-new self-join contribution. |
| ownership | Vector owns descriptors; row cell spans borrow this live Scenario through log_command(). |
| failure | Unrecognized enum aborts; ordinary vector allocation failure propagates. |
| cost | At most seven replacements; weight K is never expanded. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0019

[Lines 111–115](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void log_command(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Persist the next numbered original-source command with independent source/reader progress. |
| inputs / outputs | Live Session and Command -&gt; log at disposed+1, feed=10*next and reader={100*next,next}. |
| invariants | Physical descriptors remain alive throughout the synchronous log; a pending surviving Input is resolved before any new command. |
| ownership | Local edits vector borrows Scenario rows; Session retains the encoded Input. |
| failure | Existing log/file/allocation failures propagate. |
| cost | One bounded Input encode/append using compressed replacements. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0020

[Lines 116–134](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare visible output and every known original-source row weight to the manual oracle. |
| inputs / outputs | Live Session and Group -&gt; assertions over group count, full key/values, eight r weights and one unused weight. |
| invariants | Filtered and unused weights survive despite no output; bad stays absent; rejected changes cannot leak into source state. |
| ownership | Snapshot tuples live through the comparisons; Scenario owns borrowed source cells. |
| failure | Any mismatch asserts; no error is swallowed. |
| cost | Nine source lookups plus one small snapshot; this is test inspection cost. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0021

[Lines 135–148](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string expected_epoch(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build expected canonical output using manual rows and the actual surviving Input identity. |
| inputs / outputs | Session state and before/after labels -&gt; encoded GroupEpoch bytes for current generation, disposed I and committed C. |
| invariants | Only the Input body SHA is read from actual WAL; expected group payload is never read from native snapshots. changed/group_changed are true for these commits. |
| ownership | Temporary frame bytes and changes are test workspace; encoded owning frame uses oracle account before copying to std::string. |
| failure | Missing matching Input asserts; codec/read/allocation failures propagate. |
| cost | Scan finite selected WAL, then encode at most two group changes; no production replay work added. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0022

[Lines 149–150](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L149); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L150:sha256:d38fbfc7fbc9aafb91decba317f88855457df9acc044da4456a13cc7b80e45ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Baseline preparation uses the same real API as later recovery. Expected group payloads above are independently specified, not copied from snapshots. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 151–158](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a healthy committed baseline through real Session APIs. |
| inputs / outputs | Command plus before/after oracle -&gt; log, successful decide, exact output/snapshot check and optional delivery. |
| invariants | Expected sink is appended once even when delivery is intentionally deferred; output must match the independently specified epoch. |
| ownership | Fixture retains expected bytes; real Session owns pending output until delivery. |
| failure | Unexpected Reject or byte/state mismatch asserts. |
| cost | One genuine command and optional sink append; setup cost is outside fault trace. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0024

[Lines 159–163](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reject(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a real semantic Reject while proving source/group rollback. |
| inputs / outputs | Cast or final-SUM command -&gt; aggregate_overflow, unchanged mixed state and sink, no output. |
| invariants | Reject advances command/reader progress through Session; committed result remains the mixed oracle. |
| ownership | No additional mutable owner. |
| failure | Wrong reason, source leak or output asserts. |
| cost | One genuine bounded rejected command. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0025

[Lines 164–166](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L164); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L164-L166:sha256:885834880d7f92dcbade572dfa0e02137faf487fa173e47ee9c09f1db039ba47
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_transaction_crash_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 167–172](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Namespace capture(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot exact disposable fixture namespace bytes between test iterations. |
| inputs / outputs | Closed baseline Scenario -&gt; vector of file paths and binary contents. |
| invariants | These are byte preimages for repeated faults, not an alternate query-state DTO. |
| ownership | Vector owns paths/bytes; caller has closed Session before capture. |
| failure | Filesystem/read/allocation failures propagate. |
| cost | Linear in fixture file count and total copied bytes. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0027

[Lines 173–178](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void restore(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release locks, restore captured bytes and reopen only when the target operation needs a live owner. |
| inputs / outputs | Scenario, captured namespace, Action and optional Session -&gt; exact reset baseline. |
| invariants | owner.reset precedes removing disposable fixture files; recover target leaves owner absent so recovery itself is traced. |
| ownership | Captured files remain owned by matrix; optional owns the new actual Session. |
| failure | Filesystem/write/recovery failures propagate directly. |
| cost | Rewrite finite captured bytes plus optional cold real recovery. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0028

[Lines 179–180](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L179); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L179-L180:sha256:51fc912cf280b694498eea02a5e8c5379680c6f6c80efb3eb1013e4492c91f1e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: The selected checkpoint at C1 already contains compressed weights at the bigint count boundary. Later cases retain I&gt;C after genuine semantic Rejects. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0029

[Lines 181–206](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the selected persisted starting point before tracing one operation. |
| inputs / outputs | Action -&gt; seed at C1/checkpoint generation 2; optional mixed C2 and Rejects I3/I4. Recover starts from selected generation 3 checkpoint C2/I4 plus WAL erase Commit C3/I5, missing final delivery and torn WAL/sink suffixes. |
| invariants | Seed count is INT64_MAX. Rejects make I greater than C; recovery must validate before repairing either suffix and retain the missing final sink epoch. |
| ownership | Scenario retains expected sink; optional Session closes before recover target. |
| failure | Unexpected setup result asserts; existing API errors propagate. |
| cost | At most five commands and two checkpoints, never expanded source multiplicity. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0030

[Lines 207–217](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void perform(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute exactly the target public API call under installed file observers. |
| inputs / outputs | Action dispatches log, decide Commit/Reject, deliver, checkpoint or recover. |
| invariants | No custom commit/rollback mechanism; production Session orders native and durable publication. |
| ownership | Existing optional owner receives recovered Session only on recover. |
| failure | File/Generation failures intentionally propagate to matrix; wrong semantic results assert. |
| cost | One real bounded operation; observer overhead exists only in testing libraries. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0031

[Lines 218–219](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L218); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L218-L219:sha256:c8ed2186f57c28b9fe6ec5a45764f9a3386f1f3e4fdddc29751ad4ab34ab68cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Resolve only the same surviving Input, compare complete state/sink, and then make a fresh small update to expose stale ancestor or sufficient-statistic state. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0032

[Lines 220–263](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json surviving(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the same surviving Input, inspect exact result, then expose stale state with a new update and reopen. |
| inputs / outputs | Action and owner -&gt; recovered or healthy live completion, full W/I/C/D, source/reader/group/sink checks, probe Commit and final reopen; JSON retains baseline/probe tape hex. |
| invariants | Only a genuinely incomplete log is re-logged. Healthy control probes live state before first reopen; injected cases recover uncertain files. Checkpoint generation may be old/new. Exported expected bytes have been asserted equal to actual sink bytes. |
| ownership | Existing Session alone owns query state; JSON owns finite strings. Function resets owner before returning. |
| failure | Any output/frontier/progress/source mismatch asserts; recover/decide/deliver failures propagate. |
| cost | One recovery when requested, one tiny probe and final recovery over finite history. No CPU or instruction-by-instruction crash claim. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0034

[Lines 265–320](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L265); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json matrix(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise observed syscall effects and real process exits for all seven actions on one backend. |
| inputs / outputs | Backend bool -&gt; seven healthy observations plus a repeat for every eligible before/after EIO and durability-cut event. |
| invariants | Each injected file failure is required. A retained live owner after log, Commit, Reject or delivery failure must refuse snapshots until reopen; checkpoint/recovery follow their documented validity rules. Child must exit 77. Every repaired case checks exact state, next update, account restoration and FD restoration. |
| ownership | Fixed 4096-event Hook borrows one trace scope. Byte preimages and counters are test-only. Child exits without cleanup by design; parent owns recovery. |
| failure | Only expected FileFailure/GenerationFailure are caught; unexpected errors propagate. assert guards fork/wait/trace/resource results. |
| cost | Repeated finite recovery per observed event plus fork per selected durability event; this is fault evidence, not runtime performance evidence. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |

## B0035

[Lines 321–322](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L321); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L321-L322:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_transaction_crash_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0036

[Lines 323–329](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc, char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both real backends and retain all healthy tape evidence for independent decoding. |
| inputs / outputs | One output path -&gt; fourteen case records and progress text; writes/flushes JSON and checks stream state. |
| invariants | Both reference/indexed backends run the same seven actions; no unchecked artifact-write success claim. |
| ownership | Local JSON/stream own artifacts; fixture files are scoped inside each matrix. |
| failure | Wrong argc, assertion or stream failure makes the test fail. |
| cost | Sum of two finite fault matrices and one small JSON artifact write. |
| Design | [tests/unit/sql_aggregate_transaction_crash_test.cpp](../../../../../tests/unit/sql_aggregate_transaction_crash_test.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [Refactor.md](../../../../../Refactor.md) |
