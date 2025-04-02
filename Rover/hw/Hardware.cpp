#include <lgpio.h>

#include <Hardware.h>
#include "GPIOInterface.h"
#include <iostream>

      gpioGroup motor_left_io = {
         {M_ENCODER_L}, 
         {M_IN1_L, M_IN2_L, M_EN_L}
     };
     gpioGroup motor_right_io = {
         {M_ENCODER_R}, 
         {M_IN1_R, M_IN2_R, M_EN_R}
     };
   

Hardware::Hardware(gpioGroup gpio)
: m_gpio(gpio)
{}

Hardware::~Hardware()
{
}

int Hardware::setup()
{
    int r = setup_chip();

	if(r < 0)
	{
		std::cerr << "There was a problem opening chip!" << std::endl;
		return r;
	}
	
    r = claim_input(m_gpio.inputs[0]);
    r = claim_outputs(m_gpio.outputs.data(), m_gpio.outputs.size());

    return r; 
}


int Hardware::setup_chip()
{

   static bool is_setup = false;

   static int h = -1;

   if(!is_setup)
   {
        h = lgGpiochipOpen(0);
        is_setup = true;
   }

   handle = h;
   
   return handle; 
}

int Hardware::claim_input(uint8_t pin)
{
    return lgGpioClaimInput(handle, LG_SET_PULL_UP, m_gpio.inputs[0]);
}

int Hardware::claim_outputs(const int* pin, int size)
{
    return lgGroupClaimOutput(handle, 0, m_gpio.outputs.size(), m_gpio.outputs.data(), 0);
}

int Hardware::read_pin(uint8_t pin)
{
	int v = lgGpioRead(handle, pin);
    return v;
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
        write_pin(m_gpio.outputs[0], static_cast<uint8_t>(Direction::Forward) & 1);
        write_pin(m_gpio.outputs[1], static_cast<uint8_t>(Direction::Forward) >> 1);
        //std::cerr << "Forward " << m_gpio.outputs[0] << " "<<  m_gpio.outputs[1] << std::endl;
    }
    else if(pwm < 0)
    {
       write_pin(m_gpio.outputs[0], static_cast<uint8_t>(Direction::Backwards) & 1);
       write_pin(m_gpio.outputs[1], static_cast<uint8_t>(Direction::Backwards) >> 1);
       //std::cerr << "Backwards" << std::endl;
    }
    else
    {
      write_pin(m_gpio.outputs[0], static_cast<uint8_t>(Direction::Stop) & 1);
      write_pin(m_gpio.outputs[1], static_cast<uint8_t>(Direction::Stop) >> 1);
      //std::cerr << "Stop" << std::endl;
    }

    lgTxPwm(handle, m_gpio.outputs[2], PWM_FREQ, 50, 0, 0);

    //std::cout << "pwm set " << pwm << std::endl;
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
