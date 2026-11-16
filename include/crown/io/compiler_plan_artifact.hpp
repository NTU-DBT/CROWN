#pragma once

#include "crown/io/physical.hpp"
#include "crown/ir/program.hpp"
#include "crown/resource/text.hpp"

namespace crown::io {
struct CompilerArtifactLimits {
  // Prepare checks this after serialization; replay checks before DOM parsing.
  // It does not cap all compiler DTO/temporary allocation.
  std::uint64_t bytes=64*1024*1024;
  PhysicalReadLimits replay;
};
struct CompilerArtifactStatistics {
  std::uint64_t bytes=0,preparation_ns=0,clock_reads=0;
  resource::MemoryStatistics compiler_memory;
};
// Explicit compiler DTO boundary, before native publication/admission. JSON,
// PhysicalPlan and their transient compiler allocations stay in this boundary;
// retained executable metadata and bytes use the supplied compiler account.
// Native execution must freeze/import into its original receiving account.
class CompilerPlanArtifact {
 public:
  [[nodiscard]] static CompilerPlanArtifact prepare(const resource::MemoryAccount& compiler_account,
      const PhysicalPlan&,CompilerArtifactLimits={});
  // Explicit compiler export/reconstruction of a native checked selection.
  // Includes DTO export and canonical lowering in preparation time; execution
  // never calls this boundary while mutating or publishing a native session.
  [[nodiscard]] static CompilerPlanArtifact prepare(const resource::MemoryAccount& compiler_account,
      const CompiledProgram&,CompilerArtifactLimits={});
  [[nodiscard]] static CompilerPlanArtifact replay(const resource::MemoryAccount& compiler_account,
      std::string_view,CompilerArtifactLimits={});
  CompilerPlanArtifact(const CompilerPlanArtifact&)=delete;
  CompilerPlanArtifact& operator=(const CompilerPlanArtifact&)=delete;
  CompilerPlanArtifact(CompilerPlanArtifact&&) noexcept=default;
  CompilerPlanArtifact& operator=(CompilerPlanArtifact&&) noexcept=default;
  [[nodiscard]] const CompiledProgram& program() const noexcept {return program_;}
  [[nodiscard]] std::string_view bytes() const noexcept {return bytes_.view();}
  [[nodiscard]] const CompilerArtifactStatistics& statistics() const noexcept {return statistics_;}
 private:
  CompilerPlanArtifact(CompiledProgram program,resource::AccountedText bytes,CompilerArtifactStatistics statistics)
      :program_(std::move(program)),bytes_(std::move(bytes)),statistics_(statistics) {}
  CompiledProgram program_;
  resource::AccountedText bytes_;
  CompilerArtifactStatistics statistics_;
};
} // namespace crown::io
