# `src/planner/selection_binding.cpp` — block usage map

[Source](../../../../../src/planner/selection_binding.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Require exact source/query/backend binding before admitting cached or candidate plan authority.

Snapshot SHA-256: `fe97b0a6c27b7d78fa043d64a61ad8b96ddb4c804a5553967ed554a45cd8742d`. 337 lines partitioned into 60 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/planner/selection_binding.cpp#L1) | Imports dependencies; declares namespace scope; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Private v1 tagged, length-framed bytes. Every append reserves its logical · [reviewed contract](#b0001) |
| [B0002 · 14–15](../../../../../src/planner/selection_binding.cpp#L14) | Callable definition: explicit Encoder(Budget& b, std::string_view domain,bool retained=false) :budget(b),bytes(buffer(b,retained)) | calls budget, bytes, buffer, raw · [reviewed contract](#b0002) |
| [B0003 · 16–16](../../../../../src/planner/selection_binding.cpp#L16) | Explanatory comments or spacing. | source comment (unverified): // Select ordinary output or a receiving-account text allocator. See docs/query_memory.md. · [reviewed contract](#b0003) |
| [B0004 · 17–21](../../../../../src/planner/selection_binding.cpp#L17) | Callable definition: static Text buffer(Budget& b,bool retained) | calls constexpr, Text; returns {}; Text(resource::OwnerAllocator&lt;char&gt;(b.memory,; source comment (unverified): // Select ordinary output or a receiving-account text allocator. See docs/query_memory.md. · [reviewed contract](#b0004) |
| [B0005 · 22–23](../../../../../src/planner/selection_binding.cpp#L22) | Explanatory comments or spacing. | source comment (unverified): // Append exact raw bytes after logical work/key/payload admission. See · [reviewed contract](#b0005) |
| [B0006 · 24–27](../../../../../src/planner/selection_binding.cpp#L24) | Callable definition: void raw(std::string_view text) | calls size, keys, bytes, append; source comment (unverified): // Append exact raw bytes after logical work/key/payload admission. See · [reviewed contract](#b0006) |
| [B0007 · 28–28](../../../../../src/planner/selection_binding.cpp#L28) | Callable definition: void byte(char value) | calls keys, bytes, push_back; growth push_back · [reviewed contract](#b0007) |
| [B0008 · 29–29](../../../../../src/planner/selection_binding.cpp#L29) | Explanatory comments or spacing. | source comment (unverified): // Emit fixed eight-byte big-endian scalar payload. See docs/selection_binding.md. · [reviewed contract](#b0008) |
| [B0009 · 30–32](../../../../../src/planner/selection_binding.cpp#L30) | Callable definition: void word(std::uint64_t value) | calls byte; 1 loop sites; source comment (unverified): // Emit fixed eight-byte big-endian scalar payload. See docs/selection_binding.md. · [reviewed contract](#b0009) |
| [B0010 · 33–33](../../../../../src/planner/selection_binding.cpp#L33) | Callable definition: void u(std::uint64_t value) | calls byte, word · [reviewed contract](#b0010) |
| [B0011 · 34–34](../../../../../src/planner/selection_binding.cpp#L34) | Callable definition: void s(std::int64_t value) | calls byte, word · [reviewed contract](#b0011) |
| [B0012 · 35–35](../../../../../src/planner/selection_binding.cpp#L35) | Callable definition: template&lt;class T&gt; void enumeration(T value) | calls byte, word · [reviewed contract](#b0012) |
| [B0013 · 36–36](../../../../../src/planner/selection_binding.cpp#L36) | Callable definition: void boolean(bool value) | calls byte · [reviewed contract](#b0013) |
| [B0014 · 37–37](../../../../../src/planner/selection_binding.cpp#L37) | Callable definition: void text(std::string_view value) | calls byte, word, size, raw · [reviewed contract](#b0014) |
| [B0015 · 38–38](../../../../../src/planner/selection_binding.cpp#L38) | Callable definition: void record(std::string_view value) | calls byte, text · [reviewed contract](#b0015) |
| [B0016 · 39–39](../../../../../src/planner/selection_binding.cpp#L39) | Callable definition: void count(std::size_t value) | calls byte, word · [reviewed contract](#b0016) |
| [B0017 · 40–41](../../../../../src/planner/selection_binding.cpp#L40) | Explanatory comments or spacing. | source comment (unverified): // Distinguish optional absence from a present zero/empty payload. See · [reviewed contract](#b0017) |
| [B0018 · 42–44](../../../../../src/planner/selection_binding.cpp#L42) | Callable definition: template&lt;class T, class Function&gt; void optional(const std::optional&lt;T&gt;& value, Function function) | calls byte, function; source comment (unverified): // Distinguish optional absence from a present zero/empty payload. See · [reviewed contract](#b0018) |
| [B0019 · 45–45](../../../../../src/planner/selection_binding.cpp#L45) | Explanatory comments or spacing. | source comment (unverified): // Preserve complete ordered collection multiplicity. See docs/selection_binding.md. · [reviewed contract](#b0019) |
| [B0020 · 46–48](../../../../../src/planner/selection_binding.cpp#L46) | Callable definition: template&lt;class Range, class Function&gt; void sequence(const Range& values, Function function) | calls count, size, function; 1 loop sites; source comment (unverified): // Preserve complete ordered collection multiplicity. See docs/selection_binding.md. · [reviewed contract](#b0020) |
| [B0021 · 49–49](../../../../../src/planner/selection_binding.cpp#L49) | Callable definition: template&lt;class Range&gt; void ids(const Range& values) | calls sequence, u · [reviewed contract](#b0021) |
| [B0022 · 50–51](../../../../../src/planner/selection_binding.cpp#L50) | Explanatory comments or spacing. | source comment (unverified): // Embed complete unchanged P07-v2 typed Catalog/Query binding. See · [reviewed contract](#b0022) |
| [B0023 · 52–64](../../../../../src/planner/selection_binding.cpp#L52) | Callable definition: template&lt;class C,class Q&gt; void cq(const C& catalog, const Q& query) | calls nested, borrowed, rd::score_binding, record; source comment (unverified): // Embed complete unchanged P07-v2 typed Catalog/Query binding. See · [reviewed contract](#b0023) |
| [B0024 · 65–65](../../../../../src/planner/selection_binding.cpp#L65) | Callable definition: void catalog(const Catalog& value) | calls record, cq · [reviewed contract](#b0024) |
| [B0025 · 66–66](../../../../../src/planner/selection_binding.cpp#L66) | Callable definition: void catalog(const program::Catalog& value) | calls record, cq · [reviewed contract](#b0025) |
| [B0026 · 67–68](../../../../../src/planner/selection_binding.cpp#L67) | Explanatory comments or spacing. | source comment (unverified): // Encode exact scalar kind and canonical payload for ordinary/native values. See · [reviewed contract](#b0026) |
| [B0027 · 69–89](../../../../../src/planner/selection_binding.cpp#L69) | Callable definition: template&lt;class Scalar&gt; void scalar(const Scalar& value) | calls record, u, index, s; returns storage::InlineDecimal::copy_of(std::get&lt;4&gt;(value)); std::get&lt;4&gt;(value); growth copy_of; source comment (unverified): // Encode exact scalar kind and canonical payload for ordinary/native values. See · [reviewed contract](#b0027) |
| [B0028 · 90–90](../../../../../src/planner/selection_binding.cpp#L90) | Callable definition: template&lt;class Scalar&gt; void sql_value(const std::optional&lt;Scalar&gt;& value) | calls optional, scalar · [reviewed contract](#b0028) |
| [B0029 · 91–94](../../../../../src/planner/selection_binding.cpp#L91) | Callable definition: void sql_type(const frontend::SqlType& value) | calls record, enumeration, boolean, optional · [reviewed contract](#b0029) |
| [B0030 · 95–98](../../../../../src/planner/selection_binding.cpp#L95) | Callable definition: void bind_limits(const frontend::BindLimits& value) | calls record, optional, u · [reviewed contract](#b0030) |
| [B0031 · 99–101](../../../../../src/planner/selection_binding.cpp#L99) | Callable definition: void normalize_limits(const frontend::NormalizeLimits& value) | calls record, optional, u · [reviewed contract](#b0031) |
| [B0032 · 102–103](../../../../../src/planner/selection_binding.cpp#L102) | Explanatory comments or spacing. | source comment (unverified): // Encode complete typed SQL binding source and expression program. See · [reviewed contract](#b0032) |
| [B0033 · 104–128](../../../../../src/planner/selection_binding.cpp#L104) | Callable definition: template&lt;class Bound&gt; void bound(const Bound& value) | calls record, text, catalog, sequence; source comment (unverified): // Encode complete typed SQL binding source and expression program. See · [reviewed contract](#b0033) |
| [B0034 · 129–129](../../../../../src/planner/selection_binding.cpp#L129) | Explanatory comments or spacing. | source comment (unverified): // Encode full parameter-specialized normalized source. See docs/selection_binding.md. · [reviewed contract](#b0034) |
| [B0035 · 130–150](../../../../../src/planner/selection_binding.cpp#L130) | Callable definition: template&lt;class Normalized&gt; void normalized(const Normalized& value) | calls record, bound, sequence, sql_value; source comment (unverified): // Encode full parameter-specialized normalized source. See docs/selection_binding.md. · [reviewed contract](#b0035) |
| [B0036 · 151–151](../../../../../src/planner/selection_binding.cpp#L151) | Explanatory comments or spacing. | source comment (unverified): // Encode complete supplied tree representation and claims. See docs/selection_binding.md. · [reviewed contract](#b0036) |
| [B0037 · 152–162](../../../../../src/planner/selection_binding.cpp#L152) | Callable definition: template&lt;class Tree&gt; void tree(const Tree& value) | calls record, optional, u, sequence; source comment (unverified): // Encode complete supplied tree representation and claims. See docs/selection_binding.md. · [reviewed contract](#b0037) |
| [B0038 · 163–164](../../../../../src/planner/selection_binding.cpp#L163) | Explanatory comments or spacing. | source comment (unverified): // Bind complete physical policy, finite producer limits and optional indexed backend. See · [reviewed contract](#b0038) |
| [B0039 · 165–178](../../../../../src/planner/selection_binding.cpp#L165) | Callable definition: template&lt;class Options&gt; void options(const Options& value) | calls record, text, optional, u; source comment (unverified): // Bind complete physical policy, finite producer limits and optional indexed backend. See · [reviewed contract](#b0039) |
| [B0040 · 179–186](../../../../../src/planner/selection_binding.cpp#L179) | Callable definition: template&lt;class C,class Q,class Physical,class Normalized,class Options&gt; // Frame exact core, physical catalog, normalized program… | calls record, cq, catalog, optional; source comment (unverified): // Frame exact core, physical catalog, normalized program and options as one source. See · [reviewed contract](#b0040) |
| [B0041 · 187–197](../../../../../src/planner/selection_binding.cpp#L187) | Callable definition: template&lt;class Plan&gt; void source(const Plan& p) | calls catalog, query, source_catalog, normalized; source comment (unverified): // Optional execution policy changes artifact reuse, not physical identity. · [reviewed contract](#b0041) |
| [B0042 · 198–199](../../../../../src/planner/selection_binding.cpp#L198) | Explanatory comments or spacing. | source comment (unverified): // Derive expected direct or basis source from the admitted snapshot. See · [reviewed contract](#b0042) |
| [B0043 · 200–207](../../../../../src/planner/selection_binding.cpp#L200) | Callable definition: template&lt;class SourceValue&gt; void source(const CandidateSnapshot& snapshot, const SourceValue& value) | calls std::visit, constexpr, original_proof, binding; source comment (unverified): // Derive expected direct or basis source from the admitted snapshot. See · [reviewed contract](#b0043) |
| [B0044 · 208–211](../../../../../src/planner/selection_binding.cpp#L208) | Callable definition: void context(const CandidateContext& value) | calls record, enumeration, text · [reviewed contract](#b0044) |
| [B0045 · 212–217](../../../../../src/planner/selection_binding.cpp#L212) | Callable definition: void limits(const rank::Limits& value) | calls record, u, optional, s · [reviewed contract](#b0045) |
| [B0046 · 218–241](../../../../../src/planner/selection_binding.cpp#L218) | Callable definition: template&lt;class RequestValue&gt; void request(const RequestValue& value) | calls record, enumeration, u, index; guard else require(std::is_same_v&lt;T,std::monostate&gt;);; source comment (unverified): // An absent declaration preserves the original request bytes. Presence · [reviewed contract](#b0046) |
| [B0047 · 242–242](../../../../../src/planner/selection_binding.cpp#L242) | Explanatory comments or spacing. | source comment (unverified): // Bind exact as-of ranking facts and capture configuration. See docs/selection_binding.md. · [reviewed contract](#b0047) |
| [B0048 · 243–260](../../../../../src/planner/selection_binding.cpp#L243) | Callable definition: void evidence(const rank::Evidence& value) | calls record, identity, u, boolean; source comment (unverified): // Bind exact as-of ranking facts and capture configuration. See docs/selection_binding.md. · [reviewed contract](#b0048) |
| [B0049 · 261–264](../../../../../src/planner/selection_binding.cpp#L261) | Closes surrounding scope/type. | source comment (unverified): // Check original core binding and full source agreement before scoring/publication. See · [reviewed contract](#b0049) |
| [B0050 · 265–281](../../../../../src/planner/selection_binding.cpp#L265) | Callable definition: void source_binding(const CandidateSnapshot& snapshot, const Source& source, const std::optional&lt;rank::Evidence&gt;& evidence, Budge… | calls original_proof, binding, original, actual; guard require(equal_bytes(original, actual, budget), Stop::binding_mismatch);; returns rd::score_binding(plan.catalog(),plan.query(),b,b.memory); source comment (unverified): // Check original core binding and full source agreement before scoring/publication. See · [reviewed contract](#b0050) |
| [B0051 · 282–283](../../../../../src/planner/selection_binding.cpp#L282) | Explanatory comments or spacing. | source comment (unverified): // Verify chosen compiled source and operator tree against the admitted candidate. See · [reviewed contract](#b0051) |
| [B0052 · 284–296](../../../../../src/planner/selection_binding.cpp#L284) | Callable definition: void compiled_binding(const CandidateSnapshot& snapshot, const Source& source, const MinimumHeightCandidate& candidate, const Com… | calls expected, source, query, empty; guard require(equal_bytes(expected.bytes, actual.bytes, budget), Stop::binding_mismatch);; source comment (unverified): // Verify chosen compiled source and operator tree against the admitted candidate. See · [reviewed contract](#b0052) |
| [B0053 · 297–298](../../../../../src/planner/selection_binding.cpp#L297) | Explanatory comments or spacing. | source comment (unverified): // Build the complete retained artifact-reuse key after fresh decision. See · [reviewed contract](#b0053) |
| [B0054 · 299–323](../../../../../src/planner/selection_binding.cpp#L299) | Callable definition: SelectionText cache_binding(const SelectionData& value, Origin origin, Budget& budget) | calls out, record, u, has_value; guard const auto candidate = value.snapshot.candidate(i); require(candidate.has_value());; returns plan.options().indexed_storage.has_value(); std::move(out.bytes); 1 loop sites; source comment (unverified): // Build the complete retained artifact-reuse key after fresh decision. See · [reviewed contract](#b0054) |
| [B0055 · 324–324](../../../../../src/planner/selection_binding.cpp#L324) | Explanatory comments or spacing. | source comment (unverified): // Export diagnostic bytes for one exact Value. See docs/selection_binding.md. · [reviewed contract](#b0055) |
| [B0056 · 325–327](../../../../../src/planner/selection_binding.cpp#L325) | Callable definition: std::string scalar_binding_record(const Value& value, Budget& budget) | calls out, scalar, std::move; returns std::move(out.bytes); source comment (unverified): // Export diagnostic bytes for one exact Value. See docs/selection_binding.md. · [reviewed contract](#b0056) |
| [B0057 · 328–330](../../../../../src/planner/selection_binding.cpp#L328) | Callable definition: std::string tree_binding_record(const FreeConnexTree& value, Budget& budget) | calls out, tree, std::move; returns std::move(out.bytes) · [reviewed contract](#b0057) |
| [B0058 · 331–333](../../../../../src/planner/selection_binding.cpp#L331) | Callable definition: std::string program_binding_record(const frontend::NormalizedSql& value, Budget& budget) | calls out, normalized, std::move; returns std::move(out.bytes) · [reviewed contract](#b0058) |
| [B0059 · 334–336](../../../../../src/planner/selection_binding.cpp#L334) | Callable definition: std::string core_binding_record(const Catalog& catalog, const Query& query, Budget& budget) | calls out, cq, std::move; returns std::move(out.bytes) · [reviewed contract](#b0059) |
| [B0060 · 337–337](../../../../../src/planner/selection_binding.cpp#L337) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::selection::detail · [reviewed contract](#b0060) |

## B0001

[Lines 1–13](../../../../../src/planner/selection_binding.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Text=std::string> class Encoder {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build deterministic versioned selection reproduction bytes. |
| inputs / outputs | Owns chosen text sink and borrows shared Budget. |
| invariants | Bytes preserve typed framing and exact field order; they authorize no proof/import/cache insertion. |
| ownership | Ordinary diagnostic text or account-backed scratch/capture text owns output. |
| failure | Budget/variant/allocation failures discard private output; prior logical debits remain. |
| cost | Full visited bytes/components and capacity growth, not constant time per record. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md), [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md) |

## B0002

[Lines 14–15](../../../../../src/planner/selection_binding.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Encoder(Budget& b, std::string_view domain,bool retained=false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare output allocator and emit the unframed versioned domain. |
| inputs / outputs | Borrows Budget, chooses buffer and appends domain. |
| invariants | Domain must match intended private grammar; retained selects memory purpose only. |
| ownership | Owns bytes; budget borrow ends with encoder. |
| failure | Allocator/domain append can fail before any output is returned. |
| cost | Domain byte charges/copy plus buffer allocation. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0003

[Lines 16–16](../../../../../src/planner/selection_binding.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L16:sha256:80fe58305ab81440c84c659fabb75e6dd386523422700a9005d6cde88377e8cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for buffer: Select ordinary output or a receiving-account text allocator. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies buffer; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for buffer come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 17–21](../../../../../src/planner/selection_binding.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static Text buffer(Budget& b,bool retained) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select ordinary output or a receiving-account text allocator. |
| inputs / outputs | std::string starts empty; native Text gets capture or scratch purpose with selection attribution. |
| invariants | No fresh account/grant is created and no source/query traversal occurs. |
| ownership | Returned string retains its allocator/account. |
| failure | Invalid account or later storage allocation can fail. |
| cost | Fixed allocator metadata; empty string may use inline storage. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0005

[Lines 22–23](../../../../../src/planner/selection_binding.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L23:sha256:db8c23eedc1e9632b8ecffc6f4e5c391e137e16d59ba28a945b0bfad0db8df0a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for raw: Append exact raw bytes after logical work/key/payload admission. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies raw; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for raw come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0006

[Lines 24–27](../../../../../src/planner/selection_binding.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append exact raw bytes after logical work/key/payload admission. |
| inputs / outputs | Charges n key traffic (including work), n payload, then appends n bytes. |
| invariants | Accepted work/key debits can remain if later payload/storage fails; bytes are not escaped/normalized. |
| ownership | Borrows span for call; sink owns copied bytes. |
| failure | Budget/length/allocator errors propagate. |
| cost | O(new bytes) copy plus possible existing-buffer relocation. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0007

[Lines 28–28](../../../../../src/planner/selection_binding.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void byte(char value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one admitted grammar/payload byte. |
| inputs / outputs | Charges keys(1), bytes(1), then push_back. |
| invariants | Logical charges precede actual growth. |
| ownership | Sink owns byte. |
| failure | Later charge/allocation failure may retain accepted counters. |
| cost | One logical byte plus actual string growth. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0008

[Lines 29–29](../../../../../src/planner/selection_binding.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:1e35827ebdf7463599386e647401705d0121573b5fe9db37783d29dea09f7530
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for word: Emit fixed eight-byte big-endian scalar payload. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies word; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for word come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0009

[Lines 30–32](../../../../../src/planner/selection_binding.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void word(std::uint64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit fixed eight-byte big-endian scalar payload. |
| inputs / outputs | Calls byte for shifts 56 through 0. |
| invariants | Fixed width avoids decimal ambiguity; caller tags supply type. |
| ownership | Owns emitted bytes in sink. |
| failure | Any byte charge/growth may throw. |
| cost | Eight admitted byte operations. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0010

[Lines 33–33](../../../../../src/planner/selection_binding.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void u(std::uint64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame unsigned scalar as U plus eight bytes. |
| inputs / outputs | Preserves exact uint64 bits. |
| invariants | Unsigned differs from signed/enum/Boolean tags. |
| ownership | Borrows scalar/span synchronously; sink owns output. |
| failure | Sink/budget/length failures propagate with no published partial token. |
| cost | Nine bytes. Actual allocator/capacity costs remain. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0011

[Lines 34–34](../../../../../src/planner/selection_binding.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void s(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame signed scalar in modulo-2^64 representation. |
| inputs / outputs | I tag and converted uint64 word. |
| invariants | No decimal/float formatting or sign loss. |
| ownership | Borrows scalar/span synchronously; sink owns output. |
| failure | Sink/budget/length failures propagate with no published partial token. |
| cost | Nine bytes. Actual allocator/capacity costs remain. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0012

[Lines 35–35](../../../../../src/planner/selection_binding.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void enumeration(T value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame a caller-validated enum at its record position. |
| inputs / outputs | E tag plus underlying uint64 value. |
| invariants | Record/version supplies enum domain; visitor itself does not reject unknown values. |
| ownership | Borrows scalar/span synchronously; sink owns output. |
| failure | Sink/budget/length failures propagate with no published partial token. |
| cost | Nine bytes. Actual allocator/capacity costs remain. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0013

[Lines 36–36](../../../../../src/planner/selection_binding.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boolean(bool value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame a Boolean with an exact zero/one byte. |
| inputs / outputs | B tag and one binary byte. |
| invariants | False/true cannot alias integer payloads. |
| ownership | Borrows scalar/span synchronously; sink owns output. |
| failure | Sink/budget/length failures propagate with no published partial token. |
| cost | Two bytes. Actual allocator/capacity costs remain. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0014

[Lines 37–37](../../../../../src/planner/selection_binding.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void text(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame exact byte length and string body. |
| inputs / outputs | S tag, eight-byte length and raw bytes. |
| invariants | Embedded NUL/non-UTF bytes are preserved. |
| ownership | Borrows scalar/span synchronously; sink owns output. |
| failure | Sink/budget/length failures propagate with no published partial token. |
| cost | Length-dependent body copy plus fixed frame. Actual allocator/capacity costs remain. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0015

[Lines 38–38](../../../../../src/planner/selection_binding.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void record(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a named typed record. |
| inputs / outputs | R tag and framed record name. |
| invariants | Record names and field order are versioned together. |
| ownership | Borrows scalar/span synchronously; sink owns output. |
| failure | Sink/budget/length failures propagate with no published partial token. |
| cost | Name bytes and fixed frame. Actual allocator/capacity costs remain. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0016

[Lines 39–39](../../../../../src/planner/selection_binding.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void count(std::size_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame an ordered sequence length. |
| inputs / outputs | A tag and uint64 count. |
| invariants | Supported model domain fits encoded count; no sorting/deduplication occurs. |
| ownership | Borrows scalar/span synchronously; sink owns output. |
| failure | Sink/budget/length failures propagate with no published partial token. |
| cost | Nine bytes; elements separate. Actual allocator/capacity costs remain. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0017

[Lines 40–41](../../../../../src/planner/selection_binding.cpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L41:sha256:0ca974044871fd1aec18c061f34d691a717c4b867c517bd8a3c950ab335b5665
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for function: Distinguish optional absence from a present zero/empty payload. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies function; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for function come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0018

[Lines 42–44](../../../../../src/planner/selection_binding.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T, class Function> void optional(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish optional absence from a present zero/empty payload. |
| inputs / outputs | P tag, presence byte, then synchronous callback if present. |
| invariants | Callback encoding is part of the containing versioned grammar. |
| ownership | Borrows optional/callback during call. |
| failure | Callback or sink failures abort private record. |
| cost | Two bytes plus actual present payload. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0019

[Lines 45–45](../../../../../src/planner/selection_binding.cpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L45:sha256:b3943a9951114af9e6941ce4f2436f9ac424ceee7a9b5b598e4207f6306e6083
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for function: Preserve complete ordered collection multiplicity. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies function; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for function come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0020

[Lines 46–48](../../../../../src/planner/selection_binding.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range, class Function> void sequence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve complete ordered collection multiplicity. |
| inputs / outputs | Frames size then calls encoder callback for every value. |
| invariants | No implicit canonical reordering or semantic deduplication. |
| ownership | Borrows stable range/callback. |
| failure | Nested sink/budget failures propagate. |
| cost | Linear visited elements and all nested bytes. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0021

[Lines 49–49](../../../../../src/planner/selection_binding.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> void ids(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode exact local IDs in their supplied order. |
| inputs / outputs | Sequence of U(id.value). |
| invariants | IDs remain binding-local; key generation does not establish bounds. |
| ownership | Borrows range. |
| failure | Sink failures propagate; caller supplies valid artifact context. |
| cost | Nine bytes per ID plus count frame. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0022

[Lines 50–51](../../../../../src/planner/selection_binding.cpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L51:sha256:8c08de400f0487d7811b0eb138d0ddd6b160daf0e27e04adcc47ef0407beaf08
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Range: Embed complete unchanged P07-v2 typed Catalog/Query binding. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Range; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Range come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0023

[Lines 52–64](../../../../../src/planner/selection_binding.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class C,class Q> void cq(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Embed complete unchanged P07-v2 typed Catalog/Query binding. |
| inputs / outputs | Delegates nested encoding under carried budget/account, then frames candidate-binding-v2 and copies nested bytes. |
| invariants | Nested charges happen before outer frame; both copies are intentionally charged. No JSON, digest-only comparison or alpha-remapping. |
| ownership | Keeps native nested buffer alive through append; ordinary branch is explicit no-account diagnostic boundary. |
| failure | Borrowed visitor counters carry on exceptions; no partial key returns. |
| cost | Full model/metadata/constant binding traversal plus outer byte copy and actual growth. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0024

[Lines 65–65](../../../../../src/planner/selection_binding.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void catalog(const Catalog& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame the entire ordinary physical/source catalog. |
| inputs / outputs | Named catalog-with-empty-query and nested CQ with Query{}. |
| invariants | Includes unused tables and all metadata, not just query references. |
| ownership | Borrows catalog; temporary query is empty. |
| failure | Sink/visitor failures propagate. |
| cost | Full nested catalog encoding. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0025

[Lines 66–66](../../../../../src/planner/selection_binding.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void catalog(const program::Catalog& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame native physical catalog without ordinary export. |
| inputs / outputs | Uses empty program::Query and unchanged native CQ visitor. |
| invariants | No ordinary catalog mirror or semantic identity substitution. |
| ownership | Borrows immutable native ranges. |
| failure | Budget/account/sink failures propagate. |
| cost | Complete native catalog bytes and outer framing. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0026

[Lines 67–68](../../../../../src/planner/selection_binding.cpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L68:sha256:5ba2b72774aca39de182b7bf77c7f5318a31b9e488768798f3748b80adae97d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for index: Encode exact scalar kind and canonical payload for ordinary/native values. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies index; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for index come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0027

[Lines 69–89](../../../../../src/planner/selection_binding.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Scalar> void scalar(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode exact scalar kind and canonical payload for ordinary/native values. |
| inputs / outputs | Frames variant index, integer/string/Boolean/date or bounded InlineDecimal rendering. |
| invariants | Date/int and decimal/string remain distinct. Decimal conservatively charges 41 work/payload before fixed-array rendering; no ordinary Decimal/string export is needed. |
| ownership | Borrows input, uses bounded local text, sink owns copied bytes. |
| failure | Unsupported/valueless kind becomes internal Failure; render/sink/budget errors propagate. |
| cost | String bytes variable; Decimal rendering bounded by its 38-digit domain plus emitted bytes. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md), [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0028

[Lines 90–90](../../../../../src/planner/selection_binding.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Scalar> void sql_value(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve SQL NULL as optional scalar absence. |
| inputs / outputs | Presence frame and exact scalar if present. |
| invariants | NULL is not a native Value alternative or false/zero. |
| ownership | Borrows optional value. |
| failure | Nested scalar/sink errors propagate. |
| cost | Presence bytes plus actual scalar payload. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md) |

## B0029

[Lines 91–94](../../../../../src/planner/selection_binding.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sql_type(const frontend::SqlType& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind SQL kind, nullability and exact decimal domain. |
| inputs / outputs | Named record, enum, Boolean and optional precision/scale. |
| invariants | Type-sensitive metadata is retained rather than inferred from values. |
| ownership | Borrows type value. |
| failure | Sink/budget failures propagate. |
| cost | Fixed metadata framing. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md) |

## B0030

[Lines 95–98](../../../../../src/planner/selection_binding.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bind_limits(const frontend::BindLimits& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain original binding producer limits in source bytes. |
| inputs / outputs | Optional work, expression and recursion limits. |
| invariants | These copied fields do not raise host replay admission caps. |
| ownership | Borrows scalar options. |
| failure | Sink/budget failure propagates. |
| cost | Fixed field framing. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md) |

## B0031

[Lines 99–101](../../../../../src/planner/selection_binding.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void normalize_limits(const frontend::NormalizeLimits& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain normalization producer work option. |
| inputs / outputs | Named record and optional work cap. |
| invariants | The bytes describe source configuration, not fresh resource authority. |
| ownership | Borrows scalar option. |
| failure | Sink failures propagate. |
| cost | Fixed framing. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md) |

## B0032

[Lines 102–103](../../../../../src/planner/selection_binding.cpp#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L103:sha256:c0d6f3db8f8ce81b276a1d25673c71bf283287a152fb40452d73efb2e44bc3e2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for catalog: Encode complete typed SQL binding source and expression program. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies catalog; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for catalog come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0033

[Lines 104–128](../../../../../src/planner/selection_binding.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Bound> void bound(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete typed SQL binding source and expression program. |
| inputs / outputs | Source/catalog/parameters/semantics/wrapper, occurrences/locations, expression variants/arguments, predicates/outputs, limits/work. |
| invariants | Field order and variant tags preserve names, offsets, ordered/repeated outputs and typed NULL; no semantic-only reduction. |
| ownership | Borrows stable ordinary/native binding; output owns bytes. |
| failure | Valueless/unsupported nested variants or budget/storage failures abort private encoding. |
| cost | Visits all model fields, text and expression arguments; no AST execution. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md) |

## B0034

[Lines 129–129](../../../../../src/planner/selection_binding.cpp#L129); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L129:sha256:0184ac99d2d862feaaf56e52c8e08652297f0d5b53dacb74c360671be90974b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for bound: Encode full parameter-specialized normalized source. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies bound; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for bound come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0035

[Lines 130–150](../../../../../src/planner/selection_binding.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Normalized> void normalized(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode full parameter-specialized normalized source. |
| inputs / outputs | Binding/parameters/constants/core CQ/adapters/routes/outputs/limits/work/schema version. |
| invariants | Equal core semantics cannot replace distinct source predicates, adapters or output contracts. |
| ownership | Borrows immutable ordinary/native views. |
| failure | Nested visitor/budget/storage failures propagate. |
| cost | Full source/program traversal and payload bytes. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md), [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0036

[Lines 151–151](../../../../../src/planner/selection_binding.cpp#L151); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L151-L151:sha256:cbfe83f50c95a7b158de1fd194a7d572bf9a293d1c701ef6ed116ec761079e97
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for u: Encode complete supplied tree representation and claims. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies u; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for u come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0037

[Lines 152–162](../../../../../src/planner/selection_binding.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Tree> void tree(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete supplied tree representation and claims. |
| inputs / outputs | Root, ordered nodes/IDs/kinds/scopes/children/occurrences/separators, connex/height claims. |
| invariants | This is raw tree identity, distinct from child-order canonical structural key and independent of validity authority. |
| ownership | Borrows tree; owns bytes. |
| failure | Caller authority checks occur elsewhere; encoding failures publish nothing. |
| cost | All node/scope/edge/claim/text bytes. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md) |

## B0038

[Lines 163–164](../../../../../src/planner/selection_binding.cpp#L163); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L163-L164:sha256:40e262cb13b18c7ea03aa2d5f2a98de8126afbb7c964a63780de4bd39c94c0bb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for text: Bind complete physical policy, finite producer limits and optional indexed backend. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies text; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for text come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0039

[Lines 165–178](../../../../../src/planner/selection_binding.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Options> void options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind complete physical policy, finite producer limits and optional indexed backend. |
| inputs / outputs | Four policy strings, lower/identity limits and exact indexed profile/cap/work suffix. |
| invariants | Absent indexed configuration preserves original reference bytes; unsupported configuration is not enabled by encoding. |
| ownership | Borrows options. |
| failure | Sink/budget failure propagates. |
| cost | Policy byte lengths plus fixed backend/configuration fields. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0040

[Lines 179–186](../../../../../src/planner/selection_binding.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source(const C& c, const Q& q, const Physical& physical,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame exact core, physical catalog, normalized program and options as one source. |
| inputs / outputs | physical-source record with nested model/catalog/program/options. |
| invariants | Source excludes current tree; compiled artifact comparison separately includes chosen raw tree. |
| ownership | Borrows all source fields synchronously. |
| failure | Nested errors propagate. |
| cost | Full source encoding, not a hash shortcut. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0041

[Lines 187–197](../../../../../src/planner/selection_binding.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L187-L197:sha256:66eb2503dd7a43e26d5120444daf7422931901a5008860335797fde2a99c6621
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind optional compiled-input execution policy and its receiving preparation limits into deterministic plan-source and artifact-cache bytes. |
| inputs / outputs | Encode the complete physical source/options record; when the plan is a prepared CompiledProgram, append R(input-execution-v1), its versioned execution key, and U work/instruction limits. |
| invariants | The suffix follows PhysicalOptions and appears only when input_preparation_limits() is present. PhysicalPlan and interpreted CompiledProgram keep their prior bytes. Observed preparation usage, base-copy work and physical/source hashes are not changed. |
| ownership | Reads borrowed immutable plan/source handles and writes to the Encoder-selected ordinary or account-backed byte buffer; it transfers no plan or cache ownership. |
| failure | Budget admission can reject framing/key bytes before buffer growth; a failed source binding cannot publish a selection or cache artifact. |
| cost | Walks the existing source/options fields. The prepared branch adds fixed record/scalar framing and the execution-key bytes without walking normalized source a second time. |
| Design | [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [tests/unit/input_specialization_cache_test.cpp](../../../../../tests/unit/input_specialization_cache_test.cpp) |

## B0042

[Lines 198–199](../../../../../src/planner/selection_binding.cpp#L198); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L198-L199:sha256:a1ce646dd7fa946aa25344d6e7974ab87f3719d8fc3954ff7fb2d6fc03fe6a16
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for std: Derive expected direct or basis source from the admitted snapshot. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies std; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for std come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0043

[Lines 200–207](../../../../../src/planner/selection_binding.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class SourceValue> void source(const CandidateSnapshot& snapshot,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive expected direct or basis source from the admitted snapshot. |
| inputs / outputs | Direct captures original proof catalog/query and no normalized program; basis visits its actual plan. |
| invariants | Never substitutes a prefix or merely semantically equivalent model for original binding. |
| ownership | Temporary binding handle retains model through encoding. |
| failure | Invalid variant/plan or nested failures propagate. |
| cost | Exact source traversal with shared binding lifetime. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0044

[Lines 208–211](../../../../../src/planner/selection_binding.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void context(const CandidateContext& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind candidate update/arithmetic/planner/optimization/cost/canonicalization context. |
| inputs / outputs | Enum plus five namespace strings. |
| invariants | Namespace labels are identity inputs, not new implementation capability. |
| ownership | Borrows context. |
| failure | Sink/budget failure propagates. |
| cost | All namespace bytes plus fixed tag. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0045

[Lines 212–217](../../../../../src/planner/selection_binding.cpp#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void limits(const rank::Limits& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame all finite aggregate request/capture processing caps. |
| inputs / outputs | Eight additive dimensions, candidates, score bits and optional signed time. |
| invariants | Caps remain exact key inputs; retention caps/cache-use mode are separate observations. |
| ownership | Borrows value options. |
| failure | No validation here; admitted callers supply coherent values. |
| cost | Fixed fields plus optional duration frame. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0046

[Lines 218–241](../../../../../src/planner/selection_binding.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class RequestValue> void request(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame complete admitted selection request and constraint. |
| inputs / outputs | Frame original policies/constraint/aggregate limits. If update_patterns exists, append update-pattern-admissibility;1, source SHA-256/table count and every canonical table/insertion_only/fifo_scope field. |
| invariants | Absent declaration emits exactly the original request bytes. Distinct raw scope IDs cannot alias merely because analyses agree. Existing allocator-byte refusal remains. |
| ownership | Borrow the caller/captured request and its immutable declaration during encoding; the result byte buffer belongs to the receiving encoder account. |
| failure | Internal require/budget/storage failures propagate. |
| cost | Original cap/framing work plus 64 digest bytes and O(R) rule framing only when requested; no report or row serialization. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0047

[Lines 242–242](../../../../../src/planner/selection_binding.cpp#L242); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L242-L242:sha256:c9465edea44bb5e96f9be5fba1d9534ac252b1d69b56dbee50b89f3ad0436540
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for evidence: Bind exact as-of ranking facts and capture configuration. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies evidence; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for evidence come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0048

[Lines 243–260](../../../../../src/planner/selection_binding.cpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void evidence(const rank::Evidence& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind exact as-of ranking facts and capture configuration. |
| inputs / outputs | Identity/modes/boundaries, weights, sources/observations, policy reasons/denominator and capture options. |
| invariants | Excludes preparation usage, actual consumption and elapsed diagnostics; fresh assessment/source checks still occur independently. |
| ownership | Borrows immutable evidence/account-backed vectors. |
| failure | Sink/budget errors abort token. |
| cost | Complete fact-vector/text-free scalar traversal; sizes can scale with sources. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0049

[Lines 261–264](../../../../../src/planner/selection_binding.cpp#L261); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L261-L264:sha256:bd0989baf58ebc637d2fb2b075132ab6b0043447fbfb9cedb695c009dd5f4d72
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the Encoder class and anonymous namespace, then attach the note introducing source_binding() for original-core and complete-source agreement. |
| inputs / outputs | The close delimiters and note have no runtime inputs or outputs. source_binding() receives snapshot, source, optional evidence, and the active Budget in the following block. |
| invariants | This is a lexical boundary plus navigation note. The note does not perform binding checks; source_binding() and its callers provide those checks. |
| ownership | The delimiters and comment own no storage. The following function borrows its arguments for the call. |
| failure | A misplaced class/namespace delimiter fails compilation. The comment adds no runtime failure; function failures arise from source_binding() and its callers. |
| cost | Compile-time scope parsing only; the following source_binding() performs byte encoding/comparison and budgeted work. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0050

[Lines 265–281](../../../../../src/planner/selection_binding.cpp#L265); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void source_binding(const CandidateSnapshot& snapshot,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check original core binding and full source agreement before scoring/publication. |
| inputs / outputs | Basis core bytes must equal original proof model; expected full source is encoded and compared with evidence source when present. |
| invariants | Exact framed bytes, not semantic/digest equality. No evidence means no current-owner freshness assertion. |
| ownership | Owns temporary native strings under receiving account; borrows typed input owners. |
| failure | Mismatch throws binding_mismatch; all charge/allocation failures remain precommit. |
| cost | Full model/source encodings and byte comparisons, including normalized programs/options. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0051

[Lines 282–283](../../../../../src/planner/selection_binding.cpp#L282); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L282-L283:sha256:28857eb0098394bf18072595c06c8d63f3ae5d3f22192a09e32888b6094aa39c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for compiled_binding: Verify chosen compiled source and operator tree against the admitted candidate. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies compiled_binding; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for compiled_binding come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0052

[Lines 284–296](../../../../../src/planner/selection_binding.cpp#L284); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compiled_binding(const CandidateSnapshot& snapshot,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the full compiled source and the executable geometry derived from the admitted chosen candidate. |
| inputs / outputs | Encode expected PhysicalSource from snapshot/source plus the candidate-derived operator tree, then encode the actual program source/tree and compare every framed byte. A nonempty contradiction expects the canonical empty operator tree; every other input expects the candidate raw tree unchanged. |
| invariants | The predicate reads the admitted candidate query, never an untrusted route label. The original positive-height candidate/proof and its raw tree stay in the retained family and cache key. Source options/normalized program/backend remain in the full equality gate; matching digests or a cache hit cannot bypass it. |
| ownership | Both possible expected trees are lvalues selected through a const reference, so ordinary geometry is borrowed without a deep copy. Two private buffers use the receiving account and do not retain borrowed views. |
| failure | Any source/geometry mismatch becomes binding_mismatch; resource or allocation failure aborts before cache publication. The helper adds no local recovery or exception translation. |
| cost | Two complete source/tree encodings plus the examined comparison bytes and account-backed buffer growth. Constant geometry avoids traversing the original body tree here, but source encoding remains proportional to source metadata; no constant-time equality claim. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0053

[Lines 297–298](../../../../../src/planner/selection_binding.cpp#L297); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L297-L298:sha256:be70f05619eee78b2bc6a194f58254ba13619b1d71dec487d81db95400cc39e4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for cache_binding: Build the complete retained artifact-reuse key after fresh decision. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies cache_binding; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for cache_binding come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0054

[Lines 299–323](../../../../../src/planner/selection_binding.cpp#L299); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SelectionText cache_binding(const SelectionData& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the complete retained artifact-reuse key after fresh decision. |
| inputs / outputs | Implementation domains, original model/height/context/family/order, full candidate keys/trees, source/options/request, chosen/eligibility and evidence/origin. |
| invariants | Excludes proof bytes/provenance, measured usage, cache mode/caps and transient current-owner diagnostics; typed proof/fresh assessments/binding gates remain mandatory. |
| ownership | Returns account-backed capture text; borrows immutable prepared Data. |
| failure | Final sample and all encoded charges can fail before lookup/commit. |
| cost | Full retained family/source/evidence bytes and repeated framing; actual string capacity is account-backed. |
| Design | [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md), [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0055

[Lines 324–324](../../../../../src/planner/selection_binding.cpp#L324); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L324-L324:sha256:4953715d6414ef98ec04506cd54ed61004525313ada4e36358060e15f0ef801c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for scalar_binding_record: Export diagnostic bytes for one exact Value. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies scalar_binding_record; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for scalar_binding_record come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0056

[Lines 325–327](../../../../../src/planner/selection_binding.cpp#L325); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string scalar_binding_record(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export diagnostic bytes for one exact Value. |
| inputs / outputs | Ordinary Encoder uses CROWN-SELECTION-SCALAR;1; then matching visitor. |
| invariants | Bytes cannot construct a Selection, import proof or insert into cache. |
| ownership | Returned std::string owns bytes; all input/budget borrows end. |
| failure | Encoding/variant/length/allocation failure returns no partial record; accepted diagnostics may remain. |
| cost | Full payload encoding and ordinary output growth outside native result retention. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0057

[Lines 328–330](../../../../../src/planner/selection_binding.cpp#L328); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string tree_binding_record(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export diagnostic bytes for one complete raw tree. |
| inputs / outputs | Ordinary Encoder uses CROWN-SELECTION-TREE;1; then matching visitor. |
| invariants | Bytes cannot construct a Selection, import proof or insert into cache. |
| ownership | Returned std::string owns bytes; all input/budget borrows end. |
| failure | Encoding/variant/length/allocation failure returns no partial record; accepted diagnostics may remain. |
| cost | Full payload encoding and ordinary output growth outside native result retention. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0058

[Lines 331–333](../../../../../src/planner/selection_binding.cpp#L331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string program_binding_record(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export diagnostic bytes for one full normalized SQL program. |
| inputs / outputs | Ordinary Encoder uses CROWN-SELECTION-PROGRAM;1; then matching visitor. |
| invariants | Bytes cannot construct a Selection, import proof or insert into cache. |
| ownership | Returned std::string owns bytes; all input/budget borrows end. |
| failure | Encoding/variant/length/allocation failure returns no partial record; accepted diagnostics may remain. |
| cost | Full payload encoding and ordinary output growth outside native result retention. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0059

[Lines 334–336](../../../../../src/planner/selection_binding.cpp#L334); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string core_binding_record(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export diagnostic bytes for one exact Catalog/Query. |
| inputs / outputs | Ordinary Encoder uses CROWN-SELECTION-CORE;1; then matching visitor. |
| invariants | Bytes cannot construct a Selection, import proof or insert into cache. |
| ownership | Returned std::string owns bytes; all input/budget borrows end. |
| failure | Encoding/variant/length/allocation failure returns no partial record; accepted diagnostics may remain. |
| cost | Full payload encoding and ordinary output growth outside native result retention. |
| Design | [docs/selection_binding.md §Diagnostic entry domains and exact records](../../../../selection_binding.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0060

[Lines 337–337](../../../../../src/planner/selection_binding.cpp#L337); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L337-L337:sha256:41848aefb30bbb259c959e13f974e1f553bad9051ef8e1ee6f1df63b5ac2ac7c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::selection::detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/selection_binding.cpp](../../../../../src/planner/selection_binding.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |
