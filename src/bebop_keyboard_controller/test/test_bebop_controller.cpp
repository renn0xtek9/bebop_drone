#include <bebop_controller.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace bebop_keyboard_controller{

using namespace ::testing;


TEST(TakeOffAndLanding, NoLandingAtStart)
{   
    std::size_t number_of_calls{};
    auto take_off_or_land_callback_mock=[&number_of_calls](){number_of_calls++;};
    BebopController unit(take_off_or_land_callback_mock);
    unit.land();
    EXPECT_EQ(number_of_calls, 1);	
    EXPECT_TRUE(false);
}

}
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
//   ros::init(argc, argv, "tester");
//   ros::NodeHandle nh;
  return RUN_ALL_TESTS();
}
