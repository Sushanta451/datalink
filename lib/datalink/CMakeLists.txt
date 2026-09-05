add_library(datalink STATIC src/version.cpp)
add_library(datalink::datalink ALIAS datalink)

# PUBLIC: the include path is part of the library's contract, so anything that
# links datalink can resolve <datalink/...> without restating the path.
target_include_directories(
  datalink PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# PUBLIC: headers use C++20 constructs, so the requirement propagates to
# consumers rather than being satisfied only while compiling this library.
target_compile_features(datalink PUBLIC cxx_std_20)

# PRIVATE: warning and sanitizer settings are build details of this target and
# must not be forced onto consumers.
#
# datalink is the portable protocol core and is intended to build freestanding
# for bare-metal targets. It deliberately links no other project library --
# in particular not `net`, which is host-only POSIX code. Adding a dependency
# here is what would break the port, so this list is the enforcement point.
target_link_libraries(datalink PRIVATE project_warnings project_sanitizers)
