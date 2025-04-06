#include <Motor.h>
#include <globals.h>

#include <stdlib.h>
#include <memory>

constexpr double kv = 0.05; // V/rpm

Motor::Motor(int id, std::unique_ptr<GPIOInterface> gpio) : m_gpio(std::move(gpio)),
                                                            id_(id)
{
}

int Motor::setup()
{
   return m_gpio->setup();
}

void Motor::read_encoder()
{
   int v = m_gpio->read_encoder();
   encoder_ += direction_sign_ * abs(v - encoderPrev_);
   encoderPrev_ = v;
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

void Motor::set_input(int pwm)
{
   m_gpio->set_pwm(pwm * kv);
   direction_sign_ = (pwm > 0) - (pwm < 0);
}

void Motor::stop()
{
   set_input(0);
}
