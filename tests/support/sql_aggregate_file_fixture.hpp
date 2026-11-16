#pragma once

#include "crown/recovery/sql_aggregate_files.hpp"
#include "crown/ir/digest.hpp"
#include "crown/planner/oracle.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

namespace crown::sql_aggregate_file_test {
namespace ar=recovery::sql_aggregate;
using Cell=runtime::sql_rows::Cell;
// Test-only lexical directory owner. Cleanup is best effort and runs outside
// allocation-denial scopes; it is not production namespace recovery machinery.
struct Directory {
  std::string name;
  Directory() {
    char pattern[]="/tmp/crown-r2-files-XXXXXX";const auto path=::mkdtemp(pattern);assert(path);name=path;
  }
  ~Directory() { std::error_code error;std::filesystem::remove_all(name,error); }
  [[nodiscard]] std::string file(std::string_view leaf="file") const { return name+"/"+std::string(leaf); }
};
inline void put(const std::string& path,std::string_view bytes) {
  std::ofstream out(path,std::ios::binary|std::ios::trunc);out.write(bytes.data(),static_cast<std::streamsize>(bytes.size()));assert(out);
}
inline std::string contents(const std::string& path) {
  std::ifstream in(path,std::ios::binary);return {std::istreambuf_iterator<char>(in),std::istreambuf_iterator<char>()};
}
inline std::size_t descriptors() {
  std::size_t count=0;for(const auto& entry:std::filesystem::directory_iterator("/proc/self/fd")) { static_cast<void>(entry);++count; }return count;
}
inline std::size_t temporaries(const Directory& dir) {
  std::size_t count=0;
  for(const auto& entry:std::filesystem::directory_iterator(dir.name))if(entry.path().filename().native().starts_with(".crown-r2-"))++count;
  return count;
}
inline ar::Hash hash(char value) { ar::Hash result{};result.fill(value);return result; }
inline Cell number(std::int64_t value) { return storage::ScalarView{value}; }
// Genuine original SQL and actual native tree; record tests never fabricate a
// descriptor from editable metadata. Capture is on for full before/after frames.
struct Schema {
  resource::MemoryAccount account=resource::MemoryAccount::create(128ULL*1024*1024);
  ar::Admitted admitted=make(account);
  ar::Binding binding;
  ar::WalHeader wal;
  ar::SinkHeader sink;
  static ar::Admitted make(const resource::MemoryAccount& receiving) {
    Catalog catalog{1,{{"r",{{"g",ScalarType::string,true},{"x",ScalarType::int64,true}}}}};
    auto result=frontend::bind_sql_aggregate_into(receiving,"SELECT g,COUNT(*),SUM(x) FROM r GROUP BY g",catalog);
    assert(std::holds_alternative<frontend::SqlAggregateProgram>(result));
    auto program=std::get<frontend::SqlAggregateProgram>(std::move(result));const auto core=program.source_program().export_core();
    const auto selected=planner::minimum_tree(core.catalog,core.query);assert(selected.tree);
    runtime::sql_aggregate::Options options;options.capture_changes=true;
    return ar::admit_into(receiving,std::move(program),*selected.tree,{},options);
  }
  Schema() {
    binding.query_id.fill('1');binding.descriptor_sha256=admitted.descriptor.sha256();
    wal={binding,7,hash('a'),0,0};sink.binding=binding;sink.sink_id.fill('2');
  }
};
// Three commands: a real nullable-key commit, a transport Reject at I2/C1,
// then a real no-op commit at I3/C2 with a whole empty group epoch. The middle
// Reject is a file-protocol fixture, not an independent semantic replay proof.
struct Packets {
  std::vector<ar::Frame> wal,sink;
  explicit Packets(Schema& s) {
    const auto& program=s.admitted.descriptor.program();const std::array<Cell,2> row{Cell{},number(5)};
    std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,2}};
    wal.push_back(ar::encode(s.account,program,0,s.wal));sink.push_back(ar::encode(s.account,program,0,s.sink));
    wal.push_back(ar::encode(s.account,program,1,ar::InputView{1,edits,ar::SourcePosition{"feed",10},ar::ReaderPosition{10,1}}));
    {
      const auto output=s.admitted.runtime.prepare_batch({1,edits}).commit();assert(output.output.size()==1);
      sink.push_back(ar::encode(s.account,program,1,ar::GroupEpochView{7,1,1,wal[1].info().body_sha256,output.changed,output.group_changed,output.output}));
    }
    wal.push_back(ar::encode(s.account,program,2,ar::Commit{1,wal[1].info().body_sha256,1,1,sink[1].bytes().size(),sha256_fixed(sink[1].bytes())}));
    edits[0].before=9;edits[0].after=0;
    wal.push_back(ar::encode(s.account,program,3,ar::InputView{2,edits,{},{}}));
    wal.push_back(ar::encode(s.account,program,4,ar::Reject{3,wal[3].info().body_sha256,2,1,ar::RejectReason::weight_mismatch}));
    edits[0].before=2;edits[0].after=2;
    wal.push_back(ar::encode(s.account,program,5,ar::InputView{3,edits,{},{}}));
    {
      const auto output=s.admitted.runtime.prepare_batch({2,edits}).commit();assert(output.output.empty());
      sink.push_back(ar::encode(s.account,program,2,ar::GroupEpochView{8,3,2,wal[5].info().body_sha256,output.changed,output.group_changed,output.output}));
    }
    wal.push_back(ar::encode(s.account,program,6,ar::Commit{5,wal[5].info().body_sha256,3,2,sink[2].bytes().size(),sha256_fixed(sink[2].bytes())}));
  }
  [[nodiscard]] static std::string prefix(const std::vector<ar::Frame>& frames,std::size_t count) {
    std::string result;for(std::size_t i=0;i<count;++i)result+=frames[i].bytes();return result;
  }
};
template<class Action> void refused(Action action) {
  bool failed=false;try { action(); } catch(const std::exception&) { failed=true; }assert(failed);
}
// Recompute both protected checksums so hostile complete frames reach actual
// structure/sequence/schema checks rather than stopping at a stale digest.
inline void reseal(std::string& bytes) {
  const auto body=sha256_fixed(std::string_view(bytes).substr(ar::frame_header_size));std::copy(body.begin(),body.end(),bytes.begin()+20);
  const auto prefix=sha256_fixed(std::string_view(bytes).substr(0,ar::frame_prefix_size));std::copy(prefix.begin(),prefix.end(),bytes.begin()+ar::frame_prefix_size);
}
} // namespace crown::sql_aggregate_file_test
