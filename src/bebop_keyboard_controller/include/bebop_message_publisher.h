#ifndef BEBOP_MESSAGE_PUBLISHER_H
#define BEBOP_MESSAGE_PUBLISHER_H

namespace bebop_keyboard_controller {

class BebopMessagePublisher {
public:
  void sendTakeOffOrLandingMessage();
  void sendCmdVelMessage(const double linear_x, const double linear_y,
                         const double linear_z, const double angular_z);
};

} // namespace bebop_keyboard_controller

#endif // BEBOP_MESSAGE_PUBLISHER_H
