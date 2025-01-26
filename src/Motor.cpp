#include <Motor.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory>
Motor::Motor(std::shared_ptr<GPIOInterface> gpio) : 
m_gpio(std::move(gpio))
{
}


int Motor::setup(int id, gpioGroup* gpio)
{
   id_ = id;
   //m->io = *gpio;

   m_gpio->claim_output();
   m_gpio->claim_input();

   // res = lgGroupClaimOutput(h, 0, 3, m->io.outputs, 0);
   // res = lgGpioClaimInput(h, LG_SET_PULL_UP, m->io.inputs[0]);

   // m->encoder = 0;
   // m->pwm = 0;
   // m->direction = 1;

   return 0;
}

void Motor::read_encoder()
{
   //int v = lgGpioRead(m->chip_handle, m->io.inputs[0]);
   
   // m->encoder += m->direction * abs(v - m->encoder_pulse_prev);

   // m->encoder_pulse_prev = v;
}

void Motor::estimate_speed(int window, double Ts)
{
   //  static int cnt[2] = {0, 0};

   //  if(++cnt[m->motor_id] % window == 0)
   //  {
   //      m->speed = (m->encoder - m->encoder_prev)/(Ts * (double)window);
   //      m->encoder_prev = m->encoder;
   //      cnt[m->motor_id] = 0;
   //  }
}

int Motor::run(Direction cmd, int pwmSet)
{
   // int r = LG_OKAY;

   // r = lgGpioWrite(m->chip_handle, m->io.outputs[0], cmd & 1);
   // r = lgGpioWrite(m->chip_handle, m->io.outputs[1], cmd >> 1);
    
   // if (r != LG_OKAY) 
   // {
   //    printf("Could not set direction!\n");
   //    return r;
   // }

   // m->direction = (cmd == MOTOR_FORWARD) - (cmd == MOTOR_BACKWARDS);

   // r = lgTxPwm(m->chip_handle, m->io.outputs[2], PWM_FREQ, pwm_set, 0, 0);

   // m->pwm = pwm_set;

   return 0;
}

void Motor::stop()
{
   // Motor::run(MOTOR_STOP, 0);
}

