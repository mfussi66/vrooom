#ifndef HARDWARE_H
#define HARDWARE_H

#define M_ENCODER_L 19
#define M_IN1_L 17
#define M_IN2_L 27
#define M_EN_L 22

#define M_ENCODER_R 26
#define M_IN1_R 23
#define M_IN2_R 24
#define M_EN_R 25

typedef struct 
{
    int inputs[1];
    int outputs[3];
} gpioGroup;

extern gpioGroup motor_left_io;
extern gpioGroup motor_right_io;

int free_stuff(int h);

#endif