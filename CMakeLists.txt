cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----

project(
    Cicero
    VERSION 1.0
    LANGUAGES C
)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

cmake_policy(SET CMP0048 NEW)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Compiler Options ----
include(cmake/CompilerWarnings.cmake)
include(cmake/tools.cmake)

# ---- Add dependencies ----
include(cmake/CPM.cmake)
# set(CPM_SOURCE_CACHE "extern")
set(FETCHCONTENT_BASE_DIR "extern")

CPMUsePackageLock(package-lock.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.6.0")

CPMAddPackage(
    NAME cgreen
    GIT_TAG 1.4.0
    GITHUB_REPOSITORY cgreen-devs/cgreen
    OPTIONS "CGREEN_WITH_UNIT_TESTS OFF" "CMAKE_INSTALL_BINDIR bin"
)

# CPMAddPackage(
#     NAME klib
#     GIT_TAG master
#     GITHUB_REPOSITORY attractivechaos/klib
# )

# ---- Create Library ----
add_library(Cicero
    include/cicero/cicero.h
    include/cicero/mafsa.h
    src/cicero_types.h
    src/cicero_tables.h
    src/init.c
    src/rack.c
    src/movegen.c
    src/score.c
    src/legal.c
    src/mafsabuilder.c
    src/mafsa.c
    src/iconv.h
)
target_compile_features(Cicero PRIVATE c_std_99)
set_c_project_warnings(Cicero)
target_include_directories(
    Cicero PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                  $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
  # DEPENDENCIES "fmt 7.1.3"
)

# ---- Subdirectories ----
add_subdirectory(tests)
