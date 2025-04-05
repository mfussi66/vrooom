#include "mockHardware.h"
#include <iostream>

mockHardware::mockHardware()
{
}

mockHardware::~mockHardware()
{
}

int mockHardware::setup() { return 0; }

int mockHardware::read_encoder()
{
    // std::cout << "read pin " << std::format("{:d}", pin) << std::endl;
    return 0;
}

int mockHardware::set_pwm(int pwm)
{
    return 0;
}
