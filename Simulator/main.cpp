#include <raylib.h>

#include <iostream>

#include "Comms.h"

std::array<double, 2> pwm = {10, -10};

void computeState(double& p_, double& theta_)
{
    double kv = 1;
    double R = 0.03;
    double v = (pwm[0] * kv + pwm[1] * kv) * R / 2;
    double w = (pwm[0] * kv - pwm[1] * kv);

    double ts = static_cast<double>(GetFrameTime());

    p_ += v * ts;
    theta_ += w * ts;
}

int main(int argc, char *argv[]) {

  Comms comms("rover.pwm.set");

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Rover Simulator");

  SetTargetFPS(60);

  double p = 0;
  double theta = 0;

  while (!WindowShouldClose()) {

    comms.checkMessages();

    computeState(p, theta);

    std::cerr << theta << std::endl;

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Viam Rover Simulator V0.0", 20, 20, 20, DARKGRAY);

    // Rectangle symbolizes the rover
    DrawRectanglePro((Rectangle) {screenWidth / 4 * 2 - 60, 250, 120, 60},
                    (Vector2) {0, 0}, theta, DARKBLUE);                 // Draw a color-filled rectangle with pro parameters


    EndDrawing();
  }
  CloseWindow();

  return 0;
}
