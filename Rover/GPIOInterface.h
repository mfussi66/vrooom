#pragma once

#include <cstdint>
#include <array>

typedef struct 
{
    std::array<int, 1> inputs;
    std::array<int, 3> outputs;
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

    virtual int setup(const gpioGroup& gpio)
    {
        return setup();
    };

    virtual int setup() 
    {
        return 0;
    };

    // virtual int claim_input(uint8_t pin) = 0;
    // virtual int claim_outputs(const int* pin, int size) = 0;
    virtual int read_pin(uint8_t pin)= 0;
    virtual int write_pin(uint8_t pin, int value) = 0;
    virtual int set_pwm(int pwm) = 0;

};

