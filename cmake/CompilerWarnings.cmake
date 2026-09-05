# Reusable warning configuration.
#
# The warnings live on an INTERFACE target instead of CMAKE_CXX_FLAGS so that
# they apply only to targets that opt in. Third-party code pulled in by
# FetchContent shares the same compiler invocation but must not inherit
# -Werror, which a global flag variable would make impossible.

add_library(project_warnings INTERFACE)

set(DATALINK_GCC_CLANG_WARNINGS
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wshadow
    -Wconversion
    -Wsign-conversion)

target_compile_options(
  project_warnings INTERFACE
  "$<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang,AppleClang>:${DATALINK_GCC_CLANG_WARNINGS}>"
)
