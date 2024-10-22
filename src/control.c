#include "control.h"

MotionController motion_controller = 
{
    .l_wheel_pid = {
        1.0,
        {0.0, 0.0, 0.001, 1.0},
        0.0,
        0.001
        },
    .r_wheel_pid = {
        1.0,
        {0.0, 0.0, 0.001, 1.0},
        0.0,
        0.001
        }
};


double integrator_step(Integrator *itg, double x)
{
     itg->x += x;
     itg->x *= (itg->ki / itg->Ts); 
}

double pid_step(PID* pid, double r, double y)
{
    double e = r - y;

    integrator_step(&pid->integrator, e);

    double u = pid->kp * e + pid->integrator.x;

    return u;
}

void motion_control_step(double *r, double *y, double* u)
{
    u[0] = pid_step(&motion_controller.l_wheel_pid, r[0], y[0]);
    u[1] = pid_step(&motion_controller.r_wheel_pid, r[1], y[1]);
}
