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

void rover_run(int pwm_set)
{
    if(motion_state == 0)
        rover_forward(pwm_set);

    switch (motion_state)
    {
    case 1:
        rover_forward(pwm_set);
        break;
        case 2:
        rover_backwards(pwm_set);
        break;
    case 3:
        rover_backwards(pwm_set);
        break;
    case 4:
        rover_backwards(pwm_set);
        break;
    default:
        rover_stop();
        break;
    }
}

void rover_forward(int pwm_set)
{
    motor_forward(&motor_left);
    motor_forward(&motor_right);
    motor_pwm_set(&motor_left, pwm_set);
    motor_pwm_set(&motor_right, pwm_set);
    motion_state = 1;
}

void rover_backwards(int pwm_set)
{
    motor_backwards(&motor_left);
    motor_backwards(&motor_right);
    motor_pwm_set(&motor_left, pwm_set);
    motor_pwm_set(&motor_right, pwm_set);
    motion_state = 2;
}

void rover_left(int pwm_set)
{
    motor_backwards(&motor_left);
    motor_forward(&motor_right);
    motor_pwm_set(&motor_left, pwm_set);
    motor_pwm_set(&motor_right, pwm_set);
    motion_state = 3;
}

void rover_right(int pwm_set)
{
    motor_forward(&motor_left);
    motor_backwards(&motor_right);
    motor_pwm_set(&motor_left, pwm_set);
    motor_pwm_set(&motor_right, pwm_set);
    motion_state = 4;
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
