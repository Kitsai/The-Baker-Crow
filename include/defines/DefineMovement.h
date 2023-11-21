#ifndef Movement_h_
#define Movement_h_

#include <cmath>

constexpr int GLOBAL_SPEED_SCALER = 100;

// CAMERA
#define CAMERA_A 100
#define CAMERA_RESET_A 150
#define CAMERA_SPEED_LIM 300

//TUKI OVERWORLD
#define TOW_SPEED_LIM 25
#define TOW_A 3000
constexpr float TOW_DAMP_STATIC = .5F;
constexpr float TOW_DAMP_MOVING = .8F;

#define TOW_DASH_SPEED 100
#define TOW_DASH_TIME 0.5F
constexpr float TOW_DASH_DAMP = .001F;

#endif