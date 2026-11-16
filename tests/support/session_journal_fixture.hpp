#pragma once
#include "crown/runtime/session_journal.hpp"
#include "session_file_fixture.hpp"
#include "crown/ir/digest.hpp"
namespace crown::session_journal_test {
namespace typed=session_checkpoint_test;
namespace window=window_checkpoint_test;
using typed::check;
using session_file_test::Directory;
using session_file_test::contents;
using session_file_test::descriptors;
namespace jp=recovery::journal;
inline runtime::SessionJournalOptions options() {
  runtime::SessionJournalOptions result;constexpr std::string_view id="0123456789abcdef0123456789abcdef";
  std::copy(id.begin(),id.end(),result.query_id.begin());return result;
}
// Trusted complete fixture frames only; views borrow bytes and do not validate checksums.
inline std::vector<std::string_view> frames(const std::string& bytes) {
  std::vector<std::string_view> result;std::size_t offset=0;
  while(offset<bytes.size()) {
    check(bytes.size()-offset>=jp::frame_header_size,"truncated test log frame");std::uint64_t size=0;
    for(unsigned i=0;i<8;++i)size|=std::uint64_t(static_cast<unsigned char>(bytes[offset+12+i]))<<(8*i);
    size+=jp::frame_header_size;check(size<=bytes.size()-offset,"truncated test log body");result.emplace_back(bytes.data()+offset,static_cast<std::size_t>(size));offset+=static_cast<std::size_t>(size);
  }
  return result;
}
inline runtime::SessionOptions session_options(unsigned kind) {runtime::SessionOptions result;if(kind==2)result.delta.mode=runtime::DeltaMode::maintenance;return result;}
struct Fixture {
  Directory directory;
  typed::Case test;
  runtime::QuerySession::Owner session;
  std::string checkpoint,log;
  explicit Fixture(bool indexed=false,unsigned kind=0):test(typed::fixture(indexed,kind)),session(runtime::QuerySession::create_typed(test.plan,{},session_options(kind))),
      checkpoint(directory.file("base.crown")),log(directory.file("query.wal")) {
    session->start();static_cast<void>(session->checkpoint_file(checkpoint));session->enable_journal(checkpoint,log,options());
  }
  void offer(std::size_t index=0) {typed::enqueue(*session,io::InputEvent{test.updates[index],io::SourcePosition{"test",100+index}});}
  // Intentionally leaves the actual epoch prepared, without committing.
  void prepare() {check(session->begin_next(),"journal fixture missing head");while(session->step()!=runtime::DeltaStep::prepared){}}
};
} // namespace crown::session_journal_test
