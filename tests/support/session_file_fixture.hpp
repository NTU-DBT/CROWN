#pragma once

#include "crown/recovery/session_file.hpp"
#include "session_checkpoint_test_fixture.hpp"
#include "window_checkpoint_test_fixture.hpp"
#include <array>
#include <filesystem>
#include <fstream>
#include <unistd.h>

namespace crown::session_file_test {
namespace typed=session_checkpoint_test;
namespace window=window_checkpoint_test;
using typed::check;
// Uncopied lexical test owner; recursive cleanup is best effort, not an OOM guarantee.
struct Directory {
  std::string name;
  Directory() {
    std::array<char,64> pattern{};constexpr std::string_view prefix="/tmp/crown-checkpoint-XXXXXX";
    std::copy(prefix.begin(),prefix.end(),pattern.begin());const auto path=::mkdtemp(pattern.data());
    check(path!=nullptr,"temporary checkpoint directory creation failed");name=path;
  }
  ~Directory(){std::error_code error;std::filesystem::remove_all(name,error);}
  [[nodiscard]] std::string file(std::string_view leaf="state.crown") const {return name+"/"+std::string(leaf);}
};
inline std::string contents(const std::string& path) {
  std::ifstream input(path,std::ios::binary);return {std::istreambuf_iterator<char>(input),std::istreambuf_iterator<char>()};
}
inline std::size_t descriptors() {
  std::size_t count=0;for(const auto& entry:std::filesystem::directory_iterator("/proc/self/fd")){static_cast<void>(entry);++count;}return count;
}
inline std::size_t temporaries(const Directory& directory) {
  std::size_t count=0;for(const auto& entry:std::filesystem::directory_iterator(directory.name))
    if(entry.path().filename().native().starts_with(".crown-checkpoint-"))++count;
  return count;
}
inline void remove_temporaries(const Directory& directory) {
  for(const auto& entry:std::filesystem::directory_iterator(directory.name))
    if(entry.path().filename().native().starts_with(".crown-checkpoint-"))std::filesystem::remove(entry.path());
}
// Images own funded byte vectors; copying images can allocate and duplicate bytes.
struct Pair {
  typed::Case test;
  CompiledProgram compiler;
  runtime::QuerySession::Owner source;
  Database database;
  recovery::SessionImage old_image,new_image;
  explicit Pair(bool indexed):test(typed::fixture(indexed,1)),compiler(CompiledProgram::standalone(test.plan)),
      source(runtime::QuerySession::create_typed(test.plan)) {
    database.tables.resize(1);source->start();typed::step(*source,test,database,test.updates[0],runtime::DeltaMode::delta);
    old_image=source->checkpoint_image();typed::step(*source,test,database,test.updates[1],runtime::DeltaMode::delta);new_image=source->checkpoint_image();
  }
};
} // namespace crown::session_file_test
