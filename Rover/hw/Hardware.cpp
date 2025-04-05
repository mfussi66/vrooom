#include <Hardware.h>
#include <lgpio.h>

#include <iostream>

#include "GPIOInterface.h"

#define M_ENCODER_R 19
#define M_IN1_R 17
#define M_IN2_R 27
#define M_EN_R 22

#define M_ENCODER_L 26
#define M_IN1_L 23
#define M_IN2_L 24
#define M_EN_L 25

gpioGroup motor_left_io = {{M_ENCODER_L}, {M_IN1_L, M_IN2_L, M_EN_L}};
gpioGroup motor_right_io = {{M_ENCODER_R}, {M_IN1_R, M_IN2_R, M_EN_R}};

Hardware::Hardware(gpioGroup gpio) : m_gpio(gpio) {}

Hardware::~Hardware() {}

int Hardware::setup() {
  static bool is_setup = false;

  static int h = -1;

  if (!is_setup) {
    h = lgGpiochipOpen(0);
    is_setup = true;
  }

  handle = h;

  if (r < 0) {
    std::cerr << "There was a problem opening chip!" << std::endl;
    return r;
  }

  r = lgGpioClaimInput(handle, LG_SET_PULL_UP, m_gpio.inputs[0]);
  r = lgGroupClaimOutput(handle, 0, m_gpio.outputs.size(),
                         m_gpio.outputs.data(), 0);

  return r;
}

int Hardware::read_encoder()
{
  return lgGpioRead(handle, m_gpio.outputs[0]);
}

int Hardware::write_pin(uint8_t pin, int value) {
  lgGpioWrite(handle, pin, value);
  return LG_OKAY;
}

int Hardware::set_pwm(int pwm) {
  if (pwm > 0) {
    write_pin(m_gpio.outputs[0], static_cast<uint8_t>(Direction::Forward) & 1);
    write_pin(m_gpio.outputs[1], static_cast<uint8_t>(Direction::Forward) >> 1);

  } else if (pwm < 0) {
    write_pin(m_gpio.outputs[0],
              static_cast<uint8_t>(Direction::Backwards) & 1);
    write_pin(m_gpio.outputs[1],
              static_cast<uint8_t>(Direction::Backwards) >> 1);
  } else {
    write_pin(m_gpio.outputs[0], static_cast<uint8_t>(Direction::Stop) & 1);
    write_pin(m_gpio.outputs[1], static_cast<uint8_t>(Direction::Stop) >> 1);
  }

  lgTxPwm(handle, m_gpio.outputs[2], PWM_FREQ, 50, 0, 0);

  // std::cout << "pwm set " << pwm << std::endl;
  return LG_OKAY;
}

int Hardware::free_stuff(int h) {
  lgGpioFree(h, M_ENCODER_L);
  lgGpioFree(h, M_ENCODER_R);
  lgGpioFree(h, M_IN1_L);
  lgGpioFree(h, M_IN2_L);
  lgGpioFree(h, M_IN1_R);
  lgGpioFree(h, M_IN2_R);

  return LG_OKAY;
}
