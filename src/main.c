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

   //rover_run(30, ROVER_RIGHT);

   double encoder_left = 0;
   double encoder_right = 0;

   double wl = 0;
   double wr = 0;

     double w_sp = 1;
     double e_l_old = 0;
     double e_r_old = 0;

   while (keepRunning)
   {
      lguSleep(0.001);

      rover_get_wheels_angles(&encoder_left, &encoder_right);
      rover_get_wheels_speeds(64, 0.001, &wl, &wr);

      // double e_l = w_sp - wl;
      // double e_r = w_sp - wr;

      // double u_l = e_l * 35 + 1000 * (e_l + e_l_old) * 0.001 / 2;
      // double u_r = e_r * 35 + 1000 * (e_r + e_r_old) * 0.001 / 2;

      // e_l_old = e_l;
      // e_r_old = e_r;

      // rover_run(u_l, u_r, ROVER_FORWARD);

      static int cnt = 0;
      if(++cnt % 10 == 0)
      {
         printf("left= %.3f %.3f | right=%.3f %.3f\n", encoder_left, wl, encoder_right, wr);
         cnt = 0;
      }
      
   }

   printf("Quitting...\n");

   rover_close();
}
