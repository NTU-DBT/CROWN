#include "crown/planner/difference.hpp"
#include "crown/api/error.hpp"
#include <limits>

namespace crown::planner::difference {
namespace {
struct Budget {
  std::uint64_t remaining, used = 0;
  void take() {
    if (!remaining) throw Error("difference_work_limit", "difference pair admission work grant exceeded");
    --remaining; ++used;
  }
};
void require(bool condition, const char* message) {
  if (!condition) throw Error("difference_admission", message);
}
} // namespace

struct Plan::Data {
  fallback::Plan left, right;
  Profile profile;
  std::uint64_t work;
};
const fallback::Plan& Plan::left() const & noexcept { return data_->left; }
const fallback::Plan& Plan::right() const & noexcept { return data_->right; }
const PhysicalPlan& Plan::source_only() const & noexcept { return data_->left.source_only(); }
const Profile& Plan::profile() const & noexcept { return data_->profile; }
std::uint64_t Plan::work() const noexcept { return data_->work; }

Estimates Plan::estimates(std::span<const std::uint64_t> tablecounts) const {
  require(tablecounts.size() == data_->left.originalcatalog().tables.size(),
          "difference estimates require one count per original source table");
  Estimates result;
  result.left = data_->left.estimates(tablecounts);
  result.right = data_->right.estimates(tablecounts);
  result.overflow = result.left.overflow || result.right.overflow;
  result.source_rows = result.left.source_rows;
  result.output_rows_upper = result.left.output_rows_upper;
  result.output_multiplicity_upper = data_->profile.mode == Mode::set_except
      ? result.left.output_rows_upper : result.left.assignments_upper;
  if (result.source_rows && result.output_rows_upper) {
    if (*result.output_rows_upper > std::numeric_limits<std::uint64_t>::max() - *result.source_rows)
      result.overflow = true;
    else result.state_rows_upper = *result.source_rows + *result.output_rows_upper;
  }
  return result;
}

Plan admit(const Catalog& catalog, const Query& leftquery, const Query& rightquery,
           Mode mode, const PhysicalOptions& options, const Limits& limits) {
  require(mode == Mode::set_except || mode == Mode::bag_except_all, "unknown difference mode");
  Budget budget{limits.work}; budget.take();
  try {
    auto left = fallback::admit(catalog, leftquery, options, limits.left);
    auto right = fallback::admit(catalog, rightquery, options, limits.right);
    const auto& lhs = left.query(); const auto& rhs = right.query();
    require(lhs.head.size() == rhs.head.size(), "difference operands require the same output arity");
    for (std::size_t i = 0; i < lhs.head.size(); ++i) {
      budget.take();
      require(lhs.variables[lhs.head[i].variable.value].type == rhs.variables[rhs.head[i].variable.value].type,
              "difference output positions require the same scalar type");
    }
    Profile profile; profile.mode = mode;
    if (mode == Mode::bag_except_all) profile.semantics = "exact_bag_except_all_physical_set_witness_counts";
    profile.left_class = left.profile().query_class; profile.right_class = right.profile().query_class;
    profile.left_reason = left.profile().reason; profile.right_reason = right.profile().reason;
    return Plan(std::make_shared<Plan::Data>(Plan::Data{std::move(left), std::move(right), profile, budget.used}));
  } catch (const Error& error) {
    if (error.code() == "difference_admission" || error.code() == "difference_work_limit") throw;
    if (error.code() == "fallback_work_limit" || error.code() == "resource_limit")
      throw Error("difference_work_limit", error.what());
    throw Error("difference_admission", error.what());
  }
}
} // namespace crown::planner::difference
