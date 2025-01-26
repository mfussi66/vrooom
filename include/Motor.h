#pragma once

//#include <hardware.h>

#include "GPIOInterface.h"

#include <cmath>
#include <cstdio>
#include <thread>
#include <memory>

class Motor {
public:
    enum class Direction {
        Stop = 0b0,
        Forward = 0b10,
        Backwards = 0b01
    };

    static constexpr double PWM_FREQ = 1000;
    static constexpr double ENCODER_RESOLUTION = 1986.0;

    Motor(std::shared_ptr<GPIOInterface> gpio);
    int setup(int id, gpioGroup* gpio);
    void read_encoder();
    void estimate_speed(int window, double Ts);
    int run(Direction cmd, int pwmSet);
    void stop();

    double getAngle() const {
        return (static_cast<double>(encoder_) / ENCODER_RESOLUTION) * 2.0 * M_PI;
    }

private:
    std::shared_ptr<GPIOInterface> m_gpio;
    int id_;
    double encoder_ = 0.0;
    double encoderPrev_ = 0.0;
    double speed_ = 0.0;
    int encoderPulsePrev_ = 0;
    int pwm_ = 0;
    Direction direction_ = Direction::Stop;
    gpioGroup io_;
};
