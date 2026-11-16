#include "crown/io/batch.hpp"
#include "crown/ir/program.hpp"
#include "crown/io/checkpoint.hpp"

namespace crown::io {
// This thin authority bridge belongs to crown_plan. Core native queue storage
// has no link back to the planner or executable-program implementation.
TypedQueue::TypedQueue(const CompiledProgram& program,QueueMode mode,QueueLimits limits,InputLimits input_limits)
    :TypedQueue(program.account(),program.source_catalog_owner(),mode,limits,input_limits,true) {}
TypedQueue::TypedQueue(const CompiledProgram& program,const QueueCheckpoint& state)
    :TypedQueue(program,state,SourceStateLimits{}) {}
TypedQueue::TypedQueue(const CompiledProgram& program,const QueueCheckpoint& state,const SourceStateLimits& limits)
    :TypedQueue(program.account(),program.source_catalog_owner(),state,limits,true) {}
} // namespace crown::io
