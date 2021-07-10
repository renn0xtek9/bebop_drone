#ifndef KEYBOARD_HOOK_H
#define KEYBOARD_HOOK_H

class KeyboardHook {
public:
  KeyboardHook(const std::function<void()> forward,
               std::function<void()> backward, std::function<void()> left,
               std::function<void()> right)
      : m_move_forward_callback(forward), m_move_backward_callback(backward),
        m_move_left_callback(left), m_move_right_callback(right){};

private:
  std::function<void()> m_move_forward_callback{};
  std::function<void()> m_move_backward_callback{};
  std::function<void()> m_move_left_callback{};
  std::function<void()> m_move_right_callback{};
}

#endif // KEYBOARD_HOOK_H
