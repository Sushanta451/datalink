add_library(net STATIC src/version.cpp)
add_library(datalink::net ALIAS net)

target_include_directories(
  net PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_features(net PUBLIC cxx_std_20)

# net is host-only POSIX transport code. It links no other project library:
# the protocol core stays above it, and the two are joined only by an
# application. Keeping this list free of `datalink` prevents a cycle and keeps
# the dependency direction one-way.
target_link_libraries(net PRIVATE project_warnings project_sanitizers)
