#pragma once

#include <lgpio.h>

#include <Hardware.h>
#include "GPIOInterface.h"

class Hardware : public GPIOInterface
{
private:
   gpioGroup motor_left_io = {
   {M_ENCODER_L}, 
   {M_IN1_L, M_IN2_L, M_EN_L}
};
gpioGroup motor_right_io = {
   {M_ENCODER_R}, 
   {M_IN1_R, M_IN2_R, M_EN_R}
};


public:
   Hardware(/* args */);
   ~Hardware();
};

Hardware::Hardware(/* args */)
{
   setup_chip
}

Hardware::~Hardware()
{
}

static int Hardware::setup_chip()
{

   static bool is_setup = false;

   // if(!is_setup)
   // lgpioSetup
   // is_setup = true;
      // r = lgGpioWrite(m->chip_handle, m->io.outputs[0], cmd & 1);
      // r = lgGpioWrite(m->chip_handle, m->io.outputs[1], cmd >> 1);
      // r = lgTxPwm(m->chip_handle, m->io.outputs[2], PWM_FREQ, pwm_set, 0, 0);
}

int Hardware::claim_input()
{
    // std::cout << "claimed input" << std::endl;
    return 0;
}

int Hardware::claim_output()
{
    // std::cout << "claimed output" << std::endl;
    return 0;
}

int Hardware::read_pin(uint8_t pin)
{
    // std::cout << "read pin " << std::format("{:d}", pin) << std::endl;
    return 0;
}

int Hardware::write_pin(uint8_t pin, int value)
{
    //std::cout << "wp " << pin << ": " << value << std::endl;
    return 0;
}

int Hardware::set_pwm(int pwm)
{
    if(pwm > 0) 
    {
        write_pin(0, static_cast<uint8_t>(Direction::Forward) & 1);
        write_pin(0, static_cast<uint8_t>(Direction::Forward) >> 1);
    }
    else if(pwm < 0)
    {
        write_pin(0, static_cast<uint8_t>(Direction::Backwards) & 1);
        write_pin(0, static_cast<uint8_t>(Direction::Backwards) >> 1);
    }
    else
    {
        write_pin(0, static_cast<uint8_t>(Direction::Stop) & 1);
        write_pin(0, static_cast<uint8_t>(Direction::Stop) >> 1);   
    }

   // std::cout << "pwm set " << pwm << std::endl;
    return 0;
}

int free_stuff(int h)
{
   lgGpioFree(h, M_ENCODER_L);
   lgGpioFree(h, M_ENCODER_R);
   lgGpioFree(h, M_IN1_L);
   lgGpioFree(h, M_IN2_L);
   lgGpioFree(h, M_IN1_R);
   lgGpioFree(h, M_IN2_R);

   return LG_OKAY;
}
