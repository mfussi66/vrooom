#ifndef MOTOR_H
#define MOTOR_H

#include <hardware.h>

#define PWM_FREQ 1000

enum 
{
   MOTOR_STOP = 0b0,
   MOTOR_FORWARD = 0b10,
   MOTOR_BACKWARDS = 0b01
};

typedef struct
{
   int motor_id;
   int chip_handle;
   int encoder;
   int encoder_pulse_prev;
   int pwm;
   int direction;
   gpioGroup io;
} motor;

int motor_setup(motor *m, int h, int id, gpioGroup* gpio);

void motor_read_encoder(motor* m);

void motor_run(motor* m, unsigned int cmd, int pwm_set);

void motor_command_set(motor* m, unsigned int cmd);

void motor_stop(motor* m);

void motor_pwm_set(motor* m, int pwm_set);

#endif
