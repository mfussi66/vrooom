#pragma once

#include <lgpio.h>

#include <Hardware.h>
#include "GPIOInterface.h"

Hardware::Hardware(gpioGroup gpio)
: m_gpio(gpio)
{}

Hardware::~Hardware()
{
}

int Hardware::setup(const gpioGroup& gpio) { 
    
    int r = setup_chip();

    claim_input(gpio.inputs.data());
    claim_outputs(gpio.outputs.data(), gpio.outputs.size());

    return 0; 

}

int Hardware::setup_chip()
{

   static bool is_setup = false;

   if(!is_setup)
   {
        handle = lgGpiochipOpen(0);
        is_setup = true;
   }
   // 

}

int Hardware::claim_input(uint8_t pin)
{
    int res = 0;
    res = lgGpioClaimInput(handle, LG_SET_PULL_UP, m_gpio.inputs[0]);
    return 0;
}

int Hardware::claim_outputs(const int* pin, int size)
{
    lgGroupClaimOutput(handle, 0, 3, m_gpio.outputs, 0);
    return 0;
}

int Hardware::read_pin(uint8_t pin)
{
    // std::cout << "read pin " << std::format("{:d}", pin) << std::endl;
    return 0;
}

int Hardware::write_pin(uint8_t pin, int value)
{
    lgGpioWrite(handle, pin, value);
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

    lgTxPwm(handle, m->io.outputs[2], PWM_FREQ, pwm, 0, 0);

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
