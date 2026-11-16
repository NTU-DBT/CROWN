# `tests/unit/query_explain_test.cpp` — block usage map

[Source](../../../../../tests/unit/query_explain_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `19c119906a3cd2abf59fcc06ede79868a85f584654033e5c2f7aaf41ba5dd4a2`. 186 lines partitioned into 50 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/query_explain_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 21–21](../../../../../tests/unit/query_explain_test.cpp#L21) | Type/record definition: struct Unexpected |  · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../tests/unit/query_explain_test.cpp#L22) | Callable definition: void check() | calls ; guard void check(){if(armed){if(remaining==0){if(unexpected)throw Unexpected{};throw std::bad_alloc{};}--… · [reviewed contract](#b0003) |
| [B0004 · 23–23](../../../../../tests/unit/query_explain_test.cpp#L23) | Callable definition: void* allocate(std::size_t n) | calls check, std::malloc; guard void* allocate(std::size_t n){check();if(void* p=std::malloc(n==0?1:n))return p;throw std::bad_allo…; returns p; growth allocate, malloc · [reviewed contract](#b0004) |
| [B0005 · 24–24](../../../../../tests/unit/query_explain_test.cpp#L24) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 25–25](../../../../../tests/unit/query_explain_test.cpp#L25) | Callable definition: void* operator new(std::size_t n) | calls fault::allocate; returns fault::allocate(n); growth allocate, new · [reviewed contract](#b0006) |
| [B0007 · 26–26](../../../../../tests/unit/query_explain_test.cpp#L26) | Callable definition: void* operator new\[\](std::size_t n) | calls ; returns fault::allocate(n); growth allocate, new · [reviewed contract](#b0007) |
| [B0008 · 27–27](../../../../../tests/unit/query_explain_test.cpp#L27) | Callable definition: void operator delete(void* p) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 28–28](../../../../../tests/unit/query_explain_test.cpp#L28) | Callable definition: void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 29–29](../../../../../tests/unit/query_explain_test.cpp#L29) | Callable definition: void operator delete(void* p,std::size_t) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 30–30](../../../../../tests/unit/query_explain_test.cpp#L30) | Callable definition: void operator delete\[\](void* p,std::size_t) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 31–31](../../../../../tests/unit/query_explain_test.cpp#L31) | Callable definition: void* operator new(std::size_t n,std::align_val_t a) | calls fault::check, posix_memalign; guard void* operator new(std::size_t n,std::align_val_t a){fault::check();void* p=nullptr;if(posix_memali…; returns p; growth new · [reviewed contract](#b0012) |
| [B0013 · 32–32](../../../../../tests/unit/query_explain_test.cpp#L32) | Callable definition: void* operator new\[\](std::size_t n,std::align_val_t a) | calls ; returns ::operator new(n,a); growth new · [reviewed contract](#b0013) |
| [B0014 · 33–33](../../../../../tests/unit/query_explain_test.cpp#L33) | Callable definition: void operator delete(void* p,std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0014) |
| [B0015 · 34–34](../../../../../tests/unit/query_explain_test.cpp#L34) | Callable definition: void operator delete\[\](void* p,std::align_val_t) noexcept | calls  · [reviewed contract](#b0015) |
| [B0016 · 35–35](../../../../../tests/unit/query_explain_test.cpp#L35) | Callable definition: void operator delete(void* p,std::size_t,std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0016) |
| [B0017 · 36–36](../../../../../tests/unit/query_explain_test.cpp#L36) | Callable definition: void operator delete\[\](void* p,std::size_t,std::align_val_t) noexcept | calls  · [reviewed contract](#b0017) |
| [B0018 · 37–50](../../../../../tests/unit/query_explain_test.cpp#L37) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;Report&gt;); · [reviewed contract](#b0018) |
| [B0019 · 51–51](../../../../../tests/unit/query_explain_test.cpp#L51) | Callable definition: template&lt;class T&gt; concept ReportFrom=requires(T v) | calls  · [reviewed contract](#b0019) |
| [B0020 · 52–52](../../../../../tests/unit/query_explain_test.cpp#L52) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!ReportFrom&lt;SearchProgress&gt; && !ReportFrom&lt;ReplayProgress&gt; && !ReportFrom&lt;HeightCerti… · [reviewed contract](#b0020) |
| [B0021 · 53–53](../../../../../tests/unit/query_explain_test.cpp#L53) | Callable definition: void require(bool value,const char* reason) | calls std::runtime_error; guard void require(bool value,const char* reason){if(!value)throw std::runtime_error(reason);} · [reviewed contract](#b0021) |
| [B0022 · 54–54](../../../../../tests/unit/query_explain_test.cpp#L54) | Callable definition: template&lt;class F&gt; void rejects(F&& f,const char* code=nullptr) | calls f, require, code; guard template&lt;class F&gt; void rejects(F&& f,const char* code=nullptr){bool caught=false;try{f();}catch(con… · [reviewed contract](#b0022) |
| [B0023 · 55–55](../../../../../tests/unit/query_explain_test.cpp#L55) | Callable definition: bool same(const SearchStatistics& a,const SearchStatistics& b) | calls ; returns a.work==b.work&&a.states==b.states&&a.partitions==b.partitions&&a.candidates==b.candidates&&a.cache… · [reviewed contract](#b0023) |
| [B0024 · 56–56](../../../../../tests/unit/query_explain_test.cpp#L56) | Callable definition: bool same(const SearchProgress& a,const SearchProgress& b) | calls ; returns a.phase==b.phase&&a.last_stop==b.last_stop&&a.result==b.result&&a.heights==b.heights&&a.producer_co… · [reviewed contract](#b0024) |
| [B0025 · 57–57](../../../../../tests/unit/query_explain_test.cpp#L57) | Callable definition: bool same(const ReplayProgress& a,const ReplayProgress& b) | calls ; returns a.phase==b.phase&&a.last_stop==b.last_stop&&a.complete==b.complete&&a.valid==b.valid&&a.checked_cla… · [reviewed contract](#b0025) |
| [B0026 · 58–58](../../../../../tests/unit/query_explain_test.cpp#L58) | Callable definition: ContinuationLimits unlimited() | calls reset; returns l · [reviewed contract](#b0026) |
| [B0027 · 59–59](../../../../../tests/unit/query_explain_test.cpp#L59) | Callable definition: ReplayOptions replay_unlimited() | calls reset; returns o · [reviewed contract](#b0027) |
| [B0028 · 60–60](../../../../../tests/unit/query_explain_test.cpp#L60) | Callable definition: SearchOptions options(SearchPolicy policy=SearchPolicy::strict) | calls unlimited; returns o · [reviewed contract](#b0028) |
| [B0029 · 61–61](../../../../../tests/unit/query_explain_test.cpp#L61) | Callable definition: Report capture(const ExactSearch& s) | calls progress, Report::capture, require, same; guard Report capture(const ExactSearch& s){const auto before=s.progress();auto r=Report::capture(s);requi…; returns r · [reviewed contract](#b0029) |
| [B0030 · 62–62](../../../../../tests/unit/query_explain_test.cpp#L62) | Callable definition: Report capture(const CertificateReplay& s) | calls progress, Report::capture, require, same; guard Report capture(const CertificateReplay& s){const auto before=s.progress();auto r=Report::capture(s)…; returns r · [reviewed contract](#b0030) |
| [B0031 · 63–63](../../../../../tests/unit/query_explain_test.cpp#L63) | Callable definition: void no_tree(const Report& r) | calls require, witness, rejects, io::write_query_explain_tree_json; guard void no_tree(const Report& r){require(!r.witness(),"unexpected witness");rejects(\[&\]{static_cast&lt;vo… · [reviewed contract](#b0031) |
| [B0032 · 64–65](../../../../../tests/unit/query_explain_test.cpp#L64) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0032) |
| [B0033 · 66–66](../../../../../tests/unit/query_explain_test.cpp#L66) | Callable definition: void file(const std::filesystem::path& p,const std::string& value) | calls out, write, data, size; guard void file(const std::filesystem::path& p,const std::string& value){std::ofstream out(p,std::ios::bi… · [reviewed contract](#b0033) |
| [B0034 · 67–67](../../../../../tests/unit/query_explain_test.cpp#L67) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0034) |
| [B0035 · 68–68](../../../../../tests/unit/query_explain_test.cpp#L68) | Callable definition: void boundary(const Report& r,Export fn) | calls fn, require, empty, size; guard void boundary(const Report& r,Export fn){const auto text=fn(r,{});require(!text.empty(),"empty expo… · [reviewed contract](#b0035) |
| [B0036 · 69–69](../../../../../tests/unit/query_explain_test.cpp#L69) | Callable definition: std::string hex(std::string_view text) | calls empty; returns out.empty()?@ :out; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 70–70](../../../../../tests/unit/query_explain_test.cpp#L70) | Callable definition: template&lt;class T&gt; void opt(std::ostream& out,const std::optional&lt;T&gt;& x) | calls  · [reviewed contract](#b0037) |
| [B0038 · 71–71](../../../../../tests/unit/query_explain_test.cpp#L71) | Callable definition: template&lt;class Range&gt; void ids(std::ostream& out,const Range& xs) | calls size; 1 loop sites · [reviewed contract](#b0038) |
| [B0039 · 72–75](../../../../../tests/unit/query_explain_test.cpp#L72) | Callable definition: void expected(const Report& r,const std::filesystem::path& path) | calls height_status, source, opt, lower; 3 loop sites · [reviewed contract](#b0039) |
| [B0040 · 76–81](../../../../../tests/unit/query_explain_test.cpp#L76) | Callable definition: void emit(const Report& r,const std::string& label) | calls std::to_string, expected, string, file · [reviewed contract](#b0040) |
| [B0041 · 82–82](../../../../../tests/unit/query_explain_test.cpp#L82) | Callable definition: void complete(ExactSearch& s,std::uint64_t quantum=17) | calls progress, advance, require, capture; guard void complete(ExactSearch& s,std::uint64_t quantum=17){while(s.progress().result==ResultKind::unfin…; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 83–83](../../../../../tests/unit/query_explain_test.cpp#L83) | Callable definition: void complete(CertificateReplay& r,std::uint64_t quantum=13) | calls progress, advance, require, capture; guard void complete(CertificateReplay& r,std::uint64_t quantum=13){while(!r.progress().complete){const au…; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 84–84](../../../../../tests/unit/query_explain_test.cpp#L84) | Callable definition: void terminal_matches(const Report& r,const OracleResult& expected) | calls require, optimum, has_value, lower; guard void terminal_matches(const Report& r,const OracleResult& expected){require(expected.status!=Oracle… · [reviewed contract](#b0043) |
| [B0044 · 85–101](../../../../../tests/unit/query_explain_test.cpp#L85) | Callable definition: void family() | calls fx::finite_three_variable_family, require, size, fx::anchors; guard auto fixtures=fx::finite_three_variable_family();require(fixtures.size()==426,"finite family cardin…; growth push_back; 3 loop sites · [reviewed contract](#b0044) |
| [B0045 · 102–155](../../../../../tests/unit/query_explain_test.cpp#L102) | Callable definition: void states() | calls fx::hypergraph, ExactSearch::create, options, capture; guard for(const auto q:{WorkQuantum{0,{}},WorkQuantum{1,std::chrono::nanoseconds{0}},WorkQuantum{1,std::c…; returns capture(s); growth insert, push_back; 22 loop sites; source comment (unverified): // Positive quantum-time stop is an actual clock boundary; zero quantum was checked separately. · [reviewed contract](#b0045) |
| [B0046 · 156–167](../../../../../tests/unit/query_explain_test.cpp#L156) | Callable definition: void metadata() | calls push_back, std::string, max, Date::parse; guard auto s=ExactSearch::create(c,q,options());auto before=capture(s);complete(s);auto r=capture(s);cons…; growth push_back; 2 loop sites; source comment (unverified): // Raw invalid-byte values and identifiers remain legal native bindings. Each malformed UTF-8 class is rejected only by… · [reviewed contract](#b0046) |
| [B0047 · 168–171](../../../../../tests/unit/query_explain_test.cpp#L168) | Callable definition: template&lt;class F&gt; void sweep(F&& operation) | calls operation, require, max; guard for(std::size_t point=0;;++point){bool failed=false;fault::remaining=point;fault::unexpected=false;…; 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 172–184](../../../../../tests/unit/query_explain_test.cpp#L172) | Callable definition: void faults() | calls fx::hypergraph, ExactSearch::create, options, complete; guard sweep(\[&\]{std::optional&lt;Report&gt; result;result.emplace(Report::capture(owner));});require(same(froze…; growth emplace; 3 loop sites; source comment (unverified): // Every failure stays armed during unwinding and destruction of intermediates. Publication is an optional set only aft… · [reviewed contract](#b0048) |
| [B0049 · 185–185](../../../../../tests/unit/query_explain_test.cpp#L185) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0049) |
| [B0050 · 186–186](../../../../../tests/unit/query_explain_test.cpp#L186) | Callable definition: int main(int argc,char** argv) | calls require, std::filesystem::create_directories, states, metadata; guard int main(int argc,char** argv){try{require(argc&gt;=2,"usage: test OUTPUT_DIR \[states\|metadata\|faults\|…; returns 0; 1 · [reviewed contract](#b0050) |

## B0001

[Lines 1–20](../../../../../tests/unit/query_explain_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:7010b336628124e16d2cdd9ec235ea461917f58de5eec475811b0449c9a96eaf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare query_explain_test.cpp: include "crown/io/query_explain.hpp", "crown/api/error.hpp", "tree_oracle.hpp", "query_families.hpp", &lt;algorithm&gt;, &lt;cstdlib&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;new&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;string&gt;, &lt;type_traits&gt;, &lt;utility&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–21](../../../../../tests/unit/query_explain_test.cpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Unexpected {};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the dedicated non-bad_alloc exception marker for terminal internal-failure tests. |
| inputs / outputs | Declaration: \`struct Unexpected\`. Inputs/outputs in this selected body: Declare the dedicated non-bad_alloc exception marker for terminal internal-failure tests. |
| invariants | The marker has no payload or public CROWN meaning. |
| ownership | Plain local fixture value type; declared containers and scalar values are owned by the record. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Plain fixture data declaration; no runtime work. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0003

[Lines 22–22](../../../../../tests/unit/query_explain_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(){if(armed){if(remaining==0){if(unexpected)throw Unexpected{};throw std::bad_alloc{};}--remaining;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | When armed, fail the next probed replacement-new request; throw Unexpected or bad_alloc according to a thread-local switch. |
| inputs / outputs | Declaration: \`void check()\`. Inputs/outputs in this selected body: When armed, fail the next probed replacement-new request; throw Unexpected or bad_alloc according to a thread-local switch. |
| invariants | Probe state is thread-local; on reaching zero the selected exception is thrown. This is not a runtime API error. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | When armed at zero, throws Unexpected or std::bad_alloc according to the thread-local switch; this helper does not translate either. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0004

[Lines 23–23](../../../../../tests/unit/query_explain_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate(std::size_t n){check();if(void* p=std::malloc(n==0?1:n))return p;throw std::bad_alloc{};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate requested bytes after fault check with malloc, translating null to bad_alloc. |
| inputs / outputs | Declaration: \`void* allocate(std::size_t n)\`. Inputs/outputs in this selected body: Allocate requested bytes after fault check with malloc, translating null to bad_alloc. |
| invariants | The injected failure occurs before malloc; real malloc failure also raises bad_alloc. |
| ownership | Returns malloc-backed raw storage; ownership transfers to the caller, which releases it through the matching replacement delete path. |
| failure | Throws std::bad_alloc before malloc at the selected point or if malloc fails. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0005

[Lines 24–24](../../../../../tests/unit/query_explain_test.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in query_explain_test.cpp: namespace fault. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 25–25](../../../../../tests/unit/query_explain_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n){return fault::allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intercept ordinary scalar throwing global new and route through the fault allocator. |
| inputs / outputs | Declaration: \`void* operator new(std::size_t n)\`. Inputs/outputs in this selected body: Intercept ordinary scalar throwing global new and route through the fault allocator. |
| invariants | Direct ordinary scalar replacement only; no nothrow form is defined. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Direct ordinary/aligned throwing replacement can throw std::bad_alloc at the armed probe point or on backing allocation failure. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0007

[Lines 26–26](../../../../../tests/unit/query_explain_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n){return fault::allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary array throwing global new through the scalar replacement. |
| inputs / outputs | Declaration: \`void* operator new\[\](std::size_t n)\`. Inputs/outputs in this selected body: Route ordinary array throwing global new through the scalar replacement. |
| invariants | Array form delegates through the scalar replacement and its failpoint. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Direct ordinary/aligned throwing replacement can throw std::bad_alloc at the armed probe point or on backing allocation failure. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0008

[Lines 27–27](../../../../../tests/unit/query_explain_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar replacement storage through std::free. |
| inputs / outputs | Declaration: \`void operator delete(void* p) noexcept\`. Inputs/outputs in this selected body: Free scalar replacement storage through std::free. |
| invariants | Null-safe standard delete pairing; no allocation behavior is asserted. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0009

[Lines 28–28](../../../../../tests/unit/query_explain_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array replacement storage through std::free. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* p) noexcept\`. Inputs/outputs in this selected body: Free array replacement storage through std::free. |
| invariants | Array delete is directly defined and frees backing allocation. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0010

[Lines 29–29](../../../../../tests/unit/query_explain_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized scalar replacement storage through std::free. |
| inputs / outputs | Declaration: \`void operator delete(void* p,std::size_t) noexcept\`. Inputs/outputs in this selected body: Free sized scalar replacement storage through std::free. |
| invariants | Sized delete is directly defined and does not count bytes. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0011

[Lines 30–30](../../../../../tests/unit/query_explain_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized array replacement storage through std::free. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* p,std::size_t) noexcept\`. Inputs/outputs in this selected body: Free sized array replacement storage through std::free. |
| invariants | Sized array delete is directly defined and does not extend fault coverage. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0012

[Lines 31–31](../../../../../tests/unit/query_explain_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n,std::align_val_t a){fault::check();void* p=nullptr;if(posix_memalign(&p,static_cast<std::size_t>(a),n==0?1:n)!=0)throw std::bad_alloc{};return p;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intercept aligned scalar throwing global new with fault check and posix_memalign. |
| inputs / outputs | Declaration: \`void* operator new(std::size_t n,std::align_val_t a)\`. Inputs/outputs in this selected body: Intercept aligned scalar throwing global new with fault check and posix_memalign. |
| invariants | Aligned scalar form is directly replaced; injection happens before posix_memalign. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Direct ordinary/aligned throwing replacement can throw std::bad_alloc at the armed probe point or on backing allocation failure. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0013

[Lines 32–32](../../../../../tests/unit/query_explain_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n,std::align_val_t a){return ::operator new(n,a);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned array global new through aligned scalar new. |
| inputs / outputs | Declaration: \`void* operator new\[\](std::size_t n,std::align_val_t a)\`. Inputs/outputs in this selected body: Route aligned array global new through aligned scalar new. |
| invariants | Aligned array requests delegate to aligned scalar replacement. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Direct ordinary/aligned throwing replacement can throw std::bad_alloc at the armed probe point or on backing allocation failure. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0014

[Lines 33–33](../../../../../tests/unit/query_explain_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::align_val_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free aligned scalar storage through std::free. |
| inputs / outputs | Declaration: \`void operator delete(void* p,std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Free aligned scalar storage through std::free. |
| invariants | Aligned deallocation form only; no allocator-system guarantee. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0015

[Lines 34–34](../../../../../tests/unit/query_explain_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::align_val_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free aligned array storage through std::free. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* p,std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Free aligned array storage through std::free. |
| invariants | Aligned array delete frees through directly defined function. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0016

[Lines 35–35](../../../../../tests/unit/query_explain_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t,std::align_val_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized aligned scalar storage through std::free. |
| inputs / outputs | Declaration: \`void operator delete(void* p,std::size_t,std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Free sized aligned scalar storage through std::free. |
| invariants | Sized aligned scalar deallocation only. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0017

[Lines 36–36](../../../../../tests/unit/query_explain_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::size_t,std::align_val_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized aligned array storage through std::free. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* p,std::size_t,std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Free sized aligned array storage through std::free. |
| invariants | Sized aligned array deallocation only. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0018

[Lines 37–50](../../../../../tests/unit/query_explain_test.cpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L50:sha256:9427648eb986cf785dafed1c971c2374d37cc63043916d5dd4b40b62dab63e09
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare query_explain_test.cpp: bind local aliases/name imports; require 7 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 51–51](../../../../../tests/unit/query_explain_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> concept ReportFrom=requires(T v){Report::from(v);};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | At compile time, detect whether Report::from accepts a given type. |
| inputs / outputs | Declaration: \`template&lt;class T&gt; concept ReportFrom=requires(T v)\`. Inputs/outputs in this selected body: At compile time, detect whether Report::from accepts a given type. |
| invariants | Compile-time requires expression only; no runtime construction or proof conversion occurs. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0020

[Lines 52–52](../../../../../tests/unit/query_explain_test.cpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L52:sha256:955245408794ef72502730cc627634d83bafbdaba741e2b57d3818891a758c20
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare query_explain_test.cpp: require 1 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 53–53](../../../../../tests/unit/query_explain_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value,const char* reason){if(!value)throw std::runtime_error(reason);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a query-explain fixture assertion with runtime_error. |
| inputs / outputs | Declaration: \`void require(bool value,const char* reason)\`. Inputs/outputs in this selected body: Fail a query-explain fixture assertion with runtime_error. |
| invariants | False condition throws std::runtime_error. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | A failed fixture assertion raises std::runtime_error; no production error translation. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0022

[Lines 54–54](../../../../../tests/unit/query_explain_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void rejects(F&& f,const char* code=nullptr){bool caught=false;try{f();}catch(const Error& e){caught=true;if(code)require(e.code()==code,"wrong rejection code");}require(caught,"expected rejection");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one action to throw crown::api::Error and optionally match its code. |
| inputs / outputs | Declaration: \`template&lt;class F&gt; void rejects(F&& f,const char* code=nullptr)\`. Inputs/outputs in this selected body: Require one action to throw crown::api::Error and optionally match its code. |
| invariants | Catches only Error; no throw/wrong code fails; other exceptions propagate. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0023

[Lines 55–55](../../../../../tests/unit/query_explain_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same(const SearchStatistics& a,const SearchStatistics& b){return a.work==b.work&&a.states==b.states&&a.partitions==b.partitions&&a.candidates==b.candidates&&a.cache_hits==b.cache_hits&&a.certificate_work==b.certificate_work&&a.hierarchy_tests==b.hierarchy_tests&&a.hierarchy_hits==b.hierarchy_hits&&a.singleton_hits==b.singleton_hits&&a.empty_body_hits==b.empty_body_hits&&a.component_splits==b.component_splits&&a.symmetry_skips==b.symmetry_skips&&a.bound_prunes==b.bound_prunes;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all exposed SearchStatistics fields. |
| inputs / outputs | Declaration: \`bool same(const SearchStatistics& a,const SearchStatistics& b)\`. Inputs/outputs in this selected body: Compare all exposed SearchStatistics fields. |
| invariants | Fieldwise equality is limited to the struct’s public counters. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0024

[Lines 56–56](../../../../../tests/unit/query_explain_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same(const SearchProgress& a,const SearchProgress& b){return a.phase==b.phase&&a.last_stop==b.last_stop&&a.result==b.result&&a.heights==b.heights&&a.producer_complete==b.producer_complete&&a.proof_complete==b.proof_complete&&a.producer==b.producer&&a.replay==b.replay&&same(a.structural,b.structural)&&a.limit_revision==b.limit_revision;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact-search phase/result/heights, producer/replay state, structural counters and limit revision. |
| inputs / outputs | Declaration: \`bool same(const SearchProgress& a,const SearchProgress& b)\`. Inputs/outputs in this selected body: Compare exact-search phase/result/heights, producer/replay state, structural counters and limit revision. |
| invariants | Equality is over exposed state; it does not compare hidden search frames. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0025

[Lines 57–57](../../../../../tests/unit/query_explain_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same(const ReplayProgress& a,const ReplayProgress& b){return a.phase==b.phase&&a.last_stop==b.last_stop&&a.complete==b.complete&&a.valid==b.valid&&a.checked_claims==b.checked_claims&&a.work==b.work&&a.limit_revision==b.limit_revision;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare replay state, checked claims, work and revision. |
| inputs / outputs | Declaration: \`bool same(const ReplayProgress& a,const ReplayProgress& b)\`. Inputs/outputs in this selected body: Compare replay state, checked claims, work and revision. |
| invariants | Equality is over exposed replay progress; no certificate correctness follows from equality alone. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0026

[Lines 58–58](../../../../../tests/unit/query_explain_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ContinuationLimits unlimited(){ContinuationLimits l;l.producer.work.reset();l.replay.work.reset();l.logical_depth.reset();return l;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return producer/replay/depth limits reset to unbounded. |
| inputs / outputs | Declaration: \`ContinuationLimits unlimited()\`. Inputs/outputs in this selected body: Return producer/replay/depth limits reset to unbounded. |
| invariants | Unbounded owner limits do not disable explicit per-call quantum yields. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0027

[Lines 59–59](../../../../../tests/unit/query_explain_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReplayOptions replay_unlimited(){ReplayOptions o;o.limits.work.reset();o.logical_depth.reset();return o;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return CertificateReplay options with work and depth limits reset. |
| inputs / outputs | Declaration: \`ReplayOptions replay_unlimited()\`. Inputs/outputs in this selected body: Return CertificateReplay options with work and depth limits reset. |
| invariants | Unbounded replay limits still permit per-call quanta. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0028

[Lines 60–60](../../../../../tests/unit/query_explain_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchOptions options(SearchPolicy policy=SearchPolicy::strict){SearchOptions o;o.policy=policy;o.limits=unlimited();return o;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return SearchOptions for one strict/best-found policy using unlimited limits. |
| inputs / outputs | Declaration: \`SearchOptions options(SearchPolicy policy=SearchPolicy::strict)\`. Inputs/outputs in this selected body: Return SearchOptions for one strict/best-found policy using unlimited limits. |
| invariants | Policy choice affects whether an unpublished incumbent is exposed; it does not alter the original-query exactness requirement. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0029

[Lines 61–61](../../../../../tests/unit/query_explain_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Report capture(const ExactSearch& s){const auto before=s.progress();auto r=Report::capture(s);require(same(before,s.progress()),"capture advanced search");require(same(before,*r.search_progress()),"search progress copy mismatch");require(&r.binding().catalog()==&s.binding().catalog(),"binding catalog identity lost");require(&r.binding().query()==&s.binding().query(),"binding query identity lost");return r;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a report from ExactSearch without advancing it and preserve the search binding identity. |
| inputs / outputs | Declaration: \`Report capture(const ExactSearch& s)\`. Inputs/outputs in this selected body: Capture a report from ExactSearch without advancing it and preserve the search binding identity. |
| invariants | Capture copies public progress and retains typed evidence without advancing; SearchBinding shares the search owner’s immutable catalog/query identity. |
| ownership | Search is borrowed; returned QueryExplanation owns copied progress and typed evidence handles while sharing immutable binding identity. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0030

[Lines 62–62](../../../../../tests/unit/query_explain_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Report capture(const CertificateReplay& s){const auto before=s.progress();auto r=Report::capture(s);require(same(before,s.progress()),"capture advanced replay");require(same(before,*r.replay_progress()),"replay progress copy mismatch");return r;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a report from CertificateReplay without advancing it and preserve replay progress. |
| inputs / outputs | Declaration: \`Report capture(const CertificateReplay& s)\`. Inputs/outputs in this selected body: Capture a report from CertificateReplay without advancing it and preserve replay progress. |
| invariants | Capture does not advance replay; report owns copied progress/proof artifacts. |
| ownership | Replay is borrowed; returned QueryExplanation owns copied replay progress and typed evidence handles. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0031

[Lines 63–63](../../../../../tests/unit/query_explain_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void no_tree(const Report& r){require(!r.witness(),"unexpected witness");rejects([&]{static_cast<void>(io::write_query_explain_tree_json(r));},"query_explain_no_witness");rejects([&]{static_cast<void>(io::write_query_explain_dot(r));},"query_explain_no_witness");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require no witness and assert tree JSON/DOT exports return query_explain_no_witness. |
| inputs / outputs | Declaration: \`void no_tree(const Report& r)\`. Inputs/outputs in this selected body: Require no witness and assert tree JSON/DOT exports return query_explain_no_witness. |
| invariants | Absence is not an empty tree; only a typed checked upper witness can be tree-exported. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0032

[Lines 64–65](../../../../../tests/unit/query_explain_test.cpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L65:sha256:2a4c5512ab82398996e5915376f08bd3b1e86b052ca578c1ac59e5d7159fa4ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare query_explain_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0033

[Lines 66–66](../../../../../tests/unit/query_explain_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void file(const std::filesystem::path& p,const std::string& value){std::ofstream out(p,std::ios::binary);out.write(value.data(),static_cast<std::streamsize>(value.size()));require(static_cast<bool>(out),"write corpus");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write the supplied bytes to one corpus-side path using binary output. |
| inputs / outputs | Declaration: \`void file(const std::filesystem::path& p,const std::string& value)\`. Inputs/outputs in this selected body: Write the supplied bytes to one corpus-side path using binary output. |
| invariants | Binary stream output writes exactly supplied corpus bytes; filesystem errors are caught by caller. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0034

[Lines 67–67](../../../../../tests/unit/query_explain_test.cpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L67:sha256:bca70ecb473ef461c58ffad7c91d0a910793e8841537bbdf12894498bde958dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare query_explain_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0035

[Lines 68–68](../../../../../tests/unit/query_explain_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boundary(const Report& r,Export fn){const auto text=fn(r,{});require(!text.empty(),"empty export");require(fn(r,{text.size()})==text,"exact output boundary rejected");rejects([&]{static_cast<void>(fn(r,{text.size()-1}));},"resource_limit");rejects([&]{static_cast<void>(fn(r,{0}));},"resource_limit");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check text exporter output limits at exact byte length, one byte below and zero. |
| inputs / outputs | Declaration: \`void boundary(const Report& r,Export fn)\`. Inputs/outputs in this selected body: Check text exporter output limits at exact byte length, one byte below and zero. |
| invariants | Exact output length is accepted; shorter limits reject with resource_limit, including zero. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0036

[Lines 69–69](../../../../../tests/unit/query_explain_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string hex(std::string_view text){std::string out;constexpr char digits[]="0123456789abcdef";for(char c:text){auto v=static_cast<unsigned char>(c);out+=digits[v>>4U];out+=digits[v&15U];}return out.empty()?"-":out;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hex-encode raw bytes, returning dash for empty input. |
| inputs / outputs | Declaration: \`std::string hex(std::string_view text)\`. Inputs/outputs in this selected body: Hex-encode raw bytes, returning dash for empty input. |
| invariants | Encodes raw bytes as two lowercase hex digits each; not UTF-8 validation. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0037

[Lines 70–70](../../../../../tests/unit/query_explain_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void opt(std::ostream& out,const std::optional<T>& x){if(x)out<<*x;else out<<"null";}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write an optional value or null token to a stream. |
| inputs / outputs | Declaration: \`template&lt;class T&gt; void opt(std::ostream& out,const std::optional&lt;T&gt;& x)\`. Inputs/outputs in this selected body: Write an optional value or null token to a stream. |
| invariants | Optional absence prints the literal null token. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0038

[Lines 71–71](../../../../../tests/unit/query_explain_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> void ids(std::ostream& out,const Range& xs){out<<xs.size();for(auto x:xs)out<<' '<<x.value;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write a count and numeric values for a range of strong IDs. |
| inputs / outputs | Declaration: \`template&lt;class Range&gt; void ids(std::ostream& out,const Range& xs)\`. Inputs/outputs in this selected body: Write a count and numeric values for a range of strong IDs. |
| invariants | IDs are exported by \`.value\`, preserving range order. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0039

[Lines 72–75](../../../../../tests/unit/query_explain_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expected(const Report& r,const std::filesystem::path& path){std::ostringstream out;out<<"status "<<static_cast<int>(r.height_status())<<" source "<<static_cast<int>(r.source())<<" lower ";opt(out,r.lower());out<<" upper ";opt(out,r.upper());out<<'\n';
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate expected serialization facts for report status/source/bounds, witness/certificate and work counters. |
| inputs / outputs | Declaration: \`void expected(const Report& r,const std::filesystem::path& path)\`. Inputs/outputs in this selected body: Generate expected serialization facts for report status/source/bounds, witness/certificate and work counters. |
| invariants | Expected record is a separately constructed corpus oracle; external checker performs byte comparison. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0040

[Lines 76–81](../../../../../tests/unit/query_explain_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void emit(const Report& r,const std::string& label){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit expected, JSON, text, tree JSON and DOT outputs under a unique test label; reject witness exports when there is no witness. |
| inputs / outputs | Declaration: \`void emit(const Report& r,const std::string& label)\`. Inputs/outputs in this selected body: Emit expected, JSON, text, tree JSON and DOT outputs under a unique test label; reject witness exports when there is no witness. |
| invariants | JSON/text and typed witness tree/DOT outputs are distinct; no-witness cases explicitly reject witness formats. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0041

[Lines 82–82](../../../../../tests/unit/query_explain_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void complete(ExactSearch& s,std::uint64_t quantum=17){while(s.progress().result==ResultKind::unfinished){const auto a=s.advance({quantum,{}});require(a.stopped_for==StopReason::quantum_work||a.stopped_for==StopReason::complete,"unexpected search resource/failure outcome");auto r=capture(s);require(!r.optimum()||r.search_progress()->proof_complete,"premature optimum");}require(s.progress().phase==SearchPhase::complete,"search did not complete");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance ExactSearch in bounded quanta to terminal completion and assert no optimum precedes proof completion. |
| inputs / outputs | Declaration: \`void complete(ExactSearch& s,std::uint64_t quantum=17)\`. Inputs/outputs in this selected body: Advance ExactSearch in bounded quanta to terminal completion and assert no optimum precedes proof completion. |
| invariants | Accepts only quantum_work/complete, captures between steps, and rejects optimum before proof_complete. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0042

[Lines 83–83](../../../../../tests/unit/query_explain_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void complete(CertificateReplay& r,std::uint64_t quantum=13){while(!r.progress().complete){const auto a=r.advance({quantum,{}});require(a.stopped_for==StopReason::quantum_work||a.stopped_for==StopReason::complete,"unexpected replay resource/failure outcome");static_cast<void>(capture(r));}require(r.progress().valid&&r.checked().has_value(),"valid certificate did not replay");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance CertificateReplay in bounded quanta and require a valid checked certificate at completion. |
| inputs / outputs | Declaration: \`void complete(CertificateReplay& r,std::uint64_t quantum=13)\`. Inputs/outputs in this selected body: Advance CertificateReplay in bounded quanta and require a valid checked certificate at completion. |
| invariants | Accepts only quantum_work/complete and requires final checked authority. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0043

[Lines 84–84](../../../../../tests/unit/query_explain_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void terminal_matches(const Report& r,const OracleResult& expected){require(expected.status!=OracleStatus::resource_limit,"reference resource result is NOT an accepted skip");if(expected.status==OracleStatus::proven_minimum){require(r.optimum().has_value(),"reference positive disagreement");require(r.lower()==expected.minimum_height&&r.upper()==expected.minimum_height,"independent literal height mismatch");require(r.witness()->height()==*expected.minimum_height,"witness height mismatch");}else{require(r.infeasibility().has_value(),"reference negative disagreement");require(!r.lower()&&!r.upper()&&!r.witness(),"negative minted witness/bounds");}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare report authority/bounds to independent exhaustive oracle result; a reference resource-limit status is a failure. |
| inputs / outputs | Declaration: \`void terminal_matches(const Report& r,const OracleResult& expected)\`. Inputs/outputs in this selected body: Compare report authority/bounds to independent exhaustive oracle result; a reference resource-limit status is a failure. |
| invariants | Only the finite supported oracle cases are compared; a resource-limit oracle is not accepted as a skip. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0044

[Lines 85–101](../../../../../tests/unit/query_explain_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void family(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run 426 finite three-variable fixtures plus 11 anchor fixtures under both policies and replay each certificate against the oracle. |
| inputs / outputs | Declaration: \`void family()\`. Inputs/outputs in this selected body: Run 426 finite three-variable fixtures plus 11 anchor fixtures under both policies and replay each certificate against the oracle. |
| invariants | 437 finite cases per policy; P03 exhaustive oracle and fixture family bound are not generalized to all input sizes. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | 437 finite fixtures under both policies with certificate replay; no general scaling claim. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0045

[Lines 102–155](../../../../../tests/unit/query_explain_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void states(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise admitted/preprocess/search/upper-only/proof-publication/resource-limit/cancel/move/lifetime states for search and replay. |
| inputs / outputs | Declaration: \`void states()\`. Inputs/outputs in this selected body: Exercise admitted/preprocess/search/upper-only/proof-publication/resource-limit/cancel/move/lifetime states for search and replay. |
| invariants | Strict hides upper witness before proof completion; best_found may expose only checked upper authority; cancellation/movement must preserve already-owned report values. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Finite state-transition matrix, not wall-clock work. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0046

[Lines 156–167](../../../../../tests/unit/query_explain_test.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void metadata(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check metadata binding with NUL/escaped values, exact scalar types, malformed UTF-8 transport failures and report immutability. |
| inputs / outputs | Declaration: \`void metadata()\`. Inputs/outputs in this selected body: Check metadata binding with NUL/escaped values, exact scalar types, malformed UTF-8 transport failures and report immutability. |
| invariants | Native admission accepts byte strings; only explicitly tested text encoders reject malformed UTF-8. DOT success in the raw-byte case is not generalized to all malformed fields. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | One metadata fixture plus six malformed-byte classes. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0047

[Lines 168–171](../../../../../tests/unit/query_explain_test.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void sweep(F&& operation){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep replacement-new failure points: operation runs armed through unwinding, then retries unarmed after each bad_alloc. |
| inputs / outputs | Declaration: \`template&lt;class F&gt; void sweep(F&& operation)\`. Inputs/outputs in this selected body: Sweep replacement-new failure points: operation runs armed through unwinding, then retries unarmed after each bad_alloc. |
| invariants | Directly defined ordinary and aligned global throwing-new forms are fail-injected; no nothrow replacement, direct malloc/account/systemcall seam or unknown delegation claim. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Catches bad_alloc for the retry sweep and disarms before retry; other exceptions disarm then propagate. |
| cost | Repeats the supplied operation at successive observed allocation points until success. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0048

[Lines 172–184](../../../../../tests/unit/query_explain_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void faults(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise report capture/export failures, same-owner search/replay recovery, Unexpected terminal failure, and raw-byte capture/encoding. |
| inputs / outputs | Declaration: \`void faults()\`. Inputs/outputs in this selected body: Exercise report capture/export failures, same-owner search/replay recovery, Unexpected terminal failure, and raw-byte capture/encoding. |
| invariants | bad_alloc remains retryable on same ExactSearch/CertificateReplay owner; Unexpected is terminal failed state. Export/capture acts on saved reports and is retried unarmed. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | bad_alloc continuation is retryable on the same search/replay owner; Unexpected produces terminal internal_failure. No direct malloc/account/systemcall failure is injected. |
| cost | Finite report/search/replay/raw-byte fault cases; no broad resource-account claim. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |

## B0049

[Lines 185–185](../../../../../tests/unit/query_explain_test.cpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L185:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in query_explain_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0050

[Lines 186–186](../../../../../tests/unit/query_explain_test.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){try{require(argc>=2,"usage: test OUTPUT_DIR [states|metadata|faults|family|all]");destination=argv[1];std::filesystem::create_directories(destination);const std::string group=argc>2?argv[2]:"all";if(group=="all"||group=="states")states();if(group=="all"||group=="metadata")metadata();if(group=="all"||group=="faults")faults();if(group=="all"||group=="family")family();require(group=="all"||group=="states"||group=="metadata"||group=="faults"||group=="family","unknown group");std::cout<<"PASS "<<group<<" reports="<<serial<<'\n';return 0;}catch(const std::exception& e){fault::armed=false;std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}catch(...){fault::armed=false;std::cerr<<"FAIL: unexpected exception\n";return 2;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch selected states/metadata/faults/family corpus groups, catch ordinary/unknown exceptions and return status. |
| inputs / outputs | Declaration: \`int main(int argc,char** argv)\`. Inputs/outputs in this selected body: Dispatch selected states/metadata/faults/family corpus groups, catch ordinary/unknown exceptions and return status. |
| invariants | Writes test artifacts under argv destination; no compilation or execution result is claimed by this card. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | The driver catches documented exceptions, prints a diagnostic and returns a nonzero status. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [src/observability/query_explain.cpp](../../../../../src/observability/query_explain.cpp), [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/observability.md § Height, cost, and proof scope](../../../../observability.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/verification/o07-query-explain-test-proposal/README.md § What the executable requires](../../../../verification/o07-query-explain-test-proposal/README.md) |
