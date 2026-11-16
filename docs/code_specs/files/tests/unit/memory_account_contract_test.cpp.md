# `tests/unit/memory_account_contract_test.cpp` — block usage map

[Source](../../../../../tests/unit/memory_account_contract_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `9c8e3bb5b34e7db932a1fa551a5319fc49135c877375b043cb5e9a8cb009bf2f`. 3648 lines partitioned into 177 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–36](../../../../../tests/unit/memory_account_contract_test.cpp#L1) | Imports dependencies; controls preprocessing. | growth new · [reviewed contract](#b0001) |
| [B0002 · 37–41](../../../../../tests/unit/memory_account_contract_test.cpp#L37) | declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Test-executable-only replacement new/delete. The registry and observation · [reviewed contract](#b0002) |
| [B0003 · 42–42](../../../../../tests/unit/memory_account_contract_test.cpp#L42) | Type/record definition: struct Record |  · [reviewed contract](#b0003) |
| [B0004 · 43–58](../../../../../tests/unit/memory_account_contract_test.cpp#L43) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 59–70](../../../../../tests/unit/memory_account_contract_test.cpp#L59) | Type/record definition: struct Observation |  · [reviewed contract](#b0005) |
| [B0006 · 71–71](../../../../../tests/unit/memory_account_contract_test.cpp#L71) | Explanatory comments or spacing. |  |
| [B0007 · 72–75](../../../../../tests/unit/memory_account_contract_test.cpp#L72) | Callable definition: inline Observation observe() noexcept | calls ; returns {calls, successful_calls, freed_calls, successful_bytes, freed_bytes, · [reviewed contract](#b0007) |
| [B0008 · 76–76](../../../../../tests/unit/memory_account_contract_test.cpp#L76) | Explanatory comments or spacing. |  |
| [B0009 · 77–85](../../../../../tests/unit/memory_account_contract_test.cpp#L77) | Callable definition: inline void position(std::size_t bytes) | calls max, size · [reviewed contract](#b0009) |
| [B0010 · 86–86](../../../../../tests/unit/memory_account_contract_test.cpp#L86) | Explanatory comments or spacing. |  |
| [B0011 · 87–100](../../../../../tests/unit/memory_account_contract_test.cpp#L87) | Callable definition: inline void remember(void* address, std::size_t bytes) noexcept | calls ; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 101–101](../../../../../tests/unit/memory_account_contract_test.cpp#L101) | Explanatory comments or spacing. |  |
| [B0013 · 102–116](../../../../../tests/unit/memory_account_contract_test.cpp#L102) | Callable definition: inline void forget(void* address) noexcept | calls ; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 117–117](../../../../../tests/unit/memory_account_contract_test.cpp#L117) | Explanatory comments or spacing. |  |
| [B0015 · 118–125](../../../../../tests/unit/memory_account_contract_test.cpp#L118) | Callable definition: \[\[gnu::noinline\]\] inline void* allocate(std::size_t bytes) | calls position, std::malloc, remember; returns address; growth allocate, malloc · [reviewed contract](#b0015) |
| [B0016 · 126–126](../../../../../tests/unit/memory_account_contract_test.cpp#L126) | Explanatory comments or spacing. |  |
| [B0017 · 127–146](../../../../../tests/unit/memory_account_contract_test.cpp#L127) | Callable definition: \[\[gnu::noinline\]\] inline void* aligned(std::size_t bytes, std::size_t alignment) | calls position, std::malloc, remember, max; returns address; address; growth malloc · [reviewed contract](#b0017) |
| [B0018 · 147–147](../../../../../tests/unit/memory_account_contract_test.cpp#L147) | Explanatory comments or spacing. |  |
| [B0019 · 148–151](../../../../../tests/unit/memory_account_contract_test.cpp#L148) | Callable definition: \[\[gnu::noinline\]\] inline void release(void* address) noexcept | calls forget, std::free · [reviewed contract](#b0019) |
| [B0020 · 152–152](../../../../../tests/unit/memory_account_contract_test.cpp#L152) | Explanatory comments or spacing. |  |
| [B0021 · 153–168](../../../../../tests/unit/memory_account_contract_test.cpp#L153) | Type/record definition: class Scope |  · [reviewed contract](#b0021) |
| [B0022 · 169–170](../../../../../tests/unit/memory_account_contract_test.cpp#L169) | Closes surrounding scope/type. | source comment (unverified): // namespace memory_trace · [reviewed contract](#b0022) |
| [B0023 · 171–171](../../../../../tests/unit/memory_account_contract_test.cpp#L171) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n) | calls memory_trace::allocate; returns memory_trace::allocate(n); growth allocate, new · [reviewed contract](#b0023) |
| [B0024 · 172–172](../../../../../tests/unit/memory_account_contract_test.cpp#L172) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n) | calls ; returns memory_trace::allocate(n); growth allocate, new · [reviewed contract](#b0024) |
| [B0025 · 173–173](../../../../../tests/unit/memory_account_contract_test.cpp#L173) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n, const std::nothrow_t&) noexcept | calls memory_trace::allocate; returns memory_trace::allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0025) |
| [B0026 · 174–174](../../../../../tests/unit/memory_account_contract_test.cpp#L174) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n, const std::nothrow_t&) noexcept | calls ; returns memory_trace::allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0026) |
| [B0027 · 175–175](../../../../../tests/unit/memory_account_contract_test.cpp#L175) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n, std::align_val_t a) | calls memory_trace::aligned; returns memory_trace::aligned(n, static_cast&lt;std::size_t&gt;(a)); growth new · [reviewed contract](#b0027) |
| [B0028 · 176–176](../../../../../tests/unit/memory_account_contract_test.cpp#L176) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n, std::align_val_t a) | calls ; returns memory_trace::aligned(n, static_cast&lt;std::size_t&gt;(a)); growth new · [reviewed contract](#b0028) |
| [B0029 · 177–177](../../../../../tests/unit/memory_account_contract_test.cpp#L177) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n, std::align_val_t a, const std::nothrow_t&) noexcept | calls memory_trace::aligned; returns memory_trace::aligned(n, static_cast&lt;std::size_t&gt;(a)); nullptr; growth new · [reviewed contract](#b0029) |
| [B0030 · 178–178](../../../../../tests/unit/memory_account_contract_test.cpp#L178) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n, std::align_val_t a, const std::nothrow_t&) noexcept | calls ; returns memory_trace::aligned(n, static_cast&lt;std::size_t&gt;(a)); nullptr; growth new · [reviewed contract](#b0030) |
| [B0031 · 179–179](../../../../../tests/unit/memory_account_contract_test.cpp#L179) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p) noexcept | calls memory_trace::release · [reviewed contract](#b0031) |
| [B0032 · 180–180](../../../../../tests/unit/memory_account_contract_test.cpp#L180) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0032) |
| [B0033 · 181–181](../../../../../tests/unit/memory_account_contract_test.cpp#L181) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::size_t) noexcept | calls memory_trace::release · [reviewed contract](#b0033) |
| [B0034 · 182–182](../../../../../tests/unit/memory_account_contract_test.cpp#L182) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::size_t) noexcept | calls  · [reviewed contract](#b0034) |
| [B0035 · 183–183](../../../../../tests/unit/memory_account_contract_test.cpp#L183) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, const std::nothrow_t&) noexcept | calls memory_trace::release · [reviewed contract](#b0035) |
| [B0036 · 184–184](../../../../../tests/unit/memory_account_contract_test.cpp#L184) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0036) |
| [B0037 · 185–185](../../../../../tests/unit/memory_account_contract_test.cpp#L185) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::align_val_t) noexcept | calls memory_trace::release · [reviewed contract](#b0037) |
| [B0038 · 186–186](../../../../../tests/unit/memory_account_contract_test.cpp#L186) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::align_val_t) noexcept | calls  · [reviewed contract](#b0038) |
| [B0039 · 187–187](../../../../../tests/unit/memory_account_contract_test.cpp#L187) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::size_t, std::align_val_t) noexcept | calls memory_trace::release · [reviewed contract](#b0039) |
| [B0040 · 188–188](../../../../../tests/unit/memory_account_contract_test.cpp#L188) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::size_t, std::align_val_t) noexcept | calls  · [reviewed contract](#b0040) |
| [B0041 · 189–189](../../../../../tests/unit/memory_account_contract_test.cpp#L189) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::align_val_t, const std::nothrow_t&) noexcept | calls memory_trace::release · [reviewed contract](#b0041) |
| [B0042 · 190–190](../../../../../tests/unit/memory_account_contract_test.cpp#L190) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::align_val_t, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0042) |
| [B0043 · 191–200](../../../../../tests/unit/memory_account_contract_test.cpp#L191) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0043) |
| [B0044 · 201–203](../../../../../tests/unit/memory_account_contract_test.cpp#L201) | Callable definition: void verify(bool condition, const char* message) | calls std::runtime_error · [reviewed contract](#b0044) |
| [B0045 · 204–204](../../../../../tests/unit/memory_account_contract_test.cpp#L204) | Explanatory comments or spacing. |  |
| [B0046 · 205–217](../../../../../tests/unit/memory_account_contract_test.cpp#L205) | Callable definition: template&lt;class Action&gt; bool rejects_as(Action&& action, std::string_view category) | calls action, code; returns error.code() == category; error.code() == category · [reviewed contract](#b0046) |
| [B0047 · 218–218](../../../../../tests/unit/memory_account_contract_test.cpp#L218) | Explanatory comments or spacing. |  |
| [B0048 · 219–226](../../../../../tests/unit/memory_account_contract_test.cpp#L219) | Callable definition: template&lt;class Action&gt; bool throws_bad_alloc(Action&& action) | calls action; returns false; true · [reviewed contract](#b0048) |
| [B0049 · 227–227](../../../../../tests/unit/memory_account_contract_test.cpp#L227) | Explanatory comments or spacing. |  |
| [B0050 · 228–235](../../../../../tests/unit/memory_account_contract_test.cpp#L228) | Callable definition: bool contains_any(const memory_trace::Observation& observation, const std::array&lt;std::size_t, memory_trace::attempt_capacity&gt;& si… | calls ; returns true; false; 2 loop sites · [reviewed contract](#b0050) |
| [B0051 · 236–236](../../../../../tests/unit/memory_account_contract_test.cpp#L236) | Explanatory comments or spacing. |  |
| [B0052 · 237–244](../../../../../tests/unit/memory_account_contract_test.cpp#L237) | Callable definition: bool contains_any_since(const memory_trace::Observation& observation, std::size_t begin, const std::array&lt;std::size_t, memory_tra… | calls ; returns true; false; 2 loop sites · [reviewed contract](#b0052) |
| [B0053 · 245–245](../../../../../tests/unit/memory_account_contract_test.cpp#L245) | Explanatory comments or spacing. |  |
| [B0054 · 246–249](../../../../../tests/unit/memory_account_contract_test.cpp#L246) | Callable definition: void verify_observation(const memory_trace::Observation& observation) | calls verify · [reviewed contract](#b0054) |
| [B0055 · 250–250](../../../../../tests/unit/memory_account_contract_test.cpp#L250) | Explanatory comments or spacing. |  |
| [B0056 · 251–254](../../../../../tests/unit/memory_account_contract_test.cpp#L251) | Callable definition: void verify_unchanged(const MemoryAccount& account, const MemoryStatistics& before, const char* message) | calls verify, statistics · [reviewed contract](#b0056) |
| [B0057 · 255–255](../../../../../tests/unit/memory_account_contract_test.cpp#L255) | Explanatory comments or spacing. |  |
| [B0058 · 256–446](../../../../../tests/unit/memory_account_contract_test.cpp#L256) | Callable definition: void test_measurement_and_limits() | calls MemoryAccount::create, max, allocate, statistics; growth allocate; 2 loop sites; source comment (unverified): // Fresh account: the previously measured real request total is the limit. · [reviewed contract](#b0058) |
| [B0059 · 447–447](../../../../../tests/unit/memory_account_contract_test.cpp#L447) | Explanatory comments or spacing. |  |
| [B0060 · 448–556](../../../../../tests/unit/memory_account_contract_test.cpp#L448) | Callable definition: void test_alignment_zero_and_invalid_requests() | calls MemoryAccount::create, allocate, statistics, observe; growth allocate; 4 loop sites · [reviewed contract](#b0060) |
| [B0061 · 557–557](../../../../../tests/unit/memory_account_contract_test.cpp#L557) | Explanatory comments or spacing. |  |
| [B0062 · 558–634](../../../../../tests/unit/memory_account_contract_test.cpp#L558) | Callable definition: void test_moves_and_orphaned_block() | calls MemoryAccount::create, allocate, statistics, verify; growth allocate · [reviewed contract](#b0062) |
| [B0063 · 635–635](../../../../../tests/unit/memory_account_contract_test.cpp#L635) | Explanatory comments or spacing. |  |
| [B0064 · 636–693](../../../../../tests/unit/memory_account_contract_test.cpp#L636) | Callable definition: void test_upstream_failures() | calls scope, throws_bad_alloc, MemoryAccount::create, max; growth allocate; 2 loop sites; source comment (unverified): // Every attempt fails until the scope closes. · [reviewed contract](#b0064) |
| [B0065 · 694–694](../../../../../tests/unit/memory_account_contract_test.cpp#L694) | Explanatory comments or spacing. |  |
| [B0066 · 695–725](../../../../../tests/unit/memory_account_contract_test.cpp#L695) | Callable definition: void test_fixed_current_churn() | calls MemoryAccount::create, statistics, allocate, data; growth allocate; 2 loop sites · [reviewed contract](#b0066) |
| [B0067 · 726–726](../../../../../tests/unit/memory_account_contract_test.cpp#L726) | Explanatory comments or spacing. |  |
| [B0068 · 727–780](../../../../../tests/unit/memory_account_contract_test.cpp#L727) | Callable definition: void test_allocator_rebind_and_equality() | calls MemoryAccount::create, verify, select_on_container_copy_construction, std::move; growth allocate · [reviewed contract](#b0068) |
| [B0069 · 781–781](../../../../../tests/unit/memory_account_contract_test.cpp#L781) | Explanatory comments or spacing. |  |
| [B0070 · 782–868](../../../../../tests/unit/memory_account_contract_test.cpp#L782) | Callable definition: void test_vector_map_allocator_accounting() | calls MemoryAccount::create, statistics, observe, reserve; growth emplace, push_back, reserve; 4 loop sites · [reviewed contract](#b0070) |
| [B0071 · 869–869](../../../../../tests/unit/memory_account_contract_test.cpp#L869) | Explanatory comments or spacing. |  |
| [B0072 · 870–1005](../../../../../tests/unit/memory_account_contract_test.cpp#L870) | Callable definition: void test_vector_copy_budget_and_unequal_move() | calls MemoryAccount::create, max, observe, reserve; growth push_back, reserve; 6 loop sites · [reviewed contract](#b0072) |
| [B0073 · 1006–1006](../../../../../tests/unit/memory_account_contract_test.cpp#L1006) | Explanatory comments or spacing. |  |
| [B0074 · 1007–1039](../../../../../tests/unit/memory_account_contract_test.cpp#L1007) | Callable definition: void test_open_nested_string_coverage_gap_witness() | calls MemoryAccount::create, reserve, statistics, observe; growth emplace_back, reserve; source comment (unverified): // Negative witness only: the adapter does not redirect nested string payloads. · [reviewed contract](#b0074) |
| [B0075 · 1040–1040](../../../../../tests/unit/memory_account_contract_test.cpp#L1040) | Explanatory comments or spacing. |  |
| [B0076 · 1041–1060](../../../../../tests/unit/memory_account_contract_test.cpp#L1041) | Callable definition: void test_admission_failures_without_upstream_attempts() | calls MemoryAccount::create, MemoryAccount::control_bytes, statistics, scope; growth allocate; source comment (unverified): // Every ordinary allocation would fail persistently. · [reviewed contract](#b0076) |
| [B0077 · 1061–1061](../../../../../tests/unit/memory_account_contract_test.cpp#L1061) | Explanatory comments or spacing. |  |
| [B0078 · 1062–1101](../../../../../tests/unit/memory_account_contract_test.cpp#L1062) | Callable definition: void test_inline_decimal_without_allocating_temporaries() | calls size, crown::Decimal::parse, to_string, scope; growth copy_of; 4 loop sites; source comment (unverified): // Reference parsing/formatting belongs to fixture setup, outside the scope · [reviewed contract](#b0078) |
| [B0079 · 1102–1102](../../../../../tests/unit/memory_account_contract_test.cpp#L1102) | Explanatory comments or spacing. |  |
| [B0080 · 1103–1265](../../../../../tests/unit/memory_account_contract_test.cpp#L1103) | Callable definition: void test_accounted_row_payload_limits_and_lifetime() | calls binary, back, min, crown::Date::parse; growth clone, copy_of; 1 loop sites · [reviewed contract](#b0080) |
| [B0081 · 1266–1266](../../../../../tests/unit/memory_account_contract_test.cpp#L1266) | Explanatory comments or spacing. |  |
| [B0082 · 1267–1305](../../../../../tests/unit/memory_account_contract_test.cpp#L1267) | Callable definition: void test_accounted_row_order_matches_public_rows() | calls min, max, std::string, crown::Date::parse; growth copy_of; 5 loop sites · [reviewed contract](#b0082) |
| [B0083 · 1306–1306](../../../../../tests/unit/memory_account_contract_test.cpp#L1306) | Explanatory comments or spacing. |  |
| [B0084 · 1307–1314](../../../../../tests/unit/memory_account_contract_test.cpp#L1307) | Type/record definition: class ForwardDeclaredOwner |  · [reviewed contract](#b0084) |
| [B0085 · 1315–1315](../../../../../tests/unit/memory_account_contract_test.cpp#L1315) | Type/record definition: struct ForwardDeclaredOwner::Data |  · [reviewed contract](#b0085) |
| [B0086 · 1316–1317](../../../../../tests/unit/memory_account_contract_test.cpp#L1316) | Callable definition: ForwardDeclaredOwner::ForwardDeclaredOwner(const MemoryAccount& account) : data_(crown::resource::make_accounted_unique&lt;Data&gt;(acc… | calls data_; growth make_accounted_unique · [reviewed contract](#b0086) |
| [B0087 · 1318–1318](../../../../../tests/unit/memory_account_contract_test.cpp#L1318) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0087) |
| [B0088 · 1319–1319](../../../../../tests/unit/memory_account_contract_test.cpp#L1319) | Callable definition: int ForwardDeclaredOwner::value() const noexcept | calls ; returns data_-&gt;value · [reviewed contract](#b0088) |
| [B0089 · 1320–1320](../../../../../tests/unit/memory_account_contract_test.cpp#L1320) | Explanatory comments or spacing. |  |
| [B0090 · 1321–1321](../../../../../tests/unit/memory_account_contract_test.cpp#L1321) | Type/record definition: struct ProbeConstructionFailure |  · [reviewed contract](#b0090) |
| [B0091 · 1322–1333](../../../../../tests/unit/memory_account_contract_test.cpp#L1322) | Callable definition: struct alignas(64) OwnershipProbe | calls OwnershipProbe, values, resize, ~OwnershipProbe; growth resize · [reviewed contract](#b0091) |
| [B0092 · 1334–1334](../../../../../tests/unit/memory_account_contract_test.cpp#L1334) | Explanatory comments or spacing. |  |
| [B0093 · 1335–1425](../../../../../tests/unit/memory_account_contract_test.cpp#L1335) | Callable definition: void test_accounted_unique_and_shared_lifetimes() | calls MemoryAccount::create, statistics, cursor_owner, verify; growth make_accounted_shared, make_accounted_unique · [reviewed contract](#b0093) |
| [B0094 · 1426–1426](../../../../../tests/unit/memory_account_contract_test.cpp#L1426) | Explanatory comments or spacing. |  |
| [B0095 · 1427–1517](../../../../../tests/unit/memory_account_contract_test.cpp#L1427) | Callable definition: void test_accounted_factory_construction_failures() | calls verify, MemoryAccount::create, observe, build; growth make_accounted_shared, make_accounted_unique; 3 loop sites; source comment (unverified): // Both variants have an accounted nested vector. Each failed allocation · [reviewed contract](#b0095) |
| [B0096 · 1518–1518](../../../../../tests/unit/memory_account_contract_test.cpp#L1518) | Explanatory comments or spacing. |  |
| [B0097 · 1519–1543](../../../../../tests/unit/memory_account_contract_test.cpp#L1519) | Callable definition: void verify_attribution_partition(const MemoryAccount& account, std::span&lt;const crown::resource::MemoryAttribution&gt; owners) | calls statistics, memory_trace::observe, statistics_for, verify; 3 loop sites · [reviewed contract](#b0097) |
| [B0098 · 1544–1544](../../../../../tests/unit/memory_account_contract_test.cpp#L1544) | Explanatory comments or spacing. |  |
| [B0099 · 1545–1681](../../../../../tests/unit/memory_account_contract_test.cpp#L1545) | Callable definition: void test_operator_attribution_without_separate_grants() | calls std::string, crown::row_hash, MemoryAccount::create, size; growth allocate, clone, copy_of, make_accounted_shared, make_accounted_unique, push_back; 4 loop sites · [reviewed contract](#b0099) |
| [B0100 · 1682–1682](../../../../../tests/unit/memory_account_contract_test.cpp#L1682) | Explanatory comments or spacing. |  |
| [B0101 · 1683–1693](../../../../../tests/unit/memory_account_contract_test.cpp#L1683) | Callable definition: crown::storage::TupleLayout metadata_fixture() | calls binding, back, TupleLayout, std::move; returns TupleLayout(LayoutId{37}, { · [reviewed contract](#b0101) |
| [B0102 · 1694–1700](../../../../../tests/unit/memory_account_contract_test.cpp#L1694) | Callable definition: crown::Row metadata_row_fixture() | calls binary, back, std::move, crown::Decimal::parse; returns {std::int64_t{9007199254740993LL}, std::move(binary), · [reviewed contract](#b0102) |
| [B0103 · 1701–1701](../../../../../tests/unit/memory_account_contract_test.cpp#L1701) | Explanatory comments or spacing. |  |
| [B0104 · 1702–1797](../../../../../tests/unit/memory_account_contract_test.cpp#L1702) | Callable definition: void test_accounted_layout_identity_validation_and_retention() | calls first, metadata_fixture, separate, sources; growth clone, emplace; source comment (unverified): // Drop both remaining public input tokens outside the trace; source input · [reviewed contract](#b0104) |
| [B0105 · 1798–1798](../../../../../tests/unit/memory_account_contract_test.cpp#L1798) | Explanatory comments or spacing. |  |
| [B0106 · 1799–1875](../../../../../tests/unit/memory_account_contract_test.cpp#L1799) | Callable definition: void test_accounted_layout_full_allocation_failure_sweep() | calls metadata_fixture, MemoryAccount::create, allocate, observe; growth allocate; 4 loop sites · [reviewed contract](#b0106) |
| [B0107 · 1876–1876](../../../../../tests/unit/memory_account_contract_test.cpp#L1876) | Explanatory comments or spacing. |  |
| [B0108 · 1877–1955](../../../../../tests/unit/memory_account_contract_test.cpp#L1877) | Callable definition: void test_accounted_projection_values_tokens_and_retention() | calls native_source, metadata_fixture, native_target, projected_layout; growth emplace · [reviewed contract](#b0108) |
| [B0109 · 1956–1956](../../../../../tests/unit/memory_account_contract_test.cpp#L1956) | Explanatory comments or spacing. |  |
| [B0110 · 1957–2002](../../../../../tests/unit/memory_account_contract_test.cpp#L1957) | Callable definition: void test_accounted_projection_rejected_mapping_contracts() | calls metadata_fixture, projected_layout, context, std::string; 2 loop sites · [reviewed contract](#b0110) |
| [B0111 · 2003–2003](../../../../../tests/unit/memory_account_contract_test.cpp#L2003) | Explanatory comments or spacing. |  |
| [B0112 · 2004–2095](../../../../../tests/unit/memory_account_contract_test.cpp#L2004) | Callable definition: void test_accounted_projection_full_allocation_failure_sweep() | calls metadata_fixture, projected_layout, metadata_row_fixture, MemoryAccount::create; growth allocate, emplace; 2 loop sites · [reviewed contract](#b0112) |
| [B0113 · 2096–2096](../../../../../tests/unit/memory_account_contract_test.cpp#L2096) | Explanatory comments or spacing. |  |
| [B0114 · 2097–2140](../../../../../tests/unit/memory_account_contract_test.cpp#L2097) | Callable definition: void test_exact_allocation_usage_views() | calls MemoryAccount::create, observe, allocate, usage; growth allocate, emplace, reserve · [reviewed contract](#b0114) |
| [B0115 · 2141–2141](../../../../../tests/unit/memory_account_contract_test.cpp#L2141) | Explanatory comments or spacing. |  |
| [B0116 · 2142–2236](../../../../../tests/unit/memory_account_contract_test.cpp#L2142) | Callable definition: void test_accounted_arena_retention_generations_and_reports() | calls metadata_fixture, metadata_row_fixture, row_hash, legacy; growth emplace, insert; 1 loop sites · [reviewed contract](#b0116) |
| [B0117 · 2237–2237](../../../../../tests/unit/memory_account_contract_test.cpp#L2237) | Explanatory comments or spacing. |  |
| [B0118 · 2238–2349](../../../../../tests/unit/memory_account_contract_test.cpp#L2238) | Callable definition: void test_accounted_arena_allocation_failures_and_limits() | calls metadata_fixture, metadata_row_fixture, MemoryAccount::create, AccountedLayout::freeze; growth emplace, insert; 3 loop sites · [reviewed contract](#b0118) |
| [B0119 · 2350–2350](../../../../../tests/unit/memory_account_contract_test.cpp#L2350) | Explanatory comments or spacing. |  |
| [B0120 · 2351–2436](../../../../../tests/unit/memory_account_contract_test.cpp#L2351) | Callable definition: void test_accounted_arena_bounded_churn_model() | calls metadata_fixture, metadata_row_fixture, row_hash, MemoryAccount::create; growth emplace, insert; 10 loop sites · [reviewed contract](#b0120) |
| [B0121 · 2437–2437](../../../../../tests/unit/memory_account_contract_test.cpp#L2437) | Explanatory comments or spacing. |  |
| [B0122 · 2438–2451](../../../../../tests/unit/memory_account_contract_test.cpp#L2438) | Type/record definition: struct NativeTableInput |  · [reviewed contract](#b0122) |
| [B0123 · 2452–2462](../../../../../tests/unit/memory_account_contract_test.cpp#L2452) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0123) |
| [B0124 · 2463–2473](../../../../../tests/unit/memory_account_contract_test.cpp#L2463) | Callable definition: void prepare_metadata(const NativeTableInput& native, std::uint64_t limit = 1U &lt;&lt; 24) | calls crown::resource::MemoryAccount::create, AccountedLayout::freeze, size, AccountedProjection::freeze; growth emplace; 2 loop sites · [reviewed contract](#b0124) |
| [B0125 · 2474–2479](../../../../../tests/unit/memory_account_contract_test.cpp#L2474) | Callable definition: void prepare(const NativeTableInput& native, std::uint64_t limit = 1U &lt;&lt; 24) | calls prepare_metadata, emplace, size, add_index; growth emplace, insert; 2 loop sites · [reviewed contract](#b0125) |
| [B0126 · 2480–2481](../../../../../tests/unit/memory_account_contract_test.cpp#L2480) | Closes surrounding scope/type. |  · [reviewed contract](#b0126) |
| [B0127 · 2482–2550](../../../../../tests/unit/memory_account_contract_test.cpp#L2482) | Callable definition: void test_native_table_ownership_journals_and_cursors() | calls oracle, insert, tuple, prepare; growth emplace, insert · [reviewed contract](#b0127) |
| [B0128 · 2551–2551](../../../../../tests/unit/memory_account_contract_test.cpp#L2551) | Explanatory comments or spacing. |  |
| [B0129 · 2552–2569](../../../../../tests/unit/memory_account_contract_test.cpp#L2552) | Callable definition: void perform_native_table_operation(NativeAccountedTableFixture& f, std::size_t operation) | calls insert, add_index, erase, apply; growth insert · [reviewed contract](#b0129) |
| [B0130 · 2570–2570](../../../../../tests/unit/memory_account_contract_test.cpp#L2570) | Explanatory comments or spacing. |  |
| [B0131 · 2571–2641](../../../../../tests/unit/memory_account_contract_test.cpp#L2571) | Callable definition: void test_native_table_allocation_failure_sweeps() | calls prepare, emplace, journal, observe; growth emplace, insert; 3 loop sites · [reviewed contract](#b0131) |
| [B0132 · 2642–2642](../../../../../tests/unit/memory_account_contract_test.cpp#L2642) | Explanatory comments or spacing. |  |
| [B0133 · 2643–2708](../../../../../tests/unit/memory_account_contract_test.cpp#L2643) | Callable definition: void test_native_table_bounded_model_and_same_account_copy() | calls oracle, add_index, Projection, prepare; growth insert; 9 loop sites · [reviewed contract](#b0133) |
| [B0134 · 2709–2709](../../../../../tests/unit/memory_account_contract_test.cpp#L2709) | Explanatory comments or spacing. |  |
| [B0135 · 2710–2771](../../../../../tests/unit/memory_account_contract_test.cpp#L2710) | Callable definition: void test_native_journal_replacements_and_owner_lifetime() | calls prepare, emplace, pin, get; growth emplace, insert · [reviewed contract](#b0135) |
| [B0136 · 2772–2772](../../../../../tests/unit/memory_account_contract_test.cpp#L2772) | Explanatory comments or spacing. |  |
| [B0137 · 2773–2791](../../../../../tests/unit/memory_account_contract_test.cpp#L2773) | Callable definition: void test_containing_allocation_classification() | calls MemoryAccount::create, allocate, statistics, scope; growth allocate · [reviewed contract](#b0137) |
| [B0138 · 2792–2792](../../../../../tests/unit/memory_account_contract_test.cpp#L2792) | Explanatory comments or spacing. |  |
| [B0139 · 2793–2795](../../../../../tests/unit/memory_account_contract_test.cpp#L2793) | Callable definition: constexpr crown::storage::IndexWork indexed_test_work() | calls ; returns {1000000000, 1000000000, 1000000000, 1000000000, 1000000000} · [reviewed contract](#b0139) |
| [B0140 · 2796–2798](../../../../../tests/unit/memory_account_contract_test.cpp#L2796) | Callable definition: constexpr crown::storage::IndexedLimits indexed_test_limits() | calls ; returns {80, 4, 256, 320, 640, 4096, 96, 192, 128} · [reviewed contract](#b0140) |
| [B0141 · 2799–2821](../../../../../tests/unit/memory_account_contract_test.cpp#L2799) | Type/record definition: struct AccountedIndexedFixture | growth emplace, insert; 2 loop sites · [reviewed contract](#b0141) |
| [B0142 · 2822–2822](../../../../../tests/unit/memory_account_contract_test.cpp#L2822) | Explanatory comments or spacing. |  |
| [B0143 · 2823–2858](../../../../../tests/unit/memory_account_contract_test.cpp#L2823) | Callable definition: void test_accounted_indexed_work_and_allocation_identity() | calls MemoryAccount::create, emplace, reserve, AccountedIndexWork::create; growth emplace, reserve · [reviewed contract](#b0143) |
| [B0144 · 2859–2859](../../../../../tests/unit/memory_account_contract_test.cpp#L2859) | Explanatory comments or spacing. |  |
| [B0145 · 2860–2922](../../../../../tests/unit/memory_account_contract_test.cpp#L2860) | Callable definition: void test_accounted_indexed_journals_and_retention() | calls prepare, grant, indexed_test_work, memory_statistics; growth emplace, insert · [reviewed contract](#b0145) |
| [B0146 · 2923–2923](../../../../../tests/unit/memory_account_contract_test.cpp#L2923) | Explanatory comments or spacing. |  |
| [B0147 · 2924–2929](../../../../../tests/unit/memory_account_contract_test.cpp#L2924) | Callable definition: void prepare_indexed_operation(AccountedIndexedFixture& f, std::size_t operation) | calls emplace, journal, insert; growth emplace, insert · [reviewed contract](#b0147) |
| [B0148 · 2930–2958](../../../../../tests/unit/memory_account_contract_test.cpp#L2930) | Callable definition: void perform_indexed_operation(AccountedIndexedFixture& f, std::size_t operation, crown::storage::IndexWorkAllowance& work) | calls insert, add_index, erase, apply; growth insert · [reviewed contract](#b0148) |
| [B0149 · 2959–2959](../../../../../tests/unit/memory_account_contract_test.cpp#L2959) | Explanatory comments or spacing. |  |
| [B0150 · 2960–3014](../../../../../tests/unit/memory_account_contract_test.cpp#L2960) | Callable definition: void test_accounted_indexed_persistent_failures_and_peak() | calls prepare, prepare_indexed_operation, work, indexed_test_work; growth insert; 3 loop sites · [reviewed contract](#b0150) |
| [B0151 · 3015–3015](../../../../../tests/unit/memory_account_contract_test.cpp#L3015) | Explanatory comments or spacing. |  |
| [B0152 · 3016–3099](../../../../../tests/unit/memory_account_contract_test.cpp#L3016) | Callable definition: void test_accounted_indexed_work_and_component_limits() | calls prepare, indexed_test_work, grant, perform_indexed_operation; growth insert; 6 loop sites · [reviewed contract](#b0152) |
| [B0153 · 3100–3100](../../../../../tests/unit/memory_account_contract_test.cpp#L3100) | Explanatory comments or spacing. |  |
| [B0154 · 3101–3172](../../../../../tests/unit/memory_account_contract_test.cpp#L3101) | Callable definition: void test_accounted_indexed_churn_and_sparse_cursors() | calls oracle, add_index, Projection, prepare; growth insert; 10 loop sites · [reviewed contract](#b0154) |
| [B0155 · 3173–3181](../../../../../tests/unit/memory_account_contract_test.cpp#L3173) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0155) |
| [B0156 · 3182–3196](../../../../../tests/unit/memory_account_contract_test.cpp#L3182) | Callable definition: void prepare(const NativeTableInput& native, crown::storage::StorageBackend backend) | calls prepare_metadata, AccountedIndexWork::create, indexed_test_work, emplace; growth emplace, insert; 2 loop sites · [reviewed contract](#b0156) |
| [B0157 · 3197–3198](../../../../../tests/unit/memory_account_contract_test.cpp#L3197) | Closes surrounding scope/type. |  · [reviewed contract](#b0157) |
| [B0158 · 3199–3201](../../../../../tests/unit/memory_account_contract_test.cpp#L3199) | Callable definition: template&lt;class T&gt; concept TemporaryTableBorrow = requires(const T&& table, crown::TupleHandle handle) | calls get · [reviewed contract](#b0158) |
| [B0159 · 3202–3203](../../../../../tests/unit/memory_account_contract_test.cpp#L3202) | Callable definition: template&lt;class T&gt; concept TemporaryTableBorrowWithWork = requires(const T&& table, crown::TupleHandle handle, crown::storage::Ind… | calls get · [reviewed contract](#b0159) |
| [B0160 · 3204–3206](../../../../../tests/unit/memory_account_contract_test.cpp#L3204) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!TemporaryTableBorrow&lt;crown::storage::AccountedStorageTable&gt; && · [reviewed contract](#b0160) |
| [B0161 · 3207–3326](../../../../../tests/unit/memory_account_contract_test.cpp#L3207) | Callable definition: void test_accounted_native_dispatch_and_composed_journals() | calls prepare, verify_observation, observe, grant; growth emplace, insert; 1 loop sites · [reviewed contract](#b0161) |
| [B0162 · 3327–3327](../../../../../tests/unit/memory_account_contract_test.cpp#L3327) | Explanatory comments or spacing. |  |
| [B0163 · 3328–3388](../../../../../tests/unit/memory_account_contract_test.cpp#L3328) | Callable definition: void test_accounted_native_dispatch_allocation_failures() | calls grant, indexed_test_work, second, indexed_test_limits; growth emplace, insert; 3 loop sites · [reviewed contract](#b0163) |
| [B0164 · 3389–3411](../../../../../tests/unit/memory_account_contract_test.cpp#L3389) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0164) |
| [B0165 · 3412–3415](../../../../../tests/unit/memory_account_contract_test.cpp#L3412) | Callable definition: \[\[nodiscard\]\] std::optional&lt;crown::storage::IndexedBackendSpec&gt; specification(crown::storage::StorageBackend backend) const | calls indexed_test_limits, indexed_test_work; returns {}; crown::storage::IndexedBackendSpec{indexed_test_limits(), indexed_test_work()} · [reviewed contract](#b0165) |
| [B0166 · 3416–3420](../../../../../tests/unit/memory_account_contract_test.cpp#L3416) | Callable definition: \[\[nodiscard\]\] crown::storage::AccountedPlanStorage create(const crown::resource::MemoryAccount& account, crown::storage::StorageB… | calls crown::storage::detail::AccountedPlanStorageTesting::create, specification; returns crown::storage::detail::AccountedPlanStorageTesting::create(account, crown::PhysicalRoute::tree, · [reviewed contract](#b0166) |
| [B0167 · 3421–3421](../../../../../tests/unit/memory_account_contract_test.cpp#L3421) | Closes surrounding scope/type. |  · [reviewed contract](#b0167) |
| [B0168 · 3422–3436](../../../../../tests/unit/memory_account_contract_test.cpp#L3422) | Type/record definition: struct AccountedPlanFixture | growth emplace, insert; 3 loop sites · [reviewed contract](#b0168) |
| [B0169 · 3437–3437](../../../../../tests/unit/memory_account_contract_test.cpp#L3437) | Callable definition: template&lt;class T&gt; concept TemporaryPlanBorrow = requires(const T&& plan) | calls table · [reviewed contract](#b0169) |
| [B0170 · 3438–3439](../../../../../tests/unit/memory_account_contract_test.cpp#L3438) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!TemporaryPlanBorrow&lt;crown::storage::AccountedPlanStorage&gt;); · [reviewed contract](#b0170) |
| [B0171 · 3440–3546](../../../../../tests/unit/memory_account_contract_test.cpp#L3440) | Callable definition: void test_accounted_compiled_plan_binding_and_lifetimes() | calls emplace, row_hash, prepare, verify_observation; growth emplace; 7 loop sites · [reviewed contract](#b0171) |
| [B0172 · 3547–3547](../../../../../tests/unit/memory_account_contract_test.cpp#L3547) | Explanatory comments or spacing. |  |
| [B0173 · 3548–3597](../../../../../tests/unit/memory_account_contract_test.cpp#L3548) | Callable definition: void test_accounted_compiled_plan_allocation_failures_and_peak() | calls work, indexed_test_work, create, snapshot_copy; growth insert; 3 loop sites · [reviewed contract](#b0173) |
| [B0174 · 3598–3598](../../../../../tests/unit/memory_account_contract_test.cpp#L3598) | Explanatory comments or spacing. |  |
| [B0175 · 3599–3603](../../../../../tests/unit/memory_account_contract_test.cpp#L3599) | Callable definition: void test_empty_handle_and_unique_current_bytes() | calls rejects_as, statistics, verify · [reviewed contract](#b0175) |
| [B0176 · 3604–3605](../../../../../tests/unit/memory_account_contract_test.cpp#L3604) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0176) |
| [B0177 · 3606–3648](../../../../../tests/unit/memory_account_contract_test.cpp#L3606) | Callable definition: int main() | calls test_measurement_and_limits, test_alignment_zero_and_invalid_requests, test_moves_and_orphaned_block, test_upstream_failures · [reviewed contract](#b0177) |

## B0001

[Lines 1–36](../../../../../tests/unit/memory_account_contract_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/api/error.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile this one test executable against the account and accounted-storage APIs it exercises. |
| inputs / outputs | The translation unit imports error, memory, allocator/ownership, accounted row/layout/projection/arena/reference/index/table/plan types and a plan-testing bridge; indexed/table testing headers are conditional on CROWN_ACCOUNTED_INDEXED_TESTING. |
| invariants | Includes make declarations available; the conditional test bridge does not change the production API or execute merely by being included. |
| ownership | No runtime object is owned by this include block. |
| failure | Missing headers, incompatible declarations, or a disabled feature used by later test code fail compilation; this block catches no runtime errors. |
| cost | Preprocessing and compilation only; no account allocation or per-update runtime work is added to the library. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [src/storage/accounted_plan_testing.hpp](../../../../../src/storage/accounted_plan_testing.hpp) |

## B0002

[Lines 37–41](../../../../../tests/unit/memory_account_contract_test.cpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Test-executable-only replacement new/delete.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark the allocation probe as a test-executable-only replacement new/delete harness and set its fixed trace capacities. |
| inputs / outputs | The surrounding definitions use up to 2,048 address records and 256 attempted request-size entries; scalar, array, and aligned replacement new call the probe before malloc/aligned_alloc. |
| invariants | The fixed arrays avoid recursive dynamic allocation by the tracer. The replacement functions belong to this executable; they are not installed in the production runtime. |
| ownership | Static buffers and address records are test-process state. The record and live-byte globals are shared; later counters and gates include thread-local state, so this is not a concurrency guarantee. |
| failure | A configured Scope cut throws std::bad_alloc before the underlying malloc; ordinary allocation failure also throws. Trace-capacity overflow is reported by flags in the adjacent state block. |
| cost | The executable pays replacement-wrapper cost. \`remember()\` scans the fixed array only while tracing is enabled; \`forget()\` searches for a tracked address when it is released, even if tracing has since stopped. Disabled \`remember()\` returns without tracking, and a full registry sets its overflow flag. The hook records intercepted \`operator new\` request sizes, not allocator usable bytes, RSS, or every heap path. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0003

[Lines 42–42](../../../../../tests/unit/memory_account_contract_test.cpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Record { void* address = nullptr; std::size_t bytes = 0; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one address and request-size entry for replacement-new tracking. |
| inputs / outputs | Fields are \`address\` and \`bytes\`; address null denotes free slot and bytes records original request. |
| invariants | The fixed record table does not grow; only exact requests registered through new are remembered. |
| ownership | The registry owns the record slot, not the allocation; caller owns address until delete. |
| failure | No throw; registry-full is reported by a separate overflow flag. |
| cost | Two scalars per fixed slot; no heap. |
| Design | tests/unit/memory_account_contract_test.cpp:42-42, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0004

[Lines 43–58](../../../../../tests/unit/memory_account_contract_test.cpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::array<Record, record_capacity> records{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold fixed test-only address records and counters for observed global allocation requests. |
| inputs / outputs | \`position()\` records attempted requested bytes before malloc and applies the fail-after cut; \`remember()\` records successful addresses/requested bytes; \`forget()\` removes released addresses. The \`Observation\` value copies counters, byte totals, and overflow/trigger flags. |
| invariants | record and attempt capacities are finite; overflow sets flags and can make the trace incomplete. \`calls\` overflow throws. \`live_bytes\` is shared state; the other observation/fault counters are thread-local. |
| ownership | The static record array stores non-owning addresses until \`forget\`; it does not own allocation payloads. The copied \`Observation\` is a fixed value. |
| failure | The enabled fail cut throws before malloc; malloc/aligned allocation failure also throws. Attempt and record overflow are flagged, not treated as complete counts. |
| cost | While tracing is enabled, \`remember()\` linearly scans at most 2,048 fixed records; \`forget()\` searches for a previously tracked address on release. Disabled tracking returns early, and a full registry flags \`record_overflow\` rather than tracking the new address. The byte totals are the intercepted C++ \`operator new\` request arguments; an account-owned upstream request can equal a \`MemoryAccount\` requested-byte charge, but this probe covers only tracked requests and is not allocator usable size or process memory. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/resource/memory.hpp §MemoryUsage byte definitions](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp §account upstream requests](../../../../../src/resource/memory.cpp) |

## B0005

[Lines 59–70](../../../../../tests/unit/memory_account_contract_test.cpp#L59); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Observation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a fixed snapshot of trace counters and request records. |
| inputs / outputs | Fields include call/success/free counts and bytes, 256 attempts, attempt count, overflow flags and selected-failure flag. |
| invariants | Separates attempted, successful and freed traffic; truncated fixed arrays invalidate sample. |
| ownership | Owns its request array by value; does not retain registry addresses. |
| failure | No exception channel; verify_observation rejects overflow later. |
| cost | Bounded 256-entry array copy; no heap. |
| Design | tests/unit/memory_account_contract_test.cpp:59-70, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0007

[Lines 72–75](../../../../../tests/unit/memory_account_contract_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Observation observe() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Take a point-in-time snapshot of the thread-local allocation tracer. |
| inputs / outputs | Returns call/success/free counts and bytes plus a copy of the fixed attempts array, counts and overflow/trigger flags. |
| invariants | Does not reset or advance counters; attempts and successes/frees remain separate. |
| ownership | Returns a fixed-size value; live registry remains owned by memory_trace. |
| failure | No failure path; noexcept. |
| cost | Copies 256 request slots and scalars; no heap. |
| Design | tests/unit/memory_account_contract_test.cpp:72-75, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0009

[Lines 77–85](../../../../../tests/unit/memory_account_contract_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void position(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count an ordinary C++ new request and fail at the configured persistent position. |
| inputs / outputs | When enabled, increments calls, records requested bytes if capacity remains and examines remaining threshold. |
| invariants | Disabled trace is a no-op; remaining zero sets triggered and throws before backing allocation; positive remaining decrements once. |
| ownership | Borrows thread-local Scope state and fixed attempt array. |
| failure | Throws bad_alloc on selected position or counter overflow. |
| cost | Constant-time counter/log work; fixed storage prevents recursive allocation. |
| Design | tests/unit/memory_account_contract_test.cpp:77-85, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0011

[Lines 87–100](../../../../../tests/unit/memory_account_contract_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void remember(void* address, std::size_t bytes) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register a successfully malloc-backed replacement-new pointer. |
| inputs / outputs | Finds first empty record, stores address and original request size, updates successful/live/peak bytes. |
| invariants | Registered size is the new request, not allocator usable size; registry overflow sets a flag without growth. |
| ownership | Registry borrows backing allocation; caller owns address until matching delete. |
| failure | No throw; record overflow makes sample incomplete. |
| cost | Linear scan of at most 2048 fixed records; no heap. |
| Design | tests/unit/memory_account_contract_test.cpp:87-100, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0013

[Lines 102–116](../../../../../tests/unit/memory_account_contract_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void forget(void* address) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove a traced replacement-new pointer and account its release. |
| inputs / outputs | Finds address in fixed registry, clears record and subtracts stored request bytes; counts free while tracing is enabled. |
| invariants | Null/unregistered pointer leaves records unchanged; free count is distinct from successful request count. |
| ownership | Does not own allocation; caller’s replacement delete calls free after unregistering. |
| failure | This helper is declared noexcept and releases only a registry record or malloc-backed pointer. |
| cost | Linear scan of fixed 2048-entry registry; no heap. |
| Design | tests/unit/memory_account_contract_test.cpp:102-116, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0015

[Lines 118–125](../../../../../tests/unit/memory_account_contract_test.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] inline void* allocate(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back ordinary scalar/array replacement new with malloc after fault admission. |
| inputs / outputs | Calls position(bytes), mallocs max(bytes,1), registers success and returns pointer. |
| invariants | Zero-byte new uses one backing byte but records zero request; injected failure precedes malloc. |
| ownership | Returned allocation belongs to caller until release(). |
| failure | Throws bad_alloc for selected position or malloc failure. |
| cost | One position check plus malloc and fixed-record scan; direct malloc callers bypass. |
| Design | tests/unit/memory_account_contract_test.cpp:118-125, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0017

[Lines 127–146](../../../../../tests/unit/memory_account_contract_test.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] inline void* aligned(std::size_t bytes, std::size_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back aligned replacement new while retaining requested byte count. |
| inputs / outputs | Calls position(bytes); uses malloc for normal alignment or checked aligned_alloc rounding for larger alignment. |
| invariants | Zero-byte request backs one byte; rounding overflow throws; record stores unrounded request bytes. |
| ownership | Returned block is registered and released through replacement aligned delete. |
| failure | Throws bad_alloc for injection, rounding overflow or backing allocator failure. |
| cost | One trace check, one backing allocation and registry scan; only aligned C++ new uses it. |
| Design | tests/unit/memory_account_contract_test.cpp:127-146, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0019

[Lines 148–151](../../../../../tests/unit/memory_account_contract_test.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] inline void release(void* address) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Unregister and free storage returned by a replacement new overload. |
| inputs / outputs | Calls forget(address), then std::free(address). |
| invariants | Null is safe; accounting is exact only for pointers registered through this executable’s new overloads. |
| ownership | Ends caller ownership of the backing allocation. |
| failure | This helper is declared noexcept and releases only a registry record or malloc-backed pointer. |
| cost | One fixed-registry scan and free; direct frees are not attributed. |
| Design | tests/unit/memory_account_contract_test.cpp:148-151, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0021

[Lines 153–168](../../../../../tests/unit/memory_account_contract_test.cpp#L153); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Scope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable fixed-storage tracing and optional persistent fail-after injection for one lexical region. |
| inputs / outputs | Constructor resets counters/flags, stores threshold and enables; destructor disables and resets threshold. |
| invariants | No nested scope; selected zero rejects this and later allocation requests until destruction. |
| ownership | Noncopyable RAII wrapper borrows thread-local tracer state; does not own allocations. |
| failure | Nested scope terminates; new failures are thrown by position(), not this type. |
| cost | Scalar resets only; no allocation. |
| Design | tests/unit/memory_account_contract_test.cpp:153-168, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0022

[Lines 169–170](../../../../../tests/unit/memory_account_contract_test.cpp#L169); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L169-L170:sha256:f662f8670e9358ac4c79eaebcc9a195eee8026cf9dfe483a542eac73d0e4ea0e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in memory_account_contract_test.cpp: namespace memory_trace. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 171–171](../../../../../tests/unit/memory_account_contract_test.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n) { return memory_trace::allocate(n); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this scalar/array, aligned or nothrow global new overload through the fixed trace seam. |
| inputs / outputs | Passes requested bytes and optional alignment to memory_trace::allocate/aligned. |
| invariants | All forms count the same position; nothrow overloads catch all exceptions and return null. |
| ownership | Returned malloc-backed pointer is caller-owned until replacement delete. |
| failure | Throwing form propagates bad_alloc; nothrow form returns nullptr. |
| cost | One trace check/backing allocation; direct malloc and syscalls are not intercepted. |
| Design | tests/unit/memory_account_contract_test.cpp:171-171, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0024

[Lines 172–172](../../../../../tests/unit/memory_account_contract_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n) { return memory_trace::allocate(n); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this scalar/array, aligned or nothrow global new overload through the fixed trace seam. |
| inputs / outputs | Passes requested bytes and optional alignment to memory_trace::allocate/aligned. |
| invariants | All forms count the same position; nothrow overloads catch all exceptions and return null. |
| ownership | Returned malloc-backed pointer is caller-owned until replacement delete. |
| failure | Throwing form propagates bad_alloc; nothrow form returns nullptr. |
| cost | One trace check/backing allocation; direct malloc and syscalls are not intercepted. |
| Design | tests/unit/memory_account_contract_test.cpp:172-172, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0025

[Lines 173–173](../../../../../tests/unit/memory_account_contract_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n, const std::nothrow_t&) noexcept { try { return memory_trace::allocate(n); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this scalar/array, aligned or nothrow global new overload through the fixed trace seam. |
| inputs / outputs | Passes requested bytes and optional alignment to memory_trace::allocate/aligned. |
| invariants | All forms count the same position; nothrow overloads catch all exceptions and return null. |
| ownership | Returned malloc-backed pointer is caller-owned until replacement delete. |
| failure | Throwing form propagates bad_alloc; nothrow form returns nullptr. |
| cost | One trace check/backing allocation; direct malloc and syscalls are not intercepted. |
| Design | tests/unit/memory_account_contract_test.cpp:173-173, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0026

[Lines 174–174](../../../../../tests/unit/memory_account_contract_test.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n, const std::nothrow_t&) noexcept { try { return memory_trace::allocate(n); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this scalar/array, aligned or nothrow global new overload through the fixed trace seam. |
| inputs / outputs | Passes requested bytes and optional alignment to memory_trace::allocate/aligned. |
| invariants | All forms count the same position; nothrow overloads catch all exceptions and return null. |
| ownership | Returned malloc-backed pointer is caller-owned until replacement delete. |
| failure | Throwing form propagates bad_alloc; nothrow form returns nullptr. |
| cost | One trace check/backing allocation; direct malloc and syscalls are not intercepted. |
| Design | tests/unit/memory_account_contract_test.cpp:174-174, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0027

[Lines 175–175](../../../../../tests/unit/memory_account_contract_test.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t a) { return memory_trace::aligned(n, static_cast<std::size_t>(a)); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this scalar/array, aligned or nothrow global new overload through the fixed trace seam. |
| inputs / outputs | Passes requested bytes and optional alignment to memory_trace::allocate/aligned. |
| invariants | All forms count the same position; nothrow overloads catch all exceptions and return null. |
| ownership | Returned malloc-backed pointer is caller-owned until replacement delete. |
| failure | Throwing form propagates bad_alloc; nothrow form returns nullptr. |
| cost | One trace check/backing allocation; direct malloc and syscalls are not intercepted. |
| Design | tests/unit/memory_account_contract_test.cpp:175-175, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0028

[Lines 176–176](../../../../../tests/unit/memory_account_contract_test.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t a) { return memory_trace::aligned(n, static_cast<std::size_t>(a)); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this scalar/array, aligned or nothrow global new overload through the fixed trace seam. |
| inputs / outputs | Passes requested bytes and optional alignment to memory_trace::allocate/aligned. |
| invariants | All forms count the same position; nothrow overloads catch all exceptions and return null. |
| ownership | Returned malloc-backed pointer is caller-owned until replacement delete. |
| failure | Throwing form propagates bad_alloc; nothrow form returns nullptr. |
| cost | One trace check/backing allocation; direct malloc and syscalls are not intercepted. |
| Design | tests/unit/memory_account_contract_test.cpp:176-176, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0029

[Lines 177–177](../../../../../tests/unit/memory_account_contract_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t a, const std::nothrow_t&) noexcept { try { return memory_trace::aligned(n, static_cast<std::size_t>(a)); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this scalar/array, aligned or nothrow global new overload through the fixed trace seam. |
| inputs / outputs | Passes requested bytes and optional alignment to memory_trace::allocate/aligned. |
| invariants | All forms count the same position; nothrow overloads catch all exceptions and return null. |
| ownership | Returned malloc-backed pointer is caller-owned until replacement delete. |
| failure | Throwing form propagates bad_alloc; nothrow form returns nullptr. |
| cost | One trace check/backing allocation; direct malloc and syscalls are not intercepted. |
| Design | tests/unit/memory_account_contract_test.cpp:177-177, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0030

[Lines 178–178](../../../../../tests/unit/memory_account_contract_test.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t a, const std::nothrow_t&) noexcept { try { return memory_trace::aligned(n, static_cast<std::size_t>(a)); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this scalar/array, aligned or nothrow global new overload through the fixed trace seam. |
| inputs / outputs | Passes requested bytes and optional alignment to memory_trace::allocate/aligned. |
| invariants | All forms count the same position; nothrow overloads catch all exceptions and return null. |
| ownership | Returned malloc-backed pointer is caller-owned until replacement delete. |
| failure | Throwing form propagates bad_alloc; nothrow form returns nullptr. |
| cost | One trace check/backing allocation; direct malloc and syscalls are not intercepted. |
| Design | tests/unit/memory_account_contract_test.cpp:178-178, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0031

[Lines 179–179](../../../../../tests/unit/memory_account_contract_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:179-179, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0032

[Lines 180–180](../../../../../tests/unit/memory_account_contract_test.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:180-180, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0033

[Lines 181–181](../../../../../tests/unit/memory_account_contract_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::size_t) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:181-181, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0034

[Lines 182–182](../../../../../tests/unit/memory_account_contract_test.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::size_t) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:182-182, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0035

[Lines 183–183](../../../../../tests/unit/memory_account_contract_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, const std::nothrow_t&) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:183-183, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0036

[Lines 184–184](../../../../../tests/unit/memory_account_contract_test.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, const std::nothrow_t&) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:184-184, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0037

[Lines 185–185](../../../../../tests/unit/memory_account_contract_test.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::align_val_t) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:185-185, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0038

[Lines 186–186](../../../../../tests/unit/memory_account_contract_test.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:186-186, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0039

[Lines 187–187](../../../../../tests/unit/memory_account_contract_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::size_t, std::align_val_t) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:187-187, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0040

[Lines 188–188](../../../../../tests/unit/memory_account_contract_test.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::size_t, std::align_val_t) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:188-188, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0041

[Lines 189–189](../../../../../tests/unit/memory_account_contract_test.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::align_val_t, const std::nothrow_t&) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:189-189, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0042

[Lines 190–190](../../../../../tests/unit/memory_account_contract_test.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t, const std::nothrow_t&) noexcept { memory_trace::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the matching delete overload through memory_trace::release. |
| inputs / outputs | Passes pointer to the common unregister/free function; size/alignment tags do not recompute allocation. |
| invariants | Registered request bytes are removed once; null is safe. |
| ownership | Ends the caller lifetime of replacement-new storage. |
| failure | This replacement delete is declared noexcept and does not throw; it releases matching tracer storage. |
| cost | One fixed-record scan and free for pointers allocated through new seam. |
| Design | tests/unit/memory_account_contract_test.cpp:190-190, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0043

[Lines 191–200](../../../../../tests/unit/memory_account_contract_test.cpp#L191); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using crown::resource::AllocationLifetime;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide test-local account aliases and retain the measured raw request sizes used to target later fault/validation assertions. |
| inputs / outputs | \`observed_large_block_requests\` and its count copy up to 256 request sizes from a successful 4,096-byte, 256-aligned MemoryAccount block setup; later tests search that captured set after invalid and failed allocations. |
| invariants | The buffer is bounded by the tracer attempt capacity and represents upstream \`operator new\` request sizes, not logical payload or account statistics. |
| ownership | The buffer is a fixed test-owned array with values only; it owns neither the account nor its blocks. |
| failure | The setup can propagate account/upstream allocation errors. This declaration does not catch them; the later test asserts the malformed requests do not repeat a captured large request. |
| cost | Fixed array copy and bounded membership checks in the test harness; no production path reads this state. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/resource/memory.hpp §MemoryAccount::allocate](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp §allocation sizing and allocation admission](../../../../../src/resource/memory.cpp) |

## B0044

[Lines 201–203](../../../../../tests/unit/memory_account_contract_test.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool condition, const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a false test assertion with its diagnostic. |
| inputs / outputs | Returns normally for true; otherwise throws runtime_error(message). |
| invariants | Successful assertions have no state effect. |
| ownership | Borrows message and condition for the call. |
| failure | Only false throws; diagnostic construction can allocate. |
| cost | Constant check on success; error formatting occurs only on failure. |
| Design | tests/unit/memory_account_contract_test.cpp:201-203, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0046

[Lines 205–217](../../../../../tests/unit/memory_account_contract_test.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool rejects_as(Action&& action, std::string_view category) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize the expected typed contract/failure category from one action. |
| inputs / outputs | Runs action once and compares the code from MemoryFailure, tuple/projection/arena/table validation, IndexFailure or crown::Error. |
| invariants | Unexpected/unlisted exception and action success return false; it does not translate errors. |
| ownership | Action/category are borrowed during call; no state is retained. |
| failure | Test action exception is caught by reference; unknown exception maps to false. |
| cost | One action invocation plus catch chain; helper does not allocate on its normal boolean result. |
| Design | tests/unit/memory_account_contract_test.cpp:205-217, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0048

[Lines 219–226](../../../../../tests/unit/memory_account_contract_test.cpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool throws_bad_alloc(Action&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish an upstream std::bad_alloc from account MemoryFailure. |
| inputs / outputs | Runs action once and returns true only for std::bad_alloc after excluding MemoryFailure. |
| invariants | MemoryFailure is explicitly false despite deriving from bad_alloc. |
| ownership | Borrows action; no result ownership. |
| failure | Any other exception is caught and reported false. |
| cost | One action invocation and exception dispatch; success path has no heap operation. |
| Design | tests/unit/memory_account_contract_test.cpp:219-226, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

## B0050

[Lines 228–235](../../../../../tests/unit/memory_account_contract_test.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool contains_any(const memory_trace::Observation& observation,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Search a captured request-size list for any candidate upstream size. |
| inputs / outputs | Compares every observed attempted byte count with the supplied candidate size array. |
| invariants | Matches raw C++ new request size, not account payload or vector capacity. |
| ownership | Borrows Observation and fixed arrays; returns bool. |
| failure | Caller-provided count is assumed within fixed array capacity. |
| cost | O(observed_attempts × candidate_sizes); no dynamic storage. |
| Design | tests/unit/memory_account_contract_test.cpp:228-235, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0052

[Lines 237–244](../../../../../tests/unit/memory_account_contract_test.cpp#L237); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool contains_any_since(const memory_trace::Observation& observation, std::size_t begin,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Search only new requests appended after a saved observation index. |
| inputs / outputs | Scans attempt records from \`begin\` to current count against candidate sizes. |
| invariants | Prior setup requests cannot satisfy this later-operation check. |
| ownership | Borrows fixed arrays and Observation. |
| failure | Caller must supply a valid observation offset. |
| cost | O(later_attempts × candidate_sizes), fixed storage. |
| Design | tests/unit/memory_account_contract_test.cpp:237-244, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0054

[Lines 246–249](../../../../../tests/unit/memory_account_contract_test.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify_observation(const memory_trace::Observation& observation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a tracer sample whose fixed attempt or live-record registry overflowed. |
| inputs / outputs | Checks attempt_overflow and record_overflow flags in an Observation snapshot. |
| invariants | Only complete fixed-capacity evidence is accepted by follow-on byte/count checks. |
| ownership | Takes Observation by value; it does not modify tracer counters. |
| failure | Overflow throws runtime_error; it does not grow the buffers or retry. |
| cost | Two boolean checks plus fixed snapshot copy; no dynamic growth. |
| Design | tests/unit/memory_account_contract_test.cpp:246-249, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0056

[Lines 251–254](../../../../../tests/unit/memory_account_contract_test.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify_unchanged(const MemoryAccount& account, const MemoryStatistics& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all MemoryStatistics fields with a saved account baseline. |
| inputs / outputs | Reads account.statistics() and compares full struct equality. |
| invariants | Includes current, limit, peak, history counters and purpose/lifetime partitions. |
| ownership | Borrows account/message; expected stats is immutable value. |
| failure | Mismatch throws runtime_error. |
| cost | One fixed stats copy; does not scan allocations beyond statistics accessor. |
| Design | tests/unit/memory_account_contract_test.cpp:251-254, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0058

[Lines 256–446](../../../../../tests/unit/memory_account_contract_test.cpp#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_measurement_and_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile controller/aligned-block requested bytes with MemoryAccount usage, exercise exact and one-byte-under quotas, shared handle exhaustion, and lifetime relabeling. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Reconcile controller/aligned-block requested bytes with MemoryAccount usage, exercise exact and one-byte-under quotas, shared handle exhaustion, and lifetime relabeling.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: control_bytes did not match the observed controller request; the aligned data block produced no observed upstream request; current statistics did not reconcile with successful upstream requests; peak or successful history did not reconcile with observed requests; payload accounting did not preserve the requested block size. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryBlock\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope() records successful C++ new requests without injecting failure; admission/validation categories are checked separately where present. |
| cost | Source-map evidence shows 2 loop(s), growth sites allocate. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:256-446, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0060

[Lines 448–556](../../../../../tests/unit/memory_account_contract_test.cpp#L448); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_alignment_zero_and_invalid_requests() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check four alignment values, zero payload, malformed alignment/purpose/lifetime and overflow rejection before upstream allocation. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Check four alignment values, zero payload, malformed alignment/purpose/lifetime and overflow rejection before upstream allocation.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: block data did not satisfy its requested alignment; zero-sized block changed payload accounting; alignment and zero-size requests did not reconcile with observed upstream bytes; memory_contract; non-power-of-two alignment was not rejected as a contract error. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryBlock\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope() records successful C++ new requests without injecting failure; admission/validation categories are checked separately where present. |
| cost | Source-map evidence shows 4 loop(s), growth sites allocate. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:448-556, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0062

[Lines 558–634](../../../../../tests/unit/memory_account_contract_test.cpp#L558); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_moves_and_orphaned_block() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify account/block moves are allocation-free and a block retains its control after the last public account handle is dropped. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Verify account/block moves are allocation-free and a block retains its control after the last public account handle is dropped.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: independent accounts reused an owner identifier; account move construction did not empty its source; account move assignment did not empty the constructed handle; account move assignment did not transfer its source; block move construction did not empty its source. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryBlock\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope() records successful C++ new requests without injecting failure; admission/validation categories are checked separately where present. |
| cost | Source-map evidence shows 0 loop(s), growth sites allocate. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:558-634, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0064

[Lines 636–693](../../../../../tests/unit/memory_account_contract_test.cpp#L636); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_upstream_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail the first controller and data-block upstream request; preserve prior payload/account state and allow a later smaller retry. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Fail the first controller and data-block upstream request; preserve prior payload/account state and allow a later smaller retry.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: controller upstream failure was wrapped or retried; controller failure did not target the observed controller request size; failed controller allocation leaked observed bytes; data-block upstream failure was wrapped or retried; data-block failure did not target the measured large upstream request. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryBlock\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | The block selects a failure position and requires the upstream path to throw std::bad_alloc; validation/quota rejection is distinguished when asserted. |
| cost | Source-map evidence shows 2 loop(s), growth sites allocate. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:636-693, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0066

[Lines 695–725](../../../../../tests/unit/memory_account_contract_test.cpp#L695); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_fixed_current_churn() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run 128 allocate/write/reset rounds and ensure current partitions return to baseline while histories and peak advance. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Run 128 allocate/write/reset rounds and ensure current partitions return to baseline while histories and peak advance.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: churn retained current allocation state; churn history/peak diverged from fixed current state; final account release leaked observed upstream allocations. |
| ownership | Local owning types: \`MemoryAccount\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope() records successful C++ new requests without injecting failure; admission/validation categories are checked separately where present. |
| cost | Source-map evidence shows 2 loop(s), growth sites allocate. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:695-725, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0068

[Lines 727–780](../../../../../tests/unit/memory_account_contract_test.cpp#L727); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_allocator_rebind_and_equality() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check allocator equality/rebind/copy selection/move and shared allocation accounting; empty allocator must not silently allocate. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Check allocator equality/rebind/copy selection/move and shared allocation accounting; empty allocator must not silently allocate.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: same account/purpose did not compare equal across rebinds; allocator equality ignored purpose or account identity; copy selection changed allocator account or purpose; allocator move did not leave both handles sharing the account; moved allocator handles did not share allocation/deallocation accounting. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryAllocator\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | The block selects a failure position and requires the upstream path to throw std::bad_alloc; validation/quota rejection is distinguished when asserted. |
| cost | Source-map evidence shows 0 loop(s), growth sites allocate. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:727-780, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0070

[Lines 782–868](../../../../../tests/unit/memory_account_contract_test.cpp#L782); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_vector_map_allocator_accounting() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile an accounted vector buffer and map nodes with actual requests and their purpose partitions, then release them. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Reconcile an accounted vector buffer and map nodes with actual requests and their purpose partitions, then release them.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: vector current bytes did not reconcile with observed upstream requests; vector buffer was charged to the wrong purpose; vector population changed a value; vector buffer release did not restore current account bytes; vector/account destruction did not reclaim every observed upstream request. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryAllocator\`, \`std::vector\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope() records successful C++ new requests without injecting failure; admission/validation categories are checked separately where present. |
| cost | Source-map evidence shows 4 loop(s), growth sites emplace, push_back, reserve. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:782-868, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0072

[Lines 870–1005](../../../../../tests/unit/memory_account_contract_test.cpp#L870); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_vector_copy_budget_and_unequal_move() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure an exact vector quota, reject a copy before data allocation, and prove unequal-account move allocates at destination. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Measure an exact vector quota, reject a copy before data allocation, and prove unequal-account move allocates at destination.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: vector copy budget sample did not measure its real controller and buffer requests; vector budget sample was not fully measured and reclaimed; fresh vector account did not reproduce the measured exact aggregate; vector copy selection minted or changed its account; memory_limit. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryAllocator\`, \`std::vector\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope() records successful C++ new requests without injecting failure; admission/validation categories are checked separately where present. |
| cost | Source-map evidence shows 6 loop(s), growth sites push_back, reserve. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:870-1005, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0074

[Lines 1007–1039](../../../../../tests/unit/memory_account_contract_test.cpp#L1007); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_open_nested_string_coverage_gap_witness() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show that applying MemoryAllocator to vector&lt;string&gt; accounts only the outer buffer, not the nested long string payload. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Show that applying MemoryAllocator to vector&lt;string&gt; accounts only the outer buffer, not the nested long string payload.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: nested string witness was not constructed; outer vector request was not fully charged before nested payload creation; nested string payload did not appear outside outer-container accounting; nested string coverage witness did not reclaim its observed allocations. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryAllocator\`, \`std::vector\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope() records successful C++ new requests without injecting failure; admission/validation categories are checked separately where present. |
| cost | Source-map evidence shows 0 loop(s), growth sites emplace_back, reserve. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1007-1039, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0076

[Lines 1041–1060](../../../../../tests/unit/memory_account_contract_test.cpp#L1041); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_admission_failures_without_upstream_attempts() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm persistent new failure and show limit/overflow/alignment admission wins with zero upstream attempts. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Arm persistent new failure and show limit/overflow/alignment admission wins with zero upstream attempts.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: memory_limit; memory_overflow; memory_contract; resource admission diagnostics attempted an ordinary upstream allocation. |
| ownership | Local owning types: \`MemoryAccount\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 0 loop(s), growth sites allocate. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1041-1060, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0078

[Lines 1062–1101](../../../../../tests/unit/memory_account_contract_test.cpp#L1062); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_inline_decimal_without_allocating_temporaries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare InlineDecimal render/ordering/equality against Decimal for 11 values with global C++ new persistently denied. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Compare InlineDecimal render/ordering/equality against Decimal for 11 values with global C++ new persistently denied.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: -99999999999999999999999999999999999999; -0.00000000000000000000000000000000000001; -0.000; +001.2300; 0.00000000000000000000000000000000000001. |
| ownership | Local owning types: fixed values and fixture state. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 4 loop(s), growth sites copy_of. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1062-1101, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0080

[Lines 1103–1265](../../../../../tests/unit/memory_account_contract_test.cpp#L1103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_row_payload_limits_and_lifetime() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise deep mixed-row copy, same/cross-account clones, exact/under budgets, upstream failure, retained owner, and 64 churn updates. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Exercise deep mixed-row copy, same/cross-account clones, exact/under budgets, upstream failure, retained owner, and 64 churn updates.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: 0001-01-01; -99999999999999999999999999999999999999; -0.00000000000000000000000000000000000001; accounted row did not reconcile its single payload block and controller; accounted row did not own the complete exact binary input. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedRow\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | The block selects a failure position and requires the upstream path to throw std::bad_alloc; validation/quota rejection is distinguished when asserted. |
| cost | Source-map evidence shows 1 loop(s), growth sites clone, copy_of. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1103-1265, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

## B0082

[Lines 1267–1305](../../../../../tests/unit/memory_account_contract_test.cpp#L1267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_row_order_matches_public_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare row hash/equality/order against public Row for 11 typed edge cases while reads run under Scope(0). |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Compare row hash/equality/order against public Row for 11 typed edge cases while reads run under Scope(0).; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: 9999-12-31; -0.00000000000000000000000000000000000001; 12345678901234567890123456789012345678; accounted row changed canonical hash framing; accounted row changed lexicographic typed-row ordering/equality. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedRow\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 5 loop(s), growth sites copy_of. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1267-1305, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

## B0084

[Lines 1307–1314](../../../../../tests/unit/memory_account_contract_test.cpp#L1307); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ForwardDeclaredOwner {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove the account-aware unique wrapper works with a private incomplete Data declaration. |
| inputs / outputs | Stores AccountedUnique&lt;Data&gt;; constructor takes MemoryAccount; value() returns the payload integer. |
| invariants | Data is completed later in this translation unit and destructor is out-of-line after completion. |
| ownership | Unique handle/deleter owns Data and retains account; value access borrows while wrapper lives. |
| failure | Construction may propagate account/upstream allocation failure; destructor is RAII cleanup. |
| cost | Wrapper stores one unique handle; object allocation is separate and account-charged. |
| Design | tests/unit/memory_account_contract_test.cpp:1307-1314, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), include/crown/resource/allocator.hpp:20-96, include/crown/resource/ownership.hpp:1-76 |

## B0085

[Lines 1315–1315](../../../../../tests/unit/memory_account_contract_test.cpp#L1315); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ForwardDeclaredOwner::Data { int value; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the private payload owned through the incomplete-type wrapper. |
| inputs / outputs | Contains one integer \`value\`, initialized to 37 by wrapper construction. |
| invariants | Completes the nested type before the destructor definition. |
| ownership | Owned exclusively by ForwardDeclaredOwner::data_. |
| failure | No additional member-level failure exists; only the surrounding account-aware factory can fail during construction. |
| cost | One integer payload; allocation belongs to AccountedUnique factory. |
| Design | tests/unit/memory_account_contract_test.cpp:1315-1315, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), include/crown/resource/allocator.hpp:20-96, include/crown/resource/ownership.hpp:1-76 |

## B0086

[Lines 1316–1317](../../../../../tests/unit/memory_account_contract_test.cpp#L1316); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ForwardDeclaredOwner::ForwardDeclaredOwner(const MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the wrapper’s private Data through the accounted unique factory. |
| inputs / outputs | Takes MemoryAccount and initializes AccountedUnique&lt;Data&gt; with cursor purpose and integer payload 37. |
| invariants | Construction binds one account-aware deleter to the forward-declared object. |
| ownership | Unique pointer owns Data and retains the account; wrapper is the sole strong owner. |
| failure | Accounted factory may propagate MemoryFailure or upstream bad_alloc; no retry is performed. |
| cost | One account-backed Data allocation at actual size/alignment; payload int is separate from charge framing. |
| Design | tests/unit/memory_account_contract_test.cpp:1316-1317, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), include/crown/resource/allocator.hpp:20-96, include/crown/resource/ownership.hpp:1-76 |

## B0087

[Lines 1318–1318](../../../../../tests/unit/memory_account_contract_test.cpp#L1318); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ForwardDeclaredOwner::~ForwardDeclaredOwner() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define destruction out of line after the nested Data type is complete so the accounted unique owner can destroy its forward-declared payload. |
| inputs / outputs | No arguments or result; when a \`ForwardDeclaredOwner\` leaves scope, its \`AccountedUnique&lt;Data&gt;\` member is destroyed. |
| invariants | The definition follows the complete \`Data\` declaration. \`MemoryDelete&lt;Data&gt;\` destroys the object then deallocates through its stored allocator. |
| ownership | The unique pointer owns Data; its deleter retains the MemoryAccount allocator and the \`cursor\` purpose chosen by the constructor. No separate raw Data pointer escapes this class. |
| failure | The destructor body is defaulted and has no catch or recovery branch. \`MemoryDelete&lt;T&gt;\` is \`noexcept\` and statically requires a nothrow-destructible payload, so this path exposes no recoverable destructor error. |
| cost | No allocation occurs in the definition. Object destruction releases one accounted Data allocation and updates the owning account. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/resource/ownership.hpp §AccountedUnique and MemoryDelete](../../../../../include/crown/resource/ownership.hpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [src/resource/memory.cpp §deallocation](../../../../../src/resource/memory.cpp) |

## B0088

[Lines 1319–1319](../../../../../tests/unit/memory_account_contract_test.cpp#L1319); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int ForwardDeclaredOwner::value() const noexcept { return data_->value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement test helper \`value\` on the arguments declared in source. |
| inputs / outputs | Inputs follow \`int ForwardDeclaredOwner::value() const noexcept\`; source calls \`ForwardDeclaredOwner::value\`. |
| invariants | Returns or throws according to its source body. |
| ownership | Borrows arguments during call unless returned value owns copied data; retained state is fixed trace storage. |
| failure | Allocator failures follow the operation called; no translation is added. |
| cost | 0 source loop(s); growth sites none; fixed tracer buffers prevent recursive trace allocation. |
| Design | tests/unit/memory_account_contract_test.cpp:1319-1319, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0090

[Lines 1321–1321](../../../../../tests/unit/memory_account_contract_test.cpp#L1321); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProbeConstructionFailure {};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinct exception marker for a throwing OwnershipProbe constructor after member setup. |
| inputs / outputs | Empty type is thrown when the explicit fail flag is true. |
| invariants | Separates constructor unwinding from injected std::bad_alloc. |
| ownership | Carries no resource or state. |
| failure | Caught by the factory test’s explicit marker handler. |
| cost | Empty exception marker; no account claim. |
| Design | tests/unit/memory_account_contract_test.cpp:1321-1321, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0091

[Lines 1322–1333](../../../../../tests/unit/memory_account_contract_test.cpp#L1322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct alignas(64) OwnershipProbe {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the over-aligned factory probe with an account-allocated nested vector and construction/destruction counters. |
| inputs / outputs | Constructor takes account/fail/tag; vector resizes to 96 integers of 37 before optional ProbeConstructionFailure. |
| invariants | Object alignment is 64; completed increments only after the throw point; destructor increments destroyed. |
| ownership | Factory owns object; vector allocator shares supplied account and is destroyed before object storage/control. |
| failure | Nested resize may throw bad_alloc; explicit fail flag throws ProbeConstructionFailure after member setup. |
| cost | Object/control/vector allocations are measured as actual new requests, not inferred from sizeof. |
| Design | tests/unit/memory_account_contract_test.cpp:1322-1333, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0093

[Lines 1335–1425](../../../../../tests/unit/memory_account_contract_test.cpp#L1335); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_unique_and_shared_lifetimes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise forward-declared unique ownership, 64-aligned object/member storage, shared alias/weak lifetime and last owner release. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Exercise forward-declared unique ownership, 64-aligned object/member storage, shared alias/weak lifetime and last owner release.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: forward-declared accounted owner lost its object; forward-declared accounted owner did not reclaim its object; unique object/member allocations did not reconcile with actual upstream requests; unique ownership move allocated or lost its nested state; unique deleter did not retain the object account after owner release. |
| ownership | Local owning types: \`MemoryAccount\`, \`std::weak_ptr\`, \`std::shared_ptr\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope() records successful C++ new requests without injecting failure; admission/validation categories are checked separately where present. |
| cost | Source-map evidence shows 0 loop(s), growth sites make_accounted_shared, make_accounted_unique. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1335-1425, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), include/crown/resource/allocator.hpp:20-96, include/crown/resource/ownership.hpp:1-76 |

## B0095

[Lines 1427–1517](../../../../../tests/unit/memory_account_contract_test.cpp#L1427); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_factory_construction_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep all measured unique/shared construction requests, explicit constructor throw, and exact/one-under observed peak. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Sweep all measured unique/shared construction requests, explicit constructor throw, and exact/one-under observed peak.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: shared factory changed a nested value; unique factory changed a nested value; successful factory sample did not reclaim all object/member allocations; factory allocation-position sample was empty or leaked; persistent factory failure leaked state, changed current attribution, or allocated in recovery. |
| ownership | Local owning types: \`MemoryAccount\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | The block selects a failure position and requires the upstream path to throw std::bad_alloc; validation/quota rejection is distinguished when asserted. |
| cost | Source-map evidence shows 3 loop(s), growth sites make_accounted_shared, make_accounted_unique. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1427-1517, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), include/crown/resource/allocator.hpp:20-96, include/crown/resource/ownership.hpp:1-76 |

## B0097

[Lines 1519–1543](../../../../../tests/unit/memory_account_contract_test.cpp#L1519); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify_attribution_partition(const MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile every supplied attribution partition to one account-wide snapshot. |
| inputs / outputs | Takes a MemoryAccount reference and a span of MemoryAttribution keys; reads each statistics_for result and returns void after fixed-array sums. |
| invariants | Each partition reports the same account owner and key; sums equal whole-account current/purpose/lifetime totals and reads do not mutate stats or call new. |
| ownership | Borrows the account and caller-owned span; accumulators are fixed local arrays and no owner registry escapes. |
| failure | Any partition mismatch throws test runtime_error; no allocator fault is injected. |
| cost | O(owner_count × outstanding allocations) because statistics_for scans per tag; fixed-array sums add no heap growth. |
| Design | tests/unit/memory_account_contract_test.cpp:1519-1543, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0099

[Lines 1545–1681](../../../../../tests/unit/memory_account_contract_test.cpp#L1545); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_operator_attribution_without_separate_grants() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check immutable attribution across blocks/allocators/row/factories under one account limit, including 48 transient tags. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Check immutable attribution across blocks/allocators/row/factories under one account limit, including 48 transient tags.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: binary\0payload; operator block bytes do not match the independently observed upstream request; controller attribution or empty distinct owner report is wrong; lifetime relabeling changed operator ownership or physical reservation; allocator rebind/equality lost immutable operator attribution. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryBlock\`, \`AccountedRow\`, \`MemoryAllocator\`, \`std::weak_ptr\`, \`std::vector\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 4 loop(s), growth sites allocate, clone, copy_of, make_accounted_shared, make_accounted_unique, push_back, reserve. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1545-1681, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0101

[Lines 1683–1693](../../../../../tests/unit/memory_account_contract_test.cpp#L1683); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
crown::storage::TupleLayout metadata_fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the ordinary source layout used to compare metadata freezing and projection semantics. |
| inputs / outputs | Takes no arguments and returns a TupleLayout with LayoutId 37, seven fields, LayoutContext version 11 and a 4096-byte binary binding. |
| invariants | Descriptor contains repeated VariableId 7, two constrained Decimal fields and TableId 3/origin 19. |
| ownership | Returns a public source DTO with its own vector/string storage; AccountedLayout later deep-copies it into the account. |
| failure | Ordinary TupleLayout/string allocation can propagate before the test’s injected freeze phase. |
| cost | Source string/field-vector allocations are setup costs outside MemoryAccount-owned freeze totals. |
| Design | tests/unit/memory_account_contract_test.cpp:1683-1693, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp) |

## B0102

[Lines 1694–1700](../../../../../tests/unit/memory_account_contract_test.cpp#L1694); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
crown::Row metadata_row_fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the source row used by metadata validation and projection tests. |
| inputs / outputs | Takes no arguments and returns an owning seven-cell Row with 4096-byte binary text, repeated integers, bool, boundary Date and extreme Decimal values. |
| invariants | Values satisfy the source layout’s field kinds, decimal domains and repeated-variable equality. |
| ownership | Returned Row owns its string/cell data independently; account-backed tuples must deep-copy it. |
| failure | Ordinary row/string parsing allocation may fail during setup before fault sweeps. |
| cost | The 4096-byte source string is fixture storage; account-backed copies are measured separately. |
| Design | tests/unit/memory_account_contract_test.cpp:1694-1700, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

## B0104

[Lines 1702–1797](../../../../../tests/unit/memory_account_contract_test.cpp#L1702); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_layout_identity_validation_and_retention() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test freeze deep copy, equal descriptor versus token identity, tuple diagnostics, cross-account clone and post-registry retention. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Test freeze deep copy, equal descriptor versus token identity, tuple diagnostics, cross-account clone and post-registry retention.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: source token alias was copied into another metadata allocation; frozen layout retained input storage or confused descriptor equality with token identity; invalid_tuple; scalar_overflow; compiled tuple validation changed semantics or allocated diagnostics. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedLayout\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 0 loop(s), growth sites clone, emplace. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1702-1797, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp) |

## B0106

[Lines 1799–1875](../../../../../tests/unit/memory_account_contract_test.cpp#L1799); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_layout_full_allocation_failure_sweep() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail each observed AccountedLayout freeze request and check prior-state rollback plus exact/one-byte-under measured peak. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Fail each observed AccountedLayout freeze request and check prior-state rollback plus exact/one-byte-under measured peak.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: metadata peak/current did not reconcile with independent raw allocation events; metadata sample missed scratch/control allocation positions; metadata failure did not unwind scratch/descriptor/control storage without recovery allocation; metadata failure changed prior state bytes; metadata failure sweep retained prior/controller storage. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryBlock\`, \`AccountedLayout\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | The block selects a failure position and requires the upstream path to throw std::bad_alloc; validation/quota rejection is distinguished when asserted. |
| cost | Source-map evidence shows 4 loop(s), growth sites allocate. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1799-1875, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp) |

## B0108

[Lines 1877–1955](../../../../../tests/unit/memory_account_contract_test.cpp#L1877); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_projection_values_tokens_and_retention() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare repeated-field AccountedProjection output with native oracle and check mapping-copy/token/output-owner behavior. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Compare repeated-field AccountedProjection output with native oracle and check mapping-copy/token/output-owner behavior.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: projection copy allocated or retained caller mapping storage; projection values/domain/token/attribution or independent repeated payloads differ from native oracle; layout_mismatch; invalid_projection; projection mismatch/invalid mapping diagnostics allocated or changed prior state. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedLayout\`, \`AccountedProjection\`, \`std::vector\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 0 loop(s), growth sites emplace. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1877-1955, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0110

[Lines 1957–2002](../../../../../tests/unit/memory_account_contract_test.cpp#L1957); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_projection_rejected_mapping_contracts() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject six mapping cases covering context, arity, scalar domain, variable identity and repeated-variable constraints. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Reject six mapping cases covering context, arity, scalar domain, variable identity and repeated-variable constraints.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: invalid_projection; invalid projection fixture was accepted by native reference oracle; projection descriptor proof accepted a bad mapping or retained temporary validation state; rejected projection proof retained metadata or map storage. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedLayout\`, \`AccountedProjection\`, \`std::vector\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope() records successful C++ new requests without injecting failure; admission/validation categories are checked separately where present. |
| cost | Source-map evidence shows 2 loop(s), growth sites none. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:1957-2002, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0112

[Lines 2004–2095](../../../../../tests/unit/memory_account_contract_test.cpp#L2004); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_projection_full_allocation_failure_sweep() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep freeze+apply allocation positions while preserving input tuple, then test exact/one-under peak admission. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Sweep freeze+apply allocation positions while preserving input tuple, then test exact/one-under peak admission.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: projection/output current or simultaneous peak differs from actual raw requests; projection sample missed scratch/control/output allocation positions; projection/output failure changed prior tuple state or attempted allocating recovery; projection failure sweep retained prior tuple/metadata storage; memory_limit. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryBlock\`, \`AccountedLayout\`, \`AccountedProjection\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | The block selects a failure position and requires the upstream path to throw std::bad_alloc; validation/quota rejection is distinguished when asserted. |
| cost | Source-map evidence shows 2 loop(s), growth sites allocate, emplace. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2004-2095, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0114

[Lines 2097–2140](../../../../../tests/unit/memory_account_contract_test.cpp#L2097); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_exact_allocation_usage_views() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check MemoryBlock and vector allocator usage against observed requests and reject wrong capacity/foreign owner. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Check MemoryBlock and vector allocator usage against observed requests and reject wrong capacity/foreign owner.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: block usage did not report the independently observed real request; container usage was a capacity estimate rather than its actual request; memory_contract; allocation introspection accepted wrong size/owner or changed its stored request; lifetime classification changed actual allocation usage. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryBlock\`, \`MemoryAllocator\`, \`std::vector\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 0 loop(s), growth sites allocate, emplace, reserve. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2097-2140, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0116

[Lines 2142–2236](../../../../../tests/unit/memory_account_contract_test.cpp#L2142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_arena_retention_generations_and_reports() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise arena pin/erase retention, directory growth, slot generation reuse, move, clear and full owner reporting. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Exercise arena pin/erase retention, directory growth, slot generation reuse, move, clear and full owner reporting.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: legacy/accounted arena identities collide or attribution is not the native owner; foreign_handle; accounted arena foreign-owner rejection allocated; layout_mismatch; arena accepted a descriptor-equal foreign token or allocated its rejection. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedLayout\`, \`AccountedTupleArena\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 1 loop(s), growth sites emplace, insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2142-2236, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp), [src/storage/accounted_arena.cpp](../../../../../src/storage/accounted_arena.cpp) |

## B0118

[Lines 2238–2349](../../../../../tests/unit/memory_account_contract_test.cpp#L2238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_arena_allocation_failures_and_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep arena construction/insertion/reuse allocation failures, check exact/under peaks and retry after the fault scope. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Sweep arena construction/insertion/reuse allocation failures, check exact/under peaks and retry after the fault scope.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: arena State/control construction failure changed accounting or allocated recovery; failed arena construction retained metadata/controller; arena reuse fixture erase failed; arena simultaneous peak differs from raw allocation events; arena allocation sample lost rows or outstanding request reconciliation. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedLayout\`, \`AccountedTupleArena\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | The block selects a failure position and requires the upstream path to throw std::bad_alloc; validation/quota rejection is distinguished when asserted. |
| cost | Source-map evidence shows 3 loop(s), growth sites emplace, insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2238-2349, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp), [src/storage/accounted_arena.cpp](../../../../../src/storage/accounted_arena.cpp) |

## B0120

[Lines 2351–2436](../../../../../tests/unit/memory_account_contract_test.cpp#L2351); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_arena_bounded_churn_model() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run 512 deterministic insert/erase/pin/unpin/clear steps over 16 keys/8 pins and verify final clear. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Run 512 deterministic insert/erase/pin/unpin/clear steps over 16 keys/8 pins and verify final clear.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: arena model erase failed; arena model live payload mismatch; arena model pin lifetime mismatch; arena model record census or actual requested bytes diverged; arena model diagnostics allocated. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedLayout\`, \`AccountedTupleArena\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 10 loop(s), growth sites emplace, insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2351-2436, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp), [src/storage/accounted_arena.cpp](../../../../../src/storage/accounted_arena.cpp) |

## B0122

[Lines 2438–2451](../../../../../tests/unit/memory_account_contract_test.cpp#L2438); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NativeTableInput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own public source layouts/projections/rows used to build accounted native-table fixtures. |
| inputs / outputs | Contains one 3-field layout, three one-field projected targets, four rows and static field-index arrays for fields 0/1/2. |
| invariants | The rows include repeated 4096-byte strings for equality/memory cases and a smaller retry row. |
| ownership | Owns standard source DTOs; \`NativeAccountedTableFixture\` later deep-copies them into a MemoryAccount. |
| failure | Ordinary fixture construction errors occur before native-table fault sweeps. |
| cost | Source strings/layout vectors allocate outside accounted table deltas; copied engine-owned requests are separately measured. |
| Design | tests/unit/memory_account_contract_test.cpp:2438-2451, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_reference.hpp](../../../../../include/crown/storage/accounted_reference.hpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), tests/unit/memory_account_contract_test.cpp:2438-2480 |

## B0123

[Lines 2452–2462](../../../../../tests/unit/memory_account_contract_test.cpp#L2452); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NativeAccountedTableFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build reusable native reference-table state for ownership, cursor, journal, and account-byte tests. |
| inputs / outputs | \`prepare_metadata(native, limit)\` creates an account (default 16 MiB), freezes the source and three target layouts/projections, and accounts four input tuples. \`prepare()\` then creates relation 6001, adds three indexes, and inserts the two selected handles. |
| invariants | The source \`NativeTableInput\` is borrowed during preparation; the four tuple members are accounted copies. \`before_table_live\` is sampled after metadata/tuple setup and before table storage. |
| ownership | The fixture owns the MemoryAccount handle, layouts, projections, tuple optionals, optional table/journal, and scalar handles/index IDs. Accounted objects route nested storage through the same controller; handles are identities, not payload owners. |
| failure | Layout/projection/tuple/table creation and insertions can throw on validation, account limit, or upstream failure. The helper has no catch or fixture rollback protocol; callers scope its lifetime and test failure behavior. |
| cost | Fixture setup creates fixed counts (four tuples, three projections/indexes, two rows). Raw \`memory_trace::live_bytes\` and MemoryAccount requested bytes are separately asserted; this is setup work, not runtime update complexity. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_projection.hpp](../../../../../include/crown/storage/accounted_projection.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [tests/unit/memory_account_contract_test.cpp §fixture callers](../../../../../tests/unit/memory_account_contract_test.cpp) |

## B0124

[Lines 2463–2473](../../../../../tests/unit/memory_account_contract_test.cpp#L2463); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_metadata(const NativeTableInput& native, std::uint64_t limit = 1U << 24) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare account-backed source/target layouts, projections and tuple inputs before native table setup. |
| inputs / outputs | Takes NativeTableInput and optional account limit (default 1&lt;&lt;24); mutates fixture fields and records the pre-table live-byte boundary. |
| invariants | All frozen layouts/projections and four tuples use one account; table-only measurement starts after metadata setup. |
| ownership | Fixture owns account, layouts, projections and tuple handles; native input remains an independent DTO oracle. |
| failure | Freeze/import allocation or quota failure propagates before table construction. |
| cost | Copies source/target descriptors, maps and row payloads; setup is excluded from later table-only bytes. |
| Design | tests/unit/memory_account_contract_test.cpp:2463-2473, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0125

[Lines 2474–2479](../../../../../tests/unit/memory_account_contract_test.cpp#L2474); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare(const NativeTableInput& native, std::uint64_t limit = 1U << 24) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish reference-table fixture setup after preparing account-backed metadata. |
| inputs / outputs | Takes native fixture plus optional cap; creates RelationId 6001, registers projections 0/1, and inserts input tuples 0/1. |
| invariants | Two handles/two index IDs identify baseline state; before_table_live remains before table ownership. |
| ownership | Fixture owns table, metadata and inputs on a shared account; handles borrow table owner/generation identity. |
| failure | Table/index/insert allocation failures propagate; dedicated sweeps inject around individual operations. |
| cost | Builds one table, two indexes and two rows; account bytes include allocator framing and container storage. |
| Design | tests/unit/memory_account_contract_test.cpp:2474-2479, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0126

[Lines 2480–2481](../../../../../tests/unit/memory_account_contract_test.cpp#L2480); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L2480-L2481:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in memory_account_contract_test.cpp: struct NativeAccountedTableFixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0127

[Lines 2482–2550](../../../../../tests/unit/memory_account_contract_test.cpp#L2482); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_native_table_ownership_journals_and_cursors() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native table and journal/cursor/pin/snapshot lifetimes with ReferenceTable, including orphaned outputs. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Compare native table and journal/cursor/pin/snapshot lifetimes with ReferenceTable, including orphaned outputs.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: native accounted table state/indices/rows do not reconcile with raw requests or owner identity; native table no-ops allocate or change registered index identity; no-op invalidated native cursors; storage_busy; exclusive table journal allowed a public cursor. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedTupleArena\`, \`AccountedReferenceTable\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 0 loop(s), growth sites emplace, insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2482-2550, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_reference.hpp](../../../../../include/crown/storage/accounted_reference.hpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), tests/unit/memory_account_contract_test.cpp:2438-2480 |

## B0129

[Lines 2552–2569](../../../../../tests/unit/memory_account_contract_test.cpp#L2552); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void perform_native_table_operation(NativeAccountedTableFixture& f, std::size_t operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch one numbered reference-table operation for the allocation-position sweep. |
| inputs / outputs | Takes fixture reference and operation index; executes one of 13 insert/index/erase/export/cursor/journal/table-construction paths and returns void. |
| invariants | Cases use prepared fixture inputs/projections/handles; an unknown index fails the test. |
| ownership | Borrows the fixture; snapshots/cursors/temporary table are operation-local and must release before comparison. |
| failure | A selected operation may propagate bad_alloc; retry happens only after fault scope closes. |
| cost | Actual new-request count is sampled by the caller for each case; erase_key also forms its projected key. |
| Design | tests/unit/memory_account_contract_test.cpp:2552-2569, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_reference.hpp](../../../../../include/crown/storage/accounted_reference.hpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), tests/unit/memory_account_contract_test.cpp:2438-2480 |

## B0131

[Lines 2571–2641](../../../../../tests/unit/memory_account_contract_test.cpp#L2571); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_native_table_allocation_failure_sweeps() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail every measured request across thirteen table operations and test exact/one-under insert peak. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Fail every measured request across thirteen table operations and test exact/one-under insert peak.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: native table peak differs from independent upstream events; native table allocation sample leaked or has no real positions; native table failure operation=%zu position=%zu\n; native table failure changed prior rows/handles/indexes/bytes or allocated recovery; failed journal operation published an undo entry. |
| ownership | Local owning types: fixed values and fixture state. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | The block selects a failure position and requires the upstream path to throw std::bad_alloc; validation/quota rejection is distinguished when asserted. |
| cost | Source-map evidence shows 3 loop(s), growth sites emplace, insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2571-2641, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_reference.hpp](../../../../../include/crown/storage/accounted_reference.hpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), tests/unit/memory_account_contract_test.cpp:2438-2480 |

## B0133

[Lines 2643–2708](../../../../../tests/unit/memory_account_contract_test.cpp#L2643); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_native_table_bounded_model_and_same_account_copy() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run 256 reference-table model steps and verify same-account snapshot-copy tokens and row IDs. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Run 256 reference-table model steps and verify same-account snapshot-copy tokens and row IDs.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: native oracle erase failed; accounted model erase failed; native table model membership differs from reference oracle; native table model row differs from oracle; native table churn leaked logical history, slots or actual requests. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedLayout\`, \`AccountedProjection\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 9 loop(s), growth sites insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2643-2708, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_reference.hpp](../../../../../include/crown/storage/accounted_reference.hpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), tests/unit/memory_account_contract_test.cpp:2438-2480 |

## B0135

[Lines 2710–2771](../../../../../tests/unit/memory_account_contract_test.cpp#L2710); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_native_journal_replacements_and_owner_lifetime() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test journal replacement rollback, tuple ID restore, committed history release, external pin and writer outliving facade. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Test journal replacement rollback, tuple ID restore, committed history release, external pin and writer outliving facade.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: replacement journal original erase failed; replacement reused a live identity or could not erase its own insert; second replacement or adjacent erase failed; invalid_cursor; multi-operation rollback lost original addresses/generation or retained tentative rows. |
| ownership | Local owning types: \`AccountedTupleArena\`, \`AccountedReferenceTable\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 0 loop(s), growth sites emplace, insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2710-2771, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_reference.hpp](../../../../../include/crown/storage/accounted_reference.hpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), tests/unit/memory_account_contract_test.cpp:2438-2480 |

## B0137

[Lines 2773–2791](../../../../../tests/unit/memory_account_contract_test.cpp#L2773); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_containing_allocation_classification() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test interior-pointer lifetime classification and wrong owner/account/purpose rejection. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Test interior-pointer lifetime classification and wrong owner/account/purpose rejection.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: portable interior classification did not affect the actual block; memory_contract; portable interior lookup accepted a different owner/account/purpose; portable classification allocated or changed physical byte history; portable classification fixture leaked. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryBlock\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 0 loop(s), growth sites allocate. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2773-2791, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0139

[Lines 2793–2795](../../../../../tests/unit/memory_account_contract_test.cpp#L2793); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr crown::storage::IndexWork indexed_test_work() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a high deterministic work allowance for ordinary indexed fixtures. |
| inputs / outputs | Takes no arguments; returns five IndexWork domains set to 1,000,000,000. |
| invariants | Routine fixture operations stay below this allowance; boundary tests replace it with smaller values. |
| ownership | Scalar value object; no account/control ownership. |
| failure | No helper failure path; table operations enforce work limits. |
| cost | O(1) scalar construction; work counts are not bytes. |
| Design | tests/unit/memory_account_contract_test.cpp:2793-2795, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0140

[Lines 2796–2798](../../../../../tests/unit/memory_account_contract_test.cpp#L2796); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr crown::storage::IndexedLimits indexed_test_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide finite indexed component ceilings for routine fixtures. |
| inputs / outputs | Takes no arguments; returns \`{80,4,256,320,640,4096,96,192,128}\`. |
| invariants | Initial two-index/two-row fixture fits; per-component tests override one ceiling. |
| ownership | Scalar values copied into table; no account ownership. |
| failure | No helper failure; table admission may reject at the selected cap. |
| cost | O(1) construction; fields count table components, not MemoryAccount bytes. |
| Design | tests/unit/memory_account_contract_test.cpp:2796-2798, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0141

[Lines 2799–2821](../../../../../tests/unit/memory_account_contract_test.cpp#L2799); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle a shared-account indexed table, metadata, work control and initial rows for indexed boundary/failure cases. |
| inputs / outputs | Members hold NativeAccountedTableFixture metadata, AccountedIndexWork, optional indexed table, two handles/indexes and table-byte boundary. |
| invariants | prepare() creates metadata/work/table, applies optional collision profile, then registers two indexes and two rows. |
| ownership | Fixture owns table/work/metadata; table and metadata share account; handles borrow table owner identity. |
| failure | Setup may propagate capacity/account/allocation failure; cases test operation failure afterward. |
| cost | Two rows/two indexes plus metadata setup; large default work allowance is separate from byte cap. |
| Design | tests/unit/memory_account_contract_test.cpp:2799-2821, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0143

[Lines 2823–2858](../../../../../tests/unit/memory_account_contract_test.cpp#L2823); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_indexed_work_and_allocation_identity() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check shared work-control identity, atomic multi-domain denial, and allocator classification by correct account/count. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Check shared work-control identity, atomic multi-domain denial, and allocator classification by correct account/count.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: direct allocator classification did not report its real allocation; memory_contract; direct header classification accepted wrong count or account; owning index work copy changed grant identity or admitted a different query; storage_work_limit. |
| ownership | Local owning types: \`MemoryAccount\`, \`MemoryAllocator\`, \`AccountedIndexWork\`, \`std::vector\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 0 loop(s), growth sites emplace, reserve. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2823-2858, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0145

[Lines 2860–2922](../../../../../tests/unit/memory_account_contract_test.cpp#L2860); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_indexed_journals_and_retention() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check indexed journal rollback/commit, history/cursor invalidation, work identity and orphan writer lifetime. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Check indexed journal rollback/commit, history/cursor invalidation, work identity and orphan writer lifetime.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: indexed owned records/directories differ from independent requests; indexed journal erase failed; indexed replacement journal lost identity; storage_contract; journal cursor accepted a different work object. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedTupleArena\`, \`AccountedIndexedTable\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 0 loop(s), growth sites emplace, insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2860-2922, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0147

[Lines 2924–2929](../../../../../tests/unit/memory_account_contract_test.cpp#L2924); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_indexed_operation(AccountedIndexedFixture& f, std::size_t operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the journal setup required by selected indexed operation cases. |
| inputs / outputs | Takes AccountedIndexedFixture and operation ID; starts journal for 4,5,15–17,19–20 and pre-inserts input 2 for 19/20. |
| invariants | Other operation IDs leave journal empty; dispatcher uses the same numeric operation map. |
| ownership | Journal is fixture-owned and shares table/account/work; input tuples remain fixture-owned. |
| failure | Journal/pre-insert allocations may fail before selected operation positions are sampled. |
| cost | Setup allocations are outside the per-operation count measured by the caller. |
| Design | tests/unit/memory_account_contract_test.cpp:2924-2929, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0148

[Lines 2930–2958](../../../../../tests/unit/memory_account_contract_test.cpp#L2930); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void perform_indexed_operation(AccountedIndexedFixture& f, std::size_t operation, crown::storage::IndexWorkAllowance& work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch one numbered indexed-table operation with its explicit work allowance. |
| inputs / outputs | Takes fixture reference, operation index and IndexWorkAllowance reference; executes one of 23 mutation/query/export/work-control paths. |
| invariants | Work-bearing table calls receive the provided grant; journal cases use fixture-owned state; unknown ID fails. |
| ownership | Borrows fixture and grant; snapshots/cursors/temp tables are local to the selected operation. |
| failure | Can propagate bad_alloc, memory_limit, storage_capacity or storage_work_limit to the sweep. |
| cost | Each operation’s new-request count is measured independently; key projection setup is included in erase_key/bucket cases. |
| Design | tests/unit/memory_account_contract_test.cpp:2930-2958, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0150

[Lines 2960–3014](../../../../../tests/unit/memory_account_contract_test.cpp#L2960); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_indexed_persistent_failures_and_peak() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep each observed allocation in 23 indexed operations and check exact/under insertion peak. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Sweep each observed allocation in 23 indexed operations and check exact/under insertion peak.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: indexed real peak differs from independent requests; indexed allocation sample leaked; indexed allocation failure operation=%zu position=%zu\n; indexed failure changed prior bytes/rows/indexes or allocated recovery; indexed persistent failure sweep leaked. |
| ownership | Local owning types: fixed values and fixture state. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | The block selects a failure position and requires the upstream path to throw std::bad_alloc; validation/quota rejection is distinguished when asserted. |
| cost | Source-map evidence shows 3 loop(s), growth sites insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:2960-3014, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0152

[Lines 3016–3099](../../../../../tests/unit/memory_account_contract_test.cpp#L3016); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_indexed_work_and_component_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure work dimensions, exact/one-under each nonzero dimension, nine component caps and three exhaustion counters. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Measure work dimensions, exact/one-under each nonzero dimension, nine component caps and three exhaustion counters.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: storage_work_limit; one-unit-under work denial changed owned state or allocated diagnostics; storage_capacity; finite indexed component denial changed previous state or byte partition; capacity failure lost old lookup. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedIndexWork\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 6 loop(s), growth sites insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:3016-3099, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0154

[Lines 3101–3172](../../../../../tests/unit/memory_account_contract_test.cpp#L3101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_indexed_churn_and_sparse_cursors() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run 256 oracle model steps and compare cursor startup after erasing from 8- and 64-row populations to eight live rows. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Run 256 oracle model steps and compare cursor startup after erasing from 8- and 64-row populations to eight live rows.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: indexed model erase failed; indexed model key census differs from reference; indexed model membership differs from reference; indexed model row differs from reference; indexed churn leaked logical history, rows or accounted bytes. |
| ownership | Local owning types: fixed values and fixture state. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 10 loop(s), growth sites insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:3101-3172, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0155

[Lines 3173–3181](../../../../../tests/unit/memory_account_contract_test.cpp#L3173); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedDispatchFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the same table fixture through the reference or indexed storage dispatcher for cross-backend accounting and failure checks. |
| inputs / outputs | \`prepare(native, backend)\` creates accounted index-work state and the chosen table; an optional collision-profile macro configures indexed test collisions, then a local explicit grant seeds three indexes and two inserts. |
| invariants | The metadata fixture supplies the account, layout, projections, and input tuples. The stored table backend must match the passed selector; collision overrides apply only to indexed test builds. |
| ownership | The nested fixture owns the account and source metadata; optional table/journal own backend state. \`handles\` and \`indices\` are scalar IDs; \`work\` is the shared test work owner used by later journals/cursors. |
| failure | Accounted work creation and table/index/insert operations may throw on allocation, validation, or work limits. This helper does not catch them. |
| cost | Setup is fixed at three indexes and two inserted rows per backend, with one local seeding grant. It records a raw byte baseline for later comparison; no CPU or production timing is measured. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [tests/unit/memory_account_contract_test.cpp §backend callers](../../../../../tests/unit/memory_account_contract_test.cpp) |

## B0156

[Lines 3182–3196](../../../../../tests/unit/memory_account_contract_test.cpp#L3182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare(const NativeTableInput& native, crown::storage::StorageBackend backend) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the composed AccountedStorageTable fixture for the selected backend. |
| inputs / outputs | Takes native input and backend; freezes metadata, creates work, builds reference/indexed facade, adds two indexes and inserts two rows. |
| invariants | Indexed collision mutation is compiled only under CROWN_ACCOUNTED_COLLISION_PROFILE; metadata and facade share account. |
| ownership | Fixture owns metadata, work and optional facade; handles refer to table owner IDs. |
| failure | Setup account/table/index/insert allocation errors propagate; separate tests sweep operation failures. |
| cost | Setup includes metadata copies plus two indexes/two rows and precedes the before_table_live boundary. |
| Design | tests/unit/memory_account_contract_test.cpp:3182-3196, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0157

[Lines 3197–3198](../../../../../tests/unit/memory_account_contract_test.cpp#L3197); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L3197-L3198:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in memory_account_contract_test.cpp: struct AccountedDispatchFixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0158

[Lines 3199–3201](../../../../../tests/unit/memory_account_contract_test.cpp#L3199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> concept TemporaryTableBorrow = requires(const T&& table, crown::TupleHandle handle) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Statically forbid borrowed payload access through an rvalue AccountedStorageTable. |
| inputs / outputs | For T, checks whether \`std::move(table).get(handle)\` is a valid expression. |
| invariants | Static assertion requires the concept to be false for AccountedStorageTable. |
| ownership | Compile-time only; no table or handle is constructed and no payload is borrowed. |
| failure | Ill-formed rvalue overload resolution is the intended outcome; no runtime exception. |
| cost | Compile-time requires-expression; no runtime allocation or work charge. |
| Design | tests/unit/memory_account_contract_test.cpp:3199-3201, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0159

[Lines 3202–3203](../../../../../tests/unit/memory_account_contract_test.cpp#L3202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> concept TemporaryTableBorrowWithWork = requires(const T&& table, crown::TupleHandle handle,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Statically forbid work-aware payload borrowing through an rvalue AccountedStorageTable. |
| inputs / outputs | For T, checks whether \`std::move(table).get(handle, IndexWorkAllowance*)\` is a valid expression. |
| invariants | Static assertion requires false for AccountedStorageTable, including the indexed overload. |
| ownership | Compile-time only; the grant pointer is a type placeholder and never refers to live state. |
| failure | Ill-formed rvalue overload resolution is the intended outcome. |
| cost | Compile-time constraint check; no runtime work or allocation. |
| Design | tests/unit/memory_account_contract_test.cpp:3202-3203, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0160

[Lines 3204–3206](../../../../../tests/unit/memory_account_contract_test.cpp#L3204); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(!TemporaryTableBorrow<crown::storage::AccountedStorageTable> &&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make compilation reject borrowing a tuple pointer from a temporary dispatched table, with or without an IndexWork grant. |
| inputs / outputs | The two requires-expressions probe \`std::move(table).get(handle)\` and \`std::move(table).get(handle, work)\` for \`AccountedStorageTable\`. |
| invariants | Both rvalue expressions must be unavailable, matching the deleted \`get(...) const &&\` overload. This prevents taking a borrow directly from a temporary table expression; it does not keep a pointer obtained from a named table alive after that table or row is destroyed. |
| ownership | Compile-time only; a successful lvalue \`get\` returns a borrowed pointer whose validity depends on the table and row lifetime. |
| failure | No runtime exception path exists here. If either rvalue expression becomes viable, the static assertion fails the test target build. |
| cost | Compile-time requires/trait checks only; no table lookup, account allocation, or per-call overhead. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/storage/accounted_table.hpp §get ref-qualified overloads](../../../../../include/crown/storage/accounted_table.hpp) |

## B0161

[Lines 3207–3326](../../../../../tests/unit/memory_account_contract_test.cpp#L3207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_native_dispatch_and_composed_journals() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise public reference/indexed backend dispatch and prove two writers share one indexed work grant. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Exercise public reference/indexed backend dispatch and prove two writers share one indexed work grant.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: accounted dispatch changed backend, identities or metadata; accounted dispatch report lost actual backend ownership; dispatch pin or borrowed value copied payload; dispatch probes/report/pin/diagnostic allocated; accounted dispatch collections changed logical contents. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedTupleArena\`, \`AccountedStorageTable\`, \`AccountedIndexWork\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 1 loop(s), growth sites emplace, insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:3207-3326, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_reference.hpp](../../../../../include/crown/storage/accounted_reference.hpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), tests/unit/memory_account_contract_test.cpp:2438-2480, [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp) |

## B0163

[Lines 3328–3388](../../../../../tests/unit/memory_account_contract_test.cpp#L3328); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_native_dispatch_allocation_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep seven public dispatch allocation operations on both backends while preserving initial state. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Sweep seven public dispatch allocation operations on both backends while preserving initial state.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: dispatch copy sample lost rows; dispatch snapshot sample lost rows; dispatch allocation sample missing or leaked; dispatch did not persistently fail an observed position; dispatch allocation failure changed previous state or retained temporary bytes. |
| ownership | Local owning types: \`AccountedStorageTable\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 3 loop(s), growth sites emplace, insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:3328-3388, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_reference.hpp](../../../../../include/crown/storage/accounted_reference.hpp), [src/storage/accounted_reference.cpp](../../../../../src/storage/accounted_reference.cpp), tests/unit/memory_account_contract_test.cpp:2438-2480, [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp) |

## B0164

[Lines 3389–3411](../../../../../tests/unit/memory_account_contract_test.cpp#L3389); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NativePlanStorageInput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply deterministic native-looking metadata to the test-only accounted plan-storage bridge. |
| inputs / outputs | The selected fields define a synthetic 64-character identity, three layouts, three relations, three index requirements, and three sample rows. The \`specification()\` and \`create()\` methods immediately after this selected range choose backend options and pass the fixture spans to the test-only bridge. |
| invariants | The identity and row values are synthetic test inputs, not a compiler-admitted physical identity or production plan. The three index bindings deliberately include shared and distinct projection tokens. |
| ownership | The fixture owns its source values. \`create()\` borrows their spans/string view for the call; the test-only constructor freezes account-owned layout/projection metadata and materializes tables in the receiving MemoryAccount. |
| failure | The bridge and account-backed construction can throw for invalid bindings, work caps, memory caps, or upstream allocation. The fixture does not translate those errors. |
| cost | The fixture supplies three layouts, relations, index requirements, and three rows, including two 4-KiB strings. Construction charges account storage and indexed metadata work where selected; these synthetic inputs do not measure CPU or represent a genuine compiler admission. |
| Design | [tests/unit/memory_account_contract_test.cpp §plan fixture callers](../../../../../tests/unit/memory_account_contract_test.cpp), [src/storage/accounted_plan_testing.hpp](../../../../../src/storage/accounted_plan_testing.hpp), [src/storage/accounted_plan.cpp §accounted metadata construction](../../../../../src/storage/accounted_plan.cpp), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp) |

## B0165

[Lines 3412–3415](../../../../../tests/unit/memory_account_contract_test.cpp#L3412); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::optional<crown::storage::IndexedBackendSpec> specification(crown::storage::StorageBackend backend) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select optional backend-specific limits/work metadata for the plan fixture. |
| inputs / outputs | Takes StorageBackend; returns empty for reference_ordered_v1 or IndexedBackendSpec from test limits/work for indexed backend. |
| invariants | Backend choice determines whether indexed parameters enter plan construction. |
| ownership | Returns a value; borrows no account or table state. |
| failure | No explicit failure for the two backend enum values used by this fixture. |
| cost | O(1) optional/value construction; no table/account allocation. |
| Design | tests/unit/memory_account_contract_test.cpp:3412-3415, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp) |

## B0166

[Lines 3416–3420](../../../../../tests/unit/memory_account_contract_test.cpp#L3416); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] crown::storage::AccountedPlanStorage create(const crown::resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct AccountedPlanStorage through its private test-only metadata shim. |
| inputs / outputs | Takes account, backend, borrowed fixture arrays/spans and optional work pointer; returns AccountedPlanStorage. |
| invariants | Plan owns frozen copies and preserves intended aliases; input spans need live only during construction. |
| ownership | Borrows NativePlanStorageInput arrays during call; returned plan owns account-backed storage. |
| failure | Plan validation, quota and allocation errors propagate from the actual constructor; shim adds no translation. |
| cost | Variable descriptor/binding/index preparation; actual allocations charge the supplied account. |
| Design | tests/unit/memory_account_contract_test.cpp:3416-3420, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [src/storage/accounted_plan_testing.hpp](../../../../../src/storage/accounted_plan_testing.hpp) |

## B0167

[Lines 3421–3421](../../../../../tests/unit/memory_account_contract_test.cpp#L3421); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L3421-L3421:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in memory_account_contract_test.cpp: struct NativePlanStorageInput. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0168

[Lines 3422–3436](../../../../../tests/unit/memory_account_contract_test.cpp#L3422); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedPlanFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle a shared-account plan, three imported row inputs and two initial handles per relation. |
| inputs / outputs | Members are MemoryAccount, optional AccountedPlanStorage, three optional AccountedTuple inputs and 3×2 TupleHandles. |
| invariants | prepare() creates plan via NativePlanStorageInput and inserts two rows in each of three relations. |
| ownership | Plan and inputs retain the same account; handles are relation-owner-scoped identifiers. |
| failure | Caller cap may fail during partial setup; one-under fixture explicitly verifies retry state. |
| cost | Three relations × two rows, plus shared metadata; usage is measured from actual account totals. |
| Design | tests/unit/memory_account_contract_test.cpp:3422-3436, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [src/storage/accounted_plan_testing.hpp](../../../../../src/storage/accounted_plan_testing.hpp) |

## B0169

[Lines 3437–3437](../../../../../tests/unit/memory_account_contract_test.cpp#L3437); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> concept TemporaryPlanBorrow = requires(const T&& plan) { std::move(plan).table(crown::RelationId{0}); };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Statically reject AccountedPlanStorage table borrowing from a temporary plan. |
| inputs / outputs | For T, checks whether \`std::move(plan).table(RelationId{0})\` is a valid expression. |
| invariants | Static assertion requires false for AccountedPlanStorage. |
| ownership | Compile-time only; no plan or table reference is created. |
| failure | Ill-formed rvalue overload resolution is intended; no runtime error. |
| cost | Compile-time requires-expression; no runtime allocation or account work. |
| Design | tests/unit/memory_account_contract_test.cpp:3437-3437, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [src/storage/accounted_plan_testing.hpp](../../../../../src/storage/accounted_plan_testing.hpp) |

## B0170

[Lines 3438–3439](../../../../../tests/unit/memory_account_contract_test.cpp#L3438); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(!TemporaryPlanBorrow<crown::storage::AccountedPlanStorage>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a table reference to be unavailable when selected from a temporary \`AccountedPlanStorage\`. |
| inputs / outputs | The concept probes \`std::move(plan).table(RelationId{0})\` and the assertion requires that expression to be ill-formed. |
| invariants | The concept probes \`std::move(plan).table(RelationId{0})\`, matching the deleted \`table(...) const &&\` overload. It rejects a borrow directly from a temporary plan expression; callers must still retain a named plan while using a borrowed table reference. |
| ownership | The assertion owns no plan or table; an actual table borrow remains tied to the plan object and its storage lifetime. |
| failure | This is a compile-time guard. A newly viable rvalue overload causes compilation failure; there is no runtime catch here. |
| cost | No runtime call or allocation; only concept substitution and static assertion during compilation. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [include/crown/storage/accounted_plan.hpp §table ref-qualified overloads](../../../../../include/crown/storage/accounted_plan.hpp) |

## B0171

[Lines 3440–3546](../../../../../tests/unit/memory_account_contract_test.cpp#L3440); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_compiled_plan_binding_and_lifetimes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check source release, shared/distinct metadata aliases, same-account copy, move ownership and work boundaries. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Check source release, shared/distinct metadata aliases, same-account copy, move ownership and work boundaries.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa; plan binding retained source metadata or collapsed distinct projection tokens; plan binding lost source aliases/native row or index identities; plan metadata/instance/table/arena/input records did not reconcile with actual requests; plan binding diagnostics allocated. |
| ownership | Local owning types: \`MemoryAccount\`, \`AccountedTupleArena\`, \`AccountedPlanStorage\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 7 loop(s), growth sites emplace. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:3440-3546, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [src/storage/accounted_plan_testing.hpp](../../../../../src/storage/accounted_plan_testing.hpp) |

## B0173

[Lines 3548–3597](../../../../../tests/unit/memory_account_contract_test.cpp#L3548); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_accounted_compiled_plan_allocation_failures_and_peak() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep construction/snapshot-copy requests for both plan backends and test measured exact/one-under peaks. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Sweep construction/snapshot-copy requests for both plan backends and test measured exact/one-under peaks.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: plan allocation sample missing or leaked; plan missed persistent failure at observed request; failed plan constructor/copy changed existing ownership/rows; plan failure invariant allocated; plan failure sweep leaked. |
| ownership | Local owning types: fixed values and fixture state. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | Scope(0) is a zero-new oracle for the covered diagnostic/read path: any ordinary C++ new request fails immediately. Direct malloc/syscalls are outside the seam. |
| cost | Source-map evidence shows 3 loop(s), growth sites insert. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:3548-3597, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), [include/crown/storage/accounted_plan.hpp](../../../../../include/crown/storage/accounted_plan.hpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [src/storage/accounted_plan_testing.hpp](../../../../../src/storage/accounted_plan_testing.hpp) |

## B0175

[Lines 3599–3603](../../../../../tests/unit/memory_account_contract_test.cpp#L3599); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_empty_handle_and_unique_current_bytes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require statistics() on a default empty MemoryAccount to return memory_contract. |
| inputs / outputs | Takes no arguments and returns void. It constructs/operates on Require statistics() on a default empty MemoryAccount to return memory_contract.; observable results are the state/error assertions in the invariant field. |
| invariants | Assertions in this block include: memory_contract; empty handle statistics were not rejected as a contract error. |
| ownership | Local owning types: \`MemoryAccount\`. Accounted values retain shared controls through their defined handles; public Row/DTO inputs remain separate oracles when copied. |
| failure | No position-based allocation fault is injected. This is test-oracle evidence, not a production failure theorem. |
| cost | Source-map evidence shows 0 loop(s), growth sites none. Replacement C++ new records raw request sizes; MemoryAccount requested_bytes include header/alignment framing and payload_bytes is caller size. Direct malloc/syscalls are outside the seam. |
| Design | tests/unit/memory_account_contract_test.cpp:3599-3603, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt), include/crown/resource/allocator.hpp:20-96, include/crown/resource/ownership.hpp:1-76 |

## B0176

[Lines 3604–3605](../../../../../tests/unit/memory_account_contract_test.cpp#L3604); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L3604-L3605:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in memory_account_contract_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/memory_account_contract_test.cpp](../../../../../tests/unit/memory_account_contract_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0177

[Lines 3606–3648](../../../../../tests/unit/memory_account_contract_test.cpp#L3606); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the memory-account component checks in fixed order and print success only after every function returns. |
| inputs / outputs | Takes no arguments; returns 0 after 40 named test/helper entry points complete, otherwise an uncaught exception exits the test process. |
| invariants | The success message is reached only after all registered function calls return; no whole-query acceptance is claimed. |
| ownership | Each called test owns and releases its own fixture/account state; no fixture state is shared across cases. |
| failure | An uncaught assertion/runtime/allocation exception prevents later calls and yields process failure; main has no catch/retry boundary. |
| cost | Sequentially invokes the component cases; each test’s own request sweeps dominate, while this dispatch adds no account allocation. |
| Design | tests/unit/memory_account_contract_test.cpp:3606-3648, include/crown/resource/memory.hpp:71-182, src/resource/memory.cpp:83-265, [CMakeLists.txt](../../../../../CMakeLists.txt) |
