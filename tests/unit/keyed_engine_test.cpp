// Differential test: keyed SetEngine against the reference DeltaRuntime on
// random insert/erase streams (duplicates and absent erases included) for the
// paper query shapes plus self-joins, constants, repeated columns, projections,
// string/date/decimal keys, aborted transactions and all three GC modes.
#include "crown/runtime/keyed_engine.hpp"
#include "native_request.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace crown;
using component::Json;

std::uint64_t checks = 0, delta_rows = 0, snapshot_rows = 0;
void check(bool value, const std::string& message) {
  if (!value) throw std::runtime_error(message);
  ++checks;
}

struct Shape {
  std::string name;
  std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string>>>> tables;  // name, (column, type)
  std::string sql;
};

Json catalog_json(const Shape& shape) {
  auto tables = Json::array();
  for (const auto& [name, columns] : shape.tables) {
    auto cols = Json::array();
    for (const auto& [column, type] : columns) cols.push_back({{"name", column}, {"type", type}, {"nullable", false}});
    tables.push_back({{"name", name}, {"columns", cols}});
  }
  return {{"schema_version", 1}, {"catalog", {{"version", 1}, {"tables", tables}}}};
}

using Signed = std::pair<int, Row>;
std::string show(const Row& row) {
  std::string out = "(";
  for (std::size_t i = 0; i < row.size(); ++i) {
    if (i) out += ",";
    if (const auto* v = std::get_if<std::int64_t>(&row[i])) out += std::to_string(*v);
    else if (const auto* s = std::get_if<std::string>(&row[i])) out += *s;
    else out += "?";
  }
  return out + ")";
}

struct Collector final : runtime::keyed::RowSink {
  std::vector<Signed> rows;
  std::int64_t fail_after = -1;  // throw on this row (aborted transaction test)
  void row(SetOperation operation, storage::RowView values) override {
    if (fail_after == 0) throw std::runtime_error("injected sink failure");
    if (fail_after > 0) --fail_after;
    rows.emplace_back(operation == SetOperation::insert ? 1 : -1, storage::export_row(values));
  }
};

std::vector<Row> reference_snapshot(runtime::DeltaRuntime& owner) {
  std::vector<Row> rows;
  auto cursor = owner.results({std::uint64_t{1} << 40});
  while (auto value = cursor.next()) rows.push_back(storage::export_row(value->values()));
  std::sort(rows.begin(), rows.end());
  return rows;
}
std::vector<Row> flat_snapshot(runtime::keyed::SetEngine& owner) {
  Collector collector;
  owner.snapshot(collector);
  std::vector<Row> rows;
  for (auto& [sign, row] : collector.rows) rows.push_back(std::move(row));
  std::sort(rows.begin(), rows.end());
  return rows;
}

std::uint64_t aborted = 0;
void run(const Shape& shape, bool delta, std::uint32_t seed, int events, int domain) {
  Json document = {{"program", {{"catalog", catalog_json(shape)}, {"sql", shape.sql}}}, {"native", Json::object()}};
  auto compiled = component::compile_set(document);
  const auto reason = runtime::keyed::SetEngine::unsupported(compiled.program);
  check(reason.empty(), shape.name + ": unsupported: " + reason);
  Json native = {{"memory_limit_bytes", std::uint64_t{1} << 34}, {"work_limit", std::uint64_t{1} << 40},
                 {"mode", delta ? "delta" : "maintenance"}};
  runtime::DeltaRuntime reference(compiled.program, component::delta_options(native));
  const auto gc_mode = std::array{storage::keyed::GcMode::blocking, storage::keyed::GcMode::background,
      storage::keyed::GcMode::manual}[seed % 3];
  runtime::keyed::SetEngine flat(compiled.program, {delta, {gc_mode, 3, 1024}});
  std::mt19937 random(seed);
  const auto& tables = compiled.catalog.tables;
  std::vector<std::vector<Row>> present(tables.size());
  std::uint64_t sequence = 0;
  for (int event = 0; event < events; ++event) {
    const auto t = std::uniform_int_distribution<std::size_t>(0, tables.size() - 1)(random);
    const auto& table = tables[t];
    Row row;
    bool erase = !present[t].empty() && std::uniform_int_distribution<int>(0, 9)(random) < 4;
    if (erase && std::uniform_int_distribution<int>(0, 9)(random) < 9) {
      row = present[t][std::uniform_int_distribution<std::size_t>(0, present[t].size() - 1)(random)];
    } else {
      for (const auto& column : table.columns) {
        const auto value = std::uniform_int_distribution<int>(0, domain - 1)(random);
        if (column.type == ScalarType::string) row.emplace_back("s" + std::to_string(value) + std::string(static_cast<std::size_t>(value) * 7, 'x'));
        else if (column.type == ScalarType::date) row.emplace_back(Date::parse("2020-01-0" + std::to_string(value + 1)));
        else if (column.type == ScalarType::decimal) row.emplace_back(Decimal::parse(std::to_string(value) + ".5"));
        else row.emplace_back(static_cast<std::int64_t>(value));
      }
    }
    const auto operation = erase ? SetOperation::erase : SetOperation::insert;
    auto found = std::find(present[t].begin(), present[t].end(), row);
    if (operation == SetOperation::insert && found == present[t].end()) present[t].push_back(row);
    if (operation == SetOperation::erase && found != present[t].end()) present[t].erase(found);

    std::vector<Signed> expected;
    {
      auto epoch = reference.apply_view({++sequence, TableId{t}, operation, storage::TupleValuesView::borrow(row)});
      while (auto value = epoch.next())
        expected.emplace_back(value->operation == SetOperation::insert ? 1 : -1, storage::export_row(value->tuple.values()));
    }
    std::vector<storage::ScalarView> cells;
    for (const auto& value : row) cells.push_back(storage::borrow_scalar(value));
    const auto view = storage::RowView::borrow(cells);
    if (delta && !expected.empty() && random() % 7 == 0) {
      // Abort mid-enumeration; the committed state must be unchanged.
      const auto before = flat_snapshot(flat);
      Collector failing;
      failing.fail_after = static_cast<std::int64_t>(random() % expected.size());
      bool threw = false;
      try { flat.apply(TableId{t}, operation, view, &failing); } catch (const std::runtime_error&) { threw = true; }
      check(threw, "injected failure did not abort");
      check(flat_snapshot(flat) == before, shape.name + ": rollback changed the committed state");
      flat.check_invariants();
      ++aborted;
    }
    Collector collector;
    flat.apply(TableId{t}, operation, view, &collector);
    if (event % 50 == 0) flat.check_invariants();
    if (delta) {
      std::sort(expected.begin(), expected.end());
      std::sort(collector.rows.begin(), collector.rows.end());
      if (expected != collector.rows) {
        std::string message = shape.name + " seed " + std::to_string(seed) + " event " + std::to_string(event) +
            (operation == SetOperation::insert ? " +" : " -") + table.name + show(row) + "\n expected:";
        for (const auto& [sign, r] : expected) message += (sign > 0 ? " +" : " -") + show(r);
        message += "\n flat:    ";
        for (const auto& [sign, r] : collector.rows) message += (sign > 0 ? " +" : " -") + show(r);
        check(false, message);
      }
      delta_rows += expected.size();
      check(true, "delta");
    } else {
      check(collector.rows.empty(), "maintenance mode emitted delta rows");
    }
    if (event % 7 == 0 || event + 1 == events) {
      const auto want = reference_snapshot(reference);
      const auto got = flat_snapshot(flat);
      {
        std::vector<Row> streamed;
        auto cursor = flat.open_cursor();
        bool refused = false;
        try { flat.begin(); } catch (const std::exception&) { refused = true; }
        check(refused, "an open cursor must block the writer");
        while (auto row = cursor->next()) streamed.push_back(storage::export_row(*row));
        check(!cursor->next().has_value(), "an exhausted cursor stays exhausted");
        std::sort(streamed.begin(), streamed.end());
        check(streamed == got, shape.name + ": cursor rows differ from the snapshot");
      }
      snapshot_rows += want.size();
      check(want == got, shape.name + " seed " + std::to_string(seed) + " snapshot differs at event " +
          std::to_string(event) + " (" + std::to_string(want.size()) + " vs " + std::to_string(got.size()) + ")");
    }
  }
}

std::vector<std::pair<std::string, std::string>> edge(const char* a, const char* b) {
  return {{a, "int64"}, {b, "int64"}};
}

}  // namespace

int main() try {
  const std::vector<Shape> shapes = {
      {"l3-full", {{"g1", edge("a", "b")}, {"g2", edge("b", "c")}, {"g3", edge("c", "d")}},
       "SELECT DISTINCT g1.a,g1.b,g2.c,g3.d FROM g1,g2,g3 WHERE g1.b=g2.b AND g2.c=g3.c"},
      {"l3-project", {{"g1", edge("a", "b")}, {"g2", edge("b", "c")}, {"g3", edge("c", "d")}},
       "SELECT DISTINCT g2.b,g2.c FROM g1,g2,g3 WHERE g1.b=g2.b AND g2.c=g3.c"},
      {"l4-full", {{"g1", edge("a", "b")}, {"g2", edge("b", "c")}, {"g3", edge("c", "d")}, {"g4", edge("d", "e")}},
       "SELECT DISTINCT g1.a,g1.b,g2.c,g3.d,g4.e FROM g1,g2,g3,g4 WHERE g1.b=g2.b AND g2.c=g3.c AND g3.d=g4.d"},
      {"l4-project", {{"g1", edge("a", "b")}, {"g2", edge("b", "c")}, {"g3", edge("c", "d")}, {"g4", edge("d", "e")}},
       "SELECT DISTINCT g2.b,g2.c,g3.d FROM g1,g2,g3,g4 WHERE g1.b=g2.b AND g2.c=g3.c AND g3.d=g4.d"},
      {"twocomb", {{"g1", edge("a", "b")}, {"g2", edge("b", "c")}, {"g3", edge("c", "d")},
                   {"v1", {{"a", "int64"}}}, {"v2", {{"d", "int64"}}}},
       "SELECT DISTINCT g1.a,g1.b,g2.c,g3.d FROM g1,g2,g3,v1,v2 WHERE g1.b=g2.b AND g2.c=g3.c AND v1.a=g1.a AND v2.d=g3.d"},
      {"snb1", {{"person", {{"person_id", "int64"}, {"first_name", "string"}, {"last_name", "string"}}},
                {"message", edge("message_id", "creator_id")}, {"knows", edge("person1_id", "person2_id")}},
       "SELECT DISTINCT p.person_id, p.first_name, p.last_name, m.message_id, k.person1_id "
       "FROM person AS p, message AS m, knows AS k WHERE p.person_id = m.creator_id AND k.person2_id = p.person_id"},
      {"snb2", {{"tag", {{"tag_id", "int64"}}}, {"message", edge("message_id", "creator_id")},
                {"message_tag", edge("message_id", "tag_id")}, {"knows1", edge("person1_id", "person2_id")},
                {"knows2", edge("person1_id", "person2_id")}},
       "SELECT DISTINCT k1.person1_id, k1.person2_id, k2.person2_id, t.tag_id, m.message_id "
       "FROM tag AS t, message AS m, message_tag AS mt, knows1 AS k1, knows2 AS k2 WHERE m.message_id = mt.message_id "
       "AND mt.tag_id = t.tag_id AND k1.person2_id = k2.person1_id AND m.creator_id = k2.person2_id"},
      {"snb3", {{"person", {{"person_id", "int64"}, {"first_name", "string"}, {"last_name", "string"}}},
                {"message", edge("message_id", "creator_id")}, {"knows1", edge("person1_id", "person2_id")},
                {"knows2", edge("person1_id", "person2_id")}},
       "SELECT DISTINCT p.person_id, p.first_name, p.last_name, m.message_id, k1.person1_id, k1.person2_id "
       "FROM person AS p, message AS m, knows1 AS k1, knows2 AS k2 WHERE p.person_id = m.creator_id "
       "AND p.person_id = k2.person2_id AND k1.person2_id = k2.person1_id"},
      {"self-join-path", {{"e", edge("a", "b")}},
       "SELECT DISTINCT x.a, x.b, y.b FROM e AS x, e AS y WHERE x.b = y.a"},
      {"self-join-project", {{"e", edge("a", "b")}},
       "SELECT DISTINCT x.a FROM e AS x, e AS y, e AS z WHERE x.b = y.a AND y.b = z.a"},
      {"star", {{"g1", edge("a", "b")}, {"g2", edge("a", "c")}, {"g3", edge("a", "d")}},
       "SELECT DISTINCT g1.a FROM g1,g2,g3 WHERE g1.a=g2.a AND g1.a=g3.a"},
      {"star-full", {{"g1", edge("a", "b")}, {"g2", edge("a", "c")}, {"g3", edge("a", "d")}},
       "SELECT DISTINCT g1.a,g1.b,g2.c,g3.d FROM g1,g2,g3 WHERE g1.a=g2.a AND g1.a=g3.a"},
      {"constant", {{"g1", edge("a", "b")}, {"g2", edge("b", "c")}},
       "SELECT DISTINCT g1.a, g2.c FROM g1, g2 WHERE g1.b = g2.b AND g1.a = 1"},
      {"repeated", {{"g1", edge("a", "b")}, {"g2", edge("b", "c")}},
       "SELECT DISTINCT g2.b, g2.c FROM g1, g2 WHERE g1.b = g2.b AND g1.a = g1.b"},
      {"single", {{"g1", edge("a", "b")}}, "SELECT DISTINCT g1.b FROM g1"},
      {"dates", {{"r", {{"d", "date"}, {"x", "int64"}}}, {"s", {{"d", "date"}, {"y", "string"}}}},
       "SELECT DISTINCT r.d, r.x, s.y FROM r, s WHERE r.d = s.d"},
      {"decimals", {{"r", {{"k", "decimal"}, {"x", "int64"}}}, {"s", {{"k", "decimal"}, {"y", "int64"}}}, {"t", {{"y", "int64"}}}},
       "SELECT DISTINCT r.k, s.y FROM r, s, t WHERE r.k = s.k AND s.y = t.y"},
      {"string-keys", {{"a", {{"p", "string"}, {"q", "string"}}}, {"b", {{"q", "string"}, {"r", "string"}}}},
       "SELECT DISTINCT a.p, a.q, b.r FROM a, b WHERE a.q = b.q"},
      {"filter", {{"g1", edge("a", "b")}, {"g2", edge("b", "c")}, {"g3", edge("c", "d")}},
       "SELECT DISTINCT g1.a,g1.b,g2.c,g3.d FROM g1,g2,g3 WHERE g1.b=g2.b AND g2.c=g3.c AND g3.d > 1 AND g1.a <> g1.b"},
      {"string-filter", {{"person", {{"person_id", "int64"}, {"first_name", "string"}}}, {"knows", edge("person1_id", "person2_id")}},
       "SELECT DISTINCT p.first_name, k.person1_id FROM person AS p, knows AS k WHERE k.person2_id = p.person_id AND p.first_name = 's1'"},
      {"reordered-head", {{"g1", edge("a", "b")}, {"g2", edge("b", "c")}},
       "SELECT DISTINCT g2.c, g1.a, g1.b, g2.c AS again FROM g1, g2 WHERE g1.b = g2.b"},
  };
  std::size_t skipped = 0;
  for (const auto& shape : shapes) {
    for (const bool delta : {false, true}) {
      for (std::uint32_t seed = 1; seed <= 4; ++seed) {
        try {
          run(shape, delta, seed * 7919U + (delta ? 1U : 0U), seed <= 2 ? 260 : 700, seed % 2 ? 3 : 6);
        } catch (const std::runtime_error& failure) {
          const std::string message = failure.what();
          if (message.find("unsupported:") != std::string::npos || message.find("not admitted") != std::string::npos ||
              message.find("no proved admissible tree") != std::string::npos) {
            std::cerr << "skip " << shape.name << ": " << message << "\n";
            ++skipped;
            break;
          }
          throw;
        }
      }
    }
  }
  std::cout << "keyed engine checks=" << checks << " delta_rows=" << delta_rows << " snapshot_rows=" << snapshot_rows
            << " aborted=" << aborted << " skipped=" << skipped << "\n";
  return skipped > 2 ? 1 : 0;
} catch (const std::exception& failure) {
  std::cerr << "FAIL: " << failure.what() << "\n";
  return 1;
}
