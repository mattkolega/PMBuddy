add_library(common STATIC
    fs.cpp
)

target_link_libraries(common
    PRIVATE
        project_sanitizers
        project_warnings
        fmt::fmt
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

option(PMBUDDY_DEBUG OFF)
if(PMBUDDY_DEBUG)
    target_compile_definitions(common PUBLIC PMBUDDY_DEBUG)
endif()
