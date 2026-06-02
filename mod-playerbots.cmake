# Optional integration with mod-individual-progression (IP-aware autogear)
list(FIND MODULE_LIST__ "mod-individual-progression" PLAYERBOTS_IP_MODULE_INDEX)
if(NOT PLAYERBOTS_IP_MODULE_INDEX EQUAL -1)
  target_compile_definitions(modules PRIVATE PLAYERBOTS_HAS_INDIVIDUAL_PROGRESSION)
  target_include_directories(modules PRIVATE
    "${CMAKE_SOURCE_DIR}/modules/mod-individual-progression/src")
  message(STATUS "  |  * mod-playerbots: Individual Progression autogear integration enabled")
endif()
