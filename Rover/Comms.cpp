#include <Comms.h>

#include <lcm/lcm-cpp.hpp>
#include <chrono>
#include <iostream>
#include <rovertypes/motor_commands_t.hpp>

Comms::Comms(const std::string& channel_name)
{
    lcm_ptr = std::make_unique<lcm::LCM>();

    if(!lcm_ptr->good()) {std::cout << "lcm is NOT good" << std::endl;}

    ref_sub = lcm_ptr->subscribe(channel_name, &Comms::handleMessage, this);
    ref_sub->setQueueCapacity(10);

}

void Comms::handleMessage(const lcm::ReceiveBuffer* rbuf,
                          const std::string& chan,
                          const rovertypes::twist_t* msg)
{
    wref_ = msg->w;
    vref_ = msg->v;
    std::cout << "msg at " << msg->timestamp << std::endl;

    // msg->timestamp = std::chrono::high_resolution_clock::now().time_since_epoch();
}

void Comms::publishCommands(double pwm_l,
                            double pwm_r)
{
  rovertypes::motor_commands_t c {.pwm = {pwm_l, pwm_r}};
  lcm_ptr->publish("outputs.pwm", &c);
}

Comms::~Comms()
{
}
