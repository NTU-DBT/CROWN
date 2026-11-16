#include "crown/io/admission.hpp"

#include "crown/io/binding.hpp"
#include "crown/io/normalization.hpp"
#include "crown/io/recognition.hpp"
#include "json.hpp"
#include <limits>

namespace crown::io {
namespace {
Json optional_integer(std::optional<std::uint64_t> value) { return value ? Json(*value) : Json(nullptr); }
}  // namespace
// Diagnostic compiler DTO: frontend/structure status never lowers or starts execution.
Json write_admission(const frontend::AdmissionResult& result) {
  Json output{{"schema_version",1},{"admission_scope","frontend_and_structure"},
      {"admission_status",frontend::admission_status_name(result.status)},{"phase",result.phase},
      {"execution_status","not_lowered"},{"route",nullptr},{"diagnostic",nullptr},{"program",nullptr},{"structure",nullptr},
      {"work",{{"binding",optional_integer(result.work.binding)},{"normalization",optional_integer(result.work.normalization)},
          {"recognition",optional_integer(result.work.recognition)}}},
      {"limits",{{"binding",{{"work_limit",optional_integer(result.limits.binding.work_limit)},
          {"expression_limit",result.limits.binding.expression_limit},{"recursion_limit",result.limits.binding.recursion_limit}}},
          {"normalization",{{"work_limit",optional_integer(result.limits.normalization.work_limit)}}},
          {"recognition",{{"work_limit",optional_integer(result.limits.recognition.work_limit)}}}}}};
  if (result.route) output["route"] = *result.route == frontend::AdmissionRoute::free_connex ? "free_connex" : "constant_empty";
  if (result.diagnostic) {
    const auto failure = write_sql_binding(frontend::BindingDiagnostic{result.phase,*result.diagnostic});
    output["diagnostic"] = failure.at("diagnostic");
  }
  if (result.program) output["program"] = write_sql_normalization(*result.program);
  if (result.structure && result.program) output["structure"] = write_structural_analysis(*result.structure,result.program->core);
  return output;
}

frontend::AdmissionOptions read_admission_options(std::string_view text) {
  const auto input = detail::parse_json(text);
  detail::fields(input,"$",{"schema_version"},{"parameter_types","parameter_values","limits"});
  detail::version(input.at("schema_version"),"$.schema_version");
  frontend::AdmissionOptions options;
  if (input.contains("parameter_types")) options.binding = read_bind_options(Json{{"schema_version",1},{"parameters",input.at("parameter_types")}}.dump());
  if (input.contains("parameter_values")) options.parameters = read_parameter_values(Json{{"schema_version",1},{"values",input.at("parameter_values")}}.dump());
  if (!input.contains("limits")) return options;
  const auto& limits = input.at("limits");
  detail::fields(limits,"$.limits",{},{"binding","normalization","recognition"});
  const auto work = [](const Json& node, std::optional<std::uint64_t>& target) {
    if (node.contains("work_limit")) target = node.at("work_limit").is_null() ? std::optional<std::uint64_t>{} : detail::unsigned_integer(node.at("work_limit"),"work_limit");
  };
  if (limits.contains("binding")) {
    const auto& binding = limits.at("binding");
    detail::fields(binding,"$.limits.binding",{},{"work_limit","expression_limit","recursion_limit"});
    work(binding,options.binding.limits.work_limit);
    const auto size = [](const Json& node,const char* name,std::size_t& target) {
      if (!node.contains(name)) return;
      const auto value = detail::unsigned_integer(node.at(name),name);
      if (value > std::numeric_limits<std::size_t>::max()) detail::fail(name,"exceeds host size_t range");
      target = static_cast<std::size_t>(value);
    };
    size(binding,"expression_limit",options.binding.limits.expression_limit);
    size(binding,"recursion_limit",options.binding.limits.recursion_limit);
  }
  if (limits.contains("normalization")) {
    detail::fields(limits.at("normalization"),"$.limits.normalization",{},{"work_limit"});
    work(limits.at("normalization"),options.normalization.work_limit);
  }
  if (limits.contains("recognition")) {
    detail::fields(limits.at("recognition"),"$.limits.recognition",{},{"work_limit"});
    work(limits.at("recognition"),options.recognition.work_limit);
  }
  return options;
}
}  // namespace crown::io
