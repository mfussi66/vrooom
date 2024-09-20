#include <motor.h>
#include <rover.h>
#include <stdio.h>
#include <lgpio.h>

motor motor_left;
motor motor_right;

int chip_handle = 0;

int motion_state = 0;
double l_old = 0;
double r_old = 0;

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

void rover_run(int pwm_set_left,int pwm_set_right, unsigned int direction)
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

    motor_run(&motor_left, direction & 0b11, pwm_set_left);
    motor_run(&motor_right, (direction >> 2), pwm_set_right);
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

void rover_get_wheels_angles(double* left, double* right)
{

    motor_read_encoder(&motor_left);
    motor_read_encoder(&motor_right);
    *left = motor_get_angle(&motor_left);
    *right = motor_get_angle(&motor_right);
}

void rover_get_wheels_speeds(int window, double Ts, double* vl, double* vr)
{
    motor_read_encoder(&motor_left);
    motor_read_encoder(&motor_right);
    double l = motor_get_angle(&motor_left);
    double r = motor_get_angle(&motor_right);

    static int cnt = 0;

    if(++cnt % window == 0)
    {
        *vl = (l - l_old)/(Ts * (double)window);
        l_old = l;
        *vr = (r - r_old)/(Ts * (double)window);
        r_old = r;
        cnt = 0;
    }
}