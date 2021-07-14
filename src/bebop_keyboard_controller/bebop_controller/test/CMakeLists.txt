add_executable(test_bebop_controller test_bebop_controller.cpp)
target_link_libraries(test_bebop_controller PRIVATE bebop_controller gtest)
add_test(NAME test_bebop_controller COMMAND test_bebop_controller )

# if (CATKIN_ENABLE_TESTING)
#   catkin_add_gtest(test_bebop_controller test_bebop_controller.cpp)
#   target_link_libraries(test_bebop_controller bebop_controller ${catkin_LIBRARIES})
# endif()
