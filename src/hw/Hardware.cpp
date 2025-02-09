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
}

Hardware::~Hardware()
{
}

int setup_chip()
{
      // r = lgGpioWrite(m->chip_handle, m->io.outputs[0], cmd & 1);
      // r = lgGpioWrite(m->chip_handle, m->io.outputs[1], cmd >> 1);
   // r = lgTxPwm(m->chip_handle, m->io.outputs[2], PWM_FREQ, pwm_set, 0, 0);
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
