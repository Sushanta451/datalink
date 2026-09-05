add_executable(node main.cpp)

target_compile_features(node PRIVATE cxx_std_20)

# The application is the only place the portable core and the host transport
# are joined. Both libraries are otherwise independent.
target_link_libraries(node PRIVATE datalink::datalink datalink::net
                                   project_warnings project_sanitizers)
