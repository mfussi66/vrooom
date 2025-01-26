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

int mockHardware::read_pin()
{
    std::cout << "claimed input" << std::endl;
    return 0;
}

int mockHardware::write_pin()
{
    std::cout << "claimed output" << std::endl;
    return 0;
}

int mockHardware::set_pwm()
{
    std::cout << "claimed output" << std::endl;
    return 0;
}
