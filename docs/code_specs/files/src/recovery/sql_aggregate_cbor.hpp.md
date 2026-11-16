# `src/recovery/sql_aggregate_cbor.hpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_cbor.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `f30a3e96fcafa6fa5631545a01f77bcc9b40db0e675ab4545b6f0c56d66b98c1`. 75 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/recovery/sql_aggregate_cbor.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // The factory's CBOR subset is definite integers/TEXT/arrays/maps/bool/NULL. · [reviewed contract](#b0001) |
| [B0002 · 11–12](../../../../../src/recovery/sql_aggregate_cbor.hpp#L11) | Callable definition: public: Cbor(binary_detail::Budget& budget,const DescriptorLimits& limits) : budget_(budget),limits_(limits) | calls budget_, limits_ · [reviewed contract](#b0002) |
| [B0003 · 13–15](../../../../../src/recovery/sql_aggregate_cbor.hpp#L13) | Callable definition: void inspect(std::string_view bytes) | calls value, binary_detail::require, size; guard binary_detail::Reader reader{bytes,budget_};value(reader,0);binary_detail::require(reader.position=… · [reviewed contract](#b0003) |
| [B0004 · 16–30](../../../../../src/recovery/sql_aggregate_cbor.hpp#L16) | Callable definition: private: static bool utf8(std::string_view text) noexcept | calls size; returns false; false; 2 loop sites; source comment (unverified): // CBOR TEXT allows U+0000; SQL type/name validation is a later factory step. · [reviewed contract](#b0004) |
| [B0005 · 31–40](../../../../../src/recovery/sql_aggregate_cbor.hpp#L31) | Callable definition: std::pair&lt;unsigned,std::uint64_t&gt; head(binary_detail::Reader& reader) | calls require, charge, integer; guard require(items_&lt;limits_.cbor_items,ImageFault::limit);++items_;budget_.charge(1);; returns {major,additional}; {major,result}; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 41–47](../../../../../src/recovery/sql_aggregate_cbor.hpp#L41) | Callable definition: std::string_view text(binary_detail::Reader& reader,std::uint64_t count,bool key) | calls binary_detail::require, take, charge, utf8; guard binary_detail::require(count&lt;=budget_.limits.scalar_bytes && count&lt;=SIZE_MAX,ImageFault::limit);; returns result; source comment (unverified): // Factory binding images retain opaque hint/name bytes as string values. · [reviewed contract](#b0006) |
| [B0007 · 48–70](../../../../../src/recovery/sql_aggregate_cbor.hpp#L48) | Callable definition: void value(binary_detail::Reader& reader,std::size_t depth) | calls require, head, text, charge; guard require(depth&lt;=limits_.cbor_depth,ImageFault::limit);const auto \[major,count\]=head(reader);; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 71–75](../../../../../src/recovery/sql_aggregate_cbor.hpp#L71) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::recovery::sql_aggregate::detail · [reviewed contract](#b0008) |

## B0001

[Lines 1–10](../../../../../src/recovery/sql_aggregate_cbor.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:d531885c3f1f8206d46cfbf29724ba744b8e25195e6a93c47212d16e8968a533
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Header guard and descriptor/binary-budget dependencies, then opens the SQL aggregate detail namespace and begins the strict CBOR-subset validator class. Embedded source note records intended usage: The factory's CBOR subset is definite integers/TEXT/arrays/maps/bool/NULL. Validate minimal widths, key UTF8, depth/items/work and strict map-key ordering before a DOM can allocate or erase duplicate keys. No tags/bytes/floats. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [docs/code_specs/files/src/recovery/sql_aggregate_cbor.hpp.md](sql_aggregate_cbor.hpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0002

[Lines 11–12](../../../../../src/recovery/sql_aggregate_cbor.hpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 public:
  Cbor(binary_detail::Budget& budget,const DescriptorLimits& limits) : budget_(budget),limits_(limits) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the wire preflight object to one shared byte/work Budget and immutable DescriptorLimits. |
| inputs / outputs | Stores references to the caller’s Budget and limits plus a local CBOR item counter. |
| invariants | The same Cbor instance validates binding and recipe in order so the item allowance is shared across both components. |
| ownership | Budget and limits must outlive the Cbor helper; the helper owns no input buffer. |
| failure | Construction performs no validation or allocation. |
| cost | Two reference stores and one zeroed counter. |
| Design | [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0003

[Lines 13–15](../../../../../src/recovery/sql_aggregate_cbor.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void inspect(std::string_view bytes) {
    binary_detail::Reader reader{bytes,budget_};value(reader,0);binary_detail::require(reader.position==bytes.size());
  }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require exactly one complete supported CBOR value in the supplied component bytes. |
| inputs / outputs | Creates a bounded Reader over the component, parses one root at depth zero, and rejects any trailing bytes. |
| invariants | This is structural preflight only; it never materializes or rewrites the parsed value. |
| ownership | Input bytes and shared Budget are borrowed for the call. |
| failure | Truncated, unsupported, over-limit or trailing encodings fail with ImageFailure. |
| cost | Visits every encoded head/content byte through the shared Reader budget plus structural comparisons. |
| Design | [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0004

[Lines 16–30](../../../../../src/recovery/sql_aggregate_cbor.hpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 private:
  static bool utf8(std::string_view text) noexcept {
    // CBOR TEXT allows U+0000; SQL type/name validation is a later factory step.
    std::size_t i=0;
    while(i<text.size()) {
      const auto first=static_cast<unsigned char>(text[i++]);if(first<0x80)continue;
      const auto count=first>=0xc2 && first<=0xdf?1U:first>=0xe0 && first<=0xef?2U:first>=0xf0 && first<=0xf4?3U:0U;
      if(!count || text.size()-i<count)return false;
      const auto second=static_cast<unsigned char>(text[i]);
      if((first==0xe0 && second<0xa0) || (first==0xed && second>=0xa0) ||
          (first==0xf0 && second<0x90) || (first==0xf4 && second>=0x90))return false;
      for(unsigned j=0;j<count;++j)if((static_cast<unsigned char>(text[i++])&0xc0U)!=0x80U)return false;
    }
    return true;
  }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate UTF8 map-key bytes while leaving CBOR text values opaque. |
| inputs / outputs | Rejects malformed/overlong encodings, surrogate code points and values beyond Unicode’s upper bound. |
| invariants | The check is only used for map keys; string values are structurally bounded and retained byte-for-byte for genuine catalog/SQL validation later. |
| ownership | Reads a borrowed string_view, returns a scalar, and is noexcept. |
| failure | Returns false on malformed UTF8; caller maps that to ImageFault::scalar. |
| cost | Linear key-byte scan, no allocation. |
| Design | [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0005

[Lines 31–40](../../../../../src/recovery/sql_aggregate_cbor.hpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::pair<unsigned,std::uint64_t> head(binary_detail::Reader& reader) {
    using binary_detail::require;
    require(items_<limits_.cbor_items,ImageFault::limit);++items_;budget_.charge(1);
    const auto first=reader.integer(1);const auto major=static_cast<unsigned>(first>>5),additional=static_cast<unsigned>(first&31);
    if(additional<24)return {major,additional};
    require(additional>=24 && additional<=27);const auto width=1U<<(additional-24);
    std::uint64_t result=0;for(unsigned i=0;i<width;++i)result=(result<<8)|reader.integer(1);
    constexpr std::array<std::uint64_t,4> minimum{24,256,65536,4294967296ULL};
    require(result>=minimum[additional-24]);return {major,result};
  }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and validate one CBOR initial head with minimal integer/length width. |
| inputs / outputs | Counts one item, charges the initial byte and extra-width bytes, and accepts only compact values or additional-info widths 1/2/4/8 with minimum legal values. |
| invariants | Rejects indefinite/reserved widths and nonminimal encodings before interpreting a major-type payload. |
| ownership | Advances the borrowed Reader and shared Budget; returns major type plus decoded unsigned argument. |
| failure | Truncation, item/work cap or malformed width fails with the corresponding fixed ImageFailure. |
| cost | Constant control plus at most eight encoded head bytes per item. |
| Design | [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0006

[Lines 41–47](../../../../../src/recovery/sql_aggregate_cbor.hpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::string_view text(binary_detail::Reader& reader,std::uint64_t count,bool key) {
    binary_detail::require(count<=budget_.limits.scalar_bytes && count<=SIZE_MAX,ImageFault::limit);
    const auto result=reader.take(static_cast<std::size_t>(count));
    // Factory binding images retain opaque hint/name bytes as string values.
    // Preserve them exactly; genuine SQL/catalog admission checks their use.
    if(key){budget_.charge(count);binary_detail::require(utf8(result),ImageFault::scalar);}return result;
  }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a bounded CBOR text payload and validate UTF8 only for map keys. |
| inputs / outputs | Checks declared length against scalar-byte limits and SIZE_MAX, consumes exactly that span through Reader, and for keys charges/checks UTF8. |
| invariants | Value text remains opaque bytes; domain-specific UTF8/type restrictions belong to the real SQL/catalog factories. |
| ownership | Returned view borrows the original frame and is compared only during this preflight. |
| failure | Oversized/truncated text fails as a bounded wire/scalar error; malformed key UTF8 fails before DOM parsing. |
| cost | O(text length) Reader accounting; key text additionally costs an UTF8 scan. |
| Design | [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md) |

## B0007

[Lines 48–70](../../../../../src/recovery/sql_aggregate_cbor.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void value(binary_detail::Reader& reader,std::size_t depth) {
    using binary_detail::require;
    require(depth<=limits_.cbor_depth,ImageFault::limit);const auto [major,count]=head(reader);
    switch(major) {
      case 0:return;
      case 1:require(count<=INT64_MAX,ImageFault::scalar);return;
      case 3:static_cast<void>(text(reader,count,false));return;
      case 4:
        require(count<=limits_.cbor_items-items_,ImageFault::limit);
        for(std::uint64_t i=0;i<count;++i)value(reader,depth+1);
        return;
      case 5:{
        require(count<=(limits_.cbor_items-items_)/2,ImageFault::limit);std::string_view previous;
        for(std::uint64_t i=0;i<count;++i) {
          const auto [kind,size]=head(reader);require(kind==3);const auto key=text(reader,size,true);
          if(i>0){budget_.charge(std::min(previous.size(),key.size()));require(previous<key);}previous=key;
          value(reader,depth+1);
        }return;
      }
      case 7:require(count==20 || count==21 || count==22);return;
      default:require(false);
    }
  }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the restricted definite CBOR value tree, depth, item counts and ordered unique string map keys. |
| inputs / outputs | Accepts unsigned/negative integers, text, arrays, maps, booleans and null; recursively visits arrays/maps and compares map keys in strict string-byte order. |
| invariants | Rejects bytes, tags, floats, indefinite forms, unsupported simple values, non-string keys, duplicates and unsorted keys before a DOM can erase ambiguity. |
| ownership | Uses only the borrowed Reader, shared Budget, scalar prior-key view and bounded call stack. |
| failure | Depth/items/work/schema errors raise fixed ImageFailure; stack depth is capped at DescriptorLimits.cbor_depth and maximum configured depth 256. |
| cost | Linear encoded-byte/item traversal plus charged common-prefix key comparison extents; recursion stack is depth bounded. |
| Design | [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [docs/sql_aggregate_descriptor.md §Wire and bounded parsing](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_descriptor.md §Ownership, failure and cost](../../../../sql_aggregate_descriptor.md) |

## B0008

[Lines 71–75](../../../../../src/recovery/sql_aggregate_cbor.hpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L75:sha256:bf8bf3bd4767a1404092850ee3f8dacc7ae07c77456525b16f931d00e1bc9fd4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finishes Cbor’s borrowed Budget/DescriptorLimits references and item counter, closes the helper class and its detail namespace. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp), [docs/code_specs/files/src/recovery/sql_aggregate_cbor.hpp.md](sql_aggregate_cbor.hpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |
