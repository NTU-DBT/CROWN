#pragma once
#include "crown/runtime/session_generation.hpp"
#include "session_journal_fixture.hpp"
#include <iomanip>

namespace crown::generation_test {
namespace typed=session_checkpoint_test;
namespace window=window_checkpoint_test;
namespace jp=recovery::journal;
using typed::check;
using session_file_test::Directory;
using session_file_test::contents;
using session_file_test::descriptors;
inline runtime::SessionGenerationOptions options() {
  runtime::SessionGenerationOptions result;result.journal=session_journal_test::options();return result;
}
inline runtime::SessionGenerationRecoveryOptions recovery_options() {
  runtime::SessionGenerationRecoveryOptions result;result.replay.journal=session_journal_test::options();return result;
}
inline std::string path(const std::string& root,std::uint64_t generation,std::string_view suffix) {
  std::ostringstream out;out<<root<<".g"<<std::hex<<std::setw(16)<<std::setfill('0')<<generation<<suffix;return out.str();
}
inline void put(const std::string& name,std::string_view bytes) {
  std::ofstream out(name,std::ios::binary|std::ios::trunc);out.write(bytes.data(),static_cast<std::streamsize>(bytes.size()));check(static_cast<bool>(out),"generation fixture write failed");
}
// Inspected fixed metadata is not a native owner or retirement/publication receipt.
inline recovery::GenerationRoot root(const std::string& name) {return recovery::inspect_generation_root(contents(name));}
struct Fixture {
  Directory directory;
  typed::Case test;
  runtime::QuerySession::Owner session;
  std::string name;
  explicit Fixture(bool indexed=false,unsigned kind=1,bool enable=true):test(typed::fixture(indexed,kind)),
      session(runtime::QuerySession::create_typed(test.plan,{},session_journal_test::session_options(kind))),name(directory.file("query.root")) {
    session->start();if(enable)session->enable_generation(name,options());
  }
  void update(std::size_t index) {
    typed::enqueue(*session,io::InputEvent{test.updates[index],io::SourcePosition{"feed",test.updates[index].sequence*10}});
    check(session->begin_next(),"generation event missing");static_cast<void>(typed::finish(*session));
  }
};
} // namespace crown::generation_test
