#ifndef MOTOR_H
#define MOTOR_H

#include <hardware.h>
#include <math.h>
#include <stdio.h>
#define PWM_FREQ 1000

#define ENCODER_RESOLUTION 1986.0F

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
   double encoder;
   double encoder_prev;
   double speed;
   int encoder_pulse_prev;
   int pwm;
   int direction;
   gpioGroup io;
} motor;

int motor_setup(motor *m, int h, int id, gpioGroup* gpio);

void motor_read_encoder(motor* m);

void motor_estimate_speed(motor* m, int window, double Ts);

void motor_run(motor* m, unsigned int cmd, int pwm_set);

void motor_command_set(motor* m, unsigned int cmd);

void motor_stop(motor* m);

void motor_pwm_set(motor* m, int pwm_set);

double static inline motor_get_angle(motor* m)
{
   return ((float)m->encoder) / ENCODER_RESOLUTION * 2.0 * M_PI;
}
#endif
