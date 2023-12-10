#ifndef Movement_h_
#define Movement_h_

#include <cmath>

// CAMERA
constexpr float CAMERA_A = 100;
constexpr float CAMERA_RESET_A = 150;
constexpr float CAMERA_SPEED_LIM = 300;

// GENERAL
constexpr float DAMP_STATIC = .5F;
constexpr float DAMP_MOVING = .8F;

// TUKI OVERWORLD
constexpr float TOW_SPEED_LIM = 500;
constexpr float TOW_A = 1500;
constexpr float TOW_DAMP_STATIC = .5F;
constexpr float TOW_DAMP_MOVING = .8F;


constexpr float TOW_DASH_M = 10;
constexpr float TOW_DASH_SPEED = 2500;
constexpr float TOW_DASH_TIME = 0.5F;
constexpr float TOW_DASH_DAMP = .001F;

// PAVAO
constexpr float PAVAO_SPEED_LIM = 150;
constexpr float PAVAO_A = 1500;

// PANCAKE
constexpr float PANCAKE_SPEED_LIM = 200;
constexpr float PANCAKE_A = 1500;


#endif