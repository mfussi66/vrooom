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
    communicator = std::make_unique<Comms>("/twist.set");
}

Rover::~Rover()
{
}

int Rover::start()
{
    left_wheel->setup();
    right_wheel->setup();

    std::thread tml(&Motor::run, left_wheel.get());
    std::thread tmr(&Motor::run, right_wheel.get());
    std::thread rr(&Rover::run, this);
    
    rr.join();
    tml.join();
    tmr.join();

    close();

    return 0;
}

void Rover::run()
{
    while(!should_stop.test())
    {
        communicator->lcm_ptr->handleTimeout(5);
        run_speed_ctrl();
        std::this_thread::sleep_for(10ms);
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

    communicator->publishCommands(wl, wr);
}
