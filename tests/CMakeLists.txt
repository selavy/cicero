add_executable(cgreen-first cgreen-first.c)
target_link_libraries(cgreen-first
    PUBLIC
        Cicero
        ${CGREEN_SHARED_LIBRARY}
)
target_include_directories(
    cgreen-first
    PUBLIC
    ${CGREEN_PUBLIC_INCLUDE_DIRS}
)
target_compile_features(cgreen-first PUBLIC c_std_99)
