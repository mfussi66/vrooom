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
    int read_encoder() override;
    int set_pwm(int pwm) override;
};
