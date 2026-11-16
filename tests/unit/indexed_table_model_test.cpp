// Exercise the common InsertResult and shared-owner interfaces.
// This fixture exercises only the ordinary table APIs.
#include "crown/storage/indexed.hpp"
#include "crown/storage/reference.hpp"
#ifdef CROWN_STORAGE_TESTING
#include "indexed_testing.hpp"
#endif
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && !defined(CROWN_STORAGE_TESTING)
#error "Collision fixture requires the coherent testing storage library"
#endif

#include <algorithm>
#include <array>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

using namespace crown;
using namespace crown::storage;

namespace {

void verify(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}

IndexWorkAllowance ample() {
  return IndexWorkAllowance(IndexWork{1'000'000'000, 1'000'000'000,
                                      1'000'000'000, 1'000'000'000,
                                      1'000'000'000});
}

template <class Function>
decltype(auto) with_work(Function&& function) {
  auto allowance = ample();
  return std::forward<Function>(function)(allowance);
}

enum class Kind : std::uint8_t { integer, text, boolean, date, decimal };

struct Cell {
  Kind kind;
  std::string payload;
  bool operator==(const Cell&) const = default;
  auto operator<=>(const Cell&) const = default;
};

using ModelRow = std::vector<Cell>;
using ModelCell = Cell;
using ModelKey = ModelRow;
using TupleNumber = std::uint64_t;
using IndexNumber = std::uint64_t;

struct RawRow {
  std::int64_t integer;
  std::string text;
  bool boolean;
  std::string date;
  std::string decimal;
};

constexpr std::array<std::int64_t, 8> integer_values{
    0,
    std::numeric_limits<std::int64_t>::min(),
    9'007'199'254'740'992LL,
    9'007'199'254'740'993LL,
    9'007'199'254'740'994LL,
    -1,
    1,
    42};

constexpr std::array<std::string_view, 6> date_values{
    "1970-01-01", "1969-12-31", "2000-01-01", "2000-02-29", "0001-01-01", "9999-12-31"};

constexpr std::array<std::int32_t, 6> date_epoch_days{
    0, -1, 10'957, 11'016, -719'162, 2'932'896};

constexpr std::array<std::string_view, 6> decimal_values{
    "0.000",
    "1.2300",
    "-12.500",
    "1.23",
    "0.000000000000000001",
    "12345678901234567890123456789012345678"};

RawRow raw_row(std::size_t number) {
  // Two independently generated pool entries have equal row values. The
  // decimal spellings differ, so row identity also covers canonical aliases.
  if (number == 30) {
    auto row = raw_row(12);
    row.decimal = "0.000000";
    return row;
  }
  if (number == 31) {
    auto row = raw_row(13);
    row.decimal = "1.23";
    return row;
  }

  std::string text;
  switch (number) {
    case 0: text = std::string("nul\0tail", 8); break;
    case 1: text = std::string("\x80\xfftail", 6); break;
    case 2: text = std::string("\0\xff", 2); break;
    case 3: text.assign(1024, 'x');text.push_back('\0');text += "tail";break;
    default: text = "payload-" + std::to_string(number); break;
  }
  return RawRow{integer_values[number % integer_values.size()],
                std::move(text), (number % 2) != 0,
                std::string(date_values[number % date_values.size()]),
                std::string(decimal_values[number % decimal_values.size()])};
}

std::int32_t literal_epoch_days(std::string_view literal) {
  for (std::size_t i = 0; i < date_values.size(); ++i)
    if (date_values[i] == literal) return date_epoch_days[i];
  throw std::runtime_error("date fixture has no independent epoch-day literal");
}

// This small decimal formatter is the model's own value canonicalizer. It
// handles the fixture's ordinary base-10 literals without native Decimal APIs.
std::string canonical_decimal(std::string_view literal) {
  bool negative = false;
  std::size_t offset = 0;
  if (!literal.empty() && (literal.front() == '-' || literal.front() == '+')) {
    negative = literal.front() == '-';
    offset = 1;
  }

  std::string digits;
  std::size_t scale = 0;
  bool after_point = false;
  for (; offset < literal.size(); ++offset) {
    const char ch = literal[offset];
    if (ch == '.') {
      after_point = true;
    } else {
      digits.push_back(ch);
      if (after_point) ++scale;
    }
  }

  const auto first = digits.find_first_not_of('0');
  if (first == std::string::npos) return "0";
  digits.erase(0, first);
  while (scale != 0 && !digits.empty() && digits.back() == '0') {
    digits.pop_back();
    --scale;
  }

  std::string body;
  if (scale == 0) {
    body = digits;
  } else if (digits.size() <= scale) {
    body = "0." + std::string(scale - digits.size(), '0') + digits;
  } else {
    const auto split = digits.size() - scale;
    body = digits.substr(0, split) + "." + digits.substr(split);
  }
  return negative ? "-" + body : body;
}

// The expected cells are generated directly from the raw fixture literals.
// They never pass through Value equality, hashing, Tuple, or Projection.
ModelRow model_row(const RawRow& row) {
  return ModelRow{
      {Kind::integer, std::to_string(row.integer)},
      {Kind::text, row.text},
      {Kind::boolean, row.boolean ? "1" : "0"},
      {Kind::date, std::to_string(literal_epoch_days(row.date))},
      {Kind::decimal, canonical_decimal(row.decimal)}};
}

Tuple native_row(const TupleLayout& layout, const RawRow& raw) {
  Row values;
  values.emplace_back(raw.integer);
  values.emplace_back(raw.text);
  values.emplace_back(raw.boolean);
  values.emplace_back(Date::parse(raw.date));
  values.emplace_back(Decimal::parse(raw.decimal));
  return layout.tuple(std::move(values));
}

ModelCell decode_cell(const Value& value) {
  return std::visit([](const auto& scalar) -> ModelCell {
    using T = std::decay_t<decltype(scalar)>;
    if constexpr (std::is_same_v<T, std::int64_t>) {
      return {Kind::integer, std::to_string(scalar)};
    } else if constexpr (std::is_same_v<T, std::string>) {
      return {Kind::text, scalar};
    } else if constexpr (std::is_same_v<T, bool>) {
      return {Kind::boolean, scalar ? "1" : "0"};
    } else if constexpr (std::is_same_v<T, Date>) {
      return {Kind::date, std::to_string(scalar.epoch_days())};
    } else {
      return {Kind::decimal, canonical_decimal(scalar.to_string())};
    }
  }, value);
}

ModelRow decode_tuple(const Tuple& tuple) {
  ModelRow result;
  result.reserve(tuple.values().size());
  for (const auto& value : crown::storage::export_row(tuple.values())) result.push_back(decode_cell(value));
  return result;
}

ModelKey project_model(const ModelRow& row, const std::vector<std::size_t>& fields) {
  ModelKey key;
  key.reserve(fields.size());
  for (const auto field : fields) key.push_back(row.at(field));
  return key;
}

Tuple literal_probe(const TupleLayout& target, const Tuple& source,
                    const std::vector<std::size_t>& fields) {
  // Select the declared source slots directly; this intentionally does not
  // call Projection::apply or derive expected data from a native projection.
  Row values;
  values.reserve(fields.size());
  for (const auto field : fields) values.push_back(crown::storage::export_row(source.values()).at(field));
  return target.tuple(std::move(values));
}

struct HandlePair {
  TupleHandle indexed;
  TupleHandle reference;
};

struct IndexModel {
  std::size_t program;
  std::vector<std::size_t> fields;
};

struct ModelState {
  std::uint64_t next_tuple = 1;
  std::uint64_t next_index = 1;
  std::map<ModelRow, TupleNumber> by_value;
  std::map<TupleNumber, ModelRow> by_id;
  std::vector<TupleNumber> insertion_order;
  std::map<TupleNumber, HandlePair> handles;
  std::vector<TupleNumber> stale_ids;
  std::map<IndexNumber, IndexModel> indexes;
  std::map<std::size_t, IndexNumber> active_programs;
};

void erase_model_row(ModelState& model, TupleNumber id) {
  const auto found = model.by_id.find(id);
  verify(found != model.by_id.end(), "model attempted to erase a non-live row");
  model.by_value.erase(found->second);
  model.by_id.erase(found);
  const auto order = std::find(model.insertion_order.begin(), model.insertion_order.end(), id);
  verify(order != model.insertion_order.end(), "model insertion-order row was absent");
  model.insertion_order.erase(order);
  model.stale_ids.push_back(id);
}

std::map<ModelKey, std::set<TupleNumber>> model_buckets(
    const ModelState& model, const std::vector<std::size_t>& fields) {
  std::map<ModelKey, std::set<TupleNumber>> result;
  for (const auto& [id, row] : model.by_id)
    result[project_model(row, fields)].insert(id);
  return result;
}

std::vector<TupleNumber> ids_from_set(const std::set<TupleNumber>& ids) {
  return {ids.begin(), ids.end()};
}

std::vector<TupleNumber> handle_ids(const std::vector<TupleHandle>& handles,
                                    StorageOwnerId owner, RelationId relation) {
  std::vector<TupleNumber> result;
  result.reserve(handles.size());
  for (const auto& handle : handles) {
    verify(handle.owner == owner && handle.relation == relation,
           "bucket returned a handle from another storage owner or relation");
    result.push_back(handle.tuple.value);
  }
  verify(std::is_sorted(result.begin(), result.end()),
         "bucket traversal violated monotonic logical tuple-ID order");
  return result;
}

class DeterministicBits {
 public:
  std::uint64_t next() noexcept {
    state_ ^= state_ << 13U;
    state_ ^= state_ >> 7U;
    state_ ^= state_ << 17U;
    return state_;
  }
 private:
  std::uint64_t state_ = 0x8b5ad4cef1297603ULL;
};

void differential_model() {
  // Large scalar payloads deliberately occupy only a small actual node set;
  // this is exact-value coverage, not a huge-cardinality runtime measurement.
  constexpr RelationId relation{77};
  TupleLayout source(LayoutId{700}, {{ScalarType::int64}, {ScalarType::string},
      {ScalarType::boolean}, {ScalarType::date}, {ScalarType::decimal}});
  const std::vector<std::vector<std::size_t>> program_fields{
      {}, {0, 0}, {4, 3, 2, 1, 0}, {0}, {0}, {1}, {2}, {3}, {4}};

  std::vector<TupleLayout> target_layouts;
  std::vector<Projection> programs;
  target_layouts.reserve(program_fields.size());
  programs.reserve(program_fields.size());
  for (std::size_t p = 0; p < program_fields.size(); ++p) {
    std::vector<Field> target_fields;
    std::vector<FieldId> source_fields;
    target_fields.reserve(program_fields[p].size());
    source_fields.reserve(program_fields[p].size());
    for (const auto source_field : program_fields[p]) {
      verify(source_field<source.fields().size(),"projection fixture source field is out of range");
      target_fields.push_back(source.fields()[source_field]);
      source_fields.emplace_back(FieldId{static_cast<std::uint32_t>(source_field)});
    }
    if (p == 4) {
      // Share the source and target layout tokens with program 3 while
      // constructing a distinct immutable Projection program object.
      target_layouts.push_back(target_layouts.at(3));
    } else {
      target_layouts.emplace_back(LayoutId{800 + static_cast<std::uint64_t>(p)},
                                  std::move(target_fields));
    }
    programs.emplace_back(source, target_layouts.back(), std::move(source_fields));
  }
  verify(programs[3].source().same_token(programs[4].source()) &&
             programs[3].target().same_token(programs[4].target()) &&
             !programs[3].same_token(programs[4]),
         "independent-equal program fixture did not share layouts and separate program identity");

  std::vector<RawRow> raw_pool;
  std::vector<ModelRow> model_pool;
  std::vector<Tuple> native_pool;
  raw_pool.reserve(32);
  model_pool.reserve(32);
  native_pool.reserve(32);
  for (std::size_t i = 0; i < 32; ++i) {
    raw_pool.push_back(raw_row(i));
    model_pool.push_back(model_row(raw_pool.back()));
    native_pool.push_back(native_row(source, raw_pool.back()));
  }

  constexpr IndexedLimits limits{64, 16, 1024, 1024, 4096, 8192, 128, 16};
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 1
  static_assert(limits.directory_slots <= 65536);
  verify((native_pool[0].hash() & ~std::uint64_t{0xffff}) !=
      (native_pool[1].hash() & ~std::uint64_t{0xffff}),
      "same-bucket fixture lacks different full cached hashes");
#endif
  ReferenceTable reference(relation, source);
  IndexedTable indexed(relation, source, limits);
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 1
  detail::IndexedTesting::collisions(indexed, detail::CollisionMode::same_bucket);
#elif defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 2
  detail::IndexedTesting::collisions(indexed, detail::CollisionMode::same_full_hash);
#elif defined(CROWN_STORAGE_COLLISION_PROFILE)
#error "Unknown collision fixture profile"
#endif
  verify(indexed.owner() != reference.owner(), "reference and indexed owners collided");
  ModelState model;
  DeterministicBits bits;

  const auto find_model_row = [&](std::size_t pool_slot) -> std::optional<TupleNumber> {
    const auto found = model.by_value.find(model_pool.at(pool_slot));
    if (found == model.by_value.end()) return std::nullopt;
    return found->second;
  };

  const auto insert = [&](std::size_t pool_slot) {
    const auto optimized = with_work([&](auto& work) {
      return indexed.insert(native_pool.at(pool_slot), work);
    });
    const auto oracle = reference.insert(native_pool.at(pool_slot));
    const auto existing = find_model_row(pool_slot);
    const bool expected_inserted = !existing.has_value();
    const TupleNumber expected_id = existing.value_or(model.next_tuple);
    verify(optimized.inserted == expected_inserted && oracle.inserted == expected_inserted,
           "insert/duplicate result differed from the independent model");
    verify(optimized.handle.tuple.value == expected_id && oracle.handle.tuple.value == expected_id,
           "insert logical ID differed from the independent model");
    verify(optimized.handle.owner == indexed.owner() && oracle.handle.owner == reference.owner(),
           "insert returned a handle from the wrong backend owner");
    if (expected_inserted) {
      ++model.next_tuple;
      model.by_value.emplace(model_pool.at(pool_slot), expected_id);
      model.by_id.emplace(expected_id, model_pool.at(pool_slot));
      model.insertion_order.push_back(expected_id);
    }
    model.handles[expected_id] = HandlePair{optimized.handle, oracle.handle};
  };

  const auto erase_value = [&](std::size_t pool_slot) {
    const auto expected = find_model_row(pool_slot);
    const bool optimized = with_work([&](auto& work) {
      return indexed.erase(native_pool.at(pool_slot), work);
    });
    const bool oracle = reference.erase(native_pool.at(pool_slot));
    verify(optimized == expected.has_value() && oracle == expected.has_value(),
           "erase-by-value result differed from the independent model");
    if (expected) erase_model_row(model, *expected);
  };

  const auto erase_handle = [&](TupleNumber id) {
    const auto known = model.handles.find(id);
    const HandlePair handles = known != model.handles.end()
        ? known->second
        : HandlePair{
              TupleHandle{indexed.owner(), relation, TupleId{model.next_tuple + 1'000'000}},
              TupleHandle{reference.owner(), relation, TupleId{model.next_tuple + 1'000'000}}};
    const bool expected = model.by_id.contains(id);
    const bool optimized = with_work([&](auto& work) {
      return indexed.erase(handles.indexed, work);
    });
    const bool oracle = reference.erase(handles.reference);
    verify(optimized == expected && oracle == expected,
           "erase-by-handle result differed from the independent model");
    if (expected) erase_model_row(model, id);
  };

  const auto add_index = [&](std::size_t program) {
    const auto optimized = with_work([&](auto& work) {
      return indexed.add_index(programs.at(program), work);
    });
    const auto oracle = reference.add_index(programs.at(program));
    const auto existing = model.active_programs.find(program);
    const bool is_new = existing == model.active_programs.end();
    const IndexNumber expected_id = is_new ? model.next_index : existing->second;
    verify(optimized.value == expected_id && oracle.value == expected_id,
           "add-index logical ID or same-token idempotence differed from the model");
    if (is_new) {
      ++model.next_index;
      model.indexes.emplace(expected_id, IndexModel{program, program_fields.at(program)});
      model.active_programs.emplace(program, expected_id);
    }
  };

  const auto drop_index = [&](IndexNumber id) {
    const bool expected = model.indexes.contains(id);
    const bool optimized = with_work([&](auto& work) {
      return indexed.drop_index(IndexId{id}, work);
    });
    const bool oracle = reference.drop_index(IndexId{id});
    verify(optimized == expected && oracle == expected,
           "drop-index result differed from the independent model");
    if (expected) {
      const auto program = model.indexes.at(id).program;
      model.indexes.erase(id);
      model.active_programs.erase(program);
    }
  };

  const auto erase_key = [&](IndexNumber id, std::size_t pool_slot) {
    const auto index = model.indexes.find(id);
    verify(index != model.indexes.end(), "fixture selected an absent index for erase-key");
    const auto expected_buckets = model_buckets(model, index->second.fields);
    const auto probe_key = project_model(model_pool.at(pool_slot), index->second.fields);
    const auto expected_members = expected_buckets.find(probe_key);
    const std::size_t expected_count = expected_members == expected_buckets.end()
        ? 0 : expected_members->second.size();
    const auto native_key = literal_probe(target_layouts.at(index->second.program),
        native_pool.at(pool_slot), index->second.fields);
    const auto optimized = with_work([&](auto& work) {
      return indexed.erase_key(IndexId{id}, native_key, work);
    });
    const auto oracle = reference.erase_key(IndexId{id}, native_key);
    verify(optimized == expected_count && oracle == expected_count,
           "erase-key count differed from the independent map-of-sets model");
    if (expected_members != expected_buckets.end()) {
      const auto removed = ids_from_set(expected_members->second);
      for (const auto row_id : removed) erase_model_row(model, row_id);
    }
  };

  const auto clear = [&] {
    with_work([&](auto& work) { indexed.clear(work); });
    reference.clear();
    const auto removed = model.insertion_order;
    for (const auto id : removed) erase_model_row(model, id);
  };

  const auto query = [&](std::size_t pool_slot) {
    const auto expected = find_model_row(pool_slot);
    const auto optimized = with_work([&](auto& work) {
      return indexed.find(native_pool.at(pool_slot), work);
    });
    const auto oracle = reference.find(native_pool.at(pool_slot));
    verify(optimized.has_value() == expected.has_value() && oracle.has_value() == expected.has_value(),
           "find presence differed from the independent model");
    if (expected) {
      verify(optimized->tuple.value == *expected && oracle->tuple.value == *expected,
             "find logical ID differed from the independent model");
      const auto handles = model.handles.at(*expected);
      const auto* indexed_tuple = with_work([&](auto& work) {
        return indexed.get(handles.indexed, work);
      });
      const auto* reference_tuple = reference.get(handles.reference);
      verify(indexed_tuple != nullptr && reference_tuple != nullptr &&
                 decode_tuple(*indexed_tuple) == model.by_id.at(*expected) &&
                 decode_tuple(*reference_tuple) == model.by_id.at(*expected),
             "get of a found row differed from the independent model");
    }
  };

  const auto compare_all = [&] {
    verify(indexed.size() == model.by_id.size() && reference.size() == model.by_id.size(),
           "backend row count differed from the independent model");

    std::vector<ModelRow> expected_insertion_order;
    expected_insertion_order.reserve(model.insertion_order.size());
    for (const auto id : model.insertion_order)
      expected_insertion_order.push_back(model.by_id.at(id));
    const auto optimized_snapshot = with_work([&](auto& work) { return indexed.snapshot(work); });
    std::vector<ModelRow> observed_insertion_order;
    observed_insertion_order.reserve(optimized_snapshot.size());
    for (const auto& tuple : optimized_snapshot) observed_insertion_order.push_back(decode_tuple(tuple));
    verify(observed_insertion_order == expected_insertion_order,
           "indexed snapshot did not preserve model insertion order and membership");

    const auto reference_snapshot = reference.snapshot();
    std::vector<ModelRow> observed_reference_rows;
    observed_reference_rows.reserve(reference_snapshot.size());
    for (const auto& tuple : reference_snapshot) observed_reference_rows.push_back(decode_tuple(tuple));
    std::sort(observed_reference_rows.begin(), observed_reference_rows.end());
    std::vector<ModelRow> expected_reference_rows;
    expected_reference_rows.reserve(model.by_value.size());
    for (const auto& [row, id] : model.by_value) {
      static_cast<void>(id);
      expected_reference_rows.push_back(row);
    }
    verify(observed_reference_rows == expected_reference_rows,
           "reference snapshot membership differed after lexical-order normalization");

    for (std::size_t pool_slot = 0; pool_slot < model_pool.size(); ++pool_slot) {
      const auto expected = find_model_row(pool_slot);
      const auto optimized = with_work([&](auto& work) {
        return indexed.find(native_pool[pool_slot], work);
      });
      const auto oracle = reference.find(native_pool[pool_slot]);
      verify(optimized.has_value() == expected.has_value() && oracle.has_value() == expected.has_value(),
             "input-pool find hit/miss differed from the independent model");
      if (expected)
        verify(optimized->tuple.value == *expected && oracle->tuple.value == *expected,
               "input-pool find returned the wrong logical ID");
    }

    for (const auto id : model.insertion_order) {
      const auto handles = model.handles.at(id);
      const auto* indexed_tuple = with_work([&](auto& work) {
        return indexed.get(handles.indexed, work);
      });
      const auto* reference_tuple = reference.get(handles.reference);
      verify(indexed_tuple != nullptr && reference_tuple != nullptr &&
                 decode_tuple(*indexed_tuple) == model.by_id.at(id) &&
                 decode_tuple(*reference_tuple) == model.by_id.at(id),
             "active logical ID get differed from the independent model");
    }
    if (!model.stale_ids.empty()) {
      const auto handles = model.handles.at(model.stale_ids.back());
      const auto* indexed_tuple = with_work([&](auto& work) {
        return indexed.get(handles.indexed, work);
      });
      const auto* reference_tuple = reference.get(handles.reference);
      verify(indexed_tuple == nullptr && reference_tuple == nullptr,
             "stale logical ID remained readable after erase or clear");
    }

    std::vector<IndexId> optimized_indices = with_work([&](auto& work) {
      return indexed.indices(work);
    });
    std::vector<IndexId> reference_indices = reference.indices();
    const auto by_index_id = [](IndexId a, IndexId b) { return a.value < b.value; };
    std::sort(optimized_indices.begin(), optimized_indices.end(), by_index_id);
    std::sort(reference_indices.begin(), reference_indices.end(), by_index_id);
    std::vector<IndexId> expected_indices;
    expected_indices.reserve(model.indexes.size());
    for (const auto& [id, state] : model.indexes) {
      static_cast<void>(state);
      expected_indices.emplace_back(IndexId{id});
    }
    verify(optimized_indices == expected_indices && reference_indices == expected_indices,
           "active index IDs differed from the independent model");

    for (const auto& [id, index] : model.indexes) {
      const IndexId index_id{id};
      const auto optimized_projection = with_work([&](auto& work) {
        return indexed.projection(index_id, work);
      });
      const auto reference_projection = reference.projection(index_id);
      verify(optimized_projection.same_token(programs.at(index.program)) &&
                 reference_projection.same_token(programs.at(index.program)),
             "backend returned a projection with the wrong program identity");
      const auto read_fields = [](const Projection& projection) {
        std::vector<std::size_t> result;
        result.reserve(projection.fields().size());
        for (const auto field : projection.fields()) result.push_back(field.value);
        return result;
      };
      verify(read_fields(optimized_projection) == index.fields &&
                 read_fields(reference_projection) == index.fields,
             "backend projection slots differed from the independent program description");

      const auto expected_buckets = model_buckets(model, index.fields);
      verify(with_work([&](auto& work) { return indexed.key_count(index_id, work); }) ==
                 expected_buckets.size(),
             "indexed live key count differed from the independent model");
      verify(reference.key_count(index_id) == expected_buckets.size(),
             "reference live key count differed from the independent model");

      std::vector<ModelKey> expected_keys;
      expected_keys.reserve(expected_buckets.size());
      for (const auto& [key, members] : expected_buckets) {
        static_cast<void>(members);
        expected_keys.push_back(key);
      }
      const auto optimized_keys = with_work([&](auto& work) {
        return indexed.keys(index_id, work);
      });
      const auto reference_keys = reference.keys(index_id);
      std::vector<ModelKey> observed_optimized_keys, observed_reference_keys;
      observed_optimized_keys.reserve(optimized_keys.size());
      observed_reference_keys.reserve(reference_keys.size());
      for (const auto& key : optimized_keys) observed_optimized_keys.push_back(decode_tuple(key));
      for (const auto& key : reference_keys) observed_reference_keys.push_back(decode_tuple(key));
      std::sort(observed_optimized_keys.begin(), observed_optimized_keys.end());
      std::sort(observed_reference_keys.begin(), observed_reference_keys.end());
      verify(observed_optimized_keys == expected_keys && observed_reference_keys == expected_keys &&
                 optimized_keys.size() == expected_buckets.size() &&
                 reference_keys.size() == expected_buckets.size(),
             "active index key sets differed from the independent map-of-sets model");

      for (std::size_t pool_slot = 0; pool_slot < model_pool.size(); ++pool_slot) {
        const auto model_key = project_model(model_pool[pool_slot], index.fields);
        const auto members = expected_buckets.find(model_key);
        const std::vector<TupleNumber> expected_ids = members == expected_buckets.end()
            ? std::vector<TupleNumber>{} : ids_from_set(members->second);
        const auto probe = literal_probe(target_layouts.at(index.program),
            native_pool[pool_slot], index.fields);
        const auto optimized_bucket = with_work([&](auto& work) {
          return indexed.bucket(index_id, probe, work);
        });
        const auto reference_bucket = reference.bucket(index_id, probe);
        verify(handle_ids(optimized_bucket, indexed.owner(), relation) == expected_ids &&
                   handle_ids(reference_bucket, reference.owner(), relation) == expected_ids,
               "input-pool hit/miss bucket IDs differed from the independent model");
      }
    }

    // Diagnostics are deliberately invoked outside every operational grant.
    indexed.check_invariants();
    reference.check_invariants();
  };

  for (std::size_t operation = 0; operation < 2'000; ++operation) {
    if (operation < program_fields.size()) {
      add_index(operation);
    } else if (operation == 9) {
      add_index(3);  // Reuse the exact immutable program token.
    } else if (operation == 10) {
      add_index(4);  // Independently constructed but field-equal program.
    } else if (operation < 43) {
      insert(operation - 11);
    } else if (operation == 43 || operation == 44) {
      erase_value(0);  // The second attempt is deliberately absent.
    } else if (operation == 45) {
      const auto id = find_model_row(1);
      verify(id.has_value(), "forced handle erase row was not inserted");
      erase_handle(*id);
    } else if (operation == 46) {
      verify(!model.stale_ids.empty(), "forced stale-handle row was not erased");
      erase_handle(model.stale_ids.back());
    } else if (operation == 47) {
      const auto id = model.active_programs.at(3);
      erase_key(id, 2);
    } else if (operation == 48) {
      drop_index(model.active_programs.at(5));
    } else if (operation == 49) {
      clear();
    } else if (operation == 50) {
      insert(0);
    } else if (operation == 51) {
      add_index(5);  // A dropped index receives a fresh monotonic identity.
    } else if (operation == 52) {
      erase_handle(model.by_value.at(model_pool.at(0)));
    } else if (operation >= 53) {
      const auto choice = bits.next() % 100;
      const auto pool_slot = static_cast<std::size_t>(bits.next() % model_pool.size());
      if (choice < 34) {
        insert(pool_slot);
      } else if (choice < 46) {
        erase_value(pool_slot);
      } else if (choice < 57) {
        if (!model.insertion_order.empty() && (bits.next() & 1U) == 0) {
          const auto active = model.insertion_order[bits.next() % model.insertion_order.size()];
          erase_handle(active);
        } else if (!model.stale_ids.empty()) {
          erase_handle(model.stale_ids[bits.next() % model.stale_ids.size()]);
        } else if (!model.insertion_order.empty()) {
          erase_handle(model.insertion_order.back());
        } else {
          erase_handle(model.next_tuple + 1'000'000);
        }
      } else if (choice < 68) {
        add_index(static_cast<std::size_t>(bits.next() % program_fields.size()));
      } else if (choice < 77) {
        if (!model.indexes.empty()) {
          auto it = model.indexes.begin();
          std::advance(it, static_cast<std::ptrdiff_t>(bits.next() % model.indexes.size()));
          drop_index(it->first);
        } else {
          drop_index(model.next_index + 10);
        }
      } else if (choice < 89) {
        if (!model.indexes.empty()) {
          auto it = model.indexes.begin();
          std::advance(it, static_cast<std::ptrdiff_t>(bits.next() % model.indexes.size()));
          erase_key(it->first, pool_slot);
        }
      } else if (choice < 92) {
        clear();
      } else {
        query(pool_slot);
      }
    }
    compare_all();
  }
}

}  // namespace

int main() {
  differential_model();
  std::cout << "S04 indexed table deterministic differential model completed";
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 1
  std::cout << " hash_profile=same_bucket\n";
#elif defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 2
  std::cout << " hash_profile=same_full_hash\n";
#else
  std::cout << " hash_profile=native\n";
#endif
}
