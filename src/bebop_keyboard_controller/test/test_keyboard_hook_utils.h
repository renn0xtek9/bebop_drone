#ifndef TEST_KEYBOARD_HOOK_UTILS_H
#define TEST_KEYBOARD_HOOK_UTILS_H
#include<array>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

template <class container>
void displayArray(container array)
{
    for (int i=0;i<array.size();++i)
    {
        printf("%x ",array[i]);fflush(stdout);
    }
    printf("\n");fflush(stdout);
}

void displayKeymap(Display* display)
{
    std::array<char, 32> keymap{};
    XQueryKeymap(display, keymap.data());
    displayArray(keymap);
}

#endif //TEST_KEYBOARD_HOOK_UTILS_H
