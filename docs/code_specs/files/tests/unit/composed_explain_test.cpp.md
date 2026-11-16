# `tests/unit/composed_explain_test.cpp` — block usage map

[Source](../../../../../tests/unit/composed_explain_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e940c8b51a89b122bc7b47feb1aa24adae979bf1b59927a69c701bc7359d99d1`. 130 lines partitioned into 59 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/composed_explain_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 21–21](../../../../../tests/unit/composed_explain_test.cpp#L21) | Type/record definition: struct Unexpected |  · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../tests/unit/composed_explain_test.cpp#L22) | Callable definition: void check() | calls ; guard void check(){if(armed){if(remaining==0){if(unexpected)throw Unexpected{};throw std::bad_alloc{};}--… · [reviewed contract](#b0003) |
| [B0004 · 23–23](../../../../../tests/unit/composed_explain_test.cpp#L23) | Callable definition: void* allocate(std::size_t n) | calls check, std::malloc; guard void* allocate(std::size_t n){check();if(void* p=std::malloc(n==0?1:n))return p;throw std::bad_allo…; returns p; growth allocate, malloc · [reviewed contract](#b0004) |
| [B0005 · 24–24](../../../../../tests/unit/composed_explain_test.cpp#L24) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 25–25](../../../../../tests/unit/composed_explain_test.cpp#L25) | Callable definition: void* operator new(std::size_t n) | calls fault::allocate; returns fault::allocate(n); growth allocate, new · [reviewed contract](#b0006) |
| [B0007 · 26–26](../../../../../tests/unit/composed_explain_test.cpp#L26) | Callable definition: void* operator new\[\](std::size_t n) | calls ; returns fault::allocate(n); growth allocate, new · [reviewed contract](#b0007) |
| [B0008 · 27–27](../../../../../tests/unit/composed_explain_test.cpp#L27) | Callable definition: void operator delete(void* p) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 28–28](../../../../../tests/unit/composed_explain_test.cpp#L28) | Callable definition: void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 29–29](../../../../../tests/unit/composed_explain_test.cpp#L29) | Callable definition: void operator delete(void* p,std::size_t) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 30–30](../../../../../tests/unit/composed_explain_test.cpp#L30) | Callable definition: void operator delete\[\](void* p,std::size_t) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 31–31](../../../../../tests/unit/composed_explain_test.cpp#L31) | Callable definition: void* operator new(std::size_t n,std::align_val_t a) | calls fault::check, posix_memalign; guard void* operator new(std::size_t n,std::align_val_t a){fault::check();void* p=nullptr;if(posix_memali…; returns p; growth new · [reviewed contract](#b0012) |
| [B0013 · 32–32](../../../../../tests/unit/composed_explain_test.cpp#L32) | Callable definition: void* operator new\[\](std::size_t n,std::align_val_t a) | calls ; returns ::operator new(n,a); growth new · [reviewed contract](#b0013) |
| [B0014 · 33–33](../../../../../tests/unit/composed_explain_test.cpp#L33) | Callable definition: void operator delete(void* p,std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0014) |
| [B0015 · 34–34](../../../../../tests/unit/composed_explain_test.cpp#L34) | Callable definition: void operator delete\[\](void* p,std::align_val_t) noexcept | calls  · [reviewed contract](#b0015) |
| [B0016 · 35–35](../../../../../tests/unit/composed_explain_test.cpp#L35) | Callable definition: void operator delete(void* p,std::size_t,std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0016) |
| [B0017 · 36–36](../../../../../tests/unit/composed_explain_test.cpp#L36) | Callable definition: void operator delete\[\](void* p,std::size_t,std::align_val_t) noexcept | calls  · [reviewed contract](#b0017) |
| [B0018 · 37–46](../../../../../tests/unit/composed_explain_test.cpp#L37) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;Report&gt;); · [reviewed contract](#b0018) |
| [B0019 · 47–47](../../../../../tests/unit/composed_explain_test.cpp#L47) | Callable definition: std::uint64_t clock_tick() noexcept | calls ; returns ++clocks*10 · [reviewed contract](#b0019) |
| [B0020 · 48–48](../../../../../tests/unit/composed_explain_test.cpp#L48) | Callable definition: void check(bool x,const char* message) | calls std::runtime_error; guard void check(bool x,const char* message){if(!x)throw std::runtime_error(message);} · [reviewed contract](#b0020) |
| [B0021 · 49–49](../../../../../tests/unit/composed_explain_test.cpp#L49) | Callable definition: template&lt;class F&gt;void error(F&& f,const char* code=nullptr) | calls f, check, code; guard template&lt;class F&gt;void error(F&& f,const char* code=nullptr){bool caught=false;try{f();}catch(const … · [reviewed contract](#b0021) |
| [B0022 · 50–51](../../../../../tests/unit/composed_explain_test.cpp#L50) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0022) |
| [B0023 · 52–52](../../../../../tests/unit/composed_explain_test.cpp#L52) | Callable definition: void write(const std::filesystem::path& p,const std::string& s) | calls o, data, size, check; guard void write(const std::filesystem::path& p,const std::string& s){std::ofstream o(p,std::ios::binary)… · [reviewed contract](#b0023) |
| [B0024 · 53–53](../../../../../tests/unit/composed_explain_test.cpp#L53) | Callable definition: Row row(std::int64_t n) | calls ; returns {Value{n}} · [reviewed contract](#b0024) |
| [B0025 · 54–61](../../../../../tests/unit/composed_explain_test.cpp#L54) | Type/record definition: struct Fixture | returns lower_tree(c,q,tree); {seq,TableId{1},SetOperation::insert,row(9)}; growth insert · [reviewed contract](#b0025) |
| [B0026 · 62–62](../../../../../tests/unit/composed_explain_test.cpp#L62) | Callable definition: DeltaOptions opts(ObservationMode mode=ObservationMode::trace) | calls ; returns o · [reviewed contract](#b0026) |
| [B0027 · 63–63](../../../../../tests/unit/composed_explain_test.cpp#L63) | Callable definition: std::shared_ptr&lt;const DeclaredBenchmarkContext&gt; label(std::string value) | calls std::move; returns std::make_shared&lt;const DeclaredBenchmarkContext&gt;(BenchmarkLabels{std::move(value),@ ,@ ,@ }); growth make_shared · [reviewed contract](#b0027) |
| [B0028 · 64–64](../../../../../tests/unit/composed_explain_test.cpp#L64) | Callable definition: std::string hex(std::string_view x) | calls empty; returns @; s; 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 65–65](../../../../../tests/unit/composed_explain_test.cpp#L65) | Callable definition: template&lt;class T&gt;void opt(std::ostream& o,const std::optional&lt;T&gt;& v) | calls  · [reviewed contract](#b0029) |
| [B0030 · 66–66](../../../../../tests/unit/composed_explain_test.cpp#L66) | Callable definition: void configuration(std::ostream& o,const char* scope,const std::optional&lt;ObservationConfiguration&gt;& cfg) | calls requested_options, support_owner, generation, generation_saturated · [reviewed contract](#b0030) |
| [B0031 · 67–67](../../../../../tests/unit/composed_explain_test.cpp#L67) | Callable definition: void declared(std::ostream& o,const char* scope,const std::shared_ptr&lt;const DeclaredBenchmarkContext&gt;& d) | calls labels, hex; 1 loop sites · [reviewed contract](#b0031) |
| [B0032 · 68–68](../../../../../tests/unit/composed_explain_test.cpp#L68) | Callable definition: auto option_tuple(const DeltaOptions& x) | calls ; returns std::tuple{x.mode,x.completion,x.live_maintenance,x.view,x.work_limit,x.cursor.work_limit,x.epoch_v… · [reviewed contract](#b0032) |
| [B0033 · 69–69](../../../../../tests/unit/composed_explain_test.cpp#L69) | Callable definition: std::string option_native(const DeltaOptions& x) | calls constexpr, has_value, opt, std::apply; returns o.str() · [reviewed contract](#b0033) |
| [B0034 · 70–70](../../../../../tests/unit/composed_explain_test.cpp#L70) | Callable definition: void initialization(std::ostream& o,const char* scope,const std::optional&lt;InitializationContext&gt;& c) | calls opt · [reviewed contract](#b0034) |
| [B0035 · 71–71](../../../../../tests/unit/composed_explain_test.cpp#L71) | Callable definition: std::string plan_native(const auto& p) | calls route, opt, validation, tree; returns o.str(); 4 loop sites · [reviewed contract](#b0035) |
| [B0036 · 72–72](../../../../../tests/unit/composed_explain_test.cpp#L72) | Callable definition: std::string session_context_native(const std::shared_ptr&lt;const SessionRunContext&gt;& c) | calls hex, opt, n, export_value; returns @; o.str(); 2 loop sites · [reviewed contract](#b0036) |
| [B0037 · 73–75](../../../../../tests/unit/composed_explain_test.cpp#L73) | Callable definition: std::string observation_native(const ObservationTrace& t) | calls session_context_native, initialization, configuration, declared; returns o.str(); 3 loop sites · [reviewed contract](#b0037) |
| [B0038 · 76–76](../../../../../tests/unit/composed_explain_test.cpp#L76) | Callable definition: std::string gauge_native(const auto& g) | calls str; returns o.str(); o.str(); 2 loop sites · [reviewed contract](#b0038) |
| [B0039 · 77–77](../../../../../tests/unit/composed_explain_test.cpp#L77) | Callable definition: std::string status_native(const SessionStatus& s) | calls opt, str; returns o.str() · [reviewed contract](#b0039) |
| [B0040 · 78–78](../../../../../tests/unit/composed_explain_test.cpp#L78) | Callable definition: void cursor_work(std::ostream& o,const char* scope,const CursorWork& w) | calls  · [reviewed contract](#b0040) |
| [B0041 · 79–79](../../../../../tests/unit/composed_explain_test.cpp#L79) | Callable definition: std::string cursor_native(const std::optional&lt;CursorObservation&gt;& c) | calls cursor_work, configuration, opt, size; returns @; o.str(); 2 loop sites · [reviewed contract](#b0041) |
| [B0042 · 80–80](../../../../../tests/unit/composed_explain_test.cpp#L80) | Callable definition: std::string runtime_native(SupportOwnerId id,std::uint64_t sequence,std::optional&lt;DeltaState&gt; state,const DeltaRuntimeProfile& p) | calls str; returns o.str() · [reviewed contract](#b0042) |
| [B0043 · 81–81](../../../../../tests/unit/composed_explain_test.cpp#L81) | Callable definition: std::string owner_native(const DeltaRuntime& owner) | calls state, committed_state_gauges, runtime_native, owner; returns runtime_native(owner.owner(),owner.sequence(),owner.state(),owner.profile())+plan_native(owner.plan… · [reviewed contract](#b0043) |
| [B0044 · 82–82](../../../../../tests/unit/composed_explain_test.cpp#L82) | Callable definition: std::string owner_native(const QuerySession& owner) | calls report_metadata, runtime_native, owner, sequence; returns runtime_native(metadata.owner(),metadata.sequence(),metadata.state(),metadata.profile())+plan_nativ… · [reviewed contract](#b0044) |
| [B0045 · 83–83](../../../../../tests/unit/composed_explain_test.cpp#L83) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0045) |
| [B0046 · 84–84](../../../../../tests/unit/composed_explain_test.cpp#L84) | Callable definition: void boundary(const Report& r,Encoder encode) | calls encode, check, size, error; guard void boundary(const Report& r,Encoder encode){const auto s=encode(r,{});check(encode(r,{s.size()})=… · [reviewed contract](#b0046) |
| [B0047 · 85–85](../../../../../tests/unit/composed_explain_test.cpp#L85) | Callable definition: void emit(const char* name,const Report& r,const std::string& native) | calls std::to_string, write, string, io::write_explain_json · [reviewed contract](#b0047) |
| [B0048 · 86–86](../../../../../tests/unit/composed_explain_test.cpp#L86) | Callable definition: template&lt;class Owner&gt;Report capture(Owner& owner,const char* label_name=nullptr) | calls owner_native, constexpr, report_metadata, options; guard template&lt;class Owner&gt;Report capture(Owner& owner,const char* label_name=nullptr){const auto before=…; returns owner.report_metadata().options(); owner.options() · [reviewed contract](#b0048) |
| [B0049 · 87–87](../../../../../tests/unit/composed_explain_test.cpp#L87) | Callable definition: void metric(const ObservationSummary& s,MetricId id,MetricAvailability a,std::uint64_t v=0) | calls check; guard void metric(const ObservationSummary& s,MetricId id,MetricAvailability a,std::uint64_t v=0){const a… · [reviewed contract](#b0049) |
| [B0050 · 88–103](../../../../../tests/unit/composed_explain_test.cpp#L88) | Callable definition: void lifecycle() | calls DeltaRuntime::initialize, plan, opts, check; guard for(auto method:{BuildMethod::direct,BuildMethod::insertion_replay}){BuildOptions b{method,99991};a…; returns r.kind==TraceKind::native_event; r.kind==TraceKind::child_enqueued; 5 loop sites; source comment (unverified): // Output callbacks describe actual attempts, not caller labels or durable delivery. · [reviewed contract](#b0050) |
| [B0051 · 104–104](../../../../../tests/unit/composed_explain_test.cpp#L104) | Callable definition: void enqueue(QuerySession& s,PhysicalSetUpdate u) | calls batch, std::move, check; guard void enqueue(QuerySession& s,PhysicalSetUpdate u){io::TransportBatch batch({io::InputEvent{std::mov… · [reviewed contract](#b0051) |
| [B0052 · 105–108](../../../../../tests/unit/composed_explain_test.cpp#L105) | Callable definition: void sessions() | calls opts, label, QuerySession::create_typed, plan; guard void sessions(){Fixture f;SessionOptions o;o.delta=opts();o.declared_benchmark=label("session");o.s…; 3 loop sites; source comment (unverified): // Window metadata-only pending barrier must withhold gauges while delta itself is ready. · [reviewed contract](#b0052) |
| [B0053 · 109–110](../../../../../tests/unit/composed_explain_test.cpp#L109) | Callable definition: void caps() | calls push_back, insert, row, opts; guard void caps(){Fixture f;for(bool heavy:{false,true}){auto fixture=f;if(heavy){fixture.c.tables\[1\].con…; growth insert, push_back; 2 loop sites · [reviewed contract](#b0053) |
| [B0054 · 111–111](../../../../../tests/unit/composed_explain_test.cpp#L111) | Callable definition: VerifiedOptimum optimum(const Catalog& c,const Query& q) | calls reset, ExactSearch::create, progress, advance; guard VerifiedOptimum optimum(const Catalog& c,const Query& q){SearchOptions o;o.limits.producer.work.res…; returns *s.optimum(); 1 loop sites · [reviewed contract](#b0054) |
| [B0055 · 112–123](../../../../../tests/unit/composed_explain_test.cpp#L112) | Callable definition: void authority() | calls optimum, reset, reference::exhaustive_minimum_tree, check; guard void authority(){Fixture f;auto proof=optimum(f.c,f.q);SearchLimits l;l.work_limit.reset();l.recurs…; returns std::pair{std::move(report),std::move(native_facts)}; growth push_back; 3 loop sites; source comment (unverified): // Same structural shape is insufficient: metadata, aliases and source identity are exact native fences. · [reviewed contract](#b0055) |
| [B0056 · 124–124](../../../../../tests/unit/composed_explain_test.cpp#L124) | Callable definition: template&lt;class F,class Verify&gt;void sweep(F&& op,Verify&& verify) | calls op, verify, check, max; guard template&lt;class F,class Verify&gt;void sweep(F&& op,Verify&& verify){std::size_t failures=0;for(std::si…; 1 loop sites · [reviewed contract](#b0056) |
| [B0057 · 125–128](../../../../../tests/unit/composed_explain_test.cpp#L125) | Callable definition: void faults() | calls DeltaRuntime::initialize, plan, opts, apply; guard void faults(){Fixture f;auto runtime=DeltaRuntime::initialize(f.plan(),f.db,opts());auto e=runtime.…; 2 loop sites · [reviewed contract](#b0057) |
| [B0058 · 129–129](../../../../../tests/unit/composed_explain_test.cpp#L129) | Closes surrounding scope/type. |  · [reviewed contract](#b0058) |
| [B0059 · 130–130](../../../../../tests/unit/composed_explain_test.cpp#L130) | Callable definition: int main(int argc,char** argv) | calls check, std::filesystem::create_directories, detail::set_observation_clock_for_testing, lifecycle; guard int main(int argc,char** argv){try{check(argc&gt;=2,"usage: composed-test OUTPUT \[all\|lifecycle\|sessio…; returns 0; 1 · [reviewed contract](#b0059) |

## B0001

[Lines 1–20](../../../../../tests/unit/composed_explain_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:f2f3621a0dddf5cbc7a55ee9810a8feaa90476afebff2437c3d360511a3f7fa3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare composed_explain_test.cpp: include "crown/io/explain.hpp", "crown/planner/lower.hpp", "crown/api/error.hpp", "tree_oracle.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;cstdlib&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;new&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;tuple&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–21](../../../../../tests/unit/composed_explain_test.cpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Unexpected {};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the test-only exception type for a deliberately non-bad_alloc fault path. |
| inputs / outputs | No fields or inputs; construction identifies Unexpected. |
| invariants | The source’s \`unexpected\` flag is never set by the test paths, so sweeps exercise bad_alloc rather than this exception. |
| ownership | Owns no state. |
| failure | If thrown by fault::check it is not caught as bad_alloc in sweep and is propagated after disarming. |
| cost | Empty exception type. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0003

[Lines 22–22](../../../../../tests/unit/composed_explain_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(){if(armed){if(remaining==0){if(unexpected)throw Unexpected{};throw std::bad_alloc{};}--remaining;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the composed-test allocation fault index to one replacement-new request. |
| inputs / outputs | No explicit input; when armed and remaining is zero it throws Unexpected only if the unused flag is true, otherwise bad_alloc; positive remaining decrements. |
| invariants | In the exercised source paths unexpected remains false, so sweep catches bad_alloc; the seam counts calls, not bytes. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0004

[Lines 23–23](../../../../../tests/unit/composed_explain_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate(std::size_t n){check();if(void* p=std::malloc(n==0?1:n))return p;throw std::bad_alloc{};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate malloc-backed storage for ordinary replacement new. |
| inputs / outputs | Size enters; fault::check runs, then malloc(bytes or 1) returns or null throws bad_alloc. |
| invariants | Only this replacement path and the aligned wrapper call the test fault point. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0005

[Lines 24–24](../../../../../tests/unit/composed_explain_test.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in composed_explain_test.cpp: namespace fault. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 25–25](../../../../../tests/unit/composed_explain_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n){return fault::allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary scalar new through the fault allocator. |
| inputs / outputs | Size enters; malloc-backed pointer or bad_alloc exits. |
| invariants | Fault injection is inactive outside sweep scopes. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0007

[Lines 26–26](../../../../../tests/unit/composed_explain_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n){return fault::allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary array new\[\] through the fault allocator. |
| inputs / outputs | Size enters; malloc-backed pointer or bad_alloc exits. |
| invariants | Array and scalar forms share fault::remaining. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0008

[Lines 27–27](../../../../../tests/unit/composed_explain_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar replacement-new storage. |
| inputs / outputs | Pointer enters; no return value. |
| invariants | Calls free; no fault hook. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0009

[Lines 28–28](../../../../../tests/unit/composed_explain_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array replacement-new storage. |
| inputs / outputs | Pointer enters; no return value. |
| invariants | Calls free; no fault hook. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0010

[Lines 29–29](../../../../../tests/unit/composed_explain_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized scalar delete. |
| inputs / outputs | Pointer and size enter; no return value. |
| invariants | Ignores size and frees pointer. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0011

[Lines 30–30](../../../../../tests/unit/composed_explain_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized array delete. |
| inputs / outputs | Pointer and size enter; no return value. |
| invariants | Ignores size and frees pointer. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0012

[Lines 31–31](../../../../../tests/unit/composed_explain_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n,std::align_val_t a){fault::check();void* p=nullptr;if(posix_memalign(&p,static_cast<std::size_t>(a),n==0?1:n)!=0)throw std::bad_alloc{};return p;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate aligned scalar storage through the composed-test fail-index and posix_memalign. |
| inputs / outputs | Size/alignment enter; fault::check may throw; successful aligned backing returns pointer or posix_memalign failure throws bad_alloc. |
| invariants | Aligned requests participate in the same index as ordinary new; direct posix_memalign calls do not. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0013

[Lines 32–32](../../../../../tests/unit/composed_explain_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n,std::align_val_t a){return ::operator new(n,a);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned array new\[\] through aligned scalar replacement new. |
| inputs / outputs | Size/alignment enter; delegates to ::operator new(size,alignment). |
| invariants | One fault check occurs through the delegated aligned allocation. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0014

[Lines 33–33](../../../../../tests/unit/composed_explain_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::align_val_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide aligned scalar delete. |
| inputs / outputs | Pointer/alignment enter; no return. |
| invariants | Ignores alignment and frees pointer. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0015

[Lines 34–34](../../../../../tests/unit/composed_explain_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::align_val_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide aligned array delete. |
| inputs / outputs | Pointer/alignment enter; no return. |
| invariants | Ignores alignment and frees pointer. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0016

[Lines 35–35](../../../../../tests/unit/composed_explain_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t,std::align_val_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized aligned scalar delete. |
| inputs / outputs | Pointer/size/alignment enter; no return. |
| invariants | Ignores size/alignment and frees pointer. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0017

[Lines 36–36](../../../../../tests/unit/composed_explain_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::size_t,std::align_val_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized aligned array delete. |
| inputs / outputs | Pointer/size/alignment enter; no return. |
| invariants | Ignores size/alignment and frees pointer. |
| ownership | The test owns thread-local injector flags/index; successful requests return malloc-backed storage (aligned requests use posix_memalign) and matching delete frees it. |
| failure | Only ordinary and aligned throwing scalar/array global new paths call fault::check. Direct malloc/realloc/posix_memalign calls and system calls are not faulted; nothrow forms are not replaced. \`unexpected\` is declared but never enabled by these source paths; sweeps catch bad_alloc only. |
| cost | Each injected point counts one replaced C++ allocation call, not bytes/RSS/work/time. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0018

[Lines 37–46](../../../../../tests/unit/composed_explain_test.cpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L46:sha256:8796a6da3aac3e5424c9fc27f9159232cd50f440a22bb672414ff5b1db059210
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare composed_explain_test.cpp: bind local aliases/name imports; require 6 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 47–47](../../../../../tests/unit/composed_explain_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t clocks=0;std::uint64_t clock_tick() noexcept{return ++clocks*10;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide one deterministic fake observation clock tick. |
| inputs / outputs | No input; increments clocks and returns 10 times the new count. |
| invariants | This is an injected clock source; its values do not represent wall-clock nanoseconds. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0020

[Lines 48–48](../../../../../tests/unit/composed_explain_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool x,const char* message){if(!x)throw std::runtime_error(message);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed composed-test predicate into std::runtime_error. |
| inputs / outputs | Boolean and C-string message enter; true returns, false throws. |
| invariants | Does not catch crown::api::Error or allocation errors. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0021

[Lines 49–49](../../../../../tests/unit/composed_explain_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F>void error(F&& f,const char* code=nullptr){bool caught=false;try{f();}catch(const Error& e){caught=true;if(code)check(e.code()==code,"wrong error code");}check(caught,"expected Error");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a crown::api::Error and optionally match its exact code. |
| inputs / outputs | Forwarded action and optional code enter; matching Error returns normally. |
| invariants | Catches only Error; wrong/missing code fails, other exception types propagate. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0022

[Lines 50–51](../../../../../tests/unit/composed_explain_test.cpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L51:sha256:b328d36b645323d46df6c893280cf9e1d881e5d3162637b22bb46e21f17bb4fa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare composed_explain_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 52–52](../../../../../tests/unit/composed_explain_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void write(const std::filesystem::path& p,const std::string& s){std::ofstream o(p,std::ios::binary);o.write(s.data(),static_cast<std::streamsize>(s.size()));check(bool(o),"write artifact");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write one expected or encoded artifact to a binary file path. |
| inputs / outputs | Filesystem path and string are borrowed; opens ofstream, writes full string bytes, then checks stream state. |
| invariants | Failure to write becomes runtime_error; output is a test artifact, not a durable runtime journal or external sink. |
| ownership | Borrows report/native expected string; creates filesystem path and stream for one artifact. File bytes are written from the supplied owning string. |
| failure | Open/write errors fail through check; filesystem and stream exceptions otherwise propagate. These are generated test artifacts, not a durable runtime journal/sink. |
| cost | One file write of the supplied artifact length; no atomicity, durability, or throughput claim. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Encodings and schemas](../../../../observability.md) |

## B0024

[Lines 53–53](../../../../../tests/unit/composed_explain_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row row(std::int64_t n){return {Value{n}};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one-column fixture Row for a result value. |
| inputs / outputs | int64 enters; owning Row with one scalar Value exits. |
| invariants | No runtime storage view escapes. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0025

[Lines 54–61](../../../../../tests/unit/composed_explain_test.cpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the fixed R/S projected-query fixture and produce plans/updates. |
| inputs / outputs | Fixture contains R(x,y), S(y), R(7,9) source; plan() lowers native R/S tree, update(seq) inserts S(9). |
| invariants | The query projects x; after S(9), result is 7; with an extra R(8,9), results are 7 and 8. |
| ownership | Owns catalog/query/tree/database. Each returned lowered plan/update is a value; no runtime is retained. |
| failure | Lowering or row construction errors propagate. |
| cost | One tiny two-table query with one source row. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0026

[Lines 62–62](../../../../../tests/unit/composed_explain_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions opts(ObservationMode mode=ObservationMode::trace){DeltaOptions o;o.view=ResultView::core;o.physical.support.observation={mode,256,1,0,true};o.physical.support.order=PropagationOrder::lifo;o.work_limit=17011;o.physical.work_limit=11003;o.physical.support.work_limit=7103;o.physical.derivation_limit=13007;o.physical.support.support_limit=9209;o.cursor.work_limit=19001;o.epoch_view.work_limit=23003;o.spool_row_limit=251;o.spool_byte_limit=28001;return o;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build fixed nested core-view delta options for composed report fixtures. |
| inputs / outputs | ObservationMode enters; returns core-view options with exact support/physical/delta/cursor/view/spool ceilings. |
| invariants | Options select requested limits only; no claim that work/bytes/time were consumed at those ceilings. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0027

[Lines 63–63](../../../../../tests/unit/composed_explain_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const DeclaredBenchmarkContext> label(std::string value){return std::make_shared<const DeclaredBenchmarkContext>(BenchmarkLabels{std::move(value),"typed-adapter","declared-codec","declared-sink"});}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build shared benchmark labels from one run label. |
| inputs / outputs | Owning string enters; immutable shared context exits with fixed adapter/codec/sink labels. |
| invariants | Declared labels do not claim measured callbacks or durable delivery. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0028

[Lines 64–64](../../../../../tests/unit/composed_explain_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string hex(std::string_view x){if(x.empty())return "-";std::string s;for(char b:x){const auto v=static_cast<unsigned char>(b);s+="0123456789abcdef"[v>>4U];s+="0123456789abcdef"[v&15U];}return s;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hex-encode each byte of a string view for native diagnostics. |
| inputs / outputs | String view enters; lowercase hex string exits, empty maps to \`-\`. |
| invariants | Preserves embedded NUL and invalid UTF-8 bytes exactly. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0029

[Lines 65–65](../../../../../tests/unit/composed_explain_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T>void opt(std::ostream& o,const std::optional<T>& v){if(v)o<<*v;else o<<"null";}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write an optional value or \`null\` to a stream. |
| inputs / outputs | Stream and optional are borrowed; scalar text is emitted. |
| invariants | Formatting helper does not infer a missing identity. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0030

[Lines 66–66](../../../../../tests/unit/composed_explain_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void configuration(std::ostream& o,const char* scope,const std::optional<ObservationConfiguration>& cfg){if(!cfg){o<<"config "<<scope<<" null\n";return;}const auto& c=*cfg;const auto x=c.requested_options();o<<"config "<<scope<<' '<<c.support_owner()<<' '<<c.generation()<<' '<<c.generation_saturated()<<' '<<static_cast<int>(c.mode())<<' '<<static_cast<int>(c.completion())<<' '<<static_cast<int>(c.live_maintenance())<<' '<<static_cast<int>(c.view())<<' '<<c.query_factors()<<' '<<static_cast<int>(x.mode)<<' '<<static_cast<int>(x.completion)<<' '<<static_cast<int>(x.live_maintenance)<<' '<<static_cast<int>(x.view)<<' ';opt(o,x.work_limit);o<<' ';opt(o,x.cursor.work_limit);o<<' ';opt(o,x.epoch_view.work_limit);o<<' '<<x.spool_row_limit<<' '<<x.spool_byte_limit<<' ';opt(o,x.physical.work_limit);o<<' '<<x.physical.derivation_limit<<' ';opt(o,x.physical.support.work_limit);o<<' '<<x.physical.support.support_limit<<' '<<static_cast<int>(x.physical.support.order)<<' '<<x.physical.support.capture_transitions<<' '<<static_cast<int>(x.physical.support.observation.mode)<<' '<<x.physical.support.observation.trace_capacity<<' '<<x.physical.support.observation.sample_period<<' '<<x.physical.support.observation.sample_offset<<' '<<x.physical.support.observation.trace_timings<<'\n';}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize an ObservationConfiguration or literal null with requested nested options. |
| inputs / outputs | Scope, output stream, and optional configuration are borrowed; emits owner/generation/resolution/factor fields and all requested limits/settings. |
| invariants | Current configuration versus attempt-bound config is determined by caller scope string; no values are mutated. |
| ownership | Borrowed report/snapshot/context values are formatted into an owning std::string; temporary streams own their string buffers. |
| failure | Formatting/allocation errors propagate; serializer does not mutate the source report/runtime. |
| cost | Walks the listed metadata/trace/gauge/cursor fields and constructs a textual oracle; output length/CPU are not bounded here. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0031

[Lines 67–67](../../../../../tests/unit/composed_explain_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void declared(std::ostream& o,const char* scope,const std::shared_ptr<const DeclaredBenchmarkContext>& d){o<<"labels "<<scope;if(!d){o<<" null\n";return;}for(const auto* x:{&d->labels().run,&d->labels().input_adapter,&d->labels().output_codec,&d->labels().sink})o<<' '<<(*x?hex(**x):"null");o<<'\n';}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the four declared benchmark labels while retaining missing-versus-empty distinction. |
| inputs / outputs | Scope and shared const declaration are borrowed; emits null record or hex encodings of run/adapter/codec/sink. |
| invariants | Empty string maps to \`-\`; absent maps to \`null\`; encoding is raw-byte hex rather than UTF-8 text. |
| ownership | Borrowed report/snapshot/context values are formatted into an owning std::string; temporary streams own their string buffers. |
| failure | Formatting/allocation errors propagate; serializer does not mutate the source report/runtime. |
| cost | Walks the listed metadata/trace/gauge/cursor fields and constructs a textual oracle; output length/CPU are not bounded here. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0032

[Lines 68–68](../../../../../tests/unit/composed_explain_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto option_tuple(const DeltaOptions& x){const auto& p=x.physical;const auto& a=p.support;const auto& v=a.observation;return std::tuple{x.mode,x.completion,x.live_maintenance,x.view,x.work_limit,x.cursor.work_limit,x.epoch_view.work_limit,x.spool_row_limit,x.spool_byte_limit,p.work_limit,p.derivation_limit,a.work_limit,a.support_limit,a.order,a.capture_transitions,v.mode,v.trace_capacity,v.sample_period,v.sample_offset,v.trace_timings};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract option fields used in native owner/report equality. |
| inputs / outputs | DeltaOptions is borrowed; tuple of scalar, optional and enum settings exits. |
| invariants | Only listed options are compared; no runtime is advanced. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0033

[Lines 69–69](../../../../../tests/unit/composed_explain_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string option_native(const DeltaOptions& x){std::ostringstream o;auto emit=[&](const auto& v){using T=std::decay_t<decltype(v)>;if constexpr(std::is_enum_v<T>)o<<static_cast<int>(v);else if constexpr(requires{v.has_value();})opt(o,v);else o<<v;o<<' ';};std::apply([&](const auto&... values){(emit(values),...);},option_tuple(x));return o.str();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the extracted option tuple to a native diagnostic string. |
| inputs / outputs | DeltaOptions enters by const reference; stream-produced owning string exits. |
| invariants | Enums are numeric; optionals use null/value formatting; no JSON escaping is intended. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0034

[Lines 70–70](../../../../../tests/unit/composed_explain_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void initialization(std::ostream& o,const char* scope,const std::optional<InitializationContext>& c){o<<"init "<<scope;if(!c)o<<" null";else{o<<' '<<static_cast<int>(c->route);if(!c->applied_build)o<<" null";else{o<<' '<<static_cast<int>(c->applied_build->method)<<' ';opt(o,c->applied_build->work_limit);}}o<<'\n';}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize optional initialization route and BuildOptions values. |
| inputs / outputs | Scope and optional InitializationContext are borrowed; writes route/build method/work limit or null. |
| invariants | Does not infer build options for an empty constructor. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0035

[Lines 71–71](../../../../../tests/unit/composed_explain_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string plan_native(const auto& p){std::ostringstream o;o<<"plan "<<static_cast<int>(p.route())<<' ';opt(o,p.validation().native_height);o<<' ';if(p.tree().root)o<<p.tree().root->value;else o<<"null";o<<'\n';for(std::size_t i=0;i<p.tree().nodes.size();++i){const auto& n=p.tree().nodes[i];o<<"tnode "<<i<<' '<<hex(n.id)<<' '<<static_cast<int>(n.kind)<<' ';opt(o,n.occurrence);o<<' '<<n.scope.size();for(auto v:n.scope)o<<' '<<v.value;o<<' '<<n.children.size();for(auto v:n.children)o<<' '<<v.value;o<<' '<<p.validation().separators[i].size();for(auto v:p.validation().separators[i])o<<' '<<v.value;o<<' '<<(std::ranges::find(p.validation().maximal_connex,NodeId{i})!=p.validation().maximal_connex.end())<<'\n';}return o.str();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize compiled-plan route, native height/root, tree nodes, separators, and maximal-connex membership. |
| inputs / outputs | Compiled plan is borrowed; owning diagnostic string exits. |
| invariants | Node IDs are byte-hex encoded; output preserves tree order and validation vectors. |
| ownership | Borrowed report/snapshot/context values are formatted into an owning std::string; temporary streams own their string buffers. |
| failure | Formatting/allocation errors propagate; serializer does not mutate the source report/runtime. |
| cost | Walks the listed metadata/trace/gauge/cursor fields and constructs a textual oracle; output length/CPU are not bounded here. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0036

[Lines 72–72](../../../../../tests/unit/composed_explain_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string session_context_native(const std::shared_ptr<const SessionRunContext>& c){std::ostringstream o;if(!c)return "runfield self null null\n";auto n=[&](const char* k,auto v){o<<"runfield "<<k<<" n "<<v<<'\n';};auto b=[&](const char* k,bool v){o<<"runfield "<<k<<" b "<<v<<'\n';};auto text=[&](const char* k,const std::optional<std::string>& v){o<<"runfield "<<k<<" s "<<(v?hex(*v):"null")<<'\n';};auto optional=[&](const char* k,const auto& v){o<<"runfield "<<k<<" n ";opt(o,v);o<<'\n';};n("input_kind",static_cast<int>(c->input_kind));const auto i=c->input.export_value();n("input_options.format",static_cast<int>(i.format));o<<"runfield input_options.table n ";if(i.table)o<<i.table->value;else o<<"null";o<<'\n';n("input_options.delimiter_byte",static_cast<unsigned>(static_cast<unsigned char>(i.delimiter)));b("input_options.header",i.header);n("input_options.csv_operation",static_cast<int>(i.csv_operation));text("input_options.null_token",i.null_token);text("input_options.source",i.source);n("input_options.byte_offset",i.byte_offset);n("input_options.limits.record_bytes",i.limits.record_bytes);n("input_options.limits.field_bytes",i.limits.field_bytes);n("input_options.limits.columns",i.limits.columns);n("input_options.limits.source_bytes",i.limits.source_bytes);n("input_options.limits.sources",i.limits.sources);optional("input_options.limits.total_bytes",i.limits.total_bytes);optional("input_options.limits.records",i.limits.records);for(const auto& [token,table]:i.relation_tokens)o<<"runtoken "<<hex(token)<<' '<<table.value<<'\n';n("snapshot.rows",c->snapshot.rows);n("snapshot.accounted_bytes",c->snapshot.bytes);optional("snapshot.cursor_work_limit",c->snapshot.cursor.work_limit);if(c->queue){n("queue.batches",c->queue->batches);n("queue.events",c->queue->events);n("queue.accounted_bytes",c->queue->bytes);}if(c->window){n("window.width",c->window->width);n("window.fifo",static_cast<int>(c->window->fifo));n("window.max_labels",c->window->max_labels);n("window.max_accounted_bytes",c->window->max_accounted_bytes);n("window.command_work_limit",c->window->command_work_limit);for(auto id:c->window->managed_tables)o<<"runmanaged "<<id.value<<'\n';}o<<"runoptions "<<option_native(c->requested_delta)<<'\n';n("resolved_mode",static_cast<int>(c->resolved_mode));n("resolved_completion",static_cast<int>(c->resolved_completion));initialization(o,"session",c->initialization);return o.str();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize every immutable SessionRunContext field used by owner equality. |
| inputs / outputs | Shared const context is borrowed; emits input kind/options/limits/tokens, snapshot caps, optional queue/window settings, requested delta options, resolved values, and init route. |
| invariants | Null context has an explicit sentinel; raw string metadata is hex encoded so NUL/invalid UTF-8 are preserved. |
| ownership | Borrowed report/snapshot/context values are formatted into an owning std::string; temporary streams own their string buffers. |
| failure | Formatting/allocation errors propagate; serializer does not mutate the source report/runtime. |
| cost | Walks the listed metadata/trace/gauge/cursor fields and constructs a textual oracle; output length/CPU are not bounded here. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [docs/session_lifecycle.md § Native typed input ownership](../../../../session_lifecycle.md) |

## B0037

[Lines 73–75](../../../../../tests/unit/composed_explain_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string observation_native(const ObservationTrace& t){std::ostringstream o;const auto& s=t.snapshot;o<<session_context_native(s.session_context);initialization(o,"current",s.initialization);configuration(o,"current",s.current_configuration);declared(o,"current",s.current_declared_benchmark);o<<"lifetime "<<s.attempts<<' '<<s.commits<<' '<<s.aborts<<' '<<s.lifetime_counts_saturated<<'\n';
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize observation snapshot, attempt summaries, outputs, lifetime counters, and copied trace records. |
| inputs / outputs | ObservationTrace is borrowed; string output includes context/config/labels, current/last summaries and metric values, disposition flags, trace header and numeric events. |
| invariants | Every trace field is numeric; tuple payloads/string callbacks are not retained by TraceRecord. |
| ownership | Borrowed report/snapshot/context values are formatted into an owning std::string; temporary streams own their string buffers. |
| failure | Formatting/allocation errors propagate; serializer does not mutate the source report/runtime. |
| cost | Walks the listed metadata/trace/gauge/cursor fields and constructs a textual oracle; output length/CPU are not bounded here. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0038

[Lines 76–76](../../../../../tests/unit/composed_explain_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string gauge_native(const auto& g){std::ostringstream o;if(!g){o<<"gauge null\n";return o.str();}o<<"gauge "<<g->owner<<' '<<g->sequence<<' '<<g->base_tuples.value<<' '<<static_cast<int>(g->base_tuples.availability)<<' '<<g->base_tuples.saturated<<'\n';for(const auto& b:g->bases)o<<"base "<<b.table.value<<' '<<b.tuples<<'\n';for(const auto& n:g->nodes)o<<"nodegauge "<<n.node.value<<' '<<static_cast<int>(n.kind)<<' '<<n.records<<' '<<n.survivors<<' '<<n.projected_parent_keys<<' '<<static_cast<int>(n.visible_factor_assignments.availability)<<' '<<n.visible_factor_assignments.value<<'\n';return o.str();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize optional committed-state gauges to a native string. |
| inputs / outputs | Optional gauge capture is borrowed; null sentinel or owner/sequence/base/node counters exit. |
| invariants | Availability and saturation flags are emitted alongside numeric values; no row payloads are serialized. |
| ownership | Borrowed report/snapshot/context values are formatted into an owning std::string; temporary streams own their string buffers. |
| failure | Formatting/allocation errors propagate; serializer does not mutate the source report/runtime. |
| cost | Walks the listed metadata/trace/gauge/cursor fields and constructs a textual oracle; output length/CPU are not bounded here. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md) |

## B0039

[Lines 77–77](../../../../../tests/unit/composed_explain_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string status_native(const SessionStatus& s){std::ostringstream o;o<<"session "<<static_cast<int>(s.state)<<' '<<static_cast<int>(s.phase)<<' '<<s.committed_sequence<<' '<<s.input_failed<<' '<<s.end_of_input<<' ';opt(o,s.pending_sequence);o<<' '<<s.pending_work<<' '<<s.output_remaining<<' ';opt(o,s.pending_command_sequence);o<<'\n';if(s.queue)o<<"queue "<<s.queue->batches<<' '<<s.queue->events<<' '<<s.queue->accounted_bytes<<' '<<s.queue->closed<<' '<<s.queue->failed<<'\n';if(s.window)o<<"window "<<s.window->completed_command_sequence<<' '<<s.window->physical_sequence<<' '<<s.window->completed_watermark<<' '<<s.window->last_label<<' ';if(s.window){opt(o,s.window->active_command_sequence);o<<' '<<s.window->completed_steps<<' '<<s.window->total_steps<<'\n';}return o.str();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize session state/phase/progress plus optional queue/window status. |
| inputs / outputs | SessionStatus is borrowed; one string with session and optional queue/window values exits. |
| invariants | Pending/committed sequences and failure flags are written literally; no mutation occurs. |
| ownership | Borrowed report/snapshot/context values are formatted into an owning std::string; temporary streams own their string buffers. |
| failure | Formatting/allocation errors propagate; serializer does not mutate the source report/runtime. |
| cost | Walks the listed metadata/trace/gauge/cursor fields and constructs a textual oracle; output length/CPU are not bounded here. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0040

[Lines 78–78](../../../../../tests/unit/composed_explain_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cursor_work(std::ostream& o,const char* scope,const CursorWork& w){o<<"cwork "<<scope<<' '<<w.work<<' '<<w.calls<<' '<<w.route_checks<<' '<<w.descriptor_steps<<' '<<w.frame_initializations<<' '<<w.cursor_opens<<' '<<w.cursor_advances<<' '<<w.frame_closes<<' '<<w.tuple_lookups<<' '<<w.selected_rows<<' '<<w.bucket_lookups<<' '<<w.key_fields<<' '<<w.equality_checks<<' '<<w.output_fields<<' '<<w.rows_emitted<<' '<<w.binding_checks<<' '<<w.binding_rejections<<' '<<w.direct_lookups<<' '<<w.overlay_rows<<' '<<w.fragment_steps<<' '<<w.binding_values<<' '<<w.witness_probes<<' '<<w.witness_rows<<' '<<w.join_rejections<<'\n';}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize all named CursorWork counters. |
| inputs / outputs | Scope and CursorWork are borrowed; one textual counter record exits. |
| invariants | Counter values remain work/count fields, not elapsed time or byte totals. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0041

[Lines 79–79](../../../../../tests/unit/composed_explain_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string cursor_native(const std::optional<CursorObservation>& c){std::ostringstream o;if(!c)return "cursor null\n";for(const auto& [name,value]:std::array<std::pair<const char*,const CursorWork*>,5>{{{"startup",&c->mandatory.startup},{"results",&c->mandatory.results},{"termination",&c->mandatory.termination},{"failed",&c->mandatory.failed},{"last",&c->mandatory.last}}})cursor_work(o,name,*value);configuration(o,"cursor",c->configuration);o<<"cursoroptions "<<static_cast<int>(c->view)<<' '<<static_cast<int>(c->options.mode)<<' '<<c->options.trace_capacity<<' '<<c->options.sample_period<<' '<<c->options.sample_offset<<' '<<c->options.trace_timings<<' '<<c->tentative_at_creation<<' ';if(c->side)o<<static_cast<int>(*c->side);else o<<"null";o<<' ';opt(o,c->limits.work_limit);o<<'\n';o<<"cursor "<<c->owner<<' '<<c->sequence<<' '<<c->cursor_id<<' '<<c->cursor_id_saturated<<' '<<c->constructed<<' '<<static_cast<int>(c->source)<<' '<<static_cast<int>(c->state)<<' '<<static_cast<int>(c->terminal_reason)<<' '<<c->mandatory.total_work<<' '<<c->mandatory.max_result_work<<' '<<c->mandatory.cleanup_frames<<'\n';for(std::size_t i=0;i<c->values.size();++i)o<<"cmetric "<<i<<' '<<static_cast<int>(c->values[i].availability)<<' '<<c->values[i].value<<' '<<c->values[i].saturated<<'\n';return o.str();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize optional cursor observation, all phase work records, options, state, and metric values. |
| inputs / outputs | Optional CursorObservation is borrowed; returns null sentinel or native string from cursor_work and fields. |
| invariants | Reports five mandatory work groups and cursor identity/state; numbers are counters/status, not wall-clock or byte estimates. |
| ownership | Borrowed report/snapshot/context values are formatted into an owning std::string; temporary streams own their string buffers. |
| failure | Formatting/allocation errors propagate; serializer does not mutate the source report/runtime. |
| cost | Walks the listed metadata/trace/gauge/cursor fields and constructs a textual oracle; output length/CPU are not bounded here. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0042

[Lines 80–80](../../../../../tests/unit/composed_explain_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string runtime_native(SupportOwnerId id,std::uint64_t sequence,std::optional<DeltaState> state,const DeltaRuntimeProfile& p){std::ostringstream o;o<<"runtimestate "<<id.value<<' '<<sequence<<' ';if(state)o<<static_cast<int>(*state);else o<<"null";o<<' '<<static_cast<int>(p.mode)<<' '<<static_cast<int>(p.completion)<<' '<<static_cast<int>(p.live_maintenance)<<' '<<static_cast<int>(p.view)<<'\n';return o.str();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a DeltaRuntime owner identity/state/profile tuple. |
| inputs / outputs | Owner ID, sequence, optional state and profile are values; one diagnostic line exits. |
| invariants | No owner mutation or live query execution. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0043

[Lines 81–81](../../../../../tests/unit/composed_explain_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string owner_native(const DeltaRuntime& owner){auto s=owner.state();std::optional<CommittedStateGauges> g;if(s==DeltaState::ready||s==DeltaState::committed_output)g=owner.committed_state_gauges();return runtime_native(owner.owner(),owner.sequence(),owner.state(),owner.profile())+plan_native(owner.plan())+observation_native(owner.observation_trace())+gauge_native(g)+cursor_native(owner.last_cursor_observation());}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build native diagnostic facts for a DeltaRuntime owner. |
| inputs / outputs | Runtime borrowed; serializes owner/state/profile, plan, observation trace, committed gauges only in ready/committed_output state, and cursor observation. |
| invariants | For private states gauge output is null; this diagnostic does not mutate the owner. |
| ownership | Borrowed report/snapshot/context values are formatted into an owning std::string; temporary streams own their string buffers. |
| failure | Formatting/allocation errors propagate; serializer does not mutate the source report/runtime. |
| cost | Walks the listed metadata/trace/gauge/cursor fields and constructs a textual oracle; output length/CPU are not bounded here. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0044

[Lines 82–82](../../../../../tests/unit/composed_explain_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string owner_native(const QuerySession& owner){const auto metadata=owner.report_metadata();return runtime_native(metadata.owner(),metadata.sequence(),metadata.state(),metadata.profile())+plan_native(metadata.plan())+observation_native(owner.observation_trace())+gauge_native(owner.report_gauges())+cursor_native(owner.last_cursor_observation())+status_native(owner.status());}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build native diagnostic facts for a QuerySession owner. |
| inputs / outputs | Session borrowed; obtains report metadata and serializes runtime/profile/plan/observation/gauges/cursor/status. |
| invariants | Status and session-attached context are compared with captured report in tests; no input is consumed. |
| ownership | Borrowed report/snapshot/context values are formatted into an owning std::string; temporary streams own their string buffers. |
| failure | Formatting/allocation errors propagate; serializer does not mutate the source report/runtime. |
| cost | Walks the listed metadata/trace/gauge/cursor fields and constructs a textual oracle; output length/CPU are not bounded here. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0045

[Lines 83–83](../../../../../tests/unit/composed_explain_test.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L83:sha256:b4bb7ac77ef0655408b7ec2af1bc60a416a6d0b99a8caa6fe2e1d2ca07521994
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare composed_explain_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0046

[Lines 84–84](../../../../../tests/unit/composed_explain_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boundary(const Report& r,Encoder encode){const auto s=encode(r,{});check(encode(r,{s.size()})==s,"exact encoded cap");error([&]{static_cast<void>(encode(r,{s.size()-1}));},"resource_limit");error([&]{static_cast<void>(encode(r,{0}));},"resource_limit");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact encoded output length is accepted and smaller encoded-byte caps reject. |
| inputs / outputs | Report and encoder function pointer enter; full string is generated, exact size succeeds, size-1 and zero limits must throw resource_limit. |
| invariants | This is an encoded-output byte cap only; it does not bound allocation overhead or report/runtime memory. |
| ownership | PlanExplanation owns an immutable report Data value and shared/captured plan/observation/evidence records. Runtime is borrowed during capture; return is a report value independent of the facade object. |
| failure | The helper expects Error code resource_limit for the short caps; encoder errors outside those cases propagate. |
| cost | Encodes the full report once plus three boundary encodes. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0047

[Lines 85–85](../../../../../tests/unit/composed_explain_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void emit(const char* name,const Report& r,const std::string& native){const auto base=dir/(std::to_string(serial++)+"-"+name);write(base.string()+".expected",native);write(base.string()+".json",io::write_explain_json(r));write(base.string()+".txt",io::write_explain_text(r));write(base.string()+".tree.json",io::write_explain_tree_json(r));write(base.string()+".dot",io::write_explain_dot(r));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write one named report and native-facts artifact set. |
| inputs / outputs | Name, PlanExplanation, and owning native diagnostic string enter; increments serial and writes \`.expected\`, \`.json\`, \`.txt\`, \`.tree.json\`, and \`.dot\` files under dir. |
| invariants | The native file is an oracle image; the other four are renderings. Writes are ordinary test artifacts and do not establish durable runtime delivery. |
| ownership | Borrows report/native expected string; creates filesystem path and stream for one artifact. File bytes are written from the supplied owning string. |
| failure | Open/write errors fail through check; filesystem and stream exceptions otherwise propagate. These are generated test artifacts, not a durable runtime journal/sink. |
| cost | One file write of the supplied artifact length; no atomicity, durability, or throughput claim. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Encodings and schemas](../../../../observability.md), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md) |

## B0048

[Lines 86–86](../../../../../tests/unit/composed_explain_test.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Owner>Report capture(Owner& owner,const char* label_name=nullptr){const auto before=owner_native(owner);const auto tick=clocks;const auto options=[&]{if constexpr(std::is_same_v<Owner,QuerySession>)return owner.report_metadata().options();else return owner.options();}();if constexpr(std::is_same_v<Owner,QuerySession>)check(session_context_native(owner.run_context())==session_context_native(owner.observations().session_context),"session metadata context join differs");const auto config=owner.observations().current_configuration;if(config)check(option_tuple(config->requested_options())==option_tuple(options),"current options reconstruction differs from native owner");auto r=Report::capture(owner);check(r.mode().options()&&option_tuple(*r.mode().options())==option_tuple(options),"captured current options differ from owning runtime");check(clocks==tick,"capture sampled optional clock");check(owner_native(owner)==before,"capture changed native owner facts");check(observation_native(ObservationTrace{*r.observation(),{r.trace_records().begin(),r.trace_records().end()}})==observation_native(owner.observation_trace()),"capture observation copy differs");check(gauge_native(r.gauges())==gauge_native([&]()->std::optional<CommittedStateGauges>{if constexpr(std::is_same_v<Owner,QuerySession>)return owner.report_gauges();else{auto s=owner.state();return s==DeltaState::ready||s==DeltaState::committed_output?std::optional{owner.committed_state_gauges()}:std::nullopt;}}()),"capture gauges differ");check(cursor_native(r.cursor())==cursor_native(owner.last_cursor_observation()),"capture cursor differs");if(label_name)emit(label_name,r,before);return r;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a PlanExplanation from a DeltaRuntime or QuerySession and compare it with current native owner facts. |
| inputs / outputs | Mutable owner and optional label enter; saves owner-native string/clock/options, calls Report::capture, verifies context/options/trace/gauges/cursor equality and no clock/owner change, optionally emits files, returns owning Report. |
| invariants | For session, report metadata context must equal observation context. Captured config/mode and owner facts stay unchanged; \`label_name\` triggers filesystem artifact writes. |
| ownership | Owner is borrowed during synchronous capture; returned PlanExplanation owns an immutable report capture. Its captured mode may share native state independently of the facade lifetime. |
| failure | Capture/render/oracle errors propagate; the helper does not catch product errors. |
| cost | Copies and serializes fixed metadata, trace/gauges/cursor/plan; optional label adds five artifact writes. No timing or total-byte bound. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0049

[Lines 87–87](../../../../../tests/unit/composed_explain_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void metric(const ObservationSummary& s,MetricId id,MetricAvailability a,std::uint64_t v=0){const auto& m=s.metric(id);check(m.availability==a,"metric availability");if(a==MetricAvailability::available)check(m.value==v,"literal hand-count metric");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one observation metric availability and exact literal value. |
| inputs / outputs | ObservationSummary, MetricId, expected availability/value enter; returns or throws. |
| invariants | If availability is not available, the numeric value is not asserted by this helper. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0050

[Lines 88–103](../../../../../tests/unit/composed_explain_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifecycle(){Fixture f;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise PlanExplanation lifecycle across initialization, four observation modes, pending/commit/output, mode generation, trace, callback, and output ownership. |
| inputs / outputs | Builds direct/replay/rebuilt and empty runtimes; in each mode captures pending/paused/draining/prepared/committed states, transfers/discards result, switches modes/labels, checks generation saturation, callbacks, trace truncation/sampling, and encoder caps. |
| invariants | Init routes/build options match exact request and bootstrap does not count user attempts. Pending gauge unavailable; mode switch rejected during pending; historical attempt config/labels stay begin-bound. Off/counters do not read fake clock. Sink failure leaves row retryable; causal trace event IDs and output flags reflect callbacks. Trace cap3 truncates and sample period2 may yield not_sampled. Existing captured reports survive move and owner facade destruction; moved-from access is invalid_explanation. |
| ownership | Each local runtime/Epoch and Report is owned by its case. Old Report values are retained across later mode/label changes, runtime move, and destruction of that runtime facade. Callback row arguments are borrowed for the call. |
| failure | Expected product errors include pending-mode invalid-state and encoder resource_limit; sink callback runtime_error is caught locally and retried. Other mismatches throw test runtime_error. |
| cost | Runs fixed tiny R/S fixtures under four modes. Fake clock is deterministic and not wall time; trace and work/counters are bounded fixture oracles, not performance measurements. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0051

[Lines 104–104](../../../../../tests/unit/composed_explain_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void enqueue(QuerySession& s,PhysicalSetUpdate u){io::TransportBatch batch({io::InputEvent{std::move(u),{}}});check(s.enqueue(batch)==io::Admission::accepted,"typed enqueue");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one typed update into a QuerySession. |
| inputs / outputs | Session and PhysicalSetUpdate enter; wraps update in one TransportBatch and requires Admission::accepted. |
| invariants | Success transfers batch to queue; helper returns void. |
| ownership | Arguments are borrowed or copied by value as declared; returned option/row/value/string images own their contents. |
| failure | Fixture and diagnostic helpers propagate allocation/encoding errors; check converts a false predicate to runtime_error. |
| cost | Fixed small fixture or field conversion; no runtime benchmark. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0052

[Lines 105–108](../../../../../tests/unit/composed_explain_test.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sessions(){Fixture f;SessionOptions o;o.delta=opts();o.declared_benchmark=label("session");o.snapshot.rows=53;o.snapshot.bytes=8192;o.snapshot.cursor.work_limit=1000;auto s=QuerySession::create_typed(f.plan(),f.db,{3,11,8192},o);capture(*s,"session-created");enqueue(*s,f.update());s->start();check(s->begin_next_result()==SessionBegin::pending,"session begin");capture(*s,"session-pending");s->pause();capture(*s,"session-paused");s->start();s->start_drain();capture(*s,"session-draining");while(s->step()!=DeltaStep::prepared){}capture(*s,"session-prepared");s->commit();auto live=capture(*s,"session-committed");const auto frozen=io::write_explain_json(live);const auto trace=live.trace_records();check(!trace.empty(),"session trace absent");auto snap=s->snapshot();check(snap.rows.size()==1&&snap.rows[0].values()==row(7),"session literal result");capture(*s,"session-cursor");s->stop();auto stopped=capture(*s,"session-stopped");check(stopped.gauges().has_value()&&stopped.mode().presence()==observability::RuntimePresence::stopped_retained,"stopped runtime lost gauges");s->drop();auto dropped=capture(*s,"session-dropped");check(!dropped.gauges()&&!dropped.mode().state()&&dropped.trace_records().empty()&&dropped.observation()->trace==TraceDisposition::released,"drop retains runtime/trace");check(io::write_explain_json(live)==frozen&&live.trace_records().size()==trace.size(),"old trace/capture mutated after drop");s.reset();check(io::write_explain_json(live)==frozen,"facade destruction invalidated report");auto moved=std::move(live);error([&]{static_cast<void>(live.plan());},"invalid_explanation");for(const Encoder e:{static_cast<Encoder>(io::write_explain_json),static_cast<Encoder>(io::write_explain_text),static_cast<Encoder>(io::write_explain_dot),static_cast<Encoder>(io::write_explain_tree_json)})boundary(moved,e);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise composed session reports through typed input, pending phases, stop/drop, and window metadata barrier. |
| inputs / outputs | Creates typed session with one queued update, captures created/pending/paused/draining/prepared/committed/cursor/stopped/dropped reports, checks snapshot row7, retains old report across drop/facade destruction/move, and tests four encoder boundaries. Then creates a windowed session with metadata-only watermark command and captures its barriers. |
| invariants | Stopped report retains gauges; dropped report has no gauges/runtime state and released trace. Old serialized report/trace stays unchanged. Private metadata-only window barrier reports delta ready but no gauges; after prepare/commit/drop the phases advance. |
| ownership | Session owns input queue/window and mutable runtime; each Report is an owning capture retained beyond stop/drop/session reset. Output snapshot Row is owning. |
| failure | Only moved-from report access expects invalid_explanation and short encoder caps expect resource_limit; other APIs propagate errors. |
| cost | One typed update and one metadata-only window command; encoded-size exact/short checks; no durable session journal or external sink. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/session_lifecycle.md § O03 typed queues and operational windows (accepted)](../../../../session_lifecycle.md) |

## B0053

[Lines 109–110](../../../../../tests/unit/composed_explain_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void caps(){Fixture f;for(bool heavy:{false,true}){auto fixture=f;if(heavy){fixture.c.tables[1].constraints.push_back(UniqueConstraint{"S_unique",{ColumnId{0}},ConstraintStatus::enforced});for(std::int64_t i=100;i<200;++i)fixture.db.tables[1].insert(row(i));}auto o=opts();o.physical.work_limit=heavy?130:43;auto owner=DeltaRuntime::initialize(fixture.plan(),fixture.db,o);error([&]{static_cast<void>(owner.apply(fixture.update()));},"resource_limit");check(owner.sequence()==0&&!owner.has_answer(),"cap changed committed results");const auto s=owner.observations();check(s.last&&s.last->outcome==ObservationOutcome::aborted,"cap missing abort");metric(*s.last,MetricId::support_work,MetricAvailability::available,40);metric(*s.last,MetricId::physical_work_inclusive,MetricAvailability::unavailable);metric(*s.last,MetricId::physical_work_exclusive,MetricAvailability::unavailable);const auto raw=s.last->metric(MetricId::physical_work_inclusive).value;check(raw==(heavy?107U:4U),"literal raw incomplete coordinator prefix");if(heavy){metric(*s.last,MetricId::physical_constraint_rows,MetricAvailability::available,102);metric(*s.last,MetricId::physical_constraint_validations,MetricAvailability::available,1);}capture(owner,heavy?"cap-heavy107":"cap-small4");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check work-limit abort reporting on small and constraint-heavy R/S inputs. |
| inputs / outputs | Builds small/large S fixtures, applies one S insert with physical work cap 43 or 130, expects resource_limit, checks sequence0/no answer/aborted outcome and literal support/physical partial metrics. |
| invariants | Both support work values are 40; physical inclusive/exclusive availability is unavailable after abort, while raw incomplete prefix value is 4 small or 107 heavy. Heavy case checks 102 constraint rows/one validation. These partial values are not a completed physical-work total. |
| ownership | Each case owns fixture copy and DeltaRuntime; after abort the owner is captured without committing the failed input. |
| failure | Expected product failure is resource_limit; observation stores aborted summary and partial diagnostic counters. |
| cost | Small fixture or 100 added S rows plus one enforced uniqueness constraint; these work counters do not represent CPU time or wall duration. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/physical_runtime.md § Work and resource limits](../../../../physical_runtime.md) |

## B0054

[Lines 111–111](../../../../../tests/unit/composed_explain_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VerifiedOptimum optimum(const Catalog& c,const Query& q){SearchOptions o;o.limits.producer.work.reset();o.limits.replay.work.reset();o.limits.logical_depth.reset();auto s=ExactSearch::create(c,q,o);while(s.progress().result==ResultKind::unfinished){auto a=s.advance({31,{}});check(a.stopped_for==StopReason::quantum_work||a.stopped_for==StopReason::complete,"proof unexpected resource stop");}check(s.optimum().has_value(),"expected genuine optimum");return *s.optimum();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run ExactSearch to a verified optimum in quantum-sized advances for the supplied catalog/query. |
| inputs / outputs | Catalog/query are borrowed; SearchOptions work/depth-like limits are reset, search advances in quantum 31 until complete, and VerifiedOptimum exits. |
| invariants | Each advance must stop for quantum_work or complete; returned handle is genuine optimum for this query binding. This helper does not establish a general theorem or bound search resources. |
| ownership | Proof/candidate/family values and compiled plans own/share immutable evidence; QueryExplanation/PlanExplanation values retain their own copied handles. The test fixture and report values live in authority() scope unless a nested lambda explicitly ends a facade lifetime. |
| failure | Invalid evidence/query bindings must throw the named crown Error; the literal evaluator/tree oracle/search proof mismatch throws runtime_error. This checks fixed fixture authority binding, not a theorem for all plans. |
| cost | Runs exact search in quantum-31 advances and an independent exhaustive tree oracle for the tiny fixture; this is fixture-level proof comparison, not a general performance bound. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md) |

## B0055

[Lines 112–123](../../../../../tests/unit/composed_explain_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void authority(){Fixture f;auto proof=optimum(f.c,f.q);SearchLimits l;l.work_limit.reset();l.recursion_limit.reset();l.literal_scope_limit.reset();const auto independent=reference::exhaustive_minimum_tree(f.c,f.q,l);check(independent.status==OracleStatus::proven_minimum&&independent.minimum_height==proof.height(),"literal proof disagreement");auto p=lower_tree(f.c,f.q,proof.upper().tree());auto upper=Report::create(p,proof.upper());check(!upper.optimum(),"upper minted optimum");emit("typed-upper",upper,plan_native(p)+"literal_height "+std::to_string(*independent.minimum_height)+"\n");const auto nodes=p.tree().nodes.size();static_cast<void>(Report::create(p,proof,{},observability::ExplainLimits{nodes}));error([&]{static_cast<void>(Report::create(p,proof,{},observability::ExplainLimits{nodes-1}));},"resource_limit");auto relabelled_tree=proof.upper().tree();relabelled_tree.nodes[0].id+="-different-label";auto relabelled_plan=lower_tree(f.c,f.q,relabelled_tree);error([&]{static_cast<void>(Report::create(relabelled_plan,proof.upper()));},"explain_upper");check(Report::create(relabelled_plan,proof).optimum().has_value(),"original optimum wrongly restricted to one witness representation");auto minimum=Report::create(p,proof);emit("typed-optimum",minimum,plan_native(p)+"literal_height "+std::to_string(*independent.minimum_height)+"\n");
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check proof/candidate binding and explain rendering across exact fixture, structural negatives, UTF-8, and one facade lifetime. |
| inputs / outputs | Builds verified optimum and independent exhaustive oracle for R/S; checks checked upper vs optimum, node caps, relabeled witness, CandidateProvider family/context/catalog binding, seven metadata/alias/source changes, cyclic false query, empty contradiction, invalid UTF-8 labels, and a captured report returned from a lambda-local runtime. |
| invariants | The tiny independent oracle must report proven_minimum and match exact-search height. Constant-false selected operator height0 has checked_constant_operator status but no optimum; separate nonempty cyclic negative has no tree witness and tree JSON rejects it. Empty original contradiction gets height0 verified proof. Invalid raw bytes fail JSON/text encoding but structural tree/DOT exports work and runtime sequence is unchanged. Report readback occurs after only the lambda-local DeltaRuntime facade is destroyed; proof, CandidateProvider, candidate and family remain in outer authority() scope, so this does not prove their destruction. |
| ownership | VerifiedOptimum, CandidateSnapshot, proof/family handles and reports are value/shared immutable artifacts. In the final lambda the local DeltaRuntime facade ends before returned report access; outer proof/provider/family owners remain alive. Reports retain captured plan/state. |
| failure | Specific authority/limit/text errors are checked by code: resource_limit, explain_upper/candidate/family/binding/context, query_explain_no_witness, and text_encoding. No arbitrary theorem or external P08 corpus is tested by this fixture. |
| cost | Repeated small exact-search quantum steps, one independent exhaustive oracle, several metadata variants and fixed-size report exports; no timing or byte bound. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0056

[Lines 124–124](../../../../../tests/unit/composed_explain_test.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F,class Verify>void sweep(F&& op,Verify&& verify){std::size_t failures=0;for(std::size_t i=0;;++i){bool bad=false;fault::remaining=i;fault::armed=true;try{op();}catch(const std::bad_alloc&){bad=true;}catch(...){fault::armed=false;throw;}fault::armed=false;verify();if(!bad){check(failures>0,"fault sweep did not fail");std::cout<<"sweep allocations="<<i<<'\n';break;}++failures;op();verify();check(i!=std::numeric_limits<std::size_t>::max(),"fault index overflow");}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep one operation over increasing global-new fault positions, verify state, and retry after each failure with injection disabled. |
| inputs / outputs | Forwarded op and verify callbacks enter; each loop arms \`remaining=i\`, catches bad_alloc only, disarms, runs verify, and on failure reruns op then verify before incrementing. |
| invariants | The same runtime/session/report used by the caller remains across all positions and retries; the retry is unfaulted. First successful point requires at least one earlier failure. \`Unexpected\` is not selected by these call sites. |
| ownership | The DeltaRuntime/QuerySession/report are constructed before their sweep and remain the same owners across failure, verify, and the explicit unfaulted retry operation. The sweep creates no replacement owner per fault point. |
| failure | For each index, arms the new seam around op, catches bad_alloc only, disarms before verify, and on a failed point runs op again with injection off. verify compares exact native owner facts/clock and retained report encoding. Non-bad_alloc exceptions disarm then propagate. |
| cost | Increases the replaced allocation-call fault index until first success; no count/byte/RSS/CPU or duration bound is asserted. Operations and oracle serializers may allocate outside the armed scope. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0057

[Lines 125–128](../../../../../tests/unit/composed_explain_test.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void faults(){Fixture f;auto runtime=DeltaRuntime::initialize(f.plan(),f.db,opts());auto e=runtime.apply(f.update());e.discard();auto baseline=owner_native(runtime);auto report=capture(runtime);auto encoded=io::write_explain_json(report);const auto tick=clocks;auto verify=[&]{check(owner_native(runtime)==baseline&&clocks==tick,"persistent fault changed owner/clock");check(io::write_explain_json(report)==encoded,"persistent fault mutated retained report");};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep report capture/read/encoding allocation failures for ready runtime and pending/stopped/dropped session states. |
| inputs / outputs | Creates and commits one runtime update, retains its Report/JSON, then sweeps runtime Report::capture, observation_trace, gauges, four encoders; creates session and sweeps captures pending, stopped, dropped. |
| invariants | After each failure and unfaulted retry, exact owner-native state/clock and frozen report bytes remain unchanged. The sweep does not recreate owner per fault point and does not sweep filesystem writes or product mutation. |
| ownership | The same DeltaRuntime or QuerySession and frozen PlanExplanation live across each helper sweep; each individual capture/string temporary is local. |
| failure | The harness injects only bad_alloc through ordinary/aligned throwing global new forms. Operations are read/capture/encode; no output sink, durable journal or memory-account denial is injected. |
| cost | Each capture/read/encoder is swept until its first successful allocation index; owner snapshots and verify string formatting run outside the armed scope. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0058

[Lines 129–129](../../../../../tests/unit/composed_explain_test.cpp#L129); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L129:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in composed_explain_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0059

[Lines 130–130](../../../../../tests/unit/composed_explain_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){try{check(argc>=2,"usage: composed-test OUTPUT [all|lifecycle|sessions|caps|authority|faults]");dir=argv[1];std::filesystem::create_directories(dir);const std::string group=argc>2?argv[2]:"all";detail::set_observation_clock_for_testing(clock_tick);if(group=="all"||group=="lifecycle")lifecycle();if(group=="all"||group=="sessions")sessions();if(group=="all"||group=="caps")caps();if(group=="all"||group=="authority")authority();if(group=="all"||group=="faults")faults();check(group=="all"||group=="lifecycle"||group=="sessions"||group=="caps"||group=="authority"||group=="faults","unknown group");detail::set_observation_clock_for_testing(nullptr);std::cout<<"PASS "<<group<<" reports="<<serial<<'\n';return 0;}catch(const std::exception& e){fault::armed=false;detail::set_observation_initial_generation_for_testing(0);detail::set_observation_clock_for_testing(nullptr);std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a selected composed-report group, create its output directory, and clear test hooks on exit. |
| inputs / outputs | Requires output directory and optional group in {all,lifecycle,sessions,caps,authority,faults}; installs fake clock and dispatches requested group(s), prints PASS or catches std::exception and returns 1. |
| invariants | Success and failure paths clear the observation clock; failure also disables fault seam and resets initial generation test hook. No run is claimed by this packet. |
| ownership | main owns output path/group strings; group helpers own their test fixtures. |
| failure | Invalid args/group or any scenario error returns 1 after cleanup; this contract describes source flow only. |
| cost | Runs selected report/render groups and may write artifacts; no duration or complete suite execution claim. |
| Design | [tests/unit/composed_explain_test.cpp](../../../../../tests/unit/composed_explain_test.cpp) |
