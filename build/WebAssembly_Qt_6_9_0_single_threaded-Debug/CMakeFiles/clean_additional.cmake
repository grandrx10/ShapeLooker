# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ShapeLooker_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ShapeLooker_autogen.dir\\ParseCache.txt"
  "ShapeLooker_autogen"
  )
endif()
