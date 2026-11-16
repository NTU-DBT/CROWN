#pragma once
#include "crown/io/ingest.hpp"
#include "crown/ir/physical.hpp"
#include <optional>
#include <string>
namespace crown::cli {
// Diagnostic input/event caps and modeled reference work/bytes are separate
// from native execution memory; these estimates do not bound every allocation.
[[nodiscard]] std::string verify_workflow_trace(const PhysicalPlan&,const std::string&,
    io::InputOptions,std::optional<std::uint64_t>,std::uint64_t,std::uint64_t,
    std::uint64_t,std::size_t);
}
