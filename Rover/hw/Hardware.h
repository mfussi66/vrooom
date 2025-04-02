#ifndef HARDWARE_H
#define HARDWARE_H

#include "GPIOInterface.h"
#include <cstdint>

#define M_ENCODER_R 19
#define M_IN1_R 17
#define M_IN2_R 27
#define M_EN_R 22

#define M_ENCODER_L 26
#define M_IN1_L 23
#define M_IN2_L 24
#define M_EN_L 25

class Hardware : public GPIOInterface
{
private:
    int handle = -1;
    
    gpioGroup m_gpio;

    static constexpr double PWM_FREQ = 1000;

public:
    Hardware(gpioGroup gpio);
    ~Hardware();

    int setup(const gpioGroup& gpio) override;
    int read_pin(uint8_t pin) override;
    int write_pin(uint8_t pin, int value) override;
    int set_pwm(int pwm) override;
    int free_stuff(int h);
    int setup_chip();
    int claim_input(uint8_t pin);
    int claim_outputs(const int* pin, int size);
};

#endif

