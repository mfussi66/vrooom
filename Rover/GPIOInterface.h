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

    virtual int read_encoder() = 0;
    virtual int set_pwm(int pwm) = 0;
};

