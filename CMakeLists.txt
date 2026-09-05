cmake_minimum_required(VERSION 3.20)

project(
  datalink
  VERSION 0.1.0
  DESCRIPTION "TDMA mesh network protocol library"
  LANGUAGES CXX)

# Only the top-level build owns global switches such as testing and the
# compile-command database; when this project is consumed via add_subdirectory
# those decisions belong to the enclosing build.
if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  option(DATALINK_BUILD_TESTS "Build the datalink test suite" ON)
else()
  option(DATALINK_BUILD_TESTS "Build the datalink test suite" OFF)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerWarnings)

# Sanitizers are an INTERFACE target rather than a global flag so that a
# consumer embedding this project is never forced into an instrumented build.
# The generator expression keeps the flags out of Release and RelWithDebInfo
# even under multi-config generators, where CMAKE_BUILD_TYPE is empty.
add_library(project_sanitizers INTERFACE)

# Cross builds target bare metal, where the sanitizer runtimes do not exist.
if(NOT CMAKE_CROSSCOMPILING)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(DATALINK_SANITIZER_FLAGS -fsanitize=address,undefined
                                 -fno-omit-frame-pointer)
    target_compile_options(
      project_sanitizers INTERFACE
      "$<$<CONFIG:Debug>:${DATALINK_SANITIZER_FLAGS}>")
    target_link_options(
      project_sanitizers INTERFACE
      "$<$<CONFIG:Debug>:${DATALINK_SANITIZER_FLAGS}>")
  endif()
endif()

add_subdirectory(lib/datalink)
add_subdirectory(lib/net)
add_subdirectory(apps/node)

if(DATALINK_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
