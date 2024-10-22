#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include <motor.h>
#include <hardware.h>
#include <rover.h>

#include <lgpio.h>

static volatile int keepRunning = 1;

void intHandler(int d)
{
   keepRunning = 0;
}

int main(int argc, char *argv[])
{
   signal(SIGINT, intHandler);

   rover_setup();

   while (keepRunning)
   {
      lguSleep(0.001);

      rover_read_encoders();
      rover_estimate_wheels_speeds();

      rover_run_speed_ctrl(10, 10);

      static int cnt = 0;
      if(++cnt % 100 == 0)
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

   printf("Quitting...\n");

   rover_close();
}
