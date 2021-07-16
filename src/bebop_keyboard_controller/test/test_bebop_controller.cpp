#include <bebop_controller.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "test_utils.h"

namespace bebop_keyboard_controller {

using namespace ::testing;

TEST(TakeOffAndLanding, NoLandingAtStart) {
  CallbackMock callback_mock{};
  BebopController unit(callback_mock());
  unit.land();
  EXPECT_EQ(callback_mock.numberOfCalls(), 0);
}

TEST(TakeOffAndLanding, CanTakeOffAtStart) {
  CallbackMock callback_mock{};
  BebopController unit(callback_mock());
  unit.takeOff();
  EXPECT_EQ(callback_mock.numberOfCalls(), 1);
}

TEST(TakeOffAndLanding, MultipleTakeOffAndMultipleLanding) {
  CallbackMock callback_mock{};
  BebopController unit(callback_mock());
  unit.takeOff();
  unit.takeOff();
  EXPECT_EQ(callback_mock.numberOfCalls(), 1);
  unit.land();
  EXPECT_EQ(callback_mock.numberOfCalls(), 2);
  unit.land();
  EXPECT_EQ(callback_mock.numberOfCalls(), 2);
  unit.takeOff();
  EXPECT_EQ(callback_mock.numberOfCalls(), 3);
}

} // namespace bebop_keyboard_controller
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  //   ros::init(argc, argv, "tester");
  //   ros::NodeHandle nh;
  return RUN_ALL_TESTS();
}
