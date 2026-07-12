find_package(wxWidgets QUIET COMPONENTS core base adv)

if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
else()
    include(FetchContent)

    set(wxBUILD_SAMPLES OFF CACHE BOOL "Build wxWidgets samples")
    set(wxBUILD_TESTS OFF CACHE BOOL "Build wxWidgets tests")

    FetchContent_Declare(
        wxWidgets
        GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
        GIT_TAG v3.2.8.1
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(wxWidgets)
endif()

add_executable(igrf_tool
    src/gui.cpp
    src/main_frame.hpp
    src/main_frame.cpp
)

if(wxWidgets_FOUND)
    target_link_libraries(igrf_tool PRIVATE ${wxWidgets_LIBRARIES})
else()
    target_link_libraries(igrf_tool PRIVATE wx::core wx::base wx::adv)
endif()

add_custom_command(
    TARGET igrf_tool
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/exe"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:igrf_tool>"
            "${CMAKE_SOURCE_DIR}/exe/$<TARGET_FILE_NAME:igrf_tool>"
    COMMENT "Copying igrf_tool to ${CMAKE_SOURCE_DIR}/exe"
)
