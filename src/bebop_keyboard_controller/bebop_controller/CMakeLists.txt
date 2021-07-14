add_library(bebop_controller src/bebop_controller.cpp)
target_include_directories(bebop_controller PUBLIC include)
add_subdirectory(test)
