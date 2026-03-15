cmake_minimum_required(VERSION 3.22)
project(WCMakeBoilerplate
        LANGUAGES C
        VERSION "1.0.0")

set(CMAKE_C_STANDARD 90)

add_subdirectory(WLib)

add_executable(Executable main.c)
target_link_libraries(Executable WLib::WLib)

# install executable to CMAKE_INSTALL_PREFIX during INSTALL target invocation
include(GNUInstallDirs)
install(TARGETS Executable)