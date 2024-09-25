# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FirstQT_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FirstQT_autogen.dir\\ParseCache.txt"
  "FirstQT_autogen"
  )
endif()
