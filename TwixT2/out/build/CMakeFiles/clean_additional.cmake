# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "TwixT2\\CMakeFiles\\TwixT2_autogen.dir\\AutogenUsed.txt"
  "TwixT2\\CMakeFiles\\TwixT2_autogen.dir\\ParseCache.txt"
  "TwixT2\\TwixT2_autogen"
  )
endif()
