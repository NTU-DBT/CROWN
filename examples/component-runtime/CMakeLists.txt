cmake_minimum_required(VERSION 3.25)
project(crown_component_runtime LANGUAGES CXX)
find_package(Crown 0.1 CONFIG REQUIRED)

foreach(_component IN ITEMS set rows session aggregate)
  if(_component STREQUAL "set")
    set(_source native_set.cpp)
  elseif(_component STREQUAL "rows")
    set(_source native_rows.cpp)
  else()
    set(_source "${_component}.cpp")
  endif()
  add_executable("crown_component_${_component}" "${_source}")
  set_target_properties("crown_component_${_component}" PROPERTIES CXX_EXTENSIONS OFF)
  if(_component STREQUAL "aggregate")
    target_link_libraries("crown_component_${_component}" PRIVATE CROWN::sql_aggregate_runtime)
  elseif(_component STREQUAL "rows")
    target_link_libraries("crown_component_${_component}" PRIVATE CROWN::sql_rows)
  else()
    target_link_libraries("crown_component_${_component}" PRIVATE CROWN::runtime)
  endif()
  target_compile_options("crown_component_${_component}" PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror)
endforeach()

# The optional observer links separately qualified original libraries unchanged.
# Its source, build and fmt paths are explicit so no baseline is fetched here.
set(CROWN_LEGACY_CPP_SOURCE "" CACHE PATH "Pinned DynaGox dynagox_cpp/implement source")
set(CROWN_LEGACY_CPP_BUILD "" CACHE PATH "Qualified original C++ baseline build")
set(CROWN_LEGACY_FMT_SOURCE "" CACHE PATH "Pinned fmt source used by that baseline")
if(CROWN_LEGACY_CPP_SOURCE AND CROWN_LEGACY_CPP_BUILD AND CROWN_LEGACY_FMT_SOURCE)
  add_executable(crown_component_legacy_cpp legacy_cpp.cpp)
  set_target_properties(crown_component_legacy_cpp PROPERTIES CXX_EXTENSIONS OFF)
  target_include_directories(crown_component_legacy_cpp SYSTEM PRIVATE
    "${CROWN_LEGACY_CPP_SOURCE}/experiments/include" "${CROWN_LEGACY_CPP_SOURCE}/experiments/include/crown"
    "${CROWN_LEGACY_CPP_SOURCE}/multi_hash_map/include" "${CROWN_LEGACY_CPP_SOURCE}/utils/include"
    "${CROWN_LEGACY_FMT_SOURCE}/include")
  target_link_libraries(crown_component_legacy_cpp PRIVATE CROWN::core CROWN::json
    "${CROWN_LEGACY_CPP_BUILD}/experiments/libcrown_lib.a"
    "${CROWN_LEGACY_CPP_BUILD}/utils/libutils.a" "${CROWN_LEGACY_CPP_BUILD}/_deps/fmt-build/libfmt.a")
  target_compile_options(crown_component_legacy_cpp PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror)
endif()
