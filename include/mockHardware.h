#pragma once
#include "GPIOInterface.h"

class mockHardware : public GPIOInterface
{
private:
    /* data */
public:
    mockHardware(/* args */);
    ~mockHardware();

    int claim_input() override;
    int claim_output() override;
    int read_pin() override;
    int write_pin() override;
    int set_pwm() override;
};
