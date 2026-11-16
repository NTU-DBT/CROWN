#pragma once

#include "crown/io/document.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <initializer_list>
#include <set>

namespace crown::io::detail {
[[noreturn]] inline void fail(const std::string& path, const std::string& message) {
  throw Error("invalid_document", path + ": " + message);
}
inline void fields(const Json& value, const std::string& path,
                   std::initializer_list<std::string_view> required,
                   std::initializer_list<std::string_view> optional = {}) {
  if (!value.is_object()) fail(path, "expected object");
  for (auto name : required) if (!value.contains(name)) fail(path, "missing field " + std::string(name));
  for (const auto& [name, unused] : value.items()) {
    static_cast<void>(unused);
    if (std::find(required.begin(), required.end(), name) == required.end() &&
        std::find(optional.begin(), optional.end(), name) == optional.end()) fail(path, "unknown field " + name);
  }
}
inline const Json::array_t& array(const Json& value, std::string_view path) {
  if (!value.is_array()) fail(std::string(path), "expected array");
  return value.get_ref<const Json::array_t&>();
}
inline std::string string(const Json& value, const std::string& path) {
  if (!value.is_string()) fail(path, "expected string");
  return value.get<std::string>();
}
inline std::uint64_t unsigned_integer(const Json& value, const std::string& path) {
  if (!value.is_number_integer() || (!value.is_number_unsigned() && value.get<std::int64_t>() < 0)) fail(path, "expected unsigned 64-bit integer");
  return value.get<std::uint64_t>();
}
inline void version(const Json& value, const std::string& path, std::uint64_t expected = 1) {
  if (unsigned_integer(value, path) != expected) throw Error("unsupported_version", path + ": expected schema_version " + std::to_string(expected));
}
inline Json parse_json(std::string_view text) {
  // DOM and duplicate-key sets allocate ordinary memory; depth is the only size cap here.
  try {
    std::vector<std::set<std::string>> object_keys;
    const auto callback = [&object_keys](int depth, Json::parse_event_t event, Json& parsed) {
      if (depth > 256) throw Error("resource_limit", "JSON nesting exceeds operational limit of 256");
      if (event == Json::parse_event_t::object_start) object_keys.emplace_back();
      if (event == Json::parse_event_t::key && !object_keys.back().insert(parsed.get<std::string>()).second) {
        throw Error("invalid_document", "duplicate object key: " + parsed.get<std::string>());
      }
      if (event == Json::parse_event_t::object_end) object_keys.pop_back();
      return true;
    };
    return Json::parse(text, callback);
  } catch (const Json::exception& error) {
    throw Error("invalid_document", error.what());
  }
}
}  // namespace crown::io::detail
