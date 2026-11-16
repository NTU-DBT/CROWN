#pragma once
#include "generation_fixture.hpp"
#include "crown/runtime/session_local_sink.hpp"
namespace crown::local_sink_test {
namespace typed=session_checkpoint_test;
namespace window=window_checkpoint_test;
namespace sk=recovery::sink;
using typed::check;
using session_file_test::Directory;
using session_file_test::contents;
using session_file_test::descriptors;
inline runtime::SessionLocalSinkOptions options() {
  runtime::SessionLocalSinkOptions result;constexpr std::string_view id="fedcba9876543210fedcba9876543210";std::copy(id.begin(),id.end(),result.sink_id.begin());return result;
}
// Commit retains outbox delivery for the caller; no public next_output drain here.
inline void finish(runtime::QuerySession& session) {while(session.step()!=runtime::DeltaStep::prepared){}session.commit();}
// Epoch owns native rows during export; returned signed set owns ordinary copies.
inline typed::Output output(const sk::Epoch& epoch) {
  typed::Output result;for(const auto& row:epoch.rows)check(result.emplace(row.operation,storage::export_row(storage::TupleValuesView::borrow(row.values.view()))).second,"duplicate persisted signed row");return result;
}
inline void apply(Database& database,const PhysicalSetUpdate& update) {
  auto& table=database.tables[update.table.value];if(update.operation==SetOperation::insert)table.insert(update.values);else table.erase(update.values);
}
struct Fixture {
  generation_test::Fixture query;
  std::string path;
  explicit Fixture(bool indexed=false,unsigned kind=1):query(indexed,kind),path(query.directory.file("results.sink")) {query.session->create_local_sink(path,options());}
  void commit(std::size_t index) {typed::enqueue(*query.session,io::InputEvent{query.test.updates[index],io::SourcePosition{"feed",query.test.updates[index].sequence*10}});check(query.session->begin_next(),"local sink input missing");finish(*query.session);}
};
} // namespace crown::local_sink_test
