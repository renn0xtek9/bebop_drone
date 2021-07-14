#include <bebop_controller.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace bebop_keyboard_controller{





TEST(TakeOffAndLanding, NoLandingAtStart)
{   
    MOCK_METHOD0(void, take_of_or_land,());
    // auto take_off_or_land_callback=[](){};
    BebopController unit(take_of_or_land);
    unit.land();
    EXPECT_EQ(1000, 10);	
}

}
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
//   ros::init(argc, argv, "tester");
//   ros::NodeHandle nh;
  return RUN_ALL_TESTS();
}
