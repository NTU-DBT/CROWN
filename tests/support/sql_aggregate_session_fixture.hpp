#pragma once

#include "crown/recovery/sql_aggregate_session.hpp"
#include "sql_aggregate_file_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include <iomanip>
#include <sstream>

namespace crown::sql_aggregate_session_test {
namespace ar=recovery::sql_aggregate;
using Cell=runtime::sql_rows::Cell;
using sql_aggregate_file_test::Directory;
using sql_aggregate_file_test::contents;
using sql_aggregate_file_test::put;
using sql_aggregate_file_test::number;
using sql_aggregate_file_test::refused;
using sql_aggregate_file_test::reseal;
inline Cell text(std::string_view value) { return storage::ScalarView{value}; }
inline Catalog schema() { return {1,{{"r",{{"g",ScalarType::string,true},{"x",ScalarType::int64,true}}}}}; }
// Genuine SQL/compiler metadata is test setup. Mutable native state is created
// only inside Session factories, so a receiving session has no shadow database.
struct Fixture {
  Directory directory;
  std::string root=directory.file("query.root"),sink=directory.file("groups.sink");
  resource::MemoryAccount account=resource::MemoryAccount::create(128ULL*1024*1024);
  frontend::SqlAggregateProgram program;
  FreeConnexTree tree;
  PhysicalOptions physical;
  runtime::sql_aggregate::Options normal;
  ar::SessionLimits limits;
  ar::SessionIdentity identity;
  explicit Fixture(bool indexed=false,Catalog catalog=schema(),std::string_view sql="SELECT g,COUNT(*),SUM(x) FROM r GROUP BY g") {
    auto result=frontend::bind_sql_aggregate_into(account,sql,catalog);assert(std::holds_alternative<frontend::SqlAggregateProgram>(result));
    program=std::get<frontend::SqlAggregateProgram>(std::move(result));
    if(!program.source_program().contradiction()) {
      const auto core=program.source_program().export_core();const auto selected=planner::minimum_tree(core.catalog,core.query);assert(selected.tree);tree=*selected.tree;
    }
    if(indexed) {physical=s04_runtime::options();limits.rebuild.source.indexed_work=storage::IndexWork{100000000,100000000,256ULL*1024*1024,100000000,100000000};}
    normal.capture_changes=true;identity.query_id.fill('1');identity.sink_id.fill('2');
  }
  [[nodiscard]] ar::Session create() { return ar::Session::create_into(account,{root,sink},identity,program,tree,physical,normal,limits); }
  [[nodiscard]] ar::Session recover() { return ar::Session::recover_into(account,{root,sink},identity.query_id,limits); }
};
inline std::string generation_file(const Fixture& f,std::uint64_t generation,std::string_view suffix=".wal") {
  std::ostringstream out;out<<f.root<<".g"<<std::hex<<std::setw(16)<<std::setfill('0')<<generation<<suffix;return out.str();
}
// Split only known complete fixture frames. This helper neither validates nor
// authorizes imported state; hostile mutations use production recovery afterward.
inline std::vector<std::string> frames(std::string_view bytes) {
  std::vector<std::string> result;std::size_t at=0;
  while(at<bytes.size()) {
    assert(bytes.size()-at>=ar::frame_header_size);std::uint64_t body=0;
    for(unsigned i=0;i<8;++i)body|=std::uint64_t(static_cast<unsigned char>(bytes[at+12+i]))<<(8*i);
    assert(body<=bytes.size()-at-ar::frame_header_size);const auto size=ar::frame_header_size+static_cast<std::size_t>(body);
    result.emplace_back(bytes.substr(at,size));at+=size;
  }
  return result;
}
inline std::string join(const std::vector<std::string>& frames,std::size_t count) {
  std::string out;for(std::size_t i=0;i<count;++i)out+=frames[i];return out;
}
inline ar::Decision step(ar::Session& session,std::span<const runtime::sql_rows::SourceReplacement> edits,bool deliver=true) {
  const auto next=session.state().disposed+1;session.log({next,edits,{},{}});auto result=session.decide();if(deliver && !result.rejected)assert(session.deliver());return result;
}
inline void state(const ar::Session& s,std::uint64_t w,std::uint64_t i,std::uint64_t c,std::uint64_t d) {
  const auto value=s.state();assert(value.logged==w && value.disposed==i && value.committed==c && value.delivered==d);
}
} // namespace crown::sql_aggregate_session_test
