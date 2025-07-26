#include <Comms.h>

#include <rovertypes/motor_commands_t.hpp>
#include <lcm/lcm-cpp.hpp>

#include <chrono>
#include <iostream>

Comms::Comms(const std::string &channel_name)
{
  lcm_ptr = std::make_unique<lcm::LCM>();

  if (!lcm_ptr->good())
  {
    std::cout << "lcm is NOT good" << std::endl;
  }

  sub = lcm_ptr->subscribe(channel_name, &Comms::handle_commands_msg, this);
  sub->setQueueCapacity(10);

  std::cout << "Reading inputs from " << channel_name << std::endl;

}

void Comms::handle_commands_msg(const lcm::ReceiveBuffer *rbuf,
                          const std::string &chan,
                          const rovertypes::motor_commands_t *msg)
{
  pwm[0] = msg->pwm[0];
  pwm[1] = msg->pwm[1];
}

void Comms::publishState()
{
  //lcm_ptr->publish("", &c);
}
