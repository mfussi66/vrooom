#include <motor.h>
#include <hardware.h>
#include <lgpio.h>
#include <stdlib.h>
#include <stdio.h>

int motor_setup(motor *m, int h, int id, gpioGroup* gpio)
{
   int res = LG_OKAY;

   m->motor_id = id;
   m->chip_handle = h;
   m->io = *gpio;

   res = lgGroupClaimOutput(h, 0, 3, m->io.outputs, 0);
   res = lgGpioClaimInput(h, LG_SET_PULL_UP, m->io.inputs[0]);

   m->encoder = 0;
   m->pwm = 0;
   m->direction = 1;

   return res;
}

void motor_read_encoder(motor* m)
{
   int v = lgGpioRead(m->chip_handle, m->io.inputs[0]);
   
   m->encoder += m->direction * abs(v - m->encoder_pulse_prev);  
   m->encoder_pulse_prev = v;
}

void motor_forward(motor* m)
{
   int r = LG_OKAY;
   r = lgGpioWrite(m->chip_handle, m->io.outputs[0], 0);
   r = lgGpioWrite(m->chip_handle, m->io.outputs[1], 1);
    
   if (r != LG_OKAY) 
   {
      printf("error\n");
      return;
   }

   m->direction = 1;
}

void motor_backwards(motor* m)
{
   int r = LG_OKAY;
   r = lgGpioWrite(m->chip_handle, m->io.outputs[0], 1);
   r = lgGpioWrite(m->chip_handle, m->io.outputs[1], 0);
    
   if (r != LG_OKAY) 
   {
      printf("error\n");
      return;
   }

   m->direction = -1;
}

void motor_stop(motor* m)
{
   int r = LG_OKAY;
   
   motor_pwm_stop(m);
   
   r = lgGpioWrite(m->chip_handle, m->io.outputs[0], 0);
   r = lgGpioWrite(m->chip_handle, m->io.outputs[1], 0);

   if (r != LG_OKAY) printf("error\n");
}

void motor_pwm_set(motor* m, int pwm_set)
{
   lgTxPwm(m->chip_handle, m->io.outputs[2], PWM_FREQ, pwm_set, 0, 0);

    m->pwm = pwm_set;
}

void motor_pwm_stop(motor* m)
{
   motor_pwm_set(m, 0);
}