# `src/storage/accounted_row.cpp` — block usage map

[Source](../../../../../src/storage/accounted_row.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries.

Snapshot SHA-256: `ca983a56289b0d85596a7d2f1c48e2ba42592b875485c3ac4ea4555d99d6a01c`. 270 lines partitioned into 42 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../scalars.md), [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../src/storage/accounted_row.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_trivially_destructible_v&lt;ScalarView&gt;); · [reviewed contract](#b0001) |
| [B0002 · 21–25](../../../../../src/storage/accounted_row.cpp#L21) | Callable definition: std::size_t checked_add(std::size_t left, std::size_t right) | calls max, MemoryFailure; returns left + right · [reviewed contract](#b0002) |
| [B0003 · 26–33](../../../../../src/storage/accounted_row.cpp#L26) | Callable definition: ScalarView borrow(const Value& value) | calls std::string_view, InlineDecimal::copy_of, MemoryFailure; returns *cell; std::string_view(*cell); growth copy_of · [reviewed contract](#b0003) |
| [B0004 · 34–42](../../../../../src/storage/accounted_row.cpp#L34) | Callable definition: template&lt;class Read&gt; std::size_t cell_payload_bytes(std::size_t size,Read read) | calls max, MemoryFailure, read, checked_add; returns bytes; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 43–66](../../../../../src/storage/accounted_row.cpp#L43) | Callable definition: template&lt;class Read&gt; resource::MemoryBlock copy_cells(const resource::MemoryAccount& account, resource::MemoryAttribution attribu… | calls cell_payload_bytes, allocate, data, read; returns block; growth allocate; 1 loop sites; source comment (unverified): // One preflight calculation is shared with exact native queue admission. · [reviewed contract](#b0005) |
| [B0006 · 67–68](../../../../../src/storage/accounted_row.cpp#L67) | declares types or opens a type body. |  · [reviewed contract](#b0006) |
| [B0007 · 69–70](../../../../../src/storage/accounted_row.cpp#L69) | Callable definition: public: void byte(std::uint8_t value) noexcept | calls  · [reviewed contract](#b0007) |
| [B0008 · 71–73](../../../../../src/storage/accounted_row.cpp#L71) | Callable definition: void integer(std::uint64_t value) noexcept | calls byte; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 74–77](../../../../../src/storage/accounted_row.cpp#L74) | Callable definition: void text(std::string_view value) noexcept | calls integer, size, byte; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 78–89](../../../../../src/storage/accounted_row.cpp#L78) | Callable definition: void value(const ScalarView& cell) noexcept | calls byte, index, integer, text; source comment (unverified): // No alternative can become valueless by throwing a move/copy. · [reviewed contract](#b0010) |
| [B0011 · 90–90](../../../../../src/storage/accounted_row.cpp#L90) | Callable definition: \[\[nodiscard\]\] std::uint64_t get() const noexcept | calls ; returns hash_ · [reviewed contract](#b0011) |
| [B0012 · 91–95](../../../../../src/storage/accounted_row.cpp#L91) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 96–120](../../../../../src/storage/accounted_row.cpp#L96) | Callable definition: InlineDecimal InlineDecimal::parse(std::string_view text) | calls empty, Error, find, size; returns InlineDecimal{}; result; 3 loop sites · [reviewed contract](#b0013) |
| [B0014 · 121–129](../../../../../src/storage/accounted_row.cpp#L121) | Callable definition: InlineDecimal InlineDecimal::copy_of(const Decimal& value) noexcept | calls parts, size, std::copy, begin; returns result; growth copy_of · [reviewed contract](#b0014) |
| [B0015 · 130–152](../../../../../src/storage/accounted_row.cpp#L130) | Callable definition: std::size_t InlineDecimal::render(std::span&lt;char&gt; output) const | calls parts, size, std::max, MemoryFailure; returns position; 4 loop sites · [reviewed contract](#b0015) |
| [B0016 · 153–156](../../../../../src/storage/accounted_row.cpp#L153) | Callable definition: bool InlineDecimal::operator==(const InlineDecimal& other) const noexcept | calls ; returns left.digits == right.digits && left.scale == right.scale && left.negative == right.negative · [reviewed contract](#b0016) |
| [B0017 · 157–178](../../../../../src/storage/accounted_row.cpp#L157) | Callable definition: std::strong_ordering InlineDecimal::operator&lt;=&gt;(const InlineDecimal& other) const noexcept | calls size, std::max; returns std::strong_ordering::equal; right.negative ? std::strong_ordering::greater : std::strong_ordering:…; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 179–179](../../../../../src/storage/accounted_row.cpp#L179) | Explanatory comments or spacing. |  |
| [B0019 · 180–183](../../../../../src/storage/accounted_row.cpp#L180) | Callable definition: const ScalarView& RowView::at(std::size_t index) const | calls MemoryFailure; returns data_\[index\] · [reviewed contract](#b0019) |
| [B0020 · 184–189](../../../../../src/storage/accounted_row.cpp#L184) | Callable definition: std::uint64_t RowView::hash() const noexcept | calls integer, cells, value, get; returns hasher.get(); 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 190–192](../../../../../src/storage/accounted_row.cpp#L190) | Callable definition: bool RowView::operator==(RowView other) const noexcept | returns size_ == other.size_ && (*this &lt;=&gt; other) == 0 · [reviewed contract](#b0021) |
| [B0022 · 193–199](../../../../../src/storage/accounted_row.cpp#L193) | Callable definition: std::strong_ordering RowView::operator&lt;=&gt;(RowView other) const noexcept | calls ; returns order; size_ &lt;=&gt; other.size_; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 200–200](../../../../../src/storage/accounted_row.cpp#L200) | Explanatory comments or spacing. |  |
| [B0024 · 201–201](../../../../../src/storage/accounted_row.cpp#L201) | Callable definition: ScalarView borrow_scalar(const Value& value) | calls borrow; returns borrow(value) · [reviewed contract](#b0024) |
| [B0025 · 202–205](../../../../../src/storage/accounted_row.cpp#L202) | Callable definition: ScalarType type_of(const ScalarView& value) | calls valueless_by_exception, resource::MemoryFailure, index; returns static_cast&lt;ScalarType&gt;(value.index()) · [reviewed contract](#b0025) |
| [B0026 · 206–206](../../../../../src/storage/accounted_row.cpp#L206) | Callable definition: bool operator==(const ScalarView& left,const Value& right) | calls ; returns left==borrow(right) · [reviewed contract](#b0026) |
| [B0027 · 207–207](../../../../../src/storage/accounted_row.cpp#L207) | Callable definition: std::strong_ordering operator&lt;=&gt;(const ScalarView& left,const Value& right) | calls ; returns left&lt;=&gt;borrow(right) · [reviewed contract](#b0027) |
| [B0028 · 208–213](../../../../../src/storage/accounted_row.cpp#L208) | Callable definition: std::strong_ordering operator&lt;=&gt;(RowView left,const Row& right) | calls size, borrow; returns order; left.size()&lt;=&gt;right.size(); 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 214–214](../../../../../src/storage/accounted_row.cpp#L214) | Callable definition: bool operator==(RowView left,const Row& right) | calls ; returns left.size()==right.size() && (left&lt;=&gt;right)==0 · [reviewed contract](#b0029) |
| [B0030 · 215–224](../../../../../src/storage/accounted_row.cpp#L215) | Callable definition: Value export_scalar(const ScalarView& value) | calls std::visit, constexpr, std::string, render; returns std::visit(\[\](const auto& cell)-&gt;Value {; std::string(cell) · [reviewed contract](#b0030) |
| [B0031 · 225–229](../../../../../src/storage/accounted_row.cpp#L225) | Callable definition: Row export_row(RowView values) | calls reserve, size, cells, push_back; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0031) |
| [B0032 · 230–230](../../../../../src/storage/accounted_row.cpp#L230) | Explanatory comments or spacing. |  |
| [B0033 · 231–232](../../../../../src/storage/accounted_row.cpp#L231) | Callable definition: AccountedRow::AccountedRow(AccountedRow&& other) noexcept : block_(std::move(other.block_)), size_(std::exchange(other.size_, 0)) | calls block_, std::move, size_, std::exchange · [reviewed contract](#b0033) |
| [B0034 · 233–236](../../../../../src/storage/accounted_row.cpp#L233) | Callable definition: AccountedRow& AccountedRow::operator=(AccountedRow&& other) noexcept | calls std::exchange; returns *this · [reviewed contract](#b0034) |
| [B0035 · 237–240](../../../../../src/storage/accounted_row.cpp#L237) | Callable definition: AccountedRow AccountedRow::copy_of(const resource::MemoryAccount& account, const Row& values, resource::MemoryAttribution attribu… | calls AccountedRow, copy_cells, size, borrow; returns AccountedRow(copy_cells(account, attribution, values.size(), \[&\](std::size_t i) { return borrow(val…; growth copy_of · [reviewed contract](#b0035) |
| [B0036 · 241–244](../../../../../src/storage/accounted_row.cpp#L241) | Callable definition: AccountedRow AccountedRow::copy_of(const resource::MemoryAccount& account, RowView values, resource::MemoryAttribution attributio… | calls AccountedRow, copy_cells, size; returns AccountedRow(copy_cells(account, attribution, values.size(), \[&\](std::size_t i) { return values\[i\]; growth copy_of · [reviewed contract](#b0036) |
| [B0037 · 245–248](../../../../../src/storage/accounted_row.cpp#L245) | Callable definition: resource::MemoryUsage AccountedRow::allocation_usage_for(const Row& values) | calls cell_payload_bytes, size, borrow, resource::MemoryAccount::allocation_bytes; returns borrow(values\[i\]); {1,resource::MemoryAccount::allocation_bytes(bytes,alignof(ScalarView)),bytes} · [reviewed contract](#b0037) |
| [B0038 · 249–252](../../../../../src/storage/accounted_row.cpp#L249) | Callable definition: resource::MemoryUsage AccountedRow::allocation_usage_for(TupleValuesView values) | calls cell_payload_bytes, size, resource::MemoryAccount::allocation_bytes; returns values\[i\]; {1,resource::MemoryAccount::allocation_bytes(bytes,alignof(ScalarView)),bytes} · [reviewed contract](#b0038) |
| [B0039 · 253–256](../../../../../src/storage/accounted_row.cpp#L253) | Callable definition: AccountedRow AccountedRow::copy_view(const resource::MemoryAccount& account,TupleValuesView values, resource::MemoryAttribution a… | calls AccountedRow, copy_cells, size; returns AccountedRow(copy_cells(account,attribution,values.size(),\[&\](std::size_t i){return values\[i\] · [reviewed contract](#b0039) |
| [B0040 · 257–265](../../../../../src/storage/accounted_row.cpp#L257) | Callable definition: AccountedRow AccountedRow::project(const resource::MemoryAccount& account, RowView values, std::span&lt;const FieldId&gt; fields, resou… | calls size, MemoryFailure, AccountedRow, copy_cells; returns AccountedRow(copy_cells(account, attribution, fields.size(),; values\[fields\[i\].value\]; 1 loop sites; source comment (unverified): // Gather directly into one admitted descriptor/payload block. There is no · [reviewed contract](#b0040) |
| [B0041 · 266–268](../../../../../src/storage/accounted_row.cpp#L266) | Callable definition: RowView AccountedRow::view() const & noexcept | calls RowView, data; returns RowView(static_cast&lt;const ScalarView*&gt;(block_.data()), size_) · [reviewed contract](#b0041) |
| [B0042 · 269–270](../../../../../src/storage/accounted_row.cpp#L269) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0042) |

## B0001

[Lines 1–20](../../../../../src/storage/accounted_row.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:8d36dedbc6bc3a3c6db484e8c05af8cafd87c2bf15345050c5082001cd1ad838
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_row.cpp: imports \`"crown/storage/accounted_row.hpp"\`, \`"crown/storage/tuple_values.hpp"\`, \`"crown/api/error.hpp"\`, \`&lt;algorithm&gt;\`, \`&lt;cstring&gt;\`, \`&lt;exception&gt;\`, \`&lt;limits&gt;\`, \`&lt;memory&gt;\`, \`&lt;type_traits&gt;\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::storage\`; opens anonymous namespace with translation-unit-local linkage; imports or aliases \`resource::MemoryFailure\`, \`resource::MemoryFault\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Span/view members borrow their source; retain the source owner for the full use window. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 21–25](../../../../../src/storage/accounted_row.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t checked_add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check native payload-size addition before framing/allocation. |
| inputs / outputs | Two size_t lengths return their sum if representable. |
| invariants | Reject wrap before any block allocation/copy. |
| ownership | Inline arithmetic only. |
| failure | Raises MemoryFailure(overflow) before the addition. |
| cost | O(1). |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0003

[Lines 26–33](../../../../../src/storage/accounted_row.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarView borrow(const Value& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt a legacy scalar to the compact native alternative. |
| inputs / outputs | Integer/bool/date copy inline, string becomes string_view and Decimal becomes bounded InlineDecimal. |
| invariants | Alternative order agrees with Value/ScalarType; canonical Decimal invariant is preserved. |
| ownership | String bytes borrow the Value; other returned alternatives own inline bits. |
| failure | Valueless/unsupported Value raises MemoryFailure(contract); success allocates nothing. |
| cost | Fixed variant dispatch plus &lt;=38 decimal digit copy; no formatting or owning Row. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0004

[Lines 34–42](../../../../../src/storage/accounted_row.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Read> std::size_t cell_payload_bytes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight exact descriptor-and-string payload size. |
| inputs / outputs | Stable cell reader/arity return descriptor bytes plus each string length, including repeated selections. |
| invariants | Check multiplication and every string-size addition; terminators and framing are not logical payload bytes. |
| ownership | Reads borrowed cells without retaining a row or allocating scratch. |
| failure | Size overflow or invalid reader value rejects before native allocation. |
| cost | O(cell count), including bounded scalar adaptation; no traversal of string contents is needed for sizing. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0005

[Lines 43–66](../../../../../src/storage/accounted_row.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryBlock copy_cells(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy stable borrowed cells into one native block. |
| inputs / outputs | Account/attribution/reader produce one block with ScalarView descriptors followed by owned exact string bytes. |
| invariants | Reader/cells/string lengths stay stable through preflight and copying. After admission ScalarView construction is nonthrowing/trivially destructible; no nested strings or second payload allocation. |
| ownership | Original account owns descriptor array, deep bytes and framing, including a real framed request for zero cells. |
| failure | Preflight/funding failure publishes no row; RAII releases any admitted block on unwinding. |
| cost | Two reads per cell plus actual copied string bytes, one native allocation; not a full legacy Row mirror. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0006

[Lines 67–68](../../../../../src/storage/accounted_row.cpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L68:sha256:fc44931cd702d1e87754c8838a964793079dd0c4da212c76575f3bb8b7696123
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_row.cpp: defines/starts \`class Hasher\` in this range. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0007

[Lines 69–70](../../../../../src/storage/accounted_row.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void byte(std::uint8_t value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mix one byte into native FNV-1a state. |
| inputs / outputs | Byte updates the uint64 accumulator. |
| invariants | Unsigned wrap is the defined FNV mixing operation. |
| ownership | Hasher owns only its inline accumulator; scalar/string inputs are borrowed. |
| failure | Noexcept for valid scalar alternatives; a valueless native hash input violates the invariant and terminates. |
| cost | One xor and multiply. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0008

[Lines 71–73](../../../../../src/storage/accounted_row.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void integer(std::uint64_t value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one fixed-width integer for stable hashing. |
| inputs / outputs | Unsigned integer feeds eight little-endian bytes. |
| invariants | Encoding does not depend on host byte order. |
| ownership | Hasher owns only its inline accumulator; scalar/string inputs are borrowed. |
| failure | Noexcept for valid scalar alternatives; a valueless native hash input violates the invariant and terminates. |
| cost | Exactly eight byte mixes. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0009

[Lines 74–77](../../../../../src/storage/accounted_row.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void text(std::string_view value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash exact string bytes with an explicit length prefix. |
| inputs / outputs | Borrowed string feeds eight-byte length then every byte. |
| invariants | Embedded NUL and signed char do not truncate or change byte identity. |
| ownership | Hasher owns only its inline accumulator; scalar/string inputs are borrowed. |
| failure | Noexcept for valid scalar alternatives; a valueless native hash input violates the invariant and terminates. |
| cost | O(string bytes), no copy. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0010

[Lines 78–89](../../../../../src/storage/accounted_row.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void value(const ScalarView& cell) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash a typed compact scalar in public-compatible canonical form. |
| inputs / outputs | Variant tag plus integer/string/bool/date or rendered decimal feed the accumulator. |
| invariants | Canonical decimal rendering uses fixed41-byte stack scratch; valid alternatives cannot fail rendering. Type tags keep different scalar kinds distinct. |
| ownership | Hasher owns only its inline accumulator; scalar/string inputs are borrowed. |
| failure | Noexcept for valid scalar alternatives; a valueless native hash input violates the invariant and terminates. |
| cost | Actual string bytes or bounded&lt;=41 decimal text bytes; no heap allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0011

[Lines 90–90](../../../../../src/storage/accounted_row.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::uint64_t get() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the current FNV accumulator. |
| inputs / outputs | Returns one uint64 hash scalar. |
| invariants | No final semantic identity or collision proof is implied. |
| ownership | Hasher owns only its inline accumulator; scalar/string inputs are borrowed. |
| failure | Noexcept for valid scalar alternatives; a valueless native hash input violates the invariant and terminates. |
| cost | O(1). |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0012

[Lines 91–95](../../../../../src/storage/accounted_row.cpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L95:sha256:fdbfdb13ad9f76990d3570f0fee81118db474df857d8a23cc4855872ece51f4d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_row.cpp: closes \`class Hasher\`, \`anonymous namespace\`. |
| inputs / outputs | This span stores or passes the listed fields \`hash_\`; constructor/function parameters and any outputs are exactly those declared here. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0013

[Lines 96–120](../../../../../src/storage/accounted_row.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InlineDecimal InlineDecimal::parse(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse the exact decimal scalar directly into inline coefficient storage. |
| inputs / outputs | Borrowed sign/digits/optional point produce canonical inline sign/scale/coefficient. |
| invariants | Same scalar grammar/canonical zero/&lt;=38digit and scale&lt;=38 rules as Decimal::parse; no floating conversion. |
| ownership | Returned38-byte coefficient array is independent of input; no success-path standard string. |
| failure | Malformed/overflow input uses owning public Error diagnostics; no partial inline result escapes. |
| cost | O(input bytes) scans with fixed inline storage; success allocates nothing. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0014

[Lines 121–129](../../../../../src/storage/accounted_row.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InlineDecimal InlineDecimal::copy_of(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the canonical public decimal into bounded native bytes. |
| inputs / outputs | Valid Decimal parts become inline digits_size/scale/sign and coefficient characters. |
| invariants | Source Decimal canonical bounds prove uint8 sizes and38-byte destination capacity. |
| ownership | Borrows source parts only during copying; output owns inline coefficient. |
| failure | Noexcept under the Decimal invariant; no fallback parser or allocation. |
| cost | At most38 character copies. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0015

[Lines 130–152](../../../../../src/storage/accounted_row.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t InlineDecimal::render(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render canonical decimal text into caller-provided scratch. |
| inputs / outputs | Mutable char span receives exact bytes without NUL; returns written count. |
| invariants | Compute complete required size and reject insufficient capacity before any write. text_capacity41 always suffices for admitted values. |
| ownership | Caller owns scratch; source is borrowed and no string is allocated. |
| failure | Too-small span raises MemoryFailure(contract) before writes; valid fixed41-byte callers cannot hit it. |
| cost | At most41 writes and fixed arithmetic. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0016

[Lines 153–156](../../../../../src/storage/accounted_row.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool InlineDecimal::operator==(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare canonical inline decimal identity. |
| inputs / outputs | Two valid inline values compare coefficient, scale and sign. |
| invariants | Canonical form makes representation equality equal numeric equality; unused array tail is irrelevant. |
| ownership | Borrowed parts only. |
| failure | Noexcept, no allocation. |
| cost | At most38 coefficient-byte comparisons plus two scalars. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0017

[Lines 157–178](../../../../../src/storage/accounted_row.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::strong_ordering InlineDecimal::operator<=>(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order inline decimals by exact signed numeric magnitude. |
| inputs / outputs | Canonical values return strong ordering. |
| invariants | Zero/sign/exponent and zero-padded digits reproduce public Decimal ordering; negative magnitude order reverses. |
| ownership | Borrows fixed inline arrays, no formatting scratch or heap owner. |
| failure | Noexcept under canonical bounds. |
| cost | At most38 digit comparisons plus fixed sign/exponent work. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0019

[Lines 180–183](../../../../../src/storage/accounted_row.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ScalarView& RowView::at(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a native cell with an explicit bounds check. |
| inputs / outputs | Index within size returns const reference to that descriptor. |
| invariants | Descriptor/string storage remains valid for the borrowed RowView lifetime. |
| ownership | Reference borrows caller/native row; no ownership retention. |
| failure | Out-of-range raises MemoryFailure(contract), not std::out_of_range. |
| cost | O(1), allocation-free success. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0020

[Lines 184–189](../../../../../src/storage/accounted_row.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t RowView::hash()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash the complete typed compact row with arity framing. |
| inputs / outputs | Valid descriptors produce one stable uint64 FNV hash. |
| invariants | Prefix cell count; encode type tags and canonical values exactly like legacy row_hash. Equal rows hash equally; collisions still require equality. |
| ownership | Borrows cells/string bytes and owns only stack accumulator/scratch. |
| failure | Noexcept for valid descriptors; valueless scalar invariant violations terminate. |
| cost | O(cells + string bytes + bounded decimal rendering); no heap allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0021

[Lines 190–192](../../../../../src/storage/accounted_row.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool RowView::operator==(RowView other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test native-row value equality with arity rejection first. |
| inputs / outputs | Different sizes return false immediately; equal-size rows compare typed scalar values. |
| invariants | Type-sensitive equality agrees with native hash canonicalization. |
| ownership | Both views borrow their source cells/strings. |
| failure | Noexcept for valid native scalar alternatives. |
| cost | O(1) for different arities; otherwise stops at first unequal cell/deep string comparison. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0022

[Lines 193–199](../../../../../src/storage/accounted_row.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::strong_ordering RowView::operator<=>(RowView other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lexicographically order compact typed rows. |
| inputs / outputs | Compare common prefix, then arity when prefix equal. |
| invariants | Variant tags participate in cross-type order; each same-type decimal order is exact numeric order. |
| ownership | Views borrow both inputs; result is one inline ordering value. |
| failure | Noexcept for valid cell storage/alternatives. |
| cost | O(common prefix plus compared string bytes), bounded decimal work per compared cell. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0024

[Lines 201–201](../../../../../src/storage/accounted_row.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarView borrow_scalar(const Value& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the compact borrowed scalar adapter at the public boundary. |
| inputs / outputs | Value returns ScalarView through borrow(). |
| invariants | String result borrows Value; Decimal is copied inline, not rendered. |
| ownership | No owner is created; caller retains the source for any string_view use. |
| failure | Invalid Value alternative propagates the adapter contract failure. |
| cost | Fixed dispatch and&lt;=38-digit copy; no success allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0025

[Lines 202–205](../../../../../src/storage/accounted_row.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarType type_of(const ScalarView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a compact scalar kind while rejecting valueless variants. |
| inputs / outputs | Valid alternative index converts to matching ScalarType. |
| invariants | ScalarView alternative order is deliberately synchronized with ScalarType. |
| ownership | Copies one enum, no retained state. |
| failure | Valueless input raises MemoryFailure(contract). |
| cost | O(1). |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0026

[Lines 206–206](../../../../../src/storage/accounted_row.cpp#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool operator==(const ScalarView& left,const Value& right)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare compact and legacy typed scalars without owning export. |
| inputs / outputs | Adapt right by borrow(), then compare native alternatives. |
| invariants | Preserve exact type tags, canonical decimal identity and string bytes. |
| ownership | Native view and legacy Values must stay alive/unchanged; no owning DTO is constructed. |
| failure | Invalid legacy Value can raise the adapter contract failure; valid comparisons allocate nothing. |
| cost | Fixed dispatch/&lt;=38-digit copy plus actual string equality. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0027

[Lines 207–207](../../../../../src/storage/accounted_row.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::strong_ordering operator<=>(const ScalarView& left,const Value& right)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order compact and legacy typed scalars without formatting. |
| inputs / outputs | Adapt right to compact borrowed value, then compare. |
| invariants | Preserve exact type tags, canonical decimal identity and string bytes. |
| ownership | Native view and legacy Values must stay alive/unchanged; no owning DTO is constructed. |
| failure | Invalid legacy Value can raise the adapter contract failure; valid comparisons allocate nothing. |
| cost | Fixed adaptation plus actual same-kind comparison. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0028

[Lines 208–213](../../../../../src/storage/accounted_row.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::strong_ordering operator<=>(RowView left,const Row& right)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order a native row against a legacy owning row directly. |
| inputs / outputs | Borrow each legacy cell in the common prefix, then compare arities. |
| invariants | Preserve exact type tags, canonical decimal identity and string bytes. |
| ownership | Native view and legacy Values must stay alive/unchanged; no owning DTO is constructed. |
| failure | Invalid legacy Value can raise the adapter contract failure; valid comparisons allocate nothing. |
| cost | O(compared prefix/deep string bytes), no owning Row conversion. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0029

[Lines 214–214](../../../../../src/storage/accounted_row.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool operator==(RowView left,const Row& right)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test native/legacy row equality with arity short-circuit. |
| inputs / outputs | Size mismatch returns false; otherwise use borrowed lexicographic comparison. |
| invariants | Preserve exact type tags, canonical decimal identity and string bytes. |
| ownership | Native view and legacy Values must stay alive/unchanged; no owning DTO is constructed. |
| failure | Invalid legacy Value can raise the adapter contract failure; valid comparisons allocate nothing. |
| cost | O(1) for different arities; otherwise actual prefix comparison. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0030

[Lines 215–224](../../../../../src/storage/accounted_row.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value export_scalar(const ScalarView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cross the explicit native-to-owning scalar DTO boundary. |
| inputs / outputs | String copies to std::string, InlineDecimal renders/parses to public Decimal, other alternatives copy inline. |
| invariants | Export preserves canonical exact value/type; it is not an internal borrowed probe. |
| ownership | Returned Value owns its standard strings; caller DTO allocation is outside native account retention. |
| failure | Standard allocation/public parse failure propagates without changing source. |
| cost | Actual copied string bytes or bounded decimal render/parse; export can allocate. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0031

[Lines 225–229](../../../../../src/storage/accounted_row.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row export_row(RowView values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a complete ordinary owning Row for external/tool use. |
| inputs / outputs | Reserve arity then export every compact scalar. |
| invariants | Result has no borrowed strings; row order/type identity are preserved. |
| ownership | Standard vector/string DTO storage is explicit, separate from accounted native row storage. |
| failure | Allocation failure destroys partial DTO; source remains unchanged. |
| cost | O(cells + copied strings + bounded decimal conversions); not a zero-copy adapter. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0033

[Lines 231–232](../../../../../src/storage/accounted_row.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedRow::AccountedRow(AccountedRow&& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer compact payload ownership without recopying descriptors or bytes. |
| inputs / outputs | Moves MemoryBlock and exchanges source size to zero. |
| invariants | Moved source is empty and owns no block; previously borrowed views still require transferred owner to survive. |
| ownership | Exactly one destination owns the original block/account charge. |
| failure | Noexcept. |
| cost | O(1), no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0034

[Lines 233–236](../../../../../src/storage/accounted_row.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedRow& AccountedRow::operator=(AccountedRow&& other)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace this row by transferring another row block. |
| inputs / outputs | Self-move leaves it unchanged; other moves release old block, transfer new block and zero source size. |
| invariants | Source/destination never share mutable payload ownership; old borrowed views cease being valid when old block releases. |
| ownership | Original native MemoryBlock/account moves; no fresh grant. |
| failure | Noexcept deallocation/move. |
| cost | Fixed native ownership/counter work plus actual upstream deallocation; no descriptor/string copy or allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0035

[Lines 237–240](../../../../../src/storage/accounted_row.cpp#L237); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedRow AccountedRow::copy_of(const resource::MemoryAccount& account, const Row& values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy stable input cells into the receiving native account. |
| inputs / outputs | Account, attribution and legacy Row Values produce one owning descriptor/string block. |
| invariants | Input values/lengths stay unchanged throughout preflight/copy. Empty row still receives a framed native allocation. |
| ownership | No borrowed string survives in the result; source need not outlive the returned AccountedRow. |
| failure | Sizing/admission failure creates no row; RAII releases partially prepared storage. |
| cost | Two cell passes plus copied string bytes; one accounted payload allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0036

[Lines 241–244](../../../../../src/storage/accounted_row.cpp#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedRow AccountedRow::copy_of(const resource::MemoryAccount& account, RowView values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy stable input cells into the receiving native account. |
| inputs / outputs | Account, attribution and compact RowView cells produce one owning descriptor/string block. |
| invariants | Input values/lengths stay unchanged throughout preflight/copy. Empty row still receives a framed native allocation. |
| ownership | No borrowed string survives in the result; source need not outlive the returned AccountedRow. |
| failure | Sizing/admission failure creates no row; RAII releases partially prepared storage. |
| cost | Two cell passes plus copied string bytes; one accounted payload allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0037

[Lines 245–248](../../../../../src/storage/accounted_row.cpp#L245); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryUsage AccountedRow::allocation_usage_for(const Row& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Predict the real single-block row request without allocating it. |
| inputs / outputs | Stable legacy Row yields allocation count1, framed requested bytes and logical descriptor/string payload bytes. |
| invariants | Uses the same cell_payload_bytes routine as copy, including zero-cell framing; this does not reserve memory or a work grant. |
| ownership | Borrows input; returns three inline accounting scalars. |
| failure | Invalid scalar or size/framing overflow rejects before allocation. |
| cost | O(cells) size scan with bounded adaptation, no string byte copy or scratch allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0038

[Lines 249–252](../../../../../src/storage/accounted_row.cpp#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryUsage AccountedRow::allocation_usage_for(TupleValuesView values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Predict the real single-block row request without allocating it. |
| inputs / outputs | Stable public values view yields allocation count1, framed requested bytes and logical descriptor/string payload bytes. |
| invariants | Uses the same cell_payload_bytes routine as copy, including zero-cell framing; this does not reserve memory or a work grant. |
| ownership | Borrows input; returns three inline accounting scalars. |
| failure | Invalid scalar or size/framing overflow rejects before allocation. |
| cost | O(cells) size scan with bounded adaptation, no string byte copy or scratch allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0039

[Lines 253–256](../../../../../src/storage/accounted_row.cpp#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedRow AccountedRow::copy_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy either legacy or native public values directly to one native row block. |
| inputs / outputs | TupleValuesView, destination account and attribution produce independent AccountedRow. |
| invariants | View/source must stay stable for both passes; input shared ownership does not become a retained output mirror. |
| ownership | Output owns deep bytes in original requested account; public view ownership is only borrowed during the call. |
| failure | View adaptation/admission failure returns no row. |
| cost | Two field passes plus actual string copies, one native allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0040

[Lines 257–265](../../../../../src/storage/accounted_row.cpp#L257); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedRow AccountedRow::project(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gather an ordered field selection directly into one native block. |
| inputs / outputs | RowView and FieldId span produce a deep owning projected row, including repeated or empty selections. |
| invariants | Check every field bound before preflight/copy; projection metadata may already be proven, but this standalone primitive still checks numeric ranges. |
| ownership | Copies selected descriptors/string bytes to the receiving account; retains no source row/vector. |
| failure | Bad field raises MemoryFailure(contract); size or funding failure leaves source unchanged. |
| cost | O(selected fields) bounds pass plus two gather passes and selected string bytes; repeated selections copy their bytes again. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0041

[Lines 266–268](../../../../../src/storage/accounted_row.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RowView AccountedRow::view() const & noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow this row descriptor array without copying or acquiring ownership. |
| inputs / outputs | Returns pointer/size RowView; default/moved-from AccountedRow gives empty view. |
| invariants | Any string and descriptor access requires the underlying MemoryBlock owner to remain alive and unchanged. |
| ownership | View itself retains no account/block; rvalue use is deleted. |
| failure | Noexcept. |
| cost | O(1). |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/scalars.md](../../../../scalars.md) |

## B0042

[Lines 269–270](../../../../../src/storage/accounted_row.cpp#L269); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L269-L270:sha256:7089e9cc52c39a53c28433397476fe0fa1e71e49e678f867277ec88cc7e152ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in src/storage/accounted_row.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/scalars.md](../../../../scalars.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
