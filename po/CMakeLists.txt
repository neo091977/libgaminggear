FILE(GLOB_RECURSE _GETTEXT_SOURCES_REL RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/*.c)

FOREACH(path ${_GETTEXT_SOURCES_REL})
  LIST(APPEND _GETTEXT_SOURCES_ABS ${CMAKE_SOURCE_DIR}/${path})  
ENDFOREACH()

SET(_GETTEXT_MACHINE_OBJECTS)
SET(_GETTEXT_PORTABLE_OBJECTS)

# Build portable object template
# Storing in source, so enduser only has to build .mo files
ADD_CUSTOM_COMMAND(
  # charset in .pot is not set to UTF-8 if sources use only ascii chars.
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.pot
  COMMAND xgettext --default-domain=${CMAKE_PROJECT_NAME}
    --output=${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.pot --sort-output
    --keyword --keyword=_ --keyword=N_ --keyword=C_:1c,2 --keyword=NC_:1c,2
    --from-code=UTF-8 --language=C
    --package-name=${CMAKE_PROJECT_NAME} --package-version=${V_MAJOR}.${V_MINOR}.${V_PATCH}
    ${_GETTEXT_SOURCES_REL}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  DEPENDS ${_GETTEXT_SOURCES_ABS}
)

# Needed to eliminate race condition on parallel builds
ADD_CUSTOM_TARGET(gettext_portable_object_template
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.pot
)

FOREACH(language ${TRANSLATION_LANGUAGES})
  # Build portable object
  ADD_CUSTOM_COMMAND(
    # - Not using --update option for msgmerge because timestamp is not updated
    #   when nothing changed.
    # - Please make sure charset is UTF-8 in .po after msginit.
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${language}.po
    COMMAND
      if [ -e ${CMAKE_CURRENT_SOURCE_DIR}/${language}.po ]\; then
        msgmerge ${CMAKE_CURRENT_SOURCE_DIR}/${language}.po ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.pot --output-file=${CMAKE_CURRENT_SOURCE_DIR}/${language}.po\;
      else
        msginit --locale=${language} --input=${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.pot --output-file=${CMAKE_CURRENT_SOURCE_DIR}/${language}.po\;
      fi
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.pot
  )
  LIST(APPEND _GETTEXT_PORTABLE_OBJECTS ${CMAKE_CURRENT_SOURCE_DIR}/${language}.po)
  
  # Build machine object
  ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${language}.mo
    COMMAND msgfmt ${CMAKE_CURRENT_SOURCE_DIR}/${language}.po --output-file=${CMAKE_CURRENT_BINARY_DIR}/${language}.mo
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${language}.po
  )
  LIST(APPEND _GETTEXT_MACHINE_OBJECTS ${CMAKE_CURRENT_BINARY_DIR}/${language}.mo)

  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${language}.mo
    DESTINATION share/locale/${language}/LC_MESSAGES
    RENAME ${CMAKE_PROJECT_NAME}.mo
  )  
ENDFOREACH()

# Additional target to only update portable objects
ADD_CUSTOM_TARGET(translations
  DEPENDS ${_GETTEXT_PORTABLE_OBJECTS}
)
ADD_DEPENDENCIES(translations gettext_portable_object_template)

ADD_CUSTOM_TARGET(gettext_machine_objects ALL
  DEPENDS ${_GETTEXT_MACHINE_OBJECTS}
)
# Not depending on translations target to allow more parallelism
ADD_DEPENDENCIES(gettext_machine_objects gettext_portable_object_template)

UNSET(_GETTEXT_PORTABLE_OBJECTS)
UNSET(_GETTEXT_MACHINE_OBJECTS)
UNSET(_GETTEXT_SOURCES_ABS)
UNSET(_GETTEXT_SOURCES_REL)
