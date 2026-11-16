include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(_crown_public_targets crown_options crown_json crown_core crown_sql crown_sql_rows crown_sql_aggregate crown_sql_aggregate_runtime crown_sql_aggregate_recovery crown_aggregate crown_plan
  crown_runtime crown_queries crown_query_explain crown_explain crown_ranking crown_selection crown_meta_candidates
  crown_ranking_runtime crown_selection_runtime crown_indexed crown_storage_table
  crown_accounted_indexed crown_accounted_storage_table crown_accounted_plan_storage)
foreach(_crown_target IN LISTS _crown_public_targets)
  string(REGEX REPLACE "^crown_" "" _crown_export_name "${_crown_target}")
  set_target_properties(${_crown_target} PROPERTIES EXPORT_NAME "${_crown_export_name}")
  if(NOT TARGET CROWN::${_crown_export_name})
    add_library(CROWN::${_crown_export_name} ALIAS ${_crown_target})
  endif()
endforeach()
target_compile_features(crown_core PUBLIC cxx_std_23)
install(TARGETS ${_crown_public_targets} EXPORT CrownTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS crown RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES "${_crown_pg_query_library}" DESTINATION "${CMAKE_INSTALL_LIBDIR}/crown/deps")
install(DIRECTORY include/crown DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES third_party/nlohmann/json.hpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/nlohmann")
install(FILES third_party/nlohmann/LICENSE.MIT DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/licenses/nlohmann")
install(DIRECTORY third_party/nlohmann/patches/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/patches/nlohmann")
install(DIRECTORY third_party/libpg_query/notices/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/licenses/libpg_query")
configure_package_config_file(cmake/CrownConfig.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/CrownConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Crown"
  PATH_VARS CMAKE_INSTALL_LIBDIR)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/CrownConfigVersion.cmake"
  VERSION ${PROJECT_VERSION} COMPATIBILITY SameMinorVersion)
install(EXPORT CrownTargets NAMESPACE CROWN:: DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Crown")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/CrownConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/CrownConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Crown")

install(DIRECTORY schemas/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/schemas" FILES_MATCHING PATTERN "*.json")

install(DIRECTORY examples/native-workflow/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/native-workflow")
install(DIRECTORY examples/cost-calibration/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/cost-calibration")
install(DIRECTORY examples/workload-measurement/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/workload-measurement")
install(DIRECTORY examples/ranking-evaluation/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/ranking-evaluation")
install(DIRECTORY examples/reoptimization/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/reoptimization")
install(DIRECTORY examples/meta-candidates/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/meta-candidates")
install(DIRECTORY examples/component-planning/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/component-planning")
install(DIRECTORY examples/component-runtime/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/component-runtime")
install(DIRECTORY examples/independent-queries/ DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/independent-queries")
install(FILES tools/support/ComponentReplay.scala DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/component-runtime")

install(FILES tools/prepare_workflow_input.py DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/examples/native-workflow")

install(FILES docs/cli.md docs/sql_aggregate_input.md DESTINATION "${CMAKE_INSTALL_DATADIR}/crown/docs")
