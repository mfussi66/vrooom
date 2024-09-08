#include <motor.h>
#include <rover.h>
#include <stdio.h>
#include <lgpio.h>

motor motor_left;
motor motor_right;

int chip_handle = 0;

int motion_state = 0;

int rover_setup()
{

   int h = lgGpiochipOpen(0);

   if (h < 0)
   {
      printf("ERROR: %s (%d)\n", lguErrorText(h), h);
      return 1;
   }

   chip_handle = h;

   if (motor_setup(&motor_left, h, 0, &motor_left_io) != 0)
   {
      printf("Could not set up left motor!");
      return -1;
   }

   if (motor_setup(&motor_right, h, 1, &motor_right_io) != 0)
   {
      printf("Could not set up right motor!");
      return -1;
   }
}

void rover_run(int pwm_set, unsigned int direction)
{
    if(direction != ROVER_FORWARD &&
        direction != ROVER_BACKWARDS &&
        direction != ROVER_LEFT &&
        direction != ROVER_RIGHT &&
        direction != ROVER_STOP)
    {
        rover_stop();
        return;
    }

    motor_run(&motor_left, direction & 0b11, pwm_set);
    motor_run(&motor_right, (direction >> 2), pwm_set);
}

void rover_stop()
{
    motor_stop(&motor_left);
    motor_stop(&motor_right);
    motion_state = 0;
}

void rover_close()
{
    rover_stop();
    free_stuff(chip_handle);
}

void rover_read_encoders(int* encoder_left, int* encoder_right)
{
    motor_read_encoder(&motor_left);
    motor_read_encoder(&motor_right);

    *encoder_left = motor_left.encoder;
    *encoder_right = motor_right.encoder;
}
