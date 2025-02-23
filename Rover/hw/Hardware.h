#ifndef HARDWARE_H
#define HARDWARE_H

#include "GPIOInterface.h"
#include <cstdint>

gpioGroup motor_left_io = {
    {M_ENCODER_L}, 
    {M_IN1_L, M_IN2_L, M_EN_L}
};
gpioGroup motor_right_io = {
    {M_ENCODER_R}, 
    {M_IN1_R, M_IN2_R, M_EN_R}
};

class Hardware : public GPIOInterface
{
private:
    int handle = -1;
    
    gpioGroup m_gpio;

    static constexpr double PWM_FREQ = 1000;

public:
    Hardware(gpioGroup gpio);
    ~Hardware();

    int claim_input(uint8_t pin) override;
    int claim_outputs(const int* pin, int size) override;
    int read_pin(uint8_t pin) override;
    int write_pin(uint8_t pin, int value) override;
    int set_pwm(int pwm) override;
    int free_stuff(int h);
    int setup_chip();
};

#endif

