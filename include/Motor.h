#pragma once

#include "GPIOInterface.h"
#include "globals.h"

#include <cmath>
#include <memory>

class Motor {
public:

    static constexpr double PWM_FREQ = 1000;
    static constexpr double ENCODER_RESOLUTION = 1986.0;

    Motor(int id, std::unique_ptr<GPIOInterface> gpio);
    int setup();
    void read_encoder();
    void estimate_speed(int window, double Ts);
    int run();
    void set_input(int pwm);
    void stop();

    double getAngle() const {
        return (static_cast<double>(encoder_) / ENCODER_RESOLUTION) * 2.0 * M_PI;
    }

private:
    std::unique_ptr<GPIOInterface> m_gpio;
    int id_;
    double encoder_ = 0.0;
    double encoderPrev_ = 0.0;
    double speed_ = 0.0;
    int encoderPulsePrev_ = 0;
    int pwm_ = 0;
    double direction_sign_ = 0;
    gpioGroup io_;
};
