#ifndef CTRL_H
#define CTRL_H

typedef struct
{
    double x;
    double x0;
    double Ts;
    double ki;
} Integrator;

typedef struct
{
    double kp;
    Integrator integrator;
    double kd;
    double Ts;
} PID;

typedef struct
{
    PID l_wheel_pid;
    PID r_wheel_pid;
} MotionController;

extern MotionController motion_controller;

void wheels_pid_init();

double pid_step(PID* pid, double r, double y);

void motion_control_step(double *r, double *y, double* u);

#endif
