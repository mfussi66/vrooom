#pragma once
#include "GPIOInterface.h"
#include "Motor.h"

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
   double l_old = 0;
   double r_old = 0;

   std::unique_ptr<Motor> left_wheel_th;
   std::unique_ptr<Motor> right_wheel_th;

public:
   Rover(std::unique_ptr<GPIOInterface> gpio_l, std::unique_ptr<GPIOInterface> gpio_r);
   ~Rover();

   void run();

   void set_motor_inputs();

   void stop();

   void close();

   void read_encoders();

   void get_wheels_angles(double *left, double *right);

   void estimate_wheels_speeds();

   void get_wheels_speeds(double *vl, double *vr);

   void run_speed_ctrl(double l_ref, double r_ref);
};
