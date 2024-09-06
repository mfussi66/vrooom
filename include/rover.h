#ifndef ROVER_H
#define ROVER_H

#include <motor.h>

int rover_setup();

void rover_run(int pwm_set);

void rover_forward(int pwm_set);

void rover_backwards(int pwm_set);

void rover_left(int pwm_set);

void rover_right(int pwm_set);

void rover_stop();

void rover_close();

void rover_read_encoders(int* encoder_left, int* encoder_right);

#endif 
