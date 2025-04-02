#include <Rover.h>
#include <globals.h>
#include <mockHardware.h>

#if USE_LGPIO
   #include <Hardware.h> 
#endif

#include <iostream>
#include <csignal>
#include <memory>

std::atomic_flag should_stop;

void shutdown(int d)
{
   should_stop.test_and_set();
}

int main(int argc, char *argv[])
{
   signal(SIGINT, shutdown);

   should_stop.clear();

   constexpr bool use_sim = true;

   if (use_sim)
   {
      auto left = std::make_unique<mockHardware>();
      auto right = std::make_unique<mockHardware>();
      Rover rover(std::move(left), std::move(right));
      return rover.start();
   }
   #if USE_LGPIO==1
   else
   {

      gpioGroup motor_left_io = {
         {M_ENCODER_L}, 
         {M_IN1_L, M_IN2_L, M_EN_L}
     };
     gpioGroup motor_right_io = {
         {M_ENCODER_R}, 
         {M_IN1_R, M_IN2_R, M_EN_R}
     };
   

      auto left = std::make_unique<Hardware>(motor_left_io);
      auto right = std::make_unique<Hardware>(motor_right_io);
      Rover rover(std::move(left), std::move(right));
      return rover.start();
   }
   #endif
}
