# `src/planner/exact.cpp` — block usage map

[Source](../../../../../src/planner/exact.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Implement the local finite partition recurrence/search machine for exact native-height optimization.

Snapshot SHA-256: `5654f4f903d3d4f2c26ead63b269115c0799a25d17c8762069e6b332e851471c`. 710 lines partitioned into 81 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/planner/exact.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Members keeps input-binding occurrence indices in sorted order; equal scopes remain distinct. See · [reviewed contract](#b0001) |
| [B0002 · 15–21](../../../../../src/planner/exact.cpp#L15) | Type/record definition: struct Key | source comment (unverified): // Key includes the native subset, generalized-root permission and C* reachability; all three · [reviewed contract](#b0002) |
| [B0003 · 22–23](../../../../../src/planner/exact.cpp#L22) | Explanatory comments or spacing. | source comment (unverified): // Order immutable memo keys by contents; shared ownership identity does not identify a state. · [reviewed contract](#b0003) |
| [B0004 · 24–28](../../../../../src/planner/exact.cpp#L24) | Type/record definition: struct KeyLess | returns *a &lt; *b; source comment (unverified): // Order immutable memo keys by contents; shared ownership identity does not identify a state. · [reviewed contract](#b0004) |
| [B0005 · 29–30](../../../../../src/planner/exact.cpp#L29) | Explanatory comments or spacing. | source comment (unverified): // Classify equal complete scopes while retaining all native IDs. See docs/planner_proofs.md, · [reviewed contract](#b0005) |
| [B0006 · 31–35](../../../../../src/planner/exact.cpp#L31) | Type/record definition: struct ScopeLess | returns *a &lt; *b; source comment (unverified): // Classify equal complete scopes while retaining all native IDs. See docs/planner_proofs.md, · [reviewed contract](#b0006) |
| [B0007 · 36–38](../../../../../src/planner/exact.cpp#L36) | Explanatory comments or spacing. | source comment (unverified): // A Choice is a producer witness, with null height for infeasibility; P02 must check a · [reviewed contract](#b0007) |
| [B0008 · 39–45](../../../../../src/planner/exact.cpp#L39) | Type/record definition: struct Choice | source comment (unverified): // A Choice is a producer witness, with null height for infeasibility; P02 must check a · [reviewed contract](#b0008) |
| [B0009 · 46–51](../../../../../src/planner/exact.cpp#L46) | Explanatory comments or spacing. | source comment (unverified): // Child edges never own their target. All records have stable addresses in a · [reviewed contract](#b0009) |
| [B0010 · 52–69](../../../../../src/planner/exact.cpp#L52) | Type/record definition: struct ChoiceArena | returns result; append(prepared); growth make_unique, push_back; source comment (unverified): // Child edges never own their target. All records have stable addresses in a · [reviewed contract](#b0010) |
| [B0011 · 70–71](../../../../../src/planner/exact.cpp#L70) | Explanatory comments or spacing. | source comment (unverified): // Metadata stores U(S), boundary B(S) and exclusive head E(S) for one actual native subset. · [reviewed contract](#b0011) |
| [B0012 · 72–72](../../../../../src/planner/exact.cpp#L72) | Type/record definition: struct Metadata | source comment (unverified): // Metadata stores U(S), boundary B(S) and exclusive head E(S) for one actual native subset. · [reviewed contract](#b0012) |
| [B0013 · 73–77](../../../../../src/planner/exact.cpp#L73) | controls preprocessing; declares callable signatures; declares values/defaults or compile-time conditions. | 2 loop sites; source comment (unverified): // Create child frames in the pending-operation scheduler before awaiting them; preserve · [reviewed contract](#b0013) |
| [B0014 · 78–81](../../../../../src/planner/exact.cpp#L78) | Callable definition: Task copy_members(Engine&, const Members& source, Members& dest) | calls operation, reserve, size, push_back; growth push_back, reserve; 1 loop sites; source comment (unverified): // Append source IDs in order to a caller-retained destination; callers pass fresh state · [reviewed contract](#b0014) |
| [B0015 · 82–83](../../../../../src/planner/exact.cpp#L82) | Explanatory comments or spacing. | source comment (unverified): // Union a stable source scope into retained scratch one variable per pending operation. See · [reviewed contract](#b0015) |
| [B0016 · 84–86](../../../../../src/planner/exact.cpp#L84) | Callable definition: Task copy_scope(Engine&, const VariableSet& source, VariableSet& dest) | calls operation, insert; growth insert; 1 loop sites; source comment (unverified): // Union a stable source scope into retained scratch one variable per pending operation. See · [reviewed contract](#b0016) |
| [B0017 · 87–88](../../../../../src/planner/exact.cpp#L87) | Explanatory comments or spacing. | source comment (unverified): // Test required ⊆ scope with an early missing-variable exit. See docs/planner_proofs.md, · [reviewed contract](#b0017) |
| [B0018 · 89–95](../../../../../src/planner/exact.cpp#L89) | Callable definition: Task contains(Engine&, const VariableSet& scope, const VariableSet& required, bool& result) | calls operation; 1 loop sites; source comment (unverified): // Test required ⊆ scope with an early missing-variable exit. See docs/planner_proofs.md, · [reviewed contract](#b0018) |
| [B0019 · 96–97](../../../../../src/planner/exact.cpp#L96) | Explanatory comments or spacing. | source comment (unverified): // Copy a checked tree into fresh certificate scratch, preserving node indices and optional · [reviewed contract](#b0019) |
| [B0020 · 98–118](../../../../../src/planner/exact.cpp#L98) | Callable definition: Task copy_tree(Engine& e, const FreeConnexTree& source, FreeConnexTree& target) | calls operation, reserve, size, push_back; growth emplace, push_back, reserve; 3 loop sites; source comment (unverified): // Copy a checked tree into fresh certificate scratch, preserving node indices and optional · [reviewed contract](#b0020) |
| [B0021 · 119–121](../../../../../src/planner/exact.cpp#L119) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0021) |
| [B0022 · 122–125](../../../../../src/planner/exact.cpp#L122) | Type/record definition: struct FrozenCandidate | source comment (unverified): // Retain the choice arena while a witness builder reads the completed root; this is a · [reviewed contract](#b0022) |
| [B0023 · 126–131](../../../../../src/planner/exact.cpp#L126) | declares types or opens a type body. | source comment (unverified): // Own exact-search cursors and memo entries; candidates pause the producer until · [reviewed contract](#b0023) |
| [B0024 · 132–132](../../../../../src/planner/exact.cpp#L132) | Callable definition: explicit Impl(std::shared_ptr&lt;const BindingData&gt; b) : binding(std::move(b)) | calls binding, std::move; source comment (unverified): // Capture the admitted binding; preprocessing starts only on step. See · [reviewed contract](#b0024) |
| [B0025 · 133–134](../../../../../src/planner/exact.cpp#L133) | Explanatory comments or spacing. | source comment (unverified): // Cancel live frames before Task/member destruction; retained candidates keep their own · [reviewed contract](#b0025) |
| [B0026 · 135–135](../../../../../src/planner/exact.cpp#L135) | Callable definition: ~Impl() | calls cancel; source comment (unverified): // Cancel live frames before Task/member destruction; retained candidates keep their own · [reviewed contract](#b0026) |
| [B0027 · 136–156](../../../../../src/planner/exact.cpp#L136) | declares values/defaults or compile-time conditions. | source comment (unverified): // Derive ports from full native scopes and global occurrence totals, never from output · [reviewed contract](#b0027) |
| [B0028 · 157–168](../../../../../src/planner/exact.cpp#L157) | Callable definition: Task metadata(const Members& members, Metadata& out) | calls operation, insert, at, contains; growth insert; 3 loop sites; source comment (unverified): // Derive ports from full native scopes and global occurrence totals, never from output · [reviewed contract](#b0028) |
| [B0029 · 169–170](../../../../../src/planner/exact.cpp#L169) | Explanatory comments or spacing. | source comment (unverified): // Publish an arena-retaining root candidate only after its wrapper is ready. See · [reviewed contract](#b0029) |
| [B0030 · 171–178](../../../../../src/planner/exact.cpp#L171) | Callable definition: Task publish(const Choice* choice) | calls operation, std::move; growth make_shared; source comment (unverified): // Publish an arena-retaining root candidate only after its wrapper is ready. See · [reviewed contract](#b0030) |
| [B0031 · 179–180](../../../../../src/planner/exact.cpp#L179) | Explanatory comments or spacing. | source comment (unverified): // Keep strict improvements only; prune with native root cost and safe child lower bounds, · [reviewed contract](#b0031) |
| [B0032 · 181–215](../../../../../src/planner/exact.cpp#L181) | Callable definition: Task consider(const std::shared_ptr&lt;const Key&gt;& key, NodeKind kind, std::optional&lt;std::size_t&gt; occurrence, std::shared_ptr&lt;const … | calls operation, empty, std::move, SUBTASK; growth make_shared, make_unique, push_back; 1 loop sites; source comment (unverified): // Keep strict improvements only; prune with native root cost and safe child lower bounds, · [reviewed contract](#b0032) |
| [B0033 · 216–217](../../../../../src/planner/exact.cpp#L216) | Explanatory comments or spacing. | source comment (unverified): // Check native ports or derive the unique normalized generalized scope from child unions · [reviewed contract](#b0033) |
| [B0034 · 218–256](../../../../../src/planner/exact.cpp#L218) | Callable definition: Task inspect_partition(const std::shared_ptr&lt;const Key&gt;& key, const Metadata& meta, std::optional&lt;std::size_t&gt; occurrence, const … | calls operation, SUBTASK, metadata, contains; growth insert, make_shared; 5 loop sites; source comment (unverified): // Check native ports or derive the unique normalized generalized scope from child unions · [reviewed contract](#b0034) |
| [B0035 · 257–258](../../../../../src/planner/exact.cpp#L257) | Explanatory comments or spacing. | source comment (unverified): // Enumerate partitions by ordered insertion; return early only at the universal nonempty · [reviewed contract](#b0035) |
| [B0036 · 259–276](../../../../../src/planner/exact.cpp#L259) | Callable definition: Task partitions(const std::shared_ptr&lt;const Key&gt;& key, const Metadata& meta, std::optional&lt;std::size_t&gt; occurrence, const Members… | calls size, SUBTASK, inspect_partition, operation; growth push_back; 1 loop sites; source comment (unverified): // Enumerate partitions by ordered insertion; return early only at the universal nonempty · [reviewed contract](#b0036) |
| [B0037 · 277–279](../../../../../src/planner/exact.cpp#L277) | Explanatory comments or spacing. | source comment (unverified): // Memoize only complete state optima; component, symmetry and incumbent rules preserve one · [reviewed contract](#b0037) |
| [B0038 · 280–335](../../../../../src/planner/exact.cpp#L280) | Callable definition: Task solve(std::shared_ptr&lt;const Key&gt; key, const Choice*& result) | calls operation, find, end, size; growth emplace, insert, make_shared, push_back; 3 loop sites; source comment (unverified): // Memoize only complete state optima; component, symmetry and incumbent rules preserve one · [reviewed contract](#b0038) |
| [B0039 · 336–337](../../../../../src/planner/exact.cpp#L336) | Explanatory comments or spacing. | source comment (unverified): // Build full scopes, equal-scope classes and variable-sharing components while preserving · [reviewed contract](#b0039) |
| [B0040 · 338–380](../../../../../src/planner/exact.cpp#L338) | Callable definition: Task preprocess() | calls operation, reserve, size, push_back; growth emplace, insert, make_shared, push_back, reserve; 9 loop sites; source comment (unverified): // Build full scopes, equal-scope classes and variable-sharing components while preserving · [reviewed contract](#b0040) |
| [B0041 · 381–383](../../../../../src/planner/exact.cpp#L381) | Explanatory comments or spacing. | source comment (unverified): // Recognize laminar incidence classes with free-variable upward closure; a hit constructs · [reviewed contract](#b0041) |
| [B0042 · 384–498](../../../../../src/planner/exact.cpp#L384) | Callable definition: Task hierarchy(const Choice*& result) | calls operation, size, contains, emplace; returns *a &lt; *b; growth emplace, insert, make_shared, push_back; 12 loop sites; source comment (unverified): // Recognize laminar incidence classes with free-variable upward closure; a hit constructs · [reviewed contract](#b0042) |
| [B0043 · 499–501](../../../../../src/planner/exact.cpp#L499) | Explanatory comments or spacing. | source comment (unverified): // Export complete memo claims and a matching independently checked upper; this producer · [reviewed contract](#b0043) |
| [B0044 · 502–555](../../../../../src/planner/exact.cpp#L502) | Callable definition: Task export_proof() | calls operation, Error, emplace, SUBTASK; growth emplace, make_shared, push_back, reserve; 7 loop sites; source comment (unverified): // Export complete memo claims and a matching independently checked upper; this producer · [reviewed contract](#b0044) |
| [B0045 · 556–557](../../../../../src/planner/exact.cpp#L556) | Explanatory comments or spacing. | source comment (unverified): // Drive the structural routes and export only after the final candidate has a checked · [reviewed contract](#b0045) |
| [B0046 · 558–587](../../../../../src/planner/exact.cpp#L558) | Callable definition: Task main() | calls operation, empty, append, SUBTASK; growth emplace, make_shared, push_back; 1 loop sites; source comment (unverified): // Drive the structural routes and export only after the final candidate has a checked · [reviewed contract](#b0046) |
| [B0047 · 588–591](../../../../../src/planner/exact.cpp#L588) | Closes surrounding scope/type. | source comment (unverified): // Allocate an inert producer shell around the owned binding; step starts work. See · [reviewed contract](#b0047) |
| [B0048 · 592–592](../../../../../src/planner/exact.cpp#L592) | Callable definition: ProducerMachine::ProducerMachine(std::shared_ptr&lt;const BindingData&gt; binding) : data_(std::make_unique&lt;Impl&gt;(std::move(binding))) | calls data_, std::move; growth make_unique; source comment (unverified): // Allocate an inert producer shell around the owned binding; step starts work. See · [reviewed contract](#b0048) |
| [B0049 · 593–603](../../../../../src/planner/exact.cpp#L593) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Destroy the producer and cancel active frames; shared candidate arenas may outlive it. See · [reviewed contract](#b0049) |
| [B0050 · 604–618](../../../../../src/planner/exact.cpp#L604) | Callable definition: UnitResult ProducerMachine::step(const UnitContext& context) | calls empty, permits, main, std::move; returns {UnitEvent::candidate_ready, 0}; {UnitEvent::producer_complete, 0}; source comment (unverified): // Advance a saved transition, stopping for the candidate handshake or depth permission before · [reviewed contract](#b0050) |
| [B0051 · 619–620](../../../../../src/planner/exact.cpp#L619) | Explanatory comments or spacing. | source comment (unverified): // Read producer progress only; phase alone carries no minimum authority. See · [reviewed contract](#b0051) |
| [B0052 · 621–621](../../../../../src/planner/exact.cpp#L621) | Callable definition: SearchPhase ProducerMachine::phase() const noexcept | calls ; returns data_-&gt;phase; source comment (unverified): // Read producer progress only; phase alone carries no minimum authority. See · [reviewed contract](#b0052) |
| [B0053 · 622–623](../../../../../src/planner/exact.cpp#L622) | Explanatory comments or spacing. | source comment (unverified): // Borrow producer counters while the machine lives; counters provide progress evidence, not · [reviewed contract](#b0053) |
| [B0054 · 624–624](../../../../../src/planner/exact.cpp#L624) | Callable definition: const SearchStatistics& ProducerMachine::statistics() const noexcept | calls ; returns data_-&gt;stats; source comment (unverified): // Borrow producer counters while the machine lives; counters provide progress evidence, not · [reviewed contract](#b0054) |
| [B0055 · 625–626](../../../../../src/planner/exact.cpp#L625) | Explanatory comments or spacing. | source comment (unverified): // Report logical coroutine depth, with zero for empty administrative or completed work. See · [reviewed contract](#b0055) |
| [B0056 · 627–627](../../../../../src/planner/exact.cpp#L627) | Callable definition: std::size_t ProducerMachine::current_depth() const noexcept | calls ; returns data_-&gt;proof \|\| data_-&gt;e.administrative_only ? 0 : data_-&gt;e.depth; source comment (unverified): // Report logical coroutine depth, with zero for empty administrative or completed work. See · [reviewed contract](#b0056) |
| [B0057 · 628–629](../../../../../src/planner/exact.cpp#L628) | Explanatory comments or spacing. | source comment (unverified): // Retain the pending arena-backed candidate for witness construction and P02 validation. See · [reviewed contract](#b0057) |
| [B0058 · 630–630](../../../../../src/planner/exact.cpp#L630) | Callable definition: std::shared_ptr&lt;const FrozenCandidate&gt; ProducerMachine::candidate() const noexcept | calls ; returns data_-&gt;pending; source comment (unverified): // Retain the pending arena-backed candidate for witness construction and P02 validation. See · [reviewed contract](#b0058) |
| [B0059 · 631–632](../../../../../src/planner/exact.cpp#L631) | Explanatory comments or spacing. | source comment (unverified): // Accept only facade-supplied P02 authority; final export checks its binding and selected · [reviewed contract](#b0059) |
| [B0060 · 633–633](../../../../../src/planner/exact.cpp#L633) | Callable definition: void ProducerMachine::accept_upper(std::shared_ptr&lt;const CheckedUpper&gt; upper) noexcept | calls std::move; source comment (unverified): // Accept only facade-supplied P02 authority; final export checks its binding and selected · [reviewed contract](#b0060) |
| [B0061 · 634–635](../../../../../src/planner/exact.cpp#L634) | Explanatory comments or spacing. | source comment (unverified): // Clear pending only after checked-upper publication succeeds, then resume exact search. See · [reviewed contract](#b0061) |
| [B0062 · 636–636](../../../../../src/planner/exact.cpp#L636) | Callable definition: void ProducerMachine::acknowledge_candidate() noexcept | calls reset; source comment (unverified): // Clear pending only after checked-upper publication succeeds, then resume exact search. See · [reviewed contract](#b0062) |
| [B0063 · 637–638](../../../../../src/planner/exact.cpp#L637) | Explanatory comments or spacing. | source comment (unverified): // Retain the exported certificate for independent replay; producer completion alone proves no · [reviewed contract](#b0063) |
| [B0064 · 639–639](../../../../../src/planner/exact.cpp#L639) | Callable definition: std::shared_ptr&lt;const HeightCertificate&gt; ProducerMachine::completed_proof() const noexcept | calls ; returns data_-&gt;proof; source comment (unverified): // Retain the exported certificate for independent replay; producer completion alone proves no · [reviewed contract](#b0064) |
| [B0065 · 640–645](../../../../../src/planner/exact.cpp#L640) | declares types or opens a type body. | source comment (unverified): // Own incremental witness copying while the frozen candidate retains all borrowed choices; · [reviewed contract](#b0065) |
| [B0066 · 646–646](../../../../../src/planner/exact.cpp#L646) | Callable definition: Impl(std::shared_ptr&lt;const BindingData&gt; b, std::shared_ptr&lt;const FrozenCandidate&gt; c) : binding(std::move(b)), candidate(std::move… | calls binding, std::move, candidate; source comment (unverified): // Capture binding and candidate owners without traversing the choice graph. See · [reviewed contract](#b0066) |
| [B0067 · 647–648](../../../../../src/planner/exact.cpp#L647) | Explanatory comments or spacing. | source comment (unverified): // Cancel copying frames before releasing their borrowed draft and candidate data. See · [reviewed contract](#b0067) |
| [B0068 · 649–649](../../../../../src/planner/exact.cpp#L649) | Callable definition: ~Impl() | calls cancel; source comment (unverified): // Cancel copying frames before releasing their borrowed draft and candidate data. See · [reviewed contract](#b0068) |
| [B0069 · 650–657](../../../../../src/planner/exact.cpp#L650) | declares values/defaults or compile-time conditions. | source comment (unverified): // Append a choice in preorder and link only existing parent IDs; keep the partial tree · [reviewed contract](#b0069) |
| [B0070 · 658–666](../../../../../src/planner/exact.cpp#L658) | Callable definition: Task append(const Choice* choice, std::optional&lt;NodeId&gt; parent) | calls size, operation, push_back, std::to_string; growth push_back; 1 loop sites; source comment (unverified): // Append a choice in preorder and link only existing parent IDs; keep the partial tree · [reviewed contract](#b0070) |
| [B0071 · 667–668](../../../../../src/planner/exact.cpp#L667) | Explanatory comments or spacing. | source comment (unverified): // Publish the concrete tree only after all choice copying finishes; its height claim still · [reviewed contract](#b0071) |
| [B0072 · 669–675](../../../../../src/planner/exact.cpp#L669) | Callable definition: Task main() | calls operation, SUBTASK, append; growth make_shared; source comment (unverified): // Publish the concrete tree only after all choice copying finishes; its height claim still · [reviewed contract](#b0072) |
| [B0073 · 676–678](../../../../../src/planner/exact.cpp#L676) | Closes surrounding scope/type. | source comment (unverified): // Allocate a witness shell retaining its binding and frozen candidate; copying starts on · [reviewed contract](#b0073) |
| [B0074 · 679–680](../../../../../src/planner/exact.cpp#L679) | Callable definition: WitnessMachine::WitnessMachine(std::shared_ptr&lt;const BindingData&gt; binding, std::shared_ptr&lt;const FrozenCandidate&gt; candidate) : da… | calls data_, std::move; growth make_unique; source comment (unverified): // Allocate a witness shell retaining its binding and frozen candidate; copying starts on · [reviewed contract](#b0074) |
| [B0075 · 681–691](../../../../../src/planner/exact.cpp#L681) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Release witness execution; any previously retained complete tree remains owned separately. · [reviewed contract](#b0075) |
| [B0076 · 692–702](../../../../../src/planner/exact.cpp#L692) | Callable definition: UnitResult WitnessMachine::step(const UnitContext& context) | calls empty, permits, main, std::move; returns {UnitEvent::witness_complete, 0}; {UnitEvent::depth_blocked, 1}; source comment (unverified): // Advance one saved witness transition and publish completion only after the draft is whole. · [reviewed contract](#b0076) |
| [B0077 · 703–704](../../../../../src/planner/exact.cpp#L703) | Explanatory comments or spacing. | source comment (unverified): // Read copier frame depth separately from tree native height. See · [reviewed contract](#b0077) |
| [B0078 · 705–705](../../../../../src/planner/exact.cpp#L705) | Callable definition: std::size_t WitnessMachine::current_depth() const noexcept | calls ; returns data_-&gt;e.administrative_only ? 0 : data_-&gt;e.depth; source comment (unverified): // Read copier frame depth separately from tree native height. See · [reviewed contract](#b0078) |
| [B0079 · 706–707](../../../../../src/planner/exact.cpp#L706) | Explanatory comments or spacing. | source comment (unverified): // Retain the complete candidate tree for P02 validation; copying alone gives no checked · [reviewed contract](#b0079) |
| [B0080 · 708–708](../../../../../src/planner/exact.cpp#L708) | Callable definition: std::shared_ptr&lt;const FreeConnexTree&gt; WitnessMachine::tree() const noexcept | calls ; returns data_-&gt;completed; source comment (unverified): // Retain the complete candidate tree for P02 validation; copying alone gives no checked · [reviewed contract](#b0080) |
| [B0081 · 709–710](../../../../../src/planner/exact.cpp#L709) | Member/declaration region. | source comment (unverified): // namespace crown::planner::continuation_detail · [reviewed contract](#b0081) |

## B0001

[Lines 1–14](../../../../../src/planner/exact.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Members = std::vector<std::size_t>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the occurrence-index sequence carried by search states and child partitions. |
| inputs / outputs | Values identify original atom positions; state and block builders append them in increasing order. |
| invariants | State members are nonempty, sorted and unique; equal scopes retain separate occurrence IDs. |
| ownership | Each vector owns its index storage; it does not retain the query. |
| failure | The alias enforces no validation; builders must preserve the sequence convention. |
| cost | Storage scales with member count; vector growth can allocate. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md) |

## B0002

[Lines 15–21](../../../../../src/planner/exact.cpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Key {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish exact subproblems by native members and the two structural context flags. |
| inputs / outputs | members selects the subtree; generalized permits a generalized root, and reachable records root membership in maximal connex C*. |
| invariants | Root starts with both flags true; children of native roots forbid generalized nodes; blocked exclusive head variables make a state infeasible. |
| ownership | Owns members and flags; memo keys are shared as const values after construction. |
| failure | Construction does not validate IDs or freeze mutable aliases; only internal builders may prepare keys. |
| cost | Key storage is linear in member count; map comparison can scan that vector. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md), [Refactor.md §5.1](../../../../../Refactor.md), [Refactor.md §5.4](../../../../../Refactor.md) |

```text
auto operator<=>(const Key&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Give memo states a value order independent of shared-pointer addresses. |
| inputs / outputs | Compares members first, then generalized and reachable flags. |
| invariants | Both flags remain part of key identity even when member sets match. |
| ownership | Borrows both keys for comparison and retains neither. |
| failure | Performs no structural validation; callers must avoid concurrent mutation. |
| cost | Lexicographic comparison is linear in the common member prefix; scalar flags follow only on a vector tie. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md) |

## B0003

[Lines 22–23](../../../../../src/planner/exact.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L23:sha256:476d749d496ebf5f4d0b0be67beba52dd1576fd529829d69c5ef7aa028a9d593
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for KeyLess: Order immutable memo keys by contents; shared ownership identity does not identify a state. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies KeyLess; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for KeyLess come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0004

[Lines 24–28](../../../../../src/planner/exact.cpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct KeyLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide content ordering for maps of shared immutable exact-state keys. |
| inputs / outputs | The comparator accepts shared Key handles and delegates to Key value ordering. |
| invariants | Equivalent keys may have different control blocks; pointees must exist and remain unchanged. |
| ownership | The stateless policy stores no key handles. |
| failure | Null handles or mutated published keys violate internal map preconditions. |
| cost | The comparator object has no per-state storage; each comparison has vector-prefix cost. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md) |

```text
bool operator()(const std::shared_ptr<const Key>& a, const std::shared_ptr<const Key>& b) const { return *a < *b; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two existing exact-state keys for ordered-container lookup. |
| inputs / outputs | Returns whether the dereferenced left Key precedes the right Key. |
| invariants | Non-null immutable keys are required throughout a map operation. |
| ownership | Borrows handles and pointees only for this comparison. |
| failure | No recovery or diagnostic is supplied for invalid pointers. |
| cost | May inspect every member in an equal-prefix vector; it does not build a replacement key. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md) |

## B0005

[Lines 29–30](../../../../../src/planner/exact.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L30:sha256:559f6737f2360a596ea511ab1f41bd12cb062dfc8d8fad0a3c6db810b176c19f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ScopeLess: Classify equal complete scopes while retaining all native IDs. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ScopeLess; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ScopeLess come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0006

[Lines 31–35](../../../../../src/planner/exact.cpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ScopeLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define complete-scope equality classes without merging atom occurrences. |
| inputs / outputs | Accepts shared variable sets for classes and native-root representative sets. |
| invariants | Ordering uses every normalized variable in a scope, including hidden variables. |
| ownership | The comparator owns no scopes; container entries retain their shared handles. |
| failure | Pointees must be non-null and must not change while used as ordered keys. |
| cost | Comparing set contents can traverse a shared variable prefix. |
| Design | [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md) |

```text
bool operator()(const std::shared_ptr<const VariableSet>& a, const std::shared_ptr<const VariableSet>& b) const { return *a < *b; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order two normalized scopes for representative selection and class lookup. |
| inputs / outputs | Returns lexicographic set order, rather than pointer order. |
| invariants | Scope equality includes the full variable set and ignores relation/alias identity only for this structural comparison. |
| ownership | Borrows both sets; it neither copies nor coalesces occurrences. |
| failure | Invalid or concurrently edited pointees violate the ordered-container contract. |
| cost | Worst-case comparison visits the smaller scope prefix before a difference or end. |
| Design | [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md) |

## B0007

[Lines 36–38](../../../../../src/planner/exact.cpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L38:sha256:3a791773990f68da329f21e670f9f253fb8d9895e40bfde2a746fcc89a684b07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Choice: A Choice is a producer witness, with null height for infeasibility; P02 must check a materialized tree before it supplies an upper bound. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Choice; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Choice come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0008

[Lines 39–45](../../../../../src/planner/exact.cpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Choice {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold a private recurrence witness or an infeasible-state sentinel. |
| inputs / outputs | height is a finite native-node height or null for infeasibility; kind, occurrence, scope and children describe a finite witness. |
| invariants | Completed records never change after publication. Generalized nodes cost zero and native nodes cost one; an infeasible sentinel has no usable witness. |
| ownership | Scope is shared; children are nonowning arena pointers. An arena-retaining owner must outlive every read. |
| failure | The default record has no finite height and is not independently checked upper authority. |
| cost | Owns one child-pointer vector and a shared scope handle; total storage depends on retained choices and edges. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [Refactor.md §5.1](../../../../../Refactor.md), [Refactor.md §5.4](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §3.2, Definitions 3.1–3.2 and native-height convention](https://arxiv.org/pdf/2301.04003v2), [P2 arXiv:2603.14754v1 §2.1.3; §2.1.4, Definition 2.14](https://arxiv.org/pdf/2603.14754v1) |

## B0009

[Lines 46–51](../../../../../src/planner/exact.cpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L51:sha256:aaa4828fef70fce21b3740c1d438e5b44f148f84ab0006fb7c91c30b9fe0e612
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ChoiceArena: Child edges never own their target. All records have stable addresses in a flat arena, so releasing a deep hierarchy uses vector iteration rather than recursively releasing shared child records. Draft records are private until publication; completed records are only exposed through const Choice*. Flat ownership keeps child pointers stable and teardown iterative over records. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ChoiceArena; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ChoiceArena come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0010

[Lines 52–69](../../../../../src/planner/exact.cpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ChoiceArena {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep choice addresses stable without recursive ownership along child edges. |
| inputs / outputs | Owns separately allocated Choice records in insertion order and returns their raw addresses. |
| invariants | Vector growth moves unique_ptr handles, not Choice payloads; completed graph edges stay valid. |
| ownership | The arena owns records flatly; FrozenCandidate shares arena lifetime independently of the producer. |
| failure | Allocation may fail before publication; arena append does not turn a draft into checked authority. |
| cost | One owning handle per retained record plus each record payload; final release iterates all retained records and their containers. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
Choice* append(std::unique_ptr<Choice>& prepared) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a prepared record into stable arena ownership. |
| inputs / outputs | Consumes a non-null unique_ptr on success and returns its unchanged payload address. |
| invariants | No candidate pointer is published until vector insertion succeeds. |
| ownership | The input owns the draft until push_back commits; the arena then owns it. |
| failure | On vector-growth failure, the noexcept unique_ptr move preserves the prepared record and existing arena entries. |
| cost | Amortized handle insertion; vector growth relocates existing handles and may allocate. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

```text
Choice* append() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create and retain a default choice for private assembly or infeasibility. |
| inputs / outputs | Returns a stable raw pointer whose height initially remains null. |
| invariants | The returned record is unpublished scratch until its caller finishes the required fields. |
| ownership | A local unique_ptr protects the new record until arena insertion commits. |
| failure | Object or vector allocation propagates; neither failure publishes a partial record. |
| cost | Allocates one Choice and may grow the owning-pointer vector. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0011

[Lines 70–71](../../../../../src/planner/exact.cpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L71:sha256:5072abc2470f45125b266a77a1332f7134bc5816011c62138cc4be5f378af388
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Metadata: Metadata stores U(S), boundary B(S) and exclusive head E(S) for one actual native subset. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Metadata; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Metadata come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0012

[Lines 72–72](../../../../../src/planner/exact.cpp#L72); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Metadata { VariableSet variables, boundary, private_head; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the inside union and the two port sets used by recurrence admissibility. |
| inputs / outputs | variables is U(S), boundary is B(S), and private_head is E(S). |
| invariants | An output starts empty and belongs to one actual member subset; private_head excludes boundary variables. |
| ownership | Owns all three variable sets independently of input scopes. |
| failure | It is scratch data, not a serialized claim or an independently checked lower bound. |
| cost | Set storage scales with variables present in the subset; inserts may allocate. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md) |

## B0013

[Lines 73–77](../../../../../src/planner/exact.cpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#define SUBTASK(expression) do { co_await operation([&] { task = (expression); }, e.depth + 1); co_await task; } while (false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Schedule coroutine-frame creation as a retryable operation before awaiting the child. |
| inputs / outputs | Uses the enclosing Engine e and reusable Task task; expression constructs the next owned child coroutine. |
| invariants | Depth permission is checked before creation; child allocation executes outside resume so failure cannot unwind the suspended parent. |
| ownership | The enclosing frame owns task and referenced operands until the child returns or cancellation detaches frames. |
| failure | Child construction may throw from the pending operation; the same operation stays pending for retry. |
| cost | Adds controlled scheduling transitions and one child frame; it does not meter allocator or map-comparison CPU work. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0014

[Lines 78–81](../../../../../src/planner/exact.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task copy_members(Engine&, const Members& source, Members& dest) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append an occurrence sequence through resumable reserve and single-element operations. |
| inputs / outputs | Borrows source and appends every member to dest without clearing it; callers use empty fresh state vectors. |
| invariants | Source order is preserved; source and destination must not alias or change independently while suspended. |
| ownership | The coroutine borrows both vectors; its caller retains them across every yield. |
| failure | Reserve or push allocation propagates at a saved operation; completed prefix remains and the failed append is retried. |
| cost | One reserve and one append per source member, plus scheduling; reserve can relocate existing destination elements. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0015

[Lines 82–83](../../../../../src/planner/exact.cpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L83:sha256:a63247eff4cc4cf88ae93beec2109fd743278a9da2d002befe9e77c8ae9f3f95
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for copy_scope: Union a stable source scope into retained scratch one variable per pending operation. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies copy_scope; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for copy_scope come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0016

[Lines 84–86](../../../../../src/planner/exact.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task copy_scope(Engine&, const VariableSet& source, VariableSet& dest) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert scope members into a retained destination at saved operation boundaries. |
| inputs / outputs | Borrows source and unions its variables into dest; it does not erase existing members. |
| invariants | Insertion is idempotent; source iteration must remain stable across yields. |
| ownership | The caller owns both sets and keeps them alive until this task finishes. |
| failure | An allocating set insert may throw while the same variable remains the next operation. |
| cost | One ordered-set insertion per source variable, with logarithmic lookup and possible node allocation. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0017

[Lines 87–88](../../../../../src/planner/exact.cpp#L87); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L87-L88:sha256:5a246ff527af7842178178ec49b20b0060f674158195742282b4abf4c57566a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for contains: Test required ⊆ scope with an early missing-variable exit. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies contains; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for contains come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0018

[Lines 89–95](../../../../../src/planner/exact.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task contains(Engine&, const VariableSet& scope, const VariableSet& required, bool& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test the subset condition required by ports, guards and connex reachability. |
| inputs / outputs | Sets result true initially, then false at the first required variable missing from scope. |
| invariants | Empty required succeeds; both sets remain stable across suspension. |
| ownership | Borrows both sets and the caller-owned result slot. |
| failure | This lookup path produces no semantic diagnostic; set lifetime and valid references are caller preconditions. |
| cost | At most one set lookup per required variable, stopping early; comparison work follows ordered-set lookup. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0019

[Lines 96–97](../../../../../src/planner/exact.cpp#L96); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L97:sha256:324af0e1259cb8133e7a4c89c61a0c7c1044fdd2bbe1a983cac6ff3afe6d79ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for copy_tree: Copy a checked tree into fresh certificate scratch, preserving node indices and optional claims through saved operations. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies copy_tree; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for copy_tree come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0020

[Lines 98–118](../../../../../src/planner/exact.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task copy_tree(Engine& e, const FreeConnexTree& source, FreeConnexTree& target) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an owning certificate-tree copy without hiding a bulk traversal in one resume. |
| inputs / outputs | Copies node identity, kinds, full scopes, edges, occurrence IDs and optional claims into a fresh empty target. |
| invariants | Node order is unchanged so root and child IDs remain valid; source and target must be distinct and source immutable. |
| ownership | The caller owns target scratch; source remains alive through the checked upper handle. |
| failure | Any allocating copy may stop with a private prefix; saved operations retry before publication. |
| cost | Work and storage scale with nodes, scope cells, child edges, IDs and optional claim cells; string/container costs remain separate. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [include/crown/ir/tree.hpp](../../../../../include/crown/ir/tree.hpp) |

## B0021

[Lines 119–121](../../../../../src/planner/exact.cpp#L119); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L121:sha256:5d7fade4d90e4d885657cf07f03cbfe97610a1d7060dd614f1020aa0d89ec3da
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous namespace. The following note asks the witness builder to retain the ChoiceArena while reading the completed root; the resulting candidate is not checked authority. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0022

[Lines 122–125](../../../../../src/planner/exact.cpp#L122); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FrozenCandidate {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a completed producer choice graph while a separate machine materializes it. |
| inputs / outputs | Carries an arena owner and one non-null completed root pointer. |
| invariants | The reachable choice records are immutable; arena growth after acknowledgment does not move their payloads. |
| ownership | Shares the arena so the candidate can outlive the producer; root and child links borrow arena records. |
| failure | A frozen candidate establishes no P02 validity or lower-bound authority. |
| cost | Publishing a wrapper allocates a control block; copying its shared handle changes ownership without copying the graph. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0023

[Lines 126–131](../../../../../src/planner/exact.cpp#L126); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProducerMachine::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the saved exact-search recurrence, scratch, memo and publication handshake. |
| inputs / outputs | Consumes an immutable admitted binding; produces frozen candidates and an unverified complete v2 certificate. |
| invariants | Only solved or soundly dominated states enter choices; pending freezes producer progress until witness validation is acknowledged. |
| ownership | Owns Engine/Task frames, scope classes, components and arena; shares checked upper and complete proof artifacts. |
| failure | Allocation escapes from saved operations for facade retry; cancelled frames must be detached before members are destroyed. |
| cost | Retains exponentially many possible states/choices plus preprocessing and export scratch; grants meter transitions, not total bytes. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0024

[Lines 132–132](../../../../../src/planner/exact.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Impl(std::shared_ptr<const BindingData> b) : binding(std::move(b)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture the immutable admitted query without starting search work. |
| inputs / outputs | Moves a non-null BindingData shared handle into the inert producer implementation. |
| invariants | Preprocessing, root creation and coroutine execution wait for step. |
| ownership | Shares the complete input snapshot rather than borrowing caller catalog/query objects. |
| failure | The constructor assumes admission already validated the binding; it does not issue null-input diagnostics. |
| cost | Initializes empty member containers and transfers one handle; the outer make_unique supplies implementation storage. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0025

[Lines 133–134](../../../../../src/planner/exact.cpp#L133); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L134:sha256:bf4410d18fa6ad750ac1595bc114d3a2366ef1b278bd57d25495c65b47e4d72e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for cancel: Cancel live frames before Task/member destruction; retained candidates keep their own arena ownership. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies cancel; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for cancel come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0026

[Lines 135–135](../../../../../src/planner/exact.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Impl() { e.cancel(); }
  std::shared_ptr<const BindingData> binding;
  Engine e;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach and destroy live producer coroutine frames before ordinary member teardown. |
| inputs / outputs | Destruction cancels active Engine frames and then lets owned search state release normally. |
| invariants | Leaf-to-root cancellation clears each Task owner before destroying its frame, avoiding a recursive Task chain. |
| ownership | Releases only this producer ownership; independently retained candidates and checked artifacts stay alive. |
| failure | Cancellation is noexcept and carries no feasibility or optimum meaning. |
| cost | Cancellation visits live frames; final member release can also visit memo entries, arena records and variable containers. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0027

[Lines 136–156](../../../../../src/planner/exact.cpp#L136); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L156:sha256:083a72554cc572fa24a4e0260ed56fe4e0bf004382eabe28275eaec200bf3eac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain binding, e, run, phase, stats, scopes, head, totals, classes, components, choices, arena, pending, upper, proof, draft, root, selected in ProducerMachine::Impl across its lifetime. Attached note: Derive ports from full native scopes and global occurrence totals, never from output projections. |
| inputs / outputs | These are stored fields for ProducerMachine::Impl, not callable parameters or results; constructors and later methods set or consume them. |
| invariants | The fields preserve the named machine or owner state between calls; counters, cursors, and stored claims remain data until adjacent methods update or validate them. |
| ownership | shared_ptr members retain their pointees through shared ownership; this span does not deep-copy them; containers and strings own their elements or bytes; Task members own coroutine frames; an Engine active handle is a non-owning traversal reference. The choices map values and selected pointer are non-owning Choice pointers into the retained ChoiceArena. That arena owns records through vector&lt;unique_ptr&lt;Choice&gt;&gt;; these pointers must not outlive or survive release of their backing arena. |
| failure | The declarations add no exception path by themselves. Constructing owner/container members or growing them later can fail through the surrounding object-creation or update path. |
| cost | Adds fixed per-instance storage for the listed values and owner/container handles; container payloads allocate or grow only as the machine prepares state; shared_ptr members retain shared payloads without a deep copy at this declaration; coroutine frame work occurs when the task is created or resumed. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0028

[Lines 157–168](../../../../../src/planner/exact.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task metadata(const Members& members, Metadata& out) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive U(S), B(S) and E(S) from actual member incidences. |
| inputs / outputs | For sorted valid members and fresh Metadata out, counts each variable once per normalized native scope. |
| invariants | count &lt; totals marks a boundary variable; only globally exclusive head variables enter private_head. |
| ownership | Borrows state members and scopes; owns a local count map and fills caller-owned scratch. |
| failure | Map/set allocation is retryable at pending operations; totals.at assumes preprocessing established every variable total. |
| cost | Scans member-scope incidences and performs ordered map/set operations; repeats metadata work for different partitions. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0029

[Lines 169–170](../../../../../src/planner/exact.cpp#L169); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L169-L170:sha256:3776ba562685b09e65dcadbfc228a7143ac97aca16a7ad2abc9ce0db2a9e8b22
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for publish: Publish an arena-retaining root candidate only after its wrapper is ready. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies publish; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for publish come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0030

[Lines 171–178](../../../../../src/planner/exact.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task publish(const Choice* choice) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one completed root choice for independent tree materialization. |
| inputs / outputs | Wraps a completed arena-resident choice in pending; the outer facade will request its concrete tree. |
| invariants | The wrapper is prepared privately before pending changes; publication does not validate the choice. |
| ownership | The frozen wrapper shares arena ownership and borrows the root address within it. |
| failure | Wrapper allocation can fail while preserving previous pending state and the completed choice. |
| cost | One wrapper/control-block allocation and shared-handle transfers; no tree traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0031

[Lines 179–180](../../../../../src/planner/exact.cpp#L179); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L179-L180:sha256:d29477b78a04e911fcdf6d6647061cc349ce6546fd600bc26c1397617dc39ed6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for consider: Keep strict improvements only; prune with native root cost and safe child lower bounds, never with residual rounds or cost scores. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies consider; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for consider come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0032

[Lines 181–215](../../../../../src/planner/exact.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task consider(const std::shared_ptr<const Key>& key, NodeKind kind,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Solve child states for one admissible root/partition and retain a strict height improvement. |
| inputs / outputs | Uses key context, root scope and disjoint blocks; updates best only after a finite candidate is complete. |
| invariants | Child reachability is parent reachability and B(child) ⊆ head. Prunes use native cost plus universal child one or completed exact child maxima; equal-height ties may be skipped. |
| ownership | Owns a private Choice until arena commit; completed child pointers borrow the retained arena. |
| failure | Infeasible children discard only this option. Allocation retries retain the prior best; no cutoff is memoized as infeasible. |
| cost | May recursively solve every child and allocate a record/edge vector; branch-and-bound reduces explored alternatives but gives no polynomial guarantee. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md), [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0033

[Lines 216–217](../../../../../src/planner/exact.cpp#L216); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L216-L217:sha256:aa7830d2292b32c0004afc72e74c8bc33876385a5aa422742d0b3320dbdef433
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for inspect_partition: Check native ports or derive the unique normalized generalized scope from child unions before considering a partition. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies inspect_partition; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for inspect_partition come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0034

[Lines 218–256](../../../../../src/planner/exact.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task inspect_partition(const std::shared_ptr<const Key>& key, const Metadata& meta,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Filter one branch partition by boundary and generalized-guard conditions. |
| inputs / outputs | For a native occurrence, checks each child boundary in that scope; otherwise derives G from variables in at least two child unions. |
| invariants | Generalized roots require at least two blocks, B(S) ⊆ G and G ⊆ every child union. This determines the normalized scope; arbitrary pairwise atom intersections are insufficient. |
| ownership | Partition and metadata are borrowed; generalized-scope and incidence scratch are private to this task. |
| failure | An inadmissible partition returns without changing best; allocating scratch operations remain retryable. |
| cost | Repeatedly derives child metadata and incidence counts; cost depends on all block scopes and ordered-container operations. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md), [Refactor.md §5.4](../../../../../Refactor.md) |

## B0035

[Lines 257–258](../../../../../src/planner/exact.cpp#L257); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L257-L258:sha256:1ecde80c157b90c50386a35d97695123c336f2c7a431375350b8b5d7dd0bcab8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for partitions: Enumerate partitions by ordered insertion; return early only at the universal nonempty lower bound one. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies partitions; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for partitions come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0036

[Lines 259–276](../../../../../src/planner/exact.cpp#L259); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task partitions(const std::shared_ptr<const Key>& key, const Metadata& meta,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate every unordered partition through insertion into existing or one new block. |
| inputs / outputs | Advances position through sorted members and mutates a caller-retained blocks stack around recursive tasks. |
| invariants | Existing blocks receive the next member in order; one new block follows them. Each partition occurs once; height one safely ends any remaining search for a nonempty state. |
| ownership | Borrows members, key, metadata, blocks and best across suspension; recursive frames retain these lifetimes. |
| failure | Each allocating insertion is a saved operation. A suspended or allocation-blocked subtree cannot be treated as a completed partition. |
| cost | Bell-number partition growth in member count, with O(member count) logical recursion before child-solving frames; block vectors may allocate. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0037

[Lines 277–279](../../../../../src/planner/exact.cpp#L277); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L277-L279:sha256:d6e6cf9d5bb76caf4597b2a5e7bac887b98df76703c727f634faeb19e30e579c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for solve: Memoize only complete state optima; component, symmetry and incumbent rules preserve one optimum. A resource stop never creates an infeasible memo value. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies solve; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for solve come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0038

[Lines 280–335](../../../../../src/planner/exact.cpp#L280); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task solve(std::shared_ptr<const Key> key, const Choice*& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the exact normalized-family optimum or infeasibility for one state. |
| inputs / outputs | Returns an arena pointer through result; consults completed memo entries and otherwise explores native and permitted generalized roots. |
| invariants | Blocked E(S) states are infeasible. Equal complete-scope native roots need one representative. Full-root disconnected components combine by maximum; memo publication follows full proof-preserving exploration/pruning. |
| ownership | Owns a shared immutable key while suspended; result points into the producer arena. |
| failure | Null height denotes completed infeasibility, not a resource stop. Allocation failure leaves the state unpublished and retryable. |
| cost | Subset memoization and symmetry reduce repetition but total recurrence/partition work remains exponential in query size. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md), [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md), [Refactor.md §5.4](../../../../../Refactor.md), [Refactor.md §11.3 P03–P04](../../../../../Refactor.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0039

[Lines 336–337](../../../../../src/planner/exact.cpp#L336); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L336-L337:sha256:00af0dabe2c6a6dbe8bfae4c0df10cdb3f7c51b7cdf5fefe8c2243215ecf985a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for preprocess: Build full scopes, equal-scope classes and variable-sharing components while preserving every original occurrence. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies preprocess; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for preprocess come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0040

[Lines 338–380](../../../../../src/planner/exact.cpp#L338); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task preprocess() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive normalized scopes, variable totals, complete-scope classes and occurrence components. |
| inputs / outputs | Reads every atom term and head variable; appends one scope per original atom and sorted member vectors for each class/component. |
| invariants | Only VariableId terms contribute incidences; repeated positions count once per scope. Union/find joins occurrences sharing a variable; nullary occurrences remain separate. |
| ownership | Owns union/find and grouping scratch while filling retained producer structures. |
| failure | Allocations occur before semantic cursor progress. Component capacity is reserved before moving its owned member vector so retry retains its source. |
| cost | Includes term scans, map/set operations and uncompressed union/find parent walks; it has no inverse-Ackermann complexity claim. |
| Design | [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0041

[Lines 381–383](../../../../../src/planner/exact.cpp#L381); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L381-L383:sha256:35c6cb17a48c4786e0a0ddc3633647b4e9452309aa02e5e44191174c5259cf80
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for hierarchy: Recognize laminar incidence classes with free-variable upward closure; a hit constructs an upper candidate at height one, then P02 checks it. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies hierarchy; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for hierarchy come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0042

[Lines 384–498](../../../../../src/planner/exact.cpp#L384); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task hierarchy(const Choice*& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize the laminar incidence/head condition and construct a height-one candidate. |
| inputs / outputs | Groups equal variable occurrence sets, orders groups by descending size and attaches native leaves below their smallest containing group. |
| invariants | Overlapping incidence sets must nest; a free proper child under a hidden ancestor rejects recognition. Equal incidence classes may mix free and hidden variables. Failure falls through to solve. |
| ownership | Owns incidence/group scratch and appends choice nodes to the retained arena; result is assigned only for a completed candidate. |
| failure | Non-hierarchy returns with no result, not infeasibility. Allocation failures retry at saved operations; P02 still checks every emitted candidate. |
| cost | Uses insertion sorting of groups, pairwise group overlap/subset tests and scans of occurrence membership; polynomial preprocessing can still be substantial for wide queries. |
| Design | [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [Refactor.md §11.3 P04](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §3.2, q-hierarchical definition; Appendix C, proof of Lemma 6.8](https://arxiv.org/pdf/2301.04003v2), [P2 arXiv:2603.14754v1 §2.1.4, q-hierarchical definition](https://arxiv.org/pdf/2603.14754v1) |

```text
struct Group {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold one equal-incidence class while building the laminar hierarchy forest. |
| inputs / outputs | members identifies occurrences; variables holds that class; free/hidden classify its variables; parent and node track construction. |
| invariants | Groups are sorted by nonincreasing incidence size before parent discovery, so a selected strict parent has already constructed its node. |
| ownership | Shares immutable incidence members, owns its variable set and borrows an arena node once created. |
| failure | A group is private scratch; unset parent/node means forest root or an unmaterialized singleton class, not an invalid public plan. |
| cost | Storage scales with incidence and variable memberships, plus one optional parent and pointer. |
| Design | [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md) |

```text
struct MemberLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group hierarchy variables by equal occurrence-incidence vectors. |
| inputs / outputs | Orders shared Members values for the incidence-class map. |
| invariants | Incidence vectors are sorted by original atom scan order and stay unchanged after grouping begins. |
| ownership | The stateless comparator retains no incidence owners. |
| failure | Null or mutated incidence vectors violate its ordered-map precondition. |
| cost | Comparison can scan an entire common incidence prefix. |
| Design | [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md) |

```text
bool operator()(const std::shared_ptr<const Members>& a, const std::shared_ptr<const Members>& b) const { return *a < *b; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two variable incidence sets during hierarchy grouping. |
| inputs / outputs | Returns the lexicographic order of their occurrence sequences. |
| invariants | Distinct variables with equal incidence compare equivalent and share a Group. |
| ownership | Borrows non-null incidence vectors for the duration of lookup. |
| failure | Does not validate sorting or generate an error report. |
| cost | Linear in the compared vector prefix; no incidence copy. |
| Design | [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md) |

## B0043

[Lines 499–501](../../../../../src/planner/exact.cpp#L499); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L499-L501:sha256:d89532d767e6b9308f8e16440a5752df5abd860b4914f6ce395cc143bca93751
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for export_proof: Export complete memo claims and a matching independently checked upper; this producer certificate still requires independent replay. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies export_proof; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for export_proof come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0044

[Lines 502–555](../../../../../src/planner/exact.cpp#L502); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task export_proof() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble a query-bound v2 certificate from the final choice and complete memo states. |
| inputs / outputs | Copies a matching P02-checked upper tree when finite, canonicalizes equal-scope orbit keys, and exports lower-bound entries. |
| invariants | Finite final height requires checked upper with identical binding ownership and height. Canonical duplicate states must agree; both flags and class multiplicities are retained. |
| ownership | Owns draft and canonical scratch; proof becomes visible only after all tree/claim copying completes. |
| failure | Missing matching upper throws invalid_search_witness; orbit disagreement throws invalid_search_proof. These are invariant failures, while allocation remains retryable. |
| cost | Copies tree payloads and all canonical member vectors, scanning each memo state against scope classes with additional ordered-map/vector insertion costs. |
| Design | [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md), [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [Refactor.md §5.5](../../../../../Refactor.md), [Refactor.md §11.3 P06](../../../../../Refactor.md) |

## B0045

[Lines 556–557](../../../../../src/planner/exact.cpp#L556); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L556-L557:sha256:1d584457edf6a425ba10b83e23e651d674440260f6451811e382c07e83c8c424
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for main: Drive the structural routes and export only after the final candidate has a checked upper; empty body alone has height zero. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies main; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for main come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0046

[Lines 558–587](../../../../../src/planner/exact.cpp#L558); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task main() {
    Task task;
    phase = SearchPhase::preprocess;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive empty, singleton, hierarchy and full exact search routes into proof export. |
| inputs / outputs | Creates arena/root lazily, publishes completed root candidates and finally exports the complete certificate. |
| invariants | Empty body alone uses height zero and no lower-state table. Every nonempty fast path has a root claim of one; unsuccessful hierarchy invokes full solve. |
| ownership | The retained producer implementation owns all route scratch and coroutine frames. |
| failure | Finite candidate publication pauses in the outer handshake before export; resource failures leave this route suspended without optimum authority. |
| cost | The selected route determines work: administrative empty handling, polynomial recognition, or exponential recurrence plus export and later replay. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [Refactor.md §5.4 Complete exact oracle and fallback](../../../../../Refactor.md), [Refactor.md §11.3 P03–P06](../../../../../Refactor.md) |

## B0047

[Lines 588–591](../../../../../src/planner/exact.cpp#L588); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L588-L591:sha256:e96d3dcff312b824f62600c23e5dde72edb7d4e1821dfdf3551def499544fd6e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. Its attached note introduces nearby behavior: Allocate an inert producer shell around the owned binding; step starts work. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0048

[Lines 592–592](../../../../../src/planner/exact.cpp#L592); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ProducerMachine::ProducerMachine(std::shared_ptr<const BindingData> binding) : data_(std::make_unique<Impl>(std::move(binding))) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an inert move-only producer around an admitted immutable binding. |
| inputs / outputs | Accepts a non-null owned binding and allocates implementation storage; first step begins execution. |
| invariants | No preprocessing, state exploration or candidate validation occurs in construction. |
| ownership | Owns Impl exclusively and shares the binding snapshot. |
| failure | Implementation allocation can throw before a machine exists; invalid null binding is outside the private protocol. |
| cost | One implementation allocation with empty search containers; input data are not recopied. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0049

[Lines 593–603](../../../../../src/planner/exact.cpp#L593); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ProducerMachine::~ProducerMachine() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release producer execution while permitting retained candidates/artifacts to survive. |
| inputs / outputs | Destroys the exclusive implementation, whose destructor cancels live coroutine frames first. |
| invariants | Destruction does not publish feasibility, infeasibility or a completed proof. |
| ownership | Drops this machine ownership; external shared candidates retain the arena they need. |
| failure | Destructor is nonthrowing under the owned standard-container element contracts. |
| cost | Visits active frames and any retained state whose last ownership is released; cost can scale with the explored search. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

```text
ProducerMachine::ProducerMachine(ProducerMachine&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer an entire saved producer to a new exclusive wrapper. |
| inputs / outputs | Moves the unique implementation pointer; the source becomes empty. |
| invariants | Internal frame and choice addresses stay unchanged; methods require a nonempty wrapper. |
| ownership | Ownership transfers without copying query, memo or coroutine state. |
| failure | Noexcept move; only destruction or reassignment is valid on the moved-from private machine. |
| cost | Transfers one unique pointer and performs no traversal. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

```text
ProducerMachine& ProducerMachine::operator=(ProducerMachine&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one producer owner with another saved producer. |
| inputs / outputs | Default unique_ptr move assignment returns the destination wrapper. |
| invariants | Any previous destination execution is cancelled through Impl destruction before replacement ownership completes. |
| ownership | Transfers the source implementation; candidate handles outside both wrappers retain their own ownership. |
| failure | Noexcept assignment; methods still require a nonempty destination afterward. |
| cost | Transfer itself is a pointer operation, but replacing a live destination may tear down all its frames and retained state. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0050

[Lines 604–618](../../../../../src/planner/exact.cpp#L604); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UnitResult ProducerMachine::step(const UnitContext& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one producer scheduler transition or report its pending publication boundary. |
| inputs / outputs | Returns candidate_ready, producer_complete, depth_blocked or advanced; creates the main coroutine lazily. |
| invariants | Pending candidate/proof events are observed before more work. Nonempty initialization checks depth one; empty administrative work uses logical depth zero. |
| ownership | Mutates the exclusively owned Impl; returned events borrow no mutable internals. |
| failure | Allocation from main construction or a pending operation propagates to the facade with the next semantic operation retained. |
| cost | One scheduler transition can perform an ordered-container operation and resume nonallocating control flow; it is not a hard CPU-time bound. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0051

[Lines 619–620](../../../../../src/planner/exact.cpp#L619); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L619-L620:sha256:aa9cef237b3a2a0f2cec3faf90ed4d61c285ee22a0f6ed863d9f50f2a6eea041
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ProducerMachine: Read producer progress only; phase alone carries no minimum authority. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ProducerMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ProducerMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0052

[Lines 621–621](../../../../../src/planner/exact.cpp#L621); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchPhase ProducerMachine::phase() const noexcept { return data_->phase; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe the producer progress phase without advancing search. |
| inputs / outputs | Returns the stored SearchPhase of a non-moved machine. |
| invariants | Phase describes producer progress, not independently verified optimum authority. |
| ownership | Returns a scalar copy; the machine retains all state. |
| failure | Noexcept getter; non-null data_ is a private caller precondition. |
| cost | One scalar read; no traversal or publication. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0053

[Lines 622–623](../../../../../src/planner/exact.cpp#L622); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L622-L623:sha256:642b3307e0047057661c14b1dc52d26b20d8b7a01351e3b420ed6de630b37fa2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ProducerMachine: Borrow producer counters while the machine lives; counters provide progress evidence, not lower bounds. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ProducerMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ProducerMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0054

[Lines 624–624](../../../../../src/planner/exact.cpp#L624); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SearchStatistics& ProducerMachine::statistics() const noexcept { return data_->stats; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose structural counters to the owning facade. |
| inputs / outputs | Returns a const reference to this producer statistics object. |
| invariants | Counts describe executed producer routes; they do not replace lower-bound proof. |
| ownership | Borrows machine storage and is invalid after implementation destruction/replacement. |
| failure | Noexcept getter with a live nonempty-machine precondition. |
| cost | Returns a reference without copying containers or collecting fresh statistics. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0055

[Lines 625–626](../../../../../src/planner/exact.cpp#L625); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L625-L626:sha256:1039a0403b8829d4b9ec761b196d6ea78b97ccf79734fda1e30c08ac07c0b8de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ProducerMachine: Report logical coroutine depth, with zero for empty administrative or completed work. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ProducerMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ProducerMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0056

[Lines 627–627](../../../../../src/planner/exact.cpp#L627); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ProducerMachine::current_depth() const noexcept { return data_->proof || data_->e.administrative_only ? 0 : data_->e.depth; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report current producer logical frame depth for resource accounting. |
| inputs / outputs | Returns zero for completed proof or administrative empty work, otherwise Engine depth. |
| invariants | This is owned-frame depth, separate from native tree height. |
| ownership | Returns a scalar while retaining Engine ownership. |
| failure | Noexcept; requires a live non-moved implementation. |
| cost | Constant-size flag/depth reads; no frame scan. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0057

[Lines 628–629](../../../../../src/planner/exact.cpp#L628); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L628-L629:sha256:5e0b7f5bed0cbbb82804fd3fa744c496c4013c5f4777039330405a8c474ca845
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ProducerMachine: Retain the pending arena-backed candidate for witness construction and P02 validation. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ProducerMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ProducerMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0058

[Lines 630–630](../../../../../src/planner/exact.cpp#L630); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const FrozenCandidate> ProducerMachine::candidate() const noexcept { return data_->pending; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the pending candidate across witness creation and validation. |
| inputs / outputs | Returns the pending immutable wrapper handle, or null when no candidate awaits acknowledgment. |
| invariants | The root graph remains completed and unchanged; the handle supplies no independent validity. |
| ownership | The returned owner retains the choice arena beyond machine lifetime. |
| failure | Noexcept shared-handle copy; requires live data_. |
| cost | Copies a shared ownership handle without materializing the tree. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0059

[Lines 631–632](../../../../../src/planner/exact.cpp#L631); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L631-L632:sha256:4cbca8da9c60b746413daadb1f74eb11f4559eeb4f17192548debbad9af6cd75
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for std: Accept only facade-supplied P02 authority; final export checks its binding and selected height. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies std; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for std come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0060

[Lines 633–633](../../../../../src/planner/exact.cpp#L633); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ProducerMachine::accept_upper(std::shared_ptr<const CheckedUpper> upper) noexcept { data_->upper = std::move(upper); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install independently checked upper authority from the facade handshake. |
| inputs / outputs | Moves a CheckedUpper handle into the producer for final export matching. |
| invariants | Caller supplies authority from ValidationMachine for this binding; export separately checks final binding identity and height. |
| ownership | Shares the checked tree/report through the new handle and releases any previous upper owner. |
| failure | Noexcept transfer; this setter performs no validation and cannot itself certify a minimum. |
| cost | Handle replacement is small, but dropping the last previous upper may release its tree/report payload. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0061

[Lines 634–635](../../../../../src/planner/exact.cpp#L634); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L634-L635:sha256:d0c431228737c4210bcc2779b5ce8362e0216b99cb1065fc0b606ab726c0759a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for reset: Clear pending only after checked-upper publication succeeds, then resume exact search. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies reset; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for reset come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0062

[Lines 636–636](../../../../../src/planner/exact.cpp#L636); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ProducerMachine::acknowledge_candidate() noexcept { data_->pending.reset(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow producer execution to continue after independent candidate processing. |
| inputs / outputs | Resets the pending wrapper; the facade calls this after checked-upper publication succeeds. |
| invariants | Acknowledgment must follow materialization, P02 validation and incumbent-owner preparation, preserving the previous public upper on failure. |
| ownership | Releases the producer pending owner; witness/facade handles can keep the candidate arena alive. |
| failure | Noexcept reset; it is a private sequencing operation, not a proof check. |
| cost | Wrapper release can destroy its control block; the producer normally still retains the arena. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp) |

## B0063

[Lines 637–638](../../../../../src/planner/exact.cpp#L637); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L637-L638:sha256:1268cf35b842331f3e1ca76e9ddc01b60e6168c73bfd902247218d59d164e73a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ProducerMachine: Retain the exported certificate for independent replay; producer completion alone proves no public optimum. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ProducerMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ProducerMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0064

[Lines 639–639](../../../../../src/planner/exact.cpp#L639); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const HeightCertificate> ProducerMachine::completed_proof() const noexcept { return data_->proof; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the completed producer certificate for independent replay. |
| inputs / outputs | Returns null before export completion, otherwise an owning immutable certificate handle. |
| invariants | Producer completion alone grants neither VerifiedOptimum nor VerifiedInfeasible. |
| ownership | The returned shared owner keeps all certificate tree/state payloads alive. |
| failure | Noexcept shared-handle copy; requires a nonempty machine. |
| cost | Copies ownership only; no certificate traversal or validation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0065

[Lines 640–645](../../../../../src/planner/exact.cpp#L640); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WitnessMachine::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own incremental conversion from a frozen choice graph to a concrete tree. |
| inputs / outputs | Retains admitted binding and candidate; produces a complete immutable FreeConnexTree handle. |
| invariants | Construction copies producer structure but does not check Cover/Connect/Guard/Above/Connex independently. |
| ownership | Owns Engine/Task frames and draft; candidate ownership keeps every borrowed Choice pointer alive. |
| failure | Allocation can suspend materialization without exposing draft; destruction must cancel frames first. |
| cost | Retains one concrete tree plus active traversal frames and candidate arena ownership; work scales with exported graph cells. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0066

[Lines 646–646](../../../../../src/planner/exact.cpp#L646); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Impl(std::shared_ptr<const BindingData> b, std::shared_ptr<const FrozenCandidate> c) : binding(std::move(b)), candidate(std::move(c)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture immutable inputs for deferred witness materialization. |
| inputs / outputs | Moves non-null binding and frozen candidate handles into an inert implementation. |
| invariants | The candidate belongs to the same producer/query protocol; copying starts only on step. |
| ownership | Shares binding and arena-retaining candidate; no caller objects are borrowed. |
| failure | Private caller must supply a valid candidate/root; constructor does not validate the tree. |
| cost | Two handle transfers and empty draft/frame initialization; outer implementation storage allocates. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0067

[Lines 647–648](../../../../../src/planner/exact.cpp#L647); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L647-L648:sha256:e518133dd289111e36e11b21a4abfa93f1e4bfa7c94ec80e87d276bcc73a5d12
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for cancel: Cancel copying frames before releasing their borrowed draft and candidate data. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies cancel; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for cancel come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0068

[Lines 649–649](../../../../../src/planner/exact.cpp#L649); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Impl() { e.cancel(); }
  std::shared_ptr<const BindingData> binding;
  std::shared_ptr<const FrozenCandidate> candidate;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach live witness-copy coroutine frames before releasing referenced drafts and candidates. |
| inputs / outputs | Destructor invokes iterative Engine cancellation before member teardown. |
| invariants | Frame borrows into draft/candidate never survive their owning implementation. |
| ownership | External completed-tree handles and candidate owners survive this machine release. |
| failure | Noexcept cancellation does not publish an invalid or partial tree. |
| cost | Visits active frames; final draft or arena release can traverse their payloads. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0069

[Lines 650–657](../../../../../src/planner/exact.cpp#L650); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L650-L657:sha256:9aa4bca2854334e29af90ed10a90cd0c322777c8c3b4c9451bd38a4fa402ea64
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain binding, candidate, e, run, draft, completed in WitnessMachine::Impl across its lifetime. Attached note: Append a choice in preorder and link only existing parent IDs; keep the partial tree private until copying completes. |
| inputs / outputs | These are stored fields for WitnessMachine::Impl, not callable parameters or results; constructors and later methods set or consume them. |
| invariants | The fields preserve the named machine or owner state between calls; counters, cursors, and stored claims remain data until adjacent methods update or validate them. |
| ownership | shared_ptr members retain their pointees through shared ownership; this span does not deep-copy them; Task members own coroutine frames; an Engine active handle is a non-owning traversal reference. |
| failure | The declarations add no exception path by themselves. Constructing owner/container members or growing them later can fail through the surrounding object-creation or update path. |
| cost | Adds fixed per-instance storage for the listed values and owner/container handles; shared_ptr members retain shared payloads without a deep copy at this declaration; coroutine frame work occurs when the task is created or resumed. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0070

[Lines 658–666](../../../../../src/planner/exact.cpp#L658); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task append(const Choice* choice, std::optional<NodeId> parent) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one choice subtree to the concrete witness in deterministic preorder. |
| inputs / outputs | Assigns the next node index/ID, copies scope and occurrence metadata, links parent, then visits children. |
| invariants | Parent IDs refer to already appended nodes; completed child pointers remain arena-valid across yields. |
| ownership | Borrows choices through the retained candidate and mutates only private draft storage. |
| failure | Node string/vector/set allocations execute as saved operations; a partial node remains private during retry. |
| cost | One node plus scope and child-link work per visited choice, with a coroutine stack proportional to witness depth. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [include/crown/ir/tree.hpp](../../../../../include/crown/ir/tree.hpp) |

## B0071

[Lines 667–668](../../../../../src/planner/exact.cpp#L667); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L667-L668:sha256:53dfe4718253e2160abc90dccb9380c771d79e0a2175e08dd46da81ef8586ce8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for main: Publish the concrete tree only after all choice copying finishes; its height claim still needs P02 checking. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies main; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for main come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0072

[Lines 669–675](../../../../../src/planner/exact.cpp#L669); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Task main() {
    Task task;
    co_await operation([&] { draft = std::make_shared<FreeConnexTree>(); });
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare and publish one complete concrete candidate tree. |
| inputs / outputs | Creates fresh draft, omits the synthetic empty-body choice at height zero, copies the root otherwise, and records claimed native height. |
| invariants | Only completed copying assigns completed; a claimed height remains subject to independent validation. |
| ownership | Owns draft and publishes it through a const shared handle. |
| failure | Allocation failure leaves the same pending operation and no completed-tree publication. |
| cost | Tree/control-block allocation plus complete node/scope traversal; empty body has no nodes. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0073

[Lines 676–678](../../../../../src/planner/exact.cpp#L676); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L676-L678:sha256:7d328e8f2a43497b0fb40a74705509abcf803eb7fc478c2e258ff44554a37bb9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. Its attached note introduces nearby behavior: Allocate a witness shell retaining its binding and frozen candidate; copying starts on step. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0074

[Lines 679–680](../../../../../src/planner/exact.cpp#L679); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WitnessMachine::WitnessMachine(std::shared_ptr<const BindingData> binding, std::shared_ptr<const FrozenCandidate> candidate)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the inert owning witness copier for one pending producer candidate. |
| inputs / outputs | Takes shared binding and candidate handles and allocates Impl. |
| invariants | No copying or validation occurs until step; inputs must belong to the private facade protocol. |
| ownership | Owns implementation exclusively and retains candidate arena ownership. |
| failure | Implementation allocation can fail before facade stage publication. |
| cost | One implementation allocation and handle moves; no graph traversal. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0075

[Lines 681–691](../../../../../src/planner/exact.cpp#L681); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WitnessMachine::~WitnessMachine() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release witness execution and any unpublished draft. |
| inputs / outputs | Destroys Impl, which cancels its active frames before members release. |
| invariants | An incomplete copy is never published by destruction. |
| ownership | Drops this machine ownership; returned complete trees retain their own payloads. |
| failure | Nonthrowing destruction under standard owned-element contracts. |
| cost | Can visit active frames, the draft tree and, on final ownership release, candidate arena records. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

```text
WitnessMachine::WitnessMachine(WitnessMachine&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer saved witness copying to a new exclusive wrapper. |
| inputs / outputs | Moves the implementation pointer, leaving the source empty. |
| invariants | Frame/draft addresses and all borrowed choice pointers stay stable. |
| ownership | Transfers candidate and draft ownership indirectly through Impl. |
| failure | Noexcept; later private methods require nonempty data_. |
| cost | Pointer transfer without graph or frame movement. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

```text
WitnessMachine& WitnessMachine::operator=(WitnessMachine&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace an existing witness copier with another saved owner. |
| inputs / outputs | Default assignment releases destination Impl and takes source Impl. |
| invariants | Old destination cancellation runs before its borrows can outlive storage. |
| ownership | Transfers exclusive implementation ownership; external trees remain shared. |
| failure | Noexcept assignment with private nonempty-method preconditions afterward. |
| cost | Transfer is small; releasing a live destination can tear down its frames and tree scratch. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0076

[Lines 692–702](../../../../../src/planner/exact.cpp#L692); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UnitResult WitnessMachine::step(const UnitContext& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance saved witness construction or report a completed tree. |
| inputs / outputs | Returns witness_complete, depth_blocked or advanced; lazily creates the root task. |
| invariants | Nonempty queries require initial depth one; administrative empty work bypasses frame ceilings with logical depth zero. |
| ownership | Mutates only the exclusively owned copier; completed tree is fetched separately. |
| failure | Pending allocation can escape for facade retry without publishing the draft. |
| cost | One scheduler transition plus nonallocating control flow; container/string operations have their own size-dependent costs. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0077

[Lines 703–704](../../../../../src/planner/exact.cpp#L703); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L703-L704:sha256:94be231f491bb8b4d8f7b45a8bbe3b5125992f3255c9a59f55b0938d2f8c7a72
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for WitnessMachine: Read copier frame depth separately from tree native height. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies WitnessMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for WitnessMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0078

[Lines 705–705](../../../../../src/planner/exact.cpp#L705); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t WitnessMachine::current_depth() const noexcept { return data_->e.administrative_only ? 0 : data_->e.depth; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report witness-copy logical coroutine depth. |
| inputs / outputs | Returns zero for administrative empty work, otherwise saved Engine depth. |
| invariants | This resource metric is distinct from candidate native height. |
| ownership | Returns a scalar and retains the copier owner. |
| failure | Noexcept; moved-from private wrappers cannot be queried. |
| cost | Constant-size Engine state reads without traversal. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0079

[Lines 706–707](../../../../../src/planner/exact.cpp#L706); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L706-L707:sha256:6516e503aca59a5cae42c0afddf2ed432256b95f85db06c4faae5cf7c401ff7f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for WitnessMachine: Retain the complete candidate tree for P02 validation; copying alone gives no checked upper. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies WitnessMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for WitnessMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0080

[Lines 708–708](../../../../../src/planner/exact.cpp#L708); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const FreeConnexTree> WitnessMachine::tree() const noexcept { return data_->completed; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the complete materialized candidate for independent P02 validation. |
| inputs / outputs | Returns null until copy completion, then a shared immutable concrete tree. |
| invariants | Completeness of copying does not establish structural validity or a minimum height. |
| ownership | The returned owner keeps tree payload alive after copier destruction. |
| failure | Noexcept handle copy with a live-machine precondition. |
| cost | Copies shared ownership only; no tree copy or validation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0081

[Lines 709–710](../../../../../src/planner/exact.cpp#L709); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L709-L710:sha256:06bb1963c8096f589c9cd8ee9c6111fd69ad2bd2488b56bcba3f60dad3b9e783
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove preprocessor macro SUBTASK after the local witness-task expansion and close namespace crown::planner::continuation_detail. |
| inputs / outputs | The preprocessor directive and namespace close have no runtime input or result. |
| invariants | The macro is undefined before later source text is processed; closing the namespace ends its compile-time name scope. |
| ownership | No runtime state or owner is created or released. |
| failure | An unmatched namespace boundary or macro-dependent later use fails compilation; no runtime failure is added. |
| cost | Preprocessor and parser bookkeeping only; no runtime work or allocation. |
| Design | [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |
