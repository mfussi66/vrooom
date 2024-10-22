#ifndef ROVER_H
#define ROVER_H

enum 
{
   ROVER_STOP = MOTOR_STOP,
                                // Right           Left
   ROVER_FORWARD =      (MOTOR_FORWARD << 2)    + MOTOR_FORWARD,
   ROVER_BACKWARDS =    (MOTOR_BACKWARDS << 2)  + MOTOR_BACKWARDS,
   ROVER_LEFT =         (MOTOR_FORWARD << 2)    + MOTOR_BACKWARDS,
   ROVER_RIGHT =        (MOTOR_BACKWARDS << 2)  + MOTOR_FORWARD
};

int rover_setup();

void rover_run(int pwm_set_left,int pwm_set_right, unsigned int direction);

void rover_stop();

void rover_close();

void rover_read_encoders();

void rover_get_wheels_angles(double* left, double* right);

void rover_estimate_wheels_speeds();

void rover_get_wheels_speeds(double* vl, double* vr);

void rover_run_speed_ctrl(double l_ref, double r_ref);

#endif 
