# `apps/crown/workflow.cpp` — block usage map

[Source](../../../../../apps/crown/workflow.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `de0f3adce25a12386eaeab626ef9005881abbfaaee751f93cf112bdc955a8e8d`. 458 lines partitioned into 48 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–29](../../../../../apps/crown/workflow.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 30–36](../../../../../apps/crown/workflow.cpp#L30) | Callable definition: std::uint64_t integer(std::string_view text) | calls std::from_chars, data, size, Error; returns value · [reviewed contract](#b0002) |
| [B0003 · 37–40](../../../../../apps/crown/workflow.cpp#L37) | Callable definition: std::size_t size(std::uint64_t value) | calls max, Error; returns static_cast&lt;std::size_t&gt;(value) · [reviewed contract](#b0003) |
| [B0004 · 41–52](../../../../../apps/crown/workflow.cpp#L41) | Callable definition: std::string read(const std::string& path,std::size_t limit=document_limit) | calls file, Error, gcount, size; returns result; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 53–56](../../../../../apps/crown/workflow.cpp#L53) | declares types or opens a type body. | source comment (unverified): // Final transport text is outside the native account and capped before append. · [reviewed contract](#b0005) |
| [B0006 · 57–58](../../../../../apps/crown/workflow.cpp#L57) | Callable definition: public: explicit Writer(std::size_t limit):limit_(limit) | calls limit_ · [reviewed contract](#b0006) |
| [B0007 · 59–62](../../../../../apps/crown/workflow.cpp#L59) | Callable definition: void raw(std::string_view text) | calls size, Error, append · [reviewed contract](#b0007) |
| [B0008 · 63–63](../../../../../apps/crown/workflow.cpp#L63) | Callable definition: void text(std::string_view value) | calls raw, Json, dump · [reviewed contract](#b0008) |
| [B0009 · 64–67](../../../../../apps/crown/workflow.cpp#L64) | Callable definition: void number(std::uint64_t value) | calls std::to_chars, raw · [reviewed contract](#b0009) |
| [B0010 · 68–81](../../../../../apps/crown/workflow.cpp#L68) | Callable definition: void json(const Json& value,unsigned depth=0) | calls Error, is_object, raw, begin; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 82–86](../../../../../apps/crown/workflow.cpp#L82) | Callable definition: void row(storage::TupleValuesView values) | calls raw, json, io::write_scalar_view; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 87–87](../../../../../apps/crown/workflow.cpp#L87) | Callable definition: std::string finish() && | calls std::move; returns std::move(text_) · [reviewed contract](#b0012) |
| [B0013 · 88–90](../../../../../apps/crown/workflow.cpp#L88) | Member/declaration region. |  · [reviewed contract](#b0013) |
| [B0014 · 91–91](../../../../../apps/crown/workflow.cpp#L91) | Callable definition: std::string encode(const Json& value,std::size_t limit) | calls writer, json, std::move, finish; returns std::move(writer).finish() · [reviewed contract](#b0014) |
| [B0015 · 92–92](../../../../../apps/crown/workflow.cpp#L92) | Explanatory comments or spacing. | source comment (unverified): // Stdout is a report view; failure here does not revoke durable sink publication. · [reviewed contract](#b0015) |
| [B0016 · 93–96](../../../../../apps/crown/workflow.cpp#L93) | Callable definition: void emit(std::string_view value) | calls write, data, size, put; source comment (unverified): // Stdout is a report view; failure here does not revoke durable sink publication. · [reviewed contract](#b0016) |
| [B0017 · 97–100](../../../../../apps/crown/workflow.cpp#L97) | declares types or opens a type body. |  · [reviewed contract](#b0017) |
| [B0018 · 101–112](../../../../../apps/crown/workflow.cpp#L101) | Callable definition: explicit Arguments(int argc,char** argv):command(argc&gt;1?argv\[1\]:"") | calls command, key, starts_with, push_back; growth emplace, push_back; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 113–116](../../../../../apps/crown/workflow.cpp#L113) | Callable definition: std::optional&lt;std::string&gt; take(const std::string& key) | calls find, end, erase; returns {}; value · [reviewed contract](#b0019) |
| [B0020 · 117–117](../../../../../apps/crown/workflow.cpp#L117) | Callable definition: std::uint64_t number(const std::string& key,std::uint64_t fallback) | calls take, integer; returns value?integer(*value):fallback · [reviewed contract](#b0020) |
| [B0021 · 118–120](../../../../../apps/crown/workflow.cpp#L118) | Callable definition: void count(std::size_t minimum,std::size_t maximum) const | calls size, Error · [reviewed contract](#b0021) |
| [B0022 · 121–121](../../../../../apps/crown/workflow.cpp#L121) | Callable definition: void finished() const | calls empty, Error, begin · [reviewed contract](#b0022) |
| [B0023 · 122–122](../../../../../apps/crown/workflow.cpp#L122) | Closes surrounding scope/type. |  · [reviewed contract](#b0023) |
| [B0024 · 123–128](../../../../../apps/crown/workflow.cpp#L123) | Callable definition: std::size_t output_limit(Arguments& arguments) | calls number, Error, size; returns size(value) · [reviewed contract](#b0024) |
| [B0025 · 129–146](../../../../../apps/crown/workflow.cpp#L129) | Callable definition: void help() | calls  · [reviewed contract](#b0025) |
| [B0026 · 147–151](../../../../../apps/crown/workflow.cpp#L147) | Type/record definition: struct Artifact |  · [reviewed contract](#b0026) |
| [B0027 · 152–152](../../../../../apps/crown/workflow.cpp#L152) | Explanatory comments or spacing. | source comment (unverified): // Existing set-family admission only; nullable/bag library APIs are separate. · [reviewed contract](#b0027) |
| [B0028 · 153–175](../../../../../apps/crown/workflow.cpp#L153) | Callable definition: Artifact compile(Arguments& arguments) | calls count, take, number, finished; returns {planner::lower_normalized(normalized,FreeConnexTree{},plan_options),nullptr,{}}; {planner::lower_n…; source comment (unverified): // Existing set-family admission only; nullable/bag library APIs are separate. · [reviewed contract](#b0028) |
| [B0029 · 176–176](../../../../../apps/crown/workflow.cpp#L176) | Explanatory comments or spacing. | source comment (unverified): // Reconstruct the plan and independently replay proof; JSON flags are not authority. · [reviewed contract](#b0029) |
| [B0030 · 177–203](../../../../../apps/crown/workflow.cpp#L177) | Callable definition: Artifact artifact(const std::string& path,std::uint64_t proof_work) | calls io::read_json, read, is_object, size; returns {std::move(plan),nullptr,{}}; {std::move(plan),encoded,optimum}; source comment (unverified): // Reconstruct the plan and independently replay proof; JSON flags are not authority. · [reviewed contract](#b0030) |
| [B0031 · 204–207](../../../../../apps/crown/workflow.cpp#L204) | Callable definition: observability::HeightEvidence evidence(const Artifact& built) | calls ; returns *built.optimum; {} · [reviewed contract](#b0031) |
| [B0032 · 208–212](../../../../../apps/crown/workflow.cpp#L208) | Callable definition: std::unique_ptr&lt;std::istream&gt; input(const std::string& path) | calls Error; returns stream; growth make_unique · [reviewed contract](#b0032) |
| [B0033 · 213–217](../../../../../apps/crown/workflow.cpp#L213) | Callable definition: std::array&lt;char,32&gt; identifier(const std::string& text) | calls size, std::all_of, begin, end; returns (c&gt;=@ && c&lt;=@ ) \|\| (c&gt;=@ && c&lt;=@ ); value · [reviewed contract](#b0033) |
| [B0034 · 218–220](../../../../../apps/crown/workflow.cpp#L218) | Callable definition: std::array&lt;char,32&gt; query_id(const CompiledProgram& program) | calls std::copy_n, physical_source_sha256, begin; returns value · [reviewed contract](#b0034) |
| [B0035 · 221–223](../../../../../apps/crown/workflow.cpp#L221) | Callable definition: runtime::SessionLocalSinkOptions sink_options(const CompiledProgram& program) | calls std::copy_n, physical_sha256, begin; returns options · [reviewed contract](#b0035) |
| [B0036 · 224–224](../../../../../apps/crown/workflow.cpp#L224) | Explanatory comments or spacing. | source comment (unverified): // Session commit owns the WAL/native publication barrier, not this stepping loop. · [reviewed contract](#b0036) |
| [B0037 · 225–225](../../../../../apps/crown/workflow.cpp#L225) | Callable definition: void finish(runtime::QuerySession& session) | calls step, commit; 1 loop sites; source comment (unverified): // Session commit owns the WAL/native publication barrier, not this stepping loop. · [reviewed contract](#b0037) |
| [B0038 · 226–234](../../../../../apps/crown/workflow.cpp#L226) | Callable definition: std::uint64_t deliver(runtime::QuerySession& session) | calls local_sink_state, status, deliver_local_epoch, Error; returns rows; 1 loop sites · [reviewed contract](#b0038) |
| [B0039 · 235–238](../../../../../apps/crown/workflow.cpp#L235) | Callable definition: void accumulate(std::uint64_t& total,std::uint64_t amount) | calls Error · [reviewed contract](#b0039) |
| [B0040 · 239–242](../../../../../apps/crown/workflow.cpp#L239) | Callable definition: std::uint64_t nanoseconds(std::chrono::steady_clock::time_point begin,std::chrono::steady_clock::time_point end) | calls count; returns elapsed&gt;0?static_cast&lt;std::uint64_t&gt;(elapsed):0 · [reviewed contract](#b0040) |
| [B0041 · 243–256](../../../../../apps/crown/workflow.cpp#L243) | Callable definition: std::string snapshot(runtime::QuerySession& session,std::size_t limit) | calls local_sink_state, generation_state, writer, raw; returns std::move(writer).finish(); 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 257–272](../../../../../apps/crown/workflow.cpp#L257) | Callable definition: std::string results(runtime::QuerySession& session,std::uint64_t sequence,std::size_t limit) | calls read_local_epoch, writer, raw, number; returns std::move(writer).finish(); growth insert; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 273–422](../../../../../apps/crown/workflow.cpp#L273) | Callable definition: int workflow(int argc,char** argv) | calls std::string_view, help, arguments, output_limit; returns 0; 0; growth make_shared; 1 loop sites; source comment (unverified): // All options/proof/labels are admitted before native file operations. A later · [reviewed contract](#b0043) |
| [B0044 · 423–427](../../../../../apps/crown/workflow.cpp#L423) | Callable definition: void diagnostic(std::string_view code,std::string_view message,const Json& details=nullptr) | calls is_null, dump · [reviewed contract](#b0044) |
| [B0045 · 428–428](../../../../../apps/crown/workflow.cpp#L428) | Explanatory comments or spacing. | source comment (unverified): // Preserve typed fault/stage/outcome; a diagnostic never authorizes blind retry. · [reviewed contract](#b0045) |
| [B0046 · 429–435](../../../../../apps/crown/workflow.cpp#L429) | Callable definition: template&lt;class Failure&gt; void file_diagnostic(std::string_view code,const Failure& error) | calls outcome, diagnostic, what, fault; source comment (unverified): // Preserve typed fault/stage/outcome; a diagnostic never authorizes blind retry. · [reviewed contract](#b0046) |
| [B0047 · 436–436](../../../../../apps/crown/workflow.cpp#L436) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0047) |
| [B0048 · 437–458](../../../../../apps/crown/workflow.cpp#L437) | Callable definition: int crown::cli::workflow_main(int argc,char** argv) | calls workflow, diagnostic, code, what; returns workflow(argc,argv); 1 · [reviewed contract](#b0048) |

## B0001

[Lines 1–29](../../../../../apps/crown/workflow.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::size_t document_limit=64U*1024U*1024U;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind file-workflow tool types and independent document/output ceilings. |
| inputs / outputs | Private aliases plus 64MiB document and default16MiB export constants configure CLI preparation. |
| invariants | Tool input/output limits are distinct from native account and proof/search grants; all paths remain set-family APIs. |
| ownership | No dynamic owner introduced. |
| failure | Declaration only; helpers enforce limits. |
| cost | Static constants/name binding only. |
| Design | [docs/cli.md](../../../../cli.md), [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0002

[Lines 30–36](../../../../../apps/crown/workflow.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t integer(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one complete unsigned workflow option. |
| inputs / outputs | from_chars uint64 requires full valid consumption. |
| invariants | No negative/partial/locale conversion or silent clamp. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | usage on malformed text. |
| cost | O(text bytes), fixed scalar state. |
| Design | [docs/cli.md](../../../../cli.md) |

## B0003

[Lines 37–40](../../../../../apps/crown/workflow.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t size(std::uint64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Narrow a workflow size only after host-range admission. |
| inputs / outputs | uint64 value must fit size_t; returns exact platform size. |
| invariants | Prevents truncating spool/output capacities. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | resource_limit on host-size overflow. |
| cost | Fixed comparison/conversion. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0004

[Lines 41–52](../../../../../apps/crown/workflow.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const std::string& path,std::size_t limit=document_limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a workflow document under caller-selected byte ceiling. |
| inputs / outputs | Binary file into 8192-byte blocks; subtraction admission precedes final string append. |
| invariants | Default64MiB; compile SQL/catalog pass narrower limits. Existing ifstream default errors are reported from open/bad state, not a durable file protocol. |
| ownership | Local stream closes; returned string owns bytes. |
| failure | io_error/resource_limit/allocation errors return no document. |
| cost | O(file bytes), ordinary tool string growth/I/O. |
| Design | [docs/cli.md](../../../../cli.md), [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0005

[Lines 53–56](../../../../../apps/crown/workflow.cpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one private complete workflow output string. |
| inputs / outputs | Stores encoded length ceiling and offers raw/text/number/DOM/row encoders; finish moves completed string. |
| invariants | Final string appends are capped before growth. Json scalar/dump temporaries and native snapshot/source copies can precede that cap and remain ordinary tool memory. |
| ownership | Writer owns transport string separately from query account; no stdout emitted before caller invokes emit. |
| failure | Encoding/limit/allocation errors discard private output; durable effects may already exist before reporting. |
| cost | Output-string growth plus per-value formatting/temporary DOM cost; no native maintenance instrumentation. |
| Design | [docs/cli.md](../../../../cli.md), [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0006

[Lines 57–58](../../../../../apps/crown/workflow.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
public: explicit Writer(std::size_t limit):limit_(limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a bounded private workflow writer. |
| inputs / outputs | Stores limit and empty string. |
| invariants | Does not reserve a native account or publish output. |
| ownership | Private ordinary transport owner. |
| failure | No explicit failure until writes. |
| cost | Fixed initialization. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0007

[Lines 59–62](../../../../../apps/crown/workflow.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one final-string append under workflow byte cap. |
| inputs / outputs | Checks text.size &lt;= limit_-text_.size(), then appends. |
| invariants | Successful invariant text_.size&lt;=limit_ prevents subtraction underflow. Does not cap already created argument/temp buffers. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | output_limit before oversized final append; allocation failures propagate. |
| cost | O(span bytes), ordinary string growth. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0008

[Lines 63–63](../../../../../apps/crown/workflow.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void text(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one JSON string through the existing Json serializer. |
| inputs / outputs | Builds Json(value), dumps strict encoded string, then raw-admits its bytes. |
| invariants | Temporary DOM/string allocation and UTF-8 validation precede final output cap; no caller text rewrite. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Json encoding316, output_limit or allocation failure returns no partial command output. |
| cost | O(string/escaped bytes) temporary ordinary Json/dump plus final copy. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0009

[Lines 64–67](../../../../../apps/crown/workflow.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void number(std::uint64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Format exact uint64 output numbers. |
| inputs / outputs | to_chars uses fixed32-byte stack buffer then appends digits. |
| invariants | Fixed type always fits; no float/locale/stream conversion. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Bounded integer formatting plus final append. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0010

[Lines 68–81](../../../../../apps/crown/workflow.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void json(const Json& value,unsigned depth=0)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream an existing diagnostic DOM without a second whole-artifact dump. |
| inputs / outputs | Objects/arrays recurse through values; scalar dump feeds raw; rejects depth&gt;128. |
| invariants | Existing DOM was allocated earlier. Keys/scalars still create per-value dump temporaries; recursion cap is export nesting, not source/proof authority. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | O(DOM values+encoded bytes), bounded recursion and ordinary scalar-string temporaries/final output growth. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0011

[Lines 82–86](../../../../../apps/crown/workflow.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row(storage::TupleValuesView values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one borrowed native output row in field order. |
| inputs / outputs | Each ScalarView passes write_scalar_view then private JSON encoding inside array delimiters. |
| invariants | No output row ownership or cursor advance occurs here; source tuple must remain live throughout synchronous formatting. |
| ownership | Borrows native payload; complete returned Writer string owns transport bytes. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | O(row width+scalar/escaped bytes), temporary scalar DOM/canonical spelling and final string copy. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0012

[Lines 87–87](../../../../../apps/crown/workflow.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string finish() &&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the completed private output buffer. |
| inputs / outputs | Rvalue-only finish moves text_ to caller. |
| invariants | Callers finish all formatting before stdout I/O; it does not attest stdout delivery or native durability. |
| ownership | Returned string becomes independent output owner. |
| failure | No explicit validation at this ownership transfer. |
| cost | Ordinary string move, no deliberate deep copy. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0013

[Lines 88–90](../../../../../apps/crown/workflow.cpp#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::size_t limit_;std::string text_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep final workflow encoded-size authority with its buffer. |
| inputs / outputs | Private size_t limit_ and owning ordinary text_ back every append. |
| invariants | Only raw grows final text after admission; per-value DOM/dump scratch has separate lifetime/cost. |
| ownership | Unique Writer-local storage. |
| failure | RAII destroys private output on failure. |
| cost | Fixed state plus string capacity, not native query-account memory. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0014

[Lines 91–91](../../../../../apps/crown/workflow.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string encode(const Json& value,std::size_t limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an already built JSON result under workflow report cap. |
| inputs / outputs | Constructs Writer, traverses Json, moves complete string. |
| invariants | Source DOM may already exceed final budget; this helper does not admit a plan/proof/source. |
| ownership | Returned text owns bytes; input DOM borrowed. |
| failure | Depth/encoding/output/allocation errors propagate before emit. |
| cost | Full DOM traversal/scalar dumps + final string growth/copy. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0015

[Lines 92–92](../../../../../apps/crown/workflow.cpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L92:sha256:01595075b208ff70f65336e40dea3a3d9a1fb60d802d3394cebe54b14de51722
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Stdout is a report view; failure here does not revoke durable sink publication. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [apps/crown/workflow.cpp](../../../../../apps/crown/workflow.cpp), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 93–96](../../../../../apps/crown/workflow.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void emit(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write one complete report view to stdout. |
| inputs / outputs | Writes bytes plus newline, checks stream state and raises output_error on detected failure. |
| invariants | Report stdout never acknowledges sink output. A detected failure can follow durable publication; current helper does not flush, so buffered late failure is a separate finding. |
| ownership | Borrows encoded text synchronously; durable sink/root ownership is elsewhere. |
| failure | output_error only when stream state is already failed; no rollback or command retry is attempted. |
| cost | One stream write/newline and OS buffering as configured; reporting outside native maintenance timing. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0017

[Lines 97–100](../../../../../apps/crown/workflow.cpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Arguments {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own workflow command tokens before any native/file authority is acquired. |
| inputs / outputs | Stores copied command, positional arguments and unique option/value map. |
| invariants | CLI token presence is not semantic admission or durable authorization; per-command consumers reject leftovers. |
| ownership | Owns copies of argv contents. |
| failure | Parser errors/allocation precede command setup. |
| cost | Ordinary argument strings/vector/map allocations. |
| Design | [docs/cli.md](../../../../cli.md) |

## B0018

[Lines 101–112](../../../../../apps/crown/workflow.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Arguments(int argc,char** argv):command(argc>1?argv[1]:"")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse workflow argv without accepting duplicate or missing option values. |
| inputs / outputs | Copies argv1 command; non-- tokens become positional, --retire is Boolean flag, other -- options consume following value. |
| invariants | An option value starting -- is rejected; positional count and allowed options are checked later before side effects. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | usage on duplicate/missing option; allocation failure before command setup. |
| cost | O(argument bytes + map operations), ordinary tool copies. |
| Design | [docs/cli.md](../../../../cli.md) |

## B0019

[Lines 113–116](../../../../../apps/crown/workflow.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::string> take(const std::string& key)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume one owned workflow option exactly once. |
| inputs / outputs | Finds key, copies its value, erases map entry; absence returns nullopt. |
| invariants | Failure during copy leaves map entry; unknown options remain for finished(). |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | O(log options + copied value bytes), ordinary string allocation. |
| Design | [docs/cli.md](../../../../cli.md) |

## B0020

[Lines 117–117](../../../../../apps/crown/workflow.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t number(const std::string& key,std::uint64_t fallback)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a numeric workflow option or explicit default. |
| inputs / outputs | take plus integer, fallback only when absent. |
| invariants | Invalid spelling never silently selects fallback. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Map lookup/copy plus O(text) parse. |
| Design | [docs/cli.md](../../../../cli.md) |

## B0021

[Lines 118–120](../../../../../apps/crown/workflow.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void count(std::size_t minimum,std::size_t maximum) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit per-command positional arity. |
| inputs / outputs | Requires count in inclusive minimum..maximum. |
| invariants | No file/native operation should precede command count validation in dispatcher branch. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Fixed vector-size checks and failure-only message construction. |
| Design | [docs/cli.md](../../../../cli.md) |

## B0022

[Lines 121–121](../../../../../apps/crown/workflow.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finished() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject any unknown/inapplicable workflow option. |
| inputs / outputs | Nonempty map after command consumers produces usage with first key. |
| invariants | Options are not silently ignored or applied to the wrong operation; gate precedes durable setup. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Fixed map-empty check; failure text copy only. |
| Design | [docs/cli.md](../../../../cli.md) |

## B0023

[Lines 122–122](../../../../../apps/crown/workflow.cpp#L122); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L122:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in workflow.cpp: struct Arguments. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [apps/crown/workflow.cpp](../../../../../apps/crown/workflow.cpp), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 123–128](../../../../../apps/crown/workflow.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t output_limit(Arguments& arguments)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit final workflow report/artifact byte ceiling. |
| inputs / outputs | Consumes --max-bytes default16MiB, maximum64MiB, minimum2; narrows with checked size(). |
| invariants | Independent export cap, not native memory/search/proof/input byte budget. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | usage above max; output_limit below minimal JSON; host overflow resource_limit. |
| cost | Option lookup/parse plus fixed checks. |
| Design | [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0025

[Lines 129–146](../../../../../apps/crown/workflow.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void help()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Print file-workflow help without native/file work. |
| inputs / outputs | Writes command/option syntax and source/root/sink authority distinctions. |
| invariants | Documents set physical streams and durable sink versus report view, not W05/W06 CLI capabilities. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This function leaves flushing to final main, which checks stdout before returning a successful process status. |
| cost | Fixed literal stream insertion; no explicit final flush in current code. |
| Design | [docs/cli.md](../../../../cli.md) |

## B0026

[Lines 147–151](../../../../../apps/crown/workflow.cpp#L147); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Artifact
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a locally admitted physical plan and its proof representation. |
| inputs / outputs | Artifact owns PhysicalPlan, diagnostic certificate Json and optional genuine VerifiedOptimum from loading. |
| invariants | JSON certificate is replay input, never authority by itself. Compile compatibility result and loaded typed proof have different phases; constant operator has null certificate. |
| ownership | Owns independent tool plan/DOM and typed proof handle; runtime receiving copy is separate. |
| failure | Private construction only after branch-specific admission; no default proof flags accepted. |
| cost | Immutable plan/proof handle retention plus ordinary Json ownership. |
| Design | [docs/cli.md](../../../../cli.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0027

[Lines 152–152](../../../../../apps/crown/workflow.cpp#L152); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L152-L152:sha256:14e4dbd14794a7551a54f20603f15901aff1c7d32fc0d6003b8b3aa4a9ada3e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Existing set-family admission only; nullable/bag library APIs are separate. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [apps/crown/workflow.cpp](../../../../../apps/crown/workflow.cpp), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0028

[Lines 153–175](../../../../../apps/crown/workflow.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Artifact compile(Arguments& arguments)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the existing admitted set SQL family to a physical workflow artifact. |
| inputs / outputs | Consumes SQL/catalog/options/search budget, binds/admit_sql; constant-empty lowers empty operator, otherwise minimum_tree must prove original minimum before lowering and serializing certificate. |
| invariants | No SqlRowsProgram, grouped aggregate or W06 transaction API invoked. Trusted local compatibility search result is required complete; serialized artifact must later undergo independent typed replay. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Admission/resource/unsupported plan errors return no artifact; compile only has no root/sink writes. |
| cost | Bounded file reads + SQL/parser/catalog/structural admission/search/lowering + ordinary certificate DOM; no native update timing claim. |
| Design | [docs/cli.md](../../../../cli.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_support.md](../../../../sql_support.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0029

[Lines 176–176](../../../../../apps/crown/workflow.cpp#L176); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L176-L176:sha256:1cfcbcb36f97b043045108c18cadcefc07d5bffc4cf2ba03ee5befcaf7bf7c27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Reconstruct the plan and independently replay proof; JSON flags are not authority. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [apps/crown/workflow.cpp](../../../../../apps/crown/workflow.cpp), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0030

[Lines 177–203](../../../../../apps/crown/workflow.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Artifact artifact(const std::string& path,std::uint64_t proof_work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load a workflow artifact by reconstructing plan and independently checking its proof. |
| inputs / outputs | Strict three-field schema1 envelope; read_physical validates reconstruction. Constant-false requires null certificate; tree route parses bound claim, replays proof quantum and compares typed optimum height plus exact serialized witness tree. |
| invariants | Raw JSON/digests do not authorize proof. A normal compiled workflow requires selected tree equal the independently checked minimum witness, stricter than general report query-wide evidence. |
| ownership | Returns admitted tool plan, retained encoded certificate and genuine typed optimum; no mutable session/root exists yet. |
| failure | Envelope/plan/certificate/replay/height/tree mismatch or resource errors precede durable setup. |
| cost | Up to64MiB read/DOM, nested encoding/reparse/plan validation, proof replay and two write_tree DOM validation/comparisons; ordinary tool overlap before receiving native state. |
| Design | [docs/cli.md](../../../../cli.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0031

[Lines 204–207](../../../../../apps/crown/workflow.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
observability::HeightEvidence evidence(const Artifact& built)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose only genuine loaded minimum evidence to EXPLAIN. |
| inputs / outputs | Returns retained VerifiedOptimum if present, else monostate. |
| invariants | Does not turn diagnostic Json certificate or constant-empty operator into original minimum proof. |
| ownership | Returned typed proof retains original immutable binding owner. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Fixed optional/shared-handle copy. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0032

[Lines 208–212](../../../../../apps/crown/workflow.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::unique_ptr<std::istream> input(const std::string& path)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open the requested physical input stream as session-owned source. |
| inputs / outputs | Creates binary ifstream, checks open, returns unique istream. |
| invariants | Opening does not validate source records or seek restored position; native recovery/session owns those rules. |
| ownership | Returned unique stream becomes session-owned; buffering remains caller/tool boundary. |
| failure | io_error on open; allocation failure before session construction. |
| cost | Ordinary stream/control allocation and file open. |
| Design | [docs/cli.md](../../../../cli.md) |

## B0033

[Lines 213–217](../../../../../apps/crown/workflow.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,32> identifier(const std::string& text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse exact query/sink identifier spelling. |
| inputs / outputs | Requires exactly32 lowercase hex characters; copies ASCII spelling into array&lt;char,32&gt;. |
| invariants | This is not decoding32 binary bytes or an authenticated receipt; identity is later bound to actual files. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | usage on wrong length/character. |
| cost | Fixed32-byte validation/copy. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0034

[Lines 218–220](../../../../../apps/crown/workflow.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,32> query_id(const CompiledProgram& program)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive default workflow query label from admitted source digest. |
| inputs / outputs | Copies first32 ASCII characters of physical_source_sha256 into fixed query-id array. |
| invariants | Navigation/binding label, not a substitute for full typed source/plan/file validation. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Fixed digest accessor/copy. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0035

[Lines 221–223](../../../../../apps/crown/workflow.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::SessionLocalSinkOptions sink_options(const CompiledProgram& program)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive default local sink label from physical plan digest. |
| inputs / outputs | Starts SessionLocalSinkOptions and fills32 ASCII sink-id bytes from physical_sha256. |
| invariants | Other sink defaults remain actual native defaults; attached file/root binding is separately checked. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Fixed metadata copy, no file creation. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0036

[Lines 224–224](../../../../../apps/crown/workflow.cpp#L224); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L224-L224:sha256:44c54b1953d89a69040c31930eb484ee95322460227d777e63bc39ce42c54d93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Session commit owns the WAL/native publication barrier, not this stepping loop. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [apps/crown/workflow.cpp](../../../../../apps/crown/workflow.cpp), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0037

[Lines 225–225](../../../../../apps/crown/workflow.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish(runtime::QuerySession& session)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete one already pending native session epoch and commit it. |
| inputs / outputs | Steps until DeltaStep::prepared, then session.commit(). |
| invariants | Real session owns resumability/WAL decision and publication. No extra event read, output acknowledgement or retry after uncertain durable failure. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Unbounded synchronous completion within native configured work/memory/spool caps; no wall-time quantum here. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0038

[Lines 226–234](../../../../../apps/crown/workflow.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t deliver(runtime::QuerySession& session)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deliver every committed physical output epoch not yet verified by local sink. |
| inputs / outputs | Compares actual sink verified sequence with committed sequence; calls deliver_local_epoch and checked-sums accepted rows. |
| invariants | Native receipt/duplicate verification, including empty epochs, defines durable prefix; stdout never supplies acknowledgement. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Sink/recovery/work/error or counter overflow can follow earlier durable delivery; no compensating rollback or blind reapply. |
| cost | O(backlogged epoch rows+wire/file/fsync work), not fixed row count metadata only. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0039

[Lines 235–238](../../../../../apps/crown/workflow.cpp#L235); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void accumulate(std::uint64_t& total,std::uint64_t amount)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate benchmark durations without uint64 overflow. |
| inputs / outputs | Adds amount only if it fits remaining range. |
| invariants | Unlike saturating diagnostic timers, this CLI aggregate rejects exhaustion. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | counter_overflow; native effects already completed are retained. |
| cost | Fixed arithmetic/branch. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0040

[Lines 239–242](../../../../../apps/crown/workflow.cpp#L239); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t nanoseconds(std::chrono::steady_clock::time_point begin,std::chrono::steady_clock::time_point end)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one measured steady-clock interval to nonnegative nanoseconds. |
| inputs / outputs | duration_cast count positive becomes uint64, otherwise0. |
| invariants | Reads provided timestamps only; not a new clock or global timing/proof guarantee. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Fixed chrono arithmetic. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0041

[Lines 243–256](../../../../../apps/crown/workflow.cpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string snapshot(runtime::QuerySession& session,std::size_t limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a current session snapshot and actual durable frontiers. |
| inputs / outputs | Obtains owning snapshot, sink/generation state; writes rows/progress/committed and verified sequence, generation/work/sink/account bytes. |
| invariants | Snapshot is an explicit native read/copy; returned requested-memory statistic includes live snapshot allocations at that point, not process RSS. Report encoding is separate from sink authority. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Snapshot/capture/output errors can happen after durable changes; no source reapplication or sink rollback. |
| cost | Full result cursor/snapshot plus source progress copy, native account requests and O(output rows/scalar bytes) ordinary encoding. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0042

[Lines 257–272](../../../../../apps/crown/workflow.cpp#L257); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string results(runtime::QuerySession& session,std::uint64_t sequence,std::size_t limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and encode one actual durable local output epoch. |
| inputs / outputs | read_local_epoch validates/owns epoch; header supplies real query/sink/physical IDs; ordered raw signed rows are formatted. |
| invariants | No export-based acknowledgement or recomputed fake result; read may allocate owning payloads before final text cap. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Native file/binding/resource/output failures do not revoke already persisted sink bytes. |
| cost | File/codec epoch read and native owning copy + O(rows/scalar/encoded bytes). |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0043

[Lines 273–422](../../../../../apps/crown/workflow.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int workflow(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch compiled file workflows through real native source/root/sink boundaries. |
| inputs / outputs | Handles compile/verify/compiled inspect first; then new run/benchmark or actual restore and snapshot/checkpoint/results, with branch-specific options validated before setup. |
| invariants | Set-family physical stream only; one command can create/durably update files before reporting fails. Query/sink labels never bypass full plan/source/checkpoint/WAL/sink validation. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Typed operation outcomes govern recovery. Final main checks stdout and contains diagnostic exceptions; process exit or missing stdout cannot establish unchanged or durable state. |
| cost | Branch-specific compile/proof receiving freeze/native epochs/recovery/fsync/scan/output; benchmark reporting explicitly excluded from processing timestamps. |
| Design | [docs/cli.md](../../../../cli.md), [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

```text
if(arguments.command=="compile")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish compiled set-family artifact. |
| inputs / outputs | Compile before private encoding/emit. |
| invariants | No root/sink side effect; output proof still rechecked when loaded. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Compile/search/lower plus complete encoding. |
| Design | [docs/cli.md](../../../../cli.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
if(arguments.command=="verify-trace")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run bounded modeled relational trace diagnostic. |
| inputs / outputs | Admits profile/native/reference/event caps, loads checked artifact, verifies complete requested stream. |
| invariants | Does not verify durable restart or independent SQL adapter semantics. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Full two-source native/reference recomputation. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md) |

```text
if(arguments.command=="validate-plan")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate compiled plan and minimum/operator scope. |
| inputs / outputs | Loads proof-checked artifact, emits typed validity/source/hash/height status. |
| invariants | constant_false checked operator is not original minimum. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Artifact/proof replay plus fixed report. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
if(arguments.command=="explain")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain a compiled admitted artifact. |
| inputs / outputs | Loads proof and typed report, selects bounded text/json/dot/tree-json. |
| invariants | No runtime/durable sink created. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Proof replay/report freeze/format. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
if(creating) {
    const auto format
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit new-run stream/mode/spool/observation configuration. |
| inputs / outputs | Consumes only creation flags and optional benchmark declaration. |
| invariants | Restore obtains saved policy instead of silently accepting unrelated creation flags. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Option copying/admission only. |
| Design | [docs/cli.md](../../../../cli.md) |

```text
const auto built=artifact(arguments.positional[0],proof_work);auto program=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare actual plan/ID authority before file workflow. |
| inputs / outputs | Loads independently checked artifact, freezes standalone compiler metadata and derives validated optional labels. |
| invariants | Native session/recovery receives its own configured finite grant; digest prefixes do not replace full binding. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Artifact replay+compiler freeze and receiving setup. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

```text
session=runtime::QuerySession::create(program,input(arguments.positional[1]),session_options);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create new native source/root/journal/sink. |
| inputs / outputs | Session creates receiving query state, enables generation then creates local sink. |
| invariants | Paths must be new; a later failure can leave prior file publication durable/uncertain. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Native admission and synchronous checkpoint/WAL/root/sink creation. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

```text
session=runtime::QuerySession::restore_generation_with_local_sink
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore actual selected native state with bound durable sink. |
| inputs / outputs | Validates root/checkpoint/journal/sink/source from origin with optional receiving cap. |
| invariants | Actual file authority controls recovery/repair; caller labels/exit status cannot assert outcome. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | File scan/hash/replay/native reconstruction and possible validated repair. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

```text
if(running) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit and durably deliver each requested physical input epoch. |
| inputs / outputs | Delivers recovered backlog first, starts source, begin→finish commit→deliver per event; checked timing/count sums. |
| invariants | Earlier committed/delivered prefix survives later failure; no batch-wide transaction. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Input, native/WAL and sink sync per epoch. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

```text
}else if(arguments.command=="checkpoint") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rotate/optionally retire only through actual native checkpoint protocol. |
| inputs / outputs | Delivers output, completes logged pending input if present, rotates generation and optional retirement. |
| invariants | Can intentionally finish one pending event; retirement requires native authenticated receipt/root conditions. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Native replay/commit/delivery plus durable checkpoint/root/history work. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

```text
}else if(reading){emit(results
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one bound physical sink epoch. |
| inputs / outputs | Calls results and reports complete epoch. |
| invariants | Report view is not acknowledgement or sink rewrite. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Actual file/codec/read copy and output. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

```text
if(arguments.command=="benchmark") {
    const auto report
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report one durable native run with actual receipt. |
| inputs / outputs | After processing timestamp, captures EXPLAIN JSON then parses nested mode/metrics and formats snapshot/receipt/timings. |
| invariants | Single run, not repeated protocol/speedup; initialization/processing exclude reporting and share fields carefully. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Additional capture/gauge/snapshot/DOM parse and nested re-encoding outside measured processing. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md), [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

```text
emit(snapshot(*session,limit));return 0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish final snapshot only after command work. |
| inputs / outputs | Formats current state/frontiers then emits. |
| invariants | Report failure does not revoke durable input/output prefix. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Snapshot scan/copies and complete encoding. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0044

[Lines 423–427](../../../../../apps/crown/workflow.cpp#L423); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void diagnostic(std::string_view code,std::string_view message,const Json& details=nullptr)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build workflow process JSON diagnostics with optional typed file details. |
| inputs / outputs | Creates schema1 error/message DOM, copies details if present, dumps to stderr. |
| invariants | Presentation only; it cannot infer rollback/durable success or replace native outcome fields. Ordinary Json/string allocation still occurs inside catch handlers. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Persistent C++ OOM or diagnostic encoding can escape this helper and its active dispatcher catch. Final main contains standard diagnostic exceptions with fixed JSON literals, without retrying completed work. |
| cost | O(message/details bytes) DOM/dump allocation and stderr I/O. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0045

[Lines 428–428](../../../../../apps/crown/workflow.cpp#L428); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L428-L428:sha256:1bf7b9efe002ba8910998d9a291b0fd080b1ec4908faeae9f7932f78b0f0784c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Preserve typed fault/stage/outcome; a diagnostic never authorizes blind retry. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [apps/crown/workflow.cpp](../../../../../apps/crown/workflow.cpp), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0046

[Lines 429–435](../../../../../apps/crown/workflow.cpp#L429); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Failure> void file_diagnostic(std::string_view code,const Failure& error)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve actual typed durable file failure outcome in a diagnostic. |
| inputs / outputs | Maps outcome index to unchanged/unknown/durable and writes fault/stage/native-error/temp-cleanup fields. |
| invariants | Unknown is not safely retryable success/failure; this function neither rescans files nor guesses publication from exit status. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Diagnostic allocation itself can fail after native failure; original operation outcome must be recovered from files, not invented. |
| cost | Fixed typed fields plus allocating Json/details/error encoding. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

## B0047

[Lines 436–436](../../../../../apps/crown/workflow.cpp#L436); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L436-L436:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in workflow.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [apps/crown/workflow.cpp](../../../../../apps/crown/workflow.cpp), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0048

[Lines 437–458](../../../../../apps/crown/workflow.cpp#L437); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int crown::cli::workflow_main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate workflow/native/durable failures at the private application boundary. |
| inputs / outputs | Runs workflow and catches Error, Json encoding/parse, native memory/image/checkpoint/generation/journal/sink/session failures, bad_alloc and remaining stdexceptions; returns1 after error presentation. |
| invariants | Distinct typed file fault/stage/publication/outcome is necessary; no handler retries command, revokes durable authority or acknowledges stdout. Catch ordering preserves derived memory and file categories. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Typed process catches preserve component outcomes. Exceptions from their diagnostic bodies bypass sibling handlers and reach final main, whose fixed fallbacks contain C++ bad_alloc and other standard exceptions. |
| cost | One terminal presentation path per command, ordinary diagnostic DOM/dump; no hot-path per-row exception layer. |
| Design | [docs/cli.md](../../../../cli.md), [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |
