#include <Motor.h>
#include <Rover.h>
#include <control.h>
#include "mockHardware.h"

#include <iostream>
#include <memory>
#include <thread>
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
	int r = 0;

    r = left_wheel->setup();
    r = right_wheel->setup();

	if (r < 0)
	{
		std::cerr << "Could not set up motors!" << std::endl;
		return r;
	}

    std::thread rr(&Rover::run, this);
    
    rr.join();

    close();

    return r;
}

void Rover::run()
{
    while(!should_stop.test())
    {
        communicator->lcm_ptr->handleTimeout(5);
        run_pwm_ctrl();
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

void Rover::run_pwm_ctrl()
{
    auto refs = communicator->get_twist_references();

    compute_odometry(1.0, 1.0);

    double wl = refs.first / R / 2 - refs.second / 2;
    double wr = refs.first / R / 2 + refs.second / 2;

    //std::cout << wl << wr << std::endl;

    left_wheel->set_input(wl);
    right_wheel->set_input(wr);

    communicator->publishCommands(wl, wr);
}
