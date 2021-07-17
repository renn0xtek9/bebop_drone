#include <gtest/gtest.h>
#include <iostream>
#include <keyboard_hook.h>
#include <mutex>
#include <thread>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

#include "test_utils.h"

using namespace std::chrono_literals;
using KeyboardHook = bebop_keyboard_controller::KeyboardHook;

struct CallbackMocks {
  CallbackMock upArrow{};
  CallbackMock downArrow{};
  CallbackMock leftArrow{};
  CallbackMock rightArrow{};
  CallbackMock pageUp{};
  CallbackMock pageDown{};
};

class PressingOnKeys : public ::testing::Test {

protected:
  KeyboardHook *keyboard_hook_;
  std::thread keyboard_hook_thread_{};
  Display *display_{};
  CallbackMocks mocks_{};

  Display *getDisplay() {
    if (display_ == nullptr) {
      Display *display_{};
      display_ = XOpenDisplay(":0");
    }
    return display_;
  }
  virtual void SetUp() {
    keyboard_hook_ = new KeyboardHook(mocks_.upArrow(), mocks_.downArrow(),
                                     mocks_.leftArrow(), mocks_.rightArrow(),
                                     mocks_.pageDown(), mocks_.pageUp());
    keyboard_hook_thread_ = std::thread(
        &bebop_keyboard_controller::KeyboardHook::run, keyboard_hook_);
  }
  virtual void terminateHook() {
    keyboard_hook_->stop();
    keyboard_hook_thread_.join();
  }
  virtual void TearDown() { delete keyboard_hook_; }
};

void pressAndReleaseKey(Display *display, unsigned int keycode) {
  XTestFakeKeyEvent(display, keycode, False, CurrentTime);
  XFlush(display);

  XTestFakeKeyEvent(display, keycode, True, CurrentTime);
  XFlush(display);

  XTestFakeKeyEvent(display, keycode, False, CurrentTime);
  XFlush(display);
}

TEST_F(PressingOnKeys, UpArrow) {
  ASSERT_EQ(mocks_.upArrow.numberOfCalls(), 0);
  unsigned int keycode = XKeysymToKeycode(getDisplay(), XK_Up);
  pressAndReleaseKey(getDisplay(), keycode);
  terminateHook();
  EXPECT_EQ(mocks_.upArrow.numberOfCalls(), 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  //   ros::init(argc, argv, "tester");
  //   ros::NodeHandle nh;
  return RUN_ALL_TESTS();
}
