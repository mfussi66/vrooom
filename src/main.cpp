#include <Rover.h>

#include <iostream>
#include <csignal>
#include <memory>
#include "mockHardware.h"

using namespace std::chrono_literals;

static volatile std::sig_atomic_t keepRunning = 1;

void intHandler(int d)
{
   keepRunning = 0;
}

int main(int argc, char *argv[])
{
   signal(SIGINT, intHandler);

   bool use_sim = false;

   //if (argc >= 2)
   // {
   //    std::string s(argv[1]);

   //    if (s == "sim")
   //    {
   //       std::printf("using sim\n");
   //    }
   // }
   // else
   // {
   //    std::printf("NOT using sim\n");
   // }

   auto mock = std::make_unique<mockHardware>();
   Rover simulated_rover(std::move(mock));

   simulated_rover.setup();

/*    rover_setup();

   while (keepRunning)
   {
      std::this_thread::sleep_for(10ms);

      rover_read_encoders();
      rover_estimate_wheels_speeds();

      rover_run_speed_ctrl(10, 10);

      static int cnt = 0;
      if (++cnt % 100 == 0)
      {
         double wl = 0;
         double wr = 0;
         double al = 0;
         double ar = 0;
         rover_get_wheels_angles(&al, &al);
         rover_get_wheels_speeds(&wl, &wr);

         printf("L = %.3f %.3f | R = %.3f %.3f\n", al, wl, ar, wr);
         cnt = 0;
      }
   }
 */
   printf("Quitting...\n");

  // rover_close();

  return 0;
}
