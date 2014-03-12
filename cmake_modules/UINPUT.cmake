# Stefan Achatz 2013
#
# Tries to find location of uinput dev.
# uinput module has to be loaded, or default is taken
# Following vairables are set:
#
# UINPUTDIR
#
# Does nothing if UINPUTDIR is already set.

IF(UINPUTDIR)
  MESSAGE(STATUS "Uinput was set to ${UINPUTDIR}")
ELSE()
  FIND_PATH(UINPUTDIR uinput
    HINTS
      /dev
      /dev/input
  )
  
  IF(UINPUTDIR)
    MESSAGE(STATUS "Uinput found in ${UINPUTDIR}")
  ELSE()
    SET(UINPUTDIR "/dev")
    MESSAGE(STATUS "Uinput not found. Using default ${UINPUTDIR}")
  ENDIF()
  
  SET(UINPUTDIR "${UINPUTDIR}" CACHE PATH "" FORCE)
ENDIF()
