#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/api/error.hpp"
#include <chrono>

namespace crown::io {
namespace {
using Clock=std::chrono::steady_clock;
// Prepare already serialized ordinary DTO scratch; this caps retained wire bytes,
// not total compiler allocation. Replay applies it before parsing caller bytes.
void size(std::string_view bytes,const CompilerArtifactLimits& limits) {
  if(bytes.empty() || bytes.size()>limits.bytes)throw Error("compiler_artifact_limit","compiler artifact exceeds its byte grant");
}
// Snapshot the whole supplied compiler account, including other retained owners.
CompilerArtifactStatistics capture_statistics(const resource::MemoryAccount& account,std::size_t bytes,Clock::time_point started) {
  const auto ended=Clock::now();
  if(ended<started)throw Error("compiler_artifact_clock","compiler artifact clock regressed");
  return {bytes,static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(ended-started).count()),2,account.statistics()};
}
resource::AccountedText retain(const resource::MemoryAccount& account,std::string_view bytes) {
  return resource::AccountedText::copy_of(account,bytes,{resource::MemoryOwnerKind::immutable_metadata,0},resource::MemoryPurpose::immutable_metadata);
}
} // namespace
CompilerPlanArtifact CompilerPlanArtifact::prepare(const resource::MemoryAccount& account,const PhysicalPlan& plan,CompilerArtifactLimits limits) {
  const auto started=Clock::now();CompiledProgram program;resource::AccountedText bytes;
  {
    const auto serialized=write_physical(plan).dump();size(serialized,limits);
    program=CompiledProgram::compile(account,plan);bytes=retain(account,serialized);
  }
  const auto measured=capture_statistics(account,bytes.size(),started);
  return CompilerPlanArtifact(std::move(program),std::move(bytes),measured);
}
CompilerPlanArtifact CompilerPlanArtifact::replay(const resource::MemoryAccount& account,std::string_view serialized,CompilerArtifactLimits limits) {
  const auto started=Clock::now();size(serialized,limits);CompiledProgram program;
  {
    const auto plan=read_physical(serialized,limits.replay);program=CompiledProgram::compile(account,plan);
  }
  auto bytes=retain(account,serialized);
  return CompilerPlanArtifact(std::move(program),std::move(bytes),capture_statistics(account,serialized.size(),started));
}
CompilerPlanArtifact CompilerPlanArtifact::prepare(const resource::MemoryAccount& account,const CompiledProgram& source,CompilerArtifactLimits limits) {
  const auto started=Clock::now();CompiledProgram program;resource::AccountedText bytes;
  if(!source)throw Error("compiler_artifact_input","supply a checked compiled source");
  {
    const auto exported=PhysicalPlan::from_compiled(source);
    const auto plan=exported.normalized()?planner::lower_normalized(*exported.normalized(),exported.tree(),exported.options(),limits.replay.program,limits.replay.lowering):
        planner::lower_tree(exported.catalog(),exported.query(),exported.tree(),exported.options(),limits.replay.lowering);
    if(plan.physical_sha256()!=source.physical_sha256() || plan.physical_source_sha256()!=source.physical_source_sha256())
      throw Error("compiler_artifact_binding","compiler reconstruction differs from the checked program");
    const auto serialized=write_physical(plan).dump();size(serialized,limits);
    program=CompiledProgram::compile(account,plan);bytes=retain(account,serialized);
  }
  const auto measured=capture_statistics(account,bytes.size(),started);
  return CompilerPlanArtifact(std::move(program),std::move(bytes),measured);
}
} // namespace crown::io
