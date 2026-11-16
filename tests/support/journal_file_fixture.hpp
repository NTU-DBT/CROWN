#pragma once
#include "crown/recovery/journal_file.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>
namespace crown::journal_file_test {
namespace jp=recovery::journal;
inline void check(bool condition,const char* message){if(!condition)throw std::runtime_error(message);}
// Borrowed view: keep Encoded alive; converting it to string copies ordinary bytes.
inline std::string_view bytes(const jp::Encoded& value){return {value.bytes.data(),value.bytes.size()};}
// Use one uncopied lexical owner; implicit copies duplicate the cleanup pathname.
struct Directory {
  std::string name;
  Directory(){char path[]="/tmp/crown-journal-XXXXXX";const auto result=::mkdtemp(path);check(result!=nullptr,"mkdtemp failed");name=result;}
  ~Directory(){std::error_code error;std::filesystem::remove_all(name,error);}
  std::string file(std::string_view leaf="state.wal") const {return name+"/"+std::string(leaf);}
};
// Stream flags are unchecked here; callers inspect/assert the resulting fixture bytes.
inline std::string contents(const std::string& path){std::ifstream f(path,std::ios::binary);return {std::istreambuf_iterator<char>(f),{}};}
inline void put(const std::string& path,std::string_view data){std::ofstream f(path,std::ios::binary|std::ios::trunc);f.write(data.data(),static_cast<std::streamsize>(data.size()));check(static_cast<bool>(f),"fixture write failed");}
inline std::size_t descriptors(){std::size_t n=0;for(const auto& e:std::filesystem::directory_iterator("/proc/self/fd")){static_cast<void>(e);++n;}return n;}
inline std::size_t temporaries(const Directory& directory){std::size_t n=0;for(const auto& e:std::filesystem::directory_iterator(directory.name))if(e.path().filename().native().starts_with(".crown-journal-"))++n;return n;}
inline std::string fixture(const std::string& directory,const char* leaf) {
  std::ifstream f(directory+"/"+leaf+".hex");std::string text,result;f>>text;check(!text.empty() && text.size()%2==0,"missing journal fixture");
  constexpr std::string_view digits="0123456789abcdef";result.reserve(text.size()/2);
  for(std::size_t k=0;k<text.size();k+=2){const auto a=digits.find(text[k]),b=digits.find(text[k+1]);check(a<16 && b<16,"bad fixture hex");result.push_back(static_cast<char>(a*16+b));}return result;
}
// Frozen header/input, but commit uses the production encoder and is not independent.
struct Frames {
  std::string header,input,commit;
  jp::Header binding;
  explicit Frames(const std::string& directory):header(fixture(directory,"header")),input(fixture(directory,"physical-input")),binding(jp::inspect(header).header) {
    jp::Commit decision;decision.input_ordinal=1;decision.input_sha256=jp::inspect(input).body_sha256;decision.physical_sequence=1;decision.command_sequence=1;
    auto account=resource::MemoryAccount::create(1024*1024);const auto encoded=jp::encode(account,2,jp::PayloadView{decision});commit=bytes(encoded);
  }
};
} // namespace crown::journal_file_test
