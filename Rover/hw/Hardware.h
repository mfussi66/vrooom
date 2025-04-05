#ifndef HARDWARE_H
#define HARDWARE_H

#include "GPIOInterface.h"
#include <cstdint> 

extern gpioGroup motor_left_io;
extern gpioGroup motor_right_io;

class Hardware : public GPIOInterface
{
private:
    int handle = -1;
    
    gpioGroup m_gpio;

    static constexpr double PWM_FREQ = 1000;

public:
    Hardware(gpioGroup gpio);
    ~Hardware();

    int setup() override;
    int read_encoder() override;
    int write_pin(uint8_t pin, int value) override;
    int set_pwm(int pwm) override;
    int free_stuff(int h);
};

#endif

