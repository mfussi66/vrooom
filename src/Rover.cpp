#include <Motor.h>
#include <Rover.h>
#include <control.h>
#include "mockHardware.h"

#include <iostream>
#include <memory>
#include <thread>

Rover::Rover(std::unique_ptr<GPIOInterface> gpio_l, std::unique_ptr<GPIOInterface> gpio_r)
{

    left_wheel_th = std::make_unique<Motor>(0, std::move(gpio_l));
    right_wheel_th = std::make_unique<Motor>(1, std::move(gpio_r));
}

Rover::~Rover()
{
}

void Rover::run()
{
    left_wheel_th->setup();
    right_wheel_th->setup();

    std::thread tml(&Motor::run, left_wheel_th.get());
    std::thread tmr(&Motor::run, right_wheel_th.get());

    set_motor_inputs();

    tml.join();
    tmr.join();
}

void Rover::set_motor_inputs()
{
    left_wheel_th->set_input(20);
    right_wheel_th->set_input(-20);
}

void Rover::stop()
{
    left_wheel_th->stop();
    right_wheel_th->stop();
}

void Rover::close()
{
    stop();
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
