add_library(keyboard_hook src/keyboard_hook.cpp)
target_include_directories(keyboard_hook PUBLIC include)
target_link_libraries(keyboard_hook PUBLIC X11)
add_subdirectory(test)
