#pragma once

#include "crown/ir/program.hpp"
#include "crown/resource/ownership.hpp"
#include "../frontend/sql_scalar.hpp"
#include <limits>

namespace crown::program::detail {
template<class T> using InputVector=std::vector<T,resource::MemoryAllocator<T>>;
using InputCells=std::span<SqlValue>;
struct InputInstruction {
  using Execute=void (*)(const InputInstruction&,storage::RowView,InputCells,storage::IndexWorkAllowance*);
  frontend::ExpressionId target;
  ColumnId column;
  Span<frontend::ExpressionId> arguments;
  Execute execute;
};
struct InputRange {std::size_t begin=0,count=0;};

inline void input_column(const InputInstruction& instruction,storage::RowView row,
    InputCells values,storage::IndexWorkAllowance*) {
  if(instruction.target.value>=values.size())throw storage::IndexFailure(storage::IndexFault::contract);
  values[instruction.target.value]=row.at(instruction.column.value);
}
template<frontend::SqlOperator Operation>
void input_operation(const InputInstruction& instruction,storage::RowView,
    InputCells values,storage::IndexWorkAllowance* work) {
  if(instruction.target.value>=values.size())throw storage::IndexFailure(storage::IndexFault::contract);
  values[instruction.target.value]=frontend::sql_detail::evaluate(Operation,instruction.arguments,values,work);
}
inline InputInstruction::Execute input_executor(frontend::SqlOperator operation) {
  using enum frontend::SqlOperator;
#define CROWN_INPUT_OPERATION(name) case name:return &input_operation<name>
  switch(operation) {
    CROWN_INPUT_OPERATION(equal);CROWN_INPUT_OPERATION(not_equal);
    CROWN_INPUT_OPERATION(less);CROWN_INPUT_OPERATION(less_equal);
    CROWN_INPUT_OPERATION(greater);CROWN_INPUT_OPERATION(greater_equal);
    CROWN_INPUT_OPERATION(conjunction);CROWN_INPUT_OPERATION(disjunction);CROWN_INPUT_OPERATION(negation);
    CROWN_INPUT_OPERATION(is_null);CROWN_INPUT_OPERATION(is_not_null);
    CROWN_INPUT_OPERATION(is_true);CROWN_INPUT_OPERATION(is_not_true);
    CROWN_INPUT_OPERATION(is_false);CROWN_INPUT_OPERATION(is_not_false);
    CROWN_INPUT_OPERATION(is_unknown);CROWN_INPUT_OPERATION(is_not_unknown);
    CROWN_INPUT_OPERATION(identity_cast);CROWN_INPUT_OPERATION(literal_cast);
    CROWN_INPUT_OPERATION(widen_integer);CROWN_INPUT_OPERATION(using_value);
  }
#undef CROWN_INPUT_OPERATION
  throw storage::IndexFailure(storage::IndexFault::contract);
}

// Logical preparation checkpoints are separate from base-copy IndexWork. No
// preparation grant refills a receiving owner's existing IndexWork allowance.
class InputBudget {
  const InputPreparationLimits& limits_;
  InputPreparationUsage& usage_;
  storage::IndexWorkAllowance* receiving_;
 public:
  InputBudget(const InputPreparationLimits& limits,InputPreparationUsage& usage,storage::IndexWorkAllowance* receiving)
      :limits_(limits),usage_(usage),receiving_(receiving) {}
  void step() {
    if(usage_.work>=limits_.work)throw storage::IndexFailure(storage::IndexFault::work_limit);
    if(receiving_)receiving_->admit({.structural_steps=1});
    ++usage_.work;
  }
  template<class T> void table(std::size_t count) {
    if(count>SIZE_MAX/sizeof(T))throw storage::IndexFailure(storage::IndexFault::overflow);
    const auto bytes=count*sizeof(T);
    if(receiving_)receiving_->admit({.pointer_slots=static_cast<std::uint64_t>(bytes/sizeof(void*)+(bytes%sizeof(void*)!=0))});
  }
};

// A prepared owner exists only in the opted-in mode. Its argument views refer
// to the enclosing immutable program's admitted normalized metadata.
struct PreparedInputs {
  InputPreparationLimits limits;
  InputPreparationUsage usage;
  InputVector<InputInstruction> instructions;
  InputVector<InputRange> ranges;
  PreparedInputs(const resource::MemoryAccount& account,resource::MemoryAttribution owner,
      InputPreparationLimits value,InputPreparationUsage counters)
      :limits(value),usage(counters),
       instructions(resource::MemoryAllocator<InputInstruction>(account,resource::MemoryPurpose::immutable_metadata,owner)),
       ranges(resource::MemoryAllocator<InputRange>(account,resource::MemoryPurpose::immutable_metadata,owner)) {}

  static InputPreparationUsage analyze(const std::optional<NormalizedSql>& sql,std::size_t ports,
      const InputPreparationLimits& limits,storage::IndexWorkAllowance* receiving) {
    InputPreparationUsage usage;InputBudget budget(limits,usage,receiving);budget.step();
    if(!sql)return usage;
    // A constant executable has no ports even when its admitted SQL source
    // retains dormant adapters. Only executable ports need instructions.
    if(ports && sql->adapters.size()!=ports)throw storage::IndexFailure(storage::IndexFault::contract);
    for(std::size_t port=0;port<ports;++port) {
      budget.step();const auto& adapter=sql->adapters[port];
      for(const auto id:adapter.program) {
        budget.step();
        if(usage.instructions>=limits.instructions)throw storage::IndexFailure(storage::IndexFault::capacity);
        ++usage.instructions;
        const auto& expression=sql->binding.expressions.at(id.value).node;
        if(const auto* column=std::get_if<BoundColumn>(&expression)) {
          if(column->occurrence.value!=port)throw storage::IndexFailure(storage::IndexFault::contract);
        } else if(const auto* operation=std::get_if<BoundOperation>(&expression)) {
          static_cast<void>(input_executor(operation->operation));
          for(const auto argument:operation->arguments) {
            budget.step();if(argument.value>=sql->constants.size())throw storage::IndexFailure(storage::IndexFault::contract);
          }
        } else throw storage::IndexFailure(storage::IndexFault::contract);
      }
    }
    return usage;
  }
  static std::shared_ptr<const PreparedInputs> build(const resource::MemoryAccount& account,
      resource::MemoryAttribution owner,const std::optional<NormalizedSql>& sql,std::size_t ports,
      const InputPreparationLimits& limits,InputPreparationUsage usage,storage::IndexWorkAllowance* receiving) {
    InputBudget allocation(limits,usage,receiving);allocation.table<PreparedInputs>(1);
    auto result=resource::make_accounted_shared<PreparedInputs>(owner,account,resource::MemoryPurpose::immutable_metadata,
        account,owner,limits,usage);
    InputBudget budget(result->limits,result->usage,receiving);
    if(sql) {
      budget.table<InputRange>(ports);result->ranges.reserve(ports);
      budget.table<InputInstruction>(usage.instructions);result->instructions.reserve(usage.instructions);
      for(std::size_t port=0;port<ports;++port) {
        const auto& adapter=sql->adapters[port];
        budget.step();result->ranges.push_back({result->instructions.size(),adapter.program.size()});
        for(const auto id:adapter.program) {
          budget.step();const auto& expression=sql->binding.expressions.at(id.value).node;
          if(const auto* column=std::get_if<BoundColumn>(&expression))
            result->instructions.push_back({id,column->column,{},&input_column});
          else {
            const auto& operation=std::get<BoundOperation>(expression);
            result->instructions.push_back({id,ColumnId{},operation.arguments,input_executor(operation.operation)});
          }
        }
      }
    }
    if(result->instructions.capacity()>SIZE_MAX/sizeof(InputInstruction) || result->ranges.capacity()>SIZE_MAX/sizeof(InputRange))
      throw storage::IndexFailure(storage::IndexFault::overflow);
    const auto code_bytes=result->instructions.capacity()*sizeof(InputInstruction);
    const auto range_bytes=result->ranges.capacity()*sizeof(InputRange);
    if(range_bytes>SIZE_MAX-code_bytes)throw storage::IndexFailure(storage::IndexFault::overflow);
    result->usage.metadata_bytes=code_bytes+range_bytes;
    return result;
  }
  void execute(OccurrenceId port,storage::RowView row,InputCells values,storage::IndexWorkAllowance* work) const {
    const auto& range=ranges.at(port.value);
    for(std::size_t offset=0;offset<range.count;++offset) {
      if(work)work->admit({.structural_steps=1});
      const auto& instruction=instructions[range.begin+offset];instruction.execute(instruction,row,values,work);
    }
  }
};
inline storage::IndexWork input_work_difference(storage::IndexWork before,storage::IndexWork after) {
  return {before.structural_steps-after.structural_steps,before.scalar_fields-after.scalar_fields,
      before.scalar_bytes-after.scalar_bytes,before.pointer_slots-after.pointer_slots,before.link_actions-after.link_actions};
}
} // namespace crown::program::detail
