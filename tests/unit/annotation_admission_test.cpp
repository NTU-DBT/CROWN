#include "crown/annotations/policy.hpp"
#include "crown/io/physical.hpp"
#include "crown/planner/lower.hpp"
#include <iostream>
#include <stdexcept>

namespace {
using namespace crown;
template<class F> void rejects(F action, std::string_view code) {
  try { action(); }
  catch (const Error& error) {
    if (error.code() != code) throw std::runtime_error("wrong backend admission error: " + error.code());
    return;
  }
  throw std::runtime_error("unsupported annotation selected a set backend");
}
void run() {
  const Catalog catalog{1, {{"R", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}}, {{"r", TableId{0}, {VariableId{0}}}}, {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0}, {{"r", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  for (const bool indexed : {false, true}) {
    PhysicalOptions options;
    if (indexed) options.indexed_storage = storage::IndexedBackendSpec{};
    const auto plan = planner::lower_tree(catalog, query, tree, options);
    if (plan.guarantee().semantics != "exact_set" || plan.guarantee().arithmetic != "exact-nonnull-v1")
      throw std::runtime_error("set guarantee changed");
    for (const auto policy : {annotations::MultiplicityPolicy::name, annotations::IntegerPolicy::name,
                              annotations::DecimalPolicy::name, std::string_view("floating-point"),
                              std::string_view("general-semiring-v1"), std::string_view("")}) {
      options.policy.arithmetic = policy;
      rejects([&] { static_cast<void>(planner::lower_tree(catalog, query, tree, options)); }, "invalid_policy");
      rejects([&] { static_cast<void>(io::query_identity(catalog, query, options.policy)); }, "invalid_policy");
      const auto encoded = io::write_physical_options(options).dump();
      rejects([&] { static_cast<void>(io::read_physical_options(encoded)); }, "invalid_policy");
    }
  }
}
}  // namespace
int main() {
  try { run(); std::cout << "Both physical backends reject unsupported annotation profiles\n"; }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
