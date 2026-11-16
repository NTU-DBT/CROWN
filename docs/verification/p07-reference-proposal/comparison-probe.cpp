// Isolated proposal comparison; not registered in repository build/test targets.
#include "collector.hpp"
#include "../p07-generator-proposal/machine.hpp"
#include "../p07-key-proposal/key_machine.hpp"
#include "crown/io/document.hpp"
#include "crown/planner/verify.hpp"
#include "tree_oracle.hpp"

#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>

namespace {
using namespace crown;
namespace ap = planner::alternatives_proposal;

void require(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}

Document load(const char* name) {
  std::ifstream input(name);
  require(input.good(), "cannot read proposal query");
  return io::read_document(std::string{std::istreambuf_iterator<char>(input), {}});
}

std::string production_key(std::shared_ptr<const FreeConnexTree> tree) {
  auto budget = std::make_shared<ap::ContentBudget>();
  std::shared_ptr<const std::string> retained;
  {
    ap::StructuralKeyMachine key(std::move(tree), budget);
    for (std::uint64_t i = 0; i < 1'000'000; ++i) {
      const auto update = key.step({256});
      require(update.event != ap::KeyEvent::stopped, "key unexpectedly stopped");
      if (update.event == ap::KeyEvent::key_ready) {
        retained = key.key();
        const auto before = key.statistics().completed_steps;
        require(key.step({256}).event == ap::KeyEvent::key_ready &&
                    key.statistics().completed_steps == before && key.key() == retained,
                "key ready observation changed progress or ownership");
        break;
      }
    }
  }
  require(static_cast<bool>(retained), "key did not complete within probe guard");
  return *retained;
}

io::Json compare(const char* name, const Document& document, std::size_t height,
                 std::optional<std::size_t> expected_count) {
  validate(document.catalog, document.query);
  const auto reference = reference::collect_normal_form_plan_set(
      document.catalog, document.query, height);
  require(reference.exhausted && !reference.resource_limited,
          "reference family did not exhaust");
  std::set<std::string> reference_set;
  std::map<std::string, std::string> signature_to_key, key_to_signature;
  const auto pair = [&](const std::string& signature, const std::string& key) {
    const auto [forward, inserted_forward] = signature_to_key.emplace(signature, key);
    require(inserted_forward || forward->second == key,
            "same reference identity produced different proposal keys");
    const auto [backward, inserted_backward] = key_to_signature.emplace(key, signature);
    require(inserted_backward || backward->second == signature,
            "proposal key merged distinct reference identities");
  };
  for (const auto& plan : reference.plans) {
    require(planner::validate_tree(document.catalog, document.query, plan.representative).valid,
            "reference returned a P02-invalid tree");
    require(reference::normal_form_reference_signature(plan.representative) == plan.signature,
            "reference representative and signature disagree");
    reference_set.insert(plan.signature);
    pair(plan.signature, production_key(std::make_shared<const FreeConnexTree>(plan.representative)));
  }

  auto binding = std::make_shared<const planner::continuation_detail::BindingData>(
      planner::continuation_detail::BindingData{document.catalog, document.query});
  auto budget = std::make_shared<ap::ContentBudget>();
  ap::NormalFormGenerator generator(binding, height, budget);
  std::set<std::string> generated_set;
  std::shared_ptr<const FreeConnexTree> retained;
  std::string retained_signature;
  std::uint64_t drafts = 0, accepted = 0;
  bool exhausted = false;
  for (std::uint64_t i = 0; i < 10'000'000; ++i) {
    const auto update = generator.step({256});
    require(update.event != ap::GeneratorEvent::stopped, "generator unexpectedly stopped");
    if (update.event == ap::GeneratorEvent::exhausted) { exhausted = true; break; }
    if (update.event != ap::GeneratorEvent::draft_ready) continue;
    ++drafts;
    const auto draft = generator.draft();
    const auto before = generator.statistics().completed_steps;
    require(draft && generator.step({256}).event == ap::GeneratorEvent::draft_ready &&
                generator.statistics().completed_steps == before && generator.draft() == draft,
            "ready draft observation changed progress or ownership");
    const auto checked = planner::validate_tree(document.catalog, document.query, *draft);
    if (checked.valid) {
      require(checked.native_height == height, "generator accepted a different height");
      ++accepted;
      auto signature = reference::normal_form_reference_signature(*draft);
      generated_set.insert(signature);
      pair(signature, production_key(draft));
      if (!retained) { retained = draft; retained_signature = std::move(signature); }
    }
    generator.consume_draft();
  }
  require(exhausted, "generator did not exhaust within probe guard");
  require(generated_set == reference_set, "generator and independent reference sets differ");
  require(!expected_count || generated_set.size() == *expected_count,
          "unexpected complete small-family count");
  require(signature_to_key.size() == generated_set.size() &&
              key_to_signature.size() == generated_set.size(),
          "key/reference identity relation is not bijective");
  require(retained && reference::normal_form_reference_signature(*retained) == retained_signature,
          "retained generated draft changed after further enumeration");
  return {{"case", name}, {"height_filter", height}, {"drafts", drafts},
          {"p02_accepted_drafts", accepted}, {"distinct_plans", generated_set.size()},
          {"reference_work_units", reference.work_units},
          {"generator_steps", generator.statistics().completed_steps},
          {"both_exhausted", true}, {"signature_sets_equal", true},
          {"key_reference_bijection", true}, {"retained_handles_stable", true}};
}

Document scoped_document(const std::array<unsigned, 3>& scopes, unsigned head) {
  Document document;
  const auto used = scopes[0] | scopes[1] | scopes[2];
  std::array<std::optional<VariableId>, 2> variables;
  for (std::size_t i = 0; i != 2; ++i) {
    if ((used & (1U << i)) == 0) continue;
    variables[i] = VariableId{document.query.variables.size()};
    document.query.variables.push_back(Variable{"v" + std::to_string(i), ScalarType::string});
    if ((head & (1U << i)) != 0) {
      document.query.head.push_back(Output{*variables[i], "o" + std::to_string(i)});
    }
  }
  for (std::size_t occurrence = 0; occurrence != scopes.size(); ++occurrence) {
    const auto name = "R" + std::to_string(occurrence);
    Table table{name, {}};
    Atom atom{name, TableId{occurrence}, {}};
    for (std::size_t i = 0; i != 2; ++i) {
      if ((scopes[occurrence] & (1U << i)) == 0) continue;
      table.columns.push_back(Column{"c" + std::to_string(i), ScalarType::string});
      atom.terms.emplace_back(std::in_place_type<VariableId>, *variables[i]);
    }
    document.catalog.tables.push_back(std::move(table));
    document.query.atoms.push_back(std::move(atom));
  }
  return document;
}
}  // namespace

int main(int argc, char** argv) {
  try {
    require(argc == 3, "supply Boolean R/S/T and equal-scope self-join query files");
    const auto boolean = load(argv[1]), self_join = load(argv[2]);
    io::Json rows = io::Json::array();
    rows.push_back(compare("boolean_rst", boolean, 2, 3));
    rows.push_back(compare("equal_scope_self_join", self_join, 1, 4));
    Document empty;
    rows.push_back(compare("empty_body", empty, 0, 1));
    auto singleton = boolean;
    singleton.query.atoms.resize(1);
    singleton.query.variables.resize(1);
    rows.push_back(compare("singleton", singleton, 1, 1));
    Document nullary;
    nullary.catalog.tables.push_back(Table{"N", {}});
    nullary.query.atoms.push_back(Atom{"N", TableId{0}, {}});
    rows.push_back(compare("nullary_singleton", nullary, 1, 1));

    io::Json finite_rows = io::Json::array();
    for (unsigned first = 0; first != 4; ++first) {
      for (unsigned second = 0; second != 4; ++second) {
        for (unsigned third = 0; third != 4; ++third) {
          const auto used = first | second | third;
          for (unsigned head = 0; head != 4; ++head) {
            if ((head & used) != head) continue;
            const auto document = scoped_document({first, second, third}, head);
            const auto optimum = reference::exhaustive_minimum_tree(document.catalog, document.query);
            require(optimum.status == planner::OracleStatus::proven_minimum && optimum.minimum_height,
                    "frozen literal oracle did not supply a small-case minimum");
            const auto name = "scopes_" + std::to_string(first) + "_" +
                std::to_string(second) + "_" + std::to_string(third) + "_head_" + std::to_string(head);
            finite_rows.push_back(compare(name.c_str(), document, *optimum.minimum_height, {}));
          }
        }
      }
    }
    require(finite_rows.size() == 225, "finite three-atom family cardinality changed");

    const auto zero = reference::collect_normal_form_plan_set(
        boolean.catalog, boolean.query, 2, {0});
    require(!zero.exhausted && zero.resource_limited &&
                zero.stop == reference::NormalFormCollectionStop::work_limit,
            "zero reference work did not report an incomplete resource stop");
    auto four_atoms = self_join;
    four_atoms.query.atoms.push_back(four_atoms.query.atoms.front());
    four_atoms.query.atoms.back().occurrence = "fourth";
    validate(four_atoms.catalog, four_atoms.query);
    const auto native_cap = reference::collect_normal_form_plan_set(
        four_atoms.catalog, four_atoms.query, 1);
    require(!native_cap.exhausted && native_cap.resource_limited &&
                native_cap.stop == reference::NormalFormCollectionStop::native_occurrence_cap,
            "reference native cap did not report an incomplete resource stop");
    Document wide;
    Table table{"W", {}};
    Atom atom{"W", TableId{0}, {}};
    for (std::size_t i = 0; i != 4; ++i) {
      const auto name = "v" + std::to_string(i);
      wide.query.variables.push_back(Variable{name, ScalarType::string});
      table.columns.push_back(Column{name, ScalarType::string});
      atom.terms.emplace_back(std::in_place_type<VariableId>, VariableId{i});
    }
    wide.catalog.tables.push_back(std::move(table));
    wide.query.atoms.push_back(std::move(atom));
    validate(wide.catalog, wide.query);
    const auto variable_cap = reference::collect_normal_form_plan_set(wide.catalog, wide.query, 1);
    require(!variable_cap.exhausted && variable_cap.resource_limited &&
                variable_cap.stop == reference::NormalFormCollectionStop::active_variable_cap,
            "reference variable cap did not report an incomplete resource stop");
    std::cout << io::Json{{"proposal_only", true}, {"cases", std::move(rows)},
                         {"finite_three_atom_cases", std::move(finite_rows)},
                         {"zero_work_incomplete", true}, {"native_cap_incomplete", true},
                         {"variable_cap_incomplete", true}}.dump(2) << '\n';
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
