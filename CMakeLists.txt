cmake_minimum_required(VERSION 3.31)

project(
    PMBuddy
    VERSION 0.1.0
    DESCRIPTION "Pac-Man arcade emulator"
    LANGUAGES CXX C
)

# Enable OBJC on macOS so third-party libs like NFD work properly
if(APPLE)
    enable_language(OBJC)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/ProjectConfig.cmake)

include(FetchContent)
# Get fmt library for formatting console output
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        12.2.0
    GIT_SHALLOW    TRUE
)
# Get SDL3 for multimedia functionality
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.16
    GIT_SHALLOW    TRUE
)
# Get NFD for file dialogs
FetchContent_Declare(
    nfd
    GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended.git
    GIT_TAG v1.4.0
    GIT_SHALLOW TRUE
)

# Stop SDL from compiling tests
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(fmt SDL3 nfd)

# Populate project version info in code
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

add_executable(pmbuddy
    src/main.cpp
)

target_link_libraries(pmbuddy
    PRIVATE
        project_sanitizers
        project_warnings
        fmt::fmt
        nfd
        SDL3::SDL3
)

target_include_directories(pmbuddy PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
