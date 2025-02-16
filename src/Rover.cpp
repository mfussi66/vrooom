#include <Motor.h>
#include <Rover.h>
#include <control.h>
#include "mockHardware.h"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std::chrono_literals;

Rover::Rover(std::unique_ptr<GPIOInterface> gpio_l, std::unique_ptr<GPIOInterface> gpio_r)
{

    left_wheel = std::make_unique<Motor>(0, std::move(gpio_l));
    right_wheel = std::make_unique<Motor>(1, std::move(gpio_r));
    communicator = std::make_unique<Comms>("inputs.twist_refs");
}

Rover::~Rover()
{
}

void Rover::start()
{
    left_wheel->setup();
    right_wheel->setup();

    std::thread tml(&Motor::run, left_wheel.get());
    std::thread tmr(&Motor::run, right_wheel.get());
    std::thread rr(&Rover::run, this);
    
    rr.join();
    tml.join();
    tmr.join();
}

void Rover::run()
{
    while(!should_stop.test())
    {
        run_speed_ctrl();
        std::this_thread::sleep_for(200ms);
    }
}

void Rover::stop()
{
    left_wheel->stop();
    right_wheel->stop();
}

void Rover::close()
{
    std::cout << "Closing rover..." <<std::endl;
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

void Rover::compute_odometry(double wl, double wr)
{
    double V = (wr + wl) / 2 * R;
    double W = (wr - wl);
}

void Rover::run_speed_ctrl()
{
    auto refs = communicator->get_twist_references();

    compute_odometry(1.0, 1.0);

    double wl = refs.first / R / 2 - refs.second / 2;
    double wr = refs.first / R / 2 + refs.second / 2;

    left_wheel->set_input(wl);
    right_wheel->set_input(wr);

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
