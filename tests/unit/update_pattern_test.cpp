#include "update_pattern_fixture.hpp"
#include "crown/planner/update_pattern.hpp"
#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include <array>
#include <iostream>

namespace {
using namespace crown;
using c02_test::check;
namespace ip = crown::patterns;
namespace pp = planner::patterns;

// Build genuine P02/P07 handles; fixture expectations never create authority.
CompiledProgram compile(const c02_test::Fixture& fixture,
                        const planner::CandidateSnapshot& candidates) {
  return CompiledProgram::standalone(planner::lower_tree(
      fixture.catalog, fixture.query, candidates.candidate(0)->tree()));
}

template<class Function> void rejects(Function function, ip::Fault expected) {
  bool rejected = false;
  try { function(); }
  catch (const ip::Failure& failure) { rejected = failure.fault() == expected; }
  check(rejected, "declaration accepted an invalid shape or insufficient grant");
}

// Capture canonical table order and explicit group membership without merging
// unrelated FIFO scopes. Logical grants and allocator limits are independent.
void declaration_contract(const CompiledProgram& source) {
  const auto account = resource::MemoryAccount::create(1 << 20);
  const auto baseline = account.statistics().current;
  const std::array rules{ip::TableRule{TableId{2}, false, UINT64_MAX},
      ip::TableRule{TableId{0}, true, 0}, ip::TableRule{TableId{1}, false, UINT64_MAX}};
  {
    const auto declaration = ip::Declaration::capture(account, source, rules);
    check(declaration.matches(source) && declaration.constrained(),
          "declaration lost its source or explicit scope");
    check(declaration.rules()[0].table == TableId{0} &&
          declaration.find(TableId{1})->fifo_scope == UINT64_MAX &&
          declaration.find(TableId{2})->fifo_scope == UINT64_MAX &&
          declaration.find(TableId{3}) == nullptr, "canonical rule lookup changed");
    const auto usage = declaration.captured_usage();
    ip::Limits exact{usage.work, usage.cells, usage.payload_bytes};
    check(ip::Declaration::capture(account, source, rules, exact).captured_usage() == usage,
          "exact declaration grant was not reproducible");
    for (unsigned dimension = 0; dimension < 3; ++dimension) {
      auto low = exact;
      if (dimension == 0) --low.work;
      if (dimension == 1) --low.cells;
      if (dimension == 2) --low.payload_bytes;
      const auto before = account.statistics().current;
      rejects([&] { static_cast<void>(ip::Declaration::capture(account, source, rules, low)); },
          dimension == 0 ? ip::Fault::work_limit :
          dimension == 1 ? ip::Fault::cell_limit : ip::Fault::byte_limit);
      check(account.statistics().current == before, "failed capture retained partial storage");
    }
    auto record = declaration.export_record();
    check(ip::Declaration::import(account, record).export_record().rules == record.rules,
          "declaration DTO round trip changed the rules");
    record.source_sha256[0] = record.source_sha256[0] == '0' ? '1' : '0';
    check(!ip::Declaration::import(account, record).matches(source),
          "shape-valid imported hash gained source authority");
    record.source_sha256[0] = 'G';
    rejects([&] { static_cast<void>(ip::Declaration::import(account, record)); }, ip::Fault::invalid_declaration);
    record = declaration.export_record(); record.rules[1].table = record.rules[0].table;
    rejects([&] { static_cast<void>(ip::Declaration::import(account, record)); }, ip::Fault::invalid_declaration);
    record = declaration.export_record(); record.rules[0].table = TableId{record.source_tables};
    rejects([&] { static_cast<void>(ip::Declaration::import(account, record)); }, ip::Fault::invalid_declaration);
    const auto receiving = resource::MemoryAccount::create(1 << 20);
    const auto before = receiving.statistics().current;
    {
      const auto copy = ip::Declaration::copy_of(receiving, declaration);
      check(copy.matches(source) && copy.captured_usage() == declaration.copy_usage() &&
            receiving.statistics().current.requested_bytes > before.requested_bytes,
            "declaration copy escaped the receiving account");
    }
    check(receiving.statistics().current == before, "declaration copy retained a dead receiving allocation");
  }
  check(account.statistics().current == baseline, "declaration teardown leaked accounted storage");
  const auto empty = ip::Declaration::capture(account, source, {});
  check(!empty.constrained() && empty.rules().empty(),
        "empty declaration invented an update constraint");
  const auto tiny = resource::MemoryAccount::create(resource::MemoryAccount::control_bytes());
  bool failed = false;
  try { static_cast<void>(ip::Declaration::capture(tiny, source, rules)); }
  catch (const resource::MemoryFailure&) { failed = true; }
  check(failed && tiny.statistics().current.allocations == 1, "capture bypassed its actual query cap");
}

// An independently known three-member family separates a joint FIFO promise
// from per-table FIFO and makes the child-only insertion condition observable.
void height_two_contract(const c02_test::Fixture& fixture,
                         const planner::CandidateSnapshot& candidates,
                         const CompiledProgram& source) {
  const auto account = resource::MemoryAccount::create(8 << 20);
  const auto count_cases = [&](std::span<const ip::TableRule> rules, pp::SufficientCase expected) {
    const auto declaration = ip::Declaration::capture(account, source, rules);
    unsigned count = 0;
    for (std::size_t index = 0; index < candidates.candidate_count(); ++index) {
      const auto result = pp::analyse(account, source, *candidates.candidate(index), declaration);
      check(result.stop == planner::ranking::Stop::complete && result.analysis.has_value(),
            "genuine source/candidate analysis failed");
      check(result.analysis->candidate.structural_key() == candidates.candidate(index)->structural_key() &&
            result.analysis->declaration.matches(source) &&
            result.analysis->declaration.export_record().rules == declaration.export_record().rules,
            "retained analysis lost its source/candidate/declaration context");
      const auto transfer = expected == pp::SufficientCase::insertion_only ?
          pp::Transfer::checked_monotone_source : pp::Transfer::checked_typed_cq;
      check(result.analysis->height == 2 && result.analysis->transfer == transfer,
            "analysis changed height authority or transfer gate");
      count += result.analysis->sufficient == expected;
    }
    return count;
  };
  const std::array joint{ip::TableRule{TableId{0}, false, 17},
      ip::TableRule{TableId{1}, false, 17}, ip::TableRule{TableId{2}, false, 17}};
  check(count_cases(joint, pp::SufficientCase::height_two_edges) == 3,
        "explicit joint FIFO did not cover every native edge");
  auto separate = joint; separate[1].fifo_scope = 18; separate[2].fifo_scope = 19;
  check(count_cases(separate, pp::SufficientCase::unknown) == 3,
        "per-table FIFO was promoted to joint FIFO");
  const std::array insert_child{ip::TableRule{TableId{2}, true, 0}};
  check(count_cases(insert_child, pp::SufficientCase::height_two_edges) == 1,
        "insertion-only child did not distinguish the compatible topology");
  auto all_insert = joint;
  for (auto& rule : all_insert) rule.insertion_only = true;
  check(count_cases(all_insert, pp::SufficientCase::insertion_only) == 3,
        "all-insertion sufficient case was not recognized");
  const auto declaration = ip::Declaration::capture(account, source, joint);
  const auto candidate = *candidates.candidate(0);
  const auto before_constructor = account.statistics().current;
  const pp::Analysis unanalysed(account, candidate, declaration);
  check(unanalysed.transfer == pp::Transfer::not_checked &&
        unanalysed.sufficient == pp::SufficientCase::unknown && unanalysed.edges.empty() &&
        account.statistics().current == before_constructor,
        "raw report construction allocated or claimed a completed transfer");
  const auto measured = pp::analyse(account, source, candidate, declaration);
  auto limits = planner::ranking::Limits{};
  limits.work = measured.usage.work; limits.cells = measured.usage.cells;
  limits.payload_bytes = measured.usage.payload_bytes;
  limits.binding_key_bytes = measured.usage.binding_key_bytes;
  check(pp::analyse(account, source, candidate, declaration, limits).stop == planner::ranking::Stop::complete,
        "exact analysis grant failed");
  --limits.work;
  const auto low = pp::analyse(account, source, candidate, declaration, limits);
  check(low.stop == planner::ranking::Stop::work_limit && !low.analysis,
        "partial analysis escaped a failed grant");
  auto changed = fixture; changed.query.variables[0].name += "_foreign";
  const auto foreign = CompiledProgram::standalone(planner::lower_tree(
      changed.catalog, changed.query, candidate.tree()));
  check(pp::analyse(account, foreign, candidate, declaration).stop == planner::ranking::Stop::binding_mismatch,
        "foreign source reused a declaration");
  const auto foreign_declaration = ip::Declaration::capture(account, foreign, joint);
  check(pp::analyse(account, foreign, candidate, foreign_declaration).stop == planner::ranking::Stop::binding_mismatch,
        "same-shaped foreign candidate passed the full typed binding comparison");
}

// Arbitrary height-one maintenance needs only bounded occurrence fanout;
// projection and aliases need no FIFO transfer. Nullable direct input remains
// outside compiler admission, before a pattern analysis can be requested.
void transfer_contract() {
  const auto account = resource::MemoryAccount::create(8 << 20);
  for (unsigned variant = 0; variant < 5; ++variant) {
    c02_test::Fixture fixture;
    fixture.catalog.tables = {{"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}};
    fixture.query.variables = {{"x", ScalarType::int64}};
    fixture.query.atoms = {{"r", TableId{0}, {VariableId{0}, VariableId{0}}}};
    if (variant == 1) fixture.query.atoms[0].terms[1] = Value{std::int64_t{42}};
    if (variant == 2) fixture.query.atoms[0].terms[1] = IgnoredColumn{};
    if (variant == 3) fixture.catalog.tables[0].columns[1].nullable = true;
    if (variant == 4) fixture.query.atoms.push_back({"again", TableId{0}, {VariableId{0}, VariableId{0}}});
    if (variant == 3) {
      bool rejected = false;
      try { static_cast<void>(c02_test::candidates(fixture, 1, 0)); }
      catch (const Error& error) { rejected = error.code() == "unsupported_nullability"; }
      check(rejected, "nullable direct CQ bypassed the existing compiler admission");
      continue;
    }
    const auto candidates = c02_test::candidates(fixture, 1, 0);
    const auto source = compile(fixture, candidates);
    const auto declaration = ip::Declaration::capture(account, source, {});
    const auto result = pp::analyse(account, source, *candidates.candidate(0), declaration);
    check(result.stop == planner::ranking::Stop::complete && result.analysis.has_value(), "transfer fixture analysis failed");
    check(result.analysis->sufficient == pp::SufficientCase::height_one &&
        result.analysis->transfer == pp::Transfer::checked_event_mapping,
        "height-one occurrence mapping was unnecessarily restricted");
  }
}
// The general mixed-pattern characterization remains open. Use a genuine
// checked height-three witness and retain only its first candidate, without
// pretending that a finite prefix exhausted every native tree.
void taller_contract() {
  const auto fixture = pattern_test::height_three_fixture();
  const auto family = pattern_test::height_three_family(fixture);
  const auto candidate = *family.candidate(0);
  const auto source = CompiledProgram::standalone(planner::lower_tree(fixture.catalog, fixture.query, candidate.tree()));
  std::vector<ip::TableRule> rules;
  for (std::size_t t = 0; t < fixture.catalog.tables.size(); ++t) rules.push_back({TableId{t}, false, 1});
  const auto declaration = ip::Declaration::capture(source.account(), source, rules);
  const auto result = pp::analyse(source.account(), source, candidate, declaration);
  check(result.stop == planner::ranking::Stop::complete &&
        result.analysis->sufficient == pp::SufficientCase::unknown && result.analysis->height == 3,
        "height-three mixed case escaped the conservative boundary");
  for (auto& rule : rules) rule.insertion_only = true;
  const auto insertions = ip::Declaration::capture(source.account(), source, rules);
  check(pp::analyse(source.account(), source, candidate, insertions).analysis->sufficient == pp::SufficientCase::insertion_only,
        "all-insertion sufficient case unnecessarily depended on height two");
  // Make one first-native branch arbitrary; its strict descendants remain
  // insertion-only. This is a genuinely taller mixed
  // case, rather than the already accepted all-insertion case.
  std::vector<NodeId> order{*candidate.tree().root};
  TableId first_native{};bool found=false;
  for(std::size_t i=0;i<order.size() && !found;++i) {
    const auto& node=candidate.tree().nodes[order[i].value];
    if(node.kind==NodeKind::native){first_native=fixture.query.atoms[*node.occurrence].table;found=true;}
    else order.insert(order.end(),node.children.begin(),node.children.end());
  }
  check(found,"taller fixture has no first native node");rules[first_native.value].insertion_only=false;
  const auto mixed=ip::Declaration::capture(source.account(),source,rules);
  const auto proved=pp::analyse(source.account(),source,candidate,mixed);
  check(proved.stop==planner::ranking::Stop::complete && proved.analysis->sufficient==pp::SufficientCase::subtree_edges &&
      std::any_of(proved.analysis->edges.begin(),proved.analysis->edges.end(),[](const auto& edge){
        return edge.basis==pp::EdgeBasis::subtree_insertion_only;}),"monotone taller subtree was not recognized");
}

// Constant routes need no maintained join. SQL all-insertion and arbitrary
// height-one cases use the admitted source event mapping, not FIFO transfer.
void route_contract() {
  const auto account = resource::MemoryAccount::create(8 << 20);
  for (const bool contradiction : {false, true}) {
    c02_test::Fixture fixture; fixture.query.contradiction = contradiction;
    const auto candidates = c02_test::candidates(fixture, 0, 0);
    const auto source = compile(fixture, candidates);
    const auto declaration = ip::Declaration::capture(account, source, {});
    const auto result = pp::analyse(account, source, *candidates.candidate(0), declaration);
    check(result.stop == planner::ranking::Stop::complete &&
          result.analysis->sufficient == pp::SufficientCase::constant_result &&
          result.analysis->transfer == pp::Transfer::not_required, "constant route claimed an unnecessary source transfer");
  }
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64}}}}};
  const auto bound = frontend::bind_sql("SELECT DISTINCT x FROM r", catalog);
  check(std::holds_alternative<frontend::BoundSql>(bound), "SQL transfer fixture did not bind");
  const auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized), "SQL transfer fixture did not normalize");
  const auto& program = std::get<frontend::NormalizedSql>(normalized);
  const auto candidates = c02_test::candidates({program.core_catalog, program.core, {}}, 1, 0);
  const auto source = CompiledProgram::standalone(planner::lower_normalized(program, candidates.candidate(0)->tree()));
  const std::array rules{ip::TableRule{TableId{0}, true, 1}};
  const auto declaration = ip::Declaration::capture(account, source, rules);
  const auto result = pp::analyse(account, source, *candidates.candidate(0), declaration);
  check(result.stop == planner::ranking::Stop::complete && result.analysis->sufficient == pp::SufficientCase::insertion_only &&
        result.analysis->transfer == pp::Transfer::checked_monotone_source, "SQL monotone transfer was not recognized");
  const auto unrestricted=ip::Declaration::capture(account,source,{});
  const auto arbitrary=pp::analyse(account,source,*candidates.candidate(0),unrestricted);
  check(arbitrary.analysis->sufficient==pp::SufficientCase::height_one &&
      arbitrary.analysis->transfer==pp::Transfer::checked_event_mapping,"SQL height-one arbitrary transfer failed");
}

}

int main() {
  try {
    const auto fixture = c02_test::fixture();
    const auto candidates = c02_test::candidates(fixture);
    const auto source = compile(fixture, candidates);
    declaration_contract(source);
    height_two_contract(fixture, candidates, source);
    transfer_contract();
    taller_contract();
    route_contract();
    std::cout << "update-pattern declaration and conditional analysis contracts passed\n";
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n'; return 1;
  }
}
