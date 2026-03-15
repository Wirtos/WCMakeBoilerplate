cmake_minimum_required(VERSION 3.22)
project(WLib
        LANGUAGES C
        VERSION "1.0.0"
        DESCRIPTION "TrashGuy C library created to be easily usable from other languages with CFFI support.")

set(CMAKE_C_STANDARD 90)

option(BUILD_SHARED_LIBS "Build as dynamic library" OFF)
option(WLIB_OPTION "Example build option" OFF)
option(WLIB_BUILD_DOCS "Build docs" OFF)

add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET HEADERS
        FILES wlib.h
        PRIVATE
        wlib.c
)

target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:WLIB_STATIC_DEFINE>
        PRIVATE
        # we're building the lib
        WLIB_EXPORTS
        $<$<BOOL:${WLIB_OPTION}>:WLIB_OPTION>
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# install actual compiled binaries produced by WLib library
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        COMPONENT ${PROJECT_NAME}
        FILE_SET HEADERS
)

# install targets' resulting files (WLibTargets.cmake),
# this is where WLib::WLib points to actual library binary files
install(EXPORT ${PROJECT_NAME}Targets
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        NAMESPACE {PROJECT_NAME}::
)

# Generate main config file which can be used in find_package later
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

# Creates a version file which contains our version (1.0.0),
# used in find_package for version requirements
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Version.cmake"
        COMPATIBILITY SameMajorVersion
)

if (WLIB_BUILD_DOCS)
    find_package(Doxygen REQUIRED)

    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doxygen")
    set(DOXYGEN_EXTRACT_STATIC YES)
    doxygen_add_docs(${PROJECT_NAME}_docs
            wlib.c
            wlib.h
            ALL
    )
    install(DIRECTORY "${DOXYGEN_OUTPUT_DIRECTORY}" DESTINATION "${CMAKE_INSTALL_DOCDIR}/${PROJECT_NAME}")
endif ()