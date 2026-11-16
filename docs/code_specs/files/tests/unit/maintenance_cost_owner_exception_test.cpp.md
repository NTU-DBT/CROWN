# `tests/unit/maintenance_cost_owner_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ea5d8ecd563d64cdb39bdff60c0dba17cf432d898787de80a976ed061b6dc9c2`. 600 lines partitioned into 89 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Persistent allocation failures for public cost::capture and cost::estimate. · [reviewed contract](#b0001) |
| [B0002 · 27–37](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L27) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t bytes) | calls std::malloc; returns pointer; growth allocate, malloc; source comment (unverified): // Keep failing every later allocation after the selected position. · [reviewed contract](#b0002) |
| [B0003 · 38–38](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L38) | Explanatory comments or spacing. |  |
| [B0004 · 39–48](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L39) | Type/record definition: struct Fault |  · [reviewed contract](#b0004) |
| [B0005 · 49–50](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L49) | Closes surrounding scope/type. | source comment (unverified): // namespace c03_owner_fault · [reviewed contract](#b0005) |
| [B0006 · 51–51](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L51) | Callable definition: void* operator new(std::size_t bytes) | calls c03_owner_fault::allocate; returns c03_owner_fault::allocate(bytes); growth allocate, new · [reviewed contract](#b0006) |
| [B0007 · 52–52](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L52) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns c03_owner_fault::allocate(bytes); growth allocate, new · [reviewed contract](#b0007) |
| [B0008 · 53–55](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L53) | Callable definition: void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept | calls c03_owner_fault::allocate; returns c03_owner_fault::allocate(bytes); nullptr; growth allocate, new · [reviewed contract](#b0008) |
| [B0009 · 56–58](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L56) | Callable definition: void* operator new\[\](std::size_t bytes, const std::nothrow_t&) noexcept | calls ; returns c03_owner_fault::allocate(bytes); nullptr; growth allocate, new · [reviewed contract](#b0009) |
| [B0010 · 59–59](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L59) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 60–60](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L60) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 61–61](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L61) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0012) |
| [B0013 · 62–62](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L62) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0013) |
| [B0014 · 63–63](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L63) | Callable definition: void operator delete(void* pointer, const std::nothrow_t&) noexcept | calls std::free · [reviewed contract](#b0014) |
| [B0015 · 64–64](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L64) | Callable definition: void operator delete\[\](void* pointer, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0015) |
| [B0016 · 65–75](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L65) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0016) |
| [B0017 · 76–78](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L76) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0017) |
| [B0018 · 79–79](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L79) | Explanatory comments or spacing. |  |
| [B0019 · 80–84](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L80) | Callable definition: auto stamp_image(const ws::Stamp& value) | calls ; returns std::tuple{value.owner.value, value.committed_epoch, value.interval_start_epoch, · [reviewed contract](#b0019) |
| [B0020 · 85–90](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L85) | Callable definition: auto metadata_image(const ws::Metadata& value) | calls ; returns std::tuple{value.attempts, value.committed, value.aborted, value.selected, value.complete, · [reviewed contract](#b0020) |
| [B0021 · 91–94](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L91) | Callable definition: auto workload_memory_image(const ws::Memory& value) | calls ; returns std::tuple{value.object_bytes, value.descriptors_bytes, value.committed_bytes, · [reviewed contract](#b0021) |
| [B0022 · 95–98](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L95) | Callable definition: auto owner_usage_image(const stats::Usage& value) | calls ; returns std::tuple{value.work, value.rows, value.distinct_keys, value.accounted_bytes, · [reviewed contract](#b0022) |
| [B0023 · 99–102](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L99) | Callable definition: auto owner_limits_image(const stats::Limits& value) | calls ; returns std::tuple{value.work, value.rows, value.distinct_keys, value.accounted_bytes, · [reviewed contract](#b0023) |
| [B0024 · 103–107](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L103) | Callable definition: auto ranking_usage_image(const pr::Usage& value) | calls ; returns std::tuple{value.work, value.cells, value.binding_key_bytes, value.payload_bytes, · [reviewed contract](#b0024) |
| [B0025 · 108–114](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L108) | Callable definition: auto ranking_limits_image(const pr::Limits& value) | calls count; returns std::tuple{value.work, value.cells, value.binding_key_bytes, value.payload_bytes, · [reviewed contract](#b0025) |
| [B0026 · 115–118](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L115) | Callable definition: auto mode_identity_image(const pr::ModeIdentity& value) | calls ; returns std::tuple{value.delta_owner, value.requested_mode, value.resolved_mode, · [reviewed contract](#b0026) |
| [B0027 · 119–125](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L119) | Callable definition: auto evidence_identity_image(const pr::EvidenceIdentity& value) | calls mode_identity_image; returns std::tuple{value.owner, value.epoch, value.interval_start, value.reset, · [reviewed contract](#b0027) |
| [B0028 · 126–133](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L126) | Callable definition: auto capture_accounting_image(const pr::CaptureAccounting& value) | calls ranking_limits_image; returns std::tuple{ranking_limits_image(value.processing_limits), value.state, · [reviewed contract](#b0028) |
| [B0029 · 134–136](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L134) | Callable definition: auto owner_stamp_image(const stats::OwnerStamp& value) | calls ; returns std::tuple{value.owner.value, value.sequence, value.layer} · [reviewed contract](#b0029) |
| [B0030 · 137–137](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L137) | Explanatory comments or spacing. |  |
| [B0031 · 138–151](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L138) | Type/record definition: struct WorkloadImage |  · [reviewed contract](#b0031) |
| [B0032 · 152–152](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L152) | Explanatory comments or spacing. |  |
| [B0033 · 153–164](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L153) | Callable definition: WorkloadImage workload_image(const ws::Snapshot& value) | calls descriptors, cells, previous_cells, std::string; returns {std::string(value.plan().physical_sha256()), stamp_image(value.stamp()), value.options(), · [reviewed contract](#b0033) |
| [B0034 · 165–165](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L165) | Explanatory comments or spacing. |  |
| [B0035 · 166–174](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L166) | Type/record definition: struct OwnerImage |  · [reviewed contract](#b0035) |
| [B0036 · 175–175](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L175) | Explanatory comments or spacing. |  |
| [B0037 · 176–180](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L176) | Type/record definition: struct InputWeightImage |  · [reviewed contract](#b0037) |
| [B0038 · 181–186](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L181) | Type/record definition: struct SourceObservationImage |  · [reviewed contract](#b0038) |
| [B0039 · 187–191](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L187) | Type/record definition: struct SourceCardinalityImage |  · [reviewed contract](#b0039) |
| [B0040 · 192–206](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L192) | Type/record definition: struct EvidenceImage |  · [reviewed contract](#b0040) |
| [B0041 · 207–207](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L207) | Explanatory comments or spacing. |  |
| [B0042 · 208–212](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L208) | Type/record definition: struct CandidateContextImage |  · [reviewed contract](#b0042) |
| [B0043 · 213–221](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L213) | Type/record definition: struct CandidateImage |  · [reviewed contract](#b0043) |
| [B0044 · 222–227](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L222) | Type/record definition: struct ProfileImage |  · [reviewed contract](#b0044) |
| [B0045 · 228–228](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L228) | Explanatory comments or spacing. |  |
| [B0046 · 229–229](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L229) | Callable definition: auto limits_image(const stats::Limits& value) | calls owner_limits_image; returns owner_limits_image(value) · [reviewed contract](#b0046) |
| [B0047 · 230–230](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L230) | Explanatory comments or spacing. |  |
| [B0048 · 231–238](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L231) | Callable definition: OwnerImage owner_image(const stats::OwnerCapture& value) | calls check, components, empty, std::string; guard check(value.components().empty(), "cost::capture unexpectedly returned state components");; returns {std::string(value.plan().physical_sha256()), owner_stamp_image(value.stamp()),; source comment (unverified): // cost::capture requests no source-state components; preserve that explicit · [reviewed contract](#b0048) |
| [B0049 · 239–239](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L239) | Explanatory comments or spacing. |  |
| [B0050 · 240–261](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L240) | Callable definition: EvidenceImage evidence_image(const runtime::ranking::RuntimeEvidence& value) | calls inputs, captured, check, session_context; guard check(!value.session_context(),; returns {std::string(inputs.plan().physical_sha256()), std::move(weights),; growth push_back; 3 loop sites · [reviewed contract](#b0050) |
| [B0051 · 262–262](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L262) | Explanatory comments or spacing. |  |
| [B0052 · 263–270](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L263) | Callable definition: CandidateImage candidate_image(const planner::MinimumHeightCandidate& value) | calls context, provenance, structural_key, height; returns {value.structural_key(), value.height(), · [reviewed contract](#b0052) |
| [B0053 · 271–271](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L271) | Explanatory comments or spacing. |  |
| [B0054 · 272–274](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L272) | Callable definition: ProfileImage profile_image(const model::Profile& value) | calls candidate_image, candidate, evidence_image, evidence; returns {candidate_image(value.candidate()), evidence_image(value.evidence()), value.memory_at_capture()} · [reviewed contract](#b0054) |
| [B0055 · 275–275](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L275) | Explanatory comments or spacing. |  |
| [B0056 · 276–280](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L276) | Type/record definition: struct CoefficientImage |  · [reviewed contract](#b0056) |
| [B0057 · 281–288](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L281) | Type/record definition: struct CalibrationImage |  · [reviewed contract](#b0057) |
| [B0058 · 289–289](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L289) | Explanatory comments or spacing. |  |
| [B0059 · 290–301](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L290) | Callable definition: CalibrationImage calibration_image(const model::Calibration& value) | calls check, fit_summary, fit_observations, empty; guard check(!value.fit_summary() && value.fit_observations().empty(),; returns result; 1 loop sites · [reviewed contract](#b0059) |
| [B0060 · 302–302](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L302) | Explanatory comments or spacing. |  |
| [B0061 · 303–308](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L303) | Type/record definition: struct ConfidenceImage |  · [reviewed contract](#b0061) |
| [B0062 · 309–316](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L309) | Type/record definition: struct TermImage |  · [reviewed contract](#b0062) |
| [B0063 · 317–330](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L317) | Type/record definition: struct CandidateEstimateImage |  · [reviewed contract](#b0063) |
| [B0064 · 331–331](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L331) | Explanatory comments or spacing. |  |
| [B0065 · 332–347](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L332) | Callable definition: CandidateEstimateImage candidate_estimate_image(const model::CandidateEstimate& value) | calls profile_image, push_back, stamp_image, candidate_image; returns {candidate_image(value.candidate), std::move(profile), std::move(terms),; growth push_back; 1 loop sites · [reviewed contract](#b0065) |
| [B0066 · 348–349](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L348) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0066) |
| [B0067 · 350–354](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L350) | Callable definition: auto output_demand_image(const model::OutputDemand& value) | calls ; returns std::tuple{value.snapshot_requests, value.snapshot_rows_per_request, · [reviewed contract](#b0067) |
| [B0068 · 355–362](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L355) | Type/record definition: struct ResultImage |  · [reviewed contract](#b0068) |
| [B0069 · 363–363](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L363) | Explanatory comments or spacing. |  |
| [B0070 · 364–371](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L364) | Callable definition: ResultImage result_image(const model::Result& value) | calls candidates, push_back, candidate_estimate_image, input_demand; returns {calibration_image(value.calibration()), std::move(candidates), std::move(input),; growth emplace_back, push_back; 2 loop sites · [reviewed contract](#b0070) |
| [B0071 · 372–373](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L372) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0071) |
| [B0072 · 374–379](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L374) | Callable definition: Relation current_result(const runtime::PhysicalRuntime& owner) | calls results, next, insert, crown::storage::export_row; returns result; growth insert; 1 loop sites · [reviewed contract](#b0072) |
| [B0073 · 380–380](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L380) | Explanatory comments or spacing. |  |
| [B0074 · 381–388](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L381) | Type/record definition: struct RuntimeImage |  · [reviewed contract](#b0074) |
| [B0075 · 389–393](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L389) | Callable definition: RuntimeImage runtime_image(const runtime::PhysicalRuntime& owner) | calls workload_statistics, sequence, ready, has_answer; returns {owner.sequence(), owner.ready(), owner.has_answer(), owner.canonical_state(), · [reviewed contract](#b0075) |
| [B0076 · 394–394](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L394) | Explanatory comments or spacing. |  |
| [B0077 · 395–401](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L395) | Callable definition: void verify_new_profile(const model::Profile& profile,const ProfileImage& expected, const crown::resource::MemoryStatistics& befo… | calls profile_image, check; guard check(image.memory==before,"new profile did not record actual pre-capture memory statistics"); · [reviewed contract](#b0077) |
| [B0078 · 402–402](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L402) | Explanatory comments or spacing. |  |
| [B0079 · 403–417](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L403) | Callable definition: std::size_t count_capture_allocations(Account& account, const crown::resource::MemoryUsage& baseline, const planner::CandidateSna… | calls statistics, model::capture, check, verify_new_profile; guard check(counted.stop == pr::Stop::complete && counted.profile,"successful capture count failed");; returns count · [reviewed contract](#b0079) |
| [B0080 · 418–418](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L418) | Explanatory comments or spacing. |  |
| [B0081 · 419–457](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L419) | Callable definition: std::size_t sweep_capture(Account& account, const crown::resource::MemoryUsage& baseline, const planner::CandidateSnapshot& candi… | calls count_capture_allocations, statistics, fault, model::capture; guard check(triggered && attempted &gt;= position + 1, "capture allocation position was not reached");; returns positions; 1 loop sites · [reviewed contract](#b0081) |
| [B0082 · 458–458](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L458) | Explanatory comments or spacing. |  |
| [B0083 · 459–473](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L459) | Callable definition: std::size_t count_estimate_allocations(Account& account, const crown::resource::MemoryUsage& baseline, const planner::CandidateSn… | calls model::estimate, check, result_image, reset; guard check(counted.stop == pr::Stop::complete && counted.result &&; returns count · [reviewed contract](#b0083) |
| [B0084 · 474–474](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L474) | Explanatory comments or spacing. |  |
| [B0085 · 475–514](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L475) | Callable definition: std::size_t sweep_estimate(Account& account, const crown::resource::MemoryUsage& baseline, const planner::CandidateSnapshot& cand… | calls count_estimate_allocations, statistics, fault, model::estimate; guard check(triggered && attempted &gt;= position + 1, "estimate allocation position was not reached");; returns positions; 1 loop sites · [reviewed contract](#b0085) |
| [B0086 · 515–515](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L515) | Explanatory comments or spacing. |  |
| [B0087 · 516–590](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L516) | Callable definition: void run(bool indexed) | calls c02_test::fixture, c02_test::candidates, candidate_count, candidate; guard check(candidate.has_value(), "fixture candidate missing");; growth insert; 3 loop sites · [reviewed contract](#b0087) |
| [B0088 · 591–592](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L591) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0088) |
| [B0089 · 593–600](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L593) | Callable definition: int main() | calls run, what; returns 1; 1 loop sites · [reviewed contract](#b0089) |

## B0001

[Lines 1–26](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Persistent allocation failures for public cost::capture and cost::estimate.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up the test executable that injects persistent standard-new failures into maintenance-cost capture and estimate. |
| inputs / outputs | The includes load ranking fixtures, reference/indexed runtime support, MemoryAccount, cost types, and fault/image containers. The following harness counts ordinary, array, and nothrow replacement-new attempts before \`malloc\`; a selected position and every later intercepted attempt fail until its Fault scope closes. Aligned replacement overloads are not provided. |
| invariants | The test counts allocations in a successful baseline call, sweeps positions only within that measured call, expects \`allocation_failure\` with no partial Profile/Result and retained state unchanged, then retries once after each complete sweep. |
| ownership | Fault counters and replacement allocator state are test-executable globals/thread-local; account-backed source Profile, receiving Result, runtime, and host-side assertion images remain separate owners. |
| failure | The public \`capture\` and \`estimate\` boundaries are noexcept and map injected \`std::bad_alloc\` to \`allocation_failure\`; the test main catches \`std::exception\` for assertion/setup failure. This harness does not intercept every direct allocation API. |
| cost | Counts are ordinary new attempts, including the failing attempt; no byte, RSS, CPU, or timing measure is taken. Account current bytes are checked separately for receiving-account rollback and retained source ownership. |
| Design | [tests/unit/maintenance_cost_owner_exception_test.cpp](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp §capture and estimate failure boundaries](../../../../../src/runtime/maintenance_cost.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0002

[Lines 27–37](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject one persistent failure at a selected C++ allocation position. |
| inputs / outputs | Increments thread-local count; throws when fail_after is zero; otherwise mallocs max(bytes,1). |
| invariants | All later requests remain denied until Fault closes; size is the replacement-new request. |
| ownership | Returned pointer belongs to caller until matching delete; fault counters are borrowed thread-local state. |
| failure | Selected position or malloc failure throws bad_alloc; no retry. |
| cost | One count and malloc per admitted new/new\[\]; direct malloc/syscalls bypass seam. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:27-37, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0004

[Lines 39–48](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fault {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope a persistent failure position for one public operation. |
| inputs / outputs | Resets allocation count/triggered, sets fail_after and disables it on destruction. |
| invariants | Noncopyable; after selected position subsequent requests stay denied within scope. |
| ownership | RAII guard borrows thread-local state; owns no Profile, Result or runtime. |
| failure | The allocation seam throws bad_alloc; Fault does not catch. |
| cost | Fixed scalar writes; interposes global C++ new/new\[\] only. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:39-48, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0005

[Lines 49–50](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L50:sha256:e8d3723f521681aff4df123f0d5cebc91c9e48c5688090c6ae8834567d589c9e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in maintenance_cost_owner_exception_test.cpp: namespace c03_owner_fault. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/maintenance_cost_owner_exception_test.cpp](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 51–51](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return c03_owner_fault::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the named replacement C++ allocation overload into the C03 persistent-failure seam. |
| inputs / outputs | Receives byte count and returns c03_owner_fault::allocate(bytes). |
| invariants | Every scalar/array form increments the same thread-local allocation count; this file defines no aligned-new overload. |
| ownership | Returned malloc block belongs to the caller until a matching replacement delete calls free. |
| failure | Selected failure or malloc failure propagates std::bad_alloc. |
| cost | One counter update and, if admitted, one malloc call. Direct malloc/syscall requests are invisible to this C++ new seam. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:51-51, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0007

[Lines 52–52](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return c03_owner_fault::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the named replacement C++ allocation overload into the C03 persistent-failure seam. |
| inputs / outputs | Receives byte count and returns c03_owner_fault::allocate(bytes). |
| invariants | Every scalar/array form increments the same thread-local allocation count; this file defines no aligned-new overload. |
| ownership | Returned malloc block belongs to the caller until a matching replacement delete calls free. |
| failure | Selected failure or malloc failure propagates std::bad_alloc. |
| cost | One counter update and, if admitted, one malloc call. Direct malloc/syscall requests are invisible to this C++ new seam. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:52-52, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0008

[Lines 53–55](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the named replacement C++ allocation overload into the C03 persistent-failure seam. |
| inputs / outputs | Receives byte count and forwards to c03_owner_fault::allocate; nothrow overload catches any exception and returns nullptr. |
| invariants | Every scalar/array form increments the same thread-local allocation count; this file defines no aligned-new overload. |
| ownership | Returned malloc block belongs to the caller until a matching replacement delete calls free. |
| failure | Selected failure or malloc failure becomes nullptr through the noexcept nothrow wrapper. |
| cost | One counter update and, if admitted, one malloc call. Direct malloc/syscall requests are invisible to this C++ new seam. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:53-55, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0009

[Lines 56–58](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes, const std::nothrow_t&) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the named replacement C++ allocation overload into the C03 persistent-failure seam. |
| inputs / outputs | Receives byte count and forwards to c03_owner_fault::allocate; nothrow overload catches any exception and returns nullptr. |
| invariants | Every scalar/array form increments the same thread-local allocation count; this file defines no aligned-new overload. |
| ownership | Returned malloc block belongs to the caller until a matching replacement delete calls free. |
| failure | Selected failure or malloc failure becomes nullptr through the noexcept nothrow wrapper. |
| cost | One counter update and, if admitted, one malloc call. Direct malloc/syscall requests are invisible to this C++ new seam. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:56-58, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0010

[Lines 59–59](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the matching replacement C++ new overload. |
| inputs / outputs | Takes the pointer and ignores optional size/nothrow metadata; calls std::free directly. |
| invariants | All delete overloads use the same backing allocator; deallocation does not increment the fault-injection new counter. |
| ownership | Ends caller ownership of the malloc-backed global-new allocation. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One free call; free is not counted as a new attempt and direct allocator/syscall work is not instrumented. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:59-59, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0011

[Lines 60–60](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the matching replacement C++ new overload. |
| inputs / outputs | Takes the pointer and ignores optional size/nothrow metadata; calls std::free directly. |
| invariants | All delete overloads use the same backing allocator; deallocation does not increment the fault-injection new counter. |
| ownership | Ends caller ownership of the malloc-backed global-new allocation. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One free call; free is not counted as a new attempt and direct allocator/syscall work is not instrumented. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:60-60, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0012

[Lines 61–61](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the matching replacement C++ new overload. |
| inputs / outputs | Takes the pointer and ignores optional size/nothrow metadata; calls std::free directly. |
| invariants | All delete overloads use the same backing allocator; deallocation does not increment the fault-injection new counter. |
| ownership | Ends caller ownership of the malloc-backed global-new allocation. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One free call; free is not counted as a new attempt and direct allocator/syscall work is not instrumented. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:61-61, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0013

[Lines 62–62](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the matching replacement C++ new overload. |
| inputs / outputs | Takes the pointer and ignores optional size/nothrow metadata; calls std::free directly. |
| invariants | All delete overloads use the same backing allocator; deallocation does not increment the fault-injection new counter. |
| ownership | Ends caller ownership of the malloc-backed global-new allocation. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One free call; free is not counted as a new attempt and direct allocator/syscall work is not instrumented. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:62-62, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0014

[Lines 63–63](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the matching replacement C++ new overload. |
| inputs / outputs | Takes the pointer and ignores optional size/nothrow metadata; calls std::free directly. |
| invariants | All delete overloads use the same backing allocator; deallocation does not increment the fault-injection new counter. |
| ownership | Ends caller ownership of the malloc-backed global-new allocation. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One free call; free is not counted as a new attempt and direct allocator/syscall work is not instrumented. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:63-63, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0015

[Lines 64–64](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the matching replacement C++ new overload. |
| inputs / outputs | Takes the pointer and ignores optional size/nothrow metadata; calls std::free directly. |
| invariants | All delete overloads use the same backing allocator; deallocation does not increment the fault-injection new counter. |
| ownership | Ends caller ownership of the malloc-backed global-new allocation. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One free call; free is not counted as a new attempt and direct allocator/syscall work is not instrumented. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:64-64, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0016

[Lines 65–75](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace model = crown::runtime::cost;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep test-local short names bound to the concrete fixture, cost, ranking, workload, statistics, account, Profile, and Result types. |
| inputs / outputs | \`c02_test\` supplies the ranking fixture helpers; \`model\`, \`pr\`, \`ws\`, and \`stats\` alias the maintenance-cost, ranking, workload, and statistics namespaces. \`Account\`, \`Profile\`, and \`Result\` name their specific public types. |
| invariants | These aliases change lookup only inside this anonymous namespace; they do not wrap, copy, or extend the referenced types. |
| ownership | No object or resource is owned by a namespace/type alias. |
| failure | Alias resolution errors fail compilation. Runtime allocation failures are handled by the separate Fault wrapper and API calls. |
| cost | No runtime work; aliases are resolved during compilation. |
| Design | [tests/unit/maintenance_cost_owner_exception_test.cpp](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp) |

## B0017

[Lines 76–78](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a test exception when a semantic assertion fails. |
| inputs / outputs | Consumes bool and string_view; builds std::string/runtime_error on false. |
| invariants | Successful check leaves account/runtime unchanged. |
| ownership | Message is borrowed on success and copied into owned exception on failure. |
| failure | False throws runtime_error; main catches std::exception. |
| cost | Success is a branch; diagnostic path may allocate. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:76-78, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0019

[Lines 80–84](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto stamp_image(const ws::Stamp& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot all workload identity and saturation fields for before/after comparison. |
| inputs / outputs | Returns tuple of owner ID, committed/interval epochs, reset/config/segment IDs, format version and saturation flags. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:80-84, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0020

[Lines 85–90](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto metadata_image(const ws::Metadata& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot workload attempt/publication/selection/truncation/action counters. |
| inputs / outputs | Returns tuple including attempts, committed/aborted/selected/complete, truncation, guards/actions, clear/merge/saturation/protocol flags. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:85-90, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0021

[Lines 91–94](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto workload_memory_image(const ws::Memory& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot workload collector’s reported object, vector and route byte categories. |
| inputs / outputs | Returns seven separate counters: object, descriptors, committed, attempt, previous, retained-payload and routes bytes. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:91-94, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0022

[Lines 95–98](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto owner_usage_image(const stats::Usage& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot statistics owner work, row/key, accounted-byte and capacity usage. |
| inputs / outputs | Returns work, rows, distinct keys, accounted bytes and maximum row/histogram/heavy capacities. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:95-98, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0023

[Lines 99–102](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto owner_limits_image(const stats::Limits& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot configured owner-capture ceilings. |
| inputs / outputs | Returns work, rows, distinct keys, accounted bytes, projection width and heavy-key limits. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:99-102, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0024

[Lines 103–107](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto ranking_usage_image(const pr::Usage& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot ranking work and byte domains plus measured active nanoseconds. |
| inputs / outputs | Returns work, cells, binding bytes, payload bytes and separate lowering/identity/replay/normalization work and active time. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:103-107, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0025

[Lines 108–114](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto ranking_limits_image(const pr::Limits& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot all processing ceilings without collapsing work domains. |
| inputs / outputs | Returns work/cell/binding/payload/domain/candidate/score caps and optional active_time duration. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:108-114, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0026

[Lines 115–118](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto mode_identity_image(const pr::ModeIdentity& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot requested/resolved runtime mode and completion choices. |
| inputs / outputs | Returns delta owner, requested/resolved modes and completion, live-maintenance and view. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:115-118, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0027

[Lines 119–125](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto evidence_identity_image(const pr::EvidenceIdentity& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot ranking evidence identity and collection policy. |
| inputs / outputs | Returns owner/epoch/reset/config/segment/format, collection caps/period/offset/detail budget, nested modes, pending and saturation flags. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:119-125, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0028

[Lines 126–133](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto capture_accounting_image(const pr::CaptureAccounting& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot requested and returned component state plus capture limits/usage. |
| inputs / outputs | Returns processing limits, state flags, requested/returned components, state caps and current work/row/key/byte/descriptors/cell totals. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:126-133, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0029

[Lines 134–136](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto owner_stamp_image(const stats::OwnerStamp& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot statistics-owner identity, sequence and layer. |
| inputs / outputs | Returns owner value, sequence and layer. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:134-136, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0031

[Lines 138–151](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L138); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WorkloadImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`WorkloadImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`physical_hash\`, \`stamp\`, \`options\`, \`modes\`, \`previous_modes\`, \`descriptors\`, \`cells\`, \`previous_cells\`, \`metadata\`, \`previous_metadata\`, \`memory\`, \`pending\`, \`has_previous\`, \`replaced\`, \`previous_start\`, \`previous_end\`, \`detail_availability\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. Dynamic ownership includes \`physical_hash\`, \`descriptors\`, \`cells\`, \`previous_cells\`. |
| failure | Construction/copy of string or vector members may throw bad_alloc; scalar/enum fields have no independent failure path. |
| cost | Record copies are fixed-field copies plus dynamic copies proportional to \`physical_hash\`, \`descriptors\`, \`cells\`, \`previous_cells\`. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:138-151, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0033

[Lines 153–164](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WorkloadImage workload_image(const ws::Snapshot& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy the current and previous workload snapshot needed for runtime invariance checks. |
| inputs / outputs | Copies physical plan hash, stamp/options/modes, descriptors/current/previous cells, current/previous metadata, memory, pending/replaced/previous interval and detail availability. |
| invariants | The image includes both current and previous metadata/cells, \`has_previous\`/\`replaced\`, interval bounds and detail availability; default equality compares all. |
| ownership | Owns the copied physical hash, descriptor/cell vectors and value fields; Snapshot spans and plan are borrowed only during conversion. |
| failure | String/vector copies can throw bad_alloc; conversion is called outside the active capture fault scope for preservation checks. |
| cost | Copies O(descriptors+cells+previous cells) records plus plan hash; dynamic vectors/string own those bytes. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:153-164, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0035

[Lines 166–174](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L166); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OwnerImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`OwnerImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`physical_hash\`, \`stamp\`, \`availability\`, \`physical_source_scope\`, \`usage\`, \`limits\`, \`requested_components\`, \`component_count\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. Dynamic ownership includes \`physical_hash\`. |
| failure | Construction/copy of string or vector members may throw bad_alloc; scalar/enum fields have no independent failure path. |
| cost | Record copies are fixed-field copies plus dynamic copies proportional to \`physical_hash\`. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:166-174, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0037

[Lines 176–180](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L176); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputWeightImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`InputWeightImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`table\`, \`inserts\`, \`erases\`, \`changed\`, \`noop\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. |
| failure | The value record itself has no dynamic member allocation or independent failure path. |
| cost | Record copies are fixed-field copies; no dynamic allocation. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:176-180, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0038

[Lines 181–186](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L181); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceObservationImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`SourceObservationImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`table\`, \`state\`, \`cardinality\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. |
| failure | The value record itself has no dynamic member allocation or independent failure path. |
| cost | Record copies are fixed-field copies; no dynamic allocation. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:181-186, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0039

[Lines 187–191](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L187); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceCardinalityImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`SourceCardinalityImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`table\`, \`rows\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. |
| failure | The value record itself has no dynamic member allocation or independent failure path. |
| cost | Record copies are fixed-field copies; no dynamic allocation. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:187-191, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0040

[Lines 192–206](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L192); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EvidenceImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`EvidenceImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`physical_hash\`, \`weights\`, \`source_observations\`, \`sources\`, \`identity\`, \`accounting\`, \`depth_reasons\`, \`memory_reasons\`, \`denominator\`, \`preparation_usage\`, \`owner\`, \`workload\`, \`has_session_context\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. Dynamic ownership includes \`physical_hash\`, \`weights\`, \`source_observations\`, \`sources\`, \`owner\`, \`workload\`. |
| failure | Construction/copy of string or vector members may throw bad_alloc; scalar/enum fields have no independent failure path. |
| cost | Record copies are fixed-field copies plus dynamic copies proportional to \`physical_hash\`, \`weights\`, \`source_observations\`, \`sources\`, \`owner\`, \`workload\`. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:192-206, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0042

[Lines 208–212](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L208); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateContextImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`CandidateContextImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`updates\`, \`arithmetic\`, \`planner\`, \`optimization\`, \`cost_model\`, \`canonicalization\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. Dynamic ownership includes \`arithmetic\`, \`planner\`, \`optimization\`, \`cost_model\`, \`canonicalization\`. |
| failure | Construction/copy of string or vector members may throw bad_alloc; scalar/enum fields have no independent failure path. |
| cost | Record copies are fixed-field copies plus dynamic copies proportional to \`arithmetic\`, \`planner\`, \`optimization\`, \`cost_model\`, \`canonicalization\`. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:208-212, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0043

[Lines 213–221](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L213); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`CandidateImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`structural_key\`, \`height\`, \`context\`, \`source\`, \`family\`, \`provenance_sequence\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. Dynamic ownership includes \`structural_key\`, \`context\`. |
| failure | Construction/copy of string or vector members may throw bad_alloc; scalar/enum fields have no independent failure path. |
| cost | Record copies are fixed-field copies plus dynamic copies proportional to \`structural_key\`, \`context\`. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:213-221, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0044

[Lines 222–227](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L222); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProfileImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`ProfileImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`candidate\`, \`evidence\`, \`memory\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. Dynamic ownership includes \`candidate\`, \`evidence\`. |
| failure | Construction/copy of string or vector members may throw bad_alloc; scalar/enum fields have no independent failure path. |
| cost | Record copies are fixed-field copies plus dynamic copies proportional to \`candidate\`, \`evidence\`. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:222-227, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0046

[Lines 229–229](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L229); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto limits_image(const stats::Limits& value) { return owner_limits_image(value); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward the owner limits value through owner_limits_image. |
| inputs / outputs | Returns the same six-field limits tuple; no alternate mapping. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:229-229, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0048

[Lines 231–238](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OwnerImage owner_image(const stats::OwnerCapture& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the owner-capture report while enforcing the cost fixture’s empty-component shape. |
| inputs / outputs | Returns physical hash/stamp, availability and physical scope, usage/limits, requested components and component count after requiring components().empty(). |
| invariants | An owner capture with any returned state component fails immediately; cost::capture is expected to request none. |
| ownership | Copies plan hash and scalar image; OwnerCapture and its component span are borrowed. |
| failure | Empty-component shape mismatch raises runtime_error; hash allocation can raise bad_alloc. |
| cost | Scales with physical hash bytes; otherwise fixed scalar copies. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:231-238, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0050

[Lines 240–261](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EvidenceImage evidence_image(const runtime::ranking::RuntimeEvidence& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy physical RuntimeEvidence and its combined owner/workload capture into an equality image. |
| inputs / outputs | Requires no session context and a present combined capture; copies weights, source observations/cardinalities, identity/accounting/reasons/denominator/preparation usage and nested owner/workload. |
| invariants | PhysicalRuntime evidence must have combined capture, no QuerySession context, and every source/input/workload fact is copied. |
| ownership | Owns vectors of weights, source observations/cardinalities and nested owner/workload images; RuntimeEvidence spans/capture are borrowed. |
| failure | Missing capture/unexpected session context throws runtime_error; vectors/strings may throw bad_alloc. |
| cost | O(weights+observations+sources+workload cells/descriptors) plus copied strings; this is oracle cost. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:240-261, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0052

[Lines 263–270](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateImage candidate_image(const planner::MinimumHeightCandidate& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy candidate structural key, height, version context and provenance. |
| inputs / outputs | Returns key/height, update profile, arithmetic/planner/optimization/cost/canonicalization IDs and provenance source/family/sequence. |
| invariants | Returns key/height, update profile, arithmetic/planner/optimization/cost/canonicalization IDs and provenance source/family/sequence. Equality/checks use the full value image and leave the source object unchanged. |
| ownership | Inputs are borrowed; any returned strings/vectors/Relation/ProfileImage own their copies and live only as test oracle values. |
| failure | Copy growth or failed equality check may raise bad_alloc/runtime_error; these checks do not change the C03 operation stop. |
| cost | Copy cost scales with the named candidate/evidence/result rows, string bytes, terms or input entries; outside injected call. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:263-270, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0054

[Lines 272–274](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ProfileImage profile_image(const model::Profile& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose candidate/evidence equality images with capture-time account statistics. |
| inputs / outputs | Returns candidate_image, evidence_image and memory_at_capture. |
| invariants | Returns candidate_image, evidence_image and memory_at_capture. Equality/checks use the full value image and leave the source object unchanged. |
| ownership | Inputs are borrowed; any returned strings/vectors/Relation/ProfileImage own their copies and live only as test oracle values. |
| failure | Copy growth or failed equality check may raise bad_alloc/runtime_error; these checks do not change the C03 operation stop. |
| cost | Copy cost scales with the named candidate/evidence/result rows, string bytes, terms or input entries; outside injected call. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:272-274, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0056

[Lines 276–280](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L276); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CoefficientImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`CoefficientImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`rate\`, \`samples\`, \`units\`, \`elapsed_ns\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. |
| failure | The value record itself has no dynamic member allocation or independent failure path. |
| cost | Record copies are fixed-field copies; no dynamic allocation. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:276-280, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0057

[Lines 281–288](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L281); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CalibrationImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`CalibrationImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`context\`, \`backend\`, \`coefficients\`, \`origin\`, \`has_fit_summary\`, \`raw_observation_count\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. Dynamic ownership includes \`context\`, \`backend\`. |
| failure | Construction/copy of string or vector members may throw bad_alloc; scalar/enum fields have no independent failure path. |
| cost | Record copies are fixed-field copies plus dynamic copies proportional to \`context\`, \`backend\`. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:281-288, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0059

[Lines 290–301](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L290); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CalibrationImage calibration_image(const model::Calibration& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy isolated calibration coefficients and assert there is no fitting history. |
| inputs / outputs | Requires no fit summary/observations; returns context/backend/origin and optional component rates, samples, units and elapsed time. |
| invariants | Requires no fit summary/observations; returns context/backend/origin and optional component rates, samples, units and elapsed time. Equality/checks use the full value image and leave the source object unchanged. |
| ownership | Inputs are borrowed; any returned strings/vectors/Relation/ProfileImage own their copies and live only as test oracle values. |
| failure | Copy growth or failed equality check may raise bad_alloc/runtime_error; these checks do not change the C03 operation stop. |
| cost | Copy cost scales with the named candidate/evidence/result rows, string bytes, terms or input entries; outside injected call. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:290-301, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0061

[Lines 303–308](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L303); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ConfidenceImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`ConfidenceImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`basis\`, \`availability\`, \`complete_inputs\`, \`observed_events\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. |
| failure | The value record itself has no dynamic member allocation or independent failure path. |
| cost | Record copies are fixed-field copies; no dynamic allocation. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:303-308, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0062

[Lines 309–316](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L309); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TermImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`TermImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`component\`, \`descriptor\`, \`units\`, \`nanoseconds\`, \`confidence\`, \`issues\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. |
| failure | The value record itself has no dynamic member allocation or independent failure path. |
| cost | Record copies are fixed-field copies; no dynamic allocation. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:309-316, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0063

[Lines 317–330](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L317); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateEstimateImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`CandidateEstimateImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`candidate\`, \`observations\`, \`terms\`, \`maintenance_ns\`, \`snapshot_ns\`, \`delta_ns\`, \`encoding_ns\`, \`checkpoint_ns\`, \`annotation_ns\`, \`total_ns\`, \`observed_stamp\`, \`observed_modes\`, \`memory_budget_bytes\`, \`memory_at_capture\`, \`future_memory_unknown\`, \`issues\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. Dynamic ownership includes \`candidate\`, \`observations\`, \`terms\`, \`observed_modes\`, \`memory_at_capture\`. |
| failure | Construction/copy of string or vector members may throw bad_alloc; scalar/enum fields have no independent failure path. |
| cost | Record copies are fixed-field copies plus dynamic copies proportional to \`candidate\`, \`observations\`, \`terms\`, \`observed_modes\`, \`memory_at_capture\`. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:317-330, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0065

[Lines 332–347](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L332); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateEstimateImage candidate_estimate_image(const model::CandidateEstimate& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one candidate estimate, terms, confidence facts and optional cost totals. |
| inputs / outputs | Returns candidate, optional observations, ordered terms, optional component/total times, stamp/modes, memory budget/capture and issue flags. |
| invariants | Returns candidate, optional observations, ordered terms, optional component/total times, stamp/modes, memory budget/capture and issue flags. Equality/checks use the full value image and leave the source object unchanged. |
| ownership | Inputs are borrowed; any returned strings/vectors/Relation/ProfileImage own their copies and live only as test oracle values. |
| failure | Copy growth or failed equality check may raise bad_alloc/runtime_error; these checks do not change the C03 operation stop. |
| cost | Copy cost scales with the named candidate/evidence/result rows, string bytes, terms or input entries; outside injected call. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:332-347, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0066

[Lines 348–349](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L348); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using InputDemandImage = std::tuple<std::size_t, ws::Operation, std::uint64_t>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the compact host-side image row used to compare returned input-demand facts across success, failure, and retry checks. |
| inputs / outputs | Each tuple stores table index, workload operation, and input count; \`result_image()\` constructs one for every \`Result::input_demand()\` entry. |
| invariants | The image preserves those three declared demand fields only; it is not the whole Result and adds no inference about measured input events. |
| ownership | The alias itself owns nothing. The caller’s \`std::vector&lt;InputDemandImage&gt;\` owns copied tuples and is separate from the result’s account-funded data. |
| failure | No failure path in the alias. Image-vector allocation can throw outside the injected call boundary when the later comparison constructs an image. |
| cost | The tuple is fixed-size; vector growth for the image is host test overhead and excluded from the cost Result account and the count captured before image comparison. |
| Design | [tests/unit/maintenance_cost_owner_exception_test.cpp](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp §InputDemand and Result](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp §Result storage](../../../../../src/runtime/maintenance_cost.cpp), [tests/unit/maintenance_cost_owner_exception_test.cpp §result_image](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp) |

## B0067

[Lines 350–354](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L350); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto output_demand_image(const model::OutputDemand& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot each requested output dimension and derived total separately. |
| inputs / outputs | Returns snapshot requests/rows, delta epochs/rows, encoded bytes, checkpoint requests/bytes, annotation changes and snapshot_rows_total. |
| invariants | The returned value tuple includes each listed field in a fixed order, so equality detects a change to any listed fact. |
| ownership | Returns an owning scalar/value tuple; source API reference is borrowed only during field reads. |
| failure | No production API call or state mutation occurs; ordinary tuple/value construction may only fail through language/runtime exception mechanisms. |
| cost | Fixed field reads and tuple construction; no dynamic string/vector copy in these scalar images. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:350-354, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0068

[Lines 355–362](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L355); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResultImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`ResultImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`calibration\`, \`candidates\`, \`input\`, \`output\`, \`usage\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. Dynamic ownership includes \`calibration\`, \`candidates\`, \`input\`. |
| failure | Construction/copy of string or vector members may throw bad_alloc; scalar/enum fields have no independent failure path. |
| cost | Record copies are fixed-field copies plus dynamic copies proportional to \`calibration\`, \`candidates\`, \`input\`. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:355-362, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0070

[Lines 364–371](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResultImage result_image(const model::Result& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an owned Result oracle across calibration, candidate estimates, demands and ranking usage. |
| inputs / outputs | Returns calibration image, ordered candidate images, ordered input-demand triples, output-demand tuple and usage tuple. |
| invariants | Returns calibration image, ordered candidate images, ordered input-demand triples, output-demand tuple and usage tuple. Equality/checks use the full value image and leave the source object unchanged. |
| ownership | Inputs are borrowed; any returned strings/vectors/Relation/ProfileImage own their copies and live only as test oracle values. |
| failure | Copy growth or failed equality check may raise bad_alloc/runtime_error; these checks do not change the C03 operation stop. |
| cost | Copy cost scales with the named candidate/evidence/result rows, string bytes, terms or input entries; outside injected call. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:364-371, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0071

[Lines 372–373](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L372); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Relation = crown::Relation;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Give the immediately following test-only \`current_result()\` helper the concrete \`crown::Relation\` set type for exported runtime rows. |
| inputs / outputs | \`Relation\` aliases \`crown::Relation\` (\`std::set&lt;Row&gt;\`). The following \`current_result(owner)\` helper uses it while draining \`owner.results()\` and inserting exported tuple values; that helper starts after this selected alias-only range. |
| invariants | The alias adds no container semantics. The subsequent helper compares exported logical set rows; this row image is not an account-byte report and does not mean cost capture retains current result payloads. |
| ownership | The alias owns nothing. In the following helper, the local set owns exported host-side \`Row\` copies after cursor traversal; the \`PhysicalRuntime\` owns its separate storage and result rows. |
| failure | The alias has no runtime failure path. The next helper can throw while reading its cursor, exporting values, or growing the host set; the test constructs that image after each injected Fault scope has ended. |
| cost | The alias has no runtime cost. The next helper traverses the current result and builds host-side row/set copies in proportion to returned rows; that assertion-image work is outside the injected count and cost Result account, not a capture/estimate CPU measurement. |
| Design | [tests/unit/maintenance_cost_owner_exception_test.cpp](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp), [include/crown/ir/model.hpp §Relation alias](../../../../../include/crown/ir/model.hpp), [include/crown/runtime/physical.hpp §results cursor](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/maintenance_cost.hpp §capture](../../../../../include/crown/runtime/maintenance_cost.hpp) |

## B0072

[Lines 374–379](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L374); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation current_result(const runtime::PhysicalRuntime& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export current runtime tuples into an owning public Relation image. |
| inputs / outputs | Walks results cursor to exhaustion and calls export_row for each tuple; returns copied Relation. |
| invariants | Walks results cursor to exhaustion and calls export_row for each tuple; returns copied Relation. Equality/checks use the full value image and leave the source object unchanged. |
| ownership | Inputs are borrowed; any returned strings/vectors/Relation/ProfileImage own their copies and live only as test oracle values. |
| failure | Copy growth or failed equality check may raise bad_alloc/runtime_error; these checks do not change the C03 operation stop. |
| cost | Copy cost scales with the named candidate/evidence/result rows, string bytes, terms or input entries; outside injected call. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:374-379, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0074

[Lines 381–388](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L381); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RuntimeImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the \`RuntimeImage\` value image used by the cost exception oracle. |
| inputs / outputs | The value record stores \`sequence\`, \`ready\`, \`has_answer\`, \`canonical\`, \`current_result\`, \`workload\`. |
| invariants | Default equality compares every stored member; optionals and status flags are retained separately rather than normalized. |
| ownership | Owns each listed by-value field; source runtime/API image is not retained. Dynamic ownership includes \`canonical\`, \`current_result\`, \`workload\`. |
| failure | Construction/copy of string or vector members may throw bad_alloc; scalar/enum fields have no independent failure path. |
| cost | Record copies are fixed-field copies plus dynamic copies proportional to \`canonical\`, \`current_result\`, \`workload\`. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:381-388, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0075

[Lines 389–393](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L389); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RuntimeImage runtime_image(const runtime::PhysicalRuntime& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture sequence/readiness/canonical output and workload state for failure comparisons. |
| inputs / outputs | Returns sequence, ready/answer flags, canonical state, owning current-result Relation and deep workload image. |
| invariants | Returns sequence, ready/answer flags, canonical state, owning current-result Relation and deep workload image. Equality/checks use the full value image and leave the source object unchanged. |
| ownership | Inputs are borrowed; any returned strings/vectors/Relation/ProfileImage own their copies and live only as test oracle values. |
| failure | Copy growth or failed equality check may raise bad_alloc/runtime_error; these checks do not change the C03 operation stop. |
| cost | Copy cost scales with the named candidate/evidence/result rows, string bytes, terms or input entries; outside injected call. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:389-393, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0077

[Lines 395–401](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L395); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify_new_profile(const model::Profile& profile,const ProfileImage& expected,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the new capture Profile to preserve candidate/evidence and store exact pre-capture memory stats. |
| inputs / outputs | Images the returned profile, compares its memory to \`before\`, then compares all immutable fields with expected. |
| invariants | Images the returned profile, compares its memory to \`before\`, then compares all immutable fields with expected. Equality/checks use the full value image and leave the source object unchanged. |
| ownership | Inputs are borrowed; any returned strings/vectors/Relation/ProfileImage own their copies and live only as test oracle values. |
| failure | Copy growth or failed equality check may raise bad_alloc/runtime_error; these checks do not change the C03 operation stop. |
| cost | Copy cost scales with the named candidate/evidence/result rows, string bytes, terms or input entries; outside injected call. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:395-401, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0079

[Lines 403–417](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L403); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t count_capture_allocations(Account& account, const crown::resource::MemoryUsage& baseline,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count successful capture new requests and establish a complete-profile baseline. |
| inputs / outputs | Calls capture once, images result, checks pre-capture account stats and resets temporary Profile. |
| invariants | Requires complete+profile and 0&lt;count&lt;8192; account current returns to retained baseline after reset. |
| ownership | Candidate/runtime borrowed; temporary Profile released; retained Profile is separate. |
| failure | Unexpected stop/profile absence fails the baseline check. |
| cost | Counts replacement C++ new/new\[\] separately from account requested and payload bytes. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:403-417, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0081

[Lines 419–457](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L419); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_capture(Account& account, const crown::resource::MemoryUsage& baseline,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail each measured capture request and prove no partial Profile or source mutation escapes. |
| inputs / outputs | Runs capture at each position, then checks stop/profile, two accounts, retained images and runtime; finally retries. |
| invariants | Every position is reached; allocation_failure has no profile; source/runtime/results remain equal; retry returns account to baseline. |
| ownership | Retained Profile/Result/runtime survive each call; the failed temporary is local; result account is independent. |
| failure | Public capture returns allocation_failure rather than partial output; injector scope covers call only. |
| cost | N fault runs plus baseline and retry, N measured C++ new requests; image comparisons are outside injection. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:419-457, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0083

[Lines 459–473](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L459); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t count_estimate_allocations(Account& account, const crown::resource::MemoryUsage& baseline,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count successful estimate new requests and capture its Result oracle. |
| inputs / outputs | Calls estimate, copies result image and resets temporary Result. |
| invariants | Requires complete result match, 0&lt;count&lt;16384 and account current return to baseline. |
| ownership | Profiles/calibration/candidates borrowed; temporary result released; retained result separate. |
| failure | A mismatch/stop fails this baseline; no catch or retry. |
| cost | Counts replacement C++ new/new\[\] only; MemoryAccount requested bytes are a separate measure. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:459-473, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0085

[Lines 475–514](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L475); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_estimate(Account& account, const crown::resource::MemoryUsage& baseline,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail every estimate request while preserving retained Result/Profile and source runtime/account. |
| inputs / outputs | For each index calls estimate under Fault, checks allocation_failure/no result and retained images/accounts, then retries. |
| invariants | All source facts and byte baselines match after failure; retry matches expected Result and returns receiver to baseline. |
| ownership | Source Profile/runtime and independent owner account outlive attempt; request/calibration borrow inputs. |
| failure | Failure is public allocation_failure, not a partial Result; persistent injector ends after call. |
| cost | N failures+retry using measured new positions; owning image comparisons happen outside Fault. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:475-514, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0087

[Lines 516–590](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L516); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a real physical runtime, retain one captured cost Profile/estimated Result and fault-sweep both public operations. |
| inputs / outputs | Selects native candidate from exact fixture; lowers reference/indexed, applies one insert, calibrates one sample/unit per component and requests two R inserts. |
| invariants | Only native candidate has observations; others carry profile_missing; baseline capture/estimate preserve runtime/workload and owner usage. |
| ownership | Runtime uses source account; retained Profile is copied; calibration/Result use separate 64 MiB account. |
| failure | Baseline setup errors fail checks; sweeps require allocation_failure with no partial result; indexed toggles backend options only. |
| cost | One capture and estimate sweep per backend; positions measured. Search and image-copy oracle costs are outside injected calls. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:516-590, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |

## B0088

[Lines 591–592](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L591); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L591-L592:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in maintenance_cost_owner_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/maintenance_cost_owner_exception_test.cpp](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0089

[Lines 593–600](../../../../../tests/unit/maintenance_cost_owner_exception_test.cpp#L593); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the owner exception case for reference and indexed runtime. |
| inputs / outputs | Calls run(false), then run(true); catches std::exception and returns failure status. |
| invariants | Both backend cases must finish for normal exit. |
| ownership | Each run owns fixture/runtime/profile/accounts locally; no data crosses runs. |
| failure | Catches once; no retry at main. |
| cost | Two full capture/estimate sweeps; no malloc/syscall instrumentation. |
| Design | tests/unit/maintenance_cost_owner_exception_test.cpp:593-600, tests/support/ranking_fixture.hpp:1-27, tests/support/indexed_runtime_fixture.hpp:1-21, [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), Refactor.md:1283-1285 |
