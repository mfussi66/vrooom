#pragma once

#include <lcm/lcm-cpp.hpp>
#include <memory>
#include <rovertypes/motor_commands_t.hpp>

class Comms {
 public:
  Comms(const std::string &channel_name);

  ~Comms() {};

  inline std::array<double, 2> getCommands() { return pwm; }

  void publishState();

  inline void check_messages()
  {
    lcm_ptr->handleTimeout(5);
  }

 private:
  std::unique_ptr<lcm::LCM> lcm_ptr;
  lcm::Subscription *sub;
  std::array<double, 2> pwm;

  void handle_commands_msg(const lcm::ReceiveBuffer *rbuf, const std::string &chan,
                     const rovertypes::motor_commands_t *msg);
};
