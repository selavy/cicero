# add_executable(cgreen-first cgreen-first.c)
# target_link_libraries(cgreen-first
#     PUBLIC
#         Cicero
#         ${CGREEN_SHARED_LIBRARY}
# )
# target_include_directories(
#     cgreen-first
#     PUBLIC
#     ${CGREEN_PUBLIC_INCLUDE_DIRS}
# )
# target_compile_features(cgreen-first PUBLIC c_std_99)

add_library(legal_moves_test SHARED legal_moves_test.c)
target_link_libraries(legal_moves_test
    PUBLIC
        Cicero
        ${CGREEN_SHARED_LIBRARY}
)
target_include_directories(
    legal_moves_test
    PUBLIC
    ${CGREEN_PUBLIC_INCLUDE_DIRS}
)
target_compile_features(legal_moves_test PUBLIC c_std_99)

add_library(mafsa_builder_test SHARED mafsa_builder_test.c)
target_link_libraries(mafsa_builder_test
    PUBLIC
        Cicero
        ${CGREEN_SHARED_LIBRARY}
)
target_include_directories(
    mafsa_builder_test
    PUBLIC
    ${CGREEN_PUBLIC_INCLUDE_DIRS}
)
target_compile_features(mafsa_builder_test PUBLIC c_std_99)

configure_file(
    run_tests.sh.in
    run_tests.sh
)
