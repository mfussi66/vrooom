#pragma once

#include <cstdint>
typedef struct 
{
    int inputs[1];
    int outputs[3];
} gpioGroup;

enum class Direction {
    Stop = 0b0,
    Forward = 0b10,
    Backwards = 0b01
};
class GPIOInterface
{
private:
    gpioGroup motor_io;

public:
    virtual ~GPIOInterface() = default;

    virtual int claim_input() = 0;
    virtual int claim_output() = 0;
    virtual int read_pin(uint8_t pin)= 0;
    virtual int write_pin(uint8_t pin, int value) = 0;
    virtual int set_pwm(int pwm) = 0;

};

