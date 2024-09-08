#ifndef ROVER_H
#define ROVER_H

enum 
{
   ROVER_STOP = 0b0,
   ROVER_FORWARD = 0b1010,
   ROVER_BACKWARDS = 0b0101,
   ROVER_LEFT = 0b1001,
   ROVER_RIGHT = 0b0110,
};

int rover_setup();

void rover_run(int pwm_set, unsigned int direction);

void rover_stop();

void rover_close();

void rover_read_encoders(int* encoder_left, int* encoder_right);

#endif 
