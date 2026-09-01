add_executable(basic_window basic_window.cpp)

target_link_libraries(basic_window PRIVATE ooray)

set_target_properties(basic_window PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
)