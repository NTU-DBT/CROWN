#pragma once
#include "tick_clock.hpp"
#include "native_request.hpp"
#include <charconv>
#include <filesystem>
#include <fstream>
#include <map>
#include <string_view>
#include <zlib.h>
#include <memory>

namespace {
using namespace crown;
using namespace component;
using Clock = paper_clock::TickClock;  // tick_clock.hpp: cheap per-phase timers
using paper_clock::nanos;
std::int64_t integer(std::string_view text) {
  std::int64_t value{};
  const auto [end,error] = std::from_chars(text.data(),text.data()+text.size(),value);
  require(error==std::errc{} && end==text.data()+text.size(),"invalid input integer");
  return value;
}
struct Input {
  bool enumerate{};
  SetOperation operation{};
  TableId table{};
  Row values;
  std::string tag;
};
// Decodes one input line into `result`, reusing its value and tag storage
// (the replay loops decode every line into one Input).
void decode(const std::string& line, const std::map<std::string,TableId>& tables,
            const std::string& format, TableId graph, Input& result) {
  result.enumerate=false;
  if (format.size()==9 && format=="graph_csv") {
    if (line.size()==1 && line[0]=='*') { result.enumerate=true; return; }
    require(line.size()>4 && line[1]==',' && (line[0]=='+' || line[0]=='-'),"invalid graph stream record");
    const auto separator=line.find(',',2);
    require(separator!=std::string::npos && line.find(',',separator+1)==std::string::npos,"invalid graph pair");
    result.operation=line[0]=='+' ? SetOperation::insert : SetOperation::erase;
    result.table=graph;
    result.values.resize(2);
    result.values[0]=integer(std::string_view(line).substr(2,separator-2));
    result.values[1]=integer(std::string_view(line).substr(separator+1));
    return;
  }
  result.values.clear(); result.tag.clear();
  if(format=="tagged_csv") {
    if(line=="*") { result.enumerate=true; return; }
    require(line.size()>4 && line[1]==',' && (line[0]=='+' || line[0]=='-'),"invalid tagged CSV record");
    result.operation=line[0]=='+' ? SetOperation::insert : SetOperation::erase;
    const auto separator=line.find(',',2);
    require(separator!=std::string::npos,"missing tagged CSV values");
    result.tag.assign(line,2,separator-2);
    std::size_t begin=separator+1;
    for(;;) {
      const auto end=line.find(',',begin);
      result.values.emplace_back(integer(std::string_view(line).substr(begin,end==std::string::npos?end:end-begin)));
      if(end==std::string::npos) break;
      begin=end+1;
    }
    return;
  }
  require(format=="jsonl","unknown paper input format");
  const auto value=io::read_json(line);
  if (value.value("enumerate",false)) { result.enumerate=true; return; }
  const auto name=value.at("table").get<std::string>();
  const auto found=tables.find(name); require(found!=tables.end(),"unknown input table");
  result.table=found->second;
  const auto operation=value.at("operation").get<std::string>();
  require(operation=="+" || operation=="-","invalid input operation");
  result.operation=operation=="+" ? SetOperation::insert : SetOperation::erase;
  for (const auto& cell:value.at("values")) result.values.push_back(io::read_scalar(cell));
}
Input decode(const std::string& line, const std::map<std::string,TableId>& tables,
             const std::string& format, TableId graph) {
  Input result; decode(line,tables,format,graph,result); return result;
}

class GzipBuffer : public std::streambuf {
  gzFile file_{};
  std::array<char,65536> buffer_{};
 protected:
  int_type underflow() override {
    if(gptr()!=egptr()) return traits_type::to_int_type(*gptr());
    const auto count=gzread(file_,buffer_.data(),static_cast<unsigned>(buffer_.size()));
    require(count>=0,"gzip input read failed");
    if(!count) return traits_type::eof();
    setg(buffer_.data(),buffer_.data(),buffer_.data()+count);
    return traits_type::to_int_type(*gptr());
  }
 public:
  explicit GzipBuffer(const char* path) : file_(gzopen(path,"rb")) { require(file_,"cannot open gzip input"); }
  ~GzipBuffer() override { if(file_) gzclose(file_); }
};


} // namespace
