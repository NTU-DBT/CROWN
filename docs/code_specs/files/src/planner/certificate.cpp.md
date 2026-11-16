# `src/planner/certificate.cpp` — block usage map

[Source](../../../../../src/planner/certificate.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Replay retained lower-bound evidence independently of search continuation state.

Snapshot SHA-256: `afe263b43cd0fe0be877d48db1977507c8ab617d3017e927144d3f0578c83a43`. 652 lines partitioned into 46 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/planner/certificate.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Groups retain input-binding occurrence indices in sorted order for independent ports and partition · [reviewed contract](#b0001) |
| [B0002 · 14–21](../../../../../src/planner/certificate.cpp#L14) | Type/record definition: struct ReplayState | source comment (unverified): // Replay keys independently retain both context flags; v2 canonicalizes only equal · [reviewed contract](#b0002) |
| [B0003 · 22–23](../../../../../src/planner/certificate.cpp#L22) | Explanatory comments or spacing. | source comment (unverified): // Order provided and verified keys by independent state contents. See docs/planner_proofs.md, · [reviewed contract](#b0003) |
| [B0004 · 24–31](../../../../../src/planner/certificate.cpp#L24) | Type/record definition: struct StateLess | returns *a &lt; *b; source comment (unverified): // Order provided and verified keys by independent state contents. See docs/planner_proofs.md, · [reviewed contract](#b0004) |
| [B0005 · 32–33](../../../../../src/planner/certificate.cpp#L32) | Explanatory comments or spacing. | source comment (unverified): // Cache only complete ports derived from checker scopes, with the owning value retaining its · [reviewed contract](#b0005) |
| [B0006 · 34–39](../../../../../src/planner/certificate.cpp#L34) | Type/record definition: struct ReplayPorts | source comment (unverified): // Cache only complete ports derived from checker scopes, with the owning value retaining its · [reviewed contract](#b0006) |
| [B0007 · 40–41](../../../../../src/planner/certificate.cpp#L40) | Explanatory comments or spacing. | source comment (unverified): // Compare pointed-to member contents while cached ports retain their own key storage. See · [reviewed contract](#b0007) |
| [B0008 · 42–46](../../../../../src/planner/certificate.cpp#L42) | Type/record definition: struct GroupLess | returns *a &lt; *b; source comment (unverified): // Compare pointed-to member contents while cached ports retain their own key storage. See · [reviewed contract](#b0008) |
| [B0009 · 47–50](../../../../../src/planner/certificate.cpp#L47) | Explanatory comments or spacing. | source comment (unverified): // All potentially allocating edits precede their cursor increments. Jobs live · [reviewed contract](#b0009) |
| [B0010 · 51–72](../../../../../src/planner/certificate.cpp#L51) | Type/record definition: struct ReplayJob | source comment (unverified): // All potentially allocating edits precede their cursor increments. Jobs live · [reviewed contract](#b0010) |
| [B0011 · 73–107](../../../../../src/planner/certificate.cpp#L73) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 108–109](../../../../../src/planner/certificate.cpp#L108) | Explanatory comments or spacing. | source comment (unverified): // Capture admitted proof and binding owners; checking starts on step. See · [reviewed contract](#b0012) |
| [B0013 · 110–111](../../../../../src/planner/certificate.cpp#L110) | Callable definition: Impl(std::shared_ptr&lt;const BindingData&gt; bnd, std::shared_ptr&lt;const HeightCertificate&gt; p) : binding(std::move(bnd)), proof(std::mo… | calls binding, std::move, proof; source comment (unverified): // Capture admitted proof and binding owners; checking starts on step. See · [reviewed contract](#b0013) |
| [B0014 · 112–113](../../../../../src/planner/certificate.cpp#L112) | Explanatory comments or spacing. | source comment (unverified): // Mark proof rejection terminal with a stable diagnostic view; do not publish checked · [reviewed contract](#b0014) |
| [B0015 · 114–117](../../../../../src/planner/certificate.cpp#L114) | Callable definition: UnitResult fail(std::string_view why) noexcept | calls ; returns {UnitEvent::proof_invalid}; source comment (unverified): // Mark proof rejection terminal with a stable diagnostic view; do not publish checked · [reviewed contract](#b0015) |
| [B0016 · 118–119](../../../../../src/planner/certificate.cpp#L118) | Explanatory comments or spacing. | source comment (unverified): // Count the nonempty dispatch frame plus jobs, or delegate active upper-validation depth. · [reviewed contract](#b0016) |
| [B0017 · 120–124](../../../../../src/planner/certificate.cpp#L120) | Callable definition: std::size_t depth() const noexcept | calls empty, current_depth, size; returns 0; upper_machine && phase == ReplayPhase::validate_upper; source comment (unverified): // Count the nonempty dispatch frame plus jobs, or delegate active upper-validation depth. · [reviewed contract](#b0017) |
| [B0018 · 125–126](../../../../../src/planner/certificate.cpp#L125) | Explanatory comments or spacing. | source comment (unverified): // Check the proposed frame depth before creating a child job. See · [reviewed contract](#b0018) |
| [B0019 · 127–129](../../../../../src/planner/certificate.cpp#L127) | Callable definition: bool permitted_push(const UnitContext& context) const noexcept | calls permits, size; returns context.permits(jobs.size() + 2); source comment (unverified): // Check the proposed frame depth before creating a child job. See · [reviewed contract](#b0019) |
| [B0020 · 130–131](../../../../../src/planner/certificate.cpp#L130) | Explanatory comments or spacing. | source comment (unverified): // Report the pending child depth without changing proof state. See · [reviewed contract](#b0020) |
| [B0021 · 132–132](../../../../../src/planner/certificate.cpp#L132) | Callable definition: UnitResult blocked() const noexcept | calls size; returns {UnitEvent::depth_blocked, jobs.size() + 2}; source comment (unverified): // Report the pending child depth without changing proof state. See · [reviewed contract](#b0021) |
| [B0022 · 133–134](../../../../../src/planner/certificate.cpp#L133) | Explanatory comments or spacing. | source comment (unverified): // Push a prepared frame before advancing its parent stage; unique_ptr storage preserves · [reviewed contract](#b0022) |
| [B0023 · 135–135](../../../../../src/planner/certificate.cpp#L135) | Callable definition: void push(std::unique_ptr&lt;ReplayJob&gt; job) | calls push_back, std::move; growth push_back; source comment (unverified): // Push a prepared frame before advancing its parent stage; unique_ptr storage preserves · [reviewed contract](#b0023) |
| [B0024 · 136–137](../../../../../src/planner/certificate.cpp#L136) | Explanatory comments or spacing. | source comment (unverified): // Pop the active frame only after transferring its result; scratch release may scale with · [reviewed contract](#b0024) |
| [B0025 · 138–138](../../../../../src/planner/certificate.cpp#L138) | Callable definition: void finish() noexcept | calls pop_back; source comment (unverified): // Pop the active frame only after transferring its result; scratch release may scale with · [reviewed contract](#b0025) |
| [B0026 · 139–140](../../../../../src/planner/certificate.cpp#L139) | Explanatory comments or spacing. | source comment (unverified): // Prepare a child frame privately; its input group stays borrowed from a retained owner. · [reviewed contract](#b0026) |
| [B0027 · 141–143](../../../../../src/planner/certificate.cpp#L141) | Callable definition: std::unique_ptr&lt;ReplayJob&gt; make(ReplayJob::Kind kind, const Group* group = nullptr) | calls ; returns j; growth make_unique; source comment (unverified): // Prepare a child frame privately; its input group stays borrowed from a retained owner. · [reviewed contract](#b0027) |
| [B0028 · 144–149](../../../../../src/planner/certificate.cpp#L144) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Run one saved independent job action; allocation can escape for retry, while invalid · [reviewed contract](#b0028) |
| [B0029 · 150–455](../../../../../src/planner/certificate.cpp#L150) | Callable definition: UnitResult ReplayMachine::Impl::run_job(const UnitContext& context) | calls back, std::move, size, push_back; returns {}; {}; growth emplace, insert, make_shared, push_back; source comment (unverified): // Run one saved independent job action; allocation can escape for retry, while invalid · [reviewed contract](#b0029) |
| [B0030 · 456–459](../../../../../src/planner/certificate.cpp#L456) | Explanatory comments or spacing. | source comment (unverified): // Publish CheckedProof only after upper checking, claim induction and matching full-query · [reviewed contract](#b0030) |
| [B0031 · 460–618](../../../../../src/planner/certificate.cpp#L460) | Callable definition: UnitResult ReplayMachine::Impl::step(const UnitContext& context) | calls empty, permits, run_job, fail; returns {UnitEvent::proof_valid}; {UnitEvent::proof_invalid}; growth emplace, emplace_back, insert, make_shared, make_unique, push_back; source comment (unverified): // Publish CheckedProof only after upper checking, claim induction and matching full-query · [reviewed contract](#b0031) |
| [B0032 · 619–621](../../../../../src/planner/certificate.cpp#L619) | Explanatory comments or spacing. | source comment (unverified): // Allocate an inert checker shell around immutable binding and certificate owners. See · [reviewed contract](#b0032) |
| [B0033 · 622–624](../../../../../src/planner/certificate.cpp#L622) | Callable definition: ReplayMachine::ReplayMachine(std::shared_ptr&lt;const BindingData&gt; binding, std::shared_ptr&lt;const HeightCertificate&gt; proof) : data_(… | calls data_, std::move; growth make_unique; source comment (unverified): // Allocate an inert checker shell around immutable binding and certificate owners. See · [reviewed contract](#b0033) |
| [B0034 · 625–635](../../../../../src/planner/certificate.cpp#L625) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Release flat checker jobs and caches; independently retained checked artifacts outlive the · [reviewed contract](#b0034) |
| [B0035 · 636–636](../../../../../src/planner/certificate.cpp#L636) | Callable definition: UnitResult ReplayMachine::step(const UnitContext& context) | calls step; returns data_-&gt;step(context); source comment (unverified): // Delegate one saved checker action; the facade alone charges work and time. See · [reviewed contract](#b0035) |
| [B0036 · 637–638](../../../../../src/planner/certificate.cpp#L637) | Explanatory comments or spacing. | source comment (unverified): // Read checker progress without advancing or creating authority. See · [reviewed contract](#b0036) |
| [B0037 · 639–639](../../../../../src/planner/certificate.cpp#L639) | Callable definition: ReplayPhase ReplayMachine::phase() const noexcept | calls ; returns data_-&gt;phase; source comment (unverified): // Read checker progress without advancing or creating authority. See · [reviewed contract](#b0037) |
| [B0038 · 640–641](../../../../../src/planner/certificate.cpp#L640) | Explanatory comments or spacing. | source comment (unverified): // Report the checker logical frame depth, including delegated upper validation. See · [reviewed contract](#b0038) |
| [B0039 · 642–642](../../../../../src/planner/certificate.cpp#L642) | Callable definition: std::size_t ReplayMachine::current_depth() const noexcept | calls depth; returns data_-&gt;depth(); source comment (unverified): // Report the checker logical frame depth, including delegated upper validation. See · [reviewed contract](#b0039) |
| [B0040 · 643–644](../../../../../src/planner/certificate.cpp#L643) | Explanatory comments or spacing. | source comment (unverified): // Count committed claim proofs; a verified prefix does not certify the whole-query optimum. · [reviewed contract](#b0040) |
| [B0041 · 645–645](../../../../../src/planner/certificate.cpp#L645) | Callable definition: std::size_t ReplayMachine::checked_claims() const noexcept | calls ; returns data_-&gt;count_checked; source comment (unverified): // Count committed claim proofs; a verified prefix does not certify the whole-query optimum. · [reviewed contract](#b0041) |
| [B0042 · 646–647](../../../../../src/planner/certificate.cpp#L646) | Explanatory comments or spacing. | source comment (unverified): // Borrow the stable checker diagnostic; owning legacy message conversion happens outside this · [reviewed contract](#b0042) |
| [B0043 · 648–648](../../../../../src/planner/certificate.cpp#L648) | Callable definition: std::string_view ReplayMachine::message() const noexcept | calls ; returns data_-&gt;diagnostic; source comment (unverified): // Borrow the stable checker diagnostic; owning legacy message conversion happens outside this · [reviewed contract](#b0043) |
| [B0044 · 649–650](../../../../../src/planner/certificate.cpp#L649) | Explanatory comments or spacing. | source comment (unverified): // Retain authority only after complete independent replay; finite roots pair with an upper, · [reviewed contract](#b0044) |
| [B0045 · 651–651](../../../../../src/planner/certificate.cpp#L651) | Callable definition: std::shared_ptr&lt;const CheckedProof&gt; ReplayMachine::checked() const noexcept | calls ; returns data_-&gt;authority; source comment (unverified): // Retain authority only after complete independent replay; finite roots pair with an upper, · [reviewed contract](#b0045) |
| [B0046 · 652–652](../../../../../src/planner/certificate.cpp#L652) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::continuation_detail · [reviewed contract](#b0046) |

## B0001

[Lines 1–13](../../../../../src/planner/certificate.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Group = std::vector<std::size_t>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name actual sorted occurrence groups used by the independent checker. |
| inputs / outputs | Groups hold original atom indexes for claim members, child blocks and component walks. |
| invariants | Proof members are validated sorted/unique/in-range before jobs use them; generated blocks preserve global order. |
| ownership | Each vector owns its indexes; job input pointers borrow a retained owner. |
| failure | The alias itself enforces no validation or lifetime. |
| cost | Linear index storage with allocation on vector growth. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0002

[Lines 14–21](../../../../../src/planner/certificate.cpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplayState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify a lower-bound proof state independently of producer key types. |
| inputs / outputs | Stores occurrences and generalized/reachable flags; v1 uses actual members and v2 uses independently derived orbit representatives. |
| invariants | Both context flags remain part of identity; canonicalization preserves the number of members. |
| ownership | Owns its occurrence vector and is shared const once indexed. |
| failure | No constructor validation; indexing validates members before a job creates this key. |
| cost | Linear member storage and lexicographic key comparison. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md) |

```text
auto operator<=>(const ReplayState&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order independently reconstructed proof states by full value. |
| inputs / outputs | Compares occurrence vector, generalized permission and reachability in declaration order. |
| invariants | Equal member groups with different flags cannot share a checked bound. |
| ownership | Borrows both key values for comparison. |
| failure | Assumes keys remain stable while indexed; it does no proof validation. |
| cost | Can scan the entire common occurrence prefix before scalar flags. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md) |

## B0003

[Lines 22–23](../../../../../src/planner/certificate.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L23:sha256:3a9cb9ddee04ed7df43e0b64666708fcd00e80b4a273697e60f726206753f075
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for StateLess: Order provided and verified keys by independent state contents. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies StateLess; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for StateLess come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 24–31](../../../../../src/planner/certificate.cpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StateLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide content ordering for shared independent replay keys. |
| inputs / outputs | Used by both provided and verified claim maps. |
| invariants | Shared-pointer address/control-block identity is irrelevant to proof-state identity. |
| ownership | Stateless policy; maps retain key owners. |
| failure | Null or mutable published key handles violate private map preconditions. |
| cost | Policy storage is empty; comparisons traverse key contents as needed. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md) |

```text
bool operator()(const std::shared_ptr<const ReplayState>& a,
                  const std::shared_ptr<const ReplayState>& b) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two shared proof-state values for lookup and duplicate detection. |
| inputs / outputs | Returns dereferenced ReplayState ordering. |
| invariants | Key pointees must be non-null and immutable for their whole indexed lifetime. |
| ownership | Borrows handles and their owned values during comparison. |
| failure | Declared noexcept; the stored numeric vectors/flags have nonthrowing value comparisons. |
| cost | Linear in the equal vector prefix, without key construction. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md) |

## B0005

[Lines 32–33](../../../../../src/planner/certificate.cpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L33:sha256:78fc0ee2b0ca11ede14ea094370d25839a9d22c8756df3a4615015ef9e2d4dbb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayPorts: Cache only complete ports derived from checker scopes, with the owning value retaining its stable member key. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayPorts; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayPorts come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 34–39](../../../../../src/planner/certificate.cpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplayPorts {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cache independently derived inside/outside unions and admissibility ports. |
| inputs / outputs | members is the actual member key; variables, outside, boundary and exclusive_head derive from checker scopes and head. |
| invariants | Published ports are complete; cache keys point into the owning value and cannot change after insertion. |
| ownership | Owns member/variable containers; port_cache shares the record that keeps its key address alive. |
| failure | A partial record stays job-private and never supplies a cached port result. |
| cost | Each cached group retains its member vector and variable sets; cache size can grow with the groups visited during replay. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0007

[Lines 40–41](../../../../../src/planner/certificate.cpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L41:sha256:65ca2782d82875480e0d949d3b0221dc7ecaf625389604763d00999d101820be
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for GroupLess: Compare pointed-to member contents while cached ports retain their own key storage. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies GroupLess; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for GroupLess come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0008

[Lines 42–46](../../../../../src/planner/certificate.cpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GroupLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow cache lookup by any actual member-vector address with equal contents. |
| inputs / outputs | Orders raw Group pointers by their pointed-to sequences. |
| invariants | Inserted key pointers belong to retained ReplayPorts; temporary lookup inputs need survive only the lookup. |
| ownership | The comparator owns no vector or pointer target. |
| failure | Null, dangling or mutated indexed groups violate the cache contract. |
| cost | Comparison can traverse an entire equal member prefix. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
bool operator()(const Group* a, const Group* b) const noexcept { return *a < *b; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare actual member groups for the independent ports cache. |
| inputs / outputs | Returns lexicographic vector order, accepting borrowed lookup groups with unrelated addresses. |
| invariants | Cached group contents never change after publication. |
| ownership | Borrows both non-null vectors without retaining them. |
| failure | Noexcept numeric-vector comparison; no validation of pointer lifetimes. |
| cost | Linear in the compared occurrence prefix; it does not copy a cache key. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0009

[Lines 47–50](../../../../../src/planner/certificate.cpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L50:sha256:5a03948a5509b3402052929a7131f38dc1f29821bc9dce723946dc656a0b66d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayJob: All potentially allocating edits precede their cursor increments. Jobs live at stable addresses, so a suspended child's input can refer to its parent. Keep stage-specific scratch at stable addresses and commit cursor progress after allocating edits. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayJob; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayJob come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0010

[Lines 51–72](../../../../../src/planner/certificate.cpp#L51); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum Kind { key, ports, components, prove, enumerate, option, child } kind;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select one independently owned replay job protocol. |
| inputs / outputs | Kind distinguishes key construction, ports, components, claim proof, partition enumeration, option checking and child-bound lookup. |
| invariants | Each kind interprets its own stage/cursors; parent continuation advances only after its child result is available. |
| ownership | Job kind owns no child frame; the implementation owns the flat job stack. |
| failure | An impossible dispatch/stage falls to proof-invalid handling instead of granting authority. |
| cost | One enum discriminator per job; algorithm cost belongs to its selected state machine. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
struct ReplayJob {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own scratch and next-action cursors for one independent replay frame. |
| inputs / outputs | Carries tagged stage/counters, borrowed input/claim pointers, private groups/sets, and shared port/key scratch. |
| invariants | Parent frames remain at stable unique_ptr payload addresses; allocating container edits precede cursor increments. partition is a separate shared stack with one active enumeration chain. |
| ownership | Owns scratch; borrows claim data from immutable proof and group data from retained parent/partition owners. |
| failure | Allocation retry must preserve the semantic next stage; jobs are never serialized or treated as completed claims. |
| cost | Frame headers include several containers and scratch values; retained payload and stack depth grow with the proof traversal. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
explicit ReplayJob(Kind k) : kind(k) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an inert frame for a chosen replay protocol. |
| inputs / outputs | Sets kind while default initializers zero cursors/flags and leave containers empty. |
| invariants | Input and claim pointers are populated by the scheduling caller before that kind uses them. |
| ownership | Owns only empty scratch initially; it retains no input by itself. |
| failure | Does not validate kind-specific preconditions; outer make_unique allocation can throw before push. |
| cost | Initializes fixed frame headers without scanning proof data. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0011

[Lines 73–107](../../../../../src/planner/certificate.cpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplayMachine::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the independent checker state from dispatch through final authority publication. |
| inputs / outputs | Retains binding/proof, optional independent upper validator, actual scopes, orbit classes, supplied/verified maps, jobs, return registers and partition stack. |
| invariants | Only completed claims enter verified; provided claims remain untrusted. Ports cache is rebuilt from actual checker scopes, and root equality is required before authority exists. |
| ownership | Owns all jobs flatly and shares immutable input/checked artifacts; internal raw input/cache pointers are backed by retained owners. |
| failure | Invalid evidence is terminal; allocation stops retain staged work for facade retry and confer no proof result. |
| cost | Independent replay can retain large claim maps, port caches and enumeration scratch; neither a transition nor shared handles bound total memory. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0012

[Lines 108–109](../../../../../src/planner/certificate.cpp#L108); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L109:sha256:ca08031cdb0eb85c7c3bd9706b172268e2003dc8cdfecd2abaf7946e7703a53f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Impl: Capture admitted proof and binding owners; checking starts on step. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Impl; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Impl come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0013

[Lines 110–111](../../../../../src/planner/certificate.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Impl(std::shared_ptr<const BindingData> bnd, std::shared_ptr<const HeightCertificate> p)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture immutable inputs for deferred independent proof replay. |
| inputs / outputs | Moves non-null binding/proof handles into an inert implementation. |
| invariants | No upper validation, scope derivation or claim indexing occurs in construction. |
| ownership | Shares owned admission snapshots rather than borrowing mutable caller documents. |
| failure | Assumes the private facade supplied non-null owners; admission performs the external validation/copying. |
| cost | Two handle transfers and empty checker-state initialization; outer implementation allocation is separate. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0014

[Lines 112–113](../../../../../src/planner/certificate.cpp#L112); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L113:sha256:f5e922a96379886c95c9220cb836b73cdef9d923414c58fbaa69c9b0455be558
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for fail: Mark proof rejection terminal with a stable diagnostic view; do not publish checked authority. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies fail; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for fail come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0015

[Lines 114–117](../../../../../src/planner/certificate.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UnitResult fail(std::string_view why) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark malformed evidence or an impossible checker state as terminal invalid proof. |
| inputs / outputs | Stores a stable diagnostic view, sets failed phase and returns proof_invalid. |
| invariants | No CheckedProof is published by failure; subsequent steps return the same terminal event. |
| ownership | Borrows why; current call sites pass static diagnostic literals with sufficient lifetime. |
| failure | Noexcept path allocates no message; scratch remains owned until facade release/cancellation. |
| cost | Two scalar/view assignments; retaining scratch means immediate failure does not traverse it. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0016

[Lines 118–119](../../../../../src/planner/certificate.cpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L119:sha256:024263e2716a0d3338e43365a973a567d816bf202c0cc092070df00a2bb7f525
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for depth: Count the nonempty dispatch frame plus jobs, or delegate active upper-validation depth. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies depth; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for depth come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0017

[Lines 120–124](../../../../../src/planner/certificate.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t depth() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report independent replay logical depth for the resource ledger. |
| inputs / outputs | Returns zero for empty/terminal replay, delegated upper-validation depth during that phase, or jobs.size()+1 for checker dispatch plus frames. |
| invariants | Dispatch counts as an owned frame for nonempty queries; native tree height is unrelated. |
| ownership | Borrows retained checker/validator state and returns a scalar. |
| failure | Noexcept observer assumes a live admitted binding. |
| cost | Uses saved sizes/depth fields; no job-stack walk. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0018

[Lines 125–126](../../../../../src/planner/certificate.cpp#L125); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L126:sha256:c41117d9cc7b3d499638a85ec38cc95b5aabebbd54393afc0b1bb97ed78a6cbf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for permitted_push: Check the proposed frame depth before creating a child job. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies permitted_push; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for permitted_push come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0019

[Lines 127–129](../../../../../src/planner/certificate.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool permitted_push(const UnitContext& context) const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check logical depth before allocating/pushing another replay job. |
| inputs / outputs | Queries context.permits(jobs.size()+2), including dispatch, current jobs and the proposed frame. |
| invariants | A rejected push leaves the same next action pending; no semantic cursor advances. |
| ownership | Borrows context and stack size without creating a frame. |
| failure | Noexcept Boolean check; a depth stop is incomplete work, not evidence rejection. |
| cost | Constant-size arithmetic and optional ceiling comparison; no container traversal. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0020

[Lines 130–131](../../../../../src/planner/certificate.cpp#L130); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L130-L131:sha256:27a445aa4786fe10a7ecdbbf82bee70abbac552cff34207d927d5b1b4a25a70c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for size: Report the pending child depth without changing proof state. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies size; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for size come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0021

[Lines 132–132](../../../../../src/planner/certificate.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UnitResult blocked() const noexcept { return {UnitEvent::depth_blocked, jobs.size() + 2}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the exact frame depth requested by a pending child push. |
| inputs / outputs | Produces depth_blocked with dispatch-plus-stack-plus-child depth. |
| invariants | Does not change phase, stack, claims or authority. |
| ownership | Returns a scalar event by value. |
| failure | Noexcept; the outer owner may later raise the ceiling and resume the same action. |
| cost | Reads stack size and constructs a small event without allocation. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0022

[Lines 133–134](../../../../../src/planner/certificate.cpp#L133); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L134:sha256:b5a5eb3d74ad3894a1c9756999a621e4e4cb92e4f7bde3576a2ed0447a6548ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for std: Push a prepared frame before advancing its parent stage; unique_ptr storage preserves frame addresses. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies std; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for std come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0023

[Lines 135–135](../../../../../src/planner/certificate.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void push(std::unique_ptr<ReplayJob> job) { jobs.push_back(std::move(job)); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one prepared replay frame to the flat owned stack. |
| inputs / outputs | Takes unique ownership of a non-null inert job and appends its handle. |
| invariants | Callers check permitted_push first and advance parent stage only after push succeeds. |
| ownership | The vector owns the frame; moving its unique_ptr does not move payload addresses borrowed by children. |
| failure | Vector growth can throw; the prepared frame is local and no child stage is published on failure. |
| cost | Amortized handle append; growth relocates O(depth) handles and may allocate. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0024

[Lines 136–137](../../../../../src/planner/certificate.cpp#L136); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L137:sha256:081ce8c91dab31410eacb5c9c201d32761f97a9b57c3903df6afc07fa53083c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for pop_back: Pop the active frame only after transferring its result; scratch release may scale with retained payload. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies pop_back; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for pop_back come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0025

[Lines 138–138](../../../../../src/planner/certificate.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish() noexcept { jobs.pop_back(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release the active replay job after its result is installed in return registers. |
| inputs / outputs | Pops exactly one nonempty stack entry; parent will consume retained return values next. |
| invariants | No child is live when its active parent frame is removed; borrowed parent input storage remains valid for each child lifetime. |
| ownership | Destroys owned job scratch; returned shared owners/moved vectors live in Impl registers. |
| failure | Noexcept under owned element destructors; calling on an empty stack violates the private protocol. |
| cost | Can free variable-size groups/sets/vectors and last shared port owners; finishing is not uniformly constant time. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0026

[Lines 139–140](../../../../../src/planner/certificate.cpp#L139); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L139-L140:sha256:074bcda856bca7d34c0f1404ffe23a6fd797ffc49a8443744f3637dd5366fe4e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for make: Prepare a child frame privately; its input group stays borrowed from a retained owner. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies make; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for make come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0027

[Lines 141–143](../../../../../src/planner/certificate.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::unique_ptr<ReplayJob> make(ReplayJob::Kind kind, const Group* group = nullptr) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an unpushed checker frame with an optional borrowed group input. |
| inputs / outputs | Allocates ReplayJob(kind), sets input and returns unique ownership for caller-specific fields and push. |
| invariants | No parent cursor advances inside make; the input group owner must outlive the new frame. |
| ownership | Returned unique_ptr owns scratch; input remains a borrow. |
| failure | Allocation failure leaves the caller at its existing scheduling stage. |
| cost | One frame allocation and constant header setup, without scanning the group. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0028

[Lines 144–149](../../../../../src/planner/certificate.cpp#L144); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L144-L149:sha256:92efd8bd7c3ca53358ea112a09e0361f99448286af28692fd981d80700452d8d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare run_job, step in src/planner/certificate.cpp with the exact signatures shown in this span. Nearby note: Run one saved independent job action; allocation can escape for retry, while invalid evidence becomes terminal. |
| inputs / outputs | Signatures: UnitResult run_job(const UnitContext& context); UnitResult step(const UnitContext& context);. These declarations specify parameter and result types; definitions supply runtime work. |
| invariants | The declarations fix C++ call types only; they do not execute, validate arguments, or create proof authority. |
| ownership | reference parameters borrow caller-owned objects for the call. |
| failure | Ill-formed or mismatched declarations fail compilation/linkage. Runtime exception and resource-stop behavior belongs to each definition. |
| cost | The compiler parses the signatures; there is no runtime work or allocation until a definition is called. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0029

[Lines 150–455](../../../../../src/planner/certificate.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UnitResult ReplayMachine::Impl::run_job(const UnitContext& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one saved action of the active independent replay protocol. |
| inputs / outputs | Dispatches the flat stack top to key/ports/components/prove/enumerate/option/child stages and returns an event. |
| invariants | Every child push is depth-checked; supplied claims become usable only after their own proof; enumeration and ports do not call producer helpers. |
| ownership | Mutates owned frames/registers/cache while retaining borrowed proof/member inputs. |
| failure | Invalid stage or failed proof returns proof_invalid; allocating edits propagate for retry before stage increments. |
| cost | One controlled action can involve map/vector/set work and scratch destruction; total replay enumerates exponential partition families. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case ReplayJob::key:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an independent v1 key or v2 equal-scope orbit key. |
| inputs / outputs | Copies actual members for v1; for v2 counts members per independently derived scope class and selects first global indexes per class. |
| invariants | Preserves member count and both flags; no producer canonical state is trusted. |
| ownership | Owns scratch counts/key until returned_key receives the completed key. |
| failure | Allocating vector appends precede count/cursor consumption, preserving the same next semantic append on retry. |
| cost | v1 scans group size; v2 additionally initializes classes and scans all occurrences, with key-vector allocations. |
| Design | [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case ReplayJob::ports:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive or reuse complete independent ports for an actual member group. |
| inputs / outputs | Scans all scopes into inside/outside unions, derives boundary/exclusive head, copies actual members and commits the complete record to port_cache. |
| invariants | The cache key belongs to its shared value; only complete records are visible and no producer metadata enters the computation. |
| ownership | Job owns partial ports; the cache owns the shared complete value and stabilizes its borrowed key pointer. |
| failure | Set/member/cache allocations retry before cursor/publication commits; a failed cache insertion leaves the complete job-private record available. |
| cost | On a miss scans query incidences and performs ordered membership/inserts; cache hits still compare member vectors and share ownership. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case ReplayJob::child:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retrieve an independently verified child lower bound with a safe omission default. |
| inputs / outputs | Canonicalizes the actual child group, then reads verified or uses universal one when no claim was supplied. |
| invariants | A provided but not yet verified state is rejected, preventing forward/circular use; null verified bound denotes infeasibility. |
| ownership | Borrows group/flags and transfers only an optional scalar through returned_bound. |
| failure | Key allocation can retry; unverified supplied dependency becomes terminal proof rejection. |
| cost | Key construction plus ordered-map lookup; omitted children avoid proving extra states but can weaken the available bound. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md) |

```text
case ReplayJob::components:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct actual occurrence connected components independently of producer union/find. |
| inputs / outputs | Walks the variable-sharing occurrence graph, marking discovered/finished nodes and rebuilding each group in global index order. |
| invariants | Empty scopes are singleton components; each occurrence enters exactly one component. |
| ownership | Owns visitation bits, frontier/groups and returns the complete component vector by move. |
| failure | Frontier/group growth commits before marks/cursor increments; allocation failure leaves the discovery step retryable. |
| cost | Potentially quadratic occurrence adjacency scans with scope membership checks, plus component storage; no union/find bound is claimed. |
| Design | [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case ReplayJob::prove:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Establish one supplied lower claim by universal, impossibility, component or exhaustive recurrence reasoning. |
| inputs / outputs | Accepts bound one universally; blocked exclusive-head states support infinity; otherwise checks every admissible native/generalized alternative. |
| invariants | v2 component maximum applies only at full-query state with both flags true and independently empty component boundaries. Missing child bounds stay one; verified infinite component suffices for infinity. |
| ownership | Borrows an immutable claim and owns ports/enumeration scratch through jobs; verification map publication occurs later in step. |
| failure | Insufficient component/alternative bounds reject. A job pause or resource stop does not prove the claim. |
| cost | May enumerate every root and Bell-number partition; base-one and blocked-state paths avoid that exhaustive work. |
| Design | [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md), [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md), [Refactor.md §5.4](../../../../../Refactor.md), [Refactor.md §11.3 P06](../../../../../Refactor.md) |

```text
case ReplayJob::enumerate:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate partitions independently by selecting the smallest-remaining member block. |
| inputs / outputs | Bits fix the first remaining member in the next block, range over its optional companions, and recurse on the complement. |
| invariants | One active enumeration chain appends/removes exactly its own block; every unordered partition is visited once, unlike producer insertion enumeration. |
| ownership | Owns block/complement scratch; the shared partition vector owns active blocks while child jobs borrow them. |
| failure | Allocating block preparation/pushes precede stage changes; depth stops leave the same block recursion pending. |
| cost | Exponential partition count with one job chain per remaining-block recursion; scratch vector growth and teardown are separate costs. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case ReplayJob::option:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one root/partition alternative against the claimed lower bound. |
| inputs / outputs | Derives each child ports, checks native boundaries or generalized shared-scope guards, propagates reachability, then combines verified child lower bounds with root cost. |
| invariants | Generalized roots need two children and G in every child union, including B(S). Finite option lower must reach the claim; an infinite child makes this alternative safely infinite. |
| ownership | Borrows active partition and claim; owns port handles and shared-variable scratch. |
| failure | Inadmissible structural options are skipped; a valid option with insufficient bound rejects the proof. Resource pause cannot skip an option. |
| cost | Includes pairwise child-union intersections, set containment scans, child key lookups and scratch retention for each partition. |
| Design | [docs/planner_proofs.md §Equivalent exhaustive branch partitions](../../../../planner_proofs.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md), [Refactor.md §5.4](../../../../../Refactor.md) |

## B0030

[Lines 456–459](../../../../../src/planner/certificate.cpp#L456); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L456-L459:sha256:8af23f0b9855df46f8f0eab6db83abfd91212d468ce2577c04ba9cd34993f06c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayMachine: Publish CheckedProof only after upper checking, claim induction and matching full-query root evidence; resource stops keep replay incomplete. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0031

[Lines 460–618](../../../../../src/planner/certificate.cpp#L460); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UnitResult ReplayMachine::Impl::step(const UnitContext& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive proof dispatch, upper validation, independent reconstruction/indexing, claim induction and root matching. |
| inputs / outputs | Accepts only v1/v2, checks minimum/tree presence, validates upper height, reconstructs scopes/classes, rejects malformed/duplicate claims, and processes claims in nondecreasing member count. |
| invariants | Only proved claims enter verified. Finite full-root bound must match checked upper height; infinite full root has no upper. Empty body requires checked empty zero tree and no states. |
| ownership | Owns phase cursors and admitted proof; aliases proof ownership to keep its upper tree alive without a bulk copy. |
| failure | Invalid evidence is terminal. Depth/allocating preparation can stop before the next phase/stage publication; CheckedProof is allocated only after whole-root matching. |
| cost | Includes term/scopes scans, pairwise scope-class comparisons, O(claim-count squared) stable insertion ordering in the worst case, exhaustive jobs and final authority allocation. |
| Design | [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [Refactor.md §5.5](../../../../../Refactor.md), [Refactor.md §11.3 P06](../../../../../Refactor.md) |

## B0032

[Lines 619–621](../../../../../src/planner/certificate.cpp#L619); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L619-L621:sha256:52501c9abf583868585f47904a9b9e8a591af61f8df26597dd8ca7bc3041318d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayMachine: Allocate an inert checker shell around immutable binding and certificate owners. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0033

[Lines 622–624](../../../../../src/planner/certificate.cpp#L622); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReplayMachine::ReplayMachine(std::shared_ptr<const BindingData> binding,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the inert owner of independent certificate replay. |
| inputs / outputs | Takes shared non-null admitted binding and certificate snapshots and allocates Impl. |
| invariants | No upper checking, scope reconstruction or claim proof occurs during construction. |
| ownership | Exclusively owns Impl while sharing immutable input owners. |
| failure | Implementation allocation may throw before facade stage commit; caller must supply the valid private protocol inputs. |
| cost | One implementation allocation and handle transfers; proof payload is not copied here. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0034

[Lines 625–635](../../../../../src/planner/certificate.cpp#L625); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReplayMachine::~ReplayMachine() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release independent replay and all remaining checker scratch. |
| inputs / outputs | Default implementation destruction releases upper validator, maps, jobs, caches and input handles. |
| invariants | Flat jobs do not recursively own parent/child frames; destruction publishes no checked result. |
| ownership | External CheckedProof handles retain their binding/proof/upper independently. |
| failure | Nonthrowing owned-container teardown; no semantic failure report is generated. |
| cost | Can traverse every retained claim/cache/frame payload and release complete input/artifact payloads on last ownership. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

```text
ReplayMachine::ReplayMachine(ReplayMachine&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer an entire saved replay owner to another wrapper. |
| inputs / outputs | Moves the exclusive implementation pointer, leaving source empty. |
| invariants | Job, input and cached-key addresses remain stable. |
| ownership | Transfers all maps/frames/artifact owners indirectly through Impl. |
| failure | Noexcept; querying or stepping a moved-from private machine is outside the protocol. |
| cost | Pointer transfer without moving proof payloads or replay frames. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

```text
ReplayMachine& ReplayMachine::operator=(ReplayMachine&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one saved replay implementation with another. |
| inputs / outputs | Default move assignment releases destination checker state and takes the source pointer. |
| invariants | External checked handles remain valid; source becomes empty after a distinct-owner transfer. |
| ownership | Exclusive implementation ownership transfers; immutable result handles keep independent shared ownership. |
| failure | Noexcept; methods require a nonempty implementation after assignment. |
| cost | Transfer itself is small but replacing a live destination may release its complete scratch/maps/jobs. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0035

[Lines 636–636](../../../../../src/planner/certificate.cpp#L636); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UnitResult ReplayMachine::step(const UnitContext& context) { return data_->step(context); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one independent checker transition to the facade resource ledger. |
| inputs / outputs | Forwards depth context and returns advanced, blocked, proof_valid or proof_invalid. |
| invariants | Delegation does not charge a second work unit; the facade owns work/time accounting. |
| ownership | Mutates the exclusive implementation; event carries no borrowed scratch. |
| failure | Allocating checker actions may escape for retry; invalid evidence returns a terminal event. |
| cost | Forwarding overhead is small; the delegated transition can perform size-dependent container work. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0036

[Lines 637–638](../../../../../src/planner/certificate.cpp#L637); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L637-L638:sha256:65c5f087bf54c60d5040f0dd72ba9c8f16fcb99a2cbc5ee8cea0ca956ccb8340
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayMachine: Read checker progress without advancing or creating authority. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0037

[Lines 639–639](../../../../../src/planner/certificate.cpp#L639); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReplayPhase ReplayMachine::phase() const noexcept { return data_->phase; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe the independent replay phase without performing a transition. |
| inputs / outputs | Returns a scalar ReplayPhase from a live nonempty wrapper. |
| invariants | Only complete with a retained checked owner supplies proof authority; mutable progress copies do not. |
| ownership | No internal storage is borrowed by the returned enum. |
| failure | Noexcept observer; moved-from wrapper access is outside the private protocol. |
| cost | One scalar state read. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0038

[Lines 640–641](../../../../../src/planner/certificate.cpp#L640); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L640-L641:sha256:0234633885eaf4f41da71a95a0e64b37148e792bb1dbc003760a298079f2e39d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for depth: Report the checker logical frame depth, including delegated upper validation. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies depth; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for depth come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0039

[Lines 642–642](../../../../../src/planner/certificate.cpp#L642); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ReplayMachine::current_depth() const noexcept { return data_->depth(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose independently tracked checker/upper-validation depth. |
| inputs / outputs | Returns Impl depth including dispatch when nonempty and active. |
| invariants | Empty/terminal replay reports zero; this metric is unrelated to native height. |
| ownership | Returns only a scalar snapshot. |
| failure | Noexcept with live data_ and admitted binding. |
| cost | Uses saved frame counts/depth values, not a traversal. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0040

[Lines 643–644](../../../../../src/planner/certificate.cpp#L643); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L643-L644:sha256:6f31accf85904c373b6a579e4f6ec6823b3559fe467a12a2b2982a69ccf8a8ad
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayMachine: Count committed claim proofs; a verified prefix does not certify the whole-query optimum. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0041

[Lines 645–645](../../../../../src/planner/certificate.cpp#L645); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ReplayMachine::checked_claims() const noexcept { return data_->count_checked; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report how many supplied lower claims completed proof and entered verified. |
| inputs / outputs | Returns the committed checked-claim counter. |
| invariants | A checked prefix cannot raise the public whole-root lower bound before replay completion. |
| ownership | Returns a scalar without exposing the mutable verified map. |
| failure | Noexcept observer requiring a live private machine. |
| cost | One counter read; no recomputation of claim proofs. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0042

[Lines 646–647](../../../../../src/planner/certificate.cpp#L646); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L646-L647:sha256:16965ce13530b80089550604e2ec2f7135f6b455fa643c83589108f3c5d7ce4c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayMachine: Borrow the stable checker diagnostic; owning legacy message conversion happens outside this accessor. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0043

[Lines 648–648](../../../../../src/planner/certificate.cpp#L648); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view ReplayMachine::message() const noexcept { return data_->diagnostic; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the checker static terminal diagnostic without allocating a string. |
| inputs / outputs | Returns an empty or literal-backed diagnostic view set by failure/completion. |
| invariants | Current diagnostics are stable static literals; the accessor does not format progress. |
| ownership | Borrows diagnostic characters and returns no owning string. |
| failure | Noexcept; requires a live machine, and no message proves authority by itself. |
| cost | Copies a string_view header; no formatting or payload traversal. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0044

[Lines 649–650](../../../../../src/planner/certificate.cpp#L649); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L649-L650:sha256:c7aa5afc78cd647f73bf2f2b1175d12f5e924d733927e1c7cea61ccd9d975834
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayMachine: Retain authority only after complete independent replay; finite roots pair with an upper, infinite roots have none. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0045

[Lines 651–651](../../../../../src/planner/certificate.cpp#L651); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const CheckedProof> ReplayMachine::checked() const noexcept { return data_->authority; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain completed independent proof authority for typed result publication. |
| inputs / outputs | Returns null until whole-root success, otherwise a shared CheckedProof with binding/proof and optional upper. |
| invariants | Finite checked root plus matching upper establishes optimum; infinite checked root without upper establishes infeasibility. |
| ownership | The returned owner preserves immutable evidence beyond replay machine lifetime. |
| failure | Noexcept handle copy; an invalid or incomplete replay never exposes authority. |
| cost | Copies shared ownership without retraversing the proof or tree. |
| Design | [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0046

[Lines 652–652](../../../../../src/planner/certificate.cpp#L652); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L652-L652:sha256:1123fc5908e02d7bbfbdec2c7b0d816c8016869dd57b2906f553a96fa4a43a59
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::continuation_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
