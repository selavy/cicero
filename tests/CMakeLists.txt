add_executable(tests tests.c)
target_link_libraries(tests
    PUBLIC
        c_project_options
        # c_project_warnings
)
# TODO: add to ctest
