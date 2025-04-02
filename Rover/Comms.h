#pragma once

#include <rovertypes/twist_t.hpp>

#include <lcm/lcm-cpp.hpp>
#include <memory>

class Comms
{
private:
  void handleMessage(const lcm::ReceiveBuffer *rbuf, const std::string &chan,
                       const rovertypes::twist_t *msg);
  lcm::Subscription* ref_sub;

  double vref_ = 0;
  double wref_ = 0;

public:

  std::unique_ptr<lcm::LCM> lcm_ptr;

  Comms(const std::string& channel_name);

  inline std::pair<double, double> get_twist_references()
  {
    return std::pair<double, double>(vref_, wref_);
  }

  void publishCommands(double pwm_l, double pwm_r);

  ~Comms();
};

