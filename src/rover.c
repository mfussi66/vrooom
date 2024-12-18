#include <motor.h>
#include <rover.h>
#include <control.h>

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

void rover_read_encoders()
{
    motor_read_encoder(&motor_left);
    motor_read_encoder(&motor_right);
}

void rover_get_wheels_angles(double* left, double* right)
{
    *left = motor_get_angle(&motor_left);
    *right = motor_get_angle(&motor_right);
}

void rover_estimate_wheels_speeds()
{
    motor_estimate_speed(&motor_left, 64, 0.001);
    motor_estimate_speed(&motor_right, 64, 0.001);
}

void rover_get_wheels_speeds(double* vl, double* vr)
{
    *vl = motor_left.speed;
    *vr = motor_right.speed;
}

void rover_run_speed_ctrl(double l_ref, double r_ref)
{
    double y[2];
    double r[2] = {l_ref, r_ref};
    double u[2];

    rover_get_wheels_speeds(&y[0], &y[1]);

    motion_control_step(r, y, u);

    if(u[0] < 0)
        motor_run(&motor_left, MOTOR_BACKWARDS, u[0]);
    else
        motor_run(&motor_right, MOTOR_FORWARD, u[0]);

    if(u[1] < 0)
        motor_run(&motor_left, MOTOR_BACKWARDS, u[1]);
    else
        motor_run(&motor_right, MOTOR_FORWARD, u[1]);
}
