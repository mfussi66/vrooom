#pragma once

#include <GPIOInterface.h>

class mockHardware : public GPIOInterface
{
public:
    mockHardware(/* args */);
    ~mockHardware(){};

    int setup() override;
    int read_encoder() override;
    int set_pwm(int pwm) override;
};
