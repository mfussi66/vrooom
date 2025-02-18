#include <Motor.h>
#include <globals.h>

#include <stdlib.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

constexpr double kv = 1; // V/rpm

Motor::Motor(int id, std::unique_ptr<GPIOInterface> gpio) : m_gpio(std::move(gpio)),
                                                            id_(id)
{
}

int Motor::setup()
{
   m_gpio->claim_output();
   m_gpio->claim_input();
   return 0;
}

void Motor::read_encoder()
{
   int v = m_gpio->read_pin(0);
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

int Motor::run()
{
   while (!should_stop.test())
   {
      read_encoder();

      m_gpio->set_pwm(pwm_ * kv);
      direction_sign_ = (pwm_ > 0) - (pwm_ < 0);

     // std::cout << std::format("motor {} pwm {}", id_, pwm_ ) << std::endl;
      std::this_thread::sleep_for(10ms);
   }

   return 0;
}

void Motor::set_input(int pwm)
{
   pwm_ = pwm;
}

void Motor::stop()
{
   set_input(0);
}
