# `apps/crown/explain.cpp` — block usage map

[Source](../../../../../apps/crown/explain.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `1aa3c0be6ae1e4b8d474dbce2fb6ce8f1e42ad38296b6d64f10936c02f2534df`. 156 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../apps/crown/explain.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–21](../../../../../apps/crown/explain.cpp#L15) | Callable definition: std::string read(const std::string& path) | calls input, Error, gcount, size; returns result; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../apps/crown/explain.cpp#L22) | Callable definition: std::uint64_t integer(std::string_view text) | calls std::from_chars, data, size, Error; returns value · [reviewed contract](#b0003) |
| [B0004 · 23–43](../../../../../apps/crown/explain.cpp#L23) | Type/record definition: struct Arguments | returns {}; value; growth emplace; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 44–49](../../../../../apps/crown/explain.cpp#L44) | Callable definition: template&lt;class Report&gt;std::string encode(const Report& report,const Arguments& a) | calls io::write_explain_json, io::write_explain_dot, io::write_explain_tree_json, io::write_explain_text; returns io::write_explain_json(report,a.text); io::write_explain_dot(report,a.text) · [reviewed contract](#b0005) |
| [B0006 · 50–57](../../../../../apps/crown/explain.cpp#L50) | Callable definition: template&lt;class Owner&gt;std::string encode_memory(const Owner& owner,const Arguments& a) | calls runtime::memory::capture, Error, io::write_memory_report, dump; returns result · [reviewed contract](#b0006) |
| [B0007 · 58–69](../../../../../apps/crown/explain.cpp#L58) | Callable definition: runtime::DeltaOptions delta_options(Arguments& a) | calls take, Error, integer; returns o · [reviewed contract](#b0007) |
| [B0008 · 70–74](../../../../../apps/crown/explain.cpp#L70) | Callable definition: std::shared_ptr&lt;const runtime::DeclaredBenchmarkContext&gt; labels(Arguments& a) | calls take, std::move; returns {}; std::make_shared&lt;const runtime::DeclaredBenchmarkContext&gt;(std::move(v)); growth make_shared · [reviewed contract](#b0008) |
| [B0009 · 75–85](../../../../../apps/crown/explain.cpp#L75) | Callable definition: observability::HeightEvidence evidence(Arguments& a,const PhysicalPlan& plan) | calls take, Error, integer, io::read_height_certificate; returns {}; *checked-&gt;optimum(); source comment (unverified): // Explicit CLI proof operation, never hidden inside capture/export. · [reviewed contract](#b0009) |
| [B0010 · 86–130](../../../../../apps/crown/explain.cpp#L86) | Callable definition: std::string run(Arguments& a) | calls io::read_document, read, number, take; returns encode(observability::QueryExplanation::capture(owner),a); encode(observability::QueryExplanation::…; growth make_unique; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 131–131](../../../../../apps/crown/explain.cpp#L131) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 132–156](../../../../../apps/crown/explain.cpp#L132) | Callable definition: int crown::cli::explain_main(int argc,char** argv) | calls std::string_view, crown::Error, args, run; returns 0; 0; 1 loop sites · [reviewed contract](#b0012) |

## B0001

[Lines 1–14](../../../../../apps/crown/explain.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using namespace crown;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind private EXPLAIN helpers to typed Crown APIs. |
| inputs / outputs | Imports public plan/report/runtime names through included APIs. |
| invariants | Compile-time lookup only; no admitted plan or owner from namespace aliases. |
| ownership | No owner introduced. |
| failure | Declaration mismatches fail compilation. |
| cost | No runtime work/storage. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

## B0002

[Lines 15–21](../../../../../apps/crown/explain.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read(const std::string& path)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one EXPLAIN artifact within a fixed 16MiB transport limit. |
| inputs / outputs | Binary ifstream is copied in 4096-byte blocks, rejecting growth beyond limit; only clean EOF returns owning text. |
| invariants | File bytes are tool DTO memory, not native query grant. Read is before artifact parsing/proof admission. |
| ownership | Local stream closes at return; returned string owns complete bytes. |
| failure | io_error/resource_limit/allocation failure returns no partial artifact. |
| cost | O(file bytes) synchronous I/O and ordinary string capacity/copies. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

## B0003

[Lines 22–22](../../../../../apps/crown/explain.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t integer(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one complete unsigned EXPLAIN numeric option. |
| inputs / outputs | from_chars uint64 must consume every byte without conversion error. |
| invariants | No whitespace/negative/partial/default-on-error coercion. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | usage on invalid spelling; no state mutation. |
| cost | O(option bytes), inline conversion. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

## B0004

[Lines 23–43](../../../../../apps/crown/explain.cpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Arguments
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own and consume EXPLAIN positional/options with format-specific validation. |
| inputs / outputs | Constructor requires subcommand/path and unique option-value pairs; validates format/memory-json applicability/max bytes. take removes one option, number parses or falls back, finished rejects leftovers. |
| invariants | memory-json cannot carry proof/benchmark labels and requires runtime/session. Size_t casts use current host width; no native grant is inferred from export bytes. |
| ownership | Arguments owns strings/map; argv borrowed only while copying. |
| failure | usage/conversion/allocation errors precede command work; unconsumed options reject before owner construction in each branch. |
| cost | O(argument text + ordered option-map operations/copies), ordinary tool allocation. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

## B0005

[Lines 44–49](../../../../../apps/crown/explain.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Report>std::string encode(const Report& report,const Arguments& a)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch a typed report to the selected bounded EXPLAIN transport. |
| inputs / outputs | json/dot/tree-json call exact overload; admitted remaining format is text. |
| invariants | Report authority remains typed; encoder does not advance search/runtime. memory-json is handled separately before this helper. |
| ownership | Returned string owns bytes; report borrowed. |
| failure | Missing witness, encoding, output-byte or allocation errors propagate. |
| cost | Full report formatting and ordinary returned string under encoded-byte cap. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

## B0006

[Lines 50–57](../../../../../apps/crown/explain.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Owner>std::string encode_memory(const Owner& owner,const Arguments& a)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture and encode the separate native memory report. |
| inputs / outputs | Requires complete consistent memory capture with report, materializes Json/dump then checks final encoded length. |
| invariants | Cap check follows DOM/string creation; it does not prebound those temporaries. Capture stop inconsistent maps runtime_contract; other incomplete capture maps resource_limit. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Incomplete/invalid capture or output/allocation failure returns no text; report is diagnostic, not native admission proof. |
| cost | Explicit account/operator report capture scans plus DOM/dump/copy and final length check, outside update work. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0007

[Lines 58–69](../../../../../apps/crown/explain.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::DeltaOptions delta_options(Arguments& a)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume EXPLAIN runtime mode/observation/live/completion/view and resource options. |
| inputs / outputs | Starts actual DeltaOptions defaults (delta mode), accepts declared spellings and optional work/memory/spool-row overrides. |
| invariants | Requested options remain separate from resolved profile; export byte cap, work grants, memory cap and spool rows have different domains. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Fixed option set plus map/string conversion work; no runtime constructed here. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

## B0008

[Lines 70–74](../../../../../apps/crown/explain.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const runtime::DeclaredBenchmarkContext> labels(Arguments& a)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain optional unmeasured benchmark label declarations. |
| inputs / outputs | Consumes four optional labels; all absent returns null, otherwise ordinary shared immutable context. |
| invariants | Caller labels are neither measured identity nor proof/durable receipt. |
| ownership | Returned shared context owns labels and may be retained by runtime observation. |
| failure | Option-copy/allocation failure precedes label publication. |
| cost | Fixed option count plus ordinary string/shared control allocation. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

## B0009

[Lines 75–85](../../../../../apps/crown/explain.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
observability::HeightEvidence evidence(Arguments& a,const PhysicalPlan& plan)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently replay an explicitly requested height certificate. |
| inputs / outputs | Reads/binds claim to actual plan core catalog/query, creates CertificateReplay and advances exactly one chosen proof quantum; returns genuine optimum only if established. |
| invariants | No certificate means empty evidence; proof-work without certificate rejects. This explicit CLI operation lies outside capture/export; partial replay cannot mint minimum. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | usage/certificate parse/resource or incomplete/rejected proof returns Error, with no report or mutable runtime. |
| cost | Artifact read, native claim parse/binding, replay admission/quantum and typed handle retention. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0010

[Lines 86–130](../../../../../apps/crown/explain.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string run(Arguments& a)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement legacy EXPLAIN physical/runtime/session and query/search command branches. |
| inputs / outputs | Reads actual typed input, consumes applicable flags, explicitly advances selected search/replay/session work and returns complete chosen report string. |
| invariants | Only implemented set-family native/session paths are instantiated; W05 nullable/bag and aggregate library APIs are not wired here. Command-side advance and report capture/export remain separate phases. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Branch-specific file/proof/admission/native/capture/encoding work; ordinary tool copies and optional full-state gauges outside engine update limits. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/cli.md](../../../../cli.md) |

```text
if(a.command=="query" || a.command=="progress" || a.command=="replay")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect an actual exact-search/replay owner. |
| inputs / outputs | Reads Document, explicit --work defaults0, captures typed QueryExplanation. |
| invariants | No hidden advance inside capture/export; tree output needs published witness. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Admission, optional explicit quantum, owning capture/formatting. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

```text
if(a.command=="replay"){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect independent certificate replay. |
| inputs / outputs | Requires certificate and applicable flags before creating owner/optional advance. |
| invariants | Partial owner progress is not checked original proof. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Certificate read/bind/admission/replay. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

```text
planner::SearchOptions options;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect exact search with strict/best-found publication policy. |
| inputs / outputs | Builds actual owner, optional explicit quantum, captures. |
| invariants | Observed strict upper can be unpublished; no invented tree. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Original-query admission/search/capture. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

```text
if(a.command=="physical"){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain an admitted physical plan with optional checked evidence. |
| inputs / outputs | Consumes flags, creates compiler-only report. |
| invariants | No runtime or native input created. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Physical read/proof, standalone report freeze/output. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

```text
if(a.command=="runtime"){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain an empty native runtime. |
| inputs / outputs | Constructs DeltaRuntime/options/labels, memory or plan capture. |
| invariants | Runtime state is actual owner; no input events loaded here. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Native receiving metadata/state construction and capture/output. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

```text
runtime::SessionOptions session_options;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure actual legacy EXPLAIN session source and lifecycle. |
| inputs / outputs | Admits JSONL/binary source/events/steps/disposition/lifecycle before session creation. |
| invariants | Owned stream/source context, no W05 nullable/bag route. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Option parsing, stream/session setup. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

```text
if(events){owner->start();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance only requested session events/steps before capture. |
| inputs / outputs | Drains/discards or preserves/transfers output according to options; commit only prepared epochs. |
| invariants | Step cap can leave private work; retain can stop at unread output, then explicit stop/drop preserves lifecycle semantics. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Actual native steps/epochs/output followed by capture; no timing benchmark. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

## B0011

[Lines 131–131](../../../../../apps/crown/explain.cpp#L131); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L131-L131:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in explain.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [apps/crown/explain.cpp](../../../../../apps/crown/explain.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 132–156](../../../../../apps/crown/explain.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int crown::cli::explain_main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present EXPLAIN help/results and bounded command exit categories. |
| inputs / outputs | Constructs Arguments/run then writes complete result; help prints supported options. Error codes are sanitized to lowercase/digit/underscore; usage2/text3/resource4/other1, bad_alloc4 and stdexception invalid_document1. |
| invariants | No error-handler retry or rollback. Current writes check stream state but do not flush before success; parent process/output finding is separate. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Three catches preserve EXPLAIN presentation. Its fixed bad_alloc fallback avoids Json construction; final main contains diagnostic exceptions and checks buffered stdout. Completed command effects are not retried. |
| cost | Help or one complete output write plus diagnostic presentation; no per-row handler machinery. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |
