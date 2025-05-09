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

  ref_sub = lcm_ptr->subscribe(channel_name, &Comms::handleMessage, this);
  ref_sub->setQueueCapacity(10);

  std::cout << "Reading inputs from " << channel_name << std::endl;

}

void Comms::handleMessage(const lcm::ReceiveBuffer *rbuf,
                          const std::string &chan,
                          const rovertypes::twist_t *msg)
{
  wref_ = msg->w;
  vref_ = msg->v;
}

void Comms::publishCommands(double pwm_l,
                            double pwm_r)
{
  rovertypes::motor_commands_t c{.timestamp = std::chrono::duration_cast<std::chrono::microseconds>(
                                                  std::chrono::high_resolution_clock::now().time_since_epoch())
                                                  .count(),
                                 .pwm = {pwm_l, pwm_r}};
  lcm_ptr->publish("rover.pwm.set", &c);
}
