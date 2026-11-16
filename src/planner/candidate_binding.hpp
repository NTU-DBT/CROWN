#pragma once
#include "crown/ir/model.hpp"
#include "crown/storage/accounted_row.hpp"
#include "crown/resource/owner_allocator.hpp"
#include <array>
#include <type_traits>
#include "crown/api/error.hpp"
#include <climits>
#include <limits>
#include <string_view>
#include <utility>
namespace crown::planner::binding_detail {
enum class LimitKind { work, bytes };
struct Limit { LimitKind kind; };
// Work is debited before bytes. A later byte rejection or sink allocation
// failure does not roll back accepted debits; this is blocking admission.
struct Budget {
  std::uint64_t& work; std::uint64_t& bytes;
  std::uint64_t max_work, max_bytes;
  void charge(std::uint64_t n) {
    if(work>max_work || n>max_work-work)throw Limit{LimitKind::work};
    work+=n;
    if(bytes>max_bytes || n>max_bytes-bytes)throw Limit{LimitKind::bytes};
    bytes+=n;
  }
};
struct Bytes {
  std::string value; Budget* budget;
  static std::string prefix(Budget* b) {
    constexpr std::string_view text="CROWN-CANDIDATE-BINDING;2;";
    if(b){b->charge(static_cast<std::uint64_t>(text.size()));}
    return std::string("CROWN-CANDIDATE-BINDING;2;");
  }
  explicit Bytes(Budget* b):value(prefix(b)),budget(b) {}
  void push_back(char c){if(budget)budget->charge(1);value.push_back(c);}
  void append(std::string_view s){if(budget)budget->charge(static_cast<std::uint64_t>(s.size()));value.append(s);}
};
struct AllocatedBytes {
  using String=std::basic_string<char,std::char_traits<char>,resource::OwnerAllocator<char>>;
  String value;Budget* budget;
  AllocatedBytes(Budget* b,const resource::MemoryAccount& account,resource::MemoryPurpose purpose,resource::MemoryAttribution owner)
      :value(resource::OwnerAllocator<char>(account,purpose,owner)),budget(b) {
    append("CROWN-CANDIDATE-BINDING;2;");
  }
  void push_back(char c){if(budget)budget->charge(1);value.push_back(c);}
  void append(std::string_view s){if(budget)budget->charge(static_cast<std::uint64_t>(s.size()));value.append(s);}
};
// Private binding format v2 directly records every Catalog/Query field. It
// never constructs a JSON DOM: that DOM's noexcept teardown can allocate while
// unwinding an admission failure. The explicit ordinary and accounted sinks
// share the same byte/field/work contract.
//
// Records are R + a framed type name followed by fields in the order below.
// Arrays are A + uint64 count; optionals are P + one presence byte. Strings are
// S + uint64 byte length + raw bytes. U/I/E carry eight-byte big-endian unsigned,
// signed or enum words; signed values use their modulo-2^64 representation.
// Booleans are B + one 0/1 byte. Every length fits the supported size_t domain;
// embedded NULs and non-UTF-8 bytes are retained without hashing or conversion.
// Admission is whole allocating work outside enumeration quanta. Field order
// and all variant/enum meanings are private versioned binding-format contracts.
static_assert(CHAR_BIT == 8);
static_assert(std::numeric_limits<std::size_t>::digits <=
              std::numeric_limits<std::uint64_t>::digits);

template<class Sink> struct BasicBindingEncoder {
  Sink bytes;
  template<class... Args> explicit BasicBindingEncoder(Budget* budget,Args&&... args):bytes(budget,std::forward<Args>(args)...) {}

  void word(std::uint64_t value) {
    for (unsigned byte = 0; byte < 8; ++byte) {
      const unsigned shift = 56U - 8U * byte;
      bytes.push_back(static_cast<char>((value >> shift) & 0xffU));
    }
  }
  void unsigned_integer(std::uint64_t value) {
    bytes.push_back('U');
    word(value);
  }
  void signed_integer(std::int64_t value) {
    bytes.push_back('I');
    word(static_cast<std::uint64_t>(value));
  }
  template<class Enum> void enumeration(Enum value) {
    bytes.push_back('E');
    word(static_cast<std::uint64_t>(value));
  }
  void boolean(bool value) {
    bytes.push_back('B');
    bytes.push_back(value ? '\x01' : '\x00');
  }
  void string(std::string_view value) {
    bytes.push_back('S');
    word(static_cast<std::uint64_t>(value.size()));
    bytes.append(value);
  }
  void record(std::string_view kind) {
    bytes.push_back('R');
    string(kind);
  }
  void sequence(std::size_t count) {
    bytes.push_back('A');
    word(static_cast<std::uint64_t>(count));
  }
  void presence(bool present) {
    bytes.push_back('P');
    bytes.push_back(present ? '\x01' : '\x00');
  }
  template<class Range> void column_ids(const Range& ids) {
    sequence(ids.size());
    for (const auto id : ids) unsigned_integer(static_cast<std::uint64_t>(id.value));
  }
  template<class ColumnView> void column(const ColumnView& value) {
    record("column");
    string(value.name);
    enumeration(value.type);
    boolean(value.nullable);
    enumeration(value.collation);
    presence(value.decimal.has_value());
    if (value.decimal) {
      record("decimal_spec");
      unsigned_integer(value.decimal->precision);
      unsigned_integer(value.decimal->scale);
    }
  }
  template<class ConstraintView> void constraint(const ConstraintView& value) {
    if (const auto* unique = std::get_if<0>(&value)) {
      record("unique_constraint");
      string(unique->name);
      column_ids(unique->columns);
      enumeration(unique->status);
    } else {
      const auto& foreign = std::get<1>(value);
      record("foreign_key_constraint");
      string(foreign.name);
      column_ids(foreign.columns);
      unsigned_integer(static_cast<std::uint64_t>(foreign.referenced_table.value));
      column_ids(foreign.referenced_columns);
      enumeration(foreign.status);
    }
  }
  template<class TableView> void table(const TableView& value) {
    record("table");
    string(value.name);
    sequence(value.columns.size());
    for (const auto& item : value.columns) column(item);
    unsigned_integer(value.source_schema_version);
    sequence(value.constraints.size());
    for (const auto& item : value.constraints) constraint(item);
    record("table_statistics");
    presence(value.statistics.row_count.has_value());
    if (value.statistics.row_count) unsigned_integer(*value.statistics.row_count);
    sequence(value.statistics.distinct_counts.size());
    for (const auto& item : value.statistics.distinct_counts) {
      record("distinct_estimate");
      column_ids(item.columns);
      unsigned_integer(item.estimate);
    }
    sequence(value.key_hints.size());
    for (const auto& item : value.key_hints) {
      record("key_hint");
      column_ids(item.columns);
      string(item.reason);
    }
  }
  template<class Scalar> void scalar(const Scalar& value) {
    record("value");
    // Explicit native variant index distinguishes every scalar type, including
    // date days versus int64 and decimal text versus a native string constant.
    unsigned_integer(static_cast<std::uint64_t>(value.index()));
    switch (value.index()) {
      case 0: signed_integer(std::get<std::int64_t>(value)); return;
      case 1: string(std::get<1>(value)); return;
      case 2: boolean(std::get<bool>(value)); return;
      case 3: signed_integer(std::get<Date>(value).epoch_days()); return;
      case 4:
        if constexpr(std::is_same_v<Sink,Bytes>) {
          // Standalone/reference encoding keeps its explicit ordinary boundary.
          if constexpr(std::is_same_v<std::remove_cvref_t<decltype(std::get<4>(value))>,Decimal>)
            string(std::get<4>(value).to_string());
          else string(std::get<Decimal>(storage::export_scalar(value)).to_string());
        }else {
          // The native runtime path renders the bounded exact coefficient in
          // fixed storage, without exporting an ordinary Decimal/string.
          const auto decimal=[&] {
            if constexpr(std::is_same_v<std::remove_cvref_t<decltype(std::get<4>(value))>,Decimal>)
              return storage::InlineDecimal::copy_of(std::get<4>(value));
            else return std::get<4>(value);
          }();
          std::array<char,storage::InlineDecimal::text_capacity> text{};
          const auto size=decimal.render(text);string({text.data(),size});
        }
        return;
      default:
        throw Error("candidate_binding_kind", "unsupported candidate scalar kind");
    }
  }
  template<class TermView> void term(const TermView& value) {
    record("term");
    unsigned_integer(static_cast<std::uint64_t>(value.index()));
    switch (value.index()) {
      case 0:
        unsigned_integer(static_cast<std::uint64_t>(std::get<VariableId>(value).value));
        return;
      case 1: scalar(std::get<1>(value)); return;
      case 2: return; // IgnoredColumn has no payload.
      default:
        throw Error("candidate_binding_kind", "unsupported candidate term kind");
    }
  }
  template<class CatalogView> void catalog(const CatalogView& value) {
    record("catalog");
    unsigned_integer(value.version);
    sequence(value.tables.size());
    for (const auto& item : value.tables) table(item);
  }
  template<class QueryView> void query(const QueryView& value) {
    record("query");
    sequence(value.variables.size());
    for (const auto& item : value.variables) {
      record("variable");
      string(item.name);
      enumeration(item.type);
    }
    sequence(value.atoms.size());
    for (const auto& item : value.atoms) {
      record("atom");
      string(item.occurrence);
      unsigned_integer(static_cast<std::uint64_t>(item.table.value));
      sequence(item.terms.size());
      for (const auto& item_term : item.terms) term(item_term);
    }
    sequence(value.head.size());
    for (const auto& item : value.head) {
      record("output");
      unsigned_integer(static_cast<std::uint64_t>(item.variable.value));
      string(item.alias);
    }
    boolean(value.contradiction);
  }
};
using BindingEncoder=BasicBindingEncoder<Bytes>;
template<class CatalogView,class QueryView>
inline std::string encode(const CatalogView& catalog, const QueryView& query, Budget* budget=nullptr) {
  BindingEncoder encoder(budget);
  encoder.catalog(catalog);
  encoder.query(query);
  return std::move(encoder.bytes.value);
}
template<class CatalogView,class QueryView>
inline AllocatedBytes::String encode(const CatalogView& catalog,const QueryView& query,
    const resource::MemoryAccount& account,resource::MemoryPurpose purpose,resource::MemoryAttribution owner,Budget* budget=nullptr) {
  BasicBindingEncoder<AllocatedBytes> encoder(budget,account,purpose,owner);
  encoder.catalog(catalog);encoder.query(query);return std::move(encoder.bytes.value);
}
} // namespace crown::planner::binding_detail
