include(FetchContent)

# Pinned to a release tag so CI is reproducible; tracking a branch would let an
# upstream change break an unrelated build.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
  GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(googletest)

# GoogleTest's headers are not built under this project's warning set, so its
# include directories are demoted to SYSTEM; otherwise -Werror would fail on
# third-party code. The SYSTEM property is set directly rather than via
# FetchContent's SYSTEM keyword, which requires CMake 3.25.
foreach(gtest_target gtest gtest_main gmock gmock_main)
  if(TARGET ${gtest_target})
    get_target_property(gtest_includes ${gtest_target}
                        INTERFACE_INCLUDE_DIRECTORIES)
    if(gtest_includes)
      target_include_directories(${gtest_target} SYSTEM
                                 INTERFACE ${gtest_includes})
    endif()
  endif()
endforeach()

include(GoogleTest)

add_executable(test_version test_version.cpp)

target_compile_features(test_version PRIVATE cxx_std_20)

target_link_libraries(
  test_version PRIVATE datalink::datalink datalink::net GTest::gtest_main
                       project_warnings project_sanitizers)

gtest_discover_tests(test_version)
