#include <crown/api/error.hpp>
#include <crown/frontend/admission.hpp>
#include <crown/io/catalog.hpp>
#include <crown/io/document.hpp>
#include <crown/planner/lower.hpp>
#include <crown/planner/oracle.hpp>
#include <crown/runtime/queries.hpp>
#include <array>
#include <fstream>
#include <iostream>

namespace {
using namespace crown;

std::string read(const char* path) {
  std::ifstream input(path,std::ios::binary);
  if (!input) throw Error("io_error","cannot open query/catalog document");
  std::string result; char block[4096];
  while (input) {
    input.read(block,sizeof(block));
    const auto count = static_cast<std::size_t>(input.gcount());
    if (count > 16U*1024U*1024U-result.size())
      throw Error("resource_limit","example document exceeds16MiB");
    result.append(block,count);
  }
  if (input.bad()) throw Error("io_error","query/catalog read failed");
  return result;
}

runtime::QuerySession::Owner create(const Catalog& catalog,const char* sql,const char* events) {
  const auto admitted = frontend::admit_sql(read(sql),catalog);
  if (admitted.status != frontend::AdmissionStatus::admitted)
    throw Error("sql_rejected","query is outside admitted set SQL");
  auto tree = FreeConnexTree{};
  if (admitted.route != frontend::AdmissionRoute::constant_empty) {
    const auto minimum = planner::minimum_tree(admitted.program->core_catalog,admitted.program->core);
    if (minimum.status != planner::OracleStatus::proven_minimum || !minimum.tree)
      throw Error("resource_limit","query minimum height was not proved");
    tree = *minimum.tree;
  }
  auto input = std::make_unique<std::ifstream>(events,std::ios::binary);
  if (!*input) throw Error("io_error","cannot open independent input stream");
  return runtime::QuerySession::create(planner::lower_normalized(*admitted.program,tree),std::move(input));
}

// Explicit serial execution uses the ordinary per-session API. The directory
// performs no update dispatch, input fan-out or scheduling inside this loop.
io::Json run(runtime::QuerySession& session) {
  session.start();
  while (session.begin_next()) {
    while (session.step() != runtime::DeltaStep::prepared) {}
    session.commit();
    while (session.next_output()) {}
  }
  const auto snapshot = session.snapshot(); auto rows = io::Json::array();
  for (const auto& tuple : snapshot.rows) {
    auto row = io::Json::array();
    for (const auto& value : tuple.values()) row.push_back(io::write_scalar_view(value));
    rows.push_back(std::move(row));
  }
  return {{"sequence",snapshot.sequence},{"rows",std::move(rows)},
          {"account_owner",session.accounted_memory_statistics()->owner}};
}
} // namespace

int main(int argc,char** argv) {
  try {
    if (argc != 6) throw crown::Error("usage","CATALOG.json QUERY_A.sql INPUT_A.jsonl QUERY_B.sql INPUT_B.jsonl");
    const auto catalog = crown::io::read_catalog(read(argv[1]));
    auto first = create(catalog,argv[2],argv[3]),second = create(catalog,argv[4],argv[5]);
    crown::runtime::IndependentQueries queries;
    const std::array ids{queries.admit(first),queries.admit(second)};
    auto results = crown::io::Json::array();
    for (const auto id : ids) results.push_back(run(queries.at(id)));
    const auto bytes = queries.directory_memory().current.requested_bytes;
    for (const auto id : ids) queries.erase(id);
    std::cout << crown::io::Json{{"queries",std::move(results)},{"directory_requested_bytes",bytes},
        {"remaining_queries",queries.size()},{"execution","independent_serial_v1"}}.dump() << '\n';
    std::cout.flush(); return std::cout ? 0 : 1;
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
