
#include <lgpio.h>
#include <hardware.h>

gpioGroup motor_left_io = {
   {M_ENCODER_L}, 
   {M_IN1_L, M_IN2_L, M_EN_L}
};
gpioGroup motor_right_io = {
   {M_ENCODER_R}, 
   {M_IN1_R, M_IN2_R, M_EN_R}
};

int free_stuff(int h)
{
   lgGpioFree(h, M_ENCODER_L);
   lgGpioFree(h, M_ENCODER_R);
   lgGpioFree(h, M_IN1_L);
   lgGpioFree(h, M_IN2_L);
   lgGpioFree(h, M_IN1_R);
   lgGpioFree(h, M_IN2_R);

   return LG_OKAY;
}
