#include "owner_statistics_fixture.hpp"
#include <iostream>
using namespace owner_fixture;
namespace {
void row(const Row& values){
  std::cout<<'[';bool first=true;
  for(const auto& value:values){if(!first)std::cout<<',';first=false;std::cout<<std::get<std::int64_t>(value);}
  std::cout<<']';
}
void show(const char* label,const PhysicalPlan& p,const Database& db){
  std::cout<<"fixture="<<label<<" plan="<<p.physical_sha256()<<'\n';
  std::cout<<"maximal_connex=";for(auto id:p.validation().maximal_connex)std::cout<<id.value<<',';std::cout<<'\n';
  auto runtime=PhysicalRuntime::initialize(p,db);
  const auto canonical=runtime.canonical_state();
  stats::OwnerRequest request;
  for(const auto& node:p.nodes()){
    std::cout<<"node="<<node.id.value<<" kind="<<(node.kind==NodeKind::generalized?"generalized":"native")<<" connex="<<node.connex<<" E="<<node.visible_relation.has_value()<<" scope=";
    for(auto v:node.scope)std::cout<<v.value<<',';
    std::cout<<" separator=";for(const auto& field:node.parent_key.target().fields())if(field.variable)std::cout<<field.variable->value<<',';
    std::cout<<'\n';
    std::vector<FieldId> fields;for(std::size_t i=0;i<node.layout.fields().size();++i)fields.push_back(FieldId{i});
    request.selections.push_back({stats::NodeScope{node.id,SupportRole::records},fields});
    request.selections.push_back({stats::NodeScope{node.id,SupportRole::survivors},fields});
    request.selections.push_back({stats::NodeScope{node.id,SupportRole::parent_support},{}});
    request.selections.push_back({stats::NodeScope{node.id,SupportRole::visible},{}});
  }
  for(const auto& node:canonical.support.nodes){
    std::cout<<"canonical node="<<node.node.value<<" records=";
    for(const auto& record:node.records){row(record.values);std::cout<<' ';}
    std::cout<<" S=";for(const auto& value:node.survivors){row(value);std::cout<<' ';}
    std::cout<<" P=";for(const auto& value:node.parent){row(value.key);std::cout<<':'<<value.count<<' ';}
    std::cout<<" E=";
    if(node.visible)for(const auto& value:*node.visible){row(value.key);std::cout<<':'<<value.count<<' ';}
    else std::cout<<"not_applicable";
    std::cout<<'\n';
  }
  const auto captured=runtime.capture_statistics(request);
  for(const auto& component:captured.components()){
    const auto scope=std::get<stats::NodeScope>(component.selection.scope);
    std::cout<<"capture node="<<scope.node.value<<" role="<<static_cast<int>(scope.role)<<" availability="<<static_cast<int>(component.availability)<<" cardinality=";
    if(component.cardinality)std::cout<<*component.cardinality;else std::cout<<"unknown";
    std::cout<<" keys=";
    if(component.distribution && component.distribution->heavy_keys)
      for(const auto& key:*component.distribution->heavy_keys){row(key.key);std::cout<<':'<<key.count<<' ';}
    else std::cout<<"unknown";
    std::cout<<'\n';
  }
}
}
int main(){
  show("original_output_separators",plan(true),database());
  show("separate_hidden_separator",hidden_separator_plan(),hidden_separator_database());
}
