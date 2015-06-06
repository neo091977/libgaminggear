# Stefan Achatz 2015
#
# Tries to find location of uhid dev.
# uhid module has to be loaded, or default is taken
# Following vairables are set:
#
# UHIDDIR
#
# Does nothing if UHIDDIR is already set.

IF(UHIDDIR)
  MESSAGE(STATUS "Uhid was set to ${UHIDDIR}")
ELSE()
  FIND_PATH(UHIDDIR uhid
    HINTS
      /dev
      /dev/hid
  )
  
  IF(UHIDDIR)
    MESSAGE(STATUS "Uhid found in ${UHIDDIR}")
  ELSE()
    SET(UHIDDIR "/dev")
    MESSAGE(STATUS "Uhid not found. Using default ${UHIDDIR}")
  ENDIF()
  
  SET(UHIDDIR "${UHIDDIR}" CACHE PATH "" FORCE)
ENDIF()
