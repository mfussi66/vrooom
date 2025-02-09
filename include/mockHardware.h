#pragma once
#include "GPIOInterface.h"
#include <cstdint>
class mockHardware : public GPIOInterface
{
private:
    /* data */
public:
    mockHardware(/* args */);
    ~mockHardware();

    int claim_input() override;
    int claim_output() override;
    int read_pin(uint8_t pin) override;
    int write_pin(uint8_t pin, int value) override;
    int set_pwm(int pwm) override;
};
