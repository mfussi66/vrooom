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

   std::string input;

   if ( (argc <= 1) || (argv[argc-1] == NULL)) {
      std::cerr << "No argument provided (--sim or --rover)!" << std::endl;
      return 1;
   }
   else {
      input = argv[argc-1];
   }

   if (input == "--sim")
   {
      std::cout << "Using simulation mode" << std::endl;

      auto left = std::make_unique<mockHardware>();
      auto right = std::make_unique<mockHardware>();
      Rover rover(std::move(left), std::move(right));
      return rover.start();
   }
   #if USE_LGPIO==1
   else if(input == "--rover")
   {
      std::cout << "Using Rover mode" << std::endl;

      auto left = std::make_unique<Hardware>(motor_left_io);
      auto right = std::make_unique<Hardware>(motor_right_io);
      Rover rover(std::move(left), std::move(right));
      return rover.start();
   }
   #endif
   else
   {
      std::cerr << "Unsupported mode " << input << std::endl <<
      "Supported modes are --sim and --rover" << std::endl;
   }
}
