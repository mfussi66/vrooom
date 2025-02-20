#pragma once
#include "GPIOInterface.h"
#include <Motor.h>
#include <Comms.h>

#include <thread>

// enum
// {
//    ROVER_STOP = MOTOR_STOP,
//                                 // Right           Left
//    ROVER_FORWARD =      (MOTOR_FORWARD << 2)    + MOTOR_FORWARD,
//    ROVER_BACKWARDS =    (MOTOR_BACKWARDS << 2)  + MOTOR_BACKWARDS,
//    ROVER_LEFT =         (MOTOR_FORWARD << 2)    + MOTOR_BACKWARDS,
//    ROVER_RIGHT =        (MOTOR_BACKWARDS << 2)  + MOTOR_FORWARD
// };

class Rover
{
private:

   std::unique_ptr<Motor> left_wheel;
   std::unique_ptr<Motor> right_wheel;
   std::unique_ptr<Comms> communicator;

   void run();

   void run_speed_ctrl();

   void compute_odometry(double wl, double wr);

public:
   Rover(std::unique_ptr<GPIOInterface> gpio_l, std::unique_ptr<GPIOInterface> gpio_r);
   ~Rover();

   static constexpr double R = 0.03; // cm

   int start();

   void stop();

   void close();
};
