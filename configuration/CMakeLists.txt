IF(SQLITE3_FOUND)
  LIST(APPEND ADDITIONAL_REQUIREMENTS sqlite3)
ENDIF()

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/gaminggear.pc.in ${CMAKE_CURRENT_BINARY_DIR}/gaminggear.pc @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/gaminggear.pc
  DESTINATION ${INSTALL_PKGCONFIGDIR}
  RENAME gaminggear-${V_MAJOR}.pc
)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/FindGAMINGGEAR.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/FindGAMINGGEAR.cmake @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/FindGAMINGGEAR.cmake
  DESTINATION ${INSTALL_CMAKE_MODULESDIR}
  RENAME FindGAMINGGEAR${V_MAJOR}.cmake
)
