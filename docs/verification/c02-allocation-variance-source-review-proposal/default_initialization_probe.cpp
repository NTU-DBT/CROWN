#include "profile_values.hpp"
#include <memory>

namespace {
using namespace allocation_probe;
template<class T> void default_object(const char* label) {
  begin();T value;const auto counts=end();verify(value);emit(label,"stack_default",counts);
}
template<class T> void value_object(const char* label) {
  begin();T value{};const auto counts=end();verify(value);emit(label,"stack_value",counts);
}
template<class T> void shared_object(const char* label) {
  begin();auto value=std::make_shared<T>();const auto counts=end();verify(*value);emit(label,"make_shared_empty",counts);
}
template<class T> void pair(const char* label){default_object<T>(label);value_object<T>(label);}
template<class T> void triple(const char* label){pair<T>(label);shared_object<T>(label);}
}
int main(){try{
  using namespace allocation_probe;
  std::printf("default-probe scope=success-only forms=22 string_size=%zu empty_string_capacity=%zu\n",sizeof(std::string),std::string{}.capacity());
  for(const auto& text:operation_modes)std::printf("literal group=operation_modes bytes=%zu value=%.*s\n",text.size(),static_cast<int>(text.size()),text.data());
  for(const auto& text:assumptions)std::printf("literal group=assumptions bytes=%zu value=%.*s\n",text.size(),static_cast<int>(text.size()),text.data());
  for(const auto& text:output_accounting)std::printf("literal group=output_accounting bytes=%zu value=%.*s\n",text.size(),static_cast<int>(text.size()),text.data());
  triple<crown::GuaranteeProfile>("GuaranteeProfile");
  {begin();auto value=std::make_shared<crown::GuaranteeProfile>(crown::GuaranteeProfile{});const auto counts=end();verify(*value);emit("GuaranteeProfile","make_shared_from_value",counts);}
  triple<crown::PhysicalOptions>("PhysicalOptions");
  default_object<crown::io::CachePolicy>("CachePolicy");
  triple<OptionsProfile>("OptionsProfile_nested");
  pair<OperationModes>("OperationModes_member");
  pair<Assumptions>("Assumptions_member");
  pair<OutputAccounting>("OutputAccounting_member");
  pair<ScalarStrings>("ScalarStrings_member");
  {begin();std::vector<std::string> value={"compile_only","reference_storage_initialization"};const auto counts=end();vector_values(value,operation_modes);emit("operation_modes","direct_vector",counts);}
  {begin();std::vector<std::string> value={"single_writer","nonnull_exact_binary_values","ordered_standard_containers"};const auto counts=end();vector_values(value,assumptions);emit("assumptions","direct_vector",counts);}
  {begin();std::vector<std::string> value={"one_action_per_emitted_tuple","retained_snapshots_and_buffers_accounted_separately"};const auto counts=end();vector_values(value,output_accounting);emit("output_accounting","direct_vector",counts);}
  std::puts("default-probe descriptor_checks=passed measured_forms=22 persistent_failures=not_executed");
}catch(const std::exception& error){allocation_probe::measuring=false;std::fprintf(stderr,"default-probe error=%s\n",error.what());return 1;}}
