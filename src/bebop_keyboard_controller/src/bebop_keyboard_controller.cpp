#include <ros/ros.h>

/**
Software License Agreement (BSD)

\file      bebop_keyboard_controller.cpp
\authors   Maxime Haseblauer <maxime.haselbauer@googlemail.com>
\copyright Copyright (c) 2021 Maxime Haselbauer, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.
 * Neither the name of Autonomy Lab nor the names of its contributors may be
used to endorse or promote products derived from this software without specific
prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WAR- RANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, IN- DIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <algorithm>
#include <string>
#include <vector>

#include <ros/ros.h>


#include <keyboard_hook.h>

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "bebop_keyboard_controller",
            ros::init_options::NoSigintHandler);
  ros::NodeHandle nh;
  ros::Publisher take_off_or_land_publisher =
      nh.advertise<std_msgs::Empty>("/bebop/takeoff", 1000);

  void take_off_of_land = [&]() {
    std_msgs::Empty msg{};
    take_off_or_land_publisher.publish(msg);
  };

  std_msgs

  bebop_keyboard_controller::KeyboardHook keyboard_hook(take_off_of_land);

  ("/bebop/takeoff")

      / bebop /
      cmd_vel

          ROS_INFO("bebop_driver nodelet loaded.");
  ros::spin();
  return 0;
}
