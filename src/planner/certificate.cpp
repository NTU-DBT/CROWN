#include "continuation_machine.hpp"

#include <algorithm>
#include <map>
#include <utility>

namespace crown::planner::continuation_detail {
namespace {
// Groups retain input-binding occurrence indices in sorted order for independent ports and partition
// checks. See docs/planner_proofs.md, lower-bound evidence.
using Group = std::vector<std::size_t>;
// Replay keys independently retain both context flags; v2 canonicalizes only equal
// complete-scope orbits. See docs/planner_proofs.md, P04 symmetry.
struct ReplayState {
  Group occurrences;
  bool generalized = false;
  bool reachable = false;
  // Include occurrence order and both flags in proof-key equality. See
  // docs/planner_proofs.md, lower-bound evidence.
  auto operator<=>(const ReplayState&) const = default;
};
// Order provided and verified keys by independent state contents. See docs/planner_proofs.md,
// lower-bound evidence.
struct StateLess {
  // Borrow immutable replay keys for content comparison; duplicate ownership does not create
  // a distinct claim. See docs/planner_proofs.md, lower-bound evidence.
  bool operator()(const std::shared_ptr<const ReplayState>& a,
                  const std::shared_ptr<const ReplayState>& b) const noexcept {
    return *a < *b;
  }
};
// Cache only complete ports derived from checker scopes, with the owning value retaining its
// stable member key. See docs/planner_proofs.md, P06 authority.
struct ReplayPorts {
  // The cache owns this key through its shared value. Its address and contents
  // remain stable after publication; lookups may use any actual member group.
  Group members;
  VariableSet variables, boundary, exclusive_head, outside;
};
// Compare pointed-to member contents while cached ports retain their own key storage. See
// docs/planner_proofs.md, P06 authority.
struct GroupLess {
  // Equivalent actual member vectors hit the same independently derived ports record. See
  // docs/planner_proofs.md, P06 authority.
  bool operator()(const Group* a, const Group* b) const noexcept { return *a < *b; }
};
// All potentially allocating edits precede their cursor increments. Jobs live
// at stable addresses, so a suspended child's input can refer to its parent.
// Keep stage-specific scratch at stable addresses and commit cursor progress after allocating
// edits. See docs/planner_continuations.md, grants.
struct ReplayJob {
  // Choose a saved independent replay protocol; kinds do not share producer enumeration
  // state. See docs/planner_continuations.md, grants.
  enum Kind { key, ports, components, prove, enumerate, option, child } kind;
  // Initialize an inert replay frame; the scheduling caller supplies the kind-specific input
  // before execution. See docs/planner_continuations.md, grants.
  explicit ReplayJob(Kind k) : kind(k) {}
  unsigned stage = 0;
  std::size_t a = 0, b = 0, c = 0, d = 0, maximum = 0;
  const Group* input = nullptr;
  const LowerBoundEntry* claim = nullptr;
  bool generalized = false, reachable = false;
  std::optional<std::size_t> target;
  Group first, second, counts;
  std::vector<unsigned char> bits;
  std::vector<Group> groups;
  std::vector<std::shared_ptr<ReplayPorts>> group_ports;
  VariableSet shared;
  VariableSet::const_iterator it;
  std::shared_ptr<ReplayPorts> port;
  std::shared_ptr<ReplayState> state;
};
}  // namespace

// Own supplied claims separately from verified bounds and publish authority only after
// whole-root matching. See docs/planner_proofs.md, P06 authority.
struct ReplayMachine::Impl {
  std::shared_ptr<const BindingData> binding;
  std::shared_ptr<const HeightCertificate> proof;
  std::unique_ptr<ValidationMachine> upper_machine;
  std::shared_ptr<const CheckedUpper> upper;
  std::shared_ptr<const CheckedProof> authority;
  ReplayPhase phase = ReplayPhase::admitted;
  std::string_view diagnostic;
  bool v2 = false;
  unsigned stage = 0;
  std::size_t a = 0, b = 0, c = 0, order_pos = 0, count_checked = 0;
  std::vector<VariableSet> scopes;
  VariableSet head;
  std::vector<std::size_t> classes, representatives;
  VariableSet::const_iterator left, right;
  std::vector<std::size_t> ordered;
  std::map<std::shared_ptr<const ReplayState>, std::optional<std::size_t>, StateLess> provided, verified;
  std::vector<std::unique_ptr<ReplayJob>> jobs;
  // Return registers are moved, never copied, at frame return.
  std::shared_ptr<ReplayState> returned_key;
  std::shared_ptr<ReplayPorts> returned_ports;
  // This cache is derived solely from the independently reconstructed scopes.
  // A node is visible only after all port sets and its member key are complete.
  std::map<const Group*, std::shared_ptr<ReplayPorts>, GroupLess> port_cache;
  std::vector<Group> returned_components;
  std::optional<std::size_t> returned_bound;
  Group all;
  // A single enumeration is active at once. Descending frames append one
  // smallest-remaining block; returning frames remove exactly that block.
  std::vector<Group> partition;

  // Capture admitted proof and binding owners; checking starts on step. See
  // docs/planner_continuations.md, grants.
  Impl(std::shared_ptr<const BindingData> bnd, std::shared_ptr<const HeightCertificate> p)
      : binding(std::move(bnd)), proof(std::move(p)) {}
  // Mark proof rejection terminal with a stable diagnostic view; do not publish checked
  // authority. See docs/planner_continuations.md, authority.
  UnitResult fail(std::string_view why) noexcept {
    diagnostic = why; phase = ReplayPhase::failed;
    return {UnitEvent::proof_invalid};
  }
  // Count the nonempty dispatch frame plus jobs, or delegate active upper-validation depth.
  // See docs/planner_continuations.md, resource accounting.
  std::size_t depth() const noexcept {
    if (binding->query.atoms.empty() || phase == ReplayPhase::complete || phase == ReplayPhase::failed) return 0;
    return upper_machine && phase == ReplayPhase::validate_upper
        ? std::max<std::size_t>(1, upper_machine->current_depth()) : jobs.size() + 1;
  }
  // Check the proposed frame depth before creating a child job. See
  // docs/planner_continuations.md, resource accounting.
  bool permitted_push(const UnitContext& context) const noexcept {
    return context.permits(jobs.size() + 2);
  }
  // Report the pending child depth without changing proof state. See
  // docs/planner_continuations.md, resource accounting.
  UnitResult blocked() const noexcept { return {UnitEvent::depth_blocked, jobs.size() + 2}; }
  // Push a prepared frame before advancing its parent stage; unique_ptr storage preserves
  // frame addresses. See docs/planner_continuations.md, grants.
  void push(std::unique_ptr<ReplayJob> job) { jobs.push_back(std::move(job)); }
  // Pop the active frame only after transferring its result; scratch release may scale with
  // retained payload. See docs/planner_continuations.md, retained state.
  void finish() noexcept { jobs.pop_back(); }
  // Prepare a child frame privately; its input group stays borrowed from a retained owner.
  // See docs/planner_continuations.md, grants.
  std::unique_ptr<ReplayJob> make(ReplayJob::Kind kind, const Group* group = nullptr) {
    auto j = std::make_unique<ReplayJob>(kind); j->input = group; return j;
  }
  UnitResult run_job(const UnitContext& context);
  UnitResult step(const UnitContext& context);
};

// Run one saved independent job action; allocation can escape for retry, while invalid
// evidence becomes terminal. See docs/planner_continuations.md, grants.
UnitResult ReplayMachine::Impl::run_job(const UnitContext& context) {
  auto& j = *jobs.back();
  switch (j.kind) {
    // Build v1 actual keys or v2 class-count representatives from checker-derived complete
    // scopes. See docs/planner_proofs.md, P04 symmetry.
    case ReplayJob::key:
      switch (j.stage) {
        case 0: {
          auto state = std::make_shared<ReplayState>();
          state->generalized = j.generalized; state->reachable = j.reachable;
          j.state = std::move(state); j.stage = v2 ? 1 : 5; return {};
        }
        case 1:
          if (j.counts.size() < representatives.size()) { j.counts.push_back(0); return {}; }
          j.stage = 2; return {};
        case 2:
          if (j.a < j.input->size()) { ++j.counts[classes[(*j.input)[j.a]]]; ++j.a; return {}; }
          j.a = 0; j.stage = 3; return {};
        case 3:
          if (j.a < classes.size()) {
            auto& remaining = j.counts[classes[j.a]];
            if (remaining) { j.state->occurrences.push_back(j.a); --remaining; }
            ++j.a; return {};
          }
          j.stage = 6; return {};
        case 5:
          if (j.a < j.input->size()) { j.state->occurrences.push_back((*j.input)[j.a]); ++j.a; return {}; }
          j.stage = 6; return {};
        default: returned_key = std::move(j.state); finish(); return {};
      }
    // Derive actual inside/outside ports independently and cache them only after every set
    // and the owning key are complete. See docs/planner_proofs.md, P06 authority.
    case ReplayJob::ports:
      switch (j.stage) {
        case 0: {
          const auto cached = port_cache.find(j.input);
          if (cached != port_cache.end()) {
            returned_ports = cached->second; finish(); return {};
          }
          j.port = std::make_shared<ReplayPorts>(); j.stage = 1; return {};
        }
        case 1:
          if (j.a == scopes.size()) { j.it = j.port->variables.begin(); j.stage = 3; return {}; }
          j.it = scopes[j.a].begin();
          j.generalized = std::binary_search(j.input->begin(), j.input->end(), j.a);
          j.stage = 2; return {};
        case 2:
          if (j.it != scopes[j.a].end()) {
            (j.generalized ? j.port->variables : j.port->outside).insert(*j.it);
            ++j.it; return {};
          }
          ++j.a; j.stage = 1; return {};
        case 3:
          if (j.it != j.port->variables.end()) {
            if (j.port->outside.contains(*j.it)) j.port->boundary.insert(*j.it);
            else if (head.contains(*j.it)) j.port->exclusive_head.insert(*j.it);
            ++j.it; return {};
          }
          j.b = 0; j.stage = 4; return {};
        case 4:
          if (j.b < j.input->size()) {
            j.port->members.push_back((*j.input)[j.b]); ++j.b; return {};
          }
          j.stage = 5; return {};
        case 5:
          // emplace can allocate, but it copies only a pointer and shared
          // ownership. A failure leaves this exact publication retryable.
          port_cache.emplace(&j.port->members, j.port);
          returned_ports = std::move(j.port); finish(); return {};
      }
      break;
    // Use only verified child claims; an omitted child supplies universal one, while an
    // unproved supplied dependency rejects. See docs/planner_proofs.md, lower-bound evidence.
    case ReplayJob::child:
      if (j.stage == 0) {
        if (!permitted_push(context)) return blocked();
        auto task = make(ReplayJob::key, j.input);
        task->generalized = j.generalized; task->reachable = j.reachable;
        push(std::move(task)); j.stage = 1; return {};
      } else {
        auto found = verified.find(returned_key);
        if (found != verified.end()) returned_bound = found->second;
        else {
          if (provided.contains(returned_key)) return fail("proof uses a state before its smaller dependencies");
          returned_bound = 1;
        }
        finish(); return {};
      }
    // Reconstruct components by an independent scope-sharing graph walk; nullary occurrences
    // stay separate. See docs/planner_proofs.md, P04 components.
    case ReplayJob::components:
      // Independent occurrence graph walk. Each adjacency test scans one
      // scope member per step; empty scopes form their own components.
      switch (j.stage) {
        case 0:
          if (j.bits.size() < scopes.size()) { j.bits.push_back(0); return {}; }
          j.stage = 1; return {};
        case 1:
          if (j.a == scopes.size()) { returned_components = std::move(j.groups); finish(); return {}; }
          if (j.bits[j.a]) { ++j.a; return {}; }
          j.first.push_back(j.a); j.bits[j.a] = 1; j.b = 0; j.stage = 2; return {};
        case 2:
          if (j.b == j.first.size()) { j.c = 0; j.stage = 6; return {}; }
          j.c = 0; j.stage = 3; return {};
        case 3:
          if (j.c == scopes.size()) { ++j.b; j.stage = 2; return {}; }
          if (j.bits[j.c]) { ++j.c; return {}; }
          j.it = scopes[j.first[j.b]].begin(); j.stage = 4; return {};
        case 4:
          if (j.it == scopes[j.first[j.b]].end()) { ++j.c; j.stage = 3; return {}; }
          if (scopes[j.c].contains(*j.it)) {
            j.first.push_back(j.c); j.bits[j.c] = 1; ++j.c; j.stage = 3;
          } else ++j.it;
          return {};
        case 6:
          // Reconstruct in global occurrence order, avoiding a bulk sort.
          if (j.c < scopes.size()) {
            if (j.bits[j.c] == 1) j.second.push_back(j.c);
            ++j.c; return {};
          }
          j.stage = 7; return {};
        case 7:
          j.groups.push_back(std::move(j.second)); j.c = 0; j.stage = 8; return {};
        case 8:
          if (j.c < j.first.size()) { j.bits[j.first[j.c]] = 2; ++j.c; return {}; }
          j.first.clear(); ++j.a; j.stage = 1; return {};
      }
      break;
    // Prove every alternative or an independently justified base/component case before a
    // claim reaches verified. See docs/planner_proofs.md, lower-bound evidence and P04
    // components.
    case ReplayJob::prove:
      switch (j.stage) {
        case 0:
          if (j.claim->bound == 1) { finish(); return {}; }
          if (!permitted_push(context)) return blocked();
          push(make(ReplayJob::ports, &j.claim->occurrences)); j.stage = 1; return {};
        case 1:
          j.port = std::move(returned_ports);
          if (!j.claim->connex_reachable && !j.port->exclusive_head.empty()) { finish(); return {}; }
          j.stage = v2 && j.claim->generalized_allowed && j.claim->connex_reachable &&
                    j.claim->occurrences.size() == scopes.size() ? 2 : 10;
          return {};
        case 2:
          if (!permitted_push(context)) return blocked();
          push(make(ReplayJob::components)); j.stage = 3; return {};
        case 3:
          j.groups = std::move(returned_components);
          j.stage = j.groups.size() >= 2 ? 4 : 10; j.maximum = 1; return {};
        case 4:
          if (j.a == j.groups.size()) {
            if (!j.claim->bound || j.maximum < *j.claim->bound)
              return fail("component bounds do not establish full-query lower bound");
            finish(); return {};
          }
          if (!permitted_push(context)) return blocked();
          push(make(ReplayJob::ports, &j.groups[j.a])); j.stage = 5; return {};
        case 5:
          if (!returned_ports->boundary.empty()) return fail("invalid independently derived component boundary");
          if (!permitted_push(context)) return blocked();
          { auto task = make(ReplayJob::child, &j.groups[j.a]); task->generalized = task->reachable = true;
            push(std::move(task)); }
          j.stage = 6; return {};
        case 6:
          if (!returned_bound) { finish(); return {}; }
          j.maximum = std::max(j.maximum, *returned_bound); ++j.a; j.stage = 4; return {};
        case 10:
          if (j.a == j.claim->occurrences.size()) { j.stage = 20; return {}; }
          j.it = j.port->boundary.begin(); j.stage = 11; return {};
        case 11:
          if (j.it != j.port->boundary.end()) {
            if (!scopes[j.claim->occurrences[j.a]].contains(*j.it)) { ++j.a; j.stage = 10; }
            else ++j.it;
            return {};
          }
          j.b = 0; j.first.clear(); j.stage = 12; return {};
        case 12:
          if (j.b < j.claim->occurrences.size()) {
            if (j.b != j.a) j.first.push_back(j.claim->occurrences[j.b]);
            ++j.b; return {};
          }
          j.stage = 13; return {};
        case 13:
          if (!permitted_push(context)) return blocked();
          { auto task = make(ReplayJob::enumerate, &j.first); task->claim = j.claim;
            task->a = j.claim->occurrences[j.a]; push(std::move(task)); }
          j.stage = 14; return {};
        case 14: ++j.a; j.stage = 10; return {};
        case 20:
          if (!j.claim->generalized_allowed) { finish(); return {}; }
          if (!permitted_push(context)) return blocked();
          { auto task = make(ReplayJob::enumerate, &j.claim->occurrences);
            task->claim = j.claim; task->generalized = true; push(std::move(task)); }
          j.stage = 21; return {};
        default: finish(); return {};
      }
    // Enumerate by the block containing the smallest remaining member and recurse on its
    // complement. See docs/planner_proofs.md, independent lower-bound evidence.
    case ReplayJob::enumerate:
      switch (j.stage) {
        case 0:
          if (j.input->empty()) {
            if (!permitted_push(context)) return blocked();
            auto task = make(ReplayJob::option);
            task->claim = j.claim; task->generalized = j.generalized; task->a = j.a;
            push(std::move(task)); j.stage = 9; return {};
          }
          if (j.bits.size() < j.input->size()) { j.bits.push_back(j.bits.empty() ? 1 : 0); return {}; }
          j.b = 0; j.stage = 1; return {};
        case 1:
          if (j.b < j.input->size()) {
            (j.bits[j.b] ? j.first : j.second).push_back((*j.input)[j.b]); ++j.b; return {};
          }
          j.stage = 2; return {};
        case 2:
          partition.push_back(std::move(j.first)); j.stage = 3; return {};
        case 3:
          if (!permitted_push(context)) return blocked();
          { auto task = make(ReplayJob::enumerate, &j.second);
            task->claim = j.claim; task->generalized = j.generalized; task->a = j.a;
            push(std::move(task)); }
          j.stage = 4; return {};
        case 4:
          partition.pop_back(); j.second.clear(); j.b = j.bits.size(); j.stage = 5; return {};
        case 5:
          if (j.b <= 1) { finish(); return {}; }
          if (j.bits[j.b - 1]) { j.bits[j.b - 1] = 0; --j.b; return {}; }
          j.bits[j.b - 1] = 1; j.b = 0; j.stage = 1; return {};
        default: finish(); return {};
      }
    // Check ports, generalized guards and reachability before comparing root cost plus child
    // lower bounds with the claim. See docs/planner_proofs.md, branch partitions.
    case ReplayJob::option:
      switch (j.stage) {
        case 0:
          if (j.generalized && partition.size() < 2) { finish(); return {}; }
          j.stage = 1; return {};
        case 1:
          if (j.b == partition.size()) { j.b = 0; j.c = 1; j.stage = j.generalized ? 10 : 20; return {}; }
          if (!permitted_push(context)) return blocked();
          push(make(ReplayJob::ports, &partition[j.b])); j.stage = 2; return {};
        case 2:
          j.group_ports.push_back(std::move(returned_ports)); j.it = j.group_ports.back()->boundary.begin(); j.stage = 3; return {};
        case 3:
          if (!j.generalized && j.it != j.group_ports.back()->boundary.end()) {
            if (!scopes[j.a].contains(*j.it)) { finish(); return {}; }
            ++j.it; return {};
          }
          ++j.b; j.stage = 1; return {};
        case 10:
          if (j.b == partition.size()) {
            if (!permitted_push(context)) return blocked();
            push(make(ReplayJob::ports, &j.claim->occurrences)); j.stage = 14; return {};
          }
          if (j.c == partition.size()) { ++j.b; j.c = j.b + 1; return {}; }
          j.it = j.group_ports[j.b]->variables.begin(); j.stage = 11; return {};
        case 11:
          if (j.it != j.group_ports[j.b]->variables.end()) {
            if (j.group_ports[j.c]->variables.contains(*j.it)) j.shared.insert(*j.it);
            ++j.it; return {};
          }
          ++j.c; j.stage = 10; return {};
        case 14:
          j.port = std::move(returned_ports); j.it = j.port->boundary.begin(); j.stage = 15; return {};
        case 15:
          if (j.it != j.port->boundary.end()) {
            if (!j.shared.contains(*j.it)) { finish(); return {}; }
            ++j.it; return {};
          }
          j.b = 0; j.it = j.shared.begin(); j.stage = 16; return {};
        case 16:
          if (j.b == partition.size()) { j.b = 0; j.stage = 20; return {}; }
          if (j.it != j.shared.end()) {
            if (!j.group_ports[j.b]->variables.contains(*j.it)) { finish(); return {}; }
            ++j.it; return {};
          }
          ++j.b; j.it = j.shared.begin(); return {};
        case 20:
          if (j.b == partition.size()) {
            const auto lower = j.maximum + (j.generalized ? 0U : 1U);
            if (!j.claim->bound || lower < *j.claim->bound)
              return fail("claimed lower bound is not established for every root/partition alternative");
            finish(); return {};
          }
          j.reachable = j.claim->connex_reachable;
          j.it = j.group_ports[j.b]->boundary.begin(); j.stage = 21; return {};
        case 21:
          if (j.reachable && j.it != j.group_ports[j.b]->boundary.end()) {
            if (!head.contains(*j.it)) j.reachable = false;
            else ++j.it;
            return {};
          }
          j.stage = 22; return {};
        case 22:
          if (!permitted_push(context)) return blocked();
          { auto task = make(ReplayJob::child, &partition[j.b]);
            task->generalized = j.generalized; task->reachable = j.reachable; push(std::move(task)); }
          j.stage = 23; return {};
        case 23:
          if (!returned_bound) { finish(); return {}; }
          j.maximum = std::max(j.maximum, *returned_bound); ++j.b; j.stage = 20; return {};
      }
      break;
  }
  return fail("invalid replay continuation state");
}

// Publish CheckedProof only after upper checking, claim induction and matching full-query
// root evidence; resource stops keep replay incomplete. See docs/planner_proofs.md, P06
// authority.
UnitResult ReplayMachine::Impl::step(const UnitContext& context) {
  if (phase == ReplayPhase::complete) return {UnitEvent::proof_valid};
  if (phase == ReplayPhase::failed) return {UnitEvent::proof_invalid};
  // The dispatch/scanning cursor is itself an owned replay frame.
  if (!binding->query.atoms.empty() && !context.permits(1)) return {UnitEvent::depth_blocked, 1};
  if (!jobs.empty()) return run_job(context);
  switch (phase) {
    case ReplayPhase::admitted: phase = ReplayPhase::dispatch; return {};
    case ReplayPhase::dispatch:
      if (stage == 0) {
        v2 = proof->algorithm == "crown_partition_exact_v2";
        if (!v2 && proof->algorithm != "crown_partition_exact_v1")
          return fail("unsupported exact-search certificate algorithm");
        if (proof->minimum_height.has_value() != proof->tree.has_value())
          return fail("a minimum needs an upper tree; infeasibility must not include one");
        stage = 1; return {};
      }
      if (proof->tree) {
        // Aliasing ownership keeps the immutable tree alive without a bulk copy.
        auto tree = std::shared_ptr<const FreeConnexTree>(proof, &*proof->tree);
        auto machine = std::make_unique<ValidationMachine>(binding, std::move(tree));
        upper_machine = std::move(machine); phase = ReplayPhase::validate_upper; stage = 0; return {};
      }
      phase = ReplayPhase::build_scopes; stage = 0; return {};
    case ReplayPhase::validate_upper: {
      const auto result = upper_machine->step(context);
      if (result.event == UnitEvent::depth_blocked) return result;
      if (result.event == UnitEvent::upper_invalid) return fail("invalid upper tree or height mismatch");
      if (result.event == UnitEvent::upper_valid) {
        auto checked = upper_machine->checked();
        if (!checked || checked->height != proof->minimum_height) return fail("invalid upper tree or height mismatch");
        upper = std::move(checked); phase = ReplayPhase::build_scopes; stage = 0;
      }
      return {};
    }
    case ReplayPhase::build_scopes:
      if (binding->query.atoms.empty()) {
        if (proof->minimum_height != 0 || !proof->lower_bounds.empty())
          return fail("empty-body proof must be the empty height-zero tree with no states");
        phase = ReplayPhase::match_root; stage = 3; return {};
      }
      switch (stage) {
        case 0:
          if (a == binding->query.atoms.size()) { a = 0; stage = 2; return {}; }
          scopes.emplace_back(); b = 0; stage = 1; return {};
        case 1:
          if (b < binding->query.atoms[a].terms.size()) {
            if (const auto* variable = std::get_if<VariableId>(&binding->query.atoms[a].terms[b])) scopes.back().insert(*variable);
            ++b; return {};
          }
          ++a; stage = 0; return {};
        default:
          if (a < binding->query.head.size()) { head.insert(binding->query.head[a].variable); ++a; return {}; }
          a = b = 0; stage = 0; phase = v2 ? ReplayPhase::classify_scope_orbits : ReplayPhase::index_claims; return {};
      }
    case ReplayPhase::classify_scope_orbits:
      switch (stage) {
        case 0:
          if (a == scopes.size()) { a = b = 0; phase = ReplayPhase::index_claims; return {}; }
          b = 0; stage = 1; return {};
        case 1:
          if (b == representatives.size()) { stage = 4; return {}; }
          if (scopes[a].size() != scopes[representatives[b]].size()) { ++b; return {}; }
          left = scopes[a].begin(); right = scopes[representatives[b]].begin(); stage = 2; return {};
        case 2:
          if (left == scopes[a].end()) { stage = 5; return {}; }
          if (*left != *right) { ++b; stage = 1; return {}; }
          ++left; ++right; return {};
        case 4:
          representatives.push_back(a); stage = 5; return {};
        default:
          classes.push_back(b); ++a; stage = 0; return {};
      }
    case ReplayPhase::index_claims:
      switch (stage) {
        case 0:
          if (a == proof->lower_bounds.size()) {
            a = 1; b = 1; stage = 0; phase = ReplayPhase::order_claims; return {};
          }
          if (proof->lower_bounds[a].occurrences.empty())
            return fail("proof state occurrences must be nonempty, sorted, unique and in range");
          b = 0; stage = 1; return {};
        case 1: {
          const auto& e = proof->lower_bounds[a];
          if (b < e.occurrences.size()) {
            if (e.occurrences[b] >= scopes.size() || (b && e.occurrences[b - 1] >= e.occurrences[b]))
              return fail("proof state occurrences must be nonempty, sorted, unique and in range");
            ++b; return {};
          }
          if (e.bound && (*e.bound == 0 || *e.bound > e.occurrences.size()))
            return fail("finite state bound must be between one and its native occurrence count");
          stage = 2; return {};
        }
        case 2: {
          if (!permitted_push(context)) return blocked();
          const auto& e = proof->lower_bounds[a];
          auto task = make(ReplayJob::key, &e.occurrences);
          task->generalized = e.generalized_allowed; task->reachable = e.connex_reachable;
          push(std::move(task)); stage = 3; return {};
        }
        case 3:
          if (!provided.emplace(returned_key, proof->lower_bounds[a].bound).second)
            return fail("duplicate lower-bound state");
          stage = 4; return {};
        default:
          ordered.push_back(a); ++a; stage = 0; return {};
      }
    case ReplayPhase::order_claims:
      // Stable adjacent insertion: one size comparison/swap per transition.
      if (a >= ordered.size()) { order_pos = 0; phase = ReplayPhase::prove_claim; stage = 0; return {}; }
      if (b && proof->lower_bounds[ordered[b]].occurrences.size() < proof->lower_bounds[ordered[b - 1]].occurrences.size()) {
        std::swap(ordered[b], ordered[b - 1]); --b; return {};
      }
      ++a; b = a; return {};
    case ReplayPhase::prove_claim:
      switch (stage) {
        case 0:
          if (order_pos == ordered.size()) { a = 0; phase = ReplayPhase::match_root; return {}; }
          if (!permitted_push(context)) return blocked();
          { auto task = make(ReplayJob::prove); task->claim = &proof->lower_bounds[ordered[order_pos]]; push(std::move(task)); }
          stage = 1; return {};
        case 1: {
          if (!permitted_push(context)) return blocked();
          const auto& e = proof->lower_bounds[ordered[order_pos]];
          auto task = make(ReplayJob::key, &e.occurrences);
          task->generalized = e.generalized_allowed; task->reachable = e.connex_reachable;
          push(std::move(task)); stage = 2; return {};
        }
        default:
          verified.emplace(returned_key, proof->lower_bounds[ordered[order_pos]].bound);
          ++count_checked; ++order_pos; stage = 0; return {};
      }
    case ReplayPhase::match_root:
      switch (stage) {
        case 0:
          if (a < scopes.size()) { all.push_back(a); ++a; return {}; }
          stage = 1; return {};
        case 1:
          if (!permitted_push(context)) return blocked();
          { auto task = make(ReplayJob::key, &all); task->generalized = task->reachable = true; push(std::move(task)); }
          stage = 2; return {};
        case 2: {
          const auto root = verified.find(returned_key);
          if (root == verified.end() || root->second != proof->minimum_height)
            return fail("missing or mismatched full-query lower bound");
          stage = 3; return {};
        }
        default: {
          auto checked = std::make_shared<CheckedProof>();
          checked->binding = binding; checked->proof = proof; checked->upper = upper;
          authority = std::move(checked);
          diagnostic = proof->tree ? (v2 ? "upper tree and v2 lower bound verified" : "upper tree and exhaustive lower bound verified")
                                   : "empty admissible family verified";
          phase = ReplayPhase::complete; return {UnitEvent::proof_valid};
        }
      }
    default: return fail("invalid replay continuation phase");
  }
}

// Allocate an inert checker shell around immutable binding and certificate owners. See
// docs/planner_continuations.md, grants.
ReplayMachine::ReplayMachine(std::shared_ptr<const BindingData> binding,
                             std::shared_ptr<const HeightCertificate> proof)
    : data_(std::make_unique<Impl>(std::move(binding), std::move(proof))) {}
// Release flat checker jobs and caches; independently retained checked artifacts outlive the
// machine. See docs/planner_continuations.md, lifetime.
ReplayMachine::~ReplayMachine() = default;
// Transfer the saved replay owner without moving frames or cached key payloads. See
// docs/planner_continuations.md, lifetime.
ReplayMachine::ReplayMachine(ReplayMachine&&) noexcept = default;
// Replace checker ownership and release prior destination state; retained checked handles
// remain valid. See docs/planner_continuations.md, lifetime.
ReplayMachine& ReplayMachine::operator=(ReplayMachine&&) noexcept = default;
// Delegate one saved checker action; the facade alone charges work and time. See
// docs/planner_continuations.md, resource accounting.
UnitResult ReplayMachine::step(const UnitContext& context) { return data_->step(context); }
// Read checker progress without advancing or creating authority. See
// docs/planner_continuations.md, authority.
ReplayPhase ReplayMachine::phase() const noexcept { return data_->phase; }
// Report the checker logical frame depth, including delegated upper validation. See
// docs/planner_continuations.md, resource accounting.
std::size_t ReplayMachine::current_depth() const noexcept { return data_->depth(); }
// Count committed claim proofs; a verified prefix does not certify the whole-query optimum.
// See docs/planner_continuations.md, authority.
std::size_t ReplayMachine::checked_claims() const noexcept { return data_->count_checked; }
// Borrow the stable checker diagnostic; owning legacy message conversion happens outside this
// accessor. See docs/planner_continuations.md, resource accounting.
std::string_view ReplayMachine::message() const noexcept { return data_->diagnostic; }
// Retain authority only after complete independent replay; finite roots pair with an upper,
// infinite roots have none. See docs/planner_continuations.md, authority.
std::shared_ptr<const CheckedProof> ReplayMachine::checked() const noexcept { return data_->authority; }
}  // namespace crown::planner::continuation_detail
