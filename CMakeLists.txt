cmake_minimum_required(VERSION 3.17)

project(Cicero C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

include(cmake/CompilerWarnings.cmake)
# add_library(cxx_project_warnings INTERFACE)
add_library(c_project_warnings   INTERFACE)
# set_cxx_project_warnings(cxx_project_warnings)
set_c_project_warnings(c_project_warnings)

# add_library(cxx_project_options INTERFACE)
add_library(c_project_options   INTERFACE)
# target_compile_features(cxx_project_options INTERFACE cxx_std_17)
target_compile_features(c_project_options   INTERFACE c_std_99)
include(cmake/Sanitizers.cmake)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("-- enabling sanitizers")
    # enable_sanitizers(cxx_project_options)
    enable_sanitizers(c_project_options)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_library(Cicero
    include/cicero/cicero.h
    src/cicero_types.h
    src/cicero_tables.h
    src/init.c
    src/rack.c
    src/movegen.c
    src/score.c
    src/legal.c
)
target_link_libraries(Cicero
    PRIVATE
    c_project_options
    # c_project_warnings
)
target_include_directories(Cicero PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)
