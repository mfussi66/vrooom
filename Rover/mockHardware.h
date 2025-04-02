#pragma once

#include "GPIOInterface.h"
#include <cstdint>

class mockHardware : public GPIOInterface
{
private:
    
public:
    mockHardware(/* args */);
    ~mockHardware();

    int setup() override;
    int read_pin(uint8_t pin) override;
    int write_pin(uint8_t pin, int value) override;
    int set_pwm(int pwm) override;
};
