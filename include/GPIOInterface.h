#pragma once

typedef struct 
{
    int inputs[1];
    int outputs[3];
} gpioGroup;


class GPIOInterface
{
private:
    gpioGroup motor_left_io;
    gpioGroup motor_right_io;

public:
    virtual ~GPIOInterface() = default;

    virtual int claim_input() = 0;
    virtual int claim_output() = 0;
    virtual int read_pin() = 0;
    virtual int write_pin() = 0;
    virtual int set_pwm() = 0;

};

