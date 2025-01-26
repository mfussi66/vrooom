//#include <motor.h>
#include <Rover.h>
#include <control.h>
#include "mockHardware.h"

#include <iostream>
#include <memory>

Rover::Rover(std::shared_ptr<GPIOInterface> gpio) : m_gpio(std::move(gpio))
{
}

Rover::~Rover()
{
}

int Rover::setup()
{
    left_wheel_th = std::make_unique<Motor>(std::move(m_gpio));
    right_wheel_th = std::make_unique<Motor>(std::move(m_gpio));

    return 0;
}

void Rover::run(int pwm_set_left, int pwm_set_right, unsigned int direction)
{
    // if (direction != ROVER_FORWARD &&
    //     direction != ROVER_BACKWARDS &&
    //     direction != ROVER_LEFT &&
    //     direction != ROVER_RIGHT &&
    //     direction != ROVER_STOP)
    // {
    //     stop();
    //     return;
    // }

    // motor_run(&motor_left, direction & 0b11, pwm_set_left);
    // motor_run(&motor_right, (direction >> 2), pwm_set_right);
}

void Rover::stop()
{
    // motor_stop(&motor_left);
    // motor_stop(&motor_right);
    motion_state = 0;
}

void Rover::close()
{
    stop();
    //free_stuff(chip_handle);
}

void Rover::read_encoders()
{
    // motor_read_encoder(&motor_left);
    // motor_read_encoder(&motor_right);
}

void Rover::get_wheels_angles(double *left, double *right)
{
    // *left = motor_get_angle(&motor_left);
    // *right = motor_get_angle(&motor_right);
}

void Rover::estimate_wheels_speeds()
{
    // motor_estimate_speed(&motor_left, 64, 0.001);
    // motor_estimate_speed(&motor_right, 64, 0.001);
}

void Rover::get_wheels_speeds(double *vl, double *vr)
{
    // *vl = motor_left.speed;
    // *vr = motor_right.speed;
}

void Rover::run_speed_ctrl(double l_ref, double r_ref)
{
    // double y[2];
    // double r[2] = {l_ref, r_ref};
    // double u[2];

    // get_wheels_speeds(&y[0], &y[1]);

    // motion_control_step(r, y, u);

    // if (u[0] < 0)
    //     motor_run(&motor_left, MOTOR_BACKWARDS, u[0]);
    // else
    //     motor_run(&motor_right, MOTOR_FORWARD, u[0]);

    // if (u[1] < 0)
    //     motor_run(&motor_left, MOTOR_BACKWARDS, u[1]);
    // else
    //     motor_run(&motor_right, MOTOR_FORWARD, u[1]);
}
