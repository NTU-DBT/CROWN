// Single-thread update/enumeration benchmark for one lowered plan on one engine.
//
//   crown_kernel_bench WORKLOAD ENGINE N MODE
//     WORKLOAD  qh     Q(x,y,z)   :- R(x,y), S(x,z)
//               line3  Q(a,b,c,d) :- R(a,b), S(b,c), T(c,d)
//               star   Q(x,a,b,c) :- R(x,a), S(x,b), T(x,c)
//     ENGINE    ref | idx   DeltaRuntime on the reference / indexed storage backend
//               cmp         compact kernel (crown/runtime/compact.hpp)
//     N         rows loaded round-robin over the relations (about four rows per join key)
//     MODE      delta       every update drains its signed result delta
//               maint       state maintenance only
//
// It reports load time per insert, accounted bytes and live allocations per
// stored tuple, then a FIFO churn (erase the oldest row, insert a fresh one;
// CHURN=<count> overrides its length) with time, accounted allocations and
// operator-new calls per update, and finally a full enumeration. Rows are
// generated before any timed loop. Global operator new is replaced only to
// count calls. Numbers are for comparing engines on one machine in one build.
#include "crown/planner/lower.hpp"
#include "crown/planner/oracle.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/compact.hpp"
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <cstdlib>
#include <iostream>
#include <new>
#include <optional>
#include <random>
#include <set>
#include <string>
#include <vector>
static std::uint64_t g_new = 0;
void* operator new(std::size_t n) { ++g_new; if (void* p = std::malloc(n ? n : 1)) return p; throw std::bad_alloc(); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }
using namespace crown; using namespace crown::runtime;
using Clock = std::chrono::steady_clock;
static double ns_since(Clock::time_point a) { return std::chrono::duration<double, std::nano>(Clock::now() - a).count(); }
static Column col(const char* n) { return Column{n, ScalarType::int64}; }
static Table tab(const char* n, std::initializer_list<const char*> cs) { Table t; t.name = n; for (auto c : cs) t.columns.push_back(col(c)); return t; }
static Variable var(const char* n) { return Variable{n, ScalarType::int64}; }
int main(int argc, char** argv) {
  if (argc < 5) { std::cerr << "usage: crown_kernel_bench WORKLOAD(qh|line3|star) ENGINE(ref|idx|cmp) N MODE(delta|maint)\n"; return 2; }
  const std::string w = argv[1], backend = argv[2], mode = argv[4]; const std::size_t N = std::stoull(argv[3]);
  Catalog catalog; Query query;
  if (w == "qh") {
    catalog = Catalog{1, {tab("R", {"x", "y"}), tab("S", {"x", "z"})}};
    query.variables = {var("x"), var("y"), var("z")};
    query.atoms = {{"R", TableId{0}, {VariableId{0}, VariableId{1}}}, {"S", TableId{1}, {VariableId{0}, VariableId{2}}}};
    query.head = {{VariableId{0}, "x"}, {VariableId{1}, "y"}, {VariableId{2}, "z"}};
  } else if (w == "line3") {
    catalog = Catalog{1, {tab("R", {"a", "b"}), tab("S", {"b", "c"}), tab("T", {"c", "d"})}};
    query.variables = {var("a"), var("b"), var("c"), var("d")};
    query.atoms = {{"R", TableId{0}, {VariableId{0}, VariableId{1}}}, {"S", TableId{1}, {VariableId{1}, VariableId{2}}}, {"T", TableId{2}, {VariableId{2}, VariableId{3}}}};
    query.head = {{VariableId{0}, "a"}, {VariableId{1}, "b"}, {VariableId{2}, "c"}, {VariableId{3}, "d"}};
  } else if (w == "star") {
    catalog = Catalog{1, {tab("R", {"x", "a"}), tab("S", {"x", "b"}), tab("T", {"x", "c"})}};
    query.variables = {var("x"), var("a"), var("b"), var("c")};
    query.atoms = {{"R", TableId{0}, {VariableId{0}, VariableId{1}}}, {"S", TableId{1}, {VariableId{0}, VariableId{2}}}, {"T", TableId{2}, {VariableId{0}, VariableId{3}}}};
    query.head = {{VariableId{0}, "x"}, {VariableId{1}, "a"}, {VariableId{2}, "b"}, {VariableId{3}, "c"}};
  } else { std::cerr << "bad workload\n"; return 2; }
  const auto tree = planner::minimum_tree(catalog, query);
  if (!tree.tree) { std::cerr << "no tree\n"; return 1; }
  PhysicalOptions popts;
  if (backend == "idx") { const std::size_t big = 64'000'000; const std::uint64_t W = 1'000'000'000'000ULL;
    popts.indexed_storage = storage::IndexedBackendSpec{{big, 64, big, big, big, big, big, big, big}, {W, W, W, W, W}}; }
  DeltaOptions opt; opt.mode = mode == "delta" ? DeltaMode::delta : DeltaMode::maintenance;
  opt.work_limit = std::nullopt; opt.physical.work_limit = std::nullopt; opt.physical.support.work_limit = std::nullopt;
  opt.physical.support.memory_limit_bytes = 40ULL << 30; opt.physical.support.observation.mode = ObservationMode::off;
  opt.cursor.work_limit = std::nullopt; opt.spool_row_limit = 1ULL << 40; opt.spool_byte_limit = 1ULL << 40;
  const bool compact_engine = backend == "cmp";
  auto plan = planner::lower_tree(catalog, query, *tree.tree, popts);
  std::optional<DeltaRuntime> full; std::optional<compact::Runtime> fast;
  if (compact_engine) fast.emplace(plan); else full.emplace(plan, opt);
  struct Counter final : compact::RowSink { std::uint64_t rows = 0; std::uint64_t sum = 0; void row(const compact::Word* w) override { ++rows; if (w) sum += w[0]; } } counter;
  auto stats = [&] { return compact_engine ? fast->memory_statistics() : full->accounted_memory_statistics(); };
  const auto m0 = stats();
  std::mt19937_64 rng(1); const std::size_t T = catalog.tables.size();
  const std::int64_t keys = std::max<std::int64_t>(1, static_cast<std::int64_t>(N / 4));
  std::uniform_int_distribution<std::int64_t> k(0, keys - 1), big(0, 1'000'000'000);
  auto gen = [&](std::size_t t) {
    if (w != "line3") return Row{Value{k(rng)}, Value{big(rng)}};
    if (t == 0) return Row{Value{big(rng)}, Value{k(rng)}};
    if (t == 1) return Row{Value{k(rng)}, Value{k(rng)}};
    return Row{Value{k(rng)}, Value{big(rng)}};
  };
  // Pre-generate distinct rows so the timed loops contain engine calls only.
  const std::size_t K = std::getenv("CHURN") ? std::stoull(std::getenv("CHURN")) : std::max<std::size_t>(1000, N / 4);
  std::vector<std::vector<Row>> rows_for(T); { std::vector<std::set<Row>> seen(T);
    for (std::size_t i = 0; i < N + K + T; ++i) { const auto t = i % T; Row r = gen(t); if (seen[t].insert(r).second) rows_for[t].push_back(std::move(r)); } }
  std::vector<std::size_t> head(T, 0), tail(T, 0);
  std::uint64_t seq = 0, out = 0;
  auto apply = [&](std::size_t t, SetOperation op, const Row& row) {
    if (compact_engine) { fast->apply(TableId{t}, op, row, mode == "delta" ? &counter : nullptr); return; }
    auto e = full->apply(PhysicalSetUpdate{++seq, TableId{t}, op, row}); while (e.next()) ++out; };
  std::size_t stored = 0; const std::size_t per = N / T;
  auto t0 = Clock::now();
  for (std::size_t i = 0; i < per; ++i) for (std::size_t t = 0; t < T; ++t) { if (tail[t] + K / T + 1 >= rows_for[t].size()) continue; apply(t, SetOperation::insert, rows_for[t][tail[t]++]); ++stored; }
  const double load_ns = ns_since(t0) / static_cast<double>(stored);
  const auto m1 = stats();
  // FIFO churn: delete the oldest row of a relation, then insert a fresh one.
  double del_ns = 0, ins_ns = 0; std::uint64_t del_acct = 0, ins_acct = 0, del_new = 0, ins_new = 0; std::size_t dels = 0, inss = 0;
  for (std::size_t i = 0; i < K; ++i) {
    const auto t = i % T; if (head[t] >= tail[t] || tail[t] >= rows_for[t].size()) continue;
    const Row& old = rows_for[t][head[t]++];
    auto a0 = stats().successful_allocations; auto n0 = g_new; auto c0 = Clock::now();
    apply(t, SetOperation::erase, old); del_ns += ns_since(c0);
    del_acct += stats().successful_allocations - a0; del_new += g_new - n0; ++dels;
    const Row& r = rows_for[t][tail[t]++];
    a0 = stats().successful_allocations; n0 = g_new; c0 = Clock::now();
    apply(t, SetOperation::insert, r); ins_ns += ns_since(c0);
    ins_acct += stats().successful_allocations - a0; ins_new += g_new - n0; ++inss;
  }
  out += counter.rows; counter.rows = 0;
  double enum_ns = 0; std::uint64_t rows = 0; { auto e0 = Clock::now();
    if (compact_engine) { fast->enumerate(counter); rows = counter.rows; }
    else { auto cursor = full->results(ResultCursorOptions{std::nullopt}); while (auto r = cursor.next()) ++rows; }
    enum_ns = ns_since(e0); }
  std::printf("%-5s %-3s %-5s N=%zu | load %.0f ns/ins | %.0f B/tuple, %.1f live allocs/tuple | churn: ins %.0f ns (%.1f acct allocs, %.1f new) del %.0f ns (%.1f acct allocs, %.1f new) | enum %llu rows %.0f ns/row\n",
      w.c_str(), backend.c_str(), mode.c_str(), stored, load_ns,
      double(m1.current.requested_bytes - m0.current.requested_bytes) / double(stored), double(m1.current.allocations - m0.current.allocations) / double(stored),
      ins_ns / double(std::max<std::size_t>(1, inss)), double(ins_acct) / double(std::max<std::size_t>(1, inss)), double(ins_new) / double(std::max<std::size_t>(1, inss)),
      del_ns / double(std::max<std::size_t>(1, dels)), double(del_acct) / double(std::max<std::size_t>(1, dels)), double(del_new) / double(std::max<std::size_t>(1, dels)),
      (unsigned long long)rows, rows ? enum_ns / double(rows) : 0.0);
}
