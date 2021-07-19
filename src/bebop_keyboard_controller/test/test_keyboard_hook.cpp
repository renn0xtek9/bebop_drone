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

void pressAndReleaseKey(Display *display, unsigned int keycode) {
  XTestFakeKeyEvent(display, keycode, False, CurrentTime);
  XFlush(display);

  XTestFakeKeyEvent(display, keycode, True, CurrentTime);
  XFlush(display);
  std::this_thread::sleep_for(200ms);

  XTestFakeKeyEvent(display, keycode, False, CurrentTime);
  XFlush(display);
}

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
      display_ = XOpenDisplay(":0");
    }
    return display_;
  }

  void performTest(const unsigned int XKeyValue, CallbackMock &mock) {
    ASSERT_TRUE(getDisplay() != nullptr);
    unsigned int keycode = XKeysymToKeycode(getDisplay(), XKeyValue);
    pressAndReleaseKey(getDisplay(), keycode);
    terminateHook();
    EXPECT_EQ(mock.numberOfCalls(), 1);
  }

  virtual void SetUp() {
    XInitThreads();
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

TEST_F(PressingOnKeys, UpArrow) {
  performTest(XK_Up,mocks_.upArrow);
}

TEST_F(PressingOnKeys, DownArrow) {
  performTest(XK_Down,mocks_.downArrow);
}

TEST_F(PressingOnKeys, LeftArrow) {
  performTest(XK_Left,mocks_.leftArrow);
}

TEST_F(PressingOnKeys, RightArrow) {
  performTest(XK_Right,mocks_.rightArrow);
}

TEST_F(PressingOnKeys, PageUp) {
  performTest(XK_Page_Up,mocks_.pageUp);
}

TEST_F(PressingOnKeys, PageDown) {
  performTest(XK_Page_Down,mocks_.pageDown);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  //   ros::init(argc, argv, "tester");
  //   ros::NodeHandle nh;
  return RUN_ALL_TESTS();
}
