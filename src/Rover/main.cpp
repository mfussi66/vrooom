#include <Rover.h>
#include <globals.h>
#include <mockHardware.h>

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

   auto mock_left = std::make_unique<mockHardware>();
   auto mock_right = std::make_unique<mockHardware>();

   Rover rover(std::move(mock_left), std::move(mock_right));

   rover.start();
   
   printf("Quitting...\n");

   rover.close();

  return 0;
}
