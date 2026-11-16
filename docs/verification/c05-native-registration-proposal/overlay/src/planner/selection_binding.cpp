#include "selection_detail.hpp"
#include <string_view>
#include <type_traits>

namespace crown::planner::selection::detail {
namespace {
// Private v1 tagged, length-framed bytes. Every append reserves its logical
// work/key/payload charge before string growth. No JSON or digest equality.
class Encoder {
 public:
  Budget& budget;
  std::string bytes;
  explicit Encoder(Budget& b, std::string_view domain) : budget(b) { raw(domain); }
  void raw(std::string_view text) {
    const auto n = static_cast<std::uint64_t>(text.size());
    budget.keys(n); budget.bytes(n); bytes.append(text);
  }
  void byte(char value) { budget.keys(1); budget.bytes(1); bytes.push_back(value); }
  void word(std::uint64_t value) {
    for (unsigned n = 0; n < 8; ++n) byte(static_cast<char>((value >> (56U - 8U * n)) & 255U));
  }
  void u(std::uint64_t value) { byte('U'); word(value); }
  void s(std::int64_t value) { byte('I'); word(static_cast<std::uint64_t>(value)); }
  template<class T> void enumeration(T value) { byte('E'); word(static_cast<std::uint64_t>(value)); }
  void boolean(bool value) { byte('B'); byte(value ? '\1' : '\0'); }
  void text(std::string_view value) { byte('S'); word(static_cast<std::uint64_t>(value.size())); raw(value); }
  void record(std::string_view value) { byte('R'); text(value); }
  void count(std::size_t value) { byte('A'); word(static_cast<std::uint64_t>(value)); }
  template<class T, class Function> void optional(const std::optional<T>& value, Function function) {
    byte('P'); byte(value ? '\1' : '\0'); if (value) function(*value);
  }
  template<class Range, class Function> void sequence(const Range& values, Function function) {
    count(values.size()); for (const auto& value : values) function(value);
  }
  template<class T> void ids(const std::vector<T>& values) { sequence(values, [&](const auto id) { u(id.value); }); }
  void cq(const Catalog& catalog, const Query& query) {
    std::string nested;
    budget.borrowed([&](rd::Budget& b) { nested = rd::binding(catalog, query, b); });
    record("candidate-binding-v2"); text(nested);
  }
  void catalog(const Catalog& value) { record("catalog-with-empty-query"); cq(value, Query{}); }
  void scalar(const Value& value) {
    record("value"); u(value.index());
    switch (value.index()) {
      case 0: s(std::get<std::int64_t>(value)); return;
      case 1: text(std::get<std::string>(value)); return;
      case 2: boolean(std::get<bool>(value)); return;
      case 3: s(std::get<Date>(value).epoch_days()); return;
      case 4: {
        budget.work(41); budget.bytes(41);
        text(std::get<Decimal>(value).to_string()); return;
      }
      default: throw Failure{Stop::internal_error, Resource::none, {}, 0};
    }
  }
  void sql_value(const frontend::SqlValue& value) { optional(value, [&](const Value& v) { scalar(v); }); }
  void sql_type(const frontend::SqlType& value) {
    record("sql-type"); enumeration(value.kind); boolean(value.nullable);
    optional(value.decimal, [&](const DecimalSpec& spec) { u(spec.precision); u(spec.scale); });
  }
  void bind_limits(const frontend::BindLimits& value) {
    record("bind-limits"); optional(value.work_limit, [&](auto n) { u(n); });
    u(value.expression_limit); u(value.recursion_limit);
  }
  void normalize_limits(const frontend::NormalizeLimits& value) {
    record("normalize-limits"); optional(value.work_limit, [&](auto n) { u(n); });
  }
  void bound(const frontend::BoundSql& value) {
    record("bound-sql"); text(value.source); catalog(value.catalog);
    sequence(value.parameters, [&](const auto& type) { sql_type(type); });
    enumeration(value.semantics); optional(value.inner_semantics, [&](auto x) { enumeration(x); });
    enumeration(value.wrapper); text(value.wrapper_alias);
    sequence(value.occurrences, [&](const auto& x) {
      record("bound-occurrence"); u(x.table.value); text(x.alias);
      sequence(x.column_names, [&](const auto& name) { text(name); });
      optional(x.location, [&](auto n) { u(n); }); boolean(x.include_descendants);
    });
    sequence(value.expressions, [&](const auto& x) {
      record("bound-expression"); sql_type(x.type); u(x.node.index());
      std::visit([&](const auto& node) {
        using T = std::decay_t<decltype(node)>;
        if constexpr (std::is_same_v<T, frontend::BoundColumn>) { u(node.occurrence.value); u(node.column.value); }
        else if constexpr (std::is_same_v<T, frontend::BoundLiteral>) { sql_value(node.value); }
        else if constexpr (std::is_same_v<T, frontend::BoundParameter>) { u(node.number); }
        else { enumeration(node.operation); ids(node.arguments); }
      }, x.node);
      optional(x.location, [&](auto n) { u(n); });
    });
    ids(value.predicates);
    sequence(value.outputs, [&](const auto& x) { text(x.name); u(x.expression.value); });
    bind_limits(value.limits); u(value.work);
  }
  void normalized(const frontend::NormalizedSql& value) {
    record("normalized-sql"); bound(value.binding);
    sequence(value.parameters, [&](const auto& v) { sql_value(v); });
    sequence(value.constants, [&](const auto& v) { sql_value(v); });
    cq(value.core_catalog, value.core);
    sequence(value.adapters, [&](const auto& x) {
      record("occurrence-adapter"); u(x.occurrence.value); u(x.base.value); ids(x.predicates); ids(x.non_null_columns);
      sequence(x.equal_columns, [&](const auto& pair) { u(pair.left.value); u(pair.right.value); });
      sequence(x.column_classes, [&](const auto& v) { optional(v, [&](auto id) { u(id.value); }); });
      sequence(x.projection, [&](const auto& p) { u(p.variable.value); u(p.expression.value); });
      ids(x.program);
      sequence(x.constant_columns, [&](const auto& c) { u(c.column.value); scalar(c.value); });
    });
    sequence(value.base_routes, [&](const auto& route) { ids(route); });
    sequence(value.outputs, [&](const auto& x) {
      record("normalized-output"); text(x.name); sql_type(x.type); u(x.value.index());
      if (const auto* core = std::get_if<frontend::CoreOutput>(&x.value)) u(core->column);
      else scalar(std::get<frontend::ConstantOutput>(x.value).value);
    });
    normalize_limits(value.limits); u(value.work); u(value.schema_version);
  }
  void tree(const FreeConnexTree& value) {
    record("raw-tree"); optional(value.root, [&](auto id) { u(id.value); });
    sequence(value.nodes, [&](const auto& node) {
      record("raw-node"); text(node.id); enumeration(node.kind);
      sequence(node.scope, [&](auto id) { u(id.value); }); ids(node.children);
      optional(node.occurrence, [&](auto id) { u(id); });
      optional(node.claimed_separator, [&](const auto& set) { sequence(set, [&](auto id) { u(id.value); }); });
    });
    optional(value.claimed_connex, [&](const auto& nodes) { ids(nodes); });
    optional(value.claimed_native_height, [&](auto n) { u(n); });
  }
  void options(const PhysicalOptions& value) {
    record("physical-options"); text(value.policy.arithmetic); text(value.policy.planner);
    text(value.policy.optimization); text(value.policy.cost_model);
    optional(value.limits.work_limit, [&](auto n) { u(n); });
    optional(value.limits.identity.work_limit, [&](auto n) { u(n); });
  }
  void source(const Catalog& c, const Query& q, const Catalog& physical,
      const std::optional<frontend::NormalizedSql>& program, const PhysicalOptions& opts) {
    record("physical-source"); cq(c, q); catalog(physical);
    optional(program, [&](const auto& p) { normalized(p); }); options(opts);
  }
  void source(const PhysicalPlan& p) { source(p.catalog(), p.query(), p.source_catalog(), p.normalized(), p.options()); }
  void source(const CandidateSnapshot& snapshot, const Source& value) {
    if (const auto* direct = std::get_if<DirectCQ>(&value)) {
      const auto binding = snapshot.original_proof().binding();
      source(binding.catalog(), binding.query(), binding.catalog(), {}, direct->options);
    } else source(std::get<PhysicalBasis>(value).plan);
  }
  void context(const CandidateContext& value) {
    record("candidate-context"); enumeration(value.updates); text(value.arithmetic); text(value.planner);
    text(value.optimization); text(value.cost_model); text(value.canonicalization);
  }
  void limits(const rank::Limits& value) {
    record("ranking-limits"); u(value.work); u(value.cells); u(value.binding_key_bytes); u(value.payload_bytes);
    u(value.lowering_work); u(value.identity_work); u(value.binding_replay_work); u(value.normalization_work);
    u(value.candidates); u(value.score_bits);
    optional(value.active_time, [&](auto time) { s(time.count()); });
  }
  void request(const Request& value) {
    record("selection-request"); enumeration(value.policy); enumeration(value.fallback); enumeration(value.family);
    enumeration(value.layout); enumeration(value.indexes); u(value.constraint.index());
    if (const auto* cap = std::get_if<TupleIndexSlotLimit>(&value.constraint)) text(cap->maximum);
    else require(std::holds_alternative<std::monostate>(value.constraint));
    limits(value.limits.aggregate);
  }
  void evidence(const rank::Evidence& value) {
    record("ranking-evidence"); const auto& id = value.identity();
    u(id.owner); u(id.epoch); u(id.interval_start); u(id.reset); u(id.configuration); u(id.segment); u(id.format);
    u(id.collection_mode); u(id.max_cells); u(id.period); u(id.offset); u(id.detail_budget);
    boolean(id.modes.delta_owner); u(id.modes.requested_mode); u(id.modes.resolved_mode);
    u(id.modes.requested_completion); u(id.modes.resolved_completion); u(id.modes.live_maintenance); u(id.modes.view);
    boolean(id.pending); boolean(id.reset_saturated); boolean(id.configuration_saturated); boolean(id.segment_saturated);
    sequence(value.weights(), [&](const auto& x) { u(x.table.value); u(x.inserts); u(x.erases); u(x.changed); u(x.noop); });
    sequence(value.sources(), [&](const auto& x) { u(x.table.value); u(x.rows); });
    sequence(value.source_observations(), [&](const auto& x) {
      u(x.table.value); enumeration(x.state); optional(x.cardinality, [&](auto n) { u(n); });
    });
    u(value.denominator()); u(value.depth_reasons()); u(value.memory_reasons());
    const auto& a = value.capture_accounting(); record("capture-configuration"); limits(a.processing_limits);
    enumeration(a.state); boolean(a.state_requested); u(a.requested_components); u(a.returned_components);
    u(a.state_work_limit); u(a.state_rows_limit); u(a.state_keys_limit); u(a.state_bytes_limit);
    u(a.state_projection_width); u(a.state_heavy_keys); u(a.snapshot_descriptors); u(a.snapshot_cells);
  }
};
}
void source_binding(const CandidateSnapshot& snapshot, const Source& source,
    const std::optional<rank::Evidence>& evidence, Budget& budget) {
  if (const auto* basis = std::get_if<PhysicalBasis>(&source)) {
    const auto binding = snapshot.original_proof().binding();
    std::string original, actual;
    budget.borrowed([&](rd::Budget& b) {
      original = rd::binding(binding.catalog(), binding.query(), b);
      actual = rd::binding(basis->plan.catalog(), basis->plan.query(), b);
    });
    require(equal_bytes(original, actual, budget), Stop::binding_mismatch);
  }
  Encoder expected(budget, "CROWN-SELECTION-SOURCE;1;"); expected.source(snapshot, source);
  if (evidence) {
    Encoder actual(budget, "CROWN-SELECTION-SOURCE;1;"); actual.source(evidence->plan());
    require(equal_bytes(expected.bytes, actual.bytes, budget), Stop::binding_mismatch);
  }
}
void compiled_binding(const CandidateSnapshot& snapshot, const Source& source,
    const MinimumHeightCandidate& candidate, const PhysicalPlan& plan, Budget& budget) {
  Encoder expected(budget, "CROWN-SELECTION-COMPILED-INPUT;1;");
  expected.source(snapshot, source); expected.tree(candidate.tree());
  Encoder actual(budget, "CROWN-SELECTION-COMPILED-INPUT;1;");
  actual.source(plan); actual.tree(plan.tree());
  require(equal_bytes(expected.bytes, actual.bytes, budget), Stop::binding_mismatch);
}
std::string cache_binding(const SelectionData& value, Origin origin, Budget& budget) {
  Encoder out(budget, "CROWN-SELECTION-ARTIFACT;1;");
  out.record("implementation-domain"); out.u(1); out.u(2); out.u(1); out.u(1);
  out.text("crown-lower-v1"); out.u(1); out.u(1); out.u(2); out.text("reference_ordered_v1");
  const auto proof = value.snapshot.original_proof(); const auto binding = proof.binding();
  out.cq(binding.catalog(), binding.query()); out.u(proof.height()); out.context(value.snapshot.context());
  out.enumeration(value.snapshot.family()); out.boolean(value.snapshot.family_exhausted());
  const auto count = value.snapshot.candidate_count(); out.count(count);
  for (std::size_t i = 0; i < count; ++i) {
    const auto candidate = value.snapshot.candidate(i); require(candidate.has_value());
    out.text(candidate->structural_key()); out.u(candidate->height()); out.tree(candidate->tree());
  }
  out.record("explicit-source"); out.u(value.source.index()); out.source(value.snapshot, value.source);
  if (const auto* basis = std::get_if<PhysicalBasis>(&value.source)) out.tree(basis->plan.tree());
  out.request(value.request); out.record("decision"); out.enumeration(value.effective); out.u(value.fallback);
  out.u(value.selected); require(value.chosen.has_value()); out.text(value.chosen->structural_key()); out.tree(value.chosen->tree());
  out.sequence(value.decisions, [&](const auto& x) { out.u(x.candidate_index); out.enumeration(x.eligibility); });
  out.enumeration(origin); out.optional(value.evidence, [&](const auto& facts) { out.evidence(facts); });
  budget.sample();
  return std::move(out.bytes);
}
std::string scalar_binding_record(const Value& value, Budget& budget) {
  Encoder out(budget, "CROWN-SELECTION-SCALAR;1;"); out.scalar(value); return std::move(out.bytes);
}
std::string tree_binding_record(const FreeConnexTree& value, Budget& budget) {
  Encoder out(budget, "CROWN-SELECTION-TREE;1;"); out.tree(value); return std::move(out.bytes);
}
std::string program_binding_record(const frontend::NormalizedSql& value, Budget& budget) {
  Encoder out(budget, "CROWN-SELECTION-PROGRAM;1;"); out.normalized(value); return std::move(out.bytes);
}
std::string core_binding_record(const Catalog& catalog, const Query& query, Budget& budget) {
  Encoder out(budget, "CROWN-SELECTION-CORE;1;"); out.cq(catalog, query); return std::move(out.bytes);
}
} // namespace crown::planner::selection::detail
