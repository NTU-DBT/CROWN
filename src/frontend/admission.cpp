#include "crown/frontend/admission.hpp"

#include "crown/api/error.hpp"
#include <utility>

namespace crown::frontend {
namespace {
void rejection(AdmissionResult& result, BindingDiagnostic failure) {
  result.phase = std::move(failure.phase);
  const auto& code = failure.diagnostic.code;
  if (code == "invalid_ast") throw Error("binding_contract",failure.diagnostic.message);
  result.status = code == "resource_limit" ? AdmissionStatus::resource_limit : result.phase == "syntax" ? AdmissionStatus::syntax_error :
      code.starts_with("unsupported_") ? AdmissionStatus::unsupported_semantics : AdmissionStatus::semantic_error;
  result.diagnostic = std::move(failure.diagnostic);
}
}  // namespace

AdmissionResult admit_normalized(NormalizedSql program, planner::RecognitionLimits limits, NormalizeLimits grounding_limits) {
  AdmissionResult result;
  result.limits = {program.binding.limits,program.limits,limits};
  result.work.binding = program.binding.work;
  if (program.schema_version == 1) {
    NormalizeOptions options; options.parameters = program.parameters; options.limits = program.limits;
    if (grounding_limits.work_limit && (!options.limits.work_limit || *grounding_limits.work_limit < *options.limits.work_limit)) options.limits.work_limit = grounding_limits.work_limit;
    result.limits.normalization = options.limits;
    auto grounded = normalize_sql(program.binding,options);
    if (auto* failure = std::get_if<BindingDiagnostic>(&grounded)) { rejection(result,std::move(*failure)); return result; }
    program = std::get<NormalizedSql>(std::move(grounded));
  }
  if (program.schema_version != 2) throw Error("admission_contract","admission requires a validated normalized v1 or v2 program");
  result.work.normalization = program.work;
  result.program = std::move(program);
  auto run = planner::analyze_bounded(result.program->core_catalog,result.program->core,limits);
  result.work.recognition = run.work;
  if (!run.analysis) {
    rejection(result,{"recognition",{"resource_limit","GYO recognition exceeded its work budget; no query class is claimed",{},{},{},{}}});
    return result;
  }
  result.structure = std::move(run.analysis);
  if (result.program->core.contradiction) {
    result.status = AdmissionStatus::admitted; result.route = AdmissionRoute::constant_empty;
  } else if (result.structure->query_class == planner::QueryClass::free_connex) {
    result.status = AdmissionStatus::admitted; result.route = AdmissionRoute::free_connex;
  } else if (result.structure->query_class == planner::QueryClass::cyclic) {
    rejection(result,{"recognition",{"cyclic_body","the normalized body has a cyclic GYO residual; it is outside the free-connex core",{},{},{},{}}});
    result.status = AdmissionStatus::cyclic_body;
  } else {
    rejection(result,{"recognition",{"non_free_connex","the body is acyclic but adding the ordered output's variable set leaves a cyclic residual",{},{},{},{}}});
    result.status = AdmissionStatus::non_free_connex;
  }
  if (result.status == AdmissionStatus::admitted) result.phase = "complete";
  return result;
}

AdmissionResult admit_sql(std::string_view source, const Catalog& catalog, const AdmissionOptions& options) {
  AdmissionResult result;
  result.limits = {options.binding.limits,options.normalization,options.recognition};
  auto bound = bind_sql(source,catalog,options.binding);
  if (auto* failure = std::get_if<BindingDiagnostic>(&bound)) { rejection(result,std::move(*failure)); return result; }
  const auto& binding = std::get<BoundSql>(bound);
  result.work.binding = binding.work;
  NormalizeOptions normalization; normalization.parameters = options.parameters; normalization.limits = options.normalization;
  auto normalized = normalize_sql(binding,normalization);
  if (auto* failure = std::get_if<BindingDiagnostic>(&normalized)) { rejection(result,std::move(*failure)); return result; }
  return admit_normalized(std::get<NormalizedSql>(std::move(normalized)),options.recognition);
}

std::string admission_status_name(AdmissionStatus status) {
  switch (status) {
    case AdmissionStatus::admitted: return "admitted";
    case AdmissionStatus::syntax_error: return "syntax_error";
    case AdmissionStatus::semantic_error: return "semantic_error";
    case AdmissionStatus::unsupported_semantics: return "unsupported_semantics";
    case AdmissionStatus::cyclic_body: return "cyclic_body";
    case AdmissionStatus::non_free_connex: return "non_free_connex";
    case AdmissionStatus::resource_limit: return "resource_limit";
  }
  throw Error("admission_contract","unknown admission status");
}
}  // namespace crown::frontend
