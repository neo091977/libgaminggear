CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

ADD_CUSTOM_COMMAND(
  OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
  COMMAND doxygen
  DEPENDS
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

ADD_CUSTOM_TARGET(documentation ALL
  DEPENDS
    ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
)

INSTALL(
  FILES
    evdev.h
    gaminggear_hscale.h
    gaminggear_macro_dialog.h
    gaminggear_macro_editor_dialog.h
    gaminggear_text_dialog.h
    gaminggear_timeout_bar.h
    gaminggear_timeout_dialog.h
    gaminggear_xy_scales.h
	${CMAKE_CURRENT_BINARY_DIR}/gaminggear.h
    gdk_key_translations.h
    hid_uid.h
    key_translations.h
    libusb.h
    macro.h
    macro_threads.h
    threads.h
  DESTINATION include/gaminggear-${V_MAJOR}/gaminggear
)

INSTALL(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
  DESTINATION share/gaminggear
)
