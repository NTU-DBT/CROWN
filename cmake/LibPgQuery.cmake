# Build the pinned libpg_query source archive locally.  Keep this as an
# imported target so upstream's own Makefile remains responsible for compiling
# its generated PostgreSQL source set.
set(_crown_pg_query_archive
    "${CMAKE_CURRENT_LIST_DIR}/../third_party/libpg_query/libpg_query-18.1.0.tar.gz")
set(_crown_pg_query_sha256
    "2d3486cf6a9d3955b53e66235db39d62b54216c820cd392ab66dc842c5b1316d")
file(SHA256 "${_crown_pg_query_archive}" _crown_pg_query_actual_sha256)
if(NOT _crown_pg_query_actual_sha256 STREQUAL _crown_pg_query_sha256)
  message(FATAL_ERROR
    "Vendored libpg_query 18.1.0 archive checksum mismatch: ${_crown_pg_query_actual_sha256}")
endif()

find_program(CROWN_MAKE_EXECUTABLE NAMES gmake make REQUIRED)
execute_process(
  COMMAND "${CROWN_MAKE_EXECUTABLE}" --version
  RESULT_VARIABLE _crown_make_result
  OUTPUT_VARIABLE _crown_make_version
  ERROR_VARIABLE _crown_make_error)
if(NOT _crown_make_result EQUAL 0 OR NOT _crown_make_version MATCHES "GNU Make")
  message(FATAL_ERROR
    "libpg_query requires GNU Make; found '${CROWN_MAKE_EXECUTABLE}'. ${_crown_make_error}")
endif()

find_package(Threads REQUIRED)

set(_crown_pg_query_extract_root "${CMAKE_CURRENT_BINARY_DIR}/_deps/libpg_query")
set(_crown_pg_query_source_dir "${_crown_pg_query_extract_root}/libpg_query-18.1.0")
set(_crown_pg_query_library "${_crown_pg_query_source_dir}/libpg_query.a")
set(_crown_pg_query_header "${_crown_pg_query_source_dir}/pg_query.h")
# CMake validates INTERFACE include directories during generation. Create the
# empty build-tree directory now; the build command replaces it with the
# verified archive contents before a consumer compiles.
file(MAKE_DIRECTORY "${_crown_pg_query_source_dir}")

# Make reconfiguration invalidate the static library when compiler or flags
# change, without causing a rebuild when the generated configuration is
# unchanged.
set(_crown_pg_query_build_config "${CMAKE_CURRENT_BINARY_DIR}/_deps/libpg_query-build-config.txt")
string(CONCAT _crown_pg_query_build_config_content
  "compiler=${CMAKE_C_COMPILER}\n"
  "compiler_arg1=${CMAKE_C_COMPILER_ARG1}\n"
  "compiler_id=${CMAKE_C_COMPILER_ID}\n"
  "compiler_version=${CMAKE_C_COMPILER_VERSION}\n"
  "compiler_target=${CMAKE_C_COMPILER_TARGET}\n"
  "sysroot=${CMAKE_SYSROOT}\n"
  "c_flags=${CMAKE_C_FLAGS}\n"
  "sanitizers=${CROWN_SANITIZERS}\n"
  "make=${CROWN_MAKE_EXECUTABLE}\n")
file(GENERATE OUTPUT "${_crown_pg_query_build_config}" CONTENT "${_crown_pg_query_build_config_content}")

# Recheck the vendored archive at build time as well as configure time, so a
# changed file cannot be silently extracted after this build directory was
# configured.
set(_crown_pg_query_verify_script "${CMAKE_CURRENT_BINARY_DIR}/_deps/verify-libpg-query.cmake")
string(CONCAT _crown_pg_query_verify_contents
  "file(SHA256 [==[${_crown_pg_query_archive}]==] _actual_sha256)\n"
  "if(NOT _actual_sha256 STREQUAL [==[${_crown_pg_query_sha256}]==])\n"
  "  message(FATAL_ERROR \"Vendored libpg_query 18.1.0 archive checksum mismatch at build time\")\n"
  "endif()\n")
file(GENERATE OUTPUT "${_crown_pg_query_verify_script}" CONTENT "${_crown_pg_query_verify_contents}")

# Pass through CMake's C flags and instrument the dependency itself when
# sanitizers are enabled. The upstream Makefile appends its own required flags.
set(_crown_pg_query_cflags "${CMAKE_C_FLAGS}")
if(CMAKE_SYSROOT)
  string(APPEND _crown_pg_query_cflags " --sysroot=${CMAKE_SYSROOT}")
endif()
set(_crown_pg_query_cc "${CMAKE_C_COMPILER}")
if(CMAKE_C_COMPILER_ARG1)
  string(APPEND _crown_pg_query_cc " ${CMAKE_C_COMPILER_ARG1}")
endif()
if(CMAKE_C_COMPILER_TARGET)
  string(APPEND _crown_pg_query_cc " --target=${CMAKE_C_COMPILER_TARGET}")
endif()
if(CROWN_SANITIZERS)
  string(APPEND _crown_pg_query_cflags " -fsanitize=address,undefined -fno-omit-frame-pointer")
endif()
set(_crown_pg_query_make_args
    "${CROWN_MAKE_EXECUTABLE}" -C "${_crown_pg_query_source_dir}" build
    "CC=${_crown_pg_query_cc}")
if(NOT _crown_pg_query_cflags STREQUAL "")
  list(APPEND _crown_pg_query_make_args "CFLAGS=${_crown_pg_query_cflags}")
endif()

add_custom_command(
  OUTPUT "${_crown_pg_query_library}" "${_crown_pg_query_header}"
  COMMAND "${CMAKE_COMMAND}" -P "${_crown_pg_query_verify_script}"
  COMMAND "${CMAKE_COMMAND}" -E rm -rf "${_crown_pg_query_extract_root}"
  COMMAND "${CMAKE_COMMAND}" -E make_directory "${_crown_pg_query_extract_root}"
  COMMAND "${CMAKE_COMMAND}" -E chdir "${_crown_pg_query_extract_root}"
          "${CMAKE_COMMAND}" -E tar xzf "${_crown_pg_query_archive}"
  COMMAND ${_crown_pg_query_make_args}
  # The tarball preserves upstream source timestamps, so refresh the public
  # header timestamp to keep it a stable declared build output.
  COMMAND "${CMAKE_COMMAND}" -E touch "${_crown_pg_query_header}"
  DEPENDS "${_crown_pg_query_archive}" "${CMAKE_CURRENT_LIST_FILE}"
          "${_crown_pg_query_verify_script}" "${_crown_pg_query_build_config}"
  COMMENT "Building pinned libpg_query 18.1.0 from the vendored archive"
  USES_TERMINAL
  VERBATIM)

add_custom_target(_crown_pg_query_build
  DEPENDS "${_crown_pg_query_library}" "${_crown_pg_query_header}")

add_library(crown_pg_query STATIC IMPORTED GLOBAL)
set_target_properties(crown_pg_query PROPERTIES
  IMPORTED_LOCATION "${_crown_pg_query_library}")
target_include_directories(crown_pg_query SYSTEM INTERFACE "${_crown_pg_query_source_dir}")
target_link_libraries(crown_pg_query INTERFACE Threads::Threads)
if(CROWN_SANITIZERS)
  target_link_options(crown_pg_query INTERFACE -fsanitize=address,undefined)
endif()
add_dependencies(crown_pg_query _crown_pg_query_build)
