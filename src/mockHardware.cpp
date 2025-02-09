#include "mockHardware.h"
#include <iostream>

mockHardware::mockHardware()
{
}

mockHardware::~mockHardware()
{
}

int mockHardware::claim_input()
{
    std::cout << "claimed input" << std::endl;
    return 0;
}

int mockHardware::claim_output()
{
    std::cout << "claimed output" << std::endl;
    return 0;
}

int mockHardware::read_pin(u_int8_t pin)
{
    std::cout << "claimed input" << std::endl;
    return 0;
}

int mockHardware::write_pin(uint8_t pin, int value)
{
    //std::cout << "wp " << pin << ": " << value << std::endl;
    return 0;
}

int mockHardware::set_pwm(int pwm)
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
