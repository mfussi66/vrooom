#ifndef HARDWARE_H
#define HARDWARE_H

#define M_ENCODER_R 19
#define M_IN1_R 17
#define M_IN2_R 27
#define M_EN_R 22

#define M_ENCODER_L 26
#define M_IN1_L 23
#define M_IN2_L 24
#define M_EN_L 25

typedef struct 
{
    int inputs[1];
    int outputs[3];
} gpioGroup;

extern gpioGroup motor_left_io;
extern gpioGroup motor_right_io;

int free_stuff(int h);

#endif