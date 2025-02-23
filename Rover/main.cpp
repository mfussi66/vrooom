#include <Rover.h>
#include <globals.h>
#include <mockHardware.h>
#include <Hardware.h>

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

   bool use_sim = true;

   if (use_sim)
   {
      auto left = std::make_unique<mockHardware>();
      auto right = std::make_unique<mockHardware>();
      Rover rover(std::move(left), std::move(right));
      return rover.start();
   }
   else
   {
      auto left = std::make_unique<Hardware>(motor_left_io);
      auto right = std::make_unique<Hardware>(motor_right_io);
      Rover rover(std::move(left), std::move(right));
      return rover.start();
   }
}
