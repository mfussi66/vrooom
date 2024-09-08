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

void rover_run(int pwm_set, unsigned int direction);

void rover_stop();

void rover_close();

void rover_read_encoders(int* encoder_left, int* encoder_right);

#endif 
