SET(pwd ${CMAKE_CURRENT_LIST_DIR})

SET(src "")
AUX_SOURCE_DIRECTORY(${pwd} src)
add_executable(supermario ${src})
message(STATUS "supermario added ${src}")

target_link_libraries(supermario ${stdgl_libraries})
