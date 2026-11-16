#pragma once
#include "crown/ir/model.hpp"
#include "crown/api/error.hpp"
#include <climits>
#include <limits>
#include <string_view>
#include <utility>
namespace crown::planner::frozen_binding_v2 {
// Private binding format v2 directly records every Catalog/Query field. It
// uses ordinary strings and no JSON DOM. Current vendored JSON has its own
// bad_alloc cleanup fallback; it is separate from this frozen byte-format test.
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

struct BindingEncoder {
  std::string bytes = "CROWN-CANDIDATE-BINDING;2;";

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
  void column_ids(const std::vector<ColumnId>& ids) {
    sequence(ids.size());
    for (const auto id : ids) unsigned_integer(static_cast<std::uint64_t>(id.value));
  }
  void column(const Column& value) {
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
  void constraint(const Constraint& value) {
    if (const auto* unique = std::get_if<UniqueConstraint>(&value)) {
      record("unique_constraint");
      string(unique->name);
      column_ids(unique->columns);
      enumeration(unique->status);
    } else {
      const auto& foreign = std::get<ForeignKeyConstraint>(value);
      record("foreign_key_constraint");
      string(foreign.name);
      column_ids(foreign.columns);
      unsigned_integer(static_cast<std::uint64_t>(foreign.referenced_table.value));
      column_ids(foreign.referenced_columns);
      enumeration(foreign.status);
    }
  }
  void table(const Table& value) {
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
  void scalar(const Value& value) {
    record("value");
    // Explicit native variant index distinguishes every scalar type, including
    // date days versus int64 and decimal text versus a native string constant.
    unsigned_integer(static_cast<std::uint64_t>(value.index()));
    switch (value.index()) {
      case 0: signed_integer(std::get<std::int64_t>(value)); return;
      case 1: string(std::get<std::string>(value)); return;
      case 2: boolean(std::get<bool>(value)); return;
      case 3: signed_integer(std::get<Date>(value).epoch_days()); return;
      case 4:
        // Canonical exact text; its temporary string has nonallocating teardown.
        string(std::get<Decimal>(value).to_string());
        return;
      default:
        throw Error("candidate_binding_kind", "unsupported candidate scalar kind");
    }
  }
  void term(const Term& value) {
    record("term");
    unsigned_integer(static_cast<std::uint64_t>(value.index()));
    switch (value.index()) {
      case 0:
        unsigned_integer(static_cast<std::uint64_t>(std::get<VariableId>(value).value));
        return;
      case 1: scalar(std::get<Value>(value)); return;
      case 2: return; // IgnoredColumn has no payload.
      default:
        throw Error("candidate_binding_kind", "unsupported candidate term kind");
    }
  }
  void catalog(const Catalog& value) {
    record("catalog");
    unsigned_integer(value.version);
    sequence(value.tables.size());
    for (const auto& item : value.tables) table(item);
  }
  void query(const Query& value) {
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
// Test byte equivalence only: editable source metadata is not admission authority.
std::string binding_bytes(const Catalog& catalog, const Query& query) {
  BindingEncoder encoder;
  encoder.catalog(catalog);
  encoder.query(query);
  return std::move(encoder.bytes);
}
} // namespace crown::planner::frozen_binding_v2
