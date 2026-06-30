find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

add_executable(igrf_tool
    src/gui.cpp
)

target_link_libraries(igrf_tool
    PRIVATE
        ${wxWidgets_LIBRARIES}
)