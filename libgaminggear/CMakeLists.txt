SET(SOURCES
  gaminggear_configuration.c
  gaminggear_evdev.c
  gaminggear_helper.c
  gaminggear_key_file.c
  gaminggear_key_translations.c
  gaminggear_libusb.c
  gaminggear_macro_keystrokes.c
  gaminggear_macro_thread.c
  gaminggear_macro_threads.c
  gaminggear_macro.c
  gaminggear_macros.c
  macros_converter_roccat_arvo.c
  macros_converter_roccat_kone.c
  macros_converter_roccat_valo.c
  macros_converter_roccat.c
)

IF(SQLITE3_FOUND)
  SET(SOURCES ${SOURCES}
    macros_converter_steelseries_engine3.c
  )
ENDIF(SQLITE3_FOUND)

ADD_LIBRARY (libgaminggear SHARED ${SOURCES})

ADD_DEPENDENCIES(libgaminggear
  generated_headers
)

TARGET_LINK_LIBRARIES(libgaminggear
  ${USB1_LIBRARIES}
  ${GLIB2_LIBRARIES}
  ${SQLITE3_LIBRARIES}
)

SET_TARGET_PROPERTIES(libgaminggear
  PROPERTIES
    VERSION ${V_MAJOR}.${V_MINOR}.${V_MICRO}
    SOVERSION ${V_MAJOR}
    OUTPUT_NAME gaminggear
    COMPILE_FLAGS "-DG_LOG_DOMAIN=\\\"GamingGear\\\""
)

INSTALL(TARGETS libgaminggear DESTINATION ${INSTALL_LIBDIR}/gaminggear-${V_MAJOR})
