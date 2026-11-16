#include "index_scalar_work.hpp"

#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

using namespace crown;
using namespace crown::storage;
namespace detail = crown::storage::detail;

namespace {
void verify(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}
template <class Function>
void rejects(std::string_view code, Function&& function) {
  bool rejected = false;
  try { function(); }
  catch (const Error& error) { verify(error.code() == code, "wrong error code");rejected = true; }
  verify(rejected, "operation unexpectedly succeeded");
}

void scalar_boundaries() {
  TupleLayout layout(LayoutId{11}, {{ScalarType::int64}, {ScalarType::string},
      {ScalarType::boolean}, {ScalarType::date}, {ScalarType::decimal}});
  const std::string bytes{static_cast<char>(0), static_cast<char>(255), 'A'};
  const auto decimal = Decimal::parse("-0." + std::string(37, '0') + "1");
  verify(decimal.to_string().size() == 41, "Decimal formatter bound fixture differs");
  const auto tuple = layout.tuple(Row{std::numeric_limits<std::int64_t>::min(), bytes,
      true, Date::parse("0001-01-01"), decimal});
  // Eight row-framing bytes, then tagged payloads: 9 +12 +2 +9 +50.
  IndexWorkAllowance exact(IndexWork{.scalar_fields = 10, .scalar_bytes = 90});
  verify(detail::admitted_hash(tuple, exact) == tuple.hash() && exact.remaining() == IndexWork{},
         "native typed hash or exact admitted boundary changed");
  IndexWorkAllowance short_bytes(IndexWork{.scalar_fields = 10, .scalar_bytes = 89});
  rejects("storage_work_limit", [&] { static_cast<void>(detail::admitted_hash(tuple, short_bytes)); });
  IndexWorkAllowance short_fields(IndexWork{.scalar_fields = 9, .scalar_bytes = 90});
  rejects("storage_work_limit", [&] { static_cast<void>(detail::admitted_hash(tuple, short_fields)); });
  verify(std::get<std::string>(crown::storage::export_row(tuple.values())[1]) == bytes && std::get<Decimal>(crown::storage::export_row(tuple.values())[4]) == decimal,
         "failed hash admission changed immutable input");
  IndexWorkAllowance copy(IndexWork{.scalar_fields = 10, .scalar_bytes = 58});
  detail::admit_tuple_copy(tuple, copy);
  verify(copy.remaining() == IndexWork{}, "copy admission counts differ");
  IndexWorkAllowance equal(IndexWork{.scalar_fields = 20, .scalar_bytes = 116});
  verify(detail::admitted_equal(tuple, tuple, equal) && equal.remaining() == IndexWork{},
         "exact typed equality admission differs");
  TupleLayout reconstructed(LayoutId{11}, std::vector<Field>(layout.fields().begin(),layout.fields().end()));
  const auto foreign = reconstructed.tuple(tuple.values());
  IndexWorkAllowance zero(IndexWork{});
  verify(!detail::admitted_equal(tuple, foreign, zero) && zero.remaining() == IndexWork{},
         "equal descriptor incorrectly acquired layout-token identity");

  const std::vector<FieldId> slots{FieldId{1}, FieldId{4}, FieldId{0}, FieldId{1}};
  auto key_layout = projected_layout(LayoutId{12}, layout, slots);
  Projection projection(layout, key_layout, slots);
  IndexWorkAllowance projection_work(IndexWork{.scalar_fields = 8, .scalar_bytes = 52});
  const auto key = detail::admitted_projection(projection, tuple, projection_work);
  verify(projection_work.remaining() == IndexWork{} && key.layout().same_token(key_layout) &&
      key.values() == Row{bytes, decimal, std::numeric_limits<std::int64_t>::min(), bytes},
      "repeated/reordered projection values or charges differ");
  rejects("layout_mismatch", [&] { static_cast<void>(detail::admitted_projection(projection, foreign, zero)); });
  TupleLayout nullary(LayoutId{13}, {});Projection empty(layout, nullary, {});
  const auto empty_key = detail::admitted_projection(empty, tuple, zero);
  verify(empty_key.values().empty() && empty_key.layout().same_token(nullary), "nullary projection differs");
  IndexWorkAllowance empty_hash(IndexWork{.scalar_bytes = 8});
  verify(detail::admitted_hash(empty_key, empty_hash) == empty_key.hash() && empty_hash.remaining() == IndexWork{},
         "empty key hash framing differs");
}

void canonical_and_large_counters() {
  TupleLayout layout(LayoutId{21}, {{ScalarType::decimal}});
  const auto one = layout.tuple(Row{Decimal::parse("1")});
  const auto same = layout.tuple(Row{Decimal::parse("1.000")});
  IndexWorkAllowance equal(IndexWork{.scalar_fields = 4, .scalar_bytes = 76});
  verify(detail::admitted_equal(one, same, equal), "canonical Decimal aliases became distinct");
  const std::uint64_t above_double = (std::uint64_t{1} << 53U) + 117U;
  IndexWorkAllowance exact(IndexWork{.structural_steps = above_double});
  exact.admit(IndexWork{.structural_steps = 1});
  verify(exact.remaining().structural_steps == above_double - 1, "work counter lost integer precision");
  exact.admit(IndexWork{.structural_steps = above_double - 1});
  rejects("storage_work_limit", [&] { exact.admit(IndexWork{.structural_steps = 1}); });
  IndexWorkAllowance maximum(IndexWork{.structural_steps = std::numeric_limits<std::uint64_t>::max()});
  maximum.admit(IndexWork{.structural_steps = std::numeric_limits<std::uint64_t>::max()});
  verify(maximum.remaining() == IndexWork{}, "maximum finite allowance overflowed");
  // These are work-count checks. Actual support payload/membership differential
  // coverage remains a separate table/runtime acceptance requirement.
}
}  // namespace

int main() {
  scalar_boundaries();canonical_and_large_counters();
  std::cout << "S04 scalar draft: native framing, token admission and literal work boundaries passed\n";
}
