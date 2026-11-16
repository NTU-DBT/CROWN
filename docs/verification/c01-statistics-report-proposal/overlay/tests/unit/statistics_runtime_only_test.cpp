#include "owner_statistics_fixture.hpp"
#include "workload_statistics_fixture.hpp"
#include <type_traits>
using namespace owner_fixture;
static_assert(!std::is_default_constructible_v<SessionStatisticsContext>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(std::declval<SessionStatisticsContext&>().metadata())>>);
int main(){
  const auto p=plan();const auto db=database();SessionOptions options;options.delta=workload_fixture::delta_options();
  auto session=QuerySession::create_typed(p,db,{},options);const auto empty=session->capture_statistics_context();
  check(!empty.state_requested() && empty.combined()->state().components().empty() && empty.combined()->state().usage().rows==0);
  session->configure_workload_statistics(workload_fixture::enabled());auto captured=session->capture_statistics_context(request(p));
  check(captured.metadata().owner()==captured.combined()->state().stamp().owner && captured.metadata().sequence()==0);
  fixture_facts(captured.combined()->state(),db);session->drop();const auto released=session->capture_statistics_context();
  check(!released.combined() && released.workload_options().mode==workload::Mode::counters && released.status().state==SessionState::dropped);
  fixture_facts(captured.combined()->state(),db);auto moved=std::move(captured);check(captured.metadata().owner()==moved.metadata().owner());
}
