#pragma once

#ifndef CROWN_RUNTIME_TESTING
#error "runtime probes require the separate testing runtime target"
#endif

#include "crown/runtime/delta.hpp"

namespace crown::runtime {
class QuerySession;
class WindowController;
// Defined only beside actual private owners in the testing runtime variant.
class RuntimeTestProbe {
 public:
  static SupportRuntime& support(PhysicalRuntime& runtime);
  static PhysicalRuntime& physical(DeltaRuntime& runtime);
  static std::size_t set_satisfied(SupportRuntime&,NodeId,const Row&,std::size_t);
  static std::uint64_t set_projection(SupportRuntime&,NodeId,bool visible,const Row&,std::uint64_t);
  static std::uint64_t set_derivation(PhysicalRuntime&,OccurrenceId,const Row&,std::uint64_t);
  static std::uint64_t set_live_bucket(DeltaRuntime&,NodeId,bool child,const Row&,std::uint64_t);
  static std::size_t set_live_total(DeltaRuntime&,InvariantComponent,std::size_t);
  static void seed_physical_sequence(PhysicalRuntime&,std::uint64_t);
  static void seed_delta_sequence(DeltaRuntime&,std::uint64_t);
  static void seed_c01_report_saturation(DeltaRuntime&);
  static void seed_window_sequence(WindowController&,std::uint64_t);
  static void seed_session_physical_sequence(QuerySession&,std::uint64_t);
};
}  // namespace crown::runtime
