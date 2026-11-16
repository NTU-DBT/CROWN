#include "selection_detail.hpp"
#include <string_view>
#include <type_traits>

namespace crown::planner::selection::detail {
namespace {
// Private v1 tagged, length-framed bytes. Every append reserves its logical
// work/key/payload charge before string growth. No JSON or digest equality.
// Build deterministic versioned selection reproduction bytes. See docs/selection_binding.md.
template<class Text=std::string> class Encoder {
 public:
  Budget& budget;
  Text bytes;
  explicit Encoder(Budget& b, std::string_view domain,bool retained=false)
      :budget(b),bytes(buffer(b,retained)) { raw(domain); }
  // Select ordinary output or a receiving-account text allocator. See docs/query_memory.md.
  static Text buffer(Budget& b,bool retained) {
    if constexpr(std::is_same_v<Text,std::string>)return {};
    else return Text(resource::OwnerAllocator<char>(b.memory,
        retained?resource::MemoryPurpose::capture:resource::MemoryPurpose::scratch,selection_memory_owner));
  }
  // Append exact raw bytes after logical work/key/payload admission. See
  // docs/selection_accounting.md.
  void raw(std::string_view text) {
    const auto n = static_cast<std::uint64_t>(text.size());
    budget.keys(n); budget.bytes(n); bytes.append(text);
  }
  void byte(char value) { budget.keys(1); budget.bytes(1); bytes.push_back(value); }
  // Emit fixed eight-byte big-endian scalar payload. See docs/selection_binding.md.
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
  // Distinguish optional absence from a present zero/empty payload. See
  // docs/selection_binding.md.
  template<class T, class Function> void optional(const std::optional<T>& value, Function function) {
    byte('P'); byte(value ? '\1' : '\0'); if (value) function(*value);
  }
  // Preserve complete ordered collection multiplicity. See docs/selection_binding.md.
  template<class Range, class Function> void sequence(const Range& values, Function function) {
    count(values.size()); for (const auto& value : values) function(value);
  }
  template<class Range> void ids(const Range& values) { sequence(values, [&](const auto id) { u(id.value); }); }
  // Embed complete unchanged P07-v2 typed Catalog/Query binding. See
  // docs/selection_binding.md.
  template<class C,class Q> void cq(const C& catalog, const Q& query) {
    // Charge the nested component before the outer frame, as in v1. Keep its
    // native buffer alive through the append without an ordinary string mirror.
    if(budget.memory) {
      SelectionText nested(selection_allocator<char>(budget.memory));
      budget.borrowed([&](rd::Budget& b) {nested=rd::score_binding(catalog,query,b,b.memory);});
      record("candidate-binding-v2");text(nested);
    }else {
      std::string nested;
      budget.borrowed([&](rd::Budget& b) {nested=rd::binding(catalog,query,b);});
      record("candidate-binding-v2");text(nested);
    }
  }
  void catalog(const Catalog& value) { record("catalog-with-empty-query"); cq(value, Query{}); }
  void catalog(const program::Catalog& value) { record("catalog-with-empty-query"); cq(value, program::Query{}); }
  // Encode exact scalar kind and canonical payload for ordinary/native values. See
  // docs/selection_binding.md.
  template<class Scalar> void scalar(const Scalar& value) {
    record("value"); u(value.index());
    switch (value.index()) {
      case 0: s(std::get<std::int64_t>(value)); return;
      case 1: text(std::get<1>(value)); return;
      case 2: boolean(std::get<bool>(value)); return;
      case 3: s(std::get<Date>(value).epoch_days()); return;
      case 4: {
        budget.work(41); budget.bytes(41);
        const auto decimal=[&] {
          if constexpr(std::is_same_v<std::remove_cvref_t<decltype(std::get<4>(value))>,Decimal>)
            return storage::InlineDecimal::copy_of(std::get<4>(value));
          else return std::get<4>(value);
        }();
        std::array<char,storage::InlineDecimal::text_capacity> formatted{};
        const auto size=decimal.render(formatted);text({formatted.data(),size});
        return;
      }
      default: throw Failure{Stop::internal_error, Resource::none, {}, 0};
    }
  }
  template<class Scalar> void sql_value(const std::optional<Scalar>& value) { optional(value, [&](const auto& v) { scalar(v); }); }
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
  // Encode complete typed SQL binding source and expression program. See
  // docs/selection_binding.md.
  template<class Bound> void bound(const Bound& value) {
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
        else if constexpr (requires{node.value;}) { sql_value(node.value); }
        else if constexpr (std::is_same_v<T, frontend::BoundParameter>) { u(node.number); }
        else { enumeration(node.operation); ids(node.arguments); }
      }, x.node);
      optional(x.location, [&](auto n) { u(n); });
    });
    ids(value.predicates);
    sequence(value.outputs, [&](const auto& x) { text(x.name); u(x.expression.value); });
    bind_limits(value.limits); u(value.work);
  }
  // Encode full parameter-specialized normalized source. See docs/selection_binding.md.
  template<class Normalized> void normalized(const Normalized& value) {
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
      else scalar(std::get<1>(x.value).value);
    });
    normalize_limits(value.limits); u(value.work); u(value.schema_version);
  }
  // Encode complete supplied tree representation and claims. See docs/selection_binding.md.
  template<class Tree> void tree(const Tree& value) {
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
  // Bind complete physical policy, finite producer limits and optional indexed backend. See
  // docs/selection_binding.md.
  template<class Options> void options(const Options& value) {
    record("physical-options"); text(value.policy.arithmetic); text(value.policy.planner);
    text(value.policy.optimization); text(value.policy.cost_model);
    optional(value.limits.work_limit, [&](auto n) { u(n); });
    optional(value.limits.identity.work_limit, [&](auto n) { u(n); });
    if (value.indexed_storage) {
      record("indexed-storage-v1");text("indexed_chained_v1");text("insertion_first_live_key_v1");
      text("per_table_including_undo");text("operation_aggregate");
      const auto& cap=value.indexed_storage->per_table;const auto& work=value.indexed_storage->per_operation;
      u(cap.rows);u(cap.indices);u(cap.keys);u(cap.memberships);u(cap.nodes);u(cap.directory_slots);
      u(cap.arena_slots);u(cap.arena_pins);u(cap.journal_entries);
      u(work.structural_steps);u(work.scalar_fields);u(work.scalar_bytes);u(work.pointer_slots);u(work.link_actions);
    }
  }
  template<class C,class Q,class Physical,class Normalized,class Options>
  // Frame exact core, physical catalog, normalized program and options as one source. See
  // docs/selection_binding.md.
  void source(const C& c, const Q& q, const Physical& physical,
      const std::optional<Normalized>& program, const Options& opts) {
    record("physical-source"); cq(c, q); catalog(physical);
    optional(program, [&](const auto& p) { normalized(p); }); options(opts);
  }
  template<class Plan> void source(const Plan& p) {
    source(p.catalog(), p.query(), p.source_catalog(), p.normalized(), p.options());
    // Optional execution policy changes artifact reuse, not physical identity.
    // Interpreted plans retain their original source and cache bytes.
    if constexpr(requires{p.input_preparation_limits();}) {
      if(const auto limits=p.input_preparation_limits()) {
        record("input-execution-v1");text(p.input_execution_key());
        u(limits->work);u(limits->instructions);
      }
    }
  }
  // Derive expected direct or basis source from the admitted snapshot. See
  // docs/selection_binding.md.
  template<class SourceValue> void source(const CandidateSnapshot& snapshot, const SourceValue& value) {
    std::visit([&](const auto& input) {
      if constexpr(requires{input.options;}) {
        const auto binding=snapshot.original_proof().binding();
        source(binding.catalog(),binding.query(),binding.catalog(),std::optional<frontend::NormalizedSql>{},input.options);
      }else std::visit([&](const auto& plan){source(plan);},input.plan);
    },value);
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
  template<class RequestValue> void request(const RequestValue& value) {
    record("selection-request"); enumeration(value.policy); enumeration(value.fallback); enumeration(value.family);
    enumeration(value.layout); enumeration(value.indexes); u(value.constraint.index());
    std::visit([&](const auto& cap) {
      using T=std::remove_cvref_t<decltype(cap)>;
      if constexpr(std::is_same_v<T,TupleIndexSlotLimit> || std::is_same_v<T,CapturedTupleIndexSlotLimit>)text(cap.maximum);
      else require(std::is_same_v<T,std::monostate>);
    },value.constraint);
    limits(value.limits.aggregate);
    // An absent declaration preserves the original request bytes. Presence
    // adds an explicitly versioned domain and every source-bound rule field.
    if (value.update_patterns) {
      const auto& declaration = *value.update_patterns;
      record("update-pattern-admissibility;1");
      const auto& hash = declaration.source_sha256();
      text(std::string_view(hash.data(), hash.size()));
      u(declaration.source_tables());
      sequence(declaration.rules(), [&](const auto& rule) {
        u(rule.table.value);
        boolean(rule.insertion_only);
        u(rule.fifo_scope);
      });
    }
  }
  // Bind exact as-of ranking facts and capture configuration. See docs/selection_binding.md.
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
// Check original core binding and full source agreement before scoring/publication. See
// docs/selection_binding.md.
void source_binding(const CandidateSnapshot& snapshot, const Source& source,
    const std::optional<rank::Evidence>& evidence, Budget& budget) {
  if (const auto* basis = std::get_if<PhysicalBasis>(&source)) {
    const auto binding = snapshot.original_proof().binding();
    SelectionText original(selection_allocator<char>(budget.memory)),actual(selection_allocator<char>(budget.memory));
    budget.borrowed([&](rd::Budget& b) {
      original = rd::score_binding(binding.catalog(), binding.query(), b,b.memory);
      actual=std::visit([&](const auto& plan){return rd::score_binding(plan.catalog(),plan.query(),b,b.memory);},basis->plan);
    });
    require(equal_bytes(original, actual, budget), Stop::binding_mismatch);
  }
  Encoder<SelectionText> expected(budget, "CROWN-SELECTION-SOURCE;1;"); expected.source(snapshot, source);
  if (evidence) {
    Encoder<SelectionText> actual(budget, "CROWN-SELECTION-SOURCE;1;"); actual.source(evidence->plan());
    require(equal_bytes(expected.bytes, actual.bytes, budget), Stop::binding_mismatch);
  }
}
// Verify chosen compiled source and operator tree against the admitted candidate. See
// docs/selection_binding.md.
void compiled_binding(const CandidateSnapshot& snapshot, const Source& source,
    const MinimumHeightCandidate& candidate, const CompiledProgram& plan, Budget& budget) {
  Encoder<SelectionText> expected(budget, "CROWN-SELECTION-COMPILED-INPUT;1;");
  expected.source(snapshot, source);
  // Derive operator geometry from the admitted query, preserving the family tree.
  const FreeConnexTree empty;
  const auto& query=candidate.query();
  const auto& tree=query.contradiction && !query.atoms.empty()?empty:candidate.tree();
  expected.tree(tree);
  Encoder<SelectionText> actual(budget, "CROWN-SELECTION-COMPILED-INPUT;1;");
  actual.source(plan); actual.tree(plan.tree());
  require(equal_bytes(expected.bytes, actual.bytes, budget), Stop::binding_mismatch);
}
// Build the complete retained artifact-reuse key after fresh decision. See
// docs/selection_binding.md.
SelectionText cache_binding(const SelectionData& value, Origin origin, Budget& budget) {
  Encoder<SelectionText> out(budget, "CROWN-SELECTION-ARTIFACT;1;",true);
  out.record("implementation-domain"); out.u(1); out.u(2); out.u(1); out.u(1);
  const auto* direct=std::get_if<CapturedDirectCQ>(&value.source);
  const bool indexed=direct ? direct->options.indexed_storage.has_value() :
      std::visit([](const auto& plan){return plan.options().indexed_storage.has_value();},std::get<PhysicalBasis>(value.source).plan);
  out.text(indexed ? "crown-lower-v2" : "crown-lower-v1");out.u(indexed ? 2 : 1);out.u(indexed ? 2 : 1);
  out.u(2);out.text(indexed ? "indexed_chained_v1" : "reference_ordered_v1");
  const auto proof = value.snapshot.original_proof(); const auto binding = proof.binding();
  out.cq(binding.catalog(), binding.query()); out.u(proof.height()); out.context(value.snapshot.context());
  out.enumeration(value.snapshot.family()); out.boolean(value.snapshot.family_exhausted());
  const auto count = value.snapshot.candidate_count(); out.count(count);
  for (std::size_t i = 0; i < count; ++i) {
    const auto candidate = value.snapshot.candidate(i); require(candidate.has_value());
    out.text(candidate->structural_key()); out.u(candidate->height()); out.tree(candidate->tree());
  }
  out.record("explicit-source"); out.u(value.source.index()); out.source(value.snapshot, value.source);
  if (const auto* basis = std::get_if<PhysicalBasis>(&value.source)) std::visit([&](const auto& plan){out.tree(plan.tree());},basis->plan);
  out.request(value.request); out.record("decision"); out.enumeration(value.effective); out.u(value.fallback);
  out.u(value.selected); require(value.chosen.has_value()); out.text(value.chosen->structural_key()); out.tree(value.chosen->tree());
  out.sequence(value.decisions, [&](const auto& x) { out.u(x.candidate_index); out.enumeration(x.eligibility); });
  out.enumeration(origin); out.optional(value.evidence, [&](const auto& facts) { out.evidence(facts); });
  budget.sample();
  return std::move(out.bytes);
}
// Export diagnostic bytes for one exact Value. See docs/selection_binding.md.
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
