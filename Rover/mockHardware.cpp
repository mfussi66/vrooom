#include "mockHardware.h"
#include <iostream>

mockHardware::mockHardware()
{
}

mockHardware::~mockHardware()
{
}

int mockHardware::setup() { return 0; }

int mockHardware::read_pin(uint8_t pin)
{
    // std::cout << "read pin " << std::format("{:d}", pin) << std::endl;
    return 0;
}

int mockHardware::write_pin(uint8_t pin, int value)
{
    //std::cout << "wp " << pin << ": " << value << std::endl;
    return 0;
}

int mockHardware::set_pwm(int pwm)
{
    return 0;
}
