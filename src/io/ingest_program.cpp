#include "crown/io/ingest.hpp"
#include "crown/ir/program.hpp"
#include "crown/io/input_options.hpp"
#include "crown/api/error.hpp"
#include "native_input.hpp"
#include "crown/io/checkpoint.hpp"

namespace crown::io {
EventReader::EventReader(std::istream& input,const CompiledProgram& program,InputOptions options,InputProgress progress)
    :EventReader(program.account(),input,program.source_catalog_owner(),std::move(options),std::move(progress),true) {}
// Full schema fingerprint work allocates under program.account(); equality is
// catalog compatibility, not source-owner/account or committed-progress authority.
bool EventReader::matches_catalog(const CompiledProgram& program) const {
  return input_detail::catalog_fingerprint(program.account(),program.source_catalog_owner(),true).view()==catalog_sha256();
}
EventReader EventReader::with_options(std::istream& input,const CompiledProgram& program,
    const AccountedInputOptions& options,InputProgress progress) {
  if(!options.account() || options.account().statistics().owner!=program.account().statistics().owner)
    throw Error("invalid_input_options","native input options belong to a different query account");
  return EventReader(program.account(),input,program.source_catalog_owner(),options,std::move(progress),true);
}
EventReader EventReader::restore_state(std::istream& input,const CompiledProgram& program,const ReaderCheckpoint& state) {
  return restore_state(input,program,state,SourceStateLimits{});
}
EventReader EventReader::restore_state(std::istream& input,const CompiledProgram& program,const ReaderCheckpoint& state,const SourceStateLimits& limits) {
  return EventReader(program.account(),input,program.source_catalog_owner(),state,limits,true);
}
void EventReader::validate_checkpoint_options(const CompiledProgram& program,const AccountedInputOptions& options,const AccountedInputProgress& progress) {
  validate_options(program.source_catalog_owner(),options,progress);
}
} // namespace crown::io
