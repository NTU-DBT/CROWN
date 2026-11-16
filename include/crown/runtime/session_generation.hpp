#pragma once
#include "crown/runtime/session_journal.hpp"
#include "crown/recovery/generation.hpp"

namespace crown::runtime {
struct SessionGenerationOptions {
  SessionJournalOptions journal;
  recovery::GenerationLimits root;
  // Includes first/current; rotation retains older pairs until explicit verified
  // retirement advances the durable floor and completes recorded cleanup.
  std::uint64_t retained_generations=32;
  recovery::PlanDescriptorLimits descriptor;
};
struct SessionGenerationRecoveryOptions {
  // The root supplies replay.journal.generation; query_id remains an expected
  // binding. Its output frontier never authorizes historical file deletion.
  SessionJournalRecoveryOptions replay;
  recovery::GenerationLimits root;
  std::uint64_t retained_generations=32;
  recovery::PlanDescriptorLimits descriptor;
};
struct SessionGenerationState {
  // Last known metadata; when recovery_required, reopen the actual root.
  // Selected fields retain no lock and cannot authorize history retirement.
  bool enabled=false,recovery_required=false;
  recovery::GenerationRoot selected;
  std::uint64_t operations=0,validation_work=0;
  bool retirement_pending=false;
  std::uint64_t retirement_first=0,retirement_before=0;
};
} // namespace crown::runtime
