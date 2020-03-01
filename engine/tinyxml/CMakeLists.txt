cmake_minimum_required(VERSION 2.8)

project(tinyxml)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(tinyxml
  tinystr.cpp
  tinyxml.cpp
  tinyxmlerror.cpp
  tinyxmlparser.cpp
)
list(APPEND PUBLIC_HEADERS tinyxml.h)
list(APPEND PUBLIC_HEADERS tinystr.h)
set_target_properties(tinyxml PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

install(TARGETS tinyxml
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  FRAMEWORK DESTINATION "Library/Frameworks"
  PUBLIC_HEADER DESTINATION include
)
