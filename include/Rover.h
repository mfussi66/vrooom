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
  
// motor motor_left;
// motor motor_right;

int chip_handle = 0;

int motion_state = 0;
double l_old = 0;
double r_old = 0;

std::shared_ptr<GPIOInterface> m_gpio;

std::unique_ptr<Motor> left_wheel_th;
std::unique_ptr<Motor> right_wheel_th;

public:
   Rover(std::shared_ptr<GPIOInterface> gpio);
   ~Rover();

   int setup();

   void run(int pwm_set_left,int pwm_set_right, unsigned int direction);

   void stop();

   void close();

   void read_encoders();

   void get_wheels_angles(double* left, double* right);

   void estimate_wheels_speeds();

   void get_wheels_speeds(double* vl, double* vr);

   void run_speed_ctrl(double l_ref, double r_ref);

};

 
