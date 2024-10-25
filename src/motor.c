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

void motor_estimate_speed(motor* m, int window, double Ts)
{
    static int cnt[2] = {0, 0};

    if(++cnt[m->motor_id] % window == 0)
    {
        m->speed = (m->encoder - m->encoder_prev)/(Ts * (double)window);
        m->encoder_prev = m->encoder;
        cnt[m->motor_id] = 0;
    }
}

int motor_run(motor* m, unsigned int cmd, int pwm_set)
{
   int r = LG_OKAY;

   r = lgGpioWrite(m->chip_handle, m->io.outputs[0], cmd & 1);
   r = lgGpioWrite(m->chip_handle, m->io.outputs[1], cmd >> 1);
    
   if (r != LG_OKAY) 
   {
      printf("Could not set direction!\n");
      return r;
   }

   m->direction = (cmd == MOTOR_FORWARD) - (cmd == MOTOR_BACKWARDS);

   r = lgTxPwm(m->chip_handle, m->io.outputs[2], PWM_FREQ, pwm_set, 0, 0);

   m->pwm = pwm_set;

   return r;
}

void motor_stop(motor* m)
{
   motor_run(m, MOTOR_STOP, 0);
}
