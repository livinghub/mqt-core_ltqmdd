#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "JKQ::qfr" for configuration "Debug"
set_property(TARGET JKQ::qfr APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(JKQ::qfr PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libqfr.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS JKQ::qfr )
list(APPEND _IMPORT_CHECK_FILES_FOR_JKQ::qfr "${_IMPORT_PREFIX}/lib/libqfr.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
