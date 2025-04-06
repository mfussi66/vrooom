#include <mockHardware.h>

mockHardware::mockHardware()
{
}

int mockHardware::setup() { return 0; }

int mockHardware::read_encoder()
{
    return 0;
}

int mockHardware::set_pwm(int pwm)
{
    return 0;
}
