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

   rover_run(30, ROVER_RIGHT);

   int encoder_left = 0;
   int encoder_right = 0;

   while (keepRunning)
   {
      lguSleep(0.01);

      rover_read_encoders(&encoder_left, &encoder_right);
      
      printf("left= %d  right=%d\n", encoder_left, encoder_right);
   }

   printf("Quitting...\n");

   rover_close();
}
