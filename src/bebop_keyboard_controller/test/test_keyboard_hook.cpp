#include <gtest/gtest.h>
#include <iostream>
#include <keyboard_hook.h>
#include <mutex>
#include <thread>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

#include "test_keyboard_hook_utils.h"
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
// CallbackMocks mocks{};

class PressingOnKeys : public ::testing::Test {

protected:
  KeyboardHook *keyboard_hook;
  std::thread keyboard_hook_thread{};
  Display *display{};
   CallbackMocks mocks_{};

  Display* getDisplay() {
    if (display == nullptr) {
      Display *display{};
      display = XOpenDisplay(":0");
    }
    return display;
  }
  virtual void SetUp() {
    keyboard_hook = new KeyboardHook(mocks_.upArrow(), mocks_.downArrow(),
                                     mocks_.leftArrow(), mocks_.rightArrow(),
                                     mocks_.pageDown(), mocks_.pageUp());
    keyboard_hook_thread = std::thread(
        &bebop_keyboard_controller::KeyboardHook::run, keyboard_hook);
  }
  virtual void terminateHook() {
    keyboard_hook->stop();
    keyboard_hook_thread.join();
  }
  virtual void TearDown() { delete keyboard_hook; }
};

void pressAndReleaseKey(Display *display, unsigned int keycode) {
  XTestFakeKeyEvent(display, keycode, False, CurrentTime);
  XFlush(display);
  // displayKeymap(display);

  XTestFakeKeyEvent(display, keycode, True, CurrentTime);
  XFlush(display);
  displayKeymap(display);

  XTestFakeKeyEvent(display, keycode, False, CurrentTime);
  XFlush(display);
}

TEST_F(PressingOnKeys, UpArrow) {
  // std::thread keyboard_hook_thread(
  //     &bebop_keyboard_controller::KeyboardHook::run, keyboard_hook);
  ASSERT_EQ(mocks_.upArrow.numberOfCalls(), 0);

  unsigned int keycode = XKeysymToKeycode(getDisplay(), XK_Up);
  pressAndReleaseKey(getDisplay(), keycode);
  terminateHook();

  EXPECT_EQ(mocks_.upArrow.numberOfCalls(), 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  // bebop_keyboard_controller::KeyboardHook keyboard_hook(
  //     mocks.upArrow(), mocks.downArrow(), mocks.leftArrow(),
  //     mocks.rightArrow(), mocks.pageDown(), mocks.pageUp());

  // std::thread keyboard_hook_thread(
  //     &bebop_keyboard_controller::KeyboardHook::run, &keyboard_hook);

  //   ros::init(argc, argv, "tester");
  //   ros::NodeHandle nh;
  int ret = RUN_ALL_TESTS();
  // keyboard_hook.stop();
  // keyboard_hook_thread.join();
  return ret;
}
